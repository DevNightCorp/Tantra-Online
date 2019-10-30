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
#define GetMob2MyRandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min));

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
//extern CMob                   pMob     [MAX_MOB];  // �߸���������.
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
	//if( eTNCell_SafetyZone & g_krgCell[TargetY][TargetX].usProperty ) return eTNRes_SafetyZone; // safety zone�̶�� ��� skill�� ������� �ʴ´�.
    int enter_targetcnt = 0;
	enter_targetcnt = a_iTargetCount; //fors_debug ���ּ���Ŀ�괫������ĵط�
	if( eWaitAct_TownPortal == m_kWaitAction.iAction ) 
	{	m_kWaitAction.iAction = eWaitAct_None; m_snMovePortal = 0; 
		if(m_kWaitAction.iAction == eWaitAct_ZonePortal)
		{	char pch[256] = {0,};
			sprintf(pch, "Char:%s pustica is stopped by castskil", MOB.szName);
			Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
		}
	}
	//if( eWaitAct_TownPortal2 == m_kWaitAction.iAction ) return eTNRes_Failed;	//	������ ��ų�� ����Ҽ� ����
	//if( eWaitAct_TownPortal2 == m_kWaitAction.iAction ) m_kWaitAction.iAction = eWaitAct_None;
	//if( eWaitAct_TownPortal3 == m_kWaitAction.iAction ) return eTNRes_Failed;	//	������ ��ų�� ����Ҽ� ����
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

				if((ServerIndex+1) != MOB.bySaveZone)
				{
					pUser[m_iHandle].m_byCloseType = eCloseSystem;
					pUser[m_iHandle].m_byCloseAndGoZone = MOB.bySaveZone;
					pUser[m_iHandle].m_snGoX = MOB.snSaveX;
					pUser[m_iHandle].m_snGoY = MOB.snSaveZ;
				}
				
				return eTNRes_HaveNoGuild;
			}
		}
	}

	//SYSTEMTIME st;
	//GetLocalTime( &st );

	int iRes = eCmbt_Normal; // ������������� ���� ����, ���� ������ ����(hit)�� �ƴϴ�. �ܼ��� ������ ���������� ����Ǿ��ٴ� ���̴�.
	unsigned short usSkillID = a_pMsg->snSkillID;
	TNSKILL_DATA kSkill;
	int iIndex = 0, iSkillBookIndex = MAX_SKILL ;
	TNEFFECT kMulStrike, kMulStrike2; // multiple-strike�� ������ ���Ǵ� ����	

	if( eCmbt_Echo == a_pMsg->snRes )
	{
		BroadcastCastSkill( a_pMsg, a_iTargetCount );
		// hack �˻�
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
	TurnOffAffection( eTNAfn_MoveSpeedMinus2 );
	TurnOffAffection( eTNAfn_Invisible );

	a_pMsg->bySkillLevel = 0; //MOB.bySkill[i];

	if( (eTNSwitch_PKDisable&g_iSwitch) && (eTNMob_PC==m_eMobType) && (eZoneType_Normal == g_iZoneType) )		//	PK��������ϰ��
	{
		if(usSkillID == eTNSkl_NormalAttack)
		{
			for(int i=0; i<TN_MAX_TARGET_COUNT; i++)
			{
				if( a_pMsg->krgTarget[i].snKeyID>0 && a_pMsg->krgTarget[i].snKeyID<MAX_USER )	//	����� ���ݽ� Ÿ�ٿ��� ����
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
			int nIndex = m_krgSkill[i].iIndex;				//+ m_krgSkill[iSkillBookIndex].byLevelPlus; // data �迭���� index

			kSkill = pSkillData[nIndex];
			if(kSkill.iAllowedTargets == eTNAT_Enemy)		//	���� �����ϴ� ��ų�ϰ��
			{
				for(int i=0; i<TN_MAX_TARGET_COUNT; i++)
				{
					if( a_pMsg->krgTarget[i].snKeyID>0 && a_pMsg->krgTarget[i].snKeyID<MAX_USER )	//	����� ���ݽ� Ÿ�ٿ��� ����
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
			iIndex = m_krgSkill[iSkillBookIndex].iIndex; //+ m_krgSkill[iSkillBookIndex].byLevelPlus; // data �迭���� index
		}
		else
		{
			iIndex = m_krgSkill[m_iSkillCharged].iIndex;
			iSkillBookIndex = m_iSkillCharged;
		}

		kSkill = pSkillData[iIndex];


		if( eTNMob_PC == m_eMobType ) 
		{
			if( eZone_Cruma2 == g_iZoneID || eZone_Kalia1 == g_iZoneID || eZone_Kalia2 == g_iZoneID ) // �Ƴ�ī ũ�縶 & Į����
			{
				if( kSkill.kReq.byLevel > MOB.byLevel )
				{
					MoveZoneByNPC( eSaveNPC_Mandra );
					//MoveZone( eZone_Mandra, 486, 190 );
					return eTNRes_LevelIsNotAllowed;
				}
			}
		}

		if( eTNSklD_Unlimited == kSkill.iCastDuration ) return eTNRes_SkillPassiveSkill;
		if( 0 != kSkill.iReqWeapon )
		{
			short iIndex = get_WeaponIndex();
			if( !(kSkill.iReqWeapon & pItemData[iIndex].sItemType) ) return eTNRes_ReqWeapon;
		}
	}

	a_pMsg->bySkillLevel = kSkill.byLevel;




	// �طο� ��ų(normal skill ����)�̰� safety zone�̸�, ��ų�� �ߵ���Ű�� �ʴ´�. - edited by spencer(04.12.17)
	if( !( kSkill.sSkillType & eTNSklT_Aid ) && ( eTNCell_SafetyZone & g_krgCell[TargetY][TargetX].usProperty ) ) return eTNRes_SafetyZone;

	CheckAffections( CurrentTime );


	
	#ifdef __DYNAMIC_LOG__
	//if( eTNMob_PC == m_eMobType )
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\r\n[CastSkill] SkillID %d(lvl:%d)�� ���, target��:%d > ReadyTime: %u, Range: %d, AOE: %d, Now:%u \r\n", usSkillID, kSkill.byLevel, a_iTargetCount, kSkill.iAttackSpeed, kSkill.iRange, kSkill.iAOE, CurrentTime );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif

//fors_debug 1MN
	/*
	// client �޸���
	// client�� �޸𸮸� �����Ͽ� ������ ��ų�� �����ϴ� �ҹ� user�� ��� ���� code
	// <2005.12.08> ��Ƽ�� ��ų�� ��� ��ų ���� �ӵ��� ������ ������.(���� delay�� ���� ���� ��� �ߵ��Ǵ� ������ �߻�)
	// ���� ��ų ����� �޽����� �ι� ������.(echo, cast) �� �� �޽��� ������ �ð��� ���ؼ�
	// ������ �ð����� ������ �۴ٸ�, �� ����� ��찡 �ִ�. �׷��� ���� �̷� ������ �߻��Ѵ�. client�ʿ� Ȯ���� ��û�� ������.
*/	if( eTNMob_PC == m_eMobType )	//fors_debu skill
	{
		int iClientReadyTime = 0;
		int iInterval = 0;
		if( 0 < usSkillID )
		{
			bool bCheckInterval = true;
			int iWeaponIndex = get_WeaponIndex( eTNEqu_OneHandWeapon );
//fors_debug_skill
			//m_kLastTime �ṹ
//	unsigned int uiReadyTime ; //�ϴμ����ͷ�ʱ��
//	unsigned int uiCastTime ; //�ϴμ���������Ҫ���ĵ�ʱ��

			// if( (eTNWpn_Bow & pItemData[iWeaponIndex].sItemType) || (eTNWpn_Staff & pItemData[iWeaponIndex].sItemType) ) bCheckInterval = false;
    /*        if (( kSkill.iAttackSpeed !=0 ) && (kSkill.iReadyTime > 500) && (m_kLastTime.uiReadyTime > 500)) 
		//	if( (usSkillID != 3228) &&  (usSkillID != 3211) &&  (usSkillID != 3014) )
			{// rem before 08 open to crack 1MN 
	//			iInterval = (int)(CurrentTime - m_kSkillCastRecord.uiTime); // ���� �ð����� echo �ð��� �� time interval, �׻� ����̾�� �Ѵ�.
	//			iClientReadyTime = kSkill.iAttackSpeed - iInterval - 100; // ������ ������ �����̴�. ��������:0.1��
	//			if( 0 <= iClientReadyTime ) ++m_kSkillCastRecord.iCount;
				iInterval = (int)(CurrentTime -  m_kLastTime.uiAttacked );
	//			iInterval = (int)(CurrentTime -  m_kLastTime.uiCastTime ); 
		//		iClientReadyTime = kSkill.iAttackSpeed - iInterval - 100; // ������ ������ �����̴�. ��������:0.1��
		     //if ((iInterval <=500) && (iInterval >=150))
			if ((iInterval < kSkill.iReadyTime ) && (iInterval >= 50))  //kSkill.iAttackSpeed
			 {
			//	 ++m_kSkillCastRecord.iCount;
			AddCrackError( m_iHandle, 100, CRACK_SKILLCASTSPEED_HACK );
			return eTNRes_HackUser;
			 }
			} */
	//		m_kLastTime.uiCastTime =CurrentTime;
			//fors_debug ������ʱ����ĵط�,���� curready+lastapply
	        int iIntCheck =0;
			int iNeedTime2 =0;
			g_ParamMgr.HT_bGetPCSkillReadyTime(usSkillID, 1, &iNeedTime2 );
            iIntCheck = (int)(CurrentTime - m_kLastTime.uiReadyTime);
if (usSkillID == 3264 || usSkillID == 3257 || usSkillID == 3245 || usSkillID == 3206 || usSkillID == 3335 || usSkillID == 3334 || usSkillID == 3341 || usSkillID == 3306 || usSkillID == 3312 || usSkillID == 3323 || usSkillID == 3343 || usSkillID == 3322 || usSkillID == 3324 || usSkillID == 3116 || usSkillID == 3109 || usSkillID == 3112 || usSkillID == 3129 || usSkillID == 3162 || usSkillID == 3122 || usSkillID == 3130 || usSkillID == 3143 || usSkillID == 3128 )
            if ( (m_kLastTime.uiCastTime+iNeedTime2) > 500) 
			  if ( iIntCheck < (m_kLastTime.uiCastTime+iNeedTime2) )
				  if ( iIntCheck < 1000 ) 
			  {
	      char temp[100] = { 0,0,0, };
		  sprintf( temp, "SKILL 1MN CHECK: iIntCheck [%d] m_kLastTime.uiCastTime[%d],player[%s],curskillID[%d],curReadyTime[%d],realyneedtime[%d]",iIntCheck,m_kLastTime.uiCastTime,MOB.szName,usSkillID,iNeedTime2,(m_kLastTime.uiCastTime+iNeedTime2));
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP); 
              return eTNRes_SkillNotCoolYet;
			  }

			m_kLastTime.uiReadyTime = CurrentTime;
            int iNeedTime1 =0;

	       g_ParamMgr.HT_bGetPCSkillApplyTime(usSkillID, 1, &iNeedTime1 );

	        m_kLastTime.uiCastTime = iNeedTime1;
            
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

//		if( 5 < m_kSkillCastRecord.iCount )
	//	{
	//		AddCrackError( m_iHandle, 100, CRACK_SKILLCASTSPEED_HACK );
		//	return eTNRes_HackUser;
	//	}
	}
//debug */
	

	// ���� speed �˻�
	unsigned int uiGap = 0;

	bool bNormalAttackOrder = true;

	int iAttackSpeed = kSkill.iAttackSpeed;
	int iVarIndex = eTNVar_CastSpeed; // DD �����̴�.
	if( eTNSklT_EnergyOfSword & kSkill.sSkillType ) iVarIndex = eTNVar_AttackSpeed;
	iAttackSpeed -= Percent( iAttackSpeed, (m_krgVariation[iVarIndex][eVar_Equipment].iPPlus + m_krgVariation[iVarIndex][eVar_PassiveSkill].iPPlus + m_krgVariation[iVarIndex][eVar_Skill].iPPlus) ); 
	iAttackSpeed -= (m_krgVariation[iVarIndex][eVar_Equipment].iPlus + m_krgVariation[iVarIndex][eVar_PassiveSkill].iPlus + m_krgVariation[iVarIndex][eVar_Skill].iPlus );

	if( eTNSkl_NormalAttack == usSkillID )
	{	
		kSkill.iActivateTime = 0; // 400�� �ְ�� ���� ���ǵ� �̴�. ���⿡���� �� ��ġ�� cool-down ���̴�. ���� ������ ���� ���� Ʋ���� �� �ִ�.
		// �ּ� 400 ������ ��Ʈ���̳� ��Ÿ ������ ���ؼ� �׻� ������ �� ����. ���� �ְ� 100���� ������ �س���.
		if( 0 < m_kPrevSkill.sID ) // ��ų ���� ��Ÿ ��� ��, �ð� term�� ª�� ���ش�. ������ client�� ��Ȯ�� �ð��� ���缭 ������ �ϳ�, ���� �׷��� �ʱ� ������ �׳� server������ ���ֵ��� ó������.
		{
			if( CurrentTime < m_kPrevSkill.uiTime + 4000 ) iAttackSpeed = 400;
		}

		if( g_irgSetting[eCnst_SpeedMin] > iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMin];
		else if( g_irgSetting[eCnst_SpeedMax] < iAttackSpeed ) iAttackSpeed = g_irgSetting[eCnst_SpeedMax];		
		//iAttackSpeed = 0; // item�� ���� ready time�� ��� 0�̴�. => edited by spencer(2004.12.17), �� �̷� �ڵ尡 �־�����? �̰��� item�� �ּ� ���� delay�� �����ϴ� ����� �����Ѵ�.
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
		//		sprintf(chBuf, "\t[CastSkill] skill:%d, ������ ������ �ƴѵ� follow�� ���� �ð��� �ִ�.Now:%d, FireHitGapTime: %u > \r\n", usSkillID, CurrentTime, a_pMsg->dwFireHitGapTime );
		//		WriteLog( chBuf, m_szLogFile );
		//	}
		//	#endif
		//}
		a_pMsg->dwFireHitGapTime = 0;
	}

	unsigned int uiAttackTime = CurrentTime - a_pMsg->dwFireHitGapTime; // attackTime : ���� ������ ������ �ð�
	unsigned int uiPreviousAttackTime = m_kLastTime.uiAttacked; // ������ ���������� �����ߴ� �ð�
	if( uiAttackTime < uiPreviousAttackTime )
	{ // �Ųٷ� hit�� ���, �����̻����� ���� ���ݺ��� �� �ʰ� ������ �� �ִ�.		
		uiPreviousAttackTime = m_kLastTime.uiAttackedOld;
		bNormalAttackOrder = false;
	}
	
	uiGap = uiAttackTime - uiPreviousAttackTime; // ���� ���� �ð��� ���� ���� �ð��� ���� ���� ���ϸ� �� ���ݰ��� �ð� ���� ���� �� �ִ�.
	//uiGap = CurrentTime - m_kLastTime.uiAttacked;

	#ifdef __DYNAMIC_LOG__
	if( m_iDebugFlag )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t[CastSkill] Attack Speed �˻�> ReadyTime:%u, Gap(�����ݽ��۽ð�-�������ݽð�):%u, AttackTime:%u, Now:%u, FireHItGapTime:%u, PrevAtkTime:%u(LastAttacked:%u) \r\n"
			, iAttackSpeed, uiGap, uiAttackTime, CurrentTime, a_pMsg->dwFireHitGapTime, uiPreviousAttackTime, m_kLastTime.uiAttacked );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif
	
	if( eTNMob_PC == m_eMobType )
	{
		// ���ǵ��� ���� - ���ġ �˻� routine
		if( eHack_MaxAttackTimeRecordCount > m_iAttackTimeRecordIndex)
		{
			m_uirgAttackTimeRecord[m_iAttackTimeRecordIndex] = CurrentTime;
			++m_iAttackTimeRecordIndex;
		}
		else
		{// 10���� ���� �ð��� ��ϵǾ� �ִ�. ����� ���ؼ� ���� �ð����� �۴ٸ� hacking���� �Ǵ��� �Ѵ�. �ְ� ���� �ӵ��� 400ms�̹Ƿ� 4000(400*10ȸ, 4��) �Ʒ� ��ġ�� ���� �� ����.
			// ������ ù��°�� 10��° �ð����� ���Ѵ�.

			int iTimeGap = m_uirgAttackTimeRecord[eHack_MaxAttackTimeRecordCount-1] - m_uirgAttackTimeRecord[0];
			m_iAttackTimeRecordIndex = 0;
			memset( m_uirgAttackTimeRecord, 0 , sizeof(m_uirgAttackTimeRecord) );

			//if( eHack_MaxAttackTimeGap > uiTimeGap )
			if( g_irgSetting[eCnst_AttackSpeedHack] > iTimeGap )				
			{// ��ŷ(or �õ�) �̴�. ����� ����� ������ ���������.
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
//fors_debug ��ʱ�ȹر������ ���� hack speed
				//AddCrackError( m_iHandle, 100, CRACK_ATTACK_SPEED_HACK );
			}
		}
        if (usSkillID==3042)  m_krgSkill[iSkillBookIndex].uiCoolDownTime =1000;//fors_debug �����Ƿ�������ʹ�õط����޸����ˣ�

		if( eTNSkl_NormalAttack == usSkillID ) uiGap = m_krgSkill[MAX_SKILL].uiCoolDownTime  + iAttackSpeed;
		else uiGap = m_krgSkill[iSkillBookIndex].uiCoolDownTime + iAttackSpeed;
		#ifdef __DYNAMIC_LOG__
		//if( eTNMob_PC == m_eMobType )
		if( m_iDebugFlag )
		{
			char chBuf[256] = { 0,0,0, };
			sprintf(chBuf, "\t[CastSkill] Cooldown �˻�: ���� �ð�: %d, now: %u > uiGap: %d\r\n", uiGap- CurrentTime, CurrentTime, uiGap );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
		if( uiGap > CurrentTime ) // ���� �Ұ�
		{
			return eTNRes_SkillNotCoolYet; //fors_debug ���˻᷵�ص�����?
		}
	} // if( eTNMob_PC == m_eMobType )
	else // monster �� ���
	{
		if( (unsigned int)iAttackSpeed > uiGap )
		{
			//#ifdef __DYNAMIC_LOG__
			//if( m_iDebugFlag )
			//{
			//	WriteLog( "\t[CastSkill] ���ݼӵ� ����(�� ������ ������ �ݺ��Ǹ� ���ǵ����� ���ɼ��� ����\r\n", m_szLogFile );
			//}
			//#endif

			return eTNRes_SkillNotActionYet; // �� ���� ���� �ð� ���� ���ǵ� ���� �ð����� ������, �������� ������ �ƴϹǷ�, �� ���� packet�� skip�� ���ش�.
		}
	}

	
	int iAttackRange = kSkill.iRange;
	if( eTNSklR_WeaponBase == kSkill.iRange ) iAttackRange = pItemData[get_WeaponIndex()].iRange;
	if( TN_RANGE_DISTANT < iAttackRange )
	{
		iAttackRange += (m_krgVariation[eTNVar_RangeUp][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_Skill].iPlus ); // Range Up effect ó��
		iAttackRange -= (m_krgVariation[eTNVar_RangeDown][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeDown][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeDown][eVar_Skill].iPlus ); // Range Down effect ó��

		//#ifdef __DEBUG_LOG__
		//if( m_iDebugFlag )
		//{
		//	char chBuf[256] = { 0,0,0, };
		//	sprintf(chBuf, "\t[CastSkill] AttackRange:%d, RangUp(equip:%d, passive:%d, active:%d), RangeDown(equip:%d, passive:%d, active:%d)"
		//		, iAttackRange
		//		, m_krgVariation[eTNVar_RangeUp][eVar_Equipment].iPlus, m_krgVariation[eTNVar_RangeUp][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_RangeUp][eVar_Skill].iPlus
		//		, m_krgVariation[eTNVar_RangeDown][eVar_Equipment].iPlus, m_krgVariation[eTNVar_RangeDown][eVar_PassiveSkill].iPlus, m_krgVariation[eTNVar_RangeDown][eVar_Skill].iPlus
		//		);
		//	WriteLog( chBuf, m_szLogFile );
		//}
		//#endif
	}
	
	int iBaseAttackRange = iAttackRange; // ���� ��ġ�� ���� ���� ��Ÿ�, melee ������ ��� 2�̴�.

	//iAttackRange += (m_krgVariation[eTNVar_RangeUp][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RangeUp][eVar_Skill].iPlus ); // ��� ��ų ��뿡 ���� range up effect ó��
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
		if( 0 >= a_iTargetCount ) return eTNRes_InvalidTarget0; // unit Ÿ���ε�, Ÿ�ټ��� 0�̶��, ����
		byBodyRadius = m_byBodyRadius;
		if( eTNSklR_Self == kSkill.iRange ) // self & buffer skill�� ���
		{			
			if( m_iHandle != a_pMsg->krgTarget[0].snKeyID ) return eTNRes_InvalidTarget1; // �ڱ� �ڽ��ε�, target�� �ڱ� �ڽ��� �ƴ϶��, ����
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
				if( TN_RANGE_DISTANT > iBaseAttackRange ) // melee �� ��� ���� �˻縦 �Ѵ�.
				{
					// Height ���� ����Ѵ�. added by spencer(2005.1.25)
					int iHeight = g_krgCell[kCasterPos.y][kCasterPos.x].usHeight - g_krgCell[kTargetPos.y][kTargetPos.x].usHeight;
					if( 0 > iHeight ) iHeight = 0 - iHeight; // ������ ��� ����� ������ �Ѵ�.	
					if( 300 < iHeight ) // ���� ���� �̻��̰� melee�����̸�, �Ұ�
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
			//if( sUnitID < MAX_USER ) // ĳ���� �̶��, ������ �� ���ش�.
			//	iAttackRange += (eTNChr_DistCorrect + eTNChr_DistCorrect);

			int iDist = CalDistance( kCasterPos, kTargetPos, byBodyRadius, pMob[sUnitID].get_BodyRadius() );
			if( iDist > iAttackRange )
			{
				#ifdef __DYNAMIC_LOG__
				if( m_iDebugFlag ) // �Ÿ� ������ �ϴ� �ֵ鿡 ���� log�� �����.
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] �Ÿ�����> AOE:Unit, Distance: %d <= AttackRange: %d, Range: %d, caster(%s) ��ġ(%d,%d), taker(%s) ��ġ(%d,%d) - %dmm%ddd %dhh%dms%dmm \r\n"
						, iDist, iAttackRange, kSkill.iRange, MOB.szName, kCasterPos.x, kCasterPos.y, pMob[sUnitID].MOB.szName, kTargetPos.x, kTargetPos.y
						, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
						);
					WriteLog( chBuf, m_szLogFile );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_HackDist] );
				}
				#endif //__TN_4TH_LOG__
				bIsInAttackRange = false; // ��ȿ �Ÿ� ���� ��ġ�ϰ� ���� �ʴٸ�, ...
				if (g_iZoneID == 10) return eTNRes_PathIsBlocked; //fors_debug ֻ�����������Ŵ���һ��Զ��
			}
			else
			{
				int iCheckPath = 1;
				if( eTNMob_NPC == m_eMobType )
				{
					if( eTNReact_Ignore & pMonsterData[MOB.nTP].byQuest[eMonPrty_Reserved6] ) iCheckPath = 0;
				}

				if( iCheckPath ) // �������� �̵��� �ϴ� monster�� ��쿡��, ...
				{// �ֽ��������� ó���� �Ѵ�.
					
					int iRes = IsPathCleared( kCasterPos.x, kCasterPos.y, kTargetPos.x, kTargetPos.y, iDist/*, iAttackRange*/ );
					if( iRes )
					{
						#ifdef __DYNAMIC_LOG__
						if( m_iDebugFlag )
						{
							char chBuf[512] = { 0,0,0, };
							sprintf(chBuf, "\t[CastSkill] ���� ����> Res:%d, height > caster:%d, target:%d, dist:%d \r\n"
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
					sprintf(chBuf, "\t[CastSkill] �Ÿ�> AOE:Unit, Distance: %d <= AttackRange: %d, Range: %d, caster ��ġ(%d,%d), taker ��ġ(%d,%d) \r\n", iDist, iAttackRange, kSkill.iRange, kCasterPos.x, kCasterPos.y, kTargetPos.x, kTargetPos.y );
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
	else if( eTNSklA_Unit < kSkill.iAOE ) // ���� ��ų�̶��, ...
	{
		if( eTNSklR_Self < kSkill.iRange )
		{			
			kTargetPos.x = a_pMsg->snMapX;
			kTargetPos.y = a_pMsg->snMapZ;

			if( CalDistance( kCasterPos, kTargetPos , m_byBodyRadius, 0 ) > iAttackRange )
			{ // caster�� ��ǥ����(map)������ �Ÿ� ����
				#ifdef __DYNAMIC_LOG__
				//if( eTNMob_PC == m_eMobType )
				if( m_iDebugFlag )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] �Ÿ�����> AOE:����, Distance: %d <= AttackRange: %d, Range: %d\r\n", CalDistance( kCasterPos, kTargetPos, m_byBodyRadius, 0 ), iAttackRange, kSkill.iRange );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif
				return eTNRes_OutOfRange;
			}
		}
		else // �ڽ��� �߽����� �ϴ� ���� ��ų�� ���, ��ǥ�������� �Ÿ��� ���� �ʿ䰡 ����.
		{ // iRange�� -1�� ��쵵 �ִ�.
			kTargetPos = kCasterPos;
		}

		byBodyRadius = 0;
		iAttackRange = kSkill.iAOE + eTNChr_DistCorrect;


		for( int i = 0; i < a_iTargetCount; ++i )
		{
			//fors_debug come here log all look look
	//  char temp[256] = { 0,0,0, };
    //sprintf( temp, "log attack skill target:%d when:i %d", a_pMsg->krgTarget[i].snKeyID,i);
    //Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP); 

			if( (0 == kSkill.byFollow) && (0 < kSkill.iAOE) ) // follow�� ���� ���� ������ ���� ������ target�� ���ؼ� �Ÿ� �˻縦 ���ش�.
			{
				
		short sUnitID = a_pMsg->krgTarget[i].snKeyID;  //fors_debug a_pMsg->krgTarget[i].snKeyID come here δ��MD5ǰ��Ⱥ�������ĵط� log about :attack skill target
//if (g_iZoneID != 10 )
//{
		if( pMob[m_iHandle].MOB.snTribe ==TRIBE_NAGA || pMob[m_iHandle].MOB.snTribe ==TRIBE_KINNARA || pMob[m_iHandle].MOB.snTribe == TRIBE_DEVA || pMob[m_iHandle].MOB.snTribe == TRIBE_GARUDA)
//if (((kSkill.sID == 3308 || kSkill.sID == 3321 || kSkill.sID == 3334 || kSkill.sID == 3335) && (i > 9)) || (kSkill.sID != 3308 && kSkill.sID != 3321 && kSkill.sID != 3334 && kSkill.sID != 3335 )  &&  ( i > 3))
if ( enter_targetcnt == TN_MAX_TARGET_COUNT )
if (i > 1)  
if (a_pMsg->krgTarget[i].snKeyID >0 )
  if ((i > 0) && ((i+1)<=TN_MAX_TARGET_COUNT))
  {
//   if (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0)
   if (a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i-1].snKeyID || a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i+1].snKeyID  )
     {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
     }
   if (( a_pMsg->krgTarget[i-1].snKeyID == a_pMsg->krgTarget[i+1].snKeyID ) && (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0) )
   {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
   }

  } 
//}
  if( IDX_MOB >= sUnitID || MAX_MOB <= sUnitID ) continue;

				HS2D_COORD kUnitPos;
				pMob[sUnitID].get_Coord( kUnitPos );

				if( CalDistance( kTargetPos, kUnitPos, 0, pMob[sUnitID].get_BodyRadius() ) > iAttackRange )
				{
					a_pMsg->krgTarget[i].snKeyID = 0;
					//bIsInAttackRange = false; // ��ȿ �Ÿ� ���� ��ġ�ϰ� ���� �ʴٸ�, ...
				}

				#ifdef __TN_4TH_LOG__
				if( eTNMob_PC == m_eMobType )
				{
					char chBuf[256] = { 0,0,0, };
					sprintf(chBuf, "\t[CastSkill] Distance: %d <= AOE %d, ����:%d \r\n", CalDistance( kTargetPos, kUnitPos, byBodyRadius, pMob[sUnitID].get_BodyRadius() ), kSkill.iAOE, bIsInAttackRange );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif //__TN_4TH_LOG__
			}
		}
	}
	else if( eTNSklA_NA == kSkill.iAOE ) // target�� �������� �ʴ� skill�� ���, ��ȯ�� �̿� ���Ѵ�.
	{
		#ifdef __TN_2ND_LOG__
		{
			WriteLog( "[CastSkill] AOE: NA\r\n", m_szLogFile );
		}
		#endif //__TN_2ND_LOG__
	}


	//----------------------------------------------------------------------------
	// Targeting �˻�
	// �����ڿ� ����ڵ鿡 ���� mirror�� �־�� �Ѵ�. ����ڴ� �ټ��� �� �ִ�.
	// �Ʒ����� �����ڿ� ���� �͸� ó���Ǿ��ִ�.
	// �߰��� ����ڿ� ���� mirroring�� ó���ؾ� �Ѵ�.
	//----------------------------------------------------------------------------
	int iAttacker = m_iHandle;
	if( eTNMob_NPC == pMob[iAttacker].m_eMobType ) // ���� �� ������ ���� �ʿ�� ���� ���̴�.
	{// ��ȯ���̶��, targeting�ÿ� attacker�� �������� �����ؼ� �˻��Ѵ�.
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
		{ // monster �̶��
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

		if( sUnitID == m_iHandle )  // �ڱ��ڽ��� Ÿ���� ���, party�� �����ش�.
		{		
			int iTargetIndex = 1;

			int iLeader = Leader;
			if( 0 == Leader ) iLeader = m_iHandle;
			else
			{ // leader�� �߰�
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
	// ���� ���� ���, ���� ��� Ȯ��
	//--------------------------------------------------------------------
	int iDuelOpponent = 0;
	if( 0 < iAttacker && MAX_USER > iAttacker ) // PC�� ��쿡�� 
	{
		if( eChallenge_Combat == pUser[iAttacker].m_nChallengeMode )// �����ڰ� ���� ���̴�. 
		{
			iDuelOpponent = pUser[iAttacker].m_nChallenger;
		}
	}

	//--------------------------------------------------------------------
	// ��� ���� ������ �˾ƿ��� �κ�
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
			if( nTarget>0 && nTarget<MAX_USER )			//	�÷��̾ ��ų������ 
			{
				nTargetGuild = GetGuild(pMob[nTarget].MOB.nGuildID);
				if(strncmp(pGuild[nMyGuild].GUILD.AlliedGuildName1, pGuild[nTargetGuild].GUILD.GuildName, SZGUILD_LENGTH)==0)
					bAllied[i] = true;					//	���ձ�弳��
			}
		}
	}

	int iDefender = 0;
	int iDefClan = 0;
	int iDefGuildID = 0;

	int iInvalidTargetCount = 0;
	for( int i = 0; i < a_iTargetCount; ++i )
	{
		short sUnitID = a_pMsg->krgTarget[i].snKeyID; //fors_debug target[i] come here ͬ���Ⱥ������
//if (g_iZoneID != 10 )
//{
		if( pMob[m_iHandle].MOB.snTribe ==TRIBE_NAGA || pMob[m_iHandle].MOB.snTribe ==TRIBE_KINNARA || pMob[m_iHandle].MOB.snTribe == TRIBE_DEVA || pMob[m_iHandle].MOB.snTribe == TRIBE_GARUDA)
//if (((kSkill.sID == 3308 || kSkill.sID == 3321 || kSkill.sID == 3334 || kSkill.sID == 3335) && (i > 9)) || (kSkill.sID != 3308 && kSkill.sID != 3321 && kSkill.sID != 3334 && kSkill.sID != 3335 )  &&  ( i > 3))
if ( enter_targetcnt == TN_MAX_TARGET_COUNT )
if (i > 1)  
if (a_pMsg->krgTarget[i].snKeyID >0 )
  if ((i > 0) && ((i+1)<=TN_MAX_TARGET_COUNT))
  {
//   if (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0)
   if (a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i-1].snKeyID || a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i+1].snKeyID  )
     {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
     }
   if (( a_pMsg->krgTarget[i-1].snKeyID == a_pMsg->krgTarget[i+1].snKeyID ) && (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0) )
   {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
   }

  }  
//}
  if( 0 >= sUnitID || MAX_MOB <= sUnitID )
		{ 
			++iInvalidTargetCount;
			a_pMsg->krgTarget[i].snKeyID = 0;
			continue; 
		}

		iDefender = sUnitID;
		if( eTNMob_NPC == pMob[iDefender].m_eMobType )
		{ // ��ȯ���̶��, ������ defender�� �����ؼ� targeting �˻��Ѵ�.
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
			{// ����� ����� ƨ���.
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
			{ // ���߿� ������ ���� ���� �ʿ�
			}
			else
			{
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}  	        
		}


		//--------------------------------------------------------------------
		// ���� ���� ���, ���� ��� Ȯ��
		//--------------------------------------------------------------------
		if( 0 < iDuelOpponent ) // �����ڰ� ���� ���̴�.
		{
			if( (iDuelOpponent != iDefender) && (m_iHandle != iDefender) ) // �������ε�.. ��밡 ���� ��밡 �ƴϰų� �ڽŵ� �ƴϴ�.
			{// ���� �߿���, target�� ���� ����̰ų� �ڽ��̾�� �Ѵ�.
				++iInvalidTargetCount;
				a_pMsg->krgTarget[i].snKeyID = 0;
				continue;
			}
		}

		if( 0 < iDefender && MAX_USER > iDefender ) // PC�� ��쿡�� 
		{
			if( eChallenge_Combat == pUser[iDefender].m_nChallengeMode )// ����ڰ� ���� ���̴�. 
			{
				if( (iAttacker != pUser[iDefender].m_nChallenger) && (iAttacker != m_iHandle) ) // �׷� �����ڴ� ���� ����̾�� �Ѵ�. ���� ��밡 �ƴϸ� targeting ����
				{
					++iInvalidTargetCount;
					a_pMsg->krgTarget[i].snKeyID = 0;
					continue;
				}
			}
		}


		//if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
		//{// ����������� ���� guild���� target�� �� �� ����. ��, duel field�� �ƴҶ��̴�.
		//	bool bIsInvalid = false;

		//	if( bIsInvalid )
		//	{
		//		++iInvalidTargetCount;
		//		a_pMsg->krgTarget[i].snKeyID = 0;
		//		continue;
		//	}
		//}

		if( eZoneType_Guild == g_iZoneType ) // ��� ��Ÿ��
		{
			if( eTNCell_DuelZone & g_krgCell[pMob[sUnitID].TargetY][pMob[sUnitID].TargetX].usProperty ) // target�� duel �� �ȿ� �ִٸ�, attacker�� duel�� �ȿ� �־�� �Ѵ�.
			{
				if( eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty )
				{
				}
				else // target�� duel�� �ȿ� �ִµ�, attacker�� duel�� �ȿ� ���� ���, targeting�� �߸��� ���̴�.
				{
					++iInvalidTargetCount;
					a_pMsg->krgTarget[i].snKeyID = 0;
					continue;
				}
			}

			if( eTNMob_NPC == pMob[iDefender].m_eMobType )
			{ // monster �̶��
				if( eTNAT_Enemy == kSkill.iAllowedTargets || eTNAT_EnemyCorpse == kSkill.iAllowedTargets ) pAllowedTarget = (int*)&(g_irgEnemyTableStrH[iAttClan]);
				else if( (eTNAT_Friend == kSkill.iAllowedTargets) || (eTNAT_FriendCorpse == kSkill.iAllowedTargets) || (eTNAT_FriendNParty == kSkill.iAllowedTargets) ) pAllowedTarget = (int*)&g_irgFriendTableStrH[iAttClan];
			}
			else
			{ 
				if( eTNMob_PC == pMob[iAttacker].m_eMobType ) pAllowedTarget = NULL; // ������ ������ ��� PC�� ���				
			}
		}

		if( (NULL != pAllowedTarget) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
		{
			int iNotChallengeMode = 1; // �� ���°� �Ϲ� ����, ���� ����̸� ģ���� ���� �ȴ�.
			int iFlag = pAllowedTarget[iDefClan]; // ���ΰ�? true�̸� ģ���̰� false�̸� ���̴�.

			if( eTNMob_PC == pMob[iAttacker].m_eMobType ) // caster(������)�� PC�̶��, ...
			{
				if( iDefender == pUser[iAttacker].m_nChallenger ) iNotChallengeMode = 0; // ���� ���� �����̴�. �׷� ���̹Ƿ� ���ݰ���
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
			        
			if( eTNMob_PC == pMob[iAttacker].m_eMobType ) // caster(������)�� PC�̶��, ...
			{
				if( eTNMob_PC == pMob[iDefender].m_eMobType ) // �� �� PC��� PK ������ Ȯ��������Ѵ�.    		
				{// sUnitID�� iDefender�� �����ϴ�.
					if( iDefender == iAttacker ) bIsInvalid = true; //return eTNRes_TargetSelf; // �ڱ��ڽſ��� �طο� skill(item)�� �� ���, ...
					
					int iSiege = g_kSiege.get_Started();
					if( !iSiege ) // �������� �ƴ϶��
					{
						if( ((g_irgSetting[eCnst_Restriction] > pMob[iAttacker].MOB.byLevel) || (g_irgSetting[eCnst_Restriction] > pMob[iDefender].MOB.byLevel)) 
							&& pUser[iAttacker].m_nChallenger!=iDefender ) bIsInvalid = true;
					}
					if( eTNVSAfn_ProtectFromPK & pMob[iAttacker].m_iAffections ) bIsInvalid = true;
					if( eTNVSAfn_ProtectFromPK & pMob[iDefender].m_iAffections ) bIsInvalid = true;

					if( (eZoneType_Guild == g_iZoneType) && !(eTNCell_DuelZone & g_krgCell[TargetY][TargetX].usProperty) )
					{// ����������� ���� guild���� target�� �� �� ����. ��, duel field�� �ƴҶ��̴�.
						// ���� �����̸� target�� �� �� ����. �κ��� �߰��� ��
						if( iDefGuildID == iAttGuildID ) bIsInvalid = true;	//	�������� ��������
						else if(bAllied[i]) bIsInvalid = true;									//	���ձ��� ��������
					}

					// party������ ������ �� ����.
					if( pMob[iAttacker].IsParty( iDefender ) ) bIsInvalid = true;					
				}
				else // defender�� npc �̶��, ��ȯ���� PC�� �ν�����.
				{
					if( eTNCell_DontAttackMonster & g_krgCell[TargetY][TargetX].usProperty ) bIsInvalid = true;

					// [ToDo] �Ʒ��� Ȯ���� �غ��� �Ѵ�.
					//if( sUnitID  == m_iFamiliar ) bIsInvalid = true; // �� familiar�� ���, ...
					//if( sUnitID  == m_iRetainer ) bIsInvalid = true; // �� retainer�� ���, ...
					//if( eTNCls_Summoned == pMob[sUnitID].MOB.byClass1 )
					//{ // �� ��Ƽ�� faimiliar���� Ȯ���� ����� �Ѵ�.
					//	int iParty = 0;
					//	int iLeader = Leader;
					//	if( 0 == iLeader ) iLeader = m_iHandle;
					//	for(int p = 0; p < MAX_PARTY; ++p )
					//	{
					//		iParty = pMob[iLeader].m_irgParty[p];
					//		if( 0 >= iParty || MAX_USER <= iParty ) continue;
					//		if( sUnitID == pMob[iParty].m_iFamiliar ) bIsInvalid = true; // �� ��Ƽ�� familiar�̴�.
					//		if( sUnitID == pMob[iParty].m_iRetainer ) bIsInvalid = true; // �� ��Ƽ�� familiar�̴�.
					//	}
					//}
				}
			} // if( eTNMob_PC == m_eMobType ) // caster(������)�� PC�̶��, ...
			else // attacker�� monster�̴�.
			{
				if( eTNVSAfn_ProtectFromMonster & pMob[sUnitID].m_iAffections ) bIsInvalid = true;
				if( sUnitID == Leader ) bIsInvalid = true; // ��ȯ���� ������ ������ �� ����.
			}		
			
			if( !bIsInvalid )
			{	
				if( 0 >= pMob[sUnitID].TargetY || MAX_GRIDY <= pMob[sUnitID].TargetY ) bIsInvalid = true;
				if( 0 >= pMob[sUnitID].TargetX || MAX_GRIDX <= pMob[sUnitID].TargetX ) bIsInvalid = true;
				if( eTNCell_SafetyZone & g_krgCell[pMob[sUnitID].TargetY][pMob[sUnitID].TargetX].usProperty ) bIsInvalid = true;
				if( eTNImm_All == pMob[sUnitID].m_iImmunity ) bIsInvalid = true; // npc�� contact�ϱ� ���ؼ� �����µ�, NPC contact message�� ���� �������.
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
			{// ����������� ���� guild���� target�� �� �� �ִ�. ��, duel field�� �ƴҶ��̴�.
				// ���� ������ target�� �� �� �ִ�. �κ��� �߰��� ��
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	������峪 ���±������Ը� ����
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
			{// ����������� ���� guild���� target�� �� �� �ִ�. ��, duel field�� �ƴҶ��̴�.
				// ���� ������ target�� �� �� �ִ�. �κ��� �߰��� ��
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	������峪 ���±������Ը� ����
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
			{// ����������� ���� guild���� target�� �� �� �ִ�. ��, duel field�� �ƴҶ��̴�.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	������峪 ���±������Ը� ����
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
			{// ����������� ���� guild���� target�� �� �� �ִ�. ��, duel field�� �ƴҶ��̴�.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	������峪 ���±������Ը� ����
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
			{// ����������� ���� guild���� target�� �� �� �ִ�. ��, duel field�� �ƴҶ��̴�.
				if( pMob[sUnitID].MOB.nGuildID != MOB.nGuildID && !bAllied[i]) bIsInvalid = true;	//	������峪 ���±������Ը� ����
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
		return eTNRes_InvalidTarget3;  // Ÿ���� �ϳ��� ����.
	}


/*
	if( eTNSkl_NormalAttack == usSkillID )
	{ // retainer���� ���� ����� �־���� �Ѵ�.
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
		if( eItm_Arrow == kSkill.kCost.sItemID ) // ȭ���̶�� shield_slot�� �����Ǿ� �ִ�.
		{
			if( kSkill.kCost.sItemID != pItemData[MOB.Equip[eTNEqu_Shield].snIndex].sID ) return eTNRes_CostItem;
			--MOB.Equip[eTNEqu_Shield].byCount;
			a_pMsg->snPackCount = MOB.Equip[eTNEqu_Shield].byCount;
			if( 0 >= MOB.Equip[eTNEqu_Shield].byCount ) ZeroMemory(&(MOB.Equip[eTNEqu_Shield]), sizeof(STRUCT_ITEM));			
		}
		else if( 0 < kSkill.kCost.sItemID )
		{// �������� inventory���� ã�Ƽ� ������ ����� �Ѵ�.
			int irgSlot[eConst_CheckItemSlot] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };
			int iCount = 0;
			iCount = CheckItem( kSkill.kCost.sItemID, kSkill.kCost.byItemCount, irgSlot );
			if( iCount >= kSkill.kCost.byItemCount ) RemoveItem( kSkill.kCost.byItemCount, irgSlot );
			else return eTNRes_CostItem;
		}
		
		DecHP( kSkill.kCost.iHP );
		DecTP( iCostTP );

		// party���鿡�� HP ���¸� ǥ��
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
			// party���� ������ ���� UpdateStatus �޽��� ����
		}
	}
	else // NPC
	{
		if( 0 < kSkill.kCost.iHP ) // monster�� ��쵵 HP�� cost�� �Ҹ��� �� �ִ�.
		{
			if( MOB.nHP < kSkill.kCost.iHP ) return eTNRes_CostHP;
			DecHP( kSkill.kCost.iHP );
		}

		if( 0 < kSkill.sSpeak && eTNSpch_MaxCommentCount > kSkill.sSpeak ) // ���ϱⰡ ��ϵǾ� �ִٸ�, ...
		{
			Speak( kSkill.sSpeak, a_pMsg->krgTarget[0].snKeyID, eTNAI_None );
		}
	}

	a_pMsg->snRes = (short)eTNRes_Succeeded; // ������ �������� ����
	TNDAMAGE kDamageSrc;
	if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
	{		    
        CalDamage( kDamageSrc, kSkill );

		if( eTNSkl_NormalAttack != usSkillID ) //��ų �����̰�
		{
			if( m_bDualWeapon ) // �̵����� ���
			{		
				if( m_kDualHit.Random() ) // �޼� ���⸦ ����� Ȯ�� ����, m_krgMastery[eWpnMtryIdx_DualWpn].iParam1
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
		else // �Ϲ� ����
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
		short sUnitID = a_pMsg->krgTarget[i].snKeyID;//fors_debug target[i] come here Ⱥ��
//if (g_iZoneID != 10 )
//{
		if( pMob[m_iHandle].MOB.snTribe ==TRIBE_NAGA || pMob[m_iHandle].MOB.snTribe ==TRIBE_KINNARA || pMob[m_iHandle].MOB.snTribe == TRIBE_DEVA || pMob[m_iHandle].MOB.snTribe == TRIBE_GARUDA)
//if (((kSkill.sID == 3308 || kSkill.sID == 3321 || kSkill.sID == 3334 || kSkill.sID == 3335) && (i > 9)) || (kSkill.sID != 3308 && kSkill.sID != 3321 && kSkill.sID != 3334 && kSkill.sID != 3335 )  &&  ( i > 3))
if ( enter_targetcnt == TN_MAX_TARGET_COUNT )
if (i > 1)  
if (a_pMsg->krgTarget[i].snKeyID >0 )
  if ((i > 0) && ((i+1)<=TN_MAX_TARGET_COUNT))
  {
//   if (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0)
   if (a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i-1].snKeyID || a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i+1].snKeyID  )
     {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
     }
   if (( a_pMsg->krgTarget[i-1].snKeyID == a_pMsg->krgTarget[i+1].snKeyID ) && (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0) )
   {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
   }

  }
//}
  if( IDX_MOB >= sUnitID || MAX_MOB <= sUnitID ) continue;

		if( eTNAT_Enemy == kSkill.iAllowedTargets )
		{
			if( pMob[sUnitID].IsDead() )
			{
				a_pMsg->krgTarget[i].byRes = eCmbt_Dodge;
				a_pMsg->krgTarget[i].iDamage = 0;
				a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;//0�� ���̴�.
				a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
				continue;
			}

			if( !(eTNCPhase_StartAction & kSkill.sCombatPhase) ) pMob[sUnitID].OnUnderAttack( m_iHandle );

			// ----------------------------------------------------
			// ���� ����, ������,  ������
			// ----------------------------------------------------
			if( eZoneType_Normal == g_iZoneType )
			{
				int iAttacker = m_iHandle;
				if( eTNAIO_HaveMaster & m_iAIOption )
				{
					if( 0 < Leader && MAX_USER > Leader ) iAttacker = Leader;
				}
				
				bool bCheckFirstStrike = false;
				if( eTNMob_PC == pMob[iAttacker].m_eMobType ) bCheckFirstStrike = true; // caster(������)�� PC�̶��, ...
			
				if( bCheckFirstStrike )
				{ //
					int iDefender = sUnitID;
					if( eTNAIO_HaveMaster & pMob[sUnitID].m_iAIOption )					
						if( 0 < pMob[sUnitID].Leader && MAX_USER > pMob[sUnitID].Leader ) iDefender = pMob[sUnitID].Leader;

					if( eTNMob_PC == pMob[iDefender].m_eMobType ) // �� �� PC��� PK ������ Ȯ��������Ѵ�.    		
					{
						if( 0 == pMob[iAttacker].MOB.snKarma &&  0 == pMob[iDefender].MOB.snKarma ) //�� �� �����ڰ� �ƴ� ��쿡��, ���� ���� ó���� ���ش�.
						{
							int iUnderSiege = g_kSiege.get_Started();
							if( !iUnderSiege )
							{ // �������� �ƴ϶��, ...
								if( (0 == pMob[iDefender].m_uiPkDurTime) && (pUser[iAttacker].m_nChallenger != iDefender) ) // �ֽ����� �ƴϰ�, ����ڰ� ���� �����ڰ� �ƴ� ���
								{
									pMob[iAttacker].m_iPKDefender = iDefender;
									pMob[iAttacker].m_iAffections = pMob[iAttacker].m_iAffections | eTNVSAfn_PKAttacker;
									if( 0 == pMob[iAttacker].m_uiPkDurTime ) BroadcastUpdateStatusMsg();
									pMob[iAttacker].m_uiPkDurTime = CurrentTime + g_irgSetting[eCnst_FirstStrikeDur];					
								}
							} // if( !iUnderSiege )
						} // if( 0 == pMob[iAttacker].MOB.snKarma &&  0 == pMob[iDefender].MOB.snKarma ) 
					} // if( eTNMob_PC == pMob[iDefender].m_eMobType ) // �� �� PC��� PK ������ Ȯ��������Ѵ�.  
				} // if( bCheckFirstStrike )
			}
		}

		bool bCheckDodgeSpeed = true;
		if( eTNSklT_MultipleStrike & kSkill.sSkillType )
		{
			if( 0 < i ) bCheckDodgeSpeed = false;
		}

		if( bIsInAttackRange ) // ��Ÿ� �̳��� �ִٸ�, ...
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
					sprintf(chBuf, "[CastSkill] �����(%d, %s)�� ȸ���Ͽ���. \r\n", a_pMsg->krgTarget[i].snKeyID, pMob[a_pMsg->krgTarget[i].snKeyID].MOB.szName );
					WriteLog( chBuf, m_szLogFile );
				}
				#endif // __TN_3RD_LOG__
				continue;
			}

			
			if( (eTNVSAfn_ProtectFromAttackOnlyOnce & pMob[sUnitID].m_iAffections) && (!( kSkill.sSkillType & eTNSklT_Aid )) )
			{ // �طο� ��ų�� casting�� ������ �ߴ�. ������ eTNVSAfn_ProtectFromAttackOnlyOnce ȿ���� ���� ��� ���õȴ�.
				a_pMsg->krgTarget[i].byRes = (byte)eCmbt_Normal;
				a_pMsg->krgTarget[i].iDamage = 0;
				a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
				a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;

				pMob[sUnitID].RemoveEffect( eTNAfn_ProtectFromAttackOnlyOnce );
				continue;
			}

			

			// ���� ������ ���			
			int iDamage = 0;
			if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
			{
				TNDAMAGE kDamage = kDamageSrc;
				if( eTNSkl_NormalAttack != usSkillID ) iRes = eCmbt_Normal;
				else
				{
					if( eCmbt_Critical == iRes )
					{
						double dPercent = 200; // default�� 200%
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
						// critical ��, �Ӽ� ���� ���� 2��� �Ѵ�.
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
							pMob[sUnitID].OnTakeDamage( kBonusDamage, m_iHandle,eCon_MaxGap,kSkill.sID );
							iDamage += kBonusDamage.iSum;
						}
					}
				}

				if( 0 == i ) UpdateEquipDur( iDamage, 1 ); // ���� 1ȸ�� ������ 1�� ��������.

				if( eTNCPhase_CastInstant3 & kSkill.sCombatPhase ) CastInstant3( kSkill, pMob[sUnitID].m_iLastDamage ); // steal HP/MP ����

				// ���� ������ ���� �ÿ� �̰��� �߰��� ����� �� ���̴�.
				// if( eTNVSAfn_StealHP & m_iAffections ) // HP ���
				// if( eTNVSAfn_StealMP & m_iAffections ) // MP ���

				//if( eTNCPhase_Taunt & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant0( kSkill, pMob[sUnitID].m_iLastDamage, m_iHandle );
			}// if( eTNCPhase_DealDamage & kSkill.sCombatPhase )

			
			if( !( kSkill.sSkillType & eTNSklT_Aid ) ) // �طο� ��ų�� ���,
			{// �̷ο� ��ų�̸� ������ effect�� ������ �ȵȴ�.				
				pMob[sUnitID].TurnOffAffection( eTNAfn_Sleep );				
				pMob[sUnitID].TurnOffAffection( eTNAfn_MoveSpeedMinus2 );
				pMob[sUnitID].TurnOffAffection( eTNAfn_Invisible );
				
			}

			if( eTNCPhase_OnTakeInstant1 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant1( m_iHandle, kSkill ); // ��ü����
			if( eTNCPhase_OnTakeInstant2 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant2( m_iHandle, kSkill, iSkillBookIndex ); // alive ����			
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
			{// func���� 1�� ��쿡�� effect #1�� param���� �����ȴ�.
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

			if( eCmbt_Normal == iRes || eCmbt_Critical == iRes ) // ������ ������ ����, ����ȴ�. 
			{ // ���Ⱑ ���� ������ �ƴ� ���� �ִ°�?
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

				if( eWaitAct_TownPortal  == pMob[sUnitID].m_kWaitAction.iAction ) { pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; m_snMovePortal = 0; } // ����ϴ� action�� ��������.
				if(m_kWaitAction.iAction == eWaitAct_ZonePortal)
				{	char pch[256] = {0,};
					if(0<sUnitID && sUnitID<MAX_USER)
						sprintf(pch, "Char:%s pustica is stopped by Char:%s's castskill", pMob[sUnitID].MOB.szName, MOB.szName);
					else
						sprintf(pch, "Char:%s pustica is stopped by Monster:%s's castskill", pMob[sUnitID].MOB.szName, MOB.szName);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
				}
				//if( eWaitAct_TownPortal2 == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; // ����ϴ� action�� ��������.
				//if( eWaitAct_TownPortal3 == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None; // ����ϴ� action�� ��������.
				if( eWaitAct_SummonParty == pMob[sUnitID].m_kWaitAction.iAction ) pMob[sUnitID].m_kWaitAction.iAction = eWaitAct_None;

				if( m_iHandle != sUnitID ) // �����ڿ� 
				{
					TNDAMAGE kDamageReflected;
					int iReflectDamage = pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_PassiveSkill].iPPlus;
					if( 0 > iReflectDamage ) iReflectDamage = 0;
					if( g_irgSetting[eCnst_ReflectMax] < iReflectDamage ) iReflectDamage = g_irgSetting[eCnst_ReflectMax];

					kDamageReflected.irgPierce[0] = Percent( iDamage, iReflectDamage );

					// 2005.4.25, �ű� reflect damage ��� �߰�, added by spencer
					kDamageReflected.irgPierce[0] += pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_PassiveSkill].iPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPlus;

					if( 0 < kDamageReflected.irgPierce[0] )
					{
						OnTakeDamage( kDamageReflected, sUnitID,eCon_MaxGap,kSkill.sID );
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
		else // ��Ÿ� �ٱ��� �ִ�. ȸ�Ƿ� ó��
		{
			a_pMsg->krgTarget[i].byRes = (byte)eCmbt_Dodge;
			a_pMsg->krgTarget[i].iDamage = 0;
			a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
			a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;
		}

	
		#ifdef __DYNAMIC_LOG__
		if( pMob[sUnitID].m_iDebugFlag )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "*** Caster(%d, %s)�� ���� ��ų/������(%d) ���, %dȸ ���ݰ��:%d(0,1:����, 2:����), ��Ÿ��̳�:%d -> �����(%d, %s)�� Damage:%d�� �޾Ƽ� HP�� %d�� �Ǿ���. Affections:%u \r\n"
				, m_iHandle, MOB.szName				
				, a_pMsg->snSkillID, i+1, a_pMsg->krgTarget[i].byRes, bIsInAttackRange, a_pMsg->krgTarget[i].snKeyID, pMob[a_pMsg->krgTarget[i].snKeyID].MOB.szName, a_pMsg->krgTarget[i].iDamage, a_pMsg->krgTarget[i].iHP, a_pMsg->krgTarget[i].iAffection );
			pMob[sUnitID].Print( chBuf );
		}

		if( m_iDebugFlag )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[CastSkill] ��ų/������(%d) ���, %dȸ ���ݰ��:%d(0,1:����, 2:����), ��Ÿ��̳�:%d -> �����(%d, %s)�� Damage:%d�� �޾Ƽ� HP�� %d�� �Ǿ���. Affections:%u \r\n"
				, a_pMsg->snSkillID, i+1, a_pMsg->krgTarget[i].byRes, bIsInAttackRange, a_pMsg->krgTarget[i].snKeyID, pMob[a_pMsg->krgTarget[i].snKeyID].MOB.szName, a_pMsg->krgTarget[i].iDamage, a_pMsg->krgTarget[i].iHP, a_pMsg->krgTarget[i].iAffection );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif
	}

	if( eTNSklT_MultipleStrike & kSkill.sSkillType )
	{// func���� 1�� ��쿡�� effect #1�� param���� �����ȴ�.
		if( (1 == kSkill.krgEffect[0].kFunc.iData) && (eTNCPhase_OnAffect & kSkill.sCombatPhase) )
		{
			short sUnitID = a_pMsg->krgTarget[0].snKeyID;
			pMob[sUnitID].AddEffect( kMulStrike, m_iHandle, m_iHandle );
			pMob[sUnitID].AddEffect( kMulStrike2, m_iHandle, m_iHandle );
		}
	}

	if( (eTNSkl_NormalAttack==usSkillID) && m_bDualWeapon ) //�Ϲ� �����̰� �̵����� ���
	{
		if( m_kDualHit.Random() ) // �޼� ���⸦ ����� Ȯ�� ����, m_krgMastery[eWpnMtryIdx_DualWpn].iParam1
		{
			memset( &(a_pMsg->krgTarget[1]), 0, sizeof(a_pMsg->krgTarget[1]) );
			a_pMsg->krgTarget[1].snKeyID = a_pMsg->krgTarget[0].snKeyID;
			a_iTargetCount = 2;
			UseLeftWeapon( a_pMsg );
		}	
	}

	// ���� ��� ������ activateTime�� 1000 �̴�. �׷��Ƿ� ���������� �ٷ� �ٸ� action�� �Ұ��ϴ�.
	// PC ���, skill�� ���� activateTime�� ApplyTime��(attack point������ �ð��� ����. attack point ��ġ�� ��ų���� ���� Ʋ����.)�� ����.
	// item�� ��Ÿ�� ����ε�.. �̶����� attack point ������ ������ �ð��� ����.
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
		unsigned int uiCoolDownCorrect = (unsigned int)(kSkill.iCoolDownTime * 0.2);

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
					sprintf(chBuf, "[CastSkill] ��ų/������(%d) ���, ���� ��ٿ�:%u, �������ٿ�:%u(����:%d) \r\n"
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
	if( 0 < m_iHandle && MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendMessage(); // PC�� ���, ...

	for( int i = 0; i < a_iTargetCount; ++i )
	{
		short sUnitID = a_pMsg->krgTarget[i].snKeyID; //fors_debug target[i] come here Ⱥ��
//if (g_iZoneID != 10 )
//{		
		if( pMob[m_iHandle].MOB.snTribe ==TRIBE_NAGA || pMob[m_iHandle].MOB.snTribe ==TRIBE_KINNARA || pMob[m_iHandle].MOB.snTribe == TRIBE_DEVA || pMob[m_iHandle].MOB.snTribe == TRIBE_GARUDA)
//if (((kSkill.sID == 3308 || kSkill.sID == 3321 || kSkill.sID == 3334 || kSkill.sID == 3335) && (i > 9)) || (kSkill.sID != 3308 && kSkill.sID != 3321 && kSkill.sID != 3334 && kSkill.sID != 3335 )  &&  ( i > 3))
if ( enter_targetcnt == TN_MAX_TARGET_COUNT )
if (i > 1)  
if (a_pMsg->krgTarget[i].snKeyID >0 )
  if ((i > 0) && ((i+1)<=TN_MAX_TARGET_COUNT))
  {
//   if (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0)
   if (a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i-1].snKeyID || a_pMsg->krgTarget[i].snKeyID == a_pMsg->krgTarget[i+1].snKeyID  )
     {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
     }
   if (( a_pMsg->krgTarget[i-1].snKeyID == a_pMsg->krgTarget[i+1].snKeyID ) && (a_pMsg->krgTarget[i-1].snKeyID >0 && a_pMsg->krgTarget[i+1].snKeyID >0) )
   {
	  char temp[256] = { 0,0,0, };
	  	  sprintf( temp, "log attack skill target:%d when:i %d skillid: %d,target-1: %d,target+1: %d", a_pMsg->krgTarget[i].snKeyID,i,kSkill.sID,a_pMsg->krgTarget[i-1].snKeyID,a_pMsg->krgTarget[i+1].snKeyID);
          Log(temp, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);        
          CloseUser(m_iHandle);
          return eTNRes_InvalidTarget9;
   }

  }
//}
  if( IDX_MOB > sUnitID || MAX_MOB <= sUnitID ) continue;

		if( TRIBE_DEVA != pMob[sUnitID].MOB.snTribe && TRIBE_GARUDA != pMob[sUnitID].MOB.snTribe ) pMob[sUnitID].m_kLastTime.uiCombat = CurrentTime + eDly_TPRecv;
		if( eTNCPhase_StatusChanged & kSkill.sCombatPhase ) // eTNCPhase_OnTakeInstant2 + eTNCPhase_OnAffect
		{
			//pMob[sUnitID].NotifyUpdateStatusMsg(); // cast_unit/area_skill �޽����� ������ �ߺ� ���ԵǾ� ���� ���̴�.
			pMob[sUnitID].BroadcastUpdateStatusMsg();
			pMob[sUnitID].NotifyUpdateUIMsg();
		}
		if( eTNSklT_ChangeTP & kSkill.sSkillType )
		{
			pMob[sUnitID].NotifyUpdateStatusMsg(); // TP ���濡 ���� ��!!
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

	//if( eTNSklA_NA == kSkill.iAOE ) CastOnly( kSkill ); // ����skill���� ����Ѵ�.
	if( eTNCPhase_CastOnly & kSkill.sCombatPhase ) CastOnly( kSkill );

	if( IsDead() ) OnKilled( a_pMsg->krgTarget[0].snKeyID, 0 );


	return eTNRes_Succeeded;
}



// Pierce damage�� ���� ������ �ʿ��ϴ�.
void CMob::CalDamage( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iHand )
{
	a_kDamage = a_kSkill.kDamage;

	// �Ʒ��� ������ ���� �� �� �ڵ��� �� ���� �� ������, ��ȭ�� ���� ���輺���� �������� ����.
	if( eTNMob_PC == m_eMobType )
	{
		if( eTNSklT_EnergyOfSword & a_kSkill.sSkillType ) a_kDamage = m_krgDamage[a_iHand]; // ���� ����� skill
		else // DD skill �� ���
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

	if( !(eTNSklT_EnergyOfSword & a_kSkill.sSkillType) ) // ���� ����� ������ �ƴ� ���(DD, DOT, ...)
	{
		if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe ) // ������ ����
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
		} //if( TRIBE_DEVA == MOB.snTribe || TRIBE_GARUDA == MOB.snTribe ) // ������ ����


		//--------------------------------------   % ����   -------------------------------------
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


		//----------------------------------   +/- ����   -----------------------------------------
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
	} //if( !(eTNSklT_EnergyOfSword & a_kSkill.sSkillType) ) // ���� ������ �ƴ� ���, ...

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


// combatphase : 1 (4�� ���� ���ԵǾ� �־�� �Ѵ�.)
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


// combatphase : 2(4�� ���� ���ԵǾ� �־�� �Ѵ�.)
void CMob::CastInstant2( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iTarget, int& a_iCriticalHit )
{
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 >= a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant != a_kSkill.krgEffect[i].iDuration ) continue;
		switch( a_kSkill.krgEffect[i].iID )
		{
		case eTNAfn_MultipleStrike : // instant1
			{//���� damage�� ������ �ִ°�?				
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
			{ //���� damage�� ������ �ִ°�?
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit�� �����ƴٸ�, �߰� critical hit�� ����.

				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon�� Ư�� �ɷ��� ��, ...
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
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit�� �����ƴٸ�, �߰� critical hit�� ����.
				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon�� Ư�� �ɷ��� ��, ...
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
				if( eCmbt_Critical == a_iCriticalHit ) break; // critical hit�� �����ƴٸ�, �߰� critical hit�� ����.

				if( 0 >= a_iSkillBookIndex || MAX_SKILL < a_iSkillBookIndex ) break;
				if( MAX_SKILL == a_iSkillBookIndex ) // weapon�� Ư�� �ɷ��� ��, ...
				{
					int iDice = rand() % 100;
					if( iDice >= a_kSkill.krgEffect[i].iParam1 ) break;
				}
				else
                    if( !m_krgSkill[a_iSkillBookIndex].kDeck.Random() ) break;

				a_kDamage.iDecDef = a_kSkill.krgEffect[i].iParam2; // ������ iDecDef(%)��ŭ �پ�� �Ŀ� damage�� ���ȴ�.
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
				if( 0 >= a_iTarget || MAX_USER <= a_iTarget ) break; // monster�� ��� skip
				int iBurnTP = Percent( pMob[a_iTarget].m_iMaxTP, a_kSkill.krgEffect[i].iParam1 );
				if( iBurnTP >= pMob[a_iTarget].MOB.nTP ) iBurnTP = pMob[a_iTarget].MOB.nTP;
				pMob[a_iTarget].DecTP( iBurnTP );

				// party���鿡�� TP ���¸� ǥ��
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
					// party���� ������ ���� UpdateStatus �޽��� ����
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
				if( iDice < a_kSkill.krgEffect[i].iParam1 ) // Ȯ��
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
		case eTNAfn_BonusDamage : // ������, pierce damage type�� ���ʽ��� �����ش�.
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
		case eTNAfn_BonusDamage2 : // ������, �Ϲ� ���� damage type�� ���ʽ��� �����ش�.
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
		case eTNAfn_BonusDamage3 : // ������ �̻���¿� �ɷ� �ִٸ�, ���ʽ��� �����ش�.
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
		case eTNAfn_BonusDamage7 : // ������ �̻�����϶�, ��� ���ʽ��� �����ش�.
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
		case eTNAfn_BonusDamage4 : // ���� ȸ������ ���� ��ġ���� �۴ٸ�, ���ʽ��� �����ش�.
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
		case eTNAfn_BonusDamage5 :// Ư�� ���⸦ �����ϰ� ������ 
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
			{ // �ڽ��� �ٷ� ���� ���°� � �����϶�?
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
		case etnAfn_BonusDamage8 : // pierce damage ���ʽ��� �����ش�.
			{
				int iMinDamage = PlayDice( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2);
				a_kDamage.irgPierce[0] += iMinDamage;
				a_kDamage.irgPierce[1] += iMinDamage;
			}
			break;
		case etnAfn_BonusDamage9 : // 0,1�� �����Ͽ� MaxHP�� ����MaxHP������ Damage�� Ȯ���� �߰�
			{
				if( 0 == a_kSkill.krgEffect[i].kFunc.iData ) // 0�϶� ���غ��� ������ �߰�
				{
					if( m_iMaxHP > a_kSkill.krgEffect[i].iParam1 )
					{
						int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam2 );			
						int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 )	;		
						a_kDamage.irgPierce[0] += iMinDamage;
						a_kDamage.irgPierce[1] += iMaxDamage;
					}
				}else if( 1 == a_kSkill.krgEffect[i].kFunc.iData ) // 1�϶� ���غ��� ������ �߰�
				{
					if( m_iMaxHP < a_kSkill.krgEffect[i].iParam1 )
					{
						int iMinDamage = Percent( a_kDamage.irgBase[0], a_kSkill.krgEffect[i].iParam2 );			
						int iMaxDamage = Percent( a_kDamage.irgBase[1], a_kSkill.krgEffect[i].iParam2 );			
						a_kDamage.irgPierce[0] += iMinDamage;
						a_kDamage.irgPierce[1] += iMaxDamage;
					}
				}
			}
			break;
		case eTNAfn_SlayerItem :
			{
				if( 0 == a_kSkill.krgEffect[i].kFunc.iData )
				{ // monster family, reserved0 field�� ��ü������ ���
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


// combatphase : 4 fors_debug deal_damage
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

    short sLevelGap = pMob[a_iTarget].MOB.byLevel - MOB.byLevel + eCon_MaxGap; // ����� - ������ + eCon_MaxGap
    if( 0 > sLevelGap ) sLevelGap = 0;
    if( eCon_MaxGapCount <= sLevelGap ) sLevelGap = eCon_LastIndex;
	int iHP = pMob[a_iTarget].MOB.nHP;
	int iRemainingHP = 0;
    iRemainingHP = pMob[a_iTarget].OnTakeDamage( kDamage, m_iHandle, sLevelGap );
	kDamage.iSum = iHP - iRemainingHP;
    
    //UpdateEquipDur( kDamage.iSum, 1 ); // ���⸦ ������� ����, ...
    pMob[a_iTarget].UpdateEquipDur( kDamage.iSum );// ����� ����� �������� ���δ�.
    
	// taunt/detaunt effect�� ���⿡�� ó���ص� �ǳ� ���ɻ� �ϳ��� phase�� ����.

    return kDamage.iSum;
}


// combatphase : 8(4�� ���� ���ԵǾ� �־�� �Ѵ�.) or 256
// steal �迭
void CMob::CastInstant3( TNSKILL_DATA& a_kSkill, int a_iDamage ) // �߰������� �ߵ��ϴ� instant
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
// �ڱ� �ڽ��� ���� ������ �Ѵ�.
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
					//if( 0 > x ) x = 0 - x; // target�� ��ǥ�� ������ ��ǥ���� ũ��.
					//if( 0 > y ) y = 0 - y; // target�� ��ǥ�� ������ ��ǥ���� ũ��.
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
				nm.Effect = 11; // �̵� ����, // 0:�ɱ�  1:����  2:�ȱ�  3:�ٱ�  4:����  5:�ڷ���Ʈ,	6:�и���(knock-back), 7:�̲�������(�̵��ִϾ���)  8:����, 9:�λ�, 10:���� , 11:dash

				GridMulticast( m_iHandle, kDest.x, kDest.y, (MSG_STANDARD*)&nm );
				if( MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendOneMessage( (char*)&nm, sizeof(nm) );
				if( MAX_USER > a_iTarget ) pUser[a_iTarget].cSock.SendOneMessage( (char*)&nm, sizeof(nm) );
			}
			break;

		case eTNAfn_SummonTotem : 
			{// ���� ����
				// 1. �ֽ����̶�� Ÿ�ֽ��� �����ϹǷ� �����ϰ� �ൿ�� �Ұ��̴�.
				//	2. guild war�̶�� Ÿ guild�� �����ϸ� �ȴ�. �̰��� ��� ���հ��� ������ �Ѵٴ� ���̴�.
				// ���� zone�� vaild�ϴٸ� ����
				if( (eZoneType_God != g_iZoneType) && (eZoneType_Guild != g_iZoneType) )
				{
					SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictSummonItem] );
					return eTNRes_Failed;
				}

				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Totem, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 10 );
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
			{	// �йи��� ��ȯ
				if( MAX_USER < a_iTarget && MAX_MOB > a_iTarget )
				{// ���������� �˻��ϴ� routine
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
				if( eTNRes_Succeeded == iRes ) // ������ �� �ִ�.
				{
					if( 0 < m_irgSummoned[eTNCls2_Familiar] ) KillMobSummoned( eTNCls2_Familiar );//DeleteMob( m_irgSummoned[eTNCls2_Familiar], 1, 55 );
					int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Familiar, m_byClan, 0, TargetX, TargetY, a_iTarget, false, a_kSkill.krgEffect[i].iDuration, 0, 20 );
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
		case eTNAfn_SummonTracker : // ���Ͱ� PC���� ���̴� ��ȯ���� ��ȯ~
			{ // ��Ǫ�� �縣�� ��ȯ
				Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Tracker, m_byClan, 0, TargetX, TargetY, a_iTarget, false, a_kSkill.krgEffect[i].iDuration, 0, 30 );
			}
			break;
		} // end of switch
	} // end of for

	return eTNRes_Succeeded;
}

// combatphase : 256(4�� ���� ���ԵǾ� �־�� �Ѵ�.) 
void CMob::OnTakeInstant0( TNSKILL_DATA& a_kSkill, int a_iDamage, int a_iAttacker ) // �߰������� �ߵ��ϴ� instant
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
// target(corpse)���� �������� ȿ���� ����
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
				if (g_iZoneID == 11 ) break; //fors_debug ��һ�α�֤����ԭ�����������
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
// target(alive)���� �������� ȿ���� ����
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
		//case eTNAfn_TownPortal3: //	��� ����Ǫ��Ƽī
		//	{
		//		if( eWaitAct_None != m_kWaitAction.iAction ) continue;
		//		if( eTNVSAfn_HaveKalaCore & m_iAffections ) return eTNRes_Failed; // kala-core�� ������ ������, town portal�� �������� ���ϰ� �Ѵ�.
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
		case eTNAfn_ReflectDamage: //fors_debug �������ⷴ���˺������ĵط�
			{
/*		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ReflectDamage][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_ReflectDamage][a_eVarType].iPPlus += a_kEffect.iParam1; */
        //    m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
			}
			break;
		case eTNAfn_BreakMagicShield:
			{
				m_kMagicShield.set_Cur( 0 );
				if( eTNVSAfn_MagicShield & m_iAffections ) m_iAffections =  m_iAffections ^ eTNVSAfn_MagicShield;
			}
			break;
		case eTNAfn_EnhancedMagicShield :
			{
				int iHP = (a_kSkill.krgEffect[i].kFunc.iData * MOB.nTP)/10;
				m_kEnhancedMagicShield.Init( iHP, iHP );
			//	m_iAffections = m_iAffections | eTNVSAfn_EnhancedMagicShield;
				m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPlus = a_kSkill.krgEffect[i].iParam1;
				m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPPlus = a_kSkill.krgEffect[i].iParam2;
                m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
				/*
				if( eTNMob_PC == m_eMobType )
				{
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[OnTakeInstant2] 10. Effect(func:%d, param1:%d, param2:%d), tp:%d, hp:%d, ehnacedmagicshield:%d\r\n"
						, a_kSkill.krgEffect[i].kFunc.iData, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2
						, MOB.nTP, iHP, m_kEnhancedMagicShield.get_Cur()
						);
					WriteLog( chBuf, m_szLogFile );
				}
				*/
			}
			break;
		case eTNAfn_BreakEnhancedMagicShield:
			{
				m_kEnhancedMagicShield.set_Cur( 0 );
				if( eTNVSAfn_EnhancedMagicShield & m_iAffections ) m_iAffections =  m_iAffections ^ eTNVSAfn_EnhancedMagicShield;
			}
			break;
		case eTNAfn_ManaShield :
			m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
			break;
		case eTNAfn_ProtectFromAttackOnlyOnce :
			m_iAffections = m_iAffections | ToAbv( a_kSkill.krgEffect[i].iID );
			break;
		case eTNAfn_TP2Zero :
			DecTP( MOB.nTP );
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
				if( 3 > iDist ) continue; // ���� ������ ��ġ�� PC���� pull���� �ʴ´�.
				int iRes = PickFreeMobGrid( m_iHandle, &x, &y );
				if( FALSE == iRes ) continue; // �� �ڸ��� ���ٸ� pull�� �������� ���Ѵ�.

				MSG_Action sm; GetAction( m_iHandle, x, y, &sm );
				sm.Effect = 6; // 6 is for the knock-back action.				
				GridMulticast( m_iHandle, x, y, (MSG_STANDARD*)&sm, 50 );	// ���� ��ǥ �̵����� ���ִ� ���̴�.
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
				//if( eKala_Brahma == MOB.snTribe || eKala_Vishnu == MOB.snTribe || eKala_Siva == MOB.snTribe ) continue; // hard-cording ���߿� ����.				
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
				GridMulticast( m_iHandle, NextX, NextY, (MSG_STANDARD*)&sm, 30 );	// ���� ��ǥ �̵����� ���ִ� ���̴�.
				if( MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.SendOneMessage( (char*)&sm, sizeof(sm) );
				//GridMulticast( NextX, NextY, (MSG_STANDARD*)&sm, -1, 30 ); // ���� ��ǥ �̵��� ���� �ʴ´�.
				m_uiActionLock = CurrentTime + 2000;
			}
			break;
		case eTNAfn_Teleport :
			{//fors_debug ��ֹ����
			int iInterval=0;
			int iInterval1=0;
			int iInterval2=0;

            iInterval = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiAttacked );
            iInterval1 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiActivate );
			iInterval2 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiMoved );
			if (( iInterval <= 3000 ) || ( iInterval2 <= 3000 )  || ( iInterval1 <= 3000 )) 
			{
					SendClientMessage(m_iHandle,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
					return eTNRes_Failed;
			}

			Teleport( m_iHandle, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2 );
			}
			break;
		case eTNAfn_Terror  :
			{// ���� ������ �ؼ�, ���� ���θ� �����ؾ� �Ѵ�.
				if( eTNMob_PC == m_eMobType ) break;

				if( 0 >= a_iSkillBookIndex || MAX_SKILL <= a_iSkillBookIndex ) continue;
				if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
				{
					int iLevelGap = MOB.byLevel - pMob[a_iCaster].MOB.byLevel;
					if( 0 < iLevelGap ) // ����ڰ� �� ���� �����̶��, ���� Ȯ���� ����߸���.
					{						
						int iRate = m_kTolerance.iTerror * iLevelGap;
						int iDice = rand() % 100;
						if( iDice < iRate ) break;
					}

					LetsFlee( a_iCaster ); // �������� ��ġ�� �ݴ�������� ������ ����.
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
		case eTNAfn_ResetQuest : // 31~35�� 2������ quest
			{
				time_t now; time(&now);
				if((now - m_dwQuestInitTime) < (3*24*3600)) return eTNRes_Failed;

				//MOB.byQuest[0] = 255; // �ʺ��� ����Ʈ�� �������� �ʴ´�.
				//MOB.byQuest[1] = 1;
				for( int q = 11; q < 31; ++q ) MOB.byQuest[q] = 0;
				for( int q = 36; q < 90; ++q ) MOB.byQuest[q] = 0; //fors_debug ��ֹף������0
				MOB.byQuest[11] = 1;
				m_dwQuestInitTime = now;

				char pch[128] = {0,};
				sprintf(pch, "rst Quest_instance - %s", MOB.szName);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				SendQuestHistory( m_iHandle );
			}
			break;
		case eTNAfn_UnPack :
			{ // func : ���� ����(ȭ���� ��� 250��)
			  // Param1 : Item ID
			  // Param2 : Ǯ���� ����
				int iEmptySlot = 0;
				int iInserted = 0;

				for( int iSlot = 0; iSlot < byMaxInven; ++iSlot )
				{
					if( 0 >= MOB.Inven[iSlot].snIndex ) ++iEmptySlot; // �󽽷��̴�.
				}

				if( iEmptySlot >= a_kSkill.krgEffect[i].iParam2 )
				{					
					short sItemIndex = (short)(a_kSkill.krgEffect[i].iParam1 - HT_PARAMTYPE_ITEM_START + 1 );

					for( int iSlot = 0; iSlot < byMaxInven; ++iSlot )
					{
						if( iInserted >= a_kSkill.krgEffect[i].iParam2 ) break;

						if( 0 >= MOB.Inven[iSlot].snIndex ) // �󽽷��̴�.
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
				{// �� ������ ���ڸ���.
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
						MOB.Equip[i].snDurability = sMaxDur;	//	�����ϰ�
						sm.byIndex=i; sm.byDummy = 0;			//	0:������������� ����, 1:���ǾƷ� ����
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
				if( (ServerIndex+1) == SERVER_K3DUNGEON )
				{	int nX = TargetX; int nY = TargetY;
					if( (nX>235 && nX<352 && nY>240 && nY<350) || 
						(nX>830 && nX<935 && nY>86 && nY<195) ||
						(nX>678 && nX<791 && nY>680 && nY<795) ) return eTNRes_Failed;
				}

				m_kWaitAction.iAction = eWaitAct_SummonParty;
				m_kWaitAction.uiWaitingTime = CurrentTime + eWaitTime_SummonParty;	

				int iLeader = Leader;
				if( 0 >= iLeader || MAX_USER <= iLeader ) iLeader = m_iHandle; // �ڽ��� �����̴�. 

				// ��Ƽ���� ��ȯ
				for( int d = 0; d < MAX_PARTY+1; ++d )
				{   
					int fol = 0;
					if(d==0) fol = iLeader;
					else fol = pMob[iLeader].m_irgParty[d-1];
					if( 0 > fol || MAX_USER <= fol ) continue;
					if( fol == m_iHandle ) continue;							//	��Ƽ��ȯ�ڴ� ������ �ʾƵ� �ȴ�.		 
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
					sprintf(sm.szMsg, "�����մϴ� ?�ܢ�!! %s���� COMRADE(�ĸ���) GeForce 6600 3.3ns �� ��÷�Ǿ����ϴ�.", MOB.szName);
					strncpy(sm.szName, "źƮ����", SZNAME_LENGTH);
					sm.byTrimuriti = MOB.byTrimuriti;

					if(!MSGServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
					{	Log("err brodcast MSG-SEND MESSAGE_EXTRA",pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
					}
				}
				if(byResult==2)						//	��ǰ���� 2~6����� ����
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
			{	pUser[m_iHandle].m_byItemStatus |= 0x01;			//	eTNAfn_FuncBeauty�� m_byItemStatus�� ������ 0st bit���
			}	break;
		case eTNAfn_TownPortal : // �̵��� Ǫ��Ƽī
			{	
				if( eWaitAct_None != m_kWaitAction.iAction ) continue;
			//	if (g_iZoneID == 10) return eTNRes_Failed;//fors_debug ����ֱ�ӽ���С�ɻ�
			int iInterval=0;
			int iInterval1=0;
			int iInterval2=0;

            iInterval = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiAttacked );
            iInterval1 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiActivate );
			iInterval2 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiMoved );
			if (( iInterval <= 3000 ) || ( iInterval2 <= 3000 )  || ( iInterval1 <= 3000 )) 
			{
					SendClientMessage(m_iHandle,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
					return eTNRes_Failed;
			}

				if( eTNVSAfn_HaveKalaCore & m_iAffections ) 
				{	char pch[256] = {0,};
					sprintf(pch, "Char:%s pustica is stopped by kala-core", MOB.szName);
					Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

					return eTNRes_Failed; // kala-core�� ������ ������, town portal�� �������� ���ϰ� �Ѵ�.
				}
				m_kWaitAction.iAction = eWaitAct_TownPortal;
				m_kWaitAction.uiWaitingTime = CurrentTime + a_kSkill.krgEffect[i].iDuration;
			}
			break;
		case eTNAfn_ChangeTrimuritiSiva:
			{	if(MOB.byLevel <= 29) break;			//	29�����ϴ� ���Ұ��ϴ�
				if((ServerIndex+1) != 1) break;			//	1�����ܿ��� ���Ұ��ϴ�
				if(MOB.nGuildID != 0) break;			//	������ ��� ���Ұ��ϴ�

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
		//case eTNAfn_TownPortal2 : // ���� Ǫ��Ƽī
		//	{	
		//		if( eWaitAct_None != m_kWaitAction.iAction ) continue;
		//		if( eTNVSAfn_HaveKalaCore & m_iAffections ) return eTNRes_Failed; // kala-core�� ������ ������, town portal�� �������� ���ϰ� �Ѵ�.
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
// target(alive)���� ���������� ȿ���� ��Ÿ���� �ð� ���Ӽ��� ������ ��쿡�� ȣ���� ���ش�.
// instant effect���� �ɷ��ش�.
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
		sprintf(chBuf, "  => [OnTakeAffections] Caster(%d, %s, Lvl:%d, HP:%d)�� ��ų(%d, Lvl:%d)�� ��(%d, %s, Lvl:%d, HP:%d)���� ����. LevelGap:%d \r\n", a_iCaster, pMob[a_iCaster].MOB.szName, pMob[a_iCaster].MOB.byLevel, pMob[a_iCaster].MOB.nHP, a_kSkill.sID, a_kSkill.byLevel, m_iHandle, MOB.szName, MOB.byLevel, MOB.nHP, a_iLevelGap );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_2ND_LOG__

	int iRes = eTNRes_Failed;
	for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
	{
		if( 0 == a_kSkill.krgEffect[i].iID ) continue;
		if( eTNSklD_Instant == a_kSkill.krgEffect[i].iDuration ) continue;

		//if( eVar_Skill == a_eVarType || eVar_Potion == a_eVarType ) // action, active skill�� ��츸, ...
		if( eVar_Skill == a_eVarType )
		{
			if( eTNSklD_Instant >= a_kSkill.krgEffect[i].iDuration ) continue; // ���� ��ų�� ���, permanent�ϰ� ���ӵǴ� ���� ����.
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
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
								iRate = m_kTolerance.iSleep * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}

							if( m_krgResistEffect[eRst_Sleep].Random() ) // ���׿� ������ ���
							{
								#ifdef __DEBUG_LOG__
								{
									char chBuf[512] = { 0,0,0, };
									sprintf(chBuf, "[%d��%d�� %d��%d��%d��] OnTakeAffections, eTNAfn_Sleep> Caster:%d, MyHandle:%d, SkillID:%d\r\n"
										, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
										, a_iCaster, m_iHandle, a_kSkill.sID
										);
									WriteLog( chBuf, m_szLogFile );
								}
								#endif

								break;
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
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
								iRate = m_kTolerance.iHold * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}						
							AddEffect( a_kSkill.krgEffect[i], a_iCaster, a_iPartyLeader );
							iRes = eTNRes_Succeeded;
						}
					}
					break;
				case eTNAfn_HoldNSlowMove :
					{
						if( pMob[a_iCaster].m_krgSkill[a_iSkillBookIndex].kDeck.Random() )
						{
							int iTolerance = g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[MOB.byLevel][eCon_RS] - g_krgConsider[eTNMob_PC][eTNMob_PC].irgVal[pMob[a_iCaster].MOB.byLevel][eCon_RS];
							if( 0 < iTolerance )
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
								iRate = m_kTolerance.iHold * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}

							if( m_krgResistEffect[eRst_HoldNSlow].Random() ) // ���׿� ������ ���
							{
								#ifdef __DEBUG_LOG__
								{
									char chBuf[512] = { 0,0,0, };
									sprintf(chBuf, "[%d��%d�� %d��%d��%d��] OnTakeAffections, eTNAfn_HoldNSlowMove> Caster:%d, MyHandle:%d, SkillID:%d\r\n"
										, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
										, a_iCaster, m_iHandle, a_kSkill.sID
										);
									WriteLog( chBuf, m_szLogFile );
								}
								#endif

								break;
							}

							TNEFFECT kHold, kSlowMove;
							kHold = a_kSkill.krgEffect[i];
							kHold.iID = eTNAfn_Hold;
							kHold.iDuration = 3000;

							AddEffect( kHold, a_iCaster, a_iPartyLeader );

							//Slower Move	0/1	n	�������� ����		0 : + 1: % +
							kSlowMove.iID = eTNAfn_MoveSpeedMinus;
							kSlowMove.kFunc.iData = 0; // ���밪 ����
							kSlowMove.iDuration = a_kSkill.krgEffect[i].iDuration;
							kSlowMove.iParam1 = a_kSkill.krgEffect[i].iParam2;
							AddEffect( kSlowMove, a_iCaster, a_iPartyLeader );
							
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
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
								iRate = m_kTolerance.iStun * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}

							if( m_krgResistEffect[eRst_Stun].Random() ) // ���׿� ������ ���
							{
								#ifdef __DEBUG_LOG__
								{
									char chBuf[512] = { 0,0,0, };
									sprintf(chBuf, "[%d��%d�� %d��%d��%d��] OnTakeAffections, eTNAfn_Stun> Caster:%d, MyHandle:%d, SkillID:%d\r\n"
										, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
										, a_iCaster, m_iHandle, a_kSkill.sID
										);
									WriteLog( chBuf, m_szLogFile );
								}
								#endif

								break;
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
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
								iRate = m_kTolerance.iBlind * iTolerance;
								int iDice = rand() % 1000;
								if( iDice < iRate ) break;
							}

							if( m_krgResistEffect[eRst_Blind].Random() ) // ���׿� ������ ���
							{
								#ifdef __DEBUG_LOG__
								{
									char chBuf[512] = { 0,0,0, };
									sprintf(chBuf, "[%d��%d�� %d��%d��%d��] OnTakeAffections, eTNAfn_Stun> Caster:%d, MyHandle:%d, SkillID:%d\r\n"
										, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
										, a_iCaster, m_iHandle, a_kSkill.sID
										);
									WriteLog( chBuf, m_szLogFile );
								}
								#endif

								break;
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
							{ // ����ڰ� �� ���� ������ ���, ���� Ȯ���� ����߸���.
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
						//SetBattle( m_iHandle, a_iCaster ); // damage�� ����, ������ �ϵ��� �Ѵ�.
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
					sprintf(chBuf, "[%d��%d�� %d��%d��%d��] OnTakeAffections> Caster:%d, MyHandle:%d, EffectID:%d, EffectDur:%d, Param1:%d, Param2:%d \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, a_iCaster, m_iHandle, a_kSkill.krgEffect[i].iID, a_kSkill.krgEffect[i].iDuration, a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2 );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Assert] );
				}
				#endif
				RemoveEffect( a_kSkill.krgEffect[i].iID );
			}
		}
		else AffectEffect( a_kSkill.krgEffect[i], eVar_PassiveSkill, a_eAdd, a_iCaster, a_iPartyLeader, a_iLevelGap ); // passive skill �� ��츸, ...
	} // end of for

	return iRes;
}

//---------------------------------------------------------------------------------------------------------------------------------
// ���� �ð��� ������ effect ����
// ���� �ð��� ������ effect�� ��쿡��  a_eBuff�� true �̴�.
//---------------------------------------------------------------------------------------------------------------------------------
void CMob::AffectEffect( TNEFFECT a_kEffect, int a_eVarType, int a_eAdd, int a_iCaster, int a_iPartyLeader, int a_iLevelGap )
{	
	if( 0 > a_eVarType || eVar_PassiveSkill < a_eVarType ) return;	
	if( eVar_Equipment == a_eVarType )
		if( eTNSklD_Unlimited != a_kEffect.iDuration ) return; // equipment�� ��쿡�� duration���� -1(unlimited)�� effect���� �����Ѵ�.

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		char chBuf[256] = { 0,0,0, };
		sprintf(chBuf, "\t\t[AffectEffect] %d(0:�߰�,1:����)> ID: %d, Func: %d, Dur: %d, Param1: %d, Param2: %d, Effect����:%d(0:���,1:����,2:�нú�), LevelGap:%d, LevelGap��������Param1:%d \r\n"
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
			//if( eAfn_Remove == a_eAdd )
			//{
			//	TNEFFECT kEffect;
			//	kEffect.iID = eTNAfn_MoveSpeedPlus;
			//	kEffect.kFunc.iData = 0;
			//	kEffect.iDuration = 20000;
			//	kEffect.iParam1 = 3;
			//	AddEffect( kEffect, m_iHandle, m_iHandle );
			//}

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
	case eTNAfn_MoveSpeedPlus : // �̼� ����

		if( 0 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPlus += a_kEffect.iParam1;
		else if( 1 == a_kEffect.kFunc.iData ) m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;

		//m_krgVariation[eTNVar_MoveSpeed][a_eVarType].iPPlus += a_kEffect.iParam1;
		if( eVar_Skill == a_eVarType ) UpdateSpeed();
		break;
	case eTNAfn_MoveSpeedMinus :
	case eTNAfn_MoveSpeedMinus2 :
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
	case eTNAfn_BreakLinkOfSpirit:
		{
			m_iLinker = 0;
			m_krgVariation[eTNVar_SpiritLink][a_eVarType].iPlus = 0;
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
	case eTNAfn_ResistStun:
		{
			m_krgVariation[eTNVar_ResistStun][a_eVarType].iPlus += a_kEffect.iParam1;
			UpdateResistEffects( eRst_Stun );
		}
		break;
	case eTNAfn_ResistBlind:
		{
			m_krgVariation[eTNVar_ResistBlind][a_eVarType].iPlus += a_kEffect.iParam1;
			UpdateResistEffects( eRst_Blind );
		}
		break;
	case eTNAfn_ResistSleep:
		{
			m_krgVariation[eTNVar_ResistSleep][a_eVarType].iPlus += a_kEffect.iParam1;
			UpdateResistEffects( eRst_Sleep );
		}
		break;
	case eTNAfn_ResistHoldNSlow:
		{
			m_krgVariation[eTNVar_ResistHoldNSlow][a_eVarType].iPlus += a_kEffect.iParam1;
			UpdateResistEffects( eRst_HoldNSlow );
		}
		break;
		
	case eTNAfn_Immunity :
		{// �ϳ��� effect �� ���� immunity ����, �ϳ��� effect�� ���ؼ� immunity�� �ɱ� ����. ������ �ټ��� �ϱ⿡�� ������ ����
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
		{ // �ټ��� ���� immunity�� �ѹ��� �ɶ�, ����ϸ� ����.
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
/*
//eTNAfn_ACPlus	
	
                m_krgVariation[eTNVar_AC][eVar_Skill].iPPlus += 30;
		UpdateDefense();
		
//eTNAfn_AttackRatePlus		
                 m_krgVariation[eTNVar_AttackRate][eVar_Skill].iPPlus += 30;
		 UpdateCF();
		
//eTNAfn_DodgeRatePlus
                m_krgVariation[eTNVar_DodgeRate][eVar_Skill].iPPlus += 30;
	        UpdateCF();		
		
//eTNAfn_AllDamagePlus

				m_krgVariation[eTNVar_MinDamage][eVar_Skill].iPPlus += 30;
				m_krgVariation[eTNVar_MaxDamage][eVar_Skill].iPPlus += 30;
				m_krgVariation[eTNVar_FireDamage][eVar_Skill].iPPlus += 30;
				m_krgVariation[eTNVar_ColdDamage][eVar_Skill].iPPlus += 30;
				m_krgVariation[eTNVar_LightningDamage][eVar_Skill].iPPlus += 30;
				m_krgVariation[eTNVar_PoisonDamage][eVar_Skill].iPPlus += 30;
		                UpdateDamage(); */
			if( eAfn_Remove == a_eAdd )
			{
				pMob[m_iHandle].Init( m_iHandle );
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
			//if( eTNInAfn_EnhanceHardnessOfArmor & m_iInnerAffections ) m_iInnerAffections =  m_iInnerAffections ^ eTNInAfn_EnhanceHardnessOfArmor;
			m_krgVariation[eTNVar_EnhanceHardnessOfArmor][a_eVarType].iPlus = eConst_EnhanceHardnessOfArmorBase;
		}
		else
		{
			//m_iInnerAffections = m_iInnerAffections | eTNInAfn_EnhanceHardnessOfArmor;
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

					// client�� skill�� ���� ����(level ����)�� ��������� �Ѵ�. �޽����� ���� ���Ǹ� ����� �Ѵ�.
					MSG_SKILL_UP_EFFECT kMsg;
					kMsg.wType = SKILL_UP_EFFECT;
					kMsg.wPDULength = sizeof(MSG_SKILL_UP_EFFECT) - sizeof(HEADER);
					kMsg.snID = m_krgSkill[i].sID;
					kMsg.byLevel = pSkillData[iSkillIndex].byLevel;
					kMsg.byLevelPlus = (byte)m_krgSkill[i].byLevelPlus;

					pUser[m_iHandle].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_SKILL_UP_EFFECT) );

					// ���� m_krgSkill[i].iIndex�� levelPlus �� ���̾� �Ѵ�. �׸��� skillData�� ���� index�̴�. skill�� ����ϱ� ���� plus �����ش�.

					break;
				}
			}
		}
		break;
	}
}


// ���� damage�� ���´�.
void CMob::AbsorbDamageWithMagicShield( int& a_iDamage )
{
	if( !(eTNVSAfn_MagicShield & m_iAffections) ) return;// �Ķ�ī ��ų�� �ɷ��� ����, ...
	if( 0 >= a_iDamage ) return;
	if( 0 >= m_kMagicShield.get_Cur() ) return;

	int iDamageTobeDealt = Percent( a_iDamage, 70 );
	int iDamageRemained = a_iDamage - iDamageTobeDealt;

	if( m_kMagicShield.get_Cur() < iDamageTobeDealt )
	{
		iDamageRemained += (iDamageTobeDealt - m_kMagicShield.get_Cur());
		m_kMagicShield.set_Cur( 0 );

		m_iAffections =  m_iAffections ^ eTNVSAfn_MagicShield;

		#ifdef __TN_3RD_LOG__
		if( eTNMob_PC == m_eMobType )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[Shield] Mob(%d)�� magic shield�� %d damage�� �޾� �������ϴ�. m_iAffections:%d \r\n",m_iHandle, a_iDamage, m_iAffections );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_3RD_LOG__
	}
	else
	{
		m_kMagicShield.Dec( iDamageTobeDealt );
		#ifdef __TN_3RD_LOG__
		if( eTNMob_PC == m_eMobType )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[Shield] Mob(%d)�� magic shield�� %d damage�� �޾Ƴ½��ϴ�. ���� HP�� %d�Դϴ�.\r\n", m_iHandle, a_iDamage, m_kMagicShield.get_Cur() );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_3RD_LOG__
	}

	a_iDamage = iDamageRemained;
}


void CMob::AbsorbDamageWithEnhancedMagicShield( int& a_iDamage, int a_iType )
{
	if( !(eTNVSAfn_EnhancedMagicShield & m_iAffections) ) return;
	if( 0 >= a_iDamage ) return;
	if( 0 >= m_kEnhancedMagicShield.get_Cur() ) return;

	int iPercent = m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPlus;
	if( eConst_Elemental == a_iType ) iPercent = m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPPlus;

	int iDamageTobeDealt = Percent( a_iDamage, iPercent );
	int iDamageRemained = a_iDamage - iDamageTobeDealt;


	/*
	if( eTNMob_PC == m_eMobType )
	{
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[AbsorbDamageWithEnhancedMagicShield] 0. Param(damage:%d, type:%d), magicshield'HP:%d, percent:%d(%d,%d), damagetobedealt:%d, damageRemained:%d"
			, a_iDamage, a_iType, m_kEnhancedMagicShield.get_Cur()
			, iPercent, m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPlus, m_krgVariation[eTNVar_EnhancedMagicShield][eVar_Skill].iPPlus
			, iDamageTobeDealt, iDamageRemained
			);
		WriteLog( chBuf, m_szLogFile );
	}
	*/

	if( m_kEnhancedMagicShield.get_Cur() < iDamageTobeDealt )
	{
		iDamageRemained += (iDamageTobeDealt - m_kEnhancedMagicShield.get_Cur());
		m_kEnhancedMagicShield.set_Cur( 0 );

		m_iAffections =  m_iAffections ^ eTNVSAfn_EnhancedMagicShield;

		#ifdef __TN_3RD_LOG__
		if( eTNMob_PC == m_eMobType )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[AbsorbDamageWithEnhancedMagicShield] 10. Mob(%d)�� enhanced magic shield�� %d damage�� �޾� �������ϴ�. m_iAffections:%d, type:%d \r\n",m_iHandle, iDamageTobeDealt, m_iAffections, a_iType );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_3RD_LOG__
	}
	else
	{
		m_kEnhancedMagicShield.Dec( iDamageTobeDealt );
		#ifdef __TN_3RD_LOG__
		if( eTNMob_PC == m_eMobType )
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[AbsorbDamageWithEnhancedMagicShield] 20. Mob(%d)�� enhanced magic shield�� %d damage�� �޾Ƴ½��ϴ�. ���� HP�� %d�Դϴ�. type:%d \r\n", m_iHandle, iDamageTobeDealt, m_kMagicShield.get_Cur(), a_iType );
			WriteLog( chBuf, m_szLogFile );
		}
		#endif //__TN_3RD_LOG__
	}

	a_iDamage = iDamageRemained;
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
		nHP += (m_krgVariation[eTNVar_HealPlus][eVar_Equipment].iPlus + m_krgVariation[eTNVar_HealPlus][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_HealPlus][eVar_Skill].iPlus );

		IncHP( nHP );

		// party���鿡�� HP ���¸� ǥ��
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
			// party���� ������ ���� UpdateStatus �޽��� ����
		}
	}
}


void CMob::OnRecoverTP( int a_iTP, int a_iFunc, unsigned int a_hHealer )
{ 
	if( eTNInAfn_CantRecoverTP & m_iInnerAffections ) return;

	int iTP = a_iTP;
	if( 1 == a_iFunc ) iTP = a_iTP * ( 1 + pMob[a_hHealer].m_kChakra.sMind / 50 );

	iTP += (m_krgVariation[eTNVar_RecoverTPPlus][eVar_Equipment].iPlus + m_krgVariation[eTNVar_RecoverTPPlus][eVar_PassiveSkill].iPlus + m_krgVariation[eTNVar_RecoverTPPlus][eVar_Skill].iPlus);

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
		sprintf( szGeneral, "[BroadcastCastSkill] Res:%d> Attacker(Handle:%d, HP:%d, Aff:%u), skillID:%d, uiNow:%u \r\n"
			, a_pMsg->snRes
			, a_pMsg->snCasterKeyID, pMob[a_pMsg->snCasterKeyID].MOB.nHP, (int)pMob[a_pMsg->snCasterKeyID].m_iAffections
			, a_pMsg->snSkillID
			, CurrentTime
			 );
		int iPrintCount = 1;
		if( 1 < a_iTargetCount ) iPrintCount = TN_MAX_TARGET_COUNT;
		for( int i = 0; i < iPrintCount; ++i )
		{
			sprintf( szTarget, "\t- Target%d(Res:%d, H:%d, HP:%d, DMG:%d, Aff:%u)\r\n", i, a_pMsg->krgTarget[i].byRes, a_pMsg->krgTarget[i].snKeyID, a_pMsg->krgTarget[i].iHP, a_pMsg->krgTarget[i].iDamage, (int)a_pMsg->krgTarget[i].iAffection );
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
//fors_debug ����״̬��飬������ʱ��ȥ��
	if( m_kLastTime.uiAffectionChecked > a_uiNow ) return; // 0.5�� �̳����� �ٽ� �˻����� �ʴ´�.

	#ifdef __TN_4TH_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );

		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[CheckEffects] %d��%d��%d��(%u), mob(%d, %s)'s Affections: %u \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, CurrentTime, m_iHandle, MOB.szName, m_iAffections );
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
			sprintf(chBuf, "\t Affection ID: %d, Expire: %u, Now: %u, m_iAffections: %u \r\n", m_krgAffection[i].kEffect.iID, m_krgAffection[i].uiExpireTime, CurrentTime, m_iAffections );
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
	if( (eTNAfn_MaxHPPMinus==a_kEffect.iID) && (eTNImm_MaxHPDown & m_iImmunity) ) return;	
	if( (eTNImm_Heal==a_kEffect.iID) && (eTNImm_Heal & m_iImmunity) ) return;
	if( (eTNAfn_Weakness==a_kEffect.iID) && (eTNImm_Weaken & m_iImmunity) ) return;
	if( (eTNAfn_PreventRegenHP==a_kEffect.iID) && (eTNImm_PreventRegenHP & m_iImmunity) ) return;
	if( (eTNAfn_PreventRegenTP==a_kEffect.iID) && (eTNImm_PreventRegenTP & m_iImmunity) ) return;
	if( (eTNAfn_AttackSpeedMinus==a_kEffect.iID) && (eTNImm_AttackSpeedMinus & m_iImmunity) ) return;
	if( (eTNAfn_MoveSpeedMinus==a_kEffect.iID) && (eTNImm_MoveSpeedMinus & m_iImmunity) ) return;
	if( (eTNAfn_Invisible==a_kEffect.iID) && (eTNVSAfn_HaveKalaCore & m_iAffections) ) return; // kala-core�� ���� ���¿�����, ������ �� �� ����.
	if( (eTNAfn_MoveSpeedPlus==a_kEffect.iID) && (eTNVSAfn_Invisible & m_iAffections) ) return; // invisible���¿����� �̼� ������ �ȵȴ�.
//	if( (eTNAfn_ProtectAll==a_kEffect.iID) && (eTNVSAfn_Invisible & m_iAffections) ) return;
	//if( (eTNAfn_Invisible==a_kEffect.iID) && (eTNVSAfn_MoveSpeedPlus & m_iAffections) ) RemoveEffect( eTNAfn_MoveSpeedPlus );// �̼� �������¿��� invisible�� �ɸ�, �̼��� Ǯ����.
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
//	- 0�� �����ϸ�, ������ effect�� affection���� ����϶�� sub-sequential�� �۾��� ���ݵȴ�. �̰��� ��������, 1�� �����ϸ� �ȴ�.
int CMob::UpdateAffection( TNEFFECT& a_kEffect, int a_iAffIndex, int a_iPartyLeader )
{
	if( eTNSklD_Instant == a_kEffect.iDuration ) return 1;

	if( (m_krgAffection[a_iAffIndex].kEffect.kFunc.iData == a_kEffect.kFunc.iData) && (m_krgAffection[a_iAffIndex].kEffect.iParam1 == a_kEffect.iParam1) && (m_krgAffection[a_iAffIndex].kEffect.iParam2 == a_kEffect.iParam2) )
	{	// ������ �Ȱ��� ��ų�̶��, ...(���ӽð��� �����Ѵ�.)
		unsigned int uiExpireTime = CurrentTime + a_kEffect.iDuration;
		if( m_krgAffection[a_iAffIndex].uiExpireTime < uiExpireTime )
		{
			m_krgAffection[a_iAffIndex].uiExpireTime = uiExpireTime; //	���ο� ��ų�� ������ Ÿ���� �����ų�� �ִٸ� �����Ѵ�.
			m_krgAffection[a_iAffIndex].uiStartTime = CurrentTime;
			m_krgAffection[a_iAffIndex].iPartyLeader = a_iPartyLeader;
		}
		//int nCurrent	= m_krgAffection[a_iAffIndex].uiExpireTime;
		//int nNew		= CurrentTime + a_kEffect.iDuration;
		//if(nNew>=nCurrent) 
		//{	
		//	m_krgAffection[a_iAffIndex].uiExpireTime = nNew;		//	���ο� ��ų�� ������ Ÿ���� �����ų�� �ִٸ� �����Ѵ�.
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
// Visual Affection���� ��ϵǴ� effect���� �����Ѵ�.
//-----------------------------------------------------
void CMob::TurnOffAffection( int a_eID )
{	
	__int64 iAff = ToAbv( a_eID );
	if( !(iAff & m_iAffections) ) return;
if (eTNAfn_BlessOfGod == a_eID) 
{
pMob[m_iHandle].Init(m_iHandle);
pMob[m_iHandle].BroadcastUpdateStatusMsg();
pMob[m_iHandle].NotifyUpdateUIMsg();
}
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
		sprintf(chBuf, "\t*[RemoveEffect] Aff:%d, %d��%d��%d��(%d), ������Aff:%u, �����Aff:%u\r\n"
			, a_eAffID, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, CurrentTime, m_iAffections, m_iAffections ^ iAff );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	if( 0 == m_iAffTop ) return;
	int iAffIndex = get_Affection( a_eAffID );
	if( 0 >= iAffIndex || eConst_MaxAffectionCount < iAffIndex ) return; // ��ϵǾ� ���� �ʴٸ�, ...

	AffectEffect( m_krgAffection[iAffIndex].kEffect, eVar_Skill, eAfn_Remove, 0, 0, 0 ); // �����Ѵ�.

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
	if( eTNSklD_Instant >= a_kEffect.iDuration ) return eTNRes_Failed; // instant�� passive effect���� ������� �ʿ䰡 ����.
	
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
	//if ( m_krgAffection[iAffIndex].kEffect.iID == eTNAfn_MoveSpeedPlus )
	  // if (pMob[m_iHandle].MOB.byLevel == 140 ) 
        //  m_krgAffection[iAffIndex].kEffect.iID = 9999;
	m_iAffections = m_iAffections | ToAbv( m_krgAffection[iAffIndex].kEffect.iID );
	m_iInnerAffections = m_iInnerAffections | ToAbv2( m_krgAffection[iAffIndex].kEffect.iID );

	#ifdef __TN_3RD_LOG__
	if( eTNMob_PC == m_eMobType )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "\t[RegisterAffection] �ð�%d��%d��%d��> AffID:%d, Dur(%d ~ %d)variation:%d, Dur:%d, PartyLeader:%d \r\n"
			, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_krgAffection[iAffIndex].kEffect.iID, m_krgAffection[iAffIndex].uiStartTime, m_krgAffection[iAffIndex].uiExpireTime
			, m_krgAffection[iAffIndex].kEffect.iParam1, m_krgAffection[iAffIndex].kEffect.iDuration, m_krgAffection[iAffIndex].iPartyLeader );
		WriteLog( chBuf, m_szLogFile );
	}
	#endif //__TN_3RD_LOG__

	return eTNRes_Succeeded;
}


// affection���� �ִ� �ð� ���� ȿ�� ó��
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

			// party���鿡�� HP ���¸� ǥ��
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
				// party���� ������ ���� UpdateStatus �޽��� ����
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
				sprintf(chBuf, "[����(����) ����]%d��%d��%d��, ���ӵȽð�:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPierce[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
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
				sprintf(chBuf, "[���� ����]%d��%d��%d��, ���ӵȽð�:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPhy[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
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
				sprintf(chBuf, "[����(����) ����]%d��%d��%d��, ���ӵȽð�:%d, sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  kDamage.irgPierce[0] );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__
			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
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
				sprintf(chBuf, "[ȭ�� ����]%d��%d��%d��, ���ӽð�:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__

			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 4);
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
				sprintf(chBuf, "[�ñ� ����]%d��%d��%d��, ���ӽð�:%d, Raw sDamage:%d\r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 5);
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
				sprintf(chBuf, "[���� ����]%d��%d��%d��, ���ӽð�:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 6);
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
				sprintf(chBuf, "[�� ����]%d��%d��%d��, ���ӽð�:%d, Raw sDamage:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, iTerm,  sDamage );
				WriteLog( chBuf, m_szLogFile );
			}
			#endif //__TN_2ND_LOG__


			OnTakeDamage( kDamage, m_krgAffection[a_iAffIndex].iPartyLeader,eCon_MaxGap,888 );
			if( IsDead() ) OnKilled( m_krgAffection[a_iAffIndex].iPartyLeader, 7);
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
			sprintf(chBuf, "[get_Affection]%d��%d��%d��, �ִ� ���� ����> m_iLastAff:%d \r\n", g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, m_iLastAff );
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
		case eTNAfn_EnhancedMagicShield : return eTNVSAfn_EnhancedMagicShield;
		case eTNAfn_ProtectFromAttackOnlyOnce : return 	eTNVSAfn_ProtectFromAttackOnlyOnce;
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
		case eTNAfn_MoveSpeedPlus : 
			{
		//	 if (pMob[m_iHandle].MOB.byLevel == 140) 
		//	 {
			//	if (g_iZoneID == 1 || g_iZoneID == 10) //fors_debug ����ʲô���ĵط�
					return eTNVSAfn_MoveSpeedPlus;//eTNVSAfn_MoveSpeed140R;
				//else
				//	return eTNVSAfn_MoveSpeed140B;
		//	 }
		//	 else 
			}
		case     9999 :     	return eTNVSAfn_ProtectAll;
		case eTNAfn_MoveSpeedMinus : return eTNVSAfn_MoveSpeedMinus;
		case eTNAfn_MoveSpeedMinus2 : return eTNVSAfn_MoveSpeedMinus2;
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
		case eTNAfn_CantRecoverTP: return eTNInAfn_CantRecoverTP;
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
		sprintf(chBuf, "[CastOnly] Mob(%d,%u)�� ��ų(%d) cast \r\n", a_kSkill.sID );
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

                // ��ȯ�� ��

                //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
                int iSummonCount = a_kSkill.krgEffect[i].iParam2; // ��ȯ�Ǵ� ��
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
							sprintf(chBuf, "[CastOnly] Summon ���� > ���̻� monster handle�� ���� ���� ����. \r\n" );
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
					{// random�ϰ� �� ������ �¾��.
						iIndex = rand() % 8;
						x = krgPos[iIndex].x + rand() % iSize;
						y = krgPos[iIndex].y + rand() % iSize;
					}

					int iMob = Summon( a_kSkill.krgEffect[i].iParam1, a_kSkill.krgEffect[i].iParam2, a_kSkill.krgEffect[i].iDuration
						, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic, m_byClan, 0, x, y, CurrentTarget, false, 0, 0, 40 );

					if( 0 == iMob ) ++iSummonCount;
					if( 30 <= iSummonCount ) break;
                }                			    
			}
			break;

		case eTNAfn_SummonInteractor :
			{
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopFallDown, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic
					, a_kSkill.krgEffect[i].iParam2, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 50 );
			}
			break;
		case eTNAfn_SummonInteractor2 :
			{
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopRaise, a_kSkill.krgEffect[i].kFunc.iData, eTNCls2_Basic
					, a_kSkill.krgEffect[i].iParam2, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 51 );
			}
			break;

		case eTNAfn_SummonRetainer :
			{	// �йи��� ��ȯ					
				if( 0 < m_irgSummoned[eTNCls2_Retainer] ) KillMobSummoned( eTNCls2_Retainer );//DeleteMob( m_irgSummoned[eTNCls2_Retainer], 1, 0, eTNPrdt_RemoveNormal, 60 );
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Retainer, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 60 );
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
			{// �Ϲ��������� ����ȴ�.
				if( eZoneType_Normal != g_iZoneType ) return;

				int iMonsterID = a_kSkill.krgEffect[i].iParam1;
				// eTNCls_Summoned�� ��쿡 ��� case�� ��ġ���� Ȯ���ؾ� �Ѵ�.
				if( 0 < m_irgSummoned[eTNCls2_Mine] ) DeleteMob( m_irgSummoned[eTNCls2_Mine], 1, 0, eTNPrdt_RemoveNormal, 70 );
				int iMob = Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Mine, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 70 );
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
			{// �ֽ��� �������� �����Ѵ�.
				if( eZoneType_God != g_iZoneType ) return;

				if( 0 < m_irgSummoned[eTNCls2_Mine] ) DeleteMob( m_irgSummoned[eTNCls2_Mine], 1, 0, eTNPrdt_RemoveNormal, 80 );
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Mine, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 80 );
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
				// random�ϰ� monster ID�� ����ȴ�. �׷� ��� ����Ǿ�� �ϴ°�?



				if( 0 < m_irgSummoned[eTNCls2_Pet] ) DeleteMob( m_irgSummoned[eTNCls2_Pet], 1, 0, eTNPrdt_RemoveNormal, 70 );
				int iMob = Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Pet, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 90 );
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
				int iMob = Summon( a_kSkill.krgEffect[i].iParam1, 1, eTNPrdt_PopNormal, eTNCls_Summoned, eTNCls2_Pet, m_byClan, 0, TargetX, TargetY, 0, false, a_kSkill.krgEffect[i].iDuration, 0, 100 );
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
				//assert( !"Illusion skill�� �����ؾ� �Ѵ�." );
			}
			break;
		} // end of switch
	} // end of for
}


// 2, 56 ,JapanEventBGM.mp3

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
		if( m_bMoveZone ) return;			//	Ÿ������ �̵��ؾ� �� �ɸ��Ͱ� ��Ȱ����.
	}

	if( NULL == a_pMsg ) return;
	if( eTNClan_GM == m_byClan ) return;
	if( ITEM_PLACE_INVEN != a_pMsg->byPlace ) return;
	if( 0 > a_pMsg->byIndex || MAX_INVEN <= a_pMsg->byIndex ) return;
	if( 0 >= MOB.Inven[a_pMsg->byIndex].snIndex ) return;
	if( 0 >= MOB.Inven[a_pMsg->byIndex].byCount ) return;
	if( 0 >= m_iHandle || MAX_USER <= m_iHandle ) return;

	BYTE byMax = 0; int nItemIndex = MOB.Inven[a_pMsg->byIndex].snIndex+HT_PARAMTYPE_ITEM_START-1;
//	TNITEM_DATA kItem = pItemData[MOB.Inven[a_pMsg->byIndex].snIndex];
	TNITEM_DATA kItem = pItemData[MOB.Inven[a_pMsg->byIndex].snIndex];
	if(kItem.krgEffect[0].iID==eTNAfn_TownPortal) 
	{

			int iInterval=0;
			int iInterval1=0;
			int iInterval2=0;

            iInterval = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiAttacked );
            iInterval1 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiActivate );
			iInterval2 = (int)(CurrentTime -  pMob[m_iHandle].m_kLastTime.uiMoved );
			if (( iInterval <= 3000 ) || ( iInterval2 <= 3000 )  || ( iInterval1 <= 3000 )) 
			{
					SendClientMessage(m_iHandle,g_pMessageStringTable[_ServerReboot_Cant_Connect] );
					return;
			}
	//  if (g_iZoneID == 10) return; //fors_debug �������С�ɻ�
	   if(!IsUsablePustica(kItem.krgEffect[0].iParam1, kItem.krgEffect[0].iParam2, a_pMsg->snWarpID)) 
		{
			NotifyUpdateStatusMsg();
			pUser[m_iHandle].cSock.SendMessage();
			return;
		}
	}
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
		if(MOB.byQuest[51]!=0 && MOB.byQuest[51]!=1) return;	//	����Ʈ�ʱ�ȭ������1�� k3�ó����� ����Ʈ�� �����̵� �����̸� ����Ҽ�����.
	}

	if( (eItem_Resurrect80 == nItemIndex) || (eItem_Resurrect100 == nItemIndex) || (7078 == nItemIndex) )
	{ // duel field������ ��Ȱ�ֹ���(80%, 100%)�� ����� �� ����.
		if( 0 >= TargetY || MAX_GRIDY <= TargetY ) return;
		if( 0 >= TargetX || MAX_GRIDX <= TargetX ) return;
		if (g_iZoneID == 10 || g_iZoneID == 16) return;
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

	//-------------------------------------------------------------------------------------
	// �Ʒ��� ��� ������ ���� Ư���� ��츦 ó���ϱ� ���� �ϵ� �ڵ� --;
	//-------------------------------------------------------------------------------------
	bool bWriteLog = false;
	bool bIsMonsterScroll = false;
	if( eItem_MonsterScroll == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID 
		|| eItem_MonsterScroll2 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		|| eItem_MonsterScroll3 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		|| eItem_MonsterScroll4 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		|| eItem_MonsterScroll5 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
		) // ������� ������
	{		
		if( eZone_Pamir != g_iZoneID ) //�Ĺ̸� ������ �ƴ϶��, ����� �� ���ٰ� client�� �޽����� �������ش�.
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
		) // Į���� ������ ��ȯ ������
	{		
		if( eZone_Pamir != g_iZoneID ) //�Ĺ̸� ������ �ƴ϶��, ����� �� ���ٰ� client�� �޽����� �������ش�.
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


	if( (6731 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID)	) 
	{		
		if( eZone_Katacomb != g_iZoneID ) //�ϵμ��� ������ �ƴ϶��, ����� �� ���ٰ� client�� �޽����� �������ش�.
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
		sprintf(chBuf, "[UseItem] %d��%d�� %d��%d��%d�� > Item ID:%d who:%d,%s\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID
			, m_iHandle, MOB.szName );
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
	}


/*
	if( (6729 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID) 
		) 
	{		
		if( eZone_Castle != g_iZoneID ) //����� ������ �ƴ϶��, ����� �� ���ٰ� client�� �޽����� �������ش�.
		{
			SendClientMessage( m_iHandle, g_pMessageStringTable[_RestrictToUseaItemAt17] );
			return;
		}
	}
*/

	if( pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].kCost.sItemID )
	{
		if( kItem.krgEffect[0].iID==eTNAfn_TownPortal && eTNVSAfn_HaveKalaCore & m_iAffections ) return; // kala-core�� ������ ������, town portal�� �������� ���ϰ� �Ѵ�.
		if( kItem.krgEffect[0].iID==eTNAfn_TownPortal2 && eTNVSAfn_HaveKalaCore & m_iAffections ) return; // kala-core�� ������ ������, town portal�� �������� ���ϰ� �Ѵ�.

		//int iCoolDownSlot = 0;
		int iCoolDownSlot = pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sItemType;

		//--------------------------------------------------------------------
		// Ư�� affection�� �ɷ� ������, Ư�� ������ group ����� ���´�.
		//--------------------------------------------------------------------
		if( eTNInAfn_CantRecoverTP & m_iInnerAffections )
		{
			if( (2 == iCoolDownSlot) || ( 56 == iCoolDownSlot ) )
			{
				SendClientMessage( m_iHandle, g_pMessageStringTable[_CantRecoverTP] );
				return;
			}
		}

		if( eTNVSAfn_Invulnerable & m_iAffections )
		{
			if( 10 == iCoolDownSlot ) // Ǫ��Ƽī �迭
			{
				SendClientMessage( m_iHandle, g_pMessageStringTable[_CantUseAnyPustica] );
				return;
			}
		}

		if( 0 < pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].iAttackSpeed ) // cool-down �ð��� �ִ� item
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

		//if(snDay>0)		//	�Ⱓ�� ������
		//{	int nIndex = nItemIndex - HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START;
		//	if(nIndex>0 || nIndex<MAX_TIMEITEM)
		//	{
		//		time_t now; time(&now);
		//		if(now>pUser[m_iHandle].m_time[nIndex])
		//		{	pUser[m_iHandle].m_time[nIndex] = now+snDay*24*3600;			//	���Ⱓ�� ����� �������� �������� �������� ���ڸ� �߰��Ѵ�
		//		}	else
		//		{	pUser[m_iHandle].m_time[nIndex] += snDay*24*3600;				//	���Ⱓ�� ������� ���� �����۱��Ž� ���⳯�ڿ� �߰��Ѵ�.
		//		}
		//	} 
		//}

		if(!bRet)	//	ID�� �߸��� �Ⱓ�� �������̰ų� �Ķ���������� ���� ���
		{
			SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
			return;	
		}
	
		m_snResurrect = a_pMsg->snWarpID;			//	��Ȱ�� ��� ��Ȱ��ġ����(�����ۺ�Ȱ�� ��ġ��������)
		if( eTNCPhase_OnTakeInstant1 & kItem.sCombatPhase ) OnTakeInstant1( m_iHandle, kItem ); // ��ü����
		if( eTNCPhase_OnTakeInstant2 & kItem.sCombatPhase ) iUseResult = OnTakeInstant2( m_iHandle, kItem, 0 ); // ���������� �ۿ��� �͵�
		if( eTNCPhase_OnChargInstance & kItem.sCombatPhase ) OnChargInstance(kItem);
		if( eTNCPhase_OnAffect & kItem.sCombatPhase ) OnTakeAffections( kItem, 0, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
		if( eTNCPhase_StartAction & kItem.sCombatPhase ) iUseResult = StartAction( m_iHandle, kItem, 0 );
		if( eTNCPhase_CastOnly & kItem.sCombatPhase ) CastOnly( kItem );
		m_snResurrect = RESURRECT_TYPE_PRESENT;		//	��Ȱ�� ��� ��Ȱ��ġ����(������ �̿ܿ��� ����ġ��Ȱ)
		
		
		if( bIsMonsterScroll ) // ������� ������(���� �ֹ���)�� ���
		{
			/*
			// deck���� monster card ������ ������.
			int iMonsterIndex = g_kMonsterScroll.Random();
			if( 0 > iMonsterIndex || eMon_CountOfMonsterToBeSummon <= iMonsterIndex )
			{
				// ���� �α׸� �����.
				iMonsterIndex = 0;
			}
			int iMonsterID = g_irgMonsterToBeSummon[iMonsterIndex];
			*/
			int iMonsterID = 0;
			if( eItem_MonsterScroll == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[0].DrawMonsterCard();
			else if( eItem_MonsterScroll2 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[1].DrawMonsterCard();
			else if( eItem_MonsterScroll3 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[2].DrawMonsterCard();
			else if( eItem_MonsterScroll4 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[3].DrawMonsterCard(); // 6774 �������4 , 6775 �������5
			else if( eItem_MonsterScroll5 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID ) iMonsterID = g_krgMagicLamp[4].DrawMonsterCard(); // added by spencer, 4th september 2006

			int iMonsterHandle = pMob[m_iHandle].Summon( iMonsterID, 1, eTNPrdt_PopNormal, eTNCls_Warrior, eTNCls2_Basic, eTNClan_Neutral, 0, TargetX, TargetY, 0, false, 0, 0, 101 );
			if( MAX_USER > iMonsterHandle || MAX_MOB <= iMonsterHandle )
			{ // ���� ��ȯ�� ���и� �� ���̴�. item�� ������� ���� ������ �����Ѵ�.
				iUseResult = eTNRes_Failed;
				return;
			}
			else
			{
				pMob[iMonsterHandle].m_iDebugFlag = 1;
			}
		}
		

		if( eTNRes_Succeeded == iUseResult )
		{// ���������� item�� ��� => cooldown�� ����, ������ 1�� ���δ�.
			m_sLastItemUsed = MOB.Inven[a_pMsg->byIndex].snIndex ;
			m_byLastItemUsedCount = MOB.Inven[a_pMsg->byIndex].byCount;
			m_byLastItemUsedLoc = a_pMsg->byIndex;

			m_uirgInstantCoolDownTime[iCoolDownSlot] = CurrentTime + pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].iAttackSpeed;
			--MOB.Inven[a_pMsg->byIndex].byCount;
			if( bWriteLog ) WriteLog( " successed!", g_szrgLogFileName[eLogFileName_ItemThatSummonMonster] );
		}
        if( (6706 == pItemData[MOB.Inven[a_pMsg->byIndex].snIndex].sID)	) //fors_debug red_name ʹ����Ʒ
		{
			MOB.snKarma=0;
        //    BroadcastUpdateStatusMsg();
      //      NotifyUpdateStatusMsg();
		}


		if( (1 == iCoolDownSlot) || (2 == iCoolDownSlot) || (20 == iCoolDownSlot) ) // HP/TP potion�� ���
		{	// party���鿡�� HP ���¸� ǥ��
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
				// party���� ������ ���� UpdateStatus �޽��� ����
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
		char strItem[128] = {0,};	// ������ ��� �α�...
		if (BASE_CheckItemLog(&a_pMsg->kItem))
		{	BASE_GetItemCode(&a_pMsg->kItem,strItem);
			sprintf(temp,"use %s",strItem);
			Log(temp,pUser[m_iHandle].AccountName,pUser[m_iHandle].IP);
		}
	}
}


void CMob::CancelToUseItem()
{
	if( 0 > m_byLastItemUsedLoc || MAX_INVEN <= m_byLastItemUsedLoc ) return;

	if( m_sLastItemUsed == MOB.Inven[m_byLastItemUsedLoc].snIndex )
	{
		MOB.Inven[m_byLastItemUsedLoc].byCount = m_byLastItemUsedCount;
	}
}


int CMob::Regen( double a_dPercent, byte byType)	//	type 0 : regen,   type 1 : resurrect
{
	if( IsAlive() ) return eTNRes_Failed;
	if( MAX_USER <= m_iHandle ) return eTNRes_Failed; // npc(or monster)�� ���� skip
	if( eTNMob_PC != m_eMobType ) return eTNRes_Failed;
	if(100 < a_dPercent ) a_dPercent = 0;//return eTNRes_Failed;
	if( 0 > a_dPercent  ) a_dPercent = 0;

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
		else if(MOB.bySaveZone!=(ServerIndex+1))  // ���������� ���Ǿ� �ִµ�, �� ��ġ�� �ٸ� zone�̴�.
		{
			int nSave=MOB.bySaveZone;
			if(MOB.byLevel<TRIMURITY_LEVEL_LOW && (nSave==SERVER_KRUMA_LOW || nSave==SERVER_KRUMA_HIGH || nSave==SERVER_CHATURANGKA))
			{	if(ServerIndex+1 == 1)
				{	m_snResurrect = RESURRECT_TYPE_TOWN;
					Resurrect(a_dPercent, 50);
				}	else
				{	MOB.bySaveZone=0; sm.byZone = 1;
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return eTNRes_Succeeded;

					int iDecPrana = m_iPranaDec;
					double dPrana = a_dPercent / 100;
					AcquirePrana( (int)(iDecPrana * dPrana) );

					m_kWaitAction.iAction = eWaitAct_ZonePortal;
					m_bMoveZone = true;

					pUser[m_iHandle].m_byCloseType = eCloseRegen;
					pUser[m_iHandle].m_byCloseAndGoZone = 1;
					pUser[m_iHandle].m_snGoX = -1;
					pUser[m_iHandle].m_snGoY = -1;
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
						
					sm.byZone = nSave; 
					pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); 

					int iDecPrana = m_iPranaDec;
					double dPrana = a_dPercent / 100;
					AcquirePrana( (int)(iDecPrana * dPrana) );
					MOB.nHP = Percent( m_iMaxHP, 50 );
					MOB.nTP = Percent( m_iMaxTP, 50 );

					m_kWaitAction.iAction = eWaitAct_ZonePortal;
					m_bMoveZone = true;

					pUser[m_iHandle].m_byCloseType = eCloseRegen;
					pUser[m_iHandle].m_byCloseAndGoZone = nSave;
					pUser[m_iHandle].m_snGoX = MOB.snZ=MOB.snSaveX;
					pUser[m_iHandle].m_snGoY = MOB.snZ=MOB.snSaveZ;

					return eTNRes_Succeeded;
				}
			}
		}
		else
		{	if(MOB.byLevel<TRIMURITY_LEVEL_LOW && (MOB.bySaveZone==SERVER_KRUMA_LOW || MOB.bySaveZone==SERVER_KRUMA_HIGH || MOB.bySaveZone==SERVER_CHATURANGKA))
			{
				MOB.bySaveZone=0; sm.byZone = 1;
				pUser[m_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(sm)); return eTNRes_Succeeded;

				int iDecPrana = m_iPranaDec;
				double dPrana = a_dPercent / 100;
				AcquirePrana( (int)(iDecPrana * dPrana) );

				m_kWaitAction.iAction = eWaitAct_ZonePortal;
				m_bMoveZone = true;

				pUser[m_iHandle].m_byCloseType = eCloseRegen;
				pUser[m_iHandle].m_byCloseAndGoZone = 1;
				pUser[m_iHandle].m_snGoX = -1;
				pUser[m_iHandle].m_snGoY = -1;
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
		Resurrect(0, 20, ePortal_CastleW);	//	���� ���������� ��Ȱ�Լ��̹Ƿ� ��Ż�� ������ ���� �վ�� �Ѵ�.
	}
	else if(byType==REGEN_TYPE_CASTLE2)
	{
		m_snResurrect = RESURRECT_TYPE_PORTAL;
		Resurrect(0, 20, ePortal_CastleN);	//	���� ���������� ��Ȱ�Լ��̹Ƿ� ��Ż�� ������ ���� �վ�� �Ѵ�.
	}
	else
	{
		m_snResurrect = RESURRECT_TYPE_PRESENT;
		Resurrect(a_dPercent, 20);
	}

	return eTNRes_Succeeded;
}

//	���� �������� ��Ȱ�� �����ϴ� �Լ��̴�.
void CMob::Resurrect( double a_dPercent, int nRecoverry, int iPortal)
{
	if(a_dPercent<0) a_dPercent = 0;
	if(a_dPercent>100) a_dPercent = 100;
	if(nRecoverry<0) nRecoverry = 0;
	if(nRecoverry>100) nRecoverry = 100;

	S_SCP_RESP_INIT_REGEN_CHAR sm;
	sm.wType = SCP_RESP_INIT_REGEN_CHAR;
	sm.byZone = ServerIndex+1;

	//	������ �Ķ���� ������ �Ѵ�.
	int iDecPrana = m_iPranaDec;
	int nX = 0; int nZ = 0; int tx=0; int ty=0;

	MOB.nHP = Percent( m_iMaxHP, nRecoverry );
	MOB.nTP = Percent( m_iMaxTP, nRecoverry );

	Init( m_iHandle );

	MOB.byZone = ServerIndex+1;				//	����� savezone���� �� ������ ������ ������ �ٲ��ش�.
	if ((sm.byZone == 11) || (MOB.byZone == 11)) { sm.byZone=1; MOB.byZone=1;} //fors_debug check relive 11
   // if ((sm.byZone == 10) || (MOB.byZone == 10)) { sm.byZone=1; MOB.byZone=1;}
   // if ((sm.byZone == 16) || (MOB.byZone == 16)) { sm.byZone=1; MOB.byZone=1;}
	//pUser[m_iHandle].LastAction	= m->dwClientTick;
	Direction	= 0;
	State		= 1;


	if(m_snResurrect==RESURRECT_TYPE_SAVE)
	{
		nX = MOB.snSaveX; nZ = MOB.snSaveZ;
	}
	else if(m_snResurrect==RESURRECT_TYPE_PRESENT)
	{
//fors_debug ��ǿ����ԭ���ж�
	if (g_iZoneID == 10)
	{  
		 short snnx =0; short snny=0;
		if(MOB.byTrimuriti == eTNClan_Vishnu)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1254, &snnx, &snny )) return;	
		if(MOB.byTrimuriti == eTNClan_Brahma)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1255, &snnx, &snny )) return;	
		if(MOB.byTrimuriti == eTNClan_Siva)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1256, &snnx, &snny )) return;	
          nX = snnx ;  nZ = snny;

	}
	else if (g_iZoneID == 16 )  //����Ҫ������ԭ�ظ��� fors_debug
	{
		nX = 268 ;
		nZ = 732 ;
	}
	else
	{

		nX = TargetX; nZ = TargetY;
	}
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
		if(!bRet || (dwServerID-40000)!=(ServerIndex+1))	//	��Ż������ �߸��Ǿ��ų� ������ ���̾ƴ� ��Ż�� ��� ���������� ��Ȱ��Ų��.
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
    //fors_debug re_live here ���񸴻�������
	short snx =0; short sny=0;
	if (g_iZoneID == 10)
	{  
		if(MOB.byTrimuriti == eTNClan_Vishnu)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1254, &snx, &sny )) return;	
		if(MOB.byTrimuriti == eTNClan_Brahma)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1255, &snx, &sny )) return;	
		if(MOB.byTrimuriti == eTNClan_Siva)
	     if(!g_ParamMgr.HT_bGetNPCPosition( 1256, &snx, &sny )) return;	
         tx = snx; ty = sny;

	}
	else if (g_iZoneID == 16 )  //����Ҫ������ԭ�ظ��� fors_debug
	{
		tx = 268 ;
		ty = 732 ;
	}
	else
	{
	PickFreeMobGrid( m_iHandle, &nX, &nZ );
	tx = nX; ty = nZ;
	}

	//	REGEN PACKET ������ ä���.
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

		//	���� �̵��� �����ɸ����� �˸���, ���� ������ �����´�.
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

	m_iPranaDec = 0;

	// �� ������ ������ mob�鿡�� �����Ѵ�.
	S_SCP_INIT_OTHER_MOB sOther;
	GetCreateMob(m_iHandle,&sOther); 
	GridMulticast(tx,ty,(MSG_STANDARD*)&sOther,m_iHandle,100);
	// ���� ������ �����´�.
	SendGridMob(m_iHandle);
	pUser[m_iHandle].cSock.SendMessage();

	//	��Ƽ������ hpȸ���� �˸���
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
				short snx =0; short sny=0;
				if(m_snMovePortal == ePortal_Gen)
				{
                   if (g_iZoneID == 10)
				   { if(MOB.byTrimuriti == eTNClan_Vishnu)
				       if(!g_ParamMgr.HT_bGetNPCPosition( 1254, &snx, &sny )) break;
                     if(MOB.byTrimuriti == eTNClan_Brahma)
				       if(!g_ParamMgr.HT_bGetNPCPosition( 1255, &snx, &sny )) break;
                     if(MOB.byTrimuriti == eTNClan_Siva)
				       if(!g_ParamMgr.HT_bGetNPCPosition( 1256, &snx, &sny )) break;
				   }
					GetTrimurityArea(m_iHandle, x, y);
				//fors_debug Ϊ����С�ɶ�����
				//	int tret = PickFreeMobGrid(m_iHandle,&x,&y);
				//	if	(tret==FALSE) break;

					if(m_iHandle>0 && m_iHandle<MAX_USER) 
					{
					
					if (g_iZoneID == 10)
					  { pUser[m_iHandle].nPreX = snx; pUser[m_iHandle].nPreY = sny;}
					else
					  { pUser[m_iHandle].nPreX = x; pUser[m_iHandle].nPreY = y;}
					}

					MSG_Action sm;
					if (g_iZoneID == 10)
                    GetAction(m_iHandle,snx,sny,&sm);
					else
					GetAction(m_iHandle,x,y,&sm);
					sm.Effect = 5;
					if( 0 < m_iHandle && MAX_USER > m_iHandle ) pUser[m_iHandle].cSock.AddMessage((char*)&sm,sizeof(sm));                           
					if (g_iZoneID == 10)
                    GridMulticast(m_iHandle,snx,sny,(MSG_STANDARD*)&sm,100,ACTION_WARP);
					else
					GridMulticast(m_iHandle,x,y,(MSG_STANDARD*)&sm,100,ACTION_WARP);

					char pch[256] = {0,};
					sprintf(pch, "Char:%s move to town completed by pustica %d x %d y %d snx %d sny", MOB.szName,x,y,snx,sny); //fors_debug use_small_fly
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

					short snX,snY=0; byte byZone=0;
					bool bRet = g_ParamMgr.HT_bGetNPCZone( m_snSaveNPC, &byZone );
					bRet &= g_ParamMgr.HT_bGetNPCPosition( m_snSaveNPC, &snX, &snY );
					if(!bRet) break;	//	�˼� ���� npc���� �̵�
					pUser[m_iHandle].m_byCloseType = eClosePustica;
					pUser[m_iHandle].m_byCloseAndGoZone = byZone;
					pUser[m_iHandle].m_snGoX = (short)snX;
					pUser[m_iHandle].m_snGoY = (short)snY;
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
						if(snChakra>355 || iSkillPointUsed>63) return;	//	��ũ������ 355���� ũ�ų� ��ų����Ʈ�� 63���� Ŭ�ÿ��� ����ũ�縶������ ���ԺҰ���û(2005.11.25)
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
					{	pUser[m_iHandle].m_byCloseType = eClosePustica;
						pUser[m_iHandle].m_byCloseAndGoZone = byMoveZone;
						short snX=GetRandom(snStartX, snEndX); short snZ=GetRandom(snStartZ, snEndZ);
						pUser[m_iHandle].m_snGoX = snX;
						pUser[m_iHandle].m_snGoY = snZ;
						sprintf(pch, "Char:%s move to portal:%d completed by pustica", MOB.szName, m_snMovePortal);
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

				if( 0 >= iLeader || MAX_USER <= iLeader ) iLeader = m_iHandle; // �ڽ��� �����̴�. ��Ƽ���鸸 ��ȯ�ϸ� �ȴ�.
				else // �ڽ��� ������ �ƴϴ�. ������ �ٸ� ��Ƽ������ ��ȯ�ؾ� �Ѵ�.
				{
					if( !pMob[iLeader].IsDead() && !(eTNVSAfn_HaveKalaCore & pMob[iLeader].m_iAffections) )
					{
                        Teleport( iLeader, TargetX, TargetY );

						sprintf(pch, "dbg Char:%s recalled by summon_party item to posx:%d posy:%d", pMob[iLeader].MOB.szName, TargetX, TargetY);
						Log(pch, pUser[iLeader].AccountName, pUser[iLeader].IP);
					}
				}

				// ��Ƽ���� ��ȯ
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

//fors_debug cast_skill֮ǰ����useskilll
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
	kMsg.bySkillLevel = 1; // monster ��ų���� ��� 1 level�̴�.

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
					//if( 0  == irgTarget[i] ) continue;  //fors_debug �ͻ���Ҫ�ͷ����һ����Ŀ������
         /* 		char pch[128] = {0,};
				sprintf(pch, "server target:%d ", irgTarget[i]);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				sprintf(pch, "client target:%d ", kMsg.krgTarget[iTargetCount].snKeyID);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
*/
					kMsg.krgTarget[iTargetCount].snKeyID = (short)irgTarget[i];
					++iTargetCount;					
				}
			}
			if( 3 < m_iAttackCount ) Think( eTNAI_Attack, CurrentTarget );
		}
		else if( eTNSklA_Unit < iAOE )
		{ // ���� ��ų�� ���, target�� ���� ��� ������ �ʿ��ϴ�.
			if( eTNAT_EnemyFarFirst == iAllowedTargets ) SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget, 1 );
			else SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget, 0 );

			for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
			{
				//if( 0  == irgTarget[i] ) break;  //fors_debug �ͻ���Ҫ�ͷ����һ����Ŀ������
          	/*	char pch[128] = {0,};
				sprintf(pch, "server target:%d ", irgTarget[i]);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				sprintf(pch, "client target:%d ", kMsg.krgTarget[iTargetCount].snKeyID);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
*/
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
		{// ���� ���� �ִ� target�� friend�ΰ��� �˻��Ѵ�.
			int* pAllowedTarget = NULL;
			if( eZoneType_God == g_iZoneType ) pAllowedTarget = (int*)&(g_irgFriendTableRvR[m_byClan]);
			else if( eZoneType_Guild == g_iZoneType ) pAllowedTarget = (int*)&(g_irgFriendTableStrH[m_byClan]);
			else pAllowedTarget = (int*)&g_irgFriendTable[m_byClan];

			if( NULL != pAllowedTarget )
			{
				if( pAllowedTarget[pMob[CurrentTarget].m_byClan] ) // true �̸� friend�� �ƴϴ�.
				{// �������� friend�� �� ���� ã�´�.
					iRange = 10;
					iMaxTargetCount = 1;
					SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget );
					kMsg.krgTarget[0].snKeyID = (short)irgTarget[0];
				}
				else // friend �̴�.
				{					
					kMsg.krgTarget[0].snKeyID = (short)CurrentTarget;
				}
				iTargetCount = 1;
			}
			else return; // null �� ��, ���� null�� �� ����.
		}
		else if( eTNSklA_Unit < iAOE )
		{ // ���� ��ų�� ���, target�� ���� ��� ������ �ʿ��ϴ�.
			SelectTarget( iRange, iAllowedTargets, iMaxTargetCount, irgTarget );
			for( int i = 0; i < TN_MAX_TARGET_COUNT; ++i )
			{
				//if( 0  == irgTarget[i] ) break;  //fors_debug �ͻ���Ҫ�ͷ����һ����Ŀ������
          		/*char pch[128] = {0,};
				sprintf(pch, "server target:%d ", irgTarget[i]);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);

				sprintf(pch, "client target:%d ", kMsg.krgTarget[iTargetCount].snKeyID);
				Log(pch, pUser[m_iHandle].AccountName, pUser[m_iHandle].IP);
*/

				kMsg.krgTarget[iTargetCount].snKeyID = (short)irgTarget[i];
				++iTargetCount;					
			}
			if( TN_MAX_TARGET_COUNT > iTargetCount )
			{// ��ų �����ϴ� ���� ����
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
			if  (fol<MAX_USER) continue; //  PC�̸� skip
			if  (pMob[fol].Mode==MOB_EMPTY||pMob[fol].MOB.nHP<=0) 
			{   if  (pMob[fol].Mode!=MOB_EMPTY) DeleteMob(fol,1, 0, eTNPrdt_RemoveNormal, 100);
				m_irgParty[d] = 0;
				continue; // ��Ƽ���� ����.
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
		{ // ���� ��ų�� ���, target�� ���� ��� ������ �ʿ��ϴ�.
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
		sprintf(chBuf, "\r\n[UseSkill] iRes:%d, SkillID %d, target��:%d > Target(%d,%d,%d,%d,%d ...), Aff%d, Imm:%d \r\n"
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
	if( MOB_PEACE != Mode ) // �������ε� ������ ������ �ð��� ���� �ư�, ��� ������ �޾� HP�� �پ��ٸ�, ... ��ġ���� ������ �� �ִ�.
	{
		if( CurrentTime > (m_kLastTime.uiAttacked + 20000) ) // �ֱ� 20�ʵ��� ������ ���ߴٸ�, 
			if( CurrentTime < (m_kLastTime.uiDamaged + 10000 ) ) // �ֱ� 10�ʵ��� ������ �޾Ҵٸ�, DOT�̶��?
			{
				m_iBlockedCell = eTNCell_SafetyZone | eTNCell_MonsterCantMoveInThisCell;

				{ // ���� �̷����� �ߴ����� ���� ������ �����. ���� ���� ��𿡼� �������� 
					//SYSTEMTIME st;
					//GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf(chBuf, "[CheckInvalidCombat(); %d��%d�� %d��%d��%d��] Monster> Hndl:%d, tribe:%d, Mode:%d, FSM:%d, HP:%d, Now:%u, Last Atk:%u, Dmg:%u \r\n"
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

int CMob::CheckItem( short a_sItemID, int a_iCount, int* a_irgSlot ) // inventory���� ã�ƺ���.
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
			if( eConst_CheckItemSlot <= iSlotIndex ) break;
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
//	- a_bCollided : �� �� �ڸ��� �����ؾ��ϴ� ���� ���� ����, true�̸� �� �� ��ġ�� ����ؾ� �Ѵ�.
int CMob::Summon( int a_iMonsterID, int a_iCount, int a_iPopType, int a_iClass1, int a_iClass2, int a_iClan, int a_iDirection, int x, int y, int a_iTarget, bool a_bCollided, int a_iLifeTime, int a_iOldHandle, int a_iCaller, int a_iRoute )
{
	if( (0 != a_iTarget) && (a_iTarget == m_iHandle) ) return 0;
	if( eTNCls2_Basic > a_iClass2 || eTNCls2_Mine < a_iClass2 ) a_iClass2 = eTNCls2_Basic;

	// ��ȯ�� ��
	int iMonsterDataIndex = a_iMonsterID - 2000; // the index of monster data
	int iIndex = 0;


	int iMob = a_iOldHandle;

	if( eZone_Chaturanka == g_iZoneID )
	{
		if( 2113 == a_iMonsterID ) iMob = 1000; // ��Ǫ�⺴
		else if( 2112 == a_iMonsterID ) iMob = 1001; // ��Ǫ
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
			sprintf(chBuf, "[CastOnly] Summon ���� > ���̻� monster handle�� ���� ���� ����. \r\n" );
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
		sprintf(chBuf, "[Summon(); %d��%d�� %d��%d��%d��] tribe:%d, handle:%d, caller:%d, GerateIndex:%d, HP:%d, class(%d,%d), Mode:%d, FSM:%d, Now:%u, Killed:%u, SummonMonster:%d \r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, MOB.snTribe, m_iHandle, a_iCaller, GenerateIndex, MOB.nHP, MOB.byClass1, MOB.byClass2
			, Mode, m_eFSM, CurrentTime, m_kLastTime.uiKilled, a_iMonsterID
			);
		WriteLog( chBuf, m_szLogFile );
	}	
	#endif

	pMob[iMob].MOB = pMonsterData[iMonsterDataIndex];
	pMob[iMob].MOB.nTP = iMonsterDataIndex;
	pMob[iMob].Init( iMob ); // �ʱ�ȭ

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
	{ // ��ȯ ��ġ�� ������ �Ǿ� ���� ���� ��쿡�� ��ȯ���� ��ġ�� ������� �Ѵ�.		
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
			{ // ��ȯ ��ġ�� ������ �Ǿ� ���� ���� ��쿡�� ��ȯ���� ��ġ�� ������� �Ѵ�.		
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


	if( 0 < pMobGrid[y][x] && MAX_MOB > pMobGrid[y][x] ) // �ٸ� mob�� ��ġ�ϰ� �ִ�.
	{		
		if( a_bCollided ) // dest �ڸ��� �˻��ϰ�, �ٸ� mob�� ������, ó��(����)�� �Ŀ�, �� �� ��ġ�� ��ġ�� ��Ų��.
		{
			int iOccupiedMob = pMobGrid[y][x];
			int iNewX, iNewY;
			iNewX = x; iNewY = y;
			int tret = PickFreeMobGrid( iMob, &iNewX, &iNewY );
			if( FALSE == tret )
			{ // user�̸� kick out �����ְ�, monster�̸� �ܼ��� ���δ�.
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user�̸�
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
			else // ������ ��ġ�� �ٲ۴�.
			{			
				if( 0 < iOccupiedMob && MAX_USER > iOccupiedMob ) // user�̸�
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
			if( FALSE == tret ) return 0; // summon�� fail���� ����� ���� ���� ���, ...
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

	pMob[iMob].MOB.byClass1 = (byte)a_iClass1; // ��ȯ�Ǵ� NPC�� ����
	pMob[iMob].MOB.byClass2 = (byte)a_iClass2; // ��ȯ�Ǵ� NPC�� �� ����            
	pMob[iMob].m_byClan = pMob[iMob].MOB.byTrimuriti = (byte)a_iClan; // ��ȯ�Ǵ� ���� NPC-Monster���̴�. ���� m_byClan�� MOB.byTrimuriti ���� �����ϴ�.
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
	{// ��ȯ���� Ȱ�� ������ ����Ѵ�.
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
		pMob[iMob].m_kLastTime.uiSelectTarget = pMob[iMob].m_uiLifeTime; // ��ȯ������ target�� ���Ƿ� �������� �ʴ´�.

		m_irgSummoned[a_iClass2] = iMob;
		pMob[iMob].Leader = m_iHandle;		
		pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_HaveMaster;

		strcmp( pMob[iMob].MOB.szName, MOB.szName );

		if( 0 >= pMob[iMob].MOB.byLevel || 100 < pMob[iMob].MOB.byLevel ) pMob[iMob].MOB.byLevel = MOB.byLevel;
		if( eTNCls2_Mine == a_iClass2 ) pMob[iMob].MOB.byLevel = 199;

		pMob[iMob].m_iButtonStatus = m_iButtonStatus;
	
		pMob[iMob].m_iBlockedCell = m_iBlockedCell; // ������ ������.

		if( eTNCls2_Retainer == a_iClass2 || eTNCls2_Pet == a_iClass2 ) pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_GetCommand;
		if( eTNCls2_Familiar == a_iClass2 || eTNCls2_Tracker == a_iClass2 ) pMob[iMob].m_iAIOption = pMob[iMob].m_iAIOption | eTNAIO_CombatOnly;
	}

	pMob[iMob].m_uiActionLock = CurrentTime + iSummonDelay;
	pMob[iMob].m_iDirection = a_iDirection;
	                    
	S_SCP_INIT_OTHER_MOB sm;
	GetCreateMob( iMob, &sm );
	sm.byPopType = a_iPopType; // ��ȯ�� ���� ���� ��ȣ
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

	// �޼տ� ��� �ִ� weapon�� ���� index �˻�
	if( MOB.nHP < kSkill.kCost.iHP ) return eTNRes_CostHP;
	if( MOB.nTP < kSkill.kCost.iTP ) return eTNRes_CostTP;
	if( 0 < kSkill.kCost.sItemID )
	{// �������� inventory���� ã�Ƽ� ������ ����� �Ѵ�.
		int irgSlot[eConst_CheckItemSlot] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };
		int iCount = 0;
		iCount = CheckItem( kSkill.kCost.sItemID, kSkill.kCost.byItemCount, irgSlot );
		if( iCount >= kSkill.kCost.byItemCount ) RemoveItem( kSkill.kCost.byItemCount, irgSlot );
		else return eTNRes_CostItem;
	}
	
	DecHP( kSkill.kCost.iHP );
	DecTP( kSkill.kCost.iTP );

	// party���鿡�� HP ���¸� ǥ��
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
		// party���� ������ ���� UpdateStatus �޽��� ����
	}

	TNDAMAGE kDamageSrc;
	if( eTNCPhase_DealDamage & kSkill.sCombatPhase )
	{		    
        CalDamage( kDamageSrc, kSkill, eHnd_Left );
        if( eTNCPhase_CastInstant1 & kSkill.sCombatPhase ) CastInstant1( kDamageSrc, kSkill );
	}

	if( 0 > sUnitID ) return eTNRes_InvalidTarget6; // Ÿ�� ID�� �߸��ƴ�.

	if( eTNAT_Enemy == kSkill.iAllowedTargets )
	{
		if( pMob[sUnitID].IsDead() )
		{
			a_pMsg->krgTarget[i].byRes = eCmbt_Dodge;
			a_pMsg->krgTarget[i].iDamage = 0;
			a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;//0�� ���̴�.
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

	// ���� ������ ���			
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
		if( 0 == i ) UpdateEquipDur( iDamage, 2 ); // ���� 1ȸ�� ������ 1�� ��������.

		if( eTNCPhase_CastInstant3 & kSkill.sCombatPhase ) CastInstant3( kSkill, pMob[sUnitID].m_iLastDamage );
		if( eTNCPhase_Taunt & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant0( kSkill, pMob[sUnitID].m_iLastDamage, m_iHandle );
	}			
	if( eTNCPhase_OnTakeInstant1 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant1( m_iHandle, kSkill ); // ��ü����
	if( eTNCPhase_OnTakeInstant2 & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeInstant2( m_iHandle, kSkill, iSkillBookIndex );
	if( eTNCPhase_OnAffect & kSkill.sCombatPhase ) pMob[sUnitID].OnTakeAffections( kSkill, iSkillBookIndex, m_iHandle, m_iHandle, eAfn_Add, eVar_Skill );
	
	a_pMsg->krgTarget[i].byRes = (byte)iRes;
    a_pMsg->krgTarget[i].iDamage = iDamage;
    a_pMsg->krgTarget[i].iHP = pMob[sUnitID].MOB.nHP;
    a_pMsg->krgTarget[i].iAffection = pMob[sUnitID].m_iAffections;	

	if( eCmbt_Normal == iRes || eCmbt_Critical == iRes ) // ������ ������ ����, ����ȴ�. 
	{ // ���Ⱑ ���� ������ �ƴ� ���� �ִ°�?
		TNDAMAGE kDamageReflected;
		int iReflectDamage = pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Equipment].iPPlus + pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Skill].iPPlus /*+ pMob[sUnitID].m_krgVariation[eTNVar_ReflectDamage][eVar_Potion].iPPlus*/;
		if( 0 > iReflectDamage ) iReflectDamage = 0;
		if( g_irgSetting[eCnst_ReflectMax] < iReflectDamage ) iReflectDamage = g_irgSetting[eCnst_ReflectMax];
		kDamageReflected.irgPierce[0] = Percent( a_pMsg->krgTarget[i].iDamage, iReflectDamage );

		if( 0 < kDamageReflected.irgPierce[0] ) OnTakeDamage( kDamageReflected, sUnitID );
		
/* 
		// party���鿡�� HP ���¸� ǥ��
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
			// party���� ������ ���� UpdateStatus �޽��� ����
		}		
*/
	}

	return eTNRes_Succeeded;
}

bool CMob::ExpandFunc(int nTimeIndex, short snDays)
{
	short snDay = snDays;
	struct tm when;
	//bool bRet = true; int nItemIndex = 0;
	//nItemIndex = HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START+nTimeIndex;
	//bRet &= g_ParamMgr.HT_bGetItemTimeLimit(nItemIndex, &snDay);
	//if(!bRet)	//	����������� ����ߴµ� ������ �߻�
	//{	char chBuf[256] = { 0,0,0, };
	//	sprintf(chBuf, "err Premium-Item used but parameter error occured:%s Item:%d", MOB.szName, nItemIndex);
	//	TimeWriteLog(chBuf, ".\\LOG\\[Log]Premium-Item.txt" );
	//	return false;
	//}

	if(pUser[m_iHandle].m_time[nTimeIndex] > 2141022783)	//	2037.11.5�ϱ��� �����Ǿ� ���� ���(2038���� �Ѿ�� �����߻��Ѵ�)
		return false;

	//__time64_t chtime = (__time64_t)pUser[m_iHandle].m_time[nTimeIndex];
	//when = *_localtime64(&chtime);
	//if((when.tm_year-100) >= 2037) return false;

	time_t now; time(&now);
	if(now>pUser[m_iHandle].m_time[nTimeIndex])
	{	pUser[m_iHandle].m_time[nTimeIndex] = now+snDay*24*3600;	//	���Ⱓ�� ����� �������� �������� �������� ���ڸ� �߰��Ѵ�
	}	else
	{	pUser[m_iHandle].m_time[nTimeIndex] += snDay*24*3600;		//	���Ⱓ�� ������� ���� �����۱��Ž� ���⳯�ڿ� �߰��Ѵ�.
	}

	char pch[512] = {0,};
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
	case ePortal_Gen:					//	�̵��� Ǫ��Ƽī
		m_snMovePortal = ePortal_Gen;
		break;
	case ePortal_Guild:					//	���Ǫ��Ƽī(�ֽ������� ���Ұ�)
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
			if(g_iCastleOwner!=MOB.nGuildID) return false;	//	������ ������尡 �ƴϸ� ���ȵ�
			if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW || ServerIndex+1==SERVER_CHATURANGKA) return false;	//	�ֽ������� ���Ұ�
			m_snMovePortal = ePortal_CastleIN;
		}	break;
	case ePortal_Ziva:					//	����Ǫ��Ƽī
		bRet = g_ParamMgr.HT_bGetNPCZone( snTarget2, &byZone );
		if((!bRet) || (byZone == 20)) //fors_debug move zone here
		{	
			SendClientMessage(m_iHandle, g_pMessageStringTable[_Invalid_Item_Data]);
			return false;
		}
		m_snMovePortal = ePortal_Ziva;
		m_snSaveNPC = snTarget2;
		break;
	case ePortal_SZiva:					//	�������Ǫ��Ƽī
		m_snMovePortal = snTarget2;
		break;
	case ePortal_NoLimit:
		if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW) return false;
		m_snMovePortal = snTarget2;
		break;
	case ePortal_Memorized:
		if(pUser[m_iHandle].m_byZone<1 || pUser[m_iHandle].m_byZone>MAX_SERVER) return false;
		m_snMovePortal = ePortal_Memorized;
		break;
	default:				//	��Ÿ ǪũƼī(�������� �����, �����) - ���������� �����ٸ� ������ type�� ������ ����üũ�ʿ��ϴ�
		if(ServerIndex+1==SERVER_KRUMA_HIGH || ServerIndex+1==SERVER_KRUMA_LOW) return false;
		m_snMovePortal = iTarget1;
		if(m_snMovePortal == 173 && MOB.byTrimuriti==2) m_snMovePortal = 175;
		if(m_snMovePortal == 173 && MOB.byTrimuriti==4) m_snMovePortal = 174;
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
		iDefGuildID = 0; //  monster�̶�� guild�� 0
				
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

	// party������ ������ �� ����.
	if( IsParty( iDefender ) ) return eTNRes_IsPartyMember;
	//if( Leader == iDefender ) return eTNRes_IsPartyMember;
	//if( pMob[iDefender].Leader == m_iHandle ) return eTNRes_IsPartyMember;
	//for( int i = 0; i < MAX_PARTY; ++i )
	//{
	//	if( iDefender == m_irgParty[i] ) return eTNRes_IsPartyMember; // ��Ƽ���̴�.
	//}


	// zone ������ ���� ���� ���ɼ� �Ǵ�
	int* pAllowedTarget = NULL;
	if( eZoneType_God == g_iZoneType )
	{
		pAllowedTarget = (int*)&(g_irgEnemyTableRvR[m_byClan]);
	}
	else if( eZoneType_Guild == g_iZoneType )
	{
		if( eTNMob_PC == pMob[iDefender].m_eMobType ) // �Ѵ� PC�̴�. ��� �񱳸� �ؾ� �Ѵ�.
		{
			if( MOB.nGuildID == iDefGuildID ) return eTNRes_IsSameGuildMember;

			// ���� ���
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
		int iNotChallengeMode = 1; // �� ���°� �Ϲ� ����, target�� ���� ����̸� ���� �ȴ�.
		int iFlag = pAllowedTarget[iDefClan]; // ���ΰ�? true�̸� ģ���̰� false�̸� ���̴�.
		if( eTNMob_PC == m_eMobType ) // caster(������)�� PC�̶��, ...
		{
			if( iDefender == pUser[m_iHandle].m_nChallenger )
			{
				iNotChallengeMode = 0; // ���� ���� �����̴�. �׷� ���̹Ƿ� ���ݰ���
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

	if( Leader == a_iTarget ) return true; // target�� ��Ƽ���̴�.
	if( pMob[a_iTarget].Leader == m_iHandle ) return true; // ���� ��Ƽ���̴�.

	int iLeader = Leader;
	if( 0 >= iLeader ) iLeader = m_iHandle; // ���� ��Ƽ���̴�.

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
	if( 0 >= iLeader ) iLeader = m_iHandle; // ���� ��Ƽ���̴�.

	int iCount = 1;
	for( int i = 0; i < MAX_PARTY; ++i )
	{
		int iPC = pMob[iLeader].m_irgParty[i];
		if( USER_PLAY == pUser[iPC].Mode ) ++iCount;
	}

	return iCount;
}

//------------------------------------------------------------------------------------------
// Robot ���� �Լ���
//------------------------------------------------------------------------------------------

int CMob::SelectSkill2() // robot�� ��ų�� �����Ѵ�.
{ // �� ������ �ϵ� �ڵ��Ѵ�.

	enum { eSkillList_Size = 5, };
	int irgSkillList[eSkillList_Size] = { 0,0,0, }; // m_krgSkill�� index ��ȣ

	if( 0 == MOB.byClass2 )// �泪��
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 25;
		irgSkillList[2] = 20;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 1 == MOB.byClass2 ) // ������
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 25;
		irgSkillList[2] = 20;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 2 == MOB.byClass2 ) // �ܰ˾Ƽ���
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 23;
		irgSkillList[2] = 6;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 3 == MOB.byClass2 ) // Ȱ �Ƽ���
	{
		irgSkillList[0] = 100;
		irgSkillList[1] = 100;
		irgSkillList[2] = 100;
		irgSkillList[3] = 100;
		irgSkillList[4] = 100;
	}
	else if( 4 == MOB.byClass2 ) // ���� ��ũ��
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

	iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data �迭���� index

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

	if( 0 == CurrentTarget ) return 0x0010;// ���̻� ������ ����� ������ Standingby ���� ü����.

	iDist = CalDistance( m_iHandle, CurrentTarget );

	if( iDist > m_kSight.sCombat ) return 0x0010; // �þ� �ٱ��� �ִ�. ���� ����

	int iSkillIndex = m_krgSkill[m_iSkillCharged].iIndex; // data �迭���� index
	int iRange = pSkillData[iSkillIndex].iRange;

	if( iRange >= iDist ) return 0x1000;   // ���� // ��Ÿ� �����̴�.
	else return 0x0001;   // �߰�
}


//@Param
//	- a_bCollided : �� �� �ڸ��� �����ؾ��ϴ� ���� ���� ����, true�̸� �� �� ��ġ�� ����ؾ� �Ѵ�.
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

	pMob[iMob].MOB = pMob[a_iPC].MOB; // ��� ���� �����Ѵ�.
	memcpy( pMob[iMob].ViewEquip, pMob[a_iPC].ViewEquip, sizeof(pMob[iMob].ViewEquip) );
	pMob[iMob].MOB.byFace = rand() % 8 + 1;
	pMob[iMob].MOB.byHead = rand() % 8 + 1;
	pMob[iMob].Init( iMob ); // �ʱ�ȭ

	short srgTribe[8] = { 1,2, 4,8, 16,32, 64,128, };
	int iTribeIndex = rand() % 8;
	//pMob[iMob].MOB.snTribe = srgTribe[iTribeIndex];
	sprintf( pMob[iMob].MOB.szName, "Tan%d", iMob );

	//m_iBlockedCell = 0;
	pMob[iMob].m_iBlockedCell = 0; // ��� �����ϰ� ����Ѵ�.

	if( 0 == x || 0 == y )
	{ // ��ȯ ��ġ�� ������ �Ǿ� ���� ���� ��쿡�� ��ȯ���� ��ġ�� ������� �Ѵ�.		
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
	sm.byPopType = eTNPrdt_PopNormal; // ��ȯ�� ���� ���� ��ȣ
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

void CMob::SetCharPositionFromZone()
{
	if( !m_bMoveZone || MOB.nHP<=0 )			//	���̵��� ��찡 �ƴϰų� ����ð� 
	{	MOB.byZone = ServerIndex+1;				//	������ ���� ��ġ�� ����Ѵ�	
		MOB.snX = TargetX; MOB.snZ = TargetY;
	}

	if(pUser[m_iHandle].m_byCloseType == 0)		//	���� �̵��ܿ� �̵��� �ʿ��� ��� �˻�
	{	switch(ServerIndex+1)
		{										//	��ũ������ 355���� ũ�ų� ��ų����Ʈ�� 63���� Ŭ�ÿ���
		case SERVER_KRUMA_LOW:					//	����ũ�縶������ ���ԺҰ� - ���ٶ����� �̵�(2005.11.25)
			{	short snChakra = MOB.sMuscle + MOB.sNerves + MOB.sHeart + MOB.sMind;
				short snSkill  = MOB.byLevel;
				if(eTNCls_2nd < MOB.byClass1) snSkill += (((snSkill-35)/10)*2);

				if(MOB.byLevel>=TRIMURITY_LEVEL_HIGH ) 
				{	MOB.byZone=1; MOB.snX=-1; MOB.snZ=-1;
					pUser[m_iHandle].m_byCloseType = eCloseSystem;
					pUser[m_iHandle].m_byCloseAndGoZone = 1;
					pUser[m_iHandle].m_snGoX = -1;
					pUser[m_iHandle].m_snGoY = -1;
					break;
				}
			}
		case SERVER_KRUMA_HIGH:
			{	if( MOB.byLevel<TRIMURITY_LEVEL_LOW ) 
				{	MOB.byZone=1; MOB.snX=-1; MOB.snZ=-1;
					pUser[m_iHandle].m_byCloseType = eCloseSystem;
					pUser[m_iHandle].m_byCloseAndGoZone = 1; 
					pUser[m_iHandle].m_snGoX = -1;
					pUser[m_iHandle].m_snGoY = -1;
				}
			}	break;
		case SERVER_STRONGHOLD:
			{	if( !m_bMoveZone )
				{
					//if( (50 < pMob[conn].TargetX) && (570 > pMob[conn].TargetX) && (448 < pMob[conn].TargetY) && (958 > pMob[conn].TargetY) );
					//else
					//{
					//	pMob[conn].MOB.byZone=eZone_Stronghold; pMob[conn].MOB.snX=0; pMob[conn].MOB.snZ=0;
					//}
					bool bRet=true;
					DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
					bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_Stronghold_Front, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );
					if(!bRet)
					{	MOB.byZone = SERVER_SHAMBALA; MOB.snX = -1; MOB.snZ = -1;
					}
					else
					{	MOB.byZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
						MOB.snX = GetRandom(snStartX, snEndX);
						MOB.snZ = GetRandom(snStartZ, snEndZ);
					}

					if((ServerIndex+1) != MOB.byZone)	
					{
						pUser[m_iHandle].m_byCloseType = eCloseSystem;
						pUser[m_iHandle].m_byCloseAndGoZone = MOB.byZone;
						pUser[m_iHandle].m_snGoX = MOB.snX;
						pUser[m_iHandle].m_snGoY = MOB.snZ;
					}
				}
			}	break;
		case SERVER_KALIA_LOW:		//	Į���ƴ���(��,��,��), ������������ ���� ����� 
		case SERVER_KALIA_MIDDLE:	//	������������ �¾���� �����Ѵ�.
		case SERVER_KALIA_HIGH:
		case SERVER_CHATURANGKA:
			{	if((ServerIndex+1) != MOB.bySaveZone)	
				{
					pUser[m_iHandle].m_byCloseType = eCloseSystem;
					pUser[m_iHandle].m_byCloseAndGoZone = MOB.bySaveZone;
					pUser[m_iHandle].m_snGoX = MOB.snSaveX;
					pUser[m_iHandle].m_snGoY = MOB.snSaveZ;
				}
			}	break;
		case SERVER_K3DUNGEON:
			{	if( !m_bMoveZone )
				{
					bool bRet=true;
					DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
					bRet &= g_ParamMgr.HT_bGetPortalInfo( ePortal_CastleW+1, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );
					if(!bRet)
					{	MOB.byZone = SERVER_KATANA3; MOB.snX = -1; MOB.snZ = -1;
					}
					else
					{	MOB.byZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
						MOB.snX = GetRandom(snStartX, snEndX);
						MOB.snZ = GetRandom(snStartZ, snEndZ);
					}

					if((ServerIndex+1) != MOB.byZone)	
					{
						pUser[m_iHandle].m_byCloseType = eCloseSystem;
						pUser[m_iHandle].m_byCloseAndGoZone = MOB.byZone;
						pUser[m_iHandle].m_snGoX = MOB.snX;
						pUser[m_iHandle].m_snGoY = MOB.snZ;
					}
				}
			}	break;
		case eZone_Katacomb:			//	�ϵμ����濡�� ��Ƽ� ������ ������������ ������.
			{	if( MOB.nHP>0 )
				{
					int nX = TargetX; int nY = TargetY;
					if( ((66 <= nX && 166 >= nX) && (76 <= nY && 168 >= nY ))
						|| ((168 <= nX && 202 >= nX) && (74 <= nY && 96 >= nY ))
						|| ((346 <= nX && 458 >= nX) && (188 <= nY && 278 >= nY ))

						|| ((856 <= nX && 954 >= nX) && (74 <= nY && 166 >= nY ))
						|| ((824 <= nX && 856 >= nX) && (74 <= nY && 96 >= nY ))
						|| ((564 <= nX && 682 >= nX) && (188 <= nY && 278 >= nY ))
						) GetTrimurityArea(m_iHandle, nX, nY);

					MOB.snX = nX; MOB.snZ = nY;
				}
			}	break;
		}
	}

	if(pUser[m_iHandle].m_byCloseType != 0)	
	{	MOB.byZone = pUser[m_iHandle].m_byCloseAndGoZone;
		MOB.snX = pUser[m_iHandle].m_snGoX;
		MOB.snZ = pUser[m_iHandle].m_snGoY;
	}
}
