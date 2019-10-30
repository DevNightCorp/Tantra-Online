#include "htranksystem.h"
#include "Server.h"
#include "GetFunc.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern CMob                   pMob     [MAX_MOB];  // 잘못설계했음.

CHTRankSystem::CHTRankSystem(void)
{
	ZeroMemory(&m_stBramanFiletime, sizeof(m_stBramanFiletime));		//	존서버의 브라만랭킹파일파임을 초기화한다.(초기에 무조건 읽게한다)
	ZeroMemory(szBramanRanker, sizeof(szBramanRanker));					//	브라만랭커을 초기화한다.
}

CHTRankSystem::~CHTRankSystem(void)
{
}

//	Ranking 정보를 가져온다.
void CHTRankSystem::ReadRankFile(int nWorld)
{
	//	브라만랭킹을 가져온다.
	ReadBramanRank(nWorld);
}

void CHTRankSystem::ReadBramanRank(int nWorld)
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

	//	최신데이터가 아니면 리턴
	if(CompareFileTime(&m_stBramanFiletime, &filetimeLastWriteTime)>0) return;

	FILE *fp = fopen(pFile, "rt");
	if ( fp != NULL )
	{
		ZeroMemory(szBramanRanker, sizeof(szBramanRanker));

		char str[256] = {0,};
		char pName[SZNAME_LENGTH] = {0,};
		int nRank = 0;
		int nTrimuriti = 0;
		int nTribe = 0;

		while(1)
		{
			char * ret = fgets((char*)str,255,fp);
			if (ret==NULL) break;

			pName[0] = 0;
			sscanf(str,"%d %d %d %s",&nTrimuriti, &nTribe, &nRank, pName);
			if ( nTrimuriti>eTNClan_Siva || nTrimuriti<0 || nRank>MAX_RANK || nTribe<1 || nTribe>4 ) break;

			strcpy(szBramanRanker[nTrimuriti-1][nTribe-1][nRank-1], pName);
		}
	}
		
	m_stBramanFiletime = filetimeLastWriteTime;
}
int CHTRankSystem::GetBramanRank(int conn)
{
	int nTrimuriti = pMob[conn].MOB.byTrimuriti-1;
	int nTribe = 0;

	switch(pMob[conn].MOB.snTribe)
	{
	case TRIBE_NAGA:
	case TRIBE_KINNARA:
		nTribe = 1;
		break;
	case TRIBE_ASURA:
	case TRIBE_RAKSHASA:
		nTribe = 2;
		break;
	case TRIBE_YAKSA:
	case TRIBE_GANDHARVA:
		nTribe = 3;
		break;
	case TRIBE_DEVA:
	case TRIBE_GARUDA:
		nTribe = 4;
		break;
	default:
		return 0;
	}

	if(nTrimuriti<0 || nTrimuriti>eTNClan_Siva) return 0;

	for(int i=0; i<MAX_RANK; i++) { if(_mbscmp((unsigned char*)pMob[conn].MOB.szName, (unsigned char*)szBramanRanker[nTrimuriti][nTribe-1][i])==0) return i+1; }
										
	
	return 0;
}

int	CHTRankSystem::GetBramanRank(char* pChar)
{
	int conn = GetMOBID(pChar);
	if(conn<=0 || conn>MAX_USER) return 0;
	
	int nTrimuriti = pMob[conn].MOB.byTrimuriti-1;
	int nTribe = 0;

	switch(pMob[conn].MOB.snTribe)
	{
	case TRIBE_NAGA:
	case TRIBE_KINNARA:
		nTribe = 1;
		break;
	case TRIBE_ASURA:
	case TRIBE_RAKSHASA:
		nTribe = 2;
		break;
	case TRIBE_YAKSA:
	case TRIBE_GANDHARVA:
		nTribe = 3;

		break;
	case TRIBE_DEVA:
	case TRIBE_GARUDA:
		nTribe = 4;
		break;
	default:
		return 0;
	}

	if(nTrimuriti<0 || nTrimuriti>eTNClan_Siva) return 0;

	for(int i=0; i<MAX_RANK; i++) { if(_mbscmp((unsigned char*)pChar, (unsigned char*)szBramanRanker[nTrimuriti][nTribe-1][i])==0) return i+1; }
	
	return 0;
}
