#include "stdAfx.h"
#include "HTParamMgr.h"

#include "HTFile.h"
#include "HTXMLParser.h"

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
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_END ) ) ||
		 (( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_END ) ) ) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemDefenceArmor( const int id )//fors_debug ‘ˆº”Ω·ªÈÃ◊◊∞≈–∂œ «’˝≥£◊∞±∏µƒµÿ∑Ω
{
	if ( (( id >= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_START ) && ( id <= HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_END )) ||
		(( id >= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_START ) && ( id <= HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_END )) || (( id == 8901) || (id ==8902))) return true;
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
CHTParamIDCheck::HT_bIsItemCharge( const int id )
{
	//	if ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_END ) ) return true;
	//	else return false;
	if ( ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_END ) )
		|| ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_USABLE2_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_USABLE2_END ) )
		|| ( ( id >= HT_PARAMTYPE_ITEM_CHARGE_USABLE_START ) && ( id <= HT_PARAMTYPE_ITEM_CHARGE_USABLE_END ) )
		|| ( id == 6614 ) ) return true;	// 6614¥¬ æ∆∏ª∂Û¥Ÿ
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
		( id >= HT_PARAMTYPE_ITEM_USABLE2_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE2_END ) ||
		( id >= HT_PARAMTYPE_ITEM_USABLE4_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE4_END )) return true;
	else return false;
}

bool
CHTParamIDCheck::HT_bIsItemPacked( const int id )
{
	if ( (id >= HT_PARAMTYPE_ITEM_USABLE3_START ) && ( id <= HT_PARAMTYPE_ITEM_USABLE3_END ))	return true;
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
	// ¥Ÿ¿Ω¿« π¯»£¥¬ ≈©∏ÆΩ¥≥™∑Œ ¿Œ¡§, ∞≈∏Æ√º≈© æ»«—¥Ÿ.
	if (id >= 1342 && id <= 1436)
		return true;

	// 21π¯¡∏ ªı∑Œ √ﬂ∞° (≈©∏ÆΩ¥≥™ NPC »Æ¿Â)
	if (id >= 1446 && id <= 1456)
		return true;

	switch(id)
	{
		case 1263: // ≈©∏ÆΩ¥≥™ ¿œ∞ÊøÏ TRUE π›»Ø
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
		case 1340:	// 20π¯ NPC
		case 1445:	// 21π¯ NPC
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

HTIDLevel::HTIDLevel() { iID = 0; byteLevel = 0; }
HTIDLevel::~HTIDLevel() {}
HTIDLevel::HTIDLevel( const HTIDLevel& oIDLevel ) { iID = oIDLevel.iID; byteLevel = oIDLevel.byteLevel; }

#define HT_LOADCELL( szCell, Value, DataType ) \
{ strCell = (szCell); pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp ); Value = (DataType)iTemp; }

CHTBaseParamTable::CHTBaseParamTable() {}
CHTBaseParamTable::~CHTBaseParamTable() {}
#ifdef HT_NEED_NAME
bool CHTBaseParamTable::HT_bGetName( const int id, CHTString* pstrName ) { return false; }
bool CHTBaseParamTable::HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName ) { return false; }
bool CHTBaseParamTable::HT_bGetName( CHTString* pstrName ) { return false; }
#endif
bool CHTBaseParamTable::HT_bGetMonsterLevel( const int id, byte* pbyteLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterClass( const int id, byte* pbyteClass ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSize( const int id, byte* pbyteSize ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAI( const int id, int* piAI ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHelpCond( const int id, byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHelpCondCount( const int id, byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLinkCond( const int id, byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLinkCondCount( const int id, byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterCantDetect( const int id, int* piCantDetect ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMovement( const int id, byte* pbyteMovement ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMuscle( const int id, short* psMuscle ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterNerves( const int id, short* psNerves ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHeart( const int id, short* psHeart ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMind( const int id, short* psMind ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHP( const int id, unsigned int* pnHP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAttackRate( const int id, int* piAttackRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterBlockRate( const int id, byte* pbyteBlockRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterCriticalRate( const int id, byte* pbyteCriticalRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAC( const int id, int* piAC ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFireResist( const int id, int* piFireResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterColdResist( const int id, int* piColdResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLightningResist( const int id, int* piLightningResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFly( const int id, byte* pbFly ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill0( const int id, int* pidSkill0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill1( const int id, int* pidSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill2( const int id, int* pidSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill3( const int id, int* pidSkill3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill4( const int id, int* pidSkill4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill5( const int id, int* pidSkill5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill6( const int id, int* pidSkill6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill7( const int id, int* pidSkill7 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterImmunity( const int id, int* piImmunity ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterItem9DeadCount( const int id, unsigned int* pnItem9DeadCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetMonsterLevel( byte* pbyteLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterClass( byte* pbyteClass ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSize( byte* pbyteSize ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAI( int* piAI ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAggrCond( byte* pbyteAggrCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFleeCond( byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterTraceCond( byte* pbyteTraceCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHelpCond( byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHelpCondCount( byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLinkCond( byte* pbyteFleeCond ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLinkCondCount( byte* pbyteFleeCondCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterBlockedCell( int* piBlockedCell ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterCantDetect( int* piCantDetect ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterNormalSight( byte* pbyteNormalSight ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterCombatSight( byte* pbyteCombatSight ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMovement( byte* pbyteMovement ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterEventNo( unsigned int* pnEventNo ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMuscle( short* psMuscle ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterNerves( short* psNerves ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHeart( short* psHeart ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterMind( short* psMind ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterArmorType( byte* pbyteArmorType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHP( unsigned int* pnHP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAttackRate( int* piAttackRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterDodgeRate( int* piDodgeRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterBlockRate( byte* pbyteBlockRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterCriticalRate( byte* pbyteCriticalRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterAC( int* piAC ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFireResist( int* piFireResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterColdResist( int* piColdResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterLightningResist( int* piLightningResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterPoisonResist( int* piPoisonResist ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterWalkSpeed( int* piWalkSpeed ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRunSpeed( int* piRunSpeed ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterFly( byte* pbFly ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill0( int* pidSkill0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill1( int* pidSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill2( int* pidSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill3( int* pidSkill3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill4( int* pidSkill4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill5( int* pidSkill5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill6( int* pidSkill6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkill7( int* pidSkill7 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterImmunity( int* piImmunity ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardGold( unsigned int* pnRewardGold ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem0ItemID( short* psItem0ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem0DropRate( short* psItem0DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem1ItemID( short* psItem1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem1DropRate( short* psItem1DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem2ItemID( short* psItem2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem2DropRate( short* psItem2DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem3ItemID( short* psItem3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem3DropRate( short* psItem3DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem4ItemID( short* psItem4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem4DropRate( short* psItem4DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem5ItemID( short* psItem5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem5DropRate( short* psItem5DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem6ItemID( short* psItem6ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem6DropRate( short* psItem6DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem7ItemID( short* psItem7ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem7DropRate( short* psItem7DropRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem8DropRate( short* psItem8DropRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterItem8DeadCount( unsigned int* pnItem8DeadCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterItem9DropRate( short* psItem9DropRate ) { return false; }
//bool CHTBaseParamTable::HT_bGetMonsterItem9DeadCount( unsigned int* pnItem9DeadCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve0( byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve1( byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve2( byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve3( byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve4( byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve5( byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve6( byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterReserve7( byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillType( byte* pbyteType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCombatPhase( short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSpeechContent( short* psSpeechContent ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillDuration( int* piDuration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillRange( int* piRange ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillAttackType( byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastingTime( int* piCastingTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillActivateTime( int* piActivateTime ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCastCount( byte* pbyteCastCount ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1ID( int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Function( int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2ID( int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Function( int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3ID( int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Function( int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4ID( int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Function( int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5ID( int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Function( int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCostTP( int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillCostHP( int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillidCostItem( int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillidReqItem( int* pidReqItem ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqTribe( int* piReqTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl ) { return false; }                                              
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillType( byte* pbyteType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCombatPhase( short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillDuration( int* piDuration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCoolDownTime( int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillRange( int* piRange ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAllowedTarget( int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillAttackType( byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillFollowRange( byte* pbyteFollowRange ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillPierceRate( byte* pbytePierceRate ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReadyTime( int* piReadyTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCastingTime( int* piCastingTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillApplyTime( int* piApplyTime ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1ID( int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Function( int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Duration( int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2ID( int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Function( int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Duration( int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3ID( int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Function( int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Duration( int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4ID( int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Function( int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Duration( int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5ID( int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Function( int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Duration( int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostTP( int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostHP( int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillidCostItem( int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqWeaponType( int* piReqWeaponType ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillidReqItem( int* pidReqItem ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqLevel( byte* pbyteReqLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqTribe( int* piReqTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqClass( int* piReqClass ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill1( int* pidReqSkill1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill2( int* pidReqSkill2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl ) { return false; }   
bool CHTBaseParamTable::HT_bGetPCSkillReserve0( byte* pbyteReserve0 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve1( byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve2( byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve3( byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve4( byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve5( byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve6( byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetPCSkillReserve7( byte* pbyteReserve7 ) { return false; }

bool CHTBaseParamTable::HT_bGetItemLevel( const int id, byte* pbyteLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetItemClass( const int id, byte* pbyteClass ) { return false; }
bool CHTBaseParamTable::HT_bGetItemType( const int id, short* psType) { return false; }
bool CHTBaseParamTable::HT_bGetItemRupiah( const int id, int* piRupiah ) { return false; }
bool CHTBaseParamTable::HT_bGetItemSellRupiah( const int id, int* piSellRupiah ) { return false; }
bool CHTBaseParamTable::HT_bGetItemMaxDurability( const int id, short* psMaxDurability ) { return false; }
bool CHTBaseParamTable::HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCombatPhase( const int id, short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1ID( const int id, int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Function( const int id, int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2ID( const int id, int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Function( const int id, int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3ID( const int id, int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Function( const int id, int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4ID( const int id, int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Function( const int id, int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5ID( const int id, int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Function( const int id, int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetItemRange( const int id, byte* pbyteRange ) { return false; }
bool CHTBaseParamTable::HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetItemArmorType( const int id, byte* pbyteArmorType ) { return false; }
bool CHTBaseParamTable::HT_bGetItemAttackType( const int id, byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCostTP( const int id, int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCostHP( const int id, int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetItemidCostItem( const int id, int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitTribe( const int id, int* piLimitTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType ) { return false; }	
bool CHTBaseParamTable::HT_bGetItemEventID( const int id, short* psEventID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCash( const int id, int* piCash ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve1( const int id, byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve2( const int id, byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve3( const int id, byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve4( const int id, byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve5( const int id, byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve6( const int id, byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemTimeLimit( const int id, short* psTimeLimit ) { return false; }
bool CHTBaseParamTable::HT_bGetItemFXEffectID( const int id, int* pidFX ) { return false; }

bool CHTBaseParamTable::HT_bGetItemLevel( byte* pbyteLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetItemClass( byte* pbyteClass ) { return false; }
bool CHTBaseParamTable::HT_bGetItemType( short* psType) { return false; }
bool CHTBaseParamTable::HT_bGetItemRupiah( int* piRupiah ) { return false; }
bool CHTBaseParamTable::HT_bGetItemSellRupiah( int* piSellRupiah ) { return false; }
bool CHTBaseParamTable::HT_bGetItemMaxDurability( short* psMaxDurability ) { return false; }
bool CHTBaseParamTable::HT_bGetItemMaxCount( byte* pbyteMaxCount ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCombatPhase( short* psCombatPhase ) { return false; }
bool CHTBaseParamTable::HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1ID( int* piEffect1ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Function( int* piEffect1Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Duration( int* piEffect1Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Param1( int* piEffect1Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect1Param2( int* piEffect1Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2ID( int* piEffect2ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Function( int* piEffect2Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Duration( int* piEffect2Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Param1( int* piEffect2Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect2Param2( int* piEffect2Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3ID( int* piEffect3ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Function( int* piEffect3Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Duration( int* piEffect3Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Param1( int* piEffect3Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect3Param2( int* piEffect3Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4ID( int* piEffect4ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Function( int* piEffect4Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Duration( int* piEffect4Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Param1( int* piEffect4Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect4Param2( int* piEffect4Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5ID( int* piEffect5ID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Function( int* piEffect5Function ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Duration( int* piEffect5Duration ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Param1( int* piEffect5Param1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemEffect5Param2( int* piEffect5Param2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCoolDownTime( int* piCoolDownTime ) { return false; }
bool CHTBaseParamTable::HT_bGetItemRange( byte* pbyteRange ) { return false; }
bool CHTBaseParamTable::HT_bGetItemAllowedTarget( int* piAllowedTarget ) { return false; }
bool CHTBaseParamTable::HT_bGetItemArmorType( byte* pbyteArmorType ) { return false; }
bool CHTBaseParamTable::HT_bGetItemAttackType( byte* pbyteAttackType ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCostTP( int* piCostTP ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCostHP( int* piCostHP ) { return false; }
bool CHTBaseParamTable::HT_bGetItemidCostItem( int* pidCostItem ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitTribe( int* piLimitTribe ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitLevel( byte* pbyteLimitLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra ) { return false; }
bool CHTBaseParamTable::HT_bGetItemRefinableItemType( int* piRefinableItemType ) { return false; }	
bool CHTBaseParamTable::HT_bGetItemEventID( short* psEventID ) { return false; }
bool CHTBaseParamTable::HT_bGetItemCash( int* piCash ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve1( byte* pbyteReserve1 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve2( byte* pbyteReserve2 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve3( byte* pbyteReserve3 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve4( byte* pbyteReserve4 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve5( byte* pbyteReserve5 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemReserve6( byte* pbyteReserve6 ) { return false; }
bool CHTBaseParamTable::HT_bGetItemTimeLimit( short* psTimeLimit ) { return false; }
bool CHTBaseParamTable::HT_bGetItemFXEffectID( int* pidFX ) { return false; }

bool CHTBaseParamTable::HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem ) { return false; }

// NPC
bool CHTBaseParamTable::HT_bGetNPCSize( const int id, byte* pbyteSize ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCZone( const int id, byte* pbyteZone ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti ) { return false; }
int CHTBaseParamTable::HT_iGetNPCSellingItemCount( const int id ) { return -1; }
bool CHTBaseParamTable::HT_bGetNPCSellingItem( const int id, const int index, int* pidItem ) { return false; }

bool CHTBaseParamTable::HT_bGetNPCSize( byte* pbyteSize ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCZone( byte* pbyteZone ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCPosition( short* psPosX, short* psPosZ ) { return false; }
bool CHTBaseParamTable::HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti ) { return false; }
int CHTBaseParamTable::HT_iGetNPCSellingItemCount() { return -1; }
bool CHTBaseParamTable::HT_bGetNPCSellingItem( const int index, int* pidItem ) { return false; }
// Portal
bool CHTBaseParamTable::HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel ) { return false; }
bool CHTBaseParamTable::HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
short* psStartX, short* psStartZ, short* psEndX, short* psEndZ) { return false; }
bool CHTBaseParamTable::HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee ) { return false; }
bool CHTBaseParamTable::HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel) { return false; }
bool CHTBaseParamTable::HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel ) { return false; }

// TaskQuest
bool CHTBaseParamTable::HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 ) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource6( const int id,/* short* psNPCID, */byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6) { return false; }

bool CHTBaseParamTable::HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5) { return false; }
bool CHTBaseParamTable::HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel) { return false; }

bool CHTBaseParamTable::HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 ) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource2( /* short* psNPCID,*/byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource3( /* short* psNPCID,*/byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource4( /* short* psNPCID,*/byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource5( /* short* psNPCID,*/byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5) { return false; }
bool CHTBaseParamTable::HT_bGetTaskSource6( /*short* psNPCID, */byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6) { return false; }

bool CHTBaseParamTable::HT_bGetTaskReward1( /* short* psNPCID,*/byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward2( /* short* psNPCID,*/byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward3( /* short* psNPCID,*/byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward4( /* short* psNPCID,*/byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4) { return false; }
bool CHTBaseParamTable::HT_bGetTaskReward5( /* short* psNPCID,*/byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5) { return false; }
bool CHTBaseParamTable::HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel) { return false; }

CHTMonsterParamTable::CHTMonsterParamTable() : m_pParam ( 0 )
{}

CHTMonsterParamTable::~CHTMonsterParamTable()
{
	HTMonsterParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool
	CHTMonsterParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTMonsterParam_It itTable = m_mapTable.begin();

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
	CHTMonsterParamTable::HT_bLockID( const int id, const byte byteLevel )
{
	if( m_pParam != NULL )
		return false;

	HTMonsterParam_It itTable = m_mapTable.find( id );
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
	CHTMonsterParamTable::HT_bUnLockID( const int id, const byte byteLevel )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ.. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTMonsterParam;

		HT_LOADCELL( _T("ID"),					iID,							int );
		HT_LOADCELL( _T("byteLevel"), 			pRecord->byteLevel,				byte ); 
		HT_LOADCELL( _T("byteClass"), 			pRecord->byteClass,				byte );  
		HT_LOADCELL( _T("byteSize"), 			pRecord->byteSize,				byte );
		HT_LOADCELL( _T("iAI"), 				pRecord->iAI,					int );
		HT_LOADCELL( _T("byteSelectTargetTime"),pRecord->byteSelectTargetTime,	byte );
		HT_LOADCELL( _T("byteSelectTarget0"),	pRecord->byteSelectTarget0,		byte );
		HT_LOADCELL( _T("byteSelectTarget1"),	pRecord->byteSelectTarget1,		byte );
		HT_LOADCELL( _T("byteSelectTarget2"),	pRecord->byteSelectTarget2,		byte );
		HT_LOADCELL( _T("byteSelectTarget3"),	pRecord->byteSelectTarget3,		byte );
		HT_LOADCELL( _T("byteAggrCond"), 		pRecord->byteAggrCond,			byte );
		HT_LOADCELL( _T("byteFleeCond"), 		pRecord->byteFleeCond,			byte );
		HT_LOADCELL( _T("byteFleeCondCount"), 	pRecord->byteFleeCondCount,		byte );
		HT_LOADCELL( _T("byteTraceCond"), 		pRecord->byteTraceCond,			byte );
		HT_LOADCELL( _T("byteStepBaclCond"), 	pRecord->byteStepBackCond,		byte );
		HT_LOADCELL( _T("byteHelpCond"), 		pRecord->byteHelpCond,			byte );
		HT_LOADCELL( _T("byteHelpCondCount"), 	pRecord->byteHelpCondCount,		byte );
		HT_LOADCELL( _T("byteLinkCond"), 		pRecord->byteLinkCond,			byte );
		HT_LOADCELL( _T("byteLinkCondCount"), 	pRecord->byteLinkCondCount,		byte );
		HT_LOADCELL( _T("iBlockedCell"), 		pRecord->iBlockedCell,			int );
		HT_LOADCELL( _T("iCantDetect"), 		pRecord->iCantDetect,			int );
		HT_LOADCELL( _T("byteTrimuriti"), 		pRecord->byteTrimuriti,			byte );
		HT_LOADCELL( _T("byteNormalSight"), 	pRecord->byteNormalSight,		byte );
		HT_LOADCELL( _T("byteCombatSight"), 	pRecord->byteCombatSight,		byte );
		HT_LOADCELL( _T("nPopDelayMin"), 		pRecord->nPopDelayMin,			unsigned int );
		HT_LOADCELL( _T("nPopDelayMax"), 		pRecord->nPopDelayMax,			unsigned int );	
		HT_LOADCELL( _T("byteMovement"), 		pRecord->byteMovement,			byte );
		HT_LOADCELL( _T("byteSpeechRate"), 		pRecord->byteSpeechRate,		byte );
		HT_LOADCELL( _T("byteSpeechAI"), 		pRecord->byteSpeechAI,			byte );
		HT_LOADCELL( _T("nEventNo"), 			pRecord->nEventNo,				unsigned int );
		HT_LOADCELL( _T("sMuscle"), 			pRecord->sMuscle,				short );
		HT_LOADCELL( _T("sNerves"), 			pRecord->sNerves,				short );
		HT_LOADCELL( _T("sHeart"), 				pRecord->sHeart,				short );
		HT_LOADCELL( _T("sMind"), 				pRecord->sMind,					short );
		HT_LOADCELL( _T("byteArmorType"), 		pRecord->byteArmorType,			byte );
		HT_LOADCELL( _T("nHP"), 				pRecord->nHP,					unsigned int );
		HT_LOADCELL( _T("byteHPRecovery"), 		pRecord->byteHPRecovery,		byte );
		HT_LOADCELL( _T("iAttackRate"), 		pRecord->iAttackRate,			int );
		HT_LOADCELL( _T("iDodgeRate"), 			pRecord->iDodgeRate,			int );	
		//HT_LOADCELL( _T("byteBlockRate"), 		pRecord->byteBlockRate,		byte );
		//HT_LOADCELL( _T("byteCriticalRate"), 	pRecord->byteCriticalRate,		byte );
		HT_LOADCELL( _T("iAC"), 				pRecord->iAC,					int );
		HT_LOADCELL( _T("iFireResist"), 		pRecord->iFireResist,			int );
		HT_LOADCELL( _T("iColdResist"), 		pRecord->iColdResist,			int );
		HT_LOADCELL( _T("iLightningResist"),	pRecord->iLightningResist,		int );
		HT_LOADCELL( _T("iPosisonResist"), 		pRecord->iPoisonResist,			int );
		HT_LOADCELL( _T("iWalkSpeed"), 			pRecord->iWalkSpeed,			int );
		HT_LOADCELL( _T("iRunSpeed"), 			pRecord->iRunSpeed,				int );
		HT_LOADCELL( _T("bFly"), 				pRecord->bFly,					byte );
		HT_LOADCELL( _T("idSkill0"), 			pRecord->idSkill0,				int );
		HT_LOADCELL( _T("idSkill1"), 			pRecord->idSkill1,				int );
		HT_LOADCELL( _T("idSkill2"), 			pRecord->idSkill2,				int );
		HT_LOADCELL( _T("idSkill3"), 			pRecord->idSkill3,				int );
		HT_LOADCELL( _T("idSkill4"), 			pRecord->idSkill4,				int );
		HT_LOADCELL( _T("idSkill5"), 			pRecord->idSkill5,				int );
		HT_LOADCELL( _T("idSkill6"), 			pRecord->idSkill6,				int );
		HT_LOADCELL( _T("idSkill7"), 			pRecord->idSkill7,				int );
		HT_LOADCELL( _T("byteSkillPattern0"), 	pRecord->byteSkillPattern0,		byte );
		HT_LOADCELL( _T("byteSkillPattern1"), 	pRecord->byteSkillPattern1,		byte );
		HT_LOADCELL( _T("byteSkillPattern2"), 	pRecord->byteSkillPattern2,		byte );
		HT_LOADCELL( _T("byteSkillPattern3"), 	pRecord->byteSkillPattern3,		byte );
		HT_LOADCELL( _T("iImmunity"), 			pRecord->iImmunity,				int );
		HT_LOADCELL( _T("byteResistEffectConst"),pRecord->byteResistEffectConst,byte );
		HT_LOADCELL( _T("nRewardBrahmanPoint"), pRecord->nRewardBrahmanPoint,	unsigned int );
		HT_LOADCELL( _T("nRewardGold"), 		pRecord->nRewardGold,			unsigned int );
		HT_LOADCELL( _T("nRewardPrana"), 		pRecord->nRewardPrana,			unsigned int );
		HT_LOADCELL( _T("sItem0ID"), 			pRecord->sItem0ID,				short );
		HT_LOADCELL( _T("sItem0DropRate"),		pRecord->sItem0DropRate,		short );
		HT_LOADCELL( _T("sItem1ID"), 			pRecord->sItem1ID,				short );
		HT_LOADCELL( _T("sItem1DropRate"), 		pRecord->sItem1DropRate,		short );
		HT_LOADCELL( _T("sItem2ID"), 			pRecord->sItem2ID,				short );
		HT_LOADCELL( _T("sItem2DropRate"), 		pRecord->sItem2DropRate,		short );
		HT_LOADCELL( _T("sItem3ID"), 			pRecord->sItem3ID,				short );
		HT_LOADCELL( _T("sItem3DropRate"),		pRecord->sItem3DropRate,		short );
		HT_LOADCELL( _T("sItem4ID"), 			pRecord->sItem4ID,				short );
		HT_LOADCELL( _T("sItem4DropRate"),		pRecord->sItem4DropRate,		short );
		HT_LOADCELL( _T("sItem5ID"), 			pRecord->sItem5ID,				short );
		HT_LOADCELL( _T("sItem5DropRate"), 		pRecord->sItem5DropRate,		short );
		HT_LOADCELL( _T("sItem6ID"), 			pRecord->sItem6ID,				short );
		HT_LOADCELL( _T("sItem6DropRate"), 		pRecord->sItem6DropRate,		short );
		HT_LOADCELL( _T("sItem7ID"), 			pRecord->sItem7ID,				short );
		HT_LOADCELL( _T("sItem7DropRate"), 		pRecord->sItem7DropRate,		short );
		HT_LOADCELL( _T("byteItem8Grade"), 		pRecord->byteItem8Grade,		byte );
		HT_LOADCELL( _T("sItem8DropRate"), 		pRecord->sItem8DropRate,		short );
		//HT_LOADCELL( _T("nItem8DeadCount"), 	pRecord->nItem8DeadCount,		unsigned int );
		HT_LOADCELL( _T("byteItem9Grade"), 		pRecord->byteItem9Grade,		byte );
		HT_LOADCELL( _T("sItem9DropRate"), 		pRecord->sItem9DropRate,		short );
		//HT_LOADCELL( _T("nItem9DeadCount"), 	pRecord->nItem9DeadCount,		unsigned int );
		HT_LOADCELL( _T("byteReserve0"), 		pRecord->byteReserve0,			byte );
		HT_LOADCELL( _T("byteReserve1"), 		pRecord->byteReserve1,			byte );
		HT_LOADCELL( _T("byteReserve2"), 		pRecord->byteReserve2,			byte );
		HT_LOADCELL( _T("byteReserve3"), 		pRecord->byteReserve3,			byte );
		HT_LOADCELL( _T("byteReserve4"), 		pRecord->byteReserve4,			byte );
		HT_LOADCELL( _T("byteReserve5"), 		pRecord->byteReserve5,			byte );
		HT_LOADCELL( _T("byteReserve6"), 		pRecord->byteReserve6,			byte );
		HT_LOADCELL( _T("byteReserve7"), 		pRecord->byteReserve7,			byte );

		m_mapTable.insert( HTMonsterParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
	CHTMonsterParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTMonsterParam* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTMonsterParam;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTMonsterParam) );

		m_mapTable.insert( HTMonsterParam_Value( iID, pRecord ) );
	}

	return true;
}

bool
	CHTMonsterParamTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTMonsterParam_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTMonsterParam) );

		itTable++;
	}

	return true;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLevel( const int id, byte* pbyteLevel )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
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
	CHTMonsterParamTable::HT_bGetMonsterClass( const int id, byte* pbyteClass )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
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
	CHTMonsterParamTable::HT_bGetMonsterSize( const int id, byte* pbyteSize )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
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
	CHTMonsterParamTable::HT_bGetMonsterAI( const int id, int* piAI )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAI = (itTable->second)->iAI;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSelectTargetTime = (itTable->second)->byteSelectTargetTime;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSelectTarget0 = (itTable->second)->byteSelectTarget0;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSelectTarget1 = (itTable->second)->byteSelectTarget1;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSelectTarget2 = (itTable->second)->byteSelectTarget2;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSelectTarget3 = (itTable->second)->byteSelectTarget3;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteAggrCond = (itTable->second)->byteAggrCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteFleeCond = (itTable->second)->byteFleeCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteFleeCondCount = (itTable->second)->byteFleeCondCount;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteTraceCond = (itTable->second)->byteTraceCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteStepBackCond = (itTable->second)->byteStepBackCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHelpCond( const int id, byte* pbyteHelpCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteHelpCond = (itTable->second)->byteHelpCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHelpCondCount( const int id, byte* pbyteHelpCondCount )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteHelpCondCount = (itTable->second)->byteHelpCondCount;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLinkCond( const int id, byte* pbyteLinkCond )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteLinkCond = (itTable->second)->byteLinkCond;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLinkCondCount( const int id, byte* pbyteLinkCondCount )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteLinkCondCount = (itTable->second)->byteLinkCondCount;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBlockedCell = (itTable->second)->iBlockedCell;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterCantDetect( const int id, int* piCantDetect )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCantDetect = (itTable->second)->iCantDetect;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteTrimuriti = (itTable->second)->byteTrimuriti;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteNormalSight = (itTable->second)->byteNormalSight;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteCombatSight = (itTable->second)->byteCombatSight;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnPopDelayMin = (itTable->second)->nPopDelayMin;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnPopDelayMax = (itTable->second)->nPopDelayMax;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMovement( const int id, byte* pbyteMovement )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteMovement = (itTable->second)->byteMovement;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSpeechRate = (itTable->second)->byteSpeechRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSpeechAI = (itTable->second)->byteSpeechAI;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnEventNo = (itTable->second)->nEventNo;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMuscle( const int id, short* psMuscle )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psMuscle = (itTable->second)->sMuscle;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterNerves( const int id, short* psNerves )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psNerves = (itTable->second)->sNerves;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHeart( const int id, short* psHeart )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psHeart = (itTable->second)->sHeart;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMind( const int id, short* psMind )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psMind = (itTable->second)->sMind;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
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
	CHTMonsterParamTable::HT_bGetMonsterHP( const int id, unsigned int* pnHP )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnHP = (itTable->second)->nHP;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteHPRecovery = (itTable->second)->byteHPRecovery;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAttackRate( const int id, int* piAttackRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackRate = (itTable->second)->iAttackRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDodgeRate = (itTable->second)->iDodgeRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAC( const int id, int* piAC )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAC = (itTable->second)->iAC;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFireResist( const int id, int* piFireResist )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piFireResist = (itTable->second)->iFireResist;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterColdResist( const int id, int* piColdResist )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piColdResist = (itTable->second)->iColdResist;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLightningResist( const int id, int* piLightningResist )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLightningResist = (itTable->second)->iLightningResist;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piPoisonResist = (itTable->second)->iPoisonResist;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piWalkSpeed = (itTable->second)->iWalkSpeed;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRunSpeed = (itTable->second)->iRunSpeed;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFly( const int id, byte* pbFly )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
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
	CHTMonsterParamTable::HT_bGetMonsterSkill0( const int id, int* piSkill0 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill0 = (itTable->second)->idSkill0;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill1( const int id, int* piSkill1 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill1 = (itTable->second)->idSkill1;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill2( const int id, int* piSkill2 )

{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill2 = (itTable->second)->idSkill2;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill3( const int id, int* piSkill3 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill3 = (itTable->second)->idSkill3;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill4( const int id, int* piSkill4 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill4 = (itTable->second)->idSkill4;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill5( const int id, int* piSkill5 )

{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill5 = (itTable->second)->idSkill5;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill6( const int id, int* piSkill6 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill6 = (itTable->second)->idSkill6;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill7( const int id, int* piSkill7 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill7 = (itTable->second)->idSkill7;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSkillPattern0 = (itTable->second)->byteSkillPattern0;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSkillPattern1 = (itTable->second)->byteSkillPattern1;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSkillPattern2 = (itTable->second)->byteSkillPattern2;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteSkillPattern3 = (itTable->second)->byteSkillPattern3;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterImmunity( const int id, int* piImmunity )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piImmunity = (itTable->second)->iImmunity;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteResistEffectConst = (itTable->second)->byteResistEffectConst;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnRewardBrahmanPoint = (itTable->second)->nRewardBrahmanPoint;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnRewardGold = (itTable->second)->nRewardGold;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pnRewardPrana = (itTable->second)->nRewardPrana;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem0ID = (itTable->second)->sItem0ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem0DropRate = (itTable->second)->sItem0DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem1ID = (itTable->second)->sItem1ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem1DropRate = (itTable->second)->sItem1DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem2ID = (itTable->second)->sItem2ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem2DropRate = (itTable->second)->sItem2DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem3ID = (itTable->second)->sItem3ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem3DropRate = (itTable->second)->sItem3DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem4ID = (itTable->second)->sItem4ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem4DropRate = (itTable->second)->sItem4DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem5ID = (itTable->second)->sItem5ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate )

{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem5DropRate = (itTable->second)->sItem5DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID )

{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem6ID = (itTable->second)->sItem6ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem6DropRate = (itTable->second)->sItem6DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem7ID = (itTable->second)->sItem7ID;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem7DropRate = (itTable->second)->sItem7DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteItem8Grade = (itTable->second)->byteItem8Grade;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem8DropRate = (itTable->second)->sItem8DropRate;
			return true;
		}
	}
	return false;
}

//bool
//CHTMonsterParamTable::HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount )
//{
//	HTMonsterParam_It itTable = m_mapTable.find( id );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			*pnItem8DeadCount = (itTable->second)->nItem8DeadCount;
//			return true;
//		}
//	}
//	return false;
//}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteItem9Grade = (itTable->second)->byteItem9Grade;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psItem9DropRate = (itTable->second)->sItem9DropRate;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve0 = (itTable->second)->byteReserve0;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve1 = (itTable->second)->byteReserve1;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve2 = (itTable->second)->byteReserve2;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve3 = (itTable->second)->byteReserve3;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve4 = (itTable->second)->byteReserve4;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve5 = (itTable->second)->byteReserve5;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve6 = (itTable->second)->byteReserve6;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7 )
{
	HTMonsterParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve7 = (itTable->second)->byteReserve7;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLevel( byte* pbyteLevel )
{
	if ( m_pParam )
	{
		*pbyteLevel = m_pParam->byteLevel;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterClass( byte* pbyteClass )
{
	if ( m_pParam )
	{
		*pbyteClass = m_pParam->byteClass;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSize( byte* pbyteSize )
{
	if ( m_pParam )
	{
		*pbyteSize = m_pParam->byteSize;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAI( int* piAI )
{
	if ( m_pParam )
	{
		*piAI = m_pParam->iAI;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime )
{
	if ( m_pParam )
	{
		*pbyteSelectTargetTime = m_pParam->byteSelectTargetTime;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 )
{
	if ( m_pParam )
	{
		*pbyteSelectTarget0 = m_pParam->byteSelectTarget0;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 )
{
	if ( m_pParam )
	{
		*pbyteSelectTarget1 = m_pParam->byteSelectTarget1;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 )
{
	if ( m_pParam )
	{
		*pbyteSelectTarget2 = m_pParam->byteSelectTarget2;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 )
{
	if ( m_pParam )
	{
		*pbyteSelectTarget3 = m_pParam->byteSelectTarget3;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAggrCond( byte* pbyteAggrCond )
{
	if ( m_pParam )
	{
		*pbyteAggrCond = m_pParam->byteAggrCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFleeCond( byte* pbyteFleeCond )
{
	if ( m_pParam )
	{
		*pbyteFleeCond = m_pParam->byteFleeCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount )
{
	if ( m_pParam )
	{
		*pbyteFleeCondCount = m_pParam->byteFleeCondCount;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterTraceCond( byte* pbyteTraceCond )
{
	if ( m_pParam )
	{
		*pbyteTraceCond = m_pParam->byteTraceCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond )
{
	if ( m_pParam )
	{
		*pbyteStepBackCond = m_pParam->byteStepBackCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHelpCond( byte* pbyteHelpCond )
{
	if ( m_pParam )
	{
		*pbyteHelpCond = m_pParam->byteHelpCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHelpCondCount( byte* pbyteHelpCondCount )
{
	if ( m_pParam )
	{
		*pbyteHelpCondCount = m_pParam->byteHelpCondCount;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLinkCond( byte* pbyteLinkCond )
{
	if ( m_pParam )
	{
		*pbyteLinkCond = m_pParam->byteLinkCond;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLinkCondCount( byte* pbyteLinkCondCount )
{
	if ( m_pParam )
	{
		*pbyteLinkCondCount = m_pParam->byteLinkCondCount;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterBlockedCell( int* piBlockedCell )
{
	if ( m_pParam )
	{
		*piBlockedCell = m_pParam->iBlockedCell;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterCantDetect( int* piCantDetect )
{
	if ( m_pParam )
	{
		*piCantDetect = m_pParam->iCantDetect;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti )
{
	if ( m_pParam )
	{
		*pbyteTrimuriti = m_pParam->byteTrimuriti;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterNormalSight( byte* pbyteNormalSight )
{
	if ( m_pParam )
	{
		*pbyteNormalSight = m_pParam->byteNormalSight;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterCombatSight( byte* pbyteCombatSight )
{
	if ( m_pParam )
	{
		*pbyteCombatSight = m_pParam->byteCombatSight;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin )
{
	if ( m_pParam )
	{
		*pnPopDelayMin = m_pParam->nPopDelayMin;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax )
{
	if ( m_pParam )
	{
		*pnPopDelayMax = m_pParam->nPopDelayMax;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMovement( byte* pbyteMovement )
{
	if ( m_pParam )
	{
		*pbyteMovement = m_pParam->byteMovement;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate )
{
	if ( m_pParam )
	{
		*pbyteSpeechRate = m_pParam->byteSpeechRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI )
{
	if ( m_pParam )
	{
		*pbyteSpeechAI = m_pParam->byteSpeechAI;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterEventNo( unsigned int* pnEventNo )
{
	if ( m_pParam )
	{
		*pnEventNo = m_pParam->nEventNo;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMuscle( short* psMuscle )
{
	if ( m_pParam )
	{
		*psMuscle = m_pParam->sMuscle;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterNerves( short* psNerves )
{
	if ( m_pParam )
	{
		*psNerves = m_pParam->sNerves;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHeart( short* psHeart )
{
	if ( m_pParam )
	{
		*psHeart = m_pParam->sHeart;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterMind( short* psMind )
{
	if ( m_pParam )
	{
		*psMind = m_pParam->sMind;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterArmorType( byte* pbyteArmorType )
{
	if ( m_pParam )
	{
		*pbyteArmorType = m_pParam->byteArmorType;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHP( unsigned int* pnHP )
{
	if ( m_pParam )
	{
		*pnHP = m_pParam->nHP;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery )
{
	if ( m_pParam )
	{
		*pbyteHPRecovery = m_pParam->byteHPRecovery;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAttackRate( int* piAttackRate )
{
	if ( m_pParam )
	{
		*piAttackRate = m_pParam->iAttackRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterDodgeRate( int* piDodgeRate )
{
	if ( m_pParam )
	{
		*piDodgeRate = m_pParam->iDodgeRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterAC( int* piAC )
{
	if ( m_pParam )
	{
		*piAC = m_pParam->iAC;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFireResist( int* piFireResist )
{
	if ( m_pParam )
	{
		*piFireResist = m_pParam->iFireResist;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterColdResist( int* piColdResist )
{
	if ( m_pParam )
	{
		*piColdResist = m_pParam->iColdResist;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterLightningResist( int* piLightningResist )
{
	if ( m_pParam )
	{
		*piLightningResist = m_pParam->iLightningResist;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterPoisonResist( int* piPoisonResist )
{
	if ( m_pParam )
	{
		*piPoisonResist = m_pParam->iPoisonResist;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterWalkSpeed( int* piWalkSpeed )
{
	if ( m_pParam )
	{
		*piWalkSpeed = m_pParam->iWalkSpeed;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRunSpeed( int* piRunSpeed )
{
	if ( m_pParam )
	{
		*piRunSpeed = m_pParam->iRunSpeed;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterFly( byte* pbFly )
{
	if ( m_pParam )
	{
		*pbFly = m_pParam->bFly;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill0( int* pidSkill0 )
{
	if ( m_pParam )
	{
		*pidSkill0 = m_pParam->idSkill0;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill1( int* pidSkill1 )
{
	if ( m_pParam )
	{
		*pidSkill1 = m_pParam->idSkill1;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill2( int* pidSkill2 )
{
	if ( m_pParam )
	{
		*pidSkill2 = m_pParam->idSkill2;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill3( int* pidSkill3 )
{
	if ( m_pParam )
	{
		*pidSkill3 = m_pParam->idSkill3;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill4( int* pidSkill4 )
{
	if ( m_pParam )
	{
		*pidSkill4 = m_pParam->idSkill4;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill5( int* pidSkill5 )
{
	if ( m_pParam )
	{
		*pidSkill5 = m_pParam->idSkill5;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill6( int* pidSkill6 )
{
	if ( m_pParam )
	{
		*pidSkill6 = m_pParam->idSkill6;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkill7( int* pidSkill7 )
{
	if ( m_pParam )
	{
		*pidSkill7 = m_pParam->idSkill7;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 )
{
	if ( m_pParam )
	{
		*pbyteSkillPattern0 = m_pParam->byteSkillPattern0;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 )
{
	if ( m_pParam )
	{
		*pbyteSkillPattern1 = m_pParam->byteSkillPattern1;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 )
{
	if ( m_pParam )
	{
		*pbyteSkillPattern2 = m_pParam->byteSkillPattern2;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 )
{
	if ( m_pParam )
	{
		*pbyteSkillPattern3 = m_pParam->byteSkillPattern3;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterImmunity( int* piImmunity )
{
	if ( m_pParam )
	{
		*piImmunity = m_pParam->iImmunity;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst )
{
	if ( m_pParam )
	{
		*pbyteResistEffectConst = m_pParam->byteResistEffectConst;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint )
{
	if ( m_pParam )
	{
		*pnRewardBrahmanPoint = m_pParam->nRewardBrahmanPoint;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardGold( unsigned int* pnRewardGold )
{
	if ( m_pParam )
	{
		*pnRewardGold = m_pParam->nRewardGold;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana )
{
	if ( m_pParam )
	{
		*pnRewardPrana = m_pParam->nRewardPrana;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem0ItemID( short* psItem0ID )
{
	if ( m_pParam )
	{
		*psItem0ID = m_pParam->sItem0ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem0DropRate( short* psItem0DropRate )
{
	if ( m_pParam )
	{
		*psItem0DropRate = m_pParam->sItem0DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem1ItemID( short* psItem1ID )
{
	if ( m_pParam )
	{
		*psItem1ID = m_pParam->sItem1ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem1DropRate( short* psItem1DropRate )
{
	if ( m_pParam )
	{
		*psItem1DropRate = m_pParam->sItem1DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem2ItemID( short* psItem2ID )
{
	if ( m_pParam )
	{
		*psItem2ID = m_pParam->sItem2ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem2DropRate( short* psItem2DropRate )
{
	if ( m_pParam )
	{
		*psItem2DropRate = m_pParam->sItem2DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem3ItemID( short* psItem3ID )
{
	if ( m_pParam )
	{
		*psItem3ID = m_pParam->sItem3ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem3DropRate( short* psItem3DropRate )
{
	if ( m_pParam )
	{
		*psItem3DropRate = m_pParam->sItem3DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem4ItemID( short* psItem4ID )
{
	if ( m_pParam )
	{
		*psItem4ID = m_pParam->sItem4ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem4DropRate( short* psItem4DropRate )
{
	if ( m_pParam )
	{
		*psItem4DropRate = m_pParam->sItem4DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem5ItemID( short* psItem5ID )
{
	if ( m_pParam )
	{
		*psItem5ID = m_pParam->sItem5ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem5DropRate( short* psItem5DropRate )
{
	if ( m_pParam )
	{
		*psItem5DropRate = m_pParam->sItem5DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem6ItemID( short* psItem6ID )
{
	if ( m_pParam )
	{
		*psItem6ID = m_pParam->sItem6ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem6DropRate( short* psItem6DropRate )
{
	if ( m_pParam )
	{
		*psItem6DropRate = m_pParam->sItem6DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem7ItemID( short* psItem7ID )
{
	if ( m_pParam )
	{
		*psItem7ID = m_pParam->sItem7ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem7DropRate( short* psItem7DropRate )
{
	if ( m_pParam )
	{
		*psItem7DropRate = m_pParam->sItem7DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade )
{
	if ( m_pParam )
	{
		*pbyteItem8Grade= m_pParam->byteItem8Grade;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem8DropRate( short* psItem8DropRate )
{
	if ( m_pParam )
	{
		*psItem8DropRate = m_pParam->sItem8DropRate;
		return true;
	}
	return false;
}

//bool
//CHTMonsterParamTable::HT_bGetMonsterItem8DeadCount( unsigned int* pnItem8DeadCount )
//{
//	if ( m_pParam )
//	{
//		*pnItem8DeadCount = m_pParam->nItem8DeadCount;
//		return true;
//	}
//	return false;
//}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade )
{
	if ( m_pParam )
	{
		*pbyteItem9Grade = m_pParam->byteItem9Grade;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterItem9DropRate( short* psItem9DropRate )
{
	if ( m_pParam )
	{
		*psItem9DropRate = m_pParam->sItem9DropRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve0( byte* pbyteReserve0 )
{
	if ( m_pParam )
	{
		*pbyteReserve0 = m_pParam->byteReserve0;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve1( byte* pbyteReserve1 )
{
	if ( m_pParam )
	{
		*pbyteReserve1 = m_pParam->byteReserve1;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve2( byte* pbyteReserve2 )
{
	if ( m_pParam )
	{
		*pbyteReserve2 = m_pParam->byteReserve2;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve3( byte* pbyteReserve3 )
{
	if ( m_pParam )
	{
		*pbyteReserve3 = m_pParam->byteReserve3;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve4( byte* pbyteReserve4 )
{
	if ( m_pParam )
	{
		*pbyteReserve4 = m_pParam->byteReserve4;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve5( byte* pbyteReserve5 )
{
	if ( m_pParam )
	{
		*pbyteReserve5 = m_pParam->byteReserve5;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve6( byte* pbyteReserve6 )
{
	if ( m_pParam )
	{
		*pbyteReserve6 = m_pParam->byteReserve6;
		return true;
	}
	return false;
}

bool
	CHTMonsterParamTable::HT_bGetMonsterReserve7( byte* pbyteReserve7 )
{
	if ( m_pParam )
	{
		*pbyteReserve7 = m_pParam->byteReserve7;
		return true;
	}
	return false;
}

CHTMonsterSkillParamTable::CHTMonsterSkillParamTable() : m_pParam ( 0 )
{}

CHTMonsterSkillParamTable::~CHTMonsterSkillParamTable()
{
	for ( int i = 0; i < HT_PCSKILL_MAXLEVEL; ++i )
	{
		HTMonsterSkillParam_It it = m_arrmapTable[i].begin();
		while ( it != m_arrmapTable[i].end() )
		{
			if ( it->second ) delete (it->second);
			it = m_arrmapTable[i].erase( it );
		}
	}	
}

bool
	CHTMonsterSkillParamTable::HT_bLockID( const int id, const byte byteLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	if( m_pParam != NULL )
		return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bUnLockID( const int id, const byte byteLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ.. -_-
			{
				m_pParam = NULL;
				return true;
			}
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTMonsterSkillParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;
	byte byteLevel;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTMonsterSkillParam;

		HT_LOADCELL( _T("ID"),						iID,								int );
		HT_LOADCELL( _T("byteLevel"),				byteLevel,							byte );
		HT_LOADCELL( _T("byteMaxLevel"),			pRecord->byteMaxLevel,				byte );
		HT_LOADCELL( _T("byteType"),				pRecord->byteType,					byte );
		HT_LOADCELL( _T("sCombatPhase"),			pRecord->sCombatPhase,				short );
		HT_LOADCELL( _T("sSpeechContent"),			pRecord->sSpeechContent,			short );
		HT_LOADCELL( _T("iDuration"),				pRecord->iDuration,					int );
		HT_LOADCELL( _T("iCastingTime"),			pRecord->iCastingTime,				int );
		HT_LOADCELL( _T("iActivateTime"),			pRecord->iActivateTime,				int );
		HT_LOADCELL( _T("byteCastCount"),			pRecord->byteCastCount,				byte );
		HT_LOADCELL( _T("byteSuccessRate"),			pRecord->byteSuccessRate,			byte );
		HT_LOADCELL( _T("byteSyncFlag"),			pRecord->byteSyncFlag,				byte );
		HT_LOADCELL( _T("iCoolDownTime"),			pRecord->iCoolDownTime,				int	);
		HT_LOADCELL( _T("iRange"),					pRecord->iRange,					int	);
		HT_LOADCELL( _T("iAreaOfEffect"),			pRecord->iAreaOfEffect,				int	);
		HT_LOADCELL( _T("iAllowedTarget"),			pRecord->iAllowedTarget,			int	);
		HT_LOADCELL( _T("byteAttackType"),			pRecord->byteAttackType,			byte );
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
		HT_LOADCELL( _T("iReqTrimuriti"),			pRecord->iReqTrimuriti,				int );
		HT_LOADCELL( _T("iReqTribe"),				pRecord->iReqTribe,					int );
		HT_LOADCELL( _T("iReqWeaponType"),			pRecord->iReqWeaponType,			int );
		HT_LOADCELL( _T("idReqItem"),				pRecord->idReqItem,					int );
		HT_LOADCELL( _T("byteReqLevel"),			pRecord->byteReqLevel,				byte );
		HT_LOADCELL( _T("idReqSkill1"),				pRecord->idReqSkill1,				int );
		HT_LOADCELL( _T("byteReqSkill1_Lvl"),		pRecord->byteReqSkill1_Lvl,			byte );
		HT_LOADCELL( _T("idReqSkill2"),				pRecord->idReqSkill2,				int );
		HT_LOADCELL( _T("byteReqSkill2_Lvl"),		pRecord->byteReqSkill2_Lvl,			byte );
		HT_LOADCELL( _T("byteReserve0"), 			pRecord->byteReserve0,				byte );
		HT_LOADCELL( _T("byteReserve1"), 			pRecord->byteReserve1,				byte );
		HT_LOADCELL( _T("byteReserve2"), 			pRecord->byteReserve2,				byte );
		HT_LOADCELL( _T("byteReserve3"), 			pRecord->byteReserve3,				byte );
		HT_LOADCELL( _T("byteReserve4"), 			pRecord->byteReserve4,				byte );
		HT_LOADCELL( _T("byteReserve5"), 			pRecord->byteReserve5,				byte );
		HT_LOADCELL( _T("byteReserve6"), 			pRecord->byteReserve6,				byte );
		HT_LOADCELL( _T("byteReserve7"), 			pRecord->byteReserve7,				byte );

		if ( byteLevel >=0 && byteLevel < HT_PCSKILL_MAXLEVEL )
		{
			m_arrmapTable[byteLevel].insert( HTMonsterSkillParam_Value( iID, pRecord ) );
		}
		else
		{
			MessageBox( NULL, "∑π∫ß øµø™¿ª π˛æÓ≥≠ Ω∫≈≥ ∑π∫ß", "CHTMonsterSkillParamTable", MB_OK );
		}
	}

	return true;
}

bool
	CHTMonsterSkillParamTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iSkillLevel;
	int arriRecordCount[HT_PCSKILL_MAXLEVEL];

	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		pFile->HT_bRead( &arriRecordCount[iSkillLevel] );
		m_nItems += arriRecordCount[iSkillLevel];
	}

	HTMonsterSkillParam* pRecord = NULL;
	int iID;
	for ( iSkillLevel = 1; iSkillLevel < HT_PCSKILL_MAXLEVEL; ++iSkillLevel )
	{
		for ( int i = 0; i < arriRecordCount[iSkillLevel]; ++i )
		{
			pRecord = new HTMonsterSkillParam;

			pFile->HT_bRead( &iID );
			pFile->HT_bRead( pRecord, sizeof(HTMonsterSkillParam) );

			m_arrmapTable[iSkillLevel].insert( HTMonsterSkillParam_Value( iID, pRecord ) );
		}
	}

	return true;
}

bool
	CHTMonsterSkillParamTable::HT_bSave( CHTFile* pFile )
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
		HTMonsterSkillParam_It itTable = m_arrmapTable[iSkillLevel].begin();
		while ( itTable != m_arrmapTable[iSkillLevel].end() )
		{
			int iID = itTable->first;
			pFile->HT_bWrite( iID );
			pFile->HT_bWrite( itTable->second, sizeof(HTMonsterSkillParam) );

			itTable++;
		}
	}

	return true;
}

bool
	CHTMonsterSkillParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
{
	std::vector<HTIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTMonsterSkillParam_It itTable;

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

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*psSpeechContent = (itTable->second)->sSpeechContent;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteSyncFlag = (itTable->second)->byteSyncFlag;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte *pbyteReqLevel )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*piActivateTime = (itTable->second)->iActivateTime;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteCastCount = (itTable->second)->byteCastCount;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
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
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve0 = (itTable->second)->byteReserve0;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve1 = (itTable->second)->byteReserve1;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve2 = (itTable->second)->byteReserve2;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve3 = (itTable->second)->byteReserve3;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve4 = (itTable->second)->byteReserve4;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve5 = (itTable->second)->byteReserve5;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve6 = (itTable->second)->byteReserve6;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTMonsterSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve7 = (itTable->second)->byteReserve7;
			return true;
		}
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel )
{
	if ( m_pParam )
	{
		*pbyteMaxLevel = m_pParam->byteMaxLevel;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillType( byte* pbyteType )
{
	if ( m_pParam )
	{
		*pbyteType = m_pParam->byteType;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCombatPhase( short* psCombatPhase )
{
	if ( m_pParam )
	{
		*psCombatPhase = m_pParam->sCombatPhase;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSpeechContent( short* psSpeechContent )
{
	if ( m_pParam )
	{
		*psSpeechContent = m_pParam->sSpeechContent;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate )
{
	if ( m_pParam )
	{
		*pbyteSuccessRate = m_pParam->byteSuccessRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag )
{
	if ( m_pParam )
	{
		*pbyteSyncFlag = m_pParam->byteSyncFlag;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate )
{
	if ( m_pParam )
	{
		*pbyteCastingSuccessRate = m_pParam->byteCastingSuccessRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange )
{
	if ( m_pParam )
	{
		*pbyteFollowRange = m_pParam->byteFollowRange;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate )
{
	if ( m_pParam )
	{
		*pbytePierceRate = m_pParam->bytePierceRate;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillDuration( int* piDuration )
{
	if ( m_pParam )
	{
		*piDuration = m_pParam->iDuration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect )
{
	if ( m_pParam )
	{
		*piAreaOfEffect = m_pParam->iAreaOfEffect;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti )
{
	if ( m_pParam )
	{
		*piReqTrimuriti = m_pParam->iReqTrimuriti;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqTribe( int* piReqTribe )
{
	if ( m_pParam )
	{
		*piReqTribe = m_pParam->iReqTribe;
		return true;
	}
	return false;
}


bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType )
{
	if ( m_pParam )
	{
		*piReqWeaponType = m_pParam->iReqWeaponType;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillidReqItem( int* pidReqItem )
{
	if ( m_pParam )
	{
		*pidReqItem = m_pParam->idReqItem;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel )
{
	if ( m_pParam )
	{
		*pbyteReqLevel = m_pParam->byteReqLevel;
		return true;
	}
	return false;
}


bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 )
{
	if ( m_pParam )
	{
		*pidReqSkill1 = m_pParam->idReqSkill1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl )
{
	if ( m_pParam )
	{
		*pbyteReqSkill1_Lvl = m_pParam->byteReqSkill1_Lvl;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 )
{
	if ( m_pParam )
	{
		*pidReqSkill2 = m_pParam->idReqSkill2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl )
{
	if ( m_pParam )
	{
		*pbyteReqSkill2_Lvl = m_pParam->byteReqSkill2_Lvl;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParam )
	{
		*piAllowedTarget = m_pParam->iAllowedTarget;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillAttackType( byte* pbyteAttackType )
{
	if ( m_pParam )
	{
		*pbyteAttackType = m_pParam->byteAttackType;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastingTime( int* piCastingTime )
{
	if ( m_pParam )
	{
		*piCastingTime = m_pParam->iCastingTime;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillActivateTime( int* piActivateTime )
{
	if ( m_pParam )
	{
		*piActivateTime = m_pParam->iActivateTime;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCastCount( byte* pbyteCastCount )
{
	if ( m_pParam )
	{
		*pbyteCastCount = m_pParam->byteCastCount;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParam )
	{
		*piCoolDownTime = m_pParam->iCoolDownTime;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillRange( int* piRange )
{
	if ( m_pParam )
	{
		*piRange = m_pParam->iRange;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1ID( int* piEffect1ID )
{
	if ( m_pParam )
	{
		*piEffect1ID = m_pParam->iEffect1ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Function( int* piEffect1Function )
{
	if ( m_pParam )
	{
		*piEffect1Function = m_pParam->iEffect1Function;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParam )
	{
		*piEffect1Duration = m_pParam->iEffect1Duration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParam )
	{
		*piEffect1Param1 = m_pParam->iEffect1Param1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParam )
	{
		*piEffect1Param2 = m_pParam->iEffect1Param2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2ID( int* piEffect2ID )
{
	if ( m_pParam )
	{
		*piEffect2ID = m_pParam->iEffect2ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Function( int* piEffect2Function )
{
	if ( m_pParam )
	{
		*piEffect2Function = m_pParam->iEffect2Function;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParam )
	{
		*piEffect2Duration = m_pParam->iEffect2Duration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParam )
	{
		*piEffect2Param1 = m_pParam->iEffect2Param1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParam )
	{
		*piEffect2Param2 = m_pParam->iEffect2Param2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3ID( int* piEffect3ID )
{
	if ( m_pParam )
	{
		*piEffect3ID = m_pParam->iEffect3ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Function( int* piEffect3Function )
{
	if ( m_pParam )
	{
		*piEffect3Function = m_pParam->iEffect3Function;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParam )
	{
		*piEffect3Duration = m_pParam->iEffect3Duration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParam )
	{
		*piEffect3Param1 = m_pParam->iEffect3Param1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParam )
	{
		*piEffect3Param2 = m_pParam->iEffect3Param2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4ID( int* piEffect4ID )
{
	if ( m_pParam )
	{
		*piEffect4ID = m_pParam->iEffect4ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Function( int* piEffect4Function )
{
	if ( m_pParam )
	{
		*piEffect4Function = m_pParam->iEffect4Function;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParam )
	{
		*piEffect4Duration = m_pParam->iEffect4Duration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParam )
	{
		*piEffect4Param1 = m_pParam->iEffect4Param1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParam )
	{
		*piEffect4Param2 = m_pParam->iEffect4Param2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5ID( int* piEffect5ID )
{
	if ( m_pParam )
	{
		*piEffect5ID = m_pParam->iEffect5ID;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Function( int* piEffect5Function )
{
	if ( m_pParam )
	{
		*piEffect5Function = m_pParam->iEffect5Function;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParam )
	{
		*piEffect5Duration = m_pParam->iEffect5Duration;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParam )
	{
		*piEffect5Param1 = m_pParam->iEffect5Param1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParam )
	{
		*piEffect5Param2 = m_pParam->iEffect5Param2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCostTP( int* piCostTP )
{
	if ( m_pParam )
	{
		*piCostTP = m_pParam->iCostTP;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillCostHP( int* piCostHP )
{
	if ( m_pParam )
	{
		*piCostHP = m_pParam->iCostHP;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillidCostItem( int* pidCostItem )
{
	if ( m_pParam )
	{
		*pidCostItem = m_pParam->idCostItem;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 )
{
	if ( m_pParam )
	{
		*pbyteReserve0 = m_pParam->byteReserve0;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 )
{
	if ( m_pParam )
	{
		*pbyteReserve1 = m_pParam->byteReserve1;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 )
{
	if ( m_pParam )
	{
		*pbyteReserve2 = m_pParam->byteReserve2;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 )
{
	if ( m_pParam )
	{
		*pbyteReserve3 = m_pParam->byteReserve3;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 )
{
	if ( m_pParam )
	{
		*pbyteReserve4 = m_pParam->byteReserve4;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 )
{
	if ( m_pParam )
	{
		*pbyteReserve5 = m_pParam->byteReserve5;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 )
{
	if ( m_pParam )
	{
		*pbyteReserve6 = m_pParam->byteReserve6;
		return true;
	}
	return false;
}

bool
	CHTMonsterSkillParamTable::HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 )
{
	if ( m_pParam )
	{
		*pbyteReserve7 = m_pParam->byteReserve7;
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
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ.. -_-
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
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTPCSkillParam;

		HT_LOADCELL( _T("ID"),						iID,								int );
#ifdef HT_NEED_NAME
		strCell = "szName";
		//if( strLanguage == HT_LANGUAGE_CHINESE )
		//	strCell = _T("chi_szName");
		//else
		//	strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );
#endif
		HT_LOADCELL( _T("byteLevel"),				byteLevel,							byte );
		HT_LOADCELL( _T("byteMaxLevel"),			pRecord->byteMaxLevel,				byte );
		HT_LOADCELL( _T("byteType"),				pRecord->byteType,					byte );
		HT_LOADCELL( _T("sCombatPhase"),			pRecord->sCombatPhase,				short );
		HT_LOADCELL( _T("iDuration"),				pRecord->iDuration,					int );
		HT_LOADCELL( _T("byteSuccessRate"),			pRecord->byteSuccessRate,			byte );
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
		HT_LOADCELL( _T("byteReserve0"), 			pRecord->byteReserve0,				byte );
		HT_LOADCELL( _T("byteReserve1"), 			pRecord->byteReserve1,				byte );
		HT_LOADCELL( _T("byteReserve2"), 			pRecord->byteReserve2,				byte );
		HT_LOADCELL( _T("byteReserve3"), 			pRecord->byteReserve3,				byte );
		HT_LOADCELL( _T("byteReserve4"), 			pRecord->byteReserve4,				byte );
		HT_LOADCELL( _T("byteReserve5"), 			pRecord->byteReserve5,				byte );
		HT_LOADCELL( _T("byteReserve6"), 			pRecord->byteReserve6,				byte );
		HT_LOADCELL( _T("byteReserve7"), 			pRecord->byteReserve7,				byte );

		if ( byteLevel >=0 && byteLevel < HT_PCSKILL_MAXLEVEL )
		{
			m_arrmapTable[byteLevel].insert( HTPCSkillParam_Value( iID, pRecord ) );
		}
		else
		{
			MessageBox( NULL, "∑π∫ß øµø™¿ª π˛æÓ≥≠ Ω∫≈≥ ∑π∫ß", "CHTPCSkillParamTable", MB_OK );
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
	CHTPCSkillParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
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
	CHTPCSkillParamTable::HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve0 = (itTable->second)->byteReserve0;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve1 = (itTable->second)->byteReserve1;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve2 = (itTable->second)->byteReserve2;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve3 = (itTable->second)->byteReserve3;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve4 = (itTable->second)->byteReserve4;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve5 = (itTable->second)->byteReserve5;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve6 = (itTable->second)->byteReserve6;
			return true;
		}
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 )
{
	if ( byteLevel < 0 || byteLevel >= HT_PCSKILL_MAXLEVEL ) return false;

	HTPCSkillParam_It itTable = m_arrmapTable[byteLevel].find( id );
	if ( itTable != m_arrmapTable[byteLevel].end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve7 = (itTable->second)->byteReserve7;
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

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve0( byte* pbyteReserve0 )
{
	if ( m_pParam )
	{
		*pbyteReserve0 = m_pParam->byteReserve0;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve1( byte* pbyteReserve1 )
{
	if ( m_pParam )
	{
		*pbyteReserve1 = m_pParam->byteReserve1;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve2( byte* pbyteReserve2 )
{
	if ( m_pParam )
	{
		*pbyteReserve2 = m_pParam->byteReserve2;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve3( byte* pbyteReserve3 )
{
	if ( m_pParam )
	{
		*pbyteReserve3 = m_pParam->byteReserve3;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve4( byte* pbyteReserve4 )
{
	if ( m_pParam )
	{
		*pbyteReserve4 = m_pParam->byteReserve4;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve5( byte* pbyteReserve5 )
{
	if ( m_pParam )
	{
		*pbyteReserve5 = m_pParam->byteReserve5;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve6( byte* pbyteReserve6 )
{
	if ( m_pParam )
	{
		*pbyteReserve6 = m_pParam->byteReserve6;
		return true;
	}
	return false;
}

bool
	CHTPCSkillParamTable::HT_bGetPCSkillReserve7( byte* pbyteReserve7 )
{
	if ( m_pParam )
	{
		*pbyteReserve7 = m_pParam->byteReserve7;
		return true;
	}
	return false;
}

// ---------------
CHTItemParamTable::CHTItemParamTable() : m_pParam(NULL)
	/*m_pParamItemWeapon(0), m_pParamItemDefence(0), m_pParamItemAccessory(0), 
	m_pParamItemRefine(0), m_pParamItemUsable(0), m_pParamItemCollect(0), m_pParamItemQuestOnly(0)*/
{
	for ( int i = 0; i < HT_ITEMLEVEL_MAX; ++i )
	{
		m_arrvecItemID[i].clear();
	}
}

CHTItemParamTable::~CHTItemParamTable()
{
	HTItemParam_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}

	// Level ∫∞∑Œ ¿˙¿Â«ÿ ≥ı¥¬∞≈ ¡ˆøÓ¥Ÿ.
	for ( int i = 0; i < HT_ITEMLEVEL_MAX; ++i )
	{
		m_arrvecItemID[i].clear();
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
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ. -_-
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

		// Level ∫∞∑Œ ¿˙¿Â«ÿ ≥ı¥¬¥Ÿ.
		m_arrvecItemID[pRecord->byteLevel].push_back( HTItemID_Value( iID ) );
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
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemParam;

		HT_LOADCELL( _T("ID"),						iID,							int );
#ifdef HT_NEED_NAME
		//strCell = _T("szName");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szName");
		else if( strLanguage == HT_LANGUAGE_PHILIPPINE )
			strCell = _T("philippine_szName");
		else if( strLanguage == HT_LANGUAGE_INDONESIA )
			strCell = _T("indonesia_szName");
		else if( strLanguage == HT_LANGUAGE_JAPANESE )
			strCell = _T("jp_szName");
		else
			strCell = _T("kor_szName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, pRecord->szName );
#endif
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
		HT_LOADCELL( _T("iAllowedTarget"),			pRecord->iAllowedTarget,		int );
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
		HT_LOADCELL( _T("sEventID"), 				pRecord->sEventID,				short );
		HT_LOADCELL( _T("iCash"), 					pRecord->iCash,					int );
		HT_LOADCELL( _T("byteReserve1"), 			pRecord->byteReserve1,			byte );
		HT_LOADCELL( _T("byteReserve2"), 			pRecord->byteReserve2,			byte );
		HT_LOADCELL( _T("byteReserve3"), 			pRecord->byteReserve3,			byte );
		HT_LOADCELL( _T("byteReserve4"), 			pRecord->byteReserve4,			byte );
		HT_LOADCELL( _T("byteReserve5"), 			pRecord->byteReserve5,			byte );
		HT_LOADCELL( _T("byteReserve6"), 			pRecord->byteReserve6,			byte );
		HT_LOADCELL( _T("sTimeLimit"), 				pRecord->sTimeLimit,			short );
		HT_LOADCELL( _T("iEffectID"),				pRecord->idFX,					int );

		m_mapTable.insert( HTItemParam_Value( iID, pRecord ) );

		// Level ∫∞∑Œ ¿˙¿Â«ÿ ≥ı¥¬¥Ÿ.
		m_arrvecItemID[pRecord->byteLevel].push_back( HTItemID_Value( iID ) );
	}

	return true;
}

bool
	CHTItemParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
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

#ifdef HT_NEED_NAME
bool
	CHTItemParamTable::HT_bGetName( const int id, CHTString* pstrName )
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
	CHTItemParamTable::HT_bGetName( CHTString* pstrName )
{
	if( m_pParam )
	{
		*pstrName = m_pParam->szName;
		return true;
	}
	return false;
}
#endif

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
	CHTItemParamTable::HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
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
	CHTItemParamTable::HT_bGetItemEventID( const int id, short* psEventID )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psEventID = (itTable->second)->sEventID;
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
	CHTItemParamTable::HT_bGetItemReserve1( const int id, byte* pbyteReserve1 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve1 = (itTable->second)->byteReserve1;
			return true;
		}
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve2( const int id, byte* pbyteReserve2 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve2 = (itTable->second)->byteReserve2;
			return true;
		}
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve3( const int id, byte* pbyteReserve3 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve3 = (itTable->second)->byteReserve3;
			return true;
		}
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve4( const int id, byte* pbyteReserve4 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve4 = (itTable->second)->byteReserve4;
			return true;
		}
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve5( const int id, byte* pbyteReserve5 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve5 = (itTable->second)->byteReserve5;
			return true;
		}
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve6( const int id, byte* pbyteReserve6 )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pbyteReserve6 = (itTable->second)->byteReserve6;
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

bool
	CHTItemParamTable::HT_bGetItemFXEffectID( const int id, int* pidFX )
{
	HTItemParam_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pidFX = (itTable->second)->idFX;
			return true;
		}
	}
	return false;
}

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
	CHTItemParamTable::HT_bGetItemAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParam )
	{
		*piAllowedTarget = m_pParam->iAllowedTarget;
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
	CHTItemParamTable::HT_bGetItemEventID( short* psEventID )
{
	if ( m_pParam )
	{
		*psEventID = m_pParam->sEventID;
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
	CHTItemParamTable::HT_bGetItemReserve1( byte* pbyteReserve1 )
{
	if ( m_pParam )
	{
		*pbyteReserve1 = m_pParam->byteReserve1;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve2( byte* pbyteReserve2 )
{
	if ( m_pParam )
	{
		*pbyteReserve2 = m_pParam->byteReserve2;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve3( byte* pbyteReserve3 )
{
	if ( m_pParam )
	{
		*pbyteReserve3 = m_pParam->byteReserve3;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve4( byte* pbyteReserve4 )
{
	if ( m_pParam )
	{
		*pbyteReserve4 = m_pParam->byteReserve4;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve5( byte* pbyteReserve5 )
{
	if ( m_pParam )
	{
		*pbyteReserve5 = m_pParam->byteReserve5;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemReserve6( byte* pbyteReserve6 )
{
	if ( m_pParam )
	{
		*pbyteReserve6 = m_pParam->byteReserve6;
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

bool
	CHTItemParamTable::HT_bGetItemFXEffectID( int* pidFX )
{
	if ( m_pParam )
	{
		*pidFX = m_pParam->idFX;
		return true;
	}
	return false;
}

bool
	CHTItemParamTable::HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem )
{
	if ( byteLevel > 0 && byteLevel < HT_ITEMLEVEL_MAX )
	{
		if ( m_arrvecItemID[byteLevel].empty() )
		{
			*pidItem = -1;
			return false;
		}
		else
		{
			int iLevelMax = (int)m_arrvecItemID[byteLevel].size();
			int iRand = rand() % iLevelMax;
			*pidItem = m_arrvecItemID[byteLevel][iRand];
			return true;
		}
	}
	else
	{
		*pidItem = -1;
		return false;
	}
}


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
	CHTNPCParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
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
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ.. -_-
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
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTNPCParam;

		HT_LOADCELL( _T("ID"),			iID,					int );
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
	CHTPortalParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
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
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTPortalParam;

		HT_LOADCELL( _T("ID"),					iID,					int );
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

bool
	CHTPortalParamTable::HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel )
{
	HTPortalParam_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second && idMap == (itTable->second)->dwServerID )
		{
			*pdwLevel = (itTable->second)->dwZoneLevel;
			return true;
		}
		else itTable++;
	}

	*pdwLevel = 0;
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
	CHTTaskQuestParamTable::HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel )
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
			if ( m_pParam == itTable->second ) // ∆˜¿Œ≈Õ≥¢∏Æ ∫Ò±≥∏¶ «œ¥Ÿ¥œ.. -_-
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
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ.

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

CHTParameterMgr::CHTParameterMgr():m_pParamTable(0)
{
	for( int i = 0 ; i < HT_PARAMTYPE_END ; ++i )
		m_arrParamTable[i] = 0;
}

CHTParameterMgr::~CHTParameterMgr()
{
	for( int i = 0 ; i < HT_PARAMTYPE_END ; ++i )
		delete m_arrParamTable[i];

	m_vectorItemIDLevel.clear();
	m_vectorPCSkillIDLevelNagKin.clear();
	m_vectorPCSkillIDLevelAsuRak.clear();
	m_vectorPCSkillIDLevelDevGar.clear();
	m_vectorPCSkillIDLevelYakGan.clear();
	m_vectorPCSkillIDLevelEtc.clear();
	m_vectorNPCIDLevel.clear();
}

bool
	CHTParameterMgr::HT_bLockID( const int id, const byte iLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable )
	{
		m_pParamTable = pParamTable;
		return m_pParamTable->HT_bLockID( id, iLevel );
	}
	else return false;
}

bool
	CHTParameterMgr::HT_bUnLockID( const int id, const byte iLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( m_pParamTable == pParamTable ) // ∆˜¿Œ≈Õ ≥¢∏Æ ∂« ∫Ò±≥∏¶.. -_-
	{
		m_pParamTable->HT_bUnLockID( id, iLevel );
		m_pParamTable = NULL;
	}
	return false;
}

bool
	CHTParameterMgr::HT_bLoadXML( CHTString& strFile )
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
	m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL] = new CHTMonsterSkillParamTable;
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

	return bReturn;
}

bool
	CHTParameterMgr::HT_bLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return false;

	m_arrParamTable[HT_PARAMTYPE_MONSTER]		= new CHTMonsterParamTable;
	m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]	= new CHTMonsterSkillParamTable;
	m_arrParamTable[HT_PARAMTYPE_PCSKILL]		= new CHTPCSkillParamTable;
	m_arrParamTable[HT_PARAMTYPE_ITEM]			= new CHTItemParamTable;
	m_arrParamTable[HT_PARAMTYPE_NPC]			= new CHTNPCParamTable;
	m_arrParamTable[HT_PARAMTYPE_PORTAL]		= new CHTPortalParamTable;
	m_arrParamTable[HT_PARAMTYPE_TASKQUEST]		= new CHTTaskQuestParamTable;

	bool bReturn = true;

	CHTString strTable;
	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTERSKILL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PCSKILL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_NPC]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_PORTAL]->HT_bLoad( &oLoadFile );
	bReturn &= m_arrParamTable[HT_PARAMTYPE_TASKQUEST]->HT_bLoad( &oLoadFile );

	oLoadFile.HT_vClose();

	// Filll All ID for Fast 
	this->HT_bGetAllID( HT_PARAMTYPE_ITEM, &m_vectorItemIDLevel );
	this->HT_bGetAllID( HT_PARAMTYPE_NPC, &m_vectorNPCIDLevel );

	std::vector<HTIDLevel> vectorPCSkillIDLevel;
	this->HT_bGetAllID( HT_PARAMTYPE_PCSKILL, &vectorPCSkillIDLevel );

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
	CHTParameterMgr::HT_bSave( CHTString& strFile )
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

	oSaveFile.HT_vClose();

	return bReturn;
}

bool
	CHTParameterMgr::HT_bTestSave( CHTString& strFile )
{
	FILE* pFile;
	if ( pFile = fopen( (HTtchar*)strFile, "wt" ) )
	{

		int index;
		int id;
		byte byteLevel;
		CHTString str;

		std::vector<HTIDLevel> vectorIDLevel;
		vector<HTIDLevel>::iterator vec_It;

		for( int i = 1 ; i < HT_PARAMTYPE_END ; ++i )
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
				fprintf( pFile, "\nPCSkill" );
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
			default:
				fprintf( pFile, "\n");
				break;
			}
			fprintf( pFile, "\n---------------------------------------");

			if( m_arrParamTable[i] != 0 && m_arrParamTable[i]->HT_bGetAllID( &vectorIDLevel ) ) // ∏µÁ æ∆¿Ãµ∏¶ ±∏«‘
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
					HT_vTestMonsterSkillParamWithID( pFile, id, byteLevel );
					HT_vTestPCSkillParamWithID( pFile, id, byteLevel );
					HT_vTestItemParamWithID( pFile, id );
					HT_vTestNPCParamWithID( pFile, id );
					HT_vTestPortalParam( pFile, id );
					HT_vTestTaskQuestParamWithID( pFile, id );

					// Without ID
					if ( this->HT_bLockID( id, byteLevel ) )
					{
						if( i == HT_PARAMTYPE_PCSKILL || i == HT_PARAMTYPE_MONSTERSKILL )
							fprintf( pFile, "\n		Lock Successfully : ID(%d) Lvl(%d)", id, byteLevel );
						else
							fprintf( pFile, "\n		Lock Successfully : ID(%d)", id );

#ifdef HT_NEED_NAME
						if( this->HT_bGetName( &str ) ) fprintf( pFile, "\nHT_bGetName : %s", str.HT_szGetString() );
#endif
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
			}	// end of if(m_arrParamTable[i]->HT_bGetAllID( pvecIDLevel ))

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

bool
	CHTParameterMgr::HT_bGetAllID( int iType, std::vector<HTIDLevel>* pvectorIDLevel )
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

void
	CHTParameterMgr::HT_vTestMonsterParamWithID( FILE* pFile, const int id )
{
	int iOut;
	short sOut;
	unsigned int uiOut;
	byte byteOut;

	if ( this->HT_bGetMonsterLevel( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLevel : %d", byteOut );
	if ( this->HT_bGetMonsterClass( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterClass : %d", byteOut );
	if ( this->HT_bGetMonsterSize( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSize : %d", byteOut );
	if ( this->HT_bGetMonsterAI( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAI : %d", iOut );
	if ( this->HT_bGetMonsterSelectTargetTime( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTargetTime : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget0( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget0 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget1( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget1 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget2( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget2 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget3( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget3 : %d", byteOut );
	if ( this->HT_bGetMonsterAggrCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterAggrCond : %d", byteOut );
	if ( this->HT_bGetMonsterFleeCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFleeCond : %d", byteOut );
	if ( this->HT_bGetMonsterFleeCondCount( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFleeCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterTraceCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterTraceCond : %d", byteOut );
	if ( this->HT_bGetMonsterStepBackCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterStepBackCond : %d", byteOut );
	if ( this->HT_bGetMonsterHelpCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHelpCond : %d", byteOut );
	if ( this->HT_bGetMonsterHelpCondCount( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHelpCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterLinkCond( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLinkCond : %d", byteOut );
	if ( this->HT_bGetMonsterLinkCondCount( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLinkCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterBlockedCell( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterBlockedCell: %d", iOut );
	if ( this->HT_bGetMonsterCantDetect( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterCantDetect: %d", iOut );
	if ( this->HT_bGetMonsterTrimuriti( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterTrimuriti : %d", byteOut );
	if ( this->HT_bGetMonsterNormalSight( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterNormalSight : %d", byteOut );
	if ( this->HT_bGetMonsterCombatSight( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterCombatSight : %d", byteOut );
	if ( this->HT_bGetMonsterPopDelayMin( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterPopDelayMin: %d", uiOut );
	if ( this->HT_bGetMonsterPopDelayMax( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterPopDelayMax : %d", uiOut );
	if ( this->HT_bGetMonsterMovement( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterMovement : %d", byteOut );
	if ( this->HT_bGetMonsterSpeechRate( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSpeechRate : %d", byteOut );
	if ( this->HT_bGetMonsterSpeechAI( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSpeechAI : %d", byteOut );
	if ( this->HT_bGetMonsterEventNo( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterEventNo : %d", uiOut );
	if ( this->HT_bGetMonsterMuscle( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterMuscle : %d", sOut );
	if ( this->HT_bGetMonsterNerves( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterNerves : %d", sOut );
	if ( this->HT_bGetMonsterHeart( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterHeart : %d", sOut );
	if ( this->HT_bGetMonsterMind( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterMind : %d", sOut );
	if ( this->HT_bGetMonsterArmorType( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterArmorType : %d", byteOut );
	if ( this->HT_bGetMonsterHP( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterHP : %d", uiOut );
	if ( this->HT_bGetMonsterHPRecovery( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHPRecovery : %d", byteOut );
	if ( this->HT_bGetMonsterAttackRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAttackRate: %d", iOut );
	if ( this->HT_bGetMonsterDodgeRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterDodgeRate: %d", iOut );
	if ( this->HT_bGetMonsterAC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAC : %d", iOut );
	if ( this->HT_bGetMonsterFireResist( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterFireResist : %d", iOut );
	if ( this->HT_bGetMonsterColdResist( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterColdResist : %d", iOut );
	if ( this->HT_bGetMonsterLightningResist( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterLightningResist : %d", iOut );
	if ( this->HT_bGetMonsterPoisonResist( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterPoisonResist : %d", iOut );
	if ( this->HT_bGetMonsterWalkSpeed( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterWalkSpeed : %d", iOut );
	if ( this->HT_bGetMonsterRunSpeed( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterRunSpeed : %d", iOut );
	if ( this->HT_bGetMonsterFly( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFly : %d", byteOut );
	if ( this->HT_bGetMonsterSkill0( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill0 : %d", iOut );
	if ( this->HT_bGetMonsterSkill1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill1 : %d", iOut );
	if ( this->HT_bGetMonsterSkill2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill2 : %d", iOut );
	if ( this->HT_bGetMonsterSkill3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill3 : %d", iOut );
	if ( this->HT_bGetMonsterSkill4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill4 : %d", iOut );
	if ( this->HT_bGetMonsterSkill5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill5 : %d", iOut );
	if ( this->HT_bGetMonsterSkill6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill6 : %d", iOut );
	if ( this->HT_bGetMonsterSkill7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill7 : %d", iOut );
	if ( this->HT_bGetMonsterSkillPattern0( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern0 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern1( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern1 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern2( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern2 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern3( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern3 : %d", byteOut );
	if ( this->HT_bGetMonsterImmunity( id, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterImmunity : %d", iOut );
	if ( this->HT_bGetMonsterResistEffectConst( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterResistEffectConst : %d", byteOut );
	if ( this->HT_bGetMonsterRewardBrahmanPoint( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardBrahmanPoint : %d", uiOut );
	if ( this->HT_bGetMonsterRewardGold( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardGold : %d", uiOut );
	if ( this->HT_bGetMonsterRewardPrana( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardPrana : %d", uiOut );
	if ( this->HT_bGetMonsterItem0ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem0ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem0DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem0DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem1ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem1ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem1DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem1DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem2ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem2ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem2DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem2DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem3ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem3ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem3DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem3DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem4ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem4ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem4DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem4DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem5ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem5ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem5DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem5DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem6ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem6ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem6DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem6DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem7ItemID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem7ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem7DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem7DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem8Grade( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8Grade : %d", byteOut );
	if ( this->HT_bGetMonsterItem8DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8DropRate : %d", sOut );
	//if ( this->HT_bGetMonsterItem8DeadCount( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8DeadCount : %d", uiOut );
	if ( this->HT_bGetMonsterItem9Grade( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9Grade : %d", byteOut );
	if ( this->HT_bGetMonsterItem9DropRate( id, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9DropRate : %d", sOut );
	//if ( this->HT_bGetMonsterItem9DeadCount( id, &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9DeadCount : %d", uiOut );
	if ( this->HT_bGetMonsterReserve0( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve0 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve1( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve1 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve2( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve2 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve3( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve3 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve4( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve4 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve5( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve5 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve6( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve6 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve7( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestMonsterParam( FILE* pFile )
{
	int iOut;
	short sOut;
	unsigned int uiOut;
	byte byteOut;

	if ( this->HT_bGetMonsterLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLevel : %d", byteOut );
	if ( this->HT_bGetMonsterClass( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterClass : %d", byteOut );
	if ( this->HT_bGetMonsterSize( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSize : %d", byteOut );
	if ( this->HT_bGetMonsterAI( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAI : %d", iOut );
	if ( this->HT_bGetMonsterSelectTargetTime( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTargetTime : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget0( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget0 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget1( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget1 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget2( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget2 : %d", byteOut );
	if ( this->HT_bGetMonsterSelectTarget3( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSelectTarget3 : %d", byteOut );
	if ( this->HT_bGetMonsterAggrCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterAggrCond : %d", byteOut );
	if ( this->HT_bGetMonsterFleeCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFleeCond : %d", byteOut );
	if ( this->HT_bGetMonsterFleeCondCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFleeCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterTraceCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterTraceCond : %d", byteOut );
	if ( this->HT_bGetMonsterStepBackCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterStepBackCond : %d", byteOut );
	if ( this->HT_bGetMonsterHelpCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHelpCond : %d", byteOut );
	if ( this->HT_bGetMonsterHelpCondCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHelpCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterLinkCond( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLinkCond : %d", byteOut );
	if ( this->HT_bGetMonsterLinkCondCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterLinkCondCount : %d", byteOut );
	if ( this->HT_bGetMonsterBlockedCell( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterBlockedCell: %d", iOut );
	if ( this->HT_bGetMonsterCantDetect( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterCantDetect: %d", iOut );
	if ( this->HT_bGetMonsterTrimuriti( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterTrimuriti : %d", byteOut );
	if ( this->HT_bGetMonsterNormalSight( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterNormalSight : %d", byteOut );
	if ( this->HT_bGetMonsterCombatSight( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterCombatSight : %d", byteOut );
	if ( this->HT_bGetMonsterPopDelayMin( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterPopDelayMin : %d", uiOut );
	if ( this->HT_bGetMonsterPopDelayMax( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterPopDelayMax : %d", uiOut );
	if ( this->HT_bGetMonsterMovement( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterMovement : %d", byteOut );
	if ( this->HT_bGetMonsterSpeechRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSpeechRate : %d", byteOut );
	if ( this->HT_bGetMonsterSpeechAI( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSpeechAI : %d", byteOut );
	if ( this->HT_bGetMonsterEventNo( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterEventNo : %d", uiOut );
	if ( this->HT_bGetMonsterMuscle( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterMuscle : %d", sOut );
	if ( this->HT_bGetMonsterNerves( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterNerves : %d", sOut );
	if ( this->HT_bGetMonsterHeart( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterHeart : %d", sOut );
	if ( this->HT_bGetMonsterMind( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterMind : %d", sOut );
	if ( this->HT_bGetMonsterArmorType( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterArmorType : %d", byteOut );
	if ( this->HT_bGetMonsterHP( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterHP : %d", uiOut );
	if ( this->HT_bGetMonsterHPRecovery( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterHPRecovery : %d", byteOut );
	if ( this->HT_bGetMonsterAttackRate( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAttackRate : %d", iOut );
	if ( this->HT_bGetMonsterDodgeRate( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterDodgeRate : %d", iOut );
	if ( this->HT_bGetMonsterAC( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterAC : %d", iOut );
	if ( this->HT_bGetMonsterFireResist( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterFireResist : %d", iOut );
	if ( this->HT_bGetMonsterColdResist( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterColdResist : %d", iOut );
	if ( this->HT_bGetMonsterLightningResist( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterLightningResist : %d", iOut );
	if ( this->HT_bGetMonsterPoisonResist( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterPoisonResist : %d", iOut );
	if ( this->HT_bGetMonsterWalkSpeed( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterWalkSpeed : %d", iOut );
	if ( this->HT_bGetMonsterRunSpeed( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterRunSpeed : %d", iOut );
	if ( this->HT_bGetMonsterFly( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterFly : %d", byteOut );
	if ( this->HT_bGetMonsterSkill0( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill0 : %d", iOut );
	if ( this->HT_bGetMonsterSkill1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill1 : %d", iOut );
	if ( this->HT_bGetMonsterSkill2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill2 : %d", iOut );
	if ( this->HT_bGetMonsterSkill3( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill3 : %d", iOut );
	if ( this->HT_bGetMonsterSkill4( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill4 : %d", iOut );
	if ( this->HT_bGetMonsterSkill5( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill5 : %d", iOut );
	if ( this->HT_bGetMonsterSkill6( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill6 : %d", iOut );
	if ( this->HT_bGetMonsterSkill7( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkill7 : %d", iOut );
	if ( this->HT_bGetMonsterSkillPattern0( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern0 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern1( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern1 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern2( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern2 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPattern3( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPattern3 : %d", byteOut );
	if ( this->HT_bGetMonsterImmunity( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterImmunity : %d", iOut );
	if ( this->HT_bGetMonsterResistEffectConst( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterResistEffectConst : %d", byteOut );
	if ( this->HT_bGetMonsterRewardBrahmanPoint( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardBrahmanPoint : %d", uiOut );
	if ( this->HT_bGetMonsterRewardGold( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardGold : %d", uiOut );
	if ( this->HT_bGetMonsterRewardPrana( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterRewardPrana : %d", uiOut );
	if ( this->HT_bGetMonsterItem0ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem0ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem0DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem0DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem1ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem1ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem1DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem1DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem2ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem2ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem2DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem2DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem3ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem3ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem3DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem3DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem4ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem4ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem4DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem4DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem5ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem5ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem5DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem5DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem6ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem6ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem6DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem6DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem7ItemID( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem7ItemID : %d", sOut );
	if ( this->HT_bGetMonsterItem7DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem7DropRate : %d", sOut );
	if ( this->HT_bGetMonsterItem8Grade( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8Grade : %d", byteOut );
	if ( this->HT_bGetMonsterItem8DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8DropRate : %d", sOut );
	//if ( this->HT_bGetMonsterItem8DeadCount( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem8DeadCount : %d", uiOut );
	if ( this->HT_bGetMonsterItem9Grade( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9Grade : %d", byteOut );
	if ( this->HT_bGetMonsterItem9DropRate( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9DropRate : %d", sOut );
	//if ( this->HT_bGetMonsterItem9DeadCount( &uiOut ) ) fprintf( pFile, "\nHT_bGetMonsterItem9DeadCount : %d", uiOut );
	if ( this->HT_bGetMonsterReserve0( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve0 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve1( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve1 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve2( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve2 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve3( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve3 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve4( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve4 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve5( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve5 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve6( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve6 : %d", byteOut );
	if ( this->HT_bGetMonsterReserve7( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestMonsterSkillParamWithID( FILE* pFile, const int id, const byte byteLevel )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetMonsterSkillMaxLevel( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetMonsterSkillType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillType : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCombatPhase( id, byteLevel, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetMonsterSkillSpeechContent( id, byteLevel, &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSpeechContent : %d", sOut );
	if ( this->HT_bGetMonsterSkillDuration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillDuration : %d", iOut );
	if ( this->HT_bGetMonsterSkillSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSuccessRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillSyncFlag( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSyncFlag : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCastingSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingSuccessRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillFollowRange( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillFollowRange : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPierceRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPierceRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCoolDownTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCoolDownTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillRange( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillRange : %d", iOut );
	if ( this->HT_bGetMonsterSkillAreaOfEffect( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAreaOfEffect : %d", iOut );
	if ( this->HT_bGetMonsterSkillAllowedTarget( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAllowedTarget : %d", iOut );
	if ( this->HT_bGetMonsterSkillAttackType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAttackType : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCastingTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillActivateTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillActivateTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillCastCount( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastCount : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqTrimuriti( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqTrimuriti : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqTribe( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqTribe : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqWeaponType( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqWeaponType : %d", iOut );
	if ( this->HT_bGetMonsterSkillidReqItem( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonstgerSkillidReqItem : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqLevel( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqLevel : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqSkill1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqSkill1_Lvl( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill1_Lvl : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqSkill2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqSkill2_Lvl( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill2_Lvl : %d", byteOut );
	if ( this->HT_bGetMonsterSkillEffect1ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5ID( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Function( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Duration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Param1( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Param2( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillCostTP( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCostMP : %d", iOut );
	if ( this->HT_bGetMonsterSkillCostHP( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCostHP : %d", iOut );
	if ( this->HT_bGetMonsterSkillidCostItem( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillidCostItem : %d", iOut );
	if ( this->HT_bGetMonsterSkillReserve0( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve0 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve1( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve1 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve2( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve2 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve3( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve3 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve4( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve4 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve5( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve5 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve6( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve6 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve7( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestMonsterSkillParam( FILE* pFile )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetMonsterSkillMaxLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetMonsterSkillType( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillType : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCombatPhase( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetMonsterSkillSpeechContent( &sOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSpeechContent : %d", sOut );
	if ( this->HT_bGetMonsterSkillDuration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillDuration : %d", iOut );
	if ( this->HT_bGetMonsterSkillSuccessRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSuccessRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillSyncFlag( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillSyncFlag : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCastingSuccessRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingSuccessRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillFollowRange( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillFollowRange : %d", byteOut );
	if ( this->HT_bGetMonsterSkillPierceRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillPierceRate : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCoolDownTime( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCoolDownTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillRange( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillRange : %d", iOut );
	if ( this->HT_bGetMonsterSkillAreaOfEffect( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAreaOfEffect : %d", iOut );
	if ( this->HT_bGetMonsterSkillAllowedTarget( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAllowedTarget : %d", iOut );
	if ( this->HT_bGetMonsterSkillAttackType( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillAttackType : %d", byteOut );
	if ( this->HT_bGetMonsterSkillCastingTime( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastingTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillActivateTime(&iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillActivateTime : %d", iOut );
	if ( this->HT_bGetMonsterSkillCastCount( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCastCount : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqTrimuriti( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqTrimuriti : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqTribe( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqTribe : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqWeaponType( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqWeaponType : %d", iOut );
	if ( this->HT_bGetMonsterSkillidReqItem( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillidReqItem : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqLevel : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqSkill1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqSkill1_Lvl( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill1_Lvl : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReqSkill2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillReqSkill2_Lvl( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReqSkill2_Lvl : %d", byteOut );
	if ( this->HT_bGetMonsterSkillEffect1ID( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Function( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect1Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect1Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2ID( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Function( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect2Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect2Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3ID( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Function( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect3Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect3Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4ID( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Function( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect4Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect4Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5ID( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5ID : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Function( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Function : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Duration( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Duration : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Param1( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Param1 : %d", iOut );
	if ( this->HT_bGetMonsterSkillEffect5Param2( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillEffect5Param2 : %d", iOut );
	if ( this->HT_bGetMonsterSkillCostTP( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCostTP : %d", iOut );
	if ( this->HT_bGetMonsterSkillCostHP( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillCostHP : %d", iOut );
	if ( this->HT_bGetMonsterSkillidCostItem( &iOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillidCostItem : %d", iOut );
	if ( this->HT_bGetMonsterSkillReserve0( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve0 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve1( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve1 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve2( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve2 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve3( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve3 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve4( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve4 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve5( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve5 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve6( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve6 : %d", byteOut );
	if ( this->HT_bGetMonsterSkillReserve7( &byteOut ) ) fprintf( pFile, "\nHT_bGetMonsterSkillReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestPCSkillParamWithID( FILE* pFile, const int id, const byte byteLevel )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetPCSkillMaxLevel( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillType : %d", byteOut );
	if ( this->HT_bGetPCSkillCombatPhase( id, byteLevel, &sOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetPCSkillDuration( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillDuration : %d", iOut );
	if ( this->HT_bGetPCSkillSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCastingSuccessRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCastingSuccessRate : %d", byteOut );
	if ( this->HT_bGetPCSkillFollowRange( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillFollowRange : %d", byteOut );
	if ( this->HT_bGetPCSkillPierceRate( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillPierceRate : %d", byteOut );
	if ( this->HT_bGetPCSkillCoolDownTime( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCoolDownTime : %d", iOut );
	if ( this->HT_bGetPCSkillRange( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillRange : %d", iOut );
	if ( this->HT_bGetPCSkillAreaOfEffect( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAreaOfEffect : %d", iOut );
	if ( this->HT_bGetPCSkillAllowedTarget( id, byteLevel, &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAllowedTarget : %d", iOut );
	if ( this->HT_bGetPCSkillAttackType( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillAttackType : %d", byteOut );
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
	if ( this->HT_bGetPCSkillReserve0( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve0 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve1( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve1 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve2( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve2 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve3( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve3 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve4( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve4 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve5( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve5 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve6( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve6 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve7( id, byteLevel, &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestPCSkillParam( FILE* pFile )
{
	int iOut;
	byte byteOut;
	short sOut;

	if ( this->HT_bGetPCSkillMaxLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillMaxLevel : %d", byteOut );
	if ( this->HT_bGetPCSkillType( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillType : %d", byteOut );
	if ( this->HT_bGetPCSkillCombatPhase( &sOut ) ) fprintf( pFile, "\nHT_bGetPCSkillCombatPhase : %d", sOut );
	if ( this->HT_bGetPCSkillDuration( &iOut ) ) fprintf( pFile, "\nHT_bGetPCSkillDuration : %d", iOut );
	if ( this->HT_bGetPCSkillSuccessRate( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillSuccessRate : %d", byteOut );
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
	if ( this->HT_bGetPCSkillReserve0( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve0 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve1( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve1 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve2( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve2 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve3( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve3 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve4( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve4 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve5( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve5 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve6( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve6 : %d", byteOut );
	if ( this->HT_bGetPCSkillReserve7( &byteOut ) ) fprintf( pFile, "\nHT_bGetPCSkillReserve7 : %d", byteOut );
}

void
	CHTParameterMgr::HT_vTestItemParamWithID(  FILE* pFile, const int id )
{
	int iOut;
	short sOut;
	byte byteOut;

	if ( this->HT_bGetItemLevel( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLevel : %d", byteOut );
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
	if ( this->HT_bGetItemAllowedTarget( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemAllowedTarget : %d", iOut );
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
	if ( this->HT_bGetItemEventID( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemEventID : %d", sOut );
	if ( this->HT_bGetItemCash( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemCash : %d", iOut );
	if ( this->HT_bGetItemReserve1( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve1 : %d", byteOut );
	if ( this->HT_bGetItemReserve2( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve2 : %d", byteOut );
	if ( this->HT_bGetItemReserve3( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve3 : %d", byteOut );
	if ( this->HT_bGetItemReserve4( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve4 : %d", byteOut );
	if ( this->HT_bGetItemReserve5( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve5 : %d", byteOut );
	if ( this->HT_bGetItemReserve6( id, &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve6 : %d", byteOut );
	if ( this->HT_bGetItemTimeLimit( id, &sOut ) ) fprintf( pFile, "\nHT_bGetItemTimeLimit : %d", sOut );
	if ( this->HT_bGetItemFXEffectID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemFXEffectID : %d", iOut );
}

void
	CHTParameterMgr::HT_vTestItemParam( FILE* pFile )
{
	short sOut;
	byte byteOut;
	int iOut;

	if ( this->HT_bGetItemLevel( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemLevel : %d", byteOut );
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
	if ( this->HT_bGetItemAllowedTarget( &iOut ) ) fprintf( pFile, "\nHT_bGetItemAllowedTarget : %d", iOut );
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
	if ( this->HT_bGetItemEventID( &sOut ) ) fprintf( pFile, "\nHT_bGetItemEventID : %d", sOut );
	if ( this->HT_bGetItemCash( &iOut ) ) fprintf( pFile, "\nHT_bGetItemCash : %d", iOut );
	if ( this->HT_bGetItemReserve1( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve1 : %d", byteOut );
	if ( this->HT_bGetItemReserve2( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve2 : %d", byteOut );
	if ( this->HT_bGetItemReserve3( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve3 : %d", byteOut );
	if ( this->HT_bGetItemReserve4( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve4 : %d", byteOut );
	if ( this->HT_bGetItemReserve5( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve5 : %d", byteOut );
	if ( this->HT_bGetItemReserve6( &byteOut ) ) fprintf( pFile, "\nHT_bGetItemReserve6 : %d", byteOut );
	if ( this->HT_bGetItemTimeLimit( &sOut ) ) fprintf( pFile, "\nHT_bGetItemTimeLimit : %d", sOut );
	if ( this->HT_bGetItemFXEffectID( &iOut ) ) fprintf( pFile, "\nHT_bGetItemFXEffectID : %d", iOut );
}

void
	CHTParameterMgr::HT_vTestNPCParamWithID( FILE* pFile, const int id )
{
	byte byteOut;
	short sOut, sOut2;
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
	CHTParameterMgr::HT_vTestNPCParam( FILE* pFile )
{
	byte byteOut;
	short sOut, sOut2;
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
	CHTParameterMgr::HT_vTestPortalParam( FILE* pFile, const int id )
{
	int	iOut;
	DWORD dwOut, dwOut2;
	short sOut, sOut2, sOut3, sOut4;

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
	CHTParameterMgr::HT_vTestTaskQuestParamWithID( FILE* pFile, const int id )
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
	CHTParameterMgr::HT_vTestTaskQuestParam( FILE* pFile )
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

#ifdef HT_NEED_NAME
bool
	CHTParameterMgr::HT_bGetName( const int id, CHTString* pstrName )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetName( id, pstrName );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetName( const int id, const byte byteLevel, CHTString* pstrName )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetName( id, byteLevel, pstrName );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetName( CHTString* pstrName )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetName( pstrName );
	else return false;
}
#endif

bool
	CHTParameterMgr::HT_bGetMonsterLevel( const int id, byte* pbyteLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterLevel( id, pbyteLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterClass( const int id, byte* pbyteClass )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterClass( id, pbyteClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSize( const int id, byte* pbyteSize )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSize( id, pbyteSize );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAI( const int id, int* piAI )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterAI( id, piAI );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTargetTime( const int id, byte* pbyteSelectTargetTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSelectTargetTime( id, pbyteSelectTargetTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget0( const int id, byte* pbyteSelectTarget0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSelectTarget0( id, pbyteSelectTarget0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget1( const int id, byte* pbyteSelectTarget1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSelectTarget1( id, pbyteSelectTarget1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget2( const int id, byte* pbyteSelectTarget2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSelectTarget2( id, pbyteSelectTarget2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget3( const int id, byte* pbyteSelectTarget3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSelectTarget3( id, pbyteSelectTarget3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAggrCond( const int id, byte* pbyteAggrCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterAggrCond( id, pbyteAggrCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFleeCond( const int id, byte* pbyteFleeCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterFleeCond( id, pbyteFleeCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFleeCondCount( const int id, byte* pbyteFleeCondCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterFleeCondCount( id, pbyteFleeCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterTraceCond( const int id, byte* pbyteTraceCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterTraceCond( id, pbyteTraceCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterStepBackCond( const int id, byte* pbyteStepBackCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterStepBackCond( id, pbyteStepBackCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHelpCond( const int id, byte* pbyteHelpCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterHelpCond( id, pbyteHelpCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHelpCondCount( const int id, byte* pbyteHelpCondCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterHelpCondCount( id, pbyteHelpCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLinkCond( const int id, byte* pbyteLinkCond )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterLinkCond( id, pbyteLinkCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLinkCondCount( const int id, byte* pbyteLinkCondCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterLinkCondCount( id, pbyteLinkCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterBlockedCell( const int id, int* piBlockedCell )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterBlockedCell( id, piBlockedCell );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterCantDetect( const int id, int* piCantDetect )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterCantDetect( id, piCantDetect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterTrimuriti( const int id, byte* pbyteTrimuriti )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterTrimuriti( id, pbyteTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterNormalSight( const int id, byte* pbyteNormalSight )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterNormalSight( id, pbyteNormalSight );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterCombatSight( const int id, byte* pbyteCombatSight )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterCombatSight( id, pbyteCombatSight );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPopDelayMin( const int id, unsigned int* pnPopDelayMin )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterPopDelayMin( id, pnPopDelayMin );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPopDelayMax( const int id, unsigned int* pnPopDelayMax )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterPopDelayMax( id, pnPopDelayMax );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMovement( const int id, byte* pbyteMovement )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterMovement( id, pbyteMovement );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSpeechRate( const int id, byte* pbyteSpeechRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSpeechRate( id, pbyteSpeechRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSpeechAI( const int id, byte* pbyteSpeechAI )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSpeechAI( id, pbyteSpeechAI );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterEventNo( const int id, unsigned int* pnEventNo )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterEventNo( id, pnEventNo );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMuscle( const int id, short* psMuscle )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterMuscle( id, psMuscle );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterNerves( const int id, short* psNerves )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterNerves( id, psNerves );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHeart( const int id, short* psHeart )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterHeart( id, psHeart );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMind( const int id, short* psMind )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterMind( id, psMind );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterArmorType( const int id, byte* pbyteArmorType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterArmorType( id, pbyteArmorType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHP( const int id, unsigned int* pnHP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterHP( id, pnHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHPRecovery( const int id, byte* pbyteHPRecovery )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterHPRecovery( id, pbyteHPRecovery );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAttackRate( const int id, int* piAttackRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterAttackRate( id, piAttackRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterDodgeRate( const int id, int* piDodgeRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterDodgeRate( id, piDodgeRate );
	else return false;
}
/*
bool
CHTParameterMgr::HT_bGetMonsterBlockRate( const int id, byte* pbyteBlockRate )
{
CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
if ( pParamTable ) return pParamTable->HT_bGetMonsterBlockRate( id, pbyteBlockRate );
else return false;
}

bool
CHTParameterMgr::HT_bGetMonsterCriticalRate( const int id, byte* pbyteCriticalRate )
{
CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
if ( pParamTable ) return pParamTable->HT_bGetMonsterCriticalRate( id, pbyteCriticalRate );
else return false;
}
*/
bool
	CHTParameterMgr::HT_bGetMonsterAC( const int id, int* piAC )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterAC( id, piAC );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFireResist( const int id, int* piFireResist )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterFireResist( id, piFireResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterColdResist( const int id, int* piColdResist )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterColdResist( id, piColdResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLightningResist( const int id, int* piLightningResist )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterLightningResist( id, piLightningResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPoisonResist( const int id, int* piPoisonResist )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterPoisonResist( id, piPoisonResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterWalkSpeed( const int id, int* piWalkSpeed )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterWalkSpeed( id, piWalkSpeed );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRunSpeed( const int id, int* piRunSpeed )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterRunSpeed( id, piRunSpeed );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFly( const int id, byte* pbFly )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterFly( id, pbFly );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill0( const int id, int* pidSkill0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill0( id, pidSkill0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill1( const int id, int* pidSkill1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill1( id, pidSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill2( const int id, int* pidSkill2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill2( id, pidSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill3( const int id, int* pidSkill3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill3( id, pidSkill3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill4( const int id, int* pidSkill4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill4( id, pidSkill4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill5( const int id, int* pidSkill5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill5( id, pidSkill5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill6( const int id, int* pidSkill6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill6( id, pidSkill6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill7( const int id, int* pidSkill7 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkill7( id, pidSkill7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern0( const int id, byte* pbyteSkillPattern0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillPattern0( id, pbyteSkillPattern0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern1( const int id, byte* pbyteSkillPattern1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillPattern1( id, pbyteSkillPattern1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern2( const int id, byte* pbyteSkillPattern2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillPattern2( id, pbyteSkillPattern2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern3( const int id, byte* pbyteSkillPattern3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillPattern3( id, pbyteSkillPattern3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterImmunity( const int id, int* piImmunity )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterImmunity( id, piImmunity );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterResistEffectConst( const int id, byte* pbyteResistEffectConst )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterResistEffectConst( id, pbyteResistEffectConst );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardBrahmanPoint( const int id, unsigned int* pnRewardBrahmanPoint )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterRewardBrahmanPoint( id, pnRewardBrahmanPoint );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardGold( const int id, unsigned int* pnRewardGold )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterRewardGold( id, pnRewardGold );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardPrana( const int id, unsigned int* pnRewardPrana )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterRewardPrana( id, pnRewardPrana );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem0ItemID( const int id, short* psItem0ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem0ItemID( id, psItem0ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem0DropRate( const int id, short* psItem0DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem0DropRate( id, psItem0DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem1ItemID( const int id, short* psItem1ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem1ItemID( id, psItem1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem1DropRate( const int id, short* psItem1DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem1DropRate( id, psItem1DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem2ItemID( const int id, short* psItem2ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem2ItemID( id, psItem2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem2DropRate( const int id, short* psItem2DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem2DropRate( id, psItem2DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem3ItemID( const int id, short* psItem3ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem3ItemID( id, psItem3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem3DropRate( const int id, short* psItem3DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem3DropRate( id, psItem3DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem4ItemID( const int id, short* psItem4ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem4ItemID( id, psItem4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem4DropRate( const int id, short* psItem4DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem4DropRate( id, psItem4DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem5ItemID( const int id, short* psItem5ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem5ItemID( id, psItem5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem5DropRate( const int id, short* psItem5DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem5DropRate( id, psItem5DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem6ItemID( const int id, short* psItem6ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem6ItemID( id, psItem6ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem6DropRate( const int id, short* psItem6DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem6DropRate( id, psItem6DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem7ItemID( const int id, short* psItem7ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem7ItemID( id, psItem7ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem7DropRate( const int id, short* psItem7DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem7DropRate( id, psItem7DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem8Grade( const int id, byte* pbyteItem8Grade )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem8Grade( id, pbyteItem8Grade );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem8DropRate( const int id, short* psItem8DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem8DropRate( id, psItem8DropRate );
	else return false;
}

//bool
//CHTParameterMgr::HT_bGetMonsterItem8DeadCount( const int id, unsigned int* pnItem8DeadCount )
//{
//	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
//	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem8DeadCount( id, pnItem8DeadCount );
//	else return false;
//}

bool
	CHTParameterMgr::HT_bGetMonsterItem9Grade( const int id, byte* pbyteItem9Grade )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem9Grade( id, pbyteItem9Grade );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem9DropRate( const int id, short* psItem9DropRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterItem9DropRate( id, psItem9DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve0( const int id, byte* pbyteReserve0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve0( id, pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve1( const int id, byte* pbyteReserve1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve1( id, pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve2( const int id, byte* pbyteReserve2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve2( id, pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve3( const int id, byte* pbyteReserve3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve3( id, pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve4( const int id, byte* pbyteReserve4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve4( id, pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve5( const int id, byte* pbyteReserve5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve5( id, pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve6( const int id, byte* pbyteReserve6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve6( id, pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve7( const int id, byte* pbyteReserve7)
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterReserve7( id, pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLevel( byte* pbyteLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterLevel( pbyteLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSize( byte* pbyteSize )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSize( pbyteSize );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterClass( byte* pbyteClass )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterClass( pbyteClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAI( int* piAI )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterAI( piAI );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTargetTime( byte* pbyteSelectTargetTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSelectTargetTime( pbyteSelectTargetTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget0( byte* pbyteSelectTarget0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSelectTarget0( pbyteSelectTarget0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget1( byte* pbyteSelectTarget1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSelectTarget1( pbyteSelectTarget1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget2( byte* pbyteSelectTarget2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSelectTarget2( pbyteSelectTarget2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSelectTarget3( byte* pbyteSelectTarget3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSelectTarget3( pbyteSelectTarget3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAggrCond( byte* pbyteAggrCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterAggrCond( pbyteAggrCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFleeCond( byte* pbyteFleeCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterFleeCond( pbyteFleeCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFleeCondCount( byte* pbyteFleeCondCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterFleeCondCount( pbyteFleeCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterTraceCond( byte* pbyteTraceCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterTraceCond( pbyteTraceCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterStepBackCond( byte* pbyteStepBackCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterStepBackCond( pbyteStepBackCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHelpCond( byte* pbyteHelpCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterHelpCond( pbyteHelpCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHelpCondCount( byte* pbyteHelpCondCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterHelpCondCount( pbyteHelpCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLinkCond( byte* pbyteLinkCond )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterLinkCond( pbyteLinkCond );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLinkCondCount( byte* pbyteLinkCondCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterLinkCondCount( pbyteLinkCondCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterBlockedCell( int* piBlockedCell )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterBlockedCell( piBlockedCell );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterCantDetect( int* piCantDetect )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterCantDetect( piCantDetect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterTrimuriti( byte* pbyteTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterTrimuriti( pbyteTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterNormalSight( byte* pbyteNormalSight )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterNormalSight( pbyteNormalSight );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterCombatSight( byte* pbyteCombatSight )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterCombatSight( pbyteCombatSight );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPopDelayMin( unsigned int* pnPopDelayMin )

{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterPopDelayMin( pnPopDelayMin );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPopDelayMax( unsigned int* pnPopDelayMax )

{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterPopDelayMax( pnPopDelayMax );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMovement( byte* pbyteMovement )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterMovement( pbyteMovement );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSpeechRate( byte* pbyteSpeechRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSpeechRate( pbyteSpeechRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSpeechAI( byte* pbyteSpeechAI )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSpeechAI( pbyteSpeechAI );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterEventNo( unsigned int* pnEventNo )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterEventNo( pnEventNo );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMuscle( short* psMuscle )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterMuscle( psMuscle );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterNerves( short* psNerves )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterNerves( psNerves );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHeart( short* psHeart )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterHeart( psHeart );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterMind( short* psMind )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterMind( psMind );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterArmorType( byte* pbyteArmorType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterArmorType( pbyteArmorType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHP( unsigned int* pnHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterHP( pnHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterHPRecovery( byte* pbyteHPRecovery )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterHPRecovery( pbyteHPRecovery );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterAttackRate( int* piAttackRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterAttackRate( piAttackRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterDodgeRate( int* piDodgeRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterDodgeRate( piDodgeRate );
	else return false;
}
/*
bool
CHTParameterMgr::HT_bGetMonsterBlockRate( byte* pbyteBlockRate )
{
if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterBlockRate( pbyteBlockRate );
else return false;
}

bool
CHTParameterMgr::HT_bGetMonsterCriticalRate( byte* pbyteCriticalRate )
{
if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterCriticalRate( pbyteCriticalRate );
else return false;
}
*/
bool
	CHTParameterMgr::HT_bGetMonsterAC( int* piAC )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterAC( piAC );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFireResist( int* piFireResist )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterFireResist( piFireResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterColdResist( int* piColdResist )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterColdResist( piColdResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterLightningResist( int* piLightningResist )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterLightningResist( piLightningResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterPoisonResist( int* piPoisonResist )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterPoisonResist( piPoisonResist );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterWalkSpeed( int* piWalkSpeed )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterWalkSpeed( piWalkSpeed );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRunSpeed( int* piRunSpeed )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterRunSpeed( piRunSpeed );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterFly( byte* pbFly )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterFly( pbFly );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill0( int* pidSkill0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill0( pidSkill0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill1( int* pidSkill1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill1( pidSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill2( int* pidSkill2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill2( pidSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill3( int* pidSkill3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill3( pidSkill3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill4( int* pidSkill4 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill4( pidSkill4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill5( int* pidSkill5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill5( pidSkill5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill6( int* pidSkill6 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill6( pidSkill6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkill7( int* pidSkill7 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkill7( pidSkill7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern0( byte* pbyteSkillPattern0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillPattern0( pbyteSkillPattern0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern1( byte* pbyteSkillPattern1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillPattern1( pbyteSkillPattern1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern2( byte* pbyteSkillPattern2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillPattern2( pbyteSkillPattern2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPattern3( byte* pbyteSkillPattern3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillPattern3( pbyteSkillPattern3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterImmunity( int* piImmunity )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterImmunity( piImmunity );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterResistEffectConst( byte* pbyteResistEffectConst )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterResistEffectConst( pbyteResistEffectConst );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardBrahmanPoint( unsigned int* pnRewardBrahmanPoint )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterRewardBrahmanPoint( pnRewardBrahmanPoint );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardGold( unsigned int* pnRewardGold )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterRewardGold( pnRewardGold );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterRewardPrana( unsigned int* pnRewardPrana )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterRewardPrana( pnRewardPrana );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem0ItemID( short* psItem0ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem0ItemID( psItem0ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem0DropRate( short* psItem0DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem0DropRate( psItem0DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem1ItemID( short* psItem1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem1ItemID( psItem1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem1DropRate( short* psItem1DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem1DropRate( psItem1DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem2ItemID( short* psItem2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem2ItemID( psItem2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem2DropRate( short* psItem2DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem2DropRate( psItem2DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem3ItemID( short* psItem3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem3ItemID( psItem3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem3DropRate( short* psItem3DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem3DropRate( psItem3DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem4ItemID( short* psItem4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem4ItemID( psItem4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem4DropRate( short* psItem4DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem4DropRate( psItem4DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem5ItemID( short* psItem5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem5ItemID( psItem5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem5DropRate( short* psItem5DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem5DropRate( psItem5DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem6ItemID( short* psItem6ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem6ItemID( psItem6ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem6DropRate( short* psItem6DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem6DropRate( psItem6DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem7ItemID( short* psItem7ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem7ItemID( psItem7ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem7DropRate( short* psItem7DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem7DropRate( psItem7DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem8Grade( byte* pbyteItem8Grade )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem8Grade( pbyteItem8Grade );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem8DropRate( short* psItem8DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem8DropRate( psItem8DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem9Grade( byte* pbyteItem9Grade )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem9Grade( pbyteItem9Grade );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterItem9DropRate( short* psItem9DropRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterItem9DropRate( psItem9DropRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve0( byte* pbyteReserve0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve0( pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve1( byte* pbyteReserve1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve1( pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve2( byte* pbyteReserve2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve2( pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve3( byte* pbyteReserve3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve3( pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve4( byte* pbyteReserve4 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve4( pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve5( byte* pbyteReserve5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve5( pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve6( byte* pbyteReserve6 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve6( pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterReserve7( byte* pbyteReserve7 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterReserve7( pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillMaxLevel( id, byteLevel, pbyteMaxLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillType( const int id, const byte byteLevel, byte* pbyteType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillType( id, byteLevel, pbyteType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCombatPhase( id, byteLevel, psCombatPhase );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSpeechContent( const int id, const byte byteLevel, short* psSpeechContent )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillSpeechContent( id, byteLevel, psSpeechContent );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillDuration( const int id, const byte byteLevel, int* piDuration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillDuration( id, byteLevel, piDuration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillSuccessRate( id, byteLevel, pbyteSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSyncFlag( const int id, const byte byteLevel, byte* pbyteSyncFlag )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillSyncFlag( id, byteLevel, pbyteSyncFlag );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCastingSuccessRate( id, byteLevel, pbyteCastingSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillFollowRange( id, byteLevel, pbyteFollowRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillPierceRate( id, byteLevel, pbytePierceRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCoolDownTime( id, byteLevel, piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCastingTime( id, byteLevel, piCastingTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillActivateTime( const int id, const byte byteLevel, int* piActivateTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillActivateTime( id, byteLevel, piActivateTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastCount( const int id, const byte byteLevel, byte* pbyteCastCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCastCount( id, byteLevel, pbyteCastCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillRange( const int id, const byte byteLevel, int* piRange )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillRange( id, byteLevel, piRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillAreaOfEffect( id, byteLevel, piAreaOfEffect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillAllowedTarget( id, byteLevel, piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillAttackType( id, byteLevel, pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqTrimuriti( id, byteLevel, piReqTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqTribe( id, byteLevel, piReqTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqWeaponType( id, byteLevel, piReqWeaponType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillidReqItem( id, byteLevel, pidReqItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqLevel( id, byteLevel, pbyteReqLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqSkill1( id, byteLevel, pidReqSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqSkill1_Lvl( id, byteLevel, pbyteReqSkill1_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqSkill2( id, byteLevel, pidReqSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReqSkill2_Lvl( id, byteLevel, pbyteReqSkill2_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect1ID( id, byteLevel, piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect1Function( id, byteLevel, piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect1Duration( id, byteLevel, piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect1Param1( id, byteLevel, piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect1Param2( id, byteLevel, piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect2ID( id, byteLevel, piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect2Function( id, byteLevel, piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect2Duration( id, byteLevel, piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect2Param1( id, byteLevel, piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect2Param2( id, byteLevel, piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect3ID( id, byteLevel, piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect3Function( id, byteLevel, piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect3Duration( id, byteLevel, piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect3Param1( id, byteLevel, piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect3Param2( id, byteLevel, piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect4ID( id, byteLevel, piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect4Function( id, byteLevel, piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect4Duration( id, byteLevel, piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect4Param1( id, byteLevel, piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect4Param2( id, byteLevel, piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect5ID( id, byteLevel, piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect5Function( id, byteLevel, piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect5Duration( id, byteLevel, piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect5Param1( id, byteLevel, piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillEffect5Param2( id, byteLevel, piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCostTP( const int id, const byte byteLevel, int* piCostTP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCostTP( id, byteLevel, piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCostHP( const int id, const byte byteLevel, int* piCostHP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillCostHP( id, byteLevel, piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillidCostItem( id, byteLevel, pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve0( id, byteLevel, pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve1( id, byteLevel, pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve2( id, byteLevel, pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve3( id, byteLevel, pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve4( id, byteLevel, pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve5( id, byteLevel, pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve6( id, byteLevel, pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetMonsterSkillReserve7( id, byteLevel, pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillMaxLevel( byte* pbyteMaxLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillMaxLevel( pbyteMaxLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillType( byte* pbyteType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillType( pbyteType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCombatPhase( short* psCombatPhase )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCombatPhase( psCombatPhase );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSpeechContent( short* psSpeechContent )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillSpeechContent( psSpeechContent );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillDuration( int* piDuration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillDuration( piDuration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSuccessRate( byte* pbyteSuccessRate )
{
	if ( m_pParamTable ) return  m_pParamTable->HT_bGetMonsterSkillSuccessRate( pbyteSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillSyncFlag( byte* pbyteSyncFlag )
{
	if ( m_pParamTable ) return  m_pParamTable->HT_bGetMonsterSkillSyncFlag( pbyteSyncFlag );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastingSuccessRate( byte* pbyteCastingSuccessRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCastingSuccessRate( pbyteCastingSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillFollowRange( byte* pbyteFollowRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillFollowRange( pbyteFollowRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillPierceRate( byte* pbytePierceRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillPierceRate( pbytePierceRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCoolDownTime( piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastingTime( int* piCastingTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCastingTime( piCastingTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillActivateTime( int* piActivateTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillActivateTime( piActivateTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCastCount( byte* pbyteCastCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCastCount( pbyteCastCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillRange( int* piRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillRange( piRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAreaOfEffect( int* piAreaOfEffect )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillAreaOfEffect( piAreaOfEffect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillAllowedTarget( piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillAttackType( byte* pbyteAttackType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillAttackType( pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqTrimuriti( int* piReqTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqTrimuriti( piReqTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqTribe( int* piReqTribe )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqTribe( piReqTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqWeaponType( int* piReqWeaponType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqWeaponType( piReqWeaponType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillidReqItem( int* pidReqItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillidReqItem( pidReqItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqLevel( byte* pbyteReqLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqLevel( pbyteReqLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill1( int* pidReqSkill1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqSkill1( pidReqSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqSkill1_Lvl( pbyteReqSkill1_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill2( int* pidReqSkill2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqSkill2( pidReqSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReqSkill2_Lvl( pbyteReqSkill2_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1ID( int* piEffect1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect1ID( piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Function( int* piEffect1Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect1Function( piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect1Duration( piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect1Param1( piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect1Param2( piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2ID( int* piEffect2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect2ID( piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Function( int* piEffect2Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect2Function( piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect2Duration( piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect2Param1( piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect2Param2( piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3ID( int* piEffect3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect3ID( piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Function( int* piEffect3Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect3Function( piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect3Duration( piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect3Param1( piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect3Param2( piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4ID( int* piEffect4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect4ID( piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Function( int* piEffect4Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect4Function( piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect4Duration( piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect4Param1( piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect4Param2( piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5ID( int* piEffect5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect5ID( piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Function( int* piEffect5Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect5Function( piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect5Duration( piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect5Param1( piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillEffect5Param2( piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCostTP( int* piCostTP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCostTP( piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillCostHP( int* piCostHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillCostHP( piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillidCostItem( int* pidCostItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillidCostItem( pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve0( byte* pbyteReserve0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve0( pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve1( byte* pbyteReserve1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve1( pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve2( byte* pbyteReserve2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve2( pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve3( byte* pbyteReserve3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve3( pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve4( byte* pbyteReserve4 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve4( pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve5( byte* pbyteReserve5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve5( pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve6( byte* pbyteReserve6 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve6( pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMonsterSkillReserve7( byte* pbyteReserve7 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetMonsterSkillReserve7( pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillMaxLevel( id, byteLevel, pbyteMaxLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillType( id, byteLevel, pbyteType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCombatPhase( id, byteLevel, psCombatPhase );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillDuration( id, byteLevel, piDuration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillSuccessRate( id, byteLevel, pbyteSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCastingSuccessRate( id, byteLevel, pbyteCastingSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillFollowRange( id, byteLevel, pbyteFollowRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillPierceRate( id, byteLevel, pbytePierceRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCoolDownTime( id, byteLevel, piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReadyTime( id, byteLevel, piReadyTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCastingTime( id, byteLevel, piCastingTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillApplyTime( id, byteLevel, piApplyTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillRange( id, byteLevel, piRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAreaOfEffect( id, byteLevel, piAreaOfEffect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAllowedTarget( id, byteLevel, piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillAttackType( id, byteLevel, pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqTrimuriti( id, byteLevel, piReqTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqTribe( id, byteLevel, piReqTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqClass( id, byteLevel, piReqClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqWeaponType( id, byteLevel, piReqWeaponType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillidReqItem( id, byteLevel, pidReqItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqLevel( id, byteLevel, pbyteReqLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill1( id, byteLevel, pidReqSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill1_Lvl( id, byteLevel, pbyteReqSkill1_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill2( id, byteLevel, pidReqSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReqSkill2_Lvl( id, byteLevel, pbyteReqSkill2_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1ID( id, byteLevel, piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Function( id, byteLevel, piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Duration( id, byteLevel, piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Param1( id, byteLevel, piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect1Param2( id, byteLevel, piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2ID( id, byteLevel, piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Function( id, byteLevel, piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Duration( id, byteLevel, piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Param1( id, byteLevel, piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect2Param2( id, byteLevel, piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3ID( id, byteLevel, piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Function( id, byteLevel, piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Duration( id, byteLevel, piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Param1( id, byteLevel, piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect3Param2( id, byteLevel, piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4ID( id, byteLevel, piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Function( id, byteLevel, piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Duration( id, byteLevel, piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Param1( id, byteLevel, piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect4Param2( id, byteLevel, piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5ID( id, byteLevel, piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Function( id, byteLevel, piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Duration( id, byteLevel, piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Param1( id, byteLevel, piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillEffect5Param2( id, byteLevel, piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostTP( id, byteLevel, piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostHP( id, byteLevel, piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillidCostItem( id, byteLevel, pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillCostItemCount( id, byteLevel, pbyteCostItemCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve0( const int id, const byte byteLevel, byte* pbyteReserve0 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve0( id, byteLevel, pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve1( const int id, const byte byteLevel, byte* pbyteReserve1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve1( id, byteLevel, pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve2( const int id, const byte byteLevel, byte* pbyteReserve2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve2( id, byteLevel, pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve3( const int id, const byte byteLevel, byte* pbyteReserve3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve3( id, byteLevel, pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve4( const int id, const byte byteLevel, byte* pbyteReserve4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve4( id, byteLevel, pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve5( const int id, const byte byteLevel, byte* pbyteReserve5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve5( id, byteLevel, pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve6( const int id, const byte byteLevel, byte* pbyteReserve6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve6( id, byteLevel, pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve7( const int id, const byte byteLevel, byte* pbyteReserve7 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPCSkillReserve7( id, byteLevel, pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillMaxLevel( pbyteMaxLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillType( byte* pbyteType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillType( pbyteType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCombatPhase( short* psCombatPhase )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCombatPhase( psCombatPhase );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillDuration( int* piDuration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillDuration( piDuration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate )
{
	if ( m_pParamTable ) return  m_pParamTable->HT_bGetPCSkillSuccessRate( pbyteSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCastingSuccessRate( pbyteCastingSuccessRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillFollowRange( byte* pbyteFollowRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillFollowRange( pbyteFollowRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillPierceRate( byte* pbytePierceRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillPierceRate( pbytePierceRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCoolDownTime( piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReadyTime( int* piReadyTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReadyTime( piReadyTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCastingTime( int* piCastingTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCastingTime( piCastingTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillApplyTime( int* piApplyTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillApplyTime( piApplyTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillRange( int* piRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillRange( piRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAreaOfEffect( piAreaOfEffect );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAllowedTarget( piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillAttackType( byte* pbyteAttackType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillAttackType( pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqTrimuriti( piReqTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqTribe( int* piReqTribe )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqTribe( piReqTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqClass( int* piReqClass )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqClass( piReqClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqWeaponType( int* piReqWeaponType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqWeaponType( piReqWeaponType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillidReqItem( int* pidReqItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillidReqItem( pidReqItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqLevel( byte* pbyteReqLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqLevel( pbyteReqLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill1( int* pidReqSkill1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill1( pidReqSkill1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill1_Lvl( pbyteReqSkill1_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill2( int* pidReqSkill2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill2( pidReqSkill2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReqSkill2_Lvl( pbyteReqSkill2_Lvl );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1ID( int* piEffect1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1ID( piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Function( int* piEffect1Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Function( piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Duration( piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Param1( piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect1Param2( piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2ID( int* piEffect2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2ID( piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Function( int* piEffect2Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Function( piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Duration( piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Param1( piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect2Param2( piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3ID( int* piEffect3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3ID( piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Function( int* piEffect3Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Function( piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Duration( piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Param1( piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect3Param2( piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4ID( int* piEffect4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4ID( piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Function( int* piEffect4Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Function( piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Duration( piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Param1( piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect4Param2( piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5ID( int* piEffect5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5ID( piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Function( int* piEffect5Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Function( piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Duration( piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Param1( piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillEffect5Param2( piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostTP( int* piCostTP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostTP( piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostHP( int* piCostHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostHP( piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillidCostItem( int* pidCostItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillidCostItem( pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillCostItemCount( pbyteCostItemCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve0( byte* pbyteReserve0 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve0( pbyteReserve0 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve1( byte* pbyteReserve1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve1( pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve2( byte* pbyteReserve2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve2( pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve3( byte* pbyteReserve3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve3( pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve4( byte* pbyteReserve4 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve4( pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve5( byte* pbyteReserve5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve5( pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve6( byte* pbyteReserve6 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve6( pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPCSkillReserve7( byte* pbyteReserve7 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetPCSkillReserve7( pbyteReserve7 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLevel( const int id, byte* pbyteLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLevel( id, pbyteLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemClass( const int id, byte* pbyteClass )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemClass( id, pbyteClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemType( const int id, short* psType)
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemType( id, psType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRupiah( const int id, int* piRupiah )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRupiah( id, piRupiah );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemSellRupiah( const int id, int* piSellRupiah )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemSellRupiah( id, piSellRupiah );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemMaxDurability( const int id, short* psMaxDurability )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemMaxDurability( id, psMaxDurability );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemMaxCount( id, pbyteMaxCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCombatPhase( const int id, short* psCombatPhase )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCombatPhase( id, psCombatPhase );
	else return false;

}

bool
	CHTParameterMgr::HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemSkillCastingTimeRate( id, psSkillCastingTimeRate );
	else return false;

}

bool
	CHTParameterMgr::HT_bGetItemEffect1ID( const int id, int* piEffect1ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1ID( id, piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Function( const int id, int* piEffect1Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Function( id, piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Duration( id, piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Param1( id, piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect1Param2( id, piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2ID( const int id, int* piEffect2ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2ID( id, piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Function( const int id, int* piEffect2Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Function( id, piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Duration( id, piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Param1( id, piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect2Param2( id, piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3ID( const int id, int* piEffect3ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3ID( id, piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Function( const int id, int* piEffect3Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Function( id, piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Duration( id, piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Param1( id, piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect3Param2( id, piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4ID( const int id, int* piEffect4ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4ID( id, piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Function( const int id, int* piEffect4Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Function( id, piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Duration( id, piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Param1( id, piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect4Param2( id, piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5ID( const int id, int* piEffect5ID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5ID( id, piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Function( const int id, int* piEffect5Function )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Function( id, piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Duration( id, piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Param1( id, piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEffect5Param2( id, piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCoolDownTime( id, piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRange( const int id, byte* pbyteRange )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRange( id, pbyteRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemAllowedTarget( const int id, int* piAllowedTarget )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemAllowedTarget( id, piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemAttackType( const int id, byte* pbyteAttackType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemAttackType( id, pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemArmorType( const int id, byte* pbyteArmorType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemArmorType( id, pbyteArmorType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCostTP( const int id, int* piCostTP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCostTP( id, piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCostHP( const int id, int* piCostHP )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCostHP( id, piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemidCostItem( const int id, int* pidCostItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemidCostItem( id, pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitTrimuriti( id, piLimitTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitTribe( const int id, int* piLimitTribe )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitTribe( id, piLimitTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitLevel( id, pbyteLimitLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitMuscleChakra( id, psLimitMusclechakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitNerveChakra( id, psLimitNerveChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitHeartChakra( id, psLimitHeartChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemLimitSoulChakra( id, psLimitSoulChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemRefinableItemType( id, piRefinableItemType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEventID( const int id, short* psEventID )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemEventID( id, psEventID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCash( const int id, int* piCash )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemCash( id, piCash );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve1( const int id, byte* pbyteReserve1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve1( id, pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve2( const int id, byte* pbyteReserve2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve2( id, pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve3( const int id, byte* pbyteReserve3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve3( id, pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve4( const int id, byte* pbyteReserve4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve4( id, pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve5( const int id, byte* pbyteReserve5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve5( id, pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve6( const int id, byte* pbyteReserve6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemReserve6( id, pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemTimeLimit( const int id, short* psTimeLimit )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemTimeLimit( id, psTimeLimit );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemFXEffectID( const int id, int* pidFX )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetItemFXEffectID( id, pidFX );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLevel( byte* pbyteLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLevel( pbyteLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemClass( byte* pbyteClass)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLevel( pbyteClass );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemType( short* psType)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemType( psType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRupiah( int* piRupiah )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRupiah( piRupiah );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemSellRupiah( int* piSellRupiah )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemSellRupiah( piSellRupiah );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemMaxDurability( short* psMaxDurability )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemMaxDurability( psMaxDurability );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemMaxCount( byte* pbyteMaxCount )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemMaxCount( pbyteMaxCount );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCombatPhase( short* psCombatPhase )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCombatPhase( psCombatPhase );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemSkillCastingTimeRate( psSkillCastingTimeRate );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1ID( int* piEffect1ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1ID( piEffect1ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Function( int* piEffect1Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Function( piEffect1Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Duration( int* piEffect1Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Duration( piEffect1Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Param1( int* piEffect1Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Param1( piEffect1Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect1Param2( int* piEffect1Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect1Param2( piEffect1Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2ID( int* piEffect2ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2ID( piEffect2ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Function( int* piEffect2Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Function( piEffect2Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Duration( int* piEffect2Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Duration( piEffect2Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Param1( int* piEffect2Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Param1( piEffect2Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect2Param2( int* piEffect2Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect2Param2( piEffect2Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3ID( int* piEffect3ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3ID( piEffect3ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Function( int* piEffect3Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Function( piEffect3Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Duration( int* piEffect3Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Duration( piEffect3Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Param1( int* piEffect3Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Param1( piEffect3Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect3Param2( int* piEffect3Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect3Param2( piEffect3Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4ID( int* piEffect4ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4ID( piEffect4ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Function( int* piEffect4Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Function( piEffect4Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Duration( int* piEffect4Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Duration( piEffect4Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Param1( int* piEffect4Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Param1( piEffect4Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect4Param2( int* piEffect4Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect4Param2( piEffect4Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5ID( int* piEffect5ID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5ID( piEffect5ID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Function( int* piEffect5Function )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Function( piEffect5Function );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Duration( int* piEffect5Duration )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Duration( piEffect5Duration );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Param1( int* piEffect5Param1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Param1( piEffect5Param1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEffect5Param2( int* piEffect5Param2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEffect5Param2( piEffect5Param2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCoolDownTime( int* piCoolDownTime )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCoolDownTime( piCoolDownTime );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRange( byte* pbyteRange )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRange( pbyteRange );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemAllowedTarget( int* piAllowedTarget )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemAllowedTarget( piAllowedTarget );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemArmorType( byte* pbyteArmorType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemArmorType( pbyteArmorType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemAttackType( byte* pbyteAttackType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemAttackType( pbyteAttackType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCostTP( int* piCostTP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCostTP( piCostTP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCostHP( int* piCostHP )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCostHP( piCostHP );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemidCostItem( int* pidCostItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemidCostItem( pidCostItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitTrimuriti( piLimitTrimuriti );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitTribe( int* piLimitTribe )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitTribe( piLimitTribe );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitLevel( byte* pbyteLimitLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitLevel( pbyteLimitLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitMuscleChakra( psLimitMusclechakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitNerveChakra( psLimitNerveChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitHeartChakra( psLimitHeartChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemLimitSoulChakra( psLimitSoulChakra );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRefinableItemType( int* piRefinableItemType )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemRefinableItemType( piRefinableItemType );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemEventID( short* psEventID )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemEventID( psEventID );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemCash( int* piCash )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemCash( piCash );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve1( byte* pbyteReserve1 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve1( pbyteReserve1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve2( byte* pbyteReserve2 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve2( pbyteReserve2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve3( byte* pbyteReserve3 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve3( pbyteReserve3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve4( byte* pbyteReserve4 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve4( pbyteReserve4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve5( byte* pbyteReserve5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve5( pbyteReserve5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemReserve6( byte* pbyteReserve6 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemReserve6( pbyteReserve6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemTimeLimit( short* psTimeLimit )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemTimeLimit( psTimeLimit );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemFXEffectID( int* pidFX )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetItemFXEffectID( pidFX );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetItemRandIDByLevel( const byte byteLevel, int* pidItem )
{
	return m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bGetItemRandIDByLevel( byteLevel, pidItem );
}

bool
	CHTParameterMgr::HT_bGetNPCSize( const int id, byte* pbyteSize )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCSize( id, pbyteSize );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCZone( const int id, byte* pbyteZone )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCZone( id, pbyteZone );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCPosition( id, psPosX, psPosZ );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti)
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCTrimuriti( id, pbyNPCTrimuriti );
	else return false;
}

int
	CHTParameterMgr::HT_iGetNPCSellingItemCount( const int id )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_iGetNPCSellingItemCount( id );
	else return -1;
}

bool
	CHTParameterMgr::HT_bGetNPCSellingItem( const int id, const int index, int* pidItem )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetNPCSellingItem( id, index, pidItem );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCSize( byte* pbyteSize )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCSize( pbyteSize );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCZone( byte* pbyteZone )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCZone( pbyteZone );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCPosition( short* psPosX, short* psPosZ )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCPosition( psPosX, psPosZ );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCTrimuriti( pbyNPCTrimuriti );
	else return false;
}

int
	CHTParameterMgr::HT_iGetNPCSellingItemCount()
{
	if ( m_pParamTable ) return m_pParamTable->HT_iGetNPCSellingItemCount();
	else return -1;
}

bool
	CHTParameterMgr::HT_bGetNPCSellingItem( const int index, int* pidItem )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetNPCSellingItem( index, pidItem );
	else return false;
}
// Portal
bool
	CHTParameterMgr::HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetGoingPortal( id, iNo, piGoPortal, pdwFee, pdwLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
	short* psStartX, short* psStartZ, short* psEndX, short* psEndZ)
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetPortalInfo( id, pdwServerID, pdwZoneLevel, psStartX, psStartZ, psEndX, psEndZ );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( idFromPortal );
	if ( pParamTable ) return pParamTable->HT_bGetPortalFee( idFromPortal, idToPrtal, pdwFee );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel)
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( idFromPortal );
	if ( pParamTable ) return pParamTable->HT_bGetPortalLevel( idFromPortal, idToPrtal, pdwLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetMapLevelRestrict( const int idMap, DWORD* pdwLevel )
{
	CHTBaseParamTable* pParamTable = m_arrParamTable[HT_PARAMTYPE_PORTAL];
	if ( pParamTable ) return pParamTable->HT_bGetMapLevelRestrict( idMap, pdwLevel );
	else return false;
}


// TaskQuest
bool
	CHTParameterMgr::HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, 
	short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskNPCID( id, psNPCID1, psNPCID2, psNPCID3, psNPCID4, psNPCID5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource1( const int id,/*short* psNPCID, */ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource1( id,/* psNPCID,*/ pbyteSourceType1, psSourceItemID1, piSourceCount1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource2( const int id,/*short* psNPCID, */ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource2( id,/* psNPCID,*/ pbyteSourceType2, psSourceItemID2, piSourceCount2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource3( const int id,/*short* psNPCID, */ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource3( id,/* psNPCID,*/ pbyteSourceType3, psSourceItemID3, piSourceCount3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource4( const int id,/*short* psNPCID, */ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource4( id,/* psNPCID,*/ pbyteSourceType4, psSourceItemID4, piSourceCount4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource5( const int id,/*short* psNPCID, */ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource5( id,/* psNPCID,*/ pbyteSourceType5, psSourceItemID5, piSourceCount5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskSource6( id,/* psNPCID,*/ pbyteSourceType6, psSourceItemID6, piSourceCount6 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1,
	short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward1( id,/* psNPCID,*/ pbyteRewardPriority1, pbyteRewardType1,
		psReward1Rate, psRewardItemID1, piRewardCount1 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2,
	short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward2( id,/* psNPCID,*/ pbyteRewardPriority2, pbyteRewardType2,
		psReward2Rate, psRewardItemID2, piRewardCount2 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3,
	short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward3( id,/* psNPCID,*/ pbyteRewardPriority3, pbyteRewardType3,
		psReward3Rate, psRewardItemID3, piRewardCount3 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4,
	short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward4( id,/* psNPCID,*/ pbyteRewardPriority4, pbyteRewardType4,
		psReward4Rate, psRewardItemID4, piRewardCount4 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward5( const int id, /*short* psNPCID, */byte* pbyteRewardPriority5, byte* pbyteRewardType5,
	short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5 )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskReward5( id, /*psNPCID, */pbyteRewardPriority5, pbyteRewardType5,
		psReward5Rate, psRewardItemID5, piRewardCount5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* pbyteMinLevel, byte* pbyteMaxLevel )
{
	CHTBaseParamTable* pParamTable = this->HT_pGetParamTable( id );
	if ( pParamTable ) return pParamTable->HT_bGetTaskLevel( id,/* psNPCID,*/ pbyteMinLevel, pbyteMaxLevel );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskNPCID( psNPCID1, psNPCID2, psNPCID3, psNPCID4, psNPCID5 );
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource1( /*psNPCID, */pbyteSourceType1, psSourceItemID1, piSourceCount1);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource2( /* short* psNPCID,*/byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource2( /*psNPCID, */pbyteSourceType2, psSourceItemID2, piSourceCount2);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource3( /* short* psNPCID,*/byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource3( /*psNPCID, */pbyteSourceType3, psSourceItemID3, piSourceCount3);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource4( /* short* psNPCID,*/byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource4( /*psNPCID, */pbyteSourceType4, psSourceItemID4, piSourceCount4);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource5( /* short* psNPCID,*/byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource5( /*psNPCID, */pbyteSourceType5, psSourceItemID5, piSourceCount5);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskSource6( /*short* psNPCID, */byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskSource6( /*psNPCID, */pbyteSourceType6, psSourceItemID6, piSourceCount6);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward1( /*short* psNPCID, */byte* pbyteRewardPriority1, byte* pbyteRewardType1,
	short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward1( /*psNPCID, */pbyteRewardPriority1, pbyteRewardType1,
		psReward1Rate, psRewardItemID1, piRewardCount1);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward2( /*short* psNPCID, */byte* pbyteRewardPriority2, byte* pbyteRewardType2,
	short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward2( /*psNPCID, */pbyteRewardPriority2, pbyteRewardType2,
		psReward2Rate, psRewardItemID2, piRewardCount2);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward3( /*short* psNPCID, */byte* pbyteRewardPriority3, byte* pbyteRewardType3,
	short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward3( /*psNPCID, */pbyteRewardPriority3, pbyteRewardType3,
		psReward3Rate, psRewardItemID3, piRewardCount3);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward4( /*short* psNPCID, */byte* pbyteRewardPriority4, byte* pbyteRewardType4,
	short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward4( /*psNPCID, */pbyteRewardPriority4, pbyteRewardType4,
		psReward4Rate, psRewardItemID4, piRewardCount4);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskReward5( /*short* psNPCID, */byte* pbyteRewardPriority5, byte* pbyteRewardType5,
	short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5)
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskReward5( /*psNPCID, */pbyteRewardPriority5, pbyteRewardType5,
		psReward5Rate, psRewardItemID5, piRewardCount5);
	else return false;
}

bool
	CHTParameterMgr::HT_bGetTaskLevel( /* short* psNPCID,*/ byte* pbyteMinLevel, byte* pbyteMaxLevel )
{
	if ( m_pParamTable ) return m_pParamTable->HT_bGetTaskLevel( /* psNPCID,*/ pbyteMinLevel, pbyteMaxLevel );

	else return false;
}

int
	CHTParameterMgr::HT_iGetAllCount( const int iType )
{
	switch ( iType )
	{
	case HT_PARAMTYPE_PCSKILL :	return int(m_vectorPCSkillIDLevelNagKin.size()+m_vectorPCSkillIDLevelAsuRak.size()
									+ m_vectorPCSkillIDLevelDevGar.size()+m_vectorPCSkillIDLevelYakGan.size());
	case HT_PARAMTYPE_ITEM :	return (int)m_vectorItemIDLevel.size();
	case HT_PARAMTYPE_NPC :		return (int)m_vectorNPCIDLevel.size();
	default :					return -1;
	}
}

bool
	CHTParameterMgr::HT_bGetIDLevelByIndex( const int iType, const int index, int* pid, byte* pbyteLevel )
{
	switch ( iType )
	{
	case HT_PARAMTYPE_PCSKILL :
		{
			int iSizeNagKin = (int)m_vectorPCSkillIDLevelNagKin.size();
			int iSizeAsuRak = (int)m_vectorPCSkillIDLevelAsuRak.size() + iSizeNagKin;
			int iSizeDevGar = (int)m_vectorPCSkillIDLevelDevGar.size() + iSizeAsuRak;
			int iSizeYakGan = (int)m_vectorPCSkillIDLevelYakGan.size() + iSizeDevGar;
			int iSizeETC    = (int)m_vectorPCSkillIDLevelEtc.size() + iSizeYakGan;

			if ( index >= 0 && index < iSizeNagKin )
			{
				*pid = m_vectorPCSkillIDLevelNagKin[index].iID;
				*pbyteLevel = m_vectorPCSkillIDLevelNagKin[index].byteLevel;
				return true;
			}
			else if ( index >= iSizeNagKin && index < iSizeAsuRak )
			{
				*pid = m_vectorPCSkillIDLevelAsuRak[index-iSizeNagKin].iID;
				*pbyteLevel = m_vectorPCSkillIDLevelAsuRak[index-iSizeNagKin].byteLevel;
				return true;
			}
			else if ( index >= iSizeAsuRak && index < iSizeDevGar )
			{
				*pid = m_vectorPCSkillIDLevelDevGar[index-iSizeAsuRak].iID;
				*pbyteLevel = m_vectorPCSkillIDLevelDevGar[index-iSizeAsuRak].byteLevel;
				return true;
			}
			else if ( index >= iSizeDevGar && index < iSizeYakGan )
			{
				*pid = m_vectorPCSkillIDLevelYakGan[index-iSizeDevGar].iID;
				*pbyteLevel = m_vectorPCSkillIDLevelYakGan[index-iSizeDevGar].byteLevel;
				return true;
			}
			else if ( index >= iSizeYakGan && index < iSizeETC )
			{
				*pid = m_vectorPCSkillIDLevelYakGan[index-iSizeDevGar].iID;
				*pbyteLevel = m_vectorPCSkillIDLevelYakGan[index-iSizeDevGar].byteLevel;
				return true;
			}
			else return false;
		} break;
	case HT_PARAMTYPE_ITEM :
		{
			int iSize = (int)m_vectorItemIDLevel.size();
			if ( index >= 0 && index < iSize )
			{
				*pid = m_vectorItemIDLevel[index].iID;
				*pbyteLevel = m_vectorItemIDLevel[index].byteLevel;
				return true;
			}
			else return false;
		} break;
	case HT_PARAMTYPE_NPC :
		{
			int iSize = (int)m_vectorNPCIDLevel.size();
			if ( index >= 0 && index < iSize )
			{
				*pid = m_vectorNPCIDLevel[index].iID;
				*pbyteLevel = m_vectorNPCIDLevel[index].byteLevel;
				return true;
			}
			else return false;
		} break;
	default : return false;	
	}
}

int
	CHTParameterMgr::HT_iGetPCSkillIDLevelCount( const int iCharType )
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
	CHTParameterMgr::HT_bGetPCSkillIDLevel( const int iCharType, const int index, int* pid, byte* pbyteLevel )
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
	CHTParameterMgr::HT_iGetPCSkillIDCount( const int iCharType )
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
	CHTParameterMgr::HT_bGetPCSkillIDByIndex( const int iCharType, const int index, int* pid )
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

int
	CHTParameterMgr::HT_iGetIndexForMoneyItem( const unsigned long dwMoney )
{
	int iIndex = 0;
	int iParam1 = 0, iParam2 = 0;
	for( iIndex = HT_PARAMTYPE_ITEM_USABLE_MONEY_START ; iIndex <= HT_PARAMTYPE_ITEM_USABLE_MONEY_END ; ++iIndex )
	{
		// √÷º“
		if( m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bGetItemEffect1Param1( iIndex, &iParam1 ) == false ) 
			break;
		// √÷¥Î
		if( m_arrParamTable[HT_PARAMTYPE_ITEM]->HT_bGetItemEffect1Param2( iIndex, &iParam2 ) == false ) 
			break;

		if( iParam1 == 0 && iParam2 == 0 )
			break;
		else if( (unsigned long)iParam1 <= dwMoney && ( dwMoney <= (unsigned long)iParam2 || iParam2 == -1 ) )	// -1¿∫ π´«—¥Î
			return iIndex;
	}

	return 0;
}

CHTBaseParamTable*
	CHTParameterMgr::HT_pGetParamTable( int id )
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
	else
	{
		return 0;
	}
}