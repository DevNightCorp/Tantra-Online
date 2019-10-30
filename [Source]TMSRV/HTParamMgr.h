#ifndef _HTPARAMMGR_H_
#define _HTPARAMMGR_H_

#include <vector>
#include <map>

//#define HT_NEED_NAME

#include "HTFile.h"
#include "BaseDef.h"

class CHTParamIDCheck
{
public:
	 static bool		HT_bIsMonster( const int id );
	 static bool		HT_bIsMonsterSkill( const int id );
	 static bool		HT_bIsPCSkill( const int id );
	 static bool		HT_bIsItem( const int id );

	 static bool		HT_bIsPCSkillNagaKin( const int id );
	 static bool		HT_bIsPCSkillNagaKin1st( const int id );
	 static bool		HT_bIsPCSkillNagaKin2nd( const int id );
	 static bool		HT_bIsPCSkillNagaKin3rd( const int id );
	 static bool		HT_bIsPCSkillAsuRak( const int id );
	 static bool		HT_bIsPCSkillAsuRak1st( const int id );
	 static bool		HT_bIsPCSkillAsuRak2nd( const int id );
	 static bool		HT_bIsPCSkillAsuRak3rd( const int id );
	 static bool		HT_bIsPCSkillYakGan( const int id );
	 static bool		HT_bIsPCSkillYakGan1st( const int id );
	 static bool		HT_bIsPCSkillYakGan2nd( const int id );
	 static bool		HT_bIsPCSkillYakGan3rd( const int id );
	 static bool		HT_bIsPCSkillDevGaru( const int id );
	 static bool		HT_bIsPCSkillDevGaru1st( const int id );
	 static bool		HT_bIsPCSkillDevGaru2nd( const int id );
	 static bool		HT_bIsPCSkillDevGaru3rd( const int id );
	
	 static bool		HT_bIsItemRare( const int id );
	 static bool		HT_bIsItemUnique( const int id );
	 static bool		HT_bIsItemQuest( const int id );
	 static bool		HT_bIsItemMagic( const int id );

	 static bool		HT_bIsItemWeapon( const int id );
	 static bool		HT_bIsItemWeaponOneHand( const int id );
	 static bool		HT_bIsItemWeaponOneHandNormal( const int id );
	 static bool		HT_bIsItemWeaponOneHandNormalNotMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandNormalMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandRare( const int id );
	 static bool		HT_bIsItemWeaponOneHandRareNotMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandRareMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandUnique( const int id );
	 static bool		HT_bIsItemWeaponOneHandUniqueNotMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandUniqueMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandQuest( const int id );
	 static bool		HT_bIsItemWeaponOneHandQuestNotMagic( const int id );
	 static bool		HT_bIsItemWeaponOneHandQuestMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHand( const int id );
	 static bool		HT_bIsItemWeaponTwoHandNotMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandNormal( const int id );
	 static bool		HT_bIsItemWeaponTwoHandNormalNotMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandNormalMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandRare( const int id );
	 static bool		HT_bIsItemWeaponTwoHandRareNotMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandRareMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandUnique( const int id );
	 static bool		HT_bIsItemWeaponTwoHandUniqueNotMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandUniqueMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandQuest( const int id );
	 static bool		HT_bIsItemWeaponTwoHandQuestNotMagic( const int id );
	 static bool		HT_bIsItemWeaponTwoHandQuestMagic( const int id );
	 static bool		HT_bIsItemWeaponThrow( const int id );
	 static bool		HT_bIsItemWeaponThrowNormal( const int id );
	 static bool		HT_bIsItemWeaponThrowNormalNotMagic( const int id );
	// static bool		HT_bIsItemWeaponThrowNormalMagic( const int id );
	 static bool		HT_bIsItemWeaponThrowRare( const int id );
	 static bool		HT_bIsItemWeaponThrowRareNotMagic( const int id );
	// static bool		HT_bIsItemWeaponThrowRareMagic( const int id );
	 static bool		HT_bIsItemWeaponThrowUnique( const int id );
	 static bool		HT_bIsItemWeaponThrowUniqueNotMagic( const int id );
	// static bool		HT_bIsItemWeaponThrowUniqueMagic( const int id );
	 static bool		HT_bIsItemWeaponThrowQuest( const int id );
	 static bool		HT_bIsItemWeaponThrowQuestNotMagic( const int id );
	// static bool		HT_bIsItemWeaponThrowQuestMagic( const int id );
	
	 static bool		HT_bIsItemDefence( const int id );
	 static bool		HT_bIsItemDefenceArmor( const int id );
	 static bool		HT_bIsItemDefenceArmorNormal( const int id );
	 static bool		HT_bIsItemDefenceArmorRare( const int id );
	 static bool		HT_bIsItemDefenceArmorUnique( const int id );
	 static bool		HT_bIsItemDefenceArmorQuest( const int id );
	 static bool		HT_bIsItemDefencePants( const int id );
	 static bool		HT_bIsItemDefencePantsNormal( const int id );
	 static bool		HT_bIsItemDefencePantsRare( const int id );
	 static bool		HT_bIsItemDefencePantsUnique( const int id );
	 static bool		HT_bIsItemDefencePantsQuest( const int id );
	 static bool		HT_bIsItemDefenceGloves( const int id );
	 static bool		HT_bIsItemDefenceGlovesNormal( const int id );
	 static bool		HT_bIsItemDefenceGlovesRare( const int id );
	 static bool		HT_bIsItemDefenceGlovesUnique( const int id );
	 static bool		HT_bIsItemDefenceGlovesQuest( const int id );
	 static bool		HT_bIsItemDefenceHelmet( const int id );
	 static bool		HT_bIsItemDefenceHelmetNormal( const int id );
	 static bool		HT_bIsItemDefenceHelmetRare( const int id );
	 static bool		HT_bIsItemDefenceHelmetUnique( const int id );
	 static bool		HT_bIsItemDefenceHelmetQuest( const int id );
	 static bool		HT_bIsItemDefenceBelt( const int id );
	 static bool		HT_bIsItemDefenceBeltNormal( const int id );
	 static bool		HT_bIsItemDefenceBeltRare( const int id );
	 static bool		HT_bIsItemDefenceBeltUnique( const int id );
	 static bool		HT_bIsItemDefenceBeltQuest( const int id );
	 static bool		HT_bIsItemDefenceShoes( const int id );
	 static bool		HT_bIsItemDefenceShoesNormal( const int id );
	 static bool		HT_bIsItemDefenceShoesRare( const int id );
	 static bool		HT_bIsItemDefenceShoesUnique( const int id );
	 static bool		HT_bIsItemDefenceShoesQuest( const int id );
	 static bool		HT_bIsItemDefenceShield( const int id );
	 static bool		HT_bIsItemDefenceShieldNormal( const int id );
	 static bool		HT_bIsItemDefenceShieldRare( const int id );
	 static bool		HT_bIsItemDefenceShieldUnique( const int id );
	 static bool		HT_bIsItemDefenceShieldQuest( const int id );

	static bool		HT_bIsItemCharm( const int id );

	 static bool		HT_bIsItemAccessory( const int id );
	 static bool		HT_bIsItemAccessoryEarring( const int id );
	 static bool		HT_bIsItemAccessoryEarringNormal( const int id );
	 static bool		HT_bIsItemAccessoryEarringRare( const int id );
	 static bool		HT_bIsItemAccessoryEarringUnique( const int id );
	 static bool		HT_bIsItemAccessoryEarringQuest( const int id );
	 static bool		HT_bIsItemAccessoryBracelet( const int id );
	 static bool		HT_bIsItemAccessoryBraceletNormal( const int id );
	 static bool		HT_bIsItemAccessoryBraceletRare( const int id );
	 static bool		HT_bIsItemAccessoryBraceletUnique( const int id );
	 static bool		HT_bIsItemAccessoryBraceletQuest( const int id );
	 static bool		HT_bIsItemAccessoryNecklace( const int id );
	 static bool		HT_bIsItemAccessoryNecklaceNormal( const int id );
	 static bool		HT_bIsItemAccessoryNecklaceRare( const int id );
	 static bool		HT_bIsItemAccessoryNecklaceUnique( const int id );
	 static bool		HT_bIsItemAccessoryNecklaceQuest( const int id );
	 static bool		HT_bIsItemAccessoryExpandInven( const int id );
	 static bool		HT_bIsItemAccessoryExpandInvenNormal( const int id );
	 static bool		HT_bIsItemAccessoryExpandInvenQuest( const int id );
	 static bool		HT_bIsItemAccessoryRing( const int id );
	 static bool		HT_bIsItemAccessoryRingNormal( const int id );
	 static bool		HT_bIsItemAccessoryRingRare( const int id );
	 static bool		HT_bIsItemAccessoryRingUnique( const int id );
	 static bool		HT_bIsItemAccessoryRingQuest( const int id );

	 static bool		HT_bIsItemRefine( const int id );
	 static bool		HT_bIsItemRefineMain( const int id );
	 static bool		HT_bIsItemRefineSub( const int id );
	 static bool		HT_bIsItemRefineSub2( const int id );

	 static bool		HT_bIsItemCharge( const int id );
	 static bool		HT_bIsItemChargeContinuance( const int id );
	 static bool		HT_bIsItemChargeFunction( const int id );

	 static bool		HT_bIsItemUsable( const int id );
	 static bool		HT_bIsItemPacked( const int id );
	 static bool		HT_bIsItemUsableMoney( const int id );
	 static bool		HT_bIsItemUsableArrow( const int id );

	 static bool		HT_bIsItemCollect( const int id );

	 static bool		HT_bIsItemQuestOnly( const int id );

	 static bool		HT_bIsNPC( const int id );
	 static bool		HT_bIsChargeNPC( const int id);
	 static bool		HT_bIsPortal( const int id );
	 static bool		HT_bIsTaskQuest( const int id );
};

class CHTXMLParser;

struct HTIDLevel
{
	HTIDLevel();
	~HTIDLevel();
	HTIDLevel( const HTIDLevel& oIDLevel );
	int		iID;
	byte	byteLevel;
};

class CHTBaseParamTable
{
public:
	CHTBaseParamTable();
	virtual ~CHTBaseParamTable();

	//virtual	bool		HT_bGetIDLevelbyIndex( const int index, int* piID, byte* pbyteLevel ) = 0;
	virtual bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel ) = 0;

	// SetID
	virtual bool		HT_bLockID( const int id, const byte iLevel = 0 ) = 0;
	virtual bool		HT_bUnLockID( const int id, const byte iLevel = 0 ) = 0;

	// Load & Save
	virtual bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) = 0;
	virtual bool		HT_bLoad( CHTFile* pFile/*, CHTString& strTable*/ ) = 0;
	virtual bool		HT_bSave( CHTFile* pFile ) = 0;

#ifdef HT_NEED_NAME
	 virtual bool		HT_bGetName( const int id, CHTString* pstrName );
	 virtual bool		HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName );
	 virtual bool		HT_bGetName( CHTString* pstrName );
#endif

	// Monster Param with ID
	virtual bool		HT_bGetMonsterLevel( const int id, byte* pbyteLevel );
	virtual bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	virtual bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	virtual bool		HT_bGetMonsterAI( const int id, int* piAI );
	virtual bool		HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime );
	virtual bool		HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 );
	virtual bool		HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 );
	virtual bool		HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 );
	virtual bool		HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 );
	virtual bool		HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond );
	virtual bool		HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond );
	virtual bool		HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount );
	virtual bool		HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond );
	virtual bool		HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond );
	virtual bool		HT_bGetMonsterHelpCond( const int id, byte* pbyteHelpCond );
	virtual bool		HT_bGetMonsterHelpCondCount( const int id, byte* pbyteHelpCondCount );
	virtual bool		HT_bGetMonsterLinkCond( const int id, byte* pbyteLinkCond );
	virtual bool		HT_bGetMonsterLinkCondCount( const int id, byte* pbyteLinkCondCount );
	virtual bool		HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell );
	virtual bool		HT_bGetMonsterCantDetect( const int id, int* piCantDetect );
	virtual bool		HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti );
	virtual bool		HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight );
	virtual bool		HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight );
	virtual bool		HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin );
	virtual bool		HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax );
	virtual bool		HT_bGetMonsterMovement( const int id, byte* pbyteMovement );
	virtual bool		HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate );
	virtual bool		HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI );
	virtual bool		HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo );
	virtual bool		HT_bGetMonsterMuscle( const int id, short* psMuscle );
	virtual bool		HT_bGetMonsterNerves( const int id, short* psNerves );
	virtual bool		HT_bGetMonsterHeart( const int id, short* psHeart );
	virtual bool		HT_bGetMonsterMind( const int id, short* psMind );
	virtual bool		HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType );
	virtual bool		HT_bGetMonsterHP( const int id, unsigned int* pnHP );
	virtual bool		HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery );
	virtual bool		HT_bGetMonsterAttackRate( const int id, int* piAttackRate );
	virtual bool		HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate );
	//virtual bool		HT_bGetMonsterBlockRate( const int id, byte* pbyteBlockRate );
	//virtual bool		HT_bGetMonsterCriticalRate( const int id, byte* pbyteCriticalRate );
	virtual bool		HT_bGetMonsterAC( const int id, int* piAC );
	virtual bool		HT_bGetMonsterFireResist( const int id, int* piFireResist );
	virtual bool		HT_bGetMonsterColdResist( const int id, int* piColdResist );
	virtual bool		HT_bGetMonsterLightningResist( const int id, int* piLightningResist );
	virtual bool		HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist );
	virtual bool		HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed );
	virtual bool		HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed );
	virtual bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	virtual bool		HT_bGetMonsterSkill0( const int id, int* pidSkill0 );
	virtual bool		HT_bGetMonsterSkill1( const int id, int* pidSkill1 );
	virtual bool		HT_bGetMonsterSkill2( const int id, int* pidSkill2 );
	virtual bool		HT_bGetMonsterSkill3( const int id, int* pidSkill3 );
	virtual bool		HT_bGetMonsterSkill4( const int id, int* pidSkill4 );
	virtual bool		HT_bGetMonsterSkill5( const int id, int* pidSkill5 );
	virtual bool		HT_bGetMonsterSkill6( const int id, int* pidSkill6 );
	virtual bool		HT_bGetMonsterSkill7( const int id, int* pidSkill7 );
	virtual bool		HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 );
	virtual bool		HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 );
	virtual bool		HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 );
	virtual bool		HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 );
	virtual bool		HT_bGetMonsterImmunity( const int id, int* piImmunity );
	virtual bool		HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst );
	virtual bool		HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint );
	virtual bool		HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold );
	virtual bool		HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana );
	virtual bool		HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID );
	virtual bool		HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate );
	virtual bool		HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID );
	virtual bool		HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate );
	virtual bool		HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID );
	virtual bool		HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate );
	virtual bool		HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID );
	virtual bool		HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate );
	virtual bool		HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID );
	virtual bool		HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate );
	virtual bool		HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID );
	virtual bool		HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate );
	virtual bool		HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID );
	virtual bool		HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate );
	virtual bool		HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID );
	virtual bool		HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate );
	virtual bool		HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade );
	virtual bool		HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate );
	//virtual bool		HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount );
	virtual bool		HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade );
	virtual bool		HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate );
	//virtual bool		HT_bGetMonsterItem9DeadCount( const int id, unsigned int* pnItem9DeadCount );
	virtual bool		HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 );
	virtual bool		HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 );
	virtual bool		HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 );
	virtual bool		HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 );
	virtual bool		HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 );
	virtual bool		HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 );
	virtual bool		HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 );
	virtual bool		HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7 );

	// Monster Param with No ID
	virtual bool		HT_bGetMonsterLevel( byte* pbyteLevel );
	virtual bool		HT_bGetMonsterClass( byte* pbyteClass );
	virtual bool		HT_bGetMonsterSize( byte* pbyteSize );
	virtual bool		HT_bGetMonsterAI( int* piAI );
	virtual bool		HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime );
	virtual bool		HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 );
	virtual bool		HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 );
	virtual bool		HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 );
	virtual bool		HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 );
	virtual bool		HT_bGetMonsterAggrCond( byte* pbyteAggrCond );
	virtual bool		HT_bGetMonsterFleeCond( byte* pbyteFleeCond );
	virtual bool		HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount );
	virtual bool		HT_bGetMonsterTraceCond( byte* pbyteTraceCond );
	virtual bool		HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond );
	virtual bool		HT_bGetMonsterHelpCond( byte* pbyteHeloCond );
	virtual bool		HT_bGetMonsterHelpCondCount( byte* pbyteHelpCondCount );
	virtual bool		HT_bGetMonsterLinkCond( byte* pbyteLinkCond );
	virtual bool		HT_bGetMonsterLinkCondCount( byte* pbyteLinkCondCount );
	virtual bool		HT_bGetMonsterBlockedCell( int* piBlockedCell );
	virtual bool		HT_bGetMonsterCantDetect( int* piCantDetect );
	virtual bool		HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti );
	virtual bool		HT_bGetMonsterNormalSight( byte* pbyteNormalSight );
	virtual bool		HT_bGetMonsterCombatSight( byte* pbyteCombatSight );
	virtual bool		HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin );
	virtual bool		HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax );
	virtual bool		HT_bGetMonsterMovement( byte* pbyteMovement );
	virtual bool		HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate );
	virtual bool		HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI );
	virtual bool		HT_bGetMonsterEventNo( unsigned int* pnEventNo );
	virtual bool		HT_bGetMonsterMuscle( short* psMuscle );
	virtual bool		HT_bGetMonsterNerves( short* psNerves );
	virtual bool		HT_bGetMonsterHeart( short* psHeart );
	virtual bool		HT_bGetMonsterMind( short* psMind );
	virtual bool		HT_bGetMonsterArmorType( byte* pbyteArmorType );
	virtual bool		HT_bGetMonsterHP( unsigned int* pnHP );
	virtual bool		HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery );
	virtual bool		HT_bGetMonsterAttackRate( int* piAttackRate );
	virtual bool		HT_bGetMonsterDodgeRate( int* piDodgeRate );
	//virtual bool		HT_bGetMonsterBlockRate( byte* pbyteBlockRate );
	//virtual bool		HT_bGetMonsterCriticalRate( byte* pbyteCriticalRate );
	virtual bool		HT_bGetMonsterAC( int* piAC );
	virtual bool		HT_bGetMonsterFireResist( int* piFireResist );
	virtual bool		HT_bGetMonsterColdResist( int* piColdResist );
	virtual bool		HT_bGetMonsterLightningResist( int* piLightningResist );
	virtual bool		HT_bGetMonsterPoisonResist( int* piPoisonResist );
	virtual bool		HT_bGetMonsterWalkSpeed( int* piWalkSpeed );
	virtual bool		HT_bGetMonsterRunSpeed( int* piRunSpeed );
	virtual bool		HT_bGetMonsterFly( byte* pbFly );
	virtual bool		HT_bGetMonsterSkill0( int* pidSkill0 );
	virtual bool		HT_bGetMonsterSkill1( int* pidSkill1 );
	virtual bool		HT_bGetMonsterSkill2( int* pidSkill2 );
	virtual bool		HT_bGetMonsterSkill3( int* pidSkill3 );
	virtual bool		HT_bGetMonsterSkill4( int* pidSkill4 );
	virtual bool		HT_bGetMonsterSkill5( int* pidSkill5 );
	virtual bool		HT_bGetMonsterSkill6( int* pidSkill6 );
	virtual bool		HT_bGetMonsterSkill7( int* pidSkill7 );
	virtual bool		HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 );
	virtual bool		HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 );
	virtual bool		HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 );
	virtual bool		HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 );
	virtual bool		HT_bGetMonsterImmunity( int* piImmunity );
	virtual bool		HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst );
	virtual bool		HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint );
	virtual bool		HT_bGetMonsterRewardGold( unsigned int* pnRewardGold );
	virtual bool		HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana );
	virtual bool		HT_bGetMonsterItem0ItemID( short* psItem0ID );
	virtual bool		HT_bGetMonsterItem0DropRate( short* psItem0DropRate );
	virtual bool		HT_bGetMonsterItem1ItemID( short* psItem1ID );
	virtual bool		HT_bGetMonsterItem1DropRate( short* psItem1DropRate );
	virtual bool		HT_bGetMonsterItem2ItemID( short* psItem2ID );
	virtual bool		HT_bGetMonsterItem2DropRate( short* psItem2DropRate );
	virtual bool		HT_bGetMonsterItem3ItemID( short* psItem3ID );
	virtual bool		HT_bGetMonsterItem3DropRate( short* psItem3DropRate );
	virtual bool		HT_bGetMonsterItem4ItemID( short* psItem4ID );
	virtual bool		HT_bGetMonsterItem4DropRate( short* psItem4DropRate );
	virtual bool		HT_bGetMonsterItem5ItemID( short* psItem5ID );
	virtual bool		HT_bGetMonsterItem5DropRate( short* psItem5DropRate );
	virtual bool		HT_bGetMonsterItem6ItemID( short* psItem6ID );
	virtual bool		HT_bGetMonsterItem6DropRate( short* psItem6DropRate );
	virtual bool		HT_bGetMonsterItem7ItemID( short* psItem7ID );
	virtual bool		HT_bGetMonsterItem7DropRate( short* psItem7DropRate );
	virtual bool		HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade );
	virtual bool		HT_bGetMonsterItem8DropRate( short* psItem8DropRate );
	//virtual bool		HT_bGetMonsterItem8DeadCount( unsigned int* pnItem8DeadCount );
	virtual bool		HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade );
	virtual bool		HT_bGetMonsterItem9DropRate( short* psItem9DropRate );
	//virtual bool		HT_bGetMonsterItem9DeadCount( unsigned int* pnItem9DeadCount );
	virtual bool		HT_bGetMonsterReserve0( byte* pbyteReserve0 );
	virtual bool		HT_bGetMonsterReserve1( byte* pbyteReserve1 );
	virtual bool		HT_bGetMonsterReserve2( byte* pbyteReserve2 );
	virtual bool		HT_bGetMonsterReserve3( byte* pbyteReserve3 );
	virtual bool		HT_bGetMonsterReserve4( byte* pbyteReserve4 );
	virtual bool		HT_bGetMonsterReserve5( byte* pbyteReserve5 );
	virtual bool		HT_bGetMonsterReserve6( byte* pbyteReserve6 );
	virtual bool		HT_bGetMonsterReserve7( byte* pbyteReserve7 );

	// Monster Skill Param with ID
	virtual bool		HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	virtual bool		HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType );
	virtual bool		HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	virtual bool		HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent );
	virtual bool		HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration );
	virtual bool		HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	virtual bool		HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag );
	virtual bool		HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	virtual bool		HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime );
	virtual bool		HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount );
	virtual bool		HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	virtual bool		HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange );
	virtual bool		HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	virtual bool		HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	virtual bool		HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	virtual bool		HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	virtual bool		HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	virtual bool		HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	virtual bool		HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	virtual bool		HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	virtual bool		HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	virtual bool		HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	virtual bool		HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	virtual bool		HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	virtual bool		HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	virtual bool		HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	virtual bool		HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	virtual bool		HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	virtual bool		HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	virtual bool		HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	virtual bool		HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	virtual bool		HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	virtual bool		HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	virtual bool		HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	virtual bool		HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	virtual bool		HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	virtual bool		HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	virtual bool		HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	virtual bool		HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	virtual bool		HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	virtual bool		HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	virtual bool		HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	virtual bool		HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	virtual bool		HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	virtual bool		HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	virtual bool		HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	virtual bool		HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	virtual bool		HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	virtual bool		HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	virtual bool		HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	virtual bool		HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	virtual bool		HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	virtual bool		HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	virtual bool		HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	virtual bool		HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	virtual bool		HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	virtual bool		HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	virtual bool		HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	virtual bool		HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	virtual bool		HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	virtual bool		HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );

	// Skill Param without ID
	virtual bool		HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel );
	virtual bool		HT_bGetMonsterSkillType( byte* pbyteType );
	virtual bool		HT_bGetMonsterSkillCombatPhase( short* psCombatPhase );
	virtual bool		HT_bGetMonsterSkillSpeechContent( short* psSpeechContent );
	virtual bool		HT_bGetMonsterSkillDuration( int* piDuration );
	virtual bool		HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate );
	virtual bool		HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag );
	virtual bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );
	virtual bool		HT_bGetMonsterSkillActivateTime( int* piActivateTime );
	virtual bool		HT_bGetMonsterSkillCastCount( byte* pbyteCastCount );
	virtual bool		HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime );
	virtual bool		HT_bGetMonsterSkillRange( int* piRange );
	virtual bool		HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect );
	virtual bool		HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget );
	virtual bool		HT_bGetMonsterSkillAttackType( byte* pbyteAttackType );
	virtual bool		HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange );
	virtual bool		HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate );
	virtual bool		HT_bGetMonsterSkillEffect1ID( int* piEffect1ID );
	virtual bool		HT_bGetMonsterSkillEffect1Function( int* piEffect1Function );
	virtual bool		HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration );
	virtual bool		HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 );
	virtual bool		HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 );
	virtual bool		HT_bGetMonsterSkillEffect2ID( int* piEffect2ID );
	virtual bool		HT_bGetMonsterSkillEffect2Function( int* piEffect2Function );
	virtual bool		HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration );
	virtual bool		HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 );
	virtual bool		HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 );
	virtual bool		HT_bGetMonsterSkillEffect3ID( int* piEffect3ID );
	virtual bool		HT_bGetMonsterSkillEffect3Function( int* piEffect3Function );
	virtual bool		HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration );
	virtual bool		HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 );
	virtual bool		HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 );
	virtual bool		HT_bGetMonsterSkillEffect4ID( int* piEffect4ID );
	virtual bool		HT_bGetMonsterSkillEffect4Function( int* piEffect4Function );
	virtual bool		HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration );
	virtual bool		HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 );
	virtual bool		HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 );
	virtual bool		HT_bGetMonsterSkillEffect5ID( int* piEffect5ID );
	virtual bool		HT_bGetMonsterSkillEffect5Function( int* piEffect5Function );
	virtual bool		HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration );
	virtual bool		HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 );
	virtual bool		HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 );
	virtual bool		HT_bGetMonsterSkillCostTP( int* piCostTP );
	virtual bool		HT_bGetMonsterSkillCostHP( int* piCostHP );
	virtual bool		HT_bGetMonsterSkillidCostItem( int* pidCostItem );
	virtual bool		HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType );
	virtual bool		HT_bGetMonsterSkillidReqItem( int* pidReqItem );
	virtual bool		HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel );
	virtual bool		HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti );
	virtual bool		HT_bGetMonsterSkillReqTribe( int* piReqTribe );
	virtual bool		HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 );
	virtual bool		HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 );
	virtual bool		HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );
	virtual bool		HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 );
	virtual bool		HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 );
	virtual bool		HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 );
	virtual bool		HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 );
	virtual bool		HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 );
	virtual bool		HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 );
	virtual bool		HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 );
	virtual bool		HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 );

	// PC Skill Param with ID
	virtual bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	virtual bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	virtual bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	virtual bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
	virtual bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	virtual bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	virtual bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	virtual bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	virtual bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	virtual bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	virtual bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	virtual bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	virtual bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	virtual bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	virtual bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	virtual bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	virtual bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	virtual bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	virtual bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	virtual bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	virtual bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	virtual bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	virtual bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	virtual bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	virtual bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	virtual bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	virtual bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	virtual bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	virtual bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	virtual bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	virtual bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	virtual bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	virtual bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	virtual bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	virtual bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	virtual bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	virtual bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	virtual bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	virtual bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	virtual bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	virtual bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	virtual bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	virtual bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	virtual bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	virtual bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	virtual bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	virtual bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	virtual bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	virtual bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	virtual bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	virtual bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	virtual bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	virtual bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	virtual bool		HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	virtual bool		HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	virtual bool		HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	virtual bool		HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	virtual bool		HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	virtual bool		HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	virtual bool		HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	virtual bool		HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );

	// PC Skill Param without ID
	virtual bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	virtual bool		HT_bGetPCSkillType( byte* pbyteType );
	virtual bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	virtual bool		HT_bGetPCSkillDuration( int* piDuration );
	virtual bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	virtual bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	virtual bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	virtual bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	virtual bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	virtual bool		HT_bGetPCSkillRange( int* piRange );
	virtual bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	virtual bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	virtual bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	virtual bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	virtual bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	virtual bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	virtual bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	virtual bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	virtual bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	virtual bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	virtual bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	virtual bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	virtual bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	virtual bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	virtual bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	virtual bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	virtual bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	virtual bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	virtual bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	virtual bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	virtual bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	virtual bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	virtual bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	virtual bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	virtual bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	virtual bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	virtual bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	virtual bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	virtual bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	virtual bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	virtual bool		HT_bGetPCSkillCostTP( int* piCostTP );
	virtual bool		HT_bGetPCSkillCostHP( int* piCostHP );
	virtual bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	virtual bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	virtual bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	virtual bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	virtual bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	virtual bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	virtual bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	virtual bool		HT_bGetPCSkillReqClass( int* piReqClass );
	virtual bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	virtual bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	virtual bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );
	virtual bool		HT_bGetPCSkillReserve0( byte* pbyteReserve0 );
	virtual bool		HT_bGetPCSkillReserve1( byte* pbyteReserve1 );
	virtual bool		HT_bGetPCSkillReserve2( byte* pbyteReserve2 );
	virtual bool		HT_bGetPCSkillReserve3( byte* pbyteReserve3 );
	virtual bool		HT_bGetPCSkillReserve4( byte* pbyteReserve4 );
	virtual bool		HT_bGetPCSkillReserve5( byte* pbyteReserve5 );
	virtual bool		HT_bGetPCSkillReserve6( byte* pbyteReserve6 );
	virtual bool		HT_bGetPCSkillReserve7( byte* pbyteReserve7 );
	
	// Item with ID
	virtual bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	virtual bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	virtual bool		HT_bGetItemType( const int id, short* psType);
	virtual bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	virtual bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	virtual bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	virtual bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	virtual bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	virtual bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	virtual bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	virtual bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	virtual bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	virtual bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	virtual bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	virtual bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	virtual bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	virtual bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	virtual bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	virtual bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	virtual bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	virtual bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	virtual bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	virtual bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	virtual bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	virtual bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	virtual bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	virtual bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	virtual bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	virtual bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	virtual bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	virtual bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	virtual bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	virtual bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	virtual bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	virtual bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	virtual bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	virtual bool		HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget );
	virtual bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	virtual bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	virtual bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	virtual bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	virtual bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	virtual bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	virtual bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	virtual bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	virtual bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	virtual bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	virtual bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	virtual bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	virtual bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );	
	virtual bool		HT_bGetItemEventID( const int id, short* psEventID );
	virtual bool		HT_bGetItemCash( const int id, int* piCash );
	virtual bool		HT_bGetItemReserve1( const int id, byte* pbyteReserve1 );
	virtual bool		HT_bGetItemReserve2( const int id, byte* pbyteReserve2 );
	virtual bool		HT_bGetItemReserve3( const int id, byte* pbyteReserve3 );
	virtual bool		HT_bGetItemReserve4( const int id, byte* pbyteReserve4 );
	virtual bool		HT_bGetItemReserve5( const int id, byte* pbyteReserve5 );
	virtual bool		HT_bGetItemReserve6( const int id, byte* pbyteReserve6 );
	virtual bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	virtual bool		HT_bGetItemFXEffectID( const int id, int* pidFX );
	
	// Item without ID
	virtual bool		HT_bGetItemLevel( byte* pbyteLevel );
	virtual bool		HT_bGetItemClass( byte* pbyteClass );
	virtual bool		HT_bGetItemType( short* psType);
	virtual bool		HT_bGetItemRupiah( int* piRupiah );
	virtual bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	virtual bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	virtual bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	virtual bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	virtual bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	virtual bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	virtual bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	virtual bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	virtual bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	virtual bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	virtual bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	virtual bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	virtual bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	virtual bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	virtual bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	virtual bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	virtual bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	virtual bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	virtual bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	virtual bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	virtual bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	virtual bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	virtual bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	virtual bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	virtual bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	virtual bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	virtual bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	virtual bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	virtual bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	virtual bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	virtual bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	virtual bool		HT_bGetItemRange( byte* pbyteRange );
	virtual bool		HT_bGetItemAllowedTarget( int* piAllowedTarget );
	virtual bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	virtual bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	virtual bool		HT_bGetItemCostTP( int* piCostTP );
	virtual bool		HT_bGetItemCostHP( int* piCostHP );
	virtual bool		HT_bGetItemidCostItem( int* pidCostItem );
	virtual bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	virtual bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	virtual bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	virtual bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	virtual bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	virtual bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	virtual bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	virtual bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );	
	virtual bool		HT_bGetItemEventID( short* psEventID );
	virtual bool		HT_bGetItemCash( int* piCash );
	virtual bool		HT_bGetItemReserve1( byte* pbyteReserve1 );
	virtual bool		HT_bGetItemReserve2( byte* pbyteReserve2 );
	virtual bool		HT_bGetItemReserve3( byte* pbyteReserve3 );
	virtual bool		HT_bGetItemReserve4( byte* pbyteReserve4 );
	virtual bool		HT_bGetItemReserve5( byte* pbyteReserve5 );
	virtual bool		HT_bGetItemReserve6( byte* pbyteReserve6 );
	virtual bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	virtual bool		HT_bGetItemFXEffectID( int* pidFX );

	virtual bool		HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem );

	// NPC & Shop with ID
	virtual	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	virtual	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	virtual	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	virtual	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti );
	virtual	int			HT_iGetNPCSellingItemCount( const int id );
	virtual	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	// NPC & Shop without ID
	virtual	bool		HT_bGetNPCSize( byte* pbyteSize );
	virtual	bool		HT_bGetNPCZone( byte* pbyteZone );
	virtual	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	virtual	bool		HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti );
	virtual	int			HT_iGetNPCSellingItemCount();
	virtual	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

	// Portal
	virtual	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
	virtual	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
											short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	virtual	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPortal, DWORD* pdwFee );
	virtual	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPortal, DWORD* pdwLevel);

	virtual bool		HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel );
	
	// TaskQuest with ID
	virtual bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );
	
	virtual bool		HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	virtual	bool		HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	virtual	bool		HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	virtual bool		HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	virtual	bool		HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	virtual	bool		HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	virtual bool		HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	virtual	bool		HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	virtual	bool		HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	virtual	bool		HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	virtual	bool		HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	virtual	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);
	
	// TaskQuest without ID
	virtual bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	virtual bool		HT_bGetTaskSource1( /* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	virtual	bool		HT_bGetTaskSource2( /* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	virtual	bool		HT_bGetTaskSource3( /* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	virtual bool		HT_bGetTaskSource4( /* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	virtual	bool		HT_bGetTaskSource5( /* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	virtual	bool		HT_bGetTaskSource6( /* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	virtual bool		HT_bGetTaskReward1( /* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	virtual	bool		HT_bGetTaskReward2( /* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	virtual	bool		HT_bGetTaskReward3( /* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	virtual	bool		HT_bGetTaskReward4( /* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	virtual	bool		HT_bGetTaskReward5( /* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	virtual	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

protected:
//	CHTString			m_strTableName;
	unsigned int		m_nItems;

private:
};

class CHTMonsterParamTable : public CHTBaseParamTable
{
public:
	CHTMonsterParamTable();
	~CHTMonsterParamTable();

	//bool		HT_bGetIDLevelbyIndex( const int index, int* piID, byte* pbyteLevel );
	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	// Monster Param with ID
	bool		HT_bGetMonsterLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	bool		HT_bGetMonsterAI( const int id, int* piAI );
	bool		HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime );
	bool		HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 );
	bool		HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 );
	bool		HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 );
	bool		HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 );
	bool		HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond );
	bool		HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond );
	bool		HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount );
	bool		HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond );
	bool		HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond );
	bool		HT_bGetMonsterHelpCond( const int id, byte* pbyteHeloCond );
	bool		HT_bGetMonsterHelpCondCount( const int id, byte* pbyteHelpCondCount );
	bool		HT_bGetMonsterLinkCond( const int id, byte* pbyteLinkCond );
	bool		HT_bGetMonsterLinkCondCount( const int id, byte* pbyteLinkCondCount );
	bool		HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell );
	bool		HT_bGetMonsterCantDetect( const int id, int* piCantDetect );
	bool		HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti );
	bool		HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight );
	bool		HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight );
	bool		HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin );
	bool		HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax );
	bool		HT_bGetMonsterMovement( const int id, byte* pbyteMovement );
	bool		HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate );
	bool		HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI );
	bool		HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo );
	bool		HT_bGetMonsterMuscle( const int id, short* psMuscle );
	bool		HT_bGetMonsterNerves( const int id, short* psNerves );
	bool		HT_bGetMonsterHeart( const int id, short* psHeart );
	bool		HT_bGetMonsterMind( const int id, short* psMind );
	bool		HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetMonsterHP( const int id, unsigned int* pnHP );
	bool		HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery );
	bool		HT_bGetMonsterAttackRate( const int id, int* piAttackRate );
	bool		HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate );
	//bool		HT_bGetMonsterBlockRate( const int id, byte* pbyteBlockRate );
	//bool		HT_bGetMonsterCriticalRate( const int id, byte* pbyteCriticalRate );
	bool		HT_bGetMonsterAC( const int id, int* piAC );
	bool		HT_bGetMonsterFireResist( const int id, int* piFireResist );
	bool		HT_bGetMonsterColdResist( const int id, int* piColdResist );
	bool		HT_bGetMonsterLightningResist( const int id, int* piLightningResist );
	bool		HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist );
	bool		HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed );
	bool		HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed );
	bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	bool		HT_bGetMonsterSkill0( const int id, int* pidSkill0 );
	bool		HT_bGetMonsterSkill1( const int id, int* pidSkill1 );
	bool		HT_bGetMonsterSkill2( const int id, int* pidSkill2 );
	bool		HT_bGetMonsterSkill3( const int id, int* pidSkill3 );
	bool		HT_bGetMonsterSkill4( const int id, int* pidSkill4 );
	bool		HT_bGetMonsterSkill5( const int id, int* pidSkill5 );
	bool		HT_bGetMonsterSkill6( const int id, int* pidSkill6 );
	bool		HT_bGetMonsterSkill7( const int id, int* pidSkill7 );
	bool		HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 );
	bool		HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 );
	bool		HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 );
	bool		HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 );
	bool		HT_bGetMonsterImmunity( const int id, int* piImmunity );
	bool		HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst );
	bool		HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint );
	bool		HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold );
	bool		HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana );
	bool		HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID );
	bool		HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate );
	bool		HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID );
	bool		HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate );
	bool		HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID );
	bool		HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate );
	bool		HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID );
	bool		HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate );
	bool		HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID );
	bool		HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate );
	bool		HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID );
	bool		HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate );
	bool		HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID );
	bool		HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate );
	bool		HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID );
	bool		HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate );
	bool		HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade );
	bool		HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate );
	//bool		HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount );
	bool		HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade );
	bool		HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate );
	//bool		HT_bGetMonsterItem9DeadCount( const int id, unsigned int* pnItem9DeadCount );
	bool		HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 );
	bool		HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 );
	bool		HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 );
	bool		HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 );
	bool		HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 );
	bool		HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 );
	bool		HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 );
	bool		HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7 );

	// Monster Param with No ID
	bool		HT_bGetMonsterLevel( byte* pbyteLevel );
	bool		HT_bGetMonsterClass( byte* pbyteClass );
	bool		HT_bGetMonsterSize( byte* pbyteSize );
	bool		HT_bGetMonsterAI( int* piAI );
	bool		HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime );
	bool		HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 );
	bool		HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 );
	bool		HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 );
	bool		HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 );
	bool		HT_bGetMonsterAggrCond( byte* pbyteAggrCond );
	bool		HT_bGetMonsterFleeCond( byte* pbyteFleeCond );
	bool		HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount );
	bool		HT_bGetMonsterTraceCond( byte* pbyteTraceCond );
	bool		HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond );
	bool		HT_bGetMonsterHelpCond( byte* pbyteHelpCond );
	bool		HT_bGetMonsterHelpCondCount( byte* pbyteHelpCondCount );
	bool		HT_bGetMonsterLinkCond( byte* pbyteLinkCond );
	bool		HT_bGetMonsterLinkCondCount( byte* pbyteLinkCondCount );
	bool		HT_bGetMonsterBlockedCell( int* piBlockedCell );
	bool		HT_bGetMonsterCantDetect( int* piCantDetect );
	bool		HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti );
	bool		HT_bGetMonsterNormalSight( byte* pbyteNormalSight );
	bool		HT_bGetMonsterCombatSight( byte* pbyteCombatSight );
	bool		HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin );
	bool		HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax );
	bool		HT_bGetMonsterMovement( byte* pbyteMovement );
	bool		HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate );
	bool		HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI );
	bool		HT_bGetMonsterEventNo( unsigned int* pnEventNo );
	bool		HT_bGetMonsterMuscle( short* psMuscle );
	bool		HT_bGetMonsterNerves( short* psNerves );
	bool		HT_bGetMonsterHeart( short* psHeart );
	bool		HT_bGetMonsterMind( short* psMind );
	bool		HT_bGetMonsterArmorType( byte* pbyteArmorType );
	bool		HT_bGetMonsterHP( unsigned int* pnHP );
	bool		HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery );
	bool		HT_bGetMonsterAttackRate( int* piAttackRate );
	bool		HT_bGetMonsterDodgeRate( int* piDodgeRate );
	//bool		HT_bGetMonsterBlockRate( byte* pbyteBlockRate );
	//bool		HT_bGetMonsterCriticalRate( byte* pbyteCriticalRate );
	bool		HT_bGetMonsterAC( int* piAC );
	bool		HT_bGetMonsterFireResist( int* piFireResist );
	bool		HT_bGetMonsterColdResist( int* piColdResist );
	bool		HT_bGetMonsterLightningResist( int* piLightningResist );
	bool		HT_bGetMonsterPoisonResist( int* piPoisonResist );
	bool		HT_bGetMonsterWalkSpeed( int* piWalkSpeed );
	bool		HT_bGetMonsterRunSpeed( int* piRunSpeed );
	bool		HT_bGetMonsterFly( byte* pbFly );
	bool		HT_bGetMonsterSkill0( int* pidSkill0 );
	bool		HT_bGetMonsterSkill1( int* pidSkill1 );
	bool		HT_bGetMonsterSkill2( int* pidSkill2 );
	bool		HT_bGetMonsterSkill3( int* pidSkill3 );
	bool		HT_bGetMonsterSkill4( int* pidSkill4 );
	bool		HT_bGetMonsterSkill5( int* pidSkill5 );
	bool		HT_bGetMonsterSkill6( int* pidSkill6 );
	bool		HT_bGetMonsterSkill7( int* pidSkill7 );
	bool		HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 );
	bool		HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 );
	bool		HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 );
	bool		HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 );
	bool		HT_bGetMonsterImmunity( int* piImmunity );
	bool		HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst );
	bool		HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint );
	bool		HT_bGetMonsterRewardGold( unsigned int* pnRewardGold );
	bool		HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana );
	bool		HT_bGetMonsterItem0ItemID( short* psItem0ID );
	bool		HT_bGetMonsterItem0DropRate( short* psItem0DropRate );
	bool		HT_bGetMonsterItem1ItemID( short* psItem1ID );
	bool		HT_bGetMonsterItem1DropRate( short* psItem1DropRate );
	bool		HT_bGetMonsterItem2ItemID( short* psItem2ID );
	bool		HT_bGetMonsterItem2DropRate( short* psItem2DropRate );
	bool		HT_bGetMonsterItem3ItemID( short* psItem3ID );
	bool		HT_bGetMonsterItem3DropRate( short* psItem3DropRate );
	bool		HT_bGetMonsterItem4ItemID( short* psItem4ID );
	bool		HT_bGetMonsterItem4DropRate( short* psItem4DropRate );
	bool		HT_bGetMonsterItem5ItemID( short* psItem5ID );
	bool		HT_bGetMonsterItem5DropRate( short* psItem5DropRate );
	bool		HT_bGetMonsterItem6ItemID( short* psItem6ID );
	bool		HT_bGetMonsterItem6DropRate( short* psItem6DropRate );
	bool		HT_bGetMonsterItem7ItemID( short* psItem7ID );
	bool		HT_bGetMonsterItem7DropRate( short* psItem7DropRate );
	bool		HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade );
	bool		HT_bGetMonsterItem8DropRate( short* psItem8DropRate );
	//bool		HT_bGetMonsterItem8DeadCount( unsigned int* pnItem8DeadCount );
	bool		HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade );
	bool		HT_bGetMonsterItem9DropRate( short* psItem9DropRate );
	//bool		HT_bGetMonsterItem9DeadCount( unsigned int* pnItem9DeadCount );
	bool		HT_bGetMonsterReserve0( byte* pbyteReserve0 );
	bool		HT_bGetMonsterReserve1( byte* pbyteReserve1 );
	bool		HT_bGetMonsterReserve2( byte* pbyteReserve2 );
	bool		HT_bGetMonsterReserve3( byte* pbyteReserve3 );
	bool		HT_bGetMonsterReserve4( byte* pbyteReserve4 );
	bool		HT_bGetMonsterReserve5( byte* pbyteReserve5 );
	bool		HT_bGetMonsterReserve6( byte* pbyteReserve6 );
	bool		HT_bGetMonsterReserve7( byte* pbyteReserve7 );

private:
	struct HTMonsterParam
	{
		byte			byteLevel;
		byte			byteClass;
		byte			byteSize;
		int				iAI;
		byte			byteSelectTargetTime;
		byte			byteSelectTarget0;
		byte			byteSelectTarget1;
		byte			byteSelectTarget2;
		byte			byteSelectTarget3;
		byte			byteAggrCond;
		byte			byteFleeCond;
		byte			byteFleeCondCount;
		byte			byteTraceCond;
		byte			byteStepBackCond;
		byte			byteHelpCond;
		byte			byteHelpCondCount;
		byte			byteLinkCond;
		byte			byteLinkCondCount;
		int				iBlockedCell;
		int				iCantDetect;
		byte			byteTrimuriti;
		byte			byteNormalSight;
		byte			byteCombatSight;
		unsigned int	nPopDelayMin;
		unsigned int	nPopDelayMax;
		byte			byteMovement;
		byte			byteSpeechRate;
		byte			byteSpeechAI;
		unsigned int	nEventNo;
		short			sMuscle;
		short			sNerves;
		short			sHeart;
		short			sMind;
		byte			byteArmorType;
		unsigned int	nHP;
		byte			byteHPRecovery;
		int				iAttackRate;
		int				iDodgeRate;
		//byte			byteBlockRate;
		//byte			byteCriticalRate;
		int				iAC;
		int				iFireResist;
		int				iColdResist;
		int				iLightningResist;
		int				iPoisonResist;
		int				iWalkSpeed;
		int				iRunSpeed;
		byte			bFly;
		int				idSkill0;
		int				idSkill1;
		int				idSkill2;
		int				idSkill3;
		int				idSkill4;
		int				idSkill5;
		int				idSkill6;
		int				idSkill7;
		byte			byteSkillPattern0;
		byte			byteSkillPattern1;
		byte			byteSkillPattern2;
		byte			byteSkillPattern3;
		int				iImmunity;
		byte			byteResistEffectConst;
		unsigned int	nRewardBrahmanPoint;
		unsigned int	nRewardGold;
		unsigned int	nRewardPrana;
		short			sItem0ID;
		short			sItem0DropRate;
		short			sItem1ID;
		short			sItem1DropRate;
		short			sItem2ID;
		short			sItem2DropRate;
		short			sItem3ID;
		short			sItem3DropRate;
		short			sItem4ID;
		short			sItem4DropRate;
		short			sItem5ID;
		short			sItem5DropRate;
		short			sItem6ID;
		short			sItem6DropRate;
		short			sItem7ID;
		short			sItem7DropRate;
		byte			byteItem8Grade;
		short			sItem8DropRate;
		//unsigned int	nItem8DeadCount;
		byte			byteItem9Grade;
		short			sItem9DropRate;
		//unsigned int	nItem9DeadCount; 
		byte			byteReserve0;
		byte			byteReserve1;
		byte			byteReserve2;
		byte			byteReserve3;
		byte			byteReserve4;
		byte			byteReserve5;
		byte			byteReserve6;
		byte			byteReserve7;
	};

	typedef std::map<int,HTMonsterParam*>				HTMonsterParam_Map;
	typedef std::map<int,HTMonsterParam*>::value_type	HTMonsterParam_Value;
	typedef std::map<int,HTMonsterParam*>::iterator		HTMonsterParam_It;

	HTMonsterParam*		m_pParam;
	HTMonsterParam_Map	m_mapTable;
};

class CHTMonsterSkillParamTable : public CHTBaseParamTable
{
public:
	CHTMonsterSkillParamTable();
	~CHTMonsterSkillParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	// Skill Param with ID
	bool		HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent );
	bool		HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration );
	bool		HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag );
	bool		HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime );
	bool		HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount );
	bool		HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	bool		HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	bool		HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	bool		HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	bool		HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	bool		HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	bool		HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	bool		HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );

	// Skill Param without ID
	bool		HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetMonsterSkillType( byte* pbyteType );
	bool		HT_bGetMonsterSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetMonsterSkillSpeechContent( short* psSpeechContent );
	bool		HT_bGetMonsterSkillDuration( int* piDuration );
	bool		HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag );
	bool		HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetMonsterSkillRange( int* piRange );
	bool		HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetMonsterSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );
	bool		HT_bGetMonsterSkillActivateTime( int* piActivateTime );
	bool		HT_bGetMonsterSkillCastCount( byte* pbyteCastCount );
	bool		HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetMonsterSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetMonsterSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetMonsterSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetMonsterSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetMonsterSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetMonsterSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetMonsterSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetMonsterSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetMonsterSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetMonsterSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetMonsterSkillCostTP( int* piCostTP );
	bool		HT_bGetMonsterSkillCostHP( int* piCostHP );
	bool		HT_bGetMonsterSkillidCostItem( int* pidCostItem );
	bool		HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetMonsterSkillidReqItem( int* pidReqItem );
	bool		HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetMonsterSkillReqTribe( int* piReqTribe );
	bool		HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl ); 
	bool		HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 );
	bool		HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 );
	bool		HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 );
	bool		HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 );
	bool		HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 );
	bool		HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 );
	bool		HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 );
	bool		HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 );
	
private:
	struct HTMonsterSkillParam
	{
//		byte			byteLevel;
		byte			byteMaxLevel;
		byte			byteType;
		short			sCombatPhase;
		short			sSpeechContent;
		byte			byteSuccessRate;
		byte			byteSyncFlag;
		int				iDuration; 
		int				iCoolDownTime;
		int				iRange;
		int				iAreaOfEffect;
		int				iAllowedTarget;
		byte			byteAttackType;
		int				iCastingTime;
		int				iActivateTime;
		byte			byteCastCount;
		byte			byteCastingSuccessRate;
		byte			byteFollowRange;
		byte			bytePierceRate;
		int				iEffect1ID;
		int				iEffect1Function;
		int				iEffect1Duration;
		int				iEffect1Param1;
		int				iEffect1Param2;
		int				iEffect2ID;
		int				iEffect2Function;
		int				iEffect2Duration;
		int				iEffect2Param1;
		int				iEffect2Param2;
		int				iEffect3ID;
		int				iEffect3Function;
		int				iEffect3Duration;
		int				iEffect3Param1;
		int				iEffect3Param2;
		int				iEffect4ID;
		int				iEffect4Function;
		int				iEffect4Duration;
		int				iEffect4Param1;
		int				iEffect4Param2;
		int				iEffect5ID;
		int				iEffect5Function;
		int				iEffect5Duration;
		int				iEffect5Param1;
		int				iEffect5Param2;
		int				iCostTP;
		int				iCostHP;
		int				idCostItem;
		int				iReqTrimuriti;			
		int				iReqTribe;
		int				iReqWeaponType;
		int				idReqItem;
		byte			byteReqLevel;
		int				idReqSkill1;				
		byte			byteReqSkill1_Lvl;		
		int				idReqSkill2;				
		byte			byteReqSkill2_Lvl;
		byte			byteReserve0;
		byte			byteReserve1;
		byte			byteReserve2;
		byte			byteReserve3;
		byte			byteReserve4;
		byte			byteReserve5;
		byte			byteReserve6;
		byte			byteReserve7;
	};

	typedef std::map<int,HTMonsterSkillParam*>				HTMonsterSkillParam_Map;
	typedef std::map<int,HTMonsterSkillParam*>::value_type	HTMonsterSkillParam_Value;
	typedef std::map<int,HTMonsterSkillParam*>::iterator	HTMonsterSkillParam_It;

	HTMonsterSkillParam*	m_pParam;
	HTMonsterSkillParam_Map	m_arrmapTable[HT_PCSKILL_MAXLEVEL];	// Level별로 존재한다.
};

class CHTPCSkillParamTable : public CHTBaseParamTable
{
public:
	CHTPCSkillParamTable();
	~CHTPCSkillParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

#ifdef HT_NEED_NAME
	bool		HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName );
	bool		HT_bGetName( CHTString* pstrName );
#endif

	// PC Skill Param with ID
	bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
	bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	bool		HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	bool		HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	bool		HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	bool		HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	bool		HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	bool		HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	bool		HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );

	// PC Skill Param without ID
	bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( int* piDuration );
	bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( int* piCostTP );
	bool		HT_bGetPCSkillCostHP( int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl ); 
	bool		HT_bGetPCSkillReserve0( byte* pbyteReserve0 );
	bool		HT_bGetPCSkillReserve1( byte* pbyteReserve1 );
	bool		HT_bGetPCSkillReserve2( byte* pbyteReserve2 );
	bool		HT_bGetPCSkillReserve3( byte* pbyteReserve3 );
	bool		HT_bGetPCSkillReserve4( byte* pbyteReserve4 );
	bool		HT_bGetPCSkillReserve5( byte* pbyteReserve5 );
	bool		HT_bGetPCSkillReserve6( byte* pbyteReserve6 );
	bool		HT_bGetPCSkillReserve7( byte* pbyteReserve7 );
	
private:
	struct HTPCSkillParam
	{
#ifdef HT_NEED_NAME
		char			szName[HT_NAME_MAX];
#endif
//		byte			byteLevel;
		byte			byteMaxLevel;
		byte			byteType;
		short			sCombatPhase;
		byte			byteSuccessRate;
		int				iDuration;
		int				iCoolDownTime;
		int				iRange;
		int				iAreaOfEffect;
		int				iAllowedTarget;
		byte			byteAttackType;
		int				iReadyTime;
		int				iCastingTime;
		int				iApplyTime;
		byte			byteCastingSuccessRate;
		byte			byteFollowRange;
		byte			bytePierceRate;
		int				iEffect1ID;
		int				iEffect1Function;
		int				iEffect1Duration;
		int				iEffect1Param1;
		int				iEffect1Param2;
		int				iEffect2ID;
		int				iEffect2Function;
		int				iEffect2Duration;
		int				iEffect2Param1;
		int				iEffect2Param2;
		int				iEffect3ID;
		int				iEffect3Function;
		int				iEffect3Duration;
		int				iEffect3Param1;
		int				iEffect3Param2;
		int				iEffect4ID;
		int				iEffect4Function;
		int				iEffect4Duration;
		int				iEffect4Param1;
		int				iEffect4Param2;
		int				iEffect5ID;
		int				iEffect5Function;
		int				iEffect5Duration;
		int				iEffect5Param1;
		int				iEffect5Param2;
		int				iCostTP;
		int				iCostHP;
		int				idCostItem;
		byte			byteCostItemCount;
		int				iReqTrimuriti;			
		int				iReqTribe;
		int				iReqClass;
		int				iReqWeaponType;
		int				idReqItem;
		byte			byteReqLevel;
		int				idReqSkill1;				
		byte			byteReqSkill1_Lvl;		
		int				idReqSkill2;				
		byte			byteReqSkill2_Lvl;
		byte			byteReserve0;
		byte			byteReserve1;
		byte			byteReserve2;
		byte			byteReserve3;
		byte			byteReserve4;
		byte			byteReserve5;
		byte			byteReserve6;
		byte			byteReserve7;
	};

	typedef std::map<int,HTPCSkillParam*>				HTPCSkillParam_Map;
	typedef std::map<int,HTPCSkillParam*>::value_type	HTPCSkillParam_Value;
	typedef std::map<int,HTPCSkillParam*>::iterator	HTPCSkillParam_It;

	HTPCSkillParam*		m_pParam;
	HTPCSkillParam_Map	m_arrmapTable[HT_PCSKILL_MAXLEVEL];	// Level별로 존재한다.
};

class CHTItemParamTable : public CHTBaseParamTable
{
public:
	CHTItemParamTable();
	~CHTItemParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

public:

#ifdef HT_NEED_NAME
	bool		HT_bGetName( const int id, CHTString* pstrName );
	bool		HT_bGetName( CHTString* pstrName );
#endif

    // Item with ID
	bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	bool		HT_bGetItemType( const int id, short* psType);
	bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	bool		HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget );
	bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );	
	bool		HT_bGetItemEventID( const int id, short* psEventID );
	bool		HT_bGetItemCash( const int id, int* piCash );
	bool		HT_bGetItemReserve1( const int id, byte* pbyteReserve1 );
	bool		HT_bGetItemReserve2( const int id, byte* pbyteReserve2 );
	bool		HT_bGetItemReserve3( const int id, byte* pbyteReserve3 );
	bool		HT_bGetItemReserve4( const int id, byte* pbyteReserve4 );
	bool		HT_bGetItemReserve5( const int id, byte* pbyteReserve5 );
	bool		HT_bGetItemReserve6( const int id, byte* pbyteReserve6 );
	bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	bool		HT_bGetItemFXEffectID( const int id, int* pidFX );
	
	// Item without ID
	bool		HT_bGetItemLevel( byte* pbyteLevel );
	bool		HT_bGetItemClass( byte* pbyteClass );
	bool		HT_bGetItemType( short* psType);
	bool		HT_bGetItemRupiah( int* piRupiah );
	bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetItemRange( byte* pbyteRange );
	bool		HT_bGetItemAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( int* piCostTP );
	bool		HT_bGetItemCostHP( int* piCostHP );
	bool		HT_bGetItemidCostItem( int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );	
	bool		HT_bGetItemEventID( short* psEventID );
	bool		HT_bGetItemCash( int* piCash );
	bool		HT_bGetItemReserve1( byte* pbyteReserve1 );
	bool		HT_bGetItemReserve2( byte* pbyteReserve2 );
	bool		HT_bGetItemReserve3( byte* pbyteReserve3 );
	bool		HT_bGetItemReserve4( byte* pbyteReserve4 );
	bool		HT_bGetItemReserve5( byte* pbyteReserve5 );
	bool		HT_bGetItemReserve6( byte* pbyteReserve6 );
	bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	bool		HT_bGetItemFXEffectID( int* pidFX );
	
	bool		HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem );

private:
	struct HTItemParam
	{
#ifdef HT_NEED_NAME
		char			szName[HT_NAME_MAX];
#endif
		byte	byteLevel;
		byte	byteClass;
		short	sType;
		int		iRupiah;
		int		iSellRupiah;
		short	sMaxDurability;
		byte	byteMaxCount;
		short	sCombatPhase;
		short	sSkillCastingTimeRate;
		int		iEffect1ID;
		int		iEffect1Function;
		int		iEffect1Duration;
		int		iEffect1Param1;
		int		iEffect1Param2;
		int		iEffect2ID;
		int		iEffect2Function;
		int		iEffect2Duration;
		int		iEffect2Param1;
		int		iEffect2Param2;
		int		iEffect3ID;
		int		iEffect3Function;
		int		iEffect3Duration;
		int		iEffect3Param1;
		int		iEffect3Param2;
		int		iEffect4ID;
		int		iEffect4Function;
		int		iEffect4Duration;
		int		iEffect4Param1;
		int		iEffect4Param2;
		int		iEffect5ID;
		int		iEffect5Function;
		int		iEffect5Duration;
		int		iEffect5Param1;
		int		iEffect5Param2;
		int		iCoolDownTime;
		byte	byteRange;
		int		iAllowedTarget;
		byte	byteArmorType;
		byte	byteAttackType;
		int		iCostTP;
		int		iCostHP;
		int		idCostItem;
		int		iLimitTrimuriti;
		int		iLimitTribe;
		byte	byteLimitLevel;
		short	sLimitMusclechakra;
		short	sLimitNerveChakra;
		short	sLimitHeartChakra;
		short	sLimitSoulChakra;
		int		iRefinableItemType;
		short	sEventID;
		int		iCash;
		byte	byteReserve1;
		byte	byteReserve2;
		byte	byteReserve3;
		byte	byteReserve4;
		byte	byteReserve5;
		byte	byteReserve6;
		short	sTimeLimit;
		int		idFX;
	};

	typedef std::map<int,HTItemParam*>				HTItemParam_Map;
	typedef std::map<int,HTItemParam*>::value_type	HTItemParam_Value;
	typedef std::map<int,HTItemParam*>::iterator	HTItemParam_It;

	//
	typedef std::vector<int>				HTItemID_Vector;
	typedef std::vector<int>::value_type	HTItemID_Value;
	typedef std::vector<int>::iterator		HTItemID_It;

	HTItemParam_Map				m_mapTable;
	HTItemParam*				m_pParam;

	HTItemID_Vector				m_arrvecItemID[HT_ITEMLEVEL_MAX];
};

class CHTNPCParamTable : public CHTBaseParamTable
{
public :
	CHTNPCParamTable();
	~CHTNPCParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount( const int id );
	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	bool		HT_bGetNPCSize( byte* pbyteSize );
	bool		HT_bGetNPCZone( byte* pbyteZone );
	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount();
	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

private:
	struct HTNPCParam
	{
		byte	byteSize;
		byte	byteZone;
		short	sPosX;
		short	sPosZ;
		int		iNumItem;
		int		arridItem[HT_NPC_SELLING_ITEM_MAX];
		byte	byteNPCTrimuriti;
	};

	typedef std::map<int,HTNPCParam*>				HTNPCParam_Map;
	typedef std::map<int,HTNPCParam*>::value_type	HTNPCParam_Value;
	typedef std::map<int,HTNPCParam*>::iterator		HTNPCParam_It;

	HTNPCParam_Map	m_mapTable;
	HTNPCParam*		m_pParam;
};

class CHTPortalParamTable : public CHTBaseParamTable
{
public:
	CHTPortalParamTable();
	~CHTPortalParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bLockID( const int id, const byte iLevel = 0 ) { return false; }
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 ) { return false; }

	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
//#ifdef HT_NEED_NAME	
//	bool		HT_bGetName( const int id, CHTString* pstrName );
//#endif
	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
									short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee );
	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel);
	bool		HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel );

private:
	struct HTPortalParam
	{
//#ifdef HT_NEED_NAME
//		char  		szName[HT_NAME_MAX];
//#endif
		DWORD		dwServerID;
		DWORD		dwZoneLevel;

		short		sStartX;
		short		sStartZ;
		short		sEndX;
		short		sEndZ;

		int			iGoPortal[5];
		DWORD		dwFee[5];
		DWORD		dwLevel[5];
	};

	typedef std::map<DWORD,HTPortalParam*>				HTPortalParam_Map;
	typedef std::map<DWORD,HTPortalParam*>::value_type	HTPortalParam_Value;
	typedef std::map<DWORD,HTPortalParam*>::iterator		HTPortalParam_It;

	HTPortalParam_Map	m_mapTable;
	HTPortalParam*		m_pParam;
};

class CHTTaskQuestParamTable : public CHTBaseParamTable
{
public:
	CHTTaskQuestParamTable();
	~CHTTaskQuestParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );
	// with ID
	bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// without ID
	bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( /* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( /* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( /* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( /* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( /* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( /* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( /* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( /* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( /* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( /* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( /* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

private:
	struct HTTaskQuestParam
	{
		short		sNPCID1;
		short		sNPCID2;
		short		sNPCID3;
		short		sNPCID4;
		short		sNPCID5;

		byte		byteSourceType1;
		short		sSourceItemID1;
		int			iSourceCount1;
		byte		byteSourceType2;
		short		sSourceItemID2;
		int			iSourceCount2;
		byte		byteSourceType3;
		short		sSourceItemID3;
		int			iSourceCount3;
		byte		byteSourceType4;
		short		sSourceItemID4;
		int			iSourceCount4;
		byte		byteSourceType5;
		short		sSourceItemID5;
		int			iSourceCount5;
		byte		byteSourceType6;
		short		sSourceItemID6;
		int			iSourceCount6;

		byte		byteRewardPriority1;
		byte		byteRewardType1;
		short		sReward1Rate;
		short		sRewardItemID1;
		int			iRewardCount1;
		byte		byteRewardPriority2;
		byte		byteRewardType2;
		short		sReward2Rate;
		short		sRewardItemID2;
		int			iRewardCount2;
		byte		byteRewardPriority3;
		byte		byteRewardType3;
		short		sReward3Rate;
		short		sRewardItemID3;
		int			iRewardCount3;
		byte		byteRewardPriority4;
		byte		byteRewardType4;
		short		sReward4Rate;
		short		sRewardItemID4;
		int			iRewardCount4;
		byte		byteRewardPriority5;
		byte		byteRewardType5;
		short		sReward5Rate;
		short		sRewardItemID5;
		int			iRewardCount5;

		byte		byteMinLevel;			// 2005. 1. 5 선영범
		byte		byteMaxLevel;
	};

	typedef std::map<DWORD,HTTaskQuestParam*>				HTTaskQuestParam_Map;
	typedef std::map<DWORD,HTTaskQuestParam*>::value_type	HTTaskQuestParam_Value;
	typedef std::map<DWORD,HTTaskQuestParam*>::iterator		HTTaskQuestParam_It;

	HTTaskQuestParam_Map	m_mapTable;
	HTTaskQuestParam*		m_pParam;
};

class CHTParameterMgr
{
public:
	CHTParameterMgr();
	~CHTParameterMgr();

	bool		HT_bGetAllID( int iType, std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTString& strFile );
	bool		HT_bLoadXML( CHTString& strFile );
	bool		HT_bSave( CHTString& strFile );

	// for test
	bool		HT_bTestSave( CHTString& strFile );

	// 언어 설정
	void		HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }
private:
	void		HT_vTestMonsterParamWithID( FILE* pFile, const int id );
	void		HT_vTestMonsterParam( FILE* pFile );

	void		HT_vTestMonsterSkillParamWithID( FILE* pFile, const int id, const byte byteLevel );
	void		HT_vTestMonsterSkillParam( FILE* pFile );

	void		HT_vTestPCSkillParamWithID( FILE* pFile, const int id, const byte byteLevel );
	void		HT_vTestPCSkillParam( FILE* pFile );

	void		HT_vTestItemParamWithID( FILE* pFile, const int id );
	void		HT_vTestItemParam( FILE* pFile );

	void		HT_vTestNPCParamWithID( FILE* pFile, const int id );
	void		HT_vTestNPCParam( FILE* pFile );

	void		HT_vTestPortalParam( FILE* pFile, const int id );

	void		HT_vTestTaskQuestParamWithID( FILE* pFile, const int id );
	void		HT_vTestTaskQuestParam( FILE* pFile );                     

public:

#ifdef HT_NEED_NAME
	bool		HT_bGetName( const int id, CHTString* pstrName );
	bool		HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName );
	bool		HT_bGetName( CHTString* pstrName );
#endif
	// Monster Param with ID
	bool		HT_bGetMonsterLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	bool		HT_bGetMonsterAI( const int id, int* piAI );
	bool		HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime );
	bool		HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 );
	bool		HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 );
	bool		HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 );
	bool		HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 );
	bool		HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond );
	bool		HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond );
	bool		HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount );
	bool		HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond );
	bool		HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond );
	bool		HT_bGetMonsterHelpCond( const int id, byte* pbyteHelpCond );
	bool		HT_bGetMonsterHelpCondCount( const int id, byte* pbyteHelpCondCount );
	bool		HT_bGetMonsterLinkCond( const int id, byte* pbyteLinkCond );
	bool		HT_bGetMonsterLinkCondCount( const int id, byte* pbyteLinkCondCount );
	bool		HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell );
	bool		HT_bGetMonsterCantDetect( const int id, int* piCantDetect );
	bool		HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti );
	bool		HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight );
	bool		HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight );
	bool		HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin );
	bool		HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax );
	bool		HT_bGetMonsterMovement( const int id, byte* pbyteMovement );
	bool		HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate );
	bool		HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI );
	bool		HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo );
	bool		HT_bGetMonsterMuscle( const int id, short* psMuscle );
	bool		HT_bGetMonsterNerves( const int id, short* psNerves );
	bool		HT_bGetMonsterHeart( const int id, short* psHeart );
	bool		HT_bGetMonsterMind( const int id, short* psMind );
	bool		HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetMonsterHP( const int id, unsigned int* pnHP );
	bool		HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery );
	bool		HT_bGetMonsterAttackRate( const int id, int* piAttackRate );
	bool		HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate );
	//bool		HT_bGetMonsterBlockRate( const int id, byte* pbyteBlockRate );
	//bool		HT_bGetMonsterCriticalRate( const int id, byte* pbyteCriticalRate );
	bool		HT_bGetMonsterAC( const int id, int* piAC );
	bool		HT_bGetMonsterFireResist( const int id, int* piFireResist );
	bool		HT_bGetMonsterColdResist( const int id, int* piColdResist );
	bool		HT_bGetMonsterLightningResist( const int id, int* piLightningResist );
	bool		HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist );
	bool		HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed );
	bool		HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed );
	bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	bool		HT_bGetMonsterSkill0( const int id, int* pidSkill0 );
	bool		HT_bGetMonsterSkill1( const int id, int* pidSkill1 );
	bool		HT_bGetMonsterSkill2( const int id, int* pidSkill2 );
	bool		HT_bGetMonsterSkill3( const int id, int* pidSkill3 );
	bool		HT_bGetMonsterSkill4( const int id, int* pidSkill4 );
	bool		HT_bGetMonsterSkill5( const int id, int* pidSkill5 );
	bool		HT_bGetMonsterSkill6( const int id, int* pidSkill6 );
	bool		HT_bGetMonsterSkill7( const int id, int* pidSkill7 );
	bool		HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 );
	bool		HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 );
	bool		HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 );
	bool		HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 );
	bool		HT_bGetMonsterImmunity( const int id, int* piImmunity );
	bool		HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst );
	bool		HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint );
	bool		HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold );
	bool		HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana );
	bool		HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID );
	bool		HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate );
	bool		HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID );
	bool		HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate );
	bool		HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID );
	bool		HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate );
	bool		HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID );
	bool		HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate );
	bool		HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID );
	bool		HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate );
	bool		HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID );
	bool		HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate );
	bool		HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID );
	bool		HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate );
	bool		HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID );
	bool		HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate );
	bool		HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade );
	bool		HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate );
	//bool		HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount );
	bool		HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade );
	bool		HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate );
	//bool		HT_bGetMonsterItem9DeadCount( const int id, unsigned int* pnItem9DeadCount );
	bool		HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 );
	bool		HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 );
	bool		HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 );
	bool		HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 );
	bool		HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 );
	bool		HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 );
	bool		HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 );
	bool		HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7 );

	// Monster Param with No ID
	bool		HT_bGetMonsterLevel( byte* pbyteLevel );
	bool		HT_bGetMonsterClass( byte* pbyteClass );
	bool		HT_bGetMonsterSize( byte* pbyteSize );
	bool		HT_bGetMonsterAI( int* piAI );
	bool		HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime );
	bool		HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 );
	bool		HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 );
	bool		HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 );
	bool		HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 );
	bool		HT_bGetMonsterAggrCond( byte* pbyteAggrCond );
	bool		HT_bGetMonsterFleeCond( byte* pbyteFleeCond );
	bool		HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount );
	bool		HT_bGetMonsterTraceCond( byte* pbyteTraceCond );
	bool		HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond );
	bool		HT_bGetMonsterHelpCond( byte* pbyteHelpCond );
	bool		HT_bGetMonsterHelpCondCount( byte* pbyteHelpCondCount );
	bool		HT_bGetMonsterLinkCond( byte* pbyteLinkCond );
	bool		HT_bGetMonsterLinkCondCount( byte* pbyteLinkCondCount );
	bool		HT_bGetMonsterBlockedCell( int* piBlockedCell );
	bool		HT_bGetMonsterCantDetect( int* piCantDetect );
	bool		HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti );
	bool		HT_bGetMonsterNormalSight( byte* pbyteNormalSight );
	bool		HT_bGetMonsterCombatSight( byte* pbyteCombatSight );
	bool		HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin );
	bool		HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax );
	bool		HT_bGetMonsterMovement( byte* pbyteMovement );
	bool		HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate );
	bool		HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI );
	bool		HT_bGetMonsterEventNo( unsigned int* pnEventNo );
	bool		HT_bGetMonsterMuscle( short* psMuscle );
	bool		HT_bGetMonsterNerves( short* psNerves );
	bool		HT_bGetMonsterHeart( short* psHeart );
	bool		HT_bGetMonsterMind( short* psMind );
	bool		HT_bGetMonsterArmorType( byte* pbyteArmorType );
	bool		HT_bGetMonsterHP( unsigned int* pnHP );
	bool		HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery );
	bool		HT_bGetMonsterAttackRate( int* piAttackRate );
	bool		HT_bGetMonsterDodgeRate( int* piDodgeRate );
	//bool		HT_bGetMonsterBlockRate( byte* pbyteBlockRate );
	//bool		HT_bGetMonsterCriticalRate( byte* pbyteCriticalRate );
	bool		HT_bGetMonsterAC( int* piAC );
	bool		HT_bGetMonsterFireResist( int* piFireResist );
	bool		HT_bGetMonsterColdResist( int* piColdResist );
	bool		HT_bGetMonsterLightningResist( int* piLightningResist );
	bool		HT_bGetMonsterPoisonResist( int* piPoisonResist );
	bool		HT_bGetMonsterWalkSpeed( int* piWalkSpeed );
	bool		HT_bGetMonsterRunSpeed( int* piRunSpeed );
	bool		HT_bGetMonsterFly( byte* pbFly );
	bool		HT_bGetMonsterSkill0( int* pidSkill0 );
	bool		HT_bGetMonsterSkill1( int* pidSkill1 );
	bool		HT_bGetMonsterSkill2( int* pidSkill2 );
	bool		HT_bGetMonsterSkill3( int* pidSkill3 );
	bool		HT_bGetMonsterSkill4( int* pidSkill4 );
	bool		HT_bGetMonsterSkill5( int* pidSkill5 );
	bool		HT_bGetMonsterSkill6( int* pidSkill6 );
	bool		HT_bGetMonsterSkill7( int* pidSkill7 );
	bool		HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 );
	bool		HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 );
	bool		HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 );
	bool		HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 );
	bool		HT_bGetMonsterImmunity( int* piImmunity );
	bool		HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst );
	bool		HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint );
	bool		HT_bGetMonsterRewardGold( unsigned int* pnRewardGold );
	bool		HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana );
	bool		HT_bGetMonsterItem0ItemID( short* psItem0ID );
	bool		HT_bGetMonsterItem0DropRate( short* psItem0DropRate );
	bool		HT_bGetMonsterItem1ItemID( short* psItem1ID );
	bool		HT_bGetMonsterItem1DropRate( short* psItem1DropRate );
	bool		HT_bGetMonsterItem2ItemID( short* psItem2ID );
	bool		HT_bGetMonsterItem2DropRate( short* psItem2DropRate );
	bool		HT_bGetMonsterItem3ItemID( short* psItem3ID );
	bool		HT_bGetMonsterItem3DropRate( short* psItem3DropRate );
	bool		HT_bGetMonsterItem4ItemID( short* psItem4ID );
	bool		HT_bGetMonsterItem4DropRate( short* psItem4DropRate );
	bool		HT_bGetMonsterItem5ItemID( short* psItem5ID );
	bool		HT_bGetMonsterItem5DropRate( short* psItem5DropRate );
	bool		HT_bGetMonsterItem6ItemID( short* psItem6ID );
	bool		HT_bGetMonsterItem6DropRate( short* psItem6DropRate );
	bool		HT_bGetMonsterItem7ItemID( short* psItem7ID );
	bool		HT_bGetMonsterItem7DropRate( short* psItem7DropRate );
	bool		HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade );
	bool		HT_bGetMonsterItem8DropRate( short* psItem8DropRate );
	//bool		HT_bGetMonsterItem8DeadCount( unsigned int* pnItem8DeadCount );
	bool		HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade );
	bool		HT_bGetMonsterItem9DropRate( short* psItem9DropRate );
	//bool		HT_bGetMonsterItem9DeadCount( unsigned int* pnItem9DeadCount );
	bool		HT_bGetMonsterReserve0( byte* pbyteReserve0 );
	bool		HT_bGetMonsterReserve1( byte* pbyteReserve1 );
	bool		HT_bGetMonsterReserve2( byte* pbyteReserve2 );
	bool		HT_bGetMonsterReserve3( byte* pbyteReserve3 );
	bool		HT_bGetMonsterReserve4( byte* pbyteReserve4 );
	bool		HT_bGetMonsterReserve5( byte* pbyteReserve5 );
	bool		HT_bGetMonsterReserve6( byte* pbyteReserve6 );
	bool		HT_bGetMonsterReserve7( byte* pbyteReserve7 );

	// Monster Skill Param with ID
	bool		HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent );
	bool		HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration );
	bool		HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag );
	bool		HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime );
	bool		HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount );
	bool		HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	bool		HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	bool		HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	bool		HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	bool		HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	bool		HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	bool		HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	bool		HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );

	// Monster Skill Param without ID
	bool		HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetMonsterSkillType( byte* pbyteType );
	bool		HT_bGetMonsterSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetMonsterSkillSpeechContent( short* psSpeechContent );
	bool		HT_bGetMonsterSkillDuration( int* piDuration );
	bool		HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag );
	bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );
	bool		HT_bGetMonsterSkillActivateTime( int* piActivateTime );
	bool		HT_bGetMonsterSkillCastCount( byte* pbyteCastCount );
	bool		HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetMonsterSkillRange( int* piRange );
	bool		HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetMonsterSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetMonsterSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetMonsterSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetMonsterSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetMonsterSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetMonsterSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetMonsterSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetMonsterSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetMonsterSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetMonsterSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetMonsterSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetMonsterSkillCostTP( int* piCostTP );
	bool		HT_bGetMonsterSkillCostHP( int* piCostHP );
	bool		HT_bGetMonsterSkillidCostItem( int* pidCostItem );
	bool		HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetMonsterSkillidReqItem( int* pidReqItem );
	bool		HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetMonsterSkillReqTribe( int* piReqTribe );
	bool		HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 );
	bool		HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 );
	bool		HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 );
	bool		HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 );
	bool		HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 );
	bool		HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 );
	bool		HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 );
	bool		HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 );

	// PC Skill Param with ID
	bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
	bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 );
	bool		HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 );
	bool		HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 );
	bool		HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 );
	bool		HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 );
	bool		HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 );
	bool		HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 );
	bool		HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 );


	// PC Skill Param without ID
	bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( int* piDuration );
	bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( int* piCostTP );
	bool		HT_bGetPCSkillCostHP( int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );
	bool		HT_bGetPCSkillReserve0( byte* pbyteReserve0 );
	bool		HT_bGetPCSkillReserve1( byte* pbyteReserve1 );
	bool		HT_bGetPCSkillReserve2( byte* pbyteReserve2 );
	bool		HT_bGetPCSkillReserve3( byte* pbyteReserve3 );
	bool		HT_bGetPCSkillReserve4( byte* pbyteReserve4 );
	bool		HT_bGetPCSkillReserve5( byte* pbyteReserve5 );
	bool		HT_bGetPCSkillReserve6( byte* pbyteReserve6 );
	bool		HT_bGetPCSkillReserve7( byte* pbyteReserve7 );

	// Item with ID
	bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	bool		HT_bGetItemType( const int id, short* psType);
	bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	bool		HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget );
	bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );	
	bool		HT_bGetItemEventID( const int id, short* psEventID );
	bool		HT_bGetItemCash( const int id, int* piCash );
	bool		HT_bGetItemReserve1( const int id, byte* pbyteReserve1 );
	bool		HT_bGetItemReserve2( const int id, byte* pbyteReserve2 );
	bool		HT_bGetItemReserve3( const int id, byte* pbyteReserve3 );
	bool		HT_bGetItemReserve4( const int id, byte* pbyteReserve4 );
	bool		HT_bGetItemReserve5( const int id, byte* pbyteReserve5 );
	bool		HT_bGetItemReserve6( const int id, byte* pbyteReserve6 );
	bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	bool		HT_bGetItemFXEffectID( const int id, int* pidFX );
	
	// Item without ID
	bool		HT_bGetItemLevel( byte* pbyteLevel );
	bool		HT_bGetItemClass( byte* pbyteClass );
	bool		HT_bGetItemType( short* psType);
	bool		HT_bGetItemRupiah( int* piRupiah );
	bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetItemRange( byte* pbyteRange );
	bool		HT_bGetItemAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( int* piCostTP );
	bool		HT_bGetItemCostHP( int* piCostHP );
	bool		HT_bGetItemidCostItem( int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );	
	bool		HT_bGetItemEventID( short* psEventID );
	bool		HT_bGetItemCash( int* piCash );
	bool		HT_bGetItemReserve1( byte* pbyteReserve1 );
	bool		HT_bGetItemReserve2( byte* pbyteReserve2 );
	bool		HT_bGetItemReserve3( byte* pbyteReserve3 );
	bool		HT_bGetItemReserve4( byte* pbyteReserve4 );
	bool		HT_bGetItemReserve5( byte* pbyteReserve5 );
	bool		HT_bGetItemReserve6( byte* pbyteReserve6 );
	bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	bool		HT_bGetItemFXEffectID( int* pidFX );

	bool		HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem );

	// NPC & Shop with ID
	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount( const int id );
	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	// NPC & Shop without ID
	bool		HT_bGetNPCSize( byte* pbyteSize );
	bool		HT_bGetNPCZone( byte* pbyteZone );
	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount();
	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

	// Portal
	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
									short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPortal, DWORD* pdwFee );
	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPortal, DWORD* pdwLevel);
	
	bool		HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel );

	// TaskQuest with ID
	bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );
	
	bool		HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// without ID
	bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( /* short* psNPCID,*/byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( /* short* psNPCID,*/byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( /* short* psNPCID,*/byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( /* short* psNPCID,*/byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( /* short* psNPCID,*/byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( /* short* psNPCID,*/byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( /* short* psNPCID,*/byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( /* short* psNPCID,*/byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( /* short* psNPCID,*/byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( /* short* psNPCID,*/byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// Get ID & Level List
	int			HT_iGetAllCount( const int iType );
	bool		HT_bGetIDLevelByIndex( const int iType, const int index, int* pid, byte* pbyteLevel );

	int			HT_iGetPCSkillIDLevelCount( const int iCharType );
	bool		HT_bGetPCSkillIDLevel( const int iCharType, const int index, int* pid, byte* pbyteLevel );

	// Get ID List
	int			HT_iGetPCSkillIDCount( const int iCharType );
	bool		HT_bGetPCSkillIDByIndex( const int iCharType, const int index, int* pid );

	// Money
	int			HT_iGetIndexForMoneyItem( const unsigned long dwMoney );
private :
	CHTBaseParamTable*	HT_pGetParamTable( int id );

private:
	CHTBaseParamTable*	m_arrParamTable[HT_PARAMTYPE_END];
	CHTBaseParamTable*	m_pParamTable;

	std::vector<HTIDLevel> m_vectorItemIDLevel;

//	std::vector<HTIDLevel> m_vectorPCSkillIDLevel;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelNagKin;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelAsuRak;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelDevGar;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelYakGan;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelEtc;

	std::vector<int> m_vectorPCSkillIDNagKin;
	std::vector<int> m_vectorPCSkillIDAsuRak;
	std::vector<int> m_vectorPCSkillIDDevGar;
	std::vector<int> m_vectorPCSkillIDYakGan;

	std::vector<HTIDLevel> m_vectorNPCIDLevel;

	CHTString			m_szLanguage;
};

#endif	// #ifndef _HTPARAMMGR_H_
