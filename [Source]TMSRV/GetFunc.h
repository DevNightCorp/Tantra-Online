#ifndef __GETFUNC__
#define __GETFUNC__
#include <windows.h>
#include "BaseDef.h"



int	GetCreateMob         (int mob,  S_SCP_INIT_OTHER_MOB * sm);
int GetCreateMobTrade(int mob,MSG_CreateMobTrade * sm);

void  GetCreateItem        (int idx,  S_SCP_MAP_ITEM_APPEAR * sm);
void  GetAction            (int mob,  int targetx,int targety,MSG_Action*sm);
BOOL  GetEmptyItemGrid     (int * gridx, int * gridy);  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
void  GetAttack            (int mob,int target,MSG_AttackOne*sm);

int		IsPathCleared( int a_iFromX, int a_iFromY, int a_iToX, int a_iToY, int a_iDistance ) ;
int		CalDistance( int a_iMob1, int a_iMob2 ) ;
int		CalDistance( HS2D_COORD& a_kSrc, HS2D_COORD& a_kDest, byte a_nSrcBodyRadius, byte a_nDestBodyRadius ) ;
BOOL	GetAttackPos( int a_iMob, HS2D_COORD& a_kDest, HS2D_COORD& a_kSrc ) ;
//BOOL	GetEmptyMobGrid      (int conn, int  * gridx, int * gridy, int a_iSkip=0, int a_iRadius=5 );  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
BOOL	GetEmptyMobGrid      (int conn, int  * gridx, int * gridy, int a_iAdditionalBlockedCellPrty=0 );  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
bool	CheckGrid			(int x, int y, int iBlocked);
BOOL	GetMovableMobGrid	(int mob, int * tx, int * ty ); 
BOOL PickFreeMobGrid( int mob, int* tx, int* ty, int a_iAdditionalBlockedCellPrty=0 );  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
void	GetAffect            (unsigned short *out, STRUCT_AFFECT * affect);
int		GetEmptyAffect       (int mob,int type);  // return value -1 is full.
unsigned char     GetAttribute(int x,int y);
//void	GetGuild(int conn);  // Item으로 길드와 길드 레벨 세팅.
void	GetTeleportPosition(int * x, int * y);
//int		GetGuild(STRUCT_ITEM* item);
BOOL	GetHide(int mob);
int		GetExpApply(int exp, int attacker, int target);
int		GetParryRate(STRUCT_MOB * mob,int add);
BOOL	GetInView(int a,int b);
BOOL	GetInHalf(int a,int b);

int		GetCurKill		(int conn);
void	SetCurKill		(int conn,int value);
int		GetTotKill		(int conn);
void	SetTotKill		(int conn,int value);
int		GetPKPoint		(int conn);
void	SetPKPoint		(int conn,int value);
int		GetGuilty		(int conn);
void	SetGuilty		(int conn,int value);
int		GetMatchCombine	(STRUCT_ITEM *item);
int		GetMOBID		(char* pszName);
int		GetMOBIDFromID	(char* pszAccount);
STRUCT_ITEM* 	GetItem	(int conn, BYTE byPlace, BYTE byIndex);
BOOL	GetTrimurityArea(int conn, int &nX, int &nZ);
BOOL	GetArenaArea	(int conn, int &nX, int &nZ);
int		GetRandom		(int nStart, int nEnd);
int		GetItemCount	(int conn, short snItemIndex);
byte	GetScriptQuestLevel	(int conn, short snQuestID);
#endif

