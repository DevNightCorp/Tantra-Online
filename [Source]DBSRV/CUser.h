#ifndef _CUSER_
#define _CUSER_
#include <windows.h>
#include "CPSock.h"





#define USER_EMPTY    0   // 비어있다.
#define USER_ACCEPT   1   // ACCEPT 직후상태


class CUser
{
   public:
	 unsigned int    IP;
	 int    Mode;
     CPSock cSock;
	 int    Count;
	 int    Level;
	 int    Encode1;
	 int    Encode2;
	 char   Name[ACCOUNTNAME_LENGTH];
	 int    DisableID;
// Functions
   public:
   	 CUser();
	 ~CUser();
	 BOOL   AcceptUser(int ListenSocket,int WSA);
     void   Remove(void);
};


#endif