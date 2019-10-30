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
#include "TNInfluenceMap.h"
#include "TNScheduler.h"
#include "TNArena.h"
#include "Quest.h"

#include "HTNew_On.h"
#include "TFPercentMixer.h"
#include "CrackType.h"
#include "DrawInfo.h"
#include "HTRankSystem.h"
#include "GameEvent.h"
#include "Yut.h"
#include "RentalStore.h"
	
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

// �̺�Ʈ ���� �ڵ� ////////////////////////////////////////////////////////
int evStartIndex   =  0;  // ��ӽ��۹�ȣ
int evEndIndex     =  0;  // ��ӳ���ȣ
int evCurrentIndex =  0;  // ���� ��ӵ� ��ȣ
int evRate         =  0;  // ������Ȯ�� 1000�̸� 1/1000
int evItem         =  0;  // �̺�Ʈ �������� �ڵ�
int evIndex        =  0;  // �����ۿ� �����ڵ尡 �ٴ°�.
int evOn           =  0;  // �������� �������� �ִ°� 1�̸� �������� ����.
int evDelete       =  0;  // 1 �̺�Ʈ ������ ������  // 0 ��������
int evNotice	   =  1;  // �̺�Ʈ�� ������ �ߴ���		 
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
extern TNInfluenceMap    g_kInfluenceMap ; 
extern int               g_iMonsterLevelForWritingLog ;
extern TNCELL              g_krgCell[MAX_GRIDY][MAX_GRIDX] ;
char  FailAccount[16][ACCOUNTNAME_LENGTH];
E_COUNTRY_ID		   g_eCountryID = eCountryKorea;

HWND                   hWndMain;
HMENU                  hMainMenu;
unsigned int           CurrentTime  = 0;
unsigned int		   LastSendTime = 0;
int                    DropCount = 0; // �̺�Ʈ�� Ư�� ������ ��ӽ�ų�� ���.
int						ValidUser = 1000;
CMob					pMob     [MAX_MOB];
CUser					pUser    [MAX_USER];
CUser					TempUser;
CItem					pItem    [MAX_ITEM];
CGuild					pGuild[MAX_USER];
TNITEM_DATA				pItemData[MAX_ITEM_DATA];
TNSKILL_DATA			pSkillData[MAX_SKILL_DATA];
STRUCT_MOB				pMonsterData[MAX_MONSTER_DATA] ;
unsigned short         pMobGrid   [MAX_GRIDY][MAX_GRIDX];
unsigned short         pItemGrid  [MAX_GRIDY][MAX_GRIDX];



extern int              g_iHostileTable[MAX_CLAN][MAX_CLAN] ;
extern int						g_irgLevelUp[TN_MAX_LEVEL] ;
extern TNRate10000					g_krgRewardItemRate[MAX_MONSTER_DATA][eRwd_ItemCount] ;
extern TNCOEFFICIENT           g_krgCoefficientByClass[eCls_MaxLevel][eCls_MaxSpecialized] ;
extern short                   g_srgItemGroup[eRwd_ItemGroup][eRwd_ItemGroupCount] ;
extern short					g_srgGroupItemCount[eRwd_ItemGroup] ;
extern TNEFFECTTOLERANCE		g_krgEffectTolerance[eCls_MaxLevel][eCls_MaxSpecialized] ;
extern STRUCT_ITEM             g_krgItemByLevel[eItm_MaxCategory][eItm_MaxLevel] ;
extern TNDeck10000             g_krgItemRateByMonLevel[eMonster_MaxLevel] ; // card : 1~11
extern TNDeck1000              g_kRateByItemCategory ; // card : 0 ~n
extern short                   g_srgRateByItemLevel[eMonster_MaxLevel][eItm_MaxLevel] ;
extern short                   g_srgRateByItemCategory[eItm_MaxCategory] ;
int							   g_pRvRZoneList[eRvRZone_Count] = { 10, 11, 13, 14, 15, 0, 0, 0, 0, 0 } ;
extern TNCONSIDER              g_krgConsider[eCon_Sort][eCon_Sort] ;
extern TNJUDGE_COMBAT_VALUE    g_krgJudgeCombat[2][2] ;
extern int                     g_irgRvRPKConsider[eCaste_MaxLevel][eCaste_MaxLevel] ;
extern int                     g_irgRewardBP[eCaste_MaxLevel] ;
extern short					g_srgAttackTypeVSArmorTypeChart[eAAC_ArmorTypeCount][eAAC_AttackTypeCount] ; // 0, 0�� ������� �ʴ´�. 1���� �����Ѵ�.
extern TNSPEECH_CONTENT         g_krgSpeechContent[eTNSpch_MaxContentCount+1] ;
extern char                    g_szrgComment[eTNSpch_MaxCommentCount+1][101] ;
extern short                   g_srgAIList[eTNAI_MaxAICount+1][eTNAI_MaxEventSort+1] ;
extern TNACTION_LIST            g_krgActionList[eTNAI_MaxActionListCount+1] ;
extern TNACTION                g_krgAction[eTNAI_MaxActionCount+1] ;

extern char                   g_pDetectEnemyTable[ePos_MaxPosCount][2] ;
extern short                   g_pDetectEnemyRadius[eRds_MaxDetectEnemy+1] ;
int						g_bIsKaliaOpend = false ;
//int						g_iIsArenaOpend = 0 ; // �Ʒ����� �����ִ��� �˻�
//int						g_iArenaWinner = 0 ;
//int						g_irgArenaEntry[eArena_MaxEntry] = { 0,0,0, } ;
//int						g_iArenaEntryCount = 0 ;

int                     g_irgRealm[eRealm_MaxCount] = { 0,0,0, } ;

int                     g_irgKalaAltarRewarder[eKalaRewarder_MaxCount]  ;
extern TNKALA_ALTAR_OLD            g_krgKalaAltar[eKalaAltar_MaxCount] ;
extern HS2D_COORD				g_krgKalaRewarderPosition[eKalaRewarder_MaxCount][5] ;
int						g_iGambleHorse ;
int						g_iGambleYut[5];
int						g_irgGateOfDungeon[3] = { 0,0,0, } ;
TNAGGRSCORE             g_krgAggrScore[eAggrScore_MaxCount] ;
extern TNEVENT                 g_krgEventList[eEvent_MaxCount] ;
extern TNTASK                  g_krgTaskList[eTask_MaxCount] ;
extern short                   g_srgTimeSchedule[eTS_MaxSlot] ;  // 4�� tic,	900(60��*15(=60�ʸ� 4�ʷ� ������ 15�� slice))
int                     g_irgEntryCount[5] = { 110, 30, 40, 0, 40 } ; // 1,2,4�� �� �ֽ� ��ȣ, 0�� index�� sum���� �Ѵ�.(or 3�� index)
TNDeck10000             g_krgBlessOfGod[eBlss_MaxSort][5] ; //  ����/��� 2����(2)��, �� �ֽ�(1,2,4)���� 1������(5)
TNDeck1000				g_kMonsterScroll ;
TNSTRONGHOLD			g_krgStronghold[eStronghold_MaxCount] ;
HS2D_COORD				g_stPosStronghold[eStronghold_MaxCount];
DWORD					g_dwArenaMoney;
int						g_iBattleForStronghold = 0 ;
int						g_irgMonsterScroll[9] = { 2120, 2122, 2123, 2124, 2125, 2126, 2127, 2071, 2072, } ;
int                     g_irgGod[5] = { 0, 0, 0, } ;
int                     g_iZoneID = 0 ;
int						g_iZoneType = 0 ; // 0:�Ϲ�, 1:�ֽ�����, 2:�������
int                     g_iWorldID = 1 ; // ������ 1,2,3, �׼��� 0, ������ �����̹Ƿ� default�� 1�� ����
short					g_snVersion[4] ; //	Ŭ���̾�Ʈ ����üũ
int                     g_iTimeSlot = 0 ;
int                     g_iHours = 0 ;
int                     g_irgSetting[MAX_SETTING] = { 0,0,0, } ;
int                     g_irgSpeedConsider[6] = { 2000, 3000, 15, 5, 140, 0, } ; // time slice, over time, correct, crack point, log level
CTFPercentMixer			g_RefineTable;
CTFPercentMixer			g_QuestTable;
bool                    g_bDecPrana = false ;
//int                     g_iSwitch = 0xFFFFFFFF ;
int                     g_iSwitch = 0x00000000 ;
int                     g_iMonsterLevelForWritingLog = 30 ;
int                     g_iCmdMaxLength = 200 ;
#ifdef __TN_PLAYMOVIE__
int                     g_irgFlag[10] = { 0,0,0, } ;
#endif
//TNScheduler				g_kScheduler ;
//TNArena					g_kArena ;

double					g_dRwdBramanCorrect = 1 ;
double					g_dRwdPranaCorrect = 1 ;
double                  g_dRwdGoldCorrect = 1 ;
double                  g_dRwdItemCorrect = 1 ;
int						g_nGiftItemIndex = 0;
int						g_nGiftItemMaxCount = 0;
int						g_nGiftItemCount = 0;
int						g_nGiftItemFirstCount = 0;
short					g_snGiftItemGenTime = 0;
STRUCT_ITEM				GiftItem;
int                     g_iViewGridX = 65 ;
int                     g_iViewGridY = 65 ;
int                     g_iHalfGridX = 32 ;
int                     g_iHalfGridY = 32 ;
//bool                    g_bIsInRvR = false ;
int                     g_iFreeSlotForNPC = MAX_USER + 9 ;
int						g_nNameFilterCount = 0;
int						g_nChatFilterCount = 0;
char					g_strNameFilter[500][20];
char					g_strChatFilter[1000][20];

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
DWORD					g_dwRentalTex = 0;
DWORD					g_dwRentalTexMoney = 0;
//int						g_iGiftItem[5] = {0,};
//int						g_iGiftItemCount[5] = {0,};
extern STGAMEEVENT		g_kGameEvent[MAX_EVENT];
int						g_iCastleOwner = 0;

//PORTALINFO							pPortalInfo[MAX_PORTAL_COUNT];
CHTParameterMgr g_ParamMgr;


int  g_HeightWidth  = MAX_GRIDX;
int  g_HeightHeight = MAX_GRIDY;
int  g_HeightPosX   = 0;
int  g_HeightPosY   = 0;
int  BILLING        = 3;  // 0:����  1:����������(�ʱ�ȭ��)    2:���� ��������   3:�����׽�Ʈ.
int  BillCounter	= 0;  // 0�̸� ī��Ʈ�� ���� �ʴ´�.
int	 ItemCounter	= 0;
int	MSGCounter		= 0;
int	g_Week=0;
int	g_Hour=0;
int Colo150Limit=0;
int PotionReady=0;
//	 CUser���� LastReceive�� ����ϰ� �ִٰ� 10���� ����� ������ ������ �����Ѵ�. 




#ifdef _CHINESETRADITION		// �븸 LV0
		int  FREEEXP		= 0;
#elif  _CHINESESIMPLE			// �߱� LV0
		int  FREEEXP		= 0;
#else							// �ѱ� LV31
		int  FREEEXP        =  35;  
#endif 

int  CHARSELBILL    = 0;   // �ѱ��� 0�� �߱��� 1.
int  DOUBLEMODE     = 0;
int	 DEADPOINT		= 1; // �׾����� ����ġ ����
int  LastTick		= 20000;
int  POTIONCOUNT	=10;
int  PARTYBONUS     =100;
int	 GUILDBOARD		= 0;
int  ServerIndex    = -1;
int  Sapphire		=  8;	  // û�ձ��� �޴� �����̾�. �̰��� 16�̸� Ȳ�ձ��� 4, û�� 32�̸� Ȳ��2, û�� 64�� Ȳ�� 1 // �̿� ����.
int  ServerGroup    = -1;
int  GuildCounter   =  1;
int  DecayValue     =  8;
int  ServerDown     =  -1000;
int  UserCount      =  0;
int  SaveCount      =  1;
int  ItemCount      =  MAX_INITITEM;  // INITITEM�� ����������, Decay�� ������� �ʴ´�.
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
int WeekMode = 4; // ������������ �Ͽ��� ����0��~�ݿ��� ����0��
int ColoState = 8;
int ForceWeekMode = -1; // -1�� ����� �ð��� �������� ����.
int GuildDay = 6; // �����.
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

void ExecuteEmergence()
{
	int iZone = ServerIndex + 1 ;

	#ifdef __TN_LOCAL_SERVER_SWITCH__

	g_iSwitch = g_iSwitch | eTNSwitch_EventLog ;

	#endif

	if( eZone_Pamir == iZone )
	{
		g_kMonsterScroll.Init() ;
		g_kMonsterScroll.AddCard( 0, 50 ) ;
		g_kMonsterScroll.AddCard( 1, 100 ) ;
		g_kMonsterScroll.AddCard( 2, 150 ) ;
		g_kMonsterScroll.AddCard( 3, 320 ) ;
		g_kMonsterScroll.AddCard( 4, 150 ) ;
		g_kMonsterScroll.AddCard( 5, 50 ) ;
		g_kMonsterScroll.AddCard( 6, 50 ) ;
		g_kMonsterScroll.AddCard( 7, 20 ) ;
		g_kMonsterScroll.AddCard( 8, 20 ) ;
		g_kMonsterScroll.AddCard( 9, 20 ) ;
		g_kMonsterScroll.AddCard( 10, 20 ) ;
		g_kMonsterScroll.AddCard( 11, 30 ) ;
		g_kMonsterScroll.AddCard( 12, 20 ) ;

		//srand( timeGetTime() ) ;
		int iMaxShuffleCount = rand() % 10 ;
		iMaxShuffleCount += 3 ; // �ּ� 3ȸ�� �����Ѵ�.
		for( int i = 0 ; i < iMaxShuffleCount ; ++i ) g_kMonsterScroll.Shuffle() ; // ������ shuffle�� ���Ѽ� random���� �����Ų��.
	}
	else if( eZone_Chaturanka == iZone ) // ���������̸�, ...
	{
	}

	else if( (eZone_Cruma == iZone) || (eZone_Chaturanka == iZone) || (13 == iZone) || (14 == iZone) || (15 == iZone) )
	{
		g_iZoneType = eZoneType_God ;
	}
	else if( eZone_Katacomb == iZone ) // �ϵμ���
	{
		for( int y = 0 ; y < MAX_GRIDY ; ++y )
		{
			for( int x = 0 ; x < MAX_GRIDX ; ++x )
			{
				g_krgCell[y][x].usHeight = 10000 ;

				//if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usHeight = 20000 ;
			}
		}


		// ����
		for( int y = 190 ; y < 590 ; ++y )
		{
			for( int x = 155 ; x < 160 ; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked ;				
			}
		}

		for( int y = 325 ; y < 457 ; ++y )
		{
			for( int x = 80 ; x < 120 ; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked ;
			}
		}

		// ����
		for( int y = 190 ; y < 590 ; ++y )
		{
			for( int x = 865 ; x < 868 ; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked ;
			}
		}

		for( int y = 325 ; y < 457 ; ++y )
		{
			for( int x = 903 ; x < 945 ; ++x )
			{
				if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ eTNCell_Blocked ;
			}
		}


	}
	else if( eZone_Stronghold == iZone )
	{
		g_iZoneType = eZoneType_Guild ;
	}
}
     


BOOL AddCrackError(int conn,int val,int Type)
{
	if( 0 >= conn || MAX_USER <= conn ) return FALSE ;
	//if (Type!=3 && Type!=8 && Type!=15)
	//{
	sprintf(temp,"cra point: %d  type: %d",val,Type);
	Log(temp,pUser[conn].AccountName,pUser[conn].IP);  
	//}

	//	�����û�� ���� ���������Ű���ʰ� �α׸� ��������.
	//if(Type==CRACK_SPEED_HACK4)
	//{	/*sprintf(temp,"cra point: %d  type: %d",val,Type);
	//	Log(temp,pUser[conn].AccountName,pUser[conn].IP);  */
	//	return TRUE;
	//}

	pUser[conn].NumError=pUser[conn].NumError+val;
	if	(pUser[conn].NumError>=30)
	{	SendClientMessage(conn,g_pMessageStringTable[_Bad_Network_Packets]);
		pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout ;
		CloseUser(conn);
		sprintf(temp,"cra char logout type: %d",Type);
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
	int irgPopMonsters[5] = { 0, 0, 0, } ;
    if( 0 < mNPCGen.pList[idx].iGroup ) // 1~2���� group�� �ش��Ѵ�. ������ �ʿ���.
    {
        if((mNPCGen.pList[idx].krgMonsterList[0].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[0].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[0].iPopCountPerTime ) irgPopMonsters[0] = 1 ; //bPopMonster = false ;
        if((mNPCGen.pList[idx].krgMonsterList[1].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[1].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[1].iPopCountPerTime ) irgPopMonsters[1] = 1 ; //bPopMonster = false ;
        if((mNPCGen.pList[idx].krgMonsterList[2].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[2].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[2].iPopCountPerTime ) irgPopMonsters[2] = 1 ; //bPopMonster = false ;
        if((mNPCGen.pList[idx].krgMonsterList[3].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[3].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[3].iPopCountPerTime ) irgPopMonsters[3] = 1 ; //bPopMonster = false ;
        if((mNPCGen.pList[idx].krgMonsterList[4].iMaxPopCount - mNPCGen.pList[idx].krgMonsterList[4].iCurPopCount) < mNPCGen.pList[idx].krgMonsterList[4].iPopCountPerTime ) irgPopMonsters[4] = 1 ; //bPopMonster = false ;
    }
  
    int iFollowerNO = 0 ;
    int iLeader = 0 ;
    for( int iCmd = 0 ; iCmd < eCmd_MaxCount ; ++iCmd )
    {
        if( eCmd_None == mNPCGen.pList[idx].krgCommand[iCmd].iCommand ) continue ;
        if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) )// && bPopMonster )
        {
            int iIndex = mNPCGen.pList[idx].krgCommand[iCmd].iIndex ;
			if( irgPopMonsters[iIndex] ) continue ;
            for( int iPop = 0 ; iPop < mNPCGen.pList[idx].krgCommand[iCmd].iCount ; ++iPop )
            {
                if( mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount >= mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ) break ;

                int mob = 0 ;            
                for( int iReadyMobIndex = 0 ; iReadyMobIndex < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ; ++iReadyMobIndex )
                {
                    if( 1 == mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1] )
                    {
                        mob = mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][0] ;
                
            			if  (mob<MAX_USER || mob >=MAX_MOB)
            			{   sprintf(temp,"err no emptymob leader: %d - %d",idx,mob);
            				Log(temp,"-system",0);
            				continue ;  // MobList�� �� á��.
            			}
		            	  
						/*
						#ifdef __DYNAMIC_LOG__
						if( pMob[mob].m_iDebugFlag || (eZoneType_Guild == g_iZoneType) )
						{ // debug_0503
							SYSTEMTIME st ;
							GetLocalTime( &st ) ;
							char chBuf[512] = { 0,0,0, } ;
							sprintf(chBuf, "GenerateMob(); %d��%d��%d��> Handle:%d, Tribe:%d, Mode:%d, FSM:%d, generateIndex:%d, ����:%d, �غ����:%d, �ִ��˼�:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, st.wDay, st.wHour, st.wMinute
								, mob, pMob[mob].MOB.snTribe, pMob[mob].Mode, pMob[mob].m_eFSM
								, idx, iReadyMobIndex, mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1], mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								) ;
							if( eZoneType_Guild == g_iZoneType ) WriteLog( chBuf, ".\\Log\\[DEBUG]Duruka.txt" ) ;
							else WriteLog( chBuf, pMob[mob].m_szLogFile ) ;
						}	
						#endif
						*/

						//if( pMob[mob].m_kLastTime.uiKilled > CurrentTime ) continue ;
						if( pMob[mob].IsWaitToPop() ) continue ;

						pMob[mob].GenerateIndex = idx ;
						pMob[mob].RouteType = mNPCGen.pList[idx].RouteType ;
            			pMob[mob].Formation = mNPCGen.pList[idx].Formation ;
						pMob[mob].Leader = 0 ;
						//pMob[mob].m_bSolo = true ;
						pMob[mob].m_iGroup = mNPCGen.pList[idx].iGroup ; 
		          	
           				// MOB ���׸�Ʈ ����Ʈ ����
           				if( eTNRout_FixPosition == mNPCGen.pList[idx].RouteType ) // don't move
           				{
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[i] ;
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[i] ;
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[i] ; // 0
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[i] ;
          					}
          				}
          				else if( eTNRout_RandomPopNLiveThereOnly == mNPCGen.pList[idx].RouteType ) // Random Pop
          				{
							pMob[mob].RouteType = eTNRout_MoveNRoam ;
          					int iPopArea = rand() % 5 ;
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[iPopArea] - mNPCGen.pList[idx].SegmentRange[iPopArea] + rand()%(mNPCGen.pList[idx].SegmentRange[iPopArea]*2+1) ;
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[iPopArea] - mNPCGen.pList[idx].SegmentRange[iPopArea] + rand()%(mNPCGen.pList[idx].SegmentRange[iPopArea]*2+1) ;
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[iPopArea] ;
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[iPopArea];

								g_kInfluenceMap.BuildInfluenceGrids( pMob[mob].SegmentListX[i], pMob[mob].SegmentListY[i], pMob[mob].m_krgInfluenceGrid, pMob[mob].m_iInfluenceGridSize ) ;
								if( 0 >= pMob[mob].m_iInfluenceGridSize )
								{
									pMob[mob].Mode = MOB_EMPTY;
									pMob[mob].MOB.szName[0]=0;							
									continue ;
								}
								else
								{
									int iArea = rand() % pMob[mob].m_iInfluenceGridSize ;
									pMob[mob].SegmentListX[i] = pMob[mob].m_krgInfluenceGrid[iArea].x + rand()%TN_GRID_SIZE ;
									pMob[mob].SegmentListY[i] = pMob[mob].m_krgInfluenceGrid[iArea].y + rand()%TN_GRID_SIZE ;
								}
          					}
          				}
          				else
          				{
           					for (int i=0;i<MAX_SEGMENT;i++)
           					{
								pMob[mob].SegmentListX[i] = mNPCGen.pList[idx].SegmentListX[i] - mNPCGen.pList[idx].SegmentRange[i] + rand()%(mNPCGen.pList[idx].SegmentRange[i]*2+1) ;
          						pMob[mob].SegmentListY[i] = mNPCGen.pList[idx].SegmentListY[i] - mNPCGen.pList[idx].SegmentRange[i] + rand()%(mNPCGen.pList[idx].SegmentRange[i]*2+1) ;
          						pMob[mob].SegmentRange[i] = mNPCGen.pList[idx].SegmentRange[i] ;
          						pMob[mob].SegmentWait[i] = mNPCGen.pList[idx].SegmentWait[i];

								g_kInfluenceMap.BuildInfluenceGrids( pMob[mob].SegmentListX[i], pMob[mob].SegmentListY[i], pMob[mob].m_krgInfluenceGrid, pMob[mob].m_iInfluenceGridSize ) ;
								if( 0 >= pMob[mob].m_iInfluenceGridSize )
								{
										pMob[mob].Mode = MOB_EMPTY;
									pMob[mob].MOB.szName[0]=0;
									continue ;
								}
								else
								{
									int iArea = rand() % pMob[mob].m_iInfluenceGridSize ;
									pMob[mob].SegmentListX[i] = pMob[mob].m_krgInfluenceGrid[iArea].x + rand()%TN_GRID_SIZE ;
									pMob[mob].SegmentListY[i] = pMob[mob].m_krgInfluenceGrid[iArea].y + rand()%TN_GRID_SIZE ;
								}
          					}
          				}		      

						/*
						if( eZoneType_Guild == g_iZoneType )
						{// debug_0503
							SYSTEMTIME st ;
							GetLocalTime( &st ) ;
							char chBuf[512] = { 0,0,0, } ;
							sprintf(chBuf, "[%d��%d��%d��] GenerateMob() > Tribe:%d, Handle:%d, Mode:%d, FSM:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, st.wDay, st.wHour, st.wMinute
								, pMob[mob].MOB.snTribe, mob, pMob[mob].Mode, pMob[mob].m_eFSM
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								) ;
							WriteLog( chBuf, ".\\Log\\[DEBUG]Duruka.txt" ) ;
						}	
						*/

						pMob[mob].MOB = mNPCGen.pList[idx].krgMonsterList[iIndex].kMobData ;
						pMob[mob].Init(mob);

            			int ttx = pMob[mob].SegmentListX[0];
            			int tty = pMob[mob].SegmentListY[0];
            			//int tret = GetEmptyMobGrid(mob,&ttx,&tty, pMob[mob].SegmentRange[0] );
						int tret = PickFreeMobGrid(mob,&ttx,&tty ) ;
            			if  (tret==FALSE)
            			{     
            				{
            					char chBuf[256] = { 0,0,0, } ;
            					sprintf(chBuf, "[GenerateMob] monster:%d, Tribe:%d, x:%d, y:%d \r\n", mob, pMob[mob].MOB.snTribe, ttx, tty ) ;
            					WriteLog( chBuf, ".\\monster_log\\[Log]FailToPop.txt" ) ;
            				}
			            
							pMob[mob].Mode = MOB_EMPTY;
            				pMob[mob].MOB.szName[0]=0;
            				continue;
            			}
            			pMob[mob].LastX = pMob[mob].TargetX = pMob[mob].SegmentX = ttx ;
            			pMob[mob].LastY = pMob[mob].TargetY = pMob[mob].SegmentY = tty ;
		            	
            			if( 0 > mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount ) mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount = 0 ;
            			++mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount ;
						mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1] = 0 ;
             			
						memset(pMob[mob].m_irgParty,0,sizeof(pMob[mob].m_irgParty));
						if( 0 < mNPCGen.pList[idx].iGroup ) // party�� ���
						{
							if( 0 == iIndex ) iLeader = mob; // Leader�� ��츸, ����
							else // Leader�� ������ ���Ŀ���, �� Follower�� ��츸, ����
							{
								pMob[mob].Leader = iLeader ;
                				pMob[iLeader].m_irgParty[iFollowerNO]=mob;
                				++iFollowerNO ;
                			}
						}
		     
						sprintf( pMob[mob].MOB.szName, "%d_%d", mNPCGen.pList[idx].krgMonsterList[iIndex].kMobData.snTribe, mob ) ; // �� 9��
						//////////////////////////////////////////////////////////////////////

						pMob[mob].Think( eTNAI_Pop, 0 ) ;
						pMob[mob].m_iDirection = mNPCGen.pList[idx].Formation;
            			S_SCP_INIT_OTHER_MOB sm ;
            			GetCreateMob( mob, &sm ) ;
             			pMobGrid[tty][ttx] = mob ;
            			GridMulticast( ttx, tty, (MSG_STANDARD*)&sm, 0) ;

						SYSTEMTIME st ;
						GetLocalTime( &st ) ;

						#ifdef __DYNAMIC_LOG__
						if( 0 < pMonsterData[pMob[mob].MOB.nTP].byQuest[eMonPrty_Reserved4] )
						{
							char chBuf[512] = { 0,0,0, } ;
							sprintf(chBuf, "GenerateMob(); %dyy%dmm%ddd %dhh%dmi%dss> Handle:%d, Tribe:%d, Mode:%d, FSM:%d, generateIndex:%d, ����:%d, �غ����:%d, �ִ��˼�:%d, Now:%u, Killed:%u, TimeRemained:%u, HP:%d, class(%d,%d) \r\n"
								, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
								, mob, pMob[mob].MOB.snTribe, pMob[mob].Mode, pMob[mob].m_eFSM
								, idx, iReadyMobIndex, mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[iReadyMobIndex][1], mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount
								, CurrentTime, pMob[mob].m_kLastTime.uiKilled, pMob[mob].m_kLastTime.uiKilled - CurrentTime
								, pMob[mob].MOB.nHP, pMob[mob].MOB.byClass1, pMob[mob].MOB.byClass2
								) ;

							WriteLog( chBuf, pMob[mob].m_szLogFile ) ;
						}	
						#endif

						if( eTNAudit_Boss & pMonsterData[pMob[mob].MOB.nTP].byQuest[eMonPrty_Reserved4] )
						{
							char chBuf[512] = { 0,0,0, } ;
							sprintf(chBuf, "[GenerateMob] %dyy%dmm%ddd %dhh%dms%dss, Boss(%d, %d) is summoned!!\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
								, pMob[mob].MOB.snTribe, mob ) ;
							WriteLog( chBuf, ".\\Log\\[Log]BossSystem.txt" ) ;
						}

						break ;
					}
				} //for( int iReadyMobIndex = 0 ; iReadyMobIndex < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ; ++iReadyMobIndex )            	
            } // for( int iPop = 0 ; iPop < mNPCGen.pList[idx].krgCommand[iCmd] ; ++iPop )
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
        CW_USEDEFAULT,   CW_USEDEFAULT, 640+8,   480,            // W,H[Menu��ġ�� 480]
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

	//LoadDump( "���ϸ�(Ȯ��������)" );

	srand( timeGetTime() ) ;

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

	/////////////// �����͸� �ε��Ѵ�. //////////////////////
	LoadWorldSettings() ; // zone ������ ���ؼ��� ���� ������ ����.
	LoadZoneSettings() ;
	LoadItemData() ;
	LoadSkillData() ;
	LoadMonsterData() ;	
	g_kScheduler.Load() ;
	QUEST_LoadTask();
	LoadSettingTxl() ;
	//LoadSettings() ;
	//LogRewardItems() ;

	LoadStrongholdData() ;
	g_kSiege.LoadData() ;

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

	FILE* fp = NULL ;

	Reboot();

	//PrintMapInfo() ;
	//g_kInfluenceMap.Print() ;

	RegisterMonstersToArea() ;


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
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[Load Generation.idx] 0:%d(%d,%d)~(%d,%d), 1:%d(%d,%d)~(%d,%d), 2:%d(%d,%d)~(%d,%d), 3:%d(%d,%d)~(%d,%d)"
				, pGenerationArea[0].dwIndex, pGenerationArea[0].snStartX, pGenerationArea[0].snStartZ, pGenerationArea[0].snEndX, pGenerationArea[0].snEndZ
				, pGenerationArea[1].dwIndex, pGenerationArea[1].snStartX, pGenerationArea[1].snStartZ, pGenerationArea[1].snEndX, pGenerationArea[1].snEndZ
				, pGenerationArea[2].dwIndex, pGenerationArea[2].snStartX, pGenerationArea[2].snStartZ, pGenerationArea[2].snEndX, pGenerationArea[2].snEndZ
				, pGenerationArea[3].dwIndex, pGenerationArea[3].snStartX, pGenerationArea[3].snStartZ, pGenerationArea[3].snEndX, pGenerationArea[3].snEndZ
				) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadGererationArea.txt" ) ;
		}

		fclose(fpInfo);
	}	else
	{	MessageBox(hWndMain,"Can't find GenerationArea.idx","REBOOTING ERROR",NULL);
	}

	int nTrimurity=0;
	for(int i=0; i<sInfo.nDataCount; i++)
	{	nTrimurity=pGenerationArea[i].dwIndex;
		if(nTrimurity<0 || nTrimurity>3) continue;	//	0:common, 1:����帶 2:�񽴴� 3:�ù�

		BYTE byCount=TrimurityArea.byTrimuriti[nTrimurity]++;
		TrimurityArea.pArea[nTrimurity][byCount]=pGenerationArea[i];
	}

	for( int iPopArea = 1 ; iPopArea < 4 ; ++iPopArea )
	{
		if( 0 == TrimurityArea.byTrimuriti[iPopArea] )
		{
			TrimurityArea.byTrimuriti[iPopArea] = 1 ;
			TrimurityArea.pArea[iPopArea][0] = TrimurityArea.pArea[0][0] ;
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

	//IsInRvR() ;
	PopMonstersForEvent() ;
	ExecuteEmergence() ;

	if	(DBServerAddress[0]==0)
	{	MessageBox(hWndMain,"Can't get Server Group Index. check [Locakip.txt] and [ServerList.txt]","Error",MB_OK|MB_SYSTEMMODAL);
		return TRUE;
	}
	DBServerPort=LocalPort+1000;
	MSGServerPort=LocalPort+2000;
	int * pip1 = (int*)LocalIP1;
	int * pip2 = (int*)LocalIP2;

	if(g_eCountryID == eCountryPhilippines)		//	�ʸ����� DBA�� ���¶��λ���Ѵ�
		ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip1,WSA_READDB,hWndMain);
	else
		ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip2,WSA_READDB,hWndMain);

	if	(ret==NULL)
	{	Log("err Can't connect to DB-Server.","-system",0);
		MessageBox(hWndMain,"Can't connect to DB-SERVER","REBOOTING ERROR",NULL);
		return 0;
	}	else
	{	//	DB���� �ڽ��� ������ �ʱ�ȭ�� ��û��.
		S_REQUEST sm; sm.wType=SSP_REQ_ZONE_INIT;
		DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm));
	}

	// �޽������������� ASYNC�� �����Ѵ�
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

	//	DB���� �ڽ��� ������ �ʱ�ȭ�� ��û��.
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
	// ���� ���ӹ�ȣ 6��.
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

	// ���� �����׷� ��ȣȮ��
    memset(FailAccount,0,sizeof(FailAccount));
	CurrentTime=timeGetTime();
	SetTimer(hWndMain, TIMER_SEC, TICKSIZE,NULL); 
	SetTimer(hWndMain, TIMER_HOUR, 3600000,NULL); 

	g_RankSys.ReadRankFile(ServerGroup);							//	�ֽź� ��ŷ���� ���ε�(�ֽŷ�ŷ->��ų�������� ����)
	if(ServerIndex+1==SERVER_KATANA3) g_Yut.HT_ReadSaveMoney();		//	īŸ��3���ϰ�� ������ ����������� ���´�.
	if(g_eCountryID == eCountryKorea)
	{
		g_GameEvent.Initialize(ServerIndex, g_kGameEvent);									//	�̺�Ʈ ���ε�
	}

	if( ServerIndex+1 == SERVER_KATANA3 )
	{
		g_pRentalStore = new CRentalStore;							//	īŸ��3 ���� �뿩���� ����
		g_pRentalStore->HS_SetEraseDay(g_dwRentalEraseDay);
		g_pRentalStore->HS_SetRentalTex(g_dwRentalTex);
		g_pRentalStore->HS_SetRentalTexMoney(g_dwRentalTexMoney);
		g_pRentalStore->HS_Init();

		TNCastle kOwner ;											//	īŸ��3 ���� ������Ȳ�� �˸���
		g_kSiege.get_Owner( &kOwner) ;
		g_iCastleOwner = kOwner.kGuild.iID;

		Msg_CastleUpdate sm; ZeroMemory(&sm, sizeof(sm));
		sm.wType = _Msg_CastleUpdate;
		sm.iCastleOwner = kOwner.kGuild.iID;
		MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
	}

	Msg_TrimuritiStatus nm; nm.wType = _Msg_TrimuritiStatus;		//	�ֽź� �����ڵ����͸� ��û�Ѵ�.(�ֽź���� ����)
	DBServerSocket.SendOneMessage((char*)&nm, sizeof(nm));

	if( SERVER_STRONGHOLD == g_iZoneID )								//	������ϰ�� ��������� msg�� �̿��� �����Ѵ�.
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
	  // Billing�� �������� ������ ������Ʈ��.
	  case  WSA_READBILL:
	  {     if (WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {  Log("err Billing Connection lost.","-system",0);
			   BillServerSocket.CloseSocket();
			   BillCounter = 720; // ��Ÿ�̸Ӱ� 0.25���̹Ƿ� 180�� �� 3���Ŀ� ������ 1ȸ �õ�.
			   return TRUE;
            }
	        if (BillServerSocket.Receive()==FALSE)
			{  Log("err bill receive fail","-system",0);
			   BillServerSocket.CloseSocket();
			   BillCounter = 720; // ��Ÿ�̸Ӱ� 0.5���̹Ƿ� 180�� �� 3���Ŀ� ������ 1ȸ �õ�.
			   return TRUE;
			}

			//char temp[256];
			int Error=0;
			int ErrorCode=0;
            while(1)
			{  char * Msg = BillServerSocket.ReadBillMessage(0, &Error,&ErrorCode);  // ���� ReadBillMessage(ũ�����+�������+���ڵ�����) 
       		   if (Msg==NULL) break;
			   if (Error==1 || Error==2)
			   {  sprintf(temp,"err readbill (%d),%d",Error,ErrorCode );
				  Log(temp,"-system",0);
				  break;
			   }  
			   ProcessBILLMessage(Msg);// , Manage.ReceiveSize);              // �۾� �ش� ������� Billing �� ����
			   
		    };
            break; 
	  }  break;
	  case  WSA_READITEM:
	  {     if (WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {  Log("err Item Connection lost.","-system",0);
			   ItemServerSocket.CloseSocket();
			   ItemCounter = 360; // ��Ÿ�̸Ӱ� 0.5���̹Ƿ� 180�� �� 3���Ŀ� ������ 1ȸ �õ�.
			   return TRUE;
            }
	        if (ItemServerSocket.Receive()==FALSE)
			{  Log("err Item receive fail","-system",0);
			   ItemServerSocket.CloseSocket();
			   ItemCounter = 360; // ��Ÿ�̸Ӱ� 0.5���̹Ƿ� 180�� �� 3���Ŀ� ������ 1ȸ �õ�.
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
				Log("err msg close entercritical section fail","-system",0); // ���߿� ����ũ	
				continue;
			}
			MSGServerSocket.CloseSocket();
			LeaveCriticalSection (&csConnecter);
		}


		int ret = TryEnterCriticalSection(&csConnecter);
		if	(ret==NULL)
		{	Log("err msg read entercritical section fail","-system",0); // ���߿� ����ũ
			return FALSE; 
			// Log�� �����߰ڴ�.
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
				if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� MSG Public���
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
				if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� MSG Public���
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
	// DB�� �������� ������ ������Ʈ��.
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
					if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� DBA Public���
					ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip ,WSA_READDB,hWndMain);
					//if (ret!=NULL) 
					//{	//	DB���� �ڽ��� ������ �ʱ�ȭ�� ��û��.
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
					if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� DBA Public���
					ret = DBServerSocket.ConnectServer(DBServerAddress,DBServerPort,*pip,WSA_READDB,hWndMain);
					//if (ret!=NULL) 
					//{	//	DB���� �ڽ��� ������ �ʱ�ȭ�� ��û��.
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
				if ( pUser[User].AccountName[0] != 0 )
				{	sprintf(temp,"clo fd %d-%d",pUser[User].Mode,pMob[User].Mode);
						Log(temp,pUser[User].AccountName,pUser[User].IP);

						if (pUser[User].Mode == USER_PLAY && pMob[User].MOB.szName[0] != 0 && time(0)-pUser[User].LoginTime != 0)
						{
							sprintf(temp,"Play,%d,%d,%d",time(0)-pUser[User].LoginTime,pMob[User].MOB.byLevel,pMob[User].MOB.snTribe);
							EventLog(temp,pUser[User].AccountName,pMob[User].MOB.szName,pUser[User].IP);
						}
				}	else
				{
					sprintf(temp,"clo fd %d-%d",pUser[User].Mode,pMob[User].Mode);
					Log(temp,"noname",0); 
				}
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
				  sprintf(temp,"err read (%d),%d",Error,ErrorCode );
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

		int User = GetEmptyUser();         //           CLIENT�� ���� ����
		if  (User==0 || User>=ValidUser || pUser[User].cSock.pRecvBuffer==NULL ||  pUser[User].cSock.pSendBuffer==NULL )
		{   Log("err accept fail - no empty","-system",0);
			TempUser.AcceptUser(ListenSocket.Sock);
			TempUser.CloseUser();
			break;
		}

        int ret = pUser[User].AcceptUser(ListenSocket.Sock);
		if	(ret==FALSE) 
		{	Log("dbg WSA_ACCEPT fail","-system",0);
			return TRUE;
		}

		//if(ServerIndex+1 == SERVER_TRIMURITI || ServerIndex+1 == SERVER_CHATURANGKA)
		//{
		//	for(int i=0; i<MAX_USER; i++)		//	���� ����IP���� �������� ������ �������(�ֹ� ����������Ų��)
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

		//	Billing Server�� ���ٿ��� �˸���.
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

//                    Ŭ���̾�Ʈ  �޽��� ó����

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void ProcessClientMessage(int conn,char*msg)
{ 
	PHEADER header = (PHEADER)msg;

	if	(ServerDown>=120) return;

	//////////////// Speedhack, Speed hack check ////////////////////////////
	if ( pUser[conn].TickDiff != 0 )
	{
		if ( (int)( header->dwClientTick - CurrentTime ) > (int)(pUser[conn].TickDiff + 20000) )	   //	servertick���� 10sec���� ��Ŷ�� �ð��
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
	{	pUser[conn].LastReceiveTime = SecCounter;// 0.5��.
	}

	WORD wType = 0 ;
	if(pUser[conn].byTradeMode==1)
	{	wType = header->wType;
		if(wType!=_MSG_REQMobByID && wType!=_MSG_GMMode && wType!=CSP_REQ_APPEAL_CHAT && wType!=_MSG_Chat && wType!=_MSG_Broadcast &&
			wType!=CSP_REQ_WHISPER_CHAT && wType!=CSP_REQ_CHAT && wType!=_MSG_MobStore_Buy && wType!=_MSG_MobStore) return;

	}

	switch(header->wType)
	{
	case _Msg_MyRentalItemList:					//	�ڽ��� ��Ź���� �����ڸ���Ʈ�� ��û�Ѵ�.
		{	Msg_MyRentalItemList * m = (Msg_MyRentalItemList*)msg;
			
			g_pRentalStore->HS_GetItemList(pMob[conn].MOB.szName, m->stItem);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemList:					//	Ư�� ��Ź������ �����۸���Ʈ�� ��û�Ѵ�.
		{	Msg_RentalItemList * m = (Msg_RentalItemList*)msg;
			
			g_pRentalStore->HS_GetItemList(m->dwStoreIndex, m->stItem);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemAdd:					//	��Ź������ �ڽ��� �������� ����Ѵ�.
		{	Msg_RentalItemAdd * m = (Msg_RentalItemAdd*)msg;
			
			if(m->dwIndex<0 || m->dwIndex>=pMob[conn].byMaxInven) m->byResult = 1;
			DWORD dwMoney = m->dwMoney; 
			bool bRet = g_pRentalStore->HS_bAddItem(pMob[conn].MOB.szName, m->dwStoreIndex, pMob[conn].MOB.Inven[m->dwIndex], &dwMoney, m->byHour);
			if(bRet) 
			{	//	������ ���߰� ������
				m->byResult = 0;
				ZeroMemory(&pMob[conn].MOB.Inven[m->dwIndex], sizeof(pMob[conn].MOB.Inven[m->dwIndex]));

				pMob[conn].DecGold(dwMoney);
				m->dwMoney = pMob[conn].MOB.nRupiah;
			}	//	������ ���߰� ���н�
			else
				m->byResult = 1;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalItemCancel:					//	��Ź�������� �ڽ��� �÷����� �������� ��ҿ�û�Ѵ�.
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

				S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;		//	��Ź��ҷ� ���� �κ��� ������ ����
				sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
				sm.byIndex=iEmpty; sm.sitem=pMob[conn].MOB.Inven[iEmpty];
				pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm));
			}
			else
				m->byResult = 1;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalGetItem:					//	����������� ���´�.
		{	Msg_RentalGetItem * m = (Msg_RentalGetItem*)msg;
			
			STRUCT_ITEM stItem;
			int iCount = g_pRentalStore->HS_iGetStockItemCount(pMob[conn].MOB.szName);
			int iEmpty = GetEmptyInvenCount(conn);
			int iIndex = 0;
			if(iCount>iEmpty) iCount = iEmpty;	//	��� �ִ� ��ŭ�� �����۸��� �޾ƿ´�.
			for(int i=0; i<iCount; i++)
			{
				if(!g_pRentalStore->HS_bGetStockItem(pMob[conn].MOB.szName, &stItem)) continue;

				iIndex = GetEmptyInven(conn);
				if(iIndex<0 || iIndex>=pMob[conn].byMaxInven) continue;

				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=iIndex; nm.sitem=stItem;
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
			}
			if(iCount>0 && iEmpty>0) pUser[conn].cSock.SendMessage();
		}	break;
	case _Msg_RentalGetMoney:					//	������ǾƸ� ���´�.
		{	Msg_RentalGetMoney * m = (Msg_RentalGetMoney*)msg;
			
			DWORD dwMoney = 0;
			if(m->byType == 1)
			{
				if(!g_pRentalStore->HS_bGetMoney(pMob[conn].MOB.szName, &dwMoney, false)) return;
				pMob[conn].IncGold(dwMoney);
			}
			else
				if(!g_pRentalStore->HS_bGetMoney(pMob[conn].MOB.szName, &dwMoney)) return; 

			m->dwMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_RentalTex:
		{	Msg_RentalTex * m = (Msg_RentalTex*)msg;

			TNCastle kOwner ;
			g_kSiege.get_Owner( &kOwner) ;
			if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	������ ������尡 �ƴϸ� ���ȵ�
			if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	���϶��ڰ� �ƴϸ� ���ȵ�

			g_pRentalStore->HS_SetRentalTex(m->byTex);
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	//case _Msg_RentalGetTexMoney:
	//	{	Msg_RentalGetTexMoney * m = (Msg_RentalGetTexMoney*)msg;
	//		
	//		DWORD dwMoney = 0;
	//		TNCastle kOwner ;
	//		g_kSiege.get_Owner( &kOwner) ;
	//		if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	������ ������尡 �ƴϸ� ���ȵ�
	//		if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	���϶��ڰ� �ƴϸ� ���ȵ�

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
			TNCastle kOwner ;
			//STRUCT_RENTALITEM	stItem[MAX_USERRENTALITEM];
			
			g_kSiege.get_Owner( &kOwner) ;
			if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) bRet = false;	//	������ ������尡 �ƴϸ� ���ȵ�
			if(pUser[conn].nGuildLevel != eGuildMaster) bRet = false;		//	���϶��ڰ� �ƴϸ� ���ȵ�

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

			bRet &= g_pRentalStore->HS_bBuyItem(iStoreItemIndex, m->stItem);
			if(bRet)
			{
				m->byResult = 0;
				pMob[conn].MOB.Inven[iInvenIndex] = m->stItem;

				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=iInvenIndex; nm.sitem=pMob[conn].MOB.Inven[iInvenIndex];
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
			}
			else
				m->byResult = 1;

			m->dwMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_YutBet:
		{	Msg_YutBet * m = (Msg_YutBet*)msg;

			BOOL bRet = true;
			WORD wCount = 0;
			while(1)
			{
				if(!g_Yut.HT_bIsBetOn()) { bRet = false; break; }

				if(m->byPosition<0 || m->byPosition>=MAX_POSITION) 
					bRet = false;
				else
				{
					for(int i=0; i<MAX_ONEINVEN*2; i++)
					{
						if(m->wCount[i]==0) continue;
						if(pMob[conn].byMaxInven<=i) { bRet=false; break; }
						if((pMob[conn].MOB.Inven[i].snIndex+HT_PARAMTYPE_ITEM_START-1) != eItem_GoldSmall) { bRet=false; break; }
						if(pMob[conn].MOB.Inven[i].byCount<m->wCount[i]) { bRet=false; break; }
					}
				}
				break;
			}

			if(!bRet)	//	������ �ִ� ��Ŷ�� ���
			{
				m->byResult = 1;
			}
			else
			{
				m->byResult = 0;
				for(int i=0; i<pMob[conn].byMaxInven; i++)
				{
					if(m->wCount[i] == 0) continue;
					wCount += m->wCount[i];
					if(pMob[conn].MOB.Inven[i].byCount == m->wCount[i])
						ZeroMemory(&pMob[conn].MOB.Inven[i], sizeof(pMob[conn].MOB.Inven[i]));
					else
						pMob[conn].MOB.Inven[i].byCount -= m->wCount[i];
				}
			}

			if(m->byResult == 0)
                g_Yut.HT_wUserBet(pMob[conn].MOB.szName, (WORD)(m->byPosition), wCount);

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
	case _Msg_YutMoney:
		{	S_REQUEST * m = (S_REQUEST*) msg;

			S_RESULT sm; sm.wType = m->wType;
			DWORD dwMoney = g_Yut.HT_GetMoney(pMob[conn].MOB.szName);
			DWORD dwFirstMoney = dwMoney;
			if(dwMoney<=0)
			{
				sm.nResult = REPLY_YUTMONEY_NOHAVEMONEY; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm)); break;
			}
			
			BYTE byMax=0; 
			BYTE byItemCount = 0;
			g_ParamMgr.HT_bGetItemMaxCount( eItem_GoldSmall, &byMax );
			int nYutGold = eItem_GoldSmall - HT_PARAMTYPE_ITEM_START + 1;
			int nItemIndex = 0;

			for(int i=0; i<pMob[conn].byMaxInven; i++)
			{
				if(pMob[conn].MOB.Inven[i].snIndex == 0)	//	������� ��� �������� ä���
				{
					pMob[conn].MOB.Inven[i].snIndex = nYutGold;
					pMob[conn].MOB.Inven[i].snDurability = pItemData[nYutGold].sMaxDur;
					if(dwMoney>byMax)
					{
                        pMob[conn].MOB.Inven[i].byCount = byMax;
						dwMoney -= byMax;
					}
					else
					{
                        pMob[conn].MOB.Inven[i].byCount = (BYTE)dwMoney;
						dwMoney = 0;
					}
				}
				else
				{	nItemIndex = pMob[conn].MOB.Inven[i].snIndex+HT_PARAMTYPE_ITEM_START-1;
					if(nItemIndex!=eItem_GoldSmall || pMob[conn].MOB.Inven[i].byCount >= byMax) continue; 
					if((byItemCount + dwMoney) > byMax) 
					{
						pMob[conn].MOB.Inven[i].byCount = byMax;
						dwMoney -= (byMax-byItemCount);
					}
					else
					{	pMob[conn].MOB.Inven[i].byCount += (BYTE)dwMoney;
						dwMoney = 0;
					}
				}

				S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
				nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
				nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
				pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));

				if(dwMoney<=0) break;
			}

			g_Yut.HT_SetYutMoney(pMob[conn].MOB.szName, dwMoney);

			if(dwMoney >= dwFirstMoney)
                sm.nResult = REPLY_YUTMONEY_INVENFULL;
			else if(dwMoney<dwFirstMoney && dwMoney>0)
				sm.nResult = REPLY_YUTMONEY_PART;
			else
				sm.nResult = REPLY_YUTMONEY_SUCCESS;

			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}	break;
	case _Msg_SetSalesRate:
		{	Msg_SetSalesRate *m = (Msg_SetSalesRate*) msg;

			if(ServerIndex+1 != SERVER_KATANA3) break;

			if(m->byType==eSearch)						//	����
			{
				m->byRate = g_byCastleSalesRate;
				m->dwMoney = g_dwCastleSalesMoney;
			}
			else if(m->byType==eRun)					//	��������
			{
				TNCastle kOwner ;
				g_kSiege.get_Owner( &kOwner) ;
				if(pMob[conn].MOB.nGuildID != kOwner.kGuild.iID ) break;	//	�ش��尡 �ƴϸ� �̿�Ұ�
				if(pUser[conn].nGuildLevel != eGuildMaster) break;			//	���϶��ڰ� �ƴϸ� ���ȵ�

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

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
	case _Msg_GetMoney:
		{	Msg_GetMoney *m = (Msg_GetMoney*) msg;

			m->byResult = S_FALSE;
			int nType = m->nType;

			if(ServerIndex+1 != SERVER_KATANA3)					//	���� ��ȸ �� ã��� ���� īŸ��3�������� ����ȴ�.
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}

			TNCastle kOwner ;
			g_kSiege.get_Owner( &kOwner) ;
			if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID)		//	������ ������尡 �ƴϸ� ���ȵ�
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}
			if(pUser[conn].nGuildLevel != eGuildMaster)			//	���϶��ڰ� �ƴϸ� ���ȵ�
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
				return; 
			}

			switch(nType)
			{
			case eGetMoneyYut:
				{
					if(ServerIndex+1 != SERVER_KATANA3) break;

					TNCastle kOwner ;
					g_kSiege.get_Owner( &kOwner) ;
					if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	������ ������尡 �ƴϸ� ���ȵ�
					if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	���϶��ڰ� �ƴϸ� ���ȵ�

					m->byResult = S_OK;
					int nGold = (int)g_Yut.GetOwnerMoney();
					int nPrice = 0;
					if(!g_ParamMgr.HT_bGetItemSellRupiah(eItem_GoldSmall, &nPrice))
					{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); 
						return; 
					}

					__int64 nMoney = nGold * nPrice;
					if(nMoney>2000000000) nMoney = 2000000000;
					if(m->byAction == eRun)
					{
						pMob[conn].IncGold((int)nMoney);
						g_Yut.SetOwnerMoney(0);
						m->dwMoney = pMob[conn].MOB.nRupiah;
					}
					else 
						m->dwMoney = (DWORD)nMoney;
				}	break;
			case eGetMoneySale:								//	Msg_SetSalesRate, Msg_RentalGetTexMoney ������� �����ϰ� �ִ�
				{												//	���� �����ص� ������� �κ��ε�.
					int nMoney = (int)g_dwCastleSalesMoney;

					if(m->byAction == eRun)
					{
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
					TNCastle kOwner ;
					g_kSiege.get_Owner( &kOwner) ;
					if(kOwner.kGuild.iID!=pMob[conn].MOB.nGuildID) break;	//	������ ������尡 �ƴϸ� ���ȵ�
					if(pUser[conn].nGuildLevel != eGuildMaster) break;		//	���϶��ڰ� �ƴϸ� ���ȵ�

					if(m->byAction == eRun)
					{
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
				if  (l<4 || l>=SZNAME_LENGTH)  return;        // 4�� �̸� �Ǵ� 26�� �ʰ��� X
				for (int j=0; j<l; j++)
				{	 char x = m->szCharName[j];
					//  ����,���ĺ��� ���
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

			pUser[conn].Mode = USER_CREWAIT;     // LOGIN�� ĳ���� ������ ����.<����> ���� ó��.
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

			pUser[conn].Mode = USER_CREWAIT;     // ����� ������ ��� CREWAIT�� ����.
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

			if(g_eCountryID != eCountryKorea)
			{
				MSG_STANDARD sm; sm.wType = _Msg_VersionCheck;
				if(g_snVersion[0]!=pData->snVersion[0] || g_snVersion[1]!=pData->snVersion[1] || g_snVersion[2]!=pData->snVersion[2] || g_snVersion[3]!=pData->snVersion[3])
				{
					sm.nID = 1; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
					CloseUser(conn);

					sprintf(temp,"err Dismatch Client-Server Version!!",pUser[conn].AccountName);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					return;
				}
				else
				{	sm.nID = 0; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
				}
			}

			sprintf(temp,"dbg account:%s request move zone",pUser[conn].AccountName);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			if	(pUser[conn].Mode!=USER_ACCEPT)
			{	SendClientMessage(conn,g_pMessageStringTable[_Move_zone_Wait]);
				CrackLog(conn,"accountlogin");
				pUser[conn].cSock.SendMessage();
				sprintf(temp,"dbg account:%s request move zone fail1",pUser[conn].AccountName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout ;
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
			{	SendClientResult(conn, pData->wType, 16);	//	16 �����ڵ�
				pUser[conn].cSock.SendMessage();
				sprintf(temp,"dbg account:%s request move zone fail2",pUser[conn].AccountName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				return;
			}

			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_MOVE_ZONE_SERVER)))
			{	Log("err movezone DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
			pUser[conn].Mode = USER_LOGIN; // ������ USER_ACCEPT����.
			pMob[conn].Mode   = MOB_EMPTY;
			pUser[conn].LoginTime = time(0);
			if(pData->dwEvent > 0) pUser[conn].m_dwEvent = pData->dwEvent;

			if ( pData->szCharName[0] != 0 )
			{
				sprintf(temp,"Login,0,%d,%d",pMob[conn].MOB.byLevel,pMob[conn].MOB.snTribe);
				EventLog(temp,pUser[conn].AccountName,pMob[conn].MOB.szName,pUser[conn].IP);
			}
		}	break;
	case CSP_REQ_CHAR_SELECT:
		{
			S_CSP_REQ_CHAR_SELECT * m = (S_CSP_REQ_CHAR_SELECT *) msg;

			m->szCharName[SZNAME_LENGTH-1] = 0; m->szCharName[SZNAME_LENGTH-2] = 0;

			S_SSP_REQ_CHAR_SELECT sData;
			sData.wType = SSP_REQ_CHAR_SELECT;
			sData.wPDULength = sizeof(S_SSP_REQ_CHAR_SELECT)-sizeof(HEADER);
			strncpy(sData.szCharName, m->szCharName, SZNAME_LENGTH);
			sData.byConnectType = m->byConnType;

			if(!DBServerSocket.SendOneMessage((char*)&sData,sizeof(S_SSP_REQ_MOVE_ZONE_SERVER)))
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
			{	sprintf(temp, "err initchar1 - not USER_SELCHAR mode:%d", pUser[conn].Mode);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout ;
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

			pUser[conn].Mode	= USER_CHARWAIT;     // LOGIN�� ĳ���� ������ ����.
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
			// ���� ����ġ�� �Ʒ��� ����.
			if	( pUser[conn].SelChar.Score[m->Slot].Level>=FREEEXP && pUser[conn].SelChar.Score[m->Slot].Level<999 && BILLING == 2)  //2:���� ���� ����.
			{	if	(pUser[conn].Billing<=1) 
				{	
					if	(pUser[conn].ReqBillSec!=0 && pUser[conn].ReqBillSec<SecCounter-10)
					{	
						pUser[conn].ReqBillSec=0;
                        pUser[conn].Billing=5; 
					}	else
					{
						SendClientMessage(conn,g_pMessageStringTable[_NN_Wait_Checking_Billing]);	// ����->������ ������û ��Ŷ�� ������ ���� ������ ���û
						SendBilling(conn,pUser[conn].AccountName,1,1);								// �������Ķ��Ÿ, ������������ ���� ��û
					}
					// 
					return;
				}
                if	(pUser[conn].Billing==3) 
				{	sprintf(temp,g_pMessageStringTable[_DN_Not_Allowed_Account],FREEEXP);
					SendClientMessage(conn,temp);
					SendClientSignalParm(conn,0,_MSG_BillingPage,0);return;
				}//���⼭ Ȩ�������� ���� ������?
				if	(pUser[conn].Billing==4) { SendClientMessage(conn,g_pMessageStringTable[_NN_Using_Other_Server_Group]);return;}//���⼭ Ȩ�������� ���� ������?
				if	(pUser[conn].Billing==5) 
				{	;// 5�ʳ��� ������ �亯�� ���ϸ�, ������ 5�� ���� �ٲ��. ��, �ƹ� �޽��� ���� �α����� �ȴ�.
				}
			}
			if	( pUser[conn].SelChar.Score[m->Slot].Level>=FREEEXP && pUser[conn].SelChar.Score[m->Slot].Level<999 && BILLING == 3 && pUser[conn].SelChar.Score[m->Slot].Level>=1000)  //3:�׽�Ʈ
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
			pUser[conn].Mode	= USER_CHARWAIT;     // LOGIN�� ĳ���� ������ ����.
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

			if(g_iZoneID == SERVER_STRONGHOLD)			//	������� ��Ȱ
			{	
				if(pMob[conn].MOB.nRupiah < 20000) 
				{	pMob[conn].Regen(0, REGEN_TYPE_REGEN);
					return;
				}
				if(m->byConnType == REGEN_TYPE_ARENA)
				{
					pMob[conn].MOB.nRupiah -= 20000;
					
					if(!g_kArena.IsProgressed()/*g_iIsArenaOpend*/) g_dwArenaMoney += 20000;
					if(g_dwArenaMoney>=MONEY_ARENAEVENT)					//	ARENA �̺�Ʈ �߻����� - 1���̻��� �Ʒ����Ӵϰ� �ְ�
						if(!g_kArena.IsProgressed() && g_iBattleForStronghold==0)		//	ARENA �̺�Ʈ ���������̰� ����� ��Ȳ�� �ƴϰ�
						{	struct tm when; time_t now;						//	0~2��, 10~24�� ���̸� �̺�Ʈ�� �߻��Ѵ�.
							time(&now); when = *localtime(&now);
							if(when.tm_hour<2 || when.tm_hour>10) g_kArena.Start( (int)g_dwArenaMoney ) ; //TriggerEvent( conn, 66, pMob[conn].TargetX, pMob[conn].TargetY, 0 ) ;
						}

					pMob[conn].Regen(0, REGEN_TYPE_ARENA);
				}
				else
					pMob[conn].Regen(0, REGEN_TYPE_REGEN);
			}
			else if(g_iZoneID == SERVER_KATANA3)		//	�������� ��Ȱ
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
			else										//	���, ���������� ������ ��Ȱ
                pMob[conn].Regen(0, REGEN_TYPE_REGEN);

		}	break;
	case _MSG_TrimuritySelect:
		{	MSG_TrimuritySelect * m = (MSG_TrimuritySelect *) msg;

			if(m->byType==0)	//	�ֽ�ī��Ʈ ��ȸ
			{
				m->nBrahmaCount = g_iBrahmaCount;
				m->nVishnuCount = g_iVishnuCount;
				m->nSivaCount = g_iSivaCount;
				m->dwMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
				break;
			}

			int nMoney=0; int nBraman = 0;
			if(strcmp(pMob[conn].MOB.szName, m->CharName))									//	�ڽ��� �ƴ� ���
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Select_Others]); break;
			}

			if(pUser[conn].nGuildIndex!=0 && pMob[conn].MOB.byTrimuriti!=0)					//	������ ���
			{	SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Select_Guild]); break;
			}

			if(pMob[conn].MOB.byLevel < TRIMURITY_LEVEL) {SendClientMessage(conn, g_pMessageStringTable[_Trimuriti_Select_Want_Level]); break;}

			if(pMob[conn].MOB.byTrimuriti != 0)
			{	
				byte byFromTri = pMob[conn].MOB.byTrimuriti;
				byte byToTri = m->byTrimuriti;
				short snFrom = 0;
				short snTo = 0;
				if(byFromTri == eTNClan_Brahma) snFrom = g_iBrahmaCount;
				else if(byFromTri == eTNClan_Vishnu) snFrom = g_iVishnuCount;
				else if(byFromTri == eTNClan_Siva) snFrom = g_iSivaCount;
				else return;													//	�̿��� ���(gm�ɸ�)�� �ֽź����� �Ҽ�����
				if(byToTri == eTNClan_Brahma) snTo = g_iBrahmaCount;
				else if(byToTri == eTNClan_Vishnu) snTo = g_iVishnuCount;
				else if(byToTri == eTNClan_Siva) snTo = g_iSivaCount;
				else return;													//	�̿��� ���(gm�ɸ�)�� �ֽź����� �Ҽ�����.

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
				int nIndex1=7134-HT_PARAMTYPE_ITEM_START+1;		//	�����ּ���(7134, 15��)
				for(int i=0; i<pMob[conn].byMaxInven; i++)
				{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex1) 
					{	nCount += pMob[conn].MOB.Inven[i].byCount;
						if(nCount>15) break;
					}
				}
				if(nCount<15) {SendClientMessage(conn, g_pMessageStringTable[_Trimuriti_Select_Want_Resource]); break;}

				nCount=15;
				//	�κ����� �����ּ����������� �����Ѵ�.
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
				BOOL bRet=GetTrimurityArea(conn, nX, nZ);	//	�ֽ��� ���� �ɸ��Ͱ� �ֽź���� ������Ҹ� 1�������� �ٲپ��ش�.
				if(!bRet) {CloseUser(conn); return;}
				int tret = GetEmptyMobGrid(conn,&nX,&nZ);
				if	(tret==FALSE)
				{	sprintf(temp,"err no empty space at _MSG_TrimuritySelect x:%d y:%d",nX,nZ);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					int tret = GetEmptyMobGrid(conn,&nX,&nZ);
					if	(tret==FALSE)
					{	Log("err too many people near start point => 20",pUser[conn].AccountName,pUser[conn].IP);
						SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]);
						CloseUser(conn); return;
					}
				}

				nBraman = (int)(pMob[conn].MOB.nBramanPoint * 0.3);
				pMob[conn].DecGold(nMoney);					//	�����ֽ��� ������� ���� ���δ�.(���� �ֽ��� ���� ���� ���� �ȱ��δ�)
				pMob[conn].MOB.bySaveZone = ServerIndex+1;
				pMob[conn].MOB.snSaveX = nX;
				pMob[conn].MOB.snSaveZ = nZ;
				pMob[conn].MOB.nBramanPoint -= nBraman;
				pMob[conn].NotifyUpdateUIMsg() ;

				Msg_BramanBonus sm; sm.wType = _Msg_BramanBonus;		//	db�� ��� ����Ʈ �峳ġ�� �˸���.
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
			sm.byBgColor		= 14;			    // ä�� �޼��� ����
			sm.byTextColor		= 14;			    // ä�� �޼��� ����
			sm.byMsgType		= MESSAGE_ZONE;
			sm.byTrimuriti		= m->byTrimuriti;

			char pTri[16] = {0,};
			if(m->byTrimuriti==eTNClan_Brahma) sprintf(pTri, g_pMessageStringTable[_Brahma]);
			if(m->byTrimuriti==eTNClan_Vishnu) sprintf(pTri, g_pMessageStringTable[_Vishnu]);
			if(m->byTrimuriti==eTNClan_Siva) sprintf(pTri, g_pMessageStringTable[_Siva]);
			sprintf(sm.szMsg, g_pMessageStringTable[_Change_Trimuriti], pMob[conn].MOB.szName, pTri);
			SendToAll((MSG_STANDARD*)&sm);		//	������ �ֽż����� �����Ѵ�.

			//	�ֽŽ�ų�� �����Ѵ�.
			//	�ش����� �ֽŽ�ų ����Ʈ�� ���޵ȴ�.

			SendToAll((MSG_STANDARD*)m);		//	������ �ֽż����� �����Ѵ�.
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
			int nIndex=7116-HT_PARAMTYPE_ITEM_START+1;		//	��ȥ�� ����(7116, 10��)
			for(int i=0; i<pMob[conn].byMaxInven; i++)
			{	if(pMob[conn].MOB.Inven[i].snIndex==nIndex) 
				{	nCount += pMob[conn].MOB.Inven[i].byCount;
					if(nCount>10) break;
				}
			}
			if(nCount<10) {SendClientMessage(conn, g_pMessageStringTable[_Trimurity_Point_Want_Resource]); break;}

			nCount=10;
			//	�κ����� ��ȥ�� ���� �������� �����Ѵ�.
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
		{	S_RESULT sm;	sm.wType = SCP_RESP_SAVE_POSITION;

			//	������Ұ� �������� �������� ��Ŷ���� üũ�ϴ� �κ��߰��ؾ��Ѵ�.
			//	SAVEOBJECT, MOB DISTANCE ERROR	: ���� ��Ŷ�� ����� �����Ѵ�.
			//	sm.nResult = 1;
			//	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT));
			//	return;

			int nMap = 40001+ServerIndex; DWORD dwLevel = 0;
			if(!g_ParamMgr.HT_bGetMapLevelRestrict( nMap, &dwLevel ))
			{	sm.nResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT)); return;
			}
			if(pMob[conn].MOB.byLevel < dwLevel)
			{	sm.nResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_RESULT)); return;
			}

			//	������ MOB�� SAVE POSITION���� ������ �����Ѵ�.
			pMob[conn].MOB.bySaveZone = ServerIndex+1;
			pMob[conn].MOB.snSaveX = pMob[conn].TargetX;
			pMob[conn].MOB.snSaveZ = pMob[conn].TargetY;

			//	���� ��Ŷ�� ����� �����Ѵ�.
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

			if(m->byFace!=pMob[conn].MOB.byFace)	//	�󱼺���
			{	if(m->byFace>BEAUTY_OLD_FACE) nItemIndex = eItem_ChangeFace;
				else nItemIndex = eItem_ChangeOldFace;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash1);
				nTotCash += nCash1;
			}
			if(m->byHead!=pMob[conn].MOB.byHead)	//	�Ӹ�����
			{	if(m->byHead>BEAUTY_OLD_HAIR) nItemIndex = eItem_ChangeHair;
				else nItemIndex = eItem_ChangeOldHair;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash2);
				nTotCash += nCash2;
			}
			if(m->snTribe!=pMob[conn].MOB.snTribe)	//	����ȯ
			{	nItemIndex = eItem_ChangeSex;
				bRet &= g_ParamMgr.HT_bGetItemCash(nItemIndex, &nCash3);
				nTotCash += nCash3;
			}


			if(nTotCash<=0 || !bRet)
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty)); break;	//	�������� �˸�.
			}

			if(!bFree)	//	������ ���
			{
				if(pUser[conn].m_nCash<nTotCash)
				{	m->byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty)); break;	//	ĳ�������� �˸�.
				}
				
				pUser[conn].m_nCash -= nTotCash;	
			}

			m->nCash = pUser[conn].m_nCash;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_Beauty));				//	���漺���� �˸�.

			if(!bFree)	//	������ ���
			{
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
					nm.wType=_Msg_Cash; nm.nID=conn; 
					nm.byType=eRun; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

					if(m->byFace!=pMob[conn].MOB.byFace)	//	�󱼺���
					{	nm.nCash=nCash1; nm.snItemIndex = eItem_ChangeFace; 
					}
					if(m->byHead!=pMob[conn].MOB.byHead)	//	�Ӹ�����
					{	nm.nCash=nCash2; nm.snItemIndex = eItem_ChangeHair; 
					}
					if(m->snTribe!=pMob[conn].MOB.snTribe)	//	����ȯ
					{	nm.nCash=nCash3; nm.snItemIndex = eItem_ChangeSex; 
					}
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
					nm.wType=_Msg_Cash2; nm.ID=conn; 
					nm.C_Type = 3; 
					nm.GameServer[0] = 'T'; nm.GameServer[1] = '0'+ServerGroup; nm.GameServer[2] = 'a'+ServerIndex;
					strcpy(nm.Order_Type,"I0");
					strncpy(nm.User_id, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					sprintf(nm.User_reg_no, "%d", pUser[conn].ssn1);
					unsigned char  *cIP = (unsigned char *) &(pUser[conn].IP);
					sprintf(nm.User_IP, "%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);

					if(m->byFace!=pMob[conn].MOB.byFace)	//	�󱼺���
					{	nm.Amount=-nCash1; sprintf(nm.Item_no, "%d", eItem_ChangeFace);
					}
					if(m->byHead!=pMob[conn].MOB.byHead)	//	�Ӹ�����
					{	nm.Amount=-nCash2; sprintf(nm.Item_no, "%d", eItem_ChangeHair);
					}
					if(m->snTribe!=pMob[conn].MOB.snTribe)	//	����ȯ
					{	nm.Amount=-nCash3; sprintf(nm.Item_no, "%d", eItem_ChangeSex);
					}
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
			}

			sprintf(temp,"beauty %s Face(%02x->%02x), Head(%02x->%02x), Tribe(%04x->%04x)",pMob[conn].MOB.szName,m->byFace,pMob[conn].MOB.byFace,m->byHead,pMob[conn].MOB.byHead,m->snTribe,pMob[conn].MOB.snTribe); 
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			if(m->byFace!=pMob[conn].MOB.byFace) pMob[conn].MOB.byFace = m->byFace;		//	�󱼺���
			if(m->byHead!=pMob[conn].MOB.byHead) pMob[conn].MOB.byHead = m->byHead;		//	�Ӹ�����
			if(m->snTribe!=pMob[conn].MOB.snTribe) pMob[conn].MOB.snTribe = m->snTribe;	//	����ȯ

			// �� ������ ������ mob�鿡�� �����Ѵ�.
			int tx = pMob[conn].TargetX; int ty = pMob[conn].TargetY;
			S_SCP_INIT_OTHER_MOB sOther;
			GetCreateMob(conn,&sOther); 
			GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn);
		}	break;
	case _MSG_CLASS:
		{	MSG_CLASS* m = (MSG_CLASS*)msg;

			STRUCT_ITEM* sour = NULL;	//	�κ��� �������� �־��ش�.
			int	emptyinven = GetEmptyInven(conn);		
			if	(emptyinven<0 || emptyinven>=pMob[conn].byMaxInven) 
			{	SendClientMessage(conn, g_pMessageStringTable[_Class_Get_Item_Fail]);
				return;
			};

			bool bRet = false;
			if(m->byClass1==CLASS_LEVEL1)
			{	if(pMob[conn].MOB.byClass1!=CLASS_LEVEL0) break;		//	0�������� 1�������� �����ϴ�.
				if(pMob[conn].MOB.byClass2!=m->byClass2) break;			//	1�������� byClass2(����Ŭ����)�� �ٲܼ� ����.
				pMob[conn].MOB.byClass1=CLASS_LEVEL1; bRet=true; 		//	1����������
			}	else
			if(m->byClass1==CLASS_LEVEL2)
			{	int nClass = m->byClass2/2;
				if(pMob[conn].MOB.byClass1!=CLASS_LEVEL1) break;		//	1�������� 2�������� �����ϴ�.
				if(pMob[conn].MOB.byClass2!=nClass) break;				//  2�������� byClass2(����Ŭ����)�� ���������� üũ�Ѵ�.
				pMob[conn].MOB.byClass1=CLASS_LEVEL2;
				pMob[conn].MOB.byClass2=m->byClass2; bRet=true;
			}

			int nX=pMob[conn].TargetX; int nZ=pMob[conn].TargetY;
			m->nID=conn;
			m->byClass1=pMob[conn].MOB.byClass1;
			m->byClass2=pMob[conn].MOB.byClass2;

			if(!bRet)			//	�������н�
			{	sprintf(temp,"dbg _MSG_CLASS packet err char:%s Pclass1:%d Pclass2:%d class1:%d, class2:%d",
					pMob[conn].MOB.szName,m->byClass1,m->byClass2,pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_CLASS));
			}

			//	����������
			GridMulticast(nX,nZ,(MSG_STANDARD*)m,0,30);
			pMob[conn].UpdateEquipmentPoints() ;
			pMob[conn].NotifyUpdateUIMsg() ;

			//	�����鿡�� ������ �����Ѵ�.
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
			S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;		//	�������߰��� �˸���.
			sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
			sm.byIndex=emptyinven; sm.sitem=pMob[conn].MOB.Inven[emptyinven];
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
		}	break;
	case CSP_REQ_LEARN_SKILL :
		{	S_CSP_REQ_LEARN_SKILL* pMsg = (S_CSP_REQ_LEARN_SKILL*)msg;
			int iRes = pMob[conn].LearnSkill( pMsg->snID ) ;
			if( iRes )
			{
				#ifdef __TN_2ND_LOG__
				{
					char chBuf[256] = { 0,0,0, } ;
					sprintf( chBuf, "\t[LearnSkill] Learn Skill ���� ����: %d \r\n", iRes ) ;
					pMob[conn].Print( chBuf ) ;
				}
				#endif //__TN_2ND_LOG__
			}

		}	break ;
	case CSP_CAST_UNIT_SKILL :
		{
			S_CSP_CAST_AREA_SKILL kMsg ;
			memset( &kMsg, 0, sizeof( S_CSP_CAST_AREA_SKILL) ) ;
			memcpy( &kMsg, msg, sizeof(S_CSP_CAST_UNIT_SKILL) ) ;
			int iRes = pMob[conn].CastSkill( &kMsg, 1 ) ;
			if( iRes )
			{
				#ifdef __DYNAMIC_LOG__
				if( pMob[conn].m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, } ;
					sprintf( chBuf, "\t[CastSkill] skill ���� ����: %d \r\n", iRes ) ;
					pMob[conn].Print( chBuf ) ;
				}
				#endif //__DYNAMIC_LOG__
				kMsg.snRes = (short)iRes ;
				short sUnitID = kMsg.krgTarget[0].snKeyID ;
				if( 0 >= sUnitID || MAX_MOB <= sUnitID )
				{
					kMsg.krgTarget[0].snKeyID = 0 ;
					kMsg.krgTarget[0].iHP = 0 ;
					kMsg.krgTarget[0].iAffection = 0 ;
				}
				else
				{
					kMsg.krgTarget[0].iHP = pMob[sUnitID].MOB.nHP ;
					kMsg.krgTarget[0].iAffection = pMob[sUnitID].m_iAffections ;
				}

				kMsg.krgTarget[0].byRes = (byte)eCmbt_Dodge ;
				kMsg.krgTarget[0].snDamage = 0 ;
								
				pMob[conn].BroadcastCastSkill( &kMsg, 1 ) ;
			}
		}	break ;
	case CSP_CAST_AREA_SKILL :
		{
			S_CSP_CAST_AREA_SKILL* pMsg = (S_CSP_CAST_AREA_SKILL*)msg ;
			int iRes = pMob[conn].CastSkill( pMsg, TN_MAX_TARGET_COUNT ) ;
			if( iRes )
			{
				#ifdef __DYNAMIC_LOG__
				if( pMob[conn].m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, } ;
					sprintf( chBuf, "\t[CastSkill] skill ���� ����: %d \r\n", iRes ) ;
					pMob[conn].Print( chBuf ) ;
				}
				#endif //__DYNAMIC_LOG__
				pMsg->snRes = (short)iRes ;
				for( int i = 0 ; i < TN_MAX_TARGET_COUNT ; ++i )
				{
					short sUnitID = pMsg->krgTarget[i].snKeyID ;
					//if( 0 >= sUnitID || MAX_MOB <= sUnitID ) continue ;
					if( 0 >= sUnitID || MAX_MOB <= sUnitID )
					{
						pMsg->krgTarget[i].snKeyID = 0 ;
						pMsg->krgTarget[i].iHP = 0 ;
						pMsg->krgTarget[i].iAffection = 0 ;
					}
					else
					{
						pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP ;
						pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections ;
					}

					pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge ;
					pMsg->krgTarget[i].snDamage = 0 ;
					pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP ;
					pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections ;
				}

				pMob[conn].BroadcastCastSkill( pMsg, TN_MAX_TARGET_COUNT ) ;
			}

		}	break ;
	case MSG_APPLY_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return ;
			MSG_APPLY_SIEGE* pMsg = (MSG_APPLY_SIEGE*)msg ;
			pMsg->snResult = eTNRes_Succeeded ;

			SYSTEMTIME st ;
			GetLocalTime( &st ) ;

			//-------------------------------------------------------
			// ���� ��û �Ⱓ�� �˻��Ѵ�.
			//-------------------------------------------------------
			if( 1 == g_kSiege.get_ExpiryOftheTerm() )
			{
				SendClientMessage( conn, g_pMessageStringTable[_ExpireOfTheTermForSiege] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return ;
			}

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\r\n[%dYY%dMM%dDD %2dHH%2dMI%2dSS] MSG_APPLY_SIEGE_ID\r\n\t10 > who: %s, ClanSlot:%d, ExpandSlot:%d \r\n"
					, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
					, pMob[conn].MOB.szName, pMsg->byClanSlot, pMsg->byExpandSlot );
				WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
			}
			#endif 

			//-------------------------------------------------------
			// ���� ��û�� �Ҹ�Ǵ� ���� �˻��Ѵ�.
			//-------------------------------------------------------
			int iFee = g_irgSetting[eCnst_FeeForSiegeSupport];
			//bool bBreak = false ;
			if( 0 == pMsg->byExpandSlot  ) // leader�� ��û
			{
				if( 1 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege1] ;
				else if( 2 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege2] ;
				else if( 3 == pMsg->byClanSlot ) iFee = g_irgSetting[eCnst_FeeForSiege3] ;
				//if( iFee > pMob[conn].get_Gold() ) bBreak = true ;
			}
			//int iFee = TNSiege::eApplyFee_SiegeSupport;
			////bool bBreak = false ;
			//if( 0 == pMsg->byExpandSlot  ) // leader�� ��û
			//{
			//	if( 1 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege1 ;
			//	else if( 2 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege2 ;
			//	else if( 3 == pMsg->byClanSlot ) iFee = TNSiege::eApplyFee_Siege3 ;
			//	//if( iFee > pMob[conn].get_Gold() ) bBreak = true ;
			//}


			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t20 > Check gold > gold:%d, fee:%d\r\n",  pMob[conn].get_Gold(), iFee );
				WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
			}
			#endif 

			if( iFee > pMob[conn].get_Gold() )
			{// ���� �����ϴٴ� �޽���				
				SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughGold] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return ;
			}


			//-------------------------------------------------------
			// 7402 �������� 10 �� �Ҹ��Ѵ�.
			//-------------------------------------------------------			
			int irgSlot[5] = { -1,-1,-1,-1,-1 } ; // item �˻�/���Ÿ� ���� slot No ���
			int iItemID = 7402;
			int iCountRequired = g_irgSetting[eCnst_ItemCount];
			int iCount = 0 ;
			if( 0 == pMsg->byExpandSlot  ) // leader�� ��û
			{
				iCount = pMob[conn].CheckItem( iItemID, iCountRequired, irgSlot ) ; // �䱸������ �������� ���ϸ� 0�� return

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\t30 > Check items > count:%d, iCountRequired:%d \r\n", iCount, iCountRequired );
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif 

				if( iCount < iCountRequired )
				{
					SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughItem] ) ;
					pMsg->snResult = eTNRes_Failed ;
					pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
					return;
				}
			}
			
			//-------------------------------------------------------
			// ��� ���ǿ� �¾ƾ� �Ѵ�. 60 level 20�� �̻�
			//-------------------------------------------------------
			int iGuildID = pMob[conn].MOB.nGuildID ;
			int iGuildIndex = pUser[conn].nGuildIndex ;
			CGuild kGuild;
			int iRes = ReadGuildFile( iGuildID, &kGuild );
			if( FALSE == iRes )
			{ // ��尡 ����Ȯ�ϴ�.
				SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return;
			}


			//if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) ) // ������� �ƴ϶��,
			if( !kGuild.IsGuildManager( pMob[conn].MOB.szName ) ) // ��� ������(�����, �α����)�� �ƴ϶��, ...
			{
				SendClientMessage( conn, g_pMessageStringTable[_NotGuildMaster] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return;
			}			
					
			int iLevelRequired = g_irgSetting[eCnst_MemberLevel];
			int iMemberCountRequired = g_irgSetting[eCnst_MemberCount1]; // leader�� ��û
			if( 0 < pMsg->byExpandSlot  ) iMemberCountRequired = g_irgSetting[eCnst_MemberCount2];
			int iMemberCount = 0;
			for( int i = 0 ; i < MAX_GUILD_MEMBER ; ++i )
			{
				if( iLevelRequired <= kGuild.GUILD.Member[i].byLevel ) ++iMemberCount;
			}

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t40 > Check Guild > iMemberCount:%d, required:%d \r\n", iMemberCount, iMemberCountRequired );
				WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
			}
			#endif 
			
			if( iMemberCountRequired > iMemberCount )
			{
				SendClientMessage( conn, g_pMessageStringTable[_HaveNotEnoughMember] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return;
			}
		
			iRes = g_kSiege.RegisterEntry( iGuildID, pMsg->byClanSlot, pMsg->byExpandSlot, conn ) ; // guild ID, clan slot, expand slot, applier
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes )
				{
					SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] ) ;	
				}
				else if( eTNRes_InvalidGuild == iRes )
				{
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\t55 > Register Entry > Res:%d > guidID:%d(idx:%d) \t---> Failed \r\n"
						, iRes, iGuildID, iGuildIndex );
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif 

				pMsg->snResult = iRes; //eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return ;
			}
			else
			{
				pMob[conn].DecGold( iFee );
				if( 0 == pMsg->byExpandSlot  ) pMob[conn].RemoveItem( iCountRequired, irgSlot ) ; 
				SendClientMessage( conn, g_pMessageStringTable[_CompletedToApplySiege] ) ;	

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\t50 > Register Entry > Res:%d > guidID:%d(idx:%d) \t---> Succeeded \r\n"
						, iRes, iGuildID, iGuildIndex );
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif

			}



			int iAllyGuildID = pGuild[iGuildIndex].nAlliedID ;

			iRes = g_kSiege.RegisterEntry( iAllyGuildID, pMsg->byClanSlot, pMsg->byExpandSlot+1, conn ) ;
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes )
				{
					SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] ) ;	
				}
				else if( eTNRes_InvalidGuild == iRes )
				{
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\t65 > Ally > Register Entry > Res:%d > guidID:%d \t---> Failed \r\n"
						, iRes, iAllyGuildID );
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif

				pMsg->snResult = iRes; //eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
				return ;
			}
			else
			{
				char szNotify[1024] = { 0,0,0, } ;
				sprintf( szNotify, g_pMessageStringTable[_CompletedToApplySiege], g_pMessageStringTable[_AllyGuild] ) ;
				SendClientMessage( conn, szNotify ) ;	

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\t60 > Ally > Register Entry > Res:%d > guidID:%d \t---> Succeeded \r\n"
						, iRes, iAllyGuildID );
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif
			}


			#ifdef __TN_TOP_LOG__
			{
				WriteLog( "\t 100 > Completed to register the entry of the siege\r\n", ".\\Log\\[Log]Castle.txt" ) ;
			}
			#endif


			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_APPLY_SIEGE) ) ;
		}
		break ;


	case MSG_GIVEUP_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return ;
			MSG_GIVEUP_SIEGE* pMsg = (MSG_GIVEUP_SIEGE*)msg;

			int iRes = eTNRes_Failed;
			//-------------------------------------------------------
			// ��� ���ǿ� �¾ƾ� �Ѵ�. 60 level 20�� �̻�
			//-------------------------------------------------------
			int iGuildID = pMob[conn].MOB.nGuildID ;
			int iGuildIndex = pUser[conn].nGuildIndex ;
			CGuild kGuild;
			iRes = ReadGuildFile( iGuildID, &kGuild );
			if( FALSE == iRes )
			{ // ��尡 ����Ȯ�ϴ�.
				SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_GIVEUP_SIEGE) ) ;
				return;
			}

			if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) ) // ������� �ƴ϶��,
			{
				SendClientMessage( conn, g_pMessageStringTable[_NotGuildMaster] ) ;
				pMsg->snResult = eTNRes_Failed ;
				pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_GIVEUP_SIEGE) ) ;
				return;
			}			

			iRes = g_kSiege.GiveUpSiege( iGuildID ) ;
			//if( iRes )
			//{// ���� ���� ������ ���, ��� ������ ���, ��ϵǾ� ���� ���� ���
			//	SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsNotRegistered] ) ;
			//}
			//else SendClientMessage( conn, g_pMessageStringTable[_YourGuildIsRegistered] ) ;

		}
		break;

	case MSG_STATE_OF_THE_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return ;
			MSG_STATE_OF_THE_SIEGE* pMsg = (MSG_STATE_OF_THE_SIEGE*)msg ;
			g_kSiege.get_Symbols( pMsg->irgClan ) ;

			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_STATE_OF_THE_SIEGE) ) ;
		}
		break ;
/*
	case MSG_SIEGE_ENTRY_ID :
		{
			MSG_SIEGE_ENTRY* pMsg = (MSG_SIEGE_ENTRY*)msg ;

		}
		break ;
*/
	case MSG_CHECK_SIEGE_ENTRY_ID :
		{
			if( eZone_Castle != g_iZoneID ) return ;
			MSG_CHECK_SIEGE_ENTRY* pMsg = (MSG_CHECK_SIEGE_ENTRY*)msg ;
			//pMsg->byClanSlot 
			//pMsg->byPage
			MSG_SIEGE_ENTRY kEntryMsg ;
			memset( &kEntryMsg, 0 , sizeof(kEntryMsg) ) ;
			kEntryMsg.wType = MSG_SIEGE_ENTRY_ID ;
			kEntryMsg.wPDULength = sizeof(MSG_SIEGE_ENTRY)-sizeof(HEADER);

			kEntryMsg.byDate = 1 ;
			kEntryMsg.byClanSlot = pMsg->byClanSlot ;
			kEntryMsg.byPage = pMsg->byPage ;
			const int iElementCount = 8 ;
			int iExpandSlot = pMsg->byPage * iElementCount ;
			int iEnd = iExpandSlot + iElementCount ;
			int iIndex = 0 ;
			for( ; iExpandSlot < iEnd ; ++iExpandSlot )
			{
				TNGUILD_INFO kGuild ;
				g_kSiege.GetEntry( pMsg->byClanSlot, iExpandSlot, kGuild ) ;
				kEntryMsg.irgGuildID[iIndex] = kGuild.iID ;
				kEntryMsg.dwrgGuildMark[iIndex] = kGuild.dwMark ;
				strncpy( kEntryMsg.szrgGuildName[iIndex], kGuild.szName, SZGUILD_LENGTH ) ;
				++iIndex ;
			}

			pUser[conn].cSock.SendOneMessage( (char*)&kEntryMsg, sizeof(MSG_SIEGE_ENTRY) ) ;
		}
		break ;
	case MSG_FIX_DATE_OF_SIEGE_ID :
		{
			if( eZone_Castle != g_iZoneID ) return ;
			MSG_FIX_DATE_OF_SIEGE* pMsg = (MSG_FIX_DATE_OF_SIEGE*)msg ;

			if( 0 == pMsg->byWhat ) // ������¥ ��û
			{
				pMsg->byDate = (byte)g_kSiege.get_DateToHold() ;
			}
			else if( 1 == pMsg->byWhat ) // ���� ��¥ ���� by ���� ��� guild master
			{
				//---------------------------------------------
				// ���� ��� �渶���� Ȯ���ؾ� �Ѵ�.
				//---------------------------------------------
				int iDefenseGuild = g_kSiege.get_OwnerGuild();
				int iGuildID = pMob[conn].MOB.nGuildID ;
	
				if( iDefenseGuild != iGuildID )
				{// ���� �ƽ����� ��� �����Ͱ� �ƴմϴ�.
					SendClientMessage( conn, g_pMessageStringTable[_NotDefenseGuildMaster] ) ;
					return;
				}

				int iGuildIndex = pUser[conn].nGuildIndex ;
				CGuild kGuild;
				int iRes = ReadGuildFile( iGuildID, &kGuild );
				if( FALSE == iRes )
				{ // ��尡 ����Ȯ�ϴ�.
					SendClientMessage( conn, g_pMessageStringTable[_Guild_Not_Fine_Guild] ) ;
					return;
				}

				if( strcmp( kGuild.szGuildMaster, pMob[conn].MOB.szName) )
				{// ���� �ƽ����� ��� �����Ͱ� �ƴմϴ�.
					SendClientMessage( conn, g_pMessageStringTable[_NotDefenseGuildMaster] ) ;
					return;
				}

				g_kSiege.SelectDate( pMsg->byDate ) ;
			}

			pUser[conn].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_FIX_DATE_OF_SIEGE) ) ;
		}
		break ;
	case MSG_PET_COMMAND_ID :
		{
			MSG_PET_COMMAND* pMsg = (MSG_PET_COMMAND*)msg ;
			if( 0 >= conn || MAX_USER <= conn) return ;
			int iMob = pMob[conn].m_irgSummoned[eTNCls2_Retainer];
			if( MAX_USER > iMob || MAX_MOB <= iMob ) return ;

			if( 1 == pMsg->iAction ) // �����ض�
			{
				int iRes = pMob[conn].CanAttackTarget( pMsg->iParam1 ) ;
				if( eTNRes_Succeeded == iRes )
				{
					pMob[iMob].ClearCurrentTarget() ;
					pMob[iMob].ClearAttacker( 0 ) ;
					pMob[iMob].MemorizeAttacker( 0, 1, pMsg->iParam1 ) ;
				}

				if( pMob[conn].IsDebugOn( eTNDbg_Pet ) )
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "[Pet_Command] Attack> res:%d, master:%d, target:%d \r\n"
						,iRes , conn, pMsg->iParam1 ) ;

					WriteLog( chBuf, ".\\Log\\[Log]Pet.txt" ) ;
				}
			}
			else if( 2 == pMsg->iAction ) // �����
			{
				pMob[iMob].ClearCurrentTarget() ;
				pMob[iMob].ClearAttacker( 0 ) ;
				pMob[iMob].Mode = MOB_PEACE ;
				pMob[iMob].OnFollow( pMob[iMob].Leader ) ;
			}
		}
		break ;
	case MSG_ITEM_ID :
		{	
			MSG_ITEM* pMsg = (MSG_ITEM*)msg ;

			bool bCheckAffection = true ;
			if(pMsg->byIndex<0 || pMsg->byIndex>=pMob[conn].byMaxInven) break;
			int nItemIndex = pMob[conn].MOB.Inven[pMsg->byIndex].snIndex+HT_PARAMTYPE_ITEM_START-1 ;
			if( (HT_PARAMTYPE_ITEM_CHARGE_START <= nItemIndex) && (HT_PARAMTYPE_ITEM_CHARGE_END >= nItemIndex ) )
			{
				bCheckAffection = false ;
			}

			if( nItemIndex!=eItem_Resurrect1 && nItemIndex!=eItem_Resurrect2 && bCheckAffection )
			{	if( (eTNVSAfn_Stun & pMob[conn].m_iAffections) || (eTNVSAfn_Sleep & pMob[conn].m_iAffections)  ) break ;	
			}


			if( eItm_Use == pMsg->byType ) 
			{	

				char strItem[128];	// ������ ��� �α�...
				if (BASE_CheckItemLog(&pMob[conn].MOB.Inven[pMsg->byIndex]))
				{	BASE_GetItemCode(&pMob[conn].MOB.Inven[pMsg->byIndex],strItem);
					sprintf(temp,"use %s",strItem);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}
				if(pMsg->byIndex<0 || pMsg->byIndex>=pMob[conn].byMaxInven)
				{	sprintf(temp, "Invalid Inven position packet:%d of max:%d\r\n", pMsg->byIndex, pMob[conn].byMaxInven);
					Log( temp,pUser[conn].AccountName,pUser[conn].IP) ;
					return;
				}

				if(nItemIndex==eItem_Resurrect1 || nItemIndex==eItem_Resurrect2)				//	������ �ֹ������
					pMob[conn].UseItem( pMsg, eTNFsm_Dead) ;
				else
                    pMob[conn].UseItem( pMsg ) ;
			}
		}	break ;
	case CONTACT_NPC :
		{// class1�� 19�� ��쿡, client���� �� �޽����� �������ش�.
			MSG_CONTACT_NPC* pMsg = (MSG_CONTACT_NPC*)msg ;

			if( eTNSwitch_ContactNPC & g_iSwitch )
			{ 
				SYSTEMTIME st ;
				GetLocalTime( &st ) ;
				char chBuf[512] = { 0,0,0, } ;
				sprintf( chBuf, "[%dMM%dDD %dHH%dMI%dSS] CONTACT_NPC received! > NPCID:%d\r\n"
					, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
					, pMsg->snNPCID
					) ;
				WriteLog( chBuf, ".\\Monster_Log\\[Log]ContactNPC.txt" ) ;
			}

			int iNPCID = pMsg->snNPCID ;
			if( MAX_USER > iNPCID || MAX_MOB <= iNPCID ) break ;// NPC �� ��쿡��, ...
			int tclan = pMob[iNPCID].m_byClan ;

			if( eTNSwitch_ContactNPC & g_iSwitch )
			{ 
				char chBuf[512] = { 0,0,0, } ;
				sprintf( chBuf, "\t- clan:%d, Hostile:%d, EventID:%d \r\n"
					, tclan, g_iHostileTable[pMob[conn].m_byClan][tclan]
					, pMob[iNPCID].MOB.snBagIndex
					) ;
				WriteLog( chBuf, ".\\Monster_Log\\[Log]ContactNPC.txt" ) ;
			}

			if( pMob[conn].m_byClan<0 || pMob[conn].m_byClan>eTNClan_NPC || tclan<0 || tclan>eTNClan_NPC )
			{	Log("err clan out or range", pMob[conn].MOB.szName, 0 ) ;
				break ;
			}
			if ( 0 < g_iHostileTable[pMob[conn].m_byClan][tclan] ) break ;
				
			//int iMonsterDataIndex = pMob[iNPCID].MOB.nTP ;
			int iEventID = pMob[iNPCID].MOB.snBagIndex ;
			if( 0 < iEventID ) // event ó��
			{
				TriggerEvent( conn, iEventID, 0, 0, iNPCID, 20 ) ;	
			}
		}	break ;
	case REGISTER_KALA_CORE :
		{
			MSG_REGISTER_KALA_CORE* pMsg = (MSG_REGISTER_KALA_CORE*)msg ;
			int iAltarSlot = pMsg->snID ;
			if( 0 > iAltarSlot || eKalaAltar_MaxCount <= iAltarSlot ) return ; // invalid kala-altar ID
			if( g_krgKalaAltar[iAltarSlot].sTrimuriti != pMob[conn].m_byClan ) return ; // �ֽ��� Ʋ����.
			if( 0 < g_kKalaSystem.IsEmptyAltar( iAltarSlot ) ) return ; // ��� ���� �ʴ�.
			//if( 0 != g_irgKalaAltar[iAltarSlot] ) return ; // ��� ���� �ʴ�.
			if( !(eTNVSAfn_HaveKalaCore & pMob[conn].m_iAffections) ) return ; // have a kala-core affection�� �˻��Ѵ�.
			int iDist = pMob[conn].CalDistance2( g_krgKalaAltar[iAltarSlot].x, g_krgKalaAltar[iAltarSlot].y ) ;
			if( 10 < iDist ) return ;
			// check a kala-core.  // 3�ֽſ� ���� kala-core�� Ʋ���� ������, �� 3���� �˻縦 ���ľ� �� ���̴�. 

			SYSTEMTIME st ;
			GetLocalTime( &st ) ;

			int iMonsterID = 0 ;
			int irgSlot[5] = { -1,-1,-1,-1,-1 } ;
			int iCount = 0 ;
			iCount = pMob[conn].CheckItem( eKalaCore_Brahma, 1, irgSlot ) ;
			iMonsterID = eKala_Brahma ;
			if( 0 >= iCount )
			{	iCount = pMob[conn].CheckItem( eKalaCore_Vishnu, 1, irgSlot ) ;
				iMonsterID = eKala_Vishnu ;
			}
			if( 0 >= iCount )
			{
				iCount = pMob[conn].CheckItem( eKalaCore_Siva, 1, irgSlot ) ;
				iMonsterID = eKala_Siva ;
			}
			if( 1 > iCount )
			{
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] REGISTER_KALA_CORE > Have no kala-core! -> TotalCount:%d \r\n"
						, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						,iCount
						) ;
					WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
				}
				return ;
			}
			pMob[conn].RemoveItem( iCount, irgSlot ) ; // remove the kala-core.
			
			pMob[conn].m_iAffections = pMob[conn].m_iAffections ^ eTNVSAfn_HaveKalaCore ;
			pMob[conn].BroadcastUpdateStatusMsg() ;

			int iRes = g_kKalaSystem.InstallKala( iMonsterID, g_krgKalaAltar[iAltarSlot].sTrimuriti, iAltarSlot, conn ) ;
			if( iRes )
			{
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] Register_Kala-core > InstallKala() > Res:%d \r\n"
						, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, iRes
						) ;
					WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
				}
				return ;
			}

			int iTxtIndex = 0 ;
			if( eKala_Brahma == iMonsterID ) iTxtIndex = _Brahma ;
			else if( eKala_Vishnu == iMonsterID ) iTxtIndex = _Vishnu ;
			else if( eKala_Siva == iMonsterID ) iTxtIndex = _Siva ;

			int iTrimuritiIndex = 0 ;
			if( eTNClan_Brahma == pMob[conn].m_byClan ) iTrimuritiIndex = _Brahma ;
			else if( eTNClan_Vishnu == pMob[conn].m_byClan ) iTrimuritiIndex = _Vishnu ;
			else if( eTNClan_Siva == pMob[conn].m_byClan ) iTrimuritiIndex = _Siva ;

			char szMsg[1024] = { 0,0,0, } ;	
			sprintf( szMsg, g_pMessageStringTable[_Register_Kala_Core]
				, g_pMessageStringTable[iTrimuritiIndex] , pMob[conn].MOB.szName, pMob[conn].TargetX, pMob[conn].TargetY, g_pMessageStringTable[iTxtIndex] ) ;
			PostMessageToZone( szMsg ) ;

			{
				SYSTEMTIME st ;
				GetLocalTime( &st ) ;
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
				strcat( szMsg, chBuf ) ;
				WriteLog( szMsg, ".\\Log\\[Log]KalaSystem.txt" ) ;
			}

			//g_kKalaSystem.ChangeInfo( iKalaSlot, TNKalaSystem::eLoc_Altar, pMsg->snID, g_irgKalaAltar[pMsg->snID], 0, 0, 0, 0 ) ;
			MoveKalaRewarder() ;

		}	break ;
	case CSP_REQ_UPDATE_UI :
		{
			S_CSP_REQ_UPDATE_UI* pMsg = (S_CSP_REQ_UPDATE_UI*)msg;
			pMob[conn].NotifyUpdateUIMsg() ;
		}	break ;
	case CSP_REQ_UPDATE_STATUS :
		{
			if( 0 >= conn && MAX_USER <= conn ) break ;

			S_CSP_REQ_UPDATE_STATUS* pMsg = (S_CSP_REQ_UPDATE_STATUS*)msg;

			if( MAX_USER <= pMsg->snKeyID && MAX_MONSTER > pMsg->snKeyID && pMob[pMsg->snKeyID].IsNotLocked() ) // �����̰� ���� lock ������ �Ϸ�Ǿ� ���� ������
			{
				S_SCP_RESP_UPDATE_STATUS kMsg ;
				kMsg.wType = SCP_RESP_UPDATE_STATUS ;
				//kMsg.Size = sizeof( S_SCP_RESP_UPDATE_STATUS ) ;
				kMsg.snKeyID = (short)pMsg->snKeyID ;
				kMsg.iHP = pMob[pMsg->snKeyID].MOB.nHP ;
				kMsg.iTP = 0;
				kMsg.iPrana = 0;
				kMsg.iAffections = pMob[pMsg->snKeyID].m_iAffections  ;
				kMsg.snKarma = 0 ;

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof( S_SCP_RESP_UPDATE_STATUS ) ) ;
			}
			else if( 0 < pMsg->snKeyID && MAX_USER > pMsg->snKeyID ) // PC�� ���
			{
				S_SCP_RESP_UPDATE_STATUS kMsg ;
				kMsg.wType = SCP_RESP_UPDATE_STATUS ;
				//kMsg.Size = sizeof( S_SCP_RESP_UPDATE_STATUS ) ;
				kMsg.snKeyID = (short)pMsg->snKeyID ;
				kMsg.iHP = pMob[pMsg->snKeyID].MOB.nHP ;
				kMsg.iTP = pMob[pMsg->snKeyID].MOB.nTP ;
				kMsg.iPrana = pMob[pMsg->snKeyID].MOB.nPrana ;
				kMsg.iAffections = pMob[pMsg->snKeyID].m_iAffections  ;
				kMsg.snKarma = pMob[pMsg->snKeyID].MOB.snKarma ;

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof( S_SCP_RESP_UPDATE_STATUS ) ) ;
			}
		}	break ;
	case CSP_REQ_INCREASE_CHAKRA :
		{
			S_CSP_REQ_INCREASE_CHAKRA* pMsg = (S_CSP_REQ_INCREASE_CHAKRA*)msg;
			pMob[conn].IncChakra( (int)pMsg->byChakra ) ;
		}	break ;
	case _MSG_TOGGLE_BUTTON :
		{
			MSG_TOGGLE_BUTTON* pMsg = (MSG_TOGGLE_BUTTON*)msg ;
			if( 1 == pMsg->byButton ) // PK ��ư
			{
				if( eTNSwitch_PKDisable &g_iSwitch ) return ;
				if( 0 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus ^ eTNBtn_PK ;
				else if( 1 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus | eTNBtn_PK ;

				for( int i = 1; i < eFellow_MaxCount; ++i )
				{
					int iMob = pMob[conn].m_irgSummoned[i];
					if( MAX_USER <= iMob && MAX_MOB > iMob ) pMob[iMob].m_iButtonStatus = pMob[conn].m_iButtonStatus ;

				}
			}
			/*
			else if( 2 == pMsg->byButton ) // Assist ��ư
			{
				int iPartyLeader = pMob[conn].Leader ;
				if( 0 == iPartyLeader ) break ;
				MSG_CHANGE_TARGET kMsg ;
				kMsg.snTarget = (short)(pMob[iPartyLeader].m_iTargetHandle) ;
				if( 0 == kMsg.snTarget ) break ; // target�� �����Ǿ� ���� ���� ���, ...

				pUser[conn].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_TARGET) ) ;
				
				//if( 0 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus ^ eTNBtn_Assist ;
				//else if( 1 == pMsg->byValue ) pMob[conn].m_iButtonStatus = pMob[conn].m_iButtonStatus | eTNBtn_Assist ;
			}*/
		}	break ;
	case _MSG_CHANGE_TARGET :
		{
			if( 0 != pMob[conn].Leader ) break ;
			MSG_CHANGE_TARGET* pMsg = (MSG_CHANGE_TARGET*)msg ;			
			//pMob[conn].m_iTargetHandle = pMsg->snTarget ;
			
			for( int i = 0 ; i < MAX_PARTY ; ++i )
			{
				int iPartyMember = pMob[conn].m_irgParty[i] ;
				if( 0 >= iPartyMember || MAX_USER <= iPartyMember ) continue ;
				pUser[iPartyMember].cSock.AddMessage( (char*)pMsg, sizeof(MSG_CHANGE_TARGET) ) ;
				//pUser[iPartyMember].cSock.SendOneMessage( (char*)pMsg, sizeof(MSG_CHANGE_TARGET) ) ;
			}
		}
		break ;
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
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
			}

			bool bRet=true; DWORD dwLevel=0; DWORD dwFee=0;			
			DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
			if(m->wStartPortalID!=0)	//	�Ϲ����� ��Ż�̵�
			{	bRet &= g_ParamMgr.HT_bGetPortalFee(m->wStartPortalID, m->wEndPortalID, &dwFee);
			}	

			bRet &= g_ParamMgr.HT_bGetPortalInfo(m->wEndPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ);

			int iFee = (int)dwFee ;

			if(!bRet) 
			{	sprintf(temp,"dbg CSP_REQ_MOVE_PORTAL find portal data error startp:%d endp:%d",m->wStartPortalID, m->wEndPortalID);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
			}

			if(pMob[conn].MOB.byLevel < (byte)dwLevel)		//	��Ż�̵��� �ʿ��� ������ �������
			{	sm.byResult=REPLY_MOVE_PORTAL_WANTLEVEL; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
			}

			if(pMob[conn].MOB.nRupiah < iFee)	//	��Ż�̵��� �ʿ��� ���� �����Ұ��
			{	sm.byResult=REPLY_MOVE_PORTAL_WANTMONEY; 
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
			}

			BYTE byMoveZone = (BYTE)(dwServerID - HT_MAP_START + 1);
			if(byMoveZone>=SERVER_KALIA_LOW && byMoveZone<=SERVER_KALIA_HIGH)
				if(!g_bIsKaliaOpend) return;
			if(byMoveZone==SERVER_KALIA_LOW)
			{	short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
				if(snChakra>297)	//	��ũ������ 297���� Ŭ��쿡�� ����Į���ƴ����� ���ԺҰ���û(2005.5.19)
				{	sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
				}
			}	else
			if(byMoveZone==SERVER_KALIA_MIDDLE)
			{	short snChakra = pMob[conn].MOB.sMuscle + pMob[conn].MOB.sNerves + pMob[conn].MOB.sHeart + pMob[conn].MOB.sMind;
				if(snChakra>378)	//	��ũ������ 378���� Ŭ��쿡�� �߷�Į���ƴ����� ���ԺҰ���û(2005.5.19)
				{	sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
				}
			}
			if(byMoveZone==SERVER_STRONGHOLD)			//	����������� ī�콺Ʈ�㿡�� �ش���������常 ���԰���
			{
				int iHold = m->wEndPortalID - 216;		//	ī�콺Ʈ�� 1�� ~ 4�� : 216 ~ 219
				if(iHold>=0 && iHold<eStronghold_MaxCount)
				{
					if(g_krgStronghold[iHold].iOwner!=pMob[conn].MOB.nGuildID)
					{
						sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
						pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); break ;
					}
				}
			}

			if(byMoveZone == (ServerIndex+1))	//	�������̸�
			{	int tx = GetRandom(snStartX, snEndX);
				int ty = GetRandom(snStartZ, snEndZ);

				int iCount = 0 ;
				int tret = GetEmptyMobGrid(conn,&tx,&ty);
				if	(tret==FALSE)
				{	
					tx = GetRandom(snStartX, snEndX);
					ty = GetRandom(snStartZ, snEndZ);

					tret = GetEmptyMobGrid(conn,&tx,&ty) ;
					while( FALSE == tret )
					{
						++iCount ;
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
						tret = GetEmptyMobGrid(conn,&tx,&ty) ;
					}
				}

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm)-sizeof(HEADER);
				nm.TargetX=tx; nm.TargetY= ty;
				nm.dwKeyID = conn; nm.PosX=0; nm.PosY=0;
				nm.Direction = 0; nm.Effect = 5;

				if  (pUser[conn].Mode!=USER_PLAY) return;
				if  ( 0 >= pMob[conn].MOB.nHP ) return;

				///////////////////////////////// 4096 4096 �ܺ� üũ /////////////////////////////////////////////////
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

				MSG_Money_Move mm; mm.wType=_MSG_Money_Move;			//	��Ż�̿����� ���� ���� ���Ҹ� �˸���.
				mm.byFromPlace=ITEM_PLACE_PORTAL; mm.byToPlace=ITEM_PLACE_INVEN;
				mm.dwFromMoney=0; mm.dwToMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)&mm, sizeof(MSG_Money_Move));

				//// 30�� ���� PK�� ������ �ȵǰ� �Ѵ�.
				//TNEFFECT kEffect ;
				//kEffect.iID = eTNAfn_ProtectFromPK ;
				//kEffect.iDuration = 15000 ;
				//pMob[conn].AddEffect( kEffect, conn, conn ) ;

			}	else
			{	if  (ServerDown!=-1000)
				{	SendClientMessage(conn,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
					return;
				}

				sprintf(temp,"dbg char:%s move portal to other zone:%d",pMob[conn].MOB.szName,byMoveZone);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);

				//	��Ż�̵��� 
				pMob[conn].DecGold(iFee);

				pMob[conn].m_kWaitAction.iAction = eWaitAct_ZonePortal ;

				sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
				sm.byZone=byMoveZone; sm.nMoney=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
				pMob[conn].m_eFSM = eTNFsm_Stand ;
				pMob[conn].m_kLastTime.uiSitted = 0 ;
			}
		}	break;
	case _MSG_Action:		// �̵�, �ڷ���Ʈ
		{	
			if( eTNVSAfn_DontMove & pMob[conn].m_iAffections ) break ;
			
			if( eWaitAct_TownPortal  == pMob[conn].m_kWaitAction.iAction ) pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
			//if( eWaitAct_TownPortal2 == pMob[conn].m_kWaitAction.iAction ) return;	//	�������̹Ƿ� �ٸ� �̵��� �Ҽ� ����
			//if( eWaitAct_TownPortal2 == pMob[conn].m_kWaitAction.iAction ) pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
			//if( eWaitAct_TownPortal3 == pMob[conn].m_kWaitAction.iAction ) return;	//	�������̹Ƿ� �ٸ� �̵��� �Ҽ� ����
			if( eWaitAct_SummonParty == pMob[conn].m_kWaitAction.iAction ) pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;

			MSG_Action * m = (MSG_Action *) msg;
			if( pUser[conn].Mode != USER_PLAY ) {SendHpMode(conn);return;}
			if( 0 >= pMob[conn].MOB.nHP )
			{
				if( 50 < pMob[conn].m_iHPProblem )
				{
					int iKiller = pMob[conn].m_iKiller ;
					char szKiller[128] = { 0,0,0, } ;
					if( 0 >= iKiller || MAX_MOB <= iKiller )
					{
						iKiller = 0 ;
						strcpy( szKiller, "Unknown" ) ;
					}
					else
					{
						strcpy( szKiller, pMob[iKiller].MOB.szName ) ;
					}

					S_SCP_RESP_REMOVE_MOB sm ;
					sm.wType = SCP_RESP_REMOVE_MOB ; 
					sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER) ;
					sm.nID = conn ;
					sm.byResult = 1 ; 
					sm.dwKillerID = iKiller ;
					sm.byRemoveType = 0 ;
					sm.snTribe = pMob[iKiller].MOB.snTribe ;
					strcpy( sm.szName, pMob[iKiller].MOB.szName ) ;
					GridMulticast( pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, -1) ;

					#ifdef __TN_TOP_LOG__
					{
						SYSTEMTIME st ;
						GetLocalTime( &st ) ;

						char chBuf[512] = { 0,0,0, } ;
						sprintf(chBuf, "[%d��%d�� %d��%d��%d��] SendHpMode > ����(%d,%s) killer(%d, %s)�� ���� �׾���.\r\n"
							, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
							,conn, pMob[conn].MOB.szName, iKiller, szKiller ) ; 
						WriteLog( chBuf, ".\\Log\\[Err]OnKilled.txt" ) ;
					}
					#endif

					pMob[conn].m_iHPProblem = 0 ;
					return ;
				}

				++pMob[conn].m_iHPProblem ;
				return;

				/*
				SendHpMode(conn);
				S_SCP_RESP_REMOVE_MOB sm ;
				sm.wType = SCP_RESP_REMOVE_MOB ; 
				sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER) ;
				sm.nID = conn ;
				sm.byResult = 1 ; 
				sm.dwKillerID = 0 ;
				sm.snTribe = pMob[0].MOB.snTribe ;
				strcpy( sm.szName, pMob[0].MOB.szName ) ;
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
			//////////////////////// �׼� Ÿ��üũ ///////////////////////////////////////////////
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
			//////////////////////// �ӵ� üũ ///////////////////////////////////////////////
			//if	(m->Speed>pMob[conn].m_snCurMovingSpeed)
			//{	m->Speed = pMob[conn].m_snCurMovingSpeed;
			//	AddCrackError(conn,5,4);
			//	Log("etc diffrent movement.",pUser[conn].AccountName,pUser[conn].IP);
			//}
			//////////////////////// �ڷ���Ʈ�� �ƴѵ� �Ÿ��� ū��� ///////////////////////////////////////////////
			int ix = pMob[conn].TargetX;
			int iy = pMob[conn].TargetY;
			int iDist = pMob[conn].m_iMoveSpeed + 2 ;
			if  (m->Effect!=1 && m->Effect!=2 && (m->TargetX<ix-g_iViewGridX || m->TargetX>ix+g_iViewGridX ||m->TargetY<iy-g_iViewGridY || m->TargetY>iy+g_iViewGridY))
			{	if	(m->TargetX < ix-(g_iHalfGridX) || m->TargetX>ix+(g_iHalfGridX) || m->TargetY<iy-(g_iHalfGridY) || m->TargetY>iy+(g_iHalfGridY) )
				{	// �űⰡ �ָ� ������ ���� ��ġ�� ����
					Teleport( conn, ix, iy ) ;
					//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
					//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return;
				}
				else
				{	// ������ �����߰�
					AddCrackError(conn,1,CRACK_SPEED_HACK1);
				}
			}
/*
			HS2D_COORD kSrc, kDest ;
			kSrc.x = ix ;
			kSrc.y = iy ;
			kDest.x = m->TargetX ;
			kDest.y = m->TargetY ;
			int iMoveDist = CalDistance( kSrc, kDest, 0, 0 ) ;
			int iRes = pMob[conn].CheckMoveHack( iMoveDist, pMob[conn].m_iMoveSpeed, CurrentTime ) ;
*/
			//int iRes = pMob[conn].CheckMoveHack( m->Effect ) ;
			//if( iRes ) AddCrackError( conn, iRes, CRACK_SPEED_HACK2 ) ; // speed hack�̴�.

/*
			if  (m->Effect!=1 && m->Effect!=2 && (m->TargetX<ix-g_iViewGridX || m->TargetX>ix+g_iViewGridX ||m->TargetY<iy-g_iViewGridY || m->TargetY>iy+g_iViewGridY))
			{	if	(m->TargetX < ix-(g_iHalfGridX) || m->TargetX>ix+(g_iHalfGridX) || m->TargetY<iy-(g_iHalfGridY) || m->TargetY>iy+(g_iHalfGridY) )
				{	// �űⰡ �ָ� ������ ���� ��ġ�� ����
					Teleport( conn, ix, iy ) ;
					//MSG_Action sm;	GetAction(conn,ix,iy,&sm);
					//pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return;
				}	else
				{	// ������ �����߰�
					AddCrackError(conn,1,5);
				}
			}
*/
			///////////////////////////////// 4096 4096 �ܺ� üũ /////////////////////////////////////////////////
			if  (m->TargetX<=0 || m->TargetX>=MAX_GRIDX ||m->TargetY<=0 || m->TargetY>=MAX_GRIDY)
			{	Log("err action - viewgrid",pMob[conn].MOB.szName,pUser[conn].IP);
				return;
			}

			if( 0 == m->Effect )
			{
				#ifdef __TN_PLAYMOVIE__
				return ;
				#endif
				pMob[conn].m_eFSM = eTNFsm_Sit ;
				pMob[conn].m_kLastTime.uiSitted = timeGetTime() ;
			}
			else if( 1 == m->Effect )
			{
				pMob[conn].m_eFSM = eTNFsm_Stand ;
				pMob[conn].m_kLastTime.uiSitted = 0 ;
			}
		
			//if	(m->TargetX==pMob[conn].TargetX && m->TargetY==pMob[conn].TargetY)   return;  // ���ڸ��� ����
			///////////////////////////////// �ʺ��� üũ /////////////////////////////////////////////////////////
			//unsigned char Att = GetAttribute(m->TargetX,m->TargetY);
			//if	(Att&ATT_NEWBIE && pMob[conn].MOB.CurrentScore.Level>=35 && pMob[conn].MOB.CurrentScore.Level<=999)
			//{	SendClientMessage(conn,g_pMessageStringTable[_NN_Newbie_zone]);
			//	m->TargetX = pMob[conn].TargetX;
			//	m->TargetY = pMob[conn].TargetY;
			//	m->Route[0]= 0;
			//	pUser[conn].cSock.AddMessage((char*)m,m->Size);
			//	return;
			//}
			///////////////////////////// ���� ���� MSG_ACTION /////////////////////////////////////////////////
			//if  (pMob[conn].MOB.Class==3) DoRemoveHide(conn);

			if( eTNCell_SealedZone & g_krgCell[m->TargetY][m->TargetX].usProperty ) // �̵��� �� ���� �����̴�.
			{
				Teleport( conn, ix, iy ) ;
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
					// �űⰡ �ָ� ������ ���� ��ġ�� ����
					Teleport( conn, ix, iy ) ;
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
				if	(dis==-1) // �̵��������� �����Ƿ� ���� ���͸�  conn�� �����ش�.
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

			pMob[conn].m_kLastTime.uiMoved = CurrentTime ;

			GridMulticast(conn,m->TargetX,m->TargetY,(MSG_STANDARD*)msg,50);
			pUser[conn].cSock.SendMessage();
			//pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			if( 0 < g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent )
			{ // cell �� event �� ��ϵǾ� ���� ���, ...
/*
				S_SCP_RESP_WHISPER_CHAT kMsg ; 
				kMsg.wType = SCP_RESP_WHISPER_CHAT ;	
				kMsg.byResult = REPLY_ACK_OK ;
				strncpy( kMsg.szName, "System", SZNAME_LENGTH ) ;
				kMsg.byTextColor = 14 ; kMsg.byBgColor = 0 ; // ���߿� ���� ������ �ٲ۴�. ���� �� ���	

				char szResult[1024] = { 0,0,0, } ;
				sprintf( szResult, "Event ID:%d", g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent ) ;
				strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
				pUser[conn].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
*/
				TriggerEvent( conn, g_krgCell[pMob[conn].TargetY][pMob[conn].TargetX].usEvent, pMob[conn].TargetX, pMob[conn].TargetY, 0, 10 ) ;
			}

			// retainer �θ���
			pMob[conn].CallRetainer() ;
			pMob[conn].CallRobot();

			// follower���� �Ѿư���
			HS2D_COORD kPos ;
			kPos.x = m->TargetX ;
			kPos.y = m->TargetY ;
			for( int iFollowerIndex = 0 ; iFollowerIndex < eFollower_MaxCount ; ++iFollowerIndex )
			{
				int iFollower = pMob[conn].m_irgFollower[iFollowerIndex] ;
				if( MAX_USER > iFollower || MAX_MOB <= iFollower ) break ; // NPC�� follower�� �� �� �ִ�.
				if( pMob[iFollower].IsDead() ) continue ;

				pMob[iFollower].OnFollow( conn ) ;
			}

			// ����Ÿ��
			int iPassenger = pMob[conn].m_iPassenger ;
			if( 0 < iPassenger && MAX_USER > iPassenger ) // PC�� ��츸 passenger�� �� �� �ִ�.
			{			
				int x=m->TargetX;
				int y=m->TargetY;

				int tret = GetEmptyMobGrid( iPassenger, &x, &y ) ;
				if( tret)
				{
					m->dwKeyID = iPassenger ;
					m->Speed = pMob[iPassenger].m_iMoveSpeed ;
					m->Effect = 4 ; // run
					m->TargetX = x;
					m->TargetY = y;
					pUser[iPassenger].cSock.AddMessage((char*)m,sizeof(*m));
					pUser[iPassenger].cSock.SendMessage() ;
				}		
			}
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_QUEST_NOTIFY_LEVEL:
		{	S_CSP_QUEST_NOTIFY_LEVEL *m = (S_CSP_QUEST_NOTIFY_LEVEL*)msg;
			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	�ش� NPC������ ���� ���Ұ��.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC�� ���� ���� ���� ���� ���.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid���� �÷��̾ ���� ���
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
	case _MSG_Imple: // Imple�� Whisper�� ��Ʈ���ĸ� ����.
		{
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
 	case _MSG_UpdateItem:	// ������, ����ġ �ѱ���
		{		
		}     break; 
///////////////////////////////////////////////////////////////////////////////////////////////
    case CSP_REQ_TRADE_CANCEL:	// 1:1 �ŷ� ����
		{	    
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
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
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, trade�� �� �� ����.
			MSG_Trade *m = (MSG_Trade *) msg;

			if  ((0 >= pMob[conn].MOB.nHP) || (pUser[conn].Mode!=USER_PLAY))
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_TRADE);
				return;
			}

			//////////////////////// msg packet�� ���Ἲ �˻�//////////////
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
			{	if(m->TradeMoney==-1)	//	�ŷ��źθ� �Ұ�� Ŭ���̾�Ʈ���� -1�� �־ ������� �Ѵ�.
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

			// �ڽ��� ������ �������� �����Ѱ� üũ
			for (int k=0;k<MAX_TRADE;k++)
			{	
                if	(m->Item[k].snIndex!=0)
				{	// �����ǰ� â�� ������ Ʋ����, return;
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

			////////////////////// ����� �ŷ����� üũ - ��밡 �ٸ� ����� �ŷ����ΰ� 
			int UserTarget = pUser[conn].Trade.OpponentID;
			// ��ŷ� ��밡 �ڽ��ΰ�� �����۰� �� üũ. �ƴҰ��� �ݵ�� 0�̾�� �ŷ� ����.
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

			// 1. ����� OpponentID�� 0 �̸� �ڽŸ� ���۳�Ʈ�� ���� �����ϰ� �ŷ� ��Ŷ�� �ѱ�.
			if	(pUser[target].Trade.OpponentID==0)
			{	pUser[conn].Trade = *m;
				pUser[conn].Trade.MyCheck = 0;
				pUser[conn].Trade.TradeMoney = 0;
				// ���۳�Ʈ�� �ڵ� ����.
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
			// ��밡 �̹� �ڽŰ� �ŷ����ΰ��. ����� MyCheck==1 �̰� m->MyCheck==1 �̸� �ٷ� �ŷ�.
		    
            if  (m->MyCheck==1)
			{	pUser[conn].Trade.MyCheck=1;
				//pUser[conn].Trade.KeyWord  = m->KeyWord;
				//pUser[conn].Trade.CheckSum = m->CheckSum;
				pUser[conn].Trade.wSeq = m->wSeq;
				pUser[conn].Trade.dwClientTick =   m->dwClientTick;
				int ret = memcmp(&pUser[conn].Trade,m,sizeof(MSG_Trade));
				if  (ret) // üũ��ư Ŭ�� ���� ���ʴ� �ŷ� ���.
				{	RemoveTrade(conn, REPLY_TRADE_ERROR);
					RemoveTrade(target, REPLY_TRADE_ERROR);
					Log("err msg_trade - Click check button but diffrent data",pUser[conn].AccountName,pUser[conn].IP);
					return;
				} 
				if (pUser[target].Trade.MyCheck==1)
				{
					// �ŷ�����.
					if	(pUser[conn].Trade.TradeMoney<0||pUser[conn].Trade.TradeMoney>200000000)
					{	RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
					}
					if	(pUser[target].Trade.TradeMoney<0||pUser[target].Trade.TradeMoney>200000000)
					{	RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
					}

					int conncoin = pMob[conn].MOB.nRupiah - pUser[conn].Trade.TradeMoney + pUser[target].Trade.TradeMoney;
					if	(conncoin>2000000000 || conncoin<0)
					{	//	SendClientMessage(conn,g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
					}
					int tarcoin = pMob[target].MOB.nRupiah - pUser[target].Trade.TradeMoney + pUser[conn].Trade.TradeMoney;
					if	(tarcoin>2000000000 || tarcoin<0)
					{	//	SendClientMessage(target,g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
						RemoveTrade(conn, REPLY_TRADE_ERROR);
						RemoveTrade(target, REPLY_TRADE_ERROR);
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

					pMob[conn].DecGold(pUser[conn].Trade.TradeMoney);
					pMob[conn].IncGold(pUser[target].Trade.TradeMoney);
					pMob[target].DecGold(pUser[target].Trade.TradeMoney);
					pMob[target].IncGold(pUser[conn].Trade.TradeMoney);

					// Trade �α�
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
				{   // �ƴϸ� ����. Check�� ���������� �ʴ´�.
					//	SendClientSignal( conn,conn,_MSG_CNFCheck); // �������� �ݹ� 
   				    m->nID         = target;
				    m->OpponentID = conn;
				    pUser[target].cSock.AddMessage((char*)m,sizeof(*m)); // ��뿡�� ����.
                    return;
                    // ���۳�Ʈ�� Check�̸� �ŷ����� �ƴϸ� �޽��� �ѱ��.
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

			if(nID==conn)			//	�ڽ��� �ŷ���� ����
			{	if(pUser[conn].byTradeMode==m->byMode) 
				{	SendClientMessage(conn, g_pMessageStringTable[_MobStore_Set_Already]); return;
				}
						
				if(m->byMode != 0)
				{	time_t now; time(&now);
					bool bCash = true;
					if(now>(int)pUser[conn].m_time[eTime_Store] || pUser[conn].m_snTimeMode&0x4000) bCash=false;

					for(int i=0; i<MAX_MOBSTORE; i++)					//	item ��ȿ���˻�
					{	int nIndex=m->TradeItem[i].nIndex;
						if(nIndex<0 || nIndex>=pMob[conn].byMaxInven) {SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Index]); return;}
						if(m->TradeItem[i].item.snIndex==0) continue;
						STRUCT_ITEM* pSour = &(pMob[conn].MOB.Inven[nIndex]);
						STRUCT_ITEM* pDest = &(m->TradeItem[i].item);

						bool bRet=false;
						while(1)
						{	if(pSour->snIndex!=pDest->snIndex) break;
							if(pSour->byRefineLevel!=pDest->byRefineLevel ) break;
							if(memcmp(pSour->bySubRefine, pDest->bySubRefine, sizeof(BYTE)*MAX_SUBMATERIALSIZE)) break;
							if(m->TradeItem[i].item.snIndex!=0 && i>=MAX_MOBSTORE/2 && !bCash) break;	//	�������̰� ����Ҽ� ���� ������ �ε����� ä����
							if(pDest->byCount>pSour->byCount) break;
							bRet=true; break;
						}
						if(!bRet) {SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Data]); return;}
					}
				}

				pUser[conn].byTradeMode=m->byMode;
				if(m->byMode==0)						//	�ŷ���� ����
				{	memset(pUser[conn].TradeItem, 0, sizeof(pUser[conn].TradeItem));
					memset(pUser[conn].szTrade, 0, SZTRADE_LENGTH);
				}	else									//	�ŷ���� ����
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
			}	else					//	����� �ŷ��������� �˾ƿ�
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
			{	if(m->byIndex[i]!=1) continue;							//	1�� �ƴҰ��� �Ȼ�� ������.
				if(pUser[nID].TradeItem[i].item.snIndex==0) { byRet = _Invalid_Item_Data; break; }		//	����� ������ �̹� �ȸ����.
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
			{	if(m->byIndex[i]!=1) continue;							//	1�� �ƴҰ��� �Ȼ�� ������.
				if(pUser[nID].TradeItem[i].item.snIndex==0) { m->byIndex[i]=0; continue; }		//	����� ������ �̹� �ȸ����.
				int nMoney = pUser[nID].TradeItem[i].nPrice;
				if(pMob[conn].MOB.nRupiah<nMoney) { m->byIndex[i]=0; continue; }			//	���� ������ ���

				int nEmptyInven = GetEmptyInven(conn);
				if(nEmptyInven == MAX_INVEN) // ���ڸ� üũ
				{	for(int j=i; j<MAX_MOBSTORE; j++) m->byIndex[j]=0;
					SendClientMessage(conn, g_pMessageStringTable[_Inventory_Space_Lack]);	
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
				}

				int nIndex=pUser[nID].TradeItem[i].nIndex;
				if(nIndex<0 || nIndex>=pMob[nID].byMaxInven) {m->byIndex[i]=0; continue;}

				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byType = SET_ITEM_CREATE;	//	������ ����
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nEmptyInven;
				itemset.sitem = pMob[nID].MOB.Inven[nIndex];
				itemset.sitem.byCount = pUser[nID].TradeItem[i].item.byCount;
				pMob[conn].DecGold(nMoney);

				pMob[conn].MOB.Inven[nEmptyInven]=pMob[nID].MOB.Inven[nIndex];
				pMob[conn].MOB.Inven[nEmptyInven].byCount=pUser[nID].TradeItem[i].item.byCount;
				pUser[conn].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

				pMob[nID].IncGold(nMoney);

				// ���λ����� ������ �α׷� �����.
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

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	�����ڿ��� ���԰���� �˸���

			int nRemain=0;
			for(int i=0; i<MAX_MOBSTORE; i++)
			{	if(pUser[nID].TradeItem[i].item.snIndex==0) m->byIndex[i]=0;
				else { m->byIndex[i]=1; nRemain++; }
			}
			pUser[nID].cSock.SendOneMessage((char*)m, sizeof(*m));		//	�Ǹ��ڿ��� �ǸŰ���� �ȸ���.
			if(nRemain==0)												//	�������� ���� �ȷ��� ���
			{	pUser[nID].byTradeMode=0;								//	�Ǹ��� �� �Ǹ��� �ֺ����� �ǸŰ���� �ȸ���.
				memset(pUser[nID].TradeItem, 0, sizeof(pUser[nID].TradeItem));
				//MSG_MobStore nm; nm.wType=_MSG_MobStore;				//	(�Ǹ����� ���θ�� ������ client���� �ϱ����)
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
	case CSP_REQ_ITEM_MOVE:		// ����, �κ�, â���� ������ �̵�
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
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

			//	Packet ��ȿ���˻�  *item = &item
			bool bCheck=false;	int nItemIndex=0;	int nResult=0;
			while(1)
			{
				if(m->byFromPlace==ITEM_PLACE_GUILDCARGO || m->byToPlace==ITEM_PLACE_GUILDCARGO)
				{
					if ((ServerIndex+1) != SERVER_KATANA3) break;				//	���â���� īŸ��3������ �̿밡��
					int nGuildIndex = pUser[conn].nGuildIndex;
					if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) break;			//	������ �ɸ��� ��û�� 
					WORD wCargo = 0;
					
					if(m->byFromPlace==ITEM_PLACE_GUILDCARGO)
						if(!pGuild[nGuildIndex].IsUsableCargo(pUser[conn].nGuildLevel, m->snFromIndex)) { sm.nResult=REPLY_ITEM_MOVE_RIGHT; break; }	//	�������� ���� �ƽ���â���� ���
					if(m->byToPlace==ITEM_PLACE_GUILDCARGO)
						if(!pGuild[nGuildIndex].IsUsableCargo(pUser[conn].nGuildLevel, m->snToIndex)) { sm.nResult=REPLY_ITEM_MOVE_RIGHT; break; }	//	�������� ���� �ƽ���â���� ���

					//if (strncmp(pGuild[nGuildIndex].szCargoMember, pMob[conn].MOB.szName, SZNAME_LENGTH) != 0)	//	�������� �������
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
				{	if (m->snFromIndex<0||m->snFromIndex>=(MAX_CARGO*3)) break;	//	�������� â����ġ�������� üũ
					sour = &pGuild[pUser[conn].nGuildIndex].GUILD.Repository[m->snFromIndex];
					if(sour->snIndex==0) break;
				}
				else
					break;

				//////////////////////////////////////////////////////////////////////////////////////////////-DEST
				
				//////////// ����Ʈ ���� �������� �κ� �̿��� ������ �̵��� �� ����.	//////////////////////////////
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
					if((eKalaCore_Brahma - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break ;
					if((eKalaCore_Vishnu - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break ;
					if((eKalaCore_Siva - HT_PARAMTYPE_ITEM_START + 1) == sour->snIndex ) break ;
					dest = &pUser[conn].Cargo[m->snToIndex];
				}	else
				if	(m->byToPlace == ITEM_PLACE_GUILDCARGO)
				{	if (m->snToIndex<0||m->snToIndex>=MAX_CARGO*3) break;
					dest = &pGuild[pUser[conn].nGuildIndex].GUILD.Repository[m->snToIndex];

					int nPrice = 0;
					int nShopItemIndex = (dest->snIndex)+HT_PARAMTYPE_ITEM_START-1;
					if(!g_ParamMgr.HT_bGetItemSellRupiah(nShopItemIndex, &nPrice))
					{
						char strItem[128];
						BASE_GetItemCode(dest, strItem);
						sprintf(temp,"RemoveItem from move to guildcargo %s",strItem);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						ZeroMemory(dest, sizeof(STRUCT_ITEM));
					}
					
					if(dest->snIndex != 0) break;	//	���â���� ��� ������ ��ü�� �ȵȴ�. ����մ� ���â�� �ε����� �������� ä��� �ִ�
				}	else
				{   Log("dbg Trading Fails.SwapItem dest type",pUser[conn].AccountName,pUser[conn].IP); break;
				}

				if(m->byToPlace == ITEM_PLACE_EQUIP)	//	������������ ��������ȿ���˻�
				{	
					//if(pItemData[sour->snIndex].byLevel<=ITEM_EQUIP_LEVEL)							//	����5���Ͼ����� �������Ѱ˻�
						//if(pItemData[sour->snIndex].kReq.byLevel > pMob[conn].MOB.byLevel) break;

					int nLimit = 0; int nTribe = (int)pMob[conn].MOB.snTribe;
					if(!g_ParamMgr.HT_bGetItemLimitTribe( nItemIndex, &nLimit )) break;		//	�ش�������� �����Ӽ�ġ�� �������Ұ��. 
					if( nLimit!=0 && !( nTribe & nLimit ) ) break;										//	�����Ӽ��� �ٸ� �������������(��ŷ����)

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
								}	//	else	������ �Ƽ����̰� �����տ� ���ڵ幫�⸦ ��� ����̸��ٷ�ī�� ����ٸ� �ܰ��� �޼����밡���ϴ�.
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

				////	���Ұ����� �κ����������� �������̵��� ���´�
				//if((m->byFromPlace)==ITEM_PLACE_INVEN && (m->snFromIndex)>=pMob[conn].byMaxInven) break;
				//if((m->byToPlace)==ITEM_PLACE_INVEN && (m->snToIndex)>=pMob[conn].byMaxInven) break;

				//	Ȯ���κ��� ����������� Ȯ��bag�� ������ ����.
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

			//	�߸��� ��Ŷ�� ���
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
			// ����
			*dest =  tempsour;
			*sour =  tempdest;

			BOOL bEquip = false;	 
			if( ITEM_PLACE_EQUIP==m->byFromPlace && (ITEM_PLACE_CARGO==m->byToPlace || ITEM_PLACE_INVEN==m->byToPlace || ITEM_PLACE_GUILDCARGO==m->byToPlace))		//	������ Ż��
			{	bEquip= true;
				(m->snFromIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempsour, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempsour, eAfn_Remove );
				(m->snToIndex == eTNEqu_Shield)	? pMob[conn].EquipItem( &tempdest, eAfn_Add, true ) : pMob[conn].EquipItem( &tempdest, eAfn_Add );
				//if(CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(nItemIndex))			//	�κ�Ȯ������� Ż���� 
				//{	pMob[conn].byMaxInven=MAX_ONEINVEN;
				//}
			}	else 
			if((ITEM_PLACE_CARGO==m->byFromPlace || ITEM_PLACE_INVEN==m->byFromPlace || ITEM_PLACE_GUILDCARGO==m->byFromPlace) && ITEM_PLACE_EQUIP==m->byToPlace )	//	������ ����
			{	bEquip= true;
				(m->snFromIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempsour, eAfn_Add, true ) : pMob[conn].EquipItem( &tempsour, eAfn_Add );
				(m->snToIndex == eTNEqu_Shield) ?   pMob[conn].EquipItem( &tempdest, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempdest, eAfn_Remove );
				//if(CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(nItemIndex))			//	�κ�Ȯ������� ������
				//{	int nSize=0;	g_ParamMgr.HT_bGetItemEffect1Param1( nItemIndex, &nSize );
				//	pMob[conn].byMaxInven += nSize*MAX_INVEN_Y;
				//	if(pMob[conn].byMaxInven <= 0) pMob[conn].byMaxInven=MAX_ONEINVEN;
				//}
			}

			pMob[conn].UpdateEquipmentPoints() ;
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
			if(m->byFromPlace==ITEM_PLACE_GUILDCARGO && m->byToPlace==ITEM_PLACE_GUILDCARGO)		//	���â������ ���â���� �ű� ���
			{
				nm.nFromIndex = m->snFromIndex;
				nm.nToIndex = m->snToIndex; nm.item = *dest; 
			}
			else if(m->byFromPlace==ITEM_PLACE_GUILDCARGO && m->byToPlace!=ITEM_PLACE_GUILDCARGO)	//	���â���� �ܺ��� �������� ��ü��
			{
				nm.nFromIndex = m->snFromIndex;
				nm.nToIndex = -1; nm.item = *sour; 
			}
			else if(m->byFromPlace!=ITEM_PLACE_GUILDCARGO && m->byToPlace==ITEM_PLACE_GUILDCARGO)	//	���â���� �ܺ��� �������� ��ü��
			{
				nm.nFromIndex = -1;
				nm.nToIndex = m->snToIndex; nm.item = *dest; 
			}

			if(!DBServerSocket.SendOneMessage((char*)&nm,sizeof(nm)))
			{	Log("err Msg_GuildItemUpdate DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}

 			// CNF�� �ʿ��Ѱ�?
			// EQUIP�� ��� ITEM�������� �ɷ�ġ, ������ �������� Ŭ����
			// CARRY,CARGO�� ��� ������ ���ð��� GRID�� üũ.
		}  break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case CSP_REQ_ITEM_GET:
		{
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
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

			if(tx<GridX-5 || tx>GridX+5 ||ty<GridY-5 || ty>GridY+5)		//	�������� 5�� �̳��� �����۸� �ݱⰡ �����ϴ�
			{	itemget.nResult = REPLY_ITEM_MOVE_DISTANCE_ERR;
				pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;
			}

			bool bIsKalaCore = false ;
			int iKalaCore = nItemIndex ;
			if( (eKalaCore_Brahma == nItemIndex) || (eKalaCore_Vishnu == nItemIndex) || (eKalaCore_Siva == nItemIndex) ) bIsKalaCore = true ;
			if( (eTNVSAfn_HaveKalaCore & pMob[conn].m_iAffections) && bIsKalaCore ) return ;	// kala-core�� ������ �ִµ� �� Į���ھ �ֿ���� �Ѵٸ�, �ݱ� ����(���� ���Ѵ�.)
			if( bIsKalaCore && pMob[conn].m_kWaitAction.iAction != eWaitAct_None ) return;		// �̵�(Ǫ��Ƽī������)�� �������� �ֿ�� ����	

			if(pItem[itemid].m_iOwner != 0)				//	�켱������ �������
			{	if(CurrentTime<pItem[itemid].m_uiReleaseTime)	// �ݱ�켱�ð��� ������� ����.
				{	if(pItem[itemid].m_iOwner!=conn && pItem[itemid].m_iOwner!=pMob[conn].Leader)	//	������ �ƴϱ� ��Ƽ���� �ƴҰ��
					{	itemget.nResult = REPLY_ITEM_MOVE_ROUTING_TIME;
						pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));
						sprintf(temp,"Getitem routing error name:%s charid:%d partyleader:%d itemowner:%d", pMob[conn].MOB.szName, conn, pMob[conn].Leader, pItem[itemid].m_iOwner);
						WriteLog(temp,".\\MonsterLog\\[Log]RoutingFail.txt");
						return;
					}
				}
			}

			//	���ýý����߰�(2004.05.06)
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

				if(nCount>=2)							//	�й�������(share=1)
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

			/*		���� ���� ���		*/
			if(CHTParamIDCheck::HT_bIsItemUsableMoney( nItemIndex ))					//	Money�� �ֿ���
			{	if(nCount<1) nCount=1;
				int nRupiah = pItem[itemid].Money/nCount;
				if(byShare)		//	default(��Ƽ�й�)
				{	
					for (int i=0;i<MAX_PARTY+1;i++)
					{   if (i==0) fol = leader;
						else      fol = pMob[leader].m_irgParty[i-1];
   	 					if	(fol<=0||fol>=MAX_USER) continue;
						if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
						//nRupiah *= (pMob[fol].m_dGetMoneyRate/100);
						pMob[fol].IncGold(nRupiah);														//  �ֿ��� �� ����
						itemget.dwMoney = pMob[fol].MOB.nRupiah;
						pUser[fol].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));	//	���� �ֿ��ٴ� ���� �˸���.
					}
				}
				else			//	���κй�
				{	//nRupiah *= (pMob[conn].m_dGetMoneyRate/100);
					pMob[conn].IncGold(nRupiah);												//  �ֿ��� �� ����
					itemget.dwMoney = pMob[conn].MOB.nRupiah;
					pUser[conn].cSock.AddMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));	//	���� �ֿ��ٴ� ���� �˸���.
				}

				//	���� �ִ� ���������� ����.(�α�)
				//if	(BASE_NeedLog(&pItem[itemid].ITEM, pItem[itemid].Money)==NULL)	continue;
				if(pItem[itemid].Money>1000)
				{	sprintf(temp,"get money:%d", pItem[itemid].Money);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				}

				SendItemDisappear(GridX, GridY, itemid, conn);									//	�������� ������� �˸���.
				memset(&(pItem[itemid].ITEM),0,sizeof(STRUCT_ITEM));
				pUser[conn].cSock.SendMessage();
				return;
			}
			/****************************/

			//	�����۰����� ������� ��ø�������� ���������ۿ� �߾��� ��Ų��.
			BYTE byMax=0; bool bDisappear=false; 
			BYTE byFirst=pItem[itemid].ITEM.byCount;
			g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMax );
			if(byMax>1)		//	�ֿ�������� ��ø�������� ���
			{	BYTE byCount = pItem[itemid].ITEM.byCount;
				nOwner = conn;
				for(int i=0; i<pMob[conn].byMaxInven; i++)
				{
					if(pItem[itemid].ITEM.snIndex==pMob[conn].MOB.Inven[i].snIndex)
					{	if(pMob[conn].MOB.Inven[i].byCount>=byMax) continue;
						BYTE byDiff = byMax-pMob[conn].MOB.Inven[i].byCount;
						if(byCount<=byDiff) 
						{	pMob[conn].MOB.Inven[i].byCount+=byCount; 
							bDisappear=true;		//	���� ��ø�Ǿ� ������ �����.
							//	��ø�� �������� �˸���.
							S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
							nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
							nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
							pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
							break;
						}
						pMob[conn].MOB.Inven[i].byCount=byMax; 
						byCount -= byDiff; pItem[itemid].ITEM.byCount = byCount;
						//	��ø�� �������� �˸���.
						S_SCP_RESP_ITEM_SET nm; nm.wType=SCP_RESP_ITEM_SET;
						nm.byType=SET_ITEM_CREATE; nm.byPlace = ITEM_PLACE_INVEN;
						nm.byIndex=i; nm.sitem=pMob[conn].MOB.Inven[i];
						pUser[conn].cSock.AddMessage((char*)&nm,sizeof(nm));
					}
				}
			}
	
			if(!bDisappear && byFirst!=pItem[itemid].ITEM.byCount)		//	��������ø�� �ϰ� ������ ���(�κ��� ������)
			{	itemget.nResult = REPLY_ITEM_MOVE_PART;
				pUser[conn].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;	
			}

			int	emptyinven=0; 
			if(!bDisappear)
			{	for(int i=0; i<nCount; i++)
				{	emptyinven = GetEmptyInven(nOwner);		//	���ڸ��˻�.
					if(emptyinven<0 || emptyinven>=pMob[nOwner].byMaxInven) 
					{	if(nCount<=1 || byMax>1)
						{	itemget.nResult = REPLY_ITEM_MOVE_INVENTORY_LACK;	//	��Ƽ������ ������� ���� ���
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

			//	�����ڵ����(���� ������ ���ٰ�)
			if(emptyinven<0 || emptyinven>=pMob[nOwner].byMaxInven)
			{	itemget.nResult = REPLY_ITEM_MOVE_INVENTORY_LACK;	//	��Ƽ������ ������� ���� ���
				pUser[nOwner].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET)); return;	
			}

			pUser[nOwner].cSock.AddMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));
			SendItemDisappear(GridX, GridY, itemid, nOwner);						//	SCP_MAP_ITEM_DISAPPEAR ����

			#ifdef __TN_PLAYMOVIE__
			{
				// ��ü ������ �Ѵ�.
				char szMsg[1024] = { 0,0,0, } ;	
				sprintf( szMsg, g_pMessageStringTable[_PickUpItem], pMob[conn].MOB.szName ) ;
				PostMessageToZone( szMsg ) ;
			}
			#endif

			if( bIsKalaCore ) // kala-core�� ó�� �ݴ� ���, ...
			{
				pMob[nOwner].TurnOffAffection( eTNAfn_Invisible ) ;
				pMob[nOwner].m_iAffections = pMob[nOwner].m_iAffections | eTNVSAfn_HaveKalaCore ;
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_Invulnerable ;
				kEffect.iDuration = 3000 ;
				kEffect.iParam1 = 100 ;
				kEffect.iParam2 = 0 ;
				pMob[nOwner].AddEffect( kEffect, nOwner, nOwner ) ;
				pMob[nOwner].BroadcastUpdateStatusMsg() ;

				// ���� kala-core�� ȹ���ߴٴ� �޽���(���� ��ǥ ���)
				int iTxtIndex = 0 ;
				if( eKalaCore_Brahma == iKalaCore ) iTxtIndex = _Brahma ;
				else if( eKalaCore_Vishnu == iKalaCore ) iTxtIndex = _Vishnu ;
				else if( eKalaCore_Siva == iKalaCore ) iTxtIndex = _Siva ;

				int iTrimuritiIndex = 0 ;
				if( eTNClan_Brahma == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Brahma ;
				else if( eTNClan_Vishnu == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Vishnu ;
				else if( eTNClan_Siva == pMob[nOwner].m_byClan ) iTrimuritiIndex = _Siva ;

				char szMsg[1024] = { 0,0,0, } ;	
				sprintf( szMsg, g_pMessageStringTable[_PickUp_Kala_Core]
					, g_pMessageStringTable[iTrimuritiIndex], pMob[nOwner].MOB.szName, pMob[nOwner].TargetX, pMob[nOwner].TargetY, g_pMessageStringTable[iTxtIndex] ) ;
				PostMessageToZone( szMsg ) ;

				{
					SYSTEMTIME st ;
					GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					strcat( szMsg, chBuf ) ;
					WriteLog( szMsg, ".\\Log\\[Log]KalaSystem.txt" ) ;
				}

				pUser[nOwner].cSock.SendMessage() ;

				g_kKalaSystem.ChangeKalaLoc( TNKalaSystem::eLoc_Ground, 0, 0, GridX, GridY, 0, TNKalaSystem::eLoc_Inventory, 0, 0, 0, 0, nOwner ) ;
			}

			if(!bDisappear)
			{	S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byType = SET_ITEM_CREATE;	//	������ ����
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = emptyinven;
				itemset.sitem = pItem[itemid].ITEM;
				pMob[nOwner].MOB.Inven[emptyinven] = pItem[itemid].ITEM;
				pUser[nOwner].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

				//	���� �ִ� �������� ����.(���� �α�)
				char strItem[128];
				short snIndex = pItem[itemid].ITEM.snIndex;
				if (BASE_CheckItemLog(&pItem[itemid].ITEM))
				{	BASE_GetItemCode(&pItem[itemid].ITEM,strItem);
					sprintf(temp,"get %s",strItem);
					Log(temp,pUser[nOwner].AccountName,pUser[nOwner].IP);
				}
			}	else
			{	//	���� �ִ� �������� ����.(��ø�� ����� �α�)
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
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
			S_CSP_REQ_ITEM_DROP * m = (S_CSP_REQ_ITEM_DROP*) msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_DROP);
				return;
			}

			int iCoordX, iCoordY ;

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

			/*		���� ����߸����		*/
			if(m->dwMoney>0)   
			{	itemdrop.byType = DROP_TYPE_MONEY;
				if(m->byFromPlace==ITEM_PLACE_INVEN)
				{	if(m->dwMoney>(DWORD)pMob[conn].MOB.nRupiah)
					{	itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
						pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
						return;
					}
					
					pMob[conn].DecGold(m->dwMoney);								//  ������ �κ��� ����
					itemdrop.dwMoney = pMob[conn].MOB.nRupiah;
				}	else
				if(m->byFromPlace==ITEM_PLACE_CARGO)
				{	if(m->dwMoney>(DWORD)pUser[conn].Coin)
					{	itemdrop.snResult = REPLY_ITEM_MOVE_PLACE_ERR;
						pUser[conn].cSock.SendOneMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));
						// �پ�� MOB�� ���� �����Ѵ�.
						
						pMob[conn].IncGold(m->dwMoney);
						return;
					}
					pUser[conn].Coin -= m->dwMoney;									//  ������ â���� ����
					itemdrop.dwMoney = pUser[conn].Coin;
				}	else
				{	AddCrackError(conn,50,CRACK_USER_PKTHACK);
					return;
				}

				pUser[conn].cSock.AddMessage((char*)&itemdrop, sizeof(S_SCP_RESP_ITEM_DROP));

				int nItemIndex = g_ParamMgr.HT_iGetIndexForMoneyItem(m->dwMoney);
				STRUCT_ITEM item; ZeroMemory(&item, sizeof(STRUCT_ITEM));
				item.snIndex=nItemIndex-HT_PARAMTYPE_ITEM_START+1;
				
				iCoordX = m->snX ;
				iCoordY = m->snZ ;
				int destidx = CreateItem( iCoordX, iCoordY, &item, 0, m->dwMoney);						//	�������ۻ���

				//	���� ������� �α�
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
			STRUCT_ITEM tempitem ;
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

			//	Item Create & SCP_MAP_ITEM_APPEAR ����
			iCoordX = m->snX ;
			iCoordY = m->snZ ;
			int destidx = CreateItem( iCoordX, iCoordY,sour);

			memset((void*)sour,0,sizeof(STRUCT_ITEM));

			if	(m->byFromPlace==ITEM_PLACE_EQUIP)
			{
				(m->byIndex == eTNEqu_Shield) ? pMob[conn].EquipItem( &tempitem, eAfn_Remove, true ) : pMob[conn].EquipItem( &tempitem, eAfn_Remove );
				pMob[conn].UpdateEquipmentPoints() ;
				pMob[conn].NotifyUpdateUIMsg();
			}

			//	�������� ������� �α�
			char strItem[128];
			short snIndex = pItem[destidx].ITEM.snIndex;
			//if	(BASE_NeedLog(&pItem[destidx].ITEM, 0)==NULL)	continue;
			if (BASE_CheckItemLog(&pItem[destidx].ITEM))
			{					
				BASE_GetItemCode(&pItem[destidx].ITEM,strItem);
				sprintf(temp,"drop %s",strItem);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
			}

			////	SCP_RESP_ITEM_SET ����
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
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
			MSG_Packing * m = (MSG_Packing*) msg;
			
			m->byResult = 1;
			STRUCT_ITEM* sour=NULL; STRUCT_ITEM* dest=NULL;
			sour = GetItem(conn, m->byFromPlace, m->byFromIndex);
			dest = GetItem(conn, m->byToPlace, m->byToIndex);

			if(sour==NULL || dest==NULL) break;

			int nSourIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			int nDestIndex = (dest->snIndex)+HT_PARAMTYPE_ITEM_START-1;
			if(m->byType==TYPE_ITEM_PACKING)
			{	if(sour->snIndex==0 || dest->snIndex==0)				//  �������� ������� ��� ����
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}		
				if(sour->snIndex != dest->snIndex)						//	���δٸ� ������ �������� ��ø�� ����
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}
				BYTE byMax = 0; int byTotal = (dest->byCount)+(sour->byCount);
				g_ParamMgr.HT_bGetItemMaxCount( nDestIndex, &byMax );
				if(byTotal>byMax)	//	��ø�ִ���� �ʰ���
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
			{	if(m->byFromPlace!=m->byToPlace)						//	������ ���������� ����ŷ�� �ƴҰ�� ����
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}						

				BYTE byMax = 0; bool bRet = g_ParamMgr.HT_bGetItemMaxCount( nSourIndex, &byMax );
				if(!bRet)
				{	SendClientMessage(conn, g_pMessageStringTable[_Invalid_Item_Data]);
					return;
				}	
				if(sour->byCount>byMax) sour->byCount=byMax;
				if(sour->byCount <= m->byToCount || m->byToCount<=0)	//	����ŷ�� ���ڰ� �������� ������ ���� ���.
				{	m->byResult=1; pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
					return;
				}					
				if(sour->snIndex==0 || dest->snIndex!=0)				// 	����ŷ�� ��ǥ��ġ�� �������� ������ ���
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
			//	������ �޼��� ����
			m->byResult = 0;
			pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
		}	break;
	case _MSG_Money_Move:	// deposit coin to account inventory.
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
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

			int coin = pMob[conn].MOB.nRupiah;
			int cargocoin = pUser[conn].Coin;
			sprintf(temp, "dbg Move_Money:%d from Inven:d Cargo:%d ", m->dwMoney, coin, cargocoin);
			if(m->byFromPlace==ITEM_PLACE_INVEN)
			{	if(m->byToPlace==ITEM_PLACE_CARGO)
				{	cargocoin += m->dwMoney;
					coin -= m->dwMoney;
					if(coin<0 || cargocoin>2000000000)
					{	SendClientMessage(conn,g_pMessageStringTable[_Cant_Deposit_That_Much]);
					return;
					}
					pMob[conn].DecGold(m->dwMoney);

					m->dwFromMoney = pMob[conn].MOB.nRupiah;
					m->dwToMoney = cargocoin;

					if(m->dwMoney>=LOGMONEY)
					{	sprintf(temp,"dbg move money i->c [%s] %d", pMob[conn].MOB.szName, m->dwMoney);
						Log(temp, pUser[conn].AccountName, pUser[conn].IP);
					}
				}
			}	else
			if(m->byFromPlace==ITEM_PLACE_CARGO)
			{	if(m->byToPlace==ITEM_PLACE_INVEN)
				{	cargocoin -= m->dwMoney;
					coin += m->dwMoney;
					if(cargocoin<0 || coin>2000000000)
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
	case	CSP_REQ_ITEM_BUY:	// NPC���� ��ǰ���
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ��.
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
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	�ش� NPC������ ���� ���Ұ��.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC�� ���� ���� ���� ���� ���.

			S_SCP_RESP_ITEM_BUY sm; sm.wType = SCP_RESP_ITEM_BUY;
			sm.byResult=REPLY_ACK_OK; sm.snItemIndex = snIndex;

			if(!CHTParamIDCheck::HT_bIsNPC(snNpc))
			{	sprintf(tmp,"CSP_REQ_ITEM_BUY: Item_buy char:%s invalid npc id:%d", pMob[conn].MOB.szName, snNpc);
				CrackLog(conn, tmp); CloseUser(conn); return;
			}
			if(!CHTParamIDCheck::HT_bIsChargeNPC(snNpc) && 
				(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY)) return; //	NPC Grid���� �÷��̾ ���� ���

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
				{	SendClientMessage(conn,g_pMessageStringTable[_Serverdown_Itemserver]);	//	ĳ������ �ٿ��
					return;
				}
				bResult  &= g_ParamMgr.HT_bGetItemCash		(nItemIndex, &nPrice); 
				nTotPrice = nPrice*snCount;
				if(CHTParamIDCheck::HT_bIsItemChargeContinuance(nItemIndex))		//	���Ӿ����۱��Խ�(���������)
				{	if(snCount>GetEmptyInvenCount(conn))								//	�����Ϸ��� �������� ���� ������ ���� ���
					{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
						pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
					}
					if( g_eCountryID == eCountryIndonesia )
					{	;
					}
					else if( g_eCountryID == eCountryChina )
					{	if(nPrice>=30)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���̻�¥�� 10���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̻�¥�� 5���̸� ���ԺҰ�
						}	else
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.9/10)*10);				//	100���̸�¥�� 20���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̸�¥�� 10���̸� ���ԺҰ�
						}
					}
					else if( g_eCountryID == eCountryJapan )
					{	if(nPrice>=100)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���̻�¥�� 10���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̻�¥�� 5���̸� ���ԺҰ�
						}	else
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���̸�¥�� 20���̻��Խ� ����
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̸�¥�� 10���̸� ���ԺҰ�
						}
					}
					else
					{	if(nPrice>=100)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���̻�¥�� 10���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̻�¥�� 5���̸� ���ԺҰ�
						}	else
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���̸�¥�� 20���̻��Խ� ����
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���̸�¥�� 10���̸� ���ԺҰ�
						}
					}
					snCount *= byMaxCount;
				}	else															//	�Ϲݾ����۱��Խ�(���������)
				{	if((snCount+byMaxCount)/byMaxCount>GetEmptyInvenCount(conn))								//	�����Ϸ��� �������� ���� ������ ���� ���
					{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
						pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
					}
					if( g_eCountryID == eCountryIndonesia )
					{	;
					}
					else if( g_eCountryID == eCountryChina )
					{	if(nPrice>100)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);																			//	2300���ʰ�¥�� ���Խ� ������
						}
						else if(nPrice<=100 && nPrice>30)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600���ʰ� 1000������¥�� 5���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600���ʰ� 1000������¥�� 2���̸� ���ԺҰ�
						}
						else if(nPrice<=30 && nPrice>=15)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	300���ʰ� 600������¥�� 10���̻��Խ� ����
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300���ʰ� 600������¥�� 5���̸� ���ԺҰ�
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.9/10)*10);			//	100���ʰ�¥�� 40���̻��Խ� ����
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���ʰ�¥�� 20���̸� ���ԺҰ�
						}
					}
					else if( g_eCountryID == eCountryJapan )
					{	if(nPrice>2300)
						{	;																			//	2300���ʰ�¥�� ���Խ� ������
						}
						else if(nPrice<=2300 && nPrice>1000)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	1000���ʰ� 2300����¥�� 3���̻��Խ� ����
						}
						else if(nPrice<=1000 && nPrice>600)
						{	if(snCount>=5) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600���ʰ� 1000������¥�� 5���̻��Խ� ����
							if(snCount<2) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600���ʰ� 1000������¥�� 2���̸� ���ԺҰ�
						}
						else if(nPrice<=600 && nPrice>300)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	300���ʰ� 600������¥�� 10���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300���ʰ� 600������¥�� 5���̸� ���ԺҰ�
						}
						else if(nPrice<=300 && nPrice>100)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���ʰ� 300������¥�� 20���̻��Խ� ����
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���ʰ� 300������¥�� 10���̸� ���ԺҰ�
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���ʰ�¥�� 40���̻��Խ� ����
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���ʰ�¥�� 20���̸� ���ԺҰ�
						}
					}
					else
					{	if(nPrice>2300)
						{	;																			//	2300���ʰ�¥�� ���Խ� ������
						}
						else if(nPrice<=2300 && nPrice>1000)
						{	if(snCount>=3) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	1000���ʰ� 2300����¥�� 3���̻��Խ� ����
						}
						else if(nPrice<=1000 && nPrice>600)
						{	if(snCount>=5) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);			//	600���ʰ� 1000������¥�� 5���̻��Խ� ����
							if(snCount<2) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	600���ʰ� 1000������¥�� 2���̸� ���ԺҰ�
						}
						else if(nPrice<=600 && nPrice>300)
						{	if(snCount>=10) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	300���ʰ� 600������¥�� 10���̻��Խ� ����
							if(snCount<5) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	300���ʰ� 600������¥�� 5���̸� ���ԺҰ�
						}
						else if(nPrice<=300 && nPrice>100)
						{	if(snCount>=20) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���ʰ� 300������¥�� 20���̻��Խ� ����
							if(snCount<10) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���ʰ� 300������¥�� 10���̸� ���ԺҰ�
						}
						else
						{	if(snCount>=40) nTotPrice = (int)(((int)nPrice*snCount*0.8/10)*10);				//	100���ʰ�¥�� 40���̻��Խ� ����
							if(snCount<20) sm.byResult = REPLY_ITEM_BUY_MINCOUNT;						//	100���ʰ�¥�� 20���̸� ���ԺҰ�
						}
					}
				}
				if(sm.byResult==REPLY_ITEM_BUY_MINCOUNT) {pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;}
				if(!bResult)
				{	sm.byResult = REPLY_UNKNOWN;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
				if(pUser[conn].m_nCash<nTotPrice)		//	���� cash�� ��ü���԰��ݺ��� ������� ����ó��
				{	sm.byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
			}	else
			{	bResult  &= g_ParamMgr.HT_bGetItemRupiah		(nItemIndex, &nPrice); 
				nTotPrice = nPrice*snCount;
				if(ServerIndex==SERVER_TRIMURITI-1) nTotPrice = (int)(nTotPrice * 1.3) ;	//	�ֽ��������� �ǸŰ��� 30%��δ�
				if(!bResult || pMob[conn].MOB.nRupiah<nTotPrice)	//	���� ���Ǿư� ��ü���԰��ݺ��� ������� ����ó��
				{	sm.byResult = REPLY_ITEM_BUY_GOLD_WANT;
					pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY)); return;
				}
			}

			int i=0;
			for(i=0; i<pMob[conn].byMaxInven; i++)
			{	short snItem=pMob[conn].MOB.Inven[i].snIndex;
				if(snItem!=0) continue;		//	�κ��� ������ ���

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

			if(snCount == m->snItemCount)			// �ڸ��� ��� �������� �������� ���������
			{	sm.byResult = REPLY_ITEM_BUY_INVENTORY_LACK;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY));
				return;
			}

			if(CHTParamIDCheck::HT_bIsChargeNPC(snNpc))					//	����ȭ����
			{	pUser[conn].m_nCash -= nTotPrice;						//	������ �Ǳ��Ժ�� �谨
				sm.nMoney = pUser[conn].m_nCash;

				//	Item Server�� cash������ �˸���.
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
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
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
					if(g_dwCastleSalesMoney < 2000000000) g_dwCastleSalesMoney += (dwTex/2);
					nTotPrice +=  dwTex;
				}

				if(ServerIndex==SERVER_TRIMURITI-1) nTotPrice = (int)(nTotPrice * 1.3) ;	//	�ֽ��������� �ǸŰ��� 30%��δ�

				pMob[conn].DecGold(nTotPrice);							// ������ �Ǳ��Ժ�� �谨
				sm.nMoney = pMob[conn].MOB.nRupiah;
			}
			sm.byDummy = 0;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_BUY));
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case   CSP_REQ_ITEM_SELL:		// NPC���� ���� �ȱ�
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
			S_CSP_REQ_ITEM_SELL * m = (S_CSP_REQ_ITEM_SELL *) msg;

			if  (0>=pMob[conn].MOB.nHP || pUser[conn].Mode!=USER_PLAY)
			{   //	SendHpMode(conn);
				//	AddCrackError(conn,20,CRACK_NOUSER_SELL);
				return;
			}

			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	�ش� NPC������ ���� ���Ұ��.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC�� ���� ���� ���� ���� ���.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid���� �÷��̾ ���� ���
	
			S_SCP_RESP_ITEM_SELL sm; sm.wType = SCP_RESP_ITEM_SELL; 
			sm.byResult=REPLY_UNKNOWN; sm.byPlace=m->byPlace; sm.byIndex=m->byIndex;

			//	��ġ�� ������ ��ȿ�� �˻�
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

			//	������ �ش� �������� ���� ��� ����ó��
			if(sour == NULL)
			{	sm.byResult = REPLY_ITEM_SELL_OUTINDEX;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			//	������ �����ۿ� ���� �ڷᰡ ���� ��� ����ó��
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
			pMob[conn].UpdateEquipmentPoints() ;
			pMob[conn].NotifyUpdateUIMsg();

			pMob[conn].IncGold(nPrice);			// ������ �� ����

			sm.byResult=REPLY_ACK_OK; sm.nMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_SELL));
		}	break;
///////////////////////////////////////////////////////////////////////////////////////////////
	case   CSP_REQ_ITEM_REPAIR:		// NPC���� ���� ����
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
			S_CSP_REQ_ITEM_REPAIR * m = (S_CSP_REQ_ITEM_REPAIR *) msg;

			S_SCP_RESP_ITEM_REPAIR sm; sm.wType = SCP_RESP_ITEM_REPAIR; 
			sm.byResult=REPLY_UNKNOWN; sm.byPlace = m->byPlace; sm.byIndex=m->byIndex;
			sm.byDummy = 1;				//	0:������������� ����, 1:���ǾƷ� ����
			
			short snX,snY=0;  byte byZone=0; int nX=pMob[conn].TargetX; int nY=pMob[conn].TargetY;
			if(!g_ParamMgr.HT_bGetNPCPosition( m->snNPCIndex, &snX, &snY )) return;		//	�ش� NPC������ ���� ���Ұ��.
			if(!g_ParamMgr.HT_bGetNPCZone( m->snNPCIndex, &byZone )) return;
			if(byZone!=ServerIndex+1) return; // NPC�� ���� ���� ���� ���� ���.
			if(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY) return; //	NPC Grid���� �÷��̾ ���� ���

			//	��ġ�� ������ ��ȿ�� �˻�
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

			//	������ �ش� �������� ���� ��� ����ó��
			if(sour == NULL)
			{	sm.byResult = REPLY_ITEM_REPAIR_OUTINDEX;
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_SELL));
				return;
			}

			//	������ �����ۿ� ���� �ڷᰡ ���� ��� ����ó��
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
			if( sour->snDurability % 100 > 0 ) ++iCurDur;	// �ø� ó��
			float fPrice = ((HTfloat)nPrice / 10000.0f + (HTfloat)pow(nPrice, 0.85 ))*(HTfloat)(iMaxDur-iCurDur)/(HTfloat)iMaxDur;
			nPrice = (int)( fPrice * (float)sour->byCount);

			if(!bResult || nPrice>pMob[conn].MOB.nRupiah)
			{	sm.byResult = REPLY_ITEM_REPAIR_MONEY_WANT;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REPAIR));
				return;
			}

			sour->snDurability = sMaxDur;
			pMob[conn].DecGold(nPrice);			// ������ �� ����

			pMob[conn].UpdateEquipmentPoints();
			sm.byResult=REPLY_ACK_OK; sm.nMoney = pMob[conn].MOB.nRupiah;
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REPAIR));
		}	break;
	case   CSP_REQ_ITEM_REFINING:		// ������ ����
		{	
			if( eTNClan_GM == pMob[conn].MOB.byTrimuriti ) return ; // GM�̸�, �� �� ����.
			S_CSP_REQ_ITEM_REFINING * m = (S_CSP_REQ_ITEM_REFINING *) msg;

			S_SCP_RESP_ITEM_REFINING sm; sm.wType = SCP_RESP_ITEM_REFINING; 
			sm.byResult=REPLY_UNKNOWN; sm.byIndex=m->byIndex; sm.byPlace=m->byPlace;
			sm.bySubIndex[0]=m->bySubIndex[0]; sm.bySubPlace[0]=m->bySubPlace[0];
			sm.bySubIndex[1]=m->bySubIndex[1]; sm.bySubPlace[1]=m->bySubPlace[1];
			sm.bySubIndex[2]=m->bySubIndex[2]; sm.bySubPlace[2]=m->bySubPlace[2];

			//	��ġ�� ������ ��ȿ�� �˻�
			int nRefineItemIndex[3]={0,};
			STRUCT_ITEM *sour = NULL; STRUCT_ITEM *dest[3] = {0,};		//	��������� �κ��� �ִ� �͸� �����ϴ�
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

			//	������ �ش� �������� ���� ��� ����ó��
			if(sour==NULL || dest[0]==NULL)
			{	sm.byResult = REPLY_ITEM_REFINING_OUTINDEX;
				Log("err refineitem - Inven",pUser[conn].AccountName,pUser[conn].IP);
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_REFINING));
				return;
			}

			//	������ �����ۿ� ���� �ڷᰡ ���� ��� ����ó��
			if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA || dest[0]->snIndex<0 || dest[0]->snIndex>=MAX_ITEM_DATA)
			{	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_ITEM_REFINING));
				return;			
			}

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

			if(CHTParamIDCheck::HT_bIsItemRefineMain(nRefineItemIndex[0]))	//	����������
			{	nPrice = (int)(nPrice * ITEM_REFINING_COAT * pow(sour->byRefineLevel + 1, 1.8));

				//	����� �Ұ����� ������ ������ �������� ���� ����üũ�߰�(2004.11.19)	- Y.W.K
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

			if(m->bySubPlace[1]>0)	//	dest[1]�� ��ȿ��üũ
			{	if(!CHTParamIDCheck::HT_bIsItemRefineSub2( nRefineItemIndex[1] ))
				{	CrackLog(conn," CSP_REQ_ITEM_REFINING m->bySubPlace[1]>0"); 
					CloseUser(conn); return;
				}

				if(dest[1]!=NULL)
				{
					TNSKILL_DATA* pkSkill = (TNSKILL_DATA*)&pItemData[dest[1]->snIndex];

					for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
					{
						if( 0 >= pkSkill->krgEffect[i].iID ) continue ;
						switch( pkSkill->krgEffect[i].iID )
						{
						case eTNAfn_RefiningDiscount :
							{
								fDiscount = (float)pkSkill->krgEffect[i].iParam1;
								if(fDiscount<0) fDiscount = 0;
								else if(fDiscount>100) fDiscount = (float)100;
								nPrice *= (int)((100 - fDiscount)/100);
							}	break;
						default:
							break;
						}
					}
				}
			}
			if(m->bySubPlace[2]>0)	//	dest[2]�� ��ȿ��üũ
			{
			}

			int nRet = RefiningItem(conn, sour, dest);

			//	���ϴ� ���е� �����̵� �������� ���Ǿ��� �Ҹ� �ݿ��Ѵ�.
			pMob[conn].DecGold(nPrice);
			sm.nMoney = pMob[conn].MOB.nRupiah;

			char szFrom[256], szTo[256];
			BASE_GetItemCode( &tmpItem, szFrom );
			BASE_GetItemCode( sour, szTo );
			sprintf( temp, "ref Refine Result: %d, Price: %d Src: %d %s -> %s", nRet, nPrice, nRefineItemIndex[0], szFrom, szTo );
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			if(nRet > 0)
			{	sm.byResult = nRet;
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SCP_RESP_ITEM_REFINING));
				return;
			}

			//	SCP_RESP_ITEM_SET ����
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

			char szItemName[128]; byte byTrimuriti = pMob[conn].MOB.byTrimuriti ;
			int nScale = 0; BYTE byRet = 0;
			if(g_GateTick[byTrimuriti]>0 && ( ServerIndex+1 == SERVER_TRIMURITI ) )	//	���� Gateȭ��ȭ�� ���̻��� �峳�� �ʿ����
			{	m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1;
			}
			if( ServerIndex+1 == SERVER_STRONGHOLD ) 
				if(g_kArena.IsProgressed() || g_iBattleForStronghold>0)	//	���������ó� �Ʒ����̺�Ʈ ����ô� �峳�Ұ�
				{ m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; }
			

			if(byRet == 0)
			{
				for(int i=0; i<MAX_ITEM_CONTRIBUTION; i++)		//	��ġ�� ������ ��ȿ�� �˻�
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

					//	������ �ش� �������� ���� ��� ����ó��
					if(sour == NULL) {	m->byResult = REPLY_ITEM_CONTRIBUTION_OUTINDEX; byRet=1; break; }

					//	������ �����ۿ� ���� �ڷᰡ ���� ��� ����ó��
					if(sour->snIndex<0 || sour->snIndex>=MAX_ITEM_DATA) {	m->byResult = REPLY_ITEM_CONTRIBUTION_OUTINDEX; byRet=1; break; }

					//	�������� ��ø���� üũ(������ 0�� �������� �峳�ϴ� �ٹ߰�)
					if(sour->byCount<=0) {	m->byResult = REPLY_UNKNOWN; byRet=1; break; }

					bool bResult=0; int nPrice=0; BYTE byMax=0;
					int nShopItemIndex = (sour->snIndex)+HT_PARAMTYPE_ITEM_START-1;
					bResult  = g_ParamMgr.HT_bGetItemRupiah(nShopItemIndex, &nPrice); 
					bResult &= g_ParamMgr.HT_bGetItemMaxCount(nShopItemIndex, &byMax);

					//	�Ķ���� �˻�����
					if(!bResult) { m->byResult = REPLY_ITEM_CONTRIBUTION_OUTPARAM; byRet=1; break; }

					//	����Ʈ�������� ��� �Ұ�
					if ( CHTParamIDCheck::HT_bIsItemQuestOnly( nShopItemIndex ) ) { m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; break; }

					//	��ø�������� ��� �Ұ�
					if(byMax>1) { m->byResult = REPLY_ITEM_CONTRIBUTION_CANNOT; byRet=1; break; } 
					
					//if(g_bIsInRvR)			//	�ֽ��� ũ�縶�Ŵ�
					if( eZoneType_God == g_iZoneType )
					{	int nTemp = nPrice/(ITEM_CONTRIBUTION_DEVIDE*2);
						if(nTemp < 1) nTemp=1;
						nScale += nTemp;
					}
					else					//	������ �����׾Ƹ�
					{
						if(g_ItemRefineScale<10000)		//	�����׾Ƹ� Ȯ�� 10000/2000 �����ϰ��(�������峳)
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

            //	������� �Դٸ� ������ ���� ��Ŷ�̶�� ���̴�.(������ƾ����)
			//if(g_bIsInRvR)			//	�ֽ��� ũ�縶�Ŵ�
			if( ServerIndex+1 == SERVER_TRIMURITI )
			{
				nScale += (m->dwRupia/(ITEM_CONTRIBUTION_DEVIDE*2));
				int nX = 0; int nZ = 0;
				if(byTrimuriti<0 || byTrimuriti>eTNClan_Siva) { CloseUser(conn); return; }

				g_GateScale[byTrimuriti] += nScale; 
				if(g_GateScale[byTrimuriti] >= 10000)
				{
					g_GateScale[byTrimuriti] = 10000;
					g_GateTick[byTrimuriti] = 10;		//	32�ʸ��� 1������ ��320�ʰ� GateȰ��ȭ

					//	Gata Create
					if(byTrimuriti==eTNClan_Brahma)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Brahma, 0, 872, 102, 0, false ) ;
					else if(byTrimuriti==eTNClan_Vishnu)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Vishnu, 0, 129, 72, 0, false ) ;
					else if(byTrimuriti==eTNClan_Siva)
						g_hGate[byTrimuriti] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_Siva, 0, 426, 931, 0, false ) ;
					else
						{ CloseUser(conn); return; }
				}
			}	else
			if( ServerIndex+1 == SERVER_STRONGHOLD )
			{
				nScale = m->dwRupia;
				g_dwArenaMoney += nScale;
				if(g_dwArenaMoney>=MONEY_ARENAEVENT)				//	ARENA �̺�Ʈ �߻����� - 1���̻��� �Ʒ����Ӵϰ� �ְ�
				{	struct tm when; time_t now;						//	0~2��, 10~24�� ���̸� �̺�Ʈ�� �߻��Ѵ�.
					time(&now); when = *localtime(&now);
					if(when.tm_hour<2 || when.tm_hour>=10) g_kArena.Start( (int)g_dwArenaMoney ) ; //TriggerEvent( conn, 66, pMob[conn].TargetX, pMob[conn].TargetY, 0 );
				}
			}
			else					//	������ �����׾Ƹ�
			{
				if(g_ItemRefineScale+nScale+(m->dwRupia/ITEM_CONTRIBUTION_DEVIDE)<10000)	//	�����׾Ƹ� Ȯ�� 10000/2000 �����ϰ��(���Ǿ��峳)
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
				// ����Ʈ���� ���...
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
			if( ServerIndex+1 == SERVER_TRIMURITI ) m->snRefineScale = g_GateScale[byTrimuriti];
			//else if( ServerIndex+1 == SERVER_STRONGHOLD ) m->dwRupia = g_dwArenaMoney;
			else m->snRefineScale = g_ItemRefineScale;

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));
		}	break;
	case _MSG_RefineScale:
		{	MSG_RefineScale * m = (MSG_RefineScale * ) msg;

			if( ServerIndex+1 == SERVER_TRIMURITI ) m->snRefineScale = g_GateScale[pMob[conn].MOB.byTrimuriti];
			else if( ServerIndex+1 == SERVER_STRONGHOLD ) m->dwRupiah = g_dwArenaMoney;
			else m->snRefineScale = g_ItemRefineScale;

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));
		}	break;
	case CSP_REQ_CHAT:				//	�Ϲ�ä��	
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
	case CSP_REQ_WHISPER_CHAT:		//	�ͼӸ�	
		{	S_CSP_REQ_WHISPER_CHAT * m = (S_CSP_REQ_WHISPER_CHAT * ) msg;

			m->szName[SZNAME_LENGTH-1] = 0; m->szName[SZNAME_LENGTH-2] = 0;
			m->szMsg[MAX_CHAT_LENGTH-1] = 0; m->szMsg[MAX_CHAT_LENGTH-2] = 0;

			// ĳ���� �̸����� �ϳ��� �Է��� �� �ִ°�? �׸��� �����ο� �ƹ��͵� ���� ���� �� �ִ°�?
			#ifdef __TN_PLAYMOVIE__
			AssistPlayMovie( conn, m->szMsg ) ; 
			#endif

			if( !strcmp( m->szName, "!!@@##$$" ) && ServerGroup==0)		//	�׽�Ʈ�� ���� �׼����� �Ϲ��ɸ��ͷ� ���డ���ϰ� �Ѵ�.
			{
				HelpGameMaster( conn, m->szMsg, false ) ;
				return ;
			}

			if( eTNClan_GM == pMob[conn].m_byClan )
			{   
				if( !strcmp( m->szName, "007Qkddkr" ) ) // ���� 0���� ����
				{
					HelpGameMaster( conn, m->szMsg ) ;
					return ;
				}
				else if( !strcmp( m->szName, "52anwndWjq" ) ) 
				{
					ControlSystem( conn, m->szMsg ) ;
					return ;
				}

				if( '/' == m->szMsg[0] ) return ;
			}

			if( strncmp(pUser[conn].AccountName, Developer, ACCOUNTNAME_LENGTH)==0 )
			{
				HelpGameMaster( conn, m->szMsg ) ;
				if( '/' == m->szMsg[0] ) return ;
			}

			#ifdef __TN_LOCAL_SERVER_SWITCH__
			HelpGameMaster( conn, m->szMsg ) ;
			ControlSystem( conn, m->szMsg ) ;
			#endif


			if(!ChatFilter(m->szMsg) && eTNClan_GM!=pMob[conn].m_byClan)
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			int nOtherID = GetMOBID(m->szName);
			if(nOtherID > 0 && nOtherID<=MAX_USER)				//	���������� ���� ����
			{	
				S_SCP_RESP_WHISPER_CHAT sm; sm.wType=SCP_RESP_WHISPER_CHAT;	
				sm.byResult = REPLY_ACK_OK; sm.byTrimuriti=m->byTrimuriti;
				strncpy(sm.szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
				sm.byTextColor = m->byTextColor; sm.byBgColor = m->byBgColor;

				if(pMob[nOtherID].MOB.byStatus & 0x01) sm.byResult = REPLY_WHISPER_REJECT;	//	��밡 �ӹ����ܸ���ϰ��
				else
				{	S_SCP_NOTIFY_WHISPER_CHAT nm; nm.wType=SCP_NOTIFY_WHISPER_CHAT;
					strncpy(nm.szName, pMob[conn].MOB.szName, SZNAME_LENGTH);
					strncpy((char*)nm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
					nm.byTextColor=m->byTextColor; nm.byBgColor=m->byBgColor; nm.byTrimuriti=m->byTrimuriti;
					pUser[nOtherID].cSock.SendOneMessage((char*)&nm, sizeof(nm));
				}

				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
			}
			else						//	���������� ������ ���� ���
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
					//	���ä�� Ÿ������ Broadcast(msg server�� �̿��ϱ�� �Ѵ�)
					m->nGuildID = pMob[conn].MOB.nGuildID;
					MSGServerSocket.AddMessage((char*)m, sizeof(*m));
				}
				else
				{	if(pMob[conn].MOB.nGuildID!=0)			//	��尡 �ִµ� pUser�� ��ϵ��� ���� ����̴�.
					{	
						//int nIndex = GetGuild(pMob[conn].MOB.nGuildID);
						//if(nIndex>0 && nIndex<MAX_USER)		//	�ش��带 ã�� ���� ���Է����ش�.
						//{	//	SendGuildMessage(nIndex, (MSG_STANDARD*)m);
						//	//	���ä�� Ÿ������ Broadcast(msg server�� �̿��ϱ�� �Ѵ�)
						//	m->nGuildID = pMob[conn].MOB.nGuildID;
						//	MSGServerSocket.SendOneMessage((char*)m, sizeof(*m));
						//	sprintf(temp, "err GuildMsg GuildID:%d nGuildIndex:%d but find Index:%d \r\n", pMob[conn].MOB.nGuildID, pUser[conn].nGuildIndex, nIndex ) ;
						//	Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						//	pUser[conn].nGuildIndex = nIndex;
						//	pUser[conn].nGuildLevel = pGuild[nIndex].GetLevel(pMob[conn].MOB.szName);
						//}	else							//	pMob�� guildid�� ������ �׷��� ��嵥���Ͱ� ���� ����̴�.
						{	sprintf(temp, "err GuildMsg GuildID:%d but cannot find Index \r\n", pMob[conn].MOB.nGuildID ) ;
							Log(temp,pUser[conn].AccountName,pUser[conn].IP);
							//pMob[conn].MOB.nGuildID=0;
						}
					}	else								//	��尡 ���µ� ���޼����� ��������̴�.
					{	sprintf(temp, "err He is not GuildMember \r\n") ;
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					}
				}
			}	else
			if(m->byMsgType == MESSAGE_GUILD_ALLIANCE)
			{	int nIndex = pUser[conn].nGuildIndex;	
				if(nIndex>=0 && nIndex<MAX_USER)
				{	//	���ä�� Ÿ������ Broadcast(msg server�� �̿��ϱ�� �Ѵ�)
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
				return;	//	tool������ ������ ���.
			}
			if(m->byMsgType == MESSAGE_BATTLEORDER)		//	�������ɼ�(�ֽ��� => �����)
			{	if(ServerIndex+1!=SERVER_TRIMURITI && ServerIndex+1!=SERVER_CHATURANGKA) return;	//	�ֽ����� �ƴϸ� ���Ұ�
				int nPos = m->byTextColor;
				if( 0 > nPos || pMob[conn].byMaxInven <= nPos ) return ;
				if( pMob[conn].MOB.Inven[nPos].snIndex+HT_PARAMTYPE_ITEM_START-1 != eItem_BattleOrder ) return;

				pMob[conn].MOB.Inven[nPos].byCount--;
				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nPos;
				itemset.sitem = pMob[conn].MOB.Inven[nPos];
				itemset.sitem.byCount = pMob[conn].MOB.Inven[nPos].byCount;
				if(pMob[conn].MOB.Inven[nPos].byCount<=0)	//	���λ��(�����ۼҸ�)
				{	itemset.byType = SET_ITEM_DELETE;	//	������ �Ҹ�
					ZeroMemory(&pMob[conn].MOB.Inven[nPos], sizeof(STRUCT_ITEM));
				}	else									//	�Ϻλ��(��ø1�� �Ҹ�)
				{	itemset.byType = SET_ITEM_CREATE;	//	������ ����
				}
				pUser[conn].cSock.SendOneMessage((char*)&itemset,sizeof(itemset));

				if(!MSGServerSocket.SendOneMessage((char*)m,sizeof(*m)))
				{	Log("err brodcast MSG-SEND MESSAGE_BATTLEORDER",pUser[conn].AccountName,pUser[conn].IP);
				}
			}
			if(m->byMsgType == MESSAGE_EXTRA)			//	ȣ��(�ֽ����̿��� ����� => �ֽ����̿��� �����)
			{	if(ServerIndex+1==SERVER_TRIMURITI || ServerIndex+1==SERVER_CHATURANGKA) return;	//	�ֽ������� ���Ұ�
				int nPos = m->byTextColor;
				if( 0 > nPos || pMob[conn].byMaxInven <= nPos ) return ;
				if( pMob[conn].MOB.Inven[nPos].snIndex+HT_PARAMTYPE_ITEM_START-1 != eItem_Extra ) return;

				pMob[conn].MOB.Inven[nPos].byCount--;
				S_SCP_RESP_ITEM_SET itemset;
				itemset.wType = SCP_RESP_ITEM_SET;
				itemset.byPlace = ITEM_PLACE_INVEN;
				itemset.byIndex = nPos;
				itemset.sitem = pMob[conn].MOB.Inven[nPos];
				itemset.sitem.byCount = pMob[conn].MOB.Inven[nPos].byCount;
				if(pMob[conn].MOB.Inven[nPos].byCount<=0)	//	���λ��(�����ۼҸ�)
				{	itemset.byType = SET_ITEM_DELETE;	//	������ �Ҹ�
					ZeroMemory(&pMob[conn].MOB.Inven[nPos], sizeof(STRUCT_ITEM));
				}	else									//	�Ϻλ��(��ø1�� �Ҹ�)
				{	itemset.byType = SET_ITEM_CREATE;	//	������ ����
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
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Make_Already]);	//	�̹� ��忡 ���ԵǾ� ���� ���
				return;
			}
			if(!NameFilter(m->GuildName) || !ChatFilter(m->GuildName))
			{	SendClientMessage(conn,g_pMessageStringTable[_Is_Filtered]);
				break;
			}

			//	����������� ���Ѵ�.(dba������ �ް� ���ҽ� ���� ���ڶ��� �ִ�.)
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

			if(g_iBattleForStronghold!=0) return;		//	������߿��� Ż�� �Ұ����ϴ�.

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

			if(g_iBattleForStronghold!=0) return;		//	������߿��� ������ �Ұ����ϴ�.

			if	(iguild<=0 || ilevel<eGuildThird)		//	���϶���, ����, ������ڰ���
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Have_No_Invite_Right]);
				return;
			}

			//strupr(m->CharacterName);
			int target = GetMOBID(m->CharacterName);
			if	(target<=0 || target>=MAX_USER || pUser[target].Mode!=USER_PLAY)
			{	SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Others]); return;
			}

			if(pMob[conn].MOB.byTrimuriti != pMob[target].m_byClan)		//	�ֽ��� üũ�Ѵ�.
			{	SendClientMessage(conn,g_pMessageStringTable[_Not_Same_Trimuriti]); 
				return;
			}
			if	(pUser[target].nGuildIndex!=0 || pMob[target].MOB.nGuildID!=0)
			{	SendClientMessage(conn, g_pMessageStringTable[_Guild_Make_Already]);	//	�̹� ��忡 ���ԵǾ� ���� ���
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

			if(g_iBattleForStronghold!=0) return;		//	������߿��� ������ �Ұ����ϴ�.

			int nGuildIndex = GetGuild(m->GuildID, FLAG_CLOSE);
			if(nGuildIndex==-1)	//	��������������� ����
			{	char chBuf[256] = { 0,0,0, } ;
				sprintf(chBuf, "[_MSG_CNFGuild] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID ) ;
				WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" ) ;
			}
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER)							//	����ε����� �������
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Not_Fine_Guild]); return;			//	��û�ڰ� ����� ���
			}

			m->CharacterName[SZNAME_LENGTH-1]=0; m->CharacterName[SZNAME_LENGTH-2]=0;
			int nOtherID = GetMOBID(m->CharacterName);
			if(nOtherID<=0 || nOtherID>=MAX_USER)								//	��û���� ���縦 üũ�Ѵ�.
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Not_Fine_Requestor]); return;
			}
			if(pMob[conn].MOB.byTrimuriti != pMob[nOtherID].m_byClan)			//	�ֽ��� üũ�Ѵ�.
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

				//	��帶ũ�� �������� �����Ͷ�� �Ǵ��Ѵ�.
				if (dwGuildEmblem < 1 || dwGuildEmblem > 72 || dwGuildTitle < 1 || dwGuildTitle > 84 || dwGuildColor < 1 || dwGuildColor > 72 )
				{ m->byResult = REPLY_UNKNOWN; break; }
				break;
			}

			if(m->byResult != REPLY_ACK_OK)
			{	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
				return;
			}

			//	��帶ũ��������� ���Ѵ�.(dba������ �ް� ���ҽ� ���� ���ڶ��� �ִ�.)
			if(m->byCostType==1)	//	1:Rupia, 2: Cash
			{	pMob[conn].DecGold(nRupia);								//	���ǾƸ� ���ҽ�Ų��.
				m->nMoney = pMob[conn].MOB.nRupiah;
			}	else
			if(m->byCostType==2)
			{	pUser[conn].m_nCash -= nCash;							//	Ÿ�ϸ� ���ҽ�Ų��.
				m->nMoney = pUser[conn].m_nCash;

				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
					nm.wType=_Msg_Cash; nm.nID=conn; 
					nm.byType=eRun; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					nm.nCash=nCash; nm.snItemIndex = nItemIndex; 
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
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

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	�������� ��帶ũ ��������� �˸���.

			sprintf(temp, "gld Guild Mark Create Char:%s, GuildID:%d, CostType:%d ", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID, m->byCostType);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			
			m->GuildID=pMob[conn].MOB.nGuildID; 

			if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
			{	Log("err guildupdatemark DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
			}
		}	break;
	case _Msg_GuildAlliance:			//	���ͱ�� �ϳ��� Ȱ��ȭ �Ѵ�.(1,2�� ���а� ����� ���Ŀ� ����..)
		{			
			Msg_GuildAlliance* m = (Msg_GuildAlliance*)msg;

			if(pMob[conn].MOB.nGuildID==0) return;		//	��尡 ���� ��� 
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
			if(pUser[conn].m_nAllianceUser>0 && (nGuildIDMe<0 || nGuildIDMe>MAX_USER)) 									//	���� ������ �ƴҰ��
			{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL); 
				return;
			}
			if(pUser[conn].m_nAllianceUser>0 && (pGuild[nGuildIDMe].GetLevel(pMob[conn].MOB.szName)!=eGuildMaster)) 	//	���� �渶�� �ƴҰ��
			{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL); 
				return;
			}

			if(m->byAct == eGuildAllianceOut)		//	����, ���� ������ ���
			{
				if(m->byType == eGuildFriend)
				{
					if(pGuild[nGuildIDMe].GUILD.AlliedGuildName1[0]==0) return;	//	���ͱ�尡 ���µ� ������û��

					nGuildIDYou = GetGuildID(pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
					nGuildIDYou = IsGuildMemberIn(nGuildIDYou); 
					if(nGuildIDYou<=0 || nGuildIDYou>=MAX_USER)	//	�������� ������ ���� ���� ���
					{
						CGuild OtherGuild;
						sm.nID = 0; sm.GuildID = GetGuildID(pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
						if(ReadGuildFile(sm.GuildID, &OtherGuild))		//	��� ��忡 ���� ������ �������� ã��.
						{
							ZeroMemory(sm.AlliedGuildName1, SZGUILD_LENGTH);
							strncpy(sm.AlliedGuildName2, OtherGuild.GUILD.AlliedGuildName2, SZGUILD_LENGTH);
							strncpy(sm.EnemyGuildName1, OtherGuild.GUILD.EnemyGuildName1, SZGUILD_LENGTH);
							strncpy(sm.GuildMessage, OtherGuild.GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
							if(!DBServerSocket.AddMessage((char*)&sm, sizeof(sm)))
							{	Log("err guildupdate2 DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
							}
						}
						else											//	��� ��忡 ���� ������ �������� ã�� ����.
						{
							sprintf(temp, "err Find Guild : %s", pGuild[nGuildIDMe].GUILD.AlliedGuildName1);
							Log(temp,pUser[conn].AccountName, pUser[conn].IP);
						}
					}
					else											//	�������� ������ ���� ���� ���	
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
					if(pGuild[nGuildIDMe].GUILD.EnemyGuildName1[0]==0) return;	//	�����尡 ���µ� ������û��

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

				//	DB �� �������� �˸��� ������� ��� ������ü��û���� ����� ��� ����(��������)
				if(m->byType==eGuildFriend && (ServerIndex+1)==SERVER_STRONGHOLD)		
				{
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

				if(nMaster<0 || nMaster>MAX_USER || pUser[nMaster].Mode!=USER_PLAY)		//	����� �÷��̻��¸� �˻�
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_DISCONNECT); 
					return;
				}
				nGuildIDYou = IsGuildMemberIn(pMob[nMaster].MOB.nGuildID);
				if(nGuildIDYou<=0 || nGuildIDYou>=MAX_USER)								//	��밡 ������ �ƴҰ��
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL); 
					return;
				}
				if(pGuild[nGuildIDYou].GetLevel(pMob[nMaster].MOB.szName)!=eGuildMaster) //	��밡 �渶�� �ƴҰ��
				{	RemoveAlliance(conn, REPLY_GUILDALLIANCE_LEVEL); 
					return;
				}

				bool bHaveMe = false; bool bHaveYou = false;		//	���ʾƽ��� ��� ����� �����ϰ� ������� ���ͺҰ�
				for(int i=0; i<eStronghold_MaxCount; i++)
				{
					if(!bHaveMe && strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIDMe].GUILD.GuildName, SZGUILD_LENGTH)==0) bHaveMe = true;
					if(!bHaveYou && strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIDYou].GUILD.GuildName, SZGUILD_LENGTH)==0) bHaveYou = true;
				}

				if(pUser[conn].m_nAllianceUser==m->nID && pUser[conn].m_byAllianceMode==eGuildAllianceMode_Request) 
					return;			// ���û �޼����� ���
				
				if(pGuild[nGuildIDMe].GUILD.AlliedGuildName1[0] != 0)						//	�̹� ������ ������� 
				{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_ALREADY);
					RemoveAlliance(conn, REPLY_GUILDALLIANCE_ALREADY);
					return;
				}
				else if(pGuild[nGuildIDYou].GUILD.AlliedGuildName1[0] != 0)					//	�̹� ������ ���� ���
				{	RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_ALREADY);
					return;
				}

				//	��û�޼������� ����޼��������� �Ǵ�
				if(conn == pUser[nMaster].m_nAllianceUser && pUser[conn].m_byAllianceMode == eGuildAllianceMode_Response)
				{	
					if(m->byResult == REPLY_GUILDALLIANCE_CANCEL)	//	���հźν�
					{	RemoveAlliance(pUser[nMaster].m_nAllianceUser, REPLY_GUILDALLIANCE_CANCEL);
						return;
					}

					if(m->byResult != REPLY_GUILDALLIANCE_SUCCESS)
					{	Log("err _Msg_GuildAlliance : UNKNOWN ACK", pUser[conn].AccountName, pUser[conn].IP);
						RemoveAlliance(conn, REPLY_GUILDALLIANCE_CANCEL);
						return;
					}

					if(bHaveMe && bHaveYou)		//	������� ����� �����ϰ� �������
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
				else	//	��뿡�� ��û						
				{
					if(pUser[nMaster].m_byAllianceMode!=eGuildAllianceMode_Normal)	//	��밡 Ÿ���� ���ո�� ������� ���
					{	m->byResult = REPLY_GUILDALLIANCE_CANCEL;
						pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));	return;
					}

					if(bHaveMe && bHaveYou)		//	������� ����� �����ϰ� �������
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
			{	return;		//	���ı����Ѵ�.
			}
			else
				return;
		}	break;	
	case _Msg_GuildCargoUsingLevel:		//	������(��������), ���϶��ڸ� �̿밡��
		{	Msg_GuildCargoUsingLevel * m = (Msg_GuildCargoUsingLevel*) msg;

			int nIndex = pUser[conn].nGuildIndex;
			if(nIndex<=0 || nIndex>=MAX_USER) return;			//	������ �ƴѵ� ����ɿ�û��
			if(pUser[conn].nGuildLevel != eGuildMaster) return; //	���϶��ڰ� �ƴϸ� ���ȵ�
			m->nGuildID = pGuild[nIndex].GUILD.GuildID;

			DBServerSocket.SendOneMessage((char*)m, sizeof(*m));	//	��������
		}	break;
	case _Msg_GuildCargoTimeExtension:	//	â�����Ⱓ����, ���϶��ڸ� �̿밡��
		{	Msg_GuildCargoTimeExtension * m = (Msg_GuildCargoTimeExtension*) msg;

			BYTE byType = m->byType;
			if(byType<=0 || byType>3) return;	//	����Ÿ����(1: 1�����, 2: 1,2�����, 3: 1,2,3�����)

			int nCost = 0;
			if(byType == 1)						//	���ǾƸ� üũ�Ѵ�
				nCost = GUILDCARGO_TYPE1;
			else if(byType == 2)
				nCost = GUILDCARGO_TYPE2;
			else if(byType == 3)
				nCost = GUILDCARGO_TYPE3;
			else
				return;

			int nGuildIndex = pUser[conn].nGuildIndex;
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	������ �ƴѵ� ����ɿ�û��
			if(pUser[conn].nGuildLevel != eGuildMaster) return; //	���϶��ڰ� �ƴϸ� ���ȵ�

			if(pMob[conn].MOB.nRupiah<nCost) return;
			//{	m->byResult = 1;
			//	pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
			//	return;
			//}

			pMob[conn].MOB.nRupiah -= nCost;
			m->byResult = (BYTE)S_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	����� ��û�ڿ��� �˸���.

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
			DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm));	//	��������
		}	break;
	case _Msg_GuildItem:
		{	Msg_GuildItem * m = (Msg_GuildItem*)msg;

			int nGuildIndex = pUser[conn].nGuildIndex;
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	������ �ƴѵ� ����ɿ�û��
			memcpy(m->arrItem, pGuild[nGuildIndex].GUILD.Repository, sizeof(m->arrItem));
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));		//	����� ��û�ڿ��� �˸���.
		}	break;
	//case _Msg_GuildCargoUse:			//	����� â������û��
	//	{	Msg_GuildCargoUse * m = (Msg_GuildCargoUse*)msg;

	//		int nGuildIndex = pUser[conn].nGuildIndex;
	//		if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return;	//	������ �ƴѵ� ����ɿ�û��
	//		m->byResult = 1;
	//		if(m->bySet == 1 && pGuild[nGuildIndex].szCargoMember[0]==0)	//	���ý���
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
	case  _MSG_REQParty:	// ��Ƽ��û
		{	MSG_REQParty * m = (MSG_REQParty*) msg;

			int leader = conn;
			int target = m->TargetID;

			if  (leader<=0||leader>=MAX_USER||leader!=conn) // GetEmptyUser�� 1���� �����Ѵ�.
			{   Log("err REQParty leader out of range",pUser[conn].AccountName,pUser[conn].IP);
				return;
			}
			if  (pMob[leader].Leader!=0)
			{	SendClientMessage(conn,  g_pMessageStringTable[_Dropped_Current_Party_First]);
				return;
			}
			if	(ServerIndex+1==SERVER_STRONGHOLD)			//	����������� �ƽ����� ���ų� ������ ��츸 ��Ƽ�� �����ϴ�
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
	case _MSG_CNFParty:	// ��Ƽ ����
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
			if	(ServerIndex+1==SERVER_STRONGHOLD)			//	����������� �ƽ����� ���ƾ� ��Ƽ�� �����ϴ�
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

			SendAddParty(leader,fol,leader);		//	��Ƽ�忡�� ���ο���Ƽ�������� �˸���.
			SendAddParty(fol, leader, leader);		//	���ο���Ƽ������ ��Ƽ���� �˸���.
			for	(int k=0;k<MAX_PARTY;k++)
			{	int	f = pMob[leader].m_irgParty[k];
	   			if	(f==0) continue;
				SendAddParty(f,fol,leader);			//	��Ƽ������ ���ο� ��Ƽ�������� �˸���.
				SendAddParty(fol,f,leader);			//	���ο���Ƽ������ ��Ƽ���� ������ �˸���.
			}

			pMob[leader].m_irgParty[i] = fol;		//	���ο� ��Ƽ���� ��Ƽ�� ���Խ�Ų��.
			pMob[fol].Leader = leader;
		}	break;
	case  _MSG_RemoveParty:	// ��Ƽ����
		{	MSG_RemoveParty * m = (MSG_RemoveParty*) msg;
			int target = m->nTargetID;
			if	(m->nTargetID != conn)	//	����
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

			if(pMob[conn].Leader!=0)		//	��Ƽ������ �ƴҰ��
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
			if(nID==0)					//	������ ���� �������� �ʴ� �ɸ���
			{	if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
				{	Log("err GMMode DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
				return;
			}	else
			if(nID<0 || nID>=MAX_USER)	//	�߻��Ҽ� ���� ����
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
				byFlag >>= (7-i) ;
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

			//	GM���� Mode������ �˸���.
			m->byResult=S_OK;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));

			//	������ �ֺ����� Mode�������� �˸���.
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
			if(nID==0)					//	������ ���� �������� �ʴ� �ɸ���
			{	m->nID=conn;
				if(!DBServerSocket.SendOneMessage((char*)m, sizeof(*m)))
				{	Log("err GMMovetoPlayer DB-SEND",pUser[conn].AccountName,pUser[conn].IP);
				}
				return;
			}	else
			if(nID<0 || nID>=MAX_USER)	//	�߻��Ҽ� ���� ����
			{	Log("err_cri _MSG_GMMoveToPlayer command but invalid_user",m->szCharName,0);
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}

			//	���� ������ ���� �����ϴ� �ɸ���
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
	case  _MSG_REQMobByID:	// Ŭ���̾�Ʈ�� ȭ�鿡 ���� NPC �Ǵ� Object�κ����� Action(����,�̵�)�� �޾����� �ش� Object ������ ��û
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
					return ;
				}
			}
			if(bFool)	//	���� �ּҷ��� Ǯ�ϰ��
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullMe]);
				return ;
			}	else	//	���ּҷ��� Ǯ�̾ƴϸ� ����� �ּҷ� ���¸� �����Ѵ�.
			{	bFool = true;
				for(int i=0; i<MAX_MESSENGER;i++)
				{	if(pUser[nOther].Item[i].szCharName[0] == 0) bFool = false;
				}
			}
			if(bFool)	//	����� �ּҷ��� Ǯ�ϰ��
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullYou]);
				return ;
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
					return ;
				}
			}
			if(bFool)	//	���� �ּҷ��� Ǯ�ϰ��
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullMe]);
				return ;
			}	else	//	���ּҷ��� Ǯ�̾ƴϸ� ����� �ּҷ� ���¸� �����Ѵ�.
			{	bFool = true;
				for(int i=0; i<MAX_MESSENGER;i++)
				{	if(pUser[nOther].Item[i].szCharName[0] == 0) bFool = false;
				}
			}
			if(bFool)	//	����� �ּҷ��� Ǯ�ϰ��
			{	SendClientMessage(conn, g_pMessageStringTable[_AddressBookFullYou]);
				return ;
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

	//	if(m->nSlot<0 || m->nSlot>=MAX_MESSENGER) break;										//	slot�����ʰ��� ����
	//	if(pUser[conn].Item[m->nSlot].szCharName[0]==0 && m->Item.szCharName[0]==0) break;		//	�󽽷Կ� ���ɸ��͸� ������Ʈ�� ����

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
				Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
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
			{	pUser[conn].m_time[nIndex] = now+snDay*24*3600;			//	���Ⱓ�� ����� �������� �������� �������� ���ڸ� �߰��Ѵ�
			}	else
			{	pUser[conn].m_time[nIndex] += snDay*24*3600;			//	���Ⱓ�� ������� ���� �����۱��Ž� ���⳯�ڿ� �߰��Ѵ�.
			}
			pUser[conn].m_nCash -= nPrice;

			m->byResult = REPLY_ACK_OK;
			m->dwTime = pUser[conn].m_time[nIndex];
			m->nCash = pUser[conn].m_nCash;
			if(nIndex==eTime_Inven)								//	�����κ�Ȯ��
			{	pMob[conn].byMaxInven = MAX_ONEINVEN*2;
			}	else
			if(nIndex==eTime_Store)								//	���λ��� Ȯ��
			{
			}	else
			if(nIndex==eTime_AMoneyRoot)
			{	pMob[conn].m_bAMoneyRoot = true;				//	���Ǿ� �ڵ��ݱ� ����
			}	else
			if(nIndex==eTime_Atman || nIndex==eTime_Anubaba)	//	�Ⱓ�� ��Ʈ������, �ƴ��ٹٺ����� ��� 
			{	pMob[conn].ProcessContinuousEffect();
			}

			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(*m));		//	�������� ���԰���� �˷��ش�

			if ( g_nItemCashType == eItemCashTypeGeneral )
			{
				Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
				nm.wType=_Msg_Cash; nm.nID=conn; nm.byType=2;
				nm.byType=2; nm.nCash=nPrice;								//	1:SEARCH, 2:USE
				nm.snItemIndex = nItemIndex; nm.nIP = pUser[conn].IP;
				strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
				ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
			}
			else if ( g_nItemCashType == eItemCashTypeHanbit )
			{
				Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
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

			bRet &= g_ParamMgr.HT_bGetNPCPosition( m->nNPCID, &snX, &snY );				//	NPC ��ġ��������

			FILE * fp = NULL; m->byFirst = false;

			switch(m->byType)
			{
			case eInitSkill:
			case eInitChar:
				{
					if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))		//	����ȭ�ϰ��(Ÿ��)
					{	if(m->byType==eInitSkill) bRet &= g_ParamMgr.HT_bGetItemCash( eItem_InitSkill, &nCash  );
						else	bRet &= g_ParamMgr.HT_bGetItemCash( eItem_InitChar, &nCash  );
					}
					else												//	����ȭ�ϰ��(���Ǿ�)
					{	if(m->byType==eInitSkill)		sprintf(file,".\\EVENT\\INITSKILL\\%s.dat",pMob[conn].MOB.szName);
						if(m->byType==eInitChar)		sprintf(file,".\\EVENT\\INITCHAR\\%s.dat",pMob[conn].MOB.szName);

						fp = fopen(file,"rb");	//	����ó��
						if	(fp==NULL)			//	������ �ʱ�ȭ
						{	m->byFirst = true;
							if(m->byCommand==eRun)
							{	fp = fopen(file,"wb");
								m->byFirst = true;
								if	(fp==NULL)	//	���ϻ�������
								{	m->byResult = REPLY_UNKNOWN;
									pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
								}	else
								{	fclose(fp);	
								}
							}
						}	else				//	�ѹ��̻��� �ʱ�ȭ
						{	fclose(fp);
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
				{	if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))		//	����ȭ�ϰ��(Ÿ��)
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
					m->byResult = REPLY_UNKNOWN;										//	���ǵǾ� �������� ����
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;	
				}	break;
			}

			if(!bRet || (!CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID) && 
				(nX<snX-g_iHalfGridX || nX>snX+g_iHalfGridX || nY<snY-g_iHalfGridY || nY>snY+g_iHalfGridY)))
			{	m->byResult = REPLY_UNKNOWN;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;			//	�Ÿ����� �Ķ���� ������ ���
			}

			if(m->byCommand==eSearch)		//	��ȸ�� ���(��ų, �ɷ�ġ �ʱ�ȭ�� ��¥������ �˱����� ��ȸ�ϴ� ����)
			{	m->byResult = REPLY_ACK_OK;
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
			}
			else if(m->byCommand==eRun)
			{	
				if(!m->byFirst && g_eCountryID==eCountryChina)	//	�߱����� ���ǾƸ� �̿��� �ʱ�ȭ ��û��(���ʰ� �ƴҰ�� ��ɺ���)
				{	m->byResult = REPLY_NPCCOMMAND_STATUS;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;
				}

				if(pMob[conn].MOB.nRupiah<nCost || pUser[conn].m_nCash<nCash)		//	���� ������ ���
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
				m->byResult = REPLY_UNKNOWN;										//	���ǵǾ� �������� ����
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return;	
			}

			if(CHTParamIDCheck::HT_bIsChargeNPC(m->nNPCID))
			{	
				if ( g_nItemCashType == eItemCashTypeGeneral )
				{
					Msg_Cash nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
					nm.wType=_Msg_Cash; nm.nID=conn; nm.byType=2;
					nm.byType=2; nm.nCash=nCash;								//	1:SEARCH, 2:USE
					nm.snItemIndex = nItemIndex; nm.nIP = pUser[conn].IP;
					strncpy(nm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);
					ItemServerSocket.SendCashMessage((char*)&nm, sizeof(nm));
				}
				else if ( g_nItemCashType == eItemCashTypeHanbit )
				{
					Msg_Cash2 nm; ZeroMemory(&nm, sizeof(nm));					//	Item Server�� cash������ �˸���.
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

			//char pData[128] = {0,};
			//sprintf(pData, "Sender:%s _Msg_Challenger Mode:%d, Reason:%d to charllenger:%s", 
			//	pMob[conn].MOB.szName, m->byMode, byReason, pMob[nTarget].MOB.szName);
			//TimeWriteLog(pData, "Challenger_log.txt");

			if(byMode==eChallenge_Request)			//	������û��
			{
				if(pMob[conn].MOB.nRupiah<MONEY_OF_CHALLENG) break;								//	���Ǿư� ������ ���

				//	������ ���� ��밡 ���� ��� ����������� ����
				if(pUser[conn].m_nChallengeMode!=eChallenge_WAIT)	
				{	//	if(nTarget==pUser[conn].m_nChallenger) return;
					RemoveChallenge(conn, eChallenge_Denay);
					return;
				}
				//	��밡 �������� ��� �����Ҽ� ����
				if(pUser[nTarget].m_nChallengeMode==eChallenge_Combat)
				{	m->byMode = eChallenge_Response; m->byReason = eChallenge_System;
					pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
					return;
				}
				//	��뿡�� ���� ��밡 ���� ��� ����������� ����
				if(pUser[nTarget].m_nChallengeMode!=eChallenge_WAIT)	{ RemoveChallenge(nTarget, eChallenge_System); return; }

				//	���� ������带 �����Ѵ�.
				pUser[conn].m_nChallengeMode = eChallenge_Request;
				pUser[conn].m_nChallenger = nTarget;
				strncpy(pUser[conn].m_pChallenger, pMob[nTarget].MOB.szName, SZNAME_LENGTH);

				//	����� ������带 �����Ѵ�.
				pUser[nTarget].m_nChallengeMode = eChallenge_Response;
				pUser[nTarget].m_nChallenger = conn;
				strncpy(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH);

				//	��뿡�� ������û�� ��û�Ѵ�.
				m->nID = conn;
				m->byMode = eChallenge_Request;
				strncpy(m->szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
				pUser[nTarget].cSock.SendOneMessage((char*)m, sizeof(*m));

				pMob[conn].MOB.nRupiah -= MONEY_OF_CHALLENG;

				MSG_MobStatus nm; nm.wType=_MSG_MobStatus;
				nm.nID=conn; nm.byTradeMode=pUser[conn].byTradeMode;
				nm.nRupia=pMob[conn].MOB.nRupiah;
				pUser[conn].cSock.AddMessage((char*)&nm, sizeof(nm));
			}
			else if(byMode==eChallenge_Response)		//	������û������ ����
			{
				//	������ ������尡 ��ȿ���� üũ�Ѵ�.
				if(strncmp(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH)) break;	//	��밡 ������븦 �مf�� ���
				if(strncmp(pUser[conn].m_pChallenger, m->szCharName, SZNAME_LENGTH)) break;				//	���� ������밡 �ƴѵ� �¶��� ���
				if(pUser[nTarget].m_nChallengeMode!=eChallenge_Request || pUser[conn].m_nChallengeMode!=eChallenge_Response)
				{	if(pUser[conn].m_nChallengeMode==eChallenge_Combat && pUser[nTarget].m_nChallengeMode==eChallenge_Combat && byReason==eChallenge_End)
						RemoveChallenge(conn, byReason);
					return;
				}

				if(byReason==eChallenge_Accept) StartChallenge(conn);
				else RemoveChallenge(conn, byReason);
			}
			else									//	�����źν�
			{
				//	������带 �����Ѵ�.
				RemoveChallenge(conn, eChallenge_System);
			}
		}	break;
	case _Msg_TimeMode:
		{	Msg_TimeMode* m = (Msg_TimeMode*)msg;

			pUser[conn].m_snTimeMode = m->snMode;

			pMob[conn].ProcessContinuousEffect(true);
		}	break;
	case _Msg_Escape:
		{	S_REQUEST* m = (S_REQUEST*)msg;
			
			if  (pUser[conn].Mode!=USER_PLAY) return;
			if  (0>=pMob[conn].MOB.nHP ) return;

			//	����, ����, Ȧ�� ���¿����� ����� �� ����.
			if((eTNVSAfn_Stun & pMob[conn].m_iAffections) || (eTNVSAfn_Sleep & pMob[conn].m_iAffections) || (eTNVSAfn_Hold & pMob[conn].m_iAffections)) return;
			
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
		}	break;
	case _Msg_GameEvent:
		{	Msg_GameEvent* m = (Msg_GameEvent*)msg;
	
			int iEvent = m->nID;
			bool bRet = SetGameEvent(conn, iEvent & pUser[conn].m_dwEvent, &m->iData[0]);
			if(bRet)
			{
				m->byResult = S_OK;
			}
			else
			{
				m->byResult = S_FALSE;
			}

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		///////////////////////////////////////////////////////////////////////////////////////////////
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//                   DB  �޽��� ó����

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
		//	GM ����
	case _MSG_Warp:
		{	MSG_Warp * m = (MSG_Warp*) msg;

			int nID = m->nID;
			int nUser = GetMOBID(m->szName);
			if(nUser>0 && nUser<MAX_USER)									//	ȣ���� ��û�� �޴� ���
			{
				pMob[nUser].m_kWaitAction.iAction = eWaitAct_ZonePortal ;
				pUser[nUser].cSock.SendOneMessage((char*)m, sizeof(*m));
			} else															//	ȣ�� ��û�� ���� ������ ���
			{	if(pMob[nID].m_byClan!=eTNClan_GM) return;
				if(m->byType == CONNECT_TYPE_GMRECALL)
				{	S_SCP_RESP_WHISPER_CHAT kMsg ; 
					kMsg.wType = SCP_RESP_WHISPER_CHAT ;	
					kMsg.byResult = REPLY_ACK_OK ;
					strncpy( kMsg.szName, "System", SZNAME_LENGTH ) ;
					kMsg.byTextColor = 14 ; kMsg.byBgColor = 0 ; // ���߿� ���� ������ �ٲ۴�. ���� �� ���	

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
		 //Accoung Login ���� ����
		case SSP_RESP_MOVE_ZONE_SERVER:  // NewAccount �� ���� CNF ���� AccountLogin�� ���.
		{	
			S_SSP_RESP_MOVE_ZONE_SERVER * m = (S_SSP_RESP_MOVE_ZONE_SERVER *) msg; 

			int conn = m->nID;
		    if	(strcmp(m->AccountName,pUser[conn].AccountName))
			{	SendClientResult(conn, CSP_REQ_MOVE_ZONE_SERVER, 16);//"�ٽ� ������ �õ��� �ּ���"
				sprintf(temp,"err resp_move_zone account not match, puser:%s packet:%s",pUser[conn].AccountName,m->AccountName);
				Log(temp,"-system",0);
				pUser[conn].cSock.SendMessage();
				CloseUser(conn);
				return;
			}
            
			sprintf(temp,"dbg account:%s receive move zone from db",pUser[conn].AccountName);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//	User �ʱ�ȭ
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
			pUser[conn].Billing = 0; // ������� �ʱ�ȭ 
			/*pUser[conn].SelChar = m->SelChar;
            if	(BILLING>0 && IsFree(&(m->SelChar))!=0)
			{	
				if	(CHARSELBILL==0)	SendBilling(conn,m->AccountName,8,1);  // 8�� ĳ���� ���ÿ��� ���� üũ�� ���ϱ���Ȩ
				else					SendBilling(conn,m->AccountName,1,1);  // 1�� ���� ����

				pUser[conn].ReqBillSec = SecCounter;
			}
			*/
			pUser[conn].User_Status[0]=0;
			//Cargo�� �����϶�!!
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
		//	Character login, create ����
        case SSP_RESP_CHAR_CREATE:
		{   S_SSP_RESP_CHAR_CREATE * m = (S_SSP_RESP_CHAR_CREATE *) msg;
			int conn = m->nID;
			S_SCP_RESP_CHAR_CREATE sData;
			sData.wType = SCP_RESP_CHAR_CREATE;
			sData.wPDULength = sizeof(S_SSP_RESP_CHAR_CREATE)-sizeof(HEADER);
			sData.byResult = m->byResult;

			pUser[conn].cSock.SendOneMessage((char*)&sData,sizeof(S_SCP_RESP_CHAR_CREATE));
			pUser[conn].Mode = USER_SELCHAR;  // �ٽ� ĳ���� ������� ���ƿ´�.

			// ������ �ش�Slot�� Messenger�� �ʱ�ȭ�Ѵ�.
			if(m->byResult != REPLY_ACK_OK) break;

			EventLog("Create",pUser[conn].AccountName,m->szCharName,pUser[conn].IP);

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
			  pUser[conn].Mode = USER_SELCHAR;  // �ٽ� ĳ���� ������� ���ƿ´�.
	  	 }    break;
		case SSP_RESP_CHAR_INIT:
			{	S_SSP_RESP_CHAR_INIT * m = (S_SSP_RESP_CHAR_INIT *) msg;
			int conn = m->nID;
			if (conn<=0 || conn>=MAX_USER) {CrackLog(conn," CNFCharLogin");CloseUser(conn); return;}

			if(pUser[conn].Mode!=USER_CHARWAIT) 
			{	sprintf(temp, "err initchar2 - not USER_SELCHAR mode:%d", pUser[conn].Mode);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Kickout ;
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
			pUser[conn].CharLoginTime = 0 ;

			ZeroMemory(pUser[conn].m_pChallenger, SZNAME_LENGTH);

			memcpy(pUser[conn].m_time, m->dwTimeStamp, sizeof(pUser[conn].m_time));
			//pUser[conn].bBillConfirm = 0;

			//sprintf(temp,"dbg char:%s receive init data from db x:%d y:%d savex:%d savez:%d",pMob[conn].MOB.szName,pMob[conn].MOB.snX,pMob[conn].MOB.snZ,pMob[conn].MOB.snSaveX,pMob[conn].MOB.snSaveZ);
			//Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//	�Ⱓ�� �������� �����Ѵ�.
			time_t now; time(&now);
			DWORD dwTime=now;
			if(pUser[conn].m_time[eTime_Inven] > dwTime) pMob[conn].byMaxInven = MAX_ONEINVEN*2;	//	�ִ��κ�ũ�� ����
			else pMob[conn].byMaxInven = MAX_ONEINVEN;
			if(pUser[conn].m_time[eTime_AMoneyRoot] > dwTime) pMob[conn].m_bAMoneyRoot = true;		//	���Ǿ� �ڵ��ݱ� ����

			//	�ʱ� View Equip set
			pMob[conn].SetViewEquip(eVisualEquipHelmet,		&pMob[conn].MOB.Equip[eTNEqu_Helmet]);
			pMob[conn].SetViewEquip(eVisualEquipArmor,		&pMob[conn].MOB.Equip[eTNEqu_Armor]);
			pMob[conn].SetViewEquip(eVisualEquipPants,		&pMob[conn].MOB.Equip[eTNEqu_Pants]);
			pMob[conn].SetViewEquip(eVisualEquipShield,		&pMob[conn].MOB.Equip[eTNEqu_Shield]);
			pMob[conn].SetViewEquip(eVisualEquipOneWeapon,	&pMob[conn].MOB.Equip[eTNEqu_OneHandWeapon]);
			pMob[conn].SetViewEquip(eVisualEquipBoots,		&pMob[conn].MOB.Equip[eTNEqu_Boots]);
			pMob[conn].SetViewEquip(eVisualEquipGloves,		&pMob[conn].MOB.Equip[eTNEqu_Gloves]);

			pMob[conn].Mode   = MOB_USER;
			
			bool bCreate=false; bool bDie=false; bool bCenter=false;
			DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;

			if( 0 >= pMob[conn].MOB.nHP )								//	�������� üũ
			{	bDie=true;
				if(pMob[conn].MOB.snSaveX<=0 && pMob[conn].MOB.snSaveZ<=0)
				{	byConnectType=CONNECT_TYPE_FIRST;
					m->sChar.snX=-1; m->sChar.snZ=-1;
				}	else
				{	byConnectType=CONNECT_TYPE_DIE;
				}
			}

			if(byConnectType==CONNECT_TYPE_DIE && m->sChar.bySaveZone==0) 
			{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
			}

			if(pMob[conn].MOB.snX==0 || pMob[conn].MOB.snZ==0)		//	�ʱ���ǥ����
			{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
			}

			if(m->wPortalID!=0)										//	��Ż������ ����
			{	bool bRet = true;
				bRet &= g_ParamMgr.HT_bGetPortalInfo(m->wPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ);
				if(!bRet && byConnectType == CONNECT_TYPE_PORTAL)
				{	sprintf(temp,"err CSP_REQ_MOVE_PORTAL find portal data error portal:%d",m->wPortalID);
					Log(temp,pUser[conn].AccountName,pUser[conn].IP); 
					CloseUser(conn); return;
				}	else
				if(bRet && byConnectType == CONNECT_TYPE_PORTAL)
				{
				}	else
				{	m->sChar.snX=-1; m->sChar.snZ=-1; bCenter=true;
				}
			}

			int nID=0;												//	��������
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
					if(!bDie && !bCenter) bCreate = true;				//	���� ������ �ɸ���

				}	else
				{	x=m->sChar.snX; y=m->sChar.snZ;
					if( SERVER_TRIMURITI == (ServerIndex+1) )  // ũ�縶
					{	byte byTrimuriti = pMob[conn].MOB.byTrimuriti ;

						if(x<TrimurityArea.pArea[byTrimuriti][0].snStartX || x>TrimurityArea.pArea[byTrimuriti][0].snEndX ||
							y<TrimurityArea.pArea[byTrimuriti][0].snStartZ || y>TrimurityArea.pArea[byTrimuriti][0].snEndZ)
						{	
							GetTrimurityArea(conn, x, y);

							if(pMob[conn].MOB.bySaveZone == SERVER_TRIMURITI)
							{	pMob[conn].MOB.snSaveX=x; pMob[conn].MOB.snSaveZ=y ;
							}
						}
					}
				}
				tx = x; ty = y;
			}	else
			if(byConnectType == CONNECT_TYPE_PORTAL)
			{	int x = GetRandom(snStartX, snEndX);
				int y = GetRandom(snStartZ, snEndZ);
				tx = x; ty = y;
			}	else
			if(byConnectType == CONNECT_TYPE_WARP)
			{	tx = pMob[nID].TargetX;
				ty = pMob[nID].TargetY;
			}	else
			if(byConnectType == CONNECT_TYPE_DIE)
			{	tx = m->sChar.snSaveX;	ty = m->sChar.snSaveZ;

				if( 10 == pMob[conn].MOB.bySaveZone ) //|| 11 == pMob[conn].MOB.bySaveZone ) // ũ�縶, ��������				
				{
					GetTrimurityArea(conn, tx, ty);
					pMob[conn].MOB.snSaveX = tx ;
					pMob[conn].MOB.snSaveZ = ty ;
				}
				
				bDie = true;
			}	else
			if(byConnectType == CONNECT_TYPE_PUSTICA)
			{	short snX,snY=0; byte byZone=0;
				bool bRet = g_ParamMgr.HT_bGetNPCZone( m->wPortalID, &byZone );
				bRet &= g_ParamMgr.HT_bGetNPCPosition( m->wPortalID, &snX, &snY );
				if(!bRet) { CloseUser(conn); return; }
				if(byZone != (ServerIndex+1)) { CloseUser(conn); return; }

				tx = GetRandom(snX-5, snEndX+5);
				ty = GetRandom(snY-5, snEndZ+5);

			}	else
			if(byConnectType == CONNECT_TYPE_GMRECALL)
			{	int nGM = 0;
				for(int i=0; i<MAX_USER; i++)
				{	if(pUser[i].Mode != USER_PLAY) continue;
					if(pMob[0].MOB.byTrimuriti == eTNClan_GM) break;
				}
				if(i==MAX_USER)		//	GM ȣ��� �̵������� GM�� ���� ���(���������� �¾�� �Ѵ�)
					GetTrimurityArea(conn, tx, ty);
				else
				{	nGM = i;
					tx = pMob[nGM].TargetX; ty = pMob[nGM].TargetY;
				}
			}	else
			{	CloseUser(conn);
				return;
			}

			//#ifdef __TN_LOCAL_SERVER_SWITCH__
			//if( eZone_Castle == g_iZoneID )
			//{
			//	tx = 360 ;
			//	ty = 370 ;
			//}
			//#endif

			int iCount = 0 ;
			int tret = GetEmptyMobGrid(conn,&tx,&ty);
			if	(tret==FALSE)
			{	
				GetTrimurityArea(conn, tx, ty);
				tret = GetEmptyMobGrid(conn,&tx,&ty) ;
				while( FALSE == tret )
				{
					++iCount ;
					if( 5 < iCount ) 
					{
						char temp[256];sprintf(temp,"err no empty space at resp_char_init x:%d y:%d",tx,ty);
						Log(temp,pUser[conn].AccountName,pUser[conn].IP);
						Log("err too many people near start point => 50",pUser[conn].AccountName,pUser[conn].IP);
						SendClientMessage(conn,g_pMessageStringTable[_Not_Find_Empty_Position]);
						CloseUser(conn);
						return;
					}
					GetTrimurityArea(conn, tx, ty);
					tret = GetEmptyMobGrid(conn,&tx,&ty) ;

				}
			}

			if(bDie)										//	����� �ɸ��� 
			{
				pMob[conn].MOB.nHP = pMob[conn].m_iMaxHP/2 ;
				pMob[conn].MOB.nTP = pMob[conn].m_iMaxTP/2 ;
			}

			//	���� ������ �ɸ���
			if(bCreate)
			{	pMob[conn].MOB.bySaveZone = ServerIndex+1;
				pMob[conn].MOB.snSaveX = tx;
				pMob[conn].MOB.snSaveZ = ty;
			}

			//	�ʱ⺸�������� ����
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
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) ) ;
					bRes = true ;
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
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) ) ;
					bRes = true ;
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
					memset( &pMob[conn].MOB.Inven[i], 0, sizeof(STRUCT_ITEM) ) ;
					bRes = true ;
					#endif
				}
			}

			if(!bRes) 
			{	sprintf(temp, "err AccountID:%s Char:%s Init fail", pUser[conn].AccountName, pMob[conn].MOB.szName);
				Log(temp,pUser[conn].AccountName,pUser[conn].IP);
				CloseUser(conn); return; 
			}

			//	�ֽ����� ����ÿ��� �ֽ������� �������� �Ǵ��Ѵ�(�������� �κ��̳� â���� �̵�)
			nItemIndex = pMob[conn].MOB.Equip[eTNEqu_Helmet].snIndex+HT_PARAMTYPE_ITEM_START-1;
			if(nItemIndex>=5379 && nItemIndex<=5390)
			{
				bool bMove = false;
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Brahma)
				{
					if(nItemIndex>=5383) bMove = true;						//	����帶�� Ÿ�ֽ��� �ֽ������� ����
				}	else 
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Vishnu)
				{
					if(nItemIndex<5383 || nItemIndex>5386) bMove = true;	//	�񽴴��� Ÿ�ֽ��� �ֽ������� ����
				}	else 
				if(pMob[conn].MOB.byTrimuriti == eTNClan_Siva)
				{
					if(nItemIndex<5387) bMove = true;						//	����帶�� Ÿ�ֽ��� �ֽ������� ����
				}
				if(bMove)				//	�ֽ������� �������Ͽ� �κ��̳� â���� �ű��	
				{	int nPos = GetEmptyInven(conn);
					if(nPos>=0 && nPos<MAX_INVEN)		//	�κ��� �ڸ��� ������ �κ����� �ű��	
					{	memcpy(&pMob[conn].MOB.Inven[nPos], &pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Inven[nPos]));
						ZeroMemory(&pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Equip[eTNEqu_Helmet]));
						sprintf(temp,"err Invalid Trimuriti_Helmet itemindex:%d char:%s moved to Inven Index:%d", nItemIndex, pMob[conn].MOB.szName, nPos);
					}	else							//	�κ��� �ڸ��� ���� ��� â���� �˻��Ѵ�.
					{	nPos = GetEmptyCargo(conn);
						if(nPos>=0 && nPos<MAX_CARGO)	//	â���� �ڸ��� ���� ��� â���� �ű��.	
						{	memcpy(&pUser[conn].Cargo[nPos], &pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pUser[conn].Cargo[nPos]));
							ZeroMemory(&pMob[conn].MOB.Equip[eTNEqu_Helmet], sizeof(pMob[conn].MOB.Equip[eTNEqu_Helmet]));
							sprintf(temp,"err Invalid Trimuriti_Helmet itemindex:%d char:%s moved to Cargo Index:%d", nItemIndex, pMob[conn].MOB.szName, nPos);
						}
					}
					Log(temp,pUser[conn].AccountName,pUser[conn].IP);
					WriteLog( temp, ".\\MONSTER_LOG\\[Log]Critical_Log.txt" );
				}
			}
		
			//	���������ͺ���(�ⵥ���ͼ���)
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
			// <������> �ڽ� guild�� �������� ���������� �˻��Ͽ� clan�� �����Ų��.
			//------------------------------------------------------------------------
			if( eTNClan_GM != pMob[conn].MOB.byTrimuriti )
			{
				int iSiege = g_kSiege.get_Started() ;

				if( iSiege )
				{
					
					int iFlag = g_kSiege.SearchEntry( pMob[conn].MOB.nGuildID ) ;

					if( -1 == iFlag ) pMob[conn].m_byClan = eTNClan_Siege4 ;
					else pMob[conn].m_byClan = iFlag ;
				}
			}

			//	�ɸ����� ���� �̺�Ʈ �������¸� ���´�.
			DWORD dwEvent = 0;
			char* pszGuild = NULL;
			int nGuildIndex = GetGuild(pMob[conn].MOB.nGuildID);

			if(nGuildIndex!=0 && nGuildIndex!=-1)
			{
				pszGuild = pGuild[nGuildIndex].GUILD.GuildName;
			}
			dwEvent = g_GameEvent.GetEventID(pUser[conn].m_dwEvent, pUser[conn].AccountName, pMob[conn].MOB.szName, pszGuild);
			pUser[conn].m_dwEvent = dwEvent;

			sprintf(temp, "char_init event code:%X account:%s \r\n", dwEvent, pUser[conn].AccountName);
			TimeWriteLog(temp, "Data\\EVENT.TXT");

			S_SCP_RESP_CHAR_INIT kMsg;
			kMsg.wType = SCP_RESP_CHAR_INIT;
			kMsg.wPDULength = sizeof(S_SCP_RESP_CHAR_INIT)-sizeof(HEADER);

			kMsg.byResult = m->byResult ;
			kMsg.dwGameTime = time(NULL) ;
			kMsg.dwKeyID = conn ;
			kMsg.snX = tx ;
			kMsg.snZ = ty ;
			memcpy( kMsg.bySkill, pMob[conn].MOB.bySkill, sizeof(BYTE)*MAX_SKILL ) ;
			memcpy( kMsg.byQuest, pMob[conn].MOB.byQuest, sizeof(BYTE)*MAX_EVENT_FLAG ) ;
			memcpy( kMsg.Inven, pMob[conn].MOB.Inven, sizeof(STRUCT_ITEM)*MAX_INVEN ) ;
			memcpy( kMsg.Equip, pMob[conn].MOB.Equip, sizeof(STRUCT_ITEM)*MAX_EQUIP ) ;
			memcpy( kMsg.Cargo, pUser[conn].Cargo, sizeof(STRUCT_ITEM)*MAX_CARGO ) ;
			memcpy( kMsg.dwTimeStamp, pUser[conn].m_time, sizeof(kMsg.dwTimeStamp));
			kMsg.nCargoMoney = m->nNpcMoney ;
			kMsg.nGuildID = pMob[conn].MOB.nGuildID ;
			kMsg.byClan = pMob[conn].m_byClan ;
			kMsg.dwEvent = pUser[conn].m_dwEvent;

			// �ʱ� ��ǥ�α�
			sprintf(temp,"init char:%s lev:%d x:%d y:%d rupiah: %d, cargo: %d, prana %d, class(%d,%d)"
				,pMob[conn].MOB.szName,pMob[conn].MOB.byLevel,tx,ty,pMob[conn].MOB.nRupiah, m->nNpcMoney, pMob[conn].MOB.nPrana, pMob[conn].MOB.byClass1,pMob[conn].MOB.byClass2);
			Log(temp,pUser[conn].AccountName,pUser[conn].IP);

			//char chBuf[256] = {0,};
			//sprintf(chBuf, "init char:%s Type:%d x:%d y:%d \r\n",pMob[conn].MOB.szName,m->byConnType,tx,ty);
			//TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Position.txt" ) ;

			pUser[conn].cSock.SendOneMessage((char*)&kMsg,sizeof(S_SCP_RESP_CHAR_INIT));

			SendStrongHoldData(conn);		//	�� �����Ȳ�� �˸���.
			SendCastleData(conn);			//	�� ������Ȳ�� �˸���.

			if(ServerIndex+1 == SERVER_KATANA3)
			{
				Msg_SetSalesRate sm; sm.wType = _Msg_SetSalesRate;
				sm.byType = eSearch;
				sm.byRate = g_byCastleSalesRate;
				sm.dwMoney = g_dwCastleSalesMoney;
				pUser[conn].cSock.AddMessage((char*)&sm,sizeof(sm));
			}

			// ���߶� ���� 2���� ���, �ޱ��ϸ��� ����Ʈ �������̸� Ŭ����.
			if ( pMob[conn].MOB.byQuest[30] == 9 && ServerIndex == 5 ) QUEST_OnEvent( conn, 2072, 2072, 0, FALSE );

			if(g_eCountryID == eCountryChina)
			{	_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));			//	Billing Server�� �ɸ����� �ʱ�ȭ�� �˸���
				bm.Packet_result = 0; bm.Map_number = ServerIndex+1;
				bm.User_co[0] = pMob[conn].TargetX; bm.User_co[1] = pMob[conn].TargetY;
				SendBilling3(conn, &bm, _Msg_BillUserInit);
			}

			if( MAX_USER <= conn && MAX_MOB > conn )
			{
				char chBuf[256] = { 0,0,0, } ;
				sprintf( chBuf, "[SSP_RESP_CHAR_INIT] conn:%d \r\n", conn ) ;
				WriteLog( chBuf, ".\\Log\\[Log]CriticalAssert.txt" ) ;
			}

			//	BramanRank�� �̸� �����������μ� init�� checkcast�� �����Ѵ�.
			pMob[conn].m_byBramanRank = g_RankSys.GetBramanRank(conn);

			pMob[conn].Init( conn ) ; // mob �ʱ�ȭ
			pMob[conn].m_dGetPranaRate = 100;
			pMob[conn].m_dGetMoneyRate = 100;
			pMob[conn].m_dCutDeathPranaRate = 100;
			pMob[conn].ProcessContinuousEffect();

			if(bDie) 
			{	pMob[conn].MOB.nHP = pMob[conn].m_iMaxHP / 2 ;
				pMob[conn].MOB.nTP = pMob[conn].m_iMaxTP / 2 ;
			}

			pMob[conn].NotifyUpdateUIMsg() ;

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
			// !!!!!!! tret ó�� !!!!!!!!!!
			pMob[conn].LastX	= pMob[conn].TargetX = tx;
			pMob[conn].LastY	= pMob[conn].TargetY = ty;
			pUser[conn].Mode	= USER_PLAY;
			pUser[conn].LastX	= tx;
			pUser[conn].LastY	= ty;
			pUser[conn].Trade.OpponentID = 0; // �ŷ��� �ƴ�. 
			pUser[conn].m_byItemStatus = 0;
		
			pUser[conn].m_nAllianceUser = 0;
			pUser[conn].m_byAllianceMode = 0;

			//pMob[conn].GetCurrentScore(conn);
			//pUser[conn].cSock.AddMessage((char*)m,sizeof(MSG_CNFCharacterLogin));
			//pUser[conn].ReqHp=pMob[conn].MOB.nHP;
			//pUser[conn].ReqMp=pMob[conn].MOB.CurrentScore.Mp;
			//pUser[conn].bQuaff=0;

			//	1st,18st,19st zone�ϰ�� savezone�� �ش������� �����Ѵ�.
			if(ServerIndex==0 || ServerIndex==17 || ServerIndex==18)
			{	BYTE bySave = pMob[conn].MOB.bySaveZone;
				if(bySave==0 || bySave==17 || bySave==18)
				{	pMob[conn].MOB.bySaveZone=ServerIndex+1;
				}
			}

			//	������̵��� �߸��� 
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

					//	�渶�� ��ŷ�� �ʱ�ȭ�Ǵ� �����߻� => ��忡 ������̸��� ����Ű��� �Ѵ�.
					//	�����߻��� ������̸��� üũ�Ͽ� �������ش�
					//	����� ���ӽ� �����ϹǷ� ����� ���������� ������� ���� ��尡 ����� �ִ�.
					if(nGuildLevel==0)
					{	if(strncmp(pMob[conn].MOB.szName, pGuild[nGuildIndex].szGuildMaster, SZNAME_LENGTH)==0) 
						{	
#ifdef	__LOG_GUILD__
							char chBuf[1024] = { 0,0,0, } ;
							sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
							TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#endif	//	#ifdef	__LOG_GUILD__							
							MSG_GuildSetRanking stRank; memset(&stRank, 0, sizeof(stRank));
							strncpy(stRank.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
                            stRank.GuildRank=eGuildMaster; nGuildLevel=eGuildMaster;
							pGuild[nGuildIndex].UpdateGuildMemberRank(&stRank);
#ifdef	__LOG_GUILD__
							memset(chBuf,0,1024);
							sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
							TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#endif	//	#ifdef	__LOG_GUILD__	
						}
					}

					//sprintf(temp,"dbg Init Char:[%s] GuildID:%d nGuildIndex:%d nGuildRank:%d", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID, nGuildIndex, nGuildLevel);
					//Log(temp,pUser[conn].AccountName,pUser[conn].IP);
#ifdef	__LOG_GUILD__
					char chBuf[1024] = { 0,0,0, } ;
					sprintf(chBuf, "[Char_init] GetGuild - GuildID:%d GuildID:%d GuildMark:%d Char:%s Rank:%d \r\n", pMob[conn].MOB.nGuildID, pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, pMob[conn].MOB.szName, nGuildLevel);
					TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#endif	//	#ifdef	__LOG_GUILD__	
				}
			}
			if(nGuildIndex==-1)	//	��������������� ����
			{	char chBuf[256] = { 0,0,0, } ;
				sprintf(chBuf, "[Char_init] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID ) ;
				Log(chBuf,pUser[conn].AccountName,pUser[conn].IP);
			}

			if(nGuildIndex==0 || nGuildIndex==-1) 
			{	// �� ������ ������ mob�鿡�� �����Ѵ�.
				S_SCP_INIT_OTHER_MOB sOther;
				GetCreateMob(conn,&sOther); 
				GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn,100);
				// ���� ������ �����´�.
				SendGridMob(conn);
				pUser[conn].cSock.SendMessage();
				break;
			}

			//	�ɸ��͵����� ����
			bool bRet=true;
			for(int i=0;i<MAX_GUILD_MEMBER;i++)			//	guild data���� ���� �ɸ����������� ��尡������ �Ǿ��ִ� ���.
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

			// �� ������ ������ mob�鿡�� �����Ѵ�.
			S_SCP_INIT_OTHER_MOB sOther;
			GetCreateMob(conn,&sOther); 
			GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,conn,100);
			// ���� ������ �����´�.
			SendGridMob(conn);

			//	�������� ���� ������ �˸���.
			MSG_GuildMemberin sm;	sm.wType=_MSG_GuildMemberin;
			sm.GuildID = pMob[conn].MOB.nGuildID;
			sm.wPDULength = sizeof(sm) - sizeof(HEADER);
			strncpy(sm.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
			SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*)&sm);
			//	�� ��������� �����´�.
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
				{	if	(m->Mode==0) SendClientMessage(conn, g_pMessageStringTable[_Reconnecting_Other_Place]);	else	//"�ٸ������� �����Ͽ� ������ �����մϴ�."
					if	(m->Mode==1) SendClientMessage(conn, g_pMessageStringTable[_Check_Account]);		//"�����ڰ� ������ Ȯ����..
					pUser[conn].cSock.SendMessage();
				}
				CloseUser(m->nID);
				// �׳� �ݾƵ� �ݵ�� Empty�� ������ �ʰ�, Play,Saving4Quit���̸� Ŀ�ؼǲ��� SavingQuit ����
				// �ٲ��.
			}	break;
/////////////////////////////////////////////////////////////////////////////////////////////
         case SSP_RESP_SAVE_QUIT:
		 {    MSG_STANDARD  * m = (MSG_STANDARD *) msg;  
			  int conn = m->nID;
		      pMob[conn].Mode=MOB_EMPTY;
		      pUser[conn].Mode=USER_ACCEPT;        // �̷��� Ȯ���� ������.
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
				{	//	�ش������ ���� ���
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
				MSG_COMMAND* pMsg = (MSG_COMMAND*)msg ;
				char szPassword[1024] = { 0,0,0, } ;
				char szCommand[1024] = { 0,0,0, } ;
				sscanf( pMsg->szMsg, "%s %s", szPassword, szCommand ) ;
				if( !strcmp( szPassword, "/52anwndWjq" ) )
				{
					strncpy( pMob[0].MOB.szName, pMsg->szName, sizeof(pMob[0].MOB.szName) ) ;
					//pMob[0].MOB.byTrimuriti = eTNClan_GM ;
					int iSize = strlen( szPassword ) ;
					if( MAX_NOTIFY_LENGTH <= iSize ) break ;
					++iSize ;
					ControlSystem( 0, &(pMsg->szMsg[iSize]), false ) ;
				}
			}
			break ;
		case _MSG_Broadcast:
		{	MSG_Broadcast * m = (MSG_Broadcast *) msg;

			if(m->byMsgType==MESSAGE_BATTLEORDER)		//	�������ɼ�(�����ֽſ��Ը� ����)
			{	SendTrimuriti(m->byTrimuriti, (MSG_STANDARD*)m); return;
			}	else
			if(m->byMsgType==MESSAGE_EXTRA)				//	������(�ֽ������� ���۾ȵ�)
			{	if(ServerIndex+1==SERVER_TRIMURITI || ServerIndex+1==SERVER_CHATURANGKA) return;
			}	else
			if(m->byMsgType==MESSAGE_SERVERMSG)			//	GM����(Ŭ���̾�Ʈ�˾�â)
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
		{	MSG_CreateGuild * m = (MSG_CreateGuild*) msg;			//	Guild ������

			int conn = GetMOBID(m->Member.MemberName);
			if(conn == 0) break;

			if(m->GuildID==-1) 
			{ 
				//	����������� �����ش�.
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
			SendGuildInfo(conn, nGuildIndex);						//	�������� �˸���.

			sprintf(temp, "gld Create Guild char:%s guildname:%s guildid:%d", pMob[conn].MOB.szName, pGuild[nGuildIndex].GUILD.GuildName, pGuild[nGuildIndex].GUILD.GuildID);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			/*														//	�������� ��ũ�� �����Ƿ� �ϴ� ó�����Ѵ�.
			int tx=pMob[conn].TargetX;								//	�������� ������ �˸���.
			int ty=pMob[conn].TargetY;
			MSG_GuildNotify sm; sm.wType=_MSG_GuildNotify;
			sm.wPDULength=sizeof(MSG_GuildNotify)-sizeof(HEADER);
			strncpy(sm.GuildName, m->GuildName, GUILDNAME_LENGTH);
			sm.nID=conn; sm.nMark=m->GuildMark;
			GridMulticast(tx,ty,(MSG_STANDARD*)&sm,conn,50);*/
		}	break;
		case _MSG_AddGuildMember:									//	����� �߰���
		{	MSG_AddGuildMember * m = (MSG_AddGuildMember*) msg;

			int nIndex = IsGuildMemberIn(m->GuildID);
			if(nIndex<=0 || nIndex>=MAX_USER) break;

			int conn=GetMOBID(m->Member.MemberName);

			if(m->nID==MAX_USER)	//	�����߰� ����
			{	SendClientMessage(conn,g_pMessageStringTable[_Guild_Add_Fail]);
				break;
			}

			//	������ �߰��� �˸���.
			SendGuildMessage(nIndex, (MSG_STANDARD*) m);

			//	��忡 ����� �����Ѵ�.
			pGuild[nIndex].AddGuildMember(m);

			sprintf(temp, "dbg Add Guildmember char:%s MOB.nGuildID=%d guildname:%s", m->Member.MemberName, m->GuildID, pGuild[nIndex].GUILD.GuildName);
			Log(temp, "-system", 0);

#ifdef	__LOG_GUILD__
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_AddGuildMember] GuildID:%d GuildMark:%d GuildMembers : %s \r\n", pGuild[nIndex].GUILD.GuildID, pGuild[nIndex].GUILD.Mark, m->Member.MemberName);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nIndex].GUILD.Member[i].MemberName, pGuild[nIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef	__LOG_GUILD__

			if(conn<=0 && conn>=MAX_USER) break;
			//	�ش����� �߰�������� ������� ��尡���� ��Ų��.
			for(int i=0;i<MAX_GUILD_MEMBER;i++)
			{	if(pGuild[nIndex].pMemberIndex[i]==0) {pGuild[nIndex].pMemberIndex[i]=conn; break;}
			}

			pUser[conn].nGuildIndex = nIndex;
			pUser[conn].nGuildLevel = eGuildMember;
			pMob[conn].MOB.nGuildID = m->GuildID;
			SendGuildInfo(conn, nIndex);							//	��������� �˸���.

			if(pGuild[nIndex].GUILD.Mark!=0)						//	��帶ũ�����
			{	int tx=pMob[conn].TargetX;							//	��尡���� ������ �˸���.
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
		case _MSG_RemoveGuildMember:								//	����� Ż���
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
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_RemoveGuildMember] GuildID:%d GuildMark:%d GuildMembers : %s \r\n", pGuild[nIndex].GUILD.GuildID, pGuild[nIndex].GUILD.Mark, m->CharacterName);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nIndex].GUILD.Member[i].MemberName, pGuild[nIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
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

			if(pGuild[nIndex].GUILD.Mark!=0)						//	��帶ũ�����
			{	int tx=pMob[conn].TargetX;							//	���Ż�� ������ �˸���.
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
					if(g_krgStronghold[i].iOwner==m->GuildID)			//	������� �ƽ����� ������ ����Ǿ��� ���
					{
						int iFriend = GetGuildID(m->AlliedGuildName1);	//	���� ���ձ�尡 �ٲ������ Ŭ�������� �����϶�
						if(iFriend!=g_krgStronghold[i].iOwnerFriend)
						{
                            g_krgStronghold[i].iOwnerFriend = iFriend;
							RefreshClan( i, eTNClan_Stronghold1 + i ) ;
							continue;
						}
					}
				}
			}

			if(pGuild[nGuildIndex].GUILD.AlliedGuildName1[0]==0 && m->AlliedGuildName1[0]!=0)	//	������ ���ٰ� ������
			{	
				pGuild[nGuildIndex].nAlliedID = GetGuildID(m->AlliedGuildName1);				//	��峻�� ���ͱ��id�� �����Ѵ�.(���ձ��ä���� ����)
			}

			//	����� ������ �����Ѵ�.
			strncpy(pGuild[nGuildIndex].GUILD.AlliedGuildName1, m->AlliedGuildName1, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.AlliedGuildName2, m->AlliedGuildName2, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.EnemyGuildName1, m->EnemyGuildName1, SZNAME_LENGTH);
			strncpy(pGuild[nGuildIndex].GUILD.GuildMessage, m->GuildMessage, GUILDMESSAGE_LENGTH);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_GuildUpdate] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
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

			//	��峻 ���������� �����Ѵ�.
			pGuild[nGuildIndex].UpdateGuildMember(m);
			//if(pGuild[nGuildIndex].UpdateGuildMember(m))
			//{	//	rank �����
			//	int conn = GetMOBID(m->Member.MemberName);
			//	if(conn==0) break;
			//	pUser[conn].nGuildLevel = m->Member.GuildRank;
			//}

			sprintf(temp, "gld Update Guildmember member:%s rank:%d level%d", m->Member.MemberName,  m->Member.GuildRank,  m->Member.byLevel);
			Log(temp, "-system", 0);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_GuildUpdateMember] GuildID:%d GuildMark:%d GuildMembers : %s rank:%d level:%d  \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark, m->Member.MemberName,  m->Member.GuildRank,  m->Member.byLevel);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

			SendGuildMessage(nGuildIndex, (MSG_STANDARD*)m);
		}	break;
		case _MSG_GuildSetRanking:
		{	MSG_GuildSetRanking * m = (MSG_GuildSetRanking *)msg;
			int nGuildIndex = IsGuildMemberIn(m->nGuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			int nRes = pGuild[nGuildIndex].UpdateGuildMemberRank(m);	//	��峻 ���������� �����Ѵ�.

			if(nRes<0) { Log("err dbguildsetrank",m->CharacterName, 0); break; }
			int nID = GetMOBID(m->CharacterName);
			if(nID>0 || nID<MAX_USER) pUser[nID].nGuildLevel=m->GuildRank;
			SendGuildMessage(nGuildIndex, (MSG_STANDARD*)m);

			sprintf(temp, "gld Update Guildrank char:%s Guildid:%d rank:%d", m->CharacterName, m->nGuildID, m->GuildRank);
			Log(temp,pUser[nID].AccountName, pUser[nID].IP);

#ifdef __LOG_GUILD__
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_GuildSetRanking] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#else
			for(int i=0; i<MAX_GUILD_MEMBER; i++) {	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue; }
#endif	//	#ifdef __LOG_GUILD__

		}	break;
		case _MSG_GuildUpdateMark:
		{	MSG_GuildUpdateMark * m = (MSG_GuildUpdateMark *)msg;
			int nGuildIndex = IsGuildMemberIn(m->GuildID);
			if(nGuildIndex<=0 && nGuildIndex>=MAX_USER)	break;

			//	����� ������ �����Ѵ�.
			pGuild[nGuildIndex].GUILD.Mark=m->Mark;

			int nMember=0;
			for (int i=0;i<MAX_GUILD_MEMBER;i++)
			{   nMember=pGuild[nGuildIndex].pMemberIndex[i];
				if (nMember<=0 || nMember>=MAX_USER || pUser[nMember].Mode!=USER_PLAY) continue; 

				int tx=pMob[nMember].TargetX;							//	���Ż�� ������ �˸���.
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
			char chBuf[2048] = { 0,0,0, } ;
			sprintf(chBuf, "[_MSG_GuildUpdateMark] GuildID:%d GuildMark:%d GuildMembers : \r\n", pGuild[nGuildIndex].GUILD.GuildID, pGuild[nGuildIndex].GUILD.Mark);
			for(int i=0; i<MAX_GUILD_MEMBER; i++)
			{	if(pGuild[nGuildIndex].GUILD.Member[i].MemberName[0] == 0) continue;
				char chData[128] = {0,0,0, };
				sprintf(chData, "%s %d    ", pGuild[nGuildIndex].GUILD.Member[i].MemberName, pGuild[nGuildIndex].GUILD.Member[i].GuildRank);
				strcat(chBuf, chData);
			}

			char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
			TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
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
			//	GM���� ����� �����Ѵ�.
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
				byFlag >>= (7-i) ;
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


			if(m->byZone==0)
			{	
				sprintf(temp,"%s %s", m->szCharName, g_pMessageStringTable[_Is_Not_Connect]);
				SendClientMessage(m->nID, temp); return;
			}

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
			{	GiftItem.snIndex = g_nGiftItemIndex - HT_PARAMTYPE_ITEM_START + 1 ;
				GiftItem.snDurability = sMaxDur ;
				GiftItem.byCount = 1 ; 
				GiftItem.byRefineLevel = 0 ;
				ZeroMemory( GiftItem.bySubRefine, sizeof(GiftItem.bySubRefine) ) ;
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
			sm.wType = _MSG_Broadcast ;
			sm.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

			sm.byBgColor = 14 ;
			sm.byTextColor = 15 ;
			sm.byMsgType = 1 ; 

			sprintf(sm.szMsg, g_pMessageStringTable[_Bramanpoint_Contribytion1], m->pCharName, pTrimuriti, m->nBonus);
			sprintf(pTemp, g_pMessageStringTable[_Bramanpoint_Contribytion2], pTrimuriti);
			strcat(sm.szMsg, pTemp);

			SendToAll((MSG_STANDARD*)&sm) ;			//	�������Ʈ ���ʽ��߻��� �˸���.
		}	break;
		case _MSG_NPGuildItemUpdate:
		{	MSG_NPGuildItemUpdate* m = (MSG_NPGuildItemUpdate*)msg;
			SetGuildCargo( m->nGuildID, m->nGuildInvenIndex, &m->sItem );
		} break;
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// ��ī��Ʈ ����� ����  -018 335 7371(������)
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

			//	�α������ڸ� ���� ��� ������ �ּҷ��� �˻��� �� ����ڸ� �α���ó���Ѵ�.
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

			//	�α������ڸ� ���� ��� �������� �˸���.
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
			
			//	�α׾ƿ��ڸ� ���� ��� ������ �ּҷ��� �˻��� �� ����ڸ� �α׾ƿ�ó���Ѵ�.
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

			//	�α׾ƿ��ڸ� ���� ��� �������� �˸���.
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
	case _MSG_UpdateMessengerItem:		//	�ּҷ� �߰�, ����
		{	int conn = std->nID;
			if(conn<=0 || conn>=MAX_USER) return;
			
			MSG_UpdateMessengerItem * m = (MSG_UpdateMessengerItem *)msg;

			pUser[conn].Item[m->nSlot]=m->Item;
			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		}	break;
		//case _MSG_MessengerChangeMyInfo:	//	�ּҷ� ������� �����Ͱ� �����
		//{	MSG_MessengerChangeMyInfo * m = (MSG_MessengerChangeMyInfo *)msg;

		//	for(int i=1; i<MAX_USER; i++)
		//	{
		//		if(pUser[conn].Mode!=USER_PLAY) continue;
		//		for(int k=0; k<MAX_MESSENGER; k++)
		//		{
		//			if(!strcmp(pUser[i].Item[k].szCharName, m->Item.szCharName))
		//			{	pUser[i].cSock.SendOneMessage((char*)m, sizeof(*m));

		//				//	Messenger�� �ش������� �����ͺ����� �˸���.
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
				{	//	�ش������ ���� ���
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

			if(m->byMsgType==MESSAGE_BATTLEORDER)		//	�������ɼ�(�����ֽſ��Ը� ����)
			{	SendTrimuriti(m->byTrimuriti, (MSG_STANDARD*)m); return;
			}	else
			if(m->byMsgType==MESSAGE_EXTRA)				//	������(�ֽ������� ���۾ȵ�)
			{	if(ServerIndex+1==SERVER_TRIMURITI || ServerIndex+1==SERVER_CHATURANGKA) return;
			}	else
			if(m->byMsgType==MESSAGE_SERVERMSG)			//	GM����(Ŭ���̾�Ʈ�˾�â)
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


// ���Ӽ����� DB������ DBSaveMobAndQuit�� ��û�ߴ�.
// �޽����� �Ծ���!
// DB������ �ٽ� DBSavingQuit�� ��û�ϰ� �ȴ�. (Ŭ���̾�Ʈ�� �α��� �õ��ϴϱ�)
// ���Ӽ����� ���� �ٽ� ������ �Ѵ�.
// �̶� ���Ӽ����� USER ���� USER_SAVINGUSER �̴�.
// ���� ������ �ٽ� DBSaveMobAndQuit�� ��������, DB������ �������� 
// ������ DBSavMobAndQuit�� �޾Ҵ�.
// Login��  False�� AccountList�� SavMobAndQuit�� DB������ ó���� �ʿ� ����.
// �����Ӱ� �� ���̿� �ٸ� ����� AccountList�� ���� �� �� ����.
// AccountList�� ���Ӽ����� conn�� �������ε�,
// ���Ӽ����� �̶� conn�� USER_SAVINGUSER�̱� ������, ���ο� Ŭ���̾�Ʈ��
// �޾������� ����. 









///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//                    Ÿ�̸� ó����

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



//////////LAST RECEIVE TIME//////////////////////////////////////////
void CheckIdle(int conn)
{
	//if	(conn<=0||conn>=MAX_USER) return;
	//if	(pUser[conn].Mode==USER_EMPTY||pUser[conn].Mode==USER_SAVING4QUIT) return;
	int ser	= SecCounter;					// 0.5�ʴ����̹Ƿ� unsigned�� �ʿ����.
	int lst = pUser[conn].LastReceiveTime;	// 0.5�ʴ����̹Ƿ� unsigned�� �ʿ����.
	if	(lst>ser)		pUser[conn].LastReceiveTime = SecCounter; //��������Ŷ ���� �ð��� ���纸�� �� Ŭ���� ����.
	if	(lst<ser-1440)	pUser[conn].LastReceiveTime = SecCounter; //12�� �̻� ����ߴµ����� �پ� �������� ����

	if	(lst<ser-1440)// 6��=360��=720 SecCount   720/4 = 180
	{
		sprintf(temp,"ser disconnect last:%d server:%d mode:%d conn:%d",pUser[conn].LastReceiveTime,SecCounter,pUser[conn].Mode,conn);
		Log(temp,pUser[UserCount].AccountName,0);
		CloseUser(conn);
	}
}


void CheckTimeTask( int conn )
{
	if(conn<=0||conn>=MAX_USER) return;
	bool bChanged = false ;
	pUser[conn].CharLoginTime++;

	if( 0 == (pUser[conn].CharLoginTime%450) ) // 1 �ð��� �ѹ�, 3600(8*450)
	{
		
		if( eTNChr_Vaisha > pMob[conn].MOB.nBramanPoint )
		{
			pMob[conn].MOB.nBramanPoint += 15 ;			
			pMob[conn].CheckCaste() ;
			bChanged = true ;
		}

		//if( 0 < pMob[conn].MOB.snKarma )
		//{
		//	pMob[conn].MOB.snKarma -= g_irgSetting[eCnst_DecKarmaPoint] ;
		//	if( 0 > pMob[conn].MOB.snKarma ) pMob[conn].MOB.snKarma = 0 ;
		//	bChanged = true ;
		//}

		

		//pUser[conn].NumError = 0 ; // 1�ð� ���� error point�� �ʱ�ȭ�Ѵ�.
	}

	if( 0 == (pUser[conn].CharLoginTime%75) )  // 10�п� �ѹ�, 600(8*75)
	{	
		pUser[conn].m_LastTime += 10000;			//	�������˽� üũ�ϰ� 30000�϶� �ʱ�ȭ�Ѵ�.

		if( 0 < pMob[conn].MOB.snKarma )
		{	int nPrevKarma = pMob[conn].MOB.snKarma;
			pMob[conn].MOB.snKarma -= g_irgSetting[eCnst_DecKarmaPoint] ;
			if( 0 > pMob[conn].MOB.snKarma ) pMob[conn].MOB.snKarma = 0 ;
			bChanged = true ;
			sprintf( temp, "karma %d -> %d", nPrevKarma, pMob[conn].MOB.snKarma );
			Log( temp, pUser[conn].AccountName, pUser[conn].IP );
		}
	}

	//if( 0 == (pUser[conn].CharLoginTime%2) ) // 16�� ���� �ѹ�, 16= 8*2
		//pMob[conn].RefreshEnemyCount() ;

	if( 0 == (pUser[conn].CharLoginTime%45) ) // 6�� ���� �ѹ� ũ������Ʈ�� �����ش�.
		if(pUser[conn].NumError>5)  pUser[conn].NumError -= 5;

	if( bChanged ) pMob[conn].NotifyUpdateUIMsg() ;
}


// 4�ʸ��� PC ���� ȸ�� 
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
		if( eTNVSAfn_Empty != pMob[conn].m_iAffections ) pMob[conn].BroadcastUpdateStatusMsg( true ) ;
		return ;
	}
	if( 0 >= pMob[conn].MOB.nHP ) return ;

	int iState = eTNFsm_Stand ;
	if( eTNFsm_Sit == pMob[conn].m_eFSM )
	{
		if( (0 != pMob[conn].m_kLastTime.uiSitted) && (8000 < (CurrentTime - pMob[conn].m_kLastTime.uiSitted)) ) iState = eTNFsm_Sit ;
	}

    int HpRegen		= pMob[conn].m_irgHPRecovery[iState] ;
	int TpRegen		= pMob[conn].m_irgTPRecovery[iState] ;
	if( eTNInAfn_PreventRegenHP & pMob[conn].m_iInnerAffections ) HpRegen = 0 ;
	if( eTNInAfn_PreventRegenTP & pMob[conn].m_iInnerAffections ) TpRegen = 0 ;
	if( 0 < pMob[conn].MOB.snKarma )
	{ // �������̸� regen�� �ϳ��� ���� �ʴ´�.
		HpRegen = 0 ;
		TpRegen = 0 ;
	}
	//#ifdef __TN_2ND_LOG__
	//{
	//	char chBuf[512] = { 0,0,0, } ;
	//	sprintf(chBuf, "\t[regenmob] mob(%d)�� ���� HP�� %d�ε� %d�� ȸ���ؼ� %d�� �Ǿ����ϴ�. �������(%d; 0:�ɱ�,1:����)\r\n", conn, pMob[conn].MOB.nHP, HpRegen, pMob[conn].MOB.nHP+HpRegen, iState ) ;
	//	pMob[conn].Print( chBuf ) ;
	//}
	//#endif //__TN_2ND_LOG__

	pMob[conn].IncHP( HpRegen ) ;
	pMob[conn].IncTP( TpRegen ) ;

	// party���鿡�� HP ���¸� ǥ��
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
		// party���� ������ ���� UpdateStatus �޽��� ����
	}

	///////////////////////////////////////////////////////////
	pMob[conn].BroadcastUpdateStatusMsg( true ) ;
}



// ��Ÿ�̸�
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
		{	SetTimer(hWndMain, TIMER_SEC, 100,NULL);  // 1�ʿ� 10���� ������ ���� ��Ų��.
			UserCount=0;
			return;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(g_snGiftItemGenTime != 0 && (SecCounter%g_snGiftItemGenTime == 0)) 
		g_nGiftItemMaxCount--;

	CurrentTime = timeGetTime();		// CurrentTime�� 0.25�ʸ��� update
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

	if( 0 == Rst4 ) // 1��(=4/4)
	{	MSGServerSocket.SendMessage();
		if((ServerIndex+1)==SERVER_KATANA3 && g_Yut.HT_bIsPlayOn())	//	īŸ��3�� ������ ���� �������ϰ��
			if(YutCounter>0) HT_PlayYut();
	}

	if( 0 == Rst16 ) // 4��(=16/4)
	{
		// time scheduler�� ���۽�Ų��. �׷��� time�� �˾ƾ� �Ѵ�.
		int iEvent = g_srgTimeSchedule[g_iTimeSlot] ;
		if( 0 < iEvent )
		{

			{
				char chBuf[256] = { 0,0,0, } ;
				sprintf(chBuf, "\r\nTimeSlot:%d, Event:%d", g_iTimeSlot, iEvent ) ;
				WriteLog( chBuf, ".\\Monster_Log\\[Log]TimeSchedulet.txt" ) ;
			}

			TriggerEvent( 0, iEvent, 0, 0, 0, 70 ) ;
		}

		//if( g_bIsInRvR ) // �ֽ��������� äŷ�� �Ѵ�.
		if( eZoneType_God == g_iZoneType )
		{
			if( (0 == (g_iHours % 24)) && (0 == g_iTimeSlot) )
			{ // 12�ð����� �ʱ�ȸ�� ���ش�. 
				// ��Ȯ�� Ȯ���� �߻����� �ʴ´�. ��� card�� �� ���� resuffle�� �� ��, data�� refresh�ؾ��ϴµ�, 3�ֽ��̶� �� ������ �� ã�´�.
				double dDistribution[5] = { 0,0,0, } ;
				dDistribution[0] = g_irgEntryCount[eTNClan_Brahma] / g_irgEntryCount[0] ;
				dDistribution[1] = g_irgEntryCount[eTNClan_Vishnu] / g_irgEntryCount[0] ;
				dDistribution[2] = g_irgEntryCount[eTNClan_Siva] / g_irgEntryCount[0] ;

				for( int k = 0 ; k < 3 ; ++k )
				{
					dDistribution[k] = 50 - int(dDistribution[k] * dDistribution[k] * 200) ; // 50 - (2 * ((����)^2 * 100))
					if( 10 > dDistribution[k] ) dDistribution[k] = 10 ;
					if( 50 < dDistribution[k] ) dDistribution[k] = 50 ;
				}

				g_krgBlessOfGod[0][eTNClan_Brahma].Init() ;
				g_krgBlessOfGod[0][eTNClan_Brahma].AddCard( 25, (int)dDistribution[0] ) ;
				g_krgBlessOfGod[0][eTNClan_Brahma].Shuffle() ;
				g_krgBlessOfGod[0][eTNClan_Vishnu].Init() ;
				g_krgBlessOfGod[0][eTNClan_Vishnu].AddCard( 25, (int)dDistribution[1] ) ;
				g_krgBlessOfGod[0][eTNClan_Vishnu].Shuffle() ;
				g_krgBlessOfGod[0][eTNClan_Siva].Init() ;
				g_krgBlessOfGod[0][eTNClan_Siva].AddCard( 25, (int)dDistribution[2] ) ;
				g_krgBlessOfGod[0][eTNClan_Siva].Shuffle() ;

				#ifdef __TN_EMERGENCY_LOG__
				{
					SYSTEMTIME st ;
					GetLocalTime( &st ) ;

					char chBuf[1280] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n[����]%d��%d��%d��, %d : %d : %d,  ����:%d, ����帶:%d, �񽴴�:%d, �ù�:%d\r\n"
						, st.wHour, st.wMinute, st.wSecond
						, (int)dDistribution[0], (int)dDistribution[1], (int)dDistribution[2]
						,g_irgEntryCount[0], g_irgEntryCount[eTNClan_Brahma], g_irgEntryCount[eTNClan_Vishnu], g_irgEntryCount[eTNClan_Siva] ) ;
					WriteLog( chBuf, ".\\Log\\[Log]RvREntry.txt" ) ;
				}
				#endif //__TN_EMERGENCY_LOG__
			}
		}

		++ g_iTimeSlot ;
		if( eTS_MaxSlot <= g_iTimeSlot )
		{
			g_iTimeSlot = 0 ;
			++g_iHours ; // �ð� ���� �Ϳ� ���� count�� �д�.
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
				if( i%8 == Rst8 ) // 2��
				{
					pMob[i].CheckAffections( CurrentTime ) ;//  magic-affect, every 2 sec			
					pMob[i].ProgressWaitAction() ;

					////----------------------------------------------------------------
					//// ���ǵ��� ���� �ڵ� 
					////----------------------------------------------------------------
					//if(pMob[i].MOB.byTrimuriti!=eTNClan_GM) 
					//{	//	2�ʴ� �ѹ� �̵��Ÿ��� üũ�Ѵ�.
					//	nDistanceX = pMob[i].TargetX-pUser[i].nPreX;
					//	nDistanceY = pMob[i].TargetY-pUser[i].nPreY;
					//	nDistance = (int)sqrt((double)( nDistanceX*nDistanceX + nDistanceY*nDistanceY) );
					//	//	if(nDistance > ���������ִ��̵��Ÿ�) ��������
					//	if((pMob[i].m_iMoveSpeed<=5 && nDistance>25) || (pMob[i].m_iMoveSpeed>5 && nDistance>40)) 
					//	{	
					//		memset(pSpeed, 0, sizeof(pSpeed));
					//		sprintf(pSpeed, "Char:[%s] move Distance:%d per 4sec at speed:%d \r\n", pMob[i].MOB.szName, nDistance, pMob[i].m_iMoveSpeed);
					//		TimeWriteLog(pSpeed, ".\\LOG\\[Log]Move.txt" );							
					//		AddCrackError(i, 5, CRACK_SPEED_HACK4); 
					//	}
					//	pUser[i].nPreX = pMob[i].TargetX;
					//	pUser[i].nPreY = pMob[i].TargetY;
					//}
				}
				
				//if( i%16 == Rst16 ) // 4��
				//{	if(pMob[i].MOB.byTrimuriti!=eTNClan_GM) 
				//	{	//	4�ʴ� �ѹ� �̵��Ÿ��� üũ�Ѵ�.
				//		nDistanceX = pMob[i].TargetX-pUser[i].nPreX;
				//		nDistanceY = pMob[i].TargetY-pUser[i].nPreY;
				//		nDistance = sqrt((double)( nDistanceX*nDistanceX + nDistanceY*nDistanceY) );
				//		//	if(nDistance > ���������ִ��̵��Ÿ�) ��������
				//		if((pMob[i].m_iMoveSpeed<=5 && nDistance>40) || (pMob[i].m_iMoveSpeed>5 && nDistance>50)) 
				//		{	
				//			memset(pSpeed, 0, sizeof(pSpeed));
				//			sprintf(pSpeed, "Char:[%s] move Distance:%d per 4sec at speed:%d \r\n", pMob[i].MOB.szName, nDistance, pMob[i].m_iMoveSpeed);
				//			WriteLog(pSpeed, ".\\LOG\\[Log]Move.txt" ) ;							
				//			AddCrackError(i, 15, CRACK_SPEED_HACK4); 
				//		}
				//		pUser[i].nPreX = pMob[i].TargetX;
				//		pUser[i].nPreY = pMob[i].TargetY;
				//	}
				//}
				
				if( i%32 == Rst32 ) // 8��(=32/4)
				{
					RegenMob(i) ; //User regenaration HP MP,
					pMob[i].ForgetAttacker() ;
					pMob[i].ClearAggressiveScore() ;
					pMob[i].RefreshPKPrty() ;
					
					CheckTimeTask( i ) ;
				}

				if( i%128 == Rst128 ) // 32��(=128/4)
				{
					pMob[i].ProcessContinuousEffect();
				}
			}
		}
/*	
		if(i%8==Rst8)
		{
			if	(pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY)
			{
				pMob[i].CheckAffections( CurrentTime ) ;//  magic-affect, every 2 sec
				pMob[i].ProgressWaitAction() ;
			}
		}


		if( i%16 == Rst16 )
		{
			if	(pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY)
			{
				RegenMob(i) ; //User regenaration HP MP,
			}
		}
		
		if( i%32 == Rst32 )  // 8��(=32/4)
		{
			if( pMob[i].MOB.nHP>0	&&	pUser[i].Mode==USER_PLAY )
			{
				pMob[i].RefreshPKPrty() ;
				CheckTimeTask( i ) ;
			}
		}
*/

		// send packet in send buffer. every 1/4 sec.
	    if (pUser[i].cSock.nSendPosition==0) continue; // nSend�� �ʱ�ȭ ���Ӳ���� �ݵ�� 0�� �ǹǷ� USER_ACCEPT�̻����� üũ���ʿ� ����.
		pUser[i].cSock.SendMessage();
	}
	//	billing auto-reconnect check
	if  (BILLING!=0 && BillCounter>0 && BillServerSocket.Sock==NULL)
	{	BillCounter--;
		if (BillCounter<=0)
		{	int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP2;			//	�ʸ����� ������ �ζ��λ���Ѵ�
			int ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip, WSA_READBILL, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect BILL Server(x2) fail.","-system",0);
				BILLING=0;//������� ����Ѵ�.
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
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� MSG Public���
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
				SaveUser(SaveCount,0);
				SaveCount++;
				break;
			}
			SaveCount++;
		}
	}

	// Logfile ���� - 16�ʿ� �ѹ��� ��¥ �������� Ȯ���Ͽ� �α����� ���� ����.
	if (Rst64==0) // 64/4
	{	struct tm when; time_t now;
		time(&now); when= *localtime(&now);
		if(LastLogDay!=when.tm_mday)
		{
			StartLog();
		}
	}
	
	if(Rst128==0) // 32��(128/4)
	{	
		//	���� �ູ������ 32�ʴ� 50�� �����Ѵ�.
		g_ItemRefineScale -= 50;
		if(g_ItemRefineScale<0) g_ItemRefineScale=0;

		//	���� �ູ������ 32�ʴ� 50�� �����Ѵ�.
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
					if(g_hGate[i]>MAX_USER && g_hGate[i]<MAX_MOB) pMob[g_hGate[i]].OnKilled( 1000, 8 ) ;
				}
			}
		}

		// scheduler ����
		g_kScheduler.CheckNRunSchedule( CurrentTime ) ;
		g_kSiege.CheckSymbols() ;
	}

	if(Rst512==0)
	{	if(ItemServerSocket.Sock!=NULL)
		{	int ser	= SecCounter;					// 0.5�ʴ����̹Ƿ� unsigned�� �ʿ����.
			int lst = ItemServerSocket.LastReceiveTime;	// 0.5�ʴ����̹Ƿ� unsigned�� �ʿ����.
			if	(lst>ser)		ItemServerSocket.LastReceiveTime = SecCounter; //��������Ŷ ���� �ð��� ���纸�� �� Ŭ���� ����.
			if	(lst<ser-480)	ItemServerSocket.LastReceiveTime = SecCounter; //1�� �̻� ����ߴµ����� �پ� �������� ����

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
	}

    ////////////////////////////////////////////////////////////////////////////////////
	/*	hp,mp regeneration by Potion;
	if	(Rest2==0)	// ���� ȸ���ӵ� 0.5�� �ƴϰ� 1��//
	{
		for	(int i=1;i<MAX_USER;i++)
		{	if	(pUser[i].Mode!=USER_PLAY)		 continue;
			if	(pMob[i].MOB.nHP<=0) continue;
			pUser[i].bQuaff=0;
			int ret1=ApplyHp(i);
			int ret2=ApplyMp(i);
			if (ret1) SendScore(i);	else	// �ǰ����� �ٸ�������Ե� ������ �Ѵ�.
			if (ret2) SendSetHpMp(i);
			//  1�ʴϱ� 200��ŭ ȸ��
		}
	}
	*/
	// dropped item decay
	ProcessDecayItem(); 

	for	( i=Rst64;i<=mNPCGen.NumList;i=i+64)	// generator tick : 64 tick = 16 sec
	{	int Interval = mNPCGen.pList[i].MinuteGenerate ;
		if( -1 == Interval )
		{		
			GenerateMob( i, 0, 0 ) ;
			mNPCGen.pList[i].MinuteGenerate = 0 ;
		}
		else
		{
			if( 0 >= Interval )	continue ; //{sprintf(temp,"err interval(npc pop-check time)  zero :%d",i);Log(temp,"-system",0);continue;}
			if( 0 != (Div64%Interval) ) continue ;
			GenerateMob( i, 0, 0 ) ;
		}	
	}

	ProcessMonster();
	ProcessRobot();
}

void ProcessMonster()
{
	int i = 0;
	// NPC AI
	int div = SecCounter % (SECSTANDINGBY);	 // %8,  1~7�� 2��(8/4)�� ��Ÿ����.
	for	( i=MAX_USER+div;i<MAX_MOB;i+=SECSTANDINGBY)  // User�� ���ϴ� ���μ����� ������� ������ MAX_USER + div ���� �����Ѵ� (div�� 0�϶��� �ִ�.)
	{	
		if (i>=MAX_MOB) break;     // NAX_MOB�� 8�� n���̸� �̳༮�� ������.

		int mode = pMob[i].Mode;
		if( MOB_EMPTY == mode )
		{		
			if( eTNCls_Warrior == pMob[i].MOB.byClass1 ) // 2005�� 4�� 11�� �������
			{
				if( pMob[i].IsDead() )
				{// �ð� �˻�
					if( pMob[i].IsWaitToPop() ) continue ;
				
					int iIndex = pMob[i].GenerateIndex ;
					if( 0 > iIndex ) continue ;
					int iMobListIndex = pMob[i].m_irgMobListIndex[0] ;
					int iMobListIndex2 = pMob[i].m_irgMobListIndex[1] ;
					if( 0 > iIndex || mNPCGen.NumList < iIndex ) 
					{
						// ��ȯ ��ü�� ��� ����� ���� �� �ִ�.
						continue ;
					}
					mNPCGen.pList[iIndex].krgMonsterList[iMobListIndex].srgReadyMobList[iMobListIndex2][1] = 1 ;
				}
			}

			continue;
		}

		if( 0 >= pMob[i].MOB.nHP )
		{	
			//Log("err standingby processer delete hp zero mob","-system",0);
			DeleteMob(i,1);
			continue;
		}			

		if( eTNAIO_LifeTime & pMob[i].m_iAIOption )
		{
			if( (0 != pMob[i].m_uiLifeTime) && (pMob[i].m_uiLifeTime < CurrentTime) )
			{
				KillMonster( i ) ;
				continue ;
			}
		}

		if( eTNAIO_HaveMaster & pMob[i].m_iAIOption )
		{
			//int iLeader = pMob[i].Leader;
			//if( i != pMob[iLeader].m_irgSummoned[pMob[i].MOB.byClass2] )
			//{			
			//	pMob[i].OnKilled( iLeader, 14 ) ;
			//	continue;
			//}

			if( eTNCls2_Retainer == pMob[i].MOB.byClass2 )
				if( pMob[i].CheckDistanceFromMaster( eRetainer_DistanceFromMaster ) ) continue ;
		}
	
		// �׻� client���� ������ �Ѵ�.
		if( pMonsterData[pMob[i].MOB.nTP].byQuest[eMonPrty_Reserved3] ) 
		{
			S_SCP_RESP_UPDATE_STATUS kMsg ;
			kMsg.wType = SCP_RESP_UPDATE_STATUS ;
			kMsg.wPDULength = WORD(sizeof(S_SCP_RESP_UPDATE_STATUS)-sizeof(HEADER));
			kMsg.snKeyID = (short)i ;
			kMsg.iHP = pMob[i].MOB.nHP ;
			kMsg.iTP = 0 ;
			kMsg.iPrana = 0 ;
			kMsg.iAffections = pMob[i].m_iAffections  ;
			kMsg.snKarma = 0 ;

			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&kMsg, i, 50 ) ;
		}

		// ȸ��
		if( (0 < pMob[i].MOB.nHP) && (pMob[i].m_iMaxHP > pMob[i].MOB.nHP) )
		{
			int iPrevHP = pMob[i].MOB.nHP ;
			int iHPRecovery = pMob[i].m_irgHPRecovery[1] ;
			if( eTNInAfn_PreventRegenHP & pMob[i].m_iInnerAffections ) iHPRecovery = 0 ;
			pMob[i].IncHP( iHPRecovery ) ; // HP ȸ��

			pMob[i].BroadcastUpdateStatusMsg() ;
		}

		// 2�ʿ� �ѹ� ����
		pMob[i].ForgetAttacker() ;

		if( eTNCls_Trap == pMob[i].MOB.byClass1 )
		{
			if( CurrentTime < pMob[i].m_uiActionLock ) continue ;

			pMob[i].SelectSkill() ;
			pMob[i].UseSkill() ;

			continue ;
		}

		if( eTNAIO_CombatOnly & pMob[i].m_iAIOption ) continue;
		if( eTNAIO_GetCommand & pMob[i].m_iAIOption ) continue; // �̵��� ���� ���̴�.

        if( MOB_PEACE == mode )
		{	
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue ;
			pMob[i].CheckAffections( CurrentTime ) ;
			pMob[i].InitStatus() ;
			pMob[i].InitCondition() ;

			if( eTNCls_SummonOld == pMob[i].MOB.byClass1 )
			{
				int iSummoner = pMob[i].Leader ;
				if( MOB_EMPTY == pMob[iSummoner].Mode || MOB_PEACE == pMob[iSummoner].Mode )
				{ // summoner�� �׾��ų� peace ���¿� ���� ��, ��ȯ�� Ǭ��.
					KillMonster( i ) ;
					//DeleteMob( i, 123 ) ;
					continue ;
				}
			}
						
			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}

			pMob[i].m_kLastTime.uiSelectTarget = 0 ;
			//pMob[i].m_iPlusRange = 0 ;

			if( 0 < pMob[i].m_iCastCount ) pMob[i].UseSkill() ;

			int last = pMob[i].SegmentProgress;

			// 1. ������ ������ �Ѵ�.
			int enemy = 0 ;
			if( pMob[i].m_kLastTime.uiActivate < CurrentTime ) // 10�� ������ ������ ���� �ʴ´�.
			{
				enemy = pMob[i].GetEnemyFromView(); // �þ߿� ���� �־, �ڽ��� �������� �Ÿ��� �ָ� �������� �ʴ´�. (�߰����ѰŸ�)
				pMob[i].m_kLastTime.uiActivate = 0 ;
			}

			if( 0 < enemy && MAX_MOB > enemy )
			{
				pMob[i].Think( eTNAI_Detect, enemy ) ;
				pMob[i].OnUnderAttack( enemy ) ;
				continue ;
			}

			BOOL ret=pMob[i].StandingByProcessor(); 

			if( 0x1 & ret ) // ���� segment�� �̵��ϴ� �߰�
			{	
				#ifdef __TN_5TH_LOG__
				{			
					SYSTEMTIME st ;
					GetLocalTime( &st ) ;

					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "[Move] %d��%d��%d��(%d) Monster %d(%d)�� (%d,%d)���� (%d,%d)�� �̵� \r\n", st.wHour, st.wMinute, st.wSecond, CurrentTime, i, pMob[i].MOB.snTribe, pMob[i].TargetX, pMob[i].TargetY, pMob[i].NextX,pMob[i].NextY ) ;
					pMob[i].Print( chBuf ) ;
				}
				#endif // #ifdef __TN_5TH_LOG__

				pMob[i].Think( eTNAI_Move, 0 ) ;

				MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
				sm.Effect = 2 ; // walk
				GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);

				int prog = pMob[i].SegmentProgress;   
				int gene = pMob[i].GenerateIndex;
			} 

			if( 0x10 & ret ) // ���׸��� �̵� �Ϸ�.
			{	// ���� ���׸�Ʈ ���α׷����� Action�� chat�� ������.
				int	prog = pMob[i].SegmentProgress;   
				int	gene = pMob[i].GenerateIndex;
				if	(prog<0||prog>=MAX_SEGMENT)
				{	//Log("err Segment progress out of bound",pMob[i].MOB.szName,0);
					continue;
				}
				continue;
			}

			if( 0x100 & ret )      //  �� ����
			{
				KillMonster( i ) ;
				DeleteMob( i, 3 ) ;  // ����
				continue ;
			}

			if( 0x1000 & ret )    //  0x 1000 ��ó�� ��ȸ , ���� segment�� �̵��ϱ����� wait�ϴ� �ð�����
			{
				pMob[i].Think( eTNAI_Rest, 0 ) ;
			}

			if( 0x0002 & ret )                      
			{	
				if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
				Teleport(i,pMob[i].NextX,pMob[i].NextY);
			}  
		} //  if  (mode == MOB_PEACE )
		else if( MOB_FLEE == mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	//Log("err standingby processer delete hp zero mob","-system",0);
				DeleteMob(i,1);
				continue;
			} 

			pMob[i].CheckAffections( CurrentTime ) ;
			pMob[i].InitStatus() ;

			if( eTNVSAfn_DontMove & pMob[i].m_iAffections ) //if( (eTNVSAfn_Stun & pMob[i].m_iAffections) || (eTNVSAfn_Sleep & pMob[i].m_iAffections) )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}

			++pMob[i].m_iPathProgress ;
			if( (eFlee_MaxPathCount <= pMob[i].m_iPathProgress) || (0 == pMob[i].m_krgPath[pMob[i].m_iPathProgress].x ) || (0 == pMob[i].m_krgPath[pMob[i].m_iPathProgress].y ) )
			{
				pMob[i].Mode = MOB_PEACE ;
				pMob[i].UpdateSpeed() ;
				pMob[i].NextX = pMob[i].SegmentX ;
				pMob[i].NextY = pMob[i].SegmentY ;

				int iDist = pMob[i].CalDistance2( pMob[i].SegmentX, pMob[i].SegmentY ) ;
				if( (eConst_TooFarRange < iDist) )
					Teleport(i,pMob[i].NextX,pMob[i].NextY);
				else
				{
					int iMove = pMob[i].m_iMoveSpeed ;
					if( 0 >= iMove ) iMove = 1 ;
					pMob[i].m_kLastTime.uiActivate = ((iDist - pMob[i].SegmentRange[pMob[i].SegmentProgress])/iMove + 5)*1000 + CurrentTime ;
				}

				continue ;
			}
			pMob[i].NextX = pMob[i].m_krgPath[pMob[i].m_iPathProgress].x ;
			pMob[i].NextY = pMob[i].m_krgPath[pMob[i].m_iPathProgress].y ;

			MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
			sm.Effect = 3 ; // run
			GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);
		}
		else if( MOB_ROAM == mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	//Log("err standingby processer delete hp zero mob","-system",0);
				DeleteMob(i,1);
				continue;
			} 

			pMob[i].CheckAffections( CurrentTime ) ;
			pMob[i].InitStatus() ;

			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )//if( (eTNVSAfn_Stun & pMob[i].m_iAffections) || (eTNVSAfn_Sleep & pMob[i].m_iAffections) )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}

			++pMob[i].m_iPathProgress ;
			if( 0 <= pMob[i].m_iPathProgress  && eRoam_MaxPathCount > pMob[i].m_iPathProgress )
			{
				pMob[i].NextX = pMob[i].m_krgPath[pMob[i].m_iPathProgress].x ;
				pMob[i].NextY = pMob[i].m_krgPath[pMob[i].m_iPathProgress].y ;

				if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
				if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty )
				{
					pMob[i].m_iPathProgress = eRoam_MaxPathCount + 1 ;
					continue ;
				}

				MSG_Action sm; GetAction(i,pMob[i].NextX,pMob[i].NextY,&sm);
				sm.Effect = 2 ; // run
				GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm);
			}				
			else
			{
				if( eRoam_MaxPathCount < pMob[i].m_iPathProgress )
				{
					pMob[i].NextX = pMob[i].SegmentX ;
					pMob[i].NextY = pMob[i].SegmentY ;
					pMob[i].Mode = MOB_PEACE ;

					pMob[i].Think( eTNAI_Return, 0 ) ;
					int iDist = pMob[i].CalDistance2( pMob[i].SegmentX, pMob[i].SegmentY ) ;
					if( (eConst_TooFarRange < iDist) )
						Teleport(i, pMob[i].NextX, pMob[i].NextY ) ;
					else
					{
						int iMove = pMob[i].m_iMoveSpeed ;
						if( 0 >= iMove ) iMove = 1 ;
						pMob[i].m_kLastTime.uiActivate = ((iDist - pMob[i].SegmentRange[pMob[i].SegmentProgress])/iMove + 5)*1000 + CurrentTime ;
					}
				}
			}
		}
	}
	//   Battle�̴�
	div = SecCounter % SECBATTLE;	 // %2 -> 0 or 1
	//int iTic = SecCounter % (SECBATTLE*2);	// %4 -> 0,1,2,3
	int even = SecCounter % (SECBATTLE*2);	 
	if( div == even ) even = 1;
	else even = 0;

    for( i = MAX_USER + div ; i < MAX_MOB ; i += SECBATTLE )
	{	
		if( MAX_MOB <= i ) break ; // �ִ� mob �迭 index�� �Ѿ�� skip
        if( MOB_COMBAT == pMob[i].Mode )
		{
			if( 0 >= pMob[i].MOB.nHP )
			{	sprintf(temp,"err battleprocessor delete hp 0 idx:%d, leader:%d fol0:%d fol1:%d",i,pMob[i].Leader,pMob[i].m_irgParty[0],pMob[i].m_irgParty[1]);
				Log(temp,"-system",0);
				DeleteMob(i,1);
				continue;
			}

			//if( 0 == iTic) // 1�ʴ� 1ȸ ����, 0�� 4tic�� 1ȸ �߻��Ѵ�.
			if( even )
			{
				pMob[i].CheckAffections( CurrentTime ) ;
				pMob[i].CheckCondition() ;
				pMob[i].CheckInvalidCombat() ;
			}

			if( eTNVSAfn_DontAttack & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}

			if( CurrentTime < pMob[i].m_uiActionLock ) continue ;

			pMob[i].m_uiActionLock = 0 ;

			int iAllowedTargets = pMob[i].SelectSkill() ;
			if( eTNAT_Enemy == iAllowedTargets )
			{
				int ret	= pMob[i].BattleProcessor( even ); 
				int	rnd	= rand() % 100;

				if( 0x0020 & ret )      //  �� ����
				{	DeleteMob( i, 3 ); // ����
					continue;
				}

				//---------------------------------------------------------
				// Attack
				//---------------------------------------------------------
				if( eTNRA_Attack & ret )
				{	
					//if( eTNVSAfn_Invulnerable & pMob[i].m_iAffections ) continue ;					
					pMob[i].m_iCantTraceTarget = 0 ;
					pMob[i].m_iTraceCount = 0 ;
					++pMob[i].m_iAttackCount ;

					pMob[i].UseSkill() ;

					if( (eTNCls_Warrior == pMob[i].MOB.byClass1) && pMob[i].m_kWeaknessRate.Random() ) // ��ȯ�� ���͵��� weaken ���°� ���� �ʴ´�.
					{// 4�� ���� weakness ���¿� �ɸ��� �Ѵ�.						
						TNEFFECT kEffect ;
						kEffect.iID = eTNAfn_Weakness ;
						kEffect.iDuration = 4000 ;
						pMob[i].AddEffect( kEffect, i, i ) ;

						pMob[i].BroadcastUpdateStatusMsg() ;
					}					
				}	

				//---------------------------------------------------------
				// Trace
				//---------------------------------------------------------
				if( eTNRA_Trace & ret )  // ����
				{
					if( eTNAIO_NoTrace & pMob[i].m_iAIOption ) continue;//  �������� �ʴ´�.
					int tz= pMob[i].CurrentTarget;
					if( 0 >= tz || MAX_MOB <= tz ) continue ;

					// ���� ���� ���� �˻�
					if( eTNCls_Summoned != pMob[i].MOB.byClass1 )
					{// �Ϲ� ������ ��츸, ���� �˻�
						++pMob[i].m_iTraceCount ;
						++pMob[i].m_iTotalTraceCount ;
						if( eTNAI_TraceCount < pMob[i].m_iTraceCount )
						{
							if( 0 == pMob[i].m_iCantTraceTarget ) // ��ġ�� ���� �˻�
							{
								int iDice = rand() % 100 ;
								if( iDice < pMob[i].m_iTraceCount ) // ���� ���� ���
								{
									ret = ret | 0x0010 ;
									#ifdef __DYNAMIC_LOG__
									if( pMob[i].m_iDebugFlag )
									{
										char chBuf[256] = { 0,0,0, } ;
										sprintf(chBuf, "[NPC AI] ���� ����> m_iTraceCount:%d, ret:%d, target������:%d \r\n", pMob[i].m_iTraceCount, ret, pMob[tz].m_iAttackerCount ) ;
										pMob[i].Print( chBuf ) ;
									}
									#endif
								}
								else pMob[i].Think( eTNAI_Trace, tz ) ;
							}
						}

						if( 25 < pMob[i].m_iTotalTraceCount )
						{// guard�� ���, ���� �Ÿ��� ���󰡰� �ʹ� �ָ����� �ڽ��� �������� �ٷ� teleport�Ѵ�.
							if( 2900 < pMob[i].MOB.snTribe && 2923 > pMob[i].MOB.snTribe )
							{							
								pMob[i].NextX = pMob[i].SegmentX ;
								pMob[i].NextY = pMob[i].SegmentY ;
								ret = ret | 0x0002 ;
							}
						}
					} // if( eTNCls_Summoned != pMob[i].MOB.byClass1 )

					pMob[i].UpdateSpeed() ;
					pMob[i].GetTargetPos( tz ) ;

					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
					if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty ) continue ;

					MSG_Action sm; GetAction( i, pMob[i].NextX, pMob[i].NextY, &sm ) ;
					sm.Effect = 3 ;
					GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm) ;

					pMob[i].m_uiActionLock = CurrentTime + 1000 ; // 1�� ���� ��� ����			
				}

				//---------------------------------------------------------
				// Return to Home
				//---------------------------------------------------------
				if( eTNRA_ReturnToHome & ret ) // ��ȯ
				{	
					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
					Teleport(i, pMob[i].NextX, pMob[i].NextY ) ;
				}

				//---------------------------------------------------------
				// End to Combat
				//---------------------------------------------------------
				if( eTNRA_EndToCombat & ret ) // ���� ���� -> ��ȯ
				{   
					if( eTNAIO_CombatOnly & pMob[i].m_iAIOption )
					{ // ������ �ϴ� ����� ���� ����ÿ� �׾�� �Ѵ�.
						//pMob[i].KillMonster( pMob[i].Leader, 16 ) ; // ��� ���� �ð��� ������.
						KillMonster( i );
						continue ;
					}

					int iTarget = pMob[i].CurrentTarget ;
					if( 0 < iTarget && MAX_USER > iTarget )
					{
						if( pMob[iTarget].IsAlive() ) pMob[i].Think( eTNAI_GiveUpToTrace, iTarget ) ;
					}

					pMob[i].InitStatus() ;
					pMob[i].CurrentTarget = 0 ;		
					pMob[i].LetsRoam() ;

					if( eTNAIO_GetCommand & pMob[i].m_iAIOption )					
					{
						pMob[i].Mode = MOB_PEACE ;
						pMob[i].OnFollow( pMob[i].Leader ) ;
						continue ;
					}
				}
			} // if( eTNAT_Enemy == iAllowedTargets )
			else
			{
				pMob[i].UseSkill() ;
			}
		}
	}
}



void ProcessRobot()
{
	int i = 0;
	// NPC AI
	int div = SecCounter % (SECSTANDINGBY);	 // %8,  1~7�� 2��(8/4)�� ��Ÿ����.
	for	( i=ROBOT_START+div;i<ROBOT_END;i+=SECSTANDINGBY)  // User�� ���ϴ� ���μ����� ������� ������ MAX_USER + div ���� �����Ѵ� (div�� 0�϶��� �ִ�.)
	{	
		if (i>=MAX_MOB) break;     // NAX_MOB�� 8�� n���̸� �̳༮�� ������.

		int mode = pMob[i].Mode;
		if( mode == MOB_EMPTY ) continue;

		//int clan = pMob[i].m_byClan;

		if( 0 >= pMob[i].MOB.nHP )
		{	//Log("err standingby processer delete hp zero mob","-system",0);
			DeleteMob(i,1);
			continue;
		}			


		// 2�ʿ� �ѹ� ����
		pMob[i].ForgetAttacker() ;
		pMob[i].CheckAffections( CurrentTime ) ;//  magic-affect, every 2 sec
	
        if(mode == MOB_PEACE )
		{	
			pMob[i].CheckAffections( CurrentTime ) ;
			//pMob[i].ForgetAttacker() ;
			pMob[i].InitStatus() ;
						
			if( eTNVSAfn_DontMove & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}			
		}
	}

	//   Battle�̴�
	div = SecCounter % SECBATTLE;	 // %2 -> 0 or 1
	//int iTic = SecCounter % (SECBATTLE*2);	// %4 -> 0,1,2,3
	int even = SecCounter % (SECBATTLE*2);	 
	if  (div==even) even = 1;
	else even = 0;
    for( i = ROBOT_START + div ; i < ROBOT_END ; i += SECBATTLE )
	{	
		if( i >= MAX_MOB ) break ; // �ִ� mob �迭 index�� �Ѿ�� skip
        if( MOB_COMBAT == pMob[i].Mode )
		{
			if	(pMob[i].MOB.nHP<=0)
			{	sprintf(temp,"err battleprocessor delete hp 0 idx:%d, leader:%d fol0:%d fol1:%d",i,pMob[i].Leader,pMob[i].m_irgParty[0],pMob[i].m_irgParty[1]);
				Log(temp,"-system",0);
				DeleteMob(i,1);
				continue;
			}

			if( eTNVSAfn_DontAttack & pMob[i].m_iAffections )
			{
				pMob[i].m_kLastTime.uiAttacked = CurrentTime ;
				continue ;
			}

			if( CurrentTime < pMob[i].m_uiActionLock ) continue ;

			pMob[i].m_uiActionLock = 0 ;

			pMob[i].m_iSkillCharged = 100;
			int iAllowedTargets = pMob[i].SelectSkill2() ;
			if( eTNAT_Enemy == iAllowedTargets )
			{
				int ret	=	pMob[i].CheckCombat();
				int	rnd	=	rand()%100;
				if	(ret&0x0020)      //  �� ����
				{	DeleteMob(i,3); // ����
					continue;
				}
				if	(ret&0x10000) 
				{	// �̸��
					//if	(rand()%2==0) SendEmotion(i,14,1);
				}
				if	(ret&0x1000)  // ���� ���� ���� �κ�
				{	
					pMob[i].UseSkill() ;
				}	

				if	(ret&0x0001)  // �߰�
				{
					//if( eTNAIO_NoTrace & pMob[i].m_iAIOption ) continue; // ���� �Ұ� ����
					//if( 1 == pMonsterData[pMob[i].MOB.nTP].byQuest[eMonPrty_TraceCond] ) continue ; // ���� �Ұ� ����
					int tz= pMob[i].CurrentTarget;
					if( 0 >= tz || MAX_MOB <= tz ) continue ;

					pMob[i].UpdateSpeed() ;
					pMob[i].GetTargetPos(tz) ;

					if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
					if( pMob[i].m_iBlockedCell & g_krgCell[pMob[i].NextY][pMob[i].NextX].usProperty ) continue ;

					MSG_Action sm; GetAction( i, pMob[i].NextX, pMob[i].NextY, &sm ) ;
					sm.Effect = 3 ;
					GridMulticast(i,pMob[i].NextX,pMob[i].NextY,(MSG_STANDARD*)&sm) ;

					pMob[i].m_uiActionLock = CurrentTime + 1000 ; // 1�� ���� ��� ����
					//pMob[i].m_uiActionLock = CurrentTime + pMob[i].m_uiActionDelay ; // 1�� ���� ��� ����
					
				}  
				//if	(ret&0x0002)          
				//{	
				//	if (pMob[i].NextX==pMob[i].TargetX && pMob[i].NextY==pMob[i].TargetY) continue ;
				//	Teleport(i, pMob[i].NextX, pMob[i].NextY ) ;
				//}  
				if(ret&0x0010) // ���� ���� -> ��ȯ
				{   
					pMob[i].Mode = MOB_PEACE ;

					pMob[i].InitStatus() ;
					pMob[i].CurrentTarget = 0 ;

					continue;
				}
			} // if( eTNAT_Enemy == iAllowedTargets )
			else
			{
				pMob[i].UseSkill() ;
			}
		}
	}
}





// ��Ÿ�̸�
void ProcessHourTimer( void )
{	
	g_RankSys.ReadRankFile(ServerGroup);		//	�Žð� ��ŷ���� ����(���� �����ʹ� �Ϸ翡 �ѹ� ����ǰ��ִ�)
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//  �α� ���� ���� ��� StartLog(), Log()
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
	 sprintf(temp,".\\EventLog\\GAME%4.4d_%2.2d_%2.2d_%2.2d_%2.2d.txt",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec);
	 g_fpEvent=fopen(temp,"wt");
	 LastLogDay = when.tm_mday;
}		   
void CrackLog(int conn,char * str)
{ 
     if (conn>=0 && conn<MAX_MOB)
	 {  sprintf(temp,"mob:%d Account:%s Char:%s %s \n",conn, pUser[conn].AccountName, pMob[conn].MOB.szName, str);
	 }  else
     {  sprintf(temp,"mob:%d %s \n",conn, str);
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
//  ����� �ú��� ����    Ÿ��   ���γ���   
//  021212 235959 account login  etc
//  021212 235959 account logout etc
//  021212 235959 account get    etc  // ����,����,��ũ��,����
//  021212 235959 account drop   etc  // ����,����,��ũ��,����
//  021212 235959 account trade  etc  // ����,����,��ũ��,����    item 4F3C000001010202 
//  021212 235959 account use    etc  // ����,����,��         success/fail used item
//  021212 235959 account admin  etc  // ������ ������ 

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
	//int iMaxCount = MAX_MOB - g_iFreeSlotForNPC ;
	for (int i = g_iFreeSlotForNPC ; i < MAX_MOB ; ++i )
	{
		if( MAX_MOB <= i ) return 0 ;
		if( MOB_EMPTY == pMob[i].Mode ) return i ;
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
	return 0; // User�� Wizard flag�� ����.
}

void CloseUser(int conn)
{
	if	(conn<0||conn>MAX_MOB)
	{	CrackLog(conn," SaveAndQuitMobidx");
		return;
	}

	pMob[conn].DropKalaCore() ;
	pMob[conn].ClearActivity() ;
	pMob[conn].ClearProperty() ;

	if( USER_PLAY == pUser[conn].Mode )
	{
		int nTarget = pUser[conn].Trade.OpponentID;
		if(nTarget>0 && nTarget<MAX_USER)		//	�ŷ����� ����� �����Ұ�� �ŷ���Ҹ� �����ش�.
		{	RemoveTrade(nTarget, REPLY_TRADE_USER_DENAY);
			memset(&(pUser[conn].Trade), 0, sizeof(pUser[conn].Trade));
		}

		RemoveChallenge(conn, eChallenge_System);									//	������带 �ʱ�ȭ�Ѵ�
		RemoveAlliance(pUser[conn].m_nAllianceUser, REPLY_GUILDALLIANCE_DISCONNECT);//	���� ��忬�� ��û����� �ִٸ� ����Ѵ�.

		for( int iFollowerIndex = 0 ; iFollowerIndex < eFollower_MaxCount ; ++iFollowerIndex )
		{
			int iFollower = pMob[conn].m_irgFollower[iFollowerIndex] ;
			if( MAX_USER <= iFollower && MAX_MOB > iFollower ) KillMonster( iFollower ) ; //pMob[iFollower].MOB.nHP = 0 ;
		}

		if( 0 < pMob[conn].MOB.nHP )
		{
			if( eWaitAct_Quit == pMob[conn].m_kWaitAction.iAction )
			{
				if( pMob[conn].m_kWaitAction.uiWaitingTime > CurrentTime ) return ;
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
			}
			else if( eWaitAct_ZonePortal == pMob[conn].m_kWaitAction.iAction ) // zone portal�� �̿��ϱ� ����, disconnect �ϴ� ���, ...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0 ;
				#ifdef __TN_5TH_LOG__
				{
					char chBuf[256] = { 0,0,0, } ;
					sprintf(chBuf, "[CloseUser] ZonePortal> %s, time:u, action:%d \r\n", pMob[conn].MOB.szName, CurrentTime, pMob[conn].m_kWaitAction.iAction ) ;
					WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]CloseUser.txt" ) ;
				}
				#endif // __TN_5TH_LOG__
			}
			else if( eWaitAct_ServerDown == pMob[conn].m_kWaitAction.iAction ) // Server Down��...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0 ;
			}
			else if( eWaitAct_Kickout == pMob[conn].m_kWaitAction.iAction ) // Server Down��...
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_None ;
				pMob[conn].m_kWaitAction.uiWaitingTime = 0 ;
			}
			else
			{
				pMob[conn].m_kWaitAction.iAction = eWaitAct_Quit ;
				pMob[conn].m_kWaitAction.uiWaitingTime = CurrentTime + g_irgSetting[eCnst_QuitTime] ; //eWaitTime_Quit ;

				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_ProtectFromMonster ;
				kEffect.iDuration = g_irgSetting[eCnst_QuitTime] + 60000 ;
				pMob[conn].AddEffect( kEffect, conn, conn ) ;
				
				#ifdef __TN_5TH_LOG__
				{
					char chBuf[256] = { 0,0,0, } ;
					sprintf(chBuf, "[CloseUser] ZonePortal> %s, time:u, action:%d \r\n", pMob[conn].MOB.szName, CurrentTime, pMob[conn].m_kWaitAction.iAction ) ;
					WriteLog( chBuf, ".\\MONSTER_LOG\\[Log]CloseUser.txt" ) ;
				}
				#endif // __TN_5TH_LOG__
				return ;
			}
		}
	}

	int nCount=0; int nGuildIndex = GetGuild(pMob[conn].MOB.nGuildID, FLAG_CLOSE);
	if(nGuildIndex==-1)	//	��������������� ����
	{	char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "[CloseUser] Char:%s GetguildID:%d fail  \r\n", pMob[conn].MOB.szName, pMob[conn].MOB.nGuildID ) ;
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
	pUser[conn].byTradeMode=0;		//	trade mode ����(���ϸ� �޼��� ó���κп��� �ٷ� ���ϵȴ�)
	pUser[conn].LoginTime=0;
	if	(pUser[conn].IsBillConnect)  {SendBilling(conn,pUser[conn].AccountName,2,0); pUser[conn].IsBillConnect=0;}
	pUser[conn].TickDiff=0;
	pUser[conn].cSock.CloseSocket();
	//pMob[conn].Mode = MOB_EMPTY; // �ϴ� ��� ������, USER�� Empty�� �ƴϱ� ������ Save���� �и� ������ ����.

	// �ϴ� ������ �ݵ�� ���´�.

	// ��� 12���� �����Ѱ�� ������ ������ �ʾ���. << DB�� ������ ���ذ� ����>> �������

	int mode = pUser[conn].Mode;
    if (mode == USER_EMPTY || mode == USER_ACCEPT )
	{  pUser[conn].CloseUser();
	   return;
	}
	// �̰��� Mob�� �� DB�� ������ ���� Quit�� �����ϴ�.
	// SAVING4QUIT�� ��� pUser�� sock�� �̹� Invalid�̴�.
    // SAVING4QUIT���� �ٽ� CloseUser�� �°��, ó������ �ʴ´�.
    // SAVING4QUIT �޽����� ���� ���� ���Ӽ��� Ÿ�̸Ӱ� �� ���� ���� ó���Ѵ�.
    if (mode == USER_PLAY|| mode == USER_SAVING4QUIT)
	{  
		if (mode == USER_PLAY)   CharLogOut(conn);
		// *CharLogout include following*
	    RemoveParty(conn, conn);

		//	�������� ���� ���������� �˸���.
		MSG_GuildMemberout nm;	nm.wType=_MSG_GuildMemberout;
		nm.GuildID = pMob[conn].MOB.nGuildID;
		nm.wPDULength = sizeof(nm) - sizeof(HEADER);
		strncpy(nm.CharacterName, pMob[conn].MOB.szName, SZNAME_LENGTH);
		//DBServerSocket.SendOneMessage((char*)&nm, sizeof(nm));	//	���� Ŭ���̾�Ʈ������ �츰��.
		SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*)&nm);
		//int trade=pUser[conn].Trade.OpponentID;
		//if (trade>0 && trade<MAX_USER)
		//{  if (pUser[trade].Mode==USER_PLAY && pUser[trade].Trade.OpponentID==conn) RemoveTrade(trade);
		//}
		//pUser[conn].Trade.OpponentID = 0;

		//	��������� ����
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

		if(ServerIndex==(SERVER_TRIMURITI-1) || ServerIndex==(SERVER_CHATURANGKA-1))
		{
			if(pMob[conn].MOB.byLevel<TRIMURITY_LEVEL) 
			{	pMob[conn].MOB.byZone=1; pMob[conn].MOB.snX=-1; pMob[conn].MOB.snZ=-1;
			}
		}

		//	Į���ƴ���(��,��,����)���� ���� ����� �ֽ������� �¾���� �����Ѵ�.
		if((ServerIndex+1)==SERVER_KALIA_LOW || (ServerIndex+1)==SERVER_KALIA_MIDDLE || (ServerIndex+1)==SERVER_KALIA_HIGH)
		{	pMob[conn].MOB.byZone=SERVER_TRIMURITI; pMob[conn].MOB.snX=-1; pMob[conn].MOB.snZ=-1;
		}

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
		sprintf(temp,"logout char%s: positionX:%d positionZ:%d rupiah:%d cargo:%d", pMob[conn].MOB.szName, pMob[conn].MOB.snX, pMob[conn].MOB.snZ, pMob[conn].MOB.nRupiah, pUser[conn].Coin);
		Log(temp,pUser[conn].AccountName,pUser[conn].IP);

		//	Send Billing Message
		if(pUser[conn].IsBillConnect==1) SendBilling(conn,pUser[conn].AccountName,2,1);
		//char chBuf[256] = {0,};
		//sprintf(chBuf, "logout char%s: positionX:%d positionZ:%d  \r\n",pMob[conn].MOB.szName, pMob[conn].MOB.snX, pMob[conn].MOB.snZ);
		//TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Position.txt" ) ;

		//DeleteMob(conn,2);
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

CMob * GetMobFromIndex(unsigned int index)
{	   if (index<0||index>=MAX_MOB)  return NULL;
	   return &pMob[index];
}

int  GetAngle(int x,int y)
{
	 if (x==0||y==0) return 0;
	 double tangle =  atan2( (FLOAT)y, (FLOAT) x);
     int angle = (int) ((tangle*3600)/6.283184);  
     if (angle<0) angle+=3600;
	 if (angle>3600) angle-=3600;
	 return angle;
}

int  GetLength(int x,int y)
{
	 FLOAT valx = (FLOAT)(x*x);
	 FLOAT valy = (FLOAT)(y*y);     
	 FLOAT valxy = valx+valy;
	 if (valxy>100) return 100;
	 if (valxy<=0) return 0;
	 double fout= sqrt(valxy);
     int out = (int) fout;
 
	 return out;
}


BOOL ReadMob(STRUCT_MOB * mob,char * Directory)
{
	int iID = atoi( mob->szName ) ;
	//mob->snTribe = (short)iID ;
	//mob->nBramanPoint = iID - HT_PARAMTYPE_MONSTER_START + 1 ;
	if(iID<2000 || iID>=(MAX_MONSTER_DATA+2000)) return FALSE;
	memcpy( mob, &pMonsterData[iID - 2000], sizeof(STRUCT_MOB) ) ;

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
//  - a_byProductionType : ���� ���� ���� ��ȣ, 0:�״� �ִ� or �����, 1:���ϴ� FX�� �Բ� �����
//------------------------------------------------------------------
void DeleteMob( int mob, int a_iReason, int a_iKiller, byte a_byProductionType )
{  
	if( 0 > mob || MAX_MOB <= mob ) return ;
	if( 0 > a_iKiller || MAX_MOB <= a_iKiller ) a_iKiller = 0 ;
	S_SCP_RESP_REMOVE_MOB sm; sm.wType = SCP_RESP_REMOVE_MOB; 
	sm.nID=mob; sm.byResult =a_iReason;sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
	sm.dwKillerID = a_iKiller ;
	sm.byRemoveType = a_byProductionType ;
	sm.snTribe = pMob[a_iKiller].MOB.snTribe ;
	strcpy( sm.szName, pMob[a_iKiller].MOB.szName ) ;
	if( 0 < mob && MAX_USER > mob )
	{
		GridMulticast( pMob[mob].TargetX, pMob[mob].TargetY, (MSG_STANDARD*)&sm, -1) ;
	}
	else GridMulticast(pMob[mob].TargetX,pMob[mob].TargetY,(MSG_STANDARD*)&sm, mob);


	if( 0 != a_iReason ) 
	{  
		pMob[mob].Mode = MOB_EMPTY ;

#ifdef __TN_TOP_LOG__
		if( mob != pMobGrid[pMob[mob].TargetY][pMob[mob].TargetX] )
		{
			char chBuf[256] = { 0,0,0, } ;
			sprintf( chBuf, "mob %d is not located in his position(%d,%d). \n", mob, pMob[mob].TargetX, pMob[mob].TargetY ) ;
			WriteLog( chBuf, ".\\Monster_Log\\[Log]InvalidMobGrid.txt" ) ;
		}
		#endif

		pMobGrid[pMob[mob].TargetY][pMob[mob].TargetX] = 0 ;
		//RemoveParty(mob, mob);

		//if( (MAX_USER <= mob) && (eTNCls_Warrior == pMob[mob].MOB.byClass1) )  // static�� NPC�� ���
		if( MAX_USER <= mob )
		{	
			int	idx=pMob[mob].GenerateIndex;
			int iIndex = pMob[mob].m_irgMobListIndex[0] ;
		    if	(idx>=0 && idx<MAX_NPCGENERATOR)
			{	
				--mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount ;
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
	DeleteMob(conn,2); 

	//	������������ ��������� ������ҿ��� ������ �̷������ �Ѵ�.
	if(ServerIndex+1==SERVER_CHATURANGKA || pMob[conn].MOB.nHP<=0)
	{	pMob[conn].MOB.byZone = pMob[conn].MOB.bySaveZone;
		pMob[conn].MOB.snX = pMob[conn].MOB.snSaveX;
		pMob[conn].MOB.snZ = pMob[conn].MOB.snSaveZ;
	}
	else if(ServerIndex+1==SERVER_STRONGHOLD)
	{
		bool bRet=true;
		DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
		bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_Front, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;
		if(!bRet)
		{	pMob[conn].MOB.byZone = SERVER_SHAMBALA;
			pMob[conn].MOB.snX = -1;
			pMob[conn].MOB.snZ = -1;
		}
		else
		{	pMob[conn].MOB.byZone = (BYTE)( dwServerID - HT_MAP_START + 1 ) ;
			pMob[conn].MOB.snX = GetRandom(snStartX, snEndX);
			pMob[conn].MOB.snZ = GetRandom(snStartZ, snEndZ);
		}
	}
	else if(ServerIndex+1==eZone_Katacomb)				//	�ϵμ����濡�� ������ ������������ ������.
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
	sprintf(temp,"dbg charlogout char:%s x:%d y:%d",pMob[conn].MOB.szName,pMob[conn].MOB.snX,pMob[conn].MOB.snZ);
	Log(temp,pUser[conn].AccountName,pUser[conn].IP);
	//SaveUser(conn,TRUE);
	
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
	mNPCGen.RebuildAreaData() ;
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
// NPC�� mob����  enemy�� ������ ��Ͻ�Ŵ, (������)
void SetBattle(int mob,int enemy)
{
	// �ڽŰ� �ڽ��� �׷쿡�� enemy�� ���. => �ڽſ��Ը� enemy�� ���.
	if (mob<=0 || enemy<=0|| mob>=MAX_MOB || enemy>=MAX_MOB) return;

	if (pMob[mob].Mode==MOB_EMPTY) return;
	if (pMob[enemy].Mode==MOB_EMPTY) return;
	if (mob<MAX_USER && pUser[mob].Mode!=USER_PLAY) return;

	if( eTNMob_PC != pMob[mob].m_eMobType )
	{
		int iRadius = pMob[mob].m_byBodyRadius + pMob[mob].m_kSight.sCombat ;
		int dx1 = pMob[mob].TargetX - iRadius ;
		int dy1 = pMob[mob].TargetY - iRadius ; 
		int dx2 = pMob[mob].TargetX + iRadius ;
		int dy2 = pMob[mob].TargetY + iRadius ;
		if( pMob[enemy].TargetX < dx1 || pMob[enemy].TargetX > dx2 || pMob[enemy].TargetY < dy1 || pMob[enemy].TargetY > dy2 )
		{
			#ifdef __TN_4TH_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "[SetBattle] ���� �þ� �ۿ� ����> �ڽ�(%d,Tribe:%d) L(%d,%d), ��(%d,Tribe:%d) L(%d,%d), ���ݽþ�:%d, ������뿵��(%d,%d, %d,%d) \r\n", mob, pMob[mob].MOB.snTribe, pMob[mob].TargetX, pMob[mob].TargetY, enemy, pMob[enemy].MOB.snTribe, pMob[enemy].TargetX, pMob[enemy].TargetY, pMob[mob].m_kSight.sCombat, dx1, dy1, dx2, dy2 ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]Combat.txt" ) ;
			}
			#endif // __TN_4TH_LOG__

			return ;
		}
	}

	pMob[mob].Mode=MOB_COMBAT;
	pMob[mob].AddEnemyList(enemy); 
}
*/

int CreateItem(int& x, int& y, STRUCT_ITEM *sour,  int nWho, DWORD dwMoney, int a_iParty, unsigned int a_uiReleaseTime )
{
	if( NULL == sour ) return 0;
	if( 0 >= sour->snIndex || MAX_ITEM_DATA <= sour->snIndex ) return 0 ;

	GetEmptyItemGrid(&x,&y);  // true�� gridx,gridy�� ���� ��ȿ, false�� ���ڸ� ����.

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
	pItem[destidx].Decay = pItemData[sour->snIndex].byDecay ;
    pItem[destidx].GridCharge = 0;			//BASE_GetItemAbility(sour,EF_GROUND);
    pItem[destidx].Height = 0;				//HeightGrid[y][x];
	pItem[destidx].m_iOwner = a_iParty ;
	pItem[destidx].m_uiReleaseTime = a_uiReleaseTime ;
	pItem[destidx].Money = dwMoney;
	pItem[destidx].ITEM.byDummy = 0;
	pItem[destidx].ITEM.wSerial = GetRandom(0, 65535);		//	���� �ø���ѹ� �������� �������� �߰��ϱ�� ��.

	pItemGrid[y][x]=destidx;				// ItemGrid���� IDX_ITEM�� �������� ���� ��� �ε����� �´�.

	/*
	int iID = pItemData[sour->snIndex].sID ;
	if( (eKalaCore_Brahma == iID) || (eKalaCore_Vishnu == iID) || (eKalaCore_Siva == iID) )
	{		
		for( int i = 0 ; i < eKala_MaxCount ; ++i )
		{
			if( 0 == g_krgKalaGround[i].x && 0 == g_krgKalaGround[i].y )
			{
				g_krgKalaGround[i].iHandle = iID ;
				g_krgKalaGround[i].x = x ;
				g_krgKalaGround[i].y = y ;
				break ;
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
	// 1:1�ŷ� ���
	
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
	//	��ƼŻ��
	int leader = pMob[Target].Leader;
	if  (leader<0||leader>=MAX_MOB)
	{   Log("err RemoveParty but worng leader",pUser[Target].AccountName,pUser[conn].IP);
	    return;
	}
	if(leader==0) leader=Target;

	SendRemoveParty(Target, 0);  // �ڽſ��� ��ƼŻ�� �˸���.

	pMob[leader].m_iLinker = 0 ; // �츶�縶�� ��ų�� �ʱ�ȭ �����ش�.
	for (int i=0;i<MAX_PARTY;++i)
	{
		int fol = pMob[leader].m_irgParty[i] ;
	   	if( 0 >= fol || MAX_USER <= fol ) continue ;
		pMob[fol].m_iLinker = 0 ;
	}

	if  (Target!=leader)							// ���� ������ �ƴҶ�.
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

	leader = pMob[Target].m_irgParty[0];			// ���ϴ� ���� �����϶�(���ο� ������ �����ϰ� �����Ѵ�)
	memcpy(pMob[leader].m_irgParty, &(pMob[Target].m_irgParty[1]), sizeof(int)*(MAX_PARTY-1));
	pMob[leader].Leader = 0; pMob[leader].byRootingMode = pMob[Target].byRootingMode;
	pMob[Target].byRootingMode = ROOTING_PERSON;	// ��Ƽ���� Ż��� ���ø��� ���η��ø��� �ȴ�

	//	��Ƽ�忡�� ��Ƽ��°�� �α׾ƿ���Ƽ�������� �˸���.
	SendRemoveParty(leader, Target);

	bool bSolo = true;
	//	��Ƽ������ ���ο� ��Ƽ��� �α׾ƿ���Ƽ�������� �˸���.
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

// ���� ������ ���°�
void ProcessDecayItem(void)
{    
	 for (int i=0;i<DecayValue;i++)  // 2ȸ. 2���� Decay ó���� �Ѵ�.
	 {
	    ItemCount++;
        if (ItemCount>=MAX_ITEM) ItemCount = g_dwInitItem+1;
	    if (pItem[ItemCount].Mode==FALSE) continue;
		if (eItm_Permenent == pItem[ItemCount].Decay )
		{
			char szMsg[1024] = { 0,0,0, } ;
			sprintf( szMsg, g_pMessageStringTable[_Post_Item_Location], pItem[ItemCount].PosX, pItem[ItemCount].PosY ) ;
			PostMessageToZone( szMsg ) ;

			continue;
		}
		if (eItm_Decay == pItem[ItemCount].Decay) {pItem[ItemCount].Decay=1; continue;}
    
		// ���� ����� Multicast �ϴ� �κ�.
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
						short sDur = eDur_Indestructible ;
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
		TimeWriteLog( chBuf, ".\\LOG\\BillPacket.txt" ) ;
	}	else
	{	conn = atoi(std1->Session);
		if (conn<=0||conn>=MAX_USER) return;
		nResult=htonl(std1->Result);
		nRemain=htonl(std1->Bill_Remain);
		sprintf(chBuf, "Packet_Type:%d Result:%d Session:%d ID:%s Bill_Method:%s RemainTime:%d \r\n", nType, nResult, conn, std1->User_ID, std1->Bill_Method, nRemain);
		TimeWriteLog( chBuf, ".\\LOG\\BillPacket.txt" ) ;

		if(strncmp(pUser[conn].AccountName, std1->User_ID, ACCOUNTNAME_LENGTH))
		{	if(std1->Packet_Type==_Msg_BillUserPlaying)
			{	std1->Result=2;
				SendBilling2(std1, _Msg_BillUserPlaying);
			}
		
			sprintf(chBuf, "err Dismatch Bill-Zone Session : conn:%d, ID:%s connID:%s \r\n", conn, std1->User_ID, pUser[conn].AccountName);
			TimeWriteLog(chBuf, ".\\LOG\\[Log]BillError.txt"); return;
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
				sm.nCommand = 1;	//	0:����, 1:��������
				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

				sprintf(temp,"dbg _Msg_BillUserIn result:%d char:%s",nResult, pMob[conn].MOB.szName);
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

	if(g_eCountryID == eCountryIndonesia)			//	�ӽ��ڵ�
	{	strcpy(sm.User_No, "1");					//	��� �׽�Ʈ�� ���� �ϵ��ڵ�.(������ pUser[conn].m_UserNo�� �Է��Ѵ�)
	}

	BillServerSocket.SendBillMessage((char*)&sm);

	return 0;
}

int	SendBilling2(_AUTH_GAME *m,int type)
{
	m->Packet_Type = ntohl(type);
	strncpy(m->S_KEY, S_Key, sizeof(m->S_KEY));

	int nID = ntohl(1);

	if(g_eCountryID == eCountryIndonesia)			//	�ӽ��ڵ�
	{	memcpy(m->User_No, &nID, sizeof(nID));		//	��� �׽�Ʈ�� ���� �ϵ��ڵ�.(������ pUser[conn].m_UserNo�� �Է��Ѵ�)
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
	short sIndex = 0 ;
	if( HT_PARAMTYPE_MONSTERSKILL_START <= a_sID ) // monster skill �̴�.
	{
		sIndex = a_sID - HT_PARAMTYPE_MONSTERSKILL_START + 4001 ;
		return sIndex ;		
	}

	sIndex = (a_sID - HT_PARAMTYPE_PCSKILL_START )*10 + a_byLevel ;
	return sIndex ;
}


void LoadSkillData()
{
	bool bRes = false ;
	int iIndex = 0 ;
	int iRange, iAOE, iRealm, iRace ;
	short sDummy = 0 ;
	int iDummy = 0 ;
	byte byDummy = 0 ;

	for( int iID = HT_PARAMTYPE_PCSKILL_START ; iID <= HT_PARAMTYPE_PCSKILL_END ; ++ iID )
	{		
		for( byte byLevel = 1 ; byLevel < 11 ; ++byLevel )
		{	
			iIndex = (iID - HT_PARAMTYPE_PCSKILL_START )*10 + byLevel ;

			bRes = g_ParamMgr.HT_bLockID( iID, byLevel ) ;
			if( bRes )
			{
				memset( &(pSkillData[iIndex].kDamage), 0, sizeof(TNDAMAGE) ) ;
				pSkillData[iIndex].sType = 0 ;
				pSkillData[iIndex].sItemType = 0 ;
				pSkillData[iIndex].sSkillType = 0 ;
				pSkillData[iIndex].sID = iID ;
				pSkillData[iIndex].byLevel = byLevel ;
				g_ParamMgr.HT_bGetPCSkillMaxLevel( &pSkillData[iIndex].byMaxLevel ) ;
				g_ParamMgr.HT_bGetPCSkillType( &byDummy ) ;
				if( byDummy ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Aid ;
				g_ParamMgr.HT_bGetPCSkillCombatPhase( &pSkillData[iIndex].sCombatPhase ) ;
				g_ParamMgr.HT_bGetPCSkillFollowRange( &pSkillData[iIndex].byFollow ) ;
				g_ParamMgr.HT_bGetPCSkillPierceRate( &pSkillData[iIndex].byPierceRate ) ;
				g_ParamMgr.HT_bGetPCSkillDuration( &pSkillData[iIndex].iCastDuration ) ;
				g_ParamMgr.HT_bGetPCSkillSuccessRate( &pSkillData[iIndex].bySuccessRate ) ;
				g_ParamMgr.HT_bGetPCSkillReadyTime( &iDummy ) ;
				pSkillData[iIndex].iAttackSpeed = iDummy ;
				g_ParamMgr.HT_bGetPCSkillCastingTime( &iDummy ) ;
				pSkillData[iIndex].iAttackSpeed += iDummy ;
				byte byAttackPointPosition = 0 ;
				g_ParamMgr.HT_bGetPCSkillReserve1( &byAttackPointPosition ) ;
				g_ParamMgr.HT_bGetPCSkillApplyTime( &iDummy ) ;
				// ���� �Ʒ��� activateTime�� �־�� �ϴµ�, C/S���� ��Ȯ�� �۾��� �ȵǾ� 1�������� ������ �ϰڴ�.
				pSkillData[iIndex].iActivateTime = 0 ;
				//pSkillData[iIndex].iActivateTime = (iDummy*(100-byAttackPointPosition))/100 ;  // PC ��ų�� ���, ...
				//pSkillData[iIndex].iApplyTime = iDummy ;
				//if( 200 < pSkillData[iIndex].iAttackSpeed ) pSkillData[iIndex].iAttackSpeed -= 200 ;
				g_ParamMgr.HT_bGetPCSkillCoolDownTime( &pSkillData[iIndex].iCoolDownTime ) ;
				if( 200 < pSkillData[iIndex].iCoolDownTime )
				{
					//pSkillData[iIndex].iCoolDownTime = pSkillData[iIndex].iCoolDownTime * 0.97;
				}
				g_ParamMgr.HT_bGetPCSkillRange( &iRange ) ;
				pSkillData[iIndex].iRange = iRange ;
				if( 0 < pSkillData[iIndex].iRange ) pSkillData[iIndex].iRange += 2 ;
				g_ParamMgr.HT_bGetPCSkillAreaOfEffect( &iAOE ) ;
				pSkillData[iIndex].iAOE = iAOE ;
				if( 0 < pSkillData[iIndex].iAOE ) pSkillData[iIndex].iAOE += 2 ;
				g_ParamMgr.HT_bGetPCSkillAllowedTarget( &pSkillData[iIndex].iAllowedTargets ) ;
				//g_ParamMgr.HT_bGetPCSkillCastingSuccessRate( &pSkillData[iIndex].byFizzleRate ) ;
				g_ParamMgr.HT_bGetPCSkillEffect1ID( &pSkillData[iIndex].krgEffect[0].iID ) ;
				g_ParamMgr.HT_bGetPCSkillEffect1Function( &pSkillData[iIndex].krgEffect[0].kFunc.iData ) ;
				g_ParamMgr.HT_bGetPCSkillEffect1Duration( &pSkillData[iIndex].krgEffect[0].iDuration ) ;
				g_ParamMgr.HT_bGetPCSkillEffect1Param1( &pSkillData[iIndex].krgEffect[0].iParam1 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect1Param2( &pSkillData[iIndex].krgEffect[0].iParam2 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect2ID( &pSkillData[iIndex].krgEffect[1].iID ) ;
				g_ParamMgr.HT_bGetPCSkillEffect2Function( &pSkillData[iIndex].krgEffect[1].kFunc.iData ) ;
				g_ParamMgr.HT_bGetPCSkillEffect2Duration( &pSkillData[iIndex].krgEffect[1].iDuration ) ;
				g_ParamMgr.HT_bGetPCSkillEffect2Param1( &pSkillData[iIndex].krgEffect[1].iParam1 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect2Param2( &pSkillData[iIndex].krgEffect[1].iParam2 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect3ID( &pSkillData[iIndex].krgEffect[2].iID ) ;
				g_ParamMgr.HT_bGetPCSkillEffect3Function( &pSkillData[iIndex].krgEffect[2].kFunc.iData ) ;
				g_ParamMgr.HT_bGetPCSkillEffect3Duration( &pSkillData[iIndex].krgEffect[2].iDuration ) ;
				g_ParamMgr.HT_bGetPCSkillEffect3Param1( &pSkillData[iIndex].krgEffect[2].iParam1 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect3Param2( &pSkillData[iIndex].krgEffect[2].iParam2 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect4ID( &pSkillData[iIndex].krgEffect[3].iID ) ;
				g_ParamMgr.HT_bGetPCSkillEffect4Function( &pSkillData[iIndex].krgEffect[3].kFunc.iData ) ;
				g_ParamMgr.HT_bGetPCSkillEffect4Duration( &pSkillData[iIndex].krgEffect[3].iDuration ) ;
				g_ParamMgr.HT_bGetPCSkillEffect4Param1( &pSkillData[iIndex].krgEffect[3].iParam1 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect4Param2( &pSkillData[iIndex].krgEffect[3].iParam2 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect5ID( &pSkillData[iIndex].krgEffect[4].iID ) ;
				g_ParamMgr.HT_bGetPCSkillEffect5Function( &pSkillData[iIndex].krgEffect[4].kFunc.iData ) ;
				g_ParamMgr.HT_bGetPCSkillEffect5Duration( &pSkillData[iIndex].krgEffect[4].iDuration ) ;
				g_ParamMgr.HT_bGetPCSkillEffect5Param1( &pSkillData[iIndex].krgEffect[4].iParam1 ) ;
				g_ParamMgr.HT_bGetPCSkillEffect5Param2( &pSkillData[iIndex].krgEffect[4].iParam2 ) ;
				g_ParamMgr.HT_bGetPCSkillCostTP( &pSkillData[iIndex].kCost.iTP ) ;
				g_ParamMgr.HT_bGetPCSkillCostHP( &pSkillData[iIndex].kCost.iHP ) ;
				g_ParamMgr.HT_bGetPCSkillidCostItem( &iDummy ) ;
				pSkillData[iIndex].kCost.sItemID = (short)iDummy ;
				g_ParamMgr.HT_bGetPCSkillCostItemCount( &pSkillData[iIndex].kCost.byItemCount ) ;
				g_ParamMgr.HT_bGetPCSkillReqLevel( &pSkillData[iIndex].kReq.byLevel ) ;
				g_ParamMgr.HT_bGetPCSkillReqTrimuriti( &iRealm ) ;
				pSkillData[iIndex].kReq.byTrimuriti = (byte)iRealm ;
				g_ParamMgr.HT_bGetPCSkillReqTribe( &iRace ) ;
				pSkillData[iIndex].kReq.byTribe = (byte)iRace ;
				g_ParamMgr.HT_bGetPCSkillReqClass( &pSkillData[iIndex].kReq.iClass ) ;
				g_ParamMgr.HT_bGetPCSkillReqSkill1( &iDummy ) ;
				pSkillData[iIndex].kReqSkill[0].sID = (short)iDummy ;
				g_ParamMgr.HT_bGetPCSkillReqSkill1_Lvl( &pSkillData[iIndex].kReqSkill[0].byLevel ) ;
				g_ParamMgr.HT_bGetPCSkillReqSkill2( &iDummy ) ;
				pSkillData[iIndex].kReqSkill[1].sID = (short)iDummy ;
				g_ParamMgr.HT_bGetPCSkillReqSkill2_Lvl( &pSkillData[iIndex].kReqSkill[1].byLevel ) ;
				g_ParamMgr.HT_bGetPCSkillReqWeaponType( &pSkillData[iIndex].iReqWeapon ) ;
				g_ParamMgr.HT_bGetPCSkillidReqItem( &pSkillData[iIndex].iReqItem ) ;
				g_ParamMgr.HT_bGetPCSkillAttackType( &byDummy ) ;
				pSkillData[iIndex].kDamage.iAttackType = byDummy ;
				byte byWeaponBase = 0 ;
				g_ParamMgr.HT_bGetPCSkillReserve0( &byWeaponBase ) ;
				if( 1 == byWeaponBase ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword ;
				
				/*
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant1 ;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant2 ;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_CastInstant3 ;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant2 ;
				pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnAffect ;

				*/
				//pSkillData[iIndex].kReq.sMuscle = pSkillData[iIndex].kReq.sNerves = pSkillData[iIndex].kReq.sHeart = pSkillData[iIndex].kReq.sMind = 0 ;
				pSkillData[iIndex].bySyncFlag = 0 ; // off 
				//pSkillData[iIndex].iActivateTime = 0 ;  // PC ��ų�� ���, ...
				pSkillData[iIndex].byCastCount = 1 ;
				pSkillData[iIndex].sSpeak = 0 ;

				pSkillData[iIndex].iPrice = 0 ;
				pSkillData[iIndex].sMaxDur = 0 ;
				pSkillData[iIndex].byMaxPackCount = 0 ;
				pSkillData[iIndex].sEventID = 0 ;				

#ifdef __TN_LOCAL_SERVER_SWITCH__

				/*
				if( 3114 == iID ) // ��ȯ
				{
					//pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[0].iID = 120 ;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0 ;
					pSkillData[iIndex].krgEffect[0].iDuration = 30 ;
					pSkillData[iIndex].krgEffect[0].iParam1 = 2076 ;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0 ;
				}
				*/
#endif
/*
				if( 3224 == iID ) // �ƻ�� - stun
				{					
					pSkillData[iIndex].krgEffect[2].iDuration = 7000 ;
					pSkillData[iIndex].krgEffect[2].iParam1 = 100 ;

					pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[3].iID = 3020 ; // Bonus damage, ����⿡ ���� effect
					pSkillData[iIndex].krgEffect[3].kFunc.iData = 3222 ; // ���ũ�θ� 1�� ����� �Ѵ�.
					pSkillData[iIndex].krgEffect[3].iParam1 = 100 ;
					pSkillData[iIndex].krgEffect[3].iParam2 = 200 ;
				}

				if( 3226 == iID ) // ����� ��Ÿ�� - PierceStrike 2
				{
					pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[1].iID = 3061 ;
					pSkillData[iIndex].krgEffect[1].kFunc.iData = 0 ;
					pSkillData[iIndex].krgEffect[1].iDuration = 0 ;
					pSkillData[iIndex].krgEffect[1].iParam1 = 50 ;
					pSkillData[iIndex].krgEffect[1].iParam2 = 100 ;
					if( 1 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 200 ;
					else if( 2 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 300 ;
					else if( 3 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 400 ;
					else if( 4 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 500 ;
					else if( 5 == byLevel ) pSkillData[iIndex].krgEffect[1].iParam2 = 600 ;
				}

				if( 3222 == iID ) // ���ũ�� - PreventRegenHP
				{
					pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[1].iID = 3210 ;
					pSkillData[iIndex].krgEffect[1].kFunc.iData = 0 ;
					pSkillData[iIndex].krgEffect[1].iDuration = 10000 ;
					pSkillData[iIndex].krgEffect[1].iParam1 = 0 ;
					pSkillData[iIndex].krgEffect[1].iParam2 = 0 ;
				}

				if( 3241 == iID ) // ī������ - All stat + 100
				{
					pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[0].iID = 4250 ;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0 ;
					pSkillData[iIndex].krgEffect[0].iDuration = 5000 ;
					pSkillData[iIndex].krgEffect[0].iParam1 = 100 ;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0 ;
				}

				if( 3208 == iID ) // �ٻ�Ƽ - All Resist + 50
				{
					pSkillData[iIndex].sCombatPhase = 0x7F ;
					pSkillData[iIndex].krgEffect[0].iID = 4240 ;
					pSkillData[iIndex].krgEffect[0].kFunc.iData = 0 ;
					pSkillData[iIndex].krgEffect[0].iDuration = 6000 ;
					pSkillData[iIndex].krgEffect[0].iParam1 = 50 ;
					pSkillData[iIndex].krgEffect[0].iParam2 = 0 ;
				}
*/
				if( 3241 == iID )
				{
					pSkillData[iIndex].iAllowedTargets = 2 ;
				}

/*
				if( 3328 == iID )
				{
					pSkillData[iIndex].iAllowedTargets = 2 ;
				}

				if( 3330 == iID )
				{
					pSkillData[iIndex].iCastDuration = 0 ;
				}
*/
/*				
				if( 3143 == iID )
				{
					//pSkillData[iIndex].sCombatPhase = 12 ;
					//pSkillData[iIndex].krgEffect[1].iID = 3010 ;
					//pSkillData[iIndex].krgEffect[1].kFunc.iData = 0 ;
					//pSkillData[iIndex].krgEffect[1].iDuration = 0 ;
					//pSkillData[iIndex].krgEffect[1].iParam1 = 50 ;
					//pSkillData[iIndex].krgEffect[1].iParam2 = 0 ;

					pSkillData[iIndex].iCoolDownTime = 10000 ;

					if( 1 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 4 ;
					else if( 2 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 4 ;
					else if( 3 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 5 ;
					else if( 4 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 5 ;
					else if( 5 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 7 ;
					else if( 6 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 7 ;
					else if( 7 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 8 ;
					else if( 8 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 8 ;
					else if( 9 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 9 ;
					else if( 10 == byLevel ) pSkillData[iIndex].krgEffect[2].iParam2 = 9 ;
				}
*/				

				for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
				{
					if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue ;

					if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
					//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
					if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
						|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash ;

					switch( pSkillData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Resurrect :
						pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant1 ;
					case eTNAfn_Terror :
					case eTNAfn_StealHP :
					case eTNAfn_StealTP :
					case eTNAfn_KnockBack :
						pSkillData[iIndex].krgEffect[i].iDuration = 0 ;
						break ;
					case eTNAfn_Taunt :
					case eTNAfn_DeTaunt :
						pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_AffectSelf ;
						break ;
					} // end of switch


					if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue ;

					switch( pSkillData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Damage :
					case eTNAfn_DamageSplash :
						pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
						break ;
					case eTNAfn_PierceDamage :
						pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_Fire :
					case eTNAfn_FireSplash :
						pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Fire ;
						break ;
					case eTNAfn_Cold :
					case eTNAfn_ColdSplash :
						pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Cold ;
						break ;
					case eTNAfn_Lightning :
					case eTNAfn_LightningSplash :
						pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Lightning ;
						break ;
					case eTNAfn_Poison :
					case eTNAfn_PoisonSplash :
						pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Poison ;
						break ;
					case eTNAfn_MultipleStrike :
						pSkillData[iIndex].byMaxPackCount = pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam2 ;
						if( 0 > pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 0 ;
						//if( 100 < pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 100 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_MultipleStrike ;
						//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
						break ;
/*
					case eTNAfn_EnergyOfSword :
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword ;
						break ;
*/
					case eTNAfn_Resurrect :
						pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam1 ;
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Resurrect ;
						break ;
					case eTNAfn_TPBurn :
						pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_ChangeTP ;
						break ;
					} // end of switch
				}

				if( eTNCPhase_CastInstant1 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
				if( eTNCPhase_CastInstant2 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
				if( eTNCPhase_CastInstant3 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "PC> %d, SkillID:%d, Level:%d, ReqLevel:%d, Type:%d, CastDuration:%d, AttackSpeed:%d(iApplyTime:%d), CoolDownTime:%d, CombatPhase:%d(WeaponBase:%d), AllowedTarget:%d, AOE:%d, Range:%d, SuccRate:%d, Follow:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d,%d), Effect1(%d,%d,%d,%d,%d), Effect2(%d,%d,%d,%d,%d), Effect3(%d,%d,%d,%d,%d), Effect4(%d,%d,%d,%d,%d), Cost(%d,%d,%d), AAType(%d,%d), MaxLevel:%d, �ٴ�ġ��(%d,%d), reqSkill(%d,%d) \r\n"
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
						) ;
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSkillData.txt" ) ;
				}
				#endif
			}
			g_ParamMgr.HT_bUnLockID( iID, byLevel ) ;
		}
	}


	iIndex = 4001 ;
	for( int iID = HT_PARAMTYPE_MONSTERSKILL_START ; iID <= HT_PARAMTYPE_MONSTERSKILL_END ; ++ iID )
	{
		iIndex = iID + 500 ;
		bRes = g_ParamMgr.HT_bLockID( iID, 1 ) ;
		if( bRes )
		{
			// initialize
			pSkillData[iIndex].bySyncFlag = 0 ; // off 
			pSkillData[iIndex].iActivateTime = 0 ;
			pSkillData[iIndex].byCastCount = 1 ;
			pSkillData[iIndex].sSpeak = 0 ;
			memset( &(pSkillData[iIndex].kDamage), 0, sizeof(TNDAMAGE) ) ;

			pSkillData[iIndex].sType = 0 ;
			pSkillData[iIndex].sItemType = 0 ;
			pSkillData[iIndex].sSkillType = 0 ;
			pSkillData[iIndex].sID = iID ;
			pSkillData[iIndex].byLevel = 1 ;
			g_ParamMgr.HT_bGetMonsterSkillMaxLevel( &pSkillData[iIndex].byMaxLevel ) ;
			g_ParamMgr.HT_bGetMonsterSkillType( &byDummy ) ;
			if( byDummy ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Aid ;
			g_ParamMgr.HT_bGetMonsterSkillCombatPhase( &pSkillData[iIndex].sCombatPhase ) ;
			g_ParamMgr.HT_bGetMonsterSkillFollowRange( &pSkillData[iIndex].byFollow ) ;
			g_ParamMgr.HT_bGetMonsterSkillPierceRate( &pSkillData[iIndex].byPierceRate ) ;
			g_ParamMgr.HT_bGetMonsterSkillDuration( &pSkillData[iIndex].iCastDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillSuccessRate( &pSkillData[iIndex].bySuccessRate ) ;
			g_ParamMgr.HT_bGetMonsterSkillSpeechContent( &pSkillData[iIndex].sSpeak ) ;
			g_ParamMgr.HT_bGetMonsterSkillSyncFlag( &pSkillData[iIndex].bySyncFlag ) ;
			g_ParamMgr.HT_bGetMonsterSkillCastingTime( &pSkillData[iIndex].iAttackSpeed ) ;
			g_ParamMgr.HT_bGetMonsterSkillActivateTime( &pSkillData[iIndex].iActivateTime ) ;
			g_ParamMgr.HT_bGetMonsterSkillCastCount( &pSkillData[iIndex].byCastCount ) ;			
			g_ParamMgr.HT_bGetMonsterSkillCoolDownTime( &pSkillData[iIndex].iCoolDownTime ) ;
			g_ParamMgr.HT_bGetMonsterSkillRange( &iRange ) ;
			pSkillData[iIndex].iRange = iRange ;
			if( 0 < pSkillData[iIndex].iRange ) pSkillData[iIndex].iRange += 2 ;		
			g_ParamMgr.HT_bGetMonsterSkillAreaOfEffect( &iAOE ) ;
			pSkillData[iIndex].iAOE = iAOE ;
			if( 0 < pSkillData[iIndex].iAOE ) pSkillData[iIndex].iAOE += 2 ;
			g_ParamMgr.HT_bGetMonsterSkillAllowedTarget( &pSkillData[iIndex].iAllowedTargets ) ;
			//g_ParamMgr.HT_bGetMonsterSkillCastingSuccessRate( &pSkillData[iIndex].byFizzleRate ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect1ID( &pSkillData[iIndex].krgEffect[0].iID ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect1Function( &pSkillData[iIndex].krgEffect[0].kFunc.iData ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect1Duration( &pSkillData[iIndex].krgEffect[0].iDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect1Param1( &pSkillData[iIndex].krgEffect[0].iParam1 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect1Param2( &pSkillData[iIndex].krgEffect[0].iParam2 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect2ID( &pSkillData[iIndex].krgEffect[1].iID ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect2Function( &pSkillData[iIndex].krgEffect[1].kFunc.iData ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect2Duration( &pSkillData[iIndex].krgEffect[1].iDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect2Param1( &pSkillData[iIndex].krgEffect[1].iParam1 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect2Param2( &pSkillData[iIndex].krgEffect[1].iParam2 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect3ID( &pSkillData[iIndex].krgEffect[2].iID ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect3Function( &pSkillData[iIndex].krgEffect[2].kFunc.iData ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect3Duration( &pSkillData[iIndex].krgEffect[2].iDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect3Param1( &pSkillData[iIndex].krgEffect[2].iParam1 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect3Param2( &pSkillData[iIndex].krgEffect[2].iParam2 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect4ID( &pSkillData[iIndex].krgEffect[3].iID ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect4Function( &pSkillData[iIndex].krgEffect[3].kFunc.iData ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect4Duration( &pSkillData[iIndex].krgEffect[3].iDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect4Param1( &pSkillData[iIndex].krgEffect[3].iParam1 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect4Param2( &pSkillData[iIndex].krgEffect[3].iParam2 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect5ID( &pSkillData[iIndex].krgEffect[4].iID ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect5Function( &pSkillData[iIndex].krgEffect[4].kFunc.iData ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect5Duration( &pSkillData[iIndex].krgEffect[4].iDuration ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect5Param1( &pSkillData[iIndex].krgEffect[4].iParam1 ) ;
			g_ParamMgr.HT_bGetMonsterSkillEffect5Param2( &pSkillData[iIndex].krgEffect[4].iParam2 ) ;
			g_ParamMgr.HT_bGetMonsterSkillAttackType( &byDummy ) ;
			pSkillData[iIndex].kDamage.iAttackType = byDummy ;

			//pSkillData[iIndex].iAllowedTargets = eTNAT_Enemy ;


			pSkillData[iIndex].kCost.iTP = 0 ;
			pSkillData[iIndex].kCost.iHP = 0 ;
			pSkillData[iIndex].kCost.sItemID = 0 ;
			pSkillData[iIndex].kCost.byItemCount = 0 ;
			pSkillData[iIndex].kReq.byLevel = 0 ;
			pSkillData[iIndex].kReq.byTrimuriti = 0xFF ;
			pSkillData[iIndex].kReq.byTribe = 0xFF ;
			pSkillData[iIndex].kReq.iClass = 0xFFFFFFFF ;
			pSkillData[iIndex].kReq.sMuscle = pSkillData[iIndex].kReq.sNerves = pSkillData[iIndex].kReq.sHeart = pSkillData[iIndex].kReq.sMind = 0 ;
			pSkillData[iIndex].iPrice = 0 ;
			pSkillData[iIndex].sMaxDur = 0 ;
			pSkillData[iIndex].byMaxPackCount = 0 ;
			pSkillData[iIndex].sEventID = 0 ;
			pSkillData[iIndex].sSkillType = 0 ;			

/*			if( 3976 == iID ) // ��Ǫ - death words
			{
				pSkillData[iIndex].sSpeak = 400 ;
			}

			if( 3928 == iID ) // God NPC�� bless skill
			{
				pSkillData[iIndex].krgEffect[1].iID = eTNAfn_BlessOfGod ;
				pSkillData[iIndex].krgEffect[1].kFunc.iData = 0 ;
				pSkillData[iIndex].krgEffect[1].iDuration = 1800000 ;
				pSkillData[iIndex].krgEffect[1].iParam1 = 0 ;
				pSkillData[iIndex].krgEffect[1].iParam2 = 0 ;

				pSkillData[iIndex].krgEffect[2].iID = eTNAfn_Heal ;
				pSkillData[iIndex].krgEffect[2].kFunc.iData = 3 ;
				pSkillData[iIndex].krgEffect[2].iDuration = 0 ;
				pSkillData[iIndex].krgEffect[2].iParam1 = 100 ;
				pSkillData[iIndex].krgEffect[2].iParam2 = 0 ;

				pSkillData[iIndex].krgEffect[3].iID = eTNAfn_RecoverTP ;
				pSkillData[iIndex].krgEffect[3].kFunc.iData = 3 ;
				pSkillData[iIndex].krgEffect[3].iDuration = 0 ;
				pSkillData[iIndex].krgEffect[3].iParam1 = 100 ;
				pSkillData[iIndex].krgEffect[3].iParam2 = 0 ;
			}
*/

/*
			if( 3989 == iID ) // �ޱ��ϸ��� - ī�︮Ÿ�� ���� ��ȯ
			{
				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Summon ;
				pSkillData[iIndex].krgEffect[0].kFunc.iData = 10 ;
				pSkillData[iIndex].krgEffect[0].iDuration = 1 ;
				pSkillData[iIndex].krgEffect[1].iParam1 = 2068 ;
				pSkillData[iIndex].krgEffect[1].iParam2 = 1 ;

				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Summon ;
				pSkillData[iIndex].krgEffect[0].kFunc.iData = 10 ;
				pSkillData[iIndex].krgEffect[0].iDuration = 1 ;
				pSkillData[iIndex].krgEffect[1].iParam1 = 2069 ;
				pSkillData[iIndex].krgEffect[1].iParam2 = 1 ;

				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Summon ;
				pSkillData[iIndex].krgEffect[0].kFunc.iData = 10 ;
				pSkillData[iIndex].krgEffect[0].iDuration = 1 ;
				pSkillData[iIndex].krgEffect[1].iParam1 = 2070 ;
				pSkillData[iIndex].krgEffect[1].iParam2 = 1 ;
			}
*/
/*
			if( 3973 == iID ) // ������ charge
			{
				pSkillData[iIndex].bySuccessRate = 100 ;
				pSkillData[iIndex].iCastDuration = 0 ;
				pSkillData[iIndex].iAOE = eTNSklA_Unit ;
				pSkillData[iIndex].iRange = 10 ;
				pSkillData[iIndex].iAllowedTargets = eTNAT_Enemy ;
				pSkillData[iIndex].sCombatPhase = 512 + 32 + 4 ;
				pSkillData[iIndex].bySyncFlag = 1 ; // on
				pSkillData[iIndex].iAttackSpeed = 100 ;
				pSkillData[iIndex].iCoolDownTime = 0 ;
				pSkillData[iIndex].iActivateTime = 100 ;
				pSkillData[iIndex].byCastCount = 1 ;
				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Dash ;
				pSkillData[iIndex].krgEffect[1].iID = eTNAfn_KnockBack ;
				pSkillData[iIndex].krgEffect[1].iParam1 = 100 ;
				pSkillData[iIndex].krgEffect[1].iParam2 = 7 ;
				pSkillData[iIndex].krgEffect[2].iID = 1 ;
				pSkillData[iIndex].krgEffect[2].iParam1 = 2000 ;
				pSkillData[iIndex].krgEffect[2].iParam2 = 2000 ;
				// ������~!!! �ϰ� ��ģ��.
				//pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 1 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 2 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 34 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 35 ;
			}
*/
			/*
			if( 3911 == iID ) // �ޱ��ϸ��� ����
			{
				pSkillData[iIndex].bySyncFlag = 1 ; // on
				pSkillData[iIndex].iAttackSpeed = 1000 ;
				pSkillData[iIndex].iActivateTime = 1000 ;
				pSkillData[iIndex].byCastCount = 2 ;
			}
			else if( 3912 == iID )
			{
				pSkillData[iIndex].bySyncFlag = 1 ; // on
				pSkillData[iIndex].iAttackSpeed = 2000 ;
				pSkillData[iIndex].iActivateTime = 1000 ;
				pSkillData[iIndex].byCastCount = 1 ;
			}
			else if( 3967 == iID )
			{
				pSkillData[iIndex].bySyncFlag = 1 ; // on
				pSkillData[iIndex].iAttackSpeed = 1000 ;
				pSkillData[iIndex].iActivateTime = 1000 ;
				pSkillData[iIndex].byCastCount = 2 ;
			}
*/
/*
			if( 3983 == iID )
			{
				pSkillData[iIndex].krgEffect[0].iID = eTNAfn_Pull ;
				//pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant2 ;
				pSkillData[iIndex].sCombatPhase = eTNCPhase_OnTakeInstant2 ;
			}
*/


			//pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
			#ifdef __TN_TOP_LOG__
			if( 0 > pSkillData[iIndex].iRange )
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "SkillID:%d, index:%d, Range:%d \r\n", pSkillData[iIndex].sID, iIndex, pSkillData[iIndex].iRange ) ;
				WriteLog( chBuf, ".\\Log\\[Log]Assert.txt" ) ;		
			}
			#endif


			for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
			{
				if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue ;

				if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
				else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
				//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
				if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
					|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash ;

				if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue ;

				switch( pSkillData[iIndex].krgEffect[i].iID )
				{
				case eTNAfn_Damage :
				case eTNAfn_DamageSplash :
					pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_PierceDamage :
					pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					break ;
				case eTNAfn_Fire :
				case eTNAfn_FireSplash :
					pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Cold :
				case eTNAfn_ColdSplash :
					pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Lightning :
				case eTNAfn_LightningSplash :
					pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Poison :
				case eTNAfn_PoisonSplash :
					pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_MultipleStrike :
					pSkillData[iIndex].byMaxPackCount = pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam2 ;
					if( 0 > pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 0 ;
					//if( 100 < pSkillData[iIndex].sMaxDur ) pSkillData[iIndex].sMaxDur = 100 ;

					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_MultipleStrike ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Resurrect :
					pSkillData[iIndex].sMaxDur = pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Resurrect ;
					break ;
				case eTNAfn_TPBurn :
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_ChangeTP ;
					break ;
/*
				case eTNAfn_EnergyOfSword :
					pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_EnergyOfSword ;
					break ;
*/
				} // end of switch
			}

			if( eTNCPhase_CastInstant1 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
			if( eTNCPhase_CastInstant2 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
			if( eTNCPhase_CastInstant3 & pSkillData[iIndex].sCombatPhase ) pSkillData[iIndex].sCombatPhase = pSkillData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "Monster> %d, SkillID:%d, Level:%d, Type:%d, CastDuration:%d, SyncFlag:%d, AttackSpeed:%d, ActivateTime:%d, CastCount:%d, CoolDownTime:%d, CombatPhase:%d, AllowedTarget:%d, AOE:%d, Range:%d, SuccRate:%d, Follow:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d,%d), Effect1(%d,%d,%d,%d,%d), Effect2(%d,%d,%d,%d,%d), Effect3(%d,%d,%d,%d,%d), Effect4(%d,%d,%d,%d,%d), Cost(%d,%d,%d,%d), AAType(%d,%d), MaxLevel:%d, �ٴ�ġ��(%d,%d), Speech:%d \r\n"
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
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSkillData.txt" ) ;
			}
			#endif

			++iIndex ;
		}
		g_ParamMgr.HT_bUnLockID( iID, 1 ) ;
	}
/*
	{
		pSkillData[4496].bySuccessRate = 100 ;
		pSkillData[4496].iCastDuration = 0 ;
		pSkillData[4496].iAOE = eTNSklA_Unit ;
		pSkillData[4496].iRange = 10 ;
		pSkillData[4496].iAllowedTargets = eTNAT_Friend ;
		pSkillData[4496].sCombatPhase = 64 ;
		pSkillData[4496].bySyncFlag = 0 ; // off
		pSkillData[4496].iAttackSpeed = 0 ;
		pSkillData[4496].iCoolDownTime = 0 ;
		pSkillData[4496].iActivateTime = 0 ;
		pSkillData[4496].byCastCount = 1 ;
		//pSkillData[4496].krgEffect[0].

		pSkillData[4497].bySuccessRate = 100 ;
		pSkillData[4497].iCastDuration = 0 ;
		pSkillData[4497].iAOE = eTNSklA_Unit ;
		pSkillData[4497].iRange = 10 ;
		pSkillData[4497].iAllowedTargets = eTNAT_Friend ;
		pSkillData[4497].sCombatPhase = 64 ;
		pSkillData[4497].bySyncFlag = 0 ; // off
		pSkillData[4497].iAttackSpeed = 0 ;
		pSkillData[4497].iCoolDownTime = 0 ;
		pSkillData[4497].iActivateTime = 0 ;
		pSkillData[4497].byCastCount = 1 ;
	}
*/


	pSkillData[0].sID = 0 ;
	pSkillData[0].byLevel = 0 ;
	pSkillData[0].byMaxLevel = 0 ;
	pSkillData[0].sMaxDur = 0 ;
	//pSkillData[0].byFizzleRate = 100 ;
	pSkillData[0].byFollow = 0 ;
	pSkillData[0].bySuccessRate = 1 ;
	pSkillData[0].iAOE = 0 ;
	pSkillData[0].iCastDuration = eTNSklD_Instant ;
	pSkillData[0].iRange = 0 ;
	pSkillData[0].bySyncFlag = 0 ;
	pSkillData[0].byCastCount = 1 ;
	pSkillData[0].iActivateTime = 0 ;
	pSkillData[0].iAllowedTargets = eTNAT_NA ;
	pSkillData[0].iAttackSpeed = 10000 ;	
	pSkillData[0].iCoolDownTime = 10000 ;
	pSkillData[0].kCost.iHP = 10000 ;
	pSkillData[0].kCost.iTP = 10000 ;
	pSkillData[0].kReq.byLevel = eLvl_Max ;
	pSkillData[0].kReq.byTribe = 0 ;
	pSkillData[0].kReq.byTrimuriti = 0 ;
	pSkillData[0].sType = 0 ;
	pSkillData[0].sItemType = 0 ;
	pSkillData[0].sSkillType = 0 ;
	pSkillData[0].kReq.sMuscle = pSkillData[0].kReq.sNerves = pSkillData[0].kReq.sHeart = pSkillData[0].kReq.sMind = 0 ;
	pSkillData[0].iPrice = 0 ;
	pSkillData[0].sMaxDur = 0 ;
	pSkillData[0].sEventID = 0 ;
	pSkillData[0].byArmorType = 0 ;
	pSkillData[0].kDamage.iAttackType = 0 ;
}


short GetItemDataIndex( short a_sID )
{
	short sIndex = a_sID - HT_PARAMTYPE_ITEM_START + 1 ;
	return sIndex ;
}

void LoadItemData()
{
	int iSpeedCorrect = 0 ;
	int iIndex = 0 ;
	bool bRes = false ;
	short sDummy = 0 ;
	int iDummy = 0 ;
	byte byDummy = 0 ;
	for( int iID = HT_PARAMTYPE_ITEM_START ; iID <= HT_PARAMTYPE_ITEM_END ; ++ iID )
	{		
		iIndex = iID - HT_PARAMTYPE_ITEM_START + 1 ;

		iSpeedCorrect = 0 ;
		bRes = g_ParamMgr.HT_bLockID( iID ) ;
		if( bRes )
		{
			pItemData[iIndex].sID = iID ;
			memset( &(pItemData[iIndex].kDamage), 0, sizeof(TNDAMAGE) ) ;
			g_ParamMgr.HT_bGetItemLevel( &pItemData[iIndex].byLevel );
			//g_ParamMgr.HT_bGetItemClass( &pItemData[iIndex].byClass );
			g_ParamMgr.HT_bGetItemType( &pItemData[iIndex].sItemType );

			if( 0 != pItemData[iIndex].sItemType )
			{// ��� ������ ��� 32bit�� true�� �����س��´�.
				if( HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_START <= iID && HT_PARAMTYPE_ITEM_WEAPON_THROW_END >= iID )
				{
					pItemData[iIndex].sItemType = pItemData[iIndex].sItemType | eTNWpn_TwoHand ;
					iSpeedCorrect = -201 ;
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
			g_ParamMgr.HT_bGetItemCombatPhase( &pItemData[iIndex].sCombatPhase ) ;
			g_ParamMgr.HT_bGetItemCoolDownTime( &pItemData[iIndex].iAttackSpeed );	// ���ݽð����� skill������ ready time�� ��Ÿ����. �ּ� �� �ð��� ����Ǿ���� 1ȸ ������ �ߵ��Ѵ�.		
			g_ParamMgr.HT_bGetItemRange( &byDummy );
			pItemData[iIndex].iRange = byDummy ;
			g_ParamMgr.HT_bGetItemCostTP( &pItemData[iIndex].kCost.iTP );
			g_ParamMgr.HT_bGetItemCostHP( &pItemData[iIndex].kCost.iHP );
			g_ParamMgr.HT_bGetItemidCostItem( &iDummy );
			pItemData[iIndex].kCost.sItemID = (short)iDummy ;
			g_ParamMgr.HT_bGetItemLimitTrimuriti( &iDummy );
			pItemData[iIndex].kReq.byTrimuriti = (byte)iDummy ;
			g_ParamMgr.HT_bGetItemLimitTribe( &iDummy );
			pItemData[iIndex].kReq.byTribe = (byte)iDummy ;
			g_ParamMgr.HT_bGetItemLimitLevel( &pItemData[iIndex].kReq.byLevel );
			g_ParamMgr.HT_bGetItemLimitMuscleChakra( &pItemData[iIndex].kReq.sMuscle );
			g_ParamMgr.HT_bGetItemLimitNerveChakra( &pItemData[iIndex].kReq.sNerves );
			g_ParamMgr.HT_bGetItemLimitHeartChakra( &pItemData[iIndex].kReq.sHeart );
			g_ParamMgr.HT_bGetItemLimitSoulChakra( &pItemData[iIndex].kReq.sMind );
			g_ParamMgr.HT_bGetItemAllowedTarget( &pItemData[iIndex].iAllowedTargets ) ;
			g_ParamMgr.HT_bGetItemEventID( &pItemData[iIndex].sEventID );
			g_ParamMgr.HT_bGetItemAttackType( &byDummy ) ;
			pItemData[iIndex].kDamage.iAttackType = byDummy ;
			g_ParamMgr.HT_bGetItemArmorType( &pItemData[iIndex].byArmorType ) ;
			g_ParamMgr.HT_bGetItemReserve1( &pItemData[iIndex].byDecay ) ;
			if( (eItm_Decay!=pItemData[iIndex].byDecay) && (eItm_Permenent!=pItemData[iIndex].byDecay) ) pItemData[iIndex].byDecay = eItm_Decay ;
			g_ParamMgr.HT_bGetItemReserve2( &pItemData[iIndex].kReq.byZone ) ; // zone ��� ����, 0 �̸� all

			if( 3 == pItemData[iIndex].kDamage.iAttackType ) iSpeedCorrect = 0 ; // ��հ��̸�, �ӵ������� ����.
			pItemData[iIndex].iAttackSpeed += iSpeedCorrect ;
			
			pItemData[iIndex].bySyncFlag = 0 ;
			pItemData[iIndex].byCastCount = 1 ;
			pItemData[iIndex].iActivateTime = 0 ; //pItemData[iIndex].iAttackSpeed ;  // ������ cooldowntime�̴�. �̰��� �������� ����Ǿ�� �� ���̴�.
			pItemData[iIndex].iCoolDownTime = 0 ;
			pItemData[iIndex].byMaxLevel = 0 ;
			//pItemData[iIndex].byClass = 0 ;
			pItemData[iIndex].iCastDuration = eTNSklD_Instant ;
			if( 1 == pItemData[iIndex].iRange ) pItemData[iIndex].iRange = eTNChr_MeleeAttackRange ;
			pItemData[iIndex].iAOE = eTNSklA_Unit ;
			pItemData[iIndex].bySuccessRate = 0 ;
			//pItemData[iIndex].byFizzleRate = 0 ;
			pItemData[iIndex].byFollow = 0 ;
			if( eTNWpn_Bow & pItemData[iIndex].sItemType ) pItemData[iIndex].byFollow = 1 ;
			pItemData[iIndex].kReq.iClass = 0xFFFFFFFF ;
			pItemData[iIndex].iReqWeapon = 0 ;
			pItemData[iIndex].iReqItem = 0 ;
			pItemData[iIndex].sSkillType = 0 ;	

			if( HT_PARAMTYPE_ITEM_USABLE_START <= iID && HT_PARAMTYPE_ITEM_USABLE_END > iID && (0<pItemData[iIndex].iAttackSpeed) )
			{	//	�Ҹ� item�� ���, ... 0.5���� ������ �ش�.
				pItemData[iIndex].iAttackSpeed -= 500 ;
				if( 0 > pItemData[iIndex].iAttackSpeed ) pItemData[iIndex].iAttackSpeed += 500 ;
			}
#ifdef __TN_LOCAL_SERVER_SWITCH__
			if( 6729 == iID )
			{
				pItemData[iIndex].krgEffect[0].iDuration = 30 ;
				//pItemData[iIndex].krgEffect[0].iID = 3080 ;
				//pItemData[iIndex].krgEffect[0].kFunc.iData = 2 ;
				//pItemData[iIndex].krgEffect[0].iParam1 = 50 ;
				//pItemData[iIndex].krgEffect[0].iParam2 = 100 ;
			}
#endif

			{
				for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
				{
					if( 0 >= pItemData[iIndex].krgEffect[i].iID ) continue ;

					/*
					if( eTNSklD_Instant != pItemData[iIndex].krgEffect[i].iDuration )
					{
						pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_OnAffect ;
						pItemData[iIndex].iAllowedTargets = eTNAT_Self ;
					}
					*/
					pItemData[iIndex].sSkillType = pItemData[iIndex].sSkillType | eTNSklT_EnergyOfSword ;

					switch( pItemData[iIndex].krgEffect[i].iID )
					{
					case eTNAfn_Damage :
					case eTNAfn_DamageSplash :
						pItemData[iIndex].kDamage.irgPhy[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgPhy[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_PierceDamage :
						pItemData[iIndex].kDamage.irgPierce[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgPierce[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_Fire :
					case eTNAfn_FireSplash :
						pItemData[iIndex].kDamage.irgFire[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgFire[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_Cold :
					case eTNAfn_ColdSplash :
						pItemData[iIndex].kDamage.irgCold[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgCold[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_Lightning :
					case eTNAfn_LightningSplash :
						pItemData[iIndex].kDamage.irgLightning[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgLightning[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_Poison :
					case eTNAfn_PoisonSplash :
						pItemData[iIndex].kDamage.irgPoison[0] += pItemData[iIndex].krgEffect[i].iParam1 ;
						pItemData[iIndex].kDamage.irgPoison[1] += pItemData[iIndex].krgEffect[i].iParam2 ;
						break ;
					case eTNAfn_WeaponMastery : // item������ �� effect�� ���Ǿ�� �ȵȴ�.
						pItemData[iIndex].krgEffect[i].iID = 0 ;
						break ;
					case eTNAfn_TPBurn :
						pItemData[iIndex].sSkillType = pItemData[iIndex].sSkillType | eTNSklT_ChangeTP ;

					default :
						//pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_OnTakeInstant1 ;
						//pItemData[iIndex].iAllowedTargets = eTNAT_Self ;
						break ;
					} // end of switch
				}
			}

			pItemData[iIndex].kDamage.iSum = pItemData[iIndex].kDamage.irgPhy[0] + pItemData[iIndex].kDamage.irgPierce[0] + pItemData[iIndex].kDamage.irgFire[0] + pItemData[iIndex].kDamage.irgCold[0] + pItemData[iIndex].kDamage.irgLightning[0] + pItemData[iIndex].kDamage.irgPoison[0] ;
			if( 0 < pItemData[iIndex].kDamage.iSum )
			{
				pItemData[iIndex].sCombatPhase = pItemData[iIndex].sCombatPhase | eTNCPhase_DealDamage ;
				//pItemData[iIndex].iAllowedTargets = eTNAT_Enemy ;
			}


			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "Index: %d, ID:%d, AttackSpeed:%d, ActivateTime:%d, CastCount:%d, CoolDown:%d, CombatPhase:%d, AllowedTarget:%d, AOE:%d, Range:%d, ��������:%d, Damage(%d~%d,%d~%d,%d~%d,%d~%d,%d~%d,%d~%d), Effect0(%d,%d,%d,%d), Cost(%d,%d,%d,%d), Dur:%d, Pack:%d, AAType(%d,%d), SyncFlag:%d, Decay:%d \r\n"
					, iIndex, pItemData[iIndex].sID, pItemData[iIndex].iAttackSpeed, pItemData[iIndex].iActivateTime, pItemData[iIndex].byCastCount, pItemData[iIndex].iCoolDownTime, pItemData[iIndex].sCombatPhase, pItemData[iIndex].iAllowedTargets, pItemData[iIndex].iAOE, pItemData[iIndex].iRange
					, pItemData[iIndex].sItemType, pItemData[iIndex].kDamage.irgPhy[0], pItemData[iIndex].kDamage.irgPhy[1], pItemData[iIndex].kDamage.irgPierce[0], pItemData[iIndex].kDamage.irgPierce[1], pItemData[iIndex].kDamage.irgFire[0], pItemData[iIndex].kDamage.irgFire[1], pItemData[iIndex].kDamage.irgCold[0], pItemData[iIndex].kDamage.irgCold[1], pItemData[iIndex].kDamage.irgLightning[0], pItemData[iIndex].kDamage.irgLightning[1], pItemData[iIndex].kDamage.irgPoison[0], pItemData[iIndex].kDamage.irgPoison[1]
					, pItemData[iIndex].krgEffect[0].iID, pItemData[iIndex].krgEffect[0].iDuration, pItemData[iIndex].krgEffect[0].iParam1, pItemData[iIndex].krgEffect[0].iParam2
					, pItemData[iIndex].kCost.iHP, pItemData[iIndex].kCost.iTP, pItemData[iIndex].kCost.sItemID, pItemData[iIndex].kCost.byItemCount, pItemData[iIndex].sMaxDur, pItemData[iIndex].byMaxPackCount
					, pItemData[iIndex].kDamage.iAttackType, pItemData[iIndex].byArmorType, pItemData[iIndex].bySyncFlag, pItemData[iIndex].byDecay
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadItemData.txt" ) ;
			}
			#endif
		}
		g_ParamMgr.HT_bUnLockID( iID ) ;
	}

	// Pist
	pItemData[0].iActivateTime = eTNChr_PistAttackSpeed ;
	pItemData[0].bySyncFlag = 0 ;
	pItemData[0].byCastCount = 1 ;
	pItemData[0].iAttackSpeed = eTNChr_PistAttackSpeed ;
	pItemData[0].iRange = eTNChr_MeleeAttackRange ;
	memset( &pItemData[0].kDamage, 0, sizeof(TNDAMAGE) ) ;
	pItemData[0].kDamage.irgPhy[0] = 1 ;
	pItemData[0].kDamage.irgPhy[1] = 2 ;
	pItemData[0].kDamage.irgPierce[0] = pItemData[0].kDamage.irgPierce[1] = 0 ;
	pItemData[0].sSkillType = eTNSklT_EnergyOfSword ;
	pItemData[0].sItemType = 0 ;
	pItemData[0].iAllowedTargets = eTNAT_Enemy ;
	pItemData[0].sCombatPhase = eTNCPhase_DealDamage ;
	pItemData[0].byArmorType = 0 ;
	pItemData[0].byDecay = eItm_Decay ;
	pItemData[0].kDamage.iAttackType = 0 ;
	pItemData[0].sMaxDur =	eDur_Indestructible ; // �Ǽ��� ���� �������̴�.
}


void LoadMonsterData()
{
	int iIndex = 0 ;
	bool bRes = false ;

	short sDummy = 0 ;
	int iDummy = 0 ;
	byte byDummy = 0 ;
	unsigned int uiDummy = 0 ;

	for( int iID = HT_PARAMTYPE_MONSTER_START ; iID <= HT_PARAMTYPE_MONSTER_END ; ++ iID )
	{		
		iIndex = iID - HT_PARAMTYPE_MONSTER_START + 1 ;

		bRes = g_ParamMgr.HT_bLockID( iID ) ;
		if( bRes )
		{
			pMonsterData[iIndex].nTP = iIndex ;
			pMonsterData[iIndex].snTribe = (short)iID ;
			g_ParamMgr.HT_bGetMonsterTrimuriti( &pMonsterData[iIndex].byTrimuriti ) ;
			g_ParamMgr.HT_bGetMonsterLevel(&pMonsterData[iIndex].byLevel );			
			g_ParamMgr.HT_bGetMonsterClass( &pMonsterData[iIndex].byClass1 ) ; // MOB.byClass1 = pMonsterData[MOB.nTP].byClass1 ;
			pMonsterData[iIndex].byClass2 = eTNCls2_Basic ;
			if( 0 >= pMonsterData[iIndex].byClass1 ) pMonsterData[iIndex].byClass1 = eTNCls_Warrior ;
			g_ParamMgr.HT_bGetMonsterSize( &pMonsterData[iIndex].byQuest[eMonPrty_Size] );

			// Sight
			g_ParamMgr.HT_bGetMonsterNormalSight( &pMonsterData[iIndex].byQuest[eMonPrty_NormalSight] );
			g_ParamMgr.HT_bGetMonsterCombatSight( &pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] );
			g_ParamMgr.HT_bGetMonsterCantDetect( &iDummy ) ;
			pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex = (short)iDummy ;
			//pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex = (short)eTNEye_DetectVisibleOnly ;

			// Move
			g_ParamMgr.HT_bGetMonsterMovement( &pMonsterData[iIndex].byQuest[eMonPrty_Movement] );
			g_ParamMgr.HT_bGetMonsterWalkSpeed( &iDummy );
			pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed] =(byte)iDummy ;
			g_ParamMgr.HT_bGetMonsterRunSpeed( &iDummy );
			pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed] = (byte)iDummy ;
			g_ParamMgr.HT_bGetMonsterBlockedCell( &iDummy ) ;
			pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex = (short)iDummy ;

			// Pop Delay
			g_ParamMgr.HT_bGetMonsterPopDelayMin( &uiDummy ) ;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex = (short)uiDummy ;
			g_ParamMgr.HT_bGetMonsterPopDelayMax( &uiDummy ) ;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex = (short)uiDummy ;

			// Resistance
			g_ParamMgr.HT_bGetMonsterFireResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = (short)iDummy ;			
			g_ParamMgr.HT_bGetMonsterColdResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = (short)iDummy ;
			g_ParamMgr.HT_bGetMonsterLightningResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = (unsigned short)iDummy ;
			g_ParamMgr.HT_bGetMonsterPoisonResist( &iDummy );
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = (short)iDummy ;

			
			// AI & Select Target
			g_ParamMgr.HT_bGetMonsterAI( &iDummy ) ;
			pMonsterData[iIndex].byQuest[eMonPrty_AI] = (byte)iDummy ;
			//if( 2920 == pMonsterData[iIndex].snTribe || 2921 == pMonsterData[iIndex].snTribe || 2922 == pMonsterData[iIndex].snTribe ) pMonsterData[iIndex].byQuest[eMonPrty_AI] = 3 ;

			g_ParamMgr.HT_bGetMonsterSelectTargetTime( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] ) ;
			if( 0 >= pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] = 5 ;
			pMonsterData[iIndex].snKarma = pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime] * 1000 ;
			if( 10000 < pMonsterData[iIndex].snKarma ) pMonsterData[iIndex].snKarma = 10000 ; // �ִ� 10��
			if( 1000 > pMonsterData[iIndex].snKarma ) pMonsterData[iIndex].snKarma = 1000 ; // �ּ� 1��
			g_ParamMgr.HT_bGetMonsterSelectTarget0( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0] = 0 ;
			g_ParamMgr.HT_bGetMonsterSelectTarget1( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1] = 0 ;
			g_ParamMgr.HT_bGetMonsterSelectTarget2( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2] = 0 ;
			g_ParamMgr.HT_bGetMonsterSelectTarget3( &pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3] = 0 ;
			pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly] = 1 ;
			if( (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3]) ) pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly] = 0 ; // ���� ����� ��ġ�� ���� target���� ����.

			// Speech
			g_ParamMgr.HT_bGetMonsterSpeechRate( &pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] );
			g_ParamMgr.HT_bGetMonsterSpeechAI( &pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] ) pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 0 ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] ) pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI] = 0 ;
			
			// Condition		
			g_ParamMgr.HT_bGetMonsterAggrCond( &pMonsterData[iIndex].byQuest[eMonPrty_AggrCond] );			
			g_ParamMgr.HT_bGetMonsterTraceCond( &pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] );
			g_ParamMgr.HT_bGetMonsterStepBackCond( &pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] ) pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond] = 0 ;
			g_ParamMgr.HT_bGetMonsterHelpCond( &pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] ) ;
			g_ParamMgr.HT_bGetMonsterHelpCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] ) ;
			g_ParamMgr.HT_bGetMonsterLinkCond( &pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] );
			g_ParamMgr.HT_bGetMonsterLinkCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] );
			g_ParamMgr.HT_bGetMonsterFleeCond( &pMonsterData[iIndex].byQuest[eMonPrty_FleeCond] );
			g_ParamMgr.HT_bGetMonsterFleeCondCount( &pMonsterData[iIndex].byQuest[eMonPrty_FleeCondCount] );

			g_ParamMgr.HT_bGetMonsterHP( &uiDummy ); // HP
			pMonsterData[iIndex].nHP = uiDummy ;

			// Combat Factors
			pMonsterData[iIndex].sMuscle = pMonsterData[iIndex].sNerves = pMonsterData[iIndex].sHeart = pMonsterData[iIndex].sMind = 0 ;
			g_ParamMgr.HT_bGetMonsterAttackRate( &iDummy ); // AR
			pMonsterData[iIndex].sMuscle = (short)iDummy ;
			g_ParamMgr.HT_bGetMonsterDodgeRate( &iDummy ); // DG
			pMonsterData[iIndex].sNerves = (short)iDummy ;
			g_ParamMgr.HT_bGetMonsterAC( &iDummy ); // AC
			pMonsterData[iIndex].sHeart = (short)iDummy ;
			if( 0 >= pMonsterData[iIndex].sHeart ) pMonsterData[iIndex].sHeart = 1 ;
			g_ParamMgr.HT_bGetMonsterEventNo( &uiDummy );
			pMonsterData[iIndex].snBagIndex = (short)uiDummy ; // event
			g_ParamMgr.HT_bGetMonsterArmorType( &pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] ) pMonsterData[iIndex].byQuest[eMonPrty_ArmorType] = 0 ;
			g_ParamMgr.HT_bGetMonsterHPRecovery( &pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] ) ;
			g_ParamMgr.HT_bGetMonsterMuscle( &pMonsterData[iIndex].Equip[eMonPrty_DodgeSpeed].snIndex ) ; // ȸ�� �ӵ�, muscle field ���

			// Immunity & Effect Delay
			g_ParamMgr.HT_bGetMonsterImmunity( &pMonsterData[iIndex].nGuildID ) ; // immunity
			g_ParamMgr.HT_bGetMonsterResistEffectConst( &pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] ) pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] = 0 ;
			//pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst] = 10 ;

			// Reserved
			g_ParamMgr.HT_bGetMonsterReserve0( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved0] ) ; // family No
			g_ParamMgr.HT_bGetMonsterReserve1( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved1] ) ; // ������ �پ� �ִ� �߰���(����) ���� �� ��ġ�� �Ѿ�� �������� �ʴ´�.
			g_ParamMgr.HT_bGetMonsterReserve2( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved2] ) ; // Not Used, Aggr Score�� ���� index
			g_ParamMgr.HT_bGetMonsterReserve3( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] ) ; // �׻� client�� �����ؼ� ���� ���縦 user�鿡�� �˸���.
			g_ParamMgr.HT_bGetMonsterReserve4( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved4] ) ; // ���� ����(1�̸� ����)DebugFlag ����, �����ʿ��� 1�� �����Ǿ� �ִ�.
			g_ParamMgr.HT_bGetMonsterReserve5( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved5] ) ; // Action Lock �ð�, �Ϲ� ���� 1���̴�.
			g_ParamMgr.HT_bGetMonsterReserve6( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved6] ) ; // ��ġ�� ���� ���� ����(�հ� �������� ����), 1�̸� �հ�����, 0�̸� �հ� ���� ���Ѵ�.
			g_ParamMgr.HT_bGetMonsterReserve7( &pMonsterData[iIndex].byQuest[eMonPrty_Reserved7] ) ; // Not Used, 


			// Skill Pattern
			g_ParamMgr.HT_bGetMonsterSkillPattern0( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 0 ;
			g_ParamMgr.HT_bGetMonsterSkillPattern1( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 0 ;
			g_ParamMgr.HT_bGetMonsterSkillPattern2( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 0 ;
			g_ParamMgr.HT_bGetMonsterSkillPattern3( &pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] ) ;
			if( 0 > pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] || eSklPtrn_Count <= pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] ) pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 0 ;	
			pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			if( (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2]) && (0==pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3]) ) pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 1 ; // �⺻ ��ų�� ��ϵǾ� �ִ� ���	

			// Skill
			g_ParamMgr.HT_bGetMonsterSkill0( &iDummy );
			pMonsterData[iIndex].Equip[0].snIndex = iDummy ; // �⺻ ���⸦ ��Ÿ����.
			g_ParamMgr.HT_bGetMonsterSkill1( &iDummy ) ;
			pMonsterData[iIndex].Equip[1].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[1].snIndex ) pMonsterData[iIndex].Equip[1].snIndex = pMonsterData[iIndex].Equip[0].snIndex ;
			if( 0 >= pMonsterData[iIndex].Equip[0].snIndex ) pMonsterData[iIndex].Equip[0].snIndex = pMonsterData[iIndex].Equip[1].snIndex ;
			g_ParamMgr.HT_bGetMonsterSkill2( &iDummy ) ;
			pMonsterData[iIndex].Equip[2].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[2].snIndex ) pMonsterData[iIndex].Equip[2].snIndex = pMonsterData[iIndex].Equip[0].snIndex ;
			g_ParamMgr.HT_bGetMonsterSkill3( &iDummy ) ;
			pMonsterData[iIndex].Equip[3].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[3].snIndex ) pMonsterData[iIndex].Equip[3].snIndex = pMonsterData[iIndex].Equip[0].snIndex ;
			g_ParamMgr.HT_bGetMonsterSkill4( &iDummy ) ; 
			pMonsterData[iIndex].Equip[4].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[4].snIndex ) pMonsterData[iIndex].Equip[4].snIndex = 0 ; // pMonsterData[iIndex].Equip[0].snIndex ;

			pMonsterData[iIndex].Equip[5].snIndex = 0 ;
			pMonsterData[iIndex].Equip[6].snIndex = 0 ;
			pMonsterData[iIndex].Equip[7].snIndex = 0 ;
			g_ParamMgr.HT_bGetMonsterSkill5( &iDummy ) ; 
			pMonsterData[iIndex].Equip[5].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[5].snIndex ) pMonsterData[iIndex].Equip[5].snIndex = 0 ; // pMonsterData[iIndex].Equip[0].snIndex ;
			g_ParamMgr.HT_bGetMonsterSkill6( &iDummy ); 
			pMonsterData[iIndex].Equip[6].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[6].snIndex ) pMonsterData[iIndex].Equip[6].snIndex = 0 ; // pMonsterData[iIndex].Equip[0].snIndex ;
			g_ParamMgr.HT_bGetMonsterSkill7( &iDummy ); 
			pMonsterData[iIndex].Equip[7].snIndex = iDummy ;
			if( 0 >= pMonsterData[iIndex].Equip[7].snIndex ) pMonsterData[iIndex].Equip[7].snIndex = 0 ; // pMonsterData[iIndex].Equip[0].snIndex ;


			pMonsterData[iIndex].byQuest[eMonPrty_MaxRange]  = 0 ;
			for( int mr = 0 ; mr < 7 ; ++mr )
			{
				if( 0 >= pMonsterData[iIndex].Equip[mr].snIndex ) continue ;
				int iSkillIndex = pMonsterData[iIndex].Equip[mr].snIndex + 500 ;				
				if( pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] < pSkillData[iSkillIndex].iRange )
				{
					pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] = pSkillData[iSkillIndex].iRange ;
				}
			}
			if( 3 > pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] ) pMonsterData[iIndex].byQuest[eMonPrty_MaxRange] = 3 ;
			

////////////////////////////////////////////////////////////////////////////////////////
			#ifdef __TN_LOCAL_SERVER_SWITCH__
			if( 2923 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 63 ;
			}
			#endif


			if( 2923 <= iID && 2950 >= iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] = 1 ; 
			}


			if( 2901 == iID || 2902 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_Reserved3] = 1 ; 
			}

			if( 2932 == iID || 2933 == iID || 2938 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 25 ;
			}

			if( 2945 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 25 ;
			}
			if( 2944 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 26 ;
			}
/*
			if( 2110 == iID )
			{
				pMonsterData[iIndex].Equip[1].snIndex = 3645 ;
				pMonsterData[iIndex].Equip[2].snIndex = 3973 ;
				pMonsterData[iIndex].Equip[3].snIndex = 3645 ;
				pMonsterData[iIndex].Equip[4].snIndex = 3645 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 1 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 2 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 34 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 35 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}
*/			

/*
			if( 2111 == iID || (2162<= iID && 2164 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}

			if( 2110 == iID || (2159<= iID && 2161 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}

			if( 2128 == iID || (2146<= iID && 2152 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}

			if( 2109 == iID || (2156<= iID && 2158 >=iID ) ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}

			if( 2107 == iID || 2104 == iID || 2105 == iID ) //
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 10 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
			}
*/
/*
			if( 2092 == iID ) // õȣ
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] = 90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1 ;
			}
			else if( 2094 == iID ) // ����
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 92 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] = 20 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1 ;
			}
			else if( 2090 == iID || 2091 == iID || 2095 == iID || 2096 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 91 ;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] = 90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] = 1 ;
			}
*/
/*
			if( 2001 == iID || 2002 == iID ) 
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCond] =90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount] = 1 ;
			}
			if( 2003 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_AI] = 91 ;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCond] =90 ;
				pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount] = 1 ;
			}
*/
/*
			if( 2924 == iID || 2925 == iID || 2926 == iID ) // 
			{
				pMonsterData[iIndex].nHP = 10 ; //25��
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = 362 ;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = 362 ;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = 362 ;
				pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = 362 ;
				pMonsterData[iIndex].sHeart = 689 ;
				//pMonsterData[iIndex].snBagIndex = 1 ;
				//pMonsterData[iIndex].Equip[0].snIndex = 3998 ;
			}
*/
/*
			if( 2113 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 34 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 35 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 36 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 37 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;

				//pMonsterData[iIndex].byQuest[eMonPrty_AI] = 35 ;
				//pMonsterData[iIndex].nHP = 200 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] = 0 ;
			}


			if( 2112 == iID )
			{
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0] = 21 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1] = 22 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2] = 24 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3] = 25 ;
				pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly] = 0 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100 ;
				//pMonsterData[iIndex].byQuest[eMonPrty_TraceCond] = 0 ;
			}
*/
/*
			if( 2947 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 32 ;
				pMonsterData[iIndex].byClass1 = 19 ;
			}
			if( 2948 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 34 ;
				pMonsterData[iIndex].byClass1 = 19 ;
			}
			if( 2949 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 36 ;
				pMonsterData[iIndex].byClass1 = 19 ;
			}
			if( 2950 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 30 ;
				pMonsterData[iIndex].byClass1 = 19 ;
			}


			if( 2901 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 4 ;
			}
			if( 2933 == iID )
			{
				pMonsterData[iIndex].snBagIndex = 3 ;
			}

			if( 2932 <= iID && 2950 >= iID )
			{				
				pMonsterData[iIndex].byQuest[eMonPrty_Movement] = 0 ;
				pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed] = 0 ;
				pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed] = 0 ;
				pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex = 0 ;
				pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate] = 100 ;
			}
*/

////////////////////////////////////////////////////////////////////////////////////////


			//---------------------------------------
			// Reward Prana, Braman, Gold
			//---------------------------------------
			g_ParamMgr.HT_bGetMonsterRewardBrahmanPoint( &uiDummy ) ;
			pMonsterData[iIndex].nBramanPoint = (int)uiDummy ;
			if( 0 >= pMonsterData[iIndex].nBramanPoint ) pMonsterData[iIndex].nBramanPoint = 0 ;			
			//pMonsterData[iIndex].nBramanPoint = (int)(pMonsterData[iIndex].nBramanPoint*dRwdBramanCorrect) ;

			g_ParamMgr.HT_bGetMonsterRewardPrana( &uiDummy );
			pMonsterData[iIndex].nPrana = (int)uiDummy ;
			if( 0 >= pMonsterData[iIndex].nPrana ) pMonsterData[iIndex].nPrana = 0 ;			
			//pMonsterData[iIndex].nPrana = (int)(pMonsterData[iIndex].nPrana*dRwdPranaCorrect) ;
			
			g_ParamMgr.HT_bGetMonsterRewardGold( &uiDummy ) ;
			pMonsterData[iIndex].nRupiah = (int)uiDummy ;
			if( 0 >= pMonsterData[iIndex].nRupiah ) pMonsterData[iIndex].nRupiah = 0 ;			
			//pMonsterData[iIndex].nRupiah = (int)(pMonsterData[iIndex].nRupiah*dRwdGoldCorrect) ;
			int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( pMonsterData[iIndex].nRupiah ) ;
			pMonsterData[iIndex].Inven[10].snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1 ;
			pMonsterData[iIndex].Inven[10].snDurability = eDur_Indestructible ;
			pMonsterData[iIndex].Inven[10].byCount = 1 ;

			//-----------------------------
			// Reward Items
			//-----------------------------		
			int iMaxRate = 10000 ;
			g_ParamMgr.HT_bGetMonsterItem0ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[0].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[0].snDurability = pItemData[pMonsterData[iIndex].Inven[0].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[0].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[0].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[0].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[0].bySubRefine[i] = 0 ;				
				g_ParamMgr.HT_bGetMonsterItem0DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][0].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[0].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[0].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][0].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[0].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem1ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[1].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[1].snDurability = pItemData[pMonsterData[iIndex].Inven[1].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[1].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[1].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[1].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[1].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem1DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][1].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[1].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[1].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][1].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[1].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem2ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[2].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[2].snDurability = pItemData[pMonsterData[iIndex].Inven[2].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[2].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[2].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[2].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[2].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem2DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][2].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[2].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[2].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][2].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[2].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem3ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[3].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[3].snDurability = pItemData[pMonsterData[iIndex].Inven[3].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[3].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[3].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[3].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[3].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem3DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][3].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[3].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[3].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][3].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[3].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem4ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[4].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[4].snDurability = pItemData[pMonsterData[iIndex].Inven[4].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[4].byCount = 1 ; // pItemData[pMonsterData[iIndex].Inven[4].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[4].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[4].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem4DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][4].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[4].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[4].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][4].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[4].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem5ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[5].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[5].snDurability = pItemData[pMonsterData[iIndex].Inven[5].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[5].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[5].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[5].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[5].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem5DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][5].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[5].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[5].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][5].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[5].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem6ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[6].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[6].snDurability = pItemData[pMonsterData[iIndex].Inven[6].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[6].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[6].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[6].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[6].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem6DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][6].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[6].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[6].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][6].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[6].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem7ItemID( &sDummy ); // the grade is equal to Item ID.
			if( 0 < sDummy )
			{
				pMonsterData[iIndex].Inven[7].snIndex = sDummy - HT_PARAMTYPE_ITEM_START + 1 ;
				pMonsterData[iIndex].Inven[7].snDurability = pItemData[pMonsterData[iIndex].Inven[7].snIndex].sMaxDur ;
				pMonsterData[iIndex].Inven[7].byCount = 1 ; //pItemData[pMonsterData[iIndex].Inven[7].snIndex].byMaxPackCount ;
				pMonsterData[iIndex].Inven[7].byRefineLevel = 0 ;
				for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) pMonsterData[iIndex].Inven[7].bySubRefine[i] =0 ;				
				g_ParamMgr.HT_bGetMonsterItem7DropRate( &sDummy );
				sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
				g_krgRewardItemRate[iIndex][7].Init( sDummy, iMaxRate ) ;
				if( 0 >= pItemData[pMonsterData[iIndex].Inven[7].snIndex].byLevel )
				{
					pMonsterData[iIndex].Inven[7].snIndex = 0 ;
					g_krgRewardItemRate[iIndex][7].Init( 0 ) ;
				}
			}
			else pMonsterData[iIndex].Inven[7].snIndex = 0 ;

			g_ParamMgr.HT_bGetMonsterItem8Grade( &byDummy );
			pMonsterData[iIndex].Inven[8].snIndex = byDummy ;
			g_ParamMgr.HT_bGetMonsterItem8DropRate( &sDummy );
			sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
			g_krgRewardItemRate[iIndex][8].Init( sDummy, iMaxRate ) ;

			g_ParamMgr.HT_bGetMonsterItem9Grade( &byDummy );
			pMonsterData[iIndex].Inven[9].snIndex = byDummy ;
			g_ParamMgr.HT_bGetMonsterItem9DropRate( &sDummy );
			sDummy = (short)(sDummy*g_dRwdItemCorrect ) ;
			g_krgRewardItemRate[iIndex][9].Init( sDummy, iMaxRate ) ;

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[1024] = { 0,0,0, } ;
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

) ;

				WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" ) ;
			}
			#endif

		}
		g_ParamMgr.HT_bUnLockID( iID ) ;
	}

	for( int i = 0 ; i < MAX_SKILL ; ++i ) pMonsterData[0].byQuest[i] = 0 ;
	pMonsterData[0].byTrimuriti = eTNClan_Neutral ;
	pMonsterData[0].nHP = 0 ;
	pMonsterData[0].sMuscle = pMonsterData[0].sNerves = pMonsterData[0].sHeart = pMonsterData[0].sMind = 0 ;
	pMonsterData[0].snSaveX = 0 ;
	pMonsterData[0].snSaveZ = 1 ;
	pMonsterData[0].snBagIndex = 0 ;
	pMonsterData[0].nTP = 0 ; // event
	for( int i = 0 ; i < MAX_EQUIP ; ++i )  pMonsterData[0].Equip[i].snIndex = 0 ; // skill
	pMonsterData[0].nPrana = 0 ;
	for( int i = 0 ; i < MAX_INVEN ; ++i )  pMonsterData[0].Inven[i].snIndex = 0 ; // reward

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
	//	Ȯ�� ���������.

	short snSour = (pSour->snIndex)+HT_PARAMTYPE_ITEM_START-1; 
	short snDest[3] = {0,};
	for(int i=0;i<3; i++) 
	{	if( pDest[i]==NULL) continue;
		snDest[i] = (pDest[i]->snIndex)+HT_PARAMTYPE_ITEM_START-1; 
	}
	bool bChecked = false;

	int iRefinable = 0;
	g_ParamMgr.HT_bGetItemRefinableItemType( snDest[0], &iRefinable);

	// ���� ���� ���θ� �Ǵ��Ѵ�.
	if ( !CHTParamIDCheck::HT_bIsItem( snDest[0] ) ) return REPLY_ITEM_REFINING_ERROR;				// �������� �ƴϸ� ����
	if ( CHTParamIDCheck::HT_bIsItemQuest( snDest[0] ) ) return REPLY_ITEM_REFINING_ERROR;			// ����Ʈ�� �������̸� ����
	if ( CHTParamIDCheck::HT_bIsItemAccessory( snDest[0] ) ) return REPLY_ITEM_REFINING_ERROR;		// �Ǽ��縮 �������̸� ����

	if(snDest[0]==eItem_amala)
	{	ZeroMemory(pSour->bySubRefine, MAX_SUBMATERIALSIZE);
		ZeroMemory(pDest[0], sizeof(STRUCT_ITEM));
		return REPLY_ITEM_SUBREFINING_INITIALIZE;
	}	else
	{	if ( CHTParamIDCheck::HT_bIsItemWeaponOneHand( snSour ) )			// One hand �����϶�
		{	if ( (iRefinable & _REFINE_WEPON_ONEHAND) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else 
		if ( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( snSour ) || CHTParamIDCheck::HT_bIsItemWeaponThrow( snSour ))
		{	if ( (iRefinable & _REFINE_WEPON_TWOHAND) == 0 ) return REPLY_ITEM_REFINING_ERROR;	// Two hand �����϶�(Ȱ����)
			bChecked = true;
		}	else 
		if ( CHTParamIDCheck::HT_bIsItemDefenceArmor( snSour ) )			// �����϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_ARMOR) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else
		if ( CHTParamIDCheck::HT_bIsItemDefencePants( snSour ) )			// �����϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_PANTS) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else
		if ( CHTParamIDCheck::HT_bIsItemDefenceGloves( snSour ) )			// �尩�϶�
		{   if ( (iRefinable & _REFINE_DEFENCE_GLOVES) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else
		if ( CHTParamIDCheck::HT_bIsItemDefenceShield( snSour ) )			// �����϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_SHIELD) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else 
		if ( CHTParamIDCheck::HT_bIsItemDefenceBelt( snSour ) )				// ��Ʈ�϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_BELT) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else 
		if ( CHTParamIDCheck::HT_bIsItemDefenceShoes( snSour ) )			// �Ź��϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_SHOES) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else 
		if ( CHTParamIDCheck::HT_bIsItemDefenceHelmet( snSour ) )			// �����϶�
		{	if ( (iRefinable & _REFINE_DEFENCE_HELMET) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}	else
		if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( snSour ) )
		{	if ( (iRefinable & _REFINE_ACCESSORY_NECKLACE) == 0 ) return REPLY_ITEM_REFINING_ERROR;
			bChecked = true;
		}
		//	else
		//if( CHTParamIDCheck::HT_bIsItemDefencePants( snSour ) )				// �����϶�
		//{	if ( (iRefinable & eItemPants) == 0 ) return REPLY_ITEM_REFINING_ERROR;
		//	bChecked = true;
		//}	else
		//if(  CHTParamIDCheck::HT_bIsItemDefenceGloves( snSour ) )			// �����϶�
		//{	if ( (iRefinable & eItemHelmet) == 0 ) return REPLY_ITEM_REFINING_ERROR;
		//	bChecked = true;
		//}
	}

	if ( !bChecked ) return 1;	// ���� �׸񿡼� üũ������ ������ ���� �ȵ�.

	BYTE	byMainLevel = 0;			//	����÷�������
	int		iPlusRate = 0;				//	����Ȯ�� +
	float	fMultipleRate = 1.0;		//	����Ȯ�� *
	bool	bProtectItem	= false;	//	������ �Ҹ����
	bool	bProtectSubItem = false;	//	������� �Ҹ����
	bool	bJade			= false;	//	�ڵ�Ӽ�
	if(pDest[1] != NULL)
	{
		TNSKILL_DATA* pkSkill = (TNSKILL_DATA*)&pItemData[pDest[1]->snIndex] ;

		for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
		{
			if( 0 >= pkSkill->krgEffect[i].iID ) continue ;
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
	if(CHTParamIDCheck::HT_bIsItemRefineMain(snDest[0]))	//	����������
	{	BYTE byLevel = pSour->byRefineLevel + 1;
		if(byLevel > MAX_MAINREFINELEVEL)	return REPLY_ITEM_REFINING_OVER;

		int nSubIndex = snDest[0]-HT_PARAMTYPE_ITEM_REFINE_MAIN_START+1;
		//for(int i=0; i<3; i++)
		//{	if(pDest[i]==NULL) continue;
		//	ZeroMemory(pDest[i], sizeof(STRUCT_ITEM));
		//}

		nRate = (int)((REFINE_MAIN[nSubIndex-1][pSour->byRefineLevel]+g_ItemRefineScale/2000+g_ItemRefineGMScale+iPlusRate)*fMultipleRate) ;
		if(nRate > 100) nRate = 100;
		if(nRate < 0) nRate = 0;

		byRes = (BYTE)g_RefineTable.GetValue(nRate);

		//char pData[256] = {0,};
		//sprintf(pData, "Main Refine level:%d->%d, Rate:%d, subrate1:%d subrate2:%d result:%d\r\n", pSour->byRefineLevel, pSour->byRefineLevel+1, REFINE_MAIN[nSubIndex-1][pSour->byRefineLevel], g_ItemRefineScale/2000, g_ItemRefineGMScale, byRes);
		//WriteLog(pData, ".\\LOG\\[Log]Refining.txt");

		if(byRes)
		{	pSour->byRefineLevel = byLevel;
		}
		else
		{	if(pSour->byRefineLevel>=REFINE_INITIALIZE_LEVEL && pSour->byRefineLevel<REFINE_DISAPEAR_LEVEL)
			{	if(bJade) return REPLY_ITEM_REFINING_FAIL;									//	÷������ �ڵ�� ��������
				pSour->byRefineLevel = 0;
				return REPLY_ITEM_REFINING_INITIALIZE;
			}	else
			if(pSour->byRefineLevel >= REFINE_DISAPEAR_LEVEL)
			{	if(bJade) { pSour->byRefineLevel = 6; return REPLY_ITEM_REFINING_FAIL; }	//	÷������ �ڵ�� 6���� �ʱ�ȭ
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
			{	bySubItem = byTot>>4;	//	����4��Ʈ ����
			}	else
			{	bySubItem = byTot&0x0F;	//	����4��Ʈ ����
			} 

			if(bySubItem == 0) break;
		}
		if(nIndex >= MAX_SUBMATERIAL && (dwSubItem<24 || dwSubItem>=33))	return REPLY_ITEM_REFINING_OVER;

	/*	ZeroMemory(pDest, sizeof(STRUCT_ITEM));*/

		nRate = (int)((REFINE_SUB[nIndex]+g_ItemRefineScale/2000+g_ItemRefineGMScale+iPlusRate)*fMultipleRate);
		if(nRate > 100) nRate = 100;
		if(nRate < 0) nRate = 0;

		byRes = (BYTE)g_RefineTable.GetValue(nRate);

		if(dwSubItem>=20 && dwSubItem<24)		//	6620 ~ 6623 ��¥������(ī����,����Ƽ,����,���Ϲ�)
		{	dwSubItem -= 19;	//	ī���� => �󰡸���(6601), ����Ƽ => �Ҷ󸶴�(6602)
			byRes = true;
		}
		else if(dwSubItem>=24 && dwSubItem<33)	//	6624 ~ 6632 Ÿ�� ����
		{
			DWORD dwTaruSubItem = dwSubItem - 23;		//	Ÿ�� �󰡸��� => �󰡸���
			DWORD dwTaruSubItem2 = dwTaruSubItem;
			for(int i=0; i<nIndex; i++)
			{	BYTE byTot=pSour->bySubRefine[i/2]; BYTE bySubItem=0;
				if(i%2==0)
				{	bySubItem = pSour->bySubRefine[i/2]>>4;
					if(bySubItem>=10 && bySubItem<14 && dwTaruSubItem>=1 && dwTaruSubItem<5)	//	���ø���� ���ø���� �ٲ��
					{	dwTaruSubItem2 += 9;								//	
					}
					dwTot = pSour->bySubRefine[i/2]&0x0F;	//	����4��Ʈ �ʱ�ȭ
					dwTot |= (dwTaruSubItem2<<4);
				}	else
				{	bySubItem = pSour->bySubRefine[i/2]&0x0F;
					if(bySubItem>=10 && bySubItem<14 && dwTaruSubItem>=1 && dwTaruSubItem<5)	//	���ø���� ���ø���� �ٲ��
					{	dwTaruSubItem2 += 9;								//	
					}
					dwTot = pSour->bySubRefine[i/2]&0xF0;	//	����4��Ʈ �ʱ�ȭ
					dwTot |= dwTaruSubItem2;
				}

				pSour->bySubRefine[i/2] = (BYTE)dwTot;
				dwTaruSubItem2 = dwTaruSubItem;
			}
			return 0;
		}

		if(byRes)
		{	if(nIndex%2==0)
			{	dwTot = pSour->bySubRefine[nIndex/2]&0x0F;	//	����4��Ʈ �ʱ�ȭ
				dwTot |= (dwSubItem<<4);
			}	else
			{	dwTot = pSour->bySubRefine[nIndex/2]&0xF0;	//	����4��Ʈ �ʱ�ȭ
				dwTot |= dwSubItem;
			}

			pSour->bySubRefine[nIndex/2] = (BYTE)dwTot;
		}	else 
		{	return REPLY_ITEM_REFINING_FAIL;
		}
	}	else return REPLY_ITEM_REFINING_FAIL;
	
	return 0;
}

void ExchangeTrade(int nSource, int nTarget)
{
	int nIndex = 0;
	for (int i=0;i<MAX_TRADE;i++)
	{	int nIndex = pUser[nSource].Trade.InvenPos[i];

		//	�������� ����
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

		//	�������� �߰�
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
	char szFileName[512] = { ".\\Data\\WorldSettings.ini" } ;
	char szInBuf[20] = { 0,0,0, } ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Item"), _T("StaffCorrect"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_StaffCorrect] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Item"), _T("StaffMaxNerves"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_StaffMaxNerves] = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Skill"), _T("AbsorbMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_AbsorbMax] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Skill"), _T("ReflectMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_ReflectMax] = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("SpeedMin"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_SpeedMin] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("SpeedMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_SpeedMax] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("HPRecvMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_HPRecvMax] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("TPRecvMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_TPRecvMax] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("ResistMax"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_ResistMax] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Property"), _T("HeartMax"), _T("350"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_HeartMax] = atoi( szInBuf ) ;

	
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Time"), _T("ProtectFromPK"), _T("15000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_ProtectionFromPK] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Time"), _T("RwdPriority"), _T("25000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_PriorityTime] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Time"), _T("TownPortal"), _T("5000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_TownPortalTime] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Time"), _T("AdvTownPortal"), _T("5000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_AdvTownPortalTime] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;

	g_irgSetting[eCnst_QuitTime] = 15000 ;
	GetPrivateProfileString( _T("Time"), _T("Quit"), _T("15000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_QuitTime] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Time"), _T("KalaCore"), _T("1800000"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_KalaCoreDur] = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("Restriction"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_Restriction] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("RwdBramanPoint"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_RwdBramanPoint] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("DecKarmaPoint"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_DecKarmaPoint] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("RwdKarmaPoint"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_RwdKarmaPoint] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("IncKarmaPoint"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_IncKarmaPoint] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("RwdGold"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_RwdGold] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("LoseGold"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_LoseGold] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("MaxKarma"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_MaxKarma] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("MurderDropRate"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_MurderDropRate] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("InnocentDropRate"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_InnocentDropRate] = atoi( szInBuf ) ;	
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("FirstStrikerDropRate"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_FirstStrikerDropRate] = atoi( szInBuf ) ;	
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("HuntHigh"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_HuntHigh] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("HuntLow"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_HuntLow] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("PK"), _T("FirstStrikeDur"), _T("0"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_FirstStrikeDur] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Penalty"), _T("KilledByMonster "), _T("5"), szInBuf, 10, szFileName ) ;
	g_irgSetting[eCnst_PenaltyByKilled] = atoi( szInBuf ) ;

	// Siege
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiegeSupport "), _T("1000000"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_FeeForSiegeSupport] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege1 "), _T("12000000"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_FeeForSiege1] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege2 "), _T("10000000"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_FeeForSiege2] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("FeeForSiege3 "), _T("8000000"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_FeeForSiege3] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("ItemCount "), _T("10"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_ItemCount] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("MemberLevel "), _T("60"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_MemberLevel] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("MemberCount1 "), _T("5"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_MemberCount1] = atoi( szInBuf ) ;
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Siege"), _T("MemberCount2 "), _T("5"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_MemberCount2] = atoi( szInBuf ) ;

	// Height
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Height"), _T("Obstacle  "), _T("100"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_ObstacleHeight] = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Height"), _T("Character  "), _T("400"), szInBuf, 16, szFileName ) ;
	g_irgSetting[eCnst_CharacterHeight] = atoi( szInBuf ) ;


	for( int i = 0 ; i < MAX_SETTING ; ++i )
	{
		char chBuf[512] = { 0,0,0, } ;
	
		sprintf(chBuf, "%d> %d \r\n", i, g_irgSetting[i] ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadWorldSettings.txt" ) ;
	}
}


void LoadZoneSettings()
{
	char szFileName[512] = { ".\\Data\\Settings.ini" } ;
	//wsprintf( szFileName, ".\\Data\\Settings.ini" ) ;
	char szCountry[64] = { 0,0,0, };
	GetPrivateProfileString( _T("Country"), _T("Name"), _T("Korea"), szCountry, 64, szFileName );
    strupr( szCountry );
	if		( strncmp( szCountry, "KOREA", 64 ) == 0 ) g_eCountryID = eCountryKorea;
	else if ( strncmp( szCountry, "CHINA", 64 ) == 0 ) g_eCountryID = eCountryChina;
	else if ( strncmp( szCountry, "JAPAN", 64 ) == 0 ) g_eCountryID = eCountryJapan;
	else if ( strncmp( szCountry, "INDONESIA", 64 ) == 0 ) g_eCountryID = eCountryIndonesia;
	else if ( strncmp( szCountry, "PHILIPPINES", 64 ) == 0 ) g_eCountryID = eCountryPhilippines;
	else if ( strncmp( szCountry, "TAIWAN", 64 ) == 0 ) g_eCountryID = eCountryTaiwan;

	char szInBuf[20] = { 0,0,0, } ;
	GetPrivateProfileString( _T("Zone"), _T("ID"), _T("1"), szInBuf, 10, szFileName ) ;
	g_iZoneID = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Zone"), _T("Type"), _T("0"), szInBuf, 10, szFileName ) ;
	g_iZoneType = atoi( szInBuf ) ; // default�� �Ϲ����̴�.

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Country"), _T("PK"), _T("1"), szInBuf, 10, szFileName );
	int iPK = atoi( szInBuf ) ;
	if( 0 == iPK ) g_iSwitch = g_iSwitch | eTNSwitch_PKDisable ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Country"), _T("MonsterSpeech"), _T("1"), szInBuf, 10, szFileName );
	int iMonsterSpeech = atoi( szInBuf ) ;
	if( 0 == iMonsterSpeech ) g_iSwitch = g_iSwitch | eTNSwitch_MonsterSpeechDisable ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Country"), _T("AttackSpeedHack"), _T("1500"), szInBuf, 10, szFileName );
	g_irgSetting[eCnst_AttackSpeedHack] = atoi( szInBuf ) ;
	
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("World"), _T("ID"), _T("1"), szInBuf, 10, szFileName ) ;
	g_iWorldID = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Version"), _T("Ver"), _T("0.0.0.0"), szInBuf, 10, szFileName ) ;
	sscanf(szInBuf, "%d.%d.%d.%d", &g_snVersion[0], &g_snVersion[1], &g_snVersion[2], &g_snVersion[3]);

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Correct"), _T("RwdPrana"), _T("100"), szInBuf, 10, szFileName ) ;
	int iRwdPranaCorrect = atoi( szInBuf ) ;
	
	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Correct"), _T("RwdRateForNormalItem"), _T("100"), szInBuf, 10, szFileName ) ;
	int iRwdItemCorrect = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Correct"), _T("RwdGold"), _T("100"), szInBuf, 10, szFileName ) ;
	int iRwdGoldCorrect = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Correct"), _T("RwdBraman"), _T("100"), szInBuf, 10, szFileName ) ;
	int iRwdBramanCorrect = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("VisualRange"), _T("HalfGrid"), _T("32"), szInBuf, 10, szFileName ) ;
	int iHalfGrid = atoi( szInBuf ) ;
	if( 0 < iHalfGrid )
	{		
		g_iHalfGridX = g_iHalfGridY = iHalfGrid ;
		g_iViewGridX = g_iViewGridY = iHalfGrid + iHalfGrid + 1 ;
	}

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("Log"), _T("MonsterLevel"), _T("60"), szInBuf, 10, szFileName ) ;
	g_iMonsterLevelForWritingLog = atoi( szInBuf ) ;
	if( 0 >= g_iMonsterLevelForWritingLog ) g_iMonsterLevelForWritingLog = 60 ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("GiftItem"), _T("ItemIndex"), _T("0"), szInBuf, 10, szFileName ) ;
	int nItemIndex = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("GiftItem"), _T("ItemCount"), _T("0"), szInBuf, 10, szFileName ) ;
	int nItemCount = atoi( szInBuf ) ;

	memset( szInBuf, 0, 20 ) ;
	GetPrivateProfileString( _T("GiftItem"), _T("ItemGenTime"), _T("0"), szInBuf, 10, szFileName ) ;
	int nItemGenTime = atoi( szInBuf ) ;

	g_nItemCashType = GetPrivateProfileInt( _T("ItemCash"), _T("CashType"), 0, szFileName );

	g_dRwdBramanCorrect = iRwdBramanCorrect ;
	g_dRwdPranaCorrect = iRwdPranaCorrect ;
	g_dRwdGoldCorrect = iRwdGoldCorrect ;
	g_dRwdItemCorrect = iRwdItemCorrect ;
	g_nGiftItemIndex = nItemIndex;
	g_nGiftItemMaxCount = nItemCount;
	g_nGiftItemCount = g_nGiftItemMaxCount;
	g_nGiftItemFirstCount = g_nGiftItemMaxCount; 
	g_snGiftItemGenTime = nItemGenTime;

	if( 0 >= g_dRwdBramanCorrect ) g_dRwdBramanCorrect = 100 ;
	if( 0 >= g_dRwdPranaCorrect ) g_dRwdPranaCorrect = 100 ;
	if( 0 >= g_dRwdGoldCorrect ) g_dRwdGoldCorrect = 100 ;
	if( 0 >= g_dRwdItemCorrect ) g_dRwdItemCorrect = 100 ;
	if( g_nGiftItemMaxCount < 0) g_snGiftItemGenTime = 0;
	if( g_snGiftItemGenTime < 0 ) g_snGiftItemGenTime = 0;
	g_snGiftItemGenTime *= (1000/TICKSIZE);
	if(g_snGiftItemGenTime>0)
	{	ZeroMemory(&GiftItem, sizeof(GiftItem));
		
		bool bRet = true; short sMaxDur = 0;
		bRet &= g_ParamMgr.HT_bGetItemMaxDurability	(g_nGiftItemIndex, &sMaxDur);
		if(bRet)
		{	GiftItem.snIndex = g_nGiftItemIndex - HT_PARAMTYPE_ITEM_START + 1 ;
			GiftItem.snDurability = sMaxDur ;
			GiftItem.byCount = 1 ; 
			GiftItem.byRefineLevel = 0 ;
			for( int i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i ) GiftItem.bySubRefine[i] = 0 ;
		}	else
		{	g_snGiftItemGenTime = 0;
		}
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[Load Settings.ini] ZoneID:%d, WorldID:%d, ViewGrid(%d,%d), HalfGrid(%d,%d), PranaCorrect:%f, GoldCorrect:%f, BramanCorrect:%f \r\n\r\n", g_iZoneID, g_iWorldID, g_iViewGridX, g_iViewGridY, g_iHalfGridX, g_iHalfGridY, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" ) ;
	}

	g_dRwdBramanCorrect /= 100 ;
	g_dRwdPranaCorrect /= 100 ;
	g_dRwdGoldCorrect /= 100 ;
	g_dRwdItemCorrect /= 100 ;

	sprintf(szFileName, ".\\Data\\Zone%d.ini", g_iZoneID);
	GetPrivateProfileString( _T("Arena"), _T("Money"), _T("0"), szInBuf, 15, szFileName );
	g_dwArenaMoney = atoi( szInBuf ) ;

	GetPrivateProfileString( _T("Castle"), _T("SalesRate"), _T("0"), szInBuf, 15, szFileName );
	g_byCastleSalesRate = atoi( szInBuf ) ;

	GetPrivateProfileString( _T("Castle"), _T("SalesMoney"), _T("0"), szInBuf, 15, szFileName );
	g_dwCastleSalesMoney = atoi( szInBuf ) ;

	GetPrivateProfileString( _T("Castle"), _T("EraseDay"), _T("0"), szInBuf, 15, szFileName );
	g_dwRentalEraseDay = atoi( szInBuf ) ;

	GetPrivateProfileString( _T("Castle"), _T("RentalTex"), _T("0"), szInBuf, 15, szFileName );
	g_dwRentalTex = atoi( szInBuf ) ;

	GetPrivateProfileString( _T("Castle"), _T("RentalTexMoney"), _T("0"), szInBuf, 15, szFileName );
	g_dwRentalTexMoney = atoi( szInBuf ) ;
}
/*
void LoadSettingsData()
{
	FILE * fp = fopen("Settings.dat","rb");
	if( NULL == fp )	
	{	
		LoadSettings() ;
	}
	else
	{
		fread( g_irgLevelUp, sizeof(g_irgLevelUp), 1, fp ) ;
		fread( g_krgCoefficientByClass, sizeof(g_krgCoefficientByClass), 1, fp ) ;
		fread( g_srgItemGroup, sizeof(g_srgItemGroup), 1, fp ) ;
		fread( g_krgEffectTolerance, sizeof(g_krgEffectTolerance), 1, fp ) ;
		fread( g_krgItemRateByMonLevel, sizeof(g_krgItemRateByMonLevel), 1, fp ) ;
		fread( g_krgItemByLevel, sizeof(g_krgItemByLevel), 1, fp ) ;
		fread( g_krgConsider, sizeof(g_krgConsider), 1, fp ) ;
		fread( g_krgJudgeCombat, sizeof(g_krgJudgeCombat), 1, fp ) ;
		fread( g_pRvRZoneList, sizeof(g_pRvRZoneList), 1, fp ) ;
		fread( g_srgAttackTypeVSArmorTypeChart, sizeof(g_srgAttackTypeVSArmorTypeChart), 1, fp ) ;
		fread( g_szrgComment, sizeof(g_szrgComment), 1, fp ) ;
		fread( g_krgSpeechContent, sizeof(g_krgSpeechContent), 1, fp ) ;
		fread( g_srgAIList, sizeof(g_srgAIList), 1, fp ) ;
		fread( g_krgActionList, sizeof(g_krgActionList), 1, fp ) ;
		fread( g_krgAction, sizeof(g_krgAction), 1, fp ) ;
		fread( g_srgTimeSchedule, sizeof(g_srgTimeSchedule), 1, fp ) ;
		fread( g_krgEventList, sizeof(g_krgEventList), 1, fp ) ;
		fread( g_krgTaskList, sizeof(g_krgTaskList), 1, fp ) ;
		fread( g_irgRvRPKConsider, sizeof(g_irgRvRPKConsider), 1, fp ) ;
		fread( g_krgAggrScore, sizeof(g_krgAggrScore), 1, fp ) ;
		fread( g_krgKalaAltar, sizeof(g_krgKalaAltar), 1, fp ) ;
		fread( g_krgKalaRewarderPosition, sizeof(g_krgKalaRewarderPosition), 1, fp ) ;
	}
}
*/


void LoadSpeechComment()
{
	FILE* fp ;
	fp = fopen( "EventTask.txt", "rt" ) ;
	if(NULL == fp )
	{
		assert( !"Can't open ./EventTask.txt file" ) ;
		exit(0) ;
	}

	char szLine[1024] = { 0,0,0, } ;
	while(1)
	{	char* szRes = fgets( (char*)szLine, 255, fp ) ;
		if( NULL == szRes ) break ;
	
		if( '/' != szLine[0] ) continue ;
	    
		char szID[8] = { 0,0,0, } ;
		char szArguments[512] = { 0,0,0, } ;
	    
		sscanf( szLine, "%s %s", szID, szArguments ) ;    
		int iCmmID = atoi( szID ) ;
		if( 0 < iCmmID && eTNSpch_MaxCommentCount > iCmmID )
		{
			memcpy( g_szrgComment[iCmmID], szArguments, sizeof(szArguments) ) ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- iCmmID:%d, szComment:%s \r\n", iCmmID, g_szrgComment[iCmmID] ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}	

	fclose( fp ) ;
}



void LoadEventTask()
{
	FILE* fp ;
	fp = fopen( "EventTask.txt", "rt" ) ;
	if(NULL == fp )
	{
		assert( !"Can't open ./EventTask.txt file" ) ;
		exit(0) ;
	}

	char szLine[1024] = { 0,0,0, } ;
	while(1)
	{	char* szRes = fgets( (char*)szLine, 255, fp ) ;
		if( NULL == szRes ) break ;
		
		ParseData( szLine ) ;		
	}	

	fclose( fp ) ;
}


void ParseData( char* a_pCmd )
{
    if( NULL == a_pCmd ) return ;
	if( '/' != a_pCmd[0] ) return ;
	//if( 0 == szCmd[0] ) return ;
    
    char szCmd[256] = { 0,0,0, } ;
	char szArguments[512] = { 0,0,0, } ;
	char szrgArgument[20][256] = { 0,0,0, } ;
	int irgArgument[20] = { 0,0,0, } ;
    
	sscanf( a_pCmd, "%s %s", szCmd, szArguments ) ;    

	if( !strcmp( szCmd, "/Event" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2], szrgArgument[3], szrgArgument[4]
			, szrgArgument[5], szrgArgument[6], szrgArgument[7], szrgArgument[8], szrgArgument[9]
			//, szrgArgument[10], szrgArgument[11], szrgArgument[12], szrgArgument[13], szrgArgument[14]
			//, szrgArgument[15], szrgArgument[16], szrgArgument[17], szrgArgument[18], szrgArgument[19]
			) ;

		irgArgument[0] = atoi( szrgArgument[0] ) ;
		irgArgument[1] = atoi( szrgArgument[1] ) ;
		irgArgument[2] = atoi( szrgArgument[2] ) ;
		irgArgument[3] = atoi( szrgArgument[3] ) ;
		irgArgument[4] = atoi( szrgArgument[4] ) ;
		irgArgument[5] = atoi( szrgArgument[5] ) ;
		irgArgument[6] = atoi( szrgArgument[6] ) ;
		irgArgument[7] = atoi( szrgArgument[7] ) ;
		irgArgument[8] = atoi( szrgArgument[8] ) ;
		irgArgument[9] = atoi( szrgArgument[9] ) ;
		//irgArgument[10] = atoi( szrgArgument[10] ) ;
		//irgArgument[11] = atoi( szrgArgument[11] ) ;
		//irgArgument[12] = atoi( szrgArgument[12] ) ;
		//irgArgument[13] = atoi( szrgArgument[13] ) ;
		//irgArgument[14] = atoi( szrgArgument[14] ) ;
		//irgArgument[15] = atoi( szrgArgument[15] ) ;
		//irgArgument[16] = atoi( szrgArgument[16] ) ;
		//irgArgument[17] = atoi( szrgArgument[17] ) ;
		//irgArgument[18] = atoi( szrgArgument[18] ) ;
		//irgArgument[19] = atoi( szrgArgument[19] ) ;

		int iEventID = irgArgument[0] ;
		if( 0 < iEventID && eEvent_MaxCount > iEventID )
		{
			g_krgEventList[iEventID].srgTask[0] = irgArgument[1] ;
			g_krgEventList[iEventID].srgTask[1] = irgArgument[2] ;
			g_krgEventList[iEventID].srgTask[2] = irgArgument[3] ;
			g_krgEventList[iEventID].srgTask[3] = irgArgument[4] ;
			g_krgEventList[iEventID].srgTask[4] = irgArgument[5] ;
			g_krgEventList[iEventID].uiCoolDownTime = irgArgument[6] ;
			g_krgEventList[iEventID].sCount = irgArgument[7] ;
			g_krgEventList[iEventID].sProceedType = irgArgument[8] ;
			g_krgEventList[iEventID].iDuration = irgArgument[9] ;
			g_krgEventList[iEventID].uiAvailableTime = 0 ;		
			g_krgEventList[iEventID].sClan = eEvntClan_All ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- EventID:%3d, \tiTask1:%3d, \tiTask2:%3d, \tiTask3:%3d, \tiTask4:%3d, \tiTask5:%3d, \tcool-down time:%d, count:%d, procdtype:%d, DurType:%d \r\n"
					, iEventID, g_krgEventList[iEventID].srgTask[0], g_krgEventList[iEventID].srgTask[1], g_krgEventList[iEventID].srgTask[2], g_krgEventList[iEventID].srgTask[3], g_krgEventList[iEventID].srgTask[4]
					, g_krgEventList[iEventID].uiCoolDownTime, g_krgEventList[iEventID].sCount, g_krgEventList[iEventID].sProceedType, g_krgEventList[iEventID].iDuration
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}
	else if( !strcmp( szCmd, "/Task" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2], szrgArgument[3], szrgArgument[4]
			, szrgArgument[5], szrgArgument[6], szrgArgument[7]
			) ;

		irgArgument[0] = atoi( szrgArgument[0] ) ;
		irgArgument[1] = atoi( szrgArgument[1] ) ;
		irgArgument[2] = atoi( szrgArgument[2] ) ;
		irgArgument[3] = atoi( szrgArgument[3] ) ;
		irgArgument[4] = atoi( szrgArgument[4] ) ;
		irgArgument[5] = atoi( szrgArgument[5] ) ;
		irgArgument[6] = atoi( szrgArgument[6] ) ;
		irgArgument[7] = atoi( szrgArgument[7] ) ;


		int iTaskID = irgArgument[0] ;
		if( 0 < iTaskID && eTask_MaxCount > iTaskID )
		{
			g_krgTaskList[iTaskID].iActionID = irgArgument[1] ;
			g_krgTaskList[iTaskID].irgParam[0] = irgArgument[2] ;
			g_krgTaskList[iTaskID].irgParam[1] = irgArgument[3] ;
			g_krgTaskList[iTaskID].irgParam[2] = irgArgument[4] ;
			g_krgTaskList[iTaskID].irgParam[3] = irgArgument[5] ;
			g_krgTaskList[iTaskID].irgParam[4] = irgArgument[6] ;
			g_krgTaskList[iTaskID].irgParam[5] = irgArgument[7] ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- TaskID:%3d, \tActionID:%3d, \tParam1:%3d, \tParam2:%3d, \tParam3:%3d, \tParam4:%3d, \tParam5:%3d, \tParam6:%3d \r\n"
					, iTaskID, g_krgTaskList[iTaskID].iActionID
					, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
					, g_krgTaskList[iTaskID].irgParam[3], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}
	else if( !strcmp( szCmd, "/Scheduler" ) )
	{
		sscanf( szArguments, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			, szrgArgument[0], szrgArgument[1], szrgArgument[2]
			) ;

		irgArgument[0] = atoi( szrgArgument[0] ) ;
		irgArgument[1] = atoi( szrgArgument[1] ) ;
		irgArgument[2] = atoi( szrgArgument[2] ) ;


		int iMin = irgArgument[0] ;
		int iSec = irgArgument[1] ;
		int iTimeEvent = irgArgument[2] ;

		if( 0 > iMin || 60 <= iMin ) return ;
		if( 0 > iSec || 56 < iSec ) return ;
		if( 0 > iTimeEvent || eEvent_MaxCount <= iTimeEvent )  return ;

		int iTimeSlot = (iMin*60 + iSec)/4 ;
		if( 0 <= iTimeSlot && eTS_MaxSlot > iTimeSlot )
		{
			if( 0 < g_srgTimeSchedule[iTimeSlot] ) // �ٸ� event�� ����� �Ǿ� �ִٸ�, ...
			{
				int iPrevSlot = iTimeSlot-1 ;
				if( 0 > iPrevSlot ) iPrevSlot = 0 ;
				if( 0 == g_srgTimeSchedule[iPrevSlot] )
				{
					g_srgTimeSchedule[iPrevSlot] = iTimeEvent ;
					iTimeSlot = iPrevSlot ;
				}
				else
				{
					int iCount = 0 ;
					while(0 < g_srgTimeSchedule[iTimeSlot])
					{
						if( eTS_MaxSlot < iCount ) break ;
						++iCount ;
						++iTimeSlot ;
						if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot = 0 ;
					}
					g_srgTimeSchedule[iTimeSlot] = iTimeEvent ;
				}
			}
			else g_srgTimeSchedule[iTimeSlot] = iTimeEvent ;

			g_srgTimeSchedule[iTimeSlot] = (short)iTimeEvent ;
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "time slot : %d, event : %d, min: %d, sec:%d \r\n", iTimeSlot, iTimeEvent, iMin, iSec ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}
}





void LoadSettings()
{
	SYSTEMTIME st ;
	GetLocalTime( &st ) ;
	char chBuf[256] = { 0,0,0, } ;
	sprintf( chBuf, "%d%d%d%d%d", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
	int iDate = atoi( chBuf ) ;
	iDate += st.wMilliseconds ;
	//srand( iDate ) ;
	
	WriteLog( "\r\n\n------------------------------------------------------------------------------\r\n", ".\\monster_log\\[Log]LoadSettings.txt" ) ;

	// Connect
	SQLHENV m_hEnv ;
	SQLHDBC m_hDbc ;
	SQLCHAR InCon[255] ;
	SQLCHAR OutCon[255] ;
	SQLRETURN rcode ;
	SQLSMALLINT cbOutCon ;

	SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv ) ;
	SQLSetEnvAttr( m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER ) ;
	SQLAllocHandle( SQL_HANDLE_DBC, m_hEnv, &m_hDbc ) ;
	wsprintf( (char*)InCon, "DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;", ".\\Data\\Settings.mdb" ) ;
	
	rcode = SQLDriverConnect( m_hDbc, 0, InCon, sizeof(InCon), OutCon, sizeof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT ) ;

	if( -1 == rcode )
	{
		assert( !"./Data/Settings.mdb ������ ������ �� �����ϴ�." ) ;
		exit(0) ;
	}

	int iIndex = 0 ;

	// Load LevelUp table 
	char szQuery[512] = { 0,0,0, } ;
	wsprintf( szQuery, "SELECT iLevel, iPrana FROM LevelUp" ) ;

	SQLINTEGER ILevel, IPrana ;
	int iLevel = 0, iPrana = 0  ;

	SQLHSTMT hStmt ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "[LoadSettings::Load LevelUp table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1, SQL_C_ULONG, &iLevel, sizeof(int), &ILevel ) ;
		SQLGetData( hStmt, 2, SQL_C_ULONG, &iPrana, sizeof(int), &IPrana ) ;

		g_irgLevelUp[iLevel-1] = iPrana ;

		{
			char chBuf[256] = { 0,0,0, } ;
			sprintf(chBuf, "\t- level:%3d, prana:%d\r\n", iLevel, g_irgLevelUp[iLevel-1] ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;

	// Load Coefficient by Class table 
	//char szQuery[512] = { 0,0,0, } ;
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iClassLevel, iSpecializedClass, iDagger, iSword, iAxe, iBlunt, iSpear, iStaff, iClaw, iBow, iThrowing, iBare, iHP, iTP, iRecvry, iAC, iResist, iAttackRate, iDodgeRate, iAttackSpeed, iCastSpeed, iDodgeSpeed, iShield, iTwoHandSword, iTwoHandAxe FROM CoefficientByClass" ) ;

	SQLINTEGER IClassLvl, ISpcClass, IDagger, ISword, ITwoHandSword, IAxe, ITwoHandAxe, IBlunt, ISpear, IStaff, IClaw, IBow, IThrowing, IBare, IShield, IHP, ITP, IRecvry, IAC, IResist, IAttackRate, IDodgeRate, IAttackSpeed, ICastSpeed, IDodgeSpeed ;
	int iDagger, iSword, iTwoHandSword, iAxe, iTwoHandAxe, iBlunt, iSpear, iStaff, iClaw, iBow, iThrowing, iBare, iShield, iHP, iTP, iRecvry, iAC, iResist, iAttackRate, iDodgeRate, iAttackSpeed, iCastSpeed, iDodgeSpeed ;
	int iClassLevel = 0, iSpecializedClass = 0 ;

	memset( g_krgCoefficientByClass, 0, sizeof(g_krgCoefficientByClass) ) ;

	//SQLHSTMT hStmt ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load coefficientByClass table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1, SQL_C_ULONG, &iClassLevel, sizeof(int), &IClassLvl ) ;
		SQLGetData( hStmt, 2, SQL_C_ULONG, &iSpecializedClass, sizeof(int), &ISpcClass ) ;
		SQLGetData( hStmt, 3, SQL_C_ULONG, &iDagger, sizeof(int), &IDagger ) ;
		SQLGetData( hStmt, 4, SQL_C_ULONG, &iSword, sizeof(int), &ISword ) ;
		SQLGetData( hStmt, 5, SQL_C_ULONG, &iAxe, sizeof(int), &IAxe ) ;
		SQLGetData( hStmt, 6, SQL_C_ULONG, &iBlunt, sizeof(int), &IBlunt ) ;
		SQLGetData( hStmt, 7, SQL_C_ULONG, &iSpear, sizeof(int), &ISpear ) ;
		SQLGetData( hStmt, 8, SQL_C_ULONG, &iStaff, sizeof(int), &IStaff ) ;
		SQLGetData( hStmt, 9, SQL_C_ULONG, &iClaw, sizeof(int), &IClaw ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &iBow, sizeof(int), &IBow ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &iThrowing, sizeof(int), &IThrowing ) ;
		SQLGetData( hStmt, 12, SQL_C_ULONG, &iBare, sizeof(int), &IBare ) ;
		SQLGetData( hStmt, 13, SQL_C_ULONG, &iHP, sizeof(int), &IHP ) ;
		SQLGetData( hStmt, 14, SQL_C_ULONG, &iTP, sizeof(int), &ITP ) ;
		SQLGetData( hStmt, 15, SQL_C_ULONG, &iRecvry, sizeof(int), &IRecvry ) ;
		SQLGetData( hStmt, 16, SQL_C_ULONG, &iAC, sizeof(int), &IAC ) ;
		SQLGetData( hStmt, 17, SQL_C_ULONG, &iResist, sizeof(int), &IResist ) ;
		SQLGetData( hStmt, 18, SQL_C_ULONG, &iAttackRate, sizeof(int), &IAttackRate ) ;
		SQLGetData( hStmt, 19, SQL_C_ULONG, &iDodgeRate, sizeof(int), &IDodgeRate ) ;
		SQLGetData( hStmt, 20, SQL_C_ULONG, &iAttackSpeed, sizeof(int), &IAttackSpeed ) ;
		SQLGetData( hStmt, 21, SQL_C_ULONG, &iCastSpeed, sizeof(int), &ICastSpeed ) ;
		SQLGetData( hStmt, 22, SQL_C_ULONG, &iDodgeSpeed, sizeof(int), &IDodgeSpeed ) ;
		SQLGetData( hStmt, 23, SQL_C_ULONG, &iShield, sizeof(int), &IShield ) ;
		SQLGetData( hStmt, 24, SQL_C_ULONG, &iTwoHandSword, sizeof(int), &ITwoHandSword ) ;
		SQLGetData( hStmt, 25, SQL_C_ULONG, &iTwoHandAxe, sizeof(int), &ITwoHandAxe ) ;

		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDagger = iDagger ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iSword = iSword ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTwoHandSword = iTwoHandSword ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAxe = iAxe ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTwoHandAxe = iTwoHandAxe ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBlunt = iBlunt ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iSpear = iSpear ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iStaff = iStaff ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iClaw = iClaw ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBow = iBow ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iThrowing = iThrowing ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBare = iBare ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iHP = iHP ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTP = iTP ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iRecvry = iRecvry ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAC = iAC ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iResist = iResist ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAttackRate = iAttackRate ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDodgeRate = iDodgeRate ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAttackSpeed = iAttackSpeed ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iCastSpeed = iCastSpeed ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDodgeSpeed = iDodgeSpeed ;
		g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iShield = iShield ;
		
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- iClassLvl:%d, iSpcClass:%d, Dagger:%2d, Sword:%2d, TwoHandSword:%2d, Axe:%2d, TwoHandAxe:%2d, Blunt:%2d, Spear:%2d, Staff:%2d, Claw:%2d, Bow:%2d, Throwing:%2d, Bare:%2d, Shield:%2d, HP:%2d, TP1:%2d, TP2:%2d, AC:%2d, Resist:%2d, AR:%2d, DR:%2d, AtkSpd:%2d, CstSpd:%2d, DgSpd:%2d \r\n"
				, iClassLevel, iSpecializedClass
				, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDagger, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iSword, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTwoHandSword, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAxe, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTwoHandAxe, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBlunt, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iSpear, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iStaff, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iClaw, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBow, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iThrowing, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iBare, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iShield
				, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iHP, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iTP, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iRecvry, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAC, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iResist, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAttackRate, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDodgeRate, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iAttackSpeed, g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iCastSpeed , g_krgCoefficientByClass[iClassLevel][iSpecializedClass].iDodgeSpeed
				) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;

	// Load ItemGroup table 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT byGroup, SitemID FROM ItemGroup" ) ;

	SQLINTEGER IItemGroup, IItemID ;
	int iItemGroup = 0, iItemID = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load ItemGroup table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	for( int i = 0 ; i < eRwd_ItemGroup ; ++i ) g_srgGroupItemCount[i] = 0 ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1, SQL_C_ULONG, &iItemGroup, sizeof(int), &IItemGroup ) ;
		SQLGetData( hStmt, 2, SQL_C_ULONG, &iItemID, sizeof(int), &IItemID ) ;

		g_srgItemGroup[iItemGroup][g_srgGroupItemCount[iItemGroup]] = (short)iItemID ;
		++g_srgGroupItemCount[iItemGroup] ;

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- Group:%2d, ItemID:%4d\r\n", iItemGroup, iItemID ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	for( int iItemGroup = 1 ; iItemGroup < eRwd_ItemGroup ; ++iItemGroup )
	{
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- Group:%2d, ItemCount:%2d \r\n", iItemGroup, g_srgGroupItemCount[iItemGroup] ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load EffectTolerance table 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iClass1, iClass2, iHold, iStun, iSleep, iBlind, iTerror, iTaunt, iSlowMove, iSlowAttack FROM EffectTolerance" ) ;

	SQLINTEGER IClass1, IClass2, IHold, IStun, ISleep, IBlind, ITerror, ITaunt, ISlowMove, ISlowAttack ;
	int iClass1, iClass2, iHold, iStun, iSleep, iBlind, iTerror, iTaunt, iSlowMove, iSlowAttack ;
	iClass1 = iClass2 = iHold = iStun = iSleep = iBlind = iTerror = iTaunt = iSlowMove = iSlowAttack = 0 ;	

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load EffectTolerance table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1, SQL_C_ULONG, &iClass1, sizeof(int), &IClass1 ) ;
		SQLGetData( hStmt, 2, SQL_C_ULONG, &iClass2, sizeof(int), &IClass2 ) ;
		SQLGetData( hStmt, 3, SQL_C_ULONG, &iHold, sizeof(int), &IHold ) ;
		SQLGetData( hStmt, 4, SQL_C_ULONG, &iStun, sizeof(int), &IStun ) ;
		SQLGetData( hStmt, 5, SQL_C_ULONG, &iSleep, sizeof(int), &ISleep ) ;
		SQLGetData( hStmt, 6, SQL_C_ULONG, &iBlind, sizeof(int), &IBlind ) ;
		SQLGetData( hStmt, 7, SQL_C_ULONG, &iTerror, sizeof(int), &ITerror ) ;
		SQLGetData( hStmt, 8, SQL_C_ULONG, &iTaunt, sizeof(int), &ITaunt ) ;
		SQLGetData( hStmt, 9, SQL_C_ULONG, &iSlowMove, sizeof(int), &ISlowMove ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &iSlowAttack, sizeof(int), &ISlowAttack ) ;

		g_krgEffectTolerance[iClass1][iClass2].iHold = iHold ;
		g_krgEffectTolerance[iClass1][iClass2].iStun = iStun ;
		g_krgEffectTolerance[iClass1][iClass2].iSleep = iSleep ;
		g_krgEffectTolerance[iClass1][iClass2].iBlind = iBlind ;
		g_krgEffectTolerance[iClass1][iClass2].iTerror = iTerror ;
		g_krgEffectTolerance[iClass1][iClass2].iTaunt = iTaunt ;
		g_krgEffectTolerance[iClass1][iClass2].iSlowMove = iSlowMove ;
		g_krgEffectTolerance[iClass1][iClass2].iSlowAttack = iSlowAttack ;
		
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- iClassLvl:%d, iSpcClass:%d, iHold:%2d, iStun:%2d, iSleep:%2d, iBlind:%2d, iTerror:%2d, iTaunt:%2d, iSlowMove:%2d, iSlowAttack:%2d \r\n"
				, iClass1, iClass2
				, g_krgEffectTolerance[iClass1][iClass2].iHold, g_krgEffectTolerance[iClass1][iClass2].iStun, g_krgEffectTolerance[iClass1][iClass2].iSleep, g_krgEffectTolerance[iClass1][iClass2].iBlind
				, g_krgEffectTolerance[iClass1][iClass2].iTerror, g_krgEffectTolerance[iClass1][iClass2].iTaunt, g_krgEffectTolerance[iClass1][iClass2].iSlowMove, g_krgEffectTolerance[iClass1][iClass2].iSlowAttack
				) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load ItemRateByMonLevel
	memset( szQuery, 0, sizeof(szQuery) ) ;
	if( 0 == g_iWorldID ) wsprintf( szQuery, "SELECT iMonLevel, iLvl1, iLvl2, iLvl3, iLvl4, iLvl5, iLvl6, iLvl7, iLvl8, iLvl9, iLvl10, iLvl11, iLvl12, iLvl13, iLvl14, iLvl15, iLvl16, iLvl17, iLvl18, iLvl19, iLvl20 FROM ItemRateByMonLevelForTestSrv" ) ;
	else wsprintf( szQuery, "SELECT iMonLevel, iLvl1, iLvl2, iLvl3, iLvl4, iLvl5, iLvl6, iLvl7, iLvl8, iLvl9, iLvl10, iLvl11, iLvl12, iLvl13, iLvl14, iLvl15, iLvl16, iLvl17, iLvl18, iLvl19, iLvl20 FROM ItemRateByMonLevel" ) ;

	SQLINTEGER IMobLevel, ILvl1, ILvl2, ILvl3, ILvl4, ILvl5, ILvl6, ILvl7, ILvl8, ILvl9, ILvl10, ILvl11, ILvl12, ILvl13, ILvl14, ILvl15, ILvl16, ILvl17, ILvl18, ILvl19, ILvl20 ;
	int iMobLevel = 0, irgLvl[eItm_MaxLevel] = { 0,0,0,} ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load ItemRateByMonLevel table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	//srand( timeGetTime() ) ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iMobLevel, sizeof(int), &IMobLevel ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &irgLvl[1], sizeof(int), &ILvl1 ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &irgLvl[2], sizeof(int), &ILvl2 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &irgLvl[3], sizeof(int), &ILvl3 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &irgLvl[4], sizeof(int), &ILvl4 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &irgLvl[5], sizeof(int), &ILvl5 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &irgLvl[6], sizeof(int), &ILvl6 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &irgLvl[7], sizeof(int), &ILvl7 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &irgLvl[8], sizeof(int), &ILvl8 ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &irgLvl[9], sizeof(int), &ILvl9 ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &irgLvl[10], sizeof(int), &ILvl10 ) ;
		SQLGetData( hStmt, 12, SQL_C_ULONG, &irgLvl[11], sizeof(int), &ILvl11 ) ;
		SQLGetData( hStmt, 13, SQL_C_ULONG, &irgLvl[12], sizeof(int), &ILvl12 ) ;
		SQLGetData( hStmt, 14, SQL_C_ULONG, &irgLvl[13], sizeof(int), &ILvl13 ) ;
		SQLGetData( hStmt, 15, SQL_C_ULONG, &irgLvl[14], sizeof(int), &ILvl14 ) ;
		SQLGetData( hStmt, 16, SQL_C_ULONG, &irgLvl[15], sizeof(int), &ILvl15 ) ;
		SQLGetData( hStmt, 17, SQL_C_ULONG, &irgLvl[16], sizeof(int), &ILvl16 ) ;
		SQLGetData( hStmt, 18, SQL_C_ULONG, &irgLvl[17], sizeof(int), &ILvl17 ) ;
		SQLGetData( hStmt, 19, SQL_C_ULONG, &irgLvl[18], sizeof(int), &ILvl18 ) ;
		SQLGetData( hStmt, 20, SQL_C_ULONG, &irgLvl[19], sizeof(int), &ILvl19 ) ;
		SQLGetData( hStmt, 21, SQL_C_ULONG, &irgLvl[20], sizeof(int), &ILvl20 ) ;

		//for( int i = 0 ; i < eItm_MaxLevel ; ++i ) g_srgRateByItemLevel[iMobLevel][i] = irgLvl[i] ;
		//--iMobLevel ;
		if( 0 >= iMobLevel || eMonster_MaxLevel <= iMobLevel ) continue ;
		//g_krgItemRateByMonLevel[iMobLevel].Init() ;
		for( int i = 1 ; i < eItm_MaxLevel ; ++i )
		{			
			g_krgItemRateByMonLevel[iMobLevel].AddCard( i, irgLvl[i] ) ; // 1���� ����,  1~11
		}
		
		//srand( rand() ) ;
		g_krgItemRateByMonLevel[iMobLevel].Shuffle() ;
		//g_krgItemRateByMonLevel[iMobLevel].Shuffle() ;

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- MonLevel:%2d, Lvl1:%4d, Lvl2:%4d, Lvl3:%4d, Lvl4:%4d, Lvl5:%4d, Lvl6:%4d, Lvl7:%4d, Lvl8:%4d, Lvl9:%4d, Lvl10:%4d, Lvl11:%4d, Lvl12:%4d, Lvl13:%4d, Lvl14:%4d, Lvl15:%4d, Lvl16:%4d, Lvl17:%4d, Lvl18:%4d, Lvl19:%4d, Lvl20:%4d \r\n"
				, iMobLevel, irgLvl[1], irgLvl[2], irgLvl[3], irgLvl[4], irgLvl[5], irgLvl[6], irgLvl[7], irgLvl[8], irgLvl[9], irgLvl[10], irgLvl[11], irgLvl[12], irgLvl[13], irgLvl[14], irgLvl[15], irgLvl[16], irgLvl[17], irgLvl[18], irgLvl[19], irgLvl[20] ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load RateByItemCategory 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iCategory, iRate FROM RateByItemCategory" ) ;

	SQLINTEGER IItemCategory, IRate ;
	int iItemCategory = 0, iRate = 0 ; ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load RateByItemCategory table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	//g_kRateByItemCategory.Init( 1000 ) ;
	//int iIndex = 0 ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iItemCategory, sizeof(int), &IItemCategory ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iRate, sizeof(int), &IRate ) ;

		//g_srgRateByItemCategory[iType] = iRate ;
		if( 0 > iItemCategory || eItm_MaxCategory <= iItemCategory ) continue ;
		g_kRateByItemCategory.AddCard( iItemCategory, iRate ) ;	// 0���� ����
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- iCategory:%3d, iRate:%3d \r\n", iItemCategory, iRate ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
		//++iIndex ;
	}

	//srand( rand() ) ;
	g_kRateByItemCategory.Shuffle() ;
	//g_kRateByItemCategory.Shuffle() ;

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load ItemByLevel table 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iCategory, iLvl1, iLvl2, iLvl3, iLvl4, iLvl5, iLvl6, iLvl7, iLvl8, iLvl9, iLvl10, iLvl11, iLvl12, iLvl13, iLvl14, iLvl15, iLvl16, iLvl17, iLvl18, iLvl19, iLvl20 FROM ItemByLevel" ) ;

	//SQLINTEGER IItemCategory ;
	//int iItemCategory = 0 ; //, irgLvl[eItm_MaxLevel] = { 0,0,0,} ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load ItemByLevel table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iItemCategory, sizeof(int), &IItemCategory ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &irgLvl[1], sizeof(int), &ILvl1 ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &irgLvl[2], sizeof(int), &ILvl2 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &irgLvl[3], sizeof(int), &ILvl3 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &irgLvl[4], sizeof(int), &ILvl4 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &irgLvl[5], sizeof(int), &ILvl5 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &irgLvl[6], sizeof(int), &ILvl6 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &irgLvl[7], sizeof(int), &ILvl7 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &irgLvl[8], sizeof(int), &ILvl8 ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &irgLvl[9], sizeof(int), &ILvl9 ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &irgLvl[10], sizeof(int), &ILvl10 ) ;
		SQLGetData( hStmt, 12, SQL_C_ULONG, &irgLvl[11], sizeof(int), &ILvl11 ) ;
		SQLGetData( hStmt, 13, SQL_C_ULONG, &irgLvl[12], sizeof(int), &ILvl12 ) ;
		SQLGetData( hStmt, 14, SQL_C_ULONG, &irgLvl[13], sizeof(int), &ILvl13 ) ;
		SQLGetData( hStmt, 15, SQL_C_ULONG, &irgLvl[14], sizeof(int), &ILvl14 ) ;
		SQLGetData( hStmt, 16, SQL_C_ULONG, &irgLvl[15], sizeof(int), &ILvl15 ) ;
		SQLGetData( hStmt, 17, SQL_C_ULONG, &irgLvl[16], sizeof(int), &ILvl16 ) ;
		SQLGetData( hStmt, 18, SQL_C_ULONG, &irgLvl[17], sizeof(int), &ILvl17 ) ;
		SQLGetData( hStmt, 19, SQL_C_ULONG, &irgLvl[18], sizeof(int), &ILvl18 ) ;
		SQLGetData( hStmt, 20, SQL_C_ULONG, &irgLvl[19], sizeof(int), &ILvl19 ) ;
		SQLGetData( hStmt, 21, SQL_C_ULONG, &irgLvl[20], sizeof(int), &ILvl20 ) ;

		//--iItemCategory ;
		if( 0 <= iItemCategory && eItm_MaxCategory > iItemCategory )
		{
			for( int i = 1 ; i < eItm_MaxLevel ; ++i )
			{
				if( HT_PARAMTYPE_ITEM_START > irgLvl[i] ) g_krgItemByLevel[iItemCategory][i].snIndex = 0 ;
				else g_krgItemByLevel[iItemCategory][i].snIndex = irgLvl[i] - HT_PARAMTYPE_ITEM_START + 1 ;
				g_krgItemByLevel[iItemCategory][i].snDurability = pItemData[g_krgItemByLevel[iItemCategory][i].snIndex].sMaxDur ;
				g_krgItemByLevel[iItemCategory][i].byCount = 1 ;
				g_krgItemByLevel[iItemCategory][i].byRefineLevel = 0 ;
				for( int j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j ) g_krgItemByLevel[iItemCategory][i].bySubRefine[j] =0 ;

				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "g_krgItemByLevel[%2d][%2d].snIndex: %3d, dur:%4d, count:%2d, refineLvl:%d \r\n", iItemCategory, i, g_krgItemByLevel[iItemCategory][i].snIndex, g_krgItemByLevel[iItemCategory][i].snDurability, g_krgItemByLevel[iItemCategory][i].byCount, 0 ) ; 
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadRwdItem8th.txt" ) ;
				}
			}

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- Category:%3d, Lvl1:%4d, Lvl2:%4d, Lvl3:%4d, Lvl4:%4d, Lvl5:%4d, Lvl6:%4d, Lvl7:%4d, Lvl8:%4d, Lvl9:%4d, Lvl10:%4d, Lvl11:%4d, Lvl12:%4d, Lvl13:%4d, Lvl14:%4d, Lvl15:%4d, Lvl16:%4d, Lvl17:%4d, Lvl18:%4d, Lvl19:%4d, Lvl20:%4d \r\n"
					, iItemCategory, irgLvl[1], irgLvl[2], irgLvl[3], irgLvl[4], irgLvl[5], irgLvl[6], irgLvl[7], irgLvl[8], irgLvl[9], irgLvl[10], irgLvl[11], irgLvl[12], irgLvl[13], irgLvl[14], irgLvl[15], irgLvl[16], irgLvl[17], irgLvl[18], irgLvl[19], irgLvl[20] ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load Consider table 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT dfPCvsPC, rsPCvsPC, dgPCvsPC, dfPCvsNPC, rsPCvsNPC, dgPCvsNPC, dfNPCvsPC, rsNPCvsPC, dgNPCvsPC, dfNPCvsNPC, rsNPCvsNPC, dgNPCvsNPC FROM Consider" ) ;

	SQLINTEGER dfPCvsPC, rsPCvsPC, dgPCvsPC, dfPCvsNPC, rsPCvsNPC, dgPCvsNPC, dfNPCvsPC, rsNPCvsPC, dgNPCvsPC, dfNPCvsNPC, rsNPCvsNPC, dgNPCvsNPC ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load Consider table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	memset( g_krgConsider, 0, sizeof(g_krgConsider) ) ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &g_krgConsider[0][0].irgVal[iIndex][eCon_DF], sizeof(int), &dfPCvsPC ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &g_krgConsider[0][0].irgVal[iIndex][eCon_RS], sizeof(int), &rsPCvsPC ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &g_krgConsider[0][0].irgVal[iIndex][eCon_DG], sizeof(int), &dgPCvsPC ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &g_krgConsider[0][1].irgVal[iIndex][eCon_DF], sizeof(int), &dfPCvsNPC ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &g_krgConsider[0][1].irgVal[iIndex][eCon_RS], sizeof(int), &rsPCvsNPC ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &g_krgConsider[0][1].irgVal[iIndex][eCon_DG], sizeof(int), &dgPCvsNPC ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &g_krgConsider[1][0].irgVal[iIndex][eCon_DF], sizeof(int), &dfNPCvsPC ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &g_krgConsider[1][0].irgVal[iIndex][eCon_RS], sizeof(int), &rsNPCvsPC ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &g_krgConsider[1][0].irgVal[iIndex][eCon_DG], sizeof(int), &dgNPCvsPC ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &g_krgConsider[1][1].irgVal[iIndex][eCon_DF], sizeof(int), &dfNPCvsNPC ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &g_krgConsider[1][1].irgVal[iIndex][eCon_RS], sizeof(int), &rsNPCvsNPC ) ;
		SQLGetData( hStmt, 12, SQL_C_ULONG, &g_krgConsider[1][1].irgVal[iIndex][eCon_DG], sizeof(int), &dgNPCvsNPC ) ;

		if( eCon_MaxGapCount <= iIndex ) continue ;

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t[Consider] iIndex:%d  \tPCvsPC(DF:%d  \tRS:%d  \tDG:%d) \tPCvsNPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsNPC(DF:%d \tRS:%d \tDG:%d) \r\n", iIndex
				, g_krgConsider[0][0].irgVal[iIndex][0], g_krgConsider[0][0].irgVal[iIndex][1], g_krgConsider[0][0].irgVal[iIndex][2]
				, g_krgConsider[0][1].irgVal[iIndex][0], g_krgConsider[0][1].irgVal[iIndex][1], g_krgConsider[0][1].irgVal[iIndex][2]
				, g_krgConsider[1][0].irgVal[iIndex][0], g_krgConsider[1][0].irgVal[iIndex][1], g_krgConsider[1][0].irgVal[iIndex][2]
				, g_krgConsider[1][1].irgVal[iIndex][0], g_krgConsider[1][1].irgVal[iIndex][1], g_krgConsider[1][1].irgVal[iIndex][2]
					) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}

		++iIndex ;
	}


	SQLFreeStmt( hStmt, SQL_DROP ) ;

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n" ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	int iConstant = 39 ;
	for( int iLevel = 0 ; iLevel < eCon_MaxGapCount ; ++iLevel )
	{
		g_krgConsider[0][0].irgVal[iLevel][0] = 0 ; // g_krgConsider[0][1].irgVal[iLevel][0] = g_krgConsider[1][0].irgVal[iLevel][0] = g_krgConsider[1][1].irgVal[iLevel][0] = 0 ;
		g_krgConsider[0][0].irgVal[iLevel][1] = 0 ; // g_krgConsider[0][1].irgVal[iLevel][1] = g_krgConsider[1][0].irgVal[iLevel][1] = g_krgConsider[1][1].irgVal[iLevel][1] = 0 ;
		g_krgConsider[0][0].irgVal[iLevel][2] = 0 ; // g_krgConsider[0][1].irgVal[iLevel][2] = g_krgConsider[1][0].irgVal[iLevel][2] = g_krgConsider[1][1].irgVal[iLevel][2] = 0 ;

		// PC VS PC
		g_krgConsider[0][0].irgVal[iLevel][0] = int((iLevel*iLevel)/6) ; // DF
		g_krgConsider[0][0].irgVal[iLevel][1] = int((iLevel*iLevel)/39) ; // RS
		g_krgConsider[0][0].irgVal[iLevel][2] = int((iLevel*iLevel)/13) ; // DG

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t[Consider] iLevel:%d  \tPCvsPC(DF:%d  \tRS:%d  \tDG:%d) \tPCvsNPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsNPC(DF:%d \tRS:%d \tDG:%d) \r\n", iLevel
				, g_krgConsider[0][0].irgVal[iLevel][0], g_krgConsider[0][0].irgVal[iLevel][1], g_krgConsider[0][0].irgVal[iLevel][2]
				, g_krgConsider[0][1].irgVal[iLevel][0], g_krgConsider[0][1].irgVal[iLevel][1], g_krgConsider[0][1].irgVal[iLevel][2]
				, g_krgConsider[1][0].irgVal[iLevel][0], g_krgConsider[1][0].irgVal[iLevel][1], g_krgConsider[1][0].irgVal[iLevel][2]
				, g_krgConsider[1][1].irgVal[iLevel][0], g_krgConsider[1][1].irgVal[iLevel][1], g_krgConsider[1][1].irgVal[iLevel][2]
					) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	// Load JudgeCombat table 
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, criticalPCvsPC, normalPCvsPC, missPCvsPC, criticalPCvsNPC, normalPCvsNPC, missPCvsNPC, criticalNPCvsPC, normalNPCvsPC, missNPCvsPC, criticalNPCvsNPC, normalNPCvsNPC, missNPCvsNPC FROM JudgeCombat2" ) ;

	SQLINTEGER IID, criticalPCvsPC, normalPCvsPC, missPCvsPC, criticalPCvsNPC, normalPCvsNPC, missPCvsNPC, criticalNPCvsPC, normalNPCvsPC, missNPCvsPC, criticalNPCvsNPC, normalNPCvsNPC, missNPCvsNPC ;
	int irgCard[12] = { 0,0,0, }, iID = 0 ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load JudgeCombat table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iID, sizeof(int), &IID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &irgCard[0], sizeof(int), &criticalPCvsPC ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &irgCard[1], sizeof(int), &normalPCvsPC ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &irgCard[2], sizeof(int), &missPCvsPC ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &irgCard[3], sizeof(int), &criticalPCvsNPC ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &irgCard[4], sizeof(int), &normalPCvsNPC ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &irgCard[5], sizeof(int), &missPCvsNPC ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &irgCard[6], sizeof(int), &criticalNPCvsPC ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &irgCard[7], sizeof(int), &normalNPCvsPC ) ;
		SQLGetData( hStmt, 10,  SQL_C_ULONG, &irgCard[8], sizeof(int), &missNPCvsPC ) ;
		SQLGetData( hStmt, 11,  SQL_C_ULONG, &irgCard[9], sizeof(int), &criticalNPCvsNPC ) ;
		SQLGetData( hStmt, 12,  SQL_C_ULONG, &irgCard[10], sizeof(int), &normalNPCvsNPC ) ;
		SQLGetData( hStmt, 13,  SQL_C_ULONG, &irgCard[11], sizeof(int), &missNPCvsNPC ) ;

		if( 0 <= iID && eCon_JudgeCombat > iID )
		{
			g_krgJudgeCombat[0][0].irgJudgeCombat[iID][0] = irgCard[0] ;
			g_krgJudgeCombat[0][0].irgJudgeCombat[iID][1] = irgCard[1] ;
			g_krgJudgeCombat[0][0].irgJudgeCombat[iID][2] = irgCard[2] ;

			g_krgJudgeCombat[0][1].irgJudgeCombat[iID][0] = irgCard[3] ;
			g_krgJudgeCombat[0][1].irgJudgeCombat[iID][1] = irgCard[4] ;
			g_krgJudgeCombat[0][1].irgJudgeCombat[iID][2] = irgCard[5] ;

			g_krgJudgeCombat[1][0].irgJudgeCombat[iID][0] = irgCard[6] ;
			g_krgJudgeCombat[1][0].irgJudgeCombat[iID][1] = irgCard[7] ;
			g_krgJudgeCombat[1][0].irgJudgeCombat[iID][2] = irgCard[8] ;

			g_krgJudgeCombat[1][1].irgJudgeCombat[iID][0] = irgCard[9] ;
			g_krgJudgeCombat[1][1].irgJudgeCombat[iID][1] = irgCard[10] ;
			g_krgJudgeCombat[1][1].irgJudgeCombat[iID][2] = irgCard[11] ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t[Card] iID:%d \t%2d %2d %2d \t%2d %2d %2d \t%2d %2d %2d \t%2d %2d %2d \r\n"
					, iID
					, g_krgJudgeCombat[0][0].irgJudgeCombat[iID][0], g_krgJudgeCombat[0][0].irgJudgeCombat[iID][1], g_krgJudgeCombat[0][0].irgJudgeCombat[iID][2]
					, g_krgJudgeCombat[0][1].irgJudgeCombat[iID][0], g_krgJudgeCombat[0][1].irgJudgeCombat[iID][1], g_krgJudgeCombat[0][1].irgJudgeCombat[iID][2]
					, g_krgJudgeCombat[1][0].irgJudgeCombat[iID][0], g_krgJudgeCombat[1][0].irgJudgeCombat[iID][1], g_krgJudgeCombat[1][0].irgJudgeCombat[iID][2]
					, g_krgJudgeCombat[1][1].irgJudgeCombat[iID][0], g_krgJudgeCombat[1][1].irgJudgeCombat[iID][1], g_krgJudgeCombat[1][1].irgJudgeCombat[iID][2]
				);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}


	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load RvRZoneList table 
	g_pRvRZoneList[0] = 10 ;
	g_pRvRZoneList[1] = 11 ;
	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "\t[RvRZoneList] 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d \r\n"
			, g_pRvRZoneList[0], g_pRvRZoneList[1], g_pRvRZoneList[2], g_pRvRZoneList[3], g_pRvRZoneList[4], g_pRvRZoneList[5], g_pRvRZoneList[6], g_pRvRZoneList[7], g_pRvRZoneList[8], g_pRvRZoneList[9] ) ;		
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

/*
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iZoneID FROM RvRZoneList" ) ;

	SQLINTEGER IZoneID ;
	int iZoneID = 0 ;
	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load RvRZoneList table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	
	for( int i = 0 ; i < eRvRZone_Count ; ++i )  g_pRvRZoneList[i] = 0 ; // �ʱ�ȭ
	iIndex = 0 ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iZoneID, sizeof(int), &IZoneID ) ;

		if( eRvRZone_Count == iIndex ) continue ;
		g_pRvRZoneList[iIndex] = iZoneID ;
		++iIndex ;
	}

	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "\t[RvRZoneList] 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d \r\n"
			, g_pRvRZoneList[0], g_pRvRZoneList[1], g_pRvRZoneList[2], g_pRvRZoneList[3], g_pRvRZoneList[4], g_pRvRZoneList[5], g_pRvRZoneList[6], g_pRvRZoneList[7], g_pRvRZoneList[8], g_pRvRZoneList[9] ) ;		
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;
*/

	// Load AttackType VS Armor Type Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iArmorType, iDagger, iSword, iTwoHandSword, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4, iAxe, iTwoHandAxe, iSpear, iBow, iClaw, iBlunt, iMagic FROM AttackTypeVSArmorType2" ) ;

	SQLINTEGER IArmorType, IAnimal, IDemon, IGolem, IUndead, IPlant, IInsect, IHumanoid1, IHumanoid2, IHumanoid3, IHumanoid4, IMagic ;
	int iArmorType, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4, iMagic ;
	//SQLINTEGER IArmorType, IDagger, ISword, ITwoHandSword, IAxe, ITwoHandAxe, ISpear, IBow, IClaw, IBlunt, IAnimal, IDemon, IGolem, IUndead, IPlant, IInsect, IHumanoid1, IHumanoid2, IHumanoid3, IHumanoid4 ;
	//int iArmorType, iDagger, iSword, iTwoHandSword, iAxe, iTwoHandAxe, iSpear, iBow, iClaw, iBlunt, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4 ;
	iArmorType = iDagger = iSword = iTwoHandSword = iAxe = iTwoHandAxe = iSpear = iBow = iClaw = iBlunt = iAnimal = iDemon = iGolem = iUndead = iPlant = iInsect = iHumanoid1 = iHumanoid2 = iHumanoid3 = iHumanoid4 = iMagic = 0 ;

	//wsprintf( szQuery, "SELECT iArmorType, iSlash, iPierce, iCrush, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4 FROM AttackTypeVSArmorType" ) ;

	//SQLINTEGER IArmorType, ISlash, IPierce, ICrush, IAnimal, IDemon, IGolem, IUndead, IPlant, IInsect, IHumanoid1, IHumanoid2, IHumanoid3, IHumanoid4 ;
	//int iArmorType, iSlash, iPierce, iCrush, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4 ;
	//iArmorType = iSlash = iPierce = iCrush = iAnimal = iDemon = iGolem = iUndead = iPlant = iInsect = iHumanoid1 = iHumanoid2 = iHumanoid3 = iHumanoid4 = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load AttackTypeVSArmorType table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Dagger] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Sword] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_TwoHandSword] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Animal] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Demon] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Golem] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Undead] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Plant] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Insect] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid1] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid2] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid3] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid4] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Axe] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_TwoHandAxe] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Spear] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Bow] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Claw] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Blunt] = 100 ;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Magic] = 100 ;

	/*
	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\t- ArmorType:%2d, Slash:%3d, Pierce:%3d, Crush:%3d, Animal:%3d, Demon:%3d, Golem:%3d, Undead:%3d, Plant:%3d, Insect:%3d, Humanoid(%3d,%3d,%3d,%3d) \r\n"
			,iArmorType, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Slash], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Pierce], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Crush]
			, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Animal], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Demon]
			, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Golem], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Undead]
			, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Plant], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Insect]
			, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid1], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid2]
			, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid3], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid4]
			) ;		
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}
	*/

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iArmorType, sizeof(int), &IArmorType ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iDagger, sizeof(int), &IDagger ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iSword, sizeof(int), &ISword ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iTwoHandSword, sizeof(int), &ITwoHandSword ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iAnimal, sizeof(int), &IAnimal ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iDemon, sizeof(int), &IDemon ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iGolem, sizeof(int), &IGolem ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iUndead, sizeof(int), &IUndead ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &iPlant, sizeof(int), &IPlant ) ;
		SQLGetData( hStmt, 10,  SQL_C_ULONG, &iInsect, sizeof(int), &IInsect ) ;
		SQLGetData( hStmt, 11,  SQL_C_ULONG, &iHumanoid1, sizeof(int), &IHumanoid1 ) ;
		SQLGetData( hStmt, 12,  SQL_C_ULONG, &iHumanoid2, sizeof(int), &IHumanoid2 ) ;
		SQLGetData( hStmt, 13,  SQL_C_ULONG, &iHumanoid3, sizeof(int), &IHumanoid3 ) ;
		SQLGetData( hStmt, 14,  SQL_C_ULONG, &iHumanoid4, sizeof(int), &IHumanoid4 ) ;
		SQLGetData( hStmt, 15,  SQL_C_ULONG, &iAxe, sizeof(int), &IAxe ) ;
		SQLGetData( hStmt, 16,  SQL_C_ULONG, &iTwoHandAxe, sizeof(int), &ITwoHandAxe ) ;
		SQLGetData( hStmt, 17,  SQL_C_ULONG, &iSpear, sizeof(int), &ISpear ) ;
		SQLGetData( hStmt, 18,  SQL_C_ULONG, &iBow, sizeof(int), &IBow ) ;
		SQLGetData( hStmt, 19,  SQL_C_ULONG, &iClaw, sizeof(int), &IClaw ) ;
		SQLGetData( hStmt, 20,  SQL_C_ULONG, &iBlunt, sizeof(int), &IBlunt ) ;
		SQLGetData( hStmt, 21,  SQL_C_ULONG, &iMagic, sizeof(int), &IMagic ) ;

		if( eAAC_ArmorTypeCount > iArmorType && 0 < iArmorType )
		{
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Dagger] = iDagger ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Sword] = iSword ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandSword] = iTwoHandSword ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Animal] = iAnimal ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Demon] = iDemon ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Golem] = iGolem ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Undead] = iUndead ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Plant] = iPlant ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Insect] = iInsect ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid1] = iHumanoid1 ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid2] = iHumanoid2 ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid3] = iHumanoid3 ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid4] = iHumanoid4 ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Axe] = iAxe ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandAxe] = iTwoHandAxe ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Spear] = iSpear ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Bow] = iBow ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Claw] = iClaw ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Blunt] = iBlunt ;
			g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Magic] = iMagic ;
		}

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t- ArmorType:%2d, Dagger:%3d, Sword:%3d, TwoHandSword:%3d, Axe:%3d, TwoHandAxe:%3d, Spear:%3d, Bow:%3d, Claw:%3d, Blunt:%3d, Magic:%3d, Animal:%3d, Demon:%3d, Golem:%3d, Undead:%3d, Plant:%3d, Insect:%3d, Humanoid(%3d,%3d,%3d,%3d) \r\n"
				,iArmorType
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Dagger], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Sword], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandSword]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Axe], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandAxe], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Spear]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Bow], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Claw], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Blunt], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Magic]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Animal], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Demon]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Golem], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Undead]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Plant], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Insect]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid1], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid2]
				, g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid3], g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid4]
				) ;		
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load Speech Comment Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, szComment FROM SpeechComment" ) ;

	SQLINTEGER ICmmID, IComment ;
	int iCmmID = 0 ;
	char szComment[100] = { 0,0,0, } ;


	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load Speech Comment table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}


	memset( g_szrgComment, 0, sizeof(g_szrgComment) ) ;

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iCmmID, sizeof(int), &ICmmID ) ;
		SQLGetData( hStmt, 2,  SQL_C_CHAR, szComment, sizeof(szComment), &IComment ) ;

		if( 0 < iCmmID && eTNSpch_MaxCommentCount > iCmmID )
		{
			memcpy( g_szrgComment[iCmmID], szComment, sizeof(szComment) ) ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- iCmmID:%d, szComment:%s \r\n", iCmmID, g_szrgComment[iCmmID] ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;

	// Load Speech Content Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iComment1, iComment2, iComment3, iComment4, iComment5, iType1, iType2, iType3, iType4, iType5 FROM SpeechContent" ) ;

	SQLINTEGER ISCID, IComment1, IComment2, IComment3, IComment4, IComment5, IType1, IType2, IType3, IType4, IType5 ;
	int iSCID, iComment1, iComment2, iComment3, iComment4, iComment5, iType1, iType2, iType3, iType4, iType5 ;
	iSCID = iComment1 = iComment2 = iComment3 = iComment4 = iComment5 = iType1 = iType2 = iType3 = iType4 = iType5 = 0 ;


	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load Speech Contente table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}



	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iSCID, sizeof(int), &ISCID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iComment1, sizeof(int), &IComment1 ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iComment2, sizeof(int), &IComment2 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iComment3, sizeof(int), &IComment3 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iComment4, sizeof(int), &IComment4 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iComment5, sizeof(int), &IComment5 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iType1, sizeof(int), &IType1 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iType2, sizeof(int), &IType2 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &iType3, sizeof(int), &IType3 ) ;
		SQLGetData( hStmt, 10, SQL_C_ULONG, &iType4, sizeof(int), &IType4 ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &iType5, sizeof(int), &IType5 ) ;


		if( 0 < iSCID && eTNSpch_MaxContentCount > iSCID )
		{
			g_krgSpeechContent[iSCID].srgComment[0] = iComment1 ;
			g_krgSpeechContent[iSCID].srgComment[1] = iComment2 ;
			g_krgSpeechContent[iSCID].srgComment[2] = iComment3 ;
			g_krgSpeechContent[iSCID].srgComment[3] = iComment4 ;
			g_krgSpeechContent[iSCID].srgComment[4] = iComment5 ;
			g_krgSpeechContent[iSCID].srgType[0] = iType1 ;
			g_krgSpeechContent[iSCID].srgType[1] = iType2 ;
			g_krgSpeechContent[iSCID].srgType[2] = iType3 ;
			g_krgSpeechContent[iSCID].srgType[3] = iType4 ;
			g_krgSpeechContent[iSCID].srgType[4] = iType5 ;


			if( 0 < g_krgSpeechContent[iSCID].srgComment[0] ) ++g_krgSpeechContent[iSCID].iCount ;
			if( 0 < g_krgSpeechContent[iSCID].srgComment[1] ) ++g_krgSpeechContent[iSCID].iCount ;
			if( 0 < g_krgSpeechContent[iSCID].srgComment[2] ) ++g_krgSpeechContent[iSCID].iCount ;
			if( 0 < g_krgSpeechContent[iSCID].srgComment[3] ) ++g_krgSpeechContent[iSCID].iCount ;
			if( 0 < g_krgSpeechContent[iSCID].srgComment[4] ) ++g_krgSpeechContent[iSCID].iCount ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- iSCID:%3d, \tComment(%3d,%3d,%3d,%3d,%3d), \tType(%3d,%3d,%3d,%3d,%3d), \tCount(�Ѱ���):%d \r\n"
					, iSCID
					, g_krgSpeechContent[iSCID].srgComment[0], g_krgSpeechContent[iSCID].srgComment[1], g_krgSpeechContent[iSCID].srgComment[2], g_krgSpeechContent[iSCID].srgComment[3], g_krgSpeechContent[iSCID].srgComment[4]
					, g_krgSpeechContent[iSCID].srgType[0], g_krgSpeechContent[iSCID].srgType[1], g_krgSpeechContent[iSCID].srgType[2], g_krgSpeechContent[iSCID].srgType[3], g_krgSpeechContent[iSCID].srgType[4]
					, g_krgSpeechContent[iSCID].iCount ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load AI List Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iRest, iMove, iStart, iArrive, iDetect, iHelp1, iLink1, iGuard1, iBeKilled1, iUnderAttack1, iAttack, iHit, iMiss, iBeHitted, iDodge, iTrace, iGiveUpToTrace, iKillEnemy, iHelp2, iLink2, iGuard2, iBeKilled2, iUnderAttack2, iCantTrace, iReturn, iFlee, iLead, iPop, iDialog1, iDialog2, iDialog3, iDialog4 FROM AIList" ) ;

	SQLINTEGER IAIID, IRest, IMove, IStart, IArrive, IDetect, IHelp1, ILink1, IGuard1, IBeKilled1, IUnderAttack1, IAttack, IHit, IMiss, IBeHitted, IDodge, ITrace, IGiveUpToTrace, IKillEnemy, IHelp2, ILink2, IGuard2, IBeKilled2, IUnderAttack2, ICantTrace, IReturn, IFlee, ILead, IPop, IDialog1, IDialog2, IDialog3, IDialog4 ;
	int iAIID, iRest, iMove, iStart, iArrive, iDetect, iHelp1, iLink1, iGuard1, iBeKilled1, iUnderAttack1, iAttack, iHit, iMiss, iBeHitted, iDodge, iTrace, iGiveUpToTrace, iKillEnemy, iHelp2, iLink2, iGuard2, iBeKilled2, iUnderAttack2, iCantTrace, iReturn, iFlee, iLead, iPop, iDialog1, iDialog2, iDialog3, iDialog4 ;
	iAIID = iRest = iMove = iStart = iArrive = iDetect = iHelp1 = iLink1 = iGuard1 = iBeKilled1 = iUnderAttack1 = iAttack = iHit = iMiss = iBeHitted = iDodge = iTrace = iGiveUpToTrace = iKillEnemy = iHelp2 = iLink2 = iGuard2 = iBeKilled2 = iUnderAttack2 = iCantTrace = iReturn = iFlee = iLead = iPop = iDialog1 = iDialog2 = iDialog3 = iDialog4 = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load AI List table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iAIID, sizeof(int), &IAIID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iRest, sizeof(int), &IRest ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iMove, sizeof(int), &IMove ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iStart, sizeof(int), &IStart ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iArrive, sizeof(int), &IArrive ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iDetect, sizeof(int), &IDetect ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iHelp1, sizeof(int), &IHelp1 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iLink1, sizeof(int), &ILink1 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &iGuard1, sizeof(int), &IGuard1 ) ;
		SQLGetData( hStmt, 10,  SQL_C_ULONG, &iBeKilled1, sizeof(int), &IBeKilled1 ) ;
		SQLGetData( hStmt, 11, SQL_C_ULONG, &iUnderAttack1, sizeof(int), &IUnderAttack1 ) ;
		SQLGetData( hStmt, 12, SQL_C_ULONG, &iAttack, sizeof(int), &IAttack ) ;
		SQLGetData( hStmt, 13, SQL_C_ULONG, &iHit, sizeof(int), &IHit ) ;
		SQLGetData( hStmt, 14, SQL_C_ULONG, &iMiss, sizeof(int), &IMiss ) ;
		SQLGetData( hStmt, 15, SQL_C_ULONG, &iBeHitted, sizeof(int), &IBeHitted ) ;
		SQLGetData( hStmt, 16, SQL_C_ULONG, &iDodge, sizeof(int), &IDodge ) ;
		SQLGetData( hStmt, 17, SQL_C_ULONG, &iTrace, sizeof(int), &ITrace ) ;
		SQLGetData( hStmt, 18, SQL_C_ULONG, &iGiveUpToTrace, sizeof(int), &IGiveUpToTrace ) ;
		SQLGetData( hStmt, 19, SQL_C_ULONG, &iKillEnemy, sizeof(int), &IKillEnemy ) ;
		SQLGetData( hStmt, 20, SQL_C_ULONG, &iHelp2, sizeof(int), &IHelp2 ) ;
		SQLGetData( hStmt, 21, SQL_C_ULONG, &iLink2, sizeof(int), &ILink2 ) ;
		SQLGetData( hStmt, 22, SQL_C_ULONG, &iGuard2, sizeof(int), &IGuard2 ) ;
		SQLGetData( hStmt, 23, SQL_C_ULONG, &iBeKilled2, sizeof(int), &IBeKilled2 ) ;
		SQLGetData( hStmt, 24, SQL_C_ULONG, &iUnderAttack2, sizeof(int), &IUnderAttack2 ) ;
		SQLGetData( hStmt, 25, SQL_C_ULONG, &iCantTrace, sizeof(int), &ICantTrace ) ;
		SQLGetData( hStmt, 26, SQL_C_ULONG, &iReturn, sizeof(int), &IReturn ) ;
		SQLGetData( hStmt, 27, SQL_C_ULONG, &iFlee, sizeof(int), &IFlee ) ;
		SQLGetData( hStmt, 28, SQL_C_ULONG, &iLead, sizeof(int), &ILead ) ;
		SQLGetData( hStmt, 29, SQL_C_ULONG, &iPop, sizeof(int), &IPop ) ;
		SQLGetData( hStmt, 30, SQL_C_ULONG, &iDialog1, sizeof(int), &IDialog1 ) ;
		SQLGetData( hStmt, 31, SQL_C_ULONG, &iDialog2, sizeof(int), &IDialog2 ) ;
		SQLGetData( hStmt, 32, SQL_C_ULONG, &iDialog3, sizeof(int), &IDialog3 ) ;
		SQLGetData( hStmt, 33, SQL_C_ULONG, &iDialog4, sizeof(int), &IDialog4 ) ;

		if( 0 < iAIID && eTNAI_MaxAICount > iAIID )
		{
			g_srgAIList[iAIID][eTNAI_Rest] = iRest ;
			g_srgAIList[iAIID][eTNAI_Move] = iMove ;
			g_srgAIList[iAIID][eTNAI_Start] = iStart ;
			g_srgAIList[iAIID][eTNAI_Arrive] = iArrive ;
			g_srgAIList[iAIID][eTNAI_Detect] = iDetect ;
			g_srgAIList[iAIID][eTNAI_Help1] = iHelp1 ;
			g_srgAIList[iAIID][eTNAI_Link1] = iLink1 ;
			g_srgAIList[iAIID][eTNAI_Guard1] = iGuard1 ;
			g_srgAIList[iAIID][eTNAI_BeKilled1] = iBeKilled1 ;
			g_srgAIList[iAIID][eTNAI_UnderAttack1] = iUnderAttack1 ;
			g_srgAIList[iAIID][eTNAI_Attack] = iAttack ;
			g_srgAIList[iAIID][eTNAI_HitEnemy] = iHit ;
			g_srgAIList[iAIID][eTNAI_Miss] = iMiss ;
			g_srgAIList[iAIID][eTNAI_BeHitted] = iBeHitted ;
			g_srgAIList[iAIID][eTNAI_Dodge] = iDodge ;
			g_srgAIList[iAIID][eTNAI_Trace] = iTrace ;
			g_srgAIList[iAIID][eTNAI_GiveUpToTrace] = iGiveUpToTrace ;
			g_srgAIList[iAIID][eTNAI_KillEnemy] = iKillEnemy ;
			g_srgAIList[iAIID][eTNAI_Help2] = iHelp2 ;
			g_srgAIList[iAIID][eTNAI_Link2] = iLink2 ;
			g_srgAIList[iAIID][eTNAI_Guard2] = iGuard2 ;
			g_srgAIList[iAIID][eTNAI_BeKilled2] = iBeKilled2 ;
			g_srgAIList[iAIID][eTNAI_UnderAttack2] = iUnderAttack2 ;
			g_srgAIList[iAIID][eTNAI_CantTrace] = iCantTrace ;
			g_srgAIList[iAIID][eTNAI_Return] = iReturn ;
			g_srgAIList[iAIID][eTNAI_Flee] = iFlee ;
			g_srgAIList[iAIID][eTNAI_Pop] = iPop ;
			g_srgAIList[iAIID][eTNAI_Lead] = iLead ;
			g_srgAIList[iAIID][eTNAI_Dialog1] = iDialog1 ;
			g_srgAIList[iAIID][eTNAI_Dialog2] = iDialog2 ;
			g_srgAIList[iAIID][eTNAI_Dialog3] = iDialog3 ;
			g_srgAIList[iAIID][eTNAI_Dialog4] = iDialog4 ;

			{
				char chBuf[512] = { 0,0,0, } ;

				sprintf(chBuf, "\t- AIID:%3d, Peace> Rest:%3d, Move:%3d, Start:%3d, Arrive:%3d, Detect:%3d, Help1:%3d, Link1:%3d, Guard1:%3d, BeKilled1:%3d, UnderAttack1:%3d, Dialog(%3d,%3d,%3d,%3d)\r\n\t\t Combat> Attack:%3d, Hit:%3d, Dodge:%3d, Trace:%3d, GiveUpToTrace:%3d, KillEnemy:%3d, Help2:%3d, Link2:%3d, Guard2:%3d, BeKilled2:%3d, UnderAttack2:%3d, CantTrace:%3d, Return:%3d, Flee:%3d, Pop:%3d \r\n"
					, iAIID, g_srgAIList[iAIID][eTNAI_Rest], g_srgAIList[iAIID][eTNAI_Move], g_srgAIList[iAIID][eTNAI_Start], g_srgAIList[iAIID][eTNAI_Arrive]
					, g_srgAIList[iAIID][eTNAI_Detect], g_srgAIList[iAIID][eTNAI_Help1], g_srgAIList[iAIID][eTNAI_Link1], g_srgAIList[iAIID][eTNAI_Guard1]
					, g_srgAIList[iAIID][eTNAI_BeKilled1], g_srgAIList[iAIID][eTNAI_UnderAttack1], g_srgAIList[iAIID][eTNAI_Attack], g_srgAIList[iAIID][eTNAI_HitEnemy]
					, g_srgAIList[iAIID][eTNAI_Miss], g_srgAIList[iAIID][eTNAI_BeHitted], g_srgAIList[iAIID][eTNAI_Dodge], g_srgAIList[iAIID][eTNAI_Trace]
					, g_srgAIList[iAIID][eTNAI_GiveUpToTrace], g_srgAIList[iAIID][eTNAI_KillEnemy], g_srgAIList[iAIID][eTNAI_Help2], g_srgAIList[iAIID][eTNAI_Link2]
					, g_srgAIList[iAIID][eTNAI_Guard2], g_srgAIList[iAIID][eTNAI_BeKilled2], g_srgAIList[iAIID][eTNAI_UnderAttack2], g_srgAIList[iAIID][eTNAI_CantTrace]
					, g_srgAIList[iAIID][eTNAI_Return], g_srgAIList[iAIID][eTNAI_Flee], g_srgAIList[iAIID][eTNAI_Pop], g_srgAIList[iAIID][eTNAI_Lead]
					, g_srgAIList[iAIID][eTNAI_Dialog1], g_srgAIList[iAIID][eTNAI_Dialog2], g_srgAIList[iAIID][eTNAI_Dialog3], g_srgAIList[iAIID][eTNAI_Dialog4]
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load Action List Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iAction1, iAction2, iAction3 FROM ActionList" ) ;

	SQLINTEGER IALID, IAction1, IAction2, IAction3 ;
	int iALID, iAction1, iAction2, iAction3 ;
	iALID = iAction1 = iAction2 = iAction3 = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load Action List table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}


	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iALID, sizeof(int), &IALID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iAction1, sizeof(int), &IAction1 ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iAction2, sizeof(int), &IAction2 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iAction3, sizeof(int), &IAction3 ) ;

		if( 0 < iALID && eTNAI_MaxActionListCount > iALID )
		{
			g_krgActionList[iALID].iCount = 0 ;
			g_krgActionList[iALID].srgAction[0] = iAction1 ;
			g_krgActionList[iALID].srgAction[1] = iAction2 ;
			g_krgActionList[iALID].srgAction[2] = iAction3 ;

			if( 0 < g_krgActionList[iALID].srgAction[0] ) ++g_krgActionList[iALID].iCount ;
			if( 0 < g_krgActionList[iALID].srgAction[1] ) ++g_krgActionList[iALID].iCount ;
			if( 0 < g_krgActionList[iALID].srgAction[2] ) ++g_krgActionList[iALID].iCount ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- iALID:%3d, \tCount:%3d, \tAction[0]:%3d, \tAction[1]:%3d, \tAction[2]:%3d \r\n"
					, iALID, g_krgActionList[iALID].iCount, g_krgActionList[iALID].srgAction[0], g_krgActionList[iALID].srgAction[1], g_krgActionList[iALID].srgAction[2] ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load Action Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iSpeak, iGroup, iAction, iSkill, iState, iEvent FROM Action" ) ;

	SQLINTEGER IActionID, ISpeak, IGroup, IAction, ISkill, IState, IEvent ;
	int iActionID, iSpeak, iGroup, iAction, iSkill, iState, iEvent ;
	iActionID = iSpeak = iGroup = iAction = iSkill = iState = iEvent = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load Action table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iActionID, sizeof(int), &IActionID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iSpeak, sizeof(int), &ISpeak ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iGroup, sizeof(int), &IGroup ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iAction, sizeof(int), &IAction ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iSkill, sizeof(int), &ISkill ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iState, sizeof(int), &IState ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iEvent, sizeof(int), &IEvent ) ;

		if( 0 < iActionID && eTNAI_MaxActionCount > iActionID )
		{
			g_krgAction[iActionID].sSpeak = iSpeak ;
			g_krgAction[iActionID].sGroup = iGroup ;
			g_krgAction[iActionID].sAction = iAction ;
			g_krgAction[iActionID].sSkill = iSkill ;
			g_krgAction[iActionID].sState = iState ;
			g_krgAction[iActionID].sEvent = iEvent ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- ActionID:%3d, \tSpeak:%3d, \tGroup:%3d, \tAction:%3d, \tSkill:%3d, \tState:%3d, \tEvent:%3d \r\n"
					, iActionID, g_krgAction[iActionID].sSpeak, g_krgAction[iActionID].sGroup, g_krgAction[iActionID].sAction, g_krgAction[iActionID].sSkill, g_krgAction[iActionID].sState, g_krgAction[iActionID].sEvent
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load Time schedule table
	memset( g_srgTimeSchedule, 0, sizeof(g_srgTimeSchedule) ) ;
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iZone, iMin, iSec, iEvent FROM TimeSchedule" ) ;

	SQLINTEGER IZone, IMin, ISec, ITimeEvent ;
	int iZone, iMin, iSec, iTimeEvent ;
	iZone = iMin = iSec = iTimeEvent = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load TimeSchedule table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iZone, sizeof(int), &IZone ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iMin, sizeof(int), &IMin ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iSec, sizeof(int), &ISec ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iTimeEvent, sizeof(int), &ITimeEvent ) ;

		if( (0 != iZone) && (g_iZoneID != iZone) ) continue ;
		if( 0 > iMin || 60 <= iMin ) continue ;
		if( 0 > iSec || 56 < iSec ) continue ;
		if( 0 > iTimeEvent || eEvent_MaxCount <= iTimeEvent ) continue ;

		int iTimeSlot = (iMin*60 + iSec)/4 ;
		if( 0 <= iTimeSlot && eTS_MaxSlot > iTimeSlot )
		{
			if( 0 < g_srgTimeSchedule[iTimeSlot] ) // �ٸ� event�� ����� �Ǿ� �ִٸ�, ...
			{
				int iPrevSlot = iTimeSlot-1 ;
				if( 0 > iPrevSlot ) iPrevSlot = 0 ;
				if( 0 == g_srgTimeSchedule[iPrevSlot] )
				{
					g_srgTimeSchedule[iPrevSlot] = iTimeEvent ;
					iTimeSlot = iPrevSlot ;
				}
				else
				{
					int iCount = 0 ;
					while(0 < g_srgTimeSchedule[iTimeSlot])
					{
						if( eTS_MaxSlot < iCount ) break ;
						++iCount ;
						++iTimeSlot ;
						if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot = 0 ;
					}
					g_srgTimeSchedule[iTimeSlot] = iTimeEvent ;
				}
			}
			else g_srgTimeSchedule[iTimeSlot] = iTimeEvent ;

			g_srgTimeSchedule[iTimeSlot] = (short)iTimeEvent ;
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "time slot : %d, event : %d, min: %d, sec:%d, zoneID: %d \r\n", iTimeSlot, iTimeEvent, iMin, iSec, iZone ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load EventList Table
	memset( g_krgEventList, 0, sizeof(g_krgEventList) ) ;
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iZone, iID, iTask1, iTask2, iTask3, iTask4, iTask5, uiCoolDownTime, sCount, iProceedType, iDuration FROM EventList" ) ;

	SQLINTEGER IEventID, ITask1, ITask2, ITask3, ITask4, ITask5, ICoolDownTime, ICount, IProceedType, IDuration ;
	int iEventID, iTask1, iTask2, iTask3, iTask4, iTask5, iCoolDownTime, iCount, iProceedType, iDuration ;
	iZone = iEventID = iTask1 = iTask2 = iTask3 = iTask4 = iTask5 = iCoolDownTime = iCount = iProceedType = iDuration = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load EventList table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iZone, sizeof(int), &IZone ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iEventID, sizeof(int), &IEventID ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iTask1, sizeof(int), &ITask1 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iTask2, sizeof(int), &ITask2 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iTask3, sizeof(int), &ITask3 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iTask4, sizeof(int), &ITask4 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iTask5, sizeof(int), &ITask5 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iCoolDownTime, sizeof(int), &ICoolDownTime ) ;
		SQLGetData( hStmt, 9,  SQL_C_SLONG, &iCount, sizeof(int), &ICount ) ;
		SQLGetData( hStmt, 10,  SQL_C_SLONG, &iProceedType, sizeof(int), &IProceedType ) ;
		SQLGetData( hStmt, 11,  SQL_C_SLONG, &iDuration, sizeof(int), &IDuration ) ;

		if( (0 != iZone) && (g_iZoneID != iZone) ) continue ;
		if( 0 < iEventID && eEvent_MaxCount > iEventID )
		{
			g_krgEventList[iEventID].srgTask[0] = iTask1 ;
			g_krgEventList[iEventID].srgTask[1] = iTask2 ;
			g_krgEventList[iEventID].srgTask[2] = iTask3 ;
			g_krgEventList[iEventID].srgTask[3] = iTask4 ;
			g_krgEventList[iEventID].srgTask[4] = iTask5 ;
			g_krgEventList[iEventID].uiCoolDownTime = iCoolDownTime ;
			g_krgEventList[iEventID].sCount = iCount ;
			g_krgEventList[iEventID].sProceedType = iProceedType ;
			g_krgEventList[iEventID].iDuration = iDuration ;
			g_krgEventList[iEventID].uiAvailableTime = 0 ;		
			g_krgEventList[iEventID].sClan = eEvntClan_All ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- EventID:%3d, \tiTask1:%3d, \tiTask2:%3d, \tiTask3:%3d, \tiTask4:%3d, \tiTask5:%3d, \tcool-down time:%d, count:%d, procdtype:%d, DurType:%d \r\n"
					, iEventID, g_krgEventList[iEventID].srgTask[0], g_krgEventList[iEventID].srgTask[1], g_krgEventList[iEventID].srgTask[2], g_krgEventList[iEventID].srgTask[3], g_krgEventList[iEventID].srgTask[4]
					, g_krgEventList[iEventID].uiCoolDownTime, g_krgEventList[iEventID].sCount, g_krgEventList[iEventID].sProceedType, g_krgEventList[iEventID].iDuration
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load TaskList Table
	memset( g_krgTaskList, 0, sizeof(g_krgTaskList) ) ;
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iZone, iID, iActionID, iParam1, iParam2, iParam3, iParam4, iParam5, iParam6 FROM TaskList" ) ;

	SQLINTEGER ITaskID, IActionID2, IParam1, IParam2, IParam3, IParam4, IParam5, IParam6 ;
	int iTaskID, iActionID2, iParam1, iParam2, iParam3, iParam4, iParam5, iParam6 ;
	iZone = iTaskID = iActionID2 = iParam1 = iParam2 = iParam3 = iParam4 = iParam5 = iParam6 = 0 ;


	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load TaskList table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iZone, sizeof(int), &IZone ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iTaskID, sizeof(int), &ITaskID ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iActionID2, sizeof(int), &IActionID2 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iParam1, sizeof(int), &IParam1 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iParam2, sizeof(int), &IParam2 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iParam3, sizeof(int), &IParam3 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iParam4, sizeof(int), &IParam4 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iParam5, sizeof(int), &IParam5 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &iParam6, sizeof(int), &IParam6 ) ;

		if( (0 != iZone) && (g_iZoneID != iZone) ) continue ;
		if( 0 < iTaskID && eTask_MaxCount > iTaskID )
		{
			g_krgTaskList[iTaskID].iActionID = iActionID2 ;
			g_krgTaskList[iTaskID].irgParam[0] = iParam1 ;
			g_krgTaskList[iTaskID].irgParam[1] = iParam2 ;
			g_krgTaskList[iTaskID].irgParam[2] = iParam3 ;
			g_krgTaskList[iTaskID].irgParam[3] = iParam4 ;
			g_krgTaskList[iTaskID].irgParam[4] = iParam5 ;
			g_krgTaskList[iTaskID].irgParam[5] = iParam6 ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- TaskID:%3d, \tActionID:%3d, \tParam1:%3d, \tParam2:%3d, \tParam3:%3d, \tParam4:%3d, \tParam5:%3d, \tParam6:%3d \r\n"
					, iTaskID, g_krgTaskList[iTaskID].iActionID
					, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
					, g_krgTaskList[iTaskID].irgParam[3], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load RvRPKConsider Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iDefenderCaste, iRewardBP, iAttackerCaste0, iAttackerCaste1, iAttackerCaste2, iAttackerCaste3, iAttackerCaste4, iAttackerCaste5, iAttackerCaste6, iAttackerCaste7, iAttackerCaste8, iAttackerCaste9, iAttackerCaste10, iAttackerCaste11, iAttackerCaste12, iAttackerCaste13, iAttackerCaste14, iAttackerCaste15, iAttackerCaste16, iAttackerCaste17  FROM RvRPKConsider" ) ;

	SQLINTEGER IDefenderCaste, IRewardBP, IAttackerCaste0, IAttackerCaste1, IAttackerCaste2, IAttackerCaste3, IAttackerCaste4, IAttackerCaste5, IAttackerCaste6, IAttackerCaste7, IAttackerCaste8, IAttackerCaste9, IAttackerCaste10, IAttackerCaste11, IAttackerCaste12, IAttackerCaste13, IAttackerCaste14, IAttackerCaste15, IAttackerCaste16, IAttackerCaste17 ;
	int iDefenderCaste, iRewardBP, iAttackerCaste0, iAttackerCaste1, iAttackerCaste2, iAttackerCaste3, iAttackerCaste4, iAttackerCaste5, iAttackerCaste6, iAttackerCaste7, iAttackerCaste8, iAttackerCaste9, iAttackerCaste10, iAttackerCaste11, iAttackerCaste12, iAttackerCaste13, iAttackerCaste14, iAttackerCaste15, iAttackerCaste16, iAttackerCaste17 ;
	iDefenderCaste = iRewardBP = iAttackerCaste0 = iAttackerCaste1 = iAttackerCaste2 = iAttackerCaste3 = iAttackerCaste4 = iAttackerCaste5 = iAttackerCaste6 = iAttackerCaste7 = iAttackerCaste8 = iAttackerCaste9 = iAttackerCaste10 = iAttackerCaste11 = iAttackerCaste12 = iAttackerCaste13 = iAttackerCaste14 = iAttackerCaste15 = iAttackerCaste16 = iAttackerCaste17 = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load RvRPKConsider table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iDefenderCaste, sizeof(int), &IDefenderCaste ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iRewardBP, sizeof(int), &IRewardBP ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iAttackerCaste0, sizeof(int), &IAttackerCaste0 ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iAttackerCaste1, sizeof(int), &IAttackerCaste1 ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iAttackerCaste2, sizeof(int), &IAttackerCaste2 ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iAttackerCaste3, sizeof(int), &IAttackerCaste3 ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iAttackerCaste4, sizeof(int), &IAttackerCaste4 ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iAttackerCaste5, sizeof(int), &IAttackerCaste5 ) ;
		SQLGetData( hStmt, 9,  SQL_C_ULONG, &iAttackerCaste6, sizeof(int), &IAttackerCaste6 ) ;
		SQLGetData( hStmt, 10,  SQL_C_ULONG, &iAttackerCaste7, sizeof(int), &IAttackerCaste7 ) ;
		SQLGetData( hStmt, 11,  SQL_C_ULONG, &iAttackerCaste8, sizeof(int), &IAttackerCaste8 ) ;
		SQLGetData( hStmt, 12,  SQL_C_ULONG, &iAttackerCaste9, sizeof(int), &IAttackerCaste9 ) ;
		SQLGetData( hStmt, 13,  SQL_C_ULONG, &iAttackerCaste10, sizeof(int), &IAttackerCaste10 ) ;
		SQLGetData( hStmt, 14,  SQL_C_ULONG, &iAttackerCaste11, sizeof(int), &IAttackerCaste11 ) ;
		SQLGetData( hStmt, 15,  SQL_C_ULONG, &iAttackerCaste12, sizeof(int), &IAttackerCaste12 ) ;
		SQLGetData( hStmt, 16,  SQL_C_ULONG, &iAttackerCaste13, sizeof(int), &IAttackerCaste13 ) ;
		SQLGetData( hStmt, 17,  SQL_C_ULONG, &iAttackerCaste14, sizeof(int), &IAttackerCaste14 ) ;
		SQLGetData( hStmt, 18,  SQL_C_ULONG, &iAttackerCaste15, sizeof(int), &IAttackerCaste15 ) ;
		SQLGetData( hStmt, 19,  SQL_C_ULONG, &iAttackerCaste16, sizeof(int), &IAttackerCaste16 ) ;
		SQLGetData( hStmt, 20,  SQL_C_ULONG, &iAttackerCaste17, sizeof(int), &IAttackerCaste17 ) ;

		if( 0 <= iDefenderCaste && 17 >= iDefenderCaste )
		{
			g_irgRvRPKConsider[iDefenderCaste][0] = iAttackerCaste0 ;
			g_irgRvRPKConsider[iDefenderCaste][1] = iAttackerCaste1 ;
			g_irgRvRPKConsider[iDefenderCaste][2] = iAttackerCaste2 ;
			g_irgRvRPKConsider[iDefenderCaste][3] = iAttackerCaste3 ;
			g_irgRvRPKConsider[iDefenderCaste][4] = iAttackerCaste4 ;
			g_irgRvRPKConsider[iDefenderCaste][5] = iAttackerCaste5 ;
			g_irgRvRPKConsider[iDefenderCaste][6] = iAttackerCaste6 ;
			g_irgRvRPKConsider[iDefenderCaste][7] = iAttackerCaste7 ;
			g_irgRvRPKConsider[iDefenderCaste][8] = iAttackerCaste8 ;
			g_irgRvRPKConsider[iDefenderCaste][9] = iAttackerCaste9 ;
			g_irgRvRPKConsider[iDefenderCaste][10] = iAttackerCaste10 ;
			g_irgRvRPKConsider[iDefenderCaste][11] = iAttackerCaste11 ;
			g_irgRvRPKConsider[iDefenderCaste][12] = iAttackerCaste12 ;
			g_irgRvRPKConsider[iDefenderCaste][13] = iAttackerCaste13 ;
			g_irgRvRPKConsider[iDefenderCaste][14] = iAttackerCaste14 ;
			g_irgRvRPKConsider[iDefenderCaste][15] = iAttackerCaste15 ;
			g_irgRvRPKConsider[iDefenderCaste][16] = iAttackerCaste16 ;
			g_irgRvRPKConsider[iDefenderCaste][17] = iAttackerCaste17 ;
			g_irgRewardBP[iDefenderCaste] = iRewardBP ;

			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- iDefenderCaste:%3d, \tRewardBP:%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d \r\n"
					, iDefenderCaste, g_irgRewardBP[iDefenderCaste]
					, g_irgRvRPKConsider[iDefenderCaste][0], g_irgRvRPKConsider[iDefenderCaste][1], g_irgRvRPKConsider[iDefenderCaste][2], g_irgRvRPKConsider[iDefenderCaste][3]
					, g_irgRvRPKConsider[iDefenderCaste][4], g_irgRvRPKConsider[iDefenderCaste][5], g_irgRvRPKConsider[iDefenderCaste][6], g_irgRvRPKConsider[iDefenderCaste][7]
					, g_irgRvRPKConsider[iDefenderCaste][8], g_irgRvRPKConsider[iDefenderCaste][9], g_irgRvRPKConsider[iDefenderCaste][10], g_irgRvRPKConsider[iDefenderCaste][11]
					, g_irgRvRPKConsider[iDefenderCaste][12], g_irgRvRPKConsider[iDefenderCaste][13], g_irgRvRPKConsider[iDefenderCaste][14], g_irgRvRPKConsider[iDefenderCaste][15]
					, g_irgRvRPKConsider[iDefenderCaste][16], g_irgRvRPKConsider[iDefenderCaste][17]
					) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load AggrScore Table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iPhysical, iFire, iCold, iLightning, iPoison, iHealing, iTaunt, iDetaunt FROM AggrScore" ) ;

	SQLINTEGER IPhysicalSC, IFireSC, IColdSC, ILightningSC, IPoisonSC, IHealingSC, ITauntSC, IDetauntSC ;
	int iPhysicalSC, iFireSC, iColdSC, iLightningSC, iPoisonSC, iHealingSC, iTauntSC, iDetauntSC ;
	iPhysicalSC = iFireSC = iColdSC = iLightningSC = iPoisonSC = iHealingSC = iTauntSC = iDetauntSC = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load AggrScore table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	int iAggrIndex = 0 ;
	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iPhysicalSC, sizeof(int), &IPhysicalSC ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iFireSC, sizeof(int), &IFireSC ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iColdSC, sizeof(int), &IColdSC ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iLightningSC, sizeof(int), &ILightningSC ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iPoisonSC, sizeof(int), &IPoisonSC ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iHealingSC, sizeof(int), &IHealingSC ) ;
		SQLGetData( hStmt, 7,  SQL_C_ULONG, &iTauntSC, sizeof(int), &ITauntSC ) ;
		SQLGetData( hStmt, 8,  SQL_C_ULONG, &iDetauntSC, sizeof(int), &IDetauntSC ) ;

		g_krgAggrScore[iAggrIndex].iPhysical = iPhysicalSC ;
		g_krgAggrScore[iAggrIndex].iFire = iFireSC ;
		g_krgAggrScore[iAggrIndex].iCold = iColdSC ;
		g_krgAggrScore[iAggrIndex].iLightning = iLightningSC ;
		g_krgAggrScore[iAggrIndex].iPoison = iPoisonSC ;
		g_krgAggrScore[iAggrIndex].iHealing = iHealingSC ;
		g_krgAggrScore[iAggrIndex].iTaunt = iTauntSC ;
		g_krgAggrScore[iAggrIndex].iDetaunt = iDetauntSC ;

		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "\t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d \r\n"
				, g_krgAggrScore[iAggrIndex].iPhysical, g_krgAggrScore[iAggrIndex].iFire
				, g_krgAggrScore[iAggrIndex].iCold, g_krgAggrScore[iAggrIndex].iLightning
				, g_krgAggrScore[iAggrIndex].iPoison, g_krgAggrScore[iAggrIndex].iHealing
				, g_krgAggrScore[iAggrIndex].iTaunt, g_krgAggrScore[iAggrIndex].iDetaunt
				) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}

		++iAggrIndex ;
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;


	// Load kala altar table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iZone, iClan, iX, iY FROM KalaAltar" ) ;

	SQLINTEGER IClan, IX, IY ;
	int iClan, iX, iY ;;
	iID = iZone = iClan = iX = iY = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load kala altar table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iID, sizeof(int), &IID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iZone, sizeof(int), &IZone ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iClan, sizeof(int), &IClan ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iX, sizeof(int), &IX ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iY, sizeof(int), &IY ) ;

		if( g_iZoneID != iZone ) continue ;

		if( 0 <= iID && eKalaAltar_MaxCount > iID )
		{
			g_krgKalaAltar[iID].sID = iID ;
			g_krgKalaAltar[iID].sTrimuriti = iClan ;
			g_krgKalaAltar[iID].x = iX ;
			g_krgKalaAltar[iID].y = iY ;

			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "ID:%d, clan:%d, L(%d,%d) \r\n", g_krgKalaAltar[iID].sID, g_krgKalaAltar[iID].sTrimuriti, g_krgKalaAltar[iID].x, g_krgKalaAltar[iID].y ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
		}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;



	// Load kala rewarder position table
	memset( szQuery, 0, sizeof(szQuery) ) ;
	wsprintf( szQuery, "SELECT iID, iZone, iNPCIndex, iClan, iX, iY FROM KalaRewarderPosition" ) ;

	SQLINTEGER INPCIndex ;
	int iNPCIndex ;
	iID = iZone = iNPCIndex = iClan = iX = iY = 0 ;

	SQLAllocHandle( SQL_HANDLE_STMT, m_hDbc, &hStmt ) ;
	rcode = SQLExecDirect( hStmt, (SQLCHAR*)szQuery, SQL_NTS ) ;

	if( -1 == rcode )
	{
	}

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n------------------------------------------------------------------------------\r\n[LoadSettings::Load kala rewarder position table] query: %s \r\n", szQuery ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
	}

	while( SQL_SUCCESS == SQLFetch( hStmt ) )
	{
		SQLGetData( hStmt, 1,  SQL_C_ULONG, &iID, sizeof(int), &IID ) ;
		SQLGetData( hStmt, 2,  SQL_C_ULONG, &iZone, sizeof(int), &IZone ) ;
		SQLGetData( hStmt, 3,  SQL_C_ULONG, &iNPCIndex, sizeof(int), &INPCIndex ) ;
		SQLGetData( hStmt, 4,  SQL_C_ULONG, &iClan, sizeof(int), &IClan ) ;
		SQLGetData( hStmt, 5,  SQL_C_ULONG, &iX, sizeof(int), &IX ) ;
		SQLGetData( hStmt, 6,  SQL_C_ULONG, &iY, sizeof(int), &IY ) ;

		if( g_iZoneID != iZone ) continue ;
		if( 0 <= iNPCIndex && eKalaRewarder_MaxCount >= iNPCIndex )
			if( 0 <= iClan && eTNClan_Siva >= iClan )
			{
				g_krgKalaRewarderPosition[iNPCIndex][iClan].x = iX ;
				g_krgKalaRewarderPosition[iNPCIndex][iClan].y = iY ;

				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "iNPCIndex:%d, clan:%d, L(%d,%d) \r\n", iNPCIndex, iClan, g_krgKalaRewarderPosition[iNPCIndex][iClan].x, g_krgKalaRewarderPosition[iNPCIndex][iClan].y ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings.txt" ) ;
			}
	}

	SQLFreeStmt( hStmt, SQL_DROP ) ;

	// Disconnect
	SQLDisconnect( m_hDbc ) ;
	SQLFreeConnect( m_hDbc ) ;
	SQLFreeEnv( m_hEnv ) ;

}



void LogRewardItems()
{
	for( int iMon = 101 ; iMon < 105 ; ++iMon )  // MAX_MONSTER_DATA
	{
		if( pMonsterData[iMon].snTribe != iMon + 2000 ) continue ;

		char szLogFile[40] ;
		sprintf( szLogFile, ".\\monster_log\\[Rwd]Monster_%d.txt", pMonsterData[iMon].snTribe ) ;

		int irgCount[eItm_MaxLevel] = { 0,0,0, } ;
		int irgErrCount[eItm_MaxLevel] = { 0,0,0, } ;
		int irgError[3] = { 0,0,0, } ;
		int iMobLevel = 0 ;
		for( int iKillCount = 0 ; iKillCount < 10000 ; ++iKillCount )
		{
			for( int i = 0 ; i < 8 ; ++i ) // 0~7��° items
			{
				if( 0 >= pMonsterData[iMon].Inven[i].snIndex ) continue ;
				if( g_krgRewardItemRate[iMon][i].Random() )
				{
					{
						char chBuf[256] = { 0,0,0, } ;
						sprintf(chBuf, "%dth item %d \r\n", i+1, pMonsterData[iMon].Inven[i].snIndex + 4000 ) ; 
						//WriteLog( chBuf, szLogFile ) ;
					}
				}
			}

			// 9��° reward-Item
			iMobLevel = pMonsterData[iMon].Inven[8].snIndex ;
			if( 0 < iMobLevel && eMonster_MaxLevel > iMobLevel )
			{
				//if( g_krgRewardItemRate[iMon][8].Random() )
				{
					int iItemLevel = g_krgItemRateByMonLevel[iMobLevel].Random() ;  // iItemLevel : 1~11
					int iItemCategory = g_kRateByItemCategory.Random() ; // iItemCategory : 0~n
					if( (0 < iItemLevel && eItm_MaxLevel > iItemLevel) && ( 0 <= iItemCategory && eItm_MaxCategory > iItemCategory) )
					{
						if( 0 < g_krgItemByLevel[iItemCategory][iItemLevel].snIndex && MAX_ITEM > g_krgItemByLevel[iItemCategory][iItemLevel].snIndex )
						{
							++irgCount[iItemLevel] ;
							char chBuf[256] = { 0,0,0, } ;
							sprintf(chBuf, "9th item %d \r\n", g_krgItemByLevel[iItemCategory][iItemLevel].snIndex + 4000 ) ; 
							//WriteLog( chBuf, szLogFile ) ;
						}			
						else
						{
							++irgErrCount[iItemLevel] ;
							++ irgError[2] ;
							{
								char chBuf[256] = { 0,0,0, } ;
								sprintf(chBuf, "Err> 9th item , iItemCategory:%d, iItemLevel:%d, itemIndex:%d \r\n", iItemCategory, iItemLevel, g_krgItemByLevel[iItemCategory][iItemLevel].snIndex ) ; 
								WriteLog( chBuf, szLogFile ) ;
							}
						}
					}
					else ++ irgError[1] ;
				}
			}
			else ++ irgError[0] ;

			// 10��° reward-Item
			if( 0 < pMonsterData[iMon].Inven[9].snIndex )
			{
				if( g_krgRewardItemRate[iMon][9].Random() )
				{
					int iGroup =  pMonsterData[iMon].Inven[9].snIndex ;
					if( 0 < iGroup && eRwd_ItemGroup > iGroup )
					{
						int iGroupItemCount = g_srgGroupItemCount[iGroup] ;
						if( 0 < iGroupItemCount && eRwd_ItemGroupCount >= iGroupItemCount )
						{
							int iDice = rand() % iGroupItemCount ;
							short sIndex = g_srgItemGroup[iGroup][iDice] - HT_PARAMTYPE_ITEM_START + 1 ;
							if( 0 < sIndex && MAX_ITEM_DATA > sIndex )
							{
								if( 0 < pItemData[sIndex].byLevel )
								{
									{
										char chBuf[256] = { 0,0,0, } ;
										sprintf(chBuf, "10th item %d \r\n", pItemData[sIndex].sID ) ; 
										//WriteLog( chBuf, szLogFile ) ;
									}
								}
							}
						}
					}
				}
			} // if( 0 < MOB.Inven[9].snIndex ) // 10��° reward-Item
		} // for( int iKillCount = 0 ; iKillCount < 10000 ; ++iKillCount )

		{
			char chBuf[512] = { 0,0,0, } ;
			int iSum = irgCount[1] + irgCount[2] + irgCount[3] + irgCount[4] + irgCount[5] + irgCount[6] + irgCount[7] + irgCount[8] + irgCount[9] + irgCount[10] + irgCount[11] ;
			sprintf(chBuf, "9th Item ���> MonsterID:%d, MonLvl:%d  ��������:%d, ��������������(%d+%d+%d) \r\n\t���¾����۰���> 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d, 11:%d \r\n\t���������������۰���> 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d, 10:%d, 11:%d"
				, iMon+2000, iMobLevel, iSum, irgError[0], irgError[1], irgError[2]
				, irgCount[1], irgCount[2], irgCount[3], irgCount[4], irgCount[5], irgCount[6], irgCount[7], irgCount[8], irgCount[9], irgCount[10], irgCount[11]
				, irgErrCount[1], irgErrCount[2], irgErrCount[3], irgErrCount[4], irgErrCount[5], irgErrCount[6], irgErrCount[7], irgErrCount[8], irgErrCount[9], irgErrCount[10], irgErrCount[11] ) ; 
			WriteLog( chBuf, szLogFile ) ;
		}
	}

	WriteLog( "��", ".\\monster_log\\[Rwd] 1��ȸ ���̱� ��.txt" ) ;
}



void RegisterMonstersToArea()
{
	int idx = 0 ;
	int iMonsterHandle = MAX_USER + 16 ; // 1000~1015������ Handle ���� monster���� ���� reserved �Ǿ� �ִ�. �׷��� �׻� ������ 10016���� �����Ѵ�.
	// handle�� ������Ű�� ������ �ٸ� instance�� ���� handle�� ����ϱ� ������, ���� handle ������ ����� �� ���� �������� �ִ�.
	// �̰��� kala, ������¡�� ���� ���� ���ȴ�. ��� ���� handle ������ ���������ȴ�.
	for( int i = 0 ; i <= mNPCGen.NumList ; ++i )
	{
		idx = i ; 
		for( int iCmd = 0 ; iCmd < eCmd_MaxCount ; ++iCmd )
		{
			if( eCmd_None == mNPCGen.pList[idx].krgCommand[iCmd].iCommand ) continue ;
			if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) )
			{
				int iIndex = mNPCGen.pList[idx].krgCommand[iCmd].iIndex ;
				for( int iPop = 0 ; iPop < mNPCGen.pList[idx].krgCommand[iCmd].iCount ; ++iPop )
				{
					if( mNPCGen.pList[idx].krgMonsterList[iIndex].iCurPopCount >= mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ) break ;
/*
					int mob = GetEmptyNPCMob();              
            		if  (mob==0)
            		{   sprintf(temp,"err no emptymob leader: %d",idx);
            			Log(temp,"-system",0);
            			{
            				char chBuf[256] = { 0,0,0, } ;
            				sprintf(chBuf, "[DeployMonsters] GetEmptyNPCMob()�� 0�� return -> ���̻� pMob[]�迭�� ������ ���ٴ� ����. Ȯ�ο���!\r\n" ) ;
            				WriteLog( chBuf, ".\\monster_log\\[Log]FailToPop.txt" ) ;
            			}
            			continue ;  // MobList�� �� á��.
            		}
*/

					for( int r = 0 ; r < mNPCGen.pList[idx].krgMonsterList[iIndex].iMaxPopCount ; ++r )
					{       
						if( 0 == mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][0] ) // ������ش�.
						{
							mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][0] = iMonsterHandle ;
							mNPCGen.pList[idx].krgMonsterList[iIndex].srgReadyMobList[r][1] = 1 ;
							pMob[iMonsterHandle].m_irgMobListIndex[0] = iIndex ;
							pMob[iMonsterHandle].m_irgMobListIndex[1] = r ;
							++iMonsterHandle ;
							break ;
						}			        
					}	            	          	            	
				} // for( int iPop = 0 ; iPop < mNPCGen.pList[idx].krgCommand[iCmd] ; ++iPop )
			} // end of if( (eCmd_PopMonster == mNPCGen.pList[idx].krgCommand[iCmd].iCommand) && bPopMonster )
		}
	}
	g_iFreeSlotForNPC = iMonsterHandle + 1 ;
}

/*
bool IsInRvR()
{
	int iZoneID = ServerIndex + 1 ;
	for( int i = 0 ; i < eRvRZone_Count ; ++i )
	{
		if( iZoneID == g_pRvRZoneList[i] )
		{
			g_bIsInRvR = true ;
			return true ;
		}
		if( 0 == g_pRvRZoneList[i] ) return false ;
	}
	
	return false ;
}
*/

void PrintMapInfo()
{
	HS2D_COORD kCenter, kBegin, kEnd ;

	int iWidth = 39 ;
	kCenter.x = 280 ;
	kCenter.y = 40 ;

	kBegin.x = kCenter.x - iWidth ;
	kBegin.y = kCenter.y - iWidth ;
	if( 0 > kBegin.x ) kBegin.x = 0 ;
	if( 0 > kBegin.y ) kBegin.y = 0 ;
	kEnd.x = kCenter.x + iWidth ;
	kEnd.y = kCenter.y + iWidth ;
	if( MAX_GRIDX <= kEnd.x ) kEnd.x = MAX_GRIDX -1;
	if( MAX_GRIDY <= kEnd.y ) kEnd.y = MAX_GRIDY -1 ;
	
	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\n\n[PrintMapInfo()] Center(%d,%d), Begin(%d,%d) ~ End(%d,%d)\r\n", kCenter.x, kCenter.y , kBegin.x, kBegin.y, kEnd.x, kEnd.y ) ;
		WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" ) ;
	}

	for( int y = kBegin.y ; y < kEnd.y ; ++y )
	{
		WriteLog( "\r\n", ".\\monster_log\\[Log]CheckMap.txt" ) ;
		for( int x = kBegin.x ; x < kEnd.x ; ++x )
		{
			char chCell = 'O' ;
			if( g_krgCell[y][x].usProperty & eTNCell_Blocked ) chCell = 'X' ;
			if( kCenter.x == x && kCenter.y == y ) chCell = 'K' ;

			{
				char chBuf[256] = { 0,0,0, } ;
				sprintf(chBuf, "%c", chCell ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" ) ;
			}
		}	

		if( kCenter.y == y )
		{
			char chBuf[256] = { 0,0,0, } ;
			sprintf(chBuf, "\t%d", y ) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]CheckMap.txt" ) ;
		}
	}
}


// called by OnKilled() only.
// ��Ƽ������ ���󳪸� �й��Ѵ�.
void SharePrana( int a_iParty, int a_iPrana, int a_iCorpse )
{
	if( 0 >= a_iParty || MAX_USER <= a_iParty ) return ; // iParty�� PC�� ��쿡�� Prana�й�
	if( MAX_USER > a_iCorpse || MAX_MOB <= a_iCorpse ) return ;
	if( 0 >= a_iPrana ) return ;

	int nParty[MAX_PARTY+1]={0,0,0,};
	int fol=0;	int nNumParty=0;	int leader=0;	int nLevel=0;
	int nMaxLevel=0; int nMinLevel=500;
	leader = a_iParty ;

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
	if(nNumParty==0 || nLevel==0) return;		//	�Ƶ���Ƽ�� ������� ��ó�� �������.
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

	if(nNumParty == 1)		//	��Ƽ���� �ƴҰ��
	{
		int fol = nParty[0];
		if	(fol<=0||fol>=MAX_USER) return;

		nGetPrana = a_iPrana*nRatio/100;
		int nMaxPrana = 10+10*(pMob[fol].MOB.byLevel)*(pMob[fol].MOB.byLevel+1)/2;
		nMaxPrana = (int)(nMaxPrana * g_dRwdPranaCorrect) ;
		if(nGetPrana > nMaxPrana) nGetPrana=nMaxPrana;

		nGetPrana *= (pMob[fol].m_dGetPranaRate/100);

		pMob[fol].AcquirePrana( nGetPrana, true ) ; // ���� ���ʽ��� �����Ѵ�.
		QUEST_OnEvent( a_iParty, pMob[a_iCorpse].MOB.snTribe, pMob[a_iCorpse].MOB.snTribe, 0 );
	}
	else					//	��Ƽ���� ���
	{	int nMaxPrana=0;
		int nPartyPrana = 0;
		int nDiff = nMaxLevel-nMinLevel;

		if(nDiff>20)										//	�������̰� 20���� Ŭ���
		{	if(nRatio>100) 
				nPartyPrana = a_iPrana;
			else				
				nPartyPrana = a_iPrana*nRatio/100;
		}
		else												//	�������̰� 20������ ���
		{	nPartyPrana = a_iPrana*(nRatio+(nNumParty-1)*20)/100;
		}

		for (int i=0;i<nNumParty;i++)
		{   fol=nParty[i];
   	 		if	(fol<=0||fol>=MAX_USER) continue;
			if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-g_iViewGridX || tx>pMob[fol].TargetX+g_iViewGridX ||ty<pMob[fol].TargetY-g_iViewGridY || ty>pMob[fol].TargetY+g_iViewGridY) continue;
			else nGetPrana = nPartyPrana*pMob[fol].MOB.byLevel/nLevel;

			QUEST_OnEvent( fol, pMob[a_iCorpse].MOB.snTribe, pMob[a_iCorpse].MOB.snTribe, 0 );
			nMaxPrana = 10+10*(pMob[fol].MOB.byLevel)*(pMob[fol].MOB.byLevel-1)/2;
			nMaxPrana = (int)(nMaxPrana * g_dRwdPranaCorrect) ;
			//nMaxPrana *= g_dRwdPranaCorrect;
			if(nGetPrana > nMaxPrana) nGetPrana=nMaxPrana;

			nGetPrana *= (pMob[fol].m_dGetPranaRate/100);
			pMob[fol].AcquirePrana( nGetPrana, true ) ; // ���� ���ʽ��� �����Ѵ�.
		}

		SendUpdateParty(a_iParty);
	}
}

void ShareBramanPoint( int a_iParty, int a_iBP, int a_iCorpse )
{
	if( 0 >= a_iParty || MAX_USER <= a_iParty ) return ; // iParty�� PC�� ��쿡�� BP�й�
	//if( MAX_USER <= a_iCorpse || MAX_MOB <= a_iCorpse ) return ; // ���� ��ü�� NPC�̸� return
	if( 0 >= a_iBP ) return ;


	int iLeader = pMob[a_iParty].Leader ;
	if( 0 >= iLeader ) iLeader = a_iParty ;

	int iPartyCount = 0 ;
	int tx = pMob[a_iCorpse].TargetX;
	int ty = pMob[a_iCorpse].TargetY;
	int fol = 0;
	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) fol = iLeader;
		else      fol = pMob[iLeader].m_irgParty[i-1];
   	 	if	(fol<=0||fol>=MAX_USER) continue;
		if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
		++iPartyCount ;
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

	if(iPartyCount==0) iPartyCount = 1;
	int iRewardBP = a_iBP / iPartyCount ;

	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) fol = iLeader;
		else      fol = pMob[iLeader].m_irgParty[i-1];
   	 	if	(fol<=0||fol>=MAX_USER) continue;
		if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-PRANAGRIDX || tx>pMob[fol].TargetX+PRANAGRIDX ||ty<pMob[fol].TargetY-PRANAGRIDY || ty>pMob[fol].TargetY+PRANAGRIDY) continue;
		pMob[fol].IncBP( iRewardBP ) ;
		pMob[fol].NotifyUpdateUIMsg() ;
	}
}

void ChangeRwdCorrect( int a_iPrana, int a_iGold, int a_iBP )
{
	if( 0 < a_iPrana )
	{
		g_dRwdPranaCorrect = a_iPrana ;
		g_dRwdPranaCorrect /= 100 ;
	}

	if( 0 < a_iGold )
	{
		g_dRwdGoldCorrect = a_iGold ;
		g_dRwdGoldCorrect /= 100 ;
	}

	if( 0 < a_iBP )
	{
		g_dRwdBramanCorrect = a_iBP ;
		g_dRwdBramanCorrect /= 100 ;
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
	SendGuildMessage(pUser[conn].nGuildIndex, (MSG_STANDARD*) &sm);				//	������������ ���� ���������� �˸���.

	if(!DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm)))					//	Ÿ������ ���� ���������� �˸���
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
	if( a_iMin == a_iMax ) return a_iMin ;

	if( a_iMin > a_iMax )
	{
		int iTemp = a_iMin ;
		a_iMin = a_iMax ;
		a_iMax = iTemp ; 
	}
	int iDice = 0 ;
	int iGap = 0 ;
	iGap = a_iMax - a_iMin ;
	++iGap ;

	if( 0 >= iGap )  iDice = a_iMin ;
	else iDice = a_iMin + ( rand() % iGap ) ;

	return iDice ;
}

//-------------------------------------------------------------------------
// CMob::�� member�� �� ������ teleport�� ������ �������� �ǹ��̴�.
//@Param
//	- a_iMob : teleport�� ��ų target
//	- a_iX, a_iY : teleport ��ų ��ġ
//-------------------------------------------------------------------------
void Teleport( int a_iMob, int a_iX, int a_iY )
{
	if( 0 >= a_iMob || MAX_MOB <= a_iMob ) return ;
	//int tret = GetEmptyMobGrid( a_iMob, &a_iX, &a_iY ) ; // Old version
	int tret = PickFreeMobGrid( a_iMob, &a_iX, &a_iY ) ;
	if( FALSE == tret ) return ;
	if( pMob[a_iMob].m_iBlockedCell & g_krgCell[a_iY][a_iX].usProperty ) return ;

	pMob[a_iMob].KillMobSummoned( eTNCls2_Retainer );//KillRetainer() ;

	MSG_Action sm;
	GetAction(a_iMob,a_iX,a_iY,&sm);
	sm.Effect = 5 ;
	if( a_iMob < MAX_USER ) 
	{
		pUser[a_iMob].nPreX = a_iX; pUser[a_iMob].nPreY = a_iY;
		pUser[a_iMob].cSock.AddMessage( (char*)&sm, sizeof(sm) ) ;
	}

	GridMulticast(a_iMob,a_iX,a_iY,(MSG_STANDARD*)&sm,100,ACTION_WARP);

	/*
	// �ڽ��� ������ �̵��� ������ �ִ� ������ �ֵ����� �ѷ��ش�.
	S_SCP_INIT_OTHER_MOB m;
	GetCreateMob( a_iMob, &m);
	GridMulticast(a_iX, a_iY, (MSG_STANDARD*)&m, a_iMob, 50 ) ;
	*/

	pMob[a_iMob].LastX = pMob[a_iMob].TargetX ;
	pMob[a_iMob].LastY = pMob[a_iMob].TargetY ;
	pMob[a_iMob].m_kLastTime.uiSelectTarget = 0 ;
}



void HelpGameMaster( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{
	if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return ;    
    if( NULL == a_pCmd ) return ;
    if( '/' != a_pCmd[0] ) return ;

	int iZoneID = ServerIndex + 1 ;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( a_bCheckGM && (eTNClan_GM != pMob[a_iHandle].m_byClan) && strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH)!=0 ) return ;
	#endif

    // ��� command�� log�� �����. �ð� + ���� + �޽���
    int iLength = strlen( a_pCmd ) ;
    if( g_iCmdMaxLength < iLength ) return ;
    
    char szCmd[128] = { 0,0,0, } ;
    char szArgument1[256] = { 0,0,0, } ;
    char szArgument2[256] = { 0,0,0, } ;
	char szArgument3[256] = { 0,0,0, } ;
	char szArgument4[256] = { 0,0,0, } ;
	char szArgument5[256] = { 0,0,0, } ;
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0 ;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5  ) ;   
	iArgument1	=atoi(szArgument1);
	iArgument2	=atoi(szArgument2);
	iArgument3	=atoi(szArgument3);
	iArgument4	=atoi(szArgument4);
	iArgument5	=atoi(szArgument5);

    if( '/' != szCmd[0] ) return ;

	S_SCP_RESP_WHISPER_CHAT kMsg ; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT ;	
	kMsg.byResult = REPLY_ACK_OK ;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH ) ;
	kMsg.byTextColor = 14 ; kMsg.byBgColor = 0 ; // ���߿� ���� ������ �ٲ۴�. ���� �� ���	
	    
    // g_iCmdMaxLength�� �ø� �� �ְ� �ϴ� command�� �ʿ��ϴ�.
    // ���� log ����ϴ� level�� ������ �� �ְ� �ؾ��Ѵ�.
    // �߿��� monster�� ���� �׿��� � reward�� ����� �׻� log�� ���ܾ��Ѵ�.(�̷� ���¿� �°� log ��ºκ� ����)
	SYSTEMTIME st ;
	GetLocalTime( &st ) ;
    
	#ifdef __TN_TOP_LOG__
	{
		if(strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH) != 0)
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "[%d��%d�� %d��%d��%d��] %s  %s \r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd ) ;
			WriteLog( chBuf, ".\\Log\\HelpGM.txt" ) ;
		}
	}
	#endif
  

    // switch/case ���� �׽�Ʈ �غ���.
	char szResult[1024] = { 0,0,0, } ;
	strncpy( szResult, a_pCmd, iLength ) ;

    if( !strcmp( szCmd, "/stat" ) || !strcmp( szCmd, "/����" ) )// ok
    {

		int iTarget = iArgument1; // mobile handle
		//int iTarget = GetMOBID( szArguments ) ;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
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
				) ;
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd ) ;   		    
		}        
    }
    else if( !strcmp( szCmd, "/ī��Ʈ" ) )// ok
    {
		int iCaste = iArgument1; // 

		pMob[a_iHandle].m_iCaste = iCaste ;

		pMob[a_iHandle].CalCasteSkillPoint() ;

		sprintf( szResult, "%s> User(%d)'s caste:%d, caste sp : %d"
			, a_pCmd, a_iHandle, pMob[a_iHandle].m_iCaste, pMob[a_iHandle].m_kCasteSPRemaining.get_Cur() ) ;
	}
	//	�ӽ��ڵ� �׽�Ʈ��
    else if( !strcmp( szCmd, "/�̺�Ʈ�ߵ�" ) )// ok
    {
		int iEvent = iArgument1; // 
		int iParam = iArgument2;
		DWORD dwFlag = 0x00000001;

		if(iEvent<1 || iEvent>8) return;
		dwFlag = dwFlag << (iEvent-1);
		SetGameEvent(a_iHandle, dwFlag & pUser[a_iHandle].m_dwEvent, &iParam);

		sprintf( szResult, "%s> User(%d)'s EVENT:%08X, caste flag : %d"
			, a_pCmd, a_iHandle, pUser[a_iHandle].m_dwEvent, dwFlag ) ;
	}
    else if( !strcmp( szCmd, "/stat2" ) )// ok
    {
		int iTarget = iArgument1 ; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
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
				) ;
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd ) ;   		    
		}        
    }
    else if( !strcmp( szCmd, "/stat3" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )	//	���������� ���� ����
		{
			pMob[iTarget].UpdateDamage( eTNEqu_OneHandWeapon ) ;
			pMob[iTarget].UpdateDamage( eTNEqu_Shield ) ;
			pMob[iTarget].UpdateEquipmentPoints() ;

			sprintf( szResult, "%s> Right-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d), Left-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d)"
				, a_pCmd
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Left].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPoison[0]
				) ;
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd ) ;   		    
		}        
    }
	else if( !strcmp( szCmd, "/refresh" ) || !strcmp( szCmd, "/�罺��" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{	
			pMob[iTarget].Init( iTarget ) ;
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
								
				) ;
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/mv" ) || !strcmp( szCmd, "/��" ) )// ok
	{
		int x = iArgument1, y = iArgument2 ;
		int tret = GetEmptyMobGrid( a_iHandle, &x, &y ) ;
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument1, iArgument2 ) ;
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return ;
		}

		MSG_Action sm ;
		GetAction( a_iHandle, x, y, &sm ) ;
		sm.Effect = 5 ;

		pUser[a_iHandle].nPreX = x; pUser[a_iHandle].nPreY = y;
		if( a_iHandle < MAX_USER ) pUser[a_iHandle].cSock.AddMessage( (char*)&sm, sizeof(sm) ) ;
		GridMulticast( a_iHandle, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP ) ;

/*
		// �ڽ��� ������ �̵��� ������ �ִ� ������ �ֵ����� �ѷ��ش�.
		S_SCP_INIT_OTHER_MOB m ;
		GetCreateMob( a_iHandle, &m ) ;
		GridMulticast( x, y, (MSG_STANDARD*)&m, a_iHandle, 20 ) ;
*/
	}
    else if( !strcmp( szCmd, "/movepc" ) || !strcmp( szCmd, "/��ȯ" ) )// ok
    {
		int iMobID = GetMOBID( szArgument1 ) ;
		int x = iArgument2, y = iArgument3 ;
		if(x==0 && y==0) 
		{ x = pMob[a_iHandle].TargetX; y = pMob[a_iHandle].TargetY; }

		int tret = GetEmptyMobGrid( iMobID, &x, &y ) ;
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 ) ;
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return ;
		}

		if( 0 < iMobID && MAX_USER > iMobID )	//	���������� ���� ����
		{	
			MSG_Action sm ;
			GetAction( iMobID, x, y, &sm ) ;
			sm.Effect = 5 ;
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) ) ;
			GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100,ACTION_WARP ) ;

			/*
			// �ڽ��� ������ �̵��� ������ �ִ� ������ �ֵ����� �ѷ��ش�.
			S_SCP_INIT_OTHER_MOB m ;
			GetCreateMob( iMobID, &m ) ;
			GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 ) ;
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
		int iMobID = iArgument1 ; // �ű� mob ID

		if( 0 >= iMobID || MAX_MOB <= iMobID )
		{
			sprintf( szResult, "%s> Invalid ID", a_pCmd ) ;
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return ;
		}

		int x = iArgument2, y = iArgument3 ;
		int tret = GetEmptyMobGrid( iMobID, &x, &y ) ;
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 ) ;
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return ;
		}

		if( eTNMob_NPC == pMob[iMobID].m_eMobType )
		{
			if( MOB_COMBAT == pMob[iMobID].Mode ) // ���� ���̾���.
			{
				pMob[iMobID].Mode = MOB_PEACE ;
				pMob[iMobID].CurrentTarget = 0 ;
				//memset( pMob[iMobID].EnemyList, 0, sizeof( pMob[iMobID].EnemyList ) ) ;
			}
		}
		MSG_Action sm ;
		GetAction( iMobID, x, y, &sm ) ;
		sm.Effect = 5 ; // teleport
		if( iMobID < MAX_USER ) 
		{
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) ) ;
		}
		GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP ) ;
/*
		// �ڽ��� ������ �̵��� ������ �ִ� ������ �ֵ����� �ѷ��ش�.
		S_SCP_INIT_OTHER_MOB m ;
		GetCreateMob( iMobID, &m ) ;
		GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 ) ;
*/
	}
	else if( !strcmp( szCmd, "/mvzone" ) || !strcmp( szCmd, "/���̵�" ) )
	{	
		char temp[512] = { 0,0,0, } ;
		S_CSP_REQ_MOVE_PORTAL kMsg ;
		kMsg.wEndPortalID = iArgument1 ;

		S_SCP_RESP_MOVE_PORTAL sm; sm.wType=SCP_RESP_MOVE_PORTAL;

		bool bRet=true;
		DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
		bRet &= g_ParamMgr.HT_bGetPortalInfo( kMsg.wEndPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;
/*
		if(!bRet) 
		{
			sprintf( szResult, "%s> ���̵� ����> zone ID Ȯ�� ���", a_pCmd ) ;
		}

		{	sprintf(temp,"dbg CSP_REQ_MOVE_PORTAL find portal data error startp:%d endp:%d", kMsg.wStartPortalID, kMsg.wEndPortalID);
			Log(temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP);
			sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); return ;
		}
*/
		BYTE byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 ) ;
		if( bRet && (byMoveZone != (ServerIndex+1)) && (ServerDown==-1000) )	//	�ٸ� ���̸�, ...
		{
			//sprintf(temp,"dbg char:%s move portal to other zone:%d", pMob[a_iHandle].MOB.szName, byMoveZone ) ;
			//Log( temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP ) ;
			pMob[a_iHandle].m_kWaitAction.iAction = eWaitAct_ZonePortal ;

			sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
			sm.byZone=byMoveZone; sm.nMoney=pMob[a_iHandle].MOB.nRupiah;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
			
			pMob[a_iHandle].m_eFSM = eTNFsm_Stand ;
			pMob[a_iHandle].m_kLastTime.uiSitted = 0 ;
			sprintf( szResult, "%s> succeeded to move the other zone", a_pCmd ) ;
		}
		else
		{
			sprintf( szResult, "%s> faild to move the other zone> check the portal ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/hold" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{	
			if( !strcmp( "off", szArgument2 ) )// hold�� turn off �����ش�.
			{
				pMob[iTarget].TurnOffAffection( eTNAfn_Hold2 ) ;
				sprintf( szResult, "%s> hold is debuffered on a target.", a_pCmd ) ;
			}
			else
			{
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_Hold2 ;
				kEffect.iDuration = 600000 ;
				kEffect.iParam1 = 100 ;
				kEffect.iParam2 = 0 ;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				pMob[iTarget].BroadcastUpdateStatusMsg() ;
				pUser[iTarget].cSock.SendMessage() ;

				sprintf( szResult, "%s> hold is affected on a target", a_pCmd ) ;
			}
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/follow" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			if( !strcmp( "off", szArgument2 ) )
			{
				pMob[iTarget].m_iPassenger = 0 ; // follow�� turn off �����ش�.
				sprintf( szResult, "%s> I will stop to follow %d", a_pCmd, iTarget ) ;
			}
			else
			{
				pMob[iTarget].m_iPassenger = a_iHandle ;
				sprintf( szResult, "%s> I will follow %d", a_pCmd, iTarget ) ;
			}			
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/buffer" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			char szNormalInfo[1024] = { 0,0,0, } ;
			sprintf( szNormalInfo, "\r\n\r\nMob:%d/%s \r\n", iTarget, pMob[iTarget].MOB.szName ) ;
			WriteLog( szNormalInfo, ".\\monster_log\\[DEBUG]PrintBuffer.txt" ) ;

			for( int i = 0 ; i < TN_MAX_VARIATION_COUNT ; ++i )
			{
				char szBuf[1024] = { 0,0,0, } ;
				sprintf( szBuf, "Index:%d, Equip(%d,%d), Passive(%d,%d), Activ(%d,%d) \r\n"
					, i
					, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPlus					
					, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPlus
					, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPlus
					) ;
				WriteLog( szBuf, ".\\monster_log\\[DEBUG]PrintBuffer.txt" ) ;
			}
		}
		else
		{
			sprintf( szResult, "%s> Error> Invalid handle!", a_pCmd ) ;
		}

	}
	else if( !strcmp( szCmd, "/speed" ) || !strcmp( szCmd, "/���ǵ�" ) )
	{
		if( 1 <= iArgument1 && 100 >= iArgument1 )
		{	
			TNEFFECT kEffect ;
			kEffect.iID = eTNAfn_MoveSpeedPlus ;
			kEffect.iDuration = 3600000 ; // 60 ��
			kEffect.kFunc.iData = 0 ;
			kEffect.iParam1 = iArgument1 ;
			kEffect.iParam2 = 0 ;
			pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
			pMob[a_iHandle].NotifyUpdateUIMsg() ;
			pUser[a_iHandle].cSock.SendMessage() ;

			sprintf( szResult, "%s> the speed of move is %d", a_pCmd, pMob[a_iHandle].m_iMoveSpeed ) ;
		}
		else
		{
		    sprintf( szResult, "%s> the value of speed is invalid. valid value(5~100)", a_pCmd ) ;
		}
	}
#ifdef __TN_PLAYMOVIE__
	else if( !strcmp( szCmd, "/������¡��" ) )
	{
		if( 1 == iArgument1 ) g_kSiege.InstallSymbols() ;
		else g_kSiege.DestroySymbols() ;
	}
	else if( !strcmp( szCmd, "/������ȯ" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].Direction = iArgument1;

				MSG_Action sm; GetAction( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, &sm);
				sm.Effect = 1 ; // stand
				GridMulticast( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm );
			}
		}
	}
	else if( !strcmp( szCmd, "/��������" ) )
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
	else if( !strcmp( szCmd, "/��������" ) )
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
		}		// teleport�� ���
	}
	else if( !strcmp( szCmd, "/�κ��̵�" ) )
	{ //0/1
		// teleport�� ���
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
				DeleteMob(iMob,645);
				pMob[iMob].Mode = MOB_EMPTY;
			}
		}

		if( 0 < iArgument1 && 1000 > iArgument1 )
		{
			HS2D_COORD krgPos[8] ;
			int iBodyRadius = 1;//pMob[a_iHandle].m_byBodyRadius ;
			int iSize = 4;//iBodyRadius + iBodyRadius + 1 ;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return ;
			HS2D_COORD kCur ;
			kCur.x = pMob[a_iHandle].TargetX ;
			kCur.y = pMob[a_iHandle].TargetY ;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius ) ;
			krgPos[1].x = kCur.x - ( iBodyRadius ) ;
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius ) ;
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius ) ;

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[3].y = kCur.y - ( iBodyRadius ) ;
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[4].y = kCur.y - ( iBodyRadius ) ;

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;
			krgPos[6].x = kCur.x - ( iBodyRadius ) ;
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;

            // ��ȯ�� ��

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000 ; // the index of monster data
            int iSummonCount = iArgument2 ; // ��ȯ�Ǵ� ��
			int iFormation = 0 ;
			if( 7 < iSummonCount ) iFormation = 1 ;
			int iIndex = 0 ;
			int iSummoned = 0;
            for( int iCount = 0 ; iCount < iSummonCount ; ++iCount )
            {
				int x = 0, y = 0 ;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize ;
					y = krgPos[iIndex].y + rand() % iSize ;
					++iIndex ;
					if( 7 < iIndex ) iIndex = 0 ;
				}
				else
				{// random�ϰ� �� ������ �¾��.
					iIndex = rand() % 8 ;
					x = krgPos[iIndex].x + rand() % iSize ;
					y = krgPos[iIndex].y + rand() % iSize ;
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
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd ) ;
		}

		
	}
	else if( !strcmp( szCmd, "/a" ) || !strcmp( szCmd, "/�κ�����" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget() ;
				pMob[iMob].ClearAttacker( 0 ) ;
				pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 ) ;			
			}
		}
	}
	else if( !strcmp( szCmd, "/f" ) || !strcmp( szCmd, "/�κ�����" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget() ;
				pMob[iMob].ClearAttacker( 0 ) ;
				pMob[iMob].Mode = MOB_PEACE ;
				pMob[iMob].OnFollow( a_iHandle ) ;
			}
		}
	}
#endif
	else if( !strcmp( szCmd, "/summon" ) )	// monster ID, Pop Count, class
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1 ;
		if( eTNCls_Warrior != iArgument3 && eTNCls_NPC != iArgument3 && eTNCls_Event != iArgument3 ) iArgument3 = eTNCls_Warrior ;
		// eTNCls_NPC(19) �� ���� NPC-Monster�� ���¸� ���Ѵ�.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			TNSKILL_DATA kSkill ; // ��ȯ���� clan�� ��ӵȴ�.
			kSkill.krgEffect[0].iID = eTNAfn_Summon ; // 
			kSkill.krgEffect[0].kFunc.iData = iArgument3 ; // class1
			kSkill.krgEffect[0].iDuration = eTNPrdt_PopRaise ; // pop type
			kSkill.krgEffect[0].iParam1 = iArgument1 ; // monster ID
			kSkill.krgEffect[0].iParam2 = iArgument2 ; // count

			pMob[a_iHandle].CastOnly( kSkill ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/summon2" ) || !strcmp( szCmd, "/��" ) )	// monster ID, Pop Count, 8|9(clan) range
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1 ;
		if( 0 >= iArgument2 ) iArgument2 = 1 ;
		if( 0 >= iArgument3 ) iArgument3 = eTNClan_Neutral ;

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8] ;
			int iBodyRadius = pMob[a_iHandle].m_byBodyRadius ;
			int iSize = iBodyRadius + iBodyRadius + 1 ;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return ;
			HS2D_COORD kCur ;
			kCur.x = pMob[a_iHandle].TargetX ;
			kCur.y = pMob[a_iHandle].TargetY ;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius ) ;
			krgPos[1].x = kCur.x - ( iBodyRadius ) ;
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius ) ;
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius ) ;

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[3].y = kCur.y - ( iBodyRadius ) ;
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[4].y = kCur.y - ( iBodyRadius ) ;

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius ) ;
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;
			krgPos[6].x = kCur.x - ( iBodyRadius ) ;
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius ) ;

            // ��ȯ�� ��

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000 ; // the index of monster data
            int iSummonCount = iArgument2 ; // ��ȯ�Ǵ� ��
			int iFormation = 0 ;
			if( 7 < iSummonCount ) iFormation = 1 ;
			int iIndex = 0 ;
            for( int iCount = 0 ; iCount < iSummonCount ; ++iCount )
            {
				int x = 0, y = 0 ;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize ;
					y = krgPos[iIndex].y + rand() % iSize ;
					++iIndex ;
					if( 7 < iIndex ) iIndex = 0 ;
				}
				else
				{// random�ϰ� �� ������ �¾��.
					iIndex = rand() % 8 ;
					x = krgPos[iIndex].x + rand() % iSize ;
					y = krgPos[iIndex].y + rand() % iSize ;
				}

				int iMob = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Warrior, 0, iArgument3, 0, x, y, 0 ) ;

				if( 0 == iMob ) ++iSummonCount ;
				if( 30 <= iSummonCount ) break ;
            }  
		}
		else
		{
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/summon3" ) )	// monster ID, x, y, class1, clan
	{
		if	( iArgument2<0 || iArgument3<0 || iArgument2>MAX_GRIDX || iArgument3>MAX_GRIDY ) return ;
		if( eTNCls_Warrior > iArgument4 || eTNCls_NPC < iArgument4 ) iArgument4 = eTNCls_Warrior ;
		if( eTNClan_NPC < iArgument5 || eTNClan_NoTrimuritiy > iArgument5 ) return ;
		// eTNCls_NPC(19) �� ���� NPC-Monster�� ���¸� ���Ѵ�.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			pMob[a_iHandle].Summon( iArgument1/*tribe*/, 1/*pop#*/, eTNPrdt_PopRaise, iArgument4/*class1*/, eTNCls2_Basic/*class2*/, iArgument5/*clan*/, 0/*Direction*/, iArgument2, iArgument3, 0/*Enemy*/, false ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/summonpet" ) )	// monster ID, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClan = iArgument2 ;
			int iDuration = iArgument3 ;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, eTNCls_Summoned, eTNCls2_Pet, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/summonInteractor" ) )	// monster ID, class1, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClass1 = iArgument2 ;
			int iClan = iArgument3 ;
			int iDuration = iArgument4 ;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, iClass1, eTNCls2_Basic, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;
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
			sprintf( szResult, "height:%d(%d,%d), mob:%d", iHeight, x, y, iTarget ) ;
		}
		else
		{
		    sprintf( szResult, "%s>  invalid mobile handle", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/SetHeight" ) )	// obstacle, character
	{
		int iOld = g_irgSetting[eCnst_ObstacleHeight];
		g_irgSetting[eCnst_ObstacleHeight] = iArgument1; // obstacle
		g_irgSetting[eCnst_CharacterHeight] = iArgument2; // character

		sprintf( szResult, "The height of a obstacle:%d(old:%d)", g_irgSetting[eCnst_ObstacleHeight], iOld ) ;
	}
	else if( !strcmp( szCmd, "/army" ) )
	{
		if( 1 > iArgument2 ) iArgument2 = 1 ;
		if( 20 < iArgument2 ) iArgument2 = 20 ;
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8] ;
			int iSize = 1 ;
			int iBodyRadius = 1 ;
			if( 0 >= iSize ) return ;

			krgPos[0].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius ) ;
			krgPos[0].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius ) ;
			krgPos[1].x = pMob[a_iHandle].TargetX - ( iBodyRadius ) ;
			krgPos[1].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius ) ;
			krgPos[2].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius ) ;
			krgPos[2].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius ) ;

			krgPos[3].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius ) ;
			krgPos[3].y = pMob[a_iHandle].TargetY - ( iBodyRadius ) ;
			krgPos[4].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius ) ;
			krgPos[4].y = pMob[a_iHandle].TargetY - ( iBodyRadius ) ;

			krgPos[5].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius ) ;
			krgPos[5].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius ) ;
			krgPos[6].x = pMob[a_iHandle].TargetX - ( iBodyRadius ) ;
			krgPos[6].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius ) ;
			krgPos[7].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius ) ;

			if( eFollower_MaxCount < iArgument2 ) iArgument2 = eFollower_MaxCount ;
			if( 1 > iArgument2 ) iArgument2 = 1 ;
			int iIndex = 0 ;
			int iClan = 0 ;
			if( 0 == iArgument3 ) iClan = pMob[a_iHandle].m_byClan ;
			if( eTNClan_GM == iClan ) iClan = eTNClan_Neutral ;

            for( int iCount = 0 ; iCount < iArgument2 ; ++iCount )
            {
				int x = 0, y = 0 ;
				x = krgPos[iIndex].x + rand() % iSize ;
				y = krgPos[iIndex].y + rand() % iSize ;
				++iIndex ;
				if( 7 < iIndex ) iIndex = 0 ;
				int iFollower = pMob[a_iHandle].m_irgFollower[iCount] ;
				if( MAX_USER <= iFollower && MAX_MOB > iFollower ) KillMonster( iFollower ) ; //pMob[iFollower].MOB.nHP = 0 ;
				pMob[a_iHandle].m_irgFollower[iCount] = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Follower, 0, iClan, 0, x, y, 0 ) ;
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID", a_pCmd ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/releaseArmy" ) )
	{
		for( int i = 0 ; i < eFollower_MaxCount ; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgFollower[i] ;
			KillMonster( iMob ) ;
			/*
			pMob[iMob].MOB.nHP = 0 ; 
			pMob[iMob].CurrentTarget = 0 ;
			pMob[iMob].m_eFSM = eTNFsm_Dead ;
			*/
		}

		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/account" ) )		// target ID
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			sprintf( szResult, "%s> Account:%s", a_pCmd, pUser[iArgument1].AccountName ) ;		
		}
		else
		{
			sprintf( szResult, "%s> invalid ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/atk" ) )
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			for( int iIndex = 0 ; iIndex < eFollower_MaxCount ; ++iIndex )
			{
				int iFollowerIndex = pMob[a_iHandle].m_irgFollower[iIndex] ;
				if( MAX_USER > iFollowerIndex || MAX_MOB <= iFollowerIndex ) continue ;
				pMob[iFollowerIndex].m_kLastTime.uiSelectTarget = CurrentTime + 5000 ;
				pMob[iFollowerIndex].CurrentTarget = iArgument1 ;
				pMob[iFollowerIndex].OnUnderAttack( iArgument1 ) ;
			}
		}
		else if( 0 == iArgument1 )
		{ // �갳�Ͽ� ������ ��� mob(berserk�� ����)�� �����Ѵ�. // berserk �������� �ٲ۴�.

		}
		else
		{
			sprintf( szResult, "%s> invalid target ID", a_pCmd ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/truesight" ) || !strcmp( szCmd, "/����" ) )
	{
		TNEFFECT kEffect ;
		kEffect.iID = eTNAfn_WizardEyes ;
		kEffect.iDuration = 3600000 ; // 60��
		kEffect.iParam1 = 0 ;
		kEffect.iParam2 = 0 ;
		pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
		pMob[a_iHandle].NotifyUpdateStatusMsg() ;
		pUser[a_iHandle].cSock.SendMessage() ;

		sprintf( szResult, "%s> truesight is activated.", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/����" ) || !strcmp( szCmd, "/kickout" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			MSG_Broadcast kMsg ; ZeroMemory(&kMsg, sizeof(kMsg));
			kMsg.wType = _MSG_Broadcast ;
			kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

			kMsg.byMsgType = MESSAGE_SERVERMSG;
			kMsg.byBgColor = 14 ;
			kMsg.byTextColor = 15 ;
			kMsg.byMsgType = 1 ; 

			if( eCountryKorea == g_eCountryID ) strncpy( kMsg.szMsg, g_pMessageStringTable[_DisconnectedToServer], sizeof(kMsg.szMsg)) ;			
			else strncpy( kMsg.szMsg, g_pMessageStringTable[_KickedByGM], sizeof(kMsg.szMsg)) ;			
			strncpy( kMsg.szName, pMob[a_iHandle].MOB.szName, SZNAME_LENGTH ) ;
			kMsg.byTrimuriti = eTNClan_GM ;
			pUser[iTarget].cSock.AddMessage((char*)&kMsg, sizeof(kMsg));

			CloseUser( iTarget ) ;
			sprintf( szResult, "%s> The target user will be disconnected in 15 seconds", a_pCmd ) ;
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/��ġ" ) || !strcmp( szCmd, "/where" ) )// ok
    {
		int iTarget = GetMOBID( szArgument1 ) ;
		if( 0 < iTarget )	//	���������� ���� ����
		{	
			if( MAX_USER <= iTarget ) return ;		  
		    int x = pMob[iTarget].TargetX ;
		    int y = pMob[iTarget].TargetY ;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y ) ;
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/whereid" ) )// ok
    {
		int iTarget = GetMOBIDFromID( szArgument1 ) ;
		if( 0 < iTarget )	//	���������� ���� ����
		{	
			if( MAX_USER <= iTarget ) return ;		  
		    int x = pMob[iTarget].TargetX ;
		    int y = pMob[iTarget].TargetY ;
			sprintf( szResult, "ID:%s> x:%d, y:%d", a_pCmd, x, y ) ;
		}
		else
		{
			sprintf( szResult, "ID:%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/wheremob" ) )// ok
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_MOB > iTarget )	//	���������� ���� ����
		{	
		    int x = pMob[iTarget].TargetX ;
		    int y = pMob[iTarget].TargetY ;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y ) ;
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
    }
    else if( !strcmp( szCmd, "/equip" ) || !strcmp( szCmd, "/���" ) )
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{			
			STRUCT_ITEM krgItem[MAX_EQUIP] ;
			memcpy( krgItem, pMob[iTarget].MOB.Equip, sizeof(krgItem) ) ;

			for( int i = 0 ; i < MAX_EQUIP ; ++i )
			{
				if( 0 < krgItem[i].snIndex ) krgItem[i].snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
				if( 0 < krgItem[i].snDurability ) krgItem[i].snDurability = krgItem[i].snDurability / 100 + 1 ;
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
				) ;
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}        
    }
	else if( !strcmp( szCmd, "/weapon" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_OneHandWeapon] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/armor" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Armor] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/pants" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Pants] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/helmet" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Helmet] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;     
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/shield" ) || !strcmp( szCmd, "/����" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Shield] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;            
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/gloves" ) || !strcmp( szCmd, "/�尩" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Gloves] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/boots" ) || !strcmp( szCmd, "/�Ź�" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			STRUCT_ITEM kItem ;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Boots] ;
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1) ;
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1 ;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				) ;      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd ) ;
		}
	}
	else if( (!strcmp( szCmd, "/JudgeSurvival" )) || !strcmp( szCmd, "/�����̹�����" )  )		// mob handle, HP
	{
		if( eZone_Stronghold != g_iZoneID ) return ;

		char szSurvivals[512] = { 0,0,0, } ;
		if( 1 == iArgument1 )
		{
			g_kArena.OutputSurvivals( szSurvivals, 0 ) ;			
			PostMessageToZone( szSurvivals ) ;
		}
		else if( 0 == iArgument1 ) g_kArena.OutputSurvivals( szSurvivals, 1 ) ; // ���ڿ��Ը� ����� �����ش�.

		//g_kArena.CheckWinner( 1 ) ; // winner�� �˻��ϰ�, ��Ƽ���� �ƴ� ������ �˸���.
		sprintf( szResult, "%s> %s", a_pCmd, szSurvivals ) ;
	}
	else if( !strcmp( szCmd, "/Bless" ) )		// mob handle, HP
	{
		if( eZone_Cruma != g_iZoneID ) return ;

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			TriggerEvent( iArgument1, 25, pMob[iArgument1].TargetX, pMob[iArgument1].TargetY, g_irgGod[pMob[iArgument1].m_byClan], 112 ) ;
			//pMob[iArgument1].MOB.nHP = iArgument2 ;
			sprintf( szResult, "%s> %s(%d) is blessed!!!", a_pCmd, pMob[iArgument1].MOB.szName, iArgument1 ) ;
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd ) ;   		    
	}
	else if( !strcmp( szCmd, "/ChangeHP" ) )		// mob handle, HP
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].MOB.nHP = iArgument2 ;
			sprintf( szResult, "%s> HP:%d", a_pCmd, pMob[iArgument1].MOB.nHP ) ;
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd ) ;   		    
	}
	else if( !strcmp( szCmd, "/SearchMonsterHandle" ) )
	{
		iArgument1 = iArgument1;

		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			for( int i = MAX_USER ; i < MAX_MOB ; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe ) break ;
			}

			if( MAX_MOB != i ) sprintf( szResult, "%s> Monster ID: %d",  a_pCmd, i ) ; // ã�Ҵٸ�, ...
			else sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;   		    
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
				) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid Argumenteter1. argument1:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterData" ) ) // ������ monster ������ ȭ�鿡 ���
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;

			sprintf( szResult, "%s> Lvl:%d, Trimu:%d, AI:%d, HP:%d, AR:%d, DR:%d, AC:%d, Resist(%d,%d,%d,%d), ArmorType:%d", a_pCmd
				, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].nHP
				, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart  // AR/DR/AC
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
				, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType]
				) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/RecordMonsterData" ) ) // detail�� ������ ���� log file�� ���
	{
		if( 2000 <= iArgument1 && 3000 > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;

			char chBuf[1024] = { 0,0,0, } ;
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
) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" ) ;
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 2000, 2999 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterStatus" ) )		// mob id
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iDist = CalDistance( iArgument1, pMob[iArgument1].CurrentTarget ) ;
			char chBuf[1024] = { 0,0,0, } ;
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

) ;
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" ) ;
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd) ;
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterMode" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			sprintf( szResult, "Monster(%d) Mode:%d",  iArgument1, pMob[iArgument1].Mode ) ;
		}
	}
	else if( !strcmp( szCmd, "/checkmonster" ) )
	{
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			sprintf( szResult, "%s> ",  a_pCmd ) ;
			int iCount = 0 ;
			for( int i = MAX_USER ; i < MAX_MOB ; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe )
				{
					char szMonsterID[128] = { 0,0,0, } ;
					sprintf( szMonsterID, "%d: %d, ",  iCount, i ) ;
					strcat( szResult, szMonsterID ) ;
					++iCount ;				
				}
				if( 20 < iCount ) break ;
			}

			if( 0 == iCount ) sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 ) ;
		}
		else		
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetKalaSystem" ) )
	{
		// ����ϰ� �ִ� ��� kala-core ����
		// ���� ������ �ִ� ��� kala-core ����
		// altar�� �ִ� ��� kala monster ����
		// rewarder NPC �߸�ȭ
		// �������� portal NPC �߸�ȭ
		// ��� ���� ����
	}
	else if( !strcmp( szCmd, "/printkalacoreinfo" ) )
	{
		if( SERVER_TRIMURITI != iZoneID ) return ;
		g_kKalaSystem.DropKalaCoreInPC() ;
		g_kKalaSystem.CheckCountNRecovery() ;
		g_kKalaSystem.PrintScreen( szResult ) ;
		MoveKalaRewarder() ;		
	}
	else if( !strcmp( szCmd, "/removekalacore" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{
			RemoveKalaCoreInInventory( iTarget ) ;
			sprintf( szResult, "%s> the command is completed successfully.", a_pCmd ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid ID.", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/dropkalacore" ) )
	{	
		return ;
		if( SERVER_TRIMURITI != iZoneID ) return ;
		if( (eKalaCore_Brahma == iArgument1) || (eKalaCore_Vishnu == iArgument1) || (eKalaCore_Siva == iArgument1) ) 
		{
			STRUCT_ITEM kItem ;
			memset( &kItem, 0, sizeof(kItem) ) ;
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1 ;
			kItem.snDurability = eDur_Indestructible ;
			kItem.byCount = 1 ;

			int iCoordX, iCoordY ;
			iCoordX = pMob[a_iHandle].TargetX-1 ;
			iCoordY = pMob[a_iHandle].TargetY-1 ;
			CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 ) ;

			{
				//SYSTEMTIME st ;
				//GetLocalTime( &st ) ;
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, ">>> GM %s drop a kala-core(%d) at L(%d,%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[a_iHandle].MOB.szName, iArgument1, pMob[a_iHandle].TargetX-1, pMob[a_iHandle].TargetY-1, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
				WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
			}
			NotifyRvRStatus() ;
		}
		else		
		{
			sprintf( szResult, "%s> invalid kala-core ID. id: brahma:8051, vishnu:8052, siva:8053 ", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/KickOutAllPlayers" ) )
	{
		for( int i = 1 ; i < MAX_USER ; ++i )
		{
			if( USER_PLAY != pUser[i].Mode ) continue;
			ReturnPCToSaveZone( i );
		}

		sprintf( szResult, "%s> successful", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/CountMonster" ) )
	{
		if( eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1 )
		{
			int iCount = 0 ;
			for( int i = MAX_USER ; i < MAX_MOB ; ++i )
			{
				if( iArgument1 == pMob[i].m_byClan )
				{
					if( 0 < pMob[i].MOB.nHP ) ++iCount ;
				}
			}

			sprintf( szResult, "%s> count:%d ", a_pCmd, iCount ) ;
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/KillMonsterAll" ) )
	{
		for( int i = MAX_USER ; i < MAX_MOB ; ++i )
		{
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue ;
			if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue ;

			KillMonster( i ) ;
		}

		sprintf( szResult, "%s> successful", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/KillClanMonster" ) )
	{
		if( (eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1) || (eTNClan_Stronghold1 <= iArgument1 && eTNClan_Stronghold4 >= iArgument1) )
		{
			for( int i = MAX_USER ; i < MAX_MOB ; ++i )
			{
				if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue ;
				if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue ;

				if( iArgument1 == pMob[i].m_byClan )
				{
					KillMonster( i ) ;
				}
			}

			sprintf( szResult, "%s> successful", a_pCmd ) ;
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/killkala" ) )
	{
		/*
		iArgument1 = atoi( szArguments ) ;
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				KillMonster( iArgument1 ) ;
				//MoveKalaRewarder() ;

				int iAltarIndex = 0 ;
				for( ; iAltarIndex < eKalaAltar_MaxCount ; ++iAltarIndex )
				{ // Į�� ���ܿ� ��ġ�ϰ� �ִ�, ...
					int iMobHandle = g_irgKalaAltar[iAltarIndex] ;
					if( MAX_USER <= iMobHandle && MAX_MOB > iMobHandle )
					{
						if(iArgument1 == iMobHandle )
						{
							g_irgKalaAltar[iAltarIndex] = 0 ;
							break ;
						}
					}
				}

				{
					SYSTEMTIME st ;
					GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf( chBuf, "GM destroied the kala(%d) at altar(%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[iArgument1].MOB.snTribe, iAltarIndex, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
				}
			}
			else sprintf( szResult, "%s> %d is not the kala.", a_pCmd, iArgument1 ) ;   		    
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/����" ) )
	{ // mob id, direction(new)
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			int iMob = iArgument1;
			int iOldDir = pMob[iMob].m_iDirection;
			pMob[iMob].m_iDirection = iArgument2;
			S_SCP_INIT_OTHER_MOB sm ;
			GetCreateMob( iMob, &sm ) ;
			GridMulticast( pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm, 0, 100 ) ;
			
			sprintf( szResult, "%s> Mob:%d, Dir:%d->%d", a_pCmd, iMob, iOldDir, pMob[iMob].m_iDirection ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;
		}
	}
	else if( !strcmp( szCmd, "/sp" ) || !strcmp( szCmd, "/��" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].DeliverComment( &a_pCmd[9] ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;
		}
	}
	else if( !strcmp( szCmd, "/TriggerEvent" ) )		// event ID, NPC ID
	{
		if( 0 < a_iHandle && MAX_USER > a_iHandle )
			TriggerEvent( a_iHandle, iArgument1, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, iArgument2, 100 ) ;
		else TriggerEvent( 0, iArgument1, 0, 0, iArgument2, 101 ) ;	    

		sprintf( szResult, "%s> successful~ ", a_pCmd  ) ;
	}
	else if( !strcmp( szCmd, "/attack" ) || !strcmp( szCmd, "/����" ) )		// id, target
	{
		if( ( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) && ( 0 < iArgument2 && MAX_MOB > iArgument2 ) )
		{
			pMob[iArgument1].m_kLastTime.uiSelectTarget = CurrentTime + 10000 ;
			pMob[iArgument1].CurrentTarget = iArgument2 ;
			pMob[iArgument1].OnUnderAttack( iArgument2 ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID(%d) or invalid target handle(%d).", a_pCmd, iArgument1, iArgument2 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/attack2" ) || !strcmp( szCmd, "/����2" ) )
	{
		if( 0 >= a_iHandle || MAX_USER <= a_iHandle) return ;
		if( MAX_USER <= iArgument1 && MAX_MOB >= iArgument1 )
		{
			int TargetX = pMob[a_iHandle].TargetX ;
			int TargetY = pMob[a_iHandle].TargetY ;
			int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy] ;
			int x, y ;
			for( int i = 0 ; i < iMaxIndex ; ++i )
			{
				x = TargetX + g_pDetectEnemyTable[i][0] ;
				y = TargetY + g_pDetectEnemyTable[i][1] ;
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
				if	(pMob[tmob].MOB.nHP <=0) continue;
				if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
				pMob[tmob].m_kLastTime.uiSelectTarget = CurrentTime + 10000 ;
				pMob[tmob].CurrentTarget = iArgument1 ;
				pMob[tmob].OnUnderAttack( iArgument1 ) ;
			}
		}
		else
		{
			sprintf( szResult, "%s> Invalid target handle(%d).", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/killmonster" ) || !strcmp( szCmd, "/ų��" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				sprintf( szResult, "%s> can't kill the kala!!! use /killkala command.", a_pCmd ) ;  
			}
			else
			{
				KillMonster( iArgument1 ) ;
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/bufnpc" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			TNEFFECT kEffect ;
			kEffect.iID = eTNAfn_HealPlus ;
			kEffect.iDuration = 1800000 ;
			kEffect.iParam1 = iArgument2 ;
			pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle ) ;

			TNEFFECT kEffect2 ;
			kEffect2.iID = eTNAfn_RecoverTPPlus ;
			kEffect2.iDuration = 1800000 ;
			kEffect2.iParam1 = iArgument3 ;
			pMob[iArgument1].AddEffect( kEffect2, a_iHandle, a_iHandle ) ;

			TNEFFECT kEffect3 ;
			kEffect3.iID = eTNAfn_MaxHPPlus2 ;
			kEffect3.iDuration = 1800000 ;
			kEffect3.iParam1 = iArgument4 ;
			pMob[iArgument1].AddEffect( kEffect3, a_iHandle, a_iHandle ) ;

			TNEFFECT kEffect4 ;
			kEffect4.iID = eTNAfn_MaxTPPlus2 ;
			kEffect4.iDuration = 1800000 ;
			kEffect4.iParam1 = iArgument5 ;
			pMob[iArgument1].AddEffect( kEffect4, a_iHandle, a_iHandle ) ;

		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/DebugDur" ) )
	{
		iArgument2 *= 60000 ; // 1�д���
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].m_iDebugFlag2 = 0 ;
			}
			else 
			{
				pMob[iArgument1].m_iDebugFlag2 = 1 ;
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 ) ;				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/Log" ) || !strcmp( szCmd, "/log" ) ) // /log 15 => 10�е��� log�� �����, /log 15 60 => 60�е��� log�� �����.
	{
		iArgument2 *= 60000 ; // 1�д���
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Log ) ;
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000 ; // 10�п��� 1�ð�
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_Log ;
				kEffect.iDuration = iArgument2 ;
				kEffect.iParam1 = 0 ;
				kEffect.iParam2 = 0 ;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 ) ;				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/logx" ) ) // /log 15 => 10�е��� log�� �����, /log 15 60 => 60�е��� log�� �����.
	{// mob handle, debug type, duration(10��), on/off(on)
		int iDebugType = eTNDbg_None ;
		iArgument3 *= 60000 ; // 1�д���
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument4 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Debug ) ;
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 1 == iArgument2 ) iDebugType = eTNDbg_Combat ;
				else if( 2 == iArgument2 ) iDebugType = eTNDbg_Pet ;
				else if( 3 == iArgument2 ) iDebugType = eTNDbg_Immunity ;
				else if( 4 == iArgument2 ) iDebugType = eTNDbg_Affection ;

				if( 0 >= iArgument3 || 3600000 < iArgument3 ) iArgument3 = 600000 ; // 10�п��� 1�ð�
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_Debug ;
				kEffect.iDuration = iArgument3 ;
				kEffect.iParam1 = iDebugType ;
				kEffect.iParam2 = 0 ;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				sprintf( szResult, "%s> debug ID(%d), debug type:%d, dur:10 minutes.", a_pCmd, iArgument1, iArgument2 ) ;				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/logimmu" ) ) // /log 15 => 10�е��� log�� �����, /log 15 60 => 60�е��� log�� �����.
	{// mob hndl
		iArgument2 *= 60000 ; // 1�д���
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_LogImmu ) ;
			}
			else 
			{
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000 ; // 10�� ����
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_LogImmu ;
				kEffect.iDuration = iArgument2 ;
				kEffect.iParam1 = 0 ;
				kEffect.iParam2 = 0 ;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				sprintf( szResult, "%s> write log immunity for ID(%d), dur:10 minutes. Immunity:%d(%h)", a_pCmd, iArgument1, pMob[iArgument1].m_iImmunity, pMob[iArgument1].m_iImmunity ) ;
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat() ;
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill() ;
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off ;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On ;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/eventlog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_EventLog ;
		else
		{
			if( eTNSwitch_EventLog & g_iSwitch ) g_iSwitch = eTNSwitch_EventLog ^ eTNSwitch_EventLog ;
		}
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_EventLog & g_iSwitch) ) ;
	}
	else if( !strcmp( szCmd, "/contactnpclog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_ContactNPC ;
		else
		{
			if( eTNSwitch_ContactNPC & g_iSwitch ) g_iSwitch = g_iSwitch ^ eTNSwitch_ContactNPC ;
		}

		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_ContactNPC & g_iSwitch) ) ;
	}
	else if( !strcmp( szCmd, "/PopMonster" ) )
	{
		/*
		iArgument1 = atoi( szArguments ) ;
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_kLastTime.uiKilled = 0 ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ;   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/recoverkalasystem" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_RecvKalaSystem ;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_RecvKalaSystem ;
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_RecvKalaSystem & g_iSwitch) ) ;
	}
	else if( !strcmp( szCmd, "/DecPrana" ) ) // ok
	{
		if( !strcmp( "off", szArgument1 ) ) g_bDecPrana = true ;
		else g_bDecPrana = false ;
		sprintf( szResult, "%s> %d(if the value is equal to 1, the system don't decrease prana when PC is killed.)", a_pCmd, g_bDecPrana ) ;
/*
	    iArgument1 = atoi( szArguments ) ;
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_DecPrana ; //g_bDecPrana = true ;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_DecPrana ; // on
		sprintf( szResult, "%s> %d(1�� ���ԵǾ� ������ ����ġ�� off, �׾ ���󳪰� ���� �ʴ´�.)", a_pCmd, g_iSwitch ) ;
*/
	}
	/*
	else if( !strcmp( szCmd, "/ResetSkill" ) ) // ok
	{
	    iArgument1 = atoi( szArguments ) ;
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_ResetSkill ; // off
		else g_iSwitch = g_iSwitch ^ eTNSwitch_ResetSkill ;		 // on
		sprintf( szResult, "%s> %d(2�� ���ԵǾ� ������, ����ġ�� off, ��ų������ �������� �ʴ´�.)", a_pCmd, g_iSwitch ) ;
	}
	*/
/*
	else if( !strcmp( szCmd, "/cc" ) )
	{
		iArgument1 = atoi( szArguments ) ; // index
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 ) ;
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] ) ;
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 ) ;
		}
	}		   szResult
*/
	else if( !strcmp( szCmd, "/PrintRwdCorrect" ) )
	{
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect ) ;
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( iArgument1, iArgument2, iArgument3 ) ; // prana, gold, BP

		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect ) ;
	}
	else if( !strcmp( szCmd, "/kickouto" ) )
	{
		TriggerEvent( 0, 30, 0, 0, 0, 102 ) ;
		sprintf( szResult, "%s> successful~ ", a_pCmd  ) ;
	}
	else if( !strcmp( szCmd, "/kickoutx" ) )
	{
		TriggerEvent( 0, 31, 0, 0, 0, 103 ) ;
		sprintf( szResult, "%s> successful~ ", a_pCmd  ) ;
	}
	else if( !strcmp( szCmd, "/RefiningRate" ) )		//	FORMAT ===> $REFINING UP,DOWN COUNT
	{	
		if(!strcmp(szArgument1,"Up"))
		{	g_ItemRefineGMScale += iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
		}
		else if(!strcmp(szArgument1,"Down"))
		{	g_ItemRefineGMScale -= iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
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
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/Prana" ) )
	{
		int nID = GetMOBID(szArgument1);
		if( (nID<=0) || (nID>=MAX_USER) ) return;
		pMob[nID].AcquirePrana(iArgument2);
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
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
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/LogDump" ) )
	{
		fflush(fLogFile);
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/MSGLogDump" ) )
	{
		MSG_ServerCommand sm; ZeroMemory(&sm, sizeof(sm));
		sm.wType = _MSG_ServerCommand; sm.byCommandType=eCommandDump;
		if(!MSGServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
		{	Log("err charstatus MSG-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
		}
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/Exchange" ) )						//	For Test(in china)
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));
		bm.Packet_result = 0; bm.Time_Exchanged = 340;
		bm.ItemNo = 0;
		SendBilling3(a_iHandle, &bm, _Msg_BillTimeEx);
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/DropItm" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem ;
			memset( &kItem, 0, sizeof(kItem) ) ;
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1 ;
			kItem.snDurability = 10 ;
			kItem.byCount = 1 ;
			kItem.byRefineLevel = 9;

			int iCoordX, iCoordY ;
			iCoordX = pMob[a_iHandle].TargetX-1 ;
			iCoordY = pMob[a_iHandle].TargetY-1 ;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END ) ;   		    
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
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/Dress" ) )
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm)); 
		bm.Packet_result = 0; bm.article_number = 2342;
		bm.Dressed = 1;
		SendBilling3(a_iHandle, &bm, _Msg_BillDress);
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/Connect" ) )
	{
		if(!strcmp(szArgument1,"BILL"))
		{	int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP2;			//	�ʸ����� ������ �ζ��λ���Ѵ�
			int ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip, WSA_READBILL, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect BILL Server(x2) fail.","-system",0);
				BILLING=0;//������� ����Ѵ�.
			}	else
			{	_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
				SendBilling2(&sm,4);
				sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
			}
		}
		else if(!strcmp(szArgument1,"MSG"))
		{	int * pip = (int*)LocalIP2;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	�ʸ����� MSG Public���
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
		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/Report" ) )
	{
		if(!strcmp(szArgument1,"Transparency"))		//	ũ�縶���� Į���� ���� ������Ʈ�� ����ٰ� �Ű� ���� ���
		{
			int nID = iArgument2;
			if(g_bIsKaliaOpend) return;				//	Į���ƴ����� ���½ð��̸� �翬�� ������ �Ѵ�.
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
			sprintf( szResult, "%s> Successfully", a_pCmd ) ;
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
	else if( !strcmp( szCmd, "/������¥����" ) )
	{
		// �������� Ȯ�� �ܰ� �ʿ�
		int iSelected = iArgument1 ;
		g_kSiege.SelectDate( iSelected ) ;

		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/��������" ) )
	{
		sprintf( szResult, "%s> ", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/dump������Ʈ��" ) )
	{
		g_kSiege.SaveData( szArgument1 );
		sprintf( szResult, "%s> completed successfully.", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/reload������Ʈ��" ) )
	{
		g_kSiege.Init() ;
		g_kSiege.LoadData() ;
		sprintf( szResult, "%s> completed successfully.", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/ChangeClanForSiege" ) )
	{
		if( !g_kSiege.get_Started() ) return;

		#ifdef __TN_TOP_LOG__
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf(chBuf, "[eTNAct_ChangeClanForSiege] %dYY%dMM%dDD %2dHH%2dMI%2dSS> \r\n"
				, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
				) ; 
			WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
		}
		#endif


		for( int i = 1 ; i < MAX_USER ; ++i )
		{
			if( eTNClan_GM == pMob[i].m_byClan ) continue;
			//if( eTNClan_CastleOwner <= pMob[i].m_byClan && eTNClan_Siege4 >= pMob[i].m_byClan ) continue;
			if( USER_PLAY != pUser[i].Mode ) continue ;

			byte byOld = pMob[i].m_byClan;

			int iFlag = g_kSiege.SearchEntry( pMob[i].MOB.nGuildID ) ;
			if( -1 == iFlag ) pMob[i].m_byClan = eTNClan_Siege4 ;
			else pMob[i].m_byClan = iFlag ;

			MSG_CHANGE_CLAN kMsg;
			kMsg.snKeyID = i;
			kMsg.byClan = pMob[i].m_byClan;
			pUser[i].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) ) ;

			MSG_SET_ZONE_SETTINGS kZoneSettingMsg ;
			kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID ;
			kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);

			kZoneSettingMsg.snSiege = 1; //g_kSiege.get_Started(); ��������
			pUser[i].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) ) ;

			S_SCP_INIT_OTHER_MOB sm ;
			GetCreateMob( i, &sm ) ;
			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0) ;

			pUser[i].cSock.SendMessage();

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "[eTNAct_ChangeClanForSiege] PC(%d, Name:%s, Guild:%d), clan(now:%d, old:%d) \r\n"
					,i , pMob[i].MOB.szName, pMob[i].MOB.nGuildID
					, pMob[i].m_byClan, byOld
					) ; 
				WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
			}
			#endif
		}

		sprintf( szResult, "%s> successful", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/InsertToSiegeEntry" ) )
	{
		int iClanSlot = iArgument1;
		int iExpandedSlot = iArgument2;
		int iGuildID = iArgument3;

		g_kSiege.RegisterEntry( iGuildID, iClanSlot, iExpandedSlot, 1) ;

		sprintf( szResult, "%s> successful", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/RefreshEntry" ) )
	{
		g_kSiege.RefreshEntry();
		sprintf( szResult, "%s> successful", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/������û" ) )
	{// PC handle clanSlot expandSlot]
		// NPC���� �Ÿ� �˻簡 �־�� �Ѵ�.
		if( (0 < iArgument1 && MAX_USER > iArgument1) || g_kSiege.get_Started() )
		{			
			bool bBreak = false ;
			if( 0 == iArgument2 ) if( TNSiege::eApplyFee_Defense > pMob[iArgument1].get_Gold() ) bBreak = true ;
			else if( 1 == iArgument2 ) if( TNSiege::eApplyFee_Siege1 > pMob[iArgument1].get_Gold() ) bBreak = true ;
			else if( 2 == iArgument2 ) if( TNSiege::eApplyFee_Siege2 > pMob[iArgument1].get_Gold() ) bBreak = true ;
			else if( 3 == iArgument2 ) if( TNSiege::eApplyFee_Siege3 > pMob[iArgument1].get_Gold() ) bBreak = true ;

			if( bBreak )
			{// ���� �����ϴٴ� �޽���				
				SendClientMessage( iArgument1, g_pMessageStringTable[_HaveNotEnoughGold] ) ;
				return ;
			}

			char szNofity[512] = { 0,0,0, } ;
			int iGuildID = pMob[iArgument1].MOB.nGuildID ;
			int iGuildIndex = pUser[iArgument1].nGuildIndex ;

			int iRes = g_kSiege.RegisterEntry( iGuildID, iArgument2, iArgument3, iArgument1 ) ; // guild ID, clan slot, expand slot, applier
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> �̹� ��ϵǾ� ����", a_pCmd ) ;	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> ���� ��û �Ⱓ�� �����Ǿ���", a_pCmd ) ;	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> �Է� ����", a_pCmd ) ;	
			}
			else
			{
				sprintf( szResult, "%s> ������ ��� �Ϸ�1", a_pCmd ) ;				
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], pGuild[iGuildIndex].GUILD.GuildName ) ;
				SendClientMessage( iArgument1, szNofity ) ;
			}

			int iAllyGuildID = pGuild[iGuildIndex].nAlliedID ;

			iRes = g_kSiege.RegisterEntry( iAllyGuildID, iArgument2, iArgument3+1, iArgument1 ) ;
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> ���ձ��(%d)�� �̹� ��ϵǾ� ����", a_pCmd, iAllyGuildID ) ;	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> ���� ��û �Ⱓ�� �����Ǿ���", a_pCmd ) ;	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> ���ձ�� ���� �Է� ����", a_pCmd ) ;	
			}
			else
			{
				sprintf( szResult, "%s> ������ ��� �Ϸ�2", a_pCmd ) ;
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], g_pMessageStringTable[_AllyGuild] ) ;
				SendClientMessage( iArgument1, szNofity ) ;
			}

			//g_kSiege.SaveData() ;
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d. or ������ ���� ��", a_pCmd, 0, MAX_USER ) ;
		}
	}
	else if( !strcmp( szCmd, "/��������Ȯ��" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iRes = g_kSiege.SearchEntry( pMob[iArgument1].MOB.nGuildID ) ;

			sprintf( szResult, "%s> clan:%d, guild:%d, successfully.", a_pCmd, iRes, pMob[iArgument1].MOB.nGuildID ) ;

			//if( -1 == iRes ) SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsNotRegistered] ) ;
			//else SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsRegistered] ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER ) ;
		}		
	}
	else if( !strcmp( szCmd, "/������û����" ) )
	{
		g_kSiege.set_ExpiryOftheTerm( iArgument1 ) ; // 1�̸� �Ⱓ����(������û�Ұ�), 0�̸� �Ⱓ��(������û����)
		sprintf( szResult, "%s> completed successfully. => 1�̸� �Ⱓ����, 0�̸� ��û���� �Ⱓ��", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/����������" ) )
	{
		g_kSiege.set_Started( iArgument1 ) ; // 1�̸� ������ ����, 0�̸� ������ ���� ����
		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/Ŭ������" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].m_byClan = iArgument2 ;

			MSG_CHANGE_TRIMURITI kChangeMsg ;
			kChangeMsg.wType = MSG_CHANGE_TRIMURITI_ID ;
			kChangeMsg.wPDULength = sizeof(MSG_CHANGE_TRIMURITI)-sizeof(HEADER);
			kChangeMsg.snKeyID = iArgument1 ;
			kChangeMsg.byTrimuriti = pMob[iArgument1].m_byClan ;
			pUser[iArgument1].cSock.AddMessage( (char*)&kChangeMsg, sizeof(MSG_CHANGE_TRIMURITI) ) ;	

			sprintf( szResult, "%s> Successfully", a_pCmd ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER ) ;
		}	
	}
	else if( !strcmp( szCmd, "/������¡������" ) )
	{
		g_kSiege.Print() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/������Ʈ��Ȯ��" ) )
	{// iClanSlot, page
		MSG_SIEGE_ENTRY kEntryMsg ;
		memset( &kEntryMsg, 0 , sizeof(kEntryMsg) ) ;
		kEntryMsg.wType = MSG_SIEGE_ENTRY_ID ;
		kEntryMsg.wPDULength = sizeof(MSG_SIEGE_ENTRY)-sizeof(HEADER);
		kEntryMsg.byDate = 1 ;
		kEntryMsg.byClanSlot = iArgument1 ;
		kEntryMsg.byPage = iArgument2 ;
		const int iElementCount = 8 ;
		int iExpandSlot = iArgument2 * iElementCount ;
		int iEnd = iExpandSlot + iElementCount ;
		int iIndex = 0 ;
		for( ; iExpandSlot < iEnd ; ++iExpandSlot )
		{
			TNGUILD_INFO kGuild ;
			g_kSiege.GetEntry( iArgument1, iExpandSlot, kGuild ) ;
			kEntryMsg.irgGuildID[iIndex] = kGuild.iID ;
			kEntryMsg.dwrgGuildMark[iIndex] = kGuild.dwMark ;
			strncpy( kEntryMsg.szrgGuildName[iIndex], kGuild.szName, SZGUILD_LENGTH ) ;
			++iIndex ;
		}
	}
#ifdef __TN_LOCAL_SERVER_SWITCH__
	else if( !strcmp( szCmd, "/�ְ���" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer] ;
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return ;

		pMob[iMob].ClearCurrentTarget() ;
		pMob[iMob].ClearAttacker( 0 ) ;
		pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 ) ;
	}
	else if( !strcmp( szCmd, "/�ָ���" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer] ;
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return ;

		pMob[iMob].ClearCurrentTarget() ;
		pMob[iMob].ClearAttacker( 0 ) ;
		pMob[iMob].Mode = MOB_PEACE ;
		pMob[iMob].OnFollow( a_iHandle ) ;

		//pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 ) ;
	}
	else if( !strcmp( szCmd, "/��ų�ʱ�ȭ" ) )
	{
		pMob[a_iHandle].ResetSkill() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/LearnSkill" ) )
	{
		pMob[a_iHandle].LearnSkill( iArgument1, iArgument2 ) ; //( short a_sSkillID, int a_iLevel )
		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/���Ⱥ���" ) )
	{
		pMob[a_iHandle].MOB.sMind = iArgument4 ;
		pMob[a_iHandle].MOB.sHeart = iArgument3 ;
		pMob[a_iHandle].MOB.sMuscle = iArgument1 ;
		pMob[a_iHandle].MOB.sNerves = iArgument2 ;

		pMob[a_iHandle].UpdatePoints() ;
		pMob[a_iHandle].NotifyUpdateUIMsg() ;

		sprintf( szResult, "%s> Successfully", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/CastSkill" ) )
	{
		S_CSP_CAST_AREA_SKILL kMsg ;
		memset( &kMsg, 0, sizeof(S_CSP_CAST_AREA_SKILL) ) ;
		kMsg.snSkillID = iArgument1 ;
		kMsg.bySkillLevel = iArgument2 ; // monster ��ų���� ��� 1 level�̴�.

		kMsg.snCasterKeyID = (short)a_iHandle ;				
		kMsg.snMapX = (short)pMob[a_iHandle].TargetX ;
		kMsg.snMapZ = (short)pMob[a_iHandle].TargetY ;
		kMsg.snRes = 1 ;
		kMsg.krgTarget[0].snKeyID = iArgument3 ;
		int iTargetCount = 1 ;
		if( 0 < iArgument4 )
		{
			kMsg.krgTarget[1].snKeyID = iArgument4 ;
			iTargetCount = 2 ;
		}

		int iRes = pMob[a_iHandle].CastSkill( &kMsg, 1 ) ;
		sprintf( szResult, "%s> Res:%d Successfully", a_pCmd, iRes ) ;
	}
	else if( !strcmp( szCmd, "/TestEffect" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	���������� ���� ����
		{	
				TNEFFECT kEffect ;
				kEffect.iID = iArgument2 ;
				kEffect.kFunc.iData = iArgument3 ;
				kEffect.iDuration = 30000 ;
				kEffect.iParam1 = iArgument4 ;
				kEffect.iParam2 = iArgument5 ;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				pMob[iTarget].BroadcastUpdateStatusMsg() ;
				pUser[iTarget].cSock.SendMessage() ;

				sprintf( szResult, "%s> Buffer %d effect to %d", a_pCmd, iArgument2, iArgument1 ) ;
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd ) ;
		}
	}
#endif

	strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));
}



void ControlSystem( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{	
    if( NULL == a_pCmd ) return ;
    if( '/' != a_pCmd[0] ) return ;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( 0 < a_iHandle && MAX_USER > a_iHandle )	if( a_bCheckGM && (eTNClan_GM != pMob[a_iHandle].m_byClan) ) return ;
	#endif

    // ��� command�� log�� �����. �ð� + ���� + �޽���
    int iLength = strlen( a_pCmd ) ;
    if( g_iCmdMaxLength < iLength ) return ;
    
    char szCmd[256] = { 0,0,0, } ;
    char szArgument1[256] = { 0,0,0, } ;
    char szArgument2[256] = { 0,0,0, } ;
	char szArgument3[256] = { 0,0,0, } ;
	char szArgument4[256] = { 0,0,0, } ;
	char szArgument5[256] = { 0,0,0, } ;
	char szArgument6[256] = { 0,0,0, } ;
	char szArgument7[256] = { 0,0,0, } ;
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0, iArgument6 = 0, iArgument7 = 0 ;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5, szArgument6, szArgument7  ) ;
	iArgument1 = atoi( szArgument1 ) ;
	iArgument2 = atoi( szArgument2 ) ;
	iArgument3 = atoi( szArgument3 ) ;
	iArgument4 = atoi( szArgument4 ) ;
	iArgument5 = atoi( szArgument5 ) ;   
	iArgument6 = atoi( szArgument6 ) ;
	iArgument7 = atoi( szArgument7 ) ;

    if( '/' != szCmd[0] ) return ;

	S_SCP_RESP_WHISPER_CHAT kMsg ; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT ;	
	kMsg.byResult = REPLY_ACK_OK ;
	strncpy( kMsg.szName, ".", SZNAME_LENGTH ) ;
	kMsg.byTextColor = 14 ; kMsg.byBgColor = 0 ; // ���߿� ���� ������ �ٲ۴�. ���� �� ���	
	    
    // g_iCmdMaxLength�� �ø� �� �ְ� �ϴ� command�� �ʿ��ϴ�.
    // ���� log ����ϴ� level�� ������ �� �ְ� �ؾ��Ѵ�.
    // �߿��� monster�� ���� �׿��� � reward�� ����� �׻� log�� ���ܾ��Ѵ�.(�̷� ���¿� �°� log ��ºκ� ����)
	#ifdef __TN_TOP_LOG__
	if( 0 <= a_iHandle && MAX_USER > a_iHandle )
	{
		SYSTEMTIME st ;
		GetLocalTime( &st ) ;
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "[%d��%d�� %d��%d��%d��] %s  %s \r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd ) ;
		WriteLog( chBuf, ".\\Log\\ControlSystem.txt" ) ;
	}
	#endif    

  
    // switch/case ���� �׽�Ʈ �غ���.
	char szResult[1024] = { 0,0,0, } ;
	strncpy( szResult, a_pCmd, iLength ) ;
    

	if( !strcmp( szCmd, "/loadfix" ) )
	{
		FILE* fp ;
		fp = fopen( "loadfix.txt", "rt" ) ;
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd ) ;
		}
		else
		{
			char szLine[1024] = { 0,0,0, } ;
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp ) ;
				if(ret == NULL) break ;
				//HelpGameMaster( a_iHandle, szLine ) ;
				ControlSystem( 0, szLine, false ) ;
			}	
			sprintf( szResult, "%s> successful~", a_pCmd ) ;
			fclose( fp ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( iArgument1, iArgument2, iArgument3 ) ;
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f, Item:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect, g_dRwdItemCorrect ) ;
	}
	else if( !strcmp( szCmd, "/cc" ) )
	{
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 ) ;
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] ) ;
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/DropItem" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem ;
			memset( &kItem, 0, sizeof(kItem) ) ;
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1 ;
			kItem.snDurability = eDur_Indestructible ;
			kItem.byCount = 1 ;

			int iCoordX, iCoordY ;
			iCoordX = pMob[a_iHandle].TargetX-1 ;
			iCoordY = pMob[a_iHandle].TargetY-1 ;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeImmunity" ) )	 // mob handle, Immunity
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_iImmunity = iArgument2 ;
			sprintf( szResult, "%s> Immunity:%d", a_pCmd, pMob[iArgument1].m_iImmunity ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeTrimuriti" ) )	// mob id, trimuriti
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 ) // mob all
		{
			pMob[iArgument1].MOB.byTrimuriti = (byte)iArgument2 ;
			pMob[iArgument1].m_byClan = (byte)iArgument2 ;
			pMob[iArgument1].NotifyUpdateUIMsg() ;
			sprintf( szResult, "%s> change the trimuriti of %d to %d", a_pCmd, iArgument1, iArgument2 ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeLevel" ) )
	{
		if( (0 < iArgument1 && MAX_MOB > iArgument1) && ( 0 < iArgument2 && 100 >= iArgument2 ) )
		{
			pMob[iArgument1].MOB.byLevel = iArgument2 ;
			sprintf( szResult, "%s> level:%d", a_pCmd, pMob[iArgument1].MOB.byLevel ) ;
			pMob[iArgument1].NotifyUpdateUIMsg() ;
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeClass" ) )		// mob handle, class1, class2
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].MOB.byClass1 = iArgument2 ;
			pMob[iArgument1].MOB.byClass2 = iArgument3 ;

			pMob[iArgument1].NotifyUpdateUIMsg() ;
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat() ;
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill() ;
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off ;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On ;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventSetting" ) )	// event index, count, cool-down time, sProceedType, duration
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].sCount = iArgument2 ;
			g_krgEventList[iArgument1].uiCoolDownTime = iArgument3 ;
			g_krgEventList[iArgument1].sProceedType = iArgument4 ;
			//g_krgEventList[iArgument1].iDuration = iArgument5 ;

			sprintf( szResult, "%s> event index:%d, count:%d, cool-down time:%d, enable:%d", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].sCount, g_krgEventList[iArgument1].uiCoolDownTime, g_krgEventList[iArgument1].sProceedType ) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask" ) )		// event index, task1, task2, task3, task4
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[0] = iArgument2 ;
			g_krgEventList[iArgument1].srgTask[1] = iArgument3 ;
			g_krgEventList[iArgument1].srgTask[2] = iArgument4 ;
			g_krgEventList[iArgument1].srgTask[3] = iArgument5 ;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask2" ) )	// event index, task5
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[4] = iArgument2 ;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting" ) )		// task index, action ID, param1, param2, param3
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{
			g_krgTaskList[iArgument1].iActionID = iArgument2 ;
			g_krgTaskList[iArgument1].irgParam[0] = iArgument3 ;
			g_krgTaskList[iArgument1].irgParam[1] = iArgument4 ;
			g_krgTaskList[iArgument1].irgParam[2] = iArgument5 ;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting2" ) )		// task index, param4, param5, ����, ����
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{			
			g_krgTaskList[iArgument1].irgParam[3] = iArgument2 ;
			g_krgTaskList[iArgument1].irgParam[4] = iArgument3 ;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				) ;
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount ) ;
		}
	}
	else if( !strcmp( szCmd, "/ChangeEvent" ) )		// monster handle, event ID // �Է��� ������, ���� set�� event ��ȣ�� ������ش�.
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( 0 < iArgument2 ) pMob[iArgument1].MOB.snBagIndex = iArgument2 ; //
			sprintf( szResult, "%s> the event of monster(%d): %d", a_pCmd, iArgument1, pMob[iArgument1].MOB.snBagIndex ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID(handle;%d~%d)", a_pCmd, MAX_USER, MAX_MOB ) ;
		}
	}
	else if( !strcmp( szCmd, "/InitEvent" ) ) // event ������ �ʱ�ȭ �Ѵ�.
	{
		int iEvent = iArgument1; // event index

		if( 0 >= iEvent || eEvent_MaxCount <= iEvent ) sprintf( szResult, "%s> invalid event ID(handle;%d~%d)", a_pCmd, 0, eEvent_MaxCount ) ;
		else
		{
			g_krgEventList[iEvent].uiAvailableTime = 0 ;
			g_krgEventList[iEvent].sClan = eEvntClan_All ;
			g_krgEventList[iEvent].iDuration = eEvntSwitch_On ;

			sprintf( szResult, "%s> the event(%d) is initialized.", a_pCmd, iEvent ) ; 
		}
	}
	else if( !strcmp( szCmd, "/AddEventToScheduler" ) ) // event�� time scheduler�� ����Ѵ�.	// time slot, event
	{
		int iFlag = 1 ;
		if( 0 <= iArgument1 && eTS_MaxSlot > iArgument1 )
		{
			if( 0 <= iArgument2 && eEvent_MaxCount > iArgument2 ) // 0 �϶��� remove
			{
				g_srgTimeSchedule[iArgument1] = iArgument2 ;
				sprintf( szResult, "%s> the event(%d) is registered at slot(%d).", a_pCmd, iArgument2, iArgument1 ) ; 
				iFlag = 0 ;
			}
		}

		if( iFlag ) sprintf( szResult, "%s> failed", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/RemoveEventAtScheduler" ) )
	{
		for( int i = 0 ; i < eTS_MaxSlot ; ++i )
		{
			if( iArgument1 == g_srgTimeSchedule[i] ) g_srgTimeSchedule[i] = 0 ;
		}

		sprintf( szResult, "%s> the event(%d) is removed all.", a_pCmd, iArgument1 ) ; 
	}	
	else if( !strcmp( szCmd, "/ChangeMonsterHP" ) ) // raw data ����		// monster ID, Max HP, HP recovery
	{// Monster ID, HP, HPRecovery
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].nHP = iArgument2 ;
			pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] = iArgument3 ;

			sprintf( szResult, "%s> Monster(idx:%d) Max HP:%d(recv:%d)", a_pCmd, iIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterImmunity" ) ) // raw data ����			// monster ID, Immunity
	{// Monster ID, Immunity
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].nGuildID = iArgument2 ;

			sprintf( szResult, "%s> Monster(idx:%d) Immu:%d", a_pCmd, iIndex, pMonsterData[iIndex].nGuildID ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterARDG" ) )		// monster id, Attack rate, Dodge rate
	{// Monster ID, Attack Rate, Dodge Rate
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].sMuscle = iArgument2 ;
			pMonsterData[iIndex].sNerves = iArgument3 ;
			sprintf( szResult, "%s> Monster(idx:%d) AR:%d, DG:%d", a_pCmd, iIndex, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterAC" ) )		// monster ID, AC
	{// Monster ID, AC
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].sHeart = iArgument2 ;
			sprintf( szResult, "%s> Monster(idx:%d) AC:%d", a_pCmd, iIndex, pMonsterData[iIndex].sHeart ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterMR" ) )		// monster ID, fire, cold, lightning, poison
	{// Monster ID, Fire R, Cold R, Lightning R, Poison R
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = iArgument2 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = iArgument3 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = iArgument4 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = iArgument5 ;

			sprintf( szResult, "%s> Monster(idx:%d) FR:%d, CR:%d, LR:%d, PR:%d ", a_pCmd, iIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillEffect" ) ) 
	{// skill ID, Index of the effect,  Effect ID, function, duration, parameter1, parameter2
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 && 0 <= iArgument2 && 5 > iArgument2 )
		{
			int iIndex = iArgument1 + 500 ;
			pSkillData[iIndex].krgEffect[iArgument2].iID = iArgument3 ;
			pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData = iArgument4 ;
			pSkillData[iIndex].krgEffect[iArgument2].iDuration = iArgument5 ;
			pSkillData[iIndex].krgEffect[iArgument2].iParam1 = iArgument6 ;
			pSkillData[iIndex].krgEffect[iArgument2].iParam2 = iArgument7 ;

			memset( &(pSkillData[iIndex].kDamage), 0, sizeof(pSkillData[iIndex].kDamage) ) ;
			for( int i = 0 ; i < TN_MAX_EFFECT_COUNT ; ++i )
			{
				if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue ;

				if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
				else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
				//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection ;
				if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
					|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash ;

				if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue ;

				switch( pSkillData[iIndex].krgEffect[i].iID )
				{
				case eTNAfn_Damage :
				case eTNAfn_DamageSplash :
					pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_PierceDamage :
					pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					break ;
				case eTNAfn_Fire :
				case eTNAfn_FireSplash :
					pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Cold :
				case eTNAfn_ColdSplash :
					pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Lightning :
				case eTNAfn_LightningSplash :
					pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				case eTNAfn_Poison :
				case eTNAfn_PoisonSplash :
					pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1 ;
					pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2 ;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant ;
					break ;
				} // end of switch
			}

			sprintf( szResult, "%s> Monster Skill(idx:%d) Effect: ID:%d, Func:%d, Dur:%d, Param1:%d, Param2:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].krgEffect[iArgument2].iID, pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData, pSkillData[iIndex].krgEffect[iArgument2].iDuration
				, pSkillData[iIndex].krgEffect[iArgument2].iParam1, pSkillData[iIndex].krgEffect[iArgument2].iParam2				
				) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d or Invalid index of the effect.", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkill" ) )
	{// Skill ID, Attack Speed, Cooldown time, Range, AOE, Allowed Target
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500 ;
			pSkillData[iIndex].iAttackSpeed = iArgument2 ;
			pSkillData[iIndex].iActivateTime = iArgument3 ;
			pSkillData[iIndex].iRange = iArgument4 + 2 ;
			pSkillData[iIndex].iAOE = iArgument5 + 2 ;
			pSkillData[iIndex].iAllowedTargets = iArgument6 ;

			sprintf( szResult, "%s> Monster Skill(idx:%d) AttackSpeed:%d, Cooldown:%d, Range:%d, AOE:%d, AllowedTarget:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].iAttackSpeed, pSkillData[iIndex].iActivateTime, pSkillData[iIndex].iRange, pSkillData[iIndex].iAOE, pSkillData[iIndex].iAllowedTargets
				) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSight" ) )		// id, normal, combat
	{// Monster ID, Normal Sight, Combat Sight
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].byQuest[eMonPrty_NormalSight] = iArgument2 ;
			pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] = iArgument3 ;

			sprintf( szResult, "%s> Monster(idx:%d) Sight(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterPopDelay" ) )	// id, minium pop delay, maxium pop delay
	{// Monster ID, Min delay, Max delay
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex = iArgument2 ;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex = iArgument3 ;

			sprintf( szResult, "%s> Monster(idx:%d) PopDelay(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemCP" ) ) // item combat phase
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1 ;
			pItemData[iIndex].sCombatPhase = iArgument2 ;
			sprintf( szResult, "%s> Item(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pItemData[iIndex].sCombatPhase ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemEffect" ) ) // item combat phase		// item id, effect index, effect id, effect dur
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1 ;
			if( 0 > iArgument2 || 4 < iArgument2 ) return ;
			pItemData[iIndex].krgEffect[iArgument2].iID = iArgument3 ;
			pItemData[iIndex].krgEffect[iArgument2].iDuration = iArgument4 ;
			sprintf( szResult, "%s> Item(idx:%d) effectIdx:%d, effectID:%d, effectDur:%d", a_pCmd, iIndex, iArgument2, pItemData[iIndex].krgEffect[iArgument2].iID, pItemData[iIndex].krgEffect[iArgument2].iDuration ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeSkillCP" ) ) // PC skill combat phase
	{		
		if( HT_PARAMTYPE_PCSKILL_START <= iArgument1 && HT_PARAMTYPE_PCSKILL_END >= iArgument1 )
		{
			int iIndex = 0 ;
			for( int iLevel = 1 ; iLevel < 11 ; ++iLevel )
			{
				iIndex = (iArgument1 - HT_PARAMTYPE_PCSKILL_START )*10 + iLevel ;
				pSkillData[iIndex].sCombatPhase = iArgument2 ;
			}
			sprintf( szResult, "%s> PC Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_PCSKILL_START, HT_PARAMTYPE_PCSKILL_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillCP" ) ) // Monster skill combat phase		// monster skill ID, combat phase
	{		
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500 ;
			pSkillData[iIndex].sCombatPhase = iArgument2 ;

			sprintf( szResult, "%s> Monster Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterImmunity" ) ) // raw data ����			// monster ID, Immunity
	{		
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].nGuildID = iArgument2 ;

			sprintf( szResult, "%s> Monster(idx:%d) Immu:%d", a_pCmd, iIndex, pMonsterData[iIndex].nGuildID ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterARDG" ) )		// monster id, Attack rate, Dodge rate
	{		
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].sMuscle = iArgument2 ;
			pMonsterData[iIndex].sNerves = iArgument3 ;
			sprintf( szResult, "%s> Monster(idx:%d) AR:%d, DG:%d", a_pCmd, iIndex, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterAC" ) )		// monster ID, AC
	{		
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].sHeart = iArgument2 ;
			sprintf( szResult, "%s> Monster(idx:%d) AC:%d", a_pCmd, iIndex, pMonsterData[iIndex].sHeart ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterMR" ) )		// monster ID, fire, cold, lightning, poison
	{		
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = iArgument2 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = iArgument3 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = iArgument4 ;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = iArgument5 ;

			sprintf( szResult, "%s> Monster(idx:%d) FR:%d, CR:%d, LR:%d, PR:%d ", a_pCmd, iIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END ) ;   		    
		}
	}
	else if( !strcmp( szCmd, "/offcsh" ) ) // speed hack ����
	{
		if( 0 == iArgument1 ) g_irgSpeedConsider[5] = 0 ;
		else g_irgSpeedConsider[5] = 1 ;

		sprintf( szResult, "%s> switch on/off :%d(0:on, 1:off)", g_irgSpeedConsider[5] ) ;
	}
	else if( !strcmp( szCmd, "/ChangeSpeedFactor" ) ) // speed hack ����		// time slice, over time, correct, crack point, log level
	{
		if( 0 < iArgument1 )
		{
			g_irgSpeedConsider[0] = iArgument1 ;
			g_irgSpeedConsider[1] = iArgument2 ;
			g_irgSpeedConsider[2] = iArgument3 ;
			g_irgSpeedConsider[3] = iArgument4 ;
			g_irgSpeedConsider[4] = iArgument5 ;
			g_irgSpeedConsider[5] = 0 ;
		}
        
		sprintf( szResult, "%s> time slice:%d, over time:%d, correct:%d, crack point:%d, log level:%d", a_pCmd, g_irgSpeedConsider[0], g_irgSpeedConsider[1], g_irgSpeedConsider[2], g_irgSpeedConsider[3], g_irgSpeedConsider[4] ) ; 
	}
	else if( !strcmp( szCmd, "/LoadSettingAll" ) )
	{
		LoadZoneSettings() ;
		LoadWorldSettings() ;
		//	LoadSettings() ;
		LoadSettingTxl();
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/LoadSettingsMdb" ) )
	{
		LoadSettings() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/LoadSettingTxl" ) )
	{
		LoadSettingTxl() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/LoadZoneSetting" ) )
	{
		LoadZoneSettings() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/LoadWorldSetting" ) )
	{
		LoadWorldSettings() ;
		sprintf( szResult, "%s> Successfully", a_pCmd ) ; 
	}
	else if( !strcmp( szCmd, "/ChangeWorldSetting" ) )		// index, data
	{
		if( 0 <= iArgument1 && 100 > iArgument1 )
		{
			g_irgSetting[iArgument1] = iArgument2 ;

			sprintf( szResult, "%s> g_irgSetting[%d] : %d", a_pCmd, iArgument1, g_irgSetting[iArgument1] ) ; 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~99)", a_pCmd ) ;
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
				) ;
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ; 		    
		}
	}
	else if( !strcmp( szCmd, "/changepos" ) )		// monster id, segment x, segment y
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].SegmentX = iArgument2 ;
			pMob[iArgument1].SegmentY = iArgument3 ;
			pMob[iArgument1].SegmentListX[0] = pMob[iArgument1].SegmentListX[1] = pMob[iArgument1].SegmentListX[2] = pMob[iArgument1].SegmentListX[3] = pMob[iArgument1].SegmentListX[4] = iArgument2 ;
			pMob[iArgument1].SegmentListY[0] = pMob[iArgument1].SegmentListY[1] = pMob[iArgument1].SegmentListY[2] = pMob[iArgument1].SegmentListY[3] = pMob[iArgument1].SegmentListY[4] = iArgument3 ;

			sprintf( szResult, "%s> Now(%d,%d), 0:(%d,%d), 1:(%d,%d), 2(%d,%d), 3(%d,%d), 4(%d,%d)"
				, a_pCmd, pMob[iArgument1].SegmentX, pMob[iArgument1].SegmentY
				, pMob[iArgument1].SegmentListX[0], pMob[iArgument1].SegmentListY[0]
				, pMob[iArgument1].SegmentListX[1], pMob[iArgument1].SegmentListY[1]
				, pMob[iArgument1].SegmentListX[2], pMob[iArgument1].SegmentListY[2]
				, pMob[iArgument1].SegmentListX[3], pMob[iArgument1].SegmentListY[3]
				, pMob[iArgument1].SegmentListX[4], pMob[iArgument1].SegmentListY[4]
				) ;
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ) ; 		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeHalfGrid" ) ) // ok
	{
		if( 31 < iArgument1 )
		{
			g_iHalfGridX = g_iHalfGridY = iArgument1 ;
			g_iViewGridX = g_iViewGridY = g_iHalfGridX + g_iHalfGridY + 1 ;	
		}

		sprintf( szResult, "%s> ViewGrid:%d, HalfGrid:%d", a_pCmd, g_iViewGridX, g_iHalfGridX ) ;
	}
	else if( !strcmp( szCmd, "/ChangePopArea" ) ) // index, start x, end x, start z, end z
	{
		if( 0 > iArgument1 || 4 <= iArgument1 ) return ;
		TrimurityArea.pArea[iArgument1][0].snStartX = iArgument2 ;
		TrimurityArea.pArea[iArgument1][0].snEndX = iArgument3 ;
		TrimurityArea.pArea[iArgument1][0].snStartZ = iArgument4 ;			
		TrimurityArea.pArea[iArgument1][0].snEndZ = iArgument5 ;
	}


	if( 0 < a_iHandle && MAX_USER > a_iHandle )
	{
		strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
		pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
	}
}



void AssistPlayMovie( int a_iHandle, char* a_pCmd ) // play a movie�� ���� 
{
	#ifdef __TN_PLAYMOVIE__
	if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return ;    
    if( NULL == a_pCmd ) return ;
    if( '/' != a_pCmd[0] ) return ;

    // ��� command�� log�� �����. �ð� + ���� + �޽���
    int iLength = strlen( a_pCmd ) ;
    if( g_iCmdMaxLength < iLength ) return ;
    
    char szCmd[128] = { 0,0,0, } ;
	char szArguments[512] = { 0,0,0, } ;
    char szArgument1[256] = { 0,0,0, } ;
    char szArgument2[256] = { 0,0,0, } ;
	char szArgument3[256] = { 0,0,0, } ;
	char szArgument4[256] = { 0,0,0, } ;
	char szArgument5[256] = { 0,0,0, } ;
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0 ;
    
	sscanf( a_pCmd, "%s %s", szCmd, szArguments ) ;    
    if( '/' != szCmd[0] ) return ;
    if( 0 == szCmd[0] ) return ;

	S_SCP_RESP_WHISPER_CHAT kMsg ; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT ;	
	kMsg.byResult = REPLY_ACK_OK ;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH ) ;
	kMsg.byTextColor = 14 ; kMsg.byBgColor = 0 ; // ���߿� ���� ������ �ٲ۴�. ���� �� ���	
	    
    // g_iCmdMaxLength�� �ø� �� �ְ� �ϴ� command�� �ʿ��ϴ�.
    // ���� log ����ϴ� level�� ������ �� �ְ� �ؾ��Ѵ�.
    // �߿��� monster�� ���� �׿��� � reward�� ����� �׻� log�� ���ܾ��Ѵ�.(�̷� ���¿� �°� log ��ºκ� ����)

  
    // switch/case ���� �׽�Ʈ �غ���.
	char szResult[1024] = { 0,0,0, } ;
	strncpy( szResult, a_pCmd, iLength ) ;  

	if( !strcmp( szCmd, "/nokillall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1) ;
		// szArgument1 : on/off

		int iFlag = 0 ;
		if( !strcmp( szArgument1, "on" ) ) iFlag = 1 ;
		else iFlag = 0 ;

		for( int i = 1 ; i < MAX_USER ; ++i ) pMob[i].m_irgFlag[0] = iFlag ;

		sprintf( szResult, "%s> successful~", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/nokill" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 ) ;
		iArgument1 = atoi( szArgument1 ) ; // mob ID
		// argument2 : on/off

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0 ;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1 ;
			else iFlag = 0 ;

			pMob[iArgument1].m_irgFlag[0] = iFlag ;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] ) ;
		}
	}
	else if( !strcmp( szCmd, "/nokill2" ) )
	{
		sscanf( a_pCmd, "%s %s %s", szCmd, szArgument1, szArgument2 ) ;
		// szArgument1 : ĳ���͸�
		// szArgument2 : on/off
		int iArgument1 = GetMOBID( szArgument1 ) ;
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0 ;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1 ;
			else iFlag = 0 ;

			pMob[iArgument1].m_irgFlag[0] = iFlag ;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] ) ;
		}
	}
	else if( !strcmp( szCmd, "/nostun" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1) ;
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
			for( int i = 1 ; i < MAX_USER ; ++i ) pMob[i].m_iImmunity = pMob[i].m_iImmunity | eTNImm_Stun ;
		else 
			for( int i = 1 ; i < MAX_USER ; ++i ) pMob[i].m_iImmunity = 0 ;

		sprintf( szResult, "%s> successful~", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/holdall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1) ;
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
		{
			for( int i = 1 ; i < MAX_USER ; ++i )
			{			
				TNEFFECT kEffect ;
				kEffect.iID = eTNAfn_Hold ;
				kEffect.iDuration = 600000 ;
				kEffect.iParam1 = 100 ;
				kEffect.iParam2 = 0 ;
				pMob[i].AddEffect( kEffect, a_iHandle, a_iHandle ) ;
				pMob[i].BroadcastUpdateStatusMsg() ;
				pUser[i].cSock.SendMessage() ;
			}
		}
		else 
			for( int i = 1 ; i < MAX_USER ; ++i ) pMob[i].m_iImmunity = 0 ;

		sprintf( szResult, "%s> successful~", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/mvspd" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 ) ;
		iArgument1 = atoi( szArgument1 ) ; // move speed

		g_irgFlag[1] = iArgument1 ; // 0 ���� ���� �Է��ϸ� ������ ���·� ���ư���.
		for( int i = 1 ; i < MAX_USER ; ++i )
		{ 
			pMob[i].UpdateSpeed() ;
			//pMob[i].NotifyUpdateStatusMsg() ;
			pMob[i].NotifyUpdateUIMsg() ;
			pUser[i].cSock.SendMessage() ;
		}
		sprintf( szResult, "%s> successful~, g_irgFlag[1]:%d", a_pCmd, g_irgFlag[1] ) ;
	}
	else if( !strcmp( szCmd, "/killpc" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 ) ;
		// szArgument1 : ĳ���͸�
		int iMobID = GetMOBID( szArgument1 ) ;
		if( 0 < iMobID && MAX_USER > iMobID )	//	���������� ���� ����
		{	
			pMob[iMobID].MOB.nHP = 0 ;
			pMob[iMobID].CurrentTarget = 0 ;
			pMob[iMobID].m_eFSM = eTNFsm_Dead ;
			pMob[iMobID].NotifyUpdateStatusMsg() ;
			pMob[iMobID].OnKilled( a_iHandle, 10 ) ;
			sprintf( szResult, "%s> successful~", a_pCmd ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd ) ;
		}	
	}
	else if( !strcmp( szCmd, "/killmonsterall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 ) ;
		// szArgument1 : ĳ���͸�
		for( int i = MAX_USER ; i < MAX_MOB ; ++i )
		{
			KillMonster( i ) ;
			/*
			pMob[i].MOB.nHP = 0 ;
			pMob[i].CurrentTarget = 0 ;
			pMob[i].m_eFSM = eTNFsm_Dead ;
			*/
		}

		sprintf( szResult, "%s> successful~", a_pCmd ) ;
	}
	else if( !strcmp( szCmd, "/hpup" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 ) ;
		iArgument1 = atoi( szArgument1 ) ; // mob ID
		iArgument2 = atoi( szArgument2 ) ; // plus heart points

		if( (0 < iArgument1) && (MAX_USER > iArgument1) && ( 0 < iArgument2 ) )
		{
			pMob[iArgument1].MOB.sHeart += iArgument2 ;
			pMob[iArgument1].UpdatePoints() ;
			pMob[iArgument1].NotifyUpdateUIMsg() ;
			pUser[iArgument1].cSock.SendMessage() ;

			sprintf( szResult, "%s> successful~, pMob[iArgument1].MOB.sHeart:%d", a_pCmd, iArgument1, pMob[iArgument1].MOB.sHeart ) ;
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd ) ;
		}
	}
	else if( !strcmp( szCmd, "/loadscene" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 ) ;
		// szArgument1 : filename

		FILE* fp ;
		fp = fopen( szArgument1, "rt" ) ;
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd ) ;
		}
		else
		{
			char szLine[1024] = { 0,0,0, } ;
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp ) ;
				if(ret == NULL) break ;
				HelpGameMaster( a_iHandle, szLine ) ;
				AssistPlayMovie( a_iHandle, szLine ) ;
				ControlSystem( a_iHandle, szLine, false ) ;
			}	

			sprintf( szResult, "%s> successful~", a_pCmd ) ;
			fclose( fp ) ;
		}
	}

    strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH ) ;
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       

	#endif
}


// altar�� ��ġ�� kala ������ ����. �� �ֽź��� ��� �����ϰ� �ִ��� counting�Ѵ�.
// 5�� �̻� ������ �� �ֽ��� ������ NPC�� �̿��� �� �ִ�.
void MoveKalaRewarder()
{
	//int irgRealm[eRealm_MaxCount] = { 0,0,0, } ;

	for( int i = 0 ; i < eRealm_MaxCount ; ++i ) g_irgRealm[i] = 0 ;

	for( int i = 0 ; i < eKalaAltar_MaxCount ; ++i )
	{
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i ) ;
		if( MAX_USER <= iKalaMonster && MAX_MOB > iKalaMonster )
		{
			if( 0 >= pMob[iKalaMonster].MOB.nHP )
			{
				//g_irgKalaAltar[i] = 0 ;
				
			}
			else ++g_irgRealm[g_krgKalaAltar[i].sTrimuriti] ; // �ֽ��� 1,2,4���� ����.
		}
	}

	for( int i = 0 ; i < eRealm_MaxCount ; ++i )
	{
		if( 4 < g_irgRealm[i] ) // Ư�� �ֽ��� 5�� �̻��� �����Ѵٸ�, �����簡 ���� ������ �ٲ��.
		{
			if( eTNClan_Siva == i )
			{// 275, 159
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Siva ) ;
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Siva ) ;
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Siva ) ;
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Siva].x, g_krgKalaRewarderPosition[0][eTNClan_Siva].y ) ; // �ڱ� �ڽ��� teleport ��Ų��.
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Siva].x, g_krgKalaRewarderPosition[1][eTNClan_Siva].y ) ;
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Siva].x, g_krgKalaRewarderPosition[2][eTNClan_Siva].y ) ; // open a �������� gate
			}
			else if( eTNClan_Vishnu == i )
			{// 343, 852
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Vishnu ) ;
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Vishnu ) ;
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Vishnu ) ;
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[0][eTNClan_Vishnu].y ) ;
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[1][eTNClan_Vishnu].y ) ;
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Vishnu].x, g_krgKalaRewarderPosition[2][eTNClan_Vishnu].y ) ; // open a �������� gate
			}
			else if( eTNClan_Brahma == i )
			{// 871,471
				pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_Brahma ) ;
				pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_Brahma ) ;
				pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_Brahma ) ;
				Teleport( g_irgKalaAltarRewarder[0], g_krgKalaRewarderPosition[0][eTNClan_Brahma].x, g_krgKalaRewarderPosition[0][eTNClan_Brahma].y ) ;
				Teleport( g_irgKalaAltarRewarder[1], g_krgKalaRewarderPosition[1][eTNClan_Brahma].x, g_krgKalaRewarderPosition[1][eTNClan_Brahma].y ) ;
				Teleport( g_irgKalaAltarRewarder[2], g_krgKalaRewarderPosition[2][eTNClan_Brahma].x, g_krgKalaRewarderPosition[2][eTNClan_Brahma].y ) ; // open a �������� gate
			}

			NotifyRvRStatus() ;
			RecordRvRStatus() ;
			return ;
		}
	} // end of for

	// �ֽ����� �߾ӿ� ��ġ�� ��Ų��.
	pMob[g_irgKalaAltarRewarder[0]].set_Trimuriti( eTNClan_GM ) ;
	pMob[g_irgKalaAltarRewarder[1]].set_Trimuriti( eTNClan_GM ) ;
	pMob[g_irgKalaAltarRewarder[2]].set_Trimuriti( eTNClan_GM ) ;
	Teleport( g_irgKalaAltarRewarder[0], 1, 1 ) ;
	Teleport( g_irgKalaAltarRewarder[1], 1, 2 ) ;
	Teleport( g_irgKalaAltarRewarder[2], 1, 3 ) ;

	NotifyRvRStatus() ;
	RecordRvRStatus() ;
}



// �ֽ����� kala ��Ȳ�� ����, �ֽ���(ũ�縶) ���� �ִ� ��� user���� �˷��ش�.
void NotifyRvRStatus()
{
	char szMsg[1024] = { 0,0,0, } ;
	sprintf( szMsg, g_pMessageStringTable[_Post_Kala_Status], g_irgRealm[eTNClan_Brahma], g_irgRealm[eTNClan_Vishnu], g_irgRealm[eTNClan_Siva] ) ;
	if( 5 == g_irgRealm[eTNClan_Brahma] ) strcat( szMsg, g_pMessageStringTable[_Brahma_Collect_Five_Kala]) ;
	else if( 5 == g_irgRealm[eTNClan_Vishnu] ) strcat( szMsg, g_pMessageStringTable[_Vishnu_Collect_Five_Kala]) ;
	else if( 5 == g_irgRealm[eTNClan_Siva] ) strcat( szMsg, g_pMessageStringTable[_Siva_Collect_Five_Kala]) ;

	if( 4 == g_irgRealm[eTNClan_Brahma] ) strcat( szMsg, g_pMessageStringTable[_Brahma_Collect_Four_Kala]) ;
	if( 4 == g_irgRealm[eTNClan_Vishnu] ) strcat( szMsg, g_pMessageStringTable[_Vishnu_Collect_Four_Kala]) ;
	if( 4 == g_irgRealm[eTNClan_Siva] ) strcat( szMsg, g_pMessageStringTable[_Siva_Collect_Four_Kala]) ;
	PostMessageToZone( szMsg ) ;
}



void RecordRvRStatus()
{
	RVR_RECORD kRecord ;
	for( int i = 0 ; i < eKala_MaxCount ; ++i ) kRecord.krgKala[i].iLocation = -1 ; 

	int iIndex = 0 ;
	for( int i = 0 ; i < eKalaAltar_MaxCount ; ++ i )
	{
		if( eKala_MaxCount <= iIndex ) break ; 
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i ) ;
		if( 0 < iKalaMonster )
		{
			kRecord.krgKala[iIndex].iLocation = i ;
			kRecord.krgKala[iIndex].iClan = g_krgKalaAltar[i].sTrimuriti ;
			kRecord.krgKala[iIndex].iID = pMob[iKalaMonster].MOB.snTribe ;
			//if( eTNClan_Brahma == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Brahma ;
			//else if( eTNClan_Vishnu == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Vishnu ;
			//else if( eTNClan_Siva == kRecord.krgKala[iIndex].iClan ) kRecord.krgKala[iIndex].iID = eKala_Siva ;
			++iIndex ;
		}
	}
	
	kRecord.krgRewarder[0].iClan = kRecord.krgRewarder[1].iClan = kRecord.krgRewarder[2].iClan = pMob[g_irgKalaAltarRewarder[0]].m_byClan ;
	kRecord.krgRewarder[0].x = pMob[g_irgKalaAltarRewarder[0]].TargetX ;
	kRecord.krgRewarder[0].y = pMob[g_irgKalaAltarRewarder[0]].TargetY ;
	kRecord.krgRewarder[1].x = pMob[g_irgKalaAltarRewarder[1]].TargetX ;
	kRecord.krgRewarder[1].y = pMob[g_irgKalaAltarRewarder[1]].TargetY ;
	kRecord.krgRewarder[2].x = pMob[g_irgKalaAltarRewarder[2]].TargetX ;
	kRecord.krgRewarder[2].y = pMob[g_irgKalaAltarRewarder[2]].TargetY ;

	FILE* fpInfo = fopen( ".\\Data\\RvRRecord.dat", "wb" ) ;
	if( fpInfo )
	{
		fwrite( &kRecord, sizeof(RVR_RECORD), 1, fpInfo ) ;
		fclose( fpInfo ) ; 
	}
}


void PopMonstersForEvent()
{
	int iZoneID = ServerIndex + 1 ;
	if( eZone_Mandra == iZoneID ) // ���ٶ� ����
	{
		if( eCountryKorea == g_eCountryID )
		{
			if( 0 == g_iWorldID ) // �׼�
			{
				pMob[1000].Summon( 2945, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 455, 270, 0, false ) ;  // 
				pMob[1000].Summon( 2944, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 522, 272, 0, false ) ;  // 
			}

			// ������ � NPC		
			pMob[1000].Summon( 2939, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 897, 259, 0, false ) ;  // 
			pMob[1000].Summon( 2940, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 903, 259, 0, false ) ;  // 
		}


		for( int y = 228 ; y < 261 ; ++y )
		{
			for( int x = 880 ; x < 912 ; ++x )
			{
				g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone ;
			}
		}
	}
	else if( eZone_Katacomb == iZoneID ) // �ϵμ��� zone
	{
		// 4���� ��
		pMob[1000].Summon( 2252, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2/*����*/, 456, 185, 0, false ) ;  // 
		pMob[1000].Summon( 2254, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2, 166,  85, 0, false ) ;  // 
		pMob[1000].Summon( 2253, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2, 567, 185, 0, false ) ;  // 
		pMob[1000].Summon( 2255, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_Neutral, 2, 856,  85, 0, false ) ;  // 

		// trap ����
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 459,  129, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 444,   77, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 432,  101, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 432,  154, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 444,  165, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 388,  132, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 568,  129, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 580,   77, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 592,  101, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 592,  154, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 580,  165, 0, false ) ;  // 
		pMob[1000].Summon( 2258, 1, eTNPrdt_PopRaise, eTNCls_Trap, 0, eTNClan_Aggressive, 2, 636,  132, 0, false ) ;  // 
	}
	else if( eZone_Stronghold == iZoneID ) // �����
	{
		TriggerEvent( 0, 22, 0, 0, 0, 90 ) ; //
		/*
		// Gate keeper�� ��ġ
		pMob[1000].Summon( 2298, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 0, 182, 581, 0, false ) ;  // 
		pMob[1000].Summon( 2299, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 1, 441, 574, 0, false ) ;  // 
		pMob[1000].Summon( 2300, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 2, 188, 842, 0, false ) ;  // 
		pMob[1000].Summon( 2301, 1, eTNPrdt_PopNormal, eTNCls_NPC, 0, eTNClan_GM, 3, 449, 833, 0, false ) ;  // 
		*/
	}
	else if( eZone_Castle == iZoneID ) // īŸ��3, �����
	{
		TriggerEvent( 0, 81, 0, 0, 0, 91 ) ; //

		g_iGambleHorse = pMob[1000].Summon( 2359, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		g_iGambleYut[0] = pMob[1000].Summon( 2362, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		g_iGambleYut[1] = pMob[1000].Summon( 2363, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		g_iGambleYut[2] = pMob[1000].Summon( 2364, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		g_iGambleYut[3] = pMob[1000].Summon( 2365, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		g_iGambleYut[4] = pMob[1000].Summon( 2366, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, eTNClan_GM, 0, 5, 5, 0, false ) ;  // 
		//TriggerEvent( 0, 104, 0, 0, 0, 449 ) ;
	}
	else if( eZone_Cruma == iZoneID ) // ũ�縶���̶��, kala system�� setting����� �Ѵ�.
	{
		//----------------------------------------------------
		// The gate of dungeon(�ֽ� ����)
		//----------------------------------------------------
		g_irgGateOfDungeon[0] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Brahma, 0, 5, 5, 0, false ) ;  // 
		g_irgGateOfDungeon[1] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Vishnu, 0, 6, 5, 0, false ) ;  // 
		g_irgGateOfDungeon[2] = pMob[1000].Summon( 2202, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Siva, 0, 7, 5, 0, false ) ;  // 

		//----------------------------------------------------
		// Gods
		//----------------------------------------------------
		g_irgGod[eTNClan_Brahma] = pMob[1000].Summon( 2932, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Brahma, 0, MAX_GRIDX-1, MAX_GRIDY-1, 0, false ) ;  // 
		g_irgGod[eTNClan_Vishnu] = pMob[1000].Summon( 2933, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Vishnu, 0, MAX_GRIDX-2, MAX_GRIDY-1, 0, false ) ;  // 
		g_irgGod[eTNClan_Siva]   = pMob[1000].Summon( 2938, 1, eTNPrdt_PopFallDown, eTNCls_NPC, 0, eTNClan_Siva,   0, MAX_GRIDX-3, MAX_GRIDY-1, 0, false ) ;  // 

		// bless of god�� ���� �ʱ� ����
		g_krgBlessOfGod[0][eTNClan_Brahma].Init() ;
		g_krgBlessOfGod[0][eTNClan_Brahma].AddCard( 25, 50 ) ;
		g_krgBlessOfGod[0][eTNClan_Brahma].Shuffle() ;
		g_krgBlessOfGod[0][eTNClan_Vishnu].Init() ;
		g_krgBlessOfGod[0][eTNClan_Vishnu].AddCard( 25, 35 ) ;
		g_krgBlessOfGod[0][eTNClan_Vishnu].Shuffle() ;
		g_krgBlessOfGod[0][eTNClan_Siva].Init() ;
		g_krgBlessOfGod[0][eTNClan_Siva].AddCard( 25, 30 ) ;
		g_krgBlessOfGod[0][eTNClan_Siva].Shuffle() ;

				
		bool bLoadKalaRecord = false ;
		if( 0 == g_iWorldID )  // �׼��̸� ������ kala ���� ����� load�Ͽ� �����ϵ��� �Ѵ�.
		{// kala system�� ���� ����� �о�, zone�� setting
			FILE* fpInfo = fopen( ".\\Data\\RvRRecord.dat", "rb" ) ; // �׼��̶�� ��ϵǾ� �ִ� data�� load�Ѵ�.

			if( fpInfo )
			{
				RVR_RECORD kRecord ;
				memset( &kRecord, 0, sizeof(kRecord) ) ;

				fread( &kRecord, sizeof(RVR_RECORD), 1, fpInfo ) ;
				fclose( fpInfo ) ; 

				bLoadKalaRecord = true ;

				for( int i = 0 ; i < 5 ; ++i )
					if( 0 < kRecord.irgEntryCount[i] ) g_irgEntryCount[i] = kRecord.irgEntryCount[i] ;

				int irgKalaCount[4] = { 0,0,0, } ;
				for( int i = 0 ; i < eKala_MaxCount ; ++ i )
				{
					int iLocation = kRecord.krgKala[i].iLocation ;
					if( 0 > iLocation || eKalaAltar_MaxCount <= iLocation ) continue ;
					int iCountIndex = 1 ;
					if( eKala_Brahma == kRecord.krgKala[i].iID ) iCountIndex = 1 ; //++irgKalaCount[1] ;
					else if( eKala_Vishnu == kRecord.krgKala[i].iID ) iCountIndex = 2 ; //++irgKalaCount[2] ;
					else if( eKala_Siva == kRecord.krgKala[i].iID ) iCountIndex = 3 ; //++irgKalaCount[3] ;
					++irgKalaCount[iCountIndex] ;
					if( 3 < irgKalaCount[iCountIndex] ) continue ;

					g_kKalaSystem.InstallKala( kRecord.krgKala[i].iID, kRecord.krgKala[i].iClan, iLocation ) ;

				}

				// ���ڸ��� kala ���� ã�Ƽ�.. ä����� �Ѵ�.
				// 1. �ڽ��� �ֽ� ���ܿ� �ڵ����� setting �ȴ�.
				// 2. �ֽ��� �� ����� ��ġ�� �� �ٴڿ� ����߸���.
				if( 3 > irgKalaCount[1] ) // ����帶
				{
					for( int i = 0 ; i < eKalaAltar_MaxCount ; ++ i )
					{
						if( 3 <= irgKalaCount[1] ) break ;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Brahma == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, i ) ;
							++irgKalaCount[1] ;
						}
					}
				}
				if( 3 > irgKalaCount[2] ) // �񽴴�
				{
					for( int i = 0 ; i < eKalaAltar_MaxCount ; ++ i )
					{
						if( 3 <= irgKalaCount[2] ) break ;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Vishnu == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, i ) ;

							++irgKalaCount[2] ;
						}
					}
				}
				if( 3 > irgKalaCount[3] ) // �ù�
				{
					for( int i = 0 ; i < eKalaAltar_MaxCount ; ++ i )
					{
						if( 3 <= irgKalaCount[3] ) break ;
						if( (-1 == g_kKalaSystem.IsEmptyAltar( i ) ) && eTNClan_Siva == g_krgKalaAltar[i].sTrimuriti )
						{
							g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, i ) ;
	
							++irgKalaCount[3] ;
						}
					}
				}

				// convert
				if( 0 >= kRecord.iWinnerClan || 4 < kRecord.iWinnerClan) // �� ó������ kRecord.iWinnerClan���� 0�̴�.
				{
					kRecord.iWinnerClan = kRecord.krgRewarder[0].iClan ; // �ƹ� winner�� ���ٸ�, GM �ֽ�(10)�� ������ ���� ���̴�.
					if( 0 >= kRecord.iWinnerClan || 4 < kRecord.iWinnerClan) kRecord.iWinnerClan = 0 ;
				}

				g_irgKalaAltarRewarder[0] = pMob[1000].Summon( 2901, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[0][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[0][kRecord.iWinnerClan].y, 0, false ) ;
				g_irgKalaAltarRewarder[1] = pMob[1000].Summon( 2902, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[1][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[1][kRecord.iWinnerClan].y, 0, false ) ;
				g_irgKalaAltarRewarder[2] = pMob[2000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, kRecord.iWinnerClan, 0, g_krgKalaRewarderPosition[2][kRecord.iWinnerClan].x, g_krgKalaRewarderPosition[2][kRecord.iWinnerClan].y, 0, false ) ;
				//g_irgKalaAltarRewarder[2] = pMob[2000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, kRecord.iWinnerClan, 0, 1,3, false ) ;

				RecordRvRStatus() ;
			}
		}

		if( false == bLoadKalaRecord )
		{
			// kala�� 5���̻� ����� �� ������ �� NPC pop
			g_irgKalaAltarRewarder[0] = pMob[1000].Summon( 2901, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 1, 0, false ) ;  // 
			g_irgKalaAltarRewarder[1] = pMob[1000].Summon( 2902, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 2, 0, false ) ;  // 
			g_irgKalaAltarRewarder[2] = pMob[1000].Summon( 2946, 1, eTNPrdt_PopRaise, eTNCls_NPC, 0, eTNClan_NoTrimuritiy, 0, 1, 3, 0, false ) ;  // 

			// kala ���� setting, �� �ֽź��� 3����
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 0 ) ;
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 1 ) ;
			g_kKalaSystem.InstallKala( eKala_Brahma, eTNClan_Brahma, 3 ) ;
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 5 ) ;
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 6 ) ;
			g_kKalaSystem.InstallKala( eKala_Vishnu, eTNClan_Vishnu, 8 ) ;
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 10 ) ;
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 11 ) ;
			g_kKalaSystem.InstallKala( eKala_Siva, eTNClan_Siva, 13 ) ;
		}
	}
}


void RegisterTimeEvent( TNEVENT& a_kEvent, int a_iTriggerTime )
{

}


//----------------------------------------------------------------------
//@Param
//	- a_iUser : event�� trigger �ϴ� ���
//	- a_iEventID : trigger�Ǵ� event
//	- a_iX, a_iY : event�� �߻��� cell ��ġ
//	- a_iNPC : event�� ���� task�� �����ϴ� NPC
//----------------------------------------------------------------------
int TriggerEvent( int a_iUser, int a_iEventID, int a_iX, int a_iY, int a_iNPC, int a_iCaller )
{
	if( 0 >= a_iEventID || eEvent_MaxCount <= a_iEventID ) return eTNRes_EvntInvalidEventNo ;
	if( CurrentTime < g_krgEventList[a_iEventID].uiAvailableTime ) return eTNRes_EvntNotCoolYet ; // ���� cool-down�� �Ϸ���� �ʾҴ�.
	if( eEvntSwitch_Off == g_krgEventList[a_iEventID].iDuration ) return eTNRes_EvntSwitchOff ; // �̿�Ұ��̸� �� �� ����.
	if( eEvntSwitch_On < g_krgEventList[a_iEventID].iDuration && CurrentTime > g_krgEventList[a_iEventID].uiDurationTime )
	{
		g_krgEventList[a_iEventID].iDuration = eEvntSwitch_Off ; // �̿�Ұ��� �����Ѵ�.
		g_krgEventList[a_iEventID].uiDurationTime = 0 ;
		return eTNRes_EvntUseTimeOver ;
	}
	if( 0 <= g_krgEventList[a_iEventID].sClan )
	{
		if( 0 < a_iUser && MAX_USER > a_iUser )
			if( g_krgEventList[a_iEventID].sClan != pMob[a_iUser].m_byClan ) return eTNRes_EvntDiffClan ; // Ư�� clan �������� �����Ǿ� �ִ� ���
	}

	int iStartIndex = 0, iEndIndex = eTask_Sort ;
	if( eEvntPrcdType_Random == g_krgEventList[a_iEventID].sProceedType )
	{
		iStartIndex = rand() % eTask_Sort ; // ��� task ��Ͽ� ���� ä�����־�� �Ѵ�.
		iEndIndex = iStartIndex + 1 ;
	}

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;

	if( eTNSwitch_EventLog & g_iSwitch )
	{
		char chBuf[2048] = { 0,0,0, } ;
		sprintf(chBuf, "[TriggerEvent] %dmm��%ddd %dhh%dms%dss, Event:%d, Caller:%d, User:%d, NPC:%d, Coord(%d,%d) \r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
			, a_iEventID, a_iCaller, a_iUser, a_iNPC, a_iX, a_iY ) ;
		WriteLog( chBuf, ".\\Log\\[Log]EventTriggered.txt" ) ;
	}

	int iProceed = 1 ;
	
	for( int i = iStartIndex ; i < iEndIndex ; ++i )
	{
		int iTaskID = g_krgEventList[a_iEventID].srgTask[i] ;
		if( 0 >= iTaskID || eTask_MaxCount <= iTaskID ) continue ;
		if( 0 >= iProceed ) break ; // ���� ���� ������ ������ ���, ...

		switch( g_krgTaskList[iTaskID].iActionID )
		{
		case eTNAct_ResetChakra :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				pMob[a_iUser].ResetStat() ;
			}
			break ;
		case eTNAct_ResetSkillBook :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				pMob[a_iUser].ResetSkill() ;
			}
			break ;
		case eTNAct_ResetClass :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				pMob[a_iUser].ResetClass() ;
			}
			break ;
		case eTNAct_CheckItemOnly :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				int irgSlot[5] = { -1,-1,-1,-1,-1 } ; // item �˻�/���Ÿ� ���� slot No ���
				int iCount = 0 ;
				iCount = pMob[a_iUser].CheckItem( g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], irgSlot ) ; // �䱸������ �������� ���ϸ� 0�� return
				if( 0 >= iCount ) iProceed = 0 ;
			}
			break ;
		case eTNAct_CheckWeapon :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				int iWeapon = pMob[a_iUser].get_WeaponID();
				if( iWeapon != g_krgTaskList[iTaskID].irgParam[0] )
				{ // check�� item�� ����. NPC�� ���� �Ѵ�.(�ʿ��� �������� �����ϴ�.)
					if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC )
                        pMob[a_iNPC].Speak( 200, a_iUser, 0 ) ;
					return eTNRes_EvntItemNotFound ;
				}
			}
			break;

		case eTNAct_CheckRemoveItem :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				int irgSlot[5] = { -1,-1,-1,-1,-1 } ; // item �˻�/���Ÿ� ���� slot No ���
				int iCount = 0 ;
				iCount = pMob[a_iUser].CheckItem( g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], irgSlot ) ; // �䱸������ �������� ���ϸ� 0�� return
				int iRes = eTNRes_Succeeded ;
				if( iCount < g_krgTaskList[iTaskID].irgParam[1] ) iRes = eTNRes_Failed ;
				if( eTNRes_Succeeded == iRes )
                    iRes = pMob[a_iUser].RemoveItem( g_krgTaskList[iTaskID].irgParam[1], irgSlot ) ; 

				if( iRes )
				{ // check�� item�� ����. NPC�� ���� �Ѵ�.(�ʿ��� �������� �����ϴ�.)
					if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC )
                        pMob[a_iNPC].Speak( 200, a_iUser, 0 ) ;
					return eTNRes_EvntItemNotFound ;
				}
				else
				{ // ã������ item�� �ִ�.
					if( 7205 == g_krgTaskList[iTaskID].irgParam[0] ) // ��Ǫ�� ������
					{
						//SYSTEMTIME st ;
						//GetLocalTime( &st ) ;

						char chBuf[512] = { 0,0,0, } ;
						sprintf(chBuf, "[eTNAct_CheckRemoveItem] %d��%d��%d��%d��%d��, %s unlocked the gate of the king Raphu!!\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
							, pMob[a_iUser].MOB.szName ) ;
						WriteLog( chBuf, ".\\Log\\[Log]BossSystem.txt" ) ;
					}
				}
			}
			break ;
		case eTNAct_DropItem :
			{
				if( HT_PARAMTYPE_ITEM_START <= g_krgTaskList[iTaskID].irgParam[0] && HT_PARAMTYPE_ITEM_END >= g_krgTaskList[iTaskID].irgParam[0] )
				{
					STRUCT_ITEM kItem ;
					memset( &kItem, 0, sizeof(kItem) ) ;
					kItem.snIndex = g_krgTaskList[iTaskID].irgParam[0] - HT_PARAMTYPE_ITEM_START + 1 ;
					kItem.snDurability = pItemData[kItem.snIndex].sMaxDur ;
					kItem.byCount = 1 ;

					int iRes = CreateItem( g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2], &kItem, 0, 0, 0, 0 ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "[eTNAct_DropItem] %d��%d��%d��%d��%d��, A item(%d) is dropped at (%d,%d)! Result:%d(0:Failed, other:Succeeded) \r\n"
						, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, kItem.snIndex
						, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
						, iRes
						 ) ;
					WriteLog( chBuf, ".\\Log\\[Log]ItemDropByEvent.txt" ) ;				
				}
			}
			break ;
		case eTNAct_CheckQuest :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				int iQuestID = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 > iQuestID || MAX_EVENT_FLAG <= iQuestID ) return eTNRes_EvntInvalidQuestID ;
				//if( (0 >= pMob[a_iUser].MOB.byQuest[iQuestID]) || (255 <= pMob[a_iUser].MOB.byQuest[iQuestID] ) )
				if( g_krgTaskList[iTaskID].irgParam[1] != pMob[a_iUser].MOB.byQuest[iQuestID] )
				{
					iProceed = 0 ;
				}
			}
			break ;
		case eTNAct_SetClan :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo ;
				g_krgEventList[iTargetEvent].sClan = pMob[a_iUser].m_byClan ;
				//if( -1 == g_krgTaskList[iTaskID].irgParam[0] ) g_krgTaskList[iTaskID].irgParam[0] = pMob[a_iUser].m_byClan ;
				//else iProceed = pMob[a_iUser].CheckClan( g_krgTaskList[iTaskID].irgParam[0] ) ;
			}
			break ;
		case eTNAct_SetDuration :
			{
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo ;

				g_krgEventList[iTargetEvent].iDuration = g_krgTaskList[iTaskID].irgParam[1] ;
				if( 0 < g_krgEventList[iTargetEvent].iDuration ) g_krgEventList[iTargetEvent].uiDurationTime = CurrentTime + (g_krgTaskList[iTaskID].irgParam[1]*1000) ;
			}
			break ;
		case eTNAct_SetAvailableTime :
			{
				int iTargetEvent = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 > iTargetEvent || eEvent_MaxCount <= iTargetEvent ) return eTNRes_EvntInvalidEventNo ;
				g_krgEventList[iTargetEvent].uiAvailableTime = CurrentTime + (g_krgTaskList[iTaskID].irgParam[1]*1000) ;
			}
			break ;
		case eTNAct_TriggerEvent :
			{
				TriggerEvent( a_iUser, g_krgTaskList[iTaskID].irgParam[0], a_iX, a_iY, a_iNPC, 80 ) ;
			}
			break ;
		case eTNAct_AddEventOnScheduler  :
			{
				int iTimeSlot = g_iTimeSlot + (g_krgTaskList[iTaskID].irgParam[1] / 4) ;
				if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot -= eTS_MaxSlot ;
				if( 0 < g_srgTimeSchedule[iTimeSlot] ) // �ٸ� event�� ����� �Ǿ� �ִٸ�, ...
				{
					int iPrevSlot = iTimeSlot-1 ;
					if( 0 > iPrevSlot ) iPrevSlot = 0 ;
					if( 0 == g_srgTimeSchedule[iPrevSlot] ) g_srgTimeSchedule[iPrevSlot] = g_krgTaskList[iTaskID].irgParam[0] ;
					else
					{
						int iCount = 0 ;
						while(0 < g_srgTimeSchedule[iTimeSlot])
						{
							if( eTS_MaxSlot < iCount ) break ;
							++iCount ;
							++iTimeSlot ;
							if( eTS_MaxSlot <= iTimeSlot ) iTimeSlot = 0 ;
						}
						g_srgTimeSchedule[iTimeSlot] = g_krgTaskList[iTaskID].irgParam[0] ;
					}
				}
				else g_srgTimeSchedule[iTimeSlot] = g_krgTaskList[iTaskID].irgParam[0] ;
			}
			break ;
		case eTNAct_RemoveEventOnScheduler :
			{
				for( int i = 0 ; i < eTS_MaxSlot ; ++i )
					if( g_krgTaskList[iTaskID].irgParam[0] == g_srgTimeSchedule[i] ) g_srgTimeSchedule[i] = 0 ;
			}
			break ;

		case eTNAct_AddInstantEventOnScheduler :
			{
				unsigned int uiGap = g_krgTaskList[iTaskID].irgParam[1] * 1000 ;
				g_kScheduler.AddSchedule( CurrentTime, uiGap, 0, g_krgTaskList[iTaskID].irgParam[0] ) ;
			}
			break ;

		case eTNAct_Speak :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle ;
				pMob[a_iNPC].Speak( g_krgTaskList[iTaskID].irgParam[0], a_iUser, 0 ) ;
			}
			break ;
		case eTNAct_Help :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle ;
				pMob[a_iNPC].CallOthers( eTNGrp_Help, a_iUser ) ;
			}
			break ;
		case eTNAct_Link :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle ;
				pMob[a_iNPC].CallOthers( eTNGrp_Link, a_iUser ) ;
			}
			break ;
		case eTNAct_Flee :
			{
				if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle ;
				pMob[a_iNPC].LetsFlee( pMob[a_iNPC].CurrentTarget ) ;
			}
			break ;

		case eTNAct_UseSkill :
			{ // Ư�� NPC�� event�� trigger�� user���� skill�� ����. ���� user�� npc handle�� ��� �����ؾ��Ѵ�.
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				short sSkillID = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 < sSkillID )
				{
					if( MAX_USER > a_iNPC || MAX_MOB <= a_iNPC ) return eTNRes_EvntInvalidNPCHandle ;
					if( pMob[a_iNPC].set_Skill( sSkillID ) ) return eTNRes_EvntInvalidSkillID ;
					pMob[a_iNPC].CurrentTarget = a_iUser ;
					pMob[a_iNPC].UseSkill() ;
				}
			}
			break ;
		case eTNAct_ReturnPrevPos :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) continue ;
				HS2D_COORD kPos, kDest ;
				kPos.x = pMob[a_iUser].TargetX ;
				kPos.y = pMob[a_iUser].TargetY ;
				kDest.x = pMob[a_iUser].LastX ;
				kDest.y = pMob[a_iUser].LastY ;
				
				int iWidth, iHeight ;
				int iCorrect = 1 ;
				int iDist = CalDistance( kPos, kDest, 0, 0 ) ;
				if( 2 > iDist ) iCorrect = 4 ; // ��ġ�� 4�� �ڷ�
				else if( 3 > iDist ) iCorrect = 3 ; // ��ġ�� 3�� �ڷ�
				else if( 4 > iDist ) iCorrect = 2 ; // ��ġ�� 2�� �ڷ�

				if( 1 < iCorrect )
				{
					iWidth = kDest.x - kPos.x ;					
					iHeight = kDest.y - kPos.x ;
					iWidth *= iCorrect ;
					iHeight *= iCorrect ;
					kDest.x += iWidth ;
					kDest.y += iHeight ;
				}

				if	( kDest.x<0 || kDest.y<0 || kDest.x>MAX_GRIDX || kDest.y>MAX_GRIDY ) continue ;

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm)-sizeof(HEADER);
				nm.TargetX = kDest.x ; nm.TargetY = kDest.y ;
				nm.dwKeyID = a_iUser;
				nm.PosX=0; nm.PosY=0; nm.Direction = 0; 
				nm.Effect = 6 ; // knock-back motion

				pUser[a_iUser].cSock.AddMessage( (char*)&nm, sizeof(nm) ) ;
				pUser[a_iUser].cSock.SendMessage() ;
			}
			break ;
		case eTNAct_KnockBack :
			break ;
		case eTNAct_Teleport :
			{ // player�� Ư�� cell�� ��ġ�� �ϰԵǸ�, target���� �Ÿ��� ������, �̵�(teleport type)���� ó���� �Ѵ�.
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) return eTNRes_EvntInvalidUserHandle ;
				//if( 0 < g_krgTaskList[iTaskID].irgParam[0] ) // Ư�� clan�� ����Ѵ�. 0�� ���� ��� permit
				//	if( g_krgTaskList[iTaskID].irgParam[0] != pMob[a_iUser].m_byClan ) return ;

				HS2D_COORD kCell, kDest ;
				kCell.x = a_iX ;
				kCell.y = a_iY ;
				kDest.x = g_krgTaskList[iTaskID].irgParam[1] ; //pMob[a_iUser].TargetX ;
				kDest.y = g_krgTaskList[iTaskID].irgParam[2] ; // pMob[a_iUser].TargetY ;
				int iDist = CalDistance( kCell, kDest, 0, 0 ) ;
				if( 100 >= iDist )
				{
					pUser[a_iUser].nPreX = kDest.x;
					pUser[a_iUser].nPreY = kDest.y;

					MSG_Action nm; nm.wType = _MSG_Action;
					nm.wPDULength = sizeof(nm)-sizeof(HEADER);
					nm.TargetX=kDest.x ; nm.TargetY= kDest.y ;
					nm.dwKeyID = a_iUser;
					nm.PosX=0; nm.PosY=0; nm.Direction = 0; 
					nm.Effect = g_krgTaskList[iTaskID].irgParam[0] ; // �̵� ����, // 0:�ɱ�  1:����  2:�ȱ�  3:�ٱ�  4:����  5:�ڷ���Ʈ,	6:�и���(knock-back), 7:�̲�������(�̵��ִϾ���)  8:����, 9:�λ�, 10:���� 

					pUser[a_iUser].cSock.AddMessage( (char*)&nm, sizeof(nm) ) ;
					pUser[a_iUser].cSock.SendMessage() ;
				}
				else Teleport( a_iUser, kDest.x, kDest.y ) ;
			}
			break ;
		case eTNAct_RangeUp :
			{

			}
			break ;
		case eTNAct_Mine :
			{// mine�� ��޿� ���� event ID�� Ʋ����. 5����� mine�� �����Ѵٸ�, event ID�� 5�����̸� �� ���̴�.

			}
			break ; 
		case eTNAct_PopMonster :
			{// 0:monster ID, 1:x, 2:y, 3:pop type, 4:direction, 5:clan
				int iSummoner = 0 ;
				int iClan = g_krgTaskList[iTaskID].irgParam[5] ;
				if( eTNClan_NoTrimuritiy >= iClan || eTNClan_NPC < iClan ) iClan = eTNClan_Aggressive ;
				if( MAX_USER <= a_iNPC && MAX_MOB > a_iNPC ) iSummoner = a_iNPC ;
				int iMonsterHandle = pMob[iSummoner].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, g_krgTaskList[iTaskID].irgParam[3], eTNCls_Warrior, 0, iClan, g_krgTaskList[iTaskID].irgParam[4] , g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2], pMob[iSummoner].CurrentTarget, false ) ;
			}
			break ;
		case eTNAct_PopMonster2 :
			{// 0: monster ID, 1:class1, 2:clan, 3:direction, 4:x, 5:y
				int iMonsterHandle = pMob[1000].Summon( g_krgTaskList[iTaskID].irgParam[0], 1, eTNPrdt_PopNormal, g_krgTaskList[iTaskID].irgParam[1], 0, g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3] , g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5], 0, false ) ;
			}
			break ;
		case eTNAct_KillMonster : // ��ǥ ������ �ִ� Ư�� ID ���͸� ���δ�.
			{
				int iPosX = g_krgTaskList[iTaskID].irgParam[0] ;
				int iPosY = g_krgTaskList[iTaskID].irgParam[1] ;

				for( int y = iPosY - 1 ; y < iPosY + 1 ; ++y )
				{
					for( int x = iPosX - 1 ; x < iPosX + 1 ; ++x )
					{
						if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue ;
						int iMonsterHandle = pMobGrid[y][x] ;
						if( MAX_USER > iMonsterHandle || MAX_MOB <= iMonsterHandle ) continue ;
						if( pMob[iMonsterHandle].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[2] )
						{
							KillMonster( iMonsterHandle ) ;
						}
					}			
				}
			}
			break ;
		case eTNAct_KillMonsterAll : // Ư�� ID�� ���͸� ��� ���δ�.
			{//0:tribe
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						KillMonster( i ) ;
					}
				}
			}
			break ;
		case eTNAct_ChangeClanByTribe :
			{
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						pMob[i].MOB.byTrimuriti = pMob[i].m_byClan = g_krgTaskList[iTaskID].irgParam[1] ;
						pMob[i].ClearCurrentTarget() ;
						pMob[i].ClearAttacker( 0 ) ;
						pMob[i].Mode = MOB_PEACE ;
					}
				}
			}
			break ;

		case eTNAct_ChangeClanByTribe2 :
			{
				int iSiege = g_kSiege.get_Started();
				if( iSiege ) continue;

				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						pMob[i].MOB.byTrimuriti = pMob[i].m_byClan = g_krgTaskList[iTaskID].irgParam[1] ;
						pMob[i].ClearCurrentTarget() ;
						pMob[i].ClearAttacker( 0 ) ;
						pMob[i].Mode = MOB_PEACE ;
					}
				}
			}
			break ;

		case eTNAct_AffectAEffectToClanMonsters :
			{
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue ;
					if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue ;

					if( pMob[i].m_byClan == g_krgTaskList[iTaskID].irgParam[0] ) 
					{
						TNEFFECT kEffect ;
						kEffect.iID = g_krgTaskList[iTaskID].irgParam[1] ;
						kEffect.kFunc.iData = g_krgTaskList[iTaskID].irgParam[2] ;
						kEffect.iDuration = g_krgTaskList[iTaskID].irgParam[3] ;
						kEffect.iParam1 = g_krgTaskList[iTaskID].irgParam[4] ;
						kEffect.iParam2 = g_krgTaskList[iTaskID].irgParam[5] ;
						pMob[i].AddEffect( kEffect, i, i ) ;
						pMob[i].BroadcastUpdateStatusMsg() ;
					}
				}
			}
			break ;
		case eTNAct_GambleResetMomey:
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleMoney Reset \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_ResetMoney();
			}	break;
		case eTNAct_GambleBetOn:		//	������ ���ý���
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleBetOn \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_SetBet(1);
				g_Yut.HT_Init();
			}	break;
		case eTNAct_GambleBetOff:		//	������ ��������
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleBetOff \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				g_Yut.HT_SetBet(0);
			}	break;
		case eTNAct_GambleSetOn:		//	������ ���ý���
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleSetOn \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleSetOff:		//	������ ��������
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleSetOff \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleResultOn:		//	������ �������
			{
				g_Yut.HT_ShareMoney();
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleResultOn \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GambleResultOff:	//	������ �������
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GambleResultOff \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
			}	break;
		case eTNAct_GamblePlayOn:		//	������ ��������(�������� �����Ų��)
			{
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GamblePlayOn \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
				for(int x=653; x<678; x++)
				{
					for(int y=407; y<432; y++)
					{
						if(pMobGrid[y][x]==0) continue;
						sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
						TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
					}
				}
#endif	//	#ifdef __YUT_LOG__
				//g_Yut.m_iYutID = 


				g_Yut.HT_SetPlay(1);
				YutCounter = 225;		//	15�� ���� ����ȴ�.
				//YutTimer = 0;
			}	break;
		case eTNAct_GamblePlayOff:		//	������ ��������
			{
				g_Yut.HT_SetPlay(0);
#ifdef __YUT_LOG__
				sprintf(temp, "gamble GamblePlayOff \r\n"); TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
				for(int x=653; x<678; x++)
				{
					for(int y=407; y<432; y++)
					{
						if(pMobGrid[y][x]==0) continue;
						sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
						TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
					}
				}
#endif	//	#ifdef __YUT_LOG__

			}	break;
		case eTNAct_GambleBroadcast:	//	������ ���� ����
			{
				short snX,snY=0;

				WORD wMsg = g_krgTaskList[iTaskID].irgParam[0]; 
				WORD wNPC = g_krgTaskList[iTaskID].irgParam[1];

#ifdef __YUT_LOG__
				sprintf(temp, "Yut_Broadcast NPCID:%d, msgID:%d \r\n", wNPC, wMsg);
				TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__

				if(!g_ParamMgr.HT_bGetNPCPosition( wNPC, &snX, &snY )) continue;		//	�ش� NPC������ ���� ���Ұ��.

				MSG_Broadcast sm; sm.wType = _MSG_Broadcast;						//	���� �����ǰ���
				sm.byMsgType = MESSAGE_EXTRA;
				sm.byTextColor = 12;
				sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER);
				strncpy(sm.szMsg, g_pMessageStringTable[wMsg], sizeof(sm.szMsg));
				strncpy(sm.szName, g_pMessageStringTable[_YutNPCName], sizeof(sm.szName)); 
				SendToAll((MSG_STANDARD*)&sm);

				S_SCP_NOTIFY_CHAT nm;	nm.wType = SCP_NOTIFY_CHAT;					//	NPC Chat
				nm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
				nm.nID=10000+wNPC;													//	NPC + 10000(NPC�� ��� +10000�ϱ����)
				nm.byTextColor=12; nm.byBgColor = 0; nm.byTrimuriti=0;				//	���� �������� ����
				strncpy(nm.szMsg, g_pMessageStringTable[wMsg], sizeof(nm.szMsg));
				GridMulticast(snX, snY, (MSG_STANDARD*)&nm, 0, 200);
			}	break;
		case etnAct_MoveGambleHorse :
			{
				Teleport( g_iGambleHorse, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1] ) ;
			}
			break ;
		case eTNAct_KillMonsterWithClan : // Ư�� clan monster���� ��� ���δ�.
			{// 0:clan
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue ;
					if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue ;

					if( pMob[i].m_byClan == g_krgTaskList[iTaskID].irgParam[0] ) 
					{
						KillMonster( i ) ;
					}
				}
			}
			break ;
		case eTNAct_KillPC :
			{
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) continue ;
				pMob[a_iUser].MOB.nHP = 0 ;
				pMob[a_iUser].CurrentTarget = 0 ;
				pMob[a_iUser].m_eFSM = eTNFsm_Dead ;
				pMob[a_iUser].NotifyUpdateStatusMsg() ;

				pMob[a_iUser].OnKilled( a_iNPC, 8 ) ;
			}
			break ;
		case eTNAct_Vanish :
			{
				KillMonster( a_iNPC );
			}
		case eTNAct_KillMonsterInSquare :
			{
				int iStartX, iEndX, iStartY, iEndY ;

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue ;
						if( eTNCls_NPC == pMob[iMob].MOB.byClass1 ) continue ;
						if( eTNCls_Event == pMob[iMob].MOB.byClass1 ) continue ;

						KillMonster( iMob ) ;
					}
				}
			}
			break ;

		case eTNAct_KillAll :
			{
				int iStartX, iEndX, iStartY, iEndY ;

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_MOB <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.
						if( eTNCls_NPC == pMob[iMob].MOB.byClass1 ) continue ;
						if( eTNCls_Event == pMob[iMob].MOB.byClass1 ) continue ;

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							pMob[iMob].MOB.nHP = 0 ;
							pMob[iMob].NotifyUpdateStatusMsg() ;

							pMob[iMob].OnKilled( a_iNPC, 9 ) ;
						}
						else
						{
							KillMonster( iMob ) ;
						}
					}
				}
			}
			break ;
		case eTNAct_CheckKalaSystem :
			{
				CheckKalaSystem() ;
			}
			break ;
		case eTNAct_PrintKalaCoreInfo :
			{
				MoveKalaRewarder() ;
			}
			break ;
		case eTNAct_KickOut :
			{
				int iStartX, iEndX, iStartY, iEndY ;

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}
				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_MOB <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{// save �������� ���ư���. �������� zone�� �����ϱ� user���� ��� ������ �������� �Ѵ�.
							ReturnPCToSaveZone( iMob ) ;
						}
					}
				}
			}
			break ;
		case eTNAct_CountRealmEntry :
			{ // ������ �ֽ��� �����ο����� ����Ѵ�.
				int iCountCheckSum = 10000 ;
				if( (iCountCheckSum < g_irgEntryCount[eTNClan_Siva]) && (iCountCheckSum < g_irgEntryCount[eTNClan_Brahma]) && (iCountCheckSum < g_irgEntryCount[eTNClan_Vishnu]) )
				{
					g_irgEntryCount[eTNClan_Siva] -= iCountCheckSum ;
					g_irgEntryCount[eTNClan_Brahma] -= iCountCheckSum ;
					g_irgEntryCount[eTNClan_Vishnu] -= iCountCheckSum ;
				}

				for( int i = 1 ; i < MAX_USER ; ++i )
				{
					if( MOB_EMPTY == pMob[i].Mode ) continue ;
					if( USER_PLAY == pUser[i].Mode )
					{
						int iClan = pMob[i].m_byClan ;
						if( 1 > iClan || 4 < iClan ) continue ;
						++g_irgEntryCount[iClan] ;
					}
				}

				g_irgEntryCount[0] = g_irgEntryCount[eTNClan_Brahma] + g_irgEntryCount[eTNClan_Vishnu] + g_irgEntryCount[eTNClan_Siva] ;

				#ifdef __TN_EMERGENCY_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;

					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "%[dyy%dmm%ddd %dhh%dmi%dss] eTNAct_CountRealmEntry >  Total: %d, brama:%d, vishunu:%d, siva:%d \r\n"
						, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, g_irgEntryCount[0], g_irgEntryCount[eTNClan_Brahma], g_irgEntryCount[eTNClan_Vishnu], g_irgEntryCount[eTNClan_Siva] ) ;
					WriteLog( chBuf, ".\\Log\\[Log]RvREntry.txt" ) ;
				}
				#endif //__TN_EMERGENCY_LOG__
			}
			break ;
		case eTNAct_PostMessageToZone :
			{
				if( 0 > g_krgTaskList[iTaskID].irgParam[0] || MAX_STRING <= g_krgTaskList[iTaskID].irgParam[0] ) break ;
				PostMessageToZone( g_pMessageStringTable[g_krgTaskList[iTaskID].irgParam[0]], eTNClr_White, eTNClr_BG, g_krgTaskList[iTaskID].irgParam[0] ) ;
			}
			break ;
		case eTNAct_PostMessageToWorld :
			{
				if( 0 > g_krgTaskList[iTaskID].irgParam[0] || MAX_STRING <= g_krgTaskList[iTaskID].irgParam[0] ) break ;
				PostMessageToWorld( g_pMessageStringTable[g_krgTaskList[iTaskID].irgParam[0]], eTNClr_White, eTNClr_BG, g_krgTaskList[iTaskID].irgParam[0] ) ;
			}
			break ;
		case eTNAct_RecordName :
			{// Ư�� �簢 ���� ���� ��� PC name�� ����Ѵ�.
				int iStartX, iEndX, iStartY, iEndY ;
				// Param0 : �� X
				// Param1 : ���� X
				// Param2 : �� Y
				// Param3 : ���� Y
				// Param4 : ��ǥ X
				// Param5 : ��ǥ Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] Record PCs in the event(%d)\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, a_iEventID ) ;
					WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
				}
				#endif

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						if( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue ;
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� skip

						if( (eTNMob_PC == pMob[iMob].m_eMobType) && (0 < pMob[iMob].MOB.nHP) )
						{
							#ifdef __TN_TOP_LOG__
							{
								char chBuf[256] = { 0,0,0, } ;
								sprintf(chBuf, "\t- %s\r\n", pMob[iMob].MOB.szName ) ;
								WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
							}
							#endif
						}
					}
				}
			}
			break ;
		case eTNAct_RecordPCNameInZone :
			{
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[256] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n[%dMM%dDD %dHH%dMS%dSS] eTNAct_RecordPCNameInZone>\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
				}
				#endif

				for( int iPC = 0 ; iPC < MAX_USER ; ++iPC )
				{
					if( USER_PLAY != pUser[iPC].Mode ) continue ;
					if( eTNClan_GM == pMob[iPC].m_byClan ) continue ;
					if( eTNCls_NPC == pMob[iPC].MOB.byClass1 ) continue ;

					#ifdef __TN_TOP_LOG__
					{
						char chBuf[256] = { 0,0,0, } ;
						sprintf(chBuf, "\t- %s, HP:%d \r\n", pMob[iPC].MOB.szName, pMob[iPC].MOB.nHP ) ;
						WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
					}
					#endif
				}
			}
			break ;

		case eTNAct_PostStrongholdOwner :
			{
				char szMsg[1024] = { 0,0,0, } ;

				// �� 2���� ������ 8���� stronghold�� �ִ�. �ϵ��ʿ���� 2���� �ִ�. ��� �̸��� �������� �Ѵ�.
				// �θ��� �����̶�� �׷��µ�, �������� �ϳ��� zone�� �ϳ��� �������� �����ϰ� �־��µ�
				// ����� �ΰ��� zone�� �θ��� �����̶�� �θ��� �������� �߻��Ѵ�.
				if( 15 == ServerIndex ) // �θ��� 1����
				{
					if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthEasternStronghold] ) ;
						else
						{
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthEasternStronghold], g_krgStronghold[eStronghold_Northeast].szGuildName/*����*/ ) ;
						}						
					}
					else if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthWesternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthWesternStronghold], g_krgStronghold[eStronghold_Northwest].szGuildName/*����*/ ) ;
						}
					}
					else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthEasternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthEasternStronghold], g_krgStronghold[eStronghold_Southeast].szGuildName/*����*/ ) ;
						}
					}
					else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthWesternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthWesternStronghold], g_krgStronghold[eStronghold_Southwest].szGuildName/*����*/ ) ;
						}
					}
				}
				else if( 16 == ServerIndex ) // �θ��� 2����
				{
					if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthEasternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthEasternStronghold], g_krgStronghold[eStronghold_Northeast].szGuildName/*����*/ ) ;
						}						
					}
					else if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Northwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1NorthWesternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1NorthWesternStronghold], g_krgStronghold[eStronghold_Northwest].szGuildName/*����*/ ) ;
						}
					}
					else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southeast].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthEasternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthEasternStronghold], g_krgStronghold[eStronghold_Southeast].szGuildName/*����*/ ) ;
						}
					}
					else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( 0 >= g_krgStronghold[eStronghold_Southwest].iOwner )
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsNotCaptured], g_pMessageStringTable[_1SouthWesternStronghold] ) ;
						else
						{
							//g_krgStronghold[eStronghold_Northeast].iOwner �� ���� guild ID�� �˻��ؾ� �Ѵ�.
							sprintf( szMsg, g_pMessageStringTable[_StrongholdIsOccupied], g_pMessageStringTable[_1SouthWesternStronghold], g_krgStronghold[eStronghold_Southwest].szGuildName/*����*/ ) ;
						}
					}
				}

				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;

					char chBuf[2048] = { 0,0,0, } ;
					sprintf(chBuf, "[eTNAct_PostStrongholdOwner] %d��%d��%d��%d��%d��, MSG(ID:%d) : %s\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, g_krgTaskList[iTaskID].irgParam[0], szMsg ) ;
					WriteLog( chBuf, ".\\Log\\[Log]EventTriggered.txt" ) ;
				}

				PostMessageToWorld( szMsg ) ;
			}
			break ;				   
		case eTNAct_KillKingAtChaturangka : // kill a king
			{
				for( int iHandle = MAX_USER ; iHandle < MAX_MOB ; ++iHandle )
				{
					if( (2113 == pMob[iHandle].MOB.snTribe) || (2112 == pMob[iHandle].MOB.snTribe) ) // 
					{
						if( 0 < pMob[iHandle].MOB.nHP ) // alive ���¿� �ִ� ���� ���� ���� �α׿� �����.
						{
							pMob[iHandle].MOB.nHP = 0 ; 
							pMob[iHandle].CurrentTarget = 0 ;
							DeleteMob( iHandle, 125 ) ;

							pMob[iHandle].Mode = MOB_EMPTY ;
							pMobGrid[pMob[iHandle].TargetY][pMob[iHandle].TargetX] = 0 ;


							#ifdef __TN_TOP_LOG__
							{
								SYSTEMTIME st ;
								GetLocalTime( &st ) ;
								char chBuf[512] = { 0,0,0, } ;
								sprintf(chBuf, "\r\n\n[%dmm%ddd %dhh%dms%dss] kill the king \r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
								WriteLog( chBuf, ".\\Log\\[Log]BossSystem.txt" ) ;
							}
							#endif    
						}
					}					
				}
			}
			break ;
		case eTNAct_CloseKingRoomAtChaturangka : // close �������� �չ�
			{// ��� user�� ƨ�ܳ��� �Ѵ�. -> ���������� �� portal field�� teleport �����ش�. or �ֽ��� �������� ������?
				int iStartX, iEndX, iStartY, iEndY ;
				iStartX = 371 ;
				iEndX = 523 ;
				iStartY = 497 ;
				iEndY = 652 ;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n\n[%dmm%ddd %dhh%dms%dss] Close the zone of the king!\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\[Log]BossSystem.txt" ) ;
				}
				#endif    
				int irgPopPos[4][2]  = { 868, 815, 833, 813, 833, 848, 868, 851 } ;
				int iIndex = 0 ;
				
				for( int y = iStartY ; y < iEndY ; ++y )
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ;

						iIndex = rand() % 4 ;
						Teleport( iMob, irgPopPos[iIndex][0], irgPopPos[iIndex][1] ) ;
					}
			}
			break ;
		case eTNAct_CheckMonster2 : // Ư�� ID�� ���Ͱ� ���� ������ �ִ��� �ľ��Ѵ�.
			{
				int iCount = 0 ;
				for( int iMob = MAX_USER ; iMob < MAX_MOB ; ++iMob )
				{
					if( pMob[iMob].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[0] )
					{
						if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iCount ;
					}
				}		

				if( 0 == iCount ) iProceed = 0 ;
			}
			break ;

		case eTNAct_CountMonster :
			{
				int iStartX, iEndX, iStartY, iEndY ;

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				int iMonsterCount = 0 ;
				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue ;
						if( eTNMob_NPC == pMob[iMob].m_eMobType )
						{
							if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iMonsterCount ;
						}
					}
				}

				if( g_krgTaskList[iTaskID].irgParam[4] < iMonsterCount )
				{
					iProceed = 0 ;
				}
			}
			break ;
	   
		case eTNAct_CountMonsterByTribe :
			{
				int iStartX, iEndX, iStartY, iEndY ;

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				int iMonsterCount = 0 ;
				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( MAX_USER > iMob || MAX_MOB <= iMob ) continue ;
						if( eTNMob_NPC == pMob[iMob].m_eMobType )
						{
							if( g_krgTaskList[iTaskID].irgParam[4] == pMob[iMob].MOB.snTribe )
								if( (0 < pMob[iMob].MOB.nHP) && (MOB_EMPTY!=pMob[iMob].Mode) ) ++iMonsterCount ;
						}
					}
				}

				if( g_krgTaskList[iTaskID].irgParam[5] < iMonsterCount )
				{
					iProceed = 0 ;
				}
			}
			break ;

		case eTNAct_TeleportAll :
			{ // Ư�� �簢 ���� ���� ��� PC�� ��ǥ�������� teleport��Ų��.
				int iStartX, iEndX, iStartY, iEndY ;
				// Param0 : �� X
				// Param1 : ���� X
				// Param2 : �� Y
				// Param3 : ���� Y
				// Param4 : ��ǥ X
				// Param5 : ��ǥ Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.

						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							Teleport( iMob, g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] ) ;
							/*
							if( 0 >= pMob[iMob].MOB.nHP )
							{ // �׾� �ִ� ĳ���ʹ� save zone���� ������.
								MSG_MoveOtherZone sm; sm.wType=_MSG_MoveOtherZone;
								sm.byType=CONNECT_TYPE_PUSTICA; sm.snPositionID= pMob[iMob].m_snSaveNPC;
								pUser[iMob].cSock.SendOneMessage((char*)&sm, sizeof(sm));
							}
							else
							{ // PC�� �̵���Ų��.
								Teleport( iMob, g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] ) ;
							}
							*/
						}
					}
				}
			}
			break ;
		case eTNAct_ReturnPCToSaveZone :
			{
				for( int i = 1 ; i < MAX_USER ; ++i )
				{
					if( eTNClan_GM == pMob[i].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.
					ReturnPCToSaveZone( i ) ;
				}
			}
			break ;
		case eTNAct_ReturnToSaveZone :
			{
				//SYSTEMTIME st ;
				//GetLocalTime( &st ) ;

				/*
				char chBuf2[512] = { 0,0,0, } ;
				sprintf(chBuf2, "[eTNAct_ReturnToSaveZone] %d��%d��%d��%d��%d��, �ֽŴ��� ����. \r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
				WriteLog( chBuf2, ".\\Log\\[Log]EventTriggered.txt" ) ;

				{
					char chBuf[2048] = { 0,0,0, } ;
					sprintf(chBuf, "\n\n\n[eTNAct_ReturnToSaveZone] %d��%d��%d��%d��%d��\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\[Log]ReturnToSaveZone.txt" ) ;
				}
				*/

				for( int i = 1 ; i < MAX_USER ; ++i )
				{
					if( USER_PLAY == pUser[i].Mode )
					{
						int iPortalID = 163 ;
						if( eTNClan_Brahma == pMob[i].m_byClan ) iPortalID = 161 ;
						else if( eTNClan_Vishnu == pMob[i].m_byClan ) iPortalID = 162 ;

						{
							char chBuf[2048] = { 0,0,0, } ;
							sprintf(chBuf, "\t- %s\r\n", pMob[i].MOB.szName ) ;
							WriteLog( chBuf, ".\\Log\\[Log]ReturnToSaveZone.txt" ) ;
						}

						S_SCP_RESP_MOVE_PORTAL sm; sm.wType=SCP_RESP_MOVE_PORTAL;

						bool bRet=true;
						DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
						bRet &= g_ParamMgr.HT_bGetPortalInfo( iPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;

						BYTE byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 ) ;
						//if( bRet && (ServerDown==-1000) )	//	�ٸ� ���̸�, ...
						if( bRet && (byMoveZone != (ServerIndex+1)) && (ServerDown==-1000) )	//	�ٸ� ���̸�, ...						
						{
							pMob[i].m_kWaitAction.iAction = eWaitAct_ZonePortal ;

							sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
							sm.byZone=byMoveZone; sm.nMoney=pMob[i].MOB.nRupiah;
							pUser[i].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
							
							pMob[i].m_eFSM = eTNFsm_Stand ;
							pMob[i].m_kLastTime.uiSitted = 0 ;

							pMob[i].MOB.snX = GetRandom(snStartX, snEndX);
							pMob[i].MOB.snZ = GetRandom(snStartZ, snEndZ);

						}
					}
				}
			}
			break ;
		case eTNAct_ChangeField :
			{ // Ư�� �簢 ���� �Ӽ��� �����Ѵ�.
				int iStartX, iEndX, iStartY, iEndY ;
				// Param0 : �� X
				// Param1 : ���� X
				// Param2 : �� Y
				// Param3 : ���� Y
				// Param4 : ��ǥ X
				// Param5 : ��ǥ Y

				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						if( 1 == g_krgTaskList[iTaskID].irgParam[5] ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | (unsigned short)(g_krgTaskList[iTaskID].irgParam[4]) ; // �߰�
						else if( 0 == g_krgTaskList[iTaskID].irgParam[5] )
						{
							unsigned short usNewProperty = (unsigned short)(g_krgTaskList[iTaskID].irgParam[4]) ;
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty ; // XOR�� ����
						}
					}
				}
			}
			break ;

		case eTNAct_AffectAll :
			{ // Ư�� �簢 ���� �Ӽ��� �����Ѵ�.
				int iStartX, iEndX, iStartY, iEndY ;
				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.
						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							if( 0 >= pMob[iMob].MOB.nHP ) continue ;

							TNEFFECT kEffect ;
							kEffect.iID = g_krgTaskList[iTaskID].irgParam[4] ;
							kEffect.iDuration = g_krgTaskList[iTaskID].irgParam[5] ;
							kEffect.iParam1 = 100 ;
							kEffect.iParam2 = 0 ;
							pMob[iMob].AddEffect( kEffect, iMob, iMob ) ;
							pMob[iMob].BroadcastUpdateStatusMsg() ;
							pUser[iMob].cSock.SendMessage() ;
						}
					}
				}
			}
			break ;

		case eTNAct_DebufferAll :
			{ // Ư�� �簢 ���� �Ӽ��� �����Ѵ�.
				int iStartX, iEndX, iStartY, iEndY ;
				iStartX = g_krgTaskList[iTaskID].irgParam[1] ;
				iEndX = g_krgTaskList[iTaskID].irgParam[0] ;
				if( g_krgTaskList[iTaskID].irgParam[0] < g_krgTaskList[iTaskID].irgParam[1] )
				{
					iStartX = g_krgTaskList[iTaskID].irgParam[0] ;
					iEndX = g_krgTaskList[iTaskID].irgParam[1] ;
				}

				iStartY = g_krgTaskList[iTaskID].irgParam[3] ;
				iEndY = g_krgTaskList[iTaskID].irgParam[2] ;
				if( g_krgTaskList[iTaskID].irgParam[2] < g_krgTaskList[iTaskID].irgParam[3] )
				{
					iStartY = g_krgTaskList[iTaskID].irgParam[2] ;
					iEndY = g_krgTaskList[iTaskID].irgParam[3] ;
				}

				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;
						if( eTNClan_GM == pMob[iMob].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�.
						if( eTNMob_PC == pMob[iMob].m_eMobType )
						{
							if( 0 >= pMob[iMob].MOB.nHP ) continue ;
							pMob[iMob].TurnOffAffection( g_krgTaskList[iTaskID].irgParam[4] ) ;
						}
					}
				}
			}
			break ;
		case eTNAct_ChangeImmunity :
			{
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( pMob[i].MOB.snTribe == g_krgTaskList[iTaskID].irgParam[1] )
					{
						if( 1 == g_krgTaskList[iTaskID].irgParam[0] )  // �߰�
						{
							pMob[i].m_iImmunity = g_krgTaskList[iTaskID].irgParam[2] ;
						}
						else if( 0 == g_krgTaskList[iTaskID].irgParam[0] ) // ���Ÿ� �ϰԵǸ� ������ �ʱ� �⺻ �Ӽ����� ���ư���.
						{
							pMob[i].m_iImmunity = pMonsterData[pMob[i].MOB.nTP].nGuildID ;
						}
					}
				}
			}
			break ;

		case eTNAct_CountBrahmaMonster :
			{
				int iCount = 0 ;
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( eTNClan_BrahmaSoldier == pMob[i].m_byClan )
					{
						if( 0 < pMob[i].MOB.nHP ) ++iCount ;
					}
				}

				if( 0 < iCount ) iProceed = 0 ;
			}
			break ;
		case eTNAct_CountVishnuMonster :
			{
				int iCount = 0 ;
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( eTNClan_VishnuSoldier == pMob[i].m_byClan )
					{
						if( 0 < pMob[i].MOB.nHP ) ++iCount ;
					}
				}

				if( 0 < iCount ) iProceed = 0 ;
			}
			break ;
		case eTNAct_CountSivaMonster :
			{
				int iCount = 0 ;
				for( int i = MAX_USER ; i < MAX_MOB ; ++i )
				{
					if( eTNClan_SivaSoldier == pMob[i].m_byClan )
					{
						if( 0 < pMob[i].MOB.nHP ) ++iCount ;
					}
				}

				if( 0 < iCount ) iProceed = 0 ;
			}
			break ;
		case eTNAct_MoveTheGateOfDungeon :
			{
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[1024] = { 0,0,0, } ;
					sprintf(chBuf, "[eTNAct_MoveTheGateOfDungeon] %d��%d��%d��%d��%d��, �ֽŴ��� ����\
								   ����帶(%d,%d), �񽴴�(%d,%d), �ù�(%d,%d)\r\n"
								   , st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
								   , g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1]
								   , g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3]
								   , g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
								   ) ;
								   WriteLog( chBuf, ".\\Log\\[Log]EventTriggered.txt" ) ;
				}

				if( 100 < g_krgTaskList[iTaskID].irgParam[0] ) g_bIsKaliaOpend = true ;
				else g_bIsKaliaOpend = false ;

				Teleport( g_irgGateOfDungeon[0], g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1] ) ; // ����帶
				Teleport( g_irgGateOfDungeon[1], g_krgTaskList[iTaskID].irgParam[2], g_krgTaskList[iTaskID].irgParam[3] ) ; // �񽴴�
				Teleport( g_irgGateOfDungeon[2], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5] ) ; // �ù�
			}
			break ;
		case eTNAct_OnKilledLeftGeneral : // �ϵ��¼��� ���� �� ����
			{
				int iStartX, iEndX, iStartY, iEndY ;
				// StartXZ(66,76),endXZ(166,164)
				iStartX = 66 ;
				iEndX = 166 ;
				iStartY = 76 ;
				iEndY = 164 ;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] The Left-Side General is killed !\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\[Log]ChinaBossSystem.txt" ) ;
				}
				#endif    
				// StartXZ(658,959),endXZ(638,954))

				int iDestX, iDestY ;
				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;

						iDestX = PlayDice( 638, 658 ) ;
						iDestY = PlayDice( 954, 959 ) ;
						Teleport( iMob, iDestX, iDestY ) ;
					}
				}
			}
			break ;
		case eTNAct_OnKilledRightGeneral : // �ϵο켺�� ���� �� ����
			{
				int iStartX, iEndX, iStartY, iEndY ;
				//StartXZ(856,68),endXZ(958,158)
				iStartX = 856 ;
				iEndX = 958 ;
				iStartY = 68 ;
				iEndY = 158 ;

				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n\n[%dMM%dDD %dH%dM%dS] The Right-Side General is killed !\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\[Log]ChinaBossSystem.txt" ) ;
				}
				#endif    
				//StartXZ(658,959),endXZ(638,954))

				int iDestX, iDestY ;
				for( int y = iStartY ; y < iEndY ; ++y )
				{
					for( int x = iStartX ; x < iEndX ; ++x )
					{
						int iMob = pMobGrid[y][x] ;
						if( 0 >= iMob || MAX_USER <= iMob ) continue ;

						iDestX = PlayDice( 638, 658 ) ;
						iDestY = PlayDice( 954, 959 ) ;
						Teleport( iMob, iDestX, iDestY ) ;
					}
				}
			}
			break ;
		case eTNAct_KickOutOtherClanInMyStronghold :
			{
/*
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st ;
					//GetLocalTime( &st ) ;
					char chBuf[256] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\n[%dMM%dDD %dHH%dMS%dSS] eTNAct_KickOutOtherClanInMyStronghold>\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond ) ;
					WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
				}
				#endif
*/
				for( int iPC = 0 ; iPC < MAX_USER ; ++iPC )
				{
					if( eTNClan_GM == pMob[iPC].m_byClan ) continue ;
					if( eTNCls_NPC == pMob[iPC].MOB.byClass1 ) continue ;
/*
					#ifdef __TN_TOP_LOG__
					{
						char chBuf[256] = { 0,0,0, } ;
						sprintf(chBuf, "\t- %s\r\n", pMob[iPC].MOB.szName ) ;
						WriteLog( chBuf, ".\\Log\\RecordPCName.txt" ) ;
					}
					#endif
*/

					//�ƴ�����eZone_Shambala, 132,510
					HS2D_COORD kDest;
					kDest.x = 132;
					kDest.y = 510;

					int x = pMob[iPC].TargetX ;
					int y = pMob[iPC].TargetY ;
					// stronghold ���� ��ġ�ϰ� �ִٸ�, clan�� Ȯ���ؼ� Ÿ guild�̸�, kick out~
					if( eTNCell_Shrine & g_krgCell[y][x].usProperty )
					{
						int iGuildID = pMob[iPC].MOB.nGuildID ;
						if( eStronghold_Northwest == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x < 316) && (y < 707) )
							{
								if( g_krgStronghold[eStronghold_Northwest].iOwner != iGuildID && g_krgStronghold[eStronghold_Northwest].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									//Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									
									pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Northeast == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x > 316) && (y < 707) )
							{
								if( g_krgStronghold[eStronghold_Northeast].iOwner != iGuildID && g_krgStronghold[eStronghold_Northeast].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									//Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Southwest == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x < 316) && (y > 707) )
							{
								if( g_krgStronghold[eStronghold_Southwest].iOwner != iGuildID && g_krgStronghold[eStronghold_Southwest].iOwnerFriend  != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									//Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
						else if( eStronghold_Southeast == g_krgTaskList[iTaskID].irgParam[0] )
						{
							if( (x > 316) && (y > 707) )
							{
								if( g_krgStronghold[eStronghold_Southeast].iOwner != iGuildID && g_krgStronghold[eStronghold_Southeast].iOwnerFriend != iGuildID)
								{
									//if( !pMob[iPC].IsDead() ) Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									//Teleport( iPC, g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2] ) ;
									pMob[iPC].MoveZone( eZone_Shambala, kDest.x, kDest.y );
								}
							}
						}
					}
				}
			}
			break;
		case eTNAct_CheckElapsedTimeAboutStronghold :
			{
				iProceed = 0 ;
				int iLocation = g_krgTaskList[iTaskID].irgParam[0] ;
				if( 0 > iLocation || eStronghold_Southeast < iLocation ) break ;
				CTime kNow( st ) ;
				//kNow.GetCurrentTime() ;
				CTimeSpan kElapsedTime = kNow - g_krgStronghold[iLocation].kTimeOccupied ;

				if( /*7200*/30240 > kElapsedTime.GetTotalMinutes() ) iProceed = 1 ; // ����ð��� 3�ְ� ���� �ʾҴ�. 21��*24�ð�*60��					
			}
			break ;
		case eTNAct_SwitchBattleForStronghold :
			{
				g_iBattleForStronghold = g_krgTaskList[iTaskID].irgParam[0] ;

				Msg_StrongHoldStatus sm; sm.wType = _Msg_StrongHoldStatus;
				sm.byMode = g_iBattleForStronghold;
				sm.byDummy = 0; sm.snDummy = 0;
				MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));

				if( 1 == g_iBattleForStronghold )			//	����� ����
				{

				}
				else if( 0 == g_iBattleForStronghold )		//	����� ����
				{

				}
			}
			break ;
		case eTNAct_SetDuelFieldAtStronghold :
			{//345	285	736	677
				for( int y = 677 ; y < 736 ; ++y )
				{
					for( int x = 285 ; x < 345 ; ++x )
					{
						g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone ;
						//if( 20 == g_krgCell[y][x].usEvent ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_DuelZone ;
						//else if( 21 == g_krgCell[y][x].usEvent ) g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty | eTNCell_SealedZone ;
					}
				}
			}
			break ;
		case eTNAct_CloseDuelFieldAtStronghold :
			{
				for( int y = 677 ; y < 736 ; ++y )
				{
					for( int x = 285 ; x < 345 ; ++x )
					{
						unsigned short usNewProperty = (unsigned short)eTNCell_DuelZone ;
						if( usNewProperty & g_krgCell[y][x].usProperty  )							
							g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty ; // XOR�� ����
						/*
						if( 20 == g_krgCell[y][x].usEvent )
						{
							unsigned short usNewProperty = (unsigned short)eTNCell_DuelZone ;
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty ; // XOR�� ����
						}
						else if( 21 == g_krgCell[y][x].usEvent )
						{
							unsigned short usNewProperty = (unsigned short)eTNCell_SealedZone ;
							if( usNewProperty & g_krgCell[y][x].usProperty  )							
								g_krgCell[y][x].usProperty = g_krgCell[y][x].usProperty ^ usNewProperty ; // XOR�� ����
						}
						*/
					}
				}
			}
			break ;
		case eTNAct_RegisterPCtoArenaEntry :
			{
				iProceed = 0 ;
				if( 0 >= a_iUser || MAX_USER <= a_iUser ) break ; //return eTNRes_EvntInvalidUserHandle ;
				if( eTNClan_GM == pMob[a_iUser].m_byClan ) break ;

				if( g_kArena.IsFull() )
				{
					SendClientMessage( a_iUser, g_pMessageStringTable[_ArenaEntryIsFull] ) ;
					break ; //return eTNRes_ArenaEntryIsFull ;
				}

				//g_kArena.AddEntrant( a_iUser ) ;
				/*
				if( true == pMob[a_iUser].m_bIsInArenaEntry ) break ; //return eTNRes_AlreadyRegisteredInArenaEntry ;
				g_irgArenaEntry[g_iArenaEntryCount] = a_iUser ;
				++g_iArenaEntryCount ; // �����ڼ� 1 ����
				pMob[a_iUser].m_bIsInArenaEntry = true ;
				*/

				iProceed = 1 ;
			}
			break ;

		case eTNAct_StartSuvivalFight :
			{
				g_kArena.StartSurvival() ;
			}
			break ;
		case eTNAct_CheckWinner :
			{
				if( !g_kArena.IsProgressed() ) break ;

				int iRes = g_kArena.CheckWinner() ;
				if( !iRes ) // �Ʒ��� �����̹� ���ڰ� �����Ǿ���. ���� �̺�Ʈ�� trigger
				{
					TriggerEvent(0, 68, 0, 0, 0 ) ; // �Ʒ��� �����̹� �̺�Ʈ ����
				}
			}
			break ;

		case eTNAct_PostThePrize :
			{
				if( !g_kArena.IsProgressed() ) break ;

				g_kArena.Award() ;
				g_dwArenaMoney = 0 ;			

				char szMsg[1024] = { 0,0,0, } ;		
				char szWinners[512] = { 0,0,0, } ;
				g_kArena.OutputWinners( szWinners ) ;
				sprintf( szMsg, g_pMessageStringTable[_PostThePrize], szWinners, g_kArena.get_GoldToAward() ) ; // g_dwArenaMoney, �ӽ÷� 1���� �Է��ߴ�. ���߿� ������ ������ ����� �Ѵ�.

				{
					char chBuf[2048] = { 0,0,0, } ;
					sprintf(chBuf, "[eTNAct_PostThePrize] %d��%d��%d��%d��%d��, %s\r\n", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, szMsg ) ;
					WriteLog( chBuf, ".\\Log\\[Log]Stronghold.txt" ) ;
				}

				PostMessageToWorld( szMsg ) ;
			}
			break ;
		case eTNAct_KickOutLosser :
			{ // ���������� �� PC���� ƨ���.
				int iWinner = g_kSiege.get_Winner() ;

				for( int i = 1 ; i < MAX_USER ; ++i )
				{
					if( USER_PLAY != pUser[i].Mode ) continue ;
					if( eTNClan_GM == pMob[i].m_byClan ) continue ; //  GM�� ���� �̵���Ű�� �ʴ´�
					if( iWinner == pMob[i].m_byClan ) continue ;

					/*losser �̶��*/
					ReturnPCToSaveZone( i ) ;
				}
			}
			break ;
		case eTNAct_JudgeTheSiege :
			{ // symbol �� �����ָ� ã�Ƽ� ���� ���
				g_kSiege.JudgeSiege() ;

				//	���� ����� ������ ������ ��ȭ�� ������ �˸���.
				TNCastle kOwner ;
				g_kSiege.get_Owner( &kOwner) ;
				Msg_CastleUpdate sm; ZeroMemory(&sm, sizeof(sm));
				sm.wType = _Msg_CastleUpdate;
				sm.iCastleOwner = kOwner.kGuild.iID;
				MSGServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
			}
			break ;
		case eTNAct_PopSymbolForSiege :
			{
				if( 0 >= a_iUser || MAX_MOB <= a_iUser ) continue ;
				if( MAX_USER <= a_iUser )
				{
					
					//if( (eTNCls2_Retainer == pMob[a_iUser].MOB.byClass2) || (eTNCls2_Familiar == pMob[a_iUser].MOB.byClass2) || (eTNCls_Fellow == pMob[a_iUser].MOB.byClass1) ) 
					if( eTNAIO_HaveMaster & pMob[a_iUser].m_iAIOption )
					{
						a_iUser = pMob[a_iUser].Leader;
					}
				}

				g_kSiege.CaptureSymbol( pMob[a_iUser].m_byClan, a_iNPC/*symbol*/, a_iUser/*capturer*/ ) ;

				// symbol�� ���� �Ŀ� �ٷ�(���) pop �ȴٸ� �ణ ����� ���ϴ�. �׷��� delay�� �־�� �Ѵ�. ���� �����ϱ� ���� ����� �����Ǿ�� �Ѵ�.
				// 35(=7*5) ���� event/task
				// 35���� event�� 1�� �Ŀ� �����ϱ� ���� event/task
				//int TriggerEvent( int a_iUser, int a_iEventID, int a_iX, int a_iY, int a_iNPC, int a_iCaller )
				// a_iUser�� symbol�� owner�� �˾Ƴ� �� �ִ�. a_iX, a_iY�� ���ؼ� pop��ġ�� �˾Ƴ� �� �ִ�.

			}
			break ;
		case eTNAct_RecoverClanToOriginal :
			{ // call a global routine
				ChangeClan( -1, -1 ) ;
			}
			break ;
		case eTNAct_ChangeClanForSiege :
			{
				if( !g_kSiege.get_Started() ) break; // �������� �ƴ϶��, ...

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "[eTNAct_ChangeClanForSiege] %dYY%dMM%dDD %2dHH%2dMI%2dSS> \r\n"
						, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						) ; 
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif


				for( int i = 1 ; i < MAX_USER ; ++i )
				{
					if( eTNClan_GM == pMob[i].m_byClan ) continue;
					//if( eTNClan_CastleOwner <= pMob[i].m_byClan && eTNClan_Siege4 >= pMob[i].m_byClan ) continue;
					if( USER_PLAY != pUser[i].Mode ) continue ;

					byte byOld = pMob[i].m_byClan;

					int iFlag = g_kSiege.SearchEntry( pMob[i].MOB.nGuildID ) ;
					if( -1 == iFlag ) pMob[i].m_byClan = eTNClan_Siege4 ; // ���Ҽ�
					else pMob[i].m_byClan = iFlag ;

					MSG_CHANGE_CLAN kMsg;
					kMsg.snKeyID = i;
					kMsg.byClan = pMob[i].m_byClan;
					pUser[i].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) ) ;

					MSG_SET_ZONE_SETTINGS kZoneSettingMsg ;
					kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID ;
					kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);

					kZoneSettingMsg.snSiege = 1; //g_kSiege.get_Started(); ��������
					pUser[i].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) ) ;

					S_SCP_INIT_OTHER_MOB sm ;
					GetCreateMob( i, &sm ) ;
					GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0) ;

					pUser[i].cSock.SendMessage();

					#ifdef __TN_TOP_LOG__
					{
						char chBuf[512] = { 0,0,0, } ;
						sprintf(chBuf, "[eTNAct_ChangeClanForSiege] PC(%d, Name:%s, Guild:%d), clan(now:%d, old:%d) \r\n"
							,i , pMob[i].MOB.szName, pMob[i].MOB.nGuildID
							, pMob[i].m_byClan, byOld
							) ; 
						WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
					}
					#endif


/*
					S_SCP_RESP_CHAR_INIT kMsg;
					kMsg.wType = SCP_RESP_CHAR_INIT;
					kMsg.wPDULength = sizeof(S_SCP_RESP_CHAR_INIT)-sizeof(HEADER);

					kMsg.byResult = 1 ;
					kMsg.dwGameTime = time(NULL) ;
					kMsg.dwKeyID = i ;
					kMsg.snX = pMob[i].TargetX ;
					kMsg.snZ = pMob[i].TargetY ;
					memcpy( kMsg.bySkill, pMob[i].MOB.bySkill, sizeof(BYTE)*MAX_SKILL ) ;
					memcpy( kMsg.byQuest, pMob[i].MOB.byQuest, sizeof(BYTE)*MAX_EVENT_FLAG ) ;
					memcpy( kMsg.Inven, pMob[i].MOB.Inven, sizeof(STRUCT_ITEM)*MAX_INVEN ) ;
					memcpy( kMsg.Equip, pMob[i].MOB.Equip, sizeof(STRUCT_ITEM)*MAX_EQUIP ) ;
					memcpy( kMsg.Cargo, pUser[i].Cargo, sizeof(STRUCT_ITEM)*MAX_CARGO ) ;
					memcpy( kMsg.dwTimeStamp, pUser[i].m_time, sizeof(kMsg.dwTimeStamp));
					kMsg.nCargoMoney = pUser[i].Coin;
					kMsg.nGuildID = pMob[i].MOB.nGuildID ;
					kMsg.byClan = pMob[i].m_byClan ;
					kMsg.dwEvent = pUser[i].m_dwEvent;

					pUser[i].cSock.SendOneMessage((char*)&kMsg,sizeof(S_SCP_RESP_CHAR_INIT));

					S_SCP_INIT_OTHER_MOB sm ;
					GetCreateMob( i, &sm ) ;
					GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0) ;
*/
				}
			}
			break;
		case eTNAct_SwitchExpireOfTheTermForSiege :
			{
				g_kSiege.set_ExpiryOftheTerm( g_krgTaskList[iTaskID].irgParam[0] ) ; // 1�̸� �Ⱓ����(������û�Ұ�), 0�̸� �Ⱓ��(������û����)
				if( 0 < g_krgTaskList[iTaskID].irgParam[0] ) // ������û �Ұ�, ������ ����ǥ ������
				{
					char szFileName[64] = { 0,0,0, };
					sprintf( szFileName, ".\\Log\\SiegeEntry_%dYY%dMM%dDD %2dHH%2dMI%2dSS.txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );
					g_kSiege.SaveData( szFileName );
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\r\n[Switch ������û�Ⱓ] [%dYY%dMM%dDD %2dHH%2dMI%2dSS] > state:%d(0:������û����, 1:������û�Ұ�)\r\n"
						, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, g_krgTaskList[iTaskID].irgParam[0]
						) ; 
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif
			}
			break ;
		case eTNAct_SwitchSiege :
			{ // call a global routine
				g_kSiege.set_Started( g_krgTaskList[iTaskID].irgParam[0] ) ; // 0�̸� ��������, 1�̸� ��������

				if( 0 >= g_krgTaskList[iTaskID].irgParam[0] ) // off
				{
					g_kSiege.DestroySymbols() ;
					ChangeClan( -1, -1 ) ;

					for( int i = 1 ; i < MAX_USER ; ++i )
					{
						if( USER_PLAY != pUser[i].Mode ) continue ;

						MSG_SET_ZONE_SETTINGS kZoneSettingMsg ;
						kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID ;
						kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);

						kZoneSettingMsg.snSiege = 0; //g_kSiege.get_Started(); ��������
						pUser[i].cSock.SendOneMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) ) ;
					}
				}
				else // turn on
				{
					g_kSiege.InstallSymbols() ;
					g_kSiege.SaveData( ".\\Log\\[Log]Castle.txt" );
				}

				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\r\n[Start/End the siege] [%dYY%dMM%dDD %2dHH%2dMI%2dSS] > state:%d(0:��������, 1:��������)\r\n"
						, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, g_krgTaskList[iTaskID].irgParam[0]
						) ; 
					WriteLog( chBuf, ".\\Log\\[Log]Castle.txt" ) ;
				}
				#endif
			}
			break ;
		case eTNAct_FixTheDateOfTheSiege :
			{
				int iSelected = g_kSiege.get_DateToHold() ;
				//eDate_NotSelected = 0, eDate_Friday8HH, eDate_Friday10HH, eDate_Saturday8HH, eDate_Saturday10HH, eDate_Sunday8HH,

				if( TNSiege::eDate_Friday8HH == iSelected )
				{
					g_krgEventList[100].iDuration = eEvntSwitch_On ;
				}
				else if( TNSiege::eDate_Friday10HH == iSelected )
				{
					g_krgEventList[101].iDuration = eEvntSwitch_On ;
				}
				else if( TNSiege::eDate_Saturday8HH == iSelected )
				{
					g_krgEventList[102].iDuration = eEvntSwitch_On ;
				}
				else if( TNSiege::eDate_Sunday8HH == iSelected )
				{
					g_krgEventList[104].iDuration = eEvntSwitch_On ;
				}
				else
				{
					iSelected = TNSiege::eDate_Sunday8HH;
					g_krgEventList[103].iDuration = eEvntSwitch_On ;
				}

				g_kSiege.SelectDate( iSelected ) ;
			}
			break ;
		case eTNAct_PostTheResultOfTheSiege :
			{

			}
			break ;
		case eTNAct_PostTheScheduleForTheSiege : // schedule�� �־� �������� ������ �Ѵ�. ȭ���� ��¥ ���� �����̹Ƿ� ��,��, �� ������ �ϸ� �� ��
			{// ������ �������� ����� ���� 9�ÿ� ���ֵ˴ϴ�. �ڼ��� ������ ������� ������ �߽��ٿ��� ������ �ּ���.
				int iSelected = g_kSiege.get_DateToHold() ;
				if( 0 == iSelected ) break ;

				int iMessageID = _PostTheDateForSiege1 ;
				if( 2 == iSelected ) iMessageID = _PostTheDateForSiege2 ;
				else if( 3 == iSelected ) iMessageID = _PostTheDateForSiege3 ;
				else if( 4 == iSelected ) iMessageID = _PostTheDateForSiege4 ;
				else if( 5 == iSelected ) iMessageID = _PostTheDateForSiege5 ;
				else iMessageID = _PostTheDateForSiege1 ;

				PostMessageToWorld( g_pMessageStringTable[iMessageID], eTNClr_White, eTNClr_BG, iMessageID ) ;
			}
			break ;

		case eTNAct_QuestEvent :
			{
				int iTribe = pMob[a_iNPC].MOB.snTribe;
				BOOL bRes = QUEST_OnEvent( a_iUser, iTribe, iTribe );
				if( FALSE == bRes )	return eTNRes_Failed;
			}
			break;
		} // end of switch

		if( eEvntPrcdType_Sequential == g_krgEventList[a_iEventID].sProceedType ) iProceed = 1 ;
	} // end of for statement

	if( iProceed ) g_krgEventList[a_iEventID].uiAvailableTime = g_krgEventList[a_iEventID].uiCoolDownTime + CurrentTime ;

	return eTNRes_Succeeded ;
}



// �� �Լ��� Ȯ���� �������� ����Ѵ�. �� �ٸ� ó������ �� �����ϴ� Ȥ�ó� �����Ÿ��� ������ �𸣹Ƿ� ��Ȯ�μ����� �ۼ��Ǿ���.
void RemoveKalaCoreInInventory( int a_iUser )
{
	if( 0 >= a_iUser || MAX_USER <= a_iUser ) return ;

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;

	for( int i = 0 ; i < MAX_INVEN ; ++i )
	{
		int iID = pItemData[pMob[a_iUser].MOB.Inven[i].snIndex].sID ;
		if( (eKalaCore_Brahma == iID) || (eKalaCore_Vishnu == iID) || (eKalaCore_Siva == iID) )
		{
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf( chBuf, "[%dmm%ddd %dhh%dmi%dss] RemoveKalaCoreInInventory() > Remove a kala-core(%d) in %s's inventory> - \r\n"
					, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
					, iID, pMob[a_iUser].MOB.szName 
					) ;
				WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
			}
			ZeroMemory(&pMob[a_iUser].MOB.Inven[i], sizeof(STRUCT_ITEM)) ;
		}
	}
}



// TNKalaSystem class�� �������� ���Ͽ�, kala-core ������ ���� ���� ������ �̸� �������ִ� ����� ��ȭ�Ǿ�� �Ѵ�.
// TNKalaSystem�� �� 9���� slot ������ �̿��ؼ� ������ ������ �ش��ϴ� ���� kala�� �ִ��� �˻縦 �Ѵ�. ���� Ʋ���ٸ�, slot ������ �ʱ�ȭ�ϰ�
// �ű� kala-core�� �� �߾ӿ� �������Ѽ� ��ü ������ �����ش�.
// 
void CheckKalaSystem()
{
	g_kKalaSystem.DropKalaCoreInPC() ;
	g_kKalaSystem.CheckCountNRecovery() ;
	g_kKalaSystem.Print() ;

	WriteLog( "\r\n", ".\\Log\\[Log]KalaSystem.txt" ) ;
}



int SummonKala( int a_iTribe, int a_iClan, int x, int y, int& a_iHandle )
{
	if( 0 == x || 0 == y ) return 100 ;

	int iMob = 0 ;
	int iStart = 0 ;
	if( eKala_Brahma == a_iTribe ) iStart = 1000 ;
	else if( eKala_Vishnu == a_iTribe ) iStart = 1003 ;
	else if( eKala_Siva == a_iTribe ) iStart = 1006 ;

	for( int i = 0 ; i < 3 ; ++i )
	{
		if( MOB_EMPTY == pMob[iStart].Mode )
		{
			iMob = iStart ;
			break ;
		}
		++iStart ;
	}

	if( 1000 > iMob || 1008 < iMob ) return eTNRes_Failed ;

	int iMonsterDataIndex = a_iTribe - 2000 ; // the index of monster data
	pMob[iMob].MOB = pMonsterData[iMonsterDataIndex] ;
	pMob[iMob].MOB.nTP = iMonsterDataIndex ;
	pMob[iMob].Init( iMob ) ; // �ʱ�ȭ

	if( 0 < pMobGrid[y][x] && MAX_MOB > pMobGrid[y][x] ) // �ٸ� mob�� ��ġ�ϰ� �ִ�.
	{		
		if( true ) // dest �ڸ��� �˻��ϰ�, �ٸ� mob�� ������, ó��(����)�� �Ŀ�, �� �� ��ġ�� ��ġ�� ��Ų��.
		{
			int iOccupiedMob = pMobGrid[y][x] ;
			int iNewX, iNewY ;
			iNewX = x ; iNewY = y ;
			int tret = GetEmptyMobGrid( iOccupiedMob, &iNewX, &iNewY ) ;
			if( FALSE == tret )
			{ // user�̸� kick out �����ְ�, monster�̸� �ܼ��� ���δ�.
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user�̸�
				{
					SendClientMessage( iOccupiedMob, g_pMessageStringTable[_Bad_Network_Packets] ) ;
					CloseUser( iOccupiedMob ) ;
				}
				else 
				{
					KillMonster( iOccupiedMob ) ;
					/*
					pMob[iOccupiedMob].MOB.nHP = 0 ; 
					pMob[iOccupiedMob].CurrentTarget = 0 ;
					pMob[iOccupiedMob].m_eFSM = eTNFsm_Dead ;
					*/
				}
			}
			else // ������ ��ġ�� �ٲ۴�.
			{			
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user�̸�
				{
					MSG_Action sm;	GetAction( iOccupiedMob, iNewX, iNewY ,&sm ) ;
					pUser[iOccupiedMob].cSock.SendOneMessage( (char*)&sm, sizeof(sm) ) ;					
				}
				else
				{
					//pMobGrid[iNewY][iNewX] = iOccupiedMob ;
				}

				pMobGrid[iNewY][iNewX] = iOccupiedMob ;				
			}

			pMobGrid[y][x] = iMob ;
		}
		else
		{
			int tret = GetEmptyMobGrid( iMob, &x, &y, pMob[iMob].m_iBlockedCell ) ;
			if( FALSE == tret ) return 110 ; // summon�� fail���� ����� ���� ���� ���, ...
		}
	}

	pMob[iMob].LastX = pMob[iMob].TargetX = pMob[iMob].SegmentX = x ;
	pMob[iMob].LastY = pMob[iMob].TargetY = pMob[iMob].SegmentY = y ;

	// default settings
	for( int i = 0 ; i < MAX_SEGMENT ; ++i )
	{
		pMob[iMob].SegmentListX[i] = x ;
		pMob[iMob].SegmentListY[i] = y ;
		pMob[iMob].SegmentWait[i] = rand() % 8 ;
		pMob[iMob].SegmentRange[i] = rand() % 20 ;
	}
	pMob[iMob].RouteType = eTNRout_MoveNRoam ;
	pMob[iMob].Formation = 0 ;

	pMob[iMob].MOB.byClass1 = (byte)eTNCls_Event ; // ��ȯ�Ǵ� NPC�� ����
	pMob[iMob].MOB.byClass2 = 0 ; // ��ȯ�Ǵ� NPC�� �� ����            
	pMob[iMob].m_byClan = pMob[iMob].MOB.byTrimuriti = (byte)a_iClan ;

	//pMob[iMob].m_uiActionLock = 0 ;
	//pMob[iMob].m_iDirection = a_iDirection ;
	                    
	a_iHandle = iMob ;

	S_SCP_INIT_OTHER_MOB sm ;
	GetCreateMob( iMob, &sm ) ;
	sm.byPopType = eTNPrdt_PopRaise ; // ��ȯ�� ���� ���� ��ȣ
	pMobGrid[y][x] = iMob ;
	GridMulticast( x, y, (MSG_STANDARD*)&sm, 0) ;

	return eTNRes_Succeeded ;
}



void VerifyKalaOnAltar()
{
	/*
	for( int i = 0 ; i < eKalaAltar_MaxCount ; ++i )
	{
		int iKalaMonster = g_kKalaSystem.IsEmptyAltar( i ) ;
		if( (1008 < iKalaMonster) && (0 != g_irgKalaAltar[i]) )
		{
			if( MAX_MOB > g_irgKalaAltar[i] )
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "[ERROR] Altar No.%d : Mob(%d, %d)\r\n", i, g_irgKalaAltar[i], pMob[g_irgKalaAltar[i]].MOB.snTribe	) ;
				WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;

				pMob[g_irgKalaAltar[i]].MOB.nHP = 0 ; 
				pMob[g_irgKalaAltar[i]].CurrentTarget = 0 ;
				pMob[g_irgKalaAltar[i]].m_eFSM = eTNFsm_Dead ;
			}

			g_irgKalaAltar[i] = 0 ;
		}
	}
	*/
}



// �� 9������ kala ���¸� ����Ѵ�.( 1000~1008 )
// summon�� �Ϸ��� �ߴٴ� ���� altar�� �������� ���̹Ƿ� ��� altar�� ���¸� ����Ѵ�.
void LogKalaSystemInfo()
{
	/*
	char chBuf[512] = { 0,0,0, } ;
	sprintf(chBuf, "Kala> Brahma(%d,%d,%d), Vishnu(%d,%d,%d), Siva(%d,%d,%d)\
				   \tAltar> (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\
				   \r\n\n"
		, pMob[1000].m_eFSM, pMob[1001].m_eFSM, pMob[1002].m_eFSM
		, pMob[1003].m_eFSM, pMob[1004].m_eFSM, pMob[1005].m_eFSM
		, pMob[1006].m_eFSM, pMob[1007].m_eFSM, pMob[1008].m_eFSM
		, g_irgKalaAltar[0], g_irgKalaAltar[1], g_irgKalaAltar[2], g_irgKalaAltar[3], g_irgKalaAltar[4]
		, g_irgKalaAltar[5], g_irgKalaAltar[6], g_irgKalaAltar[7], g_irgKalaAltar[8], g_irgKalaAltar[9]
		, g_irgKalaAltar[10], g_irgKalaAltar[11], g_irgKalaAltar[12], g_irgKalaAltar[13], g_irgKalaAltar[14]
		) ;
	WriteLog( chBuf, ".\\Log\\[Log]KalaSystem.txt" ) ;
	*/
}

void StartChallenge(int conn)
{
	int nTarget = pUser[conn].m_nChallenger;

	Msg_Challenger sm; sm.wType = _Msg_Challenger;
	sm.byMode = eChallenge_WAIT;

	//	���� ������带 �����Ѵ�.
	pUser[conn].m_nChallengeMode = eChallenge_Combat;
	pUser[conn].m_nChallenger = nTarget;
	strncpy(pUser[conn].m_pChallenger, pMob[nTarget].MOB.szName, SZNAME_LENGTH);

	//	����� ������带 �����Ѵ�.
	pUser[nTarget].m_nChallengeMode = eChallenge_Combat;
	pUser[nTarget].m_nChallenger = conn;
	strncpy(pUser[nTarget].m_pChallenger, pMob[conn].MOB.szName, SZNAME_LENGTH);

	//	�ֹ濡�� ���������� �˸���.
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

	//	���� ������带 �����Ѵ�.
	pUser[conn].m_nChallengeMode = eChallenge_WAIT;
	pUser[conn].m_nChallenger = 0;
	ZeroMemory(pUser[conn].m_pChallenger, SZNAME_LENGTH);

	Msg_Challenger sm; sm.wType = _Msg_Challenger;
	sm.byMode = eChallenge_Response;
	sm.byReason = byReason;
	sm.nID = nTarget;
	strncpy(sm.szCharName, pMob[nTarget].MOB.szName, SZNAME_LENGTH);
	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	pMob[conn].Init( conn ) ;
	//pMob[conn].ClearAffection();
	pMob[conn].ProcessContinuousEffect();

	sprintf(pData, "SERVER SEND TO:%s _Msg_Challenger CANCELED WITH charllenger:%s mode:%d reason:%d", 
		pMob[nTarget].MOB.szName, pMob[conn].MOB.szName, eChallenge_Response, byReason);
	TimeWriteLog(pData, "Challenger_log.txt");

	//	����� ������带 �����Ѵ�.
	pUser[nTarget].m_nChallengeMode = eChallenge_WAIT;
	pUser[nTarget].m_nChallenger = 0;
	ZeroMemory(pUser[nTarget].m_pChallenger, SZNAME_LENGTH);

	sm.nID = conn;
	strncpy(sm.szCharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	pUser[nTarget].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	pMob[nTarget].Init( nTarget ) ;
	//pMob[nTarget].ClearAffection();
	pMob[nTarget].ProcessContinuousEffect();
}


// ������ ���常 �Ѵ�.
// symbol�� destroy�Ǹ� WriteSymbolDestroyer(), CompareSymbolDestroyer() �ΰ��� �Լ��� ������ call �ϵ��� �Ѵ�.
void WriteSymbolDestroyer( int a_iIndex, int a_iSymbol, int a_iGuildID ) 
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return ;
	if( 0 > a_iSymbol || 1 < a_iSymbol ) return ;
	if( 0 >= a_iGuildID ) return ;

	g_krgStronghold[a_iIndex].irgDestroyer[a_iSymbol] = a_iGuildID ;
}


// ������ �񱳸� �Ѵ�.
int CompareSymbolDestroyers( int a_iIndex )
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return eTNRes_Failed ;
	if( 0 >= g_krgStronghold[a_iIndex].irgDestroyer[0] ) return eTNRes_Failed ;
	if( 0 >= g_krgStronghold[a_iIndex].irgDestroyer[1] ) return eTNRes_Failed ;
	if( g_krgStronghold[a_iIndex].irgDestroyer[0] != g_krgStronghold[a_iIndex].irgDestroyer[1] ) return eTNRes_Failed ;

	return eTNRes_Succeeded ;
}


void CheckStrongholdStatus( int a_iIndex )
{
	if( 0 > a_iIndex || eStronghold_MaxCount <= a_iIndex ) return ;

	if( CompareSymbolDestroyers( a_iIndex ) ) // �ΰ��� symbol�� destroy�� guild�� ������ ���
	{
		// 0. ���� ���� event �ϳ����� trigger���ش�.

		// 1. ��� �Ҽ��� ��� guard���� ���δ�.
		// 2. ���ɵǾ��ٴ� ��ü �޽����� ����.
		// 3. ��� �Ҽ��� ��� guard���� ���Ӱ� ��ġ�Ѵ�.


	}
	else // �ٸ� ���
	{
		// 1. ��� ���� �ʱ�ȭ�Ѵ�.

	}
}


// stronghold.txt��� ������ ����� ���ʿ��� basic data(/S(tronghold) [ID] [Owner])�� ��ġ��Ű��
// ���ʿ��� �������̷� guard ��ġ������(/M(onster) [ID] [x] [y] [clan])�� line ������ �־���´�.
// scheduler�� 1�ð��� nȸ�� ����ǰ� �س��´�. ����� ������ ���� ������ ����� ���ο� ������ ���鵵�� �Ѵ�.
// server start up�ÿ� stronghold file�� �ε��ؼ� set�ϰ� �Ѵ�.
// ����� zone�� �����ϴ� ���ʿ��� "Stronghold.txt" data file�� �����ؾ��Ѵ�. ���⿡�� stronghold �⺻���� 4���� �� �ִ�. ��� ������
int LoadStrongholdData()
{
	if( eZone_Stronghold != g_iZoneID ) return eTNRes_Failed ;

	char szData[64] = { 0,0,0, } ;
	char szCommand[32] = { 0,0,0, } ;
    char szArgument1[32] = { 0,0,0, } ;
    char szArgument2[32] = { 0,0,0, } ;
	char szArgument3[32] = { 0,0,0, } ;
	char szArgument4[32] = { 0,0,0, } ;
	char szArgument5[32] = { 0,0,0, } ;
	char szArgument6[32] = { 0,0,0, } ;
	char szArgument7[32] = { 0,0,0, } ;
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0 ;
	
	FILE* fin ;
	fin = fopen( ".\\Data\\Stronghold.txt", "rt" ) ;
	if( NULL == fin ) 
	{ 
		MessageBox( hWndMain, "Not found Stronghold.txt in data folder.", "Failed to initialize data about the stronghold.", NULL ) ; 
		return eTNRes_Failed ; 
	}

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;
	int iYear, iMonth, iDay, iHour, iMinute ;
	bool bDateTimePatched = true ;

	while( true )
	{
		char* ret = fgets( (char*)szData, 64, fin ) ;
		if( NULL == ret ) break ;

		iYear = iMonth = iDay = iHour = iMinute = 0 ;
		sscanf( szData, "%s %s %s %s %s %s %s %s", szCommand, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5, szArgument6, szArgument7 ) ;
		iArgument1 = atoi( szArgument1 ) ; // order #
		iArgument2 = atoi( szArgument2 ) ; // owner(guild ID)
		iYear = atoi( szArgument3 ) ; // date occupied
		iMonth = atoi( szArgument4 ) ;
		iDay = atoi( szArgument5 ) ;
		iHour = atoi( szArgument6 ) ;
		iMinute = atoi( szArgument7 ) ;
	
		switch( szData[1] )
		{
		case 'M' :
			{
				pMob[1000].Summon( iArgument1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, 0, iArgument4, 0, iArgument2, iArgument3, 0, false ) ;
			}
			break ;
		case 'S' :
			{
				int iIndex = iArgument1 % 4 ; // 0,1,2,3
				g_krgStronghold[iIndex].iID = iArgument1 ;
				g_krgStronghold[iIndex].iOwner = iArgument2 ;

				if( (0 == iYear) && (0 == iMonth) && (0 == iDay) )
				{
					bDateTimePatched = false ;
					CTime kTime( st ) ;
					g_krgStronghold[iIndex].kTimeOccupied = kTime ;
				}
				else
				{
					CTime kTime( iYear, iMonth, iDay, iHour, iMinute, 0 ) ;
					g_krgStronghold[iIndex].kTimeOccupied = kTime ;
				}

				{
					char chBuf[512] = { 0,0,0, } ;
					sprintf(chBuf, "\r\n\r\n[LoadStrongholdData] %dyy%dmm%ddd %dhh%dms%dss > %d stronghold is occupied by a guild(%d) in %d-%d-%d-%d-%d\r\n"
						, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
						, iArgument1, iArgument2
						, iYear, iMonth, iDay, iHour, iMinute
						) ; 
					WriteLog( chBuf, ".\\Log\\[Log]Stronghold.txt" ) ;
				}

				CGuild guild;
				ReadGuildFile(g_krgStronghold[iIndex].iOwner, &guild);
				strncpy(g_krgStronghold[iIndex].szGuildName, guild.GUILD.GuildName, SZGUILD_LENGTH);
				g_krgStronghold[iIndex].iOwnerFriend = GetGuildID(guild.GUILD.AlliedGuildName1);
				g_krgStronghold[iIndex].dwMark = guild.GUILD.Mark;
			}
			break ;
		}
	}

	fclose( fin ) ;
	//CloseHandle( hFile ) ;

	if( false == bDateTimePatched ) SaveStrongholdData() ;

	bool bRet=true; 
	DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNW, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;	
	g_stPosStronghold[eStronghold_Northwest].x = snStartX;
	g_stPosStronghold[eStronghold_Northwest].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;	
	g_stPosStronghold[eStronghold_Northeast].x = snStartX;
	g_stPosStronghold[eStronghold_Northeast].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;	
	g_stPosStronghold[eStronghold_Southwest].x = snStartX;
	g_stPosStronghold[eStronghold_Southwest].y = snStartZ;

	bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_SNE, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ ) ;	
	g_stPosStronghold[eStronghold_Southeast].x = snStartX;
	g_stPosStronghold[eStronghold_Southeast].y = snStartZ;

	if(!bRet)
	{
		MessageBox( hWndMain, "Can't find Stronghold Portal Data in TantraParam.", "Failed to initialize data about the stronghold.", NULL ) ; 
		return eTNRes_Failed ; 
	}

	return eTNRes_Succeeded ;
}


int SaveStrongholdData()
{
	HANDLE hFile ;
	hFile = CreateFile( ".\\Data\\Stronghold.txt",					  // file name
                                GENERIC_WRITE,   // open for writing 
                                FILE_SHARE_WRITE,             // do not share 
                                NULL,                         // no security 
                                CREATE_ALWAYS,                  // open or create 
                                FILE_ATTRIBUTE_NORMAL,        // normal file 
                                NULL ) ;

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return eTNRes_Failed ;
	}


	DWORD dwRetWrite = 0 ;
	int nBufLength = 0 ;	
	char szData[64] = { 0,0,0, } ;

	// stronghold ���� ����
	for( int iStronghold = 0 ; iStronghold < eStronghold_MaxCount ; ++iStronghold )
	{
		memset( szData, 0, sizeof(szData) ) ;
		sprintf( szData, "/S %d %d %d %d %d %d %d\r\n"
			, g_krgStronghold[iStronghold].iID, g_krgStronghold[iStronghold].iOwner
			, g_krgStronghold[iStronghold].kTimeOccupied.GetYear(), g_krgStronghold[iStronghold].kTimeOccupied.GetMonth()
			, g_krgStronghold[iStronghold].kTimeOccupied.GetDay(), g_krgStronghold[iStronghold].kTimeOccupied.GetHour()
			, g_krgStronghold[iStronghold].kTimeOccupied.GetMinute()
			) ;
		nBufLength = strlen( szData ) ;
		WriteFile( hFile, szData, nBufLength, &dwRetWrite, NULL ) ;
	}

	CloseHandle( hFile ) ;

	return eTNRes_Succeeded ;
}


// ������ a_iStronghold�� �����̶��, a_iClan������ set���ش�.
void RefreshClan( int a_iStronghold, int a_iClan, int a_iClear )
{
	if(a_iStronghold<0 || a_iStronghold>=eStronghold_MaxCount) return;

	for( int i = 1 ; i < MAX_USER ; ++i )
	{
		if( 1 == a_iClear )
		{// ������ �ֽ����� ������.
			a_iClan = pMob[i].MOB.byTrimuriti ;
			//pMob[i].m_byClan = pMob[i].MOB.byTrimuriti ;
		}

		if( pMob[i].MOB.nGuildID == g_krgStronghold[a_iStronghold].iOwner ) 
		{	pMob[i].m_byClan = (byte)a_iClan ; 
			continue;
		}
		else if( pMob[i].MOB.nGuildID == g_krgStronghold[a_iStronghold].iOwnerFriend ) 
		{	pMob[i].m_byClan = (byte)a_iClan ; 
			continue;
		}
		if(pMob[i].m_byClan == (byte)a_iClan) 
			pMob[i].m_byClan = pMob[i].MOB.byTrimuriti ;
	}
}


void ChangeClan( int a_iWho, int a_iClan )
{
	for( int i = 1 ; i < MAX_USER ; ++i )
	{
		if( USER_PLAY != pUser[i].Mode ) continue ;

		byte byOld = pMob[i].m_byClan;
		if( -1 == a_iWho ) // zone�� ������ �� �ִ� ��� pc
		{
			if( -1 == a_iClan ) pMob[i].m_byClan = pMob[i].MOB.byTrimuriti ;
			else pMob[i].m_byClan = a_iClan ;
		}
		else if( pMob[i].m_byClan == a_iWho )
		{
			if( -1 == a_iClan ) pMob[i].m_byClan = pMob[i].MOB.byTrimuriti ;
			else pMob[i].m_byClan = a_iClan ;
		}

		if( byOld != pMob[i].m_byClan )
		{
			MSG_CHANGE_CLAN kMsg;
			kMsg.snKeyID = i;
			kMsg.byClan = pMob[i].m_byClan;
			pUser[i].cSock.SendOneMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) ) ;

			S_SCP_INIT_OTHER_MOB sm ;
			GetCreateMob( i, &sm ) ;
			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0) ;
		}

		//MSG_CHANGE_TRIMURITI kMsg ;
		//kMsg.snKeyID = i ;
		//kMsg.byTrimuriti = pMob[i].m_byClan ;
		//pUser[i].cSock.SendOneMessage( (char*)&kMsg, sizeof(MSG_CHANGE_TRIMURITI) ) ;	
	}
}


//@Param
//	nStrongHold : ������ ��� ID
//	nGuild : ������ ��� ID
void UpdateStrongHold(int nStronghold, int nGuild, int a_iIntruder )
{
	if( SERVER_STRONGHOLD != g_iZoneID ) return ; //	������ϰ�� ���������Ʈ������ msg�� �̿��� �����Ѵ�.
	if( 0 > a_iIntruder || MAX_USER <= a_iIntruder ) return ;

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;

	int iGuildID = pGuild[nGuild].GUILD.GuildID ;

	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\r\n[UpdateStrongHold] %dyy%dmm%ddd %dhh%dms%dss > %d stronghold is occupied by a guild(%d, %s) \r\n"
			, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
			, nStronghold, iGuildID, pGuild[nGuild].GUILD.GuildName
			) ; 
		WriteLog( chBuf, ".\\Log\\[Log]Stronghold.txt" ) ;
	}

	// ��尡 ������ ����� �����ϰ� �ִ��� �˻�
	bool bChanged = false ;
	int iOldProperty = 0 ;
	for( int i = 0 ; i < eStronghold_MaxCount ; ++i )
	{
		//if( (g_krgStronghold[i].iOwner == iGuildID) || (g_krgStronghold[i].iOwnerFriend == iGuildID) ) // ������ �ٸ� ����� ������ �ִٸ�, �ʱ�ȭ�� ���ش�.
		if( g_krgStronghold[i].iOwner == iGuildID ) // ������ �ٸ� ����� ������ �ִٸ�, �ʱ�ȭ�� ���ش�.
		{
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "\t- [UpdateStrongHold] The guild have a another stronghold. that is %d and will be free.\r\n"
					, i
					) ; 
				WriteLog( chBuf, ".\\Log\\[Log]Stronghold.txt" ) ;
			}

			RefreshClan( i, 0, 1 ) ; // stronghold i�� �����ϰ� �ִ� PC���� clan�� clear�Ѵ�.
			memset( &(g_krgStronghold[i]), 0, sizeof(TNSTRONGHOLD) ) ;
			g_krgStronghold[i].iID = i ;
			iOldProperty = i ;
			CTime kTimeInitialized( 2005, 1, 1, 0, 0, 0 ) ;
			g_krgStronghold[i].kTimeOccupied = kTimeInitialized ;
			bChanged = true ;
		}

		if( g_krgStronghold[i].iOwnerFriend == iGuildID ) // �ڽ��� ���� ��尡 �ٸ� ����� �����ϰ� �ִ�. ������ ���ش�.
		{
			Msg_GuildAlliance sm; sm.wType = _Msg_GuildAlliance;
			sm.dwClientTick = CurrentTime + pUser[a_iIntruder].TickDiff;
			sm.byType = eGuildFriend; sm.byAct = eGuildAllianceOut;

			ProcessClientMessage(a_iIntruder, (char*)&sm);
		}
	}

	g_krgStronghold[nStronghold].iID = nStronghold ;
	g_krgStronghold[nStronghold].iOwner = pGuild[nGuild].GUILD.GuildID;
	g_krgStronghold[nStronghold].dwMark = pGuild[nGuild].GUILD.Mark;
	strcpy( g_krgStronghold[nStronghold].szGuildName, pGuild[nGuild].GUILD.GuildName ) ;
	g_krgStronghold[nStronghold].iOwnerFriend = GetGuildID(pGuild[nGuild].GUILD.AlliedGuildName1);
	CTime kTime( st ) ;
	g_krgStronghold[nStronghold].kTimeOccupied = kTime ;

	// �ű� ������ ����� ���� ����
	if( eStronghold_Northwest == nStronghold ) TriggerEvent( 0, 26, 0, 0, 0, 1100 ) ;
	else if( eStronghold_Northeast == nStronghold ) TriggerEvent( 0, 27, 0, 0, 0, 1101 ) ;
	else if( eStronghold_Southwest == nStronghold ) TriggerEvent( 0, 28, 0, 0, 0, 1102 ) ;
	else if( eStronghold_Southeast == nStronghold ) TriggerEvent( 0, 29, 0, 0, 0, 1103 ) ;

	if( bChanged )
	{
		// �̹� �����ߴ� ����� ���� ���� �� immunity ����, < Edited by spencer, 2005.05.31, �Ʒ��� event ID�� �����ؾ� �Ѵ�. >
		if( eStronghold_Northwest == iOldProperty ) TriggerEvent( 0, 155, 0, 0, 0, 1200 ) ;
		else if( eStronghold_Northeast == iOldProperty ) TriggerEvent( 0, 156, 0, 0, 0, 1201 ) ;
		else if( eStronghold_Southwest == iOldProperty ) TriggerEvent( 0, 157, 0, 0, 0, 1202 ) ;
		else if( eStronghold_Southeast == iOldProperty ) TriggerEvent( 0, 158, 0, 0, 0, 1203 ) ;		
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
	if( MAX_USER > a_iHandle || MAX_MOB <= a_iHandle ) return ;

	pMob[a_iHandle].MOB.nHP = 0 ;
	pMob[a_iHandle].CurrentTarget = 0 ;
	pMob[a_iHandle].m_eFSM = eTNFsm_Dead ;

	pMob[a_iHandle].DetermineNextPopTime( 20 ) ;
}

void ReturnPCToSaveZone( int a_iPC )
{
	if( (0 >= a_iPC ) || (MAX_USER <= a_iPC) ) return ;

	if( 0 >= pMob[a_iPC].MOB.bySaveZone )
	{
		pMob[a_iPC].MOB.bySaveZone = eZone_Mandra ; // Ȥ guild �� ���� ���
		pMob[a_iPC].MOB.snSaveX = 486 ; // ���ٶ��� ��Ż 486, 190
		pMob[a_iPC].MOB.snSaveZ = 190 ;		
	}
	
	BYTE byZoneToMove = pMob[a_iPC].MOB.bySaveZone ;
	HS2D_COORD kPos ;
	kPos.x = pMob[a_iPC].MOB.snSaveX ;
	kPos.y = pMob[a_iPC].MOB.snSaveZ ;

	if( eZone_Castle == byZoneToMove ) // ���� ��
	{
		byZoneToMove = eZone_Mandra ;
		kPos.x = 486 ;
		kPos.y = 190 ;
	}


	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;
	sm.byZone = byZoneToMove;
	sm.snX = (short)kPos.x;
	sm.snZ = (short)kPos.x;
	pMob[a_iPC].m_kWaitAction.iAction = eWaitAct_ZonePortal;
	pUser[a_iPC].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 


	//pMob[a_iPC].MoveZone( byZoneToMove, kPos.x, kPos.y ) ;
}



int PostMessageToZone( char* a_pMsg, int a_iTextColor, int a_iBGColor, int a_iMessage )
{
	if( NULL == a_pMsg ) return eTNRes_Failed ;
	//if( 0 > a_iMessage || MAX_STRING <= a_iMessage ) return eTNRes_Failed ;

	MSG_Broadcast kMsg ;
	//memset( &kMsg, 0, sizeof(kMsg) ) ;
	kMsg.wType = _MSG_Broadcast ;
	kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

	kMsg.byBgColor = a_iBGColor ;
	kMsg.byTextColor = a_iTextColor ;
	kMsg.byMsgType = 1 ; 

	strcpy( kMsg.szMsg, a_pMsg/*g_pMessageStringTable[a_iMessage]*/ ) ;
	strncpy( kMsg.szName, g_pMessageStringTable[_Announcement]/*"����"*/, SZNAME_LENGTH ) ;
	kMsg.byTrimuriti = eTNClan_GM ;

	SendToAll( (MSG_STANDARD*)&kMsg ) ;

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;

	{
		char chBuf[2048] = { 0,0,0, } ;
		sprintf(chBuf, "[eTNAct_PostMessageToZone] %dYY%dMM%dDD %dHH%dMI%dSS, MSGID:%d, %s\r\n"
			, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
			, a_iMessage, kMsg.szMsg ) ;
		WriteLog( chBuf, ".\\Log\\[Log]EventTriggered.txt" ) ;
	}

	if( 112 == a_iMessage ) // "Į���� ������ ���� ���Ƚ��ϴ�. �ֽ� ���� �ֽŻ��� Ŭ���ϼ���."
	{
		for( int iUser = 0 ; iUser < MAX_USER ; ++iUser )
		{	if( USER_PLAY != pUser[iUser].Mode ) continue ;
			SendClientMessage( iUser, g_pMessageStringTable[_OpenTheGate] ) ;
		}
	}

	return eTNRes_Succeeded ;
}


int PostMessageToWorld( char* a_pMsg, int a_iTextColor, int a_iBGColor, int a_iMessage )
{
	if( NULL == a_pMsg ) return eTNRes_Failed ;
	//if( 0 > a_iMessage || MAX_STRING <= a_iMessage ) return eTNRes_Failed ;

	MSG_Broadcast kMsg ;
	//memset( &kMsg, 0, sizeof(kMsg) ) ;
	kMsg.wType = _MSG_Broadcast ;
	kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

	kMsg.byBgColor = a_iBGColor ;
	kMsg.byTextColor = a_iTextColor ;

	strcpy( kMsg.szMsg, a_pMsg/*g_pMessageStringTable[a_iMessage]*/ ) ;
	kMsg.szMsg[MAX_NOTIFY_LENGTH-1] = 0 ; kMsg.szMsg[MAX_NOTIFY_LENGTH-2] = 0 ;
	strncpy( kMsg.szName, g_pMessageStringTable[_Announcement]/*"����"*/, SZNAME_LENGTH ) ;
	kMsg.byTrimuriti = eTNClan_GM ;
	kMsg.byMsgType = MESSAGE_POSTTOWORLD ;

	SYSTEMTIME st ;
	GetLocalTime( &st ) ;
	{
		char chBuf[2048] = { 0,0,0, } ;
		sprintf(chBuf, "[eTNAct_PostMessageToWorld] %dYY%dMM%dDD %dHH%dMI%dSS, MSGID:%d, %s\r\n"
			, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
			, a_iMessage, kMsg.szMsg ) ;
		WriteLog( chBuf, ".\\Log\\[Log]EventTriggered.txt" ) ;
	}

	if( !MSGServerSocket.SendOneMessage( (char*)&kMsg, sizeof(kMsg) ) )
	{	Log("err brodcast MSG-SEND POST A MESSAGE", "system", 0 ) ;
	}

	return eTNRes_Succeeded ;
}


void HT_PlayYut()
{
	int nTimer = YutCounter--%15;							//	15�ʸ��� �ݺ��Ǵ� task.
	switch(nTimer)
	{
	case 7:	//	������ ��������(���)
		{
            S_SCP_NOTIFY_CHAT nm;	nm.wType = SCP_NOTIFY_CHAT;					//	NPC Chat(���)
			nm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
			nm.nID=10000+1299;													//	��� + 10000(NPC�� ��� +10000�ϱ����)
			nm.byTextColor=12; nm.byBgColor = 0; nm.byTrimuriti=0;				//	���� �������� ����

			short snX, snY = 0;
			if(!g_ParamMgr.HT_bGetNPCPosition( 1299, &snX, &snY )) return;	//	�ش� NPC������ ���� ���Ұ��.

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
	case 5:	//	���� �̵�
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
			else		//	���� ���� �ึ�� �Ϸ��� ���
			{
				nX = 5;
				nZ = 5;

				BYTE byResult = g_Yut.HT_byGetResult();
				if(byResult>0 && byResult<6) Teleport( g_iGambleYut[byResult-1], 5, 5 ) ;
			}

			int tret = GetEmptyMobGrid(g_iGambleHorse,&nX,&nZ);
			if	(tret==FALSE)
			{	
#ifdef __YUT_LOG__				
				sprintf(temp,"err no empty space at HT_PlayYut x:%d y:%d \r\n",nX,nZ);
				TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__
				int tret = GetEmptyMobGrid(g_iGambleHorse,&nX,&nZ);
				if	(tret==FALSE)
				{	
#ifdef __YUT_LOG__					
					sprintf(temp,"err no empty space at HT_PlayYut x:%d y:%d \r\n",nX,nZ);
					TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
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
			TimeWriteLog(temp, ".\\LOG\\[Log]Yut.txt");
#endif	//	#ifdef __YUT_LOG__

			GridMulticast(g_iGambleHorse, nX, nZ, (MSG_STANDARD*)&sm, 200, ACTION_YUT);

#ifdef __YUT_LOG__
			sprintf(temp, "Yut_Horse move from x:%d y:%d MobGrid:%d to x:%d y:%d MobGrid:%d \r\n", nOldX, nOldY, pMobGrid[nOldY][nOldX], pMob[g_iGambleHorse].TargetX, pMob[g_iGambleHorse].TargetY, pMobGrid[pMob[g_iGambleHorse].TargetY][pMob[g_iGambleHorse].TargetX]);
			TimeWriteLog(temp, ".\\LOG\\[Log]Yut.txt");

			TimeWriteLog("���̵� \r\n",".\\LOG\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__
		}	break;
	case 3:	//	����������
		{	if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			int nEvent = g_Yut.HT_byGetPrePosition() + 36;

#ifdef __YUT_LOG__
			TimeWriteLog("������������ \r\n",".\\LOG\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__

			TriggerEvent(0, nEvent, 0, 0, 0, 0);

#ifdef __YUT_LOG__
			TimeWriteLog("������������ \r\n",".\\LOG\\[Log]Yut.txt");
			for(int x=653; x<678; x++)
			{
				for(int y=407; y<432; y++)
				{
					if(pMobGrid[y][x]==0) continue;
					sprintf(temp, "YutGrid[%d][%d] - ID:%d, MobPosX:%d, MobPosX:%d HP:%d, Mode:%d \r\n", y, x, pMobGrid[y][x], pMob[pMobGrid[y][x]].TargetX, pMob[pMobGrid[y][x]].TargetY, pMob[pMobGrid[y][x]].MOB.nHP, pMob[pMobGrid[y][x]].Mode); 
					TimeWriteLog(temp,".\\LOG\\[Log]Yut.txt");
				}
			}
#endif	//	#ifdef __YUT_LOG__
		}	break;
	case 2:	//	�������(��,��,��,��,�����)
		{
			if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			BYTE byResult = g_Yut.HT_byGetResult();

			if(byResult>0 && byResult<6)
							Teleport( g_iGambleYut[byResult-1], 5, 5 ) ;

			//	Teleport( g_Yut.HT_byGetResult(), 5, 5 ) ;
		}	break;
	case 0:	//	�������(��,��,��,��,�����)
		{
			if(g_Yut.HT_byGetPosition() >= MAX_POSITION) break;

			byte byResult = g_Yut.HT_byYutPlay();

			if(byResult>0 && byResult<6)
				Teleport( g_iGambleYut[byResult-1], 666, 419 ) ;
		}
	}
}


int CountMonster( int a_iTribe )
{
	int iCount = 0 ;
	for( int i = MAX_USER ; i < MAX_MOB ; ++i )
	{
		if( MOB_EMPTY == pMob[i].Mode ) continue ;
		if( a_iTribe == pMob[i].MOB.snTribe ) ++iCount ;
	}

	return iCount ;
}

void DumpMobile( int a_iHandle )
{
	if( 0 >= a_iHandle || MAX_MOB <= a_iHandle ) return;

	FILE* fOut = NULL;
	char szFileName[64] = { 0,0,0,};
	sprintf( szFileName, ".\\Log\\%s_%d.dum", pMob[a_iHandle].MOB.szName, a_iHandle );
	fOut = fopen( szFileName, "wb" );
	if( NULL == fOut ) return;

	fwrite( (void*)&pMob[a_iHandle], sizeof(CMob), 1, fOut );

	fclose( fOut );
}


void LoadDump( char* a_pFileName )
{
	FILE* fIn = NULL;
	char szFileName[64] = { 0,0,0,};
	sprintf( szFileName, ".\\Log\\%s.dum", a_pFileName );

	fIn = fopen( szFileName, "rb" );
	if( NULL == fIn ) return;

	CMob kDump;
	fread( (void*)&kDump, sizeof(CMob), 1, fIn );

	fclose( fIn );
}

bool SetGameEvent(int iHandle, DWORD dwGameEventID, int* piParam)
{
	if(iHandle<=0 || iHandle>=MAX_USER) return false;
	if(dwGameEventID == 0) return false;

	//	�ִ� ���� 4*8 ���� �����ϳ� 8���� ����ϱ�� �Ѵ�.
	for(int i=0; i<8; i++)
	{
		DWORD dwFlag = 0x00000001 << i;
		if((dwGameEventID & dwFlag) == 0) continue;

		sprintf(temp, "Event:%X, Flag:%X, account:%s \r\n", dwGameEventID, dwFlag, pUser[iHandle].AccountName);
		TimeWriteLog(temp, "Data\\EVENT.TXT");

		for(int k=0; k<5; k++)
		{
			int iAction = g_kGameEvent[i].stAction[k].iAction;
			if(iAction==0) continue;

			switch(iAction)
			{
			case eTNAfn_PranaRatebyLevel:			//	��ɽ� ȹ������ �������� ��� �� ����(��������)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
                        pMob[iHandle].m_dGetPranaRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_MoneyRatebyLevel:			//	���Ǿ� ����� ����Ȯ���� ��� �� ����(��������)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
						pMob[iHandle].m_dGetMoneyRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_DeathPranaRatebyLevel:		//	����� ���� ������ ��� �� ����(��������)
				{
					if(pMob[iHandle].MOB.byLevel < g_kGameEvent[i].stAction[k].iParam2)
						pMob[iHandle].m_dCutDeathPranaRate = g_kGameEvent[i].stAction[k].iParam1;
				}	break;
			case eTNAfn_LevelUpFromLevel1:			//	������ ����1���
				{
					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow) break;
					if(pMob[iHandle].MOB.byLevel>iLevelHigh) break;
					pMob[iHandle].LevelUp();
					pMob[iHandle].Init( iHandle ) ;
					pMob[iHandle].NotifyUpdateUIMsg() ;
				}	break;
			case eTNAfn_LevelUpFromLevel3:			//	������ ����3���
				{
					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow) break;
					if(pMob[iHandle].MOB.byLevel>iLevelHigh) break;
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].LevelUp();
					pMob[iHandle].Init( iHandle ) ;
					pMob[iHandle].NotifyUpdateUIMsg() ;
				}	break;
			case eTNAfn_LevelUpFromLevel5:			//	������ ����5���
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
					pMob[iHandle].Init( iHandle ) ;
					pMob[iHandle].NotifyUpdateUIMsg() ;
				}	break;
			case eTNAfn_GiveItem:				//	����������(�ڸ������� ����)
				{
					int iItemIndex = g_kGameEvent[i].stAction[k].iParam1;
					int iCount = g_kGameEvent[i].stAction[k].iParam2;
					GiveItem(iHandle, iItemIndex, iCount);
				}	break;
			case eTNAfn_ChangeTribeFromLevel:	//	��������
				{
					for(int j=0; j<8; j++)
					{
						if(*piParam == (short)pow(2, j)) break;
					}

					if(j==8) return false;			//	�������� �׼ǽ���(�߸��� �������� ���)

					int iLevelLow = g_kGameEvent[i].stAction[k].iParam1;
					int iLevelHigh = g_kGameEvent[i].stAction[k].iParam2;
					if(pMob[iHandle].MOB.byLevel<iLevelLow || pMob[iHandle].MOB.byLevel>iLevelHigh) return false;

					pMob[iHandle].MOB.snTribe = *piParam;
					//	1���������¸� class2 �׸��� ���� �ٲ��ش�
					//	2���������¸� 1���������·� �ٲ��ش�
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

					// �� ������ ������ mob�鿡�� �����Ѵ�.
					int tx = pMob[iHandle].TargetX; int ty = pMob[iHandle].TargetY;
					S_SCP_INIT_OTHER_MOB sOther;
					GetCreateMob(iHandle,&sOther); 
					GridMulticast(tx,ty,(MSG_STANDARD*)&sOther, iHandle);
				}	break;
			//case eTNAfn_Attendence:				//	�⼮üũ
			//	{
			//		bool bRet = g_GameEvent.CheckDate(pUser[iHandle].AccountName);

			//	}	break;
			case eTNAfn_Coupon:						//	������� - ����������(1������ ���ް���)
				{
					char* pData = (char*)(piParam+4);
					if(GetEmptyInvenCount(iHandle)==0) return false;	//	�κ��丮�� Ǯ�ϰ��(������ 1�� �̹Ƿ� Ǯ���ƴϸ� ���޵ȴ�)
					bool bRet = g_GameEvent.m_Coupon.UseCoupon(pData);
					if(!bRet) return false;

					int iItemIndex1 = g_kGameEvent[i].stAction[k].iParam1;
					int iItemCount = g_kGameEvent[i].stAction[k].iParam2;
					GiveItem(iHandle, iItemIndex1, iItemCount);
				}	break;
			case eANAfn_GiveItemMaharaja:
				{
					if(pUser[iHandle].nGuildLevel != eGuildMaster) return false;	//	���϶��ڿ��Ը� �ش��ϴ� �̺�Ʈ�̴�
					if((k+GetEmptyInvenCount(iHandle)) < 5) return false;			//	�ִ� 5���� �������� �����ִ�

					int iItemIndex = g_kGameEvent[i].stAction[k].iParam1;
					int iCount = g_kGameEvent[i].stAction[k].iParam2;
					GiveItem(iHandle, iItemIndex, iCount);
				}
			default:
				{

				}	break;
			}
		}

		if(g_kGameEvent[i].iType == 0)	//	��ȸ�� �̺�Ʈ�ϰ��
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


			pUser[iHandle].m_dwEvent -= pow(2, i);
		}
	}

	return true;
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