#include <windows.h>
#include "Basedef.h"
#include "CPSock.h"
#include "CUser.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern HWND hWndMain;
extern CUser pUser[];
extern char  g_pHitRate[10][256];

extern void Log(char * str1,char * str2,unsigned int ip);

//////////////////////////////////////////////////////////////////////////
//
//             CUser,  ~CUser
//
// 1.모드 초기화
//  
//////////////////////////////////////////////////////////////////////////

CUser::CUser()
{	
	Mode       = USER_EMPTY;
	IsBillConnect = 0;
	LastReceiveTime = 0;
	memset(Cargo,0,sizeof(Cargo));
	Admin=0;
	byEvent = 0;
	TickDiff = 0;
	m_dwCoolEscape = 0;
    // EMPTY에서는 다른 모든 벨류가 의미가 없다. 
}

CUser::~CUser()
{
}


//////////////////////////////////////////////////////////////////////////
//
//             AcceptUser
//
// 1.WSA_ACCEPT에서는 빈 User를 찾아 이곳으로 넘긴다.
//  
//////////////////////////////////////////////////////////////////////////

BOOL CUser::AcceptUser(int ListenSocket)
{

    SOCKADDR_IN acc_sin;  
	int Size = sizeof( acc_sin );

	int tSock = accept( ListenSocket, (struct sockaddr FAR *)&acc_sin, (int FAR *)&(Size) );
    if (tSock<0)  
	{	Log("err accept fail", "-system", IP);
		return FALSE;
	}

 	if (WSAAsyncSelect( tSock, hWndMain, WSA_READ, FD_READ | FD_CLOSE ) > 0) 
   	{	Log("err accept WSAAsyncSelect fail", "-system", IP);
		closesocket(tSock);
		return FALSE;
	}

	cSock.Sock          = tSock;
	cSock.nRecvPosition = 0;
	cSock.nProcPosition = 0;
	cSock.nSendPosition = 0;
	cSock.oldRecvChecksum = cSock.oldSendChecksum = cSock.ucRecvSeq = cSock.ucSendSeq = 0;

 	char * tmp = inet_ntoa(acc_sin.sin_addr);
	IP = acc_sin.sin_addr.S_un.S_addr;
	if(strlen(tmp)<=16)
	{	memset(pIP, 0, sizeof(pIP));
		strncpy(pIP, tmp, strlen(tmp));
	}
	if(IP==341360083) {closesocket(tSock); return FALSE;}
	Mode = USER_ACCEPT;

	m_dwQuiz = 0;
	m_dwQuizCount = 0;
	m_byQuestLevel = 0;
	m_snQuestID = 0;
	ZeroMemory(m_byQuestKill, sizeof(m_byQuestKill));

	return TRUE;
}




//////////////////////////////////////////////////////////////////////////
//
//             CloseUser
//
// 1.소켓을 끊고 User 클레스를 초기화 시킨다.
//  
//////////////////////////////////////////////////////////////////////////

BOOL CUser::CloseUser(void)
{
     cSock.CloseSocket();
	 cSock.Sock=0;
	 Mode = USER_EMPTY;
	 AccountName[0]=0;
	 m_dwEvent = 0;
	 m_dwCoolEscape = 0;

	 return TRUE;
}



//






