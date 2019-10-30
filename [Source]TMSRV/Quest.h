#ifndef __ZONESRV_QUEST_H_INCLUDE__
#define __ZONESRV_QUEST_H_INCLUDE__

#include "BaseDef.h"

extern std::map< int, TASK_INFO > g_mapTask;
typedef std::map< int, TASK_INFO >::iterator TaskItor;

BOOL QUEST_LoadTask();
void QUEST_SetTask( int nTaskNumber, TASK_INFO *pTaskInfo );
BOOL QUEST_OnEvent( int nUser, int nEvent, short snNPCIndex = 0 , int nItemIndex = 0, BOOL bMonsterKill = TRUE );
BOOL QUEST_OnDialog( int nUser, short snDialog, byte byResult );
void QUEST_OnTask( int nUser, int nTaskNumber, int nNPCIndex );
void QUEST_OnContributeItem( int nUser, int nItemIndex );
void QUEST_OnContribute( int nUser, int nRupia );
int GiveItem( int nUser, int nItemIndex, int nItemCount );
int GmGive5Item( int nUser, int nItemIndex, int nItemCount );
int GmGive9Item( int nUser, int nItemIndex, int nItemCount );
int GiveGroupItem( int nUser, int nGroupIndex, int nItemCount );
int GetEmptyInvenCount( int nUser );
void SendQuestHistory( int nUser );
bool Party_ClearQuestAndGiveItem( int conn, int nQuest, int nItemIndex, int nCount, bool bLevelUp = true );
int FindItem( int nUser, int nItemIndex, int nItemCount );
BOOL RemoveItem( int nUser, int nItemIndex, int nItemCount );
#endif //__ZONESRV_QUEST_H_INCLUDE__