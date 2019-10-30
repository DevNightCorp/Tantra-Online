#ifndef _BASEDEF_
#define _BASEDEF_

#include <windows.h>
#include <map>
#include <atltime.h>

#ifndef __CHATSRV__
	#include "CPSock.h"
#endif	//	#ifndef __CHATSERVER__

#ifdef __ZONE_SERVER__
	#include "TNDeck100.h"
#endif

//	#define _ACCOUNTPASS_MD5_CHANGE_
#define _ACCOUNTNAME_LENGTH_52BYTES_
#define		MAX_INT					2000000000
#define		MAX_ENGLISH				400			
#define		DBG_TRACE					// 디버그 트레이스 
#define		APP_VERSION				563
#define		GAME_PORT				18400
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           DEFINE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		DB_PORT					7514      // DB서버의 수신포트

#define		ADMIN_PORT				8895 
#define		TSMON_PORT				15110
#define		BILL_PORT				3010
#define		WHATSUP_PORT			5000	  // What's up 서비스용 포트(중국용)
#define		CHAT_PORT				5555
#define		MAX_ZONE				6
#define		MAX_SERVER				50      // DB서버 1개에 붙을수 있는 Game서버의 갯수
#define		MAX_SERVERGROUP			10
#define		MAX_SERVERNUMBER		(MAX_SERVER+4)// ZONE+DB+MSG+CHAT+DAEMON
#define		INDEXOFDBA				0
#define		SERVER_SHAMBALA			2
#define		SERVER_KRUMA_HIGH		10 // 고랩 크루마 존
#define		SERVER_CHATURANGKA		11 // 차투랑가 존
#define		SERVER_KALIA_LOW		13	//	칼리아던전 저랩
#define		SERVER_KALIA_MIDDLE		14	//	칼리아던전 저랩
#define		SERVER_KALIA_HIGH		15	//	칼리아던전 저랩
#define		SERVER_STRONGHOLD		16	//	요새전
#define		SERVER_KATANA3			17	//	카타나3
#define		SERVER_KRUMA_LOW		20	//	저랩 크루마존
#define		SERVER_K3DUNGEON		21	//	K3 던전

#define		INDEXOFMESSENGER		51
#define		INDEXOFDAEMON			52
#define		INDEXOFCHAT				53
#define		MAX_IP_LENGTH			16
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		SECSTANDINGBY			8      // 초타이머에 의한 대기상태 NPC ACTION 분할값. 2.0초(=8*0.25초)
#define		SECBATTLE				2      // 초타이머에 의한 전투상태 NPC ACTION 분할값. 0.5초(=2*0.25초)
#define		TICKSIZE				250
#define		MAX_USER				1000      // pUser의 인덱스이자 pMob의 인덱스 pMob의 MAX_USER이후는 NPC
#define		ROBOT_START				800
#define		ROBOT_END				1000
#define		MAX_ADMIN				50      // 10개 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
	#define		OLD_ACCOUNTNAME_LENGTH	20		// 이전 어카운트 이름길이
	#define		ACCOUNTNAME_LENGTH		52      // 어카운트의 이름길이
#else
	#define ACCOUNTNAME_LENGTH			20
#endif

#define		ACCOUNTPASS_LENGTH		36     // 어카운트의 비번길이CHATROO

#define		REALNAME_LENGTH			24      // 어카운트의 가입자 본명 길이
#define		EMAIL_LENGTH			48      // 어카운트의 가입자 이메일 길이
#define		ADDRESS_LENGTH			80      // 어카운트의 가입자 주소 길이
#define		TELEPHONE_LENGTH		16      // 어카운트의 가입자 전화번호 길이
#define		MAX_GUILD				4096   // 길드네임을 위한 크기
#define		MOB_PER_ACCOUNT			3      // 어카운트당 만들수 있는 Char의 갯수
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		IDX_MOB					0      // Mob 은 0부터 시작.
#define		MAX_MONSTER				3500
#define		MAX_MOB					5000      // PC와 NPC 맙의 최대 갯수. CMob 어레이크기
#define		SZNAME_LENGTH			20      // NPC또는 Char의 이름 길이
#define		GUILDNAME_LENGTH		20	  // Guild Name의 길이
#define		MAX_SCORE				16      // MOB의 특성 (점수,돈,경험치...)
#define		MAX_EQUIP				16      // 캐랙터가 입을수 있는 아이템, 머리와 몸통이 각각 0,1번째다.
#define		MAX_INVEN				48      // MOBInven는Char의  Mob과 Ship의 의 Inventory 총합이다.
#define		MEMORIZE_POSITION		71		//	인벤토리의 71번째 공간을 위치저장 공간 존, 좌표로 사용하기로 한다.
#define		QUEST_INITCASTING		70		//	인벤토리의 70번째 공간을 퀘스트초기화 케스팅타임으로 사용하기로 한다.
#define		QUEST_SCRIPT			69		//	인벤토리의 69번째 공간을 퀘스트 스크립트 데이터로 사용하기로 한다.
#define		QUEST_SCRIPT_HISTORY	67		//	인벤토리의 67, 68번째 공간을 퀘스트 스크립트 히스토리데이터로 사용하기로 한다.
#define		MAX_ONEINVEN			24
#define		MAX_CARGO				120      // 어카운트별 아이템 참고se
#define		MAX_SKILL				100	  // 캐릭터별 스킬 최대값
#define		MAX_SKILL_DATA			7000     // 스킬 최대 개수
#define		MONSTER_SKILL_START		4001
#define		MAX_EVENT_FLAG			100	  // 캐릭터별 퀘스트 플래그 최대값
#define		MAX_DESC				24   
#define		MAX_CLASS				8
#define		MAX_MONSTER_DATA		1000
#define		MAX_SETTING				128
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_SUMMONLIST			2048
#define		MAX_NPCGENERATOR		4096      // NPC생성 종류 리스트. NpcGener.txt에서 읽어 들인 내용이다.
#define		MAX_CLAN				26
#define		MAX_SEGMENT				5   // 이 값을 수정하면 바로 아래의 LAST_SEGMENT를 꼭 수정해준다.
#define		LAST_SEGMENT			4
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		IDX_ITEM				10000      // Item은 ID가 10000번 이후로 붙는다.
#define		MAX_ITEM				5000      // 땅바닥에 놓이는 아이템 어레이 크기
#define		MAX_ITEMLIST			3000	  // 아이템 이펙트 리스트
#define		MAX_ITEM_DATA			6000      // 아이템 최대 개수(원래 아이템 개수5000 + monster item 개수 1000)
#define		ITEMNAME_LENGTH			28      // 아이템의 이름 길이
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MESSAGE_LENGTH			96      // MSG_MessagePanel 또는 MessageBox의 스트링 길이
#define		MAX_DBACCOUNT			(MAX_USER*MAX_SERVER) // Game서버당 MAX_USER개를 받을수 있는데 DB서버에서는 이 전체 접속 리스트를 들고 있어야 한다.
#define		MAX_CHATACCOUNT			(MAX_USER*MAX_SERVER*MAX_SERVERGROUP)
#define		IsUser(value)			((((value)>=0&&(value)<MAX_USER ) ? TRUE : FALSE) )
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_GRIDX				1024		// 전체 셀 가로 세로 크기
#define		MAX_GRIDY				1024
#define		PRANAGRIDX				100
#define		PRANAGRIDY				100
//#define		VIEWGRIDX				65		// Multicasting 할 가로 세로 크기
//#define		VIEWGRIDY				65
//#define		HALFGRIDX				32		// Multicasting 반지름
//#define		HALFGRIDY				32
#define		TRACE_LIMIT				24
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_ROUTE				24
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		InvenGRIDX				9	// 인벤 가로 세로 크기
#define		InvenGRIDY				7
#define		CARGOGRIDX				9	// 창고 가로 세로 크기	
#define		CARGOGRIDY				14
#define		MAX_FORMATION			5 // 대형 (종류)갯수

#define		MAX_GROUNDMASK			6
#define		MAX_INITITEM			64
#define		MAX_SKILLINDEX			101	// 실제는 0-100	
#define		BASE_EQUIP_LIMIT		40
#define		MAX_TRADE				8
#define		MAX_AUTOTRADE			12
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_SHOPLIST			27
#define		SET_ITEM_CREATE			0
#define		SET_ITEM_DELETE			1
#define		ITEM_REFINING_COAT		0.2		//	아이템제련시 아이템가격의 20% 적용
#define		ITEM_REPAIR_COAT		0.85	//	아이템제련시 아이템가격의 20% 적용
//	#define		ITEM_SELL_COAT			6		//	아이템제련시 아이템가격의 20% 적용
#define MAX_TASKITEM_SOURCE			6
#define MAX_TASKITEM_REWARD			5
#define MAX_TASKNPC_COUNT			5
#define MAX_TASKITEM_PRIORITY		5

// country
enum E_COUNTRY_ID
{
	eCountryKorea = 0,
	eCountryChina = 1,
	eCountryJapan = 2,
	eCountryIndonesia = 3,
	eCountryPhilippines = 4,
	eCountryTaiwan = 5,
	eCountryMexico = 6,
	eCountryForceDword = 0xffffffff
};

//	char
const int	TRIMURITY_LEVEL_LOW			=	30;				//	주신변경레벨
const int	TRIMURITY_LEVEL_HIGH		=	200;				//	주신변경레벨
const int	TRIMURITY_POINT_LEVEL		=	100;			//	스킬포인트레벨
const int	MONEY_TRIMURITY_UP			=	50000;			//	스킬포인트업시 필요비용
const int	MONEY_CHANGE_TRIMURITY_DOWN	=	100000;			//	주신변경시 필요비용	
const int   MONEY_CHANGE_TRIMURITY_UP	=	1000000;		//	주신변경시 필요비용

//	Init
const int	CONNECT_TYPE_FIRST		=	1;
const int	CONNECT_TYPE_PORTAL		=	2;
const int	CONNECT_TYPE_WARP		=	3;
const int   CONNECT_TYPE_DIE		=	4;
const int   CONNECT_TYPE_PUSTICA	=	5;
const int   CONNECT_TYPE_REAL_DIE	=	6;
const int   CONNECT_TYPE_GMRECALL	=	7;

#define MAX_GENERATION_AREA 100
#define MAX_TRIMURITY_AREA  10

//	Regen && Resurrect
const int	REGEN_TYPE_REGEN		=	0;
const int	REGEN_TYPE_RESURRECT	=	1;
const int	REGEN_TYPE_ARENA		=	2;
const int   REGEN_TYPE_CASTLE1		=	3;
const int   REGEN_TYPE_CASTLE2		=	4;
const int	RESURRECT_TYPE_SAVE		=	1;
const int	RESURRECT_TYPE_PRESENT	=	2;
const int	RESURRECT_TYPE_TOWN		=	3;
const int	RESURRECT_TYPE_ARENA	=	4;
const int	RESURRECT_TYPE_PORTAL	=	5;
const int	RESURRECT_TYPE_TEST		=	9;

//	chat 
#define		MAX_CHAT_LENGTH			224
#define		MAX_GROUPCHAT_LENGTH	48
#define		MAX_NOTIFY_LENGTH		1024
#define		HT_PARAMTYPE_NONE		0
const int	MAX_BASE_CHAKRA	=		7 ;
const int	MAX_CHATROOM			=	60;
const int	MAX_CHATROOMMEMBER		=	8;
const int	SZCHATROOMPASS_LENGTH	=	8;		//	채팅방 비번
const int	SZROOM_LENGTH			=	20;		//	채팅방명은 한글기준으로 9자 까지로 한다.	
const int	MAX_CHATPAGEUSER		=	20;		//	대기실 유저페이지 리스팅유저수
const int	MAX_WORLDCHATUSER		= 2000;
const int	MAX_CHATUSER			= MAX_WORLDCHATUSER * MAX_SERVERGROUP;
const int	MAX_CHATWAITUSER		= MAX_WORLDCHATUSER - (MAX_CHATROOM * MAX_CHATROOMMEMBER);

typedef enum _EChatRoomOrder
{
	eExpel		= 1,

} EChatRoomOrder;

const int	MESSAGE_PARTY				=	1;
const int	MESSAGE_GUILD				=	2;
const int	MESSAGE_GUILD_ALLIANCE		=	3;
const int	MESSAGE_ZONE				=	1;
const int	MESSAGE_WORLD				=	2;
const int	MESSAGE_GAME				=	3;
const int	MESSAGE_BATTLEORDER			=	4;
const int	MESSAGE_EXTRA				=	5;
const int	MESSAGE_SERVERMSG			=	6;
const int	MESSAGE_POSTTOWORLD			=   7;

const int	MSG_TYPE_PARTY	=	0;
const int	MSG_TYPE_GUILD	=	1;
const int	MSG_TYPE_ZONE	=	2;
const int	MSG_TYPE_WORLD	=	3;
const int	MSG_TYPE_GAME	=	4;

//	아이템
const int ITEM_PLACE_MAP			=	0;
const int ITEM_PLACE_INVEN			=	1;
const int ITEM_PLACE_EQUIP			=	2;
const int ITEM_PLACE_CARGO			=	3;
const int ITEM_PLACE_OTHERTRADE		=	4;
const int ITEM_PLACE_QUEST			=	5;
const int ITEM_PLACE_STORE			=	6;
const int ITEM_PLACE_EVENT			=	7;
const int ITEM_PLACE_PORTAL			=	9;
const int ITEM_PLACE_CHATURANGA		=	10;
const int ITEM_PLACE_GUILDCARGO		=	11;
const int ITEM_PLACE_RENTALSTORE	=   12;

const int MAX_INVEN_X				=	6;
const int MAX_INVEN_Y				=	4;
const int TYPE_ITEM_PACKING			=	1;
const int TYPE_ITEM_UNPACKING		=	2;
const int ITEM_EQUIP_LEVEL			=	5;

//	Item Drop
const int DROP_TYPE_MONEY			=   0;
const int DROP_TYPE_ITEM			=   1;

//	 재련관련상수
const int  _REFINE_WEPON_ONEHAND		=	1;	
const int  _REFINE_WEPON_TWOHAND		=	2;	
const int  _REFINE_DEFENCE_SHIELD		=	4;	
const int  _REFINE_DEFENCE_ARMOR		=	8;	
const int  _REFINE_DEFENCE_HELMET		=	16;	
const int  _REFINE_DEFENCE_BELT			=	32;	
const int  _REFINE_DEFENCE_SHOES		=	64;	
const int  _REFINE_ACCESSORY_EARRING	=	128;	
const int  _REFINE_ACCESSORY_BRACELET	=	256;	
const int  _REFINE_ACCESSORY_RING		=	512;	
const int  _REFINE_ACCESSORY_NECKLACE	=	1024;	
const int  _REFINE_DEFENCE_PANTS		=	2048;	
const int  _REFINE_DEFENCE_GLOVES		=	4096;	
const int  MAX_ITEM_CONTRIBUTION		=	10;
const int  ITEM_CONTRIBUTION_DEVIDE		=	225;
const int  MAX_MAINREFINELEVEL			=	15;		// 주재련레벨
const int  MAX_SUBMATERIAL				=	10;		// 보조재료의 최대갯수
const int  MAX_SUBMATERIALSIZE			=	5;

//	최대 교환아이템의 개수
const int	MAX_CARRY	= 8;
const int   MAX_MOBSTORE = 24;
const int   SZTRADE_LENGTH = 64;

//	Party
const int	MAX_PARTY			=	7;	// 한 그룹의 최대수( 1+5) 
const int	PARTY_PICKUP_TIME	=	10000;
const int	ROOTING_SHARE		=	1;
const int	ROOTING_PERSON		=	0;

//	Guild
#define		GUILD_FILE_PATH			"G:/"
const int	MAX_GUILD_MEMBER	=	50;

const int	SZGUILD_LENGTH		=	20;
const int	GUILDMESSAGE_LENGTH =   256;
const int	GUILDMARK_CREATE_COST	=	3000000;
const int	GUILDCARGO_TYPE1		=	2000000;
const int	GUILDCARGO_TYPE2		=	3000000;
const int	GUILDCARGO_TYPE3		=	3500000;

enum { eGuild_Remove_me = 1, eGuild_Remove_you = 2, eGuild_Remove_All = 3, } ;
const bool	FLAG_CLOSE			=	0;
const bool	FLAG_OPEN			=	1;
//	class1
const int	CLASS_LEVEL0		=	0;
const int	CLASS_LEVEL1		=	1;
const int	CLASS_LEVEL2		=	2;

//	class2
const int	CLASS_SATVAN		=	0;
const int	CLASS_DHVANTA		=	1;
const int	CLASS_NIRVANA		=	2;
const int	CLASS_MANTRIKA		=	3;
const int	CLASS_SATVAN1		=	0;
const int	CLASS_SATVAN2		=	1;
const int	CLASS_DHVANTA1		=	2;
const int	CLASS_DHVANTA2		=	3;
const int	CLASS_NIRVANA1		=	4;
const int	CLASS_NIRVANA2		=	5;
const int	CLASS_MANTRIKA1		=	6;
const int	CLASS_MANTRIKA2		=	7;

const int	CLASS_SATVAN_ITEM	=	4048;
const int	CLASS_DHVANTA_ITEM	=	4049;
const int	CLASS_NIRVANA_ITEM	=	4341;
const int	CLASS_MANTRIKA_ITEM	=	4122;

//	SYSTEM
const int	SYSTEM_ARALM_GAME_EXPIRED = 1;

//	Action
const int	ACTION_MOVE			=	0;
const int	ACTION_WARP			=	1;
const int	ACTION_YUT			=	2;

//	Event
const int EVENT_COUPON			=	1;
const int	MAX_EVENT			=	8;
#define		EVENTFILE			"Data\\Event%d.bin"
#define		EVENTFILE_DONE		"Data\\EventDone%d.bin"
#define		EVENTFILE_LOG		"Data\\GameEventLog.bin"

//	LimitedStore
const int MAX_LIMITEDITEM		= 40;
const int MAX_LimitedStore		= 2;
#define		FILE_LIMITEDSTORE	".\\Data\\LimitStoreItem.txt"

enum { eEvent1 = 1, eEvent2 = 2, eEvent3 = 4, eEvent4 = 8, eEvent5 = 16, };
struct STACTION
{
	int iAction;
	int iParam1;
	int iParam2;
	//union uParam3
	//{
	//	struct { short snX, snY};
	//	int iParam3;
	//};
};

struct STGAMEEVENT
{
	int iEventID;
	int iType;
	int iTarget;
	int iZone;
	STACTION	stAction[6];
};

//	LOG
const int LOGMONEY				=	1000000;

//	Developer
#define Developer				"TANDEV01"

//	요새전관련
const int MONEY_ARENAEVENT		=	100000000;

//	Billing(cash)
const int MAX_TIMEITEM			=	10;
enum { eTime_Inven = 0, eTime_Store = 1, eTime_AMoneyRoot = 2, eTime_Anubaba = 3, eTime_Atman = 4, eTime_15Chakra = 5, eTime_Block = 9, } ;

//	Challenge
const int	MONEY_OF_CHALLENGE		=	10000;
typedef enum _EChallenge { eChallenge_WAIT = 0, eChallenge_Request = 1, eChallenge_Response = 2, eChallenge_Combat = 3, } EChallenge;
typedef enum _EChallengeReason { eChallenge_Accept = 0, eChallenge_Denay = 1, eChallenge_Rest = 2, eChallenge_System = 3, eChallenge_End = 4,  } EChallengeReason;
/*----------------------------------------------------------------------------*/
// 아이템 제련 성공확률
/*----------------------------------------------------------------------------*/
const int REFINE_INITIALIZE_LEVEL	= 4;
const int REFINE_DISAPEAR_LEVEL		= 7;

//	Ranking
const int MAX_RANK				= 100;
#define RANKFILE				"K:\\Rank%02d.txt"

//	Yut(윷놀이)
const int MAX_POSITION	=	29;
const int MAX_BETUSER	=	20000;
enum
{
	eYut_bet	= 0x00000001,
	eYut_set	= 0x00000010,
	eYut_play	= 0x00000100,
	eYut_Result = 0x00001000,
};
const double dYut_Bounus[MAX_POSITION] = 
{
	1,		1.8,	1,		1,		1.2,	1,	1.5,	2,		2,		1.8,
	2,		2.5,	3,		3.5,	3,		2,	1.8,	2,		1.8,	1.8,
	8,		5,		1.5,	3,		2.4,	4,	2.3,	3.5,	3.8
};

//	대여상점
const int MAX_RENTALSTORE		=	21;
const int MAX_RENTALSTOREITEM	=	30;
const int MAX_USERRENTALITEM	=	30;
const int MAX_RENTALUSER		=	10000;
const int MAX_RENTALITEM		=	100000;
const int MAX_ERASETIME			=	30*24*60*60;	//	30일기준
#define		RENTALSTORE			"Data\\RentalStore.txt"

//	Quiz
#define		FILE_QUIZ			"Data\\Quiz.txt"
const int MAX_QUIZCOUNT			=	100;
const int MAX_QUIZSTRING		=	1024;
const int MAX_QUIZANSWER		=	4;
const int MAX_QUIZANSWERSTRING	=	20;


#define HT_MAP_START						40001

#define HT_PARAMTYPE_NONE					0


//#ifdef HT_NEED_NAME
//#define HT_NAME_MAX 50
//#endif

#define		TRIBE_NAGA			1//0x01	// 나가
#define		TRIBE_ASURA			4//0x02	// 아수라
#define		TRIBE_YAKSA			16//0x03	// 야크사
#define		TRIBE_DEVA			64//0x04	// 데바
#define		TRIBE_KINNARA		2//0x05	// 킨나라
#define		TRIBE_RAKSHASA		8//0x06	// 라크샤사
#define		TRIBE_GANDHARVA		32//0x07	// 간다르바
#define		TRIBE_GARUDA		128//0x08	// 가루다

#define		BEAUTY_OLD_HAIR		5
#define		BEAUTY_OLD_FACE		5
#define		BEAUTY_NEW_HAIR		8
#define		BEAUTY_NEW_FACE		8

#define HT_PARAMTYPE_NONE					0

// 몬스터 ID 영역
#define HT_PARAMTYPE_MONSTER				1
#define HT_PARAMTYPE_MONSTER_START			2001
#define HT_PARAMTYPE_MONSTER_END			2999

//// 몬스터 스킬의 ID 영역
//#define HT_PARAMTYPE_MONSTERSKILL			2
//#define HT_PARAMTYPE_MONSTERSKILL_START		3501
//#define HT_PARAMTYPE_MONSTERSKILL_END		3999
// 몬스터 스킬의 ID 영역
#define HT_PARAMTYPE_MONSTERSKILL			2
#define HT_PARAMTYPE_MONSTERSKILL_START		41001
#define HT_PARAMTYPE_MONSTERSKILL_END		43999

// 캐릭터 스킬의 ID 영역
#define HT_PARAMTYPE_PCSKILL				3
#define HT_PARAMTYPE_PCSKILL_START			3001
#define HT_PARAMTYPE_PCSKILL_END			3499

// 아이템의 ID 영역
#define HT_PARAMTYPE_ITEM					4
#define HT_PARAMTYPE_ITEM_START				4001
#define HT_PARAMTYPE_ITEM_END				9989

// NPC ID 영역
#define HT_PARAMTYPE_NPC					5
#define HT_PARAMTYPE_NPC_START				1001
#define HT_PARAMTYPE_NPC_END				1999
#define HT_NPC_SELLING_ITEM_MAX				49

// Portal
#define HT_PARAMTYPE_PORTAL					6
#define HT_PARAMTYPE_PORTAL_START			101
#define HT_PARAMTYPE_PORTAL_END				1000

// TaskQuest
#define HT_PARAMTYPE_TASKQUEST				7
#define HT_PARAMTYPE_TASKQUEST_START		10001
#define HT_PARAMTYPE_TASKQUEST_END			15000

#define HT_PARAMTYPE_END					8

// 스킬 중 나가/킨나라
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_START				3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_END				3100

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_START			3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_END			3020

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_START			3021
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_END			3040

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_START			3041
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_END			3060

// 스킬 중 아수라/락샤사
#define HT_PARAMTYPE_PCSKILL_ASURARAK_START				3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_END				3200

#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_START			3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_END			3120

#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_START			3121
#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_END			3140

#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_START			3141
#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_END			3160

// 스킬 중 야크샤/간다르바
#define HT_PARAMTYPE_PCSKILL_YAKGAN_START				3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_END					3300

#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_START			3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_END				3220

#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_START			3221
#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_END				3240

#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_START			3241
#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_END				3260

// 스킬 중 데바/가루다
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_START				3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_END				3400

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_START			3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_END			3320

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_START			3321
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_END			3340

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_START			3341
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_END			3360

// 아이템 중 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_START							4001
#define HT_PARAMTYPE_ITEM_WEAPON_END							5000

// 아이템 중 한손 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_START					4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_END					4300

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_START			4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_END				4140

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_START	4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_END	4110

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_START		4111
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_END		4140

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_START				4141
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_END				4280

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_START	4141
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_END		4250

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_START		4251
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_END			4280

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_START			4281
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_END				4290

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_START	4281
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_END	4288

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_START		4289
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_END		4290

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_START			4291
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_END				4300

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_START	4291
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_END		4298

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_START		4299
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_END		4300

// 아이템 중 양손 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_START					4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_END					4600

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_START			4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_END				4440

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_START	4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_END	4410

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_START		4411
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_END		4440

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_START				4441
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_END				4580

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_START	4441
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_END		4550

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_START		4551
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_END			4580

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_START			4581
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_END				4590

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_START	4581
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_END	4588

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_START		4589
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_END		4590

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_START			4591
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_END				4600

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_START	4591
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_END		4598

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_START		4599
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_END		4600

// 아이템 중 투척 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_START					4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_END						4700

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_START				4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_END				4645

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_START	4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_END		4645

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_START		4646
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_END			4690

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_START				4646
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_END					4690

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_START		4646
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_END		4690

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_START			4696
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_END			4660

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_START				4691
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_END				4695

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_START	4691
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_END		4695

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_START		4664
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_END			4665

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_START				4696
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_END				4700

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_START		4696
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_END		4700

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_START		4669
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_END			4670

// 방어구
#define HT_PARAMTYPE_ITEM_DEFENCE_START							5001
#define HT_PARAMTYPE_ITEM_DEFENCE_END							6000

// 방어구 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_START						8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_END						8675

// 갑옷
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_START					5001
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_END						5150

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_START			5001
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_END				5070

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_START				5071
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_END				5140

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_START			5141
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_END				5145

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_START				5146
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_END				5150

// 갑옷 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_START				8606
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_END					8675

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_START			8606
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_END			8640

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_START			8641
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_END				8670

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_START			8671
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_END			8675

// 바지
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_START					5151
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_END						5250

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_START			5151
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_END				5195

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_START				5196
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_END				5240

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_START			5241
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_END				5245

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_START				5246
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_END				5250

// 바지 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_START				8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_END					8305

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_START			8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_END			8250

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_START			8251
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_END				8300

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_START			8301
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_END			8305

// 투구
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_START					5251
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_END					5400

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_START			5251
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_END				5320

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_START				5321
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_END				5390

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_START			5391
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_END				5395

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_START			5396
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_END				5400

// 투구 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_START				8306
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_END					8405

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_START		8306
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_END			8350

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_START			8351
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_END			8400

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_START		8401
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_END			8405

// 장갑
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_START					5401
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_END					5500

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_START			5401
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_END				5445

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_START				5446
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_END				5490

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_START			5491
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_END				5495

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_START			5496
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_END				5500

// 장갑 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_START				8441
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_END					8525

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_START		8441
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_END			8480

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_START			8481
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_END			8520

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_START		8521
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_END			8525

// 허리띠
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_START					5501
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_END						5600

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_START				5501
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_END				5545

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_START				5546
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_END					5590

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_START				5591
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_END				5595

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_START				5596
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_END				5600

// 신발
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_START					5601
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_END						5700

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_START			5601
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_END				5645

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_START				5646
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_END				5690

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_START			5691
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_END				5695

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_START				5696
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_END				5700

// 신발 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_START				8526
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_END					8605

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_START			8526
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_END			8570

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_START			8571
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_END				8600

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_START			8601
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_END			8605

// 방패
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_START					5701
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_END					5800

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_START			5701
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_END				5745

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_START				5746
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_END				5790

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_START			5791
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_END				5795

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_START			5796
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_END				5800

// 부적
#define HT_PARAMTYPE_ITEM_CHARM_START							5801
#define HT_PARAMTYPE_ITEM_CHARM_END								5850

// 악세사리
#define HT_PARAMTYPE_ITEM_ACCESSORY_START						6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_END							6500

// 귀걸이
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_START				6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_END					6100

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_START		6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_END			6045

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_START			6046
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_END			6090

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_START		6091
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_END			6095

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_START			6096
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_END			6100

// 팔찌
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_START				6101
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_END				6200

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_START		6101
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_END			6145

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_START			6146
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_END			6190

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_START		6191
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_END			6195

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_START		6196
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_END			6200

// 목걸이
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_START				6201
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_END				6300

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_START		6201
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_END			6245

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_START			6246
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_END			6290

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_START		6291
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_END			6295

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_START		6296
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_END			6300

// 인벤확장
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_START			6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_END				6310

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_START	6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_END		6308

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_START		6309
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_END		6310

// 반지
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_START					6401
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_END					6500

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_START			6401
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_END				6445

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_START				6446
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_END				6490

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_START			6491
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_END				6495

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_START			6496
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_END				6500

// 제련 재료
#define HT_PARAMTYPE_ITEM_REFINE_START							6501
#define HT_PARAMTYPE_ITEM_REFINE_END							6700

// 메인제련
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_START						6501
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_END						6550

// 첨가 제련재료2
#define HT_PARAMTYPE_ITEM_REFINE_SUB3_START						6526
#define HT_PARAMTYPE_ITEM_REFINE_SUB3_END						6550

// 첨가 제련재료
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_START						6551
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_END						6600

// 보조제련
#define HT_PARAMTYPE_ITEM_REFINE_SUB_START						6601
#define HT_PARAMTYPE_ITEM_REFINE_SUB_END						6700

// 유료화 아이템-지속아이템
#define HT_PARAMTYPE_ITEM_CHARGE_START							6801
#define HT_PARAMTYPE_ITEM_CHARGE_END							7000

#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_START				6801
#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_END				6950

#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START					6951
#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_END					7000

// 유료화 아이템 중 소모성 아이템
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_START					7031
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_END						7070

#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_START					6719
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_END 					6722

// 소비 아이템 (1)
#define HT_PARAMTYPE_ITEM_USABLE_START							7001
#define HT_PARAMTYPE_ITEM_USABLE_END							7100

// 소비 아이템 (2)
#define HT_PARAMTYPE_ITEM_USABLE2_START							6701
#define HT_PARAMTYPE_ITEM_USABLE2_END							6770

// 소비 아이템 (3) 묶음 물약 등
#define HT_PARAMTYPE_ITEM_USABLE3_START							6771
#define HT_PARAMTYPE_ITEM_USABLE3_END							6800

// 소비 아이템 (3)
#define HT_PARAMTYPE_ITEM_USABLE4_START							8681
#define HT_PARAMTYPE_ITEM_USABLE4_END							8800

// 루피아
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_START					7081
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_END						7090

// 화살
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_START					7091
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_END						7100

// 수집 아이템
#define HT_PARAMTYPE_ITEM_COLLECT_START							7101
#define HT_PARAMTYPE_ITEM_COLLECT_END							8000

// 퀘스트 전용 아이템
#define HT_PARAMTYPE_ITEM_QUESTONLY_START						8001
#define HT_PARAMTYPE_ITEM_QUESTONLY_END							8200

#define HT_PCSKILL_MAXLEVEL			11

#define HT_ITEMLEVEL_MAX			255

//	0:실패, -1:재련불가능
const int REFINE_MAIN[7][MAX_MAINREFINELEVEL] = {				
	{80		,70		,60		,45		,30		,0		,0		,0		,0		,0		,0		,0,		0,	0,	0},
	{100	,100	,90		,75		,65		,55		,40		,10		,0		,0		,0		,0,		0,	0,	0},
	{100	,100	,100	,100	,80		,70		,60		,20		,10		,5		,0		,0,		0,	0,	0},
	{40		,30		,25		,0		,0		,0		,0		,0		,0		,0		,0		,0,		0,	0,	0},
	{100	,100	,100	,100	,100	,100	,100	,80		,50		,30		,20		,10,	0,	0,	0},
	{100	,100	,100	,100	,100	,100	,100	,100	,100	,-1		,-1		,-1,	-1,	-1,	-1},
	{-1		,-1		,-1		,-1		,-1		,-1		,-1		,-1		,-1		,-1		,-1		,-1,	30,	20,	10}
};	

const int REFINE_SUB[10] = {100	,100	,100	,80		,70		,40		,10		,5		,3		,1};

enum	ECHAR_DIR{
		ECHAR_STOP       =  0,
		ECHAR_RIGHT      = '6',
		ECHAR_DOWNRIGHT  = '3', 
		ECHAR_DOWN       = '2',
		ECHAR_DOWNLEFT   = '1',
		ECHAR_LEFT       = '4',	 
		ECHAR_UPLEFT     = '7',
		ECHAR_UP         = '8',
		ECHAR_UPRIGHT    = '9'
};

#define MAX_AFFECT			4
#define VISUAL_EQUIP		7
/*
#define AFFECT_SANC			1  // 0 :NONE
#define AFFECT_HASTE		2  // 0 :NONE
#define AFFECT_DAMUP		3  // 0 :NONE
*/
struct STRUCT_AFFECT
{
	   short Type;
	   short Value;
	   short Level;
	   short Time;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           STRUCTURE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
struct STRUCT_INITITEM 
{    
       short PosX;
       short PosY;
       short nIndex;
       short Rotate;
};

struct STRUCT_SPELL
{
		int	SkillPoint;
		int	TargetType;      // 0:자신  1:타인   2:자신타인   3:지역3  4:지역5 
		int	ManaSpent;       // 마나소모량
		int	Delay;           // 마법재사용에 필요한시간
		int	Range;           // 사정거리
		int	InstanceType; 
		int	InstanceValue;
		int	TickType;     
		int	TickValue;    
		int	AffectType;   
		int	AffectValue;
		int	AffectTime;
		unsigned char Act[8];
		int	InstanceAttribute;
		int	TickAttribute;
		int	Aggressive;
		int	MaxTarget;
		int	bParty;
		int	AffectResist;
		int	Passive;
};
//  Index:          마법번호                    - 0-71 각 클레스별 0-23(기사) 24-47(마사) 48-71(수사) 72-96(협사)
//  SkillPoint:     배우는데 필요한 기술포인트 
//  TargetType:     0:자신만  1:타인  2:자신또는타인 3:땅3x3  4:땅5x5
//  ManaSpent:      기본 마나 소모량 계열숙련도가 100이면 200% 
//  Delay:          한번 쓰고 다시 쓰기까지 필요한 시간 단위는 초.
//  Range:          사정거리
//  InstanceType:   마법이 적용되는 순간 처리되는 효과 - 0:없음 1:HP증감       2:HP%증감      3:화면점멸  
//  InstanceValue:  HP증가량 또는 감소량 또는 화면점멸정도.
//  TickType:       틱(4초)마나 처리되는 효과          - 0:없음 1:HP+증감      2:HP%증감      3:3x3HP감소    4:3x3HP증가 
//  TickValue:      HP증가량 또는 감소량
//  AffectType:     걸려있는동안 Score 변화            - 0:없음 1:달리기+변화  2:저항력%변화  3:Dex%변화     4:공속+변화
//  AffectValue:    +- 또는 %량. +-는 더해지거나 빠지고, %는 현제량 기준으로 2배시 200 1/2시 50
//

// Dropped item은 mask단위로 존재한다. -> 별도스트럭쳐 없음
// 값은 unsigned short 를 사용하고 아이디는 20000-30000이며, 20000이 어레이 0에 배치된다.
struct STRUCT_ITEMLIST
{      //int				   Style;						// 스타일
       //int				   Position;					// 장착 가능 부위 -> 2부위 이상 장착가능시 Bitmask(?)
       char					Name[ITEMNAME_LENGTH];		// 아이템 이름
       short				nIndexMesh;
       short				nIndexTexture;
       short				nIndexVisualEffect;
	   short				nReqLvl;
	   short				nReqStr;
	   short				nReqInt;
	   short				nReqDex;
	   short				nReqCon;
	   int					nPrice;
   	   short				nUnique;
	   short				nPos;
	   short				nExtra;
	   short				nGrade;

};
//////////////////////////////////////////////////////////////////////////
struct STRUCT_SCORE
{
	  short   Level;
	  short   Ac;
	  short   Damage;
      unsigned char   Reserved;   // 하위 4비트(0-15):0범인(凡人). 1상인. 2창고  3스킬  4범인(犯人) 5. 
	                              // 상위 4비트(0-15) 디렉션 1,2,3,4,6,7,8,9 또는 none(0)
	  unsigned char   AttackRun;  // 상위 4비트 공격속도   - 0:50%   5:100%   10:200%
                                  // 하위 4비트 달리기속도 - 1-6                        
	  short   MaxHp,   MaxMp;
	  short   Hp   ,   Mp   ;
	  short   snMuscleChakra, snNerveChakra, snHeartChakra, snSoulChakra;
	  unsigned char Special[4];  // 무기숙련도/ 각마법계열별숙련도1,2,3
};

struct STRUCT_ITEM // 16 bytes
{		short		snIndex ; // Shopitem 에서의 index
		short		snDurability ;
		WORD		wSerial;
		short		snDummy;	

		BYTE		byCount ;
		BYTE		bySubRefine[MAX_SUBMATERIALSIZE] ;
		BYTE		byDummy;
		BYTE		byRefineLevel ;
};

struct STRUCT_ITEMVIEW
{
	SHORT		snIndex ;		//	Shopitem 에서의 index
	BYTE		byMainRef;		//	속성에 따른 비트셋이 필요함.
	BYTE		byRefineLevel;	//	제련레벨
};

typedef struct _S_CHARACTER_LIST
{
	char		szCharName[SZNAME_LENGTH];
	short    	snTribe;      
	BYTE    	byTrimuriti;  
	BYTE    	byTrimuritiClass; 

	int     	nBrahmanPoint;
	short   	snChakraMuscle;
	short   	snChakraNerve;
	short   	snChakraHeart;
	short		snChakraSoul;    
    STRUCT_ITEM	Equip[VISUAL_EQUIP];

	in_addr		LastServerIP;
	int			LastZone;

	short		LastServerPort;
	BYTE    	byFaceType;   
	BYTE		byHeadType;
	BYTE		byLevel;
	BYTE		byGMStatus;		//	bit flag(0x01:케릭터블럭, 0x02:투명모드, 0x04:채팅블럭, ...)	
	BYTE		byClass1;			//	bit flag 중목중복은 | 연산사용.
	BYTE		byClass2;

	short		snKarma;
	short		snDummy;
} S_CHARACTER_LIST, *PS_CHARACTER_LIST;

struct STRUCT_SELCHAR
{      
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];
};



struct STRUCT_MOB // 32+24+24+100+100+1152+256 = 1688 bytes = 1.688 kb, 실제로 1024*2만큼이 쓰일것이다.
{		
		char			        szName[SZNAME_LENGTH];
		short					sMuscle ;
		short					sNerves ;
		short					sHeart ;
		short					sMind ;
		short					snTribe;
		short					snBagIndex;  // 32

		int						nPrana;
		int						nHP;
		int						nTP;
		int						nRupiah;
		int						nBramanPoint;
		int						nGuildID;   // 24
//		int						nTrimurityLearn;
		
		BYTE					byTrimuriti;		
		BYTE					byLevel;
		BYTE					byFace;
		BYTE					byHead;

		BYTE					byInvenBag;
		BYTE					bySpecialName;		// Class 로 변경을 해줘야 함. int
		BYTE					byZone;
		BYTE					bySaveZone;

		BYTE					byStatus;			//	bit flag(0x01:귓말거절, ...)
		BYTE					byGMStatus;			//	bit flag(0x01:케릭터블럭, 0x02:투명모드, 0x04:채팅블럭, ...)	
		BYTE					byClass1;				//	bit flag 중목중복은 | 연산사용.
		BYTE					byClass2;

		short					snKarma;
		BYTE					byDecPranaRate;		//	사망으로 인한 프라나 감소분(%)
		BYTE					byKillLevel;		//	사망시 기준랩

		short					snX;
		short					snZ;
		short					snSaveX;
		short					snSaveZ; // 24
		
		BYTE					bySkill[MAX_SKILL];  // 100
		BYTE					byQuest[MAX_EVENT_FLAG]; // 100
		STRUCT_ITEM				Inven[72]; // 16 * 72
		STRUCT_ITEM				Equip[MAX_EQUIP]; // 16 * 16	
};

struct	STRUCT_COMBINE	
{		int	Target;
		int	Source[MAX_TRADE];
		int	Refine[MAX_TRADE];
};

#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
	struct OLD_STRUCT_ACCOUNTFILE
	{
		char				AccountName[OLD_ACCOUNTNAME_LENGTH];
		char				AccountPass[ACCOUNTPASS_LENGTH];
		STRUCT_MOB          Char[MOB_PER_ACCOUNT];
		STRUCT_ITEM			Cargo[MAX_CARGO];
		int                 Coin;
		int					ssn1;
		int					ssn2;
		DWORD				dwTimeStamp[MAX_TIMEITEM];
	};
#endif
	struct STRUCT_ACCOUNTFILE // 20+16+1688*3+16*120+12 = 7032 bytes = 1968 + 5064(1688*3)
	{
			char				AccountName[ACCOUNTNAME_LENGTH];
			char				AccountPass[ACCOUNTPASS_LENGTH];
			STRUCT_MOB          Char[MOB_PER_ACCOUNT];
			STRUCT_ITEM			Cargo[MAX_CARGO];
			int                 Coin;
			int					ssn1;
			int					ssn2;
			DWORD				dwTimeStamp[MAX_TIMEITEM];
	};

struct STRUCT_GUILD_MEMBER
{
		char	MemberName[SZNAME_LENGTH];

		BYTE	GuildRank;
		BYTE	GuildState;			//	0:빈슬롯, 1:로그off, 2:로그on
		BYTE	byLevel;
		BYTE	byDummy;
		short	snTribe;
		BYTE	byClass1;
		BYTE	byClass2;
};
struct STRUCT_GUILD
{
		char				GuildName[SZNAME_LENGTH];
		char				AlliedGuildName1[SZNAME_LENGTH];
		char				AlliedGuildName2[SZNAME_LENGTH];
		char				EnemyGuildName1[SZNAME_LENGTH];
		DWORD				dwTime[3];
		DWORD				dwDummy;
		BYTE				byCargoLevel[3];
		BYTE				byDummy;
		int					GuildID;
		int					Mark;
		char				GuildMessage[GUILDMESSAGE_LENGTH];
		STRUCT_GUILD_MEMBER Member[MAX_GUILD_MEMBER];
		STRUCT_ITEM			Repository[MAX_CARGO*3];	// 창고 3개
};

struct TASK_INFO
{
	short snNPCID[MAX_TASKNPC_COUNT]; 
	short snDummy1;
	byte bySourceType[MAX_TASKITEM_SOURCE];
	byte byDummy1[2];
	byte byRewardType[MAX_TASKITEM_REWARD];
	byte byDummy2[3];
	byte byRewardPriority[MAX_TASKITEM_REWARD];
	byte byDummy3[3];
	short snSourceIndex[MAX_TASKITEM_SOURCE];
	short snRewardIndex[MAX_TASKITEM_REWARD];
	short snDummy2;
	short snRewardRate[MAX_TASKITEM_REWARD];
	short snDummy3;
	int nSourceCount[MAX_TASKITEM_SOURCE];
	int nRewardCount[MAX_TASKITEM_REWARD];
	byte byMinLevel;
	byte byMaxLevel;
	short snDummy4;
};

#define MAX_LEVEL      355

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//       fors_debug struct                                    STRUCTURE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Message Structure 의 ID 인덱싱 방식  
//        0 - MAX_USER           User
// MAX_USER - MAX_MOB            NPC
// 10000    - 10000+MAX_OBJ    Object   
/////////////////////////////////////////////////////////////////////////////////////////////
//
//    |______________|_____________|   ....  |____________|
//    0           MAX_USER      MAX_MOB      10000    10000+MAX_OBJ
#define _MSG       WORD		wType;						\
                   WORD		wSeq;						\
	  	           WORD		wPDULength;                 \
				   WORD		wDummy;						\
 		           DWORD	dwClientTick;  

		
struct  MSG_STANDARD
{  	    _MSG;
		int nID;
};
struct  MSG_STANDARDPARM
{  	    _MSG;
		int nID;
        int Parm;
};

struct  MSG_STANDARDPARM2
{  	    _MSG;
		int nID;
        int Parm1;
		int Parm2;
};
struct  MSG_STANDARDPARM3
{  	    _MSG;
		int nID;
        int Parm1;
		int Parm2;
		int Parm3;
};

//////////////////////////////////////////////////////////////////////////////////////////
#define    _MSG_ClosedSocket			0
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//           DB 서버     - >   게임 서버
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define FLAG_DB2GAME                 0x0400
/////////////////////////////////////////////////////////////////////
#define _MSG_DBMessagePanel       (  1 | FLAG_DB2GAME)
#define _MSG_DBMessageBoxOk       (  2 | FLAG_DB2GAME)
#define _MSG_DBMessageBoxYesNo    (  3 | FLAG_DB2GAME)

#define _MSG_DBCloseNothing       (  4 | FLAG_DB2GAME)
#define _MSG_DBSavingQuit         ( 10 | FLAG_DB2GAME)
struct   MSG_DBSavingQuit 
{       _MSG;
		 int  nID;
	     char AccountName[ACCOUNTNAME_LENGTH];
		 int  Mode;
};
#define _MSG_DBCNFAccountLogin			( 22 | FLAG_DB2GAME)
#define _MSG_DBCNFCharacterLogin		( 23 | FLAG_DB2GAME)
#define _MSG_DBCNFNewCharacter			( 24 | FLAG_DB2GAME)
#define _MSG_DBCNFDeleteCharacter		( 25 | FLAG_DB2GAME)
#define _MSG_DBNewAccountFail			( 26 | FLAG_DB2GAME)
#define _MSG_DBAccountLoginFail			( 27 | FLAG_DB2GAME)
#define _MSG_DBCharacterLoginFail		( 28 | FLAG_DB2GAME)
#define _MSG_DBNewCharacterFail			( 29 | FLAG_DB2GAME)
#define _MSG_DBDeleteCharacterFail		( 30 | FLAG_DB2GAME)
#define _MSG_DBAlreadyPlaying			( 31 | FLAG_DB2GAME)    
#define _MSG_DBStillPlaying				( 32 | FLAG_DB2GAME)    
#define _MSG_DBAccountLoginFail_Account ( 33 | FLAG_DB2GAME)    
#define _MSG_DBAccountLoginFail_Pass    ( 34 | FLAG_DB2GAME)    
#define _MSG_DBSetIndex                 ( 35 | FLAG_DB2GAME)    // ID:Server Parm:Group
#define _MSG_DBAccountLoginFail_Block   ( 36 | FLAG_DB2GAME)    
#define _MSG_DBAccountLoginFail_Disable ( 37 | FLAG_DB2GAME)    
#define _MSG_DBOnlyOncePerDay			( 38 | FLAG_DB2GAME)    


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//               게임 서버   - >   DB 서버
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define  FLAG_GAME2DB                0x0800
#define _MSG_DBNewCharacter         ( 2 | FLAG_GAME2DB) //   캐랙터 만들기
#define _MSG_DBAccountLogin         ( 3 | FLAG_GAME2DB) //   어카운트 로그인
#define _MSG_DBCharacterLogin       ( 4 | FLAG_GAME2DB) //   캐랙터 로그인
#define _MSG_DBNoNeedSave           ( 5 | FLAG_GAME2DB) //   접속 종료, 저장할게 없음.
#define _MSG_DBSaveMob              ( 7 | FLAG_GAME2DB)
struct	MSG_DBSaveMob
{       _MSG;
		int			   nID;
	 	int            Slot;            
		STRUCT_MOB     MOB;
		STRUCT_ITEM    Cargo[MAX_CARGO];
		int				Coin;
		char			ShortSkill[8];
		char			AccountName[ACCOUNTNAME_LENGTH];
		int				Export;
		DWORD			dwTimeStamp[MAX_TIMEITEM];
};
#define	_MSG_DBDeleteCharacter		( 9 | FLAG_GAME2DB)
#define	_MSG_MessageDBImple			(11 | FLAG_GAME2DB | FLAG_DB2GAME) //   Parm 
struct	MSG_MessageDBImple
{		_MSG;
		int nID;
		int Level;
		char     String[MESSAGE_LENGTH]; 
};
#define  _MSG_MessageDBRecord		( 12 | FLAG_GAME2DB) 
//#define _MSG_GuildZoneReport		( 13 | FLAG_GAME2DB)
//struct	MSG_GuildZoneReport
//{		_MSG;
//		int	Guild[MAX_GUILDZONE];
//};
#define	_MSG_DBSendItem				( 12 | FLAG_GAME2DB | FLAG_DB2GAME) // PARM  
struct	MSG_DBSendItem
{		_MSG;
		int nID;
		int Result;					// 0: 요청,성공  1:게임중이아님  2:대상이다름 3:빈자리없음 
		char Account[ACCOUNTNAME_LENGTH];
		STRUCT_ITEM	Item;
};

//-------------------------------------------------------
//	added by 정재웅(2003.11.22)
//-------------------------------------------------------
int Percent( double a_dValue, double a_dPercent ) ;

#define TN_MAX_COEFFICIENT_COUNT	4
#define TN_MAX_TARGET_COUNT			16
#define TN_MAX_SKILLBOOK_SIZE		1500
#define TN_MAX_EFFECT_COUNT			5
#define TN_ADDON_EFFECT_COUNT		5
#define TN_MAX_VARIATION_COUNT		72
#define TN_RANGE_DISTANT			6
#define TN_PC_SKILL_COUNT			100
#define TN_MONSTER_SKILL_COUNT		9
#define TN_ATTACKER_COUNT			16
#define TN_MAX_LEVEL				201 // 100 fors_debug level max
#define TN_BRAMAN_POINT				50
#define TN_MASTERY_COUNT			11
#define TN_CFTABLE_COUNT			9


//#define TN_DURABILITY_CONST			100
// 상수 정의
enum { eSummonCaller_TriggerEvent1 = 20, eSummonCaller_TriggerEvent2 = 30
		, eSummonCaller_Normal = 100, eSummonCaller_Familiar, eSummonCaller_Fellow, eSummonCaller_Tracker
		, eSummonCaller_MonsterScroll = 110, eSummonCaller_GMCommand = 120,
} ;

enum { eCnst_StaffCorrect = 0, eCnst_StaffMaxNerves, eCnst_AbsorbMax, eCnst_ReflectMax
		, eCnst_SpeedMin, eCnst_SpeedMax, eCnst_HPRecvMax, eCnst_TPRecvMax, eCnst_ResistMax
		, eCnst_ProtectionFromPK, eCnst_PriorityTime, eCnst_TownPortalTime, eCnst_AdvTownPortalTime, eCnst_QuitTime
		, eCnst_Restriction, eCnst_RwdBramanPoint, eCnst_DecKarmaPoint, eCnst_RwdKarmaPoint, eCnst_IncKarmaPoint, eCnst_RwdGold, eCnst_LoseGold, eCnst_MaxKarma, eCnst_MurderDropRate, eCnst_InnocentDropRate, eCnst_FirstStrikerDropRate, eCnst_HuntHigh, eCnst_HuntLow, eCnst_FirstStrikeDur
		, eCnst_CondCoolDown, eCnst_KalaCoreDur, eCnst_PenaltyByKilled
		, eCnst_HeartMax, eCnst_AttackSpeedHack
		, eCnst_FeeForSiegeSupport, eCnst_FeeForSiege1, eCnst_FeeForSiege2, eCnst_FeeForSiege3, eCnst_ItemCount, eCnst_MemberLevel, eCnst_MemberCount1, eCnst_MemberCount2
		, eCnst_ObstacleHeight, eCnst_CharacterHeight, eCnst_KarmaForRestrictingToAttack
		, eCnst_PenaltyBPByKilled
		, eCnst_AllowedLevelLow, eCnst_AllowedLevelHigh
		, eCnst_SkillCastIntervalHack
		,
};

enum { eSiz_RwdCorrect = 4, eRwd_Prana =0, eRwd_Gold = 1, eRwd_Braman = 2, eRwd_Item = 3, eSiz_Type = 3, eRwd_Total = 0, eRwd_Base = 1, eRwd_Extra = 2, eRwd_ExtraMinus = 3, };
enum { eSiz_Room = 32, eSiz_EventDeck = 12, eSiz_EventDeck1000 = 2};
enum { eRetainer_DistanceFromMaster = 32, } ;
enum { eCmd_None = 0, eCmd_PopMonster = 1, eCmd_DropItem = 2, eCmd_MaxCount = 6, eArea_MaxMobListCount = 6, } ;
enum { eSklPtrn_Count = 50, eSklPtrn_Size = 10, eAAC_ArmorTypeCount = 15, eAAC_AttackTypeCount = 21, ePath_MaxCount = 5, eFlee_MaxPathCount = 5, eRoam_MaxPathCount = 5, eSmbl_MaxSize = 7, } ;
enum { eSdg_SymbolCount = 7, eSdg_MaxEntry = 200, eSdg_LeaderSize = 4, } ; // 공성전 관련
enum { eItm_Use = 0, eItm_Info, eItem_Brd, eItm_Arrow = 7092, /*eItm_TownPortal = 7011, eItm_TownPortal2 = 7028, eItm_TownPortal3 = 7034, eItm_TownPortal4 = 7072,*/ eItem_Resurrect1 = 7031, eItem_Resurrect2 = 7039, eItm_Permenent = 2, eItm_Decay = 0};
enum { eItem_amala = 6614, eItem_jade = 6551, eItem_apad = 6555, eItem_Resurrect80 = 7031, eItem_Resurrect100 = 7039, eItm_SummonParty = 7078, };
enum { eItem_Init2ndClass = 7050, eItem_ChangeHair = 7051, eItem_ChangeFace = 7052, eItem_ChangeSex = 7053, eItem_ChangeGuildMark = 7054, eItem_ChangeOldHair = 7055, eItem_ChangeOldFace = 7056, eItem_ChangeOldGuildMark = 7057, eItem_GuildCreate = 6756, };
enum { eItem_InitSkill = 7061, eItem_InitChar = 7062, eItem_InitSkillChar = 7063, eItem_InitQuest1 = 7077, eItem_InitQuest2 = 7416, };
enum { eItem_BattleOrder = 7043, eItem_Extra = 7038, eItem_PartyPenalty = 7048, eItem_NoLimitPortal = 7049, eItem_Pt4 = 7067, };
enum { eItem_GoldSmall = 7383, eItem_ChangeCharname = 6759, };
enum { eSetItem_Size = 256, eSetItem_MaxEffectItem = 3, };
enum { eLogFile_Size = 32, eLogFileName_Assert = 0, eLogFileName_BossSystem, eLogFileName_KalaSystem, eLogFileName_Stronghold, eLogFileName_Castle, eLogFileName_ArenaEvent
		, eLogFileName_RvREntry, eLogFileName_EventTriggered, eLogFileName_ItemThatSummonMonster, eLogFileName_ItemDroppedByEvent
		, eLogFileName_InvalidCombat, eLogFileName_RecordPCName, eLogFileName_CountMonster, eLogFileName_OnKilled
		, eLogFileName_HackDist, eLogFileName_HackAttackSpeed, eLogFileName_MagicLamp,
		};
enum { eCharDeleteDefault = 0, eCharDeleteRename = 1, eCharDeleteClean = 2, eCharDeleteGM = 3,};
enum { eSiz_Route = 64, };
enum { eItem_MonsterScroll = 6719, eItem_MonsterScroll2 = 6745, eItem_MonsterScroll3 = 6758, eItem_MonsterScroll4 = 6749, eItem_MonsterScroll5 = 6750, eConst_CheckItemSlot = 10,};
enum { ePnlt_DecPrana = 0, ePnlt_NoPenalty, ePnlt_DecBP, ePnlt_Exception, };
enum { eBlss_Max = 600, eBlss_Min = 100, };
enum { eZone_Mandra = 1, eZone_Shambala =2, eZone_Pamir = 8, eZone_Exile = 9, eZone_Cruma = 10, eZone_Chaturanka = 11, eZone_Katacomb = 12, eZone_Kalia1 = 13, eZone_Kalia2 = 14, eZone_Kalia3 = 15, eZone_Stronghold = 16, eZone_Castle = 17, eZone_Cruma2 = 20, eZone_CastleDungeon = 21, } ;
enum { eSaveNPC_Mandra = 1120, eSaveNPC_Shambala =1154, eSaveNPC_Jina = 1155, eSaveNPC_9Zone = 1156, eSaveNPC_Cruma_Brahma = 1254, eSaveNPC_Cruma_Vishunu = 1255, eSaveNPC_Cruma_Siva = 1256, } ;
enum { eCls_MaxLevel = 4, eCls_MaxSpecialized = 8, } ;
enum { eHack_MaxAttackTimeRecordCount = 5, eHack_MaxAttackTimeGap = 1500, } ;
enum { eConst_LevelGap = 15, eConst_TooFarRange = 80, eConst_MaxAffectionCount = 63, eConst_CantTrace = 2, } ;
enum { eDur_Indestructible = 25500, eLvl_Max = 255, } ;
enum { eConst_EnhanceHardnessOfArmorBase = 50, };
enum { eConst_Physical = 0, eConst_Elemental, };
//enum { ePK_Restriction = 20, ePK_Murder = 0, ePK_RwdBramanPoint = 50, ePK_DecKarmaPoint = 250, ePK_RwdKarmaPoint = 100, ePK_IncKarmaPoint = 500, ePK_RwdGold = 45, ePK_LoseGold = 50, ePK_MaxKarma = 30000, ePK_MurderDropRate = 10, eHnt_High = 5, eHnt_Low = 1, } ;
//enum { ePK_PKDurationTime = 180000, ePK_AttackSize = 4, } ;
enum { eRvRZone_Count = 10, } ;
enum { eCon_JudgeCombat= 10, eCon_MaxGapCount = 201, eCon_LastIndex = 40, eCon_PrtyCount = 3, eCon_MaxGap = 20, eCon_Sort = 2, eCon_DF = 0, eCon_RS = 1, eCon_DG = 2, } ;
enum { eHnt_Novice = 10, eHnt_DecPrana = 10, } ;
enum { eRwd_ItemCount = 10, eRwd_ItemGroup = 64, eRwd_ItemGroupCount = 101, eMonster_MaxLevel = 31, eItm_MaxLevel = 21, eItm_MaxCategory = 140, } ;
enum { eVar_Equipment = 0, eVar_Skill = 1, eVar_PassiveSkill = 2, eAfn_Add = 0, eAfn_Remove = 1, eAfn_Permanent = 0, eAfn_Buffer = 1, } ;
enum { eSkl_Melee = 0, eSkl_Range = 1, eSkl_Unit = 2, eSkl_Area = 3, eSkl_Death = 4, } ;
enum { eWhr_Equipment = 0, eWhr_Map = 1, eWhr_TradePane = 2, eWhr_Bag1 = 3, eWhr_Bag2 = 4, eWhr_Bag3 = 5, };
enum { eEqu_Weapon = 0, eEqu_Shield = 1, eEqu_Armoretnac = 2, eEqu_Boots = 3, eEqu_Helmet = 4, eEqu_Belt = 5, eEqu_Neckrace = 6, eEqu_EarringL = 7, eEqu_EarringR = 8, eEqu_RingL = 9, eEqu_RingR = 10, eEqu_Bag = 11, eEqu_BraceletL = 12, eEqu_BraceletR = 13, eEqu_GauntletL = 12, eEqu_GauntletR = 13, } ;
enum { eStt_Base = 0, eStt_Changed = 1, eStt_Extra = 2, eStt_Braman = 0, eStt_Str = 1, eStt_Dex = 2, eStt_Vital = 3, eStt_Energy = 4, eCF_AttackRate = 5, eCF_DodgeRate = 6, eCF_BlockRate = 7, eCF_CriticalHitRate = 8, eCF_AC = 9,  };
enum { eRst_Fire = 0, eRst_Cold = 1, eRst_Lightning = 2, eRst_Poison = 3 } ;
enum { eTolr_Hold = 0, eTolr_Stun, eTolr_Sleep, eTolr_Terror, eTolr_Taunt, eTolr_SlowMove, eTolr_SlowAttack } ;
enum { eWaitAct_None = 0, eWaitAct_TownPortal = 1, eWaitAct_Quit, eWaitAct_ZonePortal, /*eWaitAct_TownPortal2, eWaitAct_TownPortal3,*/ eWaitAct_ServerDown, eWaitAct_Kickout, eWaitAct_SummonParty} ;
enum { ePortal_Gen = 0, ePortal_Guild, ePortal_SZiva, ePortal_Ziva, ePortal_Viryu, ePortal_NoLimit, ePortal_Castle, ePortal_Memorized, };
enum { eCloseMemorized = 1, eClosePortal, eClosePustica, eCloseSystem, eCloseRegen, };
enum { ePortal_Stronghold_SNW = 202, ePortal_Stronghold_SNE = 203, ePortal_Stronghold_SSW = 204, ePortal_Stronghold_SSE = 205, };
enum { ePortal_Stronghold_NW = 206, ePortal_Stronghold_NE = 207, ePortal_Stronghold_SW = 208, ePortal_Stronghold_SE = 209, ePortal_Stronghold_Front = 210, };
enum { ePortal_CastleIN = 223, ePortal_CastleW = 220, ePortal_CastleN = 228, };
enum { /*eWaitTime_TownPortal = 5000, eWaitTime_TownPortal2 = 2000,*/ eWaitTime_Quit = 10000, eWaitTime_SummonParty = 5000, } ;
enum { eCmbt_Echo = -1, eCmbt_Normal = 0, eCmbt_Critical, eCmbt_Dodge, eCmbt_Blocked, eCmbt_Miss, eCmbt_MemoryTime = 60000, } ;
enum { eBlk_None = 0, eBlk_Forbidden = 1, eBlk_Pc = 2, eBlk_Monster = 3, eBlk_OutOfMap = 4, eBlk_SafeZone = 5 } ; // 이동시 block된 이유
enum { ePop_Succ = 0, ePop_CantPop, ePop_OutOfPopArea, ePop_InvalidCoord } ; // 몬스터 pop시에 사용하는 enum
enum { ePath_Succ = 0, ePath_OutOfActiveArea, ePath_Forbidden, ePath_Idential, ePath_OutOfMap, ePath_TooFar, ePath_Blocked } ; // path-finding시의 enum
enum { eTNAI_TraceCount = 15 } ;
enum { eATDG_Count = 9, eConst_MaxInstantCoolDonw = 128, eConst_MaxCooldownTimeCount = 4, eCldnTm_DropItem = 0, } ;
enum { eMonSkl_MaxIndex = 9, } ;
enum { eRds_MaxDetectEnemy = 20, ePos_MaxPosCount = 1681, } ;
//enum { eConst_MaxAbsorbDamage = 50, eConst_MaxReflectDamage = 50, } ;
enum { eKala_MaxCount = 9, eKalaAltar_MaxCount = 15, eKalaCore_Brahma = 8051, eKalaCore_Vishnu = 8052, eKalaCore_Siva = 8053, eKalaCore_Neutral = 8054, eKala_Neutral = 2923, eKala_Brahma = 2924, eKala_Vishnu = 2925, eKala_Siva = 2926, eKala_Event1 = 2927, eKala_Event2 = 2928, eKala_Event3 = 2929, } ;
enum { eReturnToShrine = 1, } ;
enum { eCaste_MaxLevel = 18, } ;
enum { eDly_TPRecv = 1000, } ;
//enum { eSpd_Min = 500, eSpd_Max = 25000, } ;
enum { eRealm_MaxCount = 5, eKalaRewarder_MaxCount = 3, } ;
enum { eEvent_MaxCount = 256, eTask_MaxCount = 512, eTask_Sort = 5, eTask_Param = 6, } ;
enum { eAggrScore_MaxCount = 10, } ;
enum { eFollower_MaxCount = 20, eRobot_MaxCount = 128, eFellow_MaxCount = 10, } ;
enum { eGuard_SivaArcher = 2908, eGuard_VishnuArcher = 2912, eGuard_BrahmaArcher = 2916, eGuard_SivaTower = 2917, eGuard_VishnuTower = 2918, eGuard_BrahmaTower = 2919, } ;
//enum { eHP_MaxRecvry = 500, eTP_MaxRecvry = 400, eResist_Max = 100 , } ;
enum { eTS_MaxSlot = 900, } ; // time scheduler
enum { eMvLog_Size = 5, } ;
enum { eEvnt_ResetChaturangka = 99, } ;
enum { eEvntPrcdType_Sequential = 0, eEvntPrcdType_Conditional , eEvntPrcdType_Random, } ;
enum { eEvntClan_All = -1, eEvntSwitch_On = 0, eEvntSwitch_Off = -1, } ;
enum { eChkHack_Time = 5000, eChkHack_Refresh = 6000, eChkHack_LogLevel = 12, } ;
enum { eCls_MajorCount = 4, eCls_MinorCount = 8, } ;
enum { eWpnMtryIdx_All = 0, eWpnMtryIdx_Sword, eWpnMtryIdx_Axe, eWpnMtryIdx_Spear, eWpnMtryIdx_Blunt, eWpnMtryIdx_Claw, eWpnMtryIdx_Staff, eWpnMtryIdx_Bow, eWpnMtryIdx_Dagger, eWpnMtryIdx_TwoHanded, eWpnMtryIdx_DualWpn, } ;
enum { eBlss_MaxSort = 2, } ;
enum { eHnd_Count = 2, eHnd_Right = 0, eHnd_Left = 1, } ;
enum { eCommandDump=0, } ;
enum { eStronghold_MaxCount = 4, eStronghold_Northwest = 0, eStronghold_Northeast = 1, eStronghold_Southwest = 2, eStronghold_Southeast = 3, } ;
enum { eStronghold_NorthwestSymbol2 = 2297, eStronghold_NortheastSymbol2 = 2307, eStronghold_SouthwestSymbol2 = 2310, eStronghold_SoutheastSymbol2 = 2313, } ;
enum { eZoneType_Normal = 0, eZoneType_God = 1, eZoneType_Guild = 2, } ;
enum { eGuildFriend = 1, eGuildHost = 2, }; 
enum { eGuildAllianceIn = 1, eGuildAllianceOut = 2, };
enum { eArena_MaxEntry = 300, } ;
enum { eGuildAllianceMode_Normal = 0, eGuildAllianceMode_Request = 1, eGuildAllianceMode_Response = 2, };
enum { eGetMoneyYut = 1, eGetMoneySale = 2, eGetMoneyRentalStore = 3, };
enum { eGameEventAttendance = 1, };
//enum { eNPCSato = 1299, };
enum { eRst_Max = 8, eRst_Stun = 0, eRst_Blind, eRst_HoldNSlow, eRst_Sleep, };

union HS2D_COORD
{
	int iBuf ;
	struct
	{
		short x ;
		short y ;
	} ;
};


struct HSRECT
{
	HS2D_COORD LeftTop;
	HS2D_COORD RightBottom;
};


struct TNKALA_ALTAR_OLD // 칼라 제단
{
	short sID ;
	short sTrimuriti ;
	short x ;
	short y ;
	int iKala ;
} ;


/*
const TNKALA_ALTAR_OLD g_krgKalaAltar[eKalaAltar_MaxCount] =
{
	0,  1, 720, 438, 0, // 시바 방면
	1,  1, 720, 466, 0, // 가운데, installed
	2,  1, 720, 494, 0,
	3,  1, 844, 659, 0, // installed
	4,  1, 814, 659, 0, // installed
	5,  1, 688, 547, 0,
	6,  2, 407, 784, 0, // installed
	7,  2, 393, 760, 0,
	8,  2, 369, 749, 0,
	9,  2, 248, 685, 0, // installed
	10, 2, 250, 594, 0, // installed
	11, 2, 364, 597, 0,
	12, 4, 275, 335, 0, // installed
	13, 4, 255, 363, 0,
	14, 4, 294, 363, 0,
	15, 4, 552, 211, 0, // installed
	16, 4, 512, 211, 0, // installed
	17, 4, 543, 323, 0,
} ;
*/

const TNKALA_ALTAR_OLD g_krgKalaAltar2[eKalaAltar_MaxCount] =
{
	0,  1, 908, 717, 0,
	1,  1, 844, 153, 0, // 성 양쪽 1
	2,  1, 933, 153, 0, // 성 양쪽 2
	3,  1, 708, 160, 0, // 요새 1
	4,  1, 708, 118, 0, // 요새 2
	5,  2, 402,  97, 0,
	6,  2, 103, 139, 0, // 성 양쪽 1
	7,  2, 203, 140, 0, // 성 양쪽 2
	8,  2, 125, 568, 0, // 요새 1
	9,  2,  83, 568, 0, // 요새 2
	10, 4, 132, 915, 0, // 초소
	11, 4, 476, 844, 0, // 성 양쪽 1
	12, 4, 476, 934, 0, // 성 양쪽 2
	13, 4, 803, 938, 0, // 요새 1
	14, 4, 803, 896, 0, // 요새 2
	
} ;



struct TNSTRONGHOLD
{	
	int		iID ;
	int		iOwner ; // guild ID
	int		iOwnerFriend;
	char	szGuildName[SZNAME_LENGTH] ;
	DWORD	dwMark;
	CTime	kTimeOccupied ;
	int		irgDestroyer[2] ; // 상징물을 뽀갠 guild ID 저장, 초기화되어야 한다.
	// date, 기타등등
} ;



struct TNCELL
{
	unsigned short usHeight ;
	unsigned short usProperty ;
	unsigned short usEvent ;
	short sGrid ;
} ;



struct TNEVENT
{
	short sCount ; // -1:unlimited, 0<:가능횟수
	short srgTask[eTask_Sort] ;
	unsigned int uiAvailableTime ; // trigger될 수 있는 때, 현재 time이 이 수치보다 작으면, event가 trigger되지 않는다.(variable)
	unsigned int uiCoolDownTime ; // event가 얼마나 자주 trigger될 수 있는가~(static)
	int iDuration ; // 지속시간 type, 0이면 계속 이용가능, 0이상이면 설정 시간끼지 이용 가능, -1이면 이용 불가
	unsigned int uiDurationTime ; // 지정된 시간까지일 경우 time 값 설정
	short sClan ;
	short sProceedType ; // event에 등록된 task가 sequential하게 진행되어야 하는가? 1 이상이면 절대적은 순차 처리를 말한다. 즉 앞의 것이 실패하면 그곳에서 끝난다.
} ;


struct TNTASK
{
	int iActionID ;
	int irgParam[eTask_Param] ;
	TNTASK() : iActionID(0) {} 
} ;


struct TNRoute
{
	int iID;
	int iMethod;
	int irgSegmentListX[MAX_SEGMENT];
	int irgSegmentListY[MAX_SEGMENT];
    int irgSegmentListWait[MAX_SEGMENT];
	int irgSegmentListRange[MAX_SEGMENT];
};

struct TNAGGRSCORE
{
	int iPhysical ;
	int iFire ;
	int iCold ;
	int iLightning ;
	int iPoison ;
	int iHealing ;
	int iTaunt ;
	int iDetaunt ;
} ;

struct TNCHAKRA
{
	short sMuscle ;
	short sNerves ;
	short sHeart ;
	short sMind ;
	TNCHAKRA() : sMuscle(0), sNerves(0), sHeart(0), sMind(0) {}
};


struct TNAFFAIR
{
	byte byTrimuriti ; // byte
	byte byTribe ;
	byte byLevel ;
	int iBramanPoint ;
	int iClass ;
};


struct TNLOCATION
{
	byte byRegion ;
	byte byZone ;
	HS2D_COORD kPos ;
};

struct TNSIGHT
{
	short sPeace ;
	short sCombat ;
} ;


struct TNDAMAGE
{
	int irgBase[2] ;
	int irgPhy[2] ;
	int irgPierce[2] ; // 방어도를 무시하는 damage
	int irgFire[2] ;
	int irgCold[2] ;
	int irgLightning[2] ;
	int irgPoison[2] ;	
	int iSum ;
	int iAttackType ;
	int iDecDef ;

	TNDAMAGE() { iSum = irgBase[0] = irgBase[1] = irgPhy[0] = irgPhy[1] = irgPierce[0] = irgPierce[1] = irgFire[0] = irgFire[1] = irgCold[0] = irgCold[1] = irgLightning[0] = irgLightning[1] = irgPoison[0] = irgPoison[1] = iAttackType = iDecDef = 0 ; }
	//inline TNDAMAGE& operator=( TNDAMAGE a_kDamage ) ;
	//inline void Clear() { iSum = irgPhy[0] = irgPhy[1] = irgFire[0] = irgFire[1] = irgCold[0] = irgCold[1] = irgLightning[0] = irgLightning[1] = irgPoison[0] = irgPoison[1] = irgPierce[0] = irgPierce[1] = 0 ; }
	//inline	void Sum() { iSum = irgPhy[0] + irgFire[0] + irgCold[0] + irgLightning[0] + irgPoison[0] + irgPierce[0] ; }
	
};
/*
TNDAMAGE& TNDAMAGE::operator=(	TNDAMAGE a_kDamage )
{
	irg
}
*/

struct TNCOMBAT_FACTORS
{
	int iAttackRate ;
	int iDodgeRate ;
	int iDodgeSpeed ; // 회피 delay 시간
	int iDefense ;
	int iAC ;
	int irgResist[4] ;
	int iDodgeRateBonus ;
	TNCOMBAT_FACTORS() : iAttackRate(0), iDodgeRate(0), iDodgeRateBonus(0), iDodgeSpeed(0), iDefense(0), iAC(0) { irgResist[0] = irgResist[1] = irgResist[2] = irgResist[3] = 0 ; }
};


struct TNCOST
{
	int iTP ;
	int iHP ;
	short sItemID ;
	byte byItemCount ;
	byte byDummy ;
	TNCOST() : iTP(0), iHP(0), sItemID(0), byItemCount(0) {}
};


struct TNREQUIREMENT
{
	short byTribe ;
	byte byTrimuriti ;
	byte byLevel ;

	int iClass ;
	short sMuscle ;
	short sNerves ;
	short sHeart ;
	short sMind ;

	byte byClass1;
	byte byClass2;
	byte byZone;
	byte byDummy;
	TNREQUIREMENT() : byTrimuriti(0xFF), byTribe(0xFF), byLevel(0), sMuscle(0), sNerves(0), sHeart(0), sMind(0), byZone(0), byClass1(0), byClass2(0), iClass(0xFFFFFFFF) {}
};


struct TNVARIATION
{
	int iPlus ;
	int iPPlus ;
	//int iMinus ;
	//int iPMinus ;

	TNVARIATION() : iPlus(0), iPPlus(0) {} //, iMinus(0), iPMinus(0) {} 
	inline void Clear() { iPlus = iPPlus = 0 ; } //iMinus = iPMinus = 0 ; }
};

struct TNSKILLCASTRECORD
{
	unsigned short sID ;
	byte byLevel ;
	byte byDummy1 ;
	unsigned int uiTime ;
	short sTarget ;
	short sDummy2 ;
};

union HSDATA
{
	int iData ;
	struct
	{
		short sData1 ; // low(낮은 수)
		short sData2 ; // high(높은 수)
	} ;
};


struct TNEFFECT
{
	int iID ;
	HSDATA kFunc ;
	//int iFunction ;
	int iDuration ;
	int iParam1 ;
	int iParam2 ;
	TNEFFECT() : iID(0), /*iFunction(0),*/ iDuration(0), iParam1(0), iParam2(0) {} 
};


struct TNSKILL_DATA
{
	unsigned short sID ;
	short sType ; // log를 남기기 위한 flag, 0x0001과 and 연산 시 true이면 log를 남긴다.
	int iAttackSpeed ;	// 발동하기까지 걸리는 시간, 무기는 공속, skill은 casting time 이다.
	int iReadyTime ;
	int iCastTime ;
	//int iApplyTime ;  // 
	int iActivateTime ;
	int iCoolDownTime ;
	int iCastDuration ; // 발동한 후에 계속 모션을 취하는 시간, -1:passive, 0:instant, 0<:지속시간(초;최대120초)
	int iRange ;
	int iAOE ;

	byte byLevel ;
	byte byMaxLevel ;
	byte bySyncFlag ;
	byte byCastCount ;

	//char iRange ;  // -2:unlimited, -1:weapon-base, 0:self, 0<:range
	//char iAOE ; // -1:N/a, 0:Unit, 0<:범위반경	
	//byte byDummy2 ;
	//byte byDummy3 ;

	byte bySuccessRate ;
	byte byFollow ; // follow가 날아가는 최대 비거리
	byte byPierceRate ; // 관통 확률	
	byte byArmorType ;
	
	short sProperty ;
	short sCombatPhase ;
	short sSpeak ;
	short sSkillType ;
	int iAllowedTargets ;

	TNEFFECT krgEffect[TN_MAX_EFFECT_COUNT] ;
	TNCOST kCost ;
	TNREQUIREMENT kReq ;

	// item 특수
	int iPrice ;
	short sEventID ;
	short sMaxDur ;
	short sItemType ;
	byte byMaxPackCount ;
	byte byDecay ;
	TNDAMAGE kDamage ;

	// skill 특수
	
	int iReqWeapon ;
	int iReqItem ;
	struct TNBASE_SKILL
	{
		unsigned short sID ;
		byte byLevel ;
		byte byDummy ;
	};
	TNBASE_SKILL kReqSkill[2] ;
};

typedef struct TNSKILL_DATA	TNITEM_DATA ;



struct TNAFFECTION
{
	TNEFFECT kEffect ;
	unsigned int uiExpireTime ; // 완료 시간
	unsigned int uiStartTime ;
	int iPartyLeader ;
};



struct TNATTACKER
{
	int iID ;
	int iDamage ; // score를 나타낸다.
	int iScore ;
	unsigned int uiReleaseTime ;
	TNATTACKER() : iID(0), iDamage(0), iScore(0), uiReleaseTime(0) {}
} ;


struct TNLASTEST_TIME
{
	unsigned int uiActivate ; // 활동을 시작하는 시간, 이 수치보다 크면 활동을 한다.
	unsigned int uiMoved ;
	unsigned int uiAttackedOld ; // 이전 이전 공격 시간
	unsigned int uiAttacked ; // 이전 공격 시간
	unsigned int uiDamaged ;
	unsigned int uiKilled ;
	unsigned int uiHealed ;
	unsigned int uiSitted ;
	unsigned int uiSelectTarget ;
	unsigned int uiCombat ;
	unsigned int uiAffectionChecked ;
	unsigned int uiDodged ;
	unsigned int uiReadyTime ;
	unsigned int uiCastTime ;

	void Init( unsigned int a_uiTime )
	{
		uiMoved = uiAttacked = uiAttackedOld = uiHealed = a_uiTime ;
		uiActivate = uiKilled = uiSitted = uiSelectTarget = uiCombat = uiAffectionChecked = uiDodged = uiReadyTime = uiCastTime = 0 ;
	}
} ;


struct TNACTION_LIST // 8 bytes
{
	int iCount ;
	short srgAction[3] ;
} ;


struct TNACTION
{
	short sSpeak ;
	short sGroup ;
	short sAction ;
	unsigned short sSkill ;
	short sState ;
	short sEvent ;
} ;


struct TNSETITEM
{
	int iID;
	int irgReq[MAX_EQUIP]; // 16
	int irgEffectItem[3];
} ;


struct TNSPEECH_CONTENT  // 44 bytes
{
	int iCount ;	
	short srgComment[5] ; 
	short srgType[5] ;
} ;

struct TNCONSIDER
{
	int irgVal[eCon_MaxGapCount][eCon_PrtyCount] ;
} ;


struct TNJUDGE_COMBAT_VALUE
{
	int irgJudgeCombat[eCon_JudgeCombat][3] ; // critical/normal/miss
} ;



typedef struct _KALA_LOCATION
{
	int iLocation ;
	int iID ;
	int iClan ;
} KALA_LOCATION ;

typedef struct _KALA_REWARDER
{
	int iClan ;
	int x ;
	int y ;

} KALA_REWARDER ;

typedef struct _RVR_RECORD
{
	KALA_LOCATION krgKala[eKala_MaxCount] ;
	KALA_REWARDER krgRewarder[3] ;
	int iWinnerClan ;
	int irgEntryCount[5] ;
} RVR_RECORD ;


#ifdef __ZONE_SERVER__
	struct TNJUDGE_COMBAT
	{
		TNDeck100 krgJudgeCombat[eCon_JudgeCombat] ;
	} ;
#endif

/*
struct TNAILIST // 56(14*4) bytes
{
	short sRest ;  // 1
	short sMove ;
	short sArrive ;
	short sDetect ;
	short sHelp1 ;
	short sLink1 ;
	short sGuard1 ;
	short sBeKilled1 ;
	short sUnderAttack1 ;
	short sAttack ; // 10
	short sHit ;
	short sMiss ;
	short sBeHitted ;
	short sDodge ;
	short sTrace ;
	short sGiveUpToTrace ;
	short sKillEnemy ;
	short sHelp2 ;
	short sLink2 ;
	short sGuard2 ;  // 20
	short sBeKilled2 ;
	short sUnderAttack2 ; 
	short sCantTrace ;
	short sReturn ;
	short sFlee ;
	short sLead ;
	short sPop ;  // 27
	short srgDialog[4] ;  // 31
} ;
*/


struct TNCOEFFICIENT
{
	int iDagger ;
	int iSword ;
	int iTwoHandSword ;
	int iAxe ;
	int iTwoHandAxe ;
	int iBlunt ;
	int iSpear ;
	int iStaff ;
	int iClaw ;
	int iBow ;
	int iThrowing ;
	int iBare ;
	int iShield ;
	int iHP ;
	int iTP ;
	int iRecvry ;
	int iAC ;
	int iResist ;
	int iAttackRate ;
	int iDodgeRate ;
	int iAttackSpeed ;
	int iCastSpeed ;
	int iDodgeSpeed ;
};


struct TNEFFECTTOLERANCE
{
	int iHold ;
	int iStun ;
	int iSleep ;
	int iBlind ;
	int iTerror ;
	int iTaunt ;
	int iSlowMove ;
	int iSlowAttack ;
} ;

typedef enum _ETNItemPlace
{
	ePlace_Cargo = 0x00,
	ePlace_Inven = 0x01,
	ePlace_Equip = 0x02,
} ETNItemPlace;


typedef enum _ETNRace
{
	eTNRac_Naga		= 0x01,
	eTNRac_Asura	= 0x02,
	eTNRac_Yaksa	= 0x04,
	eTNRac_Deva		= 0x08,
	eTNRac_KimNara	= 0x10,
	eTNRac_Rakshasa = 0x20,
	eTNRac_Gandharva = 0x40,
	eTNRac_Garuda	= 0x80,
	eTNRac_GM		= 0x00,
} ETNRace ;


typedef enum _ETNCombatSyncPhase
{
	eTNCSP_Echo = 0,
	eTNCSP_Calculate,
} ETNCombatSyncPhase ;

typedef enum _ETNResult
{
	eTNRes_Succeeded = 0,
	eTNRes_Failed = 1,
	eTNRes_InvalidHandle = 2, 
	eTNRes_InvalidGuild = 3,
	eTNRes_PCOnly = 4,
	eTNRes_NPCOnly = 5,
	eTNRes_IsFriend = 6,
	eTNRes_IsEnemy = 7,
	eTNRes_IsDead = 8,
	eTNRes_IsGM = 9,
	
	//eTNRes_InvalidTarget = 10,
	eTNRes_InvalidCoord = 11,
	eTNRes_IsNotFound = 12,
	eTNRes_SafetyZone = 13,
	eTNRes_BlockedZone = 14,
	eTNRes_NotEmpty = 15,
	eTNRes_HaveDontAttackAffection = 16,
	eTNRes_HaveInvulnerableAffection = 17,
	eTNRes_Sit = 18,
	eTNRes_HackUser = 19,
	
	eTNRes_ReqLevel = 20,
	eTNRes_ReqTrimuriti = 21,
	eTNRes_ReqRace = 22,
	eTNRes_ReqClass = 23,
	eTNRes_ReqCaste = 24,
	eTNRes_ReqChakra = 25,
	eTNRes_ReqBaseSkill = 26,
	eTNRes_ReqWeapon = 27,
	eTNRes_ReqItem = 28,
	
	eTNRes_OutOfRange = 30,
	eTNRes_PathIsBlocked = 31,
	eTNRes_OutofMeleeRange = 32,
	eTNRes_CellBlocked = 33,
	eTNRes_Obstacle = 34,
	eTNRes_TooHigh = 35,

	eTNRes_TargetSelf = 40,
	eTNRes_TargetClan = 41,
	eTNRes_TargetNovice = 42,
	eTNRes_LevelIsNotAllowed = 45,
	eTNRes_TooHighKarma = 46,
	eTNRes_HaveNoGuild = 47,
	eTNRes_HaveNoMaster = 48,


	eTNRes_EvntInvalidEventNo = 50,
	eTNRes_EvntInvalidUserHandle = 51,
	eTNRes_EvntInvalidNPCHandle = 52,
	eTNRes_EvntInvalidQuestID = 53,
	eTNRes_EvntInvalidSkillID = 54,
	eTNRes_EvntNotCoolYet = 55,
	eTNRes_EvntSwitchOff = 56,
	eTNRes_EvntUseTimeOver = 57,
	eTNRes_EvntDiffClan = 58,
	eTNRes_EvntItemNotFound = 59,

	eTNRes_InvalidSlotIndex = 60,
	eTNRes_AltarIsNotEmpty = 61,
	eTNRes_InvalidLocation = 62,

	eTNRes_InvalidTarget0 = 70,
	eTNRes_InvalidTarget1 = 71,
	eTNRes_InvalidTarget2 = 72,
	eTNRes_InvalidTarget3 = 73,
	eTNRes_InvalidTarget4 = 74,
	eTNRes_InvalidTarget5 = 75,
	eTNRes_InvalidTarget6 = 76,
	eTNRes_InvalidTarget7 = 77,
	eTNRes_InvalidTarget8 = 78,
	eTNRes_InvalidTarget9 = 79,

	eTNRes_SkillNotRegistered = 100,
	eTNRes_SkillNotLearned = 101,
	eTNRes_SkillNotCoolYet = 102,
	eTNRes_SkillNotActionYet = 103,
	eTNRes_SkillCantLearnMore = 104,
	eTNRes_SkillHaveNotSkillPoint = 105,
	eTNRes_SkillPassiveSkill = 106,
	eTNRes_SkillReset = 107,
	eTNRes_CostTP = 110,
	eTNRes_CostHP = 111,
	eTNRes_CostItem = 112,

	eTNRes_LackInventorySlot = 120,
	eTNRes_ArenaEntryIsFull	= 121,
	eTNRes_AlreadyRegisteredInArenaEntry = 122,
	eTNRes_AlreadyRegisteredInSiegeEntry = 131,
	eTNRes_ExpiryOftheTerm = 132,

	// targeting
	eTNRes_IsPartyMember = 140,
	eTNRes_IsSameGuildMember = 141,
	eTNRes_IsAlly = 142,

} ETNResult ;




typedef enum _ETNMessage
{
	eTNMsg_Recover = 0,
	eTNMsg_Affection,
	eTNMsg_Skill,
	
} ETNMessage ;




typedef enum _ETNSklILL
{
	eTNSkl_NormalAttack = 0,

	eTNSklF_HaveNotFollow = 0,
	eTNSklF_Follow = 1,

	eTNSklR_Unlimited = -2, // range
	eTNSklR_WeaponBase = -1,
	eTNSklR_Self = 0, 

	eTNSklA_NA = -1,  // area(or target)
	eTNSklA_Unit = 0,

	eTNSklD_Instant = 0, // duration
	eTNSklD_Unlimited = -1,

} ETNSklill ;




typedef enum _ETNENTITY
{
	eTNEnt_INVALID = 0,
	eTNEnt_Pc = 100,
	eTNEnt_Monster = 200,
	eTNEnt_Npc = 300,
	eTNEnt_Item = 400,
	eTNEnt_Forbidden = 1000 ,
	eTNEnt_TResainStructure = 1100 ,
	eTNEnt_SpecialStructure = 1200 ,
	eTNEnt_EventStructure = 1300
} ETNEntity ;



// bit vector 로 한다.
typedef enum _ETNFsmState
{
	eTNFsm_None		= -2,
	eTNFsm_Dead		= -1,

	eTNFsm_Sit		= 0,
	eTNFsm_Stand	= 1,
	eTNFsm_Run		= 3, 
	eTNFsm_Walk		= 4,

	eTNFsm_Help		= 10,
	eTNFsm_Link		= 11,

} ETNFsmState ;


typedef enum _ETNCharacter
{
	eTNChr_PistAttackSpeed	= 1500,

	eTNChr_MoveSpeed		= 5,
	eTNChr_DevaMvSpeed		= 4,
	eTNChr_GMMvSpeed        = 10,

	eTNChr_MeleeAttackRange = 2,
	eTNChr_DistCorrect		= 6,
	eTNChr_Vaisha			= 55000,
} eTNCharacter ;



// affection을 동시에 여러 가지가 있을 수 있기 때문에 bitvector과 같은 방법을 써야 한다.
// skill(magic)에 의해 영향을 받는 목록들을 포함한다.
typedef enum _ETNAffectionState
{
	eTNAfn_None = 0,
	eTNAfn_Damage = 1,
	eTNAfn_DamageSplash = 2,
	eTNAfn_EnergyOfSword = 3,
	eTNAfn_PierceDamage = 4, // phycical, 방어력 100% 무시
	eTNAfn_DamageTP = 5, // TP를 줄인다.
	eTNAfn_PercentDamage = 6, // Max HP의 일정 % HP를 줄인다.
	eTNAfn_Fire = 10,
	eTNAfn_Cold = 11,
	eTNAfn_Lightning = 12,
	eTNAfn_Poison = 13, 
	eTNAfn_FireSplash = 14,
	eTNAfn_ColdSplash = 15,
	eTNAfn_LightningSplash = 16,
	eTNAfn_PoisonSplash = 17,
	eTNAfn_DOTbyDice = 18,

	eTNAfn_Summon = 100,
	eTNAfn_Illusion = 110,
	eTNAfn_SummonFamiliar = 120,
	eTNAfn_SummonTracker = 130,
	eTNAfn_SummonTotem = 140,
	eTNAfn_SummonInteractor = 150,
	eTNAfn_SummonInteractor2 = 151,
	eTNAfn_SummonRetainer = 160,
	eTNAfn_LayMine = 170,
	eTNAfn_LayMine2 = 171,
	eTNAfn_SummonPet = 180,
	eTNAfn_SummonPetRandomly = 181,


	eTNAfn_Invisible = 1060,
	eTNAfn_WizardEyes = 1065,
	eTNAfn_Hold	= 2000,
	eTNAfn_Hold2 = 2005, // seidge mode
	eTNAfn_HoldNSlowMove = 2006, 
	eTNAfn_Stun = 2010, // 기절
	eTNAfn_Sleep = 2020, // 잠
	eTNAfn_Blind = 2040, // 장님, 시야를 1로 줄인다.
	eTNAfn_Concentration = 2210,
	eTNAfn_Disruption = 2220,
	eTNAfn_Invulnerable = 2230,
	eTNAfn_Immunity = 2240,
	eTNAfn_Immunity2 = 2241,
	eTNAfn_MagicShield = 2500,
	eTNAfn_BreakMagicShield = 2505,
	eTNAfn_ManaShield = 2510,
	eTNAfn_SpiritLink = 2520,
	eTNAfn_BreakLinkOfSpirit = 2525,
	eTNAfn_EnhancedMagicShield = 2530,
	eTNAfn_BreakEnhancedMagicShield = 2535,
	eTNAfn_TP2Zero = 2540,
	eTNAfn_CantRecoverTP = 2550,
	eTNAfn_ProtectFromAttackOnlyOnce = 2560,

	// 특수 용도
	eTNAfn_ExpandBag30 = 2900,
	eTNAfn_ProtectFromPK = 2910,
	eTNAfn_ProtectFromMonster = 2915,
	eTNAfn_ResetStat = 2920,
	eTNAfn_ResetSkill = 2930,
	eTNAfn_Log = 2940,
	eTNAfn_LogImmu = 2941,
	eTNAfn_Debug = 2945,
	eTNAfn_BlessOfGod = 2950,
	eTNAfn_ResetClass = 2960,
	eTNAfn_RepairAll = 2970,
	eTNAfn_ResetQuest = 2980,
	eTNAfn_BonusExp = 2990,

	eTNAfn_ExpandBag7 = 2971,
	eTNAfn_ExpandStore7 = 2972,
	eTNAfn_AMoneyRoot7 = 2973,
	eTNAfn_MAtman7 = 2974,
	eTNAfn_MAnubaba7 = 2975,
	eTNAfn_M15Chakra7 =2976,

	eTNAfn_ExpandStore30 = 2981,
	eTNAfn_AMoneyRoot30 = 2982,
	eTNAfn_MAtman30 = 2983,
	eTNAfn_MAnubaba30 = 2984,
	eTNAfn_M15Chakra30 =2985,
	eTNAfn_FuncBeauty = 2991,
	eTNAfn_ExpandFunc = 2998,
	eTNAfn_ExpandItem = 2999,

	eTNAfn_StealHP = 3000,
	eTNAfn_StealTP = 3010,
	eTNAfn_BonusDamage = 3020,
	eTNAfn_BonusDamage2 = 3021,
	eTNAfn_BonusDamage3 = 3022,
	eTNAfn_BonusDamage4 = 3023,
	eTNAfn_BonusDamage5 = 3024,
	eTNAfn_BonusDamage6 = 3025,
	eTNAfn_BonusDamage7 = 3026,
	etnAfn_BonusDamage8 = 3027,
	etnAfn_BonusDamage9 = 3028,
	eTNAfn_BonusEffect	= 3030,
	eTNAfn_MultipleStrike = 3040,
	eTNAfn_CriticalStrike = 3050,
	eTNAfn_PierceStrike = 3060,
	eTNAfn_PierceStrike2 = 3061,
	eTNAfn_HPDown = 3065,
	eTNAfn_KnockBack = 3070,
	eTNAfn_Pull = 3075,
	eTNAfn_Heal = 3080,
	eTNAfn_RecoverTP = 3085,
	eTNAfn_Cure = 3090,
	eTNAfn_TPBurn = 3100,
	eTNAfn_Resurrect = 3110,
	eTNAfn_ReflectDamage = 3120,
	eTNAfn_AbsorbDamage= 3130,
	eTNAfn_AbsorbElementalDamage= 3135,
	eTNAfn_Terror = 3140, // 도망가게 한다.
	eTNAfn_Taunt = 3150, // 약 올려서 공격하게 한다.
	eTNAfn_DeTaunt = 3151,
	eTNAfn_RangeUp = 3160,
	eTNAfn_RangeDown = 3165,
	eTNAfn_TownPortal  = 3170,
	eTNAfn_TownPortal2 = 3180,
	eTNAfn_TownPortal3 = 3181,
	eTNAfn_SaveTPCost = 3190,
	eTNAfn_SlayerItem = 3200,
	eTNAfn_PreventRegenHP = 3210,
	eTNAfn_PreventRegenTP = 3220,
	eTNAfn_SkillUp = 3230,
	eTNAfn_Dash = 3240,
	eTNAfn_Teleport = 3250,
	eTNAfn_CantUsePotion = 3260,
	eTNAfn_100PCriticalHit = 3270, // 100% 크리티컬 히트
	eTNAfn_Recall = 3280,
	eTNAfn_Weakness = 3290,
	eTNAfn_SuccessRate = 3300,
	eTNAfn_SummonParty = 3310,
	eTNAfn_MoveToTheMandraTown = 3320,
	eTNAfn_ReduceKaram = 3330,
	eTNAfn_SummonFriend = 3340,
	eTNAfn_Sucide = 3350,

	eTNAfn_WeaponMastery = 4000,	
	//eTNAfn_MagicMastery = 4010, // elemental damage
	eTNAfn_ElementalDamagePlus = 4010,
	eTNAfn_ElementalDamageMinus = 4011,
	eTNAfn_DamagePlus = 4100,
	eTNAfn_DamageMinus = 4101,
	eTNAfn_DamagePlus2 = 4102,
	eTNAfn_DamageMinus2 = 4103,
	eTNAfn_FireDamagePlus = 4110,
	eTNAfn_FireDamageMinus = 4111,
	eTNAfn_ColdDamagePlus = 4120,
	eTNAfn_ColdDamageMinus = 4121,
	eTNAfn_LightningDamagePlus = 4130,
	eTNAfn_LightningDamageMinus = 4131,
	eTNAfn_PoisonDamagePlus = 4140,
	eTNAfn_PoisonDamageMinus = 4141,
	eTNAfn_FireResistPlus = 4150,
	eTNAfn_FireResistMinus = 4151,
	eTNAfn_ColdResistPlus = 4160,
	eTNAfn_ColdResistMinus = 4161,
	eTNAfn_LightningResistPlus = 4170,
	eTNAfn_LightningResistMinus = 4171,
	eTNAfn_PoisonResistPlus = 4180,
	eTNAfn_PoisonResistMinus = 4181,
	eTNAfn_MusclePlus = 4200,
	eTNAfn_MuscleMinus = 4201,
	eTNAfn_MusclePlus2 = 4202,
	eTNAfn_NervesPlus = 4210,
	eTNAfn_NervesMinus = 4211,
	eTNAfn_NervesPlus2 = 4212,
	eTNAfn_HeartPlus = 4220,	
	eTNAfn_HeartMinus = 4221,
	eTNAfn_HeartPlus2 = 4222,
	eTNAfn_MindPlus = 4230,
	eTNAfn_MindMinus = 4231,
	eTNAfn_MindPlus2 = 4232,
	eTNAfn_AllResistPlus = 4240,
	eTNAfn_AllResistMinus = 4241,
	eTNAfn_AllStatePlus = 4250,
	eTNAfn_AllStateMinus = 4251,
	eTNAfn_AllStatePlus2 = 4252,
	eTNAfn_AllStateMinus2 = 4253,
	eTNAfn_AllDamagePlus = 4260,
	eTNAfn_AllDamageMinus = 4261,
	eTNAfn_FixedDamagePlus = 4270, // 계산 후에 최종 단계에서 추가된다.
	eTNAfn_FixedDamageMinus = 4271,
	eTNAfn_FixedDamagePlus2 = 4280, // 계산 후에 최종 단계에서 추가된다.
	eTNAfn_FixedDamageMinus2 = 4281,
	eTNAfn_AttackRatePlus = 4300,
	eTNAfn_AttackRateMinus = 4301,
	eTNAfn_AttackRatePlus2 = 4302,
	eTNAfn_AttackRateMinus2 = 4303,
	eTNAfn_DodgeRatePlus = 4310,
	eTNAfn_DodgeRateMinus = 4311,
	eTNAfn_DodgeRatePlus2 = 4312, // new
	eTNAfn_DodgeRateMinus2 = 4313, // new
	eTNAfn_DodgeSpeedUp = 4340,
	eTNAfn_DodgeSpeedDown = 4341,
	eTNAfn_DefensePlus = 4330,
	eTNAfn_DefenseMinus = 4331,
	eTNAfn_DefensePlus2 = 4332,
	eTNAfn_DefenseMinus2 = 4333,
	eTNAfn_ACPlus = 4320,
	eTNAfn_ACMinus = 4321,
	eTNAfn_MaxHPPlus = 4400,
	eTNAfn_MaxHPMinus = 4401,
	eTNAfn_MaxHPPPlus = 4402,
	eTNAfn_MaxHPPMinus = 4403,
	eTNAfn_MaxHPPlusByMind = 4404,
	eTNAfn_LockMaxHP = 4405,
	eTNAfn_MaxHPPlus2 = 4406,
	eTNAfn_MaxTPPlus2 = 4407,
	eTNAfn_HPRecoveryPlus = 4410,
	eTNAfn_HPRecoveryMinus = 4411,
	eTNAfn_MaxTPPlus = 4420,
	eTNAfn_MaxTPMinus = 4421,
	eTNAfn_MaxTPPlusByMind = 4424,
	eTNAfn_LockMaxTP = 4425,
	eTNAfn_TPRecoveryPlus = 4430,
	eTNAfn_TPRecoveryMinus = 4431,
	eTNAfn_MoveSpeedPlus = 4440,
	eTNAfn_MoveSpeedMinus = 4441,
	eTNAfn_MoveSpeedMinus2 = 4442,
	eTNAfn_AttackSpeedPlus = 4450,
	eTNAfn_AttackSpeedMinus = 4451,
	eTNAfn_CastSpeedPlus = 4460,
	eTNAfn_CastSpeedMinus = 4461,
	eTNAfn_EnhanceWeapon = 4470,
	eTNAfn_LostTrace = 4480,
	eTNAfn_EnhanceArmor = 4490,
	eTNAfn_VictoryHPBonus = 4500,
	eTNAfn_VictoryTPBonus = 4505,
	eTNAfn_CriticalBonus = 4510,
	eTNAfn_HealPlus		= 4520,
	eTNAfn_RecoverTPPlus	= 4530,
	eTNAfn_EnhanceHardnessOfArmor = 4540,
	eTNAfn_DamageBonusForNextAttack = 4550,
	//eTNAfn_PerfectDodge = 4560,
	eTNAfN_PetGrowth = 4570,
	eTNAfn_ChangeTrimuritiSiva = 4580,
	eTNAfn_ChangeTrimuritiBrahma = 4590,
	eTNAfn_ChangeTrimuritiVishnu = 4600,
	//	EVENT
	eTNAfn_RefiningJade			= 4610,		//	아이템 소멸방지
	eTNAfn_RefiningDecrease		= 4611,		//	아이템 레벨 감소(주재련 실패시)
	eTNAfn_RefiningDiscount		= 4620,		//	제련비용 감소
	eTNAfn_RefiningRateUp		= 4630,		//	제련확률 상승
	eTNAfn_RefiningProtect		= 4640,		//	제련재료 소멸방지
	eTNAfn_PranaRatebyLevel		= 4650,		//	프라나 획득치 상승 또는 하향
	eTNAfn_DeathPranaRatebyLevel= 4660,		//	사망치 프라나 감소비율
	eTNAfn_MoneyRatebyLevel		= 4670,		//	루피아 습득 비율
	//	eTNAfn_Attendence		= 4680,		//	출석체크이벤트(웹에서 해결)
	eTNAfn_LevelUpFromLevel1	= 4690,		//	레벨을 1개 업시켜준다(레벨기준)
	eTNAfn_LevelUpFromLevel3	= 4691,		//	레벨을 3개 업시켜준다(레벨기준)
	eTNAfn_LevelUpFromLevel5	= 4692,		//	레벨을 5개 업시켜준다(레벨기준)
	eTNAfn_GiveItem				= 4700,		//	아이템을 인벤에 지급한다.
	eTNAfn_ChangeTribeFromLevel = 4710,		//	케릭터의 종족을 바꿔준다(레벨기준)
	eTNAfn_Coupon				= 4720,		//	쿠폰이벤트 - 아이템 1개지급
	eANAfn_GiveItemMaharaja		= 4730,		//	마하라자에게 선물을 지급한다
	eANAfn_QuestStatus			= 4740,		//	스크립트 퀘스트를 발동시킨다.

	eTNAfn_ResistStun = 4800,
	eTNAfn_ResistSleep = 4810,
	eTNAfn_ResistBlind = 4820,
	eTNAfn_ResistHoldNSlow = 4830,


	// etc
	eTNAfn_Birth		= 10000,
	eTNAfn_Death		= 10010,
	eTNAfn_FireFX		= 10020,
	eTNAfn_UnPack		= 10030,
	eTNAfn_IWantIt		= 10040,
	eTNAfn_MicroSound	= 10041,

} ETNAffectionState ;


// client에 affection 정보를 알려주기 위한 bit-vector이다.
typedef enum _ETNVisualAffection
{
	eTNVSAfn_DontMove				= 0x00002380,
	eTNVSAfn_DontAttack				= 0x00000300,
	eTNVSAfn_CantDefense			= 0x00000700,

	// Outer Affections
	eTNVSAfn_Empty					= 0x00000000,
	eTNVSAfn_Damage					= 0x00000001,
	eTNVSAfn_Fire					= 0x00000002,
	eTNVSAfn_Cold					= 0x00000004,
	eTNVSAfn_Lightning				= 0x00000008,
	eTNVSAfn_Poison					= 0x00000010, 
	eTNVSAfn_Invisible				= 0x00000020,
	eTNVSAfn_WizardEyes				= 0x00000040,	
	eTNVSAfn_Hold					= 0x00000080,
	eTNVSAfn_Stun					= 0x00000100, 
	eTNVSAfn_Sleep					= 0x00000200, 
	eTNVSAfn_Blind					= 0x00000400, 
	eTNVSAfn_Invulnerable			= 0x00000800, // 10
	eTNVSAfn_MagicShield			= 0x00001000, // 아수라 - 파라카
	eTNVSAfn_Hold2					= 0x00002000, // seidge mode	
	eTNVSAfn_ManaShield				= 0x00004000, // 데바 - 마나쉴드
	eTNVSAfn_ReflectDamage			= 0x00008000,
	eTNVSAfn_RecoverTP				= 0x00010000,	
	eTNVSAfn_Heal					= 0x00020000, 
	eTNVSAfn_Weakness				= 0x00040000,
	eTNVSAfn_EnhancedMagicShield	= 0x00080000,
	eTNVSAfn_MoveSpeedMinus2		= 0x00100000,
	eTNVSAfn_ProtectFromMonster		= 0x00200000,
	eTNVSAfn_MoveSpeedPlus			= 0x00400000,
    eTNVSAfn_MoveSpeed140R			= 0x01600000,
	eTNVSAfn_MoveSpeed140B			= 0x00600000,	
	eTNVSAfn_MoveSpeedMinus			= 0x00800000,  
	eTNVSAfn_AttackSpeedPlus		= 0x01000000,
	eTNVSAfn_AttackSpeedMinus		= 0x02000000, 
	eTNVSAfn_ProtectFromAttackOnlyOnce= 0x04000000,
	eTNVSAfn_ProtectAll				= 0x08000000,
	eTNVSAfn_HaveKalaCore			= 0x10000000,
	eTNVSAfn_ProtectFromPK			= 0x20000000, // 30
	eTNVSAfn_PKAttacker				= 0x40000000, // 선제공격자
	eTNVSAfn_BlessOfGod				= 0x80000000, // eTNVSAfn_HaveKalaCore과 절대 중복되지 않는다.

	// Inner Affections
	eTNInAfn_Empty					= 0x00000000,
	eTNInAfn_Taunt					= 0x00000001,
	eTNInAfn_DeTaunt				= 0x00000002,
	eTNInAfn_Immunity				= 0x00000004,
	eTNInAfn_SpiritLink             = 0x00000008,
	eTNInAfn_PreventRegenHP			= 0x00000010,
	eTNInAfn_PreventRegenTP         = 0x00000020,
	eTNInAfn_LostTrace				= 0x00000040,	
	eTNInAfn_EnhanceHardnessOfArmor	= 0x00000080,
	eTNInAfn_Immunity2				= 0x00000100,
	eTNInAfn_CantRecoverTP			= 0x00000200,
	
} ETNVisualAffection ;


typedef enum _ETNInnerAffection
{
} ETNInnerAffection ;


typedef enum _ETNEye // 보지 못하는 목록이 bit vector로 등록되어야 한다.
{
	eTNEye_DetectAll				= 0x00000000,
	eTNEye_DetectVisibleOnly		= eTNVSAfn_Invisible, //0x00000020,
} ETNEye ;


typedef enum _ETNImmunity
{
	eTNImm_Damage				= 0x00000001,
	eTNImm_Fire					= 0x00000002,
	eTNImm_Cold					= 0x00000004,
	eTNImm_Lightning			= 0x00000008,
	eTNImm_Poison				= 0x00000010, 
	eTNImm_Pierce   			= 0x00000020,
	eTNImm_Weaken				= 0x00000040, 
	eTNImm_Hold					= 0x00000080,
	eTNImm_Stun					= 0x00000100, 
	eTNImm_Sleep				= 0x00000200, 
	eTNImm_Blind				= 0x00000400, 
	eTNImm_KnockBack			= 0x00000800,
	eTNImm_Pull					= 0x00001000,
	eTNImm_PreventRegenHP		= 0x00002000, // 8192
	eTNImm_PreventRegenTP		= 0x00004000, // 16384
	eTNImm_Terror				= 0x00008000,
	eTNImm_Heal					= 0x00010000,
	//eTNImm_Invulnerable			= 0x00000800, // 10
	//eTNImm_MagicShield			= 0x00001000,	
	//eTNImm_RecoverTP			= 0x00004000,
	//eTNImm_ReflectDamage		= 0x00008000,
	//eTNImm_FireDamagePlus		= 0x00010000,
	//eTNImm_ColdDamagePlus		= 0x00020000,
	//eTNImm_LightningDamagePlus	= 0x00040000,
	//eTNImm_PoisonDamagePlus		= 0x00080000, // 20
	//eTNImm_PFStronghold1		= 0x00100000,
	//eTNImm_PFStronghold2		= 0x00200000,
	//eTNImm_PFStronghold3		= 0x00400000,
	//eTNImm_PFStronghold4		= 0x00800000,
	eTNImm_MoveSpeedMinus		= 0x01000000,  
	//eTNImm_AttackSpeedPlus	= 0x02000000,
	eTNImm_AttackSpeedMinus		= 0x04000000, // 27
	eTNImm_HPDown				= 0x08000000,
	eTNImm_MaxHPDown			= 0x10000000,
	//eTNImm_Elemental			= 0x20000000,
	//eTNImm_Elemental			= 0x40000000,
	//eTNImm_All				= 0x80000000, // 살제로는 아래와 같이 모든 bit가 1인 경우에 대한 값을 가져야 한다.
	eTNImm_All					= 0xFFFFFFFF,
} ETNImmunity ;



typedef enum _ETNVariationIndex
{
	eTNVar_MinDamage = 0,
	eTNVar_MaxDamage,
	eTNVar_FireDamage, 
	eTNVar_ColdDamage,
	eTNVar_LightningDamage,
	eTNVar_PoisonDamage,
	eTNVar_FireResist, 
	eTNVar_ColdResist,
	eTNVar_LightningResist,
	eTNVar_PoisonResist,
	eTNVar_Muscle, // 10
	eTNVar_Nerves,
	eTNVar_Heart,
	eTNVar_Mind,
	eTNVar_AttackRate,
	eTNVar_DodgeRate,
	eTNVar_AC,
	eTNVar_MaxHP,
	eTNVar_HPRecovery,
	eTNVar_MaxTP,
	eTNVar_TPRecovery, // 20
	eTNVar_MoveSpeed,
	eTNVar_AttackSpeed,
	eTNVar_CastSpeed,
	eTNVar_RangeUp,
	eTNVar_Concentration,  //25
	eTNVar_Disruption,
	eTNVar_ReflectDamage,
	eTNVar_AbsorbDamage, // 28
	eTNVar_Defense, //
	eTNVar_DodgeSpeed, // 30
	eTNVar_EnhanceWeapon,
	eTNVar_SaveTPCost,
	eTNVar_LockMaxHP,
	eTNVar_LockMaxTP, // 34,
	eTNVar_SpiritLink, // 35,
	eTNVar_SuccessRate, // 36, limit
	eTNVar_EnhanceHelmet = 37,
	//eTNVar_EnhanceHardness = 38, // 내구도 감소율을 줄인다.
	eTNVar_DamageBonusForNextAttack = 38,
	eTNVar_RangeDown = 39,
	eTNVar_EnhanceNecklace = 40,
	eTNVar_EnhanceArmor = 41,
	eTNVar_EnhanceBelt = 42,
	eTNVar_PetGrowthHP = 43,
	eTNVar_PetGrowthDamage = 44,
	eTNVar_PetGrowthAttackSpeed = 45,
	eTNVar_ReduceKaram = 46,
	eTNVar_EnhanceBoots = 49,
	eTNVar_EnhanceGloves = 50,
	eTNVar_EnhancePants = 51,
	eTNVar_VictoryHPBonus = 52,
	eTNVar_VictoryTPBonus = 53,
	eTNVar_CriticalBonus = 54,
	eTNVar_PranaBonus = 55,
	eTNVar_FixedDamage = 56,
	eTNVar_HealPlus = 57,
	eTNVar_RecoverTPPlus = 58,
	eTNVar_FixedDamage2 = 59,
	eTNVar_AbsorbElementalDamage = 60,
	eTNVar_EnhanceHardnessOfArmor = 61,
	eTNVar_EnhancedMagicShield = 62,
	eTNVar_ResistStun = 63,
	eTNVar_ResistBlind = 64,
	eTNVar_ResistHoldNSlow = 65,
	eTNVar_ResistSleep,

} ETNVariationIndex ;


typedef enum _ETNItemType
{
	eTNItm_Invalid			= -1,
	eTNItm_OneHandWeapon	= 0x00000001,
	eTNItm_TwoHandWeapon	= 0x00000002,
	eTNItm_Shield			= 0x00000004,
	eTNItm_Armor			= 0x00000008,
	eTNItm_Helmet			= 0x00000010,
	eTNItm_Belt				= 0x00000020,
	eTNItm_Boots			= 0x00000040,
	eTNItm_Earring			= 0x00000080,
	eTNItm_Neckrace			= 0x00000100,
	eTNItm_Ring				= 0x00000200,
	eTNItm_Bracelet			= 0x00000400,
} ETNItemType ;



typedef enum _ETNEquipmentSlot
{
	eTNEqu_Helmet				= 0,
	eTNEqu_EarringRight			= 1,
	eTNEqu_EarringLeft			= 2,
	eTNEqu_Necklace				= 3,
	eTNEqu_Armor				= 4, 
	eTNEqu_Belt					= 5,
	eTNEqu_OneHandWeapon		= 6,
	eTNEqu_Shield				= 7,
	eTNEqu_BraceletRight		= 8,
	eTNEqu_BraceletLeft			= 9,
	eTNEqu_RingRight			= 10,
	eTNEqu_RignLeft				= 11,
	eTNEqu_Boots				= 12,
	eTNEqu_Gloves				= 13,
	eTNEqu_Pants				= 14,
	eTNEqu_Bag					= 15,
	eTNEqu_TwoHandWeapon		= 100,
} ETNEquipmentSlot ;


// 모두 one-hand weapon
typedef enum _ETNWeaponType
{
	eTNWpn_Sword			= 0x0001,
	eTNWpn_Axe				= 0x0002,	
	eTNWpn_Spear			= 0x0004,
	eTNWpn_Blunt			= 0x0008,
	eTNWpn_Claw				= 0x0010,
	eTNWpn_Staff			= 0x0020,  // 32
	eTNWpn_Bow				= 0x0040,  // 64
	eTNWpn_Dagger			= 0x0080,  // 128
	eTNWpn_Shield			= 0x0100,  // 256
	eTNWpn_TwoHand  		= 0x0200,  // 512
	eTNWpn_DualHand			= 0x0400,  // 1024
	eTNWpn_Bare				= 0x0800,
	eTNWpn_All				= 0xFFFF,  // 65535

	eTNWpn_Heavy			= 0x0006,
} ETNWeaponType ;


typedef enum _ETNSkillType
{
	eTNSklT_Affection		= 0x0001,
	eTNSklT_Instant			= 0x0002,
	eTNSklT_Aid				= 0x0004,
	eTNSklT_Splash			= 0x0010,
	eTNSklT_MultipleStrike	= 0x0020,
	eTNSklT_EnergyOfSword   = 0x0040,
	eTNSklT_Resurrect		= 0x0080,
	eTNSklT_Fire			= 0x0100,
	eTNSklT_Cold			= 0x0200,
	eTNSklT_Lightning		= 0x0400,
	eTNSklT_Poison			= 0x0800,
	eTNSklT_ChangeTP		= 0x1000,
	eTNSklT_ChangeHP		= 0x2000,
} ETNSkillType ;


typedef enum _ETNCombatPhase
{
	// 아래의 6개는 combat progress를 나타낸다. bit가 check가 되어 있으면 그 과정을 수행한다.
	eTNCPhase_CastInstant1		= 0x0001,  // caster 자신에서 계산, damage up/down 계열
	eTNCPhase_CastInstant2		= 0x0002,  // caster 자신에서 계산, 추가적인 damage 관련 effect, pierce strike, critical-strike, multiple-strike
	eTNCPhase_DealDamage		= 0x0004,  // caster 자신에서 계산, deal damage
	eTNCPhase_CastInstant3		= 0x0008, // caster 자신에서 계산, steal 계열
	eTNCPhase_OnTakeInstant1	= 0x0010, // target(corpse)에게 순간적인 효과를 내는
	eTNCPhase_OnTakeInstant2	= 0x0020, // target(alive)에게 순간적인 효과를 내는
	eTNCPhase_OnAffect			= 0x0040, // target(alive)에게 지속적으로 효과를 나타내는
	eTNCPhase_AffectSelf		= 0x0080, // 자신에게 지속적으로 효과를 나타내는, target이 자신 이외일 경우이지만 자신한테도 영향이 미쳐야할 경우에만 사용한다. 보통 selt buff는 바로 위의 eTNCPhase_OnAffect를 사용한다.
	eTNCPhase_Taunt				= 0x0100, // 256
	eTNCPhase_StartAction		= 0x0200, // 자신에게 특수한 action을 발동시킨다. , 512
	eTNCPhase_OnChargInstance	= 0x0400, // 자신에게 특수한 action을 발동시킨다. , 1024
	eTNCPhase_CastOnly			= 0x0800,

	eTNCPhase_StatusChanged		= 0x0060, // eTNCPhase_OnTakeInstant2 + eTNCPhase_OnAffect
} ETNCombatPhase ;


typedef enum _ETNSpeechState
{
	eTNSpch_Idle = 0,
	eTNSpch_Attack,
	eTNSpch_Detect,
	eTNSpch_Trace,
	eTNSpch_Flee,
	eTNSpch_Killed,
	eTNSpch_Pop,
	eTNSpch_CantTrace,
	eTNSpch_Help,
	eTNSpch_Link,
	eTNSpch_Guard,
	eTNSpch_Lead, // 11
	eTNSpch_Dialog1,
	eTNSpch_Dialog2,
	eTNSpch_Dialog3,
	eTNSpch_Dialog4,	
} ETNSpeechState ;


typedef enum _EVisualEquipSlot
{
	eVisualEquipHelmet		= 0,
	eVisualEquipArmor		= 1,
	eVisualEquipPants		= 2,
	eVisualEquipShield		= 3,
	eVisualEquipOneWeapon	= 4,
	eVisualEquipBoots		= 5,
	eVisualEquipGloves		= 6,
} EVisualEquipSlot;



typedef enum _ETNAllowedTarget
{
	eTNAT_NA				= 0,
	eTNAT_Self				= 1,
	eTNAT_Friend			= 2,
	eTNAT_FriendExceptMe	= 3, // friendly except me
	eTNAT_Enemy				= 4, // near enemy
	eTNAT_Party				= 5,
	eTNAT_Guild				= 6,
	eTNAT_All				= 7,
	eTNAT_FriendCorpse		= 8,
	eTNAT_EnemyCorpse		= 9,
	eTNAT_Gate				= 10,
	eTNAT_SelfNEnemy		= 11,
	eTNAT_FriendNParty		= 12,
	eTNAT_EnemyFarFirst		= 13, // far enemy
} ETNAllowedTarget ;



typedef enum _ETNCellInfo
{
	eTNCell_PCNotAllowed				= 0x0210,

	eTNCell_SafetyZone					= 0x0001,
	//eTNCell_Collision					= 0x0002, // 이전에 이렇게 했음
	eTNCell_PKAllowed					= 0x0004,	
	eTNCell_Shrine						= 0x0008,
	eTNCell_Blocked						= 0x0010,
	eTNCell_AttackThrough				= 0x0020,
	eTNCell_MonsterCantMoveInThisCell	= 0x0040,
	//eTNCell_DuelField					= 0x0080,
	eTNCell_DuelZone					= 0x0100,
	eTNCell_SealedZone					= 0x0200,

	eTNCell_DontAttackMonster			= 0x2000,
	eTNCell_MountObject					= 0x4000,
	//eTNCell_MonsterNotAllowed			= 0x0011,
	//eTNCell_NPCNotAllowed				= 0x0000,
	eTNCell_HaveEvent					= 0x8000,

	eTNCell_NotAllowedKalaCore			= 0x0018,
} ETNCellInfo ;


typedef enum _ETNRouteType
{
	eTNRout_MoveNRoam = 0,
	eTNRout_MoveNPhaseOut = 1,
	eTNRout_Patrol = 2,
	eTNRout_GoNReturnNPhaseOut = 3,
	eTNRout_Rotation = 4,
	eTNRout_RandomPopNLiveThereOnly = 8,
	eTNRout_FixPosition = 10,
} ETNRouteType ;


typedef enum _ETNClan
{
	eTNClan_Friendly = 0, // 0은 우호이다.
	eTNClan_Hostile = 11, // 11 부터 hostile이다.

	eTNClan_NoTrimuritiy = 0,
	eTNClan_Brahma		= 1,
	eTNClan_Vishnu		= 2,
	eTNClan_Hunter		= 3,
	eTNClan_Siva		= 4, 
	eTNClan_BrahmaSoldier = 5,
	eTNClan_VishnuSoldier = 6,
	eTNClan_SivaSoldier = 7,
	eTNClan_Neutral		= 8,
	eTNClan_Aggressive	= 9, 
	eTNClan_GM			= 10,
	eTNClan_VictimNeut	= 11,
	eTNClan_VictimAggr	= 12,
	eTNClan_Berserker	= 13,
	eTNClan_Stronghold1	= 14,
	eTNClan_Stronghold2	= 15,
	eTNClan_Stronghold3	= 16,
	eTNClan_Stronghold4	= 17,
	eTNClan_NPC			= 18,
	eTNClan_CastleOwner	= 19,
	eTNClan_Siege1		= 20,
	eTNClan_Siege2		= 21,
	eTNClan_Siege3		= 22,
	eTNClan_Siege4		= 23,
	eTNClan_Reserved,
} ETNClan ;

// 정리가 잘못되어 있다.
typedef enum _ETNClass
{
	eTNMob_PC = 0,
	eTNMob_NPC,

	eTNCls_1st = 0,
	eTNCls_2nd,
	eTNCls_3rd,

	// NPC 직업 목록
	eTNCls_Warrior = 10, // 일반 몬스터(전투형)
	eTNCls_Summoned = 11, // 소환된 몬스터
	eTNCls_SummonOld = 12,
	eTNCls_Follower = 13, // 
	eTNCls_Trap = 14, // 함정
	eTNCls_Structure = 15,
	eTNCls_Event = 17,
	eTNCls_Quest = 18, // quest 관련 mobile
	eTNCls_NPC = 19,	 // 19, client에서 contact_npc 메시지를 전달한다.

	// 직업 세분화
	eTNCls2_Basic = 0,
	eTNCls2_Pet = 1,
	eTNCls2_Familiar = 2, // 단순히 공격만 하는 패밀리어
	eTNCls2_Totem = 3,
	eTNCls2_Retainer = 4,
	eTNCls2_Tracker = 5,
	eTNCls2_Mine = 6,
		
	//
	eTNCls2_Guard, // 근처에 소환되어서 소환자를 보호한다.
	//eTNCls2_Soldier, // 병사개념
} ETNClass ;

typedef enum _ETNAIOption
{
	eTNAIO_None						= 0x00000000,
	eTNAIO_GetCommand				= 0x00000001, // 주인으로부터 명령을 받는가?
	eTNAIO_NoTrace					= 0x00000002, // 추적을 하는가?
	eTNAIO_Robot					= 0x00000004,
	eTNAIO_Follow					= 0x00000010,
	eTNAIO_HaveMaster				= 0x00000020, // 주인이 있냐?
	eTNAIO_LifeTime					= 0x00000040, // 살아 있는 시간 제한이 있는가?
	eTNAIO_CombatOnly				= 0x00000080, // 전투만 하는가?

} ETNAIOption;


typedef enum _ETNReaction
{
	eTNRA_None						= 0x00000000,
	eTNRA_Attack					= 0x00000001,
	eTNRA_Trace						= 0x00000002, // 주인으로부터 명령을 받는가?		
	eTNRA_EndToCombat				= 0x00000004,
	eTNRA_ReturnToHome				= 0x00000008, // 추적을 하는가?

} ETNReaction;


typedef enum _ETNMonsterProperty
{
	eMonPrty_AI = 0,
	eMonPrty_NormalSight = 1,
	eMonPrty_CombatSight,
	eMonPrty_Movement,
	eMonPrty_WalkSpeed,
	eMonPrty_RunSpeed, // 5
	eMonPrty_Size,
	eMonPrty_DodgeSpeed,
	//eMonPrty_FireResist,
	//eMonPrty_ColdResist,
	//eMonPrty_LightningResist,
	//eMonPrty_PoisonResist, 
	eMonPrty_PopDelayMin = 10, // 10
	eMonPrty_PopDelayMax,
	eMonPrty_BlockedCell, // 이동 못하는 cell 정보
	eMonPrty_CantDetect, // 감지하지 못하는 affection정보
	eMonPrty_Resist,	
	eMonPrty_SpeechRate,
	eMonPrty_HPRecovery,
	eMonPrty_AggrCond,
	eMonPrty_TraceCond,
	eMonPrty_StepBackCond,
	eMonPrty_HelpCond,
	eMonPrty_HelpCondCount,
	eMonPrty_LinkCond,
	eMonPrty_LinkCondCount,
	eMonPrty_FleeCond,
	eMonPrty_FleeCondCount,
	eMonPrty_SklPtrn0,
	eMonPrty_SklPtrn1, 
	eMonPrty_SklPtrn2, // 20
	eMonPrty_SklPtrn3,
	eMonPrty_UseDefaultSkillOnly,
	eMonPrty_SelectTargetTime,
	eMonPrty_SelectTarget0,
	eMonPrty_SelectTarget1,
	eMonPrty_SelectTarget2,
	eMonPrty_SelectTarget3,
	eMonPrty_SelectTargetComplexly,
	eMonPrty_SpeechAI,	
	eMonPrty_ResistEffectConst,
	eMonPrty_ArmorType,
	eMonPrty_MaxRange,	
	eMonPrty_Class, 
	eMonPrty_Reserved0, // eMonPrty_Reserved1		
	eMonPrty_Reserved1,
	eMonPrty_Reserved2,
	eMonPrty_Reserved3,
	eMonPrty_Reserved4,
	eMonPrty_Reserved5,
	eMonPrty_Reserved6,
	eMonPrty_Reserved7,

} ETNMonsterProperty ;


typedef enum _ETNAI
{
	eTNAI_None = 0,
	eTNAI_Rest,
	eTNAI_Move,
	eTNAI_Start,
	eTNAI_Arrive,
	eTNAI_Detect,
	eTNAI_Help1,
	eTNAI_Link1,
	eTNAI_Guard1,
	eTNAI_BeKilled1,
	eTNAI_UnderAttack1, // 10
	eTNAI_Attack,
	eTNAI_HitEnemy, // critical hit로 적을 때렸을 때,
	eTNAI_Miss,
	eTNAI_BeHitted, // critical hit로 맞았을 때
	eTNAI_Dodge,
	eTNAI_Trace,
	eTNAI_GiveUpToTrace,
	eTNAI_KillEnemy,
	eTNAI_Help2,
	eTNAI_Link2, // 20
	eTNAI_Guard2,
	eTNAI_BeKilled2,
	eTNAI_UnderAttack2,	
	eTNAI_CantTrace,  // 걸치기 event
	eTNAI_StopToAttack, // 몹 몰이 방지
	eTNAI_Return,
	eTNAI_Flee,
	eTNAI_Lead,
	eTNAI_Pop,
	eTNAI_Dialog1,  // 30
	eTNAI_Dialog2,  
	eTNAI_Dialog3,
	eTNAI_Dialog4, // 33

	eTNAI_MaxAICount = 256,
	eTNAI_MaxEventSort = 33,
	eTNAI_MaxActionListCount = 3300,
	eTNAI_MaxActionCount = 1000,
	eTNSpch_MaxContentCount = 1000, 
	eTNSpch_MaxCommentCount = 1200, 
	//eTNSpch_Count = 200,
	//eTNSpch_StateCount = 16,
	eTNPath_Count = 5,
	
} ETNAI ;


typedef enum _ETNGroup
{
	eTNGrp_Help		= 10,
	eTNGrp_Link		= 20,

	eTNGrp_MaxHelperCount = 5, 
} ETNGroup ;


typedef enum _ETNAction
{	
	eTNAct_UseSkill						= 10,
	eTNAct_UseSkillSelf					= 11,	
	eTNAct_PopMonster					= 100,
	eTNAct_PopMonster2					= 101, // class1, clan, direction, x, y
	eTNAct_PopMonster3					= 102, // Monster ID	clan	pop type	n(개체수)	route ID	life time
	eTNAct_PopMonster4					= 103, // 부모의 모든 속성을 상속해서 pop // Monster ID	
	eTNAct_PopMonster5					= 104, // 이벤트를 수행해주는 npc를 pop 시킨다.
	eTNAct_PopMonster6					= 105, // 
	eTNAct_KillMonster					= 110,
	eTNAct_KillMonsterAll				= 120,
	eTNAct_KillMonsterWithClan			= 130,
	eTNAct_KillMonsterWithTribe			= 140,
	eTNAct_Speak						= 150,
	eTNAct_Help							= 160,
	eTNAct_Link							= 170,

	eTNAct_Flee							= 180,
	eTNAct_TriggerEvent					= 1000,
	eTNAct_AddEventOnScheduler			= 1010,
	eTNAct_RemoveEventOnScheduler		= 1011,
	eTNAct_AddInstantEventOnScheduler	= 1012,
	eTNAct_CheckRemoveItem				= 1020,
	eTNAct_CheckItemOnly				= 1030,
	eTNAct_CheckWeapon					= 1035,
	eTNAct_ReturnPrevPos				= 1040,
	eTNAct_Teleport						= 1050,
	eTNAct_TeleportParty				= 1055, //
	eTNAct_DropItem						= 1060,
	eTNAct_RangeUp						= 1070,
	eTNAct_SetClan						= 1080,
	eTNAct_SetDuration					= 1090,
	eTNAct_SetAvailableTime				= 1100,
	eTNAct_KnockBack					= 1110,
	eTNAct_CheckQuest					= 1120,
	eTNAct_ResetChakra					= 1130,
	eTNAct_ResetSkillBook				= 1140,
	eTNAct_ResetClass					= 1150,
	eTNAct_CheckMonster2				= 1160,
	eTNAct_ChangeImmunity				= 1170,
	eTNAct_ChangeBaseRwdCorrect			= 1180, 
	eTNAct_PlusExtraRwdCorrect			= 1185, 
	eTNAct_MinusExtraRwdCorrect			= 1186,
	eTNAct_GoldBomb						= 1200,
	eTNAct_KillAll						= 2000,
	eTNAct_KickOut						= 2010,
	eTNAct_KillPC						= 2020,	
	eTNAct_CheckKalaSystem				= 2030,
	eTNAct_PrintKalaCoreInfo			= 2040,
	eTNAct_MoveTheGateOfDungeon			= 2050,
	eTNAct_MoveTheSymbolAtByruCastle	= 2051, // 비류성 내성 상징물 이동
	eTNAct_CheckByruCastleMaster		= 2052, // 비류성 성주인지 확인
	eTNAct_OnKilledLeftGeneral			= 2060,
	eTNAct_OnKilledRightGeneral			= 2070,
	eTNAct_KillMonsterInSquare			= 2080,
	eTNAct_KillMonsterInSquare2			= 2081,
	eTNAct_Vanish						= 2085,
	eTNAct_ChangeField					= 2090,
	eTNAct_AffectAll					= 2100,
	eTNAct_DebufferAll					= 2101,
	eTNAct_AffectAEffectToClanMonsters	= 2200,
	eTNAct_ChangeClanByTribe			= 2210, // 항상 수행할 수 있다.
	eTNAct_ChangeClanByTribe2			= 2211, // 공성전이 아닐때만 수행된다.
	eTNAct_IdentifyStrongholdOwner		= 2220, // location: 0~3
	eTNAct_GambleBetOn					= 3010,
	eTNAct_GambleBetOff					= 3020,
	eTNAct_GambleSetOn					= 3030,
	eTNAct_GambleSetOff					= 3040,
	eTNAct_GambleResultOn				= 3050,
	eTNAct_GambleResultOff				= 3060,
	eTNAct_GamblePlayOn					= 3070,
	eTNAct_GamblePlayOff				= 3080,
	eTNAct_GambleBroadcast				= 3090,
	eTNAct_GambleResetMomey				= 3100,
	etnAct_MoveGambleHorse				= 3110,
	eTNAct_DrawCard						= 3200,
	eTNAct_DrawCard2					= 3205,
	eTNAct_CheckPartyLeader				= 3210,
	eTNAct_InstallEventField			= 4000,
	eTNAct_Mine							= 9000,
	eTNAct_PostMessageToZone			= 10000,
	eTNAct_PostMessageToWorld			= 10010,
	eTNAct_RecordName					= 10020,
	eTNAct_PostStrongholdOwner			= 10030,
	eTNAct_RecordPCNameInZone			= 10040,
	eTNAct_CheckStrongholdOwner			= 10100,
	eTNAct_KillKingAtChaturangka		= 20000,
	eTNAct_CloseKingRoomAtChaturangka	= 20010,	
	eTNAct_CountRealmEntry				= 20020,
	eTNAct_CountMonster					= 20100,
	eTNAct_CountMonsterByTribe			= 20101,
	eTNAct_TeleportAll					= 20110,
	eTNAct_ReturnToTrimuritiZone		= 20120, // 실제로는 범용적인 함수가 아니다.
	eTNAct_ReturnPCToSaveZone			= 20121,
	eTNAct_CountBrahmaMonster			= 20130,
	eTNAct_CountVishnuMonster			= 20140,
	eTNAct_CountSivaMonster				= 20150,
	eTNAct_KickOutOtherClanInMyStronghold = 20160,
	eTNAct_SwitchBattleForStronghold	= 20170,
	eTNAct_SetDuelFieldAtStronghold		= 20180,
	eTNAct_CloseDuelFieldAtStronghold	= 20190,
	eTNAct_RegisterPCtoArenaEntry		= 20200,
	eTNAct_PostThePrize					= 20210,
	eTNAct_StartSuvivalFight			= 20300,
	eTNAct_CheckWinner					= 20310,
	eTNAct_CheckElapsedTimeAboutStronghold = 20320,
	eTNAct_RefreshCharacterData			= 20330,
	eTNAct_KickOutLosser				= 21000,
	eTNAct_JudgeTheSiege				= 21010,
	eTNAct_PopSymbolForSiege			= 21020,
	eTNAct_RecoverClanToOriginal		= 21030,
	eTNAct_SwitchSiege					= 21040,
	eTNAct_PostTheResultOfTheSiege		= 21050,
	eTNAct_FixTheDateOfTheSiege			= 21060,
	eTNAct_SwitchExpireOfTheTermForSiege = 21070,
	eTNAct_PostTheScheduleForTheSiege	= 21080,
	eTNAct_ChangeClanForSiege			= 21090,
	eTNAct_InitBarunaKnightQuest		= 21100,
	eTNAct_QuestEvent					= 22000,
	eTNAct_RewardBramanPointInRect		= 23000,
	eTNAct_RewardBramanPointInRect2		= 23001, // param에 들어오는 인자, 즉 a_iUser, a_iNPC에 의해 동작하게 된다.
	eTNAct_RewardBufferInRect			= 23010,
	eTNAct_RewardBufferInRect2			= 23011, // param에 들어오는 인자, 즉 a_iUser, a_iNPC에 의해 동작하게 된다.
} ETNAction ;

typedef enum _ETNDebug
{
	eTNDbg_None					= 0x00000000,
	eTNDbg_Combat				= 0x00000001,
	eTNDbg_Pet					= 0x00000002,	
	eTNDbg_Immunity				= 0x00000004,
	eTNDbg_Affection			= 0x00000008,

} ETNDebug ;

typedef enum _ETNMonsterSwitch
{
	// Reserved4
	// audit purpose
	eTNAudit_Boss				= 0x00000001,
	eTNAudit_LifeCycle			= 0x00000002,

	// Reserved6
	// react by path blocked
	eTNReact_Pass				= 0x00000001,
	eTNReact_Ignore				= 0x00000002,

	// Reserved7
	eTNMonster_Boss				= 0x00000001,

} ETNMonsterSwitch ;

typedef enum _ETNCOLOR
{
	eTNClr_White	= 15,
	eTNClr_Red		= 11,
	eTNClr_BG		= 14,

} ETNCOLOR ;
/*
typedef enum _ETReactionByPathBlocked
{
	eTNReact_Pass			= 0x00000001,
	eTNReact_Ignore			= 0x00000002,
} ETReactionByPathBlocked ;
*/


typedef enum _ETNStatus
{
	eTNSts_None				= 0x00000000,
	eTNSts_Help				= 0x00000001,
	eTNSts_Link				= 0x00000002,
	eTNSts_Guard			= 0x00000004,
/*
	eTNImm_Cold				= 0x00000004,
	eTNImm_Lightning		= 0x00000008,
	eTNImm_Poison			= 0x00000010, 
	//eTNImm_Invisible		= 0x00000020,
	//eTNImm_WizardEyes		= 0x00000040, 
	eTNImm_Hold				= 0x00000080,
	eTNImm_Stun				= 0x00000100, 
	eTNImm_Sleep			= 0x00000200, 
*/
} ETNStatus ;



typedef enum _ETNCondition
{ 
	eTNCond_MaxSort = 3,

	eTNCond_Help = 0,
	eTNCond_Link,
	eTNCond_Flee,
} ETNCondition ;


typedef enum _ETNUnderAttack
{
	eTNUndAtt_Normal = 0,
	eTNUndAtt_Help = 1,
	eTNUndAtt_Link = 2,
} ETNUnderAttack ;


typedef enum _ETNSelectTarget
{
	eTNSelectTarget_NearestDistance = 0,
	eTNSelectTarget_HighDamage = 1,
	eTNSelectTarget_LowHP = 2,
	eTNSelectTarget_LowDefense = 3,
	eTNSelectTarget_LowLevel = 4,
	eTNSelectTarget_Hostile = 5,
	eTNSelectTarget_Naga = 6,
	eTNSelectTarget_Asura = 7,
	eTNSelectTarget_Yaksha = 8,
	eTNSelectTarget_Deva = 9,
} ETNSelectTarget ;



typedef enum _ETNAttackType
{
	eTNAttackType_Dagger = 1,
	eTNAttackType_Sword = 2,
	eTNAttackType_TwoHandSword = 3,
	eTNAttackType_Animal,
	eTNAttackType_Demon,
	eTNAttackType_Golem,
	eTNAttackType_Undead,
	eTNAttackType_Plant,
	eTNAttackType_Insect,
	eTNAttackType_Humanoid1, // 10
	eTNAttackType_Humanoid2,
	eTNAttackType_Humanoid3,
	eTNAttackType_Humanoid4,
	eTNAttackType_Axe, // 14
	eTNAttackType_TwoHandAxe,
	eTNAttackType_Spear,
	eTNAttackType_Bow,
	eTNAttackType_Claw,
	eTNAttackType_Blunt, // 19
	eTNAttackType_Magic, // 20
} ETNAttackType ;


typedef enum _ETNArmorType
{
	eTNArmorType_Cloth = 0,
	eTNArmorType_Light = 1,
	eTNArmorType_Medium = 2,
	eTNArmorType_Heavy = 3,
	eTNArmorType_Animal = 4,
	eTNArmorType_Demon = 5,
	eTNArmorType_Golem = 6,
	eTNArmorType_Undead = 7,
	eTNArmorType_Plant = 8,
	eTNArmorType_Insect = 9,
	eTNArmorType_Humanoid1 = 10,
	eTNArmorType_Humanoid2 = 11,
	eTNArmorType_Humanoid3 = 12,
	eTNArmorType_Humanoid4 = 13,

} ETNArmorType ;


typedef enum _ETNButtonStatus
{
	eTNBtn_PK		= 0x00000001,
	eTNBtn_Run		= 0x00000002,
	eTNBtn_Assist	= 0x00000004,
} ETNButtonStatus;

typedef enum _ETNSpeechLocation
{
	eTNSpchLoc_ChatWindow = 0,
	eTNSpchLoc_Head = 1,
	eTNSpchLoc_All = 2,
} ETNSpeechLocation ;


typedef enum _ETNSwitch  // 1일 경우는 off된 것이다. 0일 경우는 on
{
	eTNSwitch_Empty					= 0x00000000,
	eTNSwitch_DecPrana				= 0x00000001,
	//eTNSwitch_ResetSkill			= 0x00000002,
	eTNSwitch_RecvKalaSystem		= 0x00000004,
	eTNSwitch_PKDisable				= 0x00000008,
	eTNSwitch_MonsterSpeechDisable	= 0x00000010,
	eTNSwitch_EventLog				= 0x00000020,
	eTNSwitch_ContactNPC			= 0x00000040,
} ETNSwitch ;


typedef enum _ETNProduction  // 연출 효과
{
	eTNPrdt_PopNormal = 0, // 그냥 지면위에서 펑하고 나타남, 출현시 주위에 둥그런 FX가 터짐
	eTNPrdt_PopRaise = 1, // 지면 아래에서 서서히 지면 위로 올라오는 연출
	eTNPrdt_PopDescend = 2, // 높은 곳에서 지면으로 서서히 내려온다.(가속도:0)
	eTNPrdt_PopFallDown = 3, // 높은 곳에서 지면으로 가속되면서 떨어짐.(하늘에서 물체가 떨어지는 느낌, 차투랑가 개폐문에 쓰일 예정)

	eTNPrdt_RemoveNormal = 0,
	eTNPrdt_RemoveBoom = 1,
	eTNPrdt_RemoveFadeOut = 2,
} ETNProduction ;


typedef enum _ETNCaste
{
	eTNCaste_Sudra3 = 0,
	eTNCaste_Sudra2 = 1,
	eTNCaste_Sudra1 = 2,
	eTNCaste_Baisha3 = 3,
	eTNCaste_Baisha2 = 4,
	eTNCaste_Baisha1 = 5,
	eTNCaste_Cushatri3 = 6,
	eTNCaste_Cushatri2 = 7,
	eTNCaste_Cushatri1 = 8,
	eTNCaste_Braman3 = 9,
	eTNCaste_Braman2 = 10,
	eTNCaste_Braman1 = 11,
	eTNCaste_Avatara3 = 12, 
	eTNCaste_Avatara2 = 13,
	eTNCaste_Avatara1 = 14,
	eTNCaste_MahaRaja3= 15,
	eTNCaste_MahaRaja2 = 16,
	eTNCaste_MahaRaja1 = 17,
} ETNCaste ;

typedef enum _ETNCasteRank
{
	eTNCasteRank_Cushatri3 = 93,
	eTNCasteRank_Cushatri2 = 64,
	eTNCasteRank_Cushatri1 = 45,
	eTNCasteRank_Braman3 = 33,
	eTNCasteRank_Braman2 = 26,
	eTNCasteRank_Braman1 = 19,
	eTNCasteRank_Avatara3 = 12, 
	eTNCasteRank_Avatara2 = 9,
	eTNCasteRank_Avatara1 = 6,
	eTNCasteRank_MahaRaja3= 3,
	eTNCasteRank_MahaRaja2 = 2,
	eTNCasteRank_MahaRaja1 = 1,
} ETNCasteRank;

typedef enum _ETNCasteRankOld
{
	eTNCasteRankOld_Cushatri3 = 248,
	eTNCasteRankOld_Cushatri2 = 168,
	eTNCasteRankOld_Cushatri1 = 118,
	eTNCasteRankOld_Braman3 = 88,
	eTNCasteRankOld_Braman2 = 63,
	eTNCasteRankOld_Braman1 = 43,
	eTNCasteRankOld_Avatara3 = 28, 
	eTNCasteRankOld_Avatara2 = 18,
	eTNCasteRankOld_Avatara1 = 11,
	eTNCasteRankOld_MahaRaja3= 6,
	eTNCasteRankOld_MahaRaja2 = 3,
	eTNCasteRankOld_MahaRaja1 = 1,
} ETNCasteRankOld;

typedef enum _EGuildLevel
{
	eGuildMaster		= 10,
	eGuildSubMaster		= 9,
	eGuildThird			= 8,
	eGuildForth			= 7,
	eGuildMember		= 0,
} EGuildLevel;

/*********************************************/
//	2004.08.26(능력치, 스킬 초기화 관련패킷)
typedef enum _ENPCCommandTYPE
{
	eInitSkill			= 1,
	eInitChar			= 2,
	eInit2ndClass		= 3,
	eInitSkillChar		= 4,
	eEvent				= 5,
	eInitQuest			= 6
} ENPCCommandTYPE;

typedef enum _ECommand
{
	eSearch				= 1,
	eRun				= 2,
} ECommand;

typedef enum _ERequest
{
	eRequest			= 1,
	eResponse			= 2,
} ERequest;
/*********************************************/

//#define __TN_CHANGE_5LVL__
//#define __TN_PLAYMOVIE__
//#define __TN_LOCAL_SERVER_SWITCH__
//#define __TN_EMERGENCY_LOG__
#define __DEBUG_LOG__
#define __TN_TOP_LOG__
#define __DYNAMIC_LOG__
//#define __BEFORE_KRUMA_REMODELING__ // 크루마 리모델링 이전 설정(2006.09.05)
//#define __BEFORE_SET_ITEM_EXPANDED__ //set item에서 effect3를 추가 확장하기 전이면 ON, 그렇지 않으면 OFF
//#define __BEFORE_MAGIC_LAMP_EXPANDED__ // 요술램프가 3종이라면 ON, 5종으로 확장됐다면, OFF
//#define __TN_1ST_LOG__
//#define __TN_2ND_LOG__
//#define __TN_3RD_LOG__
//#define __TN_4TH_LOG__
//#define __TN_5TH_LOG__


#define SKIPCHECKTICK  235543242


#define TRIMURITI_BRAHMA	1
#define TRIMURITI_VISHNU	2
#define TRIMURITI_SIVA		4

#define	TRIBE_NONE			255		// 종족 제한 없음
#define TRIBE_NAGA			1		// 나가
#define TRIBE_KINNARA		2		// 아수라
#define TRIBE_ASURA			4		// 야크사
#define TRIBE_RAKSHASA		8		// 데바
#define TRIBE_YAKSA			16		// 킨나라
#define TRIBE_GANDHARVA		32		// 라크샤사
#define TRIBE_DEVA			64		// 간다르바
#define TRIBE_GARUDA		128		// 가루다

#pragma	pack(push, 1)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 맵에 관련된 상수
namespace _MAP_MANAGER
{
	const int NAME_LEN = 26;						// 맵 이름 길이
	const int CELLS_PER_GRID = 4;					// 그리드 당 셀 개수
	const int CELLS_PER_CS = 4;						// CriticalSection당 셀 개수
	const int LIST_COUNT_ON_CELL = 3;				// 한 셀(그리드)당 오브젝트 리스트 개수
	const int VIM_CHANGE_RANGE = 1;					// VIM 변경 범위
	const float VIM_CHANGE_VALUE_SIDE = 0.5f;		// 직선 방향 VIM 변경 값
	const float VIM_CHANGE_VALUE_CORNER = 0.25f;	// 대각선 방향 VIM 변경 값
	const int DEFAULT_FIND_ARRANGE_DISTANCE = 5;	// 기본 배치 가능위치 검색 범위
};

namespace _CELL_STATE
{
	const unsigned short CELL_SAFE_ZONE				= 0x0001;
	const unsigned short CELL_CONFLICT_ENABLE		= 0x0002;
	const unsigned short CELL_PK_ENABLE				= 0x0004;
	const unsigned short CELL_INDOOR				= 0x0008;
	const unsigned short CELL_MOVE_DISABLE			= 0x0010;
	const unsigned short CELL_SIT_ENABLE			= 0x0020;
	const unsigned short MAP_OBJECT_SIT_ENABLE		= 0x2000;
	const unsigned short MAP_OBJECT_MOUNT_ENABLE	= 0x4000;
}

#define		HEADER_VERSION_SIZE		5
#define		HEADER_UPDATE_SIZE		20

typedef struct _S_FILE_HEADER_INFO	{
	char	szVersion	[HEADER_VERSION_SIZE];
	char	szUpdateDate[HEADER_UPDATE_SIZE];
	int		nDataCount;
} S_FILE_HEADER_INFO;

struct _S_GOBJ_GENERATIONAREA_PARAMS
{
	DWORD	dwIndex;		// 생성 영역 Index(사용안함).
	SHORT	snStartX;		// 생성 영역 시작 X 좌표
	SHORT	snStartZ;		// 생성 영역 시작 Z 좌표
	SHORT	snEndX;			// 생성 영역 끝 X좌표 
 	SHORT	snEndZ;			// 생성 영역 끝 Z좌표
};

struct _S_TRIMURITY_AREA
{
	BYTE	byTrimuriti[4];
	_S_GOBJ_GENERATIONAREA_PARAMS pArea[4][MAX_TRIMURITY_AREA];
};

typedef struct _S_GOBJ_MONSTER_RANGE
{
	int		nStartX;	// X 좌표(가로)
	int		nStartZ;	// Z 좌표(세로)
	int		nEndX;		// X 좌표(가로)
	int		nEndZ;		// Z 좌표(세로)
	int		nHeight;
}S_MonsterRange;

struct _TNAREA_PROPERTY
{
	enum { eBhvCond_Aggr = 0, eBhvCond_Flee = 1 } ;

	unsigned int uiMonsterID ; // 0이 아닌 값이 들어오면 loading을 시작한다.
	int iDeployCount;  // pop 수

	int iBehavior ;
	int irgBhvCond[3] ;
	int irgGroup[7] ;
	unsigned int uiMaxHP ;
	unsigned int uiHPRecoveryRate ;
	unsigned int uiPopDelay ;
	unsigned int uiMovementRate ;
	unsigned int uiSight ;

	unsigned int uirgCombatFactor[5] ;
	int irgAC[2] ;
	int irgResistElement[5] ;
	int irgSpeed[5] ;
	unsigned int uiRewardPrana ;
	unsigned int uiEvent ;

	int irgReserved[2] ;
};

typedef struct _TNAREA_PROPERTY TNAREA_PROPERTY ;



struct TNDEPLOY_DATA
{
	int nArrangeIndex ;
	int iZoneNo ; // not in use

	int iVision ;
	int iLink ;
	int iGuard ;
	unsigned int uiBossID ;

	S_MonsterRange	kCreateRange;
	S_MonsterRange	kActioiRange;

	TNAREA_PROPERTY krgMonsters[6] ;
	int irgReserved[2] ;
};

#pragma pack (pop)




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
#define FLAG_GAME2CLIENT                0x0100          // 서버가 날리는 메시지        256   //
#define FLAG_CLIENT2GAME                0x0200          // 클라이언트가 날리는 메시지  512   //

///////////////////////////////////////////////////////////////////////////////////////////////
//        Base
////////////////////////////////////////////////////////////////////////////////////////// ^
#define  _MSG_MessagePanel                 ( 1 | FLAG_GAME2CLIENT)
struct    MSG_MessagePanel
{        _MSG;
		  int	   nID;
          char     String[MESSAGE_LENGTH];  
};
////////////////////////////////////////////////////////////////////////////////////
//        Login
////////////////////////////////////////////////////////////////////////////////////
#define  _MSG_NewAccount                    ( 10 | FLAG_CLIENT2GAME) 
struct    MSG_NewAccount
{        _MSG;
          //STRUCT_ACCOUNT ACCOUNT;
	      int      Version;
};
#define  _MSG_CNFNewAccount                 ( 12 | FLAG_GAME2CLIENT)
#define  _MSG_AccountLogin                  ( 13 | FLAG_CLIENT2GAME)

#define		SSP_REQ_MOVE_ZONE_SERVER	0x0001
#define		SSP_RESP_MOVE_ZONE_SERVER	SSP_REQ_MOVE_ZONE_SERVER+0x8000
struct		S_SSP_REQ_MOVE_ZONE_SERVER
{	
	_MSG;
	int			nID;
	char		AccountName[ACCOUNTNAME_LENGTH];	//	계정 ID
	char		AccountPass[ACCOUNTPASS_LENGTH];	//	계정 비번
	char		szCharName[SZNAME_LENGTH];					// Character Name
};
struct		S_SSP_RESP_MOVE_ZONE_SERVER
{
	_MSG;
	int				nID;
	int				nResult;
	char			AccountName[ACCOUNTNAME_LENGTH];
	int				ssn1;
	int				ssn2;
};

#define		_Msg_UserInfo			0x0008
struct		Msg_UserInfo
{
	_MSG;
	int			nType;								//	1:login, 2:logout
	int			nID;
	char		AccountName[ACCOUNTNAME_LENGTH];	//	계정 ID
};

#define		_Msg_CharInit			0x0009
struct		Msg_CharInit
{
	_MSG;
	int			nID;
	short		snTribe;
	byte		byTrimuriti;
	byte		byDummy;
	char		AccountName[ACCOUNTNAME_LENGTH];
	char		szName[SZNAME_LENGTH];
};


#define		SSP_REQ_CHAR_CREATE		0x0002
#define		SSP_RESP_CHAR_CREATE	SSP_REQ_CHAR_CREATE+0x8000
struct S_SSP_REQ_CHAR_CREATE
{
	_MSG;
	int		nID;
	char   	szCharName[SZNAME_LENGTH];  

	BYTE   	byTrimuriti;                                                                                       
	BYTE   	byFaceType;  
	BYTE   	byChakraMuscle;
	BYTE   	byChakraNerve;

	BYTE   	byChakraHeart;
	BYTE	byChakraSoul; 
	BYTE	byHeadType;
	BYTE	byDummy;

	short   snTribe; 
	short   snDummy;
};
struct S_SSP_RESP_CHAR_CREATE
{
	_MSG;
	int		nID;
	BYTE	byResult;
	BYTE	bySlot;
	short	snDummy;
	char	szCharName[SZNAME_LENGTH];
};
#define		SSP_REQ_CHAR_REMOVE		0x0003
#define		SSP_RESP_CHAR_REMOVE	SSP_REQ_CHAR_REMOVE+0x8000
struct	S_SSP_REQ_CHAR_REMOVE
{
	_MSG;
	int		nID;
	char    szCharName[SZNAME_LENGTH];
	//char    szJumin[16];  
};
struct	S_SSP_RESP_CHAR_REMOVE
{
	_MSG;
	int		nID;
	BYTE	byResult;
	BYTE	byDummy;
	short	snDummy;
};

#define		SSP_REQ_CHAR_LIST			0x0004
#define		SSP_RESP_CHAR_LIST			0x8004
struct S_SSP_REQ_CHAR_LIST
{
	_MSG;
	int		nID;
};
struct S_SSP_RESP_CHAR_LIST
{
	_MSG;
	int					nID;
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];  
};

#define SSP_REQ_CHAR_SELECT				0x0005
#define SSP_RESP_CHAR_SELECT			0x8005
struct S_SSP_REQ_CHAR_SELECT
{
	_MSG;
	int					nID;
	char	szCharName[SZNAME_LENGTH];
	BYTE	byConnectType;
	BYTE	byDummy;
	short	snDummy;
};
struct S_SSP_RESP_CHAR_SELECT
{
	_MSG;
	int		nID;
	BYTE	byResult;
	BYTE	byWorldNo;				
	BYTE	byZoneNo;
	BYTE	byConnectType;
};

#define SSP_REQ_CHAR_INIT				0x0006
#define SSP_RESP_CHAR_INIT				0x8006
struct	S_SSP_REQ_CHAR_INIT
{
	_MSG;
	int			nID;
	char		szCharName[SZNAME_LENGTH];
	char		szTargetName[SZNAME_LENGTH];
	BYTE        byConnType;	
	BYTE		byConnPos;
	BYTE		bySlot;
	BYTE		byDummy;

	WORD		wPortalID;	
	short		snDummy;
};
struct S_SSP_RESP_CHAR_INIT
{
	_MSG;
	char		szTargetName[SZNAME_LENGTH];
	BYTE		byResult;
	BYTE        byConnType;	
	BYTE		byConnPos;
	BYTE		bySlot;

	WORD		wPortalID;
	short		snDummy;
	int			nID;
	int			nSlot;
	int			nNpcMoney;
	STRUCT_MOB	sChar;
	STRUCT_ITEM sNpcInven[MAX_CARGO];
	DWORD		dwTimeStamp[10];
};

#define SSP_REQ_SAVE_QUIT			0x0007
#define SSP_RESP_SAVE_QUIT			0x8007
struct  S_SSP_REQ_SAVE_QUIT
{   _MSG;
	int				nID;
	int				Slot;            
	STRUCT_MOB		MOB;
	STRUCT_ITEM		Cargo[MAX_CARGO];
	int				Coin;
	char			ShortSkill[8];
	char			AccountName[ACCOUNTNAME_LENGTH];
	DWORD			dwTimeStamp[MAX_TIMEITEM];
};


#define SSP_REQ_CHARACTER_SEARCH	0x0014
#define SSP_RESP_CHARACTER_SEARCH	0x0015
typedef struct _S_SSP_REQ_CHARACTER_SEARCH
{	_MSG;
	int													nID;
	char												szCharName[SZNAME_LENGTH];		// 검색할 캐릭터 이름
} S_SSP_REQ_CHARACTER_SEARCH, *PS_SSP_REQ_CHARACTER_SEARCH;
// GSCP_INIT_CHAR : 0xA547
typedef struct _S_SSP_RESP_CHARACTER_SEARCH
{	_MSG;
	int													nID;
	BYTE												byResult;						// 검색 결과( 0:성공, 1:실패)
	BYTE												byZone;							// 캐릭터 위치한 존
	SHORT												snDummy;
	char												szAccountID[ACCOUNTNAME_LENGTH];// 검색한 캐릭터 계정.
	char												szCharName[SZNAME_LENGTH];		// 검색한 캐릭터 이름.
} S_SSP_RESP_CHARACTER_SEARCH, * PS_SSP_RESP_CHARACTER_SEARCH;


#define SSP_REQ_PERFORMANCE_INFO	0x7001
#define SSP_RESP_PERFORMANCE_INFO	0xF001
#define SSP_REQ_SHUTDOWN			0x7002
#define SSP_REQ_CLOSE_TERMINAL		0x7003

typedef struct _S_SSP_RESP_PERFORMANCE_INFO
{	_MSG
	double dbCPURate;
	double dbDiskRead;
	double dbDiskWrite;
	DWORD  dwMemoryTotal;
	DWORD  dwMemoryAvailable;
	double dbTCPSent;
	double dbTCPReceive;
} S_SSP_RESP_PERFORMANCE_INFO, *PS_SSP_RESP_PERFORMANCE_INFO;

#define SSP_REQ_IMPORT_LOGFILE		0x7003
#define SSP_RESP_IMPORT_LOGFILE		0xF003

typedef struct _S_SSP_RESP_IMPORT_LOGFILE
{	_MSG;
	BYTE	byResult;
	BYTE	byWorld;
	BYTE	byZone;					 
	BYTE	byDummy;
	int		nFileCount;
} S_SSP_RESP_IMPORT_LOGFILE, *PS_SSP_RESP_IMPORT_LOGFILE;

#define  _MSG_CNFAccountLogin               ( 14 | FLAG_GAME2CLIENT)
struct    MSG_CNFAccountLogin 
{        _MSG;
          STRUCT_SELCHAR SelChar;
		  char           AccountName[ACCOUNTNAME_LENGTH];
};
#define  _MSG_NewCharacter                  ( 15 | FLAG_CLIENT2GAME) 
struct    MSG_NewCharacter 
{        _MSG;
		  int   nID;
          int	Slot; 
		  BYTE	byTrimuriti;
		  BYTE	byFace;
		  BYTE	byTribe;
		  BYTE	byDummy;
		  char  szName[SZNAME_LENGTH];
};
#define  _MSG_CNFNewCharacter               ( 16 | FLAG_GAME2CLIENT)
struct    MSG_CNFNewCharacter
{        _MSG;
		  int nID;
		  STRUCT_SELCHAR SelChar;
};
#define  _MSG_DeleteCharacter               ( 17 | FLAG_CLIENT2GAME) 
struct    MSG_DeleteCharacter
{        _MSG;
		  int			 nID;
          int            Slot; 
	      char szName[SZNAME_LENGTH];
};
#define  _MSG_CNFDeleteCharacter            ( 18 | FLAG_GAME2CLIENT)
struct    MSG_CNFDeleteCharacter
{        _MSG;
		  int nID;
		  STRUCT_SELCHAR SelChar;
};
#define  _MSG_CharacterLogin                ( 19 | FLAG_CLIENT2GAME)
struct    MSG_CharacterLogin
{        _MSG;
		  int	   nID;
          int      Slot;
	      int      Force;
};
#define  _MSG_CNFCharacterLogin             ( 20 | FLAG_GAME2CLIENT)
struct    MSG_CNFCharacterLogin
{        _MSG;
		  int nID;
          short PosX,PosY;
		  STRUCT_MOB		MOB;
		  unsigned short	Slot;
		  unsigned short	ClientID;
		  unsigned short	Weather;
		  short				snDummy;
		  char				ShortSkill[8];
};
#define  _MSG_CharacterLogout               ( 21 | FLAG_CLIENT2GAME)
#define  _MSG_CNFCharacterLogout            ( 22 | FLAG_GAME2CLIENT)
#define  _MSG_NewAccountFail                ( 23 | FLAG_GAME2CLIENT)
#define  _MSG_AccountLoginFail              ( 24 | FLAG_GAME2CLIENT)
#define  _MSG_CharacterLoginFail            ( 25 | FLAG_GAME2CLIENT)
#define  _MSG_NewCharacterFail              ( 26 | FLAG_GAME2CLIENT)
#define  _MSG_DeleteCharacterFail           ( 27 | FLAG_GAME2CLIENT)
#define  _MSG_AlreadyPlaying                ( 28 | FLAG_GAME2CLIENT)
#define  _MSG_StillPlaying                  ( 29 | FLAG_GAME2CLIENT)    

////////////////////////////////////////////////////////////////////////////////////
//        Chat/Stats
////////////////////////////////////////////////////////////////////////////////////
#define  _MSG_MessageChat                   ( 51 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_MessageChat
{        _MSG;
		  char     String[MESSAGE_LENGTH];  
};
#define  _MSG_MessageWhisper                ( 52 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_MessageWhisper
{        _MSG;
          char		szName[SZNAME_LENGTH];
		  char		String[MESSAGE_LENGTH]; 
		  short		Color;
		  short		snDummy;
};

//#define  _MSG_MessageImple                  ( 53 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
//struct    MSG_MessageImple
//{        _MSG;
//	 	  char     String[MESSAGE_LENGTH];  
//};
#define  _MSG_UpdateScore   			    ( 54 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_UpdateScore
{        _MSG;
          STRUCT_SCORE   Score;
     	  unsigned char  Critical;   unsigned char SaveMana;
		  unsigned short Affect[MAX_AFFECT];
		  unsigned short Guild;
		  unsigned short GuildLevel;
		  char           Resist[4];
		  unsigned short ReqHp;
		  unsigned short ReqMp;

};
#define  _MSG_UpdateEtc      			    ( 55 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_UpdateEtc 
{        _MSG;
          int			Exp;
		  unsigned int	LearnedSkill;
          short			ScoreBonus;
   	      short			SpecialBonus;
	      short			SkillBonus;
		  short			snDummy;
          int			Coin;
};
#define  _MSG_CNFMobKill   			        ( 56 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_CNFMobKill
{        _MSG;
          unsigned short KilledMob;
		  unsigned short Killer;
		  unsigned int   Exp;//각각 자신의 현재 경험치를 보내준다-받은사람의 경험치
};
#define  _MSG_UpdateCargoCoin   	        ( 57 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
/*
#define  _MSG_CNFMobKillParty		        ( 58 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_CNFMobKillParty
{        _MSG;
          unsigned short KilledMob;
		  unsigned short Killer;
		  unsigned int   Exp;
		  unsigned s//[MAX_PARTY+1];
};
*/
////////////////////////////////////////////////////////////////////////////////////
//        Mob
////////////////////////////////////////////////////////////////////////////////////
#define  _MSG_CreateMobTrade            (99 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_CreateMobTrade
{       _MSG;
		char           szName[SZNAME_LENGTH];
        short          PosX,PosY;

        unsigned short MobID;    
		unsigned short Equip[MAX_EQUIP];     //   | 0000 | 0000 | 0000 | 0000   4비트 제련 12비트 아이템
        unsigned short Affect[MAX_AFFECT];               //     SANC   ITEM_INDEX(0-4095)
		unsigned short Guild;
		unsigned short          CreateType;
		STRUCT_SCORE   Score;
		char           Desc[MAX_DESC];
};

#define  _MSG_CreateMob  		            (100 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_CreateMob
{        _MSG;
		  char           szName[SZNAME_LENGTH];
          short          PosX,PosY;
          unsigned short MobID;
          unsigned short Equip[MAX_EQUIP];     //   | 0000 | 0000 | 0000 | 0000
          unsigned short Affect[MAX_AFFECT];               //     SANC   ITEM_INDEX(0-4095)
		  unsigned short Guild;
		  unsigned short CreateType;
		  STRUCT_SCORE   Score;
};
#define	 _MSG_RemoveMob            	        (101 | FLAG_GAME2CLIENT )
struct    MSG_RemoveMob
{        _MSG;
	      int RemoveType;   // 0:이동에 의한 클리핑 리무브   1:사망 삭제  2:로그아웃 삭제  3:이동후 삭제맙이 이동을 완료.
};
#define	 _MSG_Action		                (102 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_Action
{    	 _MSG;
		  int		dwKeyID; 
          short		PosX,PosY;
	      int		Speed;
		  short		Effect;		// 0:앉기  1:서기  2:걷기  3:뛰기  4:날기  5:텔레포트,	6:밀리기(knock-back), 7:미끄러지기(이동애니없음)  8:도발, 9:인사, 10:돌격 
		  short		Direction;	//
	      unsigned short TargetX,TargetY;
};
#define  _MSG_Stop                          (103 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
#define  _MSG_Illusion                      (104 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)


#define  _MSG_REQMobByID   		            (105| FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_REQMobByID
{        _MSG;
          short MobID;
		  short	snDummy;
};
#define  _MSG_Motion    		            (106 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_Motion
{        _MSG;
	      short int Motion;
		  short int Parm;
	 	  float		Direction;
};
#define  _MSG_UpdateEquip                   (107 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_UpdateEquip
{        _MSG;
	      unsigned short  sEquip[MAX_EQUIP];
		  short				snDummy;
};

struct	STRUCT_DAM 
{		unsigned short		TargetID;
		short				Damage;

};

#define   MAX_TARGET 13
#define  _MSG_Attack                        (108 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_Attack    
{
	    _MSG;
		//
		unsigned short		AttackerID;
		unsigned short		Progress;
		unsigned short		PosX,		PosY;
		unsigned short		TargetX,	TargetY;
		//
		short 				SkillIndex;		// 0-98-106  (-1이면 물리적 공격)
        short				CurrentMp;
		// 이하 byte 2개로 해결되는지 검토
		unsigned char		Motion;
		unsigned char		SkillParm;		// 스킬 효과 증폭률 또는 물리공격 이펙트. 0 이 디폴트.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0비트 더블 1비트 크리티칼

		unsigned int		CurrentExp;
		short				ReqMp;
		short				Rsv;
		//
		STRUCT_DAM			Dam[MAX_TARGET];


};
//#define  _MSG_CreateItem                    (110 | FLAG_CLIENT2GAME)
//struct    MSG_CreateItem
//{        _MSG;                       
//          unsigned short GridX,GridY;
//          unsigned short ItemID;      
//  	      STRUCT_ITEM    Item;      
//          unsigned char  Rotate;
//          unsigned char  State;
//		  unsigned char  Height;
//		  unsigned char  Create;
//};
//#define  _MSG_RemoveItem                    (111 | FLAG_GAME2CLIENT )
//struct    MSG_RemoveItem 
//{        _MSG;                       
//          unsigned short ItemID;      
//};
//#define  _MSG_GetItem	      	   		    (112 | FLAG_CLIENT2GAME)
//struct    MSG_GetItem
//{        _MSG;
//          int      DestType;
//          int      DestPos;
//	      unsigned short	ItemID;
//		  unsigned short GridX,GridY;
//};
//#define  _MSG_CNFGetItem	      			(113 | FLAG_GAME2CLIENT)
//struct    MSG_CNFGetItem
//{        _MSG;
//          int      DestType;
//	      int	   DestPos;
//	      STRUCT_ITEM		Item;
//};
//#define  _MSG_DropItem 	      	   		    (114 | FLAG_CLIENT2GAME)
//struct    MSG_DropItem
//{        _MSG;
//          int      SourType;
//		  int      SourPos;        
//		  int      Rotate;
//		  unsigned short GridX,GridY;
//	      unsigned short ItemID;
//          
//};
#define  _MSG_UseItem                       (115 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME )
struct    MSG_UseItem
{        _MSG;
          int      SourType;
		  int      SourPos;
          int      DestType;
		  int      DestPos;

		  unsigned short GridX,GridY;
	      unsigned short ItemID;
};
#define   STATE_NOTHING 0
#define   STATE_OPEN    1
#define   STATE_CLOSED  2
#define   STATE_LOCKED  3
#define  _MSG_UpdateItem 	      	        (116 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME  )
struct    MSG_UpdateItem
{        _MSG;   // ID는 client
          int ItemID;
          short State;                        // [원하는바뀐상태] 0:이도저도아닌거 1:열린문  2:닫힌문   3:잠긴문     
		                                    // lock과 unlock은 key가 있는 경우만.
		                                    // 보물상자 처리는 미정..
		  short Height;
};

#define  _MSG_CNFDropItem 	       		    (117 | FLAG_GAME2CLIENT)
struct    MSG_CNFDropItem
{        _MSG;
          int      SourType;
	  	  int      SourPos;    
          int      Rotate;
          unsigned short GridX,GridY;
};
#define  _MSG_SwapItem                      (118 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_SwapItem 
{		_MSG;
		unsigned char	SourType;
		unsigned char	SourPos;
		unsigned char	DestType;
		unsigned char	DestPos;
		unsigned short	TargetID;
};
#define _MSG_ApplyBonus                     (119 | FLAG_CLIENT2GAME)
struct   MSG_ApplyBonus
{
  	    _MSG;
	     short      BonusType;    // 보너스 대분류 0:ScoreBonus 1:Special 2:Skill
	     short      Detail;       // 스코어 0:Str        1:Int      2:Dex      3:Con
		                          // 스페셜 0:Special1   1:Special2 2:Special2 3:Special4
		                          // 기술번호  1000-1071  (Detail-1000)/24=Class   (Detail-1000)%24=SkillNumber
		 unsigned short TargetID;
};

#define _MSG_SetShortSkill                 (120 | FLAG_CLIENT2GAME)
struct   MSG_SetShortSkill
{
	    _MSG;
		char  Skill[12];              // 스킬번호 0-23
};

//#define _MSG_Buy                           (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
//struct   MSG_Buy
//{
//	    _MSG;
//		unsigned short TargetID;                // 사려는 상인 NPC ID
//		short TargetInvenPos;          // 사려는 상인의 Inven 위치.
//		short MyInvenPos;              // 사서 받으려는 나의 Inven 위치.
//		int   Coin;
//};
//
//#define _MSG_Sell                          (122 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
//struct   MSG_Sell
//{
//	    _MSG;
//		unsigned short TargetID;                // 팔려는 상인 NPC ID
//		short MyType;
//		short MyPos;                // 나의 팔 아이템의 Inven
//};
#define _MSG_REQShopList                  (123 | FLAG_CLIENT2GAME)
struct   MSG_REQShopList                 // 클라이언트가 보낼때는 Leader만 사용. 
{                                        // 서버가 보낼때는 전체 리스트
	    _MSG;
		 unsigned short TargetID;
};
#define  _MSG_ShopList                   (124 | FLAG_GAME2CLIENT )
struct    MSG_ShopList
{
	      _MSG;
		  int         ShopType;              // 1:상인  2:카고(안쓰지만)  3:스킬
		  STRUCT_ITEM List[MAX_SHOPLIST];
		  int         Tax;
};

#define  _MSG_SetHpMp                         (129 | FLAG_GAME2CLIENT )
struct    MSG_SetHpMp
{
         _MSG;
		 short Hp,Mp;
		 short ReqHp,ReqMp;

};
#define _MSG_SendItem                         (130 | FLAG_GAME2CLIENT )
struct   MSG_SendItem
{  
        _MSG;
		short DestType;
		short DestPos;
		STRUCT_ITEM Item;
};
#define _MSG_Trade                            ( 131 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct   MSG_Trade
{       _MSG;
		int				nID;
		char			szCharName[SZNAME_LENGTH];
        STRUCT_ITEM		Item[MAX_TRADE];
		char			InvenPos[MAX_TRADE];
		int				TradeMoney;
		unsigned char	MyCheck;
		unsigned short	OpponentID;
};
#define _MSG_QuitTrade                       ( 132 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // STANDARD
#define _MSG_Inven                           ( 133 |FLAG_GAME2CLIENT)                    // STANDARD
struct   MSG_Inven
{
         _MSG;
         STRUCT_ITEM    Inven[72];
		 int            Coin;
};
#define _MSG_CNFCheck                        ( 134 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // STANDARD
#define _MSG_Withdraw                        ( 135 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // STANDARDPARM
#define _MSG_Deposit                         ( 136 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // STANDARDPARM

#define _MSG_Restart                         ( 137 | FLAG_CLIENT2GAME) // STANDARD
#define  _MSG_SetHpDam                       ( 138 | FLAG_GAME2CLIENT )
struct    MSG_SetHpDam
{
         _MSG;
		 short Hp,Dam;

};
#define _MSG_Weather                         ( 139 | FLAG_GAME2CLIENT ) // STANDARDPARM

#define _MSG_Quest                           ( 139 | FLAG_CLIENT2GAME ) // STANDARDPARM2
#define _MSG_Deprivate                       ( 140 | FLAG_CLIENT2GAME ) // STANDARDPARM

#define _MSG_ReqChallange                    ( 141 | FLAG_GAME2CLIENT ) // STANDARD       서버가 클라이언트에게 Ok,Cancel의 기회를 준다.
#define _MSG_Challange                       ( 142 | FLAG_CLIENT2GAME)  // STANDARDPARM Parm에 타겟 아이디.
#define _MSG_ChallangeConfirm                ( 143 | FLAG_CLIENT2GAME)  // ReqChallange에 대한 클라이언트의 응답이다.
#define _MSG_ReqTeleport                     ( 144 | FLAG_CLIENT2GAME )
#define _MSG_EnterVillage                    ( 145 | FLAG_CLIENT2GAME )
#define _MSG_SetHpMode                       ( 146 | FLAG_CLIENT2GAME ) 
struct   MSG_SetHpMode
{
         _MSG;
		 short Hp,Mode;

};
#define _MSG_SetClan                        ( 147 | FLAG_GAME2CLIENT )  // STANDARD PARM
#define _MSG_BillingPage                    ( 148 | FLAG_GAME2CLIENT )  // STANDARD PARM
#define _MSG_Imple                          ( 149 | FLAG_CLIENT2GAME )  // MSG_Whisper
#define _MSG_CloseShop                      ( 150 | FLAG_GAME2CLIENT )  // STANDARD

#define _MSG_AutoTrade                      ( 151 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct   MSG_AutoTrade
{       _MSG;
         char           Desc[MAX_DESC]; // 한글 11자 // 파는사람이름은 ID에서 구한다.
         STRUCT_ITEM    Item[MAX_AUTOTRADE];
		 char           InvenPos[MAX_AUTOTRADE];
		 int            TradeMoney[MAX_AUTOTRADE];
		 unsigned short Tax;
		 unsigned short TargetID;
};
#define _MSG_ReqBuy                         ( 152 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct  MSG_ReqBuy
{       _MSG;
        int Pos;
		unsigned short TargetID;
		int Price;
		int Tax;
		STRUCT_ITEM item;
};
#define _MSG_PKMode                         ( 153 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // Standard Parm
#define _MSG_ReqTradeList                   ( 154 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // Standard Parm
#define _MSG_ItemSold                       ( 155 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) // Standard Parm2  Parm1:Seller Parm2:Pos
#define _MSG_ClearMenu						( 156 |FLAG_GAME2CLIENT ) //




#define  _MSG_AttackOne                        (157 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_AttackOne
{
	    _MSG;
		//
		unsigned short		AttackerID;
		unsigned short		Progress;
		unsigned short		PosX,		PosY;
		unsigned short		TargetX,	TargetY;
		short 				SkillIndex;		// 0-98-106  (-1이면 물리적 공격)
        short				CurrentMp;
		unsigned char		Motion;
		unsigned char		SkillParm;		// 스킬 효과 증폭률 또는 물리공격 이펙트. 0 이 디폴트.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0비트 더블 1비트 크리티칼

		unsigned int		CurrentExp;
		short				ReqMp;
		short				Rsv;
		STRUCT_DAM			Dam[1];
};
#define  _MSG_AttackTwo						(158 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_AttackTwo
{
	    _MSG;
		unsigned short		AttackerID;
		unsigned short		Progress;
		unsigned short		PosX,		PosY;
		unsigned short		TargetX,	TargetY;
		short 				SkillIndex;		// 0-98-106  (-1이면 물리적 공격)
        short				CurrentMp;
		unsigned char		Motion;
		unsigned char		SkillParm;		// 스킬 효과 증폭률 또는 물리공격 이펙트. 0 이 디폴트.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0비트 더블 1비트 크리티칼
		unsigned int		CurrentExp;
		short				ReqMp;
		short				Rsv;
		//
		STRUCT_DAM			Dam[2];


};
#define	_MSG_ReqRanking						 (159 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARD_PARM2  PARM1:TargetID, PARM2: 0:1vs1 1:5vs5   2:10vs10  3:Ok

#define  _MSG_Ping 							 (160 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARD
#define  _MSG_StartTime						 (161 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM
#define  _MSG_EnvEffect						 (162 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME) 
struct    MSG_EnvEffect
{
	    _MSG;
		short		x1;
		short		y1;

		short		x2;
		short		y2;

		short		Effect;
		short		EffectParm;
};
#define	_MSG_SoundEffect						(163 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM
#define _MSG_GuildDisable                   	(164 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM

#define _MSG_GuildBoard							(165 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM2

#define _MSG_CombineItem                        (166 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct  MSG_CombineItem
{       _MSG;
		 STRUCT_ITEM    Item[MAX_TRADE];
		 char           InvenPos[MAX_TRADE];
};
#define _MSG_CombineComplete					(167 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM  0:취소 1:성공 2:실패
#define _MSG_WarInfo							(168 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM  전쟁중 길드, 0은 해제
#define _MSG_TransperCharacter					(169 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME)  // STANDARDPARM2 
#define _MSG_ReqTransper						(170 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB)  // STANDARDPARM2 
struct MSG_ReqTransper						
{       _MSG;
		int		Result;							// 0:Success		1:Same Name Exist		2:No Space at Transper Server   3:Unknown Error	
		int		Slot;
		char	OldName[SZNAME_LENGTH];
		char	NewName[SZNAME_LENGTH];

};
//#define	  //efine _MSG_ReqTransper						(170 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME)  // STANDARDPARM2 

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//               NP 서버   - >   DB 서버
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define FLAG_DB2NP                      0x1000        
#define FLAG_NP2DB                      0x2000        

#define  _MSG_NPReqIDPASS            ( 1 | FLAG_DB2NP) //   어카운트 만들기
#define  _MSG_NPIDPASS               ( 2 | FLAG_NP2DB) //   캐랙터 만들기
struct    MSG_NPIDPASS
{        _MSG;
		 int  nID;
		 char Account[ACCOUNTNAME_LENGTH];
		 int  Encode1;
		 char Pass[ACCOUNTPASS_LENGTH];
		 int  Encode2;
};
#define  _MSG_NPReqAccount           ( 3 | FLAG_NP2DB) //   어카운트 조회
struct    MSG_NPReqAccount
{        _MSG;
		 char Account[ACCOUNTNAME_LENGTH];
		 char Char[SZNAME_LENGTH];
};
#define  _MSG_NPNotFound             ( 4 | FLAG_DB2NP) //   Signal
#define  _MSG_NPAccountInfo          ( 5 | FLAG_DB2NP) //   
struct    MSG_NPAccountInfo
{        _MSG;
		  STRUCT_ACCOUNTFILE account;
		  short Session;
		  short State;           // 0:Normal  1:Blocked(@)  2:Deleted(_)  3:Disabled(#)
		  char GuildName[GUILDNAME_LENGTH];
		  int  GuildRank;
		  char Memo[MAX_CHAT_LENGTH];
};
#define  _MSG_NPReqSaveAccount       ( 6 | FLAG_NP2DB) //   MSG_NPAccountInfo
#define  _MSG_NPDisable              ( 7 | FLAG_NP2DB | FLAG_DB2NP) 
#define  _MSG_NPEnable               ( 8 | FLAG_NP2DB | FLAG_DB2NP) //   NPEnableParm 
struct    MSG_NPEnable
{        _MSG;
          char     AccountName[ACCOUNTNAME_LENGTH];
};

#define  _MSG_NPNotice               ( 9 | FLAG_NP2DB| FLAG_DB2NP | FLAG_DB2GAME) //   Parm 
struct    MSG_NPNotice
{        _MSG;
		  int	   nID;
          int      Parm1;
		  int      Parm2;
          char     AccountName[ACCOUNTNAME_LENGTH];
		  char     String[MAX_NOTIFY_LENGTH];  
};

#define  _MSG_NPState               (10 | FLAG_NP2DB| FLAG_DB2NP) //   Parm 

#define _MSG_NPCreateCharacter       (11 | FLAG_NP2DB| FLAG_DB2NP) 
struct	 MSG_NPCreateCharacter
{       _MSG;
		int nSlot;
		char szAccountName[ACCOUNTNAME_LENGTH];
		char szCharName[SZNAME_LENGTH];
		STRUCT_MOB MOB;
};
#define _MSG_NPDeleteCharacter  (12 | FLAG_NP2DB| FLAG_DB2NP) // Result 0: Success Delete Parm2
struct MSG_NPDeleteCharacter								  //        1: Threre's Same Name Already
{		_MSG;												  //        2: No space
		int nSlot;
		char szAccountName[ACCOUNTNAME_LENGTH];
		char szCharName[SZNAME_LENGTH];
};

#define _MSG_NPUserCount	( 13 | FLAG_NP2DB | FLAG_DB2NP )
struct MSG_NPUserCount
{	_MSG;
	int nUserCount[MAX_SERVER];
};

#define _MSG_NPAppeal		( 14 | FLAG_NP2DB | FLAG_DB2NP )
struct MSG_NPAppeal
{	_MSG;
	char szAccountName[ACCOUNTNAME_LENGTH];
	char szCharName[SZNAME_LENGTH];
	char szMsg[MAX_CHAT_LENGTH];
};

#define _MSG_NPReqGuildInfo	( 15 | FLAG_NP2DB )
struct MSG_NPReqGuildInfo
{	_MSG;
	int			nGuildID;
    char		GuildName[SZNAME_LENGTH];
};
#define _MSG_NPGuildInfo	( 16 | FLAG_DB2NP )
struct MSG_NPGuildInfo
{	_MSG;
	int			 nGuildID;
	STRUCT_GUILD GuildInfo;
};

#define _MSG_NPAdminLevel	( 17 | FLAG_DB2NP | FLAG_NP2DB )
struct MSG_NPAdminLevel
{	_MSG;
	int		nUser;
	int		nLevel;
};

#define _MSG_NPTaskInfo		( 18 | FLAG_NP2DB )
struct MSG_NPTaskInfo
{	_MSG;
	int			nZoneNumber;
	int			nTaskNumber;
	TASK_INFO	sTaskInfo;
};

#define _MSG_NPGiftInfo		( 19 | FLAG_NP2DB )
struct MSG_NPGiftInfo
{	_MSG;
	int		nGiftItemIndex;
	int		nGiftItemCount;
	short	snGiftItemGenTime;
	short	snZone;
};

#define _MSG_NPGuildItemUpdate  ( 20 | FLAG_NP2DB )
struct MSG_NPGuildItemUpdate
{	_MSG;
	int				nGuildID;
	int				nGuildInvenIndex;
	STRUCT_ITEM		sItem;
};


struct S_SellItem
{
	unsigned long	dwItemID;
	unsigned long	dwPrice;
	unsigned long	dwCount;
};

struct S_LimitedStore
{
	int nNPCID;
	S_SellItem	stItem[MAX_LIMITEDITEM+1];	//	0번 index는 사용안한다
};

#define _MSG_NPLimitedStore		( 21 |  FLAG_NP2DB )
struct MSG_NPLimitedStore
{
	_MSG;
	byte			byZone;
	byte			byDummy;
	short			snDummy;
	S_LimitedStore	stStore;
};
// 0:Success		1:Same Name Exist		2:No Space at Transper Server   3:Unknown Error	

#define _MSG_NPGuildCargoUpdate  ( 22 | FLAG_NP2DB )
struct MSG_NPGuildCargoUpdate
{	_MSG;
	int				nGuildID;
	STRUCT_ITEM		sItem[MAX_CARGO*3];
	DWORD			dwTime[3];
};


/////////////////////////////////////////////////////////////////////
//       펑션
/////////////////////////////////////////////////////////////////////
//void                BASE_ClearMob             (STRUCT_MOB*    mob);
//void                BASE_ClearItem            (STRUCT_ITEM*   item);
//int                 BASE_GetMobAbility        (STRUCT_MOB*    mob,   unsigned char Type);
//int                 BASE_GetMaxAbility        (STRUCT_MOB*    mob,   unsigned char Type);

//int                 BASE_GetItemAbility       (STRUCT_ITEM*   item,  unsigned char Type);
//int                 BASE_GetItemAbilityNosancE_COUNTRY_ID contry (STRUCT_ITEM*   item,  unsigned char Type);
//int                 BASE_GetStaticItemAbility (STRUCT_ITEM*   item,  unsigned char Type);
//int                 BASE_GetBonusItemAbility  (STRUCT_ITEM*   item,  unsigned char Type);
//int                 BASE_GetBonusItemAbilityNosanc  (STRUCT_ITEM*   item,  unsigned char Type);
//int                 BASE_GetMobCheckSum       (STRUCT_MOB*    mob);
int                 BASE_InitializeBaseDef    (E_COUNTRY_ID contry);

//void                BASE_InitializeszName(char * file,int off);
void                BASE_InitializeMessage(char * file);
//void				BASE_WriteMessageBin();
//BOOL				BASE_ReadMessageBin();
void				BASE_InitModuleDir        (void);
//void				BASE_InitializeEffectName (void);
//void			    BASE_InitializeMathTable  (void);
//void                BASE_InitializeItemList   (void);
BOOL				BASE_ReadItemListFile(char * filename,int build);
//void                BASE_InitializeHitRate    (void);
//void                BASE_InitializeInitItem   (void);
int                 BASE_InitializeAttribute  (E_COUNTRY_ID contry);
//void                BASE_InitializeGuildName  (void);
//void				BASE_InitializeClientGuildName(int group);

//void				BASE_ApplyAttribute(char * pHeight,int size);
//int                 BASE_ReadItemList         (void);
//void				BASE_UnderBarToSpace      (char*          szStr);
//void				BASE_SpaceToUnderBar      (char*          szStr);
bool				BASE_CheckValidString     (char*          szCharacterID );
//bool				BASE_CheckHangul          (unsigned short word);
//void                BASE_InitializeSkill      (void);
//BOOL BASE_CheckPacket(MSG_STANDARD *m);
////////////////////////  CLIENT BINARY RESOURCE ///////////////////////////
//void				BASE_WriteSkillBin		  (void);
//int  				BASE_ReadSkillBin		  (void);
//void				BASE_WriteItemList        (int nItemList);
//void				BASE_ReadItemList         (void);
//void				BASE_WriteEffectNameTable (void);
//void				BASE_ReadEffectNameTable  (void);
//void                BASE_WriteInitItem        (void);
//int                 BASE_ReadInitItem         (void);

//BOOL                BASE_CanInven             (STRUCT_ITEM *item, STRUCT_ITEM  *Inven,int DestX,int DestY,int * error);
BOOL                BASE_CanTrade(STRUCT_ITEM * Inven,int nCount,STRUCT_ITEM *MyTrade,STRUCT_ITEM * OpponentTrade);
//BOOL                BASE_CanCargo(STRUCT_ITEM *item, STRUCT_ITEM  *cargo,int DestX,int DestY);
//BOOL                BASE_CanEquip             (STRUCT_ITEM* item, STRUCT_SCORE *score,int Pos, int Class, STRUCT_ITEM* pBaseEquip);
//void                BASE_GetDestByAction      (unsigned short *x,unsigned short * y, MSG_Action * mv);
//int                 BASE_GetHitRate           (STRUCT_SCORE* att, STRUCT_SCORE* def);
//int                 BASE_GetDamageRate        (STRUCT_SCORE* att, int idx);
//int                 BASE_GetHitDamage(STRUCT_SCORE *att, STRUCT_SCORE *def,int Skill,unsigned char * Progress,int Critical,unsigned int * ProgressPoint, unsigned char * bDouble, unsigned char * bCritical,unsigned char * error);
//void                BASE_GetCurrentScore(STRUCT_MOB & MOB,STRUCT_AFFECT * Affect);
int                 BASE_GetRoute(int x,int y,int *tx,int *ty,char *Route,int distance, int m_iBlockedCell ) ; //,short** height);
int                 BASE_GetDistance(int x1,int y1,int x2,int y2);
//BOOL                BASE_UpdateItem(int maskidx,int CurrentState,int NextState,int xx,int yy,char * pHeight,int Rotate,int * height);
void                BASE_GetHitPosition(int sx, int sy, int * tx , int  *ty ) ; //, short** pHeight);
//void                BASE_GetHitPosition2(int sx, int sy, int * tx , int  *ty,char * pHeight);

//int                 BASE_GetSpeed(STRUCT_SCORE *score);
//int                 BASE_GetManaSpent(int SKillNumber, int SaveMana,int Special);
//BOOL				BASE_GetDoubleCritical(STRUCT_MOB *mob, unsigned short * sProgress, unsigned short *cProgress, unsigned char * bDoubleCritical);
//int                 BASE_GetDamage(int dam,int ac , int combat);
//int                 BASE_GetSkillDamage(int dam,int ac,int combat);

BOOL                BASE_InitializeServerList(void);
BOOL                BASE_InitializeServerList_Client(int *pTest, int *pCountryCode);
int                 BASE_GetIndex(STRUCT_ITEM * item);
//
//int                 BASE_GetArena(int x, int y);
//int                 BASE_GetVillage(int x, int y);
//void				BASE_GetGuildName(int ServerGroup,unsigned short usGuild, char* szGuildName);
//void				BASE_GetClientGuildName(int ServerGroup,unsigned short usGuild, char* szGuildName,int Sub=0);


//BOOL                BASE_UpdateItem2(int maskidx,int CurrentState,int NextState,int xx,int yy,char * pHeight,int rotate,int height);

// ANSI       [Blink] [Letter-R] [Letter-G] [Letter-B] [BOLD] [bg-R] [bg-G] [bg-B]
//              7        6           5          4        3      2      1      0

//extern void BASE_WriteItemList(int nItemList);
//extern int  BASE_GetAccuracyRate(STRUCT_SCORE *att);
extern void BASE_GetFirstKey(char * source,char * dest);
extern bool BASE_GetKey(int nUserID , BYTE byPlace, BYTE byPosition, int& nKey);
void BASE_SpaceToUnderBar(char* szStr);
void BASE_UnderBarToSpace(char* szStr);
extern BYTE BASE_GetRefineVariable(STRUCT_ITEM * pRef);

//extern void BASE_GetKorFirst(int temp,int *a);
//extern int  BASE_GetItemSanc(STRUCT_ITEM * item);
//extern int  BASE_GetItemSancSuccess(STRUCT_ITEM * item);
//extern int  BASE_GetSuccessRate(STRUCT_ITEM * item,int OriLacto);
//extern int	BASE_GetGrowthRate(STRUCT_ITEM * item);

//extern int  BASE_SetItemSanc(STRUCT_ITEM * item,int sanc,int success);
//
//extern int  BASE_GetItemAmount(STRUCT_ITEM * item);
//extern void BASE_SetItemAmount(STRUCT_ITEM * item,int amount);
//extern int BASE_GetSum(char * p ,int size);
//extern int BASE_GetSum2(char * p ,int size);

//void BASE_GetLanguage(char *str,int idx);
//void BASE_GetLanguage(char *str,int idx,char *parm1);
//void BASE_GetLanguage(char *str,int idx,char *parm1 , char *parm2);
//void BASE_GetLanguage(char *str,int idx,int parm1);
//void BASE_GetLanguage(char *str,int idx,int parm1, int parm2);
//void BASE_GetLanguage(char *str,int idx,char * parm1, int parm2);
//void BASE_GetLanguage(char *str,int idx,int parm1, char *parm2);
BOOL BASE_CheckItemLog(STRUCT_ITEM *pItem);
void BASE_GetItemCode(STRUCT_ITEM * item,char * str);

//extern void BASE_SortTradeItem(STRUCT_ITEM * Item,int Type); // Buffer의 크기는 int * Size
extern STRUCT_ITEM * GetItemPointer(STRUCT_MOB * mob, STRUCT_ITEM * cargo,int type,int pos);
//extern int  BASE_GetSkillDamage(int SkillNum, STRUCT_MOB * mob,int weather,int weapondamage);

extern char g_pFormation[MAX_FORMATION][MAX_PARTY][2]; 
extern int			g_pNextLevel[MAX_LEVEL+1];
extern int			g_pIncrementHp[4];
extern int			g_pIncrementMp[4];
extern STRUCT_SPELL g_pSpell[MAX_SKILLINDEX];
extern char			g_pAffectTable[32][24];

//extern short pHeightGrid[MAX_GRIDY][MAX_GRIDX];
//extern WORD g_pAttribute[MAX_GRIDY][MAX_GRIDX];

extern BOOL		BASE_GetHttpRequest(char * httpname,char * Request,int MaxBuffer);
extern int		BASE_GetEnglish(char *name);
int				BASE_GetHpMp(STRUCT_MOB* mob);
extern char		g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
extern unsigned	g_pServerListBin[MAX_SERVERGROUP][MAX_SERVERNUMBER];
extern unsigned	short g_pServerListPort[MAX_SERVERGROUP][MAX_SERVERNUMBER];

#define MAX_STRING          400
extern char  g_pMessageStringTable[MAX_STRING][128];
extern int BASE_NeedLog(STRUCT_ITEM *item,int money);
extern int BaseSIDCHM[4][6];
#define ATT_VILLAGE     1
#define ATT_CANTGO      2
#define ATT_CANTSUMMON  4
#define ATT_HOUSE       8
#define ATT_TELEPORT   16
#define ATT_GUILD      32
#define ATT_PK         64 
#define ATT_NEWBIE    128 


#define RSV_FROST    0x01
#define RSV_DRAIN    0x02
#define RSV_VISION   0x04
#define RSV_PARRY    0x08
#define RSV_HIDE	 0x10
#define RSV_HASTE    0x20
#define RSV_CAST     0x40
#define RSV_BLOCK    0x80

//#define MSV_RANGE	 0x01
//#define MSV_CRAFT	 0x02
//#define MSV_BACKPACK 0x04
#define MSV_SNOOP	0x01	// CreateMob에 전달되는것은 0-3비트
#define MSV_TOWN	0xC0	// 상위 2비트가 시작 마을이다

#define                TIMER_SEC    0
#define                TIMER_MIN    1
#define                TIMER_HOUR   2
#define					TIMER_YUT	5

#define LEARN_00	0x00000001
#define LEARN_01	0x00000002
#define LEARN_02	0x00000004
#define LEARN_03	0x00000008
#define LEARN_04	0x00000010
#define LEARN_05	0x00000020
#define LEARN_06	0x00000040
#define LEARN_07	0x00000080
#define LEARN_08	0x00000100
#define LEARN_09	0x00000200
#define LEARN_10	0x00000400
#define LEARN_11	0x00000800
#define LEARN_12	0x00001000
#define LEARN_13	0x00002000
#define LEARN_14	0x00004000
#define LEARN_15	0x00008000
#define LEARN_16	0x00010000
#define LEARN_17	0x00020000
#define LEARN_18	0x00040000
#define LEARN_19	0x00080000
#define LEARN_20	0x00100000
#define LEARN_21	0x00200000
#define LEARN_22	0x00400000
#define LEARN_23	0x00800000

#define CELL_SAFE_ZONE			 (0x01)
#define CELL_CONFLICT_ENABLE	 (0x02)
#define CELL_PK_ENABLE			 (0x04)
#define CELL_INDOOR				 (0x08)
#define CELL_MOVE_DISABLE		 (0x10)
#define CELL_SIT_ENABLE			 (0x20)
#define MAP_OBJECT_SIT_ENABLE	 (0x40)
#define MAP_OBJECT_MOUNT_ENABLE	 (0x80)

#define CSP_REQ_LOGIN                                     0x1001      // 로그인 요청 메시지
#define CSP_REQ_WORLD_LIST                                0x1002      // 월드 서버 리스트 요청
#define CSP_REQ_MOVE_ZONE_SERVER                          0x1003      // 월드 대표 존서버에 접속을 요청
#define _Msg_VersionCheck								0x1004			//	클라이언트의 버전을 체크한다.
#define CSP_REQ_CHAR_LIST                                 0x1011      // 해당 월드의 캐릭터 리스트 요청
#define CSP_REQ_CHAR_CREATE                               0x1012      // 케릭터 생성을 요청
#define CSP_REQ_CHAR_REMOVE                               0x1013      // 케릭터 삭제를 요청
#define CSP_REQ_CHAR_SELECT                               0x1014      // 케릭터 선택후 존서버 접속 요청
#define CSP_REQ_EXIT_ZONE_SERVER                          0x1015      // 캐릭터 선택창을 빠져나가고, 월드서버 선택창으로 이동 요청
#define CSP_REQ_CHAR_LOGOUT                               0x1021      // 캐릭터의 로그 아웃을 요청
#define CSP_REQ_REMOVE_MOB								  0x1022      // 캐릭터 로그아웃, 워프, 순간이동의 주변전송 요청
#define CSP_OTHER_CHAR_LOGOUT_NOTIFY                      0x1023      // 캐릭터의 로그아웃, 워프, 순간이동을 파티, 길드, 주소록 관련 케릭터에게 전송요청
const int	_MSG_Status					=	0x1031;
struct MSG_Status
{
	_MSG
	int		nID;
	BYTE	byStatus;
	BYTE	byDummy1;
	short	snDummy1;
};
#define CSP_REQ_CHAR_INIT                                 0x1101      // 캐릭터의 접속초기정보 요청 메세지
const int	_MSG_InitSkill				=	0x1104;
struct MSG_InitSkill
{
	_MSG
	BYTE					bySkill[MAX_SKILL];
};

#define CSP_INIT_GUILD                                    0x1105      // 자신의 길드초기정보를 전송함.
#define CSP_INIT_ADDRESS_BOOK                             0x1106      // 주소록 정보 전송을 요청
#define CSP_REQ_CHAR_HISTORY                              0x1108      // 케릭터 히스토리정보 요청
#define CSP_INIT_EQUIPMENT                                0x1109      // 케릭터 착용장비 요청
//#define CSP_INIT_MONSTER_NPC                              0x1111      // 주변 Monster/NPC 정보 전송 요청
#define CSP_INIT_OTHER_MOB                                0x1112      // 주변 다른 케릭터 정보 전송 요청
#define CSP_INIT_REAL_ADDRESS_BOOK                        0x1113      // 주소록 정보 전송을 요청
#define CSP_INIT_REAL_GUILD                               0x1114      // 길드 정보 전송을 요청
#define CSP_INIT_REAL_GUILD_MEMBER                        0x1115      // 길드 정보 전송을 요청
#define CSP_INIT_ITEM                                     0x1121      // 주변 아이템 데이터 처리 요청 메세지
#define CSP_INIT_WORLD_USER_COUNT                         0x1161      // 월드별 접속자수를 처리함.
#define CSP_INIT_GUILD_MEMBER                             0x1171      // 자신의 길드원정보를 전송함.
#define _MSG_TrimuritiCount					0x1181
struct MSG_TrimuritiCount
{
	_MSG
	DWORD	dwBrahma;
	DWORD	dwVishunu;
	DWORD	dwSiva;
};

#define CSP_REQ_CHAR_MOVE                                 0x1201      // 캐릭터 이동 요청 메시지
#define CSP_OTHER_CHAR_MOVE                               0x1202      // 캐릭터의 이동성공을 다른 캐릭터에게 알려줌
#define CSP_MONSTER_MOVE_STEP                             0x1206      // 한셀 이동을 주변에 전송
#define CSP_MONSTER_MOVE_NSTEP                            0x1207      // 여러셀 이동을 주변에 전송
#define CSP_MONSTER_MOVE_END                              0x1208      // 여러셀 이동의 결과 좌표를 전송
#define CSP_REQ_ITEM_USE                                  0x1223      // 아이템 사용 요청
#define CSP_ITEM_USE_BROADCAST                            0x1224      // 아이템 사용을 주변 다른 캐릭터들에게 전송 요청
#define CSP_ITEM_REMOVE                                   0x1225      // 인벤토리에서 아이템 사라짐을 요청
#define CSP_REQ_CHAR_MOVE_BROADCAST                       0x1227      // 케릭터의 이동을 요청한다.

#define CSP_REQ_ATK_CHAR                                  0x1301      // 캐릭터의 공격 요청
#define CSP_ATK_CHAR_BROADCAST                            0x1302      // 캐릭터의 공격을 주변 캐릭터들에게 전송 요청
#define CSP_REQ_ITEM_EQUIPMENT                            0x1401      // 아이템 장착을 요청
#define CSP_ITEM_EQUIPMENT_BROADCAST                      0x1402      // 아이템 장착을 주변 캐릭터에게 전송
#define CSP_ITEM_ABRASION                                 0x1411      // 아이템 사라짐을 알림
#define CSP_ITEM_ABRASION_BROADCAST                       0x1412      // 아이템 사라짐을 주변 다른 캐릭터들에게 전송

//	1501	CHAT
//	1601	GUILD
#define CSP_REQ_QUEST_HISTORY                             0x1701      // 퀘스트 히스토리 정보 요청
#define CSP_QUEST_DIALOG                                  0x1702      // 대화문 결과 전송
#define CSP_QUEST_NOTIFY_LEVEL                            0x1703      // 퀘스트 단계 알림
#define CSP_CHAR_PING                                     0x1831      // 케릭터의 게임접속중임을 알린다.
#define _MSG_Beauty							0x1912						//	케릭터 미용실
struct MSG_Beauty
{
	_MSG
	BYTE			byResult;
	BYTE			byDummy;
	BYTE       		byFace; 
	BYTE			byHead;
	short      		snTribe;
	short			snDummy;
	int				nCash;
};

#define _MSG_CLASS							0x1981				// 케릭터의 전직을 요청한다.
struct MSG_CLASS
{
	_MSG
	int			nID;
	BYTE		byClass1;
	BYTE		byClass2;
	short		snDummy;
};
#define _MSG_TOGGLE_BUTTON								  0x1980
#define _MSG_CHANGE_TARGET								  0x1990
#define CSP_REQ_SKILL_REGIST                              0x2001      // 스킬 등록을 요청한다
#define CSP_SKILL_REGIST                                  0x2002      // 카스트 상승에 따른 스킬 자동 등록을 알려준다
#define CSP_REQ_SKILL_SELECT                              0x2003      // 등록된 스킬을 선택/해제
#define CSP_REQ_SKILL_SELECT_BROADCAST                    0x2004      // 등록된 스킬을 선택/해제
#define CSP_REQ_SKILL_USE2_CHAR                           0x2011      // 캐릭터의 스킬 공격 준비동작을 요청
#define CSP_SKILL_READY_CHAR_BROADCAST                    0x2012      // 캐릭터의 스킬 공격 준비동작을 주변에 전송
#define CSP_REQ_SKILL_ATK_CHAR                            0x2013      // 캐릭터의 스킬 공격을 요청
#define CSP_SKILL_ATK_CHAR_BROADCAST                      0x2014      // 캐릭터의 스킬 공격을 주변 캐릭터들에게 전송
#define CSP_REQ_SKILL_LEVEL_UP                            0x2021      // 캐릭터의 스킬 Level-Up을 요청
#define CSP_REQ_SHOP_SKILL_LIST                           0x2022      // 습득 가능한 스킬 List를 요청
//	0x2201	TRADE
#define CSP_REQ_MY_ENTYR_LIST                             0x2305      // 자신이 등록,보관 아이템 요청
#define CSP_REQ_TRADE_ITEM_SEEK                           0x2306      // 보관 아이템 찾기 요청
//	0X2401	PARTY
#define CSP_REQ_TROUBLE_REPORT                            0x2541      // 서버에 신고내용을 접수한다.
#define CSP_REQ_TROUBLE_REPORT_LIST                       0x2542      // 서버에 신고내용의 리스트를 요청한다.
#define CSP_REQ_TROUBLE_REPORT_SET                        0x2543      // 신고내용의 처리상황을 받는다.
#define GCSP_REQ_TROUBLE_REPORT_LIST                      0x2544      // 로그인 요청 메시지
#define GCSP_REQ_TROUBLE_REPORT_SET                       0x2545      // 로그인 요청 메시지
#define GCSP_REQ_TROUBLE_REPORT                           0x2546      // 로그인 요청 메시지
#define GCSP_REQ_PARAMETER_CHANGE                         0x2550      // 캐릭터의 기본 정보값을 변경 요청
#define GCSP_REQ_ITEM_INSERT                              0x2551      // 아이템 삽입 요청
#define GCSP_REQ_ITEM_DELETE                              0x2552      // 아이템 삭제 요청
#define GCSP_REQ_SKILL_INSERT                             0x2553      // 스킬 삽입 요청
#define GCSP_REQ_SKILL_DELETE                             0x2554      // 스킬 삭제 요청
#define CSP_REQ_CHAR_INFO                                 0x2561      // 케릭터 정보 요청 메시지
#define CSP_REQ_CHAR_EQUIPMENT                            0x2562      // 케릭터의 장착정보 요청 메시지
#define CSP_REQ_CHAR_SKILL                                0x2563      // 케릭터의 스킬정보 요청 메시지
#define CSP_REQ_CLOSE_CHAR                                0x2571      // 케릭터의 접속종료 요청 메시지
#define CSP_REQ_JOIN_ADDRESS_BOOK                         0x2603      // 주소록에 캐릭터 추가를 요청
#define CSP_JOIN_ADDRESS_BOOK_NOTIFY                      0x2604      // 주소록 추가 요청을 캐릭터에게 전송요청 메세지
#define CSP_REQ_JOIN_ADDRESS_BOOK_RESULT                  0x2605      // 주소록 추가 요청 결과를 서버에 전송
#define CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0x2606      // 주소록 추가 요청에 대한 승인 결과를 캐릭터에게 전송요청메세지
#define CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE                0x2607      // 주소록에 있는 캐릭터 정보의 삭제를 요청
#define CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0x2608      // 주소록에서 삭제를 알린다
#define CSP_REQ_ADDRESS_BOOK_GROUP_ADD                    0x2611      // 주소록에 그룹의 추가를 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_DELETE                 0x2612      // 주소록에 그룹의 삭제를 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_MOVE                   0x2613      // 주소록에 케릭터의 그룹이동을 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_RENAME                 0x2614      // 주소록에 그룹의 이름변경을 요청
#define CSP_REQ_ADDRESS_BOOK_STATUS                       0x2621      // 주소록 등록요청의 거부를 세팅요청
#define CSP_REQ_LEARN_SKILL                               0x3210      // Learn a skill
#define CSP_REQ_CAST_SKILL                                0x3220      // cast a skill
#define CSP_CAST_SKILL_BROADCAST                          0x3230      // cast a skill
#define CSP_CAST_UNIT_SKILL                               0x3240      // unit을 타겟으로 하는 스킬
#define CSP_CAST_AREA_SKILL                               0x3250      // ground를 타겟으로 하는 범위 스킬
#define CSP_DEBUFFER_SKILL                                0X3260      // 버핑된 skill이 강제적으로 remove됐음을 알린다.
#define CSP_REQ_CHAR_ACT                                  0x3300      // Action
#define CSP_CHAR_ACT_BROADCAST                            0x3310      // Action을 broadcast
#define CSP_REQ_UPDATE_UI                                 0x3500      // Update UI
#define CSP_REQ_UPDATE_STATUS                             0x3501      // Update Status
#define CSP_LEVEL_UP_BROADCAST                            0x3510      // level up
#define CSP_REQ_INCREASE_CHAKRA                           0x3520      // Increase a chakra point

#define SCP_RESP_LOGIN                                    0x9001      // 로그인 응답 메시지
#define SCP_RESP_WORLD_LIST                               0x9002      // 월드 서버 리스트 응답
#define SCP_RESP_MOVE_ZONE_SERVER                         0x9003      // 월드 대표 존서버에 접속 응답
#define SCP_RESP_CHAR_LIST                                0x9011      // 캐릭터 리스트 전송
#define SCP_RESP_CHAR_CREATE                              0x9012      // 케릭터 생성 응답 메시지
#define SCP_RESP_CHAR_REMOVE                              0x9013      // 케릭터 삭제 응답 메세지
#define SCP_RESP_CHAR_SELECT	                          0x9014      // 케릭터 선택후 존서버 접속 응답 메시지
#define SCP_RESP_EXIT_ZONE_SERVER                         0x9015      // 캐릭터 선택창을 빠져나가고, 월드서버 선택창으로 이동 응답 메세지
#define SCP_RESP_CHAR_LOGOUT                              0x9021      // 캐릭터의 로그 아웃 응답 메시지
#define SCP_RESP_REMOVE_MOB                               0x9022      // 캐릭터 로그아웃, 워프, 순간이동의 주변전송 응답 메세지
#define SCP_OTHER_CHAR_LOGOUT_NOTIFY                      0x9023      // 캐릭터의 로그아웃, 워프, 순간이동을 파티, 길드, 주소록 관련 케릭터에게 전송 응답 메세지
#define SCP_RESP_CHAR_INIT                                0x9101      // 캐릭터의 접속초기정보 응답 메세지

#define SCP_INIT_SKILL                                    0x9104      // 케릭터의 스킬정보 전송 응답 메세지
#define SCP_INIT_GUILD                                    0x9105      // 길드의 실시간 정보 전송 응답 메세지
#define SCP_INIT_ADDRESS_BOOK                             0x9106      // 주소록 정보 전송 응답 메세지
#define SCP_RESP_CHAR_HISTORY                             0x9108      // 케릭터 히스토리정보 응답 메세지
#define SCP_INIT_EQUIPMENT                                0x9109      // 케릭터 착용장비 요청에 대한 응답 메세지
//#define SCP_INIT_MONSTER_NPC                              0x9111      // 주변 Monster/NPC 정보 전송 응답 메세지
#define SCP_INIT_OTHER_MOB                                0x9112      // 주변 다른 케릭터 정보 응답 메세지
#define SCP_INIT_REAL_ADDRESS_BOOK                        0x9113      // 주소록 정보 전송 응답 메세지
#define SCP_INIT_REAL_GUILD                               0x9114      // 길드의 실시간 정보 전송 응답 메세지
#define SCP_INIT_REAL_GUILD_MEMBER                        0x9115      // 길드멤의 실시간 정보 전송 응답 메세지
#define SCP_INIT_ITEM                                     0x9121      // 주변 아이템 데이터 처리 응답 메세지
#define SCP_INIT_WORLD_USER_COUNT                         0x9161      // 월드별 접속자수를 처리함.
#define SCP_INIT_GUILD_MEMBER                             0x9171      // 자신의 길드원정보를 전송함.
#define SCP_RESP_CHAR_MOVE                                0x9201      // 캐릭터 이동에 대한 결과 메시지
#define SCP_OTHER_CHAR_MOVE                               0x9202      // 이동정보를 다른 캐릭터에게 알려줌
#define SCP_MONSTER_MOVE_STEP                             0x9206      // 한셀 이동을 주변에 전송
#define SCP_MONSTER_MOVE_NSTEP                            0x9207      // 여러셀 이동을 주변에 전송
#define SCP_MONSTER_MOVE_END                              0x9208      // 여러셀 이동의 결과 좌표를 전송
#define SCP_RESP_ITEM_USE                                 0x9223      // 아이템 사용 응답 메세지
#define SCP_ITEM_USE_BROADCAST                            0x9224      // 아이템 사용을 주변 다른 캐릭터들에게 전송 응답 메세지
#define SCP_ITEM_REMOVE                                   0x9225      // 인벤토리에서 아이템 사라짐을 알려줌
#define SCP_RESP_CHAR_MOVE_BROADCAST                      0x9227      // 케릭터의 이동을 요청에 대한 응답메세지
#define SCP_RESP_ATK_CHAR                                 0x9301      // 캐릭터의 공격 응답 메세지
#define SCP_ATK_CHAR_BROADCAST                            0x9302      // 캐릭터의 공격을 주변 캐릭터들에게 전송 응답 메세지
#define SCP_RESP_ITEM_EQUIPMENT                           0x9401      // 아이템 장착 요청에 대한 결과
#define SCP_ITEM_EQUIPMENT_BROADCAST                      0x9402      // 아이템 장착을 주변 캐릭터에게 전송
#define SCP_ITEM_ABRASION                                 0x9411      // 아이템 사라짐을 알림 응답 메세지
#define SCP_ITEM_ABRASION_BROADCAST                       0x9412      // 아이템 사라짐을 주변 다른 캐릭터들에게 전송 응답 메세지
#define SCP_RESP_QUEST_HISTORY                            0x9701      // 퀘스트 히스토리 정보 전송
#define SCP_QUEST_DIALOG                                  0x9702      // 대화문 출력
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // 퀘스트 단계 알림
#define SCP_QUEST_DIALOG                                  0x9702      // 대화문 출력
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // 퀘스트 단계 알림
#define SCP_RESP_SKILL_REGIST                             0xA001      // 스킬 등록 결과 응답 메세지
#define SCP_SKILL_REGIST                                  0xA002      // 카스트 상승에 따른 스킬 자동 등록 결과 응답 메세지
#define SCP_RESP_SKILL_SELECT                             0xA003      // 등록된 스킬을 선택/해제 결과 응답 메세지
#define SCP_RESP_SKILL_SELECT_BROADCAST                   0xA004      // 등록된 스킬을 선택/해제 결과 응답 메세지
#define SCP_RESP_SKILL_USE2_CHAR                          0xA011      // 캐릭터의 스킬 공격 준비동작 요청 결과 메세지
#define SCP_SKILL_READY_CHAR_BROADCAST                    0xA012      // 캐릭터의 스킬 공격 준비동작을 주변에 전송결과 메세지
#define SCP_RESP_SKILL_ATK_CHAR                           0xA013      // 캐릭터의 스킬 공격 응답 메세지
#define SCP_SKILL_ATK_CHAR_BROADCAST                      0xA014      // 캐릭터의 스킬 공격을 주변 캐릭터들에게 전송 결과 메세지
#define SCP_RESP_SKILL_LEVEL_UP                           0xA021      // 캐릭터의 스킬 Level-Up 요청 결과 메세지
#define SCP_RESP_SHOP_SKILL_LIST                          0xA022      // 습득 가능한 스킬 List 요청에 대한 응답메세지
#define SCP_RESP_TROUBLE_REPORT                           0xA541      // 서버에 신고내용을 접수한다.
#define SCP_RESP_TROUBLE_REPORT_LIST                      0xA542      // 서버에 신고내용의 리스트를 요청한다.
#define SCP_RESP_TROUBLE_REPORT_SET                       0xA543      // 신고내용의 처리상황을 받는다.
#define GSCP_RESP_TROUBLE_REPORT_LIST                     0xA544      // 로그인 응답 메시지
#define GSCP_RESP_TROUBLE_REPORT_SET                      0xA545      // 로그인 응답 메시지
#define GSCP_RESP_TROUBLE_REPORT                          0xA546      // 로그인 응답 메시지
#define GSCP_INIT_ITEM                                    0xA548      // 캐릭터 아이템 정보
#define GSCP_INIT_SKILL                                   0xA549      // 캐릭터 스킬 정보
#define GSCP_RESP_PARAMETER_CHANGE                        0xA550      // 캐릭터의 기본 정보값을 변경 요청에 대한 결과
#define GSCP_RESP_ITEM_INSERT                             0xA551      // 아이템 삽입 결과
#define GSCP_RESP_ITEM_DELETE                             0xA552      // 아이템 삭제 결과
#define GSCP_RESP_SKILL_INSERT                            0xA553      // 스킬 삽입 결과
#define GSCP_RESP_SKILL_DELETE                            0xA554      // 스킬 삭제 결과
#define SCP_RESP_CHAR_INFO                                0xA561      // 케릭터 정보 응답 메시지
#define SCP_RESP_CHAR_EQUIPMENT                           0xA562      // 케릭터의 장착정보 응답 메시지
#define SCP_RESP_CHAR_SKILL                               0xA563      // 케릭터의 스킬정보 응답 메시지
#define SCP_RESP_CLOSE_CHAR                               0xA571      // 케릭터의 접속종료 응답 메시지
#define SCP_RESP_JOIN_ADDRESS_BOOK                        0xA603      // 주소록에 캐릭터추가 요청에 대한 응답메세지
#define SCP_JOIN_ADDRESS_BOOK_NOTIFY                      0xA604      // 주소록 추가 요청을 캐릭터에게 전송메세지
#define SCP_RESP_JOIN_ADDRESS_BOOK_RESULT                 0xA605      // 주소록 추가 요청 결과에 결과 메세지
#define SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0xA606      // 주소록 추가 요청에 대한 승인 결과를 캐릭터에게 전송
#define SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE               0xA607      // 주소록에 있는 캐릭터 정보의 삭제요청에 대한 응답메세지
#define SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0xA608      // 주소록에서 삭제를 알린다
#define SCP_RESP_ADDRESS_BOOK_GROUP_ADD                   0xA611      // 주소록에 그룹의 추가 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_DELETE                0xA612      // 주소록에 그룹의 삭제 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_MOVE                  0xA613      // 주소록에 케릭터의 그룹이동 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_RENAME                0xA614      // 주소록에 그룹의 이름변경을 요청결과
#define SCP_RESP_ADDRESS_BOOK_STATUS                      0xA621      // 주소록 등록요청의 거부를 세팅요청
#define MSG_ITEM_ID                                       0xB100      // item 관련
#define SCP_RESP_LEARN_SKILL                              0xB210      // Learn a skill
#define SCP_RESP_CAST_SKILL                               0xB220      // cast a skill
#define SCP_CAST_SKILL_BROADCAST                          0xB230      // cast a skill
#define SCP_RESP_CHAR_ACT                                 0xB300      // Action
#define SCP_CHAR_ACT_BROADCAST                            0xB310      // Action을 broadcast
#define SCP_RESP_UPDATE_UI                                0xB500      // Update UI
#define SCP_RESP_UPDATE_STATUS                            0xB501      // Update Status
#define SCP_LEVEL_UP_BROADCAST                            0xB510      // level up
#define SCP_RESP_INCREASE_CHAKRA                          0xB520      // Increase a chakra point
#define REGISTER_KALA_CORE								  0xB530      // register a kala-core on the kala-altar.
#define CONTACT_NPC                                       0xB540      // NPC와 접촉을 할때
#define SKILL_UP_EFFECT                                   0xB550      // skill up effect 발동 시
#define SCP_FIRE_FX_BROADCAST		                      0xB560      // Fire a Effect
#define MSG_SET_ZONE_SETTINGS_ID                          0xB570		// zone의 설정 사항을 client에 전달한다.
#define MSG_CHANGE_TRIMURITI_ID                           0xB580		// clan을 변경을 client에 알린다.
#define MSG_CHANGE_CLAN_ID                                0xB585
#define MSG_APPLY_SIEGE_ID                                0xB590		// 공성 신청을 한다.
#define MSG_TRIGGER_EVENT_ID                              0xB600		// 특정 event를 실행시킨다.
#define	MSG_STATE_OF_THE_SIEGE_ID						  0xB610		// 공성 상징물 점령 상태
#define	MSG_PET_COMMAND_ID                                0xB620		// 팻에게 명령을 내림
#define MSG_SIEGE_ENTRY_ID                                0xB630
#define MSG_CHECK_SIEGE_ENTRY_ID                          0xB640
#define CONFIRM_SIEGE_ENTRY_ID                            0xB650
#define MSG_FIX_DATE_OF_SIEGE_ID                          0Xb660
#define MSG_GIVEUP_SIEGE_ID                               0Xb670

typedef struct _S_REQUEST
{	_MSG
} S_REQUEST, * PS_REQUEST;

typedef struct _S_RESULT
{	_MSG
	int                                              nResult;      // Result Field
} S_RESULT, * PS_RESULT;

typedef struct _S_TNITEM_DATA
{
	DWORD                                             dwKeyID;      // Item handle
	int                                               iID;          // Item ID
	short                                             snDur;        // Item 내구성
	BYTE                                              nPack;        // Item 중첩개수
	BYTE											  byDummy;
	WORD                                              wrgMaterial[10];// 추가되는 보조재료

} S_TNITEM_DATA, * PS_TNITEM_DATA;


typedef struct _S_TNSKILL_DATA
{
	short               								snID;          // Skill ID
	BYTE                								byLevel;      // Skill Level
	BYTE												byDummy;

} S_TNSKILL_DATA, * PS_TNSKILL_DATA;


typedef struct _S_TNCHAKRA
{
	short                                             snMuscle;     // 근육 차크라
	short                                             snNerves;     // 신경 차크라
	short                                             snHeart;      // 심장 차크라
	short                                             snMind;       // 정신 차크라

} S_TNCHAKRA, * PS_TNCHAKRA;


typedef struct _S_TNRESIST
{
	short                                             snFire;       // fire 저항
	short                                             snCold;       // cold 저항
	short                                             snLightning;  // lightning 저항
	short                                             snPoison;     // poison 저항

} S_TNRESIST, * PS_TNRESIST;


typedef struct _S_TNDAMAGE
{
	int                                           iMin;        // 최소
	int                                           iMax;        // 최대
	int											  iFire ;
	int											  iCold ;
	int											  iLightning ;
	int											  iPoison ;

} S_TNDAMAGE, * PS_TNDAMAGE;


typedef struct _S_TNTARGET_DATA
{
	byte                                            byRes ; // result; 0,1: 성공, 2:실패
	byte                                            byDummy1 ;
	short											snKeyID ;
	int												iDamage ;
	int												iHP ;
	__int64                                         iAffection ;
} S_TNTARGET_DATA, *PS_TNTARGET_DATA ;

struct S_PARTY
{
 	  char		Name[SZNAME_LENGTH];

      BYTE		byLevel;
	  BYTE		byRootingMode;
	  short		snDummy;

	  int		nID;
	  int		nMaxHP;
	  int		nCurHP;
	  int		nMaxTP;
	  int		nCurTP;
	  __int64	nAffections;
};


typedef struct _S_GUILD_SKILL
{
	DWORD		dwIndex;      // 스킬인덱스
	BYTE		byLevel;      // 현재 스킬레벨
	BYTE		byDummy;
	short		snDummy;

} S_GUILD_SKILL, * PS_GUILD_SKILL;


typedef struct _S_GUILD_MEMBER_INFO
{
	char		 szName[SZNAME_LENGTH];   // 길드원 캐릭터의 이름
	BYTE         byTrimuritiClass;// 캐릭터의 주신계급                                     
	BYTE         bySpecialName;// 캐릭터의 특수칭호                                     
	BYTE         byGuildAuthority;// 길드내의 지위                                     
	BYTE         byTribe;      // 캐릭터의 종족                                     
				 
	BYTE         byCastClass;  // 캐릭터의 카스트 계급                                     
	BYTE         byCastGrade;  // 캐릭터의 카스트 등급                                     
	BYTE         byConnect;    // 캐릭터의 접속여부                                     
	BYTE		 byDummy;
	int          nContribution;// 캐릭터의 길드내 공헌도                                     

} S_GUILD_MEMBER_INFO, * PS_GUILD_MEMBER_INFO;

typedef struct _S_QUEST_HISTORY_INFO
{
	BYTE        byIndex;      // 플래그 인덱스                                      
	BYTE        byValue;      // 플래스 값                                      
	short		snDummy;
} S_QUEST_HISTORY_INFO, * PS_QUEST_HISTORY_INFO;


typedef struct _S_KEY_ID
{
	DWORD                                             dwKeyID;      

} S_KEY_ID, * PS_KEY_ID;

typedef struct _S_USER_REPORT_LIST
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // 처리상황
	char                                              szReport[512];

} S_USER_REPORT_LIST, * PS_USER_REPORT_LIST;


typedef struct _S_REPORT_LIST
{
	DWORD                                           	dwIndex;      // 접수시 발급되는 접수번호
	char                                            	szCharName[SZNAME_LENGTH];
	BYTE                                            	byWorld;   
	BYTE                                            	byProceed;    // 처리상황
	short												snDummy;
	DWORD                                           	dwTime;       

	char                                            	szReport[512];
	char                                            	szNote[256];  // 비고

} S_REPORT_LIST, * PS_REPORT_LIST;


typedef struct _S_SKILLINFO
{
	BYTE                                            	byType;       // Skill의 종류
	BYTE                                            	byLevel;      // Skill Level
	short												snDummy;
	DWORD                                           	dwIndex;      // Skill Index

} S_SKILLINFO, * PS_SKILLINFO;

//
//typedef struct _S_ADDRESS_MEMBER_INFO
//{
//	char                                              szName[SZNAME_LENGTH];   // 주소록 캐릭터의 이름
//	BYTE                                              byTrimuriti;  // 캐릭터의 주신
//	BYTE                                              byTribe;      // 캐릭터의 종족
//	BYTE                                              byCastClass;  // 캐릭터의 카스트 등급
//	BYTE                                              byCastGrade;  // 캐릭터의 카스트 계급
//	WORD                                              wServerID;    // 케릭터가 위치한 서버ID
//
//} S_ADDRESS_MEMBER_INFO, * PS_ADDRESS_MEMBER_INFO;
//
//struct S_SCP_RESP_RESULT
//{
//	_MSG;
//	int		nResult;
//};



// CSP_REQ_MOVE_ZONE_SERVER : 0x1003
typedef struct _S_CSP_REQ_MOVE_ZONE_SERVER
{
	_MSG;
    char    AccountName[ACCOUNTNAME_LENGTH];	//	계정 ID
	char    AccountPass[ACCOUNTPASS_LENGTH];	//	계정 비번
	char    szCharName[SZNAME_LENGTH];						// Character Name
	short	snVersion[4];
	DWORD	dwEvent;
	DWORD	dwDummy1;
	DWORD	dwDummy2;
} S_CSP_REQ_MOVE_ZONE_SERVER, * PS_CSP_REQ_MOVE_ZONE_SERVER;


// SCP_RESP_MOVE_ZONE_SERVER : 0x9003
typedef struct _S_SCP_RESP_MOVE_ZONE_SERVER
{
	_MSG;
	int    nResult;     // Result Field
} S_SCP_RESP_MOVE_ZONE_SERVER, * PS_SCP_RESP_MOVE_ZONE_SERVER;


// CSP_REQ_CHAR_LIST : 0x1011
typedef struct _S_CSP_REQ_CHAR_LIST
{
	_MSG;
} S_CSP_REQ_CHAR_LIST, * PS_CSP_REQ_CHAR_LIST;


// SCP_RESP_CHAR_LIST : 0x9011
typedef struct _S_SCP_RESP_CHAR_LIST
{
	_MSG;
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];    

} S_SCP_RESP_CHAR_LIST, * PS_SCP_RESP_CHAR_LIST;


// CSP_REQ_CHAR_CREATE : 0x1012
typedef struct _S_CSP_REQ_CHAR_CREATE
{
	_MSG;
	char    szCharName[SZNAME_LENGTH];                                        
	short   snTribe;   
	short	snDummy;

	BYTE    byTrimuriti;                                          
	BYTE    byFaceType;                                           
	BYTE	byHeadType;										
	BYTE	byDummy;										

	BYTE   	byChakraMuscle;
	BYTE   	byChakraNerve;
	BYTE   	byChakraHeart;
	BYTE	byChakraSoul; 

} S_CSP_REQ_CHAR_CREATE, * PS_CSP_REQ_CHAR_CREATE;


// SCP_RESP_CHAR_CREATE : 0x9012
typedef struct _S_SCP_RESP_CHAR_CREATE
{
	_MSG;
	BYTE    byResult;     // Result Field

} S_SCP_RESP_CHAR_CREATE, * PS_SCP_RESP_CHAR_CREATE;


// CSP_REQ_CHAR_REMOVE : 0x1013
typedef struct _S_CSP_REQ_CHAR_REMOVE
{
	_MSG;
	char    szCharName[SZNAME_LENGTH];
	int		ssn1;
	int		ssn2;

} S_CSP_REQ_CHAR_REMOVE, * PS_CSP_REQ_CHAR_REMOVE;


// SCP_RESP_CHAR_REMOVE : 0x9013
typedef struct _S_SCP_RESP_CHAR_REMOVE
{
	_MSG;
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CHAR_REMOVE, * PS_SCP_RESP_CHAR_REMOVE;


// CSP_REQ_ZONE_CONNECT : 0x1014
typedef struct _S_CSP_REQ_CHAR_SELECT
{
	_MSG;
	char												szCharName[SZNAME_LENGTH];
	BYTE												byCastClass;  
	BYTE												byCastGrade;  
	BYTE												byConnType;   // 접속위치
	BYTE												byDummy;

} S_CSP_REQ_CHAR_SELECT, * PS_CSP_REQ_CHAR_SELECT;


// SCP_RESP_ZONE_CONNECT : 0x9014
typedef struct _S_SCP_RESP_CHAR_SELECT
{
	_MSG;
	BYTE												byResult;     // Result Field
	BYTE												byZone;    // Server ID
	short												snDummy;
} S_SCP_RESP_CHAR_SELECT, * PS_SCP_RESP_CHAR_SELECT;


typedef struct _MSG_PET_COMMAND
{
	_MSG ;
	int			iAction ; // 1:attack 
	int			iParam1 ; // target
	int			iParam2 ;
} MSG_PET_COMMAND ;


typedef struct _MSG_FIX_DATE_OF_SIEGE
{
	_MSG ;
	BYTE		byWhat ; // 0: 서버에게 공성 날짜를 요청할때, 1:결정된 공성 날짜를 서버에 알려줄때
	BYTE		byDate  ; //공성 날짜(0, 1~n), 0:결정된날짜가 없을경우, 0 초과:결정된 날짜 순서번호
	short		sDummy ;
} MSG_FIX_DATE_OF_SIEGE ;



typedef struct _MSG_CHECK_SIEGE_ENTRY
{
	_MSG ;
	BYTE		byClanSlot ; // leader(clan) slot 
	BYTE		byPage ; // 0~4
} MSG_CHECK_SIEGE_ENTRY ;


typedef struct _MSG_SIEGE_ENTRY
{
	_MSG ;
	BYTE		byDate  ; //공성 날짜
	BYTE		byClanSlot ; // 0:수성, 1:공성1, 2:공성2, 3:공성3
	BYTE		byPage ; // 0~4
	BYTE		byDummy ;
	int			irgGuildID[8] ; // 0 이면 비어 있는 것이다.
	DWORD		dwrgGuildMark[8] ; // 0 이면 비어 있는 것이다.
	char		szrgGuildName[8][SZGUILD_LENGTH] ; 
} MSG_SIEGE_ENTRY ;


typedef struct _MSG_STATE_OF_THE_SIEGE
{
	_MSG ;
	int			irgClan[11] ; // symbol에 대한 각 clan의 점령 상태
} MSG_STATE_OF_THE_SIEGE ;


typedef struct _MSG_SET_ZONE_SETTINGS // 서버에서 일방적으로 보내는 메시지 타입
{
	_MSG ;
	short		snSiege ; // 0은 공성전 종료, 1은 공성전 중(시작)
	short		snDummy ; // 
	int			iCastle ; // 수성측 길드 ID
} MSG_SET_ZONE_SETTINGS ;


typedef struct _MSG_CHANGE_CLAN
{
	_MSG;
	short		snKeyID;
	BYTE		byClan; // clan 번호
	BYTE		byDummy;
} MSG_CHANGE_CLAN;


typedef struct _MSG_CHANGE_TRIMURITI // 서버에서 일방적으로 보내는 메시지 타입
{
	_MSG ;
	short		snKeyID ; // 캐릭터 ID
	BYTE		byTrimuriti ; // 변경될 주신
	BYTE		byDummy ;
} MSG_CHANGE_TRIMURITI ;


// client가 server로 요청, server는 trial이후에 결과를 reply해준다.
typedef struct _MSG_APPLY_SIEGE
{
	_MSG ;
	BYTE		byClanSlot ; // leader(clan) slot 
	BYTE		byExpandSlot ; // 하위 slot
	short		snResult ; // 신청 결과 값
	//int			nGuildID ; // 신청한 guild ID
} MSG_APPLY_SIEGE ;


// client가 server로 요청, server는 trial이후에 결과를 reply해준다.
typedef struct _MSG_GIVEUP_SIEGE
{
	_MSG ;
	short		snResult ; // 신청 결과 값
	short		snDummy;
} MSG_GIVEUP_SIEGE ;


typedef struct _CONFIRM_SIEGE_ENTRY
{
	_MSG ;
} CONFIRM_SIEGE_ENTRY ;


typedef struct _MSG_TRIGGER_EVENT
{
	_MSG ;
	int			iNPC ;
	int			iSelected ;
} MSG_TRIGGER_EVENT ;


typedef struct _MSG_ITEM
{
	_MSG ;
	short                                           	snUserKeyID ;
	short                                           	snWarpID ;		//	고급형 이동의 푸스티카 사용시 이동장소ID
	BYTE												byType ;		// use/info
	BYTE												byPlace ;		// equipment, bag1~~ , ...
	BYTE												byIndex ;
	BYTE												byResult ;
	STRUCT_ITEM											kItem ;			// 중첩개수가 0이면 삭제해준다.
} MSG_ITEM ;


typedef struct _MSG_SKILL_UP_EFFECT
{
	_MSG ;
	short                                              snID ;
	byte                                               byLevel ; // 현재의 level
	byte                                               byLevelPlus ; // 상승한 수치, 이 수치가 0보다 크면, level 숫자를 파란색으로 표기
	// 따라서 byLevel + byLevelPlus 값이 현재 스킬 level
} MSG_SKILL_UP_EFFECT ;


typedef struct _MSG_REGISTER_KALA_CORE
{
	_MSG ;
	short												snID ; // 칼라제단 ID
	short												sDummy ;
} MSG_REGISTER_KALA_CORE ;


typedef struct _MSG_CONTACT_NPC
{
	_MSG ;
	short                                              snNPCID ;
} MSG_CONTACT_NPC ;

// CSP_REQ_LEARN_SKILL : 0x3210
typedef struct _S_CSP_REQ_LEARN_SKILL
{
	_MSG;
	short												snID;          // Skill ID
	short												snDummy;

} S_CSP_REQ_LEARN_SKILL, * PS_CSP_REQ_LEARN_SKILL;


// SCP_RESP_LEARN_SKILL : 0xB210
typedef struct _S_SCP_RESP_LEARN_SKILL
{
	_MSG;
	BYTE												byRes;        // Result
	BYTE												byDummy;
	short												snDummy;
	S_TNSKILL_DATA										kSkill;       // level up될 skill 정보

} S_SCP_RESP_LEARN_SKILL, * PS_SCP_RESP_LEARN_SKILL;




// SCP_CAST_SKILL_BROADCAST : 0x3240
typedef struct _S_CSP_CAST_UNIT_SKILL
{
	_MSG ;	
	unsigned short									  snSkillID ;       // cast한 skill ID
	short                                             snCasterKeyID;// Caster handle
	int                                               iSkillIcon ; // bit vector, 관련된 스킬 ICON   <===
	DWORD                                             dwFireHitGapTime ; // 발사하고 적중할 때까지 걸린 시간  <===
	DWORD                                             dwEndTime ;  // 스킬 시전이 종료되는 시간
	DWORD                                             dwDurationTime ; // 지속 시간으로 이 시간에 적용이 끝난다.
	DWORD                                             dwCoolDownTime ; // 이 시간에 cool-down이 완료된다.
	short                                             snCasterX;    // Caster의 현재 x 좌표
	short                                             snCasterZ;    // Caster의 현재 y 좌표
	int                                               iCasterHP;    // Caster의 현 HP
	int                                               iCasterTP;    // Caster의 현 TP
	__int64                                           iCasterAffections ; // Caster에게 현재 걸려있는 affection
	short                                             snMapX;       // Target map x 좌표(ground), 필수 사항
	short                                             snMapZ;       // Target map y 좌표(ground), 필수 사항
	short                                             snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:장애물충돌 ...)
	short                                             snPackCount ;  // 소모된 item의 현재 남은 개수(화살의 개수)]
	byte                                              bySkillLevel ;
	byte                                              byDummy ;
	short                                             sDummy2 ;
	S_TNTARGET_DATA                                   kTarget ;

} S_CSP_CAST_UNIT_SKILL, * PS_CSP_CAST_UNIT_SKILL;



// CSP_REQ_CAST_SKILL : 0x3250
typedef struct _S_CSP_CAST_AREA_SKILL
{
	_MSG;
	unsigned short									  snSkillID ;       // cast한 skill ID	
	short                                             snCasterKeyID;// Caster handle
	int                                               iSkillIcon ; // bit vector, 관련된 스킬 ICON   <===
	DWORD                                             dwFireHitGapTime ; // 발사하고 적중할 때까지 걸린 시간   <===
	DWORD                                             dwEndTime ;  // 스킬 시전이 종료되는 시간
	DWORD                                             dwDurationTime ; // 지속 시간으로 이 시간에 적용이 끝난다.
	DWORD                                             dwCoolDownTime ; // 이 시간에 cool-down이 완료된다.	
	short                                             snCasterX;    // Caster의 현재 x 좌표
	short                                             snCasterZ;    // Caster의 현재 y 좌표
	int                                               iCasterHP;    // Caster의 현 HP
	int                                               iCasterTP;    // Caster의 현 TP
	__int64                                           iCasterAffections ; // Caster에게 현재 걸려있는 affection
	short                                             snMapX;       // Target map x 좌표(ground), 필수 사항
	short                                             snMapZ;       // Target map y 좌표(ground), 필수 사항
	short                                             snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:장애물충돌 ...)
	short                                             snPackCount ;  // 소모된 item의 현재 남은 개수(화살의 개수)
	byte                                              bySkillLevel ;
	byte                                              byDummy ;
	short                                             sDummy2 ;
	S_TNTARGET_DATA                                   krgTarget[TN_MAX_TARGET_COUNT] ;

} S_CSP_CAST_AREA_SKILL, *PS_CSP_CAST_AREA_SKILL ;



//CSP_DEBUFFER_SKILL // 단순히 client상에 표시된 skill icon을 없애기 위한 용도이다. 실제 성능을 빼는 것은 이미 적용되고 있다.
typedef struct _S_CSP_DEBUFFER_SKILL
{
	_MSG ;
	short                                             snSkillID ;
	short                                             snDummy ;
	__int64                                           iCasterAffections ; // Caster에게 현재 걸려있는 affection, // 이것이 따로 필요한가?
} S_CSP_DEBUFFER_SKILL, *PS_CSP_DEBUFFER_SKILL ;



struct MSG_TOGGLE_BUTTON
{
	_MSG;
	BYTE											byButton ; // 누른 버튼, 1:PK_btn, 2:assist btn
	BYTE											byValue ; // 현재 상태값 0(off)/1(on)
	short											snDummy ; 
} ;


struct MSG_CHANGE_TARGET
{
	_MSG ;
	short											snTarget ;
	short											snDummy ;
} ;


// CSP_REQ_CHAR_ACT : 0x3300
typedef struct _S_CSP_REQ_CHAR_ACT
{
	_MSG;
	BYTE                                              byAct;        // 취하려는 행동

} S_CSP_REQ_CHAR_ACT, * PS_CSP_REQ_CHAR_ACT;


// SCP_RESP_CHAR_ACT : 0xB300
typedef struct _S_SCP_RESP_CHAR_ACT
{
	_MSG;
} S_SCP_RESP_CHAR_ACT, * PS_SCP_RESP_CHAR_ACT;


// CSP_CHAR_ACT_BROADCAST : 0x3310
typedef struct _S_CSP_CHAR_ACT_BROADCAST
{
	_MSG;
} S_CSP_CHAR_ACT_BROADCAST, * PS_CSP_CHAR_ACT_BROADCAST;


// SCP_CHAR_ACT_BROADCAST : 0xB310
typedef struct _S_SCP_CHAR_ACT_BROADCAST
{
	_MSG;
	DWORD                                             dwKeyID;      // PC handle
	BYTE                                              byAct;        // 취하려는 행동

} S_SCP_CHAR_ACT_BROADCAST, * PS_SCP_CHAR_ACT_BROADCAST;


// CSP_REQ_UPDATE_UI : 0x3500
typedef struct _S_CSP_REQ_UPDATE_UI
{
	_MSG;
} S_CSP_REQ_UPDATE_UI, * PS_CSP_REQ_UPDATE_UI;


// SCP_RESP_UPDATE_UI : 0xB500
typedef struct _S_SCP_RESP_UPDATE_UI
{
	_MSG;
	short								snX;          // 현재 x 좌표
	short                              	snZ;          // 현재 y 좌표   
	char								byteSpeed1;											
	BYTE                               	byLevel ;      // 현 Level
	BYTE                                byCaste ;      // Caste 계급
	BYTE                                byRangePlus ; // 원거리 공격 사거리 증가 수치, 보통은 0, 사거리 증가 스킬이 걸렸을 경우에는 0 초과 <===
	char								byteSpeed2;	
	BYTE                                bySaveTPCost ; // TP cost 절약 수치 <===
	BYTE                                byClass1 ;     // 전직 단계
	BYTE								byClass2 ;     // 세부 직업
	BYTE                                byDummy1 ;     //
	BYTE                                byDummy2 ;     //
	char								byteAS1;	
	char								byteSpeed3;	
	//int                               iMoveSpeed ;   // 현 MoveSpeed 
	//int                               iAttackSpeed ; // 현 일반 무기 기반 공격 속도, skill에는 적용이 안된다. <===
	short                               snAttackSpeedCorrect ; // 무기 기반 속도 증가 수치( 이 수치만큼을 더 빠르게) <===
	short                               snCastSpeedCorrect ; // 무기 기반이 아닌 skill 속도 증가 수치 <===
	short                               snDDup ;		// DD type skill의 공격력 up을 표기한다. <===
	short								snKarma ;     //<===
	int                                 iBramanPoint ; // 현 Braman point	
	int                                 iPietyPoint ; // 현 신앙심 point <===
	int                                 iTitle ;       // Title
	int                                 iMaxPrana ;    // 최대 Prana
	int                                 iPrana ;       // 현 Prana
	S_TNCHAKRA                          krgChakra[2] ; // 0:base chakra, 1:changed chakra
	short                               snCPRemaining ;// 남은 Chakra Point
	short                               snSPRemaining ;// 남은 Skill Point
	int                                 iHP ;          // 현 HP
	int                                 iMaxHP ;       // 최대 HP
	int                                 iHPRecovery ;  // HP회복량/초
	int                                 iTP ;          // 현 TP
	int                                 iMaxTP ;       // 최대 TP
	int                                 iTPRecovery ;  // TP회복량/초
	short                               snAC ;         // AC
	short                               snAttackRate ; // Attack Rate
	short                               snDodgeRate ;  // Dodge Rate
	short                               snCasteSPRemaining ;	// <===
	char								byteSpeedCorrection;	
	char								byteAS2;	
	char								byteSpeedParity;	
	char								byteAS3;	
	S_TNRESIST                          kResist ;      // 저항
	S_TNDAMAGE                          kDamage ;		// damage
	int									iGold ;       // 돈
	int                                 iSkillIcon ; // bit vector, 관련된 스킬 ICON  <===
	__int64                             iAffections ;  // <===
	char								byteAS4;	
	char								byteParity;
	short								snDummy;
} S_SCP_RESP_UPDATE_UI, * PS_SCP_RESP_UPDATE_UI;


// CSP_REQ_UPDATE_STATUS : 0x3501
typedef struct _S_CSP_REQ_UPDATE_STATUS
{
	_MSG;
	short                                             snKeyID ;		// who
} S_CSP_REQ_UPDATE_STATUS, * PS_CSP_REQ_UPDATE_STATUS;


// SCP_RESP_UPDATE_STATUS : 0xB501
typedef struct _S_SCP_RESP_UPDATE_STATUS
{
	_MSG;
	short                                             snKeyID ;		// who
	short                                             snKarma ;
	int                                               iHP;          // 현 HP
	int                                               iTP;          // 현 TP
	int                                               iPrana;       // 현 Prana
	__int64                                           iAffections ; // 현재 걸려있는 affection
	int                                               iSkillIcon ; // bit vector, 관련된 스킬 ICON <===
	int                                               iPietyPoint ; // 현 신앙심 point <===
	int                                               iMoveSpeed ;   // 현 MoveSpeed <===
	int                                               iAttackSpeed ; // 현 일반 무기 기반 공격 속도, skill에는 적용이 안된다. <===
	short                                             snAttackSpeedCorrect ; // 무기 기반 속도 증가 수치( 이 수치만큼을 더 빠르게) <===
	short                                             snCastSpeedCorrect ; // 무기 기반이 아닌 skill 속도 증가 수치 <===

} S_SCP_RESP_UPDATE_STATUS, * PS_SCP_RESP_UPDATE_STATUS;


// CSP_LEVEL_UP_BROADCAST : 0x3510
typedef struct _S_CSP_LEVEL_UP_BROADCAST
{
	_MSG;
} S_CSP_LEVEL_UP_BROADCAST, * PS_CSP_LEVEL_UP_BROADCAST;


// SCP_LEVEL_UP_BROADCAST : 0xB510
typedef struct _S_SCP_LEVEL_UP_BROADCAST
{
	_MSG;
	DWORD                                             dwKeyID;      // PC handle
	BYTE                                              byLevel;      // 현 Level

} S_SCP_LEVEL_UP_BROADCAST, * PS_SCP_LEVEL_UP_BROADCAST;


// SCP_FIRE_EFFECT_BROADCAST : 0xB560
typedef struct _S_SCP_FIRE_FX_BROADCAST
{
	_MSG;
	DWORD                                             dwKeyID ;      // PC handle
	int                                               iFX ;      // 켜야될 FX ID
} S_SCP_FIRE_FX_BROADCAST, * PS_SCP_FIRE_FX_BROADCAST ;



// CSP_REQ_INCREASE_CHAKRA : 0x3520
typedef struct _S_CSP_REQ_INCREASE_CHAKRA
{
	_MSG;
	BYTE                                              byChakra;     // 올리려는 chakra(0:muscle, 1:nerves, 2:heart, 3:mind)

} S_CSP_REQ_INCREASE_CHAKRA, * PS_CSP_REQ_INCREASE_CHAKRA;


// SCP_RESP_INCREASE_CHAKRA : 0xB520
typedef struct _S_SCP_RESP_INCREASE_CHAKRA
{
	_MSG;
} S_SCP_RESP_INCREASE_CHAKRA, * PS_SCP_RESP_INCREASE_CHAKRA;



// SCP_OTHER_CHAR_LOGOUT : 0x9022
typedef struct _S_SCP_RESP_REMOVE_MOB
{
	_MSG;
	int                                             nID;      
	BYTE                                            byResult ;     // client에서 없어지는 이유 - 1:killed, 2:logout, 3:sucide, 5:teleport(out)
	BYTE											byRemoveType ; // 사라지는 연출번호; 0:일반 죽는 애니(or 그냥 사라짐), 1:펑하고 사라짐
	short                                           snTribe ; // 종족 정보, 2000~3000이면 몬스터이다. 100이하이면 PC이다.
	DWORD                                           dwKillerID ;
	char											szName[SZNAME_LENGTH] ; // 캐릭터명 정보
} S_SCP_RESP_REMOVE_MOB, * PS_SCP_RESP_REMOVE_MOB;


// CSP_REQ_EXIT_ZONE_SERVER : 0x1015
typedef struct _S_CSP_REQ_EXIT_ZONE_SERVER
{

} S_CSP_REQ_EXIT_ZONE_SERVER, * PS_CSP_REQ_EXIT_ZONE_SERVER;


// SCP_RESP_EXIT_ZONE_SERVER : 0x9015
typedef struct _S_SCP_RESP_EXIT_ZONE_SERVER
{
	BYTE                                              byWorldCount; // World Server Count Field

} S_SCP_RESP_EXIT_ZONE_SERVER, * PS_SCP_RESP_EXIT_ZONE_SERVER;

#define		CSP_REQ_SAVE_POSITION	0x1016
//	S_REQUEST 를 이용한다.
#define		SCP_RESP_SAVE_POSITION	0x9016
//	S_RESULT 를 이용한다.


// CSP_REQ_CHAR_LOGOUT : 0x1021
typedef struct _S_CSP_REQ_CHAR_LOGOUT
{

} S_CSP_REQ_CHAR_LOGOUT, * PS_CSP_REQ_CHAR_LOGOUT;


// SCP_RESP_CHAR_LOGOUT : 0x9021
typedef struct _S_SCP_RESP_CHAR_LOGOUT
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CHAR_LOGOUT, * PS_SCP_RESP_CHAR_LOGOUT;


// CSP_OTHER_CHAR_LOGOUT : 0x1022
typedef struct _S_CSP_OTHER_CHAR_LOGOUT
{

} S_CSP_OTHER_CHAR_LOGOUT, * PS_CSP_OTHER_CHAR_LOGOUT;




// CSP_OTHER_CHAR_LOGOUT_NOTIFY : 0x1023
typedef struct _S_CSP_OTHER_CHAR_LOGOUT_NOTIFY
{

} S_CSP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_CSP_OTHER_CHAR_LOGOUT_NOTIFY;


// SCP_OTHER_CHAR_LOGOUT_NOTIFY : 0x9023
typedef struct _S_SCP_OTHER_CHAR_LOGOUT_NOTIFY
{
	char                                              	szCharName[SZNAME_LENGTH];
	BYTE                                              	byResult;     // 접속종료 스타일
	BYTE                                              	byRegion;     
	BYTE                                              	byZone;  
	BYTE												byDummy;

} S_SCP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_SCP_OTHER_CHAR_LOGOUT_NOTIFY;


// CSP_INIT_CHAR : 0x1101
typedef struct _S_CSP_REQ_CHAR_INIT
{
	_MSG;
	BYTE        byConnType;   // 접속유형                                      
	BYTE        byConnPos;    // 접속위치                                      
	WORD        wPortalID;    // 접속포탈ID                                      
	char        szCharName[SZNAME_LENGTH];
	char		szTargetName[SZNAME_LENGTH];

} S_CSP_REQ_CHAR_INIT, * PS_CSP_REQ_CHAR_INIT;


// SCP_INIT_CHAR : 0x9101
typedef struct _S_SCP_RESP_CHAR_INIT
{
	_MSG;
	BYTE					byResult;		// 초기화 결과
	BYTE					byIsDead;		//	0:살아있음, 1:죽어있음
	short					snBagIndex;

    DWORD                   dwGameTime ;
	DWORD					dwKeyID;
	short					snX;
	short					snZ;

	BYTE					bySkill[MAX_SKILL];
	BYTE					byQuest[MAX_EVENT_FLAG];
	STRUCT_ITEM				Inven[72];
	STRUCT_ITEM				Equip[MAX_EQUIP];
	//STRUCT_MOB			Mob;
	STRUCT_ITEM				Cargo[MAX_CARGO];
	int						nCargoMoney;
	int						nGuildID;
	DWORD					dwTimeStamp[10];

	BYTE					byClan ;
	BYTE					byDummy2 ;
	short					snDummy ;
	DWORD					dwEvent;
	DWORD					dwDummy;

	//int Handle;
	// High word : characterID,
	// Low  word : High Byte:Type(0,1,2) Low Byte:Position(0,1,2)
	//
} S_SCP_RESP_CHAR_INIT, * PS_SCP_RESP_CHAR_INIT;


// CSP_REQ_CHAR_HISTORY : 0x1108
typedef struct _S_CSP_REQ_CHAR_HISTORY
{

} S_CSP_REQ_CHAR_HISTORY, * PS_CSP_REQ_CHAR_HISTORY;


// SCP_RESP_CHAR_HISTORY : 0x9108
typedef struct _S_SCP_RESP_CHAR_HISTORY
{
	DWORD												dwStartTime;  // 히스토리 발생 시간
	WORD												wType;        // 히스토리 종류
	short												snDummy;
	char												szContent[SZNAME_LENGTH];// 히스토리 내용

} S_SCP_RESP_CHAR_HISTORY, * PS_SCP_RESP_CHAR_HISTORY;


// CSP_INIT_EQUIPMENT : 0x1109
typedef struct _S_CSP_INIT_EQUIPMENT
{

} S_CSP_INIT_EQUIPMENT, * PS_CSP_INIT_EQUIPMENT;


// SCP_INIT_EQUIPMENT : 0x9109
typedef struct _S_SCP_INIT_EQUIPMENT
{
	BYTE                                              byPlace;      // 아이템의 장착 위치
	DWORD                                             dwKeyID;      // 아이템의 KeyID
	DWORD                                             dwIndex;      // 아이템의 Index
	short                                             snCurDurability;
	short                                             snCount;      // 아이템의 수량(중첩갯수)
	BYTE                                              byX;          // 아이템 장착 X 좌표(0부터 시작)
	BYTE                                              byZ;          // 아이템 장착 Z 좌표(0부터 시작)
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_EQUIPMENT, * PS_SCP_INIT_EQUIPMENT;

//
//// CSP_INIT_MONSTER_NPC : 0x1111
//typedef struct _S_CSP_INIT_MONSTER_NPC
//{
//	DWORD                                             dwKeyID;      
//
//} S_CSP_INIT_MONSTER_NPC, * PS_CSP_INIT_MONSTER_NPC;
//
//
//// SCP_INIT_MONSTER_NPC : 0x9111
//typedef struct _S_SCP_INIT_MONSTER_NPC
//{
//	DWORD                                             dwKeyID;      
//	DWORD                                             dwIndex;      
//	BYTE                                              byType;       
//	BYTE                                              byTrimuriti;  
//	short                                             snX;          
//	short                                             snZ;          
//	BYTE                                              byY;          
//	short                                             snHeight;     
//	DWORD                                             dwStatus;     
//	int                                               nMaxHP;       
//	int                                               nCurHP;       
//	int                                               nSpeed;       
//	short                                             snDestX;      
//	short                                             snDestZ;      
//	BYTE                                              bySize;       // 몬스터의 크기
//
//} S_SCP_INIT_MONSTER_NPC, * PS_SCP_INIT_MONSTER_NPC;


// CSP_INIT_OTHER_CHAR : 0x1112
typedef struct _S_CSP_INIT_OTHER_MOB
{	_MSG
	int		nID;

} S_CSP_INIT_OTHER_MOB, * PS_CSP_INIT_OTHER_MOB;

// SCP_INIT_OTHER_CHAR : 0x9112
typedef struct _S_SCP_INIT_OTHER_MOB
{	_MSG
	int        		nID;                                             
	char       		szName[SZNAME_LENGTH];
	char       		szGuild[SZGUILD_LENGTH];
	char			szAccount[ACCOUNTNAME_LENGTH];
	int				nGuildID;

	BYTE       		byMember;                                            
	BYTE       		byFace;                                              
	BYTE       		byTrimuriti;                                         
	BYTE			byHead;
	
	BYTE       		byCastClass;                                         
	BYTE       		byCastGrade;                                         
	BYTE       		bySpecialName;
	BYTE			byGMStatus;		//	bit flag(0x01:케릭터블럭, 0x02:투명모드, 0x04:채팅블럭, ...)	
          
	BYTE       		byActiveLevel; 
	BYTE       		byActionLevel; 
	BYTE       		byType;                                              
	BYTE       		byDir;			// 방향 정보(0:random, 1~4:동서남북)

	short			snKarma;
	BYTE			byClass1;			//	bit flag 중목중복은 | 연산사용.
	BYTE			byClass2;

	BYTE			byLevel;
	BYTE			byTradeMode;
	BYTE			byPopType ; // pop될 때의 연출 모습, 0 은 기존의 것, 1은 바닥에서 서서히 올라오는 모습
	BYTE			byCollision ; // 충돌 여부, 1이면 충돌이 되어 통과하지 못하는 것이다. 0이면 통과 가능하다.
	
	short      		snHeight ;
	short      		snTargetX ;		// 케릭터의 이동시의 X좌표                                       
	short      		snTargetZ ;		// 케릭터의 이동시의 Z좌표  
	short      		snTribe ;
	
	int        		nMaxHP;                                              
	int        		nCurHP;  
	DWORD      		dwGuildMark; 
	DWORD      		dwActionSkill;                                       
 	DWORD      		dwStatus;                                      
	DWORD      		dwActiveSkill;       
	char			szTrade[SZTRADE_LENGTH];
	STRUCT_ITEMVIEW	Equip[VISUAL_EQUIP];	//	
	__int64			iAffections ;
	byte			byCaste;
	byte			byClan ; // clan 정보값, 공성전일 경우에 참조
	short			snDummy;
	DWORD			dwEvent;
	DWORD			dwDummy;
	
} S_SCP_INIT_OTHER_MOB, * PS_SCP_INIT_OTHER_MOB;


// CSP_INIT_ITEM : 0x1121
typedef struct _S_CSP_INIT_ITEM
{
	DWORD                                             dwKeyID;      

} S_CSP_INIT_ITEM, * PS_CSP_INIT_ITEM;


// SCP_INIT_ITEM : 0x9121
typedef struct _S_SCP_INIT_ITEM
{
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	BYTE                                              byPlace;      
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_ITEM, * PS_SCP_INIT_ITEM;

#define CSP_REQ_INIT_REGEN_CHAR                           0x1131      // 캐릭터 리젠 초기화 요청
#define SCP_RESP_INIT_REGEN_CHAR                          0x9131      // 인벤토리내 아이템 위치 저장 응답 메세지
// CSP_REQ_INIT_REGEN_CHAR : 0x1131
typedef struct _S_CSP_REQ_INIT_REGEN_CHAR
{	_MSG
	BYTE                                              byConnType;		//	REGEN_TYPE_CENTER(1), REGEN_TYPE_SAVE(2)
} S_CSP_REQ_INIT_REGEN_CHAR, * PS_CSP_REQ_INIT_REGEN_CHAR;
// SCP_RESP_INIT_REGEN_CHAR : 0x9131
typedef struct _S_SCP_RESP_INIT_REGEN_CHAR
{	_MSG

	BYTE       	byZone;			// 케릭터의 Zone 위치                   //	REGEN_TYPE_SAVE시 태어날 지역의 ZoneID	                    
	BYTE       	byWhether;
	short      	snX;                                                 
	short      	snZ;                                                 
 	short      	snDegree;    

	DWORD      	dwGameTime;                                             
	int        	nCurHP;			// 케릭터 HP의 현재값                                       
} S_SCP_RESP_INIT_REGEN_CHAR, * PS_SCP_RESP_INIT_REGEN_CHAR;

#define _MSG_TrimuritySelect							0x1141			// 케릭터 주신선택
struct MSG_TrimuritySelect
{	_MSG
	char		CharName[SZNAME_LENGTH];
	DWORD		dwMoney;
	BYTE		byTrimuriti;	//	케릭터의 주신선택
	BYTE		byType;			//	0:조회, 1:실행
	int			nBrahmaCount;
	int			nVishnuCount;
	int			nSivaCount;
};
#define	_MSG_TrimurityPoint								0x1142
struct MSG_TrimurityPoint
{	_MSG
	int			nBramanPoint;
	DWORD		dwMoney;
};


// CSP_INIT_WORLD_USER_COUNT : 0x1161

typedef struct _S_CSP_INIT_WORLD_USER_COUNT
{

} S_CSP_INIT_WORLD_USER_COUNT, * PS_CSP_INIT_WORLD_USER_COUNT;


// SCP_INIT_WORLD_USER_COUNT : 0x9161
typedef struct _S_SCP_INIT_WORLD_USER_COUNT
{
	short                                             snUser[20];   

} S_SCP_INIT_WORLD_USER_COUNT, * PS_SCP_INIT_WORLD_USER_COUNT;


// CSP_REQ_CHAR_MOVE : 0x1201
typedef struct _S_CSP_REQ_CHAR_MOVE
{
	BYTE                                              byDir;        // 이동상태 및 이동방향 정보
	short                                             snDegree;     
	DWORD                                             dwTickCount;  
	WORD                                              wSeqNum;      // 이동패킷 Sequence Number

} S_CSP_REQ_CHAR_MOVE, * PS_CSP_REQ_CHAR_MOVE;


// SCP_RESP_CHAR_MOVE : 0x9201
typedef struct _S_SCP_RESP_CHAR_MOVE
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // 케릭터의 X좌표
	short                                             snZ;          // 케릭터의 Z좌표
	BYTE                                              byY;          // 케릭터의 층 높이
	short                                             snHeight;     // 케릭터의 단 높이

} S_SCP_RESP_CHAR_MOVE, * PS_SCP_RESP_CHAR_MOVE;


// CSP_OTHER_CHAR_MOVE : 0x1202
typedef struct _S_CSP_OTHER_CHAR_MOVE
{

} S_CSP_OTHER_CHAR_MOVE, * PS_CSP_OTHER_CHAR_MOVE;


// SCP_OTHER_CHAR_MOVE : 0x9202
typedef struct _S_SCP_OTHER_CHAR_MOVE
{
	DWORD                                             dwKeyID;      // character KeyID
	BYTE                                              byDir;        // 캐릭터 이동상태, 방향 정보
	short                                             snDegree;     // 케릭터의 이동 각도 정보
	short                                             snMovingSpeed;// 100초당 이동가능 Cell 수
	short                                             snX;          // 케릭터의 X좌표
	short                                             snZ;          // 케릭터의 Z좌표
	BYTE                                              byY;          // 케릭터의 층 높이
	short                                             snHeight;     // 케릭터의 단 높이

} S_SCP_OTHER_CHAR_MOVE, * PS_SCP_OTHER_CHAR_MOVE;

#define CSP_REQ_ITEM_MOVE									0x1203      // 아이템 이동 결과
#define SCP_RESP_ITEM_MOVE									0x9203      // 아이템 이동 결과
// CSP_REQ_ITEM_MOVE : 0x1203
typedef struct _S_CSP_REQ_ITEM_MOVE
{	_MSG
	BYTE			byFromPlace;	// 아이템이 원래 있던 위치 : 0 맵, 1 인벤, 2 장착, 3 창고, 11 아쉬람창고										
	BYTE			byToPlace;		// 아이템을 이동시킬 대상	
	short			snDummy;
	short			snFromIndex;	// Index 번호(인벤토리상의 Index)										
	short			snToIndex;		// Index 번호(인벤토리상의 Index)										
} S_CSP_REQ_ITEM_MOVE, * PS_CSP_REQ_ITEM_MOVE;
// SCP_RESP_ITEM_MOVE : 0x9203
typedef struct _S_SCP_RESP_ITEM_MOVE
{	_MSG
	int				nResult;		// 결과 : 0-성공, 1-실패									
	BYTE			byFromPlace;	// 아이템이 원래 있던 위치 : 1, 인벤, 2, 장착, 3, 창고									
	BYTE			byToPlace;		// 아이템을 이동시킬 대상	
	short			snDummy;
	short			snFromIndex;	// Index 번호(인벤토리상의 Index)									
	short			snToIndex;		// Index 번호(인벤토리상의 Index)									
} S_SCP_RESP_ITEM_MOVE, * PS_SCP_RESP_ITEM_MOVE;

#define SCP_MAP_ITEM_APPEAR									0x9204      // 새로운 아이템의 종류및 위치 정보를 주변캐릭터에게 전송
// SCP_MAP_ITEM_APPEAR : 0x9204
typedef struct _S_SCP_MAP_ITEM_APPEAR
{	_MSG
	int				nItemID;	// Item KeyID									
	DWORD			dwIndex;    // Item Index	
	int				nMobIndex;  // MOB Index
	short			snX;        // Item X좌표									
	short			snZ;        // Item Z좌표									
} S_SCP_MAP_ITEM_APPEAR, * PS_SCP_MAP_ITEM_APPEAR;

#define SCP_MAP_ITEM_DISAPPEAR								0x9205      // 아이템이 사라진 위치를 주변캐릭터에게 전송
// SCP_MAP_ITEM_DISAPPEAR : 0x9205
typedef struct _S_SCP_MAP_ITEM_DISAPPEAR
{	_MSG
	int				nItemID;	// Item KeyID  
	char			szName[SZNAME_LENGTH];		// MOB of name
} S_SCP_MAP_ITEM_DISAPPEAR, * PS_SCP_MAP_ITEM_DISAPPEAR;

#define CSP_REQ_ITEM_DROP									0x1209	  // 아이템을 땅에 버림.
#define SCP_RESP_ITEM_DROP									0x9209	  // 아이템을 땅에 버림.
typedef struct _S_CSP_REQ_ITEM_DROP
{	_MSG
	DWORD			dwMoney;
	BYTE			byFromPlace;	// 아이템이 원래 있던 위치 : 1, 인벤, 2, 장착, 3, 창고				
	BYTE			byIndex;		// Index 번호(인벤토리상의 Index)				
	short			snDummy;				
	short			snX;			// 아이템을 버릴 X좌표				
	short			snZ;			// 아이템을 버릴 Z좌표				
} S_CSP_REQ_ITEM_DROP, *PS_CSP_REQ_ITEM_DROP;
typedef struct _S_SCP_RESP_ITEM_DROP
{	_MSG
	DWORD	dwMoney;
	short	snResult;
	BYTE	byPlace;
	BYTE	byIndex;
	BYTE	byType;
	BYTE	byDummy;
	short	snDummy;
} S_SCP_RESP_ITEM_DROP, *PS_SCP_RESP_ITEM_DROP;

#define CSP_REQ_ITEM_GET									0x120A	  // 아이템을 땅에서 주슴.
#define SCP_RESP_ITEM_GET									0x920A	  // 아이템을 땅에서 주슴.
typedef struct _S_CSP_REQ_ITEM_GET
{	_MSG
	int				nItemID;
} S_CSP_REQ_ITEM_GET, *PS_CSP_REQ_ITEM_GET;
typedef struct _S_SCP_RESP_ITEM_GET
{	_MSG
	int				nResult;
	short			snIndex;
	short			snDummy;
	DWORD			dwMoney;
} S_SCP_RESP_ITEM_GET, *PS_SCP_RESP_ITEM_GET;

#define SCP_RESP_ITEM_SET									0x920B	  // 케릭터 아이템 세팅이 변경됨.
typedef struct _S_SCP_RESP_ITEM_SET
{	_MSG
	BYTE			byType;	//	0:아이템소멸, 1:아이템생성
	BYTE			byPlace;
	BYTE			byIndex;
	BYTE			byDummy;
	STRUCT_ITEM		sitem;
} S_SCP_RESP_ITEM_SET, *PS_SCP_RESP_ITEM_SET;

#define SCP_RESP_EQUIP_SET									0x920C	  // 케릭터 장착 세팅이 변경됨.
typedef struct _S_SCP_RESP_EQUIP_SET
{	_MSG
	int				nID;
	STRUCT_ITEMVIEW	Equip[VISUAL_EQUIP];
} S_SCP_RESP_EQUIP_SET, *PS_SCP_RESP_EQUIP_SET;

#define _MSG_Money_Move										0x1226      // 루피아의 이동을 요청
struct MSG_Money_Move
{	_MSG
	BYTE			byFromPlace;										
	BYTE			byToPlace;
	short			snDummy;
	DWORD			dwMoney;											
	DWORD			dwFromMoney;										// 옮길장소의 루피아(이동성공시사용)
	DWORD			dwToMoney;											// 옮긴장소의 루피아(이동성공시사용)
};

// CSP_MONSTER_MOVE_STEP : 0x1206
typedef struct _S_CSP_MONSTER_MOVE_STEP
{

} S_CSP_MONSTER_MOVE_STEP, * PS_CSP_MONSTER_MOVE_STEP;


// SCP_MONSTER_MOVE_STEP : 0x9206
typedef struct _S_SCP_MONSTER_MOVE_STEP
{
	DWORD                                             dwKeyID;      
	BYTE                                              byDir;        
	int                                               nMoveTime;    

} S_SCP_MONSTER_MOVE_STEP, * PS_SCP_MONSTER_MOVE_STEP;


// CSP_MONSTER_MOVE_NSTEP : 0x1207
typedef struct _S_CSP_MONSTER_MOVE_NSTEP
{

} S_CSP_MONSTER_MOVE_NSTEP, * PS_CSP_MONSTER_MOVE_NSTEP;


// SCP_MONSTER_MOVE_NSTEP : 0x9207
typedef struct _S_SCP_MONSTER_MOVE_NSTEP
{
	DWORD                                             dwKeyID;      
	int                                               nMovingSpeed; 
	short                                             snX;          // 최종 x좌표
	short                                             snZ;          // 최종 z좌표

} S_SCP_MONSTER_MOVE_NSTEP, * PS_SCP_MONSTER_MOVE_NSTEP;


// CSP_MONSTER_MOVE_END : 0x1208
typedef struct _S_CSP_MONSTER_MOVE_END
{

} S_CSP_MONSTER_MOVE_END, * PS_CSP_MONSTER_MOVE_END;


// SCP_MONSTER_MOVE_END : 0x9208
typedef struct _S_SCP_MONSTER_MOVE_END
{
	DWORD                                             dwKeyID;      
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byDir;        

} S_SCP_MONSTER_MOVE_END, * PS_SCP_MONSTER_MOVE_END;

#define	_MSG_Packing									0x1221
struct MSG_Packing
{	_MSG
	BYTE	byType;				//	Packing(1), Unpacking(2)
	BYTE	byResult;			//	성공(0), 실패(1)
	BYTE	byFromPlace;
	BYTE	byFromIndex;
	BYTE	byFromCount;
	BYTE	byToPlace;
	BYTE	byToIndex;
	BYTE	byToCount;
};

//// CSP_REQ_ITEM_USE : 0x1223
//typedef struct _S_CSP_REQ_ITEM_USE
//{
//	DWORD                                             dwKeyID;      // 사용할 아이템의 KeyID
//
//} S_CSP_REQ_ITEM_USE, * PS_CSP_REQ_ITEM_USE;
//
//
//// SCP_RESP_ITEM_USE : 0x9223
//typedef struct _S_SCP_RESP_ITEM_USE
//{
//	BYTE                                              byResult;     // Result Field
//	DWORD                                             dwKeyID;      // 사용한 아이템의 KeyID
//	short                                             snCount;      // 아이템 수량
//	int                                               nCurHP;       // 캐릭터의 현재 HP
//	DWORD                                             dwCurStatus;  // 캐릭터의 상태
//
//} S_SCP_RESP_ITEM_USE, * PS_SCP_RESP_ITEM_USE;


//// CSP_ITEM_USE_BROADCAST : 0x1224
//typedef struct _S_CSP_ITEM_USE_BROADCAST
//{
//
//} S_CSP_ITEM_USE_BROADCAST, * PS_CSP_ITEM_USE_BROADCAST;
//
//
//// SCP_ITEM_USE_BROADCAST : 0x9224
//typedef struct _S_SCP_ITEM_USE_BROADCAST
//{
//	DWORD                                             dwKeyID;      // 아이템을 사용하는 캐릭터의 KeyID
//	DWORD                                             dwIndex;      // 사용한 아이템의 Index
//
//} S_SCP_ITEM_USE_BROADCAST, * PS_SCP_ITEM_USE_BROADCAST;


// CSP_ITEM_REMOVE : 0x1225
typedef struct _S_CSP_ITEM_REMOVE
{

} S_CSP_ITEM_REMOVE, * PS_CSP_ITEM_REMOVE;


// SCP_ITEM_REMOVE : 0x9225
typedef struct _S_SCP_ITEM_REMOVE
{
	DWORD                                             dwKeyID;      // 사라진 아이템의 KeyID
	BYTE                                              byPlace;      // 사라진 아이템의 위치
	short                                             snX;          // 사라진 아이템의 X 좌표
	short                                             snZ;          // 사라진 아이템의 Z 좌표

} S_SCP_ITEM_REMOVE, * PS_SCP_ITEM_REMOVE;


// CSP_REQ_CHAR_MOVE_BROADCAST : 0x1227
typedef struct _S_CSP_REQ_CHAR_MOVE_BROADCAST
{
	BYTE                                              byDir;        // 이동상태
	short                                             snToX;        // 이동시의 종착점 X좌표
	short                                             snToZ;        // 이동시의 종착점 Z좌표

} S_CSP_REQ_CHAR_MOVE_BROADCAST, * PS_CSP_REQ_CHAR_MOVE_BROADCAST;


// SCP_RESP_CHAR_MOVE_BROADCAST : 0x9227
typedef struct _S_SCP_RESP_CHAR_MOVE_BROADCAST
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	BYTE                                              byDir;        // 이동상태
	short                                             snFromX;      // 이동시의 시작점 X좌표
	short                                             snFromZ;      // 이동시의 시작점 Z좌표
	short                                             snToX;        // 이동시의 종착점 X좌표
	short                                             snToZ;        // 이동시의 종착점 Z좌표

} S_SCP_RESP_CHAR_MOVE_BROADCAST, * PS_SCP_RESP_CHAR_MOVE_BROADCAST;

#define CSP_REQ_MOVE_PORTAL                               0x1231      // 포탈을 통한 이동요청을 한다.
#define SCP_RESP_MOVE_PORTAL                              0x9231      // 포탈을 통한 이동요청 결과 전송 응답 메세지
// CSP_REQ_MOVE_PORTAL : 0x1231
typedef struct _S_CSP_REQ_MOVE_PORTAL
{	_MSG
	WORD											  wStartPortalID;	//	현재의 포탈
	WORD                                              wEndPortalID;     //  이동하고자 하는 포탈의 ID
	
} S_CSP_REQ_MOVE_PORTAL, * PS_CSP_REQ_MOVE_PORTAL;
// SCP_RESP_MOVE_PORTAL : 0x9231
typedef struct _S_SCP_RESP_MOVE_PORTAL
{	_MSG
	BYTE        byResult;		// Result Field
	BYTE		byZone;			// Potal zone
	short		snDummy;
	int			nMoney;			// 포탈 이용 후 변경된 돈
} S_SCP_RESP_MOVE_PORTAL, * PS_SCP_RESP_MOVE_PORTAL;

#define _MSG_MoveOtherZone								0x1241		//	지바푸스티카를 이용한 이동시 사용
struct MSG_MoveOtherZone
{	_MSG
	BYTE		byType;								//	const int   CONNECT_TYPE_PUSTICA	=	5;
	BYTE		byDummy;
	short		snPositionID;						//	이동장소 index(type5:위치npc index)
};

// CSP_REQ_ATK_CHAR : 0x1301
typedef struct _S_CSP_REQ_ATK_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격 대상 캐릭터의 KeyID
	DWORD                                             dwItemKeyID;  // 공격에 사용할 아이템 KeyID
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_ATK_CHAR, * PS_CSP_REQ_ATK_CHAR;


// SCP_RESP_ATK_CHAR : 0x9301
typedef struct _S_SCP_RESP_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCount;      // 투척무기일 경우, 잔여수량
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터/Monster의 현재 HP

} S_SCP_RESP_ATK_CHAR, * PS_SCP_RESP_ATK_CHAR;


// CSP_ATK_CHAR_BROADCAST : 0x1302
typedef struct _S_CSP_ATK_CHAR_BROADCAST
{

} S_CSP_ATK_CHAR_BROADCAST, * PS_CSP_ATK_CHAR_BROADCAST;


// SCP_ATK_CHAR_BROADCAST : 0x9302
typedef struct _S_SCP_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwKeyID;      // 공격을 하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;// 공격을 당하는 캐릭터의 KeyID
	BYTE                                              byEquipPart;  // 공격시에 사용하는 아이템을 장착한 부위
	BYTE                                              byResult;     // Result Field
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터의 현재 HP
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCurX;       // 공격자의 현재 X좌표
	short                                             snCurz;       // 공격자의 현재 z좌표

} S_SCP_ATK_CHAR_BROADCAST, * PS_SCP_ATK_CHAR_BROADCAST;


// CSP_REQ_ITEM_EQUIPMENT : 0x1401
typedef struct _S_CSP_REQ_ITEM_EQUIPMENT
{
	DWORD                                             dwKeyID;      // 창착할 아이템 KeyID
	BYTE                                              byEquipPart;  // 아이템 장착부위
	BYTE                                              byX;          // 장착 X 좌표
	BYTE                                              byZ;          // 장착 Z 좌표

} S_CSP_REQ_ITEM_EQUIPMENT, * PS_CSP_REQ_ITEM_EQUIPMENT;


// SCP_RESP_ITEM_EQUIPMENT : 0x9401
typedef struct _S_SCP_RESP_ITEM_EQUIPMENT
{
	BYTE                                              byResult;     // 아이템 장착 요청에 대한 결과 값
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리

} S_SCP_RESP_ITEM_EQUIPMENT, * PS_SCP_RESP_ITEM_EQUIPMENT;


// CSP_ITEM_EQUIPMENT_BROADCAST : 0x1402
typedef struct _S_CSP_ITEM_EQUIPMENT_BROADCAST
{

} S_CSP_ITEM_EQUIPMENT_BROADCAST, * PS_CSP_ITEM_EQUIPMENT_BROADCAST;


// SCP_ITEM_EQUIPMENT_BROADCAST : 0x9402
typedef struct _S_SCP_ITEM_EQUIPMENT_BROADCAST
{
	DWORD                                             dwKeyID;      // 장착 캐릭터 KeyID
	DWORD                                             dwIndex;      // 장착 아이템 인덱스
	BYTE                                              byEquipPart;  // 아이템 장착 부위
	BYTE                                              bySubMaterialCount;

} S_SCP_ITEM_EQUIPMENT_BROADCAST, * PS_SCP_ITEM_EQUIPMENT_BROADCAST;


// CSP_ITEM_ABRASION : 0x1411
typedef struct _S_CSP_ITEM_ABRASION
{

} S_CSP_ITEM_ABRASION, * PS_CSP_ITEM_ABRASION;


// SCP_ITEM_ABRASION : 0x9411
typedef struct _S_SCP_ITEM_ABRASION
{
	DWORD                                             dwKeyIDWeapon;// 무기 아이템의 KeyID
	DWORD                                             dwKeyIDBody;  // 의복 아이템의 KeyID
	DWORD                                             dwKeyIDShield;// 방패 아이템의 KeyID
	DWORD                                             dwKeyIDHead;  // 모자 아이템의 KeyID
	DWORD                                             dwKeyIDFoot;  // 신발 아이템의 KeyID
	DWORD                                             dwKeyIDBelt;  // 허리띠 아이템의 KeyID

} S_SCP_ITEM_ABRASION, * PS_SCP_ITEM_ABRASION;


// CSP_ITEM_ABRASION_BROADCAST : 0x1412
typedef struct _S_CSP_ITEM_ABRASION_BROADCAST
{

} S_CSP_ITEM_ABRASION_BROADCAST, * PS_CSP_ITEM_ABRASION_BROADCAST;


// SCP_ITEM_ABRASION_BROADCAST : 0x9412
typedef struct _S_SCP_ITEM_ABRASION_BROADCAST
{
	DWORD                                             dwKeyID;      // 아이템이 사라진 캐릭터의 KeyID
	DWORD                                             dwIndexWeapon;// 무기 아이템의 Index
	DWORD                                             dwIndexBody;  // 의복 아이템의 Index
	DWORD                                             dwIndexShield;// 방패 아이템의 Index
	DWORD                                             dwIndexHead;  // 모자 아이템의 Index
	DWORD                                             dwIndexFoot;  // 신발 아이템의 Index
	DWORD                                             dwIndexBelt;  // 허리띠 아이템의 Index

} S_SCP_ITEM_ABRASION_BROADCAST, * PS_SCP_ITEM_ABRASION_BROADCAST;

#define _MSG_MobStore		0x1421
#define _MSG_MobStore_Buy	0x1422
#define _MSG_MobStatus		0x1423
struct MOBSTOREITEM
{	int					nIndex;
	int					nPrice;
	STRUCT_ITEM			item;
};
struct MSG_MobStore
{	_MSG
	int 				nID;
	BYTE				byMode;		//	0:상거래안함, 1:상거래함
	BYTE				byDummy;
	short				snDummy;
	char				szTrade[SZTRADE_LENGTH];
	MOBSTOREITEM		TradeItem[MAX_MOBSTORE];
};
struct MSG_MobStore_Buy
{	_MSG
	int					nID;
	BYTE				byIndex[MAX_MOBSTORE];		
};
struct MSG_MobStatus
{	_MSG
	int					nID;
	BYTE				byTradeMode;
	BYTE				byDummy1;
	BYTE				byDummy2;
	BYTE				byDummy3;
	char				szTrade[SZTRADE_LENGTH];
	int					nRupia;
};

/************************************************************************************************/
//	CHAT PACKET
/************************************************************************************************/
//	일반채팅
#define CSP_REQ_CHAT					0x1501
#define SCP_RESP_CHAT					0x9501
#define SCP_NOTIFY_CHAT					0x9502
typedef struct _S_CSP_REQ_CHAT
{	_MSG
	BYTE                            byBgColor;					// 채팅 메세지 배경색
	BYTE                            byTextColor;				// 채팅 메세지 글자색
	BYTE							byTrimuriti;
	BYTE							byWhere;					// 0:채팅창, 1:머리풍선, 2:채팅창과 머리풍선 모두
	short							snDummy;
	char                            szMsg[MAX_CHAT_LENGTH];		// 채팅 메세지
} S_CSP_REQ_CHAT, * PS_CSP_REQ_CHAT;
typedef struct _S_SCP_NOTIFY_CHAT
{	_MSG
	int		nID;							// 채팅 메세지를 전송한 캐릭터 KeyID
	BYTE    byBgColor;						// 채팅 메세지 배경색
	BYTE    byTextColor;					// 채팅 메세지 글자색
	BYTE	byTrimuriti;
	BYTE	byWhere;						// 0:채팅창, 1:머리풍선, 2:채팅창과 머리풍선 모두
	short	snDummy;
	char    szMsg[MAX_CHAT_LENGTH];		// 채팅 메세지
} S_SCP_NOTIFY_CHAT, * PS_SCP_NOTIFY_CHAT;

//	귀속말
#define CSP_REQ_WHISPER_CHAT			0x1503
#define SCP_RESP_WHISPER_CHAT			0x9503
#define SCP_NOTIFY_WHISPER_CHAT			0x9504
typedef struct _S_CSP_REQ_WHISPER_CHAT
{	_MSG	
	BYTE	byBgColor;    // 채팅 메세지 배경색                                              
	BYTE	byTextColor;  // 채팅 메세지 글자색
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];   // 채팅 메세지                                              
	char    szName[SZNAME_LENGTH];   // 채팅 메세지를 전송할 캐릭터 이름                                           
} S_CSP_REQ_WHISPER_CHAT, * PS_CSP_REQ_WHISPER_CHAT;
typedef struct _S_SCP_RESP_WHISPER_CHAT
{	_MSG	
	BYTE	byResult;
	BYTE	byBgColor;				// 채팅 메세지 배경색                                              
	BYTE	byTextColor;			// 채팅 메세지 글자색  
	BYTE	byTrimuriti;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // 채팅 메세지                                              
	char    szName[SZNAME_LENGTH];				// 채팅 메세지를 전송할 캐릭터 이름                                       
} S_SCP_RESP_WHISPER_CHAT, * PS_SCP_RESP_WHISPER_CHAT;
typedef struct _S_SCP_NOTIFY_WHISPER_CHAT
{	_MSG   
	BYTE    byBgColor;    // 채팅 메세지 배경색                                          
	BYTE    byTextColor;  // 채팅 메세지 글자색  
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];   // 채팅 메세지 
	char    szName[SZNAME_LENGTH];   // 채팅 메세지를 전송한 캐릭터 이름  
                                                                               
} S_SCP_NOTIFY_WHISPER_CHAT, * PS_SCP_NOTIFY_WHISPER_CHAT;

////	공지 메세지
//#define CSP_REQ_BROADCAST				0x1505
//#define SCP_NOTIFY_BROADCAST			0x9506
//typedef struct _S_CSP_REQ_BROADCAST
//{	_MSG
//	BYTE	byMsgType;		//	파티(0), 길드(1), 존(2), 월드(3), 게임(4)		
//	BYTE	byBgColor;		//	채팅 메세지 배경색                                              
//	BYTE	byTextColor;	//	채팅 메세지 글자색                                              
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH];   // 채팅 메세지 
//} S_CSP_REQ_BROADCAST, * PS_CSP_REQ_BROADCAST;
//typedef struct _S_SCP_NOTIFY_BROADCAST
//{	_MSG
//	BYTE	byMsgType;		//	파티(0), 길드(1), 존(2), 월드(3), 게임(4)	
//	BYTE	byBgColor;		// 채팅 메세지 배경색                                              
//	BYTE	byTextColor;	// 채팅 메세지 글자색  
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH];   // 채팅 메세지   
//	char    szName[SZNAME_LENGTH];   // 채팅 메세지를 전송한 캐릭터 이름   
//} S_SCP_NOTIFY_BROADCAST, * PS_SCP_NOTIFY_BROADCAST;
#define _MSG_Chat						0x1507			//	파티, 길드채팅
struct MSG_Chat
{
	_MSG
	BYTE	byMsgType;					//	파티(1), 길드(2), 채팅방(3)	
	BYTE	byBgColor;					//	채팅 메세지 배경색                                              
	BYTE	byTextColor;				//	채팅 메세지 글자색  
	BYTE	byTrimuriti;				//	케릭터의 주신
	int		nGuildID;					//	길드채팅일 경우 해당길드의 ID
	int		nAlliedGuildID;				//	연합길드 채팅의 경우 연합길드의 ID
	char	szMsg[MAX_GROUPCHAT_LENGTH];		//	채팅 메세지
	char    szName[SZNAME_LENGTH];		//	채팅 메세지를 전송한 캐릭터 이름   
};
#define _MSG_Broadcast					0x1508
struct MSG_Broadcast
{
	_MSG
	BYTE	byMsgType;					//	존(1), 월드(2), 게임(3), 전투명령서(4), 호외(5), GM공지(6)	
	BYTE	byBgColor;					//	채팅 메세지 배경색                                              
	BYTE	byTextColor;				//	채팅 메세지 글자색(전투명령서와 호외의 경우 인벤인덱스로 사용한다.)
	BYTE	byTrimuriti;				//	케릭터의 주신
	char	szMsg[MAX_NOTIFY_LENGTH];   //	채팅 메세지   
	char    szName[SZNAME_LENGTH];		//	채팅 메세지를 전송한 캐릭터 이름   
};

// 진정 메시지
#define CSP_REQ_APPEAL_CHAT					0x150F
#define SCP_RESP_APPEAL_CHAT				0x950F
typedef struct _S_CSP_REQ_APPEAL_CHAT
{	_MSG;
	char	szMsg[MAX_CHAT_LENGTH];
} S_CSP_REQ_APPEAL_CHAT, * PS_CSP_REQ_APPEAL_CHAT;
typedef struct _S_SCP_RESP_APPEAL_CHAT
{	_MSG;
	BYTE	byResult;	// 결과 : 0x00 - 성공, 0x01 - 실패(접수되지 않음), 0x02 - 실패(진정 처리한도 초과)
	BYTE	byDummy;
	SHORT	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];
} S_SCP_RESP_APPEAL_CHAT, * PS_SCP_RESP_APPEAL_CHAT;

#define	SSP_REQ_WHISPER_CHAT		0x0010
#define SSP_RESP_WHISPER_CHAT		0x8010
#define SSP_NOTIFY_WHISPER_CHAT		0x8011
struct S_SSP_REQ_WHISPER_CHAT
{	_MSG	
	int		nID;
	BYTE	byBgColor;				// 채팅 메세지 배경색                                              
	BYTE	byTextColor;			// 채팅 메세지 글자색    
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // 채팅 메세지    
	char    szSourName[SZNAME_LENGTH];			// 채팅 메세지를 전송한 캐릭터 이름  
	char    szDestName[SZNAME_LENGTH];			// 채팅 메세지를 전송할 캐릭터 이름            
};
struct S_SSP_RESP_WHISPER_CHAT
{	_MSG	
	int		nID;
	BYTE	byResult;
	BYTE	byBgColor;				// 채팅 메세지 배경색                                              
	BYTE	byTextColor;			// 채팅 메세지 글자색  
	BYTE	byTrimuriti;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // 채팅 메세지                                              
	char    szName[SZNAME_LENGTH];				// 채팅 메세지를 전송할 캐릭터 이름 
};
struct S_SSP_NOTIFY_WHISPER_CHAT
{	_MSG	
	int		nID;
	BYTE	byBgColor;							// 채팅 메세지 배경색                                              
	BYTE	byTextColor;						// 채팅 메세지 글자색  
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];				// 채팅 메세지                                              
	char    szName[SZNAME_LENGTH];				// 채팅 메세지를 전송한 캐릭터 이름 
};

//#define	SSP_REQ_BROADCAST			0x0011
//#define SSP_NOTIFY_BROADCAST		0x8012
//struct S_SSP_REQ_BROADCAST
//{	_MSG	
//	int		nID;
//	BYTE	byMsgType;				//	파티(0), 길드(1), 존(2), 월드(3), 게임(4)	
//	BYTE	byBgColor;				//	채팅 메세지 배경색                                              
//	BYTE	byTextColor;			//	채팅 메세지 글자색
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH]; //	채팅 메세지            
//};
//struct S_SSP_NOTIFY_BROADCAST
//{	_MSG
//	BYTE	byMsgType;				//	파티(0), 길드(1), 존(2), 월드(3), 게임(4)	
//	BYTE	byBgColor;				//	채팅 메세지 배경색                                              
//	BYTE	byTextColor;			//	채팅 메세지 글자색                                              
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH]; //	채팅 메세지                                              
//	char    szName[SZNAME_LENGTH];	//	메세지를 전송한 캐릭터 이름 
//};
#define SSP_REQ_APPEAL_CHAT			0x0012
#define SSP_RESP_APPEAL_CHAT		0x0013
typedef struct _S_SSP_REQ_APPEAL_CHAT
{	_MSG;
	int		nID;
	char	szMsg[MAX_CHAT_LENGTH];
} S_SSP_REQ_APPEAL_CHAT, *PS_SSP_REQ_APPEAL_CHAT;
typedef struct _S_SSP_RESP_APPEAL_CHAT
{	_MSG;
	int		nID;
	BYTE	byResult;	// 결과 : 0x00 - 성공, 0x01 - 실패(접수되지 않음), 0x02 - 실패(진정 처리한도 초과)
	BYTE	byDummy;
	SHORT	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];
} S_SSP_RESP_APPEAL_CHAT, * PS_SSP_RESP_APPEAL_CHAT;

#define _MSG_COMMAND				0x1510
struct MSG_COMMAND
{
	_MSG
	BYTE	byMsgType;					//	존(1), 월드(2), 게임(3)	
	BYTE	byBgColor;					//	채팅 메세지 배경색                                              
	BYTE	byTextColor;				//	채팅 메세지 글자색  
	BYTE	byTrimuriti;				//	케릭터의 주신
	char	szMsg[MAX_NOTIFY_LENGTH];   //	채팅 메세지   
	char    szName[SZNAME_LENGTH];		//	채팅 메세지를 전송한 캐릭터 이름   
};

#define _MSG_ServerCommand			0x1511
struct MSG_ServerCommand
{
	_MSG
	BYTE	byCommandType;					//	명령어 종류(0:로그덤프,..)
	BYTE	byDummy1;					                                             
	BYTE	byDummy2;					
	BYTE	byDummy3;					 
};

#define	SSP_REQ_ZONE_INIT			0x0013
//	S_CSP_REQ_TRADE_CANCEL는 S_REQUEST를 이용하기로 한다.
/************************************************************************************************/
//	Guild	packet
/************************************************************************************************/
#define _MSG_GuildInfo						0x1601
struct MSG_GuildInfo
{		_MSG;
		char				GuildName[SZNAME_LENGTH];
		char				AlliedGuildName1[SZNAME_LENGTH];
		char				AlliedGuildName2[SZNAME_LENGTH];
		char				EnemyGuildName1[SZNAME_LENGTH];
		char				EnemyGuildName2[SZNAME_LENGTH];

		int					GuildID;
		int					Mark;
		DWORD				dwTime[3];
		BYTE				byCargoLevel[3];
		BYTE				byDummy;
		char				GuildMessage[GUILDMESSAGE_LENGTH];
		STRUCT_GUILD_MEMBER	Member[MAX_GUILD_MEMBER];
};
#define	_MSG_CreateGuild					0x1602  
struct	MSG_CreateGuild
{		_MSG
		int					GuildID;
		int					Trimurity;
		int					GuildMark;
		char				GuildName[GUILDNAME_LENGTH];
		STRUCT_GUILD_MEMBER Member;
};
#define	_MSG_AddGuildMember					0x1603
struct	MSG_AddGuildMember
{		_MSG
		int					GuildID;
		int					nID;
		STRUCT_GUILD_MEMBER	Member;
};
#define	_MSG_RemoveGuildMember				0x1604 
struct	MSG_RemoveGuildMember
{		_MSG
		int					GuildID;
		BYTE				byRemoveType;						//	자신이 탈퇴(1), 남을방출(2), 길드해체(3)
		BYTE				byDummy;							//	enum { eGuild_Remove_me = 1, eGuild_Remove_you = 2, eGuild_Remove_All = 3, } ;
		short				snDummy;
		char				CharacterName[SZNAME_LENGTH];
};
#define	_MSG_REQGuild						0x1605
struct	MSG_REQGuild
{		_MSG
		char				GuildName[GUILDNAME_LENGTH];
		char				CharacterName[SZNAME_LENGTH];
		int					GuildID;
		int					nDest;
};
#define	_MSG_CNFGuild						0x1606
struct	MSG_CNFGuild
{		_MSG
		int					GuildID;
		char				CharacterName[SZNAME_LENGTH];
};
#define	_MSG_GuildMemberin					0x1607
struct  MSG_GuildMemberin
{		_MSG
		int					GuildID;
		char				CharacterName[SZNAME_LENGTH];
} ;
#define _MSG_GuildMemberout					0x1608
struct	MSG_GuildMemberout
{		_MSG
		int					GuildID;
		char				CharacterName[SZNAME_LENGTH];
} ;
#define _MSG_GuildUpdate					0x1609
struct	MSG_GuildUpdate
{		_MSG
		int					nID;
		int					GuildID;
		char				AlliedGuildName1[GUILDNAME_LENGTH];
		char				AlliedGuildName2[GUILDNAME_LENGTH];
		char				EnemyGuildName1[GUILDNAME_LENGTH];
		char				EnemyGuildName2[GUILDNAME_LENGTH];
		char				GuildMessage[GUILDMESSAGE_LENGTH];				
};
#define _MSG_GuildUpdateMember					0x1610
struct MSG_GuildUpdateMember
{		_MSG
		int					nID;
		int					GuildID;
		STRUCT_GUILD_MEMBER Member;
};
#define	_MSG_GuildSetRanking					0x1611
struct MSG_GuildSetRanking
{		_MSG
		int					nID;
		int					nGuildID;
		char				CharacterName[SZNAME_LENGTH];
		BYTE				GuildRank;
		BYTE				byDummy;
		short				snDummy;
};
#define _MSG_GuildUpdateMark					0x1612
struct MSG_GuildUpdateMark
{		_MSG
		BYTE				byResult;
		BYTE				byCostType;			//	1:Rupia, 2: Cash
		short				snDummy;
		int					GuildID;
		int					Mark;
		int					nMoney;				//	루피아 또는 타니
};

#define _MSG_GuildNotify						0x1613
struct MSG_GuildNotify
{		_MSG
		int			nID;
		char		GuildName[GUILDNAME_LENGTH];
		int			nMark;
};

#define _Msg_GuildAlliance						0x1614
struct Msg_GuildAlliance
{
		_MSG
		int			nID;					//	상대의 nID
		BYTE		byResult;				
		BYTE		byType;					//	enum { eGuildFriend = 1, eGuildHost = 2, };				//	1:동맹, 2:적대
		BYTE		byAct;					//	enum { eGuildAllianceIn = 1, eGuildAllianceOut = 2, };	//	1:결성, 2:해체
		BYTE		byDummy;
};

#define _Msg_GuildCargoUsingLevel				0x1615
struct Msg_GuildCargoUsingLevel				//	공지용(전존공지), 마하라자만 이용가능
{
	_MSG
	int		nGuildID;
	BYTE	byCargoLevel[3];
	BYTE	byDummy;
};

#define _Msg_GuildCargoTimeExtension			0x1616
struct Msg_GuildCargoTimeExtension			//	마하라자만 이용가능
{
	_MSG
	BYTE	byResult;						//	0:성공, 1:실패
	BYTE	byType;							//	1: 1번사용, 2: 1,2번사용, 3: 1,2,3번사용
	short	snDummy;
};

#define _Msg_GuildCargoTime						0x1617
struct Msg_GuildCargoTime					//	공지용(전존공지), 마하라자만 이용가능
{
	_MSG
	int			nGuildID;
	DWORD		dwTime[3];
};

#define _Msg_GuildItem							0x1618
struct Msg_GuildItem
{
	_MSG
	STRUCT_ITEM arrItem[MAX_CARGO*3];				//	길드창고리스트(_Msg_GuildCargoUse로 사용요청한 길원에게 알린다)
};

//#define _Msg_GuildCargoUse						0x1619
//struct Msg_GuildCargoUse
//{
//	_MSG
//	BYTE	bySet;									//	0:사용해제, 1:사용요청
//	BYTE	byResult;								//	사용해제나 사용요청에 대한 결과(0:성공, 1:실패)
//};
//
//#define _Msg_GuildCargoUseUpdate				0x1620
//struct Msg_GuildCargoUseUpdate
//{
//	_MSG
//	int		nGuildID;
//	char	pUsingMember[SZNAME_LENGTH];			//	창고를 사용중인 케릭터(없을 경우 null)
//};

#define _Msg_GuildItemUpdate					0x1621
struct Msg_GuildItemUpdate
{
	_MSG
	int				nGuildID;
	int				nFromIndex;
	int				nToIndex;
	STRUCT_ITEM		item;
};

/************************************************************************************************/
//	MESSENGER PACKET 2700 - 2710
/************************************************************************************************/
#define	MAX_MESSENGER		28
struct STRUCT_MESSENGER_ITEM
{		char	szCharName[SZNAME_LENGTH];		
		BYTE	Status;						// 0:빈슬롯 1:OFF	2:ON	3:BLOCK?(보류)
		BYTE	Opponent;
		short	snTribe;					// 캐릭터의 종족                                   			
};

struct STRUCT_MESSENGER_LIST
{   int		Login;
    int		Slot;
	char	AccountName[ACCOUNTNAME_LENGTH];	// 현재 사용중인 어카운트
	char	CharName[SZNAME_LENGTH];
	STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];
};	

#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
	struct STRUCT_OLD_MESSENGER_LIST
	{	int		Login;
		int		Slot;
		char	AccountName[OLD_ACCOUNTNAME_LENGTH];	// 현재 사용중인 어카운트
		char	CharName[SZNAME_LENGTH];
		STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];
	};
#endif

struct STRUCT_MESSENGER_FILE
{
	STRUCT_MESSENGER_LIST Char[MOB_PER_ACCOUNT];
};

#define _MSG_MessengerLogin					0x2700	// Zone -> MSG -> nZone -> (UpdateMessengerUI) nUser
struct	MSG_MessengerLogin
{		_MSG;
		int		nID;							// 1~999
		int		nServerIndex;					// 0 -19
		int		nSlot;
		int		nGuildID;
		char	AccountName	[ACCOUNTNAME_LENGTH];
		char	CharName	[SZNAME_LENGTH];
};
#define _MSG_MessengerLogout				0x2701	// Zone -> MSG -> nZone -> (UpdateMessengerUI) nUser
struct	MSG_MessengerLogout
{		_MSG;
		int		nID;							// 1~999
		int		nServerIndex;					// 0 -19
		int		nSlot;
		int		nGuildID;
		char	AccountName	[ACCOUNTNAME_LENGTH];
		char	CharName	[SZNAME_LENGTH];
};
#define	_MSG_UpdateMessengerList			0x2702  // 전체 메신저 슬롯을 갱신한다
struct	MSG_UpdateMessengerList
{		_MSG
		int		nID;							// 1~999
		STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];
};
#define	_MSG_UpdateMessengerItem			0x2703	// 한개의 메신저 슬롯을 갱신한다
struct	MSG_UpdateMessengerItem
{		_MSG
		int		nID;							// 1~999
		int		nSlot;
		STRUCT_MESSENGER_ITEM Item;
};
// 클라이언트는 Char_init요청 직전 STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER] 을 memset(0) 한다.
// 클라이언트도 메신저에 누군가를 추가/해제 할경우 서버에 UpdateMessengerItem를 날린다.
// 요청만하고 갱신은 서버의 UpdateMessengerItem으로 갱신하고, 서버는 MessageBox도 준다.
#define _MSG_ReqMessenger					0x2704
struct MSG_ReqMessenger
{		_MSG
		int						nSlot;
		int						nTargetID;
		STRUCT_MESSENGER_ITEM	Item;
};
#define _MSG_CNFMessenger					0x2705
struct MSG_CNFMessenger
{		_MSG
		int		nSlot;
		char	CharName	[SZNAME_LENGTH];
};
#define _MSG_RemoveMessenger				0x2706
struct MSG_RemoveMessenger
{		_MSG
		int		nSlot;
};
#define _MSG_MessengerRemovelist			0x2707
struct MSG_MessengerRemovelist
{		_MSG
		int		nID;
		BYTE	bySlot;
		BYTE	byDummy;
		short	snDummy;
		char	AccountName	[ACCOUNTNAME_LENGTH];
};

//#define	_MSG_MessengerChangeMyInfo					0x2704		//	친구의 정보가 변경될 경우사용(ZS<->MSG)
//struct MSG_MessengerChangeMyInfo 
//{
//		_MSG
//		int		nID;
//		STRUCT_MESSENGER_ITEM Item;
//};
//#define _MSG_MessengerSave					0x2705		//	존서버내 유저의 messenger정보변경을 알림.(ZS->MSG)
//struct MSG_MessengerSave
//{
//		_MSG
//		int		nID;
//		int		nSlot;
//		STRUCT_MESSENGER_ITEM Item;
//};


/************************************************************************************************/
//	PARTY PACKET
/************************************************************************************************/
#define _MSG_REQParty                       0x2401
struct   MSG_REQParty                       //	파티원으로 가입을 요청함
{											//	서버가 보낼때는 전체 리스트
	    _MSG;								//	C->S, S->C 메세지
         S_PARTY Leader;
		 int   TargetID;
};
#define _MSG_CNFParty                       0x2402
struct   MSG_CNFParty                       //	파티원으로 가입을 허가함.
{                                           //	C->S 메세지
	    _MSG;
        int	TargetID;
};
#define _MSG_AddParty               		0x2403
struct   MSG_AddParty              		//	멤버추가시, 파티가입시 멤버정보가 날아간다.
{                                   		//	S->C
	    _MSG;
		int nLeaderID;
		S_PARTY Party;
};
#define _MSG_RemoveParty					0x2404
struct   MSG_RemoveParty                 	//	멤버탈퇴시나 파티해체시 멤버정보가 날아간다.
{                                        	//	C->S 자신이 탈퇴시 nID=자신, 
	    _MSG;								//	C->S 리더가 멤버방출시 nID=타인,
		int nLeaderID;						//	C->S 리더가 파티해체시 nID=MAX_USER(1000)
		int nTargetID;						//	S->C 멤버 탈퇴나 방출시 서버가 날림.
};
#define	SCP_RESP_UPDATE_PARTY				0x2406
typedef struct _S_SCP_RESP_UPDATE_PARTY
{	_MSG
	S_PARTY	Party;
} S_SCP_RESP_UPDATE_PARTY, *PS_SCP_RESP_UPDATE_PARTY;
#define _MSG_SetParty						0x2407
struct   MSG_SetParty
{	_MSG
	byte	byResult;
	byte	byRootingMode;					//	파티리더가 루팅세팅을 바꿀수 있다.(ROOTING_SHARE=0, ROOTING_PERSON=1)
	short   snDummy;
};

/************************************************************************************************/

#define _MSG_GMMode							0x2501
struct MSG_GMMode
{
		_MSG
		int		nID;
		BYTE	byResult;						//	0:성공, 1:실패
		BYTE	byGMMode;						//	bit flag(0x01:케릭터블럭, 0x02:투명모드, 0x04:채팅블럭, ...)	
		short	snDummy;
		char	szCharName[SZNAME_LENGTH];		//	bit flag 중목중복은 | 연산사용.
};
#define _MSG_GMMode_Notify					0x2502
struct MSG_GMMode_Notify
{
		_MSG
		int		nID;
		BYTE	byGMMode;						//	bit flag(0x01:케릭터블럭, 0x02:투명모드, 0x04:채팅블럭, ...)	
		BYTE	byDummy;
		short	snDummy;
};
#define _MSG_GMMovePosition					0x2503
struct MSG_GMMovePosition
{
		_MSG
		short	snX;
		short	snZ;
};
#define _MSG_GMMoveToPlayer					0x2504
struct MSG_GMMoveToPlayer
{
		_MSG
		int		nID;
		BYTE	byZone;
		BYTE	byDummy;
		short	snDummy;
		char	szCharName[SZNAME_LENGTH];
};
#define _MSG_GMKickPlayer					0x2505
struct MSG_GMKickPlayer
{	_MSG;
	int			nID;						// S->S 일때만, 클라이언트는 무조건 0을 넣는다.
	int			nResult;					// S->C 일때만, 0이면 성공, 1이면 접속중 아님.
	char		szCharName[SZNAME_LENGTH];
};
#define _MSG_Warp							0x2506
struct MSG_Warp
{	_MSG;
	int		nID;		//	호출자 ID(호출자가 없을 경우 0)
	byte	byResult;
	byte	byType;
	short	snDummy;
	DWORD	dwPlace;
	char	szName[SZNAME_LENGTH];
};
#define	_MSG_KickAccount					0x2507
struct MSG_KickAccount
{	_MSG
	int		iID;
	char	AccountName[ACCOUNTNAME_LENGTH];
};


// CSP_REQ_QUEST_HISTORY : 0x1701
typedef struct _S_CSP_REQ_QUEST_HISTORY
{

} S_CSP_REQ_QUEST_HISTORY, * PS_CSP_REQ_QUEST_HISTORY;


// SCP_RESP_QUEST_HISTORY : 0x9701
typedef struct _S_SCP_RESP_QUEST_HISTORY
{	_MSG;
	BYTE					byQuest[MAX_EVENT_FLAG];	
} S_SCP_RESP_QUEST_HISTORY, * PS_SCP_RESP_QUEST_HISTORY;


// CSP_QUEST_DIALOG : 0x1702
typedef struct _S_CSP_QUEST_DIALOG
{	_MSG;
	short                                             snDialog;		// 대화 번호
	byte                                              byResult;     // 대화 결과
	byte											  byDummy;

} S_CSP_QUEST_DIALOG, * PS_CSP_QUEST_DIALOG;


// SCP_QUEST_DIALOG : 0x9702
typedef struct _S_SCP_QUEST_DIALOG
{	_MSG;
	short                                              wIndex;       // 대화 번호
    short											   snDummy;
} S_SCP_QUEST_DIALOG, * PS_SCP_QUEST_DIALOG;


// CSP_QUEST_NOTIFY_LEVEL : 0x1703
typedef struct _S_CSP_QUEST_NOTIFY_LEVEL
{	_MSG;
	SHORT											  snNPCIndex;	// NPC 인덱스 번호
} S_CSP_QUEST_NOTIFY_LEVEL, * PS_CSP_QUEST_NOTIFY_LEVEL;


// SCP_QUEST_NOTIFY_LEVEL : 0x9703
typedef struct _S_SCP_QUEST_NOTIFY_LEVEL
{	_MSG;
	SHORT                                             snNPCIndex;   // NPC 인덱스 번호
	BYTE                                              byIndex;      // 퀘스트 인덱스 번호
	BYTE                                              byLevel;      // 퀘스트 진행 상태

} S_SCP_QUEST_NOTIFY_LEVEL, * PS_SCP_QUEST_NOTIFY_LEVEL;


// CSP_MONSTER_DISAPPEAR : 0x1801
typedef struct _S_CSP_MONSTER_DISAPPEAR
{

} S_CSP_MONSTER_DISAPPEAR, * PS_CSP_MONSTER_DISAPPEAR;


// SCP_MONSTER_DISAPPEAR : 0x9801
typedef struct _S_SCP_MONSTER_DISAPPEAR
{
	DWORD                                             dwKeyID;      // Monster의 KeyID
	BYTE                                              byType;       // Monster가 사라지는 유형

} S_SCP_MONSTER_DISAPPEAR, * PS_SCP_MONSTER_DISAPPEAR;


// CSP_CHAR_STATUS : 0x1802
typedef struct _S_CSP_CHAR_STATUS
{

} S_CSP_CHAR_STATUS, * PS_CSP_CHAR_STATUS;


// SCP_CHAR_STATUS : 0x9802
typedef struct _S_SCP_CHAR_STATUS
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	DWORD                                             dwStatus;     // 캐릭터의 상태 정보

} S_SCP_CHAR_STATUS, * PS_SCP_CHAR_STATUS;


// CSP_CHAR_MONSTER_STATUS_BROADCAST : 0x1803
typedef struct _S_CSP_CHAR_MONSTER_STATUS_BROADCAST
{

} S_CSP_CHAR_MONSTER_STATUS_BROADCAST, * PS_CSP_CHAR_MONSTER_STATUS_BROADCAST;


// SCP_CHAR_MONSTER_STATUS_BROADCAST : 0x9803
typedef struct _S_SCP_CHAR_MONSTER_STATUS_BROADCAST
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	BYTE                                              byAct;        // 상태
	DWORD                                             dwStatus;     // 상태

} S_SCP_CHAR_MONSTER_STATUS_BROADCAST, * PS_SCP_CHAR_MONSTER_STATUS_BROADCAST;


// CSP_CHAR_DEATH : 0x1805
typedef struct _S_CSP_CHAR_DEATH
{

} S_CSP_CHAR_DEATH, * PS_CSP_CHAR_DEATH;


// SCP_CHAR_DEATH : 0x9805
typedef struct _S_SCP_CHAR_DEATH
{
	short                                             snLossPrana;  // 소실된 프라나의 양
	BYTE                                              byCount;      // 소실된 아이템의 수

} S_SCP_CHAR_DEATH, * PS_SCP_CHAR_DEATH;


// CSP_CHAR_MONSTER_DEATH_BROADCAST : 0x1806
typedef struct _S_CSP_CHAR_MONSTER_DEATH_BROADCAST
{

} S_CSP_CHAR_MONSTER_DEATH_BROADCAST, * PS_CSP_CHAR_MONSTER_DEATH_BROADCAST;


// SCP_CHAR_MONSTER_DEATH_BROADCAST : 0x9806
typedef struct _S_SCP_CHAR_MONSTER_DEATH_BROADCAST
{
	DWORD                                             dwKeyID;      // 죽은 캐릭터 또는 Monster의 KeyID

} S_SCP_CHAR_MONSTER_DEATH_BROADCAST, * PS_SCP_CHAR_MONSTER_DEATH_BROADCAST;


// CSP_CHAR_HP_RECOVERY : 0x1811
typedef struct _S_CSP_CHAR_HP_RECOVERY
{

} S_CSP_CHAR_HP_RECOVERY, * PS_CSP_CHAR_HP_RECOVERY;


// SCP_CHAR_HP_RECOVERY : 0x9811
typedef struct _S_SCP_CHAR_HP_RECOVERY
{
	int                                               nCurHP;       // 회복된 후의 현재 HP
	short                                             snHPRecoveryRate;// 캐릭터의 HP 회복율
	int                                               nPrana;       // 총 프라나의 양

} S_SCP_CHAR_HP_RECOVERY, * PS_SCP_CHAR_HP_RECOVERY;


// CSP_MONSTER_HP_RECOVERY : 0x1812
typedef struct _S_CSP_MONSTER_HP_RECOVERY
{

} S_CSP_MONSTER_HP_RECOVERY, * PS_CSP_MONSTER_HP_RECOVERY;


// SCP_MONSTER_HP_RECOVERY : 0x9812
typedef struct _S_SCP_MONSTER_HP_RECOVERY
{
	int                                               nCurHP;       // 회복된 후의 현재 HP
	short                                             snStress;     // Monster 스트레스

} S_SCP_MONSTER_HP_RECOVERY, * PS_SCP_MONSTER_HP_RECOVERY;


// CSP_CHAR_CAST_PROMOTE : 0x1821
typedef struct _S_CSP_CHAR_CAST_PROMOTE
{

} S_CSP_CHAR_CAST_PROMOTE, * PS_CSP_CHAR_CAST_PROMOTE;


// SCP_CHAR_CAST_PROMOTE : 0x9821
typedef struct _S_SCP_CHAR_CAST_PROMOTE
{
	BYTE                                              byCastClass;  // 상승된 후의 카스트 등급
	BYTE                                              byCastGrade;  // 상승된 후의 카스트 계급

} S_SCP_CHAR_CAST_PROMOTE, * PS_SCP_CHAR_CAST_PROMOTE;


// CSP_CHAR_CAST_PROMOTE_BROADCAST : 0x1822
typedef struct _S_CSP_CHAR_CAST_PROMOTE_BROADCAST
{

} S_CSP_CHAR_CAST_PROMOTE_BROADCAST, * PS_CSP_CHAR_CAST_PROMOTE_BROADCAST;


// SCP_CHAR_CAST_PROMOTE_BROADCAST : 0x9822
typedef struct _S_SCP_CHAR_CAST_PROMOTE_BROADCAST
{
	char                                              	szName[SZNAME_LENGTH];   // 캐릭터의 이름
	BYTE                                              	byCastClass;  // 상승된 후의 카스트 등급
	BYTE                                              	byCastGrade;  // 상승된 후의 카스트 계급
	short												snDummy;

} S_SCP_CHAR_CAST_PROMOTE_BROADCAST, * PS_SCP_CHAR_CAST_PROMOTE_BROADCAST;


// CSP_CHAR_PING : 0x1831
typedef struct _S_CSP_CHAR_PING
{	_MSG;
} S_CSP_CHAR_PING, * PS_CSP_CHAR_PING;


// SCP_CHAR_PING : 0x9831
typedef struct _S_SCP_CHAR_PING
{

} S_SCP_CHAR_PING, * PS_SCP_CHAR_PING;


// CSP_REQ_CHAR_LOCATION : 0x1832
typedef struct _S_CSP_REQ_CHAR_LOCATION
{
	char                                              szName[SZNAME_LENGTH];   // 캐릭터의 이름

} S_CSP_REQ_CHAR_LOCATION, * PS_CSP_REQ_CHAR_LOCATION;


// SCP_RESP_CHAR_LOCATION : 0x9832
typedef struct _S_SCP_RESP_CHAR_LOCATION
{
	BYTE                                              byResult;     // Result Field
	WORD                                              wServerID;    // Server ID

} S_SCP_RESP_CHAR_LOCATION, * PS_SCP_RESP_CHAR_LOCATION;


// CSP_CHAR_PARAMS_CHANGE : 0x1911
typedef struct _S_CSP_CHAR_PARAMS_CHANGE
{

} S_CSP_CHAR_PARAMS_CHANGE, * PS_CSP_CHAR_PARAMS_CHANGE;


// SCP_CHAR_PARAMS_CHANGE : 0x9911
typedef struct _S_SCP_CHAR_PARAMS_CHANGE
{
	int                                               nPrana;       // 현재 프라나
	short                                             snChakraMuscle;// 근육의 차크라
	short                                             snChakraNerve;// 신경의 차크라
	short                                             snChakraHeart;// 심장의 차크라
	short                                             snChakraSoul; // 정신의 차크라
	short                                             snPureChakraMuscle;// 순수 근육의 차크라
	short                                             snPureChakraNerve;// 순수 신경의 차크라
	short                                             snPureChakraHeart;// 순수 심장의 차크라
	short                                             snPureChakraSoul;// 순수 정신의 차크라
	short                                             snPhysicalMinDamage;// 물리 최소 데미지
	short                                             snPhysicalMaxDamage;// 물리 최대 데미지
	short                                             snMagicMinDamage;// 마법 최소 데미지
	short                                             snMagicMaxDamage;// 마법 최대 데미지
	short                                             snFireMinDamage;// 불 최소 데미지
	short                                             snFireMaxDamage;// 불 최대 데미지
	short                                             snColdMinDamage;// 추위 최소 데미지
	short                                             snColdMaxDamage;// 추위 최대 데미지
	short                                             snPoisonMinDamage;// 독 최소 데미지
	short                                             snPoisonMaxDamage;// 독 최대 데미지
	short                                             snAcidMinDamage;// 산 최소 데미지
	short                                             snAcidMaxDamage;// 산 최대 데미지
	short                                             snArmorIntensity;// 갑옷의 강도-방어력
	short                                             snAttackSuccRate;// 공격 성공률
	short                                             snAvoidanceRate;// 회피율
	int                                               nMaxHP;       // 캐릭터의 최대 HP
	short                                             snFireResist; // 불 저항력
	short                                             snColdResist; // 추위 저항력
	short                                             snPoisonResist;// 독 저항력
	short                                             snAcidResist; // 산 저항력

} S_SCP_CHAR_PARAMS_CHANGE, * PS_SCP_CHAR_PARAMS_CHANGE;


// CSP_REQ_CHAKRA_RISING : 0x1921
typedef struct _S_CSP_REQ_CHAKRA_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID
	BYTE                                              byReqChakraPart;// 차크라 상승 요청 부위

} S_CSP_REQ_CHAKRA_RISING, * PS_CSP_REQ_CHAKRA_RISING;


// SCP_RESP_CHAKRA_RISING : 0x9921
typedef struct _S_SCP_RESP_CHAKRA_RISING
{
	BYTE                                              byResult;     // 결과
	int                                               nChakraPoint; 
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	int                                               nPrana;       

} S_SCP_RESP_CHAKRA_RISING, * PS_SCP_RESP_CHAKRA_RISING;


// CSP_REQ_BRAHMAN_RISING : 0x1922
typedef struct _S_CSP_REQ_BRAHMAN_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID

} S_CSP_REQ_BRAHMAN_RISING, * PS_CSP_REQ_BRAHMAN_RISING;


// SCP_RESP_BRAHMAN_RISING : 0x9922
typedef struct _S_SCP_RESP_BRAHMAN_RISING
{
	BYTE                                              byResult;     // 결과
	int                                               nRisingBrahman;// 상승 후 현재 브라만 포인트 값
	BYTE                                              byCastClass;  // 브라만 포인트 상승 후 카스트 등급
	BYTE                                              byCastGrade;  // 브라만 포인트 상승 후 카스트 계급
	int                                               nPrana;       

} S_SCP_RESP_BRAHMAN_RISING, * PS_SCP_RESP_BRAHMAN_RISING;


// CSP_REQ_INCREASE_INVENTORY_SLOT : 0x1931
typedef struct _S_CSP_REQ_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// 인벤토리 종류

} S_CSP_REQ_INCREASE_INVENTORY_SLOT, * PS_CSP_REQ_INCREASE_INVENTORY_SLOT;


// SCP_RESP_INCREASE_INVENTORY_SLOT : 0x9931
typedef struct _S_SCP_RESP_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // 인벤토리 슬롯 증가 요청 결과
	BYTE                                              byCount;      // Inventory Expand Info

} S_SCP_RESP_INCREASE_INVENTORY_SLOT, * PS_SCP_RESP_INCREASE_INVENTORY_SLOT;


// CSP_REQ_DECREASE_INVENTORY_SLOT : 0x1932
typedef struct _S_CSP_REQ_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// 인벤토리 종류
	BYTE                                              byX;          // Bag Item 들어갈 좌표 X
	BYTE                                              byZ;          // Bag Item 들어갈 좌표 Z

} S_CSP_REQ_DECREASE_INVENTORY_SLOT, * PS_CSP_REQ_DECREASE_INVENTORY_SLOT;


// SCP_RESP_DECREASE_INVENTORY_SLOT : 0x9932
typedef struct _S_SCP_RESP_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // 결과

} S_SCP_RESP_DECREASE_INVENTORY_SLOT, * PS_SCP_RESP_DECREASE_INVENTORY_SLOT;


// CSP_REQ_NPC_POINT_UP : 0x1941
typedef struct _S_CSP_REQ_NPC_POINT_UP
{
	DWORD                                             dwNPCKeyID;   // NPC KeyID

} S_CSP_REQ_NPC_POINT_UP, * PS_CSP_REQ_NPC_POINT_UP;


// SCP_RESP_NPC_POINT_UP : 0x9941
typedef struct _S_SCP_RESP_NPC_POINT_UP
{
	BYTE                                              byResult;     // NPC 친절도 상승 요청 결과
	DWORD                                             dwGroup;      // NPC 계통 번호
	DWORD                                             dwPoint;      // 상승 후 변경된 포인트 값

} S_SCP_RESP_NPC_POINT_UP, * PS_SCP_RESP_NPC_POINT_UP;


// CSP_REQ_CHANGE_CKAKRA_TO_PRANA : 0x1951
typedef struct _S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA
{

} S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA, * PS_CSP_REQ_CHANGE_CKAKRA_TO_PRANA;


// SCP_RESP_CHANGE_CKAKRA_TO_PRANA : 0x9951
typedef struct _S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA
{
	BYTE                                              byResult;     // NPC 친절도 상승 요청 결과
	int                                               nPrana;       // 총프라나의 양

} S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA, * PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA;


// CSP_OTHER_CHAR_PARAM_BROADCAST : 0x1952
typedef struct _S_CSP_OTHER_CHAR_PARAM_BROADCAST
{

} S_CSP_OTHER_CHAR_PARAM_BROADCAST, * PS_CSP_OTHER_CHAR_PARAM_BROADCAST;


// SCP_OTHER_CHAR_PARAM_BROADCAST : 0x9952
typedef struct _S_SCP_OTHER_CHAR_PARAM_BROADCAST
{
	DWORD                                             dwKeyID;      // 케릭터의 KeyID
	DWORD                                             dwGuildMark;  // 길드마크인덱스

} S_SCP_OTHER_CHAR_PARAM_BROADCAST, * PS_SCP_OTHER_CHAR_PARAM_BROADCAST;

//// CSP_REQ_PVP_RANKING : 0x1971
//typedef struct _S_CSP_REQ_PVP_RANKING
//{
//
//} S_CSP_REQ_PVP_RANKING, * PS_CSP_REQ_PVP_RANKING;
//
//
//// SCP_RESP_PVP_RANKING : 0x9971
//typedef struct _S_SCP_RESP_PVP_RANKING
//{
//	S_PVP_INFO                                        PvpInfo[50];  
//
//} S_SCP_RESP_PVP_RANKING, * PS_SCP_RESP_PVP_RANKING;


// CSP_REQ_SKILL_REGIST : 0x2001
typedef struct _S_CSP_REQ_SKILL_REGIST
{
	DWORD                                             dwIndex;      // 등록할 스킬의 Index
	BYTE                                              byType;       // SKILL의 종류

} S_CSP_REQ_SKILL_REGIST, * PS_CSP_REQ_SKILL_REGIST;


// SCP_RESP_SKILL_REGIST : 0xA001
typedef struct _S_SCP_RESP_SKILL_REGIST
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_SKILL_REGIST, * PS_SCP_RESP_SKILL_REGIST;


// CSP_SKILL_REGIST : 0x2002
typedef struct _S_CSP_SKILL_REGIST
{

} S_CSP_SKILL_REGIST, * PS_CSP_SKILL_REGIST;


// SCP_SKILL_REGIST : 0xA002
typedef struct _S_SCP_SKILL_REGIST
{
	DWORD                                             dwIndex;      // 자동 등록된 스킬의 Index
	BYTE                                              byType;       // SKILL의 종류

} S_SCP_SKILL_REGIST, * PS_SCP_SKILL_REGIST;


// CSP_REQ_SKILL_SELECT : 0x2003
typedef struct _S_CSP_REQ_SKILL_SELECT
{
	BYTE                                              bySelect;     // SKILL의 선택/해제
	BYTE                                              byHand;       // SKILL 오른쪽/왼쪽 구분
	DWORD                                             dwIndex;      // 선택/해제 스킬 Index

} S_CSP_REQ_SKILL_SELECT, * PS_CSP_REQ_SKILL_SELECT;


// SCP_RESP_SKILL_SELECT : 0xA003
typedef struct _S_SCP_RESP_SKILL_SELECT
{
	BYTE                                              byResult;     // SKILL 선택/해제 결과

} S_SCP_RESP_SKILL_SELECT, * PS_SCP_RESP_SKILL_SELECT;


// CSP_REQ_SKILL_SELECT_BROADCAST : 0x2004
typedef struct _S_CSP_REQ_SKILL_SELECT_BROADCAST
{

} S_CSP_REQ_SKILL_SELECT_BROADCAST, * PS_CSP_REQ_SKILL_SELECT_BROADCAST;


// SCP_RESP_SKILL_SELECT_BROADCAST : 0xA004
typedef struct _S_SCP_RESP_SKILL_SELECT_BROADCAST
{
	DWORD                                             dwKeyID;      // 케릭터의 KeyID
	BYTE                                              bySelect;     // SKILL의 선택/해제
	BYTE                                              byHand;       // SKILL 오른쪽/왼쪽 구분
	DWORD                                             dwIndex;      // 선택/해제 스킬 Index
	BYTE                                              byLevel;      // 스킬 레벨

} S_SCP_RESP_SKILL_SELECT_BROADCAST, * PS_SCP_RESP_SKILL_SELECT_BROADCAST;


// CSP_REQ_SKILL_USE2_CHAR : 0x2011
typedef struct _S_CSP_REQ_SKILL_USE2_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격할 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_SKILL_USE2_CHAR, * PS_CSP_REQ_SKILL_USE2_CHAR;


// SCP_RESP_SKILL_USE2_CHAR : 0xA011
typedef struct _S_SCP_RESP_SKILL_USE2_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_SCP_RESP_SKILL_USE2_CHAR, * PS_SCP_RESP_SKILL_USE2_CHAR;


// CSP_SKILL_READY_CHAR_BROADCAST : 0x2012
typedef struct _S_CSP_SKILL_READY_CHAR_BROADCAST
{

} S_CSP_SKILL_READY_CHAR_BROADCAST, * PS_CSP_SKILL_READY_CHAR_BROADCAST;


// SCP_SKILL_READY_CHAR_BROADCAST : 0xA012
typedef struct _S_SCP_SKILL_READY_CHAR_BROADCAST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwKeyID;      // 스킬을 사용하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;// 스킬 공격을 당하는 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표

} S_SCP_SKILL_READY_CHAR_BROADCAST, * PS_SCP_SKILL_READY_CHAR_BROADCAST;


// CSP_REQ_SKILL_ATK_CHAR : 0x2013
typedef struct _S_CSP_REQ_SKILL_ATK_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격할 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	short                                             snDegree;     // 공격자를 중심으로 한 방어자의 각도
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_SKILL_ATK_CHAR, * PS_CSP_REQ_SKILL_ATK_CHAR;


// SCP_RESP_SKILL_ATK_CHAR : 0xA013
typedef struct _S_SCP_RESP_SKILL_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCharX;      // 방어자 X 좌표
	short                                             snCharZ;      // 방어자 Z 좌표
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터/Monster의 현재 HP

} S_SCP_RESP_SKILL_ATK_CHAR, * PS_SCP_RESP_SKILL_ATK_CHAR;


// CSP_SKILL_ATK_CHAR_BROADCAST : 0x2014
typedef struct _S_CSP_SKILL_ATK_CHAR_BROADCAST
{

} S_CSP_SKILL_ATK_CHAR_BROADCAST, * PS_CSP_SKILL_ATK_CHAR_BROADCAST;


// SCP_SKILL_ATK_CHAR_BROADCAST : 0xA014
typedef struct _S_SCP_SKILL_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // 대상 Type
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // 스킬을 사용하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;//  스킬 공격을 당하는 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	short                                             snCharX;      // 방어자 X 좌표
	short                                             snCharZ;      // 방어자 Z 좌표
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터의 현재 HP
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCurX;       // 공격자의 현재 X 좌표
	short                                             snCurZ;       // 공격자의 현재 Z 좌표

} S_SCP_SKILL_ATK_CHAR_BROADCAST, * PS_SCP_SKILL_ATK_CHAR_BROADCAST;


// CSP_REQ_SKILL_LEVEL_UP : 0x2021
typedef struct _S_CSP_REQ_SKILL_LEVEL_UP
{
	DWORD                                             dwIndex;      // Level-Up을 요청할 스킬의 Index

} S_CSP_REQ_SKILL_LEVEL_UP, * PS_CSP_REQ_SKILL_LEVEL_UP;


// SCP_RESP_SKILL_LEVEL_UP : 0xA021
typedef struct _S_SCP_RESP_SKILL_LEVEL_UP
{
	BYTE                                              byResult;     // Level-Up 결과
	BYTE                                              byLevel;      // 스킬의 Level
	int                                               nPrana;       // 현재 프라나의 양
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리

} S_SCP_RESP_SKILL_LEVEL_UP, * PS_SCP_RESP_SKILL_LEVEL_UP;


// CSP_REQ_SHOP_SKILL_LIST : 0x2022
typedef struct _S_CSP_REQ_SHOP_SKILL_LIST
{
	DWORD                                             dwIndex;      
	DWORD                                             dwNpcKeyID;   

} S_CSP_REQ_SHOP_SKILL_LIST, * PS_CSP_REQ_SHOP_SKILL_LIST;


// SCP_RESP_SHOP_SKILL_LIST : 0xA022
typedef struct _S_SCP_RESP_SHOP_SKILL_LIST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCount;      // 습득 가능한 스킬의 수

} S_SCP_RESP_SHOP_SKILL_LIST, * PS_SCP_RESP_SHOP_SKILL_LIST;

#define CSP_REQ_SHOP_ITEM_LIST                            0x2101      // 제작 가능한 아이템 List를 요청
#define SCP_RESP_SHOP_ITEM_LIST                           0xA101      // 제작 가능한 아이템 List 요청에 대한 응답메세지
typedef struct _S_CSP_REQ_SHOP_ITEM_LIST
{
	DWORD                                             dwIndex;      
	DWORD                                             dwNpcKeyID;   

} S_CSP_REQ_SHOP_ITEM_LIST, * PS_CSP_REQ_SHOP_ITEM_LIST;
typedef struct _S_SCP_RESP_SHOP_ITEM_LIST
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwMakingIndex;// 제작중인 아이템 Index
	DWORD                                             dwRemainTime; // 제작중인 아이템의 남은 제작시간
	BYTE                                              byCount;      // 제작 가능한 아이템의 수

} S_SCP_RESP_SHOP_ITEM_LIST, * PS_SCP_RESP_SHOP_ITEM_LIST;

#define CSP_REQ_ITEM_BUY								  0x2102      // 아이템을 산다
#define SCP_RESP_ITEM_BUY	                              0xA102      // 아이템 구입에 대한 응답메세지
typedef struct _S_CSP_REQ_ITEM_BUY
{	_MSG;
	short											  snNPCIndex;	// 아이템 구입할 상인 index
	short                                             snItemIndex;  // 구입할 아이템 Index
	short											  snItemCount;	// 구입할 아이템 개수
	short											  snDummy;
} S_CSP_REQ_ITEM_BUY, * PS_CSP_REQ_ITEM_BUY;
typedef struct _S_SCP_RESP_ITEM_BUY
{	_MSG;
	BYTE            byResult;		// 0-성공, 1-실패
	BYTE			byDummy;
	short			snItemIndex;	// 아이템 상점인덱스
	int				nMoney;			// 상점 이용 후 변경된 돈
} S_SCP_RESP_ITEM_BUY, * PS_SCP_RESP_ITEM_BUY;

#define CSP_REQ_ITEM_SELL                               0x2104      // 아이템 수리를 요청
#define SCP_RESP_ITEM_SELL                              0xA104      // 아이템 수리요청에 대한 응답메세지
typedef struct _S_CSP_REQ_ITEM_SELL
{	_MSG;
	short	snNPCIndex;	// 아이템 판매할 상인 index
	BYTE    byPlace;	// 창고, 인벤, 장착
	BYTE	byIndex;	// 판매할 아이템 위치 Index											  
} S_CSP_REQ_ITEM_SELL, * PS_CSP_REQ_ITEM_SELL;
typedef struct _S_SCP_RESP_ITEM_SELL
{   _MSG;
	BYTE    byResult;		// 0-성공, 1-실패                                          
	BYTE	byPlace;		// 창고, 인벤, 장착										  
	BYTE	byIndex;		// 판매한 아이템 위치 Index										  
	BYTE	byDummy;
	int		nMoney;			// 상점 이용 후 변경된 돈
} S_SCP_RESP_ITEM_SELL, * PS_SCP_RESP_ITEM_SELL;

#define CSP_REQ_ITEM_REPAIR								0x2105
#define SCP_RESP_ITEM_REPAIR							0xA105
#define 	S_CSP_REQ_ITEM_REPAIR		S_CSP_REQ_ITEM_SELL	
#define		PS_CSP_REQ_ITEM_REPAIR		PS_CSP_REQ_ITEM_SELL
#define 	S_SCP_RESP_ITEM_REPAIR		S_SCP_RESP_ITEM_SELL
#define 	PS_SCP_RESP_ITEM_REPAIR		PS_SCP_RESP_ITEM_SELL

#define CSP_REQ_ITEM_REFINING                             0x2106      // 아이템 제련을 요청
#define SCP_RESP_ITEM_REFINING                            0xA106      // 아이템 제련 요청에 대한 응답메세지
typedef struct _S_CSP_REQ_ITEM_REFINING
{	_MSG
	BYTE	byPlace;
	BYTE	byIndex;
	BYTE	bySubPlace[3];											//	Index 0:주,보조재련 1:재련첨가재 2:미정
	BYTE	bySubIndex[3];
} S_CSP_REQ_ITEM_REFINING, * PS_CSP_REQ_ITEM_REFINING;
typedef struct _S_SCP_RESP_ITEM_REFINING
{	_MSG
	BYTE    byResult;     // Result Field
	BYTE	byPlace;
	BYTE	byIndex;
	BYTE	bySubPlace[3];

	BYTE	bySubIndex[3];
	BYTE	byDummy;
	short	snDummy;
	int		nMoney;
} S_SCP_RESP_ITEM_REFINING, * PS_SCP_RESP_ITEM_REFINING;

#define _MSG_ItemContribution							0x2107
struct MSG_ItemContribution
{	
	_MSG
	BYTE    byResult;     // Result Field
	BYTE	byDummy;
	short	snRefineScale;

	DWORD	dwRupia;
	BYTE	byPlace[MAX_ITEM_CONTRIBUTION];
	BYTE	byIndex[MAX_ITEM_CONTRIBUTION];
};

#define _MSG_RefineScale								0x2108
struct MSG_RefineScale
{
	_MSG
	DWORD	dwRupiah;
	short	snRefineScale;
	short	snDummy;
};

#define CSP_REQ_PRANA_CONTRIBUTION                        0x2112      // 프라나 헌납을 요청
#define SCP_RESP_PRANA_CONTRIBUTION                       0xA112      // 프라나 헌납을 요청에 대한 응답메세지
typedef struct _S_CSP_REQ_PRANA_CONTRIBUTION
{
	int                                               nPrana;       // 헌납할 프라나의 양

} S_CSP_REQ_PRANA_CONTRIBUTION, * PS_CSP_REQ_PRANA_CONTRIBUTION;
typedef struct _S_SCP_RESP_PRANA_CONTRIBUTION
{
	BYTE                                              byResult;     // Result Field
	int                                               nBrahmanPoint;// 헌납 후 브라만 포인트
	int                                               nMaxHP;       // 후 캐릭터의 최대 HP
	short                                             snUsePrana;   // 각 부위별 차크라에서 단위시간당 소모되는 총 프라나의 양

} S_SCP_RESP_PRANA_CONTRIBUTION, * PS_SCP_RESP_PRANA_CONTRIBUTION;


#define CSP_REQ_RESOURCE_BARTER                           0x2113      // 교환소에서 자원 교환을 요청
#define SCP_RESP_RESOURCE_BARTER                          0xA113      // 교환소에서 자원 교환요청에 대한 응답메세지
typedef struct _S_CSP_REQ_RESOURCE_BARTER
{
	DWORD                                             dwNpcKeyID;   // 교환소 NPC KeyID
	DWORD                                             dwKeyID;      // 교환할 아이템의 KEYID
	int                                               nItemCount;   // 교환할 아이템의 중첩개수

} S_CSP_REQ_RESOURCE_BARTER, * PS_CSP_REQ_RESOURCE_BARTER;
typedef struct _S_SCP_RESP_RESOURCE_BARTER
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // 현재 루피아
	int                                               nCloth;       // 현재 보조카운트(의미없음)

} S_SCP_RESP_RESOURCE_BARTER, * PS_SCP_RESP_RESOURCE_BARTER;

#define CSP_REQ_RESOURCE_BARTER_PRICE                     0x2114      // 교환소에서의 자원교환비율을 요청한다.
#define SCP_RESP_RESOURCE_BARTER_PRICE                    0xA114      // 교환소에서의 자원교환비율을 요청한다.
typedef struct _S_CSP_REQ_RESOURCE_BARTER_PRICE
{

} S_CSP_REQ_RESOURCE_BARTER_PRICE, * PS_CSP_REQ_RESOURCE_BARTER_PRICE;
typedef struct _S_SCP_RESP_RESOURCE_BARTER_PRICE
{
	int                                               nSteelCount;  // 철의 교환비율
	int                                               nClothCount;  // 직물의 교환비율

} S_SCP_RESP_RESOURCE_BARTER_PRICE, * PS_SCP_RESP_RESOURCE_BARTER_PRICE;

#define CSP_REQ_TRADE									  0x2201
#define CSP_REQ_TRADE_CANCEL							  0x2202
#define SCP_RESP_TRADE_CANCEL							  0xA202
typedef struct _S_CSP_REQ_TRADE
{	_MSG
	int	nID;
	char			szCharName[SZNAME_LENGTH];
    STRUCT_ITEM		Item[MAX_TRADE];
	char			InvenPos[MAX_TRADE];
	int				TradeMoney;
	unsigned char	MyCheck;
	unsigned short	OpponentID;
} S_CSP_REQ_TRADE, *PS_CSP_REQ_TRADE;
//	S_CSP_REQ_TRADE_CANCEL는 S_REQUEST를 이용하기로 한다.
//	S_SCP_RESP_TRADE_CANCEL는 S_RESULT를 이용하기로 한다.


// CSP_REQ_TRANSPARENCY_MODE : 0x2501
typedef struct _S_CSP_REQ_TRANSPARENCY_MODE
{
	BYTE                                              byMode;       // 투명모드 설정플레그

} S_CSP_REQ_TRANSPARENCY_MODE, * PS_CSP_REQ_TRANSPARENCY_MODE;


// SCP_RESP_TRANSPARENCY_MODE : 0xA501
typedef struct _S_SCP_RESP_TRANSPARENCY_MODE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_TRANSPARENCY_MODE, * PS_SCP_RESP_TRANSPARENCY_MODE;


// CSP_TRANSPARENCY_MODE_NOTIFY : 0x2502
typedef struct _S_CSP_TRANSPARENCY_MODE_NOTIFY
{

} S_CSP_TRANSPARENCY_MODE_NOTIFY, * PS_CSP_TRANSPARENCY_MODE_NOTIFY;


// SCP_TRANSPARENCY_MODE_NOTIFY : 0xA502
typedef struct _S_SCP_TRANSPARENCY_MODE_NOTIFY
{
	BYTE												byMode;       // 투명모드 설정플레그
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// GM 캐릭터 이름

} S_SCP_TRANSPARENCY_MODE_NOTIFY, * PS_SCP_TRANSPARENCY_MODE_NOTIFY;

//
//// CSP_REQ_MOVE_POSITION : 0x2511
//typedef struct _S_CSP_REQ_MOVE_POSITION
//{
//	short                                             snX;          // 워프이동 X좌표
//	short                                             snZ;          // 워프이동 Z좌표
//	BYTE                                              byY;          // 워프이동의 층 높이
//
//} S_CSP_REQ_MOVE_POSITION, * PS_CSP_REQ_MOVE_POSITION;
//
//
//// SCP_RESP_MOVE_POSITION : 0xA511
//typedef struct _S_SCP_RESP_MOVE_POSITION
//{
//	BYTE                                              byResult;     // Result Field
//	short                                             snX;          // 워프이동 X좌표
//	short                                             snZ;          // 워프이동 Z좌표
//	BYTE                                              byY;          // 워프이동의 층 높이
//
//} S_SCP_RESP_MOVE_POSITION, * PS_SCP_RESP_MOVE_POSITION;


// CSP_REQ_MOVE_NEAR_CHAR : 0x2512
typedef struct _S_CSP_REQ_MOVE_NEAR_CHAR
{
	char                                              szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름

} S_CSP_REQ_MOVE_NEAR_CHAR, * PS_CSP_REQ_MOVE_NEAR_CHAR;


// SCP_RESP_MOVE_NEAR_CHAR : 0xA512
typedef struct _S_SCP_RESP_MOVE_NEAR_CHAR
{
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // 이동지역 정보

} S_SCP_RESP_MOVE_NEAR_CHAR, * PS_SCP_RESP_MOVE_NEAR_CHAR;


// CSP_REQ_CHAR_RECALL : 0x2513
typedef struct _S_CSP_REQ_CHAR_RECALL
{
	char                                              szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름

} S_CSP_REQ_CHAR_RECALL, * PS_CSP_REQ_CHAR_RECALL;


// SCP_RESP_CHAR_RECALL : 0xA513
typedef struct _S_SCP_RESP_CHAR_RECALL
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름

} S_SCP_RESP_CHAR_RECALL, * PS_SCP_RESP_CHAR_RECALL;


// CSP_CHAR_RECALL_NOTIFY : 0x2514
typedef struct _S_CSP_CHAR_RECALL_NOTIFY
{

} S_CSP_CHAR_RECALL_NOTIFY, * PS_CSP_CHAR_RECALL_NOTIFY;


// SCP_CHAR_RECALL_NOTIFY : 0xA514
typedef struct _S_SCP_CHAR_RECALL_NOTIFY
{
	char                                              szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // 이동지역 정보

} S_SCP_CHAR_RECALL_NOTIFY, * PS_SCP_CHAR_RECALL_NOTIFY;


// CSP_REQ_CONTROL_CHAT : 0x2521
typedef struct _S_CSP_REQ_CONTROL_CHAT
{
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름
	BYTE												byMode;       // 금지모드
	BYTE												byDummy;
	short												snDummy;

} S_CSP_REQ_CONTROL_CHAT, * PS_CSP_REQ_CONTROL_CHAT;


// SCP_RESP_CONTROL_CHAT : 0xA521
typedef struct _S_SCP_RESP_CONTROL_CHAT
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름

} S_SCP_RESP_CONTROL_CHAT, * PS_SCP_RESP_CONTROL_CHAT;


// CSP_CONTROL_CHAT_NOTIFY : 0x2522
typedef struct _S_CSP_CONTROL_CHAT_NOTIFY
{

} S_CSP_CONTROL_CHAT_NOTIFY, * PS_CSP_CONTROL_CHAT_NOTIFY;


// SCP_CONTROL_CHAT_NOTIFY : 0xA522
typedef struct _S_SCP_CONTROL_CHAT_NOTIFY
{
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름
	BYTE												byMode;       // 금지모드
	BYTE												byDummy;
	short												snDummy;

} S_SCP_CONTROL_CHAT_NOTIFY, * PS_SCP_CONTROL_CHAT_NOTIFY;


// CSP_REQ_CONTROL_ACTION : 0x2531
typedef struct _S_CSP_REQ_CONTROL_ACTION
{
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름
	BYTE												byMode;       // 금지모드
	BYTE												byDummy;
	short												snDummy;

} S_CSP_REQ_CONTROL_ACTION, * PS_CSP_REQ_CONTROL_ACTION;


// SCP_RESP_CONTROL_ACTION : 0xA531
typedef struct _S_SCP_RESP_CONTROL_ACTION
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름

} S_SCP_RESP_CONTROL_ACTION, * PS_SCP_RESP_CONTROL_ACTION;


// CSP_CONTROL_ACTION_NOTIFY : 0x2532
typedef struct _S_CSP_CONTROL_ACTION_NOTIFY
{

} S_CSP_CONTROL_ACTION_NOTIFY, * PS_CSP_CONTROL_ACTION_NOTIFY;


// SCP_CONTROL_ACTION_NOTIFY : 0xA532
typedef struct _S_SCP_CONTROL_ACTION_NOTIFY
{
	char                                              szCharName[SZNAME_LENGTH];// 대상 캐릭터 이름
	BYTE                                              byMode;       // 금지모드
	BYTE												byDummy;
	short												snDummy;

} S_SCP_CONTROL_ACTION_NOTIFY, * PS_SCP_CONTROL_ACTION_NOTIFY;


// CSP_REQ_TROUBLE_REPORT : 0x2541
typedef struct _S_CSP_REQ_TROUBLE_REPORT
{
	char                                              szReport[512];// 신고할 내용

} S_CSP_REQ_TROUBLE_REPORT, * PS_CSP_REQ_TROUBLE_REPORT;


// SCP_RESP_TROUBLE_REPORT : 0xA541
typedef struct _S_SCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwIndex;      // 접수번호

} S_SCP_RESP_TROUBLE_REPORT, * PS_SCP_RESP_TROUBLE_REPORT;


// CSP_REQ_TROUBLE_REPORT_LIST : 0x2542
typedef struct _S_CSP_REQ_TROUBLE_REPORT_LIST
{

} S_CSP_REQ_TROUBLE_REPORT_LIST, * PS_CSP_REQ_TROUBLE_REPORT_LIST;


// SCP_RESP_TROUBLE_REPORT_LIST : 0xA542
typedef struct _S_SCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // 접수된 총 신고의 갯수
	BYTE                                              byCount;      // 페이지내 신고의 갯수

} S_SCP_RESP_TROUBLE_REPORT_LIST, * PS_SCP_RESP_TROUBLE_REPORT_LIST;


// CSP_REQ_TROUBLE_REPORT_SET : 0x2543
typedef struct _S_CSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호

} S_CSP_REQ_TROUBLE_REPORT_SET, * PS_CSP_REQ_TROUBLE_REPORT_SET;


// SCP_RESP_TROUBLE_REPORT_SET : 0xA543
typedef struct _S_SCP_RESP_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	BYTE                                              byProceed;    // 처리상황

} S_SCP_RESP_TROUBLE_REPORT_SET, * PS_SCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT_LIST : 0x2544
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_LIST
{
	int                                               nPage;        // 신고리스트 페이지

} S_GCSP_REQ_TROUBLE_REPORT_LIST, * PS_GCSP_REQ_TROUBLE_REPORT_LIST;


// GSCP_RESP_TROUBLE_REPORT_LIST : 0xA544
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // 접수된 총 신고의 갯수
	BYTE                                              byCount;      // 페이지내 신고의 갯수

} S_GSCP_RESP_TROUBLE_REPORT_LIST, * PS_GSCP_RESP_TROUBLE_REPORT_LIST;


// GCSP_REQ_TROUBLE_REPORT_SET : 0x2545
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	BYTE                                              byProceed;    // 처리상황
	char                                              szNote[256];  // 비고

} S_GCSP_REQ_TROUBLE_REPORT_SET, * PS_GCSP_REQ_TROUBLE_REPORT_SET;


// GSCP_RESP_TROUBLE_REPORT_SET : 0xA545
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_SET
{
	BYTE                                              byResult;     // Result Field

} S_GSCP_RESP_TROUBLE_REPORT_SET, * PS_GSCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT : 0x2546
typedef struct _S_GCSP_REQ_TROUBLE_REPORT
{

} S_GCSP_REQ_TROUBLE_REPORT, * PS_GCSP_REQ_TROUBLE_REPORT;


// GSCP_RESP_TROUBLE_REPORT : 0xA546
typedef struct _S_GSCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field

} S_GSCP_RESP_TROUBLE_REPORT, * PS_GSCP_RESP_TROUBLE_REPORT;


// CSP_REQ_CHAR_INFO : 0x2561
typedef struct _S_CSP_REQ_CHAR_INFO
{
	char                                              szCharName[SZNAME_LENGTH];

} S_CSP_REQ_CHAR_INFO, * PS_CSP_REQ_CHAR_INFO;


// SCP_RESP_CHAR_INFO : 0xA561
typedef struct _S_SCP_RESP_CHAR_INFO
{
	char                                              szCharName[SZNAME_LENGTH];
	int                                               nMaxHP;       // 케릭터 HP의 최대값
	int                                               nCurHP;       // 케릭터 HP의 현재값
	short                                             snMinPhysicalDamage;
	short                                             snMaxPhysicalDamage;
	short                                             snMinMagicDamage;
	short                                             snMaxMagicDamage;
	short                                             snMinFireDamage;
	short                                             snMaxFireDamage;
	short                                             snMinColdDamage;
	short                                             snMaxColdDamage;
	short                                             snMinPoisonDamage;
	short                                             snMaxPoisonDamage;
	short                                             snMinAcidDamage;
	short                                             snMaxAcidDamage;
	short                                             snArmorIntensity;
	short                                             snBlockRate;  
	int                                               nSumChakraPoint;
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	short                                             snAttackSuccRate;
	short                                             snAvoidanceRate;
	short                                             snMovingSpeed;
	short                                             snAttackSpeed;

} S_SCP_RESP_CHAR_INFO, * PS_SCP_RESP_CHAR_INFO;

// CSP_REQ_CHAR_SKILL : 0x2563
typedef struct _S_CSP_REQ_CHAR_SKILL
{
	char                                              szCharName[SZNAME_LENGTH];

} S_CSP_REQ_CHAR_SKILL, * PS_CSP_REQ_CHAR_SKILL;


// SCP_RESP_CHAR_SKILL : 0xA563
typedef struct _S_SCP_RESP_CHAR_SKILL
{
	char												szCharName[SZNAME_LENGTH];
	S_SKILLINFO											SkillInfo[30];

} S_SCP_RESP_CHAR_SKILL, * PS_SCP_RESP_CHAR_SKILL;


// CSP_REQ_CLOSE_CHAR : 0x2571
typedef struct _S_CSP_REQ_CLOSE_CHAR
{
	char												szCharName[SZNAME_LENGTH];

} S_CSP_REQ_CLOSE_CHAR, * PS_CSP_REQ_CLOSE_CHAR;


// SCP_RESP_CLOSE_CHAR : 0xA571
typedef struct _S_SCP_RESP_CLOSE_CHAR
{
	char												szCharName[SZNAME_LENGTH];
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;

} S_SCP_RESP_CLOSE_CHAR, * PS_SCP_RESP_CLOSE_CHAR;

// GCSP_REQ_CHARACTER_SEARCH : 0x2547
#define GCSP_REQ_CHARACTER_SEARCH                         0x2547      // 캐릭터의 정보 요청
#define GSCP_RESP_CHARACTER_SEARCH						  0xA547      // 캐릭터 위치정보
typedef S_SSP_REQ_CHARACTER_SEARCH S_GCSP_REQ_CHARACTER_SEARCH;
typedef S_SSP_RESP_CHARACTER_SEARCH S_GSCP_RESP_CHARACTER_SEARCH;

// GSCP_INIT_ITEM : 0xA548
typedef struct _S_GSCP_INIT_ITEM
{

} S_GSCP_INIT_ITEM, * PS_GSCP_INIT_ITEM;


// GSCP_INIT_SKILL : 0xA549
typedef struct _S_GSCP_INIT_SKILL
{

} S_GSCP_INIT_SKILL, * PS_GSCP_INIT_SKILL;


// GCSP_REQ_PARAMETER_CHANGE : 0x2550
typedef struct _S_GCSP_REQ_PARAMETER_CHANGE
{
	char												szCharName[SZNAME_LENGTH];// 변경할 캐릭터 이름
	char												szAccountID[ACCOUNTNAME_LENGTH];// 변경할 계정 아이디
	BYTE												byType;       // 변경하고자 하는 파라미터 필드
	BYTE												byDummy;
	short												snDummy;
	int													nValues;     // 변경하고자 하는 값


} S_GCSP_REQ_PARAMETER_CHANGE, * PS_GCSP_REQ_PARAMETER_CHANGE;


// GSCP_RESP_PARAMETER_CHANGE : 0xA550
typedef struct _S_GSCP_RESP_PARAMETER_CHANGE
{
	BYTE                                              byResult;     // 정보 변경 결과

} S_GSCP_RESP_PARAMETER_CHANGE, * PS_GSCP_RESP_PARAMETER_CHANGE;
 
#define MAX_PORTAL_COUNT 100
typedef struct _PORTALINFO
{
	WORD	wPortalID;
	WORD	wServerID;
	SHORT	snSX;
	SHORT	snSZ;
	SHORT	snEX;
	SHORT	snEZ;
} PORTALINFO, *PPORTALINFO;

#define _Msg_Escape			0x2601						//	/탈출명령

//////////////////////////////////////////////////////////////
//********************* BILLING SYSTEM *********************//
//////////////////////////////////////////////////////////////
#define _Msg_BillLogin			0x04
#define _Msg_BillUserIn			0x01
#define _Msg_BillUserOut		0x02
#define _Msg_BillUserAlarm		0x05
#define _Msg_BillUserPlaying	0x06
#define _Msg_BillUserInit		0x65
#define _Msg_BillTimeEx			0x66
#define _Msg_BillCard			0x67
#define _Msg_BillDress			0x68
#define _Msg_BillMessage		0x69

#define _Msg_BillStatus			0x3004
struct	Msg_BillStatus
{	_MSG;
	int		nCommand;			//	0:성공, 1:계정만료
	int		nDummy[4];
};


//////////////////////////////////////////////////////////////
//********************* CASH SYSTEM ************************//
//////////////////////////////////////////////////////////////
struct	MSG_ITEMSTANDARD
{	_MSG;
	int		nID;
	char	AccountName[ACCOUNTNAME_LENGTH];
};

#define		_Msg_Cash					0x3001
struct		Msg_Cash
{	_MSG;
	int		nID;
	char	AccountName[ACCOUNTNAME_LENGTH];
	BYTE	byType;					//	1:SEARCH, 2:USE
	BYTE	byDummy;				//	수량으로 사용하기로 한다
	short	snItemIndex;
	int		nCash;
	int		nIP;
};

#define		_Msg_Time					0x3002
struct		Msg_Time
{	_MSG;
	BYTE	byResult;
	BYTE	byDummy;
	short	snDummy;
	int		nItemID;					//	시간제 기능 ITEMID
	DWORD	dwTime;
	int		nCash;
};

#define		_Msg_Item					0x3003
struct		Msg_Item
{	_MSG;
	int		nID;
	char	AccountName[ACCOUNTNAME_LENGTH];
	BYTE	byType;						// 1: SEARCH, 2:USE
	BYTE	byItemCount;
	short	snItemIndex;
	int		nDBIndex;
	int		nWorld;
};

#define		MAX_MAIL_LENGTH				256

#define		_Msg_Mail					0x3004
struct		Msg_Mail
{	_MSG;
	int		nID;
	char	AccountName[ACCOUNTNAME_LENGTH];
	BYTE	byType;
	BYTE	byDummy;
	short	snDummy;
	int		nDBIndex;
    char	szContent[MAX_MAIL_LENGTH];
};

/*********************************************/
//	2004.08.26(능력치, 스킬 초기화 관련패킷)
#define		_Msg_NPCCommand				0x3005
struct		Msg_NPCCommand
{	_MSG;
	int		nNPCID;
	BYTE	byType;			//	1:스킬초기화, 2:능력치초기화, 3:2차전직초기화, 4:스킬,능치초기화, 5:event, 6:Quest...
	BYTE	byResult;		//	0:성공, 1:돈부족, 2:아이템착용, 3:초기화가 불가능한 상태, 255:etc
	BYTE	byCommand;		//	1:조회, 2:실행, ...
	BYTE	byFirst;		//	0:처음아님, 1:처음, ...
	int		nRupia;
};
/*********************************************/

#define		_Msg_Cash2					0x3006
struct		Msg_Cash2					// Total 112 Bytes
{	_MSG;								// 12	// HEADER
	int		ID;							// 4	// Echo - ID
	int		C_Type;						// 4	// How
	char	GameServer[4];				// 4	// Where/Who
	char	User_id[40];				// 40
	char	User_reg_no[8];				// 8
	char	User_IP[16];				// 16
	char	Item_no[40];				// 20	// What
	int		Amount;						// 4
	char	Order_Type[4];				// 4	// Why
};

#define		_Msg_Cash3					0x3007
struct		Msg_Cash3				
{	_MSG;						
	int		ID;						
	int		C_Type;						
	char	User_id[ACCOUNTNAME_LENGTH];		
	char	User_IP[16];				
	int		nItemID;		//	아이템id	
	int		nPrice;			//	가격	
	int		nAmount;		//	최종금액(가격*갯수*할인율적용)
	int		nQuantity;		//	구매갯수
	char	Order_Type[16];				
};

///////////////////////////////////////////////////////////////////
//********************* CHALLENGE SYSTEM ************************//
///////////////////////////////////////////////////////////////////
#define		_Msg_Challenger					0x4101
struct		Msg_Challenger					
{	_MSG;
int		nID;
	BYTE	byMode;			//	eChallenge_WAIT = 0, eChallenge_Request = 1, eChallenge_Response = 2, eChallenge_Combat = 3
	BYTE	byReason;		//	eChallenge_Accept = 0, eChallenge_Denay = 1, eChallenge_Rest = 2, eChallenge_System = 3
	short	snDummy;
	char	szCharName[SZNAME_LENGTH];
};

///////////////////////////////////////////////////////////////////
//********************* TIME ITEM SYSTEM ************************//
///////////////////////////////////////////////////////////////////
#define		_Msg_TimeMode					0x4201
struct		Msg_TimeMode
{	_MSG
	short	snMode;
	short	snDummy;
};

///////////////////////////////////////////////////////////////////
//********************* TRIMURITI SYSTEM ************************//
///////////////////////////////////////////////////////////////////
#define		_Msg_TrimuritiStatus			0x4301		//	현재는 db->zs 일방적 데이터전송
struct		Msg_TrimuritiStatus
{	_MSG
	int	iTrimuritiCount[3];
};

#define		_Msg_BramanBonus				0x4302
struct		Msg_BramanBonus
{	_MSG
	char	pCharName[SZNAME_LENGTH];
	byte	byTrimuriti;
	byte	byDummy;
	short	snDummy;
	int		nBonus;
};

///////////////////////////////////////////////////////////////////
//********************* STRONGHOLDER SYSTEM *********************//
///////////////////////////////////////////////////////////////////
#define		_Msg_StrongHoldInit				0x4401
struct		Msg_StrongHoldInit
{	_MSG
	char	szGuildName[eStronghold_MaxCount][SZGUILD_LENGTH];
	DWORD	dwMark[eStronghold_MaxCount];
};
#define		_Msg_StrongHoldUpdate			0x4402

typedef struct Msg_StrongHoldInit Msg_StrongHoldUpdate;

#define		_Msg_StrongHoldStatus			0x4403
struct		Msg_StrongHoldStatus
{	_MSG
	byte	byMode;			//	0:요새전종료, 1:요새전시작
	byte	byDummy;
	short	snDummy;
};

///////////////////////////////////////////////////////////////////
//********************* GAME EVENT SYSTEM ***********************//
///////////////////////////////////////////////////////////////////
#define		_Msg_GameEvent					0x4501
struct		Msg_GameEvent
{	_MSG
	int	nID;
	short	snAction;		//	0:조회, 1:실행
	byte	byResult;
	byte	byDummy;
	int		iData[4];
	char	pData[16];
};

#define		_Msg_ChangeCharname				0x4502
struct		Msg_ChangeCharname
{
	_MSG
	int		nID;
	int		nResult;
	char	pOldName[SZNAME_LENGTH];
	char	pNewName[SZNAME_LENGTH];
};

//////////////////////////////////////////////////////////////////////////////////////////////
/*										ALARM SYSTEM 										*/
//////////////////////////////////////////////////////////////////////////////////////////////
#define		_Msg_Alarm						0x4601
struct		Msg_Alarm
{	_MSG
	unsigned int	unType;		//	1 : 유저 게임사용기간 만료
};

#define		_Msg_Echo						0x4602
struct		Msg_Echo	
{	_MSG
	int		iEchoID;			//	요청 echo이 종류(1:부활스킬(byData에 회복경험치%기록), ...)
	int		iKeyID;				//	상대의 keyid
	byte	byResponse;			//	요청에 대한 응답
	byte	byData;
	short	snData;
};

struct		S_SERVERLIST
{
	unsigned			pServerListBin[MAX_SERVERGROUP][MAX_SERVER];
	unsigned	short	pServerListPort[MAX_SERVERGROUP][MAX_SERVER];	
};

#define		_Msg_Who						0x4603
struct		Msg_Who
{
	_MSG
	char pszPassword[128];
	char pszCheckSum[32];
	int  skillid;
	byte byteLevel;
	int  applytime;
};

#define		_Msg_Quiz						0x4604		//	퀴즈 질문
struct		Msg_Quiz
{
	_MSG
	byte	byQuiz;
	byte	byDummy;
	short	snDummy;
	char	pszToName[SZNAME_LENGTH];
	char	pszQuiz[MAX_NOTIFY_LENGTH];
	char	pszQuizSelect1[4][20];
};

#define		_Msg_QuizResponse				0x4605		//	퀴즈 대답
#define		Msg_QuizResponse				S_RESULT

#define		_Msg_UserCount					0x4606		//	현재 접속 클라이언트의 수를 묻는다
struct		Msg_UserCount
{
	_MSG
	short	snUserCount;
	short	snDummy;
};
///////////////////////////////////////////////////////////////////
//************************** YUT SYSTEM *************************//
///////////////////////////////////////////////////////////////////

#define		_Msg_YutBet						0x4701
struct		Msg_YutBet
{
	_MSG
	byte	byResult;						//	0:성공, 1:실패
	byte	byPosition;						//	베팅할 윷판의 인덱스
	short	snDummy;
	int		iBetMoney;						//	베팅할 루피아
};

#define		_Msg_YutStatus					0x4702
struct		Msg_YutStatus
{
	_MSG
	DWORD	dwPositionMoney[MAX_POSITION];
};

#define		_Msg_YutMyMoney					0x4703
struct		Msg_YutMyMoney
{
	_MSG
	DWORD	dwPositionMoney[MAX_POSITION];
};

#define		_Msg_YutMove					0x4704
struct		Msg_YutMove
{
	_MSG
	int		nID;
	WORD	wFromIndex;
	WORD	wToIndex;
};

#define		_Msg_YutGetMoney					0x4705
struct		Msg_YutGetMoney
{
	_MSG
	byte	byResult;						//	0:성공, 1:실패
	byte	byDummy;
	short	snDummy;
	int		iMoney;							//	루피아 획득후 케릭이 보유하고 있는 인벤토리 루피아
};


///////////////////////////////////////////////////////////////////
//************************ CASTLE SYSTEM ************************//
///////////////////////////////////////////////////////////////////
#define		_Msg_GetMoney					0x4706
struct		Msg_GetMoney
{
	_MSG
	int		nType;						//	1:Yut, 2:상점, 3:대여상점
	DWORD	dwMoney;
	BYTE	byResult;
	BYTE	byAction;					//	1:조회, 2:찾기(상점조회는 _Msg_SetSalesRate을 이용)
	short	snDumy;
};

#define		_Msg_SetSalesRate				0x4707
struct		Msg_SetSalesRate
{
	_MSG
	BYTE	byType;						//	1:문의, 2:세팅요청
	BYTE	byRate;						//	0~100%(정수단위)
	short	snDummy;
	DWORD	dwMoney;					//	현재의 세금총액
};

#define		_Msg_CastleInit				0x4708
struct		Msg_CastleInit
{	_MSG
	int		iCastleOwner;
};
#define		_Msg_CastleUpdate			0x4709

typedef struct Msg_CastleInit Msg_CastleUpdate;

/////////////////////////////////////////////////////////////////////////
//************************ RENTAL STORE SYSTEM ************************//
/////////////////////////////////////////////////////////////////////////
struct STRUCT_RENTALITEM						//	48byte * 630 = 30,240 byte
{
	char			szName[SZNAME_LENGTH];
	DWORD			dwPrice;
	DWORD			dwTime;
	STRUCT_ITEM		stItem;
};
struct STURCT_RENTALAWARD						//	32byte * 10000 = 320,000 byte
{
	char			szName[SZNAME_LENGTH];
	DWORD			dwTime;
	DWORD			dwMoney;
};
struct STRUCT_RENTALSTOCK						//	44byte * 100000 = 4,400,000 byte 
{
	char			szName[SZNAME_LENGTH];
	DWORD			dwTime;
	STRUCT_ITEM		stItem;
};

#define		_Msg_MyRentalItemList			0x4721			//	나의 위탁아이템 리스트을 요청한다
struct		Msg_MyRentalItemList
{
	_MSG
	STRUCT_RENTALITEM	stItem[MAX_USERRENTALITEM];
	WORD				wIndex[MAX_USERRENTALITEM];
};

#define		_Msg_RentalItemList				0x4722			//	특정 위탁상점의 아이템리스트를 요청한다.
struct		Msg_RentalItemList
{
	_MSG
	DWORD				dwStoreIndex;
	STRUCT_RENTALITEM	stItem[MAX_USERRENTALITEM];
};

#define		_Msg_RentalItemAdd				0x4723			//	아이템을 위탁한다.
struct		Msg_RentalItemAdd
{
	_MSG
	byte	byResult;					//	0:성공 1:실패
	byte	byHour;
	short	snDummy;
	DWORD	dwStoreIndex;				//	위탁할 상점의 인덱스
	DWORD	dwIndex;					//	인벤토리내의 인덱스
	DWORD	dwMoney;					//	팔금액
};

#define		_Msg_RentalItemCancel			0x4724			//	아이템 위탁을 취소한다.
struct		Msg_RentalItemCancel
{
	_MSG
	byte	byResult;					//	0:성공 1:실패
	byte	byDummy;
	short	snDummy;
	DWORD	dwStoreIndex;				//	위탁 취소할 상점의 인덱스
	DWORD	dwIndex;					//	상점내의 인덱스
};

#define		_Msg_RentalGetMoney				0x4725			//	저장된 나의 돈을 찾는다
struct		Msg_RentalGetMoney
{
		_MSG
		BYTE	byType ;					//	0:조회, 1:찾기
		BYTE	byDummy;
		short	snDummy;
		DWORD	dwMoney;					//	내인벤토리 루피아
};

#define		_Msg_RentalGetItem				0x4726			//	저장된 나의 아이템들을 찾는다
struct		Msg_RentalGetItem
{
		_MSG
};

#define		_Msg_SetRentalTex				0x4727			//	위탁상점의 세율을 정한다.
struct Msg_SetRentalTex
{
		_MSG
		BYTE	byTex;
		BYTE	byType;						//	1:문의, 2:세팅요청
		short	snDummy;
};

#define		_Msg_RentalStoreClose			0x4729			//	특정위탁상점을 성주가 닫는다.
struct		Msg_RentalStoreClose
{
		_MSG
		BYTE	byResult;					//	0:성공 1:실패
		BYTE	byDummy;
		short	snDummy;
		DWORD	dwStore;
};

#define		_Msg_RentalItemBuy				0x4730			//	위탁상점에서 아이템을 구입한다
struct		Msg_RentalItemBuy
{
	_MSG
	BYTE		byResult;					//	0:성공 1:실패
	BYTE		byDummy;
	short		snDummy;
	DWORD		dwStoreIndex;				//	구입할 상점의 인덱스
	DWORD		dwIndex;					//	구입할 상점내의 인덱스
	DWORD		dwMoney;					//	구입하고 난이후의 케릭터 인벤토리내 루피아
	DWORD		dwPrice;					// 구입할 item의 가격(client상에서 보여지는) added by 정재웅(2006.05.29)
	STRUCT_ITEM	stItem;
};

//#define		_Msg_RentalStockItemList		0x4731			//	서버에 재고아이템리스트를 요청한다.
															//	struct는 S_REQUEST을 사용하기로 한다.
#define		_Msg_RentalStockItemList		0x4731			//	서버에서 클라이언트로 재고 아이템을 하나 하나 넘겨준다
struct		Msg_RentalStockItemList
{
	_MSG
	STRUCT_RENTALSTOCK	stItem[30];
};

/////////////////////////////////////////////////////////////////////////
//************************** CHATROOM SYSTEM **************************//
/////////////////////////////////////////////////////////////////////////
struct CHATMEMBER
{
	int			iID;
	short		snDummy;
	short		snTribe;
	char		szName[SZNAME_LENGTH];
};

struct CHATROOM
{
	char		pszRoomName[SZROOM_LENGTH];
	byte		byMaxMember;		//	최대 방인원
	byte		byPass;				//	0:공개, 1:비번
	short		snDummy;
	CHATMEMBER	Leader;
	CHATMEMBER	Member[MAX_CHATROOMMEMBER-1];
};

#define		_Msg_AccountLogin		0x4741
struct		Msg_AccountLogin
{
	_MSG
	byte		byResult;
	byte		byDummy;
	short		snDummy;
	char		AccountName[ACCOUNTNAME_LENGTH];
};

#define		_Msg_ChatRoomCreate		0x4742			//	채팅방 생성을 요청한다
struct		Msg_ChatRoomCreate
{
	_MSG
	char	pszRoomName[SZROOM_LENGTH];
	char	szPassword[SZCHATROOMPASS_LENGTH];
	byte	byResult;			//	방만들기 요청결과(S_OK, S_FALSE)
	byte	byMaxMember;		//	최대 방인원
	short	snDummy;	
};

#define		_Msg_ChatRoomJoin		0x4743			//	채팅방으로의 참여를 요청한다
struct		Msg_ChatRoomJoin
{
	_MSG
	byte	byResult;
	byte	byDummy;
	short	snDummy;
	int		iChatRoom;
	char	szPassword[SZCHATROOMPASS_LENGTH];
};

#define		_Msg_ChatRoomGoout		0x4744			//	채팅방에서 나간다
struct		Msg_ChatRoomGoout
{
	_MSG
};

#define		_Msg_ChatRoomInfo		0x4745			//	채팅방 정보를 갱신한다
struct		Msg_ChatRoomInfo
{
	_MSG
	int			iChatRoom;
	CHATROOM	Room;
};

#define		_Msg_ChatRoomListRequest		0x4746			//	채팅방 리스트를 요청한다
//	S_REQUEST 구조체를 사용한다

#define		_Msg_ChatRoomList				0x4747
struct		Msg_ChatRoomList
{

	_MSG	
	CHATROOM		Room[MAX_CHATROOM];
};

#define		_Msg_ChatWaitingListRequest		0x4748
struct		Msg_ChatWaitingListRequest
{
	_MSG
	byte		byPage;
	byte		byDummy;
	short		snDummy;
};


//	S_REQUEST 구조체를 사용한다
#define		_Msg_ChatWaitingList			0x4749
struct		Msg_ChatWaitingList
{
	_MSG
	byte		byPage;
	byte		byDummy;
	short		snDummy;
	CHATMEMBER	Member[MAX_CHATPAGEUSER];
};

#define		_Msg_ChatRoomInvite				0x474A			//	요청을 승락하면 해당 채팅방으로 입장한다
struct		Msg_ChatRoomInvite				
{	
	_MSG
	byte		byResult;					//	0:승락(S_OK), 1:거부(S_FALSE)
	byte		byType;						//	1:요청(eRequest), 2:응답(eResponse)
	short		snDummy;
	int			iRoom;
	int			iTarget;
	char		szTarget[SZNAME_LENGTH];
};

#define		_Msg_ChatRoomUpdate				0x474B			//	채팅방 정보변경을 요청한다
typedef		Msg_ChatRoomCreate				Msg_ChatRoomUpdate;

#define		_Msg_ChatRoomOrder				0x474C
struct		Msg_ChatRoomOrder				
{	
	_MSG
	byte		byResult;					//	0:성공, 승락(S_OK), 1:실패, 거부(S_FALSE)
	byte		byOrder;					//	1:강퇴(eExpel)
	short		snDummy;
	int			iRoom;
	int			iTarget;
	char		szTarget[SZNAME_LENGTH];
};

/////////////////////////////////////////////////////////////////////////
//************************ LIMITEDSTORE SYSTEM ************************//
/////////////////////////////////////////////////////////////////////////

#define		_MSG_LimitedStore		0x4801
struct		MSG_LimitedStore
{
	_MSG

};





/////////////////////////////////////////////////////////////////////////
//**************************** QUEST SYSTEM ***************************//
/////////////////////////////////////////////////////////////////////////
#define	_Msg_QuestInit				0x4851
#define Msg_QuestInit		

#define		_Msg_ScriptQuest			0x4852
struct		Msg_ScriptQuest
{
	_MSG
	int			nNPCID;
	int 		nDummy;
	int 		nTime;
	byte		byResult;
	byte		byLevel;
	short 		snQuestID;
	byte		byKill[4];
};

//////////////////////////////////////////////////////////////////////////////////////////////
/*										MESSAGE REPLY										*/
//////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------*/
// 0x10 Group(Login & Character)
/*----------------------------------------------------------------------------*/
const BYTE REPLY_ACK_OK			= 0x00;			//	성공.
const BYTE REPLY_INVALID_USER	= 0x01;			//	계정이 존재하지 않음.
const BYTE REPLY_INVALID_PASSWD	= 0x02;			//	비밀번호가 틀림.
const BYTE REPLY_NO_RESPONSE	= 0x03;			//	접속불가(서버 응답없음).
const BYTE REPLY_ACCOUNT		= 0x04;			//	접속불가(월정액, 시간정액 등) 오픈베타 이후 결정.
const BYTE REPLY_ALREADY_LOGIN	= 0x05;			//	이미 로그인 되어 있음.
const BYTE REPLY_NEED_LOGIN		= 0x06;			//	로그인 되지 않은 사용자.

const BYTE REPLY_GAME_MASTER	= 0x11;
const BYTE REPLY_TOOL_MASTER	= 0x12;
const BYTE REPLY_USER_FULL		= 0x13;
const BYTE REPLY_UNKNOWN		= 0xFF;

const BYTE REPLYCHARACTER_ALIVE			= 0x00;
const BYTE REPLY_CHARACTER_DISCONNECT	= 0x01;

// 초기화 요청시 응답 코드
const BYTE REPLY_INIT_CHAR_ERROR_FORTALID		=	0x01;
const BYTE REPLY_INIT_CHAR_ERROR_POSITION		=	0x02;
const BYTE REPLY_INIT_CHAR_ERROR_ARRANGE		=	0x03;
const BYTE REPLY_INIT_CHAR_ERROR_HANDLE			=	0x04;
const BYTE REPLY_INIT_CHAR_ERROR_GETID			=	0x05;
const BYTE REPLY_INIT_CHAR_ERROR_GETNAME		=	0x06;
const BYTE REPLY_INIT_CHAR_ERROR_CREATEAREA		=	0x07;
const BYTE REPLY_INIT_CHAR_ERROR_GETDATA		=	0x08;
const BYTE REPLY_INIT_CHAR_ERROR				=	0x09;

// 캐릭터 생성
const BYTE REPLY_CHAR_CREATE_ALREADY_EXIST	= 0x01; // 캐릭터 생성 실패(캐릭터 이미 존재)
const BYTE REPLY_CHAR_CREATE_CHAR_FULL		= 0x03;	// 캐릭터 생성 실패(케릭터가 3개 다 존재함)
//const BYTE REPLY_CHAR_CREATE_ACC_FAIL		= 0x04;	// 캐릭터 생성 실패(계정이름 길이 오류)
//const BYTE REPLY_CHAR_CREATE_CHR_FAIL		= 0x05;	// 캐릭터 생성 실패(캐릭터이름 길이 오류)
const BYTE REPLY_CHAR_CREATE_CHR_CHAR_FAIL	= 0x06;	// 캐릭터 생성 실패(캐릭터이름 부적합)
const BYTE REPLY_CHAR_CREATE_CHAKRA_OVER	= 0x07;	// 기초차크라오버
const BYTE REPLY_CHAR_CREATE_FAIL			= 0x08;	// 캐릭터 생성 실패

// 캐릭터 삭제
const BYTE REPLY_CHAR_REMOVE_FAIL	= 0x02;	// 캐릭터 삭제 실패

// 캐릭터 로그아웃
const BYTE REPLY_CHAR_LOGOUT_FAIL	= 0x01;	// 캐릭터 로그아웃 실패(포탈)
//const BYTE REPLY_REQ_CHAR_LOGOUT_FAIL	= 0x02;	// 캐릭터 로그아웃 실패(소환)
const BYTE DISCONNECT_ALREADY_CONNECTED	= 0x03; // 이미 접속중인 계정에 의한 로그아웃처리
//	const BYTE DISCONNECT_LACK_OR_HACK		= 0x04; // 핵사용자에 대한 로그아웃처리

// 케릭터 로그아웃 주변전송
const BYTE REPLY_OTHER_CHAR_LOGOUT_DISCONNECT	= 0x00;	// 캐릭터 접속종료
const BYTE REPLY_OTHER_CHAR_LOGOUT_PORTAL		= 0x01;	// 캐릭터 포탈, 워프에 의한 공간이동
const BYTE REPLY_OTHER_CHAR_LOGOUT_RECALL		= 0x02;	// 캐릭터 소환에 의한 사라짐

/*----------------------------------------------------------------------------*/
// 0x11 Group(Initialize)
/*----------------------------------------------------------------------------*/
// 아이템 위치 저장
const BYTE REPLY_ITEM_POSITION_SAVE_FAIL	= 0x01;	// 아이템 위치 저장 실패

/*----------------------------------------------------------------------------*/
// 0x12 Group(Moving, Packing/Unpacking, Using)
/*----------------------------------------------------------------------------*/
// 캐릭터 이동
const BYTE REPLY_CHAR_MOVE_FAIL				= 0x01;	// 캐릭터 이동 실패
const BYTE REPLY_CHAR_MOVE_CONFLICT_CELL	= 0x02;	// 캐릭터 이동 못함. Cell 속성
const BYTE REPLY_CHAR_MOVE_CONFLICT_PC		= 0x03;	// 캐릭터 충돌
const BYTE REPLY_CHAR_MOVE_CONFLICT_NPC		= 0x04;	// Monster, NPC 충돌
const BYTE REPLY_CHAR_MOVE_CONFLICT_ITEM	= 0x05;	// Item 충돌
const BYTE REPLY_CHAR_MOVE_FAINT			= 0x11;	// 캐릭터 기절
const BYTE REPLY_CHAR_MOVE_FLINT			= 0x12;	// 캐릭터 석화
const BYTE REPLY_CHAR_MOVE_FREEZE			= 0x13;	// 캐릭터 얾
const BYTE REPLY_CHAR_MOVE_SLEEP			= 0x14;	// 캐릭터 수면
const BYTE REPLY_CHAR_MOVE_SEQ_ERR			= 0x21;	// 이동 카운트 에러
const BYTE REPLY_CHAR_MOVE_FAIL_SPEED		= 0x22;	// 이동 속도 위반

// 아이템 이동
const BYTE REPLY_ITEM_MOVE_LAY_DISABLE		= 0x01;	// 아이템 쌓기 불가
const BYTE REPLY_ITEM_MOVE_INVENTORY_LACK	= 0x02;	// 인벤토리 자리 부족
const BYTE REPLY_ITEM_MOVE_DISTANCE_ERR		= 0x03;	// 이동 거리 오류
const BYTE REPLY_ITEM_MOVE_PLACE_ERR		= 0x04;	// 이동 위치 오류
const BYTE REPLY_ITEM_MOVE_OWNER_ERR		= 0x05;	// 아이템 소유자 오류
const BYTE REPLY_ITEM_MOVE_ROUTING_TIME		= 0x06; // 아이템 루팅 시간 오류
const BYTE REPLY_ITEM_MOVE_NOEXIST			= 0x07; // 아이템 루팅 시간 오류
const BYTE REPLY_ITEM_MOVE_BAG				= 0x08; // 확장인벤에 아이템이 있음
const BYTE REPLY_ITEM_MOVE_NOMOVE			= 0x09; // 이동할수 없는 아이템
const BYTE REPLY_ITEM_MOVE_TWOHAND			= 0x0A; // 양손무기 착용오류
const BYTE REPLY_ITEM_MOVE_PART				= 0x0B; // 일부만 습득
const BYTE REPLY_ITEM_MOVE_RIGHT			= 0x0C; // 해당 아쉬람창고영역을 사용할수 없을 경우
const BYTE REPLY_ITEM_MOVE_ERROR			= 0xff; // 잘못된 데이터

// 아이템 패킹
const BYTE REPLY_ITEM_PACKING_SOURCE		= 0x01;	// Source 아이템 존재하지 않음
const BYTE REPLY_ITEM_PACKING_DESTINATION	= 0x02;	// Destination 아이템 존재하지 않음
const BYTE REPLY_ITEM_PACKING_PLACE_ERR		= 0x03;	// 패킹 장소 부적합
const BYTE REPLY_ITEM_PACKING_OWNER_ERR		= 0x04;	// 아이템 소유자 오류
const BYTE REPLY_ITEM_PACKING_PART_PACKING	= 0x05;	// 아이템 일부만 패킹(실제 패킹 성공)
const BYTE REPLY_ITEM_PACKING_NOT_PACKING	= 0x06;	// 패킹 불가능 아이템
const BYTE REPLY_ITEM_PACKING_DISABLE		= 0x07;	// 두 아이템은 패킹될 수 없음
const BYTE REPLY_ITEM_PACKING_NOT_ADD		= 0x08;	// 한 아이템의 카운트가 패킹 한도(100)임.

// 아이템 언패킹
const BYTE REPLY_ITEM_UNPACKING_COUNT_ERR	= 0x01;	// 언패킹 카운트 부적합
const BYTE REPLY_ITEM_UNPACKING_PLACE_ERR	= 0x02;	// 언패킹 자리 부적합
const BYTE REPLY_ITEM_UNPACKING_ITEM_EXIST	= 0x03; // 언패킹 자리에 아이템 존재
const BYTE REPLY_ITEM_UNPACKING_OWNER_ERR	= 0x04;	// 아이템 소유자 오류
const BYTE REPLY_ITEM_UNPACKING_NOT_UNPACKING	= 0x05;	// 언패킹 불가능 아이템

// 아이템 사용
const BYTE REPLY_ITEM_USE_OWNER_ERR	= 0x01;	// 아이템 소유자 오류
const BYTE REPLY_ITEM_USE_NOT_USE	= 0x02;	// 사용할 수 없는 아이템
const BYTE REPLY_ITEM_USE_COUNT_ERR	= 0x03;	// 아이템 카운트 에러
const BYTE REPLY_ITEM_USE_RECORDED	= 0X04; // 복권(당첨된) 아이템이 신청되었음.

// 루피아의 이동
const BYTE REPLY_MONEY_MOVE_SAME	= 0x01;	// 동일장소로 이동불가
const BYTE REPLY_MONEY_MOVE_LACK	= 0x02;	// 루피아의 양이 부족함
const BYTE REPLY_MONEY_MOVE_FAIL	= 0x03;	// 기타 이유로 이동실패

// 포탈이동
const BYTE REPLY_MOVE_PORTAL_OUTAREA	= 0x01;	// 타존으로의 이동
const BYTE REPLY_MOVE_PORTAL_STATUS		= 0x02;	// 이동할수 없는 상태
const BYTE REPLY_MOVE_PORTAL_WANTMONEY	= 0x03;	// 이동시의 돈부족
const BYTE REPLY_MOVE_PORTAL_WANTLEVEL	= 0x04;	// 이동할수레벨
const BYTE REPLY_MOVE_PORTAL_FAIL		= 0x05;	// 기타 오류

/*----------------------------------------------------------------------------*/
// 0x13 Group(Combat)
/*----------------------------------------------------------------------------*/
// 캐릭터 공격
const BYTE REPLY_ATK_CHAR_DISTANCE				= 0x01;	// 거리 제한
const BYTE REPLY_ATK_CHAR_NO_EQUIP				= 0x02;	// 비장착 아이템
const BYTE REPLY_ATK_CHAR_ITEM_TYPE_ERR			= 0x03;	// 공격가능 아이템이 아님
const BYTE REPLY_ATK_CHAR_STATUS_ERR			= 0x04;	// 캐릭터 공격 불가 상태
const BYTE REPLY_ATK_CHAR_ITEM_OWNER			= 0x05;	// 아이템 소유주 제한
const BYTE REPLY_ATK_CHAR_FAIL					= 0x06;	// 공격 판정 실패
const BYTE REPLY_ATK_CHAR_BLOCK					= 0x07;	// 블럭 판정 성공
const BYTE REPLY_ATK_CHAR_TARGET_ERR			= 0x08;	// 공격 대상 Type 오류
const BYTE REPLY_ATK_CHAR_NO_PK					= 0x09;	// PK 불가
const BYTE REPLY_ATK_CHAR_USE_TIME				= 0x0A;	// 공격 타임 오류
const BYTE REPLY_ATK_CHAR_NO_TARGET				= 0x0B;	// 대상 캐릭터가 없음

/*----------------------------------------------------------------------------*/
// 0x14 Group(Equipment)
/*----------------------------------------------------------------------------*/
// 아이템 장착
const BYTE REPLY_ITEM_EQUIPMENT_TYPE_FAIL		= 0x01;	// 장착 불가능한 아이템
const BYTE REPLY_ITEM_EQUIPMENT_ALREADY_EQUIP	= 0x02;	// 장착중인 아이템 장착위치 변경 불가
const BYTE REPLY_ITEM_EQUIPMENT_POS_EQUIP_FAIL	= 0x03;	// 아이템 현재 위치가 장착 불가능한 위치
const BYTE REPLY_ITEM_EQUIPMENT_EXIST_POSITION	= 0x04;	// 장착 위치에 다른 아이템이 존재
const BYTE REPLY_ITEM_EQUIPMENT_POS_FAIL		= 0x05;	// 장착 부위 부적합
const BYTE REPLY_ITEM_EQUIPMENT_TWOHAND			= 0x06;	// 양손 무기 장착 불가능
const BYTE REPLY_ITEM_EQUIPMENT_TRIMURITI		= 0x07;	// 주신 제한
const BYTE REPLY_ITEM_EQUIPMENT_TRIBE			= 0x08;	// 종족 제한
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_MUSCL	= 0x09;	// 근육의 차크라 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_NERVE	= 0x0A;	// 신경의 차크라 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_HEART	= 0x0B;	// 심장의 차크라 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_SOUL		= 0x0C;	// 정신의 차크라 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA			= 0x0D;	// 차크라 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_BRAHMAN			= 0x0E;	// 브라만 포인트 제한
const BYTE REPLY_ITEM_EQUIPMENT_JOBSKILL		= 0x0F;	// 직업 기술 제한
const BYTE REPLY_ITEM_EQUIPMENT_DISTANCE		= 0x10;	// 아이템과 캐릭터 거리제한
const BYTE REPLY_ITEM_EQUIPMENT_OWNER			= 0x11;	// 아이템 소유주 제한

/*----------------------------------------------------------------------------*/
// 0x15 Group(Chatting)
/*----------------------------------------------------------------------------*/
// 일반 채팅
const BYTE REPLY_NORMAL_CHAT_FAIL	= 0x01;	// 일반채팅 실패

/*----------------------------------------------------------------------------*/
// 0x16 Group(Party)
/*----------------------------------------------------------------------------*/
// 파티 생성 요청
const BYTE REPLY_OTHER_JOIN_PARTY	= 0x01;	// 이미 다른 파티에 가입 중
const BYTE REPLY_REPEAT_PARTY_NAME	= 0x02; // 파티 이름 중복
const BYTE REPLY_CREATE_PARTY_FAIL	= 0x03; // 파티 생성 실패

// 파티 해체 
const BYTE REPLY_DISBAND_LOGOUT_MASTER		= 0x01; // 파티장이 로그아웃 함.
const BYTE REPLY_DISBAND_PARTY_FAIL			= 0x02;	// 파티 해체 실패
const BYTE REPLY_DISBAND_PARTY_NOT_MASTER	= 0x03; // 파티장이 아님, 생성 파티가 없음.
const BYTE REPLY_DISBAND_PARTY_NAME_ERROR	= 0x04; // 파티 이름이 잘못됐음.
const BYTE REPLY_DISBAND_PARTY_SYSTEM_ERROR = 0xFF;	// 시스템 에러...

// 파티 가입
const BYTE REPLY_PARTY_JOIN_DIS			= 0x01; // 파티 가입 실패 - 거리 제한
const BYTE REPLY_PARTY_JOIN_PARTY		= 0x02; // 다른 파티에 가입중
const BYTE REPLY_PARTY_JOIN_NCONNECT	= 0x03; // 파티 가입 실패 - 상대방 비접속
const BYTE REPLY_PARTY_JOIN_FULL		= 0x04;	// 파티 인원수 초과
const BYTE REPLY_PARTY_JOIN_NMASTER		= 0x05;	// 파티장이 아님.
const BYTE REPLY_PARTY_ALREADY_MEMBER	= 0x06; // 파티에 가입중.
const BYTE REPLY_PARTY_JOIN_CAST		= 0x07; // 파티장의 계급이 더 낮음.

const BYTE REQ_JOIN_PARTY_OK			= 0x00;	// 파티 가입 성공
const BYTE REQ_JOIN_PARTY_REJECT		= 0x01;	// 파티 가입 실패

const BYTE REPLY_SECEDE_PARTY_SUCC		= 0x00; // 파티 탈퇴 성공
const BYTE REPLY_SECEDE_PARTY_NMASTER	= 0x01; // 파티장에 의한 탈퇴
const BYTE REPLY_SECEDE_PARTY_LOGOUT	= 0x02; // 파티원이 로그아웃 함

// 주소록 관련
const BYTE REPLY_ACCEPT_ADDRESS			= 0x00; // 주소록 추가 요청 승인
const BYTE REPLY_REJECT_ADDRESS			= 0x01; // 주소록 추가 요청 거절

const BYTE REPLY_ADDRBOOK_LOGOUT		= 0x00; // 주소록 등록자 로그아웃
const BYTE REPLY_ADDRBOOK_ZONE_MOVE		= 0x01; // 주소록 등록자 존 이동

const BYTE REPLY_ADDRESS_JOIN_DISTANCE	=	0x01;	//	거리제한 오류
const BYTE REPLY_ADDRESS_JOIN_CONNECT	=	0x02;	//	상대방이 존에 없음 오류
const BYTE REPLY_ADDRESS_JOIN_ALREADY	=	0x03;	//	이미 가입한 대상 오류

//	GUILD
const BYTE REPLY_CLIENT_CONNECT			= 0x00; // 길드원 접속중
const BYTE REPLY_CLIENT_DISCONNECT		= 0x01; // 길드원 비접속중

const BYTE REPLY_GUILDMARK_PARAM		= 0x01;
const BYTE REPLY_GUILDMARK_RIGHT		= 0x02;
const BYTE REPLY_GUILDMARK_MONEY		= 0x03;

/*----------------------------------------------------------------------------*/
// 0x19 Group(Parameter)
/*----------------------------------------------------------------------------*/
// 차크라 상승 요청
const BYTE REPLY_CHAKRA_RISING_PRANA	= 0x01;	// 프라나 부족
const BYTE REPLY_CHAKRA_RISING_CHAKRA	= 0x02;	// 차크라 제한(더이상 못올림)
const BYTE REPLY_CHAKRA_RISING_DISTANCE	= 0x03;	// 거리 제한

// 브라만 포인트 상승 요청
const BYTE REPLY_BRAHMAN_RISING_PRANA		= 0x01;	// 프라나 부족
const BYTE REPLY_BRAHMAN_RISING_BRAHMAN		= 0x02;	// 브라만 포인트 제한(더이상 못올림)
const BYTE REPLY_BRAHMAN_RISING_DISTANCE	= 0x03;	// 거리 제한

// 인벤토리 슬롯 증가 요청
const BYTE REPLY_INCREASE_INVENTORY_SLOT_MAX_COUNT	= 0x01;	// 인벤토리 최대 슬롯 초과
const BYTE REPLY_INCREASE_INVENTORY_SLOT_ITEM		= 0x02;	// 인벤토리 증가 아이템이 없음

// NPC 친밀도 상승 요청
const BYTE REPLY_NPC_POINT_UP_TYPE_ERR	= 0x01;	// NPC 계통 오류
const BYTE REPLY_NPC_POINT_UP_2MORE		= 0x02;	// 하루에 2번이상 상승 요청함

// 차크라를 프라나로 변환
const BYTE REPLY_CHANGE_CHAKRA_TO_PRANA_ERR		= 0x01;	// 변환실패
const BYTE REPLY_CHANGE_CHAKRA_TO_PRANA_EQUIP	= 0x02;	// 변환실패(아이템 착용중)

/*----------------------------------------------------------------------------*/
// 0x20 Group(Skill)
/*----------------------------------------------------------------------------*/
// 스킬 등록 요청
const BYTE REPLY_SKILL_REGIST_EXIST			= 0x01;	// 이미 존재하는 스킬임
const BYTE REPLY_SKILL_REGIST_INDEX_ERR		= 0x03;	// 인덱스 오류
const BYTE REPLY_SKILL_REGIST_TYPE_ERR		= 0x04;	// 타입 오류
const BYTE REPLY_SKILL_REGIST_ERROR			= 0x05;	// 스킬 등록 오류

// 스킬 선택/해제/삭제
const BYTE REPLY_SKILL_SELECT_HAVE_NO_SKILL	= 0x01;	// 해당 스킬 없음
const BYTE REPLY_SKILL_SELECT_HAND_ERROR	= 0x02;	// 스킬 선택 부위 오류
const BYTE REPLY_SKILL_SELECT_PASSIVE		= 0x03;	// 선택/해제/삭제 불가 스킬(패시브 스킬)
const BYTE REPLY_SKILL_SELECT_RESELECT		= 0x04;	// 이미 선택되어 있음
const BYTE REPLY_SKILL_DELETE_NOT_FREE_SKILL= 0x05; // Free Skill이 아님(스킬 삭제시)
const BYTE REPLY_SKILL_DELETE_HAVE_NO_SKILL	= 0x06;	// 해당 스킬 없음(스킬 삭제시)
const BYTE REPLY_SKILL_DELETE_RESELECT		= 0x07;	// 이미 선택되어 있음(스킬 삭제시)
const BYTE REPLY_SKILL_DELETE_SUCC			= 0x08; // 스킬삭제 성공

// 스킬 준비동작 요청
const BYTE REPLY_SKILL_USE2_CHAR_DISABLE			= 0x01;	// 캐릭터 공격불가 상태
const BYTE REPLY_SKILL_USE2_CHAR_DISTANCE			= 0x02;	// 캐릭터 거리제한
const BYTE REPLY_SKILL_USE2_CHAR_HAVE_NO_SKILL		= 0x03;	// 스킬이 없음
const BYTE REPLY_SKILL_USE2_CHAR_NO_SELECT_SKILL	= 0x04;	// 선택된 스킬이 아님
const BYTE REPLY_SKILL_USE2_CHAR_REQ_PRANA			= 0x05;	// 스킬 사용 요구 프라나 부족
const BYTE REPLY_SKILL_USE2_CHAR_ITEM_TYPE			= 0x06;	// 아이템 타입 제한
const BYTE REPLY_SKILL_USE2_CHAR_ITEM_INDEX			= 0x07;	// 아이템 인덱스 제한
const BYTE REPLY_SKILL_USE2_CHAR_SKILL_INDEX		= 0x08;	// 특정 스킬 인덱스 제한
const BYTE REPLY_SKILL_USE2_CHAR_HAVE_NO_ITEM		= 0x09;	// 장착된 아이템이 없음
const BYTE REPLY_SKILL_USE2_CHAR_NO_TARGET			= 0x0A;	// 대상 캐릭터가 없음
const BYTE REPLY_SKILL_USE2_CHAR_NO_PK				= 0x0B;	// PK 불가 지역
const BYTE REPLY_SKILL_USE2_CHAR_TARGET_ERR			= 0x0C;	// 대상 타입 오류

// 스킬 공격
const BYTE REPLY_SKILL_ATK_CHAR_DISABLE				= 0x01;	// 캐릭터 공격불가 상태
const BYTE REPLY_SKILL_ATK_CHAR_DISTANCE			= 0x02;	// 캐릭터 거리제한
const BYTE REPLY_SKILL_ATK_CHAR_HAVE_NO_SKILL		= 0x03;	// 스킬이 없음
const BYTE REPLY_SKILL_ATK_CHAR_NO_SELECT_SKILL		= 0x04;	// 선택된 스킬이 아님
const BYTE REPLY_SKILL_ATK_CHAR_REQ_PRANA			= 0x05;	// 스킬 사용 요구 프라나 부족
const BYTE REPLY_SKILL_ATK_CHAR_ITEM_TYPE			= 0x06;	// 아이템 타입 제한
const BYTE REPLY_SKILL_ATK_CHAR_ITEM_INDEX			= 0x07;	// 아이템 인덱스 제한
const BYTE REPLY_SKILL_ATK_CHAR_SKILL_INDEX			= 0x08;	// 특정 스킬 인덱스 제한
const BYTE REPLY_SKILL_ATK_CHAR_HAVE_NO_ITEM		= 0x09;	// 장착된 아이템이 없음
const BYTE REPLY_SKILL_ATK_CHAR_NO_TARGET			= 0x0A;	// 대상 캐릭터가 없음
const BYTE REPLY_SKILL_ATK_CHAR_FAIL				= 0x0B;	// 공격 판정 실패
const BYTE REPLY_SKILL_ATK_CHAR_BLOCK				= 0x0C;	// 블럭 판정 성공
const BYTE REPLY_SKILL_ATK_CHAR_NO_PK				= 0x0D;	// PK 불가 지역
const BYTE REPLY_SKILL_ATK_CHAR_TAGET_ERR			= 0x0E;	// 대상 타입 오류
const BYTE REPLY_SKILL_ATK_CHAR_USE_TIME			= 0x0F;	// 스킬 사용 시간 오류


// 스킬 Level-Up 요청
const BYTE REPLY_SKILL_LEVEL_UP_MAX_LEVEL			= 0x01;	// 스킬 최대 레벨 - 더이상 레벨 올릴 수 없음
const BYTE REPLY_SKILL_LEVEL_UP_PRANA				= 0x02;	// 프라나 부족
const BYTE REPLY_SKILL_LEVEL_UP_HAVE_NO_SKILL		= 0x03;	// 해당 스킬이 없음
const BYTE REPLY_SKILL_LEVEL_UP_DATA_MIS			= 0x04; // 레벨업 데이타가 존재하지 않음

// 주신 변경 요청 결과
const BYTE REPLY_TRIMURITI_CHANGE_PRANA_LACK		= 0x01;	// 프라나 부족
const BYTE REPLY_TRIMURITI_CHANGE_SAME_TRIMURITI	= 0x02; // 똑같은 주신변경을 하려함
const BYTE REPLY_TRIMURITI_CHANGE_FAILED			= 0x03; // 주신 변경 실패

// 귓말전송 결과
const BYTE REPLY_WHISPER_CHAR_FAIL					= 0x01;	// 귓말전송 실패
const BYTE REPLY_WHISPER_REJECT						= 0x02;

// 교환 작업 수행 시 ErrorCode
const BYTE REPLY_TRADE_SUCCESS			= 0x00;		//	정상적인 거래의 완료
const BYTE REPLY_TRADE_USER_DENAY		= 0x01;		//	상대가 거래를 취소할 경우
const BYTE REPLY_TRADE_OVER_ME			= 0x02;		//	MY 인벤의 자리가 모자람
const BYTE REPLY_TRADE_OVER_YOU			= 0x03;		//	YOUR 인벤의 자리가 모자람
const BYTE REPLY_TRADE_OUTINDEX			= 0x04;		//	아이템 인덱스 오류
const BYTE REPLY_TRADE_USER_DIE			= 0x05;		//	유저사망으로 인한 거래 취소
const BYTE REPLY_TRADE_USER_CHANGE		= 0x06;		//	유저사망으로 인한 거래 취소
const BYTE REPLY_TRADE_ERROR			= 0x09;		//	기타 오류

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// 제작소 관련
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// 에러 관련
const BYTE REPLY_ITEM_CREATE_NOT_EXIST			=	-1;
const BYTE REPLY_ITEM_CREATE_CANNOT				=	-1;

//아이템 제작 요청 시 결과 코드
const BYTE REPLY_ITEM_BUY_GOLD_WANT				=	0x01;
const BYTE REPLY_ITEM_BUY_SUB_WANT				=	0x03;
const BYTE REPLY_ITEM_BUY_INVENTORY_LACK		=	0x04;
const BYTE REPLY_ITEM_BUY_MINCOUNT				=	0x05;
const BYTE REPLY_ITEM_BUY_ALREADY				=	0x06;
const BYTE REPLY_ITEM_BUY_SELLOUT				=	0x07;		//	잔고가 모자를 경우
const BYTE REPLY_ITEM_BUY_OUTINDEX				=	0x08;		//	npc가 해당 아이템을 보유하지 않고 있을 경우

// 아이템 수리 요청 시 결과 코드
const BYTE REPLY_ITEM_REPAIR_MONEY_WANT			=	0x01;
const BYTE REPLY_ITEM_REPAIR_OUTINDEX			=   0x02;
const BYTE REPLY_ITEM_REPAIR_ENOUGH				=	0x03;
const BYTE REPLY_ITEM_REPAIR_RESERVED			=	0x04;

// 아이템 해체 요청 시 결과 코드
const BYTE REPLY_ITEM_SELL_INVENTORY_LACK		=	0x01;
const BYTE REPLY_ITEM_SELL_NO_INVENTORY			=	0x02;
const BYTE REPLY_ITEM_SELL_RESERVED				=	0x03;
const BYTE REPLY_ITEM_SELL_OUTINDEX				=	0x04;

// 아이템 제련 요청 시 결과 코드
const BYTE REPLY_ITEM_REFINING_FAIL				=	0x01;
const BYTE REPLY_ITEM_REFINING_DISAPPEAR		=	0x02;
const BYTE REPLY_ITEM_REFINING_MONEY_LACK		=	0x03;
const BYTE REPLY_ITEM_REFINING_PRANA_LACK		=	0x04;
const BYTE REPLY_ITEM_REFINING_CANNOT			=	0x05;
const BYTE REPLY_ITEM_REFINING_OVER				=	0x06;
const BYTE REPLY_ITEM_REFINING_OUTINDEX			=	0x07;
const BYTE REPLY_ITEM_REFINING_ERROR			=	0x08;
const BYTE REPLY_ITEM_REFINING_INITIALIZE		=	0x09;
const BYTE REPLY_ITEM_SUBREFINING_INITIALIZE	=	0x0A;

//	아이템 헌납관련
const BYTE REPLY_ITEM_CONTRIBUTION_OUTINDEX		=	0x01;
const BYTE REPLY_ITEM_CONTRIBUTION_OUTPARAM		=	0x02;
const BYTE REPLY_ITEM_CONTRIBUTION_CANNOT		=   0x03;
const BYTE REPLY_ITEM_CONTRIBUTION_LACK			=   0x04;
const BYTE REPLY_ITEM_CONTRIBUTION_EVENT		=	0x05;

// 아이템 리스트 결과 코드byRefineLevel = 0byRefineLevel = 0
const BYTE REPLY_ITEM_LISTING_FAILED			=	0x01;

// 교환소 결과 코드
const BYTE REPLY_BARTER_DISTANCE				=	0x01;	
const BYTE REPLY_BARTER_SOURCE_LACK				=	0x02;
const BYTE REPLY_BARTER_INVENTORY_LACK			=	0x03;
const BYTE REPLY_BARTER_NPC_DISABLE				=	0x04;
const BYTE REPLY_BARTER_DISABLE					=	0x05;

// 인벤토리 확장 해제 결과 코드
const BYTE REPLY_INVENTORY_DECREASE_NO_EXPANDED		=	0x01;
const BYTE REPLY_INVENTORY_DECREASE_ITEM_EXIST		=	0x02;
const BYTE REPLY_INVENYORY_DECREASE_INVENTORY_LACK	=	0x03;

const BYTE REPLY_EVENT_ERR_INVENTORY_LACK	= 1;
const BYTE REPLY_EVENT_ERR_PRANA_LACK		= 2;
const BYTE REPLY_EVENT_ERR_CHAKRA_LACK		= 3;
const BYTE REPLY_EVENT_ERR_RUPHIA_LACK		= 4;
const BYTE REPLY_EVENT_ERR_NO_ITEM			= 5;
const BYTE REPLY_EVENT_ERR_QUEST_ITEM		= 6;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

const BYTE REPLY_JOIN_ADDRESS_BOOK_DISTANCE		= 0x01;
const BYTE REPLY_JOIN_ADDRESS_BOOK_NOCONNECT	= 0x02;
const BYTE REPLY_JOIN_ADDRESS_BOOK_ALREADY		= 0x03;
const BYTE REPLY_JOIN_ADDRESS_BOOK_ETC			= 0x04;

const BYTE REPLY_JOIN_ADDRESS_RESULT_DERAY		= 0x02;

const BYTE REPLY_DELETE_ADDRESS_FAIL			= 0x01;

const BYTE REPLY_ADDRESS_BOOK_GROUP_ALREADY		= 0x01;
const BYTE REPLY_ADDRESS_BOOK_GROUP_NOCHAR		= 0x02;
const BYTE REPLY_ADDRESS_BOOK_GROUP_NOGROUP		= 0x03;
const BYTE REPLY_ADDRESS_BOOK_GROUP_UNKNOWN		= 0x04;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

const BYTE REPLY_GMTRANSPARENCY_ALREADY_ON		= 0x01;
const BYTE REPLY_GMTRANSPARENCY_ALREADY_OFF		= 0x02;
const BYTE REPLY_GMTRANSPARENCY_UNKNOWN			= 0x03;

//	GM 관련
const BYTE REPLY_GMMOVE_OTHER					= 0x01;	//  타지역내 워프 요청
const BYTE REPLY_GMMOVE_UNMOVE					= 0x02;	//	이동 불가지역
const BYTE REPLY_GMMOVE_DISCONNECT				= 0x03;	//	케릭터 미접속
const BYTE REPLY_GMMOVE_UNKNOWN					= 0x04;	//	워프 실패

const BYTE REPLY_GMCHAT_BIT						= 0x01;
const BYTE REPLY_GMACTION_BIT					= 0x02;
const BYTE REPLY_GMTRANSPARENCY_BIT				= 0x03;

const BYTE REPLY_GMMODE_FAIL					= 0x01;

const BYTE REPLY_GMCLOSE_CHARACTER_FAIL			= 0x01;
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

const BYTE REPLY_DISCONNECT_GMALREADY_CONNECTED			= 0x03;
const BYTE REPLY_DISCONNECT_GMLACK_OR_HACK				= 0x04;
const BYTE REPLY_DISCONNECT_GM_ORDERD					= 0x05;

//	이벤트 아이템 순위를 위한 플래그(EVENT_20030701)
const BYTE REPLY_REQ_SET_EVENT_SUCC				= 0x00;
const BYTE REPLY_REQ_SET_EVENT_FAIL				= 0x01;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

//	GUILD
const BYTE TPROTO_CLIENT_CONNECT				= 0x00;
const BYTE TPROTO_CLIENT_DISCONNECT				= 0x01;

const BYTE GUILD_ATHORITY_MASTER				= 0x00;

const BYTE	REPLY_GUILDALLIANCE_REQUEST			= 0x00;
const BYTE	REPLY_GUILDALLIANCE_SUCCESS			= 0x01;
const BYTE	REPLY_GUILDALLIANCE_ALREADY			= 0x02;
const BYTE	REPLY_GUILDALLIANCE_DISCONNECT		= 0x03;
const BYTE	REPLY_GUILDALLIANCE_LEVEL			= 0x04;
const BYTE	REPLY_GUILDALLIANCE_CANCEL			= 0x05;

//	Coupon Event
const BYTE REPLY_COUPONEVENT_0ST				= 0x00;		//	꽝
const BYTE REPLY_COUPONEVENT_1ST				= 0x01;		//	1등(InGame)
const BYTE REPLY_COUPONEVENT_2ST				= 0x02;		//	2등(InGame)
const BYTE REPLY_COUPONEVENT_3ST				= 0x03;		//	3등(InGame)
const BYTE REPLY_COUPONEVENT_4ST				= 0x04;		//	4등(InGame)
const BYTE REPLY_COUPONEVENT_5ST				= 0x05;		//	5등(InGame)
const BYTE REPLY_COUPONEVENT_6ST				= 0x06;		//	6등(InGame)
const BYTE REPLY_COUPONEVENT_7ST				= 0x07;		//	영화관람권
const BYTE REPLY_COUPONEVENT_8ST				= 0x08;		//	그래픽카드
const BYTE REPLY_COUPONEVENT_9ST				= 0x09;		//	타란튤라
const BYTE REPLY_COUPONEVENT_10ST				= 0x0A;		//	나가무드라
const BYTE REPLY_COUPONEVENT_LACK				= 0x11;		//	공간부족
const BYTE REPLY_COUPONEVENT_ERROR				= 0x12;		//	알수없는 오류
const BYTE REPLY_COUPONEVENT_UNKNOWN			= 0x13;		//	알수없는 복권

//	Gemble
const BYTE REPLY_YUTMONEY_SUCCESS				= 0x00;		//	성공
const BYTE REPLY_YUTMONEY_INVENFULL				= 0x01;		//	인벤토리에 자리가 조금도 없다
const BYTE REPLY_YUTMONEY_PART					= 0x02;		//	입벤토리가 풀이라 조금만 돈을 찾앗을 경우
const BYTE REPLY_YUTMONEY_NOHAVEMONEY			= 0x03;		//	찾을 돈이 없을 경우
const BYTE REPLY_YUTMONEY_FAIL					= 0x04;		//	기타 돈을 찾을수 없는 경우

//	Common_Response
//const BYTE	REPLY_COMMON_LACKOFMONEY			= 0x01;		//	루피아가 부족합니다
//const BYTE	REPLY_COMMON_NOT_TARGET				= 0x02;		//	이벤트 대상이 아닙니다
//const BYTE	REPLY_COMMON_ALREADY				= 0x03;		//	이미 참여하셧습니다
//const BYTE	REPLY_COMMON_NOT_CONDITION			= 0x04;		//	이벤트 조건에 해당되지 않습니다

/*********************************************/
//	2004.08.26(능력치, 스킬 초기화 관련패킷)
const BYTE REPLY_NPCCOMMAND_LACK				= 0x01;		//	루피아가 부족할경우
const BYTE REPLY_NPCCOMMAND_EQUIP				= 0x02;		//	아이템을 착용한경우
const BYTE REPLY_NPCCOMMAND_STATUS				= 0x03;		//	초기화가 불가능한 상태
const BYTE REPLY_NPCCOMMAND_NOT_TARGET			= 0x04;		//	대상이 아닌경우
const BYTE REPLY_NPCCOMMAND_ALREADY				= 0x05;		//	이이 참여한 상태
/*********************************************/

const BYTE REPLY_CHANGECHARNAME_SUCCESS			= 0x00;		//	변경성공
const BYTE REPLY_CHANGECHARNAME_LACK			= 0x01;		//	타니부족
const BYTE REPLY_CHANGECHARNAME_ALREADY			= 0x02;		//	이름중복
const BYTE REPLY_CHANGECHARNAME_FAIL1			= 0x03;		//	..
const BYTE REPLY_CHANGECHARNAME_FAIL2			= 0x04;		//	..

#endif