#include "rentalstore.h"
#include "TNDebug.h"

int g_iMoneyPos = 0;
int g_iStockPos = 0;

extern void Log(char * str1,char * str2,unsigned int ip);

CRentalStore::CRentalStore(void)
{
	m_hFileHandle = CreateFile("Data\\RentalStore.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

CRentalStore::~CRentalStore(void)
{
	if(m_hFileHandle != INVALID_HANDLE_VALUE) CloseHandle(m_hFileHandle);
}

void CRentalStore::HS_Init()
{
	m_byRentalTex = 0;
	m_dwRentalTexMoney = 0;

	m_dwEraseTime = MAX_ERASETIME;

	ZeroMemory(m_starrItem, sizeof(m_starrItem));
	ZeroMemory(m_starrMoney, sizeof(m_starrMoney));
	ZeroMemory(m_starrStockItem, sizeof(m_starrStockItem));

	m_mapItem.clear();					//	위탁 아이템
	m_mapItemStock.clear();				//	재고 아이템
	m_mapMoney.clear();					//	재고 루피아

	g_iMoneyPos = sizeof(m_starrItem);
	g_iStockPos = g_iMoneyPos + sizeof(m_starrMoney);

	HS_ReadData();
}

void CRentalStore::HS_ReadData()
{
	if(m_hFileHandle == INVALID_HANDLE_VALUE) return;

	DWORD dwRead = 0;
	LPOVERLAPPED lpOverlapped = NULL;

	time_t now; time(&now);

	int iRet = ReadFile(m_hFileHandle, m_starrItem, sizeof(m_starrItem), &dwRead, lpOverlapped);
	iRet = ReadFile(m_hFileHandle, m_starrMoney, sizeof(m_starrMoney), &dwRead, lpOverlapped);
	iRet = ReadFile(m_hFileHandle, m_starrStockItem, sizeof(m_starrStockItem), &dwRead, lpOverlapped);

	for(int i=0; i<MAX_RENTALSTORE*MAX_RENTALSTOREITEM; i++)	//	일정시간 주기로 time별 정리를 한다.
	{
		if(m_starrItem[i].szName[0]==0) continue;
		HS_bAddMapToStore(i);
	}

	for(i=0; i<MAX_RENTALUSER; i++)								//	호출되는 시점(서버시작시 정리를 한다)
	{
		if(m_starrMoney[i].szName[0]==0) continue;
		if(now-m_starrMoney[i].dwTime >= m_dwEraseTime)	//	삭제시간 초과시 삭제조치
		{
			char szData[128] = {0,};
			sprintf(szData, "ren Delete money from stock : %d", m_starrMoney[i].dwTime);
			//TimeWriteLog(szData, RENTALSTORE);
			Log(szData, "-system", NULL);
			ZeroMemory(&m_starrMoney[i], sizeof(m_starrMoney[i]));
			continue;
		}
		m_mapMoney.insert(std::map<char*, DWORD, HTStr>::value_type(m_starrMoney[i].szName, i));
	}
	for(i=0; i<MAX_RENTALITEM; i++)								//	호출되는 시점(서버시작시 정리를 한다)
	{
		if(m_starrStockItem[i].szName[0]==0) continue;
		if(now-m_starrStockItem[i].dwTime >= m_dwEraseTime)	//	삭제시간 초과시 삭제조치
		{
			char szData[256] = {0,};
			char szItem[128] = {0,};
			BASE_GetItemCode(&m_starrStockItem[i].stItem, szItem);
			sprintf(szData, "ren Delete item from stock %s", szItem);
			//TimeWriteLog(szData, RENTALSTORE);
			Log(szData, "-system", NULL);
			ZeroMemory(&m_starrStockItem[i], sizeof(m_starrStockItem[i]));
			continue;
		}
		HS_bAddMapToStock(i);
	}
}

//void CRentalStore::HS_WriteData()
//{
//	int iFile = open("RentalStore.bin", _O_WRONLY | _O_CREAT | _O_BINARY, NULL);
//	if(iFile == -1) return;
//
//	strncpy(m_starrItem[3].szName, "윤우경", SZNAME_LENGTH);
//	m_starrItem[3].dwPrice = 100;
//	m_starrItem[3].dwTime = 200;
//	m_starrItem[3].stItem.snIndex = 30000;
//
//	strncpy(m_starrMoney[3].szName, "윤지훈", SZNAME_LENGTH);
//	m_starrMoney[3].dwMoney = 400;
//	m_starrMoney[3].dwTime = 500;
//
//	strncpy(m_starrStockItem[3].szName, "윤지훈", SZNAME_LENGTH);
//	m_starrStockItem[3].dwTime = 600;
//	m_starrStockItem[3].stItem.snIndex = 700;
//
//	write(iFile, m_starrItem, sizeof(m_starrItem));
//	write(iFile, m_starrMoney, sizeof(m_starrMoney));
//	write(iFile, m_starrStockItem, sizeof(m_starrStockItem));
//	close(iFile);
//}

void CRentalStore::HS_CheckRentalStore()
{
	DWORD dwWritten = 0;
	time_t now; time(&now);
	LPOVERLAPPED lpOverlapped = NULL;
	for(int i=0; i<MAX_RENTALSTORE*MAX_RENTALSTOREITEM; i++)	//	일정시간 주기로 time별 정리를 한다.
	{
		if (m_starrItem[i].szName[0] == NULL) continue;
		if(m_starrItem[i].szName[0]==0) continue;

		if(m_starrItem[i].dwTime <= now)				//	렌탈시간 초과시 상점에서 아이템제거하고 제고목록으로 이동
		{
			for(int k=0; k<MAX_RENTALITEM; k++)
			{
				if(m_starrStockItem[k].szName[0]!=0) continue;
				strncpy(m_starrStockItem[k].szName, m_starrItem[i].szName, SZNAME_LENGTH);
				m_starrStockItem[k].dwTime = now;
				m_starrStockItem[k].stItem = m_starrItem[i].stItem;

				HS_bAddMapToStock(k);
				break;
			}
			if(k==MAX_RENTALITEM)	//	m_starrStockItem내에 저장공간이 남아 있지 않을 경우 
			{
				char szData[256] = {0,};
				char szItem[128] = {0,};
				BASE_GetItemCode(&m_starrStockItem[i].stItem, szItem);
				sprintf(szData, "ren Delete item from stock %s", szItem);
				//TimeWriteLog(szData, RENTALSTORE);
				Log(szData, "-system", NULL);
			}

			HS_bDeleteMapFromStore(i);
			ZeroMemory(&m_starrItem[i], sizeof(m_starrItem[i]));

			SetFilePointer(m_hFileHandle, sizeof(STRUCT_RENTALITEM)*i, 0, FILE_BEGIN);
			WriteFile(m_hFileHandle, &m_starrItem[i], sizeof(m_starrItem[i]), &dwWritten, lpOverlapped);
			SetFilePointer(m_hFileHandle, g_iStockPos+sizeof(STRUCT_RENTALSTOCK)*k, 0, FILE_BEGIN);
			WriteFile(m_hFileHandle, &m_starrStockItem[k], sizeof(m_starrStockItem[k]), &dwWritten, lpOverlapped);
		}
	}
}

void CRentalStore::HS_SetEraseDay(DWORD dwDay)
{
	m_dwEraseTime = dwDay*24*3600;
}

bool CRentalStore::HS_bAddItem(char* pName, int iStoreIndex, STRUCT_ITEM stItem, int iUserMoney, DWORD* pdwMoney, BYTE byHour)
{
	if(iStoreIndex<0 || iStoreIndex>=MAX_RENTALSTORE) return false;

	DWORD dwWritten = 0;
	DWORD dwPrice = *pdwMoney;
	LPOVERLAPPED lpOverlapped = NULL;

	//	1인당 최대 아이템 위탁갯수는 30개로 한정한다.
	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItem.find( pName );
	if ( it != m_mapItem.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD>& rSetChar = it->second;
		int iSize = rSetChar.size();
		if(iSize>=MAX_USERRENTALITEM) return false;
	}

	for(int i=iStoreIndex*MAX_RENTALSTOREITEM; i<(iStoreIndex+1)*MAX_RENTALSTOREITEM; i++)
	{
		if(m_starrItem[i].szName[0]==0) break;
	}

	if(i>=(iStoreIndex+1)*MAX_RENTALSTOREITEM) return false;

	double dRatio = m_byRentalTex/100.0;
	*pdwMoney = (DWORD)((*pdwMoney*dRatio)*((byHour/24.0)*1.01-0.01));
	if(iUserMoney<*pdwMoney) return false;
	
	time_t now; time(&now);
	m_starrItem[i].stItem = stItem;
	m_starrItem[i].dwPrice = dwPrice;
	m_starrItem[i].dwTime = now+byHour*3600;
	strncpy(m_starrItem[i].szName, pName, SZNAME_LENGTH);

	if(!HS_bAddMapToStore(i)) 
	{
		ZeroMemory(&m_starrItem[i], sizeof(m_starrItem[i]));
		return false;
	}

	if(m_dwRentalTexMoney<MAX_INT) m_dwRentalTexMoney += ((*pdwMoney)/2);

	SetFilePointer(m_hFileHandle, sizeof(STRUCT_RENTALITEM)*i, 0, FILE_BEGIN);
	WriteFile(m_hFileHandle, &m_starrItem[i], sizeof(m_starrItem[i]), &dwWritten, lpOverlapped);

	return true;;
}

int CRentalStore::HS_iGetStockItemCount(char* pName)
{
	int iCount = 0;
	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItemStock.find( pName );
	if ( it != m_mapItemStock.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD>& rSetChar = it->second;
		iCount = rSetChar.size();
	}

	return iCount;
}

//	케릭별 재고아이템을 하나 얻어온다.
bool CRentalStore::HS_bGetStockItem(char* pName, STRUCT_ITEM* pItem)
{
	int iIndex = 0;
	DWORD dwWritten = 0;
	LPOVERLAPPED lpOverlapped = NULL;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItemStock.find( pName );
	if ( it != m_mapItemStock.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD> rSetChar = it->second;
		std::set<DWORD>::iterator pos = rSetChar.begin();

        iIndex = *pos;
		rSetChar.erase(pos);
		if(iIndex<0 || iIndex>=MAX_RENTALITEM) return false;

		m_mapItemStock.erase(it);

		if(!rSetChar.empty())
		{
			std::set<DWORD>::iterator pos = rSetChar.begin();
			int iItemIndex = *pos;
			m_mapItemStock.insert(std::map<char*, std::set<DWORD>, HTStr>::value_type(m_starrStockItem[iItemIndex].szName, rSetChar));
		}

		*pItem = m_starrStockItem[iIndex].stItem;
		ZeroMemory(&m_starrStockItem[iIndex], sizeof(m_starrStockItem[iIndex]));

		SetFilePointer(m_hFileHandle, g_iStockPos+sizeof(STRUCT_RENTALSTOCK)*iIndex, 0, FILE_BEGIN);
		WriteFile(m_hFileHandle, &m_starrStockItem[iIndex], sizeof(m_starrStockItem[iIndex]), &dwWritten, lpOverlapped);
	}
	else
		return false;

	return true;
}


//	위탁상점별 아이템리스트를 얻어온다
void CRentalStore::HS_GetItemList(int iStoreIndex, STRUCT_RENTALITEM* pItemList)	
{
	if(iStoreIndex<0 || iStoreIndex>=MAX_RENTALSTORE) return;

	memcpy(pItemList, &m_starrItem[iStoreIndex*MAX_RENTALSTOREITEM], sizeof(STRUCT_RENTALITEM)*MAX_RENTALSTOREITEM);
}

//	케릭별 위탁한 아이템리스트를 얻어온다
void CRentalStore::HS_GetItemList(char* pName, STRUCT_RENTALITEM* pItemList, WORD* pwIndex)
{
	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItem.find( pName );
	if ( it != m_mapItem.end() )		//	해당유저의 set이 존재할 경우
	{
		int iIndex = 0;
		int iPosition = 0;

		int iMax = MAX_RENTALSTORE*MAX_RENTALSTOREITEM;
		std::set<DWORD>& rSetChar = it->second;
		std::set<DWORD>::iterator pos;
		for(pos=rSetChar.begin(); pos!=rSetChar.end(); pos++)
		{
			iIndex = *pos;
			if(iIndex>=0 && iIndex<iMax) 
			{
				memcpy(pItemList+iPosition, &m_starrItem[iIndex], sizeof(STRUCT_RENTALITEM));
				pwIndex[iPosition] = iIndex;
				++iPosition; continue;
			}
			rSetChar.erase(iIndex);		//	들어갈수 없는 값이 들어가 잇다.(cri)
		}
	}
}

void CRentalStore::HS_GetStockItemList(char* pName, int iFromIndex, STRUCT_RENTALSTOCK* pItemList)
{
	int iIndex = 0;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItemStock.find( pName );
	if ( it != m_mapItemStock.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD>& rSetChar = it->second;
		std::set<DWORD>::iterator pos;
		int iCount = rSetChar.size();
		if(iCount>30) iCount=30;

		int iIndex = 0;
		pos = rSetChar.begin();
		for(int i=0; i<iFromIndex; i++) pos++;

		for(i=0; i<iCount; i++)
		{
			iIndex = *pos;
			if(iIndex<0 || iIndex>=MAX_RENTALITEM) continue;

			memcpy(pItemList++, &m_starrStockItem[iIndex], sizeof(STRUCT_RENTALSTOCK));
			pos++;
			if(pos==rSetChar.end()) break;
		}
	}
	else
		return;
}

bool CRentalStore::HS_bDeleteItem(char* pName, int iIndex, STRUCT_ITEM* stItem)
{
	if(iIndex<0 || iIndex>=MAX_RENTALSTORE*MAX_RENTALSTOREITEM) return false;
	if(strncmp(pName, m_starrItem[iIndex].szName, SZNAME_LENGTH) != 0) return false;

	DWORD dwWritten = 0;
	LPOVERLAPPED lpOverlapped = NULL;
	bool bRet = HS_bDeleteMapFromStore(iIndex);
	if(!bRet) return false;

	*stItem = m_starrItem[iIndex].stItem;
	ZeroMemory(&m_starrItem[iIndex], sizeof(m_starrItem[iIndex]));

	SetFilePointer(m_hFileHandle, sizeof(STRUCT_RENTALITEM)*iIndex, 0, FILE_BEGIN);
	WriteFile(m_hFileHandle, &m_starrItem[iIndex], sizeof(m_starrItem[iIndex]), &dwWritten, lpOverlapped);

	return true;
}

bool CRentalStore::HS_bAddMapToStore(int iIndex)
{
	if(iIndex<0 || iIndex>=MAX_RENTALSTORE*MAX_RENTALSTOREITEM) return false;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItem.find( m_starrItem[iIndex].szName );
	if ( it != m_mapItem.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD>& rSetChar = it->second;
		rSetChar.insert(std::set<DWORD>::value_type(iIndex));
	}
	else								//	해당유저의 set이 존재하지 않을 경우
	{
		std::set<DWORD> tempSet;
		tempSet.insert(std::set<DWORD>::value_type(iIndex));
		m_mapItem.insert(std::map<char*, std::set<DWORD>, HTStr>::value_type(m_starrItem[iIndex].szName, tempSet));
	}

	return true;
}

bool CRentalStore::HS_bDeleteMapFromStore(int iIndex)
{
	if(iIndex<0 || iIndex>=MAX_RENTALSTORE*MAX_RENTALSTOREITEM) return false;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItem.find( m_starrItem[iIndex].szName );
	if ( it != m_mapItem.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD> rSetChar = it->second;
		rSetChar.erase(iIndex);
		m_mapItem.erase(it);

		if(!rSetChar.empty())
		{
			std::set<DWORD>::iterator pos = rSetChar.begin();
			int iItemIndex = *pos;
			m_mapItem.insert(std::map<char*, std::set<DWORD>, HTStr>::value_type(m_starrItem[iItemIndex].szName, rSetChar));
		}
	}
	else
	{
		return false;					//	데이터가 없는데 삭제하려고 한 경우
	}

	return true;
}

bool CRentalStore::HS_bAddMapToStock(int iIndex)
{
	if(iIndex<0 || iIndex>=MAX_RENTALITEM) return false;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItemStock.find( m_starrStockItem[iIndex].szName );
	if ( it != m_mapItemStock.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD>& rSetChar = it->second;
		rSetChar.insert(std::set<DWORD>::value_type(iIndex));
	}
	else									//	해당유저의 set이 존재하지 않을 경우
	{
		std::set<DWORD> tempSet;
		tempSet.insert(std::set<DWORD>::value_type(iIndex));
		m_mapItemStock.insert(std::map<char*, std::set<DWORD>, HTStr>::value_type(m_starrStockItem[iIndex].szName, tempSet));
	}

	return true;
}

bool CRentalStore::HS_bDeleteMapFromStock(int iIndex)
{
	if(iIndex<0 || iIndex>=MAX_RENTALITEM) return false;

	std::map<char*, std::set<DWORD>, HTStr>::iterator it = m_mapItemStock.find( m_starrStockItem[iIndex].szName );
	if ( it != m_mapItemStock.end() )		//	해당유저의 set이 존재할 경우
	{
		std::set<DWORD> rSetChar = it->second;
		rSetChar.erase(iIndex);
		m_mapItemStock.erase(it);

		if(!rSetChar.empty())
		{
			std::set<DWORD>::iterator pos = rSetChar.begin();
			int iItemIndex = *pos;
			m_mapItemStock.insert(std::map<char*, std::set<DWORD>, HTStr>::value_type(m_starrStockItem[iItemIndex].szName, rSetChar));
		}
	}
	else
	{
		return false;					//	데이터가 없는데 삭제하려고 한 경우
	}

	return true;
}

byte CRentalStore::HS_GetRentalTex()
{
	return m_byRentalTex;
}

void CRentalStore::HS_SetRentalTex(byte byTex)
{
	m_byRentalTex = byTex;
}

void CRentalStore::HS_SetRentalTexMoney(DWORD dwTexMoney)
{
	m_dwRentalTexMoney = dwTexMoney;
}

void CRentalStore::HS_GetTexMoney(DWORD* dwTexMoney, bool bSearch)
{
	*dwTexMoney = m_dwRentalTexMoney;

	if(!bSearch) m_dwRentalTexMoney = 0;
}


bool CRentalStore::HS_bGetMoney(char* pName, DWORD* pdwMoney, bool bSearch)
{
	DWORD dwWritten = 0;
	LPOVERLAPPED lpOverlapped = NULL;
	std::map<char*, DWORD, HTStr>::iterator it = m_mapMoney.find(pName);
	if ( it != m_mapMoney.end() )		//	해당유저의 set이 존재할 경우
	{
		int iIndex = it->second;
		if(iIndex<0 || iIndex>=MAX_RENTALUSER) return false;

		*pdwMoney = m_starrMoney[iIndex].dwMoney;

		if(!bSearch) 
		{	ZeroMemory(&m_starrMoney[iIndex], sizeof(m_starrMoney[iIndex]));
			m_mapMoney.erase(it);

			SetFilePointer(m_hFileHandle, g_iMoneyPos+sizeof(STURCT_RENTALAWARD)*iIndex, 0, FILE_BEGIN);
			WriteFile(m_hFileHandle, &m_starrMoney[iIndex], sizeof(m_starrMoney[iIndex]), &dwWritten, lpOverlapped);
		}
	}
	else
		*pdwMoney = 0;

	return true;
}

void CRentalStore::HS_StockItem(DWORD dwStore)
{
	if(dwStore >= MAX_RENTALSTORE) return;

	DWORD dwWritten = 0;
	LPOVERLAPPED lpOverlapped = NULL;
	time_t now; time(&now);
	int iIndex = dwStore*30;

	for(int i=0; i<MAX_RENTALSTORE*MAX_RENTALSTOREITEM; i++)	//	일정시간 주기로 time별 정리를 한다.
	{
		if(m_starrItem[i].szName[0]==0) continue;

		if(m_starrItem[i].dwTime <= now)						//	렌탈 초과시 상점에서 아이템제거하고 제고목록으로 이동
		{
			for(int k=0; k<MAX_RENTALITEM; k++)
			{
				if(m_starrStockItem[k].szName[0]!=0) continue;
				strncpy(m_starrStockItem[k].szName, m_starrItem[i].szName, SZNAME_LENGTH);
				m_starrStockItem[k].dwTime = now;
				m_starrStockItem[k].stItem = m_starrItem[i].stItem;

				HS_bAddMapToStock(k);
			}
			if(k==MAX_RENTALITEM)	//	m_starrStockItem내에 저장공간이 남아 있지 않을 경우 
			{
				char szData[256] = {0,};
				char szItem[128] = {0,};
				BASE_GetItemCode(&m_starrStockItem[i].stItem, szItem);
				sprintf(szData, "ren Delete item from stock %s", szItem);
				//TimeWriteLog(szData, RENTALSTORE);
				Log(szData, "-system", NULL);
			}

			HS_bDeleteMapFromStore(i);
			ZeroMemory(&m_starrItem[i], sizeof(m_starrItem[i]));

			SetFilePointer(m_hFileHandle, sizeof(STRUCT_RENTALITEM)*i, 0, FILE_BEGIN);
			WriteFile(m_hFileHandle, &m_starrItem[i], sizeof(m_starrItem[i]), &dwWritten, lpOverlapped);
			SetFilePointer(m_hFileHandle, g_iStockPos+sizeof(STRUCT_RENTALSTOCK)*k, 0, FILE_BEGIN);
			WriteFile(m_hFileHandle, &m_starrStockItem[k], sizeof(m_starrStockItem[k]), &dwWritten, lpOverlapped);
		}
	}	
}

void CRentalStore::HS_GetShopItemPrice(int iIndex, int* piPrice)
{
	if(iIndex<0 || iIndex>=MAX_RENTALSTORE*MAX_RENTALSTOREITEM)
		*piPrice = 0;
	else
        *piPrice = m_starrItem[iIndex].dwPrice;
}

bool CRentalStore::HS_bBuyItem(int iIndex, STRUCT_ITEM stItem)
{
	if(iIndex<0 || iIndex>=MAX_RENTALSTORE*MAX_RENTALSTOREITEM) return false;
	if(memcmp(&m_starrItem[iIndex].stItem, &stItem, sizeof(m_starrItem[iIndex].stItem)) != 0) return false;

	DWORD dwWritten = 0;
	LPOVERLAPPED lpOverlapped = NULL;
	time_t now; time(&now);

	std::map<char*, DWORD, HTStr>::iterator it = m_mapMoney.find( m_starrItem[iIndex].szName );
	if ( it != m_mapMoney.end() )		//	해당유저의 set이 존재할 경우
	{
		int iMoneyIndex = it->second;
		if(iMoneyIndex<0 || iMoneyIndex>=MAX_RENTALUSER)	//	맵데이터오류
		{
			m_mapMoney.erase(it);
			char szData[128] = {0,};
			sprintf(szData, "ren HS_bBuyItem mapdata error char:%s index:%d \r\n", m_starrItem[iIndex].szName, iIndex);
			//TimeWriteLog(szData, RENTALSTORE);
			Log(szData, "-system", NULL);
			return false;
		}
		m_starrMoney[iMoneyIndex].dwMoney += m_starrItem[iIndex].dwPrice;
		m_starrMoney[iMoneyIndex].dwTime = now;

		SetFilePointer(m_hFileHandle, g_iMoneyPos+sizeof(STURCT_RENTALAWARD)*iMoneyIndex, 0, FILE_BEGIN);
		WriteFile(m_hFileHandle, &m_starrMoney[iMoneyIndex], sizeof(m_starrMoney[iMoneyIndex]), &dwWritten, lpOverlapped);
	}
	else
	{
		for(int i=0; i<MAX_RENTALUSER; i++)
		{
			if(m_starrMoney[i].szName[0]!=0) continue;
			strncpy(m_starrMoney[i].szName, m_starrItem[iIndex].szName, sizeof(m_starrMoney[i].szName));
			m_starrMoney[i].dwMoney = m_starrItem[iIndex].dwPrice;
			m_starrMoney[i].dwTime = now;
			break;
		}
		if(i==MAX_RENTALUSER)	//	해당 아이템소유자의 돈을 쌓을 공간이 부족하다
			return false;

		m_mapMoney.insert(std::map<char*, DWORD, HTStr>::value_type(m_starrMoney[i].szName, i));
	}

	HS_bDeleteMapFromStore(iIndex);
	ZeroMemory(&m_starrItem[iIndex], sizeof(m_starrItem[iIndex]));

	SetFilePointer(m_hFileHandle, sizeof(STRUCT_RENTALITEM)*iIndex, 0, FILE_BEGIN);
	WriteFile(m_hFileHandle, &m_starrItem[iIndex], sizeof(m_starrItem[iIndex]), &dwWritten, lpOverlapped);

	return true;
}


