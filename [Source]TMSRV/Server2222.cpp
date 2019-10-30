#define _WIN32_WINNT 0x500 // for use "TryEnterCriticalSection"

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <string.h>        
#include <time.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>
//#include <atltime.h>
#include "resource.h"

#include "basedef.h"
#include "Server.h"
#include "CPSock.h"
#include "Language.h"

#include "CUser.h"
#include "CMob.h"
#include "CItem.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "HTParamMgr.h"
#include "TNKalaSystem.h"
#include "TNSiege.h"

#include "CNPCGene.h"
#include "CGuild.h"
#include "TNRate.h"
#include "TNRate10000.h"
#include "TNDeck10000.h"
#include "TNDeck1000.h"
#include "TNDeck100.h"
#include "TNDeck.h"
#include "TNInfluenceMap.h"
#include "TNScheduler.h"
#include "TNArena.h"
#include "Quest.h"
#include "TNMagicLamp.h"
#include "HTNew_On.h"
#include "TFPercentMixer.h"
#include "CrackType.h"
#include "DrawInfo.h"
#include "HTRankSystem.h"
#include "GameEvent.h"
#include "Yut.h"
#include "RentalStore.h"
#include <vector>
#include "MD5Checksum.h"
	
#pragma warning(disable:4786)

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#define __YUT_LOG__

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

int	SendBilling(int conn,char * AccountName,int type,int NewSession);
int	SendBilling2(_AUTH_GAME *m,int type);
int SendBilling3(int conn, _AUTH_GAME2 *m,int type);

// 이벤트 관련 코드 ////////////////////////////////////////////////////////
int evStartIndex   =  0;  // 드롭시작번호
int evEndIndex     =  0;  // 드롭끝번호
int evCurrentIndex =  0;  // 현재 드롭된 번호
int evRate         =  0;  // 떨어질확률 1000이면 1/1000
int evItem         =  0;  // 이벤트 아이템은 코드
int evIndex        =  0;  // 아이템에 유닉코드가 붙는가.
int evOn           =  0;  // 아이템이 떨어지고 있는가 1이면 떨어지고 있음.
int evDelete       =  0;  // 1 이벤트 아이템 삭제중  // 0 삭제안함
int evNotice	   =  1;  // 이벤트에 공지가 뜨는지		 
int DUNGEONEVENT	= 1;
int StatSapphire    = 30;
int NewbieEventServer=0;
int NumServerInGroup=1;
//////////////////////////////////////////////////////////////////////////// MS-StarForce 822
//
extern STRUCT_ITEMLIST   g_pItemList[MAX_ITEMLIST];
extern STRUCT_INITITEM   g_pInitItem[MAX_INITITEM];
extern int               g_dwInitItem;
extern int               g_pDropRate[64];
extern int               g_pDropBonus[64];
extern unsigned	short	 g_pServerListPort[MAX_SERVERGROUP][MAX_SERVERNUMBER];
extern TNInfluenceMap    g_kInfluenceMap; 
extern int               g_iMonsterLevelForWritingLog;
extern TNCELL              g_krgCell[MAX_GRIDY][MAX_GRIDX];
char  FailAccount[16][ACCOUNTNAME_LENGTH];
E_COUNTRY_ID		   g_eCountryID = eCountryKorea;

HWND                   hWndMain;
HMENU                  hMainMenu;
unsigned int           CurrentTime  = 0;
unsigned int		   LastSendTime = 0;
int                    DropCount = 0; // 이벤트로 특정 갯수를 드롭시킬때 사용.
int						ValidUser = 1000;
CMob					pMob     [MAX_MOB];
CUser					pUser    [MAX_USER];
CUser					TempUser;
CItem					pItem    [MAX_ITEM];
CGuild					pGuild[MAX_USER];
TNITEM_DATA				pItemData[MAX_ITEM_DATA];
TNSKILL_DATA			pSkillData[MAX_SKILL_DATA];
STRUCT_MOB				pMonsterData[MAX_MONSTER_DATA];
unsigned short         pMobGrid   [MAX_GRIDY][MAX_GRIDX];
unsigned short         pItemGrid  [MAX_GRIDY][MAX_GRIDX];
SYSTEMTIME g_kSystemTime;
//GetLocalTime( &g_kSystemTime );

char g_szrgLogFileName[eLogFile_Size][64];

extern int              g_iHostileTable[MAX_CLAN][MAX_CLAN];
extern int						g_irgLevelUp[TN_MAX_LEVEL];
extern TNRate10000					g_krgRewardItemRate[MAX_MONSTER_DATA][eRwd_ItemCount];
extern TNCOEFFICIENT           g_krgCoefficientByClass[eCls_MaxLevel][eCls_MaxSpecialized];
extern short                   g_srgItemGroup[eRwd_ItemGroup][eRwd_ItemGroupCount];
extern short					g_srgGroupItemCount[eRwd_ItemGroup];
extern TNEFFECTTOLERANCE		g_krgEffectTolerance[eCls_MaxLevel][eCls_MaxSpecialized];
extern STRUCT_ITEM             g_krgItemByLevel[eItm_MaxCategory][eItm_MaxLevel];
extern TNDeck10000             g_krgItemRateByMonLevel[eMonster_MaxLevel]; // card : 1~11
extern TNDeck1000              g_kRateByItemCategory; // card : 0 ~n
extern short                   g_srgRateByItemLevel[eMonster_MaxLevel][eItm_MaxLevel];
extern short                   g_srgRateByItemCategory[eItm_MaxCategory];
int							   g_pRvRZoneList[eRvRZone_Count] = { 10, 11, 13, 14, 15, 0, 0, 0, 0, 0 };
extern TNCONSIDER              g_krgConsider[eCon_Sort][eCon_Sort];
extern TNJUDGE_COMBAT_VALUE    g_krgJudgeCombat[2][2];
extern int                     g_irgRvRPKConsider[eCaste_MaxLevel][eCaste_MaxLevel];
extern int                     g_irgRewardBP[eCaste_MaxLevel];
extern short					g_srgAttackTypeVSArmorTypeChart[eAAC_ArmorTypeCount][eAAC_AttackTypeCount]; // 0, 0은 사용하지 않는다. 1부터 시작한다.
extern TNSPEECH_CONTENT         g_krgSpeechContent[eTNSpch_MaxContentCount+1];
extern char                    g_szrgComment[eTNSpch_MaxCommentCount+1][101];
extern short                   g_srgAIList[eTNAI_MaxAICount+1][eTNAI_MaxEventSort+1];
extern TNACTION_LIST            g_krgActionList[eTNAI_MaxActionListCount+1];
extern TNACTION                g_krgAction[eTNAI_MaxActionCount+1];

extern char                   g_pDetectEnemyTable[ePos_MaxPosCount][2];
extern short                   g_pDetectEnemyRadius[eRds_MaxDetectEnemy+1];
int						g_bIsKaliaOpend = false;
//int						g_iIsArenaOpend = 0; // 아레나가 열려있는지 검사
//int						g_iArenaWinner = 0;
//int						g_irgArenaEntry[eArena_MaxEntry] = { 0,0,0, };
//int						g_iArenaEntryCount = 0;

int                     g_irgRealm[eRealm_MaxCount] = { 0,0,0, };

int                     g_irgKalaAltarRewarder[eKalaRewarder_MaxCount] ;
extern TNKALA_ALTAR_OLD            g_krgKalaAltar[eKalaAltar_MaxCount];
extern HS2D_COORD				g_krgKalaRewarderPosition[eKalaRewarder_MaxCount][5];
int						g_iGambleHorse;
int						g_iGambleYut[5];
int						g_irgGateOfDungeon[3] = { 0,0,0, };
int						g_iSymbolAtByruCastle = 0;
TNAGGRSCORE             g_krgAggrScore[eAggrScore_MaxCount];
extern TNEVENT                 g_krgEventList[eEvent_MaxCount];
extern TNTASK                  g_krgTaskList[eTask_MaxCount];
extern short                   g_srgTimeSchedule[eTS_MaxSlot];  // 4초 tic,	900(60분*15(=60초를 4초로 나누면 15개 slice))
int                     g_irgEntryCount[5] = { 110, 30, 40, 0, 40 }; // 1,2,4는 각 주신 번호, 0번 index는 sum으로 한다.(or 3번 index)
TNDeck10000             g_krgBlessOfGod[eBlss_MaxSort][5]; //  전투/기부 2가지(2)에, 각 주신(1,2,4)별로 1가지씩(5)
TNRoute					g_krgRoute[eSiz_Route];
//---------------------------------------------------------------------------------
// Monster scroll
//---------------------------------------------------------------------------------
//TNDeck1000				g_kMonsterScroll;
//int g_irgMonsterToBeSummon[eMon_CountOfMonsterToBeSummon] = { 2120, 2122, 2123, 2124, 2125, 2126, 2127, 2071, 2072, };
//int g_irgMonsterToBeSummon[eMon_CountOfMonsterToBeSummon] = { 2124,2125,2126,2127,2226,2241,2238,2246,2247,2248,2249, };
//int g_irgMonsterToBeSummon[eMon_CountOfMonsterToBeSummon] = { 2124, 2125, 2126, 2127, 2226, 2241, 2238, 2246, 2247, 2248, 2249, 2071, 2072, };
//int g_irgMonsterToBeSummon[eMon_CountOfMonsterToBeSummon] = { 2124, 2125, 2126, 2127, 2071, 2072, 2241, 2238, 2246, 2247, 2473, 2473, 2473, };

TNSTRONGHOLD			g_krgStronghold[eStronghold_MaxCount];
HS2D_COORD				g_stPosStronghold[eStronghold_MaxCount];
DWORD					g_dwArenaMoney;
int						g_iBattleForStronghold = 0;
int						g_irgMonsterScroll[9] = { 2120, 2122, 2123, 2124, 2125, 2126, 2127, 2071, 2072, };
int                     g_irgGod[5] = { 0, 0, 0, };
int                     g_iZoneID = 0;
int						g_iZoneType = 0; // 0:일반, 1:주신전투, 2:요새전투
int                     g_iWorldID = 1; // 본섭은 1,2,3, 테섭은 0, 기준의 본섭이므로 default로 1을 설정
short					g_snVersion[4]; //	클라이언트 버전체크
int                     g_iTimeSlot = 0;
int                     g_iHours = 0;
int                     g_irgSetting[MAX_SETTING] = { 0,0,0, };
int                     g_irgSpeedConsider[6] = { 2000, 3000, 15, 5, 140, 0, }; // time slice, over time, correct, crack point, log level
CTFPercentMixer			g_RefineTable;
CTFPercentMixer			g_QuestTable;
bool                    g_bDecPrana = false;
//int                     g_iSwitch = 0xFFFFFFFF;
int                     g_iSwitch = 0x00000000;
int                     g_iMonsterLevelForWritingLog = 30;
int                     g_iCmdMaxLength = 200;
#ifdef __TN_PLAYMOVIE__
int                     g_irgFlag[10] = { 0,0,0, };
#endif
//TNScheduler				g_kScheduler;
//TNArena					g_kArena;

double					g_drgRwdCorrect[eSiz_RwdCorrect][eSiz_Type] = { 0, 0, 0, };
//double					g_drgRwdCorrect[eRwd_Braman][eRwd_Total] = 1;
//double					g_dRwdPranaCorrect = 1;
//double                  g_dRwdGoldCorrect = 1;
//double                  g_drgRwdCorrect[eRwd_Item][eRwd_Total] = 1;
int						g_nGiftItemIndex = 0;
int						g_nGiftItemMaxCount = 0;
int						g_nGiftItemCount = 0;
int						g_nGiftItemFirstCount = 0;
short					g_snGiftItemGenTime = 0;
STRUCT_ITEM				GiftItem;
int                     g_iViewGridX = 65;
int                     g_iViewGridY = 65;
int                     g_iHalfGridX = 32;
int                     g_iHalfGridY = 32;
//bool                    g_bIsInRvR = false;
int                     g_iFreeSlotForNPC = MAX_USER + 9;
int						g_nNameFilterCount = 0;
int						g_nChatFilterCount = 0;
char					g_strNameFilter[1500][20];
char					g_strChatFilter[1500][20];
TNDeck					g_krgEventDeck[eSiz_EventDeck];
int						g_irgRoom[eSiz_Room][2] = {  700, 700, 700, 701, 700, 702, 700, 703, 700, 704, 700, 705, 700, 706, 700, 707, 700, 708, 700, 709
													, 700, 710, 700, 711, 700, 712, 700, 713, 700, 714, 700, 715, 700, 716, 700, 717, 700, 718, 700, 719
													, 700, 720, 700, 721, 700, 722, 700, 723, 700, 724, 700, 725, 700, 726, 700, 727, 700, 728, 700, 729
													, 700, 730, 700, 731
													,
										};

CNPCGenerator			mNPCGen;
_S_GOBJ_GENERATIONAREA_PARAMS		pGenerationArea[MAX_GENERATION_AREA];
_S_TRIMURITY_AREA					TrimurityArea;
DWORD					g_dwUserConnect;
int						g_ItemRefineScale = 0;
int						g_ItemRefineGMScale = 0;
int						g_GateScale[5] = {0,};
int						g_GateTick[5] = {0,};
int						g_hGate[5] = {0,};
DWORD					g_dwCastleSalesMoney = 0;
BYTE					g_byCastleSalesRate = 0;
DWORD					g_dwRentalEraseDay = 0;
byte					g_byRentalTex = 0;
DWORD					g_dwRentalTexMoney = 0;
//int						g_iGiftItem[5] = {0,};
//int						g_iGiftItemCount[5] = {0,};
extern STGAMEEVENT		g_kGameEvent[MAX_EVENT];
int						g_iCastleOwner = 0;

//	Challenge
DWORD					g_dwChallengeMoney = 0;

//PORTALINFO							pPortalInfo[MAX_PORTAL_COUNT];
CHTParameterMgr g_ParamMgr;


int  g_HeightWidth  = MAX_GRIDX;
int  g_HeightHeight = MAX_GRIDY;
int  g_HeightPosX   = 0;
int  g_HeightPosY   = 0;
int  BILLING        = 3;  // 0:프리  1:빌링바인팅(초기화만)    2:빌링 각제집행   3:빌링테스트.
int  BillCounter	= 0;  // 0이면 카운트를 하지 않는다.
int	 ItemCounter	= 0;
int	MSGCounter		= 0;
int	g_Week=0;
int	g_Hour=0;
int Colo150Limit=0;
int PotionReady=0;
//	 CUser마다 LastReceive를 기억하고 있다가 10분이 경과한 유저는 접속을 해지한다. 




#ifdef _CHINESETRADITION		// 대만 LV0
		int  FREEEXP		= 0;
#elif  _CHINESESIMPLE			// 중국 LV0
		int  FREEEXP		= 0;
#else							// 한국 LV31
		int  FREEEXP        =  35;  
#endif 

int  CHARSELBILL    = 0;   // 한국은 0이 중국은 1.
int  DOUBLEMODE     = 0;
int	 DEADPOINT		= 1; // 죽었을때 경험치 감소
int  LastTick		= 20000;
int  POTIONCOUNT	=10;
int  PARTYBONUS     =100;
int	 GUILDBOARD		= 0;
int  ServerIndex    = -1;
int  Sapphire		=  8;	  // 청왕국이 받는 사파이어. 이것이 16이면 황왕국은 4, 청이 32이면 황은2, 청이 64면 황은 1 // 이외 없음.
int  ServerGroup    = -1;
int  GuildCounter   =  1;
int  DecayValue     =  8;
int  ServerDown     =  -1000;
int  UserCount      =  0;
int  SaveCount      =  1;
int  ItemCount      =  MAX_INITITEM;  // INITITEM은 성문등으로, Decay가 적용되지 않는다.
int  CurrentWeather =  0;
int  TESTSERVER     =  0;
int  LOCALSERVER    =  0;
int	 BRItem			=  0;
int	 TransperCharacter=0;
CPSock                 ListenSocket;
CPSock                 DBServerSocket;
CPSock                 MSGServerSocket;

char                   DBServerAddress[64];
int                    DBServerPort;

char                   MSGServerAddress[64];
int                    MSGServerPort;

CPSock                 ItemServerSocket;
char                   ItemServerAddress[64];
int                    ItemServerPort;

CPSock                 BillServerSocket;
char                   BillServerAddress[64];
int                    BillServerPort;

CPSock				   WhatsupSocket;
char				   WhatsupAddress[64];
int					   WhatsupPort;

FILE *                 fLogFile = NULL;
FILE *				   g_fpEvent = NULL;
unsigned int           SecCounter = 0;
unsigned int           MinCounter = 0;
unsigned int		   YutCounter = 0;
unsigned char          NPCRandomProgress[10]={0,0,0,0,0,0,0,0,0,0};
int  g_EmptyMob     = MAX_USER;

int PartyBonus[16] = { 100,200,300,400,500,500,500,500,500,500,500,500,500,500,500,500,};
//////////////////////////////////////////////////////////////////////////
int WeekMode = 4; // 길드전종료상태 일요일 새벽0시~금요일 새벽0시
int ColoState = 8;
int ForceWeekMode = -1; // -1은 길드전 시간을 조정하지 않음.
int GuildDay = 6; // 토요일.
int GuildHour = 21;
int NewbieHour = 20;
int BRHour		=19;
int BrState		=0;
int BrMod		=0;
int BrGrid		=0;
int ValidGuild = 3;
int NumGuildBattle = 50;
int LastLogDay = 0;
unsigned char LocalIP1[4]={0,0,0,0};
unsigned short LocalPort = 0;
char chLocalIP1[18]={0,};
unsigned char LocalIP2[4]={0,0,0,0};
char chLocalIP2[18]={0,};
char S_Key[32]={0,};
char temp[1024];
int g_dLevel1;
int g_dLevel2;
int g_dLevel;
HFONT hFont = NULL;
int ConfigReady=0;
int	g_iBrahmaCount = 0;
int	g_iVishnuCount = 0;
int	g_iSivaCount = 0;
int		g_nBrahmaBP = 0;
int		g_nVishnuBP = 0;
int		g_nSivaBP = 0;

int g_nItemCashType = 0;
enum { eItemCashTypeGeneral = 0, eItemCashTypeHanbit = 1 };

CHTRankSystem	g_RankSys;
CGameEvent		g_GameEvent;
CYut			g_Yut;
CRentalStore*	g_pRentalStore = NULL;

void SetViewEquip		(int nView, int nEquip);
void GetPCSkillMD5CheckSum( char *pCheckSum );

char g_szPCSkillCheckSum[32] = { 0, 0, };

void ExecuteEmergence()
{
	int iZone = ServerIndex + 1;

	#ifdef __TN_LOCAL_SERVER_SWITCH__

	g_iSwitch = g_iSwitch | eTNSwitch_EventLog;

	#endif

	for( int y = 0; y < 8; ++y )
	{
		for( int x = 0; x < 8; ++x )
		{
			if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked;
		}
	}


	if( eZone_Mandra == iZone )
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
	}
	else if( eZone_Shambala == iZone )
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
	}
	else if( eZone_Pamir == iZone )
	{
		g_krgMagicLamp[0].LoadData( "MagicLamp.txt" );
		g_krgMagicLamp[0].ShuffleMonsterCard();

		g_krgMagicLamp[1].LoadData( "MagicLamp2.txt" );
		g_krgMagicLamp[1].ShuffleMonsterCard();
/*
		g_kMonsterScroll.Init();
		g_kMonsterScroll.AddCard( 0, 120 );
		g_kMonsterScroll.AddCard( 1, 150 );
		g_kMonsterScroll.AddCard( 2, 150 );
		g_kMonsterScroll.AddCard( 3, 200 );
		g_kMonsterScroll.AddCard( 4, 30 );
		g_kMonsterScroll.AddCard( 5, 30 );
		g_kMonsterScroll.AddCard( 6, 70 );
		g_kMonsterScroll.AddCard( 7, 70 );
		g_kMonsterScroll.AddCard( 8, 70 );
		g_kMonsterScroll.AddCard( 9, 70 );
		g_kMonsterScroll.AddCard( 10, 20 );// 2473
		g_kMonsterScroll.AddCard( 11, 10 );// 2473
		g_kMonsterScroll.AddCard( 12, 10 );// 2473

		//srand( timeGetTime() );
		int iMaxShuffleCount = rand() % 10;
		iMaxShuffleCount += 3; // 최소 3회는 보장한다.
		for( int i = 0; i < iMaxShuffleCount; ++i ) g_kMonsterScroll.Shuffle(); // 여러번 shuffle을 시켜서 random성을 증대시킨다.
*/
	}
	else if( eZone_Cruma == iZone ) // 쿠르마, ...
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
		g_iZoneType = eZoneType_God;
	}
	else if( eZone_Chaturanka == iZone ) // 차투랑가이면, ...
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
		g_iZoneType = eZoneType_God;

		for( int y = 0; y < MAX_GRIDY; ++y )
		{
			for( int x = 0; x < MAX_GRIDX; ++x )
			{
				if( eTNCell_SafetyZone & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_SafetyZone;
			}
		}

	}
	else if( (13 == iZone) || (14 == iZone) || (15 == iZone) ) // 칼리아 주신던젼
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
		g_iZoneType = eZoneType_God;
	}
	else if( eZone_Katacomb == iZone ) // 북두성군
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;

		for( int y = 0; y < MAX_GRIDY; ++y )
		{
			for( int x = 0; x < MAX_GRIDX; ++x )
			{
				g_krgCell[y][x].usHeight = 10000;

				//if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usHeight = 20000;
			}
		}


		// 좌측
		for( int y = 190; y < 590; ++y )
		{
			for( int x = 155; x < 160; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked;				
			}
		}

		for( int y = 325; y < 457; ++y )
		{
			for( int x = 80; x < 120; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked;
			}
		}

		// 우측
		for( int y = 190; y < 590; ++y )
		{
			for( int x = 865; x < 868; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked;
			}
		}

		for( int y = 325; y < 457; ++y )
		{
			for( int x = 903; x < 945; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked;
			}
		}


	}
	else if( eZone_Stronghold == iZone )
	{
		g_iZoneType = eZoneType_Guild;
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
	}
	else if( eZone_Castle == iZone )
	{
		g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
	}
	else if( eZone_CastleDungeon == iZone )
	{
		g_krgEventDeck[0].Init( 16 );
		g_krgEventDeck[0].AddCard( 1, 1 );
		g_krgEventDeck[0].AddCard( 2, 1 );
		g_krgEventDeck[0].AddCard( 3, 1 );
		g_krgEventDeck[0].AddCard( 4, 1 );
		g_krgEventDeck[0].AddCard( 5, 1 );
		g_krgEventDeck[0].AddCard( 6, 1 );
		g_krgEventDeck[0].AddCard( 7, 1 );
		g_krgEventDeck[0].AddCard( 8, 1 );
		g_krgEventDeck[0].AddCard( 9, 1 );
		g_krgEventDeck[0].AddCard( 10, 1 );
		g_krgEventDeck[0].AddCard( 11, 1 );
		g_krgEventDeck[0].AddCard( 12, 1 );
		g_krgEventDeck[0].AddCard( 13, 1 );
		g_krgEventDeck[0].AddCard( 14, 1 );
		g_krgEventDeck[0].AddCard( 15, 1 );
		g_krgEventDeck[0].AddCard( 16, 1 );
		g_krgEventDeck[0].Shuffle();

		g_krgEventDeck[1].Init( 10 );
		g_krgEventDeck[1].AddCard( 17, 1 );
		g_krgEventDeck[1].AddCard( 18, 1 );
		g_krgEventDeck[1].AddCard( 19, 1 );
		g_krgEventDeck[1].AddCard( 20, 1 );
		g_krgEventDeck[1].AddCard( 21, 1 );
		g_krgEventDeck[1].AddCard( 22, 1 );
		g_krgEventDeck[1].AddCard( 23, 1 );
		g_krgEventDeck[1].AddCard( 24, 1 );
		g_krgEventDeck[1].AddCard( 25, 1 );
		g_krgEventDeck[1].AddCard( 26, 1 );
		g_krgEventDeck[1].Shuffle();

		g_krgEventDeck[2].Init( 4 );
		g_krgEventDeck[2].AddCard( 27, 1 );
		g_krgEventDeck[2].AddCard( 28, 1 );
		g_krgEventDeck[2].AddCard( 29, 1 );
		g_krgEventDeck[2].AddCard( 30, 1 );
		g_krgEventDeck[2].Shuffle();
		//g_krgEventDeck[2].AddCard( 31, 6 );
	}
	
}
     


BOOL AddCrackError(int conn,int val,int Type)
{
	if( 0 >= conn || MAX_USER <= conn ) return FALSE;
	//if (Type!=3 && Type!=8 && Type!=15)
	//{
	sprintf(temp,"cra point: %d  type: %d",val,Type);
	Log(temp,pUser[conn].AccountName,pUser[conn].IP);  
	//}

	//	운영팀요청에 따라 접속종료시키지않고 로그만 남기기로함.
	//if(Type==CRACK_SPEED_HACK4)
	//{	/*sprintf(temp,"cra point: %d  type: %d",val,Type);
	//	Log(temp,pUser[conn].AccountName,pUser[conn].IP);  */
	//	return TRUE;
	//}

	pUser[conn].NumError=pUser[conn].NumError+val;
	if	(pUser[conn].NumError>=30)
	{	SendClientMessage(conn,g_pMessageStringTable[_Bad_Network_Packets]);
		pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout;
		CloseUser(conn);
		sprintf(temp,"cra char:%s type: %d", pMob[conn].MOB.szName, Type);
		Log(temp,pUser[conn].AccountName,pUser[conn].IP);  
		return TRUE;
	}
	return FALSE;
}

int	ReadConfig(void)
{	
	#ifndef __TN_LOCAL_SERVER_SWITCH__
	//char temp[256];
	g_nNameFilterCount = 0; g_nChatFilterCount = 0; 
	FILE * fp=NULL;
	//FILE * fp=fopen("Config.txt","rt");
	//if(fp)
	//{	fscanf(fp,"%s %d",temp,&g_ItemRefineScale);
	//	fclose(fp);
	//} else
	//{	MessageBox(hWndMain,"cant find Config.txt","BOOTING ERROR",NULL);
	//}

	char pChar[128] = {0,};

	fp=fopen("NameFilter.txt","rt");
	if(fp)
	{	while(1)
		{	if(g_nNameFilterCount>0)
			{	int nLength = strlen(g_strNameFilter[g_nNameFilterCount-1]);
				if(g_strNameFilter[g_nNameFilterCount-1][nLength-1]=='\n')
					g_strNameFilter[g_nNameFilterCount-1][nLength-1]=0;
				if(!strcmp(g_strNameFilter[g_nNameFilterCount-1],"")) g_nNameFilterCount--;
			}

			if( fgets(pChar, 100, fp) == NULL) break;
			strncpy(g_strNameFilter[g_nNameFilterCount++], _strupr( _strdup( pChar ) ), strlen(pChar));
			ZeroMemory(pChar, sizeof(pChar));
		}
		g_nNameFilterCount--;
		fclose(fp);
	} else
	{	MessageBox(hWndMain,"cant find NameFilter.txt","BOOTING ERROR",NULL);
	}

	fp=fopen("ChatFilter.txt","rt");
	if(fp)
	{	while(1)
		{	if(g_nChatFilterCount>0)
			{	int nLength = strlen(g_strChatFilter[g_nChatFilterCount-1]);
				if(g_strChatFilter[g_nChatFilterCount-1][nLength-1]=='\n')
					g_strChatFilter[g_nChatFilterCount-1][nLength-1]=0;
				if(!strcmp(g_strChatFilter[g_nChatFilterCount-1],"")) g_nChatFilterCount--;
			}

			if( fgets(pChar, 100, fp) == NULL) break;
			strncpy(g_strChatFilter[g_nChatFilterCount++], _strupr( _strdup( pChar ) ), strlen(pChar));
			ZeroMemory(pChar, sizeof(pChar));
		}
		g_nChatFilterCount--;
		fclose(fp);
	} else
	{	MessageBox(hWndMain,"cant find NameFilter.txt","BOOTING ERROR",NULL);
	}
	#endif

	return TRUE;
}

void AddFailAccount(char * Account)
{
	for (int i=0;i<16;i++)
	{	if  (FailAccount[i][0]==0)
		{	strcpy(FailAccount[i],Account);
			return;
		}
	}
}

int  CheckFailAccount(char * Account)
{	int Num=0;
	for (int i=0;i<16;i++)
	{	if  (FailAccount[i][0]!=0)
		{	 if ( strcmp(FailAccount[i],Account)==0) Num++;
		}
	}
	return Num;
}

void GenerateMob(int idx,int xfix,int yfix)
{
    int posidx = idx;    
	int irgPopMonsters[5] = { 0, 0, 0, };
    if( 0 < mNPCGen.pList[idx].iGroup ) // 1~2번도 group에 해당한다. 수정이 필요함.
    {
        if((mNPCGen.pList[idx].krgMonsterList[0].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[0].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[0].iPopCountPerTime ) irgPopMonsters[0] = 1; //bPopMonster = false;
        if((mNPCGen.pList[idx].krgMonsterList[1].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[1].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[1].iPopCountPerTime ) irgPopMonsters[1] = 1; //bPopMonster = false;
        if((mNPCGen.pList[idx].krgMonsterList[2].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[2].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[2].iPopCountPerTime ) irgPopMonsters[2] = 1; //bPopMonster = false;
        if((mNPCGen.pList[idx].krgMonsterList[3].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[3].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[3].iPopCountPerTime ) irgPopMonsters[3] = 1; //bPopMonster = false;
        if((mNPCGen.pList[idx].krgMonsterList[4].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[4].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[4].iPopCountPerTime ) irgPopMonsters[4] = 1; //bPopMonster = false;
    }
  
    int iFollowerNO = 0;
    int iLeader = 0;
    for( int iCmd = 0; iCmd < eCmd_MaxCount; ++iCmd )
    {
        if( eCmd_None == mNPCGen.pList[idx].krgCommand[iCmd].iCommand ) continue;
        if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) )// && bPopMonster )
        {
            int iIndex = mNPCGen.pList[idx].krgCommand[iCmd].iIndex;
			if( irgPopMonsters[iIndex] ) continue;
            for( int iPop = 0; iPop < mNPCGen.pList[idx].krgCommand[iCmd].iCount; ++iPop )
            {
                if( mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount >= mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ) break;

                int mob = 0;            
                for( int iReadyMobIndex = 0; iReadyMobIndex < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount; ++iReadyMobIndex )
                {
                    if( 1 == mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1] )
                    {
                        mob = mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][0];
                
            			if  (mob<MAX_USER || mob >=MAX_MOB)
            			{   sprintf(temp,"err no emptymob leader: %d - %d",idx,mob);
            				Log(temp,"-system",0);
            				continue;  // MobList가 꽉 찼다.
            			}
		            	  
						/*
						#ifdef __DYNAMIC_LOG__
						if( pMob[mob].m_iDebugFlag || (eZoneType_Guild == g_iZoneType) )
						{ // debug_0503
							SYSTEMTIME st;
							GetLocalTime( &st );
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "GenerateMob(); %d일%d시%d분> Handle:%d, Tribe:%d, Mode:%d, FSM:%d, generateIndex:%d, 순번:%d, 준비상태:%d, 최대팝수:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute
								, mob, pMob[mob].MOB.snTribe, pMob[mob].Mode, pMob[mob].m_eFSM
								, idx, iReadyMobIndex, mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1], mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								);
							if( eZoneType_Guild == g_iZoneType ) WriteLog( chBuf, ".\\Event\\[DEBUG]Duruka.txt" );
							else WriteLog( chBuf, pMob[mob].m_szLogFile );
						}	
						#endif
						*/

						//if( pMob[mob].m_kLastTime.uiKilled > CurrentTime ) continue;
						if( pMob[mob].IsWaitToPop() ) continue;

						pMob[mob].GenerateIndex = idx;
						pMob[mob].RouteType = mNPCGen.pList[idx].RouteType;
            			pMob[mob].Formation = mNPCGen.pList[idx].Formation;
						pMob[mob].Leader = 0;
						//pMob[mob].m_bSolo = true;
						pMob[mob].m_iGroup = mNPCGen.pList[idx].iGroup; 
		          	
           				// MOB 세그먼트 리스트 세팅
           				if( eTNRout_FixPosition == mNPCGen.pList[idx].RouteType ) // don't move
           				{
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[i];
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[i];
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[i]; // 0
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[i];
          					}
          				}
          				else if( eTNRout_RandomPopNLiveThereOnly == mNPCGen.pList[idx].RouteType ) // Random Pop
          				{
							pMob[mob].RouteType = eTNRout_MoveNRoam;
          					int iPopArea = rand() % 5;
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[iPopArea] - mNPCGen.pList[idx].SegmentRange[iPopArea] + rand()%(mNPCGen.pList[idx].SegmentRange[iPopArea]*2+1);
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[iPopArea] - mNPCGen.pList[idx].SegmentRange[iPopArea] + rand()%(mNPCGen.pList[idx].SegmentRange[iPopArea]*2+1);
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[iPopArea];
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[iPopArea];

								g_kInfluenceMap.BuildInfluenceGrids( pMob[mob].SegmentListX[i], pMob[mob].SegmentListY[i], pMob[mob].m_krgInfluenceGrid, pMob[mob].m_iInfluenceGridSize );
								if( 0 >= pMob[mob].m_iInfluenceGridSize )
								{
									pMob[mob].Mode = MOB_EMPTY;
									pMob[mob].MOB.szName[0]=0;							
									continue;
								}
								else
								{
									int iArea = rand() % pMob[mob].m_iInfluenceGridSize;
									pMob[mob].SegmentListX[i] = pMob[mob].m_krgInfluenceGrid[iArea].x + rand()%TN_GRID_SIZE;
									pMob[mob].SegmentListY[i] = pMob[mob].m_krgInfluenceGrid[iArea].y + rand()%TN_GRID_SIZE;
								}
          					}
          				}
          				else
          				{
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[i] - mNPCGen.pList[idx].SegmentRange[i] + rand()%(mNPCGen.pList[idx].SegmentRange[i]*2+1);
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[i] - mNPCGen.pList[idx].SegmentRange[i] + rand()%(mNPCGen.pList[idx].SegmentRange[i]*2+1);
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[i];
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[i];

								g_kInfluenceMap.BuildInfluenceGrids( pMob[mob].SegmentListX[i], pMob[mob].SegmentListY[i], pMob[mob].m_krgInfluenceGrid, pMob[mob].m_iInfluenceGridSize );
								if( 0 >= pMob[mob].m_iInfluenceGridSize )
								{
										pMob[mob].Mode = MOB_EMPTY;
									pMob[mob].MOB.szName[0]=0;
									continue;
								}
								else
								{
									int iArea = rand() % pMob[mob].m_iInfluenceGridSize;
									pMob[mob].SegmentListX[i] = pMob[mob].m_krgInfluenceGrid[iArea].x + rand()%TN_GRID_SIZE;
									pMob[mob].SegmentListY[i] = pMob[mob].m_krgInfluenceGrid[iArea].y + rand()%TN_GRID_SIZE;
								}
          					}
          				}		      

						/*
						if( eZoneType_Guild == g_iZoneType )
						{// debug_0503
							SYSTEMTIME st;
							GetLocalTime( &st );
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "[%d일%d시%d분] GenerateMob() > Tribe:%d, Handle:%d, Mode:%d, FSM:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute
								, pMob[mob].MOB.snTribe, mob, pMob[mob].Mode, pMob[mob].m_eFSM
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								);
							WriteLog( chBuf, ".\\Event\\[DEBUG]Duruka.txt" );
						}	
						*/

						pMob[mob].MOB = mNPCGen.pList[idx].krgMonsterList[iIndex].kMobData;
						pMob[mob].Init(mob);

            			int ttx = pMob[mob].SegmentListX[0];
            			int tty = pMob[mob].SegmentListY[0];
            			//int tret = GetEmptyMobGrid(mob,&ttx,&tty, pMob[mob].SegmentRange[0] );
						int tret = PickFreeMobGrid(mob,&ttx,&tty );
            			if  (tret==FALSE)
            			{     
            				{
            					char chBuf[256] = { 0,0,0, };
            					sprintf(chBuf, "[GenerateMob] monster:%d, Tribe:%d, x:%d, y:%d \r\n", mob, pMob[mob].MOB.snTribe, ttx, tty );
            					WriteLog( chBuf, ".\\monster_log\\[Log]FailToPop.txt" );
            				}
			            
							pMob[mob].Mode = MOB_EMPTY;
            				pMob[mob].MOB.szName[0]=0;
            				continue;
            			}
            			pMob[mob].LastX = pMob[mob].TargetX = pMob[mob].SegmentX = ttx;
            			pMob[mob].LastY = pMob[mob].TargetY = pMob[mob].SegmentY = tty;
		            	
            			if( 0 > mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount ) mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount = 0;
            			++mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount;
						mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1] = 0;
             			
						memset(pMob[mob].m_irgParty,0,sizeof(pMob[mob].m_irgParty));
						if( 0 < mNPCGen.pList[idx].iGroup ) // party일 경우
						{
							if( 0 == iIndex ) iLeader = mob; // Leader일 경우만, 수행
							else // Leader가 정해진 이후에만, 즉 Follower일 경우만, 수행
							{
								pMob[mob].Leader = iLeader;
                				pMob[iLeader].m_irgParty[iFollowerNO]=mob;
                				++iFollowerNO;
                			}
						}
		     
						sprintf( pMob[mob].MOB.szName, "%d_%d", mNPCGen.pList[idx].krgMonsterList[iIndex].kMobData.snTribe, mob ); // 총 9자
						//////////////////////////////////////////////////////////////////////

						pMob[mob].Think( eTNAI_Pop, 0 );
						pMob[mob].m_iDirection = mNPCGen.pList[idx].Formation;
            			S_SCP_INIT_OTHER_MOB sm;
            			GetCreateMob( mob, &sm );
             			pMobGrid[tty][ttx] = mob;
            			GridMulticast( ttx, tty, (MSG_STANDARD*)&sm, 0);

						//SYSTEMTIME st;
						//GetLocalTime( &st );

						#ifdef __DYNAMIC_LOG__
						if( 0 < pMonsterData[pMob[mob].MOB.nTP].byQuest[eMonPrty_Reserved4] )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "GenerateMob(); %dyy%dmm%ddd %dhh%dmi%dss> Handle:%d, Tribe:%d, Mode:%d, FSM:%d, generateIndex:%d, 순번:%d, 준비상태:%d, 최대팝수:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
								, mob, pMob[mob].MOB.snTribe, pMob[mob].Mode, pMob[mob].m_eFSM
								, idx, iReadyMobIndex, mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1], mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								);

							WriteLog( chBuf, pMob[mob].m_szLogFile );
						}	
						#endif

						if( eTNAudit_Boss & pMonsterData[pMob[mob].MOB.nTP].byQuest[eMonPrty_Reserved4] )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "[GenerateMob] %dyy%dmm%ddd %dhh%dms%dss, Boss(%d, %d) is summoned!!\r\n", g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
								, pMob[mob].MOB.snTribe, mob );
							WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
						}

						break;
					}
				} //for( int iReadyMobIndex = 0; iReadyMobIndex < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount; ++iReadyMobIndex )            	
            } // for( int iPop = 0; iPop < mNPCGen.pList[idx].krgCommand[iCmd]; ++iPop )
        } // end of if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) && bPopMonster )            
    }    

	return;
}

BOOL NameFilter(char* pName)
{
	if(_mbsstr((unsigned char*)pName, (unsigned char*)"GM")) return FALSE;
	if(_mbsstr((unsigned char*)pName, (unsigned char*)"gm")) return FALSE;
	char *pDest = NULL;
	char* pChar = _strupr( _strdup( pName ) );

	for(int i=0; i<g_nNameFilterCount; i++)
	{	if(g_eCountryID==eCountryChina || g_eCountryID==eCountryKorea)
		{	pDest = (char*)_mbsstr((unsigned char*)pChar, (unsigned char*)g_strNameFilter[i]);
			if(pDest!=NULL)
			{	int nLength = _mbslen((unsigned char*)g_strNameFilter[i]);
				if(_mbsncmp((unsigned char*)pDest, (unsigned char*)g_strNameFilter[i], nLength)) continue;
				return FALSE;
			}
		}	else
		{	if(!_mbscmp((unsigned char*)pChar, (unsigned char*)g_strNameFilter[i])) return FALSE;
		}
	}

	return TRUE;
}

BOOL ChatFilter(char* pChat)
{
	char* pDest = NULL;
	char* pChar = _strupr( _strdup( pChat ) );

	for(int i=0; i<g_nChatFilterCount; i++)
	{
		pDest = (char*)_mbsstr((unsigned char*)pChar, (unsigned char*)g_strChatFilter[i]);
		if(pDest!=NULL)
		{	int nLength = _mbslen((unsigned char*)g_strChatFilter[i]);
			if(_mbsncmp((unsigned char*)pDest, (unsigned char*)g_strChatFilter[i], nLength)) continue;
			return FALSE;
		}
	}

	return TRUE;
}

LONG APIENTRY MainWndProc (HWND, UINT, UINT, LONG);
BOOL InitApplication(HANDLE hInstance)   
{    WNDCLASS  wc;  wc.style = CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS;    
     wc.lpfnWndProc = (WNDPROC)MainWndProc;  wc.cbClsExtra = 0;  wc.cbWndExtra = 0;                    
     wc.hIcon = (HICON)LoadIcon ((HINSTANCE)hInstance, "MAINICON");
     wc.hInstance = (HINSTANCE) hInstance;  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
     wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);  wc.lpszMenuName =  NULL;           
     wc.lpszClassName = "MainClass"; if(!RegisterClass(&wc)) return RegisterClass(&wc);
     return TRUE;
}

BOOL InitInstance( HANDLE hInstance, int nCmdShow)  
{    hMainMenu = CreateMenu();
 	 hWndMain = CreateWindow(   "MainClass",  "Game Server", 
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN ,    // Window style. 
        CW_USEDEFAULT,   CW_USEDEFAULT, 640+8,   480,            // W,H[Menu합치면 480]
        NULL,    hMainMenu,  (HINSTANCE)hInstance,   NULL     );
     if (!hWndMain) return (FALSE);
     ShowWindow(hWndMain, nCmdShow);  
     UpdateWindow(hWndMain);          
   return (TRUE);     
}

void SetValidUser(int num)
{

	for	(int i=0;i<MAX_USER;i++)
	{
		if	(i<num)
		{
			if	(pUser[i].cSock.pSendBuffer==NULL) pUser[i].cSock.pSendBuffer = new char[SEND_BUFFER_SIZE];//(char*)malloc(SEND_BUFFER_SIZE);
			if	(pUser[i].cSock.pSendBuffer==NULL) 
			{	sprintf(temp,"err get send buffer fail %d",i);
				Log(temp,"system",0);
			}
			if	(pUser[i].cSock.pRecvBuffer==NULL) pUser[i].cSock.pRecvBuffer = new char[RECV_BUFFER_SIZE];//(char*)malloc(RECV_BUFFER_SIZE);
			if	(pUser[i].cSock.pRecvBuffer==NULL) 
			{	sprintf(temp,"err get send buffer fail %d",i);
				Log(temp,"system",0);
			}
		}	else
		{	if	(pUser[i].cSock.pSendBuffer!=NULL) {free(pUser[i].cSock.pSendBuffer);pUser[i].cSock.pSendBuffer=NULL;}
			if	(pUser[i].cSock.pRecvBuffer!=NULL) {free(pUser[i].cSock.pRecvBuffer);pUser[i].cSock.pRecvBuffer=NULL;}
		}
	}
}

WINAPI WinMain(  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{	
	MSG msg;
	UNREFERENCED_PARAMETER( lpCmdLine );
	if	(!hPrevInstance)
	if	(!InitApplication(hInstance)) return (FALSE);             
	if	(!InitInstance(hInstance, nCmdShow)) return (FALSE);
	//OUT_DEVICE_PRECIS     OUT_RASTER_PRECIS
	hFont	=	CreateFont(12, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,	DEFAULT_PITCH,	"Fixedsys"); // |FF_DECORATIVE
	HICON mimi = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hWndMain,WM_SETICON,ICON_BIG,(DWORD)mimi);
	SendMessage(hWndMain,WM_SETICON,ICON_SMALL,(DWORD)mimi);

	//LoadDump( "28" );
	//LoadDump( "파일명(확장자제외)" );

	srand( timeGetTime() );
	GetLocalTime( &g_kSystemTime );

	SetValidUser(ValidUser);
	BASE_InitModuleDir();
	BASE_InitializeServerList();
	StartLog();
	ReadConfig();
	ConfigReady=1;

	char	name1[255] = {0,}; 
	char	name2[255] = {0,}; 
	FILE* fp1 = fopen("localip.txt","rt");
	if	(fp1) 
	{	fscanf(fp1,"%s %d",name1, &LocalPort);
		fscanf(fp1,"%s",name2);
		fclose(fp1);
		chLocalIP1[16]=0; chLocalIP1[17]=0; strncpy(chLocalIP1, name1, 16);
		chLocalIP2[16]=0; chLocalIP2[17]=0; strncpy(chLocalIP2, name2, 16);
		if(!strncmp(chLocalIP2,"",17)) memcpy(chLocalIP2, chLocalIP1, 17);
	}	else	
	{	MessageBox(hWndMain,"Can't find localip.txt","REBOOTING ERROR",NULL);
	}

	if(!g_ParamMgr.HT_bLoad(CHTString("TantraParam.tpa")))
	{	MessageBox(hWndMain,"Can't find TantraParam.tpa","REBOOTING ERROR",NULL);
	}

	GetPCSkillMD5CheckSum( g_szPCSkillCheckSum );

	/////////////// 데이터를 로딩한다. //////////////////////
	SetLogFileName();
	LoadWorldSettings(); // zone 개개에 대해서는 전혀 관련이 없다.
	LoadZoneSettings();
	LoadRouteData();
	LoadItemData();
	LoadSkillData();
	LoadMonsterData();	
	g_kScheduler.Load();
	QUEST_LoadTask();
	LoadSettingTxl();
	//LogRewardItems();

	LoadStrongholdData();
	g_kSiege.LoadData();

	if	(DBServerSocket.pSendBuffer==NULL) DBServerSocket.pSendBuffer = new char[SEND_BUFFER_SIZE*2];		//(char*)malloc(SEND_BUFFER_SIZE);
	if	(DBServerSocket.pSendBuffer==NULL) 
	{	sprintf(temp,"err get DB send buffer fail ");
		Log(temp,"system",0);
	}
	if	(DBServerSocket.pRecvBuffer==NULL) DBServerSocket.pRecvBuffer = new char[SEND_BUFFER_SIZE*2];		//	(char*)malloc(RECV_BUFFER_SIZE);
	if	(DBServerSocket.pRecvBuffer==NULL) 
	{	sprintf(temp,"err get DB recv buffer fail ");
		Log(temp,"system",0);
	}
	if	(MSGServerSocket.pSendBuffer==NULL) MSGServerSocket.pSendBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(SEND_BUFFER_SIZE);
	if	(MSGServerSocket.pSendBuffer==NULL) 
	{	sprintf(temp,"err get MSG send buffer fail ");
		Log(temp,"system",0);
	}
	if	(MSGServerSocket.pRecvBuffer==NULL) MSGServerSocket.pRecvBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(RECV_BUFFER_SIZE);
	if	(MSGServerSocket.pRecvBuffer==NULL) 
	{	sprintf(temp,"err get MSG recv buffer fail ");
		Log(temp,"system",0);
	}
	if	(ItemServerSocket.pSendBuffer==NULL) ItemServerSocket.pSendBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(SEND_BUFFER_SIZE);
	if	(ItemServerSocket.pSendBuffer==NULL) 
	{	sprintf(temp,"err get ITEM send buffer fail ");
		Log(temp,"system",0);
	}
	if	(ItemServerSocket.pRecvBuffer==NULL) ItemServerSocket.pRecvBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(RECV_BUFFER_SIZE);
	if	(ItemServerSocket.pRecvBuffer==NULL) 
	{	sprintf(temp,"err get ITEM recv buffer fail ");
		Log(temp,"system",0);
	}
	if	(BillServerSocket.pSendBuffer==NULL) BillServerSocket.pSendBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(SEND_BUFFER_SIZE);
	if	(BillServerSocket.pSendBuffer==NULL) 
	{	sprintf(temp,"err get Bill send buffer fail ");
		Log(temp,"system",0);
	}
	if	(BillServerSocket.pRecvBuffer==NULL) BillServerSocket.pRecvBuffer = new char[SEND_BUFFER_SIZE*2];	//(char*)malloc(RECV_BUFFER_SIZE);
	if	(BillServerSocket.pRecvBuffer==NULL) 
	{	sprintf(temp,"err get Bill recv buffer fail ");
		Log(temp,"system",0);
	}

	if ( g_eCountryID == eCountryChina )
	{
		if (WhatsupSocket.pSendBuffer==NULL) WhatsupSocket.pSendBuffer = new char[SEND_BUFFER_SIZE*2];
		if (WhatsupSocket.pSendBuffer==NULL)
		{	sprintf(temp,"err get What's up send buffer fail");
			Log(temp,"system",0);
		}
		if (WhatsupSocket.pRecvBuffer==NULL) WhatsupSocket.pRecvBuffer = new char[SEND_BUFFER_SIZE*2];
		if (WhatsupSocket.pRecvBuffer==NULL)
		{	sprintf(temp,"err get What's up recv buffer fail");
			Log(temp,"system",0);
		}
	}

	FILE* fp = NULL;

	Reboot();

	//PrintMapInfo();
	//g_kInfluenceMap.Print();

	RegisterMonstersToArea();


	g_dwUserConnect=0;
	memset(pGenerationArea,0,sizeof(pGenerationArea));
	memset(&TrimurityArea,0,sizeof(TrimurityArea));

	_S_FILE_HEADER_INFO sInfo;
	int ss = sizeof(sInfo);
	FILE * fpInfo = fopen("GenerationArea.idx","rb");
	if(fpInfo)
	{	fread(&sInfo,sizeof(sInfo),1,fpInfo);
		fread(pGenerationArea,sizeof(_S_GOBJ_GENERATIONAREA_PARAMS),sInfo.nDataCount,fpInfo);

		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[Load Generation.idx] 0:%d(%d,%d)~(%d,%d), 1:%d(%d,%d)~(%d,%d), 2:%d(%d,%d)~(%d,%d), 3:%d(%d,%d)~(%d,%d)"
				, pGenerationArea[0].dwIndex, pGenerationArea[0].snStartX, pGenerationArea[0].snStartZ, pGenerationArea[0].snEndX, pGenerationArea[0].snEndZ
				, pGenerationArea[1].dwIndex, pGenerationArea[1].snStartX, pGenerationArea[1].snStartZ, pGenerationArea[1].snEndX, pGenerationArea[1].snEndZ
				, pGenerationArea[2].dwIndex, pGenerationArea[2].snStartX, pGenerationArea[2].snStartZ, pGenerationArea[2].snEndX, pGenerationArea[2].snEndZ
				, pGenerationArea[3].dwIndex, pGenerationArea[3].snStartX, pGenerationArea[3].snStartZ, pGenerationArea[3].snEndX, pGenerationArea[3].snEndZ
				);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadGererationArea.txt" );
		}

		fclose(fpInfo);
	}	else
	{	MessageBox(hWndMain,"Can't find GenerationArea.idx","REBOOTING ERROR",NULL);
	}

	int nTrimurity=0;
	for(int i=0; i<sInfo.nDataCount; i++)
	{	nTrimurity=pGenerationArea[i].dwIndex;
		if(nTrimurity<0 || nTrimurity>3) continue;	//	0:common, 1:브라흐마 2:비슈느 3:시바

		BYTE byCount=TrimurityArea.byTrimuriti[nTrimurity]++;
		TrimurityArea.pArea[nTrimurity][byCount]=pGenerationArea[i];
	}

	for( int iPopArea = 1; iPopArea < 4; ++iPopArea )
	{
		if( 0 == TrimurityArea.byTrimuriti[iPopArea] )
		{
			TrimurityArea.byTrimuriti[iPopArea] = 1;
			TrimurityArea.pArea[iPopArea][0] = TrimurityArea.pArea[0][0];
		}
	}

	//char iniTemp[255];
	//char szPathname[MAX_PATH];
	//GetCurrentDirectory( MAX_PATH, szPathname );
	//strcat( szPathname, "\\" );
	//strcat( szPathname, "PortalList.ini");
	//ZeroMemory( pPortalInfo, sizeof( PORTALINFO ) * MAX_PORTAL_COUNT );
	//int nCount = GetPrivateProfileInt("Portal Count","Portal Count",0,szPathname);
	//for(i=1;i<=nCount;i++)
	//{	sprintf(iniTemp,"Portal:%d",i);
	//	pPortalInfo[i].wPortalID=GetPrivateProfileInt(iniTemp,"ID",0,szPathname);
	//	pPortalInfo[i].wServerID=GetPrivateProfileInt(iniTemp,"Server ID",0,szPathname);
	//	pPortalInfo[i].snSX=GetPrivateProfileInt(iniTemp,"snX",0,szPathname);
	//	pPortalInfo[i].snSZ=GetPrivateProfileInt(iniTemp,"snZ",0,szPathname);
	//	pPortalInfo[i].snEX=GetPrivateProfileInt(iniTemp,"enX",0,szPathname);
	//	pPortalInfo[i].snEZ=GetPrivateProfileInt(iniTemp,"enZ",0,szPathname);
	//}

	int	ret = ListenSocket.WSAInitialize();
	if	(ret==NULL)	{  Log("err WSAInitialize fail","-system",0);   return FALSE;    }
	
	/////////////SetLocalAddress////////////////////////////////////////
	//char	name1[255] = {0,}; 
	//char	name2[255] = {0,}; fp=NULL;
	//fp = fopen("localip.txt","rt");
	//if	(fp) 
	//{	fscanf(fp,"%s %d",name1, &LocalPort);
	//	fscanf(fp,"%s",name2);
	//	fclose(fp);
	//	chLocalIP1[16]=0; chLocalIP1[17]=0; strncpy(chLocalIP1, name1, 16);
	//	chLocalIP2[16]=0; chLocalIP2[17]=0; strncpy(chLocalIP2, name2, 16);
	//}	else	
	//{	MessageBox(hWndMain,"Can't find localip.txt","REBOOTING ERROR",NULL);
	//}
	int r1,r2,r3,r4,r5,r6,r7,r8;;
	sscanf(chLocalIP1,"%d.%d.%d.%d",&r1,&r2,&r3,&r4);
	sscanf(chLocalIP2,"%d.%d.%d.%d",&r5,&r6,&r7,&r8);
	LocalIP1[0]=r1;	LocalIP1[1]=r2;	LocalIP1[2]=r3;	LocalIP1[3]=r4;	
	LocalIP2[0]=r5;	LocalIP2[1]=r6;	LocalIP2[2]=r7;	LocalIP2[3]=r8;	
	////////////////////////////////////////////////////////////////////////////
	DBServerAddress[0]=0;
	for ( i=0;i<MAX_SERVERGROUP;i++)
	{	for (int j=1;j<MAX_SERVERNUMBER;j++)//MAX_SERVERNUMBER = MAX_SERVER+1
		{	if (!strcmp(g_pServerList[i][j],name1) && g_pServerListPort[i][j] == LocalPort) 
			{	strcpy(DBServerAddress,g_pServerList[i][0] );
				strcpy(MSGServerAddress,g_pServerList[i][INDEXOFMESSENGER] );
				ServerGroup=i;
				ServerIndex=j-1;
				if(g_iZoneID!=ServerIndex+1) 
				{
					MessageBox(hWndMain,"Serverlist does not correspond with the Setting in ZoneID.","Error",MB_OK|MB_SYSTEMMODAL);
					return TRUE;
				}
				break;
			}
		}
		if (DBServerAddress[0]!=0) break;      
	}

	//IsInRvR();
	PopMonstersForEvent();
	ExecuteEmergence();

	if	(DBServerAddress[0]==0)
	{	MessageBox(hWndMain,"Can't get Server Group Index. check [Locakip.txt] and [ServerList.txt]","Error",MB_OK|MB_SYSTEMMODAL);
		return TRUE;
	}
	DBServerPort=LocalPort+1000;
	MSGServerPort=LocalPort+2000;
	int * pip1 = (int*)LocalIP1;
	int * pip2 = (int*)LocalIP2;

	if(g_eCountryID == eCountryPhilippines)		//	필리핀은 DBA를 오픈라인사용한다
		ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip1,WSA_READDB,hWndMain);
	else
		ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip2,WSA_READDB,hWndMain);

	if	(ret==NULL)
	{	Log("err Can't connect to DB-Server.","-system",0);
		MessageBox(hWndMain,"Can't connect to DB-SERVER","REBOOTING ERROR",NULL);
		return 0;
	}	else
	{	//	DB에게 자신의 데이터 초기화를 요청함.
		S_REQUEST sm; sm.wType=SSP_REQ_ZONE_INIT;
		DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm));
	}

	// 메신저서버소켓은 ASYNC로 연결한다
	// MSGServerSocket.ConnectServerAsync(MSGServerAddress,MSGServerPort,*pip,WSA_READMSG,hWndMain);
	//
	if(g_eCountryID == eCountryPhilippines)
		ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort,*pip1,WSA_READMSG,hWndMain);
	else
        ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort,*pip2,WSA_READMSG,hWndMain);

	if	(ret==NULL)
	{	Log("err Can't connect to MSG-Server.","-system",0);
		MessageBox(hWndMain,"Can't connect to MSG-SERVER","REBOOTING ERROR",NULL);
		return 0;
	}

	//	DB에게 자신의 데이터 초기화를 요청함.
	S_REQUEST sm; sm.wType=SSP_REQ_ZONE_INIT;
	if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
	{	Log("err REQ_ZONE_INIT DB-SEND", "-system", 0);
	}

	NumServerInGroup = 0;
	for (int j=1;j<MAX_SERVERNUMBER;j++)//MAX_SERVERNUMBER = MAX_SERVER+1
	{	if	(g_pServerList[ServerGroup][j][0]!=0)
		{	NumServerInGroup++;
		}
	}
	if	(NumServerInGroup<=0) NumServerInGroup=1;
	if	(NumServerInGroup>10) NumServerInGroup=10;

	fp = fopen("itemserver.txt","rt");
	if	(fp)	
	{	fscanf(fp,"%s %d",ItemServerAddress,&ItemServerPort);fclose(fp);

		if(g_eCountryID == eCountryTaiwan || g_eCountryID == eCountryJapan || g_eCountryID == eCountryIndonesia)
            ret = ItemServerSocket.ConnectServer(ItemServerAddress,ItemServerPort,*pip2,WSA_READITEM,hWndMain,g_nItemCashType==eItemCashTypeGeneral);
		else
			ret = ItemServerSocket.ConnectServer(ItemServerAddress,ItemServerPort,*pip1,WSA_READITEM,hWndMain,g_nItemCashType==eItemCashTypeGeneral);



		if	(ret==NULL)
		{	Log("err Can't connect to ITEM-Server.","-system",0);
			MessageBox(hWndMain,"Can't connect to ITEM-SERVER","REBOOTING ERROR",NULL);
			return 0;
		}
		ItemServerSocket.LastReceiveTime = SecCounter;
	}

	sprintf(S_Key, "IP %s Zone %d", chLocalIP1, ServerIndex+1);
	// 빌링 게임번호 6번.
	if	(!strcmp(DBServerAddress,"211.233.25.197")) {TESTSERVER = 1;} 
	if	(!strcmp(DBServerAddress,"192.168.0.20"))	{LOCALSERVER= 1;/*BILLING=0;*/} 
	fp = fopen("biserver.txt","rt");
	if	(fp)	
	{	fscanf(fp,"%s %d",BillServerAddress,&BillServerPort);fclose(fp);
		if	(BILLING>0)
		{	
			if(g_eCountryID == eCountryPhilippines || g_eCountryID == eCountryTaiwan || g_eCountryID == eCountryIndonesia)
				ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort,*pip2,WSA_READBILL,hWndMain);
			else
				ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort,*pip1,WSA_READBILL,hWndMain);

			if	(ret==NULL)
			{	Log("err Can't connect Billing server.","-system",0);
				BILLING = 0;
			}	else
			{	_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
				SendBilling2(&sm,_Msg_BillLogin);
			}
		}
	}	else
	{	BILLING=0;
	}

	// 이제 서버그룹 번호확정
    memset(FailAccount,0,sizeof(FailAccount));
	CurrentTime=timeGetTime();
	SetTimer(hWndMain, TIMER_SEC, TICKSIZE,NULL); 
	SetTimer(hWndMain, TIMER_HOUR, 3600000,NULL); 

	g_RankSys.ReadRankFile(ServerGroup);							//	주신별 랭킹정보 업로드(주신랭킹->스킬생성에서 참조)
	if(ServerIndex+1==SERVER_KATANA3) g_Yut.HT_ReadSaveMoney();		//	카타나3존일경우 윷관련 베당금정보를 얻어온다.
	if(g_eCountryID == eCountryKorea)
	{
		g_GameEvent.Initialize(ServerIndex, g_kGameEvent);									//	이벤트 업로드
	}

	if( ServerIndex+1 == SERVER_KATANA3 )
	{
		g_pRentalStore = new CRentalStore;							//	카타나3 존의 대여상점 세팅
		g_pRentalStore->HS_Init();
		g_pRentalStore->HS_SetEraseDay(g_dwRentalEraseDay);
		g_pRentalStore->HS_SetRentalTex(g_byRentalTex);
		g_pRentalStore->HS_SetRentalTexMoney(g_dwRentalTexMoney);

		TNCastle kOwner;											//	카타나3 존의 공성상황을 알린다
		g_kSiege.get_Owner( &kOwner);
		g_iCastleOwner = kOwner.kGuild.iID;

		Msg_CastleUpdate sm; ZeroMemory(&sm, sizeof(sm));
		sm.wType = _Msg_CastleUpdate;
		sm.iCastleOwner = kOwner.kGuild.iID;
		MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
	}

	Msg_TrimuritiStatus nm; nm.wType = _Msg_TrimuritiStatus;		//	주신별 동접자데이터를 요청한다.(주신변경시 참조)
	DBServerSocket.SendOneMessage((char*)&nm, sizeof(nm));

	if( SERVER_STRONGHOLD == g_iZoneID )								//	요새존일경우 요새정보를 msg를 이용해 공지한다.
	{
		CGuild GUILD;
		Msg_StrongHoldInit sh; ZeroMemory(&sh, sizeof(sh));
		sh.wType = _Msg_StrongHoldInit;
		for(int i=0; i<eStronghold_MaxCount; i++)
		{
			strncpy(sh.szGuildName[i], g_krgStronghold[i].szGuildName, SZGUILD_LENGTH);
			sh.dwMark[i] = g_krgStronghold[i].dwMark;
		}
		MSGServerSocket.SendOneMessage((char*)&sh, sizeof(sh));
	}

	//int ip = *((int*));
    ListenSocket.StartListen( hWndMain, *pip1, LocalPort , WSA_ACCEPT);
	if (g_eCountryID==eCountryChina)
	{	WhatsupSocket.StartListen( hWndMain, *pip1, WHATSUP_PORT+LocalPort, WSA_ACCEPTWHATSUP);
	}
	while	(GetMessage(&msg, NULL, 0, 0))
    {		TranslateMessage(&msg);
			DispatchMessage(&msg); 
    }
    return	(msg.wParam);  
}

LONG APIENTRY MainWndProc( HWND hWnd, UINT message, UINT wParam, LONG lParam) 
{
	switch (message)    
	{
		case WM_TIMER:
		{   if	(wParam==TIMER_SEC)  ProcessSecTimer();
			if	(wParam==TIMER_HOUR) ProcessHourTimer();
		}	break;
	  // Billing도 끊어지면 무조건 리컨넥트다.
	  case  WSA_READBILL:
	  {     if (WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {  Log("err Billing Connection lost.","-system",0);
			   BillServerSocket.CloseSocket();
			   BillCounter = 720; // 초타이머가 0.25초이므로 180초 즉 3분후에 재접속 1회 시도.
			   return TRUE;
            }
	        if (BillServerSocket.Receive()==FALSE)
			{  Log("err bill receive fail","-system",0);
			   BillServerSocket.CloseSocket();
			   BillCounter = 720; // 초타이머가 0.5초이므로 180초 즉 3분후에 재접속 1회 시도.
			   return TRUE;
			}

			//char temp[256];
			int Error=0;
			int ErrorCode=0;
            while(1)
			{  char * Msg = BillServerSocket.ReadBillMessage(0, &Error,&ErrorCode);  // 수정 ReadBillMessage(크기고정+헤더없음+엔코딩없음) 
       		   if (Msg==NULL) break;
			   if (Error==1 || Error==2)
			   {  sprintf(temp,"err readbill (%d),%d",Error,ErrorCode );
				  Log(temp,"-system",0);
				  break;
			   }  
			   ProcessBILLMessage(Msg);// , Manage.ReceiveSize);              // 작업 해당 사용자의 Billing 을 변경
			   
		    };
            break; 
	  }  break;
	  case  WSA_READITEM:
	  {     if (WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {  Log("err Item Connection lost.","-system",0);
			   ItemServerSocket.CloseSocket();
			   ItemCounter = 360; // 초타이머가 0.5초이므로 180초 즉 3분후에 재접속 1회 시도.
			   return TRUE;
            }
	        if (ItemServerSocket.Receive()==FALSE)
			{  Log("err Item receive fail","-system",0);
			   ItemServerSocket.CloseSocket();
			   ItemCounter = 360; // 초타이머가 0.5초이므로 180초 즉 3분후에 재접속 1회 시도.
			   return TRUE;
			}

			//char temp[256];
			int Error=0;
			int ErrorCode=0;
            while(1)
			{  char * Msg = ItemServerSocket.ReadCashMessage(&Error,&ErrorCode);  
       		   if (Msg==NULL) break;
			   if (Error==1 || Error==2)
			   {  sprintf(temp,"err readItem (%d),%d",Error,ErrorCode );
				  Log(temp,"-system",0);
				  break;
			   }  
			   ProcessItemMessage(Msg);
		    };
            break; 
	  }  break;
	case  WSA_READMSG:
	{
/*		if	(WSAGETSELECTEVENT(lParam) != FD_READ)
		{	Log("err MSG connection close.","-system",0);
			while(TRUE)
			{	int ret = TryEnterCriticalSection(&csConnecter);
				Sleep(10);
				Log("err msg close entercritical section fail","-system",0); // 나중에 리마크	
				continue;
			}
			MSGServerSocket.CloseSocket();
			LeaveCriticalSection (&csConnecter);
		}


		int ret = TryEnterCriticalSection(&csConnecter);
		if	(ret==NULL)
		{	Log("err msg read entercritical section fail","-system",0); // 나중에 리마크
			return FALSE; 
			// Log는 찍어줘야겠다.
			// Sleep(500);
			// continue;
		}
		if	(MSGServerSocket.Sock==NULL && MSGServerSocket.AsyncSock==NULL)
		{	LeaveCriticalSection (&csConnecter);
			return FALSE;
		}
		MSGServerSocket.Sock = MSGServerSocket.AsyncSock;

		if	(MSGServerSocket.Receive()==FALSE)
		{	Log("err wsareadmsg fail","-system",0);
			MSGServerSocket.CloseSocket();
			LeaveCriticalSection (&csConnecter);
			return TRUE;
		}
		*/
		if	(WSAGETSELECTEVENT(lParam) != FD_READ)
  	    {	Log("err MSG connection close.","-system",0);
			Sleep(200);
			MSGServerSocket.CloseSocket();
			MSGCounter = 720;
			int ret=0;
			for (int i=0;i<2;i++)
			{   int * pip = (int*)LocalIP2;
				if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 MSG Public사용
				ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort,*pip ,WSA_READMSG,hWndMain);
				if (ret!=NULL) break;
				Sleep(200);
			}	

			return TRUE;
        }
	    if	(MSGServerSocket.Receive()==FALSE)
		{	Log("err wsareadmsg fail","-system",0);
			Sleep(200);
			MSGServerSocket.CloseSocket();
			MSGCounter = 720;
			int ret=0;
			for (int i=0;i<2;i++)
			{	int * pip = (int*)LocalIP2;
				if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 MSG Public사용
				ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort,*pip,WSA_READMSG,hWndMain);
				if (ret!=NULL) break;
				Sleep(200);
			}
			return TRUE;
		}

		//char temp[256];
		int Error=0;
		int ErrorCode=0;
		while(1)
		{	char * Msg = MSGServerSocket.ReadMessage(&Error,&ErrorCode); 
      			if (Msg==NULL) break;
			////////////////////////////////
			#ifdef  _PACKET_DEBUG
			MSG_STANDARD * debug = (MSG_STANDARD*) Msg;
			if	(BASE_CheckPacket(debug))
			{	sprintf(temp,"dbg **PACKET_DEBUG** Type:%d Size:%d",debug->Type,debug->Size);
				Log(temp,"-system",0);
				break;
			}
			#endif
			///////////////////
			if	(Error==1 || Error==2)
				{	sprintf(temp,"err readmsg (%d),%d",Error,ErrorCode );
				Log(temp,"-system",0);
				break;
			}  
			ProcessMSGMessage(Msg);// , Manage.ReceiveSize);
			
	    };
		//LeaveCriticalSection (&csConnecter);
	}	break;
	// DB는 끊어지면 무조건 리컨넥트다.
	case  WSA_READDB:
	{		if	(WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {	Log("err DB connection close.","-system",0);
				Sleep(200);
				DBServerSocket.CloseSocket();

				if(g_eCountryID == eCountryChina)
				{	PostQuitMessage(NULL); return true;
				}

				int ret=0;
				for (int i=0;i<2;i++)
				{   int * pip = (int*)LocalIP2;
					if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 DBA Public사용
					ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip ,WSA_READDB,hWndMain);
					//if (ret!=NULL) 
					//{	//	DB에게 자신의 데이터 초기화를 요청함.
					//	S_REQUEST sm; sm.wType=SSP_REQ_ZONE_INIT;
					//	DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm));
					//	break;
					//}
					Sleep(200);
				}	
				if	(ret==0)
				{	Log("err reconnect DB fail.","-system",0);
					PostQuitMessage(NULL);
					return TRUE;
				}
				return TRUE;
            }
	        if	(DBServerSocket.Receive()==FALSE)
			{	Log("err wsareaddb fail","-system",0);
				Sleep(200);
				DBServerSocket.CloseSocket();

				if(g_eCountryID == eCountryChina)
				{	PostQuitMessage(NULL); return true;
				}

				int ret=0;
				for (int i=0;i<2;i++)
				{	int * pip = (int*)LocalIP2;
					if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 DBA Public사용
					ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip,WSA_READDB,hWndMain);
					//if (ret!=NULL) 
					//{	//	DB에게 자신의 데이터 초기화를 요청함.
					//	S_REQUEST sm; sm.wType=SSP_REQ_ZONE_INIT;
					//	DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm));
					//	break;
					//}
				   Sleep(200);
				}
				if (ret==0)
				{	Log("reconnect DB fail.","-system",0);
					PostQuitMessage(NULL);
					return TRUE;
				}
				return TRUE;
			}

			//char temp[256];

			int Error=0;
			int ErrorCode=0;
            while(1)
			{  char * Msg = DBServerSocket.ReadMessage(&Error,&ErrorCode); 
       		   if (Msg==NULL) break;
			   ////////////////////////////////
               #ifdef  _PACKET_DEBUG
			   MSG_STANDARD * debug = (MSG_STANDARD*) Msg;
			   if (BASE_CheckPacket(debug))
			   {   sprintf(temp,"dbg **PACKET_DEBUG** Type:%d Size:%d",debug->Type,debug->Size);
			       Log(temp,"-system",0);
				   break;
			   }
               #endif
			   ///////////////////

			   if (Error==1 || Error==2)
			   {  sprintf(temp,"err readdb (%d),%d",Error,ErrorCode );
				  Log(temp,"-system",0);
				  break;
			   }  
			   ProcessDBMessage(Msg);// , Manage.ReceiveSize);
			   
		    };
            break;
	  }  break;
      case  WSA_READ:
	  {     
		    int User = GetUserFromSocket(wParam);  
	        if	(User ==  0)
			{	closesocket(wParam);
				break;
			}

			if (pUser[User].Mode == USER_EMPTY) break;
            //

			if (WSAGETSELECTEVENT(lParam) != FD_READ  || User>=ValidUser )
			{  
//				if ( pUser[User].AccountName[0] != 0 )
//				{	sprintf(temp,"clo fd %d-%d",pUser[User].Mode,pMob[User].Mode);
//					Log(temp,pUser[User].AccountName,pUser[User].IP);
//#ifdef __EVENT_LOG_GENERATION_
//						if (pUser[User].Mode == USER_PLAY && pMob[User].MOB.szName[0] != 0 && time(0)-pUser[User].LoginTime != 0)
//						{
//							sprintf(temp,"Play,%d,%d,%d",time(0)-pUser[User].LoginTime,pMob[User].MOB.byLevel,pMob[User].MOB.snTribe);
//							EventLog(temp,pUser[User].AccountName,pMob[User].MOB.szName,pUser[User].IP);
//						}
//#endif
//				}	else
//				{
//					sprintf(temp,"clo fd %d-%d",pUser[User].Mode,pMob[User].Mode);
//					Log(temp,"noname",0); 
//				}
				CloseUser(User);
				break;
            }

	        if (pUser[User].cSock.Receive()==FALSE)
			{	Log("clo receive",pUser[User].AccountName,pUser[User].IP);
				if(pUser[User].Mode == USER_PLAY) pMob[User].m_kWaitAction.iAction = eWaitAct_ServerDown;
				CloseUser(User);
				break;
			}

			int Error=0;
			int ErrorCode=0;
            while(1)
			{  
			   char * Msg = pUser[User].cSock.ReadMessage(&Error,&ErrorCode); 
			   if (Msg==NULL) break;
			   ////////////////////////////////
               #ifdef  _PACKET_DEBUG
			   MSG_STANDARD * debug = (MSG_STANDARD*) Msg;
			   if (Msg!=NULL && BASE_CheckPacket(debug))
			   {   sprintf(temp,"dbg **PACKET_DEBUG** Type:%d Size:%d",debug->Type,debug->Size);
			       Log(temp,"-system",0);
			   }
               #endif
			   ///////////////////
			   if (Error==1 || Error==2)
			   {  pUser[User].AccountName[ACCOUNTNAME_LENGTH-1]=0;
			      pUser[User].AccountName[ACCOUNTNAME_LENGTH-2]=0;
				  sprintf(temp,"clo err read (%d),%d",Error,ErrorCode );
				  Log(temp,pUser[User].AccountName,pUser[User].IP);
				  CloseUser(User);
			      break;
			   } 
			   ProcessClientMessage(User,Msg);// , Manage.ReceiveSize);
		    };
            break;
	  }
     break;     
     case WSA_ACCEPT:
     if (WSAGETSELECTERROR( lParam ) == 0) 
	 { 

		int User = GetEmptyUser();         //           CLIENT의 최초 접속
		if  (User==0 || User>=ValidUser || pUser[User].cSock.pRecvBuffer==NULL ||  pUser[User].cSock.pSendBuffer==NULL )
		{   Log("clo err accept fail - no empty","-system",0);
			TempUser.AcceptUser(ListenSocket.Sock);
			TempUser.CloseUser();
			break;
		}

        int ret = pUser[User].AcceptUser(ListenSocket.Sock);
		if	(ret==FALSE) 
		{	Log("dbg WSA_ACCEPT fail","-system",0);
			return TRUE;
		}

		//if(ServerIndex+1 == SERVER_KRUMA_HIGH || ServerIndex+1 == SERVER_CHATURANGKA)
		//{
		//	for(int i=0; i<MAX_USER; i++)		//	현재 동일IP에서 접속중인 유저가 있을경우(쌍방 접속해지시킨다)
		//	{	
		//		if(pUser[i].Mode == USER_EMPTY) continue;
		//		if(pUser[i].IP == pUser[User].IP && i != User)
		//		{	Log("err accept fail - same IP","-system",pUser[i].IP);
		//			Log("err accept fail - same IP","-system",pUser[User].IP);
		//			pUser[i].CloseUser();
		//			pUser[User].CloseUser();
		//			break;
		//		}
		//	}
		//}

		if  (ServerDown!=-1000)
		{	SendClientMessage(User,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
	        CloseUser(User);  
			return TRUE;
		}
		pUser[User].LastReceiveTime = SecCounter;
		sprintf(temp,"New Connection user:%d",User);
		Log(temp,"-system",pUser[User].IP);
     }  else 
 	 {  Log("err - accept - wsagetselecterror","-system",0);
     }
     break;
	case WSA_ACCEPTWHATSUP:
		if (WSAGETSELECTERROR( lParam ) == 0)
		{
			CUser WhatsupUser;
			WhatsupUser.AcceptUser(WhatsupSocket.Sock);
			WhatsupUser.CloseUser();
			break;
		}
	   break;
   case WM_PAINT:
	    g_nCurrentTextY = 10;
	    PAINTSTRUCT ps;
		BeginPaint(hWnd,&ps);
		DrawInformations(ps.hdc);
		EndPaint(hWnd,&ps);
		break; 
   case WM_CLOSE:
   {
		if	(fLogFile)	fclose(fLogFile);
		if	(g_fpEvent) fclose(g_fpEvent);
		if	(hFont)		{DeleteObject(hFont);hFont=NULL;}

		//	Billing Server에 존다운을 알린다.
		_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
		SendBilling2(&sm,4);
		ServerDown=1;

		CloseServer();

//		DefWindowProc(hWnd,message,wParam,lParam);
   }    break;
   case WM_DESTROY:
        WSACleanup();
        PostQuitMessage(0);
        break;
   default:                      
        return (DefWindowProc(hWnd, message, wParam, lParam));
		break;
   }
   return (0);
}

void CloseServer()
{

	if(g_eCountryID == eCountryKorea)
	{
		g_GameEvent.CloseEvent();
	}

	if(eZoneType_Guild == g_iZoneType)
	{
		char szFileName[512] = {0,};
		char szInBuf[20] = {0,};
		_itoa(g_dwArenaMoney, szInBuf, 10);
		sprintf(szFileName, ".\\Data\\Zone%d.ini", g_iZoneID);
		BOOL bRet = WritePrivateProfileString( _T("Arena"), _T("Money"), _T(szInBuf), szFileName );
	}

	if(g_iZoneID == SERVER_KATANA3)
	{
		char szFileName[512] = {0,};
		char szInBuf[20] = {0,};

		sprintf(szFileName, ".\\Data\\Zone%d.ini", g_iZoneID);
		_itoa(g_byCastleSalesRate, szInBuf, 10);
		BOOL bRet = WritePrivateProfileString( _T("Castle"), _T("SalesRate"), _T(szInBuf), szFileName );	

		_itoa(g_dwCastleSalesMoney, szInBuf, 10);
		bRet = WritePrivateProfileString( _T("Castle"), _T("SalesMoney"), _T(szInBuf), szFileName );	

		if(g_pRentalStore)
            delete g_pRentalStore;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//                    클라이언트  메시지 처리기

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void ProcessClientMessage(int conn,char*msg)
{ 
	PHEADER header = (PHEADER)msg;

	if	(ServerDown>=120) return;

	//////////////// Speedhack, Speed hack check ////////////////////////////
	if ( pUser[conn].TickDiff != 0 )
	{
		if ( (int)( header->dwClientTick - CurrentTime ) > (int)(pUser[conn].TickDiff + 20000) )	   //	servertick보다 10sec빠른 패킷이 올경우
		{	if(pUser[conn].m_LastTime>=30000)
			{	pUser[conn].m_LastTime = 0;
				pUser[conn].TickDiff = header->dwClientTick - CurrentTime;
			} else
			{	AddCrackError(conn, 5, CRACK_SPEED_HACK3); return;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////


	//if	(!(std->Type&FLAG_CLIENT2GAME) )
	//{	sprintf(temp,"Unknown Packet Type:%d ID:%d Size:%d KeyWord:%d",std->Type,std->ID,std->Size,std->KeyWord);
	//	Log(temp,"-system",0);
	//	return;
	//}

	if	(conn>0 && conn<MAX_USER)
	{	pUser[conn].LastReceiveTime = SecCounter;// 0.5초.
	}

	WORD wType = 0;
	if(pUser[conn].byTradeMode==1)
	{	wType = header->wType;
		if(wType!=_MSG_REQMobByID && wType!=_MSG_GMMode && wType!=CSP_REQ_APPEAL_CHAT && wType!=_MSG_Chat && wType!=_MSG_Broadcast &&
			wType!=CSP_REQ_WHISPER_CHAT && wType!=CSP_REQ_CHAT && wType!=_MSG_MobStore_Buy && wType!=_MSG_MobStore && wType!=_Msg_Who) return;
	}

	switch(header->wType)
	{
	case _Msg_Who:
		{	Msg_Who * m = (Msg_Who*)msg;
			
			if ( memcmp( g_szPCSkillCheckSum, m->pszPCSkillCheckSum, sizeof(g_szPCSkillCheckSum) ) != 0 )
			{	
				if(g_eCountryID != eCountryKorea) 
				{
					// TantraParam 수정으로 인식
					CloseUser(conn);
					sprintf(temp, "clo hack type:TantraParam char:%s", pMob[conn].MOB.szName );
					Log(temp,pUser[conn].AccountName, pUser[conn].IP);
					break;	
				}
			}

			bool bRet = RecvWhoMessage(conn, (char*)&(m->pszPassword));
			if(!bRet)							//	bot프로그램으로 인식
			{
				if(g_eCountryID == eCountryKorea)	//	
				{
					CloseUser(conn);
				}
				else if(g_eCountryID == eCountryChina)
				{
					pMob[conn].MOB.byGMStatus |= 0x01;
					CloseUser(conn);
				}
				else if(g_eCountryID == eCountryJapan)
				{
					pMob[conn].MOB.byGMStatus |= 0x01;

					CloseUser(conn);
				}
				else
				{
				}

				sprintf(temp, "clo hack type:bot - User:%s char:%s bot message is not correct.", pUser[conn].AccountName, pMob[conn].MOB.szName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			}
		}	break;
	case _Msg_MyRentalItemList:					//	자신의 위탁상점 아이텔리스트를 요청한다.
		{	Msg_MyRentalItemList * m = (Msg_MyRentalItemList*)msg;
			
			g_pRentalStore->HS_GetItemList(pMob[conn].MOB.szName, m->stItem, m->wIndex);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemList:					//	특정 위탁상점의 아이템리스트를 요청한다.
		{	Msg_RentalItemList * m = (Msg_RentalItemList*)msg;
			
			g_pRentalStore->HS_GetItemList(m->dwStoreIndex, m->stItem);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemAdd:					//	위탁상점에 자신의 아이템을 등록한다.
		{	Msg_RentalItemAdd * m = (Msg_RentalItemAdd*)msg;
			
			if(m->dwIndex<0 || m->dwIndex>=pMob[conn].byMaxInven) break;
			DWORD dwMoney = m->dwMoney; 
			bool bRet = g_pRentalStore->HS_bAddItem(pMob[conn].MOB.szName, m->dwStoreIndex, pMob[conn].MOB.Inven[m->dwIndex], pMob[conn].MOB.nRupiah, &dwMoney, m->byHour);
			if(bRet) 
			{	//	아이템 맵추가 성공시
				sprintf(temp, "ren Char:%s set item:%d to rental_store at price:%d by cost:%d", 
					pMob[conn].MOB.szName, pMob[conn].MOB.Inven[m->dwIndex].snIndex+HT_PARAMTYPE_ITEM_START-1, m->dwMoney, dwMoney);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);

				m->byResult = 0;
				ZeroMemory(&pMob[conn].MOB.Inven[m->dwIndex], sizeof(pMob[conn].MOB.Inven[m->dwIndex]));

				pMob[conn].DecGold(dwMoney);
				m->dwMoney = pMob[conn].MOB.nRupiah;
			}	//	아이템 맵추가 실패시
			else
				m->byResult = 1;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemCancel:					//	위탁상점내에 자신이 올려놓은 아이템을 취소요청한다.
		{	Msg_RentalItemCancel * m = (Msg_RentalItemCancel*)msg;
			
			STRUCT_ITEM stItem;
			DWORD	dwMoney = 0;
			bool bRet = true;
			m->byResult = 0;
			int iIndex = (m->dwStoreIndex*MAX_RENTALSTOREITEM)+m->dwIndex;
			int iEmpty = GetEmptyInven(conn);
			if(iEmpty<0 || iEmpty>=pMob[conn].byMaxInven) bRet = false;

			bRet &= g_pRentalStore->HS_bDeleteItem(pMob[conn].MOB.szName, iIndex, &stItem);
			if(bRet)
			{
				pMob[conn].MOB.Inven[iEmpty] = stItem;
				m->byResult = 0;

				S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;		//	위탁취소로 인한 인벤내 아이템 생성
				sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
				sm.byIndex=iEmpty; sm.sitem=pMob[conn].MOB.Inven[iEmpty];
				pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm));
			}
			else
				m->byResult = 1;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalGetItem:					//	재고아이템을 얻어온다.
		{	Msg_RentalGetItem * m = (Msg_RentalGetItem*)msg;
			
			STRUCT_ITEM stItem;
			int iCount = g_pRentalStore->HS_iGetStockItemCount(pMob[conn].MOB.szName);
			int iEmpty = GetEmptyInvenCount(conn);
			int iIndex = 0;
			if(iCount>iEmpty) iCount = iEmpty;	//	비어 있는 만큼의 아이템만을 받아온다.
			for(int i=0; i<iCount; i++)
			{
				if(!g_pRentalStore->HS_bGetStockItem(pMob[conn].MOB.szName, &stItem)) continue;

				iIndex = GetEmptyInven(conn);
				if(iIndex<0 || iIndex>=pMob[conn].byMaxInven) continue;

				pMob[conn].MOB.Inven[iIndex] = stItem;

				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=iIndex; nm.sitem=stItem;
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));

				sprintf(temp, "ren Char:%s get stock_item:%d in Inven", pMob[conn].MOB.szName, stItem.snIndex+HT_PARAMTYPE_ITEM_START-1);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}
			if(iCount>0 && iEmpty>0) pUser[conn].cSock.SendMessage();
		}	break;
	case _Msg_RentalGetMoney:					//	재고루피아를 얻어온다.
		{	Msg_RentalGetMoney * m = (Msg_RentalGetMoney*)msg;
			
			DWORD dwMoney = 0;
			if(m->byType == 1)
			{	if(!g_pRentalStore->HS_bGetMoney(pMob[conn].MOB.szName, &dwMoney)) return; 
				if(dwMoney>=MAX_INT) return;
				int iHap = (int)dwMoney + pMob[conn].MOB.nRupiah;
				if(iHap<0 || iHap>MAX_INT) return;

				if(!g_pRentalStore->HS_bGetMoney(pMob[conn].MOB.szName, &dwMoney, false)) return;
				pMob[conn].IncGold(dwMoney);

				sprintf(temp, "ren Char:%s get stock_money:%d -> TotInven_money:%d", pMob[conn].MOB.szName, dwMoney, pMob[conn].MOB.nRupiah);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}
			else
				if(!g_pRentalStore->HS_bGetMoney(pMob[conn].MOB.szName, &dwMoney)) return; 

			m->dwMoney = dwMoney;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_SetRentalTex:
		{	Msg_SetRentalTex * m = (Msg_SetRentalTex*)msg;

			if(m->byType == eSearch)
			{
				m->byTex = g_pRentalStore->HS_GetRentalTex();
			}
			else if(m->byType == eRun)
			{
				TNCastle kOwner;
				g_kSiege.get_Owner( &kOwner);
				if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	공성의 소유길드가 아니면 사용안됨
				if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	마하라자가 아니면 사용안됨
				if(m->byTex>7) break;

				g_pRentalStore->HS_SetRentalTex(m->byTex);
			}
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	//case _Msg_RentalGetTexMoney:
	//	{	Msg_RentalGetTexMoney * m = (Msg_RentalGetTexMoney*)msg;
	//		
	//		DWORD dwMoney = 0;
	//		TNCastle kOwner;
	//		g_kSiege.get_Owner( &kOwner);
	//		if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	공성의 소유길드가 아니면 사용안됨
	//		if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	마하라자가 아니면 사용안됨

	//		if(m->byType == 1)
	//		{
	//			g_pRentalStore->HS_GetTexMoney(&dwMoney, false);
	//			pMob[conn].IncGold(dwMoney);
	//		}
	//		else
	//			g_pRentalStore->HS_GetTexMoney(&dwMoney); 

	//		m->dwMoney = pMob[conn].MOB.nRupiah;
	//		pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
	//	}	break;
	case _Msg_RentalStoreClose:
		{	Msg_RentalStoreClose * m = (Msg_RentalStoreClose*)msg;

			bool bRet = true;
			DWORD dwMoney = 0;
			TNCastle kOwner;
			//STRUCT_RENTALITEM	stItem[MAX_USERRENTALITEM];
			
			g_kSiege.get_Owner( &kOwner);
			if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) bRet = false;	//	공성의 소유길드가 아니면 사용안됨
			if(pUser[conn].nGuildLevel != eGuildMaster) bRet = false;		//	마하라자가 아니면 사용안됨

			if(bRet)
			{
				g_pRentalStore->HS_StockItem(m->dwStore);
				m->byResult = 0;
			}
			else
				m->byResult = 0;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemBuy:
		{	Msg_RentalItemBuy * m = (Msg_RentalItemBuy*)msg;

			bool bRet = true;
			//STRUCT_RENTALITEM stItem;
			int iStoreItemIndex = m->dwStoreIndex * MAX_RENTALSTOREITEM + m->dwIndex;

			int iInvenIndex = GetEmptyInven(conn);
			if(iInvenIndex<0 || iInvenIndex>=MAX_INVEN) bRet = false;

			int iPrice = 0;
			g_pRentalStore->HS_GetShopItemPrice(iStoreItemIndex, &iPrice);
			if( pMob[conn].MOB.nRupiah < iPrice) 
				bRet = false;
			else
                bRet &= g_pRentalStore->HS_bBuyItem(iStoreItemIndex, m->stItem);

			if(bRet)
			{
				m->byResult = 0;
				pMob[conn].MOB.Inven[iInvenIndex] = m->stItem;
				pMob[conn].DecGold(iPrice);
                
				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=iInvenIndex; nm.sitem=pMob[conn].MOB.Inven[iInvenIndex];
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));

				sprintf(temp, "ren Char:%s buy rentalstore_item:%d at price:%d -> TotInven_money:%d", 
					pMob[conn].MOB.szName, nm.sitem.snIndex+HT_PARAMTYPE_ITEM_START-1, iPrice, pMob[conn].MOB.nRupiah);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}
			else
				m->byResult = 1;

			m->dwMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalStockItemList:
		{	Msg_RentalStockItemList * m = (Msg_RentalStockItemList*)msg;
			
			int iCount = 0;
			while(1)
			{
				ZeroMemory(m->stItem, sizeof(m->stItem));
				g_pRentalStore->HS_GetStockItemList(pMob[conn].MOB.szName, iCount, m->stItem);
				pUser[conn].cSock.AddMessage((char*)m, sizeof(*m));
				if(m->stItem[29].szName[0] == 0) break;
				iCount += 30;
			}
			pUser[conn].cSock.SendMessage();
		}	break;
	case _Msg_YutBet:
		{	Msg_YutBet * m = (Msg_YutBet*)msg;

			BOOL bRet = false;
			while(1)
			{
				if(!g_Yut.HT_bIsBetOn()) break;
				if(m->byPosition<0 || m->byPosition>=MAX_POSITION) break;
				if(pMob[conn].MOB.nRupiah < m->iBetMoney) break;
				if(m->iBetMoney<0 || m->iBetMoney>MAX_INT) break;
				bRet = true;
				break;
			}

			if(!bRet)	//	오류가 있는 패킷의 경우
				m->byResult = S_FALSE;
			else
			{	m->byResult = S_OK;
				pMob[conn].DecGold(m->iBetMoney);
				g_Yut.HT_wUserBet(pMob[conn].MOB.szName, (WORD)(m->byPosition), m->iBetMoney);
			}

			//g_Yut.HT_WriteLog(pMob[conn].MOB.szName);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_YutStatus:
		{	Msg_YutStatus * m = (Msg_YutStatus*)msg;

			//g_Yut.HT_WriteLog();
			g_Yut.HT_GetPositionBetMoney(m->dwPositionMoney);
			//g_Yut.HT_WriteLog();
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_YutMyMoney:
		{	Msg_YutMyMoney * m = (Msg_YutMyMoney*)msg;

			//g_Yut.HT_WriteLog(pMob[conn].MOB.szName);
			g_Yut.HT_GetPositionBetMoney(pMob[conn].MOB.szName, m->dwPositionMoney);
			//g_Yut.HT_WriteLog(pMob[conn].MOB.szName);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_YutGetMoney:
		{	Msg_YutGetMoney * m = (Msg_YutGetMoney*) msg;

			DWORD dwMoney = g_Yut.HT_GetMoney(pMob[conn].MOB.szName);
			if(dwMoney<=0)
			{	m->byResult = REPLY_YUTMONEY_NOHAVEMONEY; 
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); break;
			}
			
			int iMoney = dwMoney+pMob[conn].MOB.nRupiah;
			if(iMoney<0 || iMoney>MAX_INT) 
			{	m->byResult = REPLY_YUTMONEY_FAIL; 
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); break;
			}

			pMob[conn].IncGold((int)dwMoney);
			m->iMoney = pMob[conn].MOB.nRupiah;

			sprintf(temp, "dbg Char:%s Yut_GetMoney:%d Inven_Money:%d", pMob[conn].MOB.szName, dwMoney, pMob[conn].MOB.nRupiah);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			g_Yut.HT_SetYutMoney(pMob[conn].MOB.szName, 0);
			m->byResult = REPLY_YUTMONEY_SUCCESS;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_SetSalesRate:
		{	Msg_SetSalesRate *m = (Msg_SetSalesRate*) msg;

			if(ServerIndex+1 != SERVER_KATANA3) break;

			if(m->byType==eSearch)						//	세율문의
			{
				m->byRate = g_byCastleSalesRate;
				m->dwMoney = g_dwCastleSalesMoney;
			}
			else if(m->byType==eRun)					//	세율설정
			{
				TNCastle kOwner;
				g_kSiege.get_Owner( &kOwner);
				if(pMob[conn].MOB.nGuildID != kOwner.kGuild.iID ) break;	//	해당길드가 아니면 이용불가
				if(pUser[conn].nGuildLevel != eGuildMaster) break;			//	마하라자가 아니면 사용안됨

				if(m->byRate>100) m->byRate = 100;
				g_byCastleSalesRate = m->byRate;
				m->dwMoney = g_dwCastleSalesMoney;
				m->byType = eSearch;
				//Msg_UpdateSalesRate sm; sm.wType = _Msg_UpdateSalesRate;
				//sm.wPDULength = sizeof(Msg_UpdateSalesRate)-sizeof(HEADER);
				//sm.byRate = g_dwCastleSalesMoney;
				SendToAll((MSG_STANDARD*)m);
				m->byType=eRun;
			}
			else
				return;

			//	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	위에서 sendtoall로 이미 전송함.
		}	break;
	case _Msg_GetMoney:
		{	Msg_GetMoney *m = (Msg_GetMoney*) msg;

			m->byResult = S_FALSE;
			int nType = m->nType;

			if(ServerIndex+1 != SERVER_KATANA3)					//	세금 조회 및 찾기는 현재 카타나3존에서만 실행된다.
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}

			TNCastle kOwner;
			g_kSiege.get_Owner( &kOwner);
			if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID)		//	공성의 소유길드가 아니면 사용안됨
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}
			if(pUser[conn].nGuildLevel != eGuildMaster)			//	마하라자가 아니면 사용안됨
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}

			switch(nType)
			{
			case eGetMoneyYut:
				{
					if(ServerIndex+1 != SERVER_KATANA3) break;

					TNCastle kOwner;
					g_kSiege.get_Owner( &kOwner);
					if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	공성의 소유길드가 아니면 사용안됨
					if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	마하라자가 아니면 사용안됨

					m->byResult = S_OK;
					int nGold = (int)g_Yut.GetOwnerMoney();
					
					if(m->byAction == eRun)
					{
						__int64 iHap = nGold + pMob[conn].MOB.nRupiah;
						if(iHap>MAX_INT)
						{	m->byResult = S_FALSE;
							pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
							return; 
						}

						pMob[conn].IncGold((int)nGold);
						g_Yut.SetOwnerMoney(0);
						m->dwMoney = pMob[conn].MOB.nRupiah;
					}
					else 
						m->dwMoney = (DWORD)nGold;
				}	break;
			case eGetMoneySale:								//	Msg_SetSalesRate, Msg_RentalGetTexMoney 등등으로 구분하고 있다
				{												//	차후 통합해두 상관없을 부분인듯.
					int nMoney = (int)g_dwCastleSalesMoney;

					if(m->byAction == eRun)
					{
						__int64 iHap = nMoney + pMob[conn].MOB.nRupiah;
						if(iHap>MAX_INT)
						{	m->byResult = S_FALSE;
							pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
							return; 
						}

						pMob[conn].IncGold(nMoney);
						g_dwCastleSalesMoney = 0;
						m->dwMoney = pMob[conn].MOB.nRupiah;
					}
					else 
						m->dwMoney = nMoney;
				}	break;
			case eGetMoneyRentalStore:
				{
					DWORD dwMoney = 0;
					TNCastle kOwner;
					g_kSiege.get_Owner( &kOwner);
					if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	공성의 소유길드가 아니면 사용안됨
					if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	마하라자가 아니면 사용안됨

					if(m->byAction == eRun)
					{
						g_pRentalStore->HS_GetTexMoney(&dwMoney);
						__int64 iHap = dwMoney + pMob[conn].MOB.nRupiah;
						if(iHap>MAX_INT)
						{	m->byResult = S_FALSE;
							pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
							return; 
						}
						g_pRentalStore->HS_GetTexMoney(&dwMoney, false);
						pMob[conn].IncGold(dwMoney);
						m->dwMoney = pMob[conn].MOB.nRupiah;
					}
					else
					{
						g_pRentalStore->HS_GetTexMoney(&dwMoney);
						m->dwMoney = dwMoney;
					}
				}	break;
			default:
				{
				}	break;
			}

			m->byResult = S_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

		}	break;
	case _Msg_Echo:
		{	Msg_Echo *m = (Msg_Echo*) msg;

			int nID = m->iKeyID;
			if(nID>0 && nID<MAX_USER)
			{
				m->iKeyID = conn;
				pUser[nID].cSock.SendOneMessage((char*)m, sizeof(*m));
			}
		}	break;
	case CSP_REQ_CHAR_LIST:
		{
			S_SCP_RESP_CHAR_LIST sData;
			sData.wType = SCP_RESP_CHAR_LIST;
			memcpy(sData.sData,pUser[conn].sData,sizeof(pUser[conn].sData));

			sprintf(temp,"dbg charlist Char1:%s zone:%d Char2:%s zone:%d Char3:%s zone:%d",
				sData.sData[0].szCharName, sData.sData[0].LastZone, 
				sData.sData[1].szCharName, sData.sData[1].LastZone,
				sData.sData[2].szCharName, sData.sData[2].LastZone);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			pUser[conn].cSock.SendOneMessage((char*)&sData,sizeof(sData));
		}	break;
	case CSP_REQ_CHAR_CREATE:
		{   S_CSP_REQ_CHAR_CREATE *m = (S_CSP_REQ_CHAR_CREATE*) msg;
			m->szCharName[SZNAME_LENGTH-1]=0;m->szCharName[SZNAME_LENGTH-2]=0;

			if	(pUser[conn].Mode!=USER_SELCHAR)
			{	SendClientResult(conn,m->wType, 7);
				sprintf(temp,"err crechar not user_selchar %d %d",conn,pUser[conn].Mode);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				return;
			}  
			if ( g_eCountryID == eCountryPhilippines )
			{	int l = strlen(m->szCharName);
				if  (l<4 || l>=SZNAME_LENGTH)  return;        // 4자 미만 또는 26자 초과시 X
				for (int j=0; j<l; j++)
				{	 char x = m->szCharName[j];
					//  숫자,알파벳만 통과
	 				if  ((x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x>='0'&&x<='9')) continue;
					SendClientResult(conn,m->wType,0x06);
					pUser[conn].cSock.SendMessage();
					return;
				}
			}
			else
			{	if	(!BASE_CheckValidString(m->szCharName)) 
				{	SendClientResult(conn,m->wType,0x06);
					pUser[conn].cSock.SendMessage();
					break;
				}
			}

			if(!NameFilter(m->szCharName) || !ChatFilter(m->szCharName))
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			if ( m->snTribe == 0 || m->byTrimuriti == 10 )
			{	SendClientResult(conn,m->wType,0x06);
				pUser[conn].cSock.SendMessage();
				break;
			}

			S_SSP_REQ_CHAR_CREATE	sData;
			sData.wType = SSP_REQ_CHAR_CREATE;
			sData.wPDULength = sizeof(S_SSP_REQ_CHAR_CREATE)-sizeof(HEADER);
			sData.nID = conn;
			strcpy(sData.szCharName, m->szCharName);
			sData.byTrimuriti = m->byTrimuriti;
			sData.snTribe = m->snTribe;
			sData.byFaceType = m->byFaceType;
			sData.byHeadType = m->byHeadType;
			sData.byChakraMuscle = m->byChakraMuscle;
			sData.byChakraNerve = m->byChakraNerve;
			sData.byChakraHeart = m->byChakraHeart;
			sData.byChakraSoul = m->byChakraSoul;

			pUser[conn].Mode = USER_CREWAIT;     // LOGIN과 캐랙터 만들기는 동일.<변경> 따로 처리.
			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_CHAR_CREATE)))
			{	sprintf(temp, "err CreateUser DB-SEND %d", pUser[conn].Mode);
				Log(temp, pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	//////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_CHAR_REMOVE:
		{	S_CSP_REQ_CHAR_REMOVE *m = (S_CSP_REQ_CHAR_REMOVE *) msg;
			if	(pUser[conn].Mode!=USER_SELCHAR)
			{	SendClientResult(conn,m->wType, 7);
				sprintf(temp,"err delchar not user_selchar %d %d",conn,pUser[conn].Mode);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				return;
			}   

			if(g_eCountryID == eCountryChina)
			{	if(pUser[conn].ssn2 != m->ssn2 )
				{	SendClientResult(conn,m->wType, 7);
					sprintf(temp,"err delchar ssn not match",conn,pUser[conn].Mode);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); return;
				}
			}	else
			{	if(pUser[conn].ssn1!= m->ssn1 || pUser[conn].ssn2 != m->ssn2 )
				{	SendClientResult(conn,m->wType, 7);
					sprintf(temp,"err delchar ssn not match",conn,pUser[conn].Mode);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); return;
				}
			}

			S_SSP_REQ_CHAR_REMOVE sData;
			sData.wType = SSP_REQ_CHAR_REMOVE;
			sData.wPDULength = sizeof(S_SSP_REQ_CHAR_REMOVE)-sizeof(HEADER);
			sData.nID = conn;
			strcpy(sData.szCharName, m->szCharName);
			//strcpy(sData.szJuminI, m->szJumin);

			pUser[conn].Mode = USER_CREWAIT;     // 만들기 삭제는 모두 CREWAIT를 쓴다.
			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_CHAR_REMOVE)))
			{	Log("err delchar DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_MOVE_ZONE_SERVER:   // 
		{	S_CSP_REQ_MOVE_ZONE_SERVER* pData = (S_CSP_REQ_MOVE_ZONE_SERVER*) msg;

			//////////// Speedhack, Speed hack - Initialize /////////////////////////////////
			pUser[conn].TickDiff = pData->dwClientTick - CurrentTime;
			/////////////////////////////////////////////////////////////////////////////////

			if(g_eCountryID!=eCountryKorea || ServerGroup>=1)
			{
				MSG_STANDARD sm; sm.wType = _Msg_VersionCheck;
				if(g_snVersion[0]!=pData->snVersion[0] || g_snVersion[1]!=pData->snVersion[1] || g_snVersion[2]!=pData->snVersion[2] || g_snVersion[3]!=pData->snVersion[3])
				{
					sm.nID = 1; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
					CloseUser(conn);

					sprintf(temp,"clo err Dismatch Client-Server Version!! account:%s char:%s",pUser[conn].AccountName, pMob[conn].MOB.szName);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					return;
				}
				else
				{	sm.nID = 0; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
				}
			}


			//sprintf(temp,"dbg account:%s request move zone",pUser[conn].AccountName);
			//Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			if	(pUser[conn].Mode!=USER_ACCEPT)
			{	SendClientMessage(conn,g_pMessageStringTable[_Move_zone_Wait]);
				CrackLog(conn,"accountlogin");
				pUser[conn].cSock.SendMessage();
				sprintf(temp,"clo dbg account:%s request move zone fail1",pUser[conn].AccountName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout;
				CloseUser(conn);
				return;
			}
			pData->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			pData->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			pData->AccountPass[ACCOUNTPASS_LENGTH-1]=0;
            pData->szCharName[SZNAME_LENGTH-1]=0;

			S_SSP_REQ_MOVE_ZONE_SERVER sData;
			sData.wType = SSP_REQ_MOVE_ZONE_SERVER;
			sData.wPDULength = sizeof(S_SSP_REQ_MOVE_ZONE_SERVER)- sizeof(HEADER);
			strncpy(pUser[conn].AccountName,pData->AccountName,ACCOUNTNAME_LENGTH);
			strupr(pUser[conn].AccountName);
			strncpy(sData.AccountName,pUser[conn].AccountName,ACCOUNTNAME_LENGTH);
			strncpy(sData.AccountPass,pData->AccountPass,ACCOUNTPASS_LENGTH);
			strncpy(sData.szCharName, pData->szCharName,SZNAME_LENGTH);
			sData.nID = conn;
			int num = CheckFailAccount(sData.AccountName);
			if	(num>=3)
			{	SendClientResult(conn, pData->wType, 16);	//	16 에러코드
				pUser[conn].cSock.SendMessage();
				sprintf(temp,"dbg account:%s request move zone fail2",pUser[conn].AccountName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				return;
			}

			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_MOVE_ZONE_SERVER)))
			{	Log("err movezone DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
			pUser[conn].Mode = USER_LOGIN; // 이전은 USER_ACCEPT였다.
			pMob[conn].Mode   = MOB_EMPTY;
			pUser[conn].LoginTime = time(0);
			if(pData->dwEvent > 0) pUser[conn].m_dwEvent = pData->dwEvent;
#ifdef __EVENT_LOG_GENERATION_
			if ( pData->szCharName[0] != 0 )
			{
				sprintf(temp,"Login,0,%d,%d",pMob[conn].MOB.byLevel,pMob[conn].MOB.snTribe);
				EventLog(temp,pUser[conn].AccountName,pMob[conn].MOB.szName,pUser[conn].IP);
			}
#endif
		}	break;
	case CSP_REQ_CHAR_SELECT:
		{
			S_CSP_REQ_CHAR_SELECT * m = (S_CSP_REQ_CHAR_SELECT *) msg;

			m->szCharName[SZNAME_LENGTH-1] = 0; m->szCharName[SZNAME_LENGTH-2] = 0;
			if(m->szCharName[0]==0) break;

			S_SSP_REQ_CHAR_SELECT sData;
			sData.wType = SSP_REQ_CHAR_SELECT;
			sData.wPDULength = sizeof(S_SSP_REQ_CHAR_SELECT)-sizeof(HEADER);
			strncpy(sData.szCharName, m->szCharName, SZNAME_LENGTH);
			sData.byConnectType = m->byConnType;

			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(sData)))
			{	Log("err charselect DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		} break;
	case _MSG_Status:
		{	MSG_Status * m = (MSG_Status *) msg;
			m->nID = conn;
			pMob[conn].MOB.byStatus = m->byStatus;
			if(!DBServerSocket.SendOneMessage((char*)m,sizeof(*m)))
			{	Log("err charstatus DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_CHAR_INIT:
		{	S_CSP_REQ_CHAR_INIT * m = (S_CSP_REQ_CHAR_INIT *) msg;

			BYTE byConnectType = m->byConnType;
			if(byConnectType<CONNECT_TYPE_FIRST || byConnectType>CONNECT_TYPE_GMRECALL)
			{	CrackLog(conn," CSP_REQ_CHAR_INIT:Invalid Connect Type"); CloseUser(conn); return;
			}

			if(pUser[conn].Mode!=USER_SELCHAR) 
			{	sprintf(temp, "clo err initchar1 - not USER_SELCHAR mode:%d", pUser[conn].Mode);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout;
				CloseUser(conn);
				return;
			}

			S_SSP_REQ_CHAR_INIT sData;
			sData.wType = SSP_REQ_CHAR_INIT;
			sData.wPDULength = sizeof(S_SSP_REQ_CHAR_INIT)-sizeof(HEADER);
			sData.nID = conn;
			sData.byConnPos = m->byConnPos;
			sData.byConnType= byConnectType;
			sData.wPortalID = m->wPortalID;
			strncpy(sData.szCharName, m->szCharName, SZNAME_LENGTH);
			strncpy(sData.szTargetName, m->szTargetName, SZNAME_LENGTH);
			int nSlot = -1;
			for	(int i=0;i<MOB_PER_ACCOUNT;i++)
			{	if	(!strcmp(pUser[conn].sData[i].szCharName,m->szCharName)) {nSlot=i;break;}
			}
			if	(nSlot==-1)
			{	sprintf(temp,"err Char Init fail - slot!!");
				Log(temp,m->szCharName,pUser[conn].IP);

				break;
			}

			sData.bySlot	= nSlot;

			pUser[conn].Mode	= USER_CHARWAIT;     // LOGIN과 캐랙터 만들기는 동일.
			pMob[conn].Mode		= MOB_USER;
			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_CHAR_INIT)))
			{	Log("err initchar DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}

			/*
			MSG_CharacterLogin *m = (MSG_CharacterLogin *) msg;
			if	(m->Slot<0||m->Slot>=MOB_PER_ACCOUNT)
			{	SendClientMessage(conn,g_pMessageStringTable[_NN_SelectCharacter]);
				return;
			}
			// 무료 경험치는 아래와 같다.
			if	( pUser[conn].SelChar.Score[m->Slot].Level>=FREEEXP && pUser[conn].SelChar.Score[m->Slot].Level<999 && BILLING == 2)  //2:빌링 강제 집행.
			{	if	(pUser[conn].Billing<=1) 
				{	
					if	(pUser[conn].ReqBillSec!=0 && pUser[conn].ReqBillSec<SecCounter-10)
					{	
						pUser[conn].ReqBillSec=0;
                        pUser[conn].Billing=5; 
					}	else
					{
						SendClientMessage(conn,g_pMessageStringTable[_NN_Wait_Checking_Billing]);	// 게임->빌링의 인증요청 패킷이 씹혔을 수도 있으니 재요청
						SendBilling(conn,pUser[conn].AccountName,1,1);								// 마지막파라메타, 기존세션으로 인증 요청
					}
					// 
					return;
				}
                if	(pUser[conn].Billing==3) 
				{	sprintf(temp,g_pMessageStringTable[_DN_Not_Allowed_Account],FREEEXP);
					SendClientMessage(conn,temp);
					SendClientSignalParm(conn,0,_MSG_BillingPage,0);return;
				}//여기서 홈페이지의 결제 페이지?
				if	(pUser[conn].Billing==4) { SendClientMessage(conn,g_pMessageStringTable[_NN_Using_Other_Server_Group]);return;}//여기서 홈페이지의 결제 페이지?
				if	(pUser[conn].Billing==5) 
				{	;// 5초내에 빌링이 답변을 안하면, 유저는 5번 모드로 바뀐다. 즉, 아무 메시지 없이 로그인이 된다.
				}
			}
			if	( pUser[conn].SelChar.Score[m->Slot].Level>=FREEEXP && pUser[conn].SelChar.Score[m->Slot].Level<999 && BILLING == 3 && pUser[conn].SelChar.Score[m->Slot].Level>=1000)  //3:테스트
			{	if	(pUser[conn].Billing<=1) SendClientMessage(conn,g_pMessageStringTable[_NN_Wait_Checking_Billing]);
				if	(pUser[conn].Billing==3) 
				{	sprintf(temp,g_pMessageStringTable[_DN_Not_Allowed_Account],FREEEXP);
					SendClientMessage(conn,temp);
				}
				if (pUser[conn].Billing==4) SendClientMessage(conn,g_pMessageStringTable[_NN_Using_Other_Server_Group]);
			}
			if	(BILLING==2 && pUser[conn].Child==1 && pUser[conn].SelChar.Score[m->Slot].Level >= FREEEXP && (g_Hour<=7/||g_Hour>=23)) 
			{	SendClientMessage(conn,g_pMessageStringTable[_NN_Child_Pay]);
				break;
			}

			if	(pUser[conn].Mode!=USER_SELCHAR) 
			{	//sprintf(temp,"WRONG-CHARLOGIN %d %d %d %d",pUser[conn].Mode
				SendClientMessage(conn,"Wait a moment.");
				//CrackLog(conn,"CharLogin");
				sprintf(temp,"err charlogin not user_selchar %d %d",conn,pUser[conn].Mode);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				return;
			}   
			m->Type = _MSG_DBCharacterLogin;         m->ID   = conn;
			pUser[conn].Mode	= USER_CHARWAIT;     // LOGIN과 캐랙터 만들기는 동일.
			//pUser[conn].Child   = 0;
			pMob[conn].Mode		= MOB_USER;
			pMob[conn].MOB.Merchant = 0;
			DBServerSocket.SendOneMessage((char*)m,sizeof(MSG_CharacterLogin));
			*/
		}	break;
	case _MSG_InitSkill:
		{	MSG_InitSkill* m = (MSG_InitSkill*) msg;

			for(int i=0; i<MAX_SKILL; i++) m->bySkill[i] = pMob[conn].MOB.bySkill[i];

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case CSP_REQ_INIT_REGEN_CHAR:
		{	S_CSP_REQ_INIT_REGEN_CHAR * m = (S_CSP_REQ_INIT_REGEN_CHAR *) msg;
			
			S_SCP_RESP_INIT_REGEN_CHAR sm; sm.wType = SCP_RESP_INIT_REGEN_CHAR;
			sm.byZone = pMob[conn].MOB.bySaveZone;

			if  (pUser[conn].Mode!=USER_PLAY) return;

			if(g_iZoneID == SERVER_STRONGHOLD)			//	요새지역 부활
			{	
				if(pMob[conn].MOB.nRupiah < 20000) 
				{	pMob[conn].Regen(0, REGEN_TYPE_REGEN);
					return;
				}
				if(m->byConnType == REGEN_TYPE_ARENA)
				{
					pMob[conn].MOB.nRupiah -= 20000;
					
					if(!g_kArena.IsProgressed()/*g_iIsArenaOpend*/) g_dwArenaMoney += 20000;
					if(g_dwArenaMoney>=MONEY_ARENAEVENT)					//	ARENA 이벤트 발생조건 - 1억이상의 아레나머니가 있고
						if(!g_kArena.IsProgressed() && g_iBattleForStronghold==0)		//	ARENA 이벤트 비실행상태이고 요새전 상황이 아니고
						{	struct tm when; time_t now;						//	0~2시, 10~24시 사이면 이벤트를 발생한다.
							time(&now); when = *localtime(&now);
							if(when.tm_hour<2 || when.tm_hour>10) g_kArena.Start( (int)g_dwArenaMoney ); //TriggerEvent( conn, 66, pMob[conn].TargetX, pMob[conn].TargetY, 0 );
						}

					pMob[conn].Regen(0, REGEN_TYPE_ARENA);
				}
				else
					pMob[conn].Regen(0, REGEN_TYPE_REGEN);
			}
			else if(g_iZoneID == SERVER_KATANA3)		//	공성지역 부활
			{
				if(m->byConnType == REGEN_TYPE_CASTLE1)
				{
					pMob[conn].Regen(0, REGEN_TYPE_CASTLE1);
				}
				else if(m->byConnType == REGEN_TYPE_CASTLE2)
				{
					pMob[conn].Regen(0, REGEN_TYPE_CASTLE2);
				}
				else
					pMob[conn].Regen(0, REGEN_TYPE_REGEN);
			}
			else										//	요새, 공성지역을 제외한 부활
                pMob[conn].Regen(0, REGEN_TYPE_REGEN);

			if(pMob[conn].m_bMoveZone)
			{
				pMob[conn].MOB.nHP = pMob[conn].m_iMaxHP/2;
				pMob[conn].MOB.nTP = pMob[conn].m_iMaxTP/2;
			}

		}	break;
	case _MSG_TrimuritySelect:
		{	MSG_TrimuritySelect * m = (MSG_TrimuritySelect *) msg;

			if(m->byType==0)	//	주신카운트 조회
			{
				m->nBrahmaCount = g_iBrahmaCount;
				m->nVishnuCount = g_iVishnuCount;
				m->nSivaCount = g_iSivaCount;
				m->dwMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
				break;
			}

			int nMoney=0; int nBraman = 0;
			if(strcmp(pMob[conn].MOB.szName, m->CharName))									//	자신이 아닐 경우
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Select_Others]); break;
			}

			if(pUser[conn].nGuildIndex!=0 && pMob[conn].MOB.byTrimuriti!=0)					//	길드원일 경우
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Select_Guild]); break;
			}

			if(pMob[conn].MOB.byLevel < TRIMURITY_LEVEL_LOW) {SendClientMessage(conn, g_pMessageStringTable[_Trimuriti_Select_Want_Level]); break;}

			if(pMob[conn].MOB.byTrimuriti != 0)
			{	
				byte byFromTri = pMob[conn].MOB.byTrimuriti;
				byte byToTri = m->byTrimuriti;
				short snFrom = 0;
				short snTo = 0;
				if(byFromTri == eTNClan_Brahma) snFrom = g_iBrahmaCount;
				else if(byFromTri == eTNClan_Vishnu) snFrom = g_iVishnuCount;
				else if(byFromTri == eTNClan_Siva) snFrom = g_iSivaCount;
				else return;													//	이외의 경우(gm케릭)는 주신변경을 할수없다
				if(byToTri == eTNClan_Brahma) snTo = g_iBrahmaCount;
				else if(byToTri == eTNClan_Vishnu) snTo = g_iVishnuCount;
				else if(byToTri == eTNClan_Siva) snTo = g_iSivaCount;
				else return;													//	이외의 경우(gm케릭)로 주신변경을 할수없다.

				float fRatio = 0;
				if(snFrom <= 0) fRatio = 1;
				else fRatio = (float)snTo/snFrom;

				if(snTo <= 0) fRatio = 1;
				fRatio = (float)pow(fRatio, 1.2);

				float fPrice = 10*(float)pow(pMob[conn].MOB.byLevel, 3.25 )+990;
				nMoney = (int)(fPrice*fRatio*0.3);

				if(pMob[conn].MOB.nRupiah<nMoney) 
				{	SendClientMessage(conn, g_pMessageStringTable[_Trimuriti_Select_Want_Money]); break;
				}

				int nCount=0;
				int nIndex1=7134-HT_PARAMTYPE_ITEM_START+1;		//	고대주술서(7134, 15장)
				for(int i=0; i<pMob[conn].byMaxInven; i++)
				{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex1) 
					{	nCount += pMob[conn].MOB.Inven[i].byCount;
						if(nCount>15) break;
					}
				}
				if(nCount<15) {SendClientMessage(conn, g_pMessageStringTable[_Trimuriti_Select_Want_Resource]); break;}

				nCount=15;
				//	인벤에서 고대주술서아이템을 제거한다.
				for(i=0; i<pMob[conn].byMaxInven; i++)
				{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex1) 
					{	if(pMob[conn].MOB.Inven[i].byCount>nCount)
						{	pMob[conn].MOB.Inven[i].byCount-=nCount;

							S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
							sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
							sm.byIndex=i; sm.sitem=pMob[conn].MOB.Inven[i];
							pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
							break;
						}	else
						{	nCount-=pMob[conn].MOB.Inven[i].byCount;
							S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
							sm.byType=SET_ITEM_DELETE; sm.byPlace = ITEM_PLACE_INVEN;
							sm.byIndex=i; sm.sitem=pMob[conn].MOB.Inven[i];
							pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
							memset(&(pMob[conn].MOB.Inven[i]), 0, sizeof(STRUCT_ITEM));
						}
					}
				}

				int nX=0, nZ=0;
				BOOL bRet=GetTrimurityArea(conn, nX, nZ);	//	주신을 가진 케릭터가 주신변경시 저장장소를 1차마을로 바꾸어준다.
				if(!bRet) {CloseUser(conn); return;}
				int tret = GetEmptyMobGrid(conn,&nX,&nZ);
				if	(tret==FALSE)
				{	sprintf(temp,"err no empty space at _MSG_TrimuritySelect x:%d y:%d",nX,nZ);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					int tret = GetEmptyMobGrid(conn,&nX,&nZ);
					if	(tret==FALSE)
					{	Log("clo err too many people near start point => 20",pUser[conn].AccountName,pUser[conn].IP);
						SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]);
						CloseUser(conn); return;
					}
				}

				nBraman = (int)(pMob[conn].MOB.nBramanPoint * 0.3);
				pMob[conn].DecGold(nMoney);					//	선택주신이 있을경우 돈이 깍인다.(최초 주신이 없을 경우는 돈이 안깍인다)
				pMob[conn].MOB.bySaveZone = ServerIndex+1;
				pMob[conn].MOB.snSaveX = nX;
				pMob[conn].MOB.snSaveZ = nZ;
				pMob[conn].MOB.nBramanPoint -= nBraman;
				pMob[conn].NotifyUpdateUIMsg();

				Msg_BramanBonus sm; sm.wType = _Msg_BramanBonus;		//	db로 브라만 포인트 헌납치를 알린다.
				strncpy(sm.pCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				sm.byTrimuriti = m->byTrimuriti;
				sm.nBonus = nBraman;
				if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(Msg_BramanBonus)))
				{	Log("err Msg_BramanBonus DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
			}

			sprintf(temp,"tri Trimuriti Change from:%d To:%d Price:%d BP:%d",pMob[conn].MOB.byTrimuriti, m->byTrimuriti, nMoney, nBraman);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			pMob[conn].MOB.byTrimuriti = m->byTrimuriti;
			m->dwMoney=pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			MSG_Broadcast sm; sm.wType = _MSG_Broadcast;
			sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER);
			sm.byBgColor		= 14;			    // 채팅 메세지 배경색
			sm.byTextColor		= 14;			    // 채팅 메세지 배경색
			sm.byMsgType		= MESSAGE_ZONE;
			sm.byTrimuriti		= m->byTrimuriti;

			char pTri[16] = {0,};
			if(m->byTrimuriti==eTNClan_Brahma) sprintf(pTri, g_pMessageStringTable[_Brahma]);
			if(m->byTrimuriti==eTNClan_Vishnu) sprintf(pTri, g_pMessageStringTable[_Vishnu]);
			if(m->byTrimuriti==eTNClan_Siva) sprintf(pTri, g_pMessageStringTable[_Siva]);
			sprintf(sm.szMsg, g_pMessageStringTable[_Change_Trimuriti], pMob[conn].MOB.szName, pTri);
			SendToAll((MSG_STANDARD*)&sm);		//	존내에 주신선택을 공지한다.

			//	주신스킬을 삭제한다.
			//	해당계급의 주신스킬 포인트가 지급된다.

			SendToAll((MSG_STANDARD*)m);		//	존내에 주신선택을 공지한다.
		}	break;
	case _MSG_TrimurityPoint:
		{	MSG_TrimurityPoint * m = (MSG_TrimurityPoint *) msg;

			if(pMob[conn].MOB.byTrimuriti == 0)
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Point_Not_Trimuriti]); break;
			}
				
			if(pMob[conn].MOB.nBramanPoint >= TRIMURITY_POINT_LEVEL)
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Point_Too_High]); break;
			}

			if(pMob[conn].MOB.nRupiah < MONEY_TRIMURITY_UP)
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Point_Want_Money]); break;
			}

			int nCount=0;
			int nIndex=7116-HT_PARAMTYPE_ITEM_START+1;		//	영혼의 구슬(7116, 10개)
			for(int i=0; i<pMob[conn].byMaxInven; i++)
			{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex) 
				{	nCount += pMob[conn].MOB.Inven[i].byCount;
					if(nCount>10) break;
				}
			}
			if(nCount<10) {SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Point_Want_Resource]); break;}

			nCount=10;
			//	인벤에서 영혼의 구슬 아이템을 제거한다.
			for(i=0; i<pMob[conn].byMaxInven; i++)
			{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex) 
				{	if(pMob[conn].MOB.Inven[i].byCount>nCount)
					{	pMob[conn].MOB.Inven[i].byCount-=nCount;

						S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
						sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
						sm.byIndex=i; sm.sitem=pMob[conn].MOB.Inven[i];
						pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
						break;
					}	else
					{	nCount-=pMob[conn].MOB.Inven[i].byCount;
						S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
						sm.byType=SET_ITEM_DELETE; sm.byPlace = ITEM_PLACE_INVEN;
						sm.byIndex=i; sm.sitem=pMob[conn].MOB.Inven[i];
						pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
						memset(&(pMob[conn].MOB.Inven[i]), 0, sizeof(STRUCT_ITEM));
					}
				}
			}

			
			pMob[conn].DecGold(MONEY_TRIMURITY_UP);
			pMob[conn].IncBP(1000);
			
			m->nBramanPoint = pMob[conn].MOB.nBramanPoint;
			m->dwMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case CSP_REQ_SAVE_POSITION:
		{	S_REQUEST * m = (S_REQUEST*) msg;
			
			S_RESULT sm;	sm.wType = SCP_RESP_SAVE_POSITION;

			//	저장장소가 적합한지 전상적인 패킷인지 체크하는 부분추가해야한다.
			//	SAVEOBJECT, MOB DISTANCE ERROR	: 실패 패킷을 만들고 전송한다.
			//	sm.nResult = 1;
			//	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT));
			//	return;
			
			if(g_iZoneID==eZone_Chaturanka || g_iZoneID==eZone_Kalia1 || g_iZoneID==eZone_Kalia2 || g_iZoneID==eZone_Kalia3 || 
				g_iZoneID==eZone_Stronghold || g_iZoneID==eZone_Castle || g_iZoneID==4 || g_iZoneID==6 || g_iZoneID==12) return;
			
			bool bRet = false;
			int iNPCID = (int)m->wDummy;
			byte byTrimuriti = 0;
			short snX, snZ = 0;
			int nMap = 40001+ServerIndex; DWORD dwLevel = 0;
			int iDistance = 0;
			while(1)
			{
				if(!g_ParamMgr.HT_bGetMapLevelRestrict( nMap, &dwLevel )) break;
				if(pMob[conn].MOB.byLevel < dwLevel) break;
				if(!g_ParamMgr.HT_bGetNPCTrimuriti( iNPCID, &byTrimuriti )) break;
				if(!g_ParamMgr.HT_bGetNPCPosition( iNPCID, &snX, &snZ)) break;
				if(byTrimuriti!=0 && byTrimuriti!=pMob[conn].MOB.byTrimuriti) break;				//	주신제한에 걸리면 사용불가

				iDistance = pMob[conn].CalDistance2( snX, snZ );
				if(iDistance>g_iHalfGridX) break;													//	케릭터가 NPC와 65Grid보다 멀경우 사용불가

				bRet = true;
				break;
			}

			if(!bRet)
			{	sm.nResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT)); return;
			}

			//	성공시 MOB의 SAVE POSITION관련 정보를 세팅한다.
			pMob[conn].MOB.bySaveZone = ServerIndex+1;
			pMob[conn].MOB.snSaveX = pMob[conn].TargetX;
			pMob[conn].MOB.snSaveZ = pMob[conn].TargetY;

			//	성공 패킷을 만들고 전송한다.
			sm.nResult = REPLY_ACK_OK;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT));
		}	break;
	case _MSG_Beauty:
		{	MSG_Beauty* m = (MSG_Beauty*)msg;

			int nCash1 = 0; int nCash2 = 0; int nCash3 = 0; 
			int nTotCash = 0; bool bRet = true; 
			int nItemIndex = 0;

			bool bFree = false;
			if(pUser[conn].m_byItemStatus & 0x01) bFree = true;

			m->byResult = REPLY_ACK_OK;
			m->nCash = pUser[conn].m_nCash;

			if(m->byFace<=0 || m->byFace>BEAUTY_NEW_FACE) bRet = false;
			if(m->byHead<=0 || m->byHead>BEAUTY_NEW_HAIR) bRet = false;

			if(m->byFace!=pMob[conn].MOB.byFace)	//	얼굴변경
			{	if(m->byFace>BEAUTY_OLD_FACE) nItemIndex = eItem_ChangeFace;
				else nItemIndex = eItem_ChangeOldFace;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash1);
				nTotCash += nCash1;
			}
			if(m->byHead!=pMob[conn].MOB.byHead)	//	머리변경
			{	if(m->byHead>BEAUTY_OLD_HAIR) nItemIndex = eItem_ChangeHair;
				else nItemIndex = eItem_ChangeOldHair;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash2);
				nTotCash += nCash2;
			}
			if(m->snTribe!=pMob[conn].MOB.snTribe)	//	성전환
			{	//	변경 가능한 종족인지를 체크한다(gm으로 변신한 사례가 있었슴)
				if(m->snTribe!=TRIBE_NAGA && m->snTribe!=TRIBE_ASURA && m->snTribe!=TRIBE_YAKSA && m->snTribe!=TRIBE_DEVA && 
					m->snTribe!=TRIBE_KINNARA && m->snTribe!=TRIBE_RAKSHASA && m->snTribe!=TRIBE_GANDHARVA && m->snTribe!=TRIBE_GARUDA)
				{	m->byResult = REPLY_UNKNOWN;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty)); break;	//	실패함을 알림.
				}

				nItemIndex = eItem_ChangeSex;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash3);
				nTotCash += nCash3;
			}


			if(nTotCash<=0 || !bRet)
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty)); break;	//	실패함을 알림.
			}

			if(!bFree)	//	유료일 경우
			{
				if(pUser[conn].m_nCash<nTotCash)
				{	m->byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty)); break;	//	캐쉬부족을 알림.
				}
				
				pUser[conn].m_nCash -= nTotCash;	
			}
			else
			{
				pUser[conn].m_byItemStatus &= 0xFE;

				if(m->snTribe!=pMob[conn].MOB.snTribe) break;								//	무료모드로 종족변경은 불가능하다
			}


			m->nCash = pUser[conn].m_nCash;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty));				//	변경성공을 알림.

			if(!bFree)	//	유료일 경우
			{
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash; nm.nID=conn; 
					nm.byType=eRun; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

					if(m->byFace!=pMob[conn].MOB.byFace)	//	얼굴변경
					{	nm.nCash=nCash1; nm.snItemIndex = eItem_ChangeFace; 
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
					if(m->byHead!=pMob[conn].MOB.byHead)	//	머리변경
					{	nm.nCash=nCash2; nm.snItemIndex = eItem_ChangeHair; 
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
					if(m->snTribe!=pMob[conn].MOB.snTribe)	//	성전환
					{	nm.nCash=nCash3; nm.snItemIndex = eItem_ChangeSex; 
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash2; nm.ID=conn; 
					nm.C_Type = 3; 
					nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
					strcpy(nm.Order_Type,"I0");
					strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
					unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
					sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);

					if(m->byFace!=pMob[conn].MOB.byFace)	//	얼굴변경
					{	nm.Amount=-nCash1; sprintf(nm.Item_no, "%d", eItem_ChangeFace);
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
					if(m->byHead!=pMob[conn].MOB.byHead)	//	머리변경
					{	nm.Amount=-nCash2; sprintf(nm.Item_no, "%d", eItem_ChangeHair);
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
					if(m->snTribe!=pMob[conn].MOB.snTribe)	//	성전환
					{	nm.Amount=-nCash3; sprintf(nm.Item_no, "%d", eItem_ChangeSex);
						ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
					}
				}
			}

			sprintf(temp,"beauty %s Face(%02x->%02x), Head(%02x->%02x), Tribe(%04x->%04x)",pMob[conn].MOB.szName,m->byFace,pMob[conn].MOB.byFace,m->byHead,pMob[conn].MOB.byHead,m->snTribe,pMob[conn].MOB.snTribe); 
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			if(m->byFace!=pMob[conn].MOB.byFace) pMob[conn].MOB.byFace = m->byFace;		//	얼굴변경
			if(m->byHead!=pMob[conn].MOB.byHead) pMob[conn].MOB.byHead = m->byHead;		//	머리변경
			if(m->snTribe!=pMob[conn].MOB.snTribe) pMob[conn].MOB.snTribe = m->snTribe;	//	성전환

			// 내 정보를 주위의 mob들에게 전송한다.
			int tx = pMob[conn].TargetX; int ty = pMob[conn].TargetY;
			S_SCP_INIT_OTHER_MOB sOther;
			GetCreateMob(conn,&sOther); 
			GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn);
		}	break;
	case _MSG_CLASS:
		{	MSG_CLASS* m = (MSG_CLASS*)msg;

			STRUCT_ITEM* sour = NULL;	//	인벤에 아이템을 넣어준다.
			int	emptyinven = GetEmptyInven(conn);		
			if	(emptyinven<0 || emptyinven>=pMob[conn].byMaxInven) 
			{	SendClientMessage(conn, g_pMessageStringTable[_Class_Get_Item_Fail]);
				return;
			};

			bool bRet = false;
			if(m->byClass1==CLASS_LEVEL1)
			{	if(pMob[conn].MOB.byClass1!=CLASS_LEVEL0) break;		//	0차에서만 1차전직이 가능하다.
				if(pMob[conn].MOB.byClass2!=m->byClass2) break;			//	1차전직시 byClass2(종족클래스)를 바꿀수 없다.
				pMob[conn].MOB.byClass1=CLASS_LEVEL1; bRet=true; 		//	1차전직성공

				// Added by 정재웅(2005.12.28)
				// 1차 전직 성공시, 경험치 보너스를 준다.
				//TriggerEvent( conn, 56, pMob[conn].TargetX, pMob[conn].TargetY, g_irgGod[eTNClan_Brahma], 1300 );
			}	
			else if(m->byClass1==CLASS_LEVEL2)
			{	int nClass = m->byClass2/2;
				if(pMob[conn].MOB.byClass1!=CLASS_LEVEL1) break;		//	1차에서만 2차전직이 가능하다.
				if(pMob[conn].MOB.byClass2!=nClass) break;				//  2차전직시 byClass2(종족클래스)가 적합한지를 체크한다.
				pMob[conn].MOB.byClass1=CLASS_LEVEL2;
				pMob[conn].MOB.byClass2=m->byClass2; bRet=true;
			}

			int nX=pMob[conn].TargetX; int nZ=pMob[conn].TargetY;
			m->nID=conn;
			m->byClass1=pMob[conn].MOB.byClass1;
			m->byClass2=pMob[conn].MOB.byClass2;

			if(!bRet)			//	전직실패시
			{	sprintf(temp,"dbg _MSG_CLASS packet err char:%s Pclass1:%d Pclass2:%d class1:%d, class2:%d",
					pMob[conn].MOB.szName,m->byClass1,m->byClass2,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_CLASS));
			}

			//	전직성공시
			GridMulticast(nX,nZ,(MSG_STANDARD*)m,0,30);
			pMob[conn].UpdateEquipmentPoints();
			pMob[conn].NotifyUpdateUIMsg();

			//	길드원들에게 전직을 전송한다.
			DBUpdateGuildMember(conn);

			bool bRes=true; short snMaxDur=0; int nIndex=0;
			sour=&(pMob[conn].MOB.Inven[emptyinven]);
			memset(sour, 0, sizeof(STRUCT_ITEM));

			sour->byCount=1;
			if(pMob[conn].MOB.byClass1==CLASS_LEVEL1)
			{	if(pMob[conn].MOB.byClass2==CLASS_SATVAN)
				{	nIndex=CLASS_SATVAN_ITEM;
				}	else
				if(pMob[conn].MOB.byClass2==CLASS_DHVANTA)
				{	nIndex=CLASS_DHVANTA_ITEM;
				}	else
				if(pMob[conn].MOB.byClass2==CLASS_NIRVANA)
				{	nIndex=CLASS_NIRVANA_ITEM;
				}	else
				if(pMob[conn].MOB.byClass2==CLASS_MANTRIKA)
				{	nIndex=CLASS_MANTRIKA_ITEM;
				}
			}
			/*
			else if(pMob[conn].MOB.byClass1==CLASS_LEVEL2)
			{	SendClientMessage(conn, g_pMessageStringTable[_Class_Send]); return;
			}
			*/

			bRes = g_ParamMgr.HT_bGetItemMaxDurability	(nIndex, &snMaxDur);
			if(!bRes)
			{	sprintf(temp,"err _MSG_CLASS can't find item index:%d", nIndex);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP); return;
			}

			sour->snIndex = nIndex-HT_PARAMTYPE_ITEM_START+1;
			sour->snDurability  = snMaxDur;
			sour->byCount = 1;
			S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;		//	아이템추가를 알린다.
			sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
			sm.byIndex=emptyinven; sm.sitem=pMob[conn].MOB.Inven[emptyinven];
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
		}	break;
	case CSP_REQ_LEARN_SKILL :
		{	S_CSP_REQ_LEARN_SKILL* pMsg = (S_CSP_REQ_LEARN_SKILL*)msg;
			int iRes = pMob[conn].LearnSkill( pMsg->snID );
			if( iRes )
			{
				#ifdef __TN_2ND_LOG__
				{
					char chBuf[256] = { 0,0,0, };
					sprintf( chBuf, "\t[LearnSkill] Learn Skill 실패 원인: %d \r\n", iRes );
					pMob[conn].Print( chBuf );
				}
				#endif //__TN_2ND_LOG__
			}

		}	break;
	case CSP_CAST_UNIT_SKILL :
		{
			S_CSP_CAST_AREA_SKILL kMsg;
			memset( &kMsg, 0, sizeof( S_CSP_CAST_AREA_SKILL) );
			memcpy( &kMsg, msg, sizeof(S_CSP_CAST_UNIT_SKILL) );
			int iRes = pMob[conn].CastSkill( &kMsg, 1 );
			if( iRes )
			{
				#ifdef __DYNAMIC_LOG__
				if( pMob[conn].m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf( chBuf, "\t[CastSkill] skill 실패 원인: %d \r\n", iRes );
					pMob[conn].Print( chBuf );
				}
				#endif //__DYNAMIC_LOG__
				kMsg.snRes = (short)iRes;
				short sUnitID = kMsg.krgTarget[0].snKeyID;
				if( 0 >= sUnitID || MAX_MOB <= sUnitID )
				{
					kMsg.krgTarget[0].snKeyID = 0;
					kMsg.krgTarget[0].iHP = 0;
					kMsg.krgTarget[0].iAffection = 0;
				}
				else
				{
					kMsg.krgTarget[0].iHP = pMob[sUnitID].MOB.nHP;
					kMsg.krgTarget[0].iAffection = pMob[sUnitID].m_iAffections;
				}

				kMsg.krgTarget[0].byRes = (byte)eCmbt_Dodge;
				kMsg.krgTarget[0].iDamage = 0;
								
				pMob[conn].BroadcastCastSkill( &kMsg, 1 );
			}
		}	break;
	case CSP_CAST_AREA_SKILL :
		{
			S_CSP_CAST_AREA_SKILL* pMsg = (S_CSP_CAST_AREA_SKILL*)msg;
			int iRes = pMob[conn].CastSkill( pMsg, TN_MAX_TARGET_COUNT );
			if( iRes )
			{
				#ifdef __DYNAMIC_LOG__
				if( pMob[conn].m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf( chBuf, "\t[CastSkill] skill 실패 원인: %d \r\n", iRes );
					pMob[conn].Print( chBuf );
				}
				#endif //__DYNAMIC_LOG__
				pMsg->snRes = (short)iRes;
				for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
				{
					short sUnitID = pMsg->krgTarget[i].snKeyID;
					//if( 0 >= sUnitID || MAX_MOB <= sUnitID ) continue;
					if( 0 >= sUnitID || MAX_MOB <= sUnitID )
					{
						pMsg->krgTarget[i].snKeyID = 0;
						pMsg->krgTarget[i].iHP = 0;
						pMsg->krgTarget[i].iAffection = 0;
					}
					else
					{
						pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
						pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
					}

					pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge;
					pMsg->krgTarget[i].iDamage = 0;
					pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
					pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
				}

				pMob[conn].BroadcastCastSkill( pMsg, TN_MAX_TARGET_COUNT );
			}

		}	break;
	case MSG_APPLY_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return;
			MSG_APPLY_SIEGE* pMsg = (MSG_APPLY_SIEGE*)msg;
			pMsg->snResult = eTNRes_Succeeded;

			//SYSTEMTIME st;
			//GetLocalTime( &st );

			//-------------------------------------------------------
			// 공성 신청 기간을 검사한다.
			//-------------------------------------------------------
			if( 1 == g_kSiege.get_ExpiryOftheTerm() )
			{
				SendClientMessage( conn, g_pMessageStringTable[_ExpireOfTheTermForSiege] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\r\n[%dYY%dMM%dDD %2dHH%2dMI%2dSS] MSG_APPLY_SIEGE_ID\r\n\t10 > who: %s, ClanSlot:%d, ExpandSlot:%d \r\n"
					, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
					, pMob[conn].MOB.szName, pMsg->byClanSlot, pMsg->byExpandSlot );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif 

			//-------------------------------------------------------
			// 공성 신청에 소모되는 돈을 검사한다.
			//-------------------------------------------------------
			int iFee = g_irgSetting[eCnst_FeeForSiegeSupport];
			//bool bBreak = false;
			if( 0 == pMsg->byExpandSlot  ) // leader로 신청
			{
				if( 1 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege1];
				else if( 2 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege2];
				else if( 3 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege3];
				//if( iFee > pMob[conn].get_Gold() ) bBreak = true;
			}
			//int iFee = TNSiege::eApplyFee_SiegeSupport;
			////bool bBreak = false;
			//if( 0 == pMsg->byExpandSlot  ) // leader로 신청
			//{
			//	if( 1 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege1;
			//	else if( 2 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege2;
			//	else if( 3 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege3;
			//	//if( iFee > pMob[conn].get_Gold() ) bBreak = true;
			//}


			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t20 > Check gold > gold:%d, fee:%d\r\n",  pMob[conn].get_Gold(), iFee );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif 

			if( iFee > pMob[conn].get_Gold() )
			{// 돈이 부족하다는 메시지				
				SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughGold] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}


			//-------------------------------------------------------
			// 7402 아이템을 10 개 소모한다.
			//-------------------------------------------------------			
			int irgSlot[5] = { -1,-1,-1,-1,-1 }; // item 검사/제거를 위한 slot No 기록
			int iItemID = 7402;
			int iCountRequired = g_irgSetting[eCnst_ItemCount];
			int iCount = 0;
			if( 0 == pMsg->byExpandSlot  ) // leader로 신청
			{
				iCount = pMob[conn].CheckItem( iItemID, iCountRequired, irgSlot ); // 요구사항이 만족하지 못하면 0을 return

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t30 > Check items > count:%d, iCountRequired:%d \r\n", iCount, iCountRequired );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif 

				if( iCount < iCountRequired )
				{
					SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughItem] );
					pMsg->snResult = eTNRes_Failed;
					pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
					return;
				}
			}
			
			//-------------------------------------------------------
			// 길드 조건에 맞아야 한다. 60 level 20명 이상
			//-------------------------------------------------------
			int iGuildID = pMob[conn].MOB.nGuildID;
			int iGuildIndex = pUser[conn].nGuildIndex;
			CGuild kGuild;
			int iRes = ReadGuildFile( iGuildID, &kGuild );
			if( FALSE == iRes )
			{ // 길드가 부정확하다.
				SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}


			//if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) ) // 길드장이 아니라면,
			if( !kGuild.IsGuildManager( pMob[conn].MOB.szName ) ) // 길드 관리자(길드장, 부길드장)이 아니라면, ...
			{
				SendClientMessage( conn, g_pMessageStringTable[_NotGuildMaster] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}			
					
			int iLevelRequired = g_irgSetting[eCnst_MemberLevel];
			int iMemberCountRequired = g_irgSetting[eCnst_MemberCount1]; // leader로 신청
			if( 0 < pMsg->byExpandSlot  ) iMemberCountRequired = g_irgSetting[eCnst_MemberCount2];
			int iMemberCount = 0;
			for( int i = 0; i < MAX_GUILD_MEMBER; ++i )
			{
				if( iLevelRequired <= kGuild.GUILD.Member[i].byLevel ) ++iMemberCount;
			}

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t40 > Check Guild > iMemberCount:%d, required:%d \r\n", iMemberCount, iMemberCountRequired );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif 
			
			if( iMemberCountRequired > iMemberCount )
			{
				SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughMember] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}
		
			iRes = g_kSiege.RegisterEntry( iGuildID, pMsg->byClanSlot, pMsg->byExpandSlot, conn ); // guild ID, clan slot, expand slot, applier
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes )
				{
					SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] );	
				}
				else if( eTNRes_InvalidGuild == iRes )
				{
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t55 > Register Entry > Res:%d > guidID:%d(idx:%d) \t---> Failed \r\n"
						, iRes, iGuildID, iGuildIndex );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif 

				pMsg->snResult = iRes; //eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}
			else
			{
				pMob[conn].DecGold( iFee );
				if( 0 == pMsg->byExpandSlot  ) pMob[conn].RemoveItem( iCountRequired, irgSlot ); 

				char chBuf3[512] = { 0,0,0, };
				sprintf(chBuf3, g_pMessageStringTable[_CompletedToApplySiege], kGuild.GUILD.GuildName );
				SendClientMessage( conn, chBuf3 );	

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t50 > Register Entry > Res:%d > guidID:%d(idx:%d, Name:%s) \t---> Succeeded \r\n"
						, iRes, iGuildID, iGuildIndex, kGuild.GUILD.GuildName );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif

			}



			int iAllyGuildID = pGuild[iGuildIndex].nAlliedID;

			iRes = g_kSiege.RegisterEntry( iAllyGuildID, pMsg->byClanSlot, pMsg->byExpandSlot+1, conn );
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes )
				{
					SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] );	
				}
				else if( eTNRes_InvalidGuild == iRes )
				{
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t65 > Ally > Register Entry > Res:%d > guidID:%d \t---> Failed \r\n"
						, iRes, iAllyGuildID );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif

				pMsg->snResult = iRes; //eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
				return;
			}
			else
			{
				char szNotify[1024] = { 0,0,0, };
				sprintf( szNotify, g_pMessageStringTable[_CompletedToApplySiege], g_pMessageStringTable[_AllyGuild] );
				SendClientMessage( conn, szNotify );	

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t60 > Ally > Register Entry > Res:%d > guidID:%d \t---> Succeeded \r\n"
						, iRes, iAllyGuildID );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif
			}


			#ifdef __TN_TOP_LOG__
			{
				WriteLog( "\t 100 > Completed to register the entry of the siege\r\n", g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif


			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) );
		}
		break;


	case MSG_GIVEUP_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return;
			MSG_GIVEUP_SIEGE* pMsg = (MSG_GIVEUP_SIEGE*)msg;

			int iRes = eTNRes_Failed;
			//-------------------------------------------------------
			// 길드 조건에 맞아야 한다. 60 level 20명 이상
			//-------------------------------------------------------
			int iGuildID = pMob[conn].MOB.nGuildID;
			int iGuildIndex = pUser[conn].nGuildIndex;
			CGuild kGuild;
			iRes = ReadGuildFile( iGuildID, &kGuild );
			if( FALSE == iRes )
			{ // 길드가 부정확하다.
				SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_GIVEUP_SIEGE) );
				return;
			}

			if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) ) // 길드장이 아니라면,
			{
				SendClientMessage( conn, g_pMessageStringTable[_NotGuildMaster] );
				pMsg->snResult = eTNRes_Failed;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_GIVEUP_SIEGE) );
				return;
			}			

			iRes = g_kSiege.GiveUpSiege( iGuildID );
			//if( iRes )
			//{// 공성 연맹 리더일 경우, 길드 연합일 경우, 등록되어 있지 않을 경우
			//	SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsNotRegistered] );
			//}
			//else SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] );

		}
		break;

	case MSG_STATE_OF_THE_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return;
			MSG_STATE_OF_THE_SIEGE* pMsg = (MSG_STATE_OF_THE_SIEGE*)msg;
			g_kSiege.get_Symbols( pMsg->irgClan );

			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_STATE_OF_THE_SIEGE) );
		}
		break;
/*
	case MSG_SIEGE_ENTRY_ID :
		{
			MSG_SIEGE_ENTRY* pMsg = (MSG_SIEGE_ENTRY*)msg;

		}
		break;
*/
	case MSG_CHECK_SIEGE_ENTRY_ID :
		{
			if( eZone_Castle != g_iZoneID ) return;
			MSG_CHECK_SIEGE_ENTRY* pMsg = (MSG_CHECK_SIEGE_ENTRY*)msg;
			//pMsg->byClanSlot 
			//pMsg->byPage
			MSG_SIEGE_ENTRY kEntryMsg;
			memset( &kEntryMsg, 0 , sizeof(kEntryMsg) );
			kEntryMsg.wType = MSG_SIEGE_ENTRY_ID;
			kEntryMsg.wPDULength = sizeof(MSG_SIEGE_ENTRY)-sizeof(HEADER);

			kEntryMsg.byDate = 1;
			kEntryMsg.byClanSlot = pMsg->byClanSlot;
			kEntryMsg.byPage = pMsg->byPage;
			const int iElementCount = 8;
			int iExpandSlot = pMsg->byPage * iElementCount;
			int iEnd = iExpandSlot + iElementCount;
			int iIndex = 0;
			for(; iExpandSlot < iEnd; ++iExpandSlot )
			{
				TNGUILD_INFO kGuild;
				g_kSiege.GetEntry( pMsg->byClanSlot, iExpandSlot, kGuild );
				kEntryMsg.irgGuildID[iIndex] = kGuild.iID;
				kEntryMsg.dwrgGuildMark[iIndex] = kGuild.dwMark;
				strncpy( kEntryMsg.szrgGuildName[iIndex], kGuild.szName, SZGUILD_LENGTH );
				++iIndex;
			}

			pUser[conn].cSock.SendOneMessage( (char*)&kEntryMsg, sizeof(MSG_SIEGE_ENTRY) );
		}
		break;
	case MSG_FIX_DATE_OF_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return;
			MSG_FIX_DATE_OF_SIEGE* pMsg = (MSG_FIX_DATE_OF_SIEGE*)msg;

			if( 0 == pMsg->byWhat ) // 공성날짜 요청
			{
				pMsg->byDate = (byte)g_kSiege.get_DateToHold();
			}
			else if( 1 == pMsg->byWhat ) // 공성 날짜 결정 by 수성 길드 guild master
			{
				//---------------------------------------------
				// 수성 길드 길마인지 확인해야 한다.
				//---------------------------------------------
				int iDefenseGuild = g_kSiege.get_OwnerGuild();
				int iGuildID = pMob[conn].MOB.nGuildID;
	
				if( iDefenseGuild != iGuildID )
				{// 수성 아쉬람의 길드 마스터가 아닙니다.
					SendClientMessage( conn, g_pMessageStringTable[_NotDefenseGuildMaster] );
					return;
				}

				int iGuildIndex = pUser[conn].nGuildIndex;
				CGuild kGuild;
				int iRes = ReadGuildFile( iGuildID, &kGuild );
				if( FALSE == iRes )
				{ // 길드가 부정확하다.
					SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] );
					return;
				}

				if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) )
				{// 수성 아쉬람의 길드 마스터가 아닙니다.
					SendClientMessage( conn, g_pMessageStringTable[_NotDefenseGuildMaster] );
					return;
				}

				g_kSiege.SelectDate( pMsg->byDate );
			}

			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_FIX_DATE_OF_SIEGE) );
		}
		break;
	case MSG_PET_COMMAND_ID :
		{
			MSG_PET_COMMAND* pMsg = (MSG_PET_COMMAND*)msg;
			if( 0 >= conn || MAX_USER <= conn) return;
			int iMob = pMob[conn].m_irgSummoned[eTNCls2_Retainer];
			if( MAX_USER > iMob || MAX_MOB <= iMob ) return;

			if( 1 == pMsg->iAction ) // 공격해라
			{
				int iRes = pMob[conn].CanAttackTarget( pMsg->iParam1 );
				if( eTNRes_Succeeded == iRes )
				{
					pMob[iMob].ClearCurrentTarget();
					pMob[iMob].ClearAttacker( 0 );
					pMob[iMob].MemorizeAttacker( 0, 1, pMsg->iParam1 );
				}

				//if( pMob[conn].IsDebugOn( eTNDbg_Pet ) )
				//{
				//	char chBuf[512] = { 0,0,0, };
				//	sprintf(chBuf, "[Pet_Command] Attack> res:%d, master:%d, target:%d \r\n"
				//		,iRes , conn, pMsg->iParam1 );

				//	WriteLog( chBuf, ".\\Event\\[Log]Pet.txt" );
				//}
			}
			else if( 2 == pMsg->iAction ) // 멈춰라
			{
				pMob[iMob].ClearCurrentTarget();
				pMob[iMob].ClearAttacker( 0 );
				pMob[iMob].Mode = MOB_PEACE;
				pMob[iMob].OnFollow( pMob[iMob].Leader );
			}
		}
		break;
	case MSG_ITEM_ID :
		{	
			MSG_ITEM* pMsg = (MSG_ITEM*)msg;

			bool bCheckAffection = true;
			if(pMsg->byIndex<0 || pMsg->byIndex>=pMob[conn].byMaxInven) break;
			int nItemIndex = pMob[conn].MOB.Inven[pMsg->byIndex].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if( (HT_PARAMTYPE_ITEM_CHARGE_START <= nItemIndex) && (HT_PARAMTYPE_ITEM_CHARGE_END >= nItemIndex ) )
			{
				bCheckAffection = false;
			}

			if( nItemIndex!=eItem_Resurrect1 && nItemIndex!=eItem_Resurrect2 && bCheckAffection )
			{	if( (eTNVSAfn_Stun & pMob[conn].m_iAffections) || (eTNVSAfn_Sleep & pMob[conn].m_iAffections)  ) break;	
			}


			if( eItm_Use == pMsg->byType ) 
			{	
				if(pMsg->byIndex<0 || pMsg->byIndex>=pMob[conn].byMaxInven)
				{	sprintf(temp, "Invalid Inven position packet:%d of max:%d\r\n", pMsg->byIndex, pMob[conn].byMaxInven);
					Log( temp,pUser[conn].AccountName,pUser[conn].IP);
					return;
				}

				if(nItemIndex==eItem_Resurrect1 || nItemIndex==eItem_Resurrect2)				//	생명의 주문서사용
					pMob[conn].UseItem( pMsg, eTNFsm_Dead);
				else
                    pMob[conn].UseItem( pMsg );
			}
		}	break;
	case CONTACT_NPC :
		{// class1이 19일 경우에, client에서 현 메시지를 전달해준다.
			MSG_CONTACT_NPC* pMsg = (MSG_CONTACT_NPC*)msg;

			if( eTNSwitch_ContactNPC & g_iSwitch )
			{ 
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf( chBuf, "[%dMM%dDD %dHH%dMI%dSS] CONTACT_NPC received! > NPCID:%d\r\n"
					, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
					, pMsg->snNPCID
					);
				WriteLog( chBuf, ".\\Monster_Log\\[Log]ContactNPC.txt" );
			}

			int iNPCID = pMsg->snNPCID;
			if( MAX_USER > iNPCID || MAX_MOB <= iNPCID ) break;// NPC 일 경우에만, ...
			int tclan = pMob[iNPCID].m_byClan;

			if( eTNSwitch_ContactNPC & g_iSwitch )
			{ 
				char chBuf[512] = { 0,0,0, };
				sprintf( chBuf, "\t- clan:%d, Hostile:%d, EventID:%d \r\n"
					, tclan, g_iHostileTable[pMob[conn].m_byClan][tclan]
					, pMob[iNPCID].MOB.snBagIndex
					);
				WriteLog( chBuf, ".\\Monster_Log\\[Log]ContactNPC.txt" );
			}

			if( pMob[conn].m_byClan<0 || pMob[conn].m_byClan>eTNClan_NPC || tclan<0 || tclan>eTNClan_NPC )
			{	Log("err clan out or range", pMob[conn].MOB.szName, 0 );
				break;
			}
			if ( 0 < g_iHostileTable[pMob[conn].m_byClan][tclan] ) break;
				
			//int iMonsterDataIndex = pMob[iNPCID].MOB.nTP;
			int iEventID = pMob[iNPCID].MOB.snBagIndex;
			if( 0 < iEventID ) // event 처리
			{
				TriggerEvent( conn, iEventID, 0, 0, iNPCID, 20 );	
			}
		}	break;
	case REGISTER_KALA_CORE :
		{
			MSG_REGISTER_KALA_CORE* pMsg = (MSG_REGISTER_KALA_CORE*)msg;
			int iAltarSlot = pMsg->snID;
			if( 0 > iAltarSlot || eKalaAltar_MaxCount <= iAltarSlot ) return; // invalid kala-altar ID
			if( g_krgKalaAltar[iAltarSlot].sTrimuriti != pMob[conn].m_byClan ) return; // 주신이 틀리다.
			if( 0 < g_kKalaSystem.IsEmptyAltar( iAltarSlot ) ) return; // 비어 있지 않다.
			//if( 0 != g_irgKalaAltar[iAltarSlot] ) return; // 비어 있지 않다.
			if( !(eTNVSAfn_HaveKalaCore & pMob[conn].m_iAffections) ) return; // have a kala-core affection을 검사한다.
			int iDist = pMob[conn].CalDistance2( g_krgKalaAltar[iAltarSlot].x, g_krgKalaAltar[iAltarSlot].y );
			if( 10 < iDist ) return;
			// check a kala-core.  // 3주신에 따라 kala-core가 틀리기 때문에, 총 3번의 검사를 거쳐야 할 것이다. 

			//SYSTEMTIME st;
			//GetLocalTime( &st );

			int iMonsterID = 0;
			int irgSlot[5] = { -1,-1,-1,-1,-1 };
			int iCount = 0;
			iCount = pMob[conn].CheckItem( eKalaCore_Brahma, 1, irgSlot );
			iMonsterID = eKala_Brahma;
			if( 0 >= iCount )
			{	iCount = pMob[conn].CheckItem( eKalaCore_Vishnu, 1, irgSlot );
				iMonsterID = eKala_Vishnu;
			}
			if( 0 >= iCount )
			{
				iCount = pMob[conn].CheckItem( eKalaCore_Siva, 1, irgSlot );
				iMonsterID = eKala_Siva;
			}
			if( 1 > iCount )
			{
				{
					char chBuf[512] = { 0,0,0, };
					sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] REGISTER_KALA_CORE > Have no kala-core! -> TotalCount:%d \r\n"
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						,iCount
						);
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
				}
				return;
			}
			pMob[conn].RemoveItem( iCount, irgSlot ); // remove the kala-core.
			
			pMob[conn].m_iAffections = pMob[conn].m_iAffections ^ eTNVSAfn_HaveKalaCore;
			pMob[conn].BroadcastUpdateStatusMsg();

			int iRes = g_kKalaSystem.InstallKala( iMonsterID, g_krgKalaAltar[iAltarSlot].sTrimuriti, iAltarSlot, conn );
			if( iRes )
			{
				{
					char chBuf[512] = { 0,0,0, };
					sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] Register_Kala-core > InstallKala() > Res:%d \r\n"
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, iRes
						);
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
				}
				return;
			}

			int iTxtIndex = 0;
			if( eKala_Brahma == iMonsterID ) iTxtIndex = _Brahma;
			else if( eKala_Vishnu == iMonsterID ) iTxtIndex = _Vishnu;
			else if( eKala_Siva == iMonsterID ) iTxtIndex = _Siva;

			int iTrimuritiIndex = 0;
			if( eTNClan_Brahma == pMob[conn].m_byClan ) iTrimuritiIndex = _Brahma;
			else if( eTNClan_Vishnu == pMob[conn].m_byClan ) iTrimuritiIndex = _Vishnu;
			else if( eTNClan_Siva == pMob[conn].m_byClan ) iTrimuritiIndex = _Siva;

			char szMsg[1024] = { 0,0,0, };	
			sprintf( szMsg, g_pMessageStringTable[_Register_Kala_Core]
				, g_pMessageStringTable[iTrimuritiIndex] , pMob[conn].MOB.szName, pMob[conn].TargetX, pMob[conn].TargetY, g_pMessageStringTable[iTxtIndex] );
			PostMessageToZone( szMsg );

			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				strcat( szMsg, chBuf );
				WriteLog( szMsg, g_szrgLogFileName[eLogFileName_KalaSystem] );
			}

			//g_kKalaSystem.ChangeInfo( iKalaSlot, TNKalaSystem::eLoc_Altar, pMsg->snID, g_irgKalaAltar[pMsg->snID], 0, 0, 0, 0 );
			MoveKalaRewarder();

		}	break;
	case CSP_REQ_UPDATE_UI :
		{
			S_CSP_REQ_UPDATE_UI* pMsg = (S_CSP_REQ_UPDATE_UI*)msg;
			pMob[conn].NotifyUpdateUIMsg();
		}	break;
	case CSP_REQ_UPDATE_STATUS :
		{
			if( 0 >= conn && MAX_USER <= conn ) break;

			S_CSP_REQ_UPDATE_STATUS* pMsg = (S_CSP_REQ_UPDATE_STATUS*)msg;

			if( MAX_USER <= pMsg->snKeyID && MAX_MONSTER > pMsg->snKeyID && pMob[pMsg->snKeyID].IsNotLocked() ) // 몬스터이고 현재 lock 설정이 완료되어 있지 않을때
			{
				S_SCP_RESP_UPDATE_STATUS kMsg;
				kMsg.wType = SCP_RESP_UPDATE_STATUS;
				//kMsg.Size = sizeof( S_SCP_RESP_UPDATE_STATUS );
				kMsg.snKeyID = (short)pMsg->snKeyID;
				kMsg.iHP = pMob[pMsg->snKeyID].MOB.nHP;
				kMsg.iTP = 0;
				kMsg.iPrana = 0;
				kMsg.iAffections = pMob[pMsg->snKeyID].m_iAffections ;
				kMsg.snKarma = 0;

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof( S_SCP_RESP_UPDATE_STATUS ) );
			}
			else if( 0 < pMsg->snKeyID && MAX_USER > pMsg->snKeyID ) // PC일 경우
			{
				S_SCP_RESP_UPDATE_STATUS kMsg;
				kMsg.wType = SCP_RESP_UPDATE_STATUS;
				//kMsg.Size = sizeof( S_SCP_RESP_UPDATE_STATUS );
				kMsg.snKeyID = (short)pMsg->snKeyID;
				kMsg.iHP = pMob[pMsg->snKeyID].MOB.nHP;
				kMsg.iTP = pMob[pMsg->snKeyID].MOB.nTP;
				kMsg.iPrana = pMob[pMsg->snKeyID].MOB.nPrana;
				kMsg.iAffections = pMob[pMsg->snKeyID].m_iAffections ;
				kMsg.snKarma = pMob[pMsg->snKeyID].MOB.snKarma;

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof( S_SCP_RESP_UPDATE_STATUS ) );
			}
		}	break;
	case CSP_REQ_INCREASE_CHAKRA :
		{
			S_CSP_REQ_INCREASE_CHAKRA* pMsg = (S_CSP_REQ_INCREASE_CHAKRA*)msg;
			pMob[conn].IncChakra( (int)pMsg->byChakra );
		}	break;
	case _MSG_TOGGLE_BUTTON :
		{
			MSG_TOGGLE_BUTTON* pMsg = (MSG_TOGGLE_BUTTON*)msg;
			if( 1 == pMsg->byButton ) // PK 버튼
			{
				if( eTNSwitch_PKDisable &g_iSwitch ) return;
				if( 0 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus ^ eTNBtn_PK;
				else if( 1 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus | eTNBtn_PK;

				for( int i = 1; i < eFellow_MaxCount; ++i )
				{
					int iMob = pMob[conn].m_irgSummoned[i];
					if( MAX_USER <= iMob && MAX_MOB > iMob ) pMob[iMob].m_iButtonStatus = pMob[conn].m_iButtonStatus;

				}
			}
			/*
			else if( 2 == pMsg->byButton ) // Assist 버튼
			{
				int iPartyLeader = pMob[conn].Leader;
				if( 0 == iPartyLeader ) break;
				MSG_CHANGE_TARGET kMsg;
				kMsg.snTarget = (short)(pMob[iPartyLeader].m_iTargetHandle);
				if( 0 == kMsg.snTarget ) break; // target이 설정되어 있지 않을 경우, ...

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_TARGET) );
				
				//if( 0 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus ^ eTNBtn_Assist;
				//else if( 1 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus | eTNBtn_Assist;
			}*/
		}	break;
	case _MSG_CHANGE_TARGET :
		{
			if( 0 != pMob[conn].Leader ) break;
			MSG_CHANGE_TARGET* pMsg = (MSG_CHANGE_TARGET*)msg;			
			//pMob[conn].m_iTargetHandle = pMsg->snTarget;
			
			for( int i = 0; i < MAX_PARTY; ++i )
			{
				int iPartyMember = pMob[conn].m_irgParty[i];
				if( 0 >= iPartyMember || MAX_USER <= iPartyMember ) continue;
				pUser[iPartyMember].cSock.AddMessage( (char*)pMsg, sizeof(MSG_CHANGE_TARGET) );
				//pUser[iPartyMember].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_CHANGE_TARGET) );
			}
		}
		break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case _MSG_CharacterLogout:
		{	CharLogOut(conn);
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_MOVE_PORTAL:
		{	S_CSP_REQ_MOVE_PORTAL * m = (S_CSP_REQ_MOVE_PORTAL *) msg;

			S_SCP_RESP_MOVE_PORTAL sm; sm.wType=SCP_RESP_MOVE_PORTAL;

			if( pMob[conn].IsDead() || (eTNVSAfn_DontMove & pMob[conn].m_iAffections ))	//	if( (eTNVSAfn_Stun & pMob[conn].m_iAffections) || (eTNVSAfn_Sleep & pMob[conn].m_iAffections) ) 
			{	sm.byResult=REPLY_MOVE_PORTAL_STATUS; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
			}

			bool bRet=true; DWORD dwLevel=0; DWORD dwFee=0;			
			DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
			if(m->wStartPortalID!=0)	//	일반적인 포탈이동
			{	bRet &= g_ParamMgr.HT_bGetPortalFee(m->wStartPortalID, m->wEndPortalID, &dwFee);
			}	
			if(!bRet && m->wStartPortalID==103)	//	예외처리 - 하드코딩 (탄파람의 이동목표포탈이 갯수을 넘어간다, 만다라마을포탈)
			{
				bRet = true; dwFee = 2000;
			}

			bRet &= g_ParamMgr.HT_bGetPortalInfo(m->wEndPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ);

			int iFee = (int)dwFee;

			if(!bRet) 
			{	sprintf(temp,"dbg CSP_REQ_MOVE_PORTAL find portal data error startp:%d endp:%d",m->wStartPortalID, m->wEndPortalID);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
			}

			if(pMob[conn].MOB.byLevel < (byte)dwLevel)		//	포탈이동에 필요한 레벨이 낮을경우
			{	sm.byResult=REPLY_MOVE_PORTAL_WANTLEVEL; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
			}

			if(pMob[conn].MOB.nRupiah < iFee)	//	포탈이동에 필요한 돈이 부족할경우
			{	sm.byResult=REPLY_MOVE_PORTAL_WANTMONEY; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
			}

			BYTE byMoveZone = (BYTE)(dwServerID - HT_MAP_START + 1);
			if(eTNClan_GM != pMob[conn].MOB.byTrimuriti)	//	gm의 경우 레벨, 차크라제한 따위를 검색하지 않는다.
			{
				if(byMoveZone>=SERVER_KALIA_LOW && byMoveZone<=SERVER_KALIA_HIGH)
					if(!g_bIsKaliaOpend) return;
				if(byMoveZone==SERVER_KALIA_LOW)
				{	short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
					if(snChakra>297)	//	차크라합이 297보다 클경우에는 저랩칼리아던전에 출입불가요청(2005.5.19)
					{	sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
						pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
					}
				}	else
				if(byMoveZone==SERVER_KALIA_MIDDLE)
				{	short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
					if(snChakra>378)	//	차크라합이 378보다 클경우에는 중랩칼리아던전에 출입불가요청(2005.5.19)
					{	sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
						pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
					}
				}	else
				if(byMoveZone==SERVER_KRUMA_LOW)
				{	int iSkillPointUsed = 0; 
					for( int i = 0; i < 65; ++i ) iSkillPointUsed += pMob[conn].MOB.bySkill[i];
					for( int i = 80; i < MAX_SKILL; ++i ) iSkillPointUsed += pMob[conn].MOB.bySkill[i];
					short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
					if(snChakra>355 || iSkillPointUsed>63)	//	차크라합이 355보다 크거나 스킬포인트가 63보다 클시에는 저랩크루마지역에 출입불가요청(2005.11.25)
					{	sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
						pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
					}
				}	else
				if(byMoveZone==SERVER_STRONGHOLD)			//	요새지역에서 카우스트밤에는 해당요새소유길드만 출입가능
				{
					int iHold = m->wEndPortalID - 206;		//	요새내상점 : 206 ~ 209, 카우스트밤 : 216 ~ 219
					if(iHold>=0 && iHold<4)
					{
						if(g_krgStronghold[iHold].iOwner!=pMob[conn].MOB.nGuildID)
						{
							sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
							pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
						}
					}
					else if(iHold>=10 && iHold<14)
					{
						if(g_krgStronghold[iHold-10].iOwner!=pMob[conn].MOB.nGuildID)
						{
							sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
							pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break;
						}
					}
				}
			}

			if(byMoveZone == (ServerIndex+1))	//	동일존이면
			{	int tx = GetRandom(snStartX, snEndX);
				int ty = GetRandom(snStartZ, snEndZ);

				int iCount = 0;
				int tret = GetEmptyMobGrid(conn,&tx,&ty);
				if	(tret==FALSE)
				{	
					tx = GetRandom(snStartX, snEndX);
					ty = GetRandom(snStartZ, snEndZ);

					tret = GetEmptyMobGrid(conn,&tx,&ty);
					while( FALSE == tret )
					{
						++iCount;
						if( 5 < iCount ) 
						{
							char temp[256];sprintf(temp,"err no empty space at move portal x:%d y:%d",tx,ty);
							Log(temp,pUser[conn].AccountName,pUser[conn].IP);
							Log("err too many people near start point => 30",pUser[conn].AccountName,pUser[conn].IP);
							sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
							pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
							return;
						}
						tx = GetRandom(snStartX, snEndX);
						ty = GetRandom(snStartZ, snEndZ);
						tret = GetEmptyMobGrid(conn,&tx,&ty);
					}
				}

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm)-sizeof(HEADER);
				nm.TargetX=tx; nm.TargetY= ty;
				nm.dwKeyID = conn; nm.PosX=0; nm.PosY=0;
				nm.Direction = 0; nm.Effect = 5;

				if  (pUser[conn].Mode!=USER_PLAY) return;
				if  ( 0 >= pMob[conn].MOB.nHP ) return;

				///////////////////////////////// 4096 4096 외부 체크 /////////////////////////////////////////////////
				if  (tx<=0 || tx>=MAX_GRIDX ||ty<=0 || ty>=MAX_GRIDY)
				{	Log("err action - viewgrid",pMob[conn].MOB.szName,pUser[conn].IP);
					sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); return;
				}
	
				pUser[conn].LastAction = m->dwClientTick;
				int lastx = tx;
				int lasty = ty;
				pMob[conn].m_iDirection	= 0;
				pMob[conn].State		= 1;
				pMob[conn].DecGold(iFee);

				sprintf(temp,"dbg char:%s move portal x:%d y:%d",pMob[conn].MOB.szName,nm.TargetX,nm.TargetY);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);

				//pMob[conn].TargetX		= snX;
				//pMob[conn].TargetY		= snZ;
				pUser[conn].nPreX = tx;
				pUser[conn].nPreY = ty;
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
				GridMulticast(conn,tx,ty,(MSG_STANDARD*)&nm, 100, ACTION_WARP);

				MSG_Money_Move mm; mm.wType=_MSG_Money_Move;			//	포탈이용으로 인한 돈의 감소를 알린다.
				mm.byFromPlace=ITEM_PLACE_PORTAL; mm.byToPlace=ITEM_PLACE_INVEN;
				mm.dwFromMoney=0; mm.dwToMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)&mm, sizeof(MSG_Money_Move));

				//// 30초 동안 PK에 적용이 안되게 한다.
				//TNEFFECT kEffect;
				//kEffect.iID = eTNAfn_ProtectFromPK;
				//kEffect.iDuration = 15000;
				//pMob[conn].AddEffect( kEffect, conn, conn );

			}	else
			{	if  (ServerDown!=-1000)
				{	SendClientMessage(conn,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
					return;
				}

				sprintf(temp,"dbg char:%s move portal to other zone:%d",pMob[conn].MOB.szName,byMoveZone);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);

				//	토탈이동시 
				pMob[conn].DecGold(iFee);

				pMob[conn].m_kWaitAction.iAction = eWaitAct_ZonePortal;

				sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
				sm.byZone=byMoveZone; sm.nMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
				pMob[conn].m_eFSM = eTNFsm_Stand;
				pMob[conn].m_kLastTime.uiSitted = 0;
			}
		}	break;
	case _MSG_Action:		// 이동, 텔레포트
		{	
			if( eTNVSAfn_DontMove & pMob[conn].m_iAffections ) break;
			
			if( eWaitAct_TownPortal  == pMob[conn].m_kWaitAction.iAction ) 
			{
				char pch[256] = {0,};
				sprintf(pch, "Char:%s pustica is stopped by moving", pMob[conn].MOB.szName);
				Log(pch, pUser[conn].AccountName, pUser[conn].IP);

				pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
			}
			//if( eWaitAct_TownPortal2 == pMob[conn].m_kWaitAction.iAction ) return;	//	워프중이므로 다른 이동을 할수 없다
			//if( eWaitAct_TownPortal2 == pMob[conn].m_kWaitAction.iAction ) pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
			//if( eWaitAct_TownPortal3 == pMob[conn].m_kWaitAction.iAction ) return;	//	워프중이므로 다른 이동을 할수 없다
			if( eWaitAct_SummonParty == pMob[conn].m_kWaitAction.iAction ) pMob[conn].m_kWaitAction.iAction = eWaitAct_None;

			MSG_Action * m = (MSG_Action *) msg;
			if( pUser[conn].Mode != USER_PLAY ) {SendHpMode(conn);return;}
			if( 0 >= pMob[conn].MOB.nHP )
			{
				if( 50 < pMob[conn].m_iHPProblem )
				{
					int iKiller = pMob[conn].m_iKiller;
					char szKiller[128] = { 0,0,0, };
					if( 0 >= iKiller || MAX_MOB <= iKiller )
					{
						iKiller = 0;
						strcpy( szKiller, "Unknown" );
					}
					else
					{
						strcpy( szKiller, pMob[iKiller].MOB.szName );
					}

					S_SCP_RESP_REMOVE_MOB sm;
					sm.wType = SCP_RESP_REMOVE_MOB; 
					sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
					sm.nID = conn;
					sm.byResult = 1; 
					sm.dwKillerID = iKiller;
					sm.byRemoveType = 0;
					sm.snTribe = pMob[iKiller].MOB.snTribe;
					strcpy( sm.szName, pMob[iKiller].MOB.szName );
					GridMulticast( pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, -1);

					#ifdef __TN_TOP_LOG__
					{
						//SYSTEMTIME st;
						//GetLocalTime( &st );

						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "[%d월%d일 %d시%d분%d초] SendHpMode > 누가(%d,%s) killer(%d, %s)에 의해 죽었다.\r\n"
							, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
							,conn, pMob[conn].MOB.szName, iKiller, szKiller ); 
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_OnKilled] );
					}
					#endif

					pMob[conn].m_iHPProblem = 0;
					return;
				}

				++pMob[conn].m_iHPProblem;
				return;

				/*
				SendHpMode(conn);
				S_SCP_RESP_REMOVE_MOB sm;
				sm.wType = SCP_RESP_REMOVE_MOB; 
				sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
				sm.nID = conn;
				sm.byResult = 1; 
				sm.dwKillerID = 0;
				sm.snTribe = pMob[0].MOB.snTribe;
				strcpy( sm.szName, pMob[0].MOB.szName );
				GridMulticast( pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, -1, 50 );
				return;
*/
			}

			//sprintf(temp,"%s (%d,%d) (%d,%d)",pMob[conn].MOB.szName, pMob[conn].TargetX,pMob[conn].TargetY,m->TargetX,m->TargetY);
			//Log(temp,"record",0);

			
			unsigned int tick = m->dwClientTick;
			m->dwKeyID = conn;
			/*
			unsigned int	min;
			if	(CurrentTime>120000) min = CurrentTime-120000;  else min=0;
			//////////////////////// 액션 타임체크 ///////////////////////////////////////////////
			if	(pUser[conn].LastActionTick!=SKIPCHECKTICK && tick<pUser[conn].LastActionTick+900)
			{	sprintf(temp,"err action %d %d 900ms limit",tick,pUser[conn].LastActionTick);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				AddCrackError(conn,1,103);
				return;
			}
			
			if  (tick>CurrentTime+15000 || tick<min)
			{   sprintf(temp,"err action %d %d 15000ms limit",tick,CurrentTime);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				Log("err action faster than 15 sec - MSG_ACTION",pUser[conn].AccountName,pUser[conn].IP);
				AddCrackError(conn,1,102);
				return;
			}
			*/
		    pUser[conn].LastActionTick = tick;
			//////////////////////// 속도 체크 ///////////////////////////////////////////////
			//if	(m->Speed>pMob[conn].m_snCurMovingSpeed)
			//{	m->Speed = pMob[conn].m_snCurMovingSpeed;
			//	AddCrackError(conn,5,4);
			//	Log("etc diffrent movement.",pUser[conn].AccountName,pUser[conn].IP);
			//}
			//////////////////////// 텔레포트가 아닌데 거리가 큰경우 ///////////////////////////////////////////////
			int ix = pMob[conn].TargetX;
			int iy = pMob[conn].TargetY;
			int iDist = pMob[conn].m_iMoveSpeed + 2;
			if  (m->Effect!=1 && m->Effect!=2 && (m->TargetX<ix-g_iViewGridX || m->TargetX>ix+g_iViewGridX ||m->TargetY<iy-g_iViewGridY || m->TargetY>iy+g_iViewGridY))
			{	if	(m->TargetX < ix-(g_iHalfGridX) || m->TargetX>ix+(g_iHalfGridX) || m->TargetY<iy-(g_iHalfGridY) || m->TargetY>iy+(g_iHalfGridY) )
				{	// 거기가 멀면 강제로 원래 위치로 보정
					Teleport( conn, ix, iy );
					//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
					//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return;
				}
				else
				{	// 작으면 벌점추가
					AddCrackError(conn,1,CRACK_SPEED_HACK1);
				}
			}
/*
			HS2D_COORD kSrc, kDest;
			kSrc.x = ix;
			kSrc.y = iy;
			kDest.x = m->TargetX;
			kDest.y = m->TargetY;
			int iMoveDist = CalDistance( kSrc, kDest, 0, 0 );
			int iRes = pMob[conn].CheckMoveHack( iMoveDist, pMob[conn].m_iMoveSpeed, CurrentTime );
*/
			//int iRes = pMob[conn].CheckMoveHack( m->Effect );
			//if( iRes ) AddCrackError( conn, iRes, CRACK_SPEED_HACK2 ); // speed hack이다.

/*
			if  (m->Effect!=1 && m->Effect!=2 && (m->TargetX<ix-g_iViewGridX || m->TargetX>ix+g_iViewGridX ||m->TargetY<iy-g_iViewGridY || m->TargetY>iy+g_iViewGridY))
			{	if	(m->TargetX < ix-(g_iHalfGridX) || m->TargetX>ix+(g_iHalfGridX) || m->TargetY<iy-(g_iHalfGridY) || m->TargetY>iy+(g_iHalfGridY) )
				{	// 거기가 멀면 강제로 원래 위치로 보정
					Teleport( conn, ix, iy );
					//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
					//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return;
				}	else
				{	// 작으면 벌점추가
					AddCrackError(conn,1,5);
				}
			}
*/
			///////////////////////////////// 4096 4096 외부 체크 /////////////////////////////////////////////////
			if  (m->TargetX<=0 || m->TargetX>=MAX_GRIDX ||m->TargetY<=0 || m->TargetY>=MAX_GRIDY)
			{	Log("err action - viewgrid",pMob[conn].MOB.szName,pUser[conn].IP);
				return;
			}

			if( 0 == m->Effect )
			{
				#ifdef __TN_PLAYMOVIE__
				return;
				#endif
				pMob[conn].m_eFSM = eTNFsm_Sit;
				pMob[conn].m_kLastTime.uiSitted = timeGetTime();
			}
			else if( 1 == m->Effect )
			{
				pMob[conn].m_eFSM = eTNFsm_Stand;
				pMob[conn].m_kLastTime.uiSitted = 0;
			}
		
			//if	(m->TargetX==pMob[conn].TargetX && m->TargetY==pMob[conn].TargetY)   return;  // 제자리면 무시
			///////////////////////////////// 초보존 체크 /////////////////////////////////////////////////////////
			//unsigned char Att = GetAttribute(m->TargetX,m->TargetY);
			//if	(Att&ATT_NEWBIE && pMob[conn].MOB.CurrentScore.Level>=35 && pMob[conn].MOB.CurrentScore.Level<=999)
			//{	SendClientMessage(conn,g_pMessageStringTable[_NN_Newbie_zone]);
			//	m->TargetX = pMob[conn].TargetX;
			//	m->TargetY = pMob[conn].TargetY;
			//	m->Route[0]= 0;
			//	pUser[conn].cSock.AddMessage((char*)m,m->Size);
			//	return;
			//}
			///////////////////////////// 이하 실제 MSG_ACTION /////////////////////////////////////////////////
			//if  (pMob[conn].MOB.Class==3) DoRemoveHide(conn);

			if( eTNCell_PCNotAllowed/*eTNCell_SealedZone*/ & g_krgCell[m->TargetY][m->TargetX].usProperty ) // 이동할 수 없는 지역이다.
			{
				Teleport( conn, ix, iy );
				//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
				//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
				return;
			}

			if	(pMobGrid[m->TargetY][m->TargetX]!=0 && pMobGrid[m->TargetY][m->TargetX] != conn)
			{	int x=m->TargetX;
				int y=m->TargetY;

				int tret = GetEmptyMobGrid(conn,&x,&y);
				if(tret==FALSE)
				{	sprintf(temp,"err can't move x:%d y:%d",x,y);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					// 거기가 멀면 강제로 원래 위치로 보정
					Teleport( conn, ix, iy );
					//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
					//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return;
				}
				m->TargetX = x;
				m->TargetY = y;
				pUser[conn].cSock.AddMessage((char*)m,sizeof(*m));
			}

			pUser[conn].LastAction = m->dwClientTick;
			int self=0;
			int lastx = m->TargetX;
			int lasty = m->TargetY;
			pMob[conn].Direction	= m->Direction;
			pMob[conn].State		= m->Effect;
			/*
			char lastroute[256];
			strcpy((char*)lastroute,(char*)m->Route);
			if	(pMobGrid[m->TargetY][m->TargetX]!=0&&pMobGrid[m->TargetY][m->TargetX]!=conn)
			{	int x=m->TargetX;
				int y=m->TargetY;
				int distance=strlen((char*)m->Route);
				for (int dis=distance;dis>=0;dis--) 
				{   BASE_GetRoute(m->PosX,m->PosY,&x,&y,(char*)m->Route,dis,(short**)pHeightGrid);
					if (pMobGrid[m->TargetY][m->TargetX]==0 || pMobGrid[m->TargetY][m->TargetX]==conn) break;
				}
				if	(dis==-1) // 이동가능지가 없으므로 원상 복귀를  conn만 날려준다.
				{	m->TargetX = pMob[conn].TargetX;
					m->TargetY = pMob[conn].TargetY;
					m->Route[0]= 0;
					pUser[conn].cSock.AddMessage((char*)m,m->Size);
					return;
				}
				m->TargetX = x;
				m->TargetY = y;
				pUser[conn].cSock.AddMessage((char*)m,m->Size);
			}
			memcpy(pMob[conn].Route,m->Route,sizeof(m->Route));
			int len = strlen(pMob[conn].Route);
			unsigned char dir = 0;
			if  (len>0&&len<MAX_ROUTE)
			{   dir = pMob[conn].Route[len-1];
				dir=dir-48;
				if (dir>=1 && dir<=9) dir=(dir<<4);
				else dir = 0; 
			}
			*/

			pMob[conn].m_kLastTime.uiMoved = CurrentTime;
			pMob[conn].LastX = pMob[conn].TargetX;
			pMob[conn].LastY = pMob[conn].TargetY;

			GridMulticast(conn,m->TargetX,m->TargetY,(MSG_STANDARD*)msg,50);
			pUser[conn].cSock.SendMessage();
			//pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			if( 0 < g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent )
			{ // cell 에 event 가 등록되어 있을 경우, ...
/*
				S_SCP_RESP_WHISPER_CHAT kMsg; 
				kMsg.wType = SCP_RESP_WHISPER_CHAT;	
				kMsg.byResult = REPLY_ACK_OK;
				strncpy( kMsg.szName, "System", SZNAME_LENGTH );
				kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	

				char szResult[1024] = { 0,0,0, };
				sprintf( szResult, "Event ID:%d", g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent );
				strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
				pUser[conn].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
*/
				TriggerEvent( conn, g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent, pMob[conn].TargetX, pMob[conn].TargetY, 0, 10 );
			}

			// retainer 부르기
			pMob[conn].CallRetainer();
			pMob[conn].CallRobot();

			// follower들이 쫓아가기
			HS2D_COORD kPos;
			kPos.x = m->TargetX;
			kPos.y = m->TargetY;
			for( int iFollowerIndex = 0; iFollowerIndex < eFollower_MaxCount; ++iFollowerIndex )
			{
				int iFollower = pMob[conn].m_irgFollower[iFollowerIndex];
				if( MAX_USER > iFollower || MAX_MOB <= iFollower ) break; // NPC만 follower가 될 수 있다.
				if( pMob[iFollower].IsDead() ) continue;

				pMob[iFollower].OnFollow( conn );
			}

			// 버스타기
			int iPassenger = pMob[conn].m_iPassenger;
			if( 0 < iPassenger && MAX_USER > iPassenger ) // PC인 경우만 passenger가 될 수 있다.
			{			
				int x=m->TargetX;
				int y=m->TargetY;

				int tret = GetEmptyMobGrid( iPassenger, &x, &y );
				if( tret)
				{
					m->dwKeyID = iPassenger;
					m->Speed = pMob[iPassenger].m_iMoveSpeed;
					m->Effect = 4; // run
					m->TargetX = x;
					m->TargetY = y;
					pUser[iPassenger].cSock.AddMessage((char*)m,sizeof(*m));
					pUser[iPassenger].cSock.SendMessage();
				}		
			}
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_QUEST_NOTIFY_LEVEL:
		{	S_CSP_QUEST_NOTIFY_LEVEL *m = (S_CSP_QUEST_NOTIFY_LEVEL*)msg;
			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	해당 NPC정보를 읽지 못할경우.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC와 같은 존에 있지 않은 경우.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid내에 플레이어가 없을 경우
			QUEST_OnEvent(conn,m->snNPCIndex,m->snNPCIndex,0,FALSE);
		} break;
	case CSP_QUEST_DIALOG:
		{	S_CSP_QUEST_DIALOG *m = (S_CSP_QUEST_DIALOG*)msg;
			QUEST_OnDialog(conn,m->snDialog,m->byResult);
		}break;
	case _MSG_Quest:
		{	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)msg;
			QUEST_OnTask(conn,m->nID,m->Parm);
		}break;
	case _MSG_UseItem:
		{	
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case _MSG_Imple: // Imple의 Whisper의 스트럭쳐를 쓴다.
		{
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
 	case _MSG_UpdateItem:	// 문열기, 스위치 켜기등등
		{		
		}     break; 
///////////////////////////////////////////////////////////////////////////////////////////////
    case CSP_REQ_TRADE_CANCEL:	// 1:1 거래 종료
		{	    
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			//	if  (pMob[conn].MOB.nHP==0 || pUser[conn].Mode!=USER_PLAY)
			//  {   //SendRemoveMob(conn,conn,0,1);
			//	     SendHpMode(conn);
			//       AddCrackError(conn,10,17);
			//       return;
			//  }
            int Target = pUser[conn].Trade.OpponentID;
			RemoveTrade(conn, REPLY_TRADE_USER_DENAY);
			RemoveTrade(Target, REPLY_TRADE_USER_DENAY);
		}     break;
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_TRADE:
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, trade를 할 수 없다.
			MSG_Trade *m = (MSG_Trade *) msg;

			if  ((0 >= pMob[conn].MOB.nHP) || (pUser[conn].Mode!=USER_PLAY))
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_TRADE);
				return;
			}

			//////////////////////// msg packet의 무결성 검사//////////////
			int	target = m->OpponentID;
			if	(target<=0||target>=MAX_USER)
			{	Log("err msg_trade - target out of bound.",pUser[conn].AccountName,pUser[conn].IP);
				//	SendClientMessage(conn,g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
				RemoveTrade(conn, REPLY_TRADE_OUTINDEX);
				return;
			}
   			if	(0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{	//	SendRemoveMob(conn,conn,0,1);
				//	SendHpMode(conn);
				//	AddCrackError(conn,5,18);
				RemoveTrade(conn, REPLY_TRADE_USER_DIE);
				//RemoveTrade(target, REPLY_TRADE_USER_DIE);
				return;
			}
			if  (pUser[target].Mode!=USER_PLAY)
			{	RemoveTrade(conn,REPLY_TRADE_ERROR);
				return;
			}
			if	(m->TradeMoney<0 || m->TradeMoney > pMob[conn].MOB.nRupiah) 
			{	if(m->TradeMoney==-1)	//	거래거부를 할경우 클라이언트에서 -1을 넣어서 보내기로 한다.
				{	RemoveTrade(conn, REPLY_TRADE_USER_DENAY);
					RemoveTrade(target, REPLY_TRADE_USER_DENAY); return;
				}
				RemoveTrade(conn, REPLY_TRADE_ERROR);
				RemoveTrade(target, REPLY_TRADE_ERROR); return;
			}
			if(conn==target || !strncmp(pUser[conn].AccountName, pUser[target].AccountName, ACCOUNTNAME_LENGTH))
			{
				AddCrackError(conn,30,CRACK_MOBSTORE_SELF); return;
			}

			// 자신이 제안한 아이템이 정당한가 체크
			for (int k=0;k<MAX_TRADE;k++)
			{	
                if	(m->Item[k].snIndex!=0)
				{	// 포지션과 창고 내용이 틀리면, return;
					int cg = m->InvenPos[k];		if	(cg<0||cg>=pMob[conn].byMaxInven) return;
					int	ret = memcmp(&(pMob[conn].MOB.Inven[cg]),&(m->Item[k]),sizeof(STRUCT_ITEM));
					if ( CHTParamIDCheck::HT_bIsItemQuestOnly( m->Item[k].snIndex + HT_PARAMTYPE_ITEM_START - 1 ) ) ret |= 1;
					if (ret!=0)	 
					{	Log("err msg_trade - item remove or changed.",pUser[conn].AccountName,pUser[conn].IP);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
				}
				if	(pUser[target].Trade.Item[k].snIndex!=0)
				{	int cg = pUser[target].Trade.InvenPos[k];		
					if	(cg<0||cg>=pMob[target].byMaxInven) return;
					int ret = memcmp(&(pMob[target].MOB.Inven[cg]),&(pUser[target].Trade.Item[k]),sizeof(STRUCT_ITEM));
					if ( CHTParamIDCheck::HT_bIsItemQuestOnly( pUser[target].Trade.Item[k].snIndex + HT_PARAMTYPE_ITEM_START - 1 ) ) ret |= 1;
					if (ret!=0)	 
					{	Log("err msg_trade - item remove or changed.",pUser[conn].AccountName,pUser[conn].IP);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
				}
			}

			////////////////////// 상대의 거래상태 체크 - 상대가 다른 사람과 거래중인가 
			int UserTarget = pUser[conn].Trade.OpponentID;
			// 기거래 상대가 자신인경우 아이템과 돈 체크. 아닐경우는 반드시 0이어야 거래 성립.
			if	(UserTarget==target ) 
			{
				for (int k=0;k<MAX_TRADE;k++)
				{	
					int err = 0;
					if	(pUser[conn].Trade.Item[k].snIndex!=0) {err = memcmp(&(pUser[conn].Trade.Item[k]),&(m->Item[k]),sizeof(STRUCT_ITEM));}
					if	(err)  
					{	Log("err msg_trade - item remove or changed.",pUser[conn].AccountName,pUser[conn].IP);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
				}
			}	else
			{
				if	(UserTarget!=0)
				{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Already_Trading]);
					RemoveTrade(conn, REPLY_TRADE_ERROR);
					return;
				}
			}

			// 1. 상대의 OpponentID가 0 이면 자신만 오퍼넌트를 상대로 세팅하고 거래 패킷만 넘김.
			if	(pUser[target].Trade.OpponentID==0)
			{	pUser[conn].Trade = *m;
				pUser[conn].Trade.MyCheck = 0;
				pUser[conn].Trade.TradeMoney = 0;
				// 오퍼넌트는 자동 세팅.
				m->nID         = target;
				m->OpponentID = conn;
				strncpy(m->szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				pUser[target].cSock.AddMessage((char*)m,sizeof(*m));
				pUser[target].Trade.MyCheck = 0;
				pUser[target].Trade.TradeMoney = 0;
				return; 
			}

			if	(pUser[target].Trade.OpponentID!=conn)
			{   //	SendClientMessage(conn,g_pMessageStringTable[_NN_Already_Trading]);
				RemoveTrade(conn, REPLY_TRADE_USER_CHANGE);
				return;
			}

            for (int p=0;p<MAX_TRADE;p++)
			{
				int CarryPos = m->InvenPos[p];
				if	(CarryPos==-1)
				{   memset(&(m->Item[p]),0,sizeof(STRUCT_ITEM));
					continue;
				}
				if	(CarryPos<-1 || CarryPos >= pMob[conn].byMaxInven)
				{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
				    RemoveTrade(conn, REPLY_TRADE_ERROR);
				    return;
				}
				for (int u=0;u<MAX_TRADE;u++)
				{   if (u==p) continue;
				    if (CarryPos == m->InvenPos[u])
					{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
					    RemoveTrade(conn, REPLY_TRADE_ERROR);
					    return;
					}
				}
                m->Item[p] = pMob[conn].MOB.Inven[CarryPos];
			}
			// 상대가 이미 자신과 거래중인경우. 상대의 MyCheck==1 이고 m->MyCheck==1 이면 바로 거래.
		    
            if  (m->MyCheck==1)
			{	pUser[conn].Trade.MyCheck=1;
				//pUser[conn].Trade.KeyWord  = m->KeyWord;
				//pUser[conn].Trade.CheckSum = m->CheckSum;
				pUser[conn].Trade.wSeq = m->wSeq;
				pUser[conn].Trade.dwClientTick =   m->dwClientTick;
				int ret = memcmp(&pUser[conn].Trade,m,sizeof(MSG_Trade));
				if  (ret) // 체크버튼 클릭 실패 양쪽다 거래 취소.
				{	RemoveTrade(conn, REPLY_TRADE_ERROR);
					RemoveTrade(target, REPLY_TRADE_ERROR);
					Log("err msg_trade - Click check button but diffrent data",pUser[conn].AccountName,pUser[conn].IP);
					return;
				} 
				if (pUser[target].Trade.MyCheck==1)
				{
					// 거래성사.
					if	(pUser[conn].Trade.TradeMoney<0||pUser[conn].Trade.TradeMoney>200000000)
					{	RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
					if	(pUser[target].Trade.TradeMoney<0||pUser[target].Trade.TradeMoney>200000000)
					{	RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}

					int conncoin = pMob[conn].MOB.nRupiah - pUser[conn].Trade.TradeMoney + pUser[target].Trade.TradeMoney;
					if	(conncoin>MAX_INT || conncoin<0)
					{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
					int tarcoin = pMob[target].MOB.nRupiah - pUser[target].Trade.TradeMoney + pUser[conn].Trade.TradeMoney;
					if	(tarcoin>MAX_INT || tarcoin<0)
					{	//	SendClientMessage(target,g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}

					if (pUser[conn].Trade.TradeMoney>pMob[conn].MOB.nRupiah)
					{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Havent_Money_So_Much]);
                        //	SendClientMessage(target,g_pMessageStringTable[_NN_Opponent_Havent_Money]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
						return;
					}
					if (pUser[target].Trade.TradeMoney>pMob[target].MOB.nRupiah)
					{	//	SendClientMessage(target,g_pMessageStringTable[_NN_Havent_Money_So_Much]);
                        //	SendClientMessage(conn,g_pMessageStringTable[_NN_Opponent_Havent_Money]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
                        return;
					}
					int ret1 = BASE_CanTrade(pMob[conn].MOB.Inven,pMob[conn].byMaxInven,pUser[conn].Trade.Item,pUser[target].Trade.Item);
                    int ret2 = BASE_CanTrade(pMob[target].MOB.Inven,pMob[target].byMaxInven,pUser[target].Trade.Item,pUser[conn].Trade.Item);
					if  (ret1==0 && ret2==0)
					{   //	SendClientMessage(conn,g_pMessageStringTable[_NN_Each_Of_You_Havent_Space]);
                        //	SendClientMessage(target,g_pMessageStringTable[_NN_Each_Of_You_Havent_Space]);
						RemoveTrade(conn, REPLY_TRADE_OVER_ME);
						RemoveTrade(target, REPLY_TRADE_OVER_ME);
						return;
					}   else
					if (ret1==0)
					{   //	SendClientMessage(conn,g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
                        //	SendClientMessage(target,g_pMessageStringTable[_NN_Opponent_Have_No_Space_To]);
						RemoveTrade(conn, REPLY_TRADE_OVER_ME);
						RemoveTrade(target, REPLY_TRADE_OVER_YOU);
						return;
					}   else
					if (ret2==0)
					{   //	SendClientMessage(conn,g_pMessageStringTable[_NN_Opponent_Have_No_Space_To]);
                        //	SendClientMessage(target,g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
						RemoveTrade(conn, REPLY_TRADE_OVER_YOU);
						RemoveTrade(target, REPLY_TRADE_OVER_ME);
						return;
					}   

					int iHap1 = pUser[target].Trade.TradeMoney + pMob[conn].MOB.nRupiah;
					int iHap2 = pUser[conn].Trade.TradeMoney + pMob[target].MOB.nRupiah;
					if(iHap1<0 || iHap1>MAX_INT || iHap2<0 || iHap2>MAX_INT)
					{
						RemoveTrade(conn, REPLY_TRADE_OVER_YOU);
						RemoveTrade(target, REPLY_TRADE_OVER_ME);
						return;
					}

					pMob[conn].DecGold(pUser[conn].Trade.TradeMoney);
					pMob[conn].IncGold(pUser[target].Trade.TradeMoney);
					pMob[target].DecGold(pUser[target].Trade.TradeMoney);
					pMob[target].IncGold(pUser[conn].Trade.TradeMoney);

					// Trade 로그
					int money1 = pUser[conn].Trade.TradeMoney;
					int money2 = pUser[target].Trade.TradeMoney;
					int nn1=0;
					int nn2=0;
					if(money1>0) nn1 = 1;
					if(money2>0) nn2 = 1;

					char strItem[128];
					char logtemp[1024];
					temp[0] = 0;
					for	(int i=0;i<MAX_TRADE;i++)
					{	if (pUser[conn].Trade.Item[i].snIndex == 0 ) continue;
						BASE_GetItemCode(&pUser[conn].Trade.Item[i],strItem);
						strcat(temp," "); strcat(temp,strItem);
						nn1 = 1;
					}
					if( nn1 )
					{	sprintf(logtemp,"tra give %s %d %s", pUser[target].AccountName, money1, temp);
						Log(logtemp,pUser[conn].AccountName,pUser[conn].IP);
						sprintf(logtemp,"tra receive %s %d %s", pUser[conn].AccountName, money1, temp);
						Log(logtemp,pUser[target].AccountName,pUser[target].IP);
					}
                    
					memset(strItem, 0, sizeof(strItem));
					memset(temp, 0, sizeof(temp));
					for	( i=0;i<MAX_TRADE;i++)
					{	if (pUser[target].Trade.Item[i].snIndex == 0 ) continue;
						BASE_GetItemCode(&pUser[target].Trade.Item[i],strItem);
						strcat(temp," "); strcat(temp,strItem);
						nn2 = 1;
					}
					if( nn2 )
					{	sprintf(logtemp,"tra give %s %d %s", pUser[conn].AccountName, money2, temp);
						Log(logtemp,pUser[target].AccountName,pUser[target].IP);
						sprintf(logtemp,"tra receive %s %d %s", pUser[target].AccountName, money2, temp);
						Log(logtemp,pUser[conn].AccountName,pUser[conn].IP);
					}		

					ExchangeTrade(conn, target);

					RemoveTrade(conn, REPLY_TRADE_SUCCESS);
					RemoveTrade(target, REPLY_TRADE_SUCCESS);
					return;
				}   else
				{   // 아니면 전달. Check를 제거하지는 않는다.
					//	SendClientSignal( conn,conn,_MSG_CNFCheck); // 본인한테 콜백 
   				    m->nID         = target;
				    m->OpponentID = conn;
				    pUser[target].cSock.AddMessage((char*)m,sizeof(*m)); // 상대에게 전달.
                    return;
                    // 오퍼넌트가 Check이면 거래성사 아니면 메시지 넘기기.
				}
			}
			pUser[conn].Trade = *m;
			pUser[conn].Trade.MyCheck = 0;
			pUser[target].Trade.MyCheck = 0;
			m->nID         = target;
			m->OpponentID = conn;
			pUser[target].cSock.AddMessage((char*)m,sizeof(*m));
		}	break;///////////////////////////////////////////////////////////////////////////////////////////////
	case _MSG_MobStore:
		{	MSG_MobStore* m = (MSG_MobStore*)msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_MONSTORE);
				return;
			}

			if(!ChatFilter(m->szTrade) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			int nID = m->nID;
			if(nID<=0 || nID>=MAX_USER) return;

			if(nID==conn)			//	자신의 거래모드 세팅
			{	if(pUser[conn].byTradeMode==m->byMode) 
				{	SendClientMessage(conn, g_pMessageStringTable[_MobStore_Set_Already]); return;
				}
						
				if(m->byMode != 0)
				{	time_t now; time(&now);
					bool bCash = true;
					if(now>(int)pUser[conn].m_time[eTime_Store] || pUser[conn].m_snTimeMode&0x4000) bCash=false;

					for(int i=0; i<MAX_MOBSTORE; i++)					//	item 유효성검사
					{	int nIndex=m->TradeItem[i].nIndex;
						if(nIndex<-1 || nIndex>=pMob[conn].byMaxInven) {SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Index]); return;}
						if(m->TradeItem[i].nIndex==-1 || m->TradeItem[i].item.snIndex==0) continue;
						STRUCT_ITEM* pSour = &(pMob[conn].MOB.Inven[nIndex]);
						STRUCT_ITEM* pDest = &(m->TradeItem[i].item);

						bool bRet=false;
						for(int k=0; k<MAX_MOBSTORE; k++)	
						{
							if(i==k) continue;						//	동일한 판매물건의 비교는 의미가 없다
							if(nIndex==m->TradeItem[k].nIndex)		//	동일한 물건을 2회이상 올렷을 경우-개인상점 오픈불가
							{	bRet = true;
								break;
							}
						}
						if(bRet) {SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Data]); return;}

						while(1)
						{	if(pSour->snIndex!=pDest->snIndex) break;
							if(pSour->byRefineLevel!=pDest->byRefineLevel ) break;
							if(memcmp(pSour->bySubRefine, pDest->bySubRefine, sizeof(BYTE)*MAX_SUBMATERIALSIZE)) break;
							if(m->TradeItem[i].item.snIndex!=0 && i>=MAX_MOBSTORE/2 && !bCash) break;	//	비유료이고 사용할수 없는 영역에 인덱스를 채울경우
							if(pDest->byCount>pSour->byCount) break;
							bRet=true; break;
						}
						if(!bRet) {SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Data]); return;}
					}
				}

				pUser[conn].byTradeMode=m->byMode;
				if(m->byMode==0)						//	거래모드 해제
				{	memset(pUser[conn].TradeItem, 0, sizeof(pUser[conn].TradeItem));
					memset(pUser[conn].szTrade, 0, SZTRADE_LENGTH);
				}	else									//	거래모드 설정
				{	memcpy(pUser[conn].TradeItem, m->TradeItem, sizeof(pUser[conn].TradeItem));
					strncpy(pUser[conn].szTrade, m->szTrade, SZTRADE_LENGTH);
				}
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

				MSG_MobStatus sm; sm.wType=_MSG_MobStatus;
				sm.wPDULength=sizeof(MSG_MobStatus)-sizeof(HEADER);
				sm.nID=conn;	sm.byTradeMode=m->byMode;
				strncpy(sm.szTrade, pUser[conn].szTrade, SZTRADE_LENGTH);
				int tx = pMob[conn].TargetX;
				int ty = pMob[conn].TargetY;
				GridMulticast(tx,ty,(MSG_STANDARD*)&sm,conn,50);
			}	else					//	상대의 거래아이템을 알아옴
			{	if(pUser[nID].byTradeMode==0) {SendClientMessage(conn, g_pMessageStringTable[_MobStore_No_Mode]); break;}
				m->byMode=1;	
				memcpy(m->TradeItem, pUser[nID].TradeItem, sizeof(m->TradeItem));
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
			}
		}	break;
	case _MSG_MobStore_Buy:
		{	MSG_MobStore_Buy* m = (MSG_MobStore_Buy*)msg;

			int nID = m->nID;
			if(nID<=0 || nID>=MAX_USER) return;
			if(pUser[nID].byTradeMode==0) {SendClientMessage(conn, g_pMessageStringTable[_MobStore_No_Mode]); return;}
			if(conn==nID || !strncmp(pUser[conn].AccountName, pUser[nID].AccountName, ACCOUNTNAME_LENGTH))
			{	AddCrackError(conn,30,CRACK_MOBSTORE_SELF); return;
			}

			byte byRet = 0; int nTotMoney = 0; int nCount = 0;
			for(int i=0; i<MAX_MOBSTORE; i++)
			{	if(m->byIndex[i]!=1) continue;							//	1이 아닐경우는 안사는 물건임.
				if(pUser[nID].TradeItem[i].item.snIndex==0) { byRet = _Invalid_Item_Data; break; }		//	사려구 했으나 이미 팔린경우.
				nTotMoney += pUser[nID].TradeItem[i].nPrice;

				int nIndex=pUser[nID].TradeItem[i].nIndex;
				if(nIndex<0 || nIndex>=pMob[nID].byMaxInven) { byRet = _Invalid_Item_Data; break; }
				nCount++;
			}
			if(GetEmptyInvenCount(conn)<nCount) byRet = _Inventory_Space_Lack;

			if(byRet>0)
			{	for(int i=1; i<MAX_MOBSTORE; i++) m->byIndex[i]=0;
				SendClientMessage(conn, g_pMessageStringTable[byRet]);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			for(int i=0; i<MAX_MOBSTORE; i++)
			{	if(m->byIndex[i]!=1) continue;							//	1이 아닐경우는 안사는 물건임.
				if(pUser[nID].TradeItem[i].item.snIndex==0) { m->byIndex[i]=0; continue; }		//	사려구 했으나 이미 팔린경우.

				int nMoney = pUser[nID].TradeItem[i].nPrice;
				if(pMob[conn].MOB.nRupiah<nMoney) { m->byIndex[i]=0; continue; }			//	돈이 부족할 경우

				int nEmptyInven = GetEmptyInven(conn);
				if(nEmptyInven == MAX_INVEN) // 빈자리 체크
				{	for(int j=i; j<MAX_MOBSTORE; j++) m->byIndex[j]=0;
					SendClientMessage(conn, g_pMessageStringTable[_Inventory_Space_Lack]);	
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
				}

				int nIndex=pUser[nID].TradeItem[i].nIndex;
				if(nIndex<0 || nIndex>=pMob[nID].byMaxInven) {m->byIndex[i]=0; continue;}

				if(pUser[nID].TradeItem[i].item.snIndex!=pMob[nID].MOB.Inven[nIndex].snIndex)					//	사려구 했으나 이미 팔린경우.
				{	ZeroMemory(&pUser[nID].TradeItem[i], sizeof(pUser[nID].TradeItem[i])); 
					m->byIndex[i]=0; continue; 
				}
				if(pUser[nID].TradeItem[i].item.byRefineLevel!=pMob[nID].MOB.Inven[nIndex].byRefineLevel)		//	사려구 했으나 이미 팔린경우.
				{	ZeroMemory(&pUser[nID].TradeItem[i], sizeof(pUser[nID].TradeItem[i])); 
					m->byIndex[i]=0; continue; 
				}
				if(memcmp(pUser[nID].TradeItem[i].item.bySubRefine, pMob[nID].MOB.Inven[nIndex].bySubRefine, sizeof(BYTE)*MAX_SUBMATERIALSIZE)) 
				{	ZeroMemory(&pUser[nID].TradeItem[i], sizeof(pUser[nID].TradeItem[i]));						//	사려구 했으나 이미 팔린경우.
					m->byIndex[i]=0; continue;									
				}

				int iHap = pMob[nID].MOB.nRupiah + nMoney;
				if(iHap<0 || iHap>MAX_INT) {m->byIndex[i]=0; continue;}

				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byType = SET_ITEM_CREATE;	//	아이템 생성
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nEmptyInven;
				itemset.sitem = pMob[nID].MOB.Inven[nIndex];
				itemset.sitem.byCount = pUser[nID].TradeItem[i].item.byCount;
				pMob[conn].DecGold(nMoney);

				pMob[conn].MOB.Inven[nEmptyInven]=pMob[nID].MOB.Inven[nIndex];
				pMob[conn].MOB.Inven[nEmptyInven].byCount=pUser[nID].TradeItem[i].item.byCount;
				pUser[conn].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

				pMob[nID].IncGold(nMoney);

				// 개인상점은 무조건 로그로 남긴다.
				{	char szItemCode[128];
					BASE_GetItemCode(&itemset.sitem,szItemCode);
					sprintf(temp,"Store buy %s %s %d",pUser[nID].AccountName,szItemCode,nMoney);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					sprintf(temp,"Store sell %s %s %d",pUser[conn].AccountName,szItemCode,nMoney);
					Log(temp,pUser[nID].AccountName,pUser[nID].IP);
				}

				if(pMob[nID].MOB.Inven[nIndex].byCount>itemset.sitem.byCount) 
				{	pMob[nID].MOB.Inven[nIndex].byCount -= itemset.sitem.byCount;
				}	else
				{	memset(&(pMob[nID].MOB.Inven[nIndex]),0, sizeof(STRUCT_ITEM));
				}
				memset(&(pUser[nID].TradeItem[i]), 0, sizeof(MOBSTOREITEM));
			}

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	구입자에게 구입결과를 알린다

			int nRemain=0;
			for(int i=0; i<MAX_MOBSTORE; i++)
			{	if(pUser[nID].TradeItem[i].item.snIndex==0) m->byIndex[i]=0;
				else { m->byIndex[i]=1; nRemain++; }
			}
			pUser[nID].cSock.SendOneMessage((char*)m, sizeof(*m));		//	판매자에게 판매결과를 안린다.
			if(nRemain==0)												//	아이템이 전부 팔렷을 경우
			{	pUser[nID].byTradeMode=0;								//	판매자 및 판매자 주변에게 판매결과를 안린다.
				memset(pUser[nID].TradeItem, 0, sizeof(pUser[nID].TradeItem));
				//MSG_MobStore nm; nm.wType=_MSG_MobStore;				//	(판매자의 상인모드 해제는 client에서 하기로함)
				//nm.nID=nID; nm.byMode=0;
				//pUser[nID].cSock.SendOneMessage((char*)&nm, sizeof(nm));

				MSG_MobStatus sm; sm.wType=_MSG_MobStatus;
				sm.wPDULength=sizeof(MSG_MobStatus)-sizeof(HEADER);
				sm.nID=nID;	sm.byTradeMode=0;
				int tx = pMob[nID].TargetX;
				int ty = pMob[nID].TargetY;
				GridMulticast(tx,ty,(MSG_STANDARD*)&sm,nID,50);
			}
		}	break;
	case CSP_REQ_ITEM_MOVE:		// 장착, 인벤, 창고간 아이템 이동
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_MOVE * m = (S_CSP_REQ_ITEM_MOVE *) msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_MOVE);
				return;
			}

			STRUCT_ITEM prev = pMob[conn].MOB.Equip[14];
			STRUCT_ITEM *sour;     // SourType & DestType:   0: Equip
			STRUCT_ITEM *dest;     //                        1: Carry
			int CheckLook=0;
            //int nItemIndex;
			S_SCP_RESP_ITEM_MOVE sm; sm.wType=SCP_RESP_ITEM_MOVE;
			sm.byFromPlace=m->byFromPlace; sm.snFromIndex=m->snFromIndex; sm.nResult = 1;
			sm.byToPlace=m->byToPlace; sm.snToIndex=m->snToIndex;

			//	Packet 유효성검사  *item = &item
			bool bCheck=false;	int nItemIndex=0;	int nResult=0;
			while(1)
			{
				if(m->byFromPlace==ITEM_PLACE_GUILDCARGO || m->byToPlace==ITEM_PLACE_GUILDCARGO)
				{
					if ((ServerIndex+1) != SERVER_KATANA3) break;				//	길드창고는 카타나3에서만 이용가능
					int nGuildIndex = pUser[conn].nGuildIndex;
					if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) break;			//	길드없는 케릭이 요청시 
					WORD wCargo = 0;
					
					if(m->byFromPlace==ITEM_PLACE_GUILDCARGO)
						if(!pGuild[nGuildIndex].IsUsableCargo(pUser[conn].nGuildLevel, m->snFromIndex)) { sm.nResult=REPLY_ITEM_MOVE_RIGHT; break; }	//	사용권한이 없는 아쉬람창고일 경우
					if(m->byToPlace==ITEM_PLACE_GUILDCARGO)
						if(!pGuild[nGuildIndex].IsUsableCargo(pUser[conn].nGuildLevel, m->snToIndex)) { sm.nResult=REPLY_ITEM_MOVE_RIGHT; break; }	//	사용권한이 없는 아쉬람창고일 경우

					//if (strncmp(pGuild[nGuildIndex].szCargoMember, pMob[conn].MOB.szName, SZNAME_LENGTH) != 0)	//	사용권한이 없을경우
					//{
					//	Msg_GuildCargoUseUpdate nm; nm.wType = _Msg_GuildCargoUseUpdate;
					//	nm.nGuildID = pGuild[nGuildIndex].GUILD.GuildID;
					//	strncpy(nm.pUsingMember, pGuild[nGuildIndex].szCargoMember, SZNAME_LENGTH);
					//	pUser[conn].cSock.AddMessage((char*)&nm, sizeof(nm));
					//	break;
					//}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////-SOUR
				if  (m->byFromPlace == ITEM_PLACE_INVEN)
				{	if (m->snFromIndex<0||m->snFromIndex>=pMob[conn].byMaxInven) break;
					sour = &pMob[conn].MOB.Inven[m->snFromIndex];
				}   else
				if  (m->byFromPlace == ITEM_PLACE_EQUIP)
				{	if (m->snFromIndex<0||m->snFromIndex>=MAX_EQUIP) break;
					sour = &pMob[conn].MOB.Equip[m->snFromIndex];
					//if(m->snFromIndex==eTNEqu_Bag)
					//{	bool bRet = true;
					//	for(int i=pMob[conn].byMaxInven; i<MAX_INVEN; i++)
					//	{	if(pMob[conn].MOB.Inven[i].snIndex != 0) { bRet=false; break; }
					//	}
					//	if(!bRet) {nResult=REPLY_ITEM_MOVE_BAG; break;}
					//}
				}   else
				if  (m->byFromPlace == ITEM_PLACE_CARGO)
				{	if (m->snFromIndex<0||m->snFromIndex>=MAX_CARGO) break;
					sour = &pUser[conn].Cargo[m->snFromIndex];
				}	else
				if	(m->byFromPlace == ITEM_PLACE_GUILDCARGO)
				{	if (m->snFromIndex<0||m->snFromIndex>=(MAX_CARGO*3)) break;	//	정상적인 창고위치영역인지 체크
					sour = &pGuild[pUser[conn].nGuildIndex].GUILD.Repository[m->snFromIndex];
					if(sour->snIndex==0) break;
				}
				else
					break;

				//////////////////////////////////////////////////////////////////////////////////////////////-DEST
				
				//////////// 퀘스트 전용 아이템은 인벤 이외의 곳으로 이동할 수 없다.	//////////////////////////////
				nItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
				if (CHTParamIDCheck::HT_bIsItemQuestOnly(nItemIndex))
				{	if(m->byToPlace != ITEM_PLACE_INVEN) {nResult=REPLY_ITEM_MOVE_NOMOVE; break;}
				}

				if  (m->byToPlace == ITEM_PLACE_INVEN)
				{	if (m->snToIndex<0||m->snToIndex>=pMob[conn].byMaxInven) break;
					dest = &pMob[conn].MOB.Inven[m->snToIndex];
				}   else
				if  (m->byToPlace == ITEM_PLACE_EQUIP)
				{	if (m->snToIndex<0||m->snToIndex>=MAX_EQUIP) break;
					dest = &pMob[conn].MOB.Equip[m->snToIndex];
				}   else
				if  (m->byToPlace == ITEM_PLACE_CARGO) 
				{	if (m->snToIndex<0||m->snToIndex>=MAX_CARGO) break;
					if((eKalaCore_Brahma - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break;
					if((eKalaCore_Vishnu - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break;
					if((eKalaCore_Siva - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break;
					dest = &pUser[conn].Cargo[m->snToIndex];
				}	else
				if	(m->byToPlace == ITEM_PLACE_GUILDCARGO)
				{	if (m->snToIndex<0||m->snToIndex>=MAX_CARGO*3) break;
					dest = &pGuild[pUser[conn].nGuildIndex].GUILD.Repository[m->snToIndex];

					int nPrice = 0;
					int nShopItemIndex = (dest->snIndex)+HT_PARAMTYPE_ITEM_START-1;
					if(!g_ParamMgr.HT_bGetItemSellRupiah(nShopItemIndex, &nPrice))
					{
					/*	char strItem[128];*/
						//BASE_GetItemCode(dest, strItem);
						//sprintf(temp,"gld RemoveItem from move to guildcargo %s",strItem);
						//Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						ZeroMemory(dest, sizeof(STRUCT_ITEM));
					}
					
					if(dest->snIndex != 0) break;	//	길드창고의 경우 아이템 교체는 안된다. 비어잇는 길드창고 인덱스에 아이템을 채울수 있다
				}	else
				{   Log("dbg Trading Fails.SwapItem dest type",pUser[conn].AccountName,pUser[conn].IP); break;
				}

				if(m->byToPlace == ITEM_PLACE_EQUIP)	//	아이템장착시 아이템유효성검사
				{	
					//if(pItemData[sour->snIndex].byLevel<=ITEM_EQUIP_LEVEL)							//	레벨5이하아이템 장착제한검사
						//if(pItemData[sour->snIndex].kReq.byLevel > pMob[conn].MOB.byLevel) break;

					int nLimit = 0; int nTribe = (int)pMob[conn].MOB.snTribe;
					if(!g_ParamMgr.HT_bGetItemLimitTribe( nItemIndex, &nLimit )) break;		//	해당아이템의 종족속성치를 읽지못할경우. 
					if( nLimit!=0 && !( nTribe & nLimit ) ) break;										//	종족속성이 다른 아이템착용오류(해킹차단)

					if(m->snToIndex == eTNEqu_Helmet)
						if(!CHTParamIDCheck::HT_bIsItemDefenceHelmet(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_EarringRight || m->snToIndex == eTNEqu_EarringLeft) 
						if(!CHTParamIDCheck::HT_bIsItemAccessoryEarring(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Necklace) 
						if(!CHTParamIDCheck::HT_bIsItemAccessoryNecklace(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Armor)
						if(!CHTParamIDCheck::HT_bIsItemDefenceArmor(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Belt)
						if(!CHTParamIDCheck::HT_bIsItemDefenceBelt(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_OneHandWeapon)
					{	if(!CHTParamIDCheck::HT_bIsItemWeapon(nItemIndex)) break;
						int nLeftIndex = (pMob[conn].MOB.Equip[eTNEqu_Shield].snIndex)+HT_PARAMTYPE_ITEM_START-1;
						if(CHTParamIDCheck::HT_bIsItemWeaponTwoHand(nItemIndex) && nLeftIndex!=(HT_PARAMTYPE_ITEM_START-1)) {nResult=REPLY_ITEM_MOVE_TWOHAND; break;}
						if(CHTParamIDCheck::HT_bIsItemWeaponThrow(nItemIndex) 
							&& nLeftIndex!=HT_PARAMTYPE_ITEM_START-1 && !CHTParamIDCheck::HT_bIsItemUsableArrow(nLeftIndex)) {nResult=REPLY_ITEM_MOVE_TWOHAND; break;}
					}
					if(m->snToIndex == eTNEqu_Shield) 
					{	int nWeapon = pMob[conn].MOB.Equip[eTNEqu_OneHandWeapon].snIndex+HT_PARAMTYPE_ITEM_START-1;
						if(!CHTParamIDCheck::HT_bIsItemDefenceShield(nItemIndex)) 
						{	if(!CHTParamIDCheck::HT_bIsItemWeaponThrow(nWeapon)) 
							{	short snType = 0; 
								if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType)) break;
								short snTribe = pMob[conn].MOB.snTribe;	
								if((snTribe!=TRIBE_ASURA && snTribe!=TRIBE_RAKSHASA) || !CHTParamIDCheck::HT_bIsItemWeaponOneHand(nWeapon) ||
									snType!=eTNWpn_Dagger || pMob[conn].m_krgMastery[eWpnMtryIdx_DualWpn].iParam1<=0)
								{	nResult=REPLY_ITEM_MOVE_PLACE_ERR; break;
								}	//	else	락샤나 아수라이고 오른손에 원핸드무기를 들고 드바이리다로카를 배웠다면 단검을 왼손착용가능하다.
							}	else 
							if(!CHTParamIDCheck::HT_bIsItemUsableArrow(nItemIndex)) {nResult=REPLY_ITEM_MOVE_PLACE_ERR; break;}
						}	else
						{	if(CHTParamIDCheck::HT_bIsItemWeaponTwoHand(nWeapon) || CHTParamIDCheck::HT_bIsItemWeaponThrow(nWeapon)) {nResult=REPLY_ITEM_MOVE_PLACE_ERR; break;}
						}
					}
					if(m->snToIndex == eTNEqu_BraceletRight || m->snToIndex == eTNEqu_BraceletLeft) 
						if(!CHTParamIDCheck::HT_bIsItemAccessoryBracelet(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_RingRight || m->snToIndex == eTNEqu_RignLeft)
						if(!CHTParamIDCheck::HT_bIsItemAccessoryRing(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Boots)
						if(!CHTParamIDCheck::HT_bIsItemDefenceShoes(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Gloves) 
						if(!CHTParamIDCheck::HT_bIsItemDefenceGloves(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Pants)
						if(!CHTParamIDCheck::HT_bIsItemDefencePants(nItemIndex)) break;
					if(m->snToIndex == eTNEqu_Bag)
						if(!CHTParamIDCheck::HT_bIsItemCharm(nItemIndex)) break;
				}

				////	사용불가능한 인벤영역으로의 아이템이동을 막는다
				//if((m->byFromPlace)==ITEM_PLACE_INVEN && (m->snFromIndex)>=pMob[conn].byMaxInven) break;
				//if((m->byToPlace)==ITEM_PLACE_INVEN && (m->snToIndex)>=pMob[conn].byMaxInven) break;

				//	확장인벤에 아이템존재시 확장bag을 내릴수 없다.
				//if(m->byFromPlace==ITEM_PLACE_EQUIP && m->snFromIndex == eTNEqu_Bag)
				//{	bool bRet = true;
				//	for(int i=MAX_ONEINVEN; i<MAX_INVEN; i++) {	if(pMob[conn].MOB.Inven[i].snIndex!=0) {bRet=false; break;}}
				//	if(!bRet) {nResult=REPLY_ITEM_MOVE_BAG; break;}
				//}

				if(m->byFromPlace==ITEM_PLACE_EQUIP && m->snFromIndex == eTNEqu_OneHandWeapon)
				{	int nShield = pMob[conn].MOB.Equip[eTNEqu_Shield].snIndex+HT_PARAMTYPE_ITEM_START-1;
					short snType = 0; 
					g_ParamMgr.HT_bGetItemType(nShield, &snType);
					if(snType==eTNWpn_Dagger) break;
				}

				if(dest->snIndex) break;

				bCheck = true;
				break;
			}

			//	잘못된 패킷의 경우
			if(!bCheck)	
			{	if(nResult==0) 
				{	sm.nResult=REPLY_ITEM_MOVE_ERROR;
					sprintf(temp,"err Invalid Item_move char:%s FROMplace:%d FROMindex:%d TOplace:%d TOindex:%d",
						pMob[conn].MOB.szName,m->byFromPlace,m->snFromIndex,m->byToPlace,m->snToIndex);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
				}	else 
					sm.nResult=nResult; 

				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SCP_RESP_ITEM_MOVE)); return; 
			}

			short snFromIndex=sour->snIndex;	BYTE byFCount=sour->byCount;
			short snToIndex=dest->snIndex;		BYTE byTCount=dest->byCount;

			if(snFromIndex<0 || snFromIndex>IDX_ITEM || byFCount==0) ZeroMemory(sour, sizeof(STRUCT_ITEM));
			if(snToIndex<0 || snToIndex>IDX_ITEM || byTCount==0) ZeroMemory(dest, sizeof(STRUCT_ITEM));		

			sm.nResult = 0;
			STRUCT_ITEM tempdest = *dest;
			STRUCT_ITEM tempsour = *sour;
			memset(dest,0,sizeof(STRUCT_ITEM));
			memset(sour,0,sizeof(STRUCT_ITEM));
			// 복사
			*dest =  tempsour;
			*sour =  tempdest;

			BOOL bEquip = false;	 
			if( ITEM_PLACE_EQUIP==m->byFromPlace && (ITEM_PLACE_CARGO==m->byToPlace || ITEM_PLACE_INVEN==m->byToPlace || ITEM_PLACE_GUILDCARGO==m->byToPlace))		//	아이템 탈착
			{	bEquip= true;
				(m->snFromIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempsour, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempsour, eAfn_Remove );
				(m->snToIndex == eTNEqu_Shield)	? pMob[conn].EquipItem( &tempdest, eAfn_Add, true ) : pMob[conn].EquipItem( &tempdest, eAfn_Add );
				//if(CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(nItemIndex))			//	인벤확장아이템 탈착시 
				//{	pMob[conn].byMaxInven=MAX_ONEINVEN;
				//}
			}	else 
			if((ITEM_PLACE_CARGO==m->byFromPlace || ITEM_PLACE_INVEN==m->byFromPlace || ITEM_PLACE_GUILDCARGO==m->byFromPlace) && ITEM_PLACE_EQUIP==m->byToPlace )	//	아이템 장착
			{	bEquip= true;
				(m->snFromIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempsour, eAfn_Add, true ) : pMob[conn].EquipItem( &tempsour, eAfn_Add );
				(m->snToIndex == eTNEqu_Shield) ?   pMob[conn].EquipItem( &tempdest, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempdest, eAfn_Remove );
				//if(CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(nItemIndex))			//	인벤확장아이템 장착시
				//{	int nSize=0;	g_ParamMgr.HT_bGetItemEffect1Param1( nItemIndex, &nSize );
				//	pMob[conn].byMaxInven += nSize*MAX_INVEN_Y;
				//	if(pMob[conn].byMaxInven <= 0) pMob[conn].byMaxInven=MAX_ONEINVEN;
				//}
			}

			pMob[conn].UpdateEquipmentPoints();
			if(bEquip)
			{	pMob[conn].NotifyUpdateUIMsg();

				S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
				nm.nID = conn; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
				memcpy(nm.Equip, pMob[conn].ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);	

				int tx = pMob[conn].TargetX;
				int ty = pMob[conn].TargetY;
				GridMulticast(tx,ty,(MSG_STANDARD*)&nm,conn,30);
			}

			pUser[conn].cSock.AddMessage((char *)&sm,sizeof(S_SCP_RESP_ITEM_MOVE));			
			pUser[conn].cSock.SendMessage();

			if(m->byFromPlace!=ITEM_PLACE_GUILDCARGO && m->byToPlace!=ITEM_PLACE_GUILDCARGO) return;

			Msg_GuildItemUpdate nm; nm.wType = _Msg_GuildItemUpdate;
			nm.nGuildID = pMob[conn].MOB.nGuildID;
			if(m->byFromPlace==ITEM_PLACE_GUILDCARGO && m->byToPlace==ITEM_PLACE_GUILDCARGO)		//	길드창고에서 길드창고로 옮긴 경우
			{
				nm.nFromIndex = m->snFromIndex;
				nm.nToIndex = m->snToIndex; nm.item = *dest; 
			}
			else if(m->byFromPlace==ITEM_PLACE_GUILDCARGO && m->byToPlace!=ITEM_PLACE_GUILDCARGO)	//	길드창고와 외부의 아이템을 교체시
			{
				nm.nFromIndex = m->snFromIndex;
				nm.nToIndex = -1; nm.item = *sour; 
			}
			else if(m->byFromPlace!=ITEM_PLACE_GUILDCARGO && m->byToPlace==ITEM_PLACE_GUILDCARGO)	//	길드창고와 외부의 아이템을 교체시
			{
				nm.nFromIndex = -1;
				nm.nToIndex = m->snToIndex; nm.item = *dest; 
			}

			char szItemCode[256] = { 0, };
			BASE_GetItemCode( dest, szItemCode );
			sprintf(temp,"gld Item_move guildid:%d char:%s %s FROMplace:%d FROMindex:%d TOplace:%d TOindex:%d",
				pMob[conn].MOB.nGuildID, pMob[conn].MOB.szName, szItemCode, m->byFromPlace,m->snFromIndex,m->byToPlace,m->snToIndex);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP); 

			if(!DBServerSocket.SendOneMessage((char*)&nm,sizeof(nm)))
			{	Log("err Msg_GuildItemUpdate DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}

 			// CNF가 필요한가?
			// EQUIP의 경우 ITEM장착가능 능력치, 아이템 장착가능 클래스
			// CARRY,CARGO의 경우 아이템 세팅가능 GRID를 체크.
		}  break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_ITEM_GET:
		{
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_GET *m = (S_CSP_REQ_ITEM_GET *) msg;
			int itemid = m->nItemID;

			if(itemid<0 || itemid>=MAX_ITEM_DATA) return;

			S_SCP_RESP_ITEM_GET itemget;
			itemget.wType = SCP_RESP_ITEM_GET;
			itemget.nResult = REPLY_ACK_OK;
			itemget.snIndex = pItem[itemid].ITEM.snIndex;

			int GridX = pItem[itemid].PosX;
			int GridY = pItem[itemid].PosY;
			int tx = pMob[conn].TargetX; int ty = pMob[conn].TargetY;
			int nItemIndex = (pItem[itemid].ITEM.snIndex)+HT_PARAMTYPE_ITEM_START-1;

			if(tx<GridX-5 || tx>GridX+5 ||ty<GridY-5 || ty>GridY+5)		//	아이템은 5셀 이내의 아이템만 줍기가 가능하다
			{	itemget.nResult = REPLY_ITEM_MOVE_DISTANCE_ERR;
				pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;
			}

			bool bIsKalaCore = false;
			int iKalaCore = nItemIndex;
			if( (eKalaCore_Brahma == nItemIndex) || (eKalaCore_Vishnu == nItemIndex) || (eKalaCore_Siva == nItemIndex) ) bIsKalaCore = true;
			if( (eTNVSAfn_HaveKalaCore & pMob[conn].m_iAffections) && bIsKalaCore ) return;	// kala-core를 가지고 있는데 또 칼라코어를 주우려고 한다면, 줍기 실패(줍지 못한다.)
			if( bIsKalaCore && pMob[conn].m_kWaitAction.iAction != eWaitAct_None ) return;		// 이동(푸스티카류사용시)시 아이템을 주울수 없다	

			if(pItem[itemid].m_iOwner != 0)				//	우선순위가 있을경우
			{	if(CurrentTime<pItem[itemid].m_uiReleaseTime)	// 줍기우선시간이 경과하지 않음.
				{	if(pItem[itemid].m_iOwner!=conn && pItem[itemid].m_iOwner!=pMob[conn].Leader)	//	내꺼두 아니구 파티꺼두 아닐경우
					{	itemget.nResult = REPLY_ITEM_MOVE_ROUTING_TIME;
						pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));
						sprintf(temp,"Getitem routing error name:%s charid:%d partyleader:%d itemowner:%d", pMob[conn].MOB.szName, conn, pMob[conn].Leader, pItem[itemid].m_iOwner);
						WriteLog(temp,".\\MonsterLog\\[Log]RoutingFail.txt");
						return;
					}
				}
			}

			//	루팅시스템추가(2004.05.06)
			int nCount=0; byte byShare=0; int leader=pMob[conn].Leader;
			int nOwner=conn; byte byOwner=0; int fol=0;
			if(leader==0) leader=conn; int nMember[MAX_PARTY+1]={0,};
			if(pMob[leader].byRootingMode==ROOTING_SHARE)
			{
				if(!bIsKalaCore)
				{
					for (int i=0;i<MAX_PARTY+1;i++)
					{   if (i==0) fol = leader;
						else      fol = pMob[leader].m_irgParty[i-1];
   	 					if	(fol<=0||fol>=MAX_USER) continue;
						if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
						nMember[nCount++]=fol;
					}
				}
				else
				{	nMember[0]=conn; nCount=1;
				}

				if(nCount>=2)							//	분배대상존재(share=1)
				{	byShare=1; 
					for(int i=0; i<MAX_PARTY; i++)
					{
						int nFirst = rand()%nCount;
						int nSecond = rand()%nCount;
						if(nFirst == nSecond) continue;
						int nTemp = nMember[nFirst];
						nMember[nFirst] = nMember[nSecond];
						nMember[nSecond] = nTemp;
					}
					byOwner=SecCounter%nCount; 
					nOwner=nMember[byOwner]; 
				}
			}
			else
			{	nMember[0]=conn; nCount=1; byOwner=0; nOwner=conn;
			}

			/*		돈을 주을 경우		*/
			if(CHTParamIDCheck::HT_bIsItemUsableMoney( nItemIndex ))					//	Money를 주울경우
			{	if(nCount<1) nCount=1;
				int nRupiah = pItem[itemid].Money/nCount;
				if(byShare)		//	default(파티분배)
				{	
					for (int i=0;i<MAX_PARTY+1;i++)
					{   if (i==0) fol = leader;
						else      fol = pMob[leader].m_irgParty[i-1];
   	 					if	(fol<=0||fol>=MAX_USER) continue;
						if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
						//nRupiah *= (pMob[fol].m_dGetMoneyRate/100);
						pMob[fol].IncGold(nRupiah);														//  주운사람 돈 증가
						itemget.dwMoney = pMob[fol].MOB.nRupiah;
						pUser[fol].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));	//	돈을 주웠다는 것을 알린다.
					}
				}
				else			//	개인분배
				{	//nRupiah *= (pMob[conn].m_dGetMoneyRate/100);
					pMob[conn].IncGold(nRupiah);												//  주운사람 돈 증가
					itemget.dwMoney = pMob[conn].MOB.nRupiah;
					pUser[conn].cSock.AddMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));	//	돈을 주웠다는 것을 알린다.
				}

				//	땅에 있는 돈아이템을 주음.(로그)
				//if	(BASE_NeedLog(&pItem[itemid].ITEM, pItem[itemid].Money)==NULL)	continue;
				if(pItem[itemid].Money>1000)
				{	sprintf(temp,"get money:%d", pItem[itemid].Money);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}

				SendItemDisappear(GridX, GridY, itemid, conn);									//	아이템이 사라짐을 알린다.
				memset(&(pItem[itemid].ITEM),0,sizeof(STRUCT_ITEM));
				pUser[conn].cSock.SendMessage();
				return;
			}
			/****************************/

			//	아이템공간을 얻기전에 중첩아이템은 기존아이템에 중업을 시킨다.
			BYTE byMax=0; bool bDisappear=false; 
			BYTE byFirst=pItem[itemid].ITEM.byCount;
			g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMax );
			if(byMax>1)		//	주운아이템이 중첩아이템일 경우
			{	BYTE byCount = pItem[itemid].ITEM.byCount;
				nOwner = conn;
				for(int i=0; i<pMob[conn].byMaxInven; i++)
				{
					if(pItem[itemid].ITEM.snIndex==pMob[conn].MOB.Inven[i].snIndex)
					{	if(pMob[conn].MOB.Inven[i].byCount>=byMax) continue;
						BYTE byDiff = byMax-pMob[conn].MOB.Inven[i].byCount;
						if(byCount<=byDiff) 
						{	pMob[conn].MOB.Inven[i].byCount+=byCount; 
							bDisappear=true;		//	전부 중첩되어 아이템 사라짐.
							//	중첩된 아이템을 알린다.
							S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
							nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
							nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
							pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
							break;
						}
						pMob[conn].MOB.Inven[i].byCount=byMax; 
						byCount -= byDiff; pItem[itemid].ITEM.byCount = byCount;
						//	중첩된 아이템을 알린다.
						S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
						nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
						nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
						pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
					}
				}
			}
	
			if(!bDisappear && byFirst!=pItem[itemid].ITEM.byCount)		//	아이템중첩을 하고 남았을 경우(인벤이 가득참)
			{	itemget.nResult = REPLY_ITEM_MOVE_PART;
				pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;	
			}

			int	emptyinven=0; 
			if(!bDisappear)
			{	for(int i=0; i<nCount; i++)
				{	emptyinven = GetEmptyInven(nOwner);		//	빈자리검색.
					if(emptyinven<0 || emptyinven>=pMob[nOwner].byMaxInven) 
					{	if(nCount<=1 || byMax>1)
						{	itemget.nResult = REPLY_ITEM_MOVE_INVENTORY_LACK;	//	파티원전원 빈공간이 없을 경우
							pUser[nOwner].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;	
						}
						for(int j=byOwner; j<nCount-byOwner;j++)		
						{	nMember[j]=nMember[j+1];
						}
						nMember[nCount-1]=0; nCount--;
						byOwner=rand()%nCount; nOwner=nMember[byOwner];
					}
					else break;
				}
			}

			//	에러코드급조(차후 적절히 없앨것)
			if(emptyinven<0 || emptyinven>=pMob[nOwner].byMaxInven)
			{	itemget.nResult = REPLY_ITEM_MOVE_INVENTORY_LACK;	//	파티원전원 빈공간이 없을 경우
				pUser[nOwner].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;	
			}

			pUser[nOwner].cSock.AddMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));
			SendItemDisappear(GridX, GridY, itemid, nOwner);						//	SCP_MAP_ITEM_DISAPPEAR 전송

			#ifdef __TN_PLAYMOVIE__
			{
				// 전체 공지를 한다.
				char szMsg[1024] = { 0,0,0, };	
				sprintf( szMsg, g_pMessageStringTable[_PickUpItem], pMob[conn].MOB.szName );
				PostMessageToZone( szMsg );
			}
			#endif

			if( bIsKalaCore ) // kala-core를 처음 줍는 경우, ...
			{
				pMob[nOwner].TurnOffAffection( eTNAfn_Invisible );
				pMob[nOwner].m_iAffections = pMob[nOwner].m_iAffections | eTNVSAfn_HaveKalaCore;
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Invulnerable;
				kEffect.iDuration = 3000;
				kEffect.iParam1 = 100;
				kEffect.iParam2 = 0;
				pMob[nOwner].AddEffect( kEffect, nOwner, nOwner );
				pMob[nOwner].BroadcastUpdateStatusMsg();

				// 누가 kala-core를 획득했다는 메시지(현재 좌표 출력)
				int iTxtIndex = 0;
				if( eKalaCore_Brahma == iKalaCore ) iTxtIndex = _Brahma;
				else if( eKalaCore_Vishnu == iKalaCore ) iTxtIndex = _Vishnu;
				else if( eKalaCore_Siva == iKalaCore ) iTxtIndex = _Siva;

				int iTrimuritiIndex = 0;
				if( eTNClan_Brahma == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Brahma;
				else if( eTNClan_Vishnu == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Vishnu;
				else if( eTNClan_Siva == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Siva;

				char szMsg[1024] = { 0,0,0, };	
				sprintf( szMsg, g_pMessageStringTable[_PickUp_Kala_Core]
					, g_pMessageStringTable[iTrimuritiIndex], pMob[nOwner].MOB.szName, pMob[nOwner].TargetX, pMob[nOwner].TargetY, g_pMessageStringTable[iTxtIndex] );
				PostMessageToZone( szMsg );

				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					strcat( szMsg, chBuf );
					WriteLog( szMsg, g_szrgLogFileName[eLogFileName_KalaSystem] );
				}

				pUser[nOwner].cSock.SendMessage();

				g_kKalaSystem.ChangeKalaLoc( TNKalaSystem::eLoc_Ground, 0, 0, GridX, GridY, 0, TNKalaSystem::eLoc_Inventory, 0, 0, 0, 0, nOwner );
			}

			if(!bDisappear)
			{	S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byType = SET_ITEM_CREATE;	//	아이템 생성
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = emptyinven;
				itemset.sitem = pItem[itemid].ITEM;
				pMob[nOwner].MOB.Inven[emptyinven] = pItem[itemid].ITEM;
				pUser[nOwner].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

				//	땅에 있는 아이템을 주음.(습득 로그)
				char strItem[128];
				short snIndex = pItem[itemid].ITEM.snIndex;
				if (BASE_CheckItemLog(&pItem[itemid].ITEM))
				{	BASE_GetItemCode(&pItem[itemid].ITEM,strItem);
					sprintf(temp,"get %s",strItem);
					Log(temp,pUser[nOwner].AccountName,pUser[nOwner].IP);
				}
			}	else
			{	//	땅에 있는 아이템을 주음.(중첩후 사라짐 로그)
				char strItem[128];
				short snIndex = pItem[itemid].ITEM.snIndex;
				if (BASE_CheckItemLog(&pItem[itemid].ITEM))
				{	BASE_GetItemCode(&pItem[itemid].ITEM,strItem);
					sprintf(temp,"get %s",strItem);
					Log(temp,pUser[nOwner].AccountName,pUser[nOwner].IP);
				}
			}

			memset(&(pItem[itemid].ITEM),0,sizeof(STRUCT_ITEM));
			pUser[nOwner].cSock.SendMessage();
		}	break;
	case CSP_REQ_ITEM_DROP:
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_DROP * m = (S_CSP_REQ_ITEM_DROP*) msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_DROP);
				return;
			}

			int iCoordX, iCoordY;

			S_SCP_RESP_ITEM_DROP itemdrop;
			itemdrop.wType = SCP_RESP_ITEM_DROP;
			itemdrop.snResult = REPLY_ACK_OK;
			itemdrop.byPlace = m->byFromPlace;
			itemdrop.byIndex = m->byIndex;
			itemdrop.dwMoney = 0;

			if(m->snX<0 || m->snX>MAX_GRIDX || m->snZ<0 || m->snZ>MAX_GRIDY)
			{
				itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
				pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
				return;
			}

			int tx = pMob[conn].TargetX; int ty = pMob[conn].TargetY;

			if(tx<m->snX-g_iHalfGridX || tx>m->snX+g_iHalfGridX ||ty<m->snZ-g_iHalfGridY || ty>m->snZ+g_iHalfGridY)
			{	itemdrop.snResult = REPLY_ITEM_MOVE_DISTANCE_ERR;
				pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP)); return;
			}

			/*		돈을 떨어뜨릴경우		*/
			if(m->dwMoney>0)   
			{	itemdrop.byType = DROP_TYPE_MONEY;
				if(m->byFromPlace==ITEM_PLACE_INVEN)
				{	if(m->dwMoney>(DWORD)pMob[conn].MOB.nRupiah)
					{	itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
						pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
						return;
					}
					
					pMob[conn].DecGold(m->dwMoney);								//  구입자 인벤돈 감소
					itemdrop.dwMoney = pMob[conn].MOB.nRupiah;
				}	else
				if(m->byFromPlace==ITEM_PLACE_CARGO)
				{	if(m->dwMoney>(DWORD)pUser[conn].Coin)
					{	itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
						pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
						// 줄어든 MOB의 돈을 복귀한다.
						
						//pMob[conn].IncGold(m->dwMoney);
						return;
					}
					pUser[conn].Coin -= m->dwMoney;									//  구입자 창고돈 감소
					itemdrop.dwMoney = pUser[conn].Coin;
				}	else
				{	AddCrackError(conn,50,CRACK_USER_PKTHACK);
					return;
				}

				pUser[conn].cSock.AddMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));

				int nItemIndex = g_ParamMgr.HT_iGetIndexForMoneyItem(m->dwMoney);
				STRUCT_ITEM item; ZeroMemory(&item, sizeof(STRUCT_ITEM));
				item.snIndex=nItemIndex-HT_PARAMTYPE_ITEM_START+1;
				
				iCoordX = m->snX;
				iCoordY = m->snZ;
				int destidx = CreateItem( iCoordX, iCoordY, &item, 0, m->dwMoney);						//	돈아이템생성

				//	돈을 버릴경우 로그
				//if	(BASE_NeedLog(&pItem[destidx].ITEM, m->dwMoney)==NULL)	continue;
				if	(m->dwMoney>1000)
				{	sprintf(temp,"drop money:%d", m->dwMoney);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}

				return;
			}
			/********************************/

			itemdrop.byType = DROP_TYPE_ITEM;
			STRUCT_ITEM *sour = NULL;
			STRUCT_ITEM tempitem;
			if	(m->byFromPlace==ITEM_PLACE_INVEN)
			{	if (m->byIndex>=0&&m->byIndex<MAX_INVEN) sour = &pMob[conn].MOB.Inven[m->byIndex];
			}	else
			if	(m->byFromPlace==ITEM_PLACE_EQUIP)
			{	if (m->byIndex>=0&&m->byIndex<(MAX_EQUIP-1))
				{	sour = &pMob[conn].MOB.Equip[m->byIndex];
					tempitem = pMob[conn].MOB.Equip[m->byIndex];
				}
			}	else
			if	(m->byFromPlace==ITEM_PLACE_CARGO)
			{	if (m->byIndex>=0&&m->byIndex<MAX_CARGO) sour = &pUser[conn].Cargo[m->byIndex];
			}

			if(sour == NULL)
			{	itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
				pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
				return;
			}

			pUser[conn].cSock.AddMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));

			//	Item Create & SCP_MAP_ITEM_APPEAR 전송
			iCoordX = m->snX;
			iCoordY = m->snZ;
			int destidx = CreateItem( iCoordX, iCoordY,sour);

			memset((void*)sour,0,sizeof(STRUCT_ITEM));

			if	(m->byFromPlace==ITEM_PLACE_EQUIP)
			{
				(m->byIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempitem, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempitem, eAfn_Remove );
				pMob[conn].UpdateEquipmentPoints();
				pMob[conn].NotifyUpdateUIMsg();
			}

			//	아이템을 버릴경우 로그
			char strItem[128];
			short snIndex = pItem[destidx].ITEM.snIndex;
			//if	(BASE_NeedLog(&pItem[destidx].ITEM, 0)==NULL)	continue;
			if (BASE_CheckItemLog(&pItem[destidx].ITEM))
			{					
				BASE_GetItemCode(&pItem[destidx].ITEM,strItem);
				sprintf(temp,"drop %s",strItem);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}

			////	SCP_RESP_ITEM_SET 전송
			//S_SCP_RESP_ITEM_SET itemset;
			//itemset.wType = SCP_RESP_ITEM_SET;
			//itemset.byType = SET_ITEM_DELETE;
			//itemset.byPlace = m->byFromPlace;
			//item

			//pUser[conn].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));
			//pUser[conn].cSock.SendMessage();
		}	break;
	case _MSG_Packing:
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			MSG_Packing * m = (MSG_Packing*) msg;
			
			m->byResult = 1;
			STRUCT_ITEM* sour=NULL; STRUCT_ITEM* dest=NULL;
			sour = GetItem(conn, m->byFromPlace, m->byFromIndex);
			dest = GetItem(conn, m->byToPlace, m->byToIndex);

			if(sour==NULL || dest==NULL) break;

			int nSourIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			int nDestIndex = (dest->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			if(m->byType==TYPE_ITEM_PACKING)
			{	if(sour->snIndex==0 || dest->snIndex==0)				//  아이템이 비어있을 경우 실패
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}		
				if(sour->snIndex != dest->snIndex)						//	서로다른 종류의 아이템을 중첩시 실패
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}
				BYTE byMax = 0; int byTotal = (dest->byCount)+(sour->byCount);
				g_ParamMgr.HT_bGetItemMaxCount( nDestIndex, &byMax );
				if(byTotal>byMax)	//	중첩최대수를 초과시
				{	dest->byCount	= byMax;
					sour->byCount	= byTotal - byMax;
				}	else
				{	dest->byCount = byTotal;
					sour->byCount = 0;
					memset((void*)sour,0,sizeof(STRUCT_ITEM));
				}

				m->byFromCount	= sour->byCount;
				m->byToCount	= dest->byCount;
			}	else
			if(m->byType==TYPE_ITEM_UNPACKING)
			{	if(m->byFromPlace!=m->byToPlace)						//	동일한 지역으로의 언패킹이 아닐경우 에러
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}						

				BYTE byMax = 0; bool bRet = g_ParamMgr.HT_bGetItemMaxCount( nSourIndex, &byMax );
				if(!bRet)
				{	SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Data]);
					return;
				}	
				if(sour->byCount>byMax) sour->byCount=byMax;
				if(sour->byCount <= m->byToCount || m->byToCount<=0)	//	언패킹할 숫자가 아이템의 수보다 많을 경우.
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}					
				if(sour->snIndex==0 || dest->snIndex!=0)				// 	언패킹할 목표위치에 아이템이 존재할 경우
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}				
																					
				sour->byCount -= m->byToCount;
				memcpy((void*)dest, (void*)sour, sizeof(STRUCT_ITEM));
				dest->byCount = m->byToCount;
			}	else
			{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
				return;
			}
			//	성공시 메세지 전송
			m->byResult = 0;
			pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
		}	break;
	case _MSG_Money_Move:	// deposit coin to account inventory.
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			MSG_Money_Move * m = (MSG_Money_Move *)msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,10,CRACK_NOUSER_MONEY);
				return;
			}
  
			BYTE byFrom = m->byFromPlace;
			BYTE byTo	= m->byToPlace;

			if(byFrom == byTo)
			{	SendClientMessage(conn,g_pMessageStringTable[_Same_Place_Rupiah]);
				return;
			}
			if((byFrom!=ITEM_PLACE_INVEN && byFrom!=ITEM_PLACE_CARGO) || (byTo!=ITEM_PLACE_INVEN && byTo!=ITEM_PLACE_CARGO))
			{	SendClientMessage(conn,g_pMessageStringTable[_Money_Move_Wrong_Place]);
				return;
			}

			if(m->dwMoney>MAX_INT) return;

			int coin = pMob[conn].MOB.nRupiah;
			int cargocoin = pUser[conn].Coin;
			sprintf(temp, "dbg Move_Money:%d from Inven:d Cargo:%d ", m->dwMoney, coin, cargocoin);
			if(m->byFromPlace==ITEM_PLACE_INVEN)
			{	if(coin<(int)m->dwMoney) return;

				if(m->byToPlace==ITEM_PLACE_CARGO)
				{	cargocoin += m->dwMoney;
					if(cargocoin<0 || cargocoin>MAX_INT || m->dwMoney>MAX_INT)
					{
						return;
					}
					coin -= m->dwMoney;
					if(coin<0 || cargocoin>MAX_INT)
					{	SendClientMessage(conn,g_pMessageStringTable[_Cant_Deposit_That_Much]);
						return;
					}
					pMob[conn].DecGold(m->dwMoney);

					m->dwFromMoney = pMob[conn].MOB.nRupiah;
					m->dwToMoney = cargocoin;

					if(m->dwMoney>=LOGMONEY)
					{	sprintf(temp,"dbg move money i->c [%s] %u", pMob[conn].MOB.szName, m->dwMoney);
						Log(temp, pUser[conn].AccountName, pUser[conn].IP);
					}
				}
			}	else
			if(m->byFromPlace==ITEM_PLACE_CARGO)
			{	if(cargocoin<(int)m->dwMoney) return;
				if(m->byToPlace==ITEM_PLACE_INVEN)
				{	cargocoin -= m->dwMoney;
					coin += m->dwMoney;
					if(coin<0 || coin>MAX_INT || m->dwMoney>MAX_INT)
					{
						return;
					}

					if(cargocoin<0 || coin>MAX_INT)
					{	SendClientMessage(conn,g_pMessageStringTable[_Cant_Deposit_That_Much]);
						return;
					}
					m->dwFromMoney = cargocoin;

					pMob[conn].IncGold(m->dwMoney);
					m->dwToMoney = pMob[conn].MOB.nRupiah;

					if(m->dwMoney>=LOGMONEY)
					{	sprintf(temp,"dbg move money c->i [%s] %d", pMob[conn].MOB.szName, m->dwMoney);
						Log(temp, pUser[conn].AccountName, pUser[conn].IP);
					}
				}
			}
			pUser[conn].Coin = cargocoin;
			pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
		}	break;   
///////////////////////////////////////////////////////////////////////////////////////////////
	case	CSP_REQ_ITEM_BUY:	// NPC에게 상품사기
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없.
			S_CSP_REQ_ITEM_BUY * m = (S_CSP_REQ_ITEM_BUY *) msg;

			if ( m->snItemCount <= 0 ) return;

			short snNpc = m->snNPCIndex;
			if  (!CHTParamIDCheck::HT_bIsChargeNPC(snNpc) && (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY))
			{   //	SendHpMode(conn);
				AddCrackError(conn,20,CRACK_NOUSER_BUY);
				return;
			}
			
			char tmp[128]={0,};
			short snIndex	=	m->snItemIndex;
			int nItemIndex	=	snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(snIndex<=0 || snIndex>MAX_ITEM_DATA)
			{	CrackLog(conn," CSP_REQ_ITEM_BUY: Invalid Item Index");CloseUser(conn); return;
			}
			if(m->snItemCount<0)
			{	CrackLog(conn," CSP_REQ_ITEM_BUY: Invalid Item Count");CloseUser(conn); return;
			}

			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	해당 NPC정보를 읽지 못할경우.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC와 같은 존에 있지 않은 경우.

			S_SCP_RESP_ITEM_BUY sm; sm.wType = SCP_RESP_ITEM_BUY;
			sm.byResult=REPLY_ACK_OK; sm.snItemIndex = snIndex;

			if(!CHTParamIDCheck::HT_bIsNPC(snNpc))
			{	sprintf(tmp,"CSP_REQ_ITEM_BUY: Item_buy char:%s invalid npc id:%d", pMob[conn].MOB.szName, snNpc);
				CrackLog(conn, tmp); CloseUser(conn); return;
			}
			if(!CHTParamIDCheck::HT_bIsChargeNPC(snNpc) && 
				(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY)) return; //	NPC Grid내에 플레이어가 없을 경우

			if( g_ParamMgr.HT_bLockID( snNpc ) == true )
			{	int idItem=0; int iCount=g_ParamMgr.HT_iGetNPCSellingItemCount( );
				for ( int i = 0; i < iCount; ++i )
				{	g_ParamMgr.HT_bGetNPCSellingItem( i, &idItem );
					if(nItemIndex==idItem) break;
				}
				g_ParamMgr.HT_bUnLockID( snNpc );
				if(i>=iCount) 
				{	sprintf(tmp,"CSP_REQ_ITEM_BUY: Item_buy char:%s invalid itemid:%d from npc:%d", pMob[conn].MOB.szName, nItemIndex, snNpc);
					CrackLog(conn,tmp); CloseUser(conn); return;
				}
			}	else
			{	sprintf(tmp,"CSP_REQ_ITEM_BUY: Item_buy char:%s invalid npc id:%d or locked npcid", pMob[conn].MOB.szName, snNpc);
				CrackLog(conn,tmp); CloseUser(conn); return;
			}

			short snCount = m->snItemCount;
			bool bResult=0; int nPrice=0; BYTE byMaxCount=0; 
			short sMaxDur=0; int nTotPrice = 0;
			bResult = g_ParamMgr.HT_bGetItemMaxCount		(nItemIndex, &byMaxCount);
			bResult &= g_ParamMgr.HT_bGetItemMaxDurability	(nItemIndex, &sMaxDur);
			if(CHTParamIDCheck::HT_bIsChargeNPC(snNpc))
			{	if(ItemServerSocket.Sock==0) 
				{	SendClientMessage(conn,g_pMessageStringTable[_Serverdown_Itemserver]);	//	캐쉬서버 다운시
					return;
				}
				bResult  &= g_ParamMgr.HT_bGetItemCash		(nItemIndex, &nPrice); 
				nTotPrice = nPrice*snCount;
				if(CHTParamIDCheck::HT_bIsItemChargeContinuance(nItemIndex))		//	지속아이템구입시(유료아이템)
				{	if(snCount>GetEmptyInvenCount(conn))								//	구입하려는 아이템을 넣을 공간이 없을 경우
					{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
						pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
					}
					if( g_eCountryID == eCountryIndonesia )
					{	;
					}
					else if( g_eCountryID == eCountryChina )
					{	if(nPrice>=30)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원이상짜리 10개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원이상짜리 5개미만 구입불가
						}	else
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.9/10)*10);				//	100원미만짜리 20개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원미만짜리 10개미만 구입불가
						}
					}
					else if( g_eCountryID == eCountryJapan )
					{	if(nPrice>=100)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원이상짜리 10개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원이상짜리 5개미만 구입불가
						}	else
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원미만짜리 20개이상구입시 할인
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원미만짜리 10개미만 구입불가
						}
					}
					else
					{	if(nPrice>=100)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원이상짜리 10개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원이상짜리 5개미만 구입불가
						}	else
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원미만짜리 20개이상구입시 할인
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원미만짜리 10개미만 구입불가
						}
					}
					snCount *= byMaxCount;
				}	else															//	일반아이템구입시(유료아이템)
				{	if((snCount+byMaxCount)/byMaxCount>GetEmptyInvenCount(conn))								//	구입하려는 아이템을 넣을 공간이 없을 경우
					{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
						pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
					}
					if( g_eCountryID == eCountryIndonesia )
					{	;
					}
					else if( g_eCountryID == eCountryChina )
					{	if(nPrice>100)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);																			//	2300원초과짜리 구입시 노할인
						}
						else if(nPrice<=100 && nPrice>30)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600원초과 1000원이하짜리 5개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600원초과 1000원이하짜리 2개미만 구입불가
						}
						else if(nPrice<=30 && nPrice>=15)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	300원초과 600원이하짜리 10개이상구입시 할인
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300원초과 600원이하짜리 5개미만 구입불가
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.9/10)*10);			//	100원초과짜리 40개이상구입시 할인
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원초과짜리 20개미만 구입불가
						}
					}
					else if( g_eCountryID == eCountryJapan )
					{	if(nPrice>2300)
						{	;																			//	2300원초과짜리 구입시 노할인
						}
						else if(nPrice<=2300 && nPrice>1000)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	1000원초과 2300이하짜리 3개이상구입시 할인
						}
						else if(nPrice<=1000 && nPrice>600)
						{	if(snCount>=5) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600원초과 1000원이하짜리 5개이상구입시 할인
							if(snCount<2) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600원초과 1000원이하짜리 2개미만 구입불가
						}
						else if(nPrice<=600 && nPrice>300)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	300원초과 600원이하짜리 10개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300원초과 600원이하짜리 5개미만 구입불가
						}
						else if(nPrice<=300 && nPrice>100)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원초과 300원이하짜리 20개이상구입시 할인
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원초과 300원이하짜리 10개미만 구입불가
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원초과짜리 40개이상구입시 할인
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원초과짜리 20개미만 구입불가
						}
					}
					else
					{	if(nPrice>2300)
						{	;																			//	2300원초과짜리 구입시 노할인
						}
						else if(nPrice<=2300 && nPrice>1000)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	1000원초과 2300이하짜리 3개이상구입시 할인
						}
						else if(nPrice<=1000 && nPrice>600)
						{	if(snCount>=5) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600원초과 1000원이하짜리 5개이상구입시 할인
							if(snCount<2) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600원초과 1000원이하짜리 2개미만 구입불가
						}
						else if(nPrice<=600 && nPrice>300)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	300원초과 600원이하짜리 10개이상구입시 할인
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300원초과 600원이하짜리 5개미만 구입불가
						}
						else if(nPrice<=300 && nPrice>100)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원초과 300원이하짜리 20개이상구입시 할인
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원초과 300원이하짜리 10개미만 구입불가
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100원초과짜리 40개이상구입시 할인
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100원초과짜리 20개미만 구입불가
						}
					}
				}
				if(sm.byResult==REPLY_ITEM_BUY_MINCOUNT) {pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;}
				if(!bResult)
				{	sm.byResult = REPLY_UNKNOWN;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
				if(pUser[conn].m_nCash<nTotPrice)		//	보유 cash가 전체구입가격보다 적을경우 에러처리
				{	sm.byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
			}	else
			{	bResult  &= g_ParamMgr.HT_bGetItemRupiah		(nItemIndex, &nPrice); 
				nTotPrice = nPrice*snCount;
				if(ServerIndex==SERVER_KRUMA_HIGH-1 || ServerIndex==SERVER_KRUMA_LOW-1) nTotPrice = (int)(nTotPrice * 1.3);	//	주신전에서는 판매가가 30%비싸다
				if(!bResult || pMob[conn].MOB.nRupiah<nTotPrice)	//	보유 루피아가 전체구입가격보다 적을경우 에러처리
				{	sm.byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
			}

			int i=0;
			for(i=0; i<pMob[conn].byMaxInven; i++)
			{	short snItem=pMob[conn].MOB.Inven[i].snIndex;
				if(snItem!=0) continue;		//	인벤이 차있을 경우

				if(snCount<=byMaxCount)
				{	ZeroMemory(&pMob[conn].MOB.Inven[i], sizeof(STRUCT_ITEM));
					pMob[conn].MOB.Inven[i].snIndex=snIndex;
					pMob[conn].MOB.Inven[i].byCount=(BYTE)snCount;
					pMob[conn].MOB.Inven[i].snDurability=sMaxDur;
					pMob[conn].MOB.Inven[i].wSerial = GetRandom(0, 65535);
					pMob[conn].MOB.Inven[i].snDummy = 0;

					if(BASE_CheckItemLog(&pMob[conn].MOB.Inven[i]))
					{	char szItemCode[128];
						BASE_GetItemCode(&pMob[conn].MOB.Inven[i],szItemCode);
						sprintf( temp, "buy %s curRupia:%d", szItemCode, pMob[conn].MOB.nRupiah);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}

					S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
					nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
					nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
					pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
					snCount = 0;
					break;
				}

				snCount -= byMaxCount;
				ZeroMemory(&pMob[conn].MOB.Inven[i], sizeof(STRUCT_ITEM));
				pMob[conn].MOB.Inven[i].snIndex=snIndex;
				pMob[conn].MOB.Inven[i].byCount=(BYTE)byMaxCount;
				pMob[conn].MOB.Inven[i].snDurability=sMaxDur;
				pMob[conn].MOB.Inven[i].wSerial = GetRandom(0, 65535);
				pMob[conn].MOB.Inven[i].snDummy = 0;

				if(BASE_CheckItemLog(&pMob[conn].MOB.Inven[i]))
				{	char szItemCode[128];
					BASE_GetItemCode(&pMob[conn].MOB.Inven[i],szItemCode);
					sprintf( temp, "buy %s curRupia:%d", szItemCode, pMob[conn].MOB.nRupiah);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}

				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
			}

			if(snCount == m->snItemCount)			// 자리가 없어서 아이템을 구입하지 못했을경우
			{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY));
				return;
			}

			if(CHTParamIDCheck::HT_bIsChargeNPC(snNpc))					//	유료화상인
			{	pUser[conn].m_nCash -= nTotPrice;						//	구입자 실구입비용 삭감
				sm.nMoney = pUser[conn].m_nCash;

				//	Item Server에 cash구입을 알린다.
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));
					nm.wType=_Msg_Cash; nm.nID=conn; nm.byType=2;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					nm.byType=2; nm.nCash=nTotPrice;						//	1:SEARCH, 2:USE
					nm.nIP = pUser[conn].IP; nm.snItemIndex = m->snItemIndex + HT_PARAMTYPE_ITEM_START - 1;
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash2; nm.ID=conn; 
					nm.C_Type = 3; 
					nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
					strcpy(nm.Order_Type,"I0");
					strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
					unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
					sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
					nm.Amount=-nTotPrice; sprintf(nm.Item_no, "%d", m->snItemIndex + HT_PARAMTYPE_ITEM_START - 1);
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
			}	else
			{	
				nTotPrice = nPrice*(m->snItemCount-snCount);
				if(snNpc==1302)
				{
					DWORD dwTex = (DWORD)(nTotPrice*g_byCastleSalesRate/100.0);
					if(g_dwCastleSalesMoney < MAX_INT) g_dwCastleSalesMoney += (dwTex/2);
					nTotPrice +=  dwTex;
				}

				if(ServerIndex==SERVER_KRUMA_HIGH-1 || ServerIndex==SERVER_KRUMA_LOW-1) nTotPrice = (int)(nTotPrice * 1.3);	//	주신전에서는 판매가가 30%비싸다

				pMob[conn].DecGold(nTotPrice);							// 구입자 실구입비용 삭감
				sm.nMoney = pMob[conn].MOB.nRupiah;
			}
			sm.byDummy = 0;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY));
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case   CSP_REQ_ITEM_SELL:		// NPC에게 물건 팔기
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_SELL * m = (S_CSP_REQ_ITEM_SELL *) msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_SELL);
				return;
			}

			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	해당 NPC정보를 읽지 못할경우.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC와 같은 존에 있지 않은 경우.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid내에 플레이어가 없을 경우
	
			S_SCP_RESP_ITEM_SELL sm; sm.wType = SCP_RESP_ITEM_SELL; 
			sm.byResult=REPLY_UNKNOWN; sm.byPlace=m->byPlace; sm.byIndex=m->byIndex;

			//	위치별 아이템 유효성 검사
			STRUCT_ITEM *sour = NULL;
			STRUCT_ITEM tempItem;
			if	(m->byPlace==ITEM_PLACE_INVEN)
			{	if (m->byIndex>=0&&m->byIndex<MAX_INVEN) sour = &pMob[conn].MOB.Inven[m->byIndex];
				//if (m->SourPos<VISUAL_EQUIPPOS) CheckLook=1;
			}	else
			if	(m->byPlace==ITEM_PLACE_EQUIP)
			{	if (m->byIndex>=0&&m->byIndex<(MAX_EQUIP-1))
				{	sour = &pMob[conn].MOB.Equip[m->byIndex];
					tempItem = pMob[conn].MOB.Equip[m->byIndex];
				}
			}	else
			if	(m->byPlace==ITEM_PLACE_CARGO)
			{	if (m->byIndex>=0&&m->byIndex<MAX_CARGO) sour = &pUser[conn].Cargo[m->byIndex];
			}

			//	서버에 해당 아이템이 없을 경우 에러처리
			if(sour == NULL)
			{	sm.byResult = REPLY_ITEM_SELL_OUTINDEX;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			//	서버에 아이템에 대한 자료가 없을 경우 에러처리
			if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;			
			}

			bool bResult=0; int nPrice=0; short sMaxDur=0; BYTE byMax=0;
			int nShopItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			bResult  = g_ParamMgr.HT_bGetItemSellRupiah(nShopItemIndex, &nPrice); 
			bResult &= g_ParamMgr.HT_bGetItemMaxDurability(nShopItemIndex, &sMaxDur);
			bResult &= !CHTParamIDCheck::HT_bIsItemQuestOnly(nShopItemIndex);
			bResult &= g_ParamMgr.HT_bGetItemMaxCount(nShopItemIndex, &byMax);

			if(!bResult)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}
			if(sour->byCount>byMax) sour->byCount = byMax;

			if(nPrice<0)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			nPrice = nPrice*sour->byCount;
			int iHap = nPrice + pMob[conn].MOB.nRupiah;
			if(iHap<0 || iHap>MAX_INT)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			//	Item Sell Log
			char strItem[128]; int nn1=0;
			//if	(BASE_NeedLog(sour, nPrice)==NULL)	continue;
			if (BASE_CheckItemLog(sour))
			{	BASE_GetItemCode(sour,strItem);
				sprintf(temp,"sell %s curRupiah:%d",strItem, pMob[conn].MOB.nRupiah);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}

			ZeroMemory((char*)sour,sizeof(STRUCT_ITEM));
			if(m->byPlace==ITEM_PLACE_EQUIP)
				(m->byIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempItem, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempItem, eAfn_Remove );
			pMob[conn].UpdateEquipmentPoints();
			pMob[conn].NotifyUpdateUIMsg();

			pMob[conn].IncGold(nPrice);			// 구입자 돈 증가

			sm.byResult=REPLY_ACK_OK; sm.nMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_SELL));
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case   CSP_REQ_ITEM_REPAIR:		// NPC에게 물건 수리
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_REPAIR * m = (S_CSP_REQ_ITEM_REPAIR *) msg;

			S_SCP_RESP_ITEM_REPAIR sm; sm.wType = SCP_RESP_ITEM_REPAIR; 
			sm.byResult=REPLY_UNKNOWN; sm.byPlace = m->byPlace; sm.byIndex=m->byIndex;
			sm.byDummy = 1;				//	0:유료아이템으로 수리, 1:루피아로 수리
			
			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	해당 NPC정보를 읽지 못할경우.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC와 같은 존에 있지 않은 경우.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid내에 플레이어가 없을 경우

			//	위치별 아이템 유효성 검사
			STRUCT_ITEM *sour = NULL;
			if	(m->byPlace==ITEM_PLACE_INVEN)
			{	if (m->byIndex>=0&&m->byIndex<MAX_INVEN) sour = &pMob[conn].MOB.Inven[m->byIndex];
			}	else
			if	(m->byPlace==ITEM_PLACE_EQUIP)
			{	if (m->byIndex>=0&&m->byIndex<(MAX_EQUIP-1)) sour = &pMob[conn].MOB.Equip[m->byIndex];
			}	else
			if	(m->byPlace==ITEM_PLACE_CARGO)
			{	if (m->byIndex>=0&&m->byIndex<MAX_CARGO) sour = &pUser[conn].Cargo[m->byIndex];
			}

			//	서버에 해당 아이템이 없을 경우 에러처리
			if(sour == NULL)
			{	sm.byResult = REPLY_ITEM_REPAIR_OUTINDEX;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			//	서버에 아이템에 대한 자료가 없을 경우 에러처리
			if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;			
			}

			bool bResult=0; int nPrice=0; BYTE byMaxCount=0; short sMaxDur=0; 
			int nShopItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			bResult  = g_ParamMgr.HT_bGetItemRupiah			(nShopItemIndex, &nPrice); 
			bResult &= g_ParamMgr.HT_bGetItemMaxCount		(nShopItemIndex, &byMaxCount);
			bResult &= g_ParamMgr.HT_bGetItemMaxDurability	(nShopItemIndex, &sMaxDur);

			if(sour->snDurability == sMaxDur)
			{	sm.byResult = REPLY_ITEM_REPAIR_ENOUGH;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REPAIR));
				return;
			}

			int iCurDur = sour->snDurability/100;
			int iMaxDur = sMaxDur/100;
			if( sour->snDurability % 100 > 0 ) ++iCurDur;	// 올림 처리
			float fPrice = ((HTfloat)nPrice / 10000.0f + (HTfloat)pow(nPrice, 0.85 ))*(HTfloat)(iMaxDur-iCurDur)/(HTfloat)iMaxDur;
			nPrice = (int)( fPrice * (float)sour->byCount);

			if(!bResult || nPrice>pMob[conn].MOB.nRupiah)
			{	sm.byResult = REPLY_ITEM_REPAIR_MONEY_WANT;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REPAIR));
				return;
			}

			short snOldDurability = sour->snDurability;
			sour->snDurability = sMaxDur;
			pMob[conn].DecGold(nPrice);						// 구입자 돈 증가
			sm.byResult=REPLY_ACK_OK; sm.nMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REPAIR));

			if(snOldDurability==0)							//	내구도0으로 능치적용이 안되던 아이템의 속성을 다시 읽어서 전파한다.
			{	pMob[conn].UpdateEquipmentPoints();
				pMob[conn].NotifyUpdateUIMsg();
			}
		}	break;
	case   CSP_REQ_ITEM_REFINING:		// 아이템 제련
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return; // GM이면, 할 수 없다.
			S_CSP_REQ_ITEM_REFINING * m = (S_CSP_REQ_ITEM_REFINING *) msg;

			S_SCP_RESP_ITEM_REFINING sm; sm.wType = SCP_RESP_ITEM_REFINING; 
			sm.byResult=REPLY_UNKNOWN; sm.byIndex=m->byIndex; sm.byPlace=m->byPlace;
			sm.bySubIndex[0]=m->bySubIndex[0]; sm.bySubPlace[0]=m->bySubPlace[0];
			sm.bySubIndex[1]=m->bySubIndex[1]; sm.bySubPlace[1]=m->bySubPlace[1];
			sm.bySubIndex[2]=m->bySubIndex[2]; sm.bySubPlace[2]=m->bySubPlace[2];

			//	위치별 아이템 유효성 검사
			int nRefineItemIndex[3]={0,};
			STRUCT_ITEM *sour = NULL; STRUCT_ITEM *dest[3] = {0,};		//	재련재료들은 인벤에 있는 것만 가능하다
			if	(m->byPlace==ITEM_PLACE_INVEN)
			{	if (m->byIndex>=0&&m->byIndex<MAX_INVEN)
				{   sour = &pMob[conn].MOB.Inven[m->byIndex];
				}
			}/*	else
			if	(m->byPlace==ITEM_PLACE_EQUIP)
			{	if (m->byIndex>=0&&m->byIndex<MAX_EQUIP)
				{	sour = &pMob[conn].MOB.Equip[m->byIndex];
				}
			}	else
			if	(m->byPlace==ITEM_PLACE_CARGO)
			{	if (m->byIndex>=0&&m->byIndex<MAX_CARGO) 
				{	sour = &pUser[conn].Cargo[m->byIndex];
				}
			}*/

			for(int i=0; i<3; i++)
			{
				if	(m->bySubPlace[i]==ITEM_PLACE_INVEN)
				{	if (m->bySubIndex[i]>=0&&m->bySubIndex[i]<MAX_INVEN)
					{   dest[i] = &pMob[conn].MOB.Inven[m->bySubIndex[i]];
						nRefineItemIndex[i] = (dest[i]->snIndex)+HT_PARAMTYPE_ITEM_START-1;
					}
				}
			}/*	else
			if	(m->bySubPlace==ITEM_PLACE_EQUIP)
			{	if (m->bySubIndex>=0&&m->bySubIndex<MAX_EQUIP)
				{	dest = &pMob[conn].MOB.Equip[m->bySubIndex];
				}
			}	else
			if	(m->bySubPlace==ITEM_PLACE_CARGO)
			{	if (m->bySubIndex>=0&&m->bySubIndex<MAX_CARGO) 
				{	dest = &pUser[conn].Cargo[m->bySubIndex];
				}
			}*/

			//	서버에 해당 아이템이 없을 경우 에러처리
			if(sour==NULL || dest[0]==NULL)
			{	sm.byResult = REPLY_ITEM_REFINING_OUTINDEX;
			Log("err refineitem - Inven",pUser[conn].AccountName,pUser[conn].IP);
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_REFINING));
				return;
			}

			//	서버에 아이템에 대한 자료가 없을 경우 에러처리
			if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA || dest[0]->snIndex<0 || dest[0]->snIndex>=MAX_ITEM_DATA)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_REFINING));
				return;			
			}

			int iPrevRefineLevel = sour->byRefineLevel;

			int nPrice=0;
			int nShopItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			bool bResult = g_ParamMgr.HT_bGetItemRupiah(nShopItemIndex, &nPrice); 
			int nSubIndex = (dest[0]->snIndex)+HT_PARAMTYPE_ITEM_START-HT_PARAMTYPE_ITEM_REFINE_MAIN_START;

			if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( nShopItemIndex ) )
			{
				if(sour->bySubRefine[0] > 0 && nSubIndex!=eItem_amala)
				{	sm.byResult = REPLY_ITEM_REFINING_OVER;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));
					return;
				}
			}

			if(CHTParamIDCheck::HT_bIsItemRefineMain(nRefineItemIndex[0]))	//	무기주제련
			{	nPrice = (int)(nPrice * ITEM_REFINING_COAT * pow(sour->byRefineLevel + 1, 1.8));

				//	재련이 불가능한 레벨의 아이템 생성으로 인한 레벨체크추가(2004.11.19)	- Y.W.K
				if(REFINE_MAIN[nSubIndex-1][sour->byRefineLevel]<0)
				{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_REFINING));
					return;	
				}
				//if(g_eCountryID == eCountryJapan) nPrice = (int)(nPrice * ITEM_REFINING_COAT);
				//else nPrice = (int)(nPrice * ITEM_REFINING_COAT * pow(sour->byRefineLevel + 1, 1.8));
			}	else
			{	nPrice = (int)(nPrice * ITEM_REFINING_COAT);
			}

			if(!bResult || pMob[conn].MOB.nRupiah<nPrice)
			{	sm.byResult = REPLY_ITEM_REFINING_MONEY_LACK;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));
				return;
			}

			STRUCT_ITEM tmpItem = *sour;
			float fDiscount = 0;

			if(m->bySubPlace[1]>0)	//	dest[1]의 유효성체크
			{	if(!CHTParamIDCheck::HT_bIsItemRefineSub2( nRefineItemIndex[1] ))
				{	CrackLog(conn," CSP_REQ_ITEM_REFINING m->bySubPlace[1]>0"); 
					CloseUser(conn); return;
				}

				if(dest[1]!=NULL)
				{
					TNSKILL_DATA* pkSkill = (TNSKILL_DATA*)&pItemData[dest[1]->snIndex];

					for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
					{
						if( 0 >= pkSkill->krgEffect[i].iID ) continue;
						switch( pkSkill->krgEffect[i].iID )
						{
						case eTNAfn_RefiningDiscount :
							{
								fDiscount = (float)pkSkill->krgEffect[i].iParam1;
								if(fDiscount<0) fDiscount = 0;
								else if(fDiscount>100) fDiscount = (float)100;
								float fPrice = nPrice * ((100 - fDiscount)/100);
								nPrice = (int)fPrice;
							}	break;
						default:
							break;
						}
					}
				}

				// 제련 가능 여부를 판단한다.
				if ( !CHTParamIDCheck::HT_bIsItem( nRefineItemIndex[1] ) || 
					CHTParamIDCheck::HT_bIsItemQuest( nRefineItemIndex[1] ) || 
					CHTParamIDCheck::HT_bIsItemAccessory( nRefineItemIndex[1] ) || 
					CHTParamIDCheck::HT_bIsItemCharm( nRefineItemIndex[1] ) ) 
				{	sm.byResult = REPLY_ITEM_REFINING_ERROR;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));
					return;
				}
			}
			if(m->bySubPlace[2]>0)	//	dest[2]의 유효성체크
			{
			}

			int nRet = RefiningItem(conn, sour, dest);

			//	이하는 실패든 성공이든 보조재료와 루피아의 소모를 반영한다.
            pMob[conn].DecGold(nPrice);
			sm.nMoney = pMob[conn].MOB.nRupiah;

			char szFrom[256], szTo[256];
			BASE_GetItemCode( &tmpItem, szFrom );
			BASE_GetItemCode( sour, szTo );
			sprintf( temp, "ref Refine Result: %d, Price: %d Src: %d, %d [ %s -> %s ]"
				, nRet, nPrice, nRefineItemIndex[0], nRefineItemIndex[1], szFrom, szTo );
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			if(nRet > 0)
			{	sm.byResult = nRet;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));
				return;
			}

			// Added by 정재웅(2005.12.27)
			// 12 제련 시 경험치 보너스 이벤트 수행을 위해서
			if( 11 == iPrevRefineLevel && 12 == sour->byRefineLevel )
			{
				char szMsg[1024] = { 0,0,0, };
				sprintf( szMsg, g_pMessageStringTable[_SuccessToRefine], pMob[conn].MOB.szName );
				PostMessageToZone( szMsg );

				TriggerEvent( conn, 52, pMob[conn].TargetX, pMob[conn].TargetY, 0, 121 );
			}

			//	SCP_RESP_ITEM_SET 전송
			S_SCP_RESP_ITEM_SET itemset;
			itemset.wType = SCP_RESP_ITEM_SET;
			itemset.byType = SET_ITEM_CREATE;
			itemset.byPlace = m->byPlace;
			itemset.byIndex = m->byIndex;
			memcpy(&(itemset.sitem), sour, sizeof(STRUCT_ITEM));
			pUser[conn].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

			sm.byResult=REPLY_ACK_OK;
			pUser[conn].cSock.AddMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));

			pUser[conn].cSock.SendMessage();
		}	break;
	case _MSG_ItemContribution:
		{	MSG_ItemContribution * m = (MSG_ItemContribution * ) msg;

			char szItemName[128]; byte byTrimuriti = pMob[conn].MOB.byTrimuriti;
			int nScale = 0; BYTE byRet = 0;
			if(g_GateTick[byTrimuriti]>0 && ( ServerIndex+1 == SERVER_KRUMA_HIGH ) )	//	문이 Gate화성화시 더이상의 헌납은 필요없다
			{	m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1;
			}
			if( ServerIndex+1 == SERVER_STRONGHOLD ) 
				if(g_kArena.IsProgressed() || g_iBattleForStronghold>0)	//	요새전진행시나 아레나이벤트 진행시는 헌납불가
				{ m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; }
			

			if(byRet == 0)
			{
				for(int i=0; i<MAX_ITEM_CONTRIBUTION; i++)		//	위치별 아이템 유효성 검사
				{
					STRUCT_ITEM *sour = NULL;
					STRUCT_ITEM tempItem;
					if	(m->byPlace[i]==ITEM_PLACE_INVEN)
					{	if (m->byIndex[i]>=0&&m->byIndex[i]<MAX_INVEN) sour = &pMob[conn].MOB.Inven[m->byIndex[i]];
						//if (m->SourPos<VISUAL_EQUIPPOS) CheckLook=1;
					}	else
					if	(m->byPlace[i]==ITEM_PLACE_EQUIP)
					{	if (m->byIndex[i]>=0&&m->byIndex[i]<(MAX_EQUIP-1))
						{	sour = &pMob[conn].MOB.Equip[m->byIndex[i]];
							tempItem = pMob[conn].MOB.Equip[m->byIndex[i]];
						}
					}	else
					if	(m->byPlace[i]==ITEM_PLACE_CARGO)
					{	if (m->byIndex[i]>=0&&m->byIndex[i]<MAX_CARGO) sour = &pUser[conn].Cargo[m->byIndex[i]];
					}	else
						continue;

					//	서버에 해당 아이템이 없을 경우 에러처리
					if(sour == NULL) {	m->byResult = REPLY_ITEM_CONTRIBUTION_OUTINDEX; byRet=1; break; }

					//	서버에 아이템에 대한 자료가 없을 경우 에러처리
					if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA) {	m->byResult = REPLY_ITEM_CONTRIBUTION_OUTINDEX; byRet=1; break; }

					//	아이템의 중첩갯수 체크(갯수가 0인 아이템을 헌납하는 핵발견)
					if(sour->byCount<=0) {	m->byResult = REPLY_UNKNOWN; byRet=1; break; }

					bool bResult=0; int nPrice=0; BYTE byMax=0;
					int nShopItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
					bResult  = g_ParamMgr.HT_bGetItemRupiah(nShopItemIndex, &nPrice); 
					bResult &= g_ParamMgr.HT_bGetItemMaxCount(nShopItemIndex, &byMax);

					//	파라메터 검색실패
					if(!bResult) { m->byResult = REPLY_ITEM_CONTRIBUTION_OUTPARAM; byRet=1; break; }

					//	퀘스트아이템의 경우 불가
					if ( CHTParamIDCheck::HT_bIsItemQuestOnly( nShopItemIndex ) ) { m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; break; }

					//	중첩아이템의 경우 불가
					if(byMax>1) { m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; break; } 
					
					//if(g_bIsInRvR)			//	주신전 크루마신단
					if( eZoneType_God == g_iZoneType )
					{	int nTemp = nPrice/(ITEM_CONTRIBUTION_DEVIDE*2);
						if(nTemp < 1) nTemp=1;
						nScale += nTemp;
					}
					else					//	아이템 제련항아리
					{
						if(g_ItemRefineScale<10000)		//	제련항아리 확률 10000/2000 이하일경우(아이템헌납)
						{	int nTemp = nPrice/ITEM_CONTRIBUTION_DEVIDE;
							if(nTemp < 1) nTemp=1;
							nScale += nTemp;
						}
						else
						{	int nTemp = nPrice/(ITEM_CONTRIBUTION_DEVIDE*10);
							nScale += nTemp;
						}
					}
				}
			}
			if((int)m->dwRupia > pMob[conn].MOB.nRupiah) { m->byResult = REPLY_ITEM_CONTRIBUTION_LACK; byRet=1; }

			if(byRet) { pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m)); return; }

            //	여기까지 왔다면 오류가 없는 패킷이라는 뜻이다.(삭제루틴가동)
			//if(g_bIsInRvR)			//	주신전 크루마신단
			if( ServerIndex+1 == SERVER_KRUMA_HIGH )
			{
				nScale += (m->dwRupia/(ITEM_CONTRIBUTION_DEVIDE*2));
				int nX = 0; int nZ = 0;
				if(byTrimuriti<0 || byTrimuriti>eTNClan_Siva)
				{	sprintf(temp, "clo char:%s msg_itemcontribution", pMob[conn].MOB.szName);
					Log(temp, pUser[conn].AccountName, pUser[conn].IP);
					CloseUser(conn); return; 
				}

				g_GateScale[byTrimuriti] += nScale; 
				if(g_GateScale[byTrimuriti] >= 10000)
				{
					g_GateScale[byTrimuriti] = 10000;
					g_GateTick[byTrimuriti] = 10;		//	32초마다 1씩감소 즉320초간 Gate활성화

					//	Gata Create
					if(byTrimuriti==eTNClan_Brahma)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Brahma, 0, 192, 239, 0, false, 0, 0, 11 );
					else if(byTrimuriti==eTNClan_Vishnu)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Vishnu, 0, 873, 365, 0, false, 0, 0, 12 );
					else if(byTrimuriti==eTNClan_Siva)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Siva, 0, 422, 890, 0, false, 0, 0, 13 );
					else
					{	sprintf(temp, "clo char:%s msg_itemcontribution2", pMob[conn].MOB.szName);
						Log(temp, pUser[conn].AccountName, pUser[conn].IP);
						CloseUser(conn); return; 
                    }
				}
			}	else
			if( ServerIndex+1 == SERVER_STRONGHOLD )
			{
				nScale = m->dwRupia;
				g_dwArenaMoney += nScale;
				if(g_dwArenaMoney>=MONEY_ARENAEVENT)				//	ARENA 이벤트 발생조건 - 1억이상의 아레나머니가 있고
				{	struct tm when; time_t now;						//	0~2시, 10~24시 사이면 이벤트를 발생한다.
					time(&now); when = *localtime(&now);
					if(when.tm_hour<2 || when.tm_hour>=10) g_kArena.Start( (int)g_dwArenaMoney ); //TriggerEvent( conn, 66, pMob[conn].TargetX, pMob[conn].TargetY, 0 );
				}
			}
			else					//	아이템 제련항아리
			{
				if(g_ItemRefineScale+nScale+(m->dwRupia/ITEM_CONTRIBUTION_DEVIDE)<10000)	//	제련항아리 확률 10000/2000 이하일경우(루피아헌납)
				{	nScale += (m->dwRupia/ITEM_CONTRIBUTION_DEVIDE);
				}
				else
				{	if(g_ItemRefineScale<10000)
					{	int nMoney = m->dwRupia - (10000-g_ItemRefineScale)*ITEM_CONTRIBUTION_DEVIDE;
						nScale = 10000 - g_ItemRefineScale + nMoney/(ITEM_CONTRIBUTION_DEVIDE*10);
					}
					else
						nScale += (m->dwRupia/(ITEM_CONTRIBUTION_DEVIDE*10));
				}
				g_ItemRefineScale += nScale; 
				if(g_ItemRefineScale >= 20200) g_ItemRefineScale = 20200;
				// 퀘스트에서 사용...
				QUEST_OnContribute( conn, m->dwRupia );
			}

			pMob[conn].DecGold(m->dwRupia); m->dwRupia = pMob[conn].MOB.nRupiah;

            for(int i=0; i<MAX_ITEM_CONTRIBUTION; i++)
			{
				if(m->byPlace[i]<0) continue;
				if(m->byPlace[i]==ITEM_PLACE_INVEN)
				{	if(BASE_CheckItemLog(&pMob[conn].MOB.Inven[m->byIndex[i]])){
						BASE_GetItemCode(&pMob[conn].MOB.Inven[m->byIndex[i]],szItemName);
						sprintf(temp,"cont %s",szItemName);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}
					S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
					sm.byPlace = ITEM_PLACE_INVEN; sm.byIndex = m->byIndex[i];
					sm.sitem = pMob[conn].MOB.Inven[m->byIndex[i]]; sm.byType = SET_ITEM_DELETE;
					pUser[conn].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
					memset(&pMob[conn].MOB.Inven[m->byIndex[i]], 0, sizeof(STRUCT_ITEM));
				}
				else if(m->byPlace[i]==ITEM_PLACE_EQUIP)
				{	if(BASE_CheckItemLog(&pMob[conn].MOB.Equip[m->byIndex[i]])){
						BASE_GetItemCode(&pMob[conn].MOB.Equip[m->byIndex[i]],szItemName);
						sprintf(temp,"cont %s",szItemName);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}
					S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
					sm.byPlace = ITEM_PLACE_EQUIP; sm.byIndex = m->byIndex[i];
					sm.sitem = pMob[conn].MOB.Equip[m->byIndex[i]]; sm.byType = SET_ITEM_DELETE;
					pUser[conn].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
					memset(&pMob[conn].MOB.Equip[m->byIndex[i]], 0, sizeof(STRUCT_ITEM));
				}
				else if(m->byPlace[i]==ITEM_PLACE_CARGO)
				{	if(BASE_CheckItemLog(&pUser[conn].Cargo[m->byIndex[i]])){
						BASE_GetItemCode(&pUser[conn].Cargo[m->byIndex[i]],szItemName);
						sprintf(temp,"cont %s",szItemName);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}
					S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
					sm.byPlace = ITEM_PLACE_CARGO; sm.byIndex = m->byIndex[i];
					sm.sitem = pUser[conn].Cargo[m->byIndex[i]]; sm.byType = SET_ITEM_DELETE;
					pUser[conn].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
					memset(&pUser[conn].Cargo[m->byIndex[i]], 0, sizeof(STRUCT_ITEM));
				}
			}

			m->byResult=REPLY_ACK_OK; 
			if( ServerIndex+1 == SERVER_KRUMA_HIGH ) m->snRefineScale = g_GateScale[byTrimuriti];
			//else if( ServerIndex+1 == SERVER_STRONGHOLD ) m->dwRupia = g_dwArenaMoney;
			else m->snRefineScale = g_ItemRefineScale;

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));
		}	break;
	case _MSG_RefineScale:
		{	MSG_RefineScale * m = (MSG_RefineScale * ) msg;

			if( ServerIndex+1 == SERVER_KRUMA_HIGH ) m->snRefineScale = g_GateScale[pMob[conn].MOB.byTrimuriti];
			else if( ServerIndex+1 == SERVER_STRONGHOLD ) m->dwRupiah = g_dwArenaMoney;
			else m->snRefineScale = g_ItemRefineScale;

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));
		}	break;
	case CSP_REQ_CHAT:				//	일반채팅	
		{	S_CSP_REQ_CHAT * m = (S_CSP_REQ_CHAT * ) msg;

			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			S_SCP_NOTIFY_CHAT sm;	sm.wType = SCP_NOTIFY_CHAT;
			sm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
			sm.nID=conn; sm.byTextColor=m->byTextColor; 
			sm.byBgColor = m->byBgColor; sm.byTrimuriti=m->byTrimuriti;

			m->szMsg[MAX_CHAT_LENGTH-1] = 0; m->szMsg[MAX_CHAT_LENGTH-2] = 0;
			strncpy(sm.szMsg, m->szMsg, MAX_CHAT_LENGTH);
			GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, conn, 20);
		}	break;
	case CSP_REQ_WHISPER_CHAT:		//	귀속말	
		{	S_CSP_REQ_WHISPER_CHAT * m = (S_CSP_REQ_WHISPER_CHAT * ) msg;

			m->szName[SZNAME_LENGTH-1] = 0; m->szName[SZNAME_LENGTH-2] = 0;
			m->szMsg[MAX_CHAT_LENGTH-1] = 0; m->szMsg[MAX_CHAT_LENGTH-2] = 0;

			// 캐릭터 이름으로 하나를 입력할 수 있는가? 그리고 수신인에 아무것도 넣지 않을 수 있는가?
			#ifdef __TN_PLAYMOVIE__
			AssistPlayMovie( conn, m->szMsg ); 
			#endif

			if( !strcmp( m->szName, "!!@@##$$" ) && ServerGroup==0)		//	테스트를 위해 테섭에서 일반케릭터로 실행가능하게 한다.
			{
				HelpGameMaster( conn, m->szMsg, false );
				return;
			}

			if( eTNClan_GM == pMob[conn].m_byClan )
			{   
				if( !strcmp( m->szName, "007Qkddkr" ) ) // 숫자 0으로 시작
				{
					HelpGameMaster( conn, m->szMsg );
					return;
				}
				else if( !strcmp( m->szName, "52anwndWjq" ) ) 
				{
					ControlSystem( conn, m->szMsg );
					return;
				}

				if( '/' == m->szMsg[0] ) return;
			}

			if( strncmp(pUser[conn].AccountName, Developer, ACCOUNTNAME_LENGTH)==0 )
			{
				HelpGameMaster( conn, m->szMsg );
				if( '/' == m->szMsg[0] ) return;
			}

			#ifdef __TN_LOCAL_SERVER_SWITCH__
			HelpGameMaster( conn, m->szMsg );
			ControlSystem( conn, m->szMsg );
			#endif


			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].m_byClan)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			int nOtherID = GetMOBID(m->szName);
			if(nOtherID > 0 && nOtherID<=MAX_USER)				//	동일지역내 상대방 존재
			{	
				S_SCP_RESP_WHISPER_CHAT sm; sm.wType=SCP_RESP_WHISPER_CHAT;	
				sm.byResult = REPLY_ACK_OK; sm.byTrimuriti=m->byTrimuriti;
				strncpy(sm.szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
				sm.byTextColor = m->byTextColor; sm.byBgColor = m->byBgColor;

				if(pMob[nOtherID].MOB.byStatus & 0x01) sm.byResult = REPLY_WHISPER_REJECT;	//	상대가 귓발차단모드일경우
				else
				{	S_SCP_NOTIFY_WHISPER_CHAT nm; nm.wType=SCP_NOTIFY_WHISPER_CHAT;
					strncpy(nm.szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
					strncpy((char*)nm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
					nm.byTextColor=m->byTextColor; nm.byBgColor=m->byBgColor; nm.byTrimuriti=m->byTrimuriti;
					pUser[nOtherID].cSock.SendOneMessage((char*)&nm, sizeof(nm));
				}

				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
			}
			else						//	동일지역에 상대방이 없을 경우
			{
				S_SSP_REQ_WHISPER_CHAT nm; nm.wType=SSP_REQ_WHISPER_CHAT; 
				nm.nID=conn; nm.byTrimuriti=m->byTrimuriti;
				nm.byTextColor = m->byTextColor; nm.byBgColor = m->byBgColor;
				strncpy(nm.szSourName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				strncpy(nm.szDestName, m->szName, SZNAME_LENGTH);
				strncpy((char*)nm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
				if(!DBServerSocket.SendOneMessage((char*)&nm,sizeof(S_SSP_REQ_WHISPER_CHAT)))
				{	Log("err whisperchat DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
			}
		}	break;
	case _MSG_Chat:
		{	MSG_Chat * m = (MSG_Chat * ) msg;

			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			m->szMsg[MAX_GROUPCHAT_LENGTH-1]=0; m->szMsg[MAX_GROUPCHAT_LENGTH-2]=0;
			strncpy(m->szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			m->byTrimuriti = pMob[conn].MOB.byTrimuriti;

			if(m->byMsgType == MESSAGE_PARTY)
			{	int leader=pMob[conn].Leader;
				if(leader==0) leader=conn;
				SendPartyMessage(leader, (MSG_STANDARD*)m);
			}	else
			if(m->byMsgType == MESSAGE_GUILD)
			{	if(pUser[conn].nGuildIndex!=0)
				{	//	SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*)m);
					//	길드채팅 타존으로 Broadcast(msg server를 이용하기로 한다)
					m->nGuildID = pMob[conn].MOB.nGuildID;
					MSGServerSocket.AddMessage((char*)m, sizeof(*m));
				}
				else
				{	if(pMob[conn].MOB.nGuildID!=0)			//	길드가 있는데 pUser에 등록되지 않은 경우이다.
					{	
						//int nIndex = GetGuild(pMob[conn].MOB.nGuildID);
						//if(nIndex>0 && nIndex<MAX_USER)		//	해당길드를 찾아 값을 재입력해준다.
						//{	//	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
						//	//	길드채팅 타존으로 Broadcast(msg server를 이용하기로 한다)
						//	m->nGuildID = pMob[conn].MOB.nGuildID;
						//	MSGServerSocket.SendOneMessage((char*)m, sizeof(*m));
						//	sprintf(temp, "err GuildMsg GuildID:%d nGuildIndex:%d but find Index:%d \r\n", pMob[conn].MOB.nGuildID, pUser[conn].nGuildIndex, nIndex );
						//	Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						//	pUser[conn].nGuildIndex = nIndex;
						//	pUser[conn].nGuildLevel = pGuild[nIndex].GetLevel(pMob[conn].MOB.szName);
						//}	else							//	pMob에 guildid가 있으나 그러한 길드데이터가 없을 경우이다.
						{	sprintf(temp, "err GuildMsg GuildID:%d but cannot find Index \r\n", pMob[conn].MOB.nGuildID );
							Log(temp,pUser[conn].AccountName,pUser[conn].IP);
							//pMob[conn].MOB.nGuildID=0;
						}
					}	else								//	길드가 없는데 길드메세지를 보낸경우이다.
					{	sprintf(temp, "err He is not GuildMember \r\n");
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}
				}
			}	else
			if(m->byMsgType == MESSAGE_GUILD_ALLIANCE)
			{	int nIndex = pUser[conn].nGuildIndex;	
				if(nIndex>=0 && nIndex<MAX_USER)
				{	//	길드채팅 타존으로 Broadcast(msg server를 이용하기로 한다)
					m->nGuildID = pMob[conn].MOB.nGuildID;
					m->nAlliedGuildID = pGuild[nIndex].nAlliedID;
					MSGServerSocket.AddMessage((char*)m, sizeof(*m));
				}
			}	else 	//	unknown type
				return;
		}	break;
	case _MSG_Broadcast:
		{	MSG_Broadcast * m = (MSG_Broadcast * ) msg;

			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			m->szMsg[MAX_NOTIFY_LENGTH-1]=0; m->szMsg[MAX_NOTIFY_LENGTH-2]=0;
			strncpy(m->szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			m->byTrimuriti = pMob[conn].MOB.byTrimuriti;

			if(m->byMsgType == MESSAGE_ZONE)
			{	
				if(pMob[conn].m_byClan != eTNClan_GM) return;
				SendToAll((MSG_STANDARD*)m);
			}	else
			if(m->byMsgType == MESSAGE_WORLD)
			{	
				if(pMob[conn].m_byClan != eTNClan_GM) return;
				if(!MSGServerSocket.SendOneMessage((char*)m,sizeof(*m)))
				{	Log("err brodcast MSG-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
			}	else
			if(m->byMsgType == MESSAGE_GAME)
			{
				return;	//	tool에서만 가능한 기능.
			}
			if(m->byMsgType == MESSAGE_BATTLEORDER)		//	작전명령서(주신전 => 모든존)
			{	if(ServerIndex+1!=SERVER_KRUMA_HIGH && ServerIndex+1!=SERVER_CHATURANGKA) return;	//	주신전이 아니면 사용불가
				int nPos = m->byTextColor;
				if( 0 > nPos || pMob[conn].byMaxInven <= nPos ) return;
				if( pMob[conn].MOB.Inven[nPos].snIndex+HT_PARAMTYPE_ITEM_START-1 != eItem_BattleOrder ) return;

				pMob[conn].MOB.Inven[nPos].byCount--;
				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nPos;
				itemset.sitem = pMob[conn].MOB.Inven[nPos];
				itemset.sitem.byCount = pMob[conn].MOB.Inven[nPos].byCount;
				if(pMob[conn].MOB.Inven[nPos].byCount<=0)	//	전부사용(아이템소멸)
				{	itemset.byType = SET_ITEM_DELETE;	//	아이템 소멸
					ZeroMemory(&pMob[conn].MOB.Inven[nPos], sizeof(STRUCT_ITEM));
				}	else									//	일부사용(중첩1개 소멸)
				{	itemset.byType = SET_ITEM_CREATE;	//	아이템 갱신
				}
				pUser[conn].cSock.SendOneMessage((char*)&itemset,sizeof(itemset));

				if(!MSGServerSocket.SendOneMessage((char*)m,sizeof(*m)))
				{	Log("err brodcast MSG-SEND MESSAGE_BATTLEORDER",pUser[conn].AccountName,pUser[conn].IP);
				}
			}
			if(m->byMsgType == MESSAGE_EXTRA)			//	호외(주신전이외의 모든존 => 주신전이외의 모든존)
			{	if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_CHATURANGKA) return;	//	주신전에서 사용불가
				int nPos = m->byTextColor;
				if( 0 > nPos || pMob[conn].byMaxInven <= nPos ) return;
				if( pMob[conn].MOB.Inven[nPos].snIndex+HT_PARAMTYPE_ITEM_START-1 != eItem_Extra ) return;

				pMob[conn].MOB.Inven[nPos].byCount--;
				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nPos;
				itemset.sitem = pMob[conn].MOB.Inven[nPos];
				itemset.sitem.byCount = pMob[conn].MOB.Inven[nPos].byCount;
				if(pMob[conn].MOB.Inven[nPos].byCount<=0)	//	전부사용(아이템소멸)
				{	itemset.byType = SET_ITEM_DELETE;	//	아이템 소멸
					ZeroMemory(&pMob[conn].MOB.Inven[nPos], sizeof(STRUCT_ITEM));
				}	else									//	일부사용(중첩1개 소멸)
				{	itemset.byType = SET_ITEM_CREATE;	//	아이템 갱신
				}
				pUser[conn].cSock.SendOneMessage((char*)&itemset,sizeof(itemset));

				if(!MSGServerSocket.SendOneMessage((char*)m,sizeof(*m)))
				{	Log("err brodcast MSG-SEND MESSAGE_EXTRA",pUser[conn].AccountName,pUser[conn].IP);
				}
			}
			else		//	unknown type
				return;

		}	break;
	case CSP_REQ_APPEAL_CHAT:
		{	S_CSP_REQ_APPEAL_CHAT * m = (S_CSP_REQ_APPEAL_CHAT *) msg;

			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			S_SSP_REQ_APPEAL_CHAT sm; sm.wType = SSP_REQ_APPEAL_CHAT;
			sm.nID = conn; strncpy(sm.szMsg,m->szMsg,MAX_CHAT_LENGTH);
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(S_SSP_REQ_APPEAL_CHAT)))
			{	Log("err appealchat DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		} break;
	case GCSP_REQ_CHARACTER_SEARCH:
		{	S_GCSP_REQ_CHARACTER_SEARCH * m = (S_GCSP_REQ_CHARACTER_SEARCH *) msg;
			S_SSP_REQ_CHARACTER_SEARCH sm; sm.wType = SSP_REQ_CHARACTER_SEARCH;
			sm.nID = conn;
			strncpy(sm.szCharName,m->szCharName,SZNAME_LENGTH);
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(S_SSP_REQ_CHARACTER_SEARCH)))
			{	Log("err charactersearch DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		} break;
		///////////////////////////////////////////////////////////////////////////////////////////////
	case _MSG_CreateGuild:
		{	MSG_CreateGuild* m = (MSG_CreateGuild*) msg;

			if(!ChatFilter(m->GuildName) && eTNClan_GM!=pMob[conn].MOB.byTrimuriti)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				return;
			}
			if(_mbsstr((unsigned char*)m->GuildName,(unsigned char*)"'")!=NULL)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				return;
			}

			int len=strlen(m->GuildName);
			if	(len<4 || len>=GUILDNAME_LENGTH)
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Name_Length]);
				return;
			}
			if	(pMob[conn].MOB.byTrimuriti==0)
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Make_Trimuriti]);
				return;
			}
			if	(pMob[conn].MOB.nRupiah<GUILD_CREATE_COST)
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Make_Want_Money]);
				return;
			}
			if	(pUser[conn].nGuildIndex!=0 || pMob[conn].MOB.nGuildID!=0)
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Make_Already]);	//	이미 길드에 가입되어 있을 경우
				return;
			}
			if(!NameFilter(m->GuildName) || !ChatFilter(m->GuildName))
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			//	길드생성비용을 제한다.(dba응답을 받고 제할시 돈이 모자랄수 있다.)
			pMob[conn].DecGold(GUILD_CREATE_COST);

			MSG_MobStatus nm; nm.wType=_MSG_MobStatus;
			nm.nID=conn; nm.byTradeMode=pUser[conn].byTradeMode;
			nm.nRupia=pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)&nm, sizeof(nm));
			
			// mark check.
			// party leader check, party member number limit check. party member trimurity check.

			MSG_CreateGuild sm; sm.wType = _MSG_CreateGuild;
			sm.Trimurity = pMob[conn].MOB.byTrimuriti;
			sm.GuildMark = m->GuildMark;
			strcpy(sm.Member.MemberName,pMob[conn].MOB.szName);
			sm.Member.byLevel = pMob[conn].MOB.byLevel;
			sm.Member.GuildRank = eGuildMaster;
			sm.Member.GuildState = 0;
			sm.Member.snTribe = pMob[conn].MOB.snTribe; 
			strcpy(sm.GuildName,m->GuildName);
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err createguild DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case _MSG_RemoveGuildMember:
		{	MSG_RemoveGuildMember * m = (MSG_RemoveGuildMember *)msg;

			if(g_iBattleForStronghold!=0) return;		//	요새전중에는 탈퇴가 불가능하다.

			int iguild = pUser[conn].nGuildIndex; // STRUCT_MOB:guildid -> CMob:guildindex
			int ilevel = pUser[conn].nGuildLevel;

			if	(iguild<=0 || iguild>MAX_USER)	// guildlevel:10 -> guild master
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Not_Guild_Member]);
				return;
			}
			if(m->byRemoveType==eGuild_Remove_me)
			{
			}	else
			if(m->byRemoveType==eGuild_Remove_you)
			{	if(ilevel<eGuildSubMaster)
				{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Have_No_Eject_Right]);
					return;
				}
			}	else
			if(m->byRemoveType==eGuild_Remove_All)
			{	if	(ilevel!=eGuildMaster)	
				{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Have_No_EjectAll_Right]);
					return;
				}
			}	else
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Remove_Type_Error]);
				return;
			}
			
			MSG_RemoveGuildMember sm; sm.wType = _MSG_RemoveGuildMember;
			sm.GuildID = pMob[conn].MOB.nGuildID;
			//sm.nID = conn;
			strcpy(sm.CharacterName,m->CharacterName);
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err removeguild DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}

		}	break;
	case _MSG_REQGuild:
		{	MSG_REQGuild * m = (MSG_REQGuild *)msg;

			int iguild = pUser[conn].nGuildIndex; // STRUCT_MOB:guildid -> CMob:guildindex
			int ilevel = pUser[conn].nGuildLevel;

			if(g_iBattleForStronghold!=0) return;		//	요새전중에는 가입이 불가능하다.

			if	(iguild<=0 || ilevel<eGuildThird)		//	마하라자, 라자, 르루바자가능
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Have_No_Invite_Right]);
				return;
			}

			//strupr(m->CharacterName);
			int target = GetMOBID(m->CharacterName);
			if	(target<=0 || target>=MAX_USER || pUser[target].Mode!=USER_PLAY)
			{	SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Others]); return;
			}

			if(pMob[conn].MOB.byTrimuriti != pMob[target].m_byClan)		//	주신을 체크한다.
			{	SendClientMessage(conn,g_pMessageStringTable[_Not_Same_Trimuriti]); 
				return;
			}
			if	(pUser[target].nGuildIndex!=0 || pMob[target].MOB.nGuildID!=0)
			{	SendClientMessage(conn, g_pMessageStringTable[_Guild_Make_Already]);	//	이미 길드에 가입되어 있을 경우
				return;
			}

			strcpy(pUser[conn].InviteName,m->CharacterName);
			//
			//send parcket to target	
			MSG_REQGuild	sm;	sm.wType = _MSG_REQGuild;
			sm.GuildID = pGuild[iguild].GUILD.GuildID;
			strcpy(sm.GuildName,	pGuild[iguild].GUILD.GuildName);
			strcpy(sm.CharacterName,pMob[conn].MOB.szName);
			pUser[target].cSock.AddMessage((char*)&sm,sizeof(sm));

			//char temp[256];
			//sprintf(temp,"%s of %s guild, invited you",pMob[conn].MOB.szName, pGuild[iguild].GUILD.GuildInfo.GuildName);
			//SendClientMessage(conn,temp);
		}	break;
	case _MSG_CNFGuild:
		{	MSG_CNFGuild * m = (MSG_CNFGuild *)msg;

			if(g_iBattleForStronghold!=0) return;		//	요새전중에는 가입이 불가능하다.

			int nGuildIndex = GetGuild(m->GuildID, FLAG_CLOSE);
			if(nGuildIndex==-1)	//	길드정보가져오기 실패
			{	char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[_MSG_CNFGuild] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID );
				WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );
			}
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER)							//	길드인덱스가 없을경우
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Not_Fine_Guild]); return;			//	초청자가 없어졋을 경우
			}

			m->CharacterName[SZNAME_LENGTH-1]=0; m->CharacterName[SZNAME_LENGTH-2]=0;
			int nOtherID = GetMOBID(m->CharacterName);
			if(nOtherID<=0 || nOtherID>=MAX_USER)								//	초청자의 존재를 체크한다.
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Not_Fine_Requestor]); return;
			}
			if(pMob[conn].MOB.byTrimuriti != pMob[nOtherID].m_byClan)			//	주신을 체크한다.
			{	SendClientMessage(conn,g_pMessageStringTable[_Not_Same_Trimuriti]); return;
			}

			MSG_AddGuildMember sm; sm.wType = _MSG_AddGuildMember;
			sm.GuildID=m->GuildID; sm.nID=conn;
			strcpy(sm.Member.MemberName,pMob[conn].MOB.szName);
			sm.Member.byLevel = pMob[conn].MOB.byLevel;
			sm.Member.GuildRank = eGuildMember;
			sm.Member.GuildState = 0;
			sm.Member.snTribe = pMob[conn].MOB.snTribe; 
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err addguildmember DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case _MSG_GuildUpdate:
		{	MSG_GuildUpdate * m = (MSG_GuildUpdate *)msg;
			if(pUser[conn].nGuildLevel < eGuildThird)
			{	SendClientMessage(conn, g_pMessageStringTable[_Guild_Update_No_Right]);
				break;
			}

			int nGuildIndex = pUser[conn].nGuildIndex;
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;

			m->nID=conn; m->GuildID=pMob[conn].MOB.nGuildID;
			strncpy(m->AlliedGuildName1, pGuild[nGuildIndex].GUILD.AlliedGuildName1, GUILDNAME_LENGTH);
			strncpy(m->AlliedGuildName2, pGuild[nGuildIndex].GUILD.AlliedGuildName2, GUILDNAME_LENGTH);
			strncpy(m->EnemyGuildName1, pGuild[nGuildIndex].GUILD.EnemyGuildName1, GUILDNAME_LENGTH);
			m->GuildMessage[GUILDMESSAGE_LENGTH-1]=0; m->GuildMessage[GUILDMESSAGE_LENGTH-2]=0;
			if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
			{	Log("err guildupdate DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case _MSG_GuildSetRanking:
		{	MSG_GuildSetRanking * m = (MSG_GuildSetRanking *)msg;

			int iguild = pUser[conn].nGuildIndex; // STRUCT_MOB:guildid -> CMob:guildindex
			int ilevel = pUser[conn].nGuildLevel;
			m->CharacterName[SZNAME_LENGTH-1]=0;
			m->CharacterName[SZNAME_LENGTH-2]=0;

			if	(iguild<=0 || iguild>MAX_USER || ilevel<eGuildMaster)	// guildlevel:10 -> guild master
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Rank_No_Right]);
			return;
			}
			if(m->GuildRank==eGuildMaster)
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Rank_Full]);
				return;
			}
			if(m->GuildRank>eGuildMaster || m->GuildRank<0)
			{	SendClientMessage(conn,g_pMessageStringTable[_Bad_Network_Packets]);
				AddCrackError(conn,10,CRACK_NOUSER_TRADE);
				return;
			}
			if(!strncmp(pMob[conn].MOB.szName, m->CharacterName, SZNAME_LENGTH)) return;

			m->nID = conn;
			m->nGuildID = pMob[conn].MOB.nGuildID;

			if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
			{	Log("err guildsetranking",pUser[conn].AccountName,pUser[conn].IP);
			}

		}	break;
	case _MSG_GuildUpdateMark:
		{	MSG_GuildUpdateMark * m = (MSG_GuildUpdateMark *)msg;
			
			int iguild = pUser[conn].nGuildIndex;	//	STRUCT_MOB:guildid -> CMob:guildindex
			int ilevel = pUser[conn].nGuildLevel;
			int nRupia = 0; int nCash = 0; bool bRet = true;
			int nIndex = pUser[conn].nGuildIndex;
			int nItemIndex = 0;
			m->byResult = REPLY_ACK_OK;

			if(pGuild[iguild].GUILD.Mark==0) nItemIndex = eItem_ChangeGuildMark;
			else nItemIndex = eItem_ChangeOldGuildMark;

			while(1)
			{	DWORD dwMark = m->Mark;
				DWORD dwGuildEmblem	= (dwMark & 0x000000FF);
				DWORD dwGuildTitle	= (dwMark & 0x0000FF00) >> 8;
				DWORD dwGuildColor	= (dwMark & 0x00FF0000) >> 16;
				
				if(nIndex==0) { m->byResult = REPLY_UNKNOWN; break; }
				if(m->byCostType==1)	//	1:Rupia, 2: Cash
				{	bRet = g_ParamMgr.HT_bGetItemRupiah(nItemIndex, &nRupia); 
					if	(pMob[conn].MOB.nRupiah<nRupia) { m->byResult = REPLY_GUILDMARK_MONEY; break; }
				}	else
				if(m->byCostType==2)
				{	bRet = g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash);
					if	(pUser[conn].m_nCash<nCash) { m->byResult = REPLY_GUILDMARK_MONEY; break; }
				}
				if(!bRet) { m->byResult = REPLY_GUILDMARK_PARAM; break; }
				if	(iguild<=0 || ilevel<eGuildMaster) { m->byResult = REPLY_GUILDMARK_RIGHT; break; }

				//	길드마크가 정상적인 데이터라고 판단한다.
				if (dwGuildEmblem < 1 || dwGuildEmblem > 72 || dwGuildTitle < 1 || dwGuildTitle > 84 || dwGuildColor < 1 || dwGuildColor > 72 )
				{ m->byResult = REPLY_UNKNOWN; break; }
				break;
			}

			if(m->byResult != REPLY_ACK_OK)
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
				return;
			}

			//	길드마크생성비용을 제한다.(dba응답을 받고 제할시 돈이 모자랄수 있다.)
			if(m->byCostType==1)	//	1:Rupia, 2: Cash
			{	pMob[conn].DecGold(nRupia);								//	루피아를 감소시킨다.
				m->nMoney = pMob[conn].MOB.nRupiah;
			}	else
			if(m->byCostType==2)
			{	pUser[conn].m_nCash -= nCash;							//	타니를 감소시킨다.
				m->nMoney = pUser[conn].m_nCash;

				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash; nm.nID=conn; 
					nm.byType=eRun; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					nm.nCash=nCash; nm.snItemIndex = nItemIndex; 
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash2; nm.ID=conn; 
					nm.C_Type = 3; 
					nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
					strcpy(nm.Order_Type,"I0");
					strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
					unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
					sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
					nm.Amount=-nCash; sprintf(nm.Item_no, "%d", nItemIndex + HT_PARAMTYPE_ITEM_START - 1);
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
			}

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	유저에게 길드마크 생성결과를 알린다.

			sprintf(temp, "gld Guild Mark Create Char:%s, GuildID:%d, CostType:%d ", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID, m->byCostType);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			
			m->GuildID=pMob[conn].MOB.nGuildID; 

			if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
			{	Log("err guildupdatemark DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case _Msg_GuildAlliance:			//	동맹길드 하나만 활성화 한다.(1,2의 구분과 등록은 차후에 구현..)
		{			
			Msg_GuildAlliance* m = (Msg_GuildAlliance*)msg;

			if(pMob[conn].MOB.nGuildID==0) return;		//	길드가 없을 경우 
			if(m->byAct==eGuildAllianceIn && m->byType == eGuildFriend)
			{
				if(m->nID<=0 || m->nID>=MAX_USER) return;
				if(pMob[conn].MOB.byTrimuriti != pMob[m->nID].MOB.byTrimuriti)
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL); 
					return;
				}
			}

			MSG_GuildUpdate sm; sm.wType = _MSG_GuildUpdate;
			int nMaster = 0; int nGuildIDYou = 0; 
			int nGuildIDMe = IsGuildMemberIn(pMob[conn].MOB.nGuildID);
			if(pUser[conn].m_nAllianceUser>0 && (nGuildIDMe<0 || nGuildIDMe>MAX_USER)) 									//	내가 길드원이 아닐경우
			{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL); 
				return;
			}
			if(pUser[conn].m_nAllianceUser>0 && (pGuild[nGuildIDMe].GetLevel(pMob[conn].MOB.szName)!=eGuildMaster)) 	//	내가 길마가 아닐경우
			{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL); 
				return;
			}

			if(m->byAct == eGuildAllianceOut)		//	동맹, 적대 해제일 경우
			{
				if(m->byType == eGuildFriend)
				{
					if(pGuild[nGuildIDMe].GUILD.AlliedGuildName1[0]==0) return;	//	동맹길드가 없는데 해제요청시

					nGuildIDYou = GetGuildID(pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
					nGuildIDYou = IsGuildMemberIn(nGuildIDYou); 
					if(nGuildIDYou<=0 || nGuildIDYou>=MAX_USER)	//	상대길드원이 현재의 존에 없을 경우
					{
						CGuild OtherGuild;
						sm.nID = 0; sm.GuildID = GetGuildID(pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
						if(ReadGuildFile(sm.GuildID, &OtherGuild))		//	상대 길드에 대한 정보를 존서버가 찾음.
						{
							ZeroMemory(sm.AlliedGuildName1, SZGUILD_LENGTH);
							strncpy(sm.AlliedGuildName2, OtherGuild.GUILD.AlliedGuildName2, SZGUILD_LENGTH);
							strncpy(sm.EnemyGuildName1, OtherGuild.GUILD.EnemyGuildName1, SZGUILD_LENGTH);
							strncpy(sm.GuildMessage, OtherGuild.GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
							if(!DBServerSocket.AddMessage((char*)&sm, sizeof(sm)))
							{	Log("err guildupdate2 DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
							}
						}
						else											//	상대 길드에 대한 정보를 존서버가 찾지 못함.
						{
							sprintf(temp, "err Find Guild : %s", pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
							Log(temp,pUser[conn].AccountName, pUser[conn].IP);
						}
					}
					else											//	상대길드원이 현재의 존에 있을 경우	
					{	sm.nID = 0; sm.GuildID = pGuild[nGuildIDYou].GUILD.GuildID;
						ZeroMemory(sm.AlliedGuildName1, SZGUILD_LENGTH);
						strncpy(sm.AlliedGuildName2, pGuild[nGuildIDYou].GUILD.AlliedGuildName2, SZGUILD_LENGTH);
						strncpy(sm.EnemyGuildName1, pGuild[nGuildIDYou].GUILD.EnemyGuildName1, SZGUILD_LENGTH);
						strncpy(sm.GuildMessage, pGuild[nGuildIDYou].GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
						if(!DBServerSocket.AddMessage((char*)&sm, sizeof(sm)))
						{	Log("err guildupdate2 DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
						}
					}

					strncpy(sm.EnemyGuildName1,  pGuild[nGuildIDMe].GUILD.EnemyGuildName1, SZGUILD_LENGTH);
					ZeroMemory(sm.AlliedGuildName1, SZGUILD_LENGTH);
				}
				else
				if(m->byType == eGuildHost)
				{
					if(pGuild[nGuildIDMe].GUILD.EnemyGuildName1[0]==0) return;	//	적대길드가 없는데 해제요청시

					strncpy(sm.AlliedGuildName1,  pGuild[nGuildIDMe].GUILD.AlliedGuildName1, SZGUILD_LENGTH);
					ZeroMemory(sm.EnemyGuildName1, SZGUILD_LENGTH);
				}
				else
					return;

				m->byResult = REPLY_GUILDALLIANCE_SUCCESS;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

				sm.nID = conn; sm.GuildID = pMob[conn].MOB.nGuildID;
				strncpy(sm.AlliedGuildName2, pGuild[nGuildIDMe].GUILD.AlliedGuildName2, SZGUILD_LENGTH);
				strncpy(sm.GuildMessage, pGuild[nGuildIDMe].GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
				if(!DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm)))
				{	Log("err guildupdate2 DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}

				//	DB 로 정보갱신 알림후 요새전일 경우 연합해체요청길드와 상대길드 모두 워프(저장지역)
				if(m->byType==eGuildFriend && (ServerIndex+1)==SERVER_STRONGHOLD)		
				{
					{
						//SYSTEMTIME st;
						//GetLocalTime( &st );
						char chBuf[256] = { 0,0,0, };
						sprintf(chBuf, "\r\n\n[%dMM%dDD %dHH%dMS%dSS] type:%d, guild:%d \r\n"
							, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
							, m->byType, pMob[conn].MOB.nGuildID
							);
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
					}

					int nMember = 0;
					S_SCP_RESP_INIT_REGEN_CHAR sm;
					sm.wType = SCP_RESP_INIT_REGEN_CHAR;
					for(int i=0;i<MAX_GUILD_MEMBER;i++)
					{
						nMember = pGuild[nGuildIDMe].pMemberIndex[i];
						if(nMember==0) continue;

						sm.byZone = pMob[nMember].MOB.bySaveZone;
						pMob[nMember].m_kWaitAction.iAction = eWaitAct_ZonePortal;
						pUser[nMember].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 
					}

					for(i=0;i<MAX_GUILD_MEMBER;i++)
					{
						nMember = pGuild[nGuildIDYou].pMemberIndex[i];
						if(nMember==0) continue;

						sm.byZone = pMob[nMember].MOB.bySaveZone;
						pMob[nMember].m_kWaitAction.iAction = eWaitAct_ZonePortal;
						pUser[nMember].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 
					}
				}

				return;
			}

			if(m->byType == eGuildFriend)
			{
				nMaster = m->nID;

				if(nMaster<0 || nMaster>MAX_USER || pUser[nMaster].Mode!=USER_PLAY)		//	상대의 플레이상태를 검사
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_DISCONNECT); 
					return;
				}
				nGuildIDYou = IsGuildMemberIn(pMob[nMaster].MOB.nGuildID);
				if(nGuildIDYou<=0 || nGuildIDYou>=MAX_USER)								//	상대가 길드원이 아닐경우
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL); 
					return;
				}
				if(pGuild[nGuildIDYou].GetLevel(pMob[nMaster].MOB.szName)!=eGuildMaster) //	상대가 길마가 아닐경우
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_LEVEL); 
					return;
				}

				bool bHaveMe = false; bool bHaveYou = false;		//	양쪽아쉬람 모두 요새를 소유하고 있을경우 동맹불가
				for(int i=0; i<eStronghold_MaxCount; i++)
				{
					if(!bHaveMe && strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIDMe].GUILD.GuildName, SZGUILD_LENGTH)==0) bHaveMe = true;
					if(!bHaveYou && strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIDYou].GUILD.GuildName, SZGUILD_LENGTH)==0) bHaveYou = true;
				}

				if(pUser[conn].m_nAllianceUser==m->nID && pUser[conn].m_byAllianceMode==eGuildAllianceMode_Request) 
					return;			// 기요청 메세지일 경우
				
				if(pGuild[nGuildIDMe].GUILD.AlliedGuildName1[0] != 0)						//	이미 동맹이 있을경우 
				{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_ALREADY);
					RemoveAlliance(conn, REPLY_GUILDALLIANCE_ALREADY);
					return;
				}
				else if(pGuild[nGuildIDYou].GUILD.AlliedGuildName1[0] != 0)					//	이미 동맹이 있을 경우
				{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_ALREADY);
					return;
				}

				//	요청메세지인지 응답메세지인지를 판단
				if(conn == pUser[nMaster].m_nAllianceUser && pUser[conn].m_byAllianceMode == eGuildAllianceMode_Response)
				{	
					if(m->byResult == REPLY_GUILDALLIANCE_CANCEL)	//	연합거부시
					{	RemoveAlliance(pUser[nMaster].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL);
						return;
					}

					if(m->byResult != REPLY_GUILDALLIANCE_SUCCESS)
					{	Log("err _Msg_GuildAlliance : UNKNOWN ACK", pUser[conn].AccountName, pUser[conn].IP);
						RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL);
						return;
					}

					if(bHaveMe && bHaveYou)		//	양측모두 요새를 소유하고 있을경우
					{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL);
						RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL);
						return;
					}
					
					MSG_GuildUpdate sm;	ZeroMemory(&sm, sizeof(sm));
					sm.wType = _MSG_GuildUpdate;
					sm.nID = conn; sm.GuildID = pMob[conn].MOB.nGuildID;
					strncpy(sm.AlliedGuildName1, pGuild[nGuildIDYou].GUILD.GuildName, SZGUILD_LENGTH);
					strncpy(sm.AlliedGuildName2, pGuild[nGuildIDMe].GUILD.AlliedGuildName2, SZGUILD_LENGTH);
					strncpy(sm.EnemyGuildName1, pGuild[nGuildIDMe].GUILD.EnemyGuildName1, SZGUILD_LENGTH);
					strncpy(sm.GuildMessage, pGuild[nGuildIDMe].GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
					if(!DBServerSocket.AddMessage((char*)&sm, sizeof(sm)))
					{	Log("err guildupdate2 DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
					}

					sm.nID = nMaster; sm.GuildID = pMob[nMaster].MOB.nGuildID;
					strncpy(sm.AlliedGuildName1, pGuild[nGuildIDMe].GUILD.GuildName, SZGUILD_LENGTH);
					strncpy(sm.AlliedGuildName2, pGuild[nGuildIDYou].GUILD.AlliedGuildName2, SZGUILD_LENGTH);
					strncpy(sm.EnemyGuildName1, pGuild[nGuildIDYou].GUILD.EnemyGuildName1, SZGUILD_LENGTH);
					strncpy(sm.GuildMessage, pGuild[nGuildIDYou].GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
					if(!DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm)))
					{	Log("err guildupdate3 DB-SEND",pUser[nMaster].AccountName,pUser[nMaster].IP);
					}

					pUser[conn].m_nAllianceUser = 0;
					pUser[conn].m_byAllianceMode = eGuildAllianceMode_Normal;
					pUser[nMaster].m_nAllianceUser = 0;
					pUser[nMaster].m_byAllianceMode = eGuildAllianceMode_Normal;
				}
				else	//	상대에게 요청						
				{
					if(pUser[nMaster].m_byAllianceMode!=eGuildAllianceMode_Normal)	//	상대가 타길드와 연합모드 대기중일 경우
					{	m->byResult = REPLY_GUILDALLIANCE_CANCEL;
						pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));	return;
					}

					if(bHaveMe && bHaveYou)		//	양측모두 요새를 소유하고 있을경우
					{	m->byResult = REPLY_GUILDALLIANCE_CANCEL;
						pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));	return;
					}

					m->nID = conn; 
					pUser[conn].m_nAllianceUser = nMaster;
					pUser[conn].m_byAllianceMode = eGuildAllianceMode_Request;
					pUser[nMaster].m_nAllianceUser = conn;
					pUser[nMaster].m_byAllianceMode = eGuildAllianceMode_Response;
					pUser[nMaster].cSock.SendOneMessage((char*)m, sizeof(*m));
				}
			}
			else if(m->byType == eGuildHost)
			{	return;		//	추후구현한다.
			}
			else
				return;
		}	break;	
	case _Msg_GuildCargoUsingLevel:		//	공지용(전존공지), 마하라자만 이용가능
		{	Msg_GuildCargoUsingLevel * m = (Msg_GuildCargoUsingLevel*) msg;

			int nIndex = pUser[conn].nGuildIndex;
			if(nIndex<=0 || nIndex>=MAX_USER) return;			//	길드원이 아닌데 길드기능요청시
			if(pUser[conn].nGuildLevel != eGuildMaster) return; //	마하라자가 아니면 사용안됨
			m->nGuildID = pGuild[nIndex].GUILD.GuildID;

			DBServerSocket.SendOneMessage((char*)m, sizeof(*m));	//	전존공지
		}	break;
	case _Msg_GuildCargoTimeExtension:	//	창고사용기간연장, 마하라자만 이용가능
		{	Msg_GuildCargoTimeExtension * m = (Msg_GuildCargoTimeExtension*) msg;

			BYTE byType = m->byType;
			if(byType<=0 || byType>3) return;	//	적립타입은(1: 1번사용, 2: 1,2번사용, 3: 1,2,3번사용)

			int nCost = 0;
			if(byType == 1)						//	루피아를 체크한다
				nCost = GUILDCARGO_TYPE1;
			else if(byType == 2)
				nCost = GUILDCARGO_TYPE2;
			else if(byType == 3)
				nCost = GUILDCARGO_TYPE3;
			else
				return;

			int nGuildIndex = pUser[conn].nGuildIndex;
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	길드원이 아닌데 길드기능요청시
			if(pUser[conn].nGuildLevel != eGuildMaster) return; //	마하라자가 아니면 사용안됨

			if(pMob[conn].MOB.nRupiah<nCost) return;
			//{	m->byResult = 1;
			//	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
			//	return;
			//}

			char pch[256];	sprintf(pch,"gld char:%s expand guildcargo %d-EA for 1month ", pMob[conn].MOB.szName, byType);
			Log(pch, pUser[conn].AccountName, pUser[conn].IP);

			pMob[conn].MOB.nRupiah -= nCost;
			m->byResult = (BYTE)S_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	결과를 요청자에게 알린다.

			DWORD dwTime[3] = {0,};
			pGuild[nGuildIndex].GetCargoTime(&dwTime[0], &dwTime[1], &dwTime[2]);
			time_t now; time(&now);
			switch(byType)
			{
			case 3:
				if(now>(int)dwTime[2])
					dwTime[2] = now+30*24*3600;
				else
					dwTime[2] += 30*24*3600;
			case 2:
				if(now>(int)dwTime[1])
					dwTime[1] = now+30*24*3600;
				else
					dwTime[1] += 30*24*3600;
			case 1:
				if(now>(int)dwTime[0])
					dwTime[0] = now+30*24*3600;
				else
					dwTime[0] += 30*24*3600;
			}

			Msg_GuildCargoTime sm; sm.wType = _Msg_GuildCargoTime;
			sm.nGuildID = pMob[conn].MOB.nGuildID;
			sm.dwTime[0] = dwTime[0];
			sm.dwTime[1] = dwTime[1];
			sm.dwTime[2] = dwTime[2];
			DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm));	//	전존공지
		}	break;
	case _Msg_GuildItem:
		{	Msg_GuildItem * m = (Msg_GuildItem*)msg;

			int nGuildIndex = pUser[conn].nGuildIndex;
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	길드원이 아닌데 길드기능요청시
			memcpy(m->arrItem, pGuild[nGuildIndex].GUILD.Repository, sizeof(m->arrItem));
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	결과를 요청자에게 알린다.
		}	break;
	//case _Msg_GuildCargoUse:			//	길원이 창고사용요청시
	//	{	Msg_GuildCargoUse * m = (Msg_GuildCargoUse*)msg;

	//		int nGuildIndex = pUser[conn].nGuildIndex;
	//		if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	길드원이 아닌데 길드기능요청시
	//		m->byResult = 1;
	//		if(m->bySet == 1 && pGuild[nGuildIndex].szCargoMember[0]==0)	//	세팅실행
	//		{	m->byResult = 0;
	//			strncpy(pGuild[nGuildIndex].szCargoMember, pMob[conn].MOB.szName, SZNAME_LENGTH);
	//		}
	//		else if(m->bySet == 0 && strncmp(pMob[conn].MOB.szName, pGuild[nGuildIndex].szCargoMember, SZNAME_LENGTH)==0)
	//		{	m->byResult = 0;
	//			ZeroMemory(pGuild[nGuildIndex].szCargoMember, SZNAME_LENGTH);
	//		}

	//		pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

	//		if(m->byResult == 0)
	//		{	Msg_GuildCargoUseUpdate sm; sm.wType = _Msg_GuildCargoUseUpdate;
	//			sm.nGuildID = pGuild[nGuildIndex].GUILD.GuildID;
	//			strncpy(sm.pUsingMember, pGuild[nGuildIndex].szCargoMember, SZNAME_LENGTH);
	//			SendGuildMessage(nGuildIndex, (MSG_STANDARD*)&sm);
	//		}
	//	}	break;
	case  _MSG_REQParty:	// 파티요청
		{	MSG_REQParty * m = (MSG_REQParty*) msg;

			int leader = conn;
			int target = m->TargetID;

			if  (leader<=0||leader>=MAX_USER||leader!=conn) // GetEmptyUser는 1부터 시작한다.
			{   Log("err REQParty leader out of range",pUser[conn].AccountName,pUser[conn].IP);
				return;
			}
			if  (pMob[leader].Leader!=0)
			{	SendClientMessage(conn,  g_pMessageStringTable[_Dropped_Current_Party_First]);
				return;
			}
			if	(ServerIndex+1==SERVER_STRONGHOLD)			//	요새전에서는 아쉬람이 같거나 연합일 경우만 파티가 가능하다
			{	
				if(pMob[conn].MOB.nGuildID<=0 || pMob[target].MOB.nGuildID<=0) return;
				int nMyGuild = IsGuildMemberIn(pMob[conn].MOB.nGuildID);
				int nYouGuild = IsGuildMemberIn(pMob[target].MOB.nGuildID);
				if(nMyGuild<=0 || nMyGuild>=MAX_USER || nYouGuild<=0 || nYouGuild>=MAX_USER) return;
				if(pMob[conn].MOB.nGuildID != pMob[target].MOB.nGuildID && 
					strncmp(pGuild[nMyGuild].GUILD.AlliedGuildName1, pGuild[nYouGuild].GUILD.GuildName, SZNAME_LENGTH)!=0) return;
			}

   			if  (target<=0||target>=MAX_USER)	{	Log("err REQParty target out of range",pUser[conn].AccountName,pUser[conn].IP);	return;	}
			if  (pUser[target].Mode!=USER_PLAY)	{   SendClientMessage(conn,  g_pMessageStringTable[_Not_Connected]);				return;	}
			if  (pMob[target].Leader!=0)		{	SendClientMessage(conn,  g_pMessageStringTable[_Have_Own_Party_Already]);		return;	}
			for (int i=0;i<MAX_PARTY;i++)
			{   int fol = pMob[target].m_irgParty[i];
	   	  		if  (fol!=0)					{	SendClientMessage(conn,  g_pMessageStringTable[_Have_Own_Party_Already]);	return; }
			}

			strncpy(pUser[target].m_pPartyRequester, pMob[leader].MOB.szName, SZNAME_LENGTH);
			SendReqParty(target,leader);
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case _MSG_CNFParty:	// 파티 승인
		{	MSG_CNFParty * m = (MSG_CNFParty*) msg;

			int fol = conn;
			int leader   = m->TargetID;
			if  (leader<=0||leader>=MAX_USER)	{Log("err CNFParty leader out of range",pUser[conn].AccountName,pUser[conn].IP); return;	}
			if  (fol<=0||fol>=MAX_USER||fol!=conn) {Log("err CNFParty fol out of range",pUser[conn].AccountName,pUser[conn].IP); return;	}
			if	(conn==leader) {Log("err CNFParty fol out of range",pUser[conn].AccountName,pUser[conn].IP); return;	}
			if  (pMob[leader].Leader!=0)		{SendClientMessage(conn,  g_pMessageStringTable[_Have_Own_Party_Already]); return; }
			if  (pUser[leader].Mode!=USER_PLAY)	{SendClientMessage(conn,  g_pMessageStringTable[_Not_Connected]);   return; }
			if  (pMob[fol].Leader!=0)			{SendClientMessage(conn,  g_pMessageStringTable[_Dropped_Current_Party_First]);	return;}
			for (int i=0;i<MAX_PARTY;i++)
			{	if	(pMob[fol].m_irgParty[i]!=0)	{SendClientMessage(conn, g_pMessageStringTable[_Dropped_Current_Party_First]);return;}
			}
			if	(ServerIndex+1==SERVER_STRONGHOLD)			//	요새전에서는 아쉬람이 같아야 파티가 가능하다
			{
				if(pMob[conn].MOB.nGuildID<=0 || pMob[leader].MOB.nGuildID<=0) return;
				int nMyGuild = IsGuildMemberIn(pMob[conn].MOB.nGuildID);
				int nYouGuild = IsGuildMemberIn(pMob[leader].MOB.nGuildID);
				if(nMyGuild<=0 || nMyGuild>=MAX_USER || nYouGuild<=0 || nYouGuild>=MAX_USER) return;
				if(pMob[conn].MOB.nGuildID != pMob[leader].MOB.nGuildID && 
					strncmp(pGuild[nMyGuild].GUILD.AlliedGuildName1, pGuild[nYouGuild].GUILD.GuildName, SZNAME_LENGTH)!=0) return;
			}

			int	numfol=0; int nLevel=0;
			for	(i=0;i<MAX_PARTY;i++)	{if	(pMob[leader].m_irgParty[i]==0)	break;		}
			if	(i==MAX_PARTY)			{SendClientMessage(conn,  g_pMessageStringTable[_Partys_Full]);return;  }

			if(strncmp(pUser[conn].m_pPartyRequester, pMob[leader].MOB.szName, SZNAME_LENGTH)) return;

			SendAddParty(leader,fol,leader);		//	파티장에게 새로운파티원가입을 알린다.
			SendAddParty(fol, leader, leader);		//	새로운파티원에게 파티장을 알린다.
			for	(int k=0;k<MAX_PARTY;k++)
			{	int	f = pMob[leader].m_irgParty[k];
	   			if	(f==0) continue;
				SendAddParty(f,fol,leader);			//	파티원에게 새로운 파티원가입을 알린다.
				SendAddParty(fol,f,leader);			//	새로운파티원에게 새티원의 정보를 알린다.
			}

			pMob[leader].m_irgParty[i] = fol;		//	새로운 파티원을 파티에 가입시킨다.
			pMob[fol].Leader = leader;
		}	break;
	case  _MSG_RemoveParty:	// 파티제거
		{	MSG_RemoveParty * m = (MSG_RemoveParty*) msg;
			int target = m->nTargetID;
			if	(m->nTargetID != conn)	//	방출
			{	if	(m->nTargetID<=0 || m->nTargetID>MAX_USER)
				{	Log("err wrong nid in remove party",pUser[conn].AccountName,pUser[conn].IP);
					return;
				}
				if	(pMob[m->nTargetID].Leader!=conn)
				{	Log("err only leader can kick members",pUser[conn].AccountName,pUser[conn].IP);
					return;
				}
			}

			RemoveParty(conn, target);
		}	break;
	case _MSG_SetParty:
		{	MSG_SetParty* m = (MSG_SetParty*)msg;

			if(pMob[conn].Leader!=0)		//	파티리더가 아닐경우
			{	m->byResult=REPLY_UNKNOWN; 
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));	break;
			}

			m->byResult=REPLY_ACK_OK; 
			pMob[conn].byRootingMode = m->byRootingMode;
			SendPartyMessage(conn, (MSG_STANDARD*)m);
		}	break;
	case _MSG_GMMode:
		{	MSG_GMMode* m = (MSG_GMMode*)msg;

			if(pMob[conn].MOB.byTrimuriti != eTNClan_GM) {CrackLog(conn," _MSG_GMMode"); CloseUser(conn); return;}
			m->szCharName[SZNAME_LENGTH-1]=0; m->szCharName[SZNAME_LENGTH-2]=0;
			int nID = GetMOBID(m->szCharName);
			m->nID = conn;	m->byResult=S_FALSE;
			if(nID==0)					//	현재의 존에 존재하지 않는 케릭터
			{	if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
				{	Log("err GMMode DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
				return;
			}	else
			if(nID<0 || nID>=MAX_USER)	//	발생할수 없는 에러
			{	Log("err_cri _MSG_GMMode command but invalid_user",m->szCharName,0);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			int nX=pMob[nID].TargetX; int nZ=pMob[nID].TargetY;
			if(nX<0 || nX>=MAX_GRIDX || nZ<0 || nZ>=MAX_GRIDX)
			{	Log("err_cri _MSG_GMMode command but invalid_position",m->szCharName,0);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			BYTE bySet = m->byGMMode >> 7;
			BYTE byFlag = 0;
			BYTE byPos = 1;
			BYTE byMode = pMob[nID].MOB.byGMStatus;

			for(int i=0; i<7; i++)
			{	byFlag = m->byGMMode << (7-i);
				byFlag >>= (7-i);
				if(byFlag) 
				{	BYTE byRest = byMode << (8-i);
					byRest >>= (8-i);
					byMode >>= (i+1);
					byMode <<= 1;
					byMode += bySet;
					byMode <<= i;
					byMode += byRest;
					break;
				}
			}

			pMob[nID].MOB.byGMStatus = byMode;

			//	GM에게 Mode설정을 알린다.
			m->byResult=S_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			//	유저와 주변에게 Mode설정됨을 알린다.
			MSG_GMMode_Notify sm; sm.wType=_MSG_GMMode_Notify;
			sm.wPDULength=sizeof(MSG_GMMode_Notify)-sizeof(HEADER);
			sm.nID=nID;	sm.byGMMode=byMode;
			GridMulticast(nX,nZ,(MSG_STANDARD*)&sm,-1);
		}	break;
	case _MSG_GMMovePosition:
		{	MSG_GMMovePosition* m = (MSG_GMMovePosition*)msg;

			if(pMob[conn].MOB.byTrimuriti != eTNClan_GM) {CrackLog(conn,"_MSG_GMMovePosition"); CloseUser(conn); return;}

			short snX=m->snX; short snZ=m->snZ;
			if  (snX<=0 || snX>=MAX_GRIDX || snZ<=0 || snZ>=MAX_GRIDY)
			{	Log("err _MSG_GMMovePosition - viewgrid",pMob[conn].MOB.szName,pUser[conn].IP);
				return;
			}

			MSG_Action nm; nm.wType = _MSG_Action;
			nm.wPDULength = sizeof(nm)-sizeof(HEADER);
			nm.TargetX=snX; nm.TargetY= snZ;
			nm.dwKeyID = conn; nm.PosX=0; nm.PosY=0;
			nm.Direction = 0; nm.Effect = 5;
			nm.Speed=0;

			if  (pUser[conn].Mode!=USER_PLAY) return;
			if  (0>=pMob[conn].MOB.nHP ) return;

			if	(pMobGrid[snZ][snX]!=0 && pMobGrid[snZ][snX] != conn)
			{	int x=snX;
				int z=snZ;
				int tret = GetEmptyMobGrid(conn,&x,&z);
				if	(tret==FALSE)
				{	Log("err too many people near start point => 40",pUser[conn].AccountName,pUser[conn].IP);
					SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]); return;
				}
				snX = x; snZ = z; nm.TargetX=snX; nm.TargetY= snZ;
			}

			pUser[conn].LastAction = m->dwClientTick;
			int lastx = snX;
			int lasty = snZ;
			pMob[conn].Direction	= 0;
			pMob[conn].State		= 1;
			//pMob[conn].TargetX		= snX;
			//pMob[conn].TargetY		= snZ;

			pUser[conn].nPreX = snX; pUser[conn].nPreY = snZ;
			pUser[conn].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
			GridMulticast(conn,snX,snZ,(MSG_STANDARD*)&nm);
		}	break;
	case _MSG_GMMoveToPlayer:
		{	MSG_GMMoveToPlayer* m = (MSG_GMMoveToPlayer*)msg;

			if(pMob[conn].MOB.byTrimuriti != eTNClan_GM) {CrackLog(conn,"_MSG_GMMoveToPlayer"); CloseUser(conn); return;}

			m->szCharName[SZNAME_LENGTH-1]=0; m->szCharName[SZNAME_LENGTH-2]=0;
			int nID = GetMOBID(m->szCharName);
			if(nID==0)					//	현재의 존에 존재하지 않는 케릭터
			{	m->nID=conn;
				if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
				{	Log("err GMMovetoPlayer DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
				return;
			}	else
			if(nID<0 || nID>=MAX_USER)	//	발생할수 없는 에러
			{	Log("err_cri _MSG_GMMoveToPlayer command but invalid_user",m->szCharName,0);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			//	이하 현재의 존에 존재하는 케릭터
			int nX=pMob[nID].TargetX; int nZ=pMob[nID].TargetY;
			if(nX<0 || nX>=MAX_GRIDX || nZ<0 || nZ>=MAX_GRIDX)
			{	Log("err_cri _MSG_GMMoveToPlayer command but invalid_position",m->szCharName,0);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			MSG_Action nm; nm.wType = _MSG_Action;
			nm.wPDULength = sizeof(nm)-sizeof(HEADER);
			nm.TargetX=nX; nm.TargetY= nZ;
			nm.dwKeyID = conn; nm.PosX=0; nm.PosY=0;
			nm.Direction = 0; nm.Effect = 5;
			nm.Speed=0;

			if  (pUser[conn].Mode!=USER_PLAY) return;
			if  (0>=pMob[conn].MOB.nHP ) return;

			if	(pMobGrid[nZ][nX]!=0 && pMobGrid[nZ][nX] != conn)
			{	int tret = GetEmptyMobGrid(conn,&nX,&nZ);
				if	(tret==FALSE)
				{	Log("err _MSG_GMMoveToPlayer too many people near start point",pUser[conn].AccountName,pUser[conn].IP);
					SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]);
					return;
				}
				nm.TargetX=nX; nm.TargetY= nZ;
			}

			pUser[conn].LastAction = m->dwClientTick;
			int lastx = nX;
			int lasty = nZ;
			pMob[conn].Direction	= 0;
			pMob[conn].State		= 1;
			//pMob[conn].TargetX		= nX;
			//pMob[conn].TargetY		= nZ;

			pUser[conn].nPreX = nX; pUser[conn].nPreY = nZ;
			pUser[conn].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
			GridMulticast(conn,nX,nZ,(MSG_STANDARD*)&nm);
		}	break;
	case  _MSG_GMKickPlayer:
		{	MSG_GMKickPlayer	*m = (MSG_GMKickPlayer*) msg;

			if(pMob[conn].MOB.byTrimuriti != eTNClan_GM) {CrackLog(conn,"_MSG_GMKickPlayer"); CloseUser(conn); return;}
			if(m->szCharName[0]==0) return;

			m->nID = conn;
			if(!DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_GMKickPlayer)))
			{	Log("err GMKickPlayer DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case  _MSG_REQMobByID:	// 클라이언트가 화면에 없는 NPC 또는 Object로부터의 Action(공격,이동)을 받았을때 해당 Object 생성을 요청
		{		
			MSG_REQMobByID * m = (MSG_REQMobByID * ) msg;
			int id = m->MobID;
			if  (id<=0||id>=MAX_MOB)			{ Log("err reqmobbyid MobId Out of range",pUser[conn].AccountName,pUser[conn].IP);	return;}
			if  (pMob[id].Mode==MOB_EMPTY)	{ SendRemoveMob(conn,id,0,0);			return;}
			if  (id<MAX_USER&&pUser[id].Mode!=USER_PLAY) {SendRemoveMob(conn,id,0,0);return;}
			if  (!GetInHalf(id,conn))			{ SendRemoveMob(conn,id,0,0);        return;}
			SendCreateMob(conn , id, TRUE);
			
		}	break;
	case _MSG_ReqMessenger:
		{	MSG_ReqMessenger * m = (MSG_ReqMessenger *) msg;
			
			m->Item.szCharName[SZNAME_LENGTH-1]=0;
			m->Item.szCharName[SZNAME_LENGTH-2]=0;
			char * pName = m->Item.szCharName;

			int nOther=GetMOBID(pName);
			if(nOther<1 || nOther>=MAX_USER) break;

			bool bFool = true;
			int nSlot = m->nSlot;
			if(nSlot<0 || nSlot>=MAX_MESSENGER) break;
			if(nOther<1 || nOther>=MAX_USER) break;
			for(int i=0; i<MAX_MESSENGER;i++)
			{	if(pUser[conn].Item[i].szCharName[0] == 0) bFool = false;
				if(!strcmp(pUser[conn].Item[i].szCharName, pName)) 
				{	SendClientMessage(conn, g_pMessageStringTable[_Address_Member_Already]);
					return;
				}
			}
			if(bFool)	//	나의 주소록이 풀일경우
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullMe]);
				return;
			}	else	//	내주소록이 풀이아니면 상대의 주소록 상태를 점검한다.
			{	bFool = true;
				for(int i=0; i<MAX_MESSENGER;i++)
				{	if(pUser[nOther].Item[i].szCharName[0] == 0) bFool = false;
				}
			}
			if(bFool)	//	상대의 주소록이 풀일경우
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullYou]);
				return;
			}

			strncpy(pUser[conn].InviteMessengerName, pMob[nOther].MOB.szName, SZNAME_LENGTH);
			pUser[conn].nInviteMessengerSlot = m->nSlot;
			m->Item.snTribe = pMob[conn].MOB.snTribe;
			m->nTargetID = nOther;
			strncpy(m->Item.szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);

			pUser[nOther].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _MSG_CNFMessenger:
		{	MSG_CNFMessenger * m = (MSG_CNFMessenger *) msg;

			m->CharName[SZNAME_LENGTH-1]=0;
			m->CharName[SZNAME_LENGTH-2]=0;
			char * pName = m->CharName;

			int nOther=GetMOBID(pName);
			if(nOther<1 || nOther>=MAX_USER) break;

			int nSlot = m->nSlot;
			if(nSlot<0 || nSlot>=MAX_MESSENGER) break;

			if(strcmp(pMob[conn].MOB.szName, pUser[nOther].InviteMessengerName )) break;

			bool bFool = true;
			for(int i=0; i<MAX_MESSENGER;i++)
			{	if(pUser[conn].Item[i].szCharName[0] == 0) bFool = false;
				if(!strcmp(pUser[conn].Item[i].szCharName, pName)) 
				{	SendClientMessage(conn, g_pMessageStringTable[_Address_Member_Already]);
					return;
				}
			}
			if(bFool)	//	나의 주소록이 풀일경우
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullMe]);
				return;
			}	else	//	내주소록이 풀이아니면 상대의 주소록 상태를 점검한다.
			{	bFool = true;
				for(int i=0; i<MAX_MESSENGER;i++)
				{	if(pUser[nOther].Item[i].szCharName[0] == 0) bFool = false;
				}
			}
			if(bFool)	//	상대의 주소록이 풀일경우
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullYou]);
				return;
			}

			int nOtherSlot = pUser[nOther].nInviteMessengerSlot;
			strcpy(pUser[conn].Item[nSlot].szCharName, pMob[nOther].MOB.szName);
			pUser[conn].Item[nSlot].snTribe		= pMob[nOther].MOB.snTribe;
			pUser[conn].Item[nSlot].Status		= 2;					//	on mode
			pUser[conn].Item[nSlot].Opponent	= nOtherSlot;
			MSG_UpdateMessengerItem sm; sm.wType=_MSG_UpdateMessengerItem;
			sm.nID=conn; sm.nSlot=nSlot; sm.Item=pUser[conn].Item[nSlot];
			MSGServerSocket.AddMessage((char*)&sm, sizeof(sm));

			strcpy(pUser[nOther].Item[nOtherSlot].szCharName, pMob[conn].MOB.szName);
			pUser[nOther].Item[nOtherSlot].snTribe	= pMob[conn].MOB.snTribe;
			pUser[nOther].Item[nOtherSlot].Status		= 2;	//	on mode
			pUser[nOther].Item[nOtherSlot].Opponent	= nSlot;
			MSG_UpdateMessengerItem nm; nm.wType=_MSG_UpdateMessengerItem;
			nm.nID=nOther; nm.nSlot=nOtherSlot; nm.Item=pUser[nOther].Item[nOtherSlot];
			MSGServerSocket.AddMessage((char*)&nm, sizeof(nm));
		}	break;
	case _MSG_RemoveMessenger:
		{	MSG_RemoveMessenger * m = (MSG_RemoveMessenger *) msg;
	
			int nSlot = m->nSlot;
			if(nSlot<0 || nSlot>=MAX_MESSENGER) break;
			if(pUser[conn].Item[nSlot].szCharName[0]==0) break;
			MSG_UpdateMessengerItem nm; nm.wType=_MSG_UpdateMessengerItem;
			nm.nID=conn; nm.nSlot=nSlot; memset(&(nm.Item), 0, sizeof(nm.Item));
			MSGServerSocket.AddMessage((char*)&nm, sizeof(nm));

		}	break;
	//case _MSG_UpdateMessengerItem:
	//{	MSG_UpdateMessengerItem * m = (MSG_UpdateMessengerItem *)msg;

	//	if(m->nSlot<0 || m->nSlot>=MAX_MESSENGER) break;										//	slot법위초과시 에러
	//	if(pUser[conn].Item[m->nSlot].szCharName[0]==0 && m->Item.szCharName[0]==0) break;		//	빈슬롯에 빈케릭터를 업데이트시 에러

	//	MSGServerSocket.SendOneMessage((char*)m, sizeof(*m));
	//}	break;
	case _Msg_Cash:
		{	
			if ( g_nItemCashType == eItemCashTypeGeneral )
			{
				Msg_Cash * m = (Msg_Cash *) msg;
				m->nID = conn;
				strncpy(m->AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				m->byType = 1;		//	1:SEARCH, 2:USE
				ItemServerSocket.SendCashMessage((char*)m, sizeof(*m));
			}
			else if ( g_nItemCashType == eItemCashTypeHanbit )
			{
				Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
				nm.wType=_Msg_Cash2; nm.ID=conn; 
				nm.C_Type = 2; 
				nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
				strcpy(nm.Order_Type,"I0");
				strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
				unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
				sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
				ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
			}
		}	break;
	case _Msg_Time:
		{	Msg_Time * m = (Msg_Time *) msg;

			if(ItemServerSocket.Sock==0) SendClientMessage(conn,g_pMessageStringTable[_Serverdown_Itemserver]);
			int nPrice = 0; bool bRet = true; short	snDay = 0; 
			int nItemIndex = m->nItemID+HT_PARAMTYPE_ITEM_START-1;
			int nIndex = nItemIndex - HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START;
			if(nIndex<0 || nIndex>=MAX_TIMEITEM) bRet=false;
			if(!CHTParamIDCheck::HT_bIsItemChargeFunction(nItemIndex) || !bRet) 
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m)); return;
			}

			bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nPrice);
			bRet &= g_ParamMgr.HT_bGetItemTimeLimit(nItemIndex, &snDay);
			if(pUser[conn].m_nCash<nPrice)
			{	m->byResult = REPLY_ITEM_BUY_GOLD_WANT;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m)); return;
			}
			if(!bRet)
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m)); return;
			}

			time_t now; time(&now);
			if(now>(int)pUser[conn].m_time[nIndex])
			{	pUser[conn].m_time[nIndex] = now+snDay*24*3600;			//	사용기간이 만료된 아이템은 현재일을 기준으로 날자를 추가한다
			}	else
			{	pUser[conn].m_time[nIndex] += snDay*24*3600;			//	사용기간이 만료되지 않은 아이템구매시 만기날자에 추가한다.
			}
			pUser[conn].m_nCash -= nPrice;

			m->byResult = REPLY_ACK_OK;
			m->dwTime = pUser[conn].m_time[nIndex];
			m->nCash = pUser[conn].m_nCash;
			if(nIndex==eTime_Inven)								//	개인인벤확장
			{	pMob[conn].byMaxInven = MAX_ONEINVEN*2;
			}	else
			if(nIndex==eTime_Store)								//	개인상점 확장
			{
			}	else
			if(nIndex==eTime_AMoneyRoot)
			{	pMob[conn].m_bAMoneyRoot = true;				//	루피아 자동줍기 설정
			}	else
			if(nIndex==eTime_Atman || nIndex==eTime_Anubaba)	//	기간제 아트만부적, 아누바바부적의 경우 
			{	pMob[conn].ProcessContinuousEffect();
			}

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));		//	유저에게 구입결과를 알려준다

			if ( g_nItemCashType == eItemCashTypeGeneral )
			{
				Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
				nm.wType=_Msg_Cash; nm.nID=conn; nm.byType=2;
				nm.byType=2; nm.nCash=nPrice;								//	1:SEARCH, 2:USE
				nm.snItemIndex = nItemIndex; nm.nIP = pUser[conn].IP;
				strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
			}
			else if ( g_nItemCashType == eItemCashTypeHanbit )
			{
				Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
				nm.wType=_Msg_Cash2; nm.ID=conn; 
				nm.C_Type = 3; 
				nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
				strcpy(nm.Order_Type,"I0");
				strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
				unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
				sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
				nm.Amount=-nPrice; sprintf(nm.Item_no, "%d", nItemIndex);
				ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
			}
		}	break; 
	case _Msg_NPCCommand:
		{	Msg_NPCCommand * m = (Msg_NPCCommand *) msg;
			
			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   m->byResult = REPLY_NPCCOMMAND_STATUS;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
				//	AddCrackError(conn,20,CRACK_USER_STATUS); 
				return;
			}
			
			bool bRet = true; int nItemIndex = 0;
			int nCost = 0; int nCash = 0; char file[256] = {0,};
			short snX,snY=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;

			bRet &= g_ParamMgr.HT_bGetNPCPosition( m->nNPCID, &snX, &snY );				//	NPC 위치정보습득

			FILE * fp = NULL; m->byFirst = false;

			switch(m->byType)
			{
			case eInitSkill:
			case eInitChar:
				{
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))		//	유료화일경우(타니)
					{	if(m->byType==eInitSkill) bRet &= g_ParamMgr.HT_bGetItemCash( eItem_InitSkill, &nCash  );
						else	bRet &= g_ParamMgr.HT_bGetItemCash( eItem_InitChar, &nCash  );
					}
					else												//	무료화일경우(루피아)
					{	if(m->byType==eInitSkill)		sprintf(file,".\\EVENT\\INITSKILL\\%s.dat",pMob[conn].MOB.szName);
						if(m->byType==eInitChar)		sprintf(file,".\\EVENT\\INITCHAR\\%s.dat",pMob[conn].MOB.szName);
						if(g_eCountryID == eCountryKorea)				//	한국에서는 바이드야 대상만 가능하다
						{
							if(pMob[conn].MOB.byClass1!=CLASS_LEVEL2 || pMob[conn].MOB.byClass2!=CLASS_NIRVANA2)
							{	m->byResult = REPLY_NPCCOMMAND_NOT_TARGET;
								pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
							}
							nCost = 5000000;
						}

						fp = fopen(file,"rb");	//	파일처리
						if	(fp==NULL)			//	최초의 초기화
						{	m->byFirst = true;
							if(m->byCommand==eRun)
							{	fp = fopen(file,"wb");
								m->byFirst = true;
								if	(fp==NULL)	//	파일생성실패
								{	m->byResult = REPLY_UNKNOWN;
									pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
								}	else
								{	fclose(fp);	
								}
							}
						}	else				//	한번이상의 초기화
						{	fclose(fp);
							if(g_eCountryID == eCountryKorea)			//	한국에서는 1회만 사용가능하다
							{	m->byResult = REPLY_NPCCOMMAND_ALREADY;
								pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
							}
						}
						if(!m->byFirst) 
						{	float fLevel = (float)pMob[conn].MOB.byLevel;
							nCost = (int(pow(fLevel, 2.95)*10 + 990)/100)*100;
						}
					}
				}	break;
			case eInitSkillChar:
				{	bRet &= g_ParamMgr.HT_bGetItemCash( eItem_InitSkillChar, &nCash  );
				}	break;
			case eInit2ndClass:
				{	if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))		//	유료화일경우(타니)
					{	bRet &= g_ParamMgr.HT_bGetItemCash( eItem_Init2ndClass, &nCash  );
					}	else
					{
					}
				}	break;
			case eEvent:
				{
#ifdef __IWANTIT__
					m->nRupia = g_GameEvent.m_IWantIt.GetUserItemCount(pMob[conn].MOB.szName);
#endif	//	#ifdef __IWANTIT__
				}	break;
			default:
				{	
					m->byResult = REPLY_UNKNOWN;										//	정의되어 있지않은 명령
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;	
				}	break;
			}

			if(!bRet || (!CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID) && 
				(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY)))
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;			//	거리오류 파라메터 오류의 경우
			}

			if(m->byCommand==eSearch)		//	조회의 경우(스킬, 능력치 초기화시 공짜인지를 알기위해 조회하는 것임)
			{	m->byResult = REPLY_ACK_OK;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}
			else if(m->byCommand==eRun)
			{	
				if(!m->byFirst && g_eCountryID==eCountryChina)	//	중국에서 루피아를 이용한 초기화 요청시(최초가 아닐경우 기능블록)
				{	m->byResult = REPLY_NPCCOMMAND_STATUS;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
				}

				if(pMob[conn].MOB.nRupiah<nCost || pUser[conn].m_nCash<nCash)		//	돈이 부족할 경우
				{	m->byResult = REPLY_NPCCOMMAND_LACK;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
				}

				if(m->byType==eInitSkill)
				{	pMob[conn].ResetSkill();
					sprintf(temp, "rst Skill- %s(%d, %d)",pMob[conn].MOB.szName,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
					{	pUser[conn].m_nCash -= nCash;
						m->nRupia = pUser[conn].m_nCash;
					}	else
					{	pMob[conn].DecGold(nCost);
						m->nRupia = pMob[conn].MOB.nRupiah;
					}
					nItemIndex = eItem_InitSkill;
				}	else 
				if(m->byType==eInitChar)
				{	pMob[conn].ResetStat();
					sprintf(temp, "rst Stat - %s(%d, %d)",pMob[conn].MOB.szName,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
					{	pUser[conn].m_nCash -= nCash;
						m->nRupia = pUser[conn].m_nCash;
					}	else
					{	pMob[conn].DecGold(nCost);
						m->nRupia = pMob[conn].MOB.nRupiah;
					}
					nItemIndex = eItem_InitChar;
				}	else 
				if(m->byType==eInitSkillChar)
				{	pMob[conn].ResetSkill();
					pMob[conn].ResetStat();
					sprintf(temp, "rst Skill, Stat - %s(%d, %d)",pMob[conn].MOB.szName,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
					{	pUser[conn].m_nCash -= nCash;
						m->nRupia = pUser[conn].m_nCash;
					}
					else
					{	pMob[conn].DecGold(nCost);
						m->nRupia = pMob[conn].MOB.nRupiah;
					}
					nItemIndex = eItem_InitSkillChar;
				}	else 
				if(m->byType==eInit2ndClass)
				{	pMob[conn].ResetClass();
					pMob[conn].ResetSkill();
					pMob[conn].ResetStat();
					sprintf(temp, "rst Class, Skill, Stat - %s(%d, %d)",pMob[conn].MOB.szName,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
					{	pUser[conn].m_nCash -= nCash;
						m->nRupia = pUser[conn].m_nCash;
					}
					else
					{	pMob[conn].DecGold(nCost);
						m->nRupia = pMob[conn].MOB.nRupiah;
					}
					nItemIndex = eItem_Init2ndClass;
				}
			}	
			else
			{
				m->byResult = REPLY_UNKNOWN;										//	정의되어 있지않은 명령
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;	
			}

			if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
			{	
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash; nm.nID=conn; nm.byType=2;
					nm.byType=2; nm.nCash=nCash;								//	1:SEARCH, 2:USE
					nm.snItemIndex = nItemIndex; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server에 cash구입을 알린다.
					nm.wType=_Msg_Cash2; nm.ID=conn; 
					nm.C_Type = 3; 
					nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
					strcpy(nm.Order_Type,"I0");
					strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
					unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
					sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
					nm.Amount=-nCash; sprintf(nm.Item_no, "%d", nItemIndex);
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
			}

			m->byResult = REPLY_ACK_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			pMob[conn].ProcessContinuousEffect();

		}	break;
	case _Msg_Challenger:
		{	Msg_Challenger* m = (Msg_Challenger*)msg;

			int nTarget = m->nID; BYTE byMode = m->byMode;
			BYTE byReason = m->byReason;

			if(nTarget<=0 || nTarget>MAX_USER) break;										//	Invalid UserID
			if(strncmp(pMob[nTarget].MOB.szName, m->szCharName, SZNAME_LENGTH)) break;		//	Invalid UserName
			if(byMode<0 || byMode>eChallenge_Combat) break;									//	Invalid CombatMode
			if(g_iZoneID==SERVER_KRUMA_HIGH || g_iZoneID==SERVER_KRUMA_LOW || g_iZoneID==SERVER_CHATURANGKA
				 || g_iZoneID==SERVER_STRONGHOLD || g_iZoneID==SERVER_KATANA3) break;		//	크루마, 아나카크루마, 차투, 요새전, 공성전에서 사용불가

			//char pData[128] = {0,};
			//sprintf(pData, "Sender:%s _Msg_Challenger Mode:%d, Reason:%d to charllenger:%s", 
			//	pMob[conn].MOB.szName, m->byMode, byReason, pMob[nTarget].MOB.szName);
			//TimeWriteLog(pData, "Challenger_log.txt");

			if(byMode==eChallenge_Request)			//	결투요청시
			{
				if(pMob[conn].MOB.nRupiah<g_dwChallengeMoney) 
				{
					SendClientMessage(conn,g_pMessageStringTable[_HaveNotEnoughGold]);
					break;								//	루피아가 부족할 경우
				}

				//	나에게 결투 상대가 있을 경우 기존결투모드 해제
				if(pUser[conn].m_nChallengeMode!=eChallenge_WAIT)	
				{	//	if(nTarget==pUser[conn].m_nChallenger) return;
					RemoveChallenge(conn, eChallenge_Denay);
					return;
				}
				//	상대가 결투중일 경우 방해할수 없다
				if(pUser[nTarget].m_nChallengeMode==eChallenge_Combat)
				{	m->byMode = eChallenge_Response; m->byReason = eChallenge_System;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
					return;
				}
				//	상대에게 결투 상대가 있을 경우 기존결투모드 해제
				if(pUser[nTarget].m_nChallengeMode!=eChallenge_WAIT)	{ RemoveChallenge(nTarget, eChallenge_System); return; }

				//	나의 결투모드를 세팅한다.
				pUser[conn].m_nChallengeMode = eChallenge_Request;
				pUser[conn].m_nChallenger = nTarget;
				strncpy(pUser[conn].m_pChallenger, pMob[nTarget].MOB.szName, SZNAME_LENGTH);

				//	상대의 결투모드를 세팅한다.
				pUser[nTarget].m_nChallengeMode = eChallenge_Response;
				pUser[nTarget].m_nChallenger = conn;
				strncpy(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH);

				//	상대에게 결투신청을 요청한다.
				m->nID = conn;
				m->byMode = eChallenge_Request;
				strncpy(m->szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				pUser[nTarget].cSock.SendOneMessage((char*)m, sizeof(*m));

				pMob[conn].MOB.nRupiah -= g_dwChallengeMoney;

				MSG_MobStatus nm; nm.wType=_MSG_MobStatus;
				nm.nID=conn; nm.byTradeMode=pUser[conn].byTradeMode;
				nm.nRupia=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.AddMessage((char*)&nm, sizeof(nm));
			}
			else if(byMode==eChallenge_Response)		//	결투요청에대한 응답
			{
				//	상대와의 결투모드가 유효한지 체크한다.
				if(strncmp(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH)) break;	//	상대가 결투상대를 바꿧을 경우
				if(strncmp(pUser[conn].m_pChallenger, m->szCharName, SZNAME_LENGTH)) break;				//	나의 결투상대가 아닌데 승락한 경우
				if(pUser[nTarget].m_nChallengeMode!=eChallenge_Request || pUser[conn].m_nChallengeMode!=eChallenge_Response)
				{	if(pUser[conn].m_nChallengeMode==eChallenge_Combat && pUser[nTarget].m_nChallengeMode==eChallenge_Combat && byReason==eChallenge_End)
						RemoveChallenge(conn, byReason);
					return;
				}

				if(byReason==eChallenge_Accept) StartChallenge(conn);
				else 
				{
					if(pUser[conn].m_nChallengeMode==eChallenge_WAIT) return;

					char pData[128] = {0,};
					sprintf(pData, "SERVER SEND TO:%s _Msg_Challenger CANCELED WITH charllenger:%s mode:%d reason:%d", 
						pMob[conn].MOB.szName, pMob[nTarget].MOB.szName, eChallenge_Response, byReason);
					TimeWriteLog(pData, "Challenger_log.txt");

					//	나의 결투모드를 세팅한다.
					pUser[conn].m_nChallengeMode = eChallenge_WAIT;
					pUser[conn].m_nChallenger = 0;
					ZeroMemory(pUser[conn].m_pChallenger, SZNAME_LENGTH);

					Msg_Challenger sm; sm.wType = _Msg_Challenger;
					sm.byMode = eChallenge_Response;
					sm.byReason = byReason;
					sm.nID = nTarget;
					strncpy(sm.szCharName, pMob[nTarget].MOB.szName, SZNAME_LENGTH);
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

					sprintf(pData, "SERVER SEND TO:%s _Msg_Challenger CANCELED WITH charllenger:%s mode:%d reason:%d", 
						pMob[nTarget].MOB.szName, pMob[conn].MOB.szName, eChallenge_Response, byReason);
					TimeWriteLog(pData, "Challenger_log.txt");

					//	상대의 결투모드를 세팅한다.
					pUser[nTarget].m_nChallengeMode = eChallenge_WAIT;
					pUser[nTarget].m_nChallenger = 0;
					ZeroMemory(pUser[nTarget].m_pChallenger, SZNAME_LENGTH);

					sm.nID = conn;
					strncpy(sm.szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
					pUser[nTarget].cSock.SendOneMessage((char*)&sm, sizeof(sm));
				}
			}
			else									//	결투거부시
			{
				//	결투모드를 해제한다.
				RemoveChallenge(conn, eChallenge_System);
			}
		}	break;
	case _Msg_TimeMode:
		{	Msg_TimeMode* m = (Msg_TimeMode*)msg;

			pUser[conn].m_snTimeMode = m->snMode;

			pMob[conn].ProcessContinuousEffect(true);
		}	break;
	case _Msg_Escape: // /탈출
		{	
			//--------------------------------------------------------------------------
			// 탈출 보완
			// 1. 굉장히 먼거리를 한번에 날라왔다. 파티소환 같은 것을 통해서 --;
			//   - 문에 걸려 이동할 수 없다.
			//   - LastX, LastY로 저장된다.
			// 2. 현재 좌표와 바로 이전 좌표가 동일하므로 탈출을 할 수 없다.
			//   - 좌표가 동일하면, 바로 주위 좌표를 검색하게끔한다.?

			// 2. '/탈출'을 해서 옆으로 이동을 했다.
			//   - 문이 배치된 영역으로 서버에서는 빈 cell이지만, client에서는 충돌 처리를 하는 곳이다.
			//   - 따라서 이곳도 client 충돌 처리에 의해서 이동불가 상태이다.
			// 3. '/탈출'을 해서 이동 가능 영역으로 시도를 한다. 
			//   - 하지만 이동을 하는 LastX, LastY는 이동 불가 영역이므로 여전히 이동 불가 상태이다.
			// 4. '/탈출'을 다시 하지만 계속 제자리로 돌아오게 된다.
			//--------------------------------------------------------------------------

			S_REQUEST* m = (S_REQUEST*)msg;
			
			if  (pUser[conn].Mode!=USER_PLAY) return;
			if  (0>=pMob[conn].MOB.nHP ) return;
			if( eTNVSAfn_DontMove & pMob[conn].m_iAffections) return; //	스턴, 슬립, 홀드 상태에서는 사용할 수 없다.

			HS2D_COORD kDest, kCur;
			kCur.x = pMob[conn].TargetX;
			kCur.y = pMob[conn].TargetY;
			kDest.x = pMob[conn].LastX;
			kDest.y = pMob[conn].LastY;

			bool bTeleportRandomLocation = false;			

			int iDist = CalDistance( kCur, kDest, 0, 0 );
			if( iDist < pMob[conn].m_iMoveSpeed )
			{
				int iRes = Teleport( conn, kDest.x, kDest.y );
				if( iRes ) bTeleportRandomLocation = true;
			}
			else bTeleportRandomLocation = true;
			if( kCur.iBuf == kDest.iBuf ) bTeleportRandomLocation = true;

			if( bTeleportRandomLocation )
			{
				int nX = pMob[conn].TargetX; int nZ = pMob[conn].TargetY;
				GetMovableMobGrid(conn, &nX, &nZ);

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm)-sizeof(HEADER);
				nm.TargetX=nX; nm.TargetY= nZ;
				nm.dwKeyID = conn; nm.PosX=0; nm.PosY=0;
				nm.Direction = 0; nm.Effect = 5;
				nm.Speed=0;

				pUser[conn].LastAction = m->dwClientTick;
				int lastx = nX;
				int lasty = nZ;
				pMob[conn].Direction	= 0;
				pMob[conn].State		= 1;
				//pMob[conn].TargetX		= snX;
				//pMob[conn].TargetY		= snZ;

				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
				GridMulticast(conn,nX,nZ,(MSG_STANDARD*)&nm);
			}
		}	
		break;
	case _Msg_GameEvent:
		{	Msg_GameEvent* m = (Msg_GameEvent*)msg;
	
			int iEvent = m->nID;
			BYTE byRet = SetGameEvent(conn, iEvent & pUser[conn].m_dwEvent, &m->iData[0]);
			m->byResult = byRet;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		///////////////////////////////////////////////////////////////////////////////////////////////
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//                   DB  메시지 처리기

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void ProcessDBMessage( char* msg )
{
	HEADER * std = (HEADER *) msg;
	
	
	switch (std->wType)
	{ 
	case _Msg_GuildItemUpdate:
		{	Msg_GuildItemUpdate * m = (Msg_GuildItemUpdate*) msg;

			int iIndex = IsGuildMemberIn(m->nGuildID);
			if(iIndex>0)
			{
				SendGuildMessage(iIndex, (MSG_STANDARD*)m);
			}
		}	break;
	case _Msg_GuildCargoTime:
		{	Msg_GuildCargoTime * m = (Msg_GuildCargoTime*) msg;

			int iIndex = IsGuildMemberIn(m->nGuildID);
			if(iIndex>0)
			{
				pGuild[iIndex].SetCargoTime(m->dwTime[0], m->dwTime[1], m->dwTime[2]); 
				SendGuildMessage(iIndex, (MSG_STANDARD*)m);
			}
		}	break;
	case _Msg_GuildCargoUsingLevel:
		{	Msg_GuildCargoUsingLevel * m = (Msg_GuildCargoUsingLevel*)msg;

			int iIndex = IsGuildMemberIn(m->nGuildID);
			if(iIndex>0)
			{
				pGuild[iIndex].SetCargoLevel(m->byCargoLevel[0], m->byCargoLevel[1], m->byCargoLevel[2]);
				SendGuildMessage(iIndex, (MSG_STANDARD*)m);
			}
		}	break;
		//	GM 관련
	case _MSG_Warp:
		{	MSG_Warp * m = (MSG_Warp*) msg;

			int nID = m->nID;
			int nUser = GetMOBID(m->szName);
			if(nUser>0 && nUser<MAX_USER)									//	호출을 요청을 받는 경우
			{
				pMob[nUser].m_kWaitAction.iAction = eWaitAct_ZonePortal;
				pUser[nUser].cSock.SendOneMessage((char*)m, sizeof(*m));
			} else															//	호출 요청에 대한 응답일 경우
			{	if(pMob[nID].m_byClan!=eTNClan_GM) return;
				if(m->byType == CONNECT_TYPE_GMRECALL)
				{	S_SCP_RESP_WHISPER_CHAT kMsg; 
					kMsg.wType = SCP_RESP_WHISPER_CHAT;	
					kMsg.byResult = REPLY_ACK_OK;
					strncpy( kMsg.szName, "System", SZNAME_LENGTH );
					kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	

					if(m->byResult == S_OK)
						sprintf( kMsg.szMsg, "%s> Requested to Recall by GM", m->szName );
					else
						sprintf( kMsg.szMsg, "%s> Recall failed - Not connected", m->szName);
						
					pUser[nID].cSock.SendOneMessage((char*)&kMsg, sizeof(kMsg));
				}	else
				{
				}
			}
		}	break;
		 //Accoung Login 인증 관련
		case SSP_RESP_MOVE_ZONE_SERVER:  // NewAccount 는 따로 CNF 없이 AccountLogin을 사용.
		{	
			S_SSP_RESP_MOVE_ZONE_SERVER * m = (S_SSP_RESP_MOVE_ZONE_SERVER *) msg; 

			int conn = m->nID;
			if(conn<=0 || conn>=MAX_USER)
			{	SendClientResult(conn, CSP_REQ_MOVE_ZONE_SERVER, 16);//"다시 접속을 시도해 주세요"
				sprintf(temp,"clo err resp_move_zone account not match, conn:%d id:%s",conn,m->AccountName);
				Log(temp,"-system",0);
				pUser[conn].cSock.SendMessage();
				CloseUser(conn);
				return;
			}
		    if	(strcmp(m->AccountName,pUser[conn].AccountName))
			{	SendClientResult(conn, CSP_REQ_MOVE_ZONE_SERVER, 16);//"다시 접속을 시도해 주세요"
				sprintf(temp,"clo err resp_move_zone account not match, puser:%s packet:%s",pUser[conn].AccountName,m->AccountName);
				Log(temp,"-system",0);
				pUser[conn].cSock.SendMessage();
				CloseUser(conn);
				return;
			}
            
			//sprintf(temp,"dbg account:%s receive move zone from db",pUser[conn].AccountName);
			//Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//	User 초기화
			pUser[conn].IsBillConnect = 0;
			pUser[conn].Admin		  = 0;
			pUser[conn].ReqBillSec	  = 0;
			pUser[conn].Child		  = 0;
			pUser[conn].nInviteMessengerSlot = 0;
			pUser[conn].m_LastTime	  = 0;	//	cpu accelerator clear time

		    m->wType = SCP_RESP_MOVE_ZONE_SERVER;
			pUser[conn].Mode = USER_SELCHAR;

			S_SCP_RESP_MOVE_ZONE_SERVER moveZone;
			moveZone.wType = SCP_RESP_MOVE_ZONE_SERVER;
			moveZone.wPDULength = sizeof(S_SCP_RESP_MOVE_ZONE_SERVER)-sizeof(HEADER);
			moveZone.nResult = m->nResult;
  			pUser[conn].cSock.SendOneMessage((char*)&moveZone,sizeof(S_SCP_RESP_MOVE_ZONE_SERVER));
			pUser[conn].Billing = 0; // 빌링모드 초기화 
			/*pUser[conn].SelChar = m->SelChar;
            if	(BILLING>0 && IsFree(&(m->SelChar))!=0)
			{	
				if	(CHARSELBILL==0)	SendBilling(conn,m->AccountName,8,1);  // 8은 캐랙터 선택에서 빌링 체크를 안하기위홈
				else					SendBilling(conn,m->AccountName,1,1);  // 1은 빌링 시장

				pUser[conn].ReqBillSec = SecCounter;
			}
			*/
			pUser[conn].User_Status[0]=0;
			//Cargo를 저장하라!!
			unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
			char tmp[256]; sprintf(tmp,"sta %d.%d.%d.%d %X%X%X%X %d",cIP[0],cIP[1],cIP[2],cIP[3],pUser[conn].Mac[0],pUser[conn].Mac[1],pUser[conn].Mac[2],pUser[conn].Mac[3],conn);
			Log(tmp,pUser[conn].AccountName,pUser[conn].IP);
			if	(m->nResult) 
			{	CloseUser(conn); return;
			}

			//	move-zone success(Billing start)
			char pSession[32] = {0,};
			_itoa(conn, pSession, 10); strncpy(pUser[conn].Session ,pSession, sizeof(pSession));
			SendBilling(conn,m->AccountName,1,1);

			pUser[conn].ssn1 = m->ssn1;
			pUser[conn].ssn2 = m->ssn2;
		}	break;
		case SSP_RESP_CHAR_LIST:
			{	S_SSP_RESP_CHAR_LIST * m = (S_SSP_RESP_CHAR_LIST *) msg;
				int conn = m->nID;
				int s=sizeof(m->sData);
				memcpy(pUser[conn].sData,m->sData,s);
			} break;
		case SSP_RESP_CHAR_SELECT:
			{
				S_SSP_RESP_CHAR_SELECT *m = (S_SSP_RESP_CHAR_SELECT *) msg;
				S_SCP_RESP_CHAR_SELECT sData;
				sData.wType = SCP_RESP_CHAR_SELECT;
				sData.wPDULength = sizeof(S_SSP_RESP_CHAR_SELECT)-sizeof(HEADER);
				sData.byResult = m->byResult;
				sData.byZone = m->byZoneNo;
			} break;
		//	Character login, create 관련
        case SSP_RESP_CHAR_CREATE:
		{   S_SSP_RESP_CHAR_CREATE * m = (S_SSP_RESP_CHAR_CREATE *) msg;
			int conn = m->nID;
			S_SCP_RESP_CHAR_CREATE sData;
			sData.wType = SCP_RESP_CHAR_CREATE;
			sData.wPDULength = sizeof(S_SSP_RESP_CHAR_CREATE)-sizeof(HEADER);
			sData.byResult = m->byResult;

			pUser[conn].cSock.SendOneMessage((char*)&sData,sizeof(S_SCP_RESP_CHAR_CREATE));
			pUser[conn].Mode = USER_SELCHAR;  // 다시 캐랙터 고르기로 돌아온다.

			// 성공시 해당Slot의 Messenger를 초기화한다.
			if(m->byResult != REPLY_ACK_OK) break;
#ifdef __EVENT_LOG_GENERATION_
			EventLog("Create",pUser[conn].AccountName,m->szCharName,pUser[conn].IP);
#endif
			MSG_MessengerRemovelist sm; sm.wType=_MSG_MessengerRemovelist; 
			sm.nID=conn; sm.bySlot=m->bySlot; 
			strncpy(sm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
			MSGServerSocket.AddMessage((char*)&sm, sizeof(sm));
	  	 }    break;
/////////////////////////////////////////////////////////////////////////////////////////////
         case SSP_RESP_CHAR_REMOVE:
		 {    S_SSP_RESP_CHAR_REMOVE * m = (S_SSP_RESP_CHAR_REMOVE *) msg;
			  int conn = m->nID;
			  S_SCP_RESP_CHAR_REMOVE sData;
			  sData.wType = SCP_RESP_CHAR_REMOVE;
			  sData.wPDULength = sizeof(S_SCP_RESP_CHAR_REMOVE)-sizeof(HEADER);
			  sData.byResult = m->byResult;

			  //m->ID    = ESCENE_SELCHAR;
			  pUser[conn].cSock.SendOneMessage((char*)&sData,sizeof(S_SCP_RESP_CHAR_REMOVE));
			  pUser[conn].Mode = USER_SELCHAR;  // 다시 캐랙터 고르기로 돌아온다.
	  	 }    break;
		case SSP_RESP_CHAR_INIT:
			{	S_SSP_RESP_CHAR_INIT * m = (S_SSP_RESP_CHAR_INIT *) msg;
			int conn = m->nID;
			if (conn<=0 || conn>=MAX_USER) {CrackLog(conn," CNFCharLogin");CloseUser(conn); return;}

			if(pUser[conn].Mode!=USER_CHARWAIT) 
			{	sprintf(temp, "clo err initchar2 - not USER_SELCHAR mode:%d", pUser[conn].Mode);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout;
				CloseUser(conn);
				return;
			}

			BYTE byConnectType=m->byConnType;
			memcpy(pUser[conn].Cargo,m->sNpcInven,sizeof(STRUCT_ITEM)*MAX_CARGO);
			pMob[conn].MOB			=	m->sChar;
			pMob[conn].MOB.byZone	=	ServerIndex+1;
			pMob[conn].byRootingMode = 0;
			pMob[conn].m_snSaveNPC = 0;
			pMob[conn].m_snResurrect = RESURRECT_TYPE_PRESENT;
			pMob[conn].m_bAMoneyRoot = false;
			pUser[conn].Slot = m->bySlot;
			//srrncpy(pMob[conn].m_szCharname, m->sChar, SZNAME_LENGHT);
			//strupr(pMob[conn].m_szCharname);
			pUser[conn].CharLoginTime = 0;

			ZeroMemory(pUser[conn].m_pChallenger, SZNAME_LENGTH);

			memcpy(pUser[conn].m_time, m->dwTimeStamp, sizeof(pUser[conn].m_time));
			//pUser[conn].bBillConfirm = 0;

			//sprintf(temp,"dbg char:%s receive init data from db x:%d y:%d savex:%d savez:%d",pMob[conn].MOB.szName,pMob[conn].MOB.snX,pMob[conn].MOB.snZ,pMob[conn].MOB.snSaveX,pMob[conn].MOB.snSaveZ);
			//Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//	기간제 아이템을 설정한다.
			time_t now; time(&now);
			DWORD dwTime=now;
			if(pUser[conn].m_time[eTime_Inven] > dwTime) pMob[conn].byMaxInven = MAX_ONEINVEN*2;	//	최대인벤크기 설정
			else pMob[conn].byMaxInven = MAX_ONEINVEN;
			if(pUser[conn].m_time[eTime_AMoneyRoot] > dwTime) pMob[conn].m_bAMoneyRoot = true;		//	루피아 자동줍기 설정

			//	초기 View Equip set
			pMob[conn].SetViewEquip(eVisualEquipHelmet,		&pMob[conn].MOB.Equip[eTNEqu_Helmet]);
			pMob[conn].SetViewEquip(eVisualEquipArmor,		&pMob[conn].MOB.Equip[eTNEqu_Armor]);
			pMob[conn].SetViewEquip(eVisualEquipPants,		&pMob[conn].MOB.Equip[eTNEqu_Pants]);
			pMob[conn].SetViewEquip(eVisualEquipShield,		&pMob[conn].MOB.Equip[eTNEqu_Shield]);
			pMob[conn].SetViewEquip(eVisualEquipOneWeapon,	&pMob[conn].MOB.Equip[eTNEqu_OneHandWeapon]);
			pMob[conn].SetViewEquip(eVisualEquipBoots,		&pMob[conn].MOB.Equip[eTNEqu_Boots]);
			pMob[conn].SetViewEquip(eVisualEquipGloves,		&pMob[conn].MOB.Equip[eTNEqu_Gloves]);

			pMob[conn].Mode   = MOB_USER;
			
			bool bCreate=false; bool bCenter=false; bool bDie=false;
			DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;

			if(byConnectType==CONNECT_TYPE_DIE && m->sChar.bySaveZone==0) 
			{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
			}

			if(pMob[conn].MOB.snX==0 || pMob[conn].MOB.snZ==0)		//	초기좌표점검
			{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
			}

			if(m->wPortalID!=0)										//	포탈데이터 점검
			{	bool bRet = true;
				bRet &= g_ParamMgr.HT_bGetPortalInfo(m->wPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ);
				if(!bRet && byConnectType == CONNECT_TYPE_PORTAL)
				{	sprintf(temp,"clo err CSP_REQ_MOVE_PORTAL find portal data error portal:%d char:%s",m->wPortalID, pMob[conn].MOB.szName);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
					CloseUser(conn); return;
				}	else
				if(bRet && byConnectType == CONNECT_TYPE_PORTAL)
				{
				}	else
				{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
				}
			}

			int nID=0;												//	워프점검
			if(m->szTargetName[0]!=0)
			{	m->szTargetName[SZNAME_LENGTH-1]=0; m->szTargetName[SZNAME_LENGTH-2]=0; 
				nID = GetMOBID(m->szTargetName);
				if(nID<=0 || nID>MAX_USER) 
				{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
				}
			}

			int tx = 0; int ty = 0; 
			if(byConnectType == CONNECT_TYPE_FIRST || bCenter)
			{	int x=0; int y=0;
				if	(m->sChar.snX<0 || m->sChar.snX>MAX_GRIDX || m->sChar.snZ<0 || m->sChar.snZ>MAX_GRIDY)
				{	BOOL bRet = GetTrimurityArea(conn, x, y);
					if(!bRet) {CloseUser(conn); return;}
					if(pMob[conn].MOB.nHP>0 && !bCenter) bCreate = true;				//	최초 생성된 케릭터

				}	
				else
				{	
					x=m->sChar.snX; y=m->sChar.snZ;
					//if( SERVER_KRUMA_HIGH == (ServerIndex+1) )  // 크루마
					if( (eZone_Cruma == g_iZoneID) || (eZone_Cruma2 == g_iZoneID) )					
					{	
						byte byTrimuriti = pMob[conn].MOB.byTrimuriti;

						if(x<TrimurityArea.pArea[byTrimuriti][0].snStartX || x>TrimurityArea.pArea[byTrimuriti][0].snEndX ||
							y<TrimurityArea.pArea[byTrimuriti][0].snStartZ || y>TrimurityArea.pArea[byTrimuriti][0].snEndZ)
						{	
							GetTrimurityArea(conn, x, y);

							if(pMob[conn].MOB.bySaveZone == SERVER_KRUMA_HIGH || pMob[conn].MOB.bySaveZone == SERVER_KRUMA_LOW)
							{	
								pMob[conn].MOB.snSaveX=x; pMob[conn].MOB.snSaveZ=y;
							}
						}
					}
				}
				tx = x; ty = y;
			}	else
			if(byConnectType == CONNECT_TYPE_PORTAL)
			{	
				int x = 0; int y = 0;
				if(snStartX<=0 || snEndX>=MAX_GRIDX || snStartZ<=0 || snEndZ>=MAX_GRIDY)
				{
					x = pMob[conn].MOB.snX; y = pMob[conn].MOB.snZ;
				}
				else
				{
					x = GetRandom(snStartX, snEndX);
					y = GetRandom(snStartZ, snEndZ);
				}
				tx = x; ty = y;
			}	else
			if(byConnectType == CONNECT_TYPE_WARP)
			{	tx = pMob[nID].TargetX;
				ty = pMob[nID].TargetY;
			}	else
			if(byConnectType == CONNECT_TYPE_DIE)
			{	tx = m->sChar.snSaveX;	ty = m->sChar.snSaveZ;

				if( 10 == pMob[conn].MOB.bySaveZone ) //|| 11 == pMob[conn].MOB.bySaveZone ) // 크루마, 차투랑가				
				{
					GetTrimurityArea(conn, tx, ty);
					pMob[conn].MOB.snSaveX = tx;
					pMob[conn].MOB.snSaveZ = ty;
				}
				
				bDie = true;
			}	else
			if(byConnectType == CONNECT_TYPE_PUSTICA)
			{	short snX,snY=0; byte byZone=0;
				bool bRet = g_ParamMgr.HT_bGetNPCZone( m->wPortalID, &byZone );
				bRet &= g_ParamMgr.HT_bGetNPCPosition( m->wPortalID, &snX, &snY );
				if(!bRet) 
				{	sprintf(temp,"clo char_init getnpczone char:%s", pMob[conn].MOB.szName);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
					CloseUser(conn); return; 
				}
				if(byZone != (ServerIndex+1)) 
				{ 	sprintf(temp,"clo char_init not match zone char:%s", pMob[conn].MOB.szName);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
					CloseUser(conn); return; 
				}

				tx = GetRandom(snX-5, snEndX+5);
				ty = GetRandom(snY-5, snEndZ+5);

			}	else
			if(byConnectType == CONNECT_TYPE_GMRECALL)
			{	int nGM = 0;
				for(int i=0; i<MAX_USER; i++)
				{	if(pUser[i].Mode != USER_PLAY) continue;
					if(pMob[0].MOB.byTrimuriti == eTNClan_GM) break;
				}
				if(i==MAX_USER)		//	GM 호출로 이동했으나 GM이 없을 경우(젠지역에서 태어나게 한다)
					GetTrimurityArea(conn, tx, ty);
				else
				{	nGM = i;
					tx = pMob[nGM].TargetX; ty = pMob[nGM].TargetY;
				}
			}	else
			{	sprintf(temp,"clo char_init not match connecttype char:%s", pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
				CloseUser(conn);
				return;
			}

			//#ifdef __TN_LOCAL_SERVER_SWITCH__
			//if( eZone_Castle == g_iZoneID )
			//{
			//	tx = 360;
			//	ty = 370;
			//}
			//#endif

			int iCount = 0;
			int tret = GetEmptyMobGrid(conn,&tx,&ty);
			if	(tret==FALSE)
			{	
				GetTrimurityArea(conn, tx, ty);
				tret = GetEmptyMobGrid(conn,&tx,&ty);
				while( FALSE == tret )
				{
					++iCount;
					if( 5 < iCount ) 
					{
						char temp[256];sprintf(temp,"err no empty space at resp_char_init x:%d y:%d",tx,ty);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						Log("clo err too many people near start point => 50",pUser[conn].AccountName,pUser[conn].IP);
						SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]);
						CloseUser(conn);
						return;
					}
					GetTrimurityArea(conn, tx, ty);
					tret = GetEmptyMobGrid(conn,&tx,&ty);

				}
			}

			if(bDie)										//	사망한 케릭터 
			{
				pMob[conn].MOB.nHP = 1;
				pMob[conn].MOB.nTP = 1;
			}

			//	최초 생성된 케릭터
			if(bCreate)
			{	pMob[conn].MOB.bySaveZone = ServerIndex+1;
				pMob[conn].MOB.snSaveX = tx;
				pMob[conn].MOB.snSaveZ = ty;
			}

			//	초기보유아이템 점검
			int nItemIndex=0; short snType; BOOL bRes=true;
			for(int i=0; i<MAX_INVEN; i++)
			{	if(pMob[conn].MOB.Inven[i].snIndex==0) continue;
				nItemIndex=pMob[conn].MOB.Inven[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
				if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
				{	//memset(&(pMob[conn].MOB.Inven[i]), 0, sizeof(STRUCT_ITEM));
					sprintf(temp,"err Invalid itemindex 10 char:%s itemindex:%d place:%d index:%d=> 10",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_INVEN,i);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					WriteLog( temp, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );	bRes=false;

					#ifdef __TN_LOCAL_SERVER_SWITCH__
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) );
					bRes = true;
					#endif
				}
			}
			for(i=0; i<MAX_EQUIP; i++)
			{	if(pMob[conn].MOB.Equip[i].snIndex==0) continue;
				nItemIndex=pMob[conn].MOB.Equip[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
				if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
				{	//memset(&(pMob[conn].MOB.Equip[i]), 0, sizeof(STRUCT_ITEM));
					sprintf(temp,"err Invalid itemindex 20 char:%s itemindex:%d place:%d index:%d=> 20",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_EQUIP,i);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					WriteLog( temp, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );	bRes=false;
					#ifdef __TN_LOCAL_SERVER_SWITCH__
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) );
					bRes = true;
					#endif
				}
			}
			for(i=0; i<MAX_CARGO; i++)
			{	if(pUser[conn].Cargo[i].snIndex==0) continue;
				nItemIndex=pUser[conn].Cargo[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
				if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
				{	//memset(&(pUser[conn].Cargo[i]), 0, sizeof(STRUCT_ITEM));
					sprintf(temp,"err Invalid itemindex  char:%s itemindex:%d place:%d index:%d => 30",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_CARGO,i);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					WriteLog( temp, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );	bRes=false;
					#ifdef __TN_LOCAL_SERVER_SWITCH__
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) );
					bRes = true;
					#endif
				}
			}

			if(!bRes) 
			{	sprintf(temp, "clo err AccountID:%s Char:%s Init fail", pUser[conn].AccountName, pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				CloseUser(conn); return; 
			}

			if(pMob[conn].MOB.byGMStatus & 0x01)	//	케릭터 블록된 경우
			{	sprintf(temp, "clo dbg AccountID:%s Char:%s Init fail - Blocked ", pUser[conn].AccountName, pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				CloseUser(conn); return; 
			}

			//	주신투구 착용시에는 주신투구의 적적성을 판단한다(비적절시 인벤이나 창고로 이동)
			nItemIndex = pMob[conn].MOB.Equip[eTNEqu_Helmet].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(nItemIndex>=5379 && nItemIndex<=5390)
			{
				bool bMove = false;
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Brahma)
				{
					if(nItemIndex>=5383) bMove = true;						//	브라흐마가 타주신의 주신투구를 착용
				}	else 
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Vishnu)
				{
					if(nItemIndex<5383 || nItemIndex>5386) bMove = true;	//	비슈느가 타주신의 주신투구를 착용
				}	else 
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Siva)
				{
					if(nItemIndex<5387) bMove = true;						//	브라흐마가 타주신의 주신투구를 착용
				}
				if(bMove)				//	주신투구가 주적절하여 인벤이나 창고로 옮긴다	
				{	int nPos = GetEmptyInven(conn);
					if(nPos>=0 && nPos<MAX_INVEN)		//	인벤에 자리가 있으면 인벤으로 옮긴다	
					{	memcpy(&pMob[conn].MOB.Inven[nPos], &pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Inven[nPos]));
						ZeroMemory(&pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Equip[eTNEqu_Helmet]));
						sprintf(temp,"err Invalid Trimuriti_Helmet itemindex:%d char:%s moved to Inven Index:%d", nItemIndex, pMob[conn].MOB.szName, nPos);
					}	else							//	인벤에 자리가 없을 경우 창고를 검색한다.
					{	nPos = GetEmptyCargo(conn);
						if(nPos>=0 && nPos<MAX_CARGO)	//	창고에 자리가 있을 경우 창고로 옮긴다.	
						{	memcpy(&pUser[conn].Cargo[nPos], &pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pUser[conn].Cargo[nPos]));
							ZeroMemory(&pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Equip[eTNEqu_Helmet]));
							sprintf(temp,"err Invalid Trimuriti_Helmet itemindex:%d char:%s moved to Cargo Index:%d", nItemIndex, pMob[conn].MOB.szName, nPos);
						}
					}
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					WriteLog( temp, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );
				}
			}
		
			//	전직데이터보정(기데이터수정)
			short snTribe = pMob[conn].MOB.snTribe;
			if(pMob[conn].MOB.byClass1==0 && pMob[conn].MOB.byClass2==0)
			{	if(snTribe==TRIBE_NAGA || snTribe==TRIBE_KINNARA)
				{	pMob[conn].MOB.byClass2=CLASS_SATVAN;
				}	else
				if(snTribe==TRIBE_ASURA || snTribe==TRIBE_RAKSHASA)
				{	pMob[conn].MOB.byClass2=CLASS_DHVANTA;
				}	else
				if(snTribe==TRIBE_YAKSA || snTribe==TRIBE_GANDHARVA)
				{	pMob[conn].MOB.byClass2=CLASS_NIRVANA;
				}	else
				if(snTribe==TRIBE_DEVA || snTribe==TRIBE_GARUDA)
				{	pMob[conn].MOB.byClass2=CLASS_MANTRIKA;
				}	else
				if(snTribe==0)
				{	//	GM tribe => 0
				}	else
				{	sprintf(temp,"dbg Invalid tribe char:%s tribe:%d ",pMob[conn].MOB.szName,pMob[conn].MOB.snTribe);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}
			}

			if ( pMob[conn].MOB.byClass1 == 2 && pMob[conn].MOB.byQuest[31] != 255 )
			{
				pMob[conn].MOB.byQuest[31] = 255;
				pMob[conn].MOB.byQuest[32] = 255;
				pMob[conn].MOB.byQuest[33] = 255;
				pMob[conn].MOB.byQuest[34] = 255;
				pMob[conn].MOB.byQuest[35] = 255;
			}

			//sprintf(temp,"dbg char:%s init position x:%d y:%d",pMob[conn].MOB.szName,tx,ty);
			//Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//------------------------------------------------------------------------
			// <공성전> 자신 guild가 공성전에 참가중인지 검사하여 clan을 변경시킨다.
			//------------------------------------------------------------------------
			if( eTNClan_GM != pMob[conn].MOB.byTrimuriti )
			{
				int iSiege = g_kSiege.get_Started();

				if( iSiege )
				{
					
					int iFlag = g_kSiege.SearchEntry( pMob[conn].MOB.nGuildID );

					if( -1 == iFlag ) pMob[conn].m_byClan = eTNClan_Siege4;
					else pMob[conn].m_byClan = iFlag;
				}
			}

			//	케릭터의 현재 이벤트 참여상태를 얻어온다.
			DWORD dwEvent = 0;
			char* pszGuild = NULL;
			int nGuildIndex = GetGuild(pMob[conn].MOB.nGuildID);

			if(nGuildIndex!=0 && nGuildIndex!=-1)
			{
				pszGuild = pGuild[nGuildIndex].GUILD.GuildName;
			}
			dwEvent = g_GameEvent.GetEventID(pUser[conn].m_dwEvent, pUser[conn].AccountName, pMob[conn].MOB.szName, pszGuild);
			sprintf(temp, "char_init event code:%X account:%s from client:%X\r\n", dwEvent, pUser[conn].AccountName, pUser[conn].m_dwEvent);
			TimeWriteLog(temp, "Data\\EVENT.TXT");
			pUser[conn].m_dwEvent = dwEvent;

			S_SCP_RESP_CHAR_INIT kMsg;
			kMsg.wType = SCP_RESP_CHAR_INIT;
			kMsg.wPDULength = sizeof(S_SCP_RESP_CHAR_INIT)-sizeof(HEADER);

			kMsg.byResult = m->byResult;
			kMsg.dwGameTime = time(NULL);
			kMsg.dwKeyID = conn;
			kMsg.snX = tx;
			kMsg.snZ = ty;
			memcpy( kMsg.bySkill, pMob[conn].MOB.bySkill, sizeof(BYTE)*MAX_SKILL );
			memcpy( kMsg.byQuest, pMob[conn].MOB.byQuest, sizeof(BYTE)*MAX_EVENT_FLAG );
			memcpy( kMsg.Inven, pMob[conn].MOB.Inven, sizeof(STRUCT_ITEM)*MAX_INVEN );
			memcpy( kMsg.Equip, pMob[conn].MOB.Equip, sizeof(STRUCT_ITEM)*MAX_EQUIP );
			memcpy( kMsg.Cargo, pUser[conn].Cargo, sizeof(STRUCT_ITEM)*MAX_CARGO );
			memcpy( kMsg.dwTimeStamp, pUser[conn].m_time, sizeof(kMsg.dwTimeStamp));
			kMsg.nCargoMoney = m->nNpcMoney;
			kMsg.nGuildID = pMob[conn].MOB.nGuildID;
			kMsg.byClan = pMob[conn].m_byClan;
			kMsg.dwEvent = pUser[conn].m_dwEvent;

			if(pMob[conn].MOB.nHP<=0) kMsg.byIsDead = 1;
			else	kMsg.byIsDead = 0;

			// 초기 좌표로그
			sprintf(temp,"init char:%s lev:%d x:%d y:%d rupiah: %d, cargo: %d, prana: %d, bramanp: %d, class(%d,%d) connecttype:%d, isDead:%d"
				,pMob[conn].MOB.szName,pMob[conn].MOB.byLevel,tx,ty,pMob[conn].MOB.nRupiah, m->nNpcMoney, pMob[conn].MOB.nPrana, pMob[conn].MOB.nBramanPoint, pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2, byConnectType, kMsg.byIsDead);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			fflush(fLogFile);

			//char chBuf[256] = {0,};
			//sprintf(chBuf, "init char:%s Type:%d x:%d y:%d \r\n",pMob[conn].MOB.szName,m->byConnType,tx,ty);
			//TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Position.txt" );

			pUser[conn].cSock.SendOneMessage((char*)&kMsg,sizeof(S_SCP_RESP_CHAR_INIT));

			SendStrongHoldData(conn);		//	현 요새상황을 알린다.
			SendCastleData(conn);			//	현 공성상황을 알린다.

			if(ServerIndex+1 == SERVER_KATANA3)
			{
				Msg_SetSalesRate sm; sm.wType = _Msg_SetSalesRate;
				sm.byType = eSearch;
				sm.byRate = g_byCastleSalesRate;
				sm.dwMoney = g_dwCastleSalesMoney;
				pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
			}

			// 샴발라 던전 2층인 경우, 메그하말린 퀘스트 진행중이면 클리어.
			if ( pMob[conn].MOB.byQuest[30] == 9 && ServerIndex == 5 ) QUEST_OnEvent( conn, 2072, 2072, 0, FALSE );

			if(g_eCountryID == eCountryChina)
			{	_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));			//	Billing Server에 케릭터의 초기화를 알린다
				bm.Packet_result = 0; bm.Map_number = ServerIndex+1;
				bm.User_co[0] = pMob[conn].TargetX; bm.User_co[1] = pMob[conn].TargetY;
				SendBilling3(conn, &bm, _Msg_BillUserInit);
			}

			if( MAX_USER <= conn && MAX_MOB > conn )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf( chBuf, "[SSP_RESP_CHAR_INIT] conn:%d \r\n", conn );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}

			//	BramanRank를 미리 세팅해줌으로서 init시 checkcast를 지원한다.
			pMob[conn].m_byBramanRank = g_RankSys.GetBramanRank(conn);

			pMob[conn].Init( conn ); // mob 초기화
			pMob[conn].m_dGetPranaRate = 100;
			pMob[conn].m_dGetMoneyRate = 100;
			pMob[conn].m_dCutDeathPranaRate = 100;
			if(pMob[conn].MOB.nHP<=0) 
			{
				pMob[conn].m_eFSM = eTNFsm_Dead;
				byte byDecPranaRate = pMob[conn].MOB.byDecPranaRate;
				byte byKillLevel    = pMob[conn].MOB.byKillLevel;
				if(byDecPranaRate<0 || byDecPranaRate>100) byDecPranaRate = 100;
				if(byKillLevel<1 || byKillLevel>99) byKillLevel = 0;

				double dPercent = (double)byDecPranaRate / 100;
				int iPrana = (int)(g_irgLevelUp[byKillLevel-1] * dPercent );
				iPrana *= (int)(pMob[conn].m_dCutDeathPranaRate/100);
				pMob[conn].m_iPranaDec = iPrana;
				pMob[conn].m_byDecPranaRate = byDecPranaRate;
				pMob[conn].m_byKillLevel = byKillLevel;

				pMob[conn].MOB.byDecPranaRate = 0;
				pMob[conn].MOB.byKillLevel = 0;
			}

			// 30초 동안 PK에 적용이 안되게 한다.
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_ProtectFromPK;
			kEffect.iDuration = g_irgSetting[eCnst_ProtectionFromPK]; //15000;
			pMob[conn].AddEffect( kEffect, conn, conn );

			pMob[conn].ProcessContinuousEffect();

			if(bDie) 
			{	pMob[conn].MOB.nHP = pMob[conn].m_iMaxHP / 2;
				pMob[conn].MOB.nTP = pMob[conn].m_iMaxTP / 2;
			}

			pMob[conn].NotifyUpdateUIMsg();

            pMob[conn].LastTime = CurrentTime;
			// check snX,Y -1. set default if -1			
			pMob[conn].LastX = pMob[conn].TargetX = tx;
			pMob[conn].LastY = pMob[conn].TargetY =	ty;
			pUser[conn].Coin = m->nNpcMoney;
			pUser[conn].LastChat[0]=0;
            pUser[conn].NumError		= 0;
            pUser[conn].LastMove		= 0;
			pUser[conn].LastAction		= _MSG_Action;
			pUser[conn].LastActionTick	= SKIPCHECKTICK; 
			pUser[conn].LastAttack		= 0;
			pUser[conn].LastAttackTick  = SKIPCHECKTICK;
			pUser[conn].nPreX = pMob[conn].TargetX;
			pUser[conn].nPreY = pMob[conn].TargetY;
			pUser[conn].m_dwLastTickTime = m->dwClientTick;
			//pUser[conn].LastIllusionTick=SKIPCHECKTICK;
//			pUser[conn].RankingTarget	= 0;
//			pUser[conn].RankingType		= 0;
			memset(pUser[conn].LastSkillTick,-1,sizeof(pUser[conn].LastSkillTick));
			memset(&(pUser[conn].Trade),0,sizeof(pUser[conn].Trade));
			memset(pUser[conn].szTrade,0,SZTRADE_LENGTH);
            //for (int l=0;l<MAX_TRADE;	l++) pUser[conn].Trade.CarryPos[l]=-1;
            //for (	l=0;l<MAX_AUTOTRADE;l++) pUser[conn].AutoTrade.CarryPos[l]=-1;
			pUser[conn].TradeMode = 0;
			pUser[conn].byTradeMode = 0;
			pUser[conn].PKMode	 = 0;
			pUser[conn].m_snTimeMode  = 0;
			pUser[conn].m_nCash = 0;
			pUser[conn].m_nChallengeMode = 0;
			pUser[conn].m_nChallenger = 0;
			pUser[conn].nGuildIndex	  = 0;
			pUser[conn].nGuildLevel	  = 0;
			memset(pUser[conn].TradeItem, 0, sizeof(pUser[conn].TradeItem));

			pMobGrid[ty][tx] = conn;
			// !!!!!!! tret 처리 !!!!!!!!!!
			pMob[conn].LastX	= pMob[conn].TargetX = tx;
			pMob[conn].LastY	= pMob[conn].TargetY = ty;
			pUser[conn].Mode	= USER_PLAY;
			pUser[conn].LastX	= tx;
			pUser[conn].LastY	= ty;
			pUser[conn].Trade.OpponentID = 0; // 거래중 아님. 
			pUser[conn].m_byItemStatus = 0;
		
			pUser[conn].m_nAllianceUser = 0;
			pUser[conn].m_byAllianceMode = 0;

			SendWhoMessage(conn);			//	bot 검색

			//pMob[conn].GetCurrentScore(conn);
			//pUser[conn].cSock.AddMessage((char*)m,sizeof(MSG_CNFCharacterLogin));
			//pUser[conn].ReqHp=pMob[conn].MOB.nHP;
			//pUser[conn].ReqMp=pMob[conn].MOB.CurrentScore.Mp;
			//pUser[conn].bQuaff=0;

			//	1st,18st,19st zone일경우 savezone을 해당존으로 갱신한다.
			if(ServerIndex==0 || ServerIndex==17 || ServerIndex==18)
			{	BYTE bySave = pMob[conn].MOB.bySaveZone;
				if(bySave==0 || bySave==17 || bySave==18)
				{	pMob[conn].MOB.bySaveZone=ServerIndex+1;
				}
			}

			//	사망후이동시 잘못된 
			if(byConnectType==CONNECT_TYPE_DIE && bCenter)
			{	pMob[conn].MOB.snSaveX=tx;	pMob[conn].MOB.snSaveZ=ty;
				pMob[conn].MOB.bySaveZone=ServerIndex+1;
			}

			//	Messenger Login
			MSG_MessengerLogin	mm;	mm.wType=_MSG_MessengerLogin;
			mm.nID=conn; mm.nServerIndex=ServerIndex;
			mm.nSlot=pUser[conn].Slot; mm.nGuildID=pMob[conn].MOB.nGuildID;
			strncpy(mm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
			strncpy(mm.CharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			MSGServerSocket.AddMessage((char*)&mm, sizeof(mm));

			pUser[conn].cSock.SendMessage();

			if ( g_nItemCashType == eItemCashTypeGeneral ) 
			{
				Msg_Item sMsgItem; sMsgItem.wType = _Msg_Item;
				sMsgItem.nID = conn; sMsgItem.byType = 1;
				sMsgItem.nWorld = ServerGroup;
				strncpy(sMsgItem.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				ItemServerSocket.SendCashMessage((char*)&sMsgItem,sizeof(Msg_Item));
			}

			//	Guild Initialize
			int nGuildLevel = 0;
			if(pMob[conn].MOB.nGuildID!=0)
			{	if(nGuildIndex<=0 || nGuildIndex>=MAX_USER)
				{	sprintf(temp,"dbg Init Char:[%s] GuildID:%d nGuildIndex:%d nGuildRank:%d", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID, nGuildIndex, 0);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}	else
				{	nGuildLevel = pGuild[nGuildIndex].GetLevel(pMob[conn].MOB.szName);

					//	길마의 랭킹이 초기화되는 문제발생 => 길드에 길드장이름을 기억시키기로 한다.
					//	문제발생시 길드장이름을 체크하여 복구해준다
					//	길드장 접속시 복구하므로 길드장 접속전까지 길드장이 없는 길드가 생길수 있다.
					if(nGuildLevel==0)
					{	if(strncmp(pMob[conn].MOB.szName, pGuild[nGuildIndex].szGuildMaster, SZNAME_LENGTH)==0) 
						{	
#ifdef	__LOG_GUILD__
							char chBuf[1024] = { 0,0,0, };
							sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
							TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#endif	//	#ifdef	__LOG_GUILD__							
							MSG_GuildSetRanking stRank; memset(&stRank, 0, sizeof(stRank));
							strncpy(stRank.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
                            stRank.GuildRank=eGuildMaster; nGuildLevel=eGuildMaster;
							pGuild[nGuildIndex].UpdateGuildMemberRank(&stRank);
#ifdef	__LOG_GUILD__
							memset(chBuf,0,1024);
							sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
							TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#endif	//	#ifdef	__LOG_GUILD__	
						}
					}

					//sprintf(temp,"dbg Init Char:[%s] GuildID:%d nGuildIndex:%d nGuildRank:%d", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID, nGuildIndex, nGuildLevel);
					//Log(temp,pUser[conn].AccountName,pUser[conn].IP);
#ifdef	__LOG_GUILD__
					char chBuf[1024] = { 0,0,0, };
					sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
					TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#endif	//	#ifdef	__LOG_GUILD__	
				}
			}
			if(nGuildIndex==-1)	//	길드정보가져오기 실패
			{	char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[Char_init] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID );
				Log(chBuf,pUser[conn].AccountName,pUser[conn].IP);
			}

			if(pMob[conn].MOB.byTrimuriti!=eTNClan_GM && ServerIndex+1==SERVER_KRUMA_LOW)
			{
				short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
				short snSkill  = pMob[conn].MOB.byLevel;
				if(eTNCls_2nd < pMob[conn].MOB.byClass1) snSkill += (((snSkill-35)/10)*2);

				if(snChakra>355 || snSkill>63)	//	차크라합이 355보다 크거나 스킬포인트가 63보다 클시에는 저랩크루마지역에 출입불가요청(2005.11.25)
				{
					pMob[conn].MOB.byZone = 1;
					pMob[conn].MOB.snX = -1;
					pMob[conn].MOB.snZ = -1;
					CloseUser(conn);
				}
			}

			if(nGuildIndex==0 || nGuildIndex==-1) 
			{	// 내 정보를 주위의 mob들에게 전송한다.
				S_SCP_INIT_OTHER_MOB sOther;
				GetCreateMob(conn,&sOther); 
				GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn,100);
				// 주위 정보를 가져온다.
				SendGridMob(conn);
				pUser[conn].cSock.SendMessage();
				break;
			}

			//	케릭터데이터 점검
			bool bRet=true;
			for(int i=0;i<MAX_GUILD_MEMBER;i++)			//	guild data에는 없고 케릭터정보에는 길드가입으로 되어있는 경우.
			{	//char pMember[SZNAME_LENGTH]; ZeroMemory(pMember, SZNAME_LENGTH);
				//strcpy(pMember, pGuild[nGuildIndex].GUILD.GuildInfo.MemberName[i]); strupr(pMember);
				if(!strcmp(pMob[conn].MOB.szName, pGuild[nGuildIndex].GUILD.Member[i].MemberName)) {bRet=false; break;}
			}
			if(bRet)
			{	sprintf(temp,"dbg Init GuildID:%d but not found [%s] => set guild 0", pMob[conn].MOB.nGuildID, pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				pMob[conn].MOB.nGuildID = 0;
				break;
			}
			pUser[conn].nGuildIndex = nGuildIndex;
			pUser[conn].nGuildLevel = nGuildLevel;
			for(int i=0;i<MAX_GUILD_MEMBER;i++)
			{	if(pGuild[nGuildIndex].pMemberIndex[i]==0) {pGuild[nGuildIndex].pMemberIndex[i]=conn; break;}
			}

			pMob[conn].LastX = tx;
			pMob[conn].LastY = ty;

			// 내 정보를 주위의 mob들에게 전송한다.
			S_SCP_INIT_OTHER_MOB sOther;
			GetCreateMob(conn,&sOther); 
			GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn,100);
			// 주위 정보를 가져온다.
			SendGridMob(conn);

			//	길드원에게 나의 접속을 알린다.
			MSG_GuildMemberin sm;	sm.wType=_MSG_GuildMemberin;
			sm.GuildID = pMob[conn].MOB.nGuildID;
			sm.wPDULength = sizeof(sm) - sizeof(HEADER);
			strncpy(sm.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*)&sm);
			//	내 길드정보를 가져온다.
			SendGuildInfo(conn, nGuildIndex);

		}	break;
         case _MSG_DBSavingQuit:
		 {    MSG_DBSavingQuit  * m = (MSG_DBSavingQuit *) msg;  
				int conn = m->nID;
				if	(conn<=0 || conn>=MAX_USER)
				{	Log("err DBsavingquit - id range","-system",0);
					break;
				}

				if	(strcmp(m->AccountName,pUser[conn].AccountName))
				{	Log("err dbsavingquit account not match",m->AccountName,0);
					Log("err dbsavingquit account not match",pUser[conn].AccountName,0);
					//MSG_STANDARD sm; sm.wType = _MSG_DBNoNeedSave;    sm.nID=conn;
					//DBServerSocket.SendOneMessage((char*)&sm,sizeof(MSG_STANDARD));	  
				}
				if	(pUser[conn].Mode!=USER_PLAY && pUser[conn].Mode!=USER_SAVING4QUIT)
				{	MSG_STANDARD sm; sm.wType = _MSG_DBNoNeedSave;    sm.nID=conn;
					if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(MSG_STANDARD)))
					{	Log("err DBSavingquit DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
					}

				}

				if	(pUser[conn].Mode==USER_PLAY || pUser[conn].Mode==USER_SELCHAR )
				{	if	(m->Mode==0) SendClientMessage(conn, g_pMessageStringTable[_Reconnecting_Other_Place]);	else	//"다른곳에서 접속하여 접속을 종료합니다."
					if	(m->Mode==1) SendClientMessage(conn, g_pMessageStringTable[_Check_Account]);		//"관리자가 계정을 확인중..
					pUser[conn].cSock.SendMessage();
				}
				CloseUser(m->nID);
				// 그냥 닫아도 반드시 Empty가 되지는 않고, Play,Saving4Quit중이면 커넥션끊고 SavingQuit 모드로
				// 바뀐다.
			}	break;
/////////////////////////////////////////////////////////////////////////////////////////////
         case SSP_RESP_SAVE_QUIT:
		 {    MSG_STANDARD  * m = (MSG_STANDARD *) msg;  
			  int conn = m->nID;
		      pMob[conn].Mode=MOB_EMPTY;
		      pUser[conn].Mode=USER_ACCEPT;        // 이러면 확실히 닫힌다.
		      CloseUser(conn);
		 }    break;
		 case SSP_REQ_SHUTDOWN:
		{	ServerDown = 1;
		}	break;
		case SSP_RESP_APPEAL_CHAT:
		{	S_SSP_RESP_APPEAL_CHAT * m = (S_SSP_RESP_APPEAL_CHAT *) msg;
			S_SCP_RESP_APPEAL_CHAT sm; sm.wType = SCP_RESP_APPEAL_CHAT;
			sm.byResult = m->byResult;
			strncpy(sm.szMsg,m->szMsg,MAX_CHAT_LENGTH);
			pUser[m->nID].cSock.AddMessage((char*)&sm,sizeof(S_SCP_RESP_APPEAL_CHAT));
		} break;
		case SSP_RESP_CHARACTER_SEARCH:
		{	S_SSP_RESP_CHARACTER_SEARCH * m = (S_SSP_RESP_CHARACTER_SEARCH *) msg;
			if ( m->byResult ==0 ) sprintf(temp, "%s(%s) %s %d",m->szCharName,m->szAccountID,g_pMessageStringTable[_Is_In_Zone],m->byZone);
			else sprintf(temp, "%s %s",m->szCharName, g_pMessageStringTable[_Is_Not_Connect]);
			SendClientMessage( m->nID, temp );

		} break;
		 case SSP_RESP_WHISPER_CHAT:
		{	S_SSP_RESP_WHISPER_CHAT * m = (S_SSP_RESP_WHISPER_CHAT *) msg;
			
			int conn = m->nID;
			m->szName[SZNAME_LENGTH-1]=0; m->szName[SZNAME_LENGTH-2]=0;
			m->szMsg[MAX_CHAT_LENGTH-1]=0; m->szMsg[MAX_CHAT_LENGTH-2]=0;
			S_SCP_RESP_WHISPER_CHAT sm; sm.wType=SCP_RESP_WHISPER_CHAT;
			sm.byResult=m->byResult; sm.byTrimuriti=m->byTrimuriti;

			if(sm.byResult != REPLY_ACK_OK)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return;
			}

			sm.byTextColor=m->byTextColor; sm.byBgColor=m->byBgColor;
			strncpy(sm.szName, m->szName, SZNAME_LENGTH);
			strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}	break;
		case SSP_NOTIFY_WHISPER_CHAT:
		{	S_SSP_NOTIFY_WHISPER_CHAT * m = (S_SSP_NOTIFY_WHISPER_CHAT *) msg;

			int conn = m->nID;
			m->szName[SZNAME_LENGTH-1]=0; m->szName[SZNAME_LENGTH-2]=0;
			m->szMsg[MAX_CHAT_LENGTH-1]=0; m->szMsg[MAX_CHAT_LENGTH-2]=0;

			S_SCP_NOTIFY_WHISPER_CHAT sm; sm.wType=SCP_NOTIFY_WHISPER_CHAT;
			sm.wPDULength = sizeof(sm)-sizeof(HEADER);
			sm.byTextColor=m->byTextColor; sm.byBgColor=m->byBgColor;
			sm.byTrimuriti=m->byTrimuriti;
			strncpy(sm.szName, m->szName, SZNAME_LENGTH);
			strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}	break;
		case _MSG_Chat:
		{	MSG_Chat * m = (MSG_Chat *) msg;
			
			if(m->byMsgType==MESSAGE_PARTY)
			{
			}	else
			if(m->byMsgType==MESSAGE_GUILD)
			{	int nIndex = IsGuildMemberIn(m->nGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}	else
				{	//	해당길드원이 없을 경우
				}
			}	else
			if(m->byMsgType==MESSAGE_GUILD_ALLIANCE)
			{	int nIndex = IsGuildMemberIn(m->nGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}

				nIndex = IsGuildMemberIn(m->nAlliedGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}
			}	else
			{	//	Unknown type
			}
		}	break;
		case _MSG_COMMAND :
			{
				MSG_COMMAND* pMsg = (MSG_COMMAND*)msg;
				char szPassword[1024] = { 0,0,0, };
				char szCommand[1024] = { 0,0,0, };
				sscanf( pMsg->szMsg, "%s %s", szPassword, szCommand );
				if( !strcmp( szPassword, "/52anwndWjq" ) )
				{
					strncpy( pMob[0].MOB.szName, pMsg->szName, sizeof(pMob[0].MOB.szName) );
					//pMob[0].MOB.byTrimuriti = eTNClan_GM;
					int iSize = strlen( szPassword );
					if( MAX_NOTIFY_LENGTH <= iSize ) break;
					++iSize;
					ControlSystem( 0, &(pMsg->szMsg[iSize]), false );
				}
				else if( !strcmp( szPassword, "/tanhgm103" ) )
				{ // /tanhgm103 /DecPrana Off
					strncpy( pMob[0].MOB.szName, pMsg->szName, sizeof(pMob[0].MOB.szName) );
					//pMob[0].MOB.byTrimuriti = eTNClan_GM;
					int iSize = strlen( szPassword );
					if( MAX_NOTIFY_LENGTH <= iSize ) break;
					++iSize;
					HelpGameMaster( 0, &(pMsg->szMsg[iSize]), false );
				}
			}
			break;
		case _MSG_Broadcast:
		{	MSG_Broadcast * m = (MSG_Broadcast *) msg;

			if(m->byMsgType==MESSAGE_BATTLEORDER)		//	전투명령서(동일주신에게만 전송)
			{	SendTrimuriti(m->byTrimuriti, (MSG_STANDARD*)m); return;
			}	else
			if(m->byMsgType==MESSAGE_EXTRA)				//	전광판(주신전에는 전송안됨)
			{	if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_CHATURANGKA) return;
			}	else
			if(m->byMsgType==MESSAGE_SERVERMSG)			//	GM공지(클라이언트팝업창)
			{	
				if(ServerIndex==0)
				{
					sprintf(temp, "broadcast Sender:%s Note:%s", m->szName, m->szMsg);
					Log(temp,"-system",0);
				}
			}

			SendToAll((MSG_STANDARD*)m);
		}	break;
		case _MSG_CreateGuild:
		{	MSG_CreateGuild * m = (MSG_CreateGuild*) msg;			//	Guild 생성시

			int conn = GetMOBID(m->Member.MemberName);
			if(conn == 0) break;

			if(m->GuildID==-1) 
			{ 
				//	길드생성비용을 돌려준다.
				pMob[conn].IncGold(GUILD_CREATE_COST);

				sprintf(temp, "gld Create Fail Guild: %s Price: %d", m->GuildName, GUILD_CREATE_COST);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				
				MSG_MobStatus nm; nm.wType=_MSG_MobStatus;
				nm.nID=conn; nm.byTradeMode=pUser[conn].byTradeMode;
				nm.nRupia=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.AddMessage((char*)&nm, sizeof(nm));
				SendClientMessage(conn, g_pMessageStringTable[_Guild_Make_Name_Double]);

				SendGuildInfo(conn, -1); 
				break; 
			}

			int nGuildIndex = pGuild[conn].CreateGuild(conn, m);
			pMob[conn].MOB.nGuildID = m->GuildID;
			pUser[conn].nGuildIndex = nGuildIndex;
			pUser[conn].nGuildLevel = eGuildMaster;
			SendGuildInfo(conn, nGuildIndex);						//	길드생성을 알린다.

			sprintf(temp, "gld Create Guild char:%s guildname:%s guildid:%d", pMob[conn].MOB.szName, pGuild[nGuildIndex].GUILD.GuildName, pGuild[nGuildIndex].GUILD.GuildID);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			/*														//	길드생성시 마크가 없으므로 일단 처리안한다.
			int tx=pMob[conn].TargetX;								//	길드생성을 주위에 알린다.
			int ty=pMob[conn].TargetY;
			MSG_GuildNotify sm; sm.wType=_MSG_GuildNotify;
			sm.wPDULength=sizeof(MSG_GuildNotify)-sizeof(HEADER);
			strncpy(sm.GuildName, m->GuildName, GUILDNAME_LENGTH);
			sm.nID=conn; sm.nMark=m->GuildMark;
			GridMulticast(tx,ty,(MSG_STANDARD*)&sm,conn,50);*/
		}	break;
		case _MSG_AddGuildMember:									//	길드멤버 추가시
		{	MSG_AddGuildMember * m = (MSG_AddGuildMember*) msg;

			int nIndex = IsGuildMemberIn(m->GuildID);
			if(nIndex<=0 || nIndex>=MAX_USER) break;

			int conn=GetMOBID(m->Member.MemberName);

			if(m->nID==MAX_USER)	//	길드원추가 실패
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Add_Fail]);
				break;
			}

			//	길드원의 추가를 알린다.
			SendGuildMessage(nIndex, (MSG_STANDARD*) m);

			//	길드에 멤버를 가입한다.
			pGuild[nIndex].AddGuildMember(m);

			sprintf(temp, "gld Add Guildmember char:%s MOB.nGuildID=%d guildname:%s", m->Member.MemberName, m->GuildID, pGuild[nIndex].GUILD.GuildName);
			Log(temp, "-system", 0);

#ifdef	__LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_AddGuildMember] GuildID:%d GuildMark:%d GuildMembers : %s \r\n", pGuild[nIndex].GUILD.GuildID, pGuild[nIndex].GUILD.Mark, m->Member.MemberName);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nIndex].GUILD.Member[i].MemberName, pGuild[nIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef	__LOG_GUILD__

			if(conn<=0 && conn>=MAX_USER) break;
			//	해당존에 추가길드멤버가 잇을경우 길드가입을 시킨다.
			for(int i=0;i<MAX_GUILD_MEMBER;i++)
			{	if(pGuild[nIndex].pMemberIndex[i]==0) {pGuild[nIndex].pMemberIndex[i]=conn; break;}
			}

			pUser[conn].nGuildIndex = nIndex;
			pUser[conn].nGuildLevel = eGuildMember;
			pMob[conn].MOB.nGuildID = m->GuildID;
			SendGuildInfo(conn, nIndex);							//	길드정보를 알린다.

			if(pGuild[nIndex].GUILD.Mark!=0)						//	길드마크존재시
			{	int tx=pMob[conn].TargetX;							//	길드가입을 주위에 알린다.
				int ty=pMob[conn].TargetY;
				MSG_GuildNotify sm; sm.wType=_MSG_GuildNotify;
				sm.wPDULength=sizeof(MSG_GuildNotify)-sizeof(HEADER);
				strncpy(sm.GuildName, pGuild[nIndex].GUILD.GuildName, GUILDNAME_LENGTH);
				sm.nID=conn; sm.nMark=pGuild[nIndex].GUILD.Mark;
				GridMulticast(tx,ty,(MSG_STANDARD*)&sm,conn,50);
			}

			//	Messenger Login
			MSG_MessengerLogin	mm;	mm.wType=_MSG_MessengerLogin;
			mm.nID=conn; mm.nServerIndex=ServerIndex;
			mm.nSlot=pUser[conn].Slot; mm.nGuildID=pMob[conn].MOB.nGuildID;
			strncpy(mm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
			strncpy(mm.CharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			MSGServerSocket.AddMessage((char*)&mm, sizeof(mm));
		}	break;
		case _MSG_RemoveGuildMember:								//	길드멤버 탈퇴시
		{	MSG_RemoveGuildMember * m = (MSG_RemoveGuildMember*) msg;

			int nIndex = IsGuildMemberIn(m->GuildID);
			if(nIndex<=0 || nIndex>=MAX_USER) break;

			SendGuildMessage(nIndex, (MSG_STANDARD*) m);

			if(m->byRemoveType==eGuild_Remove_All)
			{	Log("err Guild Removeall Message", "-system", 0);
				//pGuild[nIndex].Mode = GUILD_EMPTY;
				//ZeroMemory(&pGuild[nIndex].GUILD, sizeof(STRUCT_GUILD));
				break;
			}

			sprintf(temp, "dbg _MSG_RemoveGuildMember guchar:%s guildname:%s guildid:%d", m->CharacterName, pGuild[nIndex].GUILD.GuildName, pGuild[nIndex].GUILD.GuildID);
			Log(temp, "-system", 0);

			pGuild[nIndex].RemoveGuildMember(m->CharacterName);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_RemoveGuildMember] GuildID:%d GuildMark:%d GuildMembers : %s \r\n", pGuild[nIndex].GUILD.GuildID, pGuild[nIndex].GUILD.Mark, m->CharacterName);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nIndex].GUILD.Member[i].MemberName, pGuild[nIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

			int conn = GetMOBID(m->CharacterName);
			if(conn==0) break;

			for	(int i=0;i<MAX_GUILD_MEMBER;i++)
			{	if(pGuild[nIndex].pMemberIndex[i]==conn) { pGuild[nIndex].pMemberIndex[i]=0; break;}
			}
			pMob[conn].MOB.nGuildID=0;
			pUser[conn].nGuildIndex=0;
			pUser[conn].nGuildLevel=0;

			int nAlly = pUser[conn].m_nAllianceUser;
			if(nAlly>0 && nAlly<MAX_USER)
			{
				RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL);
				RemoveAlliance(nAlly, REPLY_GUILDALLIANCE_CANCEL);
			}

			if(pGuild[nIndex].GUILD.Mark!=0)						//	길드마크존재시
			{	int tx=pMob[conn].TargetX;							//	길드탈퇴를 주위에 알린다.
				int ty=pMob[conn].TargetY;
				MSG_GuildNotify sm; sm.wType=_MSG_GuildNotify;
				sm.wPDULength=sizeof(MSG_GuildNotify)-sizeof(HEADER);
				strncpy(sm.GuildName, pGuild[nIndex].GUILD.GuildName, GUILDNAME_LENGTH);
				sm.nID=conn; sm.nMark=0;
				GridMulticast(tx,ty,(MSG_STANDARD*)&sm,conn,50);
			}
		}	break;
		//case _MSG_GuildMemberin:
		//{	MSG_GuildMemberin * m = (MSG_GuildMemberin*) msg;

		//	int nIndex = IsGuildMemberIn(m->GuildID);
		//	if(nIndex<=0 || nIndex>=MAX_USER) break;
		//	SendGuildMessage(nIndex, (MSG_STANDARD*) m);
		//}	break;
		//case _MSG_GuildMemberout:
		//{	MSG_GuildMemberout * m = (MSG_GuildMemberout*) msg;
		//	
		//	int nIndex = IsGuildMemberIn(m->GuildID);
		//	if(nIndex<=0 || nIndex>=MAX_USER) break;
		//	SendGuildMessage(nIndex, (MSG_STANDARD*) m);
		//}	break;
		case _MSG_GuildUpdate:
		{	MSG_GuildUpdate * m = (MSG_GuildUpdate *)msg;
			int nGuildIndex = IsGuildMemberIn(m->GuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			if(eZoneType_Guild == g_iZoneType)
			{
				for(int i=0; i<eStronghold_MaxCount; i++)
				{
					if(g_krgStronghold[i].iOwner==m->GuildID)			//	요새소유 아쉬람의 정보가 변경되엇을 경우
					{
						int iFriend = GetGuildID(m->AlliedGuildName1);	//	만약 연합길드가 바뀌었으면 클랜설정을 변경하라
						if(iFriend!=g_krgStronghold[i].iOwnerFriend)
						{
                            g_krgStronghold[i].iOwnerFriend = iFriend;
							RefreshClan( i, eTNClan_Stronghold1 + i );
							continue;
						}
					}
				}
			}

			if(pGuild[nGuildIndex].GUILD.AlliedGuildName1[0]==0 && m->AlliedGuildName1[0]!=0)	//	동맹이 없다가 생길경우
			{	
				pGuild[nGuildIndex].nAlliedID = GetGuildID(m->AlliedGuildName1);				//	길드내에 동맹길드id를 갱신한다.(연합길드채팅을 위함)
			}
			else if(pGuild[nGuildIndex].GUILD.AlliedGuildName1[0]!=0 && m->AlliedGuildName1[0]==0)	//	동맹이 해제 되엇을 경우
			{
				pGuild[nGuildIndex].nAlliedID = 0;
			}

			//	길드의 정보를 변경한다.
			strncpy(pGuild[nGuildIndex].GUILD.AlliedGuildName1, m->AlliedGuildName1, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.AlliedGuildName2, m->AlliedGuildName2, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.EnemyGuildName1, m->EnemyGuildName1, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.GuildMessage, m->GuildMessage, GUILDMESSAGE_LENGTH);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_GuildUpdate] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

			SendGuildMessage(nGuildIndex, (MSG_STANDARD *)m);
		}	break;
		case _MSG_GuildUpdateMember:
		{	MSG_GuildUpdateMember * m = (MSG_GuildUpdateMember *)msg;

			if(m->nID==MAX_USER)
			{	sprintf(temp, "err Update Guildmember member:%s rank:%d level%d", m->Member.MemberName,  m->Member.GuildRank,  m->Member.byLevel);
				Log(temp, "-system", 0); break;
			}

			int nGuildIndex = IsGuildMemberIn(m->GuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			//	길드내 길드원정보를 갱신한다.
			pGuild[nGuildIndex].UpdateGuildMember(m);
			//if(pGuild[nGuildIndex].UpdateGuildMember(m))
			//{	//	rank 변경시
			//	int conn = GetMOBID(m->Member.MemberName);
			//	if(conn==0) break;
			//	pUser[conn].nGuildLevel = m->Member.GuildRank;
			//}

			sprintf(temp, "gld Update Guildmember member:%s rank:%d level%d", m->Member.MemberName,  m->Member.GuildRank,  m->Member.byLevel);
			Log(temp, "-system", 0);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_GuildUpdateMember] GuildID:%d GuildMark:%d GuildMembers : %s rank:%d level:%d  \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, m->Member.MemberName,  m->Member.GuildRank,  m->Member.byLevel);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

			SendGuildMessage(nGuildIndex, (MSG_STANDARD*)m);
		}	break;
		case _MSG_GuildSetRanking:
		{	MSG_GuildSetRanking * m = (MSG_GuildSetRanking *)msg;
			int nGuildIndex = IsGuildMemberIn(m->nGuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			int nRes = pGuild[nGuildIndex].UpdateGuildMemberRank(m);	//	길드내 길드원정보를 갱신한다.

			if(nRes<0) { Log("err dbguildsetrank",m->CharacterName, 0); break; }
			int nID = GetMOBID(m->CharacterName);
			if(nID>0 || nID<MAX_USER) pUser[nID].nGuildLevel=m->GuildRank;
			SendGuildMessage(nGuildIndex, (MSG_STANDARD*)m);

			sprintf(temp, "gld Update Guildrank char:%s Guildid:%d rank:%d", m->CharacterName, m->nGuildID, m->GuildRank);
			Log(temp,pUser[nID].AccountName, pUser[nID].IP);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_GuildSetRanking] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

		}	break;
		case _MSG_GuildUpdateMark:
		{	MSG_GuildUpdateMark * m = (MSG_GuildUpdateMark *)msg;
			int nGuildIndex = IsGuildMemberIn(m->GuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			//	길드의 정보를 변경한다.
			pGuild[nGuildIndex].GUILD.Mark=m->Mark;

			int nMember=0;
			for (int i=0;i<MAX_GUILD_MEMBER;i++)
			{   nMember=pGuild[nGuildIndex].pMemberIndex[i];
				if (nMember<=0 || nMember>=MAX_USER || pUser[nMember].Mode!=USER_PLAY) continue; 

				int tx=pMob[nMember].TargetX;							//	길드탈퇴를 주위에 알린다.
				int ty=pMob[nMember].TargetY;
				MSG_GuildNotify sm; sm.wType=_MSG_GuildNotify;
				sm.wPDULength=sizeof(MSG_GuildNotify)-sizeof(HEADER);
				strncpy(sm.GuildName, pGuild[nGuildIndex].GUILD.GuildName, GUILDNAME_LENGTH);
				sm.nID=nMember; sm.nMark=pGuild[nGuildIndex].GUILD.Mark;
				GridMulticast(tx,ty,(MSG_STANDARD*)&sm,nMember,50);
			}

			SendGuildMessage(nGuildIndex, (MSG_STANDARD *)m);

			sprintf(temp, "gld Update GuildMark GuildID:%d to Mark:%d", m->GuildID, m->Mark);
			Log(temp,"-system", 0);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, };
			sprintf(chBuf, "[_MSG_GuildUpdateMark] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" );
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__
		}	break;
		case _MSG_GMMode:
		{	MSG_GMMode* m = (MSG_GMMode*)msg;

			int nID = m->nID;
			if(nID<1 || nID>=MAX_USER)
			{	Log("err _DBMSG_GMMode",m->szCharName, 0);
				return;
			}
			//	GM에게 결과를 전송한다.
			pUser[nID].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		case _MSG_GMMode_Notify:
		{	MSG_GMMode_Notify* m = (MSG_GMMode_Notify*)msg;

			int nID=m->nID;
			if(nID<1 || nID>=MAX_USER)
			{	Log("err _DBMSG_GMMode_Notify","-system", 0); return;
			}

			int tx=pMob[nID].TargetX; int tz=pMob[nID].TargetY;
			if(tx<0 || tx>=MAX_GRIDX || tz<0 || tz>=MAX_GRIDX)
			{	Log("err_cri _MSG_GMMode command but invalid_position",pMob[nID].MOB.szName,0); return;
			}

			BYTE bySet = m->byGMMode >> 7;
			BYTE byFlag = 0;
			BYTE byPos = 1;
			BYTE byMode = pMob[nID].MOB.byGMStatus;

			for(int i=0; i<7; i++)
			{	byFlag = m->byGMMode << (7-i);
				byFlag >>= (7-i);
				if(byFlag) 
				{	BYTE byRest = byMode << (8-i);
					byRest >>= (8-i);
					byMode >>= (i+1);
					byMode <<= 1;
					byMode += bySet;
					byMode <<= i;
					byMode += byRest;
					break;
				}
			}

			pMob[nID].MOB.byGMStatus = byMode;

			GridMulticast(tx,tz,(MSG_STANDARD*)m,-1,100);
		}	break;
		case _MSG_GMMoveToPlayer:
		{	MSG_GMMoveToPlayer* m = (MSG_GMMoveToPlayer*)msg;

			if(m->nID<=0 || m->nID>=MAX_USER) return;

			if(m->byZone==0)
			{	
				sprintf(temp,"%s %s", m->szCharName, g_pMessageStringTable[_Is_Not_Connect]);
				SendClientMessage(m->nID, temp); return;
			}

			pMob[m->nID].m_kWaitAction.iAction = eWaitAct_ZonePortal;
			pUser[m->nID].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		case _MSG_GMKickPlayer:	// From DB
		{	MSG_GMKickPlayer* m = (MSG_GMKickPlayer*)msg;

			int nGm = m->nID;
			if(nGm<=0 || nGm>=MAX_USER) return;
			if(pMob[nGm].MOB.byTrimuriti != eTNClan_GM) return;

			if ( m->nResult == 0 ) sprintf(temp,"%s %s", m->szCharName, g_pMessageStringTable[_Is_Closed]);
			else sprintf(temp,"%s %s", m->szCharName, g_pMessageStringTable[_Is_Not_Connect]);
			SendClientMessage(nGm,temp);
			//pUser[m->nID].cSock.SendOneMessage((char*)m, sizeof(MSG_GMKickPlayer));
		}	break;
		case _MSG_KickAccount:
		{	MSG_KickAccount* m = (MSG_KickAccount*)msg;

			int conn = m->iID;
			if(conn<=0 || conn>=MAX_USER) return;

			if(strncmp(pUser[conn].AccountName, m->AccountName, ACCOUNTNAME_LENGTH)!=0) break;

			sprintf(temp,"clo ser disconnect last:%d server:%d mode:%d conn:%d by UserManager",pUser[conn].LastReceiveTime,SecCounter,pUser[conn].Mode,conn);
			Log(temp,pUser[conn].AccountName,0);

			SendClientMessage(conn, g_pMessageStringTable[_Reconnecting_Other_Place]);
			CloseUser(conn);					//	유저와의 접속을 종료한다.
		}	break;
		case _MSG_NPTaskInfo:
		{	MSG_NPTaskInfo* m = (MSG_NPTaskInfo*)msg;
			if ( m->nTaskNumber == 0 ) break;
			QUEST_SetTask( m->nTaskNumber, &(m->sTaskInfo) );
		}	break;
		case _MSG_NPGiftInfo:
		{	MSG_NPGiftInfo* m = (MSG_NPGiftInfo*)msg;
			g_nGiftItemIndex = m->nGiftItemIndex;
			ZeroMemory(&GiftItem, sizeof(GiftItem));
			bool bRet = true; short sMaxDur = 0;
			bRet &= g_ParamMgr.HT_bGetItemMaxDurability	(g_nGiftItemIndex, &sMaxDur);
			if(bRet)
			{	GiftItem.snIndex = g_nGiftItemIndex - HT_PARAMTYPE_ITEM_START + 1;
				GiftItem.snDurability = sMaxDur;
				GiftItem.byCount = 1; 
				GiftItem.byRefineLevel = 0;
				ZeroMemory( GiftItem.bySubRefine, sizeof(GiftItem.bySubRefine) );
			}	else
			{	g_snGiftItemGenTime = 0;
			}
			g_nGiftItemCount =
			g_nGiftItemMaxCount = 
			g_nGiftItemFirstCount = m->nGiftItemCount;
			g_snGiftItemGenTime = m->snGiftItemGenTime*(1000/TICKSIZE);
		}	break;
		case _Msg_TrimuritiStatus:
		{	Msg_TrimuritiStatus* m = (Msg_TrimuritiStatus*)msg;

			g_iBrahmaCount = m->iTrimuritiCount[0];
			g_iVishnuCount = m->iTrimuritiCount[1];
			g_iSivaCount = m->iTrimuritiCount[2];	
		}	break;
		case _Msg_BramanBonus:
		{	Msg_BramanBonus* m = (Msg_BramanBonus*)msg;

			char pTrimuriti[16] = {0,};
			char pTemp[128] = {0,};
			if(m->byTrimuriti==eTNClan_Brahma)
			{
				if(ServerIndex+1==eZone_Cruma) g_nBrahmaBP += m->nBonus;
				strncpy(pTrimuriti, g_pMessageStringTable[_Brahma], sizeof(pTrimuriti));
			}
			else if(m->byTrimuriti==eTNClan_Vishnu) 
			{
				if(ServerIndex+1==eZone_Cruma) g_nVishnuBP += m->nBonus;
				strncpy(pTrimuriti, g_pMessageStringTable[_Vishnu], sizeof(pTrimuriti));;
			}
			else if(m->byTrimuriti==eTNClan_Siva) 
			{
				if(ServerIndex+1==eZone_Cruma) g_nSivaBP += m->nBonus;
				strncpy(pTrimuriti, g_pMessageStringTable[_Siva], sizeof(pTrimuriti));
			}

			MSG_Broadcast sm;
			sm.wType = _MSG_Broadcast;
			sm.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

			sm.byBgColor = 14;
			sm.byTextColor = 15;
			sm.byMsgType = 1; 

			sprintf(sm.szMsg, g_pMessageStringTable[_Bramanpoint_Contribytion1], m->pCharName, pTrimuriti, m->nBonus);
			sprintf(pTemp, g_pMessageStringTable[_Bramanpoint_Contribytion2], pTrimuriti);
			strcat(sm.szMsg, pTemp);

			SendToAll((MSG_STANDARD*)&sm);			//	브라만포인트 보너스발생을 알린다.
		}	break;
		case _MSG_NPGuildItemUpdate:
		{	MSG_NPGuildItemUpdate* m = (MSG_NPGuildItemUpdate*)msg;
			SetGuildCargo( m->nGuildID, m->nGuildInvenIndex, &m->sItem );
		} break;
   }
}

//	MSG Server Message
void ProcessMSGMessage( char* msg )
{
	MSG_STANDARD* std = (MSG_STANDARD *) msg;


	switch (std->wType)
	{ 
	case _MSG_MessengerLogin:
		{	int conn = std->nID;
			if(conn<=0 || conn>=MAX_USER) return;

			//	로그인한자를 가진 모든 유저의 주소록을 검색을 후 등록자를 로그인처리한다.
			MSG_MessengerLogin * m = (MSG_MessengerLogin *)msg;
			for(int i=1; i<MAX_USER; i++)
			{
				if(pUser[i].Mode!=USER_PLAY) continue;
				for(int k=0; k<MAX_MESSENGER; k++)
				{
					if(!strcmp(pUser[i].Item[k].szCharName, m->CharName))
					{	m->nSlot=k;
						pUser[i].Item[k].Status=2;
						pUser[i].cSock.SendOneMessage((char*)m, sizeof(*m));
						break;
					}
				}
			}

			//	로그인한자를 가진 모든 길드원에게 알린다.
			int nGuild = m->nGuildID;
			if(nGuild<=0) return;
			int nGuildIndex = GetGuild(nGuild, false);
			if(nGuildIndex>0 && nGuildIndex<MAX_USER)
			{	MSG_GuildMemberin sm; sm.wType = _MSG_GuildMemberin;
				sm.wPDULength = sizeof(MSG_GuildMemberin)-sizeof(HEADER);
				strncpy(sm.CharacterName, m->CharName, SZNAME_LENGTH);
				sm.GuildID = nGuild;	
				SendGuildMessage(nGuildIndex, (MSG_STANDARD*)&sm);
			}
		}	break;
	case _MSG_MessengerLogout:
		{	int conn = std->nID;
			if(conn<=0 || conn>=MAX_USER) return;
			
			//	로그아웃자를 가진 모든 유저의 주소록을 검색을 후 등록자를 로그아웃처리한다.
			MSG_MessengerLogout * m = (MSG_MessengerLogout *)msg;
			for(int i=1; i<MAX_USER; i++)
			{
				if(pUser[i].Mode!=USER_PLAY) continue;
				for(int k=0; k<MAX_MESSENGER; k++)
				{
					if(!strcmp(pUser[i].Item[k].szCharName, m->CharName))
					{	m->nSlot=k;
						pUser[i].Item[k].Status=1;
						pUser[i].cSock.SendOneMessage((char*)m, sizeof(*m));
						break;
					}
				}
			}

			//	로그아웃자를 가진 모든 길드원에게 알린다.
			int nGuild = m->nGuildID;
			if(nGuild<=0) return;
			int nGuildIndex = GetGuild(nGuild, false);
			if(nGuildIndex>0 && nGuildIndex<MAX_USER)
			{	MSG_GuildMemberout sm; sm.wType = _MSG_GuildMemberout;
				sm.wPDULength = sizeof(MSG_GuildMemberout)-sizeof(HEADER);
				strncpy(sm.CharacterName, m->CharName, SZNAME_LENGTH);
				sm.GuildID = nGuild;
				SendGuildMessage(nGuildIndex, (MSG_STANDARD*)&sm);
			}
		}	break;
	case _MSG_UpdateMessengerList:
		{	int conn = std->nID;
			if(conn<=0 || conn>=MAX_USER) return;	

			MSG_UpdateMessengerList * m = (MSG_UpdateMessengerList *)msg;

			memcpy(pUser[conn].Item, m->Item, sizeof(STRUCT_MESSENGER_ITEM)*MAX_MESSENGER);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _MSG_UpdateMessengerItem:		//	주소록 추가, 삭제
		{	int conn = std->nID;
			if(conn<=0 || conn>=MAX_USER) return;
			
			MSG_UpdateMessengerItem * m = (MSG_UpdateMessengerItem *)msg;

			pUser[conn].Item[m->nSlot]=m->Item;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		//case _MSG_MessengerChangeMyInfo:	//	주소록 등록자의 데이터가 변경됨
		//{	MSG_MessengerChangeMyInfo * m = (MSG_MessengerChangeMyInfo *)msg;

		//	for(int i=1; i<MAX_USER; i++)
		//	{
		//		if(pUser[conn].Mode!=USER_PLAY) continue;
		//		for(int k=0; k<MAX_MESSENGER; k++)
		//		{
		//			if(!strcmp(pUser[i].Item[k].szCharName, m->Item.szCharName))
		//			{	pUser[i].cSock.SendOneMessage((char*)m, sizeof(*m));

		//				//	Messenger로 해당유저의 데이터변경을 알린다.
		//				MSG_MessengerSave sm; sm.wType=_MSG_MessengerSave;
		//				sm.nID=conn; sm.nSlot=k; sm.Item=m->Item;
		//				MSGServerSocket.AddMessage((char*)&sm, sizeof(sm));
		//				break;
		//			}
		//		}
		//	}			
		//}	break;
	case _MSG_Chat:
		{	MSG_Chat * m = (MSG_Chat *) msg;
			
			if(m->byMsgType==MESSAGE_PARTY)
			{
			}	else
			if(m->byMsgType==MESSAGE_GUILD)
			{	int nIndex = IsGuildMemberIn(m->nGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}	else
				{	//	해당길드원이 없을 경우
				}
			}	else
			if(m->byMsgType==MESSAGE_GUILD_ALLIANCE)
			{	int nIndex = IsGuildMemberIn(m->nGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}	
				nIndex = IsGuildMemberIn(m->nAlliedGuildID);
				if(nIndex>0)
				{	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
				}
			}	else
			{	//	Unknown type
			}
		}	break;
	case _MSG_Broadcast:
		{	MSG_Broadcast * m = (MSG_Broadcast *) msg;

			if(m->byMsgType==MESSAGE_BATTLEORDER)		//	전투명령서(동일주신에게만 전송)
			{	SendTrimuriti(m->byTrimuriti, (MSG_STANDARD*)m); return;
			}	else
			if(m->byMsgType==MESSAGE_EXTRA)				//	전광판(주신전에는 전송안됨)
			{	if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_CHATURANGKA) return;
			}	else
			if(m->byMsgType==MESSAGE_SERVERMSG)			//	GM공지(클라이언트팝업창)
			{	
				if(ServerIndex==0)
				{
					sprintf(temp, "broadcast Sender:%s Note:%s", m->szName, m->szMsg);
					Log(temp,"-system",0);
				}
			}

			SendToAll((MSG_STANDARD*)m);
		}	break;
	case SSP_NOTIFY_WHISPER_CHAT:
		{	S_SSP_NOTIFY_WHISPER_CHAT * m = (S_SSP_NOTIFY_WHISPER_CHAT *) msg;

			int conn = m->nID;
			m->szName[SZNAME_LENGTH-1]=0; m->szName[SZNAME_LENGTH-2]=0;
			m->szMsg[MAX_CHAT_LENGTH-1]=0; m->szMsg[MAX_CHAT_LENGTH-2]=0;

			S_SCP_NOTIFY_WHISPER_CHAT sm; sm.wType=SCP_NOTIFY_WHISPER_CHAT;
			sm.wPDULength = sizeof(sm)-sizeof(HEADER);
			sm.byTextColor=m->byTextColor; sm.byBgColor=m->byBgColor;
			sm.byTrimuriti=m->byTrimuriti;
			strncpy(sm.szName, m->szName, SZNAME_LENGTH);
			strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}	break;
	case _MSG_GuildMemberin:
		{	MSG_GuildMemberin * m = (MSG_GuildMemberin *) msg;

			int conn = m->GuildID;
			if(conn<=0 || conn>=MAX_USER) break;
			if(pUser[conn].nGuildIndex==0) break;

			m->GuildID = pMob[conn].MOB.nGuildID;
			pUser[conn].cSock.AddMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_StrongHoldInit:
	case _Msg_StrongHoldUpdate:
		{	Msg_StrongHoldInit * m = (Msg_StrongHoldInit*)msg;

			for(int i=0; i<eStronghold_MaxCount; i++)
			{
				strncpy(g_krgStronghold[i].szGuildName, m->szGuildName[i], SZGUILD_LENGTH);
				g_krgStronghold[i].dwMark = m->dwMark[i];
			}
			SendToAll((MSG_STANDARD*)msg);
		}	break;
	case _Msg_CastleInit:
	case _Msg_CastleUpdate:
		{	Msg_CastleInit * m = (Msg_CastleInit*)msg;

			g_iCastleOwner = m->iCastleOwner;

			SendToAll((MSG_STANDARD*)msg);
		}	break;
	case _Msg_StrongHoldStatus:
		{	Msg_StrongHoldStatus * m = (Msg_StrongHoldStatus*)msg;

			g_iBattleForStronghold = m->byMode;
		}	break;
	}
}


// 게임서버가 DB서버에 DBSaveMobAndQuit을 요청했다.
// 메시지가 먹었다!
// DB서버는 다시 DBSavingQuit을 요청하게 된다. (클라이언트가 로그인 시도하니까)
// 게임서버는 역시 다시 날려야 한다.
// 이때 게임서버의 USER 모드는 USER_SAVINGUSER 이다.
// 게임 서버가 다시 DBSaveMobAndQuit을 날렸을때, DB서버가 그제서야 
// 이전의 DBSavMobAndQuit을 받았다.
// Login이  False인 AccountList의 SavMobAndQuit은 DB서버는 처리할 필요 없다.
// 공교롭게 그 사이에 다른 사람이 AccountList에 조인 할 수 없다.
// AccountList는 게임서버의 conn에 종속적인데,
// 게임서버는 이때 conn이 USER_SAVINGUSER이기 때문에, 새로운 클라이언트를
// 받았을리가 없다. 









///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//                    타이머 처리기

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



//////////LAST RECEIVE TIME//////////////////////////////////////////
void CheckIdle(int conn)
{
	//if	(conn<=0||conn>=MAX_USER) return;
	//if	(pUser[conn].Mode==USER_EMPTY||pUser[conn].Mode==USER_SAVING4QUIT) return;
	int ser	= SecCounter;					// 0.5초단위이므로 unsigned가 필요없다.
	int lst = pUser[conn].LastReceiveTime;	// 0.5초단위이므로 unsigned가 필요없다.
	if	(lst>ser)		pUser[conn].LastReceiveTime = SecCounter; //마지막패킷 받은 시간이 현재보다 더 클수는 없다.
	if	(lst<ser-1440)	pUser[conn].LastReceiveTime = SecCounter; //12분 이상 경과했는데아직 붙어 있을리가 없다

	if	(lst<ser-1440)// 6분=360초=720 SecCount   720/4 = 180
	{
		sprintf(temp,"clo ser disconnect last:%d server:%d mode:%d conn:%d",pUser[conn].LastReceiveTime,SecCounter,pUser[conn].Mode,conn);
		Log(temp,pUser[conn].AccountName,0);
		CloseUser(conn);
	}
}


void CheckTimeTask( int conn )
{
	if(conn<=0||conn>=MAX_USER) return;
	bool bChanged = false;
	pUser[conn].CharLoginTime++;

	if( 0 == (pUser[conn].CharLoginTime%450) ) // 1 시간에 한번, 3600(8*450)
	{
		
		if( eTNChr_Vaisha > pMob[conn].MOB.nBramanPoint )
		{
			pMob[conn].MOB.nBramanPoint += 15;			
			pMob[conn].CheckCaste();
			bChanged = true;
		}

		//if( 0 < pMob[conn].MOB.snKarma )
		//{
		//	pMob[conn].MOB.snKarma -= g_irgSetting[eCnst_DecKarmaPoint];
		//	if( 0 > pMob[conn].MOB.snKarma ) pMob[conn].MOB.snKarma = 0;
		//	bChanged = true;
		//}

		

		//pUser[conn].NumError = 0; // 1시간 마다 error point를 초기화한다.
	}

	if( 0 == (pUser[conn].CharLoginTime%75) )  // 10분에 한번, 600(8*75)
	{	
		pUser[conn].m_LastTime += 10000;			//	스핵점검시 체크하고 30000일때 초기화한다.

		if( 0 < pMob[conn].MOB.snKarma )
		{	int nPrevKarma = pMob[conn].MOB.snKarma;
			pMob[conn].MOB.snKarma -= g_irgSetting[eCnst_DecKarmaPoint];
			int iReduceKarma = (pMob[conn].m_krgVariation[eTNVar_ReduceKaram][eVar_Equipment].iPlus + pMob[conn].m_krgVariation[eTNVar_ReduceKaram][eVar_Skill].iPlus + pMob[conn].m_krgVariation[eTNVar_ReduceKaram][eVar_PassiveSkill].iPlus);
			pMob[conn].MOB.snKarma -= iReduceKarma;
			if( 0 > pMob[conn].MOB.snKarma ) pMob[conn].MOB.snKarma = 0;
			bChanged = true;
			sprintf( temp, "karma %d -> %d", nPrevKarma, pMob[conn].MOB.snKarma );
			Log( temp, pUser[conn].AccountName, pUser[conn].IP );
		}

		// 10분에 1회 초기화
		pMob[conn].m_kSkillCastRecord.iSkill = 0;
		pMob[conn].m_kSkillCastRecord.uiTime = 0;
		pMob[conn].m_kSkillCastRecord.iCount = 0;
	}

	//if( 0 == (pUser[conn].CharLoginTime%2) ) // 16초 마다 한번, 16= 8*2
		//pMob[conn].RefreshEnemyCount();

	if( 0 == (pUser[conn].CharLoginTime%45) ) // 6분 마다 한번 크랙포인트를 낮춰준다.
		if(pUser[conn].NumError>5)  pUser[conn].NumError -= 5;

	if( bChanged ) pMob[conn].NotifyUpdateUIMsg();
}


// 4초마다 PC 상태 회복 
void RegenMob(int conn)
{
	if(conn<=0||conn>=MAX_USER) return;

    //REGEN///////////////////////////////////////////////////////////
	if	(pMob[conn].Mode ==MOB_EMPTY)	return;
	if	(0>=pMob[conn].MOB.nHP)			return;
	if	(conn<MAX_USER && pUser[conn].Mode!=USER_PLAY) return;
    ///////////////////////////////////////////////////////////

	if( (pMob[conn].m_iMaxHP == pMob[conn].MOB.nHP) && (pMob[conn].MOB.nTP == pMob[conn].m_iMaxTP) )
	{
		if( eTNVSAfn_Empty != pMob[conn].m_iAffections ) pMob[conn].BroadcastUpdateStatusMsg( true );
		return;
	}
	if( 0 >= pMob[conn].MOB.nHP ) return;

	int iState = eTNFsm_Stand;
	if( eTNFsm_Sit == pMob[conn].m_eFSM )
	{
		if( (0 != pMob[conn].m_kLastTime.uiSitted) && (8000 < (CurrentTime - pMob[conn].m_kLastTime.uiSitted)) ) iState = eTNFsm_Sit;
	}

    int HpRegen		= pMob[conn].m_irgHPRecovery[iState];
	int TpRegen		= pMob[conn].m_irgTPRecovery[iState];
	if( eTNInAfn_PreventRegenHP & pMob[conn].m_iInnerAffections ) HpRegen = 0;
	if( eTNInAfn_PreventRegenTP & pMob[conn].m_iInnerAffections ) TpRegen = 0;
	if( eZoneType_God != g_iZoneType )
	{
		if( 0 < pMob[conn].MOB.snKarma )
		{ // 살인자이면 regen이 하나도 되지 않는다.
			HpRegen = 0;
			TpRegen = 0;
		}
	}
	//#ifdef __TN_2ND_LOG__
	//{
	//	char chBuf[512] = { 0,0,0, };
	//	sprintf(chBuf, "\t[regenmob] mob(%d)의 현재 HP가 %d인데 %d를 회복해서 %d가 되었습니다. 현재상태(%d; 0:앉기,1:서기)\r\n", conn, pMob[conn].MOB.nHP, HpRegen, pMob[conn].MOB.nHP+HpRegen, iState );
	//	pMob[conn].Print( chBuf );
	//}
	//#endif //__TN_2ND_LOG__

	pMob[conn].IncHP( HpRegen );
	pMob[conn].IncTP( TpRegen );

	// party원들에게 HP 상태를 표시
	if( conn>0 && conn<MAX_USER)
	{	S_SCP_RESP_UPDATE_PARTY sm; sm.wType=SCP_RESP_UPDATE_PARTY;
		sm.wPDULength=sizeof(sm)-sizeof(HEADER);
		sm.Party.nCurHP=pMob[conn].MOB.nHP; sm.Party.nCurTP=pMob[conn].MOB.nTP;
		sm.Party.byLevel=pMob[conn].MOB.byLevel; sm.Party.nMaxHP=pMob[conn].m_iMaxHP;
		sm.Party.nMaxTP=pMob[conn].m_iMaxTP; sm.Party.nID=conn;
		sm.Party.nAffections=pMob[conn].m_iAffections;
		strncpy(sm.Party.Name,pMob[conn].MOB.szName,SZNAME_LENGTH);

		int nLeader=0;
		if(pMob[conn].Leader==0) nLeader=conn;
		else nLeader=pMob[conn].Leader;

		SendPartyMessage(nLeader, (MSG_STANDARD*)&sm);
		// party원들 유무에 따라서 UpdateStatus 메시지 전달
	}

	///////////////////////////////////////////////////////////
	pMob[conn].BroadcastUpdateStatusMsg( true );
}



// 초타이머
void ProcessSecTimer( void )
{
	// SecCounter
	SecCounter++;

	//	Server shutdown; 
	if	(ServerDown==120)
	{	while(TRUE)
		{	// Terminate window when shut down complete
			if	(UserCount>=MAX_USER)
			{	Log("ser server down complete","-system",0);
				if (hFont)	 {DeleteObject(hFont);hFont=NULL;}
				if (DBServerSocket.nSendPosition!=DBServerSocket.nSentPosition) {DBServerSocket.SendMessage(); break;}
				int nUser = 1;
				while(TRUE)
				{	if(pUser[nUser].Mode!=USER_EMPTY && pUser[nUser].Mode!=USER_ACCEPT)
					{	pMob[nUser].m_kWaitAction.iAction = eWaitAct_ServerDown;
						CloseUser(nUser);
						if(nUser<MAX_USER) return;
					}
					++nUser;
					if(nUser==MAX_USER) break;
				}
				PostQuitMessage(NULL);
				return;
			}
            if	(pUser[UserCount].Mode==USER_EMPTY)
			{	UserCount++;
				continue;
			} 
			//  save 1 user
            pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH-1]=0;
			pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH-2]=0;
			sprintf(temp,"ser save %d - %d - %s",UserCount,pUser[UserCount].Mode,pUser[UserCount].AccountName);
			Log(temp,"-system",0);
			pMob[UserCount].m_kWaitAction.iAction = eWaitAct_ServerDown;
            CloseUser(UserCount);
			UserCount++;
			break;
		}
		return;
	}
	//	Prepare, Server shutdown.
	if	(ServerDown>=0)
	{	ServerDown++;
		if	(ServerDown%40==0)
		{	int idx = (ServerDown/40);  // 20 ~ 100 =>0-4
			char pMsg[256]; int nTime=30-idx*10;
			sprintf(pMsg, g_pMessageStringTable[_Server_Close_Time], nTime);
			SendNotice(pMsg);
		}
		if	(ServerDown==120)
		{	SetTimer(hWndMain, TIMER_SEC, 100,NULL);  // 1초에 10명씩 접속을 종료 시킨다.
			UserCount=0;
			return;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(g_snGiftItemGenTime != 0 && (SecCounter%g_snGiftItemGenTime == 0)) 
		g_nGiftItemMaxCount--;

	GetLocalTime( &g_kSystemTime );
	CurrentTime = timeGetTime();		// CurrentTime은 0.25초마다 update
	int	Rst2	=	(SecCounter&0x01);	//SecCounter%2;
	int	Rst4	=	(SecCounter&0x03);	//SecCounter%4;
	int	Rst8	=	(SecCounter&0x07);	//SecCounter%8;
    int Rst16	=	(SecCounter&0x0F);	//SecCounter%16;
	int Div16	=	(SecCounter>>4);	//SecCounter/16;
	int Rst32	=	(SecCounter&0x1F);	//SecCounter%32;
	int Div32	=	(SecCounter>>5);	//SecCounter/32;
	int Rst64	=	(SecCounter&0x3F);	//SecCounter%64;
	int Div64	=	(SecCounter>>6);	//SecCounter/64;
	int Rst128	=	(SecCounter&0x7F);	//SecCounter%128;
	int Div128	=	(SecCounter>>7);	//SecCounter/128;
	int Rst256	=	(SecCounter&0xFF);	//SecCounter%256;
	int Div256	=	(SecCounter>>8);	//SecCounter/256;
	int Rst512	=	(SecCounter&0x01FF);//SecCounter/1024;

	if( 0 == Rst4 ) // 1초(=4/4)
	{	MSGServerSocket.SendMessage();
		if((ServerIndex+1)==SERVER_KATANA3 && g_Yut.HT_bIsPlayOn())	//	카타나3의 육놀이 게임 진행중일경우
			if(YutCounter>0) HT_PlayYut();
	}

	if( 0 == Rst16 ) // 4초(=16/4)
	{
		// time scheduler를 동작시킨다. 그런데 time을 알아야 한다.
		int iEvent = g_srgTimeSchedule[g_iTimeSlot];
		if( 0 < iEvent )
		{

			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\r\nTimeSlot:%d, Event:%d", g_iTimeSlot, iEvent );
				WriteLog( chBuf, ".\\Monster_Log\\[Log]TimeSchedulet.txt" );
			}

			TriggerEvent( 0, iEvent, 0, 0, 0, 70 );
		}

		//if( g_bIsInRvR ) // 주신전에서만 채킹을 한다.
		if( eZoneType_God == g_iZoneType )
		{
			if( (0 == (g_iHours % 24)) && (0 == g_iTimeSlot) )
			{ // 12시간마다 초기회를 해준다. 
				// 정확한 확률이 발생하지 않는다. 모든 card를 다 쓰고 resuffle을 할 때, data를 refresh해야하는데, 3주신이라서 그 시점을 못 찾는다.
				double dDistribution[5] = { 0,0,0, };
				dDistribution[0] = g_irgEntryCount[eTNClan_Brahma] / g_irgEntryCount[0];
				dDistribution[1] = g_irgEntryCount[eTNClan_Vishnu] / g_irgEntryCount[0];
				dDistribution[2] = g_irgEntryCount[eTNClan_Siva] / g_irgEntryCount[0];

				
				for( int k = 0; k < 3; ++k )
				{
					//dDistribution[k] = 50 - int(dDistribution[k] * dDistribution[k] * 200); // 50 - (2 * ((분포)^2 * 100))
					dDistribution[k] = 400 - int(dDistribution[k] * dDistribution[k] * 500); // 50 - (2 * ((분포)^2 * 100))
					if( eBlss_Min > dDistribution[k] ) dDistribution[k] = eBlss_Min;
					if( eBlss_Max < dDistribution[k] ) dDistribution[k] = eBlss_Max;
				}

				g_krgBlessOfGod[0][eTNClan_Brahma].Init();
				g_krgBlessOfGod[0][eTNClan_Brahma].AddCard( 25, (int)dDistribution[0] );
				g_krgBlessOfGod[0][eTNClan_Brahma].Shuffle();
				g_krgBlessOfGod[0][eTNClan_Vishnu].Init();
				g_krgBlessOfGod[0][eTNClan_Vishnu].AddCard( 25, (int)dDistribution[1] );
				g_krgBlessOfGod[0][eTNClan_Vishnu].Shuffle();
				g_krgBlessOfGod[0][eTNClan_Siva].Init();
				g_krgBlessOfGod[0][eTNClan_Siva].AddCard( 25, (int)dDistribution[2] );
				g_krgBlessOfGod[0][eTNClan_Siva].Shuffle();

				#ifdef __TN_EMERGENCY_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );

					char chBuf[1280] = { 0,0,0, };
					sprintf(chBuf, "\r\n[분포]%d시%d분%d초, %d : %d : %d,  총합:%d, 브라흐마:%d, 비슈누:%d, 시바:%d\r\n"
						, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, (int)dDistribution[0], (int)dDistribution[1], (int)dDistribution[2]
						,g_irgEntryCount[0], g_irgEntryCount[eTNClan_Brahma], g_irgEntryCount[eTNClan_Vishnu], g_irgEntryCount[eTNClan_Siva] );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RvREntry] );
				}
				#endif //__TN_EMERGENCY_LOG__
			}
		}

		++ g_iTimeSlot;
		if( eTS_MaxSlot <= g_iTimeSlot )
		{
			g_iTimeSlot = 0;
			++g_iHours; // 시간 지난 것에 대한 count를 둔다.
		}
	}

	int nDistance = 0; int nDistanceX = 0; int nDistanceY = 0;
	char pSpeed[256] = {0,};
	for (int i=1;i<MAX_USER;i++)
	{   
		if (pUser[i].Mode == USER_EMPTY) continue;

		// User ping check, every 8 sec  
		if	(i%32==Rst32 && pUser[i].Mode!=USER_EMPTY && pUser[i].Mode!=USER_SAVING4QUIT)
		{	CheckIdle(i);
		}

		if( USER_PLAY == pUser[i].Mode )
		{
			if( 0 < pMob[i].MOB.nHP )
			{
				if( i%8 == Rst8 ) // 2초
				{
					pMob[i].CheckAffections( CurrentTime );//  magic-affect, every 2 sec			
					pMob[i].ProgressWaitAction();

					////----------------------------------------------------------------
					//// 스피드핵 판정 코드 
					////----------------------------------------------------------------
					//if(pMob[i].MOB.byTrimuriti!=eTNClan_GM) 
					//{	//	2초당 한번 이동거리를 체크한다.
					//	nDistanceX = pMob[i].TargetX-pUser[i].nPreX;
					//	nDistanceY = pMob[i].TargetY-pUser[i].nPreY;
					//	nDistance = (int)sqrt((double)( nDistanceX*nDistanceX + nDistanceY*nDistanceY) );
					//	//	if(nDistance > 추정가능최대이동거리) 스핵판정
					//	if((pMob[i].m_iMoveSpeed<=5 && nDistance>25) || (pMob[i].m_iMoveSpeed>5 && nDistance>40)) 
					//	{	
					//		memset(pSpeed, 0, sizeof(pSpeed));
					//		sprintf(pSpeed, "Char:[%s] move Distance:%d per 4sec at speed:%d \r\n", pMob[i].MOB.szName, nDistance, pMob[i].m_iMoveSpeed);
					//		TimeWriteLog(pSpeed, ".\\Event\\[Log]Move.txt" );							
					//		AddCrackError(i, 5, CRACK_SPEED_HACK4); 
					//	}
					//	pUser[i].nPreX = pMob[i].TargetX;
					//	pUser[i].nPreY = pMob[i].TargetY;
					//}
				}
				
				//if( i%16 == Rst16 ) // 4초
				//{	if(pMob[i].MOB.byTrimuriti!=eTNClan_GM) 
				//	{	//	4초당 한번 이동거리를 체크한다.
				//		nDistanceX = pMob[i].TargetX-pUser[i].nPreX;
				//		nDistanceY = pMob[i].TargetY-pUser[i].nPreY;
				//		nDistance = sqrt((double)( nDistanceX*nDistanceX + nDistanceY*nDistanceY) );
				//		//	if(nDistance > 추정가능최대이동거리) 스핵판정
				//		if((pMob[i].m_iMoveSpeed<=5 && nDistance>40) || (pMob[i].m_iMoveSpeed>5 && nDistance>50)) 
				//		{	
				//			memset(pSpeed, 0, sizeof(pSpeed));
				//			sprintf(pSpeed, "Char:[%s] move Distance:%d per 4sec at speed:%d \r\n", pMob[i].MOB.szName, nDistance, pMob[i].m_iMoveSpeed);
				//			WriteLog(pSpeed, ".\\Event\\[Log]Move.txt" );							
				//			AddCrackError(i, 15, CRACK_SPEED_HACK4); 
				//		}
				//		pUser[i].nPreX = pMob[i].TargetX;
				//		pUser[i].nPreY = pMob[i].TargetY;
				//	}
				//}
				
				if( i%32 == Rst32 ) // 8초(=32/4)
				{
					RegenMob(i); //User regenaration HP MP,
					pMob[i].ForgetAttacker();
					pMob[i].ClearAggressiveScore();
					pMob[i].RefreshPKPrty();
					
					CheckTimeTask( i );
	//				SendWhoMessage(i);
				}

				if( i%128 == Rst128 ) // 32초(=128/4)
				{
					pMob[i].ProcessContinuousEffect();

					if(pUser[i].cSock.m_iWhoTick == 0) continue;
					pUser[i].cSock.m_iWhoTick -= 128;				//	Who 요청을 할 경우 32초마다 응답을 체크한다.
					if(pUser[i].cSock.m_iWhoTick <= 0)				//	Who 요청에 5분이상 응답이 없을 경우 bot로 판별하고 접속해지시킨다.
					{	sprintf(temp,"clo char_init not match zone char:%s", pMob[i].MOB.szName);
						Log(temp,pUser[i].AccountName,pUser[i].IP); 
						CloseUser(i);
					}
				}
			}
		}
/*	
		if(i%8==Rst8)
		{
			if	(pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY)
			{
				pMob[i].CheckAffections( CurrentTime );//  magic-affect, every 2 sec
				pMob[i].ProgressWaitAction();
			}
		}


		if( i%16 == Rst16 )
		{
			if	(pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY)
			{
				RegenMob(i); //User regenaration HP MP,
			}
		}
		
		if( i%32 == Rst32 )  // 8초(=32/4)
		{
			if( pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY )
			{
				pMob[i].RefreshPKPrty();
				CheckTimeTask( i );
			}
		}
*/

		// send packet in send buffer. every 1/4 sec.
	    if (pUser[i].cSock.nSendPosition==0) continue; // nSend는 초기화 접속끊김시 반드시 0이 되므로 USER_ACCEPT이상으로 체크할필요 없음.
		pUser[i].cSock.SendMessage();
	}
	//	billing auto-reconnect check
	if  (BILLING!=0 && BillCounter>0 && BillServerSocket.Sock==NULL)
	{	BillCounter--;
		if (BillCounter<=0)
		{	int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP2;			//	필리핀은 빌링을 인라인사용한다
			int ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip, WSA_READBILL, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect BILL Server(x2) fail.","-system",0);
				BILLING=0;//무료모드로 계속한다.
			}	else
			{	_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
				SendBilling2(&sm,4);
			}
		 }
	}   else BillCounter = 0;

	//	Item auto-reconnect check
	if(ItemCounter>0 && ItemServerSocket.Sock==NULL)
	{	ItemCounter--;
		if (ItemCounter<=0)
		{	int * pip = (int*)LocalIP1;
			int ret = ItemServerSocket.ConnectServer(ItemServerAddress,ItemServerPort ,*pip, WSA_READITEM, hWndMain, g_nItemCashType==eItemCashTypeGeneral);
			if ( ret == NULL ) ItemCounter = 360;
		}
	}

	//	MSG auto-reconnect check
	if(MSGCounter>0 && MSGServerSocket.Sock==NULL)
	{	MSGCounter--;
		if (MSGCounter<=0)
		{	int * pip = (int*)LocalIP2;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 MSG Public사용
			int ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort ,*pip, WSA_READMSG, hWndMain);
			if ( ret == NULL ) MSGCounter = 720;
		}
	}

	// auto-save 1 user per 16 sec
	if	(Rst64==0)  // 64/4
	{	for (int i=0;i<10;i++)  // check 10 user
		{	if (SaveCount>=MAX_USER) SaveCount=1;
			if (pUser[SaveCount].Mode==USER_PLAY && pMob[SaveCount].Mode!=MOB_EMPTY)
			{
				//	child billing  check.
				/*
				if	(BILLING==2 && pUser[SaveCount].Child==1 && pMob[SaveCount].MOB.CurrentScore.Level >= FREEEXP && (g_Hour<=12||g_Hour>=19) ) 
				{	SendClientMessage(SaveCount,g_pMessageStringTable[_NN_Child_Pay]);
					CharLogOut(SaveCount);
					SaveCount++;
					break;
				}
				*/

				if(pUser[i].cSock.m_iWhoTick == 0) SendWhoMessage(i);			//	bot 검색

				SaveUser(SaveCount,0);
				SaveCount++;
				
				break;
			}
			SaveCount++;
		}
	}

	// Logfile 갱신 - 16초에 한번씩 날짜 지났는지 확인하여 로그파일 새로 만듦.
	if (Rst64==0) // 64/4
	{	struct tm when; time_t now;
		time(&now); when= *localtime(&now);
		if(LastLogDay!=when.tm_mday)
		{
			StartLog();
		}


	}
	
	if(Rst128==0) // 32초(128/4)
	{	
		//	제련 축복변수가 32초당 50씩 감소한다.
		g_ItemRefineScale -= 50;
		if(g_ItemRefineScale<0) g_ItemRefineScale=0;

		//	제련 축복변수가 32초당 50씩 감소한다.
		for(int i=0; i<5; i++)
		{
			if(g_GateTick[i]>0)
			{
				g_GateTick[i]--;
				if(g_GateTick[i]<=0)
				{
					g_GateTick[i] = 0;
					g_GateScale[i] = 0;
					//	Gate delete
					if(g_hGate[i]>MAX_USER && g_hGate[i]<MAX_MOB) pMob[g_hGate[i]].OnKilled( 1000, 11 );
				}
			}
		}

		// scheduler 구동
		g_kScheduler.CheckNRunSchedule( CurrentTime );
		g_kSiege.CheckSymbols();
	}

	if(Rst512==0)
	{	if(ItemServerSocket.Sock!=NULL)
		{	int ser	= SecCounter;					// 0.5초단위이므로 unsigned가 필요없다.
			int lst = ItemServerSocket.LastReceiveTime;	// 0.5초단위이므로 unsigned가 필요없다.
			if	(lst>ser)		ItemServerSocket.LastReceiveTime = SecCounter; //마지막패킷 받은 시간이 현재보다 더 클수는 없다.
			if	(lst<ser-480)	ItemServerSocket.LastReceiveTime = SecCounter; //1분 이상 경과했는데아직 붙어 있을리가 없다

			if	(lst<ser-480)
			{
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					sprintf(temp,"ITEMSERVER disconnect last:%d cur:%d",ItemServerSocket.LastReceiveTime, SecCounter);
					Log(temp,"ITEMSERVER",0);
					ItemServerSocket.CloseSocket();
				}
				ItemCounter = 360;
			}
		}

		if(ServerIndex+1==SERVER_KATANA3 && g_pRentalStore!=NULL)				//	공성전의 경우 위탁상점을 갱신한다.(2분간격)
			g_pRentalStore->HS_CheckRentalStore();
	}

    ////////////////////////////////////////////////////////////////////////////////////
	/*	hp,mp regeneration by Potion;
	if	(Rest2==0)	// 물약 회복속도 0.5초 아니고 1초//
	{
		for	(int i=1;i<MAX_USER;i++)
		{	if	(pUser[i].Mode!=USER_PLAY)		 continue;
			if	(pMob[i].MOB.nHP<=0) continue;
			pUser[i].bQuaff=0;
			int ret1=ApplyHp(i);
			int ret2=ApplyMp(i);
			if (ret1) SendScore(i);	else	// 피가차면 다른사람에게도 보여야 한다.
			if (ret2) SendSetHpMp(i);
			//  1초니까 200만큼 회복
		}
	}
	*/
	// dropped item decay
	ProcessDecayItem(); 

	for	( i=Rst64;i<=mNPCGen.NumList;i=i+64)	// generator tick : 64 tick = 16 sec
	{	int Interval = mNPCGen.pList[i].MinuteGenerate;
		if( -1 == Interval )
		{		
			GenerateMob( i, 0, 0 );
			mNPCGen.pList[i].MinuteGenerate = 0;
		}
		else
		{
			if( 0 >= Interval )	continue; //{sprintf(temp,"err interval(npc pop-check time)  zero :%d",i);Log(temp,"-system",0);continue;}
			if( 0 != (Div64%Interval) ) continue;
			GenerateMob( i, 0, 0 );
		}	
	}

	ProcessMonster();
	ProcessRobot();
}

void ProcessMonster()
{
	int i = 0;
	// NPC AI
	int div = SecCounter % (SECSTANDINGBY);	 // %8,  1~7로 2초(8/4)를 나타낸다.
	for	( i=MAX_USER+div;i<MAX_MOB;i+=SECSTANDINGBY)  // User는 이하는 프로세스와 상관없기 때문에 MAX_USER + div 에서 시작한다 (div는 0일때도 있다.)
	{	
		if (i>=MAX_MOB) break;     // NAX_MOB이 8의 n승이면 이녀석이 빠진다.

		int mode = pMob[i].Mode;
		if( MOB_EMPTY == mode )
		{		
			if( eTNCls_Warrior == pMob[i].MOB.byClass1 ) // 2005년 4월 11일 변경사항
			{
				if( pMob[i].IsDead() )
				{// 시간 검사
					if( pMob[i].IsWaitToPop() ) continue;
				
					int iIndex = pMob[i].GenerateIndex;
					if( 0 > iIndex ) continue;
					int iMobListIndex = pMob[i].m_irgMobListIndex[0];
					int iMobListIndex2 = pMob[i].m_irgMobListIndex[1];
					if( 0 > iIndex || mNPCGen.NumList < iIndex ) 
					{
						// 소환 개체의 경우 여기로 빠질 수 있다.
						continue;
					}
					mNPCGen.pList[iIndex].krgMonsterList[iMobListIndex].srgReadyMobList[iMobListIndex2][1] = 1;
				}
			}

			continue;
		}

		if( 0 >= pMob[i].MOB.nHP )
		{	
			//Log("err standingby processer delete hp zero mob","-system",0);
			DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 110);
			continue;
		}			

		if( eTNAIO_LifeTime & pMob[i].m_iAIOption )
		{
			if( (0 < pMob[i].m_uiLifeTime) && (pMob[i].m_uiLifeTime < CurrentTime) )
			{
				KillMonster( i );
				continue;
			}
		}

		if( eTNAIO_HaveMaster & pMob[i].m_iAIOption )
		{
			//int iLeader = pMob[i].Leader;
			//if( i != pMob[iLeader].m_irgSummoned[pMob[i].MOB.byClass2] )
			//{			
			//	pMob[i].OnKilled( iLeader, 14 );
			//	continue;
			//}

			if( eTNCls2_Retainer == pMob[i].MOB.byClass2 )
				if( pMob[i].CheckDistanceFromMaster( eRetainer_DistanceFromMaster ) ) continue;
		}
	
		// 항상 client에서 보여야 한다.
		if( pMonsterData[pMob[i].MOB.nTP].byQuest[eMonPrty_Reserved3] ) 
		{
			S_SCP_RESP_UPDATE_STATUS kMsg;
			kMsg.wType = SCP_RESP_UPDATE_STATUS;
			kMsg.wPDULength = WORD(sizeof(S_SCP_RESP_UPDATE_STATUS)-sizeof(HEADER));
			kMsg.snKeyID = (short)i;
			kMsg.iHP = pMob[i].MOB.nHP;
			kMsg.iTP = 0;
			kMsg.iPrana = 0;
			kMsg.iAffections = pMob[i].m_iAffections ;
			kMsg.snKarma = 0;

			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&kMsg, i, 50 );
		}

		// 회복
		if( (0 < pMob[i].MOB.nHP) && (pMob[i].m_iMaxHP > pMob[i].MOB.nHP) )
		{
			int iPrevHP = pMob[i].MOB.nHP;
			int iHPRecovery = pMob[i].m_irgHPRecovery[1];
			if( eTNInAfn_PreventRegenHP & pMob[i].m_iInnerAffections ) iHPRecovery = 0;
			pMob[i].IncHP( iHPRecovery ); // HP 회복

			pMob[i].BroadcastUpdateStatusMsg();
		}

		// 2초에 한번 수행
		pMob[i].ForgetAttacker();

		if( eTNCls_Trap == pMob[i].MOB.byClass1 )
		{
			if( CurrentTime < pMob[i].m_uiActionLock ) continue;

			pMob[i].SelectSkill();
			pMob[i].UseSkill();

			continue;
		}

		if( eTNAIO_CombatOnly & pMob[i].m_iAIOption ) continue;
		if( eTNAIO_GetCommand & pMob[i].m_iAIOption ) continue; // 이동이 없을 것이다.

        if( MOB_PEACE == mode )
		{	
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
			pMob[i].CheckAffections( CurrentTime );
			pMob[i].InitStatus();
			pMob[i].InitCondition();

			if( eTNCls_SummonOld == pMob[i].MOB.byClass1 )
			{
				int iSummoner = pMob[i].Leader;
				if( MOB_EMPTY == pMob[iSummoner].Mode || MOB_PEACE == pMob[iSummoner].Mode )
				{ // summoner가 죽었거나 peace 상태에 있을 때, 소환을 푼다.
					KillMonster( i );
					//DeleteMob( i, 123, 0, eTNPrdt_RemoveNormal, 120 );
					continue;
				}
			}
						
			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}

			pMob[i].m_kLastTime.uiSelectTarget = 0;
			//pMob[i].m_iPlusRange = 0;

			if( 0 < pMob[i].m_iCastCount ) pMob[i].UseSkill();

			int last = pMob[i].SegmentProgress;

			// 1. 리더만 색적을 한다.
			int enemy = 0;
			if( pMob[i].m_kLastTime.uiActivate < CurrentTime ) // 10초 동안은 색적을 하지 않는다.
			{
				enemy = pMob[i].GetEnemyFromView(); // 시야에 적이 있어도, 자신의 목적지와 거리가 멀면 공격하지 않는다. (추격제한거리)
				pMob[i].m_kLastTime.uiActivate = 0;
			}

			if( 0 < enemy && MAX_MOB > enemy )
			{
				pMob[i].Think( eTNAI_Detect, enemy );
				pMob[i].OnUnderAttack( enemy );
				continue;
			}

			BOOL ret=pMob[i].StandingByProcessor(); 

			if( 0x1 & ret ) // 다음 segment로 이동하는 중간
			{	
				#ifdef __TN_5TH_LOG__
				{			
					//SYSTEMTIME st;
					//GetLocalTime( &st );

					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[Move] %d시%d분%d초(%d) Monster %d(%d)가 (%d,%d)에서 (%d,%d)로 이동 \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, CurrentTime, i, pMob[i].MOB.snTribe, pMob[i].TargetX, pMob[i].TargetY, pMob[i].NextX,pMob[i].NextY );
					pMob[i].Print( chBuf );
				}
				#endif // #ifdef __TN_5TH_LOG__

				pMob[i].Think( eTNAI_Move, 0 );

				MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
				sm.Effect = 2; // walk
				GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);

				int prog = pMob[i].SegmentProgress;   
				int gene = pMob[i].GenerateIndex;
			} 

			if( 0x10 & ret ) // 세그먼터 이동 완료.
			{	// 현제 세그먼트 프로그레스의 Action을 chat로 날린다.
				int	prog = pMob[i].SegmentProgress;   
				int	gene = pMob[i].GenerateIndex;
				if	(prog<0||prog>=MAX_SEGMENT)
				{	//Log("err Segment progress out of bound",pMob[i].MOB.szName,0);
					continue;
				}
				continue;
			}

			if( 0x100 & ret )      //  맙 삭제
			{
				KillMonster( i );
				DeleteMob( i, 3, 0, eTNPrdt_RemoveNormal, 140 );  // 자폭
				continue;
			}

			if( 0x1000 & ret )    //  0x 1000 근처를 배회 , 다음 segment로 이동하기전에 wait하는 시간동안
			{
				pMob[i].Think( eTNAI_Rest, 0 );
			}

			if( 0x0002 & ret )                      
			{	
				if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
				Teleport(i,pMob[i].NextX,pMob[i].NextY);
			}  
		} //  if  (mode == MOB_PEACE )
		else if( MOB_FLEE == mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	//Log("err standingby processer delete hp zero mob","-system",0);
				DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 150);
				continue;
			} 

			pMob[i].CheckAffections( CurrentTime );
			pMob[i].InitStatus();

			if( eTNVSAfn_DontMove & pMob[i].m_iAffections ) //if( (eTNVSAfn_Stun & pMob[i].m_iAffections) || (eTNVSAfn_Sleep & pMob[i].m_iAffections) )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}

			++pMob[i].m_iPathProgress;
			if( (eFlee_MaxPathCount <= pMob[i].m_iPathProgress) || (0 == pMob[i].m_krgPath[pMob[i].m_iPathProgress].x ) || (0 == pMob[i].m_krgPath[pMob[i].m_iPathProgress].y ) )
			{
				pMob[i].Mode = MOB_PEACE;
				pMob[i].UpdateSpeed();
				pMob[i].NextX = pMob[i].SegmentX;
				pMob[i].NextY = pMob[i].SegmentY;

				int iDist = pMob[i].CalDistance2( pMob[i].SegmentX, pMob[i].SegmentY );
				if( (eConst_TooFarRange < iDist) )
					Teleport(i,pMob[i].NextX,pMob[i].NextY);
				else
				{
					int iMove = pMob[i].m_iMoveSpeed;
					if( 0 >= iMove ) iMove = 1;
					pMob[i].m_kLastTime.uiActivate = ((iDist - pMob[i].SegmentRange[pMob[i].SegmentProgress])/iMove + 5)*1000 + CurrentTime;
				}

				continue;
			}
			pMob[i].NextX = pMob[i].m_krgPath[pMob[i].m_iPathProgress].x;
			pMob[i].NextY = pMob[i].m_krgPath[pMob[i].m_iPathProgress].y;

			int tret = PickFreeMobGrid( i, &pMob[i].NextX, &pMob[i].NextY );
			if( false == tret ) continue;

			MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
			sm.Effect = 3; // run
			GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);
		}
		else if( MOB_ROAM == mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	//Log("err standingby processer delete hp zero mob","-system",0);
				DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 160);
				continue;
			} 

			pMob[i].CheckAffections( CurrentTime );
			pMob[i].InitStatus();

			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )//if( (eTNVSAfn_Stun & pMob[i].m_iAffections) || (eTNVSAfn_Sleep & pMob[i].m_iAffections) )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}

			++pMob[i].m_iPathProgress;
			if( 0 <= pMob[i].m_iPathProgress  && eRoam_MaxPathCount > pMob[i].m_iPathProgress )
			{
				pMob[i].NextX = pMob[i].m_krgPath[pMob[i].m_iPathProgress].x;
				pMob[i].NextY = pMob[i].m_krgPath[pMob[i].m_iPathProgress].y;

				if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
				if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty )
				{
					pMob[i].m_iPathProgress = eRoam_MaxPathCount + 1;
					continue;
				}

				int tret = PickFreeMobGrid( i, &pMob[i].NextX, &pMob[i].NextY );
				if( false == tret ) continue;

				MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
				sm.Effect = 2; // run
				GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);
			}				
			else
			{
				if( eRoam_MaxPathCount < pMob[i].m_iPathProgress )
				{
					pMob[i].NextX = pMob[i].SegmentX;
					pMob[i].NextY = pMob[i].SegmentY;
					pMob[i].Mode = MOB_PEACE;

					pMob[i].Think( eTNAI_Return, 0 );
					int iDist = pMob[i].CalDistance2( pMob[i].SegmentX, pMob[i].SegmentY );
					if( (eConst_TooFarRange < iDist) )
						Teleport(i, pMob[i].NextX, pMob[i].NextY );
					else
					{
						int iMove = pMob[i].m_iMoveSpeed;
						if( 0 >= iMove ) iMove = 1;
						pMob[i].m_kLastTime.uiActivate = ((iDist - pMob[i].SegmentRange[pMob[i].SegmentProgress])/iMove + 5)*1000 + CurrentTime;
					}
				}
			}
		}
	}
	//   Battle이다
	div = SecCounter % SECBATTLE;	 // %2 -> 0 or 1
	//int iTic = SecCounter % (SECBATTLE*2);	// %4 -> 0,1,2,3
	int even = SecCounter % (SECBATTLE*2);	 
	if( div == even ) even = 1;
	else even = 0;

    for( i = MAX_USER + div; i < MAX_MOB; i += SECBATTLE )
	{	
		if( MAX_MOB <= i ) break; // 최대 mob 배열 index를 넘어가면 skip
        if( MOB_COMBAT == pMob[i].Mode )
		{
			if( 0 >= pMob[i].MOB.nHP )
			{	sprintf(temp,"err battleprocessor delete hp 0 idx:%d, leader:%d fol0:%d fol1:%d",i,pMob[i].Leader,pMob[i].m_irgParty[0],pMob[i].m_irgParty[1]);
				Log(temp,"-system",0);
				DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 170);
				continue;
			}

			//if( 0 == iTic) // 1초당 1회 수행, 0은 4tic당 1회 발생한다.
			if( even )
			{
				pMob[i].CheckAffections( CurrentTime );
				pMob[i].CheckCondition();
				pMob[i].CheckInvalidCombat();
			}

			if( eTNVSAfn_DontAttack & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}

			if( CurrentTime < pMob[i].m_uiActionLock ) continue;

			pMob[i].m_uiActionLock = 0;

			int iAllowedTargets = pMob[i].SelectSkill();
			if( eTNAT_Enemy == iAllowedTargets )
			{
				int ret	= pMob[i].BattleProcessor( even ); 
				int	rnd	= rand() % 100;

				if( 0x0020 & ret )      //  맙 삭제
				{	DeleteMob( i, 3, 0, eTNPrdt_RemoveNormal, 180 ); // 자폭
					continue;
				}

				//---------------------------------------------------------
				// Attack
				//---------------------------------------------------------
				if( eTNRA_Attack & ret )
				{	
					//if( eTNVSAfn_Invulnerable & pMob[i].m_iAffections ) continue;					
					pMob[i].m_iCantTraceTarget = 0;
					pMob[i].m_iTraceCount = 0;
					++pMob[i].m_iAttackCount;

					pMob[i].UseSkill();

					if( (eTNCls_Warrior == pMob[i].MOB.byClass1) && pMob[i].m_kWeaknessRate.Random() ) // 소환된 몬스터들은 weaken 상태가 되지 않는다.
					{// 4초 동안 weakness 상태에 걸리게 한다.						
						TNEFFECT kEffect;
						kEffect.iID = eTNAfn_Weakness;
						kEffect.iDuration = 4000;
						pMob[i].AddEffect( kEffect, i, i );

						pMob[i].BroadcastUpdateStatusMsg();
					}					
				}	

				//---------------------------------------------------------
				// Trace
				//---------------------------------------------------------
				if( eTNRA_Trace & ret )  // 추적
				{
					if( eTNAIO_NoTrace & pMob[i].m_iAIOption ) continue;//  추적하지 않는다.
					int tz= pMob[i].CurrentTarget;
					if( 0 >= tz || MAX_MOB <= tz ) continue;

					// 추적 포기 여부 검사
					if( eTNCls_Summoned != pMob[i].MOB.byClass1 )
					{// 일반 몬스터일 경우만, 추적 검사
						++pMob[i].m_iTraceCount;
						++pMob[i].m_iTotalTraceCount;
						if( eTNAI_TraceCount < pMob[i].m_iTraceCount )
						{
							if( 0 == pMob[i].m_iCantTraceTarget ) // 걸치기 여부 검사
							{
								int iDice = rand() % 100;
								if( iDice < pMob[i].m_iTraceCount ) // 추적 포기 기능
								{
									ret = ret | 0x0010;
									#ifdef __DYNAMIC_LOG__
									if( pMob[i].m_iDebugFlag )
									{
										char chBuf[256] = { 0,0,0, };
										sprintf(chBuf, "[NPC AI] 추적 포기> m_iTraceCount:%d, ret:%d, target의적수:%d \r\n", pMob[i].m_iTraceCount, ret, pMob[tz].m_iAttackerCount );
										pMob[i].Print( chBuf );
									}
									#endif
								}
								else pMob[i].Think( eTNAI_Trace, tz );
							}
						}

						if( 25 < pMob[i].m_iTotalTraceCount )
						{// guard일 경우, 일정 거리만 따라가고 너무 멀리가면 자신의 지역으로 바로 teleport한다.
							if( 2900 < pMob[i].MOB.snTribe && 2923 > pMob[i].MOB.snTribe )
							{							
								pMob[i].NextX = pMob[i].SegmentX;
								pMob[i].NextY = pMob[i].SegmentY;
								ret = ret | 0x0002;
							}
						}
					} // if( eTNCls_Summoned != pMob[i].MOB.byClass1 )

					pMob[i].UpdateSpeed();
					pMob[i].GetTargetPos( tz );

					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
					if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty ) continue;

					MSG_Action sm; GetAction( i, pMob[i].NextX, pMob[i].NextY, &sm );
					sm.Effect = 3;
					GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);

					pMob[i].m_uiActionLock = CurrentTime + 1000; // 1초 동안 대기 상태			
				}

				//---------------------------------------------------------
				// Return to Home
				//---------------------------------------------------------
				if( eTNRA_ReturnToHome & ret ) // 귀환
				{	
					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
					Teleport(i, pMob[i].NextX, pMob[i].NextY );
				}

				//---------------------------------------------------------
				// End to Combat
				//---------------------------------------------------------
				if( eTNRA_EndToCombat & ret ) // 전투 종료 -> 귀환
				{   
					if( eTNAIO_CombatOnly & pMob[i].m_iAIOption )
					{ // 전투만 하는 놈들은 전투 종료시에 죽어야 한다.
						//pMob[i].KillMonster( pMob[i].Leader, 16 ); // 모두 지속 시간을 가진다.
						KillMonster( i );
						continue;
					}

					int iTarget = pMob[i].CurrentTarget;
					if( 0 < iTarget && MAX_USER > iTarget )
					{
						if( pMob[iTarget].IsAlive() ) pMob[i].Think( eTNAI_GiveUpToTrace, iTarget );
					}

					pMob[i].InitStatus();
					pMob[i].CurrentTarget = 0;		
					pMob[i].LetsRoam();

					if( eTNAIO_GetCommand & pMob[i].m_iAIOption )					
					{
						pMob[i].Mode = MOB_PEACE;
						pMob[i].OnFollow( pMob[i].Leader );
						continue;
					}
				}
			} // if( eTNAT_Enemy == iAllowedTargets )
			else
			{
				pMob[i].UseSkill();
			}
		}
	}
}



void ProcessRobot()
{
	int i = 0;
	// NPC AI
	int div = SecCounter % (SECSTANDINGBY);	 // %8,  1~7로 2초(8/4)를 나타낸다.
	for	( i=ROBOT_START+div;i<ROBOT_END;i+=SECSTANDINGBY)  // User는 이하는 프로세스와 상관없기 때문에 MAX_USER + div 에서 시작한다 (div는 0일때도 있다.)
	{	
		if (i>=MAX_MOB) break;     // NAX_MOB이 8의 n승이면 이녀석이 빠진다.

		int mode = pMob[i].Mode;
		if( mode == MOB_EMPTY ) continue;

		//int clan = pMob[i].m_byClan;

		if( 0 >= pMob[i].MOB.nHP )
		{	//Log("err standingby processer delete hp zero mob","-system",0);
			DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 190);
			continue;
		}			


		// 2초에 한번 수행
		pMob[i].ForgetAttacker();
		pMob[i].CheckAffections( CurrentTime );//  magic-affect, every 2 sec
	
        if(mode == MOB_PEACE )
		{	
			pMob[i].CheckAffections( CurrentTime );
			//pMob[i].ForgetAttacker();
			pMob[i].InitStatus();
						
			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}			
		}
	}

	//   Battle이다
	div = SecCounter % SECBATTLE;	 // %2 -> 0 or 1
	//int iTic = SecCounter % (SECBATTLE*2);	// %4 -> 0,1,2,3
	int even = SecCounter % (SECBATTLE*2);	 
	if  (div==even) even = 1;
	else even = 0;
    for( i = ROBOT_START + div; i < ROBOT_END; i += SECBATTLE )
	{	
		if( i >= MAX_MOB ) break; // 최대 mob 배열 index를 넘어가면 skip
        if( MOB_COMBAT == pMob[i].Mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	sprintf(temp,"err battleprocessor delete hp 0 idx:%d, leader:%d fol0:%d fol1:%d",i,pMob[i].Leader,pMob[i].m_irgParty[0],pMob[i].m_irgParty[1]);
				Log(temp,"-system",0);
				DeleteMob(i,1, 0, eTNPrdt_RemoveNormal, 200);
				continue;
			}

			if( eTNVSAfn_DontAttack & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime;
				continue;
			}

			if( CurrentTime < pMob[i].m_uiActionLock ) continue;

			pMob[i].m_uiActionLock = 0;

			pMob[i].m_iSkillCharged = 100;
			int iAllowedTargets = pMob[i].SelectSkill2();
			if( eTNAT_Enemy == iAllowedTargets )
			{
				int ret	=	pMob[i].CheckCombat();
				int	rnd	=	rand()%100;
				if	(ret&0x0020)      //  맙 삭제
				{	DeleteMob(i,3, 0, eTNPrdt_RemoveNormal, 210); // 자폭
					continue;
				}
				if	(ret&0x10000) 
				{	// 이모션
					//if	(rand()%2==0) SendEmotion(i,14,1);
				}
				if	(ret&0x1000)  // 실제 전투 수행 부분
				{	
					pMob[i].UseSkill();
				}	

				if	(ret&0x0001)  // 추격
				{
					//if( eTNAIO_NoTrace & pMob[i].m_iAIOption ) continue; // 추적 불가 상태
					//if( 1 == pMonsterData[pMob[i].MOB.nTP].byQuest[eMonPrty_TraceCond] ) continue; // 추적 불가 상태
					int tz= pMob[i].CurrentTarget;
					if( 0 >= tz || MAX_MOB <= tz ) continue;

					pMob[i].UpdateSpeed();
					pMob[i].GetTargetPos(tz);

					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
					if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty ) continue;

					MSG_Action sm; GetAction( i, pMob[i].NextX, pMob[i].NextY, &sm );
					sm.Effect = 3;
					GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);

					pMob[i].m_uiActionLock = CurrentTime + 1000; // 1초 동안 대기 상태
					//pMob[i].m_uiActionLock = CurrentTime + pMob[i].m_uiActionDelay; // 1초 동안 대기 상태
					
				}  
				//if	(ret&0x0002)          
				//{	
				//	if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue;
				//	Teleport(i, pMob[i].NextX, pMob[i].NextY );
				//}  
				if(ret&0x0010) // 전투 종료 -> 귀환
				{   
					pMob[i].Mode = MOB_PEACE;

					pMob[i].InitStatus();
					pMob[i].CurrentTarget = 0;

					continue;
				}
			} // if( eTNAT_Enemy == iAllowedTargets )
			else
			{
				pMob[i].UseSkill();
			}
		}
	}
}





// 초타이머
void ProcessHourTimer( void )
{	
	g_RankSys.ReadRankFile(ServerGroup);		//	매시간 랭킹정보 갱신(실제 데이터는 하루에 한번 변경되고있다)
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//  로그 파일 관련 펑션 StartLog(), Log()
//
/////////////////////////////////////////////////////////////////////////////
/////
void StartLog(void)
{    
	 if (fLogFile!=NULL) fclose(fLogFile);
	 if (g_fpEvent!=NULL) fclose(g_fpEvent);
	 struct tm when; time_t now;
	 time(&now); when= *localtime(&now);
     sprintf(temp,".\\Log\\GAME%4.4d_%2.2d_%2.2d_%2.2d_%2.2d.txt",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec);
   	 fLogFile=fopen(temp,"wt");

#ifdef __EVENT_LOG_GENERATION_
	sprintf(temp,".\\EventLog\\GAME%4.4d_%2.2d_%2.2d_%2.2d_%2.2d.txt",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec);
	g_fpEvent=fopen(temp,"wt");
#endif

	 LastLogDay = when.tm_mday;
}		   
void CrackLog(int conn,char * str)
{ 
     if (conn>=0 && conn<MAX_MOB)
	 {  sprintf(temp,"clo mob:%d Account:%s Char:%s %s \n",conn, pUser[conn].AccountName, pMob[conn].MOB.szName, str);
	 }  else
     {  sprintf(temp,"clo mob:%d %s \n",conn, str);
	 }
	 Log(temp,"-system",0);
	 SetWindowText(hWndMain,temp);
}
void Log(char * str1,char * str2,unsigned int ip)
{	 
	 struct tm when;
	 time_t now;
	 time(&now); when= *localtime(&now);
	 char LogTemp[1024];
     sprintf(LogTemp,"%2.2d%2.2d%2.2d %2.2d%2.2d%2.2d %8.8x",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec,ip);
     //int size=strlen(LogTemp);LogTemp[size-1]=0;
     sprintf(LogTemp,"%s %s %s \n",LogTemp,str2,str1);
	 if (fLogFile)
	 {  fprintf(fLogFile,LogTemp);
	 }
	 SetWindowText(hWndMain,LogTemp);
	 //
	 //SendClientMessage(conn,str1);
	 //
}
void EventLog(char * strLog,char * strAccount,char* strCharName, unsigned int ip)
{	 
	 struct tm when;
	 time_t now;
	 time(&now); when= *localtime(&now);
	 char LogTemp[1024];
	 unsigned char cIP[4]; memcpy(cIP, &ip, sizeof(cIP));
     //sprintf(TimeIP,"%2.2d%2.2d%2.2d,%2.2d%2.2d%2.2d,%d.%d.%d.%d",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec,cIP[0],cIP[1],cIP[2],cIP[3]);
     //int size=strlen(LogTemp);LogTemp[size-1]=0;
     sprintf(LogTemp,"%04d%02d%02d,%02d%02d%02d,%d.%d.%d.%d,%s,%s,%s\n",when.tm_year+1900,when.tm_mon+1,when.tm_mday,
																		when.tm_hour,when.tm_min,when.tm_sec,
																		cIP[0],cIP[1],cIP[2],cIP[3],strAccount,strCharName,strLog);
	 if (g_fpEvent)
	 {  fprintf(g_fpEvent,LogTemp);
		fflush(g_fpEvent);
	 }
}
//  년월일 시분초 계정    타입   세부내용   
//  021212 235959 account login  etc
//  021212 235959 account logout etc
//  021212 235959 account get    etc  // 오리,락토,스크랩,유닉
//  021212 235959 account drop   etc  // 오리,락토,스크랩,유닉
//  021212 235959 account trade  etc  // 오리,락토,스크랩,유닉    item 4F3C000001010202 
//  021212 235959 account use    etc  // 오리,락토,페어리         success/fail used item
//  021212 235959 account admin  etc  // 어드민의 모든명령 

int GetUserFromSocket(int Sock)
{ 
	if ( Sock == 0 ) return 0;
	for (int i=1;i<MAX_USER;i++)
    {   if (pUser[i].cSock.Sock==(unsigned)Sock) return i;
	}
	
	return 0;
}
int GetEmptyUser(void)
{	
	for (int i=1;i<MAX_USER;i++)
	{   if (pUser[i].Mode == USER_EMPTY) return i;
	}
	
	return 0;
}
int GetEmptyItem(void)
{	
	for (int i=MAX_INITITEM;i<MAX_ITEM;i++)
	{   if (pItem[i].Mode == 0) return i;
	}
	
	return 0;
}

int GetEmptyNPCMob()
{
	//int iMaxCount = MAX_MOB - g_iFreeSlotForNPC;
	for (int i = g_iFreeSlotForNPC; i < MAX_MOB; ++i )
	{
		if( MAX_MOB <= i ) return 0;
		if( MOB_EMPTY == pMob[i].Mode ) return i;
	}
	return 0;
}


int GetUserByName(char *name)
{

    if (name[0]=='+')
	{  
		char *tname = name+1;
		strupr(tname);
    	for (int i=1;i<MAX_USER;i++)
		{   if (pMob[i].Mode==MOB_EMPTY) continue;
	        if (pUser[i].Mode!=USER_PLAY) continue;
		    if (!strcmp(tname,pUser[i].AccountName)) return i;
		}
        return 0;

	}

	for (int i=1;i<MAX_USER;i++)
	{   if (pMob[i].Mode==MOB_EMPTY) continue;
	    if (pUser[i].Mode!=USER_PLAY) continue;
		if (!strcmp(name,pMob[i].MOB.szName)) return i;
	}
	return 0;
}
BOOL IsImple(int user)
{
     //if (pUser[user].Mode!=USER_PLAY && pUser[user].Mode!=USER_PLAYTOWN) return FALSE;
	//int WizardLevel = pMob[user].MOB.Score[ESC_FAME] - WIZARD_FAME+10;
	 //if (WizardLevel<0) return FALSE;
	 //return WizardLevel;
	return 0; // User에 Wizard flag를 넣자.
}

void CloseUser(int conn)
{
	if	(conn<0||conn>MAX_MOB)
	{	CrackLog(conn," SaveAndQuitMobidx");
		return;
	}

	pMob[conn].DropKalaCore();
	pMob[conn].ClearActivity();
	pMob[conn].ClearProperty();

	if( USER_PLAY == pUser[conn].Mode )
	{
		int nTarget = pUser[conn].Trade.OpponentID;
		if(nTarget>0 && nTarget<MAX_USER)		//	거래중인 대상이 존재할경우 거래취소를 보내준다.
		{	RemoveTrade(nTarget, REPLY_TRADE_USER_DENAY);
			memset(&(pUser[conn].Trade), 0, sizeof(pUser[conn].Trade));
		}

		RemoveChallenge(conn, eChallenge_System);									//	결투모드를 초기화한다
		RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_DISCONNECT);//	현재 길드연합 요청대상이 있다면 취소한다.

		for( int iFollowerIndex = 0; iFollowerIndex < eFollower_MaxCount; ++iFollowerIndex )
		{
			int iFollower = pMob[conn].m_irgFollower[iFollowerIndex];
			if( MAX_USER <= iFollower && MAX_MOB > iFollower ) KillMonster( iFollower ); //pMob[iFollower].MOB.nHP = 0;
		}

		if( 0 < pMob[conn].MOB.nHP )
		{
			if( eWaitAct_Quit == pMob[conn].m_kWaitAction.iAction )
			{
				if( pMob[conn].m_kWaitAction.uiWaitingTime > CurrentTime ) return;
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
			}
			else if( eWaitAct_ZonePortal == pMob[conn].m_kWaitAction.iAction ) // zone portal을 이용하기 위해, disconnect 하는 경우, ...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0;
				#ifdef __TN_5TH_LOG__
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "[CloseUser] ZonePortal> %s, time:u, action:%d \r\n", pMob[conn].MOB.szName, CurrentTime, pMob[conn].m_kWaitAction.iAction );
					WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]CloseUser.txt" );
				}
				#endif // __TN_5TH_LOG__
			}
			else if( eWaitAct_ServerDown == pMob[conn].m_kWaitAction.iAction ) // Server Down시...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0;
			}
			else if( eWaitAct_Kickout == pMob[conn].m_kWaitAction.iAction ) // Server Down시...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0;
			}
			else
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Quit;
				pMob[conn].m_kWaitAction.uiWaitingTime = CurrentTime + g_irgSetting[eCnst_QuitTime]; //eWaitTime_Quit;

				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_ProtectFromMonster;
				kEffect.iDuration = g_irgSetting[eCnst_QuitTime] + 60000;
				pMob[conn].AddEffect( kEffect, conn, conn );
				
				#ifdef __TN_5TH_LOG__
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "[CloseUser] ZonePortal> %s, time:u, action:%d \r\n", pMob[conn].MOB.szName, CurrentTime, pMob[conn].m_kWaitAction.iAction );
					WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]CloseUser.txt" );
				}
				#endif // __TN_5TH_LOG__
				return;
			}
		}
	}

	int nCount=0; int nGuildIndex = GetGuild(pMob[conn].MOB.nGuildID, FLAG_CLOSE);
	if(nGuildIndex==-1)	//	길드정보가져오기 실패
	{	char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[CloseUser] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID );
		Log(chBuf,pUser[conn].AccountName,pUser[conn].IP);
	}
	if(nGuildIndex>0 && nGuildIndex<MAX_USER)
	{	for(int i=0;i<MAX_GUILD_MEMBER;i++)
		{	if(conn==pGuild[nGuildIndex].pMemberIndex[i]) pGuild[nGuildIndex].pMemberIndex[i]=0; 
			if(pGuild[nGuildIndex].pMemberIndex[i]!=0) nCount++;
		}
		if(nCount==0) pGuild[nGuildIndex].Initialize();
	}
	
	pUser[conn].Admin=0;
	pUser[conn].byTradeMode=0;		//	trade mode 해제(안하면 메세지 처리부분에서 바로 리턴된다)
	pUser[conn].LoginTime=0;
	if	(pUser[conn].IsBillConnect)  {SendBilling(conn,pUser[conn].AccountName,2,0); pUser[conn].IsBillConnect=0;}
	pUser[conn].TickDiff=0;
	pUser[conn].cSock.CloseSocket();
	//pMob[conn].Mode = MOB_EMPTY; // 일단 비워 놓지만, USER가 Empty가 아니기 때문에 Save전에 밀릴 염려는 없다.

	// 일단 소켓은 반드시 끊는다.

	// 모드 12에서 종료한경우 슬롯이 닫히지 않았음. << DB가 컨펌을 안준것 같음>> 수정요망

	int mode = pUser[conn].Mode;
    if (mode == USER_EMPTY || mode == USER_ACCEPT )
	{  pUser[conn].CloseUser();
	   return;
	}
	// 이경우는 Mob을 꼭 DB에 저장한 에만 Quit이 가능하다.
	// SAVING4QUIT의 경우 pUser의 sock은 이미 Invalid이다.
    // SAVING4QUIT에서 다시 CloseUser가 온경우, 처리하지 않는다.
    // SAVING4QUIT 메시지가 먹은 경우는 게임서버 타이머가 재 전송 저장 처리한다.
    if (mode == USER_PLAY|| mode == USER_SAVING4QUIT)
	{  
		if (mode == USER_PLAY)   CharLogOut(conn);
		// *CharLogout include following*
	    RemoveParty(conn, conn);

		//	길드원에게 나의 접속종료을 알린다.
		MSG_GuildMemberout nm;	nm.wType=_MSG_GuildMemberout;
		nm.GuildID = pMob[conn].MOB.nGuildID;
		nm.wPDULength = sizeof(nm) - sizeof(HEADER);
		strncpy(nm.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
		//DBServerSocket.SendOneMessage((char*)&nm, sizeof(nm));	//	차후 클라이언트구현후 살린다.
		SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*)&nm);
		//int trade=pUser[conn].Trade.OpponentID;
		//if (trade>0 && trade<MAX_USER)
		//{  if (pUser[trade].Mode==USER_PLAY && pUser[trade].Trade.OpponentID==conn) RemoveTrade(trade);
		//}
		//pUser[conn].Trade.OpponentID = 0;

		//	저장아이템 점검
		int nItemIndex=0; short snType; BOOL bRes=true;
		for(int i=0; i<pMob[conn].byMaxInven; i++)
		{	if(pMob[conn].MOB.Inven[i].snIndex==0) continue;
			nItemIndex=pMob[conn].MOB.Inven[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
			{	//memset(&(pMob[conn].MOB.Inven[i]), 0, sizeof(STRUCT_ITEM));
				char chLog[256]={0,};
				sprintf(chLog,"err Invalid itemindex char:%s itemindex:%d place:%d index:%d",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_INVEN,i);
				Log(chLog,pUser[conn].AccountName,pUser[conn].IP);
				bRes=false;
			}
		}
		for(i=0; i<MAX_EQUIP; i++)
		{	if(pMob[conn].MOB.Equip[i].snIndex==0) continue;
			nItemIndex=pMob[conn].MOB.Equip[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
			{	//memset(&(pMob[conn].MOB.Equip[i]), 0, sizeof(STRUCT_ITEM));
				sprintf(temp,"err Invalid itemindex char:%s itemindex:%d place:%d index:%d",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_EQUIP,i);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				bRes=false;
			}
		}
		for(i=0; i<MAX_CARGO; i++)
		{	if(pUser[conn].Cargo[i].snIndex==0) continue;
			nItemIndex=pUser[conn].Cargo[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(!g_ParamMgr.HT_bGetItemType(nItemIndex, &snType))
			{	//memset(&(pUser[conn].Cargo[i]), 0, sizeof(STRUCT_ITEM));
				sprintf(temp,"err Invalid itemindex char:%s itemindex:%d place:%d index:%d",pMob[conn].MOB.szName,nItemIndex,ITEM_PLACE_CARGO,i);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				bRes=false;
			}
		}

		if(ServerIndex==(SERVER_KRUMA_HIGH-1) || ServerIndex==(SERVER_KRUMA_LOW-1) )
		{
			if(pMob[conn].MOB.byLevel<TRIMURITY_LEVEL_LOW) 
			{	pMob[conn].MOB.byZone=1; pMob[conn].MOB.snX=-1; pMob[conn].MOB.snZ=-1;
			}
		}

		if( eZone_Stronghold == g_iZoneID )
		{
			if( (50 < pMob[conn].TargetX) && (570 > pMob[conn].TargetX) && (448 < pMob[conn].TargetY) && (958 > pMob[conn].TargetY) );
			else
			{
				pMob[conn].MOB.byZone=eZone_Stronghold; pMob[conn].MOB.snX=-1; pMob[conn].MOB.snZ=-1;
			}
		}

		//	칼리아던전(저,중,고랩), 차투랑가에서 접속 종료시 주신전에서 태어나도록 세팅한다.
		if((ServerIndex+1)==SERVER_KALIA_LOW || (ServerIndex+1)==SERVER_KALIA_MIDDLE || (ServerIndex+1)==SERVER_KALIA_HIGH || (ServerIndex+1)==SERVER_CHATURANGKA)
		{	
			pMob[conn].MOB.byZone=pMob[conn].MOB.bySaveZone; 
			pMob[conn].MOB.snX=pMob[conn].MOB.snSaveX; pMob[conn].MOB.snZ=pMob[conn].MOB.snSaveZ;
		}	else
		if((ServerIndex+1)==SERVER_KRUMA_LOW)	//	차크라합이 355보다 크거나 스킬포인트가 63보다 클시에는 저랩크루마지역에 출입불가 - 만다라마을로 이동(2005.11.25)
		{
			short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
			short snSkill  = pMob[conn].MOB.byLevel;
			if(eTNCls_2nd < pMob[conn].MOB.byClass1) snSkill += (((snSkill-35)/10)*2);

			if(pMob[conn].MOB.byLevel>=TRIMURITY_LEVEL_HIGH || snChakra>355 || snSkill>63) 
			{	pMob[conn].MOB.byZone=1; 
				pMob[conn].MOB.snX=-1; pMob[conn].MOB.snZ=-1;
			}
		}

		pMob[conn].MOB.byDecPranaRate = pMob[conn].m_byDecPranaRate;
		pMob[conn].MOB.byKillLevel = pMob[conn].m_byKillLevel;

		S_SSP_REQ_SAVE_QUIT sm;  sm.wType= SSP_REQ_SAVE_QUIT;
		sm.nID	= conn;
		sm.MOB = pMob[conn].MOB;
		memcpy(sm.Cargo,pUser[conn].Cargo,sizeof(sm.Cargo));
		memcpy(sm.dwTimeStamp, pUser[conn].m_time, sizeof(sm.dwTimeStamp));
		strncpy(sm.AccountName,pUser[conn].AccountName,ACCOUNTNAME_LENGTH);
		sm.Coin = pUser[conn].Coin; 
 
		if(DBServerSocket.SendOneMessage((char*)&sm,sizeof(S_SSP_REQ_SAVE_QUIT))==FALSE)
		{	sprintf(temp,"err SSP_REQ_SAVE_QUIT DB-SEND %d, %s",conn,pMob[conn].MOB.szName);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);
		}
		// SendDBLogoutSaveMob(conn);
		pUser[conn].Mode = USER_SAVING4QUIT;
		sprintf(temp,"logout char%s: positionX:%d positionZ:%d rupiah:%d cargo:%d prana:%d hp:%d", pMob[conn].MOB.szName, pMob[conn].MOB.snX, pMob[conn].MOB.snZ, pMob[conn].MOB.nRupiah, pUser[conn].Coin, pMob[conn].MOB.nPrana, pMob[conn].MOB.nHP);
		Log(temp,pUser[conn].AccountName,pUser[conn].IP);
		fflush(fLogFile);

		//	Send Billing Message
		if(pUser[conn].IsBillConnect==1) SendBilling(conn,pUser[conn].AccountName,2,1);
		//char chBuf[256] = {0,};
		//sprintf(chBuf, "logout char%s: positionX:%d positionZ:%d  \r\n",pMob[conn].MOB.szName, pMob[conn].MOB.snX, pMob[conn].MOB.snZ);
		//TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Position.txt" );

		//DeleteMob(conn,2, 0, eTNPrdt_RemoveNormal, 220);
		return;
	}  else
	{  MSG_STANDARD sm; sm.wType = _MSG_DBNoNeedSave;
       sm.nID=conn;
	   if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(MSG_STANDARD)))
	   {	Log("err DBNoNeedSave DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
	   }
	   pMob[conn].Mode=MOB_EMPTY;
	   pUser[conn].CloseUser();
	}
}

BOOL ReadMob(STRUCT_MOB * mob,char * Directory)
{
	int iID = atoi( mob->szName );
	//mob->snTribe = (short)iID;
	//mob->nBramanPoint = iID - HT_PARAMTYPE_MONSTER_START + 1;
	if(iID<2000 || iID>=(MAX_MONSTER_DATA+2000)) return FALSE;
	memcpy( mob, &pMonsterData[iID - 2000], sizeof(STRUCT_MOB) );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////
//
//  Message Sender
//
//////////////////////////////////////////////////////////////////////////////////




//------------------------------------------------------------------
//
//@Param
//	- a_iReason  1:killed, 2:logout, 3:sucide, 5:teleport(out)
//  - a_byProductionType : 죽을 때의 연출 번호, 0:죽는 애니 or 사라짐, 1:펑하는 FX와 함께 사라짐
//------------------------------------------------------------------
void DeleteMob( int mob, int a_iReason, int a_iKiller, byte a_byProductionType, int a_iCaller )
{  
	if( 0 > mob || MAX_MOB <= mob ) return;
	if( 0 > a_iKiller || MAX_MOB <= a_iKiller ) a_iKiller = 0;
	S_SCP_RESP_REMOVE_MOB sm; sm.wType = SCP_RESP_REMOVE_MOB; 
	sm.nID=mob; sm.byResult =a_iReason;sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
	sm.dwKillerID = a_iKiller;
	sm.byRemoveType = a_byProductionType;
	sm.snTribe = pMob[a_iKiller].MOB.snTribe;
	strcpy( sm.szName, pMob[a_iKiller].MOB.szName );
	if( 0 < mob && MAX_USER > mob )
	{
		GridMulticast( pMob[mob].TargetX, pMob[mob].TargetY, (MSG_STANDARD*)&sm, -1);
	}
	else GridMulticast(pMob[mob].TargetX,pMob[mob].TargetY,(MSG_STANDARD*)&sm, mob);

	#ifdef __DYNAMIC_LOG__
	if( eTNMob_PC != pMob[mob].m_eMobType )
	{
		if( pMob[mob].m_iDebugFlag )
		{
			//SYSTEMTIME st;
			//GetLocalTime( &st );

			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[DeleteMob] %dyy%dmm%ddd %dhh%dms%dss > Mob(H:%d, Tribe:%d), Reason:%d, Killer:%d, Prdt:%d \r\n"
				, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				, mob, pMob[mob].MOB.snTribe, a_iReason, a_iKiller, a_byProductionType
				);
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
		}
	}
	#endif //__TN_4TH_LOG__


	if( 0 != a_iReason ) 
	{  
		pMob[mob].Mode = MOB_EMPTY;

		if( mob != pMobGrid[pMob[mob].TargetY][pMob[mob].TargetX] )		//	비정상적인 경우
		{
			char chBuf[256] = { 0,0,0, };
			sprintf( chBuf, "mob %d is not located in his position(%d,%d). \n", mob, pMob[mob].TargetX, pMob[mob].TargetY );
			WriteLog( chBuf, ".\\Monster_Log\\[Log]InvalidMobGrid.txt" );

			bool bFlag = false;
			for(int y=0; y<MAX_GRIDY; y++)
			{
				for(int x=0; x<MAX_GRIDX; x++)
				{
					if(pMobGrid[y][x] == mob)
					{
						pMobGrid[y][x] = 0;

						GridMulticast( x, y, (MSG_STANDARD*)&sm, -1);
						bFlag = true;
						break;
					}
				}
				if( bFlag ) break;
			}
		}	
		else															//	정상적일 경우
			pMobGrid[pMob[mob].TargetY][pMob[mob].TargetX] = 0;

		//RemoveParty(mob, mob);

		//if( (MAX_USER <= mob) && (eTNCls_Warrior == pMob[mob].MOB.byClass1) )  // static한 NPC의 경우
		if( MAX_USER <= mob )
		{	
			int	idx=pMob[mob].GenerateIndex;
			int iIndex = pMob[mob].m_irgMobListIndex[0];
		    if	(idx>=0 && idx<MAX_NPCGENERATOR)
			{	
				--mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount;
				if(mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount<0) mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount=0;
			}
		}
	 }
}


void  SaveUser(int conn,int export)
{
	MSG_DBSaveMob sm;  sm.wType= _MSG_DBSaveMob;
	sm.MOB = pMob[conn].MOB;
	sm.Slot = pUser[conn].Slot;
	memcpy(sm.Cargo,pUser[conn].Cargo,sizeof(sm.Cargo));
	sm.Coin = pUser[conn].Coin;
	sm.nID=conn;
	sm.Export = export;
	memcpy(sm.dwTimeStamp, pUser[conn].m_time, sizeof(sm.dwTimeStamp));
	strncpy(sm.AccountName,pUser[conn].AccountName,ACCOUNTNAME_LENGTH);
	if(DBServerSocket.SendOneMessage((char*)&sm,sizeof(MSG_DBSaveMob))==FALSE)
	{	sprintf(temp,"err SaveUser %d, %s",conn,pMob[conn].MOB.szName);
		Log(temp,pUser[conn].AccountName,pUser[conn].IP);
	}
}

void  CharLogOut(int conn)
{
	if	(pUser[conn].Mode!=USER_PLAY) 
	{	Log("err char logout - not user_play",pUser[conn].AccountName,pUser[conn].IP);
		SendClientSignal(conn,conn,_MSG_CNFCharacterLogout);
		return;
	}   

	//	Messenger Logout
	MSG_MessengerLogout	mm; mm.wType=_MSG_MessengerLogout;
	mm.nID=conn; mm.nServerIndex=ServerIndex;
	mm.nSlot=pUser[conn].Slot; mm.nGuildID=pMob[conn].MOB.nGuildID;
	strncpy(mm.CharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	strncpy(mm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
	MSGServerSocket.AddMessage((char*)&mm, sizeof(mm));
   
	//if	(pUser[conn].IsBillConnect && CHARSELBILL==0)  {SendBilling(conn,pUser[conn].AccountName,2,0);}

	//int trade=pUser[conn].Trade.OpponentID;
	//if (trade>0 && trade<MAX_USER)
	//{  if (pUser[trade].Mode==USER_PLAY && pUser[trade].Trade.OpponentID==conn) RemoveTrade(trade);
	//}

	pUser[conn].Mode = USER_EMPTY; 
	DeleteMob(conn,2, 0, eTNPrdt_RemoveNormal, 230); 

	//	차투랑가에서 접속종료시 저장장소에서 리젠이 이루어져야 한다.
	if(pMob[conn].MOB.nHP>0)
	{
		if(ServerIndex+1==SERVER_STRONGHOLD)
		{
			bool bRet=true;
			DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
			bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_Front, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );
			if(!bRet)
			{	pMob[conn].MOB.byZone = SERVER_SHAMBALA;
				pMob[conn].MOB.snX = -1;
				pMob[conn].MOB.snZ = -1;
			}
			else
			{	pMob[conn].MOB.byZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
				pMob[conn].MOB.snX = GetRandom(snStartX, snEndX);
				pMob[conn].MOB.snZ = GetRandom(snStartZ, snEndZ);
			}
		}
		else if(ServerIndex+1==eZone_Katacomb)				//	북두성군방에서 재접시 시작지점으로 보낸다.
		{	int nX = pMob[conn].TargetX; int nY = pMob[conn].TargetY;
			if( ((66 <= nX && 166 >= nX) && (76 <= nY && 168 >= nY ))
				|| ((168 <= nX && 202 >= nX) && (74 <= nY && 96 >= nY ))
				|| ((346 <= nX && 458 >= nX) && (188 <= nY && 278 >= nY ))

				|| ((856 <= nX && 954 >= nX) && (74 <= nY && 166 >= nY ))
				|| ((824 <= nX && 856 >= nX) && (74 <= nY && 96 >= nY ))
				|| ((564 <= nX && 682 >= nX) && (188 <= nY && 278 >= nY ))
				) GetTrimurityArea(conn, nX, nY);
	/*
	66.76 ~ 166.168
	168.74 ~ 202.96
	346.188 ~ 458.278

	856.74 ~ 954.166
	824.74 ~ 856.96
	564.188 ~ 682.278
	*/

			pMob[conn].MOB.snX = nX;
			pMob[conn].MOB.snZ = nY;
		}
		else
		{	pMob[conn].MOB.byZone = ServerIndex+1;
			pMob[conn].MOB.snX = pMob[conn].TargetX;
			pMob[conn].MOB.snZ = pMob[conn].TargetY;
		}
	}
	else	//	사망시
	{
		pMob[conn].MOB.byZone = ServerIndex+1;
		pMob[conn].MOB.snX = pMob[conn].TargetX;
		pMob[conn].MOB.snZ = pMob[conn].TargetY;
	}

	sprintf(temp,"logout char:%s lev:%d x:%d y:%d rupiah: %d, cargo: %d, prana: %d, bramanp: %d, class(%d,%d)"
		,pMob[conn].MOB.szName,pMob[conn].MOB.byLevel,pMob[conn].TargetX,pMob[conn].TargetY,pMob[conn].MOB.nRupiah, pUser[conn].Coin, pMob[conn].MOB.nPrana, pMob[conn].MOB.nBramanPoint, pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
	Log(temp,pUser[conn].AccountName,pUser[conn].IP);

	pMob[conn].Mode    = MOB_EMPTY;


	//SendClientSignal(conn,conn,_MSG_CNFCharacterLogout);
}


void Reboot()
{    
	
     for (int y=0;y<MAX_GRIDY;y++)
	 {	 for (int x=0;x<MAX_GRIDX;x++)
		 {   pMobGrid   [y][x]=0;
             pItemGrid  [y][x]=0;
             //pHeightGrid[y][x]=0;
		 }
	 }
//	BASE_InitializeMobname("MobName.txt",0);
//#ifdef _CHINESESIMPLE
//	BASE_InitializeMobname("MobName_cs.txt",1);
//#elif _CHINESETRADITION
//	BASE_InitializeMobname("MobName_ct.txt",1);
	 //#endif
	BASE_InitializeBaseDef(g_eCountryID);
	mNPCGen.ReadNPCGenerator();
	mNPCGen.VerifyData();
	mNPCGen.RebuildAreaData();
	g_RefineTable.Initialize();
	g_QuestTable.Initialize();

	//int Handle = _open( "./heightmap.dat", _O_RDONLY | _O_BINARY, NULL);
	//if (Handle==-1)
	//{  Log("err Load height grid fail","-system",0);
	//   return;
	//}
  //   _read(Handle,(void*)&pHeightGrid,sizeof(pHeightGrid));
	 //_close(Handle);

 	
    //BASE_ApplyAttribute((char*)pHeightGrid,MAX_GRIDX); 

	

	#ifdef _CHINESESIMPLE 
		BASE_InitializeMessage("Language_cs.txt");
	#elif _CHINESETRADITION
		BASE_InitializeMessage("Language_ct.txt");
	#else
		BASE_InitializeMessage("Language.txt");
	#endif

	//mSummon.Initialize();
	Log("ser start server","-system",0);
	
}

/*
// NPC인 mob에게  enemy를 적으로 등록시킴, (색적후)
void SetBattle(int mob,int enemy)
{
	// 자신과 자신의 그룹에게 enemy를 등록. => 자신에게만 enemy를 등록.
	if (mob<=0 || enemy<=0|| mob>=MAX_MOB || enemy>=MAX_MOB) return;

	if (pMob[mob].Mode==MOB_EMPTY) return;
	if (pMob[enemy].Mode==MOB_EMPTY) return;
	if (mob<MAX_USER && pUser[mob].Mode!=USER_PLAY) return;

	if( eTNMob_PC != pMob[mob].m_eMobType )
	{
		int iRadius = pMob[mob].m_byBodyRadius + pMob[mob].m_kSight.sCombat;
		int dx1 = pMob[mob].TargetX - iRadius;
		int dy1 = pMob[mob].TargetY - iRadius; 
		int dx2 = pMob[mob].TargetX + iRadius;
		int dy2 = pMob[mob].TargetY + iRadius;
		if( pMob[enemy].TargetX < dx1 || pMob[enemy].TargetX > dx2 || pMob[enemy].TargetY < dy1 || pMob[enemy].TargetY > dy2 )
		{
			#ifdef __TN_4TH_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[SetBattle] 적이 시야 밖에 있음> 자신(%d,Tribe:%d) L(%d,%d), 적(%d,Tribe:%d) L(%d,%d), 공격시야:%d, 공격허용영역(%d,%d, %d,%d) \r\n", mob, pMob[mob].MOB.snTribe, pMob[mob].TargetX, pMob[mob].TargetY, enemy, pMob[enemy].MOB.snTribe, pMob[enemy].TargetX, pMob[enemy].TargetY, pMob[mob].m_kSight.sCombat, dx1, dy1, dx2, dy2 );
				WriteLog( chBuf, ".\\monster_log\\[Log]Combat.txt" );
			}
			#endif // __TN_4TH_LOG__

			return;
		}
	}

	pMob[mob].Mode=MOB_COMBAT;
	pMob[mob].AddEnemyList(enemy); 
}
*/

int CreateItem(int& x, int& y, STRUCT_ITEM *sour,  int nWho, DWORD dwMoney, int a_iParty, unsigned int a_uiReleaseTime )
{
	if( NULL == sour ) return 0;
	if( 0 >= sour->snIndex || MAX_ITEM_DATA <= sour->snIndex ) return 0;

	GetEmptyItemGrid(&x,&y);  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.

    if (pItemGrid[y][x]) return 0;
    int destidx = GetEmptyItem();
    if (destidx==0) return 0;
	
    pItem[destidx].Mode=TRUE;
	pItem[destidx].PosX = x;
	pItem[destidx].PosY = y;
    pItem[destidx].ITEM = * sour;
    pItem[destidx].Rotate = 0;	
    pItem[destidx].State = STATE_OPEN;
	pItem[destidx].Delay = 0;
	pItem[destidx].Decay = pItemData[sour->snIndex].byDecay;
    pItem[destidx].GridCharge = 0;			//BASE_GetItemAbility(sour,EF_GROUND);
    pItem[destidx].Height = 0;				//HeightGrid[y][x];
	pItem[destidx].m_iOwner = a_iParty;
	pItem[destidx].m_uiReleaseTime = a_uiReleaseTime;
	pItem[destidx].Money = dwMoney;
	pItem[destidx].ITEM.byDummy = 0;
	pItem[destidx].ITEM.wSerial = GetRandom(0, 65535);		//	추후 시리얼넘버 대상아이템 정해지면 추가하기로 함.

	pItemGrid[y][x]=destidx;				// ItemGrid에는 IDX_ITEM이 더해지지 않은 어레이 인덱스가 온다.

	/*
	int iID = pItemData[sour->snIndex].sID;
	if( (eKalaCore_Brahma == iID) || (eKalaCore_Vishnu == iID) || (eKalaCore_Siva == iID) )
	{		
		for( int i = 0; i < eKala_MaxCount; ++i )
		{
			if( 0 == g_krgKalaGround[i].x && 0 == g_krgKalaGround[i].y )
			{
				g_krgKalaGround[i].iHandle = iID;
				g_krgKalaGround[i].x = x;
				g_krgKalaGround[i].y = y;
				break;
			}
		}
	}
	*/

    S_SCP_MAP_ITEM_APPEAR sm; 
	GetCreateItem(destidx,&sm); sm.nMobIndex = nWho;
    GridMulticast(x,y,(MSG_STANDARD*)&sm,0);
    return destidx;
}

void RemoveTrade(int target, int nError)
{
	// 1:1거래 취소
	
	if	(target>0 && target<MAX_USER)
	{
		memset(&(pUser[target].Trade),0,sizeof(pUser[target].Trade));
		for (int l=0;l<MAX_TRADE;l++) pUser[target].Trade.InvenPos[l]=-1;
		//memset(&pUser[target].AutoTrade,0,sizeof(pUser[target].AutoTrade));
		//for	(   l=0;l<MAX_AUTOTRADE;l++) pUser[target].AutoTrade.CarryPos[l]=-1;

		if (pUser[target].Mode!=USER_PLAY) return;

		S_RESULT sm; sm.wType = SCP_RESP_TRADE_CANCEL;
		sm.nResult = nError;
		pUser[target].cSock.SendOneMessage((char*)&sm, sizeof(S_RESULT));
		//if	(pUser[target].TradeMode)
		//{
		//	int ttx = pMob[target].TargetX;
		//	int tty = pMob[target].TargetY;
		// 	MSG_CreateMob sm;
		//	GetCreateMob(target,&sm); //sm.CreateType = sm.CreateType | 2;
		//	GridMulticast(ttx,tty,(MSG_STANDARD*)&sm,0);
		//	pUser[target].TradeMode=0;
		//}
	}
}

void RemoveParty( int conn, int Target )
{
	if(conn<0 && conn>=MAX_USER && Target<0 && Target>=MAX_USER) return;
	//	파티탈퇴
	int leader = pMob[Target].Leader;
	if  (leader<0||leader>=MAX_MOB)
	{   Log("err RemoveParty but worng leader",pUser[Target].AccountName,pUser[conn].IP);
	    return;
	}
	if(leader==0) leader=Target;

	SendRemoveParty(Target, 0);  // 자신에게 파티탈퇴를 알린다.

	pMob[leader].m_iLinker = 0; // 우마사마테 스킬을 초기화 시켜준다.
	for (int i=0;i<MAX_PARTY;++i)
	{
		int fol = pMob[leader].m_irgParty[i];
	   	if( 0 >= fol || MAX_USER <= fol ) continue;
		pMob[fol].m_iLinker = 0;
	}

	if  (Target!=leader)							// 내가 리더가 아닐때.
	{	SendRemoveParty(leader, Target);
        pMob[Target].Leader=0;
		bool bSolo = true;
		for (int i=0;i<MAX_PARTY;i++)
		{   int fol = pMob[leader].m_irgParty[i];
	   	  	if  (fol==0) continue;
	        if  (fol==Target) 
			{	memcpy(&(pMob[leader].m_irgParty[i]), &(pMob[leader].m_irgParty[i+1]), sizeof(int)*(MAX_PARTY-i-1));
				pMob[leader].m_irgParty[MAX_PARTY-1] = 0;
				fol = pMob[leader].m_irgParty[i];
			}
			if  (fol>0 && fol<MAX_USER) SendRemoveParty(fol, Target);
		}
        return;
	}

	leader = pMob[Target].m_irgParty[0];			// 이하는 내가 리더일때(새로운 리더를 선정하고 세팅한다)
	memcpy(pMob[leader].m_irgParty, &(pMob[Target].m_irgParty[1]), sizeof(int)*(MAX_PARTY-1));
	pMob[leader].Leader = 0; pMob[leader].byRootingMode = pMob[Target].byRootingMode;
	pMob[Target].byRootingMode = ROOTING_PERSON;	// 파티장이 탈퇴시 루팅모드는 개인루팅모드로 된다

	//	파티장에게 파티장승계와 로그아웃파티원정보를 알린다.
	SendRemoveParty(leader, Target);

	bool bSolo = true;
	//	파티원에게 새로운 파티장과 로그아웃파티원정보를 알린다.
 	for (int i=0;i<MAX_PARTY;i++)
	{   int fol = pMob[leader].m_irgParty[i];
   	  	if  (fol<=0||fol>MAX_MOB) continue;
		pMob[fol].Leader = leader; 
		if (fol<MAX_USER) { SendRemoveParty(fol, Target); bSolo = false; }
	}

	if(bSolo) pMob[leader].byRootingMode = ROOTING_PERSON;
	ZeroMemory(pMob[Target].m_irgParty, sizeof(int)*MAX_PARTY);
}

void RemoveAlliance(int target, int error)
{
	if	(target>0 && target<MAX_USER)
	{
		if (pUser[target].Mode!=USER_PLAY) return;

		Msg_GuildAlliance nm; nm.wType = _Msg_GuildAlliance;
		nm.nID = pUser[target].m_nAllianceUser; nm.byResult = error;
		nm.byType = eGuildFriend; nm.byAct = eGuildAllianceIn;
		pUser[target].cSock.SendOneMessage((char*)&nm, sizeof(nm));

		pUser[target].m_nAllianceUser = 0;
		pUser[target].m_byAllianceMode = 0;
	}
}

extern int g_pGroundMask[MAX_GROUNDMASK][4][6][6];

void DoRecall(int target)
{
	int x = pMob[target].MOB.snX;
	int y = pMob[target].MOB.snZ;

	int tret = GetEmptyMobGrid(target,&x,&y);
	MSG_Action sm;  GetAction(target,x,y,&sm);	 sm.Effect = 5;
	if (target<MAX_USER) pUser[target].cSock.AddMessage((char*)&sm,sizeof(sm));
    GridMulticast(target,x,y,(MSG_STANDARD*)&sm);
    return;
}

// 땅에 아이템 썪는거
void ProcessDecayItem(void)
{    
	 for (int i=0;i<DecayValue;i++)  // 2회. 2개씩 Decay 처리를 한다.
	 {
	    ItemCount++;
        if (ItemCount>=MAX_ITEM) ItemCount = g_dwInitItem+1;
	    if (pItem[ItemCount].Mode==FALSE) continue;
		if (eItm_Permenent == pItem[ItemCount].Decay )
		{
			char szMsg[1024] = { 0,0,0, };
			sprintf( szMsg, g_pMessageStringTable[_Post_Item_Location], pItem[ItemCount].PosX, pItem[ItemCount].PosY );
			PostMessageToZone( szMsg );

			continue;
		}
		if (eItm_Decay == pItem[ItemCount].Decay) {pItem[ItemCount].Decay=1; continue;}
    
		// 이제 지우고 Multicast 하는 부분.
	    int GridX = pItem[ItemCount].PosX;
        int GridY = pItem[ItemCount].PosY;
	    memset(&(pItem[ItemCount].ITEM),0,sizeof(STRUCT_ITEM));
		SendItemDisappear(GridX, GridY, ItemCount, 0);
	 }
}

void  ReadChallanger(void)
{
}

void ProcessItemMessage( char*msg )
{
	MSG_ITEMSTANDARD* std = (MSG_ITEMSTANDARD *) msg;

	ItemServerSocket.LastReceiveTime = SecCounter;

	int	conn = std->nID;
	if(conn<=0 || conn>=MAX_USER) return;
	if(std->wType!=_Msg_Cash2&&strncmp(std->AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH)!=0) return;
	
	switch (std->wType)
	{ 
		case _Msg_Cash:
		{
			Msg_Cash* m = (Msg_Cash*)std;

			if(m->byType==1)
			{	pUser[conn].m_nCash = m->nCash;
			}	else
			if(m->byType==2)
			{	m->nCash = pUser[conn].m_nCash;
			}

			pUser[conn].cSock.SendOneMessage( (char*)m, sizeof(*m) );
		}	break;
		case _Msg_Cash2:
		{
			Msg_Cash2 *m = (Msg_Cash2*)std;

			if(m->C_Type==2)
			{	pUser[conn].m_nCash = m->Amount;
			}	else
			{	m->Amount = pUser[conn].m_nCash;
			}

			Msg_Cash sm; ZeroMemory( &sm, sizeof(Msg_Cash) );
			sm.wType = _Msg_Cash; sm.byType = 1;
			sm.nCash = m->Amount;
			pUser[conn].cSock.SendOneMessage( (char*)&sm, sizeof(Msg_Cash) );
		}	break;
		case _Msg_Item:
		{
			Msg_Item* m = (Msg_Item*)std;

			if(m->byType==1)
			{	for (int i=0;i<MAX_CARGO;i++)
				{	if( pUser[conn].Cargo[i].snIndex==0)
					{
						pUser[conn].Cargo[i].snIndex = m->snItemIndex - HT_PARAMTYPE_ITEM_START + 1;
						pUser[conn].Cargo[i].byCount = m->byItemCount;
						short sDur = eDur_Indestructible;
						g_ParamMgr.HT_bGetItemMaxDurability( m->snItemIndex, &sDur );
						pUser[conn].Cargo[i].snDurability = sDur;

						char szLog[256], szItem[128];
						BASE_GetItemCode( &pUser[conn].Cargo[i], szItem );
						sprintf( szLog, "get %s", szItem );
						Log( szLog, pUser[conn].AccountName, pUser[conn].IP );

						S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
						sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_CARGO;
						sm.byIndex=i; sm.sitem=pUser[conn].Cargo[i];
						pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));

						m->byType = 2;
						m->nWorld = ServerGroup;
						ItemServerSocket.SendCashMessage((char*)m,sizeof(Msg_Item));
						break;
					}
				}
			}
		}	break;
		case _Msg_Mail:
		{
		}	break;
		default:
			break;
	}
}

void ProcessBILLMessage( char*msg )
{
	_AUTH_GAME* std1 = (_AUTH_GAME *) msg;
	_AUTH_GAME2* std2 = (_AUTH_GAME2 *) msg;

	char chBuf[256] = {0,}; int nType=htonl(std1->Packet_Type);
	int nResult=0; int conn=0; int nRemain=0;
	if(nType>=_Msg_BillUserInit)
	{	_AUTH_GAME2* std2 = (_AUTH_GAME2 *) msg;
		nResult=htonl(std2->Packet_result);
		sprintf(chBuf, "Packet_Type:%d Result:%d ID:%s \r\n", nType, nResult, std2->User_ID);
		TimeWriteLog( chBuf, ".\\Event\\BillPacket.txt" );
	}	else
	{	conn = atoi(std1->Session);
		if (conn<=0||conn>=MAX_USER) return;
		nResult=htonl(std1->Result);
		nRemain=htonl(std1->Bill_Remain);
		sprintf(chBuf, "Packet_Type:%d Result:%d Session:%d ID:%s Bill_Method:%s RemainTime:%d \r\n", nType, nResult, conn, std1->User_ID, std1->Bill_Method, nRemain);
		TimeWriteLog( chBuf, ".\\Event\\BillPacket.txt" );

		if(strncmp(pUser[conn].AccountName, std1->User_ID, ACCOUNTNAME_LENGTH))
		{	if(std1->Packet_Type==_Msg_BillUserPlaying)
			{	std1->Result=2;
				SendBilling2(std1, _Msg_BillUserPlaying);
			}
		
			sprintf(chBuf, "err Dismatch Bill-Zone Session : conn:%d, ID:%s connID:%s \r\n", conn, std1->User_ID, pUser[conn].AccountName);
			TimeWriteLog(chBuf, ".\\Event\\[Log]BillError.txt"); return;
		}
	}
	
	switch (nType)
	{ 
		case _Msg_BillLogin:
		{	
		}	break;
		case _Msg_BillUserIn:
		{	if(nResult==0) pUser[conn].IsBillConnect=1; 
			else 
			{	Msg_BillStatus sm; sm.wType = _Msg_BillStatus;
				sm.nCommand = 1;	//	0:성공, 1:계정만료
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

				sprintf(temp,"clo dbg _Msg_BillUserIn result:%d char:%s",nResult, pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				CloseUser(conn);
			}
		}	break;
		case _Msg_BillUserAlarm:
		{	if(nResult==1)
			{	char chBuf[256] = {0,}; 
				sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], htonl(std1->Bill_Remain));
				SendClientMessage(conn, chBuf);

				Msg_Alarm	sm; sm.wType = _Msg_Alarm;
				sm.unType = SYSTEM_ARALM_GAME_EXPIRED;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
			}
			else if(nResult==0)
			{	SendClientMessage(conn, g_pMessageStringTable[_Billing_Remain_Expire]);
				CloseUser(conn);
			}
			else if(nResult==-2)
			{	SendClientMessage(conn, g_pMessageStringTable[_Reconnecting_Other_Place]);
				if(g_eCountryID == eCountryPhilippines || g_eCountryID == eCountryIndonesia)
				{
					pUser[conn].IsBillConnect=0;
					pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout;
				}
				CloseUser(conn);
			}
		}	break;
		case _Msg_BillUserPlaying:
		{	
			if(nResult==0)
			{	if(strncmp(pUser[conn].AccountName, std1->User_ID, ACCOUNTNAME_LENGTH)==0 && pUser[conn].Mode!=USER_EMPTY)
					std1->Result = 0;
				else
					std1->Result = 2;

				SendBilling2(std1, _Msg_BillUserPlaying);
			}

		}	break;
		case _Msg_BillUserInit :
		{
		}	break;
		case _Msg_BillTimeEx:
		{
		}	break;
		case _Msg_BillCard :
		{
		}	break;
		case _Msg_BillDress:
		{
		}	break;
		case _Msg_BillMessage:
		{
		}	break;
		default:
			break;
	}
}

int	SendBilling(int conn,char * AccountName,int type,int NewSession)
{
	_AUTH_GAME sm; memset(&sm,0,sizeof(sm));
	sm.Packet_Type = ntohl(type);
	strncpy(sm.S_KEY, S_Key, sizeof(sm.S_KEY));
	strncpy(sm.Session ,pUser[conn].Session, sizeof(pUser[conn].Session));
	strncpy(sm.User_ID ,AccountName, ACCOUNTNAME_LENGTH);
	strncpy(sm.User_IP ,pUser[conn].pIP, sizeof(pUser[conn].pIP));

	int nID = 1; 

	if(g_eCountryID == eCountryIndonesia)			//	임시코드
	{	strcpy(sm.User_No, "1");					//	잠시 테스트를 위해 하드코딩.(원래는 pUser[conn].m_UserNo를 입력한다)
	}

	BillServerSocket.SendBillMessage((char*)&sm);

	return 0;
}

int	SendBilling2(_AUTH_GAME *m,int type)
{
	m->Packet_Type = ntohl(type);
	strncpy(m->S_KEY, S_Key, sizeof(m->S_KEY));

	int nID = ntohl(1);

	if(g_eCountryID == eCountryIndonesia)			//	임시코드
	{	memcpy(m->User_No, &nID, sizeof(nID));		//	잠시 테스트를 위해 하드코딩.(원래는 pUser[conn].m_UserNo를 입력한다)
	}

	BillServerSocket.SendBillMessage((char*)m);

	return 0;
}

int	SendBilling3(int conn, _AUTH_GAME2 *m,int type)
{
	m->Packet_Type = ntohl(type);
	m->Packet_result = ntohl(m->Packet_result);
	m->Map_number = ntohl(m->Map_number);
	m->User_co[0] = ntohl(m->User_co[0]);
	m->User_co[1] = ntohl(m->User_co[1]);
	m->article_number = ntohl(m->article_number);
	m->Dressed = ntohl(m->Dressed);
	m->Time_Exchanged = ntohl(m->Time_Exchanged);
	m->ItemNo = ntohl(m->ItemNo);
	strncpy(m->User_ID, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
	strncpy(m->User_roleName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	BillServerSocket.SendBillMessage((char*)m);

	return 0;
}

//PORTALINFO* GetPortal(WORD WPortalID)
//{
//	PORTALINFO* pPortal = NULL;
//
//	for(int i=0; i<MAX_PORTAL_COUNT; i++)
//	{
//		if( pPortalInfo[i].wPortalID == WPortalID )
//			return &pPortalInfo[i];
//	}
//
//	return pPortal;
//}

short GetSkillDataIndex( short a_sID, byte a_byLevel )
{
	short sIndex = 0;
	if( HT_PARAMTYPE_MONSTERSKILL_START <= a_sID ) // monster skill 이다.
	{
		sIndex = a_sID - HT_PARAMTYPE_MONSTERSKILL_START + 4001;
		return sIndex;		
	}

	sIndex = (a_sID - HT_PARAMTYPE_PCSKILL_START )*10 + a_byLevel;
	return sIndex;
}


void LoadSkillData()
{
	bool bRes = false;
	int iIndex = 0;
	int iRange, iAOE, iRealm, iRace;
	short sDummy = 0;
	int iDummy = 0;
	byte byDummy = 0;

	for( int iID = HT_PARAMTYPE_PCSKILL_START; iID <= HT_PARAMTYPE_PCSKILL_END; ++ iID )
	{		
		for( byte byLevel = 1; byLevel < 11; ++byLevel )
		{	
			iIndex = (iID - HT_PARAMTYPE_PCSKILL_START )*10 + byLevel;

			bRes = g_ParamMgr.HT_bLockID( iID, byLevel );
			if( bRes )
			{
				memset( &(pSkillData[iIndex].kDamage), 0, sizeof(TNDAMAGE) );
				pSkillData[iIndex].sType = 0;
				pSkillData[iIndex].sItemType = 0;
				pSkillData[iIndex].sSkillType = 0;
				pSkillData[iIndex].sID = iID;
				pSkillData[iIndex].byLevel = byLevel;
				g_ParamMgr.HT_bGetPCSkillMaxLevel( &pSkillData[iIndex].byMaxLevel );
				g_ParamMgr.HT_bGetPCSkillType( &byDummy );
				if( byDummy ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Aid;
				g_ParamMgr.HT_bGetPCSkillCombatPhase( &pSkillData[iIndex].sCombatPhase );
				g_ParamMgr.HT_bGetPCSkillFollowRange( &pSkillData[iIndex].byFollow );
				g_ParamMgr.HT_bGetPCSkillPierceRate( &pSkillData[iIndex].byPierceRate );
				g_ParamMgr.HT_bGetPCSkillDuration( &pSkillData[iIndex].iCastDuration );
				g_ParamMgr.HT_bGetPCSkillSuccessRate( &pSkillData[iIndex].bySuccessRate );
				g_ParamMgr.HT_bGetPCSkillReadyTime( &iDummy );
				pSkillData[iIndex].iAttackSpeed = iDummy;
				g_ParamMgr.HT_bGetPCSkillCastingTime( &iDummy );
				pSkillData[iIndex].iAttackSpeed += iDummy;
				byte byAttackPointPosition = 0;
				g_ParamMgr.HT_bGetPCSkillReserve1( &byAttackPointPosition );
				g_ParamMgr.HT_bGetPCSkillApplyTime( &iDummy );
				// 원래 아래의 activateTime이 있어야 하는데, C/S간의 정확한 작업이 안되어 1차적으로 빼도록 하겠다.
				pSkillData[iIndex].iActivateTime = 0;
				//pSkillData[iIndex].iActivateTime = (iDummy*(100-byAttackPointPosition))/100;  // PC 스킬인 경우, ...
				//pSkillData[iIndex].iApplyTime = iDummy;
				//if( 200 < pSkillData[iIndex].iAttackSpeed ) pSkillData[iIndex].iAttackSpeed -= 200;
				g_ParamMgr.HT_bGetPCSkillCoolDownTime( &pSkillData[iIndex].iCoolDownTime );
				if( 200 < pSkillData[iIndex].iCoolDownTime )
				{
					//pSkillData[iIndex].iCoolDownTime = pSkillData[iIndex].iCoolDownTime * 0.97;
				}
				g_ParamMgr.HT_bGetPCSkillRange( &iRange );
				pSkillData[iIndex].iRange = iRange;
				if( 0 < pSkillData[iIndex].iRange ) pSkillData[iIndex].iRange += 2;
				g_ParamMgr.HT_bGetPCSkillAreaOfEffect( &iAOE );
				pSkillData[iIndex].iAOE = iAOE;
				if( 0 < pSkillData[iIndex].iAOE ) pSkillData[iIndex].iAOE += 2;
				g_ParamMgr.HT_bGetPCSkillAllowedTarget( &pSkillData[iIndex].iAllowedTargets );
				//g_ParamMgr.HT_bGetPCSkillCastingSuccessRate( &pSkillData[iIndex].byFizzleRate );
				g_ParamMgr.HT_bGetPCSkillEffect1ID( &pSkillData[iIndex].krgEffect[0].iID );
				g_ParamMgr.HT_bGetPCSkillEffect1Function( &pSkillData[iIndex].krgEffect[0].kFunc.iData );
				g_ParamMgr.HT_bGetPCSkillEffect1Duration( &pSkillData[iIndex].krgEffect[0].iDuration );
				g_ParamMgr.HT_bGetPCSkillEffect1Param1( &pSkillData[iIndex].krgEffect[0].iParam1 );
				g_ParamMgr.HT_bGetPCSkillEffect1Param2( &pSkillData[iIndex].krgEffect[0].iParam2 );
				g_ParamMgr.HT_bGetPCSkillEffect2ID( &pSkillData[iIndex].krgEffect[1].iID );
				g_ParamMgr.HT_bGetPCSkillEffect2Function( &pSkillData[iIndex].krgEffect[1].kFunc.iData );
				g_ParamMgr.HT_bGetPCSkillEffect2Duration( &pSkillData[iIndex].krgEffect[1].iDuration );
				g_ParamMgr.HT_bGetPCSkillEffect2Param1( &pSkillData[iIndex].krgEffect[1].iParam1 );
				g_ParamMgr.HT_bGetPCSkillEffect2Param2( &pSkillData[iIndex].krgEffect[1].iParam2 );
				g_ParamMgr.HT_bGetPCSkillEffect3ID( &pSkillData[iIndex].krgEffect[2].iID );
				g_ParamMgr.HT_bGetPCSkillEffect3Function( &pSkillData[iIndex].krgEffect[2].kFunc.iData );
				g_ParamMgr.HT_bGetPCSkillEffect3Duration( &pSkillData[iIndex].krgEffect[2].iDuration );
				g_ParamMgr.HT_bGetPCSkillEffect3Param1( &pSkillData[iIndex].krgEffect[2].iParam1 );
				g_ParamMgr.HT_bGetPCSkillEffect3Param2( &pSkillData[iIndex].krgEffect[2].iParam2 );
				g_ParamMgr.HT_bGetPCSkillEffect4ID( &pSkillData[iIndex].krgEffect[3].iID );
				g_ParamMgr.HT_bGetPCSkillEffect4Function( &pSkillData[iIndex].krgEffect[3].kFunc.iData );
				g_ParamMgr.HT_bGetPCSkillEffect4Duration( &pSkillData[iIndex].krgEffect[3].iDuration );
				g_ParamMgr.HT_bGetPCSkillEffect4Param1( &pSkillData[iIndex].krgEffect[3].iParam1 );
				g_ParamMgr.HT_bGetPCSkillEffect4Param2( &pSkillData[iIndex].krgEffect[3].iParam2 );
				g_ParamMgr.HT_bGetPCSkillEffect5ID( &pSkillData[iIndex].krgEffect[4].iID );
				g_ParamMgr.HT_bGetPCSkillEffect5Function( &pSkillData[iIndex].krgEffect[4].kFunc.iData );
				g_ParamMgr.HT_bGetPCSkillEffect5Duration( &pSkillData[iIndex].krgEffect[4].iDuration );
				g_ParamMgr.HT_bGetPCSkillEffect5Param1( &pSkillData[iIndex].krgEffect[4].iParam1 );
				g_ParamMgr.HT_bGetPCSkillEffect5Param2( &pSkillData[iIndex].krgEffect[4].iParam2 );
				g_ParamMgr.HT_bGetPCSkillCostTP( &pSkillData[iIndex].kCost.iTP );
				g_ParamMgr.HT_bGetPCSkillCostHP( &pSkillData[iIndex].kCost.iHP );
				g_ParamMgr.HT_bGetPCSkillidCostItem( &iDummy );
				pSkillData[iIndex].kCost.sItemID = (short)iDummy;
				g_ParamMgr.HT_bGetPCSkillCostItemCount( &pSkillData[iIndex].kCost.byItemCount );
				g_ParamMgr.HT_bGetPCSkillReqLevel( &pSkillData[iIndex].kReq.byLevel );
				g_ParamMgr.HT_bGetPCSkillReqTrimuriti( &iRealm );
				pSkillData[iIndex].kReq.byTrimuriti = (byte)iRealm;
				g_ParamMgr.HT_bGetPCSkillReqTribe( &iRace );
				pSkillData[iIndex].kReq.byTribe = (byte)iRace;
				g_ParamMgr.HT_bGetPCSkillReqClass( &pSkillData[iIndex].kReq.iClass );
				g_ParamMgr.HT_bGetPCSkillReqSkill1( &iDummy );
				pSkillData[iIndex].kReqSkill[0].sID = (short)iDummy;
				g_ParamMgr.HT_bGetPCSkillReqSkill1_Lvl( &pSkillData[iIndex].kReqSkill[0].byLevel );
				g_ParamMgr.HT_bGetPCSkillReqSkill2( &iDummy );
				pSkillData[iIndex].kReqSkill[1].sID = (short)iDummy;
				g_ParamMgr.HT_bGetPCSkillReqSkill2_Lvl( &pSkillData[iIndex].kReqSkill[1].byLevel );
				g_ParamMgr.HT_bGetPCSkillReqWeaponType( &pSkillData[iIndex].iReqWeapon );
				g_ParamMgr.HT_bGetPCSkillidReqItem( &pSkillData[iIndex].iReqItem );
				g_ParamMgr.HT_bGetPCSkillAttackType( &byDummy );
				pSkillData[iIndex].kDamage.iAttackType = byDummy;
				byte byWeaponBase = 0;
				g_ParamMgr.HT_bGetPCSkillReserve0( &byWeaponBase );
				if( 1 == byWeaponBase ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword;
				
				/*
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant1;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant2;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant3;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant2;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnAffect;

				*/
				//pSkillData[iIndex].kReq.sMuscle = pSkillData[iIndex].kReq.sNerves = pSkillData[iIndex].kReq.sHeart = pSkillData[iIndex].kReq.sMind = 0;
				pSkillData[iIndex].bySyncFlag = 0; // off 
				//pSkillData[iIndex].iActivateTime = 0;  // PC 스킬인 경우, ...
				pSkillData[iIndex].byCastCount = 1;
				pSkillData[iIndex].sSpeak = 0;

				pSkillData[iIndex].iPrice = 0;
				pSkillData[iIndex].sMaxDur = 0;
				pSkillData[iIndex].byMaxPackCount = 0;
				pSkillData[iIndex].sEventID = 0;				

#ifdef __TN_LOCAL_SERVER_SWITCH__

				/*
				if( 3114 == iID ) // 소환
				{
					//pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[0].iID = 120;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0;
					pSkillData[iIndex].krgEffect[0].iDuration = 30;
					pSkillData[iIndex].krgEffect[0].iParam1 = 2076;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0;
				}
				*/
#endif
/*
				if( 3224 == iID ) // 아사라 - stun
				{					
					pSkillData[iIndex].krgEffect[2].iDuration = 7000;
					pSkillData[iIndex].krgEffect[2].iParam1 = 100;

					pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[3].iID = 3020; // Bonus damage, 연계기에 대한 effect
					pSkillData[iIndex].krgEffect[3].kFunc.iData = 3222; // 비사크로를 1차 기술로 한다.
					pSkillData[iIndex].krgEffect[3].iParam1 = 100;
					pSkillData[iIndex].krgEffect[3].iParam2 = 200;
				}

				if( 3226 == iID ) // 바즈라 만타라 - PierceStrike 2
				{
					pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[1].iID = 3061;
					pSkillData[iIndex].krgEffect[1].kFunc.iData = 0;
					pSkillData[iIndex].krgEffect[1].iDuration = 0;
					pSkillData[iIndex].krgEffect[1].iParam1 = 50;
					pSkillData[iIndex].krgEffect[1].iParam2 = 100;
					if( 1 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 200;
					else if( 2 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 300;
					else if( 3 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 400;
					else if( 4 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 500;
					else if( 5 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 600;
				}

				if( 3222 == iID ) // 비사크로 - PreventRegenHP
				{
					pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[1].iID = 3210;
					pSkillData[iIndex].krgEffect[1].kFunc.iData = 0;
					pSkillData[iIndex].krgEffect[1].iDuration = 10000;
					pSkillData[iIndex].krgEffect[1].iParam1 = 0;
					pSkillData[iIndex].krgEffect[1].iParam2 = 0;
				}

				if( 3241 == iID ) // 카도라이 - All stat + 100
				{
					pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[0].iID = 4250;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0;
					pSkillData[iIndex].krgEffect[0].iDuration = 5000;
					pSkillData[iIndex].krgEffect[0].iParam1 = 100;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0;
				}

				if( 3208 == iID ) // 바사티 - All Resist + 50
				{
					pSkillData[iIndex].sCombatPhase = 0x7F;
					pSkillData[iIndex].krgEffect[0].iID = 4240;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0;
					pSkillData[iIndex].krgEffect[0].iDuration = 6000;
					pSkillData[iIndex].krgEffect[0].iParam1 = 50;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0;
				}
*/
				if( 3241 == iID )
				{
					pSkillData[iIndex].iAllowedTargets = 2;
				}

/*
				if( 3328 == iID )
				{
					pSkillData[iIndex].iAllowedTargets = 2;
				}

				if( 3330 == iID )
				{
					pSkillData[iIndex].iCastDuration = 0;
				}
*/
/*				
				if( 3143 == iID )
				{
					//pSkillData[iIndex].sCombatPhase = 12;
					//pSkillData[iIndex].krgEffect[1].iID = 3010;
					//pSkillData[iIndex].krgEffect[1].kFunc.iData = 0;
					//pSkillData[iIndex].krgEffect[1].iDuration = 0;
					//pSkillData[iIndex].krgEffect[1].iParam1 = 50;
					//pSkillData[iIndex].krgEffect[1].iParam2 = 0;

					pSkillData[iIndex].iCoolDownTime = 10000;

					if( 1 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 4;
					else if( 2 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 4;
					else if( 3 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 5;
					else if( 4 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 5;
					else if( 5 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 7;
					else if( 6 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 7;
					else if( 7 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 8;
					else if( 8 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 8;
					else if( 9 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 9;
					else if( 10 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 9;
				}
*/				

				for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
				{
					if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue;

					if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
					//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
					if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
						|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash;

					switch( pSkillData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Resurrect :
						pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant1;
					case eTNAfn_Terror :
					case eTNAfn_StealHP :
					case eTNAfn_StealTP :
					case eTNAfn_KnockBack :
						pSkillData[iIndex].krgEffect[i].iDuration = 0;
						break;
					case eTNAfn_Taunt :
					case eTNAfn_DeTaunt :
						pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_AffectSelf;
						break;
					} // end of switch


					if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue;

					switch( pSkillData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Damage :
					case eTNAfn_DamageSplash :
						pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
						break;
					case eTNAfn_PierceDamage :
						pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_Fire :
					case eTNAfn_FireSplash :
						pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Fire;
						break;
					case eTNAfn_Cold :
					case eTNAfn_ColdSplash :
						pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Cold;
						break;
					case eTNAfn_Lightning :
					case eTNAfn_LightningSplash :
						pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Lightning;
						break;
					case eTNAfn_Poison :
					case eTNAfn_PoisonSplash :
						pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Poison;
						break;
					case eTNAfn_MultipleStrike :
						pSkillData[iIndex].byMaxPackCount = pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam2;
						if( 0 > pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 0;
						//if( 100 < pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 100;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_MultipleStrike;
						//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
						break;
/*
					case eTNAfn_EnergyOfSword :
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword;
						break;
*/
					case eTNAfn_Resurrect :
						pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam1;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Resurrect;
						break;
					case eTNAfn_TPBurn :
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_ChangeTP;
						break;
					} // end of switch
				}

				if( eTNCPhase_CastInstant1 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
				if( eTNCPhase_CastInstant2 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
				if( eTNCPhase_CastInstant3 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "PC> %d, SkillID:%d, Level:%d, ReqLevel:%d, Type:%d, CastDuration:%d, AttackSpeed:%d(iApplyTime:%d), CoolDownTime:%d, CombatPhase:%d(WeaponBase:%d), AllowedTarget:%d, AOE:%d, Range:%d, SuccRate:%d, Follow:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d,%d), Effect1(%d,%d,%d,%d,%d), Effect2(%d,%d,%d,%d,%d), Effect3(%d,%d,%d,%d,%d), Effect4(%d,%d,%d,%d,%d), Cost(%d,%d,%d), AAType(%d,%d), MaxLevel:%d, 다단치기(%d,%d), reqSkill(%d,%d) \r\n"
						, iIndex, iID, pSkillData[iIndex].byLevel, pSkillData[iIndex].kReq.byLevel, pSkillData[iIndex].sSkillType, pSkillData[iIndex].iCastDuration, pSkillData[iIndex].iAttackSpeed, pSkillData[iIndex].iActivateTime, pSkillData[iIndex].iCoolDownTime, pSkillData[iIndex].sCombatPhase, byWeaponBase, pSkillData[iIndex].iAllowedTargets, pSkillData[iIndex].iAOE, pSkillData[iIndex].iRange, pSkillData[iIndex].bySuccessRate, pSkillData[iIndex].byFollow
						, pSkillData[iIndex].kDamage.irgPhy[0], pSkillData[iIndex].kDamage.irgPhy[1], pSkillData[iIndex].kDamage.irgPierce[0], pSkillData[iIndex].kDamage.irgPierce[1], pSkillData[iIndex].kDamage.irgFire[0], pSkillData[iIndex].kDamage.irgFire[1], pSkillData[iIndex].kDamage.irgCold[0], pSkillData[iIndex].kDamage.irgCold[1], pSkillData[iIndex].kDamage.irgLightning[0], pSkillData[iIndex].kDamage.irgLightning[1], pSkillData[iIndex].kDamage.irgPoison[0], pSkillData[iIndex].kDamage.irgPoison[1]
						, pSkillData[iIndex].krgEffect[0].iID, pSkillData[iIndex].krgEffect[0].kFunc.iData, pSkillData[iIndex].krgEffect[0].iDuration, pSkillData[iIndex].krgEffect[0].iParam1, pSkillData[iIndex].krgEffect[0].iParam2
						, pSkillData[iIndex].krgEffect[1].iID, pSkillData[iIndex].krgEffect[1].kFunc.iData, pSkillData[iIndex].krgEffect[1].iDuration, pSkillData[iIndex].krgEffect[1].iParam1, pSkillData[iIndex].krgEffect[1].iParam2
						, pSkillData[iIndex].krgEffect[2].iID, pSkillData[iIndex].krgEffect[2].kFunc.iData, pSkillData[iIndex].krgEffect[2].iDuration, pSkillData[iIndex].krgEffect[2].iParam1, pSkillData[iIndex].krgEffect[2].iParam2
						, pSkillData[iIndex].krgEffect[3].iID, pSkillData[iIndex].krgEffect[3].kFunc.iData, pSkillData[iIndex].krgEffect[3].iDuration, pSkillData[iIndex].krgEffect[3].iParam1, pSkillData[iIndex].krgEffect[3].iParam2
						, pSkillData[iIndex].krgEffect[4].iID, pSkillData[iIndex].krgEffect[4].kFunc.iData, pSkillData[iIndex].krgEffect[4].iDuration, pSkillData[iIndex].krgEffect[4].iParam1, pSkillData[iIndex].krgEffect[4].iParam2
						, pSkillData[iIndex].kCost.iHP, pSkillData[iIndex].kCost.iTP, pSkillData[iIndex].kCost.sItemID
						, pSkillData[iIndex].kDamage.iAttackType, pSkillData[iIndex].byArmorType
						, pSkillData[iIndex].byMaxLevel, pSkillData[iIndex].byMaxPackCount, pSkillData[iIndex].sMaxDur
						, pSkillData[iIndex].kReqSkill[0].sID, pSkillData[iIndex].kReqSkill[1].sID
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSkillData.txt" );
				}
				#endif
			}
			g_ParamMgr.HT_bUnLockID( iID, byLevel );
		}
	}


	iIndex = 4001;
	for( int iID = HT_PARAMTYPE_MONSTERSKILL_START; iID <= HT_PARAMTYPE_MONSTERSKILL_END; ++ iID )
	{
		iIndex = MONSTER_SKILL_START + iID - HT_PARAMTYPE_MONSTERSKILL_START;
		bRes = g_ParamMgr.HT_bLockID( iID, 1 );
		if( bRes )
		{
			// initialize
			pSkillData[iIndex].bySyncFlag = 0; // off 
			pSkillData[iIndex].iActivateTime = 0;
			pSkillData[iIndex].byCastCount = 1;
			pSkillData[iIndex].sSpeak = 0;
			memset( &(pSkillData[iIndex].kDamage), 0, sizeof(TNDAMAGE) );

			pSkillData[iIndex].sType = 0;
			pSkillData[iIndex].sItemType = 0;
			pSkillData[iIndex].sSkillType = 0;
			pSkillData[iIndex].sID = iID;
			pSkillData[iIndex].byLevel = 1;
			g_ParamMgr.HT_bGetMonsterSkillMaxLevel( &pSkillData[iIndex].byMaxLevel );
			g_ParamMgr.HT_bGetMonsterSkillType( &byDummy );
			if( byDummy ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Aid;
			g_ParamMgr.HT_bGetMonsterSkillCombatPhase( &pSkillData[iIndex].sCombatPhase );
			g_ParamMgr.HT_bGetMonsterSkillFollowRange( &pSkillData[iIndex].byFollow );
			g_ParamMgr.HT_bGetMonsterSkillPierceRate( &pSkillData[iIndex].byPierceRate );
			g_ParamMgr.HT_bGetMonsterSkillDuration( &pSkillData[iIndex].iCastDuration );
			g_ParamMgr.HT_bGetMonsterSkillSuccessRate( &pSkillData[iIndex].bySuccessRate );
			g_ParamMgr.HT_bGetMonsterSkillSpeechContent( &pSkillData[iIndex].sSpeak );
			g_ParamMgr.HT_bGetMonsterSkillSyncFlag( &pSkillData[iIndex].bySyncFlag );
			g_ParamMgr.HT_bGetMonsterSkillCastingTime( &pSkillData[iIndex].iAttackSpeed );
			g_ParamMgr.HT_bGetMonsterSkillActivateTime( &pSkillData[iIndex].iActivateTime );
			g_ParamMgr.HT_bGetMonsterSkillCastCount( &pSkillData[iIndex].byCastCount );			
			g_ParamMgr.HT_bGetMonsterSkillCoolDownTime( &pSkillData[iIndex].iCoolDownTime );
			g_ParamMgr.HT_bGetMonsterSkillRange( &iRange );
			pSkillData[iIndex].iRange = iRange;
			if( 0 < pSkillData[iIndex].iRange ) pSkillData[iIndex].iRange += 2;		
			g_ParamMgr.HT_bGetMonsterSkillAreaOfEffect( &iAOE );
			pSkillData[iIndex].iAOE = iAOE;
			if( 0 < pSkillData[iIndex].iAOE ) pSkillData[iIndex].iAOE += 2;
			g_ParamMgr.HT_bGetMonsterSkillAllowedTarget( &pSkillData[iIndex].iAllowedTargets );
			//g_ParamMgr.HT_bGetMonsterSkillCastingSuccessRate( &pSkillData[iIndex].byFizzleRate );
			g_ParamMgr.HT_bGetMonsterSkillEffect1ID( &pSkillData[iIndex].krgEffect[0].iID );
			g_ParamMgr.HT_bGetMonsterSkillEffect1Function( &pSkillData[iIndex].krgEffect[0].kFunc.iData );
			g_ParamMgr.HT_bGetMonsterSkillEffect1Duration( &pSkillData[iIndex].krgEffect[0].iDuration );
			g_ParamMgr.HT_bGetMonsterSkillEffect1Param1( &pSkillData[iIndex].krgEffect[0].iParam1 );
			g_ParamMgr.HT_bGetMonsterSkillEffect1Param2( &pSkillData[iIndex].krgEffect[0].iParam2 );
			g_ParamMgr.HT_bGetMonsterSkillEffect2ID( &pSkillData[iIndex].krgEffect[1].iID );
			g_ParamMgr.HT_bGetMonsterSkillEffect2Function( &pSkillData[iIndex].krgEffect[1].kFunc.iData );
			g_ParamMgr.HT_bGetMonsterSkillEffect2Duration( &pSkillData[iIndex].krgEffect[1].iDuration );
			g_ParamMgr.HT_bGetMonsterSkillEffect2Param1( &pSkillData[iIndex].krgEffect[1].iParam1 );
			g_ParamMgr.HT_bGetMonsterSkillEffect2Param2( &pSkillData[iIndex].krgEffect[1].iParam2 );
			g_ParamMgr.HT_bGetMonsterSkillEffect3ID( &pSkillData[iIndex].krgEffect[2].iID );
			g_ParamMgr.HT_bGetMonsterSkillEffect3Function( &pSkillData[iIndex].krgEffect[2].kFunc.iData );
			g_ParamMgr.HT_bGetMonsterSkillEffect3Duration( &pSkillData[iIndex].krgEffect[2].iDuration );
			g_ParamMgr.HT_bGetMonsterSkillEffect3Param1( &pSkillData[iIndex].krgEffect[2].iParam1 );
			g_ParamMgr.HT_bGetMonsterSkillEffect3Param2( &pSkillData[iIndex].krgEffect[2].iParam2 );
			g_ParamMgr.HT_bGetMonsterSkillEffect4ID( &pSkillData[iIndex].krgEffect[3].iID );
			g_ParamMgr.HT_bGetMonsterSkillEffect4Function( &pSkillData[iIndex].krgEffect[3].kFunc.iData );
			g_ParamMgr.HT_bGetMonsterSkillEffect4Duration( &pSkillData[iIndex].krgEffect[3].iDuration );
			g_ParamMgr.HT_bGetMonsterSkillEffect4Param1( &pSkillData[iIndex].krgEffect[3].iParam1 );
			g_ParamMgr.HT_bGetMonsterSkillEffect4Param2( &pSkillData[iIndex].krgEffect[3].iParam2 );
			g_ParamMgr.HT_bGetMonsterSkillEffect5ID( &pSkillData[iIndex].krgEffect[4].iID );
			g_ParamMgr.HT_bGetMonsterSkillEffect5Function( &pSkillData[iIndex].krgEffect[4].kFunc.iData );
			g_ParamMgr.HT_bGetMonsterSkillEffect5Duration( &pSkillData[iIndex].krgEffect[4].iDuration );
			g_ParamMgr.HT_bGetMonsterSkillEffect5Param1( &pSkillData[iIndex].krgEffect[4].iParam1 );
			g_ParamMgr.HT_bGetMonsterSkillEffect5Param2( &pSkillData[iIndex].krgEffect[4].iParam2 );
			g_ParamMgr.HT_bGetMonsterSkillAttackType( &byDummy );
			pSkillData[iIndex].kDamage.iAttackType = byDummy;

			//pSkillData[iIndex].iAllowedTargets = eTNAT_Enemy;


			pSkillData[iIndex].kCost.iTP = 0;
			pSkillData[iIndex].kCost.iHP = 0;
			pSkillData[iIndex].kCost.sItemID = 0;
			pSkillData[iIndex].kCost.byItemCount = 0;
			pSkillData[iIndex].kReq.byLevel = 0;
			pSkillData[iIndex].kReq.byTrimuriti = 0xFF;
			pSkillData[iIndex].kReq.byTribe = 0xFF;
			pSkillData[iIndex].kReq.iClass = 0xFFFFFFFF;
			pSkillData[iIndex].kReq.sMuscle = pSkillData[iIndex].kReq.sNerves = pSkillData[iIndex].kReq.sHeart = pSkillData[iIndex].kReq.sMind = 0;
			pSkillData[iIndex].iPrice = 0;
			pSkillData[iIndex].sMaxDur = 0;
			pSkillData[iIndex].byMaxPackCount = 0;
			pSkillData[iIndex].sEventID = 0;
			pSkillData[iIndex].sSkillType = 0;			

/*
			if( HT_PARAMTYPE_MONSTERSKILL_START == iID )
			{
				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Pull;
				//pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant2;
				pSkillData[iIndex].sCombatPhase = eTNCPhase_OnTakeInstant2;
			}
*/


			//pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
			#ifdef __TN_TOP_LOG__
			if( 0 > pSkillData[iIndex].iRange )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "SkillID:%d, index:%d, Range:%d \r\n", pSkillData[iIndex].sID, iIndex, pSkillData[iIndex].iRange );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );		
			}
			#endif


			for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
			{
				if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue;

				if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
				else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
					|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash;

				if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue;

				switch( pSkillData[iIndex].krgEffect[i].iID )
				{
				case eTNAfn_Damage :
				case eTNAfn_DamageSplash :
					pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_PierceDamage :
					pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					break;
				case eTNAfn_Fire :
				case eTNAfn_FireSplash :
					pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Cold :
				case eTNAfn_ColdSplash :
					pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Lightning :
				case eTNAfn_LightningSplash :
					pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Poison :
				case eTNAfn_PoisonSplash :
					pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_MultipleStrike :
					pSkillData[iIndex].byMaxPackCount = pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam2;
					if( 0 > pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 0;
					//if( 100 < pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 100;

					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_MultipleStrike;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Resurrect :
					pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Resurrect;
					break;
				case eTNAfn_TPBurn :
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_ChangeTP;
					break;
/*
				case eTNAfn_EnergyOfSword :
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword;
					break;
*/
				} // end of switch
			}

			if( eTNCPhase_CastInstant1 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
			if( eTNCPhase_CastInstant2 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
			if( eTNCPhase_CastInstant3 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage;

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "Monster> %d, SkillID:%d, Level:%d, Type:%d, CastDuration:%d, SyncFlag:%d, AttackSpeed:%d, ActivateTime:%d, CastCount:%d, CoolDownTime:%d, CombatPhase:%d, AllowedTarget:%d, AOE:%d, Range:%d, SuccRate:%d, Follow:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d,%d), Effect1(%d,%d,%d,%d,%d), Effect2(%d,%d,%d,%d,%d), Effect3(%d,%d,%d,%d,%d), Effect4(%d,%d,%d,%d,%d), Cost(%d,%d,%d,%d), AAType(%d,%d), MaxLevel:%d, 다단치기(%d,%d), Speech:%d \r\n"
					, iIndex, iID, pSkillData[iIndex].byLevel, pSkillData[iIndex].sSkillType, pSkillData[iIndex].iCastDuration, pSkillData[iIndex].bySyncFlag, pSkillData[iIndex].iAttackSpeed, pSkillData[iIndex].iActivateTime, pSkillData[iIndex].byCastCount, pSkillData[iIndex].iCoolDownTime, pSkillData[iIndex].sCombatPhase, pSkillData[iIndex].iAllowedTargets, pSkillData[iIndex].iAOE, pSkillData[iIndex].iRange, pSkillData[iIndex].bySuccessRate, pSkillData[iIndex].byFollow
					, pSkillData[iIndex].kDamage.irgPhy[0], pSkillData[iIndex].kDamage.irgPhy[1], pSkillData[iIndex].kDamage.irgPierce[0], pSkillData[iIndex].kDamage.irgPierce[1], pSkillData[iIndex].kDamage.irgFire[0], pSkillData[iIndex].kDamage.irgFire[1], pSkillData[iIndex].kDamage.irgCold[0], pSkillData[iIndex].kDamage.irgCold[1], pSkillData[iIndex].kDamage.irgLightning[0], pSkillData[iIndex].kDamage.irgLightning[1], pSkillData[iIndex].kDamage.irgPoison[0], pSkillData[iIndex].kDamage.irgPoison[1]
					, pSkillData[iIndex].krgEffect[0].iID, pSkillData[iIndex].krgEffect[0].kFunc.iData, pSkillData[iIndex].krgEffect[0].iDuration, pSkillData[iIndex].krgEffect[0].iParam1, pSkillData[iIndex].krgEffect[0].iParam2
					, pSkillData[iIndex].krgEffect[1].iID, pSkillData[iIndex].krgEffect[1].kFunc.iData, pSkillData[iIndex].krgEffect[1].iDuration, pSkillData[iIndex].krgEffect[1].iParam1, pSkillData[iIndex].krgEffect[1].iParam2
					, pSkillData[iIndex].krgEffect[2].iID, pSkillData[iIndex].krgEffect[2].kFunc.iData, pSkillData[iIndex].krgEffect[2].iDuration, pSkillData[iIndex].krgEffect[2].iParam1, pSkillData[iIndex].krgEffect[2].iParam2
					, pSkillData[iIndex].krgEffect[3].iID, pSkillData[iIndex].krgEffect[3].kFunc.iData, pSkillData[iIndex].krgEffect[3].iDuration, pSkillData[iIndex].krgEffect[3].iParam1, pSkillData[iIndex].krgEffect[3].iParam2
					, pSkillData[iIndex].krgEffect[4].iID, pSkillData[iIndex].krgEffect[4].kFunc.iData, pSkillData[iIndex].krgEffect[4].iDuration, pSkillData[iIndex].krgEffect[4].iParam1, pSkillData[iIndex].krgEffect[4].iParam2
					, pSkillData[iIndex].kCost.iHP, pSkillData[iIndex].kCost.iTP, pSkillData[iIndex].kCost.sItemID, pSkillData[iIndex].kCost.byItemCount
					, pSkillData[iIndex].kDamage.iAttackType, pSkillData[iIndex].byArmorType
					, pSkillData[iIndex].byMaxLevel, pSkillData[iIndex].byMaxPackCount, pSkillData[iIndex].sMaxDur, pSkillData[iIndex].sSpeak
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSkillData.txt" );
			}
			#endif

			++iIndex;
		}
		g_ParamMgr.HT_bUnLockID( iID, 1 );
	}
/*
	{
		pSkillData[4496].bySuccessRate = 100;
		pSkillData[4496].iCastDuration = 0;
		pSkillData[4496].iAOE = eTNSklA_Unit;
		pSkillData[4496].iRange = 10;
		pSkillData[4496].iAllowedTargets = eTNAT_Friend;
		pSkillData[4496].sCombatPhase = 64;
		pSkillData[4496].bySyncFlag = 0; // off
		pSkillData[4496].iAttackSpeed = 0;
		pSkillData[4496].iCoolDownTime = 0;
		pSkillData[4496].iActivateTime = 0;
		pSkillData[4496].byCastCount = 1;
		//pSkillData[4496].krgEffect[0].

		pSkillData[4497].bySuccessRate = 100;
		pSkillData[4497].iCastDuration = 0;
		pSkillData[4497].iAOE = eTNSklA_Unit;
		pSkillData[4497].iRange = 10;
		pSkillData[4497].iAllowedTargets = eTNAT_Friend;
		pSkillData[4497].sCombatPhase = 64;
		pSkillData[4497].bySyncFlag = 0; // off
		pSkillData[4497].iAttackSpeed = 0;
		pSkillData[4497].iCoolDownTime = 0;
		pSkillData[4497].iActivateTime = 0;
		pSkillData[4497].byCastCount = 1;
	}
*/


	pSkillData[0].sID = 0;
	pSkillData[0].byLevel = 0;
	pSkillData[0].byMaxLevel = 0;
	pSkillData[0].sMaxDur = 0;
	//pSkillData[0].byFizzleRate = 100;
	pSkillData[0].byFollow = 0;
	pSkillData[0].bySuccessRate = 1;
	pSkillData[0].iAOE = 0;
	pSkillData[0].iCastDuration = eTNSklD_Instant;
	pSkillData[0].iRange = 0;
	pSkillData[0].bySyncFlag = 0;
	pSkillData[0].byCastCount = 1;
	pSkillData[0].iActivateTime = 0;
	pSkillData[0].iAllowedTargets = eTNAT_NA;
	pSkillData[0].iAttackSpeed = 10000;	
	pSkillData[0].iCoolDownTime = 10000;
	pSkillData[0].kCost.iHP = 10000;
	pSkillData[0].kCost.iTP = 10000;
	pSkillData[0].kReq.byLevel = eLvl_Max;
	pSkillData[0].kReq.byTribe = 0;
	pSkillData[0].kReq.byTrimuriti = 0;
	pSkillData[0].sType = 0;
	pSkillData[0].sItemType = 0;
	pSkillData[0].sSkillType = 0;
	pSkillData[0].kReq.sMuscle = pSkillData[0].kReq.sNerves = pSkillData[0].kReq.sHeart = pSkillData[0].kReq.sMind = 0;
	pSkillData[0].iPrice = 0;
	pSkillData[0].sMaxDur = 0;
	pSkillData[0].sEventID = 0;
	pSkillData[0].byArmorType = 0;
	pSkillData[0].kDamage.iAttackType = 0;
}


short GetItemDataIndex( short a_sID )
{
	short sIndex = a_sID - HT_PARAMTYPE_ITEM_START + 1;
	return sIndex;
}

void LoadItemData()
{
	int iSpeedCorrect = 0;
	int iIndex = 0;
	bool bRes = false;
	short sDummy = 0;
	int iDummy = 0;
	byte byDummy = 0;
	for( int iID = HT_PARAMTYPE_ITEM_START; iID <= HT_PARAMTYPE_ITEM_END; ++ iID )
	{		
		iIndex = iID - HT_PARAMTYPE_ITEM_START + 1;

		iSpeedCorrect = 0;
		bRes = g_ParamMgr.HT_bLockID( iID );
		if( bRes )
		{
			pItemData[iIndex].sID = iID;
			memset( &(pItemData[iIndex].kDamage), 0, sizeof(TNDAMAGE) );
			g_ParamMgr.HT_bGetItemLevel( &pItemData[iIndex].byLevel );
			//g_ParamMgr.HT_bGetItemClass( &pItemData[iIndex].byClass );
			g_ParamMgr.HT_bGetItemType( &pItemData[iIndex].sItemType );

			if( 0 != pItemData[iIndex].sItemType )
			{// 양손 무기일 경우 32bit를 true로 셋팅해놓는다.
				if( HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_START <= iID && HT_PARAMTYPE_ITEM_WEAPON_THROW_END >= iID )
				{
					pItemData[iIndex].sItemType = pItemData[iIndex].sItemType | eTNWpn_TwoHand;
					iSpeedCorrect = -201;
				}
			}
			
			g_ParamMgr.HT_bGetItemRupiah( &pItemData[iIndex].iPrice );			
			g_ParamMgr.HT_bGetItemMaxCount( &pItemData[iIndex].byMaxPackCount );
			g_ParamMgr.HT_bGetItemMaxDurability( &pItemData[iIndex].sMaxDur );
			g_ParamMgr.HT_bGetItemEffect1ID( &pItemData[iIndex].krgEffect[0].iID );
			g_ParamMgr.HT_bGetItemEffect1Function( &pItemData[iIndex].krgEffect[0].kFunc.iData );
			g_ParamMgr.HT_bGetItemEffect1Duration( &pItemData[iIndex].krgEffect[0].iDuration );
			g_ParamMgr.HT_bGetItemEffect1Param1( &pItemData[iIndex].krgEffect[0].iParam1 );
			g_ParamMgr.HT_bGetItemEffect1Param2( &pItemData[iIndex].krgEffect[0].iParam2 );
			g_ParamMgr.HT_bGetItemEffect2ID( &pItemData[iIndex].krgEffect[1].iID );
			g_ParamMgr.HT_bGetItemEffect2Function( &pItemData[iIndex].krgEffect[1].kFunc.iData );
			g_ParamMgr.HT_bGetItemEffect2Duration( &pItemData[iIndex].krgEffect[1].iDuration );
			g_ParamMgr.HT_bGetItemEffect2Param1( &pItemData[iIndex].krgEffect[1].iParam1 );
			g_ParamMgr.HT_bGetItemEffect2Param2( &pItemData[iIndex].krgEffect[1].iParam2 );
			g_ParamMgr.HT_bGetItemEffect3ID( &pItemData[iIndex].krgEffect[2].iID );
			g_ParamMgr.HT_bGetItemEffect3Function( &pItemData[iIndex].krgEffect[2].kFunc.iData );
			g_ParamMgr.HT_bGetItemEffect3Duration( &pItemData[iIndex].krgEffect[2].iDuration );
			g_ParamMgr.HT_bGetItemEffect3Param1( &pItemData[iIndex].krgEffect[2].iParam1 );
			g_ParamMgr.HT_bGetItemEffect3Param2( &pItemData[iIndex].krgEffect[2].iParam2 );
			g_ParamMgr.HT_bGetItemEffect4ID( &pItemData[iIndex].krgEffect[3].iID );
			g_ParamMgr.HT_bGetItemEffect4Function( &pItemData[iIndex].krgEffect[3].kFunc.iData );
			g_ParamMgr.HT_bGetItemEffect4Duration( &pItemData[iIndex].krgEffect[3].iDuration );
			g_ParamMgr.HT_bGetItemEffect4Param1( &pItemData[iIndex].krgEffect[3].iParam1 );
			g_ParamMgr.HT_bGetItemEffect4Param2( &pItemData[iIndex].krgEffect[3].iParam2 );
			g_ParamMgr.HT_bGetItemEffect5ID( &pItemData[iIndex].krgEffect[4].iID );
			g_ParamMgr.HT_bGetItemEffect5Function( &pItemData[iIndex].krgEffect[4].kFunc.iData );
			g_ParamMgr.HT_bGetItemEffect5Duration( &pItemData[iIndex].krgEffect[4].iDuration );
			g_ParamMgr.HT_bGetItemEffect5Param1( &pItemData[iIndex].krgEffect[4].iParam1 );
			g_ParamMgr.HT_bGetItemEffect5Param2( &pItemData[iIndex].krgEffect[4].iParam2 );
			g_ParamMgr.HT_bGetItemCombatPhase( &pItemData[iIndex].sCombatPhase );
			g_ParamMgr.HT_bGetItemCoolDownTime( &pItemData[iIndex].iAttackSpeed );	// 공격시간으로 skill에서는 ready time을 나타낸다. 최소 이 시간이 경과되어야지 1회 공격이 발동한다.		
			g_ParamMgr.HT_bGetItemRange( &byDummy );
			pItemData[iIndex].iRange = byDummy;
			g_ParamMgr.HT_bGetItemCostTP( &pItemData[iIndex].kCost.iTP );
			g_ParamMgr.HT_bGetItemCostHP( &pItemData[iIndex].kCost.iHP );
			g_ParamMgr.HT_bGetItemidCostItem( &iDummy );
			pItemData[iIndex].kCost.sItemID = (short)iDummy;
			g_ParamMgr.HT_bGetItemLimitTrimuriti( &iDummy );
			pItemData[iIndex].kReq.byTrimuriti = (byte)iDummy;
			g_ParamMgr.HT_bGetItemLimitTribe( &iDummy );
			pItemData[iIndex].kReq.byTribe = (byte)iDummy;
			g_ParamMgr.HT_bGetItemLimitLevel( &pItemData[iIndex].kReq.byLevel );
			g_ParamMgr.HT_bGetItemLimitMuscleChakra( &pItemData[iIndex].kReq.sMuscle );
			g_ParamMgr.HT_bGetItemLimitNerveChakra( &pItemData[iIndex].kReq.sNerves );
			g_ParamMgr.HT_bGetItemLimitHeartChakra( &pItemData[iIndex].kReq.sHeart );
			g_ParamMgr.HT_bGetItemLimitSoulChakra( &pItemData[iIndex].kReq.sMind );
			g_ParamMgr.HT_bGetItemAllowedTarget( &pItemData[iIndex].iAllowedTargets );
			g_ParamMgr.HT_bGetItemEventID( &pItemData[iIndex].sEventID );
			g_ParamMgr.HT_bGetItemAttackType( &byDummy );
			pItemData[iIndex].kDamage.iAttackType = byDummy;
			g_ParamMgr.HT_bGetItemArmorType( &pItemData[iIndex].byArmorType );
			g_ParamMgr.HT_bGetItemReserve1( &pItemData[iIndex].byDecay ); // Reserved1
			if( (eItm_Decay!=pItemData[iIndex].byDecay) && (eItm_Permenent!=pItemData[iIndex].byDecay) ) pItemData[iIndex].byDecay = eItm_Decay;
			g_ParamMgr.HT_bGetItemReserve2( &pItemData[iIndex].kReq.byZone ); // zone 사용 제한, 0 이면 all

			g_ParamMgr.HT_bGetItemReserve3( &byDummy ); // Reserved3 -> log를 남기기 위한 것
			pItemData[iIndex].sType = byDummy;

			if( 3 == pItemData[iIndex].kDamage.iAttackType ) iSpeedCorrect = 0; // 양손검이면, 속도보정이 없다.
			pItemData[iIndex].iAttackSpeed += iSpeedCorrect;
			
			pItemData[iIndex].bySyncFlag = 0;
			pItemData[iIndex].byCastCount = 1;
			pItemData[iIndex].iActivateTime = 0; //pItemData[iIndex].iAttackSpeed;  // 무기의 cooldowntime이다. 이것은 동적으로 변경되어야 할 것이다.
			pItemData[iIndex].iCoolDownTime = 0;
			pItemData[iIndex].byMaxLevel = 0;
			//pItemData[iIndex].byClass = 0;
			pItemData[iIndex].iCastDuration = eTNSklD_Instant;
			if( 1 == pItemData[iIndex].iRange ) pItemData[iIndex].iRange = eTNChr_MeleeAttackRange;
			pItemData[iIndex].iAOE = eTNSklA_Unit;
			pItemData[iIndex].bySuccessRate = 0;
			//pItemData[iIndex].byFizzleRate = 0;
			pItemData[iIndex].byFollow = 0;
			if( eTNWpn_Bow & pItemData[iIndex].sItemType ) pItemData[iIndex].byFollow = 1;
			pItemData[iIndex].kReq.iClass = 0xFFFFFFFF;
			pItemData[iIndex].iReqWeapon = 0;
			pItemData[iIndex].iReqItem = 0;
			pItemData[iIndex].sSkillType = 0;	

			if( HT_PARAMTYPE_ITEM_USABLE_START <= iID && HT_PARAMTYPE_ITEM_USABLE_END > iID && (0<pItemData[iIndex].iAttackSpeed) )
			{	//	소모성 item의 경우, ... 0.5초의 여유를 준다.
				pItemData[iIndex].iAttackSpeed -= 500;
				if( 0 > pItemData[iIndex].iAttackSpeed ) pItemData[iIndex].iAttackSpeed += 500;
			}


#ifdef __TN_LOCAL_SERVER_SWITCH__
			if( 5001 == iID ) pItemData[iIndex].byMaxLevel = 1;
			else if( 5251 == iID ) pItemData[iIndex].byMaxLevel = 1;
			else if( 5601 == iID ) pItemData[iIndex].byMaxLevel = 1;
			else if( 5151 == iID ) pItemData[iIndex].byMaxLevel = 1;
			else
			{
			}

			if( 6729 == iID )
			{
				pItemData[iIndex].krgEffect[0].iDuration = 30;
				//pItemData[iIndex].krgEffect[0].iID = 3080;
				//pItemData[iIndex].krgEffect[0].kFunc.iData = 2;
				//pItemData[iIndex].krgEffect[0].iParam1 = 50;
				//pItemData[iIndex].krgEffect[0].iParam2 = 100;
			}
#endif

			{
				for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
				{
					if( 0 >= pItemData[iIndex].krgEffect[i].iID ) continue;

					/*
					if( eTNSklD_Instant != pItemData[iIndex].krgEffect[i].iDuration )
					{
						pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_OnAffect;
						pItemData[iIndex].iAllowedTargets = eTNAT_Self;
					}
					*/
					pItemData[iIndex].sSkillType = pItemData[iIndex].sSkillType | eTNSklT_EnergyOfSword;

					switch( pItemData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Damage :
					case eTNAfn_DamageSplash :
						pItemData[iIndex].kDamage.irgPhy[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgPhy[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_PierceDamage :
						pItemData[iIndex].kDamage.irgPierce[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgPierce[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_Fire :
					case eTNAfn_FireSplash :
						pItemData[iIndex].kDamage.irgFire[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgFire[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_Cold :
					case eTNAfn_ColdSplash :
						pItemData[iIndex].kDamage.irgCold[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgCold[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_Lightning :
					case eTNAfn_LightningSplash :
						pItemData[iIndex].kDamage.irgLightning[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgLightning[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_Poison :
					case eTNAfn_PoisonSplash :
						pItemData[iIndex].kDamage.irgPoison[0] += pItemData[iIndex].krgEffect[i].iParam1;
						pItemData[iIndex].kDamage.irgPoison[1] += pItemData[iIndex].krgEffect[i].iParam2;
						break;
					case eTNAfn_WeaponMastery : // item에서는 이 effect가 사용되어서는 안된다.
						pItemData[iIndex].krgEffect[i].iID = 0;
						break;
					case eTNAfn_TPBurn :
						pItemData[iIndex].sSkillType = pItemData[iIndex].sSkillType | eTNSklT_ChangeTP;

					default :
						//pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant1;
						//pItemData[iIndex].iAllowedTargets = eTNAT_Self;
						break;
					} // end of switch
				}
			}

			pItemData[iIndex].kDamage.iSum = pItemData[iIndex].kDamage.irgPhy[0] + pItemData[iIndex].kDamage.irgPierce[0] + pItemData[iIndex].kDamage.irgFire[0] + pItemData[iIndex].kDamage.irgCold[0] + pItemData[iIndex].kDamage.irgLightning[0] + pItemData[iIndex].kDamage.irgPoison[0];
			if( 0 < pItemData[iIndex].kDamage.iSum )
			{
				pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_DealDamage;
				//pItemData[iIndex].iAllowedTargets = eTNAT_Enemy;
			}


			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "Index: %d, ID:%d, AttackSpeed:%d, ActivateTime:%d, CastCount:%d, CoolDown:%d, CombatPhase:%d, AllowedTarget:%d, AOE:%d, Range:%d, 무기종류:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d), Cost(%d,%d,%d,%d), Dur:%d, Pack:%d, AAType(%d,%d), SyncFlag:%d, Decay:%d \r\n"
					, iIndex, pItemData[iIndex].sID, pItemData[iIndex].iAttackSpeed, pItemData[iIndex].iActivateTime, pItemData[iIndex].byCastCount, pItemData[iIndex].iCoolDownTime, pItemData[iIndex].sCombatPhase, pItemData[iIndex].iAllowedTargets, pItemData[iIndex].iAOE, pItemData[iIndex].iRange
					, pItemData[iIndex].sItemType, pItemData[iIndex].kDamage.irgPhy[0], pItemData[iIndex].kDamage.irgPhy[1], pItemData[iIndex].kDamage.irgPierce[0], pItemData[iIndex].kDamage.irgPierce[1], pItemData[iIndex].kDamage.irgFire[0], pItemData[iIndex].kDamage.irgFire[1], pItemData[iIndex].kDamage.irgCold[0], pItemData[iIndex].kDamage.irgCold[1], pItemData[iIndex].kDamage.irgLightning[0], pItemData[iIndex].kDamage.irgLightning[1], pItemData[iIndex].kDamage.irgPoison[0], pItemData[iIndex].kDamage.irgPoison[1]
					, pItemData[iIndex].krgEffect[0].iID, pItemData[iIndex].krgEffect[0].iDuration, pItemData[iIndex].krgEffect[0].iParam1, pItemData[iIndex].krgEffect[0].iParam2
					, pItemData[iIndex].kCost.iHP, pItemData[iIndex].kCost.iTP, pItemData[iIndex].kCost.sItemID, pItemData[iIndex].kCost.byItemCount, pItemData[iIndex].sMaxDur, pItemData[iIndex].byMaxPackCount
					, pItemData[iIndex].kDamage.iAttackType, pItemData[iIndex].byArmorType, pItemData[iIndex].bySyncFlag, pItemData[iIndex].byDecay
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadItemData.txt" );
			}
			#endif
		}
		g_ParamMgr.HT_bUnLockID( iID );
	}

	// Pist
	pItemData[0].iActivateTime = eTNChr_PistAttackSpeed;
	pItemData[0].bySyncFlag = 0;
	pItemData[0].byCastCount = 1;
	pItemData[0].iAttackSpeed = eTNChr_PistAttackSpeed;
	pItemData[0].iRange = eTNChr_MeleeAttackRange;
	memset( &pItemData[0].kDamage, 0, sizeof(TNDAMAGE) );
	pItemData[0].kDamage.irgPhy[0] = 1;
	pItemData[0].kDamage.irgPhy[1] = 2;
	pItemData[0].kDamage.irgPierce[0] = pItemData[0].kDamage.irgPierce[1] = 0;
	pItemData[0].sSkillType = eTNSklT_EnergyOfSword;
	pItemData[0].sItemType = 0;
	pItemData[0].iAllowedTargets = eTNAT_Enemy;
	pItemData[0].sCombatPhase = eTNCPhase_DealDamage;
	pItemData[0].byArmorType = 0;
	pItemData[0].byDecay = eItm_Decay;
	pItemData[0].kDamage.iAttackType = 0;
	pItemData[0].sMaxDur =	eDur_Indestructible; // 맨손은 무한 내구도이다.
}


void LoadMonsterData()
{
	int iIndex = 0;
	bool bRes = false;

	short sDummy = 0;
	int iDummy = 0;
	byte byDummy = 0;
	unsigned int uiDummy = 0;

	for( int iID = HT_PARAMTYPE_MONSTER_START; iID <= HT_PARAMTYPE_MONSTER_END; ++ iID )
	{		
		iIndex = iID - HT_PARAMTYPE_MONSTER_START + 1;

		bRes = g_ParamMgr.HT_bLockID( iID );
		if( bRes )
		{
			pMonsterData[iIndex].nTP = iIndex;
			pMonsterData[iIndex].snTribe = (short)iID;
			g_ParamMgr.HT_bGetMonsterTrimuriti( &pMonsterData[iIndex].byTrimuriti );
			g_ParamMgr.HT_bGetMonsterLevel(&pMonsterData[iIndex].byLevel );			
			g_ParamMgr.HT_bGetMonsterClass( &pMonsterData[iIndex].byClass1 ); // MOB.byClass1 = pMonsterData[MOB.nTP].byClass1;
			pMonsterData[iIndex].byClass2 = eTNCls2_Basic;
			if( 0 >= pMonsterData[iIndex].byClass1 ) pMonsterData[iIndex].byClass1 = eTNCls_Warrior;
			g_ParamMgr.HT_bGetMonsterSize( &pMonsterData[iIndex].byQuest[eMonPrty_Size] );

			// Sight
			g_ParamMgr.HT_bGetMonsterNormalSight( &pMonsterData[iIndex].byQuest[eMonPrty_NormalSight] );
			g_ParamMgr.HT_bGetMonsterCombatSight( &pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] );
			g_ParamMgr.HT_bGetMonsterCantDetect( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex = (short)iDummy;
			//pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex = (short)eTNEye_DetectVisibleOnly;

			// Move
			g_ParamMgr.HT_bGetMonsterMovement( &pMonsterData[iIndex].byQuest[eMonPrty_Movement] );
			g_ParamMgr.HT_bGetMonsterWalkSpeed( &iDummy );
			pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed] =(byte)iDummy;
			g_ParamMgr.HT_bGetMonsterRunSpeed( &iDummy );
			pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed] = (byte)iDummy;
			g_ParamMgr.HT_bGetMonsterBlockedCell( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex = (short)iDummy;

			// Pop Delay
			g_ParamMgr.HT_bGetMonsterPopDelayMin( &uiDummy );
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex = (short)uiDummy;
			g_ParamMgr.HT_bGetMonsterPopDelayMax( &uiDummy );
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex = (short)uiDummy;

			// Resistance
			g_ParamMgr.HT_bGetMonsterFireResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = (short)iDummy;			
			g_ParamMgr.HT_bGetMonsterColdResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = (short)iDummy;
			g_ParamMgr.HT_bGetMonsterLightningResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = (unsigned short)iDummy;
			g_ParamMgr.HT_bGetMonsterPoisonResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = (short)iDummy;

			
			// AI & Select Target
			g_ParamMgr.HT_bGetMonsterAI( &iDummy );
			pMonsterData[iIndex].byQuest[eMonPrty_AI] = (byte)iDummy;
			//if( 2920 == pMonsterData[iIndex].snTribe || 2921 == pMonsterData[iIndex].snTribe || 2922 == pMonsterData[iIndex].snTribe ) pMonsterData[iIndex].byQuest[eMonPrty_AI] = 3;

			g_ParamMgr.HT_bGetMonsterSelectTargetTime( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] );
			if( 0 >= pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] = 5;
			pMonsterData[iIndex].snKarma = pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] * 1000;
			if( 10000 < pMonsterData[iIndex].snKarma ) pMonsterData[iIndex].snKarma = 10000; // 최대 10초
			if( 1000 > pMonsterData[iIndex].snKarma ) pMonsterData[iIndex].snKarma = 1000; // 최소 1초
			g_ParamMgr.HT_bGetMonsterSelectTarget0( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] = 0;
			g_ParamMgr.HT_bGetMonsterSelectTarget1( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] = 0;
			g_ParamMgr.HT_bGetMonsterSelectTarget2( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] = 0;
			g_ParamMgr.HT_bGetMonsterSelectTarget3( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] = 0;
			pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly] = 1;
			if( (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3]) ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly] = 0; // 가장 가까운 위치의 적만 target으로 정함.

			// Speech
			g_ParamMgr.HT_bGetMonsterSpeechRate( &pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] );
			g_ParamMgr.HT_bGetMonsterSpeechAI( &pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] ) pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 0;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] ) pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] = 0;
			
			// Condition		
			g_ParamMgr.HT_bGetMonsterAggrCond( &pMonsterData[iIndex].byQuest[eMonPrty_AggrCond] );			
			g_ParamMgr.HT_bGetMonsterTraceCond( &pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] );
			g_ParamMgr.HT_bGetMonsterStepBackCond( &pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] ) pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] = 0;
			g_ParamMgr.HT_bGetMonsterHelpCond( &pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] );
			g_ParamMgr.HT_bGetMonsterHelpCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] );
			g_ParamMgr.HT_bGetMonsterLinkCond( &pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] );
			g_ParamMgr.HT_bGetMonsterLinkCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] );
			g_ParamMgr.HT_bGetMonsterFleeCond( &pMonsterData[iIndex].byQuest[eMonPrty_FleeCond] );
			g_ParamMgr.HT_bGetMonsterFleeCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_FleeCondCount] );

			g_ParamMgr.HT_bGetMonsterHP( &uiDummy ); // HP
			pMonsterData[iIndex].nHP = uiDummy;

			// Combat Factors
			pMonsterData[iIndex].sMuscle = pMonsterData[iIndex].sNerves = pMonsterData[iIndex].sHeart = pMonsterData[iIndex].sMind = 0;
			g_ParamMgr.HT_bGetMonsterAttackRate( &iDummy ); // AR
			pMonsterData[iIndex].sMuscle = (short)iDummy;
			g_ParamMgr.HT_bGetMonsterDodgeRate( &iDummy ); // DG
			pMonsterData[iIndex].sNerves = (short)iDummy;
			g_ParamMgr.HT_bGetMonsterAC( &iDummy ); // AC
			pMonsterData[iIndex].sHeart = (short)iDummy;
			if( 0 >= pMonsterData[iIndex].sHeart ) pMonsterData[iIndex].sHeart = 1;
			g_ParamMgr.HT_bGetMonsterEventNo( &uiDummy );
			pMonsterData[iIndex].snBagIndex = (short)uiDummy; // event
			g_ParamMgr.HT_bGetMonsterArmorType( &pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] ) pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] = 0;
			g_ParamMgr.HT_bGetMonsterHPRecovery( &pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] );
			g_ParamMgr.HT_bGetMonsterMuscle( &pMonsterData[iIndex].Equip[eMonPrty_DodgeSpeed].snIndex ); // 회피 속도, muscle field 사용

			// Immunity & Effect Delay
			g_ParamMgr.HT_bGetMonsterImmunity( &pMonsterData[iIndex].nGuildID ); // immunity
			g_ParamMgr.HT_bGetMonsterResistEffectConst( &pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] ) pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] = 0;
			//pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] = 10;

			// Reserved
			g_ParamMgr.HT_bGetMonsterReserve0( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved0] ); // family No
			g_ParamMgr.HT_bGetMonsterReserve1( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved1] ); // 적에게 붙어 있는 추격자(몬스터) 수가 이 수치를 넘어가면 선공하지 않는다.
			g_ParamMgr.HT_bGetMonsterReserve2( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved2] ); // Not Used, Aggr Score에 대한 index
			g_ParamMgr.HT_bGetMonsterReserve3( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] ); // 항상 client에 전송해서 나의 존재를 user들에게 알린다.
			g_ParamMgr.HT_bGetMonsterReserve4( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved4] ); // DebugFlag 상태, 1이면 log를 남긴다.
			g_ParamMgr.HT_bGetMonsterReserve5( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved5] ); // Action Lock 시간, 일반 몹은 1초이다.
			g_ParamMgr.HT_bGetMonsterReserve6( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved6] ); // 걸치기 반응 수행 여부(뚫고 지나가는 여부), 1이면 뚫고가고, 0이면 뚫고 가지 못한다.
			g_ParamMgr.HT_bGetMonsterReserve7( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved7] ); // boss는 1번 bit로 설정된다. guard는 2번 bit를 설정한다.


			// Skill Pattern
			g_ParamMgr.HT_bGetMonsterSkillPattern0( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 0;
			g_ParamMgr.HT_bGetMonsterSkillPattern1( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 0;
			g_ParamMgr.HT_bGetMonsterSkillPattern2( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 0;
			g_ParamMgr.HT_bGetMonsterSkillPattern3( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] );
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 0;	
			pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			if( (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3]) ) pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 1; // 기본 스킬만 등록되어 있는 경우	

			// Skill
			g_ParamMgr.HT_bGetMonsterSkill0( &iDummy );
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[0].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START; // 기본 무기를 나타낸다.
			g_ParamMgr.HT_bGetMonsterSkill1( &iDummy );
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[1].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[1].snIndex ) pMonsterData[iIndex].Equip[1].snIndex = pMonsterData[iIndex].Equip[0].snIndex;
			if( 0 >= pMonsterData[iIndex].Equip[0].snIndex ) pMonsterData[iIndex].Equip[0].snIndex = pMonsterData[iIndex].Equip[1].snIndex;
			g_ParamMgr.HT_bGetMonsterSkill2( &iDummy );
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[2].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[2].snIndex ) pMonsterData[iIndex].Equip[2].snIndex = pMonsterData[iIndex].Equip[0].snIndex;
			g_ParamMgr.HT_bGetMonsterSkill3( &iDummy );
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[3].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[3].snIndex ) pMonsterData[iIndex].Equip[3].snIndex = pMonsterData[iIndex].Equip[0].snIndex;
			g_ParamMgr.HT_bGetMonsterSkill4( &iDummy ); 
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[4].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[4].snIndex ) pMonsterData[iIndex].Equip[4].snIndex = 0; // pMonsterData[iIndex].Equip[0].snIndex;

			pMonsterData[iIndex].Equip[5].snIndex = 0;
			pMonsterData[iIndex].Equip[6].snIndex = 0;
			pMonsterData[iIndex].Equip[7].snIndex = 0;
			g_ParamMgr.HT_bGetMonsterSkill5( &iDummy ); 
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[5].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[5].snIndex ) pMonsterData[iIndex].Equip[5].snIndex = 0; // pMonsterData[iIndex].Equip[0].snIndex;
			g_ParamMgr.HT_bGetMonsterSkill6( &iDummy ); 
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[6].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[6].snIndex ) pMonsterData[iIndex].Equip[6].snIndex = 0; // pMonsterData[iIndex].Equip[0].snIndex;
			g_ParamMgr.HT_bGetMonsterSkill7( &iDummy ); 
			if( HT_PARAMTYPE_MONSTERSKILL_START > iDummy ) iDummy = HT_PARAMTYPE_MONSTERSKILL_START;
			pMonsterData[iIndex].Equip[7].snIndex = iDummy-HT_PARAMTYPE_MONSTERSKILL_START;
			if( 0 >= pMonsterData[iIndex].Equip[7].snIndex ) pMonsterData[iIndex].Equip[7].snIndex = 0; // pMonsterData[iIndex].Equip[0].snIndex;


			pMonsterData[iIndex].byQuest[eMonPrty_MaxRange]  = 0;
			//for( int mr = 0; mr < 7; ++mr )
			//{
			//	if( 0 >= pMonsterData[iIndex].Equip[mr].snIndex ) continue;
			//	int iSkillIndex = pMonsterData[iIndex].Equip[mr].snIndex + 500;				
			//	if( pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] < pSkillData[iSkillIndex].iRange )
			//	{
			//		pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] = pSkillData[iSkillIndex].iRange;
			//	}
			//}
			//if( 3 > pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] ) pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] = 3;
			

////////////////////////////////////////////////////////////////////////////////////////
			#ifdef __TN_LOCAL_SERVER_SWITCH__
			if( 2923 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 63;
			}
			#endif


			if( 2923 <= iID && 2950 >= iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] = 1; 
			}


			if( 2901 == iID || 2902 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] = 1; 
			}

			if( 2932 == iID || 2933 == iID || 2938 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 25;
			}

			if( 2945 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 25;
			}
			if( 2944 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 26;
			}
/*
			if( 2110 == iID )
			{
				pMonsterData[iIndex].Equip[1].snIndex = 3645;
				pMonsterData[iIndex].Equip[2].snIndex = 3973;
				pMonsterData[iIndex].Equip[3].snIndex = 3645;
				pMonsterData[iIndex].Equip[4].snIndex = 3645;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 1;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 2;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 34;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 35;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}
*/			

/*
			if( 2111 == iID || (2162<= iID && 2164 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}

			if( 2110 == iID || (2159<= iID && 2161 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}

			if( 2128 == iID || (2146<= iID && 2152 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}

			if( 2109 == iID || (2156<= iID && 2158 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}

			if( 2107 == iID || 2104 == iID || 2105 == iID ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
			}
*/
/*
			if( 2092 == iID ) // 천호
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 90;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] = 90;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1;
			}
			else if( 2094 == iID ) // 팽후
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 92;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] = 20;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1;
			}
			else if( 2090 == iID || 2091 == iID || 2095 == iID || 2096 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 91;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] = 90;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] = 1;
			}
*/
/*
			if( 2001 == iID || 2002 == iID ) 
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 90;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] =90;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1;
			}
			if( 2003 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 91;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] =90;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] = 1;
			}
*/
/*
			if( 2924 == iID || 2925 == iID || 2926 == iID ) // 
			{
				pMonsterData[iIndex].nHP = 10; //25만
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = 362;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = 362;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = 362;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = 362;
				pMonsterData[iIndex].sHeart = 689;
				//pMonsterData[iIndex].snBagIndex = 1;
				//pMonsterData[iIndex].Equip[0].snIndex = 3998;
			}
*/
/*
			if( 2113 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 34;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 35;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 36;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 37;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;

				//pMonsterData[iIndex].byQuest[eMonPrty_AI] = 35;
				//pMonsterData[iIndex].nHP = 200;
				//pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100;
				//pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] = 0;
			}


			if( 2112 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 21;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 22;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 24;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 25;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0;
				//pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100;
				//pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] = 0;
			}
*/
/*
			if( 2947 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 32;
				pMonsterData[iIndex].byClass1 = 19;
			}
			if( 2948 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 34;
				pMonsterData[iIndex].byClass1 = 19;
			}
			if( 2949 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 36;
				pMonsterData[iIndex].byClass1 = 19;
			}
			if( 2950 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 30;
				pMonsterData[iIndex].byClass1 = 19;
			}


			if( 2901 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 4;
			}
			if( 2933 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 3;
			}

			if( 2932 <= iID && 2950 >= iID )
			{				
				pMonsterData[iIndex].byQuest[eMonPrty_Movement] = 0;
				pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed] = 0;
				pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed] = 0;
				pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex = 0;
				pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100;
			}
*/

////////////////////////////////////////////////////////////////////////////////////////


			//---------------------------------------
			// Reward Prana, Braman, Gold
			//---------------------------------------
			g_ParamMgr.HT_bGetMonsterRewardBrahmanPoint( &uiDummy );
			pMonsterData[iIndex].nBramanPoint = (int)uiDummy;
			if( 0 >= pMonsterData[iIndex].nBramanPoint ) pMonsterData[iIndex].nBramanPoint = 0;			
			//pMonsterData[iIndex].nBramanPoint = (int)(pMonsterData[iIndex].nBramanPoint*dRwdBramanCorrect);

			g_ParamMgr.HT_bGetMonsterRewardPrana( &uiDummy );
			pMonsterData[iIndex].nPrana = (int)uiDummy;
			if( 0 >= pMonsterData[iIndex].nPrana ) pMonsterData[iIndex].nPrana = 0;			
			//pMonsterData[iIndex].nPrana = (int)(pMonsterData[iIndex].nPrana*dRwdPranaCorrect);
			
			g_ParamMgr.HT_bGetMonsterRewardGold( &uiDummy );
			pMonsterData[iIndex].nRupiah = (int)uiDummy;
			if( 0 >= pMonsterData[iIndex].nRupiah ) pMonsterData[iIndex].nRupiah = 0;			
			//pMonsterData[iIndex].nRupiah = (int)(pMonsterData[iIndex].nRupiah*dRwdGoldCorrect);
			int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( pMonsterData[iIndex].nRupiah );
			pMonsterData[iIndex].Inven[10].snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1;
			pMonsterData[iIndex].Inven[10].snDurability = eDur_Indestructible;
			pMonsterData[iIndex].Inven[10].byCount = 1;

			//-----------------------------
			// Reward Items
			//-----------------------------		
			int iMaxRate = 10000;
			g_ParamMgr.HT_bGetMonsterItem0ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[0].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[0].snDurability = pItemData[pMonsterData[iIndex].Inven[0].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[0].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[0].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[0].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[0].bySubRefine[i] = 0;				
				g_ParamMgr.HT_bGetMonsterItem0DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][0].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[0].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[0].snIndex = 0;
					g_krgRewardItemRate[iIndex][0].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[0].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem1ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[1].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[1].snDurability = pItemData[pMonsterData[iIndex].Inven[1].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[1].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[1].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[1].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[1].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem1DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][1].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[1].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[1].snIndex = 0;
					g_krgRewardItemRate[iIndex][1].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[1].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem2ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[2].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[2].snDurability = pItemData[pMonsterData[iIndex].Inven[2].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[2].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[2].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[2].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[2].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem2DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][2].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[2].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[2].snIndex = 0;
					g_krgRewardItemRate[iIndex][2].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[2].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem3ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[3].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[3].snDurability = pItemData[pMonsterData[iIndex].Inven[3].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[3].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[3].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[3].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[3].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem3DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][3].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[3].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[3].snIndex = 0;
					g_krgRewardItemRate[iIndex][3].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[3].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem4ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[4].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[4].snDurability = pItemData[pMonsterData[iIndex].Inven[4].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[4].byCount = 1; // pItemData[pMonsterData[iIndex].Inven[4].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[4].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[4].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem4DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][4].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[4].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[4].snIndex = 0;
					g_krgRewardItemRate[iIndex][4].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[4].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem5ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[5].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[5].snDurability = pItemData[pMonsterData[iIndex].Inven[5].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[5].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[5].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[5].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[5].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem5DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][5].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[5].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[5].snIndex = 0;
					g_krgRewardItemRate[iIndex][5].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[5].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem6ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[6].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[6].snDurability = pItemData[pMonsterData[iIndex].Inven[6].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[6].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[6].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[6].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[6].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem6DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][6].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[6].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[6].snIndex = 0;
					g_krgRewardItemRate[iIndex][6].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[6].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem7ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[7].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1;
				pMonsterData[iIndex].Inven[7].snDurability = pItemData[pMonsterData[iIndex].Inven[7].snIndex].sMaxDur;
				pMonsterData[iIndex].Inven[7].byCount = 1; //pItemData[pMonsterData[iIndex].Inven[7].snIndex].byMaxPackCount;
				pMonsterData[iIndex].Inven[7].byRefineLevel = 0;
				for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) pMonsterData[iIndex].Inven[7].bySubRefine[i] =0;				
				g_ParamMgr.HT_bGetMonsterItem7DropRate( &sDummy );
				sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
				g_krgRewardItemRate[iIndex][7].Init( sDummy, iMaxRate );
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[7].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[7].snIndex = 0;
					g_krgRewardItemRate[iIndex][7].Init( 0 );
				}
			}
			else pMonsterData[iIndex].Inven[7].snIndex = 0;

			g_ParamMgr.HT_bGetMonsterItem8Grade( &byDummy );
			pMonsterData[iIndex].Inven[8].snIndex = byDummy;
			g_ParamMgr.HT_bGetMonsterItem8DropRate( &sDummy );
			sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
			g_krgRewardItemRate[iIndex][8].Init( sDummy, iMaxRate );

			g_ParamMgr.HT_bGetMonsterItem9Grade( &byDummy );
			pMonsterData[iIndex].Inven[9].snIndex = byDummy;
			g_ParamMgr.HT_bGetMonsterItem9DropRate( &sDummy );
			sDummy = (short)(sDummy*g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
			g_krgRewardItemRate[iIndex][9].Init( sDummy, iMaxRate );

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[1024] = { 0,0,0, };
				sprintf(chBuf, "ID:%d, Lvl:%d, Trimu:%d, AI:%d, Class1:%d, BlockedCell:%d, HP:%d, AR:%d, DR:%d, AC:%d, Sight(%d,%d), CantDetect:%d, Movement:%d, MvSpeed(%d,%d), Resist(%d,%d,%d,%d), Size:%d, Speech(%d/%d), HPRecv:%d, Cond(%d,%d,%d), cond2(%d,%d,%d,%d,%d,%d), PopDelay(%d,%d), skill(%d,%d,%d,%d,%d,%d,%d,%d), sklPtrn(%d,%d,%d,%d / DefaultOnly:%d), SelectTarget(Time:%d, %d,%d,%d,%d / DefaultOnly:%d), Immu(%d,%d), ArmorType:%d, Event:%d\
							   \r\n\t RewPrana:%d, RewBraman:%d, RewGold:%d, RewItem0(%d,%d) RewItem1(%d,%d), RewItem2(%d,%d), RewItem3(%d,%d), RewItem4(%d,%d), RewItem5(%d,%d), RewItem6(%d,%d), RewItem7(%d,%d), RewItem8(%d,%d), RewItem9(%d,%d), Reserved(0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d) \r\n"
, pMonsterData[iIndex].snTribe, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].byClass1/*pMonsterData[iIndex].byQuest[eMonPrty_Class]*/, pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart
, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight], pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex, pMonsterData[iIndex].byQuest[eMonPrty_Movement], pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed], pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed]
, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
, pMonsterData[iIndex].byQuest[eMonPrty_Size], pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate], pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI], pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery]
, pMonsterData[iIndex].byQuest[eMonPrty_AggrCond], pMonsterData[iIndex].byQuest[eMonPrty_TraceCond], pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond]  // cond1
, pMonsterData[iIndex].byQuest[eMonPrty_HelpCond], pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount], pMonsterData[iIndex].byQuest[eMonPrty_LinkCond], pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount], pMonsterData[iIndex].byQuest[eMonPrty_FleeCond], pMonsterData[iIndex].byQuest[eMonPrty_FleeCondCount] // cond2
, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex // pop delay
, pMonsterData[iIndex].Equip[0].snIndex, pMonsterData[iIndex].Equip[1].snIndex, pMonsterData[iIndex].Equip[2].snIndex, pMonsterData[iIndex].Equip[3].snIndex, pMonsterData[iIndex].Equip[4].snIndex, pMonsterData[iIndex].Equip[5].snIndex, pMonsterData[iIndex].Equip[6].snIndex, pMonsterData[iIndex].Equip[7].snIndex // skill
, pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3], pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly]  // skill pattern
, pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3], pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly]  // select target
, pMonsterData[iIndex].nGuildID, pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst]
, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType], pMonsterData[iIndex].snBagIndex
, pMonsterData[iIndex].nPrana, pMonsterData[iIndex].nBramanPoint, pMonsterData[iIndex].nRupiah
, pMonsterData[iIndex].Inven[0].snIndex, g_krgRewardItemRate[iIndex][0].get_Rate()
, pMonsterData[iIndex].Inven[1].snIndex, g_krgRewardItemRate[iIndex][1].get_Rate()
, pMonsterData[iIndex].Inven[2].snIndex, g_krgRewardItemRate[iIndex][2].get_Rate()
, pMonsterData[iIndex].Inven[3].snIndex, g_krgRewardItemRate[iIndex][3].get_Rate()
, pMonsterData[iIndex].Inven[4].snIndex, g_krgRewardItemRate[iIndex][4].get_Rate()
, pMonsterData[iIndex].Inven[5].snIndex, g_krgRewardItemRate[iIndex][5].get_Rate()
, pMonsterData[iIndex].Inven[6].snIndex, g_krgRewardItemRate[iIndex][6].get_Rate()
, pMonsterData[iIndex].Inven[7].snIndex, g_krgRewardItemRate[iIndex][7].get_Rate()
, pMonsterData[iIndex].Inven[8].snIndex, g_krgRewardItemRate[iIndex][8].get_Rate()
, pMonsterData[iIndex].Inven[9].snIndex, g_krgRewardItemRate[iIndex][9].get_Rate()
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved0], pMonsterData[iIndex].byQuest[eMonPrty_Reserved1], pMonsterData[iIndex].byQuest[eMonPrty_Reserved2]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved3], pMonsterData[iIndex].byQuest[eMonPrty_Reserved4], pMonsterData[iIndex].byQuest[eMonPrty_Reserved5]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved6], pMonsterData[iIndex].byQuest[eMonPrty_Reserved7]

);

				WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" );
			}
			#endif

		}
		g_ParamMgr.HT_bUnLockID( iID );
	}

	for( int i = 0; i < MAX_SKILL; ++i ) pMonsterData[0].byQuest[i] = 0;
	pMonsterData[0].byTrimuriti = eTNClan_Neutral;
	pMonsterData[0].nHP = 0;
	pMonsterData[0].sMuscle = pMonsterData[0].sNerves = pMonsterData[0].sHeart = pMonsterData[0].sMind = 0;
	pMonsterData[0].snSaveX = 0;
	pMonsterData[0].snSaveZ = 1;
	pMonsterData[0].snBagIndex = 0;
	pMonsterData[0].nTP = 0; // event
	for( int i = 0; i < MAX_EQUIP; ++i )  pMonsterData[0].Equip[i].snIndex = 0; // skill
	pMonsterData[0].nPrana = 0;
	for( int i = 0; i < MAX_INVEN; ++i )  pMonsterData[0].Inven[i].snIndex = 0; // reward

}

int GetEmptyInven(int conn)
{
	if(conn<1 || conn>MAX_USER) return MAX_INVEN;

	int snIndex=0;	BYTE byCount=0;
	for(int i=0; i<pMob[conn].byMaxInven; i++)
	{	byCount=pMob[conn].MOB.Inven[i].byCount;
		snIndex=pMob[conn].MOB.Inven[i].snIndex;
		
		if(snIndex<0 || snIndex>=MAX_ITEM_DATA || byCount<=0) ZeroMemory(&pMob[conn].MOB.Inven[i], sizeof(STRUCT_ITEM));
		if(pMob[conn].MOB.Inven[i].snIndex == 0) return i;
	}

	return MAX_INVEN;
}

int GetEmptyCargo(int conn)
{
	if(conn<1 || conn>MAX_USER) return MAX_CARGO;

	int snIndex=0;	BYTE byCount=0;
	for(int i=0; i<MAX_CARGO; i++)
	{	byCount=pUser[conn].Cargo[i].byCount;
		snIndex=pUser[conn].Cargo[i].snIndex;
		
		if(snIndex<0 || snIndex>=MAX_ITEM_DATA || byCount<=0) ZeroMemory(&pUser[conn].Cargo[i], sizeof(STRUCT_ITEM));
		if(pUser[conn].Cargo[i].snIndex == 0) return i;
	}

	return MAX_CARGO;
}

int RefiningItem(int nID, STRUCT_ITEM* pSour, STRUCT_ITEM** pDest)
{
	//	확률 미적용상태.

	short snSour = (pSour->snIndex)+HT_PARAMTYPE_ITEM_START-1; 
	short snDest[3] = {0,};
	for(int i=0;i<3; i++) 
	{	if( pDest[i]==NULL) continue;
		snDest[i] = (pDest[i]->snIndex)+HT_PARAMTYPE_ITEM_START-1; 
	}
	bool bChecked = false;

	if(snDest[0]==eItem_amala)
	{	ZeroMemory(pSour->bySubRefine, MAX_SUBMATERIALSIZE);
		ZeroMemory(pDest[0], sizeof(STRUCT_ITEM));
		return REPLY_ITEM_SUBREFINING_INITIALIZE;
	}	else
	{	
		bChecked = bRefiningCheckPart(snSour, snDest[0]);
	}

	if(snDest[1]==eItem_apad)
	{
		if(bChecked)		//	아파드는 아이템부위 제한이 걸린 보조재료에 대해서만 사용이 가능하다
			return REPLY_ITEM_REFINING_FAIL;

		int nIndex = 0;
		DWORD dwSubItem=snDest[0]-HT_PARAMTYPE_ITEM_REFINE_SUB_START+1; DWORD dwTot=0;
		if(dwSubItem<1 || dwSubItem>9) return REPLY_ITEM_REFINING_FAIL;	//	라가마니 ~ 아즈나까지 대역의 보조재련재료만 사용이 가능하다.

		for(nIndex=0; nIndex<MAX_SUBMATERIAL; nIndex++)
		{	
			dwTot=pSour->bySubRefine[nIndex/2];

			if(nIndex%2==0)
			{	dwTot = pSour->bySubRefine[nIndex/2]&0x0F;	//	상위4비트 초기화
				dwTot |= (dwSubItem<<4);
			}	else
			{	dwTot = pSour->bySubRefine[nIndex/2]&0xF0;	//	하위4비트 초기화
				dwTot |= dwSubItem;
			}

			pSour->bySubRefine[nIndex/2] = (BYTE)dwTot;
		}

		for(int i=0; i<3; i++)
		{	if( pDest[i]==NULL) continue;
			ZeroMemory(pDest[i], sizeof(STRUCT_ITEM));
		}

		return 0;
	}
	else
	{
        if(!bChecked )		//	아파드가 아닐경우 아이템부위 제한이 걸린 보조재료는 사용할 수 없다.
			return REPLY_ITEM_REFINING_FAIL;	
	}

	BYTE	byMainLevel = 0;			//	주재련레벨보정
	int		iPlusRate = 0;				//	성공확률 +
	float	fMultipleRate = 1.0;		//	성공확률 *
	bool	bProtectItem	= false;	//	아이템 소멸방지
	bool	bProtectSubItem = false;	//	제련재료 소멸방지
	bool	bJade			= false;	//	자드속성
	if(pDest[1] != NULL)
	{
		TNSKILL_DATA* pkSkill = (TNSKILL_DATA*)&pItemData[pDest[1]->snIndex];

		for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
		{
			if( 0 >= pkSkill->krgEffect[i].iID ) continue;
			switch( pkSkill->krgEffect[i].iID )
			{
			case eTNAfn_RefiningJade :
				{
					bJade = true;	
				}	break;
			case eTNAfn_RefiningRateUp :
				{
					iPlusRate += pkSkill->krgEffect[i].iParam1;
					fMultipleRate += (float)(pkSkill->krgEffect[i].iParam2/100.0);
				}	break;
			case eTNAfn_RefiningProtect :
				{
					bProtectSubItem = true;
				}	break;
			default:
				break;
			}
		}
	}

	for(int i=0; i<3; i++)
	{	if( pDest[i]==NULL) continue;
		if(i==0 && bProtectSubItem) continue;
		ZeroMemory(pDest[i], sizeof(STRUCT_ITEM));
	}

	BYTE byRes=0; int nRate = 0;
	if(CHTParamIDCheck::HT_bIsItemRefineMain(snDest[0]))	//	무기주제련
	{	BYTE byLevel = pSour->byRefineLevel + 1;
		if(byLevel > MAX_MAINREFINELEVEL)	return REPLY_ITEM_REFINING_OVER;

		int nSubIndex = snDest[0]-HT_PARAMTYPE_ITEM_REFINE_MAIN_START+1;
		//for(int i=0; i<3; i++)
		//{	if(pDest[i]==NULL) continue;
		//	ZeroMemory(pDest[i], sizeof(STRUCT_ITEM));
		//}

		nRate = (int)((REFINE_MAIN[nSubIndex-1][pSour->byRefineLevel]+g_ItemRefineScale/2000+g_ItemRefineGMScale+iPlusRate)*fMultipleRate);
		if(nRate > 100) nRate = 100;
		if(nRate < 0) nRate = 0;

		byRes = (BYTE)g_RefineTable.GetValue(nRate);

		//char pData[256] = {0,};
		//sprintf(pData, "Main Refine level:%d->%d, Rate:%d, subrate1:%d subrate2:%d result:%d\r\n", pSour->byRefineLevel, pSour->byRefineLevel+1, REFINE_MAIN[nSubIndex-1][pSour->byRefineLevel], g_ItemRefineScale/2000, g_ItemRefineGMScale, byRes);
		//WriteLog(pData, ".\\Event\\[Log]Refining.txt");

		if(byRes)
		{	pSour->byRefineLevel = byLevel;
		}
		else
		{	if(pSour->byRefineLevel>=REFINE_INITIALIZE_LEVEL && pSour->byRefineLevel<REFINE_DISAPEAR_LEVEL)
			{	if(bJade) return REPLY_ITEM_REFINING_FAIL;									//	첨가제가 자드면 레벨유지
				pSour->byRefineLevel = 0;
				return REPLY_ITEM_REFINING_INITIALIZE;
			}	else
			if(pSour->byRefineLevel >= REFINE_DISAPEAR_LEVEL)
			{	if(bJade) { pSour->byRefineLevel = 6; return REPLY_ITEM_REFINING_FAIL; }	//	첨가제가 자드면 6으로 초기화
				ZeroMemory(pSour, sizeof(STRUCT_ITEM));
				return REPLY_ITEM_REFINING_DISAPPEAR;
			}	else return REPLY_ITEM_REFINING_FAIL;
		}
	}
	else if(CHTParamIDCheck::HT_bIsItemRefineSub(snDest[0]))
	{	int nIndex = 0;
		DWORD dwSubItem=snDest[0]-HT_PARAMTYPE_ITEM_REFINE_SUB_START+1; DWORD dwTot=0;

		for(nIndex=0; nIndex<MAX_SUBMATERIAL; nIndex++)
		{	BYTE byTot=pSour->bySubRefine[nIndex/2]; BYTE bySubItem=0;
			if(nIndex%2==0)
			{	bySubItem = byTot>>4;	//	상위4비트 리드
			}	else
			{	bySubItem = byTot&0x0F;	//	하위4비트 리드
			} 

			if(bySubItem == 0) break;
		}
		if(nIndex >= MAX_SUBMATERIAL && (dwSubItem<24 || dwSubItem>=33))	return REPLY_ITEM_REFINING_OVER;

		nRate = (int)((REFINE_SUB[nIndex]+g_ItemRefineScale/2000+g_ItemRefineGMScale+iPlusRate)*fMultipleRate);
		if(nRate > 100) nRate = 100;
		if(nRate < 0) nRate = 0;

		byRes = (BYTE)g_RefineTable.GetValue(nRate);

		if(dwSubItem>=20 && dwSubItem<24)		//	6620 ~ 6623 가짜아이템(카질라,프락티,마뉴,바하바)
		{	dwSubItem -= 19;	//	카질라 => 라가마니(6601), 프락티 => 닐라마니(6602)
			byRes = true;
		}
		else if(dwSubItem>=24 && dwSubItem<33)	//	6624 ~ 6632 타루 제련
		{
			DWORD dwTaruSubItem = dwSubItem - 23;		//	타루 라가마니 => 라가마니
			DWORD dwTaruSubItem2 = dwTaruSubItem;
			for(int i=0; i<nIndex; i++)
			{	BYTE byTot=pSour->bySubRefine[i/2]; BYTE bySubItem=0;
				if(i%2==0)
				{	bySubItem = pSour->bySubRefine[i/2]>>4;
					if(bySubItem>=10 && bySubItem<14 && dwTaruSubItem>=1 && dwTaruSubItem<5)	//	엔시리즈는 엔시리즈로 바뀐다
					{	dwTaruSubItem2 += 9;								//	
					}
					dwTot = pSour->bySubRefine[i/2]&0x0F;	//	상위4비트 초기화
					dwTot |= (dwTaruSubItem2<<4);
				}	else
				{	bySubItem = pSour->bySubRefine[i/2]&0x0F;
					if(bySubItem>=10 && bySubItem<14 && dwTaruSubItem>=1 && dwTaruSubItem<5)	//	엔시리즈는 엔시리즈로 바뀐다
					{	dwTaruSubItem2 += 9;								//	
					}
					dwTot = pSour->bySubRefine[i/2]&0xF0;	//	하위4비트 초기화
					dwTot |= dwTaruSubItem2;
				}

				pSour->bySubRefine[i/2] = (BYTE)dwTot;
				dwTaruSubItem2 = dwTaruSubItem;
			}
			return 0;
		}

		if(byRes)
		{	if(nIndex%2==0)
			{	dwTot = pSour->bySubRefine[nIndex/2]&0x0F;	//	상위4비트 초기화
				dwTot |= (dwSubItem<<4);
			}	else
			{	dwTot = pSour->bySubRefine[nIndex/2]&0xF0;	//	하위4비트 초기화
				dwTot |= dwSubItem;
			}

			pSour->bySubRefine[nIndex/2] = (BYTE)dwTot;
		}	else 
		{	return REPLY_ITEM_REFINING_FAIL;
		}
	}	else return REPLY_ITEM_REFINING_FAIL;
	
	return 0;
}

bool bRefiningCheckPart(short snSour, short snDest)
{
	int iRefinable = 0;
	g_ParamMgr.HT_bGetItemRefinableItemType( snDest, &iRefinable);

	if ( CHTParamIDCheck::HT_bIsItemWeaponOneHand( snSour ) )			// One hand 무기일때
	{	if ( (iRefinable & _REFINE_WEPON_ONEHAND) == 0 ) return false;
	}	else 
	if ( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( snSour ) || CHTParamIDCheck::HT_bIsItemWeaponThrow( snSour ))
	{	if ( (iRefinable & _REFINE_WEPON_TWOHAND) == 0 ) return false;	// Two hand 무기일때(활포함)
	}	else 
	if ( CHTParamIDCheck::HT_bIsItemDefenceArmor( snSour ) )			// 갑옷일때
	{	if ( (iRefinable & _REFINE_DEFENCE_ARMOR) == 0 ) return false;
	}	else
	if ( CHTParamIDCheck::HT_bIsItemDefencePants( snSour ) )			// 바지일때
	{	if ( (iRefinable & _REFINE_DEFENCE_PANTS) == 0 ) return false;
	}	else
	if ( CHTParamIDCheck::HT_bIsItemDefenceGloves( snSour ) )			// 장갑일때
	{   if ( (iRefinable & _REFINE_DEFENCE_GLOVES) == 0 ) return false;
	}	else
	if ( CHTParamIDCheck::HT_bIsItemDefenceShield( snSour ) )			// 방패일때
	{	if ( (iRefinable & _REFINE_DEFENCE_SHIELD) == 0 ) return false;
	}	else 
	if ( CHTParamIDCheck::HT_bIsItemDefenceBelt( snSour ) )				// 벨트일때
	{	if ( (iRefinable & _REFINE_DEFENCE_BELT) == 0 ) return false;
	}	else 
	if ( CHTParamIDCheck::HT_bIsItemDefenceShoes( snSour ) )			// 신발일때
	{	if ( (iRefinable & _REFINE_DEFENCE_SHOES) == 0 ) return false;
	}	else 
	if ( CHTParamIDCheck::HT_bIsItemDefenceHelmet( snSour ) )			// 모자일때
	{	if ( (iRefinable & _REFINE_DEFENCE_HELMET) == 0 ) return false;
	}	else
	if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( snSour ) )
	{	if ( (iRefinable & _REFINE_ACCESSORY_NECKLACE) == 0 ) return false;
	}
	//	else
	//if( CHTParamIDCheck::HT_bIsItemDefencePants( snSour ) )				// 바지일때
	//{	if ( (iRefinable & eItemPants) == 0 ) return REPLY_ITEM_REFINING_ERROR;
	//	bChecked = true;
	//}	else
	//if(  CHTParamIDCheck::HT_bIsItemDefenceGloves( snSour ) )			// 투구일때
	//{	if ( (iRefinable & eItemHelmet) == 0 ) return REPLY_ITEM_REFINING_ERROR;
	//	bChecked = true;
	//}

	return true;
}

void ExchangeTrade(int nSource, int nTarget)
{
	int nIndex = 0;
	for (int i=0;i<MAX_TRADE;i++)
	{	int nIndex = pUser[nSource].Trade.InvenPos[i];

		//	아이템의 삭제
		if(pUser[nSource].Trade.Item[i].snIndex!=0)
		{	nIndex = pUser[nSource].Trade.InvenPos[i];
			//if	(nIndex<0 || nIndex>=pMob[nSource].byMaxInven) continue;
			if	(nIndex==-1) continue;

			S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
			sm.byPlace = ITEM_PLACE_INVEN; sm.byIndex = nIndex;
			sm.sitem = pMob[nSource].MOB.Inven[nIndex]; sm.byType = SET_ITEM_DELETE;
			pUser[nSource].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
			memset(&(pMob[nSource].MOB.Inven[nIndex]),0,sizeof(STRUCT_ITEM));
		}
		if(pUser[nTarget].Trade.Item[i].snIndex!=0)
		{	nIndex = pUser[nTarget].Trade.InvenPos[i];
			if	(nIndex==-1) continue;
			S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
			sm.byPlace = ITEM_PLACE_INVEN; sm.byIndex = nIndex;
			sm.sitem = pMob[nTarget].MOB.Inven[nIndex];	sm.byType = SET_ITEM_DELETE;
			pUser[nTarget].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
			memset(&(pMob[nTarget].MOB.Inven[nIndex]),0,sizeof(STRUCT_ITEM));
		}

		//	아이템의 추가
		if(pUser[nSource].Trade.Item[i].snIndex!=0)
		{	nIndex = GetEmptyInven(nTarget);
			if(nIndex<0 || nIndex>=pMob[nTarget].byMaxInven) continue;
			S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
			sm.byPlace = ITEM_PLACE_INVEN; sm.byIndex = nIndex;
			sm.sitem = pUser[nSource].Trade.Item[i]; sm.byType = SET_ITEM_CREATE;
			pUser[nTarget].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
			pMob[nTarget].MOB.Inven[nIndex] = pUser[nSource].Trade.Item[i];
		}
		if(pUser[nTarget].Trade.Item[i].snIndex!=0)
		{	nIndex = GetEmptyInven(nSource);
			if(nIndex<0 || nIndex>=pMob[nSource].byMaxInven) continue;
			S_SCP_RESP_ITEM_SET sm; sm.wType = SCP_RESP_ITEM_SET;		
			sm.byPlace = ITEM_PLACE_INVEN; sm.byIndex = nIndex;
			sm.sitem = pUser[nTarget].Trade.Item[i];	sm.byType = SET_ITEM_CREATE;
			pUser[nSource].cSock.AddMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SET));
			pMob[nSource].MOB.Inven[nIndex] = pUser[nTarget].Trade.Item[i];
		}
	}

	ZeroMemory(&(pUser[nSource].Trade), sizeof(MSG_Trade));
	ZeroMemory(&(pUser[nTarget].Trade), sizeof(MSG_Trade));
}


void LoadWorldSettings()
{
	char szFileName[512] = { ".\\Data\\WorldSettings.ini" };
	char szInBuf[20] = { 0,0,0, };

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Item"), _T("StaffCorrect"), _T("200"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_StaffCorrect] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Item"), _T("StaffMaxNerves"), _T("350"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_StaffMaxNerves] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Skill"), _T("AbsorbMax"), _T("50"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AbsorbMax] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Skill"), _T("ReflectMax"), _T("150"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_ReflectMax] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("SpeedMin"), _T("400"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_SpeedMin] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("SpeedMax"), _T("25000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_SpeedMax] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("HPRecvMax"), _T("500"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_HPRecvMax] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("TPRecvMax"), _T("400"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_TPRecvMax] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("ResistMax"), _T("120"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_ResistMax] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Property"), _T("HeartMax"), _T("400"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_HeartMax] = atoi( szInBuf );

	
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Time"), _T("ProtectFromPK"), _T("15000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_ProtectionFromPK] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Time"), _T("RwdPriority"), _T("25000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_PriorityTime] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Time"), _T("TownPortal"), _T("5000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_TownPortalTime] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Time"), _T("AdvTownPortal"), _T("5000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AdvTownPortalTime] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );

	g_irgSetting[eCnst_QuitTime] = 15000;
	GetPrivateProfileString( _T("Time"), _T("Quit"), _T("7000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_QuitTime] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Time"), _T("KalaCore"), _T("1800000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_KalaCoreDur] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("Restriction"), _T("20"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_Restriction] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("RwdBramanPoint"), _T("50"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_RwdBramanPoint] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("DecKarmaPoint"), _T("25"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_DecKarmaPoint] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("RwdKarmaPoint"), _T("100"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_RwdKarmaPoint] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("IncKarmaPoint"), _T("600"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_IncKarmaPoint] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("RwdGold"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_RwdGold] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("LoseGold"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_LoseGold] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("MaxKarma"), _T("30000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_MaxKarma] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("MurderDropRate"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_MurderDropRate] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("InnocentDropRate"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_InnocentDropRate] = atoi( szInBuf );	
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("FirstStrikerDropRate"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_FirstStrikerDropRate] = atoi( szInBuf );	
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("HuntHigh"), _T("5"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_HuntHigh] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("HuntLow"), _T("1"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_HuntLow] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("FirstStrikeDur"), _T("180000"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_FirstStrikeDur] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("PK"), _T("KarmaForRestrictingToAttack"), _T("1800"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_KarmaForRestrictingToAttack] = atoi( szInBuf );

	// KilledByMonster
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("KilledByMonster"), _T("LosePrana"), _T("5"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_PenaltyByKilled] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("KilledByMonster"), _T("LoseBP"), _T("25"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_PenaltyBPByKilled] = atoi( szInBuf );

	
	// Siege
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiegeSupport"), _T("1000000"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_FeeForSiegeSupport] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege1"), _T("12000000"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_FeeForSiege1] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege2"), _T("10000000"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_FeeForSiege2] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege3"), _T("8000000"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_FeeForSiege3] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("ItemCount"), _T("10"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_ItemCount] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("MemberLevel"), _T("60"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_MemberLevel] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("MemberCount1"), _T("5"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_MemberCount1] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Siege"), _T("MemberCount2"), _T("5"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_MemberCount2] = atoi( szInBuf );
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Version"), _T("Ver"), _T("0.0.0.0"), szInBuf, 10, szFileName );
	sscanf(szInBuf, "%d.%d.%d.%d", &g_snVersion[0], &g_snVersion[1], &g_snVersion[2], &g_snVersion[3]);

	//// Height
	//memset( szInBuf, 0, 20 );
	//GetPrivateProfileString( _T("Height"), _T("Obstacle  "), _T("100"), szInBuf, 16, szFileName );
	//g_irgSetting[eCnst_ObstacleHeight] = atoi( szInBuf );

	//memset( szInBuf, 0, 20 );
	//GetPrivateProfileString( _T("Height"), _T("Character  "), _T("400"), szInBuf, 16, szFileName );
	//g_irgSetting[eCnst_CharacterHeight] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Hack"), _T("SkillCastInterval"), _T("15"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_SkillCastIntervalHack] = atoi( szInBuf );


	for( int i = 0; i < MAX_SETTING; ++i )
	{
		char chBuf[512] = { 0,0,0, };
	
		sprintf(chBuf, "%d> %d \r\n", i, g_irgSetting[i] );
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadWorldSettings.txt" );
	}
}


void LoadZoneSettings()
{
	char szFileName[512] = { ".\\Data\\Settings.ini" };
	//wsprintf( szFileName, ".\\Data\\Settings.ini" );
	char szCountry[64] = { 0,0,0, };
	GetPrivateProfileString( _T("Country"), _T("Name"), _T("Korea"), szCountry, 64, szFileName );
    strupr( szCountry );
	if		( strncmp( szCountry, "KOREA", 64 ) == 0 ) g_eCountryID = eCountryKorea;
	else if ( strncmp( szCountry, "CHINA", 64 ) == 0 ) g_eCountryID = eCountryChina;
	else if ( strncmp( szCountry, "JAPAN", 64 ) == 0 ) g_eCountryID = eCountryJapan;
	else if ( strncmp( szCountry, "INDONESIA", 64 ) == 0 ) g_eCountryID = eCountryIndonesia;
	else if ( strncmp( szCountry, "PHILIPPINES", 64 ) == 0 ) g_eCountryID = eCountryPhilippines;
	else if ( strncmp( szCountry, "TAIWAN", 64 ) == 0 ) g_eCountryID = eCountryTaiwan;

	char szInBuf[20] = { 0,0,0, };
	GetPrivateProfileString( _T("Zone"), _T("ID"), _T("1"), szInBuf, 10, szFileName );
	g_iZoneID = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Zone"), _T("Type"), _T("0"), szInBuf, 10, szFileName );
	g_iZoneType = atoi( szInBuf ); // default는 일반존이다.

	// Country
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Country"), _T("PK"), _T("1"), szInBuf, 10, szFileName );
	int iPK = atoi( szInBuf );
	if( 0 == iPK ) g_iSwitch = g_iSwitch | eTNSwitch_PKDisable;

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Country"), _T("MonsterSpeech"), _T("1"), szInBuf, 10, szFileName );
	int iMonsterSpeech = atoi( szInBuf );
	if( 0 == iMonsterSpeech ) g_iSwitch = g_iSwitch | eTNSwitch_MonsterSpeechDisable;

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Country"), _T("AttackSpeedHack"), _T("1500"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AttackSpeedHack] = atoi( szInBuf );
	
	// World
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("World"), _T("ID"), _T("1"), szInBuf, 10, szFileName );
	g_iWorldID = atoi( szInBuf );

	// Version
	if(g_eCountryID!=eCountryKorea)
	{
		memset( szInBuf, 0, 20 );
		GetPrivateProfileString( _T("Version"), _T("Ver"), _T("0.0.0.0"), szInBuf, 10, szFileName );
		sscanf(szInBuf, "%d.%d.%d.%d", &g_snVersion[0], &g_snVersion[1], &g_snVersion[2], &g_snVersion[3]);
	}

	// Allowed Level
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("AllowedLevel"), _T("Low"), _T("0"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AllowedLevelLow] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("AllowedLevel"), _T("High"), _T("100"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AllowedLevelHigh] = atoi( szInBuf );

	// Height
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Height"), _T("Obstacle"), _T("100"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_ObstacleHeight] = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Height"), _T("Character"), _T("500"), szInBuf, 16, szFileName );
	g_irgSetting[eCnst_CharacterHeight] = atoi( szInBuf );


	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Correct"), _T("RwdPrana"), _T("100"), szInBuf, 10, szFileName );
	int iRwdPranaCorrect = atoi( szInBuf );
	
	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Correct"), _T("RwdRateForNormalItem"), _T("100"), szInBuf, 10, szFileName );
	int iRwdItemCorrect = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Correct"), _T("RwdGold"), _T("100"), szInBuf, 10, szFileName );
	int iRwdGoldCorrect = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Correct"), _T("RwdBraman"), _T("100"), szInBuf, 10, szFileName );
	int iRwdBramanCorrect = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("VisualRange"), _T("HalfGrid"), _T("32"), szInBuf, 10, szFileName );
	int iHalfGrid = atoi( szInBuf );
	if( 0 < iHalfGrid )
	{		
		g_iHalfGridX = g_iHalfGridY = iHalfGrid;
		g_iViewGridX = g_iViewGridY = iHalfGrid + iHalfGrid + 1;
	}

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("Log"), _T("MonsterLevel"), _T("60"), szInBuf, 10, szFileName );
	g_iMonsterLevelForWritingLog = atoi( szInBuf );
	if( 0 >= g_iMonsterLevelForWritingLog ) g_iMonsterLevelForWritingLog = 60;

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("GiftItem"), _T("ItemIndex"), _T("0"), szInBuf, 10, szFileName );
	int nItemIndex = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("GiftItem"), _T("ItemCount"), _T("0"), szInBuf, 10, szFileName );
	int nItemCount = atoi( szInBuf );

	memset( szInBuf, 0, 20 );
	GetPrivateProfileString( _T("GiftItem"), _T("ItemGenTime"), _T("0"), szInBuf, 10, szFileName );
	int nItemGenTime = atoi( szInBuf );

	g_nItemCashType = GetPrivateProfileInt( _T("ItemCash"), _T("CashType"), 0, szFileName );

	ChangeRwdCorrect( eRwd_Base, iRwdPranaCorrect, iRwdGoldCorrect, iRwdBramanCorrect, iRwdItemCorrect );

	//g_drgRwdCorrect[eRwd_Braman][eRwd_Total] = iRwdBramanCorrect;
	//g_drgRwdCorrect[eRwd_Prana][eRwd_Total] = iRwdPranaCorrect;
	//g_drgRwdCorrect[eRwd_Gold][eRwd_Total] = iRwdGoldCorrect;
	//g_drgRwdCorrect[eRwd_Item][eRwd_Total] = iRwdItemCorrect;
	//if( 0 >= g_drgRwdCorrect[eRwd_Braman][eRwd_Total] ) g_drgRwdCorrect[eRwd_Braman][eRwd_Total] = 100;
	//if( 0 >= g_drgRwdCorrect[eRwd_Prana][eRwd_Total] ) g_drgRwdCorrect[eRwd_Prana][eRwd_Total] = 100;
	//if( 0 >= g_drgRwdCorrect[eRwd_Gold][eRwd_Total] ) g_drgRwdCorrect[eRwd_Gold][eRwd_Total] = 100;
	//if( 0 >= g_drgRwdCorrect[eRwd_Item][eRwd_Total] ) g_drgRwdCorrect[eRwd_Item][eRwd_Total] = 100;
	//g_drgRwdCorrect[eRwd_Braman][eRwd_Total] /= 100;
	//g_drgRwdCorrect[eRwd_Prana][eRwd_Total] /= 100;
	//g_drgRwdCorrect[eRwd_Gold][eRwd_Total] /= 100;
	//g_drgRwdCorrect[eRwd_Item][eRwd_Total] /= 100;

	g_nGiftItemIndex = nItemIndex;
	g_nGiftItemMaxCount = nItemCount;
	g_nGiftItemCount = g_nGiftItemMaxCount;
	g_nGiftItemFirstCount = g_nGiftItemMaxCount; 
	g_snGiftItemGenTime = nItemGenTime;

	if( g_nGiftItemMaxCount < 0) g_snGiftItemGenTime = 0;
	if( g_snGiftItemGenTime < 0 ) g_snGiftItemGenTime = 0;
	g_snGiftItemGenTime *= (1000/TICKSIZE);
	if(g_snGiftItemGenTime>0)
	{	ZeroMemory(&GiftItem, sizeof(GiftItem));
		
		bool bRet = true; short sMaxDur = 0;
		bRet &= g_ParamMgr.HT_bGetItemMaxDurability	(g_nGiftItemIndex, &sMaxDur);
		if(bRet)
		{	GiftItem.snIndex = g_nGiftItemIndex - HT_PARAMTYPE_ITEM_START + 1;
			GiftItem.snDurability = sMaxDur;
			GiftItem.byCount = 1; 
			GiftItem.byRefineLevel = 0;
			for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) GiftItem.bySubRefine[i] = 0;
		}	else
		{	g_snGiftItemGenTime = 0;
		}
	}

	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[Load Settings.ini] ZoneID:%d, WorldID:%d, ViewGrid(%d,%d), HalfGrid(%d,%d), PranaCorrect:%f, GoldCorrect:%f, BramanCorrect:%f \r\n\r\n", g_iZoneID, g_iWorldID, g_iViewGridX, g_iViewGridY, g_iHalfGridX, g_iHalfGridY, g_drgRwdCorrect[eRwd_Prana][eRwd_Total], g_drgRwdCorrect[eRwd_Gold][eRwd_Total], g_drgRwdCorrect[eRwd_Braman][eRwd_Total] );
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
	}


	sprintf(szFileName, ".\\Data\\Zone%d.ini", g_iZoneID);
	GetPrivateProfileString( _T("Arena"), _T("Money"), _T("0"), szInBuf, 15, szFileName );
	g_dwArenaMoney = atoi( szInBuf );

	GetPrivateProfileString( _T("Castle"), _T("SalesRate"), _T("0"), szInBuf, 15, szFileName );
	g_byCastleSalesRate = atoi( szInBuf );

	GetPrivateProfileString( _T("Castle"), _T("SalesMoney"), _T("0"), szInBuf, 15, szFileName );
	g_dwCastleSalesMoney = atoi( szInBuf );

	GetPrivateProfileString( _T("Castle"), _T("EraseDay"), _T("0"), szInBuf, 15, szFileName );
	g_dwRentalEraseDay = atoi( szInBuf );

	GetPrivateProfileString( _T("Castle"), _T("RentalTex"), _T("0"), szInBuf, 15, szFileName );
	g_byRentalTex = atoi( szInBuf );

	GetPrivateProfileString( _T("Castle"), _T("RentalTexMoney"), _T("0"), szInBuf, 15, szFileName );
	g_dwRentalTexMoney = atoi( szInBuf );

	if(g_eCountryID == eCountryJapan)
	{
		memset( szInBuf, 0, 20 );
		GetPrivateProfileString( _T("Challenge"), _T("Money"), _T("0"), szInBuf, 16, szFileName );
		g_dwChallengeMoney = (DWORD)atoi( szInBuf );
	}
	else
	{	g_dwChallengeMoney = MONEY_OF_CHALLENGE;
	}
}


void LoadSpeechComment()
{
	FILE* fp;
	fp = fopen( "EventTask.txt", "rt" );
	if(NULL == fp )
	{
		assert( !"Can't open ./EventTask.txt file" );
		exit(0);
	}

	char szLine[1024] = { 0,0,0, };
	while(1)
	{	char* szRes = fgets( (char*)szLine, 255, fp );
		if( NULL == szRes ) break;
	
		if( '/' != szLine[0] ) continue;
	    
		char szID[8] = { 0,0,0, };
		char szArguments[512] = { 0,0,0, };
	    
		sscanf( szLine, "%s %s", szID, szArguments );    
		int iCmmID = atoi( szID );
		if( 0 < iCmmID && eTNSpch_MaxCommentCount > iCmmID )
		{
			memcpy( g_szrgComment[iCmmID], szArguments, sizeof(szArguments) );

			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- iCmmID:%d, szComment:%s \r\n", iCmmID, g_szrgComment[iCmmID] );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" );
			}
		}
	}	

	fclose( fp );
}



void LoadEventTask()
{
	FILE* fp;
	fp = fopen( "EventTask.txt", "rt" );
	if(NULL == fp )
	{
		assert( !"Can't open ./EventTask.txt file" );
		exit(0);
	}

	char szLine[1024] = { 0,0,0, };
	while(1)
	{	char* szRes = fgets( (char*)szLine, 255, fp );
		if( NULL == szRes ) break;
		
		ParseData( szLine );		
	}	

	fclose( fp );
}


void ParseData( char* a_pCmd )
{
    if( NULL == a_pCmd ) return;
	if( '/' != a_pCmd[0] ) return;
	//if( 0 == szCmd[0] ) return;
    
    char szCmd[256] = { 0,0,0, };
	char szArguments[512] = { 0,0,0, };
	char szrgArgument[20][256] = { 0,0,0, };
	int irgArgument[20] = { 0,0,0, };
    
	sscanf( a_pCmd, "%s %s", szCmd, szArguments );    

	if( !strcmp( szCmd, "/Event" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2], szrgArgument[3], szrgArgument[4]
			, szrgArgument[5], szrgArgument[6], szrgArgument[7], szrgArgument[8], szrgArgument[9]
			//, szrgArgument[10], szrgArgument[11], szrgArgument[12], szrgArgument[13], szrgArgument[14]
			//, szrgArgument[15], szrgArgument[16], szrgArgument[17], szrgArgument[18], szrgArgument[19]
			);

		irgArgument[0] = atoi( szrgArgument[0] );
		irgArgument[1] = atoi( szrgArgument[1] );
		irgArgument[2] = atoi( szrgArgument[2] );
		irgArgument[3] = atoi( szrgArgument[3] );
		irgArgument[4] = atoi( szrgArgument[4] );
		irgArgument[5] = atoi( szrgArgument[5] );
		irgArgument[6] = atoi( szrgArgument[6] );
		irgArgument[7] = atoi( szrgArgument[7] );
		irgArgument[8] = atoi( szrgArgument[8] );
		irgArgument[9] = atoi( szrgArgument[9] );
		//irgArgument[10] = atoi( szrgArgument[10] );
		//irgArgument[11] = atoi( szrgArgument[11] );
		//irgArgument[12] = atoi( szrgArgument[12] );
		//irgArgument[13] = atoi( szrgArgument[13] );
		//irgArgument[14] = atoi( szrgArgument[14] );
		//irgArgument[15] = atoi( szrgArgument[15] );
		//irgArgument[16] = atoi( szrgArgument[16] );
		//irgArgument[17] = atoi( szrgArgument[17] );
		//irgArgument[18] = atoi( szrgArgument[18] );
		//irgArgument[19] = atoi( szrgArgument[19] );

		int iEventID = irgArgument[0];
		if( 0 < iEventID && eEvent_MaxCount > iEventID )
		{
			g_krgEventList[iEventID].srgTask[0] = irgArgument[1];
			g_krgEventList[iEventID].srgTask[1] = irgArgument[2];
			g_krgEventList[iEventID].srgTask[2] = irgArgument[3];
			g_krgEventList[iEventID].srgTask[3] = irgArgument[4];
			g_krgEventList[iEventID].srgTask[4] = irgArgument[5];
			g_krgEventList[iEventID].uiCoolDownTime = irgArgument[6];
			g_krgEventList[iEventID].sCount = irgArgument[7];
			g_krgEventList[iEventID].sProceedType = irgArgument[8];
			g_krgEventList[iEventID].iDuration = irgArgument[9];
			g_krgEventList[iEventID].uiAvailableTime = 0;		
			g_krgEventList[iEventID].sClan = eEvntClan_All;

			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- EventID:%3d, \tiTask1:%3d, \tiTask2:%3d, \tiTask3:%3d, \tiTask4:%3d, \tiTask5:%3d, \tcool-down time:%d, count:%d, procdtype:%d, DurType:%d \r\n"
					, iEventID, g_krgEventList[iEventID].srgTask[0], g_krgEventList[iEventID].srgTask[1], g_krgEventList[iEventID].srgTask[2], g_krgEventList[iEventID].srgTask[3], g_krgEventList[iEventID].srgTask[4]
					, g_krgEventList[iEventID].uiCoolDownTime, g_krgEventList[iEventID].sCount, g_krgEventList[iEventID].sProceedType, g_krgEventList[iEventID].iDuration
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" );
			}
		}
	}
	else if( !strcmp( szCmd, "/Task" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2], szrgArgument[3], szrgArgument[4]
			, szrgArgument[5], szrgArgument[6], szrgArgument[7]
			);

		irgArgument[0] = atoi( szrgArgument[0] );
		irgArgument[1] = atoi( szrgArgument[1] );
		irgArgument[2] = atoi( szrgArgument[2] );
		irgArgument[3] = atoi( szrgArgument[3] );
		irgArgument[4] = atoi( szrgArgument[4] );
		irgArgument[5] = atoi( szrgArgument[5] );
		irgArgument[6] = atoi( szrgArgument[6] );
		irgArgument[7] = atoi( szrgArgument[7] );


		int iTaskID = irgArgument[0];
		if( 0 < iTaskID && eTask_MaxCount > iTaskID )
		{
			g_krgTaskList[iTaskID].iActionID = irgArgument[1];
			g_krgTaskList[iTaskID].irgParam[0] = irgArgument[2];
			g_krgTaskList[iTaskID].irgParam[1] = irgArgument[3];
			g_krgTaskList[iTaskID].irgParam[2] = irgArgument[4];
			g_krgTaskList[iTaskID].irgParam[3] = irgArgument[5];
			g_krgTaskList[iTaskID].irgParam[4] = irgArgument[6];
			g_krgTaskList[iTaskID].irgParam[5] = irgArgument[7];

			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- TaskID:%3d, \tActionID:%3d, \tParam1:%3d, \tParam2:%3d, \tParam3:%3d, \tParam4:%3d, \tParam5:%3d, \tParam6:%3d \r\n"
					, iTaskID, g_krgTaskList[iTaskID].iActionID
					, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
					, g_krgTaskList[iTaskID].irgParam[3], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" );
			}
		}
	}
	else if( !strcmp( szCmd, "/Scheduler" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2]
			);

		irgArgument[0] = atoi( szrgArgument[0] );
		irgArgument[1] = atoi( szrgArgument[1] );
		irgArgument[2] = atoi( szrgArgument[2] );


		int iMin = irgArgument[0];
		int iSec = irgArgument[1];
		int iTimeEvent = irgArgument[2];

		if( 0 > iMin || 60 <= iMin ) return;
		if( 0 > iSec || 56 < iSec ) return;
		if( 0 > iTimeEvent || eEvent_MaxCount <= iTimeEvent )  return;

		int iTimeSlot = (iMin*60 + iSec)/4;
		if( 0 <= iTimeSlot && eTS_MaxSlot > iTimeSlot )
		{
			if( 0 < g_srgTimeSchedule[iTimeSlot] ) // 다른 event가 등록이 되어 있다면, ...
			{
				int iPrevSlot = iTimeSlot-1;
				if( 0 > iPrevSlot ) iPrevSlot = 0;
				if( 0 == g_srgTimeSchedule[iPrevSlot] )
				{
					g_srgTimeSchedule[iPrevSlot] = iTimeEvent;
					iTimeSlot = iPrevSlot;
				}
				else
				{
					int iCount = 0;
					while(0 < g_srgTimeSchedule[iTimeSlot])
					{
						if( eTS_MaxSlot < iCount ) break;
						++iCount;
						++iTimeSlot;
						if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot = 0;
					}
					g_srgTimeSchedule[iTimeSlot] = iTimeEvent;
				}
			}
			else g_srgTimeSchedule[iTimeSlot] = iTimeEvent;

			g_srgTimeSchedule[iTimeSlot] = (short)iTimeEvent;
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "time slot : %d, event : %d, min: %d, sec:%d \r\n", iTimeSlot, iTimeEvent, iMin, iSec );
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" );
		}
	}
}





void LogRewardItems()
{
	for( int iMon = 101; iMon < 105; ++iMon )  // MAX_MONSTER_DATA
	{
		if( pMonsterData[iMon].snTribe != iMon + 2000 ) continue;

		char szLogFile[40];
		sprintf( szLogFile, ".\\monster_log\\[Rwd]Monster_%d.txt", pMonsterData[iMon].snTribe );

		int irgCount[eItm_MaxLevel] = { 0,0,0, };
		int irgErrCount[eItm_MaxLevel] = { 0,0,0, };
		int irgError[3] = { 0,0,0, };
		int iMobLevel = 0;
		for( int iKillCount = 0; iKillCount < 10000; ++iKillCount )
		{
			for( int i = 0; i < 8; ++i ) // 0~7번째 items
			{
				if( 0 >= pMonsterData[iMon].Inven[i].snIndex ) continue;
				if( g_krgRewardItemRate[iMon][i].Random() )
				{
					{
						char chBuf[256] = { 0,0,0, };
						sprintf(chBuf, "%dth item %d \r\n", i+1, pMonsterData[iMon].Inven[i].snIndex + 4000 ); 
						//WriteLog( chBuf, szLogFile );
					}
				}
			}

			// 9번째 reward-Item
			iMobLevel = pMonsterData[iMon].Inven[8].snIndex;
			if( 0 < iMobLevel && eMonster_MaxLevel > iMobLevel )
			{
				//if( g_krgRewardItemRate[iMon][8].Random() )
				{
					int iItemLevel = g_krgItemRateByMonLevel[iMobLevel].Random();  // iItemLevel : 1~11
					int iItemCategory = g_kRateByItemCategory.Random(); // iItemCategory : 0~n
					if( (0 < iItemLevel && eItm_MaxLevel > iItemLevel) && ( 0 <= iItemCategory && eItm_MaxCategory > iItemCategory) )
					{
						if( 0 < g_krgItemByLevel[iItemCategory][iItemLevel].snIndex && MAX_ITEM > g_krgItemByLevel[iItemCategory][iItemLevel].snIndex )
						{
							++irgCount[iItemLevel];
							char chBuf[256] = { 0,0,0, };
							sprintf(chBuf, "9th item %d \r\n", g_krgItemByLevel[iItemCategory][iItemLevel].snIndex + 4000 ); 
							//WriteLog( chBuf, szLogFile );
						}			
						else
						{
							++irgErrCount[iItemLevel];
							++ irgError[2];
							{
								char chBuf[256] = { 0,0,0, };
								sprintf(chBuf, "Err> 9th item , iItemCategory:%d, iItemLevel:%d, itemIndex:%d \r\n", iItemCategory, iItemLevel, g_krgItemByLevel[iItemCategory][iItemLevel].snIndex ); 
								WriteLog( chBuf, szLogFile );
							}
						}
					}
					else ++ irgError[1];
				}
			}
			else ++ irgError[0];

			// 10번째 reward-Item
			if( 0 < pMonsterData[iMon].Inven[9].snIndex )
			{
				if( g_krgRewardItemRate[iMon][9].Random() )
				{
					int iGroup =  pMonsterData[iMon].Inven[9].snIndex;
					if( 0 < iGroup && eRwd_ItemGroup > iGroup )
					{
						int iGroupItemCount = g_srgGroupItemCount[iGroup];
						if( 0 < iGroupItemCount && eRwd_ItemGroupCount >= iGroupItemCount )
						{
							int iDice = rand() % iGroupItemCount;
							short sIndex = g_srgItemGroup[iGroup][iDice] - HT_PARAMTYPE_ITEM_START + 1;
							if( 0 < sIndex && MAX_ITEM_DATA > sIndex )
							{
								if( 0 < pItemData[sIndex].byLevel )
								{
									{
										char chBuf[256] = { 0,0,0, };
										sprintf(chBuf, "10th item %d \r\n", pItemData[sIndex].sID ); 
										//WriteLog( chBuf, szLogFile );
									}
								}
							}
						}
					}
				}
			} // if( 0 < MOB.Inven[9].snIndex ) // 10번째 reward-Item
		} // for( int iKillCount = 0; iKillCount < 10000; ++iKillCount )

		{
			char chBuf[512] = { 0,0,0, };
			int iSum = irgCount[1] + irgCount[2] + irgCount[3] + irgCount[4] + irgCount[5] + irgCount[6] + irgCount[7] + irgCount[8] + irgCount[9] + irgCount[10] + irgCount[11];
			sprintf(chBuf, "9th Item 통계> MonsterID:%d, MonLvl:%d  나온총합:%d, 나오지않은총합(%d+%d+%d) \r\n\t나온아이템개수> 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d, 11:%d \r\n\t나오지않은아이템개수> 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d, 11:%d"
				, iMon+2000, iMobLevel, iSum, irgError[0], irgError[1], irgError[2]
				, irgCount[1], irgCount[2], irgCount[3], irgCount[4], irgCount[5], irgCount[6], irgCount[7], irgCount[8], irgCount[9], irgCount[10], irgCount[11]
				, irgErrCount[1], irgErrCount[2], irgErrCount[3], irgErrCount[4], irgErrCount[5], irgErrCount[6], irgErrCount[7], irgErrCount[8], irgErrCount[9], irgErrCount[10], irgErrCount[11] ); 
			WriteLog( chBuf, szLogFile );
		}
	}

	WriteLog( "끝", ".\\monster_log\\[Rwd] 1만회 죽이기 끝.txt" );
}



void RegisterMonstersToArea()
{
	int idx = 0;
	int iMonsterHandle = MAX_USER + 16; // 1000~1015까지는 Handle 고정 monster들을 위해 reserved 되어 있다. 그래서 항상 시작은 10016에서 부터한다.
	// handle을 고정시키지 않으면 다른 instance가 동일 handle을 사용하기 때문에, 고정 handle 개념을 사용할 수 없는 문제점이 있다.
	// 이것은 kala, 공성상징물 등을 위해 사용된다. 모두 고정 handle 값으로 유지관리된다.
	for( int i = 0; i <= mNPCGen.NumList; ++i )
	{
		idx = i; 
		for( int iCmd = 0; iCmd < eCmd_MaxCount; ++iCmd )
		{
			if( eCmd_None == mNPCGen.pList[idx].krgCommand[iCmd].iCommand ) continue;
			if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) )
			{
				int iIndex = mNPCGen.pList[idx].krgCommand[iCmd].iIndex;
				for( int iPop = 0; iPop < mNPCGen.pList[idx].krgCommand[iCmd].iCount; ++iPop )
				{
					if( mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount >= mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ) break;
/*
					int mob = GetEmptyNPCMob();              
            		if  (mob==0)
            		{   sprintf(temp,"err no emptymob leader: %d",idx);
            			Log(temp,"-system",0);
            			{
            				char chBuf[256] = { 0,0,0, };
            				sprintf(chBuf, "[DeployMonsters] GetEmptyNPCMob()이 0을 return -> 더이상 pMob[]배열에 여유가 없다는 것임. 확인요함!\r\n" );
            				WriteLog( chBuf, ".\\monster_log\\[Log]FailToPop.txt" );
            			}
            			continue;  // MobList가 꽉 찼다.
            		}
*/

					for( int r = 0; r < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount; ++r )
					{       
						if( 0 == mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][0] ) // 등록해준다.
						{
							mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][0] = iMonsterHandle;
							mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][1] = 1;
							pMob[iMonsterHandle].m_irgMobListIndex[0] = iIndex;
							pMob[iMonsterHandle].m_irgMobListIndex[1] = r;
							++iMonsterHandle;
							break;
						}			        
					}	            	          	            	
				} // for( int iPop = 0; iPop < mNPCGen.pList[idx].krgCommand[iCmd]; ++iPop )
			} // end of if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) && bPopMonster )
		}
	}
	g_iFreeSlotForNPC = iMonsterHandle + 1;
}

/*
bool IsInRvR()
{
	int iZoneID = ServerIndex + 1;
	for( int i = 0; i < eRvRZone_Count; ++i )
	{
		if( iZoneID == g_pRvRZoneList[i] )
		{
			g_bIsInRvR = true;
			return true;
		}
		if( 0 == g_pRvRZoneList[i] ) return false;
	}
	
	return false;
}
*/

void PrintMapInfo()
{
	HS2D_COORD kCenter, kBegin, kEnd;

	int iWidth = 39;
	kCenter.x = 280;
	kCenter.y = 40;

	kBegin.x = kCenter.x - iWidth;
	kBegin.y = kCenter.y - iWidth;
	if( 0 > kBegin.x ) kBegin.x = 0;
	if( 0 > kBegin.y ) kBegin.y = 0;
	kEnd.x = kCenter.x + iWidth;
	kEnd.y = kCenter.y + iWidth;
	if( MAX_GRIDX <= kEnd.x ) kEnd.x = MAX_GRIDX -1;
	if( MAX_GRIDY <= kEnd.y ) kEnd.y = MAX_GRIDY -1;
	
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n\n\n[PrintMapInfo()] Center(%d,%d), Begin(%d,%d) ~ End(%d,%d)\r\n", kCenter.x, kCenter.y , kBegin.x, kBegin.y, kEnd.x, kEnd.y );
		WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" );
	}

	for( int y = kBegin.y; y < kEnd.y; ++y )
	{
		WriteLog( "\r\n", ".\\monster_log\\[Log]CheckMap.txt" );
		for( int x = kBegin.x; x < kEnd.x; ++x )
		{
			char chCell = 'O';
			if( g_krgCell[y][x].usProperty & eTNCell_Blocked ) chCell = 'X';
			if( kCenter.x == x && kCenter.y == y ) chCell = 'K';

			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "%c", chCell );
				WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" );
			}
		}	

		if( kCenter.y == y )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t%d", y );
			WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" );
		}
	}
}


// called by OnKilled() only.
// 파티원에게 프라나를 분배한다.
void SharePrana( int a_iParty, int a_iPrana, int a_iCorpse )
{
	if( 0 >= a_iParty || MAX_USER <= a_iParty ) return; // iParty가 PC인 경우에만 Prana분배
	if( MAX_USER > a_iCorpse || MAX_MOB <= a_iCorpse ) return;
	if( 0 >= a_iPrana ) return;

	int nParty[MAX_PARTY+1]={0,0,0,};
	int fol=0;	int nNumParty=0;	int leader=0;	int nLevel=0;
	int nMaxLevel=0; int nMinLevel=500;
	leader = a_iParty;

	int tx = pMob[a_iCorpse].TargetX;
	int ty = pMob[a_iCorpse].TargetY;
	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) fol = leader;
		else      fol = pMob[leader].m_irgParty[i-1];
   	 	if	(fol<=0||fol>=MAX_USER) continue;
		if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
		int nTempLevel = pMob[fol].MOB.byLevel;
		nParty[nNumParty++]=fol;	nLevel += nTempLevel;
		if(nTempLevel>nMaxLevel) nMaxLevel = nTempLevel;
		if(nTempLevel<nMinLevel) nMinLevel = nTempLevel;
	}

	int nRatio=0; int nGetPrana = 0; int nSubLevel = 0;
	if(nNumParty==0 || nLevel==0) return;		//	맥뎀파티가 몹사망시 근처에 없을경우.
	else nSubLevel = pMob[a_iCorpse].MOB.byLevel - nLevel/nNumParty;	

	if(nSubLevel>15)
	{	nRatio=250;
	}	
	else if(nSubLevel<=15 && nSubLevel>10)
	{	nRatio=200;
	}	
	else if(nSubLevel<=10 && nSubLevel>5)
	{	nRatio=150;
	}	
	else if(nSubLevel<=5 && nSubLevel>2)
	{	nRatio=120;
	}	
	else if(nSubLevel<=2 && nSubLevel>0)
	{	nRatio=110;
	}	
	else if(nSubLevel<=0 && nSubLevel>-11)
	{	nRatio=100;
	}
	else if(nSubLevel<=-11 && nSubLevel>-16)
	{	nRatio=80;
	}
	else
		nRatio=50;

	if(nNumParty == 1)		//	파티원이 아닐경우
	{
		int fol = nParty[0];
		if	(fol<=0||fol>=MAX_USER) return;

		nGetPrana = a_iPrana*nRatio/100;
		int nMaxPrana = 10+10*(pMob[fol].MOB.byLevel)*(pMob[fol].MOB.byLevel+1)/2;
		nMaxPrana = (int)(nMaxPrana * g_drgRwdCorrect[eRwd_Prana][eRwd_Total]);
		if(nGetPrana > nMaxPrana) nGetPrana=nMaxPrana;

		nGetPrana *= (pMob[fol].m_dGetPranaRate/100);

		pMob[fol].AcquirePrana( nGetPrana, true ); // 프라나 보너스를 적용한다.
		QUEST_OnEvent( a_iParty, pMob[a_iCorpse].MOB.snTribe, pMob[a_iCorpse].MOB.snTribe, 0 );
	}
	else					//	파티원일 경우
	{	int nMaxPrana=0;
		int nPartyPrana = 0;
		int nDiff = nMaxLevel-nMinLevel;

		if(nDiff>20)										//	레벨차이가 20보다 클경우
		{	if(nRatio>100) 
				nPartyPrana = a_iPrana;
			else				
				nPartyPrana = a_iPrana*nRatio/100;
		}
		else												//	레벨차이가 20이하일 경우
		{	nPartyPrana = a_iPrana*(nRatio+(nNumParty-1)*20)/100;
		}

		for (int i=0;i<nNumParty;i++)
		{   fol=nParty[i];
   	 		if	(fol<=0||fol>=MAX_USER) continue;
			if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-g_iViewGridX || tx>pMob[fol].TargetX+g_iViewGridX ||ty<pMob[fol].TargetY-g_iViewGridY || ty>pMob[fol].TargetY+g_iViewGridY) continue;
			else nGetPrana = nPartyPrana*pMob[fol].MOB.byLevel/nLevel;

			QUEST_OnEvent( fol, pMob[a_iCorpse].MOB.snTribe, pMob[a_iCorpse].MOB.snTribe, 0 );
			nMaxPrana = 10+10*(pMob[fol].MOB.byLevel)*(pMob[fol].MOB.byLevel-1)/2;
			nMaxPrana = (int)(nMaxPrana * g_drgRwdCorrect[eRwd_Prana][eRwd_Total]);
			//nMaxPrana *= g_drgRwdCorrect[eRwd_Prana][eRwd_Total];
			if(nGetPrana > nMaxPrana) nGetPrana=nMaxPrana;

			nGetPrana *= (int)(pMob[fol].m_dGetPranaRate/100);
			pMob[fol].AcquirePrana( nGetPrana, true ); // 프라나 보너스를 적용한다.
		}

		SendUpdateParty(a_iParty);
	}
}

void ShareBramanPoint( int a_iParty, int a_iBP, int a_iCorpse )
{
	if( 0 >= a_iParty || MAX_USER <= a_iParty ) return; // iParty가 PC인 경우에만 BP분배
	//if( MAX_USER <= a_iCorpse || MAX_MOB <= a_iCorpse ) return; // 죽은 시체가 NPC이면 return
	if( 0 >= a_iBP ) return;


	int iLeader = pMob[a_iParty].Leader;
	if( 0 >= iLeader ) iLeader = a_iParty;

	int iPartyCount = 0;
	int tx = pMob[a_iCorpse].TargetX;
	int ty = pMob[a_iCorpse].TargetY;
	int fol = 0;
	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) fol = iLeader;
		else      fol = pMob[iLeader].m_irgParty[i-1];
   	 	if	(fol<=0||fol>=MAX_USER) continue;
		if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
		++iPartyCount;
	}

	if(ServerIndex+1==eZone_Cruma)
	{
		if(pMob[a_iParty].MOB.byTrimuriti==eTNClan_Brahma && g_nBrahmaBP>0) 
		{
			a_iBP += 150; g_nBrahmaBP -= 150; 
			if(g_nBrahmaBP<0) g_nBrahmaBP=0;
		}
		else if(pMob[a_iParty].MOB.byTrimuriti==eTNClan_Vishnu && g_nVishnuBP>0) 
		{
			a_iBP += 150; g_nVishnuBP -= 150;
			if(g_nVishnuBP<0) g_nVishnuBP=0;
		}
		if(pMob[a_iParty].MOB.byTrimuriti==eTNClan_Siva && g_nSivaBP>0) 
		{
			a_iBP += 150; g_nSivaBP -= 150;
			if(g_nSivaBP<0) g_nSivaBP=0;
		}
	}

	// 기존 획득 주포+ 기존 획득 주포*( (파티원-1)*0.15 )
	if(iPartyCount<=0) iPartyCount = 1;

	//#ifdef __TN_LOCAL_SERVER_SWITCH__
	int iOld = a_iBP;
	a_iBP += (a_iBP * (iPartyCount-1) * 15) / 100;
	char chBuf[256] = { 0,0,0, };
	sprintf( chBuf, "[ShareBramanPoint] BP:%d(old:%d), party:(%d, cnt:%d)  \r\n", a_iBP, iOld, a_iParty, iPartyCount  );
	WriteLog( chBuf, ".\\Monster_Log\\[Log]BP.txt" );

	//#endif
	
	int iRewardBP = a_iBP / iPartyCount;

	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) fol = iLeader;
		else      fol = pMob[iLeader].m_irgParty[i-1];
   	 	if	(fol<=0||fol>=MAX_USER) continue;
		if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
		if  (ServerIndex+1==SERVER_KRUMA_LOW && pMob[fol].MOB.nBramanPoint>20000) continue;		//	저랩주신전에서 브라만포인트 20000초과시 브라만포인트 획득못한다(2005.11.25)
		pMob[fol].IncBP( iRewardBP );
		pMob[fol].NotifyUpdateUIMsg();
	}
}


//@Param
//	a_iType : 1:base, 2:extra(0은 total)
void ChangeRwdCorrect( int a_iType, int a_iPrana, int a_iGold, int a_iBraman, int a_iItem )
{
	if( eRwd_Base > a_iType || eRwd_ExtraMinus < a_iType ) return;

	//// backup
	//g_drgRwdCorrect[eRwd_Prana][eRwd_Extra] = g_drgRwdCorrect[eRwd_Prana][eRwd_Total];
	//g_drgRwdCorrect[eRwd_Gold][eRwd_Extra] = g_drgRwdCorrect[eRwd_Gold][eRwd_Total];
	//g_drgRwdCorrect[eRwd_Braman][eRwd_Extra] = g_drgRwdCorrect[eRwd_Braman][eRwd_Total];
	//g_drgRwdCorrect[eRwd_Item][eRwd_Extra] = g_drgRwdCorrect[eRwd_Item][eRwd_Total];

	// change
	//g_drgRwdCorrect[eRwd_Prana][a_iType] = a_iPrana;
	//g_drgRwdCorrect[eRwd_Gold][a_iType] = a_iGold;
	//g_drgRwdCorrect[eRwd_Braman][a_iType] = a_iBraman;
	//g_drgRwdCorrect[eRwd_Item][a_iType] = a_iItem;
	if( eRwd_Base == a_iType )
	{		
		if( 0 >= a_iPrana ) a_iPrana = 100;
		if( 0 >= a_iGold ) a_iGold = 100;
		if( 0 >= a_iBraman ) a_iBraman = 100;
		if( 0 >= a_iItem ) a_iItem = 100;

		g_drgRwdCorrect[eRwd_Prana][eRwd_Base] = a_iPrana;
		g_drgRwdCorrect[eRwd_Gold][eRwd_Base] = a_iGold;
		g_drgRwdCorrect[eRwd_Braman][eRwd_Base] = a_iBraman;
		g_drgRwdCorrect[eRwd_Item][eRwd_Base] = a_iItem;
	}
	else if( eRwd_Extra == a_iType )
	{
		g_drgRwdCorrect[eRwd_Prana][eRwd_Extra] += a_iPrana;
		g_drgRwdCorrect[eRwd_Gold][eRwd_Extra] += a_iGold;
		g_drgRwdCorrect[eRwd_Braman][eRwd_Extra] += a_iBraman;
		g_drgRwdCorrect[eRwd_Item][eRwd_Extra] += a_iItem;
	}
	else if( eRwd_ExtraMinus == a_iType )
	{
		g_drgRwdCorrect[eRwd_Prana][eRwd_Extra] -= a_iPrana;
		g_drgRwdCorrect[eRwd_Gold][eRwd_Extra] -= a_iGold;
		g_drgRwdCorrect[eRwd_Braman][eRwd_Extra] -= a_iBraman;
		g_drgRwdCorrect[eRwd_Item][eRwd_Extra] -= a_iItem;

		if( 0 > g_drgRwdCorrect[eRwd_Prana][eRwd_Extra] ) g_drgRwdCorrect[eRwd_Prana][eRwd_Extra] = 0;
		if( 0 > g_drgRwdCorrect[eRwd_Gold][eRwd_Extra] ) g_drgRwdCorrect[eRwd_Gold][eRwd_Extra] = 0;
		if( 0 > g_drgRwdCorrect[eRwd_Braman][eRwd_Extra] ) g_drgRwdCorrect[eRwd_Braman][eRwd_Extra] = 0;
		if( 0 > g_drgRwdCorrect[eRwd_Item][eRwd_Extra] ) g_drgRwdCorrect[eRwd_Item][eRwd_Extra] = 0;
	}

	g_drgRwdCorrect[eRwd_Prana][eRwd_Total] = g_drgRwdCorrect[eRwd_Prana][eRwd_Base] + Percent(g_drgRwdCorrect[eRwd_Prana][eRwd_Base], g_drgRwdCorrect[eRwd_Prana][eRwd_Extra]);
	g_drgRwdCorrect[eRwd_Gold][eRwd_Total] = g_drgRwdCorrect[eRwd_Gold][eRwd_Base] + Percent(g_drgRwdCorrect[eRwd_Gold][eRwd_Base], g_drgRwdCorrect[eRwd_Gold][eRwd_Extra]);
	g_drgRwdCorrect[eRwd_Braman][eRwd_Total] = g_drgRwdCorrect[eRwd_Braman][eRwd_Base] + Percent(g_drgRwdCorrect[eRwd_Braman][eRwd_Base], g_drgRwdCorrect[eRwd_Braman][eRwd_Extra]);
	g_drgRwdCorrect[eRwd_Item][eRwd_Total] = g_drgRwdCorrect[eRwd_Item][eRwd_Base] + Percent(g_drgRwdCorrect[eRwd_Item][eRwd_Base], g_drgRwdCorrect[eRwd_Item][eRwd_Extra]);

	g_drgRwdCorrect[eRwd_Prana][eRwd_Total] /= 100;
	g_drgRwdCorrect[eRwd_Gold][eRwd_Total] /= 100;
	g_drgRwdCorrect[eRwd_Braman][eRwd_Total] /= 100;
	g_drgRwdCorrect[eRwd_Item][eRwd_Total] /= 100;

	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[%dMM%dDD %dHH%dMI%dSS] PranaCorrect:%f, GoldCorrect:%f, BramanCorrect:%f, Base(%f, %f, %f), Extra(%f, %f, %f) \r\n\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Total], g_drgRwdCorrect[eRwd_Gold][eRwd_Total], g_drgRwdCorrect[eRwd_Braman][eRwd_Total]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Base], g_drgRwdCorrect[eRwd_Gold][eRwd_Base], g_drgRwdCorrect[eRwd_Braman][eRwd_Base]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Extra], g_drgRwdCorrect[eRwd_Gold][eRwd_Extra], g_drgRwdCorrect[eRwd_Braman][eRwd_Extra]
			);
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
	}
}


void DBUpdateGuildMember(int conn)
{
	if(conn<=0 || conn>=MAX_USER) return;
	if(pUser[conn].nGuildIndex==0 || pUser[conn].Mode!=USER_PLAY) return;

	MSG_GuildUpdateMember sm; sm.wType=_MSG_GuildUpdateMember;
	sm.wPDULength = sizeof(sm)-sizeof(HEADER);
	sm.GuildID = pMob[conn].MOB.nGuildID;
	sm.nID = conn; sm.Member.byLevel=pMob[conn].MOB.byLevel;
	sm.Member.GuildRank=pUser[conn].nGuildLevel;
	sm.Member.snTribe=pMob[conn].MOB.snTribe; sm.Member.GuildState=0;
	sm.Member.byClass1 = pMob[conn].MOB.byClass1;
	sm.Member.byClass2 = pMob[conn].MOB.byClass2;
	strncpy(sm.Member.MemberName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*) &sm);				//	동일지역내에 길드원 정보변경을 알린다.

	if(!DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm)))					//	타지역에 길드원 정보변경을 알린다
	{	Log("err DBUpdateGuildMember",pUser[conn].AccountName,pUser[conn].IP);
	}
}


/*
#define _Msg_GuildItemMove		???
struct Msg_GuildItemMove
{
	

};
*/


BYTE GetEventStatus(char* pAccount)
{
	if(pAccount==0) return 0;

	DWORD dwRet10 = 0;
	DWORD dwRet20 = 0;
	BYTE byStatus = 0;

	char file[256]={0,};
	sprintf(file,"H:\\%s%d.dat",pAccount,10);
	FILE * fp = fopen(file,"rb");	
	if	(fp!=NULL) { fscanf(fp,"%d",&dwRet10); byStatus+=32; fclose(fp); }
		
	memset(file,0,256);
	sprintf(file,"H:\\%s%d.dat",pAccount,20);
	fp = fopen(file,"rb");	
	if	(fp!=NULL) { fscanf(fp,"%d",&dwRet20); byStatus+=16; fclose(fp); }
	
	if(dwRet10>0) byStatus+=2;
	if(dwRet20>0) byStatus+=1;
	
	return byStatus;
}


int PlayDice( int a_iMin, int a_iMax )
{
	if( a_iMin == a_iMax ) return a_iMin;

	if( a_iMin > a_iMax )
	{
		int iTemp = a_iMin;
		a_iMin = a_iMax;
		a_iMax = iTemp; 
	}
	int iDice = 0;
	int iGap = 0;
	iGap = a_iMax - a_iMin;
	++iGap;

	if( 0 >= iGap )  iDice = a_iMin;
	else iDice = a_iMin + ( rand() % iGap );

	return iDice;
}

//-------------------------------------------------------------------------
// CMob::의 member로 한 이유는 teleport를 시전한 시전자의 의미이다.
//@Param
//	- a_iMob : teleport를 시킬 target
//	- a_iX, a_iY : teleport 시킬 위치
//-------------------------------------------------------------------------
int Teleport( int a_iMob, int a_iX, int a_iY )
{
	if( 0 >= a_iMob || MAX_MOB <= a_iMob ) return eTNRes_Failed;
	//int tret = GetEmptyMobGrid( a_iMob, &a_iX, &a_iY ); // Old version
	int tret = PickFreeMobGrid( a_iMob, &a_iX, &a_iY );
	if( FALSE == tret ) return eTNRes_Failed;
	if( pMob[a_iMob].m_iBlockedCell & g_krgCell[a_iY][a_iX].usProperty ) return eTNRes_Failed;

	pMob[a_iMob].KillMobSummoned( eTNCls2_Retainer );//KillRetainer();

	MSG_Action sm;
	GetAction(a_iMob,a_iX,a_iY,&sm);
	sm.Effect = 5;
	if( a_iMob < MAX_USER ) 
	{
		pUser[a_iMob].nPreX = a_iX; pUser[a_iMob].nPreY = a_iY;
		pUser[a_iMob].cSock.AddMessage( (char*)&sm, sizeof(sm) );
	}

	GridMulticast(a_iMob,a_iX,a_iY,(MSG_STANDARD*)&sm,100,ACTION_WARP);

	/*
	// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
	S_SCP_INIT_OTHER_MOB m;
	GetCreateMob( a_iMob, &m);
	GridMulticast(a_iX, a_iY, (MSG_STANDARD*)&m, a_iMob, 50 );
	*/

	pMob[a_iMob].LastX = pMob[a_iMob].TargetX;
	pMob[a_iMob].LastY = pMob[a_iMob].TargetY;
	pMob[a_iMob].m_kLastTime.uiSelectTarget = 0;

	return eTNRes_Succeeded;
}



void HelpGameMaster( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{	
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

	int iZoneID = ServerIndex + 1;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( a_bCheckGM )
	{
		if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return;    
		if( (eTNClan_GM != pMob[a_iHandle].m_byClan) && (strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH)!=0) ) return;
	}
	#endif

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[128] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5  );   
	iArgument1	=atoi(szArgument1);
	iArgument2	=atoi(szArgument2);
	iArgument3	=atoi(szArgument3);
	iArgument4	=atoi(szArgument4);
	iArgument5	=atoi(szArgument5);

    if( '/' != szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)
	//SYSTEMTIME st;
	//GetLocalTime( &st );
    
	#ifdef __TN_TOP_LOG__
	{
		if(strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH) != 0)
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[%d월%d일 %d시%d분%d초] %s  %s \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd );
			WriteLog( chBuf, ".\\Event\\HelpGM.txt" );
		}
	}
	#endif
  

    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );

    if( !strcmp( szCmd, "/stat" ) || !strcmp( szCmd, "/스탯" ) )// ok
    {

		int iTarget = iArgument1; // mobile handle
		//int iTarget = GetMOBID( szArguments );
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			sprintf( szResult, "%s> Account:%s, Lvl:%d, TChakra(%d,%d,%d,%d), PChakra(%d,%d,%d,%d), HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pUser[iTarget].AccountName, pMob[iTarget].MOB.byLevel, pMob[iTarget].m_kChakra.sMuscle, pMob[iTarget].m_kChakra.sNerves, pMob[iTarget].m_kChakra.sHeart, pMob[iTarget].m_kChakra.sMind
				, pMob[iTarget].MOB.sMuscle, pMob[iTarget].MOB.sNerves, pMob[iTarget].MOB.sHeart, pMob[iTarget].MOB.sMind
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID								
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/카스트" ) )// ok
    {
		int iCaste = iArgument1; // 

		pMob[a_iHandle].m_iCaste = iCaste;

		pMob[a_iHandle].CalCasteSkillPoint();

		sprintf( szResult, "%s> User(%d)'s caste:%d, caste sp : %d"
			, a_pCmd, a_iHandle, pMob[a_iHandle].m_iCaste, pMob[a_iHandle].m_kCasteSPRemaining.get_Cur() );
	}
	//	임시코드 테스트용
    else if( !strcmp( szCmd, "/이벤트발동" ) )// ok
    {
		int iEvent = iArgument1; // 
		int iParam = iArgument2;
		DWORD dwFlag = 0x00000001;

		if(iEvent<1 || iEvent>8) return;
		dwFlag = dwFlag << (iEvent-1);
		SetGameEvent(a_iHandle, dwFlag & pUser[a_iHandle].m_dwEvent, &iParam);

		sprintf( szResult, "%s> User(%d)'s EVENT:%08X, caste flag : %d"
			, a_pCmd, a_iHandle, pUser[a_iHandle].m_dwEvent, dwFlag );
	}
    else if( !strcmp( szCmd, "/stat2" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			sprintf( szResult, "%s> Account:%s, Lvl:%d, HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pUser[iTarget].AccountName, pMob[iTarget].MOB.byLevel
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID								
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/stat3" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{
			pMob[iTarget].UpdateDamage( eTNEqu_OneHandWeapon );
			pMob[iTarget].UpdateDamage( eTNEqu_Shield );
			pMob[iTarget].UpdateEquipmentPoints();

			sprintf( szResult, "%s> Right-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d), Left-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d)"
				, a_pCmd
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Left].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPoison[0]
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/stat4" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{
			sprintf( szResult, "%s> Immu:%u, Aff:%u, clan:%d"
				, a_pCmd
				, pMob[iTarget].m_iImmunity, pMob[iTarget].m_iAffections, pMob[iTarget].m_byClan
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
	else if( !strcmp( szCmd, "/refresh" ) || !strcmp( szCmd, "/재스탯" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			pMob[iTarget].Init( iTarget );
			sprintf( szResult, "%s> Lvl:%d, TChakra(%d,%d,%d,%d), PChakra(%d,%d,%d,%d), HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pMob[iTarget].MOB.byLevel, pMob[iTarget].m_kChakra.sMuscle, pMob[iTarget].m_kChakra.sNerves, pMob[iTarget].m_kChakra.sHeart, pMob[iTarget].m_kChakra.sMind
				, pMob[iTarget].MOB.sMuscle, pMob[iTarget].MOB.sNerves, pMob[iTarget].MOB.sHeart, pMob[iTarget].MOB.sMind
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID
								
				);
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/mv" ) || !strcmp( szCmd, "/이" ) )// ok
	{
		int x = iArgument1, y = iArgument2;
		int tret = GetEmptyMobGrid( a_iHandle, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument1, iArgument2 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		MSG_Action sm;
		GetAction( a_iHandle, x, y, &sm );
		sm.Effect = 5;

		pUser[a_iHandle].nPreX = x; pUser[a_iHandle].nPreY = y;
		if( a_iHandle < MAX_USER ) pUser[a_iHandle].cSock.AddMessage( (char*)&sm, sizeof(sm) );
		GridMulticast( a_iHandle, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP );

/*
		// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
		S_SCP_INIT_OTHER_MOB m;
		GetCreateMob( a_iHandle, &m );
		GridMulticast( x, y, (MSG_STANDARD*)&m, a_iHandle, 20 );
*/
	}
    else if( !strcmp( szCmd, "/movepc" ) || !strcmp( szCmd, "/소환" ) )// ok
    {
		int iMobID = GetMOBID( szArgument1 );
		int x = iArgument2, y = iArgument3;
		if(x==0 && y==0) 
		{ x = pMob[a_iHandle].TargetX; y = pMob[a_iHandle].TargetY; }

		int tret = GetEmptyMobGrid( iMobID, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		if( 0 < iMobID && MAX_USER > iMobID )	//	동일지역내 상대방 존재
		{	
			MSG_Action sm;
			GetAction( iMobID, x, y, &sm );
			sm.Effect = 5;
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) );
			GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100,ACTION_WARP );

			/*
			// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
			S_SCP_INIT_OTHER_MOB m;
			GetCreateMob( iMobID, &m );
			GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 );
			*/
		}
		else
		{
			MSG_Warp sm; sm.wType = _MSG_Warp;
			strncpy(sm.szName, szArgument1, sizeof(sm.szName));
			sm.byType = CONNECT_TYPE_GMRECALL;
			sm.nID = a_iHandle; sm.dwPlace = ServerIndex+1;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err /movepc DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}  		    
		}        
    }
	else if( !strcmp( szCmd, "/moveother" ) )// ok
	{
		int iMobID = iArgument1; // 옮길 mob ID

		if( 0 >= iMobID || MAX_MOB <= iMobID )
		{
			sprintf( szResult, "%s> Invalid ID", a_pCmd );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		int x = iArgument2, y = iArgument3;
		int tret = GetEmptyMobGrid( iMobID, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		if( eTNMob_NPC == pMob[iMobID].m_eMobType )
		{
			if( MOB_COMBAT == pMob[iMobID].Mode ) // 전투 중이었다.
			{
				pMob[iMobID].Mode = MOB_PEACE;
				pMob[iMobID].CurrentTarget = 0;
				//memset( pMob[iMobID].EnemyList, 0, sizeof( pMob[iMobID].EnemyList ) );
			}
		}
		MSG_Action sm;
		GetAction( iMobID, x, y, &sm );
		sm.Effect = 5; // teleport
		if( iMobID < MAX_USER ) 
		{
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) );
		}
		GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP );
/*
		// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
		S_SCP_INIT_OTHER_MOB m;
		GetCreateMob( iMobID, &m );
		GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 );
*/
	}
	else if( !strcmp( szCmd, "/mvzone2" ) || !strcmp( szCmd, "/존이동2" ) )
	{	
		if( eZone_Mandra <= iArgument1 && eZone_CastleDungeon >= iArgument1 )
		{
			//MoveZone( iArgument1
			
			int irgNPC[22] = { 0, eSaveNPC_Mandra, eSaveNPC_Shambala, 0, 0, 0, 0, eSaveNPC_Jina, 0, eSaveNPC_9Zone, eSaveNPC_Cruma_Brahma
				, 1257, 0, 0, 0, 0, 1295, 1297, 0, 0, 1337, 0, };
			pMob[a_iHandle].MoveZoneByNPC( irgNPC[iArgument1] );
		}
		else
		{
			sprintf( szResult, "%s> faild to move the other zone> check the portal ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/mvzone" ) || !strcmp( szCmd, "/존이동" ) )
	{	
		char temp[512] = { 0,0,0, };
		S_CSP_REQ_MOVE_PORTAL kMsg;
		kMsg.wEndPortalID = iArgument1;

		S_SCP_RESP_MOVE_PORTAL sm; sm.wType=SCP_RESP_MOVE_PORTAL;

		bool bRet=true;
		DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
		bRet &= g_ParamMgr.HT_bGetPortalInfo( kMsg.wEndPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );
/*
		if(!bRet) 
		{
			sprintf( szResult, "%s> 존이동 실패> zone ID 확인 요망", a_pCmd );
		}

		{	sprintf(temp,"dbg CSP_REQ_MOVE_PORTAL find portal data error startp:%d endp:%d", kMsg.wStartPortalID, kMsg.wEndPortalID);
			Log(temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP);
			sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); return;
		}
*/
		BYTE byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
		if( bRet && (byMoveZone != (ServerIndex+1)) && (ServerDown==-1000) )	//	다른 존이면, ...
		{
			//sprintf(temp,"dbg char:%s move portal to other zone:%d", pMob[a_iHandle].MOB.szName, byMoveZone );
			//Log( temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP );
			pMob[a_iHandle].m_kWaitAction.iAction = eWaitAct_ZonePortal;

			sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
			sm.byZone=byMoveZone; sm.nMoney=pMob[a_iHandle].MOB.nRupiah;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
			
			pMob[a_iHandle].m_eFSM = eTNFsm_Stand;
			pMob[a_iHandle].m_kLastTime.uiSitted = 0;
			sprintf( szResult, "%s> succeeded to move the other zone", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> faild to move the other zone> check the portal ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/hold" ) || !strcmp( szCmd, "/정지" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			if( !strcmp( "off", szArgument2 ) )// hold를 turn off 시켜준다.
			{
				pMob[iTarget].TurnOffAffection( eTNAfn_Hold2 );
				sprintf( szResult, "%s> hold is debuffered on a target.", a_pCmd );
			}
			else
			{
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Hold2;
				kEffect.iDuration = 600000;
				kEffect.iParam1 = 100;
				kEffect.iParam2 = 0;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[iTarget].BroadcastUpdateStatusMsg();
				pUser[iTarget].cSock.SendMessage();

				sprintf( szResult, "%s> hold is affected on a target", a_pCmd );
			}
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/follow" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			if( !strcmp( "off", szArgument2 ) )
			{
				pMob[iTarget].m_iPassenger = 0; // follow를 turn off 시켜준다.
				sprintf( szResult, "%s> I will stop to follow %d", a_pCmd, iTarget );
			}
			else
			{
				pMob[iTarget].m_iPassenger = a_iHandle;
				sprintf( szResult, "%s> I will follow %d", a_pCmd, iTarget );
			}			
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/buffer" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			char szNormalInfo[1024] = { 0,0,0, };
			sprintf( szNormalInfo, "\r\n\r\nMob:%d/%s \r\n", iTarget, pMob[iTarget].MOB.szName );
			WriteLog( szNormalInfo, ".\\monster_log\\[DEBUG]PrintBuffer.txt" );

			for( int i = 0; i < TN_MAX_VARIATION_COUNT; ++i )
			{
				char szBuf[1024] = { 0,0,0, };
				sprintf( szBuf, "Index:%d, Equip(%d,%d), Passive(%d,%d), Activ(%d,%d) \r\n"
					, i
					, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPlus					
					, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPlus
					, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPlus
					);
				WriteLog( szBuf, ".\\monster_log\\[DEBUG]PrintBuffer.txt" );
			}
		}
		else
		{
			sprintf( szResult, "%s> Error> Invalid handle!", a_pCmd );
		}

	}
	else if( !strcmp( szCmd, "/speed" ) || !strcmp( szCmd, "/스피드" ) )
	{
		if( 1 <= iArgument1 && 100 >= iArgument1 )
		{	
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_MoveSpeedPlus;
			kEffect.iDuration = 3600000; // 60 분
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = iArgument1;
			kEffect.iParam2 = 0;
			pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle );
			pMob[a_iHandle].NotifyUpdateUIMsg();
			pUser[a_iHandle].cSock.SendMessage();

			sprintf( szResult, "%s> the speed of move is %d", a_pCmd, pMob[a_iHandle].m_iMoveSpeed );
		}
		else
		{
		    sprintf( szResult, "%s> the value of speed is invalid. valid value(5~100)", a_pCmd );
		}
	}
#ifdef __TN_PLAYMOVIE__
	else if( !strcmp( szCmd, "/공성상징물" ) )
	{
		if( 1 == iArgument1 ) g_kSiege.InstallSymbols();
		else g_kSiege.DestroySymbols();
	}
	else if( !strcmp( szCmd, "/방향전환" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].Direction = iArgument1;

				MSG_Action sm; GetAction( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, &sm);
				sm.Effect = 1; // stand
				GridMulticast( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm );
			}
		}
	}
	else if( !strcmp( szCmd, "/가로정렬" ) )
	{// x, y, length
		int x = iArgument1;
		int y = iArgument2;
		int iLen = iArgument3;

		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				Teleport( iMob, x, y );
				x += 2;
			}

			if( (x-iArgument1) > iLen )
			{
				++y;
				x = iArgument1 + 1;
			}
		}
	}
	else if( !strcmp( szCmd, "/세로정렬" ) )
	{
		int x = iArgument1;
		int y = iArgument2;
		int iLen = iArgument3;

		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				Teleport( iMob, x, y );
				y += 2;
			}

			if( (y-iArgument2) > iLen )
			{
				++x;
				y = iArgument2 + 1;
			}
		}		// teleport를 사용
	}
	else if( !strcmp( szCmd, "/로봇이동" ) )
	{ //0/1
		// teleport를 사용
		if( 1 == iArgument1 ) pMob[a_iHandle].m_iAIOption = pMob[a_iHandle].m_iAIOption | eTNAIO_Follow;
		else
		{
			if( eTNAIO_Follow & pMob[a_iHandle].m_iAIOption ) pMob[a_iHandle].m_iAIOption = pMob[a_iHandle].m_iAIOption ^ eTNAIO_Follow;
		}
	}	
	else if( !strcmp( szCmd, "/robot" ) )
	{ // iPC, count, Direction, range		
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				DeleteMob(iMob,645, 0, eTNPrdt_RemoveNormal, 240);
				pMob[iMob].Mode = MOB_EMPTY;
			}
		}

		if( 0 < iArgument1 && 1000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iBodyRadius = 1;//pMob[a_iHandle].m_byBodyRadius;
			int iSize = 4;//iBodyRadius + iBodyRadius + 1;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = pMob[a_iHandle].TargetX;
			kCur.y = pMob[a_iHandle].TargetY;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[1].x = kCur.x - ( iBodyRadius );
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius );

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[3].y = kCur.y - ( iBodyRadius );
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = kCur.y - ( iBodyRadius );

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = kCur.x - ( iBodyRadius );
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius );

            // 소환할 때

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = iArgument2; // 소환되는 수
			int iFormation = 0;
			if( 7 < iSummonCount ) iFormation = 1;
			int iIndex = 0;
			int iSummoned = 0;
            for( int iCount = 0; iCount < iSummonCount; ++iCount )
            {
				int x = 0, y = 0;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
					++iIndex;
					if( 7 < iIndex ) iIndex = 0;
				}
				else
				{// random하게 한 곳에서 태어난다.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}

				
				int iMob = pMob[a_iHandle].SummonRobot( iArgument1, x, y, iArgument3 );
				if( 0 < iMob )
				{
					pMob[a_iHandle].m_irgRobot[iSummoned] = iMob;
					++iSummoned;
				}
				//if( ROBOT_START <= iMob && ROBOT_END >= iMob )  ++iSummoned;
            }  
		}
		else
		{
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd );
		}

		
	}
	else if( !strcmp( szCmd, "/a" ) || !strcmp( szCmd, "/로봇공격" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget();
				pMob[iMob].ClearAttacker( 0 );
				pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );			
			}
		}
	}
	else if( !strcmp( szCmd, "/f" ) || !strcmp( szCmd, "/로봇멈춤" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget();
				pMob[iMob].ClearAttacker( 0 );
				pMob[iMob].Mode = MOB_PEACE;
				pMob[iMob].OnFollow( a_iHandle );
			}
		}
	}
#endif
	else if( !strcmp( szCmd, "/summon" ) )	// monster ID, Pop Count, class
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1;
		if( eTNCls_Warrior != iArgument3 && eTNCls_NPC != iArgument3 && eTNCls_Event != iArgument3 ) iArgument3 = eTNCls_Warrior;
		// eTNCls_NPC(19) 일 경우는 NPC-Monster의 형태를 취한다.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			TNSKILL_DATA kSkill; // 소환자의 clan이 상속된다.
			kSkill.krgEffect[0].iID = eTNAfn_Summon; // 
			kSkill.krgEffect[0].kFunc.iData = iArgument3; // class1
			kSkill.krgEffect[0].iDuration = eTNPrdt_PopRaise; // pop type
			kSkill.krgEffect[0].iParam1 = iArgument1; // monster ID
			kSkill.krgEffect[0].iParam2 = iArgument2; // count

			pMob[a_iHandle].CastOnly( kSkill );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summon2" ) || !strcmp( szCmd, "/서" ) )	// monster ID, Pop Count, 8|9(clan) range
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1;
		if( 0 >= iArgument2 ) iArgument2 = 1;
		if( 0 >= iArgument3 ) iArgument3 = eTNClan_Neutral;

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iBodyRadius = pMob[a_iHandle].m_byBodyRadius;
			int iSize = iBodyRadius + iBodyRadius + 1;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = pMob[a_iHandle].TargetX;
			kCur.y = pMob[a_iHandle].TargetY;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[1].x = kCur.x - ( iBodyRadius );
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius );

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[3].y = kCur.y - ( iBodyRadius );
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = kCur.y - ( iBodyRadius );

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = kCur.x - ( iBodyRadius );
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius );

            // 소환할 때

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = iArgument2; // 소환되는 수
			int iFormation = 0;
			if( 7 < iSummonCount ) iFormation = 1;
			int iIndex = 0;
            for( int iCount = 0; iCount < iSummonCount; ++iCount )
            {
				int x = 0, y = 0;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
					++iIndex;
					if( 7 < iIndex ) iIndex = 0;
				}
				else
				{// random하게 한 곳에서 태어난다.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}

				int iMob = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Warrior, 0, iArgument3, 0, x, y, 0, false, 0, 0, 14 );

				if( 0 == iMob ) ++iSummonCount;
				if( 30 <= iSummonCount ) break;
            }  
		}
		else
		{
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summon3" ) )	// monster ID, x, y, class1, clan
	{
		if	( iArgument2<0 || iArgument3<0 || iArgument2>MAX_GRIDX || iArgument3>MAX_GRIDY ) return;
		if( eTNCls_Warrior > iArgument4 || eTNCls_NPC < iArgument4 ) iArgument4 = eTNCls_Warrior;
		if( eTNClan_NPC < iArgument5 || eTNClan_NoTrimuritiy > iArgument5 ) return;
		// eTNCls_NPC(19) 일 경우는 NPC-Monster의 형태를 취한다.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			pMob[a_iHandle].Summon( iArgument1/*tribe*/, 1/*pop#*/, eTNPrdt_PopRaise, iArgument4/*class1*/, eTNCls2_Basic/*class2*/, iArgument5/*clan*/, 0/*Direction*/, iArgument2, iArgument3, 0/*Enemy*/, false, 0, 0, 15 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summonpet" ) )	// monster ID, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClan = iArgument2;
			int iDuration = iArgument3;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, eTNCls_Summoned, eTNCls2_Pet, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration, 0, 16 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summonInteractor" ) )	// monster ID, class1, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClass1 = iArgument2;
			int iClan = iArgument3;
			int iDuration = iArgument4;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, iClass1, eTNCls2_Basic, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration, 0, 17 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/height" ) )	// mob handle
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )
		{	
			int x, y;
			x = pMob[iTarget].TargetX;
			y = pMob[iTarget].TargetY;
			int iHeight = g_krgCell[y][x].usHeight;
			sprintf( szResult, "height:%d(%d,%d), mob:%d", iHeight, x, y, iTarget );
		}
		else
		{
		    sprintf( szResult, "%s>  invalid mobile handle", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/SetHeight" ) )	// obstacle, character
	{
		int iOld = g_irgSetting[eCnst_ObstacleHeight];
		g_irgSetting[eCnst_ObstacleHeight] = iArgument1; // obstacle
		g_irgSetting[eCnst_CharacterHeight] = iArgument2; // character

		sprintf( szResult, "The height of a obstacle:%d(old:%d)", g_irgSetting[eCnst_ObstacleHeight], iOld );
	}
	else if( !strcmp( szCmd, "/army" ) )
	{
		if( 1 > iArgument2 ) iArgument2 = 1;
		if( 20 < iArgument2 ) iArgument2 = 20;
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iSize = 1;
			int iBodyRadius = 1;
			if( 0 >= iSize ) return;

			krgPos[0].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[0].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );
			krgPos[1].x = pMob[a_iHandle].TargetX - ( iBodyRadius );
			krgPos[1].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );
			krgPos[2].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );

			krgPos[3].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[3].y = pMob[a_iHandle].TargetY - ( iBodyRadius );
			krgPos[4].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = pMob[a_iHandle].TargetY - ( iBodyRadius );

			krgPos[5].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[5].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = pMob[a_iHandle].TargetX - ( iBodyRadius );
			krgPos[6].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );

			if( eFollower_MaxCount < iArgument2 ) iArgument2 = eFollower_MaxCount;
			if( 1 > iArgument2 ) iArgument2 = 1;
			int iIndex = 0;
			int iClan = 0;
			if( 0 == iArgument3 ) iClan = pMob[a_iHandle].m_byClan;
			if( eTNClan_GM == iClan ) iClan = eTNClan_Neutral;

            for( int iCount = 0; iCount < iArgument2; ++iCount )
            {
				int x = 0, y = 0;
				x = krgPos[iIndex].x + rand() % iSize;
				y = krgPos[iIndex].y + rand() % iSize;
				++iIndex;
				if( 7 < iIndex ) iIndex = 0;
				int iFollower = pMob[a_iHandle].m_irgFollower[iCount];
				if( MAX_USER <= iFollower && MAX_MOB > iFollower ) KillMonster( iFollower ); //pMob[iFollower].MOB.nHP = 0;
				pMob[a_iHandle].m_irgFollower[iCount] = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Follower, 0, iClan, 0, x, y, 0, false, 0, 0, 18 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/releaseArmy" ) )
	{
		for( int i = 0; i < eFollower_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgFollower[i];
			KillMonster( iMob );
			/*
			pMob[iMob].MOB.nHP = 0; 
			pMob[iMob].CurrentTarget = 0;
			pMob[iMob].m_eFSM = eTNFsm_Dead;
			*/
		}

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/account" ) )		// target ID
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			sprintf( szResult, "%s> Account:%s", a_pCmd, pUser[iArgument1].AccountName );		
		}
		else
		{
			sprintf( szResult, "%s> invalid ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/atk" ) )
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			for( int iIndex = 0; iIndex < eFollower_MaxCount; ++iIndex )
			{
				int iFollowerIndex = pMob[a_iHandle].m_irgFollower[iIndex];
				if( MAX_USER > iFollowerIndex || MAX_MOB <= iFollowerIndex ) continue;
				pMob[iFollowerIndex].m_kLastTime.uiSelectTarget = CurrentTime + 5000;
				pMob[iFollowerIndex].CurrentTarget = iArgument1;
				pMob[iFollowerIndex].OnUnderAttack( iArgument1 );
			}
		}
		else if( 0 == iArgument1 )
		{ // 산개하여 주위의 모든 mob(berserk는 제외)을 공격한다. // berserk 성향으로 바꾼다.

		}
		else
		{
			sprintf( szResult, "%s> invalid target ID", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/truesight" ) || !strcmp( szCmd, "/투시" ) )
	{
		TNEFFECT kEffect;
		kEffect.iID = eTNAfn_WizardEyes;
		kEffect.iDuration = 3600000; // 60분
		kEffect.iParam1 = 0;
		kEffect.iParam2 = 0;
		pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle );
		pMob[a_iHandle].NotifyUpdateStatusMsg();
		pUser[a_iHandle].cSock.SendMessage();

		sprintf( szResult, "%s> truesight is activated.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/강퇴" ) || !strcmp( szCmd, "/kickout" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			MSG_Broadcast kMsg; ZeroMemory(&kMsg, sizeof(kMsg));
			kMsg.wType = _MSG_Broadcast;
			kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

			kMsg.byMsgType = MESSAGE_SERVERMSG;
			kMsg.byBgColor = 14;
			kMsg.byTextColor = 15;
			kMsg.byMsgType = 1; 

			if( eCountryKorea == g_eCountryID ) strncpy( kMsg.szMsg, g_pMessageStringTable[_DisconnectedToServer], sizeof(kMsg.szMsg));			
			else strncpy( kMsg.szMsg, g_pMessageStringTable[_KickedByGM], sizeof(kMsg.szMsg));			
			strncpy( kMsg.szName, pMob[a_iHandle].MOB.szName, SZNAME_LENGTH );
			kMsg.byTrimuriti = eTNClan_GM;
			pUser[iTarget].cSock.AddMessage((char*)&kMsg, sizeof(kMsg));

			CloseUser( iTarget );
			sprintf( szResult, "%s> The target user will be disconnected in 15 seconds", a_pCmd );
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/위치" ) || !strcmp( szCmd, "/where" ) )// ok
    {
		int iTarget = GetMOBID( szArgument1 );
		if( 0 < iTarget )	//	동일지역내 상대방 존재
		{	
			if( MAX_USER <= iTarget ) return;		  
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/whereid" ) )// ok
    {
		int iTarget = GetMOBIDFromID( szArgument1 );
		if( 0 < iTarget )	//	동일지역내 상대방 존재
		{	
			if( MAX_USER <= iTarget ) return;		  
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "ID:%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
			sprintf( szResult, "ID:%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/wheremob" ) )// ok
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{	
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
    }
    else if( !strcmp( szCmd, "/equip" ) || !strcmp( szCmd, "/장비" ) )
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{			
			STRUCT_ITEM krgItem[MAX_EQUIP];
			memcpy( krgItem, pMob[iTarget].MOB.Equip, sizeof(krgItem) );

			for( int i = 0; i < MAX_EQUIP; ++i )
			{
				if( 0 < krgItem[i].snIndex ) krgItem[i].snIndex += (HT_PARAMTYPE_ITEM_START - 1);
				if( 0 < krgItem[i].snDurability ) krgItem[i].snDurability = krgItem[i].snDurability / 100 + 1;
			}

			sprintf( szResult, "%s> Helmet:%d(%d,%d),EarR:%d,EarL:%d,Neck:%d,Armor:%d(%d,%d), Belt:%d(%d,%d),HandR:%d(%d,%d),HandL:%d(%d,%d), Boots:%d(%d,%d),Gloves:%d(%d,%d),Pants:%d(%d,%d), BraR:%d,BraL:%d,RingR:%d,RingL:%d"
				, a_pCmd, krgItem[eTNEqu_Helmet].snIndex, krgItem[eTNEqu_Helmet].byRefineLevel, krgItem[eTNEqu_Helmet].snDurability
				, krgItem[eTNEqu_EarringRight].snIndex, krgItem[eTNEqu_EarringLeft].snIndex
				, krgItem[eTNEqu_Necklace].snIndex
				, krgItem[eTNEqu_Armor].snIndex, krgItem[eTNEqu_Armor].byRefineLevel, krgItem[eTNEqu_Armor].snDurability
				, krgItem[eTNEqu_Belt].snIndex, krgItem[eTNEqu_Belt].byRefineLevel, krgItem[eTNEqu_Belt].snDurability
				, krgItem[eTNEqu_OneHandWeapon].snIndex, krgItem[eTNEqu_OneHandWeapon].byRefineLevel, krgItem[eTNEqu_OneHandWeapon].snDurability
				, krgItem[eTNEqu_Shield].snIndex, krgItem[eTNEqu_Shield].byRefineLevel, krgItem[eTNEqu_Shield].snDurability
				, krgItem[eTNEqu_Boots].snIndex, krgItem[eTNEqu_Boots].byRefineLevel, krgItem[eTNEqu_Boots].snDurability
				, krgItem[eTNEqu_Gloves].snIndex, krgItem[eTNEqu_Gloves].byRefineLevel, krgItem[eTNEqu_Gloves].snDurability
				, krgItem[eTNEqu_Pants].snIndex, krgItem[eTNEqu_Pants].byRefineLevel, krgItem[eTNEqu_Pants].snDurability
				, krgItem[eTNEqu_BraceletRight].snIndex, krgItem[eTNEqu_BraceletLeft].snIndex
				, krgItem[eTNEqu_RingRight].snIndex, krgItem[eTNEqu_RignLeft].snIndex
				);
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}        
    }
	else if( !strcmp( szCmd, "/weapon" ) || !strcmp( szCmd, "/무기" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_OneHandWeapon];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/armor" ) || !strcmp( szCmd, "/갑옷" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Armor];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/pants" ) || !strcmp( szCmd, "/바지" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Pants];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/helmet" ) || !strcmp( szCmd, "/투구" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Helmet];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);     
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/shield" ) || !strcmp( szCmd, "/방패" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Shield];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);            
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/gloves" ) || !strcmp( szCmd, "/장갑" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Gloves];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/boots" ) || !strcmp( szCmd, "/신발" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Boots];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( (!strcmp( szCmd, "/JudgeSurvival" )) || !strcmp( szCmd, "/서바이벌판정" )  )		// mob handle, HP
	{
		if( eZone_Stronghold != g_iZoneID ) return;

		char szSurvivals[512] = { 0,0,0, };
		if( 1 == iArgument1 )
		{
			g_kArena.OutputSurvivals( szSurvivals, 0 );			
			PostMessageToZone( szSurvivals );
		}
		else if( 0 == iArgument1 ) g_kArena.OutputSurvivals( szSurvivals, 1 ); // 영자에게만 결과를 보여준다.

		//g_kArena.CheckWinner( 1 ); // winner를 검사하고, 파티원이 아닌 유저를 알린다.
		sprintf( szResult, "%s> %s", a_pCmd, szSurvivals );
	}
	else if( !strcmp( szCmd, "/ChangeAttackArmorType" ) )		// armor attack coefficient
	{
		if( (0 <= iArgument1) && ( eAAC_ArmorTypeCount > iArgument1) && (0 <= iArgument2) && ( eAAC_AttackTypeCount > iArgument2) )
		{
			g_srgAttackTypeVSArmorTypeChart[iArgument1][iArgument2] = iArgument3;
			sprintf( szResult, "%s> successfully~ => armor:%d, attack:%d, coefficient:%d", a_pCmd, iArgument1, iArgument2, iArgument3 );
		}
		else
		{
			sprintf( szResult, "%s> failed~  => armor:%d, attack:%d, coefficient:%d", a_pCmd, iArgument1, iArgument2, iArgument3 );
		}
	}
	else if( !strcmp( szCmd, "/Bless" ) )		// mob handle
	{
		if( eZone_Cruma != g_iZoneID ) return;

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			//TriggerEvent( iArgument1, 25, pMob[iArgument1].TargetX, pMob[iArgument1].TargetY, g_irgGod[pMob[iArgument1].m_byClan], 112 );
			//pMob[iArgument1].MOB.nHP = iArgument2;

			int iLeader = pMob[iArgument1].Leader;
			if( 0 >= iLeader ) iLeader = iArgument1; // 자신이 리더이다.

			if( !pMob[iLeader].IsDead() )
			{
				if( !(eTNVSAfn_HaveKalaCore & pMob[iLeader].m_iAffections) ) 
					TriggerEvent( iLeader, 25, pMob[iLeader].TargetX, pMob[iLeader].TargetY, g_irgGod[pMob[iLeader].m_byClan], 111 );
			}

			// 파티원들 소환
			for( int d = 0; d < MAX_PARTY; ++d )
			{   
				int fol = pMob[iLeader].m_irgParty[d];

				if( 0 > fol || MAX_USER <= fol ) continue;
				if( pMob[fol].IsDead() ) continue;
				if( eTNVSAfn_HaveKalaCore & pMob[fol].m_iAffections ) continue;

				TriggerEvent( fol, 25, pMob[fol].TargetX, pMob[fol].TargetY, g_irgGod[pMob[fol].m_byClan], 110 );
			}

			sprintf( szResult, "%s> %s(%d) is blessed!!!", a_pCmd, pMob[iArgument1].MOB.szName, iArgument1 );
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd );   		    
	}
	else if( !strcmp( szCmd, "/ChangeHP" ) )		// mob handle, HP
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].MOB.nHP = iArgument2;
			sprintf( szResult, "%s> HP:%d", a_pCmd, pMob[iArgument1].MOB.nHP );
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd );   		    
	}
	else if( !strcmp( szCmd, "/SearchMonsterHandle" ) )
	{
		iArgument1 = iArgument1;

		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe ) break;
			}

			if( MAX_MOB != i ) sprintf( szResult, "%s> Monster ID: %d",  a_pCmd, i ); // 찾았다면, ...
			else sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterStat" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{

			sprintf( szResult, "%s> Lvl:%d, Trimu:%d, AI:%d, FSM:%d, HP:%d/%d, AR:%d, DR:%d, DF:%d(AC:%d), Resist(%d,%d,%d,%d)", a_pCmd
				, pMob[iArgument1].MOB.byLevel, pMob[iArgument1].m_byClan, pMob[iArgument1].MOB.byQuest[eMonPrty_AI]
				, pMob[iArgument1].m_eFSM, pMob[iArgument1].MOB.nHP, pMob[iArgument1].m_iMaxHP
				, pMob[iArgument1].m_kCombatFactors.iAttackRate, pMob[iArgument1].m_kCombatFactors.iDodgeRate
				, pMob[iArgument1].m_kCombatFactors.iDefense, pMob[iArgument1].m_kCombatFactors.iAC, pMob[iArgument1].m_kCombatFactors.irgResist[0], pMob[iArgument1].m_kCombatFactors.irgResist[1]
				, pMob[iArgument1].m_kCombatFactors.irgResist[2], pMob[iArgument1].m_kCombatFactors.irgResist[3]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid Argumenteter1. argument1:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterData" ) ) // 간단한 monster 정보를 화면에 출력
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;

			sprintf( szResult, "%s> Lvl:%d, Trimu:%d, AI:%d, HP:%d, AR:%d, DR:%d, AC:%d, Resist(%d,%d,%d,%d), ArmorType:%d", a_pCmd
				, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].nHP
				, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart  // AR/DR/AC
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
				, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/RecordMonsterData" ) ) // detail한 정보를 서버 log file에 기록
	{
		if( 2000 <= iArgument1 && 3000 > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;

			char chBuf[1024] = { 0,0,0, };
			sprintf(chBuf, "\r\n=> ID:%d, Lvl:%d, Trimu:%d, AI:%d, Class:%d, BlockedCell:%d, HP:%d, AR:%d, DR:%d, AC:%d, Sight(%d,%d), CantDetect:%d, Movement:%d, MvSpeed(%d,%d), Resist(%d,%d,%d,%d), Size:%d, Speech(%d/%d), HPRecv:%d, Cond(%d,%d,%d), cond2(%d,%d,%d,%d,%d,%d), PopDelay(%d,%d), skill(%d,%d,%d,%d,%d,%d,%d,%d), sklPtrn(%d,%d,%d,%d / DefaultOnly:%d), SelectTarget(Time:%d, %d,%d,%d,%d / DefaultOnly:%d), Immu(%d,%d), ArmorType:%d	\
							   \r\n\t RewPrana:%d, RewBraman:%d, RewGold:%d, RewItem0(%d,%d) RewItem1(%d,%d), RewItem2(%d,%d), RewItem3(%d,%d), RewItem4(%d,%d), RewItem5(%d,%d), RewItem6(%d,%d), RewItem7(%d,%d), RewItem8(%d,%d), RewItem9(%d,%d), Reserved(0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d) \r\n"
, pMonsterData[iIndex].snTribe, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].byQuest[eMonPrty_Class], pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart
, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight], pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex, pMonsterData[iIndex].byQuest[eMonPrty_Movement], pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed], pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed]
, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
, pMonsterData[iIndex].byQuest[eMonPrty_Size], pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate], pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI], pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery]
, pMonsterData[iIndex].byQuest[eMonPrty_AggrCond], pMonsterData[iIndex].byQuest[eMonPrty_TraceCond], pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond]  // cond1
, pMonsterData[iIndex].byQuest[eMonPrty_HelpCond], pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount], pMonsterData[iIndex].byQuest[eMonPrty_LinkCond], pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount], pMonsterData[iIndex].byQuest[eMonPrty_FleeCond], pMonsterData[iIndex].byQuest[eMonPrty_FleeCondCount] // cond2
, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex // pop delay
, pMonsterData[iIndex].Equip[0].snIndex, pMonsterData[iIndex].Equip[1].snIndex, pMonsterData[iIndex].Equip[2].snIndex, pMonsterData[iIndex].Equip[3].snIndex, pMonsterData[iIndex].Equip[4].snIndex, pMonsterData[iIndex].Equip[5].snIndex, pMonsterData[iIndex].Equip[6].snIndex, pMonsterData[iIndex].Equip[7].snIndex // skill
, pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3], pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly]  // skill pattern
, pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3], pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly]  // select target
, pMonsterData[iIndex].nGuildID, pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst]
, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType]
, pMonsterData[iIndex].nPrana, pMonsterData[iIndex].nBramanPoint, pMonsterData[iIndex].nRupiah
, pMonsterData[iIndex].Inven[0].snIndex, g_krgRewardItemRate[iIndex][0].get_Rate()
, pMonsterData[iIndex].Inven[1].snIndex, g_krgRewardItemRate[iIndex][1].get_Rate()
, pMonsterData[iIndex].Inven[2].snIndex, g_krgRewardItemRate[iIndex][2].get_Rate()
, pMonsterData[iIndex].Inven[3].snIndex, g_krgRewardItemRate[iIndex][3].get_Rate()
, pMonsterData[iIndex].Inven[4].snIndex, g_krgRewardItemRate[iIndex][4].get_Rate()
, pMonsterData[iIndex].Inven[5].snIndex, g_krgRewardItemRate[iIndex][5].get_Rate()
, pMonsterData[iIndex].Inven[6].snIndex, g_krgRewardItemRate[iIndex][6].get_Rate()
, pMonsterData[iIndex].Inven[7].snIndex, g_krgRewardItemRate[iIndex][7].get_Rate()
, pMonsterData[iIndex].Inven[8].snIndex, g_krgRewardItemRate[iIndex][8].get_Rate()
, pMonsterData[iIndex].Inven[9].snIndex, g_krgRewardItemRate[iIndex][9].get_Rate()
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved0], pMonsterData[iIndex].byQuest[eMonPrty_Reserved1], pMonsterData[iIndex].byQuest[eMonPrty_Reserved2]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved3], pMonsterData[iIndex].byQuest[eMonPrty_Reserved4], pMonsterData[iIndex].byQuest[eMonPrty_Reserved5]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved6], pMonsterData[iIndex].byQuest[eMonPrty_Reserved7]
);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" );
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd);
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 2000, 2999 );   		    
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterStatus" ) )		// mob id
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iDist = CalDistance( iArgument1, pMob[iArgument1].CurrentTarget );
			char chBuf[1024] = { 0,0,0, };
			//sprintf(chBuf, "\r\n=> ID:%s, Mode:%d, CurrentTarget:%d, iDist:%d, EnemyList(%d,%d,%d,%d,%d), AttackerList(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d)
			sprintf(chBuf, "\r\n=> ID:%s, Mode:%d, CurrentTarget:%d, iDist:%d, AttackerCount:%d, AttackerList(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d), AttackerList2(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d) \
								\r\nCantTraceTarget:%d, AtkCount:%d, TraceCount:%d, TotalTrace:%d, eStatus:%d, Affections:%h, CastCount:%d, Now:%u, ActionLock:%u, m_kLastTime.uiSelectTarget:%u \
								\r\nLvl:%d, Trimu:%d, Class:%d, BlockedCell:%d, Sight(%d,%d), MvSpeed(%d), HP:%d(%d), AR:%d, DR:%d, DF:%d,, Resist(%d,%d,%d,%d), Immunity:%d, skill(%d,%d,%d,%d,%d), m_iSkillCharged:%d \
								\r\n"
, pMob[iArgument1].MOB.szName
, pMob[iArgument1].Mode, pMob[iArgument1].CurrentTarget, iDist//, pMob[iArgument1].EnemyList[0], pMob[iArgument1].EnemyList[1], pMob[iArgument1].EnemyList[2], pMob[iArgument1].EnemyList[3], pMob[iArgument1].EnemyList[4], pMob[iArgument1].EnemyList[5]
, pMob[iArgument1].m_iAttackerCount
, pMob[iArgument1].m_krgAttacker[0].iID, pMob[iArgument1].m_krgAttacker[0].iScore, pMob[iArgument1].m_krgAttacker[1].iID, pMob[iArgument1].m_krgAttacker[1].iScore, pMob[iArgument1].m_krgAttacker[2].iID, pMob[iArgument1].m_krgAttacker[2].iScore, pMob[iArgument1].m_krgAttacker[3].iID, pMob[iArgument1].m_krgAttacker[3].iScore
, pMob[iArgument1].m_krgAttacker[4].iID, pMob[iArgument1].m_krgAttacker[4].iScore, pMob[iArgument1].m_krgAttacker[5].iID, pMob[iArgument1].m_krgAttacker[5].iScore, pMob[iArgument1].m_krgAttacker[6].iID, pMob[iArgument1].m_krgAttacker[6].iScore, pMob[iArgument1].m_krgAttacker[7].iID, pMob[iArgument1].m_krgAttacker[7].iScore
, pMob[iArgument1].m_krgAttacker[8].iID, pMob[iArgument1].m_krgAttacker[8].iScore, pMob[iArgument1].m_krgAttacker[9].iID, pMob[iArgument1].m_krgAttacker[9].iScore, pMob[iArgument1].m_krgAttacker[10].iID, pMob[iArgument1].m_krgAttacker[10].iScore, pMob[iArgument1].m_krgAttacker[11].iID, pMob[iArgument1].m_krgAttacker[11].iScore
, pMob[iArgument1].m_krgAttacker[12].iID, pMob[iArgument1].m_krgAttacker[12].iScore, pMob[iArgument1].m_krgAttacker[13].iID, pMob[iArgument1].m_krgAttacker[13].iScore, pMob[iArgument1].m_krgAttacker[14].iID, pMob[iArgument1].m_krgAttacker[14].iScore, pMob[iArgument1].m_krgAttacker[15].iID, pMob[iArgument1].m_krgAttacker[15].iScore
, pMob[iArgument1].m_iCantTraceTarget, pMob[iArgument1].m_iAttackCount, pMob[iArgument1].m_iTraceCount, pMob[iArgument1].m_iTotalTraceCount, pMob[iArgument1].m_eStatus, (int)pMob[iArgument1].m_iAffections, pMob[iArgument1].m_iCastCount
, CurrentTime, pMob[iArgument1].m_uiActionLock, pMob[iArgument1].m_kLastTime.uiSelectTarget
, pMob[iArgument1].MOB.byLevel, pMob[iArgument1].m_byClan, pMob[iArgument1].MOB.byClass1, pMob[iArgument1].m_iBlockedCell
, pMob[iArgument1].m_kSight.sPeace, pMob[iArgument1].m_kSight.sCombat, pMob[iArgument1].m_iMoveSpeed
, pMob[iArgument1].MOB.nHP, pMob[iArgument1].m_irgHPRecovery[0], pMob[iArgument1].m_kCombatFactors.iAttackRate, pMob[iArgument1].m_kCombatFactors.iDodgeRate, pMob[iArgument1].m_kCombatFactors.iDefense
, pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Fire], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Cold], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Lightning], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Poison], pMob[iArgument1].m_iImmunity
, pMob[iArgument1].m_krgSkill[0].iIndex-500, pMob[iArgument1].m_krgSkill[1].iIndex-500, pMob[iArgument1].m_krgSkill[2].iIndex-500, pMob[iArgument1].m_krgSkill[3].iIndex-500, pMob[iArgument1].m_krgSkill[4].iIndex-500, pMob[iArgument1].m_iSkillCharged

);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" );
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd);
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterMode" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			sprintf( szResult, "Monster(%d) Mode:%d",  iArgument1, pMob[iArgument1].Mode );
		}
	}
	else if( !strcmp( szCmd, "/checkmonster" ) )
	{
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			sprintf( szResult, "%s> ",  a_pCmd );
			int iCount = 0;
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe )
				{
					char szMonsterID[128] = { 0,0,0, };
					sprintf( szMonsterID, "%d: %d, ",  iCount, i );
					strcat( szResult, szMonsterID );
					++iCount;				
				}
				if( 20 < iCount ) break;
			}

			if( 0 == iCount ) sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 );
		}
		else		
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetKalaSystem" ) )
	{
		// 운반하고 있는 모든 kala-core 제거
		// 땅에 떨어져 있는 모든 kala-core 제거
		// altar에 있는 모든 kala monster 제거
		// rewarder NPC 중립화
		// 차투랑가 portal NPC 중립화
		// 기록 파일 갱신
	}
	else if( !strcmp( szCmd, "/printkalacoreinfo" ) )
	{
		if( SERVER_KRUMA_HIGH != iZoneID ) return;
		g_kKalaSystem.DropKalaCoreInPC();
		g_kKalaSystem.CheckCountNRecovery();
		g_kKalaSystem.PrintScreen( szResult );
		MoveKalaRewarder();		
	}
	else if( !strcmp( szCmd, "/removekalacore" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			RemoveKalaCoreInInventory( iTarget );
			sprintf( szResult, "%s> the command is completed successfully.", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> invalid ID.", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/dropkalacore" ) )
	{	
		return;
		if( SERVER_KRUMA_HIGH != iZoneID ) return;
		if( (eKalaCore_Brahma == iArgument1) || (eKalaCore_Vishnu == iArgument1) || (eKalaCore_Siva == iArgument1) ) 
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = eDur_Indestructible;
			kItem.byCount = 1;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;
			CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );

			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, ">>> GM %s drop a kala-core(%d) at L(%d,%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[a_iHandle].MOB.szName, iArgument1, pMob[a_iHandle].TargetX-1, pMob[a_iHandle].TargetY-1, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
			}
			NotifyRvRStatus();
		}
		else		
		{
			sprintf( szResult, "%s> invalid kala-core ID. id: brahma:8051, vishnu:8052, siva:8053 ", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/KickOutAllPlayers" ) )
	{
		for( int i = 1; i < MAX_USER; ++i )
		{
			if( USER_PLAY != pUser[i].Mode ) continue;
			ReturnPCToSaveZone( i );
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/CountMonster" ) )
	{
		if( eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1 )
		{
			int iCount = 0;
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].m_byClan )
				{
					if( 0 < pMob[i].MOB.nHP ) ++iCount;
				}
			}

			sprintf( szResult, "%s> count:%d ", a_pCmd, iCount );
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/KillMonsterAll" ) )
	{
		for( int i = MAX_USER; i < MAX_MOB; ++i )
		{
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
			if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

			KillMonster( i );
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/KillClanMonster" ) )
	{
		if( (eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1) || (eTNClan_Stronghold1 <= iArgument1 && eTNClan_Stronghold4 >= iArgument1) )
		{
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
				if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

				if( iArgument1 == pMob[i].m_byClan )
				{
					KillMonster( i );
				}
			}

			sprintf( szResult, "%s> successful", a_pCmd );
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/killkala" ) )
	{
		/*
		iArgument1 = atoi( szArguments );
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				KillMonster( iArgument1 );
				//MoveKalaRewarder();

				int iAltarIndex = 0;
				for(; iAltarIndex < eKalaAltar_MaxCount; ++iAltarIndex )
				{ // 칼라 제단에 위치하고 있는, ...
					int iMobHandle = g_irgKalaAltar[iAltarIndex];
					if( MAX_USER <= iMobHandle && MAX_MOB > iMobHandle )
					{
						if(iArgument1 == iMobHandle )
						{
							g_irgKalaAltar[iAltarIndex] = 0;
							break;
						}
					}
				}

				{
					SYSTEMTIME st;
					GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf( chBuf, "GM destroied the kala(%d) at altar(%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[iArgument1].MOB.snTribe, iAltarIndex, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
				}
			}
			else sprintf( szResult, "%s> %d is not the kala.", a_pCmd, iArgument1 );   		    
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/방향" ) )
	{ // mob id, direction(new)
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			int iMob = iArgument1;
			int iOldDir = pMob[iMob].m_iDirection;
			pMob[iMob].m_iDirection = iArgument2;
			S_SCP_INIT_OTHER_MOB sm;
			GetCreateMob( iMob, &sm );
			GridMulticast( pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm, 0, 100 );
			
			sprintf( szResult, "%s> Mob:%d, Dir:%d->%d", a_pCmd, iMob, iOldDir, pMob[iMob].m_iDirection );
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/sp" ) || !strcmp( szCmd, "/말" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].DeliverComment( &a_pCmd[9] );
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/TriggerEvent" ) )		// event ID, NPC ID
	{
		if( 0 < a_iHandle && MAX_USER > a_iHandle )
			TriggerEvent( a_iHandle, iArgument1, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, iArgument2, 100 );
		else TriggerEvent( 0, iArgument1, 0, 0, iArgument2, 101 );	    

		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/attack" ) || !strcmp( szCmd, "/공격" ) )		// id, target
	{
		if( ( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) && ( 0 < iArgument2 && MAX_MOB > iArgument2 ) )
		{
			pMob[iArgument1].m_kLastTime.uiSelectTarget = CurrentTime + 10000;
			pMob[iArgument1].CurrentTarget = iArgument2;
			pMob[iArgument1].OnUnderAttack( iArgument2 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID(%d) or invalid target handle(%d).", a_pCmd, iArgument1, iArgument2 );   		    
		}
	}
	else if( !strcmp( szCmd, "/attack2" ) || !strcmp( szCmd, "/공격2" ) )
	{
		if( 0 >= a_iHandle || MAX_USER <= a_iHandle) return;
		if( MAX_USER <= iArgument1 && MAX_MOB >= iArgument1 )
		{
			int TargetX = pMob[a_iHandle].TargetX;
			int TargetY = pMob[a_iHandle].TargetY;
			int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
			int x, y;
			for( int i = 0; i < iMaxIndex; ++i )
			{
				x = TargetX + g_pDetectEnemyTable[i][0];
				y = TargetY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
				if	(pMob[tmob].MOB.nHP <=0) continue;
				if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
				pMob[tmob].m_kLastTime.uiSelectTarget = CurrentTime + 10000;
				pMob[tmob].CurrentTarget = iArgument1;
				pMob[tmob].OnUnderAttack( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> Invalid target handle(%d).", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/killmonster" ) || !strcmp( szCmd, "/킬몬" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				sprintf( szResult, "%s> can't kill the kala!!! use /killkala command.", a_pCmd );  
			}
			else
			{
				KillMonster( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
	}
	else if( !strcmp( szCmd, "/bufnpc" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_HealPlus;
			kEffect.iDuration = 1800000;
			kEffect.iParam1 = iArgument2;
			pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );

			TNEFFECT kEffect2;
			kEffect2.iID = eTNAfn_RecoverTPPlus;
			kEffect2.iDuration = 1800000;
			kEffect2.iParam1 = iArgument3;
			pMob[iArgument1].AddEffect( kEffect2, a_iHandle, a_iHandle );

			TNEFFECT kEffect3;
			kEffect3.iID = eTNAfn_MaxHPPlus2;
			kEffect3.iDuration = 1800000;
			kEffect3.iParam1 = iArgument4;
			pMob[iArgument1].AddEffect( kEffect3, a_iHandle, a_iHandle );

			TNEFFECT kEffect4;
			kEffect4.iID = eTNAfn_MaxTPPlus2;
			kEffect4.iDuration = 1800000;
			kEffect4.iParam1 = iArgument5;
			pMob[iArgument1].AddEffect( kEffect4, a_iHandle, a_iHandle );

		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );   		    
		}
	}
	else if( !strcmp( szCmd, "/DebugDur" ) )
	{
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].m_iDebugFlag2 = 0;
			}
			else 
			{
				pMob[iArgument1].m_iDebugFlag2 = 1;
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/Log" ) || !strcmp( szCmd, "/log" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Log );
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000; // 10분에서 1시간
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Log;
				kEffect.iDuration = iArgument2;
				kEffect.iParam1 = 0;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeIntervalHackCount" ) ) //
	{ // obstacle, character
		g_irgSetting[eCnst_SkillCastIntervalHack] = iArgument1;

		sprintf( szResult, "%s> Hack interval for casting a skill, limit count:%d", a_pCmd, g_irgSetting[eCnst_SkillCastIntervalHack] );
	}
	else if( !strcmp( szCmd, "/ChangeHeightSetting" ) ) //
	{ // obstacle, character
		g_irgSetting[eCnst_ObstacleHeight] = iArgument1;
		g_irgSetting[eCnst_CharacterHeight] = iArgument2;

		sprintf( szResult, "%s> Height > Obstacle:%d, Character:%d", a_pCmd, g_irgSetting[eCnst_ObstacleHeight], g_irgSetting[eCnst_CharacterHeight] );
	}
	else if( !strcmp( szCmd, "/logx" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{// mob handle, debug type, duration(10분), on/off(on)
		int iDebugType = eTNDbg_None;
		iArgument3 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument4 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Debug );
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 1 == iArgument2 ) iDebugType = eTNDbg_Combat;
				else if( 2 == iArgument2 ) iDebugType = eTNDbg_Pet;
				else if( 3 == iArgument2 ) iDebugType = eTNDbg_Immunity;
				else if( 4 == iArgument2 ) iDebugType = eTNDbg_Affection;

				if( 0 >= iArgument3 || 3600000 < iArgument3 ) iArgument3 = 600000; // 10분에서 1시간
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Debug;
				kEffect.iDuration = iArgument3;
				kEffect.iParam1 = iDebugType;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> debug ID(%d), debug type:%d, dur:10 minutes.", a_pCmd, iArgument1, iArgument2 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/logimmu" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{// mob hndl
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_LogImmu );
			}
			else 
			{
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000; // 10분 설정
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_LogImmu;
				kEffect.iDuration = iArgument2;
				kEffect.iParam1 = 0;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> write log immunity for ID(%d), dur:10 minutes. Immunity:%d(%h)", a_pCmd, iArgument1, pMob[iArgument1].m_iImmunity, pMob[iArgument1].m_iImmunity );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat();
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill();
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/eventlog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
		else
		{
			if( eTNSwitch_EventLog & g_iSwitch ) g_iSwitch = eTNSwitch_EventLog ^ eTNSwitch_EventLog;
		}
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_EventLog & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/contactnpclog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_ContactNPC;
		else
		{
			if( eTNSwitch_ContactNPC & g_iSwitch ) g_iSwitch = g_iSwitch ^ eTNSwitch_ContactNPC;
		}

		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_ContactNPC & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/PopMonster" ) )
	{
		/*
		iArgument1 = atoi( szArguments );
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_kLastTime.uiKilled = 0; 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/recoverkalasystem" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_RecvKalaSystem;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_RecvKalaSystem;
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_RecvKalaSystem & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/DecPrana" ) ) // ok
	{
		if( !strcmp( "off", szArgument1 ) ) g_bDecPrana = true;
		else g_bDecPrana = false;
		sprintf( szResult, "%s> %d(if the value is equal to 1, the system don't decrease prana when PC is killed.)", a_pCmd, g_bDecPrana );
/*
	    iArgument1 = atoi( szArguments );
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_DecPrana; //g_bDecPrana = true;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_DecPrana; // on
		sprintf( szResult, "%s> %d(1이 포함되어 있으면 스위치는 off, 죽어도 프라나가 줄지 않는다.)", a_pCmd, g_iSwitch );
*/
	}
	/*
	else if( !strcmp( szCmd, "/ResetSkill" ) ) // ok
	{
	    iArgument1 = atoi( szArguments );
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_ResetSkill; // off
		else g_iSwitch = g_iSwitch ^ eTNSwitch_ResetSkill;		 // on
		sprintf( szResult, "%s> %d(2가 포함되어 있으면, 스위치는 off, 스킬리셋이 동작하지 않는다.)", a_pCmd, g_iSwitch );
	}
	*/
/*
	else if( !strcmp( szCmd, "/cc" ) )
	{
		iArgument1 = atoi( szArguments ); // index
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 );
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] );
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 );
		}
	}		   szResult
*/
	else if( !strcmp( szCmd, "/ChangeKarma" ) )
	{// character ID, karma
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].MOB.snKarma = iArgument2;
			pMob[iArgument1].BroadcastUpdateStatusMsg();
			pMob[iArgument1].NotifyUpdateStatusMsg();
			pUser[iArgument1].cSock.SendMessage(); // PC일 경우, ...
			sprintf( szResult, "%s> mob:%d, karma:%d", a_pCmd, iArgument1, pMob[iArgument1].MOB.snKarma );
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}			
	}
	else if( !strcmp( szCmd, "/PrintRwdCorrect" ) )
	{
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f, Base(%f,%f,%f), Extra(%f,%f,%f)"
			, a_pCmd
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Total], g_drgRwdCorrect[eRwd_Gold][eRwd_Total], g_drgRwdCorrect[eRwd_Braman][eRwd_Total]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Base], g_drgRwdCorrect[eRwd_Gold][eRwd_Base], g_drgRwdCorrect[eRwd_Braman][eRwd_Base]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Extra], g_drgRwdCorrect[eRwd_Gold][eRwd_Extra], g_drgRwdCorrect[eRwd_Braman][eRwd_Extra]
			);
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( eRwd_Base, iArgument1, iArgument2, iArgument3 ); // prana, gold, braman

		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f, Base(%f,%f,%f), Extra(%f,%f,%f)"
			, a_pCmd
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Total], g_drgRwdCorrect[eRwd_Gold][eRwd_Total], g_drgRwdCorrect[eRwd_Braman][eRwd_Total]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Base], g_drgRwdCorrect[eRwd_Gold][eRwd_Base], g_drgRwdCorrect[eRwd_Braman][eRwd_Base]
			, g_drgRwdCorrect[eRwd_Prana][eRwd_Extra], g_drgRwdCorrect[eRwd_Gold][eRwd_Extra], g_drgRwdCorrect[eRwd_Braman][eRwd_Extra]
			);
	}
	else if( !strcmp( szCmd, "/kickouto" ) )
	{
		TriggerEvent( 0, 30, 0, 0, 0, 102 );
		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/kickoutx" ) )
	{
		TriggerEvent( 0, 31, 0, 0, 0, 103 );
		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/RefiningRate" ) )		//	FORMAT ===> $REFINING UP,DOWN COUNT
	{	
		if(!strcmp(szArgument1,"Up"))
		{	g_ItemRefineGMScale += iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ); 
		}
		else if(!strcmp(szArgument1,"Down"))
		{	g_ItemRefineGMScale -= iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ); 
		}
		else if(!strcmp(szArgument1,"Search"))
		{	if(iArgument2>0 && iArgument2<100)
			{	char chBuf[256]={0,};
				if(g_RefineTable.GetValue2(iArgument2)>0) sprintf(szResult, "RefiningRate %d[Percent] will be succeed..", iArgument2);
				else sprintf(szResult, "RefiningRate %d[Percent] will be fail..", iArgument2);
			}	else
			{	char chBuf[256]={0,};
				sprintf(szResult, "RefiningRate's up by GM : %d", g_ItemRefineGMScale);
			}
		}
	}
	else if( !strcmp( szCmd, "/Money" ) )
	{
		pMob[a_iHandle].IncGold(iArgument1);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Prana" ) )
	{
		int nID = GetMOBID(szArgument1);
		if( (nID<=0) || (nID>=MAX_USER) ) return;
		pMob[nID].AcquirePrana(iArgument2);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/PreventWhisper" ) )
	{	
		MSG_Status sm; sm.wType = _MSG_Status;
		sm.nID = a_iHandle;
		if(!strcmp(szArgument1,"ON") || !strcmp(szArgument1,"on"))
		{	pMob[a_iHandle].MOB.byStatus |= 0x01;
			sm.byStatus = pMob[a_iHandle].MOB.byStatus;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err charstatus DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}
		}
		else if(!strcmp(szArgument1,"OFF") || !strcmp(szArgument1,"off"))
		{	pMob[a_iHandle].MOB.byStatus &= 0xFE;
			sm.byStatus = pMob[a_iHandle].MOB.byStatus;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err charstatus DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}
		}
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LogDump" ) )
	{
		fflush(fLogFile);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/MSGLogDump" ) )
	{
		MSG_ServerCommand sm; ZeroMemory(&sm, sizeof(sm));
		sm.wType = _MSG_ServerCommand; sm.byCommandType=eCommandDump;
		if(!MSGServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
		{	Log("err charstatus MSG-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
		}
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Exchange" ) )						//	For Test(in china)
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));
		bm.Packet_result = 0; bm.Time_Exchanged = 340;
		bm.ItemNo = 0;
		SendBilling3(a_iHandle, &bm, _Msg_BillTimeEx);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/DropItm" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = 10;
			kItem.byCount = 1;
			kItem.byRefineLevel = 9;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/Card" ) )
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));				//	For Test(in china)
		bm.Packet_result = 0;
		strncpy( bm.cardNumber, "23434634456353241", 20 );
		strncpy( bm.cardPassword, "33453638584785678567857812345", 20 );
		bm.cardNumber[18]=0; bm.cardNumber[19]=0;
		bm.cardPassword[18]=0; bm.cardPassword[19]=0;
		SendBilling3(a_iHandle, &bm, _Msg_BillCard);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Dress" ) )
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm)); 
		bm.Packet_result = 0; bm.article_number = 2342;
		bm.Dressed = 1;
		SendBilling3(a_iHandle, &bm, _Msg_BillDress);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Connect" ) )
	{
		if(!strcmp(szArgument1,"BILL"))
		{	int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP2;			//	필리핀은 빌링을 인라인사용한다
			int ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip, WSA_READBILL, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect BILL Server(x2) fail.","-system",0);
				BILLING=0;//무료모드로 계속한다.
			}	else
			{	_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
				SendBilling2(&sm,4);
				sprintf( szResult, "%s> Successfully", a_pCmd ); 
			}
		}
		else if(!strcmp(szArgument1,"MSG"))
		{	int * pip = (int*)LocalIP2;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 MSG Public사용
			int ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort ,*pip, WSA_READMSG, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect MSG Server(x2) fail.","-system",0);
			}
		}
	}
	else if( !strcmp( szCmd, "/View" ) )
	{
		int nID = GetMOBID(szArgument1);
		if(nID<0 || nID>=MAX_USER)
		{	sprintf(szResult, g_pMessageStringTable[_Not_Find_Others]);
			return;
		}

		int nGuildIndex = pUser[nID].nGuildIndex;
		sprintf(szResult, "Char:%s, Level:%d, Tribe:%d, MaxHP:d, CurHP:%d, Guild:%s, Trim:%d, byGMStatus:%d, Karma:%d, Class1:%d, Class2:%d, snX:%d, snZ:%d",
			szArgument1, pMob[nID].MOB.byLevel, pMob[nID].MOB.snTribe, pMob[nID].m_iMaxHP, pMob[nID].MOB.nHP, pGuild[nGuildIndex].GUILD.GuildName, pMob[nID].MOB.byTrimuriti, pMob[nID].MOB.byGMStatus,
			pMob[nID].MOB.snKarma, pMob[nID].MOB.byClass1, pMob[nID].MOB.byClass2, pMob[nID].TargetX, pMob[nID].TargetY);
	}
	else if( !strcmp( szCmd, "/IWantIt" ) )
	{
		g_GameEvent.m_IWantIt.GetRankUser(szResult);
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/Report" ) )
	{
		if(!strcmp(szArgument1,"Transparency"))		//	크루마에서 칼리아 입장 오브잭트가 생겻다고 신고 들어올 경우
		{
			int nID = iArgument2;
			if(g_bIsKaliaOpend) return;				//	칼리아던전이 오픈시간이면 당연히 보여야 한다.
			if(nID>MAX_USER && nID<MAX_MOB)
			{
				sprintf(temp, "dbg GateMob:[%d] Discoverd at pos(%d, %d), and mob is at pos(%d, %d)",
					nID, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, pMob[nID].TargetX, pMob[nID].TargetY);
			}
			else
			{
				sprintf(temp, "dbg unkowned modid : %d", nID);
			}

			Log(temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP);
			sprintf( szResult, "%s> Successfully", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/yutbet" ) )
	{
		int iPos = iArgument1;
		int iMoney = iArgument2;

		g_Yut.HT_wUserBet(pMob[a_iHandle].MOB.szName, (WORD)iPos, iMoney);
	}
	else if( !strcmp( szCmd, "/yutmoney" ) )
	{
		int iMoney = iArgument1;
		g_Yut.HT_SetYutMoney(pMob[a_iHandle].MOB.szName, iMoney);
	}
	else if( !strcmp( szCmd, "/공성날짜예약상황확인" ) )
	{
		sprintf( szResult, "%s> Friday20HH:%d, Friday22HH:%d, Saturday20HH:%d, Satuday22HH:%d, Sunday20HH:%d"
			, a_pCmd
			, g_krgEventList[100].iDuration, g_krgEventList[101].iDuration, g_krgEventList[102].iDuration, g_krgEventList[103].iDuration, g_krgEventList[104].iDuration
			);
	}
	else if( !strcmp( szCmd, "/공성날짜결정" ) )
	{
		// 성주인지 확인 단계 필요
		int iSelected = iArgument1;
		g_kSiege.SelectDate( iSelected, false );

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성상태" ) )
	{
		sprintf( szResult, "%s> ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/dump공성엔트리" ) )
	{
		g_kSiege.SaveData( szArgument1 );
		sprintf( szResult, "%s> completed successfully.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/reload공성엔트리" ) )
	{
		g_kSiege.Init();
		g_kSiege.LoadData();
		sprintf( szResult, "%s> completed successfully.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/ChangeClanForSiege" ) )
	{
		if( !g_kSiege.get_Started() ) return;

		#ifdef __TN_TOP_LOG__
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[eTNAct_ChangeClanForSiege] %dYY%dMM%dDD %2dHH%2dMI%2dSS> \r\n"
				, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				); 
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
		}
		#endif


		for( int i = 1; i < MAX_USER; ++i )
		{
			if( eTNClan_GM == pMob[i].m_byClan ) continue;
			//if( eTNClan_CastleOwner <= pMob[i].m_byClan && eTNClan_Siege4 >= pMob[i].m_byClan ) continue;
			if( USER_PLAY != pUser[i].Mode ) continue;

			byte byOld = pMob[i].m_byClan;

			int iFlag = g_kSiege.SearchEntry( pMob[i].MOB.nGuildID );
			if( -1 == iFlag ) pMob[i].m_byClan = eTNClan_Siege4;
			else pMob[i].m_byClan = iFlag;

			MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
			kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
			kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);
			kZoneSettingMsg.snSiege = 1; //g_kSiege.get_Started(); 공성종료
			pUser[i].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );

			S_SCP_INIT_OTHER_MOB sm;
			GetCreateMob( i, &sm );
			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, i);

			MSG_CHANGE_CLAN kMsg;
			kMsg.wType = MSG_CHANGE_CLAN_ID;
			kMsg.wPDULength = sizeof(MSG_CHANGE_CLAN)-sizeof(HEADER);
			kMsg.snKeyID = i;
			kMsg.byClan = pMob[i].m_byClan;
			pUser[i].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) );

			pUser[i].cSock.SendMessage();

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[eTNAct_ChangeClanForSiege] PC(%d, Name:%s, Guild:%d), clan(now:%d, old:%d) \r\n"
					,i , pMob[i].MOB.szName, pMob[i].MOB.nGuildID
					, pMob[i].m_byClan, byOld
					); 
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/InsertToSiegeEntry" ) )
	{
		int iClanSlot = iArgument1;
		int iExpandedSlot = iArgument2;
		int iGuildID = iArgument3;

		g_kSiege.RegisterEntry( iGuildID, iClanSlot, iExpandedSlot, 1);
		g_kSiege.RefreshEntry();

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/RemoveSiegeEntry" ) )
	{// guild ID
		int iGuildID = iArgument1;

		g_kSiege.RemoveEntry( iGuildID );
		g_kSiege.RefreshEntry();

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/RefreshEntry" ) )
	{
		g_kSiege.RefreshEntry();
		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성신청" ) )
	{// PC handle clanSlot expandSlot]
		// NPC와의 거리 검사가 있어야 한다.
		if( (0 < iArgument1 && MAX_USER > iArgument1) || g_kSiege.get_Started() )
		{			
			bool bBreak = false;
			if( 0 == iArgument2 ) if( TNSiege::eApplyFee_Defense > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 1 == iArgument2 ) if( TNSiege::eApplyFee_Siege1 > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 2 == iArgument2 ) if( TNSiege::eApplyFee_Siege2 > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 3 == iArgument2 ) if( TNSiege::eApplyFee_Siege3 > pMob[iArgument1].get_Gold() ) bBreak = true;

			if( bBreak )
			{// 돈이 부족하다는 메시지				
				SendClientMessage( iArgument1, g_pMessageStringTable[_HaveNotEnoughGold] );
				return;
			}

			char szNofity[512] = { 0,0,0, };
			int iGuildID = pMob[iArgument1].MOB.nGuildID;
			int iGuildIndex = pUser[iArgument1].nGuildIndex;

			int iRes = g_kSiege.RegisterEntry( iGuildID, iArgument2, iArgument3, iArgument1 ); // guild ID, clan slot, expand slot, applier
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> 이미 등록되어 있음", a_pCmd );	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> 공성 신청 기간이 마감되었음", a_pCmd );	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> 입력 오류", a_pCmd );	
			}
			else
			{
				sprintf( szResult, "%s> 공성전 등록 완료1", a_pCmd );				
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], pGuild[iGuildIndex].GUILD.GuildName );
				SendClientMessage( iArgument1, szNofity );
			}

			int iAllyGuildID = pGuild[iGuildIndex].nAlliedID;

			iRes = g_kSiege.RegisterEntry( iAllyGuildID, iArgument2, iArgument3+1, iArgument1 );
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> 연합길드(%d)가 이미 등록되어 있음", a_pCmd, iAllyGuildID );	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> 공성 신청 기간이 마감되었음", a_pCmd );	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> 연합길드 관련 입력 오류", a_pCmd );	
			}
			else
			{
				sprintf( szResult, "%s> 공성전 등록 완료2", a_pCmd );
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], g_pMessageStringTable[_AllyGuild] );
				SendClientMessage( iArgument1, szNofity );
			}

			//g_kSiege.SaveData();
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d. or 공성전 진행 중", a_pCmd, 0, MAX_USER );
		}
	}
	else if( !strcmp( szCmd, "/공성참가확인" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iRes = g_kSiege.SearchEntry( pMob[iArgument1].MOB.nGuildID );

			sprintf( szResult, "%s> clan:%d, guild:%d, successfully.", a_pCmd, iRes, pMob[iArgument1].MOB.nGuildID );

			//if( -1 == iRes ) SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsNotRegistered] );
			//else SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsRegistered] );
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );
		}		
	}
	else if( !strcmp( szCmd, "/공성신청마감" ) )
	{
		g_kSiege.set_ExpiryOftheTerm( iArgument1 ); // 1이면 기간만료(공성신청불가), 0이면 기간중(공성신청가능)
		sprintf( szResult, "%s> completed successfully. => 1이면 기간만료, 0이면 신청가능 기간중", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성전설정" ) )
	{
		g_kSiege.set_Started( iArgument1 ); // 1이면 공성전 설정, 0이면 공성전 설정 해제
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/클랜변경" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].m_byClan = iArgument2;

			MSG_CHANGE_TRIMURITI kChangeMsg;
			kChangeMsg.wType = MSG_CHANGE_TRIMURITI_ID;
			kChangeMsg.wPDULength = sizeof(MSG_CHANGE_TRIMURITI)-sizeof(HEADER);
			kChangeMsg.snKeyID = iArgument1;
			kChangeMsg.byTrimuriti = pMob[iArgument1].m_byClan;
			pUser[iArgument1].cSock.AddMessage( (char*)&kChangeMsg, sizeof(MSG_CHANGE_TRIMURITI) );	

			sprintf( szResult, "%s> Successfully", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );
		}	
	}
	else if( !strcmp( szCmd, "/공성상징물상태" ) )
	{
		g_kSiege.Print();
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성엔트리확인" ) )
	{// iClanSlot, page
		MSG_SIEGE_ENTRY kEntryMsg;
		memset( &kEntryMsg, 0 , sizeof(kEntryMsg) );
		kEntryMsg.wType = MSG_SIEGE_ENTRY_ID;
		kEntryMsg.wPDULength = sizeof(MSG_SIEGE_ENTRY)-sizeof(HEADER);
		kEntryMsg.byDate = 1;
		kEntryMsg.byClanSlot = iArgument1;
		kEntryMsg.byPage = iArgument2;
		const int iElementCount = 8;
		int iExpandSlot = iArgument2 * iElementCount;
		int iEnd = iExpandSlot + iElementCount;
		int iIndex = 0;
		for(; iExpandSlot < iEnd; ++iExpandSlot )
		{
			TNGUILD_INFO kGuild;
			g_kSiege.GetEntry( iArgument1, iExpandSlot, kGuild );
			kEntryMsg.irgGuildID[iIndex] = kGuild.iID;
			kEntryMsg.dwrgGuildMark[iIndex] = kGuild.dwMark;
			strncpy( kEntryMsg.szrgGuildName[iIndex], kGuild.szName, SZGUILD_LENGTH );
			++iIndex;
		}
	}
	else if( !strcmp( szCmd, "/이벤트" ) )
	{	
		Msg_NPCCommand sm; sm.wType = _Msg_NPCCommand;
		sm.dwClientTick = CurrentTime + pUser[a_iHandle].TickDiff;
		sm.byType = eInitSkill;		//	스킬초기화
		sm.byCommand = eRun;		//	실행
		sm.nNPCID = 1106;			//	라훌이벤트

		ProcessClientMessage(a_iHandle, (char*)&sm);
	}
	/*
	else if( !strcmp( szCmd, "/팻공격" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer];
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return;

		pMob[iMob].ClearCurrentTarget();
		pMob[iMob].ClearAttacker( 0 );
		pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );
	}
	else if( !strcmp( szCmd, "/팻멈춤" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer];
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return;

		pMob[iMob].ClearCurrentTarget();
		pMob[iMob].ClearAttacker( 0 );
		pMob[iMob].Mode = MOB_PEACE;
		pMob[iMob].OnFollow( a_iHandle );

		//pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );
	}
	else if( !strcmp( szCmd, "/스킬초기화" ) )
	{
		pMob[a_iHandle].ResetSkill();
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/LearnSkill" ) )
	{
		pMob[a_iHandle].LearnSkill( iArgument1, iArgument2 ); //( short a_sSkillID, int a_iLevel )
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/스탯변경" ) )
	{
		pMob[a_iHandle].MOB.sMind = iArgument4;
		pMob[a_iHandle].MOB.sHeart = iArgument3;
		pMob[a_iHandle].MOB.sMuscle = iArgument1;
		pMob[a_iHandle].MOB.sNerves = iArgument2;

		pMob[a_iHandle].UpdatePoints();
		pMob[a_iHandle].NotifyUpdateUIMsg();

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/CastSkill" ) )
	{
		S_CSP_CAST_AREA_SKILL kMsg;
		memset( &kMsg, 0, sizeof(S_CSP_CAST_AREA_SKILL) );
		kMsg.snSkillID = iArgument1;
		kMsg.bySkillLevel = iArgument2; // monster 스킬들은 모두 1 level이다.

		kMsg.snCasterKeyID = (short)a_iHandle;				
		kMsg.snMapX = (short)pMob[a_iHandle].TargetX;
		kMsg.snMapZ = (short)pMob[a_iHandle].TargetY;
		kMsg.snRes = 1;
		kMsg.krgTarget[0].snKeyID = iArgument3;
		int iTargetCount = 1;
		if( 0 < iArgument4 )
		{
			kMsg.krgTarget[1].snKeyID = iArgument4;
			iTargetCount = 2;
		}

		int iRes = pMob[a_iHandle].CastSkill( &kMsg, 1 );
		sprintf( szResult, "%s> Res:%d Successfully", a_pCmd, iRes );
	}
	else if( !strcmp( szCmd, "/TestEffect" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
				TNEFFECT kEffect;
				kEffect.iID = iArgument2;
				kEffect.kFunc.iData = iArgument3;
				kEffect.iDuration = 30000;
				kEffect.iParam1 = iArgument4;
				kEffect.iParam2 = iArgument5;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[iTarget].BroadcastUpdateStatusMsg();
				pUser[iTarget].cSock.SendMessage();

				sprintf( szResult, "%s> Buffer %d effect to %d", a_pCmd, iArgument2, iArgument1 );
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	*/


	strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));
}



void ControlSystem( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{	
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( 0 < a_iHandle && MAX_USER > a_iHandle )	if( a_bCheckGM && (eTNClan_GM != pMob[a_iHandle].m_byClan) ) return;
	#endif

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[256] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
	char szArgument6[256] = { 0,0,0, };
	char szArgument7[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0, iArgument6 = 0, iArgument7 = 0;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5, szArgument6, szArgument7  );
	iArgument1 = atoi( szArgument1 );
	iArgument2 = atoi( szArgument2 );
	iArgument3 = atoi( szArgument3 );
	iArgument4 = atoi( szArgument4 );
	iArgument5 = atoi( szArgument5 );   
	iArgument6 = atoi( szArgument6 );
	iArgument7 = atoi( szArgument7 );

    if( '/' != szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, ".", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)
	#ifdef __TN_TOP_LOG__
	if( 0 <= a_iHandle && MAX_USER > a_iHandle )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[%d월%d일 %d시%d분%d초] %s  %s \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd );
		WriteLog( chBuf, ".\\Event\\ControlSystem.txt" );
	}
	#endif    

  
    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );
    

	if( !strcmp( szCmd, "/loadfix" ) )
	{
		FILE* fp;
		fp = fopen( "loadfix.txt", "rt" );
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd );
		}
		else
		{
			char szLine[1024] = { 0,0,0, };
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp );
				if(ret == NULL) break;
				//HelpGameMaster( a_iHandle, szLine );
				ControlSystem( 0, szLine, false );
			}	
			sprintf( szResult, "%s> successful~", a_pCmd );
			fclose( fp );
		}
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( eRwd_Base, iArgument1, iArgument2, iArgument3 );
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f, Item:%f", a_pCmd, g_drgRwdCorrect[eRwd_Prana][eRwd_Total], g_drgRwdCorrect[eRwd_Gold][eRwd_Total], g_drgRwdCorrect[eRwd_Braman][eRwd_Total], g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
	}
	else if( !strcmp( szCmd, "/killmonster2" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				sprintf( szResult, "%s> can't kill the kala!!! use /killkala command.", a_pCmd );  
			}
			else
			{
				KillMonster( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
	}
	else if( !strcmp( szCmd, "/cc" ) )
	{
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 );
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] );
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/DropItem" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = eDur_Indestructible;
			kItem.byCount = 1;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeImmunity" ) )	 // mob handle, Immunity
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_iImmunity = iArgument2;
			sprintf( szResult, "%s> Immunity:%d", a_pCmd, pMob[iArgument1].m_iImmunity );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTrimuriti" ) )	// mob id, trimuriti
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 ) // mob all
		{
			pMob[iArgument1].MOB.byTrimuriti = (byte)iArgument2;
			pMob[iArgument1].m_byClan = (byte)iArgument2;
			pMob[iArgument1].NotifyUpdateUIMsg();
			sprintf( szResult, "%s> change the trimuriti of %d to %d", a_pCmd, iArgument1, iArgument2 );
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeLevel" ) )
	{
		if( (0 < iArgument1 && MAX_MOB > iArgument1) && ( 0 < iArgument2 && 100 >= iArgument2 ) )
		{
			pMob[iArgument1].MOB.byLevel = iArgument2;
			sprintf( szResult, "%s> level:%d", a_pCmd, pMob[iArgument1].MOB.byLevel );
			pMob[iArgument1].NotifyUpdateUIMsg();
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeClass" ) )		// mob handle, class1, class2
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].MOB.byClass1 = iArgument2;
			pMob[iArgument1].MOB.byClass2 = iArgument3;

			pMob[iArgument1].NotifyUpdateUIMsg();
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat();
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill();
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventSetting" ) )	// event index, count, cool-down time, sProceedType, duration
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].sCount = iArgument2;
			g_krgEventList[iArgument1].uiCoolDownTime = iArgument3;
			g_krgEventList[iArgument1].sProceedType = iArgument4;
			//g_krgEventList[iArgument1].iDuration = iArgument5;

			sprintf( szResult, "%s> event index:%d, count:%d, cool-down time:%d, enable:%d", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].sCount, g_krgEventList[iArgument1].uiCoolDownTime, g_krgEventList[iArgument1].sProceedType );
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask" ) )		// event index, task1, task2, task3, task4
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[0] = iArgument2;
			g_krgEventList[iArgument1].srgTask[1] = iArgument3;
			g_krgEventList[iArgument1].srgTask[2] = iArgument4;
			g_krgEventList[iArgument1].srgTask[3] = iArgument5;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask2" ) )	// event index, task5
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[4] = iArgument2;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting" ) )		// task index, action ID, param1, param2, param3
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{
			g_krgTaskList[iArgument1].iActionID = iArgument2;
			g_krgTaskList[iArgument1].irgParam[0] = iArgument3;
			g_krgTaskList[iArgument1].irgParam[1] = iArgument4;
			g_krgTaskList[iArgument1].irgParam[2] = iArgument5;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting2" ) )		// task index, param4, param5, 미정, 미정
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{			
			g_krgTaskList[iArgument1].irgParam[3] = iArgument2;
			g_krgTaskList[iArgument1].irgParam[4] = iArgument3;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEvent" ) )		// monster handle, event ID // 입력이 없으면, 현재 set된 event 번호를 출력해준다.
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( 0 < iArgument2 ) pMob[iArgument1].MOB.snBagIndex = iArgument2; //
			sprintf( szResult, "%s> the event of monster(%d): %d", a_pCmd, iArgument1, pMob[iArgument1].MOB.snBagIndex ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID(handle;%d~%d)", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/InitEvent" ) ) // event 설정을 초기화 한다.
	{
		int iEvent = iArgument1; // event index

		if( 0 >= iEvent || eEvent_MaxCount <= iEvent ) sprintf( szResult, "%s> invalid event ID(handle;%d~%d)", a_pCmd, 0, eEvent_MaxCount );
		else
		{
			g_krgEventList[iEvent].uiAvailableTime = 0;
			g_krgEventList[iEvent].sClan = eEvntClan_All;
			g_krgEventList[iEvent].iDuration = eEvntSwitch_On;

			sprintf( szResult, "%s> the event(%d) is initialized.", a_pCmd, iEvent ); 
		}
	}
	else if( !strcmp( szCmd, "/AddEventToScheduler" ) ) // event를 time scheduler에 등록한다.	// time slot, event
	{
		int iFlag = 1;
		if( 0 <= iArgument1 && eTS_MaxSlot > iArgument1 )
		{
			if( 0 <= iArgument2 && eEvent_MaxCount > iArgument2 ) // 0 일때는 remove
			{
				g_srgTimeSchedule[iArgument1] = iArgument2;
				sprintf( szResult, "%s> the event(%d) is registered at slot(%d).", a_pCmd, iArgument2, iArgument1 ); 
				iFlag = 0;
			}
		}

		if( iFlag ) sprintf( szResult, "%s> failed", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/RemoveEventAtScheduler" ) )
	{
		for( int i = 0; i < eTS_MaxSlot; ++i )
		{
			if( iArgument1 == g_srgTimeSchedule[i] ) g_srgTimeSchedule[i] = 0;
		}

		sprintf( szResult, "%s> the event(%d) is removed all.", a_pCmd, iArgument1 ); 
	}	
	else if( !strcmp( szCmd, "/ChangeMonsterHP" ) ) // raw data 수정		// monster ID, Max HP, HP recovery
	{// Monster ID, HP, HPRecovery
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].nHP = iArgument2;
			pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) Max HP:%d(recv:%d)", a_pCmd, iIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterImmunity" ) ) // raw data 수정			// monster ID, Immunity
	{// Monster ID, Immunity
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].nGuildID = iArgument2;

			sprintf( szResult, "%s> Monster(idx:%d) Immu:%d", a_pCmd, iIndex, pMonsterData[iIndex].nGuildID ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterARDG" ) )		// monster id, Attack rate, Dodge rate
	{// Monster ID, Attack Rate, Dodge Rate
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].sMuscle = iArgument2;
			pMonsterData[iIndex].sNerves = iArgument3;
			sprintf( szResult, "%s> Monster(idx:%d) AR:%d, DG:%d", a_pCmd, iIndex, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterAC" ) )		// monster ID, AC
	{// Monster ID, AC
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].sHeart = iArgument2;
			sprintf( szResult, "%s> Monster(idx:%d) AC:%d", a_pCmd, iIndex, pMonsterData[iIndex].sHeart ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterMR" ) )		// monster ID, fire, cold, lightning, poison
	{// Monster ID, Fire R, Cold R, Lightning R, Poison R
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = iArgument2;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = iArgument3;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = iArgument4;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = iArgument5;

			sprintf( szResult, "%s> Monster(idx:%d) FR:%d, CR:%d, LR:%d, PR:%d ", a_pCmd, iIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillEffect" ) ) 
	{// skill ID, Index of the effect,  Effect ID, function, duration, parameter1, parameter2
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 && 0 <= iArgument2 && 5 > iArgument2 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].krgEffect[iArgument2].iID = iArgument3;
			pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData = iArgument4;
			pSkillData[iIndex].krgEffect[iArgument2].iDuration = iArgument5;
			pSkillData[iIndex].krgEffect[iArgument2].iParam1 = iArgument6;
			pSkillData[iIndex].krgEffect[iArgument2].iParam2 = iArgument7;

			memset( &(pSkillData[iIndex].kDamage), 0, sizeof(pSkillData[iIndex].kDamage) );
			for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
			{
				if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue;

				if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
				else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
					|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash;

				if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue;

				switch( pSkillData[iIndex].krgEffect[i].iID )
				{
				case eTNAfn_Damage :
				case eTNAfn_DamageSplash :
					pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_PierceDamage :
					pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					break;
				case eTNAfn_Fire :
				case eTNAfn_FireSplash :
					pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Cold :
				case eTNAfn_ColdSplash :
					pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Lightning :
				case eTNAfn_LightningSplash :
					pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Poison :
				case eTNAfn_PoisonSplash :
					pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				} // end of switch
			}

			sprintf( szResult, "%s> Monster Skill(idx:%d) Effect: ID:%d, Func:%d, Dur:%d, Param1:%d, Param2:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].krgEffect[iArgument2].iID, pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData, pSkillData[iIndex].krgEffect[iArgument2].iDuration
				, pSkillData[iIndex].krgEffect[iArgument2].iParam1, pSkillData[iIndex].krgEffect[iArgument2].iParam2				
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d or Invalid index of the effect.", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkill" ) )
	{// Skill ID, Attack Speed, Cooldown time, Range, AOE, Allowed Target
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].iAttackSpeed = iArgument2;
			pSkillData[iIndex].iActivateTime = iArgument3;
			pSkillData[iIndex].iRange = iArgument4 + 2;
			pSkillData[iIndex].iAOE = iArgument5 + 2;
			pSkillData[iIndex].iAllowedTargets = iArgument6;

			sprintf( szResult, "%s> Monster Skill(idx:%d) AttackSpeed:%d, Cooldown:%d, Range:%d, AOE:%d, AllowedTarget:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].iAttackSpeed, pSkillData[iIndex].iActivateTime, pSkillData[iIndex].iRange, pSkillData[iIndex].iAOE, pSkillData[iIndex].iAllowedTargets
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSight" ) )		// id, normal, combat
	{// Monster ID, Normal Sight, Combat Sight
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].byQuest[eMonPrty_NormalSight] = iArgument2;
			pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) Sight(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterPopDelay" ) )	// id, minium pop delay, maxium pop delay
	{// Monster ID, Min delay, Max delay
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex = iArgument2;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) PopDelay(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemCP" ) ) // item combat phase
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			pItemData[iIndex].sCombatPhase = iArgument2;
			sprintf( szResult, "%s> Item(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pItemData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemEffect" ) ) // item combat phase		// item id, effect index, effect id, effect dur
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			if( 0 > iArgument2 || 4 < iArgument2 ) return;
			pItemData[iIndex].krgEffect[iArgument2].iID = iArgument3;
			pItemData[iIndex].krgEffect[iArgument2].iDuration = iArgument4;
			sprintf( szResult, "%s> Item(idx:%d) effectIdx:%d, effectID:%d, effectDur:%d", a_pCmd, iIndex, iArgument2, pItemData[iIndex].krgEffect[iArgument2].iID, pItemData[iIndex].krgEffect[iArgument2].iDuration ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeSkillCP" ) ) // PC skill combat phase
	{		
		if( HT_PARAMTYPE_PCSKILL_START <= iArgument1 && HT_PARAMTYPE_PCSKILL_END >= iArgument1 )
		{
			int iIndex = 0;
			for( int iLevel = 1; iLevel < 11; ++iLevel )
			{
				iIndex = (iArgument1 - HT_PARAMTYPE_PCSKILL_START )*10 + iLevel;
				pSkillData[iIndex].sCombatPhase = iArgument2;
			}
			sprintf( szResult, "%s> PC Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_PCSKILL_START, HT_PARAMTYPE_PCSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillCP" ) ) // Monster skill combat phase		// monster skill ID, combat phase
	{		
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].sCombatPhase = iArgument2;

			sprintf( szResult, "%s> Monster Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/offcsh" ) ) // speed hack 관련
	{
		if( 0 == iArgument1 ) g_irgSpeedConsider[5] = 0;
		else g_irgSpeedConsider[5] = 1;

		sprintf( szResult, "%s> switch on/off :%d(0:on, 1:off)", g_irgSpeedConsider[5] );
	}
	else if( !strcmp( szCmd, "/ChangeSpeedFactor" ) ) // speed hack 관련		// time slice, over time, correct, crack point, log level
	{
		if( 0 < iArgument1 )
		{
			g_irgSpeedConsider[0] = iArgument1;
			g_irgSpeedConsider[1] = iArgument2;
			g_irgSpeedConsider[2] = iArgument3;
			g_irgSpeedConsider[3] = iArgument4;
			g_irgSpeedConsider[4] = iArgument5;
			g_irgSpeedConsider[5] = 0;
		}
        
		sprintf( szResult, "%s> time slice:%d, over time:%d, correct:%d, crack point:%d, log level:%d", a_pCmd, g_irgSpeedConsider[0], g_irgSpeedConsider[1], g_irgSpeedConsider[2], g_irgSpeedConsider[3], g_irgSpeedConsider[4] ); 
	}
	else if( !strcmp( szCmd, "/LoadSettingAll" ) )
	{
		LoadZoneSettings();
		LoadWorldSettings();
		LoadSettingTxl();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadSettingTxl" ) )
	{
		LoadSettingTxl();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadZoneSetting" ) )
	{
		LoadZoneSettings();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadWorldSetting" ) )
	{
		LoadWorldSettings();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/ChangeWorldSetting" ) )		// index, data
	{
		if( 0 <= iArgument1 && 100 > iArgument1 )
		{
			g_irgSetting[iArgument1] = iArgument2;

			sprintf( szResult, "%s> g_irgSetting[%d] : %d", a_pCmd, iArgument1, g_irgSetting[iArgument1] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~99)", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/printpos" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			sprintf( szResult, "%s> Now(%d,%d), 0:(%d,%d), 1:(%d,%d), 2(%d,%d), 3(%d,%d), 4(%d,%d)"
				, a_pCmd, pMob[iArgument1].SegmentX, pMob[iArgument1].SegmentY
				, pMob[iArgument1].SegmentListX[0], pMob[iArgument1].SegmentListY[0]
				, pMob[iArgument1].SegmentListX[1], pMob[iArgument1].SegmentListY[1]
				, pMob[iArgument1].SegmentListX[2], pMob[iArgument1].SegmentListY[2]
				, pMob[iArgument1].SegmentListX[3], pMob[iArgument1].SegmentListY[3]
				, pMob[iArgument1].SegmentListX[4], pMob[iArgument1].SegmentListY[4]
				);
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ); 		    
		}
	}
	else if( !strcmp( szCmd, "/changepos" ) )		// monster id, segment x, segment y
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].SegmentX = iArgument2;
			pMob[iArgument1].SegmentY = iArgument3;
			pMob[iArgument1].SegmentListX[0] = pMob[iArgument1].SegmentListX[1] = pMob[iArgument1].SegmentListX[2] = pMob[iArgument1].SegmentListX[3] = pMob[iArgument1].SegmentListX[4] = iArgument2;
			pMob[iArgument1].SegmentListY[0] = pMob[iArgument1].SegmentListY[1] = pMob[iArgument1].SegmentListY[2] = pMob[iArgument1].SegmentListY[3] = pMob[iArgument1].SegmentListY[4] = iArgument3;

			sprintf( szResult, "%s> Now(%d,%d), 0:(%d,%d), 1:(%d,%d), 2(%d,%d), 3(%d,%d), 4(%d,%d)"
				, a_pCmd, pMob[iArgument1].SegmentX, pMob[iArgument1].SegmentY
				, pMob[iArgument1].SegmentListX[0], pMob[iArgument1].SegmentListY[0]
				, pMob[iArgument1].SegmentListX[1], pMob[iArgument1].SegmentListY[1]
				, pMob[iArgument1].SegmentListX[2], pMob[iArgument1].SegmentListY[2]
				, pMob[iArgument1].SegmentListX[3], pMob[iArgument1].SegmentListY[3]
				, pMob[iArgument1].SegmentListX[4], pMob[iArgument1].SegmentListY[4]
				);
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ); 		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeHalfGrid" ) ) // ok
	{
		if( 31 < iArgument1 )
		{
			g_iHalfGridX = g_iHalfGridY = iArgument1;
			g_iViewGridX = g_iViewGridY = g_iHalfGridX + g_iHalfGridY + 1;	
		}

		sprintf( szResult, "%s> ViewGrid:%d, HalfGrid:%d", a_pCmd, g_iViewGridX, g_iHalfGridX );
	}
	else if( !strcmp( szCmd, "/ChangePopArea" ) ) // index, start x, end x, start z, end z
	{
		if( 0 > iArgument1 || 4 <= iArgument1 ) return;
		TrimurityArea.pArea[iArgument1][0].snStartX = iArgument2;
		TrimurityArea.pArea[iArgument1][0].snEndX = iArgument3;
		TrimurityArea.pArea[iArgument1][0].snStartZ = iArgument4;			
		TrimurityArea.pArea[iArgument1][0].snEndZ = iArgument5;
	}


	if( 0 < a_iHandle && MAX_USER > a_iHandle )
	{
		strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
		pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
	}
}



void AssistPlayMovie( int a_iHandle, char* a_pCmd ) // play a movie를 위한 
{
	#ifdef __TN_PLAYMOVIE__
	if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return;    
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[128] = { 0,0,0, };
	char szArguments[512] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0;
    
	sscanf( a_pCmd, "%s %s", szCmd, szArguments );    
    if( '/' != szCmd[0] ) return;
    if( 0 == szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)

  
    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );  

	if( !strcmp( szCmd, "/nokillall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		int iFlag = 0;
		if( !strcmp( szArgument1, "on" ) ) iFlag = 1;
		else iFlag = 0;

		for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_irgFlag[0] = iFlag;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/nokill" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 );
		iArgument1 = atoi( szArgument1 ); // mob ID
		// argument2 : on/off

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1;
			else iFlag = 0;

			pMob[iArgument1].m_irgFlag[0] = iFlag;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] );
		}
	}
	else if( !strcmp( szCmd, "/nokill2" ) )
	{
		sscanf( a_pCmd, "%s %s %s", szCmd, szArgument1, szArgument2 );
		// szArgument1 : 캐릭터명
		// szArgument2 : on/off
		int iArgument1 = GetMOBID( szArgument1 );
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1;
			else iFlag = 0;

			pMob[iArgument1].m_irgFlag[0] = iFlag;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] );
		}
	}
	else if( !strcmp( szCmd, "/nostun" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = pMob[i].m_iImmunity | eTNImm_Stun;
		else 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = 0;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/holdall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
		{
			for( int i = 1; i < MAX_USER; ++i )
			{			
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Hold;
				kEffect.iDuration = 600000;
				kEffect.iParam1 = 100;
				kEffect.iParam2 = 0;
				pMob[i].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[i].BroadcastUpdateStatusMsg();
				pUser[i].cSock.SendMessage();
			}
		}
		else 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = 0;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/mvspd" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		iArgument1 = atoi( szArgument1 ); // move speed

		g_irgFlag[1] = iArgument1; // 0 이하 값을 입력하면 원래의 상태로 돌아간다.
		for( int i = 1; i < MAX_USER; ++i )
		{ 
			pMob[i].UpdateSpeed();
			//pMob[i].NotifyUpdateStatusMsg();
			pMob[i].NotifyUpdateUIMsg();
			pUser[i].cSock.SendMessage();
		}
		sprintf( szResult, "%s> successful~, g_irgFlag[1]:%d", a_pCmd, g_irgFlag[1] );
	}
	else if( !strcmp( szCmd, "/killpc" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : 캐릭터명
		int iMobID = GetMOBID( szArgument1 );
		if( 0 < iMobID && MAX_USER > iMobID )	//	동일지역내 상대방 존재
		{	
			pMob[iMobID].MOB.nHP = 0;
			pMob[iMobID].CurrentTarget = 0;
			pMob[iMobID].m_eFSM = eTNFsm_Dead;
			pMob[iMobID].NotifyUpdateStatusMsg();
			pMob[iMobID].OnKilled( a_iHandle, 10 );
			sprintf( szResult, "%s> successful~", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd );
		}	
	}
	else if( !strcmp( szCmd, "/killmonsterall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : 캐릭터명
		for( int i = MAX_USER; i < MAX_MOB; ++i )
		{
			KillMonster( i );
			/*
			pMob[i].MOB.nHP = 0;
			pMob[i].CurrentTarget = 0;
			pMob[i].m_eFSM = eTNFsm_Dead;
			*/
		}

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/hpup" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 );
		iArgument1 = atoi( szArgument1 ); // mob ID
		iArgument2 = atoi( szArgument2 ); // plus heart points

		if( (0 < iArgument1) && (MAX_USER > iArgument1) && ( 0 < iArgument2 ) )
		{
			pMob[iArgument1].MOB.sHeart += iArgument2;
			pMob[iArgument1].UpdatePoints();
			pMob[iArgument1].NotifyUpdateUIMsg();
			pUser[iArgument1].cSock.SendMessage();

			sprintf( szResult, "%s> successful~, pMob[iArgument1].MOB.sHeart:%d", a_pCmd, iArgument1, pMob[iArgument1].MOB.sHeart );
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/loadscene" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : filename

		FILE* fp;
		fp = fopen( szArgument1, "rt" );
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd );
		}
		else
		{
			char szLine[1024] = { 0,0,0, };
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp );
				if(ret == NULL) break;
				HelpGameMaster( a_iHandle, szLine );
				AssistPlayMovie( a_iHandle, szLine );
				ControlSystem( a_iHandle, szLine, false );
			}	

			sprintf( szResult, "%s> successful~", a_pCmd );
			fclose( fp );
		}
	}

    strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       

	#endif
}


// altar에 위치한 kala 개수를 세고. 각 주신별로 몇개씩 소유하고 있는지 counting한다.
// 5개 이상 소유를 한 주신은 버프사 NPC를 이용할 수 있다.
void MoveKalaRewarder()
{
	//int irgRealm[eRealm_MaxCount] = { 0,0,0, };

	for( int i = 0; i < eRealm_MaxCount; ++i ) g_irgRealm[i] = 0;

	for( int i = 0; i < eKalaAltar_MaxCount; ++i )
	{
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i );
		if( MAX_USER <= iKalaMonster && MAX_MOB > iKalaMonster )
		{
			if( 0 >= pMob[iKalaMonster].MOB.nHP )
			{
				//g_irgKalaAltar[i] = 0;
				
			}
			else ++g_irgRealm[g_krgKalaAltar[i].sTrimuriti]; // 주신은 1,2,4만이 들어간다.
		}
	}

	for( int i = 0; i < eRealm_MaxCount; ++i )
	{
		if( 4 < g_irgRealm[i] ) // 특정 주신이 5개 이상을 소유한다면, 버프사가 그쪽 편으로 바뀐다.
		{
			if( eTNClan_Siva == i )
			{// 275, 159
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Siva );
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Siva );
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Siva );
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Siva].x, g_krgKalaRewarderPosition[0][eTNClan_Siva].y ); // 자기 자신을 teleport 시킨다.
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Siva].x, g_krgKalaRewarderPosition[1][eTNClan_Siva].y );
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Siva].x, g_krgKalaRewarderPosition[2][eTNClan_Siva].y ); // open a 차투랑가 gate
			}
			else if( eTNClan_Vishnu == i )
			{// 343, 852
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Vishnu );
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Vishnu );
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Vishnu );
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[0][eTNClan_Vishnu].y );
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[1][eTNClan_Vishnu].y );
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[2][eTNClan_Vishnu].y ); // open a 차투랑가 gate
			}
			else if( eTNClan_Brahma == i )
			{// 871,471
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Brahma );
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Brahma );
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Brahma );
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Brahma].x, g_krgKalaRewarderPosition[0][eTNClan_Brahma].y );
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Brahma].x, g_krgKalaRewarderPosition[1][eTNClan_Brahma].y );
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Brahma].x, g_krgKalaRewarderPosition[2][eTNClan_Brahma].y ); // open a 차투랑가 gate
			}

			NotifyRvRStatus();
			RecordRvRStatus();
			return;
		}
	} // end of for

	// 주신지역 중앙에 위치를 시킨다.
	pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_GM );
	pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_GM );
	pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_GM );
	Teleport( g_irgKalaAltarRewarder[0], 1, 1 );
	Teleport( g_irgKalaAltarRewarder[1], 1, 2 );
	Teleport( g_irgKalaAltarRewarder[2], 1, 3 );

	NotifyRvRStatus();
	RecordRvRStatus();
}



// 주신전의 kala 현황에 대해, 주신전(크루마) 내에 있는 모든 user에게 알려준다.
void NotifyRvRStatus()
{
	char szMsg[1024] = { 0,0,0, };
	sprintf( szMsg, g_pMessageStringTable[_Post_Kala_Status], g_irgRealm[eTNClan_Brahma], g_irgRealm[eTNClan_Vishnu], g_irgRealm[eTNClan_Siva] );
	if( 5 == g_irgRealm[eTNClan_Brahma] ) strcat( szMsg, g_pMessageStringTable[_Brahma_Collect_Five_Kala]);
	else if( 5 == g_irgRealm[eTNClan_Vishnu] ) strcat( szMsg, g_pMessageStringTable[_Vishnu_Collect_Five_Kala]);
	else if( 5 == g_irgRealm[eTNClan_Siva] ) strcat( szMsg, g_pMessageStringTable[_Siva_Collect_Five_Kala]);

	if( 4 == g_irgRealm[eTNClan_Brahma] ) strcat( szMsg, g_pMessageStringTable[_Brahma_Collect_Four_Kala]);
	if( 4 == g_irgRealm[eTNClan_Vishnu] ) strcat( szMsg, g_pMessageStringTable[_Vishnu_Collect_Four_Kala]);
	if( 4 == g_irgRealm[eTNClan_Siva] ) strcat( szMsg, g_pMessageStringTable[_Siva_Collect_Four_Kala]);
	PostMessageToZone( szMsg );
}



void RecordRvRStatus()
{
	RVR_RECORD kRecord;
	for( int i = 0; i < eKala_MaxCount; ++i ) kRecord.krgKala[i].iLocation = -1; 

	int iIndex = 0;
	for( int i = 0; i < eKalaAltar_MaxCount; ++ i )
	{
		if( eKala_MaxCount <= iIndex ) break; 
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i );
		if( 0 < iKalaMonster )
		{
			kRecord.krgKala[iIndex].iLocation = i;
			kRecord.krgKala[iIndex].iClan = g_krgKalaAltar[i].sTrimuriti;
			kRecord.krgKala[iIndex].iID = pMob[iKalaMonster].MOB.snTribe;
			//if( eTNClan_Brahma == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Brahma;
			//else if( eTNClan_Vishnu == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Vishnu;
			//else if( eTNClan_Siva == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Siva;
			++iIndex;
		}
	}
	
	kRecord.krgRewarder[0].iClan = kRecord.krgRewarder[1].iClan = kRecord.krgRewarder[2].iClan = pMob[g_irgKalaAltarRewarder[0]].m_byClan;
	kRecord.krgRewarder[0].x = pMob[g_irgKalaAltarRewarder[0]].TargetX;
	kRecord.krgRewarder[0].y = pMob[g_irgKalaAltarRewarder[0]].TargetY;
	kRecord.krgRewarder[1].x = pMob[g_irgKalaAltarRewarder[1]].TargetX;
	kRecord.krgRewarder[1].y = pMob[g_irgKalaAltarRewarder[1]].TargetY;
	kRecord.krgRewarder[2].x = pMob[g_irgKalaAltarRewarder[2]].TargetX;
	kRecord.krgRewarder[2].y = pMob[g_irgKalaAltarRewarder[2]].TargetY;

	FILE* fpInfo = fopen( ".\\Data\\RvRRecord.dat", "wb" );
	if( fpInfo )
	{
		fwrite( &kRecord, sizeof(RVR_RECORD), 1, fpInfo );
		fclose( fpInfo ); 
	}
}


void PopMonstersForEvent()
{
	int iZoneID = ServerIndex + 1;
	if( eZone_Mandra == iZoneID ) // 만다라 마을
	{
		g_irgGateOfDungeon[0] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 19 );  // 
		g_irgGod[eTNClan_Brahma] = pMob[1000].Summon( 2932, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Brahma, 0, 4, 3, 0, false, 0, 0, 491 );  // 

		if( eCountryKorea == g_eCountryID )
		{
			if( 0 == g_iWorldID ) // 테섭
			{
				pMob[1000].Summon( 2945, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 455, 270, 0, false, 0, 0, 20 );  // 
				pMob[1000].Summon( 2944, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 522, 272, 0, false, 0, 0, 21 );  // 
			}

			// 결투장 운영 NPC		
			pMob[1000].Summon( 2939, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 897, 259, 0, false, 0, 0, 22 );  // 
			pMob[1000].Summon( 2940, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 903, 259, 0, false, 0, 0, 23 );  // 
		}


		for( int y = 228; y < 261; ++y )
		{
			for( int x = 880; x < 912; ++x )
			{
				g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone;
			}
		}
	}
	else if( eZone_Katacomb == iZoneID ) // 북두성군 zone
	{
		// 4개의 문
		TriggerEvent( 0, 149, 0, 0, 0, 93 );
		//pMob[1000].Summon( 2252, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2/*방향*/, 456, 185, 0, false, 0, 0, 24 );  // 
		//pMob[1000].Summon( 2254, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2, 166,  85, 0, false, 0, 0, 25 );  // 
		//pMob[1000].Summon( 2253, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 17, 567, 185, 0, false, 0, 0, 26 );  // 
		//pMob[1000].Summon( 2255, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2, 856,  85, 0, false, 0, 0, 27 );  // 

		// trap 몬스터
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 459,  129, 0, false, 0, 0, 28 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 444,   77, 0, false, 0, 0, 29 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 432,  101, 0, false, 0, 0, 30 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 432,  154, 0, false, 0, 0, 31 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 444,  165, 0, false, 0, 0, 32 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 388,  132, 0, false, 0, 0, 33 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 568,  129, 0, false, 0, 0, 34 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 580,   77, 0, false, 0, 0, 35 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 592,  101, 0, false, 0, 0, 36 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 592,  154, 0, false, 0, 0, 37 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 580,  165, 0, false, 0, 0, 38 );  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 636,  132, 0, false, 0, 0, 39 );  // 
	}
	else if( eZone_Stronghold == iZoneID ) // 요새전
	{
		TriggerEvent( 0, 22, 0, 0, 0, 90 ); //
	}
	else if( eZone_Castle == iZoneID ) // 카타나3, 비류성
	{
		TriggerEvent( 0, 99, 0, 0, 0, 92 );
		TriggerEvent( 0, 81, 0, 0, 0, 91 ); //

		g_iSymbolAtByruCastle = pMob[1000].Summon( 2379, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 1, 1, 0, false, 0, 0, 400 );  // 

		g_iGambleHorse = pMob[1000].Summon( 2359, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 6, 5, 0, false, 0, 0, 40 );  // 
		g_iGambleYut[0] = pMob[1000].Summon( 2362, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 4, 0, false, 0, 0, 41 );  // 
		g_iGambleYut[1] = pMob[1000].Summon( 2363, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 42 );  // 
		g_iGambleYut[2] = pMob[1000].Summon( 2364, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 6, 0, false, 0, 0, 43 );  // 
		g_iGambleYut[3] = pMob[1000].Summon( 2365, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 3, 5, 0, false, 0, 0, 44 );  // 
		g_iGambleYut[4] = pMob[1000].Summon( 2366, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 4, 5, 0, false, 0, 0, 45 );  // 
		//g_iGambleHorse = pMob[1000].Summon( 2359, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 40 );  // 
		//g_iGambleYut[0] = pMob[1000].Summon( 2362, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 41 );  // 
		//g_iGambleYut[1] = pMob[1000].Summon( 2363, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 42 );  // 
		//g_iGambleYut[2] = pMob[1000].Summon( 2364, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 43 );  // 
		//g_iGambleYut[3] = pMob[1000].Summon( 2365, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 44 );  // 
		//g_iGambleYut[4] = pMob[1000].Summon( 2366, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false, 0, 0, 45 );  // 

		//TriggerEvent( 0, 104, 0, 0, 0, 449 );
	}
	else if( eZone_Cruma == iZoneID ) // 크루마존이라면, kala system을 setting해줘야 한다.
	{
		//----------------------------------------------------
		// The gate of dungeon(주신 던젼)
		//----------------------------------------------------
		g_irgGateOfDungeon[0] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Brahma, 0, 5, 5, 0, false, 0, 0, 46 );  // 
		g_irgGateOfDungeon[1] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Vishnu, 0, 6, 5, 0, false, 0, 0, 47 );  // 
		g_irgGateOfDungeon[2] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Siva, 0, 7, 5, 0, false, 0, 0, 48 );  // 

		//----------------------------------------------------
		// Gods
		//----------------------------------------------------
		g_irgGod[eTNClan_Brahma] = pMob[1000].Summon( 2932, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Brahma, 0, MAX_GRIDX-1, MAX_GRIDY-1, 0, false, 0, 0, 49 );  // 
		g_irgGod[eTNClan_Vishnu] = pMob[1000].Summon( 2933, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Vishnu, 0, MAX_GRIDX-2, MAX_GRIDY-1, 0, false, 0, 0, 50 );  // 
		g_irgGod[eTNClan_Siva]   = pMob[1000].Summon( 2938, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Siva,   0, MAX_GRIDX-3, MAX_GRIDY-1, 0, false, 0, 0, 51 );  // 

		// bless of god에 대한 초기 설정
		g_krgBlessOfGod[0][eTNClan_Brahma].Init();
		g_krgBlessOfGod[0][eTNClan_Brahma].AddCard( 25, 50 );
		g_krgBlessOfGod[0][eTNClan_Brahma].Shuffle();
		g_krgBlessOfGod[0][eTNClan_Vishnu].Init();
		g_krgBlessOfGod[0][eTNClan_Vishnu].AddCard( 25, 35 );
		g_krgBlessOfGod[0][eTNClan_Vishnu].Shuffle();
		g_krgBlessOfGod[0][eTNClan_Siva].Init();
		g_krgBlessOfGod[0][eTNClan_Siva].AddCard( 25, 30 );
		g_krgBlessOfGod[0][eTNClan_Siva].Shuffle();

				
		bool bLoadKalaRecord = false;
		if( 0 == g_iWorldID )  // 테섭이면 기존의 kala 최종 결과를 load하여 유지하도록 한다.
		{// kala system에 대한 기록을 읽어, zone에 setting
			FILE* fpInfo = fopen( ".\\Data\\RvRRecord.dat", "rb" ); // 테섭이라면 기록되어 있는 data를 load한다.

			if( fpInfo )
			{
				RVR_RECORD kRecord;
				memset( &kRecord, 0, sizeof(kRecord) );

				fread( &kRecord, sizeof(RVR_RECORD), 1, fpInfo );
				fclose( fpInfo ); 

				bLoadKalaRecord = true;

				for( int i = 0; i < 5; ++i )
					if( 0 < kRecord.irgEntryCount[i] ) g_irgEntryCount[i] = kRecord.irgEntryCount[i];

				int irgKalaCount[4] = { 0,0,0, };
				for( int i = 0; i < eKala_MaxCount; ++ i )
				{
					int iLocation = kRecord.krgKala[i].iLocation;
					if( 0 > iLocation || eKalaAltar_MaxCount <= iLocation ) continue;
					int iCountIndex = 1;
					if( eKala_Brahma == kRecord.krgKala[i].iID ) iCountIndex = 1; //++irgKalaCount[1];
					else if( eKala_Vishnu == kRecord.krgKala[i].iID ) iCountIndex = 2; //++irgKalaCount[2];
					else if( eKala_Siva == kRecord.krgKala[i].iID ) iCountIndex = 3; //++irgKalaCount[3];
					++irgKalaCount[iCountIndex];
					if( 3 < irgKalaCount[iCountIndex] ) continue;

					g_kKalaSystem.InstallKala( kRecord.krgKala[i].iID, kRecord.krgKala[i].iClan, iLocation );

				}

				// 모자르는 kala 수를 찾아서.. 채워줘야 한다.
				// 1. 자신의 주신 제단에 자동으로 setting 된다.
				// 2. 주신전 정 가운데의 위치의 땅 바닥에 떨어뜨린다.
				if( 3 > irgKalaCount[1] ) // 브라흐마
				{
					for( int i = 0; i < eKalaAltar_MaxCount; ++ i )
					{
						if( 3 <= irgKalaCount[1] ) break;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Brahma == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, i );
							++irgKalaCount[1];
						}
					}
				}
				if( 3 > irgKalaCount[2] ) // 비슈누
				{
					for( int i = 0; i < eKalaAltar_MaxCount; ++ i )
					{
						if( 3 <= irgKalaCount[2] ) break;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Vishnu == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, i );

							++irgKalaCount[2];
						}
					}
				}
				if( 3 > irgKalaCount[3] ) // 시바
				{
					for( int i = 0; i < eKalaAltar_MaxCount; ++ i )
					{
						if( 3 <= irgKalaCount[3] ) break;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Siva == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, i );
	
							++irgKalaCount[3];
						}
					}
				}

				// convert
				if( 0 >= kRecord.iWinnerClan || 4 < kRecord.iWinnerClan) // 맨 처음에는 kRecord.iWinnerClan값이 0이다.
				{
					kRecord.iWinnerClan = kRecord.krgRewarder[0].iClan; // 아무 winner도 없다면, GM 주신(10)을 가지고 있을 것이다.
					if( 0 >= kRecord.iWinnerClan || 4 < kRecord.iWinnerClan) kRecord.iWinnerClan = 0;
				}

				g_irgKalaAltarRewarder[0] = pMob[1000].Summon( 2901, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[0][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[0][kRecord.iWinnerClan].y, 0, false, 0, 0, 52 );
				g_irgKalaAltarRewarder[1] = pMob[1000].Summon( 2902, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[1][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[1][kRecord.iWinnerClan].y, 0, false, 0, 0, 53 );
				g_irgKalaAltarRewarder[2] = pMob[2000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[2][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[2][kRecord.iWinnerClan].y, 0, false, 0, 0, 54 );
				//g_irgKalaAltarRewarder[2] = pMob[2000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, kRecord.iWinnerClan, 0, 1,3, false );

				RecordRvRStatus();
			}
		}

		if( false == bLoadKalaRecord )
		{
			// kala를 5개이상 모았을 때 보상을 줄 NPC pop
			g_irgKalaAltarRewarder[0] = pMob[1000].Summon( 2901, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 1, 0, false, 0, 0, 55 );  // 
			g_irgKalaAltarRewarder[1] = pMob[1000].Summon( 2902, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 2, 0, false, 0, 0, 56 );  // 
			g_irgKalaAltarRewarder[2] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 3, 0, false, 0, 0, 57 );  // 

			// kala 몬스터 setting, 각 주신별로 3개씩
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 0 );
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 1 );
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 3 );
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 5 );
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 6 );
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 8 );
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 10 );
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 11 );
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 13 );
		}
	}
}


void RegisterTimeEvent( TNEVENT& a_kEvent, int a_iTriggerTime )
{

}


//----------------------------------------------------------------------
//@Param
//	- a_iUser : event를 trigger 하는 사람
//	- a_iEventID : trigger되는 event
//	- a_iX, a_iY : event가 발생된 cell 위치
//	- a_iNPC : event에 의한 task를 수행하는 NPC
//----------------------------------------------------------------------
int TriggerEvent( int a_iUser, int a_iEventID, int a_iX, int a_iY, int a_iNPC, int a_iCaller )
{
	if( 0 >= a_iEventID || eEvent_MaxCount <= a_iEventID ) return eTNRes_EvntInvalidEventNo;
	if( CurrentTime < g_krgEventList[a_iEventID].uiAvailableTime ) return eTNRes_EvntNotCoolYet; // 아직 cool-down이 완료되지 않았다.
	if( eEvntSwitch_Off == g_krgEventList[a_iEventID].iDuration ) return eTNRes_EvntSwitchOff; // 이용불가이면 쓸 수 없다.
	if( eEvntSwitch_On < g_krgEventList[a_iEventID].iDuration && CurrentTime > g_krgEventList[a_iEventID].uiDurationTime )
	{
		g_krgEventList[a_iEventID].iDuration = eEvntSwitch_Off; // 이용불가로 변경한다.
		g_krgEventList[a_iEventID].uiDurationTime = 0;
		return eTNRes_EvntUseTimeOver;
	}
	if( 0 <= g_krgEventList[a_iEventID].sClan )
	{
		if( 0 < a_iUser && MAX_USER > a_iUser )
			if( g_krgEventList[a_iEventID].sClan != pMob[a_iUser].m_byClan ) return eTNRes_EvntDiffClan; // 특정 clan 전용으로 설정되어 있는 경우
	}

	int iStartIndex = 0, iEndIndex = eTask_Sort;
	if( eEvntPrcdType_Random == g_krgEventList[a_iEventID].sProceedType )
	{
		iStartIndex = rand() % eTask_Sort; // 모든 task 목록에 값이 채워져있어야 한다.
		iEndIndex = iStartIndex + 1;
	}

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	if( eTNSwitch_EventLog & g_iSwitch )
	{
		char chBuf[2048] = { 0,0,0, };
		sprintf(chBuf, "[TriggerEvent] %dmm월%ddd %dhh%dms%dss, Event:%d, Caller:%d, User:%d, NPC:%d, Coord(%d,%d) \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, a_iEventID, a_iCaller, a_iUser, a_iNPC, a_iX, a_iY );
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
	}

	int iProceed = 1;
	
	for( int i = iStartIndex; i < iEndIndex; ++i )
	{
		int iTaskID = g_krgEventList[a_iEventID].srgTask[i];
		if( 0 >= iTaskID || eTask_MaxCount <= iTaskID ) continue;
		if( 0 >= iProceed ) break; // 순차 진행 조건이 깨졌을 경우, ...

		switch( g_krgTaskList[iTaskID].iActionID )
		{
		case eTNAct_ResetChakra :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				pMob[a_iUser].ResetStat();
			}
			break;
		case eTNAct_ResetSkillBook :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				pMob[a_iUser].ResetSkill();
			}
			break;
		case eTNAct_ResetClass :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				pMob[a_iUser].ResetClass();
			}
			break;
		case eTNAct_GoldBomb : // gold
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;

				int iGold = g_krgTaskList[iTaskID].irgParam[0]; //
				HS2D_COORD kCenter;
				kCenter.x = pMob[a_iNPC].TargetX;
				kCenter.y = pMob[a_iNPC].TargetY;

			
				STRUCT_ITEM kItem;
				int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( iGold );
				kItem.snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1;
				kItem.snDurability = eDur_Indestructible;
				kItem.byCount = 1;

				enum { e6Gap = 6, e5Gap = 5, e4Gap = 4, e3Gap = 3, e2Gap = 2, e1Gap = 1, eMaxGoldBagCount = 40, };
				HS2D_COORD krgPos[eMaxGoldBagCount];

				krgPos[0].x = kCenter.x - e4Gap;
				krgPos[0].y = kCenter.y + e4Gap;
				krgPos[1].x = kCenter.x - e2Gap;
				krgPos[1].y = kCenter.y + e4Gap;
				krgPos[2].x = kCenter.x;
				krgPos[2].y = kCenter.y + e4Gap;
				krgPos[3].x = kCenter.x + e2Gap;
				krgPos[3].y = kCenter.y + e4Gap;
				krgPos[4].x = kCenter.x + e4Gap;
				krgPos[4].y = kCenter.y + e4Gap;

				krgPos[5].x = kCenter.x - e4Gap;
				krgPos[5].y = kCenter.y + e2Gap;
				krgPos[6].x = kCenter.x - e4Gap;
				krgPos[6].y = kCenter.y;
				krgPos[7].x = kCenter.x - e4Gap;
				krgPos[7].y = kCenter.y - e2Gap;

				krgPos[8].x = kCenter.x + e4Gap;
				krgPos[8].y = kCenter.y + e2Gap;
				krgPos[9].x = kCenter.x + e4Gap;
				krgPos[9].y = kCenter.y;
				krgPos[10].x = kCenter.x + e4Gap;
				krgPos[10].y = kCenter.y - e2Gap;

				krgPos[11].x = kCenter.x - e4Gap;
				krgPos[11].y = kCenter.y - e4Gap;
				krgPos[12].x = kCenter.x - e2Gap;
				krgPos[12].y = kCenter.y - e4Gap;
				krgPos[13].x = kCenter.x;
				krgPos[13].y = kCenter.y - e4Gap;
				krgPos[14].x = kCenter.x + e2Gap;
				krgPos[14].y = kCenter.y - e4Gap;
				krgPos[15].x = kCenter.x + e4Gap;
				krgPos[15].y = kCenter.y - e4Gap;			

				krgPos[16].x = kCenter.x - e3Gap;
				krgPos[16].y = kCenter.y + e5Gap;			
				krgPos[17].x = kCenter.x - e1Gap;
				krgPos[17].y = kCenter.y + e5Gap;			
				krgPos[18].x = kCenter.x + e1Gap;
				krgPos[18].y = kCenter.y + e5Gap;			
				krgPos[19].x = kCenter.x + e3Gap;
				krgPos[19].y = kCenter.y + e5Gap;			

				krgPos[20].x = kCenter.x - e3Gap;
				krgPos[20].y = kCenter.y - e5Gap;			
				krgPos[21].x = kCenter.x - e1Gap;
				krgPos[21].y = kCenter.y - e5Gap;			
				krgPos[22].x = kCenter.x + e1Gap;
				krgPos[22].y = kCenter.y - e5Gap;			
				krgPos[23].x = kCenter.x + e3Gap;
				krgPos[23].y = kCenter.y - e5Gap;			

				krgPos[20].x = kCenter.x - e5Gap;
				krgPos[20].y = kCenter.y + e3Gap;			
				krgPos[21].x = kCenter.x - e5Gap;
				krgPos[21].y = kCenter.y + e1Gap;			
				krgPos[22].x = kCenter.x - e5Gap;
				krgPos[22].y = kCenter.y - e1Gap;			
				krgPos[23].x = kCenter.x - e5Gap;
				krgPos[23].y = kCenter.y - e3Gap;			

				krgPos[24].x = kCenter.x + e5Gap;
				krgPos[24].y = kCenter.y + e3Gap;			
				krgPos[25].x = kCenter.x + e5Gap;
				krgPos[25].y = kCenter.y + e1Gap;			
				krgPos[26].x = kCenter.x + e5Gap;
				krgPos[26].y = kCenter.y - e1Gap;			
				krgPos[27].x = kCenter.x + e5Gap;
				krgPos[27].y = kCenter.y - e3Gap;			

				krgPos[28].x = kCenter.x - e2Gap;
				krgPos[28].y = kCenter.y + e6Gap;			
				krgPos[29].x = kCenter.x;
				krgPos[29].y = kCenter.y + e6Gap;			
				krgPos[30].x = kCenter.x + e2Gap;
				krgPos[30].y = kCenter.y + e6Gap;			

				krgPos[31].x = kCenter.x - e2Gap;
				krgPos[31].y = kCenter.y - e6Gap;			
				krgPos[32].x = kCenter.x;
				krgPos[32].y = kCenter.y - e6Gap;			
				krgPos[33].x = kCenter.x + e2Gap;
				krgPos[33].y = kCenter.y - e6Gap;			

				krgPos[34].x = kCenter.x - e6Gap;
				krgPos[34].y = kCenter.y + e2Gap;			
				krgPos[35].x = kCenter.x - e6Gap;
				krgPos[35].y = kCenter.y;
				krgPos[36].x = kCenter.x - e6Gap;
				krgPos[36].y = kCenter.y - e2Gap;			

				krgPos[37].x = kCenter.x + e6Gap;
				krgPos[37].y = kCenter.y + e2Gap;			
				krgPos[38].x = kCenter.x + e6Gap;
				krgPos[38].y = kCenter.y;
				krgPos[39].x = kCenter.x + e6Gap;
				krgPos[39].y = kCenter.y - e2Gap;			

				for( int iBag = 0; iBag < eMaxGoldBagCount; ++iBag )
				{
					if( 0 >= krgPos[iBag].y || MAX_GRIDY <= krgPos[iBag].y ) continue;
					if( 0 >= krgPos[iBag].x || MAX_GRIDX <= krgPos[iBag].x ) continue;
					int iGroundX, iGroundY;
					iGroundX = krgPos[iBag].x;
					iGroundY = krgPos[iBag].y;
					CreateItem( iGroundX, iGroundY, &kItem, 0, iGold, 0, 0 );
				}
			}
			break;
		case eTNAct_CheckItemOnly :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				int irgSlot[5] = { -1,-1,-1,-1,-1 }; // item 검사/제거를 위한 slot No 기록
				int iCount = 0;
				iCount = pMob[a_iUser].CheckItem( g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], irgSlot ); // 요구사항이 만족하지 못하면 0을 return
				if( 0 >= iCount ) iProceed = 0;
			}
			break;
		case eTNAct_CheckWeapon :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				int iWeapon = pMob[a_iUser].get_WeaponID();
				if( iWeapon != g_krgTaskList[iTaskID].irgParam[0] )
				{ // check한 item이 없다. NPC가 말을 한다.(필요한 아이템이 없습니다.)
					if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC )
                        pMob[a_iNPC].Speak( 200, a_iUser, 0 );
					return eTNRes_EvntItemNotFound;
				}
			}
			break;

		case eTNAct_CheckRemoveItem :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				int irgSlot[5] = { -1,-1,-1,-1,-1 }; // item 검사/제거를 위한 slot No 기록
				int iCount = 0;
				iCount = pMob[a_iUser].CheckItem( g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], irgSlot ); // 요구사항이 만족하지 못하면 0을 return
				int iRes = eTNRes_Succeeded;
				if( iCount < g_krgTaskList[iTaskID].irgParam[1] ) iRes = eTNRes_Failed;
				if( eTNRes_Succeeded == iRes )
                    iRes = pMob[a_iUser].RemoveItem( g_krgTaskList[iTaskID].irgParam[1], irgSlot ); 

				if( iRes )
				{ // check한 item이 없다. NPC가 말을 한다.(필요한 아이템이 없습니다.)
					if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC )
                        pMob[a_iNPC].Speak( 200, a_iUser, 0 );
					return eTNRes_EvntItemNotFound;
				}
				else
				{ // 찾으려는 item이 있다.
					if( 7205 == g_krgTaskList[iTaskID].irgParam[0] ) // 라푸방 문열기
					{
						//SYSTEMTIME st;
						//GetLocalTime( &st );

						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "[eTNAct_CheckRemoveItem] %d월%d일%d시%d분%d초, %s unlocked the gate of the king Raphu!!\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
							, pMob[a_iUser].MOB.szName );
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
					}
				}
			}
			break;
		case eTNAct_DropItem :
			{
				if( HT_PARAMTYPE_ITEM_START <= g_krgTaskList[iTaskID].irgParam[0] && HT_PARAMTYPE_ITEM_END >= g_krgTaskList[iTaskID].irgParam[0] )
				{
					STRUCT_ITEM kItem;
					memset( &kItem, 0, sizeof(kItem) );
					kItem.snIndex = g_krgTaskList[iTaskID].irgParam[0] - HT_PARAMTYPE_ITEM_START + 1;
					kItem.snDurability = pItemData[kItem.snIndex].sMaxDur;
					kItem.byCount = 1;

					int iRes = CreateItem( g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2], &kItem, 0, 0, 0, 0 );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[eTNAct_DropItem] %d월%d일%d시%d분%d초, A item(%d) is dropped at (%d,%d)! Result:%d(0:Failed, other:Succeeded) \r\n"
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, kItem.snIndex
						, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
						, iRes
						 );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ItemDroppedByEvent] );				
				}
			}
			break;
		case eTNAct_CheckQuest :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				int iQuestID = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 > iQuestID || MAX_EVENT_FLAG <= iQuestID ) return eTNRes_EvntInvalidQuestID;
				//if( (0 >= pMob[a_iUser].MOB.byQuest[iQuestID]) || (255 <= pMob[a_iUser].MOB.byQuest[iQuestID] ) )
				if( g_krgTaskList[iTaskID].irgParam[1] != pMob[a_iUser].MOB.byQuest[iQuestID] )
				{
					iProceed = 0;
				}
			}
			break;
		case eTNAct_SetClan :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo;
				g_krgEventList[iTargetEvent].sClan = pMob[a_iUser].m_byClan;
				//if( -1 == g_krgTaskList[iTaskID].irgParam[0] ) g_krgTaskList[iTaskID].irgParam[0] = pMob[a_iUser].m_byClan;
				//else iProceed = pMob[a_iUser].CheckClan( g_krgTaskList[iTaskID].irgParam[0] );
			}
			break;
		case eTNAct_SetDuration :
			{
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo;

				g_krgEventList[iTargetEvent].iDuration = g_krgTaskList[iTaskID].irgParam[1];
				if( 0 < g_krgEventList[iTargetEvent].iDuration ) g_krgEventList[iTargetEvent].uiDurationTime = CurrentTime + (g_krgTaskList[iTaskID].irgParam[1]*1000);
			}
			break;
		case eTNAct_SetAvailableTime :
			{
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo;
				g_krgEventList[iTargetEvent].uiAvailableTime = CurrentTime + (g_krgTaskList[iTaskID].irgParam[1]*1000);
			}
			break;
		case eTNAct_TriggerEvent :
			{
				TriggerEvent( a_iUser, g_krgTaskList[iTaskID].irgParam[0], a_iX, a_iY, a_iNPC, 80 );
			}
			break;
		case eTNAct_AddEventOnScheduler  :
			{
				int iTimeSlot = g_iTimeSlot + (g_krgTaskList[iTaskID].irgParam[1] / 4);
				if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot -= eTS_MaxSlot;
				if( 0 < g_srgTimeSchedule[iTimeSlot] ) // 다른 event가 등록이 되어 있다면, ...
				{
					int iPrevSlot = iTimeSlot-1;
					if( 0 > iPrevSlot ) iPrevSlot = 0;
					if( 0 == g_srgTimeSchedule[iPrevSlot] ) g_srgTimeSchedule[iPrevSlot] = g_krgTaskList[iTaskID].irgParam[0];
					else
					{
						int iCount = 0;
						while(0 < g_srgTimeSchedule[iTimeSlot])
						{
							if( eTS_MaxSlot < iCount ) break;
							++iCount;
							++iTimeSlot;
							if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot = 0;
						}
						g_srgTimeSchedule[iTimeSlot] = g_krgTaskList[iTaskID].irgParam[0];
					}
				}
				else g_srgTimeSchedule[iTimeSlot] = g_krgTaskList[iTaskID].irgParam[0];
			}
			break;
		case eTNAct_RemoveEventOnScheduler :
			{
				for( int i = 0; i < eTS_MaxSlot; ++i )
					if( g_krgTaskList[iTaskID].irgParam[0] == g_srgTimeSchedule[i] ) g_srgTimeSchedule[i] = 0;
			}
			break;

		case eTNAct_AddInstantEventOnScheduler :
			{
				unsigned int uiGap = g_krgTaskList[iTaskID].irgParam[1] * 1000;
				g_kScheduler.AddSchedule( CurrentTime, uiGap, 0, g_krgTaskList[iTaskID].irgParam[0] );
			}
			break;

		case eTNAct_Speak :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;
				pMob[a_iNPC].Speak( g_krgTaskList[iTaskID].irgParam[0], a_iUser, 0 );
			}
			break;
		case eTNAct_Help :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;
				pMob[a_iNPC].CallOthers( eTNGrp_Help, a_iUser );
			}
			break;
		case eTNAct_Link :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;
				pMob[a_iNPC].CallOthers( eTNGrp_Link, a_iUser );
			}
			break;
		case eTNAct_Flee :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;
				pMob[a_iNPC].LetsFlee( pMob[a_iNPC].CurrentTarget );
			}
			break;

		case eTNAct_UseSkill :
			{ // 특정 NPC가 event를 trigger한 user에게 skill을 쓴다. 따라서 user와 npc handle이 모두 존재해야한다.
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				unsigned short usSkillID = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 < usSkillID )
				{
					if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle;
					if( pMob[a_iNPC].set_Skill( usSkillID ) ) return eTNRes_EvntInvalidSkillID;
					pMob[a_iNPC].CurrentTarget = a_iUser;
					pMob[a_iNPC].UseSkill();
				}
			}
			break;
		case eTNAct_ReturnPrevPos :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) continue;
				HS2D_COORD kPos, kDest;
				kPos.x = pMob[a_iUser].TargetX;
				kPos.y = pMob[a_iUser].TargetY;
				kDest.x = pMob[a_iUser].LastX;
				kDest.y = pMob[a_iUser].LastY;
				
				int iWidth, iHeight;
				int iCorrect = 1;
				int iDist = CalDistance( kPos, kDest, 0, 0 );
				if( 2 > iDist ) iCorrect = 4; // 위치를 4배 뒤로
				else if( 3 > iDist ) iCorrect = 3; // 위치를 3배 뒤로
				else if( 4 > iDist ) iCorrect = 2; // 위치를 2배 뒤로

				if( 1 < iCorrect )
				{
					iWidth = kDest.x - kPos.x;					
					iHeight = kDest.y - kPos.x;
					iWidth *= iCorrect;
					iHeight *= iCorrect;
					kDest.x += iWidth;
					kDest.y += iHeight;
				}

				if	( kDest.x<0 || kDest.y<0 || kDest.x>MAX_GRIDX || kDest.y>MAX_GRIDY ) continue;

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm)-sizeof(HEADER);
				nm.TargetX = kDest.x; nm.TargetY = kDest.y;
				nm.dwKeyID = a_iUser;
				nm.PosX=0; nm.PosY=0; nm.Direction = 0; 
				nm.Effect = 6; // knock-back motion

				pUser[a_iUser].cSock.AddMessage( (char*)&nm, sizeof(nm) );
				pUser[a_iUser].cSock.SendMessage();
			}
			break;
		case eTNAct_KnockBack :
			break;
		case eTNAct_Teleport :
			{ // player가 특정 cell에 위치를 하게되면, target과의 거리가 가까우면, 이동(teleport type)으로 처리를 한다.
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				//if( 0 < g_krgTaskList[iTaskID].irgParam[0] ) // 특정 clan만 허락한다. 0일 경우는 모두 permit
				//	if( g_krgTaskList[iTaskID].irgParam[0] != pMob[a_iUser].m_byClan ) return;

				HS2D_COORD kCell, kDest;
				kCell.x = a_iX;
				kCell.y = a_iY;
				kDest.x = g_krgTaskList[iTaskID].irgParam[1]; //pMob[a_iUser].TargetX;
				kDest.y = g_krgTaskList[iTaskID].irgParam[2]; // pMob[a_iUser].TargetY;
				int iDist = CalDistance( kCell, kDest, 0, 0 );
				if( 100 >= iDist )
				{
					pUser[a_iUser].nPreX = kDest.x;
					pUser[a_iUser].nPreY = kDest.y;

					MSG_Action nm; nm.wType = _MSG_Action;
					nm.wPDULength = sizeof(nm)-sizeof(HEADER);
					nm.TargetX=kDest.x; nm.TargetY= kDest.y;
					nm.dwKeyID = a_iUser;
					nm.PosX=0; nm.PosY=0; nm.Direction = 0; 
					nm.Effect = g_krgTaskList[iTaskID].irgParam[0]; // 이동 형태, // 0:앉기  1:서기  2:걷기  3:뛰기  4:날기  5:텔레포트,	6:밀리기(knock-back), 7:미끄러지기(이동애니없음)  8:도발, 9:인사, 10:돌격 

					pUser[a_iUser].cSock.AddMessage( (char*)&nm, sizeof(nm) );
					pUser[a_iUser].cSock.SendMessage();
				}
				else Teleport( a_iUser, kDest.x, kDest.y );
			}
			break;
		case eTNAct_TeleportParty :
			{
				int iLeader = pMob[a_iUser].Leader ;
				if( 0 >= iLeader || MAX_USER <= iLeader ) iLeader = a_iUser ; // 자신이 리더이다. 

				// 파티원들 소환
				for( int d = 0 ; d < MAX_PARTY+1 ; ++d )
				{   
					int fol = 0;
					if(d==0) fol = iLeader;
					else fol = pMob[iLeader].m_irgParty[d-1] ;
					if( 0 > fol || MAX_USER <= fol ) continue ;					
					Teleport( fol, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1]);
				}		
			}
			break;
		case eTNAct_RangeUp :
			{

			}
			break;
		case eTNAct_Mine :
			{// mine의 등급에 따라 event ID가 틀리다. 5등급의 mine이 존재한다면, event ID도 5가지이면 될 것이다.

			}
			break; 
		case eTNAct_PopMonster :
			{// 0:monster ID, 1:x, 2:y, 3:pop type, 4:direction, 5:clan
				int iSummoner = 0;
				int iClan = g_krgTaskList[iTaskID].irgParam[5];
				if( eTNClan_NoTrimuritiy >= iClan || eTNClan_NPC < iClan ) iClan = eTNClan_Aggressive;
				if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC ) iSummoner = a_iNPC;
				int iMonsterHandle = pMob[iSummoner].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, g_krgTaskList[iTaskID].irgParam[3], eTNCls_Warrior, eTNCls2_Basic, iClan, g_krgTaskList[iTaskID].irgParam[4] , g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2], pMob[iSummoner].CurrentTarget, false, 0, 0, 60 );
			}
			break;
		case eTNAct_PopMonster2 :
			{// 0: monster ID, 1:class1, 2:clan, 3:direction, 4:x, 5:y
				int iMonsterHandle = pMob[1000].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, eTNPrdt_PopNormal, g_krgTaskList[iTaskID].irgParam[1], eTNCls2_Basic, g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3] , g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5], 0, false, 0, 0, 61 );
			}
			break;
		case eTNAct_PopMonster3 : // 0: Monster ID	1:clan	2:pop type	3:n(개체수)	4:route ID	5:life time
			{
				for( int i = 0; i < g_krgTaskList[iTaskID].irgParam[3]; ++i )
				{
					int iMonsterHandle = pMob[1000].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, g_krgTaskList[iTaskID].irgParam[2], eTNCls_Warrior, eTNCls2_Basic, g_krgTaskList[iTaskID].irgParam[1]/*clan*/, 0, 0, 0, 0, false, g_krgTaskList[iTaskID].irgParam[5], 0, 62, g_krgTaskList[iTaskID].irgParam[4]/*route*/ );
				}
				//int iRes = pMob[iMonsterHandle].set_Segment( g_krgTaskList[iTaskID].irgParam[4] );
			}
			break;
		case eTNAct_PopMonster4 : // 0: Monster ID	1: PopType
			{ // 부모의 모든 속성을 상속해서 pop
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) break;
				int iMonsterHandle = pMob[a_iNPC].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, g_krgTaskList[iTaskID].irgParam[1], pMob[a_iNPC].MOB.byClass1, pMob[a_iNPC].MOB.byClass2, pMob[a_iNPC].m_byClan, 0, pMob[a_iNPC].TargetX, pMob[a_iNPC].TargetY, pMob[a_iNPC].CurrentTarget, false, 0, 0, 63, 0 );
			}
			break;
		case eTNAct_KillMonster : // 좌표 주위에 있는 특정 ID 몬스터를 죽인다.
			{
				int iPosX = g_krgTaskList[iTaskID].irgParam[0];
				int iPosY = g_krgTaskList[iTaskID].irgParam[1];

				// 지정된 좌표에 죽이려는 몬스터가 있는 경우
				int iMonsterHandle = pMobGrid[iPosY][iPosX];				
				if( pMob[iMonsterHandle].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[2] ) KillMonster( iMonsterHandle );

				int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
				int x = 0, y = 0;			
				for( int i = 0; i < iMaxIndex; ++i )
				{
					x = iPosX + g_pDetectEnemyTable[i][0];
					y = iPosY + g_pDetectEnemyTable[i][1];
					if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
					iMonsterHandle = pMobGrid[y][x];
					if( MAX_USER > iMonsterHandle || MAX_MOB <= iMonsterHandle ) continue;
					if( pMob[iMonsterHandle].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[2] )
					{
						KillMonster( iMonsterHandle );
					}
				}
			}
			break;
		case eTNAct_KillMonsterAll : // 특정 ID의 몬스터를 모두 죽인다.
			{//0:tribe
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						KillMonster( i );
					}
				}
			}
			break;
		case eTNAct_ChangeClanByTribe :
			{
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						pMob[i].MOB.byTrimuriti = pMob[i].m_byClan = g_krgTaskList[iTaskID].irgParam[1];
						pMob[i].ClearCurrentTarget();
						pMob[i].ClearAttacker( 0 );
						pMob[i].Mode = MOB_PEACE;
					}
				}
			}
			break;

		case eTNAct_ChangeClanByTribe2 :
			{
				int iSiege = g_kSiege.get_Started();
				if( iSiege ) continue;

				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						pMob[i].MOB.byTrimuriti = pMob[i].m_byClan = g_krgTaskList[iTaskID].irgParam[1];
						pMob[i].ClearCurrentTarget();
						pMob[i].ClearAttacker( 0 );
						pMob[i].Mode = MOB_PEACE;
					}
				}
			}
			break;
		case eTNAct_ChangeBaseRwdCorrect :
			{				
				//ChangeRwdCorrect( eRwd_Base, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
			}
			break;
		case eTNAct_PlusExtraRwdCorrect :
			{
				ChangeRwdCorrect( eRwd_Extra, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], 0, 0 );
			}
			break;
		case eTNAct_MinusExtraRwdCorrect :
			{
				ChangeRwdCorrect( eRwd_ExtraMinus, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], 0, 0 );
			}
			break;
		case eTNAct_AffectAEffectToClanMonsters :
			{
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
					if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

					if( pMob[i].m_byClan == g_krgTaskList[iTaskID].irgParam[0] ) 
					{
						TNEFFECT kEffect;
						kEffect.iID = g_krgTaskList[iTaskID].irgParam[1];
						kEffect.kFunc.iData = g_krgTaskList[iTaskID].irgParam[2];
						kEffect.iDuration = g_krgTaskList[iTaskID].irgParam[3];
						kEffect.iParam1 = g_krgTaskList[iTaskID].irgParam[4];
						kEffect.iParam2 = g_krgTaskList[iTaskID].irgParam[5];
						pMob[i].AddEffect( kEffect, i, i );
						pMob[i].BroadcastUpdateStatusMsg();
					}
				}
			}
			break;
		case eTNAct_GambleResetMomey:
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleMoney Reset \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_ResetMoney();
			}	break;
		case eTNAct_GambleBetOn:		//	윷놀이 베팅시작
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleBetOn \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_SetBet(1);
				g_Yut.HT_Init();
			}	break;
		case eTNAct_GambleBetOff:		//	윷놀이 베팅종료
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleBetOff \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_SetBet(0);
			}	break;
		case eTNAct_GambleSetOn:		//	육놀이 세팅시작
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleSetOn \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleSetOff:		//	육놀이 세팅종료
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleSetOff \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleResultOn:		//	육놀이 결과생성
			{
				g_Yut.HT_ShareMoney();
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleResultOn \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleResultOff:	//	육놀이 결과정리
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleResultOff \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GamblePlayOn:		//	육놀이 게임진행(서버에서 진행시킨다)
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GamblePlayOn \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
				for(int x=653; x<678; x++)
				{
					for(int y=407; y<432; y++)
					{
						if(pMobGrid[y][x]==0) continue;
						sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
						TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
					}
				}
#endif	//	#ifdef __YUT_LOG__
				//g_Yut.m_iYutID = 


				g_Yut.HT_SetPlay(1);
				YutCounter = 225;		//	15초 마다 실행된다.
				//YutTimer = 0;
			}	break;
		case eTNAct_GamblePlayOff:		//	육놀이 게임종료
			{
				g_Yut.HT_SetPlay(0);
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GamblePlayOff \r\n"); TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
				for(int x=653; x<678; x++)
				{
					for(int y=407; y<432; y++)
					{
						if(pMobGrid[y][x]==0) continue;
						sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
						TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
					}
				}
#endif	//	#ifdef __YUT_LOG__

			}	break;
		case eTNAct_GambleBroadcast:	//	육놀이 관련 공지
			{
				short snX,snY=0;

				WORD wMsg = g_krgTaskList[iTaskID].irgParam[0]; 
				WORD wNPC = g_krgTaskList[iTaskID].irgParam[1];

#ifdef __YUT_LOG__
				sprintf(temp, "Yut_Broadcast NPCID:%d, msgID:%d \r\n", wNPC, wMsg);
				TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__

				if(!g_ParamMgr.HT_bGetNPCPosition( wNPC, &snX, &snY )) continue;		//	해당 NPC정보를 읽지 못할경우.

				MSG_Broadcast sm; sm.wType = _MSG_Broadcast;						//	존내 전광판공지
				sm.byMsgType = MESSAGE_EXTRA;
				sm.byTextColor = 12;
				sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER);
				strncpy(sm.szMsg, g_pMessageStringTable[wMsg], sizeof(sm.szMsg));
				strncpy(sm.szName, g_pMessageStringTable[_YutNPCName], sizeof(sm.szName)); 
				SendToAll((MSG_STANDARD*)&sm);

				S_SCP_NOTIFY_CHAT nm;	nm.wType = SCP_NOTIFY_CHAT;					//	NPC Chat
				nm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
				nm.nID=10000+wNPC;													//	NPC + 10000(NPC의 경우 +10000하기로함)
				nm.byTextColor=12; nm.byBgColor = 0; nm.byTrimuriti=0;				//	차후 정해지면 변경
				strncpy(nm.szMsg, g_pMessageStringTable[wMsg], sizeof(nm.szMsg));
				GridMulticast(snX, snY, (MSG_STANDARD*)&nm, 0, 200);
			}	break;
		case etnAct_MoveGambleHorse :
			{
				Teleport( g_iGambleHorse, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1] );
			}
			break;
		case eTNAct_KillMonsterWithClan : // 특정 clan monster들은 모두 죽인다.
			{// 0:clan
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
					if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

					if( pMob[i].m_byClan == g_krgTaskList[iTaskID].irgParam[0] ) 
					{
						KillMonster( i );
					}
				}
			}
			break;
		case eTNAct_KillPC :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) continue;
				pMob[a_iUser].MOB.nHP = 0;
				pMob[a_iUser].CurrentTarget = 0;
				pMob[a_iUser].m_eFSM = eTNFsm_Dead;
				pMob[a_iUser].NotifyUpdateStatusMsg();

				int iPosX = pMob[a_iUser].TargetX;
				int iPosY = pMob[a_iUser].TargetY;

				if( eZone_Chaturanka == g_iZoneID )
				{
					//a_iNPC를 찾아야 한다.
					int iMonsterHandle = 0;
					int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
					int x = 0, y = 0;			
					for( int i = 0; i < iMaxIndex; ++i )
					{
						x = iPosX + g_pDetectEnemyTable[i][0];
						y = iPosY + g_pDetectEnemyTable[i][1];
						if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
						iMonsterHandle = pMobGrid[y][x];
						if( MAX_USER > iMonsterHandle || MAX_MOB <= iMonsterHandle ) continue;
						if( 2934 <= pMob[iMonsterHandle].MOB.snTribe && 2937 >= pMob[iMonsterHandle].MOB.snTribe )
						{
							a_iNPC = iMonsterHandle;
							pMob[a_iUser].OnKilled( a_iNPC, 8 );
							break;
						}
					}
				}
				else
				{
					pMob[a_iUser].OnKilled( a_iNPC, 8 );
				}
				
			}
			break;
		case eTNAct_Vanish :
			{
				KillMonster( a_iNPC );
			}
		case eTNAct_KillMonsterInSquare :
			{
				int iStartX, iEndX, iStartY, iEndY;

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue;
						if( eTNCls_NPC == pMob[iMob].MOB.byClass1 ) continue;
						if( eTNCls_Event == pMob[iMob].MOB.byClass1 ) continue;

						if( 0 == g_krgTaskList[iTaskID].irgParam[4] ) KillMonster( iMob );
						else
						{
							if( pMob[iMob].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[4] ) KillMonster( iMob );
						}
					}
				}
			}
			break;

		case eTNAct_KillAll :
			{
				int iStartX, iEndX, iStartY, iEndY;

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_MOB <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.
						if( eTNCls_NPC == pMob[iMob].MOB.byClass1 ) continue;
						if( eTNCls_Event == pMob[iMob].MOB.byClass1 ) continue;

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							pMob[iMob].MOB.nHP = 0;
							pMob[iMob].NotifyUpdateStatusMsg();

							pMob[iMob].OnKilled( a_iNPC, 9 );
						}
						else
						{
							KillMonster( iMob );
						}
					}
				}
			}
			break;
		case eTNAct_RefreshCharacterData :
			{
				for( int i = 1; i < MAX_USER; ++i )
				{
					if( MOB_EMPTY == pMob[i].Mode ) continue;
					if( USER_PLAY != pUser[i].Mode ) continue;
					pMob[i].NotifyUpdateStatusMsg();
				}
			}
			break;
		case eTNAct_CheckKalaSystem :
			{
				CheckKalaSystem();
			}
			break;
		case eTNAct_PrintKalaCoreInfo :
			{
				MoveKalaRewarder();
			}
			break;
		case eTNAct_DrawCard: // deck
			{
				int iDeck = g_krgTaskList[iTaskID].irgParam[0];
				int iEvent = g_krgEventDeck[iDeck].Random();

				TriggerEvent( a_iUser, iEvent, a_iX, a_iY, a_iNPC, 1205 );		
			}
			break;
		case eTNAct_KickOut :
			{
				int iStartX, iEndX, iStartY, iEndY;

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}
				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_MOB <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{// save 지역으로 돌아간다. 차투랑가 zone이 닫히니까 user들을 모두 밖으로 내보내야 한다.
							ReturnPCToSaveZone( iMob );
						}
					}
				}
			}
			break;
		case eTNAct_CountRealmEntry :
			{ // 꾸준한 주신전 참여인원수를 기록한다.
				int iCountCheckSum = 10000;
				if( (iCountCheckSum < g_irgEntryCount[eTNClan_Siva]) && (iCountCheckSum < g_irgEntryCount[eTNClan_Brahma]) && (iCountCheckSum < g_irgEntryCount[eTNClan_Vishnu]) )
				{
					g_irgEntryCount[eTNClan_Siva] -= iCountCheckSum;
					g_irgEntryCount[eTNClan_Brahma] -= iCountCheckSum;
					g_irgEntryCount[eTNClan_Vishnu] -= iCountCheckSum;
				}

				for( int i = 1; i < MAX_USER; ++i )
				{
					if( MOB_EMPTY == pMob[i].Mode ) continue;
					if( USER_PLAY == pUser[i].Mode )
					{
						int iClan = pMob[i].m_byClan;
						if( 1 > iClan || 4 < iClan ) continue;
						++g_irgEntryCount[iClan];
					}
				}

				g_irgEntryCount[0] = g_irgEntryCount[eTNClan_Brahma] + g_irgEntryCount[eTNClan_Vishnu] + g_irgEntryCount[eTNClan_Siva];

				#ifdef __TN_EMERGENCY_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );

					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "%[dyy%dmm%ddd %dhh%dmi%dss] eTNAct_CountRealmEntry >  Total: %d, brama:%d, vishunu:%d, siva:%d \r\n"
						, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, g_irgEntryCount[0], g_irgEntryCount[eTNClan_Brahma], g_irgEntryCount[eTNClan_Vishnu], g_irgEntryCount[eTNClan_Siva] );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RvREntry] );
				}
				#endif //__TN_EMERGENCY_LOG__
			}
			break;
		case eTNAct_PostMessageToZone :
			{
				if( 0 > g_krgTaskList[iTaskID].irgParam[0] || MAX_STRING <= g_krgTaskList[iTaskID].irgParam[0] ) break;
				PostMessageToZone( g_pMessageStringTable[g_krgTaskList[iTaskID].irgParam[0]], eTNClr_White, eTNClr_BG, g_krgTaskList[iTaskID].irgParam[0] );
			}
			break;
		case eTNAct_PostMessageToWorld :
			{
				if( 0 > g_krgTaskList[iTaskID].irgParam[0] || MAX_STRING <= g_krgTaskList[iTaskID].irgParam[0] ) break;
				PostMessageToWorld( g_pMessageStringTable[g_krgTaskList[iTaskID].irgParam[0]], eTNClr_White, eTNClr_BG, g_krgTaskList[iTaskID].irgParam[0] );
			}
			break;
		case eTNAct_RecordName :
			{// 특정 사각 지역 내의 모든 PC name을 기록한다.
				int iStartX, iEndX, iStartY, iEndY;
				// Param0 : 끝 X
				// Param1 : 시작 X
				// Param2 : 끝 Y
				// Param3 : 시작 Y
				// Param4 : 목표 X
				// Param5 : 목표 Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] Record PCs in the event(%d)\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, a_iEventID );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RecordPCName] );
				}
				#endif

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						if( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 skip

						if( (eTNMob_PC == pMob[iMob].m_eMobType) && (0 < pMob[iMob].MOB.nHP) )
						{
							#ifdef __TN_TOP_LOG__
							{
								char chBuf[256] = { 0,0,0, };
								sprintf(chBuf, "\t- %s\r\n", pMob[iMob].MOB.szName );
								WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RecordPCName] );
							}
							#endif
						}
					}
				}
			}
			break;
		case eTNAct_RecordPCNameInZone :
			{
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n[%dMM%dDD %dHH%dMS%dSS] eTNAct_RecordPCNameInZone>\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RecordPCName] );
				}
				#endif

				for( int iPC = 0; iPC < MAX_USER; ++iPC )
				{
					if( USER_PLAY != pUser[iPC].Mode ) continue;
					if( eTNClan_GM == pMob[iPC].m_byClan ) continue;
					if( eTNCls_NPC == pMob[iPC].MOB.byClass1 ) continue;

					#ifdef __TN_TOP_LOG__
					{
						char chBuf[256] = { 0,0,0, };
						sprintf(chBuf, "\t- %s, HP:%d \r\n", pMob[iPC].MOB.szName, pMob[iPC].MOB.nHP );
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_RecordPCName] );
					}
					#endif
				}
			}
			break;

		case eTNAct_PostStrongholdOwner :
			{
				char szMsg[1024] = { 0,0,0, };

				// 총 2개의 지역에 8개의 stronghold가 있다. 북동쪽요새는 2개가 있다. 요새 이름이 정해져야 한다.
				// 두르가 지역이라고 그랬는데, 기존에는 하나의 zone을 하나의 지역으로 이해하고 있었는데
				// 현재는 두개의 zone을 두르가 지역이라고 부르는 문제점이 발생한다.
				if( 15 == ServerIndex ) // 두르가 1지역
				{
					if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthEasternStronghold] );
						else
						{
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthEasternStronghold], g_krgStronghold[eStronghold_Northeast].szGuildName/*길드명*/ );
						}						
					}
					else if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthWesternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthWesternStronghold], g_krgStronghold[eStronghold_Northwest].szGuildName/*길드명*/ );
						}
					}
					else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthEasternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthEasternStronghold], g_krgStronghold[eStronghold_Southeast].szGuildName/*길드명*/ );
						}
					}
					else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthWesternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthWesternStronghold], g_krgStronghold[eStronghold_Southwest].szGuildName/*길드명*/ );
						}
					}
				}
				else if( 16 == ServerIndex ) // 두르가 2지역
				{
					if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthEasternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthEasternStronghold], g_krgStronghold[eStronghold_Northeast].szGuildName/*길드명*/ );
						}						
					}
					else if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthWesternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthWesternStronghold], g_krgStronghold[eStronghold_Northwest].szGuildName/*길드명*/ );
						}
					}
					else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthEasternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthEasternStronghold], g_krgStronghold[eStronghold_Southeast].szGuildName/*길드명*/ );
						}
					}
					else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthWesternStronghold] );
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner 에 대한 guild ID를 검색해야 한다.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthWesternStronghold], g_krgStronghold[eStronghold_Southwest].szGuildName/*길드명*/ );
						}
					}
				}

				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );

					char chBuf[2048] = { 0,0,0, };
					sprintf(chBuf, "[eTNAct_PostStrongholdOwner] %d월%d일%d시%d분%d초, MSG(ID:%d) : %s\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, g_krgTaskList[iTaskID].irgParam[0], szMsg );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
				}

				PostMessageToWorld( szMsg );
			}
			break;				   
		case eTNAct_KillKingAtChaturangka : // kill a king
			{
				for( int iHandle = MAX_USER; iHandle < MAX_MOB; ++iHandle )
				{
					if( (2113 == pMob[iHandle].MOB.snTribe) || (2112 == pMob[iHandle].MOB.snTribe) ) // 
					{
						if( 0 < pMob[iHandle].MOB.nHP ) // alive 상태에 있던 것을 죽일 때만 로그에 남긴다.
						{
							pMob[iHandle].MOB.nHP = 0; 
							pMob[iHandle].CurrentTarget = 0;
							DeleteMob( iHandle, 125, 0, eTNPrdt_RemoveNormal, 250 );

							pMob[iHandle].Mode = MOB_EMPTY;
							//if(iHandle!=pMobGrid[pMob[iHandle].TargetY][pMob[iHandle].TargetX]) MessageBox(NULL, "error_DELETEMOB2", "error", MB_OK);
							pMobGrid[pMob[iHandle].TargetY][pMob[iHandle].TargetX] = 0;


							#ifdef __TN_TOP_LOG__
							{
								//SYSTEMTIME st;
								//GetLocalTime( &st );
								char chBuf[512] = { 0,0,0, };
								sprintf(chBuf, "\r\n\n[%dmm%ddd %dhh%dms%dss] kill the king \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
								WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
							}
							#endif    
						}
					}					
				}
			}
			break;
		case eTNAct_CloseKingRoomAtChaturangka : // close 차투랑가 왕방
			{// 모든 user를 튕겨내야 한다. -> 차투랑가의 빈 portal field로 teleport 시켜준다. or 주신전 지역으로 보낸다?
				int iStartX, iEndX, iStartY, iEndY;
				iStartX = 371;
				iEndX = 523;
				iStartY = 497;
				iEndY = 652;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n\n[%dmm%ddd %dhh%dms%dss] Close the zone of the king!\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
				}
				#endif    
				int irgPopPos[4][2]  = { 868, 815, 833, 813, 833, 848, 868, 851 };
				int iIndex = 0;
				
				for( int y = iStartY; y < iEndY; ++y )
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue;

						ReturnPCToSaveZone(iMob);
					}
			}
			break;
		case eTNAct_CheckMonster2 : // 특정 ID의 몬스터가 현재 생존해 있는지 파악한다.
			{
				int iCount = 0;
				for( int iMob = MAX_USER; iMob < MAX_MOB; ++iMob )
				{
					if( pMob[iMob].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iCount;
					}
				}		

				if( 0 == iCount ) iProceed = 0;
			}
			break;

		case eTNAct_CountMonster :
			{
				int iStartX, iEndX, iStartY, iEndY;

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				int iMonsterCount = 0;
				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue;
						if( eTNMob_NPC == pMob[iMob].m_eMobType )
						{
							if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iMonsterCount;
						}
					}
				}

				if( g_krgTaskList[iTaskID].irgParam[4] < iMonsterCount )
				{
					iProceed = 0;
				}
			}
			break;
	   
		case eTNAct_CountMonsterByTribe :
			{
				int iStartX, iEndX, iStartY, iEndY;

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				int iMonsterCount = 0;
				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue;
						if( eTNMob_NPC == pMob[iMob].m_eMobType )
						{
							if( g_krgTaskList[iTaskID].irgParam[4] == pMob[iMob].MOB.snTribe )
								if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iMonsterCount;
						}
					}
				}

				if( g_krgTaskList[iTaskID].irgParam[5] < iMonsterCount )
				{
					iProceed = 0;
				}
			}
			break;

		case eTNAct_TeleportAll :
			{ // 특정 사각 지역 내의 모든 PC를 목표지점으로 teleport시킨다.
				int iStartX, iEndX, iStartY, iEndY;
				// Param0 : 끝 X
				// Param1 : 시작 X
				// Param2 : 끝 Y
				// Param3 : 시작 Y
				// Param4 : 목표 X
				// Param5 : 목표 Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				//char pLog[512] = { 0,0,0, };
				//int iUserCount = 0;
				//for( int y = 0; y < MAX_GRIDY; ++y )
				//{
				//	for( int x = 0; x < MAX_GRIDY; ++x )
				//	{	int iMob = pMobGrid[y][x];
				//		if(iMob<=0 || iMob>=MAX_USER) continue;

				//		sprintf( pLog, "\tName:%s, coord(%d,%d), TargetX:%d, TargetY:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
				//			pMob[iMob].MOB.szName, x, y, pMob[iMob].TargetX, pMob[iMob].TargetY, pMob[iMob].Mode, pMob[iMob].m_byClan, pMob[iMob].m_eMobType);
				//		WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );
				//		++iUserCount;
				//	}
				//}
				//sprintf( pLog, "iStartX:%d, iEndX:%d, iStartY:%d, iEndY:%d UserCount:%d \r\n", iStartX, iEndX, iStartY, iEndY, iUserCount);
				//WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );

				//iUserCount = 0;
				//for(int i=1; i<10; i++)
				//{
				//	if(pUser[i].Mode == USER_EMPTY) continue;

				//	sprintf( pLog, "Name:%s, coord(%d,%d), grid:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
				//		pMob[i].MOB.szName, pMob[i].TargetX, pMob[i].TargetY, pMobGrid[pMob[i].TargetY][pMob[i].TargetX], pMob[i].Mode, pMob[i].m_byClan, pMob[i].m_eMobType);
				//	WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );
				//	++iUserCount;

				//}
				//sprintf( pLog, "iStartX:%d, iEndX:%d, iStartY:%d, iEndY:%d UserCount:%d \r\n", iStartX, iEndX, iStartY, iEndY, iUserCount);
				//WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );


				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;

						//sprintf( pLog, "\tName:%s, coord(%d,%d), TargetX:%d, TargetY:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
						//	pMob[iMob].MOB.szName, x, y, pMob[iMob].TargetX, pMob[iMob].TargetY, pMob[iMob].Mode, pMob[iMob].m_byClan, pMob[iMob].m_eMobType);
						//WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );

						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							{
								char chBuf[512] = { 0,0,0, };
								sprintf( chBuf, "\tName:%s, coord(%d,%d)\r\n", pMob[iMob].MOB.szName, x, y );
								WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
							}

							Teleport( iMob, g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] );
							/*
							if( 0 >= pMob[iMob].MOB.nHP )
							{ // 죽어 있는 캐릭터는 save zone으로 보낸다.
								MSG_MoveOtherZone sm; sm.wType=_MSG_MoveOtherZone;
								sm.byType=CONNECT_TYPE_PUSTICA; sm.snPositionID= pMob[iMob].m_snSaveNPC;
								pUser[iMob].cSock.SendOneMessage((char*)&sm, sizeof(sm));
							}
							else
							{ // PC만 이동시킨다.
								Teleport( iMob, g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] );
							}
							*/
						}
					}
				}

				//iUserCount = 0;
				//for( int y = 0; y < MAX_GRIDY; ++y )
				//{
				//	for( int x = 0; x < MAX_GRIDY; ++x )
				//	{	int iMob = pMobGrid[y][x];
				//		if(iMob<=0 || iMob>=MAX_USER) continue;

				//		sprintf( pLog, "\tName:%s, coord(%d,%d), TargetX:%d, TargetY:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
				//			pMob[iMob].MOB.szName, x, y, pMob[iMob].TargetX, pMob[iMob].TargetY, pMob[iMob].Mode, pMob[iMob].m_byClan, pMob[iMob].m_eMobType);
				//		WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );
				//		++iUserCount;
				//	}
				//}

				//sprintf( pLog, "iStartX:%d, iEndX:%d, iStartY:%d, iEndY:%d UserCount:%d \r\n", iStartX, iEndX, iStartY, iEndY, iUserCount);
				//WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );
			}
			break;
		case eTNAct_ReturnPCToSaveZone :
			{
				for( int i = 1; i < MAX_USER; ++i )
				{
					if( eTNClan_GM == pMob[i].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.
					ReturnPCToSaveZone( i );
				}
			}
			break;
		case eTNAct_ReturnToTrimuritiZone :
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				/*
				char chBuf2[512] = { 0,0,0, };
				sprintf(chBuf2, "[eTNAct_ReturnToSaveZone] %d월%d일%d시%d분%d초, 주신던젼 닫힘. \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				WriteLog( chBuf2, g_szrgLogFileName[eLogFileName_EventTriggered] );

				{
					char chBuf[2048] = { 0,0,0, };
					sprintf(chBuf, "\n\n\n[eTNAct_ReturnToSaveZone] %d월%d일%d시%d분%d초\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, ".\\Event\\[Log]ReturnToSaveZone.txt" );
				}
				*/

		/*		char pLog[512] = { 0,0,0, };
				int iUserCount = 0;
				for( int y = 0; y < MAX_GRIDY; ++y )
				{
					for( int x = 0; x < MAX_GRIDY; ++x )
					{	int iMob = pMobGrid[y][x];
						if(iMob<=0 || iMob>=MAX_USER) continue;

						sprintf( pLog, "\tName:%s, coord(%d,%d), TargetX:%d, TargetY:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
							pMob[iMob].MOB.szName, x, y, pMob[iMob].TargetX, pMob[iMob].TargetY, pMob[iMob].Mode, pMob[iMob].m_byClan, pMob[iMob].m_eMobType);
						WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );
						++iUserCount;
					}
				}
				sprintf( pLog, "Zone UserCount:%d \r\n",iUserCount);
				WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );

				iUserCount = 0;
				for(int i=1; i<10; i++)
				{
					if(pUser[i].Mode == USER_EMPTY) continue;

					sprintf( pLog, "Name:%s, coord(%d,%d), grid:%d, Mode:%d, Clan:%d, Type:%d \r\n", 
						pMob[i].MOB.szName, pMob[i].TargetX, pMob[i].TargetY, pMobGrid[pMob[i].TargetY][pMob[i].TargetX], pMob[i].Mode, pMob[i].m_byClan, pMob[i].m_eMobType);
					WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered
					] );
					++iUserCount;

				}
				sprintf( pLog, "Play UserCount:%d \r\n", iUserCount);
				WriteLog( pLog, g_szrgLogFileName[eLogFileName_EventTriggered] );*/

				for( int i = 1; i < MAX_USER; ++i )
				{
					if( USER_PLAY == pUser[i].Mode )
					{
						ReturnPCToSaveZone(i);
					}
				}

				for( int i = 1; i < MAX_USER; ++i )
				{
					pMob[i].m_kWaitAction.iAction = eWaitAct_ZonePortal;
					CloseUser(i);
				}
			}
			break;
		case eTNAct_ChangeField :
			{ // 특정 사각 지역 속성을 변경한다.
				int iStartX, iEndX, iStartY, iEndY;
				// Param0 : 끝 X
				// Param1 : 시작 X
				// Param2 : 끝 Y
				// Param3 : 시작 Y
				// Param4 : 목표 X
				// Param5 : 목표 Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						if( 1 == g_krgTaskList[iTaskID].irgParam[5] ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | (unsigned short)(g_krgTaskList[iTaskID].irgParam[4]); // 추가
						else if( 0 == g_krgTaskList[iTaskID].irgParam[5] )
						{
							unsigned short usNewProperty = (unsigned short)(g_krgTaskList[iTaskID].irgParam[4]);
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty; // XOR로 제거
						}
					}
				}
			}
			break;

		case eTNAct_AffectAll :
			{ // 특정 사각 지역 속성을 변경한다.
				int iStartX, iEndX, iStartY, iEndY;
				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.
						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							if( 0 >= pMob[iMob].MOB.nHP ) continue;

							TNEFFECT kEffect;
							kEffect.iID = g_krgTaskList[iTaskID].irgParam[4];
							kEffect.iDuration = g_krgTaskList[iTaskID].irgParam[5];
							kEffect.iParam1 = 100;
							kEffect.iParam2 = 0;
							pMob[iMob].AddEffect( kEffect, iMob, iMob );
							pMob[iMob].BroadcastUpdateStatusMsg();
							pUser[iMob].cSock.SendMessage();
						}
					}
				}
			}
			break;

		case eTNAct_DebufferAll :
			{ // 특정 사각 지역 속성을 변경한다.
				int iStartX, iEndX, iStartY, iEndY;
				iStartX = g_krgTaskList[iTaskID].irgParam[1];
				iEndX = g_krgTaskList[iTaskID].irgParam[0];
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0];
					iEndX = g_krgTaskList[iTaskID].irgParam[1];
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3];
				iEndY = g_krgTaskList[iTaskID].irgParam[2];
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2];
					iEndY = g_krgTaskList[iTaskID].irgParam[3];
				}

				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다.
						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							if( 0 >= pMob[iMob].MOB.nHP ) continue;
							pMob[iMob].TurnOffAffection( g_krgTaskList[iTaskID].irgParam[4] );
						}
					}
				}
			}
			break;
		case eTNAct_ChangeImmunity :
			{
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[1] )
					{
						if( 1 == g_krgTaskList[iTaskID].irgParam[0] )  // 추가
						{
							pMob[i].m_iImmunity = g_krgTaskList[iTaskID].irgParam[2];
						}
						else if( 0 == g_krgTaskList[iTaskID].irgParam[0] ) // 제거를 하게되면 원래의 초기 기본 속성으로 돌아간다.
						{
							pMob[i].m_iImmunity = pMonsterData[pMob[i].MOB.nTP].nGuildID;
						}
					}
				}
			}
			break;

		case eTNAct_CountBrahmaMonster :
			{
				int iCount = 0;
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( eTNClan_BrahmaSoldier == pMob[i].m_byClan )
					{
						if( pMob[i].IsDead() ) continue;
						++iCount;
						//if( 0 < pMob[i].MOB.nHP ) ++iCount;
					}
				}

				if( 0 < iCount )
				{
					iProceed = 0;

					if( 6> iCount )
					{
						char chBuf[1024] = { 0,0,0, };
						sprintf(chBuf, "[eTNAct_CountBrahmaMonster] %d월%d일%d시%d분%d초> \r\n"
									, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
									);
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

						for( int i = MAX_USER; i < MAX_MOB; ++i )
						{
							if( eTNClan_BrahmaSoldier == pMob[i].m_byClan )
							{
								if( pMob[i].IsDead() ) continue;

								{
									char chBuf[1024] = { 0,0,0, };
									sprintf(chBuf, "\t[eTNAct_CountBrahmaMonster] h:%d, Trb:%d, pos(%d,%d) \r\n"
												, i, pMob[i].MOB.snTribe, pMob[i].TargetX, pMob[i].TargetY												
												);
									WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

								}
							}
						}
					}
				}
			}
			break;
		case eTNAct_CountVishnuMonster :
			{
				int iCount = 0;
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( eTNClan_VishnuSoldier == pMob[i].m_byClan )
					{
						if( pMob[i].IsDead() ) continue;
						++iCount;
						//if( 0 < pMob[i].MOB.nHP ) ++iCount;
					}
				}

				if( 0 < iCount )
				{
					iProceed = 0;

					if( 6 > iCount )
					{
						char chBuf[1024] = { 0,0,0, };
						sprintf(chBuf, "[eTNAct_CountVishnuMonster] %d월%d일%d시%d분%d초> \r\n"
									, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
									);
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

						for( int i = MAX_USER; i < MAX_MOB; ++i )
						{
							if( eTNClan_VishnuSoldier == pMob[i].m_byClan )
							{
								if( pMob[i].IsDead() ) continue;

								{
									char chBuf[1024] = { 0,0,0, };
									sprintf(chBuf, "\t[eTNAct_CountVishnuMonster] h:%d, Trb:%d, pos(%d,%d) \r\n"
												, i, pMob[i].MOB.snTribe, pMob[i].TargetX, pMob[i].TargetY												
												);
									WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

								}
							}
						}
					}
				}
			}
			break;
		case eTNAct_CountSivaMonster :
			{
				int iCount = 0;
				for( int i = MAX_USER; i < MAX_MOB; ++i )
				{
					if( eTNClan_SivaSoldier == pMob[i].m_byClan )
					{
						if( pMob[i].IsDead() ) continue;
						++iCount;
						//if( 0 < pMob[i].MOB.nHP ) ++iCount;
					}
				}

				if( 0 < iCount )
				{
					iProceed = 0;

					if( 6 > iCount )
					{
						char chBuf[1024] = { 0,0,0, };
						sprintf(chBuf, "[eTNAct_CountSivaMonster] %d월%d일%d시%d분%d초> \r\n"
									, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
									);
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

						for( int i = MAX_USER; i < MAX_MOB; ++i )
						{
							if( eTNClan_SivaSoldier == pMob[i].m_byClan )
							{
								if( pMob[i].IsDead() ) continue;

								{
									char chBuf[1024] = { 0,0,0, };
									sprintf(chBuf, "\t[eTNAct_CountSivaMonster] h:%d, Trb:%d, pos(%d,%d)\r\n"
												, i, pMob[i].MOB.snTribe, pMob[i].TargetX, pMob[i].TargetY											
												);
									WriteLog( chBuf, g_szrgLogFileName[eLogFileName_CountMonster] );

								}
							}
						}
					}
				}
			}
			break;
		case eTNAct_MoveTheGateOfDungeon :
			{
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[1024] = { 0,0,0, };
					sprintf(chBuf, "[eTNAct_MoveTheGateOfDungeon] %d월%d일%d시%d분%d초, 주신던젼 개폐\
								   브라흐마(%d,%d), 비슈누(%d,%d), 시바(%d,%d)\r\n"
								   , g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
								   , g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1]
								   , g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3]
								   , g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
								   );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
				}

				if( 100 < g_krgTaskList[iTaskID].irgParam[0] ) g_bIsKaliaOpend = true;
				else g_bIsKaliaOpend = false;

				Teleport( g_irgGateOfDungeon[0], g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1] ); // 브라흐마
				Teleport( g_irgGateOfDungeon[1], g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3] ); // 비슈누
				Teleport( g_irgGateOfDungeon[2], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] ); // 시바
			}
			break;
		case eTNAct_MoveTheSymbolAtByruCastle :// 비류성 내성 상징물 이동
			{
				if( eZone_Castle != g_iZoneID ) return eTNRes_Failed;
				Teleport( g_iSymbolAtByruCastle, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1] );
			}
			break;
		case eTNAct_CheckByruCastleMaster :// 비류성 성주인지 확인
			{
				if( eZone_Castle != g_iZoneID ) return eTNRes_Failed;
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle;
				//---------------------------------------------
				// 수성 길드 길마인지 확인해야 한다.
				//---------------------------------------------
				int iDefenseGuild = g_kSiege.get_OwnerGuild();
				int iGuildID = pMob[a_iUser].MOB.nGuildID;
	
				if( iDefenseGuild != iGuildID )
				{// 수성 아쉬람의 길드 마스터가 아닙니다.
					SendClientMessage( a_iUser, g_pMessageStringTable[_NotByruCastleMaster] );
					return eTNRes_Failed;
				}

				int iGuildIndex = pUser[a_iUser].nGuildIndex;
				CGuild kGuild;
				int iRes = ReadGuildFile( iGuildID, &kGuild );
				if( FALSE == iRes )
				{ // 길드가 부정확하다.
					SendClientMessage( a_iUser, g_pMessageStringTable[_Guild_Not_Fine_Guild] );
					return eTNRes_Failed;
				}

				if( strcmp( kGuild.szGuildMaster, pMob[a_iUser].MOB.szName) )
				{// 수성 아쉬람의 길드 마스터가 아닙니다.
					SendClientMessage( a_iUser, g_pMessageStringTable[_NotByruCastleMaster] );
					return eTNRes_Failed;
				}
			}
			break;
		case eTNAct_OnKilledLeftGeneral : // 북두좌성군 죽은 후 연출
			{
				int iStartX, iEndX, iStartY, iEndY;
				// StartXZ(66,76),endXZ(166,164)
				iStartX = 66;
				iEndX = 166;
				iStartY = 76;
				iEndY = 164;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] The Left-Side General is killed !\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
				}
				#endif    
				// StartXZ(658,959),endXZ(638,954))

				int iDestX, iDestY;
				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;

						iDestX = PlayDice( 638, 658 );
						iDestY = PlayDice( 954, 959 );
						Teleport( iMob, iDestX, iDestY );
					}
				}
			}
			break;
		case eTNAct_OnKilledRightGeneral : // 북두우성군 죽은 후 연출
			{
				int iStartX, iEndX, iStartY, iEndY;
				//StartXZ(856,68),endXZ(958,158)
				iStartX = 856;
				iEndX = 958;
				iStartY = 68;
				iEndY = 158;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] The Right-Side General is killed !\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
				}
				#endif    
				//StartXZ(658,959),endXZ(638,954))

				int iDestX, iDestY;
				for( int y = iStartY; y < iEndY; ++y )
				{
					for( int x = iStartX; x < iEndX; ++x )
					{
						int iMob = pMobGrid[y][x];
						if( 0 >= iMob || MAX_USER <= iMob ) continue;

						iDestX = PlayDice( 638, 658 );
						iDestY = PlayDice( 954, 959 );
						Teleport( iMob, iDestX, iDestY );
					}
				}
			}
			break;
		case eTNAct_KickOutOtherClanInMyStronghold :
			{

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\r\n\n[eTNAct_KickOutOtherClanInMyStronghold] %dMM%dDD %dHH%dMS%dSS >  Param:(%d,%d,%d) 0(%d,%d), 1(%d,%d), 2(%d,%d), 3(%d,%d) \r\n"
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
						, g_krgStronghold[eStronghold_Northwest].iOwner, g_krgStronghold[eStronghold_Northwest].iOwnerFriend
						, g_krgStronghold[eStronghold_Northeast].iOwner, g_krgStronghold[eStronghold_Northeast].iOwnerFriend
						, g_krgStronghold[eStronghold_Southwest].iOwner, g_krgStronghold[eStronghold_Southwest].iOwnerFriend
						, g_krgStronghold[eStronghold_Southeast].iOwner, g_krgStronghold[eStronghold_Southeast].iOwnerFriend
						);
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
				}
				#endif

				for( int iPC = 0; iPC < MAX_USER; ++iPC )
				{
					if( eTNClan_GM == pMob[iPC].m_byClan ) continue;
					if( eTNCls_NPC == pMob[iPC].MOB.byClass1 ) continue;	
					if( USER_PLAY != pUser[iPC].Mode ) continue;

					int iGuildID = pMob[iPC].MOB.nGuildID;

					//아누마을eZone_Shambala, 132,510
					HS2D_COORD kDest;
					kDest.x = 132;
					kDest.y = 510;

					int x = pMob[iPC].TargetX;
					int y = pMob[iPC].TargetY;

					#ifdef __TN_TOP_LOG__
					{
						char chBuf[256] = { 0,0,0, };
						sprintf(chBuf, "\t- PC(%s, H:%d), Guild:%d, Pos(%d,%d) \r\n"
							, pMob[iPC].MOB.szName, iPC
							, iGuildID, x, y
							);
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
					}
					#endif

					// stronghold 내에 위치하고 있다면, clan을 확인해서 타 guild이면, kick out~
					if( eTNCell_Shrine & g_krgCell[y][x].usProperty )
					{						
						if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x < 316) && (y < 707) )
							{
								if( g_krgStronghold[eStronghold_Northwest].iOwner != iGuildID && g_krgStronghold[eStronghold_Northwest].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									
									//pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x > 316) && (y < 707) )
							{
								if( g_krgStronghold[eStronghold_Northeast].iOwner != iGuildID && g_krgStronghold[eStronghold_Northeast].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									//pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x < 316) && (y > 707) )
							{
								if( g_krgStronghold[eStronghold_Southwest].iOwner != iGuildID && g_krgStronghold[eStronghold_Southwest].iOwnerFriend  != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									//pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x > 316) && (y > 707) )
							{
								if( g_krgStronghold[eStronghold_Southeast].iOwner != iGuildID && g_krgStronghold[eStronghold_Southeast].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] );
									//pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
					}
				}
			}
			break;
		case eTNAct_CheckElapsedTimeAboutStronghold :
			{
				iProceed = 0;
				int iLocation = g_krgTaskList[iTaskID].irgParam[0];
				if( 0 > iLocation || eStronghold_Southeast < iLocation ) break;
				CTime kNow( g_kSystemTime );
				//kNow.GetCurrentTime();
				CTimeSpan kElapsedTime = kNow - g_krgStronghold[iLocation].kTimeOccupied;

				if( /*7200*/30240 > kElapsedTime.GetTotalMinutes() ) iProceed = 1; // 경과시간이 3주가 넘지 않았다. 21일*24시간*60분					
			}
			break;
		case eTNAct_SwitchBattleForStronghold :
			{
				g_iBattleForStronghold = g_krgTaskList[iTaskID].irgParam[0];

				Msg_StrongHoldStatus sm; sm.wType = _Msg_StrongHoldStatus;
				sm.byMode = g_iBattleForStronghold;
				sm.byDummy = 0; sm.snDummy = 0;
				MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));

				if( 1 == g_iBattleForStronghold )			//	요새전 시작
				{

				}
				else if( 0 == g_iBattleForStronghold )		//	요새전 종료
				{

				}
			}
			break;
		case eTNAct_SetDuelFieldAtStronghold :
			{//345	285	736	677
				for( int y = 677; y < 736; ++y )
				{
					for( int x = 285; x < 345; ++x )
					{
						g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone;
						//if( 20 == g_krgCell[y][x].usEvent ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone;
						//else if( 21 == g_krgCell[y][x].usEvent ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_SealedZone;
					}
				}
			}
			break;
		case eTNAct_CloseDuelFieldAtStronghold :
			{
				for( int y = 677; y < 736; ++y )
				{
					for( int x = 285; x < 345; ++x )
					{
						unsigned short usNewProperty = (unsigned short)eTNCell_DuelZone;
						if( usNewProperty & g_krgCell[y][x].usProperty  )							
							g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty; // XOR로 제거
						/*
						if( 20 == g_krgCell[y][x].usEvent )
						{
							unsigned short usNewProperty = (unsigned short)eTNCell_DuelZone;
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty; // XOR로 제거
						}
						else if( 21 == g_krgCell[y][x].usEvent )
						{
							unsigned short usNewProperty = (unsigned short)eTNCell_SealedZone;
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty; // XOR로 제거
						}
						*/
					}
				}
			}
			break;
		case eTNAct_RegisterPCtoArenaEntry :
			{
				iProceed = 0;
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) break; //return eTNRes_EvntInvalidUserHandle;
				if( eTNClan_GM == pMob[a_iUser].m_byClan ) break;

				if( g_kArena.IsFull() )
				{
					SendClientMessage( a_iUser, g_pMessageStringTable[_ArenaEntryIsFull] );
					break; //return eTNRes_ArenaEntryIsFull;
				}

				//g_kArena.AddEntrant( a_iUser );
				/*
				if( true == pMob[a_iUser].m_bIsInArenaEntry ) break; //return eTNRes_AlreadyRegisteredInArenaEntry;
				g_irgArenaEntry[g_iArenaEntryCount] = a_iUser;
				++g_iArenaEntryCount; // 참가자수 1 증가
				pMob[a_iUser].m_bIsInArenaEntry = true;
				*/

				iProceed = 1;
			}
			break;

		case eTNAct_StartSuvivalFight :
			{
				g_kArena.StartSurvival();
			}
			break;
		case eTNAct_CheckWinner :
			{
				if( !g_kArena.IsProgressed() ) break;

				int iRes = g_kArena.CheckWinner();
				if( !iRes ) // 아레나 서바이벌 승자가 결정되었다. 종료 이벤트를 trigger
				{
					TriggerEvent(0, 68, 0, 0, 0 ); // 아레나 서바이벌 이벤트 종료
				}
			}
			break;

		case eTNAct_PostThePrize :
			{
				if( !g_kArena.IsProgressed() ) break;

				g_kArena.Award();
				g_dwArenaMoney = 0;			

				char szMsg[1024] = { 0,0,0, };		
				char szWinners[512] = { 0,0,0, };
				g_kArena.OutputWinners( szWinners );
				sprintf( szMsg, g_pMessageStringTable[_PostThePrize], szWinners, g_kArena.get_GoldToAward() ); // g_dwArenaMoney, 임시로 1억을 입력했다. 나중에 변수로 변경을 해줘야 한다.

				{
					char chBuf[2048] = { 0,0,0, };
					sprintf(chBuf, "[eTNAct_PostThePrize] %d월%d일%d시%d분%d초, %s\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, szMsg );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
				}

				PostMessageToWorld( szMsg );
			}
			break;
		case eTNAct_KickOutLosser :
			{ // 공성전에서 진 PC들을 튕긴다.
				int iWinner = g_kSiege.get_Winner();

				for( int i = 1; i < MAX_USER; ++i )
				{
					if( USER_PLAY != pUser[i].Mode ) continue;
					if( eTNClan_GM == pMob[i].m_byClan ) continue; //  GM인 경우는 이동시키지 않는다
					if( iWinner == pMob[i].m_byClan ) continue;

					/*losser 이라면*/
					//ReturnPCToSaveZone( i );

					 //x: 114~138  y: 124:~192
					int iOrder = i % 3; // 0,1,2
					if( 0 == iOrder) 
					{
						Teleport( i, 126, 138 );
					}
					else if( 1 == iOrder )
					{
						Teleport( i, 126, 158 );
					}
					else
					{
						Teleport( i, 126, 177 );
					}

					/*

					bool bFound = false;
					HS2D_COORD kPos;
					for( int y = 124; y < 192; ++y )
					{
						bFound = false;
						for( int x = 114; x < 138; ++x )
						{
							if( 0 != pMobGrid[y][x] ) continue; // mob이 그 자리를 차지하고 있으면, ...
							if( pMob[i].m_iBlockedCell & g_krgCell[y][x].usProperty ) continue;
							// x, y가 빈자리이라면, ...						
							bFound = true;
							kPos.x = x;
							kPos.y = y;
							break;
						}
						if( bFound ) break;
					}

					Teleport( i, kPos.x, kPos.y );
					*/
				}
			}
			break;
		case eTNAct_JudgeTheSiege :
			{ // symbol 의 소유주를 찾아서 점수 계산
				g_kSiege.JudgeSiege();

				//	점수 계산후 공성의 소유주 변화를 전존에 알린다.
				TNCastle kOwner;
				g_kSiege.get_Owner( &kOwner);
				Msg_CastleUpdate sm; ZeroMemory(&sm, sizeof(sm));
				sm.wType = _Msg_CastleUpdate;
				sm.iCastleOwner = kOwner.kGuild.iID;
				MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
			}
			break;
		case eTNAct_PopSymbolForSiege :
			{
				if( 0 >= a_iUser || MAX_MOB <= a_iUser ) continue;
				if( MAX_USER <= a_iUser )
				{
					
					//if( (eTNCls2_Retainer == pMob[a_iUser].MOB.byClass2) || (eTNCls2_Familiar == pMob[a_iUser].MOB.byClass2) || (eTNCls_Fellow == pMob[a_iUser].MOB.byClass1) ) 
					if( eTNAIO_HaveMaster & pMob[a_iUser].m_iAIOption )
					{
						a_iUser = pMob[a_iUser].Leader;
					}
				}

				g_kSiege.CaptureSymbol( pMob[a_iUser].m_byClan, a_iNPC/*symbol*/, a_iUser/*capturer*/ );

				// symbol이 죽은 후에 바로(즉시) pop 된다면 약간 어색할 듯하다. 그래서 delay가 있어야 한다. 따라서 예약하기 위한 방법이 제공되어야 한다.
				// 35(=7*5) 개의 event/task
				// 35개의 event를 1분 후에 예약하기 위한 event/task
				//int TriggerEvent( int a_iUser, int a_iEventID, int a_iX, int a_iY, int a_iNPC, int a_iCaller )
				// a_iUser로 symbol의 owner를 알아낼 수 있다. a_iX, a_iY를 통해서 pop위치를 알아낼 수 있다.

			}
			break;
		case eTNAct_RecoverClanToOriginal :
			{ // call a global routine
				ChangeClan( -1, -1 );
			}
			break;
		case eTNAct_ChangeClanForSiege :
			{
				if( !g_kSiege.get_Started() ) break; // 공성전이 아니라면, ...

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[eTNAct_ChangeClanForSiege] %dYY%dMM%dDD %2dHH%2dMI%2dSS> \r\n"
						, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						); 
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif


				for( int i = 1; i < MAX_USER; ++i )
				{
					if( eTNClan_GM == pMob[i].m_byClan ) continue;
					//if( eTNClan_CastleOwner <= pMob[i].m_byClan && eTNClan_Siege4 >= pMob[i].m_byClan ) continue;
					if( USER_PLAY != pUser[i].Mode ) continue;

					byte byOld = pMob[i].m_byClan;

					int iFlag = g_kSiege.SearchEntry( pMob[i].MOB.nGuildID );
					if( -1 == iFlag ) pMob[i].m_byClan = eTNClan_Siege4; // 무소속
					else pMob[i].m_byClan = iFlag;

					MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
					kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
					kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);
					kZoneSettingMsg.snSiege = 1; //g_kSiege.get_Started(); 공성종료
					pUser[i].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );

					S_SCP_INIT_OTHER_MOB sm;
					GetCreateMob( i, &sm );
					GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, i);


					MSG_CHANGE_CLAN kMsg;
					kMsg.wType = MSG_CHANGE_CLAN_ID;
					kMsg.wPDULength = sizeof(MSG_CHANGE_CLAN)-sizeof(HEADER);
					kMsg.snKeyID = i;
					kMsg.byClan = pMob[i].m_byClan;
					pUser[i].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) );

					pUser[i].cSock.SendMessage();

					#ifdef __TN_TOP_LOG__
					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "[eTNAct_ChangeClanForSiege] PC(%d, Name:%s, Guild:%d), clan(now:%d, old:%d) \r\n"
							,i , pMob[i].MOB.szName, pMob[i].MOB.nGuildID
							, pMob[i].m_byClan, byOld
							); 
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
					}
					#endif


/*
					S_SCP_RESP_CHAR_INIT kMsg;
					kMsg.wType = SCP_RESP_CHAR_INIT;
					kMsg.wPDULength = sizeof(S_SCP_RESP_CHAR_INIT)-sizeof(HEADER);

					kMsg.byResult = 1;
					kMsg.dwGameTime = time(NULL);
					kMsg.dwKeyID = i;
					kMsg.snX = pMob[i].TargetX;
					kMsg.snZ = pMob[i].TargetY;
					memcpy( kMsg.bySkill, pMob[i].MOB.bySkill, sizeof(BYTE)*MAX_SKILL );
					memcpy( kMsg.byQuest, pMob[i].MOB.byQuest, sizeof(BYTE)*MAX_EVENT_FLAG );
					memcpy( kMsg.Inven, pMob[i].MOB.Inven, sizeof(STRUCT_ITEM)*MAX_INVEN );
					memcpy( kMsg.Equip, pMob[i].MOB.Equip, sizeof(STRUCT_ITEM)*MAX_EQUIP );
					memcpy( kMsg.Cargo, pUser[i].Cargo, sizeof(STRUCT_ITEM)*MAX_CARGO );
					memcpy( kMsg.dwTimeStamp, pUser[i].m_time, sizeof(kMsg.dwTimeStamp));
					kMsg.nCargoMoney = pUser[i].Coin;
					kMsg.nGuildID = pMob[i].MOB.nGuildID;
					kMsg.byClan = pMob[i].m_byClan;
					kMsg.dwEvent = pUser[i].m_dwEvent;

					pUser[i].cSock.SendOneMessage((char*)&kMsg,sizeof(S_SCP_RESP_CHAR_INIT));

					S_SCP_INIT_OTHER_MOB sm;
					GetCreateMob( i, &sm );
					GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
*/
				}
			}
			break;
		case eTNAct_SwitchExpireOfTheTermForSiege :
			{
				g_kSiege.set_ExpiryOftheTerm( g_krgTaskList[iTaskID].irgParam[0] ); // 1이면 기간만료(공성신청불가), 0이면 기간중(공성신청가능)
				if( 0 < g_krgTaskList[iTaskID].irgParam[0] ) // 공성신청 불가, 공성전 구성표 고정됨
				{
					char szFileName[64] = { 0,0,0, };
					sprintf( szFileName, ".\\Event\\SiegeEntry_%dYY%dMM%dDD %2dHH%2dMI%2dSS.txt", g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					g_kSiege.SaveData( szFileName );
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\r\n[Switch 공성신청기간] [%dYY%dMM%dDD %2dHH%2dMI%2dSS] > state:%d(0:공성신청가능, 1:공성신청불가)\r\n"
						, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, g_krgTaskList[iTaskID].irgParam[0]
						); 
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif
			}
			break;
		case eTNAct_SwitchSiege :
			{ // call a global routine
				g_kSiege.set_Started( g_krgTaskList[iTaskID].irgParam[0] ); // 0이면 공성종료, 1이면 공성시작

				if( 0 >= g_krgTaskList[iTaskID].irgParam[0] ) // off
				{
					g_kSiege.DestroySymbols();
					ChangeClan( -1, -1 );

					for( int i = 1; i < MAX_USER; ++i )
					{
						if( USER_PLAY != pUser[i].Mode ) continue;

						MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
						kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
						kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);

						kZoneSettingMsg.snSiege = 0; //g_kSiege.get_Started(); 공성종료
						pUser[i].cSock.SendOneMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );
					}
				}
				else // turn on
				{
					g_kSiege.InstallSymbols();
					g_kSiege.SaveData( ".\\Event\\[Bak]Castle.txt" );
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\r\n[Start/End the siege] [%dYY%dMM%dDD %2dHH%2dMI%2dSS] > state:%d(0:공성종료, 1:공성시작)\r\n"
						, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, g_krgTaskList[iTaskID].irgParam[0]
						); 
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
				}
				#endif
			}
			break;
		case eTNAct_FixTheDateOfTheSiege :
			{
				int iSelected = g_kSiege.get_DateToHold();
				//eDate_NotSelected = 0, eDate_Friday8HH, eDate_Friday10HH, eDate_Saturday8HH, eDate_Saturday10HH, eDate_Sunday8HH,

				if( TNSiege::eDate_Friday8HH == iSelected )
				{
					g_krgEventList[100].iDuration = eEvntSwitch_On;
				}
				else if( TNSiege::eDate_Friday10HH == iSelected )
				{
					g_krgEventList[101].iDuration = eEvntSwitch_On;
				}
				else if( TNSiege::eDate_Saturday8HH == iSelected )
				{
					g_krgEventList[102].iDuration = eEvntSwitch_On;
				}
				else if( TNSiege::eDate_Sunday8HH == iSelected )
				{
					g_krgEventList[104].iDuration = eEvntSwitch_On;
				}
				else
				{
					iSelected = TNSiege::eDate_Saturday10HH;
					g_krgEventList[103].iDuration = eEvntSwitch_On;
				}

				g_kSiege.SelectDate( iSelected );
			}
			break;
		case eTNAct_PostTheResultOfTheSiege :
			{

			}
			break;
		case eTNAct_PostTheScheduleForTheSiege : // schedule에 넣어 정기적인 공지를 한다. 화요일 날짜 결정 마감이므로 수,목, 금 정도에 하면 될 듯
			{// 금주의 공성전은 토요일 저녁 9시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
				int iSelected = g_kSiege.get_DateToHold();
				if( 0 == iSelected ) break;

				int iMessageID = _PostTheDateForSiege1;
				if( 2 == iSelected ) iMessageID = _PostTheDateForSiege2;
				else if( 3 == iSelected ) iMessageID = _PostTheDateForSiege3;
				else if( 4 == iSelected ) iMessageID = _PostTheDateForSiege4;
				else if( 5 == iSelected ) iMessageID = _PostTheDateForSiege5;
				else iMessageID = _PostTheDateForSiege1;

				PostMessageToWorld( g_pMessageStringTable[iMessageID], eTNClr_White, eTNClr_BG, iMessageID );
			}
			break;

		case eTNAct_QuestEvent :
			{
				int iTribe = pMob[a_iNPC].MOB.snTribe;
				BOOL bRes = QUEST_OnEvent( a_iUser, iTribe, iTribe );
				if( FALSE == bRes )	return eTNRes_Failed;
			}
			break;
		} // end of switch

		if( eEvntPrcdType_Sequential == g_krgEventList[a_iEventID].sProceedType ) iProceed = 1;
	} // end of for statement

	if( iProceed ) g_krgEventList[a_iEventID].uiAvailableTime = g_krgEventList[a_iEventID].uiCoolDownTime + CurrentTime;

	return eTNRes_Succeeded;
}



// 이 함수는 확인의 차원에서 사용한다. 즉 다른 처리들을 다 수행하는 혹시나 문제거리가 있을지 모르므로 재확인성으로 작성되었다.
void RemoveKalaCoreInInventory( int a_iUser )
{
	if( 0 >= a_iUser || MAX_USER <= a_iUser ) return;

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	for( int i = 0; i < MAX_INVEN; ++i )
	{
		int iID = pItemData[pMob[a_iUser].MOB.Inven[i].snIndex].sID;
		if( (eKalaCore_Brahma == iID) || (eKalaCore_Vishnu == iID) || (eKalaCore_Siva == iID) )
		{
			{
				char chBuf[512] = { 0,0,0, };
				sprintf( chBuf, "[%dmm%ddd %dhh%dmi%dss] RemoveKalaCoreInInventory() > Remove a kala-core(%d) in %s's inventory> - \r\n"
					, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
					, iID, pMob[a_iUser].MOB.szName 
					);
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
			}
			ZeroMemory(&pMob[a_iUser].MOB.Inven[i], sizeof(STRUCT_ITEM));
		}
	}
}



// TNKalaSystem class의 도입으로 인하여, kala-core 개수가 맞지 않을 때에는 이를 보정해주는 방법이 변화되어야 한다.
// TNKalaSystem의 총 9개의 slot 정보를 이용해서 각각의 정보에 해당하는 곳에 kala가 있는지 검사를 한다. 만약 틀리다면, slot 정보를 초기화하고
// 신규 kala-core를 맵 중앙에 생성시켜서 전체 개수를 맞춰준다.
// 
void CheckKalaSystem()
{
	g_kKalaSystem.DropKalaCoreInPC();
	g_kKalaSystem.CheckCountNRecovery();
	g_kKalaSystem.Print();

	WriteLog( "\r\n", g_szrgLogFileName[eLogFileName_KalaSystem] );
}



int SummonKala( int a_iTribe, int a_iClan, int x, int y, int& a_iHandle )
{
	if( 0 == x || 0 == y ) return 100;

	int iMob = 0;
	int iStart = 0;
	if( eKala_Brahma == a_iTribe ) iStart = 1000;
	else if( eKala_Vishnu == a_iTribe ) iStart = 1003;
	else if( eKala_Siva == a_iTribe ) iStart = 1006;

	for( int i = 0; i < 3; ++i )
	{
		if( MOB_EMPTY == pMob[iStart].Mode )
		{
			iMob = iStart;
			break;
		}
		++iStart;
	}

	if( 1000 > iMob || 1008 < iMob ) return eTNRes_Failed;

	int iMonsterDataIndex = a_iTribe - 2000; // the index of monster data
	pMob[iMob].MOB = pMonsterData[iMonsterDataIndex];
	pMob[iMob].MOB.nTP = iMonsterDataIndex;
	pMob[iMob].Init( iMob ); // 초기화

	if( 0 < pMobGrid[y][x] && MAX_MOB > pMobGrid[y][x] ) // 다른 mob이 위치하고 있다.
	{		
		if( true ) // dest 자리를 검사하고, 다른 mob이 있으면, 처리(제거)한 후에, 꼭 그 위치에 위치를 시킨다.
		{
			int iOccupiedMob = pMobGrid[y][x];
			int iNewX, iNewY;
			iNewX = x; iNewY = y;
			int tret = GetEmptyMobGrid( iOccupiedMob, &iNewX, &iNewY );
			if( FALSE == tret )
			{ // user이면 kick out 시켜주고, monster이면 단순히 죽인다.
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user이면
				{
					char temp[256] = {0,};
					sprintf(temp, "clo SummonKala char:%s", pMob[iOccupiedMob].MOB.szName);
					Log(temp, pUser[iOccupiedMob].AccountName,pUser[iOccupiedMob].IP);
					SendClientMessage( iOccupiedMob, g_pMessageStringTable[_Bad_Network_Packets] );
					CloseUser( iOccupiedMob );
				}
				else 
				{
					KillMonster( iOccupiedMob );
					/*
					pMob[iOccupiedMob].MOB.nHP = 0; 
					pMob[iOccupiedMob].CurrentTarget = 0;
					pMob[iOccupiedMob].m_eFSM = eTNFsm_Dead;
					*/
				}
			}
			else // 기존의 위치를 바꾼다.
			{			
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user이면
				{
					MSG_Action sm;	GetAction( iOccupiedMob, iNewX, iNewY ,&sm );
					pUser[iOccupiedMob].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );					
				}
				else
				{
					//pMobGrid[iNewY][iNewX] = iOccupiedMob;
				}

				pMobGrid[iNewY][iNewX] = iOccupiedMob;	
				//if(iOccupiedMob==0) MessageBox(NULL, "error_SUMMONKALA", "error", MB_OK);
			}

			pMobGrid[y][x] = iMob;
			//if(iMob==0) MessageBox(NULL, "error_SUMMONKALA2", "error", MB_OK);
		}
		else
		{
			int tret = GetEmptyMobGrid( iMob, &x, &y, pMob[iMob].m_iBlockedCell );
			if( FALSE == tret ) return 110; // summon이 fail나도 상관이 없는 것일 경우, ...
		}
	}

	pMob[iMob].LastX = pMob[iMob].TargetX = pMob[iMob].SegmentX = x;
	pMob[iMob].LastY = pMob[iMob].TargetY = pMob[iMob].SegmentY = y;

	// default settings
	for( int i = 0; i < MAX_SEGMENT; ++i )
	{
		pMob[iMob].SegmentListX[i] = x;
		pMob[iMob].SegmentListY[i] = y;
		pMob[iMob].SegmentWait[i] = rand() % 8;
		pMob[iMob].SegmentRange[i] = rand() % 20;
	}
	pMob[iMob].RouteType = eTNRout_MoveNRoam;
	pMob[iMob].Formation = 0;

	pMob[iMob].MOB.byClass1 = (byte)eTNCls_Event; // 소환되는 NPC의 직업
	pMob[iMob].MOB.byClass2 = 0; // 소환되는 NPC의 상세 직업            
	pMob[iMob].m_byClan = pMob[iMob].MOB.byTrimuriti = (byte)a_iClan;

	//pMob[iMob].m_uiActionLock = 0;
	//pMob[iMob].m_iDirection = a_iDirection;
	                    
	a_iHandle = iMob;

	S_SCP_INIT_OTHER_MOB sm;
	GetCreateMob( iMob, &sm );
	sm.byPopType = eTNPrdt_PopRaise; // 소환될 때의 연출 번호
	pMobGrid[y][x] = iMob;
	GridMulticast( x, y, (MSG_STANDARD*)&sm, 0);
	//if(iMob==0) MessageBox(NULL, "error__SUMMONKALA3", "error", MB_OK);

	return eTNRes_Succeeded;
}



void VerifyKalaOnAltar()
{
	/*
	for( int i = 0; i < eKalaAltar_MaxCount; ++i )
	{
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i );
		if( (1008 < iKalaMonster) && (0 != g_irgKalaAltar[i]) )
		{
			if( MAX_MOB > g_irgKalaAltar[i] )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[ERROR] Altar No.%d : Mob(%d, %d)\r\n", i, g_irgKalaAltar[i], pMob[g_irgKalaAltar[i]].MOB.snTribe	);
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );

				pMob[g_irgKalaAltar[i]].MOB.nHP = 0; 
				pMob[g_irgKalaAltar[i]].CurrentTarget = 0;
				pMob[g_irgKalaAltar[i]].m_eFSM = eTNFsm_Dead;
			}

			g_irgKalaAltar[i] = 0;
		}
	}
	*/
}



// 총 9마리의 kala 상태를 출력한다.( 1000~1008 )
// summon을 하려고 했다는 것은 altar에 꼿으려는 것이므로 모든 altar의 상태를 출력한다.
void LogKalaSystemInfo()
{
	/*
	char chBuf[512] = { 0,0,0, };
	sprintf(chBuf, "Kala> Brahma(%d,%d,%d), Vishnu(%d,%d,%d), Siva(%d,%d,%d)\
				   \tAltar> (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\
				   \r\n\n"
		, pMob[1000].m_eFSM, pMob[1001].m_eFSM, pMob[1002].m_eFSM
		, pMob[1003].m_eFSM, pMob[1004].m_eFSM, pMob[1005].m_eFSM
		, pMob[1006].m_eFSM, pMob[1007].m_eFSM, pMob[1008].m_eFSM
		, g_irgKalaAltar[0], g_irgKalaAltar[1], g_irgKalaAltar[2], g_irgKalaAltar[3], g_irgKalaAltar[4]
		, g_irgKalaAltar[5], g_irgKalaAltar[6], g_irgKalaAltar[7], g_irgKalaAltar[8], g_irgKalaAltar[9]
		, g_irgKalaAltar[10], g_irgKalaAltar[11], g_irgKalaAltar[12], g_irgKalaAltar[13], g_irgKalaAltar[14]
		);
	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
	*/
}

void StartChallenge(int conn)
{
	int nTarget = pUser[conn].m_nChallenger;

	Msg_Challenger sm; sm.wType = _Msg_Challenger;
	sm.byMode = eChallenge_WAIT;

	//	나의 결투모드를 세팅한다.
	pUser[conn].m_nChallengeMode = eChallenge_Combat;
	pUser[conn].m_nChallenger = nTarget;
	strncpy(pUser[conn].m_pChallenger, pMob[nTarget].MOB.szName, SZNAME_LENGTH);

	//	상대의 결투모드를 세팅한다.
	pUser[nTarget].m_nChallengeMode = eChallenge_Combat;
	pUser[nTarget].m_nChallenger = conn;
	strncpy(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH);

	//	쌍방에게 결투성립을 알린다.
	sm.nID = nTarget;
	sm.byMode = eChallenge_Combat;
	strncpy(sm.szCharName, pUser[conn].m_pChallenger, SZNAME_LENGTH);
	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));

	sm.nID = conn;
	strncpy(sm.szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	pUser[nTarget].cSock.SendOneMessage((char*)&sm,sizeof(sm));
}

void RemoveChallenge(int conn, BYTE byReason)
{
	if(pUser[conn].m_nChallengeMode==eChallenge_WAIT) return;

	int nTarget = pUser[conn].m_nChallenger;

	char pData[128] = {0,};
	sprintf(pData, "SERVER SEND TO:%s _Msg_Challenger CANCELED WITH charllenger:%s mode:%d reason:%d", 
		pMob[conn].MOB.szName, pMob[nTarget].MOB.szName, eChallenge_Response, byReason);
	TimeWriteLog(pData, "Challenger_log.txt");

	//	나의 결투모드를 세팅한다.
	pUser[conn].m_nChallengeMode = eChallenge_WAIT;
	pUser[conn].m_nChallenger = 0;
	ZeroMemory(pUser[conn].m_pChallenger, SZNAME_LENGTH);

	Msg_Challenger sm; sm.wType = _Msg_Challenger;
	sm.byMode = eChallenge_Response;
	sm.byReason = byReason;
	sm.nID = nTarget;
	strncpy(sm.szCharName, pMob[nTarget].MOB.szName, SZNAME_LENGTH);
	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	pMob[conn].Init( conn );
	////pMob[conn].ClearAffection();
	pMob[conn].ProcessContinuousEffect();

	sprintf(pData, "SERVER SEND TO:%s _Msg_Challenger CANCELED WITH charllenger:%s mode:%d reason:%d", 
		pMob[nTarget].MOB.szName, pMob[conn].MOB.szName, eChallenge_Response, byReason);
	TimeWriteLog(pData, "Challenger_log.txt");

	//	상대의 결투모드를 세팅한다.
	pUser[nTarget].m_nChallengeMode = eChallenge_WAIT;
	pUser[nTarget].m_nChallenger = 0;
	ZeroMemory(pUser[nTarget].m_pChallenger, SZNAME_LENGTH);

	sm.nID = conn;
	strncpy(sm.szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	pUser[nTarget].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	pMob[nTarget].Init( nTarget );
	//pMob[nTarget].ClearAffection();
	pMob[nTarget].ProcessContinuousEffect();
}


// 무조건 저장만 한다.
// symbol이 destroy되면 WriteSymbolDestroyer(), CompareSymbolDestroyer() 두개의 함수를 무조건 call 하도록 한다.
void WriteSymbolDestroyer( int a_iIndex, int a_iSymbol, int a_iGuildID ) 
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return;
	if( 0 > a_iSymbol || 1 < a_iSymbol ) return;
	if( 0 >= a_iGuildID ) return;

	g_krgStronghold[a_iIndex].irgDestroyer[a_iSymbol] = a_iGuildID;
}


// 무조건 비교만 한다.
int CompareSymbolDestroyers( int a_iIndex )
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return eTNRes_Failed;
	if( 0 >= g_krgStronghold[a_iIndex].irgDestroyer[0] ) return eTNRes_Failed;
	if( 0 >= g_krgStronghold[a_iIndex].irgDestroyer[1] ) return eTNRes_Failed;
	if( g_krgStronghold[a_iIndex].irgDestroyer[0] != g_krgStronghold[a_iIndex].irgDestroyer[1] ) return eTNRes_Failed;

	return eTNRes_Succeeded;
}


void CheckStrongholdStatus( int a_iIndex )
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return;

	if( CompareSymbolDestroyers( a_iIndex ) ) // 두개의 symbol을 destroy한 guild가 동일할 경우
	{
		// 0. 주인 변경 event 하나만을 trigger해준다.

		// 1. 요새 소속의 모든 guard들을 죽인다.
		// 2. 점령되었다는 전체 메시지를 띄운다.
		// 3. 요새 소속의 모든 guard들을 새롭게 배치한다.


	}
	else // 다를 경우
	{
		// 1. 모든 것을 초기화한다.

	}
}


// stronghold.txt라는 파일을 만들어 앞쪽에는 basic data(/S(tronghold) [ID] [Owner])를 위치시키고
// 뒤쪽에는 가변길이로 guard 배치데이터(/M(onster) [ID] [x] [y] [clan])를 line 단위로 넣어놓는다.
// scheduler에 1시간에 n회씩 저장되게 해놓는다. 저장될 때에는 기존 파일을 지우고 새로운 파일을 만들도록 한다.
// server start up시에 stronghold file을 로드해서 set하게 한다.
// 요새전 zone을 서비스하는 최초에도 "Stronghold.txt" data file이 존재해야한다. 여기에는 stronghold 기본정도 4개만 들어가 있다. 모두 무소유
int LoadStrongholdData()
{
	if( eZone_Stronghold != g_iZoneID ) return eTNRes_Failed;

	char szData[64] = { 0,0,0, };
	char szCommand[32] = { 0,0,0, };
    char szArgument1[32] = { 0,0,0, };
    char szArgument2[32] = { 0,0,0, };
	char szArgument3[32] = { 0,0,0, };
	char szArgument4[32] = { 0,0,0, };
	char szArgument5[32] = { 0,0,0, };
	char szArgument6[32] = { 0,0,0, };
	char szArgument7[32] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0;
	
	FILE* fin;
	fin = fopen( ".\\Data\\Stronghold.txt", "rt" );
	if( NULL == fin ) 
	{ 
		MessageBox( hWndMain, "Not found Stronghold.txt in data folder.", "Failed to initialize data about the stronghold.", NULL ); 
		return eTNRes_Failed; 
	}

	//SYSTEMTIME st;
	//GetLocalTime( &st );
	int iYear, iMonth, iDay, iHour, iMinute;
	bool bDateTimePatched = true;

	while( true )
	{
		char* ret = fgets( (char*)szData, 64, fin );
		if( NULL == ret ) break;

		iYear = iMonth = iDay = iHour = iMinute = 0;
		sscanf( szData, "%s %s %s %s %s %s %s %s", szCommand, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5, szArgument6, szArgument7 );
		iArgument1 = atoi( szArgument1 ); // order #
		iArgument2 = atoi( szArgument2 ); // owner(guild ID)
		iYear = atoi( szArgument3 ); // date occupied
		iMonth = atoi( szArgument4 );
		iDay = atoi( szArgument5 );
		iHour = atoi( szArgument6 );
		iMinute = atoi( szArgument7 );
	
		switch( szData[1] )
		{
		case 'M' :
			{
				pMob[1000].Summon( iArgument1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, iArgument4, 0, iArgument2, iArgument3, 0, false, 0, 0, 70 );
			}
			break;
		case 'S' :
			{
				int iIndex = iArgument1 % 4; // 0,1,2,3
				g_krgStronghold[iIndex].iID = iArgument1;
				g_krgStronghold[iIndex].iOwner = iArgument2;

				if( (0 == iYear) && (0 == iMonth) && (0 == iDay) )
				{
					bDateTimePatched = false;
					CTime kTime( g_kSystemTime );
					g_krgStronghold[iIndex].kTimeOccupied = kTime;
				}
				else
				{
					CTime kTime( iYear, iMonth, iDay, iHour, iMinute, 0 );
					g_krgStronghold[iIndex].kTimeOccupied = kTime;
				}

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\r\n\r\n[LoadStrongholdData] %dyy%dmm%ddd %dhh%dms%dss > %d stronghold is occupied by a guild(%d) in %d-%d-%d-%d-%d\r\n"
						, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						, iArgument1, iArgument2
						, iYear, iMonth, iDay, iHour, iMinute
						); 
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
				}

				CGuild guild;
				ReadGuildFile(g_krgStronghold[iIndex].iOwner, &guild);
				strncpy(g_krgStronghold[iIndex].szGuildName, guild.GUILD.GuildName, SZGUILD_LENGTH);
				g_krgStronghold[iIndex].iOwnerFriend = GetGuildID(guild.GUILD.AlliedGuildName1);
				g_krgStronghold[iIndex].dwMark = guild.GUILD.Mark;
			}
			break;
		}
	}

	fclose( fin );
	//CloseHandle( hFile );

	if( false == bDateTimePatched ) SaveStrongholdData();

	bool bRet=true; 
	DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNW, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );	
	g_stPosStronghold[eStronghold_Northwest].x = snStartX;
	g_stPosStronghold[eStronghold_Northwest].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );	
	g_stPosStronghold[eStronghold_Northeast].x = snStartX;
	g_stPosStronghold[eStronghold_Northeast].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );	
	g_stPosStronghold[eStronghold_Southwest].x = snStartX;
	g_stPosStronghold[eStronghold_Southwest].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );	
	g_stPosStronghold[eStronghold_Southeast].x = snStartX;
	g_stPosStronghold[eStronghold_Southeast].y = snStartZ;

	if(!bRet)
	{
		MessageBox( hWndMain, "Can't find Stronghold Portal Data in TantraParam.", "Failed to initialize data about the stronghold.", NULL ); 
		return eTNRes_Failed; 
	}

	return eTNRes_Succeeded;
}


int SaveStrongholdData()
{
	HANDLE hFile;
	hFile = CreateFile( ".\\Data\\Stronghold.txt",					  // file name
                                GENERIC_WRITE,   // open for writing 
                                FILE_SHARE_WRITE,             // do not share 
                                NULL,                         // no security 
                                CREATE_ALWAYS,                  // open or create 
                                FILE_ATTRIBUTE_NORMAL,        // normal file 
                                NULL );

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return eTNRes_Failed;
	}


	DWORD dwRetWrite = 0;
	int nBufLength = 0;	
	char szData[64] = { 0,0,0, };

	// stronghold 정보 저장
	for( int iStronghold = 0; iStronghold < eStronghold_MaxCount; ++iStronghold )
	{
		memset( szData, 0, sizeof(szData) );
		sprintf( szData, "/S %d %d %d %d %d %d %d\r\n"
			, g_krgStronghold[iStronghold].iID, g_krgStronghold[iStronghold].iOwner
			, g_krgStronghold[iStronghold].kTimeOccupied.GetYear(), g_krgStronghold[iStronghold].kTimeOccupied.GetMonth()
			, g_krgStronghold[iStronghold].kTimeOccupied.GetDay(), g_krgStronghold[iStronghold].kTimeOccupied.GetHour()
			, g_krgStronghold[iStronghold].kTimeOccupied.GetMinute()
			);
		nBufLength = strlen( szData );
		WriteFile( hFile, szData, nBufLength, &dwRetWrite, NULL );
	}

	CloseHandle( hFile );

	return eTNRes_Succeeded;
}


// 유저가 a_iStronghold의 주인이라면, a_iClan값으로 set해준다.
void RefreshClan( int a_iStronghold, int a_iClan, int a_iClear )
{
	if(a_iStronghold<0 || a_iStronghold>=eStronghold_MaxCount) return;

	for( int i = 1; i < MAX_USER; ++i )
	{
		if( 1 == a_iClear )
		{// 원래의 주신으로 돌린다.
			a_iClan = pMob[i].MOB.byTrimuriti;
			//pMob[i].m_byClan = pMob[i].MOB.byTrimuriti;
		}

		if( pMob[i].MOB.nGuildID == g_krgStronghold[a_iStronghold].iOwner ) 
		{	pMob[i].m_byClan = (byte)a_iClan; 
			continue;
		}
		else if( pMob[i].MOB.nGuildID == g_krgStronghold[a_iStronghold].iOwnerFriend ) 
		{	pMob[i].m_byClan = (byte)a_iClan; 
			continue;
		}
		if(pMob[i].m_byClan == (byte)a_iClan) 
			pMob[i].m_byClan = pMob[i].MOB.byTrimuriti;
	}
}


void ChangeClan( int a_iWho, int a_iClan )
{
	for( int i = 1; i < MAX_USER; ++i )
	{
		if( USER_PLAY != pUser[i].Mode ) continue;

		byte byOld = pMob[i].m_byClan;
		if( -1 == a_iWho ) // zone에 접속을 해 있는 모든 pc
		{
			if( -1 == a_iClan ) pMob[i].m_byClan = pMob[i].MOB.byTrimuriti;
			else pMob[i].m_byClan = a_iClan;
		}
		else if( pMob[i].m_byClan == a_iWho )
		{
			if( -1 == a_iClan ) pMob[i].m_byClan = pMob[i].MOB.byTrimuriti;
			else pMob[i].m_byClan = a_iClan;
		}

		if( byOld != pMob[i].m_byClan )
		{
			MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
			kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
			kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);
			kZoneSettingMsg.snSiege = g_kSiege.get_Started(); //g_kSiege.get_Started(); 공성종료
			pUser[i].cSock.SendOneMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );

			S_SCP_INIT_OTHER_MOB sm;
			GetCreateMob( i, &sm );
			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, i);

			MSG_CHANGE_CLAN kMsg;
			kMsg.wType = MSG_CHANGE_CLAN_ID;
			kMsg.wPDULength = sizeof(MSG_CHANGE_CLAN)-sizeof(HEADER);
			kMsg.snKeyID = i;
			kMsg.byClan = pMob[i].m_byClan;
			pUser[i].cSock.SendOneMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) );

		}

		//MSG_CHANGE_TRIMURITI kMsg;
		//kMsg.snKeyID = i;
		//kMsg.byTrimuriti = pMob[i].m_byClan;
		//pUser[i].cSock.SendOneMessage( (char*)&kMsg, sizeof(MSG_CHANGE_TRIMURITI) );	
	}
}


//@Param
//	nStrongHold : 점령한 요새 ID
//	nGuild : 점령한 길드 ID
void UpdateStrongHold(int nStronghold, int nGuild, int a_iIntruder )
{
	if( SERVER_STRONGHOLD != g_iZoneID ) return; //	요새존일경우 요새업데이트정보를 msg를 이용해 공지한다.
	if( 0 > a_iIntruder || MAX_USER <= a_iIntruder ) return;

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	int iGuildID = pGuild[nGuild].GUILD.GuildID;

	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\r\n\r\n[UpdateStrongHold] %dyy%dmm%ddd %dhh%dms%dss > %d stronghold is occupied by a guild(%d, %s) \r\n"
			, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, nStronghold, iGuildID, pGuild[nGuild].GUILD.GuildName
			); 
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
	}

	// 길드가 기존에 요새를 소유하고 있는지 검사
	bool bChanged = false;
	int iOldProperty = 0;
	for( int i = 0; i < eStronghold_MaxCount; ++i )
	{
		//if( (g_krgStronghold[i].iOwner == iGuildID) || (g_krgStronghold[i].iOwnerFriend == iGuildID) ) // 기존에 다른 요새를 가지고 있다면, 초기화를 해준다.
		if( g_krgStronghold[i].iOwner == iGuildID ) // 기존에 다른 요새를 가지고 있다면, 초기화를 해준다.
		{
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- [UpdateStrongHold] The guild have a another stronghold. that is %d and will be free.\r\n"
					, i
					); 
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Stronghold] );
			}

			RefreshClan( i, 0, 1 ); // stronghold i를 소유하고 있던 PC들의 clan을 clear한다.
			memset( &(g_krgStronghold[i]), 0, sizeof(TNSTRONGHOLD) );
			g_krgStronghold[i].iID = i;
			iOldProperty = i;
			CTime kTimeInitialized( 2005, 1, 1, 0, 0, 0 );
			g_krgStronghold[i].kTimeOccupied = kTimeInitialized;
			bChanged = true;
		}

		if( g_krgStronghold[i].iOwnerFriend == iGuildID ) // 자신의 연합 길드가 다른 요새를 소유하고 있다. 연합을 깨준다.
		{
			Msg_GuildAlliance sm; sm.wType = _Msg_GuildAlliance;
			sm.dwClientTick = CurrentTime + pUser[a_iIntruder].TickDiff;
			sm.byType = eGuildFriend; sm.byAct = eGuildAllianceOut;

			ProcessClientMessage(a_iIntruder, (char*)&sm);
		}
	}

	g_krgStronghold[nStronghold].iID = nStronghold;
	g_krgStronghold[nStronghold].iOwner = pGuild[nGuild].GUILD.GuildID;
	g_krgStronghold[nStronghold].dwMark = pGuild[nGuild].GUILD.Mark;
	strcpy( g_krgStronghold[nStronghold].szGuildName, pGuild[nGuild].GUILD.GuildName );
	g_krgStronghold[nStronghold].iOwnerFriend = GetGuildID(pGuild[nGuild].GUILD.AlliedGuildName1);
	CTime kTime( g_kSystemTime );
	g_krgStronghold[nStronghold].kTimeOccupied = kTime;

	// 신규 점령한 요새에 대한 공지
	if( eStronghold_Northwest == nStronghold ) TriggerEvent( 0, 26, 0, 0, 0, 1100 );
	else if( eStronghold_Northeast == nStronghold ) TriggerEvent( 0, 27, 0, 0, 0, 1101 );
	else if( eStronghold_Southwest == nStronghold ) TriggerEvent( 0, 28, 0, 0, 0, 1102 );
	else if( eStronghold_Southeast == nStronghold ) TriggerEvent( 0, 29, 0, 0, 0, 1103 );

	if( bChanged )
	{
		// 이미 점령했던 요새에 대한 공지 및 immunity 해제, < Edited by spencer, 2005.05.31, 아래의 event ID는 수정해야 한다. >
		if( eStronghold_Northwest == iOldProperty ) TriggerEvent( 0, 155, 0, 0, 0, 1200 );
		else if( eStronghold_Northeast == iOldProperty ) TriggerEvent( 0, 156, 0, 0, 0, 1201 );
		else if( eStronghold_Southwest == iOldProperty ) TriggerEvent( 0, 157, 0, 0, 0, 1202 );
		else if( eStronghold_Southeast == iOldProperty ) TriggerEvent( 0, 158, 0, 0, 0, 1203 );		
	}

	CGuild GUILD;
	Msg_StrongHoldUpdate sm; ZeroMemory(&sm, sizeof(sm));
	sm.wType = _Msg_StrongHoldUpdate;

	for(int i=0; i<eStronghold_MaxCount; i++)
	{
		strncpy(sm.szGuildName[i], g_krgStronghold[i].szGuildName, SZGUILD_LENGTH);
		sm.dwMark[i] = g_krgStronghold[i].dwMark;
	}

	MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
}


void KillMonster( int a_iHandle )
{
	if( MAX_USER > a_iHandle || MAX_MOB <= a_iHandle ) return;

	if( eTNAIO_HaveMaster & pMob[a_iHandle].m_iAIOption ) pMob[a_iHandle].ReleaseLinkWithMaster();

	pMob[a_iHandle].MOB.nHP = 0;
	pMob[a_iHandle].CurrentTarget = 0;
	pMob[a_iHandle].m_eFSM = eTNFsm_Dead;

	pMob[a_iHandle].DetermineNextPopTime( 20 );
}


void ReturnPCToSaveZone( int a_iPC )
{
	if( (0 >= a_iPC ) || (MAX_USER <= a_iPC) ) return;

	if( 0 >= pMob[a_iPC].MOB.bySaveZone )
	{
		pMob[a_iPC].MOB.bySaveZone = eZone_Mandra; // 혹 guild 가 없을 경우
		pMob[a_iPC].MOB.snSaveX = 486; // 만다라마을 포탈 486, 190
		pMob[a_iPC].MOB.snSaveZ = 190;		
	}
	
	BYTE byZoneToMove = pMob[a_iPC].MOB.bySaveZone;
	HS2D_COORD kPos;
	kPos.x = pMob[a_iPC].MOB.snSaveX;
	kPos.y = pMob[a_iPC].MOB.snSaveZ;

	if( eZone_Castle == byZoneToMove ) // 만약 만
	{
		byZoneToMove = eZone_Mandra;
		kPos.x = 486;
		kPos.y = 190;
	}


	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;
	sm.byZone = byZoneToMove;
	sm.snX = (short)kPos.x;
	sm.snZ = (short)kPos.x;
	pMob[a_iPC].m_kWaitAction.iAction = eWaitAct_ZonePortal;
	pUser[a_iPC].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 


	//pMob[a_iPC].MoveZone( byZoneToMove, kPos.x, kPos.y );
}


int PostMessageToZone( char* a_pMsg, int a_iTextColor, int a_iBGColor, int a_iMessage )
{
	if( NULL == a_pMsg ) return eTNRes_Failed;
	//if( 0 > a_iMessage || MAX_STRING <= a_iMessage ) return eTNRes_Failed;

	MSG_Broadcast kMsg;
	//memset( &kMsg, 0, sizeof(kMsg) );
	kMsg.wType = _MSG_Broadcast;
	kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

	kMsg.byBgColor = a_iBGColor;
	kMsg.byTextColor = a_iTextColor;
	kMsg.byMsgType = 1; 

	strcpy( kMsg.szMsg, a_pMsg/*g_pMessageStringTable[a_iMessage]*/ );
	strncpy( kMsg.szName, g_pMessageStringTable[_Announcement]/*"공지"*/, SZNAME_LENGTH );
	kMsg.byTrimuriti = eTNClan_GM;

	SendToAll( (MSG_STANDARD*)&kMsg );

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	//{
	//	char chBuf[2048] = { 0,0,0, };
	//	sprintf(chBuf, "[eTNAct_PostMessageToZone] %dYY%dMM%dDD %dHH%dMI%dSS, MSGID:%d, %s\r\n"
	//		, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
	//		, a_iMessage, kMsg.szMsg );
	//	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
	//}

	if( 112 == a_iMessage ) // "칼리아 던전의 문이 열렸습니다. 주신 성의 주신상을 클릭하세요."
	{
		for( int iUser = 0; iUser < MAX_USER; ++iUser )
		{	if( USER_PLAY != pUser[iUser].Mode ) continue;
			SendClientMessage( iUser, g_pMessageStringTable[_OpenTheGate] );
		}
	}

	return eTNRes_Succeeded;
}


int PostMessageToWorld( char* a_pMsg, int a_iTextColor, int a_iBGColor, int a_iMessage )
{
	if( NULL == a_pMsg ) return eTNRes_Failed;
	//if( 0 > a_iMessage || MAX_STRING <= a_iMessage ) return eTNRes_Failed;

	MSG_Broadcast kMsg;
	//memset( &kMsg, 0, sizeof(kMsg) );
	kMsg.wType = _MSG_Broadcast;
	kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

	kMsg.byBgColor = a_iBGColor;
	kMsg.byTextColor = a_iTextColor;

	strcpy( kMsg.szMsg, a_pMsg/*g_pMessageStringTable[a_iMessage]*/ );
	kMsg.szMsg[MAX_NOTIFY_LENGTH-1] = 0; kMsg.szMsg[MAX_NOTIFY_LENGTH-2] = 0;
	strncpy( kMsg.szName, g_pMessageStringTable[_Announcement]/*"공지"*/, SZNAME_LENGTH );
	kMsg.byTrimuriti = eTNClan_GM;
	kMsg.byMsgType = MESSAGE_POSTTOWORLD;

	//SYSTEMTIME st;
	//GetLocalTime( &st );
	//{
	//	char chBuf[2048] = { 0,0,0, };
	//	sprintf(chBuf, "[eTNAct_PostMessageToWorld] %dYY%dMM%dDD %dHH%dMI%dSS, MSGID:%d, %s\r\n"
	//		, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
	//		, a_iMessage, kMsg.szMsg );
	//	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_EventTriggered] );
	//}

	if( !MSGServerSocket.SendOneMessage( (char*)&kMsg, sizeof(kMsg) ) )
	{	Log("err brodcast MSG-SEND POST A MESSAGE", "system", 0 );
	}

	return eTNRes_Succeeded;
}


void HT_PlayYut()
{
	int nTimer = YutCounter--%15;							//	15초마다 반복되는 task.
	switch(nTimer)
	{
	case 7:	//	말에게 전진명령(사또)
		{
            S_SCP_NOTIFY_CHAT nm;	nm.wType = SCP_NOTIFY_CHAT;					//	NPC Chat(사또)
			nm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
			nm.nID=10000+1299;													//	사또 + 10000(NPC의 경우 +10000하기로함)
			nm.byTextColor=12; nm.byBgColor = 0; nm.byTrimuriti=0;				//	차후 정해지면 변경

			short snX, snY = 0;
			if(!g_ParamMgr.HT_bGetNPCPosition( 1299, &snX, &snY )) return;	//	해당 NPC정보를 읽지 못할경우.

			if(g_Yut.HT_byGetPosition() >= MAX_POSITION)
			{
				strncpy(nm.szMsg, g_pMessageStringTable[_Yut_PlayEnd], sizeof(nm.szMsg));
				GridMulticast(snX, snY, (MSG_STANDARD*)&nm, 0, 200);
				break;
			}

			switch(g_Yut.HT_byGetResult())
			{
			case 1:
				{	strncpy(nm.szMsg, g_pMessageStringTable[_YutPlayDo], sizeof(nm.szMsg));
				}	break;
			case 2:
				{	strncpy(nm.szMsg, g_pMessageStringTable[_YutPlayGae], sizeof(nm.szMsg));
				}	break;
			case 3:
				{	strncpy(nm.szMsg, g_pMessageStringTable[_YutPlayGul], sizeof(nm.szMsg));
				}	break;
			case 4:
				{	strncpy(nm.szMsg, g_pMessageStringTable[_YutPlayYut], sizeof(nm.szMsg));
				}	break;
			case 5:
				{	strncpy(nm.szMsg, g_pMessageStringTable[_YutPlayMo], sizeof(nm.szMsg));
				}	break;
			default:
				break;
			}
			GridMulticast(snX, snY, (MSG_STANDARD*)&nm, 0, 200);
		}
		break;
	case 5:	//	말의 이동
		{	if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;
			
			Msg_YutMove sm; sm.wType = _Msg_YutMove;
			sm.wPDULength = sizeof(Msg_YutMove) - sizeof(HEADER);
			sm.wFromIndex = g_Yut.HT_byGetPosition()+1;

			int nX, nZ = 0;
			int nPos = g_Yut.HT_byMoveYut();
			if(nPos>= 0 && nPos<MAX_POSITION)
			{	
				nX = g_Yut.m_uniPosition[nPos].x;
				nZ = g_Yut.m_uniPosition[nPos].y;
			}
			else		//	말이 실제 행마를 완료한 경우
			{
				nX = 5;
				nZ = 5;

				BYTE byResult = g_Yut.HT_byGetResult();
				if(byResult>0 && byResult<6) Teleport( g_iGambleYut[byResult-1], 5, 5 );
			}

			int tret = GetEmptyMobGrid(g_iGambleHorse,&nX,&nZ);
			if	(tret==FALSE)
			{	
#ifdef __YUT_LOG__				
				sprintf(temp,"err no empty space at HT_PlayYut x:%d y:%d \r\n",nX,nZ);
				TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				int tret = GetEmptyMobGrid(g_iGambleHorse,&nX,&nZ);
				if	(tret==FALSE)
				{	
#ifdef __YUT_LOG__					
					sprintf(temp,"err no empty space at HT_PlayYut x:%d y:%d \r\n",nX,nZ);
					TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				}
			}

			int nOldX, nOldY = 0;
			nOldX = pMob[g_iGambleHorse].TargetX;
			nOldY = pMob[g_iGambleHorse].TargetY;

			sm.nID = g_iGambleHorse;
			sm.wToIndex = nPos+1;

#ifdef __YUT_LOG__
			sprintf(temp, "Yut_Horse move from x:%d y:%d MobGrid:%d from %d to %d by result:%d \r\n", nOldX, nOldY, pMobGrid[nOldY][nOldX], sm.wFromIndex, sm.wToIndex, g_Yut.HT_byGetResult());
			TimeWriteLog(temp, ".\\Event\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__

			GridMulticast(g_iGambleHorse, nX, nZ, (MSG_STANDARD*)&sm, 200, ACTION_YUT);

#ifdef __YUT_LOG__
			sprintf(temp, "Yut_Horse move from x:%d y:%d MobGrid:%d to x:%d y:%d MobGrid:%d \r\n", nOldX, nOldY, pMobGrid[nOldY][nOldX], pMob[g_iGambleHorse].TargetX, pMob[g_iGambleHorse].TargetY, pMobGrid[pMob[g_iGambleHorse].TargetY][pMob[g_iGambleHorse].TargetX]);
			TimeWriteLog(temp, ".\\Event\\[Log]Yut.txt");

			TimeWriteLog("말이동 \r\n",".\\Event\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__
		}	break;
	case 3:	//	투명몹생성
		{	if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			int nEvent = g_Yut.HT_byGetPrePosition() + 36;

#ifdef __YUT_LOG__
			TimeWriteLog("투명몹생성전 \r\n",".\\Event\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__

			TriggerEvent(0, nEvent, 0, 0, 0, 0);

#ifdef __YUT_LOG__
			TimeWriteLog("투명몹생성후 \r\n",".\\Event\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__
		}	break;
	case 2:	//	결과삭제(도,개,걸,윷,모삭제)
		{
			if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			BYTE byResult = g_Yut.HT_byGetResult();

			if(byResult>0 && byResult<6)
							Teleport( g_iGambleYut[byResult-1], 5, 5 );

			//	Teleport( g_Yut.HT_byGetResult(), 5, 5 );
		}	break;
	case 0:	//	결과산출(도,개,걸,윷,모생성)
		{
			if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			byte byResult = g_Yut.HT_byYutPlay();

			if(byResult>0 && byResult<6)
				Teleport( g_iGambleYut[byResult-1], 666, 419 );
		}
	}
}


int CountMonster( int a_iTribe )
{
	int iCount = 0;
	for( int i = MAX_USER; i < MAX_MOB; ++i )
	{
		if( MOB_EMPTY == pMob[i].Mode ) continue;
		if( a_iTribe == pMob[i].MOB.snTribe ) ++iCount;
	}

	return iCount;
}

void DumpMobile( int a_iHandle )
{
	if( 0 >= a_iHandle || MAX_MOB <= a_iHandle ) return;

	FILE* fOut = NULL;
	char szFileName[64] = { 0,0,0,};
	sprintf( szFileName, ".\\Event\\%s_%d.dum", pMob[a_iHandle].MOB.szName, a_iHandle );
	fOut = fopen( szFileName, "wb" );
	if( NULL == fOut ) return;

	fwrite( (void*)&pMob[a_iHandle], sizeof(CMob), 1, fOut );

	fclose( fOut );
}


void LoadDump( char* a_pFileName )
{
	FILE* fIn = NULL;
	char szFileName[64] = { 0,0,0,};
	sprintf( szFileName, ".\\Event\\%s.dum", a_pFileName );

	fIn = fopen( szFileName, "rb" );
	if( NULL == fIn ) return;

	CMob kDump;
	fread( (void*)&kDump, sizeof(CMob), 1, fIn );

	fclose( fIn );
}

BYTE SetGameEvent(int iHandle, DWORD dwGameEventID, int* piParam)
{
	DWORD dwResult = 0; 
	if(iHandle<=0 || iHandle>=MAX_USER) return (BYTE)dwResult;
	if(dwGameEventID == 0) return (BYTE)dwResult;

	//	최대 동시 4*8 개가 가능하나 8개만 사용하기로 한다.
	for(int i=0; i<8; i++)
	{
		DWORD dwFlag = 0x00000001 << i;
		if((dwGameEventID & dwFlag) == 0) continue;

		sprintf(temp, "Event:%X, Flag:%X, account:%s \r\n", dwGameEventID, dwFlag, pUser[iHandle].AccountName);
		TimeWriteLog(temp, "Data\\EVENT.TXT");

		int iGiveItemCount = 0;
		for(int k=0; k<5; k++)																//	아이템지급 이벤트액션의 갯수를 체크한다
			if(g_kGameEvent[i].stAction[k].iAction == eTNAfn_GiveItem) iGiveItemCount++;	

		if(iGiveItemCount>0 && iGiveItemCount>GetEmptyInvenCount(iHandle)) continue;		//	지급이벤트보다 빈공간이 작을 경우 다음 이벤트

		for(k=0; k<5; k++)
		{
			int iAction = g_kGameEvent[i].stAction[k].iAction;
			if(iAction==0) continue;

			switch(iAction)
			{
			case eTNAfn_PranaRatebyLevel:			//	사냥시 획득프라나 일정비율 상승 및 하향(레벨제한)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
                        pMob[iHandle].m_dGetPranaRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_MoneyRatebyLevel:			//	루피아 습득시 일정확률로 상승 및 하향(레벨제한)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
						pMob[iHandle].m_dGetMoneyRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_DeathPranaRatebyLevel:		//	사망시 프라나 감소율 상승 및 하향(레벨제한)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
						pMob[iHandle].m_dCutDeathPranaRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_LevelUpFromLevel1:			//	레벨별 레벨1상승
				{
					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow) break;
					if(pMob[iHandle].MOB.byLevel>iLevelHigh) break;
					pMob[iHandle].LevelUp();
					pMob[iHandle].Init( iHandle );
					pMob[iHandle].NotifyUpdateUIMsg();
				}	break;
			case eTNAfn_LevelUpFromLevel3:			//	레벨별 레벨3상승
				{
					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow) break;
					if(pMob[iHandle].MOB.byLevel>iLevelHigh) break;
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].Init( iHandle );
					pMob[iHandle].NotifyUpdateUIMsg();
				}	break;
			case eTNAfn_LevelUpFromLevel5:			//	레벨별 레벨5상승
				{
					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow) break;
					if(pMob[iHandle].MOB.byLevel>iLevelHigh) break;
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].Init( iHandle );
					pMob[iHandle].NotifyUpdateUIMsg();
				}	break;
			case eTNAfn_GiveItem:				//	아이템지급(자리없으면 안줌)
				{
					int iItemIndex = g_kGameEvent[i].stAction[k].iParam1;
					int iCount = g_kGameEvent[i].stAction[k].iParam2;

					GiveItem(iHandle, iItemIndex, iCount);
				}	break;
			case eTNAfn_ChangeTribeFromLevel:	//	종족변경
				{
					for(int j=0; j<8; j++)
					{
						if(*piParam == (short)pow(2, j)) break;
					}

					if(j==8) return false;			//	종족변경 액션실패(잘못된 데이터의 경우)

					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow || pMob[iHandle].MOB.byLevel>iLevelHigh) return (BYTE)dwResult;

					pMob[iHandle].MOB.snTribe = *piParam;
					//	1차전직상태면 class2 항목을 같이 바꿔준다
					//	2차전직상태면 1차전직상태로 바꿔준다
					/*
					if(pMob[iHandle].MOB.byClass1==CLASS_LEVEL1 || pMob[iHandle].MOB.byClass1==CLASS_LEVEL2)
					{
						pMob[iHandle].MOB.byClass1 = CLASS_LEVEL1;
						switch ( pMob[iHandle].MOB.snTribe )
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							pMob[iHandle].MOB.byClass2 = CLASS_SATVAN;
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							pMob[iHandle].MOB.byClass2 = CLASS_DHVANTA;
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							pMob[iHandle].MOB.byClass2 = CLASS_NIRVANA;
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							pMob[iHandle].MOB.byClass2 = CLASS_MANTRIKA;
							break;
						}
					}
					*/

					pMob[iHandle].Init(iHandle);
					pMob[iHandle].ResetClass();
					pMob[iHandle].ResetSkill();
					pMob[iHandle].ResetStat();

					// 내 정보를 주위의 mob들에게 전송한다.
					int tx = pMob[iHandle].TargetX; int ty = pMob[iHandle].TargetY;
					S_SCP_INIT_OTHER_MOB sOther;
					GetCreateMob(iHandle,&sOther); 
					GridMulticast(tx,ty,(MSG_STANDARD*)&sOther, iHandle);
				}	break;
			//case eTNAfn_Attendence:				//	출석체크
			//	{
			//		bool bRet = g_GameEvent.CheckDate(pUser[iHandle].AccountName);

			//	}	break;
			case eTNAfn_Coupon:						//	쿠폰사용 - 아이템지급(1개까지 지급가능)
				{
					char* pData = (char*)(piParam+4);
					if(GetEmptyInvenCount(iHandle)==0) return (BYTE)dwResult;	//	인벤토리가 풀일경우(지급이 1개 이므로 풀만아니면 지급된다)
					bool bRet = g_GameEvent.m_Coupon.UseCoupon(pData);
					if(!bRet) return (BYTE)dwResult;

					int iItemIndex1 = g_kGameEvent[i].stAction[k].iParam1;
					int iItemCount = g_kGameEvent[i].stAction[k].iParam2;
					GiveItem(iHandle, iItemIndex1, iItemCount);
				}	break;
			case eANAfn_GiveItemMaharaja:
				{
					if(pUser[iHandle].nGuildLevel != eGuildMaster) return (BYTE)dwResult;	//	마하라자에게만 해당하는 이벤트이다
					if((k+GetEmptyInvenCount(iHandle)) < 5) return (BYTE)dwResult;			//	최대 5개의 아이템이 들어갈수있다

					int iItemIndex = g_kGameEvent[i].stAction[k].iParam1;
					int iCount = g_kGameEvent[i].stAction[k].iParam2;
					GiveItem(iHandle, iItemIndex, iCount);
				}
			default:
				{

				}	break;
			}
		}

		if(g_kGameEvent[i].iType == 0)	//	일회성 이벤트일경우
		{
			if(g_kGameEvent[i].iTarget == 0)
                g_GameEvent.RemoveEvent(i, pUser[iHandle].AccountName);
			else if(g_kGameEvent[i].iTarget == 1)
				g_GameEvent.RemoveEvent(i, pMob[iHandle].MOB.szName);
			else
			{
				if(pUser[iHandle].nGuildIndex>0 && (pUser[iHandle].nGuildIndex<MAX_USER))
					g_GameEvent.RemoveEvent(i, pGuild[pUser[iHandle].nGuildIndex].GUILD.GuildName);
			}


			pUser[iHandle].m_dwEvent -= (DWORD)pow(2, i);
		}


		dwResult |= dwFlag;
	}

	return (BYTE)dwResult;
}

void SetGuildCargo(int iGuildID, int iCargoIndex, STRUCT_ITEM* pData)
{
	int iIndex = IsGuildMemberIn(iGuildID);
	pGuild[iIndex].GUILD.Repository[iCargoIndex] = *pData;

	Msg_GuildItemUpdate sm; sm.wType = _Msg_GuildItemUpdate;
	sm.wPDULength = sizeof(sm)-sizeof(HEADER);
	sm.nGuildID = iGuildID;
	sm.nFromIndex = -1; sm.nToIndex = iCargoIndex;
	sm.item = *pData;

	SendGuildMessage(iIndex, (MSG_STANDARD*)&sm);

	return;
}


//enum { eLogFileName_Assert = 0, eLogFileName_BossSystem, eLogFileName_KalaSystem, eLogFileName_Stronghold, eLogFileName_Castle, eLogFileName_ArenaEvent
//		, eLogFileName_RvREntry, eLogFileName_EventTriggered, eLogFileName_ItemThatSummonMonster, eLogFileName_ItemDroppedByEvent
//		, eLogFileName_InvalidCombat, eLogFileName_RecordPCName, eLogFileName_CountMonster, eLogFileName_OnKilled
//		, eLogFileName_HackDist, eLogFileName_HackAttackSpeed,
void SetLogFileName()
{
	char szDate[512] = { 0,0,0, };
	sprintf( szDate, "_%4dYY%2dMM%2dDD%2dHH"
		, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour//, g_kSystemTime.wMinute, g_kSystemTime.wSecond
		);

	sprintf( g_szrgLogFileName[eLogFileName_Assert], ".\\Event\\[Log]Assert_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_BossSystem], ".\\Event\\[Log]BossSystem_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_KalaSystem], ".\\Event\\[Log]KalaSystem_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_Stronghold], ".\\Event\\[Log]Stronghold_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_Castle], ".\\Event\\[Log]Castle_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_ArenaEvent], ".\\Event\\[Log]ArenaEvent_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_RvREntry], ".\\Event\\[Log]RvREntry_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_EventTriggered], ".\\Event\\[Log]EventTriggered_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_ItemThatSummonMonster], ".\\Event\\[Log]UseItem_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_ItemDroppedByEvent], ".\\Event\\[Log]ItemDroppedByEvent_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_InvalidCombat], ".\\Event\\[Log]InvalidCombat_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_RecordPCName], ".\\Event\\[Log]RecordPCName_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_CountMonster], ".\\Event\\[Log]CountMonster_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_OnKilled], ".\\Event\\[Log]OnKilled_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_HackDist], ".\\Event\\[Log]HackDist_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_HackAttackSpeed], ".\\Event\\[Log]HackAttackSpeed_%s.txt", szDate );
	sprintf( g_szrgLogFileName[eLogFileName_MagicLamp], ".\\Event\\[Log]MagicLamp_%s.txt", szDate );


	for( int i = 0; i < eLogFile_Size; ++i )
	{
		WriteLog( g_szrgLogFileName[i], ".\\Monster_Log\\[Log]LoadLogFileName.txt" );
		WriteLog( "\r\n", ".\\Monster_Log\\[Log]LoadLogFileName.txt" );
	}
}


int LoadRouteData()
{
	memset( g_krgRoute, 0, sizeof(g_krgRoute) );

	char szData[128] = { 0,0,0, };
    char szArgument1[32] = { 0,0,0, }; // ID
    char szArgument2[32] = { 0,0,0, }; // Route

	char szSegmentX[MAX_SEGMENT][32] = { 0,0,0, }; // Segment
	char szSegmentY[MAX_SEGMENT][32] = { 0,0,0, };
	char szSegmentRange[MAX_SEGMENT][32] = { 0,0,0, };
	char szSegmentWait[MAX_SEGMENT][32] = { 0,0,0, };

    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0, iArgument6 = 0, iArgument7 = 0, iArgument8 = 0, iArgument9 = 0 ;
	
	FILE* fin;
	fin = fopen( ".\\Data\\Route.txt", "rt" );
	if( NULL == fin ) 
	{ 
		WriteLog( "No Route information\r\n", ".\\monster_log\\[Log]LoadRouteData.txt" );
		//MessageBox( hWndMain, "Not found Route.txt in data folder.", "Failed to initialize data about the Route.", NULL ); 
		return eTNRes_Failed; 
	}

	WriteLog( "\r\n\r\n", ".\\monster_log\\[Log]LoadRouteData.txt" );

	while( true )
	{
		char* ret = fgets( (char*)szData, 128, fin );
		if( NULL == ret ) break;

		sscanf( szData, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", szArgument1, szArgument2
			, szSegmentX[0], szSegmentY[0], szSegmentRange[0], szSegmentWait[0]
			, szSegmentX[1], szSegmentY[1], szSegmentRange[1], szSegmentWait[1]
			, szSegmentX[2], szSegmentY[2], szSegmentRange[2], szSegmentWait[2]
			, szSegmentX[3], szSegmentY[3], szSegmentRange[3], szSegmentWait[3]
			, szSegmentX[4], szSegmentY[4], szSegmentRange[4], szSegmentWait[4]
			);

		if( '/' == szArgument1[0] && '/' == szArgument1[1] ) continue;

		iArgument1 = atoi( szArgument1 ); // ID #
		if( 0 >= iArgument1 || eSiz_Route <= iArgument1 ) continue;
		g_krgRoute[iArgument1].iMethod = atoi( szArgument2 ); // Route

		// Segment
		g_krgRoute[iArgument1].irgSegmentListX[0] = atoi( szSegmentX[0] );
		g_krgRoute[iArgument1].irgSegmentListY[0] = atoi( szSegmentY[0] );
		g_krgRoute[iArgument1].irgSegmentListRange[0] = atoi( szSegmentRange[0] );
		g_krgRoute[iArgument1].irgSegmentListWait[0] = atoi( szSegmentWait[0] );

		g_krgRoute[iArgument1].irgSegmentListX[1] = atoi( szSegmentX[1] );
		g_krgRoute[iArgument1].irgSegmentListY[1] = atoi( szSegmentY[1] );
		g_krgRoute[iArgument1].irgSegmentListRange[1] = atoi( szSegmentRange[1] );
		g_krgRoute[iArgument1].irgSegmentListWait[1] = atoi( szSegmentWait[1] );

		g_krgRoute[iArgument1].irgSegmentListX[2] = atoi( szSegmentX[2] );
		g_krgRoute[iArgument1].irgSegmentListY[2] = atoi( szSegmentY[2] );
		g_krgRoute[iArgument1].irgSegmentListRange[2] = atoi( szSegmentRange[2] );
		g_krgRoute[iArgument1].irgSegmentListWait[2] = atoi( szSegmentWait[2] );

		g_krgRoute[iArgument1].irgSegmentListX[3] = atoi( szSegmentX[3] );
		g_krgRoute[iArgument1].irgSegmentListY[3] = atoi( szSegmentY[3] );
		g_krgRoute[iArgument1].irgSegmentListRange[3] = atoi( szSegmentRange[3] );
		g_krgRoute[iArgument1].irgSegmentListWait[3] = atoi( szSegmentWait[3] );

		g_krgRoute[iArgument1].irgSegmentListX[4] = atoi( szSegmentX[4] );
		g_krgRoute[iArgument1].irgSegmentListY[4] = atoi( szSegmentY[4] );
		g_krgRoute[iArgument1].irgSegmentListRange[4] = atoi( szSegmentRange[4] );
		g_krgRoute[iArgument1].irgSegmentListWait[4] = atoi( szSegmentWait[4] );

		#ifdef __TN_TOP_LOG__
		{
			char chBuf[1024] = { 0,0,0, };
			sprintf( chBuf, "ID: %3d, Route:%2d, Segment0(%3d,%3d,%2d,%2d), Segment1(%3d,%3d,%2d,%2d), Segment2(%3d,%3d,%2d,%2d), Segment3(%3d,%3d,%2d,%2d), Segment4(%3d,%3d,%2d,%2d) \r\n"
				, iArgument1, g_krgRoute[iArgument1].iMethod
				, g_krgRoute[iArgument1].irgSegmentListX[0], g_krgRoute[iArgument1].irgSegmentListY[0], g_krgRoute[iArgument1].irgSegmentListRange[0], g_krgRoute[iArgument1].irgSegmentListWait[0]
				, g_krgRoute[iArgument1].irgSegmentListX[1], g_krgRoute[iArgument1].irgSegmentListY[1], g_krgRoute[iArgument1].irgSegmentListRange[1], g_krgRoute[iArgument1].irgSegmentListWait[1]
				, g_krgRoute[iArgument1].irgSegmentListX[2], g_krgRoute[iArgument1].irgSegmentListY[2], g_krgRoute[iArgument1].irgSegmentListRange[2], g_krgRoute[iArgument1].irgSegmentListWait[2]
				, g_krgRoute[iArgument1].irgSegmentListX[3], g_krgRoute[iArgument1].irgSegmentListY[3], g_krgRoute[iArgument1].irgSegmentListRange[3], g_krgRoute[iArgument1].irgSegmentListWait[3]
				, g_krgRoute[iArgument1].irgSegmentListX[4], g_krgRoute[iArgument1].irgSegmentListY[4], g_krgRoute[iArgument1].irgSegmentListRange[4], g_krgRoute[iArgument1].irgSegmentListWait[4]
				);

			WriteLog( chBuf, ".\\monster_log\\[Log]LoadRouteData.txt" );
		}
		#endif
	}

	fclose( fin );

	return eTNRes_Succeeded;
}

void GetPCSkillMD5CheckSum( char *pCheckSum )
{
	std::vector< HTIDLevel > vecIDLevel;
	g_ParamMgr.HT_bGetAllID( HT_PARAMTYPE_PCSKILL, &vecIDLevel );

	int *pCastTimes = new int[vecIDLevel.size()];
	for ( int i = 0 ; i < vecIDLevel.size() ; i++ )
	{
		HTIDLevel &oIDLevel = vecIDLevel[i];
        g_ParamMgr.HT_bGetPCSkillReadyTime( oIDLevel.iID, oIDLevel.byteLevel, &pCastTimes[i] );
	}

	CMD5Checksum::GetMD5( (byte*)pCastTimes, vecIDLevel.size() * sizeof(int), pCheckSum );
	delete[] pCastTimes;
}