#ifndef __SENDFUNC__
#define __SENDFUNC__

#include <windows.h>
#include "basedef.h"

void SendClientMessage		(int conn,  char * msg                                    );
void SendClientResult		(int conn,	 WORD wType, BYTE byResult);
void SendClientSignal		(int conn,  int     id,          WORD signal              );

void SendCreateMob			(int dest,  int sour, BOOL bSend);
void SendRemoveMob			(int dest,  int sour, int Type,BOOL bSend               );
void SendCreateItem			(int conn,  int item, BOOL bSend               );
void SendRemoveItem			(int dest, int nID, int bSend);
void GridMulticast		    (int  mob,	int tx  ,	int  ty,	MSG_STANDARD * msg,	int max=100, BYTE byType=0);	//	type(0:이동, 1:워프)
void GridMulticast			(int  tx,	int ty  ,	MSG_STANDARD * msg,	int skip, int max=100);
//void GridMulticast			(int mob,	int tx,		int ty,		MSG_STANDARD * msg/*, int Priority = 100*/);

void SendAddParty			(int target,int whom,int leader);
void SendReqParty			(int target,int leader);
void SendRemoveParty		(int target, int whom);
void SendUpdateParty		(int Source);
void SendPartyMessage		(int nPartyIndex, MSG_STANDARD* msg);
void SendGridMob        	(int conn);
void SendNotice         	(char * msg);
void SendToAll				(MSG_STANDARD * msg);
void SendTrimuriti			(BYTE byTrimuriti, MSG_STANDARD * msg);
void SendHpMode         	(int conn);
void SendGuildList      	(int conn);
void SendGuildMessage		(int nGuildIndex, MSG_STANDARD* pMsg);
void SendGuildChat			(int conn,int gid,char * str,unsigned char bg,unsigned char text);
void SendGuildInfo			(int conn,int nGuildIndex);
void SendItemDisappear  	(int tx, int ty, int nID, int nMOBID);
void SendStrongHoldData		(int conn);
void SendWhoMessage			(int conn);
bool RecvWhoMessage			(int conn, char* pWho);
void SendQuiz				(int conn, int nQuiz = 0);
void BroadCastTrimuritiSelection	(int conn);
void SendTrimuritiCount		(int conn);
void SendYutBroadcast		(short snX, short snY, int iNPC, int iMsg);
void SendScriptQuestHistory (int conn, int nNPC);
#endif
