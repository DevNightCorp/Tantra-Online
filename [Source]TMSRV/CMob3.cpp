#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "Basedef.h"
#include "Server.h"
#include "CMob.h"
#include "ItemEffect.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "CUser.h"
#include "HTParamMgr.h"
#include "Language.h"
#include "Quest.h"
#include "CrackType.h"
#include "GameEvent.h"
#include "CGuild.h"
#include "TNDeck1000.h"
#include "TNSiege.h"
#include "TNMagicLamp.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern CHTParameterMgr	g_ParamMgr;
extern CGameEvent		g_GameEvent;
//extern CGuild			pGuild[MAX_USER];
extern TNSTRONGHOLD		g_krgStronghold[eStronghold_MaxCount];
extern CPSock           MSGServerSocket;
extern int				g_iCastleOwner;

static byte g_byrgAffection[eConst_MaxAffectionCount+1] =
{
	1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16,17,18,19,20,
	21,22,23,23,25,26,27,28,29,30,
	31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,
	51,52,53,54,55,56,57,58,59,60,
	61,62,63,0
};

extern int ServerIndex;
extern unsigned int CurrentTime;
extern TNCELL              g_krgCell[MAX_GRIDY][MAX_GRIDX];
//extern unsigned short         pMobGrid   [MAX_GRIDY][MAX_GRIDX];
//extern CMob                   pMob     [MAX_MOB];  // 잘못설계했음.
//extern TNITEM_DATA            pItemData	[MAX_ITEM_DATA];
//extern TNSKILL_DATA           pSkillData	[MAX_SKILL_DATA];
//extern STRUCT_MOB				pMonsterData[MAX_MONSTER_DATA];

extern int                    g_iHostileTable[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTablePKOn[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTablePKOff[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTable[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTableRvR[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTableRvR[MAX_CLAN][MAX_CLAN];
extern int					  g_irgEnemyTableStrH[MAX_CLAN][MAX_CLAN];
extern int					  g_irgFriendTableStrH[MAX_CLAN][MAX_CLAN];
extern int                    g_pDirectionalTable[9][9];
extern int                    g_pKnockbackTable[9][2];
extern short                   g_pDetectEnemyRadius[eRds_MaxDetectEnemy+1];
extern char                   g_pDetectEnemyTable[ePos_MaxPosCount][2];
extern _S_TRIMURITY_AREA      TrimurityArea;
extern int                    g_iMonsterLevelForWritingLog;
//extern bool                   g_bIsInRvR;
extern int                     g_iZoneType;
extern short  				  g_srgAttackTypeVSArmorTypeChart[eAAC_ArmorTypeCount][eAAC_AttackTypeCount];
extern TNCONSIDER              g_krgConsider[eCon_Sort][eCon_Sort];
//extern int                     g_irgKalaAltar[eKalaAltar_MaxCount];
extern int                     g_irgSetting[MAX_SETTING];
extern int						g_iSwitch;

extern CMob * GetMobFromIndex(unsigned int idx);
extern void Log(char * str1,char * str2,unsigned int ip);
extern STRUCT_ITEMLIST   g_pItemList[MAX_ITEMLIST];
//extern CUser pUser[MAX_SERVER];

extern int   GetEmptyNPCMob       (void);
extern void CloseUser            (int conn);
extern int Percent( double a_dValue, double a_dPercent );
extern TNDeck1000				g_kMonsterScroll;
extern int					g_iCastleOwner;


unsigned int g_uiPermitToWrite = 0;

int CMob::CastSkill( S_CSP_CAST_AREA_SKILL* a_pMsg, int a_iTargetCount )
{
	if( NULL == a_pMsg ) return eTNRes_Failed;
	if( IsDead() ) return eTNRes_IsDead;
	if( eTNClan_GM == m_byClan ) return eTNRes_IsGM;
	if( eTNVSAfn_DontAttack & m_iAffections ) return eTNRes_HaveDontAttackAffection;
	if( eTNVSAfn_Invulnerable & m_iAffections ) return eTNRes_HaveInvulnerableAffection;
	if( 0 >= TargetY || MAX_GRIDY <= TargetY ) return eTNRes_InvalidCoord;
	if( 0 >= TargetX || MAX_GRIDX <= TargetX ) return eTNRes_InvalidCoord;
	if( eTNFsm_Sit == m_eFSM ) return eTNRes_Sit;
	if( m_iBlockedCell/*eTNCell_Blocked*/ & g_krgCell[TargetY][TargetX].usProperty ) return eTNRes_BlockedZone;
	//if( eTNCell_SafetyZone & g_krgCell[TargetY][TargetX].usProperty ) return eTNRes_SafetyZone; // safety zone이라면 어떠한 skill도 허용하지 않는다.

	if( eWaitAct_TownPortal == m_kWaitAction.iAction ) 
	{	m_kWaitAction.iAction = eWaitAct_None; m_snMovePortal = 0; 
		if(m_kWaitAction.iAction == eWaitAct_ZonePortal)
		{	char pch[256] = {0,};
			sprintf(pch, "Char:%s pustica is stopped by castskil", MOB.szName);
			Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
		}
	}
	//if( eWaitAct_TownPortal2 == m_kWaitAction.iAction ) return eTNRes_Failed;	//	워프시 스킬을 사용할수 없다
	//if( eWaitAct_TownPortal2 == m_kWaitAction.iAction ) m_kWaitAction.iAction = eWaitAct_None;
	//if( eWaitAct_TownPortal3 == m_kWaitAction.iAction ) return eTNRes_Failed;	//	워프시 스킬을 사용할수 없다
	if( eWaitAct_SummonParty == m_kWaitAction.iAction ) m_kWaitAction.iAction = eWaitAct_None;
	if( eTNMob_PC == m_eMobType ) 
	{
		if( g_irgSetting[eCnst_KarmaForRestrictingToAttack] <= MOB.snKarma ) return eTNRes_TooHighKarma;

		bool bKickOut = false;
		if( (MOB.byLevel < g_irgSetting[eCnst_AllowedLevelLow]) || (MOB.byLevel > g_irgSetting[eCnst_AllowedLevelHigh]) ) 
		{
			MoveZoneByNPC( eSaveNPC_Mandra );
			//MoveZone( eZone_Mandra, 486, 190 );
			return eTNRes_LevelIsNotAllowed;
		}

		if( (eZoneType_Guild == g_iZoneType) )
		{
			if(0 == MOB.nGuildID)
			{
				S_SCP_RESP_INIT_REGEN_CHAR sm;
				sm.wType = SCP_RESP_INIT_REGEN_CHAR;
				sm.byZone = MOB.bySaveZone;
				m_kWaitAction.iAction = eWaitAct_ZonePortal;
				pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 
	
				return eTNRes_HaveNoGuild;
			}
		}
	}

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	int iRes = eCmbt_Normal; // 전투판정결과를 위한 변수, 전투 판정의 성공(hit)은 아니다. 단순한 전투가 성공적으로 수행되었다는 것이다.
	unsigned short usSkillID = a_pMsg->snSkillID;
	TNSKILL_DATA kSkill;
	int iIndex = 0, iSkillBookIndex = MAX_SKILL ;
	TNEFFECT kMulStrike, kMulStrike2; // multiple-strike일 때에만 사용되는 변수	

	if( eCmbt_Echo == a_pMsg->snRes )
	{
		BroadcastCastSkill( a_pMsg, a_iTargetCount );
		// hack 검사
		if( 0 < a_pMsg->snSkillID )
		{
			m_kSkillCastRecord.iSkill = a_pMsg->snSkillID;
			m_kSkillCastRecord.uiTime = CurrentTime;
		}

		if( eTNMob_NPC == m_eMobType )
		{
			iIndex = m_krgSkill[m_iSkillCharged].iIndex;
			kSkill = pSkillData[iIndex];
			if( eTNCPhase_StartAction & kSkill.sCombatPhase ) StartAction( m_iHandle, kSkill, CurrentTarget );
		}

		m_iCombatSyncPhase = eTNCSP_Echo;

		return eTNRes_Succeeded;
	}

	m_iPrevAffections = m_iAffections;
	TurnOffAffection( eTNAfn_Invisible );

	a_pMsg->bySkillLevel = 0; //MOB.bySkill[i];

	if( (eTNSwitch_PKDisable&g_iSwitch) && (eTNMob_PC==m_eMobType) && (eZoneType_Normal == g_iZoneType) )		//	PK금지모드일경우
	{
		if(usSkillID == eTNSkl_NormalAttack)
		{
			for(int i=0; i<TN_MAX_TARGET_COUNT; i++)
			{
				if( a_pMsg->krgTarget[i].snKeyID>0 && a_pMsg->krgTarget[i].snKeyID<MAX_USER )	//	사람을 공격시 타겟에서 제외
					a_pMsg->krgTarget[i].snKeyID = 0;
			}
		}
		else
		{
			for( int i=0; i<MAX_SKILL; ++i ) 
				if( m_krgSkill[i].sID  == usSkillID ) break;
			if(i>=MAX_SKILL) return eTNRes_SkillNotRegistered;
			if(MOB.bySkill[i] <= 0) return eTNRes_SkillNotLearned;
			a_pMsg->bySkillLevel = MOB.bySkill[i];
			int nIndex = m_krgSkill[i].iIndex;				//+ m_krgSkill[iSkillBookIndex].byLevelPlus; // data 배열상의 index

			kSkill = pSkillData[nIndex];
			if(kSkill.iAllowedTargets == eTNAT_Enemy)		//	적을 공격하는 스킬일경우
			{
				for(int i=0; i<TN_MAX_TARGET_COUNT; i++)
				{
					if( a_pMsg->krgTarget[i].snKeyID>0 && a_pMsg->krgTarget[i].snKeyID<MAX_USER )	//	사람을 공격시 타겟에서 제외
						a_pMsg->krgTarget[i].snKeyID = 0;
				}
			}
		}
	}

	
	if( eTNSkl_NormalAttack == usSkillID )
	{
	     iIndex = get_WeaponIndex();
		 kSkill = pItemData[iIndex];    
	}
	else
	{
		if( eTNMob_PC == m_eMobType )
		{
			for( iSkillBookIndex = 0; iSkillBookIndex < MAX_SKILL; ++iSkillBookIndex ) if( m_krgSkill[iSkillBookIndex].sID  == usSkillID ) break;
			if( MAX_SKILL <= iSkillBookIndex ) return eTNRes_SkillNotRegistered;
			if( 0 >= MOB.bySkill[iSkillBookIndex] ) return eTNRes_SkillNotLearned;
			iIndex = m_krgSkill[iSkillBookIndex].iIndex; //+ m_krgSkill[iSkillBookIndex].byLevelPlus; // data 배열상의 index
		}
		else
		{
			iIndex = m_krgSkill[m_iSkillCharged].iIndex;
			iSkillBookIndex = m_iSkillCharged;
		}

		kSkill = pSkillData[iIndex];

		if( eTNSklD_Unlimited == kSkill.iCastDuration ) return eTNRes_SkillPassiveSkill;
		if( 0 != kSkill.iReqWeapon )
		{
			short iIndex = get_WeaponIndex();
			if( !(kSkill.iReqWeapon & pItemData[iIndex].sItemType) ) return eTNRes_ReqWeapon;
		}
	}

	a_pMsg->bySkillLevel = kSkill.byLevel;

	// 해로운 스킬(normal skill 포함)이고 safety zone이면, 스킬을 발동시키지 않는다. - edited by spencer(04.12.17)
	if( !( kSkill.sSkillType & eTNSklT_Aid ) && ( eTNCell_SafetyZone & g_krgCell[TargetY][TargetX].usProperty ) ) return eTNRes_SafetyZone;

	CheckAffections( CurrentTime );

	
	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n[CastSkill] SkillID %d(lvl:%d)을 사용, target수:%d > ReadyTime: %u, Range: %d, AOE: %d, Now:%u \r\n", usSkillID, kSkill.byLevel, a_iTargetCount, kSkill.iAttackSpeed, kSkill.iRange, kSkill.iAOE, CurrentTime );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif


	/*
	// client 메모리핵
	// client의 메모리를 조작하여 빠르게 스킬을 시전하는 불법 user를 잡기 위한 code
	// <2005.12.08> 액티브 스킬의 경우 스킬 시전 속도가 굉장히 빠르다.(거의 delay가 없이 시전 즉시 발동되는 현상이 발생)
	// 보통 스킬 사용은 메시지를 두번 날린다.(echo, cast) 이 두 메시지 사이의 시간을 비교해서
	// 정해진 시간보다 월등히 작다면, 핵 사용일 경우가 있다. 그런데 현재 이런 현상이 발생한다. client쪽에 확인을 요청한 사항임.
	if( eTNMob_PC == m_eMobType )	
	{
		int iClientReadyTime = 0;
		int iInterval = 0;
		if( 0 < usSkillID )
		{
			bool bCheckInterval = true;
			int iWeaponIndex = get_WeaponIndex( eTNEqu_OneHandWeapon );
			if( (eTNWpn_Bow & pItemData[iWeaponIndex].sItemType) || (eTNWpn_Staff & pItemData[iWeaponIndex].sItemType) ) bCheckInterval = false;

			if( bCheckInterval )
			{// 
				iInterval = (int)(CurrentTime - m_kSkillCastRecord.uiTime); // 현재 시간에서 echo 시간을 뺀 time interval, 항상 양수이어야 한다.
				iClientReadyTime = kSkill.iAttackSpeed - iInterval - 100; // 음수가 나오면 정상이다. 오차범위:0.1초
				if( 0 <= iClientReadyTime ) ++m_kSkillCastRecord.iCount;
			}

			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "\t[Hack] bCheckInterval:%d, skillcasted:%d, attackSpeed:%d, interval:%d, Client-ReadyTime:%d, count:%d, echo skill(id:%d, time:%u), now:%u \r\n"
					, bCheckInterval, usSkillID, kSkill.iAttackSpeed, iInterval, iClientReadyTime
					, m_kSkillCastRecord.iCount
					, m_kSkillCastRecord.iSkill, m_kSkillCastRecord.uiTime
					, CurrentTime
					);
				WriteLog( chBuf, m_szLogFile );
			}
			#endif
		}

		if( g_irgSetting[eCnst_SkillCastIntervalHack] < m_kSkillCastRecord.iCount )
		{
			AddCrackError( m_iHandle, 100, CRACK_SKILLCASTSPEED_HACK );
			return eTNRes_HackUser;
		}
	}
	*/
	

	// 공격 speed 검사
	unsigned int uiGap = 0;

	bool bNormalAttackOrder = true;

	int iAttackSpeed = kSkill.iAttackSpeed;
	int iVarIndex = eTNVar_CastSpeed; // DD 공속이다.
	if( eTNSklT_EnergyOfSword & kSkill.sSkillType ) iVarIndex = eTNVar_AttackSpeed;
	iAttackSpeed -= Percent( iAttackSpeed, (m_krgVariation[iVarIndex][eVar_Equipment].iPPlus + m_krgVariation[iVarIndex][eVar_PassiveSkill].iPPlus + m_krgVariation[iVarIndex][eVar_Skill].iPPlus) ); 
	iAttackSpeed -= (m_krgVariation[iVarIndex][eVar_Equipment].iPlus + m_krgVariation[iVarIndex][eVar_PassiveSkill].iPlus + m_krgVariation[iVarIndex][eVar_Skill].iPlus );

	if( eTNSkl_NormalAttack == usSkillID )
	{	
		kSkill.iActivateTime = 0; // 400은 최고로 빠른 스피드 이다. 무기에서는 이 수치가 cool-down 값이다. 무기 종류에 따라 값이 틀려질 수 있다.
		// 최소 400 공속은 네트웍이나 기타 이유로 인해서 항상 지켜질 수 없다. 여유 있게 100정도 설정을 해놨다.
		if( 0 < m_kPrevSkill.sID ) // 스킬 후의 평타 사용 시, 시간 term을 짧게 해준다. 원래는 client가 정확히 시간을 맞춰서 보내야 하나, 현재 그렇지 않기 때문에 그냥 server측에서 빼주도록 처리했음.
		{
			if( CurrentTime < m_kPrevSkill.uiTime + 4000 ) iAttackSpeed = 400;
		}

		if( g_irgSetting[eCnst_SpeedMin] > iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMin];
		else if( g_irgSetting[eCnst_SpeedMax] < iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMax];		
		//iAttackSpeed = 0; // item에 의한 ready time은 모두 0이다. => edited by spencer(2004.12.17), 왜 이런 코드가 있었을까? 이것은 item의 최소 공속 delay를 무시하는 결과를 도출한다.
	}
	else
	{
		if( 0 > iAttackSpeed ) iAttackSpeed = 0;
	}
	

	if( !(eTNCPhase_DealDamage & kSkill.sCombatPhase) ) 
	{
		//if( 0 < a_pMsg->dwFireHitGapTime )
		//{
		//	#ifdef __DYNAMIC_LOG__
		//	{
		//		char chBuf[256] = { 0,0,0, };
		//		sprintf(chBuf, "\t[CastSkill] skill:%d, 데미지 공격이 아닌데 follow가 날라간 시간이 있다.Now:%d, FireHitGapTime: %u > \r\n", usSkillID, CurrentTime, a_pMsg->dwFireHitGapTime );
		//		WriteLog( chBuf, m_szLogFile );
		//	}
		//	#endif
		//}
		a_pMsg->dwFireHitGapTime = 0;
	}

	unsigned int uiAttackTime = CurrentTime - a_pMsg->dwFireHitGapTime; // attackTime : 실제 공격을 시작한 시간
	unsigned int uiPreviousAttackTime = m_kLastTime.uiAttacked; // 이전에 마지막으로 공격했던 시간
	if( uiAttackTime < uiPreviousAttackTime )
	{ // 거꾸로 hit된 경우, 유도미사일은 나중 공격보다 더 늦게 도착할 수 있다.		
		uiPreviousAttackTime = m_kLastTime.uiAttackedOld;
		bNormalAttackOrder = false;
	}
	
	uiGap = uiAttackTime - uiPreviousAttackTime; // 현재 공격 시간과 이전 공격 시간에 대한 차를 구하면 두 공격간의 시간 차를 구할 수 있다.
	//uiGap = CurrentTime - m_kLastTime.uiAttacked;

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[CastSkill] Attack Speed 검사> ReadyTime:%u, Gap(현공격시작시간-이전공격시간):%u, AttackTime:%u, Now:%u, FireHItGapTime:%u, PrevAtkTime:%u(LastAttacked:%u) \r\n"
			, iAttackSpeed, uiGap, uiAttackTime, CurrentTime, a_pMsg->dwFireHitGapTime, uiPreviousAttackTime, m_kLastTime.uiAttacked );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
	
	if( eTNMob_PC == m_eMobType )
	{
		// 스피드핵 방지 - 평균치 검사 routine
		if( eHack_MaxAttackTimeRecordCount > m_iAttackTimeRecordIndex)
		{
			m_uirgAttackTimeRecord[m_iAttackTimeRecordIndex] = CurrentTime;
			++m_iAttackTimeRecordIndex;
		}
		else
		{// 10번의 공격 시간이 기록되어 있다. 평균을 구해서 일정 시간보다 작다면 hacking으로 판단을 한다. 최고 빠른 속도가 400ms이므로 4000(400*10회, 4초) 아래 수치가 나올 수 없다.
			// 간단히 첫번째와 10번째 시간차를 구한다.

			int iTimeGap = m_uirgAttackTimeRecord[eHack_MaxAttackTimeRecordCount-1] - m_uirgAttackTimeRecord[0];
			m_iAttackTimeRecordIndex = 0;
			memset( m_uirgAttackTimeRecord, 0 , sizeof(m_uirgAttackTimeRecord) );

			//if( eHack_MaxAttackTimeGap > uiTimeGap )
			if( g_irgSetting[eCnst_AttackSpeedHack] > iTimeGap )				
			{// 해킹(or 시도) 이다. 기록을 남기고 연결을 끊어버린다.
				#ifdef __TN_TOP_LOG__
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[Attack Speed] Who : %s(Acc:%s, Hnd:%d,Mode:%d,FSM:%d), Gap:%u, When : %dmm%ddd %dhh%dmm%dss \r\n"
						, MOB.szName, pUser[m_iHandle].AccountName, m_iHandle, Mode, m_eFSM
						, iTimeGap
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						);
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_HackAttackSpeed] );
				}
				#endif

				AddCrackError( m_iHandle, 100, CRACK_ATTACK_SPEED_HACK );
			}
		}

		if( eTNSkl_NormalAttack == usSkillID ) uiGap = m_krgSkill[MAX_SKILL].uiCoolDownTime  + iAttackSpeed;
		else uiGap = m_krgSkill[iSkillBookIndex].uiCoolDownTime + iAttackSpeed;
		#ifdef __DYNAMIC_LOG__
		//if( eTNMob_PC == m_eMobType )
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t[CastSkill] Cooldown 검사: 남은 시간: %d, now: %u > uiGap: %d\r\n", uiGap- CurrentTime, CurrentTime, uiGap );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
		if( uiGap > CurrentTime ) // 시전 불가
		{
			return eTNRes_SkillNotCoolYet;
		}
	} // if( eTNMob_PC == m_eMobType )
	else // monster 인 경우
	{
		if( (unsigned int)iAttackSpeed > uiGap )
		{
			//#ifdef __DYNAMIC_LOG__
			//if( m_iDebugFlag )
			//{
			//	WriteLog( "\t[CastSkill] 공격속도 오류(이 오류만 여러번 반복되면 스피드핵일 가능성이 있음\r\n", m_szLogFile );
			//}
			//#endif

			return eTNRes_SkillNotActionYet; // 두 공격 간의 시간 차가 정의된 공격 시간보다 작으면, 정상적인 공격이 아니므로, 이 공격 packet은 skip을 해준다.
		}
	}

	
	int iAttackRange = kSkill.iRange;
	if( eTNSklR_WeaponBase == kSkill.iRange ) iAttackRange = pItemData[get_WeaponIndex()].iRange;
	if( TN_RANGE_DISTANT < iAttackRange )
	{
		iAttackRange += (m_krgVariation[eTNVar_RangeUp][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_Skill].iPlus ); // Range Up effect 처리
		iAttackRange -= (m_krgVariation[eTNVar_RangeDown][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeDown][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeDown][eVar_Skill].iPlus ); // Range Down effect 처리
	}
	
	int iBaseAttackRange = iAttackRange; // 보정 수치가 들어가기 전의 사거리, melee 무기의 경우 2이다.

	//iAttackRange += (m_krgVariation[eTNVar_RangeUp][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_Skill].iPlus ); // 모든 스킬 사용에 대한 range up effect 처리
	//if( eTNMob_PC == m_eMobType ) iAttackRange += eTNChr_DistCorrect;
	if( eTNMob_PC == m_eMobType )
	{
		iAttackRange += eTNChr_DistCorrect;
		//if( !(eTNVSAfn_DontMove & m_iAffections) ) iAttackRange += eTNChr_DistCorrect;
	}

	HS2D_COORD kCasterPos, kTargetPos;
	byte byBodyRadius = 0;
	get_Coord( kCasterPos );
	bool bIsInAttackRange = true;
	if( eTNSklA_Unit == kSkill.iAOE )		
	{
		if( 0 >= a_iTargetCount ) return eTNRes_InvalidTarget0; // unit 타겟인데, 타겟수가 0이라면, 에러
		byBodyRadius = m_byBodyRadius;
		if( eTNSklR_Self == kSkill.iRange ) // self & buffer skill일 경우
		{			
			if( m_iHandle != a_pMsg->krgTarget[0].snKeyID ) return eTNRes_InvalidTarget1; // 자기 자신인데, target이 자기 자신이 아니라면, 에러
			a_iTargetCount = 1;
		}
		else
		{
			if( 0 == kSkill.byPierceRate ) a_iTargetCount = 1;

			short sUnitID = a_pMsg->krgTarget[0].snKeyID;
			if( 0 >= sUnitID || MAX_MOB <= sUnitID ) return eTNRes_InvalidTarget2;
			pMob[sUnitID].get_Coord( kTargetPos );

			if( eZoneType_God == g_iZoneType ) 
			{
				if( TN_RANGE_DISTANT > iBaseAttackRange ) // melee 일 경우 높이 검사를 한다.
				{
					// Height 차를 계산한다. added by spencer(2005.1.25)
					int iHeight = g_krgCell[kCasterPos.y][kCasterPos.x].usHeight - g_krgCell[kTargetPos.y][kTargetPos.x].usHeight;
					if( 0 > iHeight ) iHeight = 0 - iHeight; // 음수일 경우 양수로 변경을 한다.	
					if( 300 < iHeight ) // 일정 높이 이상이고 melee공격이면, 불가
					{
						return eTNRes_OutofMeleeRange;
					}
				}
			}

			//if( eTNMob_PC == m_eMobType )
			//{
			//	if( !(eTNVSAfn_DontMove & m_iAffections) ) iAttackRange += eTNChr_DistCorrect;
			//}

			if( eTNMob_PC == pMob[sUnitID].m_eMobType )
			{				
				if( !(eTNVSAfn_DontMove & pMob[sUnitID].m_iAffections) ) iAttackRange += eTNChr_DistCorrect;
			}
			//if( sUnitID < MAX_USER ) // 캐릭터 이라면, 보정을 더 해준다.
			//	iAttackRange += (eTNChr_DistCorrect + eTNChr_DistCorrect);

			int iDist = CalDistance( kCasterPos, kTargetPos, byBodyRadius, pMob[sUnitID].get_BodyRadius() );
			if( iDist > iAttackRange )
			{
				#ifdef __DYNAMIC_LOG__
				if( m_iDebugFlag ) // 거리 오류를 하는 애들에 대한 log를 남긴다.
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] 거리오류> AOE:Unit, Distance: %d <= AttackRange: %d, Range: %d, caster(%s) 위치(%d,%d), taker(%s) 위치(%d,%d) - %dmm%ddd %dhh%dms%dmm \r\n"
						, iDist, iAttackRange, kSkill.iRange, MOB.szName, kCasterPos.x, kCasterPos.y, pMob[sUnitID].MOB.szName, kTargetPos.x, kTargetPos.y
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						);
					WriteLog( chBuf, m_szLogFile );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_HackDist] );
				}
				#endif //__TN_4TH_LOG__
				bIsInAttackRange = false; // 유효 거리 내에 위치하고 있지 않다면, ...
			}
			else
			{
				int iCheckPath = 1;
				if( eTNMob_NPC == m_eMobType )
				{
					if( eTNReact_Ignore & pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved6] ) iCheckPath = 0;
				}

				if( iCheckPath ) // 정상적이 이동을 하는 monster인 경우에만, ...
				{// 주신전에서만 처리를 한다.
					
					int iRes = IsPathCleared( kCasterPos.x, kCasterPos.y, kTargetPos.x, kTargetPos.y, iDist/*, iAttackRange*/ );
					if( iRes )
					{
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "\t[CastSkill] 높이 오류> Res:%d, height > caster:%d, target:%d, dist:%d \r\n"
								, iRes
								, g_krgCell[kCasterPos.y][kCasterPos.x].usHeight
								, g_krgCell[kTargetPos.y][kTargetPos.x].usHeight
								, iDist
								);
							WriteLog( chBuf, m_szLogFile );
						}
						#endif //__TN_4TH_LOG__

						return eTNRes_PathIsBlocked;
					}
				}
				#ifdef __DYNAMIC_LOG__
				if( m_iDebugFlag ) 
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] 거리> AOE:Unit, Distance: %d <= AttackRange: %d, Range: %d, caster 위치(%d,%d), taker 위치(%d,%d) \r\n", iDist, iAttackRange, kSkill.iRange, kCasterPos.x, kCasterPos.y, kTargetPos.x, kTargetPos.y );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif //__TN_4TH_LOG__
			}

			if( bIsInAttackRange )
			{				
				if( eTNSklT_MultipleStrike & kSkill.sSkillType )
				{
					a_iTargetCount = kSkill.byMaxPackCount;
					for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
					{
						if( i < a_iTargetCount ) a_pMsg->krgTarget[i].snKeyID = a_pMsg->krgTarget[0].snKeyID;
						else a_pMsg->krgTarget[i].snKeyID = 0;
					}

					kMulStrike = kSkill.krgEffect[1];
					kMulStrike.iParam1 = kMulStrike.iParam2 = 0;			
					kMulStrike2 = kSkill.krgEffect[2];
					kMulStrike2.iParam1 = kMulStrike2.iParam2 = 0;
				}
				else if( eTNSklT_Splash & kSkill.sSkillType )
				{
					a_iTargetCount = TN_MAX_TARGET_COUNT;
				}
			}
		}
	}
	else if( eTNSklA_Unit < kSkill.iAOE ) // 범위 스킬이라면, ...
	{
		if( eTNSklR_Self < kSkill.iRange )
		{			
			kTargetPos.x = a_pMsg->snMapX;
			kTargetPos.y = a_pMsg->snMapZ;

			if( CalDistance( kCasterPos, kTargetPos , m_byBodyRadius, 0 ) > iAttackRange )
			{ // caster와 목표지점(map)까지의 거리 오류
				#ifdef __DYNAMIC_LOG__
				//if( eTNMob_PC == m_eMobType )
				if( m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] 거리오류> AOE:범위, Distance: %d <= AttackRange: %d, Range: %d\r\n", CalDistance( kCasterPos, kTargetPos, m_byBodyRadius, 0 ), iAttackRange, kSkill.iRange );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif
				return eTNRes_OutOfRange;
			}
		}
		else // 자신을 중심으로 하는 범위 스킬일 경우, 목표지점과의 거리를 구할 필요가 없다.
		{ // iRange가 -1인 경우도 있다.
			kTargetPos = kCasterPos;
		}

		byBodyRadius = 0;
		iAttackRange = kSkill.iAOE + eTNChr_DistCorrect;

		for( int i = 0; i < a_iTargetCount; ++i )
		{
			if( (0 == kSkill.byFollow) && (0 < kSkill.iAOE) ) // follow가 없고 범위 공격인 것은 각각의 target에 대해서 거리 검사를 해준다.
			{
				short sUnitID = a_pMsg->krgTarget[i].snKeyID;
				if( IDX_MOB >= sUnitID || MAX_MOB <= sUnitID ) continue;

				HS2D_COORD kUnitPos;
				pMob[sUnitID].get_Coord( kUnitPos );

				if( CalDistance( kTargetPos, kUnitPos, 0, pMob[sUnitID].get_BodyRadius() ) > iAttackRange )
				{
					a_pMsg->krgTarget[i].snKeyID = 0;
					//bIsInAttackRange = false; // 유효 거리 내에 위치하고 있지 않다면, ...
				}

				#ifdef __TN_4TH_LOG__
				if( eTNMob_PC == m_eMobType )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] Distance: %d <= AOE %d, 성공:%d \r\n", CalDistance( kTargetPos, kUnitPos, byBodyRadius, pMob[sUnitID].get_BodyRadius() ), kSkill.iAOE, bIsInAttackRange );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif //__TN_4TH_LOG__
			}
		}
	}
	else if( eTNSklA_NA == kSkill.iAOE ) // target을 지정하지 않는 skill인 경우, 소환이 이에 속한다.
	{
		#ifdef __TN_2ND_LOG__
		{
			WriteLog( "[CastSkill] AOE: NA\r\n", m_szLogFile );
		}
		#endif //__TN_2ND_LOG__
	}


	//----------------------------------------------------------------------------
	// Targeting 검사
	// 공격자와 방어자들에 대한 mirror가 있어야 한다. 방어자는 다수일 수 있다.
	// 아래에는 공격자에 대한 것만 처리되어있다.
	// 추가로 방어자에 대한 mirroring을 처리해야 한다.
	//----------------------------------------------------------------------------
	int iAttacker = m_iHandle;
	if( eTNMob_NPC == pMob[iAttacker].m_eMobType ) // 굳이 이 조건을 비교할 필요는 없을 것이다.
	{// 소환수이라면, targeting시에 attacker는 주인으로 참조해서 검사한다.
		if( eTNAIO_HaveMaster & pMob[iAttacker].m_iAIOption )
			if( 0 < pMob[iAttacker].Leader && MAX_USER > pMob[iAttacker].Leader ) iAttacker = pMob[iAttacker].Leader;
	}

	int iAttClan = pMob[iAttacker].m_byClan;
	int iAttGuildID = pMob[iAttacker].MOB.nGuildID;

	int* pAllowedTarget = NULL;
	if( eZoneType_God == g_iZoneType )
	{
		if( eTNAT_Enemy == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets ) pAllowedTarget = (int*)&(g_irgEnemyTableRvR[iAttClan]);
        else if( (eTNAT_Friend == kSkill.iAllowedTargets) || (eTNAT_FriendCorpse == kSkill.iAllowedTargets) || (eTNAT_FriendNParty == kSkill.iAllowedTargets) ) pAllowedTarget = (int*)&g_irgFriendTableRvR[iAttClan];
    }
	else if( eZoneType_Guild == g_iZoneType )
	{		
		if( eTNMob_NPC == m_eMobType )
		{ // monster 이라면
			if( eTNAT_Enemy == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets ) pAllowedTarget = (int*)&(g_irgEnemyTableStrH[iAttClan]);
			else if( (eTNAT_Friend == kSkill.iAllowedTargets) || (eTNAT_FriendCorpse == kSkill.iAllowedTargets) || (eTNAT_FriendNParty == kSkill.iAllowedTargets) ) pAllowedTarget = (int*)&g_irgFriendTableStrH[iAttClan];
		}
    }
	else //if( eZoneType_Normal == g_iZoneType )
    {
        if( eTNAT_Enemy == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets )
        {            
            if( eTNBtn_PK & m_iButtonStatus ) pAllowedTarget = (int*)&g_irgEnemyTablePKOn[iAttClan];
            else pAllowedTarget = (int*)&g_irgEnemyTablePKOff[iAttClan];
        }            
        else if( (eTNAT_Friend == kSkill.iAllowedTargets) || (eTNAT_FriendCorpse == kSkill.iAllowedTargets) || (eTNAT_FriendNParty == kSkill.iAllowedTargets) ) pAllowedTarget = (int*)&g_irgFriendTable[iAttClan];
    }

	if( eTNAT_Friend == kSkill.iAllowedTargets )
	{		
		if( 3337 == usSkillID )
		{
			short sUnitID = a_pMsg->krgTarget[0].snKeyID;
			if( !IsParty( sUnitID ) ) return eTNRes_InvalidTarget9;
		}
	}

	if( eTNAT_FriendNParty == kSkill.iAllowedTargets )
	{
		short sUnitID = a_pMsg->krgTarget[0].snKeyID;
		if( NULL != pAllowedTarget )
		{
			int iFlag = pAllowedTarget[pMob[sUnitID].m_byClan];
			if( iFlag )
			{
				a_pMsg->krgTarget[0].snKeyID = m_iHandle;
				sUnitID = m_iHandle;
			}            
		}

		if( sUnitID == m_iHandle )  // 자기자신이 타겟인 경우, party로 돌려준다.
		{		
			int iTargetIndex = 1;

			int iLeader = Leader;
			if( 0 == Leader ) iLeader = m_iHandle;
			else
			{ // leader를 추가
				a_pMsg->krgTarget[iTargetIndex].snKeyID = Leader;
				++iTargetIndex;
			}
			
			for( int i = 0; i < MAX_PARTY; ++i )
			{
				short sPartyID = pMob[iLeader].m_irgParty[i];
				if( 0 >= sPartyID || MAX_USER <= sPartyID ) continue;
				if( pMob[sPartyID].IsDead() ) continue;
				int iDist = CalDistance( m_iHandle, sPartyID );
				if( 40 < iDist ) continue;

				if( m_iHandle != sPartyID )
				{
					a_pMsg->krgTarget[iTargetIndex].snKeyID = sPartyID;
					++iTargetIndex;
				}
			}

			//if( m_iHandle != Leader ) a_pMsg->krgTarget[iTargetIndex].snKeyID = Leader;

			a_iTargetCount = iTargetIndex;
		}
	}
	else if( eTNAT_Friend == kSkill.iAllowedTargets )
	{
		if( NULL != pAllowedTarget )
		{
			short sUnitID = a_pMsg->krgTarget[0].snKeyID;
			int iFlag = pAllowedTarget[pMob[sUnitID].m_byClan];
			if( iFlag )
			{
				a_pMsg->krgTarget[0].snKeyID = m_iHandle;
			}            
		}
	}

	//--------------------------------------------------------------------
	// 길드 연합 정보를 알아오는 부분
	//--------------------------------------------------------------------
	byte bAllied[TN_MAX_TARGET_COUNT] = {0,};

	if( eTNMob_PC == pMob[iAttacker].m_eMobType && g_iZoneType == eZoneType_Guild )
	{
		int nMyGuild = GetGuild(iAttGuildID);
		int nTarget = 0;
		int nTargetGuild = 0;
		for(int i=0; i<TN_MAX_TARGET_COUNT; i++)
		{
			nTarget = a_pMsg->krgTarget[i].snKeyID;
			if( nTarget>0 && nTarget<MAX_USER )			//	플레이어에 스킬시전시 
			{
				nTargetGuild = GetGuild(pMob[nTarget].MOB.nGuildID);
				if(strncmp(pGuild[nMyGuild].GUILD.AlliedGuildName1, pGuild[nTargetGuild].GUILD.GuildName, SZGUILD_LENGTH)==0)
					bAllied[i] = true;					//	연합길드설정
			}
		}
	}

	int iDefender = 0;
	int iDefClan = 0;
	int iDefGuildID = 0;

	int iInvalidTargetCount = 0;
	for( int i = 0; i < a_iTargetCount; ++i )
	{
		short sUnitID = a_pMsg->krgTarget[i].snKeyID;
		if( 0 >= sUnitID || MAX_MOB <= sUnitID )
		{ 
			++iInvalidTargetCount;
			a_pMsg->krgTarget[i].snKeyID = 0;
			continue; 
		}

		iDefender = sUnitID;
		if( eTNMob_NPC == pMob[iDefender].m_eMobType )
		{ // 소환수이라면, 주인을 defender로 설정해서 targeting 검사한다.
			if( eTNAIO_HaveMaster & pMob[iDefender].m_iAIOption )
				if( 0 < pMob[iDefender].Leader && MAX_USER > pMob[iDefender].Leader ) iDefender = pMob[iDefender].Leader;
		}

		iDefClan = pMob[iDefender].m_byClan;
		iDefGuildID = pMob[iDefender].MOB.nGuildID;

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			int iParty = 0;
			if( pMob[iAttacker].IsParty( iDefender ) ) iParty = 1;

			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\r\n**DEBUG**[CastSkill] Targeting > Attacker(%d(m_iHandle:%d), %d, %d), Defender(%d,(unit:%d), %d, %d), Party:%d \r\n"
				, iAttacker, m_iHandle, iAttClan, iAttGuildID, iDefender, sUnitID, iDefClan, iDefGuildID, iParty
				);
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //
		


		if( eTNClan_GM == pMob[iDefender].m_byClan )
		{ 
			++iInvalidTargetCount;
			a_pMsg->krgTarget[i].snKeyID = 0;
			continue; 
		}

		if( (eTNClan_NoTrimuritiy > pMob[sUnitID].m_byClan)	|| (eTNClan_Reserved < pMob[sUnitID].m_byClan ) )
		{
			char chBuf[256] = { 0,0,0, };
			if( MAX_USER > sUnitID )
			{// 기록을 남기고 튕긴다.
				char temp[256] = {0,};
				sprintf(chBuf, "\t[CastSkill] clan:%d, trimuriti:%d, handle:%d, name:%s, account:%s\r\n", pMob[sUnitID].m_byClan, pMob[sUnitID].MOB.byTrimuriti, sUnitID, pMob[sUnitID].MOB.szName, pUser[sUnitID].AccountName );
				SendClientMessage( sUnitID, g_pMessageStringTable[_DisconnectedToServer] );
				sprintf(temp, "clo CastSkill %s", chBuf);
				Log( temp, pUser[sUnitID].AccountName, pUser[sUnitID].IP );
				CloseUser( sUnitID );
				return eTNRes_Failed;
			}
			else
				sprintf(chBuf, "\t[CastSkill] clan:%d, trimuriti:%d, handle:%d, Tribe:%d, name:%s\r\n"
				, pMob[sUnitID].m_byClan, pMob[sUnitID].MOB.byTrimuriti, sUnitID, pMob[sUnitID].MOB.snTribe, pMob[sUnitID].MOB.szName );
			WriteLog( chBuf, ".\\Event\\[Log]InvalidClan.txt" );
			
			++iInvalidTargetCount;
			a_pMsg->krgTarget[i].snKeyID = 0;
			continue; 
		}

		if( pMob[sUnitID].IsDead() ) // if( MOB_EMPTY == pMob[sUnitID].Mode )
		{ 
			if( eTNAT_FriendCorpse == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets )
			{ // 나중에 시폭에 대한 문의 필요
			}
			else
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}  	        
		}


		if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
		{// 요새전에서는 동일 guild원은 target이 될 수 없다. 단, duel field가 아닐때이다.
			bool bIsInvalid = false;

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}

		if( eZoneType_Guild == g_iZoneType )
		{
			if( eTNMob_NPC == pMob[iDefender].m_eMobType )
			{ // monster 이라면
				if( eTNAT_Enemy == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets ) pAllowedTarget = (int*)&(g_irgEnemyTableStrH[iAttClan]);
				else if( (eTNAT_Friend == kSkill.iAllowedTargets) || (eTNAT_FriendCorpse == kSkill.iAllowedTargets) || (eTNAT_FriendNParty == kSkill.iAllowedTargets) ) pAllowedTarget = (int*)&g_irgFriendTableStrH[iAttClan];
			}
			else
			{ 
				if( eTNMob_PC == pMob[iAttacker].m_eMobType ) pAllowedTarget = NULL; // 공격자 수비자 모두 PC인 경우				
			}
		}

		if( (NULL != pAllowedTarget) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
		{
			int iNotChallengeMode = 1; // 이 상태가 일반 상태, 결투 모드이면 친구도 적이 된다.
			int iFlag = pAllowedTarget[iDefClan]; // 적인가? true이면 친구이고 false이면 적이다.

			if( eTNMob_PC == pMob[iAttacker].m_eMobType ) // caster(공격자)가 PC이라면, ...
			{
				if( iDefender == pUser[iAttacker].m_nChallenger ) iNotChallengeMode = 0; // 현재 결투 상태이다. 그럼 적이므로 공격가능
			}	

			if( iFlag && iNotChallengeMode )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}		
			    
		if( eTNAT_Enemy == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;
			        
			if( eTNMob_PC == pMob[iAttacker].m_eMobType ) // caster(공격자)가 PC이라면, ...
			{
				if( eTNMob_PC == pMob[iDefender].m_eMobType ) // 둘 다 PC라면 PK 제한을 확인해줘야한다.    		
				{// sUnitID와 iDefender는 동일하다.
					if( iDefender == iAttacker ) bIsInvalid = true; //return eTNRes_TargetSelf; // 자기자신에게 해로운 skill(item)을 쓸 경우, ...
					
					int iSiege = g_kSiege.get_Started();
					if( !iSiege ) // 공성전이 아니라면
					{
						if( ((g_irgSetting[eCnst_Restriction] > pMob[iAttacker].MOB.byLevel) || (g_irgSetting[eCnst_Restriction] > pMob[iDefender].MOB.byLevel)) 
							&& pUser[iAttacker].m_nChallenger!=iDefender ) bIsInvalid = true;
					}
					if( eTNVSAfn_ProtectFromPK & pMob[iAttacker].m_iAffections ) bIsInvalid = true;
					if( eTNVSAfn_ProtectFromPK & pMob[iDefender].m_iAffections ) bIsInvalid = true;

					if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
					{// 요새전에서는 동일 guild원은 target이 될 수 없다. 단, duel field가 아닐때이다.
						// 연합 길드원이면 target이 될 수 없다. 부분을 추가할 곳
						if( iDefGuildID == iAttGuildID ) bIsInvalid = true;	//	같은길드는 공격제외
						else if(bAllied[i]) bIsInvalid = true;									//	연합길드는 공격제외
					}

					// party원들을 공격할 수 없다.
					if( pMob[iAttacker].IsParty( iDefender ) ) bIsInvalid = true;					
				}
				else // defender가 npc 이라면, 소환수는 PC로 인식힌다.
				{
					if( eTNCell_DontAttackMonster & g_krgCell[TargetY][TargetX].usProperty ) bIsInvalid = true;

					// [ToDo] 아래는 확인을 해봐야 한다.
					//if( sUnitID  == m_iFamiliar ) bIsInvalid = true; // 내 familiar일 경우, ...
					//if( sUnitID  == m_iRetainer ) bIsInvalid = true; // 내 retainer일 경우, ...
					//if( eTNCls_Summoned == pMob[sUnitID].MOB.byClass1 )
					//{ // 내 파티의 faimiliar인지 확인을 해줘야 한다.
					//	int iParty = 0;
					//	int iLeader = Leader;
					//	if( 0 == iLeader ) iLeader = m_iHandle;
					//	for(int p = 0; p < MAX_PARTY; ++p )
					//	{
					//		iParty = pMob[iLeader].m_irgParty[p];
					//		if( 0 >= iParty || MAX_USER <= iParty ) continue;
					//		if( sUnitID == pMob[iParty].m_iFamiliar ) bIsInvalid = true; // 내 파티의 familiar이다.
					//		if( sUnitID == pMob[iParty].m_iRetainer ) bIsInvalid = true; // 내 파티의 familiar이다.
					//	}
					//}
				}
			} // if( eTNMob_PC == m_eMobType ) // caster(공격자)가 PC이라면, ...
			else // attacker가 monster이다.
			{
				if( eTNVSAfn_ProtectFromMonster & pMob[sUnitID].m_iAffections ) bIsInvalid = true;
				if( sUnitID == Leader ) bIsInvalid = true; // 소환물을 주인을 공격할 수 없다.
			}		
			
			if( !bIsInvalid )
			{	
				if( 0 >= pMob[sUnitID].TargetY || MAX_GRIDY <= pMob[sUnitID].TargetY ) bIsInvalid = true;
				if( 0 >= pMob[sUnitID].TargetX || MAX_GRIDX <= pMob[sUnitID].TargetX ) bIsInvalid = true;
				if( eTNCell_SafetyZone & g_krgCell[pMob[sUnitID].TargetY][pMob[sUnitID].TargetX].usProperty ) bIsInvalid = true;
				if( eTNImm_All == pMob[sUnitID].m_iImmunity ) bIsInvalid = true; // npc와 contact하기 위해서 뺐었는데, NPC contact message를 따로 만들었다.
				if( eTNVSAfn_Invulnerable & pMob[sUnitID].m_iAffections ) bIsInvalid = true;			    
			}
			
			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}  	        
		}
		else if( eTNAT_Friend == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;
			if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
			{// 요새전에서는 동일 guild원만 target이 될 수 있다. 단, duel field가 아닐때이다.
				// 연합 길드원도 target이 될 수 있다. 부분을 추가할 곳
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	같은길드나 협력길드원에게만 적용
			}

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}
		else if( eTNAT_FriendNParty == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;
			if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
			{// 요새전에서는 동일 guild원만 target이 될 수 있다. 단, duel field가 아닐때이다.
				// 연합 길드원도 target이 될 수 있다. 부분을 추가할 곳
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	같은길드나 협력길드원에게만 적용
			}

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}
		else if( eTNAT_Party == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;

			if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
			{// 요새전에서는 동일 guild원만 target이 될 수 있다. 단, duel field가 아닐때이다.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	같은길드나 협력길드원에게만 적용
			}

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}
		else if( eTNAT_FriendCorpse == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;

			if( pMob[sUnitID].IsAlive() ) bIsInvalid = true;
			if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
			{// 요새전에서는 동일 guild원만 target이 될 수 있다. 단, duel field가 아닐때이다.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	같은길드나 협력길드원에게만 적용
			}

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}
		else if( eTNAT_FriendExceptMe == kSkill.iAllowedTargets )
		{
			bool bIsInvalid = false;

			if( m_iHandle == sUnitID ) bIsInvalid = true;
			if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
			{// 요새전에서는 동일 guild원만 target이 될 수 있다. 단, duel field가 아닐때이다.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	같은길드나 협력길드원에게만 적용
			}

			if( bIsInvalid )
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}		
	}    

	if( (iInvalidTargetCount >= a_iTargetCount) && (eTNSklA_NA != kSkill.iAOE) && (0 < a_iTargetCount) )
	{
		m_iCastCount = 0;
		return eTNRes_InvalidTarget3;  // 타겟이 하나도 없다.
	}


/*
	if( eTNSkl_NormalAttack == usSkillID )
	{ // retainer에게 공격 명령을 넣어줘야 한다.
		if( (MAX_USER <= m_iRetainer) && (MAX_MOB > m_iRetainer) )
		{
			int iTarget = a_pMsg->krgTarget[0].snKeyID;
			pMob[m_iRetainer].MemorizeAttacker( 0, 1, iTarget );
		}
	}
*/	
	if( eTNMob_PC == m_eMobType )
	{// check cost		
		int iCostTPSavedByPercent = Percent( kSkill.kCost.iTP, (m_krgVariation[eTNVar_SaveTPCost][eVar_Skill].iPPlus + m_krgVariation[eTNVar_SaveTPCost][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_SaveTPCost][eVar_PassiveSkill].iPPlus) );
		if( 0 > iCostTPSavedByPercent ) iCostTPSavedByPercent = 0;
		int iCostTP = kSkill.kCost.iTP - iCostTPSavedByPercent - (m_krgVariation[eTNVar_SaveTPCost][eVar_Skill].iPlus + m_krgVariation[eTNVar_SaveTPCost][eVar_Equipment].iPlus + m_krgVariation[eTNVar_SaveTPCost][eVar_PassiveSkill].iPlus);
		if( 0 > iCostTP ) iCostTP = 0;
		if( MOB.nHP < (kSkill.kCost.iHP+1) ) return eTNRes_CostHP;
		if( MOB.nTP < iCostTP ) return eTNRes_CostTP;
		if( eItm_Arrow == kSkill.kCost.sItemID ) // 화살이라면 shield_slot에 장착되어 있다.
		{
			if( kSkill.kCost.sItemID != pItemData[MOB.Equip[eTNEqu_Shield].snIndex].sID ) return eTNRes_CostItem;
			--MOB.Equip[eTNEqu_Shield].byCount;
			a_pMsg->snPackCount = MOB.Equip[eTNEqu_Shield].byCount;
			if( 0 >= MOB.Equip[eTNEqu_Shield].byCount ) ZeroMemory(&(MOB.Equip[eTNEqu_Shield]), sizeof(STRUCT_ITEM));			
		}
		else if( 0 < kSkill.kCost.sItemID )
		{// 아이템을 inventory에서 찾아서 삭제를 해줘야 한다.
			int irgSlot[5] = { -1,-1,-1,-1,-1 };
			int iCount = 0;
			iCount = CheckItem( kSkill.kCost.sItemID, kSkill.kCost.byItemCount, irgSlot );
			if( iCount >= kSkill.kCost.byItemCount ) RemoveItem( kSkill.kCost.byItemCount, irgSlot );
			else return eTNRes_CostItem;
		}
		
		DecHP( kSkill.kCost.iHP );
		DecTP( iCostTP );

		// party원들에게 HP 상태를 표시
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
			// party원들 유무에 따라서 UpdateStatus 메시지 전달
		}
	}
	else // NPC
	{
		if( 0 < kSkill.kCost.iHP ) // monster의 경우도 HP를 cost를 소모할 수 있다.
		{
			if( MOB.nHP < kSkill.kCost.iHP ) return eTNRes_CostHP;
			DecHP( kSkill.kCost.iHP );
		}

		if( 0 < kSkill.sSpeak && eTNSpch_MaxCommentCount > kSkill.sSpeak ) // 말하기가 등록되어 있다면, ...
		{
			Speak( kSkill.sSpeak, a_pMsg->krgTarget[0].snKeyID, eTNAI_None );
		}
	}

	a_pMsg->snRes = (short)eTNRes_Succeeded; // 전투의 성공적인 수행
	TNDAMAGE kDamageSrc;
	if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
	{		    
        CalDamage( kDamageSrc, kSkill );

		if( eTNSkl_NormalAttack != usSkillID ) //스킬 공격이고
		{
			if( m_bDualWeapon ) // 이도류일 경우
			{		
				if( m_kDualHit.Random() ) // 왼손 무기를 사용할 확률 성공, m_krgMastery[eWpnMtryIdx_DualWpn].iParam1
				{
					kDamageSrc.irgBase[0] += m_krgDamage[eHnd_Left].irgBase[0];
					kDamageSrc.irgBase[1] += m_krgDamage[eHnd_Left].irgBase[1];
					kDamageSrc.irgPhy[0] += m_krgDamage[eHnd_Left].irgPhy[0];
					kDamageSrc.irgPhy[1] += m_krgDamage[eHnd_Left].irgPhy[1];
					kDamageSrc.irgPierce[0] += m_krgDamage[eHnd_Left].irgPierce[0];
					kDamageSrc.irgPierce[1] += m_krgDamage[eHnd_Left].irgPierce[1];
					kDamageSrc.irgFire[0] += m_krgDamage[eHnd_Left].irgFire[0];
					kDamageSrc.irgFire[1] += m_krgDamage[eHnd_Left].irgFire[1];
					kDamageSrc.irgCold[0] += m_krgDamage[eHnd_Left].irgCold[0];
					kDamageSrc.irgCold[1] += m_krgDamage[eHnd_Left].irgCold[1];
					kDamageSrc.irgLightning[0] += m_krgDamage[eHnd_Left].irgLightning[0];
					kDamageSrc.irgLightning[1] += m_krgDamage[eHnd_Left].irgLightning[1];
					kDamageSrc.irgPoison[0] += m_krgDamage[eHnd_Left].irgPoison[0];
					kDamageSrc.irgPoison[1] += m_krgDamage[eHnd_Left].irgPoison[1];
				}
			}
		}
		else // 일반 공격
		{
			int iFixedDamage2 = m_krgVariation[eTNVar_FixedDamage2][eVar_PassiveSkill].iPlus	+ m_krgVariation[eTNVar_FixedDamage2][eVar_Equipment].iPlus;
			kDamageSrc.irgPierce[0] += iFixedDamage2;
			kDamageSrc.irgPierce[1] += iFixedDamage2;
		}
	
		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\r\n**DEBUG**[CastSkill] Damage() 10 > Base(%d,%d), Phy(%d,%d), Pierce(%d,%d), Fire(%d,%d), Cold(%d,%d), Lightning(%d,%d), Poison(%d,%d) \r\n"
				, kDamageSrc.irgBase[0], kDamageSrc.irgBase[1]
				, kDamageSrc.irgPhy[0], kDamageSrc.irgPhy[1]
				, kDamageSrc.irgPierce[0], kDamageSrc.irgPierce[1]
				, kDamageSrc.irgFire[0], kDamageSrc.irgFire[1]
				, kDamageSrc.irgCold[0], kDamageSrc.irgCold[1]
				, kDamageSrc.irgLightning[0], kDamageSrc.irgLightning[1]
				, kDamageSrc.irgPoison[0], kDamageSrc.irgPoison[1]
				);
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //
		

        if( eTNCPhase_CastInstant1 & kSkill.sCombatPhase ) CastInstant1( kDamageSrc, kSkill );
	}

	__int64 iCasterAffections = m_iAffections;
	for( int i = 0; i < a_iTargetCount; ++i )
	{
		short sUnitID = a_pMsg->krgTarget[i].snKeyID;
		if( IDX_MOB >= sUnitID || MAX_MOB <= sUnitID ) continue;

		if( eTNAT_Enemy == kSkill.iAllowedTargets )
		{
			if( pMob[sUnitID].IsDead() )
			{
				a_pMsg->krgTarget[i].byRes = eCmbt_Dodge;
				a_pMsg->krgTarget[i].iDamage = 0;
				a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;//0일 것이다.
				a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
				continue;
			}

			if( !(eTNCPhase_StartAction & kSkill.sCombatPhase) ) pMob[sUnitID].OnUnderAttack( m_iHandle );

			// ----------------------------------------------------
			// 선제 공격, 선공자,  보라돌이
			// ----------------------------------------------------
			if( eZoneType_Normal == g_iZoneType )
			{
				int iAttacker = m_iHandle;
				if( eTNAIO_HaveMaster & m_iAIOption )
				{
					if( 0 < Leader && MAX_USER > Leader ) iAttacker = Leader;
				}
				
				bool bCheckFirstStrike = false;
				if( eTNMob_PC == pMob[iAttacker].m_eMobType ) bCheckFirstStrike = true; // caster(공격자)가 PC이라면, ...
			
				if( bCheckFirstStrike )
				{ //
					int iDefender = sUnitID;
					if( eTNAIO_HaveMaster & pMob[sUnitID].m_iAIOption )					
						if( 0 < pMob[sUnitID].Leader && MAX_USER > pMob[sUnitID].Leader ) iDefender = pMob[sUnitID].Leader;

					if( eTNMob_PC == pMob[iDefender].m_eMobType ) // 둘 다 PC라면 PK 제한을 확인해줘야한다.    		
					{
						if( 0 == pMob[iAttacker].MOB.snKarma &&  0 == pMob[iDefender].MOB.snKarma ) //둘 다 살인자가 아닌 경우에만, 선제 공격 처리를 해준다.
						{
							int iUnderSiege = g_kSiege.get_Started();
							if( !iUnderSiege )
							{ // 공성전이 아니라면, ...
								if( (0 == pMob[iDefender].m_uiPkDurTime) && (pUser[iAttacker].m_nChallenger != iDefender) ) // 주신전이 아니고, 방어자가 선제 공격자가 아닌 경우
								{
									pMob[iAttacker].m_iPKDefender = iDefender;
									pMob[iAttacker].m_iAffections = pMob[iAttacker].m_iAffections | eTNVSAfn_PKAttacker;
									if( 0 == pMob[iAttacker].m_uiPkDurTime ) BroadcastUpdateStatusMsg();
									pMob[iAttacker].m_uiPkDurTime = CurrentTime + g_irgSetting[eCnst_FirstStrikeDur];					
								}
							} // if( !iUnderSiege )
						} // if( 0 == pMob[iAttacker].MOB.snKarma &&  0 == pMob[iDefender].MOB.snKarma ) 
					} // if( eTNMob_PC == pMob[iDefender].m_eMobType ) // 둘 다 PC라면 PK 제한을 확인해줘야한다.  
				} // if( bCheckFirstStrike )
			}
		}

		bool bCheckDodgeSpeed = true;
		if( eTNSklT_MultipleStrike & kSkill.sSkillType )
		{
			if( 0 < i ) bCheckDodgeSpeed = false;
		}

		if( bIsInAttackRange ) // 사거리 이내에 있다면, ...
		{
			byte bySuccessRate = kSkill.bySuccessRate;
			
			if( 0 == bySuccessRate ) iRes = pMob[sUnitID].OnDefense( m_kCombatFactors.iAttackRate, m_iHandle, bCheckDodgeSpeed );
			else
			{
				bySuccessRate += (byte)m_krgVariation[eTNVar_SuccessRate][eVar_PassiveSkill].iPlus;
				byte nDice =(byte)(rand() % 100);
				if( nDice > bySuccessRate ) iRes = eCmbt_Dodge;
			}

			if( eCmbt_Dodge == iRes )
			{
				a_pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge;
				a_pMsg->krgTarget[i].iDamage = 0;
				a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
				a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;

				Think( eTNAI_Miss, sUnitID );
				pMob[sUnitID].Think( eTNAI_Dodge, m_iHandle );

				#ifdef __TN_3RD_LOG__
				if( eTNMob_PC == m_eMobType )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "[CastSkill] 방어자(%d, %s)가 회피하였슴. \r\n", a_pMsg->krgTarget[i].snKeyID, pMob[a_pMsg->krgTarget[i].snKeyID].MOB.szName );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif // __TN_3RD_LOG__
				continue;
			}

			// 공격 성공일 경우			
			int iDamage = 0;
			if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
			{
				TNDAMAGE kDamage = kDamageSrc;
				if( eTNSkl_NormalAttack != usSkillID ) iRes = eCmbt_Normal;
				else
				{
					if( eCmbt_Critical == iRes )
					{
						double dPercent = 200; // default는 200%
						if( 0 < m_krgVariation[eTNVar_CriticalBonus][eVar_PassiveSkill].iPPlus ) dPercent += m_krgVariation[eTNVar_CriticalBonus][eVar_PassiveSkill].iPPlus;

						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "**DEBUG**[CastSkill] CriticalHit 10 > Percent:%d(%d), Damage(%d~%d, %d~%d, %d~%d, %d~%d, %d~%d, %d~%d, %d~%d)  \r\n"
								, dPercent, m_krgVariation[eTNVar_CriticalBonus][eVar_PassiveSkill].iPPlus
								, kDamage.irgBase[0], kDamage.irgBase[1]
								, kDamage.irgPhy[0], kDamage.irgPhy[1]
								, kDamage.irgPierce[0], kDamage.irgPierce[1]
								, kDamage.irgFire[0], kDamage.irgFire[1]
								, kDamage.irgCold[0], kDamage.irgCold[1]
								, kDamage.irgLightning[0], kDamage.irgLightning[1]
								, kDamage.irgPoison[0], kDamage.irgPoison[1]
								);
							WriteLog( chBuf, m_szLogFile );
						}
						#endif

						kDamage.irgBase[0] = Percent( kDamage.irgBase[0], dPercent );
						kDamage.irgBase[1] = Percent( kDamage.irgBase[1], dPercent );
						kDamage.irgPhy[0] = Percent( kDamage.irgPhy[0], dPercent );
						kDamage.irgPhy[1] = Percent( kDamage.irgPhy[1], dPercent );
						//kDamage.irgPierce[0] = Percent( kDamage.irgPierce[0], dPercent );
						//kDamage.irgPierce[1] = Percent( kDamage.irgPierce[1], dPercent );
						// critical 시, 속성 제련 값도 2배로 한다.
						kDamage.irgFire[0] = Percent( kDamage.irgFire[0], dPercent );
						kDamage.irgFire[1] = Percent( kDamage.irgFire[1], dPercent );
						kDamage.irgCold[0] = Percent( kDamage.irgCold[0], dPercent );
						kDamage.irgCold[1] = Percent( kDamage.irgCold[1], dPercent );
						kDamage.irgLightning[0] = Percent( kDamage.irgLightning[0], dPercent );
						kDamage.irgLightning[1] = Percent( kDamage.irgLightning[1], dPercent );
						kDamage.irgPoison[0] = Percent( kDamage.irgPoison[0], dPercent );
						kDamage.irgPoison[1] = Percent( kDamage.irgPoison[1], dPercent );

						/*
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "**DEBUG**[CastSkill] CriticalHit 20 > Percent:%d(%d), Damage(%d~%d, %d~%d, %d~%d, %d~%d, %d~%d, %d~%d, %d~%d)  \r\n"
								, dPercent, m_krgVariation[eTNVar_CriticalBonus][eVar_PassiveSkill].iPPlus
								, kDamage.irgBase[0], kDamage.irgBase[1]
								, kDamage.irgPhy[0], kDamage.irgPhy[1]
								, kDamage.irgPierce[0], kDamage.irgPierce[1]
								, kDamage.irgFire[0], kDamage.irgFire[1]
								, kDamage.irgCold[0], kDamage.irgCold[1]
								, kDamage.irgLightning[0], kDamage.irgLightning[1]
								, kDamage.irgPoison[0], kDamage.irgPoison[1]
								);
							WriteLog( chBuf, m_szLogFile );
						}
						#endif
						*/
					}
				}
                if( eTNCPhase_CastInstant2 & kSkill.sCombatPhase ) CastInstant2( kDamage, kSkill, iSkillBookIndex, sUnitID, iRes );

                int iPercent = 100;
                if( eTNSklT_Splash & kSkill.sSkillType ) if( 0 < i ) iPercent = 50;
                iDamage = DealDamage( kDamage, sUnitID, iPercent );			

				if( eTNVSAfn_Weakness & pMob[sUnitID].m_iAffections )
				{
					if( eTNSkl_NormalAttack != usSkillID )
					{
						iRes = eCmbt_Critical;
						TNDAMAGE kBonusDamage;
						int iBonusDamage = iDamage;
						if( 0 > iBonusDamage ) iBonusDamage = 0;
						else
						{
							kBonusDamage.irgPierce[0] = iBonusDamage;
							pMob[sUnitID].OnTakeDamage( kBonusDamage, m_iHandle );
							iDamage += kBonusDamage.iSum;
						}
					}
				}

				if( 0 == i ) UpdateEquipDur( iDamage, 1 ); // 공격 1회당 내구도 1씩 떨어진다.

				if( eTNCPhase_CastInstant3 & kSkill.sCombatPhase ) CastInstant3( kSkill, pMob[sUnitID].m_iLastDamage ); // steal HP/MP 관련

				// 흡입 버프가 있을 시에 이곳에 추가를 해줘야 할 것이다.
				// if( eTNVSAfn_StealHP & m_iAffections ) // HP 흡수
				// if( eTNVSAfn_StealMP & m_iAffections ) // MP 흡수

				//if( eTNCPhase_Taunt & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant0( kSkill, pMob[sUnitID].m_iLastDamage, m_iHandle );
			}// if( eTNCPhase_DealDamage & kSkill.sCombatPhase )

			
			if( !( kSkill.sSkillType & eTNSklT_Aid ) ) // 해로운 스킬인 경우,
			{// 이로운 스킬이면 다음의 effect가 꺼지면 안된다.
				pMob[sUnitID].TurnOffAffection( eTNAfn_Sleep );				
				pMob[sUnitID].TurnOffAffection( eTNAfn_Invisible );
			}

			if( eTNCPhase_OnTakeInstant1 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant1( m_iHandle, kSkill ); // 시체관련
			if( eTNCPhase_OnTakeInstant2 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant2( m_iHandle, kSkill, iSkillBookIndex ); // alive 관련			
			if( eTNCPhase_OnAffect & kSkill.sCombatPhase )
			{
				int iBufferResult = pMob[sUnitID].OnTakeAffections( kSkill, iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
				if( (0 >= iDamage) && ( eTNRes_Failed == iBufferResult ) ) iRes = eCmbt_Dodge;
			}
			if( eTNCPhase_AffectSelf & kSkill.sCombatPhase ) OnTakeAffections( kSkill, iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
			if( eTNCPhase_StartAction & kSkill.sCombatPhase )
			{
				int iResult = StartAction( m_iHandle, kSkill, sUnitID );
				if( iResult )
				{
					iRes = eCmbt_Dodge;
					iDamage = 0;
				}
			}
			   
			if( eTNSklT_MultipleStrike & kSkill.sSkillType )
			{// func값이 1일 경우에는 effect #1의 param값이 누적된다.
				if( 1 == kSkill.krgEffect[0].kFunc.iData )
				{
					kMulStrike.iParam1 += kSkill.krgEffect[1].iParam1;
					kMulStrike.iParam2 += kSkill.krgEffect[1].iParam2;
					kMulStrike2.iParam1 += kSkill.krgEffect[2].iParam1;
					kMulStrike2.iParam2 += kSkill.krgEffect[2].iParam2;
				}
			}

			a_pMsg->krgTarget[i].byRes = (byte)iRes;
            a_pMsg->krgTarget[i].iDamage = iDamage;
            a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;                                                                           
            a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;

			if( eCmbt_Normal == iRes || eCmbt_Critical == iRes ) // 공격이 성공일 때만, 수행된다. 
			{ // 여기가 공격 성공이 아닐 때가 있는가?
				if( 0 < usSkillID )
				{
					m_kPrevSkill.sID = usSkillID;
					m_kPrevSkill.byLevel = kSkill.byLevel;
					m_kPrevSkill.uiTime = CurrentTime;
					m_kPrevSkill.sTarget = sUnitID;
				}

				if( eCmbt_Critical == iRes )
				{
					Think( eTNAI_HitEnemy, sUnitID );
					pMob[sUnitID].Think( eTNAI_BeHitted, m_iHandle );
				}

				if( eWaitAct_TownPortal  == pMob[sUnitID].m_kWaitAction.iAction ) { pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; m_snMovePortal = 0; } // 대기하던 action이 없어진다.
				if(m_kWaitAction.iAction == eWaitAct_ZonePortal)
				{	char pch[256] = {0,};
					if(0<sUnitID && sUnitID<MAX_USER)
						sprintf(pch, "Char:%s pustica is stopped by Char:%s's castskill", pMob[sUnitID].MOB.szName, MOB.szName);
					else
						sprintf(pch, "Char:%s pustica is stopped by Monster:%s's castskill", pMob[sUnitID].MOB.szName, MOB.szName);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
				//if( eWaitAct_TownPortal2 == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; // 대기하던 action이 없어진다.
				//if( eWaitAct_TownPortal3 == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; // 대기하던 action이 없어진다.
				if( eWaitAct_SummonParty == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None;

				if( m_iHandle != sUnitID ) // 시전자와 
				{
					TNDAMAGE kDamageReflected;
					int iReflectDamage = pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_PassiveSkill].iPPlus;
					if( 0 > iReflectDamage ) iReflectDamage = 0;
					if( g_irgSetting[eCnst_ReflectMax] < iReflectDamage ) iReflectDamage = g_irgSetting[eCnst_ReflectMax];

					kDamageReflected.irgPierce[0] = Percent( iDamage, iReflectDamage );

					// 2005.4.25, 신규 reflect damage 기능 추가, added by spencer
					kDamageReflected.irgPierce[0] += pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_PassiveSkill].iPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPlus;

					if( 0 < kDamageReflected.irgPierce[0] )
					{
						OnTakeDamage( kDamageReflected, sUnitID );
	/*
						int iEmptyTargetSlot = i+1;
						for(; iEmptyTargetSlot < TN_MAX_TARGET_COUNT; ++iEmptyTargetSlot )
							if( IDX_MOB >= a_pMsg->krgTarget[iEmptyTargetSlot].snKeyID || MAX_MOB <= a_pMsg->krgTarget[iEmptyTargetSlot].snKeyID ) break;			
						if( TN_MAX_TARGET_COUNT > iEmptyTargetSlot )
						{					
							++iTargetCountAdded;
							a_pMsg->krgTarget[iEmptyTargetSlot].snKeyID = m_iHandle;
							a_pMsg->krgTarget[iEmptyTargetSlot].iDamage = kDamageReflected.irgPierce[0];
							a_pMsg->krgTarget[iEmptyTargetSlot].iHP = MOB.nHP;
							a_pMsg->krgTarget[iEmptyTargetSlot].iAffection = m_iAffections;
						}					
	*/
					}
				}
			}
		}
		else // 사거리 바깥에 있다. 회피로 처리
		{
			a_pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge;
			a_pMsg->krgTarget[i].iDamage = 0;
			a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
			a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
		}

		#ifdef __DYNAMIC_LOG__
		if( m_iDebugFlag )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[CastSkill] 스킬/아이템(%d) 사용, %d회 공격결과:%d(0,1:성공, 2:실패), 사거리이내:%d -> 방어자(%d, %s)가 Damage:%d를 받아서 HP가 %d가 되었음. Affections:%d \r\n"
				, a_pMsg->snSkillID, i+1, a_pMsg->krgTarget[i].byRes, bIsInAttackRange, a_pMsg->krgTarget[i].snKeyID, pMob[a_pMsg->krgTarget[i].snKeyID].MOB.szName, a_pMsg->krgTarget[i].iDamage, a_pMsg->krgTarget[i].iHP, a_pMsg->krgTarget[i].iAffection );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}

	if( eTNSklT_MultipleStrike & kSkill.sSkillType )
	{// func값이 1일 경우에는 effect #1의 param값이 누적된다.
		if( (1 == kSkill.krgEffect[0].kFunc.iData) && (eTNCPhase_OnAffect & kSkill.sCombatPhase) )
		{
			short sUnitID = a_pMsg->krgTarget[0].snKeyID;
			pMob[sUnitID].AddEffect( kMulStrike, m_iHandle, m_iHandle );
			pMob[sUnitID].AddEffect( kMulStrike2, m_iHandle, m_iHandle );
		}
	}

	if( (eTNSkl_NormalAttack==usSkillID) && m_bDualWeapon ) //일반 공격이고 이도류일 경우
	{
		if( m_kDualHit.Random() ) // 왼손 무기를 사용할 확률 성공, m_krgMastery[eWpnMtryIdx_DualWpn].iParam1
		{
			memset( &(a_pMsg->krgTarget[1]), 0, sizeof(a_pMsg->krgTarget[1]) );
			a_pMsg->krgTarget[1].snKeyID = a_pMsg->krgTarget[0].snKeyID;
			a_iTargetCount = 2;
			UseLeftWeapon( a_pMsg );
		}	
	}

	// 몬스터 경우 보통은 activateTime이 1000 이다. 그러므로 연속적으로 바로 다른 action이 불가하다.
	// PC 경우, skill인 경우는 activateTime에 ApplyTime값(attack point이후의 시간이 들어간다. attack point 위치가 스킬마다 각각 틀리다.)이 들어간다.
	// item은 평타일 경우인데.. 이때에도 attack point 이후의 나머지 시간이 들어간다.
	m_uiActionLock = uiAttackTime + kSkill.iActivateTime; 
	if( bNormalAttackOrder )
	{
		m_kLastTime.uiAttackedOld = m_kLastTime.uiAttacked;
		m_kLastTime.uiAttacked = m_uiActionLock;
	}

	--m_iCastCount;
	if( TRIBE_DEVA != MOB.snTribe && TRIBE_GARUDA != MOB.snTribe ) m_kLastTime.uiCombat = CurrentTime + eDly_TPRecv;

	if( eTNSkl_NormalAttack == usSkillID )
	{
		m_krgSkill[MAX_SKILL].uiCoolDownTime = m_uiActionLock; //+ kSkill.iCoolDownTime;
		a_pMsg->dwCoolDownTime = m_krgSkill[MAX_SKILL].uiCoolDownTime;
	}
	else
	{
		unsigned int uiCoolDownTimeChanged = kSkill.iCoolDownTime;
		unsigned int uiCoolDownCorrect = (unsigned int)(kSkill.iCoolDownTime * 0.1);

		if( eTNMob_PC == m_eMobType )
		{
			if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe )
			{
				if( 100 < MOB.sMind )
				{
					double dMind = MOB.sMind;
					if( 500 < dMind ) dMind = 500;
					double dCoolDownTime = kSkill.iCoolDownTime;
					
					uiCoolDownTimeChanged = kSkill.iCoolDownTime - (int)(dCoolDownTime * ( (dMind - 100 ) / 800 ) );
				}
				#ifdef __DYNAMIC_LOG__
				if( m_iDebugFlag )
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[CastSkill] 스킬/아이템(%d) 사용, 원래 쿨다운:%u, 변경된쿨다운:%u(정신:%d) \r\n"
						, a_pMsg->snSkillID, kSkill.iCoolDownTime, uiCoolDownTimeChanged, MOB.sMind );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif
			}
		}

		uiCoolDownTimeChanged = uiCoolDownTimeChanged - uiCoolDownCorrect;
		if( 0 > uiCoolDownTimeChanged ) uiCoolDownTimeChanged = 0;
		m_krgSkill[iSkillBookIndex].uiCoolDownTime = m_uiActionLock + uiCoolDownTimeChanged;
		a_pMsg->dwCoolDownTime = m_krgSkill[iSkillBookIndex].uiCoolDownTime;
	}

	a_pMsg->dwDurationTime = CurrentTime + kSkill.iCastDuration;
	
	BroadcastCastSkill( a_pMsg, a_iTargetCount );
	if( eTNCPhase_AffectSelf & kSkill.sCombatPhase ) NotifyUpdateUIMsg();
	if( iCasterAffections != m_iAffections ) BroadcastUpdateStatusMsg();
	if( 0 < m_iHandle && MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendMessage(); // PC일 경우, ...

	for( int i = 0; i < a_iTargetCount; ++i )
	{
		short sUnitID = a_pMsg->krgTarget[i].snKeyID;
		if( IDX_MOB > sUnitID || MAX_MOB <= sUnitID ) continue;

		if( TRIBE_DEVA != pMob[sUnitID].MOB.snTribe && TRIBE_GARUDA != pMob[sUnitID].MOB.snTribe ) pMob[sUnitID].m_kLastTime.uiCombat = CurrentTime + eDly_TPRecv;
		if( eTNCPhase_StatusChanged & kSkill.sCombatPhase ) // eTNCPhase_OnTakeInstant2 + eTNCPhase_OnAffect
		{
			//pMob[sUnitID].NotifyUpdateStatusMsg(); // cast_unit/area_skill 메시지에 내용이 중복 포함되어 있을 것이다.
			pMob[sUnitID].BroadcastUpdateStatusMsg();
			pMob[sUnitID].NotifyUpdateUIMsg();
		}
		if( eTNSklT_ChangeTP & kSkill.sSkillType )
		{
			pMob[sUnitID].NotifyUpdateStatusMsg(); // TP 변경에 대한 것!!
		}

		if( 0 < sUnitID && MAX_USER > sUnitID ) pUser[sUnitID].cSock.SendMessage();
		//if( (0 < a_pMsg->krgTarget[i].iDamage) && pMob[sUnitID].IsDead() && (0==pMob[sUnitID].m_iPranaDec) )
		if( (0 < a_pMsg->krgTarget[i].iDamage) && pMob[sUnitID].IsDead() && (0>=a_pMsg->krgTarget[i].iHP) )
		{
			Think( eTNAI_KillEnemy, sUnitID );

			pMob[sUnitID].OnKilled( m_iHandle, 1 );
			if( eTNMob_PC == m_eMobType)
			{
				//--m_iEnemyCount;
				//if( 0 > m_iEnemyCount ) m_iEnemyCount = 0;
			}			
		}		
	}

	//if( eTNSklA_NA == kSkill.iAOE ) CastOnly( kSkill ); // 몬스터skill에서 사용한다.
	if( eTNCPhase_CastOnly & kSkill.sCombatPhase ) CastOnly( kSkill );

	if( IsDead() ) OnKilled( a_pMsg->krgTarget[0].snKeyID, 0 );


	return eTNRes_Succeeded;
}



// Pierce damage에 대한 고찰이 필요하다.
void CMob::CalDamage( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iHand )
{
	a_kDamage = a_kSkill.kDamage;

	// 아래쪽 로직이 조금 더 잘 코딩될 수 있을 것 같은데, 변화에 대한 위험성으로 수정하지 않음.
	if( eTNMob_PC == m_eMobType )
	{
		if( eTNSklT_EnergyOfSword & a_kSkill.sSkillType ) a_kDamage = m_krgDamage[a_iHand]; // 무기 기반한 skill
		else // DD skill 인 경우
		{
			int iConstant = 250; // 2.5
			if( 0 < a_kDamage.irgPhy[0] )
			{
				a_kDamage.irgPhy[0] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgPhy[0]*3 +500)/1000 + m_kChakra.sMind-12;
				a_kDamage.irgPhy[1] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgPhy[1]*3 +500)/1000 + m_kChakra.sMind-12;
			}
			if( 0 < a_kDamage.irgFire[0] )
			{
				a_kDamage.irgFire[0] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgFire[0]*3 +500)/1000 + m_kChakra.sMind-12;
				a_kDamage.irgFire[1] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgFire[1]*3 +500)/1000 + m_kChakra.sMind-12;
			}
			if( 0 < a_kDamage.irgCold[0] )
			{
				a_kDamage.irgCold[0] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgCold[0]*3 +500)/1000 + m_kChakra.sMind-12;
				a_kDamage.irgCold[1] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgCold[1]*3 +500)/1000 + m_kChakra.sMind-12;
			}
			if( 0 < a_kDamage.irgLightning[0] )
			{
				a_kDamage.irgLightning[0] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgLightning[0]*3 +500)/1000 + m_kChakra.sMind-12;
				a_kDamage.irgLightning[1] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgLightning[1]*3 +500)/1000 + m_kChakra.sMind-12;
			}
			if( 0 < a_kDamage.irgPoison[0] )
			{
				a_kDamage.irgPoison[0] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgPoison[0]*3 +500)/1000 + m_kChakra.sMind-12;
				a_kDamage.irgPoison[1] = ((m_kChakra.sMind*iConstant/100+m_kChakra.sNerves+100)*a_kDamage.irgPoison[1]*3 +500)/1000 + m_kChakra.sMind-12;
			}
		}
	}

	if( !(eTNSklT_EnergyOfSword & a_kSkill.sSkillType) ) // 무기 기반한 공격이 아닌 경우(DD, DOT, ...)
	{
		if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe ) // 지팡이 적용
		{
			int iWeaponIndex = get_WeaponIndex();
			if( 0 > iWeaponIndex || MAX_ITEM_DATA <= iWeaponIndex ) iWeaponIndex = 0;
			if( eTNWpn_Staff & pItemData[iWeaponIndex].sItemType )
			{	
				short sNerves = m_kChakra.sNerves;
				if( g_irgSetting[eCnst_StaffMaxNerves] < sNerves ) sNerves = g_irgSetting[eCnst_StaffMaxNerves];
				short sLevelRest = 5*MOB.byLevel + 25;
				if( sLevelRest < sNerves ) sNerves = sLevelRest;
				int iMinDmg = (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgPhy[0]*sNerves)/10000 + m_krgWeaponDamage[eHnd_Right].irgPhy[0];
				int iMaxDmg = (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgPhy[1]*sNerves)/10000 + m_krgWeaponDamage[eHnd_Right].irgPhy[1];
				if( 0 < a_kDamage.irgPhy[0] )
				{
					a_kDamage.irgPhy[0] += iMinDmg;
					a_kDamage.irgPhy[1] += iMaxDmg;
				}
	/*
				if( 0 < a_kDamage.irgPierce[0] )
				{ 
					a_kDamage.irgPierce[0] += iMinDmg;				
					a_kDamage.irgPierce[1] += iMaxDmg;
				}
	*/
				if( 0 < a_kDamage.irgFire[0] )
				{
					a_kDamage.irgFire[0] += iMinDmg;
					a_kDamage.irgFire[1] += iMaxDmg;
					if( a_kSkill.sSkillType & eTNSklT_Fire )
					{
						a_kDamage.irgFire[0] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgFire[0] * sNerves )/10000;
						a_kDamage.irgFire[1] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgFire[1] * sNerves )/10000;
					}
				}
				if( 0 < a_kDamage.irgCold[0] )
				{
					a_kDamage.irgCold[0] += iMinDmg;
					a_kDamage.irgCold[1] += iMaxDmg; 
					if( a_kSkill.sSkillType & eTNSklT_Cold )
					{
						a_kDamage.irgCold[0] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgCold[0] * sNerves )/10000;
						a_kDamage.irgCold[1] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgCold[1] * sNerves )/10000;
					}
				}
				if( 0 < a_kDamage.irgLightning[0] )
				{
					a_kDamage.irgLightning[0] += iMinDmg;
					a_kDamage.irgLightning[1] += iMaxDmg; 
					if( a_kSkill.sSkillType & eTNSklT_Lightning )
					{
						a_kDamage.irgLightning[0] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgLightning[0] * sNerves )/10000;
						a_kDamage.irgLightning[1] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgLightning[1] * sNerves )/10000;
					}
				}
				if( 0 < a_kDamage.irgPoison[0] )
				{
					a_kDamage.irgPoison[0] += iMinDmg;
					a_kDamage.irgPoison[1] += iMaxDmg; 
					if( a_kSkill.sSkillType & eTNSklT_Poison )
					{
						a_kDamage.irgPoison[0] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgPoison[0] * sNerves )/10000;
						a_kDamage.irgPoison[1] += (g_irgSetting[eCnst_StaffCorrect] * m_krgWeaponDamage[eHnd_Right].irgPoison[1] * sNerves )/10000;
					}
				}
			}
		} //if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe ) // 지팡이 적용


		//--------------------------------------   % 증감   -------------------------------------
		if( 0 < a_kDamage.irgPhy[0] )
		{
			a_kDamage.irgPhy[0] += Percent( a_kDamage.irgPhy[0], (m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MinDamage][eVar_PassiveSkill].iPPlus ) );
			a_kDamage.irgPhy[1] += Percent( a_kDamage.irgPhy[1], (m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_MaxDamage][eVar_PassiveSkill].iPPlus ) );

			/*
			int iDamageBonusForNextAttack = m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPPlus; //+ m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_PassiveSkill].iPPlus;
			if( 0 < iDamageBonusForNextAttack )
			{
				a_kDamage.irgPhy[0] += Percent( a_kDamage.irgPhy[0], iDamageBonusForNextAttack );
				a_kDamage.irgPhy[1] += Percent( a_kDamage.irgPhy[1], iDamageBonusForNextAttack );
				m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPPlus = 0;
			}
			*/
		}
		if( a_kDamage.irgFire[0] )
		{
			int iPPlus = m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPPlus;
			a_kDamage.irgFire[0] += Percent( a_kDamage.irgFire[0], iPPlus );
			a_kDamage.irgFire[1] += Percent( a_kDamage.irgFire[1], iPPlus );
		}
		if( a_kDamage.irgCold[0] )
		{
			int iPPlus = m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPPlus;
			a_kDamage.irgCold[0] += Percent( a_kDamage.irgCold[0], iPPlus );
			a_kDamage.irgCold[1] += Percent( a_kDamage.irgCold[1], iPPlus );
		}
		if( a_kDamage.irgLightning[0] )
		{
			int iPPlus = m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPPlus;
			a_kDamage.irgLightning[0] += Percent( a_kDamage.irgLightning[0], iPPlus );
			a_kDamage.irgLightning[1] += Percent( a_kDamage.irgLightning[1], iPPlus );
		}
		//if( a_kDamage.irgPoison[0] )
		{
			int iPPlus = m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPPlus + m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPPlus;
			a_kDamage.irgPoison[0] += Percent( a_kDamage.irgPoison[0], iPPlus );
			a_kDamage.irgPoison[1] += Percent( a_kDamage.irgPoison[1], iPPlus );
		}


		//----------------------------------   +/- 증감   -----------------------------------------
		if( 0 < a_kDamage.irgPhy[0] )
		{	
			a_kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_Equipment].iPlus;
			a_kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_Equipment].iPlus;
			a_kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgPhy[0] += m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPlus;
			a_kDamage.irgPhy[1] += m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPlus;
		}
		if( 0 < a_kDamage.irgFire[0] )
		{
			a_kDamage.irgFire[0] += m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPlus;
			a_kDamage.irgFire[1] += m_krgVariation[eTNVar_FireDamage][eVar_Equipment].iPlus;
			a_kDamage.irgFire[0] += m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgFire[1] += m_krgVariation[eTNVar_FireDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgFire[0] += (m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_FireDamage][eVar_Potion].iPlus*/);
			a_kDamage.irgFire[1] += (m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_FireDamage][eVar_Potion].iPlus*/);
		}
		if( 0 < a_kDamage.irgCold[0] )
		{
			a_kDamage.irgCold[0] += m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPlus;
			a_kDamage.irgCold[1] += m_krgVariation[eTNVar_ColdDamage][eVar_Equipment].iPlus;
			a_kDamage.irgCold[0] += m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgCold[1] += m_krgVariation[eTNVar_ColdDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgCold[0] += (m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_ColdDamage][eVar_Potion].iPlus*/);
			a_kDamage.irgCold[1] += (m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_ColdDamage][eVar_Potion].iPlus*/);
		}
		if( 0 < a_kDamage.irgLightning[0] )
		{
			a_kDamage.irgLightning[0] += m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPlus;
			a_kDamage.irgLightning[1] += m_krgVariation[eTNVar_LightningDamage][eVar_Equipment].iPlus;
			a_kDamage.irgLightning[0] += m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgLightning[1] += m_krgVariation[eTNVar_LightningDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgLightning[0] += (m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_LightningDamage][eVar_Potion].iPlus*/);
			a_kDamage.irgLightning[1] += (m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_LightningDamage][eVar_Potion].iPlus*/);
		}
		//if( 0 < a_kDamage.irgPoison[0] )
		{
			a_kDamage.irgPoison[0] += m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPlus;
			a_kDamage.irgPoison[1] += m_krgVariation[eTNVar_PoisonDamage][eVar_Equipment].iPlus;
			a_kDamage.irgPoison[0] += m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgPoison[1] += m_krgVariation[eTNVar_PoisonDamage][eVar_PassiveSkill].iPlus;
			a_kDamage.irgPoison[0] += (m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_PoisonDamage][eVar_Potion].iPlus*/);
			a_kDamage.irgPoison[1] += (m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPlus /*+ m_krgVariation[eTNVar_PoisonDamage][eVar_Potion].iPlus*/);
		}
	} //if( !(eTNSklT_EnergyOfSword & a_kSkill.sSkillType) ) // 물리 공격이 아닌 경우, ...

	int iDamageBonusForNextAttack = m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPPlus; //+ m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Equipment].iPPlus + m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_PassiveSkill].iPPlus;
	if( 0 < iDamageBonusForNextAttack )
	{
		a_kDamage.irgPhy[0] += Percent( a_kDamage.irgPhy[0], iDamageBonusForNextAttack );
		a_kDamage.irgPhy[1] += Percent( a_kDamage.irgPhy[1], iDamageBonusForNextAttack );
		m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPPlus = 0;
	}

	iDamageBonusForNextAttack = m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPlus; //+ m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Equipment].iPlus + m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_PassiveSkill].iPlus;
	if( 0 < iDamageBonusForNextAttack )
	{
		a_kDamage.irgPhy[0] += iDamageBonusForNextAttack;
		a_kDamage.irgPhy[1] += iDamageBonusForNextAttack;
		m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPlus = 0;
	}

	int iFixedDamage = m_krgVariation[eTNVar_FixedDamage][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_FixedDamage][eVar_Skill].iPlus + m_krgVariation[eTNVar_FixedDamage][eVar_Equipment].iPlus;
	a_kDamage.irgPierce[0] += iFixedDamage;
	a_kDamage.irgPierce[1] += iFixedDamage;
}


// combatphase : 1 (4도 같이 포함되어 있어야 한다.)
void CMob::CastInstant1( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill )
{
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_DamagePlus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgPhy[0] )
				{
					a_kDamage.irgPhy[0] += a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgPhy[1] += a_kSkill.krgEffect[i].iParam2;				
				}
/*
				if( 0 < a_kDamage.irgPierce[0] ) 
				{
					a_kDamage.irgPierce[0] += a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgPierce[1] += a_kSkill.krgEffect[i].iParam2;				
				}
*/
			}
			else
			{
				a_kDamage.irgPhy[0] += Percent( a_kDamage.irgPhy[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgPhy[1] += Percent( a_kDamage.irgPhy[1] , a_kSkill.krgEffect[i].iParam2 );
				//a_kDamage.irgPierce[0] += Percent( a_kDamage.irgPierce[0], a_kSkill.krgEffect[i].iParam1 );
				//a_kDamage.irgPierce[1] += Percent( a_kDamage.irgPierce[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_DamageMinus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgPhy[0] )
				{
					a_kDamage.irgPhy[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgPhy[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgPhy[0] ) a_kDamage.irgPhy[0] = 0;
				if( 0 > a_kDamage.irgPhy[1] ) a_kDamage.irgPhy[1] = 0;
				/*
				if( 0 < a_kDamage.irgPierce[0] )
				{
					a_kDamage.irgPierce[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgPierce[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgPierce[0] ) a_kDamage.irgPierce[0] = 0;
				if( 0 > a_kDamage.irgPierce[1] ) a_kDamage.irgPierce[1] = 0;
				*/
			}
			else
			{
				a_kDamage.irgPhy[0] -= Percent(a_kDamage.irgPhy[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgPhy[1] -= Percent(a_kDamage.irgPhy[1], a_kSkill.krgEffect[i].iParam2 );
				//a_kDamage.irgPierce[0] -= Percent(a_kDamage.irgPierce[0], a_kSkill.krgEffect[i].iParam1 );
				//a_kDamage.irgPierce[1] -= Percent(a_kDamage.irgPierce[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_FireDamagePlus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgFire[0] )
				{	
					a_kDamage.irgFire[0] += a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgFire[1] += a_kSkill.krgEffect[i].iParam2;
				}
			}
			else
			{
				a_kDamage.irgFire[0] += Percent(a_kDamage.irgFire[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgFire[1] += Percent(a_kDamage.irgFire[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_FireDamageMinus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgFire[0] )
				{	
					a_kDamage.irgFire[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgFire[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgFire[0] ) a_kDamage.irgFire[0] = 0;
				if( 0 > a_kDamage.irgFire[1] ) a_kDamage.irgFire[1] = 0;
			}
			else
			{
				a_kDamage.irgFire[0] -= Percent(a_kDamage.irgFire[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgFire[1] -= Percent(a_kDamage.irgFire[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_ColdDamagePlus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgCold[0] )
				{
					a_kDamage.irgCold[0] += a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgCold[1] += a_kSkill.krgEffect[i].iParam2;
				}
			}
			else
			{
				a_kDamage.irgCold[0] += Percent(a_kDamage.irgCold[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgCold[1] += Percent(a_kDamage.irgCold[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_ColdDamageMinus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgCold[0] )
				{
					a_kDamage.irgCold[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgCold[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgCold[0] ) a_kDamage.irgCold[0] = 0;
				if( 0 > a_kDamage.irgCold[1] ) a_kDamage.irgCold[1] = 0;
			}
			else
			{
				a_kDamage.irgCold[0] -= Percent(a_kDamage.irgCold[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgCold[1] -= Percent(a_kDamage.irgCold[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_LightningDamagePlus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgLightning[0] )
				{
					a_kDamage.irgLightning[0] += a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgLightning[1] += a_kSkill.krgEffect[i].iParam2;
				}
			}
			else
			{
				a_kDamage.irgLightning[0] += Percent(a_kDamage.irgLightning[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgLightning[1] += Percent(a_kDamage.irgLightning[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_LightningDamageMinus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgLightning[0] )
				{
					a_kDamage.irgLightning[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgLightning[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgLightning[0] ) a_kDamage.irgLightning[0] = 0;
				if( 0 > a_kDamage.irgLightning[1] ) a_kDamage.irgLightning[1] = 0;
			}
			else
			{
				a_kDamage.irgLightning[0] -= Percent(a_kDamage.irgLightning[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgLightning[1] -= Percent(a_kDamage.irgLightning[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_PoisonDamagePlus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgPoison[0] ) a_kDamage.irgPoison[0] += a_kSkill.krgEffect[i].iParam1;
				if( 0 < a_kDamage.irgPoison[1] ) a_kDamage.irgPoison[1] += a_kSkill.krgEffect[i].iParam2;
			}
			else
			{
				a_kDamage.irgPoison[0] += Percent(a_kDamage.irgPoison[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgPoison[1] += Percent(a_kDamage.irgPoison[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_PoisonDamageMinus :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
			{
				if( 0 < a_kDamage.irgPoison[0] )
				{
					a_kDamage.irgPoison[0] -= a_kSkill.krgEffect[i].iParam1;
					a_kDamage.irgPoison[1] -= a_kSkill.krgEffect[i].iParam2;
				}
				if( 0 > a_kDamage.irgPoison[0] ) a_kDamage.irgPoison[0] = 0;
				if( 0 > a_kDamage.irgPoison[1] ) a_kDamage.irgPoison[1] = 0;
			}
			else
			{
				a_kDamage.irgPoison[0] -= Percent(a_kDamage.irgPoison[0], a_kSkill.krgEffect[i].iParam1 );
				a_kDamage.irgPoison[1] -= Percent(a_kDamage.irgPoison[1], a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		}
	} // for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )  
}


// combatphase : 2(4도 같이 포함되어 있어야 한다.)
void CMob::CastInstant2( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iTarget, int& a_iCriticalHit )
{
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_MultipleStrike : // instant1
			{//물리 damage만 증감이 있는가?				
				a_kDamage.irgPhy[0] = Percent( a_kDamage.irgPhy[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPhy[1] = Percent( a_kDamage.irgPhy[1], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgFire[0] = Percent( a_kDamage.irgFire[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgFire[1] = Percent( a_kDamage.irgFire[1], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgCold[0] = Percent( a_kDamage.irgCold[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgCold[1] = Percent( a_kDamage.irgCold[1], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgLightning[0] = Percent( a_kDamage.irgLightning[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgLightning[1] = Percent( a_kDamage.irgLightning[1], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPoison[0] = Percent( a_kDamage.irgPoison[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPoison[1] = Percent( a_kDamage.irgPoison[1], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPierce[0] = Percent( a_kDamage.irgPierce[0], a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPierce[1] = Percent( a_kDamage.irgPierce[1], a_kSkill.krgEffect[i].iParam2 );
				//a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_CriticalStrike :  // instant1
			{ //물리 damage만 증감이 있는가?
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit이 결정됐다면, 추가 critical hit은 없다.

				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon의 특수 능력일 때, ...
				{
					int iDice = rand() % 100;
					if( iDice >= a_kSkill.krgEffect[i].iParam1 ) break;
				}
				else 
					if( !m_krgSkill[a_iSkillBookIndex].kDeck.Random() )  break;

				if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
				{
					a_kDamage.irgPhy[0] += Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPhy[1] += Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
				}
				else
				{
					a_kDamage.irgPhy[0] += a_kSkill.krgEffect[i].iParam2;
					a_kDamage.irgPhy[1] += a_kSkill.krgEffect[i].iParam2;
				}
				a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_PierceStrike :
			{
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit이 결정됐다면, 추가 critical hit은 없다.
				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon의 특수 능력일 때, ...
				{
					int iDice = rand() % 100;
					if( iDice >= a_kSkill.krgEffect[i].iParam1 ) break;
				}
				else
                    if( !m_krgSkill[a_iSkillBookIndex].kDeck.Random() ) break;

				//if( a_kSkill.krgEffect[i].iParam1 < (rand() % 100) ) break;
				int iMinDamage = Percent( a_kDamage.irgPhy[0], a_kSkill.krgEffect[i].iParam2 );
				int iMaxDamage = Percent( a_kDamage.irgPhy[1], a_kSkill.krgEffect[i].iParam2 );
				
				a_kDamage.irgPierce[0] += iMinDamage;
				a_kDamage.irgPierce[1] += iMaxDamage;
				a_kDamage.irgPhy[0] -= iMinDamage;
				if( 0 > a_kDamage.irgPhy[0] ) a_kDamage.irgPhy[0] = 0;
				a_kDamage.irgPhy[1] -= iMaxDamage;
				if( 0 > a_kDamage.irgPhy[1] ) a_kDamage.irgPhy[1] = 0;
				a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_PierceStrike2 :
			{
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit이 결정됐다면, 추가 critical hit은 없다.

				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon의 특수 능력일 때, ...
				{
					int iDice = rand() % 100;
					if( iDice >= a_kSkill.krgEffect[i].iParam1 ) break;
				}
				else
                    if( !m_krgSkill[a_iSkillBookIndex].kDeck.Random() ) break;

				a_kDamage.iDecDef = a_kSkill.krgEffect[i].iParam2; // 방어력이 iDecDef(%)만큼 줄어든 후에 damage가 계산된다.
				//a_iCriticalHit = eCmbt_Critical;
			}
			break;	
		case eTNAfn_HPDown :
			{
				if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) break;
				if( eTNImm_HPDown & pMob[a_iTarget].m_iImmunity ) a_kDamage.irgPierce[0] = a_kDamage.irgPierce[1] = 0;
				else a_kDamage.irgPierce[0] = a_kDamage.irgPierce[1] = Percent( pMob[a_iTarget].MOB.nHP, a_kSkill.krgEffect[i].iParam1 );
				//a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_TPBurn :
			{
				if( 0 >= a_iTarget || MAX_USER <= a_iTarget ) break; // monster의 경우 skip
				int iBurnTP = Percent( pMob[a_iTarget].m_iMaxTP, a_kSkill.krgEffect[i].iParam1 );
				if( iBurnTP >= pMob[a_iTarget].MOB.nTP ) iBurnTP = pMob[a_iTarget].MOB.nTP;
				pMob[a_iTarget].DecTP( iBurnTP );

				// party원들에게 TP 상태를 표시
				if( a_iTarget>0 && a_iTarget<MAX_USER)
				{	S_SCP_RESP_UPDATE_PARTY sm; sm.wType=SCP_RESP_UPDATE_PARTY;
					sm.wPDULength=sizeof(sm)-sizeof(HEADER);
					sm.Party.nCurHP=pMob[a_iTarget].MOB.nHP; sm.Party.nCurTP=pMob[a_iTarget].MOB.nTP;
					sm.Party.byLevel=pMob[a_iTarget].MOB.byLevel; sm.Party.nMaxHP=pMob[a_iTarget].m_iMaxHP;
					sm.Party.nMaxTP=pMob[a_iTarget].m_iMaxTP; sm.Party.nID=a_iTarget;
					sm.Party.nAffections=pMob[a_iTarget].m_iAffections;
					strncpy(sm.Party.Name,pMob[a_iTarget].MOB.szName,SZNAME_LENGTH);

					int nLeader=0;
					if(pMob[a_iTarget].Leader==0) nLeader=a_iTarget;
					else nLeader=pMob[a_iTarget].Leader;

					SendPartyMessage(nLeader, (MSG_STANDARD*)&sm);
					// party원들 유무에 따라서 UpdateStatus 메시지 전달
				}

				//pMob[a_iTarget].MOB.nTP -= iBurnTP;
				//if( 0 > pMob[a_iTarget].MOB.nTP ) pMob[a_iTarget].MOB.nTP = 0;
				int iBurnDamage = Percent( iBurnTP, a_kSkill.krgEffect[i].iParam2 );
				a_kDamage.irgPierce[0] += iBurnDamage;
				a_kDamage.irgPierce[1] += iBurnDamage;
				//a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_BonusEffect : 
			{
				if( 0 >= m_kPrevSkill.sID ) break;
				if( m_kPrevSkill.sID != a_kSkill.krgEffect[i].kFunc.iData ) break;
				if( CurrentTime > m_kPrevSkill.uiTime + 4000 ) break;
				if( m_kPrevSkill.sTarget != a_iTarget ) break;

				int iDice = rand() % 100;
				if( iDice < a_kSkill.krgEffect[i].iParam1 ) // 확률
				{
					TNEFFECT kEffect;
					kEffect.iID = a_kSkill.krgEffect[i].iParam2; // effect ID
					kEffect.iDuration = 4000;
					kEffect.kFunc.iData = 0;
					kEffect.iParam1 = 0;
					kEffect.iParam2 = 0;
					AddEffect( kEffect, m_iHandle, m_iHandle );
				}
			}
			break;
		case eTNAfn_BonusDamage : // 연계기로, pierce damage type을 보너스로 더해준다.
			{
				if( 0 >= m_kPrevSkill.sID ) break;
				if( m_kPrevSkill.sID != a_kSkill.krgEffect[i].kFunc.iData ) break;
				if( CurrentTime > m_kPrevSkill.uiTime + 4000 ) break;
				if( m_kPrevSkill.sTarget != a_iTarget ) break;

				int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1 * m_kPrevSkill.byLevel );
				int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 * m_kPrevSkill.byLevel );
				a_kDamage.irgPierce[0] += iMinDamage;
				a_kDamage.irgPierce[1] += iMaxDamage;
				a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_BonusDamage2 : // 연계기로, 일반 물리 damage type을 보너스로 더해준다.
			{
				if( 0 >= m_kPrevSkill.sID ) break;
				if( m_kPrevSkill.sID != a_kSkill.krgEffect[i].kFunc.iData ) break;
				if( CurrentTime > m_kPrevSkill.uiTime + 4000 ) break;
				if( m_kPrevSkill.sTarget != a_iTarget ) break;

				int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1 * m_kPrevSkill.byLevel );
				int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 * m_kPrevSkill.byLevel );
				a_kDamage.irgPhy[0] += iMinDamage;
				a_kDamage.irgPhy[1] += iMaxDamage;
				a_iCriticalHit = eCmbt_Critical;
			}
			break;
		case eTNAfn_BonusDamage3 : // 상대방이 이상상태에 걸려 있다면, 보너스를 더해준다.
			{
				if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) break; 
				if( a_kSkill.krgEffect[i].kFunc.iData & pMob[a_iTarget].m_iAffections )
				{
					int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1);
					int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPierce[0] += iMinDamage;
					a_kDamage.irgPierce[1] += iMaxDamage;
					a_iCriticalHit = eCmbt_Critical;
				}				
			}
			break;
		case eTNAfn_BonusDamage7 : // 상대방이 이상상태일때, 상수 보너스를 더해준다.
			{
				if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) break; 
				if( a_kSkill.krgEffect[i].kFunc.iData & pMob[a_iTarget].m_iAffections )
				{
					int iMinDamage = PlayDice( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2);
					a_kDamage.irgPierce[0] += iMinDamage;
					a_kDamage.irgPierce[1] += iMinDamage;
					a_iCriticalHit = eCmbt_Critical;
				}				
			}
			break;
		case eTNAfn_BonusDamage4 : // 상대방 회피율이 일정 수치보다 작다면, 보너스를 더해준다.
			{
				if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) break; 
				if( a_kSkill.krgEffect[i].kFunc.iData > pMob[a_iTarget].m_kCombatFactors.iDodgeRate )
				{
					int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1);
					int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPierce[0] += iMinDamage;
					a_kDamage.irgPierce[1] += iMaxDamage;					
					a_iCriticalHit = eCmbt_Critical;
				}				
			}
			break;
		case eTNAfn_BonusDamage5 :// 특정 무기를 착용하고 있으면 
			{
				int iWeaponIndex = get_WeaponIndex( eHnd_Right );
				if( 0 > iWeaponIndex || MAX_ITEM_DATA <= iWeaponIndex ) break;

				if( a_kSkill.krgEffect[i].kFunc.iData & pItemData[iWeaponIndex].sItemType )
				{
					int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1);
					int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPierce[0] += iMinDamage;
					a_kDamage.irgPierce[1] += iMaxDamage;
					a_iCriticalHit = eCmbt_Critical;
				}	
			}
			break;
		case eTNAfn_BonusDamage6 :
			{ // 자신의 바로 이전 상태가 어떤 상태일때?
				if( a_kSkill.krgEffect[i].kFunc.iData & m_iPrevAffections )
				{
					int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam1);
					int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPierce[0] += iMinDamage;
					a_kDamage.irgPierce[1] += iMaxDamage;
					a_iCriticalHit = eCmbt_Critical;
				}				
			}
			break;
		case etnAfn_BonusDamage8 : // pierce damage 보너스를 더해준다.
			{
				int iMinDamage = PlayDice( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2);
				a_kDamage.irgPierce[0] += iMinDamage;
				a_kDamage.irgPierce[1] += iMinDamage;
			}
			break;
		case eTNAfn_SlayerItem :
			{
				if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
				{ // monster family, reserved0 field를 대체적으로 사용
					if( a_kSkill.krgEffect[i].iParam1 != pMob[a_iTarget].m_iFamily ) break;
					a_kDamage.irgPhy[0] = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPhy[1] = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
				}
				else
				{ // armor type
					if( a_kSkill.krgEffect[i].iParam1 != pMob[a_iTarget].get_ArmorType() ) break;
					a_kDamage.irgPhy[0] = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam2 );
					a_kDamage.irgPhy[1] = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );
				}
				//a_iCriticalHit = eCmbt_Critical;
			}
			break;
		}
	} // for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )  
}


// combatphase : 4
int CMob::DealDamage( TNDAMAGE& a_kDamage, int a_iTarget, int a_iPercent )
{
	if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) return 0;

    TNDAMAGE kDamage;
	//kDamage.irgBase[0] = (short)PlayDice( a_kDamage.irgBase[0], a_kDamage.irgBase[1] );
    kDamage.irgPhy[0] = PlayDice( a_kDamage.irgPhy[0], a_kDamage.irgPhy[1] );
	kDamage.irgPierce[0] = PlayDice( a_kDamage.irgPierce[0], a_kDamage.irgPierce[1] );
    kDamage.irgFire[0] = PlayDice( a_kDamage.irgFire[0], a_kDamage.irgFire[1] );
    kDamage.irgCold[0] = PlayDice( a_kDamage.irgCold[0], a_kDamage.irgCold[1] );
    kDamage.irgLightning[0] = PlayDice( a_kDamage.irgLightning[0], a_kDamage.irgLightning[1] );
    kDamage.irgPoison[0] = PlayDice( a_kDamage.irgPoison[0], a_kDamage.irgPoison[1] );    
    if( 0 <= a_iPercent && 100 > a_iPercent )
    {
    	kDamage.irgPhy[0] = Percent(kDamage.irgPhy[0], a_iPercent );
		kDamage.irgPierce[0] = Percent(kDamage.irgPierce[0], a_iPercent );
    	kDamage.irgFire[0] = Percent(kDamage.irgFire[0], a_iPercent );
    	kDamage.irgCold[0] = Percent(kDamage.irgCold[0], a_iPercent );
    	kDamage.irgLightning[0] = Percent(kDamage.irgLightning[0], a_iPercent );
    	kDamage.irgPoison[0] = Percent(kDamage.irgPoison[0], a_iPercent );    	
    }

	if( 0 < a_kDamage.iAttackType && eAAC_AttackTypeCount > a_kDamage.iAttackType )
	{
		byte byDefenderArmorType = pMob[a_iTarget].get_ArmorType();
		if( 0 < byDefenderArmorType && eAAC_ArmorTypeCount > byDefenderArmorType ) 
			kDamage.irgPhy[0] = Percent( kDamage.irgPhy[0], g_srgAttackTypeVSArmorTypeChart[byDefenderArmorType][a_kDamage.iAttackType] );
	}

    kDamage.iSum = kDamage.irgPhy[0] + kDamage.irgFire[0] + kDamage.irgCold[0] + kDamage.irgLightning[0] + kDamage.irgPoison[0] + kDamage.irgPierce[0];    
    if( 0 >= kDamage.iSum ) return 0;
	kDamage.iDecDef = a_kDamage.iDecDef;

    short sLevelGap = pMob[a_iTarget].MOB.byLevel - MOB.byLevel + eCon_MaxGap; // 방어자 - 공격자 + eCon_MaxGap
    if( 0 > sLevelGap ) sLevelGap = 0;
    if( eCon_MaxGapCount <= sLevelGap ) sLevelGap = eCon_LastIndex;
	int iHP = pMob[a_iTarget].MOB.nHP;
	int iRemainingHP = 0;
    iRemainingHP = pMob[a_iTarget].OnTakeDamage( kDamage, m_iHandle, sLevelGap );
	kDamage.iSum = iHP - iRemainingHP;
    
    //UpdateEquipDur( kDamage.iSum, 1 ); // 무기를 사용했을 때만, ...
    pMob[a_iTarget].UpdateEquipDur( kDamage.iSum );// 방어자 장비의 내구성을 줄인다.
    
	// taunt/detaunt effect를 여기에서 처리해도 되나 성능상 하나의 phase로 뺀다.

    return kDamage.iSum;
}


// combatphase : 8(4도 같이 포함되어 있어야 한다.) or 256
// steal 계열
void CMob::CastInstant3( TNSKILL_DATA& a_kSkill, int a_iDamage ) // 추가적으로 발동하는 instant
{    
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_StealHP  :			
			OnHeal( Percent(a_iDamage, a_kSkill.krgEffect[i].iParam1), 0, m_iHandle );
			break;
		case eTNAfn_StealTP  :
			OnRecoverTP( Percent(a_iDamage, a_kSkill.krgEffect[i].iParam1), 0, m_iHandle );
			break;
		}
	}
}


// combatphase : 512
// 자기 자신이 직접 수행을 한다.
int CMob::StartAction( int a_iCaster, TNSKILL_DATA& a_kSkill, int a_iTarget )
{
	if( IsDead() ) return eTNRes_Failed;
	if( 0 >= a_iCaster || MAX_MOB <= a_iCaster ) return eTNRes_Failed;

	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		//if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_Sucide :
			{
				if( eTNMob_PC == pMob[a_iCaster].m_eMobType ) return eTNRes_Failed;
				KillMonster( a_iCaster );
			}
			break;
		case eTNAfn_Dash :
			{
				if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) return eTNRes_InvalidTarget4;
				if( eTNVSAfn_DontMove & m_iAffections ) return eTNRes_Failed;

				int iRealDist = CalDistance( m_iHandle, a_iTarget );
				int iMoveRange = a_kSkill.krgEffect[i].iParam1;

				HS2D_COORD kCur, kDest;
				kCur.x = TargetX;
				kCur.y = TargetY;
				kDest = kCur;

				if( iRealDist < iMoveRange )
				{					
					kDest.x = pMob[a_iTarget].TargetX;
					kDest.y = pMob[a_iTarget].TargetY;
					GetAttackPos( m_iHandle, kDest, kCur );
				}
				else
				{
					int x = pMob[a_iTarget].TargetX - TargetX;
					int y = pMob[a_iTarget].TargetY - TargetY;
					//if( 0 > x ) x = 0 - x; // target의 좌표가 현재의 좌표보다 크다.
					//if( 0 > y ) y = 0 - y; // target의 좌표가 현재의 좌표보다 크다.
					int iDivide = 5;
					x = x/iDivide; // 1/5
					y = y/iDivide; // 1/5
					HS2D_COORD kPos;
					kPos.x = TargetX;
					kPos.y = TargetY;
					for( int i = 0; i < iDivide; ++i )
					{
						kPos.x += x;
						kPos.y += y;
						int iDist = CalDistance( kCur, kPos, m_byBodyRadius, 0 );
						if( iDist > iMoveRange ) break;
						if( 0 >= kPos.y || MAX_GRIDY <= kPos.y ) break;
						if( 0 >= kPos.x || MAX_GRIDX <= kPos.x ) break;
						if( m_iBlockedCell & g_krgCell[kPos.y][kPos.x].usProperty ) break;
						kDest = kPos;						
					}
				}	

				int iDestX, iDestY;
				iDestX = kDest.x; 
				iDestY=  kDest.y;

				int tret = PickFreeMobGrid( m_iHandle, &iDestX, &iDestY );
				if( false == tret ) return eTNRes_Failed;

				kDest.x = iDestX;
				kDest.y = iDestY;

				MSG_Action nm; nm.wType = _MSG_Action;
				nm.wPDULength = sizeof(nm) - sizeof(HEADER);
				nm.TargetX = kDest.x; nm.TargetY = kDest.y;
				nm.dwKeyID = m_iHandle;
				nm.PosX=0; nm.PosY=0; nm.Direction = 0; 
				nm.Effect = 11; // 이동 형태, // 0:앉기  1:서기  2:걷기  3:뛰기  4:날기  5:텔레포트,	6:밀리기(knock-back), 7:미끄러지기(이동애니없음)  8:도발, 9:인사, 10:돌격 , 11:dash

				GridMulticast( m_iHandle, kDest.x, kDest.y, (MSG_STANDARD*)&nm );
				if( MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendOneMessage( (char*)&nm, sizeof(nm) );
				if( MAX_USER > a_iTarget ) pUser[a_iTarget].cSock.SendOneMessage( (char*)&nm, sizeof(nm) );
			}
			break;

		case eTNAfn_SummonTotem : 
			{// 토템 몬스터
				// 1. 주신전이라면 타주신을 공격하므로 적절하게 행동을 할것이다.
				//	2. guild war이라면 타 guild를 공격하면 된다. 이것은 요새 연합과도 공격을 한다는 것이다.
				// 현재 zone이 vaild하다면 진행
				if( (eZoneType_God != g_iZoneType) && (eZoneType_Guild != g_iZoneType) )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictSummonItem] );
					return eTNRes_Failed;
				}

				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Totem, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 1 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
					return eTNRes_Failed;
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_SummonFamiliar :
			{	// 패밀리어 소환
				if( MAX_USER < a_iTarget && MAX_MOB > a_iTarget )
				{// 보스몹인지 검사하는 routine
					int iDataIndex = pMob[a_iTarget].MOB.nTP;
					if( 0 < iDataIndex && MAX_MONSTER_DATA > iDataIndex )
					{
						if( eTNMonster_Boss & pMonsterData[iDataIndex].byQuest[eMonPrty_Reserved7] )
						{
							int iCostTP = a_kSkill.kCost.iTP - m_krgVariation[eTNVar_SaveTPCost][eVar_Skill].iPlus;
							IncTP( iCostTP );
							return eTNRes_InvalidTarget5;
						}
					}
				}
				
				int iRes = CanAttackTarget( a_iTarget );
				if( eTNRes_Succeeded == iRes ) // 공격할 수 있다.
				{
					if( 0 < m_irgSummoned[eTNCls2_Familiar] ) KillMobSummoned( eTNCls2_Familiar );//DeleteMob( m_irgSummoned[eTNCls2_Familiar], 1, 55 );
					int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Familiar, m_byClan, 0, TargetX, TargetY, a_iTarget, false, a_kSkill.krgEffect[i].iDuration, 0, 2 );
					if( 0 >= iMob || MAX_MOB <= iMob )
					{
						SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
					}
					else
					{
						
					}
				}
			}
			break;
		case eTNAfn_SummonTracker : // 몬스터가 PC에게 붙이는 소환몹을 소환~
			{ // 라푸의 사르파 소환
				Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Tracker, m_byClan, 0, TargetX, TargetY, a_iTarget, false, a_kSkill.krgEffect[i].iDuration, 0, 3 );
			}
			break;
		} // end of switch
	} // end of for

	return eTNRes_Succeeded;
}

// combatphase : 256(4도 같이 포함되어 있어야 한다.) 
void CMob::OnTakeInstant0( TNSKILL_DATA& a_kSkill, int a_iDamage, int a_iAttacker ) // 추가적으로 발동하는 instant
{
	return;

	int iScore = 0;
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_Taunt :
		case eTNAfn_DeTaunt :
			{
				iScore = ScoreDamage( a_kSkill.krgEffect[i].iID, a_iDamage );
				MemorizeAttacker( 0, iScore, a_iAttacker );
			}
			break;
		}
	}
}


// combatphase : 16
// target(corpse)에게 순간적인 효과를 내는
void  CMob::OnTakeInstant1( int a_iCaster, TNSKILL_DATA& a_kSkill )
{
	if( IsAlive() ) return;

	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_Resurrect :
			{
				if( m_bIsInArenaEntry ) break;
				Regen( a_kSkill.krgEffect[i].iParam1, REGEN_TYPE_RESURRECT ); // a_kSkill.krgEffect[i].iParam1

				if(a_iCaster<=0 || a_iCaster>=MAX_USER) return;
				char pData[256] = {0,};
				sprintf(pData, "res Resurrect char:%s MaxHP:%d HP:%d MaxTP:%d TP:%d from Char:%s", MOB.szName,m_iMaxHP,MOB.nHP,m_iMaxTP,MOB.nTP, pMob[a_iCaster].MOB.szName);
				Log( pData, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
			}
			break;
		}
	}
}



// combatphase : 32 
// target(alive)에게 순간적인 효과를 내는
int CMob::OnTakeInstant2( int a_iCaster, TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex )
{
	if( IsDead() ) return eTNRes_Failed;
	if( 0 >= a_iCaster || MAX_MOB <= a_iCaster ) return eTNRes_Failed;

	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_SummonFriend :
			{
				Teleport( m_iHandle, pMob[a_iCaster].TargetX, pMob[a_iCaster].TargetY );
			}
			break;
		case eTNAfn_Heal :
			{
				if( 2 == a_kSkill.krgEffect[i].kFunc.iData )
				{
					if( 0 >= a_kSkill.krgEffect[i].iParam2 ) a_kSkill.krgEffect[i].iParam2 = m_iMaxHP;
					a_kSkill.krgEffect[i].iParam1 += (m_iMaxHP / a_kSkill.krgEffect[i].iParam2);
					a_kSkill.krgEffect[i].kFunc.iData = 0;
				}
				else if( 3 == a_kSkill.krgEffect[i].kFunc.iData )
				{
					a_kSkill.krgEffect[i].iParam1 = Percent( m_iMaxHP, a_kSkill.krgEffect[i].iParam1 );
					a_kSkill.krgEffect[i].kFunc.iData = 0;
				}
				OnHeal( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].kFunc.iData, a_iCaster );
			}
			break;
		case eTNAfn_RecoverTP :
			{
				if( 2 == a_kSkill.krgEffect[i].kFunc.iData )
				{
					if( 0 >= a_kSkill.krgEffect[i].iParam2 ) a_kSkill.krgEffect[i].iParam2 = m_iMaxTP;
					a_kSkill.krgEffect[i].iParam1 += (m_iMaxTP / a_kSkill.krgEffect[i].iParam2);
					a_kSkill.krgEffect[i].kFunc.iData = 0;
				}
				else if( 3 == a_kSkill.krgEffect[i].kFunc.iData )
				{
					a_kSkill.krgEffect[i].iParam1 = Percent( m_iMaxTP, a_kSkill.krgEffect[i].iParam1 );
					a_kSkill.krgEffect[i].kFunc.iData = 0;
				}
				OnRecoverTP( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].kFunc.iData, a_iCaster );
			}
			break;
		//case eTNAfn_TownPortal3: //	고급 지바푸스티카
		//	{
		//		if( eWaitAct_None != m_kWaitAction.iAction ) continue;
		//		if( eTNVSAfn_HaveKalaCore & m_iAffections ) return eTNRes_Failed; // kala-core를 가지고 있으면, town portal을 동작하지 못하게 한다.
		//		m_kWaitAction.iAction = eWaitAct_TownPortal3;
		//	}	
		//	break;
		case eTNAfn_Cure :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData ) OnCure( a_kSkill.krgEffect[i].iParam1 );
			else if( 1 == a_kSkill.krgEffect[i].kFunc.iData ) ClearAffection();
			break;
		case eTNAfn_MagicShield :
			m_kMagicShield.Init( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam1 );
			m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
			break;
		case eTNAfn_ManaShield :
			m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
			break;
		case eTNAfn_DamageBonusForNextAttack :
			if( 0 == a_kSkill.krgEffect[i].kFunc.iData ) m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPlus = a_kSkill.krgEffect[i].iParam1;
			else if( 1 == a_kSkill.krgEffect[i].kFunc.iData ) m_krgVariation[eTNVar_DamageBonusForNextAttack][eVar_Skill].iPPlus = a_kSkill.krgEffect[i].iParam1;
			break;
		case eTNAfn_Pull :
			{
				//if( (eTNImm_All == m_iImmunity) || 
				if( eTNImm_Pull & m_iImmunity ) continue;
				if( eTNVSAfn_Hold & m_iAffections ) continue;
				if( eTNVSAfn_Hold2 & m_iAffections ) continue;
				//if( 3 < m_byBodyRadius ) continue;
				//if( 0 >= a_iSkillBookIndex || MAX_SKILL <= a_iSkillBookIndex ) continue;
				//if( !pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() ) continue;

				int x, y;
				x = pMob[a_iCaster].TargetX;
				y = pMob[a_iCaster].TargetY;
				int iDist = CalDistance( a_iCaster, m_iHandle );
				if( 3 > iDist ) continue; // 현재 가깝게 위치한 PC들은 pull하지 않는다.
				int iRes = PickFreeMobGrid( m_iHandle, &x, &y );
				if( FALSE == iRes ) continue; // 빈 자리가 없다면 pull을 성공하지 못한다.

				MSG_Action sm; GetAction( m_iHandle, x, y, &sm );
				sm.Effect = 6; // 6 is for the knock-back action.				
				GridMulticast( m_iHandle, x, y, (MSG_STANDARD*)&sm, 50 );	// 실제 좌표 이동까지 해주는 것이다.
				if( MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );
				//m_uiActionLock = CurrentTime + 1000;
			}
			break;
		case eTNAfn_KnockBack :
			{
				//if( (eTNImm_All & m_iImmunity) || 
				if( eTNImm_KnockBack & m_iImmunity ) continue;
				if( eTNVSAfn_DontMove & m_iAffections ) continue;
				if( 1 < m_byBodyRadius ) continue;
				//if( eKala_Brahma == MOB.snTribe || eKala_Vishnu == MOB.snTribe || eKala_Siva == MOB.snTribe ) continue; // hard-cording 나중에 뺀다.				
				if( 0 >= a_iSkillBookIndex || MAX_SKILL <= a_iSkillBookIndex ) continue;
				if( !pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() ) continue;

				int iDistant = a_kSkill.krgEffect[i].iParam2;
				if( eTNMob_PC == m_eMobType ) iDistant /= 2;
				//else if( 1 == m_byBodyRadius ) iDistant /= 2;

				int x = TargetX - pMob[a_iCaster].TargetX ;
				int y = TargetY - pMob[a_iCaster].TargetY;
				while( -4 > x || 4 < x || -4 > y || 4 < y )
				{
					x = (x+1) / 2;
					y = (y+1) / 2;
				}
				x += 4;
				y += 4;
				int iDir = g_pDirectionalTable[y][x];
				HS2D_COORD kPos, kDest;
				kDest.x = TargetX;
				kDest.y = TargetY;
				for( int p = 0; p < a_kSkill.krgEffect[i].iParam2; ++p )
				{
					kPos.x = kDest.x + g_pKnockbackTable[iDir][0];
					kPos.y = kDest.y + g_pKnockbackTable[iDir][1];
					if( 0 >= kPos.y || MAX_GRIDY <= kPos.y ) break;
					if( 0 >= kPos.x || MAX_GRIDX <= kPos.x ) break;
					if( m_iBlockedCell & g_krgCell[kPos.y][kPos.x].usProperty ) break;
					kDest = kPos;
				}

				NextX = kDest.x;
				NextY = kDest.y;

				int tret = PickFreeMobGrid( m_iHandle, &NextX, &NextY );
				if( false == tret ) return eTNRes_Failed;

				MSG_Action sm; GetAction( m_iHandle, NextX, NextY, &sm );
				sm.Effect = 6; // 6 is for the knock-back action.				
				GridMulticast( m_iHandle, NextX, NextY, (MSG_STANDARD*)&sm, 30 );	// 실제 좌표 이동까지 해주는 것이다.
				if( MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );
				//GridMulticast( NextX, NextY, (MSG_STANDARD*)&sm, -1, 30 ); // 실제 좌표 이동은 하지 않는다.
				m_uiActionLock = CurrentTime + 2000;
			}
			break;
		case eTNAfn_Teleport :
			Teleport( m_iHandle, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2 );
			break;
		case eTNAfn_Terror  :
			{// 내성 굴림을 해서, 도망 여부를 결정해야 한다.
				if( eTNMob_PC == m_eMobType ) break;

				if( 0 >= a_iSkillBookIndex || MAX_SKILL <= a_iSkillBookIndex ) continue;
				if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
				{
					int iLevelGap = MOB.byLevel - pMob[a_iCaster].MOB.byLevel;
					if( 0 < iLevelGap ) // 방어자가 더 높은 레벨이라면, 성공 확률을 떨어뜨린다.
					{						
						int iRate = m_kTolerance.iTerror * iLevelGap;
						int iDice = rand() % 100;
						if( iDice < iRate ) break;
					}

					LetsFlee( a_iCaster ); // 공격자의 위치와 반대방향으로 도망을 간다.
				}
			}
			break;
		case eTNAfn_ResetStat :
			ResetStat();
			ProcessContinuousEffect();
			break;
		case eTNAfn_ResetSkill :
			ResetSkill();
			ProcessContinuousEffect();
			break;
		case eTNAfn_ResetClass :
			if( ResetClass() ) return eTNRes_Failed;
			ProcessContinuousEffect();
			break;
		case eTNAfn_ResetQuest : // 31~35은 2차전직 quest
			//MOB.byQuest[0] = 255; // 초보자 퀘스트는 리셋하지 않는다.
			//MOB.byQuest[1] = 1;
			for( int q = 11; q < 31; ++q ) MOB.byQuest[q] = 0;
			for( int q = 36; q < 100; ++q ) MOB.byQuest[q] = 0;
			SendQuestHistory( m_iHandle );
			break;
		case eTNAfn_UnPack :
			{ // func : 묶음 개수(화살일 경우 250개)
			  // Param1 : Item ID
			  // Param2 : 풀어질 개수
				int iEmptySlot = 0;
				int iInserted = 0;

				for( int iSlot = 0; iSlot < byMaxInven; ++iSlot )
				{
					if( 0 >= MOB.Inven[iSlot].snIndex ) ++iEmptySlot; // 빈슬롯이다.
				}

				if( iEmptySlot >= a_kSkill.krgEffect[i].iParam2 )
				{					
					short sItemIndex = (short)(a_kSkill.krgEffect[i].iParam1 - HT_PARAMTYPE_ITEM_START + 1 );

					for( int iSlot = 0; iSlot < byMaxInven; ++iSlot )
					{
						if( iInserted >= a_kSkill.krgEffect[i].iParam2 ) break;

						if( 0 >= MOB.Inven[iSlot].snIndex ) // 빈슬롯이다.
						{
							ZeroMemory( &MOB.Inven[iSlot], sizeof(STRUCT_ITEM) );
							MOB.Inven[iSlot].snIndex = sItemIndex;
							MOB.Inven[iSlot].byCount= a_kSkill.krgEffect[i].kFunc.iData ; // pItemData[sItemIndex].byMaxPackCount;
							MOB.Inven[iSlot].snDurability = pItemData[sItemIndex].sMaxDur;
							MOB.Inven[iSlot].wSerial = GetRandom(0, 65535);
							MOB.Inven[iSlot].snDummy = 0;

							S_SCP_RESP_ITEM_SET itemset;
							itemset.wType = SCP_RESP_ITEM_SET;
							itemset.byType = SET_ITEM_CREATE;
							itemset.byPlace = ITEM_PLACE_INVEN; // inventory
							itemset.byIndex = iSlot;
							memcpy(&(itemset.sitem), &(MOB.Inven[iSlot]), sizeof(STRUCT_ITEM));
							pUser[m_iHandle].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));	

							char strItem[128] = {0,};
							char temp[256] ={0,};
							if (BASE_CheckItemLog(&MOB.Inven[iSlot]))
							{	BASE_GetItemCode(&MOB.Inven[iSlot], strItem);
								sprintf(temp,"get %s",strItem);
								Log(temp,pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
							}

							++iInserted;
						}
					}
				}
				else
				{// 빈 슬롯이 모자른다.
					SendClientMessage( m_iHandle, g_pMessageStringTable[_Inventory_Space_Lack] );
					return eTNRes_LackInventorySlot;
				}
			}
			break;
		case eTNAfn_MoveToTheMandraTown :
			{
				MoveZone( eZone_Mandra, 486, 190 );
			}
			break;
		case eTNAfn_FireFX :
			{
				S_SCP_FIRE_FX_BROADCAST kMsg;
				kMsg.wType = SCP_FIRE_FX_BROADCAST;
				kMsg.wPDULength = WORD(sizeof(S_SCP_FIRE_FX_BROADCAST)-sizeof(HEADER));
				kMsg.dwKeyID = m_iHandle;
				kMsg.iFX = a_kSkill.krgEffect[i].iParam1;

				GridMulticast( TargetX, TargetY, (MSG_STANDARD*)&kMsg, -1, 50 );
			}
			break;
		case eTNAfn_RepairAll :
			{	int nItemIndex = 0; short sMaxDur=0; 
				S_SCP_RESP_ITEM_REPAIR sm; sm.wType = SCP_RESP_ITEM_REPAIR; 
				sm.byResult=REPLY_ACK_OK; sm.byPlace = ITEM_PLACE_EQUIP; 
				for(int i=0; i<MAX_EQUIP; i++)
				{	if(MOB.Equip[i].snIndex==0) continue;
					nItemIndex=MOB.Equip[i].snIndex+HT_PARAMTYPE_ITEM_START-1;

					if(!g_ParamMgr.HT_bGetItemMaxDurability(nItemIndex, &sMaxDur))
					{	char pLog[256] = {0,};
						sprintf(pLog,"err eTNAfn_RepairAll Invalid itemindex char:%s itemindex:%d place:%d index:%d",MOB.szName,nItemIndex,ITEM_PLACE_EQUIP,i);
						Log(pLog,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
						WriteLog( pLog, ".\\Event\\[Log]Critical_Log.txt" ); continue;
					}
					if(MOB.Equip[i].snDurability!=sMaxDur)
					{	STRUCT_ITEM tmpItem = MOB.Equip[i];
						MOB.Equip[i].snDurability = sMaxDur;	//	수리하고
						sm.byIndex=i; sm.byDummy = 0;			//	0:유료아이템으로 수리, 1:루피아로 수리
						pUser[m_iHandle].cSock.AddMessage((char*)&sm,sizeof(sm));

						char temp[1024] = {0,};
						char szFrom[256], szTo[256];
						BASE_GetItemCode( &tmpItem, szFrom );
						BASE_GetItemCode( &MOB.Equip[i], szTo );
						sprintf(temp, "repair Repaired by RepairAll [from %s To %s]", szFrom, szTo);
						Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
					}
				}				
				pUser[m_iHandle].cSock.SendMessage();
				UpdatePoints();
			}
			break;
		case eTNAfn_SummonParty :
			{
				if( eWaitAct_None != m_kWaitAction.iAction ) continue;
				m_kWaitAction.iAction = eWaitAct_SummonParty;
				m_kWaitAction.uiWaitingTime = CurrentTime + eWaitTime_SummonParty;	

				int iLeader = Leader;
				if( 0 >= iLeader || MAX_USER <= iLeader ) iLeader = m_iHandle; // 자신이 리더이다. 

				// 파티원들 소환
				for( int d = 0; d < MAX_PARTY+1; ++d )
				{   
					int fol = 0;
					if(d==0) fol = iLeader;
					else fol = pMob[iLeader].m_irgParty[d-1];
					if( 0 > fol || MAX_USER <= fol ) continue;
					if( fol == m_iHandle ) continue;							//	파티소환자는 보내지 않아도 된다.		 
					char pBuf[128] = {0,};
					sprintf(pBuf, g_pMessageStringTable[_SummonParty], MOB.szName);
					SendClientMessage(fol, pBuf);
				}
			}
			break;
		case eTNAfn_IWantIt:
			{
				g_GameEvent.m_IWantIt.IncreaseUserItemCount(MOB.szName);
			}	break;
		case eTNAfn_MicroSound:
			{
				int nIndex = 0;
				byte byResult = g_GameEvent.m_MicroSound.UseCoupon(&nIndex);

				if(byResult==1)
				{	MSG_Broadcast sm; ZeroMemory(&sm, sizeof(sm));
					sm.wType = _MSG_Broadcast;
					//	sm.byBgColor = 0; sm.byTextColor = 
					sprintf(sm.szMsg, "축하합니다 ?♪♬!! %s님이 COMRADE(컴리드) GeForce 6600 3.3ns 상에 당첨되었습니다.", MOB.szName);
					strncpy(sm.szName, "탄트라운영팀", SZNAME_LENGTH);
					sm.byTrimuriti = MOB.byTrimuriti;

					if(!MSGServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
					{	Log("err brodcast MSG-SEND MESSAGE_EXTRA",pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
					}
				}
				if(byResult==2)						//	상품지급 2~6등까지 지급
				{	GiveItem(m_iHandle, 7218, 1);
				}
				else if(byResult==3)
				{	GiveItem(m_iHandle, 7067, 1);
				}
				else if(byResult==4)
				{	GiveItem(m_iHandle, 7063, 1);
				}
				else if(byResult==5)
				{	GiveItem(m_iHandle, 7068, 255);
				}
				else if(byResult==6)
				{	GiveItem(m_iHandle, 7039, 1);
				}

				Msg_GameEvent sm; ZeroMemory(&sm, sizeof(sm));
				sm.wType = _Msg_GameEvent; sm.byResult = byResult;

				pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));

				char pch[128] = {0,};
				sprintf(pch, "Rank:%d, Index:%d, Account:%s, Char:%s \r\n", byResult, nIndex, pUser[m_iHandle].AccountName, MOB.szName);
				TimeWriteLog(pch, "MocroSound.dat");
			}	break;
		}
	}

	return eTNRes_Succeeded;
}

int CMob::OnChargInstance(TNSKILL_DATA& a_kSkill)
{
	if( IsDead() ) return eTNRes_Failed;

	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;

		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_ExpandBag7:
			{	ExpandFunc(eTime_Inven, 7);
				byMaxInven = MAX_ONEINVEN*2;
			}	break;
		case eTNAfn_ExpandStore7:
			{	ExpandFunc(eTime_Store, 7);
			}	break;
		case eTNAfn_AMoneyRoot7:
			{	ExpandFunc(eTime_AMoneyRoot, 7);
				m_bAMoneyRoot = true;
			}	break;
		case eTNAfn_MAtman7:
			{	ExpandFunc(eTime_Atman, 7);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_MAnubaba7:
			{	ExpandFunc(eTime_Anubaba, 7);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_M15Chakra7:
			{	ExpandFunc(eTime_15Chakra, 7);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_ExpandBag30:
			{	ExpandFunc(eTime_Inven);
				byMaxInven = MAX_ONEINVEN*2;
			}	break;
		case eTNAfn_ExpandStore30:
			{	ExpandFunc(eTime_Store);
			}	break;
		case eTNAfn_AMoneyRoot30:
			{	ExpandFunc(eTime_AMoneyRoot);
				m_bAMoneyRoot = true;
			}	break;
		case eTNAfn_MAtman30:
			{	ExpandFunc(eTime_Atman);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_MAnubaba30:
			{	ExpandFunc(eTime_Anubaba);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_M15Chakra30:
			{	ExpandFunc(eTime_15Chakra);
				//ProcessContinuousEffect();
			}	break;
		case eTNAfn_ExpandFunc:
			{	int nEffect[4] = {0,};
				nEffect[0] = a_kSkill.krgEffect[i].kFunc.iData;
				nEffect[1] = a_kSkill.krgEffect[i].iDuration;
				nEffect[2] = a_kSkill.krgEffect[i].iParam1;
				nEffect[3] = a_kSkill.krgEffect[i].iParam2;

				TNSKILL_DATA sData; ZeroMemory(&sData, sizeof(sData));
				for(int i=0; i<4; i++) sData.krgEffect[i].iID = nEffect[i];
		
				OnChargInstance(sData);

			}	break;
		case eTNAfn_ExpandItem:
			{
				int nIndex1 = a_kSkill.krgEffect[i].kFunc.iData;
				int nCount1 = a_kSkill.krgEffect[i].iDuration;
				int nIndex2 = a_kSkill.krgEffect[i].iParam1;
				int nCount2 = a_kSkill.krgEffect[i].iParam2;

				if(!CHTParamIDCheck::HT_bIsItem(nIndex1)) continue;	//	item1 index check
				GiveItem(m_iHandle, nIndex1, nCount1);

				if(!CHTParamIDCheck::HT_bIsItem(nIndex2)) continue;	//	item2 index check
				GiveItem(m_iHandle, nIndex2, nCount2);

			}	break;
		case eTNAfn_FuncBeauty:
			{	pUser[m_iHandle].m_byItemStatus |= 0x01;			//	eTNAfn_FuncBeauty는 m_byItemStatus의 오른쪽 0st bit사용
			}	break;
		case eTNAfn_TownPortal : // 이동의 푸스티카
			{	
				if( eWaitAct_None != m_kWaitAction.iAction ) continue;
				if( eTNVSAfn_HaveKalaCore & m_iAffections ) 
				{	char pch[256] = {0,};
					sprintf(pch, "Char:%s pustica is stopped by kala-core", MOB.szName);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

					return eTNRes_Failed; // kala-core를 가지고 있으면, town portal을 동작하지 못하게 한다.
				}
				m_kWaitAction.iAction = eWaitAct_TownPortal;
				m_kWaitAction.uiWaitingTime = CurrentTime + a_kSkill.krgEffect[i].iDuration;
			}
			break;
		case eTNAfn_ChangeTrimuritiSiva:
			{	if(MOB.byLevel <= 29) break;			//	29랩이하는 사용불가하다
				if((ServerIndex+1) != 1) break;			//	1번존외에는 사용불가하다
				if(MOB.nGuildID != 0) break;			//	길드원일 경우 사용불가하다

				MOB.byTrimuriti = eTNClan_Siva;
				BroadCastTrimuritiSelection(m_iHandle);
			}	break;
		case eTNAfn_ChangeTrimuritiBrahma:
			{	if(MOB.byLevel <= 29) break;
				if((ServerIndex+1) != 1) break;
				if(MOB.nGuildID != 0) break;

				MOB.byTrimuriti = eTNClan_Brahma;
				BroadCastTrimuritiSelection(m_iHandle);
			}	break;

		case eTNAfn_ChangeTrimuritiVishnu:
			{	if(MOB.byLevel <= 29) break;
				if((ServerIndex+1) != 1) break;
				if(MOB.nGuildID != 0) break;

				MOB.byTrimuriti = eTNClan_Vishnu;
				BroadCastTrimuritiSelection(m_iHandle);
			}	break;
		//case eTNAfn_TownPortal2 : // 지바 푸스티카
		//	{	
		//		if( eWaitAct_None != m_kWaitAction.iAction ) continue;
		//		if( eTNVSAfn_HaveKalaCore & m_iAffections ) return eTNRes_Failed; // kala-core를 가지고 있으면, town portal을 동작하지 못하게 한다.
		//		m_kWaitAction.iAction = eWaitAct_TownPortal2;
		//		m_kWaitAction.uiWaitingTime = CurrentTime + eWaitTime_TownPortal2;
		//	}
			break;
		}

	}

	if(CHTParamIDCheck::HT_bIsItemChargeFunction(a_kSkill.sID)) ProcessContinuousEffect();

	return eTNRes_Succeeded;
}


//---------------------------------------------------------------------------------------------------------------------------------
// combatphase : 64
// target(alive)에게 지속적으로 효과를 나타내는 시간 지속성을 가지는 경우에만 호출을 해준다.
// instant effect들을 걸러준다.
//@Param
//	- a_eVarType : eVar_Equipment/eVar_Skill/eVar_PassiveSkill
//---------------------------------------------------------------------------------------------------------------------------------
int CMob::OnTakeAffections( TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iCaster, int a_iPartyLeader, int a_eAdd, int a_eVarType, int a_iLevelGap )
{
	if( IsDead() ) return eTNRes_Failed;
	//if( !(a_kSkill.sSkillType & eTNSklT_Affection) ) return;

	#ifdef __TN_2ND_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "  => [OnTakeAffections] Caster(%d, %s, Lvl:%d, HP:%d)가 스킬(%d, Lvl:%d)을 몹(%d, %s, Lvl:%d, HP:%d)에게 쓴다. LevelGap:%d \r\n", a_iCaster, pMob[a_iCaster].MOB.szName, pMob[a_iCaster].MOB.byLevel, pMob[a_iCaster].MOB.nHP, a_kSkill.sID, a_kSkill.byLevel, m_iHandle, MOB.szName, MOB.byLevel, MOB.nHP, a_iLevelGap );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_2ND_LOG__

	int iRes = eTNRes_Failed;
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 == a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant == a_kSkill.krgEffect[i].iDuration ) continue;

		//if( eVar_Skill == a_eVarType || eVar_Potion == a_eVarType ) // action, active skill인 경우만, ...
		if( eVar_Skill == a_eVarType )
		{
			if( eTNSklD_Instant >= a_kSkill.krgEffect[i].iDuration ) continue; // 버프 스킬인 경우, permanent하게 지속되는 경우는 없다.
			if( eAfn_Add == a_eAdd )
			{				
				int iRate = 100;
				switch( a_kSkill.krgEffect[i].iID )
				{
				case eTNAfn_Sleep :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // 방어자가 더 높은 레벨인 경우, 성공 확률을 떨어뜨린다.
								iRate = m_kTolerance.iSleep * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}						
							AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_Hold :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // 방어자가 더 높은 레벨인 경우, 성공 확률을 떨어뜨린다.
								iRate = m_kTolerance.iHold * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}						
							AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_Stun :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // 방어자가 더 높은 레벨인 경우, 성공 확률을 떨어뜨린다.
								iRate = m_kTolerance.iStun * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}						
							AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_Blind :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // 방어자가 더 높은 레벨인 경우, 성공 확률을 떨어뜨린다.
								iRate = m_kTolerance.iBlind * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}						
							AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_DOTbyDice :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // 방어자가 더 높은 레벨인 경우, 성공 확률을 떨어뜨린다.
								iRate = 10 * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}
							TNEFFECT kDot = a_kSkill.krgEffect[i];
							kDot.iID = eTNAfn_Damage;
							AddEffect( kDot, a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_Taunt :
					{
						//SetBattle( m_iHandle, a_iCaster ); // damage가 들어가면, 삭제를 하도록 한다.
						MemorizeAttacker( 0, 100, a_iCaster );
						AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
						iRes = eTNRes_Succeeded;
					}
					break;
				/*
				case eTNAfn_DeTaunt :
					{
						AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
					}
					break;
				*/
				default :
					AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
					iRes = eTNRes_Succeeded;
					break;
				}				
			}
			else
			{
				#ifdef __TN_TOP_LOG__
				{
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[%d월%d일 %d시%d분%d초] OnTakeAffections> Caster:%d, MyHandle:%d, EffectID:%d, EffectDur:%d, Param1:%d, Param2:%d \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, a_iCaster, m_iHandle, a_kSkill.krgEffect[i].iID, a_kSkill.krgEffect[i].iDuration, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2 );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
				}
				#endif
				RemoveEffect( a_kSkill.krgEffect[i].iID );
			}
		}
		else AffectEffect( a_kSkill.krgEffect[i], eVar_PassiveSkill, a_eAdd, a_iCaster, a_iPartyLeader, a_iLevelGap ); // passive skill 인 경우만, ...
	} // end of for

	return iRes;
}

//---------------------------------------------------------------------------------------------------------------------------------
// 지속 시간을 가지는 effect 적용
// 지속 시간을 가지는 effect인 경우에는  a_eBuff가 true 이다.
//---------------------------------------------------------------------------------------------------------------------------------
void CMob::AffectEffect( TNEFFECT a_kEffect, int a_eVarType, int a_eAdd, int a_iCaster, int a_iPartyLeader, int a_iLevelGap )
{	
	if( 0 > a_eVarType || eVar_PassiveSkill < a_eVarType ) return;	
	if( eVar_Equipment == a_eVarType )
		if( eTNSklD_Unlimited != a_kEffect.iDuration ) return; // equipment인 경우에는 duration값이 -1(unlimited)인 effect만을 적용한다.

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t\t[AffectEffect] %d(0:추가,1:제거)> ID: %d, Func: %d, Dur: %d, Param1: %d, Param2: %d, Effect종류:%d(0:장비,1:버프,2:패시브), LevelGap:%d, LevelGap을적용한Param1:%d \r\n"
			, a_eAdd, a_kEffect.iID,  a_kEffect.kFunc.iData,  a_kEffect.iDuration,  a_kEffect.iParam1,  a_kEffect.iParam2, a_eVarType, a_iLevelGap, a_kEffect.iParam1 - (a_kEffect.iParam1 * 15 * a_iLevelGap + 50)/100 );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif // __TN_3RD_LOG__

	if( eAfn_Remove == a_eAdd )
	{
		a_kEffect.iParam1 = 0 - a_kEffect.iParam1;
		a_kEffect.iParam2 = 0 - a_kEffect.iParam2;
	}
	//else if( a_eBuff ) AddEffect( a_kEffect );

	switch( a_kEffect.iID )
	{	
	case eTNAfn_Stun :
	case eTNAfn_Sleep :
		{
			UpdateSpeed();
			UpdateCF();
		}
		break;
	case eTNAfn_Hold :
	case eTNAfn_Hold2 :
		{
			if( eVar_Skill == a_eVarType ) UpdateSpeed();
		}
		break;
	case eTNAfn_Invisible :
		{
			if( eAfn_Remove == a_eAdd )
			{
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_MoveSpeedPlus;
				kEffect.kFunc.iData = 0;
				kEffect.iDuration = 20000;
				kEffect.iParam1 = 3;
				AddEffect( kEffect, m_iHandle, m_iHandle );
			}

			if( eVar_Skill == a_eVarType ) UpdateSpeed();
		}
		break;

	case eTNAfn_Blind :
		{
			UpdateCF();
			if( eTNMob_NPC == m_eMobType )
			{
				if( eAfn_Remove == a_eAdd )
				{
					m_kSight.sPeace = pMonsterData[MOB.nTP].byQuest[eMonPrty_NormalSight];
					m_kSight.sCombat = pMonsterData[MOB.nTP].byQuest[eMonPrty_CombatSight];
				}
				else
				{
					m_kSight.sCombat = 2;
					m_kSight.sPeace = 1;
				}
			}
		}
		break;
	case eTNAfn_ReduceKaram :
		{
			m_krgVariation[eTNVar_ReduceKaram][a_eVarType].iPlus += a_kEffect.iParam1;
		}
		break;
	case eTNAfn_AllStatePlus :
	case eTNAfn_AllStatePlus2 :
		m_krgVariation[eTNVar_Muscle][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_Nerves][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_Heart][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_Mind][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_AllStateMinus :
	case eTNAfn_AllStateMinus2 :
		m_krgVariation[eTNVar_Muscle][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_Nerves][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_Heart][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_Mind][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;	
	case eTNAfn_MusclePlus :
	case eTNAfn_MusclePlus2 :
		m_krgVariation[eTNVar_Muscle][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_MuscleMinus :
		m_krgVariation[eTNVar_Muscle][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_NervesPlus :
	case eTNAfn_NervesPlus2 :
		m_krgVariation[eTNVar_Nerves][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_NervesMinus :
		m_krgVariation[eTNVar_Nerves][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_HeartPlus :
	case eTNAfn_HeartPlus2 :
		m_krgVariation[eTNVar_Heart][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_HeartMinus :
		m_krgVariation[eTNVar_Heart][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_MindPlus :
	case eTNAfn_MindPlus2 :
		m_krgVariation[eTNVar_Mind][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_MindMinus :
		m_krgVariation[eTNVar_Mind][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdatePoints();
		break;
	case eTNAfn_AllDamagePlus :
		{
			if( 0 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_MinDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus += a_kEffect.iParam1;
			}
			else if( 1 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_MinDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
			}
			if( eVar_Skill == a_eVarType ) UpdateDamage();
		}
		break;
	case eTNAfn_AllDamageMinus :
		{
			if( 0 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_MinDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
			}
			else if( 1 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_MinDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
			}
			if( eVar_Skill == a_eVarType ) UpdateDamage();
		}
		break;
	case eTNAfn_FixedDamagePlus :
		{
			m_krgVariation[eTNVar_FixedDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		}
		break;
	case eTNAfn_FixedDamageMinus :
		{
			m_krgVariation[eTNVar_FixedDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
		}
		break;
	case eTNAfn_FixedDamagePlus2 :
		{
			m_krgVariation[eTNVar_FixedDamage2][a_eVarType].iPlus += a_kEffect.iParam1;
		}
		break;
	case eTNAfn_FixedDamageMinus2 :
		{
			m_krgVariation[eTNVar_FixedDamage2][a_eVarType].iPlus -= a_kEffect.iParam1;
		}
		break;
	case eTNAfn_DamagePlus :
	case eTNAfn_DamagePlus2 :
		if( 0 == a_kEffect.kFunc.iData )
		{
			m_krgVariation[eTNVar_MinDamage][a_eVarType].iPlus += a_kEffect.iParam1;
			m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPlus += a_kEffect.iParam2;
		}
		else if( 1 == a_kEffect.kFunc.iData )
		{
			m_krgVariation[eTNVar_MinDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
			m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPPlus += a_kEffect.iParam2;
		}
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_DamageMinus :
	case eTNAfn_DamageMinus2 :
		if( 0 == a_kEffect.kFunc.iData )
		{
			m_krgVariation[eTNVar_MinDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
			m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPlus -= a_kEffect.iParam2;
		}
		else if( 1 == a_kEffect.kFunc.iData )
		{
			m_krgVariation[eTNVar_MinDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
			m_krgVariation[eTNVar_MaxDamage][a_eVarType].iPPlus -= a_kEffect.iParam2;
		}
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_ElementalDamagePlus :
		{
			if( 0 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus += a_kEffect.iParam1;
			}
			else if( 1 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
			}

			if( eVar_Skill == a_eVarType ) UpdateDamage();
		}
		break;
	case eTNAfn_ElementalDamageMinus :
		{
			if( 0 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
			}
			else if( 1 == a_kEffect.kFunc.iData )
			{
				m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
				m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
			}

			if( eVar_Skill == a_eVarType ) UpdateDamage();
		}
		break;
	case eTNAfn_FireDamagePlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_FireDamageMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_FireDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_ColdDamagePlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_ColdDamageMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_ColdDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_LightningDamagePlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_LightningDamageMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_LightningDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_PoisonDamagePlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_PoisonDamageMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData )	m_krgVariation[eTNVar_PoisonDamage][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDamage();
		break;
	case eTNAfn_AllResistPlus :
		m_krgVariation[eTNVar_FireResist][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_ColdResist][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_LightningResist][a_eVarType].iPlus += a_kEffect.iParam1;
		m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_AllResistMinus :
		m_krgVariation[eTNVar_FireResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_ColdResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_LightningResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_FireResistPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireResist][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireResist][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_FireResistMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_FireResist][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_ColdResistPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdResist][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdResist][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_ColdResistMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ColdResist][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_LightningResistPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningResist][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningResist][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_LightningResistMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_LightningResist][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_PoisonResistPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_PoisonResistMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PoisonResist][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateResist();
		break;
	case eTNAfn_AttackRatePlus :
	case eTNAfn_AttackRatePlus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackRate][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackRate][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_AttackRateMinus :
	case eTNAfn_AttackRateMinus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackRate][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackRate][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_DodgeRatePlus :
	case eTNAfn_DodgeRatePlus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DodgeRate][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DodgeRate][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_DodgeRateMinus :
	case eTNAfn_DodgeRateMinus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DodgeRate][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DodgeRate][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_DodgeSpeedUp :
		m_krgVariation[eTNVar_DodgeSpeed][a_eVarType].iPlus += a_kEffect.iParam1;		
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_DodgeSpeedDown :
		m_krgVariation[eTNVar_DodgeSpeed][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateCF();
		break;
	case eTNAfn_ACPlus : // armor class
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AC][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AC][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDefense();
		break;
	case eTNAfn_ACMinus : // armor class
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AC][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AC][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDefense();
		break;
	case eTNAfn_DefensePlus : // defense 
	case eTNAfn_DefensePlus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_Defense][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_Defense][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDefense();
		break;
	case eTNAfn_DefenseMinus : // defense
	case eTNAfn_DefenseMinus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_Defense][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_Defense][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateDefense();
		break;
	case eTNAfn_MaxHPPlus :
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxHPPlus2 :
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxHPMinus :
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxHPPPlus :		
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxHPPMinus :
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxHPPlusByMind :
		m_krgVariation[eTNVar_MaxHP][a_eVarType].iPlus += Percent( pMob[a_iCaster].m_kChakra.sMind, a_kEffect.iParam1 );
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_HPRecoveryPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_HPRecovery][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_HPRecovery][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_HPRecoveryMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_HPRecovery][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_HPRecovery][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxTPPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxTPPlus2 :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxTPMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MaxTP][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MaxTPPlusByMind :
		m_krgVariation[eTNVar_MaxTP][a_eVarType].iPlus += Percent( pMob[a_iCaster].m_kChakra.sMind, a_kEffect.iParam1 );
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_TPRecoveryPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_TPRecovery][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_TPRecovery][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_TPRecoveryMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_TPRecovery][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_TPRecovery][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateHPTP();
		break;
	case eTNAfn_MoveSpeedPlus : // 이속 증가

		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;

		//m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_MoveSpeedMinus :
		//if( 60 < m_kCombatFactors.irgResist[eRst_Cold] ) return;

		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;

		//m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_AttackSpeedPlus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		//m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_AttackSpeedMinus :		
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;
		//m_krgVariation[eTNVar_AttackSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_CastSpeedPlus :		
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		//m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_CastSpeedMinus :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPlus -= a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;
		//m_krgVariation[eTNVar_CastSpeed][a_eVarType].iPPlus -= a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	//case eTNAfn_MagicShield :
		//m_kMagicShield.Init( a_kEffect.iParam1, a_kEffect.iParam1 );
		//break;
	case eTNAfn_SpiritLink :
		{
			if( eAfn_Remove == a_eAdd )
			{
				m_iLinker = 0;
				m_krgVariation[eTNVar_SpiritLink][a_eVarType].iPlus = 0;
			}
			else
			{				
				if( a_iCaster != m_iHandle )
				{
					m_iLinker = a_iCaster;
					m_krgVariation[eTNVar_SpiritLink][a_eVarType].iPlus = a_kEffect.iParam1;
				}
			}
		}
		break;
	case eTNAfn_DamageBonusForNextAttack :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DamageBonusForNextAttack][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_DamageBonusForNextAttack][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_ReflectDamage :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ReflectDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ReflectDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_AbsorbDamage :
		m_krgVariation[eTNVar_AbsorbDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_AbsorbElementalDamage :
		m_krgVariation[eTNVar_AbsorbElementalDamage][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_SaveTPCost :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_SaveTPCost][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_SaveTPCost][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_RangeUp :
		m_krgVariation[eTNVar_RangeUp][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_RangeDown :
		m_krgVariation[eTNVar_RangeDown][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_SuccessRate :
		m_krgVariation[eTNVar_SuccessRate][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_VictoryHPBonus :
			m_krgVariation[eTNVar_VictoryHPBonus][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_VictoryTPBonus :
			m_krgVariation[eTNVar_VictoryTPBonus][a_eVarType].iPlus += a_kEffect.iParam1;
		break;

	case eTNAfn_CriticalBonus :
			m_krgVariation[eTNVar_CriticalBonus][a_eVarType].iPPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_HealPlus :
		m_krgVariation[eTNVar_HealPlus][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_RecoverTPPlus :
		m_krgVariation[eTNVar_RecoverTPPlus][a_eVarType].iPlus += a_kEffect.iParam1;
		break;	
	case eTNAfN_PetGrowth :
		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PetGrowthHP][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PetGrowthDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 2 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_PetGrowthAttackSpeed][a_eVarType].iPlus += a_kEffect.iParam1;
		break;
	case eTNAfn_WeaponMastery :	
		{
			if( eTNWpn_Sword & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Sword].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Axe & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Axe].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Spear & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Spear].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Blunt & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Blunt].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Claw & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Claw].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Staff & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Staff].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Bow & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Bow].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_Dagger & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_Dagger].iParam1 = a_kEffect.iParam1;
			}

			if( eTNWpn_TwoHand & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_TwoHanded].iParam1 = a_kEffect.iParam1;
			}
			if( eTNWpn_DualHand & a_kEffect.kFunc.iData )
			{
				m_krgMastery[eWpnMtryIdx_DualWpn].iParam1 = a_kEffect.iParam1;
				m_krgMastery[eWpnMtryIdx_DualWpn].iParam2 = a_kEffect.iParam2;
			}
			
			//if( eTNWpn_All == a_kEffect.kFunc.iData ) iMasteryIndex = eWpnMtryIdx_All;
			if( eVar_Skill == a_eVarType ) UpdateDamage();
		}
		break;
	case eTNAfn_Immunity :
		{// 하나의 effect 에 대한 immunity 설정, 하나의 effect에 대해서 immunity를 걸기 쉽다. 하지만 다수를 하기에는 무리가 있음
			int iOldOne = m_iImmunity;
			bool bLog = false;
			int iImmunityModified = 0;
			if( eAfn_Remove == a_eAdd )
			{
				if( IsDebugOn( eTNDbg_Immunity ) ) bLog = true;
				int iAffection = 0 - a_kEffect.iParam1;
				iImmunityModified = Aff2Imm( iAffection );
				Remove_Immunity( iImmunityModified );
			}
			else
			{
				if( IsDebugOn( eTNDbg_Immunity ) ) bLog = true;
				iImmunityModified = Aff2Imm( a_kEffect.iParam1 );
				Add_Immunity( iImmunityModified );
			}

			if( bLog || m_iDebugFlag )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[AffectEffect()::eTNAfn_Immunity] Immunity:%u(%u), added:%d, effect-param1:%d, iImmunityModified:%u, effect-dur:%u, Now:%u \r\n"
					, m_iImmunity, iOldOne, a_eAdd, a_kEffect.iParam1, iImmunityModified, a_kEffect.iDuration, CurrentTime );
				WriteLog( chBuf, m_szLogFile );
			}
		}
		break;
	case eTNAfn_Immunity2 :
		{ // 다수에 대한 immunity를 한번에 걸때, 사용하면 좋다.
			int iOldOne = m_iImmunity;
			bool bLog = false;
			int iImmunityModified = a_kEffect.iParam1;
			if( eAfn_Remove == a_eAdd )
			{
				if( IsDebugOn( eTNDbg_Immunity ) ) bLog = true;
				iImmunityModified = 0 - iImmunityModified;
				Remove_Immunity( iImmunityModified );
			}
			else
			{
				if( IsDebugOn( eTNDbg_Immunity ) ) bLog = true;
				Add_Immunity( iImmunityModified );
			}

			if( bLog || m_iDebugFlag )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[AffectEffect()::eTNAfn_Immunity2] Immunity:%u(%u), added:%d, iImmunityModified:%u, effect-dur:%u, Now:%u \r\n"
					, m_iImmunity, iOldOne, a_eAdd, iImmunityModified, a_kEffect.iDuration, CurrentTime );
				WriteLog( chBuf, m_szLogFile );
			}
		}
		break;
	case eTNAfn_BlessOfGod :
		{
			if( MAX_USER <= m_iHandle || MAX_MOB <= m_iHandle ) break;

			if( eAfn_Remove == a_eAdd )
			{
				Init( m_iHandle );
			}
		}
		break;
	case eTNAfn_Debug :
		{
			if( eAfn_Remove == a_eAdd )
			{
				Remove_Debug( a_kEffect.iParam1 );
			}
			else Add_Debug( a_kEffect.iParam1 );
		}
		break;

	case eTNAfn_Log :
		{
			if( eAfn_Remove == a_eAdd )
			{
				m_iDebugFlag = 0;
			}
			else m_iDebugFlag = 1; 
		}
		break;
	case eTNAfn_LogImmu :
		{
			if( eAfn_Remove == a_eAdd )
			{
				Remove_Debug( eTNDbg_Immunity );
			}
			else Add_Debug( eTNDbg_Immunity );
		}
		break;
	case eTNAfn_EnhanceWeapon :
		{
			m_krgVariation[eTNVar_EnhanceWeapon][a_eVarType].iPlus += a_kEffect.iParam1;			
			/*
			if( eAfn_Remove == a_eAdd )
			{
				m_krgVariation[eTNVar_EnhanceWeapon][a_eVarType].iPlus = 0;
			}
			else m_krgVariation[eTNVar_EnhanceWeapon][a_eVarType].iPlus = a_kEffect.iParam1;			
			*/
			if( eVar_Skill == a_eVarType ) UpdateDamage();			
		}
		break;
	case eTNAfn_EnhanceArmor :
		{
			int iVarIndex = eTNVar_EnhanceHelmet;
			iVarIndex += a_kEffect.iParam2;
			if( eTNVar_EnhancePants < iVarIndex ) break;

			m_krgVariation[iVarIndex][a_eVarType].iPlus += a_kEffect.iParam1;
			if( eVar_Skill == a_eVarType ) UpdateEquipmentPoints();
		}
		break;

	case eTNAfn_BonusExp :
		{
			m_krgVariation[eTNVar_PranaBonus][a_eVarType].iPPlus += a_kEffect.iParam1;
			//if( eAfn_Remove == a_eAdd )
			//{
			//	m_krgVariation[eTNVar_PranaBonus][a_eVarType].iPPlus -= a_kEffect.iParam1;
			//}
			//else m_krgVariation[eTNVar_PranaBonus][a_eVarType].iPPlus += a_kEffect.iParam1;
		}
		break;
	case eTNAfn_LockMaxHP :
		{
			if( eAfn_Remove == a_eAdd )
			{
				m_krgVariation[eTNVar_LockMaxHP][a_eVarType].iPlus = 0;
			}
			else m_krgVariation[eTNVar_LockMaxHP][a_eVarType].iPlus = a_kEffect.iParam1;			

			if( eVar_Skill == a_eVarType ) UpdateHPTP();
		}
		break;
	case eTNAfn_LockMaxTP :
		{
			if( eAfn_Remove == a_eAdd )
			{
				m_krgVariation[eTNVar_LockMaxTP][a_eVarType].iPlus = 0;
			}
			else m_krgVariation[eTNVar_LockMaxTP][a_eVarType].iPlus = a_kEffect.iParam1;			

			if( eVar_Skill == a_eVarType ) UpdateHPTP();
		}
		break;
	case eTNAfn_EnhanceHardnessOfArmor :
		if( eAfn_Remove == a_eAdd )
		{
			if( eTNInAfn_EnhanceHardnessOfArmor & m_iInnerAffections ) m_iInnerAffections =  m_iInnerAffections ^ eTNInAfn_EnhanceHardnessOfArmor;
			m_krgVariation[eTNVar_EnhanceHardnessOfArmor][a_eVarType].iPlus = eConst_EnhanceHardnessOfArmorBase;
		}
		else
		{
			m_iInnerAffections = m_iInnerAffections | eTNInAfn_EnhanceHardnessOfArmor;
			if( eConst_EnhanceHardnessOfArmorBase > a_kEffect.iParam1 ) a_kEffect.iParam1 = eConst_EnhanceHardnessOfArmorBase;
			m_krgVariation[eTNVar_EnhanceHardnessOfArmor][a_eVarType].iPlus = a_kEffect.iParam1;
		}

		break;
	//case eTNAfn_PerfectDodge :
	//	if( eAfn_Remove == a_eAdd )
	//	{
	//		if( eTNInAfn_PerfectDodge & m_iInnerAffections ) m_iInnerAffections =  m_iInnerAffections ^ eTNInAfn_PerfectDodge;
	//	}
	//	else m_iInnerAffections = m_iInnerAffections | eTNInAfn_PerfectDodge;

	//	break;
	case eTNAfn_SkillUp :
		{
			for( int i = 0; i < MAX_SKILL; ++i )
			{
				if( m_krgSkill[i].sID == a_kEffect.iParam1 )
				{
					m_krgSkill[i].byLevelPlus += a_kEffect.iParam2;
					if( 0 > m_krgSkill[i].byLevelPlus ) m_krgSkill[i].byLevelPlus = 0;
					int iSkillIndex = m_krgSkill[i].iIndex;
					if( pSkillData[iSkillIndex].byMaxLevel < (pSkillData[iSkillIndex].byLevel + m_krgSkill[i].byLevelPlus) ) 
						m_krgSkill[i].byLevelPlus = pSkillData[iSkillIndex].byMaxLevel - pSkillData[iSkillIndex].byLevel;

					// client로 skill의 현재 상태(level 상태)를 전송해줘야 한다. 메시지를 새로 정의를 해줘야 한다.
					MSG_SKILL_UP_EFFECT kMsg;
					kMsg.wType = SKILL_UP_EFFECT;
					kMsg.wPDULength = sizeof(MSG_SKILL_UP_EFFECT) - sizeof(HEADER);
					kMsg.snID = m_krgSkill[i].sID;
					kMsg.byLevel = pSkillData[iSkillIndex].byLevel;
					kMsg.byLevelPlus = (byte)m_krgSkill[i].byLevelPlus;

					pUser[m_iHandle].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_SKILL_UP_EFFECT) );

					// 실제 m_krgSkill[i].iIndex는 levelPlus 한 값이야 한다. 그리고 skillData에 대한 index이다. skill을 사용하기 전에 plus 시켜준다.

					break;
				}
			}
		}
		break;
	}
}


// 물리 damage만 막는다.
int CMob::Shield( int a_iDamage )
{
	short sDamageRemained = a_iDamage;
	if( 0 < m_kMagicShield.get_Cur() )
	{
		if( m_kMagicShield.get_Cur() < a_iDamage )
		{
			sDamageRemained = a_iDamage - (short)m_kMagicShield.get_Cur();
			m_kMagicShield.Dec( a_iDamage );

			m_iAffections =  m_iAffections ^ eTNVSAfn_MagicShield;

			#ifdef __TN_3RD_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[Shield] Mob(%d)의 magic shield가 %d damage를 받아 깨졌습니다. m_iAffections:%d \r\n",m_iHandle, a_iDamage, m_iAffections );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_3RD_LOG__
		}
		else
		{
			m_kMagicShield.Dec( a_iDamage );
			#ifdef __TN_3RD_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[Shield] Mob(%d)의 magic shield가 %d damage를 받아냈습니다. 남은 HP는 %d입니다.\r\n", m_iHandle, a_iDamage, m_kMagicShield.get_Cur() );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_3RD_LOG__
			return 0;			
		}
	}

	return sDamageRemained;
}



void CMob::OnHeal( int a_iHP, int a_iFunc, unsigned int a_hHealer )
{ 
	if( eTNImm_Heal & m_iImmunity ) return;

	int nHP = 0;

	if( 0 == a_iFunc )
	{
		if( 0 < MOB.nHP ) nHP = a_iHP; 
	}
	else if( 1 == a_iFunc )
	{
		if( 0 < MOB.nHP ) nHP = a_iHP * ( 1 + pMob[a_hHealer].m_kChakra.sMind / 50 );
	}
	else
		return;

	if( 0 < MOB.nHP )
	{
		nHP += m_krgVariation[eTNVar_HealPlus][eVar_Skill].iPlus;

		IncHP( nHP );

		// party원들에게 HP 상태를 표시
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
			// party원들 유무에 따라서 UpdateStatus 메시지 전달
		}
	}
}


void CMob::OnRecoverTP( int a_iTP, int a_iFunc, unsigned int a_hHealer )
{ 
	int iTP = a_iTP;
	if( 1 == a_iFunc ) iTP = a_iTP * ( 1 + pMob[a_hHealer].m_kChakra.sMind / 50 );

	iTP += m_krgVariation[eTNVar_RecoverTPPlus][eVar_Skill].iPlus;

	IncTP( iTP );
}



void CMob::BroadcastCastSkill( S_CSP_CAST_AREA_SKILL* a_pMsg, int a_iTargetCount )
{
	if( 1 == a_iTargetCount ) // cast unit skill
	{
		a_pMsg->wType = CSP_CAST_UNIT_SKILL;
		a_pMsg->wPDULength = sizeof(S_CSP_CAST_UNIT_SKILL)-sizeof(HEADER);
	}
	else
	{
		a_pMsg->wType = CSP_CAST_AREA_SKILL;
		a_pMsg->wPDULength = sizeof(S_CSP_CAST_AREA_SKILL)-sizeof(HEADER);
	}

	if( 0 >= a_pMsg->snCasterKeyID || MAX_MOB <= a_pMsg->snCasterKeyID ) return; 
	a_pMsg->snCasterX = pMob[a_pMsg->snCasterKeyID].TargetX;
	a_pMsg->snCasterZ = pMob[a_pMsg->snCasterKeyID].TargetY;
	a_pMsg->iCasterHP = pMob[a_pMsg->snCasterKeyID].MOB.nHP;
	a_pMsg->iCasterTP = pMob[a_pMsg->snCasterKeyID].MOB.nTP;
	a_pMsg->iCasterAffections = pMob[a_pMsg->snCasterKeyID].m_iAffections;

	GridMulticast( a_pMsg->snCasterX, a_pMsg->snCasterZ, (MSG_STANDARD*)a_pMsg, -1, 50 );

/*
	if( eTNMob_PC == m_eMobType )
	{
		int iLeader = Leader;
		if( 0 == iLeader ) iLeader = m_iHandle;

		SendPartyMessage( iLeader, (MSG_STANDARD*)a_pMsg );
	}
*/

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char szGeneral[2048] = { 0,0,0, };
		char szTarget[1024] = { 0,0,0, };
		sprintf( szGeneral, "[BroadcastCastSkill] Res:%d> Attacker(Handle:%d, HP:%d, Aff:%d), skillID:%d, uiNow:%u \r\n"
			, a_pMsg->snRes
			, a_pMsg->snCasterKeyID, pMob[a_pMsg->snCasterKeyID].MOB.nHP, (int)pMob[a_pMsg->snCasterKeyID].m_iAffections
			, a_pMsg->snSkillID
			, CurrentTime
			 );
		int iPrintCount = 1;
		if( 1 < a_iTargetCount ) iPrintCount = TN_MAX_TARGET_COUNT;
		for( int i = 0; i < iPrintCount; ++i )
		{
			sprintf( szTarget, "\t- Target%d(Res:%d, H:%d, HP:%d, DMG:%d, Aff:%d)\r\n", i, a_pMsg->krgTarget[i].byRes, a_pMsg->krgTarget[i].snKeyID, a_pMsg->krgTarget[i].iHP, a_pMsg->krgTarget[i].iDamage, (int)a_pMsg->krgTarget[i].iAffection );
			strcat( szGeneral, szTarget );
		}
		WriteLog( szGeneral, m_szLogFile );
	}
	#endif
}


//m_kLastTime.uiAffectionChecked
void CMob::CheckAffections( unsigned int a_uiNow )
{
	if( 0 == m_iAffTop ) return;
	if( IsDead() ) return;

	if( m_kLastTime.uiAffectionChecked > a_uiNow ) return; // 0.5초 이내에는 다시 검사하지 않는다.

	#ifdef __TN_4TH_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );

		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[CheckEffects] %d시%d분%d초(%u), mob(%d, %s)'s Affections: %d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, CurrentTime, m_iHandle, MOB.szName, m_iAffections );
		WriteLog( chBuf, m_szLogFile );
		WriteLog( chBuf, ".\\monster_log\\[Log]Affections.txt" );
	}
	#endif //__TN_4TH_LOG__

	for( int i = 1; i <= m_iLastAff; ++i )
	{
		if( eTNAfn_None == m_krgAffection[i].kEffect.iID ) continue;

		#ifdef __TN_3RD_LOG__
		if( eTNMob_PC == m_eMobType )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "\t Affection ID: %d, Expire: %u, Now: %u, m_iAffections: %d \r\n", m_krgAffection[i].kEffect.iID, m_krgAffection[i].uiExpireTime, CurrentTime, m_iAffections );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_3RD_LOG__

		AffectAffection( i );
		if( m_krgAffection[i].uiExpireTime <= CurrentTime ) RemoveEffect( m_krgAffection[i].kEffect.iID );
	}

	m_kLastTime.uiAffectionChecked = a_uiNow + 500;
}


void CMob::AddEffect( TNEFFECT a_kEffect, int a_iCaster, int a_iPartyLeader )
{
	if( eTNImm_All == m_iImmunity ) return;
	if( (eTNAfn_Damage==a_kEffect.iID) && (eTNImm_Damage & m_iImmunity) ) return;
	if( (eTNAfn_Fire==a_kEffect.iID) && (eTNImm_Fire & m_iImmunity) ) return;
	if( (eTNAfn_Cold==a_kEffect.iID) && (eTNImm_Cold & m_iImmunity) ) return;
	if( (eTNAfn_Lightning==a_kEffect.iID) && (eTNImm_Lightning & m_iImmunity) ) return;
	if( (eTNAfn_Poison==a_kEffect.iID) && (eTNImm_Poison & m_iImmunity) ) return;
	if( (eTNAfn_Hold==a_kEffect.iID) && (eTNImm_Hold & m_iImmunity) ) return;
	if( (eTNAfn_Stun==a_kEffect.iID) && (eTNImm_Stun & m_iImmunity) ) return;
	if( (eTNAfn_Sleep==a_kEffect.iID) && (eTNImm_Sleep & m_iImmunity) ) return;
	if( (eTNAfn_Blind==a_kEffect.iID) && (eTNImm_Blind & m_iImmunity) ) return;
	if( (eTNImm_Heal==a_kEffect.iID) && (eTNImm_Heal & m_iImmunity) ) return;
	if( (eTNAfn_Weakness==a_kEffect.iID) && (eTNImm_Weaken & m_iImmunity) ) return;
	if( (eTNAfn_PreventRegenHP==a_kEffect.iID) && (eTNImm_PreventRegenHP & m_iImmunity) ) return;
	if( (eTNAfn_PreventRegenTP==a_kEffect.iID) && (eTNImm_PreventRegenTP & m_iImmunity) ) return;
	if( (eTNAfn_AttackSpeedMinus==a_kEffect.iID) && (eTNImm_AttackSpeedMinus & m_iImmunity) ) return;
	if( (eTNAfn_MoveSpeedMinus==a_kEffect.iID) && (eTNImm_MoveSpeedMinus & m_iImmunity) ) return;
	if( (eTNAfn_Invisible==a_kEffect.iID) && (eTNVSAfn_HaveKalaCore & m_iAffections) ) return; // kala-core를 가진 상태에서는, 투명이 될 수 없다.
	if( (eTNAfn_MoveSpeedPlus==a_kEffect.iID) && (eTNVSAfn_Invisible & m_iAffections) ) return; // invisible상태에서는 이속 증가가 안된다.
	if( (eTNAfn_Invisible==a_kEffect.iID) && (eTNVSAfn_MoveSpeedPlus & m_iAffections) ) RemoveEffect( eTNAfn_MoveSpeedPlus );// 이속 증가상태에서 invisible을 걸면, 이속이 풀린다.

	int iRes = eTNRes_Succeeded;
	int iAffIndex = get_Affection( a_kEffect.iID );
	if( 0 < iAffIndex )
	{
		iRes = UpdateAffection( a_kEffect, iAffIndex, a_iPartyLeader );
		if( iRes ) return;
	}

	iRes = RegisterAffection( a_kEffect, a_iPartyLeader );
	if( iRes ) return;
	AffectEffect( a_kEffect, eVar_Skill, eAfn_Add, a_iCaster, a_iPartyLeader );
}


//@Return
//	- 0을 리턴하면, 현재의 effect를 affection으로 등록하라는 sub-sequential한 작업이 수반된다. 이것을 막으려면, 1을 리턴하면 된다.
int CMob::UpdateAffection( TNEFFECT& a_kEffect, int a_iAffIndex, int a_iPartyLeader )
{
	if( eTNSklD_Instant == a_kEffect.iDuration ) return 1;

	if( (m_krgAffection[a_iAffIndex].kEffect.kFunc.iData == a_kEffect.kFunc.iData) && (m_krgAffection[a_iAffIndex].kEffect.iParam1 == a_kEffect.iParam1) && (m_krgAffection[a_iAffIndex].kEffect.iParam2 == a_kEffect.iParam2) )
	{	// 완전히 똑같은 스킬이라면, ...(지속시간은 제외한다.)
		unsigned int uiExpireTime = CurrentTime + a_kEffect.iDuration;
		if( m_krgAffection[a_iAffIndex].uiExpireTime < uiExpireTime )
		{
			m_krgAffection[a_iAffIndex].uiExpireTime = uiExpireTime; //	새로운 스킬이 기존의 타임을 연장시킬수 있다면 연장한다.
			m_krgAffection[a_iAffIndex].uiStartTime = CurrentTime;
			m_krgAffection[a_iAffIndex].iPartyLeader = a_iPartyLeader;
		}
		//int nCurrent	= m_krgAffection[a_iAffIndex].uiExpireTime;
		//int nNew		= CurrentTime + a_kEffect.iDuration;
		//if(nNew>=nCurrent) 
		//{	
		//	m_krgAffection[a_iAffIndex].uiExpireTime = nNew;		//	새로운 스킬이 기존의 타임을 연장시킬수 있다면 연장한다.
		//	m_krgAffection[a_iAffIndex].uiStartTime = CurrentTime;
		//	m_krgAffection[a_iAffIndex].iPartyLeader = a_iPartyLeader;
		//}	

		return 1;
	}
	else
	{
		RemoveEffect( a_kEffect.iID );
		return 0;
	}
	return 0;
}


//-----------------------------------------------------
// Visual Affection으로 등록되는 effect만을 제거한다.
//-----------------------------------------------------
void CMob::TurnOffAffection( int a_eID )
{	
	__int64 iAff = ToAbv( a_eID );
	if( !(iAff & m_iAffections) ) return;
		
	RemoveEffect( a_eID );
}


void CMob::RemoveEffect( int a_eAffID )
{	
	__int64 iAff = ToAbv( a_eAffID );
	if( iAff & m_iAffections )
	{
		m_iPrevAffections = m_iAffections;
		m_iAffections =  m_iAffections ^ iAff;
	}
	__int64 iInnerAff = ToAbv2( a_eAffID );
	if( iInnerAff & m_iInnerAffections ) m_iInnerAffections =  m_iInnerAffections ^ iInnerAff;

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );

		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t*[RemoveEffect] Aff:%d, %d시%d분%d초(%d), 기존의Aff:%u, 변경된Aff:%u\r\n"
			, a_eAffID, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, CurrentTime, m_iAffections, m_iAffections ^ iAff );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	if( 0 == m_iAffTop ) return;
	int iAffIndex = get_Affection( a_eAffID );
	if( 0 >= iAffIndex || eConst_MaxAffectionCount < iAffIndex ) return; // 등록되어 있지 않다면, ...

	AffectEffect( m_krgAffection[iAffIndex].kEffect, eVar_Skill, eAfn_Remove, 0, 0, 0 ); // 제거한다.

	--m_iAffTop;
	if( 0 > m_iAffTop )
	{
		#ifdef __TN_3RD_LOG__
		if( 0 != m_iAffections )
		{
			//SYSTEMTIME st;
			//GetLocalTime( &st );

			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "%s's affections : %x\n", MOB.szName, m_iAffections, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
		ClearAffection();
	}
	else
	{
		m_byrgAffection[m_iAffTop] = iAffIndex;
		memset( &(m_krgAffection[iAffIndex]), 0, sizeof(TNAFFECTION) );
		if( iAffIndex == m_iLastAff ) --m_iLastAff;
	}

	BroadcastUpdateStatusMsg();
	NotifyUpdateUIMsg();
}



int CMob::RegisterAffection( TNEFFECT& a_kEffect, int a_iPartyLeader )
{
	if( eTNSklD_Instant >= a_kEffect.iDuration ) return eTNRes_Failed; // instant와 passive effect들은 등록해줄 필요가 없다.
	
	if( 0 > m_iAffTop || eConst_MaxAffectionCount < m_iAffTop ) return eTNRes_Failed;
	int iAffIndex = m_byrgAffection[m_iAffTop];
	if( 0 >= iAffIndex || eConst_MaxAffectionCount < iAffIndex ) return eTNRes_Failed;
	m_byrgAffection[m_iAffTop] = 0;
	++m_iAffTop;

	m_krgAffection[iAffIndex].kEffect = a_kEffect;
	if( iAffIndex > m_iLastAff ) m_iLastAff = iAffIndex;
	m_krgAffection[iAffIndex].uiExpireTime = CurrentTime + a_kEffect.iDuration;
	m_krgAffection[iAffIndex].uiStartTime = CurrentTime;
	m_krgAffection[iAffIndex].iPartyLeader = a_iPartyLeader;

	m_iAffections = m_iAffections | ToAbv( m_krgAffection[iAffIndex].kEffect.iID );
	m_iInnerAffections = m_iInnerAffections | ToAbv2( m_krgAffection[iAffIndex].kEffect.iID );

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[RegisterAffection] 시간%d시%d분%d초> AffID:%d, Dur(%d ~ %d)variation:%d, Dur:%d, PartyLeader:%d \r\n"
			, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_krgAffection[iAffIndex].kEffect.iID, m_krgAffection[iAffIndex].uiStartTime, m_krgAffection[iAffIndex].uiExpireTime
			, m_krgAffection[iAffIndex].kEffect.iParam1, m_krgAffection[iAffIndex].kEffect.iDuration, m_krgAffection[iAffIndex].iPartyLeader );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	return eTNRes_Succeeded;
}


// affection으로 있는 시간 지속 효과 처리
void CMob::AffectAffection( int a_iAffIndex )
{
	if( IsDead() ) return;

	switch( m_krgAffection[a_iAffIndex].kEffect.iID )
	{
	case eTNAfn_Heal :
		{
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			OnHeal( (m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm), m_krgAffection[a_iAffIndex].kEffect.kFunc.iData, m_krgAffection[a_iAffIndex].iPartyLeader );
			BroadcastUpdateStatusMsg( true );			
		}
		break;
	case eTNAfn_RecoverTP :
		{
			if( eTNMob_NPC == m_eMobType ) break;
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			OnRecoverTP( (m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm), m_krgAffection[a_iAffIndex].kEffect.kFunc.iData, m_krgAffection[a_iAffIndex].iPartyLeader );
			BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_DamageTP :
		{
			if( eTNMob_NPC == m_eMobType ) break;
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			int iBurnTP = m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm;
			if( iBurnTP >= MOB.nTP ) iBurnTP = MOB.nTP;
			DecTP( iBurnTP );

			// party원들에게 HP 상태를 표시
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
				// party원들 유무에 따라서 UpdateStatus 메시지 전달
			}
			//MOB.nTP -= iBurnTP;
			//if( 0 > MOB.nTP ) MOB.nTP = 0;
		}
		break;
	case eTNAfn_PercentDamage :
		{
			TNDAMAGE kDamage;
			kDamage.irgPierce[0] = Percent( m_iMaxHP, m_krgAffection[a_iAffIndex].kEffect.iParam1 );
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgPierce[0] = (short)( kDamage.irgPierce[0] * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[물리(방어무시) 지속]%d시%d분%d초, 지속된시간:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPierce[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 3 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_Damage :
		{
			TNDAMAGE kDamage;
			kDamage.irgPhy[0] = PlayDice( m_krgAffection[a_iAffIndex].kEffect.iParam1, m_krgAffection[a_iAffIndex].kEffect.iParam2 );
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgPhy[0] = (short)( kDamage.irgPhy[0] * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[물리 지속]%d시%d분%d초, 지속된시간:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPhy[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 2 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_PierceDamage :
		{
			TNDAMAGE kDamage;
			kDamage.irgPierce[0] = PlayDice( m_krgAffection[a_iAffIndex].kEffect.iParam1, m_krgAffection[a_iAffIndex].kEffect.iParam2 );
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgPierce[0] = (short)( kDamage.irgPierce[0] * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[물리(방어무시) 지속]%d시%d분%d초, 지속된시간:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPierce[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 3 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_Fire :
		{
			short sDamage = 0;
			TNDAMAGE kDamage;
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgFire[0] = (short)( m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[화염 지속]%d시%d분%d초, 지속시간:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__

			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 4 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_Cold :
		{
			short sDamage = 0;
			TNDAMAGE kDamage;			 
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgCold[0] = (short)( m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[냉기 지속]%d시%d분%d초, 지속시간:%d, Raw sDamage:%d\r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 5 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;

	case eTNAfn_Lightning :
		{
			short sDamage = 0;
			TNDAMAGE kDamage;
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgLightning[0] = (short)( m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[전격 지속]%d시%d분%d초, 지속시간:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 6 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;

	case eTNAfn_Poison :
		{
			short sDamage = 0;
			TNDAMAGE kDamage;
			int iTerm = ElapseAffectionTime( a_iAffIndex );
			kDamage.irgPoison[0] = (short)( m_krgAffection[a_iAffIndex].kEffect.iParam1 * iTerm );

			#ifdef __TN_2ND_LOG__
			if( eTNMob_PC == m_eMobType )
			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );

				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[독 지속]%d시%d분%d초, 지속시간:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 7 );
			else BroadcastUpdateStatusMsg( true );
		}
		break;
	case eTNAfn_ManaShield :
		{

		}		
		break;


	default :
		break;
	}
}


unsigned int CMob::ElapseAffectionTime( int a_iAffIndex )
{
	if( 0 >= m_krgAffection[a_iAffIndex].kEffect.iDuration ) return 0;

	unsigned int uiTime = CurrentTime;
	if( uiTime > m_krgAffection[a_iAffIndex].uiExpireTime ) uiTime = m_krgAffection[a_iAffIndex].uiExpireTime;
	unsigned int uiGap = uiTime - m_krgAffection[a_iAffIndex].uiStartTime;
	if( uiGap > (unsigned int)m_krgAffection[a_iAffIndex].kEffect.iDuration ) uiGap = m_krgAffection[a_iAffIndex].kEffect.iDuration;

	unsigned int uiTerm = uiGap / 1000;
	if( 0 < uiTerm ) m_krgAffection[a_iAffIndex].uiStartTime = uiTime - ( uiGap - uiTerm * 1000 );

	return uiTerm;
}



int CMob::get_Affection( int a_eAffID )
{
	if( 0 >= m_iAffTop ) return 0;

	int iLast = m_iLastAff;
	if( eConst_MaxAffectionCount < iLast )
	{
		#ifdef __TN_TOP_LOG__
		{
			//SYSTEMTIME st;
			//GetLocalTime( &st );

			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[get_Affection]%d시%d분%d초, 최대 개수 오류> m_iLastAff:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_iLastAff );
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
		}
		#endif
		iLast = eConst_MaxAffectionCount;
	}
	for( int i = 1; i <= iLast; ++i )
		if( a_eAffID == m_krgAffection[i].kEffect.iID ) return i;

	return 0;
}



void CMob::OnCure( __int64 a_iVisualAffection ) // all : // 41944960
{
	if( eTNVSAfn_Stun & a_iVisualAffection ) RemoveEffect( eTNAfn_Stun );
	if( eTNVSAfn_Blind & a_iVisualAffection ) RemoveEffect( eTNAfn_Blind );
	if( eTNVSAfn_Hold & a_iVisualAffection ) RemoveEffect( eTNAfn_Hold );
	if( eTNVSAfn_Sleep & a_iVisualAffection ) RemoveEffect( eTNAfn_Sleep );
	if( eTNVSAfn_MoveSpeedMinus & a_iVisualAffection ) RemoveEffect( eTNAfn_MoveSpeedMinus ); 
	if( eTNVSAfn_AttackSpeedMinus & a_iVisualAffection ) RemoveEffect( eTNAfn_AttackSpeedMinus );
/*
	if( eTNVSAfn_Hold & a_iVisualAffection ) RemoveEffect( eTNAfn_Hold );
	if( eTNVSAfn_Stun & a_iVisualAffection ) RemoveEffect( eTNAfn_Stun );
	if( eTNVSAfn_Blind & a_iVisualAffection ) RemoveEffect( eTNAfn_Blind );
	if( eTNVSAfn_Hold & a_iVisualAffection ) RemoveEffect( eTNAfn_Hold );
	if( eTNVSAfn_Sleep & a_iVisualAffection ) RemoveEffect( eTNAfn_Sleep );
	if( eTNVSAfn_Hold & a_iVisualAffection ) RemoveEffect( eTNAfn_Hold );
*/
}



__int64 CMob::ToAbv( int a_eAffID )
{
	switch( a_eAffID )
	{
		case eTNAfn_Damage : return eTNVSAfn_Damage;
		case eTNAfn_Fire : return eTNVSAfn_Fire;
		case eTNAfn_Cold : return eTNVSAfn_Cold;
		case eTNAfn_Lightning : return eTNVSAfn_Lightning;
		case eTNAfn_Poison : return eTNVSAfn_Poison;
		case eTNAfn_Invisible : return eTNVSAfn_Invisible;
		case eTNAfn_WizardEyes : return eTNVSAfn_WizardEyes;
		case eTNAfn_Hold : return eTNVSAfn_Hold;
		case eTNAfn_Hold2 : return eTNVSAfn_Hold2; // seidge mode
		case eTNAfn_Stun : return eTNVSAfn_Stun;
		case eTNAfn_Sleep : return eTNVSAfn_Sleep;
		case eTNAfn_Blind : return eTNVSAfn_Blind;
		case eTNAfn_Invulnerable : return eTNVSAfn_Invulnerable;
		case eTNAfn_MagicShield : return eTNVSAfn_MagicShield;
		case eTNAfn_ManaShield : return eTNVSAfn_ManaShield;
		case eTNAfn_Heal : return eTNVSAfn_Heal;
		case eTNAfn_RecoverTP : return eTNVSAfn_RecoverTP;
		case eTNAfn_ReflectDamage : return eTNVSAfn_ReflectDamage;
		case eTNAfn_Weakness : return eTNVSAfn_Weakness;
		//case eTNAfn_PreventRegenHP : return eTNVSAfn_PreventRegenHP;
		//case eTNAfn_FireDamagePlus : return eTNVSAfn_FireDamagePlus;
		//case eTNAfn_ColdDamagePlus : return eTNVSAfn_ColdDamagePlus;
		//case eTNAfn_LightningDamagePlus : return eTNVSAfn_LightningDamagePlus;
		//case eTNAfn_PoisonDamagePlus : return eTNVSAfn_PoisonDamagePlus;
		//case eTNAfn_DefensePlus : return eTNVSAfn_DefensePlus;
		//case eTNAfn_ACPlus : return eTNVSAfn_ACPlus;
		//case eTNAfn_MaxHPPlus : return eTNVSAfn_MaxHPPlus;
		//case eTNAfn_MaxHPPPlus : return eTNVSAfn_MaxHPPPlus;
		//case eTNAfn_MaxTPPlus : return eTNVSAfn_MaxTPPlus;
		case eTNAfn_MoveSpeedPlus : return eTNVSAfn_MoveSpeedPlus;
		case eTNAfn_MoveSpeedMinus : return eTNVSAfn_MoveSpeedMinus;
		case eTNAfn_AttackSpeedPlus : return eTNVSAfn_AttackSpeedPlus;
		case eTNAfn_AttackSpeedMinus : return eTNVSAfn_AttackSpeedMinus;
		//case eTNAfn_DamagePlus : return eTNVSAfn_DamagePlus;
		case eTNAfn_ProtectFromPK : return eTNVSAfn_ProtectFromPK;
		case eTNAfn_ProtectFromMonster : return eTNVSAfn_ProtectFromMonster;
		case eTNAfn_BlessOfGod : return eTNVSAfn_BlessOfGod;
	};

	return eTNVSAfn_Empty;
}


__int64 CMob::ToAbv2( int a_eAffID )
{
	switch( a_eAffID )
	{// inner affection
		case eTNAfn_Taunt : return eTNInAfn_Taunt;
		case eTNAfn_DeTaunt : return eTNInAfn_DeTaunt;
		case eTNAfn_Immunity : return eTNInAfn_Immunity;
		case eTNAfn_Immunity2 : return eTNInAfn_Immunity2;
		case eTNAfn_SpiritLink : return eTNInAfn_SpiritLink;
		case eTNAfn_PreventRegenHP : return eTNInAfn_PreventRegenHP;
		case eTNAfn_PreventRegenTP : return eTNInAfn_PreventRegenTP;
		case eTNAfn_LostTrace : return eTNInAfn_LostTrace;
		case eTNAfn_EnhanceHardnessOfArmor : return eTNInAfn_EnhanceHardnessOfArmor;
		//case eTNAfn_PerfectDodge : return eTNInAfn_PerfectDodge;
			
	};

	return eTNInAfn_Empty;
}



int CMob::Aff2Imm( int a_eAffID )
{
	switch( a_eAffID )
	{// inner affection
		case eTNAfn_Damage : return eTNImm_Damage;
		case eTNAfn_Fire : return eTNImm_Fire;
		case eTNAfn_Cold : return eTNImm_Cold;
		case eTNAfn_Lightning : return eTNImm_Lightning;
		case eTNAfn_Poison : return eTNImm_Poison;
		case eTNAfn_Hold : return eTNImm_Hold;
		case eTNAfn_Stun : return eTNImm_Stun;
		case eTNAfn_Sleep : return eTNImm_Sleep;
		case eTNAfn_Blind : return eTNImm_Blind;
		case eTNAfn_MoveSpeedMinus : return eTNImm_MoveSpeedMinus;
		case eTNAfn_AttackSpeedMinus : return eTNImm_AttackSpeedMinus;
		case eTNAfn_HPDown : return eTNImm_HPDown;
	};

	return 0;
}



void CMob::ClearAffection()
{	
	memset( m_krgAffection, 0, sizeof( m_krgAffection ) );
	memcpy( m_byrgAffection, g_byrgAffection, sizeof( m_byrgAffection ) );
	m_iLastAff = 0;
	m_iAffTop = 0;

	m_iAffections = eTNVSAfn_Empty; 
	m_iInnerAffections = eTNInAfn_Empty;
}



void CMob::RemoveDamageEffect()
{

	RemoveEffect( eTNAfn_Damage );
	RemoveEffect( eTNAfn_Fire );
	RemoveEffect( eTNAfn_Cold );
	RemoveEffect( eTNAfn_Poison );
	RemoveEffect( eTNAfn_Lightning );
}


void CMob::CastOnly( TNSKILL_DATA& a_kSkill )
{
	#ifdef __TN_2ND_LOG__
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "[CastOnly] Mob(%d,%u)가 스킬(%d) cast \r\n", a_kSkill.sID );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_2ND_LOG__

	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		int iID = a_kSkill.krgEffect[i].iID; 
		if( 0 >= iID ) continue;

		#ifdef __TN_2ND_LOG__
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[CastOnly] %d. ID:%d, Dur:%d, Param1:%d, Param2:%d\r\n", i, a_kSkill.krgEffect[i].iID, a_kSkill.krgEffect[i].iDuration, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2 );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_2ND_LOG__

		switch( iID )
		{
		case eTNAfn_Summon  :
			{
				HS2D_COORD krgPos[8];
				int iSize = m_byBodyRadius + m_byBodyRadius + 1;
				if( 0 >= iSize ) return;

				krgPos[0].x = TargetX - ( iSize + m_byBodyRadius );
				krgPos[0].y = TargetY - ( iSize + m_byBodyRadius );
				krgPos[1].x = TargetX - ( m_byBodyRadius );
				krgPos[1].y = TargetY - ( iSize + m_byBodyRadius );
				krgPos[2].x = TargetX + ( m_byBodyRadius + m_byBodyRadius );
				krgPos[2].y = TargetY - ( iSize + m_byBodyRadius );

				krgPos[3].x = TargetX - ( iSize + m_byBodyRadius );
				krgPos[3].y = TargetY - ( m_byBodyRadius );
				krgPos[4].x = TargetX + ( m_byBodyRadius + m_byBodyRadius );
				krgPos[4].y = TargetY - ( m_byBodyRadius );

				krgPos[5].x = TargetX - ( iSize + m_byBodyRadius );
				krgPos[5].y = TargetY + ( m_byBodyRadius + m_byBodyRadius );
				krgPos[6].x = TargetX - ( m_byBodyRadius );
				krgPos[6].y = TargetY + ( m_byBodyRadius + m_byBodyRadius );
				krgPos[7].x = TargetX + ( m_byBodyRadius + m_byBodyRadius );
				krgPos[7].y = TargetY + ( m_byBodyRadius + m_byBodyRadius );

                // 소환할 때

                //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
                int iSummonCount = a_kSkill.krgEffect[i].iParam2; // 소환되는 수
				int iFormation = 0;
				if( 7 < iSummonCount ) iFormation = 1;
				int iIndex = 0;
                for( int iCount = 0; iCount < iSummonCount; ++iCount )
                {
					/*
					int iMob = GetEmptyNPCMob();              
					if( 0 == iMob )
					{
						#ifdef __TN_TOP_LOG__
						{
							char chBuf[256] = { 0,0,0, };
							sprintf(chBuf, "[CastOnly] Summon 실패 > 더이상 monster handle이 남아 있지 않음. \r\n" );
							WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );		
						}
						#endif
						return;
					}
					*/

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

					int iMob = Summon( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2, a_kSkill.krgEffect[i].iDuration
						, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic, m_byClan, 0, x, y, CurrentTarget, false, 0, 0, 4 );

					if( 0 == iMob ) ++iSummonCount;
					if( 30 <= iSummonCount ) break;
                }                			    
			}
			break;

		case eTNAfn_SummonInteractor :
			{
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopFallDown, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic
					, a_kSkill.krgEffect[i].iParam2, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 5 );
			}
			break;
		case eTNAfn_SummonInteractor2 :
			{
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopRaise, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic
					, a_kSkill.krgEffect[i].iParam2, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 5 );
			}
			break;

		case eTNAfn_SummonRetainer :
			{	// 패밀리어 소환					
				if( 0 < m_irgSummoned[eTNCls2_Retainer] ) DeleteMob( m_irgSummoned[eTNCls2_Retainer], 1, 0, eTNPrdt_RemoveNormal, 60 );
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Retainer, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 6 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_LayMine :
			{// 일반존에서만 수행된다.
				if( eZoneType_Normal != g_iZoneType ) return;

				int iMonsterID = a_kSkill.krgEffect[i].iParam1;
				// eTNCls_Summoned일 경우에 어떠한 case를 거치는지 확인해야 한다.
				if( 0 < m_irgSummoned[eTNCls2_Mine] ) DeleteMob( m_irgSummoned[eTNCls2_Mine], 1, 0, eTNPrdt_RemoveNormal, 70 );
				int iMob = Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Mine, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 7 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_LayMine2 :
			{// 주신전 존에서만 동작한다.
				if( eZoneType_God != g_iZoneType ) return;

				if( 0 < m_irgSummoned[eTNCls2_Mine] ) DeleteMob( m_irgSummoned[eTNCls2_Mine], 1, 0, eTNPrdt_RemoveNormal, 80 );
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Mine, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 8 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_SummonPetRandomly :
			{
				int iMonsterID = a_kSkill.krgEffect[i].iParam1;
				// random하게 monster ID가 변경된다. 그럼 어떻게 변경되어야 하는가?



				if( 0 < m_irgSummoned[eTNCls2_Pet] ) DeleteMob( m_irgSummoned[eTNCls2_Pet], 1, 0, eTNPrdt_RemoveNormal, 70 );
				int iMob = Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Pet, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 9 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_SummonPet :
			{
				if( 0 < m_irgSummoned[eTNCls2_Pet] ) DeleteMob( m_irgSummoned[eTNCls2_Pet], 1, 0, eTNPrdt_RemoveNormal, 80 );
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Pet, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 10 );
				if( 0 >= iMob || MAX_MOB <= iMob )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_SummonFailed] );
				}
				else
				{
					
				}
			}
			break;

		case eTNAfn_Illusion  :
			{
				//assert( !"Illusion skill을 구현해야 한다." );
			}
			break;
		} // end of switch
	} // end of for
}


void CMob::UseItem( MSG_ITEM* a_pMsg, int a_iFSMState )
{
	if( eTNFsm_Stand == a_iFSMState )
	{
		if( IsDead() ) return;
	}
	else
	{	char pData[256] = {0,};
		sprintf(pData, "res Resurrect Item Request char:%s", MOB.szName);
		Log( pData, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
		if( IsAlive() ) return;
		if( m_bMoveZone ) return;			//	타존으로 이동해야 할 케릭터가 부활사용시.
	}

	if( NULL == a_pMsg ) return;
	if( eTNClan_GM == m_byClan ) return;
	if( ITEM_PLACE_INVEN != a_pMsg->byPlace ) return;
	if( 0 > a_pMsg->byIndex || MAX_INVEN <= a_pMsg->byIndex ) return;
	if( 0 >= MOB.Inven[a_pMsg->byIndex].snIndex ) return;
	if( 0 >= MOB.Inven[a_pMsg->byIndex].byCount ) return;
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return;

	BYTE byMax = 0; int nItemIndex = MOB.Inven[a_pMsg->byIndex].snIndex+HT_PARAMTYPE_ITEM_START-1;
	TNITEM_DATA kItem = pItemData[MOB.Inven[a_pMsg->byIndex].snIndex];
	if(kItem.krgEffect[0].iID==eTNAfn_TownPortal)
		if(!IsUsablePustica(kItem.krgEffect[0].iParam1, kItem.krgEffect[0].iParam2, a_pMsg->snWarpID)) return;

	if(nItemIndex == eItm_SummonParty)
	{	if(eWaitAct_TownPortal == m_kWaitAction.iAction) return;
		//if(eWaitAct_TownPortal2 == m_kWaitAction.iAction) return;
		//if(eWaitAct_TownPortal3 == m_kWaitAction.iAction) return;
	}	else
	if(nItemIndex == eItem_Pt4 || (nItemIndex>=6737 && nItemIndex<=6741))
	{	int nEmpty = GetEmptyInvenCount(m_iHandle);
		if(nEmpty<8) return;
	}	else
	if(nItemIndex == eItem_InitQuest1)
	{
		if(MOB.byQuest[51] != 0) return;	//	퀘스트초기화아이템1은 k3시나리오 퀘스트가 진행이된 상태이면 사용할수없다.
	}

	if( (eItem_Resurrect80 == nItemIndex) || (eItem_Resurrect100 == nItemIndex) || (7078 == nItemIndex) )
	{ // duel field에서는 부활주문서(80%, 100%)를 사용할 수 없다.
		if( 0 >= TargetY || MAX_GRIDY <= TargetY ) return;
		if( 0 >= TargetX || MAX_GRIDX <= TargetX ) return;
		if( eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty ) return;
	}

	//short snDay = 0;
	bool bRet = true;
	bRet = g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMax );
	//bRet &= g_ParamMgr.HT_bGetItemTimeLimit(nItemIndex, &snDay);
	if(!bRet)
	{	SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
		return;
	}
	if(MOB.Inven[a_pMsg->byIndex].byCount>byMax) MOB.Inven[a_pMsg->byIndex].byCount=byMax;

	bool bWriteLog = false;
	bool bIsMonsterScroll = false;
	if( eItem_MonsterScroll == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID || eItem_MonsterScroll2 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) // 요술램프 아이템
	{		
		if( eZone_Pamir != g_iZoneID ) //파미르 지역이 아니라면, 사용할 수 없다고 client에 메시지를 전송해준다.
		{
			SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictToUseaSummonScroll] );
			return;
		}
		bIsMonsterScroll = true;
		bWriteLog = true;
	}

	if( (6729 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID) 
		|| (6734 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID)
		|| (6735 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID)
		) // 칼리아 툰데라 소환 아이템
	{		
		if( eZone_Pamir != g_iZoneID ) //파미르 지역이 아니라면, 사용할 수 없다고 client에 메시지를 전송해준다.
		{
			SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictToUseaSummonScroll] );
			return;
		}
		bWriteLog = true;

		//{
		//	char chBuf[256] = { 0,0,0, };
		//	sprintf(chBuf, "[UseItem] Item ID:%d who:%d,%s\r\n"
		//		, pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		//		, m_iHandle, MOB.szName );
		//	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
		//}
	}


	if( (6731 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID) 
		) 
	{		
		if( eZone_Katacomb != g_iZoneID ) //북두성군 지역이 아니라면, 사용할 수 없다고 client에 메시지를 전송해준다.
		{
			SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictToUseaItemAt12] );
			return;
		}
		bWriteLog = true;

		//{
		//	char chBuf[256] = { 0,0,0, };
		//	sprintf(chBuf, "[UseItem] Item ID:%d who:%d,%s\r\n"
		//		, pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		//		, m_iHandle, MOB.szName );
		//	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
		//}
	}


	if( bWriteLog )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[UseItem] %d월%d일 %d시%d분%d초 > Item ID:%d who:%d,%s\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
			, m_iHandle, MOB.szName );
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
	}


/*
	if( (6729 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID) 
		) 
	{		
		if( eZone_Castle != g_iZoneID ) //비류성 지역이 아니라면, 사용할 수 없다고 client에 메시지를 전송해준다.
		{
			SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictToUseaItemAt17] );
			return;
		}
	}
*/

	if( pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].kCost.sItemID )
	{
		if( kItem.krgEffect[0].iID==eTNAfn_TownPortal && eTNVSAfn_HaveKalaCore & m_iAffections ) return; // kala-core를 가지고 있으면, town portal을 동작하지 못하게 한다.
		if( kItem.krgEffect[0].iID==eTNAfn_TownPortal2 && eTNVSAfn_HaveKalaCore & m_iAffections ) return; // kala-core를 가지고 있으면, town portal을 동작하지 못하게 한다.

		//int iCoolDownSlot = 0;
		int iCoolDownSlot = pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sItemType;
		if( 0 < pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].iAttackSpeed ) // cool-down 시간이 있는 item
		{
			#ifdef __DYNAMIC_LOG__
			if( m_iDebugFlag )
			{
				char chBuf[256] = { 0,0,0, };
				sprintf(chBuf, "[UseItem] Item ID:%d, CoolDownTime:%d, Now:%d, TimeCooled:%d \r\n", pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID, pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].iAttackSpeed, CurrentTime, m_uirgInstantCoolDownTime[iCoolDownSlot] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //#ifdef __DYNAMIC_LOG__	
			if( 0 >= iCoolDownSlot || eConst_MaxInstantCoolDonw <= iCoolDownSlot ) return;
			if( CurrentTime < m_uirgInstantCoolDownTime[iCoolDownSlot] ) return;
			
		}
		int iUseResult = eTNRes_Succeeded;

		//if(snDay>0)		//	기간제 아이템
		//{	int nIndex = nItemIndex - HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START;
		//	if(nIndex>0 || nIndex<MAX_TIMEITEM)
		//	{
		//		time_t now; time(&now);
		//		if(now>pUser[m_iHandle].m_time[nIndex])
		//		{	pUser[m_iHandle].m_time[nIndex] = now+snDay*24*3600;			//	사용기간이 만료된 아이템은 현재일을 기준으로 날자를 추가한다
		//		}	else
		//		{	pUser[m_iHandle].m_time[nIndex] += snDay*24*3600;				//	사용기간이 만료되지 않은 아이템구매시 만기날자에 추가한다.
		//		}
		//	} 
		//}

		if(!bRet)	//	ID가 잘못된 기간제 아이템이거나 파라메터정보가 없는 경우
		{
			SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
			return;	
		}
	
		m_snResurrect = a_pMsg->snWarpID;			//	부활의 경우 부활위치설정(아이템부활은 위치설정가능)
		if( eTNCPhase_OnTakeInstant1 & kItem.sCombatPhase ) OnTakeInstant1( m_iHandle, kItem ); // 시체관련
		if( eTNCPhase_OnTakeInstant2 & kItem.sCombatPhase ) iUseResult = OnTakeInstant2( m_iHandle, kItem, 0 ); // 순간적으로 작용할 것들
		if( eTNCPhase_OnChargInstance & kItem.sCombatPhase ) OnChargInstance(kItem);
		if( eTNCPhase_OnAffect & kItem.sCombatPhase ) OnTakeAffections( kItem, 0, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
		if( eTNCPhase_StartAction & kItem.sCombatPhase ) iUseResult = StartAction( m_iHandle, kItem, 0 );
		if( eTNCPhase_CastOnly & kItem.sCombatPhase ) CastOnly( kItem );
		m_snResurrect = RESURRECT_TYPE_PRESENT;		//	부활의 경우 부활위치설정(아이템 이외에는 현위치부활)
		
		
		if( bIsMonsterScroll ) // 요술램프 아이템(몬스터 주문서)인 경우
		{
			/*
			// deck에서 monster card 한장을 꺼낸다.
			int iMonsterIndex = g_kMonsterScroll.Random();
			if( 0 > iMonsterIndex || eMon_CountOfMonsterToBeSummon <= iMonsterIndex )
			{
				// 에러 로그를 남긴다.
				iMonsterIndex = 0;
			}
			int iMonsterID = g_irgMonsterToBeSummon[iMonsterIndex];
			*/
			int iMonsterID = 0;
			if( eItem_MonsterScroll2 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[1].DrawMonsterCard();
			else iMonsterID = g_krgMagicLamp[0].DrawMonsterCard();

			int iMonsterHandle = pMob[m_iHandle].Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Basic, eTNClan_Neutral, 0, TargetX, TargetY, 0, false, 0, 0, 9 );
			if( MAX_USER > iMonsterHandle || MAX_MOB <= iMonsterHandle )
			{ // 몬스터 소환에 실패를 한 것이다. item을 사용하지 않은 것으로 생각한다.
				iUseResult = eTNRes_Failed;
				return;
			}
		}
		

		if( eTNRes_Succeeded == iUseResult )
		{// 성공적으로 item을 사용 => cooldown을 적용, 개수를 1개 줄인다.
			m_uirgInstantCoolDownTime[iCoolDownSlot] = CurrentTime + pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].iAttackSpeed;
			--MOB.Inven[a_pMsg->byIndex].byCount;
			if( bWriteLog ) WriteLog( " successed!", g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
		}

		if( (1 == iCoolDownSlot) || (2 == iCoolDownSlot) || (20 == iCoolDownSlot) ) // HP/TP potion일 경우
		{	// party원들에게 HP 상태를 표시
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
				// party원들 유무에 따라서 UpdateStatus 메시지 전달
			}
		}

		a_pMsg->snUserKeyID = m_iHandle;
		a_pMsg->byResult = eTNRes_Succeeded;
		a_pMsg->kItem = MOB.Inven[a_pMsg->byIndex];

		int idFX = 0;
		if ( g_ParamMgr.HT_bGetItemFXEffectID(nItemIndex, &idFX ) && idFX > 0 )
		{
			a_pMsg->byType = eItem_Brd;
			GridMulticast(TargetX, TargetY, (MSG_STANDARD *)a_pMsg, 0, 100);
		}	else
		{
			pUser[m_iHandle].cSock.AddMessage((char*)a_pMsg, sizeof(*a_pMsg));
		}

		//GridMulticast( TargetX, TargetY, (MSG_STANDARD*)a_pMsg, -1 );
		if( 0 >= MOB.Inven[a_pMsg->byIndex].byCount ) ZeroMemory(&MOB.Inven[a_pMsg->byIndex], sizeof(STRUCT_ITEM));// MOB.Inven[a_pMsg->byIndex].snIndex = 0;

		NotifyUpdateUIMsg();
		BroadcastUpdateStatusMsg();
		pUser[m_iHandle].cSock.SendMessage();

		char temp[256] = {0,};
		char strItem[128] = {0,};	// 아이템 사용 로그...
		if (BASE_CheckItemLog(&a_pMsg->kItem))
		{	BASE_GetItemCode(&a_pMsg->kItem,strItem);
			sprintf(temp,"use %s",strItem);
			Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
		}
	}
}

int CMob::Regen( double a_dPercent, byte byType)	//	type 0 : regen,   type 1 : resurrect
{
	if( IsAlive() ) return eTNRes_Failed;
	if( MAX_USER <= m_iHandle ) return eTNRes_Failed; // npc(or monster)일 경우는 skip
	if( eTNMob_PC != m_eMobType ) return eTNRes_Failed;
	if( 0 > a_dPercent || 100 < a_dPercent ) return eTNRes_Failed;

	char pData[256] = {0,};
	sprintf(pData, "reg char:%s Type:%d Place:%d SaveZone:%d SX:%d SZ:%d", MOB.szName, byType, m_snResurrect, MOB.bySaveZone, MOB.snSaveX, MOB.snSaveZ);
	Log( pData, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;

	int nServerIndex = ServerIndex+1;
	if(byType==REGEN_TYPE_REGEN || m_snResurrect==RESURRECT_TYPE_SAVE)
	{	
		if(MOB.bySaveZone==0)
		{
			if(nServerIndex==1 || nServerIndex==18 || nServerIndex==19)
			{
				m_snResurrect = RESURRECT_TYPE_TOWN;
				Resurrect(a_dPercent, 50);
			}
			else
			{
				sm.byZone=1;
				pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return eTNRes_Succeeded;

				int iDecPrana = m_iPranaDec;
				double dPrana = a_dPercent / 100;
				AcquirePrana( (int)(iDecPrana * dPrana) );

				m_kWaitAction.iAction = eWaitAct_ZonePortal;
				m_bMoveZone = true;
			}
		}
		else if(MOB.bySaveZone!=(ServerIndex+1))  // 저장지역이 기억되어 있는데, 그 위치가 다른 zone이다.
		{
			int nSave=MOB.bySaveZone;
			if(MOB.byLevel<TRIMURITY_LEVEL_LOW && (nSave==SERVER_KRUMA_LOW || nSave==SERVER_KRUMA_HIGH || nSave==SERVER_CHATURANGKA))
			{	if(ServerIndex+1 == 1)
				{	m_snResurrect = RESURRECT_TYPE_TOWN;
					Resurrect(a_dPercent, 50);
				}	else
				{	MOB.byZone=1; MOB.snX=-1; MOB.snZ=-1;
					MOB.bySaveZone=0; sm.byZone = 1;
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return eTNRes_Succeeded;

					int iDecPrana = m_iPranaDec;
					double dPrana = a_dPercent / 100;
					AcquirePrana( (int)(iDecPrana * dPrana) );

					m_kWaitAction.iAction = eWaitAct_ZonePortal;
					m_bMoveZone = true;
				}
			}	else
			{	if((ServerIndex==0 || ServerIndex==17 || ServerIndex==18) && (nSave==1 || nSave==18 || nSave==19))
				{	
					if(byType==REGEN_TYPE_REGEN)
					{
						m_snResurrect = RESURRECT_TYPE_TOWN;
						Resurrect(a_dPercent, 50);
					}
					else
					{
						m_snResurrect = RESURRECT_TYPE_SAVE;
						Resurrect(a_dPercent, 20);
					}
				}	else
				{	char pch[128] = {0,};
					sprintf(pch, "Char:%s x:%d y:%d move to x:%d y:%d by regen position and zone",
						MOB.szName, TargetX, TargetY, MOB.snSaveX, MOB.snSaveZ);
					Log( pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
						
					sm.byZone = nSave; MOB.byZone=nSave; 
					TargetX=MOB.snSaveX; TargetY=MOB.snSaveZ;
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 

					int iDecPrana = m_iPranaDec;
					double dPrana = a_dPercent / 100;
					AcquirePrana( (int)(iDecPrana * dPrana) );
					MOB.nHP = Percent( m_iMaxHP, 50 );
					MOB.nTP = Percent( m_iMaxTP, 50 );

					m_kWaitAction.iAction = eWaitAct_ZonePortal;
					m_bMoveZone = true;

					return eTNRes_Succeeded;
				}
			}
		}
		else
		{	if(MOB.byLevel<TRIMURITY_LEVEL_LOW && (MOB.bySaveZone==SERVER_KRUMA_LOW || MOB.bySaveZone==SERVER_KRUMA_HIGH || MOB.bySaveZone==SERVER_CHATURANGKA))
			{
				MOB.byZone=1; MOB.snX=-1; MOB.snZ=-1;
				MOB.bySaveZone=0; sm.byZone = 1;
				pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return eTNRes_Succeeded;

				int iDecPrana = m_iPranaDec;
				double dPrana = a_dPercent / 100;
				AcquirePrana( (int)(iDecPrana * dPrana) );

				m_kWaitAction.iAction = eWaitAct_ZonePortal;
				m_bMoveZone = true;
			}	else
			{	m_snResurrect = RESURRECT_TYPE_SAVE;
				Resurrect(a_dPercent, 20);
			}
		}
	}
	else if(byType==REGEN_TYPE_ARENA)
	{
		m_snResurrect = RESURRECT_TYPE_ARENA;
		Resurrect(0, 20);
	}
	else if(byType==REGEN_TYPE_CASTLE1)
	{
		m_snResurrect = RESURRECT_TYPE_PORTAL;
		Resurrect(0, 20, ePortal_CastleW);	//	현재 지역에서의 부활함수이므로 포탈이 현재의 존에 잇어야 한다.
	}
	else if(byType==REGEN_TYPE_CASTLE2)
	{
		m_snResurrect = RESURRECT_TYPE_PORTAL;
		Resurrect(0, 20, ePortal_CastleN);	//	현재 지역에서의 부활함수이므로 포탈이 현재의 존에 잇어야 한다.
	}
	else
	{
		m_snResurrect = RESURRECT_TYPE_PRESENT;
		Resurrect(a_dPercent, 20);
	}

	return eTNRes_Succeeded;
}

//	현재 존에서의 부활을 진행하는 함수이다.
void CMob::Resurrect( double a_dPercent, int nRecoverry, int iPortal)
{
	if(a_dPercent<0) a_dPercent = 0;
	if(a_dPercent>100) a_dPercent = 100;
	if(nRecoverry<0) nRecoverry = 0;
	if(nRecoverry>100) nRecoverry = 100;

	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;
	sm.byZone = ServerIndex+1;

	//	리젠시 파라메터 세팅을 한다.
	int iDecPrana = m_iPranaDec;
	int nX = 0; int nZ = 0; int tx=0; int ty=0;

	MOB.nHP = Percent( m_iMaxHP, nRecoverry );
	MOB.nTP = Percent( m_iMaxTP, nRecoverry );

	Init( m_iHandle );

	MOB.byZone = ServerIndex+1;				//	사망시 savezone으로 된 정보를 현재의 존으로 바꿔준다.
	//pUser[m_iHandle].LastAction	= m->dwClientTick;
	Direction	= 0;
	State		= 1;


	if(m_snResurrect==RESURRECT_TYPE_SAVE)
	{
		nX = MOB.snSaveX; nZ = MOB.snSaveZ;
	}
	else if(m_snResurrect==RESURRECT_TYPE_PRESENT)
	{
		nX = TargetX; nZ = TargetY;
	}
	else if(m_snResurrect==RESURRECT_TYPE_TOWN)
	{
		GetTrimurityArea(m_iHandle, nX, nZ);
	}	
	else if(m_snResurrect==RESURRECT_TYPE_ARENA)
	{	
		GetArenaArea(m_iHandle, nX, nZ);
	}	
	else if(m_snResurrect==RESURRECT_TYPE_PORTAL)
	{
		bool bRet = true;
		DWORD dwServerID, dwZoneLevel;
		short snStartX, snStartZ, snEndX, snEndZ;
		bRet = g_ParamMgr.HT_bGetPortalInfo(iPortal, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ);
		if(!bRet || (dwServerID-40000)!=(ServerIndex+1))	//	포탈정보가 잘못되엇거나 현재의 존이아닌 포탈의 경우 젠지역에서 부활시킨다.
			GetTrimurityArea(m_iHandle, nX, nZ);
		else
		{
			nX = GetRandom(snStartX, snEndX);
			nZ = GetRandom(snStartZ, snEndZ);
		}
	}
	else
	{
		char pData[256] = {0,};
		sprintf(pData, "res resurrect char:%s Type:%d TargetX:%d TargetY:%d ", MOB.szName,m_snResurrect,TargetX,TargetY);
		Log( pData, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
	}

	PickFreeMobGrid( m_iHandle, &nX, &nZ );
	tx = nX; ty = nZ;

	//	REGEN PACKET 정보를 채운다.
	sm.byWhether = 0;	
	sm.dwGameTime = 0;	sm.nCurHP = MOB.nHP;
	sm.snX=tx; sm.snZ=ty;
	sm.snDegree = 0;

	pUser[m_iHandle].cSock.AddMessage((char*)&sm,sizeof(sm));	

	if(m_snResurrect!=RESURRECT_TYPE_PRESENT)
	{
		if(m_iHandle>0 && m_iHandle<MAX_USER) 
		{
			pUser[m_iHandle].nPreX = tx; pUser[m_iHandle].nPreY = ty;
		}

		//	나의 이동을 주위케릭에게 알리고, 주위 정보를 가져온다.
		MSG_Action nm; nm.wType = _MSG_Action;
		nm.wPDULength = sizeof(nm)-sizeof(HEADER);
		nm.TargetX=tx; nm.TargetY= ty;
		nm.dwKeyID = m_iHandle; nm.PosX=0; nm.PosY=0;
		nm.Direction = 0; nm.Effect = 5;
		GridMulticast(m_iHandle,tx,ty,(MSG_STANDARD*)&nm,50);
	}

	double dPrana = a_dPercent / 100;
	AcquirePrana( (int)(iDecPrana * dPrana) );
	ProcessContinuousEffect();

	m_iPranaDec = m_byDecPranaRate = m_byKillLevel = 0;		//	프라나보상관련 변수들 초기화(이미 보상은 나갓다)

	// 내 정보를 주위의 mob들에게 전송한다.
	S_SCP_INIT_OTHER_MOB sOther;
	GetCreateMob(m_iHandle,&sOther); 
	GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,m_iHandle,100);
	// 주위 정보를 가져온다.
	SendGridMob(m_iHandle);
	pUser[m_iHandle].cSock.SendMessage();

	//	파티원에게 hp회복을 알린다
	S_SCP_RESP_UPDATE_PARTY pm; pm.wType=SCP_RESP_UPDATE_PARTY;
	pm.wPDULength=sizeof(pm)-sizeof(HEADER);
	pm.Party.nCurHP=MOB.nHP; pm.Party.nCurTP=MOB.nTP;
	pm.Party.byLevel=MOB.byLevel; pm.Party.nMaxHP=m_iMaxHP;
	pm.Party.nMaxTP=m_iMaxTP; pm.Party.nID=m_iHandle;
	pm.Party.nAffections=m_iAffections;
	strncpy(pm.Party.Name,MOB.szName,SZNAME_LENGTH);

	int nLeader=0;
	if(Leader==0) nLeader=m_iHandle;
	else nLeader=Leader;

	SendPartyMessage(nLeader, (MSG_STANDARD*)&pm);

	char pData[256] = {0,};
	sprintf(pData, "res resurrect char:%s Prana:%d MaxHP:%d HP:%d MaxTP:%d TP:%d TargetX:%d TargetY:%d ", MOB.szName,MOB.nPrana,m_iMaxHP,MOB.nHP,m_iMaxTP,MOB.nTP,TargetX,TargetY);
	Log( pData, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );

	m_snResurrect = RESURRECT_TYPE_PRESENT;

	return;
}

void CMob::ProgressWaitAction()
{
	if( eWaitAct_None == m_kWaitAction.iAction ) return;
	if( eWaitAct_ZonePortal == m_kWaitAction.iAction ) return;

	if( m_kWaitAction.uiWaitingTime < CurrentTime )
	{		
		switch( m_kWaitAction.iAction )
		{
		case eWaitAct_TownPortal :
			{			
				int x = 0; int y = 0;
				if(m_snMovePortal == ePortal_Gen)
				{
					GetTrimurityArea(m_iHandle, x, y);
					int tret = PickFreeMobGrid(m_iHandle,&x,&y);
					if	(tret==FALSE) break;

					if(m_iHandle>0 && m_iHandle<MAX_USER) 
					{
						pUser[m_iHandle].nPreX = x; pUser[m_iHandle].nPreY = y;
					}

					MSG_Action sm;
					GetAction(m_iHandle,x,y,&sm);
					sm.Effect = 5;
					if( 0 < m_iHandle && MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.AddMessage((char*)&sm,sizeof(sm));
					GridMulticast(m_iHandle,x,y,(MSG_STANDARD*)&sm,100,ACTION_WARP);

					char pch[256] = {0,};
					sprintf(pch, "Char:%s move to town completed by pustica", MOB.szName);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

					break;
				}
				else if(m_snMovePortal == ePortal_Ziva)
				{
					byte byTrimuriti = MOB.byTrimuriti;
					if( 4 == byTrimuriti ) byTrimuriti = 3;
					if( eTNClan_GM == byTrimuriti ) byTrimuriti = eTNClan_Brahma; 
					if( 0 > byTrimuriti || 3 < byTrimuriti ) break;

					pMob[m_iHandle].m_kWaitAction.iAction = eWaitAct_ZonePortal;

					MSG_MoveOtherZone sm; sm.wType=_MSG_MoveOtherZone;
					sm.byType=CONNECT_TYPE_PUSTICA; sm.snPositionID=m_snSaveNPC;
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));

					char pch[256] = {0,};
					sprintf(pch, "Char:%s move to npc:%d completed by pustica", MOB.szName, m_snSaveNPC);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

					return;
				}

				byte byTrimuriti = MOB.byTrimuriti;
				if( 4 == byTrimuriti ) byTrimuriti = 3;
				if( eTNClan_GM == byTrimuriti ) byTrimuriti = eTNClan_Brahma; 
				if( 0 > byTrimuriti || 3 < byTrimuriti ) break;
			
				bool bRet=true;
				DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
				BYTE byMoveZone = 0;

				if(m_snMovePortal == ePortal_Memorized)
				{
					byMoveZone = pUser[m_iHandle].m_byZone;
					snStartX = snEndX = pUser[m_iHandle].m_snMemX;
					snStartZ = snEndZ = pUser[m_iHandle].m_snMemY;
				}	else
				{	bRet &= g_ParamMgr.HT_bGetPortalInfo( m_snMovePortal, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );			
					if(!bRet) 
					{	m_kWaitAction.iAction = eWaitAct_None;
						SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
						break;
					}
					byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
				}



				if(byMoveZone==ServerIndex+1)
				{	short snX=GetRandom(snStartX, snEndX); short snZ=GetRandom(snStartZ, snEndZ);
					if  (snX<=0 || snX>=MAX_GRIDX || snZ<=0 || snZ>=MAX_GRIDY)
					{	Log("err eWaitAct_TownPortal3 - viewgrid", MOB.szName,pUser[m_iHandle].IP);
						break;
					}

					MSG_Action nm; nm.wType = _MSG_Action;
					nm.wPDULength = sizeof(nm)-sizeof(HEADER);
					nm.TargetX=snX; nm.TargetY= snZ;
					nm.dwKeyID = m_iHandle; nm.PosX=0; nm.PosY=0;
					nm.Direction = 0; nm.Effect = 5;
					nm.Speed=0;

					if  (pUser[m_iHandle].Mode!=USER_PLAY) break;
					if  (IsDead()) break;

					if	(pMobGrid[snZ][snX]!=0 && pMobGrid[snZ][snX] != m_iHandle)
					{	int x=snX;
						int z=snZ;
						int tret = PickFreeMobGrid(m_iHandle,&x,&z);
						if	(tret==FALSE)
						{	Log("err too many people near start point => 10",pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
							SendClientMessage(m_iHandle,g_pMessageStringTable[_Not_Find_Empty_Position]); break;
						}
						snX = x; snZ = z; nm.TargetX=snX; nm.TargetY= snZ;
					}

					int lastx = snX;
					int lasty = snZ;
					Direction	= 0;
					State		= 1;

					if(m_iHandle>0 && m_iHandle<MAX_USER) 
					{
						pUser[m_iHandle].nPreX = snX; pUser[m_iHandle].nPreY = snZ;
					}

					pUser[m_iHandle].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
					GridMulticast(m_iHandle,snX,snZ,(MSG_STANDARD*)&nm);

					char pch[256] = {0,};
					if(m_snMovePortal == ePortal_Memorized)
					{	sprintf(pch, "Char:%s move to Memorized place completed by pustica", MOB.szName);
					}	else
					{	sprintf(pch, "Char:%s move to portal:%d completed by pustica", MOB.szName, m_snMovePortal);
					}
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
				else
				{	if(byMoveZone==SERVER_KRUMA_LOW)
					{	int iSkillPointUsed = 0; 
						for( int i = 0; i < 65; ++i ) iSkillPointUsed += MOB.bySkill[i];
						for( int i = 80; i < MAX_SKILL; ++i ) iSkillPointUsed += MOB.bySkill[i];
						short snChakra = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
						if(snChakra>355 || iSkillPointUsed>63) return;	//	차크라합이 355보다 크거나 스킬포인트가 63보다 클시에는 저랩크루마지역에 출입불가요청(2005.11.25)
					}
										
					S_SCP_RESP_MOVE_PORTAL sm; ZeroMemory(&sm, sizeof(sm));
					sm.wType=SCP_RESP_MOVE_PORTAL;
					sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; sm.byZone=byMoveZone;
					sm.nMoney=pMob[m_iHandle].MOB.nRupiah;
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));

					m_kWaitAction.iAction = eWaitAct_ZonePortal;

					char pch[256] = {0,};
					if(m_snMovePortal == ePortal_Memorized)
					{	pUser[m_iHandle].m_byCloseType = eCloseMemorized;
						sprintf(pch, "Char:%s move to Memorized place completed by pustica", MOB.szName);
					}	else
					{	sprintf(pch, "Char:%s move to portal:%d completed by pustica", MOB.szName, m_snMovePortal);
					}
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

					return;
				}
			}
			break;
		//case eWaitAct_TownPortal2 :
		//	{				
		//		byte byTrimuriti = MOB.byTrimuriti;
		//		if( 4 == byTrimuriti ) byTrimuriti = 3;
		//		if( eTNClan_GM == byTrimuriti ) byTrimuriti = eTNClan_Brahma; 
		//		if( 0 > byTrimuriti || 3 < byTrimuriti ) break;

		//		MSG_MoveOtherZone sm; sm.wType=_MSG_MoveOtherZone;
		//		sm.byType=CONNECT_TYPE_PUSTICA; sm.snPositionID=m_snSaveNPC;
		//		pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		//		//int x = PlayDice(TrimurityArea.pArea[byTrimuriti][0].snStartX, TrimurityArea.pArea[byTrimuriti][0].snEndX);
		//		//int y = PlayDice(TrimurityArea.pArea[byTrimuriti][0].snStartZ, TrimurityArea.pArea[byTrimuriti][0].snEndZ);
		//		//int tret = PickFreeMobGrid(m_iHandle,&x,&y);
		//		//if	(tret==FALSE) break;

		//		//MSG_Action sm;
		//		//GetAction(m_iHandle,x,y,&sm);
		//		//sm.Effect = 5;
		//		//if( 0 < m_iHandle && MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.AddMessage((char*)&sm,sizeof(sm));
		//		//GridMulticast(m_iHandle,x,y,(MSG_STANDARD*)&sm,50,ACTION_WARP);
		//	}
		//	break;
		//case eWaitAct_TownPortal3 :
		//	{				
		//		byte byTrimuriti = MOB.byTrimuriti;
		//		if( 4 == byTrimuriti ) byTrimuriti = 3;
		//		if( eTNClan_GM == byTrimuriti ) byTrimuriti = eTNClan_Brahma; 
		//		if( 0 > byTrimuriti || 3 < byTrimuriti ) break;
		//	
		//		bool bRet=true;
		//		DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
		//		bRet &= g_ParamMgr.HT_bGetPortalInfo( m_snMovePortal, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );			
		//		if(!bRet) 
		//		{	m_kWaitAction.iAction = eWaitAct_None;
		//			SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
		//			return;
		//		}

		//		BYTE byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
		//		if(byMoveZone==ServerIndex+1)
		//		{	short snX=GetRandom(snStartX, snEndX); short snZ=GetRandom(snStartZ, snEndZ);
		//			if  (snX<=0 || snX>=MAX_GRIDX || snZ<=0 || snZ>=MAX_GRIDY)
		//			{	Log("err eWaitAct_TownPortal3 - viewgrid", MOB.szName,pUser[m_iHandle].IP);
		//				return;
		//			}

		//			MSG_Action nm; nm.wType = _MSG_Action;
		//			nm.wPDULength = sizeof(nm)-sizeof(HEADER);
		//			nm.TargetX=snX; nm.TargetY= snZ;
		//			nm.dwKeyID = m_iHandle; nm.PosX=0; nm.PosY=0;
		//			nm.Direction = 0; nm.Effect = 5;
		//			nm.Speed=0;

		//			if  (pUser[m_iHandle].Mode!=USER_PLAY) return;
		//			if  (IsDead()) return;

		//			if	(pMobGrid[snZ][snX]!=0 && pMobGrid[snZ][snX] != m_iHandle)
		//			{	int x=snX;
		//				int z=snZ;
		//				int tret = PickFreeMobGrid(m_iHandle,&x,&z);
		//				if	(tret==FALSE)
		//				{	Log("err too many people near start point => 10",pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
		//					SendClientMessage(m_iHandle,g_pMessageStringTable[_Not_Find_Empty_Position]); return;
		//				}
		//				snX = x; snZ = z; nm.TargetX=snX; nm.TargetY= snZ;
		//			}

		//			int lastx = snX;
		//			int lasty = snZ;
		//			Direction	= 0;
		//			State		= 1;

		//			if(m_iHandle>0 && m_iHandle<MAX_USER) 
		//			{
		//				pUser[m_iHandle].nPreX = snX; pUser[m_iHandle].nPreY = snZ;
		//			}

		//			pUser[m_iHandle].cSock.AddMessage((char*)&nm,sizeof(MSG_Action));
		//			GridMulticast(m_iHandle,snX,snZ,(MSG_STANDARD*)&nm);
		//		}	else
		//		{	S_SCP_RESP_MOVE_PORTAL sm; ZeroMemory(&sm, sizeof(sm));
		//			sm.wType=SCP_RESP_MOVE_PORTAL;
		//			sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; sm.byZone=byMoveZone;
		//			sm.nMoney=pMob[m_iHandle].MOB.nRupiah;
		//			pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm));

		//			pMob[m_iHandle].m_kWaitAction.iAction = eWaitAct_ZonePortal;
		//			return;
		//		}

		//	}
		//	break;
		case eWaitAct_Quit :
			{	
				Log( "clo ProgressWaitAction eWaitAct_Quit", pUser[m_iHandle].AccountName, pUser[m_iHandle].IP );
				CloseUser( m_iHandle );
			}
			break;
		case eWaitAct_SummonParty:
			{
				int iLeader = Leader;
				char pch[128] = {0,};
				sprintf(pch, "dbg Char:%s use summon_party item at posx:%d posy:%d", MOB.szName, TargetX, TargetY);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				if( 0 >= iLeader || MAX_USER <= iLeader ) iLeader = m_iHandle; // 자신이 리더이다. 파티원들만 소환하면 된다.
				else // 자신이 리더가 아니다. 리더와 다른 파티원들을 소환해야 한다.
				{
					if( !pMob[iLeader].IsDead() && !(eTNVSAfn_HaveKalaCore & pMob[iLeader].m_iAffections) )
					{
                        Teleport( iLeader, TargetX, TargetY );

						sprintf(pch, "dbg Char:%s recalled by summon_party item to posx:%d posy:%d", pMob[iLeader].MOB.szName, TargetX, TargetY);
						Log(pch, pUser[iLeader].AccountName, pUser[iLeader].IP);
					}
				}

				// 파티원들 소환
				for( int d = 0; d < MAX_PARTY; ++d )
				{   
					int fol = pMob[iLeader].m_irgParty[d];

					if( 0 > fol || MAX_USER <= fol ) continue;
					if( fol == m_iHandle ) continue;			 
					if( pMob[fol].IsDead() ) continue;
					if( eTNVSAfn_HaveKalaCore & pMob[fol].m_iAffections ) continue;

					Teleport( fol, TargetX, TargetY );
					pMob[fol].m_eFSM = eTNFsm_Stand;
					pMob[fol].m_kLastTime.uiSitted = 0;

					sprintf(pch, "dbg Char:%s recalled by summon_party item to posx:%d posy:%d", pMob[fol].MOB.szName, TargetX, TargetY);
					Log(pch, pUser[fol].AccountName, pUser[fol].IP);
				}
			}
			break;
		}
		m_kWaitAction.iAction = eWaitAct_None;
		m_kWaitAction.uiWaitingTime = 0;
	}
}


void CMob::UseSkill( short a_sProgress )
{
	if( 0 > m_iSkillCharged || eMonSkl_MaxIndex < m_iSkillCharged ) return;
	int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex;
	if( 0 >= iSkillIndex || MAX_SKILL_DATA <= iSkillIndex ) return;

	int iAllowedTargets = pSkillData[iSkillIndex].iAllowedTargets;
	int iAOE = pSkillData[iSkillIndex].iAOE;

	S_CSP_CAST_AREA_SKILL kMsg;
	memset( &kMsg, 0, sizeof(S_CSP_CAST_AREA_SKILL) );
	kMsg.snSkillID = m_krgSkill[m_iSkillCharged].sID;
	kMsg.bySkillLevel = 1; // monster 스킬들은 모두 1 level이다.

	kMsg.snCasterKeyID = (short)m_iHandle;				
	kMsg.snMapX = (short)TargetX;
	kMsg.snMapZ = (short)TargetY;
	kMsg.snRes = a_sProgress;

	if( eCmbt_Echo == a_sProgress )
	{
		CastSkill( &kMsg, 1 );
		return;
	}

	int irgTarget[TN_MAX_TARGET_COUNT] = { 0,0,0, };
	int iMaxTargetCount = TN_MAX_TARGET_COUNT;
	int iRange = iAOE;
	int iTargetCount = 0;

	if( (eTNAT_Enemy == iAllowedTargets) || (eTNAT_EnemyFarFirst == iAllowedTargets) )
	{
/*
		if( eTNSklT_Splash & pSkillData[iSkillIndex].sSkillType )
		{
			iAOE = 10;
			iRange = iAOE;
			if( pSkillData[iSkillIndex].iRange > iAOE ) iRange = pSkillData[iSkillIndex].iRange;
		}
*/
		if( eTNSklA_Unit == iAOE )
		{
			if( 0 >= CurrentTarget || MAX_MOB <= CurrentTarget ) return;
			kMsg.krgTarget[0].snKeyID = (short)CurrentTarget;
			iTargetCount = 1;

			if( eTNSklT_Splash & pSkillData[iSkillIndex].sSkillType )
			{
				SelectTarget( 5, iAllowedTargets, TN_MAX_TARGET_COUNT-1, irgTarget, 0, pMob[CurrentTarget].TargetX, pMob[CurrentTarget].TargetY );
				for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
					if( CurrentTarget == irgTarget[i] ) irgTarget[i] = 0;

				for( int i = 0; i < TN_MAX_TARGET_COUNT-1; ++i )
				{
					if( 0  == irgTarget[i] ) continue;
					kMsg.krgTarget[iTargetCount].snKeyID = (short)irgTarget[i];
					++iTargetCount;					
				}
			}
			if( 3 < m_iAttackCount ) Think( eTNAI_Attack, CurrentTarget );
		}
		else if( eTNSklA_Unit < iAOE )
		{ // 범위 스킬의 경우, target에 대한 목록 산출이 필요하다.
			if( eTNAT_EnemyFarFirst == iAllowedTargets ) SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget, 1 );
			else SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget, 0 );

			for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
			{
				if( 0  == irgTarget[i] ) break;
				kMsg.krgTarget[iTargetCount].snKeyID = (short)irgTarget[i];
				++iTargetCount;					
			}				
		} // else if( eTNSklA_Unit < iAOE )
	}
	else if( eTNAT_Self == iAllowedTargets )
	{
		kMsg.krgTarget[0].snKeyID = (short)m_iHandle;
		iTargetCount = 1; 
	}
	else if( eTNAT_Friend == iAllowedTargets )
	{
		if( eTNSklA_Unit == iAOE )
		{// 현재 잡혀 있는 target이 friend인가를 검사한다.
			int* pAllowedTarget = NULL;
			if( eZoneType_God == g_iZoneType ) pAllowedTarget = (int*)&(g_irgFriendTableRvR[m_byClan]);
			else if( eZoneType_Guild == g_iZoneType ) pAllowedTarget = (int*)&(g_irgFriendTableStrH[m_byClan]);
			else pAllowedTarget = (int*)&g_irgFriendTable[m_byClan];

			if( NULL != pAllowedTarget )
			{
				if( pAllowedTarget[pMob[CurrentTarget].m_byClan] ) // true 이면 friend가 아니다.
				{// 주위에서 friend를 한 마리 찾는다.
					iRange = 10;
					iMaxTargetCount = 1;
					SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget );
					kMsg.krgTarget[0].snKeyID = (short)irgTarget[0];
				}
				else // friend 이다.
				{					
					kMsg.krgTarget[0].snKeyID = (short)CurrentTarget;
				}
				iTargetCount = 1;
			}
			else return; // null 일 때, 절대 null일 수 없다.
		}
		else if( eTNSklA_Unit < iAOE )
		{ // 범위 스킬의 경우, target에 대한 목록 산출이 필요하다.
			SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget );
			for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
			{
				if( 0  == irgTarget[i] ) break;
				kMsg.krgTarget[iTargetCount].snKeyID = (short)irgTarget[i];
				++iTargetCount;					
			}
			if( TN_MAX_TARGET_COUNT > iTargetCount )
			{// 스킬 시전하는 본인 포함
				kMsg.krgTarget[iTargetCount].snKeyID = (short)m_iHandle;
				++iTargetCount;
			}
		} // else if( eTNSklA_Unit < iAOE )	}
	}
	else if( eTNAT_Party == iAllowedTargets )
	{
		kMsg.krgTarget[0].snKeyID = (short)m_iHandle;
		iTargetCount = 1; 
		for ( int d=0; d<MAX_PARTY;++d )
		{   int fol = m_irgParty[d];
			if  (fol<MAX_USER) continue; //  PC이면 skip
			if  (pMob[fol].Mode==MOB_EMPTY||pMob[fol].MOB.nHP<=0) 
			{   if  (pMob[fol].Mode!=MOB_EMPTY) DeleteMob(fol,1, 0, eTNPrdt_RemoveNormal, 100);
				m_irgParty[d] = 0;
				continue; // 파티에서 제거.
			}
			kMsg.krgTarget[iTargetCount].snKeyID = (short)fol;
			++iTargetCount;				
		}			
	}
	if( eTNAT_All == iAllowedTargets )
	{
		if( eTNSklA_Unit == iAOE )
		{
			kMsg.krgTarget[0].snKeyID = (short)CurrentTarget;
			iTargetCount = 1;
			if( 3 < m_iAttackCount ) Think( eTNAI_Attack, CurrentTarget );
		}
		else if( eTNSklA_Unit < iAOE )
		{ // 범위 스킬의 경우, target에 대한 목록 산출이 필요하다.
			int iEndX = TargetX + pSkillData[iSkillIndex].iAOE;
			int iEndY = TargetY + pSkillData[iSkillIndex].iAOE;
			for( int y = TargetY - pSkillData[iSkillIndex].iAOE; y < iEndY; ++y )
			{
				if( TN_MAX_TARGET_COUNT <= iTargetCount ) break;
				for( int x = TargetX - pSkillData[iSkillIndex].iAOE; x < iEndX; ++x )
				{
					if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
					int tid = pMobGrid[y][x];							
					if( tid<=0 || tid>=MAX_MOB ) continue;
					if( pMob[tid].Mode==MOB_EMPTY )	continue;
					if( tid == m_iHandle ) continue;
					if( pMob[tid].MOB.nHP<=0 ) continue;

					if( TN_MAX_TARGET_COUNT <= iTargetCount ) break;
					kMsg.krgTarget[iTargetCount].snKeyID = (short)tid;
					++iTargetCount;					
				}				
			}
		} // else if( eTNSklA_Unit < iAOE )
	}
	else if( eTNAT_FriendCorpse == iAllowedTargets )
	{
	}
	else if( eTNAT_NA == iAllowedTargets )
	{

	}

	int iRes = CastSkill( &kMsg, iTargetCount );
	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n[UseSkill] iRes:%d, SkillID %d, target수:%d > Target(%d,%d,%d,%d,%d ...), Aff%d, Imm:%d \r\n"
			, iRes, kMsg.snSkillID, iTargetCount
			, kMsg.krgTarget[0].snKeyID, kMsg.krgTarget[1].snKeyID, kMsg.krgTarget[2].snKeyID, kMsg.krgTarget[3].snKeyID, kMsg.krgTarget[4].snKeyID
            , (int)m_iAffections, m_iImmunity
			);
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_4TH_LOG__
}


void CMob::CheckInvalidCombat()
{
	if( MOB_PEACE != Mode ) // 전투중인데 마지막 공격한 시간이 오래 됐고, 계속 공격을 받아 HP가 줄었다면, ... 걸치기라고 생각할 수 있다.
	{
		if( CurrentTime > (m_kLastTime.uiAttacked + 20000) ) // 최근 20초동안 공격을 못했다면, 
			if( CurrentTime < (m_kLastTime.uiDamaged + 10000 ) ) // 최근 10초동안 공격을 받았다면, DOT이라면?
			{
				m_iBlockedCell = eTNCell_SafetyZone | eTNCell_MonsterCantMoveInThisCell;

				{ // 누가 이런것을 했는지에 대한 정보를 남긴다. 누가 언제 어디에서 누구에게 
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[CheckInvalidCombat(); %d월%d일 %d시%d분%d초] Monster> Hndl:%d, tribe:%d, Mode:%d, FSM:%d, HP:%d, Now:%u, Last Atk:%u, Dmg:%u \r\n"
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond						
						, m_iHandle, MOB.snTribe, Mode, m_eFSM, MOB.nHP
						, CurrentTime, m_kLastTime.uiAttacked, m_kLastTime.uiDamaged
						);
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_InvalidCombat] );
					for( int i = 0; i < TN_ATTACKER_COUNT; ++i )
					{
						if( 0 >= m_krgAttacker[i].iID || MAX_USER <= m_krgAttacker[i].iID ) continue;
						int iLeader = m_krgAttacker[i].iID;
						char chBuf2[512] = { 0,0,0, };
						sprintf( chBuf2, "\tPC0 > Hndl:%d, Name:%s\r\n"
							, iLeader, pMob[iLeader].MOB.szName
							);
						WriteLog( chBuf2, g_szrgLogFileName[eLogFileName_InvalidCombat] );


						for( int k = 0; k < MAX_PARTY; ++k )
						{
							int iPC = pMob[iLeader].m_irgParty[k];
							if( 0 >= iPC || MAX_USER <= iPC ) continue;
							char chBuf3[512] = { 0,0,0, };
							sprintf( chBuf3, "\tPC%d > Hndl:%d, Name:%s\r\n"
								, k+1, iPC, pMob[iPC].MOB.szName
								);
							WriteLog( chBuf3, g_szrgLogFileName[eLogFileName_InvalidCombat] );
						}
					}
				}	
			}
	}
}



void CMob::CheckCondition()
{
	if( 0 < m_kCond.irgCond[eTNCond_Help] )
	{
		//if( m_kCond.uirgExpireTime[eTNCond_Help] > CurrentTime ) break;
		if( 0 < m_kCond.irgCondCount[eTNCond_Help] )
			if( m_kCond.irgCond[eTNCond_Help] > MOB.nHP )
			{
				Think( eTNAI_Help1, CurrentTarget );
				--m_kCond.irgCondCount[eTNCond_Help];
				//m_kCond.uirgExpireTime[eTNCond_Help] = CurrentTime + g_irgSetting[eCnst_CondCoolDown];
			}
	}
	if( 0 < m_kCond.irgCond[eTNCond_Link] )
	{
		//if( m_kCond.uirgExpireTime[eTNCond_Link] > CurrentTime ) break;
		if( 0 < m_kCond.irgCondCount[eTNCond_Link] )
			if( m_kCond.irgCond[eTNCond_Link] > MOB.nHP )
			{
				Think( eTNAI_Link1, CurrentTarget );
				--m_kCond.irgCondCount[eTNCond_Link];
				//m_kCond.uirgExpireTime[eTNCond_Link] = CurrentTime + g_irgSetting[eCnst_CondCoolDown];
			}
	}
	if( 0 < m_kCond.irgCond[eTNCond_Flee] )
	{
		//if( m_kCond.uirgExpireTime[eTNCond_Flee] > CurrentTime ) break;
		if( 0 < m_kCond.irgCondCount[eTNCond_Flee] )
			if( m_kCond.irgCond[eTNCond_Flee] > MOB.nHP )
			{
				Think( eTNAI_Flee, CurrentTarget );
				--m_kCond.irgCondCount[eTNCond_Flee];
				//m_kCond.uirgExpireTime[eTNCond_Flee] = CurrentTime + g_irgSetting[eCnst_CondCoolDown];
			}
	}
}


void CMob::InitCondition()
{
	if( eTNMob_NPC != m_eMobType ) return;
	m_kCond.irgCondCount[eTNCond_Help] = pMonsterData[MOB.nTP].byQuest[eMonPrty_HelpCondCount];
	m_kCond.irgCondCount[eTNCond_Link] = pMonsterData[MOB.nTP].byQuest[eMonPrty_LinkCondCount];
	m_kCond.irgCondCount[eTNCond_Flee] = pMonsterData[MOB.nTP].byQuest[eMonPrty_FleeCondCount];
}

int CMob::CheckItem( short a_sItemID, int a_iCount, int* a_irgSlot ) // inventory에서 찾아본다.
{
	if( eTNMob_PC != m_eMobType ) return 0;
	int iCount = 0;
	int iSlotIndex = 0;	
	for( int i = 0; i < byMaxInven; ++i )
	{
		if( a_sItemID == pItemData[MOB.Inven[i].snIndex].sID )
		{
			a_irgSlot[iSlotIndex] = i;					
			iCount += MOB.Inven[i].byCount;
			++iSlotIndex;
			if( 4 < iSlotIndex ) break;
		}
		if( iCount >= a_iCount ) break;
	}

	return iCount;
}

int CMob::RemoveItem( int a_iCount, int* a_irgSlot )
{
	if( eTNMob_PC != m_eMobType ) return eTNRes_Failed;
	if( 0 >= a_iCount ) return eTNRes_Succeeded;

	for( int iSlot = 0; iSlot < 5; ++iSlot )
	{
		if( 0 > a_irgSlot[iSlot] || byMaxInven <= a_irgSlot[iSlot] ) continue;
		if( 0 >= a_iCount ) break;

		if( MOB.Inven[a_irgSlot[iSlot]].byCount > a_iCount )
		{						
			MOB.Inven[a_irgSlot[iSlot]].byCount -= a_iCount;
			a_iCount = 0;
			S_SCP_RESP_ITEM_SET itemset;
			itemset.wType = SCP_RESP_ITEM_SET;
			itemset.byType = SET_ITEM_CREATE;
			itemset.byPlace = ITEM_PLACE_INVEN; // inventory
			itemset.byIndex = a_irgSlot[iSlot];
			memcpy(&(itemset.sitem), &(MOB.Inven[a_irgSlot[iSlot]]), sizeof(STRUCT_ITEM));
			pUser[m_iHandle].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));						
		}
		else if( MOB.Inven[a_irgSlot[iSlot]].byCount == a_iCount )
		{						
			MOB.Inven[a_irgSlot[iSlot]].byCount -= a_iCount;
			a_iCount = 0;
			S_SCP_RESP_ITEM_SET itemset;
			itemset.wType = SCP_RESP_ITEM_SET;
			itemset.byType = SET_ITEM_DELETE;
			itemset.byPlace = ITEM_PLACE_INVEN; // inventory
			itemset.byIndex = a_irgSlot[iSlot];
			memcpy(&(itemset.sitem), &(MOB.Inven[a_irgSlot[iSlot]]), sizeof(STRUCT_ITEM));
			pUser[m_iHandle].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));
			memset( &(MOB.Inven[a_irgSlot[iSlot]]), 0, sizeof(STRUCT_ITEM) );
		}
		else if( MOB.Inven[a_irgSlot[iSlot]].byCount < a_iCount )
		{
			a_iCount -= MOB.Inven[a_irgSlot[iSlot]].byCount;
			MOB.Inven[a_irgSlot[iSlot]].byCount = 0;
			S_SCP_RESP_ITEM_SET itemset;
			itemset.wType = SCP_RESP_ITEM_SET;
			itemset.byType = SET_ITEM_DELETE;
			itemset.byPlace = ITEM_PLACE_INVEN; // inventory
			itemset.byIndex = a_irgSlot[iSlot];
			memcpy(&(itemset.sitem), &(MOB.Inven[a_irgSlot[iSlot]]), sizeof(STRUCT_ITEM));
			pUser[m_iHandle].cSock.AddMessage((char*)&itemset,sizeof(S_SCP_RESP_ITEM_SET));
			memset( &(MOB.Inven[a_irgSlot[iSlot]]), 0, sizeof(STRUCT_ITEM) );
		}
	}

	if( 0 == a_iCount ) return eTNRes_Succeeded;
	return eTNRes_Failed;
}



//@Param
//	- a_bCollided : 꼭 그 자리를 차지해야하는 지에 대한 여부, true이면 꼭 그 위치를 고수해야 한다.
int CMob::Summon( int a_iMonsterID, int a_iCount, int a_iPopType, int a_iClass1, int a_iClass2, int a_iClan, int a_iDirection, int x, int y, int a_iTarget, bool a_bCollided, int a_iLifeTime, int a_iOldHandle, int a_iCaller, int a_iRoute )
{
	if( (0 != a_iTarget) && (a_iTarget == m_iHandle) ) return 0;
	if( eTNCls2_Basic > a_iClass2 || eTNCls2_Tracker < a_iClass2 ) a_iClass2 = eTNCls2_Basic;

	// 소환할 때
	int iMonsterDataIndex = a_iMonsterID - 2000; // the index of monster data
	int iIndex = 0;


	int iMob = a_iOldHandle;

	if( eZone_Chaturanka == g_iZoneID )
	{
		if( 2113 == a_iMonsterID ) iMob = 1000; // 라푸기병
		else if( 2112 == a_iMonsterID ) iMob = 1001; // 라푸
		if( pMob[iMob].IsAlive() ) DeleteMob( iMob, 1, 0, eTNPrdt_RemoveBoom, 300 );
	}
	else if( eZone_Stronghold == g_iZoneID )
	{
		if( eStronghold_NorthwestSymbol2 == a_iMonsterID ) iMob = 1000;
		else if( eStronghold_NortheastSymbol2 == a_iMonsterID ) iMob = 1001;
		else if( eStronghold_SouthwestSymbol2 == a_iMonsterID ) iMob = 1002;
		else if( eStronghold_SoutheastSymbol2 == a_iMonsterID ) iMob = 1003;
		else if( 2296 == a_iMonsterID ) iMob = 1004;
		else if( 2295 == a_iMonsterID ) iMob = 1005;
		else if( 2306 == a_iMonsterID ) iMob = 1006;
		else if( 2305 == a_iMonsterID ) iMob = 1007;
		else if( 2309 == a_iMonsterID ) iMob = 1008;
		else if( 2308 == a_iMonsterID ) iMob = 1009;
		else if( 2312 == a_iMonsterID ) iMob = 1010;
		else if( 2311 == a_iMonsterID ) iMob = 1011;
/*
2296
2297
2295

2306
2307
2305

2309
2310
2308

2312
2313
2311
*/
	}

	if( MAX_USER > iMob || MAX_MOB <= iMob ) iMob = GetEmptyNPCMob();

	if( 0 == iMob )
	{
		#ifdef __TN_TOP_LOG__
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "[CastOnly] Summon 실패 > 더이상 monster handle이 남아 있지 않음. \r\n" );
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );		
		}
		#endif
		return 0;
	}

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[Summon(); %d월%d일 %d시%d분%d초] tribe:%d, handle:%d, caller:%d, GerateIndex:%d, HP:%d, class(%d,%d), Mode:%d, FSM:%d, Now:%u, Killed:%u, SummonMonster:%d \r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, MOB.snTribe, m_iHandle, a_iCaller, GenerateIndex, MOB.nHP, MOB.byClass1, MOB.byClass2
			, Mode, m_eFSM, CurrentTime, m_kLastTime.uiKilled, a_iMonsterID
			);
		WriteLog( chBuf, m_szLogFile );
	}	
	#endif

	pMob[iMob].MOB = pMonsterData[iMonsterDataIndex];
	pMob[iMob].MOB.nTP = iMonsterDataIndex;
	pMob[iMob].Init( iMob ); // 초기화

	if( eTNMob_PC == m_eMobType )
	{
		int iPetGrowthHP = m_krgVariation[eTNVar_PetGrowthHP][eVar_Skill].iPlus + m_krgVariation[eTNVar_PetGrowthHP][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_PetGrowthHP][eVar_Equipment].iPlus;
		int iPetGrowthDamage = m_krgVariation[eTNVar_PetGrowthDamage][eVar_Skill].iPlus + m_krgVariation[eTNVar_PetGrowthDamage][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_PetGrowthDamage][eVar_Equipment].iPlus;
		int iPetGrowthAttackSpeed = m_krgVariation[eTNVar_PetGrowthAttackSpeed][eVar_Skill].iPlus + m_krgVariation[eTNVar_PetGrowthAttackSpeed][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_PetGrowthAttackSpeed][eVar_Equipment].iPlus;

		bool bBuffered = false;
		if( 0 < iPetGrowthHP )
		{
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_MaxHPPlus;
			kEffect.kFunc.iData = 0;
			kEffect.iDuration = eTNSklD_Unlimited;
			kEffect.iParam1 = iPetGrowthHP;
			pMob[iMob].AffectEffect( kEffect, eVar_PassiveSkill, eAfn_Add, m_iHandle, m_iHandle, 0 );				
			bBuffered = true;
		}

		if( 0 < iPetGrowthDamage )
		{
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_DamagePlus;
			kEffect.kFunc.iData = 0;
			kEffect.iDuration = eTNSklD_Unlimited;
			kEffect.iParam1 = iPetGrowthDamage;
			kEffect.iParam2 = iPetGrowthDamage;
			pMob[iMob].AffectEffect( kEffect, eVar_PassiveSkill, eAfn_Add, m_iHandle, m_iHandle, 0 );
			bBuffered = true;
		}

		if( 0 < iPetGrowthAttackSpeed )
		{
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_CastSpeedPlus;
			kEffect.kFunc.iData = 0;
			kEffect.iDuration = eTNSklD_Unlimited;
			kEffect.iParam1 = iPetGrowthAttackSpeed;
			pMob[iMob].AffectEffect( kEffect, eVar_PassiveSkill, eAfn_Add, m_iHandle, m_iHandle, 0 );
			bBuffered = true;
		}

		if( bBuffered )
		{
			pMob[iMob].UpdatePoints();
			pMob[iMob].IncHP( 100000 );
		}
	}// if( eTNMob_PC == m_eMobType )


	int iRes = pMob[iMob].set_Segment( a_iRoute );

	if( 0 == x || 0 == y )
	{ // 소환 위치기 설정이 되어 있지 않을 경우에는 소환자의 위치를 기반으로 한다.		
		if( eTNRes_Failed == iRes )
		{
			x = TargetX;
			y = TargetY;
		}
		else
		{
			x = pMob[iMob].SegmentListX[0] - pMob[iMob].SegmentRange[0] + (rand()%pMob[iMob].SegmentRange[0]);
			y = pMob[iMob].SegmentListY[0] - pMob[iMob].SegmentRange[0] + (rand()%pMob[iMob].SegmentRange[0]);

			if( 0 == x || 0 == y )
			{ // 소환 위치기 설정이 되어 있지 않을 경우에는 소환자의 위치를 기반으로 한다.		
				x = TargetX;
				y = TargetY;
			}
		}
	}

	if( eTNRes_Failed == iRes )
	{
		for( int i = 0; i < MAX_SEGMENT; ++i )
		{
			pMob[iMob].SegmentListX[i] = x;
			pMob[iMob].SegmentListY[i] = y;
			pMob[iMob].SegmentWait[i] = rand() % 8;
			pMob[iMob].SegmentRange[i] = rand() % 20;
		}
		pMob[iMob].RouteType = eTNRout_MoveNRoam;
		
	}
	pMob[iMob].Formation = 0;


	if( 0 < pMobGrid[y][x] && MAX_MOB > pMobGrid[y][x] ) // 다른 mob이 위치하고 있다.
	{		
		if( a_bCollided ) // dest 자리를 검사하고, 다른 mob이 있으면, 처리(제거)한 후에, 꼭 그 위치에 위치를 시킨다.
		{
			int iOccupiedMob = pMobGrid[y][x];
			int iNewX, iNewY;
			iNewX = x; iNewY = y;
			int tret = PickFreeMobGrid( iMob, &iNewX, &iNewY );
			if( FALSE == tret )
			{ // user이면 kick out 시켜주고, monster이면 단순히 죽인다.
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user이면
				{
					char temp[256] = {0,};
					SendClientMessage( iOccupiedMob, g_pMessageStringTable[_Bad_Network_Packets] );
					sprintf(temp, "clo Summon user:%s  - 0 < iOccupiedMob && MAX_USER > iOccupiedMob", pMob[iOccupiedMob].MOB.szName);
					Log( temp, pUser[iOccupiedMob].AccountName, pUser[iOccupiedMob].IP );
					CloseUser( iOccupiedMob );
				}
				else 
				{
					KillMonster( iOccupiedMob );
					/*
					pMob[iOccupiedMob].MOB.nHP = 0; 
					pMob[iOccupiedMob].CurrentTarget = 0;
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
			}

			pMobGrid[y][x] = iMob;
		}
		else
		{
			int tret = GetEmptyMobGrid( iMob, &x, &y, pMob[iMob].m_iBlockedCell );
			if( FALSE == tret ) return 0; // summon이 fail나도 상관이 없는 것일 경우, ...
		}
	}

	pMob[iMob].LastX = pMob[iMob].TargetX = pMob[iMob].SegmentX = x;
	pMob[iMob].LastY = pMob[iMob].TargetY = pMob[iMob].SegmentY = y;

	//// default settings
	//for( int i = 0; i < MAX_SEGMENT; ++i )
	//{
	//	pMob[iMob].SegmentListX[i] = x;
	//	pMob[iMob].SegmentListY[i] = y;
	//	pMob[iMob].SegmentWait[i] = rand() % 8;
	//	pMob[iMob].SegmentRange[i] = rand() % 20;
	//}
	//pMob[iMob].RouteType = eTNRout_MoveNRoam;
	//pMob[iMob].Formation = 0;

	pMob[iMob].MOB.byClass1 = (byte)a_iClass1; // 소환되는 NPC의 직업
	pMob[iMob].MOB.byClass2 = (byte)a_iClass2; // 소환되는 NPC의 상세 직업            
	pMob[iMob].m_byClan = pMob[iMob].MOB.byTrimuriti = (byte)a_iClan; // 소환되는 것은 NPC-Monster형이다. 따라서 m_byClan과 MOB.byTrimuriti 값은 동일하다.
	//if( eTNClan_GM == pMob[iMob].m_byClan ) pMob[iMob].m_byClan = eTNClan_Neutral;

	if( 0 < a_iTarget )
	{
		pMob[iMob].m_kLastTime.uiSelectTarget = CurrentTime + 30000;		
		pMob[iMob].MemorizeAttacker( 0, 1, a_iTarget );
	}

	int iSummonDelay = 3000;
	pMob[iMob].m_uiLifeTime = a_iLifeTime; // default value
	if( 0 < a_iLifeTime )
	{
		pMob[iMob].m_uiLifeTime = CurrentTime + a_iLifeTime * 1000;
		pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_LifeTime;
	}

	if( eTNCls_SummonOld == a_iClass1 )
	{// 소환자의 활동 영역을 계승한다.
		pMob[iMob].MOB.byLevel = MOB.byLevel;
		pMob[iMob].RouteType = eTNRout_MoveNRoam; // RouteType;
		pMob[iMob].Formation = Formation;
		pMob[iMob].Leader = m_iHandle;
		//pMob[iMob].m_bSolo = true;
		pMob[iMob].m_iGroup = 0; // sole
		memcpy( pMob[iMob].SegmentListX, SegmentListX, sizeof(SegmentListX) );
		memcpy( pMob[iMob].SegmentListY, SegmentListY, sizeof(SegmentListY) );						
		memcpy( pMob[iMob].m_krgInfluenceGrid, m_krgInfluenceGrid, sizeof(m_krgInfluenceGrid) );
		pMob[iMob].m_iInfluenceGridSize = m_iInfluenceGridSize = 0;
	}
	else if( eTNCls_Follower == a_iClass1 )
	{
		pMob[iMob].Leader = m_iHandle;
		pMob[iMob].m_iMoveSpeed = pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_RunSpeed];
		pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_HaveMaster | eTNAIO_GetCommand | eTNAIO_CombatOnly;
	}
	else if( eTNCls_Summoned == a_iClass1 )
	{ //class2 familiar/retainer/totem
		iSummonDelay = 10;
		pMob[iMob].m_kLastTime.uiSelectTarget = pMob[iMob].m_uiLifeTime; // 소환수들은 target을 임의로 변경하지 않는다.

		m_irgSummoned[a_iClass2] = iMob;
		pMob[iMob].Leader = m_iHandle;		
		pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_HaveMaster;

		strcmp( pMob[iMob].MOB.szName, MOB.szName );

		if( 0 >= pMob[iMob].MOB.byLevel || 100 < pMob[iMob].MOB.byLevel ) pMob[iMob].MOB.byLevel = MOB.byLevel;
		pMob[iMob].m_iButtonStatus = m_iButtonStatus;
	
		pMob[iMob].m_iBlockedCell = m_iBlockedCell; // 주인을 따른다.

		if( eTNCls2_Retainer == a_iClass2 || eTNCls2_Pet == a_iClass2 ) pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_GetCommand;
		if( eTNCls2_Familiar == a_iClass2 || eTNCls2_Tracker == a_iClass2 ) pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_CombatOnly;
	}

	pMob[iMob].m_uiActionLock = CurrentTime + iSummonDelay;
	pMob[iMob].m_iDirection = a_iDirection;
	                    
	S_SCP_INIT_OTHER_MOB sm;
	GetCreateMob( iMob, &sm );
	sm.byPopType = a_iPopType; // 소환될 때의 연출 번호
	pMobGrid[y][x] = iMob;
	GridMulticast( x, y, (MSG_STANDARD*)&sm, 0, 100 );

	if( 0 != pMonsterData[iMonsterDataIndex].byQuest[eMonPrty_Reserved4] )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );

		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[%dyy%dmm%ddd %dhh%dms%dss] Summon > Boss(H:%d, Trb:%d) was summoned by Mob(H:%d, %s)!! AIOption:%u, class(%d,%d), clan(%d,%d), caller:%d \r\n"
			, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, iMob, a_iMonsterID
			, m_iHandle, MOB.szName
			, pMob[iMob].m_iAIOption
			, pMob[iMob].MOB.byClass1, pMob[iMob].MOB.byClass2
			, pMob[iMob].m_byClan, pMob[iMob].MOB.byTrimuriti
			, a_iCaller
			);
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_BossSystem] );
		pMob[iMob].Print( chBuf );
	}

	return iMob;
}                			    


int CMob::UseLeftWeapon( S_CSP_CAST_AREA_SKILL* a_pMsg )
{
	int iRes = eCmbt_Dodge;	
	int iSkillBookIndex = MAX_SKILL ;
	TNSKILL_DATA kSkill;

	int i = 1; // 2nd target
	short sUnitID = a_pMsg->krgTarget[i].snKeyID;
	kSkill = pItemData[MOB.Equip[eTNEqu_Shield].snIndex];	     

	// 왼손에 들고 있는 weapon에 대한 index 검사
	if( MOB.nHP < kSkill.kCost.iHP ) return eTNRes_CostHP;
	if( MOB.nTP < kSkill.kCost.iTP ) return eTNRes_CostTP;
	if( 0 < kSkill.kCost.sItemID )
	{// 아이템을 inventory에서 찾아서 삭제를 해줘야 한다.
		int irgSlot[5] = { -1,-1,-1,-1,-1 };
		int iCount = 0;
		iCount = CheckItem( kSkill.kCost.sItemID, kSkill.kCost.byItemCount, irgSlot );
		if( iCount >= kSkill.kCost.byItemCount ) RemoveItem( kSkill.kCost.byItemCount, irgSlot );
		else return eTNRes_CostItem;
	}
	
	DecHP( kSkill.kCost.iHP );
	DecTP( kSkill.kCost.iTP );

	// party원들에게 HP 상태를 표시
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
		// party원들 유무에 따라서 UpdateStatus 메시지 전달
	}

	TNDAMAGE kDamageSrc;
	if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
	{		    
        CalDamage( kDamageSrc, kSkill, eHnd_Left );
        if( eTNCPhase_CastInstant1 & kSkill.sCombatPhase ) CastInstant1( kDamageSrc, kSkill );
	}

	if( 0 > sUnitID ) return eTNRes_InvalidTarget6; // 타겟 ID가 잘못됐다.

	if( eTNAT_Enemy == kSkill.iAllowedTargets )
	{
		if( pMob[sUnitID].IsDead() )
		{
			a_pMsg->krgTarget[i].byRes = eCmbt_Dodge;
			a_pMsg->krgTarget[i].iDamage = 0;
			a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;//0일 것이다.
			a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
			return eTNRes_Succeeded;
		}
	}

	byte bySuccessRate = kSkill.bySuccessRate;
	if( 100 == bySuccessRate ) iRes = eCmbt_Normal;
	else if( 0 == bySuccessRate ) iRes = pMob[sUnitID].OnDefense( m_kCombatFactors.iAttackRate, m_iHandle, false );
	else
	{
		byte nDice =(byte)(rand() % 100);
		if( nDice > bySuccessRate ) iRes = eCmbt_Dodge;
	}

	if( eCmbt_Dodge == iRes )
	{
		a_pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge;
		a_pMsg->krgTarget[i].iDamage = 0;
		a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
		a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;

		return eTNRes_Succeeded;
	}
	else if( eCmbt_Critical == iRes ) iRes = eCmbt_Normal;

	// 공격 성공일 경우			
	int iDamage = 0;
	if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
	{
		TNDAMAGE kDamage = kDamageSrc;
		/*
		if( eCmbt_Critical == iRes )
		{
			kDamage.irgPhy[0] += kDamage.irgPhy[0];
			kDamage.irgPhy[1] += kDamage.irgPhy[1];
		}
		*/
        if( eTNCPhase_CastInstant2 & kSkill.sCombatPhase ) CastInstant2( kDamage, kSkill, iSkillBookIndex, sUnitID, iRes );

        int iPercent = 100;
        iDamage = DealDamage( kDamage, sUnitID, iPercent );
		if( 0 == i ) UpdateEquipDur( iDamage, 2 ); // 공격 1회당 내구도 1씩 떨어진다.

		if( eTNCPhase_CastInstant3 & kSkill.sCombatPhase ) CastInstant3( kSkill, pMob[sUnitID].m_iLastDamage );
		if( eTNCPhase_Taunt & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant0( kSkill, pMob[sUnitID].m_iLastDamage, m_iHandle );
	}			
	if( eTNCPhase_OnTakeInstant1 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant1( m_iHandle, kSkill ); // 시체관련
	if( eTNCPhase_OnTakeInstant2 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant2( m_iHandle, kSkill, iSkillBookIndex );
	if( eTNCPhase_OnAffect & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeAffections( kSkill, iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
	
	a_pMsg->krgTarget[i].byRes = (byte)iRes;
    a_pMsg->krgTarget[i].iDamage = iDamage;
    a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
    a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;	

	if( eCmbt_Normal == iRes || eCmbt_Critical == iRes ) // 공격이 성공일 때만, 수행된다. 
	{ // 여기가 공격 성공이 아닐 때가 있는가?
		TNDAMAGE kDamageReflected;
		int iReflectDamage = pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPPlus /*+ pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Potion].iPPlus*/;
		if( 0 > iReflectDamage ) iReflectDamage = 0;
		if( g_irgSetting[eCnst_ReflectMax] < iReflectDamage ) iReflectDamage = g_irgSetting[eCnst_ReflectMax];
		kDamageReflected.irgPierce[0] = Percent( a_pMsg->krgTarget[i].iDamage, iReflectDamage );

		if( 0 < kDamageReflected.irgPierce[0] ) OnTakeDamage( kDamageReflected, sUnitID );
		
/* 
		// party원들에게 HP 상태를 표시
		if( a_pMsg->krgTarget[i].iDamage>0 && sUnitID>0 && sUnitID<MAX_USER)
		{	S_SCP_RESP_UPDATE_PARTY sm; sm.wType=SCP_RESP_UPDATE_PARTY;
			sm.wPDULength=sizeof(sm)-sizeof(HEADER);
			sm.Party.nCurHP=pMob[sUnitID].MOB.nHP; sm.Party.nCurTP=pMob[sUnitID].MOB.nTP;
			sm.Party.byLevel=pMob[sUnitID].MOB.byLevel; sm.Party.nMaxHP=pMob[sUnitID].m_iMaxHP;
			sm.Party.nMaxTP=pMob[sUnitID].m_iMaxTP; sm.Party.nID=sUnitID;
			sm.Party.nAffections=pMob[sUnitID].m_iAffections;
			strncpy(sm.Party.Name,pMob[sUnitID].MOB.szName,SZNAME_LENGTH);

			int nLeader=0;
			if(pMob[sUnitID].Leader==0) nLeader=sUnitID;
            else nLeader=pMob[sUnitID].Leader;

			SendPartyMessage(nLeader, (MSG_STANDARD*)&sm);
			// party원들 유무에 따라서 UpdateStatus 메시지 전달
		}		
*/
	}

	return eTNRes_Succeeded;
}

bool CMob::ExpandFunc(int nTimeIndex, short snDays)
{
	short snDay = snDays;
	//bool bRet = true; int nItemIndex = 0;
	//nItemIndex = HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START+nTimeIndex;
	//bRet &= g_ParamMgr.HT_bGetItemTimeLimit(nItemIndex, &snDay);
	//if(!bRet)	//	유료아이템을 사용했는데 문제가 발생
	//{	char chBuf[256] = { 0,0,0, };
	//	sprintf(chBuf, "err Premium-Item used but parameter error occured:%s Item:%d", MOB.szName, nItemIndex);
	//	TimeWriteLog(chBuf, ".\\LOG\\[Log]Premium-Item.txt" );
	//	return false;
	//}

	time_t now; time(&now);
	if(now>pUser[m_iHandle].m_time[nTimeIndex])
	{	pUser[m_iHandle].m_time[nTimeIndex] = now+snDay*24*3600;	//	사용기간이 만료된 아이템은 현재일을 기준으로 날자를 추가한다
	}	else
	{	pUser[m_iHandle].m_time[nTimeIndex] += snDay*24*3600;		//	사용기간이 만료되지 않은 아이템구매시 만기날자에 추가한다.
	}

	char pch[256] = {0,};
	struct tm when;
	when= *localtime((time_t*)&(pUser[m_iHandle].m_time[nTimeIndex]));
	sprintf(pch, "dbg Char:%s Use Period_Item TimeIndex:%d Day:%d expanded to %2.2d%2.2d%2.2d %2.2d%2.2d%2.2d",
		MOB.szName, nTimeIndex, snDays, when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec);
	Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

	//Msg_Time sm; sm.wType = _Msg_Time;
	//m->byResult = REPLY_ACK_OK;
	//sm.nItemID = nTimeIndex;
	//m->dwTime = pUser[conn].m_time[nIndex];
	//m->nCash = pUser[conn].m_nCash;

	return true;
}

bool CMob::IsUsablePustica(BYTE byType, int iTarget1, short snTarget2)
{
	if(eWaitAct_TownPortal == m_kWaitAction.iAction) return false;

	bool bRet = true;
	int nGuildIndex = 0;
	byte byZone = 0;	
	switch(byType)
	{
	case ePortal_Gen:					//	이동의 푸스티카
		m_snMovePortal = ePortal_Gen;
		break;
	case ePortal_Guild:					//	요새푸스티카(주신전에서 사용불가)
		if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW || ServerIndex+1==SERVER_CHATURANGKA) return false;
		if(MOB.nGuildID==0) return false;

		nGuildIndex = IsGuildMemberIn(MOB.nGuildID);
		if(nGuildIndex<=0 || nGuildIndex>=MAX_USER) return false;

		for(int i=0; i<eStronghold_MaxCount; i++)
		{
			if(strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIndex].GUILD.GuildName, SZGUILD_LENGTH)==0 ||
				strncmp(g_krgStronghold[i].szGuildName, pGuild[nGuildIndex].GUILD.AlliedGuildName1, SZGUILD_LENGTH)==0) break;
		}

		if(i>=4) return false;

		m_snMovePortal = ePortal_Stronghold_NW+i;
		break;
	case ePortal_Castle:
		{	
			if(g_iCastleOwner!=MOB.nGuildID) return false;	//	공성의 소유길드가 아니면 사용안됨
			if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW || ServerIndex+1==SERVER_CHATURANGKA) return false;	//	주신전에서 사용불가
			m_snMovePortal = ePortal_CastleIN;
		}	break;
	case ePortal_Ziva:					//	지바푸스티카
		bRet = g_ParamMgr.HT_bGetNPCZone( snTarget2, &byZone );
		if(!bRet) 
		{	SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
			return false;
		}
		m_snMovePortal = ePortal_Ziva;
		m_snSaveNPC = snTarget2;
		break;
	case ePortal_SZiva:					//	고급지바푸스티카
		m_snMovePortal = snTarget2;
		break;
	case ePortal_NoLimit:
		if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW) return false;
		m_snMovePortal = snTarget2;
		break;
	case ePortal_Memorized:
		m_snMovePortal = ePortal_Memorized;
		break;
	default:				//	기타 푸크티카(차투랑가 입장권, 비류성) - 제약조건이 따른다면 별도의 type로 생성후 조건체크필요하다
		if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW) return false;
		m_snMovePortal = iTarget1;
		break;
	}

	char pch[256] = {0,};
	if(byType==ePortal_Ziva)
		sprintf(pch,"dbg Char:%s uses pustica from pos x:%d, y:%d to npc:%d", MOB.szName, TargetX, TargetY, m_snSaveNPC);
	else
        sprintf(pch,"dbg Char:%s uses pustica from pos x:%d, y:%d to portal:%d", MOB.szName, TargetX, TargetY, m_snMovePortal);

	Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

	return true;
}

//@Return
//	0: succeeded
//	Failed>
//		1: invalid target
//		2: not pc
//		3: party
//		4: friendly
//		5: same guild
//		6: ally
int CMob::CanAttackTarget( int a_iTarget )
{
	if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) return eTNRes_InvalidHandle;
	if( eTNMob_PC != m_eMobType ) return eTNRes_PCOnly;

	int iDefender = a_iTarget;
	int iDefClan = pMob[iDefender].m_byClan;
	int iDefGuildID = pMob[iDefender].MOB.nGuildID;
	if( eTNMob_NPC == pMob[iDefender].m_eMobType )
	{
		iDefGuildID = 0; //  monster이라면 guild는 0
				
		if( eTNAIO_HaveMaster & pMob[iDefender].m_iAIOption )
		//if( (eTNCls2_Retainer == pMob[iDefender].MOB.byClass2) || (eTNCls2_Familiar == pMob[iDefender].MOB.byClass2) || (eTNCls_Fellow == pMob[iDefender].MOB.byClass1) ) 
		{
			int iMaster = pMob[iDefender].Leader;
			if( 0 < iMaster && MAX_USER > iMaster )
			{
				iDefender = iMaster;
				iDefClan = pMob[iMaster].m_byClan;
				iDefGuildID = pMob[iMaster].MOB.nGuildID;
			}
		}
	}

	if( iDefender == m_iHandle ) return eTNRes_TargetSelf;

	// party원들을 공격할 수 없다.
	if( IsParty( iDefender ) ) return eTNRes_IsPartyMember;
	//if( Leader == iDefender ) return eTNRes_IsPartyMember;
	//if( pMob[iDefender].Leader == m_iHandle ) return eTNRes_IsPartyMember;
	//for( int i = 0; i < MAX_PARTY; ++i )
	//{
	//	if( iDefender == m_irgParty[i] ) return eTNRes_IsPartyMember; // 파티원이다.
	//}


	// zone 설정에 따른 공격 가능성 판단
	int* pAllowedTarget = NULL;
	if( eZoneType_God == g_iZoneType )
	{
		pAllowedTarget = (int*)&(g_irgEnemyTableRvR[m_byClan]);
	}
	else if( eZoneType_Guild == g_iZoneType )
	{
		if( eTNMob_PC == pMob[iDefender].m_eMobType ) // 둘다 PC이다. 길드 비교를 해야 한다.
		{
			if( MOB.nGuildID == iDefGuildID ) return eTNRes_IsSameGuildMember;

			// 연합 길드
			int nMyGuild = GetGuild( MOB.nGuildID );
			int nTargetGuild = GetGuild( iDefGuildID );
			if(strncmp(pGuild[nMyGuild].GUILD.AlliedGuildName1, pGuild[nTargetGuild].GUILD.GuildName, SZGUILD_LENGTH)==0) return eTNRes_IsAlly; 
		}
	}
	else //if( eZoneType_Normal == g_iZoneType )
	{
		if( eTNBtn_PK & m_iButtonStatus ) pAllowedTarget = (int*)&g_irgEnemyTablePKOn[m_byClan];
		else pAllowedTarget = (int*)&g_irgEnemyTablePKOff[m_byClan];
	}


	if( (NULL != pAllowedTarget) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
	{
		int iNotChallengeMode = 1; // 이 상태가 일반 상태, target과 결투 모드이면 적이 된다.
		int iFlag = pAllowedTarget[iDefClan]; // 적인가? true이면 친구이고 false이면 적이다.
		if( eTNMob_PC == m_eMobType ) // caster(공격자)가 PC이라면, ...
		{
			if( iDefender == pUser[m_iHandle].m_nChallenger )
			{
				iNotChallengeMode = 0; // 현재 결투 상태이다. 그럼 적이므로 공격가능
				if( IsDebugOn( eTNDbg_Pet ) )
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[CanAttackTarget()] Master:%d, target:%d(defender:%d), bNotChallengeMode:%d\r\n"
						, m_iHandle, a_iTarget, iDefender, iNotChallengeMode );
					WriteLog( chBuf, m_szLogFile );
				}
			}
		}

		if( iFlag && iNotChallengeMode )
		{
			return eTNRes_IsFriend;
		}
	}

	return eTNRes_Succeeded;
}



void CMob::Add_Debug( int a_iDbg )
{
	m_iDebug =  m_iDebug | a_iDbg;
}


void CMob::Remove_Debug( int a_iDbg )
{
	if( a_iDbg & m_iDebug ) m_iDebug =  m_iDebug ^ a_iDbg;
}


bool CMob::IsParty( int a_iTarget )
{
	if( 0 >= a_iTarget || MAX_MOB <= a_iTarget ) return false;

	if( Leader == a_iTarget ) return true; // target이 파티장이다.
	if( pMob[a_iTarget].Leader == m_iHandle ) return true; // 내가 파티장이다.

	int iLeader = Leader;
	if( 0 >= iLeader ) iLeader = m_iHandle; // 내가 파티장이다.

	for( int i = 0; i < MAX_PARTY; ++i )
	{
		int iMob = pMob[iLeader].m_irgParty[i];
		if( iMob == a_iTarget ) return true;
	}

	return false;
}


int CMob::CountPartyMember()
{
	int iLeader = Leader;
	if( 0 >= iLeader ) iLeader = m_iHandle; // 내가 파티장이다.

	int iCount = 1;
	for( int i = 0; i < MAX_PARTY; ++i )
	{
		int iPC = pMob[iLeader].m_irgParty[i];
		if( USER_PLAY == pUser[iPC].Mode ) ++iCount;
	}

	return iCount;
}

//------------------------------------------------------------------------------------------
// Robot 관련 함수들
//------------------------------------------------------------------------------------------

int CMob::SelectSkill2() // robot이 스킬을 선택한다.
{ // 각 종족별 하드 코딩한다.

	enum { eSkillList_Size = 5, };
	int irgSkillList[eSkillList_Size] = { 0,0,0, }; // m_krgSkill의 index 번호

	if( 0 == MOB.byClass2 )// 방나가
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 25;
		irgSkillList[2] = 20;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 1 == MOB.byClass2 ) // 공나가
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 25;
		irgSkillList[2] = 20;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 2 == MOB.byClass2 ) // 단검아수라
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 23;
		irgSkillList[2] = 6;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 3 == MOB.byClass2 ) // 활 아수라
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 100;
		irgSkillList[2] = 100;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 4 == MOB.byClass2 ) // 전투 야크샤
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 22;
		irgSkillList[2] = 23;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 5 == MOB.byClass2 )
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 22;
		irgSkillList[2] = 23;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 6 == MOB.byClass2 )
	{
		irgSkillList[0] = 0;
		irgSkillList[1] = 4;
		irgSkillList[2] = 7;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 7 == MOB.byClass2 )
	{
		irgSkillList[0] = 0;
		irgSkillList[1] = 4;
		irgSkillList[2] = 7;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}

	m_iSkillCharged = rand() % 3;//eSkillList_Size;
	int iSkillIndex = 0;

	iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data 배열상의 index

	return pSkillData[iSkillIndex].iAllowedTargets;
}


int CMob::CheckCombat()
{  
	int iDist = 0;
	if( 0 > CurrentTarget || MAX_MOB <= CurrentTarget ) CurrentTarget = 0;
	else
	{
		if( pMob[CurrentTarget].IsDead() ) CurrentTarget = 0;
	}

	if( 0 == CurrentTarget ) return 0x0010;// 더이상 공격할 대상이 없으면 Standingby 모드로 체인지.

	iDist = CalDistance( m_iHandle, CurrentTarget );

	if( iDist > m_kSight.sCombat ) return 0x0010; // 시야 바깥에 있다. 공격 종료

	int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data 배열상의 index
	int iRange = pSkillData[iSkillIndex].iRange;

	if( iRange >= iDist ) return 0x1000;   // 공격 // 사거리 안쪽이다.
	else return 0x0001;   // 추격
}


//@Param
//	- a_bCollided : 꼭 그 자리를 차지해야하는 지에 대한 여부, true이면 꼭 그 위치를 고수해야 한다.
int CMob::SummonRobot( int a_iPC, int x, int y, int a_iDirection )
{
	if( 0 >= a_iPC || MAX_USER <= a_iPC ) return 0;

	int iMob = 0;
	for( int i = ROBOT_START; i < ROBOT_END; ++i )
	{
		if( MOB_EMPTY == pMob[i].Mode )
		{
			iMob = i;
			break;
		}
	}

	if( 0 == iMob ) return 0;

	pMob[iMob].Mode = MOB_PEACE;

	pMob[iMob].MOB = pMob[a_iPC].MOB; // 모든 것을 복사한다.
	memcpy( pMob[iMob].ViewEquip, pMob[a_iPC].ViewEquip, sizeof(pMob[iMob].ViewEquip) );
	pMob[iMob].MOB.byFace = rand() % 8 + 1;
	pMob[iMob].MOB.byHead = rand() % 8 + 1;
	pMob[iMob].Init( iMob ); // 초기화

	short srgTribe[8] = { 1,2, 4,8, 16,32, 64,128, };
	int iTribeIndex = rand() % 8;
	//pMob[iMob].MOB.snTribe = srgTribe[iTribeIndex];
	sprintf( pMob[iMob].MOB.szName, "Tan%d", iMob );

	//m_iBlockedCell = 0;
	pMob[iMob].m_iBlockedCell = 0; // 모두 무시하고 통과한다.

	if( 0 == x || 0 == y )
	{ // 소환 위치기 설정이 되어 있지 않을 경우에는 소환자의 위치를 기반으로 한다.		
		x = TargetX;
		y = TargetY;
	}	

	int iRes = GetEmptyMobGrid( iMob, &x, &y, pMob[iMob].m_iBlockedCell );
	if( FALSE == iRes ) return 0;

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

	pMob[iMob].RouteType = eTNRout_FixPosition;
	pMob[iMob].Formation = 0;

	//pMob[iMob].m_byClan = m_byClan;

	pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_Robot;
	pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_GetCommand;

	pMob[iMob].m_kSight.sPeace = 32;
	pMob[iMob].m_kSight.sCombat = 64;

	pMob[iMob].m_iDirection = a_iDirection;
	                    
	S_SCP_INIT_OTHER_MOB sm;
	GetCreateMob( iMob, &sm );
	sm.byPopType = eTNPrdt_PopNormal; // 소환될 때의 연출 번호
	pMobGrid[y][x] = iMob;
	GridMulticast( x, y, (MSG_STANDARD*)&sm, 0, 100 );

	S_SCP_RESP_EQUIP_SET nm; nm.wType = SCP_RESP_EQUIP_SET;
	nm.nID = iMob; nm.wPDULength = sizeof(S_SCP_RESP_EQUIP_SET)-sizeof(HEADER);
	memcpy(nm.Equip, pMob[iMob].ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);

	GridMulticast( pMob[iMob].TargetX, pMob[iMob].TargetY,(MSG_STANDARD*)&nm, iMob, 30);

	return iMob;
}                			    


void CMob::CallRobot()
{
#ifdef __TN_PLAYMOVIE__
	if( !(eTNAIO_Follow & m_iAIOption) ) return;

	for( int i = 0; i < eRobot_MaxCount; ++i )
	{
		int iMob = m_irgRobot[i];
		if( 0 >= iMob ) continue;
		if( MOB_EMPTY == pMob[iMob].Mode ) continue;
		if( pMob[iMob].IsDead() || pMob[iMob].IsCombat() )
		{
			pMob[iMob].Mode = MOB_EMPTY;
			continue;
		}

		HS2D_COORD kDest;
		kDest.x = TargetX + 5;
		kDest.y = TargetY + 5;
		int x, y;
		x = kDest.x;
		y = kDest.y;
		GetEmptyMobGrid( iMob, &x, &y, 0 );

		MSG_Action sm; GetAction( iMob, x, y, &sm );
		sm.Effect = 3; // run
		//sm.Direction = Direction;
		GridMulticast( iMob, x, y, (MSG_STANDARD*)&sm, 30 );

		//pMob[iMob].OnFollow( m_iHandle );
	}
#endif
}

short CMob::get_WeaponID()
{
	int iWeapon = get_WeaponIndex();
	if( 0 < iWeapon && MAX_ITEM_DATA > iWeapon ) return pItemData[iWeapon].sID;
	return 0;
}

