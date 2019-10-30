#include "stdAfx.h"
#include "HTClientParamMgr.h"

#include "..\..\engine\HTUtilLib\HTFile.h"
#include "..\..\engine\HTUtilLib\HTXMLParser.h"
#include "Basedef.h"

//  언어
#define HT_LANGUAGE_KOREAN			_T("Korean")
#define HT_LANGUAGE_CHINESE			_T("Chinese")

bool
CHTParamIDCheck::HT_bIsMonster( const int id )
{
	if ( ( id >= HT_PARAMTYPE_MONSTER_START ) && ( id <= HT_PARAMTYPE_MONSTER_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsMonsterSkill( const int id )
{
	if ( ( id >= HT_PARAMTYPE_MONSTERSKILL_START ) && ( id <= HT_PARAMTYPE_MONSTERSKILL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkill( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_START ) && ( id <= HT_PARAMTYPE_PCSKILL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItem( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_START ) && ( id <= HT_PARAMTYPE_ITEM_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillNagaKin( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_NAGAKIN_START ) && ( id <= HT_PARAMTYPE_PCSKILL_NAGAKIN_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillNagaKin1st( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_START ) && ( id <= HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillNagaKin2nd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_START ) && ( id <= HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillNagaKin3rd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_START ) && ( id <= HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillAsuRak( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_ASURARAK_START ) && ( id <= HT_PARAMTYPE_PCSKILL_ASURARAK_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillAsuRak1st( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_START ) && ( id <= HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillAsuRak2nd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_START ) && ( id <= HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillAsuRak3rd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_START ) && ( id <= HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillYakGan( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_YAKGAN_START ) && ( id <= HT_PARAMTYPE_PCSKILL_YAKGAN_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillYakGan1st( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_START ) && ( id <= HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillYakGan2nd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_START ) && ( id <= HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillYakGan3rd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_START ) && ( id <= HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillDevGaru( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_DEVAGARU_START ) && ( id <= HT_PARAMTYPE_PCSKILL_DEVAGARU_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillDevGaru1st( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_START ) && ( id <= HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillDevGaru2nd( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_START ) && ( id <= HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsPCSkillDevGaru3rd( const int id )
{
	if ( id==3335) return true;
	if ( ( id >= HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_START ) && ( id <= HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRare( const int id )
{
	// Wepon - one hand
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_END ) ) return true;
	// Wepon - two hand
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_END ) ) return true;
	// Wepon - throw
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_END ) ) return true;
	// Defence
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_END ) ) return true;
	// Accessory
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_END ) ) return true;
	
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemUnique( const int id )
{
	// Wepon - one hand
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_END ) ) return true;
	// Wepon - two hand
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_END ) ) return true;
	// Wepon - throw
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_END ) ) return true;
	// Defence
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_END ) ) return true;
	// Accessory
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_END ) ) return true;

	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemQuest( const int id )
{
	// Wepon - one hand
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_END ) ) return true;
	// Wepon - two hand
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_END ) ) return true;
	// Wepon - throw
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_END ) ) return true;
	// Defence
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_END ) ) return true;
	// Accessory
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_END ) ) return true;
	// Quest Only
	else if ( ( id >= HT_PARAMTYPE_ITEM_QUESTONLY_START ) && ( id <= HT_PARAMTYPE_ITEM_QUESTONLY_END ) ) return true;

	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemMagic( const int id )
{
	// Wepon - one hand
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_END ) ) return true;
	// Wepon - two hand
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_END ) ) return true;
	else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_END ) ) return true;
	// Wepon - throw
	//else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_END ) ) return true;
	//else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_END ) ) return true;
	//else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_END ) ) return true;
	//else if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_END ) ) return true;

	else return false;
}


bool
CHTParamIDCheck::HT_bIsItemWeapon( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHand( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandNormalNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandNormalMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandRareNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandRareMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandUniqueNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandUniqueMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandQuestNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponOneHandQuestMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHand( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandNormalNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandNormalMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandRareNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandRareMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandUniqueNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandUniqueMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandQuestNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponTwoHandQuestMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrow( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowNormalNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowRareNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowUniqueNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowQuestNotMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_END ) ) return true;
	else return false;
}
/*
bool
CHTParamIDCheck::HT_bIsItemWeaponThrowNormalMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowRareMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowUniqueMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemWeaponThrowQuestMagic( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_START ) && ( id <= HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_END ) ) return true;
	else return false;
}
*/
bool
CHTParamIDCheck::HT_bIsItemDefence( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_END ) ||
		 ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmor( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_END )) || (( id == 8901) || (id ==8902)) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmorNormal( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmorRare( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmorUnique( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmorQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefencePants( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefencePantsNormal( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefencePantsRare( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefencePantsUnique( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefencePantsQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceGloves( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceGlovesNormal( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceGlovesRare( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceGlovesUnique( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceGlovesQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceHelmet( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceHelmetNormal( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceHelmetRare( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceHelmetUnique( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceHelmetQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceBelt( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceBeltNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceBeltRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceBeltUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceBeltQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShoes( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShoesNormal( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShoesRare( const int id )
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_END )) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_END )) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShoesUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_END ) ||
		 ( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShoesQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShield( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShieldNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShieldRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShieldUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceShieldQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemCharm( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_CHARM_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARM_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessory( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryEarring( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryEarringNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryEarringRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryEarringUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryEarringQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryBracelet( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryBraceletNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryBraceletRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryBraceletUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryBraceletQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryNecklace( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryNecklaceNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryNecklaceRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryNecklaceUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryNecklaceQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryExpandInvenQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryRing( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryRingNormal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryRingRare( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryRingUnique( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemAccessoryRingQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_START ) && ( id <= HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRefine( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_REFINE_START ) && ( id <= HT_PARAMTYPE_ITEM_REFINE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRefineMain( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_REFINE_MAIN_START ) && ( id <= HT_PARAMTYPE_ITEM_REFINE_MAIN_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRefineSub( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_REFINE_SUB_START ) && ( id <= HT_PARAMTYPE_ITEM_REFINE_SUB_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRefineSub2( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_REFINE_SUB2_START ) && ( id <= HT_PARAMTYPE_ITEM_REFINE_SUB2_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemRefineSub3( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_REFINE_SUB3_START ) && ( id <= HT_PARAMTYPE_ITEM_REFINE_SUB3_END ) ) return true;
	else return false;
}


bool
CHTParamIDCheck::HT_bIsItemCharge( const int id )
{
//	if ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_END ) ) return true;
//	else return false;
		if ( ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_END ) )
		|| ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_USABLE2_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_USABLE2_END ) )
		|| ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_USABLE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_USABLE_END ) )
		|| ( id == 6614 ) ) return true;	// 6614는 아말라다
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemChargeContinuance( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemChargeFunction( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemUsable( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_USABLE_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE_END ) ||
		 ( id >= HT_PARAMTYPE_ITEM_USABLE2_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE2_END )) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemUsableMoney( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_USABLE_MONEY_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE_MONEY_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemUsableArrow( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_USABLE_ARROW_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE_ARROW_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemCollect( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_COLLECT_START ) && ( id <= HT_PARAMTYPE_ITEM_COLLECT_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemQuestOnly( const int id )
{
	if ( ( id >= HT_PARAMTYPE_ITEM_QUESTONLY_START ) && ( id <= HT_PARAMTYPE_ITEM_QUESTONLY_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsNPC( const int id )
{
	if ( ( id >= HT_PARAMTYPE_NPC_START ) && ( id <= HT_PARAMTYPE_NPC_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsChargeNPC( const int id)
{
	// 다음의 번호는 크리슈나로 인정, 거리체크 안한다.
	if (id >= 1342 && id <= 1436)
		return true;

	// 21번존 새로 추가 (크리슈나 NPC 확장)
	if (id >= 1446 && id <= 1455)
		return true;

	switch(id)
	{
		case 1263: // 크리슈나 일경우 TRUE 반환
		case 1264:
		case 1265:
		case 1266:
		case 1267:
		case 1268:
		case 1269:
		case 1270:
		case 1271:
		case 1272:
		case 1273:
		case 1274:
		case 1275:
		case 1276:	
		case 1277:
		case 1296:
		case 1218:
		case 1219:
		case 1330:
		case 1340:	// 20번 NPC
		case 1445:	// 21번 NPC
			return true;
	}
	return false;
}



bool
CHTParamIDCheck::HT_bIsPortal( const int id )
{
	if ( ( id >= HT_PARAMTYPE_PORTAL_START ) && ( id <= HT_PARAMTYPE_PORTAL_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsTaskQuest( const int id )
{
	if ( ( id >= HT_PARAMTYPE_TASKQUEST_START ) && ( id <= HT_PARAMTYPE_TASKQUEST_END ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsAreaIndicate( const int id )
{
	if ( ( id >= HT_PARAMTYPE_AREAINDICATE_START ) && ( id <= HT_PARAMTYPE_AREAINDICATE_END ) ) return true;
	else return false;
}

HTIDLevel::HTIDLevel() { iID = 0; byteLevel = 0; }
HTIDLevel::~HTIDLevel() {}
HTIDLevel::HTIDLevel( const HTIDLevel& oIDLevel ) { iID = oIDLevel.iID; byteLevel = oIDLevel.byteLevel; }

#define HT_LOADCELL( szCell, Value, DataType ) \
{ strCell = (szCell); pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp ); Value = (DataType)iTemp; }

CHTBaseClientParamTable::CHTBaseClientParamTable() {}
CHTBaseClientParamTable::~CHTBaseClientParamTable() {}

bool CHTBaseClientParamTable::HT_bGetMonsterName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterSize( const int id, byte* pbyteSize ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterClass( const int id, byte* pbyteClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterFly( const int id, byte* pbFly ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterReserved7( const int id, byte* pbReseerved7 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterName( CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterSize( byte* pbyteSize ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterClass( byte* pbyteClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterFly( byte* pbFly ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterReserved7( byte* pbReseerved7 ) { return false; }

bool CHTBaseClientParamTable::HT_bGetMonsterSkillRange( const int id, int* piRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterSkillRange( int* piRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetMonsterSkillCastingTime( int* piCastingTime ) { return false; }

bool CHTBaseClientParamTable::HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl ) { return false; }

bool CHTBaseClientParamTable::HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillType( byte* pbyteType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCombatPhase( short* psCombatPhase ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillDuration( int* piDuration ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCoolDownTime( int* piCoolDownTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillRange( int* piRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAllowedTarget( int* piAllowedTarget ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillAttackType( byte* pbyteAttackType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillFollowRange( byte* pbyteFollowRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillPierceRate( byte* pbytePierceRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReadyTime( int* piReadyTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCastingTime( int* piCastingTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillApplyTime( int* piApplyTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1ID( int* piEffect1ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Function( int* piEffect1Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Duration( int* piEffect1Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2ID( int* piEffect2ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Function( int* piEffect2Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Duration( int* piEffect2Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3ID( int* piEffect3ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Function( int* piEffect3Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Duration( int* piEffect3Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4ID( int* piEffect4ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Function( int* piEffect4Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Duration( int* piEffect4Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5ID( int* piEffect5ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Function( int* piEffect5Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Duration( int* piEffect5Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostTP( int* piCostTP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostHP( int* piCostHP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillidCostItem( int* pidCostItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqWeaponType( int* piReqWeaponType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillidReqItem( int* pidReqItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqLevel( byte* pbyteLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqTribe( int* piReqTribe ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqClass( int* piReqClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill1( int* pidReqSkill1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill2( int* pidReqSkill2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl ) { return false; }  

bool CHTBaseClientParamTable::HT_bGetItemLevel( const int id, byte* pbyteLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemDescription( const int id, CHTString* pstrDescription ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemClass( const int id, byte* pbyteClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemType( const int id, short* psType) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRupiah( const int id, int* piRupiah ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemSellRupiah( const int id, int* piSellRupiah ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemMaxDurability( const int id, short* psMaxDurability ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCombatPhase( const int id, short* psCombatPhase ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1ID( const int id, int* piEffect1ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Function( const int id, int* piEffect1Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2ID( const int id, int* piEffect2ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Function( const int id, int* piEffect2Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3ID( const int id, int* piEffect3ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Function( const int id, int* piEffect3Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4ID( const int id, int* piEffect4ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Function( const int id, int* piEffect4Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5ID( const int id, int* piEffect5ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Function( const int id, int* piEffect5Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRange( const int id, byte* pbyteRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemArmorType( const int id, byte* pbyteArmorType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemAttackType( const int id, byte* pbyteAttackType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCostTP( const int id, int* piCostTP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCostHP( const int id, int* piCostHP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemidCostItem( const int id, int* pidCostItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitTribe( const int id, int* piLimitTribe ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCash( const int id, int* piCash ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemTimeLimit( const int id, short* psTimeLimit ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetItemFXEffectID( const int id, int* piFXID ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetItemEventID( const int id, short* psEventID ) { return false; }

bool CHTBaseClientParamTable::HT_bGetItemLevel( byte* pbyteLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemName( CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemDescription( CHTString* pstrDescription ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemClass( byte* pbyteClass ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemType( short* psType) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRupiah( int* piRupiah ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemSellRupiah( int* piSellRupiah ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemMaxDurability( short* psMaxDurability ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemMaxCount( byte* pbyteMaxCount ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCombatPhase( short* psCombatPhase ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1ID( int* piEffect1ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Function( int* piEffect1Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Duration( int* piEffect1Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Param1( int* piEffect1Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect1Param2( int* piEffect1Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2ID( int* piEffect2ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Function( int* piEffect2Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Duration( int* piEffect2Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Param1( int* piEffect2Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect2Param2( int* piEffect2Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3ID( int* piEffect3ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Function( int* piEffect3Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Duration( int* piEffect3Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Param1( int* piEffect3Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect3Param2( int* piEffect3Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4ID( int* piEffect4ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Function( int* piEffect4Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Duration( int* piEffect4Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Param1( int* piEffect4Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect4Param2( int* piEffect4Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5ID( int* piEffect5ID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Function( int* piEffect5Function ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Duration( int* piEffect5Duration ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Param1( int* piEffect5Param1 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemEffect5Param2( int* piEffect5Param2 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCoolDownTime( int* piCoolDownTime ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRange( byte* pbyteRange ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemArmorType( byte* pbyteArmorType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemAttackType( byte* pbyteAttackType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCostTP( int* piCostTP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCostHP( int* piCostHP ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemidCostItem( int* pidCostItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitTribe( int* piLimitTribe ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitLevel( byte* pbyteLimitLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemRefinableItemType( int* piRefinableItemType ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemCash( int* piCash ) { return false; }
bool CHTBaseClientParamTable::HT_bGetItemTimeLimit( short* psTimeLimit ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetItemFXEffectID( int* piFXID ) { return false; }
//bool CHTBaseClientParamTable::HT_bGetItemEventID( short* psEventID ) { return false; }

bool CHTBaseClientParamTable::HT_bGetNPCName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCSize( const int id, byte* pbyteSize ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCZone( const int id, byte* pbyteZone ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti ) { return false; }
int CHTBaseClientParamTable::HT_iGetNPCSellingItemCount( const int id ) { return -1; }
bool CHTBaseClientParamTable::HT_bGetNPCSellingItem( const int id, const int index, int* pidItem ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCName( CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCSize( byte* pbyteSize ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCZone( byte* pbyteZone ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCPosition( short* psPosX, short* psPosZ ) { return false; }
bool CHTBaseClientParamTable::HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti ) { return false; }
int CHTBaseClientParamTable::HT_iGetNPCSellingItemCount() { return -1; }
bool CHTBaseClientParamTable::HT_bGetNPCSellingItem( const int index, int* pidItem ) { return false; }

// Portal
bool CHTBaseClientParamTable::HT_bGetPortalName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
										  short* psStartX, short* psStartZ, short* psEndX, short* psEndZ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee ) { return false; }
bool CHTBaseClientParamTable::HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel) { return false; }

// TaskQuest
bool CHTBaseClientParamTable::HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource1( const int id, byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource2( const int id, byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource3( const int id, byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource4( const int id, byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource5( const int id, byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource6( const int id, byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6) { return false; }

bool CHTBaseClientParamTable::HT_bGetTaskReward1( const int id, byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward2( const int id, byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward3( const int id, byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward4( const int id, byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward5( const int id, byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel) { return false; }

bool CHTBaseClientParamTable::HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 ) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource1( byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource2( byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource3( byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource4( byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource5( byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskSource6( byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6) { return false; }

bool CHTBaseClientParamTable::HT_bGetTaskReward1( byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward2( byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward3( byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward4( byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskReward5( byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5) { return false; }
bool CHTBaseClientParamTable::HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel) {return false;}

// AreaIndicate
bool CHTBaseClientParamTable::HT_bGetAreaFrom( const int id, DWORD* pdwFromID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetAreaTo( const int id, DWORD* pdwToID ) { return false; }
bool CHTBaseClientParamTable::HT_bGetAreaName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseClientParamTable::HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName ) { return false; }

CHTMonsterParamTable::CHTMonsterParamTable() : m_pParamMonster ( 0 ), m_pParamMonsterSkill ( 0 )
{}

CHTMonsterParamTable::~CHTMonsterParamTable()
{
	HTMonsterParam_It itMonster = m_mapTableMonster.begin();
	while ( itMonster != m_mapTableMonster.end() )
	{
		if ( itMonster->second ) delete (itMonster->second);
		itMonster = m_mapTableMonster.erase( itMonster );
	}

	HTMonsterSkillParam_It itMonsterSkill = m_mapTableMonsterSkill.begin();
	while ( itMonsterSkill != m_mapTableMonsterSkill.end() )
	{
		if ( itMonsterSkill->second ) delete (itMonsterSkill->second);
		itMonsterSkill = m_mapTableMonsterSkill.erase( itMonsterSkill );
	}
}

bool
CHTMonsterParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	if( byteType == HT_PARAMTYPE_MONSTER )
	{
		HTMonsterParam_It itTable = m_mapTableMonster.begin();
		while ( itTable != m_mapTableMonster.end() )
		{
			HTIDLevel oIDLevel;
			oIDLevel.iID = itTable->first;
			oIDLevel.byteLevel = 0;
			vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );

			++itTable;
		}
	}
	else	// byteType == HT_PARAMTYPE_MONSTERSKILL
	{
		HTMonsterSkillParam_It itTable = m_mapTableMonsterSkill.begin();
		while ( itTable != m_mapTableMonsterSkill.end() )
		{
			HTIDLevel oIDLevel;
			oIDLevel.iID = itTable->first;
			oIDLevel.byteLevel = 0;
			vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );
			
			++itTable;
		}
	}

	return true;
}

bool
CHTMonsterParamTable::HT_bLockID( const int id, const byte byteLevel )
{
	// Monster
	if ( CHTParamIDCheck::HT_bIsMonster( id ) )
	{
		if( m_pParamMonster != NULL )
			return false;

		HTMonsterParam_It itTable = m_mapTableMonster.find( id );
		if ( itTable != m_mapTableMonster.end() )
		{
			if ( itTable->second )
			{
				m_pParamMonster = itTable->second;
				return true;
			}
		}
		return false;
	}
	// MonsterSkill
	else if ( CHTParamIDCheck::HT_bIsMonsterSkill( id ) )
	{
		if( m_pParamMonsterSkill != NULL )
			return false;

		HTMonsterSkillParam_It itTable = m_mapTableMonsterSkill.find( id );
		if ( itTable != m_mapTableMonsterSkill.end() )
		{
			if ( itTable->second )
			{
				m_pParamMonsterSkill = itTable->second;
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool
CHTMonsterParamTable::HT_bUnLockID( const int id, const byte byteLevel )
{
	// Monster
	if ( CHTParamIDCheck::HT_bIsMonster( id ) )	
	{
		HTMonsterParam_It itTable = m_mapTableMonster.find( id );
		if ( itTable != m_mapTableMonster.end() )
		{
			if ( itTable->second )
			{
				if ( m_pParamMonster == itTable->second ) // 포인터끼리 비교를 하다니.. -_-
				{
					m_pParamMonster = NULL;
					return true;
				}
			}
		}
		return false;
	}
	// MonsterSkill
	else	
	{
		HTMonsterSkillParam_It itTable = m_mapTableMonsterSkill.find( id );
		if ( itTable != m_mapTableMonsterSkill.end() )
		{
			if ( itTable->second )
			{
				if ( m_pParamMonsterSkill == itTable->second ) // 포인터끼리 비교를 하다니.. -_-
				{
					m_pParamMonsterSkill = NULL;
					return true;
				}
			}
		}
		return false;
	}
}

bool
CHTMonsterParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	if( strTable == "Monster")
	{
		HTMonsterParam* pRecord = 0;
		for ( unsigned int i = 0; i < m_nItems; ++i )
		{
			pRecord = new HTMonsterParam;

			HT_LOADCELL( _T("ID"),					iID,						int );
			if( strLanguage == HT_LANGUAGE_CHINESE )
				strCell = _T("chi_szName");
			else
				strCell = _T("kor_szName");
			pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );

			HT_LOADCELL( _T("byteSize"), 			pRecord->byteSize,			byte );
			HT_LOADCELL( _T("byteClass"), 			pRecord->byteClass,			byte );
			HT_LOADCELL( _T("bFly"), 				pRecord->bFly,				byte );
			HT_LOADCELL( _T("byteReserve7"), 		pRecord->byteReserve7,		byte );

			m_mapTableMonster.insert( HTMonsterParam_Value( iID, pRecord ) );
		}
	}
	else if( strTable == "MonsterSkill")
	{
		HTMonsterSkillParam* pRecord = 0;
		for ( unsigned int i = 0; i < m_nItems; ++i )
		{
			pRecord = new HTMonsterSkillParam;

			HT_LOADCELL( _T("ID"),					iID,							int );
			HT_LOADCELL( _T("iRange"),				pRecord->iRange,				int	);
			HT_LOADCELL( _T("iCastingTime"),		pRecord->iCastingTime,			int	);

			m_mapTableMonsterSkill.insert( HTMonsterSkillParam_Value( iID, pRecord ) );
		}
	}
	else
		return false;

	return true;
}

bool
CHTMonsterParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	int iID;
	// Monster
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;
	HTMonsterParam* pRecordMonster = NULL;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecordMonster = new HTMonsterParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecordMonster, sizeof(HTMonsterParam) );

		m_mapTableMonster.insert( HTMonsterParam_Value( iID, pRecordMonster ) );
	}
	// MonsterSkill
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;
	HTMonsterSkillParam* pRecordMonsterSkill = NULL;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecordMonsterSkill = new HTMonsterSkillParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecordMonsterSkill, sizeof(HTMonsterSkillParam) );

		m_mapTableMonsterSkill.insert( HTMonsterSkillParam_Value( iID, pRecordMonsterSkill ) );
	}

	return true;
}

bool
CHTMonsterParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	int iID;
	// Monster
	HTMonsterParam_It itMonster;
	itMonster = m_mapTableMonster.begin();
	iRecordCount = (int)m_mapTableMonster.size();
	pFile->HT_bWrite( iRecordCount );
	while ( itMonster != m_mapTableMonster.end() )
	{
		iID = itMonster->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itMonster->second, sizeof(HTMonsterParam) );

		itMonster++;
	}
	// MonsterSkill
	HTMonsterSkillParam_It itMonsterSkill;
	itMonsterSkill = m_mapTableMonsterSkill.begin();
	iRecordCount = (int)m_mapTableMonsterSkill.size();
	pFile->HT_bWrite( iRecordCount );
	while ( itMonsterSkill != m_mapTableMonsterSkill.end() )
	{
		iID = itMonsterSkill->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itMonsterSkill->second, sizeof(HTMonsterSkillParam) );

		itMonsterSkill++;
	}

	return true;
}

bool
CHTMonsterParamTable::HT_bGetMonsterName( const int id, CHTString* pstrName )
{
	HTMonsterParam_It itTable = m_mapTableMonster.find( id );
	if ( itTable != m_mapTableMonster.end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSize( const int id, byte* pbyteSize )
{
	HTMonsterParam_It itTable = m_mapTableMonster.find( id );
	if ( itTable != m_mapTableMonster.end() )
	{
		if ( itTable->second )
		{
			*pbyteSize = (itTable->second)->byteSize;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterClass( const int id, byte* pbyteClass )
{
	HTMonsterParam_It itTable = m_mapTableMonster.find( id );
	if ( itTable != m_mapTableMonster.end() )
	{
		if ( itTable->second )
		{
			*pbyteClass = (itTable->second)->byteClass;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterFly( const int id, byte* pbFly )
{
	HTMonsterParam_It itTable = m_mapTableMonster.find( id );
	if ( itTable != m_mapTableMonster.end() )
	{
		if ( itTable->second )
		{
			*pbFly = (itTable->second)->bFly;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterReserved7( const int id, byte* pbReseerved7 )
{
	HTMonsterParam_It itTable = m_mapTableMonster.find( id );
	if ( itTable != m_mapTableMonster.end() )
	{
		if ( itTable->second )
		{
			*pbReseerved7 = (itTable->second)->byteReserve7;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterName( CHTString* pstrName )
{
	if ( m_pParamMonster )
	{
		*pstrName = m_pParamMonster->szName;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSize( byte* pbyteSize )
{
	if ( m_pParamMonster )
	{
		*pbyteSize = m_pParamMonster->byteSize;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterClass( byte* pbyteClass )
{
	if ( m_pParamMonster )
	{
		*pbyteClass = m_pParamMonster->byteClass;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterFly( byte* pbFly )
{
	if ( m_pParamMonster )
	{
		*pbFly = m_pParamMonster->bFly;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterReserved7( byte* pbReseerved7 )
{
	if ( m_pParamMonster )
	{
		*pbReseerved7 = m_pParamMonster->byteReserve7;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSkillRange( const int id, int* piRange )
{
	HTMonsterSkillParam_It itTable = m_mapTableMonsterSkill.find( id );
	if ( itTable != m_mapTableMonsterSkill.end() )
	{
		if ( itTable->second )
		{
			*piRange = (itTable->second)->iRange;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime )
{
	HTMonsterSkillParam_It itTable = m_mapTableMonsterSkill.find( id );
	if ( itTable != m_mapTableMonsterSkill.end() )
	{
		if ( itTable->second )
		{
			*piCastingTime = (itTable->second)->iCastingTime;
			return true;
		}
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSkillRange( int* piRange )
{
	if ( m_pParamMonsterSkill )
	{
		*piRange = m_pParamMonsterSkill->iRange;
		return true;
	}
	return false;
}

bool
CHTMonsterParamTable::HT_bGetMonsterSkillCastingTime( int* piCastingTime )
{
	if ( m_pParamMonsterSkill )
	{
		*piCastingTime = m_pParamMonsterSkill->iCastingTime;
		return true;
	}
	return false;
}

CHTPCSkillParamTable::CHTPCSkillParamTable() : m_pParam ( 0 )
{}

CHTPCSkillParamTable::~CHTPCSkillParamTable()
{
	for ( int i = 0; i < HT_PCSKILL_MAXLEVEL; ++i )
	{
		HTPCSkillParam_It it = m_arrmapTable[i].begin();
		while ( it != m_arrmapTable[i].end() )
		{
			if ( it->second ) delete (it->second);
			it = m_arrmapTable[i].erase( it );
		}
	}	
}

bool
CHTPCSkillParamTable::HT_bLockID( const int id, const byte byteLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	if( m_pParam != NULL )
		return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			m_pParam = itTable->second;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bUnLockID( const int id, const byte byteLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // 포인터끼리 비교를 하다니.. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTPCSkillParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;
	byte byteLevel;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTPCSkillParam;

		HT_LOADCELL( _T("ID"),						iID,								int );
#ifdef HT_NEED_NAME
		strCell = "szName";
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );
#endif
		HT_LOADCELL( _T("byteLevel"),				byteLevel,							byte );
		HT_LOADCELL( _T("byteMaxLevel"),			pRecord->byteMaxLevel,				byte );
		HT_LOADCELL( _T("byteType"),				pRecord->byteType,					byte );
		HT_LOADCELL( _T("sCombatPhase"),			pRecord->sCombatPhase,				short );
		HT_LOADCELL( _T("iDuration"),				pRecord->iDuration,					int );
//		HT_LOADCELL( _T("byteSuccessRate"),			pRecord->byteSuccessRate,			byte );
		HT_LOADCELL( _T("iCoolDownTime"),			pRecord->iCoolDownTime,				int	);
		HT_LOADCELL( _T("iRange"),					pRecord->iRange,					int	);
		HT_LOADCELL( _T("iAreaOfEffect"),			pRecord->iAreaOfEffect,				int	);
		HT_LOADCELL( _T("iAllowedTarget"),			pRecord->iAllowedTarget,			int	);
		HT_LOADCELL( _T("byteAttackType"),			pRecord->byteAttackType,			byte );
		HT_LOADCELL( _T("iReadyTime"),				pRecord->iReadyTime,				int	);
		HT_LOADCELL( _T("iCastingTime"),			pRecord->iCastingTime,				int	);
		HT_LOADCELL( _T("iApplyTime"),				pRecord->iApplyTime,				int	);
		HT_LOADCELL( _T("byteCastingSuccessRate"),	pRecord->byteCastingSuccessRate,	byte );
		HT_LOADCELL( _T("byteFollowRange"),			pRecord->byteFollowRange,			byte );
		HT_LOADCELL( _T("bytePierceRate"),			pRecord->bytePierceRate,			byte );
		HT_LOADCELL( _T("iEffect1ID"),				pRecord->iEffect1ID,				int	);
		HT_LOADCELL( _T("iEffect1Function"),		pRecord->iEffect1Function,			int	);
		HT_LOADCELL( _T("iEffect1Duration"),		pRecord->iEffect1Duration,			int	);
		HT_LOADCELL( _T("iEffect1Param1"),			pRecord->iEffect1Param1,			int	);
		HT_LOADCELL( _T("iEffect1Param2"),			pRecord->iEffect1Param2,			int	);
		HT_LOADCELL( _T("iEffect2ID"),				pRecord->iEffect2ID,				int	);
		HT_LOADCELL( _T("iEffect2Function"),		pRecord->iEffect2Function,			int	);
		HT_LOADCELL( _T("iEffect2Duration"),		pRecord->iEffect2Duration,			int	);
		HT_LOADCELL( _T("iEffect2Param1"),			pRecord->iEffect2Param1,			int	);
		HT_LOADCELL( _T("iEffect2Param2"),			pRecord->iEffect2Param2,			int	);
		HT_LOADCELL( _T("iEffect3ID"),				pRecord->iEffect3ID,				int	);
		HT_LOADCELL( _T("iEffect3Function"),		pRecord->iEffect3Function,			int	);
		HT_LOADCELL( _T("iEffect3Duration"),		pRecord->iEffect3Duration,			int	);
		HT_LOADCELL( _T("iEffect3Param1"),			pRecord->iEffect3Param1,			int	);
		HT_LOADCELL( _T("iEffect3Param2"),			pRecord->iEffect3Param2,			int	);
		HT_LOADCELL( _T("iEffect4ID"),				pRecord->iEffect4ID,				int	);
		HT_LOADCELL( _T("iEffect4Function"),		pRecord->iEffect4Function,			int	);
		HT_LOADCELL( _T("iEffect4Duration"),		pRecord->iEffect4Duration,			int	);
		HT_LOADCELL( _T("iEffect4Param1"),			pRecord->iEffect4Param1,			int	);
		HT_LOADCELL( _T("iEffect4Param2"),			pRecord->iEffect4Param2,			int	);
		HT_LOADCELL( _T("iEffect5ID"),				pRecord->iEffect5ID,				int	);
		HT_LOADCELL( _T("iEffect5Function"),		pRecord->iEffect5Function,			int	);
		HT_LOADCELL( _T("iEffect5Duration"),		pRecord->iEffect5Duration,			int	);
		HT_LOADCELL( _T("iEffect5Param1"),			pRecord->iEffect5Param1,			int	);
		HT_LOADCELL( _T("iEffect5Param2"),			pRecord->iEffect5Param2,			int	);
		HT_LOADCELL( _T("iCostTP"),					pRecord->iCostTP,					int );
		HT_LOADCELL( _T("iCostHP"),					pRecord->iCostHP,					int );
		HT_LOADCELL( _T("idCostItem"),				pRecord->idCostItem,				int );
		HT_LOADCELL( _T("byteCostItemCount"),		pRecord->byteCostItemCount,			byte );
		HT_LOADCELL( _T("iReqTrimuriti"),			pRecord->iReqTrimuriti,				int );
		HT_LOADCELL( _T("iReqTribe"),				pRecord->iReqTribe,					int );
		HT_LOADCELL( _T("iReqClass"),				pRecord->iReqClass,					int );
		HT_LOADCELL( _T("iReqWeaponType"),			pRecord->iReqWeaponType,			int );
		HT_LOADCELL( _T("idReqItem"),				pRecord->idReqItem,					int );
		HT_LOADCELL( _T("byteReqLevel"),			pRecord->byteReqLevel,				byte );
		HT_LOADCELL( _T("idReqSkill1"),				pRecord->idReqSkill1,				int );
		HT_LOADCELL( _T("byteReqSkill1_Lvl"),		pRecord->byteReqSkill1_Lvl,			byte );
		HT_LOADCELL( _T("idReqSkill2"),				pRecord->idReqSkill2,				int );
		HT_LOADCELL( _T("byteReqSkill2_Lvl"),		pRecord->byteReqSkill2_Lvl,			byte );

		if ( byteLevel >=0 && byteLevel < HT_PCSKILL_MAXLEVEL )
		{
			m_arrmapTable[byteLevel].insert( HTPCSkillParam_Value( iID, pRecord ) );
		}
		else
		{
			MessageBox( NULL, "레벨 영역을 벗어난 스킬 레벨", "CHTPCSkillParamTable", MB_OK );
		}
	}

	return true;
}

bool
CHTPCSkillParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iSkillLevel;
	int arriRecordCount[HT_PCSKILL_MAXLEVEL];

	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		pFile->HT_bRead( &arriRecordCount[iSkillLevel] );
		m_nItems += arriRecordCount[iSkillLevel];
	}

	HTPCSkillParam* pRecord = NULL;
	int iID;
	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		for ( int i = 0; i < arriRecordCount[iSkillLevel]; ++i )
		{
			pRecord = new HTPCSkillParam;

			pFile->HT_bRead( &iID );
			pFile->HT_bRead( pRecord, sizeof(HTPCSkillParam) );

			m_arrmapTable[iSkillLevel].insert( HTPCSkillParam_Value( iID, pRecord ) );
		}
	}
	
	return true;
}

bool
CHTPCSkillParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iSkillLevel;
	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		int iRecordCount = (int)m_arrmapTable[iSkillLevel].size();
		pFile->HT_bWrite( iRecordCount );
	}

	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		HTPCSkillParam_It itTable = m_arrmapTable[iSkillLevel].begin();
		while ( itTable != m_arrmapTable[iSkillLevel].end() )
		{
			int iID = itTable->first;
			pFile->HT_bWrite( iID );
			pFile->HT_bWrite( itTable->second, sizeof(HTPCSkillParam) );

			itTable++;
		}
	}

	return true;
}

bool
CHTPCSkillParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTPCSkillParam_It itTable;
	
	for( int i = 0 ; i < HT_PCSKILL_MAXLEVEL ; ++i )
	{
		itTable = m_arrmapTable[i].begin();

		while ( itTable != m_arrmapTable[i].end() )
		{
			HTIDLevel oIDLevel;
			oIDLevel.iID = itTable->first;
			oIDLevel.byteLevel = i;
			vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );

			++itTable;
		}
	}

	return true;
}

#ifdef HT_NEED_NAME
bool
CHTPCSkillParamTable::HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetName( CHTString* pstrName )
{
	if ( m_pParam )
	{
		*pstrName = m_pParam->szName;
		return true;
	}
	return false;
}
#endif

bool
CHTPCSkillParamTable::HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteMaxLevel = (itTable->second)->byteMaxLevel;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteType = (itTable->second)->byteType;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*psCombatPhase = (itTable->second)->sCombatPhase;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piReqTrimuriti = (itTable->second)->iReqTrimuriti;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piReqTribe = (itTable->second)->iReqTribe;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piReqClass = (itTable->second)->iReqClass;
			return true;
		}
	}
	return false;
}

/*
bool
CHTPCSkillParamTable::HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteSuccessRate = (itTable->second)->byteSuccessRate;
			return true;
		}
	}
	return false;
}
*/
bool
CHTPCSkillParamTable::HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteCastingSuccessRate = (itTable->second)->byteCastingSuccessRate;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteFollowRange = (itTable->second)->byteFollowRange;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbytePierceRate = (itTable->second)->bytePierceRate;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piDuration = (itTable->second)->iDuration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piAreaOfEffect = (itTable->second)->iAreaOfEffect;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piReqWeaponType = (itTable->second)->iReqWeaponType;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pidReqItem = (itTable->second)->idReqItem;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReqLevel = (itTable->second)->byteReqLevel;
			return true;
		}
	}
	return false;
}


bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pidReqSkill1 = (itTable->second)->idReqSkill1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReqSkill1_Lvl = (itTable->second)->byteReqSkill1_Lvl;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pidReqSkill2 = (itTable->second)->idReqSkill2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReqSkill1_Lvl = (itTable->second)->byteReqSkill1_Lvl;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piAllowedTarget = (itTable->second)->iAllowedTarget;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteAttackType = (itTable->second)->byteAttackType;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piReadyTime = (itTable->second)->iReadyTime;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piCastingTime = (itTable->second)->iCastingTime;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piApplyTime = (itTable->second)->iApplyTime;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piCoolDownTime = (itTable->second)->iCoolDownTime;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piRange = (itTable->second)->iRange;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect1ID = (itTable->second)->iEffect1ID;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect1Function = (itTable->second)->iEffect1Function;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect1Duration = (itTable->second)->iEffect1Duration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect1Param1 = (itTable->second)->iEffect1Param1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect1Param2 = (itTable->second)->iEffect1Param2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect2ID = (itTable->second)->iEffect2ID;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect2Function = (itTable->second)->iEffect2Function;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect2Duration = (itTable->second)->iEffect2Duration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect2Param1 = (itTable->second)->iEffect2Param1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect2Param2 = (itTable->second)->iEffect2Param2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect3ID = (itTable->second)->iEffect3ID;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect3Function = (itTable->second)->iEffect3Function;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect3Duration = (itTable->second)->iEffect3Duration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect3Param1 = (itTable->second)->iEffect3Param1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect3Param2 = (itTable->second)->iEffect3Param2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect4ID = (itTable->second)->iEffect4ID;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect4Function = (itTable->second)->iEffect4Function;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect4Duration = (itTable->second)->iEffect4Duration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect4Param1 = (itTable->second)->iEffect4Param1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect4Param2 = (itTable->second)->iEffect4Param2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect5ID = (itTable->second)->iEffect5ID;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect5Function = (itTable->second)->iEffect5Function;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect5Duration = (itTable->second)->iEffect5Duration;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect5Param1 = (itTable->second)->iEffect5Param1;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piEffect5Param2 = (itTable->second)->iEffect5Param2;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piCostTP = (itTable->second)->iCostTP;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piCostHP = (itTable->second)->iCostHP;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pidCostItem = (itTable->second)->idCostItem;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteCostItemCount = (itTable->second)->byteCostItemCount;
			return true;
		}
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel )
{
	if ( m_pParam )
	{
		*pbyteMaxLevel = m_pParam->byteMaxLevel;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillType( byte* pbyteType )
{
	if ( m_pParam )
	{
		*pbyteType = m_pParam->byteType;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCombatPhase( short* psCombatPhase )
{
	if ( m_pParam )
	{
		*psCombatPhase = m_pParam->sCombatPhase;
		return true;
	}
	return false;
}

/*
bool
CHTPCSkillParamTable::HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate )
{
	if ( m_pParam )
	{
		*pbyteSuccessRate = m_pParam->byteSuccessRate;
		return true;
	}
	return false;
}
*/
bool
CHTPCSkillParamTable::HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate )
{
	if ( m_pParam )
	{
		*pbyteCastingSuccessRate = m_pParam->byteCastingSuccessRate;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillFollowRange( byte* pbyteFollowRange )
{
	if ( m_pParam )
	{
		*pbyteFollowRange = m_pParam->byteFollowRange;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillPierceRate( byte* pbytePierceRate )
{
	if ( m_pParam )
	{
		*pbytePierceRate = m_pParam->bytePierceRate;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillDuration( int* piDuration )
{
	if ( m_pParam )
	{
		*piDuration = m_pParam->iDuration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect )
{
	if ( m_pParam )
	{
		*piAreaOfEffect = m_pParam->iAreaOfEffect;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti )
{
	if ( m_pParam )
	{
		*piReqTrimuriti = m_pParam->iReqTrimuriti;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqTribe( int* piReqTribe )
{
	if ( m_pParam )
	{
		*piReqTribe = m_pParam->iReqTribe;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqClass( int* piReqClass )
{
	if ( m_pParam )
	{
		*piReqClass = m_pParam->iReqClass;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqWeaponType( int* piReqWeaponType )
{
	if ( m_pParam )
	{
		*piReqWeaponType = m_pParam->iReqWeaponType;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillidReqItem( int* pidReqItem )
{
	if ( m_pParam )
	{
		*pidReqItem = m_pParam->idReqItem;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqLevel( byte* pbyteReqLevel )
{
	if ( m_pParam )
	{
		*pbyteReqLevel = m_pParam->byteReqLevel;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill1( int* pidReqSkill1 )
{
	if ( m_pParam )
	{
		*pidReqSkill1 = m_pParam->idReqSkill1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl )
{
	if ( m_pParam )
	{
		*pbyteReqSkill1_Lvl = m_pParam->byteReqSkill1_Lvl;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill2( int* pidReqSkill2 )
{
	if ( m_pParam )
	{
		*pidReqSkill2 = m_pParam->idReqSkill2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl )
{
	if ( m_pParam )
	{
		*pbyteReqSkill2_Lvl = m_pParam->byteReqSkill2_Lvl;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParam )
	{
		*piAllowedTarget = m_pParam->iAllowedTarget;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillAttackType( byte* pbyteAttackType )
{
	if ( m_pParam )
	{
		*pbyteAttackType = m_pParam->byteAttackType;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillReadyTime( int* piReadyTime )
{
	if ( m_pParam )
	{
		*piReadyTime = m_pParam->iReadyTime;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCastingTime( int* piCastingTime )
{
	if ( m_pParam )
	{
		*piCastingTime = m_pParam->iCastingTime;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillApplyTime( int* piApplyTime )
{
	if ( m_pParam )
	{
		*piApplyTime = m_pParam->iApplyTime;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParam )
	{
		*piCoolDownTime = m_pParam->iCoolDownTime;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillRange( int* piRange )
{
	if ( m_pParam )
	{
		*piRange = m_pParam->iRange;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1ID( int* piEffect1ID )
{
	if ( m_pParam )
	{
		*piEffect1ID = m_pParam->iEffect1ID;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Function( int* piEffect1Function )
{
	if ( m_pParam )
	{
		*piEffect1Function = m_pParam->iEffect1Function;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParam )
	{
		*piEffect1Duration = m_pParam->iEffect1Duration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParam )
	{
		*piEffect1Param1 = m_pParam->iEffect1Param1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParam )
	{
		*piEffect1Param2 = m_pParam->iEffect1Param2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2ID( int* piEffect2ID )
{
	if ( m_pParam )
	{
		*piEffect2ID = m_pParam->iEffect2ID;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Function( int* piEffect2Function )
{
	if ( m_pParam )
	{
		*piEffect2Function = m_pParam->iEffect2Function;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParam )
	{
		*piEffect2Duration = m_pParam->iEffect2Duration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParam )
	{
		*piEffect2Param1 = m_pParam->iEffect2Param1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParam )
	{
		*piEffect2Param2 = m_pParam->iEffect2Param2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3ID( int* piEffect3ID )
{
	if ( m_pParam )
	{
		*piEffect3ID = m_pParam->iEffect3ID;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Function( int* piEffect3Function )
{
	if ( m_pParam )
	{
		*piEffect3Function = m_pParam->iEffect3Function;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParam )
	{
		*piEffect3Duration = m_pParam->iEffect3Duration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParam )
	{
		*piEffect3Param1 = m_pParam->iEffect3Param1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParam )
	{
		*piEffect3Param2 = m_pParam->iEffect3Param2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4ID( int* piEffect4ID )
{
	if ( m_pParam )
	{
		*piEffect4ID = m_pParam->iEffect4ID;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Function( int* piEffect4Function )
{
	if ( m_pParam )
	{
		*piEffect4Function = m_pParam->iEffect4Function;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParam )
	{
		*piEffect4Duration = m_pParam->iEffect4Duration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParam )
	{
		*piEffect4Param1 = m_pParam->iEffect4Param1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParam )
	{
		*piEffect4Param2 = m_pParam->iEffect4Param2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5ID( int* piEffect5ID )
{
	if ( m_pParam )
	{
		*piEffect5ID = m_pParam->iEffect5ID;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Function( int* piEffect5Function )
{
	if ( m_pParam )
	{
		*piEffect5Function = m_pParam->iEffect5Function;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParam )
	{
		*piEffect5Duration = m_pParam->iEffect5Duration;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParam )
	{
		*piEffect5Param1 = m_pParam->iEffect5Param1;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParam )
	{
		*piEffect5Param2 = m_pParam->iEffect5Param2;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostTP( int* piCostTP )
{
	if ( m_pParam )
	{
		*piCostTP = m_pParam->iCostTP;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostHP( int* piCostHP )
{
	if ( m_pParam )
	{
		*piCostHP = m_pParam->iCostHP;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillidCostItem( int* pidCostItem )
{
	if ( m_pParam )
	{
		*pidCostItem = m_pParam->idCostItem;
		return true;
	}
	return false;
}

bool
CHTPCSkillParamTable::HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount )
{
	if ( m_pParam )
	{
		*pbyteCostItemCount = m_pParam->byteCostItemCount;
		return true;
	}
	return false;
}

// ---------------
CHTItemParamTable::CHTItemParamTable() : m_pParam(NULL)
/*m_pParamItemWeapon(0), m_pParamItemDefence(0), m_pParamItemAccessory(0), 
m_pParamItemRefine(0), m_pParamItemUsable(0), m_pParamItemCollect(0), m_pParamItemQuestOnly(0)*/
{}

CHTItemParamTable::~CHTItemParamTable()
{
	HTItemParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool
CHTItemParamTable::HT_bLockID( const int id, const byte byteLevel )
{
	if( m_pParam != NULL )
		return false;

	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			m_pParam = itTable->second;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bUnLockID( const int id, const byte byteLevel )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // 포인터끼리 비교를 하다니. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}
bool
CHTItemParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iID;
	int iRecordCount;

	pFile->HT_bRead( &iRecordCount );

	HTItemParam* pRecord;
	for ( int i = 0; i < iRecordCount; ++i )
	{
		pRecord = new HTItemParam;
		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTItemParam) );
		m_mapTable.insert( HTItemParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTItemParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iID;
	int iRecordCount;

	HTItemParam_It it;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );
	it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		iID = it->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( it->second, sizeof(HTItemParam) );

		++it;
	}

	return true;
}

bool
CHTItemParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;
	
	HTItemParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemParam;

		HT_LOADCELL( _T("ID"),						iID,							int );

		//strCell = _T("szName");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szName");
		else
			strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );
		//strCell = _T("szDescription");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szDescription");	
		else
			strCell = _T("kor_szDescription");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szDescription );

		HT_LOADCELL( _T("byteLevel"), 				pRecord->byteLevel,				byte );
		HT_LOADCELL( _T("byteClass"), 				pRecord->byteClass,				byte );
		HT_LOADCELL( _T("sType"),					pRecord->sType,					short );
		HT_LOADCELL( _T("iRupiah"), 				pRecord->iRupiah,				int );
		HT_LOADCELL( _T("iSellRupiah"), 			pRecord->iSellRupiah,			int );
		HT_LOADCELL( _T("sMaxDurability"), 			pRecord->sMaxDurability,		short );
		HT_LOADCELL( _T("byteMaxCount"), 			pRecord->byteMaxCount,			byte );
		HT_LOADCELL( _T("sCombatPhase"), 			pRecord->sCombatPhase,			short );
		HT_LOADCELL( _T("sSkillCastingTimeRate"), 	pRecord->sSkillCastingTimeRate,	short );
		HT_LOADCELL( _T("iEffect1ID"),				pRecord->iEffect1ID,			int	);
		HT_LOADCELL( _T("iEffect1Function"),		pRecord->iEffect1Function,		int	);
		HT_LOADCELL( _T("iEffect1Duration"),		pRecord->iEffect1Duration,		int	);
		HT_LOADCELL( _T("iEffect1Param1"),			pRecord->iEffect1Param1,		int	);
		HT_LOADCELL( _T("iEffect1Param2"),			pRecord->iEffect1Param2,		int	);
		HT_LOADCELL( _T("iEffect2ID"),				pRecord->iEffect2ID,			int	);
		HT_LOADCELL( _T("iEffect2Function"),		pRecord->iEffect2Function,		int	);
		HT_LOADCELL( _T("iEffect2Duration"),		pRecord->iEffect2Duration,		int	);
		HT_LOADCELL( _T("iEffect2Param1"),			pRecord->iEffect2Param1,		int	);
		HT_LOADCELL( _T("iEffect2Param2"),			pRecord->iEffect2Param2,		int	);
		HT_LOADCELL( _T("iEffect3ID"),				pRecord->iEffect3ID,			int	);
		HT_LOADCELL( _T("iEffect3Function"),		pRecord->iEffect3Function,		int	);
		HT_LOADCELL( _T("iEffect3Duration"),		pRecord->iEffect3Duration,		int	);
		HT_LOADCELL( _T("iEffect3Param1"),			pRecord->iEffect3Param1,		int	);
		HT_LOADCELL( _T("iEffect3Param2"),			pRecord->iEffect3Param2,		int	);
		HT_LOADCELL( _T("iEffect4ID"),				pRecord->iEffect4ID,			int	);
		HT_LOADCELL( _T("iEffect4Function"),		pRecord->iEffect4Function,		int	);
		HT_LOADCELL( _T("iEffect4Duration"),		pRecord->iEffect4Duration,		int	);
		HT_LOADCELL( _T("iEffect4Param1"),			pRecord->iEffect4Param1,		int	);
		HT_LOADCELL( _T("iEffect4Param2"),			pRecord->iEffect4Param2,		int	);
		HT_LOADCELL( _T("iEffect5ID"),				pRecord->iEffect5ID,			int	);
		HT_LOADCELL( _T("iEffect5Function"),		pRecord->iEffect5Function,		int	);
		HT_LOADCELL( _T("iEffect5Duration"),		pRecord->iEffect5Duration,		int	);
		HT_LOADCELL( _T("iEffect5Param1"),			pRecord->iEffect5Param1,		int	);
		HT_LOADCELL( _T("iEffect5Param2"),			pRecord->iEffect5Param2,		int	);
		HT_LOADCELL( _T("iCostTP"),					pRecord->iCostTP,				int );
		HT_LOADCELL( _T("iCostHP"),					pRecord->iCostHP,				int );
		HT_LOADCELL( _T("idCostItem"),				pRecord->idCostItem,			int );
		HT_LOADCELL( _T("iCoolDownTime"),			pRecord->iCoolDownTime,			int	);
		HT_LOADCELL( _T("byteRange"),				pRecord->byteRange,				byte );
		HT_LOADCELL( _T("byteArmorType"),			pRecord->byteArmorType,			byte );
		HT_LOADCELL( _T("byteAttackType"),			pRecord->byteAttackType,		byte );
		HT_LOADCELL( _T("iLimitTrimuriti"), 		pRecord->iLimitTrimuriti,		int );
		HT_LOADCELL( _T("iLimitTribe"), 			pRecord->iLimitTribe,			int );
		HT_LOADCELL( _T("byteLimitLevel"), 			pRecord->byteLimitLevel,		byte );
		HT_LOADCELL( _T("sLimitMusclechakra"),		pRecord->sLimitMusclechakra,	short );
		HT_LOADCELL( _T("sLimitNerveChakra"), 		pRecord->sLimitNerveChakra,		short );
		HT_LOADCELL( _T("sLimitHeartChakra"), 		pRecord->sLimitHeartChakra,		short );	
		HT_LOADCELL( _T("sLimitSoulChakra"), 		pRecord->sLimitSoulChakra,		short );
		HT_LOADCELL( _T("iRefinableItemType"), 		pRecord->iRefinableItemType,	int );
		HT_LOADCELL( _T("iCash"), 					pRecord->iCash,					int );
		HT_LOADCELL( _T("sTimeLimit"), 				pRecord->sTimeLimit,			short );
		//HT_LOADCELL( _T("sEventID"), 				pRecord->sEventID,				short );

		m_mapTable.insert( HTItemParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTItemParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTItemParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HTIDLevel oIDLevel;
		oIDLevel.iID = it->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );

		++it;
	}

	return true;
}

bool
CHTItemParamTable::HT_bGetItemLevel( const int id, byte* pbyteLevel )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteLevel = (itTable->second)->byteLevel;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemName( const int id, CHTString* pstrName )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemDescription( const int id, CHTString* pstrDescription )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrDescription = (itTable->second)->szDescription;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemClass( const int id, byte* pbyteClass )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteClass = (itTable->second)->byteClass;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemType( const int id, short* psType)
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psType = (itTable->second)->sType;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemRupiah( const int id, int* piRupiah )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRupiah = (itTable->second)->iRupiah;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemSellRupiah( const int id, int* piSellRupiah )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSellRupiah = (itTable->second)->iSellRupiah;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemMaxDurability( const int id, short* psMaxDurability )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psMaxDurability = (itTable->second)->sMaxDurability;
			return true;
		}
	}
	return false;
}


bool
CHTItemParamTable::HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteMaxCount = (itTable->second)->byteMaxCount;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCombatPhase( const int id, short* psCombatPhase )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psCombatPhase = (itTable->second)->sCombatPhase;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psSkillCastingTimeRate = (itTable->second)->sSkillCastingTimeRate;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1ID( const int id, int* piEffect1ID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect1ID = (itTable->second)->iEffect1ID;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Function( const int id, int* piEffect1Function )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect1Function = (itTable->second)->iEffect1Function;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect1Duration = (itTable->second)->iEffect1Duration;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect1Param1 = (itTable->second)->iEffect1Param1;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect1Param2 = (itTable->second)->iEffect1Param2;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2ID( const int id, int* piEffect2ID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect2ID = (itTable->second)->iEffect2ID;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Function( const int id, int* piEffect2Function )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect2Function = (itTable->second)->iEffect2Function;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect2Duration = (itTable->second)->iEffect2Duration;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect2Param1 = (itTable->second)->iEffect2Param1;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect2Param2 = (itTable->second)->iEffect2Param2;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3ID( const int id, int* piEffect3ID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect3ID = (itTable->second)->iEffect3ID;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Function( const int id, int* piEffect3Function )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect3Function = (itTable->second)->iEffect3Function;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect3Duration = (itTable->second)->iEffect3Duration;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect3Param1 = (itTable->second)->iEffect3Param1;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect3Param2 = (itTable->second)->iEffect3Param2;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4ID( const int id, int* piEffect4ID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect4ID = (itTable->second)->iEffect4ID;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Function( const int id, int* piEffect4Function )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect4Function = (itTable->second)->iEffect4Function;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect4Duration = (itTable->second)->iEffect4Duration;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect4Param1 = (itTable->second)->iEffect4Param1;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect4Param2 = (itTable->second)->iEffect4Param2;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5ID( const int id, int* piEffect5ID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect5ID = (itTable->second)->iEffect5ID;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Function( const int id, int* piEffect5Function )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect5Function = (itTable->second)->iEffect5Function;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect5Duration = (itTable->second)->iEffect5Duration;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect5Param1 = (itTable->second)->iEffect5Param1;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEffect5Param2 = (itTable->second)->iEffect5Param2;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCoolDownTime = (itTable->second)->iCoolDownTime;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemRange( const int id, byte* pbyteRange )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteRange = (itTable->second)->byteRange;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemArmorType( const int id, byte* pbyteArmorType )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteArmorType = (itTable->second)->byteArmorType;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemAttackType( const int id, byte* pbyteAttackType )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteAttackType = (itTable->second)->byteAttackType;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCostTP( const int id, int* piCostTP )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCostTP = (itTable->second)->iCostTP;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCostHP( const int id, int* piCostHP )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCostHP = (itTable->second)->iCostHP;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemidCostItem( const int id, int* pidCostItem )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pidCostItem = (itTable->second)->idCostItem;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLimitTrimuriti = (itTable->second)->iLimitTrimuriti;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitTribe( const int id, int* piLimitTribe )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLimitTribe = (itTable->second)->iLimitTribe;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteLimitLevel = (itTable->second)->byteLimitLevel;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psLimitMusclechakra = (itTable->second)->sLimitMusclechakra;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psLimitNerveChakra = (itTable->second)->sLimitNerveChakra;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psLimitHeartChakra = (itTable->second)->sLimitHeartChakra;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psLimitSoulChakra = (itTable->second)->sLimitSoulChakra;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRefinableItemType = (itTable->second)->iRefinableItemType;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCash( const int id, int* piCash )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCash = (itTable->second)->iCash;
			return true;
		}
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemTimeLimit( const int id, short* psTimeLimit )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psTimeLimit = (itTable->second)->sTimeLimit;
			return true;
		}
	}
	return false;
}

/*bool
CHTItemParamTable::HT_bGetItemFXEffectID( const int id, int* piFXID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piFXID = (itTable->second)->idFX;
			return true;
		}
	}
	return false;
}*/

//bool
//CHTItemParamTable::HT_bGetItemEventID( const int id, short* psEventID )
//{
//	HTItemParam_It itTable = m_mapTable.find( id );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			*psEventID = (itTable->second)->sEventID;
//			return true;
//		}
//	}
//	return false;
//}

bool
CHTItemParamTable::HT_bGetItemLevel( byte* pbyteLevel )
{
	if ( m_pParam )
	{
		*pbyteLevel = m_pParam->byteLevel;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemName( CHTString* pstrName )
{
	if( m_pParam )
	{
		*pstrName = m_pParam->szName;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemDescription( CHTString* pstrDescription )
{
	if( m_pParam )
	{
		*pstrDescription = m_pParam->szDescription;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemClass( byte* pbyteClass )
{
	if ( m_pParam )
	{
		*pbyteClass = m_pParam->byteClass;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemType( short* psType)
{
	if ( m_pParam )
	{
		*psType = m_pParam->sType;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemRupiah( int* piRupiah )
{
	if ( m_pParam )
	{
		*piRupiah = m_pParam->iRupiah;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemSellRupiah( int* piSellRupiah )
{
	if ( m_pParam )
	{
		*piSellRupiah = m_pParam->iSellRupiah;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemMaxDurability( short* psMaxDurability )
{
	if ( m_pParam )
	{
		*psMaxDurability = m_pParam->sMaxDurability;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemMaxCount( byte* pbyteMaxCount )
{
	if ( m_pParam )
	{
		*pbyteMaxCount = m_pParam->byteMaxCount;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemCombatPhase( short* psCombatPhase )
{
	if ( m_pParam )
	{
		*psCombatPhase = m_pParam->sCombatPhase;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate )
{
	if ( m_pParam )
	{
		*psSkillCastingTimeRate = m_pParam->sSkillCastingTimeRate;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1ID( int* piEffect1ID )
{
	if ( m_pParam )
	{
		*piEffect1ID = m_pParam->iEffect1ID;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Function( int* piEffect1Function )
{
	if ( m_pParam )
	{
		*piEffect1Function = m_pParam->iEffect1Function;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParam )
	{
		*piEffect1Duration = m_pParam->iEffect1Duration;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParam )
	{
		*piEffect1Param1 = m_pParam->iEffect1Param1;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParam )
	{
		*piEffect1Param2 = m_pParam->iEffect1Param2;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2ID( int* piEffect2ID )
{
	if ( m_pParam )
	{
		*piEffect2ID = m_pParam->iEffect2ID;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Function( int* piEffect2Function )
{
	if ( m_pParam )
	{
		*piEffect2Function = m_pParam->iEffect2Function;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParam )
	{
		*piEffect2Duration = m_pParam->iEffect2Duration;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParam )
	{
		*piEffect2Param1 = m_pParam->iEffect2Param1;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParam )
	{
		*piEffect2Param2 = m_pParam->iEffect2Param2;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3ID( int* piEffect3ID )
{
	if ( m_pParam )
	{
		*piEffect3ID = m_pParam->iEffect3ID;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Function( int* piEffect3Function )
{
	if ( m_pParam )
	{
		*piEffect3Function = m_pParam->iEffect3Function;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParam )
	{
		*piEffect3Duration = m_pParam->iEffect3Duration;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParam )
	{
		*piEffect3Param1 = m_pParam->iEffect3Param1;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParam )
	{
		*piEffect3Param2 = m_pParam->iEffect3Param2;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4ID( int* piEffect4ID )
{
	if ( m_pParam )
	{
		*piEffect4ID = m_pParam->iEffect4ID;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Function( int* piEffect4Function )
{
	if ( m_pParam )
	{
		*piEffect4Function = m_pParam->iEffect4Function;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParam )
	{
		*piEffect4Duration = m_pParam->iEffect4Duration;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParam )
	{
		*piEffect4Param1 = m_pParam->iEffect4Param1;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParam )
	{
		*piEffect4Param2 = m_pParam->iEffect4Param2;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5ID( int* piEffect5ID )
{
	if ( m_pParam )
	{
		*piEffect5ID = m_pParam->iEffect5ID;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Function( int* piEffect5Function )
{
	if ( m_pParam )
	{
		*piEffect5Function = m_pParam->iEffect5Function;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParam )
	{
		*piEffect5Duration = m_pParam->iEffect5Duration;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParam )
	{
		*piEffect5Param1 = m_pParam->iEffect5Param1;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParam )
	{
		*piEffect5Param2 = m_pParam->iEffect5Param2;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParam )
	{
		*piCoolDownTime = m_pParam->iCoolDownTime;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemRange( byte* pbyteRange )
{
	if ( m_pParam )
	{
		*pbyteRange = m_pParam->byteRange;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemArmorType( byte* pbyteArmorType )
{
	if ( m_pParam )
	{
		*pbyteArmorType = m_pParam->byteArmorType;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemAttackType( byte* pbyteAttackType )
{
	if ( m_pParam )
	{
		*pbyteAttackType = m_pParam->byteAttackType;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCostTP( int* piCostTP )
{
	if ( m_pParam )
	{
		*piCostTP = m_pParam->iCostTP;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemCostHP( int* piCostHP )
{
	if ( m_pParam )
	{
		*piCostHP = m_pParam->iCostHP;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemidCostItem( int* pidCostItem )
{
	if ( m_pParam )
	{
		*pidCostItem = m_pParam->idCostItem;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti )
{
	if ( m_pParam )
	{
		*piLimitTrimuriti = m_pParam->iLimitTrimuriti;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitTribe( int* piLimitTribe )
{
	if ( m_pParam )
	{
		*piLimitTribe = m_pParam->iLimitTribe;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitLevel( byte* pbyteLimitLevel )
{
	if ( m_pParam )
	{
		*pbyteLimitLevel = m_pParam->byteLimitLevel;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra )
{
	if ( m_pParam )
	{
		*psLimitMusclechakra = m_pParam->sLimitMusclechakra;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra )
{
	if ( m_pParam )
	{
		*psLimitNerveChakra = m_pParam->sLimitNerveChakra;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra )
{
	if ( m_pParam )
	{
		*psLimitHeartChakra = m_pParam->sLimitHeartChakra;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra )
{
	if ( m_pParam )
	{
		*psLimitSoulChakra = m_pParam->sLimitSoulChakra;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemRefinableItemType( int* piRefinableItemType )
{
	if ( m_pParam )
	{
		*piRefinableItemType = m_pParam->iRefinableItemType;
		return true;
	}
	else return false;
}

bool
CHTItemParamTable::HT_bGetItemCash( int* piCash )
{
	if ( m_pParam )
	{
		*piCash = m_pParam->iCash;
		return true;
	}
	return false;
}

bool
CHTItemParamTable::HT_bGetItemTimeLimit( short* psTimeLimit )
{
	if ( m_pParam )
	{
		*psTimeLimit = m_pParam->sTimeLimit;
		return true;
	}
	return false;
}

/*bool
CHTItemParamTable::HT_bGetItemFXEffectID( int* piFXID )
{
	if ( m_pParam )
	{
		*piFXID = m_pParam->idFX;
		return true;
	}
	return false;
}
*/
//bool
//CHTItemParamTable::HT_bGetItemEventID( short* psEventID )
//{
//	if ( m_pParam )
//	{
//		*psEventID = m_pParam->sEventID;
//		return true;
//	}
//	else return false;
//}
CHTNPCParamTable::CHTNPCParamTable() : m_pParam (0) {}

CHTNPCParamTable::~CHTNPCParamTable()
{
	HTNPCParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool
CHTNPCParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTNPCParam_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );
		
		++itTable;
	}

	return true;
}

bool
CHTNPCParamTable::HT_bLockID( const int id, const byte iLevel )
{
	if( m_pParam != NULL )
		return false;

	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			m_pParam = itTable->second;
			return true;
		}
	}
	return false;
}

bool
CHTNPCParamTable::HT_bUnLockID( const int id, const byte iLevel )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // 포인터끼리 비교를 하다니.. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}

// Load & Save
bool
CHTNPCParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTNPCParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTNPCParam;

		HT_LOADCELL( _T("ID"),			iID,					int );
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szName");
		else
			strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );

		HT_LOADCELL( _T("byteSize"), 	pRecord->byteSize,		byte );
		HT_LOADCELL( _T("byteZone"), 	pRecord->byteZone,		byte );
		HT_LOADCELL( _T("sPosX"), 		pRecord->sPosX,			short );
		HT_LOADCELL( _T("sPosZ"), 		pRecord->sPosZ,			short );

		int iNumItem = 0;
		for ( int j = 0; j < HT_NPC_SELLING_ITEM_MAX; ++j )
		{
			CHTString strItem;
			strItem.HT_szFormat( "idItem%d", j );
			HT_LOADCELL( strItem, pRecord->arridItem[j], int );

			if ( pRecord->arridItem[j] > 0 )
			{
				++iNumItem;
			}
			else
			{
				pRecord->iNumItem = iNumItem;
				break;
			}
		}
		if( j == HT_NPC_SELLING_ITEM_MAX )
			pRecord->iNumItem = HT_NPC_SELLING_ITEM_MAX;

		HT_LOADCELL( _T("idItem49"), 		pRecord->byteNPCTrimuriti,	byte );

		m_mapTable.insert( HTNPCParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTNPCParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTNPCParam* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTNPCParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTNPCParam) );

		m_mapTable.insert( HTNPCParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTNPCParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTNPCParam_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTNPCParam) );

		itTable++;
	}

	return true;
}

bool
CHTNPCParamTable::HT_bGetNPCName( const int id, CHTString* pstrName )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCSize( const int id, byte* pbyteSize )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSize = (itTable->second)->byteSize;
			return true;
		}
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCZone( const int id, byte* pbyteZone )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteZone = (itTable->second)->byteZone;
			return true;
		}
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psPosX = (itTable->second)->sPosX;
			*psPosZ = (itTable->second)->sPosZ;
			return true;
		}
	}
	return false;
}


bool
CHTNPCParamTable::HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyNPCTrimuriti = (itTable->second)->byteNPCTrimuriti;
			return true;
		}
	}
	return false;
}

int
CHTNPCParamTable::HT_iGetNPCSellingItemCount( const int id )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			return (itTable->second)->iNumItem;
		}
	}
	return -1;
}

bool
CHTNPCParamTable::HT_bGetNPCSellingItem( const int id, const int index, int* pidItem )
{
	HTNPCParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( index >= 0 && index < (itTable->second)->iNumItem )
			{
				*pidItem = (itTable->second)->arridItem[index];
				return true;
			}			
		}
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCName( CHTString* pstrName )
{
	if ( m_pParam )
	{
		*pstrName = m_pParam->szName;
		return true;
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCSize( byte* pbyteSize )
{
	if ( m_pParam )
	{
		*pbyteSize = m_pParam->byteSize;
		return true;
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCZone( byte* pbyteZone )
{
	if ( m_pParam )
	{
		*pbyteZone = m_pParam->byteZone;
		return true;
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCPosition( short* psPosX, short* psPosZ )
{
	if ( m_pParam )
	{
		*psPosX = m_pParam->sPosX;
		*psPosZ = m_pParam->sPosZ;
		return true;
	}
	return false;
}

bool
CHTNPCParamTable::HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti )
{
	if ( m_pParam )
	{
		*pbyNPCTrimuriti = m_pParam->byteNPCTrimuriti;
		return true;
	}
	return false;
}

int
CHTNPCParamTable::HT_iGetNPCSellingItemCount()
{
	if ( m_pParam )
	{
		return m_pParam->iNumItem;
	}
	return -1;
}

bool
CHTNPCParamTable::HT_bGetNPCSellingItem( const int index, int* pidItem )
{
	if ( m_pParam )
	{
		if ( index >= 0 && index < m_pParam->iNumItem )
		{
			*pidItem = m_pParam->arridItem[index];
			return true;
		}
	}
	return false;
}

CHTPortalParamTable::CHTPortalParamTable() : m_pParam (0) {}

CHTPortalParamTable::~CHTPortalParamTable()
{
	HTPortalParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool
CHTPortalParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTPortalParam_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );
		
		++itTable;
	}

	return true;
}

// Load & Save
bool
CHTPortalParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTPortalParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTPortalParam;

		HT_LOADCELL( _T("ID"),					iID,					int );

        //strCell = _T("szName");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szName");
		else
			strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );

		HT_LOADCELL( _T("dwServerID"), 		pRecord->dwServerID,		DWORD );
		HT_LOADCELL( _T("dwZoneLevel"), 	pRecord->dwZoneLevel,		DWORD );
		HT_LOADCELL( _T("sStartX"), 		pRecord->sStartX,			short );
		HT_LOADCELL( _T("sStartZ"),			pRecord->sStartZ,			short );
		HT_LOADCELL( _T("sEndX"), 			pRecord->sEndX,				short );
		HT_LOADCELL( _T("sEndZ"), 			pRecord->sEndZ,				short );
		HT_LOADCELL( _T("iGoPortal1"), 		pRecord->iGoPortal[0],		int );
		HT_LOADCELL( _T("iGoPortal2"), 		pRecord->iGoPortal[1],		int );
		HT_LOADCELL( _T("iGoPortal3"),		pRecord->iGoPortal[2],		int	);
		HT_LOADCELL( _T("iGoPortal4"),		pRecord->iGoPortal[3],		int	);
		HT_LOADCELL( _T("iGoPortal5"),		pRecord->iGoPortal[4],		int	);
		HT_LOADCELL( _T("dwFee1"),			pRecord->dwFee[0],			DWORD );
		HT_LOADCELL( _T("dwFee2"),			pRecord->dwFee[1],			DWORD );
		HT_LOADCELL( _T("dwFee3"),			pRecord->dwFee[2],			DWORD );
		HT_LOADCELL( _T("dwFee4"),			pRecord->dwFee[3],			DWORD );
		HT_LOADCELL( _T("dwFee5"),			pRecord->dwFee[4],			DWORD );
		HT_LOADCELL( _T("dwLevel1"),		pRecord->dwLevel[0],		DWORD );
		HT_LOADCELL( _T("dwLevel2"),		pRecord->dwLevel[1],		DWORD );
		HT_LOADCELL( _T("dwLevel3"),		pRecord->dwLevel[2],		DWORD );
		HT_LOADCELL( _T("dwLevel4"),		pRecord->dwLevel[3],		DWORD );
		HT_LOADCELL( _T("dwLevel5"),		pRecord->dwLevel[4],		DWORD );

		m_mapTable.insert( HTPortalParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTPortalParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTPortalParam* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTPortalParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTPortalParam) );

		m_mapTable.insert( HTPortalParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTPortalParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTPortalParam_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTPortalParam) );

		itTable++;
	}

	return true;
}

bool
CHTPortalParamTable::HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel)
{
	HTPortalParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pdwFee = (itTable->second)->dwFee[iNo];
			*pdwLevel = (itTable->second)->dwLevel[iNo];
			*piGoPortal = (itTable->second)->iGoPortal[iNo];
			return true;
		}
	}
	return false;
}

bool
CHTPortalParamTable::HT_bGetPortalName( const int id, CHTString* pstrName)
{
	HTPortalParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTPortalParamTable::HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
										short* psStartX, short* psStartZ, short* psEndX, short* psEndZ)
{
	HTPortalParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pdwServerID = (itTable->second)->dwServerID;
			*pdwZoneLevel = (itTable->second)->dwZoneLevel;
			*psStartX = (itTable->second)->sStartX;
			*psStartZ = (itTable->second)->sStartZ;
			*psEndX = (itTable->second)->sEndX;
			*psEndZ = (itTable->second)->sEndZ;
			return true;
		}
	}
	return false;
}

bool
CHTPortalParamTable::HT_bGetPortalFee( const int idFromPortal, const int idToPortal, DWORD* pdwFee )
{
	HTPortalParam_It itTable = m_mapTable.find( idFromPortal );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			for ( int i=0; i<5; ++i )
			{
				if ( (itTable->second)->iGoPortal[i] == idToPortal )
				{
					*pdwFee = (itTable->second)->dwFee[i];
					return true;
				}
			}
		}
	}
	return false;
}

bool
CHTPortalParamTable::HT_bGetPortalLevel( const int idFromPortal, const int idToPortal, DWORD* pdwLevel)
{
	HTPortalParam_It itTable = m_mapTable.find( idFromPortal );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			for ( int i=0; i<5; ++i )
			{
				if ( (itTable->second)->iGoPortal[i] == idToPortal )
				{
					*pdwLevel = (itTable->second)->dwLevel[i];
					return true;
				}
			}
		}
	}
	return false;
}

CHTTaskQuestParamTable::CHTTaskQuestParamTable() : m_pParam (0) {}

CHTTaskQuestParamTable::~CHTTaskQuestParamTable()
{
	HTTaskQuestParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool
CHTTaskQuestParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTTaskQuestParam_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );
		
		++itTable;
	}

	return true;
}

bool
CHTTaskQuestParamTable::HT_bLockID( const int id, const byte iLevel )
{
	if( m_pParam != NULL )
		return false;

	HTTaskQuestParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			m_pParam = itTable->second;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bUnLockID( const int id, const byte iLevel )
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // 포인터끼리 비교를 하다니.. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}

// Load & Save
bool
CHTTaskQuestParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTTaskQuestParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTTaskQuestParam;

		HT_LOADCELL( _T("ID"),					iID,						int );

 		HT_LOADCELL( _T("sNPCID1"), 			pRecord->sNPCID1,			short );
		HT_LOADCELL( _T("sNPCID2"), 			pRecord->sNPCID2,			short );
		HT_LOADCELL( _T("sNPCID3"), 			pRecord->sNPCID3,			short );
		HT_LOADCELL( _T("sNPCID4"), 			pRecord->sNPCID4,			short );
		HT_LOADCELL( _T("sNPCID5"), 			pRecord->sNPCID5,			short );

		HT_LOADCELL( _T("byteSourceType1"), 	pRecord->byteSourceType1,	byte );
		HT_LOADCELL( _T("sSourceItemID1"),		pRecord->sSourceItemID1,	short );
		HT_LOADCELL( _T("iSourceCount1"), 		pRecord->iSourceCount1,		int );
		HT_LOADCELL( _T("byteSourceType2"), 	pRecord->byteSourceType2,	byte );
		HT_LOADCELL( _T("sSourceItemID2"),		pRecord->sSourceItemID2,	short );
		HT_LOADCELL( _T("iSourceCount2"), 		pRecord->iSourceCount2,		int );
		HT_LOADCELL( _T("byteSourceType3"), 	pRecord->byteSourceType3,	byte );
		HT_LOADCELL( _T("sSourceItemID3"),		pRecord->sSourceItemID3,	short );
		HT_LOADCELL( _T("iSourceCount3"), 		pRecord->iSourceCount3,		int );
		HT_LOADCELL( _T("byteSourceType4"), 	pRecord->byteSourceType4,	byte );
		HT_LOADCELL( _T("sSourceItemID4"),		pRecord->sSourceItemID4,	short );
		HT_LOADCELL( _T("iSourceCount4"), 		pRecord->iSourceCount4,		int );
		HT_LOADCELL( _T("byteSourceType5"), 	pRecord->byteSourceType5,	byte );
		HT_LOADCELL( _T("sSourceItemID5"),		pRecord->sSourceItemID5,	short );
		HT_LOADCELL( _T("iSourceCount5"), 		pRecord->iSourceCount5,		int );
		HT_LOADCELL( _T("byteSourceType6"), 	pRecord->byteSourceType6,	byte );
		HT_LOADCELL( _T("sSourceItemID6"),		pRecord->sSourceItemID6,	short );
		HT_LOADCELL( _T("iSourceCount6"), 		pRecord->iSourceCount6,		int );

		HT_LOADCELL( _T("byteRewardPriority1"),	pRecord->byteRewardPriority1,byte );
		HT_LOADCELL( _T("byteRewardType1"), 	pRecord->byteRewardType1,	byte );
		HT_LOADCELL( _T("sReward1Rate"), 		pRecord->sReward1Rate,		short );
		HT_LOADCELL( _T("sRewardItemID1"),		pRecord->sRewardItemID1,	short );
		HT_LOADCELL( _T("iRewardCount1"), 		pRecord->iRewardCount1,		int );
		HT_LOADCELL( _T("byteRewardPriority2"),	pRecord->byteRewardPriority2,byte );
		HT_LOADCELL( _T("byteRewardType2"), 	pRecord->byteRewardType2,	byte );
		HT_LOADCELL( _T("sReward2Rate"), 		pRecord->sReward2Rate,		short );
		HT_LOADCELL( _T("sRewardItemID2"),		pRecord->sRewardItemID2,	short );
		HT_LOADCELL( _T("iRewardCount2"), 		pRecord->iRewardCount2,		int );
		HT_LOADCELL( _T("byteRewardPriority3"),	pRecord->byteRewardPriority3,byte );
		HT_LOADCELL( _T("byteRewardType3"), 	pRecord->byteRewardType3,	byte );
		HT_LOADCELL( _T("sReward3Rate"), 		pRecord->sReward3Rate,		short );
		HT_LOADCELL( _T("sRewardItemID3"),		pRecord->sRewardItemID3,	short );
		HT_LOADCELL( _T("iRewardCount3"), 		pRecord->iRewardCount3,		int );
		HT_LOADCELL( _T("byteRewardPriority4"),	pRecord->byteRewardPriority4,byte );
		HT_LOADCELL( _T("byteRewardType4"), 	pRecord->byteRewardType4,	byte );
		HT_LOADCELL( _T("sReward4Rate"), 		pRecord->sReward4Rate,		short );
		HT_LOADCELL( _T("sRewardItemID4"),		pRecord->sRewardItemID4,	short );
		HT_LOADCELL( _T("iRewardCount4"), 		pRecord->iRewardCount4,		int );
		HT_LOADCELL( _T("byteRewardPriority5"),	pRecord->byteRewardPriority5,byte );
		HT_LOADCELL( _T("byteRewardType5"), 	pRecord->byteRewardType5,	byte );
		HT_LOADCELL( _T("sReward5Rate"), 		pRecord->sReward5Rate,		short );
		HT_LOADCELL( _T("sRewardItemID5"),		pRecord->sRewardItemID5,	short );
		HT_LOADCELL( _T("iRewardCount5"), 		pRecord->iRewardCount5,		int );

		HT_LOADCELL( _T("byteMinLevel"), 		pRecord->byteMinLevel,		byte );
		HT_LOADCELL( _T("byteMaxLevel"), 		pRecord->byteMaxLevel,		byte );

		m_mapTable.insert( HTTaskQuestParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTTaskQuestParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTTaskQuestParam* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTTaskQuestParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTTaskQuestParam) );

		m_mapTable.insert( HTTaskQuestParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTTaskQuestParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTTaskQuestParam_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTTaskQuestParam) );

		itTable++;
	}

	return true;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2,
												short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psNPCID1 = (itTable->second)->sNPCID1;
			*psNPCID2 = (itTable->second)->sNPCID2;
			*psNPCID3 = (itTable->second)->sNPCID3;
			*psNPCID4 = (itTable->second)->sNPCID4;
			*psNPCID5 = (itTable->second)->sNPCID5;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource1( const int id, /*short* psNPCID, */byte* pbyteSourceType1, 
																short* psSourceItemID1, int* piSourceCount1)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType1 = (itTable->second)->byteSourceType1;
			*psSourceItemID1 = (itTable->second)->sSourceItemID1;
			*piSourceCount1 = (itTable->second)->iSourceCount1;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource2( const int id, /*short* psNPCID, */byte* pbyteSourceType2, 
																short* psSourceItemID2, int* piSourceCount2)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType2 = (itTable->second)->byteSourceType2;
			*psSourceItemID2 = (itTable->second)->sSourceItemID2;
			*piSourceCount2 = (itTable->second)->iSourceCount2;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource3( const int id, /*short* psNPCID, */byte* pbyteSourceType3, 
																short* psSourceItemID3, int* piSourceCount3)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType3 = (itTable->second)->byteSourceType3;
			*psSourceItemID3 = (itTable->second)->sSourceItemID3;
			*piSourceCount3 = (itTable->second)->iSourceCount3;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource4( const int id, /*short* psNPCID, */byte* pbyteSourceType4, 
																short* psSourceItemID4, int* piSourceCount4)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType4 = (itTable->second)->byteSourceType4;
			*psSourceItemID4 = (itTable->second)->sSourceItemID4;
			*piSourceCount4 = (itTable->second)->iSourceCount4;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, 
																short* psSourceItemID5, int* piSourceCount5)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType5 = (itTable->second)->byteSourceType5;
			*psSourceItemID5 = (itTable->second)->sSourceItemID5;
			*piSourceCount5 = (itTable->second)->iSourceCount5;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, 
																short* psSourceItemID6, int* piSourceCount6)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteSourceType6 = (itTable->second)->byteSourceType6;
			*psSourceItemID6 = (itTable->second)->sSourceItemID6;
			*piSourceCount6 = (itTable->second)->iSourceCount6;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, 
										   short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteRewardPriority1 = (itTable->second)->byteRewardPriority1;
			*pbyteRewardType1 = (itTable->second)->byteRewardType1;
			*psReward1Rate = (itTable->second)->sReward1Rate;
			*psRewardItemID1 = (itTable->second)->sRewardItemID1;
			*piRewardCount1 = (itTable->second)->iRewardCount1;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, 
										   short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteRewardPriority2 = (itTable->second)->byteRewardPriority2;
			*pbyteRewardType2 = (itTable->second)->byteRewardType2;
			*psReward2Rate = (itTable->second)->sReward2Rate;
			*psRewardItemID2 = (itTable->second)->sRewardItemID2;
			*piRewardCount2 = (itTable->second)->iRewardCount2;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3,
										   short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteRewardPriority3 = (itTable->second)->byteRewardPriority3;
			*pbyteRewardType3 = (itTable->second)->byteRewardType3;
			*psReward3Rate = (itTable->second)->sReward3Rate;
			*psRewardItemID3 = (itTable->second)->sRewardItemID3;
			*piRewardCount3 = (itTable->second)->iRewardCount3;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4,
										   short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteRewardPriority4 = (itTable->second)->byteRewardPriority4;
			*pbyteRewardType4 = (itTable->second)->byteRewardType4;
			*psReward4Rate = (itTable->second)->sReward4Rate;
			*psRewardItemID4 = (itTable->second)->sRewardItemID4;
			*piRewardCount4 = (itTable->second)->iRewardCount4;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5,
										   short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*pbyteRewardPriority5 = (itTable->second)->byteRewardPriority5;
			*pbyteRewardType5 = (itTable->second)->byteRewardType5;
			*psReward5Rate = (itTable->second)->sReward5Rate;
			*psRewardItemID5 = (itTable->second)->sRewardItemID5;
			*piRewardCount5 = (itTable->second)->iRewardCount5;
			return true;
		}
	}
	return false;
}

bool 
CHTTaskQuestParamTable::HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel)
{
	HTTaskQuestParam_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//*psNPCID = (itTable->second)->sNPCID;
			*byteMinLevel = (itTable->second)->byteMinLevel;
			*byteMaxLevel = (itTable->second)->byteMaxLevel;
			return true;
		}
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	if ( m_pParam )
	{
		*psNPCID1 = m_pParam->sNPCID1;
		*psNPCID2 = m_pParam->sNPCID2;
		*psNPCID3 = m_pParam->sNPCID3;
		*psNPCID4 = m_pParam->sNPCID4;
		*psNPCID5 = m_pParam->sNPCID5;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType1 = m_pParam->byteSourceType1;
		*psSourceItemID1 = m_pParam->sSourceItemID1;
		*piSourceCount1 = m_pParam->iSourceCount1;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource2( /*short* psNPCID, */byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType2 = m_pParam->byteSourceType2;
		*psSourceItemID2 = m_pParam->sSourceItemID2;
		*piSourceCount2 = m_pParam->iSourceCount2;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource3( /*short* psNPCID, */byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType3 = m_pParam->byteSourceType3;
		*psSourceItemID3 = m_pParam->sSourceItemID3;
		*piSourceCount3 = m_pParam->iSourceCount3;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource4( /*short* psNPCID, */byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType4 = m_pParam->byteSourceType4;
		*psSourceItemID4 = m_pParam->sSourceItemID4;
		*piSourceCount4 = m_pParam->iSourceCount4;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource5( /*short* psNPCID, */byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType5 = m_pParam->byteSourceType5;
		*psSourceItemID5 = m_pParam->sSourceItemID5;
		*piSourceCount5 = m_pParam->iSourceCount5;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskSource6( /*short* psNPCID, */byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteSourceType6 = m_pParam->byteSourceType6;
		*psSourceItemID6 = m_pParam->sSourceItemID6;
		*piSourceCount6 = m_pParam->iSourceCount6;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward1( /*short* psNPCID, */byte* pbyteRewardPriority1, byte* pbyteRewardType1,
										   short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteRewardPriority1 = m_pParam->byteRewardPriority1;
		*pbyteRewardType1 = m_pParam->byteRewardType1;
		*psReward1Rate = m_pParam->sReward1Rate;
		*psRewardItemID1 = m_pParam->sRewardItemID1;
		*piRewardCount1 = m_pParam->iRewardCount1;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward2( /*short* psNPCID, */byte* pbyteRewardPriority2, byte* pbyteRewardType2,
										   short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteRewardPriority2 = m_pParam->byteRewardPriority2;
		*pbyteRewardType2 = m_pParam->byteRewardType2;
		*psReward2Rate = m_pParam->sReward2Rate;
		*psRewardItemID2 = m_pParam->sRewardItemID2;
		*piRewardCount2 = m_pParam->iRewardCount2;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward3( /*short* psNPCID, */byte* pbyteRewardPriority3, byte* pbyteRewardType3,
										   short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteRewardPriority3 = m_pParam->byteRewardPriority3;
		*pbyteRewardType3 = m_pParam->byteRewardType3;
		*psReward3Rate = m_pParam->sReward3Rate;
		*psRewardItemID3 = m_pParam->sRewardItemID3;
		*piRewardCount3 = m_pParam->iRewardCount3;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward4( /*short* psNPCID, */byte* pbyteRewardPriority4, byte* pbyteRewardType4,
										   short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteRewardPriority4 = m_pParam->byteRewardPriority4;
		*pbyteRewardType4 = m_pParam->byteRewardType4;
		*psReward4Rate = m_pParam->sReward4Rate;
		*psRewardItemID4 = m_pParam->sRewardItemID4;
		*piRewardCount4 = m_pParam->iRewardCount4;
		return true;
	}
	return false;
}

bool
CHTTaskQuestParamTable::HT_bGetTaskReward5( /*short* psNPCID, */byte* pbyteRewardPriority5, byte* pbyteRewardType5,
										   short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*pbyteRewardPriority5 = m_pParam->byteRewardPriority5;
		*pbyteRewardType5 = m_pParam->byteRewardType5;
		*psReward5Rate = m_pParam->sReward5Rate;
		*psRewardItemID5 = m_pParam->sRewardItemID5;
		*piRewardCount5 = m_pParam->iRewardCount5;
		return true;
	}
	return false;
}


bool 
CHTTaskQuestParamTable::HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel)
{
	if ( m_pParam )
	{
		//*psNPCID = m_pParam->sNPCID;
		*byteMinLevel = m_pParam->byteMinLevel;
		*byteMaxLevel = m_pParam->byteMaxLevel;
		return true;
	}
	return false;
}


// 지역표시
CHTAreaIndicateParamTable::CHTAreaIndicateParamTable()
{
}

CHTAreaIndicateParamTable::~CHTAreaIndicateParamTable()
{
	HTAreaIndicate_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

bool
CHTAreaIndicateParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTAreaIndicate_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel>::value_type( oIDLevel ) );
		
		++itTable;
	}

	return true;
}

bool
CHTAreaIndicateParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTAreaIndicate* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTAreaIndicate;

		HT_LOADCELL( _T("ID"),			iID,					int );
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szName");
		else
			strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );

		HT_LOADCELL( _T("dwFrom"), 		pRecord->dwFrom,		DWORD );
		HT_LOADCELL( _T("dwTo"), 		pRecord->dwTo,			DWORD );

		m_mapTable.insert( HTAreaIndicate_Value( iID, pRecord ) );
	}

	return ( true );
}

bool	
CHTAreaIndicateParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTAreaIndicate* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTAreaIndicate;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTAreaIndicate) );

		m_mapTable.insert( HTAreaIndicate_Value( iID, pRecord ) );
	}

	return true;
}

bool	
CHTAreaIndicateParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTAreaIndicate_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTAreaIndicate) );

		itTable++;
	}

	return true;
}

bool 
CHTAreaIndicateParamTable::HT_bGetAreaName( const int id, CHTString* pstrName )
{
	HTAreaIndicate_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrName = (itTable->second)->szName;
			return true;
		}
	}
	return false;
}

bool
CHTAreaIndicateParamTable::HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName )
{
	HTAreaIndicate_It itTable = m_mapTable.begin();

	while ( itTable!= m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( (itTable->second)->dwFrom==dwFrom && (itTable->second)->dwTo==dwTo )
			{
				*pstrName = (itTable->second)->szName;
				return true;
			}
		}
		++itTable;
	}
	return false;
}

bool		
CHTAreaIndicateParamTable::HT_bGetAreaFrom( const int id, DWORD* pdwFromID )
{
	HTAreaIndicate_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pdwFromID = (itTable->second)->dwFrom;
			return true;
		}
		++itTable;
	}

	return false;
}

bool
CHTAreaIndicateParamTable::HT_bGetAreaTo( const int id, DWORD* pdwToID )
{
	HTAreaIndicate_It itTable = m_mapTable.find( id );
	
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pdwToID = (itTable->second)->dwTo;
			return true;
		}
		++itTable;
	}

	return false;
}

CHTClientParamMgr::CHTClientParamMgr():m_pParamTable(0)
{
	for( int i = 0 ; i < HT_CLI_PARAMTYPE_END ; ++i )
		m_arrParamTable[i] = 0;
}

CHTClientParamMgr::~CHTClientParamMgr()
{
	for( int i = 0 ; i < HT_CLI_PARAMTYPE_END ; ++i )
		delete m_arrParamTable[i];

	m_vectorPCSkillIDLevelNagKin.clear();
	m_vectorPCSkillIDLevelAsuRak.clear();
	m_vectorPCSkillIDLevelDevGar.clear();
	m_vectorPCSkillIDLevelYakGan.clear();
	m_vectorPCSkillIDLevelEtc.clear();
	m_vectorNPCIDLevel.clear();
}

bool
CHTClientParamMgr::HT_bLockID( const int id, const byte iLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable )
	{
		m_pParamTable = pParamTable;
		return m_pParamTable->HT_bLockID( id, iLevel );
	}
	else return false;
}

bool
CHTClientParamMgr::HT_bUnLockID( const int id, const byte iLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( m_pParamTable == pParamTable ) // 포인터 끼리 또 비교를.. -_-
	{
		m_pParamTable->HT_bUnLockID( id, iLevel );
		m_pParamTable = NULL;
	}
	return false;
}

bool
CHTClientParamMgr::HT_bLoadXML( CHTString& strFile )
{
	bool bReturn = true;
	CHTString strTable;
	CHTXMLParser oXML;

	if ( HT_FAILED( oXML.HT_hrOpen( strFile ) ) ) return false;

	strTable = _T("Monster");
	m_arrParamTable[HT_PARAMTYPE_MONSTER] = new CHTMonsterParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("MonsterSkill");
	m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL] = new CHTMonsterParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("PCSkill");
	m_arrParamTable[HT_PARAMTYPE_PCSKILL] = new CHTPCSkillParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Item");
	m_arrParamTable[HT_PARAMTYPE_ITEM] = new CHTItemParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("NPC");
	m_arrParamTable[HT_PARAMTYPE_NPC] = new CHTNPCParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Portal");
	m_arrParamTable[HT_PARAMTYPE_PORTAL] = new CHTPortalParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_PORTAL]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("TaskQuest");
	m_arrParamTable[HT_PARAMTYPE_TASKQUEST] = new CHTTaskQuestParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_TASKQUEST]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("AreaIndicate");
	m_arrParamTable[HT_PARAMTYPE_AREAINDICATE] = new CHTAreaIndicateParamTable;
	if ( m_arrParamTable[HT_PARAMTYPE_AREAINDICATE]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	return bReturn;
}

bool
CHTClientParamMgr::HT_bLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return false;

	m_arrParamTable[HT_PARAMTYPE_MONSTER]		= new CHTMonsterParamTable;
	m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]	= new CHTMonsterParamTable;
	m_arrParamTable[HT_PARAMTYPE_PCSKILL]		= new CHTPCSkillParamTable;
	m_arrParamTable[HT_PARAMTYPE_ITEM]			= new CHTItemParamTable;
	m_arrParamTable[HT_PARAMTYPE_NPC]			= new CHTNPCParamTable;
	m_arrParamTable[HT_PARAMTYPE_PORTAL]		= new CHTPortalParamTable;
	m_arrParamTable[HT_PARAMTYPE_TASKQUEST]		= new CHTTaskQuestParamTable;
	m_arrParamTable[HT_PARAMTYPE_AREAINDICATE]	= new CHTAreaIndicateParamTable;

	bool bReturn = true;

	CHTString strTable;

	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PORTAL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_TASKQUEST]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_AREAINDICATE]->HT_bLoad( &oLoadFile );

	oLoadFile.HT_vClose();

	// Filll All ID for Fast 
	m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bGetAllID( &m_vectorNPCIDLevel );

	std::vector<HTIDLevel> vectorPCSkillIDLevel;
	m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bGetAllID( &vectorPCSkillIDLevel );

	int iSize = (int)vectorPCSkillIDLevel.size();
	for ( int i = 0; i < iSize; ++i )
	{
		if ( CHTParamIDCheck::HT_bIsPCSkillNagaKin( vectorPCSkillIDLevel[i].iID ) )
		{
			m_vectorPCSkillIDLevelNagKin.push_back( std::vector<HTIDLevel>::value_type( vectorPCSkillIDLevel[i] ) );

			std::vector<int>::iterator itFind;
			itFind = find(
				m_vectorPCSkillIDNagKin.begin(), m_vectorPCSkillIDNagKin.end(),
				std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
			if ( itFind != m_vectorPCSkillIDNagKin.end() ) {}
			else
				m_vectorPCSkillIDNagKin.push_back( std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
		}
		else if ( CHTParamIDCheck::HT_bIsPCSkillAsuRak( vectorPCSkillIDLevel[i].iID ) )
		{
			m_vectorPCSkillIDLevelAsuRak.push_back( std::vector<HTIDLevel>::value_type( vectorPCSkillIDLevel[i] ) );

			std::vector<int>::iterator itFind;
			itFind = find(
				m_vectorPCSkillIDAsuRak.begin(), m_vectorPCSkillIDAsuRak.end(),
				std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
			if ( itFind != m_vectorPCSkillIDAsuRak.end() ) {}
			else
				m_vectorPCSkillIDAsuRak.push_back( std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
		}
		else if ( CHTParamIDCheck::HT_bIsPCSkillDevGaru( vectorPCSkillIDLevel[i].iID ) )
		{
			m_vectorPCSkillIDLevelDevGar.push_back( std::vector<HTIDLevel>::value_type( vectorPCSkillIDLevel[i] ) );

			std::vector<int>::iterator itFind;
			itFind = find(
				m_vectorPCSkillIDDevGar.begin(), m_vectorPCSkillIDDevGar.end(),
				std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
			if ( itFind != m_vectorPCSkillIDDevGar.end() ) {}
			else
				m_vectorPCSkillIDDevGar.push_back( std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
		}
		else if ( CHTParamIDCheck::HT_bIsPCSkillYakGan( vectorPCSkillIDLevel[i].iID ) )
		{
			m_vectorPCSkillIDLevelYakGan.push_back( std::vector<HTIDLevel>::value_type( vectorPCSkillIDLevel[i] ) );

			std::vector<int>::iterator itFind;
			itFind = find(
				m_vectorPCSkillIDYakGan.begin(), m_vectorPCSkillIDYakGan.end(),
				std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
			if ( itFind != m_vectorPCSkillIDYakGan.end() ) {}
			else
				m_vectorPCSkillIDYakGan.push_back( std::vector<int>::value_type( vectorPCSkillIDLevel[i].iID ) );
		}
		else
		{
			m_vectorPCSkillIDLevelEtc.push_back( std::vector<HTIDLevel>::value_type( vectorPCSkillIDLevel[i] ) );
		}
	}

	vectorPCSkillIDLevel.clear();
	// Filll All ID for Fast 

	std::sort( m_vectorPCSkillIDNagKin.begin(), m_vectorPCSkillIDNagKin.end() );
	std::sort( m_vectorPCSkillIDAsuRak.begin(), m_vectorPCSkillIDAsuRak.end() );
	std::sort( m_vectorPCSkillIDDevGar.begin(), m_vectorPCSkillIDDevGar.end() );
	std::sort( m_vectorPCSkillIDYakGan.begin(), m_vectorPCSkillIDYakGan.end() );

	return bReturn;
}
 
bool
CHTClientParamMgr::HT_bSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
		return false;

	bool bReturn = true;

	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PORTAL]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_TASKQUEST]->HT_bSave( &oSaveFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_AREAINDICATE]->HT_bSave( &oSaveFile );

	oSaveFile.HT_vClose();

	return bReturn;
}

bool
CHTClientParamMgr::HT_bTestSave( CHTString& strFile )
{
	FILE* pFile;
	if ( pFile = fopen( (HTtchar*)strFile, "wt" ) )
	{
		
		int index;
		int id;
		byte byteLevel;

		std::vector<HTIDLevel> vectorIDLevel;
		vector<HTIDLevel>::iterator vec_It;

		for( int i = 1 ; i < HT_CLI_PARAMTYPE_END ; ++i )
		{
			index = 0;

			fprintf( pFile, "---------------------------------------");
			switch ( i )
			{
				case HT_PARAMTYPE_MONSTER:
					fprintf( pFile, "\nMonster" );
					break;
				case HT_PARAMTYPE_MONSTERSKILL:
					fprintf( pFile, "\nMonster Skill" );
					break;
				case HT_PARAMTYPE_PCSKILL:
					fprintf( pFile, "\nPC Skill" );
					break;
				case HT_PARAMTYPE_ITEM:
					fprintf( pFile, "\nItem" );
					break;
				case HT_PARAMTYPE_NPC:
					fprintf( pFile, "\nNPC" );
					break;
				case HT_PARAMTYPE_PORTAL:
					fprintf( pFile, "\nPortal" );
					break;
				case HT_PARAMTYPE_TASKQUEST:
					fprintf( pFile, "\nTaskQuest" );
					break;
				case HT_PARAMTYPE_AREAINDICATE:
					fprintf( pFile, "\nAreaIndicate" );
					break;
				default:
					fprintf( pFile, "\n");
					break;
			}
			fprintf( pFile, "\n---------------------------------------");

			if( m_arrParamTable[i] != 0 && m_arrParamTable[i]->HT_bGetAllID( &vectorIDLevel, i ) ) // 모든 아이디를 구함
			{
				vec_It = vectorIDLevel.begin();
				while ( vec_It != vectorIDLevel.end() )
				{
					id = vec_It->iID;
					byteLevel = vec_It->byteLevel;

					// WithID
					if( i == HT_PARAMTYPE_PCSKILL || i == HT_PARAMTYPE_MONSTERSKILL )
						fprintf( pFile, "\n    : ID(%d) Lvl(%d)", id, byteLevel );
					else
						fprintf( pFile, "\n    : ID(%d)", id );
					HT_vTestMonsterParamWithID( pFile, id );
					HT_vTestMonsterSkillParamWithID( pFile, id );
					HT_vTestPCSkillParamWithID( pFile, id, byteLevel );
					HT_vTestItemParamWithID( pFile, id );
					HT_vTestNPCParamWithID( pFile, id );
					HT_vTestPortalParam( pFile, id );
					HT_vTestTaskQuestParamWithID( pFile, id );
					HT_vTestAreaIndidcateParam( pFile, id );

					// Without ID
					if ( this->HT_bLockID( id, byteLevel ) )
					{
						if( i == HT_PARAMTYPE_PCSKILL || i == HT_PARAMTYPE_MONSTERSKILL )
							fprintf( pFile, "\n		Lock Successfully : ID(%d) Lvl(%d)", id, byteLevel );
						else
							fprintf( pFile, "\n		Lock Successfully : ID(%d)", id );
						
						HT_vTestMonsterParam( pFile );
						HT_vTestMonsterSkillParam( pFile );
						HT_vTestPCSkillParam( pFile );
						HT_vTestItemParam( pFile );	
						HT_vTestNPCParam( pFile );
						HT_vTestTaskQuestParam( pFile );

						this->HT_bUnLockID( id, byteLevel );
						fprintf( pFile, "\n		UnLock : ID(%d)", id );
					}

					fflush( pFile );

					++vec_It;
				}	//end of while
			}	// end of if(m_arrParamTable[i]->HT_bGetAllID( pvecIDLevel, i ))

			fprintf( pFile, "\n");
		}

		fclose( pFile );

		return true;
	}
	else
	{
		return false;
	}
}

void
CHTClientParamMgr::HT_vTestMonsterParamWithID( FILE* pFile, const int id )
{
	byte byteOut;
	CHTString str;

	if ( this->HT_bGetMonsterName( id, &str ) ) fprintf( pFile, "\nHT_bGetMonsterName : %s", str.HT_szGetString() );
	if ( this->HT_bGetMonsterSize( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSize : %d", byteOut );
	if ( this->HT_bGetMonsterClass( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterClass : %d", byteOut );
	if ( this->HT_bGetMonsterFly( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFly : %d", byteOut );
	if ( this->HT_bGetMonsterReserved7( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserved7 : %d", byteOut );
}

void
CHTClientParamMgr::HT_vTestMonsterParam( FILE* pFile )
{
	byte byteOut;
	CHTString str;

	if ( this->HT_bGetMonsterName( &str ) ) fprintf( pFile, "\nHT_bGetMonsterName : %s", str.HT_szGetString() );
	if ( this->HT_bGetMonsterSize( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSize : %d", byteOut );
	if ( this->HT_bGetMonsterClass( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterClass : %d", byteOut );
	if ( this->HT_bGetMonsterFly( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFly : %d", byteOut );
	if ( this->HT_bGetMonsterReserved7( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserved7 : %d", byteOut );
}

void
CHTClientParamMgr::HT_vTestMonsterSkillParamWithID( FILE* pFile, const int id )
{
	int iOut;

	if ( this->HT_bGetMonsterSkillRange( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillRange : %d", iOut );
	if ( this->HT_bGetMonsterSkillCastingTime( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingTime : %d", iOut );
}

void
CHTClientParamMgr::HT_vTestMonsterSkillParam( FILE* pFile )
{
	int iOut;

	if ( this->HT_bGetMonsterSkillRange( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillRange : %d", iOut );
	if ( this->HT_bGetMonsterSkillCastingTime( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingTime : %d", iOut );
}

void
CHTClientParamMgr::HT_vTestPCSkillParamWithID( FILE* pFile, const int id, const byte byteLevel )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetPCSkillMaxLevel( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillType : %d", byteOut );
	if ( this->HT_bGetPCSkillCombatPhase( id, byteLevel, &sOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetPCSkillDuration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillDuration : %d", iOut );
//	if ( this->HT_bGetPCSkillSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCastingSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCastingSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillFollowRange( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillFollowRange : %d", byteOut );
	if ( this->HT_bGetPCSkillPierceRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillPierceRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCoolDownTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCoolDownTime : %d", iOut );
	if ( this->HT_bGetPCSkillRange( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillRange : %d", iOut );
	if ( this->HT_bGetPCSkillAreaOfEffect( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAreaOfEffect : %d", iOut );
	if ( this->HT_bGetPCSkillAllowedTarget( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAllowedTarget : %d", iOut );
	if ( this->HT_bGetPCSkillAttackType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAttackType : %d", byteOut );
	if ( this->HT_bGetPCSkillReadyTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReadyTime : %d", iOut );
	if ( this->HT_bGetPCSkillCastingTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCastingTime : %d", iOut );
	if ( this->HT_bGetPCSkillApplyTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillApplyTime : %d", iOut );
	if ( this->HT_bGetPCSkillReqTrimuriti( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqTrimuriti : %d", iOut );
	if ( this->HT_bGetPCSkillReqTribe( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqTribe : %d", iOut );
	if ( this->HT_bGetPCSkillReqClass( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqClass : %d", iOut );
	if ( this->HT_bGetPCSkillReqWeaponType( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqWeaponType : %d", iOut );
	if ( this->HT_bGetPCSkillidReqItem( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillidReqItem : %d", iOut );
	if ( this->HT_bGetPCSkillReqLevel( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillReqSkill1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill1 : %d", iOut );
	if ( this->HT_bGetPCSkillReqSkill1_Lvl( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill1_Lvl : %d", byteOut );
	if ( this->HT_bGetPCSkillReqSkill2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill2 : %d", iOut );
	if ( this->HT_bGetPCSkillReqSkill2_Lvl( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill2_Lvl : %d", byteOut );
	if ( this->HT_bGetPCSkillEffect1ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillCostTP( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostTP : %d", iOut );
	if ( this->HT_bGetPCSkillCostHP( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostHP : %d", iOut );
	if ( this->HT_bGetPCSkillidCostItem( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillidCostItem : %d", iOut );
	if ( this->HT_bGetPCSkillCostItemCount( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostItemCount : %d", byteOut );
}

void
CHTClientParamMgr::HT_vTestPCSkillParam( FILE* pFile )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetPCSkillMaxLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillType( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillType : %d", byteOut );
	if ( this->HT_bGetPCSkillCombatPhase( &sOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetPCSkillDuration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillDuration : %d", iOut );
//	if ( this->HT_bGetPCSkillSuccessRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCastingSuccessRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCastingSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillFollowRange( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillFollowRange : %d", byteOut );
	if ( this->HT_bGetPCSkillPierceRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillPierceRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCoolDownTime( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCoolDownTime : %d", iOut );
	if ( this->HT_bGetPCSkillRange( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillRange : %d", iOut );
	if ( this->HT_bGetPCSkillAreaOfEffect( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAreaOfEffect : %d", iOut );
	if ( this->HT_bGetPCSkillAllowedTarget( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAllowedTarget : %d", iOut );
	if ( this->HT_bGetPCSkillAttackType( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAttackType : %d", byteOut );
	if ( this->HT_bGetPCSkillReadyTime( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReadyTime : %d", iOut );
	if ( this->HT_bGetPCSkillCastingTime( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCastingTime : %d", iOut );
	if ( this->HT_bGetPCSkillApplyTime( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillApplyTime : %d", iOut );
	if ( this->HT_bGetPCSkillReqTrimuriti( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqTrimuriti : %d", iOut );
	if ( this->HT_bGetPCSkillReqTribe( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqTribe : %d", iOut );
	if ( this->HT_bGetPCSkillReqClass( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqClass : %d", iOut );
	if ( this->HT_bGetPCSkillReqWeaponType( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqWeaponType : %d", iOut );
	if ( this->HT_bGetPCSkillidReqItem( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillidReqItem : %d", iOut );
	if ( this->HT_bGetPCSkillReqLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillReqSkill1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill1 : %d", iOut );
	if ( this->HT_bGetPCSkillReqSkill1_Lvl( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill1_Lvl : %d", byteOut );
	if ( this->HT_bGetPCSkillReqSkill2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill2 : %d", iOut );
	if ( this->HT_bGetPCSkillReqSkill2_Lvl( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReqSkill2_Lvl : %d", byteOut );
	if ( this->HT_bGetPCSkillEffect1ID( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Function( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect1Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect1Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2ID( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Function( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect2Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect2Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3ID( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Function( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect3Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect3Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4ID( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Function( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect4Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect4Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5ID( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5ID : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Function( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Function : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Duration : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Param1 : %d", iOut );
	if ( this->HT_bGetPCSkillEffect5Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillEffect5Param2 : %d", iOut );
	if ( this->HT_bGetPCSkillCostTP( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostTP : %d", iOut );
	if ( this->HT_bGetPCSkillCostHP( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostHP : %d", iOut );
	if ( this->HT_bGetPCSkillidCostItem( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillidCostItem : %d", iOut );
	if ( this->HT_bGetPCSkillCostItemCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCostItemCount : %d", byteOut );
}

void
CHTClientParamMgr::HT_vTestItemParamWithID(  FILE* pFile, const int id )
{
	int iOut;
	short sOut;
	byte byteOut;
	CHTString str;

	if ( this->HT_bGetItemLevel( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLevel : %d", byteOut );
	if ( this->HT_bGetItemName( id, &str ) ) fprintf( pFile, "\nHT_bGetItemName : %s", str.HT_szGetString() );
	if ( this->HT_bGetItemDescription( id, &str ) ) fprintf( pFile, "\nHT_bGetItemDescription : %s", str.HT_szGetString() );
	if ( this->HT_bGetItemClass( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemClass : %d", byteOut );
	if ( this->HT_bGetItemType( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemType : %d", sOut );
	if ( this->HT_bGetItemRupiah( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRupiah : %d", iOut );
	if ( this->HT_bGetItemSellRupiah( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemSellRupiah : %d", iOut );
	if ( this->HT_bGetItemMaxDurability( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemMaxDurability : %d", sOut );
	if ( this->HT_bGetItemMaxCount( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemMaxCount : %d", byteOut );
	if ( this->HT_bGetItemCombatPhase( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemCombatPhase : %d", sOut );
	if ( this->HT_bGetItemSkillCastingTimeRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemSkillCastingTimeRate : %d", sOut );
	if ( this->HT_bGetItemEffect1ID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1ID : %d", iOut );
	if ( this->HT_bGetItemEffect1Function( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Function : %d", iOut );
	if ( this->HT_bGetItemEffect1Duration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Duration : %d", iOut );
	if ( this->HT_bGetItemEffect1Param1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect1Param2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect2ID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2ID : %d", iOut );
	if ( this->HT_bGetItemEffect2Function( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Function : %d", iOut );
	if ( this->HT_bGetItemEffect2Duration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Duration : %d", iOut );
	if ( this->HT_bGetItemEffect2Param1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect2Param2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect3ID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3ID : %d", iOut );
	if ( this->HT_bGetItemEffect3Function( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Function : %d", iOut );
	if ( this->HT_bGetItemEffect3Duration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Duration : %d", iOut );
	if ( this->HT_bGetItemEffect3Param1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect3Param2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect4ID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4ID : %d", iOut );
	if ( this->HT_bGetItemEffect4Function( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Function : %d", iOut );
	if ( this->HT_bGetItemEffect4Duration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Duration : %d", iOut );
	if ( this->HT_bGetItemEffect4Param1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect4Param2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect5ID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5ID : %d", iOut );
	if ( this->HT_bGetItemEffect5Function( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Function : %d", iOut );
	if ( this->HT_bGetItemEffect5Duration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Duration : %d", iOut );
	if ( this->HT_bGetItemEffect5Param1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect5Param2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Param2 : %d", iOut );
	if ( this->HT_bGetItemCoolDownTime( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemCoolDownTime : %d", iOut );
	if ( this->HT_bGetItemRange( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemRange : %d", byteOut );
	if ( this->HT_bGetItemArmorType( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemArmorType : %d", byteOut );
	if ( this->HT_bGetItemAttackType( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemAttackType : %d", byteOut );
	if ( this->HT_bGetItemCostTP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemCostTP : %d", iOut );
	if ( this->HT_bGetItemCostHP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemCostHP : %d", iOut );
	if ( this->HT_bGetItemidCostItem( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemidCostItem : %d", iOut );
	if ( this->HT_bGetItemLimitTrimuriti( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemLimitTrimuriti : %d", iOut );
	if ( this->HT_bGetItemLimitTribe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemLimitTribe : %d", iOut );
	if ( this->HT_bGetItemLimitLevel( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLimitLevel : %d", byteOut );
	if ( this->HT_bGetItemLimitMuscleChakra( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitMuscleChakra : %d", sOut );
	if ( this->HT_bGetItemLimitNerveChakra( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitNerveChakra : %d", sOut );
	if ( this->HT_bGetItemLimitHeartChakra( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitHeartChakra : %d", sOut );
	if ( this->HT_bGetItemLimitSoulChakra( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitSoulChakra : %d", sOut );
	if ( this->HT_bGetItemRefinableItemType( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRefinableItemType : %d", iOut );
	if ( this->HT_bGetItemCash( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemCash : %d", iOut );
	if ( this->HT_bGetItemTimeLimit( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemTimeLimit : %d", sOut );
	//if ( this->HT_bGetItemEventID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemEventID : %d", sOut );
}

void
CHTClientParamMgr::HT_vTestItemParam( FILE* pFile )
{
	short sOut;
	byte byteOut;
	int iOut;
	CHTString str;

	if ( this->HT_bGetItemLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLevel : %d", byteOut );
	if ( this->HT_bGetItemName( &str ) ) fprintf( pFile, "\nHT_bGetItemName : %s", str.HT_szGetString() );
	if ( this->HT_bGetItemDescription( &str ) ) fprintf( pFile, "\nHT_bGetItemDescription : %s", str.HT_szGetString() );
	if ( this->HT_bGetItemClass( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemClass : %d", byteOut );
	if ( this->HT_bGetItemType( &sOut ) ) fprintf( pFile, "\nHT_bGetItemType : %d", sOut );
	if ( this->HT_bGetItemRupiah( &iOut ) ) fprintf( pFile, "\nHT_bGetItemRupiah : %d", iOut );
	if ( this->HT_bGetItemSellRupiah( &iOut ) ) fprintf( pFile, "\nHT_bGetItemSellRupiah : %d", iOut );
	if ( this->HT_bGetItemMaxDurability( &sOut ) ) fprintf( pFile, "\nHT_bGetItemMaxDurability : %d", sOut );
	if ( this->HT_bGetItemMaxCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemMaxCount : %d", byteOut );
	if ( this->HT_bGetItemCombatPhase( &sOut ) ) fprintf( pFile, "\nHT_bGetItemCombatPhase : %d", sOut );
	if ( this->HT_bGetItemSkillCastingTimeRate( &sOut ) ) fprintf( pFile, "\nHT_bGetItemSkillCastingTimeRate : %d", sOut );
	if ( this->HT_bGetItemEffect1ID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1ID : %d", iOut );
	if ( this->HT_bGetItemEffect1Function( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Function : %d", iOut );
	if ( this->HT_bGetItemEffect1Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Duration : %d", iOut );
	if ( this->HT_bGetItemEffect1Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect1Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect1Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect2ID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2ID : %d", iOut );
	if ( this->HT_bGetItemEffect2Function( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Function : %d", iOut );
	if ( this->HT_bGetItemEffect2Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Duration : %d", iOut );
	if ( this->HT_bGetItemEffect2Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect2Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect2Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect3ID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3ID : %d", iOut );
	if ( this->HT_bGetItemEffect3Function( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Function : %d", iOut );
	if ( this->HT_bGetItemEffect3Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Duration : %d", iOut );
	if ( this->HT_bGetItemEffect3Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect3Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect3Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect4ID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4ID : %d", iOut );
	if ( this->HT_bGetItemEffect4Function( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Function : %d", iOut );
	if ( this->HT_bGetItemEffect4Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Duration : %d", iOut );
	if ( this->HT_bGetItemEffect4Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect4Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect4Param2 : %d", iOut );
	if ( this->HT_bGetItemEffect5ID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5ID : %d", iOut );
	if ( this->HT_bGetItemEffect5Function( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Function : %d", iOut );
	if ( this->HT_bGetItemEffect5Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Duration : %d", iOut );
	if ( this->HT_bGetItemEffect5Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Param1 : %d", iOut );
	if ( this->HT_bGetItemEffect5Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetItemEffect5Param2 : %d", iOut );
	if ( this->HT_bGetItemCoolDownTime( &iOut ) ) fprintf( pFile, "\nHT_bGetItemCoolDownTime : %d", iOut );
	if ( this->HT_bGetItemRange( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemRange : %d", byteOut );
	if ( this->HT_bGetItemArmorType( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemArmorType : %d", byteOut );
	if ( this->HT_bGetItemAttackType( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemAttackType : %d", byteOut );
	if ( this->HT_bGetItemCostTP( &iOut ) ) fprintf( pFile, "\nHT_bGetItemCostTP : %d", iOut );
	if ( this->HT_bGetItemCostHP( &iOut ) ) fprintf( pFile, "\nHT_bGetItemCostHP : %d", iOut );
	if ( this->HT_bGetItemidCostItem( &iOut ) ) fprintf( pFile, "\nHT_bGetItemidCostItem : %d", iOut );
	if ( this->HT_bGetItemLimitTrimuriti( &iOut ) ) fprintf( pFile, "\nHT_bGetItemLimitTrimuriti : %d", iOut );
	if ( this->HT_bGetItemLimitTribe( &iOut ) ) fprintf( pFile, "\nHT_bGetItemLimitTribe : %d", iOut );
	if ( this->HT_bGetItemLimitLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLimitLevel : %d", byteOut );
	if ( this->HT_bGetItemLimitMuscleChakra( &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitMuscleChakra : %d", sOut );
	if ( this->HT_bGetItemLimitNerveChakra( &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitNerveChakra : %d", sOut );
	if ( this->HT_bGetItemLimitHeartChakra( &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitHeartChakra : %d", sOut );
	if ( this->HT_bGetItemLimitSoulChakra( &sOut ) ) fprintf( pFile, "\nHT_bGetItemLimitSoulChakra : %d", sOut );
	if ( this->HT_bGetItemRefinableItemType( &iOut ) ) fprintf( pFile, "\nHT_bGetItemRefinableItemType : %d", iOut );
	if ( this->HT_bGetItemCash( &iOut ) ) fprintf( pFile, "\nHT_bGetItemCash : %d", iOut );
	if ( this->HT_bGetItemTimeLimit( &sOut ) ) fprintf( pFile, "\nHT_bGetItemTimeLimit : %d", sOut );
	//if ( this->HT_bGetItemEventID( &sOut ) ) fprintf( pFile, "\nHT_bGetItemEventID : %d", sOut );
}

void
CHTClientParamMgr::HT_vTestNPCParamWithID( FILE* pFile, const int id )
{
	byte byteOut;
	short sOut, sOut2;
	CHTString str;

	if ( this->HT_bGetNPCName( id, &str ) ) fprintf( pFile, "\nHT_bGetNPCName : %s", str.HT_szGetString() );
	if ( this->HT_bGetNPCSize( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCSize : %d", byteOut );
	if ( this->HT_bGetNPCZone( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCZone : %d", byteOut );
	if ( this->HT_bGetNPCPosition( id, &sOut, &sOut2 ) ) fprintf( pFile, "\nHT_bGetNPCPosition : %d,%d", sOut, sOut2 );
	if ( this->HT_bGetNPCTrimuriti( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCTrimuriti : %d", byteOut );

	int iCount = this->HT_iGetNPCSellingItemCount( id );
	if ( iCount > 0 ) fprintf( pFile, "\nHT_iGetNPCSellingItemCount : %d", iCount );

	for ( int i = 0; i < iCount; ++i )
	{
		int idItem;
		if ( this->HT_bGetNPCSellingItem( id, i, &idItem ) )
			fprintf( pFile, "\nHT_bGetNPCSellingItem( %d ) : %d", i, idItem );
	}
}

void
CHTClientParamMgr::HT_vTestNPCParam( FILE* pFile )
{
	byte byteOut;
	short sOut, sOut2;
	CHTString str;

	if ( this->HT_bGetNPCName( &str ) ) fprintf( pFile, "\nHT_bGetNPCName : %s", str.HT_szGetString() );
	if ( this->HT_bGetNPCSize( &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCSize : %d", byteOut );
	if ( this->HT_bGetNPCZone( &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCZone : %d", byteOut );
	if ( this->HT_bGetNPCPosition( &sOut, &sOut2 ) ) fprintf( pFile, "\nHT_bGetNPCPosition : %d,%d", sOut, sOut2 );
	if ( this->HT_bGetNPCTrimuriti( &byteOut ) ) fprintf( pFile, "\nHT_bGetNPCTrimuriti : %d", byteOut );

	int iCount = this->HT_iGetNPCSellingItemCount();
	if ( iCount > 0 ) fprintf( pFile, "\nHT_iGetNPCSellingItemCount : %d", iCount );

	for ( int i = 0; i < iCount; ++i )
	{
		int idItem;
		if ( this->HT_bGetNPCSellingItem( i, &idItem ) )
			fprintf( pFile, "\nHT_bGetNPCSellingItem( %d ) : %d", i, idItem );
	}
}

void
CHTClientParamMgr::HT_vTestPortalParam( FILE* pFile, const int id )
{
	int	iOut;
	DWORD dwOut, dwOut2;
	short sOut, sOut2, sOut3, sOut4;
	CHTString str;

	if ( this->HT_bGetPortalName( id, &str ) ) fprintf( pFile, "\nHT_bGetPortalName : %s", str.HT_szGetString() );
	if ( this->HT_bGetPortalInfo( id, &dwOut, &dwOut2, &sOut, &sOut2, &sOut3, &sOut4) ) 
			fprintf( pFile, "\nHT_bGetPortalInfo : %d - %d(%dLvl) Start(%d,%d)End(%d,%d)", 
													id, dwOut, dwOut2, sOut, sOut2, sOut3, sOut4 );
	
	for ( int i = 0 ; i < 5 ; ++i )
	{
		if( this->HT_bGetGoingPortal( id, i, &iOut, &dwOut, &dwOut2 ) )
			fprintf( pFile, "\nHT_bGetGoingPortal(%d) : PortalID %d Fee %d Lvl %d ", i, iOut, dwOut, dwOut2 );
	}
}

void
CHTClientParamMgr::HT_vTestTaskQuestParamWithID( FILE* pFile, const int id )
{
	byte byteOut, byteOut1;
	short sOut, sOut1, sOut2, sOut3, sOut4;
	int iOut;

	if ( this->HT_bGetTaskNPCID( id, &sOut, &sOut1, &sOut2, &sOut3, &sOut4 ) ) 
		fprintf( pFile, "\nHT_bGetTaskNPCID : NPC1(%d) NPC2(%d) NPC3(%d) NPC4(%d) NPC5(%d)", sOut, sOut1, sOut2, sOut3, sOut4 );

	if ( this->HT_bGetTaskSource1( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource1 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource2( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource2 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource3( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource3 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource4( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource4 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource5( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource5 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource6( id, &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource6 : type %d:%d %d", byteOut, sOut1, iOut );

	if ( this->HT_bGetTaskReward1( id, &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward1 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward2( id, &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward2 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward3( id, &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward3 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward4( id, &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward4 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward5( id, &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward5 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	
	if ( this->HT_bGetTaskLevel( id, &byteOut, &byteOut1 ) ) 
		fprintf( pFile, "\nHT_bGetTaskLevel : type (%d ~ %d)", byteOut, byteOut1 );
}

void
CHTClientParamMgr::HT_vTestTaskQuestParam( FILE* pFile )
{
	byte byteOut, byteOut1;
	short sOut, sOut1, sOut2, sOut3, sOut4;
	int iOut;

	if ( this->HT_bGetTaskNPCID( &sOut, &sOut1, &sOut2, &sOut3, &sOut4 ) ) 
		fprintf( pFile, "\nHT_bGetTaskNPCID : NPC1(%d), NPC2(%d) NPC3(%d) NPC4(%d) NPC5(%d)", sOut, sOut1, sOut2, sOut3, sOut4 );

	if ( this->HT_bGetTaskSource1( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource1 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource2( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource2 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource3( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource3 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource4( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource4 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource5( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource5 : type %d:%d %d", byteOut, sOut1, iOut );
	if ( this->HT_bGetTaskSource6( &byteOut, &sOut1, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskSource6 : type %d:%d %d", byteOut, sOut1, iOut );

	if ( this->HT_bGetTaskReward1( &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward1 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward2( &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward2 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward3( &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward3 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward4( &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward4 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );
	if ( this->HT_bGetTaskReward5( &byteOut, &byteOut1, &sOut1, &sOut2, &iOut ) ) 
		fprintf( pFile, "\nHT_bGetTaskReward5 : P%d type %d %d%%:%d %d", byteOut, byteOut1, sOut1, sOut2, iOut );

	if ( this->HT_bGetTaskLevel( &byteOut, &byteOut1 ) ) 
		fprintf( pFile, "\nHT_bGetTaskLevel : type (%d ~ %d)", byteOut, byteOut1 );
}

void
CHTClientParamMgr::HT_vTestAreaIndidcateParam( FILE* pFile, const int id )
{
	DWORD dwOut, dwOut2;
	CHTString str;

	if ( this->HT_bGetAreaFrom( id, &dwOut ) ) fprintf( pFile, "\nHT_bGetAreaFrom : %d", dwOut );
	if ( this->HT_bGetAreaTo( id, &dwOut2 ) ) fprintf( pFile, "\nHT_bGetAreaTo : %d", dwOut2 );
	if ( this->HT_bGetAreaName( id, &str ) ) fprintf( pFile, "\nHT_bGetAreaName : %s", str.HT_szGetString() );
	if ( this->HT_bGetAreaName( dwOut, dwOut2, &str ) ) 
		fprintf( pFile, "\nHT_bGetAreaName : From %d To %d :%s", dwOut, dwOut2, str.HT_szGetString() );
}

bool
CHTClientParamMgr::HT_bGetMonsterName( const int id, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterName( id, pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSize( const int id, byte* pbyteSize )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSize( id, pbyteSize );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterClass( const int id, byte* pbyteClass )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterClass( id, pbyteClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterFly( const int id, byte* pbFly )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterFly( id, pbFly );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterReserved7( const int id, byte* pbFly )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserved7( id, pbFly );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterName( CHTString* pstrName )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterName( pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSize( byte* pbyteSize )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSize( pbyteSize );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterClass( byte* pbyteClass )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterClass( pbyteClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterFly( byte* pbFly )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterFly( pbFly );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterReserved7( byte* pbReserved7 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserved7( pbReserved7 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSkillRange( const int id, int* piRange )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillRange( id, piRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCastingTime( id, piCastingTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSkillRange( int* piRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillRange( piRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetMonsterSkillCastingTime( int* piCastingTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCastingTime( piCastingTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillMaxLevel( id, byteLevel, pbyteMaxLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillType( id, byteLevel, pbyteType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCombatPhase( id, byteLevel, psCombatPhase );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillDuration( id, byteLevel, piDuration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCastingSuccessRate( id, byteLevel, pbyteCastingSuccessRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillFollowRange( id, byteLevel, pbyteFollowRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillPierceRate( id, byteLevel, pbytePierceRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCoolDownTime( id, byteLevel, piCoolDownTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReadyTime( id, byteLevel, piReadyTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCastingTime( id, byteLevel, piCastingTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillApplyTime( id, byteLevel, piApplyTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillRange( id, byteLevel, piRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAreaOfEffect( id, byteLevel, piAreaOfEffect );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAllowedTarget( id, byteLevel, piAllowedTarget );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAttackType( id, byteLevel, pbyteAttackType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqTrimuriti( id, byteLevel, piReqTrimuriti );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqTribe( id, byteLevel, piReqTribe );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqClass( id, byteLevel, piReqClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqWeaponType( id, byteLevel, piReqWeaponType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillidReqItem( id, byteLevel, pidReqItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLEvel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqLevel( id, byteLevel, pbyteReqLEvel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill1( id, byteLevel, pidReqSkill1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill1_Lvl( id, byteLevel, pbyteReqSkill1_Lvl );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill2( id, byteLevel, pidReqSkill2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill2_Lvl( id, byteLevel, pbyteReqSkill2_Lvl );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1ID( id, byteLevel, piEffect1ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Function( id, byteLevel, piEffect1Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Duration( id, byteLevel, piEffect1Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Param1( id, byteLevel, piEffect1Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Param2( id, byteLevel, piEffect1Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2ID( id, byteLevel, piEffect2ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Function( id, byteLevel, piEffect2Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Duration( id, byteLevel, piEffect2Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Param1( id, byteLevel, piEffect2Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Param2( id, byteLevel, piEffect2Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3ID( id, byteLevel, piEffect3ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Function( id, byteLevel, piEffect3Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Duration( id, byteLevel, piEffect3Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Param1( id, byteLevel, piEffect3Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Param2( id, byteLevel, piEffect3Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4ID( id, byteLevel, piEffect4ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Function( id, byteLevel, piEffect4Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Duration( id, byteLevel, piEffect4Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Param1( id, byteLevel, piEffect4Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Param2( id, byteLevel, piEffect4Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5ID( id, byteLevel, piEffect5ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Function( id, byteLevel, piEffect5Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Duration( id, byteLevel, piEffect5Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Param1( id, byteLevel, piEffect5Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Param2( id, byteLevel, piEffect5Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostTP( id, byteLevel, piCostTP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostHP( id, byteLevel, piCostHP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillidCostItem( id, byteLevel, pidCostItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostItemCount( id, byteLevel, pbyteCostItemCount );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillMaxLevel( pbyteMaxLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillType( byte* pbyteType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillType( pbyteType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCombatPhase( short* psCombatPhase )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCombatPhase( psCombatPhase );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillDuration( int* piDuration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillDuration( piDuration );
	else return false;
}
/*
bool
CHTClientParamMgr::HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate )
{
	if ( m_pParamTable ) return  m_pParamTable->HT_bGetPCSkillSuccessRate( pbyteSuccessRate );
	else return false;
}
*/
bool
CHTClientParamMgr::HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCastingSuccessRate( pbyteCastingSuccessRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillFollowRange( byte* pbyteFollowRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillFollowRange( pbyteFollowRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillPierceRate( byte* pbytePierceRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillPierceRate( pbytePierceRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCoolDownTime( piCoolDownTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReadyTime( int* piReadyTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReadyTime( piReadyTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCastingTime( int* piCastingTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCastingTime( piCastingTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillApplyTime( int* piApplyTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillApplyTime( piApplyTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillRange( int* piRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillRange( piRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAreaOfEffect( piAreaOfEffect );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAllowedTarget( piAllowedTarget );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillAttackType( byte* pbyteAttackType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAttackType( pbyteAttackType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqTrimuriti( piReqTrimuriti );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqTribe( int* piReqTribe )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqTribe( piReqTribe );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqClass( int* piReqClass )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqClass( piReqClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqWeaponType( int* piReqWeaponType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqWeaponType( piReqWeaponType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillidReqItem( int* pidReqItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillidReqItem( pidReqItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqLevel( byte* pbyteReqLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqLevel( pbyteReqLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill1( int* pidReqSkill1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill1( pidReqSkill1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill1_Lvl( pbyteReqSkill1_Lvl );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill2( int* pidReqSkill2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill2( pidReqSkill2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill2_Lvl( pbyteReqSkill2_Lvl );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1ID( int* piEffect1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1ID( piEffect1ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Function( int* piEffect1Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Function( piEffect1Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Duration( piEffect1Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Param1( piEffect1Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Param2( piEffect1Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2ID( int* piEffect2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2ID( piEffect2ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Function( int* piEffect2Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Function( piEffect2Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Duration( piEffect2Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Param1( piEffect2Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Param2( piEffect2Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3ID( int* piEffect3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3ID( piEffect3ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Function( int* piEffect3Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Function( piEffect3Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Duration( piEffect3Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Param1( piEffect3Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Param2( piEffect3Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4ID( int* piEffect4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4ID( piEffect4ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Function( int* piEffect4Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Function( piEffect4Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Duration( piEffect4Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Param1( piEffect4Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Param2( piEffect4Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5ID( int* piEffect5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5ID( piEffect5ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Function( int* piEffect5Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Function( piEffect5Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Duration( piEffect5Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Param1( piEffect5Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Param2( piEffect5Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostTP( int* piCostTP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostTP( piCostTP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostHP( int* piCostHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostHP( piCostHP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillidCostItem( int* pidCostItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillidCostItem( pidCostItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostItemCount( pbyteCostItemCount );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLevel( const int id, byte* pbyteLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLevel( id, pbyteLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemName( const int id, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemName( id, pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemDescription( const int id, CHTString* pstrDescription )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemDescription( id, pstrDescription );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemClass( const int id, byte* pbyteClass )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemClass( id, pbyteClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemType( const int id, short* psType)
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemType( id, psType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRupiah( const int id, int* piRupiah )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRupiah( id, piRupiah );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemSellRupiah( const int id, int* piSellRupiah )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemSellRupiah( id, piSellRupiah );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemMaxDurability( const int id, short* psMaxDurability )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemMaxDurability( id, psMaxDurability );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemMaxCount( id, pbyteMaxCount );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCombatPhase( const int id, short* psCombatPhase )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCombatPhase( id, psCombatPhase );
	else return false;

}

bool
CHTClientParamMgr::HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemSkillCastingTimeRate( id, psSkillCastingTimeRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1ID( const int id, int* piEffect1ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1ID( id, piEffect1ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Function( const int id, int* piEffect1Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Function( id, piEffect1Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Duration( id, piEffect1Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Param1( id, piEffect1Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Param2( id, piEffect1Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2ID( const int id, int* piEffect2ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2ID( id, piEffect2ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Function( const int id, int* piEffect2Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Function( id, piEffect2Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Duration( id, piEffect2Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Param1( id, piEffect2Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Param2( id, piEffect2Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3ID( const int id, int* piEffect3ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3ID( id, piEffect3ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Function( const int id, int* piEffect3Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Function( id, piEffect3Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Duration( id, piEffect3Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Param1( id, piEffect3Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Param2( id, piEffect3Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4ID( const int id, int* piEffect4ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4ID( id, piEffect4ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Function( const int id, int* piEffect4Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Function( id, piEffect4Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Duration( id, piEffect4Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Param1( id, piEffect4Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Param2( id, piEffect4Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5ID( const int id, int* piEffect5ID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5ID( id, piEffect5ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Function( const int id, int* piEffect5Function )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Function( id, piEffect5Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Duration( id, piEffect5Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Param1( id, piEffect5Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Param2( id, piEffect5Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCoolDownTime( id, piCoolDownTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRange( const int id, byte* pbyteRange )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRange( id, pbyteRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemAttackType( const int id, byte* pbyteAttackType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemAttackType( id, pbyteAttackType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemArmorType( const int id, byte* pbyteArmorType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemArmorType( id, pbyteArmorType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCostTP( const int id, int* piCostTP )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCostTP( id, piCostTP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCostHP( const int id, int* piCostHP )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCostHP( id, piCostHP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemidCostItem( const int id, int* pidCostItem )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemidCostItem( id, pidCostItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitTrimuriti( id, piLimitTrimuriti );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitTribe( const int id, int* piLimitTribe )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitTribe( id, piLimitTribe );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitLevel( id, pbyteLimitLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitMuscleChakra( id, psLimitMusclechakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitNerveChakra( id, psLimitNerveChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitHeartChakra( id, psLimitHeartChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitSoulChakra( id, psLimitSoulChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRefinableItemType( id, piRefinableItemType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCash( const int id, int* piCash )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCash( id, piCash );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemTimeLimit( const int id, short* psTimeLimit )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemTimeLimit( id, psTimeLimit );
	else return false;
}

/*bool
CHTClientParamMgr::HT_bGetItemFXEffectID( const int id, int* piFXID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemFXEffectID( id, piFXID );
	else return false;
}*/

//bool
//CHTClientParamMgr::HT_bGetItemEventID( const int id, short* psEventID )
//{
//	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
//	if ( pParamTable ) return pParamTable->HT_bGetItemEventID( id, psEventID );
//	else return false;
//}

bool
CHTClientParamMgr::HT_bGetItemLevel( byte* pbyteLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLevel( pbyteLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemName( CHTString* pstrName )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemName( pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemDescription( CHTString* pstrDescription )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemDescription( pstrDescription );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemClass( byte* pbyteClass)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemClass( pbyteClass );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemType( short* psType)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemType( psType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRupiah( int* piRupiah )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRupiah( piRupiah );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemSellRupiah( int* piSellRupiah )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemSellRupiah( piSellRupiah );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemMaxDurability( short* psMaxDurability )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemMaxDurability( psMaxDurability );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemMaxCount( byte* pbyteMaxCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemMaxCount( pbyteMaxCount );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCombatPhase( short* psCombatPhase )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCombatPhase( psCombatPhase );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemSkillCastingTimeRate( psSkillCastingTimeRate );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1ID( int* piEffect1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1ID( piEffect1ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Function( int* piEffect1Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Function( piEffect1Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Duration( piEffect1Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Param1( piEffect1Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Param2( piEffect1Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2ID( int* piEffect2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2ID( piEffect2ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Function( int* piEffect2Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Function( piEffect2Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Duration( piEffect2Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Param1( piEffect2Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Param2( piEffect2Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3ID( int* piEffect3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3ID( piEffect3ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Function( int* piEffect3Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Function( piEffect3Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Duration( piEffect3Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Param1( piEffect3Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Param2( piEffect3Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4ID( int* piEffect4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4ID( piEffect4ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Function( int* piEffect4Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Function( piEffect4Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Duration( piEffect4Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Param1( piEffect4Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Param2( piEffect4Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5ID( int* piEffect5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5ID( piEffect5ID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Function( int* piEffect5Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Function( piEffect5Function );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Duration( piEffect5Duration );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Param1( piEffect5Param1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Param2( piEffect5Param2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCoolDownTime( piCoolDownTime );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRange( byte* pbyteRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRange( pbyteRange );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemArmorType( byte* pbyteArmorType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemArmorType( pbyteArmorType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemAttackType( byte* pbyteAttackType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemAttackType( pbyteAttackType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCostTP( int* piCostTP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCostTP( piCostTP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCostHP( int* piCostHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCostHP( piCostHP );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemidCostItem( int* pidCostItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemidCostItem( pidCostItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitTrimuriti( piLimitTrimuriti );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitTribe( int* piLimitTribe )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitTribe( piLimitTribe );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitLevel( byte* pbyteLimitLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitLevel( pbyteLimitLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitMuscleChakra( psLimitMusclechakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitNerveChakra( psLimitNerveChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitHeartChakra( psLimitHeartChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitSoulChakra( psLimitSoulChakra );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemRefinableItemType( int* piRefinableItemType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRefinableItemType( piRefinableItemType );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemCash( int* piCash )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCash( piCash );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetItemTimeLimit( short* psTimeLimit )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemTimeLimit( psTimeLimit );
	else return false;
}

/*bool
/*CHTClientParamMgr::HT_bGetItemFXEffectID( int* piFXID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemFXEffectID( piFXID );
	else return false;
}*/

//bool
//CHTClientParamMgr::HT_bGetItemEventID( short* psEventID )
//{
//	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEventID( psEventID );
//	else return false;
//}

bool
CHTClientParamMgr::HT_bGetNPCName( const int id, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCName( id, pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCSize( const int id, byte* pbyteSize )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCSize( id, pbyteSize );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCZone( const int id, byte* pbyteZone )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCZone( id, pbyteZone );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCPosition( id, psPosX, psPosZ );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti)
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCTrimuriti( id, pbyNPCTrimuriti );
	else return false;
}

int
CHTClientParamMgr::HT_iGetNPCSellingItemCount( const int id )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_iGetNPCSellingItemCount( id );
	else return -1;
}

bool
CHTClientParamMgr::HT_bGetNPCSellingItem( const int id, const int index, int* pidItem )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCSellingItem( id, index, pidItem );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCName( CHTString* pstrName )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCName( pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCSize( byte* pbyteSize )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCSize( pbyteSize );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCZone( byte* pbyteZone )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCZone( pbyteZone );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCPosition( short* psPosX, short* psPosZ )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCPosition( psPosX, psPosZ );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCTrimuriti( pbyNPCTrimuriti );
	else return false;
}

int
CHTClientParamMgr::HT_iGetNPCSellingItemCount()
{
	if ( m_pParamTable ) return m_pParamTable->HT_iGetNPCSellingItemCount();
	else return -1;
}

bool
CHTClientParamMgr::HT_bGetNPCSellingItem( const int index, int* pidItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCSellingItem( index, pidItem );
	else return false;
}

// Portal
bool
CHTClientParamMgr::HT_bGetPortalName( const int id, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPortalName( id, pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetGoingPortal( id, iNo, piGoPortal, pdwFee, pdwLevel );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
								   short* psStartX, short* psStartZ, short* psEndX, short* psEndZ)
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPortalInfo( id, pdwServerID, pdwZoneLevel, psStartX, psStartZ, psEndX, psEndZ );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( idFromPortal );
	if ( pParamTable ) return pParamTable->HT_bGetPortalFee( idFromPortal, idToPrtal, pdwFee );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel)
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( idFromPortal );
	if ( pParamTable ) return pParamTable->HT_bGetPortalLevel( idFromPortal, idToPrtal, pdwLevel );
	else return false;
}

// TaskQuest
bool
CHTClientParamMgr::HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, 
								  short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskNPCID( id, psNPCID1, psNPCID2, psNPCID3, psNPCID4, psNPCID5 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource1( id,/* psNPCID,*/ pbyteSourceType1, psSourceItemID1, piSourceCount1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource2( id,/* psNPCID,*/ pbyteSourceType2, psSourceItemID2, piSourceCount2 );
	else return false;
} 

bool
CHTClientParamMgr::HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource3( id,/* psNPCID,*/ pbyteSourceType3, psSourceItemID3, piSourceCount3 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource4( id,/* psNPCID,*/ pbyteSourceType4, psSourceItemID4, piSourceCount4 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource5( id,/* psNPCID,*/ pbyteSourceType5, psSourceItemID5, piSourceCount5 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource6( id,/* psNPCID,*/ pbyteSourceType6, psSourceItemID6, piSourceCount6 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1,
									  short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward1( id,/* psNPCID,*/ pbyteRewardPriority1, pbyteRewardType1,
																psReward1Rate, psRewardItemID1, piRewardCount1 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2,
									  short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward2( id,/* psNPCID,*/ pbyteRewardPriority2, pbyteRewardType2,
																psReward2Rate, psRewardItemID2, piRewardCount2 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3,
									  short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward3( id,/* psNPCID,*/ pbyteRewardPriority3, pbyteRewardType3,
																psReward3Rate, psRewardItemID3, piRewardCount3 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4,
									  short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward4( id,/* psNPCID,*/ pbyteRewardPriority4, pbyteRewardType4,
																psReward4Rate, psRewardItemID4, piRewardCount4 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5,
									  short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5 )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward5( id,/* psNPCID,*/ pbyteRewardPriority5, pbyteRewardType5,
																psReward5Rate, psRewardItemID5, piRewardCount5 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* pbyteMinLevel, byte* pbyteMaxLevel )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskLevel( id,/* psNPCID,*/ pbyteMinLevel, pbyteMaxLevel );
	else return false;
}


bool
CHTClientParamMgr::HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskNPCID( psNPCID1, psNPCID2, psNPCID3, psNPCID4, psNPCID5 );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource1( /* psNPCID,*/pbyteSourceType1, psSourceItemID1, piSourceCount1);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource2( /* short* psNPCID,*/byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource2( /* psNPCID,*/pbyteSourceType2, psSourceItemID2, piSourceCount2);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource3( /* short* psNPCID,*/byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource3( /* psNPCID,*/pbyteSourceType3, psSourceItemID3, piSourceCount3);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource4( /* short* psNPCID,*/byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource4( /* psNPCID,*/pbyteSourceType4, psSourceItemID4, piSourceCount4);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource5( /* short* psNPCID,*/byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource5( /* psNPCID,*/pbyteSourceType5, psSourceItemID5, piSourceCount5);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskSource6( /*short* psNPCID, */byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource6( /* psNPCID,*/pbyteSourceType6, psSourceItemID6, piSourceCount6);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward1( /*short* psNPCID, */byte* pbyteRewardPriority1, byte* pbyteRewardType1,
									  short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward1( /* psNPCID,*/pbyteRewardPriority1, pbyteRewardType1,
																	psReward1Rate, psRewardItemID1, piRewardCount1);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward2( /*short* psNPCID, */byte* pbyteRewardPriority2, byte* pbyteRewardType2,
									  short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward2( /* psNPCID,*/pbyteRewardPriority2, pbyteRewardType2,
																	psReward2Rate, psRewardItemID2, piRewardCount2);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward3( /*short* psNPCID, */byte* pbyteRewardPriority3, byte* pbyteRewardType3,
									  short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward3( /* psNPCID,*/pbyteRewardPriority3, pbyteRewardType3,
																	psReward3Rate, psRewardItemID3, piRewardCount3);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward4( /*short* psNPCID, */byte* pbyteRewardPriority4, byte* pbyteRewardType4,
									  short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward4( /* psNPCID,*/pbyteRewardPriority4, pbyteRewardType4,
																	psReward4Rate, psRewardItemID4, piRewardCount4);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskReward5( /*short* psNPCID, */byte* pbyteRewardPriority5, byte* pbyteRewardType5,
									  short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward5( /* psNPCID,*/pbyteRewardPriority5, pbyteRewardType5,
																	psReward5Rate, psRewardItemID5, piRewardCount5);
	else return false;
}

bool
CHTClientParamMgr::HT_bGetTaskLevel( /* short* psNPCID,*/ byte* pbyteMinLevel, byte* pbyteMaxLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskLevel( /* psNPCID,*/ pbyteMinLevel, pbyteMaxLevel );

	else return false;
}

// AreaIndicate
bool
CHTClientParamMgr::HT_bGetAreaFrom( const int id, DWORD* pdwFromID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetAreaFrom( id, pdwFromID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetAreaTo( const int id, DWORD* pdwToID )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetAreaTo( id, pdwToID );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetAreaName( const int id, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetAreaName( id, pstrName );
	else return false;
}

bool
CHTClientParamMgr::HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName )
{
	CHTBaseClientParamTable* pParamTable = m_arrParamTable[HT_PARAMTYPE_AREAINDICATE];
	if ( pParamTable ) return pParamTable->HT_bGetAreaName( dwFrom, dwTo, pstrName );
	else return false;
}

int
CHTClientParamMgr::HT_iGetAllCount( const int iType )
{
	switch ( iType )
	{
		case HT_PARAMTYPE_PCSKILL :	return int(m_vectorPCSkillIDLevelNagKin.size()+m_vectorPCSkillIDLevelAsuRak.size()
												+ m_vectorPCSkillIDLevelDevGar.size()+m_vectorPCSkillIDLevelYakGan.size());
		case HT_PARAMTYPE_NPC :		return (int)m_vectorNPCIDLevel.size();
		default :					return -1;
	}
}

bool
CHTClientParamMgr::HT_bGetNPCAllID( std::vector<HTIDLevel>* pvectorIDLevel )
{
	return m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bGetAllID( pvectorIDLevel );
}

int
CHTClientParamMgr::HT_iGetPCSkillIDLevelCount( const int iCharType )
{
	switch ( iCharType )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			return (int)m_vectorPCSkillIDLevelNagKin.size();
		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			return (int)m_vectorPCSkillIDLevelAsuRak.size();
		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			return (int)m_vectorPCSkillIDLevelDevGar.size();
		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			return (int)m_vectorPCSkillIDLevelYakGan.size();
		default:
			return -1;
	}
}

bool
CHTClientParamMgr::HT_bGetPCSkillIDLevel( const int iCharType, const int index, int* pid, byte* pbyteLevel )
{
	if ( index < 0 )
		return false;

	int iSize = 0;

	switch ( iCharType )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			iSize = (int)m_vectorPCSkillIDLevelNagKin.size();
			if ( index >= iSize )
				return false;
			
			*pid = m_vectorPCSkillIDLevelNagKin[index].iID;
			*pbyteLevel = m_vectorPCSkillIDLevelNagKin[index].byteLevel;
			return true;
		
		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			iSize = (int)m_vectorPCSkillIDLevelAsuRak.size();
			if ( index >= iSize )
				return false;

			*pid = m_vectorPCSkillIDLevelAsuRak[index].iID;
			*pbyteLevel = m_vectorPCSkillIDLevelAsuRak[index].byteLevel;
			return true;
		
		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			iSize = (int)m_vectorPCSkillIDLevelDevGar.size();
			if ( index >= iSize )
				return false;

			*pid = m_vectorPCSkillIDLevelDevGar[index].iID;
			*pbyteLevel = m_vectorPCSkillIDLevelDevGar[index].byteLevel;
			return true;
		
		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			iSize = (int)m_vectorPCSkillIDLevelYakGan.size();
			if ( index >= iSize )
				return false;

			*pid = m_vectorPCSkillIDLevelYakGan[index].iID;
			*pbyteLevel = m_vectorPCSkillIDLevelYakGan[index].byteLevel;
			return true;

		default:
			return false;				
	}
}

int
CHTClientParamMgr::HT_iGetPCSkillIDCount( const int iCharType )
{
	switch ( iCharType )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			return (int)m_vectorPCSkillIDNagKin.size();
		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			return (int)m_vectorPCSkillIDAsuRak.size();
		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			return (int)m_vectorPCSkillIDDevGar.size();
		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			return (int)m_vectorPCSkillIDYakGan.size();
		default:
			return -1;
	}
}

bool
CHTClientParamMgr::HT_bGetPCSkillIDByIndex( const int iCharType, const int index, int* pid )
{
	if ( index < 0 )
		return false;

	int iSize = 0;

	switch ( iCharType )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			iSize = (int)m_vectorPCSkillIDNagKin.size();
			if ( index >= iSize ) return false;
			else
			{
				*pid = m_vectorPCSkillIDNagKin[index];
				return true;
			}
		
		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			iSize = (int)m_vectorPCSkillIDAsuRak.size();
			if ( index >= iSize ) return false;
			else
			{
				*pid = m_vectorPCSkillIDAsuRak[index];
				return true;
			}
		
		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			iSize = (int)m_vectorPCSkillIDDevGar.size();
			if ( index >= iSize ) return false;
			else
			{
				*pid = m_vectorPCSkillIDDevGar[index];
				return true;
			}
		
		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			iSize = (int)m_vectorPCSkillIDYakGan.size();
			if ( index >= iSize ) return false;
			else
			{
				*pid = m_vectorPCSkillIDYakGan[index];
				return true;
			}

		default:
			return false;				
	}
}

CHTBaseClientParamTable*
CHTClientParamMgr::HT_pGetParamTable( int id )
{
	if ( CHTParamIDCheck::HT_bIsMonster( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_MONSTER];
	}
	else if ( CHTParamIDCheck::HT_bIsMonsterSkill( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL];
	}
	else if ( CHTParamIDCheck::HT_bIsPCSkill( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_PCSKILL];
	}
	else if ( CHTParamIDCheck::HT_bIsItem( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_ITEM];
	}
	else if ( CHTParamIDCheck::HT_bIsNPC( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_NPC];
	}
	else if ( CHTParamIDCheck::HT_bIsPortal( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_PORTAL];
	}
	else if ( CHTParamIDCheck::HT_bIsTaskQuest( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_TASKQUEST];
	}
	else if ( CHTParamIDCheck::HT_bIsAreaIndicate( id ) )
	{
		return m_arrParamTable[HT_PARAMTYPE_AREAINDICATE];
	}
	else
	{
		return 0;
	}
}

bool CHTClientParamMgr::HT_bGetAllID( int iType, std::vector<HTIDLevel>* pvectorIDLevel )
{
	pvectorIDLevel->clear();

	switch ( iType )
	{
	case HT_PARAMTYPE_MONSTER :			return m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bGetAllID( pvectorIDLevel );
	case HT_PARAMTYPE_MONSTERSKILL :	return m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]->HT_bGetAllID( pvectorIDLevel );
	case HT_PARAMTYPE_PCSKILL :			return m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bGetAllID( pvectorIDLevel );
	case HT_PARAMTYPE_ITEM :			return m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bGetAllID( pvectorIDLevel );
	case HT_PARAMTYPE_NPC:				return m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bGetAllID( pvectorIDLevel );
	default : return false;
	}
}