// ��Ʈ�ο����� ����
enum 
{ 
	GAMESEQUENCE_INTRO_INIT						= 100,
	GAMESEQUENCE_INTRO_AFTERINIT				= 101,	
	GAMESEQUENCE_INTRO_LOGSERVERCONNECT			= 102,	
	GAMESEQUENCE_INTRO_LOGIN					= 103,
	GAMESEQUENCE_INTRO_SELECTWORLD				= 104,
	GAMESEQUENCE_INTRO_CHAR_SELECT				= 105,
	GAMESEQUENCE_INTRO_NEW_CHAR					= 106,
	GAMESEQUENCE_INTRO_RETURNCOMPLETE			= 107,
};

// ���̾˷α� ��ȣ
enum
{
	_INTRO_DIALOG_NOTIFY						= 0,
	_INTRO_DIALOG_START							= 1,
	_INTRO_DIALOG_LOGIN							= 2,
	_INTRO_DIALOG_SERVERSELECT					= 3,
	_INTRO_DIALOG_BUTTONDIALOG					= 4,
	_INTRO_DIALOG_NEWCHAR						= 5,
	_INTRO_DIALOG_CHARINFO						= 6,
	_INTRO_DIALOG_CREDITNUMBER					= 7,
	_INTRO_DIALOG_MANDARASERVER					= 8,
	//_INTRO_DIALOG_CREATEZONE					= 8,
	//_INTRO_DIALOG_CONFIRMATION					= 9,
	
};

// ���̾˷α� ��ȣ
enum
{
	_INTRO_START_POS_X							= 310,
	_INTRO_START_POS_Y							= 680,

	//_INTRO_SERVERSELECT_POS_X					= 330,
	//_INTRO_SERVERSELECT_POS_Y					= 308,

	_INTRO_BTNDLG_POS_X							= 784,
	_INTRO_BTNDLG_POS_Y							= 638,

	_INTRO_MANDARASERVER_POS_X					= 257,
	_INTRO_MANDARASERVER_POS_Y					= 479,
};


// Ŀ��
enum
{
	_INTRO_CURSOR_ARROW,
	_INTRO_CURSOR_KEYBOARD,
};


// ����� �޼���
enum
{
	_USER_MESSAGE_CANCEL		= 0,
	_USER_MESSAGE_OK			= 1,
	_USER_MESSAGE_LOGIN			= 2,
	_USER_MESSAGE_END			= 3,
	_USER_MESSAGE_DELETE		= 4,
	_USER_MESSAGE_NEWCHAR		= 11,
	_USER_MESSAGE_CHARSELECT	= 12,
	_USER_MESSAGE_EXIT			= 13,
	_USER_MESSAGE_TRIBELEFT		= 111,
	_USER_MESSAGE_TRIBERIGHT	= 112,
	_USER_MESSAGE_CREATECHAR	= 10,
	_USER_MESSAGE_STARTMANDARA	= 31,
	_USER_MESSAGE_STARTFINAL	= 32,
};

enum
{
	_EDIT_BACK_MESSAGE		= 0,
	_EDIT_LOGIN_ID			= 0,
	_EDIT_LOGIN_PASSWORD	= 1,

	_EDIT_CHARSELECT_NAME1	= 0,	
	_EDIT_CHARSELECT_NAME2	= 1,
	_EDIT_CHARSELECT_NAME3	= 2,

	_EDIT_CHARINFO_TRIBE	= 0,
	_EDIT_CHARINFO_GOD		= 1,
	_EDIT_CHARINFO_CAST		= 2,
	_EDIT_CHARINFO_CHACRA	= 3,
	_EDIT_CHARINFO_BRAHMAN	= 4,
};

enum
{
	_RADIOGROUP_SERVER_LIST		= 0,
	_RADIOGROUP_CHARSEL1		= 0,
	_RADIOGROUP_CHARSEL2		= 1,
};

//const HTtchar _TRIBE_TABLE[8][13] = { "����", "�Ƽ���", "��ũ��", "����", "Ų����", "��ũ����", "���ٸ���", "�����" };
//const HTtchar _TRIBE_EDIT_KOR[8][13] = { "( ���� )", "( Ŵ���� )", "( �Ƽ��� )", "( ��ũ���� )", "( ��ũ�� )", "( ���ٸ��� )", "( ���� )", "( ����� )" };
//const HTtchar _TRIBE_EDIT_ENG[8][13] = { "Naga", "Kimnara", "Asura", "Rakshasa", "Yaksa", "Gandarva", "Deva", "Garuda" };

//const HTtchar _CAST_TABLE[5][13] = { "�����", "���̻�", "ũ��Ʈ����", "���", "�ƹ�Ÿ��" };
//const HTtchar _TRIMURITI_TABLE[3][13] = { "����帶", "�񽴴�", "�ù�" };
//---------------------------------------------------------------------------
// �˸��޽��� ���� 
//---------------------------------------------------------------------------
enum
{
	_MSG_IDPASSWORD_INPUTLOGIN			= 0,
	_MSG_LOGIN							= 1,
	_MSG_LOGIN_OK						= 2,
	_MSG_LOGOUT							= 3,
	_MSG_MOVETOZONE						= 4,
	_MSG_WORLDLIST						= 5,
	_MSG_ZONE_CONNECTING				= 6,

	_MSG_NUM							= 7,
};

//const HTtchar _MESSAGE_TABLE[_MSG_NUM][256] = 
//{ 
//	"ID�� PASSWORD�� �Է��Ͻʽÿ�.", 
//	"�α��� ���Դϴ�.",
//	"�α��� �Ǿ����ϴ�.",
//	"�α׾ƿ� �Ǿ����ϴ�.",
//	"�������� ������ ��û�մϴ�.",
//	"���忡 ���� ���� ����Ʈ�� �޾ҽ��ϴ�.",
//	"�������� �������Դϴ�.",
//};	



//---------------------------------------------------------------------------
// �����޽��� ���� 
//---------------------------------------------------------------------------
enum
{
	_ERROR_MSG_LOGIN			= 0,	
	_ERROR_MSG_USERID			= 1,	
	_ERROR_MSG_PASSWORD			= 2,
	_ERROR_MSG_SERVERREPLY		= 3,
	_ERROR_MSG_CONNECTFEE		= 4,
	_ERROR_MSG_REUSER			= 5,
	_ERROR_MSG_USETIME			= 6,
	_ERROR_MSG_SERVERCONNECT	= 7,
	_ERROR_MSG_NETWORK			= 8,	

	_ERROR_MSG_NUM				= 9,
};

//const HTtchar _ERROR_MESSAGE_TABLE[_ERROR_MSG_NUM][256] = 
//{ 	
//	"�α��ο� �����Ͽ����ϴ�. �ٽ� �õ��� �ֽñ� �ٶ��ϴ�.",
//	"����� ���̵� �����Դϴ�.",
//	"�н����� �����Դϴ�.",
//	"�������� ������ �����ϴ�.",
//	"������� ��� �����Դϴ�.",
//	"�� ����� �����Դϴ�.",
//	"���ð� �����Դϴ�.",
//	"�������� �����Դϴ�.",
//	"��Ʈ��ũ �����Դϴ�.",
//};

enum
{
	_CHARSEL_NAME				= 0,
	_CHARSEL_TRIBE				= 1,
	_CHARSEL_GOD				= 2,
	_CHARSEL_CAST				= 3,
	_CHARSEL_MUSCLE				= 4,
	_CHARSEL_NERVE				= 5,
	_CHARSEL_HEART				= 6,
	_CHARSEL_SPIRIT				= 7,
	_CHARSEL_CREATEZONE			= 8,
	_CHARSEL_CHAKRA				= 9,
};

//enum
//{
//	_NEWCHAR_BRAHMA				= 0,
//	_NEWCHAR_VISHUNU			= 1,
//	_NEWCHAR_SIVA				= 2,
//};
//
//enum
//{
//	_NEWCHAR_GROUP_FACE			= 0,
//	_NEWCHAR_GROUP_GOD			= 1,
//};
#define _MAGARA_BTN_START	2
#define _MAGARA_BTN_NUM		70

#define _LOGIN_NAME			0
#define _LOGIN_PASSWORD		1

#define _NOTIFY_TITLE			0
#define _NOTIFY_DATE			1
#define _NOTIFY_MSG_SLIDEUP		201
#define _NOTIFY_MSG_SLIDEDOWN	202

#define _TRIBE_EXPLAIN_START			1
#define _TRIBE_NUM				8
#define _TRIBE_NAME				6

#define _SERVER_PING_START		2
#define _SERVER_PING_NUM		10

#define _CHAKRA_INIT		301