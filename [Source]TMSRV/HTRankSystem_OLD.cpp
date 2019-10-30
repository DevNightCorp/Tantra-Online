#include "htranksystem_old.h"
#include "Server.h"
#include "GetFunc.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern CMob                   pMob     [MAX_MOB];  // �߸���������.

CHTRankSystemOld::CHTRankSystemOld(void)
{
	ZeroMemory(&m_stBramanFiletime, sizeof(m_stBramanFiletime));	//	�������� ��󸸷�ŷ���������� �ʱ�ȭ�Ѵ�.(�ʱ⿡ ������ �а��Ѵ�)
	ZeroMemory(szBramanRanker, eTNClan_Siva*250*SZNAME_LENGTH);					//	��󸸷�Ŀ�� �ʱ�ȭ�Ѵ�.
}

CHTRankSystemOld::~CHTRankSystemOld(void)
{
}

//	Ranking ������ �����´�.
void CHTRankSystemOld::ReadRankFile(int nWorld)
{
	//	��󸸷�ŷ�� �����´�.
	ReadBramanRank(nWorld);
}

void CHTRankSystemOld::ReadBramanRank(int nWorld)
{
	HANDLE		hRankFile					= NULL;     // handle to file
	FILETIME	filetimeCreationTime;;					// creation time
	FILETIME	filetimeLastAccessTime;;				// last access time
	FILETIME	filetimeLastWriteTime;;					// last write time
	char		pFile[32]					= {0,};

	sprintf(pFile, RANKFILE, nWorld);

	hRankFile = CreateFile(pFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	if (hRankFile == INVALID_HANDLE_VALUE) return;

	BOOL bRet = GetFileTime(hRankFile, &filetimeCreationTime, &filetimeLastAccessTime, &filetimeLastWriteTime);
	CloseHandle(hRankFile); 	

	//	�ֽŵ����Ͱ� �ƴϸ� ����
	if(CompareFileTime(&m_stBramanFiletime, &filetimeLastWriteTime)>0) return;

	FILE *fp = fopen(pFile, "rt");
	if ( fp != NULL )
	{
		ZeroMemory(szBramanRanker, eTNClan_Siva*250*SZNAME_LENGTH);

		char str[256] = {0,};
		char pName[SZNAME_LENGTH] = {0,};
		int nRank = 0;
		int nTrimuriti = 0;

		while(1)
		{
			char * ret = fgets((char*)str,255,fp);
			if (ret==NULL) break;

			pName[0] = 0;
			sscanf(str,"%d %d %s",&nTrimuriti, &nRank, pName);
			if (nTrimuriti>eTNClan_Siva || nTrimuriti<0 || nRank>250) break;

			strcpy(szBramanRanker[nTrimuriti-1][nRank-1], pName);
		}
	}
		
	m_stBramanFiletime = filetimeLastWriteTime;
}
int CHTRankSystemOld::GetBramanRank(int conn)
{
	int nTrimuriti = pMob[conn].MOB.byTrimuriti-1;
	if(nTrimuriti<0 || nTrimuriti>eTNClan_Siva) return 0;

	for(int i=0; i<250; i++) { if(_mbscmp((unsigned char*)pMob[conn].MOB.szName, (unsigned char*)szBramanRanker[nTrimuriti][i])==0) return i+1; }
	
	return 0;
}

int	CHTRankSystemOld::GetBramanRank(char* pChar)
{
	int conn = GetMOBID(pChar);
	if(conn<=0 || conn>MAX_USER) return 0;
	
	int nTrimuriti = pMob[conn].MOB.byTrimuriti-1;
	for(int i=0; i<250; i++) { if(_mbscmp((unsigned char*)pChar, (unsigned char*)szBramanRanker[nTrimuriti][i])==0) return i+1; }
	
	return 0;
}