//----------------------------------------------------------------------------//
//	파일 이름	: HTControlDef.h
//
//	파일 설명 	: 
//		- 게임의 전반적인 컨트롤에 쓰일 디파인 변수들을 정의한다.
//
//	작성자		:
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
// 비트 연산에 사용한다.
/*----------------------------------------------------------------------------*/
#define		BIT_AND(value1, value2)	((value1) & (value2))
#define		BIT_OR(value1, value2)	((value1) | (value2))

/*----------------------------------------------------------------------------*/
// 주신
/*----------------------------------------------------------------------------*/
//#define		TRIMURITI_NONE		0//0x00	// 주신 제한 없음
//#define		TRIMURITI_BRAHMA	1//0x01	// 브라흐마
//#define		TRIMURITI_VISHNU	2//0x02	// 비슈누
//#define		TRIMURITI_SIVA		4//0x03	// 시바

/*----------------------------------------------------------------------------*/
// 카스트 등급, 계급
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

//	튜토리얼 시스템
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
//  설명 : Remove MOB 메시지로 날아오는 것 처리할때 캐릭터인지 몬스터인지 체크
//  작성일자 / 작성자 : 2003.11.21 / 정의규
//-----------------------------------------------------------------------------//
#define SERVEROBJECTID_CHARACTER_START				1
#define SERVEROBJECTID_CHARACTER_END				999

#define SERVEROBJECTID_MONSTER_START				1000
#define SERVEROBJECTID_MONSTER_END					9999

#define SERVEROBJECT_IS_CHARACTER( i )		( i >= SERVEROBJECTID_CHARACTER_START ) && ( i <= SERVEROBJECTID_CHARACTER_END ) ? HT_TRUE : HT_FALSE
#define SERVEROBJECT_IS_MONSTER( i )		( i >= SERVEROBJECTID_MONSTER_START ) && ( i <= SERVEROBJECTID_MONSTER_END ) ? HT_TRUE : HT_FALSE

//-----------------------------------------------------------------------------//
//  설명 : 아이틀동작 동작 대기시간
//  작성일자 / 작성자 : 2003.4.28 / 정의규
//-----------------------------------------------------------------------------//
#define IDLE_PC_TIME										15000
#define IDLE_MONSTER_TIME									10000

//-----------------------------------------------------------------------------//
//  설명 : 사운드 관련
//  작성일자 / 작성자 : 2002.7.4 / 정의규
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
//  설명 : 인벤토리 정리
//  작성일자 / 작성자 : 2002.7.4 / 정의규
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
//#define ITEM_LOCATION_CHATURANGA_BOARD				4	// 차투랑가 보드 - 선영범 (사용안함)
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
//  설명 : 게임 시퀸스 관련
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
#define GAMESEQUNCE_MAINGAME_NONE						0
#define GAMESEQUNCE_MAINGAME_RECEIVEINITCHAR			1
#define GAMESEQUNCE_MAINGAME_DONEINITCHAR				2
#define GAMESEQUNCE_MAINGAME_GMAEPLAY					3

#define GAMESEQUNCEBIG_INTRO							0
#define GAMESEQUNCEBIG_MAIN								1


//-----------------------------------------------------------------------------//
//  설명 : 카메라 관련
//  작성일자 / 작성자 : 정의규
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
//  설명 : 리턴값 관련
//  작성일자 / 작성자 : 정의규
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
//  설명 : 인벤토리 / 아이템 관련
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
#define ITEM_ACTION_NONE								0
#define ITEM_ACTION_DOING								1
#define ITEM_ACTION_ONINVENTORY							2

//-----실재 아이템-----//
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
//  설명 : 캐릭터 관련
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//
//	ChangeAni 로 영향받는 Animation
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
//	각자의 함수가 있는 애니매이션
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
//  설명 : 네트워크 연결 관련
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//
#define STATUS_CONNECTING							0x00
#define STATUS_ALIVE								0x01
#define STATUS_DISCONNECT							0x02
#define STATUS_NONE									0xFF

//-----------------------------------------------------------------------------//
//  설명 : 인덱스 디파인 관련!
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
#define	ITEMINDEX_ASSISTANTHAT							6555

//-----------------------------------------------------------------------------//
//  설명 : 아이콘이 움직이는지 않움직이는지 체크
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
#define ICON_STATUS_NONE								1
#define ICON_STATUS_MOVE								2

//-----------------------------------------------------------------------------//
//  설명 : 서버가 테스트서버인지 메인서버인지 구분
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
#define SERVERTYPE_TEST									0
#define SERVERTYPE_MAIN									1

//-----------------------------------------------------------------------------//
//  설명 : 칼라 테이블
//  작성일자 / 작성자 : 2004.02.03 / 정의규
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
//  설명 : 동시접속 제한인원
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//
#define CONNECTNUM_SERVERLIMIT							999
#define CONNECTNUM_CLIENTLIMIT							920

//-----------------------------------------------------------------------------//
//  설명 : Zone Index Name / Map size
//  작성일자 / 작성자 : 
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

#define MAP_MANDARA_1ST									40001	// 만다라마을1st
#define MAP_MANDARA_2ND									40002	// 만다라마을2nd
#define MAP_MANDARA_DUNGEON_1ST							40003	// 만다라던전1st
#define MAP_MANDARA_DUNGEON_2ND							40004	// 만다라던전2nd
#define MAP_MANDARA_DUNGEON_3RD							40005	// 만다라던전3rd
#define MAP_MANDARA_DUNGEON_4TH							40006	// 만다라던전4th
#define MAP_JINA_1ST									40007	// 지나마을1st
#define MAP_JINA_2ND									40008	// 지나마을2nd
#define MAP_JINA_3RD									40009	// 지나마을3rd
#define MAP_JINA_4TH									40010	// 주신전 맵 아이디
#define MAP_JINA_GUILD									40011	// 지나마을길드
#define MAP_JINA_7TH_CAVE								40012	// 북두성군묘

#define MAP_EVENT_LOWKALIA								40013	// 초급칼리야
#define MAP_EVENT_MIDKALIA								40014	// 중급칼리야
#define MAP_EVENT_HIGHKALIA								40015	// 고급칼리야
#define MAP_ARENA_DURGA									40016	// Arena_Durga
#define MAP_KATHANA3_BIRYUCASTLE						40017	// BiryuCastle
#define MAP_LOWKRUMA									40020	// LowKruma
//fors_debug add map_info 21
#define MAP_K3DOWN   									40021	// LowKruma

#define MAP_INTRO										40100	// 인트로

#define HT_IS_TRIMURITIZONE( i )			( i == ZONE_KURUMA ) || ( i == ZONE_CHATURANGGA ) || ( i == ZONE_ANAKAKURUMA )  ? HT_OK : HT_FAIL
#define HT_IS_FORETRESSZONE( i )			( i == ZONE_FORTRESS ) ? HT_OK : HT_FAIL
#define HT_IS_BIRYUCASTLE( i )				( i == ZONE_BIRYUCASTLE ) ? HT_OK : HT_FAIL
#define HT_IS_MOBGATE( i )					( i == 2295 ) || ( i == 2305 ) || ( i == 2308 ) || ( i == 2311 ) || ( i == 2252 ) || ( i == 2253 ) || ( i == 2254 ) || ( i == 2255 ) || ( i == 2934 ) || ( i == 2935 ) || ( i == 2936 ) || ( i == 2937 ) || ( i == 2846 ) || ( i == 2847 ) || ( i == 2848 ) || ( i == 2445 ) || ( i == 2446 ) ? HT_OK : HT_FAIL
#define HT_IS_MOBSUMMONS( i )				( i == 2801 ) || ( i == 2802 ) || ( i == 2803 ) || ( i == 2467 ) || ( i == 2468 ) || ( i == 2804 ) || ( i == 2805 ) || ( i == 2806 ) || ( i == 2807 ) || ( i == 2808 ) || ( i == 2809 ) || ( i == 2448 ) || ( i == 2449 ) || ( i == 2450 ) || ( i == 2465 ) || ( i == 2466 ) ? HT_OK : HT_FAIL
#define HT_IS_CANNOTMOVEITEM( i )			( i == 6736 ) || ( i == 7074 ) || ( i == 7410 ) ? HT_OK : HT_FAIL

//-----------------------------------------------------------------------------//
//  설명 : IME Define
//  작성일자 / 작성자 : 2004.04.06 / 정의규
//-----------------------------------------------------------------------------//
#define INPUTMODE_NORMAL								0
#define INPUTMODE_IME									1

#define COMPOSITION_COMPSTR								0
#define COMPOSITION_RESULTSTR							1

//-----------------------------------------------------------------------------//
//  설명 : 국가번호/국가타입
//  작성일자 / 작성자 : 2004.08.23 / 정의규
//-----------------------------------------------------------------------------//
#define	INATIONALTYPE_KOREA								0
#define	INATIONALTYPE_CHINA								1
#define	INATIONALTYPE_INDONESIA							2
#define	INATIONALTYPE_PHILIPPINE						3
#define	INATIONALTYPE_JAPEN								4
#define	INATIONALTYPE_TAIWAN							5
#define	INATIONALTYPE_MEXICO							6

//-----------------------------------------------------------------------------//
//  설명 : Potal Mob ID
//  작성일자 / 작성자 : 2004.06.09 / 정의규
//-----------------------------------------------------------------------------//
#define FORPOTAL_MOBID_FORCHATURANGR					2946
#define FORPOTAL_MOBID_FORTRIMURITICAVE					2202

//-----------------------------------------------------------------------------//
//  설명 : Guild Authority
//  작성일자 / 작성자 : 2004.10.13 / 정의규
//-----------------------------------------------------------------------------//
#define	GUILD_AUTHORITY_MAHARAJA			10	// 길드 마하라자
#define	GUILD_AUTHORITY_RAJA				9	// 길드 라자
#define	GUILD_AUTHORITY_PROOBAJA			8	// 길드 프루바자
#define	GUILD_AUTHORITY_DANEACA				7	// 길드 단디카
#define	GUILD_AUTHORITY_TAPASA				6	// 길드 타파사
#define	GUILD_AUTHORITY_NONE				0	// 길드 0

//-----------------------------------------------------------------------------//
//  설명 : 포인트 과련해서 2D, 3d
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//
typedef struct _HTPoint
{
	int x, y;
} HTPoint;

//-----------------------------------------------------------------------------//
//  설명 : 키 / 마우스 입력을 입시 저장하여 각 알고리즘에 활용
//  작성일자 / 작성자 : 정의규
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
//  설명 : 
//  작성일자 / 작성자 : 
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
//  설명 : 아이템의 위치와 방를 반환
//  작성일자 / 작성자 : 정의규 / 2002.11.11
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
//  설명 : 각 인벤토리 아이템을 셋팅시킬 때
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//
typedef struct _HT_ITEMSETTING_FLAG
{
	HTint					nLocation;
	HTint					nInventory;
	//HTvector3				vecWindowPos;
	HTPoint					pCellPos;

} HT_ITEMSETTING_FLAG;

//-----------------------------------------------------------------------------//
//  설명 : 스킬
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
typedef struct _HT_SKILLINSERT_FLAG
{	
	DWORD					dwSkill_Index;
	BYTE					bySkill_Level;
	BYTE					bySkill_Type;
	BYTE					bySkill_Count;

} HT_SKILLINSERT_FLAG;

//	스킬 인벤토리와 시스템의 연결을 위해_시스템에서 배열을 얻어온다.
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

	short                   snMovingSpeed;// 아이템의 이동속도
	short                   snAttackSpeed;// 아이템의 공격속도
	short                   snCastingSpeed;// 아이템의 케스팅속도
	BYTE                    byShootRange; // 발사체의 사정거리

	//-----0:왼손, 1:오른손, 2:단축스킬창, 3:인벤토리1
	BYTE					bSkill_Location;
	BYTE					bSkill_InvenCellX;
	BYTE					pSkill_InvenCellY;

} HT_SKILLCREATE_FLAG;


//-----------------------------------------------------------------------------//
//  설명 : 공격 관련
//  작성일자 / 작성자 : 
//-----------------------------------------------------------------------------//  
typedef struct _HT_ATTACKCREATE_FLAG
{
   BYTE						Attack_TypeMO_Other;
   DWORD					Attack_ID;			//	공격 한 자의 모델 ID
   DWORD					Attack_KeyID;		//	공격 한 자의 Key_ID
   HTPoint					Attack_Pos;			//	공격 지점
   BYTE						Attack_Type;		//	공격 타입 -> 0x00:Skill, 0x01:Item, 0x02:맨손
   HTint					Attack_Kind;
   HTint					Attack_Item_KeyID;	//	공격에 사용한 아이템의 KeyID
   HTint					Attack_Item_Index;	//	공격에 사용한 아이템의 Index
   HTint					Attack_Skill_Index;	//	공격에 사용한 스킬의 index

   HTint					DisAttack_ID;		//	공격당 한 자의 모델 ID
   DWORD					DisAttack_KeyID;	//	공격당 한 자의 Key_ID
   HTPoint					DisAttack_Pos;		//	공격 타겥 지점
   short					DisAttack_snDegree;	//  각도
   
} HT_ATTACKCREATE_FLAG;


//----------------------------------------------------------------------------//
//	파일 이름	: HTControlDef.h
//
//	파일 설명 	: 
//		- 서버
//
//	작성자		:
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
// 설명 : 스킬과 아이템 정보창에 표시할 데이터의 목록
// 작성일자 / 작성자 : 2002.12.26 김선미
//-----------------------------------------------------------------------------//
//----------- 아이템 일반 정보 ----------//
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
	HT_ITEM_DATA			strName;				// 아이템 이름
	HT_ITEM_DATA			strDescription;			// 아이템 설명
	vector<HT_ITEM_DATA*>	vLimitStr;				// 제한 사항
	vector<HT_ITEM_DATA*>	vSourceStr;				// 재료
	vector<HT_ITEM_EXPANSION_DATA*>	vAttributeStr;	// 특성
} HT_ITEMINFO;

//-----------------------------------------------------------------------------//
//  설명 : World Server Infomation
//  작성일자 / 작성자 : 2002.07.30  작성자 : 윤우경
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
//	설명 : 퀘스트 이벤트의 진행 상태
//	작성일자 / 작성자 : 2003.04.17 김선미
//------------------------------------------------------------------------------//
#define QUEST_STATUS_NONE		0x00		// 퀘스트 없음
#define QUEST_STATUS_START		0x01		// 시작
#define QUEST_STATUS_PROGRESS	0x02		// 진행중
#define QUEST_STATUS_REJECTION	0x03		// 거부		// 2003.07.09 선미 추가
#define QUEST_STATUS_FAIL		0xfe		// 실패
#define QUEST_STATUS_SUCCESS	0xff		// 완료

#define QUEST_STATUS_0			0			
#define QUEST_STATUS_1			1			// 1차
#define QUEST_STATUS_2			2			// 2차
#define QUEST_STATUS_3			3			// 3차
#define QUEST_STATUS_4			4			// 4차
#define QUEST_STATUS_5			5			// 5차

//------------------------------------------------------------------------------//
//	설명 : 차크라 포인트
//	작성일자 / 작성자 : 2003.04.22 김선미
//------------------------------------------------------------------------------//
#define CHAKRA_POINT_MUSCLE		0
#define CHAKRA_POINT_NERVE		1
#define CHAKRA_POINT_HEART		2
#define CHAKRA_POINT_SOUL		3
#define BRAHMAN_POINT			4

//------------------------------------------------------------------------------//
//	설명 : 아이템 정보 구할때 구입/제련 모드 구분
//	작성일자 / 작성자 : 2003.05.13 김선미
//------------------------------------------------------------------------------//
#define NPC_ITEM_MAKING			0
#define NPC_ITEM_REFINING		1
#define NPC_ITEM_SELL			2
#define NPC_ITEM_RENTAL_SELL	3
//fors_debug 속된섬꼇列돛왠齡痂척돨
#define MAX_REFINE_MAIN_LEVEL	15	// 최대 강화 제련 가능 횟수
#define MAX_REFINE_SUB_LEVEL	10	// 최대 주술 제련 가능 횟수
#define MAX_EFFECT_NUM			5	// 한 아이템의 최대 Effect 개수
//------------------------------------------------------------------------------//
//	설명 : 커서
//	작성일자 / 작성자 : 2003.05.19 김선미
//------------------------------------------------------------------------------//
#define CURSOR_ARROW_1		0		// 화살표(arrow) 커서
#define CURSOR_ARROW_2		1
#define CURSOR_HAND_1		2		// 손(hand) 커서
#define CURSOR_HAND_2		3
#define CURSOR_HAND_ANI		4		// 움직이는 손(hand) 커서
#define CURSOR_SWORD		5		// 칼(sword) 커서
#define CURSOR_SWORD_ANI	6		// 움직이는 칼(sword) 커서
#define CURSOR_NPC			7		// 대화(NPC) 커서
#define CURSOR_NPC_ANI		8
#define CURSOR_REPAIR		9		// 수리(repair) 커서
#define CURSOR_REPAIR_ANI	10
#define CURSOR_REPAIRD		11		// 수리 불가 커서
#define CURSOR_ADDRESS		12		// Address 화살표(arrow) 커서
#define CURSOR_ADDRESS_ANI	13
#define CURSOR_PARTY		14		// Party 화살표(arrow) 커서
#define CURSOR_PARTY_ANI	15
#define CURSOR_TRADE		16		// Trade 화살표(arrow) 커서
#define CURSOR_TRADE_ANI	17
#define CURSOR_RBUTTON		18		// 오른쪽 버튼 클릭
#define CURSOR_BLOG			19		// Blog 커서
#define CURSOR_BLOG_ANI		20
#define CURSOR_SELECT		21		// SELECT 커서
#define CURSOR_SELECT_ANI	22
//------------------------------------------------------------------------------//
//	설명 : 내 트레이드 창에 언패킹된 아이템을 위한 구조체
//	작성일자 / 작성자 : 2003.05.20 김선미
//------------------------------------------------------------------------------//
typedef struct _HT_MYEXCHANGE_ITEM
{
	DWORD	dwKeyID;		// 교환창에 추가한 아이템의 KeyID
	DWORD	dwIndex;		// 교환창에 추가한 아이템의 Index
	short	snCurDurability;
	int		nItemCount;		// 교환창에 추가한 아이템의 수량
	short	snX;			// 교환창내의 아이템 X 좌표
	short	snZ;			// 교환창내의 아이템 Z 좌표
} HT_MYEXCHANGE_ITEM;

//------------------------------------------------------------------------------//
//	설명 : 
//	작성일자 / 작성자 : 정의규
//------------------------------------------------------------------------------//
typedef struct _ATTACK_FACTOR
{
	CHTString strAttackName;			//	공격자의 이름
	BYTE byTribe;						//	공격한 종족
	DWORD dwAttackKeyID;				//	공격자의 키 아이디
	DWORD dwTargetKeyID;				//	공격대상의 키 아이디
	HTint nAttackType;					//	0x01:일반공격, 0x02:스킬공격
	HTfloat fDirect;					//	공격자의 방향
	HTvector3 vecSourcePos;				//	공격자의 위치
	HTvector3 vecTargetPos;				//	공격받은자의 위치
	HTint nCharModelID;					//	공격자의 모델 아이디
	HTint iTargetModelID;				//	공격받은자의 모델 아이디
	HTint nAttackItemID;				//	공격자의 무기 인덱스
	HTint nAttackSkillID;				//	공격자의 스킬 인덱스
	BYTE  byAttackSkillIDLevel;			//	공격자의 스킬 레벨
	BYTE byAttackSkillAttribute;		//	공격자의 스킬 속성

} S_ATTACK_FACTOR, * P_ATTACK_FACTOR;


typedef struct _MSG_ATTACK_OTHERMOB
{
	HTint				iCasterHP;
	HTint				iSkillID;					//	사용한 스킬
	unsigned short		PosX,		PosY;
	unsigned short		TargetX,	TargetZ;		//	상대방의 좌표
	short               snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:장애물충돌 ...)
    HTint				iTargetModelID;
	HTvector3			vecTargetPos;
	DWORD				dwDurationTime;
	HTshort				snSkillLevel;
	S_TNTARGET_DATA     krgTarget[TN_MAX_TARGET_COUNT] ;

} S_MSG_ATTACK_OTHERMOB;




// 길드 데이터 단위
struct S_GUILD_DATA {
	STRUCT_GUILD_MEMBER			info;
	struct S_GUILD_DATA*		pNextNode;
};

//-------------------------------------------------------------------------------//
// 설명 : 퀘스트 목록
// 작성일자 / 작성자 : 2003.06.27 김선미
//-------------------------------------------------------------------------------//
#define TUTORIAL_QUEST_START		1	// 튜토리얼 퀘스트 
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

// 만다라 퀘스트
//#define SCENARIO_QUEST_1_START		11	// 1차 시나리오 퀘스트 
#define SCENARIO_QUEST_1_START		6	// 1차 시나리오 퀘스트 
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

// 샴발라 퀘스트
#define SCENARIO_QUEST_2_START		21	// 2차 시나리오 퀘스트 
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

#define QUEST_SHAMBALA_11	31 // 2차 전직
#define QUEST_SHAMBALA_12	32 // 2차 전직 - 파괴의 시험
#define QUEST_SHAMBALA_13	33 // 2차 전직 - 인내의 시험
#define QUEST_SHAMBALA_14	34 // 2차 전직 - 지혜의 시험
#define QUEST_SHAMBALA_15	35 // 2차 전직 - 의리의 시험

// 지나 퀘스트
#define SCENARIO_QUEST_3_START		36
#define SCENARIO_QUEST_3_END		40
#define QUEST_JINA_1				36
#define QUEST_JINA_2				37
#define QUEST_JINA_3				38
#define QUEST_JINA_4				39
#define QUEST_JINA_5				40

// 유배지 퀘스트 2005. 2. 16
#define SCENARIO_QUEST_4_START		41
#define SCENARIO_QUEST_4_END		45
#define QUEST_JINA2_1				41
#define QUEST_JINA2_2				42
#define QUEST_JINA2_3				43
#define QUEST_JINA2_4				44
#define QUEST_JINA2_5				45

// 북두성군 퀘스트 2005. 9. 13
#define SCENARIO_QUEST_5_START		46
#define SCENARIO_QUEST_5_END		50
#define QUEST_JINA3_1				46
#define QUEST_JINA3_2				47
#define QUEST_JINA3_3				48
#define QUEST_JINA3_4				49
#define QUEST_JINA3_5				50

// 카타나3 퀘스트 2006. 3. 14
#define SCENARIO_QUEST_6_START		51
#define SCENARIO_QUEST_6_END		55
#define QUEST_K3_1					51
#define QUEST_K3_2					52
#define QUEST_K3_3					53
#define QUEST_K3_4					54
#define QUEST_K3_5					55

// 독립 퀘스트
#define QUEST_INDEPENDENCE_1	81
#define QUEST_INDEPENDENCE_2	82

//-------------------------------------------------------------------------------//
// 설명 : 아이템 분류 번호
// 작성일자 / 작성자 : 2003.07.20 김선미
// 1-일반 아이템(무기구/방어구/액세서리 등등), 2-소모성 아이템, 3-보조재료
// 4-수집재료, 5-복권, 6-퀘스트
//-------------------------------------------------------------------------------//
#define	ITEM_CLASS_ITEM						1
#define	ITEM_CLASS_USE						2
#define	ITEM_CLASS_SUB_METERIAL				3
#define	ITEM_CLASS_COLLECTION_METERIAL		4
#define	ITEM_CLASS_LOTTERY					5
#define	ITEM_CLASS_QUEST					6

//-------------------------------------------------------------------------------//
// 설명 : 아이템 타입 
// 작성일자 / 작성자 : 2003.10.21 김선미
//-------------------------------------------------------------------------------//
#define _ITEM_TYPE_WEPON_ONEHAND			1	
#define _ITEM_TYPE_WEPON_TWOHAND			2

#define _ITEM_TYPE_WEPON_SWORD				1	// 검
#define _ITEM_TYPE_WEPON_AX					2	// 도끼
#define _ITEM_TYPE_WEPON_LANCE				4	// 창
#define _ITEM_TYPE_WEPON_MACE				8	// 둔기
#define _ITEM_TYPE_WEPON_GLOVE				16	// 격투
#define _ITEM_TYPE_WEPON_WAND				32	// 마법
#define _ITEM_TYPE_WEPON_BOW				64	// 투척
#define _ITEM_TYPE_WEPON_DAGGER				128	// 단검

#define _ITEM_TYPE_DEFENCE_SHIELD			4
#define _ITEM_TYPE_DEFENCE_ARMOR			8		// 갑옷
#define _ITEM_TYPE_DEFENCE_HELMET			16
#define _ITEM_TYPE_DEFENCE_BELT				32
#define _ITEM_TYPE_DEFENCE_SHOES			64
#define _ITEM_TYPE_DEFENCE_PANTS			2048	// 바지
#define _ITEM_TYPE_DEFENCE_GLOVES			4096	// 장갑

#define _ITEM_TYPE_ACCESSORY_EARRING		128		// 귀걸이
#define _ITEM_TYPE_ACCESSORY_NECKLACE		256		// 목걸이
#define _ITEM_TYPE_ACCESSORY_RING			512		// 반지
#define _ITEM_TYPE_ACCESSORY_BRACELET		1024	// 팔찌

#define _ITEM_TYPE_ACCESSORY_EXPANDINVEN	20		// 인벤확장
#define _ITEM_TYPE_USABLE_POSION			21		// 물약
//#define _ITEM_TYPE_USABLE_WASTE				22	// 소모
//#define _ITEM_TYPE_REFINE					23	// 제련
//#define _ITEM_TYPE_COLLECT					130	// 수집
//#define _ITEM_TYPE_QUEST					25	// 퀘스트 

//--------------------------------------------------------------------------------//
// 설명 : 아이템 이동 상태
// 작성일자 / 작성자 : 2003.08.21 김선미
//---------------------------------------------------------------------------------//
#define ITEMCONTROL_STATUS_NONE				1	// 정지
#define ITEMCONTROL_STATUS_MOVE				2	// 이동

//--------------------------------------------------------------------------------//
// 설명 : 확인/재확인 메세지 창을 발생 시키는 요인 분류
// 작성일자 / 작성자 : 2003.09.03 김선미
//---------------------------------------------------------------------------------//
//-------- 확인 -----------//
#define CONFIRM_NPCCONTROL_NPC			1	// NPC와의 에러(거리제한)
#define CONFIRM_NPCCONTROL_ITEM			2	// 아이템 구입
#define CONFIRM_NPCCONTROL_REFINING		3	// 제련
#define CONFIRM_NPCCONTROL_FIX			4	// 수리
#define CONFIRM_NPCCONTROL_DISJOINT		5	// 판매
#define CONFIRM_NPCCONTROL_BARTER_OK	6	// 교환창에서 물품판매
#define CONFIRM_NPCCONTROL_BARTER_ERR	7	
#define CONFIRM_NPCCONTROL_CHAKRA		8	// 차크라 확장
#define CONFIRM_NPCCONTROL_BRAHMAN		9	// 브라만 확장
#define CONFIRM_NPCCONTROL_SKILL		10	// 스킬 습득
#define CONFIRM_NPCCONTROL_SKILL_DEL	11	// 스킬 삭제
#define CONFIRM_NPCCONTROL_TRADE		12	// 거래소
#define CONFIRM_NPCCONTROL_ITEM_COUNT	13	// 아이템 구입개수
#define CONFIRM_NPCCONTROL_TRIMURITI	14	// 주신 선택/변경
#define CONFIRM_NPCCONTROL_COUPON_NUM_ERR	15	// 쿠폰 번호 오류
#define CONFIRM_NPCCONTROL_COUPON_ERR	16	// 쿠폰 등록 오류

#define CONFIRM_ITEMCONTROL_INVEN_SLOT	21	// 인벤 확장
#define CONFIRM_ITEMCONTROL_MINIMIZE	22	// 인벤토리 확장 해제	
#define CONFIRM_ITEMCONTROL_ITEM_USE	23	// 아이템 사용
#define CONFIRM_ITEMCONTROL_UNPACKING	24	// 아이템 분해

#define CONFIRM_INVEN_RUPIAH_MOVE		31	// 루피아 이동
#define CONFIRM_INVEN_MINIMIZE			32	// 인벤토리 확장 해제

#define CONFIRM_QUEST_ERROR				41	// 퀘스트 에러

#define CONFIRM_SKILL_LEVEL_UP			51	// 스킬 레벨 업

#define CONFIRM_EXCHANGE_REFUSE			61	// 아이템 교환 요청 거절

#define CONFIRM_CHARACTER_REBIRTH		71	// 저장지역에서 다시 태어납니다.

#define INFORWIN_PRIVATESHOP_WARNING	81 // 개인상점 경고
#define INFORWIN_PK_WARNING				82 // PK 경고
#define INFORWIN_OFFERING_NOTIFY		83 // 헌납 설명

#define CONFIRM_BLOGOPEN_ERR			85

#define CONFIRM_CASH_PAY_ERR			99 // 결제 페이지 오류 안내

#define CONFIRM_DUELSYSTEM				110	//	결투시스템
//------- 재확인 ---------//
#define RECONFIRM_NPCCONTROL_ITEM				1	// 아이템 구입
#define RECONFIRM_NPCCONTROL_REFINING			2	// 제련	
#define RECONFIRM_NPCCONTROL_DISJOINT			3	// 판매
#define RECONFIRM_NPCCONTROL_SAVEPOSITION		4	// 위치 저장
#define RECONFIRM_NPCCONTROL_COUPONREGISTER		5	// 쿠폰 등록
#define RECONFIRM_NPCCONTROL_TRIMIRITICHANGE	6	// 주신 변경

#define RECONFIRM_QUEST_TUTORIAL_START	11	// 초보자 퀘스트 시작 재확인

#define RECONFIRM_ITEMCONTROL_ITEM_DROP			16	// 아이템 버리기
#define RECONFIRM_ITEMCONTROL_INIT_CHAKRA		17	// 차크라 초기화
#define RECONFIRM_ITEMCONTROL_INIT_SKILL		18	// 스킬 초기화
#define RECONFIRM_ITEMCONTROL_CHTURANGA_ENTER	19	// 차투랑가 입장권 사용여부

#define RECONFIRM_SKILL_LEVEL_UP		21	// 스킬 레벨 업

#define RECONFIRM_EXCHANGE_REQ			31	// 아이템 교환 요청 
#define RECONFIRM_EXCHANGE_RECEIVE		32	// 아이템 교환 요청 받음
#define RECONFIRM_USING_ITEM			33	// 아이템 사용여부


#define RECONFIRM_PARTY_RECEIVE_JOIN	41 // 파티 요청 받음
#define RECONFIRM_PARTY_DELETE_MEMBER	42 // 파티 멤버 퇴출
#define RECONFIRM_PARTY_DISSOLUTION		43 // 파티 해체
#define RECONFIRM_PARTY_SECESSION		44 // 파티 탈퇴

#define RECONFIRM_ADDRESS_REQ_JOIN		51	// 주소록 등록 요청
#define RECONFIRM_ADDRESS_RECEIVE_JOIN	52	// 주소록 등록 요청 받음
#define RECONFIRM_ADDRESS_DELETE_MEMBER	53	// 멤버 삭제 

#define RECONFIRM_INVENTORY_MONEY_DROP	61	// 돈 버리기

#define RECONFIRM_INVENTORY_EXPAND		70 // 인벤토리 확장 아이템 구입 여부
#define RECONFIRM_EQU_INVENTORY_EXPAND	71 // 개인상점 인벤토리 확장 아이템 구입 여부
#define RECONFIRM_SEC_GRADE_INIT		72 // 2차 전직 초기화 구입 여부
#define RECONFIRM_AUTO_ROUTING			73 // 자동 돈줍기 구입 여부
#define RECONFIRM_CHKRA_INIT			74 // 차크라 초기화 여부
#define RECONFIRM_SKILL_INIT			75 // 스킬 초기화 여부
#define RECONFIRM_CHKRA_SKILL_INIT		76 // 차크라 및 초기화 여부

#define RECONFIRM_PORTAL_MOVEREQ		101	// 포탈 이동을 요청함

#define RECONFIRM_BLOG_GUILD_MAKE		121	// 전체 화면으로 뜨는 길드 블로그 오픈을 경고함
#define RECONFIRM_BLOG_GUILD_OPEN		122 // 전체 화면으로 뜨는 길드 블로그 오픈을 경고함
#define RECONFIRM_BLOG_PERSONAL			123	// 전체 화면으로 뜨는 개인 블로그 오픈을 경고함
#define RECONFIRM_BLOG_OTHERPERSONAL	124	// 전체 화면으로 뜨는 다른 개인의 블로그 오픈을 경고함
#define RECONFIRM_OPEN_GAMEINTRO		125	// 전체 화면으로 뜨는 게임 정보 게시판 오픈을 경고함

#define RECONFIRM_DUELSYSTEM			130	//	결투시스템

#define RECONFIRM_ASHURAMGUILDJOIN		140	//	아쉬람연합 신청
#define RECONFIRM_ASHURAMGUILDANSER		141	//	아쉬람연합 신청

#define RECONFIRM_ANSWERUSESAMUDABA		150	//	사무다바 요청 메시지 받고 재확인창 누르는지 물어보는 창

//-----------------------------------------------------------------------------//
// 설명 : 제련에 의해 아이템에 추가된 정보
// 작성일자 / 작성자 : 2003.10.20 김선미
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
// 설명 : 아이템이 가질 수 있는 속성 종류
// 작성일자 / 작성자 : 2003.10.20 김선미
//-----------------------------------------------------------------------------//
#define _ITEM_ATTRIBUTE_FIRE			1
#define _ITEM_ATTRIBUTE_COLD			2
#define _ITEM_ATTRIBUTE_ELECTRIC		3
#define _ITEM_ATTRIBUTE_POISON		4

//-----------------------------------------------------------------------------//
// 설명 : 제련 가능한 아이템 분류
// 작성일자 / 작성자 : 2003.10.21 김선미
//-----------------------------------------------------------------------------//
// 예전 첨가 가능 아이템 분류(Bit Set)
// 1-무기, 2-의복, 4-방어구, 8-허리띠, 16-신발, 32-모자, 64-액세서리
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
// 설명 : 스킬 적용 대상 분류
// 작성일자 / 작성자 : 2003.10.25 김선미
//-----------------------------------------------------------------------------//
#define _TARGET_SELF				1		
#define _TARGET_FRIENDLY			2	// field에서는 PC, 주신전에서는 같은 주신		
#define _TARGET_FRIENDLY_EXCEPT_ME	3	// 자신을 제외
#define _TARGET_ENEMEY				4
#define _TARGET_PARTY				5
#define _TARGET_GUILD				6
#define _TARGET_ALL					7	
#define _TARGET_FRIENDLY_CORPSE		8	// 동료의 시체. 부활 마법에서 사용
#define _TARGET_ENEMEY_CORPSE		9	// 적의 시체. 시체 폭파 마법에서 사용. 현재 사용마법 없음
#define _TARGET_GATE				10	// 공성전시 성문에 사용

//-----------------------------------------------------------------------------//
// 설명 : 
// 작성일자 / 작성자 : 2003.11.24 김선미
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
// 설명 : MSG_Item 메세지 보낼때 넣는 type 종류
// 작성일자 / 작성자 : 2003.12.10 김선미
//-----------------------------------------------------------------------------//
#define HT_MSG_ITEM_USE			0
#define HT_MSG_ITEM_INFO		1

//-----------------------------------------------------------------------------//
// 설명 : 아이템 속도 종류 
// 작성일자 / 작성자 : 2003.12.19 김선미
//-----------------------------------------------------------------------------//
#define HT_ITEM_SPEED_VERY_FAST		1
#define HT_ITEM_SPEED_FAST			2
#define HT_ITEM_SPEED_NORMAL		3
#define HT_ITEM_SPEED_SLOW			4
#define HT_ITEM_SPEED_VERY_SLOW		5

//-----------------------------------------------------------------------------//
// 설명 : 내구도 수치 관련 
// 작성일자 / 작성자 : 2004.1.8 김선미
//-----------------------------------------------------------------------------//
#define HT_ITEM_INFINITY_DURABILITY		25500	// 무한 내구도
#define HT_ITEM_DURABILITY_DIVIDING		100		// 화면에 보여줄때 내구도에 나눠줘야 할 수
#define HT_ITEM_DURATION_DIVIDING		1000	// 화면에 보여줄때 지속시간에 나눠줘야 할 수

//-----------------------------------------------------------------------------//
// 설명 : 아이템 이동
// 작성일자 / 작성자 : 2003.12.16 김선미
//-----------------------------------------------------------------------------//
#define HT_RESULT_ITEM_MOVE_OK			1
#define	HT_RESULT_ITEM_MOVE_FAIL		0

//-----------------------------------------------------------------------------//
// 설명 : 아이템/스킬 정보
// 작성일자 / 작성자 : 2004.01.28 김선미
//-----------------------------------------------------------------------------//
#define HT_INFO_ITEM_SELL_DIVIDING_CONST	6
#define HT_INFO_ITEM_DESCRIPT_NULL			_T("null")
#define HT_INFO_SKILL_DESCRIPT_NULL			_T("0")

//-----------------------------------------------------------------------------//
// 설명 : 개인상점 정보
// 작성일자 / 작성자 : 2004.02.03 김선미
//-----------------------------------------------------------------------------//
#define HT_STORE_MODE_START		1
#define HT_STORE_MODE_END		0

//-----------------------------------------------------------------------------//
// 설명 : 명령어
// 작성일자 / 작성자 : 2004.02.26 김선미
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
// 설명 : 특정 아이템 인덱스 선언
// 작성일자 / 작성자 : 2004.08.09 김선미
//-----------------------------------------------------------------------------//
#define HT_INDEX_DAMAGE_UP					7029 // 아누바바의 부적
#define HT_INDEX_SUPERIOR_DAMAGE_UP			6801 // 고급 아누바바의 부적(1시간용)
#define	HT_INDEX_SUPERIOR_DAMAGE_UP2		6810 // 고급 아누바바의 부적(4시간용)
#define HT_INDEX_ITEMNAME_AZEKATA			6838 // 아즈카타 부적(4시간용)
#define HT_INDEX_ITEMNAME_BARUTA			6839 // 바루타 부적(4시간용)
#define HT_INDEX_ITEMNAME_AZERUTY			6840 // 아파카야 타파스 부적(4시간용)

#define HT_INDEX_SELF_REVIVAL				7031 // 생명의 주문서
#define HT_INDEX_SELF_COMPLTEREVIVAL		7039 // 고급 생명의 주문서

#define HT_INDEX_INIT_SUB_REFINE			6614 // 아말라(속성제련 초기화 아이템)

#define HT_INDEX_EXPAND_INVEN				6951 // 인벤확장
#define HT_INDEX_EXPAND_SHOP				6952 // 상점확장
#define HT_INDEX_AUTO_ROUTING				6953 // 자동 돈줍기

#define HT_INDEX_TOTEM_JACUNAEARANI			5802 // 자쿠나 다라니(토템 아이템)

//-----------------------------------------------------------------------------//
// 설명 : 특정 Skill 인덱스 선언
// 작성일자 / 작성자 : 2005.06.24 정의규
//-----------------------------------------------------------------------------//
#define HT_SKILLINDEX_SAMUDABA				3261

//-----------------------------------------------------------------------------//
// 설명 : 길드 마크
// 작성일자 / 작성자 : 2005.09.13 정의규
//-----------------------------------------------------------------------------//
// normal은 12개, 확장은 20개씩
#define	UI_GUILD_BACKTEX_N			28001
#define	UI_GUILD_BACKTEX_B			28013
#define	UI_GUILD_BACKTEX_V			28033
#define	UI_GUILD_BACKTEX_S			28053

#define	UI_GUILD_EMBLEMTEX_N		28401
#define	UI_GUILD_EMBLEMTEX_B		28413
#define	UI_GUILD_EMBLEMTEX_V		28433
#define	UI_GUILD_EMBLEMTEX_S		28453

#define	UI_GUILD_TITLETEX			28601	// 마크는 무료가 24개 그 이후부터 
#define	UI_GUILD_TITLETEX_EXPAND	28626	// 마크는 무료가 24개 그 이후부터 

#pragma pack(pop)

#endif