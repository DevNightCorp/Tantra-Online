#include "basedef.h"
#include "Server.h"
#include "HTServerSetting.h"
#include "TNRate.h"
#include "TNRate10000.h"
#include "TNDeck10000.h"
#include "TNDeck1000.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern TNITEM_DATA		pItemData[MAX_ITEM_DATA];
extern int              g_iZoneID ;
extern                  g_iWorldID; // 본섭은 1,2,3, 테섭은 0, 기준의 본섭이므로 default로 1을 설정
int						g_irgLevelUp[TN_MAX_LEVEL];
TNRate10000				g_krgRewardItemRate[MAX_MONSTER_DATA][eRwd_ItemCount];
TNCOEFFICIENT           g_krgCoefficientByClass[eCls_MaxLevel][eCls_MaxSpecialized];
short                   g_srgItemGroup[eRwd_ItemGroup][eRwd_ItemGroupCount];
short					g_srgGroupItemCount[eRwd_ItemGroup];
TNEFFECTTOLERANCE		g_krgEffectTolerance[eCls_MaxLevel][eCls_MaxSpecialized];
STRUCT_ITEM             g_krgItemByLevel[eItm_MaxCategory][eItm_MaxLevel];
TNDeck10000             g_krgItemRateByMonLevel[eMonster_MaxLevel]; // card : 1~11
TNDeck1000              g_kRateByItemCategory; // card : 0 ~n
short                   g_srgRateByItemLevel[eMonster_MaxLevel][eItm_MaxLevel];
short                   g_srgRateByItemCategory[eItm_MaxCategory];
TNCONSIDER              g_krgConsider[eCon_Sort][eCon_Sort];
TNJUDGE_COMBAT_VALUE    g_krgJudgeCombat[2][2];
int                     g_irgRvRPKConsider[eCaste_MaxLevel][eCaste_MaxLevel];
int                     g_irgRewardBP[eCaste_MaxLevel] = { 0,0,0, };
short					g_srgAttackTypeVSArmorTypeChart[eAAC_ArmorTypeCount][eAAC_AttackTypeCount]; // 0, 0은 사용하지 않는다. 1부터 시작한다.
TNSPEECH_CONTENT         g_krgSpeechContent[eTNSpch_MaxContentCount+1];
char                    g_szrgComment[eTNSpch_MaxCommentCount+1][101];
short g_srgAIList[eTNAI_MaxAICount+1][eTNAI_MaxEventSort+1];
TNACTION_LIST            g_krgActionList[eTNAI_MaxActionListCount+1];
TNACTION                g_krgAction[eTNAI_MaxActionCount+1];
TNSETITEM				g_krgSetItem[eSetItem_Size];
//int                     g_irgKalaAltar[eKalaAltar_MaxCount] = { 0, 0, 0, };
TNKALA_ALTAR_OLD            g_krgKalaAltar[eKalaAltar_MaxCount];
HS2D_COORD				g_krgKalaRewarderPosition[eKalaRewarder_MaxCount][5];
TNEVENT                 g_krgEventList[eEvent_MaxCount];
TNTASK                  g_krgTaskList[eTask_MaxCount];
short                   g_srgTimeSchedule[eTS_MaxSlot] = { 0,0,0, };  // 4초 tic,	900(60분*15(=60초를 4초로 나누면 15개 slice))
STGAMEEVENT				g_kGameEvent[MAX_EVENT];

CHTSSettingMgr* g_pkSettingMgr = NULL;




void LoadSettingTxl()
{
	if( NULL != g_pkSettingMgr ) delete g_pkSettingMgr;
	g_pkSettingMgr = new CHTSSettingMgr;
	if( NULL == g_pkSettingMgr )
	{
		assert( !"[ERROR] can't allocate memory for HTSSetting.txl" );
		exit(0);
	}

	if(!g_pkSettingMgr->HT_bLoad(CHTString("HTSSetting.txl")))
	{	
		assert( !"[ERROR] can't load HTSSetting.txl" );
		exit(0);
	}

	int iIndex = 0;
	int id = 0;
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;
	vectorIDLevel.resize( eTNSpch_MaxCommentCount+1 );


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iAIID, iRest, iMove, iStart, iArrive, iDetect, iHelp1, iLink1, iGuard1, iBeKilled1, iUnderAttack1, iAttack, iHit, iMiss, iBeHitted, iDodge, iTrace, iGiveUpToTrace, iKillEnemy, iHelp2, iLink2, iGuard2, iBeKilled2, iUnderAttack2, iCantTrace, iStopToAttack, iReturn, iFlee, iLead, iPop, iDialog1, iDialog2, iDialog3, iDialog4;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{		
			iRest = iMove = iStart = iArrive = iDetect = iHelp1 = iLink1 = iGuard1 = iBeKilled1 = iUnderAttack1 = iAttack = iHit = iMiss = iBeHitted = iDodge = iTrace = iGiveUpToTrace = iKillEnemy = iHelp2 = iLink2 = iGuard2 = iBeKilled2 = iUnderAttack2 = iCantTrace = iStopToAttack = iReturn = iFlee = iLead = iPop = iDialog1 = iDialog2 = iDialog3 = iDialog4 = 0;		
			id = vec_It->iID;	
			iAIID = id;

			g_pkSettingMgr->HT_bGetAIListRest( id, &iRest );
			g_pkSettingMgr->HT_bGetAIListMove( id, &iMove );
			g_pkSettingMgr->HT_bGetAIListStart( id, &iStart );
			g_pkSettingMgr->HT_bGetAIListArrive( id, &iArrive );
			g_pkSettingMgr->HT_bGetAIListDetect( id, &iDetect );
			g_pkSettingMgr->HT_bGetAIListHelp1( id, &iHelp1 );
			g_pkSettingMgr->HT_bGetAIListLink1( id, &iLink1 );
			g_pkSettingMgr->HT_bGetAIListGuard( id, &iGuard1 );
			g_pkSettingMgr->HT_bGetAIListBeKilled1( id, &iBeKilled1 );
			g_pkSettingMgr->HT_bGetAIListUnderAttack1( id, &iUnderAttack1 );
			g_pkSettingMgr->HT_bGetAIListAttack( id, &iAttack );
			g_pkSettingMgr->HT_bGetAIListHit( id, &iHit );
			g_pkSettingMgr->HT_bGetAIListMiss( id, &iMiss );
			g_pkSettingMgr->HT_bGetAIListBeHitted( id, &iBeHitted );
			g_pkSettingMgr->HT_bGetAIListDodge( id, &iDodge );
			g_pkSettingMgr->HT_bGetAIListTrace( id, &iTrace );
			g_pkSettingMgr->HT_bGetAIListGiveUpToTrace( id, &iGiveUpToTrace );
			g_pkSettingMgr->HT_bGetAIListKillEnemy( id, &iKillEnemy );
			g_pkSettingMgr->HT_bGetAIListHelp2( id, &iHelp2 );
			g_pkSettingMgr->HT_bGetAIListLink2( id, &iLink2 );
			g_pkSettingMgr->HT_bGetAIListGuard2( id, &iGuard2 );
			g_pkSettingMgr->HT_bGetAIListBeKilled2( id, &iBeKilled2 );
			g_pkSettingMgr->HT_bGetAIListUnderAttack2( id, &iUnderAttack2 );
			g_pkSettingMgr->HT_bGetAIListCantTrace( id, &iCantTrace );
			g_pkSettingMgr->HT_bGetAIListStopToAttack( id, &iStopToAttack );
			g_pkSettingMgr->HT_bGetAIListReturn( id, &iReturn );
			g_pkSettingMgr->HT_bGetAIListFlee( id, &iFlee );
			g_pkSettingMgr->HT_bGetAIListLead( id, &iLead );
			g_pkSettingMgr->HT_bGetAIListPop( id, &iPop );
			g_pkSettingMgr->HT_bGetAIListDialog1( id, &iDialog1 );
			g_pkSettingMgr->HT_bGetAIListDialog2( id, &iDialog2 );
			g_pkSettingMgr->HT_bGetAIListDialog3( id, &iDialog3 );
			g_pkSettingMgr->HT_bGetAIListDialog4( id, &iDialog4 );
			
			++vec_It;

			if( 0 < iAIID && eTNAI_MaxAICount > iAIID )
			{
				g_srgAIList[iAIID][eTNAI_Rest] = iRest;
				g_srgAIList[iAIID][eTNAI_Move] = iMove;
				g_srgAIList[iAIID][eTNAI_Start] = iStart;
				g_srgAIList[iAIID][eTNAI_Arrive] = iArrive;
				g_srgAIList[iAIID][eTNAI_Detect] = iDetect;
				g_srgAIList[iAIID][eTNAI_Help1] = iHelp1;
				g_srgAIList[iAIID][eTNAI_Link1] = iLink1;
				g_srgAIList[iAIID][eTNAI_Guard1] = iGuard1;
				g_srgAIList[iAIID][eTNAI_BeKilled1] = iBeKilled1;
				g_srgAIList[iAIID][eTNAI_UnderAttack1] = iUnderAttack1;
				g_srgAIList[iAIID][eTNAI_Attack] = iAttack;
				g_srgAIList[iAIID][eTNAI_HitEnemy] = iHit;
				g_srgAIList[iAIID][eTNAI_Miss] = iMiss;
				g_srgAIList[iAIID][eTNAI_BeHitted] = iBeHitted;
				g_srgAIList[iAIID][eTNAI_Dodge] = iDodge;
				g_srgAIList[iAIID][eTNAI_Trace] = iTrace;
				g_srgAIList[iAIID][eTNAI_GiveUpToTrace] = iGiveUpToTrace;
				g_srgAIList[iAIID][eTNAI_KillEnemy] = iKillEnemy;
				g_srgAIList[iAIID][eTNAI_Help2] = iHelp2;
				g_srgAIList[iAIID][eTNAI_Link2] = iLink2;
				g_srgAIList[iAIID][eTNAI_Guard2] = iGuard2;
				g_srgAIList[iAIID][eTNAI_BeKilled2] = iBeKilled2;
				g_srgAIList[iAIID][eTNAI_UnderAttack2] = iUnderAttack2;
				g_srgAIList[iAIID][eTNAI_CantTrace] = iCantTrace;
				g_srgAIList[iAIID][eTNAI_Return] = iReturn;
				g_srgAIList[iAIID][eTNAI_Flee] = iFlee;
				g_srgAIList[iAIID][eTNAI_Pop] = iPop;
				g_srgAIList[iAIID][eTNAI_Lead] = iLead;
				g_srgAIList[iAIID][eTNAI_Dialog1] = iDialog1;
				g_srgAIList[iAIID][eTNAI_Dialog2] = iDialog2;
				g_srgAIList[iAIID][eTNAI_Dialog3] = iDialog3;
				g_srgAIList[iAIID][eTNAI_Dialog4] = iDialog4;

				{
					char chBuf[512] = { 0,0,0, };

					sprintf(chBuf, "\t- AIID:%3d, Peace> Rest:%3d, Move:%3d, Start:%3d, Arrive:%3d, Detect:%3d, Help1:%3d, Link1:%3d, Guard1:%3d, BeKilled1:%3d, UnderAttack1:%3d, Dialog(%3d,%3d,%3d,%3d)\r\n\t\t Combat> Attack:%3d, Hit:%3d, Dodge:%3d, Trace:%3d, GiveUpToTrace:%3d, KillEnemy:%3d, Help2:%3d, Link2:%3d, Guard2:%3d, BeKilled2:%3d, UnderAttack2:%3d, CantTrace:%3d, Return:%3d, Flee:%3d, Pop:%3d \r\n"
						, iAIID, g_srgAIList[iAIID][eTNAI_Rest], g_srgAIList[iAIID][eTNAI_Move], g_srgAIList[iAIID][eTNAI_Start], g_srgAIList[iAIID][eTNAI_Arrive]
						, g_srgAIList[iAIID][eTNAI_Detect], g_srgAIList[iAIID][eTNAI_Help1], g_srgAIList[iAIID][eTNAI_Link1], g_srgAIList[iAIID][eTNAI_Guard1]
						, g_srgAIList[iAIID][eTNAI_BeKilled1], g_srgAIList[iAIID][eTNAI_UnderAttack1], g_srgAIList[iAIID][eTNAI_Attack], g_srgAIList[iAIID][eTNAI_HitEnemy]
						, g_srgAIList[iAIID][eTNAI_Miss], g_srgAIList[iAIID][eTNAI_BeHitted], g_srgAIList[iAIID][eTNAI_Dodge], g_srgAIList[iAIID][eTNAI_Trace]
						, g_srgAIList[iAIID][eTNAI_GiveUpToTrace], g_srgAIList[iAIID][eTNAI_KillEnemy], g_srgAIList[iAIID][eTNAI_Help2], g_srgAIList[iAIID][eTNAI_Link2]
						, g_srgAIList[iAIID][eTNAI_Guard2], g_srgAIList[iAIID][eTNAI_BeKilled2], g_srgAIList[iAIID][eTNAI_UnderAttack2], g_srgAIList[iAIID][eTNAI_CantTrace]
						, g_srgAIList[iAIID][eTNAI_Return], g_srgAIList[iAIID][eTNAI_Flee], g_srgAIList[iAIID][eTNAI_Pop], g_srgAIList[iAIID][eTNAI_Lead]
						, g_srgAIList[iAIID][eTNAI_Dialog1], g_srgAIList[iAIID][eTNAI_Dialog2], g_srgAIList[iAIID][eTNAI_Dialog3], g_srgAIList[iAIID][eTNAI_Dialog4]
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			} // if( 0 < iAIID && eTNAI_MaxAICount > iAIID )
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bActionListGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iALID, iAction1, iAction2, iAction3;		

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iAction1 = iAction2 = iAction3 = 0;		
			id = vec_It->iID;	
			iALID = id;

			g_pkSettingMgr->HT_bGetActionListAction1( id, &iAction1 );
			g_pkSettingMgr->HT_bGetActionListAction2( id, &iAction2 );
			g_pkSettingMgr->HT_bGetActionListAction3( id, &iAction3 );
			
			++vec_It;

			if( 0 < iALID && eTNAI_MaxActionListCount > iALID )
			{
				g_krgActionList[iALID].iCount = 0;
				g_krgActionList[iALID].srgAction[0] = iAction1;
				g_krgActionList[iALID].srgAction[1] = iAction2;
				g_krgActionList[iALID].srgAction[2] = iAction3;

				if( 0 < g_krgActionList[iALID].srgAction[0] ) ++g_krgActionList[iALID].iCount;
				if( 0 < g_krgActionList[iALID].srgAction[1] ) ++g_krgActionList[iALID].iCount;
				if( 0 < g_krgActionList[iALID].srgAction[2] ) ++g_krgActionList[iALID].iCount;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- iALID:%3d, \tCount:%3d, \tAction[0]:%3d, \tAction[1]:%3d, \tAction[2]:%3d \r\n"
						, iALID, g_krgActionList[iALID].iCount, g_krgActionList[iALID].srgAction[0], g_krgActionList[iALID].srgAction[1], g_krgActionList[iALID].srgAction[2] );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )




	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bActionGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iActionID, iSpeak, iGroup, iAction, iSkill, iState, iEvent;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iActionID = iSpeak = iGroup = iAction = iSkill = iState = iEvent = 0;
			id = vec_It->iID;	
			iActionID = id;

			g_pkSettingMgr->HT_bGetActionSpeak( id, &iSpeak );
			g_pkSettingMgr->HT_bGetActionGroup( id, &iGroup );
			g_pkSettingMgr->HT_bGetActionAction( id, &iAction );
			g_pkSettingMgr->HT_bGetActionSkill( id, &iSkill );
			g_pkSettingMgr->HT_bGetActionState( id, &iState );
			g_pkSettingMgr->HT_bGetActionEvent( id, &iEvent );

			++vec_It;

			if( 0 < iActionID && eTNAI_MaxActionCount > iActionID )
			{
				g_krgAction[iActionID].sSpeak = iSpeak;
				g_krgAction[iActionID].sGroup = iGroup;
				g_krgAction[iActionID].sAction = iAction;
				g_krgAction[iActionID].sSkill = iSkill;
				g_krgAction[iActionID].sState = iState;
				g_krgAction[iActionID].sEvent = iEvent;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- ActionID:%3d, \tSpeak:%3d, \tGroup:%3d, \tAction:%3d, \tSkill:%3d, \tState:%3d, \tEvent:%3d \r\n"
						, iActionID, g_krgAction[iActionID].sSpeak, g_krgAction[iActionID].sGroup, g_krgAction[iActionID].sAction, g_krgAction[iActionID].sSkill, g_krgAction[iActionID].sState, g_krgAction[iActionID].sEvent
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )




	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bSpeechContentGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iSCID, iComment1, iComment2, iComment3, iComment4, iComment5, iType1, iType2, iType3, iType4, iType5;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iSCID = iComment1 = iComment2 = iComment3 = iComment4 = iComment5 = iType1 = iType2 = iType3 = iType4 = iType5 = 0;
			
			id = vec_It->iID;	
			iSCID = id;

			g_pkSettingMgr->HT_bGetSpeechContentComment1( id, &iComment1 );
			g_pkSettingMgr->HT_bGetSpeechContentComment2( id, &iComment2 );
			g_pkSettingMgr->HT_bGetSpeechContentComment3( id, &iComment3 );
			g_pkSettingMgr->HT_bGetSpeechContentComment4( id, &iComment4 );
			g_pkSettingMgr->HT_bGetSpeechContentComment5( id, &iComment5 );
			g_pkSettingMgr->HT_bGetSpeechContentType1( id, &iType1 );
			g_pkSettingMgr->HT_bGetSpeechContentType2( id, &iType2 );
			g_pkSettingMgr->HT_bGetSpeechContentType3( id, &iType3 );
			g_pkSettingMgr->HT_bGetSpeechContentType4( id, &iType4 );
			g_pkSettingMgr->HT_bGetSpeechContentType5( id, &iType5 );

			++vec_It;

			if( 0 < iSCID && eTNSpch_MaxContentCount > iSCID )
			{
				g_krgSpeechContent[iSCID].srgComment[0] = iComment1;
				g_krgSpeechContent[iSCID].srgComment[1] = iComment2;
				g_krgSpeechContent[iSCID].srgComment[2] = iComment3;
				g_krgSpeechContent[iSCID].srgComment[3] = iComment4;
				g_krgSpeechContent[iSCID].srgComment[4] = iComment5;
				g_krgSpeechContent[iSCID].srgType[0] = iType1;
				g_krgSpeechContent[iSCID].srgType[1] = iType2;
				g_krgSpeechContent[iSCID].srgType[2] = iType3;
				g_krgSpeechContent[iSCID].srgType[3] = iType4;
				g_krgSpeechContent[iSCID].srgType[4] = iType5;


				if( 0 < g_krgSpeechContent[iSCID].srgComment[0] ) ++g_krgSpeechContent[iSCID].iCount;
				if( 0 < g_krgSpeechContent[iSCID].srgComment[1] ) ++g_krgSpeechContent[iSCID].iCount;
				if( 0 < g_krgSpeechContent[iSCID].srgComment[2] ) ++g_krgSpeechContent[iSCID].iCount;
				if( 0 < g_krgSpeechContent[iSCID].srgComment[3] ) ++g_krgSpeechContent[iSCID].iCount;
				if( 0 < g_krgSpeechContent[iSCID].srgComment[4] ) ++g_krgSpeechContent[iSCID].iCount;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- iSCID:%3d, \tComment(%3d,%3d,%3d,%3d,%3d), \tType(%3d,%3d,%3d,%3d,%3d), \tCount(총개수):%d \r\n"
						, iSCID
						, g_krgSpeechContent[iSCID].srgComment[0], g_krgSpeechContent[iSCID].srgComment[1], g_krgSpeechContent[iSCID].srgComment[2], g_krgSpeechContent[iSCID].srgComment[3], g_krgSpeechContent[iSCID].srgComment[4]
						, g_krgSpeechContent[iSCID].srgType[0], g_krgSpeechContent[iSCID].srgType[1], g_krgSpeechContent[iSCID].srgType[2], g_krgSpeechContent[iSCID].srgType[3], g_krgSpeechContent[iSCID].srgType[4]
						, g_krgSpeechContent[iSCID].iCount );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )




	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bSpeechCommentGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iCmmID = 0;
		char szComment[101] = { 0,0,0, };

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			memset( szComment, 0, sizeof(szComment) );
			id = vec_It->iID;	
			iCmmID = id;

			g_pkSettingMgr->HT_bGetSpeechCommentComment( id, szComment );

			++vec_It;

			if( 0 < iCmmID && eTNSpch_MaxCommentCount > iCmmID )
			{
				memcpy( g_szrgComment[iCmmID], szComment, sizeof(szComment) );

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- iCmmID:%d, szComment:%s \r\n", iCmmID, g_szrgComment[iCmmID] );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bLevelUpGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iLevel = 0, iPrana = 0 ;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;	
			iLevel = id;
			if( TN_MAX_LEVEL < iLevel ) break;

			g_pkSettingMgr->HT_bGetLevelUpPrana( id, &iPrana );

			++vec_It;

			g_irgLevelUp[iLevel-1] = iPrana;

			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\t- level:%3d, prana:%d\r\n", iLevel, g_irgLevelUp[iLevel-1] );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bAttackTypeVSArmorTypeGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iArmorType, iDagger, iSword, iTwoHandSword, iAxe, iTwoHandAxe, iSpear, iBow, iClaw, iBlunt, iMagic, iAnimal, iDemon, iGolem, iUndead, iPlant, iInsect, iHumanoid1, iHumanoid2, iHumanoid3, iHumanoid4;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iArmorType = iDagger = iSword = iTwoHandSword = iAxe = iTwoHandAxe = iSpear = iBow = iClaw = iBlunt = iMagic = iAnimal = iDemon = iGolem = iUndead = iPlant = iInsect = iHumanoid1 = iHumanoid2 = iHumanoid3 = iHumanoid4 = iMagic = 0;
			id = vec_It->iID;	
			iArmorType = id;

			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeDagger( id, &iDagger );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeSword( id, &iSword );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeTwoHandSword( id, &iTwoHandSword );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeAxe( id, &iAxe );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeTwoHandAxe( id, &iTwoHandAxe );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeSpear( id, &iSpear );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeBow( id, &iBow );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeClaw( id, &iClaw );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeBlunt( id, &iBlunt );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeMagic( id, &iMagic );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeAnimal( id, &iAnimal );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeDemon( id, &iDemon );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeGolem( id, &iGolem );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeUndead( id, &iUndead );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypePlant( id, &iPlant );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeInsect( id, &iInsect );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeHumanoid1( id, &iHumanoid1 );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeHumanoid2( id, &iHumanoid2 );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeHumanoid3( id, &iHumanoid3 );
			g_pkSettingMgr->HT_bGetAttackTypeVSArmorTypeHumanoid4( id, &iHumanoid4 );

			++vec_It;

			if( eAAC_ArmorTypeCount > iArmorType && 0 < iArmorType )
			{
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Dagger] = iDagger;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Sword] = iSword;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandSword] = iTwoHandSword;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Animal] = iAnimal;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Demon] = iDemon;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Golem] = iGolem;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Undead] = iUndead;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Plant] = iPlant;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Insect] = iInsect;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid1] = iHumanoid1;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid2] = iHumanoid2;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid3] = iHumanoid3;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Humanoid4] = iHumanoid4;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Axe] = iAxe;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_TwoHandAxe] = iTwoHandAxe;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Spear] = iSpear;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Bow] = iBow;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Claw] = iClaw;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Blunt] = iBlunt;
				g_srgAttackTypeVSArmorTypeChart[iArmorType][eTNAttackType_Magic] = iMagic;
			}

			{
				char chBuf[512] = { 0,0,0, };
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
					);		
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Dagger] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Sword] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_TwoHandSword] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Animal] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Demon] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Golem] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Undead] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Plant] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Insect] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid1] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid2] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid3] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Humanoid4] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Axe] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_TwoHandAxe] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Spear] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Bow] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Claw] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Blunt] = 100;
	g_srgAttackTypeVSArmorTypeChart[0][eTNAttackType_Magic] = 100;



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bCoefficientByClassGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iClass1, iClass2, iDagger, iSword, iTwoHandSword, iAxe, iTwoHandAxe, iBlunt, iSpear, iStaff, iClaw, iBow, iThrowing, iBare, iShield, iHP, iTP, iRecvry, iAC, iResist, iAttackRate, iDodgeRate, iAttackSpeed, iCastSpeed, iDodgeSpeed;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iClass1 = iClass2 = iDagger = iSword = iTwoHandSword = iAxe = iTwoHandAxe = iBlunt = iSpear = iStaff = iClaw = iBow = iThrowing = iBare = iShield = iHP = iTP = iRecvry = iAC = iResist = iAttackRate = iDodgeRate = iAttackSpeed = iCastSpeed = iDodgeSpeed = 0;
			id = vec_It->iID;	

			g_pkSettingMgr->HT_bGetCoefficientByClassClass1( id, &iClass1 );
			g_pkSettingMgr->HT_bGetCoefficientByClassClass2( id, &iClass2 );
			g_pkSettingMgr->HT_bGetCoefficientByClassDagger( id, &iDagger );
			g_pkSettingMgr->HT_bGetCoefficientByClassSword( id, &iSword ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassTwoHandSword( id, &iTwoHandSword );
			g_pkSettingMgr->HT_bGetCoefficientByClassAxe( id, &iAxe ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassTwoHandAxe( id, &iTwoHandAxe );
			g_pkSettingMgr->HT_bGetCoefficientByClassBlunt( id, &iBlunt );  
			g_pkSettingMgr->HT_bGetCoefficientByClassSpear( id, &iSpear );  
			g_pkSettingMgr->HT_bGetCoefficientByClassStaff( id, &iStaff );  
			g_pkSettingMgr->HT_bGetCoefficientByClassClaw( id, &iClaw );
			g_pkSettingMgr->HT_bGetCoefficientByClassBow( id, &iBow ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassThrowing( id, &iThrowing );
			g_pkSettingMgr->HT_bGetCoefficientByClassBare( id, &iBare );   
			g_pkSettingMgr->HT_bGetCoefficientByClassShield( id, &iShield ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassHP( id, &iHP );  
			g_pkSettingMgr->HT_bGetCoefficientByClassTP( id, &iTP );  
			g_pkSettingMgr->HT_bGetCoefficientByClassRecvry( id, &iRecvry );
			g_pkSettingMgr->HT_bGetCoefficientByClassAC( id, &iAC );  
			g_pkSettingMgr->HT_bGetCoefficientByClassResist( id, &iResist ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassAttackRate( id, &iAttackRate ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassDodgeRate( id, &iDodgeRate ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassAttackSpeed( id, &iAttackSpeed );
			g_pkSettingMgr->HT_bGetCoefficientByClassCastSpeed( id, &iCastSpeed ); 
			g_pkSettingMgr->HT_bGetCoefficientByClassDodgeSpeed( id, &iDodgeSpeed );

			++vec_It;

			g_krgCoefficientByClass[iClass1][iClass2].iDagger = iDagger;
			g_krgCoefficientByClass[iClass1][iClass2].iSword = iSword;
			g_krgCoefficientByClass[iClass1][iClass2].iTwoHandSword = iTwoHandSword;
			g_krgCoefficientByClass[iClass1][iClass2].iAxe = iAxe;
			g_krgCoefficientByClass[iClass1][iClass2].iTwoHandAxe = iTwoHandAxe;
			g_krgCoefficientByClass[iClass1][iClass2].iBlunt = iBlunt;
			g_krgCoefficientByClass[iClass1][iClass2].iSpear = iSpear;
			g_krgCoefficientByClass[iClass1][iClass2].iStaff = iStaff;
			g_krgCoefficientByClass[iClass1][iClass2].iClaw = iClaw;
			g_krgCoefficientByClass[iClass1][iClass2].iBow = iBow;
			g_krgCoefficientByClass[iClass1][iClass2].iThrowing = iThrowing;
			g_krgCoefficientByClass[iClass1][iClass2].iBare = iBare;
			g_krgCoefficientByClass[iClass1][iClass2].iHP = iHP;
			g_krgCoefficientByClass[iClass1][iClass2].iTP = iTP;
			g_krgCoefficientByClass[iClass1][iClass2].iRecvry = iRecvry;
			g_krgCoefficientByClass[iClass1][iClass2].iAC = iAC;
			g_krgCoefficientByClass[iClass1][iClass2].iResist = iResist;
			g_krgCoefficientByClass[iClass1][iClass2].iAttackRate = iAttackRate;
			g_krgCoefficientByClass[iClass1][iClass2].iDodgeRate = iDodgeRate;
			g_krgCoefficientByClass[iClass1][iClass2].iAttackSpeed = iAttackSpeed;
			g_krgCoefficientByClass[iClass1][iClass2].iCastSpeed = iCastSpeed;
			g_krgCoefficientByClass[iClass1][iClass2].iDodgeSpeed = iDodgeSpeed;
			g_krgCoefficientByClass[iClass1][iClass2].iShield = iShield;
			
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- iClassLvl:%d, iSpcClass:%d, Dagger:%2d, Sword:%2d, TwoHandSword:%2d, Axe:%2d, TwoHandAxe:%2d, Blunt:%2d, Spear:%2d, Staff:%2d, Claw:%2d, Bow:%2d, Throwing:%2d, Bare:%2d, Shield:%2d, HP:%2d, TP1:%2d, TP2:%2d, AC:%2d, Resist:%2d, AR:%2d, DR:%2d, AtkSpd:%2d, CstSpd:%2d, DgSpd:%2d \r\n"
					, iClass1, iClass2
					, g_krgCoefficientByClass[iClass1][iClass2].iDagger, g_krgCoefficientByClass[iClass1][iClass2].iSword, g_krgCoefficientByClass[iClass1][iClass2].iTwoHandSword, g_krgCoefficientByClass[iClass1][iClass2].iAxe, g_krgCoefficientByClass[iClass1][iClass2].iTwoHandAxe, g_krgCoefficientByClass[iClass1][iClass2].iBlunt, g_krgCoefficientByClass[iClass1][iClass2].iSpear, g_krgCoefficientByClass[iClass1][iClass2].iStaff, g_krgCoefficientByClass[iClass1][iClass2].iClaw, g_krgCoefficientByClass[iClass1][iClass2].iBow, g_krgCoefficientByClass[iClass1][iClass2].iThrowing, g_krgCoefficientByClass[iClass1][iClass2].iBare, g_krgCoefficientByClass[iClass1][iClass2].iShield
					, g_krgCoefficientByClass[iClass1][iClass2].iHP, g_krgCoefficientByClass[iClass1][iClass2].iTP, g_krgCoefficientByClass[iClass1][iClass2].iRecvry, g_krgCoefficientByClass[iClass1][iClass2].iAC, g_krgCoefficientByClass[iClass1][iClass2].iResist, g_krgCoefficientByClass[iClass1][iClass2].iAttackRate, g_krgCoefficientByClass[iClass1][iClass2].iDodgeRate, g_krgCoefficientByClass[iClass1][iClass2].iAttackSpeed, g_krgCoefficientByClass[iClass1][iClass2].iCastSpeed , g_krgCoefficientByClass[iClass1][iClass2].iDodgeSpeed
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )




	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bJudgeCombatGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int irgCard[12] = { 0,0,0, };
		int iID = 0;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			memset( irgCard, 0, sizeof(irgCard) );

			id = vec_It->iID;
			iID = id;

			g_pkSettingMgr->HT_bGetJudgeCombatCriticalPCvsPC( id, &irgCard[0] );
			g_pkSettingMgr->HT_bGetJudgeCombatNormalPCvsPC( id, &irgCard[1] );
			g_pkSettingMgr->HT_bGetJudgeCombatMissPCvsPC( id, &irgCard[2] );
			g_pkSettingMgr->HT_bGetJudgeCombatCriticalPCvsNPC( id, &irgCard[3] ); 
			g_pkSettingMgr->HT_bGetJudgeCombatNormalPCvsNPC( id, &irgCard[4] );
			g_pkSettingMgr->HT_bGetJudgeCombatMissPCvsNPC( id, &irgCard[5] ); 
			g_pkSettingMgr->HT_bGetJudgeCombatCriticalNPCvsPC( id, &irgCard[6] );
			g_pkSettingMgr->HT_bGetJudgeCombatNormalNPCvsPC( id, &irgCard[7] );  
			g_pkSettingMgr->HT_bGetJudgeCombatMissNPCvsPC( id, &irgCard[8] );  
			g_pkSettingMgr->HT_bGetJudgeCombatCriticalNPCvsNPC( id, &irgCard[9] );  
			g_pkSettingMgr->HT_bGetJudgeCombatNormalNPCvsNPC( id, &irgCard[10] );
			g_pkSettingMgr->HT_bGetJudgeCombatMissNPCvsNPC( id, &irgCard[11] ); 

			++vec_It;

			if( 0 <= iID && eCon_JudgeCombat > iID )
			{
				g_krgJudgeCombat[0][0].irgJudgeCombat[iID][0] = irgCard[0];
				g_krgJudgeCombat[0][0].irgJudgeCombat[iID][1] = irgCard[1];
				g_krgJudgeCombat[0][0].irgJudgeCombat[iID][2] = irgCard[2];

				g_krgJudgeCombat[0][1].irgJudgeCombat[iID][0] = irgCard[3];
				g_krgJudgeCombat[0][1].irgJudgeCombat[iID][1] = irgCard[4];
				g_krgJudgeCombat[0][1].irgJudgeCombat[iID][2] = irgCard[5];

				g_krgJudgeCombat[1][0].irgJudgeCombat[iID][0] = irgCard[6];
				g_krgJudgeCombat[1][0].irgJudgeCombat[iID][1] = irgCard[7];
				g_krgJudgeCombat[1][0].irgJudgeCombat[iID][2] = irgCard[8];

				g_krgJudgeCombat[1][1].irgJudgeCombat[iID][0] = irgCard[9];
				g_krgJudgeCombat[1][1].irgJudgeCombat[iID][1] = irgCard[10];
				g_krgJudgeCombat[1][1].irgJudgeCombat[iID][2] = irgCard[11];

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t[Card] iID:%d \t%2d %2d %2d \t%2d %2d %2d \t%2d %2d %2d \t%2d %2d %2d \r\n"
						, iID
						, g_krgJudgeCombat[0][0].irgJudgeCombat[iID][0], g_krgJudgeCombat[0][0].irgJudgeCombat[iID][1], g_krgJudgeCombat[0][0].irgJudgeCombat[iID][2]
						, g_krgJudgeCombat[0][1].irgJudgeCombat[iID][0], g_krgJudgeCombat[0][1].irgJudgeCombat[iID][1], g_krgJudgeCombat[0][1].irgJudgeCombat[iID][2]
						, g_krgJudgeCombat[1][0].irgJudgeCombat[iID][0], g_krgJudgeCombat[1][0].irgJudgeCombat[iID][1], g_krgJudgeCombat[1][0].irgJudgeCombat[iID][2]
						, g_krgJudgeCombat[1][1].irgJudgeCombat[iID][0], g_krgJudgeCombat[1][1].irgJudgeCombat[iID][1], g_krgJudgeCombat[1][1].irgJudgeCombat[iID][2]
					);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bConsiderGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int irgCard[12] = { 0,0,0, };
		int iLevel = 0;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			memset( irgCard, 0, sizeof(irgCard) );

			id = vec_It->iID;
			iLevel = id;

			g_pkSettingMgr->HT_bGetConsiderDFPCvsPC( id, &irgCard[0] );
			g_pkSettingMgr->HT_bGetConsiderRSPCvsPC( id, &irgCard[1] );
			g_pkSettingMgr->HT_bGetConsiderDGPCvsPC( id, &irgCard[2] );
			g_pkSettingMgr->HT_bGetConsiderDFPCvsNPC( id, &irgCard[3] ); 
			g_pkSettingMgr->HT_bGetConsiderRSPCvsNPC( id, &irgCard[4] );
			g_pkSettingMgr->HT_bGetConsiderDGPCvsNPC( id, &irgCard[5] ); 
			g_pkSettingMgr->HT_bGetConsiderDFNPCvsPC( id, &irgCard[6] );
			g_pkSettingMgr->HT_bGetConsiderRSNPCvsPC( id, &irgCard[7] );  
			g_pkSettingMgr->HT_bGetConsiderDGNPCvsPC( id, &irgCard[8] );  
			g_pkSettingMgr->HT_bGetConsiderDFNPCvsNPC( id, &irgCard[9] );  
			g_pkSettingMgr->HT_bGetConsiderRSNPCvsNPC( id, &irgCard[10] );
			g_pkSettingMgr->HT_bGetConsiderDGNPCvsNPC( id, &irgCard[11] ); 

			++vec_It;

			if( 0 <= iLevel && eCon_MaxGapCount > iLevel )
			{
				g_krgConsider[0][0].irgVal[iLevel][eCon_DF] = irgCard[0];
				g_krgConsider[0][0].irgVal[iLevel][eCon_RS] = irgCard[1];
				g_krgConsider[0][0].irgVal[iLevel][eCon_DG] = irgCard[2];
				g_krgConsider[0][1].irgVal[iLevel][eCon_DF] = irgCard[3];
				g_krgConsider[0][1].irgVal[iLevel][eCon_RS] = irgCard[4];
				g_krgConsider[0][1].irgVal[iLevel][eCon_DG] = irgCard[5];
				g_krgConsider[1][0].irgVal[iLevel][eCon_DF] = irgCard[6];
				g_krgConsider[1][0].irgVal[iLevel][eCon_RS] = irgCard[7];
				g_krgConsider[1][0].irgVal[iLevel][eCon_DG] = irgCard[8];
				g_krgConsider[1][1].irgVal[iLevel][eCon_DF] = irgCard[9];
				g_krgConsider[1][1].irgVal[iLevel][eCon_RS] = irgCard[10];
				g_krgConsider[1][1].irgVal[iLevel][eCon_DG] = irgCard[11];

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t[Consider] iLevel:%d  \tPCvsPC(DF:%d  \tRS:%d  \tDG:%d) \tPCvsNPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsNPC(DF:%d \tRS:%d \tDG:%d) \r\n", iLevel
						, g_krgConsider[0][0].irgVal[iLevel][0], g_krgConsider[0][0].irgVal[iLevel][1], g_krgConsider[0][0].irgVal[iLevel][2]
						, g_krgConsider[0][1].irgVal[iLevel][0], g_krgConsider[0][1].irgVal[iLevel][1], g_krgConsider[0][1].irgVal[iLevel][2]
						, g_krgConsider[1][0].irgVal[iLevel][0], g_krgConsider[1][0].irgVal[iLevel][1], g_krgConsider[1][0].irgVal[iLevel][2]
						, g_krgConsider[1][1].irgVal[iLevel][0], g_krgConsider[1][1].irgVal[iLevel][1], g_krgConsider[1][1].irgVal[iLevel][2]
							);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	int iConstant = 39;
	for( int iLevel = 0; iLevel < eCon_MaxGapCount; ++iLevel )
	{
		g_krgConsider[0][0].irgVal[iLevel][0] = 0; // g_krgConsider[0][1].irgVal[iLevel][0] = g_krgConsider[1][0].irgVal[iLevel][0] = g_krgConsider[1][1].irgVal[iLevel][0] = 0;
		g_krgConsider[0][0].irgVal[iLevel][1] = 0; // g_krgConsider[0][1].irgVal[iLevel][1] = g_krgConsider[1][0].irgVal[iLevel][1] = g_krgConsider[1][1].irgVal[iLevel][1] = 0;
		g_krgConsider[0][0].irgVal[iLevel][2] = 0; // g_krgConsider[0][1].irgVal[iLevel][2] = g_krgConsider[1][0].irgVal[iLevel][2] = g_krgConsider[1][1].irgVal[iLevel][2] = 0;

		int iValue = iLevel*iLevel;
		if( 10000 < iValue ) iValue = 10000;
		// PC VS PC
		g_krgConsider[0][0].irgVal[iLevel][0] = int(iValue/6); // DF		
		g_krgConsider[0][0].irgVal[iLevel][2] = int(iValue/13); // DG

		g_krgConsider[0][0].irgVal[iLevel][1] = int(iValue/39); // RS
		if( 100 < iLevel && 106 > iLevel ) g_krgConsider[0][0].irgVal[iLevel][1] = int(3*iLevel-45);
		else if( 105 < iLevel ) g_krgConsider[0][0].irgVal[iLevel][1] = int(4*iLevel-150);

		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\t[Consider] iLevel:%d  \tPCvsPC(DF:%d  \tRS:%d  \tDG:%d) \tPCvsNPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsPC(DF:%d \tRS:%d \tDG:%d)  \tNPCvsNPC(DF:%d \tRS:%d \tDG:%d) \r\n", iLevel
				, g_krgConsider[0][0].irgVal[iLevel][0], g_krgConsider[0][0].irgVal[iLevel][1], g_krgConsider[0][0].irgVal[iLevel][2]
				, g_krgConsider[0][1].irgVal[iLevel][0], g_krgConsider[0][1].irgVal[iLevel][1], g_krgConsider[0][1].irgVal[iLevel][2]
				, g_krgConsider[1][0].irgVal[iLevel][0], g_krgConsider[1][0].irgVal[iLevel][1], g_krgConsider[1][0].irgVal[iLevel][2]
				, g_krgConsider[1][1].irgVal[iLevel][0], g_krgConsider[1][1].irgVal[iLevel][1], g_krgConsider[1][1].irgVal[iLevel][2]
					);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
		}
	}


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bRvRPKConsiderGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iDefenderCaste, iRewardBP, iAttackerCaste0, iAttackerCaste1, iAttackerCaste2, iAttackerCaste3, iAttackerCaste4, iAttackerCaste5, iAttackerCaste6, iAttackerCaste7, iAttackerCaste8, iAttackerCaste9, iAttackerCaste10, iAttackerCaste11, iAttackerCaste12, iAttackerCaste13, iAttackerCaste14, iAttackerCaste15, iAttackerCaste16, iAttackerCaste17;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iDefenderCaste = iRewardBP = iAttackerCaste0 = iAttackerCaste1 = iAttackerCaste2 = iAttackerCaste3 = iAttackerCaste4 = iAttackerCaste5 = iAttackerCaste6 = iAttackerCaste7 = iAttackerCaste8 = iAttackerCaste9 = iAttackerCaste10 = iAttackerCaste11 = iAttackerCaste12 = iAttackerCaste13 = iAttackerCaste14 = iAttackerCaste15 = iAttackerCaste16 = iAttackerCaste17 = 0;

			id = vec_It->iID;
			iDefenderCaste = id;

			g_pkSettingMgr->HT_bGetRvRPKConsiderRewardBP( id, &iRewardBP );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste0( id, &iAttackerCaste0 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste1( id, &iAttackerCaste1 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste2( id, &iAttackerCaste2 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste3( id, &iAttackerCaste3 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste4( id, &iAttackerCaste4 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste5( id, &iAttackerCaste5 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste6( id, &iAttackerCaste6 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste7( id, &iAttackerCaste7 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste8( id, &iAttackerCaste8 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste9( id, &iAttackerCaste9 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste10( id, &iAttackerCaste10 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste11( id, &iAttackerCaste11 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste12( id, &iAttackerCaste12 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste13( id, &iAttackerCaste13 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste14( id, &iAttackerCaste14 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste14( id, &iAttackerCaste15 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste15( id, &iAttackerCaste16 );
			g_pkSettingMgr->HT_bGetRvRPKConsiderAttackerCaste16( id, &iAttackerCaste17 );

			++vec_It;

			if( 0 <= iDefenderCaste && 17 >= iDefenderCaste )
			{
				g_irgRvRPKConsider[iDefenderCaste][0] = iAttackerCaste0;
				g_irgRvRPKConsider[iDefenderCaste][1] = iAttackerCaste1;
				g_irgRvRPKConsider[iDefenderCaste][2] = iAttackerCaste2;
				g_irgRvRPKConsider[iDefenderCaste][3] = iAttackerCaste3;
				g_irgRvRPKConsider[iDefenderCaste][4] = iAttackerCaste4;
				g_irgRvRPKConsider[iDefenderCaste][5] = iAttackerCaste5;
				g_irgRvRPKConsider[iDefenderCaste][6] = iAttackerCaste6;
				g_irgRvRPKConsider[iDefenderCaste][7] = iAttackerCaste7;
				g_irgRvRPKConsider[iDefenderCaste][8] = iAttackerCaste8;
				g_irgRvRPKConsider[iDefenderCaste][9] = iAttackerCaste9;
				g_irgRvRPKConsider[iDefenderCaste][10] = iAttackerCaste10;
				g_irgRvRPKConsider[iDefenderCaste][11] = iAttackerCaste11;
				g_irgRvRPKConsider[iDefenderCaste][12] = iAttackerCaste12;
				g_irgRvRPKConsider[iDefenderCaste][13] = iAttackerCaste13;
				g_irgRvRPKConsider[iDefenderCaste][14] = iAttackerCaste14;
				g_irgRvRPKConsider[iDefenderCaste][15] = iAttackerCaste15;
				g_irgRvRPKConsider[iDefenderCaste][16] = iAttackerCaste16;
				g_irgRvRPKConsider[iDefenderCaste][17] = iAttackerCaste17;
				g_irgRewardBP[iDefenderCaste] = iRewardBP;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- iDefenderCaste:%3d, \tRewardBP:%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d, \t%3d \r\n"
						, iDefenderCaste, g_irgRewardBP[iDefenderCaste]
						, g_irgRvRPKConsider[iDefenderCaste][0], g_irgRvRPKConsider[iDefenderCaste][1], g_irgRvRPKConsider[iDefenderCaste][2], g_irgRvRPKConsider[iDefenderCaste][3]
						, g_irgRvRPKConsider[iDefenderCaste][4], g_irgRvRPKConsider[iDefenderCaste][5], g_irgRvRPKConsider[iDefenderCaste][6], g_irgRvRPKConsider[iDefenderCaste][7]
						, g_irgRvRPKConsider[iDefenderCaste][8], g_irgRvRPKConsider[iDefenderCaste][9], g_irgRvRPKConsider[iDefenderCaste][10], g_irgRvRPKConsider[iDefenderCaste][11]
						, g_irgRvRPKConsider[iDefenderCaste][12], g_irgRvRPKConsider[iDefenderCaste][13], g_irgRvRPKConsider[iDefenderCaste][14], g_irgRvRPKConsider[iDefenderCaste][15]
						, g_irgRvRPKConsider[iDefenderCaste][16], g_irgRvRPKConsider[iDefenderCaste][17]
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )





	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bEffectToleranceGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iClass1, iClass2, iHold, iStun, iSleep, iBlind, iTerror, iTaunt, iSlowMove, iSlowAttack;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iClass1 = iClass2 = iHold = iStun = iSleep = iBlind = iTerror = iTaunt = iSlowMove = iSlowAttack = 0;	
			id = vec_It->iID;

			g_pkSettingMgr->HT_bGetEffectToleranceClass1( id, &iClass1 );
			g_pkSettingMgr->HT_bGetEffectToleranceClass2( id, &iClass2 );
			g_pkSettingMgr->HT_bGetEffectToleranceHold( id, &iHold );
			g_pkSettingMgr->HT_bGetEffectToleranceStun( id, &iStun );
			g_pkSettingMgr->HT_bGetEffectToleranceSleep( id, &iSleep );
			g_pkSettingMgr->HT_bGetEffectToleranceBlind( id, &iBlind );
			g_pkSettingMgr->HT_bGetEffectToleranceTerror( id, &iTerror );
			g_pkSettingMgr->HT_bGetEffectToleranceTaunt( id, &iTaunt );
			g_pkSettingMgr->HT_bGetEffectToleranceSlowMove( id, &iSlowMove );
			g_pkSettingMgr->HT_bGetEffectToleranceSlowAttack( id, &iSlowAttack );

			++vec_It;

			g_krgEffectTolerance[iClass1][iClass2].iHold = iHold;
			g_krgEffectTolerance[iClass1][iClass2].iStun = iStun;
			g_krgEffectTolerance[iClass1][iClass2].iSleep = iSleep;
			g_krgEffectTolerance[iClass1][iClass2].iBlind = iBlind;
			g_krgEffectTolerance[iClass1][iClass2].iTerror = iTerror;
			g_krgEffectTolerance[iClass1][iClass2].iTaunt = iTaunt;
			g_krgEffectTolerance[iClass1][iClass2].iSlowMove = iSlowMove;
			g_krgEffectTolerance[iClass1][iClass2].iSlowAttack = iSlowAttack;
			
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- iClassLvl:%d, iSpcClass:%d, iHold:%2d, iStun:%2d, iSleep:%2d, iBlind:%2d, iTerror:%2d, iTaunt:%2d, iSlowMove:%2d, iSlowAttack:%2d \r\n"
					, iClass1, iClass2
					, g_krgEffectTolerance[iClass1][iClass2].iHold, g_krgEffectTolerance[iClass1][iClass2].iStun, g_krgEffectTolerance[iClass1][iClass2].iSleep, g_krgEffectTolerance[iClass1][iClass2].iBlind
					, g_krgEffectTolerance[iClass1][iClass2].iTerror, g_krgEffectTolerance[iClass1][iClass2].iTaunt, g_krgEffectTolerance[iClass1][iClass2].iSlowMove, g_krgEffectTolerance[iClass1][iClass2].iSlowAttack
					);
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}

		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bItemByLevelGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iItemCategory = 0; 
		int irgLvl[21] = { 0,0,0, };

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iItemCategory = id;
			memset( irgLvl, 0, sizeof(irgLvl) );

			g_pkSettingMgr->HT_bGetItemByLevelLvl1( id, &irgLvl[1] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl2 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl2( id, &irgLvl[2] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl2 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl3( id, &irgLvl[3] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl3 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl4( id, &irgLvl[4] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl4 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl5( id, &irgLvl[5] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl5 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl6( id, &irgLvl[6] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl6 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl7( id, &irgLvl[7] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl7 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl8( id, &irgLvl[8] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl8 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl9( id, &irgLvl[9] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl9 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl10( id, &irgLvl[10] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl10 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl11( id, &irgLvl[11] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl11 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl12( id, &irgLvl[12] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl12 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl13( id, &irgLvl[13] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl13 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl14( id, &irgLvl[14] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl14 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl15( id, &irgLvl[15] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl15 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl16( id, &irgLvl[16] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl16 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl17( id, &irgLvl[17] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl17 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl18( id, &irgLvl[18] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl18 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl19( id, &irgLvl[19] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl19 : %d", iOut );
			g_pkSettingMgr->HT_bGetItemByLevelLvl20( id, &irgLvl[20] );   //) fprintf( pFile, "\nHT_bGetItemByLevelLvl20 : %d", iOut );

			++vec_It;

			if( eItm_MaxCategory <= iItemCategory )
			{
				assert( !"[g_krgItemByLevel] Item category is over the limit");
				exit( 0 );
			}

			if( 0 <= iItemCategory && eItm_MaxCategory > iItemCategory )
			{
				for( int i = 1; i < eItm_MaxLevel; ++i )
				{
					if( HT_PARAMTYPE_ITEM_START > irgLvl[i] ) g_krgItemByLevel[iItemCategory][i].snIndex = 0;
					else g_krgItemByLevel[iItemCategory][i].snIndex = irgLvl[i] - HT_PARAMTYPE_ITEM_START + 1;
					g_krgItemByLevel[iItemCategory][i].snDurability = pItemData[g_krgItemByLevel[iItemCategory][i].snIndex].sMaxDur;
					g_krgItemByLevel[iItemCategory][i].byCount = 1;
					g_krgItemByLevel[iItemCategory][i].byRefineLevel = 0;
					for( int j = 0; j < MAX_SUBMATERIALSIZE; ++j ) g_krgItemByLevel[iItemCategory][i].bySubRefine[j] =0;

					{
						char chBuf[512] = { 0,0,0, };
						sprintf(chBuf, "g_krgItemByLevel[%2d][%2d].snIndex: %3d, dur:%4d, count:%2d, refineLvl:%d \r\n", iItemCategory, i, g_krgItemByLevel[iItemCategory][i].snIndex, g_krgItemByLevel[iItemCategory][i].snDurability, g_krgItemByLevel[iItemCategory][i].byCount, 0 ); 
						WriteLog( chBuf, ".\\monster_log\\[Log]LoadRwdItem8th.txt" );
					}
				}

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- Category:%3d, Lvl1:%4d, Lvl2:%4d, Lvl3:%4d, Lvl4:%4d, Lvl5:%4d, Lvl6:%4d, Lvl7:%4d, Lvl8:%4d, Lvl9:%4d, Lvl10:%4d, Lvl11:%4d, Lvl12:%4d, Lvl13:%4d, Lvl14:%4d, Lvl15:%4d, Lvl16:%4d, Lvl17:%4d, Lvl18:%4d, Lvl19:%4d, Lvl20:%4d \r\n"
						, iItemCategory, irgLvl[1], irgLvl[2], irgLvl[3], irgLvl[4], irgLvl[5], irgLvl[6], irgLvl[7], irgLvl[8], irgLvl[9], irgLvl[10], irgLvl[11], irgLvl[12], irgLvl[13], irgLvl[14], irgLvl[15], irgLvl[16], irgLvl[17], irgLvl[18], irgLvl[19], irgLvl[20] );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	if( 0 != g_iWorldID )
	{
		vectorIDLevel.clear();
		if( g_pkSettingMgr->HT_bItemRateByMonLevelGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
		{
			int iMobLevel = 0;
			int irgLvl[eItm_MaxLevel] = { 0,0,0, };

			vec_It = vectorIDLevel.begin();
			while ( vec_It != vectorIDLevel.end() )
			{
				id = vec_It->iID;
				iMobLevel = id;
				memset( irgLvl, 0, sizeof(irgLvl) );

				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl1( id, &irgLvl[1] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl2( id, &irgLvl[2] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl3( id, &irgLvl[3] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl4( id, &irgLvl[4] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl5( id, &irgLvl[5] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl6( id, &irgLvl[6] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl7( id, &irgLvl[7] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl8( id, &irgLvl[8] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl9( id, &irgLvl[9] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl10( id, &irgLvl[10] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl11( id, &irgLvl[11] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl12( id, &irgLvl[12] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl13( id, &irgLvl[13] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl14( id, &irgLvl[14] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl15( id, &irgLvl[15] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl16( id, &irgLvl[16] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl17( id, &irgLvl[17] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl18( id, &irgLvl[18] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl19( id, &irgLvl[19] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelLvl20( id, &irgLvl[20] );

				++vec_It;

				if( eMonster_MaxLevel <= iMobLevel )
				{
					assert( !"[g_krgItemRateByMonLevel] Monster_MaxLevel is over the limit");
					exit( 0 );
				}

				if( 0 >= iMobLevel || eMonster_MaxLevel <= iMobLevel ) continue;
				//g_krgItemRateByMonLevel[iMobLevel].Init();
				for( int i = 1; i < eItm_MaxLevel; ++i )
				{			
					g_krgItemRateByMonLevel[iMobLevel].AddCard( i, irgLvl[i] ); // 1부터 시작,  1~11
				}
				
				//srand( rand() );
				g_krgItemRateByMonLevel[iMobLevel].Shuffle();
				//g_krgItemRateByMonLevel[iMobLevel].Shuffle();

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t-(Main SRV) MonLevel:%2d, Lvl1:%4d, Lvl2:%4d, Lvl3:%4d, Lvl4:%4d, Lvl5:%4d, Lvl6:%4d, Lvl7:%4d, Lvl8:%4d, Lvl9:%4d, Lvl10:%4d, Lvl11:%4d, Lvl12:%4d, Lvl13:%4d, Lvl14:%4d, Lvl15:%4d, Lvl16:%4d, Lvl17:%4d, Lvl18:%4d, Lvl19:%4d, Lvl20:%4d \r\n"
						, iMobLevel, irgLvl[1], irgLvl[2], irgLvl[3], irgLvl[4], irgLvl[5], irgLvl[6], irgLvl[7], irgLvl[8], irgLvl[9], irgLvl[10], irgLvl[11], irgLvl[12], irgLvl[13], irgLvl[14], irgLvl[15], irgLvl[16], irgLvl[17], irgLvl[18], irgLvl[19], irgLvl[20] );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			} // while ( vec_It != vectorIDLevel.end() )
		} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )
	}
	else
	{
		vectorIDLevel.clear();
		if( g_pkSettingMgr->HT_bItemRateByMonLevelForTestSrvGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
		{
			int iMobLevel = 0;
			int irgLvl[eItm_MaxLevel] = { 0,0,0, };

			vec_It = vectorIDLevel.begin();
			while ( vec_It != vectorIDLevel.end() )
			{
				id = vec_It->iID;
				iMobLevel = id;
				memset( irgLvl, 0, sizeof(irgLvl) );

				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl1( id, &irgLvl[1] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl2( id, &irgLvl[2] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl3( id, &irgLvl[3] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl4( id, &irgLvl[4] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl5( id, &irgLvl[5] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl6( id, &irgLvl[6] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl7( id, &irgLvl[7] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl8( id, &irgLvl[8] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl9( id, &irgLvl[9] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl10( id, &irgLvl[10] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl11( id, &irgLvl[11] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl12( id, &irgLvl[12] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl13( id, &irgLvl[13] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl14( id, &irgLvl[14] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl15( id, &irgLvl[15] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl16( id, &irgLvl[16] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl17( id, &irgLvl[17] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl18( id, &irgLvl[18] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl19( id, &irgLvl[19] );
				g_pkSettingMgr->HT_bGetItemRateByMonLevelForTestSrvLvl20( id, &irgLvl[20] );

				++vec_It;

				if( eMonster_MaxLevel <= iMobLevel )
				{
					assert( !"[g_krgItemRateByMonLevel] Monster_MaxLevel is over the limit");
					exit( 0 );
				}

				if( 0 >= iMobLevel || eMonster_MaxLevel <= iMobLevel ) continue;
				//g_krgItemRateByMonLevel[iMobLevel].Init();
				for( int i = 1; i < eItm_MaxLevel; ++i )
				{			
					g_krgItemRateByMonLevel[iMobLevel].AddCard( i, irgLvl[i] ); // 1부터 시작,  1~11
				}
				
				//srand( rand() );
				g_krgItemRateByMonLevel[iMobLevel].Shuffle();
				//g_krgItemRateByMonLevel[iMobLevel].Shuffle();

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t-(Test SRV) MonLevel:%2d, Lvl1:%4d, Lvl2:%4d, Lvl3:%4d, Lvl4:%4d, Lvl5:%4d, Lvl6:%4d, Lvl7:%4d, Lvl8:%4d, Lvl9:%4d, Lvl10:%4d, Lvl11:%4d, Lvl12:%4d, Lvl13:%4d, Lvl14:%4d, Lvl15:%4d, Lvl16:%4d, Lvl17:%4d, Lvl18:%4d, Lvl19:%4d, Lvl20:%4d \r\n"
						, iMobLevel, irgLvl[1], irgLvl[2], irgLvl[3], irgLvl[4], irgLvl[5], irgLvl[6], irgLvl[7], irgLvl[8], irgLvl[9], irgLvl[10], irgLvl[11], irgLvl[12], irgLvl[13], irgLvl[14], irgLvl[15], irgLvl[16], irgLvl[17], irgLvl[18], irgLvl[19], irgLvl[20] );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			} // while ( vec_It != vectorIDLevel.end() )
		} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )
	}

	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bItemGroupGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iItemGroup = 0, iItemID = 0;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;	
			iItemGroup = iItemID = 0;

			g_pkSettingMgr->HT_bGetItemGroupGroup( id, &iItemGroup );
			g_pkSettingMgr->HT_bGetItemGroupItemID( id, &iItemID );

			++vec_It;

			if( eRwd_ItemGroup < iItemGroup )		
			{
				assert( !"[g_srgItemGroup] Item group is over the limit" );
				exit( 0 );
			}

			g_srgItemGroup[iItemGroup][g_srgGroupItemCount[iItemGroup]] = (short)iItemID;
			++g_srgGroupItemCount[iItemGroup];

			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- Group:%2d, ItemID:%4d\r\n", iItemGroup, iItemID );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )

		for( int iItemGroup = 1; iItemGroup < eRwd_ItemGroup; ++iItemGroup )
		{
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- Group:%2d, ItemCount:%2d \r\n", iItemGroup, g_srgGroupItemCount[iItemGroup] );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		}
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bRateByItemCategoryGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iItemCategory = 0, iRate = 0;;		
		
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iItemCategory = id;

			g_pkSettingMgr->HT_bGetRateByItemCategoryRate( id, &iRate );

			++vec_It;


			if( eItm_MaxCategory <= iItemCategory )
			{
				assert( !"[g_kRateByItemCategory] Item category is over the limit");
				exit( 0 );
			}

			if( 0 > iItemCategory || eItm_MaxCategory <= iItemCategory ) continue;
			g_kRateByItemCategory.AddCard( iItemCategory, iRate );	// 0부터 시작
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- iCategory:%3d, iRate:%3d \r\n", iItemCategory, iRate );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )

		g_kRateByItemCategory.Shuffle();
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bKalaAltarGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iID, iZone, iClan, iX, iY;;
		
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iZone = iClan = iX = iY = 0;
			iID = id;

			g_pkSettingMgr->HT_bGetKalaAltarZone( id, &iZone );
			g_pkSettingMgr->HT_bGetKalaAltarClan( id, &iClan );
			g_pkSettingMgr->HT_bGetKalaAltarX( id, &iX );
			g_pkSettingMgr->HT_bGetKalaAltarY( id, &iY );

			++vec_It;
			if( g_iZoneID != iZone ) continue;

			if( 0 <= iID && eKalaAltar_MaxCount > iID )
			{
				g_krgKalaAltar[iID].sID = iID;
				g_krgKalaAltar[iID].sTrimuriti = iClan;
//				g_krgKalaAltar[iID].x = iX;
//				g_krgKalaAltar[iID].y = iY;
				g_krgKalaAltar[iID].x = 950;
				g_krgKalaAltar[iID].y = 60;
				if(iID==0)
				{
				g_krgKalaAltar[iID].x = 188;
				g_krgKalaAltar[iID].y = 196;
				}
				if(iID==1)
				{
				g_krgKalaAltar[iID].x = 238;
				g_krgKalaAltar[iID].y = 242;
				}
				if(iID==3)
				{
				g_krgKalaAltar[iID].x = 494;
				g_krgKalaAltar[iID].y = 462;
				}
				if(iID==5)
				{
				g_krgKalaAltar[iID].x = 910;
				g_krgKalaAltar[iID].y = 386;
				}
				if(iID==6)
				{
				g_krgKalaAltar[iID].x = 836;
				g_krgKalaAltar[iID].y = 402;
				}
				if(iID==8)
				{
				g_krgKalaAltar[iID].x = 470;
				g_krgKalaAltar[iID].y = 514;
				}
				if(iID==10)
				{
				g_krgKalaAltar[iID].x = 378;
				g_krgKalaAltar[iID].y = 902;
				}
				if(iID==11)
				{
				g_krgKalaAltar[iID].x = 398;
				g_krgKalaAltar[iID].y = 830;
				}
				if(iID==13)
				{
				g_krgKalaAltar[iID].x = 532;
				g_krgKalaAltar[iID].y = 510;
				} 
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "\t- Kala Altar> ID:%d, clan:%d, L(%d,%d) \r\n", g_krgKalaAltar[iID].sID, g_krgKalaAltar[iID].sTrimuriti, g_krgKalaAltar[iID].x, g_krgKalaAltar[iID].y );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bRewarderPositionGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iNPCIndex, iID, iZone, iClan, iX, iY;
		
		
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iID = iZone = iNPCIndex = iClan = iX = iY = 0;
			iID = id;

			g_pkSettingMgr->HT_bGetRewarderPositionZone( id, &iZone );
			g_pkSettingMgr->HT_bGetRewarderPositionNPCIndex( id, &iNPCIndex );
			g_pkSettingMgr->HT_bGetRewarderPositionClan( id, &iClan );
			g_pkSettingMgr->HT_bGetRewarderPositionX( id, &iX );
			g_pkSettingMgr->HT_bGetRewarderPositionY( id, &iY );

			++vec_It;
			if( g_iZoneID != iZone ) continue;

			if( 0 <= iNPCIndex && eKalaRewarder_MaxCount >= iNPCIndex )
			{
				if( 0 <= iClan && eTNClan_Siva >= iClan )
				{
					g_krgKalaRewarderPosition[iNPCIndex][iClan].x = iX;
					g_krgKalaRewarderPosition[iNPCIndex][iClan].y = iY;

					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "Rewarder Position> NPC:%d, clan:%d, L(%d,%d) \r\n", iNPCIndex, iClan, g_krgKalaRewarderPosition[iNPCIndex][iClan].x, g_krgKalaRewarderPosition[iNPCIndex][iClan].y );
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bEventListGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iZone, iEventID, iTask1, iTask2, iTask3, iTask4, iTask5, iCoolDownTime, iCount, iProceedType, iDuration;		
	
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iZone = iEventID = iTask1 = iTask2 = iTask3 = iTask4 = iTask5 = iCoolDownTime = iCount = iProceedType = iDuration = 0;

			g_pkSettingMgr->HT_bGetEventListZone( id, &iZone );
			g_pkSettingMgr->HT_bGetEventListEventID( id, &iEventID );
			g_pkSettingMgr->HT_bGetEventListTask1( id, &iTask1 );
			g_pkSettingMgr->HT_bGetEventListTask2( id, &iTask2 );
			g_pkSettingMgr->HT_bGetEventListTask3( id, &iTask3 );
			g_pkSettingMgr->HT_bGetEventListTask4( id, &iTask4 );
			g_pkSettingMgr->HT_bGetEventListTask5( id, &iTask5 );
			g_pkSettingMgr->HT_bGetEventListCoolDownTime( id, &iCoolDownTime );
			g_pkSettingMgr->HT_bGetEventListCount( id, &iCount );
			g_pkSettingMgr->HT_bGetEventListProceedType( id, &iProceedType );
			g_pkSettingMgr->HT_bGetEventListDuration( id, &iDuration );

			++vec_It;
			if( (0 != iZone) && (g_iZoneID != iZone) ) continue;

			if( eEvent_MaxCount <= iEventID )
			{
				assert( !"[g_krgEventList] Event ID is over the limit");
				exit( 0 );
			}

			if( 0 < iEventID && eEvent_MaxCount > iEventID )
			{
				g_krgEventList[iEventID].srgTask[0] = iTask1;
				g_krgEventList[iEventID].srgTask[1] = iTask2;
				g_krgEventList[iEventID].srgTask[2] = iTask3;
				g_krgEventList[iEventID].srgTask[3] = iTask4;
				g_krgEventList[iEventID].srgTask[4] = iTask5;
				g_krgEventList[iEventID].uiCoolDownTime = iCoolDownTime;
				g_krgEventList[iEventID].sCount = iCount;
				g_krgEventList[iEventID].sProceedType = iProceedType;
				g_krgEventList[iEventID].iDuration = iDuration;
				g_krgEventList[iEventID].uiAvailableTime = 0;		
				g_krgEventList[iEventID].sClan = eEvntClan_All;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- EventID:%3d, \tiTask1:%3d, \tiTask2:%3d, \tiTask3:%3d, \tiTask4:%3d, \tiTask5:%3d, \tcool-down time:%d, count:%d, procdtype:%d, DurType:%d \r\n"
						, iEventID, g_krgEventList[iEventID].srgTask[0], g_krgEventList[iEventID].srgTask[1], g_krgEventList[iEventID].srgTask[2], g_krgEventList[iEventID].srgTask[3], g_krgEventList[iEventID].srgTask[4]
						, g_krgEventList[iEventID].uiCoolDownTime, g_krgEventList[iEventID].sCount, g_krgEventList[iEventID].sProceedType, g_krgEventList[iEventID].iDuration
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )


	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bTaskListGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iZone, iTaskID, iActionID2, iParam1, iParam2, iParam3, iParam4, iParam5, iParam6;
			
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			iZone = iTaskID = iActionID2 = iParam1 = iParam2 = iParam3 = iParam4 = iParam5 = iParam6 = 0;
			id = vec_It->iID;

			g_pkSettingMgr->HT_bGetTaskListZone( id, &iZone );
			g_pkSettingMgr->HT_bGetTaskListTaskID( id, &iTaskID );
			g_pkSettingMgr->HT_bGetTaskListActionID( id, &iActionID2 );
			g_pkSettingMgr->HT_bGetTaskListParam1( id, &iParam1 );
			g_pkSettingMgr->HT_bGetTaskListParam2( id, &iParam2 );
			g_pkSettingMgr->HT_bGetTaskListParam3( id, &iParam3 );
			g_pkSettingMgr->HT_bGetTaskListParam4( id, &iParam4 );
			g_pkSettingMgr->HT_bGetTaskListParam5( id, &iParam5 );
			g_pkSettingMgr->HT_bGetTaskListParam6( id, &iParam6 );
            if (iZone == 10)
			{
			   if ( iParam1 == 2866 || iParam1 == 2867 ) iParam1 = 2081;
			   if ( iParam5 == 2866 || iParam5 ==2867 ) iParam5 = 2081;
			} 
			
			++vec_It;

			if( (0 != iZone) && (g_iZoneID != iZone) ) continue;

			if( eTask_MaxCount <= iTaskID )
			{
				assert( !"[g_krgTaskList] Task ID is over the limit");
				exit( 0 );
			}

			if( 0 < iTaskID && eTask_MaxCount > iTaskID )
			{
				g_krgTaskList[iTaskID].iActionID = iActionID2;
				g_krgTaskList[iTaskID].irgParam[0] = iParam1;
				g_krgTaskList[iTaskID].irgParam[1] = iParam2;
				g_krgTaskList[iTaskID].irgParam[2] = iParam3;
				g_krgTaskList[iTaskID].irgParam[3] = iParam4;
				g_krgTaskList[iTaskID].irgParam[4] = iParam5;
				g_krgTaskList[iTaskID].irgParam[5] = iParam6;

				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t- TaskID:%3d, \tActionID:%3d, \tParam1:%3d, \tParam2:%3d, \tParam3:%3d, \tParam4:%3d, \tParam5:%3d, \tParam6:%3d \r\n"
						, iTaskID, g_krgTaskList[iTaskID].iActionID
						, g_krgTaskList[iTaskID].irgParam[0], g_krgTaskList[iTaskID].irgParam[1], g_krgTaskList[iTaskID].irgParam[2]
						, g_krgTaskList[iTaskID].irgParam[3], g_krgTaskList[iTaskID].irgParam[4], g_krgTaskList[iTaskID].irgParam[5]
						);
					WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
				}
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bEventScheduleGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iZone, iMin, iSec, iTimeEvent;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iZone = iMin = iSec = iTimeEvent = 0;

			g_pkSettingMgr->HT_bGetEventScheduleZone( id, &iZone );
			g_pkSettingMgr->HT_bGetEventScheduleMin( id, &iMin );
			g_pkSettingMgr->HT_bGetEventScheduleSec( id, &iSec );
			g_pkSettingMgr->HT_bGetEventScheduleEvent( id, &iTimeEvent );

			++vec_It;

			if( (0 != iZone) && (g_iZoneID != iZone) ) continue;
			if( 0 > iMin || 60 <= iMin ) continue;
			if( 0 > iSec || 56 < iSec ) continue;
			if( 0 > iTimeEvent || eEvent_MaxCount <= iTimeEvent ) continue;

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
				sprintf(chBuf, "\t- Time slot : %3d, event : %3d, min: %2d, sec:%2d, zoneID: %2d \r\n", iTimeSlot, iTimeEvent, iMin, iSec, iZone );
				WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
			}
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bAIListGetAllID( &vectorIDLevel ) )



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bSetItemGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iID, iHelmet, iNecklace, iArmor, iBelt, iWeapon, iShield, iBoots, iGloves, iPants, iEffectItem, iEffectItem2, iEffectItem3;

		WriteLog( "\r\n\nHTSSetting.txl > LoadSetting() >> Set Item \r\n", ".\\monster_log\\[Log]LoadSettings2.txt" );

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iID = iHelmet = iNecklace = iArmor = iBelt = iWeapon = iShield = iBoots = iGloves = iPants = iEffectItem = iEffectItem2 = iEffectItem3 = 0;

			g_pkSettingMgr->HT_bGetSetItemID( id, &iID );
			g_pkSettingMgr->HT_bGetSetItemHelmet( id, &iHelmet );
			g_pkSettingMgr->HT_bGetSetItemNecklace( id, &iNecklace );
			g_pkSettingMgr->HT_bGetSetItemArmor( id, &iArmor );
			g_pkSettingMgr->HT_bGetSetItemBelt( id, &iBelt );
			g_pkSettingMgr->HT_bGetSetItemWeapon( id, &iWeapon );
			g_pkSettingMgr->HT_bGetSetItemShield( id, &iShield );
			g_pkSettingMgr->HT_bGetSetItemBoots( id, &iBoots );
			g_pkSettingMgr->HT_bGetSetItemGloves( id, &iGloves );
			g_pkSettingMgr->HT_bGetSetItemPants( id, &iPants );
			g_pkSettingMgr->HT_bGetSetItemEffectItem( id, &iEffectItem );
			g_pkSettingMgr->HT_bGetSetItemEffectItem2( id, &iEffectItem2 );
#ifndef __BEFORE_SET_ITEM_EXPANDED__
			g_pkSettingMgr->HT_bGetSetItemEffectItem3( id, &iEffectItem3 );
#endif

			if( 0 > iID || eSetItem_Size <= iID ) continue;

			memset( &g_krgSetItem[iID], 0, sizeof(TNSETITEM) );
			g_krgSetItem[iID].iID = iID;
			g_krgSetItem[iID].irgReq[eTNEqu_Helmet] = iHelmet;
			g_krgSetItem[iID].irgReq[eTNEqu_Necklace] = iNecklace;
			g_krgSetItem[iID].irgReq[eTNEqu_Armor] = iArmor;
			g_krgSetItem[iID].irgReq[eTNEqu_Belt] = iBelt;
			g_krgSetItem[iID].irgReq[eTNEqu_OneHandWeapon] = iWeapon;
			g_krgSetItem[iID].irgReq[eTNEqu_Shield] = iShield;
			g_krgSetItem[iID].irgReq[eTNEqu_Boots] = iBoots;
			g_krgSetItem[iID].irgReq[eTNEqu_Gloves] = iGloves;
			g_krgSetItem[iID].irgReq[eTNEqu_Pants] = iPants;
			g_krgSetItem[iID].irgEffectItem[0] = iEffectItem;
			g_krgSetItem[iID].irgEffectItem[1] = iEffectItem2;
			g_krgSetItem[iID].irgEffectItem[2] = iEffectItem3;

			++vec_It;

			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\tID:%d, Set(Helmet:%d, Necklace:%d, Armor:%d, Belt:%d, Weapon:%d, Shield:%d, Boots:%d, Gloves:%d, Pants:%d, Effect(%d, %d, %d) \r\n"
				, g_krgSetItem[iID].iID
				, iHelmet, iNecklace, iArmor, iBelt, iWeapon, iShield, iBoots, iGloves, iPants, iEffectItem, iEffectItem2, iEffectItem3
				);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadSettings2.txt" );
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bSetItemGetAllID( &vectorIDLevel ) )



	vectorIDLevel.clear();
	if( g_pkSettingMgr->HT_bGameEventGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		int iEventID, iType, iTarget, iZone, iAction1, iParam11, iParam12, iAction2, iParam21, iParam22;
		int iAction3, iParam31, iParam32, iAction4, iParam41, iParam42, iAction5, iParam51, iParam52, iAction6, iParam61, iParam62;

		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			iEventID = iType = iTarget = iAction1 = iParam11 = iParam12 = iAction2 = iParam21 = iParam22 = 0;
			iAction3 = iParam31 = iParam32 = iAction4 = iParam41 = iParam42 = iAction5 = iParam51 = iParam52 = iAction6 = iParam61 = iParam62 = 0;

			g_pkSettingMgr->HT_bGetGameEventID		( id, &iEventID );
			g_pkSettingMgr->HT_bGetGameEventType	( id, &iType );
			g_pkSettingMgr->HT_bGetGameEventTarget	( id, &iTarget );
			g_pkSettingMgr->HT_bGetGameEventZone	( id, &iZone );
			g_pkSettingMgr->HT_bGetGameEventAction1	( id, &iAction1 );
			g_pkSettingMgr->HT_bGetGameEventParam11	( id, &iParam11 );
			g_pkSettingMgr->HT_bGetGameEventParam12	( id, &iParam12 );
			g_pkSettingMgr->HT_bGetGameEventAction2	( id, &iAction2 );
			g_pkSettingMgr->HT_bGetGameEventParam21	( id, &iParam21 );
			g_pkSettingMgr->HT_bGetGameEventParam22	( id, &iParam22 );
			g_pkSettingMgr->HT_bGetGameEventAction3	( id, &iAction3 );
			g_pkSettingMgr->HT_bGetGameEventParam31	( id, &iParam31 );
			g_pkSettingMgr->HT_bGetGameEventParam32	( id, &iParam32 );
			g_pkSettingMgr->HT_bGetGameEventAction4	( id, &iAction4 );
			g_pkSettingMgr->HT_bGetGameEventParam41	( id, &iParam41 );
			g_pkSettingMgr->HT_bGetGameEventParam42	( id, &iParam42 );
			g_pkSettingMgr->HT_bGetGameEventAction5	( id, &iAction5 );
			g_pkSettingMgr->HT_bGetGameEventParam51	( id, &iParam51 );
			g_pkSettingMgr->HT_bGetGameEventParam52	( id, &iParam52 );
			g_pkSettingMgr->HT_bGetGameEventAction6	( id, &iAction6 );
			g_pkSettingMgr->HT_bGetGameEventParam61	( id, &iParam61 );
			g_pkSettingMgr->HT_bGetGameEventParam62	( id, &iParam62 );

			++vec_It;

			if(iEventID<=0 || iEventID>=MAX_EVENT) continue;

			g_kGameEvent[iEventID-1].iEventID = iEventID;
			g_kGameEvent[iEventID-1].iType = iType;
			g_kGameEvent[iEventID-1].iTarget = iTarget;
			g_kGameEvent[iEventID-1].iZone = iZone;
			g_kGameEvent[iEventID-1].stAction[0].iAction = iAction1;
			g_kGameEvent[iEventID-1].stAction[0].iParam1 = iParam11;
			g_kGameEvent[iEventID-1].stAction[0].iParam2 = iParam12;
			g_kGameEvent[iEventID-1].stAction[1].iAction = iAction2;
			g_kGameEvent[iEventID-1].stAction[1].iParam1 = iParam21;
			g_kGameEvent[iEventID-1].stAction[1].iParam2 = iParam22;
			g_kGameEvent[iEventID-1].stAction[2].iAction = iAction3;
			g_kGameEvent[iEventID-1].stAction[2].iParam1 = iParam31;
			g_kGameEvent[iEventID-1].stAction[2].iParam2 = iParam32;
			g_kGameEvent[iEventID-1].stAction[3].iAction = iAction4;
			g_kGameEvent[iEventID-1].stAction[3].iParam1 = iParam41;
			g_kGameEvent[iEventID-1].stAction[3].iParam2 = iParam42;
			g_kGameEvent[iEventID-1].stAction[4].iAction = iAction5;
			g_kGameEvent[iEventID-1].stAction[4].iParam1 = iParam51;
			g_kGameEvent[iEventID-1].stAction[4].iParam2 = iParam52;
			g_kGameEvent[iEventID-1].stAction[5].iAction = iAction6;
			g_kGameEvent[iEventID-1].stAction[5].iParam1 = iParam61;
			g_kGameEvent[iEventID-1].stAction[5].iParam2 = iParam62;
		} // while ( vec_It != vectorIDLevel.end() )
	} // if( g_pkSettingMgr->HT_bGameEventGetAllID( &vectorIDLevel ) )

	delete g_pkSettingMgr;
}

