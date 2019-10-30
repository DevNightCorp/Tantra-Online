//	.\\Data\\Event1.bin ~ .\\Data\\Event8.bin ���� �̺�Ʈ ��� ������ �����Ҽ� �ִ�.
//	�� �ش� ������ ����� Event1 ~ Event8���� ���డ���ϴ�.
//	���� HTSETTINGS.TXL���Ͽ� �̺�Ʈ�� ����� �Ǿ� �ִµ� �ش������� ���� ��쿡�� 
//	����� ������ Ŭ���̾�Ʈ�� ���� ������ �ִ� ������ �Ѵ�.


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
		if(m_kEvent[i].iEventID == 0) continue;				//	hssetting.txl�� ��ϵ��� ���� ���
		
		DWORD dwZone = 0x00000001 << iZone;
		if((dwZone & m_kEvent[i].iZone) == 0) continue;		//	����� �Ǿ����� �̺�Ʈ ��� ���� �ƴѰ��

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
		if(iTarget==0)					//	���� ����
			pUser = new char[ACCOUNTNAME_LENGTH];
		else if(iTarget==1) 			//	�ɸ��� ����
			pUser = new char[SZNAME_LENGTH];
		else							//	��� ����
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
			if ( it != m_setUser[dwEvent].end() )	//	�������� �޾ư����� ������ ����Ʈ���� �Ⱥ��� ���(������ ����������)
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
	if(m_bIsFromWeb[dwIndex])	//	m_setUser�� ������� �ʴ´�.
	{
		if(m_kEvent[dwIndex].iTarget==0)									//	���� ����
		{
			pData = new char[ACCOUNTNAME_LENGTH];
			strncpy(pData, pUser, ACCOUNTNAME_LENGTH);
		}
		else if(m_kEvent[dwIndex].iTarget==1)								//	�ɸ��� ����
		{
			pData = new char[SZNAME_LENGTH];
			strncpy(pData, pUser, SZNAME_LENGTH);
		}
		else																//	��� ����
		{
			pData = new char[SZGUILD_LENGTH];
			strncpy(pData, pUser, SZGUILD_LENGTH);
		}

		m_setUserDone[dwIndex].insert(std::set<char*, HTStr>::value_type(pData));
	}
	else						//	m_setUser�� ����Ѵ�.
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
	FILE *fp = fopen(szFile, "at");			//	������ ���������Ḧ ����Ͽ� ������ ����ڵ� ����Ʈ�� ������ �����Ѵ�.
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
		if(iTarget==0)				//	���� ����
			pUser = new char[ACCOUNTNAME_LENGTH];
		else if(iTarget==1)			//	�ɸ��� ����
			pUser = new char[SZNAME_LENGTH];
		else						//	��� ����
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
		if((m_dwEvent & dwFlag) == 0) continue;	//	������� �ʴ� �̺�Ʈ�� �����Ѵ�.(HTSETTINGS.TXL�� ���� ���)

		std::set<char*, HTStr>::iterator it;
		std::set<char*, HTStr>::iterator pos;
		if(m_kEvent[i].iTarget == 0)			//	���� ����
		{
			if(pAccount==NULL) continue;
			it = m_setUser[i].find( pAccount );
			pos = m_setUserDone[i].find( pAccount );
		}
		else if(m_kEvent[i].iTarget == 1)		//	�ɸ��� ����
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

		if(m_bIsFromWeb[i] && ((dwWebEvent & dwFlag) > 0))	//	������ ����Ǵ� �̺�Ʈ�̸� ������ ������� �����޾��� ���.
		{	
			if(pos != m_setUserDone[i].end()) continue;		//	�̹� �̺�Ʈ�� ������ �÷��̾��� ���
			dwEventID |= dwFlag;
		}

		if(!m_bIsFromWeb[i] && (it != m_setUser[i].end()))	//	�������� �̺�Ʈ�̸� ������ ���Ͽ��� ������ �̺�Ʈ ����� ���.
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
	if( it == m_setUser[dwEvent].end() ) return FALSE;	//	�ش� �̺�Ʈ ����� �ƴѰ��

	return TRUE;
}
