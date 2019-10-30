//	.\\Data\\Event1.bin ~ .\\Data\\Event8.bin 까지 이벤트 대상 파일이 존재할수 있다.
//	단 해당 파일이 존재시 Event1 ~ Event8까지 실행가능하다.
//	만약 HTSETTINGS.TXL파일에 이벤트로 등록이 되어 있는데 해당파일이 없을 경우에는 
//	대상을 웹에서 클라이언트를 통해 전달해 주는 것으로 한다.


#include "stdafx.h"
#include "GameEvent.h"
#include "TNDebug.h"

//	STGAMEEVENT				g_kGameEvent[MAX_EVENT];

CGameEvent::CGameEvent()
{
	m_dwEvent = 0;
	ZeroMemory(m_bIsFromWeb, sizeof(m_bIsFromWeb));
	ZeroMemory(m_kEvent, sizeof(m_kEvent));
}

CGameEvent::~CGameEvent()
{
	char* pData = NULL;

	for(int i=0; i<MAX_EVENT; i++)
	{
		if(m_setUser[i].size()!=0)
		{
			std::set<char*, HTStr>::iterator pos;
			for(pos = m_setUser[i].begin(); pos != m_setUser[i].end(); ++pos)
			{
				pData = *pos;
				delete pData;
			}
			m_setUser[i].clear();

		}
		if(m_setUserDone[i].size()!=0)
		{
			std::set<char*, HTStr>::iterator pos;
			for(pos = m_setUserDone[i].begin(); pos != m_setUserDone[i].end(); ++pos)
			{
				pData = *pos;
				delete pData;
			}
			m_setUserDone[i].clear();
		}
	}
}

void CGameEvent::Initialize(int iZone, STGAMEEVENT* pEventList)
{
	if(iZone<0 || iZone>=32) return;
	memcpy(m_kEvent, pEventList, sizeof(m_kEvent)); 
	for(int i=0; i<MAX_EVENT; i++)
	{
		if(m_kEvent[i].iEventID == 0) continue;				//	hssetting.txl에 등록되지 않은 경우
		
		DWORD dwZone = 0x00000001 << iZone;
		if((dwZone & m_kEvent[i].iZone) == 0) continue;		//	등록은 되엇으나 이벤트 대상 존이 아닌경우

		DWORD dwFlag = 0x00000001 << i;		//	Active Event setting
		m_dwEvent |= dwFlag;

		if(!ReadEvent(i, m_kEvent[i].iTarget))
		{
			m_bIsFromWeb[i] = true;
			if(m_kEvent[i].iType==0)
				ReadEventDone(i, m_kEvent[i].iTarget);
		}
	}

	m_Coupon.Initialize();

#ifdef __IWANTIT__
	m_IWantIt.Initialize();
#endif	//	#ifdef __IWANTIT__

#ifdef __MICROSOUND__
	m_MicroSound.Initialize();
#endif	//	#ifdef __MICROSOUND__

}

void CGameEvent::CloseEvent()
{
	m_Coupon.CloseEvent();

#ifdef __IWANTIT__
	m_IWantIt.CloseEvent();
#endif	//	#ifdef __IWANTIT__
}

bool CGameEvent::ReadEvent(DWORD dwEvent, int iTarget)
{
	if(dwEvent>=MAX_EVENT) return false;
	if(iTarget<0 || iTarget>2) return false;

	char* pUser = NULL;
	char szFile[32] = {0,};

	sprintf(szFile, EVENTFILE, dwEvent);

	FILE *fp = fopen(szFile, "rt");
	if(fp==NULL) return false;

	while(1)
	{
		if(iTarget==0)					//	계정 참조
			pUser = new char[ACCOUNTNAME_LENGTH];
		else if(iTarget==1) 			//	케릭터 참조
			pUser = new char[SZNAME_LENGTH];
		else							//	길드 참조
			pUser = new char[SZGUILD_LENGTH];


		char * ret = fgets((char*)pUser,ACCOUNTNAME_LENGTH,fp);
		if (ret==NULL) break;

        pUser[strlen(pUser)-1] = 0;
		m_setUser[dwEvent].insert(std::set<char*, HTStr>::value_type(pUser));
	}

	delete[] pUser;
	fclose(fp);

	sprintf(szFile, EVENTFILE_DONE, dwEvent);
	fp = fopen(szFile, "rt");
	if(fp != NULL && m_setUser[dwEvent].size()!=0)
	{
		while(1)
		{
			char pTemp[ACCOUNTNAME_LENGTH] = {0,};
			if( fscanf(fp, "%s", pTemp) == EOF ) break;
			std::set<char*, HTStr>::iterator it = m_setUser[dwEvent].find( pTemp );
			if ( it != m_setUser[dwEvent].end() )	//	아이템을 받아갓으나 지급자 리스트에서 안빠진 경우(비정상 서버종료등등)
			{
				pUser = *it;
				delete[] pUser;
				m_setUser[dwEvent].erase(it);
			}
		}
		fclose(fp);
	}
	return true;
}

void CGameEvent::RemoveEvent(DWORD dwIndex, char* pUser)
{
	if(dwIndex>=MAX_EVENT) return;

	char* pData = NULL;
	if(m_bIsFromWeb[dwIndex])	//	m_setUser를 사용하지 않는다.
	{
		if(m_kEvent[dwIndex].iTarget==0)									//	계정 참조
		{
			pData = new char[ACCOUNTNAME_LENGTH];
			strncpy(pData, pUser, ACCOUNTNAME_LENGTH);
		}
		else if(m_kEvent[dwIndex].iTarget==1)								//	케릭터 참조
		{
			pData = new char[SZNAME_LENGTH];
			strncpy(pData, pUser, SZNAME_LENGTH);
		}
		else																//	길드 참조
		{
			pData = new char[SZGUILD_LENGTH];
			strncpy(pData, pUser, SZGUILD_LENGTH);
		}

		m_setUserDone[dwIndex].insert(std::set<char*, HTStr>::value_type(pData));
	}
	else						//	m_setUser를 사용한다.
	{
		std::set<char*, HTStr>::iterator it = m_setUser[dwIndex].find(pUser);
		if(it != m_setUser[dwIndex].end())
		{
			pData = *it;
			delete pData;
			m_setUser[dwIndex].erase(it);
		}
	}

	char szFile[32] = {0,};
	char temp[128] = {0,};
	sprintf(szFile, EVENTFILE_DONE, dwIndex);
	FILE *fp = fopen(szFile, "at");			//	서버의 비정상종료를 대비하여 지급한 대상자들 리스트를 별도로 관리한다.
	if(fp == NULL)
	{	sprintf(temp, "RemoveEvent File : %s fail. User:%s", szFile, pUser);
		TimeWriteLog(temp, EVENTFILE_LOG);
		return;
	}

	fprintf(fp, "%s\n", pUser);
	fclose(fp);
}

bool CGameEvent::ReadEventDone(DWORD dwEvent, int iTarget)
{
	if(dwEvent>=MAX_EVENT) return false;
	if(iTarget<0 || iTarget>1) return false;

	char* pUser = NULL;
	char szFile[32] = {0,};

	sprintf(szFile, EVENTFILE_DONE, dwEvent);

	FILE *fp = fopen(szFile, "rt");
	if(fp==NULL) return false;

	while(1)
	{
		if(iTarget==0)				//	계정 참조
			pUser = new char[ACCOUNTNAME_LENGTH];
		else if(iTarget==1)			//	케릭터 참조
			pUser = new char[SZNAME_LENGTH];
		else						//	길드 참조
			pUser = new char[SZGUILD_LENGTH];

		if( fscanf(fp, "%s", pUser) == EOF ) break;
		m_setUserDone[dwEvent].insert(std::set<char*, HTStr>::value_type(pUser));
	}
	delete[] pUser;
	fclose(fp);

	return true;
}

DWORD CGameEvent::GetEventID(DWORD dwWebEvent, char* pAccount, char* pChar, char* pGuild)
{
	DWORD dwEventID = 0;

	for(int i=0; i<MAX_EVENT; i++)
	{
		DWORD dwFlag = 0x00000001<<i;
		if((m_dwEvent & dwFlag) == 0) continue;	//	진행되지 않는 이벤트는 제외한다.(HTSETTINGS.TXL에 없을 경우)

		std::set<char*, HTStr>::iterator it;
		std::set<char*, HTStr>::iterator pos;
		if(m_kEvent[i].iTarget == 0)			//	계정 참조
		{
			if(pAccount==NULL) continue;
			it = m_setUser[i].find( pAccount );
			pos = m_setUserDone[i].find( pAccount );
		}
		else if(m_kEvent[i].iTarget == 1)		//	케릭터 참조
		{	
			if(pChar==NULL) continue;
			it = m_setUser[i].find( pChar );
			pos = m_setUserDone[i].find( pChar );
		}
		else
		{	
			if(pGuild==NULL) continue;
			it = m_setUser[i].find( pGuild );
			pos = m_setUserDone[i].find( pGuild );
		}

		if(m_bIsFromWeb[i] && ((dwWebEvent & dwFlag) > 0))	//	웹에서 진행되는 이벤트이며 웹에서 대상으로 인정받앗을 경우.
		{	
			if(pos != m_setUserDone[i].end()) continue;		//	이미 이벤트를 진행한 플레이어일 경우
			dwEventID |= dwFlag;
		}

		if(!m_bIsFromWeb[i] && (it != m_setUser[i].end()))	//	서버진행 이벤트이며 데이터 파일에서 인증된 이벤트 대상일 경우.
			dwEventID |= dwFlag;
	}

	return dwEventID;
}

BOOL CGameEvent::IsServerEventMember(char* pTarger, DWORD dwEvent)
{
	if(pTarger==NULL) return FALSE;
	if(dwEvent>7) return FALSE;

	std::set<char*, HTStr>::iterator it;
	std::set<char*, HTStr>::iterator pos;

	it = m_setUser[dwEvent].find( pTarger );
	if( it == m_setUser[dwEvent].end() ) return FALSE;	//	해당 이벤트 대상이 아닌경우

	return TRUE;
}
