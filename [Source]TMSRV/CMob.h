#ifndef _CMOB_
#define _CMOB_

#include "Basedef.h"
#include "CItem.h"
#include "TNPointBar.h"
#include "TNDebug.h"
#include "TNRate.h"
//#include "TNDeck.h"
#include "TNDeck100.h"
//#include "TNCombo.h"



#define MAX_ENEMY       8


#define MOB_EMPTY       0   // ����ִ�.
#define MOB_USERDOCK    1   // ����ڰ� ������� ���� �α������� ���� ����.
#define MOB_USER        2
//#define MOB_IDLE        3
#define MOB_PEACE  4
#define MOB_COMBAT      5
#define MOB_RETURN		6
#define MOB_FLEE		7
#define MOB_ROAM		8


// #define CONTROL_USER    0 - MAX_USER
#define CONTROL_STATIC  (MAX_USER)
#define CONTROL_WANDER  (MAX_USER+1)




class CMob
{
    public:
	
	CMob();
	~CMob();

	void         ProcessorSecTimer         (void);
	int          SetSegment                (void);                // 1:ShipMove   0:DeleteObject
	void         NotifyOppObjectSyncZone   (void);
	int          StandingByProcessor       (void);
	int          BattleProcessor           ( int a_iTic );            // ret=0 Nothing,  ret=0x01 Move, ret 0x02 Fire
	//void         AddEnemyList              (short TargetId);
	//void		 RemoveEnemyList		   (short TargetId);

	int          SelectTargetFromEnemyList (void);
	void         SetMovement               (float AngleToTarget);
	void         GetCurrentScore           (int idx); // Equip���� MAX������ �̸� ��� �� ���´�.
	void         GetNextPos                (int battle);
	void         GetTargetPos              (int tz);
	BOOL         CheckGetLevel             (void);
	void         GetTargetPosDistance      (int tz);
	void         GetRandomPos              (void);


	//-------------------------------------------------------
	//	added by �����(2003.11.22)
	//-------------------------------------------------------
private :
	void Init();

// Public Operations
public :

	int CheckMoveHack( int a_iMoveType,int conn );
	//int CheckMoveHack( int a_iDistance, int a_iSpeed, unsigned int a_uiTime );
	//void LogRewardItems();
	void Print( char* a_pTxt ) { WriteLog( a_pTxt, m_szLogFile ); }
	//void RefreshEnemyCount();
	void Init( int a_iHandle );

	void Think( int a_iState, int a_iTarget );
	void Speak( int a_iSpeechContentID, int a_iTarget, int a_iState );
	void CallOthers( int a_iActionID, int a_iTarget );
	//void CallHelp( int a_iMaxCount, int a_iTarget );
	void CallRetainer();
	void CallRobot();
	void OnFollow( int a_iMob );
	void React( int a_iActionID, int a_iTarget );	
	//static void Teleport( int a_iMob, int a_iX, int a_iY );
	static int FindPath( HS2D_COORD& a_kSrc, HS2D_COORD& a_kTar, HS2D_COORD& a_kDest, HS2D_COORD& a_kPrevPos, int a_iStepDistance, int a_iBlockCell );
	static int MoveAside( HS2D_COORD& a_kSrc, HS2D_COORD& a_kTar, HS2D_COORD& a_kDest, int a_iStepDistance, int a_iBlockCell );

	//void Speak( int a_iState, int a_iTarget );
	void DeliverComment( char* a_pComment );

	// state ����
	void AcquirePrana( int a_iRewardPrana, bool a_bApplyBonus=false );
	void LevelUp();
	void IncChakra( int a_iState );
	void CheckCondition();
	void InitCondition();

	// item ����
	void UseItem( MSG_ITEM* a_pMsg, int a_iFSMState=eTNFsm_Stand );
	void CancelToUseItem();
	void EquipItem( STRUCT_ITEM* a_pEquip, int a_eAdd, bool bIsShield = false );
	void UpdateEquipmentPoints();
	void SetViewEquip(int nView, STRUCT_ITEM * pItemdata);
	int CheckSetItem();
	int ApplyItem( STRUCT_ITEM& a_kItem, int a_iEquipmentSlot );


	// combat ����
	int CastSkill( S_CSP_CAST_AREA_SKILL* a_pMsg, int a_iTargetCount=1 );
	int UseLeftWeapon( S_CSP_CAST_AREA_SKILL* a_pMsg );
	int StartAction( int a_iCaster, TNSKILL_DATA& a_kSkill, int a_iTarget );
	void CalDamage( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iHand=eHnd_Right );
	void CastInstant1( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill );
	void CastInstant2( TNDAMAGE& a_kDamage, TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iTarget, int& a_iCriticalHit );
	int DealDamage( TNDAMAGE& a_kDamage, int a_iTarget, int a_iPercent );
	void CastInstant3( TNSKILL_DATA& a_kSkill, int a_iDamage ); // �߰������� �ߵ��ϴ� instant
	void OnTakeInstant0( TNSKILL_DATA& a_kSkill, int a_iDamage, int a_iAttacker );
	void OnTakeInstant1( int a_iCaster, TNSKILL_DATA& a_kSkill ); // dead���� instant
	int OnTakeInstant2( int a_iCaster, TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex ); // alive���� instant
	int OnTakeAffections( TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iCaster, int a_iPartyLeader, int a_eAdd, int a_eVarType, int a_iLevelGap=0 ); // alive���� buffer
	int OnChargInstance(TNSKILL_DATA& a_kSkill);
	void UseSkill( short a_sProgress = 0 );
	//void SelectTarget( S_CSP_CAST_AREA_SKILL* a_pMsg );
	int SelectTarget( int a_iRange, int a_iAllowedTarget, int a_iCount, int* a_prgTarget, int a_iFarFirst=0, int a_iCenterX=0, int a_iCenterY=0 );
	void DetermineNextPopTime( int a_iCaller=0 );
	bool IsWaitToPop();
	int CanAttackTarget( int a_iTarget );
	bool IsParty( int a_iTarget );
	bool IsPartyLeader() { if( 0 >= Leader ) return true; return false; }
	int CountPartyMember();

	void RefreshPKPrty();

	void AffectEffect( TNEFFECT a_kEffect, int a_eSkill, int a_eAdd, int a_iCaster, int a_iPartyLeader, int a_iLevelGap=0 );
	void OnUnderAttack( int a_iAttacker, int a_iType = eTNUndAtt_Normal );
	int CalDistance2( short a_sDestX, short a_sDestY );
	int OnDefense( int a_iAttackRate, int a_iAttacker, bool a_bCheckDodgeSpeed=true );
	int OnTakeDamage(  TNDAMAGE& a_kDamage, int a_iAttacker, short a_sLevelGap=eCon_MaxGap,int skillID = 999 );
	void Resist( TNDAMAGE& a_kDamage );

	void MemorizeAttacker( int a_iDamage, int a_iScore, int a_iAttacker );
	void ClearAttacker( int a_iRank ); // rank �̸��� attacker���� ��� clear���ش�.
	inline void ClearCurrentTarget() { CurrentTarget = 0; };
	int get_Attacker( int a_iRank );
	void SortAttackers();
	int ScoreDamage( TNDAMAGE& a_kDamage );
	int ScoreDamage( int a_eEffect, int a_iDamage );
	void ForgetAttacker();
	void ClearAggressiveScore();
	void InitStatus();
	unsigned int get_PartyLeader(); 
	void UpdateEquipDur( int a_iDamage, int a_eItemType = 0 ); // 0�� �� �迭�� ���Ѵ�.
	void OnKilled( int a_iKiller, int a_iHow );
	void OnRewardToKiller();
	//void Revive();
	bool IsNotLocked(); // ���� ������ ��� �����Ǿ� �ִ��� �˻�

	bool IsMyAlly( int a_iGuildID );
	void ProgressWaitAction();
	short OnTakeInstantEffects( TNSKILL_DATA& a_kSkill, int a_iSkillBookIndex, int a_iCaster, int a_iPartyLeader, byte a_byPercent = 100 );

	//int AbsorbDamageWithMagicShield( int a_iDamage ); // magic shield
	void AbsorbDamageWithMagicShield( int& a_iDamage ); // magic shield
	void AbsorbDamageWithEnhancedMagicShield( int& a_iDamage, int a_iType );
	int Regen( double a_dPercent, byte byType = REGEN_TYPE_RESURRECT );		//	type 0 : regen, type 1 : resurrect
	void Resurrect( double a_dPercent, int nRecoverry = 0, int iPortal = 0);	//	REGEN�� Ÿ������ �����ϳ�, RESURRECT�� ������ �������θ� ��Ȱ�Ѵ�.
	void OnHeal( int a_iHP, int a_iFunc, unsigned int a_hHealer );
	void OnRecoverTP( int a_iTP, int a_iFunc, unsigned int a_hHealer );
	void TurnOffAffection( int a_eID );
	//int SummonMonster( int a_iMonsterID, int a_iCount, int a_iDuration );	
	//int CreateIllusion( int a_iCount, int a_iDuration );
	void LoadSkills( byte a_byrgSkill[MAX_SKILL] );
	int LearnSkill( unsigned short a_usSkillID, int a_iLevel=1 );
	int CalChakra();
	void ResetSkill();
	void ResetStat();
	int ResetClass();
	void CastOnly( TNSKILL_DATA& a_kData );

	int SelectSkill(); // monster�� ��ų�� �����Ѵ�.
	int SelectSkill2(); // monster�� ��ų�� �����Ѵ�.
	//void HandleEvent( int a_iEventID );
	//void ProcessTask( int a_iTaskID );

	void CheckInvalidCombat();
	int MoveZone( int a_iZone, int a_iX, int a_iY );
	int MoveZoneByNPC( int iNPCID );

	// RvR zone
	void DropKalaCore( int a_iReturnToShrine = 0 );
	void ClearActivity();

	int CheckClan( int a_iClan ) { if( a_iClan == m_byClan ) return 1; return 0; } // Ʋ�� ��쿡 0�� return �Ѵ�.
	int CheckItem( short a_sItemID, int a_iCount, int* a_irgSlot );
	int RemoveItem( int a_iCount, int* a_irgSlot );
	int Summon( int a_iMonsterID, int a_iCount, int a_iPopType, int a_iClass1, int a_iClass2, int a_iClan, int a_iDirection, int x, int y, int a_iTarget, bool a_bCollided, int a_iLifeTime, int a_iOldHandle, int a_iCaller, int a_iRoute=0 );
	int SummonRobot( int a_iPC, int x, int y, int a_iDirection );
	int CheckCombat();

	void ReleaseLinkWithMaster();
	void RemoveMobSummonedAll();
	void KillMobSummoned( int a_iType );
	//void KillFamiliar();
	//void KillRetainer();
	int CheckDistanceFromMaster( int a_iEffectiveDistance, int a_iClass2 );

	// �޽��� ����
	void NotifyUpdateUIMsg();
	void NotifyUpdateStatusMsg( bool a_bCheckTime = false  );
	void BroadcastUpdateStatusMsg( bool a_bCheckTime = false );
	void BroadcastCastSkill( S_CSP_CAST_AREA_SKILL* a_pMsg, int a_iTargetCount );

	void LetsFlee( int a_iEnemy );
	void LetsRoam();

	//----------------------------------
	// Affection ����
	//----------------------------------
public :	
	void CheckAffections( unsigned int a_uiNow );
	void AddEffect( TNEFFECT a_kEffect, int a_iCaster, int a_iPartyLeader );
	void RemoveEffect( int a_eAffID );
	void ClearAffection();
	void OnCure( __int64 a_iVisualAffection );
	void RemoveDamageEffect();
	void ProcessContinuousEffect(bool bSet = false);


private :
	int RegisterAffection( TNEFFECT& a_kEffect, int a_iPartyLeader);
	int UpdateAffection( TNEFFECT& a_kEffect, int a_iAffIndex, int a_iPartyLeader );
	void AffectAffection( int a_iAffTop );
	unsigned int ElapseAffectionTime( int a_iAffTop );

// Public Properties
public :
	//void set_Trimuriti( int a_eClan ) { if( eZoneType_Guild == g_iZoneType ) return; m_byClan = MOB.byTrimuriti = (byte)a_eClan; } 
	void set_Trimuriti( int a_eClan ); 
	int get_Affection( int a_eAffID );
	inline __int64 IsAff( int a_eAffID ) { return m_iAffections & ToAbv(a_eAffID); }
	void CheckCaste();
	void CalCasteSkillPoint();
	void CheckCasteSkillLevel();
	int set_Skill( unsigned short a_sSkillID );
	int set_Segment( int a_iRouteID );


// Private Properties
private :
	__int64 ToAbv( int a_eAffID );
	__int64 ToAbv2( int a_eAffID );
	inline void Add_Aff( __int64 a_iAff ) { m_iAffections = m_iAffections | a_iAff; }
	inline void Remove_Aff( __int64 a_iAff ) { if( a_iAff & m_iAffections ) m_iAffections =  m_iAffections ^ a_iAff; }
	inline void Add_Immunity( int a_iImm ) { m_iImmunity = m_iImmunity | a_iImm; }
	inline void Remove_Immunity( int a_iImm ) { if( a_iImm & m_iImmunity ) m_iImmunity =  m_iImmunity ^ a_iImm; }
	int Aff2Imm( int a_eAffID );
	void Add_Debug( int a_iDbg ); //{ m_iDebug = m_iDebug | a_iDbg; }
	void Remove_Debug( int a_iDbg ); //{ if( a_iDbg & m_iDebug ) m_iDebug =  m_iDebug ^ a_iDbg; }
	void set_JudgeCombat();

// Public Properties
public :
	inline bool IsDebugOn( int a_iDbg ) { if( a_iDbg & m_iDebug ) return true; return false; }
	inline bool IsDebugOff( int a_iDbg ) { if( a_iDbg & m_iDebug ) return false; return true; }

	inline byte get_BodyRadius() { return m_byBodyRadius; }
	inline int get_AR() { return m_kCombatFactors.iAttackRate; }
	inline void get_Coord( HS2D_COORD& a_kCoord ) { a_kCoord.x = TargetX; a_kCoord.y = TargetY; }
	bool IsDead();
	bool IsAlive();
	bool IsCombat();
    bool IsGivedLevelUpReWard(char *ch, int i_level);
    
	bool IsReachCallLevel(char* accoutn,char *ch, int i_level);
	bool IsGivedReachReWard(char *ch, int i_level);

	inline int get_MaxHP() { return m_iMaxHP; }

	void RestrictChakra();
	void UpdatePoints();
	void UpdateChakra();
	void UpdateHPTP();
	void UpdateCF();
	void UpdateDefense();
	void UpdateResist();
	void UpdateResistEffects( int a_iResistType );
	void ToBlessGod(int a_user);
	void UpdateDamage();
	void UpdateDamage( int a_iHand /* = eTNEqu_OneHandWeapon*/ );
	void UpdateSpeed();
	//void UpdateSkill( int a_iSkillBookIndex );
	int DecPrana( double a_dPercent );

	int IncHP( int a_iPoint );
	int DecHP( int a_iPoint );
	int IncTP( int a_iPoint );
	int DecTP( int a_iPoint );
	int IncGold( int a_iPoint );
	int DecGold( int a_iPoint );
	int IncPrana( int a_iPoint );
	int IncBP( int a_iPoint );
	int DecBP( int a_iPoint );
	int get_Gold() { return MOB.nRupiah; }

	byte get_ArmorType();
	int get_ItemID( int a_iEquipmentSlot );

	void ClearProperty();

	short get_WeaponID();
	void SetCharPositionFromZone();


// Private Properties
private :
	inline short get_WeaponIndex( int a_iIndex = eTNEqu_OneHandWeapon ) { return MOB.Equip[a_iIndex].snIndex; }	
	

public:
    STRUCT_MOB MOB;                                      // Mob�⺻���� 
	//STRUCT_AFFECT  Affect[MAX_AFFECT];
	STRUCT_ITEMVIEW	ViewEquip[VISUAL_EQUIP];
    int  Mode;                                           // NPC�� ��� ����
  	int  Leader;
	byte byRootingMode;									//	��Ƽ�� �ڵ��й���
	int  Formation;
    int  RouteType;
	int  m_irgMobListIndex[2]; // ��� �뵵 ��
	int  LastX,LastY;
	int  LastTime; // ��� �뵵 ��
	int  LastSpeed; // ��� �뵵 ��
	int  TargetX,TargetY;
	int  NextX,NextY;
	int  NextAction; // ��� �뵵 ��
    char Route[MAX_ROUTE];
    int  WaitSec;
	int  PosX,PosY; // ��� �뵵 ��
    int  Segment;
/// telnet:carrionfields.org:9999

	  ////////////////
	int SegmentX,SegmentY;
	int SegmentListX[MAX_SEGMENT];
	int SegmentListY[MAX_SEGMENT];
    int SegmentWait[MAX_SEGMENT];
	int SegmentRange[MAX_SEGMENT];
	int SegmentDirection;             // 0:����  1:ȸ��
	int SegmentProgress;              // 0:��ŸƮ-���׸�Ʈ0  1:���׸�Ʈ1-���׸�Ʈ2
	int GenerateIndex;
      //int Next;
	int CurrentTarget;                                                   // �����ؾ��� �� �ε���
	int m_irgParty[MAX_PARTY]; // p
    int GetEnemyFromView(void);
  	int	WeaponDamage; // ��� �뵵 ��
	int	Summoner; // ��� �뵵 ��
	int	PotionCount; // ��� �뵵 ��
	int	Parry; // ��� �뵵 ��
	int	GuildDisable; // ��� �뵵 ��
	// Ư��
	int DropBonus; // ��� �뵵 ��
	int ExpBonus; // ��� �뵵 ��
	int ForceDamage; // ��� �뵵 ��
	//int ReflectDamage;
	  // Equip�� ���� ��.
	  //int MaxDurability;
	  //int MaxDamage;
	  //int MaxLoad;
	  //
	  // 00000000 /     00000000  /  000   00000 / 00000000  
	  // Sync(MAX_256)  X Pos(MAX 2048)    Detail(MAX:8012)

	bool ExpandFunc(int nTimeIndex, short snDays = 30);
	bool IsUsablePustica(BYTE byType, int iTarget1, short snTarget2);
// Attributes
public :
	int m_iHandle;
	byte m_eMobType; // 0:Pc, 1:Monster, 3:Item

	TNCHAKRA m_kChakra; // base/changed
	TNCOMBAT_FACTORS m_kCombatFactors;
	int m_iCaste;
	byte m_byClan;

	int m_iMaxHP;
	int m_iMaxTP;
	int m_iMaxPrana;
	int m_irgHPRecovery[2];
	int m_irgTPRecovery[2];

	TNPointBar m_kCPRemaining; // ���� �ִ� chakra point
	TNPointBar m_kSPRemaining; // ���� �ִ� skill point	
	TNPointBar m_kCasteSPRemaining; // ���� �ִ� caste skill point	
	TNPointBar m_kMagicShield;
	TNPointBar m_kEnhancedMagicShield;

	TNJUDGE_COMBAT m_krgJudgeCombat[2][2];
	TNDeck100 m_krgCFTable[TN_CFTABLE_COUNT];  // combat factor table, ���ݼ����� Ȯ���ϱ� ���� �뵵
	//TNRate m_kMurderDropRate;
	//TNRate m_kInnocentDropRate;
	//TNRate m_kFirstStrikerDropRate;
	TNRate m_kWeaknessRate;

	TNRate m_krgResistEffect[eRst_Max];

	TNLASTEST_TIME m_kLastTime;
	TNSKILLCASTRECORD m_kPrevSkill;
	//TNCombo m_krgCombo[3];
	
	//int m_iCoefficientIndex;
	int m_iWeaponCoefficient;

	TNDAMAGE m_krgDamage[eHnd_Count]; // character �����ϴ� ���ݷ�
	TNDAMAGE m_krgWeaponDamage[eHnd_Count]; // ���� ��ü�� ���ݷ�
	int m_iLastDamage;
	int m_iMoveSpeed;
	int m_iAttackSpeed;
	short m_sAttackSpeedCorrect;
	short m_sCastSpeedCorrect;
	int m_iCombatSyncPhase;

	TNVARIATION m_krgVariation[TN_MAX_VARIATION_COUNT][3];
	TNSIGHT m_kSight;

	TNEFFECT m_krgMastery[TN_MASTERY_COUNT];

	struct TNSKILL
	{
		unsigned short sID;
		byte byLevelPlus;
		byte byDummy;
		unsigned int uiCoolDownTime;
		int iIndex;  // skill raw data�� ����� ���� �迭�� ���� index
		TNDAMAGE kDamage;
		TNDeck100 kDeck;
		//TNRate kDice;
		TNSKILL() : sID(0), byLevelPlus(0), uiCoolDownTime(0), iIndex(0) {}
	};

	TNSKILL m_krgSkill[MAX_SKILL+1]; // �⺻ skill �ϳ��� �߰��Ѵ�.
	unsigned int m_uirgInstantCoolDownTime[eConst_MaxInstantCoolDonw];
	unsigned int m_uirgCooldownTime[eConst_MaxCooldownTimeCount];

	TNAFFECTION m_krgAffection[eConst_MaxAffectionCount+1]; // 0�� index�� ������� �ʴ´�.
	int m_iLastAff;
	byte m_byrgAffection[eConst_MaxAffectionCount+1]; // 1,2,3,4,5, n-1, n , 0, 0, 0
	int m_iAffTop; // default �� 0

	short m_sLastItemUsed;
	byte m_byLastItemUsedCount;
	byte m_byLastItemUsedLoc;

	//bool m_bIsNotBuff;
	//std::map< int, TNAFFECTION > m_kAffMap;
	//CRITICAL_SECTION m_cs;
	int m_iBlockedCell;	
	__int64 m_iCantDetect; // ���� ������ �ʴ� ���� ���Ѵ�.
	__int64 m_iAffections; // bit vector
	__int64 m_iInnerAffections;
	__int64 m_iPrevAffections;
	int m_iImmunity; // bit vector
	byte m_isBlessGod; //fors_debug �޸�ף��ͻȻû��15���Ӿ���ʧ
	int m_iNBRank;
	int m_iUserWhat;
	
	TNEFFECTTOLERANCE m_kTolerance;
	ETNFsmState m_eFSM;
	byte m_byBodyRadius;
	bool m_bDualWeapon;
	bool m_bIsInArenaEntry;
	TNRate m_kDualHit;

	char m_szLogFile[40];	
	int m_iPartySize;
	int m_iPranaDec;
	int m_iButtonStatus;

	struct TNWAIT_ACTION // FSM���� ó���� �ؾ��Ѵ�. �켱�� �׳� ����.
	{
		int iAction;
		unsigned int uiWaitingTime;
	};
	TNWAIT_ACTION m_kWaitAction;

	struct TNMOVE_RECORD
	{
		unsigned int uiElapsed;
		HS2D_COORD kPos;
		int iSpeed;
		int behackedcount;
		int nohackcount;
	};

	unsigned int m_uirgAttackTimeRecord[eHack_MaxAttackTimeRecordCount];
	int m_iAttackTimeRecordIndex;

	struct TNSKILL_CAST_RECORD
	{
		int iSkill;
		unsigned int uiTime;
		int iCount;
	};
	TNSKILL_CAST_RECORD m_kSkillCastRecord;

	TNMOVE_RECORD m_kMoveRecord;

	struct TNMOVE_LOG
	{
		short iDistance;
		short iSpeed;
		unsigned int uiTime;
	};

	TNMOVE_LOG m_krgMoveLog[eMvLog_Size];
	int m_iMvLogIndex;

	int m_iAggressiveCorrect;
	int m_iAggressiveScore;

	int m_iKiller;
	int m_iHPProblem;

	STRUCT_ITEM m_krgSetItem[eSetItem_MaxEffectItem];



	//---------------------------------------------
	// Monster ����
	//---------------------------------------------
public :
	int m_iFamily;
	int m_iGroup;
	bool m_bSolo;
	int m_iCastCount;
	unsigned int m_uiActionLock;
	unsigned int m_uiActionDelay;
	TNATTACKER m_krgAttacker[TN_ATTACKER_COUNT];
	int m_iAttackerCount; // �ڽ��� �����ϴ� mobile ��
	int m_iCheckEnemyCount; // ���� ���� ��
	int m_iCantTraceTarget;
	int m_iReactToEnemyBehindWall;
	//int m_iEnemyCount; // �ڽ��� �����ϰ� �ִ� �� ��	
	int m_iAttackCount; // combat ���¿��� ������ �� Ƚ��, peace���¿����� 0���� �ʱ�ȭ�ȴ�.
	int m_iTraceCount;
	int m_iTotalTraceCount;
	//int m_iTargetHandle;

	TNRate m_kMovement;
	TNRate m_kAggrCond;

	HS2D_COORD m_krgPath[ePath_MaxCount];
	int m_iPathProgress;

	int m_iPathIndex;
	HS2D_COORD m_krgPathFinded[eTNPath_Count];

	int m_iIgnoreObstacle;
	//int m_iPlusRange;
	//bool m_bSkillNotCastYet;
	int m_iSkillCharged;
	int m_iSkillPatternIndex;
	int m_irgSkillPattern[eSklPtrn_Size];

	HS2D_COORD m_krgInfluenceGrid[9];
	int m_iInfluenceGridSize;	
	

	int m_iDebugFlag; // debug�� ���� ����
	int m_iDebugFlag2; // �������� debug�� ���� ����
	int m_iDebug;
	unsigned int m_uiPkDurTime;
	int m_iPKDefender;

	int m_eStatus;

    TNDeck100 m_kSelectTarget;
	unsigned int m_uiResistEffectTime;
	
	struct TNCONDITION
	{
		int irgCond[eTNCond_MaxSort];
		int irgCondCount[eTNCond_MaxSort];
		unsigned int uirgExpireTime[eTNCond_MaxSort];
	};
	TNCONDITION m_kCond;

	int m_iLinker; // spirit link
	int m_iPassenger; // �̰��� �迭�� ���¸� ���Ͽ�, �������� follower�� ������ �� �ִ�.
	int m_irgFollower[eFollower_MaxCount]; // ����(pet�ϼ��� �ְ�, guard�ϼ��� ����.)
	//int m_iFamiliar;
	//int m_iRetainer;
	int m_irgSummoned[eFellow_MaxCount];
	unsigned int m_uiLifeTime;

	int m_iDirection;

	int m_iAIOption;
	int m_iCountKilled;

	#ifdef __TN_PLAYMOVIE__
	int m_irgFlag[10];
	int m_irgRobot[eRobot_MaxCount];
	#endif


public :
	short Direction;
	short State;
	BYTE	byMaxInven;				//	�κ��� �ִ� ����������
	byte	m_byBramanRank;			//	��ŷ�� ���� �ֽŰ��(�ʱ⿡ 1�� ����)
	bool	m_bAMoneyRoot;			//	�ڵ����ݱ� on, off ��ư
	short	m_snSaveNPC;			//	����� ������ġ����
	short	m_snMovePortal;			//	��Ż ������ ���� �̵��� ��Ż����
	short	m_snResurrect;			//	��Ȱ������ ���� ��Ȱ�� ��ġ����
	bool	m_bMoveZone;
	//byte	m_byDecPranaRate;		//	����� ���� ���Һ���
	//byte	m_byKillLevel;			//	����� ���� ���Ҵ�� ����

	double	m_dGetPranaRate;
	double	m_dGetMoneyRate;
	double	m_dCutDeathPranaRate;

	DWORD	m_dwInvenBlock[3];		//	0,1,2 - �κ�1,2,3�� �ǹ��ϰ� ���� 24��Ʈ�� �ϳ��� �κ����� ����ϱ�� �Ѵ�(������� ���Խ��� ���)
	byte	m_byInitQuiz; 
	DWORD	m_dwQuestInitTime;
};


#endif