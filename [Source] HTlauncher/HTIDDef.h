#ifndef _HTIDDEF_H_
#define _HTIDDEF_H_

// These Definitions must be same as client resource xml!

// ID
// 0001 ~ 0999 : Character
// 1001 ~ 1999 : NPC & Shop
// 2001 ~ 2999 : Monster
// 3001 ~ 3999 : Skill
// 4001 ~ 9990 : Item
// 9991 ~ 9999 : Material
// 10001 ~ 19999 : TMD model
// 20001 ~ 29999 : Texture
// 30001 ~ 39999 : Sound
// 40001 ~ 40999 : Map
// 50001 ~ 50999 : Animation
// 60001 ~ 60999 : FX Character
// 61001 ~ 61999 : FXMon
// 62001 ~ 62999 : FX Monster

//--------------------------------------------------------------------------

#define HT_ID_CHARACTER_NAGA		1
#define HT_ID_CHARACTER_ASURA		2
#define HT_ID_CHARACTER_YAKSA		3
#define HT_ID_CHARACTER_DEVA		4
#define HT_ID_CHARACTER_KIMNARA		5
#define HT_ID_CHARACTER_RAKSHASA	6
#define HT_ID_CHARACTER_GANDHARVA	7
#define HT_ID_CHARACTER_GARUDA		8
#define HT_ID_CHARACTER_GM			9

//--------------------------------------------------------------------------


#define HT_ID_MAP_MANDARA_1ST		40001
#define HT_ID_MAP_MANDARA_2ND		40002
#define HT_ID_MAP_UISELECT			40003

//--------------------------------------------------------------------------


#define HT_ID_MATERIAL_CHARACTER	9991
#define HT_ID_MATERIAL_TERRAIN		9992
#define HT_ID_MATERIAL_TREELEAF		9993
#define HT_ID_MATERIAL_TREEBRANCH	9994
#define HT_ID_MATERIAL_GRASS		9995
#define HT_ID_MATERIAL_STRUCTURE	9996
#define HT_ID_MATERIAL_ITEM			9997

//--------------------------------------------------------------------------

#define HT_ID_NPC_MAN_WEAPONMAKER	1101
#define HT_ID_NPC_MAN_CLOTHMAKER	1102
#define HT_ID_NPC_MAN_GOODSMAKER	1103
#define HT_ID_NPC_MAN_SHAMAN		1104
#define HT_ID_NPC_MAN_TRADER		1105
#define HT_ID_NPC_MAN_CONNECTOR		1106
#define HT_ID_NPC_MAN_RENTER		1107
#define HT_ID_NPC_MAN_CHIEFGUARD	1108
#define HT_ID_NPC_ANU_WEAPONMAKER	1109
#define HT_ID_NPC_ANU_CLOTHMAKER	1110
#define HT_ID_NPC_ANU_GOODSMAKER	1111
#define HT_ID_NPC_MAN_GUARD01		1001
#define HT_ID_NPC_MAN_GUARD02		1002
#define HT_ID_NPC_MAN_BOY01			1003
#define HT_ID_NPC_ANU_BOY01			1004
#define HT_ID_NPC_MAN_GIRL01		1005
#define HT_ID_NPC_ANU_GIRL01		1006

//--------------------------------------------------------------------------

#define HT_ID_MONSTER_RSABHA				2001
#define HT_ID_MONSTER_VASABHUM				2002
#define HT_ID_MONSTER_VARAHA				2003
#define HT_ID_MONSTER_RSABHARAJA			2004
#define HT_ID_MONSTER_VASABHUM_CAURA		2005
#define HT_ID_MONSTER_VARAHARAJA			2006
#define HT_ID_MONSTER_MLECCHAS				2007
#define HT_ID_MONSTER_ULKAMUKHA				2008
#define HT_ID_MONSTER_SRBINDA				2009
#define HT_ID_MONSTER_MLECCHAS_CAURA		2010
#define HT_ID_MONSTER_ULKAMUKHA_CAURA		2011
#define HT_ID_MONSTER_APRAH_RSABHARAJA		2012
#define HT_ID_MONSTER_VASABHUM_KULAPRA		2013
#define HT_ID_MONSTER_APRAH_VARAHARAJA		2014
#define HT_ID_MONSTER_ULKAMUKHA_SATVAN		2015
#define HT_ID_MONSTER_HERUKA				2016
#define HT_ID_MONSTER_ANANGA				2017
#define HT_ID_MONSTER_BALASTHA_DRBHIKA		2018
#define HT_ID_MONSTER_AZNA_HERUKA			2019
#define HT_ID_MONSTER_ANANGA_DHVANTA		2020
#define HT_ID_MONSTER_PIZACAGGANA			2021
#define HT_ID_MONSTER_GHORAYOGI				2022
#define HT_ID_MONSTER_KAULITARA				2023
#define HT_ID_MONSTER_NAGAMUDRA				2024
#define HT_ID_MONSTER_MLECCHAS_KARMANA		2025
#define HT_ID_MONSTER_ZARKU					2026
#define HT_ID_MONSTER_ZARKU_RUDHIRA			2027
#define HT_ID_MONSTER_ZRBINDA_SATVAN		2028
#define HT_ID_MONSTER_BALASTHA_TUNDELA		2029
#define HT_ID_MONSTER_MEGHAMALIN			2030


//--------------------------------------------------------------------------

#define HT_ID_CHARACTER_HEAD_START		101
#define HT_ID_CHARACTER_HEAD_END		199

#define HT_ID_CHARACTER_STATEANI_START	801
#define HT_ID_CHARACTER_STATEANI_END	899

#define HT_ID_CHARACTER_ATTACKANI_START	901
#define HT_ID_CHARACTER_ATTACKANI_END	999

#define HT_ID_NPC_START					1001
#define HT_ID_NPC_END					1999

#define HT_ID_MONSTER_START				2001
#define HT_ID_MONSTER_END				2999

#define HT_ID_ITEM_START				4001
#define HT_ID_ITEM_END					8999

//----------------------------

#define HT_ID_UP_WEAR_ITEM_START			9001
#define HT_ID_UP_WEAR_ITEM_END				9099

#define HT_ID_DOWN_WEAR_ITEM_START			9101
#define HT_ID_DOWN_WEAR_ITEM_END			9199

#define HT_ID_HAND_WEAR_ITEM_START			9201
#define HT_ID_HAND_WEAR_ITEM_END			9299

#define HT_ID_SHOES_ITEM_START				9301
#define HT_ID_SHOES_ITEM_END				9399

//----------------------------
#define HT_ID_FOOT_SOUND_START			28301
#define HT_ID_FOOT_SOUND_END			28350

#define HT_ID_ITEM_REFINING_START		29001
#define HT_ID_ITEM_REFINING_END			29099

#define HT_ID_CHARACTER_TMD_START		10001
#define HT_ID_CHARACTER_TMD_END			10300

#define HT_ID_CHARACTERMESH_TMD_START	10301
#define HT_ID_CHARACTERMESH_TMD_END		10999

#define HT_ID_NPC_TMD_START				11001
#define HT_ID_NPC_TMD_END				11999

#define HT_ID_MONSTER_TMD_START			12001
#define HT_ID_MONSTER_TMD_END			12999

#define HT_ID_MONSTER_TEX_START			13001
#define HT_ID_MONSTER_TEX_END			13999

#define HT_ID_ITEM_TMD_START			14001
#define HT_ID_ITEM_TMD_END				14999

#define HT_ID_OBJS_TMD_START			18001
#define HT_ID_OBJS_TMD_END				19999

#define HT_ID_SMOBJS_TMD_START			19001
#define HT_ID_SMOBJS_TMD_END			19899

#define HT_ID_GRASS_TMD_START			19900
#define HT_ID_GRASS_TMD_END				19999

#define HT_ID_CHARACTER_TEX_START		20001
#define HT_ID_CHARACTER_TEX_END			21999

#define HT_ID_UI_INTRO_START			27001
#define HT_ID_UI_INTRO_END				27999

//====================================================================================
// 새로운UI수정(20030728)
//====================================================================================		
//#define HT_ID_UI_MAIN_START				23101
#define HT_ID_UI_MAIN_START				22101
#define HT_ID_UI_MAIN_END				23899

#define HT_ID_UI_3DSPR_START			23901
#define HT_ID_UI_3DSPR_END				23999

#define HT_ID_ITEM_TEX_START			24001
#define HT_ID_ITEM_TEX_END				24999

#define HT_ID_FX_TEX_START				25001
#define HT_ID_FX_TEX_END				25999

#define HT_ID_ETC_TEX_START				26001
#define HT_ID_ETC_TEX_END				26999

//====================================================================================
// 길드 마크를 위한 텍스쳐와 색
//====================================================================================
// 길드 마크 배경 텍스쳐
#define HT_ID_GUILDMARK_BACK_START		28001
#define HT_ID_GUILDMARK_BACK_END		28199
// 길드 마크 문양 텍스쳐
#define HT_ID_GUILDMARK_EMBLEM_START	28401
#define HT_ID_GUILDMARK_EMBLEM_END		28599
// 길드 마크 가운데 글자의 텍스쳐
#define HT_ID_GUILDMARK_TITLE_START		28601
#define HT_ID_GUILDMARK_TITLE_END		28799
// 길드 마크 문양의 색
#define HT_ID_GUILDMARK_COLOR_START		28801
#define HT_ID_GUILDMARK_COLOR_END		28999

//====================================================================================
// 지역표시를 위한 지역이름
//====================================================================================
#define HT_ID_AREAINDICATE_START		28201
#define HT_ID_AREAINDICATE_END			28300
//====================================================================================

#define HT_ID_BGM_START					30001
#define HT_ID_BGM_END					30999

#define HT_ID_PCSOUND_START				31009
#define HT_ID_PCSOUND_END				31309

#define HT_ID_NPCSOUND_START			31310
#define HT_ID_NPCSOUND_END				31999

#define HT_ID_MONSTERSOUND_START		32001
#define HT_ID_MONSTERSOUND_END			32999

#define HT_ID_ITEMSOUND_START			33001
#define HT_ID_ITEMSOUND_END				33499

#define HT_ID_ETCSOUND_START			33501
#define HT_ID_ETCSOUND_END				33599

#define HT_ID_MAP_START					40001
#define HT_ID_MAP_END					40999

#define HT_ID_CHARACTER_ANI_START		50001
#define HT_ID_CHARACTER_ANI_END			51799

#define HT_ID_NPC_ANI_START				51801
#define HT_ID_NPC_ANI_END				51999

#define HT_ID_MONSTER_ANI_START			52001
#define HT_ID_MONSTER_ANI_END			53999

#define HT_ID_FXMON_START				61001
#define HT_ID_FXMON_END					61999

//--------------------------------------------------------------------------

#define HT_ID_CHARACTER_UP_WEAR_START		71001
#define HT_ID_CHARACTER_UP_WEAR_END			71999

#define HT_ID_CHARACTER_DOWN_WEAR_START		72001
#define HT_ID_CHARACTER_DOWN_WEAR_END		72999

#define HT_ID_CHARACTER_HAND_WEAR_START		73001
#define HT_ID_CHARACTER_HAND_WEAR_END		73999

#define HT_ID_CHARACTER_SHOES_START			74001
#define HT_ID_CHARACTER_SHOES_END			74999
//--------------------------------------------------------------------------

#define HT_ID_PORTAL_START					75001
#define HT_ID_PORTAL_END					75999



#define HT_RES_TABLENAME_CHARACTER		_T("PC")
#define HT_RES_TABLENAME_HEAD			_T("Head")
//#define HT_RES_TABLENAME_WEAR			_T("Wear")
#define HT_RES_TABLENAME_UP_WEAR		_T("UpWear")
#define HT_RES_TABLENAME_DOWN_WEAR		_T("DownWear")
#define HT_RES_TABLENAME_HAND_WEAR		_T("HandWear")
#define HT_RES_TABLENAME_SHOES			_T("Shoes")
#define HT_RES_TABLENAME_PCSTATEANI		_T("PCStateAni")
#define HT_RES_TABLENAME_PCATTACKANI	_T("PCAttackAni")
#define HT_RES_TABLENAME_PCANI			_T("PCAni")
#define HT_RES_TABLENAME_PCTMD			_T("PCTMD")
#define HT_RES_TABLENAME_PCMESH			_T("PCMesh")
#define HT_RES_TABLENAME_PCTEX			_T("PCTex")
//#define HT_RES_TABLENAME_WEARITEM		_T("WearItem")
#define HT_RES_TABLENAME_UP_WEARITEM	_T("UpWearItem")
#define HT_RES_TABLENAME_DOWN_WEARITEM	_T("DownWearItem")
#define HT_RES_TABLENAME_HAND_WEARITEM	_T("HandWearItem")
#define HT_RES_TABLENAME_SHOESITEM		_T("ShoesItem")
#define HT_RES_TABLENAME_MAP			_T("Map")
#define HT_RES_TABLENAME_MATERIAL		_T("Material")
#define HT_RES_TABLENAME_NPC			_T("NPC")
#define HT_RES_TABLENAME_MONSTER		_T("Monster")
#define HT_RES_TABLENAME_NPCTMD			_T("NPCTMD")
#define HT_RES_TABLENAME_MONTMD			_T("MonTMD")
#define HT_RES_TABLENAME_MONTEX			_T("MonTex")
#define HT_RES_TABLENAME_NPCANI			_T("NPCAni")
#define HT_RES_TABLENAME_MONANI			_T("MonAni")
#define HT_RES_TABLENAME_ITEM			_T("Item")
#define HT_RES_TABLENAME_ITEMTMD		_T("ItemTMD")
#define HT_RES_TABLENAME_ITEMTEX		_T("ItemTex")
#define HT_RES_TABLENAME_BGM			_T("BGM")
#define HT_RES_TABLENAME_OBJTMD			_T("Objs")
#define HT_RES_TABLENAME_UIINTRO		_T("IntroUI")
#define HT_RES_TABLENAME_UIMAIN			_T("MainUI")
#define HT_RES_TABLENAME_UIPUB			_T("PubUI")
#define HT_RES_TABLENAME_ETCTEX			_T("ETC")
#define HT_RES_TABLENAME_FXMON			_T("FXMon")
#define HT_RES_TABLENAME_3DSPR			_T("3DSpr")
#define HT_RES_TABLENAME_PCSOUND		_T("PCSound")
#define HT_RES_TABLENAME_NPCSOUND		_T("NPCSound")
#define HT_RES_TABLENAME_MONSTERSOUND	_T("MonSound")
#define HT_RES_TABLENAME_ITEMSOUND		_T("ItemSound")
#define HT_RES_TABLENAME_ETCSOUND		_T("ETCSound")
#define HT_RES_TABLENAME_GUILDMARK_BACK		_T("GuildMarkBackTex")
#define HT_RES_TABLENAME_GUILDMARK_EMBLEM	_T("GuildMarkEmblemTex")
#define HT_RES_TABLENAME_GUILDMARK_TITLE	_T("GuildMarkTitleTex")
#define HT_RES_TABLENAME_GUILDMARK_COLOR	_T("GuildMarkColor")
#define HT_RES_TABLENAME_AREA_INDICATE		_T("AreaIndicate")// 지역표시
#define HT_RES_TABLENAME_ITEMREFINING		_T("ItemRefining")
#define HT_RES_TABLENAME_FOOTSOUND		_T("FootSound")
#define HT_RES_TABLENAME_PORTAL			_T("Portal")
//--------------------------------------------------------------------------

#define HT_IS_CHARACTER( i )			( i >= HT_ID_CHARACTER_NAGA ) && ( i <= HT_ID_CHARACTER_GM ) ? HT_TRUE : HT_FALSE
#define HT_IS_NPC( i )					( i >= HT_ID_NPC_START ) && ( i <= HT_ID_NPC_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MONSTER( i )				( i >= HT_ID_MONSTER_START ) && ( i <= HT_ID_MONSTER_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_HEAD( i )					( i >= HT_ID_CHARACTER_HEAD_START ) && ( i <= HT_ID_CHARACTER_HEAD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_UP_WEAR( i )				( i >= HT_ID_CHARACTER_UP_WEAR_START ) && ( i <= HT_ID_CHARACTER_UP_WEAR_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DOWN_WEAR( i )			( i >= HT_ID_CHARACTER_DOWN_WEAR_START ) && ( i <= HT_ID_CHARACTER_DOWN_WEAR_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_HAND_WEAR( i )			( i >= HT_ID_CHARACTER_HAND_WEAR_START ) && ( i <= HT_ID_CHARACTER_HAND_WEAR_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SHOES( i )				( i >= HT_ID_CHARACTER_SHOES_START ) && ( i <= HT_ID_CHARACTER_SHOES_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MAP( i )					( i >= HT_ID_MAP_START ) && ( i <= HT_ID_MAP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MATERIAL( i )				( i >= HT_ID_MATERIAL_CHARACTER ) && ( i <= HT_ID_MATERIAL_ITEM ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERSTATEANI( i )	( i >= HT_ID_CHARACTER_STATEANI_START ) && ( i <= HT_ID_CHARACTER_STATEANI_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERATTACKANI( i )	( i >= HT_ID_CHARACTER_ATTACKANI_START ) && ( i <= HT_ID_CHARACTER_ATTACKANI_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERANI( i )			( i >= HT_ID_CHARACTER_ANI_START ) && ( i <= HT_ID_CHARACTER_ANI_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERTMD( i )			( i >= HT_ID_CHARACTER_TMD_START ) && ( i <= HT_ID_CHARACTER_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERMESHTMD( i )		( i >= HT_ID_CHARACTERMESH_TMD_START ) && ( i <= HT_ID_CHARACTERMESH_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHARACTERTEX( i )			( i >= HT_ID_CHARACTER_TEX_START ) && ( i <= HT_ID_CHARACTER_TEX_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_UPWEARITEM( i )			( i >= HT_ID_UP_WEAR_ITEM_START ) && ( i <= HT_ID_UP_WEAR_ITEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DOWNWEARITEM( i )			( i >= HT_ID_DOWN_WEAR_ITEM_START ) && ( i <= HT_ID_DOWN_WEAR_ITEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_HANDWEARITEM( i )			( i >= HT_ID_HAND_WEAR_ITEM_START ) && ( i <= HT_ID_HAND_WEAR_ITEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SHOESITEM( i )			( i >= HT_ID_SHOES_ITEM_START ) && ( i <= HT_ID_SHOES_ITEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM( i )					( i >= HT_ID_ITEM_START ) && ( i <= HT_ID_ITEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_TMD( i )				( i >= HT_ID_ITEM_TMD_START ) && ( i <= HT_ID_ITEM_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_TEX( i )				( i >= HT_ID_ITEM_TEX_START ) && ( i <= HT_ID_ITEM_TEX_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_OBJS( i )					( i >= HT_ID_OBJS_TMD_START ) && ( i <= HT_ID_OBJS_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_NPC_TMD( i )				( i >= HT_ID_NPC_TMD_START ) && ( i <= HT_ID_NPC_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MONSTER_TMD( i )			( i >= HT_ID_MONSTER_TMD_START ) && ( i <= HT_ID_MONSTER_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MONSTER_TEX( i )			( i >= HT_ID_MONSTER_TEX_START ) && ( i <= HT_ID_MONSTER_TEX_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_NPC_ANI( i )				( i >= HT_ID_NPC_ANI_START ) && ( i <= HT_ID_NPC_ANI_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MONSTER_ANI( i )			( i >= HT_ID_MONSTER_ANI_START ) && ( i <= HT_ID_MONSTER_ANI_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BGM( i )					( i >= HT_ID_BGM_START ) && ( i <= HT_ID_BGM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_UIINTRO( i )				( i >= HT_ID_UI_INTRO_START ) && ( i <= HT_ID_UI_INTRO_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_UIMAIN( i )				( i >= HT_ID_UI_MAIN_START ) && ( i <= HT_ID_UI_MAIN_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETC( i )					( i >= HT_ID_ETC_TEX_START ) && ( i <= HT_ID_ETC_TEX_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_3DSPR( i )				( i >= HT_ID_UI_3DSPR_START ) && ( i <= HT_ID_UI_3DSPR_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_FXMON( i )				( i >= HT_ID_FXMON_START ) && ( i <= HT_ID_FXMON_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_PC_MAN( i )				( i >= HT_ID_CHARACTER_NAGA ) && ( i <= HT_ID_CHARACTER_DEVA ) ? HT_TRUE : HT_FALSE
#define HT_IS_PCSOUND( i )				( i >= HT_ID_PCSOUND_START ) && ( i <= HT_ID_PCSOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_NPCSOUND( i )				( i >= HT_ID_NPCSOUND_START ) && ( i <= HT_ID_NPCSOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEMSOUND( i )			( i >= HT_ID_ITEMSOUND_START ) && ( i <= HT_ID_ITEMSOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_MONSTERSOUND( i )			( i >= HT_ID_MONSTERSOUND_START ) && ( i <= HT_ID_MONSTERSOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETCSOUND( i )				( i >= HT_ID_ETCSOUND_START ) && ( i <= HT_ID_ETCSOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GUILDMARK_BACK( i )		( i >= HT_ID_GUILDMARK_BACK_START ) && ( i <= HT_ID_GUILDMARK_BACK_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GUILDMARK_EMBLEM( i )		( i >= HT_ID_GUILDMARK_EMBLEM_START ) && ( i <= HT_ID_GUILDMARK_EMBLEM_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GUILDMARK_TITLE( i )		( i >= HT_ID_GUILDMARK_TITLE_START ) && ( i <= HT_ID_GUILDMARK_TITLE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GUILDMARK_COLOR( i )		( i >= HT_ID_GUILDMARK_COLOR_START ) && ( i <= HT_ID_GUILDMARK_COLOR_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_AREA_INDICATE( i )		( i >= HT_ID_AREAINDICATE_START ) && ( i <= HT_ID_AREAINDICATE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_RIFINING( i )		( i >= HT_ID_ITEM_REFINING_START ) && ( i <= HT_ID_ITEM_REFINING_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_FOOT_SOUND( i )			( i >= HT_ID_FOOT_SOUND_START ) && ( i <= HT_ID_FOOT_SOUND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_PORTAL( i )				( i >= HT_ID_PORTAL_START ) && ( i <= HT_ID_PORTAL_END ) ? HT_TRUE : HT_FALSE




//-------------------------------------------------------------------------
// item def
//	화살
#define HT_ITEM_ARROW_MODELID				7091

#define HT_ID_ITEM_SWORD_START				4001
#define HT_ID_ITEM_MAGICWAND_TWOHAND_END	5999
#define HT_ID_ITEM_WEAR_SOFT_START			6001
#define HT_ID_ITEM_WEAR_HEAVY_END			6299
#define HT_ID_ITEM_GLOVE_START				5001
#define HT_ID_ITEM_GLOVE_END				5099
#define HT_ID_ITEM_DART_START				5101
#define HT_ID_ITEM_DART_END					5199
#define HT_ID_ITEM_HAT_START				6501
#define HT_ID_ITEM_HAT_END					6599
#define HT_ID_ITEM_SHIELD_START				6301
#define HT_ID_ITEM_SHIELD_END				6399
#define HT_ID_ITEM_SHOES_START				6601
#define HT_ID_ITEM_SHOES_END				6699
#define HT_ID_ITEM_ARROW_START				4601
#define HT_ID_ITEM_ARROW_END				4653

#define HT_ID_NPC_MONSTER_START				2000
#define HT_ID_NPC_MONSTER_END				3000

//#define HT_IS_ITEM_WEAPON(i)			( i >= HT_ID_ITEM_SWORD_START ) && ( i <= HT_ID_ITEM_MAGICWAND_TWOHAND_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_WEAPON(i)			( g_pEngineHandler->HT_bIsWeapon(i) ) ? HT_TRUE : HT_FALSE
//#define HT_IS_ITEM_WEAR(i)				( i >= HT_ID_ITEM_WEAR_SOFT_START ) && ( i <= HT_ID_ITEM_WEAR_HEAVY_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_WEAR(i)			( g_pEngineHandler->HT_bIsWearItem(i) ) ? HT_TRUE : HT_FALSE

//#define HT_IS_ITEM_GLOVE(i)			( i >= HT_ID_ITEM_GLOVE_START ) && ( i <= HT_ID_ITEM_GLOVE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_GLOVE(i)			( g_pEngineHandler->HT_bIsGloveItem(i) ) ? HT_TRUE : HT_FALSE
//#define HT_IS_ITEM_DART(i)			( i >= HT_ID_ITEM_DART_START ) && ( i <= HT_ID_ITEM_DART_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_DART(i)			( g_pEngineHandler->HT_bIsDartItem(i) ) ? HT_TRUE : HT_FALSE
//#define HT_IS_ITEM_HAT(i)			( i >= HT_ID_ITEM_HAT_START ) && ( i <= HT_ID_ITEM_HAT_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_HAT(i)			( g_pEngineHandler->HT_bIsHatItem(i) ) ? HT_TRUE : HT_FALSE
//#define HT_IS_ITEM_SHIELD(i)		( i >= HT_ID_ITEM_SHIELD_START ) && ( i <= HT_ID_ITEM_SHIELD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_SHIELD(i)			( g_pEngineHandler->HT_bIsShieldItem(i) ) ? HT_TRUE : HT_FALSE
//#define HT_IS_ITEM_SHOES(i)			( i >= HT_ID_ITEM_SHOES_START ) && ( i <= HT_ID_ITEM_SHOES_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_SHOES(i)			( g_pEngineHandler->HT_bIsShoesItem(i) ) ? HT_TRUE : HT_FALSE
#define HT_IS_ITEM_ARROW(i)			( i >= HT_ID_ITEM_ARROW_START ) && ( i <= HT_ID_ITEM_ARROW_END ) ? HT_TRUE : HT_FALSE

#define HT_IS_NPC_MONSTER(i)		( i >= HT_ID_NPC_MONSTER_START ) && ( i <= HT_ID_NPC_MONSTER_END ) ? HT_TRUE : HT_FALSE

#define HT_IS_GRASS(i)				( i >= HT_ID_GRASS_TMD_START ) && ( i <= HT_ID_GRASS_TMD_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SMOBJ(i)				( i >= HT_ID_SMOBJS_TMD_START ) && ( i <= HT_ID_SMOBJS_TMD_END ) ? HT_TRUE : HT_FALSE

//-------------------------------------------------------------------------
// item def
#define HT_ID_SKILL_START				3001
#define HT_ID_SKILL_END					3310

#define HT_IS_SKIL(i)					( i >= HT_ID_SKILL_START ) && ( i <= HT_ID_SKILL_END ) ? HT_TRUE : HT_FALSE

//-------------------------------------------------------------------------
// 아래의 정의들은 내부적으로만 쓰이는 것들이다.
#define HT_HEAD_TYPE_A					1
#define HT_HEAD_TYPE_B					2
#define HT_HEAD_TYPE_C					3
#define HT_HEAD_TYPE_D					4
#define HT_HEAD_TYPE_E					5
#define HT_HEAD_TYPE_F					6
#define HT_HEAD_TYPE_G					7
#define HT_HEAD_TYPE_H					8

// TODO : 메쉬 타입이 추가될때마다 이부분을 업데이트 해줘야 한다.
// 너무 바보 같으나 생각이 없다.
#define HT_MESH_WEAR_TYPE_A_FACE		"TypeA_Face"
#define HT_MESH_WEAR_TYPE_A_CHEST		"TypeA_Chest"
#define HT_MESH_WEAR_TYPE_A_PANTS		"TypeA_Pants"
#define HT_MESH_WEAR_TYPE_A_RUARM		"TypeA_RUArm"
#define HT_MESH_WEAR_TYPE_A_LUARM		"TypeA_LUArm"
#define HT_MESH_WEAR_TYPE_A_RLARM		"TypeA_RLArm"
#define HT_MESH_WEAR_TYPE_A_LLARM		"TypeA_LLArm"
#define HT_MESH_WEAR_TYPE_A_RBOOTS		"TypeA_RBoots"
#define HT_MESH_WEAR_TYPE_A_LBOOTS		"TypeA_LBoots"
#define HT_MESH_WEAR_TYPE_B_FACE		"TypeB_Face"
#define HT_MESH_WEAR_TYPE_B_CHEST		"TypeB_Chest"
#define HT_MESH_WEAR_TYPE_B_PANTS		"TypeB_Pants"
#define HT_MESH_WEAR_TYPE_B_RUARM		"TypeB_RUArm"
#define HT_MESH_WEAR_TYPE_B_LUARM		"TypeB_LUArm"
#define HT_MESH_WEAR_TYPE_B_RLARM		"TypeB_RLArm"
#define HT_MESH_WEAR_TYPE_B_LLARM		"TypeB_LLArm"
#define HT_MESH_WEAR_TYPE_B_RBOOTS		"TypeB_RBoots"
#define HT_MESH_WEAR_TYPE_B_LBOOTS		"TypeB_LBoots"
#define HT_MESH_WEAR_TYPE_C_FACE		"TypeC_Face"
#define HT_MESH_WEAR_TYPE_C_CHEST		"TypeC_Chest"
#define HT_MESH_WEAR_TYPE_C_PANTS		"TypeC_Pants"
#define HT_MESH_WEAR_TYPE_C_RUARM		"TypeC_RUArm"
#define HT_MESH_WEAR_TYPE_C_LUARM		"TypeC_LUArm"
#define HT_MESH_WEAR_TYPE_C_RLARM		"TypeC_RLArm"
#define HT_MESH_WEAR_TYPE_C_LLARM		"TypeC_LLArm"
#define HT_MESH_WEAR_TYPE_C_RBOOTS		"TypeC_RBoots"
#define HT_MESH_WEAR_TYPE_C_LBOOTS		"TypeC_LBoots"
#define HT_MESH_WEAR_TYPE_D_FACE		"TypeD_Face"
#define HT_MESH_WEAR_TYPE_D_CHEST		"TypeD_Chest"
#define HT_MESH_WEAR_TYPE_D_PANTS		"TypeD_Pants"
#define HT_MESH_WEAR_TYPE_D_RUARM		"TypeD_RUArm"
#define HT_MESH_WEAR_TYPE_D_LUARM		"TypeD_LUArm"
#define HT_MESH_WEAR_TYPE_D_RLARM		"TypeD_RLArm"
#define HT_MESH_WEAR_TYPE_D_LLARM		"TypeD_LLArm"
#define HT_MESH_WEAR_TYPE_D_RBOOTS		"TypeD_RBoots"
#define HT_MESH_WEAR_TYPE_D_LBOOTS		"TypeD_LBoots"

#define HT_MESH_WEAR_TYPE_A_RHAND		"TypeA_RHand"
#define HT_MESH_WEAR_TYPE_A_LHAND		"TypeA_LHand"
#define HT_MESH_WEAR_TYPE_B_RHAND		"TypeB_RHand"
#define HT_MESH_WEAR_TYPE_B_LHAND		"TypeB_LHand"
#define HT_MESH_WEAR_TYPE_C_RHAND		"TypeC_RHand"
#define HT_MESH_WEAR_TYPE_C_LHAND		"TypeC_LHand"
#define HT_MESH_WEAR_TYPE_D_RHAND		"TypeD_RHand"
#define HT_MESH_WEAR_TYPE_D_LHAND		"TypeD_LHand"

#define HT_MESH_WEAR_TYPE_A_SKIRT		"TypeA_Skirt"
#define HT_MESH_WEAR_TYPE_B_SKIRT		"TypeB_Skirt"
#define HT_MESH_WEAR_TYPE_F_PANTS		"TypeF_Pants"
#define HT_MESH_WEAR_TYPE_G_PANTS		"TypeG_Pants"

#define HT_MESH_WEAR_TYPE_E_FACE		"TypeE_Face"

//-------------------------------------------------------------------------

enum HT_ANIM_STATE
{
	HT_ANISTATE_STD				= 801,		// PC / NPC / MONSTER
	HT_ANISTATE_WLK				= 802,		// PC / NPC / MONSTER
	HT_ANISTATE_RUN				= 803,		// PC / NPC / MONSTER
	HT_ANISTATE_IDL				= 804,		// PC / NPC / MONSTER
	HT_ANISTATE_SIT				= 805,		// PC

	HT_ANISTATE_ATK_STD_S1H		= 806,		// PC
	HT_ANISTATE_ATK_STD_S2H		= 807,		// PC
	HT_ANISTATE_ATK_STD_SPR		= 808,		// PC
	HT_ANISTATE_ATK_STD_AXE		= 809,		// PC
	HT_ANISTATE_ATK_STD_FIST	= 825,		// PC

	HT_ANISTATE_ATK_WLK_S1H		= 810,		// PC
	HT_ANISTATE_ATK_WLK_S2H		= 811,		// PC
	HT_ANISTATE_ATK_WLK_SPR		= 812,		// PC
	HT_ANISTATE_ATK_WLK_AXE		= 813,		// PC

	HT_ANISTATE_ATK_RUN_S1H		= 814,		// PC
	HT_ANISTATE_ATK_RUN_S2H		= 815,		// PC
	HT_ANISTATE_ATK_RUN_SPR		= 816,		// PC
	HT_ANISTATE_ATK_RUN_AXE		= 817,		// PC

	HT_ANISTATE_HIT_S1H			= 818,		// PC
	HT_ANISTATE_HIT_S2H			= 819,		// PC
	HT_ANISTATE_HIT_SPR			= 820,		// PC
	HT_ANISTATE_HIT_AXE			= 821,		// PC
	HT_ANISTATE_HIT_FIST		= 826,		// PC

	HT_ANISTATE_DIE				= 822,		// PC / NPC / MONSTER
	HT_ANISTATE_SITDOWN			= 823,		// PC
	HT_ANISTATE_STANDUP			= 824,		// PC

	HT_ANISTATE_HIT				= 841,		// PC / MONSTER
	HT_ANISTATE_ATK_1			= 842,		// PC / MONSTER
	HT_ANISTATE_ATK_2			= 843,		// PC / MONSTER
	HT_ANISTATE_ATK_3			= 844,		// PC

	HT_ANISTATE_MAGIC_DEFENCE	= 851,		// PC
	HT_ANISTATE_MAGIC_HEAL		= 852,		// PC

	HT_ANISTATE_EMO_BOW			= 831,		// PC EMO, Bow, 인사
	HT_ANISTATE_EMO_CHARGE		= 832,		// PC EMO, Charge, 돌격
	HT_ANISTATE_EMO_PROVOKE		= 833,		// PC EMO, Provoke, 도발
};

// PC 전용 공격 동작
enum HT_ATTACKANIM_STATE
{
	HT_ANISTATE_ATK_IRON_ONEHAND_SWORD			= 901,
	HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD		= 902,
	HT_ANISTATE_ATK_IRON_ONEHAND_AXE			= 903,
	HT_ANISTATE_ATK_IRON_ONEHAND_MACE			= 904,
	HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON	= 905,
	HT_ANISTATE_ATK_IRON_TWOHAND_SPEAR			= 906,
	HT_ANISTATE_ATK_IRON_TWOHAND_AXE			= 907,
	HT_ANISTATE_ATK_IRON_TWOHAND_MACE			= 908,
	HT_ANISTATE_ATK_IRON_TWOHAND_SWORD			= 909,
	HT_ANISTATE_ATK_IRON_THROWING_WEAPON		= 910,
	HT_ANISTATE_ATK_WOOD_STAFF					= 911,
	HT_ANISTATE_ATK_IRON_MATIALART_WEAPON		= 913,
	HT_ANISTATE_ATK_IRON_TWOHAND_MOONSWORD		= 914,
	HT_ANISTATE_ATK_BOW							= 915,
	HT_ANISTATE_ATK_DOUBLEWEAPON				= 916,

	HT_ANISTATE_ATK_END							= 999,
};

#define HT_FX_TIME_ALWAYS		0
#define HT_FX_TIME_DAY			1
#define HT_FX_TIME_NIGHT		2

#define HT_NULL_MODEL_ID		99001

#define HT_SWORDWINDBUFFER_ID			1000000
#define HT_RTSHADOWTEXTUREIDBUFFER_ID	2000000
#define HT_SPRITESYSTEMBUFFER_ID		3000000
#define HT_FXSPRITEBUFFER_ID			4000000

#define HT_MINIMAP_BMP_ID			99002		
#define HT_MINIMAP_VILLAGE_BMP_ID	99003	

#define HT_GODMARK_MODEL_BRAHMA	10223
#define HT_GODMARK_MODEL_SIVA	10224
#define HT_GODMARK_MODEL_VISUNU	10225
#define HT_GODMARK_SIVA_TEX		_T("Lord_Siva.dds")
#define HT_GODMARK_BRAHMA_TEX	_T("Lord_Brah.dds")
#define HT_GODMARK_VISUNU_TEX	_T("Lord_Visn.dds")

enum HTEGodType
{
	HT_GODTYPE_SIVA = 1,
	HT_GODTYPE_BRAHMA = 2,
	HT_GODTYPE_VISUNU = 3,
};

#endif // #ifndef _HTIDDEF_H_