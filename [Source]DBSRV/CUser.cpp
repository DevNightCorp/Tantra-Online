#include <windows.h>
#include "Basedef.h"
#include "CPSock.h"
#include "CUser.h"


#include "CUser.h"


extern HWND hWndMain;





//////////////////////////////////////////////////////////////////////////
//
//             CUser,  ~CUser
//
// 1.��� �ʱ�ȭ
//  
//////////////////////////////////////////////////////////////////////////

CUser::CUser()
{	
	Mode = USER_EMPTY;
	IP   = 0;
	Count = 0;
	DisableID = 0;
	Level = -1;
    // EMPTY������ �ٸ� ��� ������ �ǹ̰� ����. 
}

CUser::~CUser()
{
}


//////////////////////////////////////////////////////////////////////////
//
//             AcceptUser
//
// 1.WSA_ACCEPT������ �� User�� ã�� �̰����� �ѱ��.
//  
//////////////////////////////////////////////////////////////////////////

BOOL CUser::AcceptUser(int ListenSocket,int wsa)
{

	
     SOCKADDR_IN acc_sin;  
	 int Size = sizeof( acc_sin );

	 int tSock = accept( ListenSocket, (struct sockaddr FAR *)&acc_sin, (int FAR *)&(Size) );
     if (tSock<0)  
	 {  return FALSE;
	 }

 	 if (WSAAsyncSelect( tSock, hWndMain, wsa , FD_READ | FD_CLOSE ) > 0) 
   	 {  closesocket(tSock);
	    return FALSE;
	 }
 
	 cSock.Sock          = tSock;
	 cSock.nRecvPosition = 0;
	 cSock.nProcPosition = 0;
	 cSock.nSendPosition = 0;

 	 char * tmp = inet_ntoa(acc_sin.sin_addr);
	 IP		= cSock.IP	= acc_sin.sin_addr.S_un.S_addr;
	 Mode	= USER_ACCEPT;

     
	//MSG_REQUSERINFO sm; sm.Type = _MSG_REQUSERINFO;

	 return TRUE;

}

// SAVEnQUIT


