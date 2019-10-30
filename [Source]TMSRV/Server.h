#ifndef __ZONESRV_SERVER_H_INCLUDE__
#define __ZONESRV_SERVER_H_INCLUDE__

#include "BaseDef.h"
#include "CMob.h"
#include "CUser.h"
#include "CGuild.h"
#include "TNDeck1000.h"


//BOOL InitApplication(HANDLE);
//BOOL InitInstance(HANDLE, int);
//LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
void	CloseServer();

//CMob,CUser
BOOL  ReadMob              (STRUCT_MOB * mob,char * Directory);  // MOB읽기는, NPC읽기와 User정보 읽기가 공유한다.
int   GetUserFromSocket    (int Sock);                           // ]시 사용자의 User index를 리턴한다. 
int   GetEmptyUser         (void);                               // WSA_ACCEPT시 빈 User의 index를 리턴한다.
int   GetEmptyItem         (void);
int   GetEmptyNPCMob       (void);
void  RebuildGenerator	   (void);

void	ProcessClientMessage (int conn,char*msg);
void	ProcessDBMessage     (char*msg);
void	ProcessMSGMessage     (char*msg);
void	ProcessItemMessage     (char*msg);

void  ProcessYutTimer		(void);
void  ProcessSecTimer      (void);
void  ProcessHourTimer     (void);
void  Reboot               (void);
void  ProcessDecayItem     (void);
void  ProcessImple(int conn,int level,char * str);

void ProcessMonster();
void ProcessRobot();
void DumpMobile( int a_iHandle );
void LoadDump( char* a_pFileName );



CMob*	GetMobFromIndex      (unsigned int index);
int		GetCreateMob         (int conn,MSG_CreateMob * sm);
void	SetMob               (int mob);
void	CharLogOut           (int conn);
void	DeleteMob            (int mob,int a_iReason, int a_iKiller, byte a_byProductionType/*=eTNPrdt_RemoveNormal*/, int a_iCaller ) ;
//void	SetBattle            (int mob,int enemy);
void	MobKilled            (int mob,int killer,int tx,int ty);


// 디버그, 로그 관련 펑션 
void StartLog             ( void );
void Log                  ( char * String1, char * String2 ,unsigned int ip);
void EventLog(char * strLog,char * strAccount,char* strCharName, unsigned int ip);
void CrackLog             (int conn,char * str);
void CloseUser            (int conn);
void RemoveParty          (int conn, int Target);
void RemoveTrade          (int target, int nError);
void RemoveAlliance			(int target, int error);
BOOL SetAffect(int mob, int skillnum, int Delay,int Level);
BOOL SetTick(int mob, int skillnum, int Delay,int Level);
int CreateMob(char * name,int xfix,int yfix,char *folder);


int  CreateItem(int& x, int& y, STRUCT_ITEM *sour, int nWho = 0, DWORD dwMoney = 0, int a_iParty = 0 , unsigned int a_uiReleaseTime = 0 );
BOOL UpdateItem(int item,int State,int * height);
BOOL IsImple(int user);
int  ProcessAffect(int conn);
void DoRecall(int mob);
//void DoTeleport(int mob,int x,int y);
void DoRemoveHide(int conn);
void DoSummon(int target,int x, int y);
void DoDeprivate(int conn,int target);
void DoWar (int myguild,int target);
void Combine(int conn,int sour,int dest);
BOOL CombineTreasureMap(int conn);
void ProcessBILLMessage( char*msg );
BOOL AddCrackError(int conn,int val,int Type) ;

void GuildProcess(void);
int  GetUserByName       (char *name);
void  SaveUser(int conn,int export);
void ClearArea(int x1,int y1,int x2,int y2);
void ClearAreaLevel(int x1,int y1,int x2,int y2,int lv1,int lv2);
int ApplyHp(int conn);
int ApplyMp(int conn);
void SetReqHp(int conn);
void SetReqMp(int conn);

void MoveKalaRewarder() ;
void CheckKalaSystem() ;

void PopMonstersForEvent() ;
void ExecuteEmergence() ;


void LoadWorldSettings() ;
void LoadZoneSettings() ;
void LoadSpeechComment() ;
void LoadEventTask() ;
void ParseData( char* a_pLine ) ;
//void LoadSettings() ;
void LoadMonsterData() ;
void LoadSkillData() ;
void LoadItemData() ;
void LoadSettingTxl() ;
int LoadStrongholdData() ;
int SaveStrongholdData() ;
int LoadRouteData();
void RefreshClan( int a_iStronghold, int a_iClan, int a_iClear=0 ) ;
void ChangeClan( int a_iWho, int a_iClan ) ;
void UpdateStrongHold(int nStronghold, int nGuild, int a_iIntruder );
void LogRewardItems() ;
int SummonKala( int a_iTribe, int a_iClan, int x, int y, int& a_iHandle ) ;
void VerifyKalaOnAltar() ;
void LogKalaSystemInfo() ;
void RegisterMonstersToArea() ;
//bool IsInRvR() ;
void PrintMapInfo() ;
void ChangeRwdCorrect( int a_iType, int a_iPrana, int a_iGold, int a_iBraman=100, int a_iItem=100 ) ;
void HelpGameMaster( int a_iHandle, char* a_pCmd, bool a_bCheckGM=true ) ;
void ExecuteGMCommand2nd( int a_iHandle, char* a_pCmd, bool a_bCheckGM=true );
void HelpUserFunc( int a_iHandle, char* a_pCmd );
void ControlSystem( int a_iHandle, char* a_pCmd, bool a_bCheckGM=true ) ;
void AssistPlayMovie( int a_iHandle, char* a_pCmd ) ;
int Teleport( int a_iMob, int a_iX, int a_iY ) ;
int PlayDice( int a_iMin, int a_iMax ) ;
int TriggerEvent( int a_iUser, int a_iEventID, int a_iX, int a_iY, int a_iNPC, int a_iCaller=0 ) ;
void SharePrana( int a_iParty, int a_iPrana, int a_iCorpse, bool a_bApplyCorrect ) ;
void ShareBramanPoint( int a_iParty, int a_iBP, int a_iCorpse ) ;
void RecordRvRStatus() ;
void NotifyRvRStatus() ;
void RemoveKalaCoreInInventory( int a_iUser ) ;
void KillMonster( int a_iHandle ) ;
void ReturnPCToSaveZone( int a_iPC ) ;
int PostMessageToZone( char* a_pMsg, int a_iTextColor=15, int a_iBGColor=14, int a_iMessage = 0 ) ;
int PostMessageToWorld( char* a_pMsg, int a_iTextColor=15, int a_iBGColor=14, int a_iMessage = 0 ) ;
//int Percent( double a_dValue, double a_dPercent ) ;
int CountMonster( int a_iTribe ) ;
void SetLogFileName();


short GetSkillDataIndex( short a_sID, byte a_byLevel ) ;
short GetItemDataIndex( short a_sID ) ;
int GetEmptyInven(int conn);
int GetEmptyCargo(int conn);

int RefiningItem(int nID, STRUCT_ITEM* pSour, STRUCT_ITEM** pDest);

//	Server List, Portal List 관련
PORTALINFO* GetPortal(WORD WPortalID);

//	Trade
void ExchangeTrade(int nSource, int nTarget);
void DBUpdateGuildMember(int conn);

//	Challenge
void RemoveChallenge(int conn, BYTE byReason = eChallenge_System);
void StartChallenge(int conn);

//	Gamble - Yut
void HT_PlayYut();

//	Event
BYTE SetGameEvent(int iHandle, DWORD dwGameEventID, int* piParam);

void SendCastleData(int iHandle);

//	GuildCargo
void SetGuildCargo(int iGuildID, int iCargoIndex, STRUCT_ITEM* pData);

//	Refining
bool bRefiningCheckPart(short snSour, short snDest);

//	item-server
void DeleteBlockItem(int conn);
bool IsBlockedItem(int conn, BYTE byIndex);


// extern

extern HWND                   hWndMain;
extern CMob						pMob     [MAX_MOB];
extern CUser					pUser    [MAX_USER];
extern CItem					pItem    [MAX_ITEM];
extern CGuild					pGuild[MAX_USER];
extern TNITEM_DATA				pItemData[MAX_ITEM_DATA];
extern TNSKILL_DATA				pSkillData[MAX_SKILL_DATA];	
extern STRUCT_MOB				pMonsterData[MAX_MONSTER_DATA] ;
extern unsigned short			pMobGrid   [MAX_GRIDY][MAX_GRIDX];
extern unsigned short			pItemGrid  [MAX_GRIDY][MAX_GRIDX];
extern TNSETITEM				g_krgSetItem[eSetItem_Size];
extern int						g_iZoneID;
extern SYSTEMTIME g_kSystemTime ;
extern char g_szrgLogFileName[eLogFile_Size][64];
extern TNRoute					g_krgRoute[eSiz_Route];
extern int						g_iSymbolAtByruCastle;
//extern TNDeck1000				g_kMonsterScroll;
//extern int g_irgMonsterToBeSummon[eMon_CountOfMonsterToBeSummon];

#endif //__ZONESRV_SERVER_H_INCLUDE__

