//----------------------------------------------------------------------------//
//	���� �̸�	: HTControlDef.h
//
//	���� ���� 	: 
//		- ������ �������� ��Ʈ�ѿ� ���� ������ �������� �����Ѵ�.
//
//	�ۼ���		:
//		- 2002/05/17, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
#ifndef _HTCONTROLDEF_H_
#define _HTCONTROLDEF_H_

#include "Basedef.h"
#include "HTUIIDDef.h"

#define HT_ConvertTribeS2C( iServerID, iClientID ) \
{ \
	switch ( (iServerID) ) \
	{ \
	case TRIBE_NAGA :		(iClientID) = 1; break; \
	case TRIBE_KINNARA :	(iClientID) = 5; break; \
	case TRIBE_ASURA :		(iClientID) = 2; break; \
	case TRIBE_RAKSHASA :	(iClientID) = 6; break; \
	case TRIBE_YAKSA :		(iClientID) = 3; break; \
	case TRIBE_GANDHARVA :	(iClientID) = 7; break; \
	case TRIBE_DEVA	:		(iClientID) = 4; break; \
	case TRIBE_GARUDA :		(iClientID) = 8; break; \
	case 0 :				(iClientID) = 9; break; \
	default :				(iClientID) = 0; \
	} \
}


#pragma pack(push, 1)

/*----------------------------------------------------------------------------*/
// ��Ʈ ���꿡 ����Ѵ�.
/*----------------------------------------------------------------------------*/
#define		BIT_AND(value1, value2)	((value1) & (value2))
#define		BIT_OR(value1, value2)	((value1) | (value2))

/*----------------------------------------------------------------------------*/
// �ֽ�
/*----------------------------------------------------------------------------*/
//#define		TRIMURITI_NONE		0//0x00	// �ֽ� ���� ����
//#define		TRIMURITI_BRAHMA	1//0x01	// ����帶
//#define		TRIMURITI_VISHNU	2//0x02	// �񽴴�
//#define		TRIMURITI_SIVA		4//0x03	// �ù�

/*----------------------------------------------------------------------------*/
// ī��Ʈ ���, ���
/*----------------------------------------------------------------------------*/
#define _CHARAC_CAST_NONE			0
#define _CHARAC_CAST_SUDRA_3		1
#define _CHARAC_CAST_SUDRA_3_START		0	
#define _CHARAC_CAST_SUDRA_3_END		2000
#define _CHARAC_CAST_SUDRA_2		2
#define _CHARAC_CAST_SUDRA_2_START		2001
#define _CHARAC_CAST_SUDRA_2_END		5000
#define _CHARAC_CAST_SUDRA_1		3
#define _CHARAC_CAST_SUDRA_1_START		5001
#define _CHARAC_CAST_SUDRA_1_END		10000
#define _CHARAC_CAST_VAISHA_3		4
#define _CHARAC_CAST_VAISHA_3_START		10001
#define _CHARAC_CAST_VAISHA_3_END		20000
#define _CHARAC_CAST_VAISHA_2		5
#define _CHARAC_CAST_VAISHA_2_START		20001
#define _CHARAC_CAST_VAISHA_2_END		35000
#define _CHARAC_CAST_VAISHA_1		6
#define _CHARAC_CAST_VAISHA_1_START		35001
#define _CHARAC_CAST_VAISHA_1_END		55000
#define _CHARAC_CAST_KSHATRYA_3		7
#define _CHARAC_CAST_KSHATRYA_3_START	55001
#define _CHARAC_CAST_KSHATRYA_3_END		85000
#define _CHARAC_CAST_KSHATRYA_2		8
#define _CHARAC_CAST_KSHATRYA_2_START	85001
#define _CHARAC_CAST_KSHATRYA_2_END		120000
#define _CHARAC_CAST_KSHATRYA_1		9
#define _CHARAC_CAST_KSHATRYA_1_START	120001
#define _CHARAC_CAST_KSHATRYA_1_END		160000
#define _CHARAC_CAST_BRAMAN_3		10
#define _CHARAC_CAST_BRAMAN_3_START		160001
#define _CHARAC_CAST_BRAMAN_3_END		205000
#define _CHARAC_CAST_BRAMAN_2		11
#define _CHARAC_CAST_BRAMAN_2_START		205001
#define _CHARAC_CAST_BRAMAN_2_END		255000
#define _CHARAC_CAST_BRAMAN_1		12
#define _CHARAC_CAST_BRAMAN_1_START		255001
#define _CHARAC_CAST_BRAMAN_1_END		320000
#define	_CHARAC_CAST_AVATARA_3		13
#define	_CHARAC_CAST_AVATARA_3_START	320001
#define	_CHARAC_CAST_AVATARA_3_END		400000
#define	_CHARAC_CAST_AVATARA_2		14
#define	_CHARAC_CAST_AVATARA_2_START	400001
#define	_CHARAC_CAST_AVATARA_2_END		500000
#define	_CHARAC_CAST_AVATARA_1		15
#define	_CHARAC_CAST_AVATARA_1_START	500001
#define	_CHARAC_CAST_AVATARA_1_END		650000
#define	_CHARAC_CAST_RESERVE_3		16
#define	_CHARAC_CAST_RESERVE_3_START	650001
#define	_CHARAC_CAST_RESERVE_3_END		950000
#define	_CHARAC_CAST_RESERVE_2		17
#define	_CHARAC_CAST_RESERVE_2_START	950001
#define	_CHARAC_CAST_RESERVE_2_END		1400000	
#define	_CHARAC_CAST_RESERVE_1		18
#define	_CHARAC_CAST_RESERVE_1_START	1400001
#define	_CHARAC_CAST_RESERVE_1_END		2000000
//-----------------------------------------------------------------------------

//	Ʃ�丮�� �ý���
#define TUTORIAL_STEP_NONE						0
#define TUTORIAL_STEP_FIRSTGREETINGS			1
#define TUTORIAL_STEP_RUNANDWALK				2
#define TUTORIAL_STEP_VIEWPOINTTRANS			3
#define TUTORIAL_STEP_SHOWMAPINFO				4
#define TUTORIAL_STEP_GETITEM					5
#define TUTORIAL_STEP_HUNTINGMONSTER			6
#define TUTORIAL_STEP_SITANDSTAND				7
#define TUTORIAL_STEP_SHOWCHARINFO				8
#define TUTORIAL_STEP_SHOWSKILLINFO				9
#define TUTORIAL_STEP_ENDGREETINGS				10
#define TUTORIAL_STEP_MENUSELECT				11
#define TUTORIAL_STEP_REDUCTIONKEY				101

//-----------------------------------------------------------------------------//
//  ���� : Remove MOB �޽����� ���ƿ��� �� ó���Ҷ� ĳ�������� �������� üũ
//  �ۼ����� / �ۼ��� : 2003.11.21 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define SERVEROBJECTID_CHARACTER_START				1
#define SERVEROBJECTID_CHARACTER_END				999

#define SERVEROBJECTID_MONSTER_START				1000
#define SERVEROBJECTID_MONSTER_END					9999

#define SERVEROBJECT_IS_CHARACTER( i )		( i >= SERVEROBJECTID_CHARACTER_START ) && ( i <= SERVEROBJECTID_CHARACTER_END ) ? HT_TRUE : HT_FALSE
#define SERVEROBJECT_IS_MONSTER( i )		( i >= SERVEROBJECTID_MONSTER_START ) && ( i <= SERVEROBJECTID_MONSTER_END ) ? HT_TRUE : HT_FALSE

//-----------------------------------------------------------------------------//
//  ���� : ����Ʋ���� ���� ���ð�
//  �ۼ����� / �ۼ��� : 2003.4.28 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define IDLE_PC_TIME										15000
#define IDLE_MONSTER_TIME									10000

//-----------------------------------------------------------------------------//
//  ���� : ���� ����
//  �ۼ����� / �ۼ��� : 2002.7.4 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define SOUNDEFFECT_CLICK									33501
#define SOUNDEFFECT_CLICKCHOOSE								33502
#define SOUNDEFFECT_CLICKERROR								33503
#define SOUNDEFFECT_CLICKNOTIFY								33503

#define SOUNDEFFECT_NORWALK									31010
#define SOUNDEFFECT_NORRUN									31013
#define SOUNDEFFECT_ATTWALK									31016
#define SOUNDEFFECT_ATTRUN									31019
#define SOUNDEFFECT_SIT										31021

#define SOUNDEFFECT_WIND									33504
#define SOUNDEFFECT_DRICKETS								33505

#define SOUNDBGM_MANDATA1ST_ENDING							30004

#define SOUNDBGM_MANDATA1ST_VILLAGE							30008
#define SOUNDBGM_MANDATA1ST_FIELD							30007
#define SOUNDBGM_JINA_VILLAGE								30010
#define SOUNDBGM_LOWKRUMA									30009
#define SOUNDBGM_MANDATA1ST_FIELD							30007
#define SOUNDBGM_MANDATA_DUNGEON							30011
#define SOUNDBGM_PAMIRFIELD									30012

#define SOUNDBGM_JAPAN_VILLAGE								30013
#define SOUNDBGM_JAPAN_FIELD								30014
#define SOUNDBGM_JAPAN_BATTLE								30015

#define SOUNDBGM_NEWKRUMA									30016

//-----------------------------------------------------------------------------//
//  ���� : �κ��丮 ����
//  �ۼ����� / �ۼ��� : 2002.7.4 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define INVENTORY_SELLSIZE_X							32
#define INVENTORY_SELLSIZE_Y							32

#define ITEM_LOCATION_MAP								0
#define ITEM_LOCATION_MAP_FIELD							0
#define ITEM_LOCATION_PC								1
#define ITEM_LOCATION_PC_BAG1							0
#define ITEM_LOCATION_PC_BAG2							1
#define ITEM_LOCATION_PC_BAG3							2
#define ITEM_LOCATION_EQUIP								2
#define ITEM_LOCATION_EQUIP_HEAD						0
#define ITEM_LOCATION_EQUIP_RIGHT_EAR					1
#define ITEM_LOCATION_EQUIP_LEFT_EAR					2
#define ITEM_LOCATION_EQUIP_NECK						3
#define ITEM_LOCATION_EQUIP_ARMOR						4
#define ITEM_LOCATION_EQUIP_BELT						5
#define ITEM_LOCATION_EQUIP_TWO_HAND					100
#define ITEM_LOCATION_EQUIP_RIGHT_HAND					6
#define ITEM_LOCATION_EQUIP_LEFT_HAND					7
#define ITEM_LOCATION_EQUIP_RIGHT_BRACELET				8
#define ITEM_LOCATION_EQUIP_LEFT_BRACELET				9
#define ITEM_LOCATION_EQUIP_RIGHT_RING					10
#define ITEM_LOCATION_EQUIP_LEFT_RING					11
#define ITEM_LOCATION_EQUIP_FOOT						12
#define ITEM_LOCATION_EQUIP_GLOVE						13
#define ITEM_LOCATION_EQUIP_PANTS						14
#define ITEM_LOCATION_EQUIP_BAG							15

#define ITEM_LOCATION_NPC							3
#define ITEM_LOCATION_NPC_ITEMSAVED						0
//#define ITEM_LOCATION_CHATURANGA_BOARD				4	// �������� ���� - ������ (������)
//#define ITEM_LOCATION_CHATURANGA_BOARD_ITEMSAVED		0
//#define ITEM_LOCATION_BELT							4
//#define ITEM_LOCATION_BELT_BELT1						0
//#define ITEM_LOCATION_BELT_BELT2						1
//#define ITEM_LOCATION_BELT_BELT3						2
#define ITEM_LOCATION_EXCHANGE						5
#define ITEM_LOCATION_EXCHANGE_MYWIN					0
#define ITEM_LOCATION_EXCHANGE_OTHERWIN					1
#define ITEM_LOCATION_ECONOMY						6
#define ITEM_LOCATION_ECONOMY_AIDITEM					1
//#define	ITEM_LOCATION_BARTER						7	
//#define	ITEM_LOCATION_BARTER_ITEMSAVED					0
#define ITEM_LOCATION_OFFERING						7
#define ITEM_LOCATION_OFFERING_ITEM						0
#define ITEM_LOCATION_STORE							8
#define ITEM_LOCATION_STORE_SELL						0
#define ITEM_LOCATION_STORE_BUY							1
#define ITEM_LOCATION_ASHRAMCARGO					9
#define ITEM_LOCATION_ASHRAMCARGO_BAG1					0
#define ITEM_LOCATION_RENTALSTORE					10
#define ITEM_LOCATION_RENTALSTORE_BAG1					0

#define MAINMENU_POSX									736
#define MAINMENU_POSY									0

//-----------------------------------------------------------------------------//
//  ���� : ���� ������ ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define GAMESEQUNCE_MAINGAME_NONE						0
#define GAMESEQUNCE_MAINGAME_RECEIVEINITCHAR			1
#define GAMESEQUNCE_MAINGAME_DONEINITCHAR				2
#define GAMESEQUNCE_MAINGAME_GMAEPLAY					3

#define GAMESEQUNCEBIG_INTRO							0
#define GAMESEQUNCEBIG_MAIN								1


//-----------------------------------------------------------------------------//
//  ���� : ī�޶� ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define CAMERATYPE_EYE_DEFINECAMERA						100
#define CAMERATYPE_EYE_STRAIGHTMOVE						101
#define CAMERATYPE_EYE_CENTERCHARACTER					102
#define CAMERATYPE_EYE_BACKVIEW							103
#define CAMERATYPE_EYE_FOLLOWWEAPON						104
#define CAMERATYPE_EYE_DEATH							105
#define CAMERATYPE_EYE_STARTGAMEPLAY					106
#define CAMERATYPE_EYE_FRONTVIEW						107
#define CAMERATYPE_EYE_LINEMOVE							108

#define CAMERATYPE_LOOK_DEFINECAMERA					100
#define CAMERATYPE_LOOK_STRAIGHTMOVE					101
#define CAMERATYPE_LOOK_CENTERCHARACTER					102
#define CAMERATYPE_LOOK_BACKVIEW						103
#define CAMERATYPE_LOOK_FOLLOWWEAPON					104
#define CAMERATYPE_LOOK_DEATH							105
#define CAMERATYPE_LOOK_STARTGAMEPLAY					106
#define CAMERATYPE_LOOK_FRONTVIEW						107
#define CAMERATYPE_LOOK_LINEMOVE						108


//-----------------------------------------------------------------------------//
//  ���� : ���ϰ� ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define RETURNTYPE_INTRO_COMPLETE						100
#define RETURNTYPE_DOWNLOAD_COMPLETE					100
#define RETURNTYPE_CHARACTER_COMPLETE					101

#define RETURNTYPE_LOGIN_LOGIN							101
#define RETURNTYPE_LOGIN_NEW							102
#define RETURNTYPE_LOGIN_EXIT							103
#define RETURNTYPE_LOGIN_COMPLETE						104

#define RETURNTYPE_SELECTWORLD_NONE						110
#define RETURNTYPE_SELECTWORLD_OK						111
#define RETURNTYPE_SELECTWORLD_CANCEL					112

#define RETURNTYPE_SELECTCHAR_OK						121
#define RETURNTYPE_SELECTCHAR_CANCEL					122
#define RETURNTYPE_SELECTCHAR_NEW						123
#define RETURNTYPE_SELECTCHAR_DELETE					124

#define RETURNTYPE_NEWCHAR_OK							131
#define RETURNTYPE_NEWCHAR_PREV							132
#define RETURNTYPE_NEWCHAR_NEXT							133
#define RETURNTYPE_NEWCHAR_CANCEL						134

#define RETURNTYPE_DELETECHAR_OK						135
#define RETURNTYPE_DELETECHAR_CANCEL					136

#define RETURNTYPE_SELECTSTARTPOINT_MV					137
#define RETURNTYPE_SELECTSTARTPOINT_EP					138
#define RETURNTYPE_SELECTSTARTPOINT_CANCEL				139

#define RETURNTYPE_MAIN_RETURN_SERVERSELECCT			501
#define RETURNTYPE_MAIN_RETURN_CHARACTERSELECT			502
#define	RETURNTYPE_MAINGAME_FAILD						999

#define RETURNTYPE_EXIT_INTRO							990
#define RETURNTYPE_EXIT_MAINGAME						991

//-----------------------------------------------------------------------------//
//  ���� : �κ��丮 / ������ ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define ITEM_ACTION_NONE								0
#define ITEM_ACTION_DOING								1
#define ITEM_ACTION_ONINVENTORY							2

//-----���� ������-----//
#define ITEM_ARMSTYPE_SWORD1							100
#define ITEM_DEFENSEHEADTYPE_SUIT1						200

#define ITEM_DURABILITY_NOTE_MSG						20.0f
#define ITEM_REFORM_RENDER_TIMES						3

enum
{
	_eITEM_WEAPON	= 0,
	_eITEM_BODY		,
	_eITEM_PANTS	,
	_eITEM_SHIELD	,
	_eITEM_HEAD		,
	_eITEM_FOOT		,
	_eITEM_BELT		,
	_eITEM_EQUIP_NUM,
};


//-----------------------------------------------------------------------------//
//  ���� : ĳ���� ����
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
//	ChangeAni �� ����޴� Animation
#define CHARACTER_ANISTATE_STD								0
#define CHARACTER_ANISTATE_WLK								1
#define CHARACTER_ANISTATE_RUN								2
#define CHARACTER_ANISTATE_IDL								3
#define CHARACTER_ANISTATE_SITDOWN							4
#define CHARACTER_ANISTATE_HIT								5
#define CHARACTER_ANISTATE_DIE								6
#define CHARACTER_ANISTATE_STANDUP							7
#define CHARACTER_ANISTATE_MAGIC_DEFENCE					8
#define CHARACTER_ANISTATE_SIT								9
#define CHARACTER_ANISTATE_MOBHIT							10
#define CHARACTER_ANISTATE_BOW								11
#define CHARACTER_ANISTATE_CHARGE							12
#define CHARACTER_ANISTATE_PROVOKE							13
//	������ �Լ��� �ִ� �ִϸ��̼�
#define CHARACTER_ANISTATE_NORMALATK						20
#define CHARACTER_ANISTATE_SKILLREADY						21
#define CHARACTER_ANISTATE_SKILLCAST						22
#define CHARACTER_ANISTATE_SKILLACTIVATE					23
#define CHARACTER_ANISTATE_SKILLATK							24

#define CHARACTER_SPEEDLEVEL_STOP						0
#define CHARACTER_SPEEDLEVEL_WALK						1
#define CHARACTER_SPEEDLEVEL_RUN						2
#define CHARACTER_SPEEDLEVEL_KNOCKBACK					3
#define CHARACTER_SPEEDLEVEL_ZUBAS						4
#define CHARACTER_SPEED_MAINCHARCORRECT					15
#define CHARACTER_SPEED_OTHERCHARCORRECT				14
#define CHARACTER_SPEED_MONSTERCORRECT					14
#define CHARACTER_SPEED_FOLLOWCORRECT					30

#define AOI_LEVEL_NONE									100
#define AOI_LEVEL_1										1
#define AOI_LEVEL_2										2
#define AOI_LEVEL_3										3
#define AOI_LEVEL_4										4
#define AOI_LEVEL_5										5
#define AOI_LEVEL_6										6
#define AOI_LEVEL_7										7
#define AOI_LEVEL_8										8

#define MOUSEBUTTONMOVE_SETTING							0
#define MOUSEBUTTONMOVE_MOVE							1
#define MOUSEBUTTONMOVE_STOP							2


//-----------------------------------------------------------------------------//
//  ���� : ��Ʈ��ũ ���� ����
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
#define STATUS_CONNECTING							0x00
#define STATUS_ALIVE								0x01
#define STATUS_DISCONNECT							0x02
#define STATUS_NONE									0xFF

//-----------------------------------------------------------------------------//
//  ���� : �ε��� ������ ����!
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define	ITEMINDEX_ASSISTANTHAT							6555

//-----------------------------------------------------------------------------//
//  ���� : �������� �����̴��� �ʿ����̴��� üũ
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define ICON_STATUS_NONE								1
#define ICON_STATUS_MOVE								2

//-----------------------------------------------------------------------------//
//  ���� : ������ �׽�Ʈ�������� ���μ������� ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
#define SERVERTYPE_TEST									0
#define SERVERTYPE_MAIN									1

//-----------------------------------------------------------------------------//
//  ���� : Į�� ���̺�
//  �ۼ����� / �ۼ��� : 2004.02.03 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define COLORTABLE_BLACK								0
#define COLORTABLE_BLUE									1
#define COLORTABLE_LIGHTBLUE							2
#define COLORTABLE_SKY									3
#define COLORTABLE_DARKGREEN							4
#define COLORTABLE_GREEN								5
#define COLORTABLE_LIGHTGREEN							6
#define COLORTABLE_ORANGE								7
#define COLORTABLE_LIGHTORANGE							8
#define COLORTABLE_DARKPEOPLE							9
#define COLORTABLE_PEOPLE								10
#define COLORTABLE_PURPLE								11
#define COLORTABLE_RED									12
#define COLORTABLE_YELLOW								13
#define COLORTABLE_WHITE								14

//-----------------------------------------------------------------------------//
//  ���� : �������� �����ο�
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
#define CONNECTNUM_SERVERLIMIT							999
#define CONNECTNUM_CLIENTLIMIT							920

//-----------------------------------------------------------------------------//
//  ���� : Zone Index Name / Map size
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
#define	MAP_CELL_SIZE									10

#define ZONEVALUE_CLIENT_SERVER							40000
#define ZONE_MANDARA1ST									1
#define ZONE_JINA3RD									9
#define ZONE_KURUMA										10
#define ZONE_CHATURANGGA								11
#define	ZONE_FORTRESS									16
#define	ZONE_BIRYUCASTLE								17
#define ZONE_MANDARA2ND									18
#define ZONE_MANDARA3TH									19
#define ZONE_ANAKAKURUMA								20

#define MAP_MANDARA_1ST									40001	// ���ٶ���1st
#define MAP_MANDARA_2ND									40002	// ���ٶ���2nd
#define MAP_MANDARA_DUNGEON_1ST							40003	// ���ٶ����1st
#define MAP_MANDARA_DUNGEON_2ND							40004	// ���ٶ����2nd
#define MAP_MANDARA_DUNGEON_3RD							40005	// ���ٶ����3rd
#define MAP_MANDARA_DUNGEON_4TH							40006	// ���ٶ����4th
#define MAP_JINA_1ST									40007	// ��������1st
#define MAP_JINA_2ND									40008	// ��������2nd
#define MAP_JINA_3RD									40009	// ��������3rd
#define MAP_JINA_4TH									40010	// �ֽ��� �� ���̵�
#define MAP_JINA_GUILD									40011	// �����������
#define MAP_JINA_7TH_CAVE								40012	// �ϵμ�����

#define MAP_EVENT_LOWKALIA								40013	// �ʱ�Į����
#define MAP_EVENT_MIDKALIA								40014	// �߱�Į����
#define MAP_EVENT_HIGHKALIA								40015	// ���Į����
#define MAP_ARENA_DURGA									40016	// Arena_Durga
#define MAP_KATHANA3_BIRYUCASTLE						40017	// BiryuCastle
#define MAP_LOWKRUMA									40020	// LowKruma
//fors_debug add map_info 21
#define MAP_K3DOWN   									40021	// LowKruma

#define MAP_INTRO										40100	// ��Ʈ��

#define HT_IS_TRIMURITIZONE( i )			( i == ZONE_KURUMA ) || ( i == ZONE_CHATURANGGA ) || ( i == ZONE_ANAKAKURUMA )  ? HT_OK : HT_FAIL
#define HT_IS_FORETRESSZONE( i )			( i == ZONE_FORTRESS ) ? HT_OK : HT_FAIL
#define HT_IS_BIRYUCASTLE( i )				( i == ZONE_BIRYUCASTLE ) ? HT_OK : HT_FAIL
#define HT_IS_MOBGATE( i )					( i == 2295 ) || ( i == 2305 ) || ( i == 2308 ) || ( i == 2311 ) || ( i == 2252 ) || ( i == 2253 ) || ( i == 2254 ) || ( i == 2255 ) || ( i == 2934 ) || ( i == 2935 ) || ( i == 2936 ) || ( i == 2937 ) || ( i == 2846 ) || ( i == 2847 ) || ( i == 2848 ) || ( i == 2445 ) || ( i == 2446 ) ? HT_OK : HT_FAIL
#define HT_IS_MOBSUMMONS( i )				( i == 2801 ) || ( i == 2802 ) || ( i == 2803 ) || ( i == 2467 ) || ( i == 2468 ) || ( i == 2804 ) || ( i == 2805 ) || ( i == 2806 ) || ( i == 2807 ) || ( i == 2808 ) || ( i == 2809 ) || ( i == 2448 ) || ( i == 2449 ) || ( i == 2450 ) || ( i == 2465 ) || ( i == 2466 ) ? HT_OK : HT_FAIL
#define HT_IS_CANNOTMOVEITEM( i )			( i == 6736 ) || ( i == 7074 ) || ( i == 7410 ) ? HT_OK : HT_FAIL

//-----------------------------------------------------------------------------//
//  ���� : IME Define
//  �ۼ����� / �ۼ��� : 2004.04.06 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define INPUTMODE_NORMAL								0
#define INPUTMODE_IME									1

#define COMPOSITION_COMPSTR								0
#define COMPOSITION_RESULTSTR							1

//-----------------------------------------------------------------------------//
//  ���� : ������ȣ/����Ÿ��
//  �ۼ����� / �ۼ��� : 2004.08.23 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define	INATIONALTYPE_KOREA								0
#define	INATIONALTYPE_CHINA								1
#define	INATIONALTYPE_INDONESIA							2
#define	INATIONALTYPE_PHILIPPINE						3
#define	INATIONALTYPE_JAPEN								4
#define	INATIONALTYPE_TAIWAN							5
#define	INATIONALTYPE_MEXICO							6

//-----------------------------------------------------------------------------//
//  ���� : Potal Mob ID
//  �ۼ����� / �ۼ��� : 2004.06.09 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define FORPOTAL_MOBID_FORCHATURANGR					2946
#define FORPOTAL_MOBID_FORTRIMURITICAVE					2202

//-----------------------------------------------------------------------------//
//  ���� : Guild Authority
//  �ۼ����� / �ۼ��� : 2004.10.13 / ���Ǳ�
//-----------------------------------------------------------------------------//
#define	GUILD_AUTHORITY_MAHARAJA			10	// ��� ���϶���
#define	GUILD_AUTHORITY_RAJA				9	// ��� ����
#define	GUILD_AUTHORITY_PROOBAJA			8	// ��� �������
#define	GUILD_AUTHORITY_DANEACA				7	// ��� �ܵ�ī
#define	GUILD_AUTHORITY_TAPASA				6	// ��� Ÿ�Ļ�
#define	GUILD_AUTHORITY_NONE				0	// ��� 0

//-----------------------------------------------------------------------------//
//  ���� : ����Ʈ �����ؼ� 2D, 3d
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
typedef struct _HTPoint
{
	int x, y;
} HTPoint;

//-----------------------------------------------------------------------------//
//  ���� : Ű / ���콺 �Է��� �Խ� �����Ͽ� �� �˰��� Ȱ��
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
typedef struct _HT_INTERFACE_FLAG
{
	HTPoint				pPt;
	HTint				iLeftClick;
	HTint				iRightClick;
	HTint				iLeftDown;
	HTint				iRightDown;

	HTint				bLbuttonSw;
	HTbool				bLbuttonDbClk;
	HTint				bRbuttonSw;
	HTbool				bRbuttonDbClk;

	HTint				iKeyDownSw;
	HTint				iSpecialKeyDownSw;

	WPARAM				wCameraParam;
	WPARAM				wSpecialParam;
	CHTString			sString;

} HT_INTERFACE_FLAG;

//-----------------------------------------------------------------------------//
//  ���� : 
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
typedef struct _HT_2DSPRITE_FLAG
{
	HTbool				bShow;
	HTint				iID;
	HTvector3			vPos;

	HTint				iActionSw;
	HTfloat				fActionValue;
	HTfloat				fActionTrans;

} HT_2DSPRITE_FLAG;


//-----------------------------------------------------------------------------//
//  ���� : �������� ��ġ�� �渦 ��ȯ
//  �ۼ����� / �ۼ��� : ���Ǳ� / 2002.11.11
//-----------------------------------------------------------------------------//
typedef struct _HT_ItemReturnRoom
{
	HTint		nLocation;
	HTint		nInventory;
	HTint		nCellPosx;
	HTint		nCellPosy;
	HTint		nDlgNo;
	HTint		nGroupNo;
	HTint		nBitmapNo;
	//HTvector3	vecWindowPos;
} HT_ItemReturnRoom;

//-----------------------------------------------------------------------------//
//  ���� : �� �κ��丮 �������� ���ý�ų ��
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//
typedef struct _HT_ITEMSETTING_FLAG
{
	HTint					nLocation;
	HTint					nInventory;
	//HTvector3				vecWindowPos;
	HTPoint					pCellPos;

} HT_ITEMSETTING_FLAG;

//-----------------------------------------------------------------------------//
//  ���� : ��ų
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
typedef struct _HT_SKILLINSERT_FLAG
{	
	DWORD					dwSkill_Index;
	BYTE					bySkill_Level;
	BYTE					bySkill_Type;
	BYTE					bySkill_Count;

} HT_SKILLINSERT_FLAG;

//	��ų �κ��丮�� �ý����� ������ ����_�ý��ۿ��� �迭�� ���´�.
typedef struct _HT_SKILL_INVENTORYCONNECT
{
	DWORD							dwSkillIndex;
	BYTE							byLevel;
	HTint							iSkillIconID;

} HT_SKILL_INVENTORYCONNECT;


typedef struct _HT_SKILLCREATE_FLAG
{	
	DWORD					iSkill_KeyID;
	DWORD					iSkill_Index;
	BYTE					bSkill_Type;
	BYTE					bSkill_Level;

	short                   snMovingSpeed;// �������� �̵��ӵ�
	short                   snAttackSpeed;// �������� ���ݼӵ�
	short                   snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                    byShootRange; // �߻�ü�� �����Ÿ�

	//-----0:�޼�, 1:������, 2:���ེųâ, 3:�κ��丮1
	BYTE					bSkill_Location;
	BYTE					bSkill_InvenCellX;
	BYTE					pSkill_InvenCellY;

} HT_SKILLCREATE_FLAG;


//-----------------------------------------------------------------------------//
//  ���� : ���� ����
//  �ۼ����� / �ۼ��� : 
//-----------------------------------------------------------------------------//  
typedef struct _HT_ATTACKCREATE_FLAG
{
   BYTE						Attack_TypeMO_Other;
   DWORD					Attack_ID;			//	���� �� ���� �� ID
   DWORD					Attack_KeyID;		//	���� �� ���� Key_ID
   HTPoint					Attack_Pos;			//	���� ����
   BYTE						Attack_Type;		//	���� Ÿ�� -> 0x00:Skill, 0x01:Item, 0x02:�Ǽ�
   HTint					Attack_Kind;
   HTint					Attack_Item_KeyID;	//	���ݿ� ����� �������� KeyID
   HTint					Attack_Item_Index;	//	���ݿ� ����� �������� Index
   HTint					Attack_Skill_Index;	//	���ݿ� ����� ��ų�� index

   HTint					DisAttack_ID;		//	���ݴ� �� ���� �� ID
   DWORD					DisAttack_KeyID;	//	���ݴ� �� ���� Key_ID
   HTPoint					DisAttack_Pos;		//	���� Ÿ�� ����
   short					DisAttack_snDegree;	//  ����
   
} HT_ATTACKCREATE_FLAG;


//----------------------------------------------------------------------------//
//	���� �̸�	: HTControlDef.h
//
//	���� ���� 	: 
//		- ����
//
//	�ۼ���		:
//		- 2002/05/17, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#define TNMSG_HEADER_SIZE		(sizeof(HEADER))
#define	MAX_CHAT_MSG_LENGTH		128
#define MAX_LOGIN_MSG_LENGTH	64
#define TNNETWORKERROR			0xFFFF
#define TNNETWORKCONNECT		TNNETWORKERROR-1
#define TNNETWORKDISCONNECT		TNNETWORKERROR-2

//-----------------------------------------------------------------------------//
// ���� : ��ų�� ������ ����â�� ǥ���� �������� ���
// �ۼ����� / �ۼ��� : 2002.12.26 �輱��
//-----------------------------------------------------------------------------//
//----------- ������ �Ϲ� ���� ----------//
typedef struct _HT_ITEM_DATA
{
	CHTString			str;
	HT_COLOR			color;
} HT_ITEM_DATA;

typedef struct _HT_ITEM_EXPANSION_DATA
{
	HT_ITEM_DATA		basic;
	HT_ITEM_DATA		addtion;
} HT_ITEM_EXPANSION_DATA;

typedef struct _HT_ITEMINFO
{
	HT_ITEM_DATA			strName;				// ������ �̸�
	HT_ITEM_DATA			strDescription;			// ������ ����
	vector<HT_ITEM_DATA*>	vLimitStr;				// ���� ����
	vector<HT_ITEM_DATA*>	vSourceStr;				// ���
	vector<HT_ITEM_EXPANSION_DATA*>	vAttributeStr;	// Ư��
} HT_ITEMINFO;

//-----------------------------------------------------------------------------//
//  ���� : World Server Infomation
//  �ۼ����� / �ۼ��� : 2002.07.30  �ۼ��� : �����
//-----------------------------------------------------------------------------//
//#pragma pack(push, 1)

typedef struct _WORLDLIST
{
	BYTE  byFlag;
	char  szWorldName[26];
	char  szWorldIP[16];
	short snWorldPort;
} WORLDLIST;

//------------------------------------------------------------------------------//
//	���� : ����Ʈ �̺�Ʈ�� ���� ����
//	�ۼ����� / �ۼ��� : 2003.04.17 �輱��
//------------------------------------------------------------------------------//
#define QUEST_STATUS_NONE		0x00		// ����Ʈ ����
#define QUEST_STATUS_START		0x01		// ����
#define QUEST_STATUS_PROGRESS	0x02		// ������
#define QUEST_STATUS_REJECTION	0x03		// �ź�		// 2003.07.09 ���� �߰�
#define QUEST_STATUS_FAIL		0xfe		// ����
#define QUEST_STATUS_SUCCESS	0xff		// �Ϸ�

#define QUEST_STATUS_0			0			
#define QUEST_STATUS_1			1			// 1��
#define QUEST_STATUS_2			2			// 2��
#define QUEST_STATUS_3			3			// 3��
#define QUEST_STATUS_4			4			// 4��
#define QUEST_STATUS_5			5			// 5��

//------------------------------------------------------------------------------//
//	���� : ��ũ�� ����Ʈ
//	�ۼ����� / �ۼ��� : 2003.04.22 �輱��
//------------------------------------------------------------------------------//
#define CHAKRA_POINT_MUSCLE		0
#define CHAKRA_POINT_NERVE		1
#define CHAKRA_POINT_HEART		2
#define CHAKRA_POINT_SOUL		3
#define BRAHMAN_POINT			4

//------------------------------------------------------------------------------//
//	���� : ������ ���� ���Ҷ� ����/���� ��� ����
//	�ۼ����� / �ۼ��� : 2003.05.13 �輱��
//------------------------------------------------------------------------------//
#define NPC_ITEM_MAKING			0
#define NPC_ITEM_REFINING		1
#define NPC_ITEM_SELL			2
#define NPC_ITEM_RENTAL_SELL	3
//fors_debug �ӵȼ���֪������ʲô��
#define MAX_REFINE_MAIN_LEVEL	15	// �ִ� ��ȭ ���� ���� Ƚ��
#define MAX_REFINE_SUB_LEVEL	10	// �ִ� �ּ� ���� ���� Ƚ��
#define MAX_EFFECT_NUM			5	// �� �������� �ִ� Effect ����
//------------------------------------------------------------------------------//
//	���� : Ŀ��
//	�ۼ����� / �ۼ��� : 2003.05.19 �輱��
//------------------------------------------------------------------------------//
#define CURSOR_ARROW_1		0		// ȭ��ǥ(arrow) Ŀ��
#define CURSOR_ARROW_2		1
#define CURSOR_HAND_1		2		// ��(hand) Ŀ��
#define CURSOR_HAND_2		3
#define CURSOR_HAND_ANI		4		// �����̴� ��(hand) Ŀ��
#define CURSOR_SWORD		5		// Į(sword) Ŀ��
#define CURSOR_SWORD_ANI	6		// �����̴� Į(sword) Ŀ��
#define CURSOR_NPC			7		// ��ȭ(NPC) Ŀ��
#define CURSOR_NPC_ANI		8
#define CURSOR_REPAIR		9		// ����(repair) Ŀ��
#define CURSOR_REPAIR_ANI	10
#define CURSOR_REPAIRD		11		// ���� �Ұ� Ŀ��
#define CURSOR_ADDRESS		12		// Address ȭ��ǥ(arrow) Ŀ��
#define CURSOR_ADDRESS_ANI	13
#define CURSOR_PARTY		14		// Party ȭ��ǥ(arrow) Ŀ��
#define CURSOR_PARTY_ANI	15
#define CURSOR_TRADE		16		// Trade ȭ��ǥ(arrow) Ŀ��
#define CURSOR_TRADE_ANI	17
#define CURSOR_RBUTTON		18		// ������ ��ư Ŭ��
#define CURSOR_BLOG			19		// Blog Ŀ��
#define CURSOR_BLOG_ANI		20
#define CURSOR_SELECT		21		// SELECT Ŀ��
#define CURSOR_SELECT_ANI	22
//------------------------------------------------------------------------------//
//	���� : �� Ʈ���̵� â�� ����ŷ�� �������� ���� ����ü
//	�ۼ����� / �ۼ��� : 2003.05.20 �輱��
//------------------------------------------------------------------------------//
typedef struct _HT_MYEXCHANGE_ITEM
{
	DWORD	dwKeyID;		// ��ȯâ�� �߰��� �������� KeyID
	DWORD	dwIndex;		// ��ȯâ�� �߰��� �������� Index
	short	snCurDurability;
	int		nItemCount;		// ��ȯâ�� �߰��� �������� ����
	short	snX;			// ��ȯâ���� ������ X ��ǥ
	short	snZ;			// ��ȯâ���� ������ Z ��ǥ
} HT_MYEXCHANGE_ITEM;

//------------------------------------------------------------------------------//
//	���� : 
//	�ۼ����� / �ۼ��� : ���Ǳ�
//------------------------------------------------------------------------------//
typedef struct _ATTACK_FACTOR
{
	CHTString strAttackName;			//	�������� �̸�
	BYTE byTribe;						//	������ ����
	DWORD dwAttackKeyID;				//	�������� Ű ���̵�
	DWORD dwTargetKeyID;				//	���ݴ���� Ű ���̵�
	HTint nAttackType;					//	0x01:�Ϲݰ���, 0x02:��ų����
	HTfloat fDirect;					//	�������� ����
	HTvector3 vecSourcePos;				//	�������� ��ġ
	HTvector3 vecTargetPos;				//	���ݹ������� ��ġ
	HTint nCharModelID;					//	�������� �� ���̵�
	HTint iTargetModelID;				//	���ݹ������� �� ���̵�
	HTint nAttackItemID;				//	�������� ���� �ε���
	HTint nAttackSkillID;				//	�������� ��ų �ε���
	BYTE  byAttackSkillIDLevel;			//	�������� ��ų ����
	BYTE byAttackSkillAttribute;		//	�������� ��ų �Ӽ�

} S_ATTACK_FACTOR, * P_ATTACK_FACTOR;


typedef struct _MSG_ATTACK_OTHERMOB
{
	HTint				iCasterHP;
	HTint				iSkillID;					//	����� ��ų
	unsigned short		PosX,		PosY;
	unsigned short		TargetX,	TargetZ;		//	������ ��ǥ
	short               snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:��ֹ��浹 ...)
    HTint				iTargetModelID;
	HTvector3			vecTargetPos;
	DWORD				dwDurationTime;
	HTshort				snSkillLevel;
	S_TNTARGET_DATA     krgTarget[TN_MAX_TARGET_COUNT] ;

} S_MSG_ATTACK_OTHERMOB;




// ��� ������ ����
struct S_GUILD_DATA {
	STRUCT_GUILD_MEMBER			info;
	struct S_GUILD_DATA*		pNextNode;
};

//-------------------------------------------------------------------------------//
// ���� : ����Ʈ ���
// �ۼ����� / �ۼ��� : 2003.06.27 �輱��
//-------------------------------------------------------------------------------//
#define TUTORIAL_QUEST_START		1	// Ʃ�丮�� ����Ʈ 
#define TUTORIAL_QUEST_END			5
#define QUEST_TUTORIAL_0	0
#define QUEST_TUTORIAL_1	1
#define QUEST_TUTORIAL_2	2
#define QUEST_TUTORIAL_3	3
#define QUEST_TUTORIAL_4	4
#define QUEST_TUTORIAL_5	5
#define QUEST_TUTORIAL_6	6
#define QUEST_TUTORIAL_7	7
#define QUEST_TUTORIAL_8	8
#define QUEST_TUTORIAL_9	9

// ���ٶ� ����Ʈ
//#define SCENARIO_QUEST_1_START		11	// 1�� �ó����� ����Ʈ 
#define SCENARIO_QUEST_1_START		6	// 1�� �ó����� ����Ʈ 
#define SCENARIO_QUEST_1_END		20
#define QUEST_BASIC_GRADE	6
#define QUEST_MANDARA_1		11
#define QUEST_MANDARA_2		12
#define QUEST_MANDARA_3		13
#define QUEST_MANDARA_4		14
#define QUEST_MANDARA_5		15
#define QUEST_MANDARA_6		16
#define QUEST_MANDARA_7		17
#define QUEST_MANDARA_8		18
#define QUEST_MANDARA_9		19
#define QUEST_MANDARA_10	20

// ���߶� ����Ʈ
#define SCENARIO_QUEST_2_START		21	// 2�� �ó����� ����Ʈ 
#define SCENARIO_QUEST_2_END		35
#define QUEST_SHAMBALA_1	21
#define QUEST_SHAMBALA_2	22
#define QUEST_SHAMBALA_3	23
#define QUEST_SHAMBALA_4	24
#define QUEST_SHAMBALA_5	25
#define QUEST_SHAMBALA_6	26
#define QUEST_SHAMBALA_7	27
#define QUEST_SHAMBALA_8	28
#define QUEST_SHAMBALA_9	29
#define QUEST_SHAMBALA_10	30

#define QUEST_SHAMBALA_11	31 // 2�� ����
#define QUEST_SHAMBALA_12	32 // 2�� ���� - �ı��� ����
#define QUEST_SHAMBALA_13	33 // 2�� ���� - �γ��� ����
#define QUEST_SHAMBALA_14	34 // 2�� ���� - ������ ����
#define QUEST_SHAMBALA_15	35 // 2�� ���� - �Ǹ��� ����

// ���� ����Ʈ
#define SCENARIO_QUEST_3_START		36
#define SCENARIO_QUEST_3_END		40
#define QUEST_JINA_1				36
#define QUEST_JINA_2				37
#define QUEST_JINA_3				38
#define QUEST_JINA_4				39
#define QUEST_JINA_5				40

// ������ ����Ʈ 2005. 2. 16
#define SCENARIO_QUEST_4_START		41
#define SCENARIO_QUEST_4_END		45
#define QUEST_JINA2_1				41
#define QUEST_JINA2_2				42
#define QUEST_JINA2_3				43
#define QUEST_JINA2_4				44
#define QUEST_JINA2_5				45

// �ϵμ��� ����Ʈ 2005. 9. 13
#define SCENARIO_QUEST_5_START		46
#define SCENARIO_QUEST_5_END		50
#define QUEST_JINA3_1				46
#define QUEST_JINA3_2				47
#define QUEST_JINA3_3				48
#define QUEST_JINA3_4				49
#define QUEST_JINA3_5				50

// īŸ��3 ����Ʈ 2006. 3. 14
#define SCENARIO_QUEST_6_START		51
#define SCENARIO_QUEST_6_END		55
#define QUEST_K3_1					51
#define QUEST_K3_2					52
#define QUEST_K3_3					53
#define QUEST_K3_4					54
#define QUEST_K3_5					55

// ���� ����Ʈ
#define QUEST_INDEPENDENCE_1	81
#define QUEST_INDEPENDENCE_2	82

//-------------------------------------------------------------------------------//
// ���� : ������ �з� ��ȣ
// �ۼ����� / �ۼ��� : 2003.07.20 �輱��
// 1-�Ϲ� ������(���ⱸ/��/�׼����� ���), 2-�Ҹ� ������, 3-�������
// 4-�������, 5-����, 6-����Ʈ
//-------------------------------------------------------------------------------//
#define	ITEM_CLASS_ITEM						1
#define	ITEM_CLASS_USE						2
#define	ITEM_CLASS_SUB_METERIAL				3
#define	ITEM_CLASS_COLLECTION_METERIAL		4
#define	ITEM_CLASS_LOTTERY					5
#define	ITEM_CLASS_QUEST					6

//-------------------------------------------------------------------------------//
// ���� : ������ Ÿ�� 
// �ۼ����� / �ۼ��� : 2003.10.21 �輱��
//-------------------------------------------------------------------------------//
#define _ITEM_TYPE_WEPON_ONEHAND			1	
#define _ITEM_TYPE_WEPON_TWOHAND			2

#define _ITEM_TYPE_WEPON_SWORD				1	// ��
#define _ITEM_TYPE_WEPON_AX					2	// ����
#define _ITEM_TYPE_WEPON_LANCE				4	// â
#define _ITEM_TYPE_WEPON_MACE				8	// �б�
#define _ITEM_TYPE_WEPON_GLOVE				16	// ����
#define _ITEM_TYPE_WEPON_WAND				32	// ����
#define _ITEM_TYPE_WEPON_BOW				64	// ��ô
#define _ITEM_TYPE_WEPON_DAGGER				128	// �ܰ�

#define _ITEM_TYPE_DEFENCE_SHIELD			4
#define _ITEM_TYPE_DEFENCE_ARMOR			8		// ����
#define _ITEM_TYPE_DEFENCE_HELMET			16
#define _ITEM_TYPE_DEFENCE_BELT				32
#define _ITEM_TYPE_DEFENCE_SHOES			64
#define _ITEM_TYPE_DEFENCE_PANTS			2048	// ����
#define _ITEM_TYPE_DEFENCE_GLOVES			4096	// �尩

#define _ITEM_TYPE_ACCESSORY_EARRING		128		// �Ͱ���
#define _ITEM_TYPE_ACCESSORY_NECKLACE		256		// �����
#define _ITEM_TYPE_ACCESSORY_RING			512		// ����
#define _ITEM_TYPE_ACCESSORY_BRACELET		1024	// ����

#define _ITEM_TYPE_ACCESSORY_EXPANDINVEN	20		// �κ�Ȯ��
#define _ITEM_TYPE_USABLE_POSION			21		// ����
//#define _ITEM_TYPE_USABLE_WASTE				22	// �Ҹ�
//#define _ITEM_TYPE_REFINE					23	// ����
//#define _ITEM_TYPE_COLLECT					130	// ����
//#define _ITEM_TYPE_QUEST					25	// ����Ʈ 

//--------------------------------------------------------------------------------//
// ���� : ������ �̵� ����
// �ۼ����� / �ۼ��� : 2003.08.21 �輱��
//---------------------------------------------------------------------------------//
#define ITEMCONTROL_STATUS_NONE				1	// ����
#define ITEMCONTROL_STATUS_MOVE				2	// �̵�

//--------------------------------------------------------------------------------//
// ���� : Ȯ��/��Ȯ�� �޼��� â�� �߻� ��Ű�� ���� �з�
// �ۼ����� / �ۼ��� : 2003.09.03 �輱��
//---------------------------------------------------------------------------------//
//-------- Ȯ�� -----------//
#define CONFIRM_NPCCONTROL_NPC			1	// NPC���� ����(�Ÿ�����)
#define CONFIRM_NPCCONTROL_ITEM			2	// ������ ����
#define CONFIRM_NPCCONTROL_REFINING		3	// ����
#define CONFIRM_NPCCONTROL_FIX			4	// ����
#define CONFIRM_NPCCONTROL_DISJOINT		5	// �Ǹ�
#define CONFIRM_NPCCONTROL_BARTER_OK	6	// ��ȯâ���� ��ǰ�Ǹ�
#define CONFIRM_NPCCONTROL_BARTER_ERR	7	
#define CONFIRM_NPCCONTROL_CHAKRA		8	// ��ũ�� Ȯ��
#define CONFIRM_NPCCONTROL_BRAHMAN		9	// ��� Ȯ��
#define CONFIRM_NPCCONTROL_SKILL		10	// ��ų ����
#define CONFIRM_NPCCONTROL_SKILL_DEL	11	// ��ų ����
#define CONFIRM_NPCCONTROL_TRADE		12	// �ŷ���
#define CONFIRM_NPCCONTROL_ITEM_COUNT	13	// ������ ���԰���
#define CONFIRM_NPCCONTROL_TRIMURITI	14	// �ֽ� ����/����
#define CONFIRM_NPCCONTROL_COUPON_NUM_ERR	15	// ���� ��ȣ ����
#define CONFIRM_NPCCONTROL_COUPON_ERR	16	// ���� ��� ����

#define CONFIRM_ITEMCONTROL_INVEN_SLOT	21	// �κ� Ȯ��
#define CONFIRM_ITEMCONTROL_MINIMIZE	22	// �κ��丮 Ȯ�� ����	
#define CONFIRM_ITEMCONTROL_ITEM_USE	23	// ������ ���
#define CONFIRM_ITEMCONTROL_UNPACKING	24	// ������ ����

#define CONFIRM_INVEN_RUPIAH_MOVE		31	// ���Ǿ� �̵�
#define CONFIRM_INVEN_MINIMIZE			32	// �κ��丮 Ȯ�� ����

#define CONFIRM_QUEST_ERROR				41	// ����Ʈ ����

#define CONFIRM_SKILL_LEVEL_UP			51	// ��ų ���� ��

#define CONFIRM_EXCHANGE_REFUSE			61	// ������ ��ȯ ��û ����

#define CONFIRM_CHARACTER_REBIRTH		71	// ������������ �ٽ� �¾�ϴ�.

#define INFORWIN_PRIVATESHOP_WARNING	81 // ���λ��� ���
#define INFORWIN_PK_WARNING				82 // PK ���
#define INFORWIN_OFFERING_NOTIFY		83 // �峳 ����

#define CONFIRM_BLOGOPEN_ERR			85

#define CONFIRM_CASH_PAY_ERR			99 // ���� ������ ���� �ȳ�

#define CONFIRM_DUELSYSTEM				110	//	�����ý���
//------- ��Ȯ�� ---------//
#define RECONFIRM_NPCCONTROL_ITEM				1	// ������ ����
#define RECONFIRM_NPCCONTROL_REFINING			2	// ����	
#define RECONFIRM_NPCCONTROL_DISJOINT			3	// �Ǹ�
#define RECONFIRM_NPCCONTROL_SAVEPOSITION		4	// ��ġ ����
#define RECONFIRM_NPCCONTROL_COUPONREGISTER		5	// ���� ���
#define RECONFIRM_NPCCONTROL_TRIMIRITICHANGE	6	// �ֽ� ����

#define RECONFIRM_QUEST_TUTORIAL_START	11	// �ʺ��� ����Ʈ ���� ��Ȯ��

#define RECONFIRM_ITEMCONTROL_ITEM_DROP			16	// ������ ������
#define RECONFIRM_ITEMCONTROL_INIT_CHAKRA		17	// ��ũ�� �ʱ�ȭ
#define RECONFIRM_ITEMCONTROL_INIT_SKILL		18	// ��ų �ʱ�ȭ
#define RECONFIRM_ITEMCONTROL_CHTURANGA_ENTER	19	// �������� ����� ��뿩��

#define RECONFIRM_SKILL_LEVEL_UP		21	// ��ų ���� ��

#define RECONFIRM_EXCHANGE_REQ			31	// ������ ��ȯ ��û 
#define RECONFIRM_EXCHANGE_RECEIVE		32	// ������ ��ȯ ��û ����
#define RECONFIRM_USING_ITEM			33	// ������ ��뿩��


#define RECONFIRM_PARTY_RECEIVE_JOIN	41 // ��Ƽ ��û ����
#define RECONFIRM_PARTY_DELETE_MEMBER	42 // ��Ƽ ��� ����
#define RECONFIRM_PARTY_DISSOLUTION		43 // ��Ƽ ��ü
#define RECONFIRM_PARTY_SECESSION		44 // ��Ƽ Ż��

#define RECONFIRM_ADDRESS_REQ_JOIN		51	// �ּҷ� ��� ��û
#define RECONFIRM_ADDRESS_RECEIVE_JOIN	52	// �ּҷ� ��� ��û ����
#define RECONFIRM_ADDRESS_DELETE_MEMBER	53	// ��� ���� 

#define RECONFIRM_INVENTORY_MONEY_DROP	61	// �� ������

#define RECONFIRM_INVENTORY_EXPAND		70 // �κ��丮 Ȯ�� ������ ���� ����
#define RECONFIRM_EQU_INVENTORY_EXPAND	71 // ���λ��� �κ��丮 Ȯ�� ������ ���� ����
#define RECONFIRM_SEC_GRADE_INIT		72 // 2�� ���� �ʱ�ȭ ���� ����
#define RECONFIRM_AUTO_ROUTING			73 // �ڵ� ���ݱ� ���� ����
#define RECONFIRM_CHKRA_INIT			74 // ��ũ�� �ʱ�ȭ ����
#define RECONFIRM_SKILL_INIT			75 // ��ų �ʱ�ȭ ����
#define RECONFIRM_CHKRA_SKILL_INIT		76 // ��ũ�� �� �ʱ�ȭ ����

#define RECONFIRM_PORTAL_MOVEREQ		101	// ��Ż �̵��� ��û��

#define RECONFIRM_BLOG_GUILD_MAKE		121	// ��ü ȭ������ �ߴ� ��� ��α� ������ �����
#define RECONFIRM_BLOG_GUILD_OPEN		122 // ��ü ȭ������ �ߴ� ��� ��α� ������ �����
#define RECONFIRM_BLOG_PERSONAL			123	// ��ü ȭ������ �ߴ� ���� ��α� ������ �����
#define RECONFIRM_BLOG_OTHERPERSONAL	124	// ��ü ȭ������ �ߴ� �ٸ� ������ ��α� ������ �����
#define RECONFIRM_OPEN_GAMEINTRO		125	// ��ü ȭ������ �ߴ� ���� ���� �Խ��� ������ �����

#define RECONFIRM_DUELSYSTEM			130	//	�����ý���

#define RECONFIRM_ASHURAMGUILDJOIN		140	//	�ƽ������� ��û
#define RECONFIRM_ASHURAMGUILDANSER		141	//	�ƽ������� ��û

#define RECONFIRM_ANSWERUSESAMUDABA		150	//	�繫�ٹ� ��û �޽��� �ް� ��Ȯ��â �������� ����� â

//-----------------------------------------------------------------------------//
// ���� : ���ÿ� ���� �����ۿ� �߰��� ����
// �ۼ����� / �ۼ��� : 2003.10.20 �輱��
//-----------------------------------------------------------------------------//
typedef struct _HTITEM_REFINE_PARAM
{
	HTint		iEffectID;
	HTint		iEffectFunction;
	HTint		iEffectDuration;
	HTint		iEffectParam1;
	HTint		iEffectParam2;
	//HTint		iEffect2ID;
	//HTint		iEffect2Function;
	//HTint		iEffect2Duration;
	//HTint		iEffect2Param1;
	//HTint		iEffect2Param2;
	//HTint		iEffect3ID;
	//HTint		iEffect3Function;
	//HTint		iEffect3Duration;
	//HTint		iEffect3Param1;
	//HTint		iEffect3Param2;
	//HTint		iEffect4ID;
	//HTint		iEffect4Function;
	//HTint		iEffect4Duration;
	//HTint		iEffect4Param1;
	//HTint		iEffect4Param2;
	//HTint		iEffect5ID;
	//HTint		iEffect5Function;
	//HTint		iEffect5Duration;
	//HTint		iEffect5Param1;
	//HTint		iEffect5Param2;
} HTITEM_REFINE_PARAM;

//-----------------------------------------------------------------------------//
// ���� : �������� ���� �� �ִ� �Ӽ� ����
// �ۼ����� / �ۼ��� : 2003.10.20 �輱��
//-----------------------------------------------------------------------------//
#define _ITEM_ATTRIBUTE_FIRE			1
#define _ITEM_ATTRIBUTE_COLD			2
#define _ITEM_ATTRIBUTE_ELECTRIC		3
#define _ITEM_ATTRIBUTE_POISON		4

//-----------------------------------------------------------------------------//
// ���� : ���� ������ ������ �з�
// �ۼ����� / �ۼ��� : 2003.10.21 �輱��
//-----------------------------------------------------------------------------//
// ���� ÷�� ���� ������ �з�(Bit Set)
// 1-����, 2-�Ǻ�, 4-��, 8-�㸮��, 16-�Ź�, 32-����, 64-�׼�����
//#define _REFINE_WEPON_ONEHAND		1
//#define _REFINE_WEPON_TWOHAND		2
//
//#define _REFINE_DEFENCE_SHIELD		4
//#define _REFINE_DEFENCE_ARMOR		8
//#define _REFINE_DEFENCE_HELMET		16
//#define _REFINE_DEFENCE_BELT		32
//#define _REFINE_DEFENCE_SHOES		64
//#define _REFINE_DEFENCE_PANTS		2048
//#define _REFINE_DEFENCE_GLOVES		4096
//
//#define _REFINE_ACCESSORY_EARRING	128
//#define _REFINE_ACCESSORY_BRACELET	256
//#define _REFINE_ACCESSORY_RING		512
//#define _REFINE_ACCESSORY_NECKLACE	1024

//-----------------------------------------------------------------------------//
// ���� : ��ų ���� ��� �з�
// �ۼ����� / �ۼ��� : 2003.10.25 �輱��
//-----------------------------------------------------------------------------//
#define _TARGET_SELF				1		
#define _TARGET_FRIENDLY			2	// field������ PC, �ֽ��������� ���� �ֽ�		
#define _TARGET_FRIENDLY_EXCEPT_ME	3	// �ڽ��� ����
#define _TARGET_ENEMEY				4
#define _TARGET_PARTY				5
#define _TARGET_GUILD				6
#define _TARGET_ALL					7	
#define _TARGET_FRIENDLY_CORPSE		8	// ������ ��ü. ��Ȱ �������� ���
#define _TARGET_ENEMEY_CORPSE		9	// ���� ��ü. ��ü ���� �������� ���. ���� ��븶�� ����
#define _TARGET_GATE				10	// �������� ������ ���

//-----------------------------------------------------------------------------//
// ���� : 
// �ۼ����� / �ۼ��� : 2003.11.24 �輱��
//-----------------------------------------------------------------------------//
#define HT_ITEM_INDEX_START					(HT_PARAMTYPE_ITEM_WEAPON_START-1)
#define HT_ITEM_REFINE_INDEX_START			(HT_PARAMTYPE_ITEM_REFINE_SUB_START-1)

typedef struct _S_ERROR
{
	WORD                          wType;                            // Message ID Field
	WORD                          wSeq;                             // Packet Seq Number Field
	WORD                          wPDULength;                       // PDU Length Field
	int nError;
} S_ERROR, *PS_ERROR;

//-----------------------------------------------------------------------------//
// ���� : MSG_Item �޼��� ������ �ִ� type ����
// �ۼ����� / �ۼ��� : 2003.12.10 �輱��
//-----------------------------------------------------------------------------//
#define HT_MSG_ITEM_USE			0
#define HT_MSG_ITEM_INFO		1

//-----------------------------------------------------------------------------//
// ���� : ������ �ӵ� ���� 
// �ۼ����� / �ۼ��� : 2003.12.19 �輱��
//-----------------------------------------------------------------------------//
#define HT_ITEM_SPEED_VERY_FAST		1
#define HT_ITEM_SPEED_FAST			2
#define HT_ITEM_SPEED_NORMAL		3
#define HT_ITEM_SPEED_SLOW			4
#define HT_ITEM_SPEED_VERY_SLOW		5

//-----------------------------------------------------------------------------//
// ���� : ������ ��ġ ���� 
// �ۼ����� / �ۼ��� : 2004.1.8 �輱��
//-----------------------------------------------------------------------------//
#define HT_ITEM_INFINITY_DURABILITY		25500	// ���� ������
#define HT_ITEM_DURABILITY_DIVIDING		100		// ȭ�鿡 �����ٶ� �������� ������� �� ��
#define HT_ITEM_DURATION_DIVIDING		1000	// ȭ�鿡 �����ٶ� ���ӽð��� ������� �� ��

//-----------------------------------------------------------------------------//
// ���� : ������ �̵�
// �ۼ����� / �ۼ��� : 2003.12.16 �輱��
//-----------------------------------------------------------------------------//
#define HT_RESULT_ITEM_MOVE_OK			1
#define	HT_RESULT_ITEM_MOVE_FAIL		0

//-----------------------------------------------------------------------------//
// ���� : ������/��ų ����
// �ۼ����� / �ۼ��� : 2004.01.28 �輱��
//-----------------------------------------------------------------------------//
#define HT_INFO_ITEM_SELL_DIVIDING_CONST	6
#define HT_INFO_ITEM_DESCRIPT_NULL			_T("null")
#define HT_INFO_SKILL_DESCRIPT_NULL			_T("0")

//-----------------------------------------------------------------------------//
// ���� : ���λ��� ����
// �ۼ����� / �ۼ��� : 2004.02.03 �輱��
//-----------------------------------------------------------------------------//
#define HT_STORE_MODE_START		1
#define HT_STORE_MODE_END		0

//-----------------------------------------------------------------------------//
// ���� : ��ɾ�
// �ۼ����� / �ۼ��� : 2004.02.26 �輱��
//-----------------------------------------------------------------------------//
#define COMMAND_QUICKSLOT_SIT				1
#define COMMAND_QUICKSLOT_WLK				2
#define COMMAND_QUICKSLOT_ATK				3
#define COMMAND_QUICKSLOT_TARGET			4
#define COMMAND_QUICKSLOT_EXCHANGE			5
#define COMMAND_QUICKSLOT_PICKUP			6
#define COMMAND_QUICKSLOT_PARTY				7
#define COMMAND_QUICKSLOT_PARTYWITHDRAW		8
#define COMMAND_QUICKSLOT_SHOP				9
#define COMMAND_QUICKSLOT_PROVOKE			10
#define COMMAND_QUICKSLOT_GREET				11
#define COMMAND_QUICKSLOT_RUSH				12

#define COMMAND_QUICKSLOT_BLOG				14
#define COMMAND_QUICKSLOT_DUEL				15
#define COMMAND_QUICKSLOT_AWAY				16
#define COMMAND_QUICKSLOT_ASSIST			17
#define COMMAND_QUICKSLOT_DIRECTIONS		18
#define COMMAND_QUICKSLOT_STOP				19
#define COMMAND_QUICKSLOT_SIEGE				20

//-----------------------------------------------------------------------------//
// ���� : Ư�� ������ �ε��� ����
// �ۼ����� / �ۼ��� : 2004.08.09 �輱��
//-----------------------------------------------------------------------------//
#define HT_INDEX_DAMAGE_UP					7029 // �ƴ��ٹ��� ����
#define HT_INDEX_SUPERIOR_DAMAGE_UP			6801 // ��� �ƴ��ٹ��� ����(1�ð���)
#define	HT_INDEX_SUPERIOR_DAMAGE_UP2		6810 // ��� �ƴ��ٹ��� ����(4�ð���)
#define HT_INDEX_ITEMNAME_AZEKATA			6838 // ����īŸ ����(4�ð���)
#define HT_INDEX_ITEMNAME_BARUTA			6839 // �ٷ�Ÿ ����(4�ð���)
#define HT_INDEX_ITEMNAME_AZERUTY			6840 // ����ī�� Ÿ�Ľ� ����(4�ð���)

#define HT_INDEX_SELF_REVIVAL				7031 // ������ �ֹ���
#define HT_INDEX_SELF_COMPLTEREVIVAL		7039 // ��� ������ �ֹ���

#define HT_INDEX_INIT_SUB_REFINE			6614 // �Ƹ���(�Ӽ����� �ʱ�ȭ ������)

#define HT_INDEX_EXPAND_INVEN				6951 // �κ�Ȯ��
#define HT_INDEX_EXPAND_SHOP				6952 // ����Ȯ��
#define HT_INDEX_AUTO_ROUTING				6953 // �ڵ� ���ݱ�

#define HT_INDEX_TOTEM_JACUNAEARANI			5802 // ���� �ٶ��(���� ������)

//-----------------------------------------------------------------------------//
// ���� : Ư�� Skill �ε��� ����
// �ۼ����� / �ۼ��� : 2005.06.24 ���Ǳ�
//-----------------------------------------------------------------------------//
#define HT_SKILLINDEX_SAMUDABA				3261

//-----------------------------------------------------------------------------//
// ���� : ��� ��ũ
// �ۼ����� / �ۼ��� : 2005.09.13 ���Ǳ�
//-----------------------------------------------------------------------------//
// normal�� 12��, Ȯ���� 20����
#define	UI_GUILD_BACKTEX_N			28001
#define	UI_GUILD_BACKTEX_B			28013
#define	UI_GUILD_BACKTEX_V			28033
#define	UI_GUILD_BACKTEX_S			28053

#define	UI_GUILD_EMBLEMTEX_N		28401
#define	UI_GUILD_EMBLEMTEX_B		28413
#define	UI_GUILD_EMBLEMTEX_V		28433
#define	UI_GUILD_EMBLEMTEX_S		28453

#define	UI_GUILD_TITLETEX			28601	// ��ũ�� ���ᰡ 24�� �� ���ĺ��� 
#define	UI_GUILD_TITLETEX_EXPAND	28626	// ��ũ�� ���ᰡ 24�� �� ���ĺ��� 

#pragma pack(pop)

#endif