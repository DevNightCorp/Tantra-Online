#include "./basedef.h"
#include "./CPSock.h"
void ProcessBILLMessage( char*msg );
int	SendBilling(int conn,char * AccountName,int type,int NewSession);
int SendBilling2(_AUTH_GAME *m,int type);