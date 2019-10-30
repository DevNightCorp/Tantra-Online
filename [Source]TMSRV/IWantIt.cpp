#include "basedef.h"
#include "iwantit.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

CIWantIt::CIWantIt(void)
{
	m_nIndex = 0;
	ZeroMemory(m_pJoinUser, sizeof(m_pJoinUser));
}

CIWantIt::~CIWantIt(void)
{
}

void CIWantIt::Initialize()
{
	m_nIndex = 0;
	ZeroMemory(m_pJoinUser, sizeof(m_pJoinUser));

	FILE *fp = fopen("Data\\IWantIt.txt","rt");
	if ( fp != NULL )			//	data file 존재시 맵에 삽입한다.
	{
		char str[256] = {0,};
		int nCount = 0;

		while(1)
		{
			char * ret = fgets((char*)str,255,fp);
			if (ret==NULL) break;

			nCount=0;
			sscanf(str,"%s %d",m_pJoinUser[m_nIndex],&nCount);
			m_mapTable.insert( std::map<char*,int,HTStr>::value_type( m_pJoinUser[m_nIndex], nCount ) );
			++m_nIndex;
		}
		fclose(fp);
	}

	fp = fopen("Data\\IWantItRank.txt","rt");
	if ( fp != NULL )			//	data file 존재시 맵에 삽입한다.
	{
		char str[256] = {0,};
		int nCount = 0;
		int nIndex = 0;
		for(int i=0; i<20; i++)
		{
			char * ret = fgets((char*)str,255,fp);
			if (ret==NULL) break;

			nCount=0;
			sscanf(str,"%s %d",m_pCharName[i], &m_arrsnValue[i]);
		}
		fclose(fp);
	}
}

int CIWantIt::GetUserItemCount(char* pChar)
{
	std::map<char*,int,HTStr>::iterator it = m_mapTable.find( pChar );
	if ( it != m_mapTable.end() ) return it->second;

	return 0;
}

void CIWantIt::IncreaseUserItemCount(char* pChar)
{	
	std::map<char*,int,HTStr>::iterator it = m_mapTable.find( pChar );
	if ( it != m_mapTable.end() )
	{	
		(it->second)++;		//	기존 데이터가 있을 경우
		if(it->second > m_arrsnValue[19]) InsertRank(pChar, it->second);
	}
	else					//	기존 데이터가 없을 경우
	{	strncpy(m_pJoinUser[m_nIndex], pChar, SZNAME_LENGTH);
		m_mapTable.insert( std::map<char*,int,HTStr>::value_type( m_pJoinUser[m_nIndex], 1 ) );
		if(m_arrsnValue[19]<1) InsertRank(pChar, 1);
		++m_nIndex;
	}
}

void CIWantIt::GetRankUser(char *pData)	//	20명까지 포상하기로 한다.
{
	char pChar[128] = {0,0,0,};
	sprintf(pData, "[아이원잇 랭킹] >>");
	for(int i=0; i<20; i++)
	{
		sprintf(pChar, "Rank%d char:%s Count:%d >> ", i, m_pCharName[i], m_arrsnValue[i]);
		strcat(pData, pChar);
	}
}

void CIWantIt::InsertRank(char* pChar, int nCount)
{
	int nMyPos = 18;
	for(int i=19; i>=0; i--)
	{
		if(strncmp(m_pCharName[i], pChar, SZNAME_LENGTH)==0) nMyPos = i;
		if(nCount>m_arrsnValue[i]) continue;
		break;
	}

	for(int j=nMyPos; j>i+1; j--)
	{
		m_arrsnValue[j] = m_arrsnValue[j-1];
		strncpy(m_pCharName[j], m_pCharName[j-1], SZNAME_LENGTH);
	}

	m_arrsnValue[i+1] = nCount;
	strncpy(m_pCharName[i+1], pChar, SZNAME_LENGTH);
}

void CIWantIt::CloseEvent()
{
	char* pChar = NULL;
	FILE *fp = fopen("Data\\IWantIt.txt","wt");
	if ( fp != NULL )			//	data file 존재시 맵에 삽입한다.
	{
		std::map<char*,int,HTStr>::iterator it;
		for(it=m_mapTable.begin(); it!=m_mapTable.end(); ++it)
		{
			pChar = it->first;
			fprintf(fp, "%s %d \n", it->first, it->second);
		}
		fclose(fp);
	}
	fp = fopen("Data\\IWantItRank.txt","wt");
	if ( fp != NULL )			//	data file 존재시 맵에 삽입한다.
	{
		for(int i=0; i<20; i++)
		{
			fprintf(fp, "%s %d \n", m_pCharName[i], m_arrsnValue[i]);
		}
		fclose(fp);
	}
}

