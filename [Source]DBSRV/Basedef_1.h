#ifndef _BASEDEF_
#define _BASEDEF_

#include <windows.h>
#include <map>
#include <atltime.h>
#include "CPSock.h"
#ifdef __ZONE_SERVER__
	#include "TNDeck100.h"
#endif

//	#define _ACCOUNTPASS_MD5_CHANGE_
#define _ACCOUNTNAME_LENGTH_52BYTES_

#define		MAX_ENGLISH				400			
#define		DBG_TRACE					// ����� Ʈ���̽� 
#define		APP_VERSION				563
#define		GAME_PORT				18400
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           DEFINE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		DB_PORT					7514      // DB������ ������Ʈ
#define		ADMIN_PORT				8895 
#define		TSMON_PORT				15110
#define		BILL_PORT				3010
#define		WHATSUP_PORT			5000	  // What's up ���񽺿� ��Ʈ(�߱���)
#define		MAX_ZONE				6
#define		MAX_SERVER				20      // DB���� 1���� ������ �ִ� Game������ ����
#define		MAX_SERVERGROUP			10
//#define		MAX_SERVERNUMBER		(MAX_SERVER+2)// DB+MSG+ZONE
#define		MAX_SERVERNUMBER		(MAX_SERVER+3)// DB+MSG+ZONE+DAEMON
#define		INDEXOFDBA				0
#define		SERVER_SHAMBALA			2
#define		SERVER_TRIMURITI		10 // ũ�縶 ��
#define		SERVER_CHATURANGKA		11 // �������� ��
#define		SERVER_KALIA_LOW		13	//	Į���ƴ��� ����
#define		SERVER_KALIA_MIDDLE		14	//	Į���ƴ��� ����
#define		SERVER_KALIA_HIGH		15	//	Į���ƴ��� ����
#define		SERVER_STRONGHOLD		16	//	�����
#define		SERVER_KATANA3			17	//	īŸ��3
#define		INDEXOFMESSENGER		21
#define		INDEXOFDAEMON			22
#define		MAX_IP_LENGTH			16
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		SECSTANDINGBY			8      // ��Ÿ�̸ӿ� ���� ������ NPC ACTION ���Ұ�. 2.0��(=8*0.25��)
#define		SECBATTLE				2      // ��Ÿ�̸ӿ� ���� �������� NPC ACTION ���Ұ�. 0.5��(=2*0.25��)
#define		TICKSIZE				250
#define		MAX_USER				1000      // pUser�� �ε������� pMob�� �ε��� pMob�� MAX_USER���Ĵ� NPC
#define		MAX_ADMIN				50      // 10�� 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
	#define		OLD_ACCOUNTNAME_LENGTH	20		// ���� ��ī��Ʈ �̸�����
	#define		ACCOUNTNAME_LENGTH		52      // ��ī��Ʈ�� �̸�����
#else
	#define ACCOUNTNAME_LENGTH			20
#endif

#define		ACCOUNTPASS_LENGTH		36     // ��ī��Ʈ�� �������

#define		REALNAME_LENGTH			24      // ��ī��Ʈ�� ������ ���� ����
#define		EMAIL_LENGTH			48      // ��ī��Ʈ�� ������ �̸��� ����
#define		ADDRESS_LENGTH			80      // ��ī��Ʈ�� ������ �ּ� ����
#define		TELEPHONE_LENGTH		16      // ��ī��Ʈ�� ������ ��ȭ��ȣ ����
#define		MAX_GUILD				4096   // �������� ���� ũ��
#define		MOB_PER_ACCOUNT			3      // ��ī��Ʈ�� ����� �ִ� Char�� ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		IDX_MOB					0      // Mob �� 0���� ����.
#define		MAX_MONSTER				3500
#define		MAX_MOB					5000      // PC�� NPC ���� �ִ� ����. CMob ���ũ��
#define		SZNAME_LENGTH			20      // NPC�Ǵ� Char�� �̸� ����
#define		GUILDNAME_LENGTH		20	  // Guild Name�� ����
#define		MAX_SCORE				16      // MOB�� Ư�� (����,��,����ġ...)
#define		MAX_EQUIP				16      // ĳ���Ͱ� ������ �ִ� ������, �Ӹ��� ������ ���� 0,1��°��.
#define		MAX_INVEN				72      // MOBInven��Char��  Mob�� Ship�� �� Inventory �����̴�.
#define		MAX_ONEINVEN			24
#define		MAX_CARGO				120      // ��ī��Ʈ�� ������ ����
#define		MAX_SKILL				100	  // ĳ���ͺ� ��ų �ִ밪
#define		MAX_SKILL_DATA			4500     // ��ų �ִ� ����
#define		MAX_EVENT_FLAG			100	  // ĳ���ͺ� ����Ʈ �÷��� �ִ밪
#define		MAX_DESC				24   
#define		MAX_CLASS				8
#define		MAX_MONSTER_DATA		1000
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_SUMMONLIST			2048
#define		MAX_NPCGENERATOR		4096      // NPC���� ���� ����Ʈ. NpcGener.txt���� �о� ���� �����̴�.
#define		MAX_CLAN				26
#define		MAX_SEGMENT				5   // �� ���� �����ϸ� �ٷ� �Ʒ��� LAST_SEGMENT�� �� �������ش�.
#define		LAST_SEGMENT			4
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		IDX_ITEM				10000      // Item�� ID�� 10000�� ���ķ� �ٴ´�.
#define		MAX_ITEM				5000      // ���ٴڿ� ���̴� ������ ��� ũ��
#define		MAX_ITEMLIST			3000	  // ������ ����Ʈ ����Ʈ
#define		MAX_ITEM_DATA			6000      // ������ �ִ� ����(���� ������ ����5000 + monster item ���� 1000)
#define		ITEMNAME_LENGTH			28      // �������� �̸� ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MESSAGE_LENGTH			96      // MSG_MessagePanel �Ǵ� MessageBox�� ��Ʈ�� ����
#define		MAX_DBACCOUNT			(MAX_USER*MAX_SERVER) // Game������ MAX_USER���� ������ �ִµ� DB���������� �� ��ü ���� ����Ʈ�� ��� �־�� �Ѵ�.
#define		IsUser(value)			((((value)>=0&&(value)<MAX_USER ) ? TRUE : FALSE) )
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_GRIDX				1024		// ��ü �� ���� ���� ũ��
#define		MAX_GRIDY				1024
#define		PRANAGRIDX				100
#define		PRANAGRIDY				100
//#define		VIEWGRIDX				65		// Multicasting �� ���� ���� ũ��
//#define		VIEWGRIDY				65
//#define		HALFGRIDX				32		// Multicasting ������
//#define		HALFGRIDY				32
#define		TRACE_LIMIT				24
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_ROUTE				24
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		InvenGRIDX				9	// �κ� ���� ���� ũ��
#define		InvenGRIDY				7
#define		CARGOGRIDX				9	// â�� ���� ���� ũ��	
#define		CARGOGRIDY				14
#define		MAX_FORMATION			5 // ���� (����)����

#define		MAX_GROUNDMASK			6
#define		MAX_INITITEM			64
#define		MAX_SKILLINDEX			101	// ������ 0-100	
#define		BASE_EQUIP_LIMIT		40
#define		MAX_TRADE				8
#define		MAX_AUTOTRADE			12
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_SHOPLIST			27
#define		SET_ITEM_CREATE			0
#define		SET_ITEM_DELETE			1
#define		ITEM_REFINING_COAT		0.2		//	���������ý� �����۰����� 20% ����
#define		ITEM_REPAIR_COAT		0.85	//	���������ý� �����۰����� 20% ����
//	#define		ITEM_SELL_COAT			6		//	���������ý� �����۰����� 20% ����
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
	eCountryForceDword = 0xffffffff
};

//	char
const int	TRIMURITY_LEVEL				=	30;				//	�ֽź��淹��
const int	TRIMURITY_POINT_LEVEL		=	100;			//	��ų����Ʈ����
const int	MONEY_TRIMURITY_UP			=	50000;			//	��ų����Ʈ���� �ʿ���
const int	MONEY_CHANGE_TRIMURITY_DOWN	=	100000;			//	�ֽź���� �ʿ���	
const int   MONEY_CHANGE_TRIMURITY_UP	=	1000000;		//	�ֽź���� �ʿ���

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
const int	RESURRECT_TYPE_SAVE		=	1;
const int	RESURRECT_TYPE_PRESENT	=	2;
const int	RESURRECT_TYPE_TOWN		=	3;
const int	RESURRECT_TYPE_ARENA	=	4;
const int	RESURRECT_TYPE_TEST		=	9;

//	chat 
#define		MAX_CHAT_LENGTH			224
#define		MAX_GROUPCHAT_LENGTH	48
#define		MAX_NOTIFY_LENGTH		1024
#define		HT_PARAMTYPE_NONE		0
const int	MAX_BASE_CHAKRA	=		7 ;

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

//	������
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

const int MAX_INVEN_X				=	6;
const int MAX_INVEN_Y				=	4;
const int TYPE_ITEM_PACKING			=	1;
const int TYPE_ITEM_UNPACKING		=	2;
const int ITEM_EQUIP_LEVEL			=	5;

//	Item Drop
const int DROP_TYPE_MONEY			=   0;
const int DROP_TYPE_ITEM			=   1;

//	 ��ð��û��
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
const int  MAX_MAINREFINELEVEL			=	12;		// ����÷���
const int  MAX_SUBMATERIAL				=	10;		// ��������� �ִ밹��
const int  MAX_SUBMATERIALSIZE			=	5;

//	�ִ� ��ȯ�������� ����
const int	MAX_CARRY	= 8;
const int   MAX_MOBSTORE = 24;
const int   SZTRADE_LENGTH = 64;

//	Party
const int	MAX_PARTY			=	7;	// �� �׷��� �ִ��( 1+5) 
const int	PARTY_PICKUP_TIME	=	10000;
const int	ROOTING_SHARE		=	1;
const int	ROOTING_PERSON		=	0;

//	Guild
#define		GUILD_FILE_PATH			"G:/"
const int	MAX_GUILD_MEMBER	=	50;

const int	SZGUILD_LENGTH		=	20;
const int	GUILDMESSAGE_LENGTH =   256;
const int	GUILD_CREATE_COST	=	300000;
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

//	LOG
const int LOGMONEY				=	1000000;

//	Developer
#define Developer				"TANDEV01"

//	���������
const int MONEY_ARENAEVENT		=	100000000;

//	Billing(cash)
const int MAX_TIMEITEM			=	10;
enum { eTime_Inven = 0, eTime_Store = 1, eTime_AMoneyRoot = 2, eTime_Anubaba = 3, eTime_Atman = 4, eTime_15Chakra = 5, } ;

//	Challenge
const int	MONEY_OF_CHALLENG		=	10000;
typedef enum _EChallenge { eChallenge_WAIT = 0, eChallenge_Request = 1, eChallenge_Response = 2, eChallenge_Combat = 3, } EChallenge;
typedef enum _EChallengeReason { eChallenge_Accept = 0, eChallenge_Denay = 1, eChallenge_Rest = 2, eChallenge_System = 3, eChallenge_End = 4,  } EChallengeReason;
/*----------------------------------------------------------------------------*/
// ������ ���� ����Ȯ��
/*----------------------------------------------------------------------------*/
const int REFINE_INITIALIZE_LEVEL	= 4;
const int REFINE_DISAPEAR_LEVEL		= 7;

//	Ranking
const int MAX_RANK				= 250;
#define RANKFILE				"K:\\Rank%02d.txt"

//	Yut(������)
const int MAX_POSITION	=	29;
const int MAX_BETUSER	=	20000;
enum
{
	eYut_bet	= 0x00000001,
	eYut_set	= 0x00000010,
	eYut_play	= 0x00000100,
	eYut_Result = 0x00001000,
};

#define HT_MAP_START						40001

#define HT_PARAMTYPE_NONE					0

//#ifdef HT_NEED_NAME
//#define HT_NAME_MAX 50
//#endif

#define		TRIBE_NAGA			1//0x01	// ����
#define		TRIBE_ASURA			4//0x02	// �Ƽ���
#define		TRIBE_YAKSA			16//0x03	// ��ũ��
#define		TRIBE_DEVA			64//0x04	// ����
#define		TRIBE_KINNARA		2//0x05	// Ų����
#define		TRIBE_RAKSHASA		8//0x06	// ��ũ����
#define		TRIBE_GANDHARVA		32//0x07	// ���ٸ���
#define		TRIBE_GARUDA		128//0x08	// �����

#define		BEAUTY_OLD_HAIR		5
#define		BEAUTY_OLD_FACE		5
#define		BEAUTY_NEW_HAIR		8
#define		BEAUTY_NEW_FACE		8

#define HT_PARAMTYPE_NONE					0

// ���� ID ����
#define HT_PARAMTYPE_MONSTER				1
#define HT_PARAMTYPE_MONSTER_START			2001
#define HT_PARAMTYPE_MONSTER_END			2999

// ���� ��ų�� ID ����
#define HT_PARAMTYPE_MONSTERSKILL			2
#define HT_PARAMTYPE_MONSTERSKILL_START		3501
#define HT_PARAMTYPE_MONSTERSKILL_END		3999

// ĳ���� ��ų�� ID ����
#define HT_PARAMTYPE_PCSKILL				3
#define HT_PARAMTYPE_PCSKILL_START			3001
#define HT_PARAMTYPE_PCSKILL_END			3499

// �������� ID ����
#define HT_PARAMTYPE_ITEM					4
#define HT_PARAMTYPE_ITEM_START				4001
#define HT_PARAMTYPE_ITEM_END				9989

// NPC ID ����
#define HT_PARAMTYPE_NPC					5
#define HT_PARAMTYPE_NPC_START				1001
#define HT_PARAMTYPE_NPC_END				1999
#define HT_NPC_SELLING_ITEM_MAX				50

// Portal
#define HT_PARAMTYPE_PORTAL					6
#define HT_PARAMTYPE_PORTAL_START			101
#define HT_PARAMTYPE_PORTAL_END				1000

// TaskQuest
#define HT_PARAMTYPE_TASKQUEST				7
#define HT_PARAMTYPE_TASKQUEST_START		10001
#define HT_PARAMTYPE_TASKQUEST_END			15000

#define HT_PARAMTYPE_END					8

// ��ų �� ����/Ų����
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_START				3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_END				3100

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_START			3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_END			3020

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_START			3021
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_END			3040

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_START			3041
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_END			3060

// ��ų �� �Ƽ���/������
#define HT_PARAMTYPE_PCSKILL_ASURARAK_START				3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_END				3200

#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_START			3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_END			3120

#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_START			3121
#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_END			3140

#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_START			3141
#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_END			3160

// ��ų �� ��ũ��/���ٸ���
#define HT_PARAMTYPE_PCSKILL_YAKGAN_START				3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_END					3300

#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_START			3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_END				3220

#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_START			3221
#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_END				3240

#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_START			3241
#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_END				3260

// ��ų �� ����/�����
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_START				3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_END				3400

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_START			3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_END			3320

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_START			3321
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_END			3340

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_START			3341
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_END			3360

// ������ �� ������ ID ����
#define HT_PARAMTYPE_ITEM_WEAPON_START							4001
#define HT_PARAMTYPE_ITEM_WEAPON_END							5000

// ������ �� �Ѽ� ������ ID ����
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

// ������ �� ��� ������ ID ����
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

// ������ �� ��ô ������ ID ����
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

// ��
#define HT_PARAMTYPE_ITEM_DEFENCE_START							5001
#define HT_PARAMTYPE_ITEM_DEFENCE_END							6000

// ����
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

// ����
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

// ����
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

// �尩
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

// �㸮��
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

// �Ź�
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

// ����
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

// ����
#define HT_PARAMTYPE_ITEM_CHARM_START							5801
#define HT_PARAMTYPE_ITEM_CHARM_END								5850

// �Ǽ��縮
#define HT_PARAMTYPE_ITEM_ACCESSORY_START						6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_END							6500

// �Ͱ���
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

// ����
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

// �����
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

// �κ�Ȯ��
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_START			6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_END				6310

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_START	6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_END		6308

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_START		6309
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_END		6310

// ����
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

// ���� ���
#define HT_PARAMTYPE_ITEM_REFINE_START							6501
#define HT_PARAMTYPE_ITEM_REFINE_END							6700

// ��������
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_START						6501
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_END						6550

// ÷�� �������
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_START						6551
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_END						6600

// ��������
#define HT_PARAMTYPE_ITEM_REFINE_SUB_START						6601
#define HT_PARAMTYPE_ITEM_REFINE_SUB_END						6700

// ����ȭ ������-���Ӿ�����
#define HT_PARAMTYPE_ITEM_CHARGE_START							6801
#define HT_PARAMTYPE_ITEM_CHARGE_END							7000

#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_START				6801
#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_END				6950

#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START					6951
#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_END					7000

// ����ȭ ������ �� �Ҹ� ������
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_START					7031
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_END						7070

#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_START					6719
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_END 					6722

// �Һ� ������ (1)
#define HT_PARAMTYPE_ITEM_USABLE_START							7001
#define HT_PARAMTYPE_ITEM_USABLE_END							7100

// �Һ� ������ (2)
#define HT_PARAMTYPE_ITEM_USABLE2_START							6701
#define HT_PARAMTYPE_ITEM_USABLE2_END							6800

// ���Ǿ�
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_START					7081
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_END						7090

// ȭ��
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_START					7091
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_END						7100

// ���� ������
#define HT_PARAMTYPE_ITEM_COLLECT_START							7101
#define HT_PARAMTYPE_ITEM_COLLECT_END							8000

// ����Ʈ ���� ������
#define HT_PARAMTYPE_ITEM_QUESTONLY_START						8001
#define HT_PARAMTYPE_ITEM_QUESTONLY_END							8200

#define HT_PCSKILL_MAXLEVEL			11

#define HT_ITEMLEVEL_MAX			255

//	0:����, -1:��úҰ���
const int REFINE_MAIN[6][MAX_MAINREFINELEVEL] = {				
	{80		,70		,60		,45		,30		,0		,0		,0		,0		,0		,0		,0},
	{100	,100	,90		,75		,65		,55		,40		,10		,0		,0		,0		,0},
	{100	,100	,100	,100	,80		,70		,60		,20		,10		,5		,0		,0},
	{40		,30		,25		,0		,0		,0		,0		,0		,0		,0		,0		,0},
	{100	,100	,100	,100	,100	,100	,100	,80		,50		,30		,20		,10},
	{100	,100	,100	,100	,100	,100	,100	,100	,100	,-1		,-1		,-1}
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
		int	TargetType;      // 0:�ڽ�  1:Ÿ��   2:�ڽ�Ÿ��   3:����3  4:����5 
		int	ManaSpent;       // �����Ҹ�
		int	Delay;           // �������뿡 �ʿ��ѽð�
		int	Range;           // �����Ÿ�
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
//  Index:          ������ȣ                    - 0-71 �� Ŭ������ 0-23(���) 24-47(����) 48-71(����) 72-96(����)
//  SkillPoint:     ���µ� �ʿ��� �������Ʈ 
//  TargetType:     0:�ڽŸ�  1:Ÿ��  2:�ڽŶǴ�Ÿ�� 3:��3x3  4:��5x5
//  ManaSpent:      �⺻ ���� �Ҹ� �迭���õ��� 100�̸� 200% 
//  Delay:          �ѹ� ���� �ٽ� ������� �ʿ��� �ð� ������ ��.
//  Range:          �����Ÿ�
//  InstanceType:   ������ ����Ǵ� ���� ó���Ǵ� ȿ�� - 0:���� 1:HP����       2:HP%����      3:ȭ������  
//  InstanceValue:  HP������ �Ǵ� ���ҷ� �Ǵ� ȭ����������.
//  TickType:       ƽ(4��)���� ó���Ǵ� ȿ��          - 0:���� 1:HP+����      2:HP%����      3:3x3HP����    4:3x3HP���� 
//  TickValue:      HP������ �Ǵ� ���ҷ�
//  AffectType:     �ɷ��ִµ��� Score ��ȭ            - 0:���� 1:�޸���+��ȭ  2:���׷�%��ȭ  3:Dex%��ȭ     4:����+��ȭ
//  AffectValue:    +- �Ǵ� %��. +-�� �������ų� ������, %�� ������ �������� 2��� 200 1/2�� 50
//

// Dropped item�� mask������ �����Ѵ�. -> ������Ʈ���� ����
// ���� unsigned short �� ����ϰ� ���̵�� 20000-30000�̸�, 20000�� ��� 0�� ��ġ�ȴ�.
struct STRUCT_ITEMLIST
{      //int				   Style;						// ��Ÿ��
       //int				   Position;					// ���� ���� ���� -> 2���� �̻� �������ɽ� Bitmask(?)
       char					Name[ITEMNAME_LENGTH];		// ������ �̸�
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
      unsigned char   Reserved;   // ���� 4��Ʈ(0-15):0����(����). 1����. 2â��  3��ų  4����(����) 5. 
	                              // ���� 4��Ʈ(0-15) �𷺼� 1,2,3,4,6,7,8,9 �Ǵ� none(0)
	  unsigned char   AttackRun;  // ���� 4��Ʈ ���ݼӵ�   - 0:50%   5:100%   10:200%
                                  // ���� 4��Ʈ �޸���ӵ� - 1-6                        
	  short   MaxHp,   MaxMp;
	  short   Hp   ,   Mp   ;
	  short   snMuscleChakra, snNerveChakra, snHeartChakra, snSoulChakra;
	  unsigned char Special[4];  // ������õ�/ �������迭�����õ�1,2,3
};

struct STRUCT_ITEM // 16 bytes
{		short		snIndex ; // Shopitem ������ index
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
	SHORT		snIndex ;		//	Shopitem ������ index
	BYTE		byMainRef;		//	�Ӽ��� ���� ��Ʈ���� �ʿ���.
	BYTE		byRefineLevel;	//	���÷���
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
	BYTE		byGMStatus;		//	bit flag(0x01:�ɸ��ͺ�, 0x02:������, 0x04:ä�ú�, ...)	
	BYTE		byClass1;			//	bit flag �߸��ߺ��� | ������.
	BYTE		byClass2;

	short		snKarma;
	short		snDummy;
} S_CHARACTER_LIST, *PS_CHARACTER_LIST;

struct STRUCT_SELCHAR
{      
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];
};



struct STRUCT_MOB // 32+24+24+100+100+1152+256 = 1688 bytes = 1.688 kb, ������ 1024*2��ŭ�� ���ϰ��̴�.
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
		BYTE					bySpecialName;		// Class �� ������ ����� ��. int
		BYTE					byZone;
		BYTE					bySaveZone;

		BYTE					byStatus;			//	bit flag(0x01:�Ӹ�����, ...)
		BYTE					byGMStatus;			//	bit flag(0x01:�ɸ��ͺ�, 0x02:������, 0x04:ä�ú�, ...)	
		BYTE					byClass1;				//	bit flag �߸��ߺ��� | ������.
		BYTE					byClass2;

		short					snKarma;
		BYTE					byDummy3;
		BYTE					byDummy4;

		short					snX;
		short					snZ;
		short					snSaveX;
		short					snSaveZ; // 24
		
		BYTE					bySkill[MAX_SKILL];  // 100
		BYTE					byQuest[MAX_EVENT_FLAG]; // 100
		STRUCT_ITEM				Inven[MAX_INVEN]; // 16 * 72
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
		BYTE	GuildState;			//	0:�󽽷�, 1:�α�off, 2:�α�on
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
		STRUCT_ITEM			Repository[MAX_CARGO*3];	// â�� 3��
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
//                                           STRUCTURE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Message Structure �� ID �ε��� ���  
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
//           DB ����     - >   ���� ����
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
//               ���� ����   - >   DB ����
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define  FLAG_GAME2DB                0x0800
#define _MSG_DBNewCharacter         ( 2 | FLAG_GAME2DB) //   ĳ���� �����
#define _MSG_DBAccountLogin         ( 3 | FLAG_GAME2DB) //   ��ī��Ʈ �α���
#define _MSG_DBCharacterLogin       ( 4 | FLAG_GAME2DB) //   ĳ���� �α���
#define _MSG_DBNoNeedSave           ( 5 | FLAG_GAME2DB) //   ���� ����, �����Ұ� ����.
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
		int Result;					// 0: ��û,����  1:�������̾ƴ�  2:����̴ٸ� 3:���ڸ����� 
		char Account[ACCOUNTNAME_LENGTH];
		STRUCT_ITEM	Item;
};

//-------------------------------------------------------
//	added by �����(2003.11.22)
//-------------------------------------------------------
int Percent( double a_dValue, double a_dPercent ) ;

#define TN_MAX_COEFFICIENT_COUNT	4
#define TN_MAX_TARGET_COUNT			16
#define TN_MAX_SKILLBOOK_SIZE		1500
#define TN_MAX_EFFECT_COUNT			5
#define TN_ADDON_EFFECT_COUNT		5
#define TN_MAX_VARIATION_COUNT		64
#define TN_RANGE_DISTANT			6
#define TN_PC_SKILL_COUNT			100
#define TN_MONSTER_SKILL_COUNT		9
#define TN_ATTACKER_COUNT			16
#define TN_MAX_LEVEL				101 // 100 + 1
#define TN_BRAMAN_POINT				50
#define TN_MASTERY_COUNT			11
#define TN_CFTABLE_COUNT			9


//#define TN_DURABILITY_CONST			100
// ��� ����
enum { eSummonCaller_TriggerEvent1 = 20, eSummonCaller_TriggerEvent2 = 30
		, eSummonCaller_Normal = 100, eSummonCaller_Familiar, eSummonCaller_Fellow, eSummonCaller_Tracker
		, eSummonCaller_MonsterScroll = 110, eSummonCaller_GMCommand = 120,
} ;

enum { eCnst_StaffCorrect = 0, eCnst_StaffMaxNerves, eCnst_AbsorbMax, eCnst_ReflectMax
		, eCnst_SpeedMin, eCnst_SpeedMax, eCnst_HPRecvMax, eCnst_TPRecvMax, eCnst_ResistMax
		, eCnst_ProtectionFromPK, eCnst_PriorityTime, eCnst_TownPortalTime, eCnst_AdvTownPortalTime, eCnst_QuitTime
		, eCnst_Restriction, eCnst_RwdBramanPoint, eCnst_DecKarmaPoint, eCnst_RwdKarmaPoint, eCnst_IncKarmaPoint, eCnst_RwdGold, eCnst_LoseGold, eCnst_MaxKarma, eCnst_MurderDropRate, eCnst_InnocentDropRate, eCnst_FirstStrikerDropRate, eCnst_HuntHigh, eCnst_HuntLow, eCnst_FirstStrikeDur
		, eCnst_CondCoolDown, eCnst_KalaCoreDur, eCnst_PenaltyByKilled
		, eCnst_HeartMax, eCnst_AttackSpeedHack,
};

enum { eRetainer_DistanceFromMaster = 32, } ;
enum { eCmd_None = 0, eCmd_PopMonster = 1, eCmd_DropItem = 2, eCmd_MaxCount = 6, eArea_MaxMobListCount = 6, } ;
enum { eSklPtrn_Count = 50, eSklPtrn_Size = 10, eAAC_ArmorTypeCount = 15, eAAC_AttackTypeCount = 21, ePath_MaxCount = 5, eFlee_MaxPathCount = 5, eRoam_MaxPathCount = 5, eSmbl_MaxSize = 7, } ;
enum { eSdg_SymbolCount = 7, eSdg_MaxEntry = 200, eSdg_LeaderSize = 4, } ; // ������ ����
enum { eItm_Use = 0, eItm_Info, eItem_Brd, eItm_Arrow = 7092, /*eItm_TownPortal = 7011, eItm_TownPortal2 = 7028, eItm_TownPortal3 = 7034, eItm_TownPortal4 = 7072,*/ eItem_Resurrect1 = 7031, eItem_Resurrect2 = 7039, eItm_Permenent = 2, eItm_Decay = 0};
enum { eItem_amala = 6614, eItem_jade = 6551, eItem_Resurrect80 = 7031, eItem_Resurrect100 = 7039, eItm_SummonParty = 7078, };
enum { eItem_Init2ndClass = 7050, eItem_ChangeHair = 7051, eItem_ChangeFace = 7052, eItem_ChangeSex = 7053, eItem_ChangeGuildMark = 7054, eItem_ChangeOldHair = 7055, eItem_ChangeOldFace = 7056, eItem_ChangeOldGuildMark = 7057};
enum { eItem_InitSkill = 7061, eItem_InitChar = 7062, eItem_InitSkillChar = 7063, };
enum { eItem_BattleOrder = 7043, eItem_Extra = 7038, eItem_PartyPenalty = 7048, eItem_NoLimitPortal = 7049, eItem_Pt4 = 7067, };
enum { eItem_GoldSmall = 7383, };

enum { eZone_Mandra = 1, eZone_Shambala =2, eZone_Pamir = 8, eZone_Cruma = 10, eZone_Chaturanka = 11, eZone_Katacomb = 12, eZone_Kalia1 = 13, eZone_Kalia2 = 14, eZone_Kalia3 = 15, eZone_Stronghold = 16, eZone_Castle = 17, } ;
enum { eCls_MaxLevel = 3, eCls_MaxSpecialized = 8, } ;
enum { eHack_MaxAttackTimeRecordCount = 5, eHack_MaxAttackTimeGap = 1500, } ;
enum { eConst_LevelGap = 15, eConst_TooFarRange = 80, eConst_MaxAffectionCount = 63, eConst_CantTrace = 2, } ;
enum { eDur_Indestructible = 25500, eLvl_Max = 255, } ;
//enum { ePK_Restriction = 20, ePK_Murder = 0, ePK_RwdBramanPoint = 50, ePK_DecKarmaPoint = 250, ePK_RwdKarmaPoint = 100, ePK_IncKarmaPoint = 500, ePK_RwdGold = 45, ePK_LoseGold = 50, ePK_MaxKarma = 30000, ePK_MurderDropRate = 10, eHnt_High = 5, eHnt_Low = 1, } ;
//enum { ePK_PKDurationTime = 180000, ePK_AttackSize = 4, } ;
enum { eRvRZone_Count = 10, } ;
enum { eCon_JudgeCombat= 10, eCon_MaxGapCount = 101, eCon_LastIndex = 40, eCon_PrtyCount = 3, eCon_MaxGap = 20, eCon_Sort = 2, eCon_DF = 0, eCon_RS = 1, eCon_DG = 2, } ;
enum { eHnt_Novice = 10, eHnt_DecPrana = 10, } ;
enum { eRwd_ItemCount = 10, eRwd_ItemGroup = 21, eRwd_ItemGroupCount = 101, eMonster_MaxLevel = 31, eItm_MaxLevel = 21, eItm_MaxCategory = 140, } ;
enum { eVar_Equipment = 0, eVar_Skill = 1, eVar_PassiveSkill = 2, eAfn_Add = 0, eAfn_Remove = 1, eAfn_Permanent = 0, eAfn_Buffer = 1, } ;
enum { eSkl_Melee = 0, eSkl_Range = 1, eSkl_Unit = 2, eSkl_Area = 3, eSkl_Death = 4, } ;
enum { eWhr_Equipment = 0, eWhr_Map = 1, eWhr_TradePane = 2, eWhr_Bag1 = 3, eWhr_Bag2 = 4, eWhr_Bag3 = 5, };
enum { eEqu_Weapon = 0, eEqu_Shield = 1, eEqu_Armor = 2, eEqu_Boots = 3, eEqu_Helmet = 4, eEqu_Belt = 5, eEqu_Neckrace = 6, eEqu_EarringL = 7, eEqu_EarringR = 8, eEqu_RingL = 9, eEqu_RingR = 10, eEqu_Bag = 11, eEqu_BraceletL = 12, eEqu_BraceletR = 13, eEqu_GauntletL = 12, eEqu_GauntletR = 13, } ;
enum { eStt_Base = 0, eStt_Changed = 1, eStt_Extra = 2, eStt_Braman = 0, eStt_Str = 1, eStt_Dex = 2, eStt_Vital = 3, eStt_Energy = 4, eCF_AttackRate = 5, eCF_DodgeRate = 6, eCF_BlockRate = 7, eCF_CriticalHitRate = 8, eCF_AC = 9,  };
enum { eRst_Fire = 0, eRst_Cold = 1, eRst_Lightning = 2, eRst_Poison = 3 } ;
enum { eTolr_Hold = 0, eTolr_Stun, eTolr_Sleep, eTolr_Terror, eTolr_Taunt, eTolr_SlowMove, eTolr_SlowAttack } ;
enum { eWaitAct_None = 0, eWaitAct_TownPortal = 1, eWaitAct_Quit, eWaitAct_ZonePortal, /*eWaitAct_TownPortal2, eWaitAct_TownPortal3,*/ eWaitAct_ServerDown, eWaitAct_Kickout, eWaitAct_SummonParty} ;
enum { ePortal_Gen = 0, ePortal_Guild, ePortal_SZiva, ePortal_Ziva, ePortal_Viryu, ePortal_NoLimit, };
enum { ePortal_Stronghold_SNW = 202, ePortal_Stronghold_SNE = 203, ePortal_Stronghold_SSW = 204, ePortal_Stronghold_SSE = 205, };
enum { ePortal_Stronghold_NW = 206, ePortal_Stronghold_NE = 207, ePortal_Stronghold_SW = 208, ePortal_Stronghold_SE = 209, ePortal_Stronghold_Front = 210, };
enum { /*eWaitTime_TownPortal = 5000, eWaitTime_TownPortal2 = 2000,*/ eWaitTime_Quit = 10000, eWaitTime_SummonParty = 5000, } ;
enum { eCmbt_Echo = -1, eCmbt_Normal = 0, eCmbt_Critical, eCmbt_Dodge, eCmbt_Blocked, eCmbt_Miss, eCmbt_MemoryTime = 60000, } ;
enum { eBlk_None = 0, eBlk_Forbidden = 1, eBlk_Pc = 2, eBlk_Monster = 3, eBlk_OutOfMap = 4, eBlk_SafeZone = 5 } ; // �̵��� block�� ����
enum { ePop_Succ = 0, ePop_CantPop, ePop_OutOfPopArea, ePop_InvalidCoord } ; // ���� pop�ÿ� ����ϴ� enum
enum { ePath_Succ = 0, ePath_OutOfActiveArea, ePath_Forbidden, ePath_Idential, ePath_OutOfMap, ePath_TooFar, ePath_Blocked } ; // path-finding���� enum
enum { eTNAI_TraceCount = 15 } ;
enum { eATDG_Count = 9, eConst_MaxInstantCoolDonw = 128, } ;
enum { eMonSkl_MaxIndex = 9, } ;
enum { eRds_MaxDetectEnemy = 20, ePos_MaxPosCount = 1681, } ;
//enum { eConst_MaxAbsorbDamage = 50, eConst_MaxReflectDamage = 50, } ;
enum { eKala_MaxCount = 9, eKalaAltar_MaxCount = 15, eKalaCore_Brahma = 8051, eKalaCore_Vishnu = 8052, eKalaCore_Siva = 8053, eKalaCore_Neutral = 8054, eKala_Neutral = 2923, eKala_Brahma = 2924, eKala_Vishnu = 2925, eKala_Siva = 2926, eKala_Event1 = 2927, eKala_Event2 = 2928, eKala_Event3 = 2929, } ;
enum { eReturnToShrine = 1, } ;
enum { eCaste_MaxLevel = 18, } ;
enum { eDly_TPRecv = 1000, } ;
//enum { eSpd_Min = 500, eSpd_Max = 25000, } ;
enum { eRealm_MaxCount = 5, eKalaRewarder_MaxCount = 3, } ;
enum { eEvent_MaxCount = 200, eTask_MaxCount = 512, eTask_Sort = 5, eTask_Param = 6, } ;
enum { eAggrScore_MaxCount = 10, } ;
enum { eFollower_MaxCount = 20, } ;
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
enum { eGetMoneyYut = 1, eGetMoneySale = 2, };

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


struct TNKALA_ALTAR_OLD // Į�� ����
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
	0,  1, 720, 438, 0, // �ù� ���
	1,  1, 720, 466, 0, // ���, installed
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
	1,  1, 844, 153, 0, // �� ���� 1
	2,  1, 933, 153, 0, // �� ���� 2
	3,  1, 708, 160, 0, // ��� 1
	4,  1, 708, 118, 0, // ��� 2
	5,  2, 402,  97, 0,
	6,  2, 103, 139, 0, // �� ���� 1
	7,  2, 203, 140, 0, // �� ���� 2
	8,  2, 125, 568, 0, // ��� 1
	9,  2,  83, 568, 0, // ��� 2
	10, 4, 132, 915, 0, // �ʼ�
	11, 4, 476, 844, 0, // �� ���� 1
	12, 4, 476, 934, 0, // �� ���� 2
	13, 4, 803, 938, 0, // ��� 1
	14, 4, 803, 896, 0, // ��� 2
	
} ;



struct TNSTRONGHOLD
{	
	int		iID ;
	int		iOwner ; // guild ID
	int		iOwnerFriend;
	char	szGuildName[SZNAME_LENGTH] ;
	DWORD	dwMark;
	CTime	kTimeOccupied ;
	int		irgDestroyer[2] ; // ��¡���� �ǰ� guild ID ����, �ʱ�ȭ�Ǿ�� �Ѵ�.
	// date, ��Ÿ���
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
	short sCount ; // -1:unlimited, 0<:����Ƚ��
	short srgTask[eTask_Sort] ;
	unsigned int uiAvailableTime ; // trigger�� �� �ִ� ��, ���� time�� �� ��ġ���� ������, event�� trigger���� �ʴ´�.(variable)
	unsigned int uiCoolDownTime ; // event�� �󸶳� ���� trigger�� �� �ִ°�~(static)
	int iDuration ; // ���ӽð� type, 0�̸� ��� �̿밡��, 0�̻��̸� ���� �ð����� �̿� ����, -1�̸� �̿� �Ұ�
	unsigned int uiDurationTime ; // ������ �ð������� ��� time �� ����
	short sClan ;
	short sProceedType ; // event�� ��ϵ� task�� sequential�ϰ� ����Ǿ�� �ϴ°�? 1 �̻��̸� �������� ���� ó���� ���Ѵ�. �� ���� ���� �����ϸ� �װ����� ������.
} ;


struct TNTASK
{
	int iActionID ;
	int irgParam[eTask_Param] ;
	TNTASK() : iActionID(0) {} 
} ;


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
	int irgPierce[2] ; // ���� �����ϴ� damage
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
	int iDodgeSpeed ; // ȸ�� delay �ð�
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
	TNREQUIREMENT() : byTrimuriti(0xFF), byTribe(0xFF), byLevel(0), iClass(0xFFFFFFFF),sMuscle(0), sNerves(0), sHeart(0), sMind(0) {}
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
	short sID ;
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
		short sData1 ; // low(���� ��)
		short sData2 ; // high(���� ��)
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
	short sID ;
	short sType ; //
	int iAttackSpeed ;	// �ߵ��ϱ���� �ɸ��� �ð�, ����� ����, skill�� casting time �̴�.
	//int iApplyTime ;  // 
	int iActivateTime ;
	int iCoolDownTime ;
	int iCastDuration ; // �ߵ��� �Ŀ� ��� ����� ���ϴ� �ð�, -1:passive, 0:instant, 0<:���ӽð�(��;�ִ�120��)
	int iRange ;
	int iAOE ;

	byte byLevel ;
	byte byMaxLevel ;
	byte bySyncFlag ;
	byte byCastCount ;

	//char iRange ;  // -2:unlimited, -1:weapon-base, 0:self, 0<:range
	//char iAOE ; // -1:N/a, 0:Unit, 0<:�����ݰ�	
	//byte byDummy2 ;
	//byte byDummy3 ;

	byte bySuccessRate ;
	byte byFollow ; // follow�� ���ư��� �ִ� ��Ÿ�
	byte byPierceRate ; // ���� Ȯ��	
	byte byArmorType ;
	
	short sProperty ;
	short sCombatPhase ;
	short sSpeak ;
	short sSkillType ;
	int iAllowedTargets ;

	TNEFFECT krgEffect[TN_MAX_EFFECT_COUNT] ;
	TNCOST kCost ;
	TNREQUIREMENT kReq ;

	// item Ư��
	int iPrice ;
	short sEventID ;
	short sMaxDur ;
	short sItemType ;
	byte byMaxPackCount ;
	byte byDecay ;
	TNDAMAGE kDamage ;

	// skill Ư��
	
	int iReqWeapon ;
	int iReqItem ;
	struct TNBASE_SKILL
	{
		short sID ;
		byte byLevel ;
		byte byDummy ;
	};
	TNBASE_SKILL kReqSkill[2] ;
};

typedef struct TNSKILL_DATA	TNITEM_DATA ;



struct TNAFFECTION
{
	TNEFFECT kEffect ;
	unsigned int uiExpireTime ; // �Ϸ� �ð�
	unsigned int uiStartTime ;
	int iPartyLeader ;
};



struct TNATTACKER
{
	int iID ;
	int iDamage ; // score�� ��Ÿ����.
	int iScore ;
	unsigned int uiReleaseTime ;
	TNATTACKER() : iID(0), iDamage(0), iScore(0), uiReleaseTime(0) {}
} ;


struct TNLASTEST_TIME
{
	unsigned int uiActivate ; // Ȱ���� �����ϴ� �ð�, �� ��ġ���� ũ�� Ȱ���� �Ѵ�.
	unsigned int uiMoved ;
	unsigned int uiAttackedOld ; // ���� ���� ���� �ð�
	unsigned int uiAttacked ; // ���� ���� �ð�
	unsigned int uiDamaged ;
	unsigned int uiKilled ;
	unsigned int uiHealed ;
	unsigned int uiSitted ;
	unsigned int uiSelectTarget ;
	unsigned int uiCombat ;
	unsigned int uiMoveChecked ;
	unsigned int uiDodged ;

	void Init( unsigned int a_uiTime )
	{
		uiMoved = uiAttacked = uiAttackedOld = uiHealed = a_uiTime ;
		uiActivate = uiKilled = uiSitted = uiSelectTarget = uiCombat = uiMoveChecked = uiDodged = 0 ;
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
	short sSkill ;
	short sState ;
	short sEvent ;
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

	eTNRes_InvalidTarget = 10,
	eTNRes_InvalidCoord = 11,
	eTNRes_IsNotFound = 12,
	eTNRes_SafetyZone = 13,
	eTNRes_BlockedZone = 14,
	
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

	eTNRes_TargetSelf = 40,
	eTNRes_TargetClan = 41,
	eTNRes_TargetNovice = 42,

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

	eTNRes_InvaldSlotIndex = 60,
	eTNRes_AltarIsNotEmpty = 61,

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



// bit vector �� �Ѵ�.
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



// affection�� ���ÿ� ���� ������ ���� �� �ֱ� ������ bitvector�� ���� ����� ��� �Ѵ�.
// skill(magic)�� ���� ������ �޴� ��ϵ��� �����Ѵ�.
typedef enum _ETNAffectionState
{
	eTNAfn_None = 0,
	eTNAfn_Damage = 1,
	eTNAfn_DamageSplash = 2,
	eTNAfn_EnergyOfSword = 3,
	eTNAfn_PierceDamage = 4, // phycical, ���� 100% ����
	eTNAfn_DamageTP = 5, // TP�� ���δ�.
	eTNAfn_PercentDamage = 6, // Max HP�� ���� % HP�� ���δ�.
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
	eTNAfn_SummonFellow = 140,
	eTNAfn_SummonInteractor = 150,
	eTNAfn_SummonRetainer = 160,
	eTNAfn_Invisible = 1060,
	eTNAfn_WizardEyes = 1065,
	eTNAfn_Hold	= 2000,
	eTNAfn_Hold2 = 2005, // seidge mode
	eTNAfn_Stun = 2010, // ����
	eTNAfn_Sleep = 2020, // ��
	eTNAfn_Blind = 2040, // ���, �þ߸� 1�� ���δ�.
	eTNAfn_Concentration = 2210,
	eTNAfn_Disruption = 2220,
	eTNAfn_Invulnerable = 2230,
	eTNAfn_Immunity = 2240,
	eTNAfn_Immunity2 = 2241,
	eTNAfn_MagicShield = 2500,
	eTNAfn_ManaShield = 2510,
	eTNAfn_SpiritLink = 2520,

	// Ư�� �뵵
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
	eTNAfn_Terror = 3140, // �������� �Ѵ�.
	eTNAfn_Taunt = 3150, // �� �÷��� �����ϰ� �Ѵ�.
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
	eTNAfn_100PCriticalHit = 3270, // 100% ũ��Ƽ�� ��Ʈ
	eTNAfn_Recall = 3280,
	eTNAfn_Weakness = 3290,
	eTNAfn_SuccessRate = 3300,
	eTNAfn_SummonParty = 3310,
	eTNAfn_MoveToTheMandraTown = 3320,

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
	eTNAfn_FixedDamagePlus = 4270, // ��� �Ŀ� ���� �ܰ迡�� �߰��ȴ�.
	eTNAfn_FixedDamageMinus = 4271,
	eTNAfn_FixedDamagePlus2 = 4280, // ��� �Ŀ� ���� �ܰ迡�� �߰��ȴ�.
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
	eTNAfn_PerfectDodge = 4560,
	eTNAfN_PetGrowth = 4570,

	//	Sub Refining Effect
	eTNAfn_RefiningJade		= 4610,		//	������ �Ҹ����
	eTNAfn_RefiningDiscount	= 4620,		//	���ú�� ����
	eTNAfn_RefiningRateUp	= 4630,		//	����Ȯ�� ���
	eTNAfn_RefiningProtect	= 4640,		//	������� �Ҹ����

	// etc
	eTNAfn_Birth		= 10000,
	eTNAfn_Death		= 10010,
	eTNAfn_FireFX		= 10020,
	eTNAfn_UnPack		= 10030,
	eTNAfn_IWantIt		= 10040,
	eTNAfn_MicroSound	= 10041,

} ETNAffectionState ;


// client�� affection ������ �˷��ֱ� ���� bit-vector�̴�.
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
	eTNVSAfn_MagicShield			= 0x00001000, // �Ƽ��� - �Ķ�ī
	eTNVSAfn_Hold2					= 0x00002000, // seidge mode	
	eTNVSAfn_ManaShield				= 0x00004000, // ���� - ��������
	eTNVSAfn_ReflectDamage			= 0x00008000,
	eTNVSAfn_RecoverTP				= 0x00010000,	
	eTNVSAfn_Heal					= 0x00020000, 
	eTNVSAfn_Weakness				= 0x00040000,
	eTNVSAfn_Reserved1				= 0x00080000,
	eTNVSAfn_Reserved2				= 0x00100000,
	eTNVSAfn_ProtectFromMonster		= 0x00200000,
	eTNVSAfn_MoveSpeedPlus			= 0x00400000,
	eTNVSAfn_MoveSpeedMinus			= 0x00800000,  
	eTNVSAfn_AttackSpeedPlus		= 0x01000000,
	eTNVSAfn_AttackSpeedMinus		= 0x02000000, 
	eTNVSAfn_NPCSymbol				= 0x04000000,
	eTNVSAfn_ProtectAll				= 0x08000000,
	eTNVSAfn_HaveKalaCore			= 0x10000000,
	eTNVSAfn_ProtectFromPK			= 0x20000000, // 30
	eTNVSAfn_PKAttacker				= 0x40000000, // ����������
	eTNVSAfn_BlessOfGod				= 0x80000000, // eTNVSAfn_HaveKalaCore�� ���� �ߺ����� �ʴ´�.

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
	eTNInAfn_PerfectDodge			= 0x00000100,
	
} ETNVisualAffection ;


typedef enum _ETNInnerAffection
{
} ETNInnerAffection ;


typedef enum _ETNEye // ���� ���ϴ� ����� bit vector�� ��ϵǾ�� �Ѵ�.
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
	//eTNImm_Invulnerable			= 0x00000800, // 10
	//eTNImm_MagicShield			= 0x00001000,
	//eTNImm_Heal					= 0x00002000,
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
	//eTNImm_Elemental			= 0x10000000,
	//eTNImm_Elemental			= 0x20000000,
	//eTNImm_Elemental			= 0x40000000,
	//eTNImm_All				= 0x80000000, // �����δ� �Ʒ��� ���� ��� bit�� 1�� ��쿡 ���� ���� ������ �Ѵ�.
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
	//eTNVar_EnhanceHardness = 38, // ������ �������� ���δ�.
	eTNVar_DamageBonusForNextAttack = 38,
	eTNVar_RangeDown = 39,
	eTNVar_EnhanceNecklace = 40,
	eTNVar_EnhanceArmor = 41,
	eTNVar_EnhanceBelt = 42,
	eTNVar_PetGrowthHP = 43,
	eTNVar_PetGrowthDamage = 44,
	eTNVar_PetGrowthAttackSpeed = 45,
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


// ��� one-hand weapon
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
	// �Ʒ��� 6���� combat progress�� ��Ÿ����. bit�� check�� �Ǿ� ������ �� ������ �����Ѵ�.
	eTNCPhase_CastInstant1		= 0x0001,  // caster �ڽſ��� ���, damage up/down �迭
	eTNCPhase_CastInstant2		= 0x0002,  // caster �ڽſ��� ���, �߰����� damage ���� effect, pierce strike, critical-strike, multiple-strike
	eTNCPhase_DealDamage		= 0x0004,  // caster �ڽſ��� ���, deal damage
	eTNCPhase_CastInstant3		= 0x0008, // caster �ڽſ��� ���, steal �迭
	eTNCPhase_OnTakeInstant1	= 0x0010, // target(corpse)���� �������� ȿ���� ����
	eTNCPhase_OnTakeInstant2	= 0x0020, // target(alive)���� �������� ȿ���� ����
	eTNCPhase_OnAffect			= 0x0040, // target(alive)���� ���������� ȿ���� ��Ÿ����
	eTNCPhase_AffectSelf		= 0x0080, // �ڽſ��� ���������� ȿ���� ��Ÿ����, target�� �ڽ� �̿��� ��������� �ڽ����׵� ������ ���ľ��� ��쿡�� ����Ѵ�. ���� selt buff�� �ٷ� ���� eTNCPhase_OnAffect�� ����Ѵ�.
	eTNCPhase_Taunt				= 0x0100, // 256
	eTNCPhase_StartAction		= 0x0200, // �ڽſ��� Ư���� action�� �ߵ���Ų��. , 512
	eTNCPhase_OnChargInstance	= 0x0400, // �ڽſ��� Ư���� action�� �ߵ���Ų��. , 1024
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
	eTNCell_SafetyZone					= 0x0001,
	//eTNCell_Collision					= 0x0002, // ������ �̷��� ����
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
	eTNClan_Friendly = 0, // 0�� ��ȣ�̴�.
	eTNClan_Hostile = 11, // 11 ���� hostile�̴�.

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

// ������ �߸��Ǿ� �ִ�.
typedef enum _ETNClass
{
	eTNMob_PC = 0,
	eTNMob_NPC,

	eTNCls_1st = 0,
	eTNCls_2nd,
	eTNCls_3rd,

	// NPC ���� ���
	eTNCls_Pet	= 9,
	eTNCls_Warrior = 10, // �Ϲ� ����(������)
	eTNCls_Summon = 11, // ��ȯ ����
	eTNCls_SummonOld = 12,
	eTNCls_Follower = 13, // (������)
	eTNCls_Trap = 14, // ����
	eTNCls_Fellow = 15,
	eTNCls_Event = 17,// not use
	eTNCls_Quest = 18, // quest ���� mobile
	eTNCls_NPC = 19,	 // 19, client���� contact_npc �޽����� �����Ѵ�.

	/*
	eTNCls_Mount, // Ż��(��������), Pet�̶� ��ġ�� �κ��� �� �ִ�. pet�� mount ���������� �˻��Ѵ�.
	eTNCls_Guard, // (������), �� Ÿ���� �ʿ�������?
	eTNCls_Guider,   // tutorial�� ���� ������ �����鿡�� �˸��� ����
	eTNCls_Merchant, // ����(��������)
	eTNCls_Keeper, // ������(��������)
	*/


	// ���� ����ȭ
	eTNCls2_Basic = 0,
	// class1�� summon�� ���	
	eTNCls2_Tracker = 1,
	eTNCls2_Familiar = 2, // �ܼ��� ���ݸ� �ϴ� �йи���
	eTNCls2_Summoned = 3,
	eTNCls2_Retainer = 4,
	//
	eTNCls2_Guard, // ��ó�� ��ȯ�Ǿ ��ȯ�ڸ� ��ȣ�Ѵ�.
	//eTNCls2_Soldier, // ���簳��
} ETNClass ;



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
	eMonPrty_BlockedCell, // �̵� ���ϴ� cell ����
	eMonPrty_CantDetect, // �������� ���ϴ� affection����
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
	eTNAI_HitEnemy, // critical hit�� ���� ������ ��,
	eTNAI_Miss,
	eTNAI_BeHitted, // critical hit�� �¾��� ��
	eTNAI_Dodge,
	eTNAI_Trace,
	eTNAI_GiveUpToTrace,
	eTNAI_KillEnemy,
	eTNAI_Help2,
	eTNAI_Link2, // 20
	eTNAI_Guard2,
	eTNAI_BeKilled2,
	eTNAI_UnderAttack2,	
	eTNAI_CantTrace,  // ��ġ�� event
	eTNAI_StopToAttack, // �� ���� ����
	eTNAI_Return,
	eTNAI_Flee,
	eTNAI_Lead,
	eTNAI_Pop,
	eTNAI_Dialog1,  // 30
	eTNAI_Dialog2,  
	eTNAI_Dialog3,
	eTNAI_Dialog4, // 33

	eTNAI_MaxAICount = 100,
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
	eTNAct_PopMonster					= 100,
	eTNAct_PopMonster2					= 101,	
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
	eTNAct_ReturnPrevPos				= 1040,
	eTNAct_Teleport						= 1050,
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
	eTNAct_KillAll						= 2000,
	eTNAct_KickOut						= 2010,
	eTNAct_KillPC						= 2020,	
	eTNAct_CheckKalaSystem				= 2030,
	eTNAct_PrintKalaCoreInfo			= 2040,
	eTNAct_MoveTheGateOfDungeon			= 2050,
	eTNAct_OnKilledLeftGeneral			= 2060,
	eTNAct_OnKilledRightGeneral			= 2070,
	eTNAct_KillMonsterInSquare			= 2080,
	eTNAct_ChangeField					= 2090,
	eTNAct_AffectAll					= 2100,
	eTNAct_DebufferAll					= 2101,
	eTNAct_AffectAEffectToClanMonsters	= 2200,
	eTNAct_ChangeClanByTribe			= 2210,
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
	eTNAct_Mine							= 9000,
	eTNAct_PostMessageToZone			= 10000,
	eTNAct_PostMessageToWorld			= 10010,
	eTNAct_RecordName					= 10020,
	eTNAct_PostStrongholdOwner			= 10030,
	eTNAct_RecordPCNameInZone			= 10040,
	eTNAct_KillKingAtChaturangka		= 20000,
	eTNAct_CloseKingRoomAtChaturangka	= 20010,	
	eTNAct_CountRealmEntry				= 20020,
	eTNAct_CountMonster					= 20100,
	eTNAct_CountMonsterByTribe			= 20101,
	eTNAct_TeleportAll					= 20110,
	eTNAct_ReturnToSaveZone				= 20120, // �����δ� �������� �Լ��� �ƴϴ�.
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
	eTNAct_KickOutLosser				= 21000,
	eTNAct_JudgeTheSiege				= 21010,
	eTNAct_PopSymbolForSiege			= 21020,
	eTNAct_RecoverClanToOriginal		= 21030,
	eTNAct_SwitchSiege					= 21040,
	eTNAct_PostTheResultOfTheSiege		= 21050,
	eTNAct_FixTheDateOfTheSiege			= 21060,
	eTNAct_SwitchExpireOfTheTermForSiege = 21070,
	eTNAct_PostTheScheduleForTheSiege	= 21080,
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
	// audit purpose
	eTNAudit_Boss				= 0x00000001,
	eTNAudit_LifeCycle			= 0x00000002,

	// react by path blocked
	eTNReact_Pass			= 0x00000001,
	eTNReact_Ignore			= 0x00000002,

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


typedef enum _ETNSwitch  // 1�� ���� off�� ���̴�. 0�� ���� on
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


typedef enum _ETNProduction  // ���� ȿ��
{
	eTNPrdt_PopNormal = 0, // �׳� ���������� ���ϰ� ��Ÿ��, ������ ������ �ձ׷� FX�� ����
	eTNPrdt_PopRaise = 1, // ���� �Ʒ����� ������ ���� ���� �ö���� ����
	eTNPrdt_PopDescend = 2, // ���� ������ �������� ������ �����´�.(���ӵ�:0)
	eTNPrdt_PopFallDown = 3, // ���� ������ �������� ���ӵǸ鼭 ������.(�ϴÿ��� ��ü�� �������� ����, �������� ���󹮿� ���� ����)

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
	eTNCasteRank_Cushatri3 = 248,
	eTNCasteRank_Cushatri2 = 168,
	eTNCasteRank_Cushatri1 = 118,
	eTNCasteRank_Braman3 = 88,
	eTNCasteRank_Braman2 = 63,
	eTNCasteRank_Braman1 = 43,
	eTNCasteRank_Avatara3 = 28, 
	eTNCasteRank_Avatara2 = 18,
	eTNCasteRank_Avatara1 = 11,
	eTNCasteRank_MahaRaja3= 6,
	eTNCasteRank_MahaRaja2 = 3,
	eTNCasteRank_MahaRaja1 = 1,
} ETNCasteRank;

typedef enum _EGuildLevel
{
	eGuildMaster		= 10,
	eGuildSubMaster		= 9,
	eGuildThird			= 8,
	eGuildForth			= 7,
	eGuildMember		= 0,
} EGuildLevel;

/*********************************************/
//	2004.08.26(�ɷ�ġ, ��ų �ʱ�ȭ ������Ŷ)
typedef enum _ENPCCommandTYPE
{
	eInitSkill			= 1,
	eInitChar			= 2,
	eInit2ndClass		= 3,
	eInitSkillChar		= 4,
	eEvent				= 5,
} ENPCCommandTYPE;

typedef enum _ECommand
{
	eSearch				= 1,
	eRun				= 2,
} ECommand;
/*********************************************/

//#define __TN_CHANGE_5LVL__
//#define __TN_PLAYMOVIE__
//#define __TN_LOCAL_SERVER_SWITCH__
//#define __TN_EMERGENCY_LOG__
#define __TN_TOP_LOG__
#define __DYNAMIC_LOG__
//#define __TN_1ST_LOG__
//#define __TN_2ND_LOG__
//#define __TN_3RD_LOG__
//#define __TN_4TH_LOG__
//#define __TN_5TH_LOG__


#define SKIPCHECKTICK  235543242


#define TRIMURITI_BRAHMA	1
#define TRIMURITI_VISHNU	2
#define TRIMURITI_SIVA		4

#define	TRIBE_NONE			255		// ���� ���� ����
#define TRIBE_NAGA			1		// ����
#define TRIBE_KINNARA		2		// �Ƽ���
#define TRIBE_ASURA			4		// ��ũ��
#define TRIBE_RAKSHASA		8		// ����
#define TRIBE_YAKSA			16		// Ų����
#define TRIBE_GANDHARVA		32		// ��ũ����
#define TRIBE_DEVA			64		// ���ٸ���
#define TRIBE_GARUDA		128		// �����

#pragma	pack(push, 1)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// �ʿ� ���õ� ���
namespace _MAP_MANAGER
{
	const int NAME_LEN = 26;						// �� �̸� ����
	const int CELLS_PER_GRID = 4;					// �׸��� �� �� ����
	const int CELLS_PER_CS = 4;						// CriticalSection�� �� ����
	const int LIST_COUNT_ON_CELL = 3;				// �� ��(�׸���)�� ������Ʈ ����Ʈ ����
	const int VIM_CHANGE_RANGE = 1;					// VIM ���� ����
	const float VIM_CHANGE_VALUE_SIDE = 0.5f;		// ���� ���� VIM ���� ��
	const float VIM_CHANGE_VALUE_CORNER = 0.25f;	// �밢�� ���� VIM ���� ��
	const int DEFAULT_FIND_ARRANGE_DISTANCE = 5;	// �⺻ ��ġ ������ġ �˻� ����
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
	DWORD	dwIndex;		// ���� ���� Index(������).
	SHORT	snStartX;		// ���� ���� ���� X ��ǥ
	SHORT	snStartZ;		// ���� ���� ���� Z ��ǥ
	SHORT	snEndX;			// ���� ���� �� X��ǥ 
 	SHORT	snEndZ;			// ���� ���� �� Z��ǥ
};

struct _S_TRIMURITY_AREA
{
	BYTE	byTrimuriti[4];
	_S_GOBJ_GENERATIONAREA_PARAMS pArea[4][MAX_TRIMURITY_AREA];
};

typedef struct _S_GOBJ_MONSTER_RANGE
{
	int		nStartX;	// X ��ǥ(����)
	int		nStartZ;	// Z ��ǥ(����)
	int		nEndX;		// X ��ǥ(����)
	int		nEndZ;		// Z ��ǥ(����)
	int		nHeight;
}S_MonsterRange;

struct _TNAREA_PROPERTY
{
	enum { eBhvCond_Aggr = 0, eBhvCond_Flee = 1 } ;

	unsigned int uiMonsterID ; // 0�� �ƴ� ���� ������ loading�� �����Ѵ�.
	int iDeployCount;  // pop ��

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
#define FLAG_GAME2CLIENT                0x0100          // ������ ������ �޽���        256   //
#define FLAG_CLIENT2GAME                0x0200          // Ŭ���̾�Ʈ�� ������ �޽���  512   //

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
	char		AccountName[ACCOUNTNAME_LENGTH];	//	���� ID
	char		AccountPass[ACCOUNTPASS_LENGTH];	//	���� ���
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
	char												szCharName[SZNAME_LENGTH];		// �˻��� ĳ���� �̸�
} S_SSP_REQ_CHARACTER_SEARCH, *PS_SSP_REQ_CHARACTER_SEARCH;
// GSCP_INIT_CHAR : 0xA547
typedef struct _S_SSP_RESP_CHARACTER_SEARCH
{	_MSG;
	int													nID;
	BYTE												byResult;						// �˻� ���( 0:����, 1:����)
	BYTE												byZone;							// ĳ���� ��ġ�� ��
	SHORT												snDummy;
	char												szAccountID[ACCOUNTNAME_LENGTH];// �˻��� ĳ���� ����.
	char												szCharName[SZNAME_LENGTH];		// �˻��� ĳ���� �̸�.
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
		  unsigned int   Exp;//���� �ڽ��� ���� ����ġ�� �����ش�-��������� ����ġ
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
		unsigned short Equip[MAX_EQUIP];     //   | 0000 | 0000 | 0000 | 0000   4��Ʈ ���� 12��Ʈ ������
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
	      int RemoveType;   // 0:�̵��� ���� Ŭ���� ������   1:��� ����  2:�α׾ƿ� ����  3:�̵��� �������� �̵��� �Ϸ�.
};
#define	 _MSG_Action		                (102 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct    MSG_Action
{    	 _MSG;
		  int		dwKeyID; 
          short		PosX,PosY;
	      int		Speed;
		  short		Effect;		// 0:�ɱ�  1:����  2:�ȱ�  3:�ٱ�  4:����  5:�ڷ���Ʈ,	6:�и���(knock-back), 7:�̲�������(�̵��ִϾ���)  8:����, 9:�λ�, 10:���� 
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
		short 				SkillIndex;		// 0-98-106  (-1�̸� ������ ����)
        short				CurrentMp;
		// ���� byte 2���� �ذ�Ǵ��� ����
		unsigned char		Motion;
		unsigned char		SkillParm;		// ��ų ȿ�� ������ �Ǵ� �������� ����Ʈ. 0 �� ����Ʈ.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0��Ʈ ���� 1��Ʈ ũ��ƼĮ

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
{        _MSG;   // ID�� client
          int ItemID;
          short State;                        // [���ϴ¹ٲ����] 0:�̵������ƴѰ� 1:������  2:������   3:��乮     
		                                    // lock�� unlock�� key�� �ִ� ��츸.
		                                    // �������� ó���� ����..
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
	     short      BonusType;    // ���ʽ� ��з� 0:ScoreBonus 1:Special 2:Skill
	     short      Detail;       // ���ھ� 0:Str        1:Int      2:Dex      3:Con
		                          // ����� 0:Special1   1:Special2 2:Special2 3:Special4
		                          // �����ȣ  1000-1071  (Detail-1000)/24=Class   (Detail-1000)%24=SkillNumber
		 unsigned short TargetID;
};

#define _MSG_SetShortSkill                 (120 | FLAG_CLIENT2GAME)
struct   MSG_SetShortSkill
{
	    _MSG;
		char  Skill[12];              // ��ų��ȣ 0-23
};

//#define _MSG_Buy                           (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
//struct   MSG_Buy
//{
//	    _MSG;
//		unsigned short TargetID;                // ����� ���� NPC ID
//		short TargetInvenPos;          // ����� ������ Inven ��ġ.
//		short MyInvenPos;              // �缭 �������� ���� Inven ��ġ.
//		int   Coin;
//};
//
//#define _MSG_Sell                          (122 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
//struct   MSG_Sell
//{
//	    _MSG;
//		unsigned short TargetID;                // �ȷ��� ���� NPC ID
//		short MyType;
//		short MyPos;                // ���� �� �������� Inven
//};
#define _MSG_REQShopList                  (123 | FLAG_CLIENT2GAME)
struct   MSG_REQShopList                 // Ŭ���̾�Ʈ�� �������� Leader�� ���. 
{                                        // ������ �������� ��ü ����Ʈ
	    _MSG;
		 unsigned short TargetID;
};
#define  _MSG_ShopList                   (124 | FLAG_GAME2CLIENT )
struct    MSG_ShopList
{
	      _MSG;
		  int         ShopType;              // 1:����  2:ī��(�Ⱦ�����)  3:��ų
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
         STRUCT_ITEM    Inven[MAX_INVEN];
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

#define _MSG_ReqChallange                    ( 141 | FLAG_GAME2CLIENT ) // STANDARD       ������ Ŭ���̾�Ʈ���� Ok,Cancel�� ��ȸ�� �ش�.
#define _MSG_Challange                       ( 142 | FLAG_CLIENT2GAME)  // STANDARDPARM Parm�� Ÿ�� ���̵�.
#define _MSG_ChallangeConfirm                ( 143 | FLAG_CLIENT2GAME)  // ReqChallange�� ���� Ŭ���̾�Ʈ�� �����̴�.
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
         char           Desc[MAX_DESC]; // �ѱ� 11�� // �Ĵ»���̸��� ID���� ���Ѵ�.
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
		short 				SkillIndex;		// 0-98-106  (-1�̸� ������ ����)
        short				CurrentMp;
		unsigned char		Motion;
		unsigned char		SkillParm;		// ��ų ȿ�� ������ �Ǵ� �������� ����Ʈ. 0 �� ����Ʈ.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0��Ʈ ���� 1��Ʈ ũ��ƼĮ

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
		short 				SkillIndex;		// 0-98-106  (-1�̸� ������ ����)
        short				CurrentMp;
		unsigned char		Motion;
		unsigned char		SkillParm;		// ��ų ȿ�� ������ �Ǵ� �������� ����Ʈ. 0 �� ����Ʈ.
		unsigned char		FlagLocal;		//
		unsigned char		DoubleCritical;     // 0��Ʈ ���� 1��Ʈ ũ��ƼĮ
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
#define _MSG_CombineComplete					(167 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM  0:��� 1:���� 2:����
#define _MSG_WarInfo							(168 |FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)  // STANDARDPARM  ������ ���, 0�� ����
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
//               NP ����   - >   DB ����
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define FLAG_DB2NP                      0x1000        
#define FLAG_NP2DB                      0x2000        

#define  _MSG_NPReqIDPASS            ( 1 | FLAG_DB2NP) //   ��ī��Ʈ �����
#define  _MSG_NPIDPASS               ( 2 | FLAG_NP2DB) //   ĳ���� �����
struct    MSG_NPIDPASS
{        _MSG;
		 int  nID;
		 char Account[ACCOUNTNAME_LENGTH];
		 int  Encode1;
		 char Pass[ACCOUNTPASS_LENGTH];
		 int  Encode2;
};
#define  _MSG_NPReqAccount           ( 3 | FLAG_NP2DB) //   ��ī��Ʈ ��ȸ
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
// 0:Success		1:Same Name Exist		2:No Space at Transper Server   3:Unknown Error	



/////////////////////////////////////////////////////////////////////
//       ���
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

//extern void BASE_SortTradeItem(STRUCT_ITEM * Item,int Type); // Buffer�� ũ��� int * Size
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
extern char		g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];   // "http://wydonline.co.kr/servers/server01.htm"
extern unsigned	g_pServerListBin[MAX_SERVERGROUP][MAX_SERVERNUMBER];   // "http://wydonline.co.kr/servers/server01.htm"
extern unsigned	short g_pServerListPort[MAX_SERVERGROUP][MAX_SERVERNUMBER];   // "http://wydonline.co.kr/servers/server01.htm"

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
#define MSV_SNOOP	0x01	// CreateMob�� ���޵Ǵ°��� 0-3��Ʈ
#define MSV_TOWN	0xC0	// ���� 2��Ʈ�� ���� �����̴�

#define                TIMER_SEC    0
#define                TIMER_MIN    1
#define                TIMER_HOUR   2

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

#define CSP_REQ_LOGIN                                     0x1001      // �α��� ��û �޽���
#define CSP_REQ_WORLD_LIST                                0x1002      // ���� ���� ����Ʈ ��û
#define CSP_REQ_MOVE_ZONE_SERVER                          0x1003      // ���� ��ǥ �������� ������ ��û
#define _Msg_VersionCheck								0x1004			//	Ŭ���̾�Ʈ�� ������ üũ�Ѵ�.
#define CSP_REQ_CHAR_LIST                                 0x1011      // �ش� ������ ĳ���� ����Ʈ ��û
#define CSP_REQ_CHAR_CREATE                               0x1012      // �ɸ��� ������ ��û
#define CSP_REQ_CHAR_REMOVE                               0x1013      // �ɸ��� ������ ��û
#define CSP_REQ_CHAR_SELECT                               0x1014      // �ɸ��� ������ ������ ���� ��û
#define CSP_REQ_EXIT_ZONE_SERVER                          0x1015      // ĳ���� ����â�� ����������, ���弭�� ����â���� �̵� ��û
#define CSP_REQ_CHAR_LOGOUT                               0x1021      // ĳ������ �α� �ƿ��� ��û
#define CSP_REQ_REMOVE_MOB								  0x1022      // ĳ���� �α׾ƿ�, ����, �����̵��� �ֺ����� ��û
#define CSP_OTHER_CHAR_LOGOUT_NOTIFY                      0x1023      // ĳ������ �α׾ƿ�, ����, �����̵��� ��Ƽ, ���, �ּҷ� ���� �ɸ��Ϳ��� ���ۿ�û
const int	_MSG_Status					=	0x1031;
struct MSG_Status
{
	_MSG
	int		nID;
	BYTE	byStatus;
	BYTE	byDummy1;
	short	snDummy1;
};
#define CSP_REQ_CHAR_INIT                                 0x1101      // ĳ������ �����ʱ����� ��û �޼���
const int	_MSG_InitSkill				=	0x1104;
struct MSG_InitSkill
{
	_MSG
	BYTE					bySkill[MAX_SKILL];
};

#define CSP_INIT_GUILD                                    0x1105      // �ڽ��� ����ʱ������� ������.
#define CSP_INIT_ADDRESS_BOOK                             0x1106      // �ּҷ� ���� ������ ��û
#define CSP_REQ_CHAR_HISTORY                              0x1108      // �ɸ��� �����丮���� ��û
#define CSP_INIT_EQUIPMENT                                0x1109      // �ɸ��� ������� ��û
//#define CSP_INIT_MONSTER_NPC                              0x1111      // �ֺ� Monster/NPC ���� ���� ��û
#define CSP_INIT_OTHER_MOB                                0x1112      // �ֺ� �ٸ� �ɸ��� ���� ���� ��û
#define CSP_INIT_REAL_ADDRESS_BOOK                        0x1113      // �ּҷ� ���� ������ ��û
#define CSP_INIT_REAL_GUILD                               0x1114      // ��� ���� ������ ��û
#define CSP_INIT_REAL_GUILD_MEMBER                        0x1115      // ��� ���� ������ ��û
#define CSP_INIT_ITEM                                     0x1121      // �ֺ� ������ ������ ó�� ��û �޼���
#define CSP_INIT_WORLD_USER_COUNT                         0x1161      // ���庰 �����ڼ��� ó����.
#define CSP_INIT_GUILD_MEMBER                             0x1171      // �ڽ��� ���������� ������.
#define CSP_REQ_CHAR_MOVE                                 0x1201      // ĳ���� �̵� ��û �޽���
#define CSP_OTHER_CHAR_MOVE                               0x1202      // ĳ������ �̵������� �ٸ� ĳ���Ϳ��� �˷���
#define CSP_MONSTER_MOVE_STEP                             0x1206      // �Ѽ� �̵��� �ֺ��� ����
#define CSP_MONSTER_MOVE_NSTEP                            0x1207      // ������ �̵��� �ֺ��� ����
#define CSP_MONSTER_MOVE_END                              0x1208      // ������ �̵��� ��� ��ǥ�� ����
#define CSP_REQ_ITEM_USE                                  0x1223      // ������ ��� ��û
#define CSP_ITEM_USE_BROADCAST                            0x1224      // ������ ����� �ֺ� �ٸ� ĳ���͵鿡�� ���� ��û
#define CSP_ITEM_REMOVE                                   0x1225      // �κ��丮���� ������ ������� ��û
#define CSP_REQ_CHAR_MOVE_BROADCAST                       0x1227      // �ɸ����� �̵��� ��û�Ѵ�.

#define CSP_REQ_ATK_CHAR                                  0x1301      // ĳ������ ���� ��û
#define CSP_ATK_CHAR_BROADCAST                            0x1302      // ĳ������ ������ �ֺ� ĳ���͵鿡�� ���� ��û
#define CSP_REQ_ITEM_EQUIPMENT                            0x1401      // ������ ������ ��û
#define CSP_ITEM_EQUIPMENT_BROADCAST                      0x1402      // ������ ������ �ֺ� ĳ���Ϳ��� ����
#define CSP_ITEM_ABRASION                                 0x1411      // ������ ������� �˸�
#define CSP_ITEM_ABRASION_BROADCAST                       0x1412      // ������ ������� �ֺ� �ٸ� ĳ���͵鿡�� ����

//	1501	CHAT
//	1601	GUILD
#define CSP_REQ_QUEST_HISTORY                             0x1701      // ����Ʈ �����丮 ���� ��û
#define CSP_QUEST_DIALOG                                  0x1702      // ��ȭ�� ��� ����
#define CSP_QUEST_NOTIFY_LEVEL                            0x1703      // ����Ʈ �ܰ� �˸�
#define CSP_CHAR_PING                                     0x1831      // �ɸ����� �������������� �˸���.
#define _MSG_Beauty							0x1912						//	�ɸ��� �̿��
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

#define _MSG_CLASS							0x1981				// �ɸ����� ������ ��û�Ѵ�.
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
#define CSP_REQ_SKILL_REGIST                              0x2001      // ��ų ����� ��û�Ѵ�
#define CSP_SKILL_REGIST                                  0x2002      // ī��Ʈ ��¿� ���� ��ų �ڵ� ����� �˷��ش�
#define CSP_REQ_SKILL_SELECT                              0x2003      // ��ϵ� ��ų�� ����/����
#define CSP_REQ_SKILL_SELECT_BROADCAST                    0x2004      // ��ϵ� ��ų�� ����/����
#define CSP_REQ_SKILL_USE2_CHAR                           0x2011      // ĳ������ ��ų ���� �غ����� ��û
#define CSP_SKILL_READY_CHAR_BROADCAST                    0x2012      // ĳ������ ��ų ���� �غ����� �ֺ��� ����
#define CSP_REQ_SKILL_ATK_CHAR                            0x2013      // ĳ������ ��ų ������ ��û
#define CSP_SKILL_ATK_CHAR_BROADCAST                      0x2014      // ĳ������ ��ų ������ �ֺ� ĳ���͵鿡�� ����
#define CSP_REQ_SKILL_LEVEL_UP                            0x2021      // ĳ������ ��ų Level-Up�� ��û
#define CSP_REQ_SHOP_SKILL_LIST                           0x2022      // ���� ������ ��ų List�� ��û
//	0x2201	TRADE
#define CSP_REQ_MY_ENTYR_LIST                             0x2305      // �ڽ��� ���,���� ������ ��û
#define CSP_REQ_TRADE_ITEM_SEEK                           0x2306      // ���� ������ ã�� ��û
//	0X2401	PARTY
#define CSP_REQ_TROUBLE_REPORT                            0x2541      // ������ �Ű����� �����Ѵ�.
#define CSP_REQ_TROUBLE_REPORT_LIST                       0x2542      // ������ �Ű����� ����Ʈ�� ��û�Ѵ�.
#define CSP_REQ_TROUBLE_REPORT_SET                        0x2543      // �Ű����� ó����Ȳ�� �޴´�.
#define GCSP_REQ_TROUBLE_REPORT_LIST                      0x2544      // �α��� ��û �޽���
#define GCSP_REQ_TROUBLE_REPORT_SET                       0x2545      // �α��� ��û �޽���
#define GCSP_REQ_TROUBLE_REPORT                           0x2546      // �α��� ��û �޽���
#define GCSP_REQ_PARAMETER_CHANGE                         0x2550      // ĳ������ �⺻ �������� ���� ��û
#define GCSP_REQ_ITEM_INSERT                              0x2551      // ������ ���� ��û
#define GCSP_REQ_ITEM_DELETE                              0x2552      // ������ ���� ��û
#define GCSP_REQ_SKILL_INSERT                             0x2553      // ��ų ���� ��û
#define GCSP_REQ_SKILL_DELETE                             0x2554      // ��ų ���� ��û
#define CSP_REQ_CHAR_INFO                                 0x2561      // �ɸ��� ���� ��û �޽���
#define CSP_REQ_CHAR_EQUIPMENT                            0x2562      // �ɸ����� �������� ��û �޽���
#define CSP_REQ_CHAR_SKILL                                0x2563      // �ɸ����� ��ų���� ��û �޽���
#define CSP_REQ_CLOSE_CHAR                                0x2571      // �ɸ����� �������� ��û �޽���
#define CSP_REQ_JOIN_ADDRESS_BOOK                         0x2603      // �ּҷϿ� ĳ���� �߰��� ��û
#define CSP_JOIN_ADDRESS_BOOK_NOTIFY                      0x2604      // �ּҷ� �߰� ��û�� ĳ���Ϳ��� ���ۿ�û �޼���
#define CSP_REQ_JOIN_ADDRESS_BOOK_RESULT                  0x2605      // �ּҷ� �߰� ��û ����� ������ ����
#define CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0x2606      // �ּҷ� �߰� ��û�� ���� ���� ����� ĳ���Ϳ��� ���ۿ�û�޼���
#define CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE                0x2607      // �ּҷϿ� �ִ� ĳ���� ������ ������ ��û
#define CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0x2608      // �ּҷϿ��� ������ �˸���
#define CSP_REQ_ADDRESS_BOOK_GROUP_ADD                    0x2611      // �ּҷϿ� �׷��� �߰��� ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_DELETE                 0x2612      // �ּҷϿ� �׷��� ������ ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_MOVE                   0x2613      // �ּҷϿ� �ɸ����� �׷��̵��� ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_RENAME                 0x2614      // �ּҷϿ� �׷��� �̸������� ��û
#define CSP_REQ_ADDRESS_BOOK_STATUS                       0x2621      // �ּҷ� ��Ͽ�û�� �źθ� ���ÿ�û
#define CSP_REQ_LEARN_SKILL                               0x3210      // Learn a skill
#define CSP_REQ_CAST_SKILL                                0x3220      // cast a skill
#define CSP_CAST_SKILL_BROADCAST                          0x3230      // cast a skill
#define CSP_CAST_UNIT_SKILL                               0x3240      // unit�� Ÿ������ �ϴ� ��ų
#define CSP_CAST_AREA_SKILL                               0x3250      // ground�� Ÿ������ �ϴ� ���� ��ų
#define CSP_DEBUFFER_SKILL                                0X3260      // ���ε� skill�� ���������� remove������ �˸���.
#define CSP_REQ_CHAR_ACT                                  0x3300      // Action
#define CSP_CHAR_ACT_BROADCAST                            0x3310      // Action�� broadcast
#define CSP_REQ_UPDATE_UI                                 0x3500      // Update UI
#define CSP_REQ_UPDATE_STATUS                             0x3501      // Update Status
#define CSP_LEVEL_UP_BROADCAST                            0x3510      // level up
#define CSP_REQ_INCREASE_CHAKRA                           0x3520      // Increase a chakra point

#define SCP_RESP_LOGIN                                    0x9001      // �α��� ���� �޽���
#define SCP_RESP_WORLD_LIST                               0x9002      // ���� ���� ����Ʈ ����
#define SCP_RESP_MOVE_ZONE_SERVER                         0x9003      // ���� ��ǥ �������� ���� ����
#define SCP_RESP_CHAR_LIST                                0x9011      // ĳ���� ����Ʈ ����
#define SCP_RESP_CHAR_CREATE                              0x9012      // �ɸ��� ���� ���� �޽���
#define SCP_RESP_CHAR_REMOVE                              0x9013      // �ɸ��� ���� ���� �޼���
#define SCP_RESP_CHAR_SELECT	                          0x9014      // �ɸ��� ������ ������ ���� ���� �޽���
#define SCP_RESP_EXIT_ZONE_SERVER                         0x9015      // ĳ���� ����â�� ����������, ���弭�� ����â���� �̵� ���� �޼���
#define SCP_RESP_CHAR_LOGOUT                              0x9021      // ĳ������ �α� �ƿ� ���� �޽���
#define SCP_RESP_REMOVE_MOB                               0x9022      // ĳ���� �α׾ƿ�, ����, �����̵��� �ֺ����� ���� �޼���
#define SCP_OTHER_CHAR_LOGOUT_NOTIFY                      0x9023      // ĳ������ �α׾ƿ�, ����, �����̵��� ��Ƽ, ���, �ּҷ� ���� �ɸ��Ϳ��� ���� ���� �޼���
#define SCP_RESP_CHAR_INIT                                0x9101      // ĳ������ �����ʱ����� ���� �޼���

#define SCP_INIT_SKILL                                    0x9104      // �ɸ����� ��ų���� ���� ���� �޼���
#define SCP_INIT_GUILD                                    0x9105      // ����� �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_ADDRESS_BOOK                             0x9106      // �ּҷ� ���� ���� ���� �޼���
#define SCP_RESP_CHAR_HISTORY                             0x9108      // �ɸ��� �����丮���� ���� �޼���
#define SCP_INIT_EQUIPMENT                                0x9109      // �ɸ��� ������� ��û�� ���� ���� �޼���
//#define SCP_INIT_MONSTER_NPC                              0x9111      // �ֺ� Monster/NPC ���� ���� ���� �޼���
#define SCP_INIT_OTHER_MOB                                0x9112      // �ֺ� �ٸ� �ɸ��� ���� ���� �޼���
#define SCP_INIT_REAL_ADDRESS_BOOK                        0x9113      // �ּҷ� ���� ���� ���� �޼���
#define SCP_INIT_REAL_GUILD                               0x9114      // ����� �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_REAL_GUILD_MEMBER                        0x9115      // ������ �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_ITEM                                     0x9121      // �ֺ� ������ ������ ó�� ���� �޼���
#define SCP_INIT_WORLD_USER_COUNT                         0x9161      // ���庰 �����ڼ��� ó����.
#define SCP_INIT_GUILD_MEMBER                             0x9171      // �ڽ��� ���������� ������.
#define SCP_RESP_CHAR_MOVE                                0x9201      // ĳ���� �̵��� ���� ��� �޽���
#define SCP_OTHER_CHAR_MOVE                               0x9202      // �̵������� �ٸ� ĳ���Ϳ��� �˷���
#define SCP_MONSTER_MOVE_STEP                             0x9206      // �Ѽ� �̵��� �ֺ��� ����
#define SCP_MONSTER_MOVE_NSTEP                            0x9207      // ������ �̵��� �ֺ��� ����
#define SCP_MONSTER_MOVE_END                              0x9208      // ������ �̵��� ��� ��ǥ�� ����
#define SCP_RESP_ITEM_USE                                 0x9223      // ������ ��� ���� �޼���
#define SCP_ITEM_USE_BROADCAST                            0x9224      // ������ ����� �ֺ� �ٸ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_ITEM_REMOVE                                   0x9225      // �κ��丮���� ������ ������� �˷���
#define SCP_RESP_CHAR_MOVE_BROADCAST                      0x9227      // �ɸ����� �̵��� ��û�� ���� ����޼���
#define SCP_RESP_ATK_CHAR                                 0x9301      // ĳ������ ���� ���� �޼���
#define SCP_ATK_CHAR_BROADCAST                            0x9302      // ĳ������ ������ �ֺ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_RESP_ITEM_EQUIPMENT                           0x9401      // ������ ���� ��û�� ���� ���
#define SCP_ITEM_EQUIPMENT_BROADCAST                      0x9402      // ������ ������ �ֺ� ĳ���Ϳ��� ����
#define SCP_ITEM_ABRASION                                 0x9411      // ������ ������� �˸� ���� �޼���
#define SCP_ITEM_ABRASION_BROADCAST                       0x9412      // ������ ������� �ֺ� �ٸ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_RESP_QUEST_HISTORY                            0x9701      // ����Ʈ �����丮 ���� ����
#define SCP_QUEST_DIALOG                                  0x9702      // ��ȭ�� ���
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // ����Ʈ �ܰ� �˸�
#define SCP_QUEST_DIALOG                                  0x9702      // ��ȭ�� ���
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // ����Ʈ �ܰ� �˸�
#define SCP_RESP_SKILL_REGIST                             0xA001      // ��ų ��� ��� ���� �޼���
#define SCP_SKILL_REGIST                                  0xA002      // ī��Ʈ ��¿� ���� ��ų �ڵ� ��� ��� ���� �޼���
#define SCP_RESP_SKILL_SELECT                             0xA003      // ��ϵ� ��ų�� ����/���� ��� ���� �޼���
#define SCP_RESP_SKILL_SELECT_BROADCAST                   0xA004      // ��ϵ� ��ų�� ����/���� ��� ���� �޼���
#define SCP_RESP_SKILL_USE2_CHAR                          0xA011      // ĳ������ ��ų ���� �غ��� ��û ��� �޼���
#define SCP_SKILL_READY_CHAR_BROADCAST                    0xA012      // ĳ������ ��ų ���� �غ����� �ֺ��� ���۰�� �޼���
#define SCP_RESP_SKILL_ATK_CHAR                           0xA013      // ĳ������ ��ų ���� ���� �޼���
#define SCP_SKILL_ATK_CHAR_BROADCAST                      0xA014      // ĳ������ ��ų ������ �ֺ� ĳ���͵鿡�� ���� ��� �޼���
#define SCP_RESP_SKILL_LEVEL_UP                           0xA021      // ĳ������ ��ų Level-Up ��û ��� �޼���
#define SCP_RESP_SHOP_SKILL_LIST                          0xA022      // ���� ������ ��ų List ��û�� ���� ����޼���
#define SCP_RESP_TROUBLE_REPORT                           0xA541      // ������ �Ű����� �����Ѵ�.
#define SCP_RESP_TROUBLE_REPORT_LIST                      0xA542      // ������ �Ű����� ����Ʈ�� ��û�Ѵ�.
#define SCP_RESP_TROUBLE_REPORT_SET                       0xA543      // �Ű����� ó����Ȳ�� �޴´�.
#define GSCP_RESP_TROUBLE_REPORT_LIST                     0xA544      // �α��� ���� �޽���
#define GSCP_RESP_TROUBLE_REPORT_SET                      0xA545      // �α��� ���� �޽���
#define GSCP_RESP_TROUBLE_REPORT                          0xA546      // �α��� ���� �޽���
#define GSCP_INIT_ITEM                                    0xA548      // ĳ���� ������ ����
#define GSCP_INIT_SKILL                                   0xA549      // ĳ���� ��ų ����
#define GSCP_RESP_PARAMETER_CHANGE                        0xA550      // ĳ������ �⺻ �������� ���� ��û�� ���� ���
#define GSCP_RESP_ITEM_INSERT                             0xA551      // ������ ���� ���
#define GSCP_RESP_ITEM_DELETE                             0xA552      // ������ ���� ���
#define GSCP_RESP_SKILL_INSERT                            0xA553      // ��ų ���� ���
#define GSCP_RESP_SKILL_DELETE                            0xA554      // ��ų ���� ���
#define SCP_RESP_CHAR_INFO                                0xA561      // �ɸ��� ���� ���� �޽���
#define SCP_RESP_CHAR_EQUIPMENT                           0xA562      // �ɸ����� �������� ���� �޽���
#define SCP_RESP_CHAR_SKILL                               0xA563      // �ɸ����� ��ų���� ���� �޽���
#define SCP_RESP_CLOSE_CHAR                               0xA571      // �ɸ����� �������� ���� �޽���
#define SCP_RESP_JOIN_ADDRESS_BOOK                        0xA603      // �ּҷϿ� ĳ�����߰� ��û�� ���� ����޼���
#define SCP_JOIN_ADDRESS_BOOK_NOTIFY                      0xA604      // �ּҷ� �߰� ��û�� ĳ���Ϳ��� ���۸޼���
#define SCP_RESP_JOIN_ADDRESS_BOOK_RESULT                 0xA605      // �ּҷ� �߰� ��û ����� ��� �޼���
#define SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0xA606      // �ּҷ� �߰� ��û�� ���� ���� ����� ĳ���Ϳ��� ����
#define SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE               0xA607      // �ּҷϿ� �ִ� ĳ���� ������ ������û�� ���� ����޼���
#define SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0xA608      // �ּҷϿ��� ������ �˸���
#define SCP_RESP_ADDRESS_BOOK_GROUP_ADD                   0xA611      // �ּҷϿ� �׷��� �߰� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_DELETE                0xA612      // �ּҷϿ� �׷��� ���� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_MOVE                  0xA613      // �ּҷϿ� �ɸ����� �׷��̵� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_RENAME                0xA614      // �ּҷϿ� �׷��� �̸������� ��û���
#define SCP_RESP_ADDRESS_BOOK_STATUS                      0xA621      // �ּҷ� ��Ͽ�û�� �źθ� ���ÿ�û
#define MSG_ITEM_ID                                       0xB100      // item ����
#define SCP_RESP_LEARN_SKILL                              0xB210      // Learn a skill
#define SCP_RESP_CAST_SKILL                               0xB220      // cast a skill
#define SCP_CAST_SKILL_BROADCAST                          0xB230      // cast a skill
#define SCP_RESP_CHAR_ACT                                 0xB300      // Action
#define SCP_CHAR_ACT_BROADCAST                            0xB310      // Action�� broadcast
#define SCP_RESP_UPDATE_UI                                0xB500      // Update UI
#define SCP_RESP_UPDATE_STATUS                            0xB501      // Update Status
#define SCP_LEVEL_UP_BROADCAST                            0xB510      // level up
#define SCP_RESP_INCREASE_CHAKRA                          0xB520      // Increase a chakra point
#define REGISTER_KALA_CORE								  0xB530      // register a kala-core on the kala-altar.
#define CONTACT_NPC                                       0xB540      // NPC�� ������ �Ҷ�
#define SKILL_UP_EFFECT                                   0xB550      // skill up effect �ߵ� ��
#define SCP_FIRE_FX_BROADCAST		                      0xB560      // Fire a Effect
#define MSG_SET_ZONE_SETTINGS_ID                          0xB570		// zone�� ���� ������ client�� �����Ѵ�.
#define MSG_CHANGE_TRIMURITI_ID                           0xB580		// clan�� ������ client�� �˸���.
#define MSG_APPLY_SIEGE_ID                                0xB590		// ���� ��û�� �Ѵ�.
#define MSG_TRIGGER_EVENT_ID                              0xB600		// Ư�� event�� �����Ų��.
#define	MSG_STATE_OF_THE_SIEGE_ID						  0xB610		// ���� ��¡�� ���� ����
#define	MSG_PET_COMMAND_ID                                0xB620		// �ֿ��� ����� ����
#define MSG_SIEGE_ENTRY_ID                                0xB630
#define MSG_CHECK_SIEGE_ENTRY_ID                          0xB640
#define CONFIRM_SIEGE_ENTRY_ID                            0xB650
#define MSG_FIX_DATE_OF_SIEGE_ID                          0Xb660

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
	short                                             snDur;        // Item ������
	BYTE                                              nPack;        // Item ��ø����
	BYTE											  byDummy;
	WORD                                              wrgMaterial[10];// �߰��Ǵ� �������

} S_TNITEM_DATA, * PS_TNITEM_DATA;


typedef struct _S_TNSKILL_DATA
{
	short               								snID;          // Skill ID
	BYTE                								byLevel;      // Skill Level
	BYTE												byDummy;

} S_TNSKILL_DATA, * PS_TNSKILL_DATA;


typedef struct _S_TNCHAKRA
{
	short                                             snMuscle;     // ���� ��ũ��
	short                                             snNerves;     // �Ű� ��ũ��
	short                                             snHeart;      // ���� ��ũ��
	short                                             snMind;       // ���� ��ũ��

} S_TNCHAKRA, * PS_TNCHAKRA;


typedef struct _S_TNRESIST
{
	short                                             snFire;       // fire ����
	short                                             snCold;       // cold ����
	short                                             snLightning;  // lightning ����
	short                                             snPoison;     // poison ����

} S_TNRESIST, * PS_TNRESIST;


typedef struct _S_TNDAMAGE
{
	short                                             snMin;        // �ּ�
	short                                             snMax;        // �ִ�
	short											  snFire ;
	short											  snCold ;
	short											  snLightning ;
	short											  snPoison ;

} S_TNDAMAGE, * PS_TNDAMAGE;


typedef struct _S_TNTARGET_DATA
{
	byte                                            byRes ; // result; 0,1: ����, 2:����
	byte                                            byDummy1 ;
	short                                           snDummy2 ;
	short											snKeyID ;
	short											snDamage ;
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
	DWORD		dwIndex;      // ��ų�ε���
	BYTE		byLevel;      // ���� ��ų����
	BYTE		byDummy;
	short		snDummy;

} S_GUILD_SKILL, * PS_GUILD_SKILL;


typedef struct _S_GUILD_MEMBER_INFO
{
	char		 szName[SZNAME_LENGTH];   // ���� ĳ������ �̸�
	BYTE         byTrimuritiClass;// ĳ������ �ֽŰ��                                     
	BYTE         bySpecialName;// ĳ������ Ư��Īȣ                                     
	BYTE         byGuildAuthority;// ��峻�� ����                                     
	BYTE         byTribe;      // ĳ������ ����                                     
				 
	BYTE         byCastClass;  // ĳ������ ī��Ʈ ���                                     
	BYTE         byCastGrade;  // ĳ������ ī��Ʈ ���                                     
	BYTE         byConnect;    // ĳ������ ���ӿ���                                     
	BYTE		 byDummy;
	int          nContribution;// ĳ������ ��峻 ���嵵                                     

} S_GUILD_MEMBER_INFO, * PS_GUILD_MEMBER_INFO;

typedef struct _S_QUEST_HISTORY_INFO
{
	BYTE        byIndex;      // �÷��� �ε���                                      
	BYTE        byValue;      // �÷��� ��                                      
	short		snDummy;
} S_QUEST_HISTORY_INFO, * PS_QUEST_HISTORY_INFO;


typedef struct _S_KEY_ID
{
	DWORD                                             dwKeyID;      

} S_KEY_ID, * PS_KEY_ID;

typedef struct _S_USER_REPORT_LIST
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // ó����Ȳ
	char                                              szReport[512];

} S_USER_REPORT_LIST, * PS_USER_REPORT_LIST;


typedef struct _S_REPORT_LIST
{
	DWORD                                           	dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	char                                            	szCharName[SZNAME_LENGTH];
	BYTE                                            	byWorld;   
	BYTE                                            	byProceed;    // ó����Ȳ
	short												snDummy;
	DWORD                                           	dwTime;       

	char                                            	szReport[512];
	char                                            	szNote[256];  // ���

} S_REPORT_LIST, * PS_REPORT_LIST;


typedef struct _S_SKILLINFO
{
	BYTE                                            	byType;       // Skill�� ����
	BYTE                                            	byLevel;      // Skill Level
	short												snDummy;
	DWORD                                           	dwIndex;      // Skill Index

} S_SKILLINFO, * PS_SKILLINFO;

//
//typedef struct _S_ADDRESS_MEMBER_INFO
//{
//	char                                              szName[SZNAME_LENGTH];   // �ּҷ� ĳ������ �̸�
//	BYTE                                              byTrimuriti;  // ĳ������ �ֽ�
//	BYTE                                              byTribe;      // ĳ������ ����
//	BYTE                                              byCastClass;  // ĳ������ ī��Ʈ ���
//	BYTE                                              byCastGrade;  // ĳ������ ī��Ʈ ���
//	WORD                                              wServerID;    // �ɸ��Ͱ� ��ġ�� ����ID
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
    char    AccountName[ACCOUNTNAME_LENGTH];	//	���� ID
	char    AccountPass[ACCOUNTPASS_LENGTH];	//	���� ���
	char    szCharName[SZNAME_LENGTH];						// Character Name
	short	snVersion[4];
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
	BYTE												byConnType;   // ������ġ
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
	BYTE		byWhat ; // 0: �������� ���� ��¥�� ��û�Ҷ�, 1:������ ���� ��¥�� ������ �˷��ٶ�
	BYTE		byDate  ; //���� ��¥(0, 1~n), 0:�����ȳ�¥�� �������, 0 �ʰ�:������ ��¥ ������ȣ
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
	BYTE		byDate  ; //���� ��¥
	BYTE		byClanSlot ; // 0:����, 1:����1, 2:����2, 3:����3
	BYTE		byPage ; // 0~4
	BYTE		byDummy ;
	int			irgGuildID[8] ; // 0 �̸� ��� �ִ� ���̴�.
	DWORD		dwrgGuildMark[8] ; // 0 �̸� ��� �ִ� ���̴�.
	char		szrgGuildName[8][SZGUILD_LENGTH] ; 
} MSG_SIEGE_ENTRY ;


typedef struct _MSG_STATE_OF_THE_SIEGE
{
	_MSG ;
	int			irgClan[11] ; // symbol�� ���� �� clan�� ���� ����
} MSG_STATE_OF_THE_SIEGE ;


typedef struct _MSG_SET_ZONE_SETTINGS // �������� �Ϲ������� ������ �޽��� Ÿ��
{
	_MSG ;
	short		snSiege ; // 0�� ������ �ƴ�, 1�� ������ ��
	short		snDummy ; // 
	int			iCastle ; // ������ ��� ID
} MSG_SET_ZONE_SETTINGS ;


typedef struct _MSG_CHANGE_TRIMURITI // �������� �Ϲ������� ������ �޽��� Ÿ��
{
	_MSG ;
	short		snKeyID ; // ĳ���� ID
	BYTE		byTrimuriti ; // ����� �ֽ�
	BYTE		byDummy ;
} MSG_CHANGE_TRIMURITI ;


// client�� server�� ��û, server�� trial���Ŀ� ����� reply���ش�.
typedef struct _MSG_APPLY_SIEGE
{
	_MSG ;
	BYTE		byClanSlot ; // leader(clan) slot 
	BYTE		byExpandSlot ; // ���� slot
	short		snResult ; // ��û ��� ��
	//int			nGuildID ; // ��û�� guild ID
} MSG_APPLY_SIEGE ;


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
	short                                           	snWarpID ;		//	����� �̵��� Ǫ��Ƽī ���� �̵����ID
	BYTE												byType ;		// use/info
	BYTE												byPlace ;		// equipment, bag1~~ , ...
	BYTE												byIndex ;
	BYTE												byResult ;
	STRUCT_ITEM											kItem ;			// ��ø������ 0�̸� �������ش�.
} MSG_ITEM ;


typedef struct _MSG_SKILL_UP_EFFECT
{
	_MSG ;
	short                                              snID ;
	byte                                               byLevel ; // ������ level
	byte                                               byLevelPlus ; // ����� ��ġ, �� ��ġ�� 0���� ũ��, level ���ڸ� �Ķ������� ǥ��
	// ���� byLevel + byLevelPlus ���� ���� ��ų level
} MSG_SKILL_UP_EFFECT ;


typedef struct _MSG_REGISTER_KALA_CORE
{
	_MSG ;
	short												snID ; // Į������ ID
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
	S_TNSKILL_DATA										kSkill;       // level up�� skill ����

} S_SCP_RESP_LEARN_SKILL, * PS_SCP_RESP_LEARN_SKILL;




// SCP_CAST_SKILL_BROADCAST : 0x3240
typedef struct _S_CSP_CAST_UNIT_SKILL
{
	_MSG ;	
	short											  snSkillID ;       // cast�� skill ID
	short                                             snCasterKeyID;// Caster handle
	int                                               iSkillIcon ; // bit vector, ���õ� ��ų ICON   <===
	DWORD                                             dwFireHitGapTime ; // �߻��ϰ� ������ ������ �ɸ� �ð�  <===
	DWORD                                             dwEndTime ;  // ��ų ������ ����Ǵ� �ð�
	DWORD                                             dwDurationTime ; // ���� �ð����� �� �ð��� ������ ������.
	DWORD                                             dwCoolDownTime ; // �� �ð��� cool-down�� �Ϸ�ȴ�.
	short                                             snCasterX;    // Caster�� ���� x ��ǥ
	short                                             snCasterZ;    // Caster�� ���� y ��ǥ
	int                                               iCasterHP;    // Caster�� �� HP
	int                                               iCasterTP;    // Caster�� �� TP
	__int64                                           iCasterAffections ; // Caster���� ���� �ɷ��ִ� affection
	short                                             snMapX;       // Target map x ��ǥ(ground), �ʼ� ����
	short                                             snMapZ;       // Target map y ��ǥ(ground), �ʼ� ����
	short                                             snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:��ֹ��浹 ...)
	short                                             snPackCount ;  // �Ҹ�� item�� ���� ���� ����(ȭ���� ����)]
	byte                                              bySkillLevel ;
	byte                                              byDummy ;
	short                                             sDummy2 ;
	S_TNTARGET_DATA                                   kTarget ;

} S_CSP_CAST_UNIT_SKILL, * PS_CSP_CAST_UNIT_SKILL;



// CSP_REQ_CAST_SKILL : 0x3250
typedef struct _S_CSP_CAST_AREA_SKILL
{
	_MSG;
	short											  snSkillID ;       // cast�� skill ID	
	short                                             snCasterKeyID;// Caster handle
	int                                               iSkillIcon ; // bit vector, ���õ� ��ų ICON   <===
	DWORD                                             dwFireHitGapTime ; // �߻��ϰ� ������ ������ �ɸ� �ð�   <===
	DWORD                                             dwEndTime ;  // ��ų ������ ����Ǵ� �ð�
	DWORD                                             dwDurationTime ; // ���� �ð����� �� �ð��� ������ ������.
	DWORD                                             dwCoolDownTime ; // �� �ð��� cool-down�� �Ϸ�ȴ�.	
	short                                             snCasterX;    // Caster�� ���� x ��ǥ
	short                                             snCasterZ;    // Caster�� ���� y ��ǥ
	int                                               iCasterHP;    // Caster�� �� HP
	int                                               iCasterTP;    // Caster�� �� TP
	__int64                                           iCasterAffections ; // Caster���� ���� �ɷ��ִ� affection
	short                                             snMapX;       // Target map x ��ǥ(ground), �ʼ� ����
	short                                             snMapZ;       // Target map y ��ǥ(ground), �ʼ� ����
	short                                             snRes ;       // Result(-1:echo, 0:Normal, 1:CriticalHit, 2:Dodge, 3:��ֹ��浹 ...)
	short                                             snPackCount ;  // �Ҹ�� item�� ���� ���� ����(ȭ���� ����)
	byte                                              bySkillLevel ;
	byte                                              byDummy ;
	short                                             sDummy2 ;
	S_TNTARGET_DATA                                   krgTarget[TN_MAX_TARGET_COUNT] ;

} S_CSP_CAST_AREA_SKILL, *PS_CSP_CAST_AREA_SKILL ;



//CSP_DEBUFFER_SKILL // �ܼ��� client�� ǥ�õ� skill icon�� ���ֱ� ���� �뵵�̴�. ���� ������ ���� ���� �̹� ����ǰ� �ִ�.
typedef struct _S_CSP_DEBUFFER_SKILL
{
	_MSG ;
	short                                             snSkillID ;
	short                                             snDummy ;
	__int64                                           iCasterAffections ; // Caster���� ���� �ɷ��ִ� affection, // �̰��� ���� �ʿ��Ѱ�?
} S_CSP_DEBUFFER_SKILL, *PS_CSP_DEBUFFER_SKILL ;



struct MSG_TOGGLE_BUTTON
{
	_MSG;
	BYTE											byButton ; // ���� ��ư, 1:PK_btn, 2:assist btn
	BYTE											byValue ; // ���� ���°� 0(off)/1(on)
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
	BYTE                                              byAct;        // ���Ϸ��� �ൿ

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
	BYTE                                              byAct;        // ���Ϸ��� �ൿ

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
	short								snX;          // ���� x ��ǥ
	short                              	snZ;          // ���� y ��ǥ   
	char								byteSpeed1;											
	BYTE                               	byLevel ;      // �� Level
	BYTE                                byCaste ;      // Caste ���
	BYTE                                byRangePlus ; // ���Ÿ� ���� ��Ÿ� ���� ��ġ, ������ 0, ��Ÿ� ���� ��ų�� �ɷ��� ��쿡�� 0 �ʰ� <===
	char								byteSpeed2;	
	BYTE                                bySaveTPCost ; // TP cost ���� ��ġ <===
	BYTE                                byClass1 ;     // ���� �ܰ�
	BYTE								byClass2 ;     // ���� ����
	BYTE                                byDummy1 ;     //
	BYTE                                byDummy2 ;     //
	char								byteAS1;	
	char								byteSpeed3;	
	//int                               iMoveSpeed ;   // �� MoveSpeed 
	//int                               iAttackSpeed ; // �� �Ϲ� ���� ��� ���� �ӵ�, skill���� ������ �ȵȴ�. <===
	short                               snAttackSpeedCorrect ; // ���� ��� �ӵ� ���� ��ġ( �� ��ġ��ŭ�� �� ������) <===
	short                               snCastSpeedCorrect ; // ���� ����� �ƴ� skill �ӵ� ���� ��ġ <===
	short                               snDDup ;		// DD type skill�� ���ݷ� up�� ǥ���Ѵ�. <===
	short								snKarma ;     //<===
	int                                 iBramanPoint ; // �� Braman point	
	int                                 iPietyPoint ; // �� �žӽ� point <===
	int                                 iTitle ;       // Title
	int                                 iMaxPrana ;    // �ִ� Prana
	int                                 iPrana ;       // �� Prana
	S_TNCHAKRA                          krgChakra[2] ; // 0:base chakra, 1:changed chakra
	short                               snCPRemaining ;// ���� Chakra Point
	short                               snSPRemaining ;// ���� Skill Point
	int                                 iHP ;          // �� HP
	int                                 iMaxHP ;       // �ִ� HP
	int                                 iHPRecovery ;  // HPȸ����/��
	int                                 iTP ;          // �� TP
	int                                 iMaxTP ;       // �ִ� TP
	int                                 iTPRecovery ;  // TPȸ����/��
	short                               snAC ;         // AC
	short                               snAttackRate ; // Attack Rate
	short                               snDodgeRate ;  // Dodge Rate
	short                               snCasteSPRemaining ;	// <===
	char								byteSpeedCorrection;	
	char								byteAS2;	
	char								byteSpeedParity;	
	char								byteAS3;	
	S_TNRESIST                          kResist ;      // ����
	S_TNDAMAGE                          kDamage ;		// damage
	int									iGold ;       // ��
	int                                 iSkillIcon ; // bit vector, ���õ� ��ų ICON  <===
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
	int                                               iHP;          // �� HP
	int                                               iTP;          // �� TP
	int                                               iPrana;       // �� Prana
	__int64                                           iAffections ; // ���� �ɷ��ִ� affection
	int                                               iSkillIcon ; // bit vector, ���õ� ��ų ICON <===
	int                                               iPietyPoint ; // �� �žӽ� point <===
	int                                               iMoveSpeed ;   // �� MoveSpeed <===
	int                                               iAttackSpeed ; // �� �Ϲ� ���� ��� ���� �ӵ�, skill���� ������ �ȵȴ�. <===
	short                                             snAttackSpeedCorrect ; // ���� ��� �ӵ� ���� ��ġ( �� ��ġ��ŭ�� �� ������) <===
	short                                             snCastSpeedCorrect ; // ���� ����� �ƴ� skill �ӵ� ���� ��ġ <===

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
	BYTE                                              byLevel;      // �� Level

} S_SCP_LEVEL_UP_BROADCAST, * PS_SCP_LEVEL_UP_BROADCAST;


// SCP_FIRE_EFFECT_BROADCAST : 0xB560
typedef struct _S_SCP_FIRE_FX_BROADCAST
{
	_MSG;
	DWORD                                             dwKeyID ;      // PC handle
	int                                               iFX ;      // �Ѿߵ� FX ID
} S_SCP_FIRE_FX_BROADCAST, * PS_SCP_FIRE_FX_BROADCAST ;



// CSP_REQ_INCREASE_CHAKRA : 0x3520
typedef struct _S_CSP_REQ_INCREASE_CHAKRA
{
	_MSG;
	BYTE                                              byChakra;     // �ø����� chakra(0:muscle, 1:nerves, 2:heart, 3:mind)

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
	BYTE                                            byResult ;     // client���� �������� ���� - 1:killed, 2:logout, 3:sucide, 5:teleport(out)
	BYTE											byRemoveType ; // ������� �����ȣ; 0:�Ϲ� �״� �ִ�(or �׳� �����), 1:���ϰ� �����
	short                                           snTribe ; // ���� ����, 2000~3000�̸� �����̴�. 100�����̸� PC�̴�.
	DWORD                                           dwKillerID ;
	char											szName[SZNAME_LENGTH] ; // ĳ���͸� ����
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
//	S_REQUEST �� �̿��Ѵ�.
#define		SCP_RESP_SAVE_POSITION	0x9016
//	S_RESULT �� �̿��Ѵ�.


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
	BYTE                                              	byResult;     // �������� ��Ÿ��
	BYTE                                              	byRegion;     
	BYTE                                              	byZone;  
	BYTE												byDummy;

} S_SCP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_SCP_OTHER_CHAR_LOGOUT_NOTIFY;


// CSP_INIT_CHAR : 0x1101
typedef struct _S_CSP_REQ_CHAR_INIT
{
	_MSG;
	BYTE        byConnType;   // ��������                                      
	BYTE        byConnPos;    // ������ġ                                      
	WORD        wPortalID;    // ������ŻID                                      
	char        szCharName[SZNAME_LENGTH];
	char		szTargetName[SZNAME_LENGTH];

} S_CSP_REQ_CHAR_INIT, * PS_CSP_REQ_CHAR_INIT;


// SCP_INIT_CHAR : 0x9101
typedef struct _S_SCP_RESP_CHAR_INIT
{
	_MSG;
	BYTE					byResult;		// �ʱ�ȭ ���
	BYTE					byDummy;;		//	0:�������, 1:�׾�����
	short					snBagIndex;

    DWORD                   dwGameTime ;
	DWORD					dwKeyID;
	short					snX;
	short					snZ;

	BYTE					bySkill[MAX_SKILL];
	BYTE					byQuest[MAX_EVENT_FLAG];
	STRUCT_ITEM				Inven[MAX_INVEN];
	STRUCT_ITEM				Equip[MAX_EQUIP];
	//STRUCT_MOB			Mob;
	STRUCT_ITEM				Cargo[MAX_CARGO];
	int						nCargoMoney;
	int						nGuildID;
	DWORD					dwTimeStamp[10];
	//#ifdef __TN_LOCAL_SERVER_SWITCH__
	BYTE					byClan ;
	BYTE					byDummy2 ;
	short					snDummy ;
	//#endif
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
	DWORD												dwStartTime;  // �����丮 �߻� �ð�
	WORD												wType;        // �����丮 ����
	short												snDummy;
	char												szContent[SZNAME_LENGTH];// �����丮 ����

} S_SCP_RESP_CHAR_HISTORY, * PS_SCP_RESP_CHAR_HISTORY;


// CSP_INIT_EQUIPMENT : 0x1109
typedef struct _S_CSP_INIT_EQUIPMENT
{

} S_CSP_INIT_EQUIPMENT, * PS_CSP_INIT_EQUIPMENT;


// SCP_INIT_EQUIPMENT : 0x9109
typedef struct _S_SCP_INIT_EQUIPMENT
{
	BYTE                                              byPlace;      // �������� ���� ��ġ
	DWORD                                             dwKeyID;      // �������� KeyID
	DWORD                                             dwIndex;      // �������� Index
	short                                             snCurDurability;
	short                                             snCount;      // �������� ����(��ø����)
	BYTE                                              byX;          // ������ ���� X ��ǥ(0���� ����)
	BYTE                                              byZ;          // ������ ���� Z ��ǥ(0���� ����)
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�
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
//	BYTE                                              bySize;       // ������ ũ��
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
	BYTE			byGMStatus;		//	bit flag(0x01:�ɸ��ͺ�, 0x02:������, 0x04:ä�ú�, ...)	
          
	BYTE       		byActiveLevel; 
	BYTE       		byActionLevel; 
	BYTE       		byType;                                              
	BYTE       		byDir;			// ���� ����(0:random, 1~4:��������)

	short			snKarma;
	BYTE			byClass1;			//	bit flag �߸��ߺ��� | ������.
	BYTE			byClass2;

	BYTE			byLevel;
	BYTE			byTradeMode;
	BYTE			byPopType ; // pop�� ���� ���� ���, 0 �� ������ ��, 1�� �ٴڿ��� ������ �ö���� ���
	BYTE			byCollision ; // �浹 ����, 1�̸� �浹�� �Ǿ� ������� ���ϴ� ���̴�. 0�̸� ��� �����ϴ�.
	
	short      		snHeight ;
	short      		snTargetX ;		// �ɸ����� �̵����� X��ǥ                                       
	short      		snTargetZ ;		// �ɸ����� �̵����� Z��ǥ  
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
	//#ifdef __TN_LOCAL_SERVER_SWITCH__
	byte			byClan ; // clan ������, �������� ��쿡 ����
	//#endif
	//#ifndef __TN_LOCAL_SERVER_SWITCH__
	byte			byDummy ;
	//#endif
	short			snDummy;
	
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

#define CSP_REQ_INIT_REGEN_CHAR                           0x1131      // ĳ���� ���� �ʱ�ȭ ��û
#define SCP_RESP_INIT_REGEN_CHAR                          0x9131      // �κ��丮�� ������ ��ġ ���� ���� �޼���
// CSP_REQ_INIT_REGEN_CHAR : 0x1131
typedef struct _S_CSP_REQ_INIT_REGEN_CHAR
{	_MSG
	BYTE                                              byConnType;		//	REGEN_TYPE_CENTER(1), REGEN_TYPE_SAVE(2)
} S_CSP_REQ_INIT_REGEN_CHAR, * PS_CSP_REQ_INIT_REGEN_CHAR;
// SCP_RESP_INIT_REGEN_CHAR : 0x9131
typedef struct _S_SCP_RESP_INIT_REGEN_CHAR
{	_MSG

	BYTE       	byZone;			// �ɸ����� Zone ��ġ                   //	REGEN_TYPE_SAVE�� �¾ ������ ZoneID	                    
	BYTE       	byWhether;
	short      	snX;                                                 
	short      	snZ;                                                 
 	short      	snDegree;    

	DWORD      	dwGameTime;                                             
	int        	nCurHP;			// �ɸ��� HP�� ���簪                                       
} S_SCP_RESP_INIT_REGEN_CHAR, * PS_SCP_RESP_INIT_REGEN_CHAR;

#define _MSG_TrimuritySelect							0x1141			// �ɸ��� �ֽż���
struct MSG_TrimuritySelect
{	_MSG
	char		CharName[SZNAME_LENGTH];
	DWORD		dwMoney;
	BYTE		byTrimuriti;	//	�ɸ����� �ֽż���
	BYTE		byType;			//	0:��ȸ, 1:����
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
	BYTE                                              byDir;        // �̵����� �� �̵����� ����
	short                                             snDegree;     
	DWORD                                             dwTickCount;  
	WORD                                              wSeqNum;      // �̵���Ŷ Sequence Number

} S_CSP_REQ_CHAR_MOVE, * PS_CSP_REQ_CHAR_MOVE;


// SCP_RESP_CHAR_MOVE : 0x9201
typedef struct _S_SCP_RESP_CHAR_MOVE
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // �ɸ����� X��ǥ
	short                                             snZ;          // �ɸ����� Z��ǥ
	BYTE                                              byY;          // �ɸ����� �� ����
	short                                             snHeight;     // �ɸ����� �� ����

} S_SCP_RESP_CHAR_MOVE, * PS_SCP_RESP_CHAR_MOVE;


// CSP_OTHER_CHAR_MOVE : 0x1202
typedef struct _S_CSP_OTHER_CHAR_MOVE
{

} S_CSP_OTHER_CHAR_MOVE, * PS_CSP_OTHER_CHAR_MOVE;


// SCP_OTHER_CHAR_MOVE : 0x9202
typedef struct _S_SCP_OTHER_CHAR_MOVE
{
	DWORD                                             dwKeyID;      // character KeyID
	BYTE                                              byDir;        // ĳ���� �̵�����, ���� ����
	short                                             snDegree;     // �ɸ����� �̵� ���� ����
	short                                             snMovingSpeed;// 100�ʴ� �̵����� Cell ��
	short                                             snX;          // �ɸ����� X��ǥ
	short                                             snZ;          // �ɸ����� Z��ǥ
	BYTE                                              byY;          // �ɸ����� �� ����
	short                                             snHeight;     // �ɸ����� �� ����

} S_SCP_OTHER_CHAR_MOVE, * PS_SCP_OTHER_CHAR_MOVE;

#define CSP_REQ_ITEM_MOVE									0x1203      // ������ �̵� ���
#define SCP_RESP_ITEM_MOVE									0x9203      // ������ �̵� ���
// CSP_REQ_ITEM_MOVE : 0x1203
typedef struct _S_CSP_REQ_ITEM_MOVE
{	_MSG
	BYTE			byFromPlace;	// �������� ���� �ִ� ��ġ : 0 ��, 1 �κ�, 2 ����, 3 â��, 11 �ƽ���â��										
	BYTE			byToPlace;    // �������� �̵���ų ���										
	BYTE			byFromIndex;	// Index ��ȣ(�κ��丮���� Index)										
	BYTE			byToIndex;    // Index ��ȣ(�κ��丮���� Index)										
} S_CSP_REQ_ITEM_MOVE, * PS_CSP_REQ_ITEM_MOVE;
// SCP_RESP_ITEM_MOVE : 0x9203
typedef struct _S_SCP_RESP_ITEM_MOVE
{	_MSG
	int				nResult;		// ��� : 0-����, 1-����									
	BYTE			byFromPlace;	// �������� ���� �ִ� ��ġ : 1, �κ�, 2, ����, 3, â��									
	BYTE			byToPlace;		// �������� �̵���ų ���									
	BYTE			byFromIndex;	// Index ��ȣ(�κ��丮���� Index)									
	BYTE			byToIndex;		// Index ��ȣ(�κ��丮���� Index)									
} S_SCP_RESP_ITEM_MOVE, * PS_SCP_RESP_ITEM_MOVE;

#define SCP_MAP_ITEM_APPEAR									0x9204      // ���ο� �������� ������ ��ġ ������ �ֺ�ĳ���Ϳ��� ����
// SCP_MAP_ITEM_APPEAR : 0x9204
typedef struct _S_SCP_MAP_ITEM_APPEAR
{	_MSG
	int				nItemID;	// Item KeyID									
	DWORD			dwIndex;    // Item Index	
	int				nMobIndex;  // MOB Index
	short			snX;        // Item X��ǥ									
	short			snZ;        // Item Z��ǥ									
} S_SCP_MAP_ITEM_APPEAR, * PS_SCP_MAP_ITEM_APPEAR;

#define SCP_MAP_ITEM_DISAPPEAR								0x9205      // �������� ����� ��ġ�� �ֺ�ĳ���Ϳ��� ����
// SCP_MAP_ITEM_DISAPPEAR : 0x9205
typedef struct _S_SCP_MAP_ITEM_DISAPPEAR
{	_MSG
	int				nItemID;	// Item KeyID  
	char			szName[SZNAME_LENGTH];		// MOB of name
} S_SCP_MAP_ITEM_DISAPPEAR, * PS_SCP_MAP_ITEM_DISAPPEAR;

#define CSP_REQ_ITEM_DROP									0x1209	  // �������� ���� ����.
#define SCP_RESP_ITEM_DROP									0x9209	  // �������� ���� ����.
typedef struct _S_CSP_REQ_ITEM_DROP
{	_MSG
	DWORD			dwMoney;
	BYTE			byFromPlace;	// �������� ���� �ִ� ��ġ : 1, �κ�, 2, ����, 3, â��				
	BYTE			byIndex;		// Index ��ȣ(�κ��丮���� Index)				
	short			snDummy;				
	short			snX;			// �������� ���� X��ǥ				
	short			snZ;			// �������� ���� Z��ǥ				
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

#define CSP_REQ_ITEM_GET									0x120A	  // �������� ������ �ֽ�.
#define SCP_RESP_ITEM_GET									0x920A	  // �������� ������ �ֽ�.
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

#define SCP_RESP_ITEM_SET									0x920B	  // �ɸ��� ������ ������ �����.
typedef struct _S_SCP_RESP_ITEM_SET
{	_MSG
	BYTE			byType;	//	0:�����ۼҸ�, 1:�����ۻ���
	BYTE			byPlace;
	BYTE			byIndex;
	BYTE			byDummy;
	STRUCT_ITEM		sitem;
} S_SCP_RESP_ITEM_SET, *PS_SCP_RESP_ITEM_SET;

#define SCP_RESP_EQUIP_SET									0x920C	  // �ɸ��� ���� ������ �����.
typedef struct _S_SCP_RESP_EQUIP_SET
{	_MSG
	int				nID;
	STRUCT_ITEMVIEW	Equip[VISUAL_EQUIP];
} S_SCP_RESP_EQUIP_SET, *PS_SCP_RESP_EQUIP_SET;

#define _MSG_Money_Move										0x1226      // ���Ǿ��� �̵��� ��û
struct MSG_Money_Move
{	_MSG
	BYTE			byFromPlace;										
	BYTE			byToPlace;
	short			snDummy;
	DWORD			dwMoney;											
	DWORD			dwFromMoney;										// �ű������ ���Ǿ�(�̵������û��)
	DWORD			dwToMoney;											// �ű������ ���Ǿ�(�̵������û��)
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
	short                                             snX;          // ���� x��ǥ
	short                                             snZ;          // ���� z��ǥ

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
	BYTE	byResult;			//	����(0), ����(1)
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
//	DWORD                                             dwKeyID;      // ����� �������� KeyID
//
//} S_CSP_REQ_ITEM_USE, * PS_CSP_REQ_ITEM_USE;
//
//
//// SCP_RESP_ITEM_USE : 0x9223
//typedef struct _S_SCP_RESP_ITEM_USE
//{
//	BYTE                                              byResult;     // Result Field
//	DWORD                                             dwKeyID;      // ����� �������� KeyID
//	short                                             snCount;      // ������ ����
//	int                                               nCurHP;       // ĳ������ ���� HP
//	DWORD                                             dwCurStatus;  // ĳ������ ����
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
//	DWORD                                             dwKeyID;      // �������� ����ϴ� ĳ������ KeyID
//	DWORD                                             dwIndex;      // ����� �������� Index
//
//} S_SCP_ITEM_USE_BROADCAST, * PS_SCP_ITEM_USE_BROADCAST;


// CSP_ITEM_REMOVE : 0x1225
typedef struct _S_CSP_ITEM_REMOVE
{

} S_CSP_ITEM_REMOVE, * PS_CSP_ITEM_REMOVE;


// SCP_ITEM_REMOVE : 0x9225
typedef struct _S_SCP_ITEM_REMOVE
{
	DWORD                                             dwKeyID;      // ����� �������� KeyID
	BYTE                                              byPlace;      // ����� �������� ��ġ
	short                                             snX;          // ����� �������� X ��ǥ
	short                                             snZ;          // ����� �������� Z ��ǥ

} S_SCP_ITEM_REMOVE, * PS_SCP_ITEM_REMOVE;


// CSP_REQ_CHAR_MOVE_BROADCAST : 0x1227
typedef struct _S_CSP_REQ_CHAR_MOVE_BROADCAST
{
	BYTE                                              byDir;        // �̵�����
	short                                             snToX;        // �̵����� ������ X��ǥ
	short                                             snToZ;        // �̵����� ������ Z��ǥ

} S_CSP_REQ_CHAR_MOVE_BROADCAST, * PS_CSP_REQ_CHAR_MOVE_BROADCAST;


// SCP_RESP_CHAR_MOVE_BROADCAST : 0x9227
typedef struct _S_SCP_RESP_CHAR_MOVE_BROADCAST
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	BYTE                                              byDir;        // �̵�����
	short                                             snFromX;      // �̵����� ������ X��ǥ
	short                                             snFromZ;      // �̵����� ������ Z��ǥ
	short                                             snToX;        // �̵����� ������ X��ǥ
	short                                             snToZ;        // �̵����� ������ Z��ǥ

} S_SCP_RESP_CHAR_MOVE_BROADCAST, * PS_SCP_RESP_CHAR_MOVE_BROADCAST;

#define CSP_REQ_MOVE_PORTAL                               0x1231      // ��Ż�� ���� �̵���û�� �Ѵ�.
#define SCP_RESP_MOVE_PORTAL                              0x9231      // ��Ż�� ���� �̵���û ��� ���� ���� �޼���
// CSP_REQ_MOVE_PORTAL : 0x1231
typedef struct _S_CSP_REQ_MOVE_PORTAL
{	_MSG
	WORD											  wStartPortalID;	//	������ ��Ż
	WORD                                              wEndPortalID;     //  �̵��ϰ��� �ϴ� ��Ż�� ID
	
} S_CSP_REQ_MOVE_PORTAL, * PS_CSP_REQ_MOVE_PORTAL;
// SCP_RESP_MOVE_PORTAL : 0x9231
typedef struct _S_SCP_RESP_MOVE_PORTAL
{	_MSG
	BYTE        byResult;		// Result Field
	BYTE		byZone;			// Potal zone
	short		snDummy;
	int			nMoney;			// ��Ż �̿� �� ����� ��
} S_SCP_RESP_MOVE_PORTAL, * PS_SCP_RESP_MOVE_PORTAL;

#define _MSG_MoveOtherZone								0x1241		//	����Ǫ��Ƽī�� �̿��� �̵��� ���
struct MSG_MoveOtherZone
{	_MSG
	BYTE		byType;								//	const int   CONNECT_TYPE_PUSTICA	=	5;
	BYTE		byDummy;
	short		snPositionID;						//	�̵���� index(type5:��ġnpc index)
};

// CSP_REQ_ATK_CHAR : 0x1301
typedef struct _S_CSP_REQ_ATK_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ���� ��� ĳ������ KeyID
	DWORD                                             dwItemKeyID;  // ���ݿ� ����� ������ KeyID
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_ATK_CHAR, * PS_CSP_REQ_ATK_CHAR;


// SCP_RESP_ATK_CHAR : 0x9301
typedef struct _S_SCP_RESP_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCount;      // ��ô������ ���, �ܿ�����
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ����/Monster�� ���� HP

} S_SCP_RESP_ATK_CHAR, * PS_SCP_RESP_ATK_CHAR;


// CSP_ATK_CHAR_BROADCAST : 0x1302
typedef struct _S_CSP_ATK_CHAR_BROADCAST
{

} S_CSP_ATK_CHAR_BROADCAST, * PS_CSP_ATK_CHAR_BROADCAST;


// SCP_ATK_CHAR_BROADCAST : 0x9302
typedef struct _S_SCP_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwKeyID;      // ������ �ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;// ������ ���ϴ� ĳ������ KeyID
	BYTE                                              byEquipPart;  // ���ݽÿ� ����ϴ� �������� ������ ����
	BYTE                                              byResult;     // Result Field
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ������ ���� HP
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCurX;       // �������� ���� X��ǥ
	short                                             snCurz;       // �������� ���� z��ǥ

} S_SCP_ATK_CHAR_BROADCAST, * PS_SCP_ATK_CHAR_BROADCAST;


// CSP_REQ_ITEM_EQUIPMENT : 0x1401
typedef struct _S_CSP_REQ_ITEM_EQUIPMENT
{
	DWORD                                             dwKeyID;      // â���� ������ KeyID
	BYTE                                              byEquipPart;  // ������ ��������
	BYTE                                              byX;          // ���� X ��ǥ
	BYTE                                              byZ;          // ���� Z ��ǥ

} S_CSP_REQ_ITEM_EQUIPMENT, * PS_CSP_REQ_ITEM_EQUIPMENT;


// SCP_RESP_ITEM_EQUIPMENT : 0x9401
typedef struct _S_SCP_RESP_ITEM_EQUIPMENT
{
	BYTE                                              byResult;     // ������ ���� ��û�� ���� ��� ��
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�

} S_SCP_RESP_ITEM_EQUIPMENT, * PS_SCP_RESP_ITEM_EQUIPMENT;


// CSP_ITEM_EQUIPMENT_BROADCAST : 0x1402
typedef struct _S_CSP_ITEM_EQUIPMENT_BROADCAST
{

} S_CSP_ITEM_EQUIPMENT_BROADCAST, * PS_CSP_ITEM_EQUIPMENT_BROADCAST;


// SCP_ITEM_EQUIPMENT_BROADCAST : 0x9402
typedef struct _S_SCP_ITEM_EQUIPMENT_BROADCAST
{
	DWORD                                             dwKeyID;      // ���� ĳ���� KeyID
	DWORD                                             dwIndex;      // ���� ������ �ε���
	BYTE                                              byEquipPart;  // ������ ���� ����
	BYTE                                              bySubMaterialCount;

} S_SCP_ITEM_EQUIPMENT_BROADCAST, * PS_SCP_ITEM_EQUIPMENT_BROADCAST;


// CSP_ITEM_ABRASION : 0x1411
typedef struct _S_CSP_ITEM_ABRASION
{

} S_CSP_ITEM_ABRASION, * PS_CSP_ITEM_ABRASION;


// SCP_ITEM_ABRASION : 0x9411
typedef struct _S_SCP_ITEM_ABRASION
{
	DWORD                                             dwKeyIDWeapon;// ���� �������� KeyID
	DWORD                                             dwKeyIDBody;  // �Ǻ� �������� KeyID
	DWORD                                             dwKeyIDShield;// ���� �������� KeyID
	DWORD                                             dwKeyIDHead;  // ���� �������� KeyID
	DWORD                                             dwKeyIDFoot;  // �Ź� �������� KeyID
	DWORD                                             dwKeyIDBelt;  // �㸮�� �������� KeyID

} S_SCP_ITEM_ABRASION, * PS_SCP_ITEM_ABRASION;


// CSP_ITEM_ABRASION_BROADCAST : 0x1412
typedef struct _S_CSP_ITEM_ABRASION_BROADCAST
{

} S_CSP_ITEM_ABRASION_BROADCAST, * PS_CSP_ITEM_ABRASION_BROADCAST;


// SCP_ITEM_ABRASION_BROADCAST : 0x9412
typedef struct _S_SCP_ITEM_ABRASION_BROADCAST
{
	DWORD                                             dwKeyID;      // �������� ����� ĳ������ KeyID
	DWORD                                             dwIndexWeapon;// ���� �������� Index
	DWORD                                             dwIndexBody;  // �Ǻ� �������� Index
	DWORD                                             dwIndexShield;// ���� �������� Index
	DWORD                                             dwIndexHead;  // ���� �������� Index
	DWORD                                             dwIndexFoot;  // �Ź� �������� Index
	DWORD                                             dwIndexBelt;  // �㸮�� �������� Index

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
	BYTE				byMode;		//	0:��ŷ�����, 1:��ŷ���
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
//	�Ϲ�ä��
#define CSP_REQ_CHAT					0x1501
#define SCP_RESP_CHAT					0x9501
#define SCP_NOTIFY_CHAT					0x9502
typedef struct _S_CSP_REQ_CHAT
{	_MSG
	BYTE                            byBgColor;					// ä�� �޼��� ����
	BYTE                            byTextColor;				// ä�� �޼��� ���ڻ�
	BYTE							byTrimuriti;
	BYTE							byWhere;					// 0:ä��â, 1:�Ӹ�ǳ��, 2:ä��â�� �Ӹ�ǳ�� ���
	short							snDummy;
	char                            szMsg[MAX_CHAT_LENGTH];		// ä�� �޼���
} S_CSP_REQ_CHAT, * PS_CSP_REQ_CHAT;
typedef struct _S_SCP_NOTIFY_CHAT
{	_MSG
	int		nID;							// ä�� �޼����� ������ ĳ���� KeyID
	BYTE    byBgColor;						// ä�� �޼��� ����
	BYTE    byTextColor;					// ä�� �޼��� ���ڻ�
	BYTE	byTrimuriti;
	BYTE	byWhere;						// 0:ä��â, 1:�Ӹ�ǳ��, 2:ä��â�� �Ӹ�ǳ�� ���
	short	snDummy;
	char    szMsg[MAX_CHAT_LENGTH];		// ä�� �޼���
} S_SCP_NOTIFY_CHAT, * PS_SCP_NOTIFY_CHAT;

//	�ͼӸ�
#define CSP_REQ_WHISPER_CHAT			0x1503
#define SCP_RESP_WHISPER_CHAT			0x9503
#define SCP_NOTIFY_WHISPER_CHAT			0x9504
typedef struct _S_CSP_REQ_WHISPER_CHAT
{	_MSG	
	BYTE	byBgColor;    // ä�� �޼��� ����                                              
	BYTE	byTextColor;  // ä�� �޼��� ���ڻ�
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];   // ä�� �޼���                                              
	char    szName[SZNAME_LENGTH];   // ä�� �޼����� ������ ĳ���� �̸�                                           
} S_CSP_REQ_WHISPER_CHAT, * PS_CSP_REQ_WHISPER_CHAT;
typedef struct _S_SCP_RESP_WHISPER_CHAT
{	_MSG	
	BYTE	byResult;
	BYTE	byBgColor;				// ä�� �޼��� ����                                              
	BYTE	byTextColor;			// ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // ä�� �޼���                                              
	char    szName[SZNAME_LENGTH];				// ä�� �޼����� ������ ĳ���� �̸�                                       
} S_SCP_RESP_WHISPER_CHAT, * PS_SCP_RESP_WHISPER_CHAT;
typedef struct _S_SCP_NOTIFY_WHISPER_CHAT
{	_MSG   
	BYTE    byBgColor;    // ä�� �޼��� ����                                          
	BYTE    byTextColor;  // ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];   // ä�� �޼��� 
	char    szName[SZNAME_LENGTH];   // ä�� �޼����� ������ ĳ���� �̸�  
                                                                               
} S_SCP_NOTIFY_WHISPER_CHAT, * PS_SCP_NOTIFY_WHISPER_CHAT;

////	���� �޼���
//#define CSP_REQ_BROADCAST				0x1505
//#define SCP_NOTIFY_BROADCAST			0x9506
//typedef struct _S_CSP_REQ_BROADCAST
//{	_MSG
//	BYTE	byMsgType;		//	��Ƽ(0), ���(1), ��(2), ����(3), ����(4)		
//	BYTE	byBgColor;		//	ä�� �޼��� ����                                              
//	BYTE	byTextColor;	//	ä�� �޼��� ���ڻ�                                              
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH];   // ä�� �޼��� 
//} S_CSP_REQ_BROADCAST, * PS_CSP_REQ_BROADCAST;
//typedef struct _S_SCP_NOTIFY_BROADCAST
//{	_MSG
//	BYTE	byMsgType;		//	��Ƽ(0), ���(1), ��(2), ����(3), ����(4)	
//	BYTE	byBgColor;		// ä�� �޼��� ����                                              
//	BYTE	byTextColor;	// ä�� �޼��� ���ڻ�  
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH];   // ä�� �޼���   
//	char    szName[SZNAME_LENGTH];   // ä�� �޼����� ������ ĳ���� �̸�   
//} S_SCP_NOTIFY_BROADCAST, * PS_SCP_NOTIFY_BROADCAST;
#define _MSG_Chat						0x1507			//	��Ƽ, ���ä��
struct MSG_Chat
{
	_MSG
	BYTE	byMsgType;					//	��Ƽ(1), ���(2)	
	BYTE	byBgColor;					//	ä�� �޼��� ����                                              
	BYTE	byTextColor;				//	ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;				//	�ɸ����� �ֽ�
	int		nGuildID;					//	���ä���� ��� �ش����� ID
	int		nAlliedGuildID;				//	���ձ�� ä���� ��� ���ձ���� ID
	char	szMsg[MAX_GROUPCHAT_LENGTH];		//	ä�� �޼���
	char    szName[SZNAME_LENGTH];		//	ä�� �޼����� ������ ĳ���� �̸�   
};
#define _MSG_Broadcast					0x1508
struct MSG_Broadcast
{
	_MSG
	BYTE	byMsgType;					//	��(1), ����(2), ����(3), ������ɼ�(4), ȣ��(5), GM����(6)	
	BYTE	byBgColor;					//	ä�� �޼��� ����                                              
	BYTE	byTextColor;				//	ä�� �޼��� ���ڻ�(������ɼ��� ȣ���� ��� �κ��ε����� ����Ѵ�.)
	BYTE	byTrimuriti;				//	�ɸ����� �ֽ�
	char	szMsg[MAX_NOTIFY_LENGTH];   //	ä�� �޼���   
	char    szName[SZNAME_LENGTH];		//	ä�� �޼����� ������ ĳ���� �̸�   
};

// ���� �޽���
#define CSP_REQ_APPEAL_CHAT					0x150F
#define SCP_RESP_APPEAL_CHAT				0x950F
typedef struct _S_CSP_REQ_APPEAL_CHAT
{	_MSG;
	char	szMsg[MAX_CHAT_LENGTH];
} S_CSP_REQ_APPEAL_CHAT, * PS_CSP_REQ_APPEAL_CHAT;
typedef struct _S_SCP_RESP_APPEAL_CHAT
{	_MSG;
	BYTE	byResult;	// ��� : 0x00 - ����, 0x01 - ����(�������� ����), 0x02 - ����(���� ó���ѵ� �ʰ�)
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
	BYTE	byBgColor;				// ä�� �޼��� ����                                              
	BYTE	byTextColor;			// ä�� �޼��� ���ڻ�    
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // ä�� �޼���    
	char    szSourName[SZNAME_LENGTH];			// ä�� �޼����� ������ ĳ���� �̸�  
	char    szDestName[SZNAME_LENGTH];			// ä�� �޼����� ������ ĳ���� �̸�            
};
struct S_SSP_RESP_WHISPER_CHAT
{	_MSG	
	int		nID;
	BYTE	byResult;
	BYTE	byBgColor;				// ä�� �޼��� ����                                              
	BYTE	byTextColor;			// ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH]; // ä�� �޼���                                              
	char    szName[SZNAME_LENGTH];				// ä�� �޼����� ������ ĳ���� �̸� 
};
struct S_SSP_NOTIFY_WHISPER_CHAT
{	_MSG	
	int		nID;
	BYTE	byBgColor;							// ä�� �޼��� ����                                              
	BYTE	byTextColor;						// ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;
	BYTE	byDummy;
	short	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];				// ä�� �޼���                                              
	char    szName[SZNAME_LENGTH];				// ä�� �޼����� ������ ĳ���� �̸� 
};

//#define	SSP_REQ_BROADCAST			0x0011
//#define SSP_NOTIFY_BROADCAST		0x8012
//struct S_SSP_REQ_BROADCAST
//{	_MSG	
//	int		nID;
//	BYTE	byMsgType;				//	��Ƽ(0), ���(1), ��(2), ����(3), ����(4)	
//	BYTE	byBgColor;				//	ä�� �޼��� ����                                              
//	BYTE	byTextColor;			//	ä�� �޼��� ���ڻ�
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH]; //	ä�� �޼���            
//};
//struct S_SSP_NOTIFY_BROADCAST
//{	_MSG
//	BYTE	byMsgType;				//	��Ƽ(0), ���(1), ��(2), ����(3), ����(4)	
//	BYTE	byBgColor;				//	ä�� �޼��� ����                                              
//	BYTE	byTextColor;			//	ä�� �޼��� ���ڻ�                                              
//	BYTE	byTrimuriti;
//	char	szMsg[MAX_NOTIFY_LENGTH]; //	ä�� �޼���                                              
//	char    szName[SZNAME_LENGTH];	//	�޼����� ������ ĳ���� �̸� 
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
	BYTE	byResult;	// ��� : 0x00 - ����, 0x01 - ����(�������� ����), 0x02 - ����(���� ó���ѵ� �ʰ�)
	BYTE	byDummy;
	SHORT	snDummy;
	char	szMsg[MAX_CHAT_LENGTH];
} S_SSP_RESP_APPEAL_CHAT, * PS_SSP_RESP_APPEAL_CHAT;

#define _MSG_COMMAND				0x1510
struct MSG_COMMAND
{
	_MSG
	BYTE	byMsgType;					//	��(1), ����(2), ����(3)	
	BYTE	byBgColor;					//	ä�� �޼��� ����                                              
	BYTE	byTextColor;				//	ä�� �޼��� ���ڻ�  
	BYTE	byTrimuriti;				//	�ɸ����� �ֽ�
	char	szMsg[MAX_NOTIFY_LENGTH];   //	ä�� �޼���   
	char    szName[SZNAME_LENGTH];		//	ä�� �޼����� ������ ĳ���� �̸�   
};

#define _MSG_ServerCommand			0x1511
struct MSG_ServerCommand
{
	_MSG
	BYTE	byCommandType;					//	��ɾ� ����(0:�α״���,..)
	BYTE	byDummy1;					                                             
	BYTE	byDummy2;					
	BYTE	byDummy3;					 
};

#define	SSP_REQ_ZONE_INIT			0x0013
//	S_CSP_REQ_TRADE_CANCEL�� S_REQUEST�� �̿��ϱ�� �Ѵ�.
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
		BYTE				byRemoveType;						//	�ڽ��� Ż��(1), ��������(2), �����ü(3)
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
		int					nMoney;				//	���Ǿ� �Ǵ� Ÿ��
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
		int			nID;					//	����� nID
		BYTE		byResult;				
		BYTE		byType;					//	enum { eGuildFriend = 1, eGuildHost = 2, };				//	1:����, 2:����
		BYTE		byAct;					//	enum { eGuildAllianceIn = 1, eGuildAllianceOut = 2, };	//	1:�Ἲ, 2:��ü
		BYTE		byDummy;
};

#define _Msg_GuildCargoUsingLevel				0x1615
struct Msg_GuildCargoUsingLevel				//	������(��������), ���϶��ڸ� �̿밡��
{
	_MSG
	int		nGuildID;
	BYTE	byCargoLevel[3];
	BYTE	byDummy;
};

#define _Msg_GuildCargoTimeExtension			0x1616
struct Msg_GuildCargoTimeExtension			//	���϶��ڸ� �̿밡��
{
	_MSG
	BYTE	byResult;						//	0:����, 1:����
	BYTE	byType;							//	1: 1�����, 2: 1,2�����, 3: 1,2,3�����
	short	snDummy;
};

#define _Msg_GuildCargoTime						0x1617
struct Msg_GuildCargoTime					//	������(��������), ���϶��ڸ� �̿밡��
{
	_MSG
	int			nGuildID;
	DWORD		dwTime[3];
};

#define _Msg_GuildItem							0x1618
struct Msg_GuildItem
{
	_MSG
	STRUCT_ITEM arrItem[MAX_CARGO*3];				//	���â����Ʈ(_Msg_GuildCargoUse�� ����û�� ������� �˸���)
};

#define _Msg_GuildCargoUse						0x1619
struct Msg_GuildCargoUse
{
	_MSG
	BYTE	bySet;									//	0:�������, 1:����û
	BYTE	byResult;								//	��������� ����û�� ���� ���(0:����, 1:����)
};

#define _Msg_GuildCargoUseUpdate				0x1620
struct Msg_GuildCargoUseUpdate
{
	_MSG
	int		nGuildID;
	char	pUsingMember[SZNAME_LENGTH];			//	â�� ������� �ɸ���(���� ��� null)
};

#define _Msg_GuildItemUpdate					0x1621
struct Msg_GuildItemUpdate
{
	_MSG
	int				nGuildID;
	int				nCargoIndex;
	STRUCT_ITEM		item;
};

/************************************************************************************************/
//	MESSENGER PACKET 2700 - 2710
/************************************************************************************************/
#define	MAX_MESSENGER		28
struct STRUCT_MESSENGER_ITEM
{		char	szCharName[SZNAME_LENGTH];		
		BYTE	Status;						// 0:�󽽷� 1:OFF	2:ON	3:BLOCK?(����)
		BYTE	Opponent;
		short	snTribe;					// ĳ������ ����                                   			
};

struct STRUCT_MESSENGER_LIST
{   int		Login;
    int		Slot;
	char	AccountName[ACCOUNTNAME_LENGTH];	// ���� ������� ��ī��Ʈ
	char	CharName[SZNAME_LENGTH];
	STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];
};	

#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
	struct STRUCT_OLD_MESSENGER_LIST
	{	int		Login;
		int		Slot;
		char	AccountName[OLD_ACCOUNTNAME_LENGTH];	// ���� ������� ��ī��Ʈ
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
#define	_MSG_UpdateMessengerList			0x2702  // ��ü �޽��� ������ �����Ѵ�
struct	MSG_UpdateMessengerList
{		_MSG
		int		nID;							// 1~999
		STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];
};
#define	_MSG_UpdateMessengerItem			0x2703	// �Ѱ��� �޽��� ������ �����Ѵ�
struct	MSG_UpdateMessengerItem
{		_MSG
		int		nID;							// 1~999
		int		nSlot;
		STRUCT_MESSENGER_ITEM Item;
};
// Ŭ���̾�Ʈ�� Char_init��û ���� STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER] �� memset(0) �Ѵ�.
// Ŭ���̾�Ʈ�� �޽����� �������� �߰�/���� �Ұ�� ������ UpdateMessengerItem�� ������.
// ��û���ϰ� ������ ������ UpdateMessengerItem���� �����ϰ�, ������ MessageBox�� �ش�.
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

//#define	_MSG_MessengerChangeMyInfo					0x2704		//	ģ���� ������ ����� �����(ZS<->MSG)
//struct MSG_MessengerChangeMyInfo 
//{
//		_MSG
//		int		nID;
//		STRUCT_MESSENGER_ITEM Item;
//};
//#define _MSG_MessengerSave					0x2705		//	�������� ������ messenger���������� �˸�.(ZS->MSG)
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
struct   MSG_REQParty                       //	��Ƽ������ ������ ��û��
{											//	������ �������� ��ü ����Ʈ
	    _MSG;								//	C->S, S->C �޼���
         S_PARTY Leader;
		 int   TargetID;
};
#define _MSG_CNFParty                       0x2402
struct   MSG_CNFParty                       //	��Ƽ������ ������ �㰡��.
{                                           //	C->S �޼���
	    _MSG;
        int	TargetID;
};
#define _MSG_AddParty               		0x2403
struct   MSG_AddParty              		//	����߰���, ��Ƽ���Խ� ��������� ���ư���.
{                                   		//	S->C
	    _MSG;
		int nLeaderID;
		S_PARTY Party;
};
#define _MSG_RemoveParty					0x2404
struct   MSG_RemoveParty                 	//	���Ż��ó� ��Ƽ��ü�� ��������� ���ư���.
{                                        	//	C->S �ڽ��� Ż��� nID=�ڽ�, 
	    _MSG;								//	C->S ������ �������� nID=Ÿ��,
		int nLeaderID;						//	C->S ������ ��Ƽ��ü�� nID=MAX_USER(1000)
		int nTargetID;						//	S->C ��� Ż�� ����� ������ ����.
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
	byte	byRootingMode;					//	��Ƽ������ ���ü����� �ٲܼ� �ִ�.(ROOTING_SHARE=0, ROOTING_PERSON=1)
	short   snDummy;
};

/************************************************************************************************/

#define _MSG_GMMode							0x2501
struct MSG_GMMode
{
		_MSG
		int		nID;
		BYTE	byResult;						//	0:����, 1:����
		BYTE	byGMMode;						//	bit flag(0x01:�ɸ��ͺ�, 0x02:������, 0x04:ä�ú�, ...)	
		short	snDummy;
		char	szCharName[SZNAME_LENGTH];		//	bit flag �߸��ߺ��� | ������.
};
#define _MSG_GMMode_Notify					0x2502
struct MSG_GMMode_Notify
{
		_MSG
		int		nID;
		BYTE	byGMMode;						//	bit flag(0x01:�ɸ��ͺ�, 0x02:������, 0x04:ä�ú�, ...)	
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
	int			nID;						// S->S �϶���, Ŭ���̾�Ʈ�� ������ 0�� �ִ´�.
	int			nResult;					// S->C �϶���, 0�̸� ����, 1�̸� ������ �ƴ�.
	char		szCharName[SZNAME_LENGTH];
};
#define _MSG_Warp							0x2506
struct MSG_Warp
{	_MSG;
	int		nID;		//	ȣ���� ID(ȣ���ڰ� ���� ��� 0)
	byte	byResult;
	byte	byType;
	short	snDummy;
	DWORD	dwPlace;
	char	szName[SZNAME_LENGTH];
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
	short                                             snDialog;		// ��ȭ ��ȣ
	byte                                              byResult;     // ��ȭ ���
	byte											  byDummy;

} S_CSP_QUEST_DIALOG, * PS_CSP_QUEST_DIALOG;


// SCP_QUEST_DIALOG : 0x9702
typedef struct _S_SCP_QUEST_DIALOG
{	_MSG;
	short                                              wIndex;       // ��ȭ ��ȣ
    short											   snDummy;
} S_SCP_QUEST_DIALOG, * PS_SCP_QUEST_DIALOG;


// CSP_QUEST_NOTIFY_LEVEL : 0x1703
typedef struct _S_CSP_QUEST_NOTIFY_LEVEL
{	_MSG;
	SHORT											  snNPCIndex;	// NPC �ε��� ��ȣ
} S_CSP_QUEST_NOTIFY_LEVEL, * PS_CSP_QUEST_NOTIFY_LEVEL;


// SCP_QUEST_NOTIFY_LEVEL : 0x9703
typedef struct _S_SCP_QUEST_NOTIFY_LEVEL
{	_MSG;
	SHORT                                             snNPCIndex;   // NPC �ε��� ��ȣ
	BYTE                                              byIndex;      // ����Ʈ �ε��� ��ȣ
	BYTE                                              byLevel;      // ����Ʈ ���� ����

} S_SCP_QUEST_NOTIFY_LEVEL, * PS_SCP_QUEST_NOTIFY_LEVEL;


// CSP_MONSTER_DISAPPEAR : 0x1801
typedef struct _S_CSP_MONSTER_DISAPPEAR
{

} S_CSP_MONSTER_DISAPPEAR, * PS_CSP_MONSTER_DISAPPEAR;


// SCP_MONSTER_DISAPPEAR : 0x9801
typedef struct _S_SCP_MONSTER_DISAPPEAR
{
	DWORD                                             dwKeyID;      // Monster�� KeyID
	BYTE                                              byType;       // Monster�� ������� ����

} S_SCP_MONSTER_DISAPPEAR, * PS_SCP_MONSTER_DISAPPEAR;


// CSP_CHAR_STATUS : 0x1802
typedef struct _S_CSP_CHAR_STATUS
{

} S_CSP_CHAR_STATUS, * PS_CSP_CHAR_STATUS;


// SCP_CHAR_STATUS : 0x9802
typedef struct _S_SCP_CHAR_STATUS
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	DWORD                                             dwStatus;     // ĳ������ ���� ����

} S_SCP_CHAR_STATUS, * PS_SCP_CHAR_STATUS;


// CSP_CHAR_MONSTER_STATUS_BROADCAST : 0x1803
typedef struct _S_CSP_CHAR_MONSTER_STATUS_BROADCAST
{

} S_CSP_CHAR_MONSTER_STATUS_BROADCAST, * PS_CSP_CHAR_MONSTER_STATUS_BROADCAST;


// SCP_CHAR_MONSTER_STATUS_BROADCAST : 0x9803
typedef struct _S_SCP_CHAR_MONSTER_STATUS_BROADCAST
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	BYTE                                              byAct;        // ����
	DWORD                                             dwStatus;     // ����

} S_SCP_CHAR_MONSTER_STATUS_BROADCAST, * PS_SCP_CHAR_MONSTER_STATUS_BROADCAST;


// CSP_CHAR_DEATH : 0x1805
typedef struct _S_CSP_CHAR_DEATH
{

} S_CSP_CHAR_DEATH, * PS_CSP_CHAR_DEATH;


// SCP_CHAR_DEATH : 0x9805
typedef struct _S_SCP_CHAR_DEATH
{
	short                                             snLossPrana;  // �ҽǵ� ������ ��
	BYTE                                              byCount;      // �ҽǵ� �������� ��

} S_SCP_CHAR_DEATH, * PS_SCP_CHAR_DEATH;


// CSP_CHAR_MONSTER_DEATH_BROADCAST : 0x1806
typedef struct _S_CSP_CHAR_MONSTER_DEATH_BROADCAST
{

} S_CSP_CHAR_MONSTER_DEATH_BROADCAST, * PS_CSP_CHAR_MONSTER_DEATH_BROADCAST;


// SCP_CHAR_MONSTER_DEATH_BROADCAST : 0x9806
typedef struct _S_SCP_CHAR_MONSTER_DEATH_BROADCAST
{
	DWORD                                             dwKeyID;      // ���� ĳ���� �Ǵ� Monster�� KeyID

} S_SCP_CHAR_MONSTER_DEATH_BROADCAST, * PS_SCP_CHAR_MONSTER_DEATH_BROADCAST;


// CSP_CHAR_HP_RECOVERY : 0x1811
typedef struct _S_CSP_CHAR_HP_RECOVERY
{

} S_CSP_CHAR_HP_RECOVERY, * PS_CSP_CHAR_HP_RECOVERY;


// SCP_CHAR_HP_RECOVERY : 0x9811
typedef struct _S_SCP_CHAR_HP_RECOVERY
{
	int                                               nCurHP;       // ȸ���� ���� ���� HP
	short                                             snHPRecoveryRate;// ĳ������ HP ȸ����
	int                                               nPrana;       // �� ������ ��

} S_SCP_CHAR_HP_RECOVERY, * PS_SCP_CHAR_HP_RECOVERY;


// CSP_MONSTER_HP_RECOVERY : 0x1812
typedef struct _S_CSP_MONSTER_HP_RECOVERY
{

} S_CSP_MONSTER_HP_RECOVERY, * PS_CSP_MONSTER_HP_RECOVERY;


// SCP_MONSTER_HP_RECOVERY : 0x9812
typedef struct _S_SCP_MONSTER_HP_RECOVERY
{
	int                                               nCurHP;       // ȸ���� ���� ���� HP
	short                                             snStress;     // Monster ��Ʈ����

} S_SCP_MONSTER_HP_RECOVERY, * PS_SCP_MONSTER_HP_RECOVERY;


// CSP_CHAR_CAST_PROMOTE : 0x1821
typedef struct _S_CSP_CHAR_CAST_PROMOTE
{

} S_CSP_CHAR_CAST_PROMOTE, * PS_CSP_CHAR_CAST_PROMOTE;


// SCP_CHAR_CAST_PROMOTE : 0x9821
typedef struct _S_SCP_CHAR_CAST_PROMOTE
{
	BYTE                                              byCastClass;  // ��µ� ���� ī��Ʈ ���
	BYTE                                              byCastGrade;  // ��µ� ���� ī��Ʈ ���

} S_SCP_CHAR_CAST_PROMOTE, * PS_SCP_CHAR_CAST_PROMOTE;


// CSP_CHAR_CAST_PROMOTE_BROADCAST : 0x1822
typedef struct _S_CSP_CHAR_CAST_PROMOTE_BROADCAST
{

} S_CSP_CHAR_CAST_PROMOTE_BROADCAST, * PS_CSP_CHAR_CAST_PROMOTE_BROADCAST;


// SCP_CHAR_CAST_PROMOTE_BROADCAST : 0x9822
typedef struct _S_SCP_CHAR_CAST_PROMOTE_BROADCAST
{
	char                                              	szName[SZNAME_LENGTH];   // ĳ������ �̸�
	BYTE                                              	byCastClass;  // ��µ� ���� ī��Ʈ ���
	BYTE                                              	byCastGrade;  // ��µ� ���� ī��Ʈ ���
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
	char                                              szName[SZNAME_LENGTH];   // ĳ������ �̸�

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
	int                                               nPrana;       // ���� ����
	short                                             snChakraMuscle;// ������ ��ũ��
	short                                             snChakraNerve;// �Ű��� ��ũ��
	short                                             snChakraHeart;// ������ ��ũ��
	short                                             snChakraSoul; // ������ ��ũ��
	short                                             snPureChakraMuscle;// ���� ������ ��ũ��
	short                                             snPureChakraNerve;// ���� �Ű��� ��ũ��
	short                                             snPureChakraHeart;// ���� ������ ��ũ��
	short                                             snPureChakraSoul;// ���� ������ ��ũ��
	short                                             snPhysicalMinDamage;// ���� �ּ� ������
	short                                             snPhysicalMaxDamage;// ���� �ִ� ������
	short                                             snMagicMinDamage;// ���� �ּ� ������
	short                                             snMagicMaxDamage;// ���� �ִ� ������
	short                                             snFireMinDamage;// �� �ּ� ������
	short                                             snFireMaxDamage;// �� �ִ� ������
	short                                             snColdMinDamage;// ���� �ּ� ������
	short                                             snColdMaxDamage;// ���� �ִ� ������
	short                                             snPoisonMinDamage;// �� �ּ� ������
	short                                             snPoisonMaxDamage;// �� �ִ� ������
	short                                             snAcidMinDamage;// �� �ּ� ������
	short                                             snAcidMaxDamage;// �� �ִ� ������
	short                                             snArmorIntensity;// ������ ����-����
	short                                             snAttackSuccRate;// ���� ������
	short                                             snAvoidanceRate;// ȸ����
	int                                               nMaxHP;       // ĳ������ �ִ� HP
	short                                             snFireResist; // �� ���׷�
	short                                             snColdResist; // ���� ���׷�
	short                                             snPoisonResist;// �� ���׷�
	short                                             snAcidResist; // �� ���׷�

} S_SCP_CHAR_PARAMS_CHANGE, * PS_SCP_CHAR_PARAMS_CHANGE;


// CSP_REQ_CHAKRA_RISING : 0x1921
typedef struct _S_CSP_REQ_CHAKRA_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID
	BYTE                                              byReqChakraPart;// ��ũ�� ��� ��û ����

} S_CSP_REQ_CHAKRA_RISING, * PS_CSP_REQ_CHAKRA_RISING;


// SCP_RESP_CHAKRA_RISING : 0x9921
typedef struct _S_SCP_RESP_CHAKRA_RISING
{
	BYTE                                              byResult;     // ���
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
	BYTE                                              byResult;     // ���
	int                                               nRisingBrahman;// ��� �� ���� ��� ����Ʈ ��
	BYTE                                              byCastClass;  // ��� ����Ʈ ��� �� ī��Ʈ ���
	BYTE                                              byCastGrade;  // ��� ����Ʈ ��� �� ī��Ʈ ���
	int                                               nPrana;       

} S_SCP_RESP_BRAHMAN_RISING, * PS_SCP_RESP_BRAHMAN_RISING;


// CSP_REQ_INCREASE_INVENTORY_SLOT : 0x1931
typedef struct _S_CSP_REQ_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// �κ��丮 ����

} S_CSP_REQ_INCREASE_INVENTORY_SLOT, * PS_CSP_REQ_INCREASE_INVENTORY_SLOT;


// SCP_RESP_INCREASE_INVENTORY_SLOT : 0x9931
typedef struct _S_SCP_RESP_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // �κ��丮 ���� ���� ��û ���
	BYTE                                              byCount;      // Inventory Expand Info

} S_SCP_RESP_INCREASE_INVENTORY_SLOT, * PS_SCP_RESP_INCREASE_INVENTORY_SLOT;


// CSP_REQ_DECREASE_INVENTORY_SLOT : 0x1932
typedef struct _S_CSP_REQ_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// �κ��丮 ����
	BYTE                                              byX;          // Bag Item �� ��ǥ X
	BYTE                                              byZ;          // Bag Item �� ��ǥ Z

} S_CSP_REQ_DECREASE_INVENTORY_SLOT, * PS_CSP_REQ_DECREASE_INVENTORY_SLOT;


// SCP_RESP_DECREASE_INVENTORY_SLOT : 0x9932
typedef struct _S_SCP_RESP_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // ���

} S_SCP_RESP_DECREASE_INVENTORY_SLOT, * PS_SCP_RESP_DECREASE_INVENTORY_SLOT;


// CSP_REQ_NPC_POINT_UP : 0x1941
typedef struct _S_CSP_REQ_NPC_POINT_UP
{
	DWORD                                             dwNPCKeyID;   // NPC KeyID

} S_CSP_REQ_NPC_POINT_UP, * PS_CSP_REQ_NPC_POINT_UP;


// SCP_RESP_NPC_POINT_UP : 0x9941
typedef struct _S_SCP_RESP_NPC_POINT_UP
{
	BYTE                                              byResult;     // NPC ģ���� ��� ��û ���
	DWORD                                             dwGroup;      // NPC ���� ��ȣ
	DWORD                                             dwPoint;      // ��� �� ����� ����Ʈ ��

} S_SCP_RESP_NPC_POINT_UP, * PS_SCP_RESP_NPC_POINT_UP;


// CSP_REQ_CHANGE_CKAKRA_TO_PRANA : 0x1951
typedef struct _S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA
{

} S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA, * PS_CSP_REQ_CHANGE_CKAKRA_TO_PRANA;


// SCP_RESP_CHANGE_CKAKRA_TO_PRANA : 0x9951
typedef struct _S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA
{
	BYTE                                              byResult;     // NPC ģ���� ��� ��û ���
	int                                               nPrana;       // �������� ��

} S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA, * PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA;


// CSP_OTHER_CHAR_PARAM_BROADCAST : 0x1952
typedef struct _S_CSP_OTHER_CHAR_PARAM_BROADCAST
{

} S_CSP_OTHER_CHAR_PARAM_BROADCAST, * PS_CSP_OTHER_CHAR_PARAM_BROADCAST;


// SCP_OTHER_CHAR_PARAM_BROADCAST : 0x9952
typedef struct _S_SCP_OTHER_CHAR_PARAM_BROADCAST
{
	DWORD                                             dwKeyID;      // �ɸ����� KeyID
	DWORD                                             dwGuildMark;  // ��帶ũ�ε���

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
	DWORD                                             dwIndex;      // ����� ��ų�� Index
	BYTE                                              byType;       // SKILL�� ����

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
	DWORD                                             dwIndex;      // �ڵ� ��ϵ� ��ų�� Index
	BYTE                                              byType;       // SKILL�� ����

} S_SCP_SKILL_REGIST, * PS_SCP_SKILL_REGIST;


// CSP_REQ_SKILL_SELECT : 0x2003
typedef struct _S_CSP_REQ_SKILL_SELECT
{
	BYTE                                              bySelect;     // SKILL�� ����/����
	BYTE                                              byHand;       // SKILL ������/���� ����
	DWORD                                             dwIndex;      // ����/���� ��ų Index

} S_CSP_REQ_SKILL_SELECT, * PS_CSP_REQ_SKILL_SELECT;


// SCP_RESP_SKILL_SELECT : 0xA003
typedef struct _S_SCP_RESP_SKILL_SELECT
{
	BYTE                                              byResult;     // SKILL ����/���� ���

} S_SCP_RESP_SKILL_SELECT, * PS_SCP_RESP_SKILL_SELECT;


// CSP_REQ_SKILL_SELECT_BROADCAST : 0x2004
typedef struct _S_CSP_REQ_SKILL_SELECT_BROADCAST
{

} S_CSP_REQ_SKILL_SELECT_BROADCAST, * PS_CSP_REQ_SKILL_SELECT_BROADCAST;


// SCP_RESP_SKILL_SELECT_BROADCAST : 0xA004
typedef struct _S_SCP_RESP_SKILL_SELECT_BROADCAST
{
	DWORD                                             dwKeyID;      // �ɸ����� KeyID
	BYTE                                              bySelect;     // SKILL�� ����/����
	BYTE                                              byHand;       // SKILL ������/���� ����
	DWORD                                             dwIndex;      // ����/���� ��ų Index
	BYTE                                              byLevel;      // ��ų ����

} S_SCP_RESP_SKILL_SELECT_BROADCAST, * PS_SCP_RESP_SKILL_SELECT_BROADCAST;


// CSP_REQ_SKILL_USE2_CHAR : 0x2011
typedef struct _S_CSP_REQ_SKILL_USE2_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ������ ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_SKILL_USE2_CHAR, * PS_CSP_REQ_SKILL_USE2_CHAR;


// SCP_RESP_SKILL_USE2_CHAR : 0xA011
typedef struct _S_SCP_RESP_SKILL_USE2_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_SCP_RESP_SKILL_USE2_CHAR, * PS_SCP_RESP_SKILL_USE2_CHAR;


// CSP_SKILL_READY_CHAR_BROADCAST : 0x2012
typedef struct _S_CSP_SKILL_READY_CHAR_BROADCAST
{

} S_CSP_SKILL_READY_CHAR_BROADCAST, * PS_CSP_SKILL_READY_CHAR_BROADCAST;


// SCP_SKILL_READY_CHAR_BROADCAST : 0xA012
typedef struct _S_SCP_SKILL_READY_CHAR_BROADCAST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwKeyID;      // ��ų�� ����ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;// ��ų ������ ���ϴ� ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ

} S_SCP_SKILL_READY_CHAR_BROADCAST, * PS_SCP_SKILL_READY_CHAR_BROADCAST;


// CSP_REQ_SKILL_ATK_CHAR : 0x2013
typedef struct _S_CSP_REQ_SKILL_ATK_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ������ ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	short                                             snDegree;     // �����ڸ� �߽����� �� ������� ����
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_SKILL_ATK_CHAR, * PS_CSP_REQ_SKILL_ATK_CHAR;


// SCP_RESP_SKILL_ATK_CHAR : 0xA013
typedef struct _S_SCP_RESP_SKILL_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCharX;      // ����� X ��ǥ
	short                                             snCharZ;      // ����� Z ��ǥ
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ����/Monster�� ���� HP

} S_SCP_RESP_SKILL_ATK_CHAR, * PS_SCP_RESP_SKILL_ATK_CHAR;


// CSP_SKILL_ATK_CHAR_BROADCAST : 0x2014
typedef struct _S_CSP_SKILL_ATK_CHAR_BROADCAST
{

} S_CSP_SKILL_ATK_CHAR_BROADCAST, * PS_CSP_SKILL_ATK_CHAR_BROADCAST;


// SCP_SKILL_ATK_CHAR_BROADCAST : 0xA014
typedef struct _S_SCP_SKILL_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // ��� Type
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // ��ų�� ����ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;//  ��ų ������ ���ϴ� ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	short                                             snCharX;      // ����� X ��ǥ
	short                                             snCharZ;      // ����� Z ��ǥ
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ������ ���� HP
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCurX;       // �������� ���� X ��ǥ
	short                                             snCurZ;       // �������� ���� Z ��ǥ

} S_SCP_SKILL_ATK_CHAR_BROADCAST, * PS_SCP_SKILL_ATK_CHAR_BROADCAST;


// CSP_REQ_SKILL_LEVEL_UP : 0x2021
typedef struct _S_CSP_REQ_SKILL_LEVEL_UP
{
	DWORD                                             dwIndex;      // Level-Up�� ��û�� ��ų�� Index

} S_CSP_REQ_SKILL_LEVEL_UP, * PS_CSP_REQ_SKILL_LEVEL_UP;


// SCP_RESP_SKILL_LEVEL_UP : 0xA021
typedef struct _S_SCP_RESP_SKILL_LEVEL_UP
{
	BYTE                                              byResult;     // Level-Up ���
	BYTE                                              byLevel;      // ��ų�� Level
	int                                               nPrana;       // ���� ������ ��
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�

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
	BYTE                                              byCount;      // ���� ������ ��ų�� ��

} S_SCP_RESP_SHOP_SKILL_LIST, * PS_SCP_RESP_SHOP_SKILL_LIST;

#define CSP_REQ_SHOP_ITEM_LIST                            0x2101      // ���� ������ ������ List�� ��û
#define SCP_RESP_SHOP_ITEM_LIST                           0xA101      // ���� ������ ������ List ��û�� ���� ����޼���
typedef struct _S_CSP_REQ_SHOP_ITEM_LIST
{
	DWORD                                             dwIndex;      
	DWORD                                             dwNpcKeyID;   

} S_CSP_REQ_SHOP_ITEM_LIST, * PS_CSP_REQ_SHOP_ITEM_LIST;
typedef struct _S_SCP_RESP_SHOP_ITEM_LIST
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwMakingIndex;// �������� ������ Index
	DWORD                                             dwRemainTime; // �������� �������� ���� ���۽ð�
	BYTE                                              byCount;      // ���� ������ �������� ��

} S_SCP_RESP_SHOP_ITEM_LIST, * PS_SCP_RESP_SHOP_ITEM_LIST;

#define CSP_REQ_ITEM_BUY								  0x2102      // �������� ���
#define SCP_RESP_ITEM_BUY	                              0xA102      // ������ ���Կ� ���� ����޼���
typedef struct _S_CSP_REQ_ITEM_BUY
{	_MSG;
	short											  snNPCIndex;	// ������ ������ ���� index
	short                                             snItemIndex;  // ������ ������ Index
	short											  snItemCount;	// ������ ������ ����
	short											  snDummy;
} S_CSP_REQ_ITEM_BUY, * PS_CSP_REQ_ITEM_BUY;
typedef struct _S_SCP_RESP_ITEM_BUY
{	_MSG;
	BYTE            byResult;		// 0-����, 1-����
	BYTE			byDummy;
	short			snItemIndex;	// ������ �����ε���
	int				nMoney;			// ���� �̿� �� ����� ��
} S_SCP_RESP_ITEM_BUY, * PS_SCP_RESP_ITEM_BUY;

#define CSP_REQ_ITEM_SELL                               0x2104      // ������ ������ ��û
#define SCP_RESP_ITEM_SELL                              0xA104      // ������ ������û�� ���� ����޼���
typedef struct _S_CSP_REQ_ITEM_SELL
{	_MSG;
	short	snNPCIndex;	// ������ �Ǹ��� ���� index
	BYTE    byPlace;	// â��, �κ�, ����
	BYTE	byIndex;	// �Ǹ��� ������ ��ġ Index											  
} S_CSP_REQ_ITEM_SELL, * PS_CSP_REQ_ITEM_SELL;
typedef struct _S_SCP_RESP_ITEM_SELL
{   _MSG;
	BYTE    byResult;		// 0-����, 1-����                                          
	BYTE	byPlace;		// â��, �κ�, ����										  
	BYTE	byIndex;		// �Ǹ��� ������ ��ġ Index										  
	BYTE	byDummy;
	int		nMoney;			// ���� �̿� �� ����� ��
} S_SCP_RESP_ITEM_SELL, * PS_SCP_RESP_ITEM_SELL;

#define CSP_REQ_ITEM_REPAIR								0x2105
#define SCP_RESP_ITEM_REPAIR							0xA105
#define 	S_CSP_REQ_ITEM_REPAIR		S_CSP_REQ_ITEM_SELL	
#define		PS_CSP_REQ_ITEM_REPAIR		PS_CSP_REQ_ITEM_SELL
#define 	S_SCP_RESP_ITEM_REPAIR		S_SCP_RESP_ITEM_SELL
#define 	PS_SCP_RESP_ITEM_REPAIR		PS_SCP_RESP_ITEM_SELL

#define CSP_REQ_ITEM_REFINING                             0x2106      // ������ ������ ��û
#define SCP_RESP_ITEM_REFINING                            0xA106      // ������ ���� ��û�� ���� ����޼���
typedef struct _S_CSP_REQ_ITEM_REFINING
{	_MSG
	BYTE	byPlace;
	BYTE	byIndex;
	BYTE	bySubPlace[3];											//	Index 0:��,������� 1:���÷���� 2:����
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

#define CSP_REQ_PRANA_CONTRIBUTION                        0x2112      // ���� �峳�� ��û
#define SCP_RESP_PRANA_CONTRIBUTION                       0xA112      // ���� �峳�� ��û�� ���� ����޼���
typedef struct _S_CSP_REQ_PRANA_CONTRIBUTION
{
	int                                               nPrana;       // �峳�� ������ ��

} S_CSP_REQ_PRANA_CONTRIBUTION, * PS_CSP_REQ_PRANA_CONTRIBUTION;
typedef struct _S_SCP_RESP_PRANA_CONTRIBUTION
{
	BYTE                                              byResult;     // Result Field
	int                                               nBrahmanPoint;// �峳 �� ��� ����Ʈ
	int                                               nMaxHP;       // �� ĳ������ �ִ� HP
	short                                             snUsePrana;   // �� ������ ��ũ�󿡼� �����ð��� �Ҹ�Ǵ� �� ������ ��

} S_SCP_RESP_PRANA_CONTRIBUTION, * PS_SCP_RESP_PRANA_CONTRIBUTION;


#define CSP_REQ_RESOURCE_BARTER                           0x2113      // ��ȯ�ҿ��� �ڿ� ��ȯ�� ��û
#define SCP_RESP_RESOURCE_BARTER                          0xA113      // ��ȯ�ҿ��� �ڿ� ��ȯ��û�� ���� ����޼���
typedef struct _S_CSP_REQ_RESOURCE_BARTER
{
	DWORD                                             dwNpcKeyID;   // ��ȯ�� NPC KeyID
	DWORD                                             dwKeyID;      // ��ȯ�� �������� KEYID
	int                                               nItemCount;   // ��ȯ�� �������� ��ø����

} S_CSP_REQ_RESOURCE_BARTER, * PS_CSP_REQ_RESOURCE_BARTER;
typedef struct _S_SCP_RESP_RESOURCE_BARTER
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // ���� ���Ǿ�
	int                                               nCloth;       // ���� ����ī��Ʈ(�ǹ̾���)

} S_SCP_RESP_RESOURCE_BARTER, * PS_SCP_RESP_RESOURCE_BARTER;

#define CSP_REQ_RESOURCE_BARTER_PRICE                     0x2114      // ��ȯ�ҿ����� �ڿ���ȯ������ ��û�Ѵ�.
#define SCP_RESP_RESOURCE_BARTER_PRICE                    0xA114      // ��ȯ�ҿ����� �ڿ���ȯ������ ��û�Ѵ�.
typedef struct _S_CSP_REQ_RESOURCE_BARTER_PRICE
{

} S_CSP_REQ_RESOURCE_BARTER_PRICE, * PS_CSP_REQ_RESOURCE_BARTER_PRICE;
typedef struct _S_SCP_RESP_RESOURCE_BARTER_PRICE
{
	int                                               nSteelCount;  // ö�� ��ȯ����
	int                                               nClothCount;  // ������ ��ȯ����

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
//	S_CSP_REQ_TRADE_CANCEL�� S_REQUEST�� �̿��ϱ�� �Ѵ�.
//	S_SCP_RESP_TRADE_CANCEL�� S_RESULT�� �̿��ϱ�� �Ѵ�.


// CSP_REQ_TRANSPARENCY_MODE : 0x2501
typedef struct _S_CSP_REQ_TRANSPARENCY_MODE
{
	BYTE                                              byMode;       // ������ �����÷���

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
	BYTE												byMode;       // ������ �����÷���
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// GM ĳ���� �̸�

} S_SCP_TRANSPARENCY_MODE_NOTIFY, * PS_SCP_TRANSPARENCY_MODE_NOTIFY;

//
//// CSP_REQ_MOVE_POSITION : 0x2511
//typedef struct _S_CSP_REQ_MOVE_POSITION
//{
//	short                                             snX;          // �����̵� X��ǥ
//	short                                             snZ;          // �����̵� Z��ǥ
//	BYTE                                              byY;          // �����̵��� �� ����
//
//} S_CSP_REQ_MOVE_POSITION, * PS_CSP_REQ_MOVE_POSITION;
//
//
//// SCP_RESP_MOVE_POSITION : 0xA511
//typedef struct _S_SCP_RESP_MOVE_POSITION
//{
//	BYTE                                              byResult;     // Result Field
//	short                                             snX;          // �����̵� X��ǥ
//	short                                             snZ;          // �����̵� Z��ǥ
//	BYTE                                              byY;          // �����̵��� �� ����
//
//} S_SCP_RESP_MOVE_POSITION, * PS_SCP_RESP_MOVE_POSITION;


// CSP_REQ_MOVE_NEAR_CHAR : 0x2512
typedef struct _S_CSP_REQ_MOVE_NEAR_CHAR
{
	char                                              szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�

} S_CSP_REQ_MOVE_NEAR_CHAR, * PS_CSP_REQ_MOVE_NEAR_CHAR;


// SCP_RESP_MOVE_NEAR_CHAR : 0xA512
typedef struct _S_SCP_RESP_MOVE_NEAR_CHAR
{
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // �̵����� ����

} S_SCP_RESP_MOVE_NEAR_CHAR, * PS_SCP_RESP_MOVE_NEAR_CHAR;


// CSP_REQ_CHAR_RECALL : 0x2513
typedef struct _S_CSP_REQ_CHAR_RECALL
{
	char                                              szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�

} S_CSP_REQ_CHAR_RECALL, * PS_CSP_REQ_CHAR_RECALL;


// SCP_RESP_CHAR_RECALL : 0xA513
typedef struct _S_SCP_RESP_CHAR_RECALL
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�

} S_SCP_RESP_CHAR_RECALL, * PS_SCP_RESP_CHAR_RECALL;


// CSP_CHAR_RECALL_NOTIFY : 0x2514
typedef struct _S_CSP_CHAR_RECALL_NOTIFY
{

} S_CSP_CHAR_RECALL_NOTIFY, * PS_CSP_CHAR_RECALL_NOTIFY;


// SCP_CHAR_RECALL_NOTIFY : 0xA514
typedef struct _S_SCP_CHAR_RECALL_NOTIFY
{
	char                                              szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // �̵����� ����

} S_SCP_CHAR_RECALL_NOTIFY, * PS_SCP_CHAR_RECALL_NOTIFY;


// CSP_REQ_CONTROL_CHAT : 0x2521
typedef struct _S_CSP_REQ_CONTROL_CHAT
{
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�
	BYTE												byMode;       // �������
	BYTE												byDummy;
	short												snDummy;

} S_CSP_REQ_CONTROL_CHAT, * PS_CSP_REQ_CONTROL_CHAT;


// SCP_RESP_CONTROL_CHAT : 0xA521
typedef struct _S_SCP_RESP_CONTROL_CHAT
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�

} S_SCP_RESP_CONTROL_CHAT, * PS_SCP_RESP_CONTROL_CHAT;


// CSP_CONTROL_CHAT_NOTIFY : 0x2522
typedef struct _S_CSP_CONTROL_CHAT_NOTIFY
{

} S_CSP_CONTROL_CHAT_NOTIFY, * PS_CSP_CONTROL_CHAT_NOTIFY;


// SCP_CONTROL_CHAT_NOTIFY : 0xA522
typedef struct _S_SCP_CONTROL_CHAT_NOTIFY
{
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�
	BYTE												byMode;       // �������
	BYTE												byDummy;
	short												snDummy;

} S_SCP_CONTROL_CHAT_NOTIFY, * PS_SCP_CONTROL_CHAT_NOTIFY;


// CSP_REQ_CONTROL_ACTION : 0x2531
typedef struct _S_CSP_REQ_CONTROL_ACTION
{
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�
	BYTE												byMode;       // �������
	BYTE												byDummy;
	short												snDummy;

} S_CSP_REQ_CONTROL_ACTION, * PS_CSP_REQ_CONTROL_ACTION;


// SCP_RESP_CONTROL_ACTION : 0xA531
typedef struct _S_SCP_RESP_CONTROL_ACTION
{
	BYTE												byResult;     // Result Field
	BYTE												byDummy;
	short												snDummy;
	char												szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�

} S_SCP_RESP_CONTROL_ACTION, * PS_SCP_RESP_CONTROL_ACTION;


// CSP_CONTROL_ACTION_NOTIFY : 0x2532
typedef struct _S_CSP_CONTROL_ACTION_NOTIFY
{

} S_CSP_CONTROL_ACTION_NOTIFY, * PS_CSP_CONTROL_ACTION_NOTIFY;


// SCP_CONTROL_ACTION_NOTIFY : 0xA532
typedef struct _S_SCP_CONTROL_ACTION_NOTIFY
{
	char                                              szCharName[SZNAME_LENGTH];// ��� ĳ���� �̸�
	BYTE                                              byMode;       // �������
	BYTE												byDummy;
	short												snDummy;

} S_SCP_CONTROL_ACTION_NOTIFY, * PS_SCP_CONTROL_ACTION_NOTIFY;


// CSP_REQ_TROUBLE_REPORT : 0x2541
typedef struct _S_CSP_REQ_TROUBLE_REPORT
{
	char                                              szReport[512];// �Ű��� ����

} S_CSP_REQ_TROUBLE_REPORT, * PS_CSP_REQ_TROUBLE_REPORT;


// SCP_RESP_TROUBLE_REPORT : 0xA541
typedef struct _S_SCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwIndex;      // ������ȣ

} S_SCP_RESP_TROUBLE_REPORT, * PS_SCP_RESP_TROUBLE_REPORT;


// CSP_REQ_TROUBLE_REPORT_LIST : 0x2542
typedef struct _S_CSP_REQ_TROUBLE_REPORT_LIST
{

} S_CSP_REQ_TROUBLE_REPORT_LIST, * PS_CSP_REQ_TROUBLE_REPORT_LIST;


// SCP_RESP_TROUBLE_REPORT_LIST : 0xA542
typedef struct _S_SCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // ������ �� �Ű��� ����
	BYTE                                              byCount;      // �������� �Ű��� ����

} S_SCP_RESP_TROUBLE_REPORT_LIST, * PS_SCP_RESP_TROUBLE_REPORT_LIST;


// CSP_REQ_TROUBLE_REPORT_SET : 0x2543
typedef struct _S_CSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ

} S_CSP_REQ_TROUBLE_REPORT_SET, * PS_CSP_REQ_TROUBLE_REPORT_SET;


// SCP_RESP_TROUBLE_REPORT_SET : 0xA543
typedef struct _S_SCP_RESP_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	BYTE                                              byProceed;    // ó����Ȳ

} S_SCP_RESP_TROUBLE_REPORT_SET, * PS_SCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT_LIST : 0x2544
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_LIST
{
	int                                               nPage;        // �Ű���Ʈ ������

} S_GCSP_REQ_TROUBLE_REPORT_LIST, * PS_GCSP_REQ_TROUBLE_REPORT_LIST;


// GSCP_RESP_TROUBLE_REPORT_LIST : 0xA544
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // ������ �� �Ű��� ����
	BYTE                                              byCount;      // �������� �Ű��� ����

} S_GSCP_RESP_TROUBLE_REPORT_LIST, * PS_GSCP_RESP_TROUBLE_REPORT_LIST;


// GCSP_REQ_TROUBLE_REPORT_SET : 0x2545
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	BYTE                                              byProceed;    // ó����Ȳ
	char                                              szNote[256];  // ���

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
	int                                               nMaxHP;       // �ɸ��� HP�� �ִ밪
	int                                               nCurHP;       // �ɸ��� HP�� ���簪
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
#define GCSP_REQ_CHARACTER_SEARCH                         0x2547      // ĳ������ ���� ��û
#define GSCP_RESP_CHARACTER_SEARCH						  0xA547      // ĳ���� ��ġ����
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
	char												szCharName[SZNAME_LENGTH];// ������ ĳ���� �̸�
	char												szAccountID[ACCOUNTNAME_LENGTH];// ������ ���� ���̵�
	BYTE												byType;       // �����ϰ��� �ϴ� �Ķ���� �ʵ�
	BYTE												byDummy;
	short												snDummy;
	int													nValues;     // �����ϰ��� �ϴ� ��


} S_GCSP_REQ_PARAMETER_CHANGE, * PS_GCSP_REQ_PARAMETER_CHANGE;


// GSCP_RESP_PARAMETER_CHANGE : 0xA550
typedef struct _S_GSCP_RESP_PARAMETER_CHANGE
{
	BYTE                                              byResult;     // ���� ���� ���

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

#define _Msg_Escape			0x2601						//	/Ż����

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
	int		nCommand;			//	0:����, 1:��������
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
	BYTE	byDummy;
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
	int		nItemID;					//	�ð��� ��� ITEMID
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
//	2004.08.26(�ɷ�ġ, ��ų �ʱ�ȭ ������Ŷ)
#define		_Msg_NPCCommand				0x3005
struct		Msg_NPCCommand
{	_MSG;
	int		nNPCID;
	BYTE	byType;			//	1:��ų�ʱ�ȭ, 2:�ɷ�ġ�ʱ�ȭ, 3:2�������ʱ�ȭ, 4:��ų,��ġ�ʱ�ȭ, 5:event, ...
	BYTE	byResult;		//	0:����, 1:������, 2:����������, 3:�ʱ�ȭ�� �Ұ����� ����, 255:etc
	BYTE	byCommand;		//	1:��ȸ, 2:����, ...
	BYTE	byFirst;		//	0:ó���ƴ�, 1:ó��, ...
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
#define		_Msg_TrimuritiStatus			0x4301		//	����� db->zs �Ϲ��� ����������
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
	byte	byMode;			//	0:���������, 1:���������
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
	byte	byResult;
	byte	byDummy;
	short	snDummy;
	int		iDummy[4];
	char	pData[16];
};

//////////////////////////////////////////////////////////////////////////////////////////////
/*										ALARM SYSTEM 										*/
//////////////////////////////////////////////////////////////////////////////////////////////
#define		_Msg_Alarm						0x4601
struct		Msg_Alarm
{	_MSG
	unsigned int	unType;		//	1 : ���� ���ӻ��Ⱓ ����
};

#define		_Msg_Echo						0x4602
struct		Msg_Echo	
{	_MSG
	int		iEchoID;			//	��û echo�� ����(1:��Ȱ��ų(byData�� ȸ������ġ%���), ...)
	int		iKeyID;				//	����� keyid
	byte	byResponse;			//	��û�� ���� ����
	byte	byData;
	short	snData;
};


///////////////////////////////////////////////////////////////////
//************************** YUT SYSTEM *************************//
///////////////////////////////////////////////////////////////////

#define		_Msg_YutBet						0x4701
struct		Msg_YutBet
{
	_MSG
	byte	byResult;						//	0:����, 1:����
	byte	byPosition;						//	������ ������ �ε���
	DWORD	dwDummy;
	WORD	wCount[48];						//	���� �����Ҽ� �ִ� �ִ� �κ��丮ĭ�� ��
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

#define		_Msg_YutMoney					0x4705
//	S_REQUEST S_RESPONSE�� ����ϱ�� �Ѵ�.


///////////////////////////////////////////////////////////////////
//************************ CASTLE SYSTEM ************************//
///////////////////////////////////////////////////////////////////
#define		_Msg_GetMoney					0x4706
struct		Msg_GetMoney
{
	_MSG
	int		nType;						//	1:YutOwner, 
	DWORD	dwMoney;
	BYTE	byResult;
	BYTE	byDummy;
	short	snDumy;
};

#define		_Msg_SetSalesRate				0x4707
struct		Msg_SetSalesRate
{
	_MSG
	BYTE	byType;						//	1:����, 2:���ÿ�û
	BYTE	byRate;						//	0~100%(��������)
	short	snDummy;
	DWORD	dwMoney;					//	������ �����Ѿ�
};


//////////////////////////////////////////////////////////////////////////////////////////////
/*										MESSAGE REPLY										*/
//////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------*/
// 0x10 Group(Login & Character)
/*----------------------------------------------------------------------------*/
const BYTE REPLY_ACK_OK			= 0x00;			//	����.
const BYTE REPLY_INVALID_USER	= 0x01;			//	������ �������� ����.
const BYTE REPLY_INVALID_PASSWD	= 0x02;			//	��й�ȣ�� Ʋ��.
const BYTE REPLY_NO_RESPONSE	= 0x03;			//	���ӺҰ�(���� �������).
const BYTE REPLY_ACCOUNT		= 0x04;			//	���ӺҰ�(������, �ð����� ��) ���º�Ÿ ���� ����.
const BYTE REPLY_ALREADY_LOGIN	= 0x05;			//	�̹� �α��� �Ǿ� ����.
const BYTE REPLY_NEED_LOGIN		= 0x06;			//	�α��� ���� ���� �����.

const BYTE REPLY_GAME_MASTER	= 0x11;
const BYTE REPLY_TOOL_MASTER	= 0x12;
const BYTE REPLY_USER_FULL		= 0x13;
const BYTE REPLY_UNKNOWN		= 0xFF;

const BYTE REPLYCHARACTER_ALIVE			= 0x00;
const BYTE REPLY_CHARACTER_DISCONNECT	= 0x01;

// �ʱ�ȭ ��û�� ���� �ڵ�
const BYTE REPLY_INIT_CHAR_ERROR_FORTALID		=	0x01;
const BYTE REPLY_INIT_CHAR_ERROR_POSITION		=	0x02;
const BYTE REPLY_INIT_CHAR_ERROR_ARRANGE		=	0x03;
const BYTE REPLY_INIT_CHAR_ERROR_HANDLE			=	0x04;
const BYTE REPLY_INIT_CHAR_ERROR_GETID			=	0x05;
const BYTE REPLY_INIT_CHAR_ERROR_GETNAME		=	0x06;
const BYTE REPLY_INIT_CHAR_ERROR_CREATEAREA		=	0x07;
const BYTE REPLY_INIT_CHAR_ERROR_GETDATA		=	0x08;
const BYTE REPLY_INIT_CHAR_ERROR				=	0x09;

// ĳ���� ����
const BYTE REPLY_CHAR_CREATE_ALREADY_EXIST	= 0x01; // ĳ���� ���� ����(ĳ���� �̹� ����)
const BYTE REPLY_CHAR_CREATE_CHAR_FULL		= 0x03;	// ĳ���� ���� ����(�ɸ��Ͱ� 3�� �� ������)
//const BYTE REPLY_CHAR_CREATE_ACC_FAIL		= 0x04;	// ĳ���� ���� ����(�����̸� ���� ����)
//const BYTE REPLY_CHAR_CREATE_CHR_FAIL		= 0x05;	// ĳ���� ���� ����(ĳ�����̸� ���� ����)
const BYTE REPLY_CHAR_CREATE_CHR_CHAR_FAIL	= 0x06;	// ĳ���� ���� ����(ĳ�����̸� ������)
const BYTE REPLY_CHAR_CREATE_CHAKRA_OVER	= 0x07;	// ������ũ�����
const BYTE REPLY_CHAR_CREATE_FAIL			= 0x08;	// ĳ���� ���� ����

// ĳ���� ����
const BYTE REPLY_CHAR_REMOVE_FAIL	= 0x02;	// ĳ���� ���� ����

// ĳ���� �α׾ƿ�
const BYTE REPLY_CHAR_LOGOUT_FAIL	= 0x01;	// ĳ���� �α׾ƿ� ����(��Ż)
//const BYTE REPLY_REQ_CHAR_LOGOUT_FAIL	= 0x02;	// ĳ���� �α׾ƿ� ����(��ȯ)
const BYTE DISCONNECT_ALREADY_CONNECTED	= 0x03; // �̹� �������� ������ ���� �α׾ƿ�ó��
//	const BYTE DISCONNECT_LACK_OR_HACK		= 0x04; // �ٻ���ڿ� ���� �α׾ƿ�ó��

// �ɸ��� �α׾ƿ� �ֺ�����
const BYTE REPLY_OTHER_CHAR_LOGOUT_DISCONNECT	= 0x00;	// ĳ���� ��������
const BYTE REPLY_OTHER_CHAR_LOGOUT_PORTAL		= 0x01;	// ĳ���� ��Ż, ������ ���� �����̵�
const BYTE REPLY_OTHER_CHAR_LOGOUT_RECALL		= 0x02;	// ĳ���� ��ȯ�� ���� �����

/*----------------------------------------------------------------------------*/
// 0x11 Group(Initialize)
/*----------------------------------------------------------------------------*/
// ������ ��ġ ����
const BYTE REPLY_ITEM_POSITION_SAVE_FAIL	= 0x01;	// ������ ��ġ ���� ����

/*----------------------------------------------------------------------------*/
// 0x12 Group(Moving, Packing/Unpacking, Using)
/*----------------------------------------------------------------------------*/
// ĳ���� �̵�
const BYTE REPLY_CHAR_MOVE_FAIL				= 0x01;	// ĳ���� �̵� ����
const BYTE REPLY_CHAR_MOVE_CONFLICT_CELL	= 0x02;	// ĳ���� �̵� ����. Cell �Ӽ�
const BYTE REPLY_CHAR_MOVE_CONFLICT_PC		= 0x03;	// ĳ���� �浹
const BYTE REPLY_CHAR_MOVE_CONFLICT_NPC		= 0x04;	// Monster, NPC �浹
const BYTE REPLY_CHAR_MOVE_CONFLICT_ITEM	= 0x05;	// Item �浹
const BYTE REPLY_CHAR_MOVE_FAINT			= 0x11;	// ĳ���� ����
const BYTE REPLY_CHAR_MOVE_FLINT			= 0x12;	// ĳ���� ��ȭ
const BYTE REPLY_CHAR_MOVE_FREEZE			= 0x13;	// ĳ���� ��
const BYTE REPLY_CHAR_MOVE_SLEEP			= 0x14;	// ĳ���� ����
const BYTE REPLY_CHAR_MOVE_SEQ_ERR			= 0x21;	// �̵� ī��Ʈ ����
const BYTE REPLY_CHAR_MOVE_FAIL_SPEED		= 0x22;	// �̵� �ӵ� ����

// ������ �̵�
const BYTE REPLY_ITEM_MOVE_LAY_DISABLE		= 0x01;	// ������ �ױ� �Ұ�
const BYTE REPLY_ITEM_MOVE_INVENTORY_LACK	= 0x02;	// �κ��丮 �ڸ� ����
const BYTE REPLY_ITEM_MOVE_DISTANCE_ERR		= 0x03;	// �̵� �Ÿ� ����
const BYTE REPLY_ITEM_MOVE_PLACE_ERR		= 0x04;	// �̵� ��ġ ����
const BYTE REPLY_ITEM_MOVE_OWNER_ERR		= 0x05;	// ������ ������ ����
const BYTE REPLY_ITEM_MOVE_ROUTING_TIME		= 0x06; // ������ ���� �ð� ����
const BYTE REPLY_ITEM_MOVE_NOEXIST			= 0x07; // ������ ���� �ð� ����
const BYTE REPLY_ITEM_MOVE_BAG				= 0x08; // Ȯ���κ��� �������� ����
const BYTE REPLY_ITEM_MOVE_NOMOVE			= 0x09; // �̵��Ҽ� ���� ������
const BYTE REPLY_ITEM_MOVE_TWOHAND			= 0x0A; // ��չ��� �������
const BYTE REPLY_ITEM_MOVE_PART				= 0x0B; // �Ϻθ� ����
const BYTE REPLY_ITEM_MOVE_RIGHT			= 0x0C; // �ش� �ƽ���â������ ����Ҽ� ���� ���
const BYTE REPLY_ITEM_MOVE_ERROR			= 0xff; // �߸��� ������

// ������ ��ŷ
const BYTE REPLY_ITEM_PACKING_SOURCE		= 0x01;	// Source ������ �������� ����
const BYTE REPLY_ITEM_PACKING_DESTINATION	= 0x02;	// Destination ������ �������� ����
const BYTE REPLY_ITEM_PACKING_PLACE_ERR		= 0x03;	// ��ŷ ��� ������
const BYTE REPLY_ITEM_PACKING_OWNER_ERR		= 0x04;	// ������ ������ ����
const BYTE REPLY_ITEM_PACKING_PART_PACKING	= 0x05;	// ������ �Ϻθ� ��ŷ(���� ��ŷ ����)
const BYTE REPLY_ITEM_PACKING_NOT_PACKING	= 0x06;	// ��ŷ �Ұ��� ������
const BYTE REPLY_ITEM_PACKING_DISABLE		= 0x07;	// �� �������� ��ŷ�� �� ����
const BYTE REPLY_ITEM_PACKING_NOT_ADD		= 0x08;	// �� �������� ī��Ʈ�� ��ŷ �ѵ�(100)��.

// ������ ����ŷ
const BYTE REPLY_ITEM_UNPACKING_COUNT_ERR	= 0x01;	// ����ŷ ī��Ʈ ������
const BYTE REPLY_ITEM_UNPACKING_PLACE_ERR	= 0x02;	// ����ŷ �ڸ� ������
const BYTE REPLY_ITEM_UNPACKING_ITEM_EXIST	= 0x03; // ����ŷ �ڸ��� ������ ����
const BYTE REPLY_ITEM_UNPACKING_OWNER_ERR	= 0x04;	// ������ ������ ����
const BYTE REPLY_ITEM_UNPACKING_NOT_UNPACKING	= 0x05;	// ����ŷ �Ұ��� ������

// ������ ���
const BYTE REPLY_ITEM_USE_OWNER_ERR	= 0x01;	// ������ ������ ����
const BYTE REPLY_ITEM_USE_NOT_USE	= 0x02;	// ����� �� ���� ������
const BYTE REPLY_ITEM_USE_COUNT_ERR	= 0x03;	// ������ ī��Ʈ ����
const BYTE REPLY_ITEM_USE_RECORDED	= 0X04; // ����(��÷��) �������� ��û�Ǿ���.

// ���Ǿ��� �̵�
const BYTE REPLY_MONEY_MOVE_SAME	= 0x01;	// ������ҷ� �̵��Ұ�
const BYTE REPLY_MONEY_MOVE_LACK	= 0x02;	// ���Ǿ��� ���� ������
const BYTE REPLY_MONEY_MOVE_FAIL	= 0x03;	// ��Ÿ ������ �̵�����

// ��Ż�̵�
const BYTE REPLY_MOVE_PORTAL_OUTAREA	= 0x01;	// Ÿ�������� �̵�
const BYTE REPLY_MOVE_PORTAL_STATUS		= 0x02;	// �̵��Ҽ� ���� ����
const BYTE REPLY_MOVE_PORTAL_WANTMONEY	= 0x03;	// �̵����� ������
const BYTE REPLY_MOVE_PORTAL_WANTLEVEL	= 0x04;	// �̵��Ҽ�����
const BYTE REPLY_MOVE_PORTAL_FAIL		= 0x05;	// ��Ÿ ����

/*----------------------------------------------------------------------------*/
// 0x13 Group(Combat)
/*----------------------------------------------------------------------------*/
// ĳ���� ����
const BYTE REPLY_ATK_CHAR_DISTANCE				= 0x01;	// �Ÿ� ����
const BYTE REPLY_ATK_CHAR_NO_EQUIP				= 0x02;	// ������ ������
const BYTE REPLY_ATK_CHAR_ITEM_TYPE_ERR			= 0x03;	// ���ݰ��� �������� �ƴ�
const BYTE REPLY_ATK_CHAR_STATUS_ERR			= 0x04;	// ĳ���� ���� �Ұ� ����
const BYTE REPLY_ATK_CHAR_ITEM_OWNER			= 0x05;	// ������ ������ ����
const BYTE REPLY_ATK_CHAR_FAIL					= 0x06;	// ���� ���� ����
const BYTE REPLY_ATK_CHAR_BLOCK					= 0x07;	// �� ���� ����
const BYTE REPLY_ATK_CHAR_TARGET_ERR			= 0x08;	// ���� ��� Type ����
const BYTE REPLY_ATK_CHAR_NO_PK					= 0x09;	// PK �Ұ�
const BYTE REPLY_ATK_CHAR_USE_TIME				= 0x0A;	// ���� Ÿ�� ����
const BYTE REPLY_ATK_CHAR_NO_TARGET				= 0x0B;	// ��� ĳ���Ͱ� ����

/*----------------------------------------------------------------------------*/
// 0x14 Group(Equipment)
/*----------------------------------------------------------------------------*/
// ������ ����
const BYTE REPLY_ITEM_EQUIPMENT_TYPE_FAIL		= 0x01;	// ���� �Ұ����� ������
const BYTE REPLY_ITEM_EQUIPMENT_ALREADY_EQUIP	= 0x02;	// �������� ������ ������ġ ���� �Ұ�
const BYTE REPLY_ITEM_EQUIPMENT_POS_EQUIP_FAIL	= 0x03;	// ������ ���� ��ġ�� ���� �Ұ����� ��ġ
const BYTE REPLY_ITEM_EQUIPMENT_EXIST_POSITION	= 0x04;	// ���� ��ġ�� �ٸ� �������� ����
const BYTE REPLY_ITEM_EQUIPMENT_POS_FAIL		= 0x05;	// ���� ���� ������
const BYTE REPLY_ITEM_EQUIPMENT_TWOHAND			= 0x06;	// ��� ���� ���� �Ұ���
const BYTE REPLY_ITEM_EQUIPMENT_TRIMURITI		= 0x07;	// �ֽ� ����
const BYTE REPLY_ITEM_EQUIPMENT_TRIBE			= 0x08;	// ���� ����
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_MUSCL	= 0x09;	// ������ ��ũ�� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_NERVE	= 0x0A;	// �Ű��� ��ũ�� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_HEART	= 0x0B;	// ������ ��ũ�� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA_SOUL		= 0x0C;	// ������ ��ũ�� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_CHAKRA			= 0x0D;	// ��ũ�� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_BRAHMAN			= 0x0E;	// ��� ����Ʈ ����
const BYTE REPLY_ITEM_EQUIPMENT_JOBSKILL		= 0x0F;	// ���� ��� ����
const BYTE REPLY_ITEM_EQUIPMENT_DISTANCE		= 0x10;	// �����۰� ĳ���� �Ÿ�����
const BYTE REPLY_ITEM_EQUIPMENT_OWNER			= 0x11;	// ������ ������ ����

/*----------------------------------------------------------------------------*/
// 0x15 Group(Chatting)
/*----------------------------------------------------------------------------*/
// �Ϲ� ä��
const BYTE REPLY_NORMAL_CHAT_FAIL	= 0x01;	// �Ϲ�ä�� ����

/*----------------------------------------------------------------------------*/
// 0x16 Group(Party)
/*----------------------------------------------------------------------------*/
// ��Ƽ ���� ��û
const BYTE REPLY_OTHER_JOIN_PARTY	= 0x01;	// �̹� �ٸ� ��Ƽ�� ���� ��
const BYTE REPLY_REPEAT_PARTY_NAME	= 0x02; // ��Ƽ �̸� �ߺ�
const BYTE REPLY_CREATE_PARTY_FAIL	= 0x03; // ��Ƽ ���� ����

// ��Ƽ ��ü 
const BYTE REPLY_DISBAND_LOGOUT_MASTER		= 0x01; // ��Ƽ���� �α׾ƿ� ��.
const BYTE REPLY_DISBAND_PARTY_FAIL			= 0x02;	// ��Ƽ ��ü ����
const BYTE REPLY_DISBAND_PARTY_NOT_MASTER	= 0x03; // ��Ƽ���� �ƴ�, ���� ��Ƽ�� ����.
const BYTE REPLY_DISBAND_PARTY_NAME_ERROR	= 0x04; // ��Ƽ �̸��� �߸�����.
const BYTE REPLY_DISBAND_PARTY_SYSTEM_ERROR = 0xFF;	// �ý��� ����...

// ��Ƽ ����
const BYTE REPLY_PARTY_JOIN_DIS			= 0x01; // ��Ƽ ���� ���� - �Ÿ� ����
const BYTE REPLY_PARTY_JOIN_PARTY		= 0x02; // �ٸ� ��Ƽ�� ������
const BYTE REPLY_PARTY_JOIN_NCONNECT	= 0x03; // ��Ƽ ���� ���� - ���� ������
const BYTE REPLY_PARTY_JOIN_FULL		= 0x04;	// ��Ƽ �ο��� �ʰ�
const BYTE REPLY_PARTY_JOIN_NMASTER		= 0x05;	// ��Ƽ���� �ƴ�.
const BYTE REPLY_PARTY_ALREADY_MEMBER	= 0x06; // ��Ƽ�� ������.
const BYTE REPLY_PARTY_JOIN_CAST		= 0x07; // ��Ƽ���� ����� �� ����.

const BYTE REQ_JOIN_PARTY_OK			= 0x00;	// ��Ƽ ���� ����
const BYTE REQ_JOIN_PARTY_REJECT		= 0x01;	// ��Ƽ ���� ����

const BYTE REPLY_SECEDE_PARTY_SUCC		= 0x00; // ��Ƽ Ż�� ����
const BYTE REPLY_SECEDE_PARTY_NMASTER	= 0x01; // ��Ƽ�忡 ���� Ż��
const BYTE REPLY_SECEDE_PARTY_LOGOUT	= 0x02; // ��Ƽ���� �α׾ƿ� ��

// �ּҷ� ����
const BYTE REPLY_ACCEPT_ADDRESS			= 0x00; // �ּҷ� �߰� ��û ����
const BYTE REPLY_REJECT_ADDRESS			= 0x01; // �ּҷ� �߰� ��û ����

const BYTE REPLY_ADDRBOOK_LOGOUT		= 0x00; // �ּҷ� ����� �α׾ƿ�
const BYTE REPLY_ADDRBOOK_ZONE_MOVE		= 0x01; // �ּҷ� ����� �� �̵�

const BYTE REPLY_ADDRESS_JOIN_DISTANCE	=	0x01;	//	�Ÿ����� ����
const BYTE REPLY_ADDRESS_JOIN_CONNECT	=	0x02;	//	������ ���� ���� ����
const BYTE REPLY_ADDRESS_JOIN_ALREADY	=	0x03;	//	�̹� ������ ��� ����

//	GUILD
const BYTE REPLY_CLIENT_CONNECT			= 0x00; // ���� ������
const BYTE REPLY_CLIENT_DISCONNECT		= 0x01; // ���� ��������

const BYTE REPLY_GUILDMARK_PARAM		= 0x01;
const BYTE REPLY_GUILDMARK_RIGHT		= 0x02;
const BYTE REPLY_GUILDMARK_MONEY		= 0x03;

/*----------------------------------------------------------------------------*/
// 0x19 Group(Parameter)
/*----------------------------------------------------------------------------*/
// ��ũ�� ��� ��û
const BYTE REPLY_CHAKRA_RISING_PRANA	= 0x01;	// ���� ����
const BYTE REPLY_CHAKRA_RISING_CHAKRA	= 0x02;	// ��ũ�� ����(���̻� ���ø�)
const BYTE REPLY_CHAKRA_RISING_DISTANCE	= 0x03;	// �Ÿ� ����

// ��� ����Ʈ ��� ��û
const BYTE REPLY_BRAHMAN_RISING_PRANA		= 0x01;	// ���� ����
const BYTE REPLY_BRAHMAN_RISING_BRAHMAN		= 0x02;	// ��� ����Ʈ ����(���̻� ���ø�)
const BYTE REPLY_BRAHMAN_RISING_DISTANCE	= 0x03;	// �Ÿ� ����

// �κ��丮 ���� ���� ��û
const BYTE REPLY_INCREASE_INVENTORY_SLOT_MAX_COUNT	= 0x01;	// �κ��丮 �ִ� ���� �ʰ�
const BYTE REPLY_INCREASE_INVENTORY_SLOT_ITEM		= 0x02;	// �κ��丮 ���� �������� ����

// NPC ģ�е� ��� ��û
const BYTE REPLY_NPC_POINT_UP_TYPE_ERR	= 0x01;	// NPC ���� ����
const BYTE REPLY_NPC_POINT_UP_2MORE		= 0x02;	// �Ϸ翡 2���̻� ��� ��û��

// ��ũ�� ���󳪷� ��ȯ
const BYTE REPLY_CHANGE_CHAKRA_TO_PRANA_ERR		= 0x01;	// ��ȯ����
const BYTE REPLY_CHANGE_CHAKRA_TO_PRANA_EQUIP	= 0x02;	// ��ȯ����(������ ������)

/*----------------------------------------------------------------------------*/
// 0x20 Group(Skill)
/*----------------------------------------------------------------------------*/
// ��ų ��� ��û
const BYTE REPLY_SKILL_REGIST_EXIST			= 0x01;	// �̹� �����ϴ� ��ų��
const BYTE REPLY_SKILL_REGIST_INDEX_ERR		= 0x03;	// �ε��� ����
const BYTE REPLY_SKILL_REGIST_TYPE_ERR		= 0x04;	// Ÿ�� ����
const BYTE REPLY_SKILL_REGIST_ERROR			= 0x05;	// ��ų ��� ����

// ��ų ����/����/����
const BYTE REPLY_SKILL_SELECT_HAVE_NO_SKILL	= 0x01;	// �ش� ��ų ����
const BYTE REPLY_SKILL_SELECT_HAND_ERROR	= 0x02;	// ��ų ���� ���� ����
const BYTE REPLY_SKILL_SELECT_PASSIVE		= 0x03;	// ����/����/���� �Ұ� ��ų(�нú� ��ų)
const BYTE REPLY_SKILL_SELECT_RESELECT		= 0x04;	// �̹� ���õǾ� ����
const BYTE REPLY_SKILL_DELETE_NOT_FREE_SKILL= 0x05; // Free Skill�� �ƴ�(��ų ������)
const BYTE REPLY_SKILL_DELETE_HAVE_NO_SKILL	= 0x06;	// �ش� ��ų ����(��ų ������)
const BYTE REPLY_SKILL_DELETE_RESELECT		= 0x07;	// �̹� ���õǾ� ����(��ų ������)
const BYTE REPLY_SKILL_DELETE_SUCC			= 0x08; // ��ų���� ����

// ��ų �غ��� ��û
const BYTE REPLY_SKILL_USE2_CHAR_DISABLE			= 0x01;	// ĳ���� ���ݺҰ� ����
const BYTE REPLY_SKILL_USE2_CHAR_DISTANCE			= 0x02;	// ĳ���� �Ÿ�����
const BYTE REPLY_SKILL_USE2_CHAR_HAVE_NO_SKILL		= 0x03;	// ��ų�� ����
const BYTE REPLY_SKILL_USE2_CHAR_NO_SELECT_SKILL	= 0x04;	// ���õ� ��ų�� �ƴ�
const BYTE REPLY_SKILL_USE2_CHAR_REQ_PRANA			= 0x05;	// ��ų ��� �䱸 ���� ����
const BYTE REPLY_SKILL_USE2_CHAR_ITEM_TYPE			= 0x06;	// ������ Ÿ�� ����
const BYTE REPLY_SKILL_USE2_CHAR_ITEM_INDEX			= 0x07;	// ������ �ε��� ����
const BYTE REPLY_SKILL_USE2_CHAR_SKILL_INDEX		= 0x08;	// Ư�� ��ų �ε��� ����
const BYTE REPLY_SKILL_USE2_CHAR_HAVE_NO_ITEM		= 0x09;	// ������ �������� ����
const BYTE REPLY_SKILL_USE2_CHAR_NO_TARGET			= 0x0A;	// ��� ĳ���Ͱ� ����
const BYTE REPLY_SKILL_USE2_CHAR_NO_PK				= 0x0B;	// PK �Ұ� ����
const BYTE REPLY_SKILL_USE2_CHAR_TARGET_ERR			= 0x0C;	// ��� Ÿ�� ����

// ��ų ����
const BYTE REPLY_SKILL_ATK_CHAR_DISABLE				= 0x01;	// ĳ���� ���ݺҰ� ����
const BYTE REPLY_SKILL_ATK_CHAR_DISTANCE			= 0x02;	// ĳ���� �Ÿ�����
const BYTE REPLY_SKILL_ATK_CHAR_HAVE_NO_SKILL		= 0x03;	// ��ų�� ����
const BYTE REPLY_SKILL_ATK_CHAR_NO_SELECT_SKILL		= 0x04;	// ���õ� ��ų�� �ƴ�
const BYTE REPLY_SKILL_ATK_CHAR_REQ_PRANA			= 0x05;	// ��ų ��� �䱸 ���� ����
const BYTE REPLY_SKILL_ATK_CHAR_ITEM_TYPE			= 0x06;	// ������ Ÿ�� ����
const BYTE REPLY_SKILL_ATK_CHAR_ITEM_INDEX			= 0x07;	// ������ �ε��� ����
const BYTE REPLY_SKILL_ATK_CHAR_SKILL_INDEX			= 0x08;	// Ư�� ��ų �ε��� ����
const BYTE REPLY_SKILL_ATK_CHAR_HAVE_NO_ITEM		= 0x09;	// ������ �������� ����
const BYTE REPLY_SKILL_ATK_CHAR_NO_TARGET			= 0x0A;	// ��� ĳ���Ͱ� ����
const BYTE REPLY_SKILL_ATK_CHAR_FAIL				= 0x0B;	// ���� ���� ����
const BYTE REPLY_SKILL_ATK_CHAR_BLOCK				= 0x0C;	// �� ���� ����
const BYTE REPLY_SKILL_ATK_CHAR_NO_PK				= 0x0D;	// PK �Ұ� ����
const BYTE REPLY_SKILL_ATK_CHAR_TAGET_ERR			= 0x0E;	// ��� Ÿ�� ����
const BYTE REPLY_SKILL_ATK_CHAR_USE_TIME			= 0x0F;	// ��ų ��� �ð� ����


// ��ų Level-Up ��û
const BYTE REPLY_SKILL_LEVEL_UP_MAX_LEVEL			= 0x01;	// ��ų �ִ� ���� - ���̻� ���� �ø� �� ����
const BYTE REPLY_SKILL_LEVEL_UP_PRANA				= 0x02;	// ���� ����
const BYTE REPLY_SKILL_LEVEL_UP_HAVE_NO_SKILL		= 0x03;	// �ش� ��ų�� ����
const BYTE REPLY_SKILL_LEVEL_UP_DATA_MIS			= 0x04; // ������ ����Ÿ�� �������� ����

// �ֽ� ���� ��û ���
const BYTE REPLY_TRIMURITI_CHANGE_PRANA_LACK		= 0x01;	// ���� ����
const BYTE REPLY_TRIMURITI_CHANGE_SAME_TRIMURITI	= 0x02; // �Ȱ��� �ֽź����� �Ϸ���
const BYTE REPLY_TRIMURITI_CHANGE_FAILED			= 0x03; // �ֽ� ���� ����

// �Ӹ����� ���
const BYTE REPLY_WHISPER_CHAR_FAIL					= 0x01;	// �Ӹ����� ����
const BYTE REPLY_WHISPER_REJECT						= 0x02;

// ��ȯ �۾� ���� �� ErrorCode
const BYTE REPLY_TRADE_SUCCESS			= 0x00;		//	�������� �ŷ��� �Ϸ�
const BYTE REPLY_TRADE_USER_DENAY		= 0x01;		//	��밡 �ŷ��� ����� ���
const BYTE REPLY_TRADE_OVER_ME			= 0x02;		//	MY �κ��� �ڸ��� ���ڶ�
const BYTE REPLY_TRADE_OVER_YOU			= 0x03;		//	YOUR �κ��� �ڸ��� ���ڶ�
const BYTE REPLY_TRADE_OUTINDEX			= 0x04;		//	������ �ε��� ����
const BYTE REPLY_TRADE_USER_DIE			= 0x05;		//	����������� ���� �ŷ� ���
const BYTE REPLY_TRADE_USER_CHANGE		= 0x06;		//	����������� ���� �ŷ� ���
const BYTE REPLY_TRADE_ERROR			= 0x09;		//	��Ÿ ����

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// ���ۼ� ����
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// ���� ����
const BYTE REPLY_ITEM_CREATE_NOT_EXIST			=	-1;
const BYTE REPLY_ITEM_CREATE_CANNOT				=	-1;

//������ ���� ��û �� ��� �ڵ�
const BYTE REPLY_ITEM_BUY_GOLD_WANT				=	0x01;
const BYTE REPLY_ITEM_BUY_SUB_WANT				=	0x03;
const BYTE REPLY_ITEM_BUY_INVENTORY_LACK		=	0x04;
const BYTE REPLY_ITEM_BUY_MINCOUNT				=	0x05;

// ������ ���� ��û �� ��� �ڵ�
const BYTE REPLY_ITEM_REPAIR_MONEY_WANT			=	0x01;
const BYTE REPLY_ITEM_REPAIR_OUTINDEX			=   0x02;
const BYTE REPLY_ITEM_REPAIR_ENOUGH				=	0x03;
const BYTE REPLY_ITEM_REPAIR_RESERVED			=	0x04;

// ������ ��ü ��û �� ��� �ڵ�
const BYTE REPLY_ITEM_SELL_INVENTORY_LACK		=	0x01;
const BYTE REPLY_ITEM_SELL_NO_INVENTORY			=	0x02;
const BYTE REPLY_ITEM_SELL_RESERVED				=	0x03;
const BYTE REPLY_ITEM_SELL_OUTINDEX				=	0x04;

// ������ ���� ��û �� ��� �ڵ�
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

//	������ �峳����
const BYTE REPLY_ITEM_CONTRIBUTION_OUTINDEX		=	0x01;
const BYTE REPLY_ITEM_CONTRIBUTION_OUTPARAM		=	0x02;
const BYTE REPLY_ITEM_CONTRIBUTION_CANNOT		=   0x03;
const BYTE REPLY_ITEM_CONTRIBUTION_LACK			=   0x04;
const BYTE REPLY_ITEM_CONTRIBUTION_EVENT		=	0x05;

// ������ ����Ʈ ��� �ڵ�byRefineLevel = 0byRefineLevel = 0
const BYTE REPLY_ITEM_LISTING_FAILED			=	0x01;

// ��ȯ�� ��� �ڵ�
const BYTE REPLY_BARTER_DISTANCE				=	0x01;	
const BYTE REPLY_BARTER_SOURCE_LACK				=	0x02;
const BYTE REPLY_BARTER_INVENTORY_LACK			=	0x03;
const BYTE REPLY_BARTER_NPC_DISABLE				=	0x04;
const BYTE REPLY_BARTER_DISABLE					=	0x05;

// �κ��丮 Ȯ�� ���� ��� �ڵ�
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

//	GM ����
const BYTE REPLY_GMMOVE_OTHER					= 0x01;	//  Ÿ������ ���� ��û
const BYTE REPLY_GMMOVE_UNMOVE					= 0x02;	//	�̵� �Ұ�����
const BYTE REPLY_GMMOVE_DISCONNECT				= 0x03;	//	�ɸ��� ������
const BYTE REPLY_GMMOVE_UNKNOWN					= 0x04;	//	���� ����

const BYTE REPLY_GMCHAT_BIT						= 0x01;
const BYTE REPLY_GMACTION_BIT					= 0x02;
const BYTE REPLY_GMTRANSPARENCY_BIT				= 0x03;

const BYTE REPLY_GMMODE_FAIL					= 0x01;

const BYTE REPLY_GMCLOSE_CHARACTER_FAIL			= 0x01;
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

const BYTE REPLY_DISCONNECT_GMALREADY_CONNECTED			= 0x03;
const BYTE REPLY_DISCONNECT_GMLACK_OR_HACK				= 0x04;
const BYTE REPLY_DISCONNECT_GM_ORDERD					= 0x05;

//	�̺�Ʈ ������ ������ ���� �÷���(EVENT_20030701)
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
const BYTE REPLY_COUPONEVENT_0ST				= 0x00;		//	��
const BYTE REPLY_COUPONEVENT_1ST				= 0x01;		//	1��(InGame)
const BYTE REPLY_COUPONEVENT_2ST				= 0x02;		//	2��(InGame)
const BYTE REPLY_COUPONEVENT_3ST				= 0x03;		//	3��(InGame)
const BYTE REPLY_COUPONEVENT_4ST				= 0x04;		//	4��(InGame)
const BYTE REPLY_COUPONEVENT_5ST				= 0x05;		//	5��(InGame)
const BYTE REPLY_COUPONEVENT_6ST				= 0x06;		//	6��(InGame)
const BYTE REPLY_COUPONEVENT_7ST				= 0x07;		//	��ȭ������
const BYTE REPLY_COUPONEVENT_8ST				= 0x08;		//	�׷���ī��
const BYTE REPLY_COUPONEVENT_9ST				= 0x09;		//	Ÿ��ƫ��
const BYTE REPLY_COUPONEVENT_10ST				= 0x0A;		//	���������
const BYTE REPLY_COUPONEVENT_LACK				= 0x11;		//	��������
const BYTE REPLY_COUPONEVENT_ERROR				= 0x12;		//	�˼����� ����
const BYTE REPLY_COUPONEVENT_UNKNOWN			= 0x13;		//	�˼����� ����

//	Gemble
const BYTE REPLY_YUTMONEY_SUCCESS				= 0x00;		//	����
const BYTE REPLY_YUTMONEY_INVENFULL				= 0x01;		//	�κ��丮�� �ڸ��� ���ݵ� ����
const BYTE REPLY_YUTMONEY_PART					= 0x02;		//	�Ժ��丮�� Ǯ�̶� ���ݸ� ���� ã���� ���
const BYTE REPLY_YUTMONEY_NOHAVEMONEY			= 0x03;		//	ã�� ���� ���� ���
const BYTE REPLY_YUTMONEY_FAIL					= 0x04;		//	��Ÿ ���� ã���� ���� ���


/*********************************************/
//	2004.08.26(�ɷ�ġ, ��ų �ʱ�ȭ ������Ŷ)
const BYTE REPLY_NPCCOMMAND_LACK				= 0x01;		//	���Ǿư� �����Ұ��
const BYTE REPLY_NPCCOMMAND_EQUIP				= 0x02;		//	�������� �����Ѱ��
const BYTE REPLY_NPCCOMMAND_STATUS				= 0x03;		//	�ʱ�ȭ�� �Ұ����� ����
/*********************************************/

#endif