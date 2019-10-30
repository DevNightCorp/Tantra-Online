#include <windows.h>
#include <stdio.h>
//#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include "Basedef.h"
#include "Server.h"
#include "CMob.h"
#include "ItemEffect.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "CUser.h"
#include "Quest.h"
#include "HTParamMgr.h"
#include "CNPCGene.h"
#include "TNInfluenceMap.h"
#include "TNRate10000.h"
#include "TNDeck10000.h"
#include "TNDeck1000.h"
#include "TNKalaSystem.h"
#include "TNSiege.h"
#include "Language.h"
#include "CGuild.h"
#include "TNArena.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

//enum { eTNCnt_MobSummoned = 23, };
//int g_iMobSummoned[eTNCnt_MobSummoned] = { 2124, 2125, 2126, 2127, 2226, 2241, 2238, 2246, 2247, 2248, 2249, 2071, 2072, 2447, 2198, 2850, 2190, 2851, 2469, 2221, 2217, 2470, 0, };
enum { eTNCnt_MobSummoned = 34, };
int g_iMobSummoned[eTNCnt_MobSummoned] = {
											2071, 2072, 2124, 2125, 2126, 2127, 2169
											, 2217, 2221, 2226, 2238, 2241, 2246, 2247, 2248, 2249
											, 2427, 2430, 2434, 2447, 2460, 2470, 2473
											, 2543, 2544, 2545, 2546, 2547, 2548, 2549
											, 2850, 2851
											, 0
											};

//2190 2469 2198
//2547 2548 2549

/*
±¸´Ù(2447)
Ä®¸®¾Æ Å÷µ¥¶ó(2198) ¼ÒÈ¯

»õ·Î¿î ¼ÒÈ¯¹°(2850) 
Ä®¸®¾Æ ¹«¶ó¶ó(2190) ¼ÒÈ¯

»õ·Î¿î ¼ÒÈ¯¹°(2851)
ÀÚÇÁÅ¸(2469) ¼ÒÈ¯


// Added by spencer, 12th, June, 2006

¿ä¼ú·¥ÇÁ 2

2238  »ó¹®´ë°ü
2241  Ç³¼ö´ë°ü
2246  È¯¿µ¼­½Ã
2247  È¯¿µ´ë±³
2248  È¯¿µÃÊ¼±
2249  È¯¿µ¼­½Ã
2427  °«ÆÄÁ·Àå
2434  ¸Þ
2473  ½Î¿ï¾Æºñ Àå±º
2430  ½Î¿ï¾Æºñ Àå±º

¿ä¼ú·¥ÇÁ 3

2246  È¯¿µ¼­½Ã
2247  È¯¿µ´ë±³
2248  È¯¿µÃÊ¼±
2249  È¯¿µ¼­½Ã
2427  °«ÆÄÁ·Àå
2434  ¸Þ
2473  ½Î¿ï¾Æºñ Àå±º
2543  Áö±¹ÃµÈ²
2544  ´Ù¹®ÃµÈ²
2545  ±¤¸ñÃµÈ²
2546  ÁõÀåÃµÈ²
2430  ½Î¿ï¾Æºñ Àå±º

Åä¿ë ¼ÒÈ¯±Ç
2852  Åä¿ë ¸ó½ºÅÍ

¸ó½ºÅÍ ¼ÒÈ¯±Ç
2850 Áß·¾ Ä®¸®¾Æ ¼ÒÈ¯(2169¸¦ ¼ÒÈ¯)
2851 °í·¾ ÀÚÇÁÅ¸ ¼ÒÈ¯(2851À» ¼ÒÈ¯)

2169 Áß·¾ Ä®¸®¾Æ ¼ÒÈ¯
2460 °í·¾ ÀÚÇÁÅ¸ ¼ÒÈ¯

¿ä¼ú·¥ÇÁ 1

2124  »ç¹«¾ßÅ¸(È¯´ë¿Õ)
2125  ³ª¾ß¹Ù»ê(ÃµÈ£)
2126  ¼öÄ¯(ÆØÈÄ)
2127  °¡Æ®¹Ù(¿°¶óº´)
2071  ³ª°¡¹«µå¶ó È÷¸¶
2072  ¸Þ±×ÇÏ¸»¸°
2241  Ç³¼ö´ë°ü
2238  »ó¹®´ë°ü
2246  È¯¿µ¼­½Ã
2247  È¯¿µ´ë±³
2473  ½Î¿ï¾Æºñ Àå±º



*/

extern unsigned int CurrentTime;
extern TNCELL              g_krgCell[MAX_GRIDY][MAX_GRIDX];
//extern unsigned short         pMobGrid   [MAX_GRIDY][MAX_GRIDX];
//extern CMob                   pMob     [MAX_MOB];  // Àß¸ø¼³°èÇßÀ½.
//extern CItem				  pItem	   [MAX_ITEM];
//extern TNITEM_DATA            pItemData	[MAX_ITEM_DATA];
//extern TNSKILL_DATA           pSkillData	[MAX_SKILL_DATA];
//extern STRUCT_MOB             pMonsterData[MAX_MONSTER_DATA];
//extern CGuild					pGuild[MAX_USER];
extern int                    g_irgLevelUp[TN_MAX_LEVEL];
extern TNRate10000            g_krgRewardItemRate[MAX_MONSTER_DATA][10];
extern TNArena				  g_kArena;
extern short                  g_srgItemGroup[eRwd_ItemGroup][eRwd_ItemGroupCount];
extern short                  g_srgGroupItemCount[eRwd_ItemGroup];
extern STRUCT_ITEM            g_krgItemByLevel[eItm_MaxCategory][eItm_MaxLevel];
extern TNDeck10000            g_krgItemRateByMonLevel[eMonster_MaxLevel];
extern TNDeck1000             g_kRateByItemCategory;
extern TNCOEFFICIENT          g_krgCoefficientByClass[eCls_MaxLevel][eCls_MaxSpecialized];
extern TNEFFECTTOLERANCE		g_krgEffectTolerance[eCls_MaxLevel][eCls_MaxSpecialized];
extern TNCONSIDER              g_krgConsider[eCon_Sort][eCon_Sort];
extern int                    g_pRefineTable[4][MAX_MAINREFINELEVEL];
extern int                    g_iHostileTable[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTablePKOn[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTablePKOff[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTable[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTableRvR[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTableRvR[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTableStrH[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTableStrH[MAX_CLAN][MAX_CLAN];
extern int                    g_pDirectionalTable[9][9];
extern char                   g_pAggrCorrect[eCls_MajorCount][eCls_MinorCount];
extern int                    g_pKnockbackTable[9][2];
extern short                   g_pDetectEnemyRadius[eRds_MaxDetectEnemy+1];
extern char                   g_pDetectEnemyTable[ePos_MaxPosCount][2];
extern TNJUDGE_COMBAT_VALUE    g_krgJudgeCombat[2][2];
extern int                     g_irgRvRPKConsider[eCaste_MaxLevel][eCaste_MaxLevel];
extern int                     g_irgRewardBP[eCaste_MaxLevel];
extern short			      g_krgRoamPath[eRoam_MaxPathCount][8];
extern int                    g_pSkillPatternTable[eSklPtrn_Count][eSklPtrn_Size];
extern TNSPEECH_CONTENT         g_krgSpeechContent[eTNSpch_MaxContentCount+1];
extern char                    g_szrgComment[eTNSpch_MaxCommentCount+1][101];
extern short                   g_srgAIList[eTNAI_MaxAICount+1][eTNAI_MaxEventSort+1];
extern TNACTION_LIST            g_krgActionList[eTNAI_MaxActionListCount+1];
extern TNACTION                g_krgAction[eTNAI_MaxActionCount+1];
extern int                     g_irgSetting[MAX_SETTING];
extern double                  g_drgRwdCorrect[eSiz_RwdCorrect][eSiz_Type];
//extern double                 g_dRwdPranaCorrect;
//extern double                 g_dRwdGoldCorrect;
//extern double                 g_drgRwdCorrect[eRwd_Item][eRwd_Total];
extern int						g_nGiftItemMaxCount;
extern int						g_nGiftItemCount;
//extern short					g_snGiftItemGenTime = 0;
extern STRUCT_ITEM				GiftItem;
extern int  ServerIndex;
extern int  ServerDown;
extern int                     g_iViewGridX;
extern int                     g_iViewGridY;
extern int                     g_iHalfGridX;
extern int                     g_iHalfGridY;
//extern bool                    g_bIsInRvR;
extern int                     g_iZoneType;
extern                  g_iWorldID; // º»¼·Àº 1,2,3, Å×¼·Àº 0, ±âÁØÀÇ º»¼·ÀÌ¹Ç·Î default·Î 1À» ¼³Á¤
extern TNSTRONGHOLD			   g_krgStronghold[eStronghold_MaxCount];
extern TNEVENT                 g_krgEventList[eEvent_MaxCount];
extern TNTASK                  g_krgTaskList[eTask_MaxCount];
//extern int                     g_irgKalaAltar[eKalaAltar_MaxCount];
extern TNKALA_ALTAR_OLD            g_krgKalaAltar[eKalaAltar_MaxCount];

extern TNAGGRSCORE             g_krgAggrScore[eAggrScore_MaxCount];
extern int                     g_irgSpeedConsider[6];
extern int                     g_iMonsterLevelForWritingLog;
//extern int                     g_iEnemyCount;
extern bool                    g_bDecPrana;
extern TNDeck10000             g_krgBlessOfGod[eBlss_MaxSort][5];
extern int                     g_irgGod[2][5];
extern CNPCGenerator          mNPCGen;
extern int						g_iSwitch;
//extern int						g_irgArenaEntry[eArena_MaxEntry];
//extern int						g_iArenaEntryCount;
extern CPSock                 MSGServerSocket;
#ifdef __TN_PLAYMOVIE__
extern int                     g_irgFlag[10];
#endif

extern void MoveKalaRewarder();
//extern void ControlSystem( int a_iHandle, char* a_pCmd );
//extern void ChangeRwdCorrect( int a_iPrana, int a_iGold, int a_iBP );
extern void	SharePrana( int a_iParty, int a_iPrana, int a_iCorpse, bool a_bApplyCorrect, int a_iMlevel );
extern void ShareBramanPoint( int a_iParty, int a_iBP, int a_iCorpse );
extern int Percent( double a_dValue, double a_dPercent );
extern void NotifyRvRStatus();

extern CMob * GetMobFromIndex(unsigned int idx);
extern void Log(char * str1,char * str2,unsigned int ip);
extern STRUCT_ITEMLIST   g_pItemList[MAX_ITEMLIST];
//extern CUser pUser[MAX_SERVER];
extern CHTParameterMgr g_ParamMgr;
extern E_COUNTRY_ID		g_eCountryID;

static int g_irgPartyVSParty[7] = { 1, 1, 1, 2, 2, 3, 3, }; // 1~2 => 1¸¶¸®, 3~4 => 2¸¶¸®, 5~6 => 3¸¶¸® ´ëÀÀ
extern char temp[1024];

unsigned int           mSecCounter = 0;
unsigned int           mCurrentTime  = 0;
#define GetMobMyRandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min));
// true¸é gridx,gri
CMob::CMob()
{  
	Mode    = MOB_EMPTY;
	LastX   = 0xFFFFFFFF;
	LastY   = 0xFFFFFFFF;
	Leader  = 0;
	WaitSec = 0;
	PotionCount = 0;
	Summoner = 0;
	GuildDisable=0;
	//nPartyLevel = 0;
	byMaxInven = MAX_ONEINVEN;
	byRootingMode = 0;
	GenerateIndex = -1;

	Init();
}
CMob::~CMob()
{
	//DeleteCriticalSection( &m_cs );
}

// ÃÊ±âÈ­¿¡ ´ëÇØ¼­ ¿©·¯ Á¾·ù·Î ºÐ·ù¸¦ ÇØ¾ß ÇÑ´Ù.
// 4ÃÊ¿¡ ÇÑ¹ø ºÒ¸°´Ù.
// Player´Â Regen¿¡, Battle¸¿Àº 1/2¿¡ StandingBy¸¿Àº ¸Å¹ø ºÒ¸°´Ù.
void CMob::Init()
{
	m_iHandle = 0;
	m_eMobType = eTNMob_NPC;
	m_iCaste = eTNCaste_Sudra3;
	m_byClan = eTNClan_NoTrimuritiy;
	m_iMaxHP = 0;
	m_iMaxTP = 0;
	m_iMaxPrana = 0;
	m_iWeaponCoefficient = 0;
	m_iLastDamage = 0;
	CurrentTarget = 0;

	m_iMoveSpeed = eTNChr_MoveSpeed;
	m_iAttackSpeed = eTNChr_PistAttackSpeed;
	m_sAttackSpeedCorrect = 0;
	m_sCastSpeedCorrect = 0;
	m_kSight.sPeace = 7;
	m_kSight.sCombat = 25;
	m_iAffections = 0;
	m_iInnerAffections = 0;
	m_iPrevAffections = 0;
	m_isBlessGod = 0;
	//m_iNBRank = 0;
	m_iUserWhat = 0;
	m_iCombatSyncPhase = eTNCSP_Calculate;

	memset( m_uirgAttackTimeRecord, 0 , sizeof(m_uirgAttackTimeRecord) );
	m_iAttackTimeRecordIndex = 0;
	
	m_iBlockedCell = eTNCell_Blocked;
	m_iCantDetect = eTNEye_DetectVisibleOnly;
	m_iReactToEnemyBehindWall = 1;
	m_iImmunity = 0;
	m_byBodyRadius = 0;
	m_bDualWeapon = false;	
	m_bIsInArenaEntry = false;

	m_sLastItemUsed = 0;
	m_byLastItemUsedCount = 0;
	m_byLastItemUsedLoc = 0;

	m_iPartySize = 0;
	m_iButtonStatus = eTNBtn_PK;
	m_iDebugFlag = 0;
	m_iDebugFlag2 = 0;
	m_iDebug = eTNDbg_None;
	m_iFamily = 0;
	//m_bSolo = true; // server.cpp > Generatemob()¿¡¼­ ÃÊ±âÈ­¸¦ ÇØÁØ´Ù.
	//m_iGroup = 0;
	m_iCastCount = 0;
	m_uiActionLock = 0;
	m_uiActionDelay = 1000; // ±âº» delay´Â 1ÃÊÀÌ´Ù.
	m_iAttackerCount = 0;	
	m_iAttackCount = 0;
	m_iTraceCount = 0;
	m_iTotalTraceCount = 0;
	m_iPathProgress = 0;
	m_iPathIndex = 0;
	m_iCantTraceTarget = 0;	
	//m_iEnemyCount = 0;
	m_iCheckEnemyCount = 3; // default : 3¸¶¸®(¸¸ ÃßÀûÀ» ÇÑ´Ù.)
	m_iIgnoreObstacle = 0; // Àå¾Ö¹°À» ¹«½ÃÇÏ°í °ø°ÝÇÏ±â ¼³Á¤(0:Àå¾Ö¹° °Ë»ç, 1:Àå¾Ö¹° ¹«½Ã)
	m_iSkillCharged = 0;
	m_iSkillPatternIndex = 0;
	m_uiPkDurTime = 0;
	m_iPKDefender = 0;
	m_eStatus = eTNSts_None;
	m_uiResistEffectTime = 0; 
	m_iLinker = 0;
	m_iPassenger = 0;
	//m_iFamiliar = 0;
	//m_iRetainer = 0;
	for( int i = 0; i < eFellow_MaxCount; ++i ) m_irgSummoned[i] = 0;
	m_iAIOption = eTNAIO_None;
	m_uiLifeTime = 0;
	m_snSaveNPC = 0;
	//m_iTargetHandle = 0;

	m_iMvLogIndex = 0;
	m_iAggressiveCorrect = 10;
	m_iAggressiveScore = 0;

	m_kMoveRecord.iSpeed = m_iMoveSpeed;
	m_kMoveRecord.kPos.x = 0;
	m_kMoveRecord.kPos.y = 0;
	m_kMoveRecord.uiElapsed = 0;
	m_kMoveRecord.behackedcount = 0; //fors_debug add cnt to check speed hack
	m_kMoveRecord.nohackcount = 0;

	m_iDirection = 0;
	m_iHPProblem = 0;	

	m_iCountKilled = 0;

	m_bMoveZone = false;

	if(MOB.nHP<=0)
		m_eFSM = eTNFsm_Dead;
	else
		m_eFSM = eTNFsm_Stand;

	#ifdef __TN_PLAYMOVIE__
	for( int i = 0; i < 10; ++i ) m_irgFlag[i] = 0;
	for( int i = 0; i < eRobot_MaxCount; ++i ) m_irgRobot[i] = 0;
	#endif
}



void CMob::Init( int a_iHandle )
{
	Init();

	m_iHandle = a_iHandle;
	if( 0 < a_iHandle && MAX_USER > a_iHandle ) m_eMobType = eTNMob_PC;
	else m_eMobType = eTNMob_NPC;

	if( eTNMob_PC == m_eMobType ) sprintf( m_szLogFile, ".\\monster_log\\PC_%s.txt", MOB.szName );
	else if( eTNMob_NPC == m_eMobType ) sprintf( m_szLogFile, ".\\monster_log\\Monster_%d_%d.txt", MOB.snTribe, m_iHandle );



	memset( &m_kChakra, 0, sizeof(m_kChakra) );
	memset( &m_kCombatFactors, 0, sizeof(m_kCombatFactors) );
	memset( m_irgHPRecovery, 0, sizeof(m_irgHPRecovery) );
	memset( m_irgTPRecovery, 0, sizeof(m_irgTPRecovery) );
	m_kCPRemaining.Init( 0, 0 );
	m_kSPRemaining.Init( 0, 0 );
	m_kCasteSPRemaining.Init( 0, 0 );
	m_kMagicShield.Init( 0, 0 );
	m_kEnhancedMagicShield.Init( 0, 0 );
	//m_kMurderDropRate.Init( 0, 0 );
	//m_kInnocentDropRate.Init( 0, 0 );
	//m_kFirstStrikerDropRate.Init( 0, 0 );
	m_kWeaknessRate.Init( 0, 0 );
	m_kDualHit.Init( 0, 0 ); // ÀÌµµ·ù
	unsigned int uiPrevTimeKilled = m_kLastTime.uiKilled;
	m_kLastTime.Init( CurrentTime );
	memset( m_krgDamage, 0, sizeof(m_krgDamage) );
	memset( m_krgWeaponDamage, 0, sizeof(m_krgWeaponDamage) );
	memset( m_krgVariation, 0, sizeof(m_krgVariation) );
	memset( m_krgMastery, 0, sizeof(m_krgMastery) );
	m_krgMastery[eWpnMtryIdx_DualWpn].iParam1 = 0;
	m_krgMastery[eWpnMtryIdx_DualWpn].iParam2 = 0;
	//memset( m_krgSkill, 0, sizeof(m_krgSkill) );
	for( int i = 0; i <= MAX_SKILL; ++i )
	{
		m_krgSkill[i].sID = 0;
		m_krgSkill[i].byLevelPlus = 0;
		m_krgSkill[i].byDummy = 0;
		m_krgSkill[i].uiCoolDownTime = 0;
		m_krgSkill[i].iIndex = 0;
		memset( &m_krgSkill[i].kDamage, 0, sizeof(TNDAMAGE) );
		m_krgSkill[i].kDeck.Init();
	}

	for( int i = 0; i <= eRst_Max; ++i )
	{
		m_krgResistEffect[i].Init( 0 );
	}
	
	memset( &m_kSkillCastRecord, 0, sizeof(m_kSkillCastRecord) );
	memset( m_uirgInstantCoolDownTime, 0, sizeof(m_uirgInstantCoolDownTime) );	
	memset( m_uirgCooldownTime, 0, sizeof(m_uirgCooldownTime) );
	ClearAffection();
	memset( &m_kWaitAction, 0, sizeof(m_kWaitAction) );
	memset( &m_kPrevSkill, 0, sizeof(m_kPrevSkill) );
	memset( m_krgAttacker, 0, sizeof(m_krgAttacker) );
	m_kMovement.Init( 0, 0 );
	m_kAggrCond.Init( 0, 0 );
	memset( m_krgPath, 0, sizeof(m_krgPath) );
	memset( &m_krgPathFinded, 0, sizeof(m_krgPathFinded) );		
	//m_iPlusRange = 0;
	memset( m_irgSkillPattern, 0, sizeof(m_irgSkillPattern) );
	m_kSelectTarget.Init();
	memset( &m_kCond, 0, sizeof(m_kCond) );
	set_JudgeCombat();
	memset( m_irgFollower, 0, sizeof(m_irgFollower) );
	memset( m_krgMoveLog, 0, sizeof(m_krgMoveLog) );
	memset( &m_kTolerance, 0, sizeof(m_kTolerance) );
	memset( &m_krgSetItem, 0, sizeof(m_krgSetItem) );

	m_byClan = MOB.byTrimuriti;

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	if( eTNMob_PC == m_eMobType )
	{
		sprintf( m_szLogFile, ".\\monster_log\\PC_%s.txt", MOB.szName );

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\r\n\n\n====================================================================================\r\n[Init] %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, ÁÖ½Å:%d, Á¾Á·:%d, level:%d, class1:%d, class2:%d, Chakra(%d,%d,%d,%d) \r\n"
				, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, m_byClan, MOB.snTribe, MOB.byLevel, MOB.byClass1, MOB.byClass2, MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
		if( 0 > MOB.nRupiah )
		{
			#ifdef __TN_TOP_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "Gold ¿À·ù> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, µ·:%d \r\n", g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, MOB.nRupiah );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}
			#endif // __TN_TOP_LOG__
			MOB.nRupiah = 0;
		}
		if( 0 > MOB.nPrana )
		{
			#ifdef __TN_TOP_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "Prana ¿À·ù> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, ÇÁ¶ó³ª:%d \r\n", g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, MOB.nPrana );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}
			#endif // __TN_TOP_LOG__

			MOB.nPrana = 0;
		}

		if( 0 > MOB.nHP )
		{
			#ifdef __TN_TOP_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "HP ¿À·ù> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, HP:%d \r\n", g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, MOB.nHP );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}
			#endif // __TN_TOP_LOG__

			MOB.nHP = 10;
		}

		if( 0 > MOB.byClass1 || eCls_MaxLevel <= MOB.byClass1 )
		{// 1Â÷ ÀüÁ÷ »óÅÂ error
			MOB.byClass1 = 0;
			#ifdef __TN_TOP_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "Á÷¾÷(class) ¿À·ù> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, m_iHandle:%d, class1:%d, class2:%d \r\n", g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, m_iHandle, MOB.byClass1, MOB.byClass2 );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}
			#endif // __TN_TOP_LOG__
		}

		if( 0 > MOB.byClass2 || eCls_MaxSpecialized <= MOB.byClass2 )
		{ // Á÷¾÷ ¼¼ºÐÈ­ error
			#ifdef __TN_TOP_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "Á÷¾÷(class) ¿À·ù> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, m_iHandle:%d, class1:%d, class2:%d \r\n", g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName, m_iHandle, MOB.byClass1, MOB.byClass2 );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			}
			#endif // __TN_TOP_LOG__

			if( 0 == MOB.byClass1 || 1 == MOB.byClass1 )
			{
				if( (TRIBE_NAGA==MOB.snTribe) || (TRIBE_KINNARA==MOB.snTribe) ) MOB.byClass2 = 0;
				else if( (TRIBE_ASURA==MOB.snTribe) || (TRIBE_RAKSHASA==MOB.snTribe) ) MOB.byClass2 = 1;
				else if( (TRIBE_YAKSA==MOB.snTribe) || (TRIBE_GANDHARVA==MOB.snTribe) ) MOB.byClass2 = 2;
				else if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) ) MOB.byClass2 = 3;
			}
		}			

		if( (TRIBE_YAKSA==MOB.snTribe) || (TRIBE_GANDHARVA==MOB.snTribe) )
		{ // skill ²¿ÀÌ´Â ¹®Á¦ ÇØ°áÀ» À§ÇÑ hard-cording
			// 6:¹Ùµå, 24:Æ¼¾ÆÀÚÆ¼, 29:±¸³ªÀÚ»çÆ®, 30:¾Æ±×´ÏÆÄ¶óÄ«, 40:Ä«µµ¶óÀÌ, 43:ÀÚ»çÆ®, 60:»ç¹«´Ù¹Ù, 61:ÀÚ´ÏÆ¼ÆÄ¶ó, 2:¹Ù·ç³ªÆ÷½º
			enum { eSklIdx_1 = 6, eSklIdx_2 = 24, eSklIdx_3 = 29, eSklIdx_4 = 30, eSklIdx_5 = 40, eSklIdx_6 = 43, eSklIdx_7 = 60, eSklIdx_8 = 61, eSklIdx_9 = 2, };

			#ifdef __TN_CHANGE_5LVL__
			//if( 5 < MOB.bySkill[eSklIdx_9] ) MOB.bySkill[eSklIdx_9] = 5; // ¹Ù·ç³ªÆ÷½º 5·¦Á¦
			#endif
			
			if( 2 > MOB.byClass1 )
			{// 2Â÷ ÀüÁ÷ÇÏ±â ÀÌÀüÀÌ´Ù. ±×·±µ¥ ÃÊ±âÈ­¸¦ ÇÏÁö ¾Ê¾Ò´Ù¸é, ... °­Á¦ ÃÊ±âÈ­!!!											
				int iFault = 0;
				if( 0 < MOB.bySkill[eSklIdx_1] ) iFault = 1;
				else if( 0 < MOB.bySkill[eSklIdx_2] ) iFault = 2;
				else if( 0 < MOB.bySkill[eSklIdx_3] ) iFault = 3;
				else if( 0 < MOB.bySkill[eSklIdx_4] ) iFault = 4;
				else if( 0 < MOB.bySkill[eSklIdx_5] ) iFault = 5;
				else if( 0 < MOB.bySkill[eSklIdx_6] ) iFault = 6;
				else if( 0 < MOB.bySkill[eSklIdx_7] ) iFault = 7;
				else if( 0 < MOB.bySkill[eSklIdx_8] ) iFault = 8;

				if( 5 < MOB.bySkill[eSklIdx_5] ) iFault = 5; // Ä«µµ¶óÀÌ 5·¦ ÃÊ°ú½Ã

				if( iFault )
				{// ½ºÅ³ÀÌ ²¿¿© ÀÖ´Ù.
					ResetSkill();
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SkillInitialized] );
				}
			}
			
			if( 2 == MOB.byClass1 && 4 == MOB.byClass2 ) MOB.bySkill[22] = 0; //³ªÄ«À¯´Ù(°Ý°£) ½ºÇª¶ó ¾Æ»ç¶ó: 3245 »õ·ÎÃß°¡µÈ ID , 3223
		}
		else if( (TRIBE_ASURA==MOB.snTribe) || (TRIBE_RAKSHASA==MOB.snTribe) )
		{
			// 2:¾ÈÄ«³ª
			enum { eSklIdx_1 = 2, eSklIdx_2 = 30, eSklIdx_3 = 13, };
			//if( 3 < MOB.bySkill[eSklIdx_1] ) MOB.bySkill[eSklIdx_1] = 3; // ¾ÈÄ«³ª 3·¹º§ Á¦ÇÑ
			MOB.bySkill[eSklIdx_2] = 0; // ·ÎÇÏÆ¼(3131) ½ºÅ³ ÃÊ±âÈ­
			//MOB.bySkill[eSklIdx_3] = 0; // Áê¹Ù½º(3114) ½ºÅ³ ÃÊ±âÈ­		//fors_debug ¿´ÊÇ²»ÊÇÕâÀïÈ¡ÏûÁËCKµÄFC	
		}
		else if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) )
		{
			// 24:µ¥½ºÆ¼
			enum { eSklIdx_1 = 24, eSklIdx_2 = 9, };
			//if( 3 < MOB.bySkill[eSklIdx_1] ) MOB.bySkill[eSklIdx_1] = 0; // µ¥½ºÆ¼ ½ºÅ³ ÃÊ±âÈ­
			if( 5 < MOB.bySkill[eSklIdx_2] ) MOB.bySkill[eSklIdx_2] = 5; // ¹«Å©Æ¼·ÎÄ« ½ºÅ³ 5·¦Á¦
		}
		else if( (TRIBE_NAGA==MOB.snTribe) || (TRIBE_KINNARA==MOB.snTribe) )
		{
			//2:¹Ù´ÙÅ×, 7:¹Ù·ç³ªÆ÷½º
			enum { eSklIdx_1 = 2, eSklIdx_2 = 7, eSklIdx_3 = 41, eSklIdx_4 = 21, eSklIdx_5 = 30, };
			if( 2 == MOB.byClass1 && 0 == MOB.byClass2 )
			{
				if( 0 < MOB.bySkill[eSklIdx_4] ) MOB.bySkill[eSklIdx_5] = 0; // ¿ì¸¶ »ç¸¶Å× ½ºÅ³ ÃÊ±âÈ­
				MOB.bySkill[eSklIdx_3] = 0; // »çºñÆ®¸®Æ÷½º ½ºÅ³ ÃÊ±âÈ­
				MOB.bySkill[eSklIdx_4] = 0; // »ç¸¶Å× ½ºÅ³ ÃÊ±âÈ­				
			}
			//if( 5 < MOB.bySkill[eSklIdx_1] ) MOB.bySkill[eSklIdx_1] = 5; // ¹Ù´ÙÅ× 5·¦Á¦
			//if( 5 < MOB.bySkill[eSklIdx_2] ) MOB.bySkill[eSklIdx_2] = 5; // ¹Ù·ç³ªÆ÷½º 5·¦Á¦
			
			if( 2 == MOB.byClass1 && 0 == MOB.byClass2 ) MOB.bySkill[60] = 0; //ºÎ¿ìÄ¯ÆÄ(¹æ³ª°¡)ºÎ¿ìÄ¯ÆÄ:3017 »õ·ÎÃß°¡µÈ ID , 3061			
			if( 2 == MOB.byClass1 && 1 == MOB.byClass2 ) MOB.bySkill[23] = 0; //¹Ù³ª¸£(°ø³ª°¡) Äï´Þ¸®´Ï¶óÀÌÂ¡:3015 »õ·ÎÃß°¡µÈ ID, 3024
		}
		
		if( (g_irgSetting[eCnst_HeartMax] < MOB.sHeart) && (2000 > MOB.sHeart) ) 
		{
			MOB.sHeart = g_irgSetting[eCnst_HeartMax];
			SendClientMessage( m_iHandle, g_pMessageStringTable[_HeartRestricted] );
		}

		m_iAggressiveCorrect = g_pAggrCorrect[MOB.byClass1][MOB.byClass2];

		if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) ) m_iMoveSpeed = eTNChr_DevaMvSpeed;
		if( eTNClan_GM == m_byClan )
		{
			m_iImmunity = eTNImm_Damage;
			m_iMoveSpeed = eTNChr_GMMvSpeed;
			m_iBlockedCell = 0;
			m_iCantDetect = 0;
		}
		else
		{
			if( eZoneType_Guild == g_iZoneType )
			{// ÇöÀç ¿ä»õ¸¦ ¼ÒÀ¯ÇÑ ±æµå¿¡ Æ÷ÇÔµÇ¾î ÀÖ´Â°¡¸¦ È®ÀÎÇØ¾ßÇÑ´Ù. ±×·¸´Ù¸é clanÀ» ¿ä»õ clan1~4·Î ¼³Á¤ÇÑ´Ù.
				for( int iOrder = 0; iOrder < eStronghold_MaxCount; ++iOrder )
				{
					if( 0 >= MOB.nGuildID ) continue;
					if( 0 >= g_krgStronghold[iOrder].iOwner ) continue;
					if( MOB.nGuildID == g_krgStronghold[iOrder].iOwner ) m_byClan = (byte)(eTNClan_Stronghold1 + iOrder);
					else if(MOB.nGuildID == g_krgStronghold[iOrder].iOwnerFriend ) m_byClan = (byte)(eTNClan_Stronghold1 + iOrder);

					// ¿¬ÇÕ±æµåµµ µ¿ÀÏ clanÀ» °¡Á®¾ß ÇÑ´Ù. ±×·¡¾ßÁö monster¿ÍÀÇ ¿¬°ü¼ºÀÌ °áÁ¤µÈ´Ù.
				}
			}	
			else
			{
				int iSiege = g_kSiege.get_Started();
				if( iSiege )
				{
					MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
					kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
					kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);

					kZoneSettingMsg.snSiege = iSiege;
					pUser[m_iHandle].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );

					
					// ÀÚ½Å guild°¡ °ø¼ºÀü¿¡ Âü°¡ÁßÀÎÁö °Ë»çÇÏ¿© clanÀ» º¯°æ½ÃÅ²´Ù.
					int iFlag = g_kSiege.SearchEntry( MOB.nGuildID );

					if( -1 == iFlag ) m_byClan = eTNClan_Siege4;
					else m_byClan = iFlag;
				}
			}
		} // if( eTNClan_GM == m_byClan )

		m_kTolerance = g_krgEffectTolerance[MOB.byClass1][MOB.byClass2];

		m_kMoveRecord.iSpeed = m_iMoveSpeed;
		m_kMoveRecord.kPos.x = TargetX;
		m_kMoveRecord.kPos.y = TargetY;
		m_kMoveRecord.uiElapsed = 0;

		m_iButtonStatus = 0;
		//m_iBlockedCell = eTNCell_Blocked;

		m_iMaxPrana = g_irgLevelUp[MOB.byLevel-1];
		if( m_iMaxPrana < MOB.nPrana ) MOB.nPrana = m_iMaxPrana;

		int iTotalChakra = CalChakra();

		//int iSumChakraModified = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
		//int iPlusChakra = 0;
		//if( 0 < MOB.byClass1 ) iPlusChakra = (MOB.byLevel/10)*3; // 10·¦´ç 3¾¿ Ãß°¡
		//
		//int iTotalChakra = 50 + (MOB.byLevel - 1)*5 + iPlusChakra;
		//if( 99 < MOB.byLevel )
		//{
		//	int iFactor = ((MOB.byLevel-100)/10);
		//	iTotalChakra = 577/*50 + 495 + 27 + 5*/ + iFactor*(60 + ((iFactor-1)*10)) + (MOB.byLevel-(99+(10*iFactor)))*(6+(iFactor*2));
		//}

		//m_kCPRemaining.Init( 20000, iTotalChakra - iSumChakraModified );

		int iSkillPointUsed = 0; 
		for( int i = 0; i < 65; ++i ) iSkillPointUsed += MOB.bySkill[i];
		for( int i = 80; i < MAX_SKILL; ++i ) iSkillPointUsed += MOB.bySkill[i];
		int iPlusSkillPoint = 0, iPlusSkillPointFor100Level = 0;
		if( 1 < MOB.byClass1 ) iPlusSkillPoint = ((MOB.byLevel-35)/10)*2; // 45·¦ºÎÅÍ 10·¦´ç 2¾¿ Ãß°¡
		if( 99 < MOB.byLevel ) iPlusSkillPointFor100Level = 0; // 100·¹º§ºÎÅÍÀÇ º¸³Ê½º

		int iTotalSkillPoint = MOB.byLevel + iPlusSkillPoint + iPlusSkillPointFor100Level;
		int iSPRemaining = iTotalSkillPoint - iSkillPointUsed;
		if( 0 > iSPRemaining ) iSPRemaining = 0;
		m_kSPRemaining.Init( 10000, iSPRemaining );
	
		//m_kMurderDropRate.Init( g_irgSetting[eCnst_MurderDropRate] );
		//m_kInnocentDropRate.Init( g_irgSetting[eCnst_InnocentDropRate] );
		//m_kFirstStrikerDropRate.Init( g_irgSetting[eCnst_FirstStrikerDropRate] );

		UpdateChakra();
		LoadSkills( MOB.bySkill );
		UpdateEquipmentPoints();

		//// 30ÃÊ µ¿¾È PK¿¡ Àû¿ëÀÌ ¾ÈµÇ°Ô ÇÑ´Ù.
		//TNEFFECT kEffect;
		//kEffect.iID = eTNAfn_ProtectFromPK;
		//kEffect.iDuration = g_irgSetting[eCnst_ProtectionFromPK]; //15000;
		//AddEffect( kEffect, m_iHandle, m_iHandle );

		CheckCaste();
		CalCasteSkillPoint();
		//CheckCasteSkillLevel();

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\t\t\t HP:%d, TP:%d, Gold:%d, Karma:%d, Braman:%d, Prana:%d/%d \r\n\t\t\t CPRemaining:%d(%d), SPRemaining:%d(%d), caste:%d, CasteSPRemaining:%d, class1:%d, class2:%d \r\n\n"
				, MOB.nHP, MOB.nTP, MOB.nRupiah, MOB.snKarma, MOB.nBramanPoint, MOB.nPrana, m_iMaxPrana
				, m_kCPRemaining.get_Cur(), iTotalChakra, m_kSPRemaining.get_Cur() , MOB.byLevel - iSkillPointUsed
				, m_iCaste, m_kCasteSPRemaining.get_Cur()
				, MOB.byClass1, MOB.byClass2 );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		{ // inventory³»¿¡ ÀÖ´Â kala Á¦°Å routine
			RemoveKalaCoreInInventory( m_iHandle );
		}
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		// fly-weight pattern, ±×·±µ¥ STRUCT_MOBÀÌ¶ó´Â struct¸¦ ¸ðµÎ µé°í ÀÖÀ¸¹Ç·Î ¸Þ¸ð¸® Àý¾àÀº µÇÁö ¾Ê´Â´Ù.
		//m_byClan = pMonsterData[MOB.nBramanPoint].byTrimuriti;
		MOB.nHP = pMonsterData[MOB.nTP].nHP;
		m_iMaxHP = pMonsterData[MOB.nTP].nHP;
		MOB.byClass1 = pMonsterData[MOB.nTP].byClass1;
		m_byBodyRadius = pMonsterData[MOB.nTP].byQuest[eMonPrty_Size] / 2;
		m_iMoveSpeed = pMonsterData[MOB.nTP].byQuest[eMonPrty_WalkSpeed];
		m_kSight.sPeace = pMonsterData[MOB.nTP].byQuest[eMonPrty_NormalSight];
		m_kSight.sCombat = pMonsterData[MOB.nTP].byQuest[eMonPrty_CombatSight];
		m_kMovement.Init( pMonsterData[MOB.nTP].byQuest[eMonPrty_Movement] );		
		m_kAggrCond.Init( pMonsterData[MOB.nTP].byQuest[eMonPrty_AggrCond] );
		m_kCombatFactors.iAttackRate = pMonsterData[MOB.nTP].sMuscle;
		m_kCombatFactors.iDodgeRate = pMonsterData[MOB.nTP].sNerves;
		m_kCombatFactors.iDefense = pMonsterData[MOB.nTP].sHeart;
		m_kCombatFactors.irgResist[eRst_Fire] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snIndex;
		m_kCombatFactors.irgResist[eRst_Cold] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snDurability;
		m_kCombatFactors.irgResist[eRst_Lightning] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].wSerial;
		m_kCombatFactors.irgResist[eRst_Poison] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snDummy;
		m_iImmunity = pMonsterData[MOB.nTP].nGuildID;
		m_iSkillCharged = eSkl_Melee;
		m_iCheckEnemyCount = pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved1]; // check enemy count
		m_iDebugFlag = eTNAudit_Boss & pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved4]; // º¸½ºµéÀº Ç×»ó log¸¦ ³²°Ü¾ß ÇÑ´Ù.
		m_uiActionDelay = pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved5] * 100; // ÀÌµ¿ ÈÄ action delay ½Ã°£ ¼³Á¤
		m_iReactToEnemyBehindWall = eTNReact_Pass & pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved6];
		m_kTolerance = g_krgEffectTolerance[0][0];
		m_iBlockedCell = pMonsterData[MOB.nTP].Equip[eMonPrty_BlockedCell].snIndex;
		m_iBlockedCell = m_iBlockedCell | eTNCell_DontAttackMonster; // monster¸¦ °ø°ÝÇÏÁö ¸øÇÏ´Â °÷Àº µé¾î°¡Áö ¾Ê´Â´Ù.
		//m_iBlockedCell = m_iBlockedCell | eTNCell_MonsterCantMoveInThisCell; // Â÷Åõ¶û°¡ °¢ ¹æ »çÀÌ¸¦ °Ç³Ê°¥ ¼ö ¾ø´Ù.
		m_iCantDetect = pMonsterData[MOB.nTP].Equip[eMonPrty_CantDetect].snIndex;
		//if( 0 == pMonsterData[MOB.nTP].MOB.byClass1 ) m_iBlockedCell = eTNCell_MonsterNotAllowed; // NPCµéÀº byClass1¿¡ ÀÇÇØ, Á÷¾÷ÀÌ ºÐ·ùµÈ´Ù.

		if( !(eTNImm_Stun & m_iImmunity) )  m_kWeaknessRate.Init( ((100-MOB.byLevel)/20+1) ); // 90·¦ ÀÌ»óÀÌ¸é, weakness°¡ °É¸®Áö ¾Ê´Â´Ù.

		//if( m_iDebugFlag ) sprintf( m_szLogFile, ".\\Log\\Monster_%d_%d.txt", MOB.snTribe, m_iHandle );
		//else sprintf( m_szLogFile, ".\\monster_log\\Monster_%d_%d.txt", MOB.snTribe, m_iHandle );
		sprintf( m_szLogFile, ".\\monster_log\\Monster_%d_%d.txt", MOB.snTribe, m_iHandle );

		if( (2296 == MOB.snTribe) ||
			(2297 == MOB.snTribe) ||
			(2306 == MOB.snTribe) ||
			(2307 == MOB.snTribe) ||
			(2309 == MOB.snTribe) ||
			(2310 == MOB.snTribe) ||
			(2312 == MOB.snTribe) ||
			(2313 == MOB.snTribe)
			)
			{
				m_iDebugFlag = 1;
				sprintf( m_szLogFile, ".\\Event\\Monster_%d_%d.txt", MOB.snTribe, m_iHandle );
			}

		// AI Condition
		if( 0 < pMonsterData[MOB.nTP].byQuest[eMonPrty_HelpCond] )
		{
			m_kCond.irgCond[eTNCond_Help] = Percent( m_iMaxHP, pMonsterData[MOB.nTP].byQuest[eMonPrty_HelpCond] );
			m_kCond.irgCondCount[eTNCond_Help] = pMonsterData[MOB.nTP].byQuest[eMonPrty_HelpCondCount];
		}
		if( 0 < pMonsterData[MOB.nTP].byQuest[eMonPrty_LinkCond] )
		{
			m_kCond.irgCond[eTNCond_Link] = Percent( m_iMaxHP, pMonsterData[MOB.nTP].byQuest[eMonPrty_LinkCond] );
			m_kCond.irgCondCount[eTNCond_Link] = pMonsterData[MOB.nTP].byQuest[eMonPrty_LinkCondCount];
		}
		if( 0 < pMonsterData[MOB.nTP].byQuest[eMonPrty_FleeCond] )
		{
			m_kCond.irgCond[eTNCond_Flee] = Percent( m_iMaxHP, pMonsterData[MOB.nTP].byQuest[eMonPrty_FleeCond] );
			m_kCond.irgCondCount[eTNCond_Flee] = pMonsterData[MOB.nTP].byQuest[eMonPrty_FleeCondCount];
		}

		// select target
		//if( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTargetComplexly] )
		{
			m_kSelectTarget.Init();
			m_kSelectTarget.AddCard( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTarget0], 40 );
			m_kSelectTarget.AddCard( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTarget1], 30 );
			m_kSelectTarget.AddCard( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTarget2], 20 );
			m_kSelectTarget.AddCard( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTarget3], 10 );
			m_kSelectTarget.Shuffle();		    
		}

		if( eTNCls_Summoned == MOB.byClass1 ) m_iAIOption = m_iAIOption | eTNAIO_HaveMaster | eTNAIO_LifeTime; // PC¿¡ ÀÇÇØ ¼ÒÈ¯µÇ´Â Á¾·ù
		if( eTNCls2_Retainer == MOB.byClass2 || eTNCls2_Pet == MOB.byClass2 ) m_iAIOption = m_iAIOption | eTNAIO_GetCommand; // ÁÖÀÎ ¸í·É¿¡ µû¸¥´Ù.
		if( eTNCls2_Familiar == MOB.byClass2 || eTNCls2_Tracker == MOB.byClass2 ) m_iAIOption = m_iAIOption | eTNAIO_CombatOnly; // ÀüÅõ °úÁ¤¸¸ ¼öÇà

		if( 1 == pMonsterData[MOB.nTP].byQuest[eMonPrty_TraceCond] ) m_iAIOption = m_iAIOption | eTNAIO_NoTrace; // ÃßÀûÇÏÁö ¾Ê´Â´Ù.

        Mode = MOB_PEACE;
        SegmentProgress	= 0;
        WaitSec	= SegmentWait[0];	 
        LastTime = CurrentTime;
        SegmentDirection = 0;

		m_kLastTime.uiActivate = CurrentTime + 10000; // 10ÃÊ µ¿¾ÈÀº »öÀûÀ» ÇÏÁö ¾Ê´Â´Ù.

		LoadSkills( MOB.bySkill );
	}	
	
	UpdatePoints();
}


int CMob::CalChakra()
{
	int iSumChakraModified = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
	int iPlusChakra = 0;
	if( 0 < MOB.byClass1 ) iPlusChakra = (MOB.byLevel/10)*3; // 10·¦´ç 3¾¿ Ãß°¡
	
	int iTotalChakra = 50 + (MOB.byLevel - 1)*5 + iPlusChakra;
	if( 99 < MOB.byLevel )
	{
		int iFactor = ((MOB.byLevel-100)/10);
		iTotalChakra = 572/*50 + 495 + 27 + 5*/ + iFactor*(60 + ((iFactor-1)*10)) + (MOB.byLevel-(99+(10*iFactor)))*(6+(iFactor*2));
	}

	m_kCPRemaining.Init( 20000, iTotalChakra - iSumChakraModified );

	return iTotalChakra;
}


bool CMob::IsCombat()
{ 
	if( MOB_COMBAT == Mode ) return true;
	return false; 
}

bool CMob::IsReachCallLevel(char* accoutn,char *ch, int i_level) //fors_debug ÍÆ¹ãÔ±·µ»ØµãÀ­À´µÄÍæ¼Òµ½´ï¼¶±ð¾ÙÊÖ´¦
{
    char temp[128]; char First[128];BASE_GetFirstKey(accoutn,First);
	sprintf(temp,"K:\\callotherlog\\%s\\%she_re%s.RCD",First,accoutn,ch);
     int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	 if (Handle!=-1)
	 {  close(Handle);
	    return FALSE;
	 }
	 close(Handle);
     
     Handle = open( temp, _O_CREAT | _O_RDWR | _O_TEXT , _S_IREAD | _S_IWRITE );
	 if  (Handle==-1)
	 {   if (errno==EEXIST) {Log("err ReWardgived not again1",ch,0);Log(temp,ch,0);return FALSE;}  // _O_EXCL ÀÏ¶§ ÀÌ¹Ì ÆÄÀÏÀÌ ÀÖ´Â°æ¿ì
         if (errno==EACCES) {Log("err ReWardgived not again2",ch,0);Log(temp,ch,0);return FALSE;}  // readonly¸¦ ¾²·Á°í ÇÑ°æ¿ì, ½¦¾î¸ðµå°¡ ºÒ°¡ÀÎ°æ¿ì, µð·ºÅä¸®°¡ invalid
         if (errno==EINVAL) {Log("err ReWardgived not again3",ch,0);Log(temp,ch,0);return FALSE;}  // invalid oflag or pmode argument
	     if (errno==EMFILE) {Log("err ReWardgived not again4",ch,0);Log(temp,ch,0);return FALSE;}  // ÆÄÀÏ ÇÚµéÀÌ ¾ø´Ù.
	     if (errno==ENOENT) {Log("err ReWardgived not again5",ch,0);Log(temp,ch,0);return FALSE;}  // File or Path not found
		 Log("err RCD UNKNOWN",ch,0);
		 Log(temp,ch,0);
         return FALSE;
	 }
//	 write(Handle,ac,ACCOUNTNAME_LENGTH);
	 close(Handle);
	 return TRUE;
}
bool CMob::IsGivedReachReWard(char *ch, int i_level)
{
    char temp[128]; char First[128];BASE_GetFirstKey(ch,First);
	sprintf(temp,"K:\\reach\\%s\\%s_%d.TCD",First,ch,i_level);
     int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	 if (Handle!=-1)
	 {  close(Handle);
	    return FALSE;
	 }
	 close(Handle);
     
     Handle = open( temp, _O_CREAT | _O_RDWR | _O_TEXT , _S_IREAD | _S_IWRITE );
	 if  (Handle==-1)
	 {   if (errno==EEXIST) {Log("err ReWardgived not again1",ch,0);Log(temp,ch,0);return FALSE;}  // _O_EXCL ÀÏ¶§ ÀÌ¹Ì ÆÄÀÏÀÌ ÀÖ´Â°æ¿ì
         if (errno==EACCES) {Log("err ReWardgived not again2",ch,0);Log(temp,ch,0);return FALSE;}  // readonly¸¦ ¾²·Á°í ÇÑ°æ¿ì, ½¦¾î¸ðµå°¡ ºÒ°¡ÀÎ°æ¿ì, µð·ºÅä¸®°¡ invalid
         if (errno==EINVAL) {Log("err ReWardgived not again3",ch,0);Log(temp,ch,0);return FALSE;}  // invalid oflag or pmode argument
	     if (errno==EMFILE) {Log("err ReWardgived not again4",ch,0);Log(temp,ch,0);return FALSE;}  // ÆÄÀÏ ÇÚµéÀÌ ¾ø´Ù.
	     if (errno==ENOENT) {Log("err ReWardgived not again5",ch,0);Log(temp,ch,0);return FALSE;}  // File or Path not found
		 Log("err reWard UNKNOWN",ch,0);
		 Log(temp,ch,0);
         return FALSE;
	 }
//	 write(Handle,ac,ACCOUNTNAME_LENGTH);
	 close(Handle);
	 return TRUE;
}

bool CMob::IsGivedLevelUpReWard(char *ch, int i_level)
{
    char temp[128]; char First[128];BASE_GetFirstKey(ch,First);
	sprintf(temp,"K:\\char\\%s\\%s_%d.TCD",First,ch,i_level);
     int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	 if (Handle!=-1)
	 {  close(Handle);
	    return FALSE;
	 }
	 close(Handle);
     
     Handle = open( temp, _O_CREAT | _O_RDWR | _O_TEXT , _S_IREAD | _S_IWRITE );
	 if  (Handle==-1)
	 {   if (errno==EEXIST) {Log("err ReWardgived not again1",ch,0);Log(temp,ch,0);return FALSE;}  // _O_EXCL ÀÏ¶§ ÀÌ¹Ì ÆÄÀÏÀÌ ÀÖ´Â°æ¿ì
         if (errno==EACCES) {Log("err ReWardgived not again2",ch,0);Log(temp,ch,0);return FALSE;}  // readonly¸¦ ¾²·Á°í ÇÑ°æ¿ì, ½¦¾î¸ðµå°¡ ºÒ°¡ÀÎ°æ¿ì, µð·ºÅä¸®°¡ invalid
         if (errno==EINVAL) {Log("err ReWardgived not again3",ch,0);Log(temp,ch,0);return FALSE;}  // invalid oflag or pmode argument
	     if (errno==EMFILE) {Log("err ReWardgived not again4",ch,0);Log(temp,ch,0);return FALSE;}  // ÆÄÀÏ ÇÚµéÀÌ ¾ø´Ù.
	     if (errno==ENOENT) {Log("err ReWardgived not again5",ch,0);Log(temp,ch,0);return FALSE;}  // File or Path not found
		 Log("err reWard UNKNOWN",ch,0);
		 Log(temp,ch,0);
         return FALSE;
	 }
//	 write(Handle,ac,ACCOUNTNAME_LENGTH);
	 close(Handle);
	 return TRUE;
}

bool CMob::IsDead()
{ 
	if( eTNFsm_Dead == m_eFSM ) return true;
	if( MOB_EMPTY == Mode ) return true;
	return false; 
}


bool CMob::IsAlive()
{
	if( 0 >= MOB.nHP ) m_eFSM = eTNFsm_Dead;

	if( eTNFsm_Dead != m_eFSM ) return true;
	return false;
}


void CMob::ProcessorSecTimer(void)
{

	mSecCounter++;
	
//	GetLocalTime( &g_kSystemTime );
//	mCurrentTime = timeGetTime();		// CurrentTimeÀº 0.25ÃÊ¸¶´Ù update
//	int	Rst2	=	(mSecCounter&0x01);	//SecCounter%2;
	int	Rst4	=	(mSecCounter&0x03);	//SecCounter%4;
	/*int	Rst8	=	(mSecCounter&0x07);	//SecCounter%8;
    int Rst16	=	(mSecCounter&0x0F);	//SecCounter%16;
	int Div16	=	(mSecCounter>>4);	//SecCounter/16; */
	int Rst32	=	(mSecCounter&0x1F);	//SecCounter%32;
/*	int Div32	=	(mSecCounter>>5);	//SecCounter/32;
	int Rst64	=	(mSecCounter&0x3F);	//SecCounter%64;
	int Div64	=	(mSecCounter>>6);	//SecCounter/64;
	int Rst128	=	(mSecCounter&0x7F);	//SecCounter%128;
	int Div128	=	(mSecCounter>>7);	//SecCounter/128;
	int Rst256	=	(mSecCounter&0xFF);	//SecCounter%256;
	int Div256	=	(mSecCounter>>8);	//SecCounter/256;
	int Rst512	=	(mSecCounter&0x01FF);//SecCounter/1024;
	
	*/
	m_iUserWhat = 0;

	if(Rst4 == 0)
	{	
	//	QUEST_OnEvent( m_iHandle, pMob[m_iHandle].MOB.snTribe, pMob[m_iHandle].MOB.snTribe, 0 );
	if ( g_iZoneID == 1 ) //fors_debug ÅÝÖ÷ÉñµãµØ·½ÐÂ
			if( 0 < MOB.nHP )
			{ 
				   
				     MOB.nBramanPoint +=2 ;
					 //pMob[m_iHandle].AcquirePrana( 1, true );//fors_debug ¼Ó¸öÒ»µã£¬ÓÐÏÔÊ¾Ð§¹û
				//QUEST_OnEvent( m_iHandle, pMob[m_iHandle].MOB.snTribe, pMob[m_iHandle].MOB.snTribe, 0 );
					 NotifyUpdateUIMsg();
	                
	         }
   //    mSecCounter = 0;
	          
     }
	if(Rst32 == 0)
	{	
	   if (g_iZoneID == 10 ) //fors_debug È¡ÏûÕæ×£¸£µÄµØ·½
			{ 
				   
           if ( ( pMob[m_iHandle].m_iAffections & eTNVSAfn_BlessOfGod ) && ( pMob[m_iHandle].m_isBlessGod == 2 ) ) //fors_debug test blessgod here
              pMob[m_iHandle].TurnOffAffection( eTNAfn_BlessOfGod );
	        
		   if (  pMob[m_iHandle].m_isBlessGod ==  1 )
			    pMob[m_iHandle].m_isBlessGod = 2;
	         }
       mSecCounter = 0;
	          
     }

}

//////////////////////////////////////////////////////////////////////////////
//                           
//                        StandingByProcessor
//
//////////////////////////////////////////////////////////////////////////////
//
//    1. °¡½Ã°Å¸®¿¡ °ø°ÝÇØ¾ßÇÒ ´ë»óÀÌ ÀÖ´ÂÁö °Ë»ç
//       ÀÖÀ¸¸é EnemyList¿¡ µî·Ï/°ø°Ý (NPCMODE_BATTLE)
//
//    2. ÇöÀç À§Ä¡ °è»ê
//       ½ÌÅ©Á¸ º¯È­ Ã¼Å©. ½ÌÅ©Á¸ÀÌ ¹Ù²î¾úÀ¸¸é,
//       »õ·Î¿î ½ÌÅ©Á¸ÀÇ OPP-NPC¸¦ STANDINGBY ½ÃÅ²´Ù.
//
//    3. ÇöÀç À§Ä¡°¡ ¼¼±×¸ÕÆ®ÀÎÁö °Ë»ç 
//       ¼¼±×¸ÕÆ®ÀÌ¸é, ÃÖÁ¾ µµÂøÁöÀÎÁö °Ë»ç
//       ÃÖÁ¾ µµÂøÁö¸é, IDLE, 
//       ¾Æ´Ï¸é NEXT SEGMENT »ý¼º. 
//
//    4. ÇöÀç ÁøÇà ¹æÇâÀÌ ¼¼±×¸ÕÆ®¸¦ ÇâÇØ +-10% ÀÌ»óÀÌ¸é ¹æÇâ º¸Á¤
//       ÁøÇà ¼Óµµ°¡ 0ÀÌ¸é, °¡¼Ó.
//
// 
///////////////////////////////////////////////////////////////////////////////
// TRUEÀÌ¸é Multicast¸¦ ÇÑ´Ù.
int CMob::StandingByProcessor()
{
	if( eTNVSAfn_DontMove & m_iAffections) return 0;
	if( 0 >= m_kMovement.get_Rate() ) return 0; // ÀÌµ¿¼ºÀÌ 0ÀÎ monster´Â Àý´ë ¿òÁ÷ÀÌÁö ¾Ê´Â´Ù.

    int ret=0;
    // 2. ¼¼±×¸ÕÆ®¿¡ µµÂøÇßÀ¸¸é ¼¼±×¸ÕÆ® Áõ°¡.
    if( (SegmentX==TargetX) && (SegmentY==TargetY) )
    {	
		if( 0 < WaitSec )
		{	
			WaitSec = WaitSec - SECSTANDINGBY;
			if( 0 < WaitSec ) 
			{	if( (eTNRout_MoveNRoam == RouteType) && (TargetX == SegmentListX[0]) && (TargetY == SegmentListY[0]) ) return 0;
				if( 0 == m_iMoveSpeed ) return 0;
				//	if Clan==7,8 return 0;
				ret = ret | 0x1000;
				return ret; // ÁÖÀ§¸¦ µ¹¾Æ´Ù´Ï±â
			}

			WaitSec = 0;
			if( eTNRout_MoveNRoam == RouteType && ((MAX_SEGMENT -1) == SegmentProgress ) )
			{
				if( !m_kMovement.Random() )  WaitSec = SECSTANDINGBY * 2; // 4ÃÊ(2ÃÊ*2)
			}
		}
		else // WaitSec°¡ 0 ÀÌ¶ó¸é, ...
		{	
			Think( eTNAI_Start, 0 );
			int sec = SegmentWait[SegmentProgress];
			if (sec>0) 
			{
				WaitSec = sec;
				return ret;
			}
		}

		int r = SetSegment();
		// r:0 ÀÌµ¿
		// r:1 »óÁÖ 
		// r:2 »èÁ¦ 
		if	(r==1) return ret;   
		if	(r==2)
		{	ret = ret | 0x0100;
			return ret;
		}
		if	(r==3) // ¼öÈ£À§Ä¡ °íÁ¤
		{;
		}
		// ¼¼±×¸ÕÆ® Action GridCast
	}

	GetNextPos(0);
	if	(NextX==TargetX &&NextY==TargetY)
	{	int r = SetSegment();
		return ret;
	}
	ret=ret | 0x01; // ÀÌµ¿
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////////////
//
//                           NPCBattleProcessor
//
//////////////////////////////////////////////////////////////////////////////////
//
//     1.  EnemyListÁß¿¡ °ø°Ý´ë»óÀ» ¼±Á¤ÇÑ´Ù.
//         ÀÌ¶§ ¼±Á¤ÇÑ Object°¡ À¯È¿ÇÏÁö ¾ÊÀ¸¸é Àç¼±Á¤ÇÏ°í, ³²Àº ¿ÀºêÁ§Æ®°¡ ¾øÀ¸¸é
//         MOB_PEACE ·Î º¯°æ½ÃÅ²´Ù.
//
//     2.  Enemy°¡ ÃßÀûÇÒ ÇÊ¿ä°¡ ÀÖÀ¸¸é ÃßÀûÇÑ´Ù 
//         (1.±Ø»ó¼ºÀÎ°æ¿ì, 2.³ªº¸´Ù ÃæºÐÈ÷ ¾àÇÑ °æ¿ì)
/////////////////////////////////////////////////////////////////////////////////
int CMob::BattleProcessor( int a_iTic )
{  
	int iDist = 0;

	if( 0 > CurrentTarget || MAX_MOB <= CurrentTarget ) CurrentTarget = 0;
	else
	{
		if( pMob[CurrentTarget].IsDead() ) CurrentTarget = 0;
	}

	if( 0 == CurrentTarget ) // ´õÀÌ»ó °ø°ÝÇÒ ´ë»óÀÌ ¾øÀ¸¸é Standingby ¸ðµå·Î Ã¼ÀÎÁö.
	{
		//if( eTNAIO_GetCommand & m_iAIOption ) return eTNRA_EndToCombat;
		if( eTNCls_Summoned == MOB.byClass1 ) return eTNRA_EndToCombat;

		if( 0 >= m_kMovement.get_Rate() )
		{
			//for (int i=0;i<MAX_ENEMY;i++)   EnemyList[i]=0;
			Mode = MOB_PEACE;

			NextX = SegmentX;
			NextY = SegmentY;
			return eTNRA_ReturnToHome;
		}

		return eTNRA_EndToCombat;  // ÀüÅõ Á¾·á(±ÍÈ¯ or Á×À½)
	}
	else
	{
		//if( eTNAIO_GetCommand & m_iAIOption )
		if( eTNCls_Summoned == MOB.byClass1 ) 
		{ // ¼ÒÈ¯µÈ monsterµéÀº ÀÓÀÇÀûÀ¸·Î targetÀ» º¯°æÇÏÁö ¾Ê´Â´Ù.
			iDist = CalDistance( m_iHandle, CurrentTarget );
		}
		else
		{
			iDist = SelectTargetFromEnemyList();
		}
	}

	//if( (5 != RouteType) && iDist > m_kSight.sCombat )
	if( iDist > m_kSight.sCombat ) // ÀüÅõ ½Ã¾ßº¸´Ù ´õ ¸Ö´Ù. µû¶ó¼­ ÀüÅõ Á¾·á¸¦ ÇØ¾ß ÇÑ´Ù.
	{	
		//if( eTNAIO_GetCommand & m_iAIOption ) return 0x0010;
		if( eTNCls_Summoned == MOB.byClass1 ) eTNRA_EndToCombat; // ¼ÒÈ¯µÈ monsterµéÀº ÀüÅõ Á¾·á

		if( 0 >= m_kMovement.get_Rate() )
		{
			//for (int i=0;i<MAX_ENEMY;i++)   EnemyList[i]=0;
			Mode = MOB_PEACE;

			NextX = SegmentX;
			NextY = SegmentY;
			return eTNRA_ReturnToHome; // teleport
		}

        return eTNRA_EndToCombat;  // ÀüÅõ Á¾·á, ±ÍÈ¯
	}

	int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index
	int iRange = pSkillData[iSkillIndex].iRange;


	if( 0 == m_iSkillCharged ) // default skillÀÌ ¼±ÅÃµÈ °æ¿ì, ...
	{
		//if( eTNChr_MeleeAttackRange >= iDist ) // ±Ù°Å¸® skill ¿ì¼±
		if( iRange >= iDist ) // ±Ù°Å¸® skill »ç°Å¸® ³»¿¡ Æ÷ÇÔµÇ´Â °æ¿ì
		{
			if( 0 >= MOB.Equip[eSkl_Melee].snIndex ) m_iSkillCharged = eSkl_Range; // ±Ù°Å¸® skillÀÌ ¾ø´Ù¸é,  ranged skill·Î º¯°æ
		}
		else // ±Ù°Å¸® skill »ç°Å¸®¸¦ ¹þ¾î³ª´Â °æ¿ì, ¿ø°Å¸® skill·Î °ø°ÝÀ» ÇÏ·Á°í ÇØ¾ßÇÑ´Ù.
		{
			if( 0 < MOB.Equip[eSkl_Range].snIndex ) m_iSkillCharged = eSkl_Range; // ¿ø°Å¸® skillÀÌ µî·ÏµÇ¾î ÀÖ´Ù¸é, ranged skill·Î °áÁ¤
		}

		iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index
	}	
	
	iRange = pSkillData[iSkillIndex].iRange;
	if( (eTNSklA_Unit < pSkillData[iSkillIndex].iAOE) && (eTNSklR_Self == iRange) ) iRange = pSkillData[iSkillIndex].iAOE;
	iRange += m_byBodyRadius;
	if( 0 >= iRange ) iRange = 1;
	
	if( iDist <= iRange )
	{// »ç°Å¸® ³»ÀÌ´Ï±î °ø°ÝÀ» ÇÑ´Ù.
		if( 0 >= pMonsterData[MOB.nTP].byQuest[eMonPrty_RunSpeed] ) return eTNRA_Attack;
		//if( eConst_CantTrace < m_iPlusRange ) return 0x1000;

		//if( TN_RANGE_DISTANT < iRange ) if( 80 < (rand()%100) ) return 0x0100; // 20% È®·ü·Î ¿ø°Å¸® °ø°ÝÀÏ °æ¿ì µÚ·Î ÈÄÅð

		if( 2 < m_iIgnoreObstacle ) return eTNRA_Attack;   // 3È¸ ÀÌ»ó Àå¾Ö¹°¿¡ °É¸®¸é, Àå¾Ö¹°À» ¹«½ÃÇÏ°í °ø°Ý

		// Target°ú GetHitPositionÀÌ ½ÇÆÐÇÏ¸é µµÁÖ?
		int tx=pMob[CurrentTarget].TargetX;
		int ty=pMob[CurrentTarget].TargetY;
		int bx=tx;
		int by=ty;
		BASE_GetHitPosition( TargetX, TargetY, &tx, &ty );//, (short**)pHeightGrid );//¼ÒÈ¯¼ö Àå¾Ö¹°½Ã Å¸°Ù º¯°æ?
		if	(tx!=bx || ty!=by)
		{// target°úÀÇ Áß°£¿¡ Àå¾Ö¹°ÀÌ ÀÖ¾î¼­, °ø°ÝÇÒ ¼ö ¾ø´Ù.
			//++m_iPlusRange;
			++m_iIgnoreObstacle;
			return eTNRA_Trace;
		}

		return eTNRA_Attack;   // °ø°Ý
	}
	else
	{// »ç°Å¸® ¹Ù±ùÀÌ¹Ç·Î ÃßÀûÀ» ÇØ¾ßÇÑ´Ù.
		//if( 1 == pMonsterData[MOB.nTP].byQuest[eMonPrty_TraceCond] ) // ÃßÀûÇÏÁö ¾Ê´Â´Ù.
		if( eTNAIO_NoTrace & m_iAIOption ) //  ÃßÀûÇÏÁö ¾Ê´Â ¼³Á¤À¸·Î µÇ¾î ÀÖ´Ù.
		{// ÀÚ½ÅÀÇ segment¿Í °Å¸®¸¦ °è»êÇØ¼­ ¸Ö¸® ÀÖÀ¸¸é ÃßÀûÀ» Æ÷±âÇÑ´Ù.
			HS2D_COORD kCur, kCenter;
			kCenter.x = SegmentX;
			kCenter.y = SegmentY;
			kCur.x = TargetX;
			kCur.y = TargetY;

			int iDist = CalDistance( kCur, kCenter, m_byBodyRadius, 0 );
			if( iDist > SegmentRange[0] )
			{
				Mode = MOB_PEACE;
				UpdateSpeed();
				return 0;
			}
		}

		//if( a_iEven ) return 0; // Ãß°ÝÀ» ÇØ¾ßÇÏ´Âµ¥ ÇöÀç´Â skip
		if( a_iTic ) return 0; // Ãß°ÝÀ» ÇØ¾ßÇÏ´Âµ¥ ÇöÀç´Â skip
		if( eTNVSAfn_DontMove & m_iAffections) return 0;		

		return eTNRA_Trace;   // Ãß°Ý
	}

	return 0;
}


/*
/////////////////////////////////////////////////////////////////////
//
//                  AddEnemyList
//
/////////////////////////////////////////////////////////////////////
//    °ø°Ý ´ë»óÀ» µî·ÏÇÑ´Ù.
//    Group ¸É¹öÁß ÇÏ³ª°¡ °ø°Ý´çÇßÀ»¶§,  °ø°ÝÇÑ ´ë»óÀº ±×·ì ÀüÃ¼°¡ EnemyList¿¡ µî·ÏÇÑ´Ù.
// 
void  CMob::AddEnemyList(short TargetId)
{
     if (TargetId<=0) return;

     for (int i=0;i<MAX_ENEMY;i++)
	 {   if (EnemyList[i]==TargetId) {return;}
	 }

     for (i=0;i<MAX_ENEMY;i++)
	 {   if (EnemyList[i]==0) {break;}
	 }
     if (i==MAX_ENEMY) return;
	 EnemyList[i]=TargetId; 
	 
	 return;
}

void  CMob::RemoveEnemyList(short TargetId)
{
     if (TargetId<=0) return;
     for (int i=0;i<MAX_ENEMY;i++)
	 {   if (EnemyList[i]==TargetId) {EnemyList[i]=0;return;}
	 }
	 return;
}
*/

/*
// PCÀÎ °æ¿ì¿¡¸¸ µ¿ÀÛÀ» ÇÑ´Ù.
void CMob::RefreshEnemyCount()
{
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return; // pc °æ¿ì °Ë»ç, ...
	m_iEnemyCount = 0;
	for( int i = 0; i < MAX_ENEMY; ++i )
	{

		if( MAX_USER <= EnemyList[i] && MAX_MOB > EnemyList[i] )
		{
			//if( eTNSts_Help & pMob[EnemyList[i]].m_eStatus ) continue;
			//if( eTNSts_Link & pMob[EnemyList[i]].m_eStatus ) continue;
			++m_iEnemyCount;
			if( 2 < m_iEnemyCount )	pMob[EnemyList[i]].m_iTraceCount += (m_iEnemyCount*15);  // ÀÌ°ÍÀ» °É¸é, help/link¿¡ ¹®Á¦°¡ ÀÖÀ» ¼ö ÀÖ´Ù.
			EnemyList[i] = 0;
		}

	}
}
*/


/////////////////////////////////////////////////////////////////////
//
//                   FromEnemyList
//
/////////////////////////////////////////////////////////////////////
//    °ø°Ý ´ë»óÀÚ Áß¿¡ ÇöÀç °ø°ÝÇÒ ´ë»óÀº ¼±ÅÃÇÑ´Ù.
//    ¼±ÅÃÇÑ ´ë»óÀÌ À¯È¿ÇÏÁö ¾ÊÀ¸¸é ´Ù½Ã Ã£°í,
//    °ø°Ý´ë»óÀÚ°¡ ¾øÀ¸¸é MOB_PEACE ·Î ÀüÈ¯ÇÑ´Ù.
//    EnemyList¿¡ ÀÖ´Â ÀûÀÌ ¿©·¯°³ÀÏ °æ¿ì, °¢°¢ ÀÚ½ÅÀÇ ¼Ó¼º(ÇØ±º,Midasµî)¿¡
//    µû¶ó °ø°Ý´ë»ó ¼±Á¤.  (ÇØ¾ß ÇÏ³ª ÀÏ´ÜÀº Ã³À½ °ø°Ý ¹ÞÀº »ó´ë·Î ¼¼ÆÃÇÑ´Ù.)
//
int  CMob::SelectTargetFromEnemyList()
{
	while( m_kLastTime.uiSelectTarget > CurrentTime ) // familiarµéÀº targetÀ» º¯°æÇÏÁö ¸øÇÑ´Ù.
	{// ±âÁ¸ÀÇ targetÀ» °í¼öÇÑ´Ù.
		// ±âÁ¸ targetÀÌ Á¤»óÀûÀÎÁö °Ë»ç
		if( (0 >= CurrentTarget) || (MAX_MOB <= CurrentTarget) ) break;
		if( MOB_EMPTY == pMob[CurrentTarget].Mode ) break;
		if( 0 >= pMob[CurrentTarget].MOB.nHP ) break;
		//if( m_iCantDetect & pMob[CurrentTarget].m_iAffections ) break; // Åõ¸íÀÎ Àû °¨Áö ¿©ºÎ¿¡ µû¶ó¼­

		int iDist = CalDistance( m_iHandle, CurrentTarget );
		//if( eTNCls_Summoned != MOB.byClass1 ) // warrior
		//{	
		//	if( 10 < iDist ) break; // ±âÁ¸ target°ú °Å¸®°¡ 10 ÃÊ°úÀÌ´Ù. ±×·³ ÀûÀ» ´Ù½Ã °í¸¥´Ù.
		//	// ¸¸¾à ÀûÀÌ ±Ã¼öÀÌ¶ó¸é °è¼Ó ½Å±Ô targetÀ» °áÁ¤ÇØ¾ß ÇÒ °ÍÀÌ´Ù.
		//}

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t[SelectTargetFromEnemyList] 0. ÇöÄ³¸¯ÅÍ ±×´ë·Î À¯Áö> CurrentTarget:%d, distance:%d \r\n", CurrentTarget, iDist );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		return iDist; // ½Ã°£ÀÌ ¾ÈµÇ¾úÀ¸¸é, ±×³É ±âÁ¸ÀÇ target°úÀÇ °Å¸®¸¦ return ÇÑ´Ù.
	}

	//------------------------------------------
	// ½Å±Ô targetÀ» °áÁ¤ÇÑ´Ù.
	//------------------------------------------
	CurrentTarget = 0;

	int iSize = MAX_ENEMY + MAX_ENEMY + MAX_ENEMY + MAX_ENEMY; // pc + familiar + retainer + pet
	int irgDistance[MAX_ENEMY + MAX_ENEMY + MAX_ENEMY + MAX_ENEMY] = { 0,0,0, };
	int irgCorrect[MAX_ENEMY + MAX_ENEMY + MAX_ENEMY + MAX_ENEMY] = { 0,0,0, };
	int irgEnemy[MAX_ENEMY + MAX_ENEMY + MAX_ENEMY + MAX_ENEMY] = { 0,0,0, };
	int i = 0;
	//memset( irgDistance, 0, sizeof(irgDistance) );
	//memset( irgCorrect, 0, sizeof(irgCorrect) );
	//memset( irgEnemy, 0, sizeof(irgEnemy) );

	//--------------------------------------------------------------
	// 1. ¸Æµ© party¸¦ Ã£´Â´Ù.
	//--------------------------------------------------------------
	int iMaxDamageCorrect = 10;
	int iMaxDamageParty = 0;
	int iMinDistance = 255;

	SortAttackers();
	int iRank = 0;
	while( 0 == CurrentTarget )
	{
		if( TN_ATTACKER_COUNT <= iRank )
		{ // targetÀ» ÇÏ³ªµµ ¸øÃ£Àº °ÍÀÌ´Ù.
			ClearAttacker( 3 ); // 3µî±îÁö¸¸ ³²°ÜµÎ°í ¸ðµÎ clearÇÑ´Ù. ±×·¡¼­ ÃÑ 13°³¸¦ Àçµî·ÏÇÒ ¼ö ÀÖ´Ù.		
			return 255;
		}

		iMaxDamageParty = get_Attacker( iRank );
		++iRank;

		if( 0 >= iMaxDamageParty && MAX_USER <= iMaxDamageParty ) continue;

		memcpy( irgEnemy, pMob[iMaxDamageParty].m_irgParty, sizeof(pMob[iMaxDamageParty].m_irgParty) ); // enmey ¹è¿­ Å©±â´Â 6, party ¹è¿­ Å©±â´Â 5ÀÌ´Ù.
		irgEnemy[MAX_ENEMY-1] = iMaxDamageParty;

		for( int iParty = 0; iParty < MAX_ENEMY; ++iParty ) // familiar Ãß°¡
		{
			int iMob = irgEnemy[iParty];
			if( 0 >= iMob || MAX_USER <= iMob ) continue;
			// PCÀÏ °æ¿ì¿¡¸¸ ¾Æ·¡ÀÇ ¼ÒÈ¯¼öµéÀ» Ãß°¡ÇØÁØ´Ù.
			irgEnemy[MAX_ENEMY+iParty] = pMob[iMob].m_irgSummoned[eTNCls2_Familiar];
			irgEnemy[MAX_ENEMY+MAX_ENEMY+iParty] = pMob[iMob].m_irgSummoned[eTNCls2_Retainer];
			irgEnemy[MAX_ENEMY+MAX_ENEMY+MAX_ENEMY+iParty] = pMob[iMob].m_irgSummoned[eTNCls2_Pet];
		}

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t[SelectTargetFromirgEnemy] 10. irgEnemy(%d,%d,%d,%d,%d,%d,%d,%d,%d) \r\n"
				, irgEnemy[0], irgEnemy[1], irgEnemy[2], irgEnemy[3], irgEnemy[4], irgEnemy[5], irgEnemy[6], irgEnemy[7], irgEnemy[8]
				);
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		int iTauntCorrect = 5;
		//int iPartyMemberCount = 0;
		//m_iEnemyCount = 0; // npcÀÇ °æ¿ì
		for(i = 0;i < iSize; ++i )
		{
			short tid = irgEnemy[i];
			if( tid <= 0 || tid >= MAX_MOB ) continue;
			if( MOB_EMPTY == pMob[tid].Mode ) { irgEnemy[i] = 0; continue; }
			if( pMob[tid].IsDead() ) { irgEnemy[i] = 0; continue; }
			if( 0 >= pMob[tid].MOB.nHP ) { irgEnemy[i] = 0; continue; }
			if( 0 >= pMob[tid].TargetY || MAX_GRIDY <= pMob[tid].TargetY ) { irgEnemy[i] = 0; continue; }
			if( 0 >= pMob[tid].TargetX || MAX_GRIDX <= pMob[tid].TargetX ) { irgEnemy[i] = 0; continue; }

			if( m_iBlockedCell & g_krgCell[pMob[tid].TargetY][pMob[tid].TargetX].usProperty ) irgEnemy[i] = 0;
			else if( m_iCantDetect & pMob[tid].m_iAffections ) irgEnemy[i] = 0; // Åõ¸í »óÅÂ
			else if( eTNVSAfn_ProtectFromMonster & pMob[tid].m_iAffections ) irgEnemy[i] = 0;
			else
			{
				irgDistance[i] = CalDistance( m_iHandle, tid );
				if( irgDistance[i] > m_kSight.sCombat )
				{
					if( irgEnemy[i] == m_iCantTraceTarget ) m_iCantTraceTarget = 0;
					irgEnemy[i] = 0;				
					continue;
				}
				
				//++m_iEnemyCount; // npc°¡ µî·ÏÇÏ°í ÀÖ´Â ÀûÀÇ ¼ö
				/*
				if( (tid == iMaxDamageParty) || (pMob[tid].Leader == iMaxDamageParty) ) // ¸Æµ© partyÀÏ °æ¿ì¿¡ ´õ¿í correct¸¦ ºÎ¿©ÇØÁÜ, ÇÊ¿äÇßÀ½
				{
					irgDistance[i] -= iMaxDamageCorrect;
					irgCorrect[i] += iMaxDamageCorrect;
					++iPartyMemberCount;
				}
				*/

				if( eTNInAfn_DeTaunt & pMob[tid].m_iInnerAffections )
				{
					irgDistance[i] += iTauntCorrect;
					irgCorrect[i] -= iTauntCorrect;
				}

				if( eTNInAfn_Taunt & pMob[tid].m_iInnerAffections )
				{
					irgDistance[i] -= iTauntCorrect;
					irgCorrect[i] += iTauntCorrect;
				}

				irgDistance[i] -= pMob[tid].m_iAggressiveCorrect;
				irgCorrect[i] += pMob[tid].m_iAggressiveCorrect;
			}
		}


		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t[SelectTargetFromirgEnemy] 20. irgEnemy> 0(%d;%d;%d), 1(%d;%d;%d) 2(%d;%d;%d), 3(%d;%d;%d), 4(%d;%d;%d), 5(%d;%d;%d), 6(%d;%d;%d), 7(%d;%d;%d), 8(%d;%d;%d) \r\n"
				, irgEnemy[0], irgDistance[0], irgCorrect[0]
				, irgEnemy[1], irgDistance[1], irgCorrect[1]
				, irgEnemy[2], irgDistance[2], irgCorrect[2]
				, irgEnemy[3], irgDistance[3], irgCorrect[3]
				, irgEnemy[4], irgDistance[4], irgCorrect[4]
				, irgEnemy[5], irgDistance[5], irgCorrect[5]
				, irgEnemy[6], irgDistance[6], irgCorrect[6]
				, irgEnemy[7], irgDistance[7], irgCorrect[7]
				, irgEnemy[8], irgDistance[8], irgCorrect[8]
				);
			WriteLog( chBuf, m_szLogFile );
		}
		#endif


		int iSelectTargetCorrect = 5;
		int iTargetSelected = 0;
		int iTargetIndex = 0;
		int iStandard = 0;

		// HP°¡ °¡Àå ³·Àº target, ¹æ¾î·ÂÀÌ °¡Àå ³·Àº target, °¡Àå Àû´ë°ü°è°¡ ³ôÀº target
		//, levelÀÌ °¡Àå ³·Àº target, °ø°Ý·ÂÀÌ °¡Àå ³ôÀº target
		//if( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTarget0] )
		if( pMonsterData[MOB.nTP].byQuest[eMonPrty_SelectTargetComplexly] )	
		{
			int iSelectTargetType = m_kSelectTarget.Random();
			switch( iSelectTargetType )
			{
			case eTNSelectTarget_Deva :
				{
					int iDistanceCorrect = 10;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						if( (TRIBE_DEVA==pMob[iTarget].MOB.snTribe) || (TRIBE_GARUDA==pMob[iTarget].MOB.snTribe) )
						{
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iDistanceCorrect;
						irgCorrect[iTargetIndex] += iDistanceCorrect;
					}
				}
				break;
			case eTNSelectTarget_Asura :
				{
					int iDistanceCorrect = 10;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						if( (TRIBE_ASURA==pMob[iTarget].MOB.snTribe) || (TRIBE_RAKSHASA==pMob[iTarget].MOB.snTribe) )
						{
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iDistanceCorrect;
						irgCorrect[iTargetIndex] += iDistanceCorrect;
					}
				}
				break;
			case eTNSelectTarget_Yaksha :
				{
					int iDistanceCorrect = 10;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						if( (TRIBE_YAKSA==pMob[iTarget].MOB.snTribe) || (TRIBE_GANDHARVA==pMob[iTarget].MOB.snTribe) )
						{
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iDistanceCorrect;
						irgCorrect[iTargetIndex] += iDistanceCorrect;
					}
				}
				break;
			case eTNSelectTarget_Naga :
				{
					int iDistanceCorrect = 10;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						if( (TRIBE_NAGA==pMob[iTarget].MOB.snTribe) || (TRIBE_KINNARA==pMob[iTarget].MOB.snTribe) )
						{
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iDistanceCorrect;
						irgCorrect[iTargetIndex] += iDistanceCorrect;
					}
				}
				break;
			case eTNSelectTarget_HighDamage :
				{
					iStandard = 0;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						int iDamage = pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0] + pMob[iTarget].m_krgDamage[eHnd_Right].irgPierce[0];
						if( iStandard < iDamage )
						{
							iStandard = iDamage;
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iSelectTargetCorrect;
						irgCorrect[iTargetIndex] += iSelectTargetCorrect;
					}
				}
				break;
			case eTNSelectTarget_LowHP :
				{
					iStandard = 1000000;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						int iHP = pMob[iTarget].MOB.nHP;
						if( iStandard > iHP )
						{
							iStandard = iHP;
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iSelectTargetCorrect;
						irgCorrect[iTargetIndex] += iSelectTargetCorrect;
					}
				}
				break;
			case eTNSelectTarget_LowDefense :
				{
					iStandard = 1000000;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						int iDefense = pMob[iTarget].m_kCombatFactors.iDefense;
						if( iStandard > iDefense )
						{
							iStandard = iDefense;
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iSelectTargetCorrect;
						irgCorrect[iTargetIndex] += iSelectTargetCorrect;
					}
				}
				break;
			case eTNSelectTarget_LowLevel :
				{
					iStandard = 1000000;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						int iLevel = pMob[iTarget].MOB.byLevel;
						if( iStandard > iLevel )
						{
							iStandard = iLevel;
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iSelectTargetCorrect;
						irgCorrect[iTargetIndex] += iSelectTargetCorrect;
					}
				}
				break;
			case eTNSelectTarget_Hostile :
				{
					iStandard = 0;
					for( int e = 0; e < iSize; ++e )
					{
						int iTarget = irgEnemy[e];
						if( 0 >= iTarget ) continue;
						int iClan = pMob[iTarget].m_byClan; //MOB.byTrimuriti;
						if( iStandard < g_iHostileTable[m_byClan][iClan] )
						{
							iStandard = g_iHostileTable[m_byClan][iClan];
							iTargetSelected = iTarget;
							iTargetIndex = e;
						}

						irgDistance[iTargetIndex] -= iSelectTargetCorrect;
						irgCorrect[iTargetIndex] += iSelectTargetCorrect;
					}
				}
				break;
			}

			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\t[SelectTargetFromirgEnemy] 25. irgEnemy> 0(%d;%d;%d), 1(%d;%d;%d), 2(%d;%d;%d), 3(%d;%d;%d), 4(%d;%d;%d), 5(%d;%d;%d), 6(%d;%d;%d), 7(%d;%d;%d), 8(%d;%d;%d) \r\n"
					, irgEnemy[0], irgDistance[0], irgCorrect[0]
					, irgEnemy[1], irgDistance[1], irgCorrect[1]
					, irgEnemy[2], irgDistance[2], irgCorrect[2]
					, irgEnemy[3], irgDistance[3], irgCorrect[3]
					, irgEnemy[4], irgDistance[4], irgCorrect[4]
					, irgEnemy[5], irgDistance[5], irgCorrect[5]
					, irgEnemy[6], irgDistance[6], irgCorrect[6]
					, irgEnemy[7], irgDistance[7], irgCorrect[7]
					, irgEnemy[8], irgDistance[8], irgCorrect[8]
					);
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
		}


		//--------------------------------------------------------------
		// 2. ¼±Á¤µÈ ÀûÁß¿¡¼­ °¡Àå °¡±î¿î mobÀ» ¼±ÅÃÇÑ´Ù.
		//--------------------------------------------------------------
		
		int iMinIndex = 0;
		int iCorrectIndex = 0;
		for( i = 0; i < iSize; ++i )
		{	short tid = irgEnemy[i];
			if( 0 >= tid || MAX_MOB <= tid ) continue;
			if( iMinDistance >= irgDistance[i] ) { iMinIndex = tid; iMinDistance = irgDistance[i]; iCorrectIndex = i; }
		}

		if( 255 == iMinDistance ) CurrentTarget = 0;
		else  // ÀüÅõ ½Ã¾ß ³»¿¡ ÀÖ´Â °Íµé¸¸ÀÌ´Ù. À§ÂÊ¿¡¼­ 1Â÷ÀûÀ¸·Î ÀüÅõ ½Ã¾ß °Å¸®°í filteringÇß´Ù.
		{
			CurrentTarget = iMinIndex;
			iMinDistance += irgCorrect[iCorrectIndex];
		}
	} // end of while( 0 == CurrentTarget )

	m_kLastTime.uiSelectTarget = CurrentTime + pMonsterData[MOB.nTP].snKarma;

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[SelectTargetFromirgEnemy] 30. CurrentTarget:%d(dist:%d), next time to select a new target:%d \r\n"
			, CurrentTarget, iMinDistance, m_kLastTime.uiSelectTarget );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
	
	return iMinDistance;
}





/*
/////////////////////////////////////////////////////////////////////////////////////////
//
//                  NotifyOppObjectSyncZone
//
/////////////////////////////////////////////////////////////////////////////////////////
//    ³ªÀÇ ½ÌÅ©Á¸3x3¿¡ ÀÖ´Â ¸ðµç NPCÁß¿¡ ³ª¿¡°Ô ¼±°øÇÒ¸¸ÇÑ NPC°¡ IDLE»óÅÂ¸é STANDINGBY ¸ðµå·Î ±ú¿î´Ù.
//    ÀÌºÎºÐÀÌ ¾øÀ¸¸é NPC°¡ ´Ù¸¥ NPC³ª PC¿¡°Ô Aggresive(¼±°ø) ¼Ó¼ºÀ» ÀÛµ¿ÇÏÁö ¾Ê´Â´Ù.
void  CMob::NotifyOppObjectSyncZone()
{
}
*/


/////////////////////////////////////////////////////////////////////////////////////////
//
//                  SetSegment
//
/////////////////////////////////////////////////////////////////////////////////////////
//   Àå°Å¸® ÀÌµ¿ÇÏ´Â NPC(»óÀÎµî)ÀÇ °æ¿ì Á÷ÁøÇÒ¼ö ¾ø´Â ÁöÇüÀÎ °æ¿ì
//   _/ ½ÄÀ¸·Î ÀÌµ¿ÇÒ¶§, ²©ÀÌ´Â °¡Àå °¡±î¿î ÁöÁ¡À» Ã£¾Æ Segment·Î ¼¼ÆÃÇÑ´Ù.
//   Segment¿¡ µµÂøÇÑ NPC´Â, ´Ù½Ã ÃÖÁ¾¸ñÀûÁö¿Í ÇöÀç À§Ä¡¸¦ ±Ù°Å·Î ´ÙÀ½ Segment¸¦ ¼¼ÆÃÇÏ¿© ÀÌµ¿À»
//   °è¼ÓÇÑ´Ù.
//   ¿¡³ÊÁ§ÅÍ Áö¿ª°ú ºñ¿¡³ÊÁ§ÅÍ Áö¿ªÀ¸·Î ±æÃ£±â·ÎÁ÷À» ³Ö¾î¾ß ÇÏ³ª, ÀÏ´Ü Á÷Áø Ã³¸®.
//    DestAction 0:»óÁÖ  1:¼Ò¸ê  2:¼øÂû 3:¿Õº¹  4:È¸Àü
//    SegmentDirection 0:¼øÇ× 1:È¸Ç× 
int   CMob::SetSegment()
{
								 // Start  -   0   -   1   -   2    -    3    -   Dest
                                 //    0       1       2       3         4         5
		                         //       0->    1->      2->      3->      4->
	                             //       <-0    <-1      <-2      <-3      <-4     
	if( (eTNRout_MoveNRoam > RouteType) || (eTNRout_FixPosition < RouteType) ) 
	{	
		Log("Wrong SetSegment",MOB.szName,0);
		return 0;
	}
	int Result = 0;
    while(1)
	{
	   if (!SegmentDirection) SegmentProgress++;
	   else                   SegmentProgress--;
       

		if(SegmentProgress <=-1)
		{	
			if(eTNRout_MoveNRoam == RouteType)
			{	
				SegmentProgress = 0;
				SegmentDirection = 0;
				Result = 2;
				Log("SetSegment SegmentProgress -1 but route type 0",MOB.szName,0);
				break;                                // ÀÌµ¿ÈÄ »óÁÖ¶ó Progress°¡ -1ÀÌ µÉ¼ö ¾ø´Ù.
			}	
			else if(eTNRout_MoveNPhaseOut == RouteType)
			{	
				SegmentProgress=0;
				SegmentDirection=0; // ÀÌµ¿ÈÄ ¼Ò¸êÀÌ¶ó Progress°¡ -1ÀÌ µÉ¼ö ¾ø´Ù.
			}	
			else if(eTNRout_Patrol == RouteType ) 
			{	
				SegmentProgress=0;
				SegmentDirection=0; // ¼øÂûÀÌ¹Ç·Î ÀçÃâ¹ß
				continue;
			}	
			else if(eTNRout_GoNReturnNPhaseOut == RouteType ) 
			{	
				Result = 2;// ¿Õº¹:¿Õº¹¿Ï·áÀÌ¹Ç·Î¼Ò¸ê.
				break;
			}	
			else if(eTNRout_Rotation == RouteType ) // È¸ÀüÀÌ ¿ª¹æÇâÀÌ ³ª¿Ã¼ö ¾ø´Ù.
			{	
				Log("SetSegment SegmentProgress -1 but route type 4",MOB.szName,0);
				break;
			}
			else
			{
				SegmentProgress = 0;
				SegmentDirection = 0;
				break;
			}
		}	
		else if( MAX_SEGMENT <= SegmentProgress )
		{	
			if (eTNRout_MoveNRoam == RouteType) // Çö À§Ä¡¿¡¼­ »óÁÖ 
			{   
				SegmentProgress = LAST_SEGMENT;
				Mode = MOB_PEACE;  
				//Direction = 0;
				GetCurrentScore(MAX_USER);
				Result = 1;
				break;
			}   
			else if(eTNRout_MoveNPhaseOut == RouteType) 
			{	
				Result = 2;// ¼Ò¸ê.
				break;
			}   
			else if(eTNRout_Patrol == RouteType || eTNRout_GoNReturnNPhaseOut == RouteType ) // ¿Õº¹ ¹× ¼øÂû
			{   
				SegmentProgress = LAST_SEGMENT; 
				SegmentDirection=1; 
				continue;
			}   
			else if(eTNRout_Rotation == RouteType)              // È¸Àü. °ú¿¬ Àß µÉÁö´Â¸ð¸£°Ú´Ù.
			{	
				SegmentProgress = -1;
				continue;
			}
			else
			{
				SegmentProgress = LAST_SEGMENT;
				SegmentDirection = 1;
				//Result = 0;
				break;
			}
		}  
		else
		{	
			if (SegmentListX[SegmentProgress]==0) continue; 
			Result = 0;
			break;
       }   
   };

	WaitSec  = 0;

	SegmentX = SegmentListX[SegmentProgress];
	SegmentY = SegmentListY[SegmentProgress];
	if( (eTNRout_MoveNRoam == RouteType) && (LAST_SEGMENT == SegmentProgress) )
	{
		if( 0 >= m_iInfluenceGridSize )
		{			
			#ifdef __TN_TOP_LOG__
			if( 0 == m_iDebugFlag )
			{
				m_iDebugFlag = 1;
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[SetSegment]idx:%3d, mob:%d, tribe:%d, 5th Area (%d,%d) \r\n", GenerateIndex, m_iHandle, MOB.snTribe, mNPCGen.pList[GenerateIndex].SegmentListX[LAST_SEGMENT], mNPCGen.pList[GenerateIndex].SegmentListY[LAST_SEGMENT] );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );		
			}
			#endif // __TN_TOP_LOG__
			return 0;
		}
		int iArea = rand() % m_iInfluenceGridSize;
		SegmentX = m_krgInfluenceGrid[iArea].x + rand()%TN_GRID_SIZE;
		SegmentY = m_krgInfluenceGrid[iArea].y + rand()%TN_GRID_SIZE;
	}

   return Result; // Action Multicast
}


// npc°¡ ÀÔ·ÂµÈ route¸¦ µû¶ó Á¤»óÀûÀ¸·Î ÀÌµ¿ÇÏ°Ô ÇÏ·Á¸é ¾î¶°ÇÑ ¼¼ºÎ ¼³Á¤À» ÇØÁà¾ß ÇÏ´Â°¡?
// GenereateMob() ÇÔ¼ö¸¦ »ìÆìº¸°í Á¤È®½Ã ¼³Á¤À» º¯°æÇØ¾ß ÇÒ °ÍÀÌ´Ù.
int CMob::set_Segment( int a_iRouteID )
{
	if( 0 >= a_iRouteID || eSiz_Route <= a_iRouteID ) return eTNRes_Failed;

	RouteType = g_krgRoute[a_iRouteID].iMethod;
	memcpy( SegmentListX, g_krgRoute[a_iRouteID].irgSegmentListX, sizeof(SegmentListX) );
	memcpy( SegmentListY, g_krgRoute[a_iRouteID].irgSegmentListY, sizeof(SegmentListY) );
	memcpy( SegmentWait, g_krgRoute[a_iRouteID].irgSegmentListWait, sizeof(SegmentWait) );
	memcpy( SegmentRange, g_krgRoute[a_iRouteID].irgSegmentListRange, sizeof(SegmentRange) );

	return eTNRes_Succeeded;
}


//  ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ Int Con È¿°ú MP+ HP+ Ã³¸® .
void CMob::GetCurrentScore(int idx)
{
	/*
	if (idx<MAX_USER)  pMob[idx].MOB.Clan = 0;
	if (idx<MAX_USER && MOB.BaseScore.Level<1000)
	{	MOB.Resist[0] = BASE_GetMobAbility(&MOB,EF_RESIST1);
		MOB.Resist[1] = BASE_GetMobAbility(&MOB,EF_RESIST2);
		MOB.Resist[2] = BASE_GetMobAbility(&MOB,EF_RESIST3);
		MOB.Resist[3] = BASE_GetMobAbility(&MOB,EF_RESIST4);
		MOB.Equip[0].stEffect[0].cEffect=0;
		MOB.Equip[0].stEffect[0].cValue=0;
		MOB.Rsv =0;
	}	else
	if	(idx>=MAX_USER)
	{	int geneidx = GenerateIndex;
		if	(geneidx>0&&geneidx<MAX_NPCGENERATOR)
		{	MOB.Resist[0] = mNPCGen.pList[geneidx].Leader.Resist[0];
			MOB.Resist[1] = mNPCGen.pList[geneidx].Leader.Resist[1];
			MOB.Resist[2] = mNPCGen.pList[geneidx].Leader.Resist[2];
			MOB.Resist[3] = mNPCGen.pList[geneidx].Leader.Resist[3];


		}
	}
	Parry = BASE_GetMobAbility(&MOB, EF_PARRY);

	if	(idx<MAX_USER)
	{
		pUser[idx].Range=BASE_GetMobAbility(&MOB, EF_RANGE);
	}


	BASE_GetCurrentScore(MOB,Affect);
    int Critical  = BASE_GetMobAbility(&MOB,EF_CRITICAL);
	if (Critical>255) Critical = 255;
	MOB.Critical = Critical;
	int ItemInt = MOB.CurrentScore.Int - MOB.BaseScore.Int;
	int ItemCon = MOB.CurrentScore.Con - MOB.BaseScore.Con;
	int MPDelta = ItemInt * 2;
	int HPDelta = ItemCon * 2;
	MOB.CurrentScore.MaxHp = MOB.CurrentScore.MaxHp + HPDelta;
    MOB.CurrentScore.MaxMp = MOB.CurrentScore.MaxMp + MPDelta;
	if (MOB.CurrentScore.Hp>MOB.CurrentScore.MaxHp) MOB.CurrentScore.Hp=MOB.CurrentScore.MaxHp;
	if (MOB.CurrentScore.Mp>MOB.CurrentScore.MaxMp) MOB.CurrentScore.Mp=MOB.CurrentScore.MaxMp;
	int w1=BASE_GetItemAbility(&MOB.Equip[6],EF_DAMAGE);;
	int w2=BASE_GetItemAbility(&MOB.Equip[7],EF_DAMAGE);
	if (w1>w2)	WeaponDamage=w1+(w2/3);
	else		WeaponDamage=w2+(w1/3);
	
	*/
}

void CMob::GetTargetPosDistance(int tz)
{
	/*
	 if  ((MOB.BaseScore.AttackRun&0xF)==0)
	 {   NextX = TargetX;
	     NextY = TargetY;
		 return;
	 }
	 int speed = BASE_GetSpeed(&MOB.CurrentScore);
	 int distance = speed * SECBATTLE * (TICKSIZE*4/1000)/4;
	 if (distance>=MAX_ROUTE) distance = MAX_ROUTE-1;
     // ÀÌµ¿ÁßÀÎ MOBÀº 4(STANDINGBY)ÃÊ¿¡ ÇÑ¹ø¾¿ Move?
     
	 LastX = TargetX;
	 LastY = TargetY;
/////////////////////////////////////////////////////////////////////////////////////////
	 NextX = LastX;
	 NextY = LastY;
	 if (pMob[tz].TargetX>LastX) NextX = NextX - (1 + rand()%2); else
     if (pMob[tz].TargetX<LastX) NextX = NextX + (1 + rand()%2); 
	 if (pMob[tz].TargetY>LastY) NextY = NextY - (1 + rand()%2); else
	 if (pMob[tz].TargetY<LastY) NextY = NextY + (1 + rand()%2); 

//////////////////////////////////////////////////////////////////////////////////////////

	 GetEmptyMobGrid(0,&NextX,&NextY);
	 for (int dis=distance;dis>=0;dis--) //
	 {
         BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis,(short**)pHeightGrid);
         if (pMobGrid[NextY][NextX]==0) break;
		 if (dis!=distance)  // 2¹øÂ°ºÎÅÍ´Â ÁÖÀ§ÀÇ ´Ù¸¥ Å¸ÀÏµµ °Ë»çÇÑ´Ù.
		 { 	GetEmptyMobGrid(0,&NextX,&NextY);
            BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis,(short**)pHeightGrid);
            if (pMobGrid[NextY][NextX]==0) break;
		 }  
	 }
	
     if (dis==-1 || Route[0]==0)
     {  
        NextX=TargetX;
		NextY=TargetY;
		Route[0]=0;
     }
	 return;
	 */
}


void CMob::GetRandomPos(void)
{
	int speed = m_iMoveSpeed;
	if	(m_iMoveSpeed==0)
	{	NextX = TargetX;
	    NextY = TargetY;
		return;
	}
	int distance = speed * SECSTANDINGBY/4;
	//int distance = speed * SECSTANDINGBY * (TICKSIZE*4/1000)/4;
	if (distance>=MAX_ROUTE) distance = MAX_ROUTE-1;
    // ÀÌµ¿ÁßÀÎ MOBÀº 4(STANDINGBY)ÃÊ¿¡ ÇÑ¹ø¾¿ Move?
     
	LastX = TargetX;
	LastY = TargetY;
/////////////////////////////////////////////////////////////////////////////////////////
	NextX = LastX+rand()%7-3;
	NextY = LastY+rand()%7-3;
          
//////////////////////////////////////////////////////////////////////////////////////////

	GetEmptyMobGrid(0,&NextX,&NextY);
	for (int dis=distance;dis>=0;dis--) //
	{
         BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); //, (short**)pHeightGrid);
         if (pMobGrid[NextY][NextX]==0) break;
		 if (dis!=distance)  // 2¹øÂ°ºÎÅÍ´Â ÁÖÀ§ÀÇ ´Ù¸¥ Å¸ÀÏµµ °Ë»çÇÑ´Ù.
		 { 	GetEmptyMobGrid(0,&NextX,&NextY);
            BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); //, (short**)pHeightGrid);
            if (pMobGrid[NextY][NextX]==0) break;
		 }  

	 }
     if (dis==-1 || Route[0]==0)
     {  
        NextX=TargetX;
		NextY=TargetY;
		Route[0]=0;
     }
	 return;
}

//   STANDINGBY tickÈÄÀÇ ÀÚ½ÅÀÇ À§Ä¡¸¦ ±¸ÇÑ´Ù.
//   Segment¸¦ ÇâÇØ ÀÌµ¿. ¶Ç´Â Enemy¸¦ ÇâÇØ ÀÌµ¿.
void CMob::GetTargetPos(int tz)
{
	int speed = m_iMoveSpeed; // ÃÊ´ç ÀÌµ¿ °Å¸®
 	if  (speed==0)
	{	NextX = TargetX;
		NextY = TargetY;
		return;
	}
    int distance = speed; //* SECBATTLE /4;
	if (distance>=MAX_ROUTE) distance = MAX_ROUTE-1;
     // ÀÌµ¿ÁßÀÎ MOBÀº 4(STANDINGBY)ÃÊ¿¡ ÇÑ¹ø¾¿ Move?
     
	 LastX = TargetX;
	 LastY = TargetY;
/////////////////////////////////////////////////////////////////////////////////////////
	 NextX = pMob[tz].TargetX;
	 NextY = pMob[tz].TargetY;
//////////////////////////////////////////////////////////////////////////////////////////

	 //GetEmptyMobGrid4Route(0,&NextX,&NextY);
	 //GetEmptyMobGrid(0,&NextX,&NextY);
	 HS2D_COORD kCur;
	 HS2D_COORD kDest;
	 kCur.x = TargetX;
	 kCur.y = TargetY;
	 kDest.x = NextX;
	 kDest.y = NextY;
	 GetAttackPos( m_iHandle, kDest, kCur );
	 NextX = kDest.x;
	 NextY = kDest.y;
	 for (int dis=distance;dis>=0;dis--) //
	 {
         BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); // , (short**)pHeightGrid);
		 //BASE_GetRoute2(LastX,LastY,&NextX,&NextY,Route,dis);
         if (pMobGrid[NextY][NextX]==0) break;
		 if (dis!=distance)  // 2¹øÂ°ºÎÅÍ´Â ÁÖÀ§ÀÇ ´Ù¸¥ Å¸ÀÏµµ °Ë»çÇÑ´Ù.
		 { 	GetEmptyMobGrid(0,&NextX,&NextY);
            BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); //, (short**)pHeightGrid);
            if (pMobGrid[NextY][NextX]==0) break;
		 }  
	 }

	if (dis==-1 || Route[0]==0)
	{
		int iRes = eTNRes_Failed;
		m_iPathIndex = 0;
		NextX=TargetX;
		NextY=TargetY;

		if( m_iReactToEnemyBehindWall )
		{
			HS2D_COORD kSrc, kTar, kDest;
			kSrc.x = TargetX;
			kSrc.y = TargetY;
			kTar.x = pMob[tz].TargetX;
			kTar.y = pMob[tz].TargetY;
			kDest.iBuf = 0;

			iRes = MoveAside( kSrc, kTar, kDest, distance, eTNCell_SafetyZone/*m_iBlockedCell*/ );

			if( eTNRes_Succeeded == iRes )
			{
				NextX = kDest.x;
				NextY = kDest.y;
				m_iPathIndex = 1;
			}
		}
    }


     //Distance¸¦ 1¾¿ ÁÙ°Ü°¡¸ç Valid Nextpos¸¦ ±¸ÇÑ´Ù.
	 return;
}



BOOL CMob::CheckGetLevel(void)
{
	/*
     int ret = FALSE;
	 int cls = MOB.Class;
	 int CurSeg = 0;
	 if (MOB.BaseScore.Level>=MAX_LEVEL) return 0;
	 //while(1) // ÇÑ¹ø¿¡ 1·¾½Ä
	 //{

		 int cur = MOB.BaseScore.Level;
		 if  (cur>=MAX_LEVEL-1 ) return 0;
         
  	     int exp = MOB.Exp;
		 int curexp   =  g_pNextLevel[cur];
		 int nextexp  =  g_pNextLevel[cur+1];
		 int deltaexp =  (nextexp-curexp)/4;
		 int Segment1 =  curexp + deltaexp;
		 int Segment2 =  curexp + (deltaexp*2);
		 int Segment3 =  curexp + (deltaexp*3);
		 int Segment4 =  nextexp;
         
		 if (exp>Segment3) CurSeg = 3; else
		 if (exp>Segment2) CurSeg = 2; else
		 if (exp>Segment1) CurSeg = 1; 

		 
		 if  (exp>=nextexp)
		 { 	 MOB.BaseScore.Level++;
			 MOB.BaseScore.MaxHp = MOB.BaseScore.MaxHp + g_pIncrementHp[cls];
             MOB.BaseScore.MaxMp = MOB.BaseScore.MaxMp + g_pIncrementMp[cls];
		     MOB.CurrentScore.Hp = MOB.CurrentScore.MaxHp; 
		     MOB.CurrentScore.Mp = MOB.CurrentScore.MaxMp; 
		     if (MOB.BaseScore.Level>=200) MOB.SkillBonus+=4; else MOB.SkillBonus+=3; 
		     MOB.SpecialBonus+=2;
		    if (MOB.BaseScore.Level>=255) MOB.ScoreBonus+=10; else MOB.ScoreBonus+=5;

			MOB.BaseScore.Ac++;
			 GetCurrentScore(0);
	         ret = 4;
			 Segment = 0;
		 } 	 else
		 if  (exp>=Segment3 && Segment<3) 
		 { 	 ret = 3;
		     Segment = 3;
		 }   else
		 if  (exp>=Segment2 && Segment<2)
		 {   ret = 2;
		     Segment = 2;
		 }   else
		 if  (exp>=Segment1 && Segment<1)
		 {   ret = 1;
		     Segment = 1;
		 }   else
		 {   return ret;
		 }
		 if  (ret>=1 && ret<=3)
		 {
		     MOB.CurrentScore.Hp = MOB.CurrentScore.MaxHp; 
		     MOB.CurrentScore.Mp = MOB.CurrentScore.MaxMp; 
			 GetCurrentScore(0);
		    return ret;
		 }
	 //}

	 return ret;
	*/
	return TRUE;
}

void CMob::GetNextPos(int battle)
{
	if  (m_iMoveSpeed==0)
	{	NextX = TargetX;
	    NextY = TargetY;
		return;
	}


	int speed = m_iMoveSpeed;
	//int distance = speed * SECSTANDINGBY*(TICKSIZE*4/1000)/4;
	int distance = speed * SECSTANDINGBY/4;
	if	(distance>=MAX_ROUTE) distance=MAX_ROUTE-1;
     // ÀÌµ¿ÁßÀÎ MOBÀº 4(STANDINGBY)ÃÊ¿¡ ÇÑ¹ø¾¿ Move?
    
	if( ( 0 >= SegmentX || MAX_GRIDX <= SegmentX ) || ( 0 >= SegmentY ) || ( MAX_GRIDY <= SegmentY ) )
	{	NextX=TargetX;
		NextY=TargetY;
		Route[0]=0;
		int kk=0;
		return;
	}

	LastX = TargetX;
	LastY = TargetY;
	NextX = SegmentX;
	NextY = SegmentY;
     //int aimx,aimy;
	for (int dis=distance;dis>=0;dis--) //
	{
        BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); //, (short**)pHeightGrid);
		if	(pMobGrid[NextY][NextX]==0) break;
		if	(dis!=distance)  // 2¹øÂ°ºÎÅÍ´Â ÁÖÀ§ÀÇ ´Ù¸¥ Å¸ÀÏµµ °Ë»çÇÑ´Ù.
		{ 	GetEmptyMobGrid(0,&NextX,&NextY);
            BASE_GetRoute(LastX,LastY,&NextX,&NextY,Route,dis, m_iBlockedCell ); //, (short**)pHeightGrid);
            if (pMobGrid[NextY][NextX]==0) break;
		}  
	}

	//int iForbiddenCell = eTNCell_MonsterNotAllowed;
	//if( eMob_NPC == m_eMobType ) iForbiddenCell = eTNCell_NPCNotAllowed;

	 // animx,aimyÀÇ next Æ÷Áö¼Ç.
	if	( NextX<0 || NextY<0 || NextX>MAX_GRIDX || NextY>MAX_GRIDY )
	{	NextX=TargetX;
		NextY=TargetY;
		Route[0]=0;
		int kk=0;
		return;
		// nextxy¸¦ ±¸ÇÒ¼ö ¾ø´Ù. -.-;;
	}
	if	(dis<0 || Route[0]==0 || ( m_iBlockedCell & g_krgCell[NextY][NextX].usProperty ) ) // ÀÌµ¿ ¸øÇÏ´Â Áö¿ª
	{	NextX=TargetX;
		NextY=TargetY;
		Route[0]=0;
		int kk=0;
		return;
		// nextxy¸¦ ±¸ÇÒ¼ö ¾ø´Ù. -.-;;
	}
    if	(pMobGrid[NextY][NextX]!=0) 
	{   int ll=0;
	}
    //Distance¸¦ 1¾¿ ÁÙ°Ü°¡¸ç Valid Nextpos¸¦ ±¸ÇÑ´Ù.

	return; // Á¤»ó Á¾·á
}




/////////////////////////////////////////////////////////////////////
// 
//                  GetEnemyFromView ¹ÖÊÇ·ñÖ÷¶¯¹¥»÷
//
/////////////////////////////////////////////////////////////////////
//    ½Ã¾ß¿¡ ¹ß°ßÇÏ¸é °ø°ÝÇØ¾ß ÇÒ ÀûÀÌ ÀÖ´ÂÁö Ã£´Â´Ù.
//    °ø°ÝÇÒ ´ë»óÀ» Ã£Áö ¸øÇßÀ»°æ¿ì 0À» ¸®ÅÏÇÑ´Ù.
// 
int  CMob::GetEnemyFromView(void)
{
	//if( eTNClan_Brahma == m_byClan ) return 0;
	//if( eTNClan_Vishnu >= m_byClan ) return 0; // player¶ó°í »ý°¢ÇÏ¸é µÉ °ÍÀÌ´Ù.
	//if( eTNClan_Siva == m_byClan ) return 0; // player¶ó°í »ý°¢ÇÏ¸é µÉ °ÍÀÌ´Ù.
	if( eTNClan_Neutral == m_byClan ) return 0;
	if( eTNClan_VictimNeut == m_byClan ) return 0;

	int iRadius = m_byBodyRadius + m_kSight.sPeace;
	if( 0 >= iRadius ) return 0;
	if( eRds_MaxDetectEnemy >= iRadius )
	{
		int iMaxIndex = g_pDetectEnemyRadius[iRadius];
		int x, y;
		for( int i = 0; i < iMaxIndex; ++i )
		{
			x = TargetX + g_pDetectEnemyTable[i][0];
			y = TargetY + g_pDetectEnemyTable[i][1];
			if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
			if( m_iBlockedCell & g_krgCell[y][x].usProperty ) continue;
			int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
			if	(pMob[tmob].MOB.nHP <=0) continue;
			if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
			if( m_iCantDetect & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip  //fors_debug ÊÇ·ñÄÜÖ÷¶¯¹¥»÷ icandectect = 32
			if( eTNVSAfn_ProtectFromMonster & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip
			if( ( (pMob[tmob].MOB.byLevel - MOB.byLevel) > eConst_LevelGap ) && (g_iZoneID != 10) && (g_iZoneID != 21) && (g_iZoneID != 9 ) && (g_iZoneID != 12 )  && (g_iZoneID != 16 ) ) continue; // 15·¦ ÃÊ°ú Â÷ÀÌ(16Â÷ÀÌºÎÅÍ)°¡ ³ª¸é ¼±°øÇÏÁö ¾Ê´Â´Ù. fors_debug monster_level diff ¶àÉÙ¼¶²î²»¹¥»÷
			int tclan = pMob[tmob].m_byClan;
			if	(m_byClan<0 || m_byClan>=MAX_CLAN || tclan<0 || tclan>=MAX_CLAN )
			{	Log("err clan out or range", MOB.szName, 0 );
				return 0;
			}
			if ( eTNClan_Hostile < g_iHostileTable[m_byClan][tclan] ) // g_iHostileTable[»öÀû¸÷][¹ß°ßµÈ¸÷] // -1:Aggresive, 0:neutral, 1:same clan
			{
				// ¸÷¸ôÀÌ ¹æÁö
				if( m_iCheckEnemyCount < pMob[tmob].m_iAttackerCount ) // ÀûÀÇ Àû¼ö°¡ ±âÁØÄ¡¸¦ ³Ñ¾î°¡¸é ¼±°øÀ» ÇÏÁö ¾Ê´Â´Ù.
				{
					Think( eTNAI_StopToAttack, tmob );
					return 0;
				}
				if( m_kAggrCond.Random() ) return tmob;
			}
		}
	}
	else
	{
		int dx1 = TargetX - iRadius;
		int dy1 = TargetY - iRadius; 
		int dx2 = TargetX + iRadius;
		int dy2 = TargetY + iRadius;

		for (int y=dy1;y<dy2;y++)
		{   for (int x=dx1;x<dx2;x++)
			{ 
				if	(x==TargetX&&y==TargetY) continue;
				if	(x<0||y<0||x>MAX_GRIDX||y>MAX_GRIDY) continue;
				int tmob = pMobGrid[y][x];  if (tmob==0 ) continue;
				if	(pMob[tmob].MOB.nHP <=0) continue;
				if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
				if( eTNVSAfn_ProtectFromMonster & pMob[tmob].m_iAffections ) continue;
				if( m_iCantDetect & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip
				if( ( (pMob[tmob].MOB.byLevel - MOB.byLevel) > eConst_LevelGap ) && (g_iZoneID != 10) && (g_iZoneID != 21) && (g_iZoneID != 9 ) && (g_iZoneID != 12 ) )  continue; // 15·¦ ÃÊ°ú Â÷ÀÌ(16Â÷ÀÌºÎÅÍ)°¡ ³ª¸é ¼±°øÇÏÁö ¾Ê´Â´Ù.
				int tclan = pMob[tmob].m_byClan;
				if	(m_byClan<0 || m_byClan>=MAX_CLAN || tclan<0 || tclan>=MAX_CLAN )
				{	Log("err clan out or range", MOB.szName, 0 );
					return 0;
				}
				if ( eTNClan_Hostile < g_iHostileTable[m_byClan][tclan] ) // g_iHostileTable[»öÀû¸÷][¹ß°ßµÈ¸÷] // -1:Aggresive, 0:neutral, 1:same clan
				{
					
					if( m_iCheckEnemyCount < pMob[tmob].m_iAttackerCount ) // ÀûÀÇ Àû¼ö°¡ ±âÁØÄ¡¸¦ ³Ñ¾î°¡¸é ¼±°øÀ» ÇÏÁö ¾Ê´Â´Ù.
					{
						Think( eTNAI_StopToAttack, tmob );
						return 0;
					}

					if( m_kAggrCond.Random() ) return tmob;
				}
			}
		}
	}

    return 0;
}


//@Param
//	- a_iFarFirst : 0ÀÌ¸é °¡±î¿î targetºÎÅÍ ¼±Á¤, 0ÀÌ ¾Æ´Ï¸é °¡Àå ¸Ö¸® ÀÖ´Â targetºÎÅÍ ¼±Á¤
int CMob::SelectTarget( int a_iRange, int a_iAllowedTarget, int a_iCount, int* a_prgTarget, int a_iFarFirst, int a_iCenterX, int a_iCenterY )
{
	int iRadius = m_byBodyRadius + a_iRange;
	if( 0 >= iRadius ) return eTNRes_Failed;

	if( 0 == a_iCenterX && 0 == a_iCenterY )
	{
		a_iCenterX = TargetX;
		a_iCenterY = TargetY;
	}

	if( a_iCenterX<0 || a_iCenterY<0 || a_iCenterX>MAX_GRIDX || a_iCenterY>MAX_GRIDY ) return eTNRes_Failed;

	if( TN_MAX_TARGET_COUNT < a_iCount ) a_iCount = TN_MAX_TARGET_COUNT;
	int iIndex = 0;
	int* pAllowedTarget = NULL;
	if( eTNAT_Friend == a_iAllowedTarget )
	{
		if( eZoneType_God == g_iZoneType ) pAllowedTarget = (int*)&g_irgFriendTableRvR[m_byClan];
		else if( eZoneType_Guild == g_iZoneType ) pAllowedTarget = (int*)&g_irgFriendTableStrH[m_byClan];
		else pAllowedTarget = (int*)&g_irgFriendTable[m_byClan];
	}
	else if( (eTNAT_Enemy == a_iAllowedTarget) || (eTNAT_EnemyFarFirst == a_iAllowedTarget) )
	{		
		if( eZoneType_God == g_iZoneType ) pAllowedTarget = (int*)&(g_irgEnemyTableRvR[m_byClan]);
		else if( eZoneType_Guild == g_iZoneType ) pAllowedTarget = (int*)&(g_irgEnemyTableStrH[m_byClan]);
		else pAllowedTarget = (int*)&g_irgEnemyTablePKOn[m_byClan];
	}

	if( eRds_MaxDetectEnemy >= iRadius )
	{
		int iMaxIndex = g_pDetectEnemyRadius[iRadius];		
		int x, y;

		if( 0 == a_iFarFirst ) // °¡±î¿î target ºÎÅÍ 
		{
			for( int i = 0; i < iMaxIndex; ++i )
			{
				x = a_iCenterX + g_pDetectEnemyTable[i][0];
				y = a_iCenterY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				if( m_iBlockedCell & g_krgCell[y][x].usProperty ) continue;
				int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
				if( eTNClan_GM == pMob[tmob].m_byClan) continue;
				if( pMob[tmob].MOB.nHP <=0) continue;
				if( pMob[tmob].Mode==MOB_EMPTY)	continue;
				if( eTNVSAfn_ProtectFromMonster & pMob[tmob].m_iAffections ) continue;
				if( m_iCantDetect & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip
				//if( (pMob[tmob].MOB.byLevel - MOB.byLevel) > eConst_LevelGap ) continue; // 15·¦ ÃÊ°ú Â÷ÀÌ(16Â÷ÀÌºÎÅÍ)°¡ ³ª¸é ¼±°øÇÏÁö ¾Ê´Â´Ù.
				if( NULL != pAllowedTarget )
					if( pAllowedTarget[pMob[tmob].m_byClan] ) continue;
				a_prgTarget[iIndex] = tmob;
				++iIndex;
				if( a_iCount <= iIndex ) return eTNRes_Succeeded;
			}
		}
		else
		{
			for( int i = iMaxIndex; i > 0; --i )
			{
				x = a_iCenterX + g_pDetectEnemyTable[i][0];
				y = a_iCenterY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				if( m_iBlockedCell & g_krgCell[y][x].usProperty ) continue;
				int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
				if	(eTNClan_GM == pMob[tmob].m_byClan) continue;
				if	(pMob[tmob].MOB.nHP <=0) continue;
				if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
				if( eTNVSAfn_ProtectFromMonster & pMob[tmob].m_iAffections ) continue;
				if( m_iCantDetect & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip
				//if( (pMob[tmob].MOB.byLevel - MOB.byLevel) > eConst_LevelGap ) continue; // 15·¦ ÃÊ°ú Â÷ÀÌ(16Â÷ÀÌºÎÅÍ)°¡ ³ª¸é ¼±°øÇÏÁö ¾Ê´Â´Ù.
				if( NULL != pAllowedTarget )
					if( pAllowedTarget[pMob[tmob].m_byClan] ) continue;
				a_prgTarget[iIndex] = tmob;
				++iIndex;
				if( a_iCount <= iIndex ) return eTNRes_Succeeded;
			}
		}
	}
	else
	{
		int iRandom = rand() % 3;
		int dx1 = a_iCenterX - iRadius + iRandom;
		int dy1 = a_iCenterY - iRadius; 
		int dx2 = a_iCenterX + iRadius;
		int dy2 = a_iCenterY + iRadius + iRandom;

		for( int iStep = 0; iStep < 3; ++iStep )
		{
			for (int y = dy1; y < dy2; ++y )
			{   for (int x = dx1 + iStep; x < dx2; x += 3 )
				{ 
					if	(x==a_iCenterX&&y==a_iCenterY) continue;
					if	(x<0||y<0||x>MAX_GRIDX||y>MAX_GRIDY) continue;
					int tmob = pMobGrid[y][x];  if (tmob==0 ) continue;
					if	(pMob[tmob].MOB.nHP <=0) continue;
					if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
					if( eTNVSAfn_ProtectFromMonster & pMob[tmob].m_iAffections ) continue;
					if( m_iCantDetect & pMob[tmob].m_iAffections ) continue; // Åõ¸í»óÅÂÀÇ ÀûÀº skip
					if( NULL != pAllowedTarget )
						if( pAllowedTarget[pMob[tmob].m_byClan] ) continue;
					a_prgTarget[iIndex] = tmob;
					++iIndex;
					if( a_iCount <= iIndex ) return eTNRes_Succeeded;
				}
			}
		}
	}

    return eTNRes_Succeeded;
}





// Logout½Ã¿¡ ¸ðµç Á¤º¸¸¦ clear ½ÃÄÑÁØ´Ù.
void CMob::ClearProperty()
{
	return;

	memset( &MOB, 0, sizeof(MOB) );
	Init();
}


bool CMob::IsWaitToPop()
{
	if( CurrentTime < m_kLastTime.uiKilled ) return true; // ¾ÆÁ÷ ´ë±â ½Ã°£ÀÌ ³²¾Ò´Ù.

	return false; // ±â´Ù¸®´Â ´Ü°è´Â ³Ñ¾ú´Ù.
}


void CMob::DetermineNextPopTime( int a_iCaller )
{
	int iMonsterDataIndex = MOB.nTP;

	if( 0 > iMonsterDataIndex || MAX_MONSTER_DATA <= iMonsterDataIndex )
	{
		iMonsterDataIndex = MOB.snTribe - 2000;
	}

	int iMinPopDelay = pMonsterData[iMonsterDataIndex].Equip[eMonPrty_PopDelayMin].snIndex;
	int iMaxPopDelay = pMonsterData[iMonsterDataIndex].Equip[eMonPrty_PopDelayMax].snIndex;
	int iPopDelay = PlayDice( iMinPopDelay, iMaxPopDelay );
	m_kLastTime.uiKilled = CurrentTime + iPopDelay * 1000; // 3,600,000
	
	/*
	#ifdef __TN_TOP_LOG__
	if( eZoneType_Guild == g_iZoneType )
	{
		SYSTEMTIME st;
		GetLocalTime( &st );
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] DetermineNextPopTime> Handle:%d, Tribe:%d, MonsterIndex:%d(%d), Now:%u, Killed:%u, PopDelay(%d,%d):%d, caller:%d \r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, m_iHandle, MOB.snTribe, iMonsterDataIndex, MOB.nTP
			, CurrentTime, m_kLastTime.uiKilled, iMinPopDelay, iMaxPopDelay, iPopDelay
			, a_iCaller
			);
		WriteLog( chBuf, ".\\Log\\[DEBUG]Duruka.txt" );
		//WriteLog( chBuf, ".\\Monster_Log\\[DEBUG]Immunity.txt" );
	}
	#endif
	*/
}


void CMob::RestrictChakra()
{
	//if( g_irgSetting[eCnst_HeartMax] < MOB.sHeart ) 
	if( (g_irgSetting[eCnst_HeartMax] < MOB.sHeart) && (2000 > MOB.sHeart) ) 
	{ // ¼ø¼ö Â÷Å©¶ó Á¦ÇÑ
		MOB.sHeart = g_irgSetting[eCnst_HeartMax];
		SendClientMessage( m_iHandle, g_pMessageStringTable[_HeartRestricted] );

		CalChakra();
		//int iSumChakraModified = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
		//int iPlusChakra = 0;
		//if( 0 < MOB.byClass1 ) iPlusChakra = (MOB.byLevel/10)*3; // 10·¦´ç 3¾¿ Ãß°¡
		//int iTotalChakra = 50 + (MOB.byLevel - 1)*5 + iPlusChakra;
		//if( 99 < MOB.byLevel )
		//{
		//	int iFactor = ((MOB.byLevel-100)/10);
		//	iTotalChakra = 577/*50 + 495 + 27 + 5*/ + iFactor*(60 + ((iFactor-1)*10)) + (MOB.byLevel-(99+(10*iFactor)))*(6+(iFactor*2));
		//}

		//m_kCPRemaining.Init( 20000, iTotalChakra - iSumChakraModified );
	}
}



void CMob::UpdatePoints()
{
	UpdateChakra();
	UpdateHPTP();
	UpdateCF();
	UpdateResist();
	UpdateDamage();
	UpdateDefense();
	UpdateSpeed();

	UpdateResistEffects( eRst_Stun );
	UpdateResistEffects( eRst_Sleep );
	UpdateResistEffects( eRst_Blind );
	UpdateResistEffects( eRst_HoldNSlow );
}


void CMob::UpdateChakra()
{
	if( eTNMob_PC != m_eMobType ) return;
	m_kChakra.sMuscle = MOB.sMuscle + m_krgVariation[eTNVar_Muscle][eVar_Equipment].iPlus + m_krgVariation[eTNVar_Muscle][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_Muscle][eVar_Skill].iPlus; // + m_krgVariation[eTNVar_Muscle][eVar_Potion].iPlus;
	m_kChakra.sNerves = MOB.sNerves + m_krgVariation[eTNVar_Nerves][eVar_Equipment].iPlus + m_krgVariation[eTNVar_Nerves][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_Nerves][eVar_Skill].iPlus; //+ m_krgVariation[eTNVar_Nerves][eVar_Potion].iPlus;

	RestrictChakra();

	//if( (g_irgSetting[eCnst_HeartMax] < MOB.sHeart) && (2000 > MOB.sHeart) ) 
	//{
	//	MOB.sHeart = g_irgSetting[eCnst_HeartMax];
	//	SendClientMessage( m_iHandle, g_pMessageStringTable[_HeartRestricted] );
	//	int iSumChakraModified = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
	//	int iPlusChakra = 0;
	//	if( 0 < MOB.byClass1 ) iPlusChakra = (MOB.byLevel/10)*3; // 10·¦´ç 3¾¿ Ãß°¡
	//	int iTotalChakra = 50 + (MOB.byLevel - 1)*5 + iPlusChakra;
	//	if( 99 < MOB.byLevel )
	//	{
	//		int iFactor = ((MOB.byLevel-100)/10);
	//		iTotalChakra = 577/*50 + 495 + 27 + 5*/ + iFactor*(60 + ((iFactor-1)*10)) + (MOB.byLevel-(99+(10*iFactor)))*(6+(iFactor*2));
	//	}
	//	m_kCPRemaining.Init( 20000, iTotalChakra - iSumChakraModified );
	//}

	m_kChakra.sHeart = MOB.sHeart + m_krgVariation[eTNVar_Heart][eVar_Equipment].iPlus + m_krgVariation[eTNVar_Heart][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_Heart][eVar_Skill].iPlus; //+ m_krgVariation[eTNVar_Heart][eVar_Potion].iPlus; 
	//if( g_irgSetting[eCnst_HeartMax] < m_kChakra.sHeart ) m_kChakra.sHeart = g_irgSetting[eCnst_HeartMax];
	m_kChakra.sMind = MOB.sMind + m_krgVariation[eTNVar_Mind][eVar_Equipment].iPlus + m_krgVariation[eTNVar_Mind][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_Mind][eVar_Skill].iPlus; //+ m_krgVariation[eTNVar_Mind][eVar_Potion].iPlus;
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n[UpdateChakra] Â÷Å©¶ó(Base: %d, %d, %d, %d Changed: %d, %d, %d, %d) \r\n", MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind, m_kChakra.sMuscle, m_kChakra.sNerves, m_kChakra.sHeart, m_kChakra.sMind );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	if( 1 > m_kChakra.sMuscle ) m_kChakra.sMuscle = 12 ;
	if( 1 > m_kChakra.sNerves ) m_kChakra.sNerves = 12 ;
	if( 1 > m_kChakra.sHeart ) m_kChakra.sHeart = 12 ;
	if( 1 > m_kChakra.sMind ) m_kChakra.sMind = 12 ;
}

void CMob::UpdateHPTP()
{
	int iMaxHP = 0;
	if( eTNMob_PC == m_eMobType )
	{		
		// HP
		int iHeart1 = m_kChakra.sHeart; 
		int iHeart2 = 0; 
		if( 530 < m_kChakra.sHeart )
		{
			iHeart1 = 530;
			iHeart2 = m_kChakra.sHeart - 530;
		}

		//iMaxHP = (int)(g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iHP * powf( m_kChakra.sHeart, 1.75 ) / 1000 + 5 * m_kChakra.sHeart );
		iMaxHP = (int)(g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iHP * powf( iHeart1, 1.75 ) / 1000 + 5 * iHeart1 );
		if( 0 < iHeart2 ) iMaxHP += iHeart2 * 10;

		#ifdef __TN_2ND_LOG__
		if( 0 >= iMaxHP )
		{
			//SYSTEMTIME st;
			//GetLocalTime( &st );
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> [UpdateHPTP] MaxHP:%d, Heart:%d, Coefficient:%d(class1:%d, class2:%d), powf:%f,  \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
				, iMaxHP, m_kChakra.sHeart, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iHP,  MOB.byClass1, MOB.byClass2, powf( m_kChakra.sHeart, 1.75 ) );
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			char chBuf2[256] = { 0,0,0, };
			sprintf(chBuf2, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> Â÷Å©¶ó(Base: %d, %d, %d, %d Changed: %d, %d, %d, %d) \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
				, MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind, m_kChakra.sMuscle, m_kChakra.sNerves, m_kChakra.sHeart, m_kChakra.sMind );
			WriteLog( chBuf2, g_szrgLogFileName[eLogFileName_Assert] );
		}
		#endif
		iMaxHP += Percent( iMaxHP, (m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPPlus /* + m_krgVariation[eTNVar_MaxHP][eVar_Potion].iPPlus*/) );
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPlus;
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPlus;
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPlus;

		if( iMaxHP < m_krgVariation[eTNVar_LockMaxHP][eVar_Skill].iPlus ) iMaxHP = m_krgVariation[eTNVar_LockMaxHP][eVar_Skill].iPlus;
		if( 0 >= iMaxHP ) iMaxHP = 10;

		int iSitHPRecovery = 0;
		int iHPRecoveryPPlus = m_krgVariation[eTNVar_HPRecovery][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_HPRecovery][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_HPRecovery][eVar_Skill].iPPlus; // + m_krgVariation[eTNVar_HPRecovery][eVar_Potion].iPPlus;
		iSitHPRecovery = (int)( iMaxHP/(5+(int)(iMaxHP/150)) +10 +(m_kChakra.sMind-10)/3 ); // 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iSitHPRecovery = Percent( iSitHPRecovery, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iRecvry );
		//iSitHPRecovery /= 2; // 4ÃÊµ¿¾ÈÀÇ È¸º¹·®
		iSitHPRecovery += Percent( iSitHPRecovery, iHPRecoveryPPlus );
		iSitHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_PassiveSkill].iPlus;
		iSitHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Equipment].iPlus;		
		iSitHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Skill].iPlus;
		//iSitHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Potion].iPlus;
		int iStandHPRecovery = 0;
		iStandHPRecovery = (int)( iMaxHP/(30+(int)(iMaxHP/50)) +(m_kChakra.sMind-10)/3 );// 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iStandHPRecovery = Percent( iStandHPRecovery, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iRecvry );
		//iStandHPRecovery /= 2; // 4ÃÊµ¿¾ÈÀÇ È¸º¹·®
		iStandHPRecovery += Percent( iStandHPRecovery, iHPRecoveryPPlus );
		iStandHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_PassiveSkill].iPlus;
		iStandHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Equipment].iPlus;
		iStandHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Skill].iPlus;
		//iStandHPRecovery += m_krgVariation[eTNVar_HPRecovery][eVar_Potion].iPlus;

		if( g_irgSetting[eCnst_HPRecvMax] < iSitHPRecovery ) iSitHPRecovery = g_irgSetting[eCnst_HPRecvMax];
		if( g_irgSetting[eCnst_HPRecvMax] < iStandHPRecovery ) iStandHPRecovery = g_irgSetting[eCnst_HPRecvMax];		
		m_irgHPRecovery[eTNFsm_Sit] = iSitHPRecovery;
		m_irgHPRecovery[eTNFsm_Stand] = iStandHPRecovery; 

		// TP
		int iMaxTP = 0;
		if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe ) iMaxTP = (int)( g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iTP *powf( m_kChakra.sMind, 1.75 )/100 + 4*m_kChakra.sMind - 10 );
		else iMaxTP = (int)( g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iTP*powf( m_kChakra.sHeart, 1.75 )/100 + 4*m_kChakra.sHeart - 10 );		
		iMaxTP += Percent( iMaxTP, (m_krgVariation[eTNVar_MaxTP][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MaxTP][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_MaxTP][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_MaxTP][eVar_Potion].iPPlus*/) );
		iMaxTP += m_krgVariation[eTNVar_MaxTP][eVar_PassiveSkill].iPlus;
		iMaxTP += m_krgVariation[eTNVar_MaxTP][eVar_Equipment].iPlus;
		iMaxTP += m_krgVariation[eTNVar_MaxTP][eVar_Skill].iPlus;
		//iMaxTP += m_krgVariation[eTNVar_MaxTP][eVar_Potion].iPlus;

		if( iMaxTP < m_krgVariation[eTNVar_LockMaxTP][eVar_Skill].iPlus ) iMaxTP = m_krgVariation[eTNVar_LockMaxTP][eVar_Skill].iPlus;

		m_iMaxTP = iMaxTP;
		if( iMaxTP < MOB.nTP ) MOB.nTP = iMaxTP;

		int iSitTPRecovery = 0;
		int iTPRecoveryPPlus = (m_krgVariation[eTNVar_TPRecovery][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_TPRecovery][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_TPRecovery][eVar_Skill].iPPlus/* + m_krgVariation[eTNVar_TPRecovery][eVar_Potion].iPPlus*/);
		//iSitTPRecovery = (int)( m_iMaxTP/(5+(int)(m_iMaxTP/150)) + m_kChakra.sMind/3 );// 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iSitTPRecovery = (int)( m_iMaxTP/(5+(int)(m_iMaxTP/150)) +15 );// 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iSitTPRecovery = Percent( iSitTPRecovery, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iRecvry );
		//iSitTPRecovery /= 2; // 4ÃÊµ¿¾ÈÀÇ È¸º¹·®
		iSitTPRecovery += Percent( iSitTPRecovery, iTPRecoveryPPlus );
		iSitTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_PassiveSkill].iPlus;
		iSitTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Equipment].iPlus;
		iSitTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Skill].iPlus;
		//iSitTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Potion].iPlus;
		int iStandTPRecovery = 0;
		//iStandTPRecovery = (int)( m_iMaxTP/(30+(int)(m_iMaxTP/50)) + m_kChakra.sMind/3 );// 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iStandTPRecovery = (int)( m_iMaxTP/ ( 30 + (int)(m_iMaxTP/50)) );// 8ÃÊ µ¿¾ÈÀÇ È¸º¹·®
		iStandTPRecovery = Percent( iStandTPRecovery, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iRecvry );
		//iStandTPRecovery /= 2; // 4ÃÊµ¿¾ÈÀÇ È¸º¹·®
		iStandTPRecovery += Percent( iStandTPRecovery, iTPRecoveryPPlus );
		iStandTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_PassiveSkill].iPlus;
		iStandTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Equipment].iPlus;
		iStandTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Skill].iPlus;
		//iStandTPRecovery += m_krgVariation[eTNVar_TPRecovery][eVar_Potion].iPlus;

		if( g_irgSetting[eCnst_TPRecvMax] < iSitTPRecovery ) iSitTPRecovery = g_irgSetting[eCnst_TPRecvMax];
		if( g_irgSetting[eCnst_TPRecvMax] < iStandTPRecovery ) iStandTPRecovery = g_irgSetting[eCnst_TPRecvMax];
		m_irgTPRecovery[0] = iSitTPRecovery;
		m_irgTPRecovery[1] = iStandTPRecovery;

		#ifdef __TN_2ND_LOG__
		if( 0 >= m_iMaxTP )
		{
			//SYSTEMTIME st;
			//GetLocalTime( &st );
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> [UpdateHPTP] TP:%d/%d(%%:%d, +:%d, %%:%d, +:%d, %%:%d, +:%d), TPRecv(Sit:%d, Stand:%d)\r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
				, MOB.nTP, m_iMaxTP, m_krgVariation[eTNVar_MaxTP][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MaxTP][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MaxTP][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_MaxTP][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_MaxTP][eVar_Skill].iPPlus, m_krgVariation[eTNVar_MaxTP][eVar_Skill].iPlus, m_irgTPRecovery[0], m_irgTPRecovery[1] );
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
			char chBuf2[256] = { 0,0,0, };
			sprintf(chBuf2, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> Â÷Å©¶ó(Base: %d, %d, %d, %d Changed: %d, %d, %d, %d) \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
				, MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind, m_kChakra.sMuscle, m_kChakra.sNerves, m_kChakra.sHeart, m_kChakra.sMind );
			WriteLog( chBuf2, g_szrgLogFileName[eLogFileName_Assert] );
		}
		#endif
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		iMaxHP = pMonsterData[MOB.nTP].nHP;
		iMaxHP += Percent(iMaxHP, (m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPPlus /* + m_krgVariation[eTNVar_MaxHP][eVar_Potion].iPPlus*/) );
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPlus;
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPlus;
		iMaxHP += m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPlus;

		if( iMaxHP < m_krgVariation[eTNVar_LockMaxHP][eVar_Skill].iPlus ) iMaxHP = m_krgVariation[eTNVar_LockMaxHP][eVar_Skill].iPlus;

		double dHPRecovery = pMonsterData[MOB.nTP].byQuest[eMonPrty_HPRecovery];
		dHPRecovery = dHPRecovery/10;
		int iHPRecovery = Percent( iMaxHP, dHPRecovery ); // ÃÖÁ¾ÀûÀ¸·Î 1/1000´ÜÀ§À¸·Î °è»êÇÏ±â À§ÇØ, ¸ÕÀú 10À» ³ª´©±â Çß´Ù.
		m_irgHPRecovery[0] = m_irgHPRecovery[1] =  iHPRecovery;
	}

	m_iMaxHP = iMaxHP;
	if( m_iMaxHP < MOB.nHP ) MOB.nHP = m_iMaxHP;

	#ifdef __TN_2ND_LOG__
	if( eTNMob_PC == m_eMobType && 0 >= m_iMaxHP )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> [UpdateHPTP] HP:%d/%d(%%:%d, +:%d, %%:%d, +:%d, %%:%d, +:%d), HPRecv(Sit:%d, Stand:%d)\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
			, MOB.nHP, m_iMaxHP, m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_MaxHP][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPPlus, m_krgVariation[eTNVar_MaxHP][eVar_Skill].iPlus, m_irgHPRecovery[0], m_irgHPRecovery[1] );
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
		char chBuf2[256] = { 0,0,0, };
		sprintf(chBuf2, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> Â÷Å©¶ó(Base: %d, %d, %d, %d Changed: %d, %d, %d, %d) \r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
			, MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind, m_kChakra.sMuscle, m_kChakra.sNerves, m_kChakra.sHeart, m_kChakra.sMind );
		WriteLog( chBuf2, g_szrgLogFileName[eLogFileName_Assert] );

		char chBuf3[256] = { 0,0,0, };
		sprintf(chBuf3, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> Á¾Á·:%d, ÁÖ½Å:%d\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
			, MOB.snTribe, m_byClan );
		WriteLog( chBuf3, g_szrgLogFileName[eLogFileName_Assert] );
		for( int i = 0; i < MAX_SKILL; ++i )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, " %d:%d", i, MOB.bySkill[i] );
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );			
		}

		int iItemID = HT_PARAMTYPE_ITEM_START - 1;
		char chBuf4[1025] = { 0,0,0, };
		sprintf( chBuf4, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ]%s> Helmet:%d(%d,%d),EarR:%d,EarL:%d, Neck:%d,Armor:%d(%d,%d),Belt:%d(%d,%d), HandR:%d(%d,%d),HandL:%d(%d,%d), BraR:%d,BraL:%d, RingR:%d,RingL:%d, Boots:%d(%d,%d),Gloves:%d(%d,%d),Pants:%d(%d,%d)"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.szName
			, MOB.Equip[eTNEqu_Helmet].snIndex+iItemID, MOB.Equip[eTNEqu_Helmet].byRefineLevel, MOB.Equip[eTNEqu_Helmet].snDurability
			, MOB.Equip[eTNEqu_EarringRight].snIndex+iItemID, MOB.Equip[eTNEqu_EarringLeft].snIndex+iItemID
			, MOB.Equip[eTNEqu_Necklace].snIndex+iItemID
			, MOB.Equip[eTNEqu_Armor].snIndex+iItemID, MOB.Equip[eTNEqu_Armor].byRefineLevel, MOB.Equip[eTNEqu_Armor].snDurability
			, MOB.Equip[eTNEqu_Belt].snIndex+iItemID, MOB.Equip[eTNEqu_Belt].byRefineLevel, MOB.Equip[eTNEqu_Belt].snDurability
			, MOB.Equip[eTNEqu_OneHandWeapon].snIndex+iItemID, MOB.Equip[eTNEqu_OneHandWeapon].byRefineLevel, MOB.Equip[eTNEqu_OneHandWeapon].snDurability
			, MOB.Equip[eTNEqu_Shield].snIndex+iItemID, MOB.Equip[eTNEqu_Shield].byRefineLevel, MOB.Equip[eTNEqu_Shield].snDurability
			, MOB.Equip[eTNEqu_BraceletRight].snIndex+iItemID, MOB.Equip[eTNEqu_BraceletLeft].snIndex+iItemID
			, MOB.Equip[eTNEqu_RingRight].snIndex+iItemID, MOB.Equip[eTNEqu_RignLeft].snIndex+iItemID
			, MOB.Equip[eTNEqu_Boots].snIndex+iItemID, MOB.Equip[eTNEqu_Boots].byRefineLevel, MOB.Equip[eTNEqu_Boots].snDurability
			, MOB.Equip[eTNEqu_Gloves].snIndex+iItemID, MOB.Equip[eTNEqu_Gloves].byRefineLevel, MOB.Equip[eTNEqu_Gloves].snDurability
			, MOB.Equip[eTNEqu_Pants].snIndex+iItemID, MOB.Equip[eTNEqu_Pants].byRefineLevel, MOB.Equip[eTNEqu_Pants].snDurability
			);       
		WriteLog( chBuf4, g_szrgLogFileName[eLogFileName_Assert] );



		char temp[256] = { 0,0,0, };
		sprintf( temp, "clo UpdateHPTP PC(%s)> 0 >= MaxHP", MOB.szName );
		Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		SendClientMessage( m_iHandle, g_pMessageStringTable[_Bad_Network_Packets] );
		CloseUser( m_iHandle );
	}
	#endif
}


void CMob::UpdateCF()
{
	if( eTNMob_PC == m_eMobType )
	{
		// 2004.08.19, edited by spencer, °ø¼º/È¸ÇÇ °ø½Ä ¼öÁ¤
		m_kCombatFactors.iAttackRate = int(g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iAttackRate * sqrt((double)m_kChakra.sNerves));
		//m_kCombatFactors.iAttackRate = (short)( (g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iAttackRate * m_kChakra.sNerves+5) /10 );
		m_kCombatFactors.iAttackRate += m_krgVariation[eTNVar_AttackRate][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.iAttackRate += m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPlus;
		
		m_kCombatFactors.iDodgeRate = int(g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iDodgeRate * sqrt((double)m_kChakra.sNerves));
		//m_kCombatFactors.iDodgeRate = (short)( (g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iDodgeRate * m_kChakra.sNerves +5) / 10 );
		m_kCombatFactors.iDodgeRate += m_krgVariation[eTNVar_DodgeRate][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.iDodgeRate += m_krgVariation[eTNVar_DodgeRate][eVar_Equipment].iPlus;

		m_kCombatFactors.iDodgeSpeed = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iDodgeSpeed;
		m_kCombatFactors.iDodgeRate -= m_krgVariation[eTNVar_DodgeSpeed][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.iDodgeRate -= m_krgVariation[eTNVar_DodgeSpeed][eVar_Equipment].iPlus;
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		m_kCombatFactors.iAttackRate = pMonsterData[MOB.nTP].sMuscle;
		m_kCombatFactors.iDodgeRate = pMonsterData[MOB.nTP].sNerves;
		m_kCombatFactors.iDodgeSpeed = pMonsterData[MOB.nTP].Equip[eMonPrty_DodgeSpeed].snIndex; 
	}

	// % Áõ°¨
	m_kCombatFactors.iAttackRate += Percent( m_kCombatFactors.iAttackRate, (m_krgVariation[eTNVar_AttackRate][eVar_Skill].iPPlus/* + m_krgVariation[eTNVar_AttackRate][eVar_Potion].iPPlus*/ ) );
	m_kCombatFactors.iDodgeRate += Percent( m_kCombatFactors.iDodgeRate, (m_krgVariation[eTNVar_DodgeRate][eVar_Skill].iPPlus/* + m_krgVariation[eTNVar_DodgeRate][eVar_Potion].iPPlus*/ ) ) ;

	// +/- Áõ°¨
	m_kCombatFactors.iAttackRate += ( m_krgVariation[eTNVar_AttackRate][eVar_Skill].iPlus /* + m_krgVariation[eTNVar_AttackRate][eVar_Potion].iPlus */);
	m_kCombatFactors.iDodgeRate += ( m_krgVariation[eTNVar_DodgeRate][eVar_Skill].iPlus/* + m_krgVariation[eTNVar_DodgeRate][eVar_Potion].iPlus*/ );
	m_kCombatFactors.iDodgeSpeed -= m_krgVariation[eTNVar_DodgeSpeed][eVar_Skill].iPlus;

	if( eTNVSAfn_CantDefense & m_iAffections )
	{
		m_kCombatFactors.iAttackRate = 1;
		m_kCombatFactors.iDodgeRate = 1;
	}

	if( 0 > m_kCombatFactors.iAttackRate ) m_kCombatFactors.iAttackRate = 1;
	if( 0 > m_kCombatFactors.iDodgeRate ) m_kCombatFactors.iDodgeRate = 1;
	if( 0 > m_kCombatFactors.iDodgeSpeed ) m_kCombatFactors.iDodgeSpeed = 0;

	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateCF] AR: %d(%:%d, +:%d, %:%d, +:%d, %:%d, +:%d) DR: %d(%:%d, +:%d, %:%d, +:%d, %:%d, +:%d) \r\n", m_kCombatFactors.iAttackRate, m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPlus, m_krgVariation[eTNVar_AttackRate][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_AttackRate][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_AttackRate][eVar_Skill].iPPlus, m_krgVariation[eTNVar_AttackRate][eVar_Skill].iPlus, m_kCombatFactors.iDodgeRate, m_krgVariation[eTNVar_DodgeRate][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_DodgeRate][eVar_Equipment].iPlus, m_krgVariation[eTNVar_DodgeRate][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_DodgeRate][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_DodgeRate][eVar_Skill].iPPlus, m_krgVariation[eTNVar_DodgeRate][eVar_Skill].iPlus );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
}


void CMob::UpdateDefense()
{

	int iCharDefense = 0;
	if( eTNMob_PC == m_eMobType )
	{		
		m_kCombatFactors.iAC = m_krgVariation[eTNVar_AC][eVar_Equipment].iPlus;
		m_kCombatFactors.iAC += Percent( m_kCombatFactors.iAC, (m_krgVariation[eTNVar_AC][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_AC][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AC][eVar_Skill].iPPlus) );
		m_kCombatFactors.iAC += (m_krgVariation[eTNVar_AC][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_AC][eVar_Skill].iPlus );

		iCharDefense = (m_kChakra.sMuscle-10 + m_kChakra.sNerves-10 +1)/4;
		m_kCombatFactors.iDefense = (g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iAC * m_kCombatFactors.iAC +5)/10 + iCharDefense;		
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		m_kCombatFactors.iDefense = pMonsterData[MOB.nTP].sHeart;
	}
	
	m_kCombatFactors.iDefense += Percent( m_kCombatFactors.iDefense, (m_krgVariation[eTNVar_Defense][eVar_Skill].iPPlus) );
	m_kCombatFactors.iDefense += (m_krgVariation[eTNVar_Defense][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_Defense][eVar_Skill].iPlus );
	
	if( 0 > m_kCombatFactors.iDefense ) m_kCombatFactors.iDefense = 0;

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateDefense] AC:%d, ÃÖÁ¾AC:%d(%d,%d,%d; %d,%d,%d), CharDF:%d, DF:%d(%d,%d,%d) \r\n"
			, m_krgVariation[eTNVar_AC][eVar_Equipment].iPlus, m_kCombatFactors.iAC
			, m_krgVariation[eTNVar_AC][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_AC][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_AC][eVar_Skill].iPPlus
			, m_krgVariation[eTNVar_AC][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_AC][eVar_Equipment].iPlus, m_krgVariation[eTNVar_AC][eVar_Skill].iPlus
			, iCharDefense, m_kCombatFactors.iDefense
			, m_krgVariation[eTNVar_Defense][eVar_Skill].iPPlus, m_krgVariation[eTNVar_Defense][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_Defense][eVar_Skill].iPlus 
			);
		WriteLog( chBuf, m_szLogFile );
		//if( eTNMob_PC == m_eMobType ), g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iAC
	}
	#endif
}



void CMob::UpdateResist()
{
	if( eTNMob_PC == m_eMobType )
	{
		m_kCombatFactors.irgResist[eRst_Fire] = m_kCombatFactors.irgResist[eRst_Cold] = m_kCombatFactors.irgResist[eRst_Lightning] = m_kCombatFactors.irgResist[eRst_Poison] = Percent( m_kChakra.sMind, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iResist );
		// + Passive skill
		m_kCombatFactors.irgResist[eRst_Fire] += m_krgVariation[eTNVar_FireResist][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.irgResist[eRst_Cold] += m_krgVariation[eTNVar_ColdResist][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.irgResist[eRst_Lightning] += m_krgVariation[eTNVar_LightningResist][eVar_PassiveSkill].iPlus;
		m_kCombatFactors.irgResist[eRst_Poison] += m_krgVariation[eTNVar_PoisonResist][eVar_PassiveSkill].iPlus;
		// + Equipment
		m_kCombatFactors.irgResist[eRst_Fire] += m_krgVariation[eTNVar_FireResist][eVar_Equipment].iPlus;
		m_kCombatFactors.irgResist[eRst_Cold] += m_krgVariation[eTNVar_ColdResist][eVar_Equipment].iPlus;
		m_kCombatFactors.irgResist[eRst_Lightning] += m_krgVariation[eTNVar_LightningResist][eVar_Equipment].iPlus;
		m_kCombatFactors.irgResist[eRst_Poison] += m_krgVariation[eTNVar_PoisonResist][eVar_Equipment].iPlus;
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		m_kCombatFactors.irgResist[eRst_Fire] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snIndex;
		m_kCombatFactors.irgResist[eRst_Cold] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snDurability;
		m_kCombatFactors.irgResist[eRst_Lightning] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].wSerial;
		m_kCombatFactors.irgResist[eRst_Poison] = pMonsterData[MOB.nTP].Equip[eMonPrty_Resist].snDummy;
	}

	// % Áõ°¨
	m_kCombatFactors.irgResist[eRst_Fire] += Percent( m_kCombatFactors.irgResist[eRst_Fire], (m_krgVariation[eTNVar_FireResist][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_FireResist][eVar_Potion].iPPlus*/) );	
	m_kCombatFactors.irgResist[eRst_Cold] += Percent( m_kCombatFactors.irgResist[eRst_Cold], (m_krgVariation[eTNVar_ColdResist][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_ColdResist][eVar_Potion].iPPlus*/) );	
	m_kCombatFactors.irgResist[eRst_Lightning] += Percent( m_kCombatFactors.irgResist[eRst_Lightning], (m_krgVariation[eTNVar_LightningResist][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_LightningResist][eVar_Potion].iPPlus*/) );	
	m_kCombatFactors.irgResist[eRst_Poison] += Percent( m_kCombatFactors.irgResist[eRst_Poison], (m_krgVariation[eTNVar_PoisonResist][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_PoisonResist][eVar_Potion].iPPlus*/) );

	// +/- Áõ°¨
	m_kCombatFactors.irgResist[eRst_Fire] += (m_krgVariation[eTNVar_FireResist][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_FireResist][eVar_Potion].iPlus*/);
	m_kCombatFactors.irgResist[eRst_Cold] += (m_krgVariation[eTNVar_ColdResist][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_ColdResist][eVar_Potion].iPlus*/);
	m_kCombatFactors.irgResist[eRst_Lightning] += (m_krgVariation[eTNVar_LightningResist][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_LightningResist][eVar_Potion].iPlus*/);
	m_kCombatFactors.irgResist[eRst_Poison] += (m_krgVariation[eTNVar_PoisonResist][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_PoisonResist][eVar_Potion].iPlus*/);

	if( 0 > m_kCombatFactors.irgResist[eRst_Fire] ) m_kCombatFactors.irgResist[eRst_Fire] = 0;
	if( 0 > m_kCombatFactors.irgResist[eRst_Cold] ) m_kCombatFactors.irgResist[eRst_Cold] = 0;
	if( 0 > m_kCombatFactors.irgResist[eRst_Lightning] ) m_kCombatFactors.irgResist[eRst_Lightning] = 0;
	if( 0 > m_kCombatFactors.irgResist[eRst_Poison] ) m_kCombatFactors.irgResist[eRst_Poison] = 0;

	if( eTNMob_PC == m_eMobType )
	{
		if( g_irgSetting[eCnst_ResistMax] < m_kCombatFactors.irgResist[eRst_Fire] ) m_kCombatFactors.irgResist[eRst_Fire] = g_irgSetting[eCnst_ResistMax];
		if( g_irgSetting[eCnst_ResistMax] < m_kCombatFactors.irgResist[eRst_Cold] ) m_kCombatFactors.irgResist[eRst_Cold] = g_irgSetting[eCnst_ResistMax];
		if( g_irgSetting[eCnst_ResistMax] < m_kCombatFactors.irgResist[eRst_Lightning] ) m_kCombatFactors.irgResist[eRst_Lightning] = g_irgSetting[eCnst_ResistMax];
		if( g_irgSetting[eCnst_ResistMax] < m_kCombatFactors.irgResist[eRst_Poison] ) m_kCombatFactors.irgResist[eRst_Poison] = g_irgSetting[eCnst_ResistMax];
	}

	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateResist] Fire:%d, Cold:%d, Lightning:%d, Poison:%d \r\n", m_kCombatFactors.irgResist[eRst_Fire], m_kCombatFactors.irgResist[eRst_Cold], m_kCombatFactors.irgResist[eRst_Lightning], m_kCombatFactors.irgResist[eRst_Poison] );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
}

void CMob::ToBlessGod(int a_user)
{
	if (!(eTNVSAfn_BlessOfGod & pMob[a_user].m_iAffections) )	
	{
	TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;//,kEffect5;
			kEffect1.iID = eTNAfn_ACPlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 30;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_AttackRatePlus ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 30;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_DodgeRatePlus  ;
			kEffect3.kFunc.iData = 1;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 30;
			kEffect3.iParam2 = 0;	
			
			kEffect4.iID = eTNAfn_AllDamagePlus  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 30;
			kEffect4.iParam2 = 0;				

		/*	kEffect5.iID = eTNAfn_BlessOfGod  ;
			kEffect5.kFunc.iData = 0;
			kEffect5.iDuration = eTNSklD_Unlimited;
			kEffect5.iParam1 = 0;
			kEffect5.iParam2 = 0;	*/

	AffectEffect( kEffect1, eVar_Skill, eAfn_Add, a_user, a_user, 0 );
    AffectEffect( kEffect2, eVar_Skill, eAfn_Add, a_user, a_user, 0 );
	AffectEffect( kEffect3, eVar_Skill, eAfn_Add, a_user, a_user, 0 );
	AffectEffect( kEffect4, eVar_Skill, eAfn_Add, a_user, a_user, 0 );
   // AffectEffect( kEffect5, eVar_Skill, eAfn_Add, a_user, a_user, 0 );
pMob[a_user].m_iAffections = pMob[a_user].m_iAffections ^ eTNVSAfn_BlessOfGod; //fors_debug test blessgod here iBlessOfGod
pMob[a_user].BroadcastUpdateStatusMsg();
pMob[a_user].NotifyUpdateUIMsg();
pMob[a_user].m_isBlessGod = 1; //fors_debug ¸Õ¸Õ±»×£¸£

int igivewhich=0;  
igivewhich=pMob[a_user].MOB.byTrimuriti;
if (igivewhich==1) GiveItem(a_user,7345,1);
else if (igivewhich==2) GiveItem(a_user,7347,1);
else GiveItem(a_user,7350,1);

                 int iidx = 0;
		 int irgdeng[3] = { 6758,6719,6745,};
                 iidx=GetMobMyRandom(0,2);
                 GiveItem(a_user,irgdeng[iidx],1);

//×£¸£ÔÂ¹â fors_debug
				 GiveItem(a_user,6718,1);
if (pMob[a_user].MOB.snKarma == 0)
 { 
     if (pMob[a_user].MOB.byQuest[97] != 255)
		 pMob[a_user].MOB.byQuest[97] ++ ;
	char szMsg[300] = { 0,0,0, }; 
     pMob[a_user].MOB.byQuest[96] ++ ;
	pMob[a_user].MOB.byQuest[95] ++ ;
	pMob[a_user].MOB.byQuest[94] ++ ;

     if (pMob[a_user].MOB.byQuest[97] != 255)
	 {
	     
		 sprintf( szMsg, "ÉñµÄÓÂÕß[%s]ÒÑ½ÓÊÜÉñµÄ×£¸£%d´Î", pMob[a_user].MOB.szName, pMob[a_user].MOB.byQuest[97] );								
		 PostMessageToZone( szMsg );
	 } 
	if ( pMob[a_user].MOB.byQuest[96] >= 4 )
     {
	         char szstoneMsg[300] = { 0,0,0, };
		 sprintf( szstoneMsg, "[%s]Õ½¶·ÓÂÍùÖ±Ç°,½±ÀøÉñÃØÀñÎïÒ»·Ý,", pMob[a_user].MOB.szName);								
		 PostMessageToZone( szstoneMsg );   
                 int iiidx = 0;
		 int irgNBstone[4] = { 6610,6611,6612,6613,};
         pMob[a_user].MOB.byQuest[96]=0;
                 iiidx=GetMobMyRandom(0,3);
                 GiveItem(a_user,irgNBstone[iiidx],1);
		   
     }
	if ( pMob[a_user].MOB.byQuest[95] >= 2 )
     {
	         char szstoneMsg[300] = { 0,0,0, };
		 sprintf( szstoneMsg, "[%s]Õ½¶·ÓÂÍùÖ±Ç°,½±ÀøÉñÃØÀñÎïÒ»·Ý,", pMob[a_user].MOB.szName);								
		 PostMessageToZone( szstoneMsg );   
                 int iiidx1 = 0;
		 int irgNBstone1[4] = { 6556,6553,6614,6551,};
         pMob[a_user].MOB.byQuest[95]=0;
                 iiidx1=GetMobMyRandom(0,3);
                 GiveItem(a_user,irgNBstone1[iiidx1],1);
		   
     }
	if ( pMob[a_user].MOB.byQuest[94] >= 10 )
     {
	         char szstoneMsg[300] = { 0,0,0, };
		 sprintf( szstoneMsg, "[%s]ÉñÓÂÎÞ±È,½±ÀøNB·ûÖäÒ»Ã¶,Èç»¢ÌíÒí", pMob[a_user].MOB.szName);								
		 PostMessageToZone( szstoneMsg );   
                 int iiidx2 = 0;
		 int irgNBstone2[4] = { 6842,6843,6844,6845,};
         pMob[a_user].MOB.byQuest[94]=0;
                 iiidx2=GetMobMyRandom(0,3);
                 GiveItem(a_user,irgNBstone2[iiidx2],60);
		   
     } 

	 if ( pMob[a_user].MOB.byQuest[97] == 99 )
	 {
	
	sprintf( szMsg, "ÉñµÄÓÂÕß[%s]ÒÑ½ÓÊÜµ½ÊØ»¤ÉñµÄ99´Î×£¸£,´ú±í×Å»áÓë°®ÈËÔÚÒ»ÆðÌì³¤µØ¾Ã,½«»ñµÃÊØ»¤ÉñËÍ³öµÄ½á»é×°Ò»¼þ",pMob[a_user].MOB.szName);
	PostMessageToWorld( szMsg );
	if ((pMob[a_user].MOB.snTribe == TRIBE_NAGA)|| (pMob[a_user].MOB.snTribe ==  TRIBE_ASURA)||(pMob[a_user].MOB.snTribe ==  TRIBE_YAKSA)||(pMob[a_user].MOB.snTribe == TRIBE_DEVA))
    GiveItem(a_user, 8901, 1);
	else
     GiveItem(a_user, 8902, 1);

	pMob[a_user].MOB.byQuest[97] = 255;
	 }
 }
//pMob[a_user].m_dwQuestInitTime
	}
}

void CMob::UpdateResistEffects( int a_iResistType )
{
	if( eRst_Stun > a_iResistType || eRst_Sleep < a_iResistType ) return;

	int iVar = 0;
	if( eRst_Stun == a_iResistType ) iVar = eTNVar_ResistStun;
	else if( eRst_Sleep == a_iResistType ) iVar = eTNVar_ResistSleep;
	else if( eRst_Blind == a_iResistType ) iVar = eTNVar_ResistBlind;
	else if( eRst_HoldNSlow == a_iResistType ) iVar = eTNVar_ResistHoldNSlow;
	else return;

	int iResistEffect = 0;
	iResistEffect = m_krgVariation[iVar][eVar_Equipment].iPlus + m_krgVariation[iVar][eVar_PassiveSkill].iPlus + m_krgVariation[iVar][eVar_Skill].iPlus;
	if( 100 < iResistEffect ) iResistEffect = 100;
	if( 0 > iResistEffect ) iResistEffect = 0;
	m_krgResistEffect[a_iResistType].Init( iResistEffect );

	#ifdef __DEBUG_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateResistEffects] value:%d, type:%d(0:stun,1:blind,2:Hold,3:sleep)\r\n"
			, iResistEffect, a_iResistType
			);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

}


void CMob::UpdateDamage()
{
	UpdateDamage( eTNEqu_OneHandWeapon );
	if( m_bDualWeapon ) UpdateDamage( eTNEqu_Shield );
}

// Damage °è»ê °ø½Ä¿¡ ÀÇÇØ º¯°æÀ» ÇØÁà¾ß ÇÑ´Ù.
void CMob::UpdateDamage( int a_iHand )
{
	int iHand = eHnd_Right;
	if( eTNEqu_Shield == a_iHand ) iHand = eHnd_Left;

	TNDAMAGE kDamage;
	int iMasterIndex = 0;
	int iWeaponIndex = 0;
	int iMasteryIndex = 9;
	if( eTNMob_PC == m_eMobType )
	{
		iWeaponIndex = get_WeaponIndex( a_iHand );
		if( 0 > iWeaponIndex || MAX_ITEM_DATA <= iWeaponIndex )
		{
			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[UpdateDamage] ¹«±â index ¿À·ù> WeaponIIndex:%d, \r\n", iWeaponIndex );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
			iWeaponIndex = 0;
		}

		if( (0 < iWeaponIndex) && (0 >= MOB.Equip[a_iHand].snDurability) ) iWeaponIndex = 0; // ³»±¸µµ°¡ 0ÀÌ¶ó¸é, ¸Ç¼ÕÀ¸·Î º¯°æ

		kDamage = pItemData[iWeaponIndex].kDamage;
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[UpdateDamage] Hand%d, 10(%d,%d,%d,%d)	"
				, a_iHand
				, kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1] );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iBare;
		if( iWeaponIndex )
		{
			if( 0 >= MOB.Equip[a_iHand].snDurability ) iWeaponIndex = 0; // ³»±¸µµ°¡ 0ÀÌ¶ó¸é, ¸Ç¼ÕÀ¸·Î º¯°æ

			if( eTNWpn_Sword & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Sword;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iSword;
				if( eTNWpn_TwoHand & pItemData[iWeaponIndex].sItemType ) m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iTwoHandSword;
			}
			else if( eTNWpn_Axe & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Axe;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iAxe;
				if( eTNWpn_TwoHand & pItemData[iWeaponIndex].sItemType ) m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iTwoHandAxe;
			}
			else if( eTNWpn_Spear & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Spear;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iSpear;
			}
			else if( eTNWpn_Blunt & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Blunt;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iBlunt;
			}
			else if( eTNWpn_Claw & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Claw;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iClaw;
			}
			else if( eTNWpn_Staff & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Staff;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iStaff;
			}
			else if( eTNWpn_Bow & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Bow;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iBow;
			}
			else if( eTNWpn_Dagger & pItemData[iWeaponIndex].sItemType )
			{
				iMasteryIndex = eWpnMtryIdx_Dagger;
				m_iWeaponCoefficient = g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iDagger;
			}

			//--------------------------------
			// Á¦·Ã
			//--------------------------------
			byte byRefineLevel = MOB.Equip[a_iHand].byRefineLevel;
			byRefineLevel += (m_krgVariation[eTNVar_EnhanceWeapon][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_EnhanceWeapon][eVar_Skill].iPlus + m_krgVariation[eTNVar_EnhanceWeapon][eVar_Equipment].iPlus );
			if( MAX_MAINREFINELEVEL < byRefineLevel ) byRefineLevel = MAX_MAINREFINELEVEL;

			if( 0 < byRefineLevel && MAX_MAINREFINELEVEL >= byRefineLevel ) // °­È­ Á¦·Ã
			{
				if( pItemData[iWeaponIndex].sItemType & eTNWpn_TwoHand )
				{
					if( 0 < kDamage.irgPhy[0] )
					{
						kDamage.irgPhy[0] += g_pRefineTable[1][byRefineLevel-1];
						kDamage.irgPhy[1] += g_pRefineTable[1][byRefineLevel-1];
					}
					/*
					if( 0 < kDamage.irgPierce[0] )
					{
						kDamage.irgPierce[0] += g_pRefineTable[1][byRefineLevel-1];
						kDamage.irgPierce[1] += g_pRefineTable[1][byRefineLevel-1];
					}
					*/
				}
				else
				{
					if( 0 < kDamage.irgPhy[0] )
					{
						kDamage.irgPhy[0] += g_pRefineTable[0][byRefineLevel-1];
						kDamage.irgPhy[1] += g_pRefineTable[0][byRefineLevel-1];
					}
					/*
					if( 0 < kDamage.irgPierce[0] )
					{
						kDamage.irgPierce[0] += g_pRefineTable[1][byRefineLevel-1];
						kDamage.irgPierce[1] += g_pRefineTable[1][byRefineLevel-1];
					}
					*/
				}
			}
			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "20(%d,%d), RefineLvl:%d(%d, %d/%d/%d),		"
					, kDamage.irgPhy[0], kDamage.irgPhy[1]
					, byRefineLevel, MOB.Equip[a_iHand].byRefineLevel
					, m_krgVariation[eTNVar_EnhanceWeapon][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_EnhanceWeapon][eVar_Skill].iPlus, m_krgVariation[eTNVar_EnhanceWeapon][eVar_Equipment].iPlus
					);
				WriteLog( chBuf, m_szLogFile );
			}
			#endif

			for( int i = 0; i < MAX_SUBMATERIAL; ++i )  // ¼Ó¼º Á¦·Ã
			{	BYTE byTot=MOB.Equip[a_iHand].bySubRefine[i/2]; BYTE bySubItem=0;
				if(i%2==0)
				{	bySubItem = byTot>>4;	//	»óÀ§4ºñÆ® ¸®µå
				}	else
				{	bySubItem = byTot&0x0F;	//	ÇÏÀ§4ºñÆ® ¸®µå
				}

				if( 0 == bySubItem ) continue;
				int iMatrIndex = (bySubItem + HT_PARAMTYPE_ITEM_REFINE_SUB_START - 1)  - HT_PARAMTYPE_ITEM_START + 1;
				for( int j = 0; j < TN_MAX_EFFECT_COUNT; ++j )
				{
					if( 0 >= pItemData[iMatrIndex].krgEffect[j].iID ) continue;
					switch( pItemData[iMatrIndex].krgEffect[j].iID )
					{
					case eTNAfn_Fire :
						kDamage.irgFire[0] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						kDamage.irgFire[1] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						break;
					case eTNAfn_Cold :
						kDamage.irgCold[0] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						kDamage.irgCold[1] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						break;
					case eTNAfn_Lightning :
						kDamage.irgLightning[0] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						kDamage.irgLightning[1] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						break;
					case eTNAfn_Poison :
						kDamage.irgPoison[0] += pItemData[iMatrIndex].krgEffect[j].iParam1;
						kDamage.irgPoison[1] += pItemData[iMatrIndex].krgEffect[j].iParam1;

						break;
					}
				}
			}

			if( eTNWpn_Staff & pItemData[iWeaponIndex].sItemType )
			{ // ÁöÆÎÀÌ ÀÏ¶§¸¸ ÃÖ´ë ¼Ó¼º damage¸¦ 100À¸·Î Á¦ÇÑÇÑ´Ù.
				if( 100 < kDamage.irgFire[0] ) kDamage.irgFire[0] = 100;
				if( 100 < kDamage.irgFire[1] ) kDamage.irgFire[1] = 100;
				if( 100 < kDamage.irgCold[0] ) kDamage.irgCold[0] = 100;
				if( 100 < kDamage.irgCold[1] ) kDamage.irgCold[1] = 100;
				if( 100 < kDamage.irgLightning[0] ) kDamage.irgLightning[0] = 100;
				if( 100 < kDamage.irgLightning[1] ) kDamage.irgLightning[1] = 100;
				if( 100 < kDamage.irgPoison[0] ) kDamage.irgPoison[0] = 100;
				if( 100 < kDamage.irgPoison[1] ) kDamage.irgPoison[1] = 100;
			}

			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "25(%d,%d,%d,%d)		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif

			//--------------------------------
			// ¼º´É & ·¹º§ Á¦ÇÑ
			//--------------------------------
			int iLevelGap = pItemData[iWeaponIndex].kReq.byLevel - MOB.byLevel;
			double dCorrect = 1;
			if( 0 < iLevelGap ) // ¼º´É Á¦ÇÑ
			{
				--iLevelGap;
				iLevelGap /= 6;
				double dPercent = 50 + iLevelGap * 5;
				if( 95 < dPercent ) dPercent = 95;
				dCorrect = dPercent / 100;
				kDamage.irgPhy[0] -= (int)(kDamage.irgPhy[0] * dCorrect);
				kDamage.irgPhy[1] -= (int)(kDamage.irgPhy[1] * dCorrect);
				kDamage.irgPierce[0] -= (int)(kDamage.irgPierce[0] * dCorrect);
				kDamage.irgPierce[1] -= (int)(kDamage.irgPierce[1] * dCorrect);
			}
			
			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "30(%d,%d,%d,%d), LevelGap:%d, dCorrect:%f		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], iLevelGap, dCorrect );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
		}


		//--------------------------------
		// ¹«±â ¸¶½ºÅÍ¸® Àû¿ë
		//--------------------------------
		if( iWeaponIndex ) // ¸Ç¼ÕÀÌ ¾Æ´Ï¶ó¸é, ...
		{
			if( 0 < kDamage.irgPhy[0] )
			{	
				if( eTNWpn_TwoHand & pItemData[iWeaponIndex].sItemType )
				{
					kDamage.irgPhy[0] += Percent( kDamage.irgPhy[0], m_krgMastery[eWpnMtryIdx_TwoHanded].iParam1 );
					kDamage.irgPhy[1] += Percent( kDamage.irgPhy[1], m_krgMastery[eWpnMtryIdx_TwoHanded].iParam1 );
				}

				kDamage.irgPhy[0] += m_krgMastery[iMasteryIndex].iParam1;
				kDamage.irgPhy[1] += m_krgMastery[iMasteryIndex].iParam1;
			}
		}

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "40(%d,%d,%d,%d), iMasteryIndex:%d, iParam1:%d		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], iMasteryIndex, m_krgMastery[iMasteryIndex].iParam1 );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		if( iWeaponIndex ) m_krgWeaponDamage[iHand] = kDamage;
		else m_krgWeaponDamage[iHand] = pItemData[0].kDamage; // pist //memset( &(m_krgWeaponDamage[eHnd_Right]), 0, sizeof(TNDAMAGE) );

		//2004.08.19, ³ª°¡, ¾ßÅ©»þ ¼öÁ¤
		if( TRIBE_ASURA == MOB.snTribe || TRIBE_RAKSHASA == MOB.snTribe )
		{ // ¾Æ¼ö¶ó/·«»þ»ç
			if( eTNWpn_Bow == (eTNWpn_Bow & pItemData[iWeaponIndex].sItemType) ) 
			{
				if( 0 < kDamage.irgPhy[0] )
				{
					kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle+m_kChakra.sNerves*2)/3+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sNerves - 12);
					kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle+m_kChakra.sNerves*2)/3+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sNerves - 12);
				}
			}
			else
			{
				if( 0 < kDamage.irgPhy[0] )
				{
					kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*2+m_kChakra.sNerves)/3+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sMuscle - 11);
					kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*2+m_kChakra.sNerves)/3+100) * (kDamage.irgPhy[1]+1) /1000+ kDamage.irgPhy[1] + (m_kChakra.sMuscle - 11);
				}
			}
		}
		else if( TRIBE_YAKSA == MOB.snTribe || TRIBE_GANDHARVA == MOB.snTribe )
		{// ¾ßÅ©»þ/°£´Ù¸£¹Ù
			if( 0 < kDamage.irgPhy[0] )
			{
				kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*13+m_kChakra.sNerves*2)/10+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sNerves*8/10);
				kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*13+m_kChakra.sNerves*2)/10+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sNerves*8/10);
			}
		}
		else
		{ // ³ª°¡³ª ¹ý»ç
			if( 0 < kDamage.irgPhy[0] )
			{
				kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*10+m_kChakra.sNerves)/10+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sMuscle - 10);
				kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*10+m_kChakra.sNerves)/10+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sMuscle - 10);
			}
		}

/*
		//2004.08.19, edited by spencer, °ø½Ä ¼öÁ¤
		if( TRIBE_ASURA == MOB.snTribe || TRIBE_RAKSHASA == MOB.snTribe )
		{
			if( eTNWpn_Bow == (eTNWpn_Bow & pItemData[iWeaponIndex].sItemType) ) 
			{
				if( 0 < kDamage.irgPhy[0] )
				{
					kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle+m_kChakra.sNerves*2)/3+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sNerves - 12);
					kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle+m_kChakra.sNerves*2)/3+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sNerves - 12);
				}
			}
			else
			{
				if( 0 < kDamage.irgPhy[0] )
				{
					kDamage.irgPhy[0] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*2+m_kChakra.sNerves)/3+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sMuscle - 11);
					kDamage.irgPhy[1] = m_iWeaponCoefficient * ((m_kChakra.sMuscle*2+m_kChakra.sNerves)/3+100) * (kDamage.irgPhy[1]+1) /1000+ kDamage.irgPhy[1] + (m_kChakra.sMuscle - 11);
				}
			}
		}
		else if( TRIBE_YAKSA == MOB.snTribe || TRIBE_GANDHARVA == MOB.snTribe )
		{
			if( 0 < kDamage.irgPhy[0] )
			{
				kDamage.irgPhy[0] = m_iWeaponCoefficient * (m_kChakra.sMuscle+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sNerves-10);
				kDamage.irgPhy[1] = m_iWeaponCoefficient * (m_kChakra.sMuscle+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sNerves-10);
			}
		}
		else
		{
			if( 0 < kDamage.irgPhy[0] )
			{
				kDamage.irgPhy[0] = m_iWeaponCoefficient * (m_kChakra.sMuscle+100) * kDamage.irgPhy[0] /1000 + kDamage.irgPhy[0] + (m_kChakra.sMuscle - 10);
				kDamage.irgPhy[1] = m_iWeaponCoefficient * (m_kChakra.sMuscle+100) * (kDamage.irgPhy[1]) /1000 + kDamage.irgPhy[1] + (m_kChakra.sMuscle - 10);
			}
		}
*/

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "50(%d,%d,%d,%d), m_iWeaponCoefficient:%d, Chakra(%d,%d,%d,%d)		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], m_iWeaponCoefficient, m_kChakra.sMuscle, m_kChakra.sNerves, m_kChakra.sHeart, m_kChakra.sMind );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif

		if( 0 < kDamage.irgFire[0] )
		{
			kDamage.irgFire[0] += (m_kChakra.sMind + 2)/ 5;
			kDamage.irgFire[1] += (m_kChakra.sMind + 2)/ 5;
		}
		if( 0 < kDamage.irgCold[0] )
		{
			kDamage.irgCold[0] += (m_kChakra.sMind + 2) / 5;
			kDamage.irgCold[1] += (m_kChakra.sMind + 2) / 5;
		}
		if( 0 < kDamage.irgLightning[0] )
		{
			kDamage.irgLightning[0] += (m_kChakra.sMind + 2) / 5;
			kDamage.irgLightning[1] += (m_kChakra.sMind + 2) / 5;
		}
		if( 0 < kDamage.irgPoison[0] )
		{
			kDamage.irgPoison[0] += (m_kChakra.sMind + 2) / 5;
			kDamage.irgPoison[1] += (m_kChakra.sMind + 2) / 5;
		}

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "60(%d,%d,%d,%d), Mind:%d		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], m_kChakra.sMind );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}
	else if( eTNMob_NPC == m_eMobType ) // monsterÀÏ °æ¿ì
	{		
		kDamage = pSkillData[m_krgSkill[0].sID + 500].kDamage;
	}


	//--------------------------------------   % Áõ°¨   -------------------------------------

	if( 0 < kDamage.irgPhy[0] )
	{
		kDamage.irgPhy[0] += Percent( kDamage.irgPhy[0], (m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MinDamage][eVar_PassiveSkill].iPPlus ) );
		kDamage.irgPhy[1] += Percent( kDamage.irgPhy[1], (m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MaxDamage][eVar_PassiveSkill].iPPlus ) );
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "70(%d,%d,%d,%d), Mind:%d		", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], m_kChakra.sMind );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}
	if( kDamage.irgFire[0] )
	{
		int iPPlus = m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPPlus;
		kDamage.irgFire[0] += Percent( kDamage.irgFire[0], iPPlus );
		kDamage.irgFire[1] += Percent( kDamage.irgFire[1], iPPlus );
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "71. Fire Variation(%d,%d,%d), Damage(%d,%d) ", m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPPlus, m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPPlus, kDamage.irgFire[0], kDamage.irgFire[1] );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}
	if( kDamage.irgCold[0] )
	{
		int iPPlus = m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPPlus;
		kDamage.irgCold[0] += Percent( kDamage.irgCold[0], iPPlus );
		kDamage.irgCold[1] += Percent( kDamage.irgCold[1], iPPlus );
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "72. Cold Variation(%d,%d,%d), Damage(%d,%d) ", m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPPlus, m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPPlus, kDamage.irgCold[0], kDamage.irgCold[1] );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}
	if( kDamage.irgLightning[0] )
	{
		int iPPlus = m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPPlus;
		kDamage.irgLightning[0] += Percent( kDamage.irgLightning[0], iPPlus );
		kDamage.irgLightning[1] += Percent( kDamage.irgLightning[1], iPPlus );
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "73. Cold Variation(%d,%d,%d), Damage(%d,%d) ", m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPPlus, m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPPlus, kDamage.irgCold[0], kDamage.irgCold[1] );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}
	//if( kDamage.irgPoison[0] )
	{
		int iPPlus = m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPPlus;
		kDamage.irgPoison[0] += Percent( kDamage.irgPoison[0], iPPlus );
		kDamage.irgPoison[1] += Percent( kDamage.irgPoison[1], iPPlus );
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "74. Poison Variation(%d,%d,%d), Damage(%d,%d) ", m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPPlus, m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPPlus, kDamage.irgPoison[0], kDamage.irgPoison[1] );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}

	//------------------------- +/- Áõ°¨ -----------------------------------------
	if( 0 < kDamage.irgPhy[0] )
	{	
		kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPlus;
		kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPlus;
		kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPlus;
		kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPlus;
	}
	if( 0 < kDamage.irgFire[0] )
	{
		kDamage.irgFire[0] += m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPlus;
		kDamage.irgFire[1] += m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPlus;
		kDamage.irgFire[0] += m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgFire[1] += m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgFire[0] += (m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_FireDamage][eVar_Potion].iPlus*/);
		kDamage.irgFire[1] += (m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_FireDamage][eVar_Potion].iPlus*/);
	}
	if( 0 < kDamage.irgCold[0] )
	{
		kDamage.irgCold[0] += m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPlus;
		kDamage.irgCold[1] += m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPlus;
		kDamage.irgCold[0] += m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgCold[1] += m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgCold[0] += (m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_ColdDamage][eVar_Potion].iPlus*/);
		kDamage.irgCold[1] += (m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_ColdDamage][eVar_Potion].iPlus*/);
	}
	if( 0 < kDamage.irgLightning[0] )
	{
		kDamage.irgLightning[0] += m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPlus;
		kDamage.irgLightning[1] += m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPlus;
		kDamage.irgLightning[0] += m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgLightning[1] += m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgLightning[0] += (m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_LightningDamage][eVar_Potion].iPlus*/);
		kDamage.irgLightning[1] += (m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_LightningDamage][eVar_Potion].iPlus*/);
	}
	//if( 0 < kDamage.irgPoison[0] )
	{
		kDamage.irgPoison[0] += m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPlus;
		kDamage.irgPoison[1] += m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPlus;
		kDamage.irgPoison[0] += m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgPoison[1] += m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPlus;
		kDamage.irgPoison[0] += (m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_PoisonDamage][eVar_Potion].iPlus*/);
		kDamage.irgPoison[1] += (m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_PoisonDamage][eVar_Potion].iPlus*/);
	}


	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t80(%d,%d,%d,%d), Variation(Min:+:%d,%%:%d, +:%d,%%:%d  Max:+:%d,%%:%d, +:%d,%%:%d) \r\n", kDamage.irgPhy[0], kDamage.irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPlus, m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPPlus );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	m_krgDamage[iHand] = kDamage;

	if( eHnd_Left == iHand ) // ¿Þ¼Õ¹«±âÀÌ¶ó¸é È¿À²¼ºÀÌ Á¤ÀÇµÇ¾î ÀÖÀ» °ÍÀÌ´Ù.
	{
		// °è»êµÈ damage¸¦  %·Î Àç °è»êÇÑ´Ù.
		int iPercent = m_krgMastery[eWpnMtryIdx_DualWpn].iParam2;
		m_krgDamage[eHnd_Left].irgPhy[0] = Percent( m_krgDamage[eHnd_Left].irgPhy[0], iPercent );
		m_krgDamage[eHnd_Left].irgPhy[1] = Percent( m_krgDamage[eHnd_Left].irgPhy[1], iPercent );
		m_krgDamage[eHnd_Left].irgPierce[0] = Percent( m_krgDamage[eHnd_Left].irgPierce[0], iPercent );
		m_krgDamage[eHnd_Left].irgPierce[1] = Percent( m_krgDamage[eHnd_Left].irgPierce[1], iPercent );
		m_krgDamage[eHnd_Left].irgFire[0] = Percent( m_krgDamage[eHnd_Left].irgFire[0], iPercent );
		m_krgDamage[eHnd_Left].irgFire[1] = Percent( m_krgDamage[eHnd_Left].irgFire[1], iPercent );
		m_krgDamage[eHnd_Left].irgCold[0] = Percent( m_krgDamage[eHnd_Left].irgCold[0], iPercent );
		m_krgDamage[eHnd_Left].irgCold[1] = Percent( m_krgDamage[eHnd_Left].irgCold[1], iPercent );
		m_krgDamage[eHnd_Left].irgLightning[0] = Percent( m_krgDamage[eHnd_Left].irgLightning[0], iPercent );
		m_krgDamage[eHnd_Left].irgLightning[1] = Percent( m_krgDamage[eHnd_Left].irgLightning[1], iPercent );
		m_krgDamage[eHnd_Left].irgPoison[0] = Percent( m_krgDamage[eHnd_Left].irgPoison[0], iPercent );
		m_krgDamage[eHnd_Left].irgPoison[1] = Percent( m_krgDamage[eHnd_Left].irgPoison[1], iPercent );
	}

	m_krgDamage[iHand].irgBase[0] = m_krgDamage[iHand].irgPhy[0];
	m_krgDamage[iHand].irgBase[1] = m_krgDamage[iHand].irgPhy[1];

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateDamage] WeaponIIndex:%d, Phy:%d~%d, Pierce:%d~%d, Fire:%d~%d, Cold:%d~%d, Lightning:%d~%d, Poison:%d~%d, class1:%d, class2:%d, WeaponCoefficient:%d, masteryIndex:%d, mastery+:%d Variation(Min:+:%d,%:%d,Max:+:%d,%:%d)\r\n"
			, iWeaponIndex, m_krgDamage[eHnd_Right].irgPhy[0], m_krgDamage[eHnd_Right].irgPhy[1], kDamage.irgPierce[0], kDamage.irgPierce[1], m_krgDamage[eHnd_Right].irgFire[0], m_krgDamage[eHnd_Right].irgFire[1], m_krgDamage[eHnd_Right].irgCold[0], m_krgDamage[eHnd_Right].irgCold[1], m_krgDamage[eHnd_Right].irgLightning[0], m_krgDamage[eHnd_Right].irgLightning[1], m_krgDamage[eHnd_Right].irgPoison[0], m_krgDamage[eHnd_Right].irgPoison[1], MOB.byClass1, MOB.byClass2, m_iWeaponCoefficient, iMasterIndex, m_krgMastery[iMasterIndex].iParam1
			, m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPPlus);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif // __TN_3RD_LOG__
}



void CMob::UpdateSpeed()
{
	if( eTNMob_PC == m_eMobType )
	{
		m_iMoveSpeed = eTNChr_MoveSpeed;
		if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) ) m_iMoveSpeed = eTNChr_DevaMvSpeed;
		if( eTNClan_GM == m_byClan ) m_iMoveSpeed = eTNChr_GMMvSpeed;
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		if( MOB_COMBAT == Mode || MOB_FLEE == Mode ) m_iMoveSpeed = pMonsterData[MOB.nTP].byQuest[eMonPrty_RunSpeed];
		else if( eTNCls_Follower == MOB.byClass1 ) m_iMoveSpeed = pMonsterData[MOB.nTP].byQuest[eMonPrty_RunSpeed];
		else m_iMoveSpeed = pMonsterData[MOB.nTP].byQuest[eMonPrty_WalkSpeed];
	}

	//if( !(eTNVSAfn_Invisible & m_iAffections) ) // Åõ¸íÀÌ ¾Æ´Ï¶ó¸é, ...
	{
		//m_iMoveSpeed += Percent( m_iMoveSpeed, (m_krgVariation[eTNVar_MoveSpeed][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_Skill].iPPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_Potion].iPPlus) );
		m_iMoveSpeed += ( m_iMoveSpeed * (m_krgVariation[eTNVar_MoveSpeed][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_Skill].iPPlus) ) / 100;
		m_iMoveSpeed += (m_krgVariation[eTNVar_MoveSpeed][eVar_Equipment].iPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_MoveSpeed][eVar_Skill].iPlus);
	}

	if( 1 > m_iMoveSpeed ) m_iMoveSpeed = 1;

	if( eTNVSAfn_DontMove & m_iAffections) m_iMoveSpeed = 0;
	//if( eTNVSAfn_Hold & m_iAffections) m_iMoveSpeed = 1;

	#ifdef __TN_PLAYMOVIE__
	if( 0 < g_irgFlag[1] ) m_iMoveSpeed = g_irgFlag[1];
	#endif

	if( eTNMob_NPC == m_eMobType ) return;  // monster´Â ¹«±â°¡ ¾øÀ¸¹Ç·Î ÇÊ¿ä¾ø´Ù.

	short iIndex = get_WeaponIndex();
	int iAttackSpeed = pItemData[iIndex].iAttackSpeed;
	iAttackSpeed -= Percent( iAttackSpeed, (m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPPlus) ); 
	iAttackSpeed -= (m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPlus );

	if( g_irgSetting[eCnst_SpeedMin] > iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMin];
	else if( g_irgSetting[eCnst_SpeedMax] < iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMax];

	m_iAttackSpeed = iAttackSpeed;

	//m_iAttackSpeed -= Percent( m_iAttackSpeed, (m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPPlus /*+ m_krgVariation[eTNVar_AttackSpeed][eVar_Potion].iPPlus*/) ) ;
	//m_iAttackSpeed -= (m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPlus);

	//if( eSpd_Min > m_iAttackSpeed ) m_iAttackSpeed = eSpd_Min;
	//else if( eSpd_Max < m_iAttackSpeed ) m_iAttackSpeed = eSpd_Max;

	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateSpeed] Move: %d, +(%d,%d,%d), %%:%d, %%:%d, %%:%d, Attack: %d, +(%d,%d,%d), %%:%d, %%:%d, %%:%d, weaponIndex:%d \r\n", m_iMoveSpeed, m_krgVariation[eTNVar_MoveSpeed][eVar_Equipment].iPlus, m_krgVariation[eTNVar_MoveSpeed][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_MoveSpeed][eVar_Skill].iPlus, m_krgVariation[eTNVar_MoveSpeed][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_MoveSpeed][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_MoveSpeed][eVar_Skill].iPPlus, m_iAttackSpeed, m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPlus, m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPlus, m_krgVariation[eTNVar_AttackSpeed][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_AttackSpeed][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_AttackSpeed][eVar_Skill].iPPlus, iIndex );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
}



// a_bApplyBonus´Â false¸¦ default·Î °¡Áø´Ù. ¸ó½ºÅÍ »ç³É½Ã¿¡¸¸ bonus¸¦ ¹Þ´Â´Ù.
void CMob::AcquirePrana( int a_iRewardPrana, bool a_bApplyBonus )
{
	int iPrevPrana = MOB.nPrana;

	double dPercent = 100;
	if( a_bApplyBonus ) dPercent += (m_krgVariation[eTNVar_PranaBonus][eVar_PassiveSkill].iPPlus + m_krgVariation[eTNVar_PranaBonus][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_PranaBonus][eVar_Skill].iPPlus );
	int iPranaToIncrease = Percent( a_iRewardPrana, dPercent );

	IncPrana( iPranaToIncrease );

	//#ifdef __TN_2ND_LOG__
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[AcquirePrana] Prana:%d(%d,%d) È¹µæÇØ¼­ ÃÑ Prana:%d/%d, PranaBonus(%d/%d/%d)\r\n", iPranaToIncrease, a_iRewardPrana, dPercent, MOB.nPrana, m_iMaxPrana
			, m_krgVariation[eTNVar_PranaBonus][eVar_PassiveSkill].iPPlus, m_krgVariation[eTNVar_PranaBonus][eVar_Equipment].iPPlus, m_krgVariation[eTNVar_PranaBonus][eVar_Skill].iPPlus
			);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	if( m_iMaxPrana <= MOB.nPrana )
	{
		if( TN_MAX_LEVEL <= MOB.byLevel )
		{
			NotifyUpdateStatusMsg();			
			return;
		}
		int iPranaRested = iPranaToIncrease - (m_iMaxPrana - iPrevPrana);
		LevelUp();
		AcquirePrana( iPranaRested );
	}
	else NotifyUpdateStatusMsg();
}



void CMob::LevelUp()
{
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return;
	if( TN_MAX_LEVEL <= MOB.byLevel )
	{
		MOB.byLevel = TN_MAX_LEVEL;
		return;
	}

	++MOB.byLevel;
	CalChakra();
	//int iSumChakraModified = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
	//int iPlusChakra = 0;
	//if( 0 < MOB.byClass1 ) iPlusChakra = (MOB.byLevel/10)*3; // 10·¦´ç 3¾¿ Ãß°¡
	//int iTotalChakra = 50 + (MOB.byLevel - 1)*5 + iPlusChakra;
	//if( 99 < MOB.byLevel )
	//{
	//	int iFactor = ((MOB.byLevel-100)/10);
	//	iTotalChakra = 577/*50 + 495 + 27 + 5*/ + iFactor*(60 + ((iFactor-1)*10)) + (MOB.byLevel-(99+(10*iFactor)))*(6+(iFactor*2));
	//}
	//m_kCPRemaining.set_Cur( iTotalChakra - iSumChakraModified );

	int iSkillPointUsed = 0; 
	for( int i = 0; i < 65; ++i ) iSkillPointUsed += MOB.bySkill[i];
	for( int i = 80; i < MAX_SKILL; ++i ) iSkillPointUsed += MOB.bySkill[i];
	//for( int i = 0; i < MAX_SKILL; ++i ) iSkillPointUsed += MOB.bySkill[i];
	int iPlusSkillPoint = 0;
	if( 1 < MOB.byClass1 ) iPlusSkillPoint = ((MOB.byLevel-35)/10)*2; // 45·¦ºÎÅÍ 10·¦´ç 2¾¿ Ãß°¡
	int iTotalSkillPoint = MOB.byLevel + iPlusSkillPoint;
	int iSPRemaining = iTotalSkillPoint - iSkillPointUsed;
	if( 0 > iSPRemaining ) iSPRemaining = 0;
	m_kSPRemaining.set_Cur( iSPRemaining );
	int iLevel = MOB.byLevel;
	m_iMaxPrana = g_irgLevelUp[iLevel-1];
	MOB.nPrana = 0;

	MOB.nHP = m_iMaxHP;
	MOB.nTP = m_iMaxTP;

	UpdateEquipmentPoints();

	{
		char chBuf[256] = { 0, 0, 0, };
		sprintf( chBuf, "lev %s Level:%d, Chakra(%d,%d,%d,%d), Brahman(%d) rupiah:%d cargo:%d", MOB.szName, MOB.byLevel, MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind, MOB.nBramanPoint, MOB.nRupiah, pUser[m_iHandle].Coin );
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
	}

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[LevelUp] Çö level: %d, ·¦¾÷ Prana¿ä±¸Ä¡: %d, CPRemaining: %d, SPRemaining: %d \r\n", MOB.byLevel, m_iMaxPrana, m_kCPRemaining.get_Cur(), m_kSPRemaining.get_Cur() );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
	//fors_debug ÐÂÊÖËÍ×°±¸
   if (MOB.byLevel==10) 
	{
		if (IsGivedLevelUpReWard(MOB.szName,10))
		{
		char chBuf[256] = { 0,0,0, };
	int iTribe = MOB.snTribe;
	if( (TRIBE_NAGA==iTribe) || (TRIBE_KINNARA==iTribe) ) 
	{
GmGive5Item(m_iHandle, 5042, 1);
GmGive5Item(m_iHandle, 5315, 1);
GmGive5Item(m_iHandle, 5187, 1);
GmGive5Item(m_iHandle, 5437, 1);
GmGive5Item(m_iHandle, 5608, 1);
GmGive5Item(m_iHandle, 4352, 1);	
	}
	else if( (TRIBE_ASURA==iTribe) || (TRIBE_RAKSHASA==iTribe) ) 
	{
GmGive5Item(m_iHandle, 5043, 1);
GmGive5Item(m_iHandle, 5188, 1);
GmGive5Item(m_iHandle, 5316, 1);
GmGive5Item(m_iHandle, 5438, 1);
GmGive5Item(m_iHandle, 5609, 1);
GmGive5Item(m_iHandle, 4611, 1);
GmGive5Item(m_iHandle, 4061, 1);	
	}
	else if( (TRIBE_YAKSA==iTribe) || (TRIBE_GANDHARVA==iTribe) ) 
	{
GmGive5Item(m_iHandle, 5044, 1);
GmGive5Item(m_iHandle, 5189, 1);
GmGive5Item(m_iHandle, 5317, 1);
GmGive5Item(m_iHandle, 5439, 1);
GmGive5Item(m_iHandle, 5610, 1);
GmGive5Item(m_iHandle, 4353, 1);
GmGive5Item(m_iHandle, 4064, 1);	
	}
	else if( (TRIBE_DEVA==iTribe) || (TRIBE_GARUDA==iTribe) ) 
	{
GmGive5Item(m_iHandle, 5045, 1);
GmGive5Item(m_iHandle, 5190, 1);
GmGive5Item(m_iHandle, 5318, 1);
GmGive5Item(m_iHandle, 5611, 1);
GmGive5Item(m_iHandle, 5440, 1);
GmGive5Item(m_iHandle, 4424, 1);
GmGive5Item(m_iHandle, 4125, 1);


	
	}

        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
		}
	}

//fors_debug to_give_level_up item Éý¼¶½±Àø
    if (MOB.byLevel==110) 
	{
		IsReachCallLevel(pUser[m_iHandle].AccountName,MOB.szName,110);
		if (IsGivedLevelUpReWard(MOB.szName,110))
		{
		char chBuf[256] = { 0,0,0, };

        GiveItem(m_iHandle, 7031, 20);
		GiveItem(m_iHandle, 7068, 1250);

        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
		}
	}
    if (MOB.byLevel==120) 
	{
		if (IsGivedLevelUpReWard(MOB.szName,120))
		{
		char chBuf[256] = { 0,0,0, };

        GiveItem(m_iHandle, 7039, 20);
		GiveItem(m_iHandle, 7070, 2500);

        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
		}
	}
    if (MOB.byLevel==130) 
	{
		if (IsGivedLevelUpReWard(MOB.szName,130))
		{
		char chBuf[256] = { 0,0,0, };

        GiveItem(m_iHandle, 7065, 1);
		GiveItem(m_iHandle, 7038, 20);

        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
		}
	}
    if (MOB.byLevel==140) 
	{
		if ( IsGivedLevelUpReWard(MOB.szName,140) && (MOB.byQuest[98] != 255))
		{
		char chBuf[256] = { 0,0,0, };

        GiveItem(m_iHandle, 6505, 5);
		GiveItem(m_iHandle, 6507, 5);
        MOB.byQuest[98] = 255;
        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
		}
	}
   if (MOB.byLevel==140) 
{
		if ( IsGivedReachReWard(MOB.szName,140) && (MOB.byQuest[99] != 255)) //fors_debug ½«140µÄÔùËÍ×°±¸·ÅÁíÍâÒ»¸öÄ¿Â¼
		{
		char chBuf[256] = { 0,0,0, };
	int iTribe = MOB.snTribe;
	if( (TRIBE_NAGA==iTribe) || (TRIBE_KINNARA==iTribe) )  //fors_debug GmGive9Item»¹ÒªÅªÒ»¸ö+9µÄ
	{
GmGive9Item(m_iHandle, 5046, 1);
GmGive9Item(m_iHandle, 5191, 1);
GmGive9Item(m_iHandle, 5319, 1);
GmGive9Item(m_iHandle, 5441, 1);
GmGive9Item(m_iHandle, 5612, 1);
GiveItem(m_iHandle, 4371, 1);	
	}
	else if( (TRIBE_ASURA==iTribe) || (TRIBE_RAKSHASA==iTribe) ) 
	{

GmGive9Item(m_iHandle, 5047, 1);
GmGive9Item(m_iHandle, 5192, 1);
GmGive9Item(m_iHandle, 5320, 1);
GmGive9Item(m_iHandle, 5442, 1);
GmGive9Item(m_iHandle, 5613, 1);
	if (MOB.byClass2 ==3 )
GiveItem(m_iHandle, 4614, 1);
else if (MOB.byClass2 ==2 ) GiveItem(m_iHandle, 4074, 1);
	
	}
	else if( (TRIBE_YAKSA==iTribe) || (TRIBE_GANDHARVA==iTribe) ) 
	{
GmGive9Item(m_iHandle, 5048, 1);
GmGive9Item(m_iHandle, 5193, 1);
GmGive9Item(m_iHandle, 8306, 1);
GmGive9Item(m_iHandle, 5443, 1);
GmGive9Item(m_iHandle, 5614, 1);
GiveItem(m_iHandle, 4370, 1);
	}
	else if( (TRIBE_DEVA==iTribe) || (TRIBE_GARUDA==iTribe) ) 
	{
GmGive9Item(m_iHandle, 5049, 1);
GmGive9Item(m_iHandle, 5194, 1);
GmGive9Item(m_iHandle, 8307, 1);
GmGive9Item(m_iHandle, 5444, 1);
GmGive9Item(m_iHandle, 5615, 1);
GiveItem(m_iHandle, 4128, 1);

	
	}
	MOB.byQuest[99] = 255;
	        sprintf( chBuf, "[LevelUp] %s giveReWard %d level give", MOB.szName, MOB.byLevel);
		Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

		//char chBuf[256] = {0,}; 
		sprintf(chBuf, g_pMessageStringTable[_Billing_Remain_Time], MOB.byLevel);
		SendClientMessage(m_iHandle, chBuf);
	}
	
}


//ok....
	S_SCP_LEVEL_UP_BROADCAST kMsg;
	kMsg.wType = SCP_LEVEL_UP_BROADCAST;
	kMsg.wPDULength = WORD(sizeof(S_SCP_LEVEL_UP_BROADCAST)-sizeof(HEADER));
	kMsg.dwKeyID = m_iHandle;
	kMsg.byLevel = MOB.byLevel; //m_kLevel.get_Cur();

	GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&kMsg, -1, 30 );
	//pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_LEVEL_UP_BROADCAST));

#ifdef __EVENT_LOG_GENERATION_
	if( MOB.byLevel >= 30 && MOB.byLevel % 10 == 0 )
	{
		char chBuf[256];
		time_t tTime = time(0);
		sprintf(chBuf, "Play,%d,%d,%d",tTime-pUser[m_iHandle].LoginTime,MOB.byLevel,MOB.snTribe);
		EventLog(chBuf, pUser[m_iHandle].AccountName, MOB.szName, pUser[m_iHandle].IP);
		pUser[m_iHandle].LoginTime = tTime;
	}
#endif

	NotifyUpdateUIMsg();
	SaveUser(m_iHandle,0); //auto_save

	//	±æµå¿øµé¿¡°Ô ·¹º§¾÷À» Àü¼ÛÇÑ´Ù.
	DBUpdateGuildMember(m_iHandle);

}


void CMob::IncChakra( int a_iState )
{
	if( m_kCPRemaining.IsZero() ) return;

	switch( a_iState )
	{
	case eStt_Str :
		{
			++MOB.sMuscle;
			m_kCPRemaining.Dec(1);
		}
		break;
	case eStt_Dex :
		{
			++MOB.sNerves;
			m_kCPRemaining.Dec(1);
		}
		break;
	case eStt_Vital :
		{
			++MOB.sHeart;
			m_kCPRemaining.Dec(1);
/*
			if( g_irgSetting[eCnst_HeartMax] <= MOB.sHeart ) 
			{
				MOB.sHeart = g_irgSetting[eCnst_HeartMax];
				SendClientMessage( m_iHandle, g_pMessageStringTable[_HeartRestricted] );				
			}
			else
			{
				++MOB.sHeart;
				m_kCPRemaining.Dec(1);
			}
*/
		}
		break;
	case eStt_Energy :
		{
			++MOB.sMind;
			m_kCPRemaining.Dec(1);
		}
		break;
	}

/*	
	switch( a_iState )
	{
	case eStt_Str :
		++MOB.sMuscle;
		m_kCPRemaining.Dec(1);
		break;
	case eStt_Dex :
		++MOB.sNerves;
		m_kCPRemaining.Dec(1);
		break;
	case eStt_Vital :
		{
			int iMaxChakra = MOB.byLevel*2 + 100;
			if( iMaxChakra > MOB.sHeart )
			{
				++MOB.sHeart;
				m_kCPRemaining.Dec(1);
			}
			//++MOB.sHeart;
		}
		break;
	case eStt_Energy :
		++MOB.sMind;
		m_kCPRemaining.Dec(1);
		break;
	}
*/

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[IncChakra] Çö level: %d, m_kCPRemaining: %d, SPRemaining: %d, chakra(%d,%d,%d,%d) \r\n", MOB.byLevel, m_kCPRemaining.get_Cur(), m_kSPRemaining.get_Cur(), MOB.sMuscle, MOB.sNerves, MOB.sHeart, MOB.sMind );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	UpdatePoints();
	NotifyUpdateUIMsg();
}


void CMob::NotifyUpdateUIMsg()
{
	if( eTNMob_PC != m_eMobType ) return;

	S_SCP_RESP_UPDATE_UI kMsg;
	kMsg.wType = SCP_RESP_UPDATE_UI;
	kMsg.snX = TargetX;
	kMsg.snZ = TargetY;
	kMsg.byLevel = MOB.byLevel;//  m_kLevel.get_Cur();	
	kMsg.iBramanPoint = MOB.nBramanPoint;
	kMsg.byCaste = (byte)m_iCaste;
	kMsg.iTitle = 0;
	kMsg.krgChakra[0].snMuscle = MOB.sMuscle;
	kMsg.krgChakra[0].snNerves = MOB.sNerves;
	kMsg.krgChakra[0].snHeart = MOB.sHeart;
	kMsg.krgChakra[0].snMind = MOB.sMind;
	kMsg.krgChakra[1].snMuscle = m_kChakra.sMuscle;
	kMsg.krgChakra[1].snNerves = m_kChakra.sNerves;
	kMsg.krgChakra[1].snHeart = m_kChakra.sHeart;
	kMsg.krgChakra[1].snMind = m_kChakra.sMind;
	//kMsg.snCPRemaining = MOB.sRemaining;
	kMsg.snCPRemaining = (short)m_kCPRemaining.get_Cur();
	kMsg.snSPRemaining = (short)m_kSPRemaining.get_Cur();
	kMsg.snCasteSPRemaining = (short)m_kCasteSPRemaining.get_Cur();
	kMsg.byClass1 = MOB.byClass1;
	kMsg.byClass2 = MOB.byClass2;
	kMsg.iPrana = MOB.nPrana;
	kMsg.iMaxPrana = m_iMaxPrana;
	kMsg.iHP = MOB.nHP;
	kMsg.iMaxHP = m_iMaxHP;
	kMsg.iHPRecovery = m_irgHPRecovery[1];
	kMsg.iTP = MOB.nTP;
	kMsg.iMaxTP = m_iMaxTP;
	kMsg.iTPRecovery = m_irgTPRecovery[1];
	kMsg.snAC = m_kCombatFactors.iDefense;
	kMsg.snAttackRate = m_kCombatFactors.iAttackRate;
	kMsg.snDodgeRate = m_kCombatFactors.iDodgeRate;
	kMsg.kResist.snFire = m_kCombatFactors.irgResist[eRst_Fire];
	kMsg.kResist.snCold = m_kCombatFactors.irgResist[eRst_Cold];
	kMsg.kResist.snLightning = m_kCombatFactors.irgResist[eRst_Lightning];
	kMsg.kResist.snPoison = m_kCombatFactors.irgResist[eRst_Poison];
//	kMsg.iMoveSpeed = m_iMoveSpeed; //fors_debug check speed msg here movespeed
	//kMsg.iAttackSpeed = m_iAttackSpeed; // °ø¼Ó º¯È­ ¼öÄ¡°¡ Àû¿ëµÈ °ª
	//kMsg.snAttackVariation = 10; // ¹«±â »ç¿ë skill °ø¼Ó º¯È­ ¼öÄ¡
	//kMsg.snCastVariation = 20; // ¹«±â ¹Ì»ç¿ë ½Ã skill °ø¼Ó º¯È­ ¼öÄ¡
	kMsg.iGold = MOB.nRupiah;

	kMsg.kDamage.iMin = m_krgDamage[eHnd_Right].irgPhy[0] + m_krgDamage[eHnd_Right].irgPierce[0];
	kMsg.kDamage.iMax = m_krgDamage[eHnd_Right].irgPhy[1] + m_krgDamage[eHnd_Right].irgPierce[1];
	kMsg.kDamage.iFire = m_krgDamage[eHnd_Right].irgFire[0];
	kMsg.kDamage.iCold = m_krgDamage[eHnd_Right].irgCold[0];
	kMsg.kDamage.iLightning = m_krgDamage[eHnd_Right].irgLightning[0];
	kMsg.kDamage.iPoison = m_krgDamage[eHnd_Right].irgPoison[0];

	char byteSpeed = (char)m_iMoveSpeed; // °ªÀÇ ¹üÀ§´Â 4ºÎÅÍ 25 »çÀÌÁ¤µµ·Î °¡Á¤ÇÑ´Ù.
	int iAttackSpeed = m_iAttackSpeed;	// °ªÀº ´ë·« 500ºÎÅÍ 3000 »çÀÌÀÇ °ªÀÌ´Ù.

	//if(m_iMoveSpeed<0 || m_iMoveSpeed>25)
	//{
	//	char chBuf[128] = { 0,0,0, };
	//	sprintf(chBuf, "invalid Data char:%s, movespeed:%d \r\n", MOB.szName, m_iMoveSpeed );
	//	WriteLog( chBuf, ".\\Log\\[Log]Update_ui.txt" );
	//}

	char byteTemp = (char)(byteSpeed / 3.0f); // ÀÌ°ªÀº 1ºÎÅÍ 8±îÁöÀÇ °ªÀÌ´Ù.

	kMsg.byteSpeed1 = byteTemp + 104;
	kMsg.byteSpeed2 = byteTemp + 15;
	kMsg.byteSpeed3 = byteTemp + 74;

	kMsg.byteSpeedCorrection = byteSpeed - byteTemp*3; // ÀÌ °ªÀÇ ¹üÀ§´Â 0ºÎÅÍ 2±îÁöÀÇ °ªÀÌ µÇ°Ú´Ù.
	kMsg.byteSpeedCorrection ^= 0xFF;

	kMsg.byteSpeedParity = 0;
	for ( char i = 0; i < 7; ++i )	// ÀÌ¼ÓÀÌ 25¸¦ ³ÑÁö ¾Ê´Â´Ù°í °¡Á¤
		kMsg.byteSpeedParity += (( byteSpeed & (1<<i) ) != 0);

	kMsg.byteAS1 = (char)((iAttackSpeed & 0xC00) >> 10) + 26;
	kMsg.byteAS2 = (char)((iAttackSpeed & 0x380) >> 7) + 61;
	kMsg.byteAS3 = (char)((iAttackSpeed & 0x70) >> 4) + 27;
	kMsg.byteAS4 = (char)(iAttackSpeed & 0xF) +15;

	kMsg.byteParity = 0;
	for ( char i = 0; i < 15; ++i )
		kMsg.byteParity += ((iAttackSpeed & (1 << i)) != 0);

	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_RESP_UPDATE_UI));
//fors_debug log speed info here
//sprintf( temp, "log speed m_iMoveSpeed:%d,bytetemp:%d,byspeed1:%d,byspeed2:%d,byspeed3:%d,byteSpeedCorrection:%d ",m_iMoveSpeed,(int)(kMsg.byteSpeed1),(int)(kMsg.byteSpeed2),(int)(kMsg.byteSpeed3),(int)(kMsg.byteSpeedCorrection));
//Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

	#ifdef __TN_5TH_LOG__
	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[NotifyUpdateUIMsg] handle:%d, Prana:%d, HP:%d, TP:%d, Affection:%u \r\n", m_iHandle, kMsg.iPrana, kMsg.iHP, kMsg.iTP, m_iAffections );
		WriteLog( chBuf, ".\\Monster_Log\\[Log]test.txt" );
	}
	#endif

	#ifdef __TN_2ND_LOG__
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );

		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\r\n[NotifyUpdateUIMsg] %d½Ã%dºÐ%dÃÊ> User:%d, L(%d,%d), Mv:%d, Atk:%d, Level:%d, Braman:%d, Karma:%d Caste:%d, Title:%d, BaseChakra(%d,%d,%d,%d)/Changed(%d,%d,%d,%d)\r\n	\
					   ³²ÀºCP:%d, ³²ÀºSP:%d, Prana:%d/%d, Gold:%d, HP:%d/%d(%d), TP:%d/%d(%d), AC:%d, AR:%d, DG:%d, Resist(%d,%d,%d,%d), Damage(%d~%d, %d/%d/%d/%d), »ýÁ¸»óÅÂ:%d(-1:Dead, else Alive) \r\n"
, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_iHandle, kMsg.snX, kMsg.snZ, kMsg.iMoveSpeed, kMsg.iAttackSpeed, kMsg.byLevel, kMsg.iBramanPoint, MOB.snKarma, kMsg.byCaste, kMsg.iTitle
			, kMsg.krgChakra[0].snMuscle, kMsg.krgChakra[0].snNerves, kMsg.krgChakra[0].snHeart, kMsg.krgChakra[0].snMind
			, kMsg.krgChakra[1].snMuscle, kMsg.krgChakra[1].snNerves, kMsg.krgChakra[1].snHeart, kMsg.krgChakra[1].snMind
			, kMsg.snCPRemaining, kMsg.snSPRemaining, kMsg.iPrana, kMsg.iMaxPrana, kMsg.iGold, kMsg.iHP, kMsg.iMaxHP, kMsg.iHPRecovery, kMsg.iTP, kMsg.iMaxTP, kMsg.iTPRecovery
			, kMsg.snAC, kMsg.snAttackRate, kMsg.snDodgeRate, kMsg.kResist.snFire, kMsg.kResist.snCold, kMsg.kResist.snLightning, kMsg.kResist.snPoison
			, kMsg.kDamage.snMin, kMsg.kDamage.snMax, kMsg.kDamage.snFire, kMsg.kDamage.snCold, kMsg.kDamage.snLightning, kMsg.kDamage.snPoison
			, m_eFSM
			);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif // #ifdef __TN_2ND_LOG__
}


void CMob::NotifyUpdateStatusMsg( bool a_bCheckTime )
{
	if( eTNMob_PC != m_eMobType ) return;
	if( a_bCheckTime && (m_kLastTime.uiCombat > CurrentTime) ) return;
	m_kLastTime.uiCombat = 0;

	S_SCP_RESP_UPDATE_STATUS kMsg;
	kMsg.wType = SCP_RESP_UPDATE_STATUS;
	//kMsg.  = sizeof( S_SCP_RESP_UPDATE_STATUS );
	kMsg.snKeyID = (short)m_iHandle;
	kMsg.iHP = MOB.nHP;
	kMsg.iTP = MOB.nTP;
	kMsg.iPrana = MOB.nPrana;
	kMsg.iAffections = m_iAffections ;
	kMsg.snKarma = MOB.snKarma;

	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_RESP_UPDATE_STATUS));
	for( int i = 0; i < MAX_PARTY; ++i )
	{
		if( 0 == m_irgParty[i] ) continue;
		if( 0 < m_irgParty[i] && m_irgParty[i] < MAX_USER ) pUser[m_irgParty[i]].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_RESP_UPDATE_STATUS));
	}	

	#ifdef __TN_5TH_LOG__
	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[NotifyUpdateStatusMsg] handle:%d, Prana:%d, HP:%d, TP:%d, Affections:%u, Karma:%d\r\n", m_iHandle, kMsg.iPrana, kMsg.iHP, kMsg.iTP, kMsg.iAffections, kMsg.snKarma );
		WriteLog( chBuf, ".\\Monster_Log\\[Log]test.txt" );
	}
	#endif

	#ifdef __TN_3RD_LOG__
	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[NotifyUpdateStatusMsg] Prana:%d, HP:%d, TP:%d, Affections:%u, Karma:%d\r\n", kMsg.iPrana, kMsg.iHP, kMsg.iTP, kMsg.iAffections, kMsg.snKarma );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
}


void CMob::BroadcastUpdateStatusMsg( bool a_bCheckTime )
{
	if( a_bCheckTime && (m_kLastTime.uiCombat > CurrentTime) ) return;
	m_kLastTime.uiCombat = 0;

	S_SCP_RESP_UPDATE_STATUS kMsg;
	kMsg.wType = SCP_RESP_UPDATE_STATUS;
	kMsg.wPDULength = WORD(sizeof(S_SCP_RESP_UPDATE_STATUS)-sizeof(HEADER));
	kMsg.snKeyID = (short)m_iHandle;
	kMsg.iHP = MOB.nHP;
	kMsg.iAffections = m_iAffections ;
	if( eTNMob_PC == m_eMobType )
	{
		kMsg.iTP = MOB.nTP;
		kMsg.iPrana = MOB.nPrana;
		kMsg.snKarma = MOB.snKarma;
	}
	else if( eTNMob_NPC == m_eMobType )
	{
		kMsg.iTP = 0;
		kMsg.iPrana = 0;
		kMsg.snKarma = 0;
	}

	GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&kMsg, -1, 50 );

	#ifdef __TN_5TH_LOG__
	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[BroadcastUpdateStatusMsg] Handle:%d, HP:%d, Affections:%u \r\n", m_iHandle, kMsg.iHP, kMsg.iAffections );
		WriteLog( chBuf, ".\\Monster_Log\\[Log]test.txt" );
	}
	#endif

}

/*
void CMob::BroadcastMotionMsg( int a_iMotion )
{
	S_SCP_CHAR_ACT_BROADCAST kMsg;
	kMsg.wType	=	SCP_CHAR_ACT_BROADCAST;
	kMsg.dwKeyID = m_iHandle;
	kMsg.byAct = (BYTE)a_iMotion;

	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_CHAR_ACT_BROADCAST));
}


void CMob::BroadcastLevelUpMsg()
{

}
*/

int CMob::ApplyItem( STRUCT_ITEM& a_kItem, int a_iEquipmentSlot )
{
	int	iItemDataIndex = a_kItem.snIndex;
	if( 0 >= iItemDataIndex || MAX_ITEM_DATA < iItemDataIndex ) return eTNRes_Failed;

	#ifdef __TN_2ND_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[UpdateEquipmentPoints] À§Ä¡:%d, Àåºñ(ID:%d, Index:%d) Á¾·ù(¹«±â):%d, damage(%d~%d), ³»±¸µµ:%d, ·¦Á¦:%d(mob·¦:%d) \r\n"
			, iEquipIndex, pItemData[iItemDataIndex].sID, iItemDataIndex, pItemData[iItemDataIndex].sItemType
			, pItemData[iItemDataIndex].kDamage.irgPhy[0], pItemData[iItemDataIndex].kDamage.irgPhy[1]
			, MOB.Equip[iEquipIndex].snDurability, pItemData[iItemDataIndex].kReq.byLevel, MOB.byLevel
			);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	if( 0 >= a_kItem.snDurability ) return eTNRes_Failed; // ³»±¸µµ°¡ 0ÀÎ °ÍÀº skip		
	//if( MOB.Equip[iEquipIndex].snDurability > pItemData[MOB.Equip[iEquipIndex].snIndex+4000].sMaxDur ) MOB.Equip[iEquipIndex].snDurability = pItemData[MOB.Equip[iEquipIndex].snIndex+4000].sMaxDur;
	//if( 5 >= pItemData[iItemDataIndex].byLevel ) if( MOB.byLevel < pItemData[iItemDataIndex].kReq.byLevel ) continue; // item lvlÀÌ 5ÀÌÇÏÀÏ¶§, item ·¾Á¦¸¦ µûÁø´Ù.

	
	if( (eTNEqu_Shield == a_iEquipmentSlot) && (eTNWpn_Dagger & pItemData[iItemDataIndex].sItemType) )
	{ // ÀÌµµ·ùÀÌ¸é, ...
		if( 0 >= m_krgMastery[eWpnMtryIdx_DualWpn].iParam1 ) return eTNRes_Failed;
	}

	int iLevelGap = pItemData[iItemDataIndex].kReq.byLevel - MOB.byLevel;
	double dCorrect = 1;
	if( 0 < iLevelGap ) // ¼º´É Á¦ÇÑ
	{
		--iLevelGap;
		iLevelGap /= 6;
		double dPercent = 50 + iLevelGap * 5;
		if( 95 < dPercent ) dPercent = 95;
		dCorrect = dPercent / 100;
	}

	for( int iEffectIndex = 0; iEffectIndex < TN_MAX_EFFECT_COUNT; ++iEffectIndex )
	{
		if( 0 >= pItemData[iItemDataIndex].krgEffect[iEffectIndex].iID ) continue;
		TNEFFECT kEffect = pItemData[iItemDataIndex].krgEffect[iEffectIndex];
		
		if( 1 > dCorrect )
		{
			if( eTNAfn_ACPlus == kEffect.iID ) kEffect.iParam1 -= (int)(kEffect.iParam1*dCorrect);
			else if( eTNAfn_ACMinus == kEffect.iID ) kEffect.iParam1 += (int)(kEffect.iParam1*dCorrect);
		}

		if( eTNWpn_Shield & pItemData[iItemDataIndex].sItemType )
		{
			if( eTNAfn_ACPlus == kEffect.iID ) kEffect.iParam1 = Percent( kEffect.iParam1, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iShield );
			else if( eTNAfn_ACMinus == kEffect.iID ) kEffect.iParam1 = Percent( kEffect.iParam1, g_krgCoefficientByClass[MOB.byClass1][MOB.byClass2].iShield );
		}
		
		AffectEffect( kEffect, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	}

	// Á¦·Ã ¹× ±âÅ¸
	if(	CHTParamIDCheck::HT_bIsItemDefence(pItemData[iItemDataIndex].sID) )	// ¹æ¾î±¸ÀÏ °æ¿ì	
	{
		//---------------------------------------------------------
		// °­È­ Á¦·Ã - ¹æ¾î±¸
		//---------------------------------------------------------
		if( 0 < a_kItem.byRefineLevel )
		{
			int iRefineLevel = a_kItem.byRefineLevel - 1;

			switch( a_iEquipmentSlot )
			{
			case eTNEqu_Helmet :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceHelmet][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceHelmet][eVar_Skill].iPlus;
				break;
			case eTNEqu_Necklace :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceNecklace][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceNecklace][eVar_Skill].iPlus;
				break;
			case eTNEqu_Armor :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceArmor][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceArmor][eVar_Skill].iPlus;
				break;
			case eTNEqu_Belt :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceBelt][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceBelt][eVar_Skill].iPlus;
				break;
			case eTNEqu_Boots :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceBoots][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceBoots][eVar_Skill].iPlus;
				break;
			case eTNEqu_Gloves :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhanceGloves][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhanceGloves][eVar_Skill].iPlus;
				break;
			case eTNEqu_Pants :
				iRefineLevel = iRefineLevel + m_krgVariation[eTNVar_EnhancePants][eVar_Equipment].iPlus + m_krgVariation[eTNVar_EnhancePants][eVar_Skill].iPlus;
				break;
			}

			if( MAX_MAINREFINELEVEL <= iRefineLevel ) iRefineLevel = MAX_MAINREFINELEVEL - 1;
			int iDefenseIndex = 3;
			if( (CHTParamIDCheck::HT_bIsItemDefenceArmor(pItemData[iItemDataIndex].sID)) || (CHTParamIDCheck::HT_bIsItemDefencePants(pItemData[iItemDataIndex].sID)) || (CHTParamIDCheck::HT_bIsItemDefenceShield(pItemData[iItemDataIndex].sID)) ) iDefenseIndex = 2;
			int iAC = g_pRefineTable[iDefenseIndex][iRefineLevel]; // °­È­ Á¦·Ã
			if( 1 > dCorrect ) iAC -= (int)(iAC*dCorrect);
			m_krgVariation[eTNVar_AC][eVar_Equipment].iPlus += iAC; // ³ªÁß¿¡ eTNVar_AC·Î º¯°æÀ» ÇØ¾ßÇÑ´Ù.
		}

		for( int i = 0; i < MAX_SUBMATERIAL; ++i )  // ¼Ó¼º Á¦·Ã
		{	BYTE byTot=a_kItem.bySubRefine[i/2]; BYTE bySubItem=0;
			if(i%2==0)
			{	bySubItem = byTot>>4;	//	»óÀ§4ºñÆ® ¸®µå
			}	else
			{	bySubItem = byTot&0x0F;	//	ÇÏÀ§4ºñÆ® ¸®µå
			} 

			if( 0 == bySubItem ) continue;
			int iSubRefineIndex = (bySubItem + HT_PARAMTYPE_ITEM_REFINE_SUB_START - 1)  - HT_PARAMTYPE_ITEM_START + 1;
			for( int j = 0; j < TN_MAX_EFFECT_COUNT; ++j )
			{
				if( 0 >= pItemData[iSubRefineIndex].krgEffect[j].iID ) continue;
				switch( pItemData[iSubRefineIndex].krgEffect[j].iID )
				{
				case eTNAfn_FireResistPlus :
					m_krgVariation[eTNVar_FireResist][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_ColdResistPlus :
					m_krgVariation[eTNVar_ColdResist][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_LightningResistPlus :
					m_krgVariation[eTNVar_LightningResist][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_PoisonResistPlus :
					m_krgVariation[eTNVar_PoisonResist][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_DodgeRatePlus :  // Çã¸®¶ì¿Í ¹æÆÐÀÏ¶§¸¸
					if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefenceShield(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemCharm(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_DodgeRate][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;					
				case eTNAfn_AttackRatePlus : // Çï¸äÀÏ¶§¸¸
					if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;
				case eTNAfn_MusclePlus :
					m_krgVariation[eTNVar_Muscle][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_NervesPlus :
					m_krgVariation[eTNVar_Nerves][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_HeartPlus :
					m_krgVariation[eTNVar_Heart][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_MindPlus :
					m_krgVariation[eTNVar_Mind][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
/*					case eTNAfn_MusclePlus :
					if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefenceShoes(pItemData[iItemDataIndex].sID) ||
						CHTParamIDCheck::HT_bIsItemDefenceHelmet(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefencePants(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_Muscle][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;
				case eTNAfn_NervesPlus :
					if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefenceShoes(pItemData[iItemDataIndex].sID) ||
						CHTParamIDCheck::HT_bIsItemDefenceHelmet(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefencePants(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_Nerves][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;
				case eTNAfn_HeartPlus :
					if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefenceShoes(pItemData[iItemDataIndex].sID) ||
						CHTParamIDCheck::HT_bIsItemDefenceHelmet(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefencePants(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_Heart][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;
				case eTNAfn_MindPlus :
					if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefenceShoes(pItemData[iItemDataIndex].sID) ||
						CHTParamIDCheck::HT_bIsItemDefenceHelmet(pItemData[iItemDataIndex].sID) || CHTParamIDCheck::HT_bIsItemDefencePants(pItemData[iItemDataIndex].sID) )
					{
						m_krgVariation[eTNVar_Mind][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					}
					break;*/
				}
			}
		}
	}
	else if( CHTParamIDCheck::HT_bIsItemWeapon( pItemData[iItemDataIndex].sID ) )	// ¹«±âÀÏ °æ¿ì		
	{
		if( eTNEqu_Shield == a_iEquipmentSlot ) // ¿Þ¼Õ¹«±â(ÀÌµµ·ù)
		{
			m_bDualWeapon = true;
			UpdateDamage( eTNEqu_Shield );
			/*
			// °è»êµÈ damage¸¦  %·Î Àç °è»êÇÑ´Ù.
			int iPercent = m_krgMastery[eWpnMtryIdx_DualWpn].iParam2;
			m_krgDamage[eHnd_Left].irgPhy[0] = Percent( m_krgDamage[eHnd_Left].irgPhy[0], iPercent );
			m_krgDamage[eHnd_Left].irgPhy[1] = Percent( m_krgDamage[eHnd_Left].irgPhy[1], iPercent );
			m_krgDamage[eHnd_Left].irgFire[0] = Percent( m_krgDamage[eHnd_Left].irgFire[0], iPercent );
			m_krgDamage[eHnd_Left].irgFire[1] = Percent( m_krgDamage[eHnd_Left].irgFire[1], iPercent );
			m_krgDamage[eHnd_Left].irgCold[0] = Percent( m_krgDamage[eHnd_Left].irgCold[0], iPercent );
			m_krgDamage[eHnd_Left].irgCold[1] = Percent( m_krgDamage[eHnd_Left].irgCold[1], iPercent );
			m_krgDamage[eHnd_Left].irgLightning[0] = Percent( m_krgDamage[eHnd_Left].irgLightning[0], iPercent );
			m_krgDamage[eHnd_Left].irgLightning[1] = Percent( m_krgDamage[eHnd_Left].irgLightning[1], iPercent );
			m_krgDamage[eHnd_Left].irgPoison[0] = Percent( m_krgDamage[eHnd_Left].irgPoison[0], iPercent );
			m_krgDamage[eHnd_Left].irgPoison[1] = Percent( m_krgDamage[eHnd_Left].irgPoison[1], iPercent );
			*/

			m_kDualHit.Init( m_krgMastery[eWpnMtryIdx_DualWpn].iParam1 );
		}

		for( int i = 0; i < MAX_SUBMATERIAL; ++i )  // ¼Ó¼º Á¦·Ã
		{	BYTE byTot=a_kItem.bySubRefine[i/2]; BYTE bySubItem=0;
			if(i%2==0)
			{	bySubItem = byTot>>4;	//	»óÀ§4ºñÆ® ¸®µå
			}	else
			{	bySubItem = byTot&0x0F;	//	ÇÏÀ§4ºñÆ® ¸®µå
			} 

			if( 0 == bySubItem ) continue;
			int iSubRefineIndex = (bySubItem + HT_PARAMTYPE_ITEM_REFINE_SUB_START - 1)  - HT_PARAMTYPE_ITEM_START + 1;
			for( int j = 0; j < TN_MAX_EFFECT_COUNT; ++j )
			{
				if( 0 >= pItemData[iSubRefineIndex].krgEffect[j].iID ) continue;
				switch( pItemData[iSubRefineIndex].krgEffect[j].iID )
				{
				case eTNAfn_AttackRatePlus :
					m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_MusclePlus :
					m_krgVariation[eTNVar_Muscle][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_NervesPlus :
					m_krgVariation[eTNVar_Nerves][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_HeartPlus :
					m_krgVariation[eTNVar_Heart][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_MindPlus :
					m_krgVariation[eTNVar_Mind][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				}
			}
		}
	}
	else if( ( HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_START <= pItemData[iItemDataIndex].sID && HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_END >= pItemData[iItemDataIndex].sID ) ) // ¸ñ°ÉÀÌÀÏ °æ¿ì		
	{
		for( int i = 0; i < MAX_SUBMATERIAL; ++i )  // ¼Ó¼º Á¦·Ã
		{	BYTE byTot=a_kItem.bySubRefine[i/2]; BYTE bySubItem=0;
			if(i%2==0)
			{	bySubItem = byTot>>4;	//	»óÀ§4ºñÆ® ¸®µå
			}	else
			{	bySubItem = byTot&0x0F;	//	ÇÏÀ§4ºñÆ® ¸®µå
			} 

			if( 0 == bySubItem ) continue;
			int iSubRefineIndex = (bySubItem + HT_PARAMTYPE_ITEM_REFINE_SUB_START - 1)  - HT_PARAMTYPE_ITEM_START + 1;
			for( int j = 0; j < TN_MAX_EFFECT_COUNT; ++j )
			{
				if( 0 >= pItemData[iSubRefineIndex].krgEffect[j].iID ) continue;
				switch( pItemData[iSubRefineIndex].krgEffect[j].iID )
				{
				case eTNAfn_SaveTPCost :
					m_krgVariation[eTNVar_SaveTPCost][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_HPRecoveryPlus :
					m_krgVariation[eTNVar_HPRecovery][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_TPRecoveryPlus :
					m_krgVariation[eTNVar_TPRecovery][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_MaxHPPlus :
					m_krgVariation[eTNVar_MaxHP][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_MaxTPPlus :
					m_krgVariation[eTNVar_MaxTP][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNAfn_AttackRatePlus :
					m_krgVariation[eTNVar_AttackRate][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				case eTNVar_AbsorbElementalDamage:
					m_krgVariation[eTNVar_AbsorbElementalDamage][eVar_Equipment].iPlus += pItemData[iSubRefineIndex].krgEffect[j].iParam1;
					break;
				}
			}
		}
	}

	return eTNRes_Succeeded;
}


void CMob::UpdateEquipmentPoints()
{
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[UpdateEquipmentPoints] \r\n" );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

	//-----------------------------------------------------------------------------------------
	// ÃÊ±âÈ­
	//-----------------------------------------------------------------------------------------
	m_iImmunity = 0;
	m_bDualWeapon = false;
	for( int i = 0; i < TN_MAX_VARIATION_COUNT; ++i ) m_krgVariation[i][eVar_Equipment].Clear();
	for( int i = 0; i < MAX_SKILL; ++i ) m_krgSkill[i].byLevelPlus  = 0;

	//-----------------------------------------------------------------------------------------
	// ±âº» Àåºñ ¼º´É °è»ê
	//-----------------------------------------------------------------------------------------
	for( int iEquipIndex = 0; iEquipIndex < MAX_EQUIP; ++iEquipIndex ) 
	{
		ApplyItem( MOB.Equip[iEquipIndex], iEquipIndex );
	}
	//Ì××°Ð§¹û fors_debug
    int iTribe = MOB.snTribe;
	if (MOB.byLevel >= 100) {
//sh
if ( MOB.Equip[eTNEqu_Armor].snIndex == 1100  && MOB.Equip[eTNEqu_Gloves].snIndex == 1471  && MOB.Equip[eTNEqu_Pants].snIndex == 1221 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_AllStatePlus ;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 5;
			kEffect1.iParam2 = 0;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}	
//md
if ( MOB.Equip[eTNEqu_Armor].snIndex == 1101  && MOB.Equip[eTNEqu_Gloves].snIndex == 1472  && MOB.Equip[eTNEqu_Pants].snIndex == 1222 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_AllStatePlus ;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 5;
			kEffect1.iParam2 = 0;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}	

	if( (TRIBE_NAGA==iTribe) || (TRIBE_KINNARA==iTribe) )
	{
	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 4332 && MOB.Equip[eTNEqu_Armor].snIndex == 1130 && MOB.Equip[eTNEqu_Boots].snIndex == 4530  && MOB.Equip[eTNEqu_Gloves].snIndex == 4445  && MOB.Equip[eTNEqu_Pants].snIndex == 4205 )		
	{
			TNEFFECT kEffect1,kEffect2;
			kEffect1.iID = eTNAfn_ACPlus;
			kEffect1.kFunc.iData = 0;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 300;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_AbsorbDamage ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 30;
			kEffect2.iParam2 = 0;	
			
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
        AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );	
	}

	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 1391 && MOB.Equip[eTNEqu_Necklace].snIndex == 2291  && MOB.Equip[eTNEqu_Armor].snIndex == 1141 && MOB.Equip[eTNEqu_Belt].snIndex == 1591 && MOB.Equip[eTNEqu_Boots].snIndex == 1691  && MOB.Equip[eTNEqu_Gloves].snIndex == 1491  && MOB.Equip[eTNEqu_Pants].snIndex == 1241 )		
	{
			TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;
			kEffect1.iID = eTNAfn_AllStatePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_EnhanceWeapon ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 2;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_ResistHoldNSlow  ;
			kEffect3.kFunc.iData = 1;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 5;
			kEffect3.iParam2 = 0;	

			kEffect4.iID = eTNAfn_AbsorbDamage  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 20;
			kEffect4.iParam2 = 0;

	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect3, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect4, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	}
	//sz
       else if ( MOB.Equip[eTNEqu_Armor].snIndex == 1102  && MOB.Equip[eTNEqu_Gloves].snIndex == 1473  && MOB.Equip[eTNEqu_Pants].snIndex == 1223 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_EnhanceWeapon ;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 1;
			kEffect1.iParam2 = 0;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}
	
	}
//¹­´ÌÌ×
if( (TRIBE_ASURA==iTribe) || (TRIBE_RAKSHASA==iTribe) )
	{
	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 4333  && MOB.Equip[eTNEqu_Armor].snIndex == 1127  && MOB.Equip[eTNEqu_Boots].snIndex == 4531  && MOB.Equip[eTNEqu_Gloves].snIndex == 4446  && MOB.Equip[eTNEqu_Pants].snIndex == 4206 )		
	{
			TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;
			kEffect1.iID = eTNAfn_HPRecoveryPlus;
			kEffect1.kFunc.iData = 0;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 100;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_TPRecoveryPlus ;
			kEffect2.kFunc.iData = 0;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 100;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_MoveSpeedPlus  ;
			kEffect3.kFunc.iData = 0;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 1;
			kEffect3.iParam2 = 0;	

			kEffect4.iID = eTNAfn_AbsorbDamage  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 30;
			kEffect4.iParam2 = 0;
       if (MOB.byClass2 ==3 )
       {
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
       } else if (MOB.byClass2 ==2 )
    {
	AffectEffect( kEffect3, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    }
	AffectEffect( kEffect4, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );

	}	
	

	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 1392 && MOB.Equip[eTNEqu_Necklace].snIndex == 2292  && MOB.Equip[eTNEqu_Armor].snIndex == 1142 && MOB.Equip[eTNEqu_Belt].snIndex == 1592 && MOB.Equip[eTNEqu_Boots].snIndex == 1692  && MOB.Equip[eTNEqu_Gloves].snIndex == 1492  && MOB.Equip[eTNEqu_Pants].snIndex == 1242 )		
	{
			TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;
			kEffect1.iID = eTNAfn_AllStatePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_ResistSleep ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 5;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_EnhanceWeapon  ;
			kEffect3.kFunc.iData = 1;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 1;
			kEffect3.iParam2 = 0;	

			kEffect4.iID = eTNAfn_AbsorbDamage  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 20;
			kEffect4.iParam2 = 0;

	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect3, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect4, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );

	}
	//sz
       else if ( MOB.Equip[eTNEqu_Armor].snIndex == 1103  && MOB.Equip[eTNEqu_Gloves].snIndex == 1474  && MOB.Equip[eTNEqu_Pants].snIndex == 1224 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_FixedDamagePlus2 ;
			kEffect1.kFunc.iData = 0;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 1;
			kEffect1.iParam2 = 150;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}
	
	}
//È­Ì× 
if( (TRIBE_YAKSA==iTribe) || (TRIBE_GANDHARVA==iTribe) )
	{
	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 4334 && MOB.Equip[eTNEqu_Armor].snIndex == 1128 && MOB.Equip[eTNEqu_Boots].snIndex == 4532  && MOB.Equip[eTNEqu_Gloves].snIndex == 4447  && MOB.Equip[eTNEqu_Pants].snIndex == 4207 )		
	{
			TNEFFECT kEffect1,kEffect2;
			kEffect1.iID = eTNAfn_AllStatePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_AbsorbDamage ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 30;
			kEffect2.iParam2 = 0;	
			
			
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	}
	

	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 1393 && MOB.Equip[eTNEqu_Necklace].snIndex == 2293  && MOB.Equip[eTNEqu_Armor].snIndex == 1143 && MOB.Equip[eTNEqu_Belt].snIndex == 1593 && MOB.Equip[eTNEqu_Boots].snIndex == 1693  && MOB.Equip[eTNEqu_Gloves].snIndex == 1493  && MOB.Equip[eTNEqu_Pants].snIndex == 1243 )		
	{
			TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;
			kEffect1.iID = eTNAfn_AllStatePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_ResistStun ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 5;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_FixedDamagePlus2  ;
			kEffect3.kFunc.iData = 1;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 0;
			kEffect3.iParam2 = 5;	


			kEffect4.iID = eTNAfn_AbsorbDamage  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 20;
			kEffect4.iParam2 = 0;

	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect3, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect4, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}
	
	//sz
       else if ( MOB.Equip[eTNEqu_Armor].snIndex == 1104  && MOB.Equip[eTNEqu_Gloves].snIndex == 1475  && MOB.Equip[eTNEqu_Pants].snIndex == 1225 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_PoisonDamagePlus ;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}
		
	}


//·¨Ê¦Ì×

if( (TRIBE_DEVA==iTribe) || (TRIBE_GARUDA==iTribe) )
	{
        if ( MOB.Equip[eTNEqu_Helmet].snIndex == 4335 && MOB.Equip[eTNEqu_Armor].snIndex == 1133 && MOB.Equip[eTNEqu_Boots].snIndex == 4533  && MOB.Equip[eTNEqu_Gloves].snIndex == 4448  && MOB.Equip[eTNEqu_Pants].snIndex == 4208 )		
	{
			TNEFFECT kEffect1,kEffect2;
			kEffect1.iID = eTNAfn_AllDamagePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_AbsorbDamage ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 30;
			kEffect2.iParam2 = 0;	
			

	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );

	
	}	

	if ( MOB.Equip[eTNEqu_Helmet].snIndex == 1394 && MOB.Equip[eTNEqu_Necklace].snIndex == 2294  && MOB.Equip[eTNEqu_Armor].snIndex == 1144 && MOB.Equip[eTNEqu_Belt].snIndex == 1594 && MOB.Equip[eTNEqu_Boots].snIndex == 1694  && MOB.Equip[eTNEqu_Gloves].snIndex == 1494  && MOB.Equip[eTNEqu_Pants].snIndex == 1244 )		
	{
			TNEFFECT kEffect1,kEffect2,kEffect3,kEffect4;
			kEffect1.iID = eTNAfn_AllStatePlus;
			kEffect1.kFunc.iData = 1;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 10;
			kEffect1.iParam2 = 0;	
			
			kEffect2.iID = eTNAfn_ResistBlind ;
			kEffect2.kFunc.iData = 1;
			kEffect2.iDuration = eTNSklD_Unlimited;
			kEffect2.iParam1 = 5;
			kEffect2.iParam2 = 0;	
			
			kEffect3.iID = eTNAfn_AllDamagePlus  ;
			kEffect3.kFunc.iData = 1;
			kEffect3.iDuration = eTNSklD_Unlimited;
			kEffect3.iParam1 = 10;
			kEffect3.iParam2 = 0;	

			kEffect4.iID = eTNAfn_AbsorbDamage  ;
			kEffect4.kFunc.iData = 1;
			kEffect4.iDuration = eTNSklD_Unlimited;
			kEffect4.iParam1 = 20;
			kEffect4.iParam2 = 0;

	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
    AffectEffect( kEffect2, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect3, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	AffectEffect( kEffect4, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	}
	//sz
       else if ( MOB.Equip[eTNEqu_Armor].snIndex == 1105  && MOB.Equip[eTNEqu_Gloves].snIndex == 1476  && MOB.Equip[eTNEqu_Pants].snIndex == 1226 )		
	{
			TNEFFECT kEffect1;
			kEffect1.iID = eTNAfn_RangeUp ;
			kEffect1.kFunc.iData = 0;
			kEffect1.iDuration = eTNSklD_Unlimited;
			kEffect1.iParam1 = 1;
			kEffect1.iParam2 = 0;	
				
	AffectEffect( kEffect1, eVar_Equipment, eAfn_Add, m_iHandle, m_iHandle, 0 );
	
	
	}	
	}


	}
 //select_here to modify
	//-----------------------------------------------------------------------------------------
	// set item Ãß°¡ °è»ê
	//-----------------------------------------------------------------------------------------
	CheckSetItem();
	//ApplyItem( m_krgSetItem[0], 0 );
	//ApplyItem( m_krgSetItem[1], 0 );
	//ApplyItem( m_krgSetItem[2], 0 );


	UpdatePoints();
}


int CMob::CheckSetItem()
{
	memset( &m_krgSetItem, 0, sizeof(m_krgSetItem) );

	int iSetItemIndex = 0;
	int iSetItemID = 0;
	int iCount = 1;
	enum { eSet_MaxCount = 10, };
	int irgChecked[eSet_MaxCount] = { 0,0,0, };
	bool bAlreadyChecked = false;

	for( int iEquipIndex = 0; iEquipIndex < MAX_EQUIP; ++iEquipIndex ) 
	{		
		int	iItemDataIndex = MOB.Equip[iEquipIndex].snIndex;
		if( 0 >= iItemDataIndex || MAX_ITEM_DATA < iItemDataIndex ) continue; 
		if( 0 >= MOB.Equip[iEquipIndex].snDurability ) continue; // ³»±¸µµ°¡ 0ÀÎ °ÍÀº skip

		iSetItemID = 0;
		iCount = 1; 
		iSetItemID = pItemData[iItemDataIndex].byMaxLevel;
		if( 0 >= iSetItemID || eSetItem_Size <= iSetItemID ) continue;
		bAlreadyChecked = false;

		for( int i = 0; i < eSet_MaxCount; ++i )
		{ 
			if( iSetItemID == irgChecked[i] )
			{
				bAlreadyChecked = true;
				break;
			}
		}

		if( bAlreadyChecked ) continue;

		
		
		//if( 0 < iSetItemID && eSetItem_Size > iSetItemID )
		{ // Æ¯Á¤ setitemÀÇ Âø¿ë Á¶°ÇÀ» °Ë»çÇß´Ù. ÀÌÁ¦ ±× set itemÀ» ¸î piece ÀåÂøÇß´ÂÁö °Ë»çÇØ¼­ Ãß°¡ ¼º´ÉÀ» ÁøÇàÇÑ´Ù.
			// ÀÌ¹Ì Ã³¸®µÈ °ÍÀÎÁö È®ÀÎÇÏ´Â °úÁ¤ÀÌ ÀÖ¾î¾ß ÇÑ´Ù.			

			for( int i = iEquipIndex+1; i < MAX_EQUIP; ++i ) 
			{		
				int	iItemDataIndex = MOB.Equip[i].snIndex;
				if( 0 >= iItemDataIndex || MAX_ITEM_DATA < iItemDataIndex ) continue; 
				if( 0 >= MOB.Equip[i].snDurability ) continue; // ³»±¸µµ°¡ 0ÀÎ °ÍÀº skip

				if( iSetItemID == pItemData[iItemDataIndex].byMaxLevel ) ++iCount;
			}

			for( int i = 0; i < eSet_MaxCount; ++i )
			{
				if( 0 == irgChecked[i] )
				{
					irgChecked[i] = iSetItemID;
					break;
				}
			}


			if( 3 <= iCount )
			{
				m_krgSetItem[iSetItemIndex].snIndex = g_krgSetItem[iSetItemID].irgEffectItem[0] - HT_PARAMTYPE_ITEM_START + 1;
				m_krgSetItem[iSetItemIndex].byCount = 1;
				m_krgSetItem[iSetItemIndex].snDurability = eDur_Indestructible;

				ApplyItem( m_krgSetItem[iSetItemIndex], 0 );
				++iSetItemIndex;
			}

			if( 5 <= iCount )
			{
				m_krgSetItem[iSetItemIndex].snIndex = g_krgSetItem[iSetItemID].irgEffectItem[1] - HT_PARAMTYPE_ITEM_START + 1;
				m_krgSetItem[iSetItemIndex].byCount = 1;
				m_krgSetItem[iSetItemIndex].snDurability = eDur_Indestructible;
				ApplyItem( m_krgSetItem[iSetItemIndex], 0 );
				++iSetItemIndex;
			}

			if( 7 <= iCount )
			{
				m_krgSetItem[iSetItemIndex].snIndex = g_krgSetItem[iSetItemID].irgEffectItem[2] - HT_PARAMTYPE_ITEM_START + 1;
				m_krgSetItem[iSetItemIndex].byCount = 1;
				m_krgSetItem[iSetItemIndex].snDurability = eDur_Indestructible;
				ApplyItem( m_krgSetItem[iSetItemIndex], 0 );
				++iSetItemIndex;
			}

			#ifdef __DEBUG_LOG__
			//if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[CheckSetItem] iEquipSlot:%d, SetItemID:%d, Piece:%d, effect(%d,%d,%d), iSetItemIndex(Àû¿ëµÇ´Â È¿°ú°³¼ö):%d \r\n"
					, iEquipIndex, iSetItemID, iCount
					, g_krgSetItem[iSetItemID].irgEffectItem[0], g_krgSetItem[iSetItemID].irgEffectItem[1], g_krgSetItem[iSetItemID].irgEffectItem[2]
					, iSetItemIndex
					);
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
			

			if( eSetItem_MaxEffectItem <= iSetItemIndex ) return eTNRes_Succeeded;
		}
	}

	//if( 0 == iSetItemID ) return eTNRes_Failed; // set itemÀ» ÀåÂøÇÏ°í ÀÖÁö ¾Ê´Ù.

	//// ÇØ´ç setitemÀÇ Âø¿ë Á¶°ÇÀ» °Ë»çÇÑ´Ù.
	//bool bNotRequired = false;
	//for( int iEquipIndex = 0; iEquipIndex < MAX_EQUIP; ++iEquipIndex ) 
	//{		
	//	int iItemID = g_krgSetItem[iSetItemID].irgReq[iEquipIndex];
	//	if( 0 < iItemID )
	//	{
	//		if( 0 >= MOB.Equip[iEquipIndex].snDurability ) return eTNRes_Failed; // ³»±¸µµ°¡ 0ÀÎ °ÍÀº skip
	//		if( iItemID != get_ItemID( iEquipIndex ) ) return eTNRes_Failed;
	//	}
	//}
	//
	//m_kSetItem.snIndex = g_krgSetItem[iSetItemID].irgEffectItem[0] - HT_PARAMTYPE_ITEM_START + 1;
	//m_kSetItem.byCount = 1;
	//m_kSetItem.snDurability = eDur_Indestructible;

	return eTNRes_Succeeded;
}


/*
int CMob::PlayDice( int a_iMinDamage, int a_iMaxDamage )
{
	int iDamage = 0;
	int iGap = 0;
	iGap = a_iMaxDamage - a_iMinDamage;
	++iGap;

	if( 0 >= iGap )  iDamage = a_iMinDamage;
	else iDamage = a_iMinDamage + ( rand() % iGap );

	return iDamage;
}
*/

int CMob::CalDistance2( short a_sDestX, short a_sDestY )
{
	int iTempX = TargetX - a_sDestX;
	int iTempY = TargetY - a_sDestY;

	double dRealDist = sqrt( (double)(iTempX*iTempX + iTempY*iTempY) );
	int iDistance = (int)dRealDist;
	if( 0.5 <= (dRealDist - (double)iDistance) ) ++iDistance;
	if( 0 > iDistance ) iDistance = 0;

	return iDistance;
}



// DB¿¡¼­ data¸¦ ÀÐ¾î¿Í¼­ Ã³¸®¸¦ ÇØÁà¾ß ÇÑ´Ù.
void CMob::LoadSkills( byte a_byrgSkill[MAX_SKILL] )
{
	int iIndex = 0;
	int iSkillID = 0; 
	if( eTNMob_PC == m_eMobType )
	{
		int iStartID = 0;
		int iEndID = 0;
		switch ( MOB.snTribe )
		{
			case TRIBE_NAGA	 :		
			case TRIBE_KINNARA :
				iStartID = HT_PARAMTYPE_PCSKILL_NAGAKIN_START;
				iEndID = HT_PARAMTYPE_PCSKILL_NAGAKIN_END;
				break;			
			case TRIBE_ASURA :		
			case TRIBE_RAKSHASA :
				iStartID = HT_PARAMTYPE_PCSKILL_ASURARAK_START;
				iEndID = HT_PARAMTYPE_PCSKILL_ASURARAK_END;
				break;
			case TRIBE_YAKSA :		
			case TRIBE_GANDHARVA:
				iStartID = HT_PARAMTYPE_PCSKILL_YAKGAN_START;
				iEndID = HT_PARAMTYPE_PCSKILL_YAKGAN_END;
				break;
			case TRIBE_DEVA :
			case TRIBE_GARUDA:
				iStartID = HT_PARAMTYPE_PCSKILL_DEVAGARU_START;
				iEndID = HT_PARAMTYPE_PCSKILL_DEVAGARU_END;
				break;
		}
		
		for( int i = iStartID; i < iEndID; ++ i )
		{
			m_krgSkill[iIndex].sID = i;
			if( 0 >= a_byrgSkill[iIndex] ) m_krgSkill[iIndex].iIndex = 0;
			else // levelÀÌ 1 ÀÌ»óÀÎ °æ¿ì
			{
				m_krgSkill[iIndex].iIndex = (m_krgSkill[iIndex].sID-HT_PARAMTYPE_PCSKILL_NAGAKIN_START)*10 + a_byrgSkill[iIndex];
				m_krgSkill[iIndex].kDamage = pSkillData[m_krgSkill[iIndex].iIndex].kDamage;
				m_krgSkill[iIndex].uiCoolDownTime = 0;
				// passive skillÀÏ °æ¿ì ½ÃÀüÀ» ÇØÁØ´Ù.
				if( eTNSklD_Unlimited == pSkillData[m_krgSkill[iIndex].iIndex].iCastDuration )
				{
					#ifdef __DYNAMIC_LOG__
					if( m_iDebugFlag )
					{
						char chBuf[256] = { 0,0,0, };
						sprintf(chBuf, "\t- [LoadSkills] passive skill ¹ßµ¿: SkillID: %d(lvl:%d), À§Ä¡Index:%d   \r\n", pSkillData[m_krgSkill[iIndex].iIndex].sID, pSkillData[m_krgSkill[iIndex].iIndex].byLevel, m_krgSkill[iIndex].iIndex );
						WriteLog( chBuf, m_szLogFile );
					}
					#endif
					OnTakeAffections( pSkillData[m_krgSkill[iIndex].iIndex], iIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_PassiveSkill );
				}

				for( int s = 0; s < TN_MAX_EFFECT_COUNT; ++s )
				{
					if( 0 >= pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].iID ) continue;
					switch( pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].iID )
					{
					case eTNAfn_Hold :
					case eTNAfn_HoldNSlowMove :
					case eTNAfn_Stun :
					case eTNAfn_Sleep :
					case eTNAfn_Blind :
					case eTNAfn_CriticalStrike :
					case eTNAfn_PierceStrike :
					case eTNAfn_PierceStrike2 :
					case eTNAfn_KnockBack :
					case eTNAfn_Terror :
						m_krgSkill[iIndex].kDeck.AddCard( 0, 100-pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].iParam1 );
						m_krgSkill[iIndex].kDeck.AddCard( 1, pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].iParam1 );
						m_krgSkill[iIndex].kDeck.Shuffle();
						break;
					case eTNAfn_DOTbyDice :
						m_krgSkill[iIndex].kDeck.AddCard( 0, 100-pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].kFunc.iData );
						m_krgSkill[iIndex].kDeck.AddCard( 1, pSkillData[m_krgSkill[iIndex].iIndex].krgEffect[s].kFunc.iData );
						m_krgSkill[iIndex].kDeck.Shuffle();
						break;
					}
				}
			}

			++iIndex;
		}
	}
	else if( eTNMob_NPC == m_eMobType )
	{		
		for( int i = 0; i < TN_MONSTER_SKILL_COUNT; ++i )
		{
			m_krgSkill[i].sID = pMonsterData[MOB.nTP].Equip[i].snIndex+HT_PARAMTYPE_MONSTERSKILL_START;
			if( (0!=m_krgSkill[i].sID) && (HT_PARAMTYPE_MONSTERSKILL_START > m_krgSkill[i].sID  || HT_PARAMTYPE_MONSTERSKILL_END < m_krgSkill[i].sID) )
			{
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf( chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] LoadSkills> Àß¸øµÈ ¸ó½ºÅÍ skill ID: %d\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_krgSkill[i].sID );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
				}
				#endif // __TN_TOP_LOG__
				return;
			}
			m_krgSkill[i].iIndex = pMonsterData[MOB.nTP].Equip[i].snIndex + MONSTER_SKILL_START;
			m_krgSkill[i].kDamage = pSkillData[m_krgSkill[i].iIndex].kDamage;
			m_krgSkill[i].uiCoolDownTime = 0;

			MOB.bySkill[i] = 1; // skill level Àº ¸ðµÎ 1ÀÌ´Ù.

			for( int s = 0; s < TN_MAX_EFFECT_COUNT; ++s )
			{
				if( 0 >= pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iID ) continue;
				//if( eTNSklD_Instant >= pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iDuration ) continue;
				switch( pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iID )
				{
				case eTNAfn_Hold :
				case eTNAfn_HoldNSlowMove :
				case eTNAfn_Stun :
				case eTNAfn_Sleep :
				case eTNAfn_Blind :
				case eTNAfn_CriticalStrike :
				case eTNAfn_PierceStrike :
				case eTNAfn_PierceStrike2 :
				case eTNAfn_KnockBack :
				case eTNAfn_Terror :				
					m_krgSkill[i].kDeck.AddCard( 0, 100-pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iParam1 );
					m_krgSkill[i].kDeck.AddCard( 1, pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iParam1 );
					m_krgSkill[i].kDeck.Shuffle();
					//m_krgSkill[i].kDice.Init( pSkillData[m_krgSkill[i].iIndex].krgEffect[s].iParam1 );
					break;
				case eTNAfn_DOTbyDice :
					m_krgSkill[i].kDeck.AddCard( 0, 100-pSkillData[m_krgSkill[i].iIndex].krgEffect[s].kFunc.iData );
					m_krgSkill[i].kDeck.AddCard( 1, pSkillData[m_krgSkill[i].iIndex].krgEffect[s].kFunc.iData );
					m_krgSkill[i].kDeck.Shuffle();
					break;
				}
			}
		}
	}
}


int CMob::LearnSkill( unsigned short a_usSkillID, int a_iLevel )
{
	if( eTNMob_PC != m_eMobType || 0 >= a_usSkillID ) return eTNRes_Failed;

/*
	// ÀÓ½Ã ÄÚµå
	enum { eGoldTiger = 3331, eSilverTiger = 3332, eWolf = 3115, };
	if( eGoldTiger == a_sSkillID ) return eTNRes_Failed;
	if( eSilverTiger == a_sSkillID ) return eTNRes_Failed;
	if( eWolf == a_sSkillID ) return eTNRes_Failed;
*/
	bool IsCasteSkill = false;
	int iRes = eTNRes_Failed;
	if( (3065 <= a_usSkillID && 3080 > a_usSkillID) || (3165 <= a_usSkillID && 3180 > a_usSkillID) || (3265 <= a_usSkillID && 3280 > a_usSkillID) || (3365 <= a_usSkillID && 3380 > a_usSkillID) )
	{
		IsCasteSkill = true;
		if( a_iLevel <= m_kCasteSPRemaining.get_Cur() ) iRes = eTNRes_Succeeded;
		else iRes = eTNRes_SkillHaveNotSkillPoint;
	}
	else
	{
		if( a_iLevel <= m_kSPRemaining.get_Cur() ) iRes = eTNRes_Succeeded;
		else iRes = eTNRes_SkillHaveNotSkillPoint;
	}

	#ifdef __TN_3RD_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n[LearnSkill] skill ID:%d, level:%d, ³²¾ÆÀÖ´Â SP: %d, ÁÖ½Å½ºÅ³SP:%d \r\n"
			, a_usSkillID, a_iLevel, m_kSPRemaining.get_Cur(), m_kCasteSPRemaining.get_Cur() );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	int iSkillBookIndex = 0;
	if( eTNRes_Succeeded == iRes ) // ¿©À¯ skill point°¡ ÀÖÀ» °æ¿ì
	{
		for( iSkillBookIndex = 0; iSkillBookIndex < MAX_SKILL; ++iSkillBookIndex ) if( m_krgSkill[iSkillBookIndex].sID  == a_usSkillID ) break;
		if( MAX_SKILL <= iSkillBookIndex ) iRes = eTNRes_SkillNotRegistered;
		else
		{			
			int iDataIndex = m_krgSkill[iSkillBookIndex].iIndex;
			byte byMaxLevel = pSkillData[iDataIndex].byMaxLevel;
			if( 0 == MOB.bySkill[iSkillBookIndex] )
			{
				iDataIndex = (m_krgSkill[iSkillBookIndex].sID-HT_PARAMTYPE_PCSKILL_NAGAKIN_START)*10 + 1;
				byMaxLevel = pSkillData[iDataIndex].byMaxLevel;
			}

		    if( byMaxLevel <= MOB.bySkill[iSkillBookIndex] ) iRes = eTNRes_SkillCantLearnMore; // 
		    else
		    {
				/*
				int iSpareLevel = byMaxLevel - MOB.bySkill[iSkillBookIndex];
				if( iSpareLevel < a_iLevel ) a_iLevel = iSpareLevel;
				*/
				if( 0 != MOB.bySkill[iSkillBookIndex] ) ++iDataIndex;

				if( pSkillData[iDataIndex].kReq.byLevel > MOB.byLevel ) return eTNRes_ReqLevel;

				//-----------------------------------------------------------------
				// ÁÖ½Å ½ºÅ³ÀÌ Ãß°¡µÇ¸é¼­, ½ºÅ³ ¹è¿ï¶§ ¿ä±¸Á¶°ÇÀÌ ´Ù¾çÇØÁ³´Ù.
				//-----------------------------------------------------------------
				if( IsCasteSkill )
				{
					if( 0 < pSkillData[iDataIndex].kReq.byTrimuriti )
					{ // 1. ÁÖ½ÅÀÌ ÀÏÄ¡ÇÏ´ÂÁö °Ë»ç, 2. caste°¡ ÀûÇÕÇÑÁö °Ë»ç
						if( MOB.byTrimuriti != pSkillData[iDataIndex].kReq.byTrimuriti ) return eTNRes_ReqTrimuriti;
					}

					if( pSkillData[iDataIndex].kReq.iClass > m_iCaste ) return eTNRes_ReqCaste; // // class´Â caste·Î ´ëÃ¼ÇØ¼­ »ç¿ëÇÑ´Ù.
				}

				bool brgSkill[2] = { false, false };
				for(int k = 0; k < 2; ++k )
				{
					if( 0 < pSkillData[iDataIndex].kReqSkill[k].sID )
					{
						for( int i = 0; i < TN_PC_SKILL_COUNT; ++i )
						{
							if( m_krgSkill[i].sID == pSkillData[iDataIndex].kReqSkill[k].sID )
							{
								if( pSkillData[iDataIndex].kReqSkill[k].byLevel > MOB.bySkill[i] ) return eTNRes_ReqBaseSkill;
								else brgSkill[k] = true;
							}
							else if( m_krgSkill[i].sID > pSkillData[iDataIndex].kReqSkill[k].sID ) break;
						}
					}
					else brgSkill[k] = true;
				}

				if( brgSkill[0] && brgSkill[1] ) // ¸ðµÎ ¸¸Á·
		        {
					if( IsCasteSkill ) m_kCasteSPRemaining.Dec(1);
					else m_kSPRemaining.Dec(1);

		            ++MOB.bySkill[iSkillBookIndex];
		            m_krgSkill[iSkillBookIndex].iIndex = iDataIndex;
					m_krgSkill[iSkillBookIndex].kDamage = pSkillData[iDataIndex].kDamage;

					for( int s = 0; s < TN_MAX_EFFECT_COUNT; ++s )
					{
						if( 0 >= pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].iID ) continue;
						//if( eTNSklD_Instant >= pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].iDuration ) continue;
						switch( pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].iID )
						{
						case eTNAfn_Hold :
						case eTNAfn_HoldNSlowMove :
						case eTNAfn_Stun :
						case eTNAfn_Sleep :
						case eTNAfn_Blind :
						case eTNAfn_CriticalStrike :
						case eTNAfn_PierceStrike :
						case eTNAfn_PierceStrike2 :
						case eTNAfn_KnockBack :
						case eTNAfn_Terror :
							m_krgSkill[iSkillBookIndex].kDeck.AddCard( 0, 100 - pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].iParam1 );
							m_krgSkill[iSkillBookIndex].kDeck.AddCard( 1, pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].iParam1 );
							m_krgSkill[iSkillBookIndex].kDeck.Shuffle();
							break;
						case eTNAfn_DOTbyDice :
							m_krgSkill[iSkillBookIndex].kDeck.AddCard( 0, 100 - pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].kFunc.iData );
							m_krgSkill[iSkillBookIndex].kDeck.AddCard( 1, pSkillData[m_krgSkill[iSkillBookIndex].iIndex].krgEffect[s].kFunc.iData );
							m_krgSkill[iSkillBookIndex].kDeck.Shuffle();
							break;
						}
					}		            

		            if( eTNSklD_Unlimited == pSkillData[iDataIndex].iCastDuration )
		            { 
		                if( 1 < MOB.bySkill[iSkillBookIndex] ) OnTakeAffections( pSkillData[iDataIndex-1], iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Remove, eVar_PassiveSkill ); //AffectPermanentEffects( pSkillData[m_krgSkill[i].iIndex-1], eAfn_Remove );
		                OnTakeAffections( pSkillData[iDataIndex], iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_PassiveSkill ); //AffectPermanentEffects( pSkillData[m_krgSkill[i].iIndex], eAfn_Add );
						UpdateEquipmentPoints();
		            }

					NotifyUpdateUIMsg();
		        }
		    }
		}		
	}

	S_SCP_RESP_LEARN_SKILL kMsg;
	kMsg.wType = SCP_RESP_LEARN_SKILL;
	kMsg.byRes = (BYTE)iRes;
	kMsg.kSkill.snID = (signed)a_usSkillID;
	kMsg.kSkill.byLevel = MOB.bySkill[iSkillBookIndex];

	#ifdef __TN_2ND_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[LearnSkill] 2. Res: %d, skill> ID: %d, Level: %d, ³²¾ÆÀÖ´Â SP: %d, caste sp:%d \r\n"
			, kMsg.byRes, kMsg.kSkill.snID, kMsg.kSkill.byLevel, m_kSPRemaining.get_Cur(), m_kCasteSPRemaining.get_Cur() );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_2ND_LOG__

	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_RESP_LEARN_SKILL));

	return eTNRes_Succeeded;
}


void CMob::ResetSkill()
{
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return;

	DropKalaCore();
	//if( eTNSwitch_ResetSkill & g_iSwitch ) return;
	memset( MOB.bySkill, 0, sizeof(MOB.bySkill) );
	for( int i = 0; i <= MAX_SKILL; ++i )	m_krgSkill[i].uiCoolDownTime = 0;

	Init( m_iHandle );
	NotifyUpdateUIMsg();
	// clientÀÇ skill panelÀ» ÃÊ±âÈ­ ÇÏ´Â ¸Þ½ÃÁö
	S_SCP_RESP_LEARN_SKILL kMsg;
	kMsg.wType = SCP_RESP_LEARN_SKILL;
	kMsg.byRes = eTNRes_SkillReset;
	kMsg.kSkill.snID = 0;
	kMsg.kSkill.byLevel = 0;
	pUser[m_iHandle].cSock.AddMessage( (char*)&kMsg, sizeof(S_SCP_RESP_LEARN_SKILL) );
}


void CMob::ResetStat()
{
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return;

	DropKalaCore();

	if( (TRIBE_NAGA==MOB.snTribe) || (TRIBE_KINNARA==MOB.snTribe) )
	{
		MOB.sMuscle = 12;
		MOB.sNerves = 10;
		MOB.sHeart = 11;
		MOB.sMind = 10;
	}
	else if( (TRIBE_ASURA==MOB.snTribe) || (TRIBE_RAKSHASA==MOB.snTribe) )
	{
		MOB.sMuscle = 11;
		MOB.sNerves = 12;
		MOB.sHeart = 10;
		MOB.sMind = 10;
	}
	else if( (TRIBE_YAKSA==MOB.snTribe) || (TRIBE_GANDHARVA==MOB.snTribe) )
	{
		MOB.sMuscle = 11;
		MOB.sNerves = 11;
		MOB.sHeart = 11;
		MOB.sMind = 10;
	}
	else if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) )
	{
		MOB.sMuscle = 10;
		MOB.sNerves = 10;
		MOB.sHeart = 10;
		MOB.sMind = 13;
	}

	//int iTotalChakra = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
	//m_kCPRemaining.Init( 1275, 50 + (MOB.byLevel - 1) * 5 - iTotalChakra );

	Init( m_iHandle );
	NotifyUpdateUIMsg();
}


int CMob::ResetClass()
{
	if( 2 > MOB.byClass1 ) return eTNRes_Failed;

	int iTribe = MOB.snTribe;
	MOB.byClass1 = 1;
	if( (TRIBE_NAGA==iTribe) || (TRIBE_KINNARA==iTribe) ) MOB.byClass2 = 0;
	else if( (TRIBE_ASURA==iTribe) || (TRIBE_RAKSHASA==iTribe) ) MOB.byClass2 = 1;
	else if( (TRIBE_YAKSA==iTribe) || (TRIBE_GANDHARVA==iTribe) ) MOB.byClass2 = 2;
	else if( (TRIBE_DEVA==iTribe) || (TRIBE_GARUDA==iTribe) ) MOB.byClass2 = 3;
	MOB.byQuest[31] = MOB.byQuest[32] = MOB.byQuest[33] = MOB.byQuest[34] = MOB.byQuest[35] = 0;
	SendQuestHistory( m_iHandle );
	NotifyUpdateUIMsg();

	//	±æµå¿øµé¿¡°Ô ÀüÁ÷ÃÊ±âÈ­¸¦ Àü¼ÛÇÑ´Ù.
	DBUpdateGuildMember(m_iHandle);

	return eTNRes_Succeeded;
}


int CMob::OnDefense( int a_iAttackRate, int a_iAttacker, bool a_bCheckDodgeSpeed )
{
	if( 0 >= a_iAttacker || MAX_MOB <= a_iAttacker ) return eCmbt_Dodge;
	//if( eTNInAfn_PerfectDodge & m_iInnerAffections ) return eCmbt_Dodge; // Àý´ë È¸ÇÇ

    short sLevelGap = MOB.byLevel - pMob[a_iAttacker].MOB.byLevel + eCon_MaxGap; // ¹æ¾îÀÚ - °ø°ÝÀÚ + eCon_MaxGap
    if( 0 > sLevelGap ) sLevelGap = 0;
    if( eCon_MaxGapCount <= sLevelGap ) sLevelGap = eCon_LastIndex;

	int iDodgeConsider = 0; // g_krgConsider[pMob[a_iAttacker].m_eMobType][m_eMobType].irgVal[sLevelGap][eCon_DG];
	if( (eTNMob_PC == m_eMobType) && (eTNMob_PC == pMob[a_iAttacker].m_eMobType) )
	{
		int iLvlGap = MOB.byLevel - pMob[a_iAttacker].MOB.byLevel;
		if( 0 < iLvlGap ) // ¹æ¾îÀÚ°¡ ·¹º§ÀÌ ³ôÀ¸¸é, ¹æ¾î¿¡ °ü·ÃÇØ¼­ ÀÌµæÀ» ¾ò´Â´Ù. °ø°ÝÀÚ°¡ ·¹º§ÀÌ ³ôÀ¸¸é, ÀÌµæÀº ¾ø´Ù.
		{
			iDodgeConsider = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_DG] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iAttacker].MOB.byLevel][eCon_DG];
			//if( 40 < iDodgeConsider ) iDodgeConsider = 40;
		}
	}

	//int iDodge = m_kCombatFactors.iDodgeRate + Percent( m_kCombatFactors.iDodgeRate, iDodgeConsider );
	int iDodge = m_kCombatFactors.iDodgeRate + iDodgeConsider;
	if( 0 >= iDodge ) iDodge = 0;
	int iResult = a_iAttackRate - iDodge;

	int iJudgeCombatIndex = 0;
	if( 290 < iResult ) iJudgeCombatIndex = 0;
	else if( 200 < iResult && 290 >= iResult ) iJudgeCombatIndex = 1;
	else if( 120 < iResult && 200 >= iResult ) iJudgeCombatIndex = 2;
	else if( 50 < iResult && 120 >= iResult ) iJudgeCombatIndex = 3;
	else if(  -50 < iResult && 50 >= iResult ) iJudgeCombatIndex = 4;
	else if(  -120 < iResult &&  -50 >= iResult ) iJudgeCombatIndex = 5;
	else if(  -200 < iResult &&  -120 >= iResult ) iJudgeCombatIndex = 6;
	else if(  -290 < iResult &&  -200 >= iResult ) iJudgeCombatIndex = 7;
	else if(  -390 < iResult &&  -290 >= iResult ) iJudgeCombatIndex = 8;
	else if(  -390 >= iResult ) iJudgeCombatIndex = 9;

	//int iCmbtRes = m_krgCFTable[iJudgeCombatIndex].Random();
	int iCmbtRes = m_krgJudgeCombat[pMob[a_iAttacker].m_eMobType][m_eMobType].krgJudgeCombat[iJudgeCombatIndex].Random();
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "  => [OnDefense] AttackRate: %d, DodgeRate: %d(%d), Attack/Dodge: %d, iJudgeCombatIndex:%d, iCmbtRes:%d, m_iAffections:%u, iDodgeConsider:%d \r\n", a_iAttackRate, iDodge, m_kCombatFactors.iDodgeRate, iResult, iJudgeCombatIndex, iCmbtRes, m_iAffections, iDodgeConsider ); 
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	if( (m_kLastTime.uiDodged > CurrentTime) && a_bCheckDodgeSpeed )
	{
		if( eCmbt_Dodge == iCmbtRes ) iCmbtRes = eCmbt_Normal;
	}
	else
	{
		m_kLastTime.uiDodged = CurrentTime + m_kCombatFactors.iDodgeSpeed;
	}

	return iCmbtRes;
}


//int CMob::OnDefense( int a_iAttackRate, int a_iAttacker )
//{
//	if( 0 >= a_iAttacker || MAX_MOB <= a_iAttacker ) return eCmbt_Dodge;
//
//	int iHitRate = 100;
//    short sLevelGap = MOB.byLevel - pMob[a_iAttacker].MOB.byLevel + eCon_MaxGap; // ¹æ¾îÀÚ - °ø°ÝÀÚ + eCon_MaxGap
//    if( 0 > sLevelGap ) sLevelGap = 0;
//    if( eCon_MaxGapCount <= sLevelGap ) sLevelGap = eCon_LastIndex;
//
//	int iDodgeConsider = g_krgConsider[pMob[a_iAttacker].m_eMobType][m_eMobType].irgVal[sLevelGap][eCon_DG];
//	//if( (0 == sLevelGap) && ( 0 == pMob[a_iAttacker].m_eMobType ) && (1 ==m_eMobType ) ) iDodgeConsider = -40;
//	int iDodge = m_kCombatFactors.iDodgeRate + Percent( m_kCombatFactors.iDodgeRate, iDodgeConsider );
//	iDodge += m_kCombatFactors.iDodgeRateBonus;
//
//	//if( eTNVSAfn_CantDefense & m_iAffections ) iDodge = 100;
//	if( 0 >= iDodge ) iDodge = 1;
//	int iResult = a_iAttackRate * 100 / iDodge;
//
//	int iJudgeCombatIndex = 0;
//	if( 500 <= iResult ) iJudgeCombatIndex = 0;
//	else if( 300 <= iResult && 500 > iResult ) iJudgeCombatIndex = 1;
//	else if( 200 <= iResult && 300 > iResult ) iJudgeCombatIndex = 2;
//	else if( 125 <= iResult && 200 > iResult ) iJudgeCombatIndex = 3;
//	else if(  80 <= iResult && 125 > iResult ) iJudgeCombatIndex = 4;
//	else if(  50 <= iResult &&  80 > iResult ) iJudgeCombatIndex = 5;
//	else if(  33 <= iResult &&  50 > iResult ) iJudgeCombatIndex = 6;
//	else if(  20 <= iResult &&  33 > iResult ) iJudgeCombatIndex = 7;
//	else if(  20 > iResult ) iJudgeCombatIndex = 8;
//
//	//int iCmbtRes = m_krgCFTable[iJudgeCombatIndex].Random();
//	int iCmbtRes = m_krgJudgeCombat[pMob[a_iAttacker].m_eMobType][m_eMobType].krgJudgeCombat[iJudgeCombatIndex].Random();
//	#ifdef __DYNAMIC_LOG__
//	if( m_iDebugFlag )
//	{
//		char chBuf[256] = { 0,0,0, };
//		sprintf(chBuf, "  => [OnDefense] AttackRate: %d, DodgeRate: %d(%d), Attack/Dodge: %d, iJudgeCombatIndex:%d, iCmbtRes:%d, m_iAffections:%d, iDodgeConsider:%d \r\n", a_iAttackRate, iDodge, m_kCombatFactors.iDodgeRate, iResult, iJudgeCombatIndex, iCmbtRes, m_iAffections, iDodgeConsider ); 
//		WriteLog( chBuf, m_szLogFile );
//	}
//	#endif //__TN_3RD_LOG__
//
///*
//	if( m_kLastTime.uiDodged > CurrentTime )
//	{
//		if( eCmbt_Dodge == iCmbtRes ) iCmbtRes = eCmbt_Normal;
//	}
//	else
//	{
//		m_kLastTime.uiDodged = CurrentTime + m_kCombatFactors.iDodgeSpeed;
//	}
//*/
//	return iCmbtRes;
//}


void CMob::Resist( TNDAMAGE& a_kDamage )
{
	if( 0 < a_kDamage.irgFire[0] ) a_kDamage.irgFire[0] = 100 * a_kDamage.irgFire[0] / ( 5 * m_kCombatFactors.irgResist[eRst_Fire] + 100);
	if( 0 < a_kDamage.irgCold[0] ) a_kDamage.irgCold[0] = 100 * a_kDamage.irgCold[0] / ( 5 * m_kCombatFactors.irgResist[eRst_Cold] + 100);
	if( 0 < a_kDamage.irgLightning[0] ) a_kDamage.irgLightning[0] = 100 * a_kDamage.irgLightning[0] / ( 5 * m_kCombatFactors.irgResist[eRst_Lightning] + 100);
	if( 0 < a_kDamage.irgPoison[0] ) a_kDamage.irgPoison[0] = 100 * a_kDamage.irgPoison[0] / ( 5 * m_kCombatFactors.irgResist[eRst_Poison] + 100);
}



//-------------------------------------------------------------------------------------------
// ÀüÅõ ¼³Á¤À¸·Î º¯È¯ÇÏ°í ±×¿Í °ü·ÃµÈ °ÍµéÀ» ¸ðµÎ Ã³¸®ÇÏ±â À§ÇÑ ÇÔ¼ö
// ´Ü¼øÇÏ°Ô ÀüÅõ ¼³Á¤À¸·Î º¯°æÀ» ÇÏ´Â °ÍÀº MemorizeAttacker()ÇÔ¼ö¸¦ »ç¿ëÇÑ´Ù.
//-------------------------------------------------------------------------------------------
void CMob::OnUnderAttack( int a_iAttacker, int a_iType )
{
	if( 0 >= a_iAttacker || MAX_MOB <= a_iAttacker ) return;
	if( IsDead() ) return;
	if( m_iHandle == a_iAttacker ) return;	// ÀÚ±âÀÚ½ÅÀÌ´Ù.

	if( MOB_COMBAT == Mode ) // ÀüÅõ ÁßÀÌ°í
	{
		if( 3 < m_iAttackerCount ) Think( eTNAI_UnderAttack2, a_iAttacker ); // ÀûÀÇ ¼ö¸¦ ÆÄ¾ÇÇÑ ÈÄ¿¡ Ã³¸®ÇÑ´Ù.		
	}
	else
	{
		if( eTNUndAtt_Normal == a_iType ) Think( eTNAI_UnderAttack1, a_iAttacker );
		m_kLastTime.uiAttacked = CurrentTime;
	}

	MemorizeAttacker( 0, 1, a_iAttacker );
	pMob[a_iAttacker].MemorizeAttacker( 0, 1, m_iHandle );

	if( 1 == m_iGroup ) // party, guard¼³Á¤ÀÌ µÇ¾î ÀÖÀ» ¼ö°¡ ÀÖ´Ù.
	{
		int iLeader = Leader;
		if( 0 >= iLeader ) iLeader = m_iHandle;

		for ( int d=0; d<MAX_PARTY;++d )
		{   int fol = pMob[iLeader].m_irgParty[d];
			if  (fol< MAX_USER) continue; //  PCÀÌ¸é skip
			if( fol == m_iHandle ) continue;			

			if( iLeader == m_iHandle ) // party leader°¡ °ø°ÝÀ» ¹Þ¾ÒÀ» °æ¿ì, guardÀÏ °æ¿ì
			{
				pMob[fol].MemorizeAttacker( 0, 1, a_iAttacker );
				pMob[fol].m_eStatus = pMob[fol].m_eStatus | eTNSts_Guard;
			}
			else
			{
				if( eTNSts_Guard & pMob[fol].m_eStatus ) continue;
				if( MOB_COMBAT == pMob[fol].Mode ) continue;
				pMob[fol].MemorizeAttacker( 0, 1, a_iAttacker );
			}
		} // for ( int d=0; d<MAX_PARTY;++d )
	}
}



//-------------------------------------------------------------------------------------------------
//@Param 999 ÎïÀíÉËº¦»òÕßÎïÀí×·¼ÓÉËº¦  888 ÔªËØ×·¼ÓÉËº¦ ÆäËûID ¼¼ÄÜÒ»´ÎÐÔÉËº¦ //fors_debug ÐÞ¸ÄÁËËùÓÐ´Ëº¯ÊýµÄ´«ÈëÖµ
//	- a_iDamage : ÃÑ physical damage°¡ ÀÔ·ÂµÇ°í ±×¸®°í ½ÇÁ¦·Î HP¸¦ ±ïÀº damage ¾çÀ» outputÇØÁØ´Ù. 
//-------------------------------------------------------------------------------------------------
int CMob::OnTakeDamage( TNDAMAGE& a_kDamage, int a_iAttacker, short a_sLevelGap,int skillID  )
{
	//if( IsDead() || (m_iHandle == a_iAttacker) ||( eTNImm_All == m_iImmunity ) || (0 >= a_iAttacker) || (MAX_MOB <= a_iAttacker) )
	if( IsDead() || (eTNImm_All == m_iImmunity) || (0 >= a_iAttacker) || (MAX_MOB <= a_iAttacker) || (0 > a_sLevelGap) || (eCon_MaxGapCount <= a_sLevelGap) )
	{
		a_kDamage.iSum = 0;
if ( g_iZoneID == 10 || g_iZoneID == 16 )
if ( eTNMob_PC == m_eMobType && 0 < a_iAttacker && MAX_USER > a_iAttacker )
{
	char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t\t[On_BUTNOUSE] whoer(%d, %s),--miImm(%d)\r\n", m_iHandle, pMob[m_iHandle].MOB.szName,m_iImmunity); 
	//	WriteLog( chBuf, m_szLogFile );
 Log(chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP); 
}
		
		return MOB.nHP;
	}

	TurnOffAffection( eTNAfn_Sleep );

	if( eTNVSAfn_ManaShield & m_iAffections )
	{
		RemoveEffect( eTNAfn_ManaShield );
		a_kDamage.iSum = 0;
		return MOB.nHP;
	}

	int iDefenseConsider = g_krgConsider[pMob[a_iAttacker].m_eMobType][m_eMobType].irgVal[a_sLevelGap][eCon_DF];	
	int iDefense = m_kCombatFactors.iDefense + Percent( m_kCombatFactors.iDefense, iDefenseConsider );
	int iResistConsider = g_krgConsider[pMob[a_iAttacker].m_eMobType][m_eMobType].irgVal[a_sLevelGap][eCon_RS];
	int iFireResist = m_kCombatFactors.irgResist[eRst_Fire] + Percent( m_kCombatFactors.irgResist[eRst_Fire], iResistConsider );
	int iColdResist = m_kCombatFactors.irgResist[eRst_Cold] + Percent( m_kCombatFactors.irgResist[eRst_Cold], iResistConsider );
	int iLightningResist = m_kCombatFactors.irgResist[eRst_Lightning] + Percent( m_kCombatFactors.irgResist[eRst_Lightning], iResistConsider );
	int iPoisonResist = m_kCombatFactors.irgResist[eRst_Poison] + Percent( m_kCombatFactors.irgResist[eRst_Poison], iResistConsider );

	if( eTNMob_PC == m_eMobType )
	{
		if( eTNMob_PC == pMob[a_iAttacker].m_eMobType )
		{ // °ø°ÝÀÚ¿Í ¼öºñÀÚ°¡ ¸ðµÎ PCÀÌ´Ù.
			int iSiege = g_kSiege.get_Started();
			if( !iSiege ) // °ø¼ºÀüÀÌ ¾Æ´Ï¶ó¸é
			{
				if( (g_irgSetting[eCnst_Restriction] > MOB.byLevel) && a_iAttacker!=pUser[m_iHandle].m_nChallenger)
				{
					a_kDamage.iSum = 0;
					return MOB.nHP;
				}
			}

			int iLvlGap = MOB.byLevel - pMob[a_iAttacker].MOB.byLevel;
			if( 0 >= iLvlGap )
			{
				iDefenseConsider = 0;
				iResistConsider = 0;
				iDefense = m_kCombatFactors.iDefense;
				iFireResist = m_kCombatFactors.irgResist[eRst_Fire];
				iColdResist = m_kCombatFactors.irgResist[eRst_Cold];
				iLightningResist = m_kCombatFactors.irgResist[eRst_Lightning];
				iPoisonResist = m_kCombatFactors.irgResist[eRst_Poison];
			}
			else // ¹æ¾îÀÚ°¡ ·¹º§ÀÌ ³ôÀ¸¸é, ¹æ¾î¿¡ °ü·ÃÇØ¼­ ÀÌµæÀ» ¾ò´Â´Ù. °ø°ÝÀÚ°¡ ·¹º§ÀÌ ³ôÀ¸¸é, ÀÌµæÀº ¾ø´Ù.
			{
				iDefenseConsider = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_DF] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iAttacker].MOB.byLevel][eCon_DF];
				iDefense = m_kCombatFactors.iDefense + iDefenseConsider;

				iResistConsider = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iAttacker].MOB.byLevel][eCon_RS];
				iFireResist = m_kCombatFactors.irgResist[eRst_Fire] + iResistConsider;
				iColdResist = m_kCombatFactors.irgResist[eRst_Cold] + iResistConsider;
				iLightningResist = m_kCombatFactors.irgResist[eRst_Lightning] + iResistConsider;
				iPoisonResist = m_kCombatFactors.irgResist[eRst_Poison] + iResistConsider;

				if( g_irgSetting[eCnst_ResistMax] < iFireResist ) iFireResist = g_irgSetting[eCnst_ResistMax];
				if( g_irgSetting[eCnst_ResistMax] < iColdResist ) iColdResist = g_irgSetting[eCnst_ResistMax];
				if( g_irgSetting[eCnst_ResistMax] < iLightningResist ) iLightningResist = g_irgSetting[eCnst_ResistMax];
				if( g_irgSetting[eCnst_ResistMax] < iPoisonResist ) iPoisonResist = g_irgSetting[eCnst_ResistMax];
			}
		}

		if( (eTNImm_Damage & m_iImmunity) && (eTNImm_Pierce & m_iImmunity)  )
		{
			if( eTNClan_GM != m_byClan )
			{
				if( eTNInAfn_Immunity2 & m_iInnerAffections); // Á¤»ó
				else
				{
					m_iImmunity = 0;
				}
			}
		}
	}

	/*
	// FixedDamage´Â ¸ðµç °Í¿¡ ´ëÇØ¼­ Àû¿ë, FixedDamage2´Â µ¿Àû ½ºÅ³¿¡ ÀÇÇÑ °Í¸¸ Á¦¿Ü
	a_kDamage.irgPierce[0] += (pMob[a_iAttacker].m_krgVariation[eTNVar_FixedDamage][eVar_PassiveSkill].iPlus
		+ pMob[a_iAttacker].m_krgVariation[eTNVar_FixedDamage][eVar_Skill].iPlus
		+ pMob[a_iAttacker].m_krgVariation[eTNVar_FixedDamage][eVar_Equipment].iPlus );
	a_kDamage.irgPierce[0] += (pMob[a_iAttacker].m_krgVariation[eTNVar_FixedDamage2][eVar_PassiveSkill].iPlus
		+ pMob[a_iAttacker].m_krgVariation[eTNVar_FixedDamage2][eVar_Equipment].iPlus );
	*/

	if( eTNImm_Damage & m_iImmunity ) a_kDamage.irgPhy[0] = 0;
	if( eTNImm_Pierce & m_iImmunity ) a_kDamage.irgPierce[0] = 0;	

	if( 0 >= a_kDamage.irgPhy[0] ) a_kDamage.irgPhy[0] = 0;
	else
	{		
		//if( g_bIsInRvR )
		if( eZoneType_God == g_iZoneType )
		{
			if( (eTNMob_PC == m_eMobType) && (eTNMob_PC == pMob[a_iAttacker].m_eMobType) )
				iDefense += Percent( m_kCombatFactors.iDefense, g_irgRvRPKConsider[m_iCaste][pMob[a_iAttacker].m_iCaste] );
		}
		if( 0 > iDefense ) iDefense = 0;
		//iDefense -= a_kDamage.iDecDef;
		iDefense -= Percent( iDefense, a_kDamage.iDecDef );
		if( 0 > iDefense ) iDefense = 0;
		a_kDamage.irgPhy[0] = ( a_kDamage.irgPhy[0]*150) / ( iDefense + 150 );

		// ÆÄ¶óÄ«, Çâ»óµÈ ÆÄ¶óÄ« ½ºÅ³
		AbsorbDamageWithMagicShield( a_kDamage.irgPhy[0] );
		AbsorbDamageWithEnhancedMagicShield( a_kDamage.irgPhy[0], eConst_Physical );

		int iAbsorbDamage = m_krgVariation[eTNVar_AbsorbDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AbsorbDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_AbsorbDamage][eVar_PassiveSkill].iPPlus;
		if( 0 > iAbsorbDamage ) iAbsorbDamage = 0;
		if( g_irgSetting[eCnst_AbsorbMax] < iAbsorbDamage ) iAbsorbDamage = g_irgSetting[eCnst_AbsorbMax];
		if( 0 < a_kDamage.irgPhy[0] ) a_kDamage.irgPhy[0] = a_kDamage.irgPhy[0] - Percent( a_kDamage.irgPhy[0], iAbsorbDamage );  // absorb damage, ¹°¸® µ¥¹ÌÁö¸¸ Èí¼öÇÑ´Ù.
		if( 0 > a_kDamage.irgPhy[0] ) a_kDamage.irgPhy[0] = 0;
	}

	if( 0 >= a_kDamage.irgPierce[0] ) a_kDamage.irgPierce[0] = 0;
	/*
	else
	{
		//a_kDamage.irgPierce[0] = AbsorbDamageWithMagicShield( a_kDamage.irgPierce[0] );
		//if( 0 < a_kDamage.irgPierce[0] ) a_kDamage.irgPierce[0] = a_kDamage.irgPierce[0] - Percent( a_kDamage.irgPierce[0], (m_krgVariation[eTNVar_AbsorbDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AbsorbDamage][eVar_Skill].iPPlus ) );  // absorb damage, ¹°¸® µ¥¹ÌÁö¸¸ Èí¼öÇÑ´Ù.
		//if( 0 > a_kDamage.irgPierce[0] ) a_kDamage.irgPierce[0] = 0;
	}
	*/


	if( eTNImm_Fire & m_iImmunity ) a_kDamage.irgFire[0] = 0;
	if( eTNImm_Cold & m_iImmunity ) a_kDamage.irgCold[0] = 0;
	if( eTNImm_Lightning & m_iImmunity ) a_kDamage.irgLightning[0] = 0;
	if( eTNImm_Poison & m_iImmunity ) a_kDamage.irgPoison[0] = 0;
	
	int iResist = 0;
	if( 0 < a_kDamage.irgFire[0] )
	{
		//iResist = m_kCombatFactors.irgResist[eRst_Fire] + Percent( m_kCombatFactors.irgResist[eRst_Fire], iResistConsider );
		a_kDamage.irgFire[0] = 100 * a_kDamage.irgFire[0] / ( 2 * iFireResist  + 100);
	}
	if( 0 < a_kDamage.irgCold[0] )
	{
		//iResist = m_kCombatFactors.irgResist[eRst_Cold] + Percent( m_kCombatFactors.irgResist[eRst_Cold], iResistConsider );
		a_kDamage.irgCold[0] = 100 * a_kDamage.irgCold[0] / ( 2 * iColdResist + 100);
	}
	if( 0 < a_kDamage.irgLightning[0] )
	{
		//iResist = m_kCombatFactors.irgResist[eRst_Lightning] + Percent( m_kCombatFactors.irgResist[eRst_Lightning], iResistConsider );
		a_kDamage.irgLightning[0] = 100 * a_kDamage.irgLightning[0] / ( 2 * iLightningResist + 100);
	}
	if( 0 < a_kDamage.irgPoison[0] )
	{
		//iResist = m_kCombatFactors.irgResist[eRst_Poison] + Percent( m_kCombatFactors.irgResist[eRst_Poison], iResistConsider );
		a_kDamage.irgPoison[0] = 100 * a_kDamage.irgPoison[0] / ( 2 * iPoisonResist + 100);
	}

	int iElementalDamage = a_kDamage.irgFire[0] + a_kDamage.irgCold[0] + a_kDamage.irgLightning[0] + a_kDamage.irgPoison[0];

	AbsorbDamageWithEnhancedMagicShield( iElementalDamage, eConst_Elemental );


	//--------------------------------------------------
	// Absorb elemental damage
	//--------------------------------------------------
	int iAbsorbElementalDamage = m_krgVariation[eTNVar_AbsorbElementalDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_AbsorbElementalDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_AbsorbElementalDamage][eVar_PassiveSkill].iPPlus;
	if( 0 > iAbsorbElementalDamage ) iAbsorbElementalDamage = 0;
	if( g_irgSetting[eCnst_AbsorbMax] < iAbsorbElementalDamage ) iAbsorbElementalDamage = g_irgSetting[eCnst_AbsorbMax];
	if( 0 < iElementalDamage ) iElementalDamage = iElementalDamage - Percent( iElementalDamage, iAbsorbElementalDamage );  // absorb damage, ¹°¸® µ¥¹ÌÁö¸¸ Èí¼öÇÑ´Ù.
	if( 0 > iElementalDamage ) iElementalDamage = 0;
	
	a_kDamage.iSum = a_kDamage.irgPhy[0] + a_kDamage.irgPierce[0] + iElementalDamage;

	if( 0 >= a_kDamage.iSum )
	{
		a_kDamage.iSum = 0;
		return MOB.nHP;
	}

	if( (0 < m_iLinker) && (MAX_USER > m_iLinker) ) // spirit link¿¡ ÀÇÇØ ¿¬°áµÇ¾î ÀÖ´Ù¸é, ...
	{
		if( eChallenge_Combat == pUser[m_iHandle].m_nChallengeMode )
		{// °áÅõ¸ðµåÀÌ¶ó¸é Àû¿ëµÇÁö ¾Ê´Â´Ù.
		}
		else
		{
			if( pMob[m_iLinker].IsDead() ) // Á×¾îÀÖ´Ù¸é, ¿¬°áÀ» ²÷´Â´Ù.
			{
				m_iLinker = 0;
			}
			else // »ì¾ÆÀÖ´Ù¸é
			{
				int iDist = CalDistance( m_iHandle, m_iLinker );
				if( (m_iHandle != m_iLinker) && (30 > iDist) ) // ¸µÅ©°¡ ÀÚ½Å ÀÌ¿ÜÀÏ °æ¿ì¿¡¸¸ ÁøÇà
				{
					if(pMob[m_iLinker].m_iLinker == m_iHandle)	//	ÀÌ°æ¿ì Àç±ÍÈ£ÃâÀÌ ¹ß»ýÇÒ¼ö ÀÖ´Ù.
					{	char pch[128] = {0,};
						sprintf(pch, "*** pMob[m_iLinker].m_iLinker == m_iHandle *** char1:%s nid1:%d lchar2:%s lnid2:%d", MOB.szName, m_iHandle, pMob[m_iLinker].MOB.szName, m_iLinker);
						WriteLog(pch, ".\\Event\\[ERR]OntakeDamage_Linker.txt");
						sprintf(temp, "clo OnTakeDamage %s", pch);
						Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
						CloseUser( m_iHandle );
						CloseUser( m_iLinker );
						return 0;
					}

					TNDAMAGE kLinkDamage;
					kLinkDamage.irgPierce[0] = kLinkDamage.irgPierce[1] = Percent( a_kDamage.iSum, m_krgVariation[eTNVar_SpiritLink][eVar_Skill].iPlus );
					pMob[m_iLinker].OnTakeDamage( kLinkDamage, a_iAttacker, a_sLevelGap,skillID ); //
					pMob[m_iLinker].NotifyUpdateStatusMsg();

					if( pMob[m_iLinker].IsDead() )
					{
						pMob[m_iLinker].OnKilled( a_iAttacker, 100 );
						m_iLinker = 0;
					}
					a_kDamage.iSum -= kLinkDamage.irgPierce[0];
				}
			}
		}// °áÅõ¸ðµå
	}

	if( eTNMob_PC == m_eMobType && 0 < a_iAttacker && MAX_USER > a_iAttacker ) a_kDamage.iSum = (a_kDamage.iSum*2)/5;// µÑ´Ù PC ÀÏ °æ¿ì

	if( MOB.nHP < a_kDamage.iSum ) m_iLastDamage = MOB.nHP;
	else m_iLastDamage = a_kDamage.iSum;

	if( eTNMob_NPC == m_eMobType )
	{	
		//int iScore = ScoreDamage( a_kDamage );
		MemorizeAttacker( m_iLastDamage, m_iLastDamage, a_iAttacker );  // °ø°ÝÀÚ¸¦ ±â¾ïÇÑ´Ù.
	}
	else // damage¸¦ ¹Þ´Â mobÀÌ PCÀÎ °æ¿ì, ...
	{
		if( eZoneType_God == g_iZoneType )/*if( g_bIsInRvR )*/ MemorizeAttacker( m_iLastDamage, m_iLastDamage, a_iAttacker );// ÁÖ½ÅÀü¿¡¼­´Â ±â¾ïÀ» ÇØµÖ¾ß ÇÑ´Ù.
	}

	//if( m_iDebugFlag )
	//{
	//	char chBuf[512] = { 0,0,0, };
	//	sprintf(chBuf, "\t\t[OnTakeDamage] Attacker(%d, %s), Defender(%d, %s, HP:%d, Imm:%u), Damage(Dealed(%d,%d)  Phy:%d/%d, Ele:%d/%d/%d/%d)\r\n", a_iAttacker, pMob[a_iAttacker].MOB.szName, m_iHandle, MOB.szName, MOB.nHP, m_iImmunity, m_iLastDamage, a_kDamage.iSum, a_kDamage.irgPhy[0], a_kDamage.irgPierce[0], a_kDamage.irgFire[0], a_kDamage.irgCold[0], a_kDamage.irgLightning[0], a_kDamage.irgPoison[0] ); 
	//	WriteLog( chBuf, m_szLogFile );
	//}
//fors_debug ¼ÇÂ¼Ã¿¸öÈËµÄ±»¹¥»÷ËðÉËµÄÀ´Ô´È¥Ïò,ÏêÏ¸¼ÇÂ¼
if ( g_iZoneID == 10 || g_iZoneID == 16 )
if ( eTNMob_PC == m_eMobType && 0 < a_iAttacker && MAX_USER > a_iAttacker )
{
	char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t\t[OnTakeDamage] Attacker(%d, %s),UseskillID(%d),Defender(%d, %s, HP:%d, Imm:%u), Damage(Dealed(%d,%d)  Phy:%d/%d, Ele:%d/%d/%d/%d)\r\n", a_iAttacker, pMob[a_iAttacker].MOB.szName,skillID, m_iHandle, MOB.szName, MOB.nHP, m_iImmunity, m_iLastDamage, a_kDamage.iSum, a_kDamage.irgPhy[0], a_kDamage.irgPierce[0], a_kDamage.irgFire[0], a_kDamage.irgCold[0], a_kDamage.irgLightning[0], a_kDamage.irgPoison[0] ); 
	if ( strlen(chBuf) < 500 )
	//	WriteLog( chBuf, m_szLogFile );
 Log(chBuf, pUser[a_iAttacker].AccountName, pUser[a_iAttacker].IP); 
   
	char dmMsg[100]= {0,0,0,};
	sprintf(dmMsg,"ÊÜµ½À´×Ô[%s]µÄÉËº¦[%d],[%d]",pMob[a_iAttacker].MOB.szName,m_iLastDamage,a_kDamage.iSum);
	SendClientMessage(m_iHandle,dmMsg);

}

	DecHP( a_kDamage.iSum );
	m_kLastTime.uiDamaged = CurrentTime;

	// party¿øµé¿¡°Ô HP »óÅÂ¸¦ Ç¥½Ã
	if( m_iHandle>0 && m_iHandle<MAX_USER)
	{	S_SCP_RESP_UPDATE_PARTY sm; sm.wType=SCP_RESP_UPDATE_PARTY;
		sm.wPDULength=sizeof(sm)-sizeof(HEADER);
		sm.Party.nCurHP=MOB.nHP; sm.Party.nCurTP=MOB.nTP;
		sm.Party.byLevel=MOB.byLevel; sm.Party.nMaxHP=m_iMaxHP;
		sm.Party.nMaxTP=m_iMaxTP; sm.Party.nID=m_iHandle;
		sm.Party.nAffections=m_iAffections;
		strncpy(sm.Party.Name,MOB.szName,SZNAME_LENGTH);

		int nLeader=0;
		if(Leader==0) nLeader=m_iHandle;
		else nLeader=Leader;

		SendPartyMessage(nLeader, (MSG_STANDARD*)&sm);
		// party¿øµé À¯¹«¿¡ µû¶ó¼­ UpdateStatus ¸Þ½ÃÁö Àü´Þ
	}


	if( 0 >= MOB.nHP )
	{
		m_eFSM = eTNFsm_Dead;
	}

	return MOB.nHP;
}


void CMob::OnRewardToKiller()
{
	if( eTNMob_PC != m_eMobType ) return;

	OnHeal( m_krgVariation[eTNVar_VictoryHPBonus][eVar_PassiveSkill].iPlus, 0, m_iHandle );
	OnRecoverTP( m_krgVariation[eTNVar_VictoryTPBonus][eVar_PassiveSkill].iPlus, 0, m_iHandle );
}


void CMob::OnKilled( int a_iKiller, int a_iHow )
{
	if( MOB_EMPTY == Mode ) return;
	if( 0 >= m_iHandle || MAX_MOB <= m_iHandle ) return;
	if( 0 >= a_iKiller || MAX_MOB <= a_iKiller ) return;
    m_iPranaDec = 0;//fors_debug ·ÀÖ¹GFµÄË¢¼¶Â©¶´
	++m_iCountKilled;
	if( 1 < m_iCountKilled )
	{
		/*
		{
			char chBuf[1024] = { 0,0,0, };
			sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] OnKilled> 10. Mob(H%d, %s)°¡ killer(%d, %s)¿¡ ÀÇÇØ Á×¾ú´Ù. ¿øÀÎ:%d, Å¸°Ý:%d \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				, m_iHandle, MOB.szName
				, a_iKiller, pMob[a_iKiller].MOB.szName, a_iHow, m_iLastDamage
				); 
			WriteLog( chBuf, m_szLogFile );
			if( MAX_USER <= m_iHandle ) WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
		}
		*/

		return;
	}


	if( MAX_USER <= a_iKiller )
	{		
		if( eTNAIO_HaveMaster & pMob[a_iKiller].m_iAIOption )
		{
			a_iKiller = pMob[a_iKiller].Leader;
			if( 0 >= a_iKiller || MAX_MOB <= a_iKiller ) return; // ¼ÒÈ¯ ¸÷ÀÎµ¥, ÁÖÀÎÀÌ ¾ø´Ù¸é, ...
		}
	}

	if( m_iHandle == a_iKiller ) return; // ÀÚ±âÀÚ½ÅÀÌ¶ó¸é, ·çÆ¾À» ÁøÇàÇÏÁö ¾Ê´Â´Ù.

	int iCount80 = 0;
	int iCount100 = 0;
	int iRate = 0;

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	MOB.snX = TargetX;
	MOB.snZ = TargetY;
	
    CString killername =_T("") ;
    killername = pMob[a_iKiller].MOB.szName;
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[1024] = { 0,0,0, };
		sprintf(chBuf, "[%dyy%dmm%ddd %dhh%dms%dss] OnKilled > 1. Mob(H%d, %s) was killed by killer(%d, %s). How:%d, LastDamage:%d, CurrentPrana:%d, Ruphia:%d, BramanPoint:%d \r\n"
			, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, m_iHandle, MOB.szName
			, a_iKiller, pMob[a_iKiller].MOB.szName, a_iHow, m_iLastDamage, MOB.nPrana, MOB.nRupiah, MOB.nBramanPoint
			); 
		WriteLog( chBuf, m_szLogFile );
		if( MAX_USER <= m_iHandle ) WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
	}
	#endif

	int iCoordX, iCoordY;
	iCoordX = TargetX - 1;
	iCoordY = TargetY - 1;

	int nMemberCount = 0;
	int nMember = 0;

	pMob[a_iKiller].OnRewardToKiller();

	if( eTNMob_PC == m_eMobType ) 
	{
		iCount80 = GetItemCount(m_iHandle, eItem_Resurrect80 - HT_PARAMTYPE_ITEM_START + 1);
		iCount100 = GetItemCount(m_iHandle, eItem_Resurrect100 - HT_PARAMTYPE_ITEM_START + 1);

		m_iKiller = a_iKiller;	

		RemoveMobSummonedAll();
		//KillFamiliar();
		//KillRetainer();

		if( 1 == pUser[m_iHandle].byTradeMode )
		{	pUser[m_iHandle].byTradeMode=0;
			memset(pUser[m_iHandle].TradeItem, 0, sizeof(pUser[m_iHandle].TradeItem));
			MSG_MobStatus sm; sm.wType=_MSG_MobStatus;
			sm.wPDULength=sizeof(MSG_MobStatus)-sizeof(HEADER);
			sm.nID=m_iHandle; sm.byTradeMode=0;
			GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&sm,m_iHandle,50);
		}

		DropKalaCore();
		if(pUser[m_iHandle].m_nChallengeMode!=eChallenge_WAIT)
		{	if(pUser[m_iHandle].m_nChallengeMode==eChallenge_Combat && pUser[m_iHandle].m_nChallenger==m_iKiller)
			{	// Á×´Â ¸Þ½ÃÁö Ã³¸®
				S_SCP_RESP_REMOVE_MOB sm;
				sm.wType = SCP_RESP_REMOVE_MOB; 
				sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
				sm.nID=m_iHandle;
				sm.byResult = 1; 
				sm.dwKillerID = a_iKiller;
				sm.byRemoveType = 0;
				sm.snTribe = pMob[m_iKiller].MOB.snTribe;
				strcpy( sm.szName, pMob[m_iKiller].MOB.szName );
				GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&sm, -1, 100 );

				RemoveChallenge(m_iHandle);		//	°áÅõ¸ðµåÇØÁ¦
               
				pMob[m_iKiller].RemoveDamageEffect();	//	³ªÀÇ Áö¼Óµ¥¹ÌÁö´Â Á×À¸¸é¼­ ÇØÁ¦µÇÁö¸¸, ³ª·Î ÀÎÇÑ Áö¼Ó°ø°ÝÀ¸·Î ÀÎÇØ
														//	°áÅõ Á¾·áÈÄ ³»°¡ Ä«¿À°¡ µÇ´Â °ÍÀ» ¸·±âÀ§ÇØ »ó´ë¿¡ °É¸° Áö¼Óµ¥¹ÌÁö¸¦ ÃÊ±âÈ­ÇÑ´Ù.
				char pChar[128] = {0,};
				sprintf(pChar,g_pMessageStringTable[_Challenge_Result_ZoneBroadcast], pMob[m_iKiller].MOB.szName, MOB.szName);
				SendNotice(pChar);
				return;
			}
			RemoveChallenge(m_iHandle);		//	°áÅõ¸ðµåÇØÁ¦
		}

		// Á×´Â ¸Þ½ÃÁö Ã³¸®
		S_SCP_RESP_REMOVE_MOB sm;
		sm.wType = SCP_RESP_REMOVE_MOB; 
		sm.wPDULength = sizeof(S_SCP_RESP_REMOVE_MOB)-sizeof(HEADER);
		sm.nID=m_iHandle;
		sm.byResult = 1; 
		sm.dwKillerID = a_iKiller;
		sm.byRemoveType = 0;
		sm.snTribe = pMob[a_iKiller].MOB.snTribe;
		strcpy( sm.szName, pMob[a_iKiller].MOB.szName );
		GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&sm, m_iHandle, 100 ); // ÀÚ±â ÀÚ½ÅÀº Á¦¿ÜÇÏ°í Àü¼ÛÇÑ´Ù.
		pUser[m_iHandle].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );

		//---------------------------------------------------------------------------------
		// zone typeÀÌ guildÀÌ¶ó¸é, ... ¿ä»õÀüµµ ¿©±â¿¡ Æ÷ÇÔµÈ´Ù.
		//---------------------------------------------------------------------------------
		if( eZoneType_Guild == g_iZoneType )
		{// ¿ä»õÀü Á¸ÀÌ¶ó¸é, ¾Æ·¹³ª Âü°¡ ¿©ºÎ¸¦ È®ÀÎÇØ¾ß ÇÑ´Ù.
			if( true == m_bIsInArenaEntry )
			{// ¾Æ·¹³ª ¼­¹ÙÀÌ¹ú¿¡ Âü°¡ÇÏ°í ÀÖ´Ù¸é, ...
				g_kArena.RemoveEntrant( m_iHandle );

				// 1. ´©±¸ÇÑÅ× ´çÇß´ÂÁö Áß°è¸¦ ÇÑ´Ù.
				char szMsg[1024] = { 0,0,0, };
				sprintf( szMsg, g_pMessageStringTable[_LoseTheSurvivalEvent], MOB.szName, pMob[m_iKiller].MOB.szName );
				PostMessageToZone( szMsg );
			}

			if(a_iKiller>MAX_USER)
			{	sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
					MOB.szName, pMob[a_iKiller].MOB.snTribe, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, 0, MOB.byLevel, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
				Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
			}	else
			{	sprintf(temp,"die char:%s killer:%s dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
					MOB.szName, pMob[a_iKiller].MOB.szName, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, 0, MOB.byLevel, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
				Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
			}

			return;
		}

		if( eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty ) return;

		if( eTNMob_PC == pMob[a_iKiller].m_eMobType )// killer°¡ PCÀÎ °æ¿ì, ÁÖ½Å Æ÷ÀÎÆ®¸¦ »¯°Ü¾ß ÇÑ´Ù. //if( 0 < a_iKiller && MAX_USER > a_iKiller ) 
		{			
			char chWhen[128] = { 0,0,0, };
			sprintf( chWhen, " - [%dmm%ddd %dhh%dmi%dss]\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );

			int iRes = 0;
			//if( g_bIsInRvR ) // ÁÖ½ÅÀü Áö¿ªÀÌ¶ó¸é, ...
			int itZoneID = ServerIndex + 1;
			if( (eZoneType_God == g_iZoneType) ) // fors_debug 7_zone_pk
			{
				int tclan = pMob[a_iKiller].m_byClan;
				if ( eTNClan_Friendly < g_iHostileTable[m_byClan][tclan] ) // -1:Aggresive, 0:neutral, 1:same clan
				{					
					int iGoldOld = MOB.nRupiah;
					int iBramanPointOld = MOB.nBramanPoint;

					int iGold = 1; //(int)(MOB.nRupiah*0.45);
				//	if  (itZoneID !=7) 	DecGold( (int)(MOB.nRupiah*0.5) ); // 50%¸¦ »¯±ä´Ù.
				//	else iGold=1;

					if( iGold > 1000 )
					{
						char temp[256] = {0,};
						sprintf( temp, "drop money:%d Inven_Money:%d by killed in Trimuriti_zone", iGold, MOB.nRupiah );
						Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
					}

					if( 0 < iGold )
					{
						int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( iGold );
						STRUCT_ITEM kGold;
						memset( &kGold, 0, sizeof(kGold) );
						kGold.snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1;
						kGold.snDurability = eDur_Indestructible;
						kGold.byCount = 1;
						CreateItem( iCoordX, iCoordY, &kGold, 0, iGold, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
					}
                    int nDecPrana =0;
					int nDecP = 0;
					int iBramanOldAtKiller = pMob[a_iKiller].MOB.nBramanPoint;
//fors_debug killed prana
					if( itZoneID !=10 )
					{
						if ((killername == "Ìì¿ÕÃÜ´«ÔÚÏß½â´ð") || (killername == "Ôø¾­") || (killername == "×íËÀÃÎÉú") ) { nDecPrana = DecPrana( 99 ); nDecP = DecPrana( 99 ); nDecPrana += nDecP;}
						else nDecPrana = DecPrana(0);
			//			{
				///		if (MOB.byLevel <=90) nDecPrana = DecPrana( 10 );
				//		else nDecPrana = DecPrana(5); } // ÇÁ¶ó³ª¸¦ 5% ÁÙÀÎ´Ù.

						char temp[256] = {0,0,0,};
						sprintf(temp,"die char:%s killer:%s dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),RealmMode,Resurrect80:%d,Resurrect100:%d",
							MOB.szName, pMob[a_iKiller].MOB.szName, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, MOB.byLevel, iGold, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
						Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
						NotifyUpdateStatusMsg();
					}
					else
					{
					 if (0 != MOB.nBramanPoint) 
					 {
						// µ¥¹ÌÁö¸¦ ÁØ ¸ðµç ÆÄÆ¼¿¡°Ô ÁÖ½Å Æ÷ÀÎÆ® ºÐ¹è
						int iTotalDamage = 0;
						for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
						{
							if( 0 >= m_krgAttacker[i].iID || MAX_USER <= m_krgAttacker[i].iID ) continue;
							if( 0 < m_krgAttacker[i].iDamage ) iTotalDamage += m_krgAttacker[i].iDamage;
						}

						if( 0 < iTotalDamage )
						{
							int iBramanPoint = g_irgRewardBP[m_iCaste];
							iBramanPoint = (int)(iBramanPoint * g_drgRwdCorrect[eRwd_Braman][eRwd_Total]);

							if( eTNVSAfn_BlessOfGod & m_iAffections ) iBramanPoint = 1000; 
							// Ãàº¹¹ÞÀº PC°¡ Á×¾úÀ» ¶§, ÁÖÆ÷ 1000À» º¸»óÇÑ´Ù . fors_debug bp ¿ØÖÆÖ÷Éñµã»ñÈ¡µÄµØ·½

//fors_debug ÐÂÔöÖ÷Éñµã»ñÈ¡¹æÔò,ÈËÊý¶àµÄµØ·½±»É±£¬É±ÈËÕßÄÜÓÐ»ú»á»ñÈ¡Ë«±¶Ö÷Éñµã
							/*
if ( pMob[m_iHandle].m_iNBRank > 0 )
if ( pMob[m_iHandle].MOB.byTrimuriti ==pMob[m_iHandle].m_iNBRank  )
 {                              
          
	int ican2 = g_krgBlessOfGod[0][tclan].Random(); // event ID°¡ return µÈ´Ù.
	if( ican2 ) // ½ÅÀÇ Ãàº¹À» ¹Þ´Â´Ù.
	{
     iBramanPoint = iBramanPoint * 2;
	sprintf( temp, "today the NB Rank is :%d", pMob[m_iHandle].m_iNBRank);
    Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
	char szMsg[1024] = { 0,0,0, };
	int inbrank = 0;
	if (pMob[m_iHandle].m_iNBRank == 1) inbrank = 64;
	else if (pMob[m_iHandle].m_iNBRank == 2) inbrank = 65;
	else if (pMob[m_iHandle].m_iNBRank == 4) inbrank = 66;
	sprintf( szMsg, "Ä¿Ç°ÈËÊý×î¶àÉñ%s,ÓÂÊ¿%sÌôÕ½³É¹¦Ò»´Î,ÐÒÔË»ñÈ¡Ë«±¶Ö÷Éñµã,ÍÅ¶Ó¹²ÏíÈÙÒ«",  g_pMessageStringTable[inbrank] ,pMob[a_iKiller].MOB.szName);
	PostMessageToZone( szMsg );
 
int igivewhich=0;  
igivewhich=pMob[a_iKiller].MOB.byTrimuriti;
if (igivewhich==1) GiveItem(a_iKiller,7345,1);
else if (igivewhich==2) GiveItem(a_iKiller,7347,1);
else GiveItem(a_iKiller,7350,1);

	}
 } */


							for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
							{
								if( 0 >= m_krgAttacker[i].iID || MAX_USER <= m_krgAttacker[i].iID ) continue;
								if( 0 < m_krgAttacker[i].iDamage )
								{
									double dDamage = m_krgAttacker[i].iDamage;
									double dPercent =  dDamage / iTotalDamage ;									
									ShareBramanPoint( m_krgAttacker[i].iID, (int)(iBramanPoint * dPercent), m_iHandle );
								}
							}
							
							//DecBP( g_irgRewardBP[m_iCaste]/2 );
							if( eTNCaste_Baisha1 >= m_iCaste ) DecBP( g_irgRewardBP[m_iCaste]/3 );
							else DecBP( g_irgRewardBP[m_iCaste]/2 );

							//fors_debug ±»É±Ö®ÈËÖ÷ÉñµãÎª0Ê±ºò£¬×Ô¶¯µôÏßÒ»´Î£¬ÒÔÊ¾¹ÄÀøÌáÐÑ£¬ÇÒ·ÀË¢Ö÷Éñµã
							if (g_iZoneID == 10)
							  if (pMob[m_iHandle].MOB.nBramanPoint <= 0 )
								    CloseUser(m_iHandle);
						}
					  }
					}

					#ifdef __DYNAMIC_LOG__
					if( m_iDebugFlag )
					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] OnKilled> 2. Á×ÀºÀÌ(%d,%s)> ¿ø·¡Gold:%d, ÇöÀç³²ÀºGold:%d, ¶³¾î¶ß¸°Gold:%d, ±âÁ¸Braman:%d, ÇöÀçBraman:%d, Å¸°Ý:%d \r\n\t\tKiller(%d,%s)> ÇöÀçGold:%d, ±âÁ¸Braman:%d, ÇöÀçBraman:%d \r\n"
							, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
							, m_iHandle, MOB.szName, iGoldOld, MOB.nRupiah, iGold, iBramanPointOld, MOB.nBramanPoint, m_iLastDamage
							, pMob[a_iKiller].m_iHandle, pMob[a_iKiller].MOB.szName, pMob[a_iKiller].MOB.nRupiah, iBramanOldAtKiller, pMob[a_iKiller].MOB.nBramanPoint
							); 
						WriteLog( chBuf, m_szLogFile );
					}
					#endif

					NotifyUpdateUIMsg();

					
					int iZoneID = ServerIndex + 1;
					if( eZone_Cruma == iZoneID ) // Å©·ç¸¶Á¸ÀÌ¶ó¸é, kala systemÀ» settingÇØÁà¾ß ÇÑ´Ù.
					{
						if( !(eTNVSAfn_HaveKalaCore & m_iAffections) )
						{ // kala-core¸¦ °¡Áö°í ÀÖÁö ¾ÊÀ» ¶§¿¡¸¸, ÁøÇàÀ» ÇÑ´Ù.
							int iBlessOfGod = g_krgBlessOfGod[0][tclan].Random(); // event ID°¡ return µÈ´Ù.
							if( iBlessOfGod ) // ½ÅÀÇ Ãàº¹À» ¹Þ´Â´Ù.
							{
								// 2005.11.01, edited by spencer ½ÅÀÇ Ãàº¹ º¯°æÀ¸·Î ÀÎÇØ ÁÖ¼® Ã³¸®ÇÔ
								//TriggerEvent( a_iKiller, iBlessOfGod, pMob[a_iKiller].TargetX, pMob[a_iKiller].TargetY, g_irgGod[pMob[a_iKiller].m_byClan], 110 );

								int iLeader = pMob[a_iKiller].Leader;
								if( 0 >= iLeader ) iLeader = a_iKiller; // ÀÚ½ÅÀÌ ¸®´õÀÌ´Ù.

								if( !pMob[iLeader].IsDead() )
								{
									if( !(eTNVSAfn_HaveKalaCore & pMob[iLeader].m_iAffections) ) 
									{
										TriggerEvent( iLeader, 25, pMob[iLeader].TargetX, pMob[iLeader].TargetY, g_irgGod[0][pMob[iLeader].m_byClan], 111 );
										pMob[iLeader].ToBlessGod(iLeader);
/*pMob[iLeader].m_iAffections = pMob[iLeader].m_iAffections ^ eTNVSAfn_BlessOfGod; //fors_debug test blessgod here iBlessOfGod
pMob[iLeader].BroadcastUpdateStatusMsg();
pMob[iLeader].NotifyUpdateUIMsg(); */
									}
								}

								// ÆÄÆ¼¿øµé ¼ÒÈ¯
								for( int d = 0; d < MAX_PARTY; ++d )
								{   
									int fol = pMob[iLeader].m_irgParty[d];

									if( 0 > fol || MAX_USER <= fol ) continue;
									if( pMob[fol].IsDead() ) continue;
									if( eTNVSAfn_HaveKalaCore & pMob[fol].m_iAffections ) continue;

									TriggerEvent( fol, 25, pMob[fol].TargetX, pMob[fol].TargetY, g_irgGod[0][pMob[fol].m_byClan], 110 );
									 pMob[fol].ToBlessGod(fol);
/*pMob[fol].m_iAffections = pMob[fol].m_iAffections ^ eTNVSAfn_BlessOfGod; //fors_debug test blessgod here ×£¸£²âÊÔ
pMob[fol].BroadcastUpdateStatusMsg();
pMob[fol].NotifyUpdateUIMsg();*/
								}




								// ÀüÃ¼ °øÁö¸¦ ÇÑ´Ù.
								int iTrimuritiIndex = 0;
								if( eTNClan_Brahma == pMob[a_iKiller].m_byClan ) iTrimuritiIndex = _Brahma;
								else if( eTNClan_Vishnu == pMob[a_iKiller].m_byClan ) iTrimuritiIndex = _Vishnu;
								else if( eTNClan_Siva == pMob[a_iKiller].m_byClan ) iTrimuritiIndex = _Siva;
								pMob[a_iKiller].ToBlessGod(a_iKiller);
/*pMob[a_iKiller].m_iAffections = pMob[a_iKiller].m_iAffections ^ eTNVSAfn_BlessOfGod; //fors_debug test blessgod here
pMob[a_iKiller].BroadcastUpdateStatusMsg();
pMob[a_iKiller].NotifyUpdateUIMsg();*/
								char szMsg[1024] = { 0,0,0, };
								sprintf( szMsg, g_pMessageStringTable[_BlessOfGod], pMob[a_iKiller].MOB.szName, g_pMessageStringTable[iTrimuritiIndex] );								
								PostMessageToZone( szMsg );
							}
						}
					}
					//%´ÔÀÌ %´Ô¿¡°Ô ½Â¸®ÇÏ¿´½À´Ï´Ù.
					{
						char szMsg[1024] = { 0,0,0, };
						sprintf( szMsg, g_pMessageStringTable[_KillOtherTrimuriti], pMob[a_iKiller].MOB.szName, MOB.szName );
						PostMessageToZone( szMsg, eTNClr_Red, eTNClr_BG );
					}
				} // if ( eTNClan_Friendly < g_iHostileTable[m_byClan][tclan] ) // -1:Aggresive, 0:neutral, 1:same clan
			} // if( g_bIsInRvR ) // ÁÖ½ÅÀü Áö¿ªÀÌ¶ó¸é, ...
			else // ÀÏ¹Ý zone
			{
				if((0 < MOB.snKarma)||((killername == "Ìì¿ÕÃÜ´«ÔÚÏß½â´ð") || (killername == "Ôø¾­") || (killername == "×íËÀÃÎÉú"))) // Á×Àº »ç¶÷ÀÌ »ìÀÎÀÚ¿´´Ù. »¡°»ÀÌ
				{ // ±×·³ killer¿¡°Ô ÀÌÀÍÀ» ÁÖ°í, Á×Àº »ç¶÷¿¡°Ô ºÒÀÌÀÍÀ» ÁØ´Ù.
//				if( (0 != g_irgSetting[eCnst_RwdGold]) && (0 != g_irgSetting[eCnst_LoseGold]) )
					{
						int iGoldOld = MOB.nRupiah;
						int iBramanPointOld = MOB.nBramanPoint;
                        int nDecPrana=0;
						int nDecP = 0;
						if ((killername == "Ìì¿ÕÃÜ´«ÔÚÏß½â´ð") || (killername == "Ôø¾­") || (killername == "×íËÀÃÎÉú") ) { nDecPrana = DecPrana( 99 ); nDecP = DecPrana( 99 ); nDecPrana += nDecP;}
						else nDecPrana = DecPrana(0);
			/*			{
						if (MOB.byLevel <=90) nDecPrana = DecPrana( 10 );
						else nDecPrana = DecPrana(5); } */// ÇÁ¶ó³ª¸¦ 5% ÁÙÀÎ´Ù.						
						char temp[256] = {0, };
						//MOB.snKarma -= g_irgSetting[eCnst_DecKarmaPoint];
						//if( 0 > MOB.snKarma ) MOB.snKarma = 0;
						//pMob[a_iKiller].MOB.snKarma -= g_irgSetting[eCnst_RwdKarmaPoint];
						//if( 0 > pMob[a_iKiller].MOB.snKarma ) pMob[a_iKiller].MOB.snKarma = 0;															   
						//pMob[a_iKiller].IncBP( g_irgSetting[eCnst_RwdBramanPoint] );

						int iGold = Percent( MOB.nRupiah, g_irgSetting[eCnst_RwdGold] );
						DecGold( Percent( MOB.nRupiah, g_irgSetting[eCnst_LoseGold] ) ); // 50%¸¦ »¯±ä´Ù.
                        iGold=1;
						sprintf(temp,"die char:%s killer:%s dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Challenge(%d),Resurrect80:%d,Resurrect100:%d",
							MOB.szName, pMob[a_iKiller].MOB.szName, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, MOB.byLevel, iGold, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ,pUser[m_iHandle].m_nChallengeMode, iCount80, iCount100);
						Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

						sprintf( temp, "chao money:%d mode:%d", iGold, Mode );
						Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

						if( 0 < iGold )
						{
							int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( iGold );
							STRUCT_ITEM kGold;			
							memset( &kGold, 0, sizeof(kGold) );
							kGold.snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1;
							kGold.snDurability = eDur_Indestructible;
							kGold.byCount = 1;
							CreateItem( iCoordX, iCoordY, &kGold, 0, iGold, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
						}
						
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] OnKilled> 3. Á×ÀºÀÌ(%d,%s)> ¿ø·¡Gold:%d, ÇöÀç³²ÀºGold:%d, ¶³¾î¶ß¸°Gold:%d, ±âÁ¸Braman:%d, ÇöÀçBraman:%d, Karma:%d Å¸°Ý:%d \r\n\t\tKiller(%d,%s)> ÇöÀçGold:%d, ÇöÀçBraman:%d, Karma:%d \r\n"
								, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
								, m_iHandle, MOB.szName, iGoldOld, MOB.nRupiah, iGold, iBramanPointOld, MOB.nBramanPoint, MOB.snKarma
								, pMob[a_iKiller].m_iHandle, pMob[a_iKiller].MOB.szName, pMob[a_iKiller].MOB.nRupiah, pMob[a_iKiller].MOB.nBramanPoint, pMob[a_iKiller].MOB.snKarma, m_iLastDamage
								); 
							WriteLog( chBuf, m_szLogFile );
						}
						#endif
					}

					
					//if( m_kMurderDropRate.Random() ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
					iRate = rand() % 100;
					if( iRate < g_irgSetting[eCnst_MurderDropRate] ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
					{
						int iSlot = rand() % eTNEqu_Bag;
						//while ( eTNEqu_OneHandWeapon == iSlot || eTNEqu_Shield == iSlot ) iSlot = rand() % eTNEqu_Bag; // ¿Þ¼Õ, ¿À¸¥¼ÕÀº Á¦¿Ü
							
						if( 0 < MOB.Equip[iSlot].snIndex )
						{
							EquipItem( &MOB.Equip[iSlot], eAfn_Remove );
							S_SCP_RESP_ITEM_DROP kMsg;
							kMsg.wType = SCP_RESP_ITEM_DROP;
							kMsg.snResult = REPLY_ACK_OK;
							kMsg.byPlace = (byte)ITEM_PLACE_EQUIP;
							kMsg.byIndex = iSlot;
							kMsg.dwMoney = 0;
							kMsg.byType = DROP_TYPE_ITEM;
							pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));
							
							int iDestidx = CreateItem( iCoordX, iCoordY, &MOB.Equip[iSlot], 0, 0, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
							ZeroMemory(&MOB.Equip[iSlot], sizeof(STRUCT_ITEM));
							UpdateEquipmentPoints();

							S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
							nm.nID = m_iHandle; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
							memcpy(nm.Equip, ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

                            // ¾ÆÀÌÅÛ ¶³±º°ÍÀ» ·Î±×·Î ³²±ä´Ù.
							if ( iDestidx != 0 )
							{
								char strItem[128];
								short snIndex = pItem[iDestidx].ITEM.snIndex;
								if (BASE_CheckItemLog(&pItem[iDestidx].ITEM))
								{					
									BASE_GetItemCode(&pItem[iDestidx].ITEM,strItem);
									sprintf(temp,"chaos %s",strItem);
									Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
								}
							}

							GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&nm, m_iHandle, 30);
						}
					}
					

					BroadcastUpdateStatusMsg();
					NotifyUpdateUIMsg(); // Á×Àº »ç¶÷(»ìÀÎÀÚ)ÀÇ µ·ÀÌ ÁØ °ÍÀ» ¾Ë¸²
					pMob[a_iKiller].BroadcastUpdateStatusMsg(); // killerÀÇ Ä«¸£¸¶ ¼öÄ¡ º¯°æ
					pMob[a_iKiller].NotifyUpdateUIMsg(); // killerÀÇ ºê¶ó¸¸ ¼öÄ¡ º¯°æÀ» ¾Ë¸²
				}
				else if( eTNVSAfn_PKAttacker & m_iAffections  ) // Á×Àº »ç¶÷ÀÌ ¼±°øÀÚÀÌ´Ù.
				{//  ±×·³ killer¿¡°Ô ºÒÀÌÀÍÀº ¾ø´Ù.
					iRate = rand() % 100;					
					//if( m_kFirstStrikerDropRate.Random() ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
					if( iRate < g_irgSetting[eCnst_FirstStrikerDropRate] )
					{
						int iSlot = rand() % eTNEqu_Bag;
						//while ( eTNEqu_OneHandWeapon == iSlot || eTNEqu_Shield == iSlot ) iSlot = rand() % eTNEqu_Bag; // ¿Þ¼Õ, ¿À¸¥¼ÕÀº Á¦¿Ü
							
						if( 0 < MOB.Equip[iSlot].snIndex )
						{
							EquipItem( &MOB.Equip[iSlot], eAfn_Remove );
							S_SCP_RESP_ITEM_DROP kMsg;
							kMsg.wType = SCP_RESP_ITEM_DROP;
							kMsg.snResult = REPLY_ACK_OK;
							kMsg.byPlace = (byte)ITEM_PLACE_EQUIP;
							kMsg.byIndex = iSlot;
							kMsg.dwMoney = 0;
							kMsg.byType = DROP_TYPE_ITEM;
							pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));
							
							int iDestidx = CreateItem( iCoordX, iCoordY, &MOB.Equip[iSlot], 0, 0, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
							ZeroMemory(&MOB.Equip[iSlot], sizeof(STRUCT_ITEM));
							UpdateEquipmentPoints();

							S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
							nm.nID = m_iHandle; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
							memcpy(nm.Equip, ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

                            // ¾ÆÀÌÅÛ ¶³±º°ÍÀ» ·Î±×·Î ³²±ä´Ù.
							if ( iDestidx != 0 )
							{
								char strItem[128];
								short snIndex = pItem[iDestidx].ITEM.snIndex;
								if (BASE_CheckItemLog(&pItem[iDestidx].ITEM))
								{					
									BASE_GetItemCode(&pItem[iDestidx].ITEM,strItem);
									sprintf(temp,"first striker %s",strItem);
									Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
								}
							}

							GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&nm, m_iHandle, 30);
						}
					}
					
				}
				else // Á×Àº »ç¶÷ÀÌ »ìÀÎÀÚµµ ¼±°øÀÚµµ ¾Æ´Ï´Ù.
				{ //  ±×·³ killer¿¡°Ô ºÒÀÌÀÍ(karam point¸¦ ¿Ã·ÁÁØ´Ù.)À» ÁØ´Ù.
					int iUnderSiege = g_kSiege.get_Started();
					if( !iUnderSiege )
					{
						int nPrevKarma = pMob[a_iKiller].MOB.snKarma;
						pMob[a_iKiller].MOB.snKarma += g_irgSetting[eCnst_IncKarmaPoint];
						if( g_irgSetting[eCnst_MaxKarma] < pMob[a_iKiller].MOB.snKarma ) pMob[a_iKiller].MOB.snKarma = g_irgSetting[eCnst_MaxKarma]; 
						char temp[256] = {0,0,0, };
						sprintf( temp, "karma %d -> %d", nPrevKarma, pMob[a_iKiller].MOB.snKarma );
						Log( temp, pUser[a_iKiller].AccountName, pUser[a_iKiller].IP );
						/*
						pMob[a_iKiller].m_iPKDefender = 0;
						pMob[a_iKiller].m_uiPkDurTime = 0;
						pMob[a_iKiller].m_iAffections = pMob[a_iKiller].m_iAffections ^ eTNVSAfn_PKAttacker;
						*/
						pMob[a_iKiller].BroadcastUpdateStatusMsg();
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] OnKilled> 4. Á×ÀºÀÌ(%d,%s)> ÇöÀç³²ÀºGold:%d, ÇöÀçBraman:%d, Karma:%d \r\n\t\tKiller(%d,%s)> ÇöÀçGold:%d, ÇöÀçBraman:%d, Karma:%d, Å¸°Ý:%d \r\n"
								, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
								, m_iHandle, MOB.szName, MOB.nRupiah, MOB.nBramanPoint, MOB.snKarma
								, pMob[a_iKiller].m_iHandle, pMob[a_iKiller].MOB.szName, pMob[a_iKiller].MOB.nRupiah, pMob[a_iKiller].MOB.nBramanPoint, pMob[a_iKiller].MOB.snKarma, m_iLastDamage
								); 
							WriteLog( chBuf, m_szLogFile );
						}
						#endif

						//if( m_kInnocentDropRate.Random() ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
						iRate = rand() % 100;
						if( iRate < g_irgSetting[eCnst_InnocentDropRate] )
						{
							int iSlot = rand() % eTNEqu_Bag;
							//while ( eTNEqu_OneHandWeapon == iSlot || eTNEqu_Shield == iSlot ) iSlot = rand() % eTNEqu_Bag; // ¿Þ¼Õ, ¿À¸¥¼ÕÀº Á¦¿Ü
								
							if( 0 < MOB.Equip[iSlot].snIndex )
							{
								EquipItem( &MOB.Equip[iSlot], eAfn_Remove );
								S_SCP_RESP_ITEM_DROP kMsg;
								kMsg.wType = SCP_RESP_ITEM_DROP;
								kMsg.snResult = REPLY_ACK_OK;
								kMsg.byPlace = (byte)ITEM_PLACE_EQUIP;
								kMsg.byIndex = iSlot;
								kMsg.dwMoney = 0;
								kMsg.byType = DROP_TYPE_ITEM;
								pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));
								
								int iDestidx = CreateItem( iCoordX, iCoordY, &MOB.Equip[iSlot], 0, 0, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
								ZeroMemory(&MOB.Equip[iSlot], sizeof(STRUCT_ITEM));
								UpdateEquipmentPoints();

								S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
								nm.nID = m_iHandle; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
								memcpy(nm.Equip, ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

								// ¾ÆÀÌÅÛ ¶³±º°ÍÀ» ·Î±×·Î ³²±ä´Ù.
								if ( iDestidx != 0 )
								{
									char strItem[128];
									short snIndex = pItem[iDestidx].ITEM.snIndex;
									if (BASE_CheckItemLog(&pItem[iDestidx].ITEM))
									{					
										BASE_GetItemCode(&pItem[iDestidx].ITEM,strItem);
										sprintf(temp,"innocent %s",strItem);
										Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
									}
								}

								GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&nm, m_iHandle, 30);
							}
						}
						
					} // if( !UnderSiege )
				}
			}
		}
		else if( eTNMob_NPC == pMob[a_iKiller].m_eMobType ) // killer°¡ monster ÀÎ °æ¿ì
		{// hard-coding --;
			int iMonsterID = pMob[a_iKiller].MOB.snTribe;
			int iMonsterDataIndex = pMob[a_iKiller].MOB.nTP;

			
			//--------------------------------------------------------------------------------
			// ÆÐ³ÎÆ¼
			// ±æµåÀü : ¾Æ¹«°Íµµ ¾øÀ½
			// ÁÖ½ÅÀü : ³ëÆÐ³ÎÆ¼/ÇÁ¶ó³ª/ÁÖÆ÷
			// ÀÏ¹ÝÀü : ³ëÆÐ³ÎÆ¼/ÇÁ¶ó³ª/itemdropbykarma/¿¹¿Ü»çÇ×(¸Þ±×ÇÏ¸»¸°)
			//--------------------------------------------------------------------------------

			int iDecBP = 0;
			int nDecPrana = 0;
			if( eZoneType_Guild == g_iZoneType )  // ¿ä»õÀüÅõÀÌ¶ó¸é handicapÀÌ ÇÏ³ªµµ ¾ø´Ù.
			{
				sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
					MOB.szName, iMonsterID, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, MOB.byLevel, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
				Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
			}
			else
			{				
				if( ePnlt_DecPrana == pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_Reserved2] )
				{
					if( eHnt_Novice < MOB.byLevel ) nDecPrana = DecPrana( g_irgSetting[eCnst_PenaltyByKilled] );
				}
				else if( ePnlt_DecBP == pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_Reserved2] )
				{
					iDecBP = DecBP( g_irgSetting[eCnst_PenaltyBPByKilled] );
				}
				else if( ePnlt_NoPenalty == pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_Reserved2] ) ;
				else if( ePnlt_Exception == pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_Reserved2] )
				{
                    if( 2072 == iMonsterID && MOB.byQuest[30] == 9 ) ;// ¸Þ±×ÇÏ¸»¸° Äù½ºÆ® Áß¿¡ ¸Þ±×ÇÏ¸»¸°ÇÑÅ× Á×À¸¸é, °æÇèÄ¡ ¾È±ðÀ½.
					else
					{
						if( eHnt_Novice < MOB.byLevel ) nDecPrana = DecPrana( g_irgSetting[eCnst_PenaltyByKilled] );
					}
				}

				sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d(lv:%d) decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
					MOB.szName, iMonsterID, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, MOB.byLevel, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
				Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				if( eZoneType_Normal == g_iZoneType )
				{
					if( 0 < MOB.snKarma ) // Á×Àº »ç¶÷ÀÌ »ìÀÎÀÚ¿´´Ù.
					{
						int iRate = rand() % 100;
						if( iRate < g_irgSetting[eCnst_MurderDropRate] )
						{
							int iSlot = rand() % eTNEqu_Bag;
							//while ( eTNEqu_OneHandWeapon == iSlot || eTNEqu_Shield == iSlot ) iSlot = rand() % eTNEqu_Bag; // ¿Þ¼Õ, ¿À¸¥¼ÕÀº Á¦¿Ü
								
							if( 0 < MOB.Equip[iSlot].snIndex )
							{
								(iSlot==eTNEqu_Shield) ? EquipItem( &MOB.Equip[iSlot], eAfn_Remove, true ) : EquipItem( &MOB.Equip[iSlot], eAfn_Remove );
								S_SCP_RESP_ITEM_DROP kMsg;
								kMsg.wType = SCP_RESP_ITEM_DROP;
								kMsg.snResult = REPLY_ACK_OK;
								kMsg.byPlace = (byte)ITEM_PLACE_EQUIP;
								kMsg.byIndex = iSlot;
								kMsg.dwMoney = 0;
								kMsg.byType = DROP_TYPE_ITEM;
								pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));

								int iDestidx = CreateItem( iCoordX, iCoordY, &MOB.Equip[iSlot], 0, 0, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
								ZeroMemory(&MOB.Equip[iSlot], sizeof(STRUCT_ITEM));
								UpdateEquipmentPoints();

								S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
								nm.nID = m_iHandle; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
								memcpy(nm.Equip, ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

								// ¾ÆÀÌÅÛ ¶³±º°ÍÀ» ·Î±×·Î ³²±ä´Ù.
								if ( iDestidx != 0 )
								{
									char temp[512] = { 0,0,0, };
									char strItem[128];
									short snIndex = pItem[iDestidx].ITEM.snIndex;
									if (BASE_CheckItemLog(&pItem[iDestidx].ITEM))
									{					
										BASE_GetItemCode(&pItem[iDestidx].ITEM,strItem);
										sprintf(temp,"chaos %s",strItem);
										Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
									}
								}

								GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&nm, m_iHandle, 30);
							}
						}
					} // if( 0 < MOB.snKarma )
				} // if( eZoneType_Normal == g_iZoneType )
			}


			
/*
* ÁÖ½Å Áö¿ª¿¡¼­ Á×¾úÀ» ¶§
  - ÁÖ½ÅÀÌ ¾ø´Â ¸ó½ºÅÍ¿¡°Ô Á×¾úÀ» ¶§ °æÇèÄ¡ 5% ±ðÀÓ
  - ÁÖ½ÅÀÌ ÀÖ´Â ¸ó½ºÅÍ¿¡°Ô Á×¾úÀ» ¶§ ÁÖ½Å Æ÷ÀÎÆ® 25Á¡ ±ðÀÓ => °¡µå
    ÁÖ½Å Æ÷ÀÎÆ®°¡ ¾ø´Ù¸é °æÇèÄ¡°¡ 5% ±ðÀÓ
  - Á¤Âûº´¿¡°Ô´Â ÁÖ½ÅÆ÷ÀÎÆ®, °æÇèÄ¡ ¸ðµÎ ¾È ±ðÀÓ

2372	ºê¶óÈå¸¶ ¾Æ½Ã ¾Æ¹Ù¶ó
2373	ºê¶óÈå¸¶ Ä«ÆÄ ¾Æ¹Ù¶ó
2374	ºñ½´´© ¾Æ½Ã ¾Æ¹Ù¶ó
2375	ºñ½´´© Ä«ÆÄ ¾Æ¹Ù¶ó
2376	½Ã¹Ù ¾Æ½Ã ¾Æ¹Ù¶ó
2377	½Ã¹Ù Ä«ÆÄ ¾Æ¹Ù¶ó

2348, 2349, 2350
  */
			
			/*

			if( eZoneType_God == g_iZoneType )
			{					
				int nDecPrana = 0;
				if( (2901 <= iMonsterID && 2922 >= iMonsterID) || (2372 <= iMonsterID && 2377 >= iMonsterID) || (2348 <= iMonsterID && 2350 >= iMonsterID) ) DecBP( g_irgSetting[eCnst_PenaltyBPByKilled] ); // °¡µåÇÑÅ× Á×ÀÓÀ» ´çÇÏ¸é, ... ÇöÀç Ä«½ºÆ®¿¡ ÇØ´çÇÏ´Â BP·®ÀÇ 1/2À» ÁÙÀÎ´Ù.
				else if( 2948 <= iMonsterID && 2956 >= iMonsterID ); // Å©·ç¸¶/Àú·¦ Å©·ç¸¶ - Á¤Âûº´
				else if( 2934 <= iMonsterID && 2937 >= iMonsterID ); // Â÷Åõ¶û°¡ - ¹®Â¦
				else nDecPrana = DecPrana( g_irgSetting[eCnst_PenaltyByKilled] ); // ÁÖ½ÅÀü Áö¿ªÀÌ¶ó¸é, ÇÁ¶ó³ª¸¦ 5% ÁÙ¿©ÁØ´Ù.(´Ü, guard¿¡°Ô Á×ÀÓÀ» ´çÇÏ¸é, ÇÁ¶ó³ª¸¦ ÁÙÀÌÁö ¾Ê´Â´Ù.)

				char temp[256] = {0,0,0,};
				sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
					MOB.szName, iMonsterID, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
				Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

			}
			else if( eZoneType_Guild == g_iZoneType ) // ¿ä»õÀüÅõÀÌ¶ó¸é handcapÀÌ ÇÏ³ªµµ ¾ø´Ù.
			{			

			}
			else
			{
				
				if( 0 < MOB.snKarma ) // Á×Àº »ç¶÷ÀÌ »ìÀÎÀÚ¿´´Ù.
				{
					iRate = rand() % 100;
					if( iRate < g_irgSetting[eCnst_MurderDropRate] )
					{
						int iRate = rand()%100;
						//if( m_kMurderDropRate.Random() ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
						if( iRate < 10 ) // 10%È®·ü·Î ·£´ýÇÏ°Ô Âø¿ë ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
						{
							int iSlot = rand() % eTNEqu_Bag;
							//while ( eTNEqu_OneHandWeapon == iSlot || eTNEqu_Shield == iSlot ) iSlot = rand() % eTNEqu_Bag; // ¿Þ¼Õ, ¿À¸¥¼ÕÀº Á¦¿Ü
								
							if( 0 < MOB.Equip[iSlot].snIndex )
							{
								(iSlot==eTNEqu_Shield) ? EquipItem( &MOB.Equip[iSlot], eAfn_Remove, true ) : EquipItem( &MOB.Equip[iSlot], eAfn_Remove );
								S_SCP_RESP_ITEM_DROP kMsg;
								kMsg.wType = SCP_RESP_ITEM_DROP;
								kMsg.snResult = REPLY_ACK_OK;
								kMsg.byPlace = (byte)ITEM_PLACE_EQUIP;
								kMsg.byIndex = iSlot;
								kMsg.dwMoney = 0;
								kMsg.byType = DROP_TYPE_ITEM;
								pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));

								int iDestidx = CreateItem( iCoordX, iCoordY, &MOB.Equip[iSlot], 0, 0, a_iKiller, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
								ZeroMemory(&MOB.Equip[iSlot], sizeof(STRUCT_ITEM));
								UpdateEquipmentPoints();

								S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
								nm.nID = m_iHandle; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
								memcpy(nm.Equip, ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

								// ¾ÆÀÌÅÛ ¶³±º°ÍÀ» ·Î±×·Î ³²±ä´Ù.
								if ( iDestidx != 0 )
								{
									char temp[512] = { 0,0,0, };
									char strItem[128];
									short snIndex = pItem[iDestidx].ITEM.snIndex;
									if (BASE_CheckItemLog(&pItem[iDestidx].ITEM))
									{					
										BASE_GetItemCode(&pItem[iDestidx].ITEM,strItem);
										sprintf(temp,"chaos %s",strItem);
										Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
									}
								}

								GridMulticast(TargetX,TargetY,(MSG_STANDARD*)&nm, m_iHandle, 30);
							}
						}
					}
				}

				int nDecPrana = 0;
				char temp[256]={0,0,0,};
				if( (2930 <= iMonsterID && 2931 >= iMonsterID) || (2425 == iMonsterID) || (2426==iMonsterID) )
				{
					sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
						MOB.szName, iMonsterID, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
					Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
				else if ( 2072 == iMonsterID && MOB.byQuest[30] == 9 )
				{// ¸Þ±×ÇÏ¸»¸° Äù½ºÆ® Áß¿¡ ¸Þ±×ÇÏ¸»¸°ÇÑÅ× Á×À¸¸é, °æÇèÄ¡ ¾È±ðÀ½.
					sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
						MOB.szName, iMonsterID, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
					Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
				else
				{
					if( eHnt_Novice < MOB.byLevel ) nDecPrana = DecPrana( g_irgSetting[eCnst_PenaltyByKilled] ); // ÇÁ¶ó³ª¸¦ 5% ÁÙ¿©ÁØ´Ù.
					sprintf(temp,"die char:%s killer:Monster(%d) dam:%d, Prana:%d MAXHP:%d HP:%d MAXTP:%d TP:%d decprana:%d decgold:%d, karma:%d killed(%d,%d) killer(%d,%d),Resurrect80:%d,Resurrect100:%d",
						MOB.szName, iMonsterID,, m_iLastDamage, MOB.nPrana, m_iMaxHP, MOB.nHP, m_iMaxTP, MOB.nTP, nDecPrana, 0, MOB.snKarma, MOB.snX, MOB.snZ, pMob[a_iKiller].MOB.snX, pMob[a_iKiller].MOB.snZ, iCount80, iCount100);
					Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
			} // if( eZoneType_God == g_iZoneType )

			*/

			QUEST_OnEvent( m_iHandle, pMob[a_iKiller].MOB.snTribe, pMob[a_iKiller].MOB.snTribe, 0, FALSE );
			NotifyUpdateStatusMsg();

			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "OnKilled> 5. killer(%d, %s)¿¡ ÀÇÇØ Á×¾ú´Ù. º¯µ¿µÈ ÈÄ Prana:%d, Gold:%d, ÁÖ½ÅP:%d Å¸°Ý:%d \r\n"
					, a_iKiller, pMob[a_iKiller].MOB.szName, MOB.nPrana, MOB.nRupiah, MOB.nBramanPoint, m_iLastDamage ); 
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
		}		
	}
	else if( eTNMob_NPC == m_eMobType ) // NPC(monster Æ÷ÇÔ)ÀÌ¶ó¸é
	{
		if( eTNAIO_HaveMaster & m_iAIOption )
		{
			ReleaseLinkWithMaster();
			//pMob[Leader].m_irgSummoned[MOB.byClass2] = 0;
			
			DeleteMob( m_iHandle, 1, a_iKiller, eTNPrdt_RemoveBoom, 10 );
			return;
		}

		int iKalaSlot = 0;

		HS2D_COORD kPos;
		kPos.x = TargetX;
		kPos.y = TargetY;
		int iMaxDamageParty = 0;
		int iMaxDamage = 0;
		int iTotalDamage = 0;
		for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
		{
			if( 0 >= m_krgAttacker[i].iID || MAX_MOB <= m_krgAttacker[i].iID ) continue;
			if( 0 < m_krgAttacker[i].iDamage ) iTotalDamage += m_krgAttacker[i].iDamage;

			if( iMaxDamage < m_krgAttacker[i].iDamage )
			{
				iMaxDamageParty = m_krgAttacker[i].iID;
				iMaxDamage = m_krgAttacker[i].iDamage;
			}
		}

		int iRemoveProduct = eTNPrdt_RemoveNormal;
		if( eZoneType_Guild == g_iZoneType ) iRemoveProduct = eTNPrdt_RemoveFadeOut;
			
		if( 2 > m_iAttackCount ) Think( eTNAI_BeKilled1, iMaxDamageParty );
		else Think( eTNAI_BeKilled2, iMaxDamageParty );
		
		DeleteMob( m_iHandle, 1, a_iKiller, (byte)iRemoveProduct, 20 );

		if( 0 >= iTotalDamage ) iTotalDamage = pMonsterData[MOB.nTP].nHP;
		int iRwdPrana = MOB.nPrana;
		bool bApplyCorrect = true;
		if( eZone_Pamir == g_iZoneID ) //ÆÄ¹Ì¸£ Áö¿ªÀÌ¶ó¸é, ...
		{
			for( int i = 0; i < eTNCnt_MobSummoned; ++i )
			{
				if( MOB.snTribe == g_iMobSummoned[i] )
				{
					bApplyCorrect = false;
					break;
				}
			}
		}
	
		if( bApplyCorrect )	iRwdPrana = (int)(MOB.nPrana * g_drgRwdCorrect[eRwd_Prana][eRwd_Total]);

		if (g_iZoneID==24) //fors_debug K5´¥·¢µÄBOSS¹Ö
		{
            if  (MOB.snTribe==2705) 
			{ 

	char szMsg[500] = { 0,0,0, };
	sprintf( szMsg, "Ä§ÍõÒÑ±»ÏûÃð,µ«ÊÇËüµÄÐ¡µÜ»¹²»¸ÊÐÄ,ÓÂÊ¿ÃÇ×¼±¸ºÃÁËÃ´??????");
	PostMessageToWorld( szMsg );    

				//BOSS¹ÒÁËºóÕÙ»½³öÐ¡¹Ö 
		for( int i = MAX_USER; i < MAX_MOB; ++i )
		{
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
			if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

			KillMonster( i );
		}
         for( int irandCount = 0; irandCount < 100; ++irandCount )
		 {
			HS2D_COORD krgPos[8];
			int iBodyRadius = 3;
			int iSize = iBodyRadius + iBodyRadius + 1;
			iSize = 3;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = GetMobMyRandom(10,900);
			kCur.y = GetMobMyRandom(10,900);
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

            // ¼ÒÈ¯ÇÒ ¶§

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = 5; // ¼ÒÈ¯µÇ´Â ¼ö
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
				{// randomÇÏ°Ô ÇÑ °÷¿¡¼­ ÅÂ¾î³­´Ù.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}
				 int irgmonster[10] = { 2694, 2700, 2701, 2770, 2771, 2772, 2774, 2775, 2778, 2779,};
			     int irgid=GetMobMyRandom(0,9);
                                int MonID = irgmonster[irgid];
				int iMob = pMob[1].Summon( MonID, 100, eTNPrdt_PopRaise, eTNCls_Warrior, 0, eTNClan_Aggressive, 0, x, y, 0, false, 0, 0, 140 );

				if( 0 == iMob ) ++iSummonCount;
				//if( 30 <= iSummonCount ) break;
            }
			//				sprintf(temp, "random pos:%d,%d \r\n", kCur.x, kCur.y);
			//	TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
			}

//////////////////////////////////little boss
 for( int irandCount = 0; irandCount < 20; ++irandCount )
		 {
			HS2D_COORD krgPos[8];
			int iBodyRadius = 3;
			int iSize = iBodyRadius + iBodyRadius + 1;
			iSize = 3;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = GetMobMyRandom(10,900);
			kCur.y = GetMobMyRandom(10,900);
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

            // ¼ÒÈ¯ÇÒ ¶§

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = 3; // ¼ÒÈ¯µÇ´Â ¼ö
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
				{// randomÇÏ°Ô ÇÑ °÷¿¡¼­ ÅÂ¾î³­´Ù.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}

								 int irgmonster1[44] = { 2036,2037,2038,2039,2040,2041,2042,2043,2044,2045,2052,2053,2054,2055,2056,2057,2058,2059,2060,2071,2072,2114,2115,2116,2117,2118,2119,2120,2121,2122,2123,2124,2125,2126,2127,2288,2514,2515,2516,2517,2503,2504,2505,2506,};
			     int irgid1=GetMobMyRandom(0,43);


                                int MonID = irgmonster1[irgid1];
				int iMob = pMob[1].Summon( MonID, 100, eTNPrdt_PopRaise, eTNCls_Warrior, 0, eTNClan_Aggressive, 0, x, y, 0, false, 0, 0, 140 );

				if( 0 == iMob ) ++iSummonCount;
				//if( 30 <= iSummonCount ) break;
            }
			//				sprintf(temp, "random pos:%d,%d \r\n", kCur.x, kCur.y);
			//	TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
			}
/////////////////////////////////////////////////////finally boss
 for( int irandCount = 0; irandCount < 10; ++irandCount )
		 {
			HS2D_COORD krgPos[8];
			int iBodyRadius = 3;
			int iSize = iBodyRadius + iBodyRadius + 1;
			iSize = 3;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = GetMobMyRandom(10,900);
			kCur.y = GetMobMyRandom(10,900);
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

            // ¼ÒÈ¯ÇÒ ¶§

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = 1; // ¼ÒÈ¯µÇ´Â ¼ö
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
				{// randomÇÏ°Ô ÇÑ °÷¿¡¼­ ÅÂ¾î³­´Ù.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}
                                int MonID = 2704;
				int iMob = pMob[1].Summon( MonID, 100, eTNPrdt_PopRaise, eTNCls_Warrior, 0, eTNClan_Aggressive, 0, x, y, 0, false, 0, 0, 140 );

				if( 0 == iMob ) ++iSummonCount;
				//if( 30 <= iSummonCount ) break;
            }
			//				sprintf(temp, "random pos:%d,%d \r\n", kCur.x, kCur.y);
			//	TimeWriteLog(temp,".\\Event\\[Log]Yut.txt");
			}




			}
 



			 char chBuf[200]={0,0,};
		   sprintf( chBuf, "[killmonsterID] monsterID %d  ",MOB.snTribe);
		  Log( chBuf, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );	
		}
		for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
		{
			if( 0 >= m_krgAttacker[i].iID || MAX_USER <= m_krgAttacker[i].iID ) continue;
			if( 0 < m_krgAttacker[i].iDamage )
			{
				double dDamage = m_krgAttacker[i].iDamage;
				double dPercent =  dDamage / iTotalDamage ;
				
     		     SharePrana( m_krgAttacker[i].iID, (int)(iRwdPrana * dPercent), m_iHandle, bApplyCorrect,MOB.byLevel);

		//fors_debug ÔÂ¹â
		 char chBuf[200]={0,0,};
		int iwhat=GetMobMyRandom(1,100);
		if (g_iZoneID == 24)
		{
           if ( iwhat >= 70 && iwhat<=80)
		   {
              GiveItem(m_krgAttacker[i].iID,7357,1);
    sprintf( chBuf, "[givek5xiaoboss] the thing get is ok iwhat %d,a_iKiller %d ", iwhat,m_krgAttacker[i].iID);
		Log( chBuf, pUser[m_krgAttacker[i].iID].AccountName, pUser[m_krgAttacker[i].iID].IP );	
		   }
		}
/*		if (g_iZoneID == 22)
		{
		if (MOB.byLevel<60)
		{
			if (iwhat>30 && iwhat<50)
			{
				GiveItem(m_krgAttacker[i].iID,6718,1);
				        sprintf( chBuf, "[givezhongqiu] the thing get is ok iwhat %d,a_iKiller %d ", iwhat,m_krgAttacker[i].iID);
		Log( chBuf, pUser[m_krgAttacker[i].iID].AccountName, pUser[m_krgAttacker[i].iID].IP );	
			}

		}
		else if ( iwhat >= 70 && iwhat<=80)
		{
			GiveItem(m_krgAttacker[i].iID,6718,1);
				        sprintf( chBuf, "[givezhongqiu] the thing get is ok iwhat %d,a_iKiller %d ", iwhat,m_krgAttacker[i].iID);
		Log( chBuf, pUser[m_krgAttacker[i].iID].AccountName, pUser[m_krgAttacker[i].iID].IP );	
		}
		}
*/
			   
			}
		}

		DetermineNextPopTime( 10 );
		/*
		int iMinPopDelay = pMonsterData[MOB.nTP].Equip[eMonPrty_PopDelayMin].snIndex;
		int iMaxPopDelay = pMonsterData[MOB.nTP].Equip[eMonPrty_PopDelayMax].snIndex;
		int iPopDelay = PlayDice( iMinPopDelay, iMaxPopDelay );
		m_kLastTime.uiKilled = CurrentTime + iPopDelay * 1000; // 3,600,000
		*/

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag && (MAX_USER > iMaxDamageParty && 0 < iMaxDamageParty ) )
		{
			char chBuf[512] = { 0,0,0, };
			
			sprintf(chBuf, "[%dyy%dmm%ddd %dhh%dms%dss] OnKilled > Mob(H:%d, Trb:%d), How:%d > 6. LastDamage:%d, LastDamageDealer:%d, party be rewarded:%d, dead time:%u, next pop time:%u \r\n"
				, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				, m_iHandle, MOB.snTribe, a_iHow, m_iLastDamage
				, a_iKiller, iMaxDamageParty, CurrentTime, m_kLastTime.uiKilled ); 
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
			

			memset( chBuf, 0, sizeof(chBuf) );
			sprintf(chBuf, "\tOnKilled::MaxDamageParty> 1. %s\r\n", pMob[iMaxDamageParty].MOB.szName ); 
			WriteLog( chBuf, m_szLogFile );

			int iNumber = 2;
			for( int i = 0; i < MAX_PARTY; ++i )
			{

				int iParty = pMob[iMaxDamageParty].m_irgParty[i];
				if( 0 >= iParty || MAX_USER <= iParty ) continue;

				memset( chBuf, 0, sizeof(chBuf) );
				sprintf(chBuf, "\tOnKilled::MaxDamageParty> %d. %s\r\n", iNumber, pMob[iParty].MOB.szName );
				WriteLog( chBuf, m_szLogFile );
				++iNumber;
			}
		}
		#endif
		

		if( eZoneType_Guild == g_iZoneType )
		{
			if( 0 >= pMob[iMaxDamageParty].MOB.nGuildID ) return;		//	±æµå°¡ ¾øÀ» °æ¿ì

			int nGuildIndex = GetGuild(pMob[iMaxDamageParty].MOB.nGuildID, FLAG_CLOSE);
			if(nGuildIndex<=0 || nGuildIndex>=MAX_USER)	return;			//	±æµå°¡ ¾øÀ» °æ¿ì

			if( eStronghold_NorthwestSymbol2 == MOB.snTribe )
			{
				UpdateStrongHold(eStronghold_Northwest, nGuildIndex, a_iKiller );
				SaveStrongholdData();
				RefreshClan( eStronghold_Northwest, eTNClan_Stronghold1 );
			}
			else if( eStronghold_NortheastSymbol2 == MOB.snTribe )
			{
				UpdateStrongHold(eStronghold_Northeast, nGuildIndex, a_iKiller );
				SaveStrongholdData();
				RefreshClan( eStronghold_Northeast, eTNClan_Stronghold2 );
			}
			else if( eStronghold_SouthwestSymbol2 == MOB.snTribe )
			{
				UpdateStrongHold(eStronghold_Southwest, nGuildIndex, a_iKiller );
				SaveStrongholdData();
				RefreshClan( eStronghold_Southwest, eTNClan_Stronghold3 );
			}
			else if( eStronghold_SoutheastSymbol2 == MOB.snTribe )
			{
				UpdateStrongHold(eStronghold_Southeast, nGuildIndex, a_iKiller );
				SaveStrongholdData();
				RefreshClan( eStronghold_Southeast, eTNClan_Stronghold4 );
			}
		}

		if( 0 >= iMaxDamageParty || MAX_USER <= iMaxDamageParty ) return; // ¸Æµ© ÆÄÆ¼°¡ ¸ó½ºÅÍÀÌ¶ó¸é, ...º¸»óÀ» ÇÏÁö ¾Ê´Â´Ù.

		//if( IsInRvR() ) // ÁÖ½ÅÀü Áö¿ª

		if( eZoneType_God == g_iZoneType )
		{
			if( eKala_Brahma == MOB.snTribe || eKala_Vishnu == MOB.snTribe || eKala_Siva == MOB.snTribe )
			{
				int iTxtIndex = 0;
				if( eKala_Brahma == MOB.snTribe ) iTxtIndex = _Brahma;
				else if( eKala_Vishnu == MOB.snTribe ) iTxtIndex = _Vishnu;
				else if( eKala_Siva == MOB.snTribe ) iTxtIndex = _Siva;

				char szMsg[1024] = { 0,0,0, };
				sprintf( szMsg, g_pMessageStringTable[_Destroy_Kala], kPos.x, kPos.y, g_pMessageStringTable[iTxtIndex] );
				PostMessageToZone( szMsg );

				MoveKalaRewarder();
			}

			int tx = TargetX;
			int ty = TargetY;
			int fol=0;
			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = iMaxDamageParty;
				else      fol = pMob[iMaxDamageParty].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				++nMember;
				if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-g_iViewGridX || tx>pMob[fol].TargetX+g_iViewGridX ||ty<pMob[fol].TargetY-g_iViewGridY || ty>pMob[fol].TargetY+g_iViewGridY) continue;
				++nMemberCount;
			}
		}
		else // ÁÖ½ÅÀü Áö¿ª ¿ÜÀÇ ¸ðµç Áö¿ª, ...
		{// Karma Ã³¸®					iMaxDamageParty
			int tx = TargetX;
			int ty = TargetY;
			int fol=0;
			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = iMaxDamageParty;
				else      fol = pMob[iMaxDamageParty].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				++nMember;
				if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-g_iViewGridX || tx>pMob[fol].TargetX+g_iViewGridX ||ty<pMob[fol].TargetY-g_iViewGridY || ty>pMob[fol].TargetY+g_iViewGridY) continue;
				++nMemberCount;
				if( 0 < pMob[fol].MOB.snKarma )
				{						
					if( MOB.byLevel >= pMob[fol].MOB.byLevel && pMob[fol].MOB.snKarma > 0 )
					{
						int nPrevKarma = pMob[fol].MOB.snKarma;
						pMob[fol].MOB.snKarma -= g_irgSetting[eCnst_HuntHigh];
						if( 0 > pMob[fol].MOB.snKarma ) pMob[fol].MOB.snKarma = 0;	
						char temp[256] = {0,0,0, };
						sprintf( temp, "karma %d -> %d", nPrevKarma, pMob[fol].MOB.snKarma );
						Log( temp, pUser[fol].AccountName, pUser[fol].IP );
					}
					else if( (MOB.byLevel < pMob[fol].MOB.byLevel) && ((MOB.byLevel + 10) >= pMob[fol].MOB.byLevel) && pMob[fol].MOB.snKarma > 0 ) 
					{
						int nPrevKarma = pMob[fol].MOB.snKarma;
						pMob[fol].MOB.snKarma -= g_irgSetting[eCnst_HuntLow];
						if( 0 > pMob[fol].MOB.snKarma ) pMob[fol].MOB.snKarma = 0;
						char temp[256] = {0,0,0, };
						sprintf( temp, "karma %d -> %d", nPrevKarma, pMob[fol].MOB.snKarma );
						Log( temp, pUser[fol].AccountName, pUser[fol].IP );
					}

					pMob[fol].BroadcastUpdateStatusMsg(); // killerÀÇ Ä«¸£¸¶ ¼öÄ¡ º¯°æ
				}
			}
		}

		if(nMemberCount<=0) 
		{	//char chBuf[256] = { 0,0,0, };
			//sprintf(chBuf, "err OnKilled - Party:%d, Killer:%d, Leader:%d, MobIndex:%d  \r\n", iMaxDamageParty, a_iKiller, pMob[a_iKiller].Leader, m_iHandle ); 
			//WriteLog( chBuf, ".\\LOG\\[Log]CRITICALERROR.txt" );
			nMemberCount = 1;	//	ÆÄÆ¼¿øÀÌ 0¸íÀÏ°æ¿ì(ÀÖÀ»¼ö ¾ø´Â °æ¿ìÀÌ´Ù)
		}

		//if( 0 >= a_iKiller || MAX_USER <= a_iKiller ) return; // ¸·Å¸ Ä£ °ÍÀÌ ¸ó½ºÅÍÀÌ¶ó¸é, ...

		int iEventID = MOB.snBagIndex;
		if( 0 < iEventID ) // event Ã³¸®
		{
			TriggerEvent( iMaxDamageParty, iEventID, TargetX, TargetY, m_iHandle, 1311 );	
		}

		//-------------------------------------------------------
		// Reward Items(+ Gold)
		//-------------------------------------------------------
		if(a_iKiller>0 && a_iKiller<MAX_USER && g_nGiftItemMaxCount<g_nGiftItemCount)		//	ÄÉ¸¯ÀÌ ¸ó½ºÅÍ »ç³É½Ã ¼±¹°¾ÆÀÌÅÛÀÌ Á¸Àç
		{	g_nGiftItemCount--;
			CreateItem( iCoordX, iCoordY, &GiftItem, MOB.snTribe, 0, iMaxDamageParty, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
		}

		if( 0 < pMonsterData[MOB.nTP].nRupiah )		//	·çÇÇ¾Æ º¸»ó(ÆÄÆ¼°¡ ÀÚµ¿ºÐ¹è¸ðµåÀÌ°í ÆÄÆ¼ÀåÀÌ ÀÚµ¿½ÀµæÀÎ °æ¿ì - 1/N)
		{	int iGold = (int)(MOB.nRupiah * g_drgRwdCorrect[eRwd_Gold][eRwd_Total]);
			bool bAutoRooting = pMob[iMaxDamageParty].m_bAMoneyRoot && (pMob[iMaxDamageParty].byRootingMode==ROOTING_SHARE);
			bAutoRooting = bAutoRooting || (nMember==1 && pMob[a_iKiller].m_bAMoneyRoot);	//	¼Ö·Î»ç³ÉÀÌ°í ÀÚµ¿ºÐ¹èÀÏ °æ¿ì

			if(bAutoRooting)
			{	int fol = 0; int tx = TargetX; int ty = TargetY;
				S_SCP_RESP_ITEM_GET itemget;
				itemget.wType = SCP_RESP_ITEM_GET;
				itemget.nResult = REPLY_ACK_OK;
				itemget.snIndex = pMonsterData[MOB.nTP].Inven[10].snIndex;

				for (int i=0;i<MAX_PARTY+1;i++)
				{   if (i==0) fol = iMaxDamageParty;
					else      fol = pMob[iMaxDamageParty].m_irgParty[i-1];
   	 				if	(fol<=0||fol>=MAX_USER) continue;
					if	(pMob[fol].MOB.nHP<=0 ||  tx<pMob[fol].TargetX-g_iViewGridX || tx>pMob[fol].TargetX+g_iViewGridX ||ty<pMob[fol].TargetY-g_iViewGridY || ty>pMob[fol].TargetY+g_iViewGridY) continue;

					int iMoney = iGold/nMemberCount;
					//iMoney *= (pMob[fol].m_dGetMoneyRate/100);

					pMob[fol].IncGold(iMoney);
					itemget.dwMoney = pMob[fol].MOB.nRupiah;
					pUser[fol].cSock.SendOneMessage((char*)&itemget, sizeof(S_SCP_RESP_ITEM_GET));	//	µ·À» ÁÖ¿ü´Ù´Â °ÍÀ» ¾Ë¸°´Ù.
				}
			}	
			else									//	ÀÚµ¿ºÐ¹è°¡ ¾Æ´Ñ°æ¿ì
			{	CreateItem( iCoordX, iCoordY, &pMonsterData[MOB.nTP].Inven[10], MOB.snTribe, iGold, iMaxDamageParty, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
			}
		}
		
		/*
		// kala event Ã³¸® code(½ÃÇà±â°£: 2004.4.20~2004.4.27), coded by spencer(It's just hard-cording.)
		if( eKala_Event1 == MOB.snTribe || eKala_Event2 == MOB.snTribe || eKala_Event3 == MOB.snTribe || 2112 == MOB.snTribe
			|| 2169 == MOB.snTribe || 2170 == MOB.snTribe || 2171 == MOB.snTribe
			|| 2472 == MOB.snTribe || 2473 == MOB.snTribe || 2474 == MOB.snTribe
			|| 2354 == MOB.snTribe || 2355 == MOB.snTribe || 2356 == MOB.snTribe )
		{
			int iGold = 5000;
			if( eKala_Event1 == MOB.snTribe ) iGold = 5000;
			else if( eKala_Event2 == MOB.snTribe ) iGold = 10000;
			else if( eKala_Event3 == MOB.snTribe ) iGold = 25000;
			else if( 2112 == MOB.snTribe ) iGold = 125000; // Â÷Åõ¶û°¡ - ¶óÇª
			else if( 2169 == MOB.snTribe ) iGold = 25000;
			else if( 2170 == MOB.snTribe ) iGold = 75000;
			else if( 2171 == MOB.snTribe ) iGold = 125000;

			else if( 2354 == MOB.snTribe ) iGold = 5000;
			else if( 2355 == MOB.snTribe ) iGold = 10000;
			else if( 2356 == MOB.snTribe ) iGold = 25000;
			else if( 2472 == MOB.snTribe ) iGold = 5000;
			else if( 2473 == MOB.snTribe ) iGold = 10000;
			else if( 2474 == MOB.snTribe ) iGold = 25000;

			
			STRUCT_ITEM kItem;
			int iGoldIndex = g_ParamMgr.HT_iGetIndexForMoneyItem( iGold );
			kItem.snIndex = iGoldIndex - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = eDur_Indestructible;
			kItem.byCount = 1;

			enum { e6Gap = 6, e5Gap = 5, e4Gap = 4, e3Gap = 3, e2Gap = 2, e1Gap = 1, eMaxGoldBagCount = 40, };
			HS2D_COORD krgPos[eMaxGoldBagCount];

			krgPos[0].x = TargetX - e4Gap;
			krgPos[0].y = TargetY + e4Gap;
			krgPos[1].x = TargetX - e2Gap;
			krgPos[1].y = TargetY + e4Gap;
			krgPos[2].x = TargetX;
			krgPos[2].y = TargetY + e4Gap;
			krgPos[3].x = TargetX + e2Gap;
			krgPos[3].y = TargetY + e4Gap;
			krgPos[4].x = TargetX + e4Gap;
			krgPos[4].y = TargetY + e4Gap;

			krgPos[5].x = TargetX - e4Gap;
			krgPos[5].y = TargetY + e2Gap;
			krgPos[6].x = TargetX - e4Gap;
			krgPos[6].y = TargetY;
			krgPos[7].x = TargetX - e4Gap;
			krgPos[7].y = TargetY - e2Gap;

			krgPos[8].x = TargetX + e4Gap;
			krgPos[8].y = TargetY + e2Gap;
			krgPos[9].x = TargetX + e4Gap;
			krgPos[9].y = TargetY;
			krgPos[10].x = TargetX + e4Gap;
			krgPos[10].y = TargetY - e2Gap;

			krgPos[11].x = TargetX - e4Gap;
			krgPos[11].y = TargetY - e4Gap;
			krgPos[12].x = TargetX - e2Gap;
			krgPos[12].y = TargetY - e4Gap;
			krgPos[13].x = TargetX;
			krgPos[13].y = TargetY - e4Gap;
			krgPos[14].x = TargetX + e2Gap;
			krgPos[14].y = TargetY - e4Gap;
			krgPos[15].x = TargetX + e4Gap;
			krgPos[15].y = TargetY - e4Gap;			

			krgPos[16].x = TargetX - e3Gap;
			krgPos[16].y = TargetY + e5Gap;			
			krgPos[17].x = TargetX - e1Gap;
			krgPos[17].y = TargetY + e5Gap;			
			krgPos[18].x = TargetX + e1Gap;
			krgPos[18].y = TargetY + e5Gap;			
			krgPos[19].x = TargetX + e3Gap;
			krgPos[19].y = TargetY + e5Gap;			

			krgPos[20].x = TargetX - e3Gap;
			krgPos[20].y = TargetY - e5Gap;			
			krgPos[21].x = TargetX - e1Gap;
			krgPos[21].y = TargetY - e5Gap;			
			krgPos[22].x = TargetX + e1Gap;
			krgPos[22].y = TargetY - e5Gap;			
			krgPos[23].x = TargetX + e3Gap;
			krgPos[23].y = TargetY - e5Gap;			

			krgPos[20].x = TargetX - e5Gap;
			krgPos[20].y = TargetY + e3Gap;			
			krgPos[21].x = TargetX - e5Gap;
			krgPos[21].y = TargetY + e1Gap;			
			krgPos[22].x = TargetX - e5Gap;
			krgPos[22].y = TargetY - e1Gap;			
			krgPos[23].x = TargetX - e5Gap;
			krgPos[23].y = TargetY - e3Gap;			

			krgPos[24].x = TargetX + e5Gap;
			krgPos[24].y = TargetY + e3Gap;			
			krgPos[25].x = TargetX + e5Gap;
			krgPos[25].y = TargetY + e1Gap;			
			krgPos[26].x = TargetX + e5Gap;
			krgPos[26].y = TargetY - e1Gap;			
			krgPos[27].x = TargetX + e5Gap;
			krgPos[27].y = TargetY - e3Gap;			

			krgPos[28].x = TargetX - e2Gap;
			krgPos[28].y = TargetY + e6Gap;			
			krgPos[29].x = TargetX;
			krgPos[29].y = TargetY + e6Gap;			
			krgPos[30].x = TargetX + e2Gap;
			krgPos[30].y = TargetY + e6Gap;			

			krgPos[31].x = TargetX - e2Gap;
			krgPos[31].y = TargetY - e6Gap;			
			krgPos[32].x = TargetX;
			krgPos[32].y = TargetY - e6Gap;			
			krgPos[33].x = TargetX + e2Gap;
			krgPos[33].y = TargetY - e6Gap;			

			krgPos[34].x = TargetX - e6Gap;
			krgPos[34].y = TargetY + e2Gap;			
			krgPos[35].x = TargetX - e6Gap;
			krgPos[35].y = TargetY;
			krgPos[36].x = TargetX - e6Gap;
			krgPos[36].y = TargetY - e2Gap;			

			krgPos[37].x = TargetX + e6Gap;
			krgPos[37].y = TargetY + e2Gap;			
			krgPos[38].x = TargetX + e6Gap;
			krgPos[38].y = TargetY;
			krgPos[39].x = TargetX + e6Gap;
			krgPos[39].y = TargetY - e2Gap;			

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
		*/


		for( int i = 0; i < 8; ++i ) // 1~8¹øÂ° items
		{
			if( 0 >= pMonsterData[MOB.nTP].Inven[i].snIndex ) continue; //fors_debug ²âÊÔ×öÐÞ¸Ä=0È¥µô ¼Ó!
			if( g_krgRewardItemRate[MOB.nTP][i].Random() )
			{
				#ifdef __DYNAMIC_LOG__
				if( m_iDebugFlag )
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );

					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] %dth> \t¸÷ %d \t¾ÆÀÌÅÛ %d \tÆÄÆ¼ %d \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, i+1, MOB.nTP+2000, pMonsterData[MOB.nTP].Inven[i].snIndex + 4000, iMaxDamageParty ); 
					WriteLog( chBuf, ".\\monster_log\\[Log]RewardItem.txt" );
				}
				#endif
				iCoordX = TargetX;
				iCoordY = TargetY;
				CreateItem( iCoordX, iCoordY, &pMonsterData[MOB.nTP].Inven[i], MOB.snTribe, 0, iMaxDamageParty, CurrentTime + g_irgSetting[eCnst_PriorityTime] );	

				int iID = pItemData[pMonsterData[MOB.nTP].Inven[i].snIndex].sID;
				if( (eKalaCore_Brahma == iID) || (eKalaCore_Vishnu == iID) || (eKalaCore_Siva == iID) )
				{
					g_kKalaSystem.ChangeKalaLoc( TNKalaSystem::eLoc_Altar, 0, m_iHandle, 0, 0, 0, TNKalaSystem::eLoc_Ground, 0, 0, iCoordX, iCoordY, 0, iMaxDamageParty );
				}
			}
		}

		// 9¹øÂ° reward-Item
		int iMobLevel = pMonsterData[MOB.nTP].Inven[8].snIndex;
		if( 0 < iMobLevel && eMonster_MaxLevel > iMobLevel )
		{
			if( g_krgRewardItemRate[MOB.nTP][8].Random() )
			{
				int iItemLevel = g_krgItemRateByMonLevel[iMobLevel].Random();  // iItemLevel : 1~21
				int iItemCategory = g_kRateByItemCategory.Random(); // iItemCategory : 0~n
				if( (0 < iItemLevel && eItm_MaxLevel > iItemLevel) && ( 0 <= iItemCategory && eItm_MaxCategory > iItemCategory) )
					if( 0 < g_krgItemByLevel[iItemCategory][iItemLevel].snIndex && MAX_ITEM_DATA > g_krgItemByLevel[iItemCategory][iItemLevel].snIndex )
					{
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							//SYSTEMTIME st;
							//GetLocalTime( &st );

							char chBuf[256] = { 0,0,0, };
							sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] 9th> \t¸÷ %d \t¾ÆÀÌÅÛ %d \tÆÄÆ¼ %d, MobLvl:%d, ItemCategory:%d, ItemLevel:%d \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.snTribe, g_krgItemByLevel[iItemCategory][iItemLevel].snIndex + 4000, iMaxDamageParty, iMobLevel, iItemCategory , iItemLevel ); 
							WriteLog( chBuf, ".\\monster_log\\[Log]RewardItem.txt" );
						}
						#endif
						iCoordX = TargetX;
						iCoordY = TargetY;
						CreateItem( iCoordX, iCoordY, &g_krgItemByLevel[iItemCategory][iItemLevel], MOB.snTribe, 0, iMaxDamageParty, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
					}
			}
		}

		// 10¹øÂ° reward-Item, group¿¡ µû¸¥ ºÐ·ù
		if( 0 < pMonsterData[MOB.nTP].Inven[9].snIndex )
		{
			if( g_krgRewardItemRate[MOB.nTP][9].Random() )
			{
				int iGroup =  pMonsterData[MOB.nTP].Inven[9].snIndex;
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
								STRUCT_ITEM kItem;
								kItem.snIndex = sIndex;
								kItem.snDurability = pItemData[sIndex].sMaxDur;
								kItem.byCount = 1; //pItemData[MOB.Inven[9].snIndex].byMaxPackCount;
								kItem.byRefineLevel = 0;
								for( int i = 0; i < MAX_SUBMATERIALSIZE; ++i ) kItem.bySubRefine[i] = 0;
								iCoordX = TargetX;
								iCoordY = TargetY;
								CreateItem( iCoordX, iCoordY, &kItem, MOB.snTribe, 0, iMaxDamageParty, CurrentTime + g_irgSetting[eCnst_PriorityTime] );
								#ifdef __DYNAMIC_LOG__
								if( m_iDebugFlag )
								{
									//SYSTEMTIME st;
									//GetLocalTime( &st );

									char chBuf[256] = { 0,0,0, };
									sprintf(chBuf, "[%d¿ù%dÀÏ %d½Ã%dºÐ%dÃÊ] 10th> \t¸÷ %d \t¾ÆÀÌÅÛ %d \tÆÄÆ¼ %d \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, MOB.nTP+2000, pItemData[sIndex].sID , iMaxDamageParty ); 
									WriteLog( chBuf, ".\\monster_log\\[Log]RewardItem.txt" );
								}
								#endif
							}
						}
					}
				}
			}
		} // if( 0 < MOB.Inven[9].snIndex ) // 10¹øÂ° reward-Item
	}
}



//--------------------------------------------------------------
// attackerµéÀ» score·Î ³»¸²Â÷¼øÀ¸·Î sortÇÑ´Ù.
//--------------------------------------------------------------
void CMob::SortAttackers()
{
	TNATTACKER kTemp;
	int iLast = TN_ATTACKER_COUNT - 1;
	// damage¿¡ ´ëÇØ¼­ ³»¸²Â÷¼ø Á¤·Ä
	for( int i = 0; i < iLast; ++i )
	{
		for( int j = i+1; j < TN_ATTACKER_COUNT; ++j )
		{
			if( m_krgAttacker[i].iScore < m_krgAttacker[j].iScore ) 
			{
				kTemp = m_krgAttacker[i];
				m_krgAttacker[i] = m_krgAttacker[j];
				m_krgAttacker[j] = kTemp;
			}
		}
	}


}


int CMob::get_Attacker(	int a_iRank )
{
	if( 0 > a_iRank || TN_ATTACKER_COUNT <= a_iRank ) return 0;
	return m_krgAttacker[a_iRank].iID;
}


//-------------------------------------------------------------------------------------------
// combat mode·Î ÀüÈ¯À» ÇÑ´Ù. ±×¸®°í targetÀÌ ºñ¾î ÀÖÀ¸¸é, ±â¾ïÀ» ÇØµÐ´Ù.
// score¸¦ ±â¾ïÀ» ÇÑ´Ù.
// OnUnderAttack()¿¡¼­ MemorizeAttack( 0, 1, n), Áï damage°¡ 0À¸·Î µÇ¾î ÀÖ´Ù.
//-------------------------------------------------------------------------------------------
void CMob::MemorizeAttacker( int a_iDamage, int a_iScore, int a_iAttacker )
{
	if( 0 >= a_iAttacker && MAX_MOB <= a_iAttacker ) return;
	if( m_iHandle == a_iAttacker ) return;

	Mode = MOB_COMBAT;
	if( 0 >= CurrentTarget )
	{// Ã³À½ °ø°ÝÀ» ¹ÞÀ» °æ¿ìÀÌ´Ù.
		CurrentTarget = a_iAttacker;
		//m_kLastTime.uiAttacked = CurrentTime;
		if( eTNCls_Summoned != pMob[a_iAttacker].MOB.byClass1 ) m_kLastTime.uiSelectTarget = CurrentTime + 2000;
	}


	if( eTNAIO_HaveMaster & pMob[a_iAttacker].m_iAIOption )
		if( 0 < pMob[a_iAttacker].Leader && MAX_USER > pMob[a_iAttacker].Leader ) a_iAttacker = pMob[a_iAttacker].Leader;

	int iPartyLeader = pMob[a_iAttacker].Leader;
	if( 0 >= iPartyLeader ) iPartyLeader = a_iAttacker;

	if( (eTNMob_PC == m_eMobType) && (MAX_USER <= iPartyLeader) ) return; // ¼öºñÀÚ°¡ PCÀÌ°í °ø°ÝÀÚ°¡ NPCÀÌ¸é damage¸¦ ±â·ÏÇÏÁö ¾Ê´Â´Ù.

	// ±âÁ¸ Àû¿¡ ´ëÇÑ score ´©Àû
	for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
	{
		if( iPartyLeader == m_krgAttacker[i].iID )
		{
			if( 19000000000 > m_krgAttacker[i].iDamage ) m_krgAttacker[i].iDamage += a_iDamage;
			if( 19000000000 > m_krgAttacker[i].iScore ) m_krgAttacker[i].iScore += a_iScore;
			if( 0 > m_krgAttacker[i].iScore ) m_krgAttacker[i].iScore = 0;
			m_krgAttacker[i].uiReleaseTime = CurrentTime + eCmbt_MemoryTime; // 1ºÐ µÚ¿¡ ¾ø¾îÁø´Ù.
			#ifdef __TN_3RD_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\t[MemorizeAttacker] 2. party(%d) °»½Å, damage: %d, ÃÑ damage: %d, releaseTime: %d \r\n", iPartyLeader, a_iDamage, m_krgAttacker[i].iDamage, m_krgAttacker[i].uiReleaseTime ); 
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_3RD_LOG__

			return;
		}	
	}

	// ÀûÀ» ½Å±Ô µî·Ï
	int iMinorPartyIndex = 0;
	unsigned int uiOldestTime = m_krgAttacker[0].uiReleaseTime;
	for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
	{
		if( (0 == m_krgAttacker[i].iID) )
		{
            m_krgAttacker[i].iID = iPartyLeader;
			m_krgAttacker[i].iDamage = a_iDamage;
			m_krgAttacker[i].iScore = a_iScore;
			if( 0 > m_krgAttacker[i].iScore ) m_krgAttacker[i].iScore = 0;
			unsigned int uiMemoryTime = eCmbt_MemoryTime;
			if( 0 == a_iDamage ) uiMemoryTime = 20000; // ¼±°ø¿¡ ÀÇÇØ °ø°ÝÀ» ½ÃÀÛÇÏ´Â °æ¿ì¿¡´Â 20ºÐ µ¿¾È¸¸ ³²±ä´Ù.
			m_krgAttacker[i].uiReleaseTime = CurrentTime + uiMemoryTime; 
			#ifdef __TN_3RD_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\t[MemorizeAttacker] 1. party(%d) µî·Ï, damage: %d \r\n", iPartyLeader, a_iDamage ); 
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_3RD_LOG__
			++m_iAttackerCount;
			return;
		}

		if( uiOldestTime > m_krgAttacker[i].uiReleaseTime ) // ÃÖ±Ù±îÁö °ø°ÝÇÑ partyÀÏ¼ö·Ï release time°ªÀÌ Å©´Ù.
		{
			uiOldestTime = m_krgAttacker[i].uiReleaseTime;
			iMinorPartyIndex = i;
		}
	}

	// ½Å±Ô µî·Ïµµ ¸øÇÑ °æ¿ì
	int iGap = uiOldestTime - CurrentTime;
	if( 30000 > iGap ) // 30ÃÊµ¿¾È ¾Æ¹« ¹ÝÀÀÀÌ ¾ø¾ú´Ù¸é, ... ±³Ã¼¸¦ ÇØÁØ´Ù.
	{
        m_krgAttacker[iMinorPartyIndex].iID = iPartyLeader;
		m_krgAttacker[iMinorPartyIndex].iDamage = a_iDamage;
		m_krgAttacker[iMinorPartyIndex].iScore = a_iScore;
		m_krgAttacker[iMinorPartyIndex].uiReleaseTime = CurrentTime + eCmbt_MemoryTime; 
		//++m_iAttackerCount; // ±âÁ¸ÀÇ °ÍÀ» ±³Ã¼ÇÏ´Â °ÍÀÌ±â ¶§¹®¿¡, 1À» Áõ°¡½ÃÄÑÁÙ ÇÊ¿ä°¡ ¾ø´Ù.
	}
}



int CMob::ScoreDamage( TNDAMAGE& a_kDamage )
{	// score¸¦ °è»êÇÑ´Ù.
	int iAggrIndex = pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved2];
	int iScore = 0;
	iScore = a_kDamage.irgPhy[0] * g_krgAggrScore[iAggrIndex].iPhysical;
	iScore += a_kDamage.irgFire[0] * g_krgAggrScore[iAggrIndex].iFire;
	iScore += a_kDamage.irgCold[0] * g_krgAggrScore[iAggrIndex].iCold;
	iScore += a_kDamage.irgLightning[0] * g_krgAggrScore[iAggrIndex].iLightning;
	iScore += a_kDamage.irgPoison[0] * g_krgAggrScore[iAggrIndex].iPoison;

	return iScore;
}


// taunt/detaunt/healingÀ» À§ÇÑ scoreÀ» °è»êÇÑ´Ù.
//@Param
//	- a_eEffect : taunt/detaunt/heal
//	- a_iDamage : healing ¾çÀÌ µÉ ¼öµµ ÀÖ´Ù.
int CMob::ScoreDamage( int a_eEffect, int a_iDamage )
{	// score¸¦ °è»êÇÑ´Ù.
	int iAggrIndex = pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved2];
	int iScore = 0;

	if( eTNAfn_Heal == a_eEffect ) iScore = a_iDamage * g_krgAggrScore[iAggrIndex].iHealing;
	else if( eTNAfn_Taunt == a_eEffect ) iScore = a_iDamage * g_krgAggrScore[iAggrIndex].iTaunt;
	else if( eTNAfn_DeTaunt == a_eEffect ) iScore = a_iDamage * g_krgAggrScore[iAggrIndex].iDetaunt;

	return iScore;
}


void CMob::ClearAggressiveScore()
{
	unsigned int uiGap = CurrentTime - m_kLastTime.uiAttacked;
	if( 60000 < uiGap ) m_iAggressiveScore = 0;
}

//--------------------------------------------------------------------------------------
// PCÀÎ °æ¿ì´Â 8ÃÊ´ç 1È¸ call
// NPCÀÎ °æ¿ì´Â peace»óÅÂ¿¡¼­ tic(0.25ÃÊ)¸¶´Ù call
//--------------------------------------------------------------------------------------
void CMob::ForgetAttacker()
{
	if( 0 >= m_iAttackerCount ) return;

	int iCount = 0;
	//unsigned int uiTime10Sec = eCmbt_MemoryTime - 10000;
	//unsigned int uiTime5Sec = eCmbt_MemoryTime - 5000;
	for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
	{
		if( 0 >= m_krgAttacker[i].iID || MAX_MOB <= m_krgAttacker[i].iID ) continue;
		
		if( CurrentTime > m_krgAttacker[i].uiReleaseTime )
		{ 
			#ifdef __TN_3RD_LOG__
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[ForgetAttacker] %d. party(%d) »èÁ¦, ÃÑ damage: %d, releaseTime: %d \r\n\n", i, m_krgAttacker[i].iID, m_krgAttacker[i].iDamage, m_krgAttacker[i].uiReleaseTime ); 
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_3RD_LOG__
			--m_iAttackerCount;
			memset( &(m_krgAttacker[i]), 0, sizeof(TNATTACKER) );
			continue;
		}

		++iCount;

		if( (eTNMob_PC == m_eMobType) && (MAX_USER <= m_krgAttacker[i].iID) && (3 < iCount) )
		{
			pMob[m_krgAttacker[i].iID].m_iTraceCount += 15;
			--m_iAttackerCount;
			memset( &(m_krgAttacker[i]), 0, sizeof(TNATTACKER) );
			continue;
		}
/*
		unsigned uiGap = m_krgAttacker[i].uiReleaseTime - CurrentTime;
		if( (0==m_krgAttacker[i].iDamage) && (0<m_krgAttacker[i].iScore) )		
		{
			if( uiTime5Sec > uiGap ) pMob[m_krgAttacker[i].iID].m_iTraceCount += 15; // 5ÃÊ ÃÊ°ú µÇ¾ú´Ù. -> ÃßÀûÈ®·ü Áõ°¡

			if( uiTime10Sec > uiGap ) // 10ÃÊ ÃÊ°ú µÇ¾ú´Ù. // ¸®½ºÆ®¿¡¼­ »èÁ¦
			{
				--m_iAttackerCount;				
				memset( &(m_krgAttacker[i]), 0, sizeof(TNATTACKER) );
				continue;
			}			

		}
*/
	}	
}



void CMob::ClearAttacker( int a_iRank )
{
	if( 0 > a_iRank || TN_ATTACKER_COUNT <= a_iRank ) return;

	for( int i = a_iRank; i < TN_ATTACKER_COUNT; ++i )
	{
		if( 0 < m_krgAttacker[i].iID && MAX_MOB > m_krgAttacker[i].iID )
		{
			--m_iAttackerCount;
			memset( &(m_krgAttacker[i]), 0, sizeof(TNATTACKER) );
		}
	}

	//¸¸¾à a_iRank°¡ 0ÀÌ¶ó¸é ¸ðµç attacker¸¦ Áö¿î´Ù´Â °ÍÀÌ´Ù. µû¶ó¼­ ÇöÀçÀÇ target(enemy)µµ clearµÇ¾î¾ß ÇÑ´Ù.
	if( 0 == a_iRank ) ClearCurrentTarget();
}



// <04.04.27> ³»±¸µµ °¨¼Ò ·çÆ¾À» °£¼ÒÈ­ ½ÃÅ´. edited by Á¤Àç¿õ
// ³»±¸µµ°¡ ¹«ÇÑÀÏ °æ¿ì, Áï°¢ return ÇÏ°Ô ÇÔ.
// ¾î´ÀÁ¤µµ ·¹º§ÀÌ µÇ¸é ¸ðµç Àåºñ¸¦ Âø¿ëÇÏ°í ÀÖ±â ¶§¹®¿¡, ÀåÂø ¿©ºÎ¿¡ µû¸¥ Ãß°¡ °¨¼Ò ·çÆ¾À» ±»ÀÌ ³ÖÀ» ÇÊ¿ä°¡ ¾ø´Ù.
void CMob::UpdateEquipDur( int a_iDamage, int a_eItemType )
{
	if( eTNMob_PC != m_eMobType ) return;


	int iDenominator = eConst_EnhanceHardnessOfArmorBase;
	//if( eTNInAfn_EnhanceHardnessOfArmor & m_iInnerAffections )
	{
		//iDenominator = 100;		
		iDenominator = m_krgVariation[eTNVar_EnhanceHardnessOfArmor][eVar_Skill].iPlus + m_krgVariation[eTNVar_EnhanceHardnessOfArmor][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_EnhanceHardnessOfArmor][eVar_Equipment].iPlus;
		if( eConst_EnhanceHardnessOfArmorBase > iDenominator ) iDenominator = eConst_EnhanceHardnessOfArmorBase;
	}
		
	int iDurReduced = 0;
	if( 1 == a_eItemType ) iDurReduced = 1; //a_iDamage / 100; // ¹«±âÀÏ °æ¿ì
	else iDurReduced = a_iDamage / iDenominator; // ¹«±â ÀÌ¿ÜÀÇ °æ¿ì

	MSG_ITEM kMsg;
	kMsg.wType = MSG_ITEM_ID;
	kMsg.wPDULength = WORD( sizeof(MSG_ITEM)-sizeof(HEADER) );
	kMsg.snUserKeyID = m_iHandle;
	kMsg.byType = eItm_Info;
	kMsg.byPlace = ITEM_PLACE_EQUIP;

	if( 1 == a_eItemType ) // ¿À¸¥¼Õ ¹«±âÀÏ °æ¿ì
	{
		if( eDur_Indestructible == MOB.Equip[eTNEqu_OneHandWeapon].snDurability ) return;
		//if( eDur_Indestructible > MOB.Equip[eTNEqu_OneHandWeapon].snDurability ) 
		MOB.Equip[eTNEqu_OneHandWeapon].snDurability -= iDurReduced;
		if( 0 > MOB.Equip[eTNEqu_OneHandWeapon].snDurability )
		{
			MOB.Equip[eTNEqu_OneHandWeapon].snDurability = 0;
			UpdateEquipmentPoints();
		}
		kMsg.byIndex = (BYTE)eTNEqu_OneHandWeapon;
		kMsg.kItem = MOB.Equip[eTNEqu_OneHandWeapon];
	} else
	if( 2 == a_eItemType ) // ¿Þ¼Õ ´Ü°ËÀÏ °æ¿ì
	{
		if( eDur_Indestructible == MOB.Equip[eTNEqu_Shield].snDurability ) return;
		//if( eDur_Indestructible > MOB.Equip[eTNEqu_OneHandWeapon].snDurability ) 
		MOB.Equip[eTNEqu_Shield].snDurability -= iDurReduced;
		if( 0 > MOB.Equip[eTNEqu_Shield].snDurability )
		{
			MOB.Equip[eTNEqu_Shield].snDurability = 0;
			UpdateEquipmentPoints();
		}
		kMsg.byIndex = (BYTE)eTNEqu_Shield;
		kMsg.kItem = MOB.Equip[eTNEqu_Shield];
	}
	else
	{
		int iDice = rand() % 100;

		int iSlot = 0;
		if( 0 <= iDice && 20 > iDice ) iSlot = eTNEqu_Armor;// °©¿Ê 20
		else if( 20 <= iDice && 35 > iDice ) iSlot = eTNEqu_Shield; // ¹æÆÐ 15
		else if( 35 <= iDice && 55 > iDice ) iSlot = eTNEqu_Helmet; // Åõ±¸ 20
		else if( 55 <= iDice && 65 > iDice ) iSlot = eTNEqu_Gloves; // Àå°© 10
		else if( 65 <= iDice && 75 > iDice ) iSlot = eTNEqu_Belt; // º§Æ® 10
		else if( 75 <= iDice && 90 > iDice ) iSlot = eTNEqu_Pants; // ¹ÙÁö 15
		else if( 90 <= iDice && 100 > iDice ) iSlot = eTNEqu_Boots; // ºÎÃ÷ 10

		if( 0 < MOB.Equip[iSlot].snIndex ) // itemÀÌ ÀåÂøµÇ¾î ÀÖ´Ù¸é, ...
		{
			if( eDur_Indestructible <= MOB.Equip[iSlot].snDurability ) return;
			//if( eDur_Indestructible > MOB.Equip[eTNEqu_Armor].snDurability ) 
			int iDurBefore = MOB.Equip[iSlot].snDurability;
			MOB.Equip[iSlot].snDurability -= iDurReduced;
			if( 0 > MOB.Equip[iSlot].snDurability )
			{
				MOB.Equip[iSlot].snDurability = 0;
				UpdateEquipmentPoints();
			}
			kMsg.byIndex = (BYTE)iSlot;
			kMsg.kItem = MOB.Equip[iSlot];

			//if( 0 < m_iDebugFlag2 )
			{
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "Mob:%d, ¹æ¾î±¸:%d, ÀÌÀü³»±¸µµ:%d, ÇöÀç³»±¸µµ:%d(±ïÀÎ³»±¸µµ:%d), °è¼ö:%d \r\n"
						, m_iHandle, MOB.Equip[iSlot].snIndex, iDurBefore, MOB.Equip[iSlot].snDurability, iDurReduced, iDenominator );
					WriteLog( chBuf, ".\\Monster_Log\\[DEBUG]Durability.txt" );
				}
				#endif  
			}
		}
	}

	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(MSG_ITEM) );
}



bool CMob::IsNotLocked()
{
	for( int i = 0; i < TN_ATTACKER_COUNT; ++i ) if( 0 == m_krgAttacker[i].iID ) return true;

	return false;
}



int CMob::DecPrana( double a_dPercent )
{
	if ( 0 == a_dPercent) m_iPranaDec = 0;
	if( 0 >= a_dPercent || 100 < a_dPercent ) return 0;
	//if( eTNSwitch_DecPrana & g_iSwitch ) return;
	if( g_bDecPrana ) return 0;

	double dPercent = a_dPercent / 100;
	int iPrana = (int)(g_irgLevelUp[MOB.byLevel-1] * dPercent );
	iPrana *= (m_dCutDeathPranaRate/100);
	m_iPranaDec = iPrana;

	if( MOB.nPrana < iPrana )
	{
		int iPranaRemained = iPrana - MOB.nPrana ;
		MOB.nPrana -= iPrana;
		if( 0 > MOB.nPrana ) MOB.nPrana = 0;

		// level down
		if( 1 < MOB.byLevel )
		{	
			--MOB.byLevel;
			int iMaxPrana = g_irgLevelUp[MOB.byLevel-1];
			m_iMaxPrana = iMaxPrana;
			MOB.nPrana = iMaxPrana;
			MOB.nPrana -= iPranaRemained;
			if( 0 > MOB.nPrana ) MOB.nPrana = 0;

			NotifyUpdateUIMsg();
			UpdateEquipmentPoints();

			//	±æµå¿øµé¿¡°Ô ·¹º§´Ù¿îÀ» ¾Ë¸°´Ù.
			DBUpdateGuildMember(m_iHandle);
		}		
	}
	else
	{
		MOB.nPrana -= iPrana;
		if( 0 > MOB.nPrana ) MOB.nPrana = 0;
	}

	return iPrana;
}


void CMob::SetViewEquip(int nView, STRUCT_ITEM * pItemdata)
{
	ViewEquip[nView].snIndex		= pItemdata->snIndex;
	ViewEquip[nView].byMainRef		= BASE_GetRefineVariable(pItemdata);
	ViewEquip[nView].byRefineLevel	= pItemdata->byRefineLevel;
}


void CMob::EquipItem( STRUCT_ITEM* a_pItem, int a_eAdd, bool bIsShield )
{
	short	snIndex = a_pItem->snIndex;
	if( 0 >= snIndex || MAX_ITEM_DATA < snIndex ) return; 

	short snSour = snIndex+HT_PARAMTYPE_ITEM_START-1; 

	if(a_eAdd == eAfn_Add)
	{	if(CHTParamIDCheck::HT_bIsItemDefenceHelmet(snSour))		SetViewEquip(eVisualEquipHelmet,	a_pItem);
		else if(CHTParamIDCheck::HT_bIsItemDefenceArmor(snSour))	SetViewEquip(eVisualEquipArmor,		a_pItem);
		else if(CHTParamIDCheck::HT_bIsItemDefenceShield(snSour))	SetViewEquip(eVisualEquipShield,	a_pItem);
		else if(CHTParamIDCheck::HT_bIsItemWeapon(snSour))			//	¹«±â´Â ¿Þ¼Õ, ¿À¸¥¼Õ ÀüºÎ ÀåÂø°¡´ÉÇÏ´Ù
		{											if(bIsShield)	SetViewEquip(eVisualEquipShield,	a_pItem);
													else			SetViewEquip(eVisualEquipOneWeapon,	a_pItem);
		}
		else if(CHTParamIDCheck::HT_bIsItemDefenceShoes(snSour))	SetViewEquip(eVisualEquipBoots,		a_pItem);
		else if(CHTParamIDCheck::HT_bIsItemDefenceGloves(snSour))	SetViewEquip(eVisualEquipGloves,	a_pItem);
		else if(CHTParamIDCheck::HT_bIsItemDefencePants(snSour))	SetViewEquip(eVisualEquipPants,		a_pItem);
	}	else
	if(a_eAdd == eAfn_Remove)
	{	if(CHTParamIDCheck::HT_bIsItemDefenceHelmet(snSour))		ZeroMemory(&ViewEquip[eVisualEquipHelmet],		sizeof(STRUCT_ITEMVIEW));
		else if(CHTParamIDCheck::HT_bIsItemDefenceArmor(snSour))	ZeroMemory(&ViewEquip[eVisualEquipArmor],		sizeof(STRUCT_ITEMVIEW));
		else if(CHTParamIDCheck::HT_bIsItemDefenceShield(snSour))	ZeroMemory(&ViewEquip[eVisualEquipShield],		sizeof(STRUCT_ITEMVIEW));
		else if(CHTParamIDCheck::HT_bIsItemWeapon(snSour))			//	¹«±â´Â ¿Þ¼Õ, ¿À¸¥¼Õ ÀüºÎ Å»Âø°¡´ÉÇÏ´Ù
		{											if(bIsShield)	ZeroMemory(&ViewEquip[eVisualEquipShield],		sizeof(STRUCT_ITEMVIEW));
													else			ZeroMemory(&ViewEquip[eVisualEquipOneWeapon],	sizeof(STRUCT_ITEMVIEW));
		}
		else if(CHTParamIDCheck::HT_bIsItemDefenceShoes(snSour))	ZeroMemory(&ViewEquip[eVisualEquipBoots],		sizeof(STRUCT_ITEMVIEW));
		else if(CHTParamIDCheck::HT_bIsItemDefenceGloves(snSour))	ZeroMemory(&ViewEquip[eVisualEquipGloves],		sizeof(STRUCT_ITEMVIEW));
		else if(CHTParamIDCheck::HT_bIsItemDefencePants(snSour))	ZeroMemory(&ViewEquip[eVisualEquipPants],		sizeof(STRUCT_ITEMVIEW));	
	}
}


int CMob::IncHP( int a_iPoint )
{	
	if( MAX_INT <= MOB.nHP ) return MAX_INT;
	if( 0 >= a_iPoint ) return MOB.nHP;

	//EnterCriticalSection( &m_cs );
	MOB.nHP += a_iPoint;
	if( m_iMaxHP < MOB.nHP ) MOB.nHP = m_iMaxHP;
	//LeaveCriticalSection( &m_cs );

	return MOB.nHP;
}


int CMob::DecHP( int a_iPoint )
{
	#ifdef __TN_PLAYMOVIE__
	if( 1 == m_irgFlag[0] ) return MOB.nHP;
	#endif

	if( 0 >= a_iPoint ) return MOB.nHP;
	//EnterCriticalSection( &m_cs );
	MOB.nHP -= a_iPoint;
	if( 0 > MOB.nHP ) MOB.nHP = 0;
	//LeaveCriticalSection( &m_cs );

	return MOB.nHP;
}



int CMob::IncTP( int a_iPoint )
{
	if( eTNMob_NPC == m_eMobType ) return MOB.nTP;
	if( MAX_INT <= MOB.nTP ) return MAX_INT;
	if( 0 >= a_iPoint ) return MOB.nTP;

	//EnterCriticalSection( &m_cs );
	MOB.nTP += a_iPoint;
	if( m_iMaxTP < MOB.nTP ) MOB.nTP = m_iMaxTP;
	//LeaveCriticalSection( &m_cs );

	return MOB.nTP;
}


int CMob::DecTP( int a_iPoint )
{
	if( eTNMob_NPC == m_eMobType ) return MOB.nTP;
	if( 0 >= a_iPoint ) return MOB.nTP;
	//EnterCriticalSection( &m_cs );
	MOB.nTP -= a_iPoint;
	if( 0 > MOB.nTP ) MOB.nTP = 0;
	//LeaveCriticalSection( &m_cs );

	return MOB.nTP;
}


int CMob::IncGold( int a_iPoint )
{
	if( 0 >= a_iPoint ) return MOB.nRupiah;

	int iHap = MOB.nRupiah + a_iPoint;
	if(iHap<0 || iHap>MAX_INT)
	{	MOB.nRupiah = MAX_INT;
		SendClientMessage(m_iHandle, g_pMessageStringTable[_InvenMoneyFull]);	
	}
	else
		MOB.nRupiah += a_iPoint;

	return MOB.nRupiah;
}


int CMob::DecGold( int a_iPoint )
{
	if( 0 >= a_iPoint ) return MOB.nRupiah;
	//EnterCriticalSection( &m_cs );
	MOB.nRupiah -= a_iPoint;
	if( 0 > MOB.nRupiah ) MOB.nRupiah = 0;
	//LeaveCriticalSection( &m_cs );

	return MOB.nRupiah;
}


int CMob::IncPrana( int a_iPoint )
{
	if( MAX_INT <= MOB.nPrana ) return MAX_INT;
	if( 0 >= a_iPoint ) return MOB.nPrana;

	//EnterCriticalSection( &m_cs );
	//double dPrana = MOB.nPrana + a_iPoint;
	MOB.nPrana += a_iPoint;
	if( m_iMaxPrana < MOB.nPrana ) MOB.nPrana = m_iMaxPrana;
	//LeaveCriticalSection( &m_cs );

	return MOB.nPrana;
}



int CMob::IncBP( int a_iPoint )
{
	int nPrevBraman = MOB.nBramanPoint;
	int nPrevCast = m_byBramanRank;
	if( MAX_INT <= MOB.nBramanPoint ) return MAX_INT;
	if( 0 >= a_iPoint ) return MOB.nBramanPoint;

	if( eTNVSAfn_BlessOfGod & m_iAffections ) a_iPoint += a_iPoint;
	MOB.nBramanPoint += a_iPoint;
	if( MAX_INT < MOB.nBramanPoint ) MOB.nBramanPoint = MAX_INT;

	CheckCaste();

	char temp[256];
	sprintf( temp, "bram Braman %d -> %d, Cast %d -> %d", nPrevBraman, MOB.nBramanPoint, nPrevCast, m_byBramanRank );
	Log( temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
	return MOB.nBramanPoint;
}


int CMob::DecBP( int a_iPoint )
{
	if( 0 >= a_iPoint ) return MOB.nBramanPoint;
	//EnterCriticalSection( &m_cs );
	MOB.nBramanPoint -= a_iPoint;
	if( 0 > MOB.nBramanPoint ) MOB.nBramanPoint = 0;
	//LeaveCriticalSection( &m_cs );

	CheckCaste();

	return MOB.nBramanPoint;
}



void CMob::LetsFlee( int a_iEnemy )
{
	if( MAX_USER > m_iHandle || MAX_MOB <= m_iHandle ) return; // pc ÀÏ °æ¿ì
	if( 0 >= a_iEnemy || MAX_MOB <= a_iEnemy ) return;
	if( eTNImm_Terror & m_iImmunity ) return;

	#ifdef __TN_4TH_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[LetsFlee] ³»À§Ä¡(%d,%d), ÀûÀ§Ä¡(%d,%d), ³» ´Þ¸®±â½ºÇÇµå:%d \r\n", TargetX, TargetY, pMob[a_iEnemy].TargetX, pMob[a_iEnemy].TargetY, pMonsterData[MOB.nTP].byQuest[eMonPrty_RunSpeed] );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_4TH_LOG__

	Think( eTNAI_Flee, a_iEnemy );

	//int iGap = CalDistance2( pMob[a_iEnemy].TargetX, pMob[a_iEnemy].TargetY );
	int x = TargetX - pMob[a_iEnemy].TargetX ;
	int y = TargetY - pMob[a_iEnemy].TargetY;
	while( -4 > x || 4 < x || -4 > y || 4 < y )
	{
		x = (x+1) / 2;
		y = (y+1) / 2;
	}
	x += 4;
	y += 4;
	int iDir = g_pDirectionalTable[y][x];
	x = TargetX;
	y = TargetY;

	int iDistance = pMonsterData[MOB.nTP].byQuest[eMonPrty_RunSpeed] * SECBATTLE/4;
	m_krgPath[0].x = TargetX + (g_pKnockbackTable[iDir][0] * iDistance );
	m_krgPath[0].y = TargetY + (g_pKnockbackTable[iDir][1] * iDistance );
	if( 0 >= m_krgPath[0].y || MAX_GRIDY <= m_krgPath[0].y ) return;
	if( 0 >= m_krgPath[0].x || MAX_GRIDX <= m_krgPath[0].x ) return;	

	if( m_iBlockedCell & g_krgCell[m_krgPath[0].y][m_krgPath[0].x].usProperty )
	{
		m_krgPath[0].x = 0;
		m_krgPath[0].y = 0;
	}
	#ifdef __TN_5TH_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[LetsFlee] (%d,%d) ", m_krgPath[0].x, m_krgPath[0].y );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_5TH_LOG__

	for( int i = 1; i < eFlee_MaxPathCount; ++i )
	{
		m_krgPath[i].x = m_krgPath[i-1].x + (g_pKnockbackTable[iDir][0] * iDistance );
		m_krgPath[i].y = m_krgPath[i-1].y + (g_pKnockbackTable[iDir][1] * iDistance );
		if( 0 >= m_krgPath[i].y || MAX_GRIDY <= m_krgPath[i].y ) break;
		if( 0 >= m_krgPath[i].x || MAX_GRIDX <= m_krgPath[i].x ) break;	
		if( m_iBlockedCell & g_krgCell[m_krgPath[i].y][m_krgPath[i].x].usProperty )
		{
			m_krgPath[i].x = 0;
			m_krgPath[i].y = 0;
		}

		#ifdef __TN_5TH_LOG__
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, " -> (%d,%d)", m_krgPath[i].x, m_krgPath[i].y );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_5TH_LOG__
	}

	#ifdef __TN_5TH_LOG__
	WriteLog( "\r\n", m_szLogFile );
	#endif //__TN_5TH_LOG__

	m_iPathProgress = -1;
	Mode = MOB_FLEE;
}



void CMob::LetsRoam()
{
	int iPathIndex = rand() % eRoam_MaxPathCount;
	m_krgPath[0].x = LastX;
	m_krgPath[0].y = LastY;

	// ´Ü¼ø ¹«½ÄÇÑ ¿À·ù °Ë»ç
	m_krgPath[1].x = m_krgPath[0].x + g_krgRoamPath[iPathIndex][0];
	m_krgPath[1].y = m_krgPath[0].y + g_krgRoamPath[iPathIndex][1];
	if( (0 >= m_krgPath[1].y || MAX_GRIDY <= m_krgPath[1].y ) || ( 0 >= m_krgPath[1].x || MAX_GRIDX <= m_krgPath[1].x ) )
	{
		m_krgPath[1].x = m_krgPath[0].x;
		m_krgPath[1].y = m_krgPath[0].y;
	}
	else if( m_iBlockedCell & g_krgCell[m_krgPath[1].y][m_krgPath[1].x].usProperty )
	{
		m_krgPath[1].x = m_krgPath[0].x;
		m_krgPath[1].y = m_krgPath[0].y;
	}

	m_krgPath[2].x = m_krgPath[1].x + g_krgRoamPath[iPathIndex][2];
	m_krgPath[2].y = m_krgPath[1].y + g_krgRoamPath[iPathIndex][3];
	if( (0 >= m_krgPath[2].y || MAX_GRIDY <= m_krgPath[2].y ) || ( 0 >= m_krgPath[2].x || MAX_GRIDX <= m_krgPath[2].x ) )
	{
		m_krgPath[2].x = m_krgPath[1].x;
		m_krgPath[2].y = m_krgPath[1].y;
	}
	else if( m_iBlockedCell & g_krgCell[m_krgPath[2].y][m_krgPath[2].x].usProperty )
	{
		m_krgPath[2].x = m_krgPath[1].x;
		m_krgPath[2].y = m_krgPath[1].y;
	}

	m_krgPath[3].x = m_krgPath[2].x + g_krgRoamPath[iPathIndex][4];
	m_krgPath[3].y = m_krgPath[2].y + g_krgRoamPath[iPathIndex][5];
	if( (0 >= m_krgPath[3].y || MAX_GRIDY <= m_krgPath[3].y ) || ( 0 >= m_krgPath[3].x || MAX_GRIDX <= m_krgPath[3].x ) )
	{
		m_krgPath[3].x = m_krgPath[2].x;
		m_krgPath[3].y = m_krgPath[2].y;
	}
	else if( m_iBlockedCell & g_krgCell[m_krgPath[3].y][m_krgPath[3].x].usProperty )
	{
		m_krgPath[3].x = m_krgPath[2].x;
		m_krgPath[3].y = m_krgPath[2].y;
	}

	m_krgPath[4].x = m_krgPath[3].x + g_krgRoamPath[iPathIndex][6];
	m_krgPath[4].y = m_krgPath[3].y + g_krgRoamPath[iPathIndex][7];
	if( (0 >= m_krgPath[4].y || MAX_GRIDY <= m_krgPath[4].y ) || ( 0 >= m_krgPath[4].x || MAX_GRIDX <= m_krgPath[4].x ) )
	{
		m_krgPath[4].x = m_krgPath[3].x;
		m_krgPath[4].y = m_krgPath[3].y;
	}
	else if( m_iBlockedCell & g_krgCell[m_krgPath[4].y][m_krgPath[4].x].usProperty )
	{
		m_krgPath[4].x = m_krgPath[3].x;
		m_krgPath[4].y = m_krgPath[3].y;
	}

	m_iPathProgress = -1;
	Mode = MOB_ROAM;
	UpdateSpeed();

	#ifdef __TN_4TH_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[LetsRoam] path (%d,%d) -> (%d,%d) -> (%d,%d) -> (%d,%d) -> (%d,%d)\r\n"
			, m_krgPath[0].x, m_krgPath[0].y, m_krgPath[1].x, m_krgPath[1].y, m_krgPath[2].x, m_krgPath[2].y, m_krgPath[3].x, m_krgPath[3].y, m_krgPath[4].x, m_krgPath[4].y );
		Print( chBuf );
	}
	#endif //__TN_4TH_LOG__
}


void CMob::Think( int a_iState, int a_iTarget )
{
	if( MAX_USER > m_iHandle || MAX_MOB <= m_iHandle ) return;
	if( 0 >= a_iState || eTNAI_MaxEventSort < a_iState ) return;

	int iAIID = MOB.byQuest[eMonPrty_AI];
	if( 0 >= iAIID || eTNAI_MaxAICount < iAIID ) return;

	// AI¿Í Event
	//int iEventID = g_srgAIList[iAIID][a_iState];
	//TriggerEvent( m_iHandle, iEventID, TargetX, TargetY, 0 );

	int iActionListID = g_srgAIList[iAIID][a_iState];
	if( 0 >= iActionListID || eTNAI_MaxActionListCount < iActionListID ) return;

	if( 0 >= g_krgActionList[iActionListID].iCount ) return;
	int iActionIndex = rand() % g_krgActionList[iActionListID].iCount;
	int iActionID = g_krgActionList[iActionListID].srgAction[iActionIndex];
	if( 0 >= iActionID || eTNAI_MaxActionCount < iActionID ) return;

	//------------------------------------
	// 1. Speak(¸»ÇÏ±â)
	//------------------------------------
	int iSpeechContentID = g_krgAction[iActionID].sSpeak;
	Speak( iSpeechContentID, a_iTarget, a_iState );

	//------------------------------------
	// 2. Group
	//------------------------------------
	CallOthers( iActionID, a_iTarget );

	//------------------------------------
	// 3. Action
	//------------------------------------
	React( iActionID, a_iTarget );

	//------------------------------------
	// 4. Skill
	//------------------------------------
	unsigned short usSkillID = g_krgAction[iActionID].sSkill;
	if( 0 < usSkillID )
	{
		for( int iSkillBookIndex = 0; iSkillBookIndex < TN_MONSTER_SKILL_COUNT; ++iSkillBookIndex )
			if( m_krgSkill[iSkillBookIndex].sID  == usSkillID ) break;
		if( TN_MONSTER_SKILL_COUNT <= iSkillBookIndex ) return;

		m_iSkillCharged = iSkillBookIndex; 
		//m_bSkillNotCastYet = true;
		int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index
		m_iCastCount = pSkillData[iSkillIndex].byCastCount;
		if( pSkillData[iSkillIndex].bySyncFlag )
		{
			UseSkill( -1 ); // ¿¬Ãâ¿ë ¸Þ½ÃÁö Àü¼Û
			m_uiActionLock = CurrentTime + pSkillData[iSkillIndex].iAttackSpeed + 250;
		}
	}

	//-------------------------------------
	// 5. Events
	//-------------------------------------
	short sEvent = g_krgAction[iActionID].sEvent;
	if( 0 < sEvent ) TriggerEvent( a_iTarget, sEvent, TargetX, TargetY, m_iHandle, 30 );
}


void CMob::Speak( int a_iSpeechContentID, int a_iTarget, int a_iState )
{
	if( eTNSwitch_MonsterSpeechDisable & g_iSwitch ) return;

	if( 0 >= a_iSpeechContentID || eTNSpch_MaxContentCount < a_iSpeechContentID ) return;
	if( 0 >= g_krgSpeechContent[a_iSpeechContentID].iCount || 5 < g_krgSpeechContent[a_iSpeechContentID].iCount ) return;
	int iCommentIndex = rand() % g_krgSpeechContent[a_iSpeechContentID].iCount;
	int iCommentID = g_krgSpeechContent[a_iSpeechContentID].srgComment[iCommentIndex];
	if( 0 >= iCommentID || eTNSpch_MaxCommentCount < iCommentID ) return;
	if( '\0' == g_szrgComment[iCommentID][0] ) return;
	
	int iSpeechRate = MOB.byQuest[eMonPrty_SpeechRate];
	switch( a_iState ) // °¢ eventº° ¸»ÇÒ È®·üÀ» Â÷º°È­ÇÑ´Ù.
	{
	case eTNAI_CantTrace :
		iSpeechRate = 100;
		break;
	case eTNAI_Dodge :
		iSpeechRate -= 10;
		break;
	}
	
	
	int iDice = rand() % 100; // È®·üÀ» ±¸ÇÑ´Ù.
	if( iDice > iSpeechRate ) return;
	int iCommentType = g_krgSpeechContent[a_iSpeechContentID].srgType[iCommentIndex];
	int iCommentFormat = iCommentType % 10;
	if( 1 == iCommentFormat ) iCommentFormat = rand() % 2; // 0 or 1, commentÀÇ ´Ù¾çÇÔÀ» Ãß±âÇÏ±â À§ÇØ

	char szComment[MAX_CHAT_LENGTH] = { 0,0,0, };
	switch( iCommentFormat )
	{
	case 0 :
		sprintf( szComment, "%s", g_szrgComment[iCommentID] );
		break;
	case 1 :
		if( 0 < a_iTarget && MAX_USER > a_iTarget ) sprintf( szComment, "%s %s", pMob[a_iTarget].MOB.szName, g_szrgComment[iCommentID] );
		else sprintf( szComment, "%s", g_szrgComment[iCommentID] );
		break;
	case 2 :
		if( 0 < a_iTarget && MAX_USER > a_iTarget ) sprintf( szComment, "%s %s", g_szrgComment[iCommentID], pMob[a_iTarget].MOB.szName );
		else sprintf( szComment, "%s", g_szrgComment[iCommentID] );
		break;
	default :
		return;		
		break;
	}

	int iCommentLocation = iCommentType / 10;  // 0~9=>0(Ã¤ÆÃÃ¢), 10~19=>1(¸Ó¸®À§), 20~29=>2(Ã¤ÆÃÃ¢+¸Ó¸®À§)
	if( 0 > iCommentLocation || 2 < iCommentLocation ) iCommentLocation = eTNSpchLoc_Head;

	S_SCP_NOTIFY_CHAT sm;	sm.wType = SCP_NOTIFY_CHAT;
	sm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
	sm.nID = m_iHandle;
	sm.byTextColor = 15;
	sm.byBgColor = 0;
	sm.byTrimuriti = MOB.byTrimuriti;
	sm.byWhere = iCommentLocation; // 0:Ã¤ÆÃÃ¢, 1:¸Ó¸®À§, 2:Ã¤ÆÃÃ¢+¸Ó¸®À§

	strncpy( sm.szMsg, szComment, sizeof(szComment) );
	GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&sm, m_iHandle, 20);
}



void CMob::CallOthers( int a_iActionID, int a_iTarget )
{
	if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) return;

	switch( g_krgAction[a_iActionID].sGroup )
	{
	case eTNGrp_Help :
		{
			if( eTNSts_Help & m_eStatus ) return;  // ½Ã°£ ÁÖ±â¸¶´Ù ÇÑ¹ø¾¿ call µÈ´Ù. ÁÖ±â ½Ã°£ÀÌ µÇ¾úÀ¸¸é help status´Â offµÈ´Ù.			
			m_eStatus = m_eStatus | eTNSts_Help;
			int iHelperCount = 0;
			int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
			int x = 0, y = 0;			
			for( int i = 0; i < iMaxIndex; ++i )
			{
				x = TargetX + g_pDetectEnemyTable[i][0];
				y = TargetY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				int tmob = pMobGrid[y][x];
				if ( MAX_USER > tmob ) continue;
				if(pMob[tmob].MOB.nHP <=0) continue;
				if(pMob[tmob].Mode==MOB_EMPTY)	continue;
				if( MOB_COMBAT == pMob[tmob].Mode ) continue; // ÀÌ°ÍÀº help condition¿¡ ¹ÝÀÀÇÏ¸é, battle ¸ðµå·Î ¹Ù²ï´Ù.
				if( MOB.byQuest[eMonPrty_Reserved0] != pMob[tmob].MOB.byQuest[eMonPrty_Reserved0] ) continue; // °°Àº family¸¸ ¼±ÅÃµÊ.
				
				pMob[tmob].m_eStatus = pMob[tmob].m_eStatus | eTNSts_Help;
				pMob[tmob].MemorizeAttacker( 0, 1, a_iTarget );
				++iHelperCount;
				if( eTNGrp_MaxHelperCount < iHelperCount ) break;
			}
		}
		break;
	case eTNGrp_Link :
		{
			if( eTNSts_Link & m_eStatus ) return;  // ¿ÀÁ÷ ÇÑ¹ø¸¸ link callÀ» ÇÑ´Ù.

			int iLinkCount = 0;
			int iAttackerCount = 0;
			int iAttackerLeader = pMob[a_iTarget].Leader;
			if( 0 >= iAttackerLeader )
			{
				iAttackerLeader = a_iTarget;
				++iAttackerCount;
			}

			for ( int d=0; d<MAX_PARTY;++d )
			{   int fol = pMob[iAttackerLeader].m_irgParty[d];
				if  (fol<MAX_USER) continue; //  PCÀÌ¸é skip
				if  (pMob[fol].Mode==MOB_EMPTY||pMob[fol].MOB.nHP<=0) 
				{   if  (pMob[fol].Mode!=MOB_EMPTY) DeleteMob(fol,1, 0, eTNPrdt_RemoveNormal, 30 );
					pMob[iAttackerLeader].m_irgParty[d]=0;
					continue; // ÆÄÆ¼¿¡¼­ Á¦°Å.
				}
				++iAttackerCount;
			}
			if( MAX_PARTY+1 < iAttackerCount ) iAttackerCount = MAX_PARTY + 1;
			iLinkCount = g_irgPartyVSParty[iAttackerCount];

			m_eStatus = m_eStatus | eTNSts_Link;
			if( 1 >= iLinkCount ) break;

			--iLinkCount; // caller´Â »«´Ù.
			int iHelperCount = 0;
			int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
			int x = 0, y = 0;

			for( int i = 0; i < iMaxIndex; ++i )
			{
				x = TargetX + g_pDetectEnemyTable[i][0];
				y = TargetY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				if( m_iBlockedCell & g_krgCell[y][x].usProperty ) continue;
				int tmob = pMobGrid[y][x];
				if ( MAX_USER > tmob ) continue;
				if(pMob[tmob].MOB.nHP <=0) continue;
				if(pMob[tmob].Mode==MOB_EMPTY)	continue;
				if( MOB_COMBAT == pMob[tmob].Mode ) continue;
				if( MOB.byQuest[eMonPrty_Reserved0] != pMob[tmob].MOB.byQuest[eMonPrty_Reserved0] ) continue; // °°Àº family¸¸ ¼±ÅÃµÊ.

				pMob[tmob].m_eStatus = pMob[tmob].m_eStatus | eTNSts_Link;
				pMob[tmob].MemorizeAttacker( 0, 1, a_iTarget );
				++iHelperCount;
				if( iLinkCount <= iHelperCount ) break;
			}
		}
		break;
	}
}



void CMob::React( int a_iActionID, int a_iTarget )
{
	switch( g_krgAction[a_iActionID].sAction )
	{
	case 30 : // 30
		{
			LetsFlee( a_iTarget );
		}
		break;
	case 60 : // 60 teleportÇØ¼­ Á¢±ÙÇÏ±â
		{
			if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) break;
			int iDist = CalDistance( m_iHandle, a_iTarget );
			if( iDist > m_kSight.sCombat ) break;

			int x = pMob[a_iTarget].TargetX;
			int y = pMob[a_iTarget].TargetY;	
			if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) break;
			if( m_iBlockedCell & g_krgCell[y][x].usProperty ) break;

			Teleport( m_iHandle, x, y );
		}
		break;
	case 70 : // 70
		{
			//int iRange = pSkillData[MOB.Equip[eSkl_Range].snIndex + 500].iRange;
			//m_iPlusRange = 25 - iRange;
		}
		break;
	case 1111 :
		{
			TriggerEvent( 0, 24, 0, 0, m_iHandle, 31 );
		}
		break;
	case 1112 : // ¶óÇª Á×À» ¶§ Ä³¸¯ÅÍµé ±â·Ï
		{
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
				sprintf(chBuf, "\r\n\n\n[%dyy%dmm%ddd %dhh%dms%dss] Raphu(%d) was killed!\r\n"
					, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_iHandle );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
			}
			#endif  

			int iCount = 0;
			for( int y = iStartY; y < iEndY; ++y )
				for( int x = iStartX; x < iEndX; ++x )
				{
					int iMob = pMobGrid[y][x];
					if( 0 >= iMob || MAX_USER <= iMob ) continue;
					++iCount;
					#ifdef __TN_TOP_LOG__
					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "%d. %s\r\n", iCount, pMob[iMob].MOB.szName );
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
					}
					#endif
				}
		}
		break;
	case 1113 : // ¸Þ±×ÇÏ¸»¸° Á×À» ¶§ Ä³¸¯ÅÍµé ±â·Ï
		{
			#ifdef __TN_TOP_LOG__
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\r\n\n\n[%dyy%dmm%ddd %dhh%dms%dss] Meghamalinn(%d) was killed!\r\n"
					, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_iHandle );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
			}
			#endif  

			int iCount = 0;
			for( int i = 0; i < MAX_USER; ++i )
			{
				if( USER_PLAY != pUser[i].Mode ) continue;
				++iCount;
				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "%d. %s\r\n", iCount, pMob[i].MOB.szName );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
				}
				#endif
			}
		}
		break;
	case 1120 : // ºÏµÎÁÂ¼º±º Á×Àº ÈÄ ¿¬Ãâ
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
				sprintf(chBuf, "\r\n\n\n[%dyy%dmm%ddd %dhh%dms%dss] The Left-Side General was killed !\r\n"
					, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
			}
			#endif    
			// StartXZ(658,959),endXZ(638,954))


			int iCount = 0;
			for( int y = iStartY; y < iEndY; ++y )
			{
				for( int x = iStartX; x < iEndX; ++x )
				{
					int iMob = pMobGrid[y][x];
					if( 0 >= iMob || MAX_USER <= iMob ) continue;
					++iCount;
					#ifdef __TN_TOP_LOG__
					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "%d. %s, HP:%d\r\n", iCount, pMob[iMob].MOB.szName, pMob[iMob].MOB.nHP );
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
					}
					#endif
				}
			}
		}
		break;
	case 1121 : // ºÏµÎ¿ì¼º±º Á×Àº ÈÄ ¿¬Ãâ
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
				sprintf(chBuf, "\r\n\n\n[%dyy%dmm%ddd %dhh%dms%dss] The Right-Side General was killed !\r\n"
					, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
			}
			#endif    
			//StartXZ(658,959),endXZ(638,954))

			int iCount = 0;
			for( int y = iStartY; y < iEndY; ++y )
			{
				for( int x = iStartX; x < iEndX; ++x )
				{
					int iMob = pMobGrid[y][x];
					if( 0 >= iMob || MAX_USER <= iMob ) continue;
					++iCount;
					#ifdef __TN_TOP_LOG__
					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "%d. %s, HP:%d\r\n", iCount, pMob[iMob].MOB.szName, pMob[iMob].MOB.nHP );
						WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
					}
					#endif
				}
			}
		}
		break;
	}
}




void CMob::DeliverComment( char* a_pComment )
{
    if( NULL == a_pComment ) return;
	if( MOB.nHP <= 0 ) return;
	if( Mode == MOB_EMPTY ) return;
	if( IsDead() ) return;

	S_SCP_NOTIFY_CHAT sm;	sm.wType = SCP_NOTIFY_CHAT;
	sm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
	sm.nID = m_iHandle;
	sm.byTextColor = 15;
	sm.byBgColor = 0;
	sm.byTrimuriti = MOB.byTrimuriti;
	sm.byWhere = eTNSpchLoc_All;

	memset( &(sm.szMsg), 0 , sizeof( sm.szMsg ) );
	memcpy( &(sm.szMsg), a_pComment, MAX_CHAT_LENGTH );

	GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&sm, m_iHandle, 50);
}



int CMob::FindPath( HS2D_COORD& a_kSrc, HS2D_COORD& a_kTar, HS2D_COORD& a_kDest, HS2D_COORD& a_kPrevPos, int a_iStepDistance, int a_iBlockCell )
{
	bool bEast, bWest, bNorth, bSouth;
	bEast = bWest = bNorth = bSouth = true;

	int iStartX = a_kSrc.x - a_iStepDistance;
	int iEndX = a_kSrc.x + a_iStepDistance;
	int iStartY = a_kSrc.y - a_iStepDistance;
	int iEndY = a_kSrc.y + a_iStepDistance;

	if( a_kPrevPos.x == iStartX ) bWest = false;
	if( a_kPrevPos.x == iEndX ) bEast = false;
	if( a_kPrevPos.y == iStartY ) bNorth = false;
	if( a_kPrevPos.y == iEndY ) bSouth = false;

	//int iEdgeWidth = a_iStepDistance + a_iStepDistance; // 2¹è
	HS2D_COORD krgPos[100];
	int iSize = 0;

	int x = 0, y = 0;

	if( bNorth )
	{
		y = iStartY;  // north
		for( x = iStartX; x <= iEndX; ++x )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
		}
	}

	if( bSouth )
	{
		y = iEndY; // south
		for( x = iStartX; x <= iEndX; ++x )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	if( bWest )
	{		
		x = iStartX;// west
		for( int y = iStartY+1; y <= iEndY-1; ++y )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	if( bEast )
	{
		x = iEndX; // east
		for( int y = iStartY+1; y <= iEndY-1; ++y )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	int iMinDist = 1000;
	for( int i = 0; i < iSize; ++i )
	{
		//if( a_krgPrevPos[eTNPath_Count].iBuf == krgPos[i].iBuf ) continue;
		//if( a_krgPrevPos[eTNPath_Count].iBuf == krgPos[i].iBuf ) continue;
		//if( a_krgPrevPos[eTNPath_Count].iBuf == krgPos[i].iBuf ) continue;
		//if( a_krgPrevPos[3].iBuf == krgPos[i].iBuf ) continue;
		//if( a_krgPrevPos[4].iBuf == krgPos[i].iBuf ) continue;
		//if( a_krgPrevPos[5].iBuf == krgPos[i].iBuf ) continue;
		if( a_iBlockCell & g_krgCell[krgPos[i].y][krgPos[i].x].usProperty ) continue;
		int iDist = CalDistance( a_kTar, krgPos[i], 0, 0 );
		if( iMinDist > iDist )
		{
			a_kDest = krgPos[i];
			iMinDist = iDist;
		}
	}

	if( iMinDist <= a_iStepDistance ) return eTNRes_Succeeded;
	return eTNRes_Failed;

	//if( 1000 == iMinDist ) return eTNRes_Failed;
	//return eTNRes_Succeeded;
}


int CMob::MoveAside( HS2D_COORD& a_kSrc, HS2D_COORD& a_kTar, HS2D_COORD& a_kDest, int a_iStepDistance, int a_iBlockCell )
{
	bool bEast, bWest, bNorth, bSouth;
	bEast = bWest = bNorth = bSouth = true;
	if( 3 > a_iStepDistance ) a_iStepDistance = 3;

	int iStartX = a_kSrc.x - a_iStepDistance;
	int iEndX = a_kSrc.x + a_iStepDistance;
	int iStartY = a_kSrc.y - a_iStepDistance;
	int iEndY = a_kSrc.y + a_iStepDistance;

	HS2D_COORD krgPos[100];
	memset( krgPos, 0, sizeof(krgPos) );
	int iSize = 0;

	int x = 0, y = 0;

	if( bNorth )
	{
		y = iStartY;  // north
		for( x = iStartX; x <= iEndX; ++x )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	if( bSouth )
	{
		y = iEndY; // south
		for( x = iStartX; x <= iEndX; ++x )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	if( bWest )
	{		
		x = iStartX;// west
		for( int y = iStartY+1; y <= iEndY-1; ++y )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	if( bEast )
	{
		x = iEndX; // east
		for( int y = iStartY+1; y <= iEndY-1; ++y )
		{
			krgPos[iSize].x = x;
			krgPos[iSize].y = y;
			++iSize;
		}
	}

	int iMidX, iMidY;
	bool bFound = false;
	int iMinDist = 1000;
	iMinDist = CalDistance( a_kSrc, a_kTar, 0, 0 );
	for( int i = 0; i < iSize; ++i )
	{
		if( a_iBlockCell & g_krgCell[krgPos[i].y][krgPos[i].x].usProperty ) continue;		
		iMidX = ( krgPos[i].x - a_kSrc.x ) / 2;
		iMidY = ( krgPos[i].y - a_kSrc.y ) / 2;
		if( a_iBlockCell & g_krgCell[iMidY][iMidX].usProperty ) continue;
		int iDist = CalDistance( a_kTar, krgPos[i], 0, 0 );
		if( iMinDist > iDist )
		{
			bFound = true;
			a_kDest = krgPos[i];
			iMinDist = iDist;
		}
	}

	if( bFound ) return eTNRes_Succeeded;
	//if( iMinDist <= a_iStepDistance ) return eTNRes_Succeeded;
	return eTNRes_Failed;
}


int CMob::SelectSkill()
{
	int iSkillIndex = 0;
	
	//if( 0 < m_iCastCount ) m_bSkillNotCastYet = true;
	//if( m_bSkillNotCastYet ) // ¾ÆÁ÷ ½ÃÀüÀ» ÇÏÁö ¾Ê¾ÒÀ¸¸é, ÇöÀçÀÇ skillÀ» º¯°æÇÏÁö ¾Ê´Â´Ù.
	if( 0 < m_iCastCount )
	{
		iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index		
		return pSkillData[iSkillIndex].iAllowedTargets;
	}

	if( pMonsterData[MOB.nTP].byQuest[eMonPrty_UseDefaultSkillOnly] )
	{
		m_iSkillCharged = 0; // ±âº» ½ºÅ³¸¸ µî·ÏµÇ¾î ÀÖ´Â °æ¿ì

		iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index		
		return pSkillData[iSkillIndex].iAllowedTargets;
	}

	if( 0 > m_iSkillPatternIndex || eSklPtrn_Size <= m_iSkillPatternIndex ) m_iSkillPatternIndex = 0;
	if( 0 == m_iSkillPatternIndex )
	{
		int iIndex = rand() % 4;
		iIndex += eMonPrty_SklPtrn0; // skill pattern 0~3 Áß¿¡¼­ ÇÏ³ª¸¦ ¼±ÅÃÇÑ´Ù.
		int iSkillPtrnIndex = MOB.byQuest[iIndex];
		if( 0 <= iSkillPtrnIndex && eSklPtrn_Count > iSkillPtrnIndex )
		{
			memcpy( m_irgSkillPattern, g_pSkillPatternTable[iSkillPtrnIndex], sizeof(m_irgSkillPattern) );
		}
		else memset( m_irgSkillPattern, 0, sizeof(m_irgSkillPattern) );
	}

	m_iSkillCharged = m_irgSkillPattern[m_iSkillPatternIndex];
	if( 0 > m_iSkillCharged || 7 < m_iSkillCharged ) m_iSkillCharged = 0;
	++m_iSkillPatternIndex;
	//m_bSkillNotCastYet = true;
	//m_iCastCount = 1;

	iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index
	m_iCastCount = pSkillData[iSkillIndex].byCastCount;
	if( pSkillData[iSkillIndex].bySyncFlag )
	{
		UseSkill( -1 ); // ¿¬Ãâ¿ë ¸Þ½ÃÁö Àü¼Û
		m_uiActionLock = CurrentTime + pSkillData[iSkillIndex].iAttackSpeed + 250;
	}

	return pSkillData[iSkillIndex].iAllowedTargets;
}


void CMob::RefreshPKPrty()
{
	if( 0 >= m_uiPkDurTime )
	{
		m_uiPkDurTime = 0;
		if( m_iAffections & eTNVSAfn_PKAttacker )
		{
			m_iPKDefender = 0;			
			m_iAffections = m_iAffections ^ eTNVSAfn_PKAttacker;
		}
		return;
	}

	if( m_uiPkDurTime < CurrentTime )
	{
		m_iPKDefender = 0;
		m_uiPkDurTime = 0;
		m_iAffections = m_iAffections ^ eTNVSAfn_PKAttacker;
		BroadcastUpdateStatusMsg();
	}
}


byte CMob::get_ArmorType()
{ 
	if( eTNMob_PC == m_eMobType ) return pItemData[MOB.Equip[eTNEqu_Armor].snIndex].byArmorType; 
	return pMonsterData[MOB.nTP].byQuest[eMonPrty_ArmorType];
}



int CMob::get_ItemID( int a_iEquipmentSlot )
{ 
	if( 0 > a_iEquipmentSlot || MAX_EQUIP <= a_iEquipmentSlot ) return 0;
	return pItemData[MOB.Equip[a_iEquipmentSlot].snIndex].sID;
}

void CMob::set_JudgeCombat()
{
	// PC vs PC
	m_krgJudgeCombat[0][0].krgJudgeCombat[0].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[0].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[0][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[0].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[0][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[0].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[0][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[0].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[1].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[1].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[1][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[1].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[1][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[1].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[1][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[1].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[2].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[2].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[2][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[2].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[2][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[2].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[2][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[2].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[3].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[3].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[3][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[3].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[3][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[3].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[3][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[3].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[4].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[4].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[4][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[4].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[4][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[4].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[4][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[4].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[5].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[5].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[5][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[5].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[5][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[5].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[5][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[5].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[6].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[6].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[6][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[6].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[6][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[6].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[6][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[6].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[7].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[7].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[7][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[7].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[7][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[7].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[7][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[7].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[8].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[8].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[8][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[8].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[8][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[8].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[8][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[8].Shuffle();
	m_krgJudgeCombat[0][0].krgJudgeCombat[9].Init();
	m_krgJudgeCombat[0][0].krgJudgeCombat[9].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][0].irgJudgeCombat[9][0] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[9].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][0].irgJudgeCombat[9][1] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[9].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][0].irgJudgeCombat[9][2] );
	m_krgJudgeCombat[0][0].krgJudgeCombat[9].Shuffle();

	// PC vs NPC
	m_krgJudgeCombat[0][1].krgJudgeCombat[0].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[0].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[0][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[0].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[0][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[0].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[0][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[0].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[1].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[1].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[1][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[1].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[1][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[1].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[1][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[1].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[2].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[2].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[2][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[2].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[2][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[2].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[2][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[2].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[3].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[3].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[3][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[3].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[3][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[3].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[3][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[3].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[4].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[4].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[4][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[4].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[4][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[4].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[4][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[4].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[5].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[5].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[5][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[5].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[5][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[5].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[5][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[5].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[6].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[6].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[6][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[6].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[6][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[6].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[6][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[6].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[7].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[7].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[7][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[7].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[7][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[7].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[7][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[7].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[8].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[8].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[8][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[8].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[8][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[8].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[8][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[8].Shuffle();
	m_krgJudgeCombat[0][1].krgJudgeCombat[9].Init();
	m_krgJudgeCombat[0][1].krgJudgeCombat[9].AddCard( eCmbt_Critical, g_krgJudgeCombat[0][1].irgJudgeCombat[9][0] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[9].AddCard( eCmbt_Normal, g_krgJudgeCombat[0][1].irgJudgeCombat[9][1] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[9].AddCard( eCmbt_Dodge, g_krgJudgeCombat[0][1].irgJudgeCombat[9][2] );
	m_krgJudgeCombat[0][1].krgJudgeCombat[9].Shuffle();

	// NPC vs PC
	m_krgJudgeCombat[1][0].krgJudgeCombat[0].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[0].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[1][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[0].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[0][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[0].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[0][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[0].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[1].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[1].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[1][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[1].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[1][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[1].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[1][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[1].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[2].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[2].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[2][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[2].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[2][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[2].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[2][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[2].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[3].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[3].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[3][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[3].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[3][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[3].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[3][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[3].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[4].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[4].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[4][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[4].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[4][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[4].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[4][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[4].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[5].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[5].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[5][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[5].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[5][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[5].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[5][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[5].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[6].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[6].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[6][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[6].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[6][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[6].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[6][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[6].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[7].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[7].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[7][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[7].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[7][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[7].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[7][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[7].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[8].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[8].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[8][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[8].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[8][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[8].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[8][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[8].Shuffle();
	m_krgJudgeCombat[1][0].krgJudgeCombat[9].Init();
	m_krgJudgeCombat[1][0].krgJudgeCombat[9].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][0].irgJudgeCombat[9][0] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[9].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][0].irgJudgeCombat[9][1] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[9].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][0].irgJudgeCombat[9][2] );
	m_krgJudgeCombat[1][0].krgJudgeCombat[9].Shuffle();

	// NPC vs NPC
	m_krgJudgeCombat[1][1].krgJudgeCombat[0].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[0].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[1][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[0].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[0][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[0].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[0][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[0].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[1].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[1].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[1][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[1].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[1][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[1].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[1][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[1].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[2].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[2].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[2][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[2].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[2][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[2].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[2][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[2].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[3].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[3].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[3][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[3].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[3][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[3].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[3][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[3].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[4].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[4].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[4][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[4].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[4][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[4].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[4][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[4].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[5].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[5].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[5][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[5].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[5][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[5].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[5][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[5].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[6].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[6].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[6][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[6].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[6][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[6].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[6][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[6].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[7].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[7].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[7][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[7].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[7][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[7].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[7][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[7].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[8].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[8].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[8][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[8].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[8][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[8].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[8][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[8].Shuffle();
	m_krgJudgeCombat[1][1].krgJudgeCombat[9].Init();
	m_krgJudgeCombat[1][1].krgJudgeCombat[9].AddCard( eCmbt_Critical, g_krgJudgeCombat[1][1].irgJudgeCombat[9][0] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[9].AddCard( eCmbt_Normal, g_krgJudgeCombat[1][1].irgJudgeCombat[9][1] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[9].AddCard( eCmbt_Dodge, g_krgJudgeCombat[1][1].irgJudgeCombat[9][2] );
	m_krgJudgeCombat[1][1].krgJudgeCombat[9].Shuffle();
}



// Á×À» ¶§³ª Á¾·áÇÒ ¶§ ¹ß»ýÀ» ÇÑ´Ù.
void CMob::DropKalaCore( int a_iReturnToShrine )
{
	if( !(eTNVSAfn_HaveKalaCore & m_iAffections) ) return; // kala-core¸¦ ¼ÒÀ¯ÇÏ°í ÀÖ´Ù¸é, ¶³¾î¶ß·Á¾ß ÇÏ°í, ¼Ò¸êµÇ¾î¼­´Â ¾ÈµÈ´Ù.
	if( SERVER_KRUMA_HIGH != (ServerIndex + 1) ) // Å©·ç¸¶°¡ ¾Æ´Ï¸é ±×³É »èÁ¦¸¦ ½ÃÅ²´Ù.
	{
		RemoveKalaCoreInInventory( m_iHandle );
		return;
	}

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	int x, y;
	x = TargetX;
	y = TargetY;

	int irgSlot[3][eConst_CheckItemSlot] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, }; // item °Ë»ç/Á¦°Å¸¦ À§ÇÑ slot No ±â·Ï
	int irgCount[3] = { 0,0,0, };
	irgCount[0] = CheckItem( eKalaCore_Brahma, 1, irgSlot[0] ); // ¿ä±¸»çÇ×ÀÌ ¸¸Á·ÇÏÁö ¸øÇÏ¸é 0À» return
	irgCount[1] = CheckItem( eKalaCore_Vishnu, 1, irgSlot[1] ); // ¿ä±¸»çÇ×ÀÌ ¸¸Á·ÇÏÁö ¸øÇÏ¸é 0À» return
	irgCount[2] = CheckItem( eKalaCore_Siva, 1, irgSlot[2] ); // ¿ä±¸»çÇ×ÀÌ ¸¸Á·ÇÏÁö ¸øÇÏ¸é 0À» return

	//int iRes = eTNRes_Succeeded;
	int iTotalCount = irgCount[0]+irgCount[1]+irgCount[2];
	if( 1 > iTotalCount )
	{
		{
			char chBuf[512] = { 0,0,0, };
			sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] DropKalaCore() > Have no kala-core! -> TotalCount:%d \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				,iTotalCount
				);
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
		}
		return; //iRes = eTNRes_Failed;
	}
	if( 1 < iTotalCount )
	{
		{
			char chBuf[512] = { 0,0,0, };
			sprintf( chBuf, "<<ERROR [%dmm%ddd %dhh%dmi%dss] DropKalaCore() > Two or more kala-core is founded! -> TotalCount:%d \r\n"
				, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				,iTotalCount
				);
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
		}		
	}
	
	int iTxtIndex = 0;
	int iMonsterID = 0;
	int iClan = 0;
	int iInventorySlot = -1;
	if( 0 < irgCount[0] )//if( eKalaCore_Brahma == iID )
	{
		iClan = eTNClan_Brahma;
		iMonsterID = eKala_Brahma;
		iTxtIndex = _Brahma;
		for( int k = 0; k < 5; ++k )
		{
			if( -1 < irgSlot[0][k] )
			{
				iInventorySlot = irgSlot[0][k];
				break;
			}
		}
	}
	else if( 0 < irgCount[1] )//else if( eKalaCore_Vishnu == iID )
	{
		iClan = eTNClan_Vishnu;
		iMonsterID = eKala_Vishnu;
		iTxtIndex = _Vishnu;
		for( int k = 0; k < 5; ++k )
		{
			if( -1 < irgSlot[1][k] )
			{
				iInventorySlot = irgSlot[1][k];
				break;
			}
		}
	}
	else if( 0 < irgCount[2] )//else if( eKalaCore_Siva == iID )
	{
		iClan = eTNClan_Siva;
		iMonsterID = eKala_Siva;
		iTxtIndex = _Siva;
		for( int k = 0; k < 5; ++k )
		{
			if( -1 < irgSlot[2][k] )
			{
				iInventorySlot = irgSlot[2][k];
				break;
			}
		}
	}

	// ºó ÀÚ±â ÁÖ½Å Á¦´ÜÀ» Ã£¾Æ¼­ ±×°÷¿¡ À§Ä¡ÇÑ´Ù. ¸¸¾à ºó ÀÚ¸®°¡ ¾ø´Ù¸é, ¸Ê Áß¾Ó¿¡ Ä®¶óÄÚ¾î ÇüÅÂ·Î À§Ä¡ÇÏ°Ô µÈ´Ù.
	if( (eTNCell_NotAllowedKalaCore & g_krgCell[TargetY][TargetX].usProperty) || a_iReturnToShrine )
	{	
		int iAltarSlot = g_kKalaSystem.FindEmptyAltar( iClan );
		if( -1 == iAltarSlot )
		{// ºó ÀÚ±â ÁÖ½Å Á¦´ÜÀÌ ¾ø´Ù. ¸Ê Áß¾Ó¿¡ Ä®¶óÄÚ¾î¸¦ ¶³¾î¶ß¸°´Ù.
			x = 526;
			y = 476;
		}
		else
		{// ºó ÀÚ±â ÁÖ½Å Á¦´ÜÀ» Ã£¾Ò´Ù. Á¦´Ü¿¡ ³õ´Â´Ù.
			g_kKalaSystem.InstallKala( iMonsterID, iClan, iAltarSlot, m_iHandle ); // ³»ºÎ¿¡¼­ ChangeKalaLoc() È£Ãâ-> kalaÁ¤º¸ º¯°æ

			S_SCP_RESP_ITEM_SET itemset;
			itemset.wType = SCP_RESP_ITEM_SET;
			itemset.byType = SET_ITEM_DELETE;
			itemset.byPlace = ITEM_PLACE_INVEN; // inventory
			itemset.byIndex = iInventorySlot;
			memcpy(&(itemset.sitem), &(MOB.Inven[iInventorySlot]), sizeof(STRUCT_ITEM));
			pUser[m_iHandle].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));

			ZeroMemory(&MOB.Inven[iInventorySlot], sizeof(STRUCT_ITEM));
			m_iAffections = m_iAffections ^ eTNVSAfn_HaveKalaCore;	
			BroadcastUpdateStatusMsg();

			char szMsg[1024] = { 0,0,0, };
			sprintf( szMsg, g_pMessageStringTable[_Drop_Register_Kala_Core], MOB.szName, g_pMessageStringTable[iTxtIndex], g_krgKalaAltar[iAltarSlot].x, g_krgKalaAltar[iAltarSlot].y );
			PostMessageToZone( szMsg );

			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				strcat( szMsg, chBuf );
				WriteLog( szMsg, g_szrgLogFileName[eLogFileName_KalaSystem] );
			}

			MoveKalaRewarder();

			return; // ¼º°ø
		}
	} // if( (eTNCell_Shrine & g_krgCell[TargetY][TargetX].usProperty) || a_iReturnToShrine )

	//iKalaCore = iID;
	S_SCP_RESP_ITEM_DROP kMsg;
	kMsg.wType = SCP_RESP_ITEM_DROP;
	kMsg.snResult = REPLY_ACK_OK;
	kMsg.byPlace = (byte)ITEM_PLACE_INVEN;
	kMsg.byIndex = iInventorySlot;
	kMsg.dwMoney = 0;
	kMsg.byType = DROP_TYPE_ITEM;
	pUser[m_iHandle].cSock.AddMessage((char*)&kMsg, sizeof(S_SCP_RESP_ITEM_DROP));
	
	int iDropRes = CreateItem( x, y, &MOB.Inven[iInventorySlot], MOB.snTribe, 0, 0, 0 );
	if( 0 == iDropRes )
	{//<ToDo> Log¸¦ ³²°Ü¾ß ÇÑ´Ù.				
	}

	g_kKalaSystem.ChangeKalaLoc( TNKalaSystem::eLoc_Inventory, 0, 0, 0, 0, m_iHandle, TNKalaSystem::eLoc_Ground, 0, 0, x, y, 0 );

	ZeroMemory(&MOB.Inven[iInventorySlot], sizeof(STRUCT_ITEM));
	m_iAffections = m_iAffections ^ eTNVSAfn_HaveKalaCore;
	BroadcastUpdateStatusMsg();

	char szMsg[1024] = { 0,0,0, };	
	sprintf( szMsg, g_pMessageStringTable[_Drop_kala_Core], MOB.szName, g_pMessageStringTable[iTxtIndex], x, y );
	PostMessageToZone( szMsg );

	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, " - [%dmm%ddd %dhh%dmi%dss]\r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
		strcat( szMsg, chBuf );
		WriteLog( szMsg, g_szrgLogFileName[eLogFileName_KalaSystem] );
	}

	NotifyRvRStatus();
	// ´©°¡ kala¸¦ ¾î´À ÁÂÇ¥ ±ÙÃ³¿¡ ¶³¾î¶ß·È´Ù´Â ¸Þ½ÃÁö¸¦ »Ñ·Á¾ß ÇÑ´Ù.
	//ÇöÀç °¢ ÁÖ½Åº° Ä®¶ó º¸À¯ ÇöÈ² ¸Þ½ÃÁö

	RemoveKalaCoreInInventory( m_iHandle ); // ÃÖÁ¾ ÀçÈ®ÀÎ
}


void CMob::CheckCaste() //fors_debug master_skill ÅÐ¶ÏÖ÷ÉñµÈ¼¶°´ÅÅÃûµÄµØ·½
{	
	m_iCaste = eTNCaste_Sudra3;
/*		if( MOB.nBramanPoint>360000 ) m_iCaste = eTNCaste_MahaRaja1;
		else if( MOB.nBramanPoint>330000 && MOB.nBramanPoint<=360000 ) m_iCaste = eTNCaste_MahaRaja2;
		else if( MOB.nBramanPoint>300000 && MOB.nBramanPoint<=330000 ) m_iCaste = eTNCaste_MahaRaja3;
		else if( MOB.nBramanPoint>270000 && MOB.nBramanPoint<=300000 ) m_iCaste = eTNCaste_Avatara1;
		else if( MOB.nBramanPoint>240000 && MOB.nBramanPoint<=270000 ) m_iCaste = eTNCaste_Avatara2;
		else if( MOB.nBramanPoint>210000 && MOB.nBramanPoint<=240000 ) m_iCaste = eTNCaste_Avatara3;
		else if( MOB.nBramanPoint>180000 && MOB.nBramanPoint<=210000 ) m_iCaste = eTNCaste_Braman1;
		else if( MOB.nBramanPoint>150000 && MOB.nBramanPoint<=180000 ) m_iCaste = eTNCaste_Braman2;
		else if( MOB.nBramanPoint>120000 && MOB.nBramanPoint<=150000 ) m_iCaste = eTNCaste_Braman3;
		else if( MOB.nBramanPoint>90000 && MOB.nBramanPoint<=120000 ) m_iCaste = eTNCaste_Cushatri1;
		else if( MOB.nBramanPoint>60000 && MOB.nBramanPoint<=90000 ) m_iCaste = eTNCaste_Cushatri2;
		else if( MOB.nBramanPoint>=30000 && MOB.nBramanPoint<=60000 ) m_iCaste = eTNCaste_Cushatri3; 

*/
	if( g_eCountryID == eCountryKorea )
	{
		if( m_byBramanRank>0 && m_byBramanRank<=eTNCasteRank_MahaRaja1 ) m_iCaste = eTNCaste_MahaRaja1;
		else if( m_byBramanRank>eTNCasteRank_MahaRaja1 && m_byBramanRank<=eTNCasteRank_MahaRaja2 ) 
		  { 
		     if( MOB.nBramanPoint>330000)  m_iCaste = eTNCaste_MahaRaja2;
		     else m_iCaste = eTNCaste_MahaRaja3;
		     
		  }
		else if( m_byBramanRank>eTNCasteRank_MahaRaja2 && m_byBramanRank<=eTNCasteRank_MahaRaja3 ) 
		   {
		     if( MOB.nBramanPoint>300000)
		      m_iCaste = eTNCaste_MahaRaja3;
		     else m_iCaste = eTNCaste_Avatara1;
		      
		    }
		else if( m_byBramanRank>eTNCasteRank_MahaRaja3 && m_byBramanRank<=eTNCasteRank_Avatara1 )
		   { 
		     if( MOB.nBramanPoint>270000  ) m_iCaste = eTNCaste_Avatara1;
		     else m_iCaste = eTNCaste_Avatara2;
		     
		   }
		else if( m_byBramanRank>eTNCasteRank_Avatara1 && m_byBramanRank<=eTNCasteRank_Avatara2 ) 
		   {
		     if( MOB.nBramanPoint>240000 ) m_iCaste = eTNCaste_Avatara2;
		     else  m_iCaste = eTNCaste_Avatara3;
		      
		   }
		else if( m_byBramanRank>eTNCasteRank_Avatara2 && m_byBramanRank<=eTNCasteRank_Avatara3 )
		      {
		       if( MOB.nBramanPoint>210000 )  m_iCaste = eTNCaste_Avatara3;
		       else  m_iCaste = eTNCaste_Braman1;
		      }
		else if( m_byBramanRank>eTNCasteRank_Avatara3 && m_byBramanRank<=eTNCasteRank_Braman1 ) 
		     {
		       if( MOB.nBramanPoint>180000 )    m_iCaste = eTNCaste_Braman1;
		       else m_iCaste = eTNCaste_Braman2;
		       
		      }
		else if( m_byBramanRank>eTNCasteRank_Braman1 && m_byBramanRank<=eTNCasteRank_Braman2 ) 
		     {
		       if( MOB.nBramanPoint>150000 ) m_iCaste = eTNCaste_Braman2;
		       else m_iCaste = eTNCaste_Braman3;
		      }
		else if( m_byBramanRank>eTNCasteRank_Braman2 && m_byBramanRank<=eTNCasteRank_Braman3 ) 
		     {
		      if( MOB.nBramanPoint>120000)  m_iCaste = eTNCaste_Braman3;
		      else m_iCaste = eTNCaste_Cushatri1;
		     }
		else if( m_byBramanRank>eTNCasteRank_Braman3 && m_byBramanRank<=eTNCasteRank_Cushatri1 ) m_iCaste = eTNCaste_Cushatri1;
		else if( m_byBramanRank>eTNCasteRank_Cushatri1 && m_byBramanRank<=eTNCasteRank_Cushatri2 ) m_iCaste = eTNCaste_Cushatri2;
		else if( m_byBramanRank>eTNCasteRank_Cushatri2 && m_byBramanRank<=eTNCasteRank_Cushatri3 ) m_iCaste = eTNCaste_Cushatri3;
		else
		{
			if( 2000 > MOB.nBramanPoint )  m_iCaste = eTNCaste_Sudra3;
			else if( 2000 <= MOB.nBramanPoint && 4000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Sudra2;
			else if( 4000 <= MOB.nBramanPoint && 6000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Sudra1;
			else if( 6000 <= MOB.nBramanPoint && 8000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha3;
			else if( 8000 <= MOB.nBramanPoint && 10000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha2;
			else if( 10000 <= MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha1;
		}
	}	

/*	if( g_eCountryID == eCountryKorea )
	{
		if( m_byBramanRank>0 && m_byBramanRank<=eTNCasteRank_MahaRaja1 ) m_iCaste = eTNCaste_MahaRaja1;
		else if( m_byBramanRank>eTNCasteRank_MahaRaja1 && m_byBramanRank<=eTNCasteRank_MahaRaja2 ) m_iCaste = eTNCaste_MahaRaja2;
		else if( m_byBramanRank>eTNCasteRank_MahaRaja2 && m_byBramanRank<=eTNCasteRank_MahaRaja3 ) m_iCaste = eTNCaste_MahaRaja3;
		else if( m_byBramanRank>eTNCasteRank_MahaRaja3 && m_byBramanRank<=eTNCasteRank_Avatara1 ) m_iCaste = eTNCaste_Avatara1;
		else if( m_byBramanRank>eTNCasteRank_Avatara1 && m_byBramanRank<=eTNCasteRank_Avatara2 ) m_iCaste = eTNCaste_Avatara2;
		else if( m_byBramanRank>eTNCasteRank_Avatara2 && m_byBramanRank<=eTNCasteRank_Avatara3 ) m_iCaste = eTNCaste_Avatara3;
		else if( m_byBramanRank>eTNCasteRank_Avatara3 && m_byBramanRank<=eTNCasteRank_Braman1 ) m_iCaste = eTNCaste_Braman1;
		else if( m_byBramanRank>eTNCasteRank_Braman1 && m_byBramanRank<=eTNCasteRank_Braman2 ) m_iCaste = eTNCaste_Braman2;
		else if( m_byBramanRank>eTNCasteRank_Braman2 && m_byBramanRank<=eTNCasteRank_Braman3 ) m_iCaste = eTNCaste_Braman3;
		else if( m_byBramanRank>eTNCasteRank_Braman3 && m_byBramanRank<=eTNCasteRank_Cushatri1 ) m_iCaste = eTNCaste_Cushatri1;
		else if( m_byBramanRank>eTNCasteRank_Cushatri1 && m_byBramanRank<=eTNCasteRank_Cushatri2 ) m_iCaste = eTNCaste_Cushatri2;
		else if( m_byBramanRank>eTNCasteRank_Cushatri2 && m_byBramanRank<=eTNCasteRank_Cushatri3 ) m_iCaste = eTNCaste_Cushatri3;
		else
		{
			if( 2000 > MOB.nBramanPoint )  m_iCaste = eTNCaste_Sudra3;
			else if( 2000 <= MOB.nBramanPoint && 4000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Sudra2;
			else if( 4000 <= MOB.nBramanPoint && 6000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Sudra1;
			else if( 6000 <= MOB.nBramanPoint && 8000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha3;
			else if( 8000 <= MOB.nBramanPoint && 10000 > MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha2;
			else if( 10000 <= MOB.nBramanPoint ) m_iCaste = eTNCaste_Baisha1;
		}
	}	
*/
}


void CMob::CalCasteSkillPoint()
{
	/*
	int iBaseIDNum = 0;
	if( (TRIBE_NAGA==MOB.snTribe) || (TRIBE_KINNARA==MOB.snTribe) ) iBaseIDNum = 3000;
	else if( (TRIBE_ASURA==MOB.snTribe) || (TRIBE_RAKSHASA==MOB.snTribe) ) iBaseIDNum = 3100;
	else if( (TRIBE_YAKSA==MOB.snTribe) || (TRIBE_GANDHARVA==MOB.snTribe) ) iBaseIDNum = 3200;
	else if( (TRIBE_DEVA==MOB.snTribe) || (TRIBE_GARUDA==MOB.snTribe) ) iBaseIDNum = 3300;
	*/

	//bool bInvalidCasteSkill = false;
	int iCasteSkillPointUsed = 0;
	for( int i = 65; i < 80; ++i )
	{ // Àý´ë·Î ÁÖ½Å ½ºÅ³ÀÌ´Ù.
		int iDataIndex = m_krgSkill[i].iIndex;
		if( pSkillData[iDataIndex].kReq.iClass > m_iCaste )
		{
			MOB.bySkill[i] = 0;

			S_SCP_RESP_LEARN_SKILL kMsg;
			kMsg.wType = SCP_RESP_LEARN_SKILL;
			kMsg.byRes = (BYTE)eTNRes_Succeeded;
			kMsg.kSkill.snID = pSkillData[iDataIndex].sID;
			kMsg.kSkill.byLevel = 0;

			pUser[m_iHandle].cSock.AddMessage((char*)&kMsg,sizeof(S_SCP_RESP_LEARN_SKILL));
		}
		if( 0 > MOB.bySkill[i] ) MOB.bySkill[i] = 0;
		iCasteSkillPointUsed += MOB.bySkill[i];
	}

	int iTotalCasteSkillPoint = (m_iCaste/3) * 2 - 3; // 1, 3, 5, 7
	if( 0 > iTotalCasteSkillPoint ) iTotalCasteSkillPoint = 0;
	//if( eTNCaste_MahaRaja3 <= m_iCaste ) ++iTotalCasteSkillPoint; // ¸¶ÇÏ¶óÀÚÀÌ¸é ÃÑ 2point¸¦ ¾ò°ÔµÈ´Ù.
	int iCasteSPRemaining = iTotalCasteSkillPoint - iCasteSkillPointUsed;
	//if( (0 > iCasteSPRemaining) || bInvalidCasteSkill ) // ÁÖ½Å µî±ÞÀÌ ¶³¾îÁø °ÍÀÌ´Ù.
	if( 0 > iCasteSPRemaining ) // ÁÖ½Å µî±ÞÀÌ ¶³¾îÁø °ÍÀÌ´Ù.
	{// ÁÖ½Å ½ºÅ³À» ÃÊ±âÈ­ÇÑ´Ù.
		for( int i = 65; i < 80; ++i ) MOB.bySkill[i] = 0;
		iCasteSPRemaining = iTotalCasteSkillPoint;
		SendClientMessage( m_iHandle, g_pMessageStringTable[_CasteSkillIsReseted] );
	}
	m_kCasteSPRemaining.Init( 10000, iCasteSPRemaining );

	NotifyUpdateUIMsg();
}


void CMob::CheckCasteSkillLevel()
{
	bool bChanged = false;
	for( int i = 65; i < 80; ++i )
	{
		int iDataIndex = m_krgSkill[i].iIndex;
		if( pSkillData[iDataIndex].kReq.iClass > m_iCaste )
		{
			MOB.bySkill[i] = 0;
			bChanged = true; 
		}
	}

	if( bChanged ) CalCasteSkillPoint();
}

int CMob::set_Skill( unsigned short a_sSkillID )
{
	for( int iSkillBookIndex = 0; iSkillBookIndex < TN_MONSTER_SKILL_COUNT; ++iSkillBookIndex )
		if( m_krgSkill[iSkillBookIndex].sID  == a_sSkillID ) break;
	if( TN_MONSTER_SKILL_COUNT <= iSkillBookIndex ) return eTNRes_Failed;

	m_iSkillCharged = iSkillBookIndex; 
	//m_bSkillNotCastYet = true;
	int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data ¹è¿­»óÀÇ index
	m_iCastCount = pSkillData[iSkillIndex].byCastCount;

	return eTNRes_Succeeded;
}

void CMob::set_Trimuriti( int a_eClan ) 
{
	if( eZoneType_Guild == g_iZoneType ) return;

	m_byClan = MOB.byTrimuriti = (byte)a_eClan; 
} 

int CMob::CheckMoveHack( int a_iMoveType, int conn )
{
	//fors_debug checkmovehack first code not modify
	if( g_irgSpeedConsider[5] ) return eTNRes_Succeeded;
	if( eTNClan_GM == m_byClan ) return eTNRes_Succeeded;
	if( m_kMoveRecord.uiElapsed > CurrentTime ) return eTNRes_Succeeded;

	int iTimeBetween = CurrentTime - m_kMoveRecord.uiElapsed + g_irgSpeedConsider[0];
	if( (0 == m_kMoveRecord.uiElapsed) || (g_irgSpeedConsider[1] < iTimeBetween) || ((2 != a_iMoveType) && (3 != a_iMoveType)) ) 
	{ // /ÃÊ±âÈ­, ÀÌµ¿ typeÀÌ °È±â³ª ¶Ù±â°¡ ¾Æ´Ò °æ¿ì(teleport,...), ½Ã°£°¸ÀÌ refresh¸¦ ³ÑÀ» °æ¿ì
		m_kMoveRecord.uiElapsed = CurrentTime + g_irgSpeedConsider[0]; // 1ÃÊ µÚ
		m_kMoveRecord.iSpeed = m_iMoveSpeed;
		m_kMoveRecord.kPos.x = TargetX;
		m_kMoveRecord.kPos.y = TargetY;

		return eTNRes_Succeeded;
	}

	HS2D_COORD kCur;	
	kCur.x = TargetX;
	kCur.y = TargetY;
	int iMoveDist = CalDistance( m_kMoveRecord.kPos, kCur, 0, 0 );
	iMoveDist *= 10000;
	int iSpeedAvg = (m_kMoveRecord.iSpeed + m_iMoveSpeed) * 5; // XXXX/2*10;
	
	m_kMoveRecord.kPos = kCur;
	m_kMoveRecord.iSpeed = m_iMoveSpeed;
	
	if( 0 >= iTimeBetween ) return eTNRes_Succeeded;
	//if( 50000 < iMoveDist ) return eTNRes_Succeeded;

	int iDistPerTime = iMoveDist / iTimeBetween;
	int iSpeedCorrect = iSpeedAvg / 4 + g_irgSpeedConsider[2];
	int iDistDiff = iDistPerTime - (iSpeedAvg + iSpeedCorrect);
	
	m_kMoveRecord.uiElapsed = CurrentTime + g_irgSpeedConsider[0]; // 

	//char chBuf[512] = { 0,0,0, };
	//sprintf(chBuf, "move hack> name %s, iTimeBetween:%d, iMoveDist:%d, iDistPerTime:%d, iSpeedAvg:%d, SpeedCorrect:%d, iDistDiff:%d  \n",pMob[conn].MOB.szName,iTimeBetween, iMoveDist, iDistPerTime, iSpeedAvg, iSpeedCorrect, iDistDiff );
	//WriteLog( chBuf,  g_szrgLogFileName[eLogFileName_Assert] );

//	#ifdef __TN_TOP_LOG__
	//if( g_irgSpeedConsider[4] < iDistPerTime )
//	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
//		char chBuf[512] = { 0,0,0, };
//		sprintf(chBuf, "move hack> %dÀÏ%d½Ã%dºÐ> Ä³¸¯ÅÍ:%s, iTimeBetween:%d, iMoveDist:%d, iDistPerTime:%d, iSpeedAvg:%d, SpeedCorrect:%d, iDistDiff:%d \n\n"
//			, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, MOB.szName
//			,iTimeBetween, iMoveDist, iDistPerTime, iSpeedAvg, iSpeedCorrect, iDistDiff );
//		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
//	}
//	#endif
//fors_debug add_check_speed log cc not kick
	if( 0 < iDistDiff )
	{ // hack user
		//WriteLog( "***", m_szLogFile );
		int iCheckHow=0;
		if (g_iZoneID==10)
			iCheckHow=16;
		else
		    iCheckHow=25;
		if( iCheckHow >= iDistDiff ) return eTNRes_Succeeded ;//g_irgSpeedConsider[3];  // light
		else {
			++m_kMoveRecord.behackedcount;
			if (m_kMoveRecord.behackedcount >=3) 
			{
	          char chBuf[512] = { 0,0,0, };
	          sprintf(chBuf, "be kicked name:%s > iTimeBetween:%d, iMoveDist:%d, iDistPerTime:%d, iSpeedAvg:%d, SpeedCorrect:%d, iDistDiff:%d \n",pMob[conn].MOB.szName,iTimeBetween, iMoveDist, iDistPerTime, iSpeedAvg, iSpeedCorrect, iDistDiff );
	          WriteLog( chBuf,  g_szrgLogFileName[eLogFileName_Assert] );
	          return 15; // heavy
			}
		}
	}
	else
	{
		++m_kMoveRecord.nohackcount;
		if (m_kMoveRecord.nohackcount >=5){m_kMoveRecord.behackedcount=0;m_kMoveRecord.nohackcount=0;}

	}

	return eTNRes_Succeeded;
}


void CMob::InitStatus()
{
	m_iAttackCount = 0; // °ø°ÝÈ½¼ö
	m_iCantTraceTarget = 0;
	m_iTraceCount = 0; // ´ÜÀ§ ÃßÀûÈ½¼ö
	m_iTotalTraceCount = 0; // ÃÑ ÃßÀûÈ½¼ö
	m_eStatus = eTNSts_None;
	m_iIgnoreObstacle = 0; // Àå¾Ö¹°À» ¹«½ÃÇÏ°í °ø°ÝÇÏ±â ¼³Á¤(0:Àå¾Ö¹° °Ë»ç, 1:Àå¾Ö¹° ¹«½Ã)
	if( eTNMob_NPC == m_eMobType )
	{
		m_iBlockedCell = pMonsterData[MOB.nTP].Equip[eMonPrty_BlockedCell].snIndex;
		m_iBlockedCell = m_iBlockedCell | eTNCell_DontAttackMonster; // monster¸¦ °ø°ÝÇÏÁö ¸øÇÏ´Â °÷Àº µé¾î°¡Áö ¾Ê´Â´Ù.
	}
}


//user°¡ Á¾·á¸¦ ÇÒ¶§, ±âÁ¸¿¡ ÇÏ´ø ÀÏµéÀº clear½ÃÄÑÁØ´Ù.
void CMob::ClearActivity()
{
	RemoveMobSummonedAll();
	//KillFamiliar();
	//KillRetainer();

#ifdef __TN_PLAYMOVIE__
	if( !(eTNAIO_Follow & m_iAIOption) ) return;

	for( int i = 0; i < eRobot_MaxCount; ++i )
	{
		int iMob = m_irgRobot[i];
		if( 0 >= iMob ) continue;
		if( MOB_EMPTY == pMob[iMob].Mode ) continue;

		DeleteMob(iMob,645, 0, eTNPrdt_RemoveNormal, 40 );
		pMob[iMob].Mode = MOB_EMPTY;
	}
#endif


	if( 0 < m_iLinker )	m_iLinker = 0;

	if( m_bIsInArenaEntry ) // ¾Æ·¹³ª ÀÌº¥Æ®¿¡ Âü°¡ÁßÀÌ¶ó¸é
	{
		g_kArena.RemoveEntrant( m_iHandle );
	}
}


void CMob::ProcessContinuousEffect(bool bSet)
{
	time_t now; time(&now);
	DWORD dwTime=now;
	TNEFFECT kEffect;

	if(pUser[m_iHandle].m_snTimeMode & 0x8000)
	{	byMaxInven = MAX_ONEINVEN;														//	ÀÎº¥È®Àå ºñÀû¿ë¸ðµå
	}	else
	{	if(pUser[m_iHandle].m_time[eTime_Inven] > dwTime) byMaxInven = MAX_ONEINVEN*2;	//	ÀÎº¥È®Àå Àû¿ë¸ðµåÀÌ°í »ç¿ë±â°£ÀÏ¶§
	}

	if(pUser[m_iHandle].m_snTimeMode & 0x2000)
	{	m_bAMoneyRoot = false;															//	ÀÚµ¿µ·ÁÝ±â ºñÀû¿ë¸ðµå
	}	else
	{	if(pUser[m_iHandle].m_time[eTime_AMoneyRoot] > dwTime) m_bAMoneyRoot = true;	//	ÀÚµ¿µ·ÁÝ±â Àû¿ë¸ðµåÀÌ°í »ç¿ë±â°£ÀÏ¶§
	}

	if(pUser[m_iHandle].m_time[eTime_Anubaba]>dwTime)		//	±â°£Á¦ ¾Æ´©¹Ù¹ÙºÎÀû
	{	
		if(pUser[m_iHandle].m_snTimeMode & 0x1000)										
		{	if(bSet)
			{
				RemoveEffect(eTNAfn_DamagePlus);				//	¾Æ´©¹Ù¹Ù ºñÀû¿ë¸ðµå
				RemoveEffect(eTNAfn_ElementalDamagePlus);
				//RemoveEffect(eTNAfn_FireDamagePlus);
				//RemoveEffect(eTNAfn_ColdDamagePlus);
				//RemoveEffect(eTNAfn_LightningDamagePlus);
			}
		}	else											//	¾Æ´©¹Ù¹Ù Àû¿ë¸ðµåÀÌ°í »ç¿ë±â°£ÀÏ¶§
		{	kEffect.iID = eTNAfn_DamagePlus;				// ¹°¸® °ø°Ý·Â up
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 1;
			kEffect.iParam1 = 30;
			kEffect.iParam2 = 30;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_ElementalDamagePlus;		
			kEffect.iDuration = 36000000;
			kEffect.kFunc.iData = 1;
			kEffect.iParam1 = 12;
			kEffect.iParam2 = 12;
			AddEffect( kEffect, m_iHandle, m_iHandle );

/*			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_FireDamagePlus;			// ¼Ó¼º °ø°Ý·Â up(ºÒ)
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 1;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 15;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_ColdDamagePlus;			// ¼Ó¼º °ø°Ý·Â up(¾óÀ½)
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 1;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 15;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_LightningDamagePlus;		// ¼Ó¼º °ø°Ý·Â up(¶óÀÌÆ®´×)
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 1;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 15;
			AddEffect( kEffect, m_iHandle, m_iHandle );*/

		}
	}

	if(pUser[m_iHandle].m_time[eTime_Atman]>dwTime)			//	±â°£Á¦ ¾ÆÆ®¸¸ºÎÀû
	{	if(pUser[m_iHandle].m_snTimeMode & 0x0800)								
		{	if(bSet)
			{		RemoveEffect(eTNAfn_MaxHPPPlus);				//	¾ÆÆ®¸¸ ºñÀû¿ë¸ðµå
					RemoveEffect(eTNAfn_MaxHPPlus);
			}
		}	else											//	¾ÆÆ®¸¸ Àû¿ë¸ðµåÀÌ°í »ç¿ë±â°£ÀÏ¶§
		{	ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_MaxHPPPlus;				// HP¿Ã¸®´Â°Í
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 27;
			kEffect.iParam2 = 0; 
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_MaxHPPlus;				// HP¿Ã¸®´Â°Í
			kEffect.iDuration = 36000000;					// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 270;
			kEffect.iParam2 = 0; 
			AddEffect( kEffect, m_iHandle, m_iHandle );
		}
	}

	if(pUser[m_iHandle].m_time[eTime_15Chakra]>dwTime)	//	±â°£Á¦ 15Â÷Å©¶ó¾÷ºÎÀû
	{	if(pUser[m_iHandle].m_snTimeMode & 0x0400)								
		{	if(bSet)
			{	RemoveEffect(eTNAfn_MusclePlus2);			//	±â°£Á¦ 15Â÷Å©¶ó¾÷ ºñÀû¿ë¸ðµå
				RemoveEffect(eTNAfn_NervesPlus2);
				RemoveEffect(eTNAfn_HeartPlus2);
				RemoveEffect(eTNAfn_MindPlus2);
			}
		}	else										//	±â°£Á¦ 15Â÷Å©¶ó¾÷ Àû¿ë¸ðµå
		{	kEffect.iID = eTNAfn_MusclePlus2;			// ±ÙÀ° Â÷Å©¶ó up
			kEffect.iDuration = 36000000;				// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 0;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_NervesPlus2;			// ½Å°æ Â÷Å©¶ó up
			kEffect.iDuration = 36000000;				// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 0;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_HeartPlus2;			// ½ÉÀå Â÷Å©¶ó up
			kEffect.iDuration = 36000000;				// 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 0;
			AddEffect( kEffect, m_iHandle, m_iHandle );

			ZeroMemory(&kEffect, sizeof(kEffect));
			kEffect.iID = eTNAfn_MindPlus2;			// Á¤½Å Â÷Å©¶ó up
			kEffect.iDuration = 36000000;              // 10½Ã°£ Áö¼Ó, ÇÏÁö¸¸ 32ÃÊ¸¶´Ù °è¼Ó °»½ÅÀ» ÇÏ±â ¶§¹®¿¡ ¹«ÇÑÈ÷ °É·Á ÀÖÀ» °ÍÀÌ´Ù.
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = 15;
			kEffect.iParam2 = 0;
			AddEffect( kEffect, m_iHandle, m_iHandle );
		}
	}

	NotifyUpdateUIMsg();
}


bool CMob::IsMyAlly( int a_iGuildID )
{
	int iMyGuildID = GetGuild( MOB.nGuildID );
	int iOtherGuildID = GetGuild( a_iGuildID );
	if( 0 == strncmp( pGuild[iMyGuildID].GUILD.AlliedGuildName1, pGuild[iOtherGuildID].GUILD.GuildName, SZGUILD_LENGTH ) ) return true;

	return false;
}



int CMob::MoveZone( int a_iZone, int a_iX, int a_iY )
{	
	if( MAX_USER <= m_iHandle || 0 >= m_iHandle ) return eTNRes_Failed;
	//¾Æ´©¸¶À», 132,510

	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;
	sm.byZone = a_iZone;
	sm.snX = (short)a_iX;
	sm.snZ = (short)a_iY;
	m_kWaitAction.iAction = eWaitAct_ZonePortal;
	pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 

	if((ServerIndex+1) != a_iZone)
	{
		pUser[m_iHandle].m_byCloseType = eCloseSystem;
		pUser[m_iHandle].m_byCloseAndGoZone = a_iZone;
		pUser[m_iHandle].m_snGoX = (short)a_iX;
		pUser[m_iHandle].m_snGoY = (short)a_iY;
	}

/* portal ÀÌµ¿Àº 100% È®½ÇÇÏ°Ô ¼öÇàµÇ´Â °ÍÀÌ ¾Æ´Ï¶ó°í ÇÑ´Ù.
	//if( eZone_Mandra > a_iZone || eZone_Castle < a_iZone ) return eTNRes_Failed;
	S_SCP_RESP_MOVE_PORTAL sm;
	ZeroMemory( &sm, sizeof(sm) );
	sm.wType = SCP_RESP_MOVE_PORTAL;
	sm.byResult = REPLY_MOVE_PORTAL_OUTAREA; 
	sm.byZone = (BYTE)a_iZone;
	sm.nMoney = MOB.nRupiah;
	pUser[m_iHandle].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );

\\Event\\\\Event\\\\Event\\\\Event\\	MOB.byZone = (BYTE)a_iZone;
	MOB.snX = (short)a_iX;
	MOB.snZ = (short)a_iY;
	m_kWaitAction.iAction = eWaitAct_ZonePortal;					//	ÀÌµ¿ºÒ°¡ && Á¢¼ÓÁ¾·á½Ã µô·¹ÀÌ ¾øÀ½
*/
	return eTNRes_Succeeded;
}

int CMob::MoveZoneByNPC( int iNPCID )
{	
	if( 0 >= iNPCID ) return eTNRes_Failed;
	BYTE byZone = 0;
	bool bRet = g_ParamMgr.HT_bGetNPCZone( iNPCID, &byZone );
	if(!bRet) return eTNRes_Failed;

	MSG_MoveOtherZone sm; sm.wType=_MSG_MoveOtherZone;
	sm.byType=CONNECT_TYPE_PUSTICA; sm.snPositionID=iNPCID;
	m_kWaitAction.iAction = eWaitAct_ZonePortal;
	pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	return eTNRes_Succeeded;
}

// ¼ÒÈ¯¼ö°¡ master¿ÍÀÇ ¿¬°áÀ» ²÷´Â´Ù. ´Ü¼øÈ÷ ¿¬°á¸¸ ²÷´Â´Ù.
void CMob::ReleaseLinkWithMaster()
{
	if( 0 >= Leader || MAX_MOB <= Leader ) return;
	if( eTNCls2_Basic > MOB.byClass2 || eTNCls2_Mine < MOB.byClass2 ) MOB.byClass2 = eTNCls2_Basic;
	pMob[Leader].m_irgSummoned[MOB.byClass2] = 0;	
	Leader = 0;
}


// master°¡ ¼ÒÈ¯ÇÑ ¸ðµç monsterµéÀ» remove
void CMob::RemoveMobSummonedAll()
{
	KillMobSummoned( eTNCls2_Familiar );
	KillMobSummoned( eTNCls2_Retainer );
}


void CMob::KillMobSummoned( int a_iType )
{
	if( eTNCls2_Basic > a_iType || eTNCls2_Mine < a_iType ) return;
	int iMob = m_irgSummoned[a_iType];
	if( MAX_USER <= iMob && MAX_MOB > iMob )
	{// familiar°¡ ÀÖ´Ù¸é Á×ÀÎ´Ù.
		m_irgSummoned[a_iType] = 0;
		if( m_iHandle != pMob[iMob].Leader ) return;
		DeleteMob( iMob, 21, m_iHandle, eTNPrdt_RemoveBoom, 50 );
		//pMob[iMob].OnKilled( m_iHandle, 21 );// ÀÌ°ÍÀ» callÇÏ°Ô µÇ¸é recursive callÀÌ µÈ´Ù.
	}
}


int CMob::CheckDistanceFromMaster( int a_iEffectiveDistance, int a_iClass2 )
{
	if( 0 >= Leader || MAX_MOB <= Leader ) return eTNRes_HaveNoMaster;
	int iDist = CalDistance( m_iHandle, Leader );
	if( a_iEffectiveDistance < iDist )
	{
		pMob[Leader].KillMobSummoned( a_iClass2 );
		//DeleteMob( m_iHandle, 1, m_iHandle, eTNPrdt_RemoveBoom, 310 );
		//OnKilled( Leader, 23 );
		return eTNRes_Failed;
	}

	return eTNRes_Succeeded;
}


void CMob::CallRetainer()
{
	int iMob = m_irgSummoned[eTNCls2_Retainer];
	if( MAX_USER > iMob || MAX_MOB <= iMob ) return;
	if( pMob[iMob].IsDead() ) return;
	if( pMob[iMob].IsCombat() ) return;
	if( pMob[iMob].m_iBlockedCell & g_krgCell[TargetY][TargetX].usProperty )
	{// retainer´Â eTNCell_SafetyZone, eTNCell_Blocked, eTNCell_MonsterCantMoveInThisCell, eTNCell_SealedZone À¸·Î µé¾î°¥ ¼ö ¾ø´Ù.
		KillMobSummoned( eTNCls2_Retainer );
		//KillRetainer();
		return;
	}

	if( pMob[iMob].CheckDistanceFromMaster( eRetainer_DistanceFromMaster, eTNCls2_Retainer ) ) return;

	pMob[iMob].OnFollow( m_iHandle );
}


//@Param
//	a_iMob : µû¶ó°¡¾ßÇÒ target
void CMob::OnFollow( int a_iMob )
{
	if( 0 >= a_iMob || MAX_MOB <= a_iMob ) return;

	GetTargetPos( a_iMob );
	if( NextX==TargetX && NextY==TargetY ) return;
	if( m_iBlockedCell & g_krgCell[NextY][NextX].usProperty ) return;

	MSG_Action sm; GetAction( m_iHandle, NextX, NextY, &sm );
	sm.Effect = 3; // run
	GridMulticast( m_iHandle, NextX, NextY, (MSG_STANDARD*)&sm, 30 );
}


