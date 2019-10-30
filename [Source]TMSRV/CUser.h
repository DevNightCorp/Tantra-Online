#ifndef _CUSER_
#define _CUSER_
#include <windows.h>

#include "Basedef.h"
#include "CPSock.h"
#include "CMob.h"



// �⺻������ MOB ������ ���� ��쿡��, Ŭ���̾�Ʈ Ŀ�ؼ� �ν�Ʈ�� LOGIN �÷��׸� �������ָ� �ȴ�.
// MOB������ �ִ� ��쿡�� SAVING4QUIT ���·� ������, MOB_SAVE�� ��û�Ѵ�. 
// MOB_SAVE�� CNF���� SAVING4QUIT�� EMPTY�� �ٲ۴�.



//----------------------------------------------------------------------------------------------------------
#define USER_EMPTY       0   // ����ִ�.
#define USER_ACCEPT      1   // ACCEPT ���Ļ���. CloseUser���� �������� �ʴ´�.
#define USER_LOGIN       2   // DB������ ID,PASS�� �ѱ�� ��ٸ�����. CloseUser���� �������� �ʴ´�. 
                             // CloseUser�� DB���������� ���°�� ó������ �ʴ´�. 
                             // CloseUser�� ���� DB�� SaveUser�� �ƴ� Login flag�� reset ��Ų��.
//-------��ī��Ʈ �α��� �ߴ°�----------------------------------------------------------------------------
#define USER_SELCHAR     11   // DB������ ĳ���� �߿��� ����� ���� ���� ��.
#define USER_CHARWAIT    12   // DB�������� ĳ���� ������ �о� ������ 
#define USER_CREWAIT     13   // CreateCharactor��û���� �̻��¿��� Login�� �Ұ��ϴ�.
#define USER_DELWAIT     14   // DB�������� ĳ���� ������ �о� ������ 

//-------���Ӽ����� MOB�����Ͱ� �ִ°�----------------------------------------------------------------------
#define USER_PLAY        22   // DB������ ������ ä����, ����� ������ �ʵ尡 ��ȿ�� ����.
#define USER_SAVING4QUIT 24   // ������ �̹� ���� �Ǿ���, SAVEUSER�� DB������ ������  CNF�� EMPTY�� �ٲ۴�. Sock�� NULL�̴�.
//#define USER_RECONNECT   24   // �̹� �������϶�, ���� ������ ���� ����Ǳ⸦ ��ٸ��� ����. CloseUser���� �������� �ʴ´�.



// A�� �������̰� BCD�� ���ÿ� ���� ������ ��û�ߴ�.

// B�� ��û���� DB������ A�� ������ ������ �䱸�Ѵ�. �̶� ���Ӽ����� Ŭ���̾�Ʈ�� ���� ������.
// C�� ��û���� DB������ A�� ������ ������ �䱸�Ѵ�. �̶� ���Ӽ����� Ŭ���̾�Ʈ�� ���� ������.
// D�� ��û���� DB������ A�� ������ ������ �䱸�Ѵ�. �̶� ���Ӽ����� Ŭ���̾�Ʈ�� ���� ������.
// �̶� ���Ӽ����� USER_SELCHAR ������ AccountName�� ä���� �־ ��ȿ�� Account�� ���� �ʴ´�.
// A�� ���� ���Ӽ����� A�� ������ü A�� �������� ��û�� DB������ ������.
// DB������ A�� ������ ������ �䱸��ü ��ٸ��� ��� �� ���� ��û�� ���� ���� �޽����� �ٽ� ������.
// (A�� ���� ������ �޽����� �Ծ� �������� �ֱ� ����)
// B�� 4�� �������� 3ȸ ���� �����ϱ⸦ �õ��Ѵ�. ->  Client�� Ư�� ��忡�� Sock�� NULL�� ��� ī��Ʈ �ϸ�
// �õ��� �ݺ��ϴ� 3ȸ ���н� "�����ڰ� ����, �����Ҽ� �����ϴ�. �����Ŀ� �ٽ� �õ��� �ּ���"�� ����.
// �� ��õ��� ��¯ ���� BCD�� �ϳ��� �Դ´�.
// DB ������ �������� ���� �޽����� ���� "�ٸ������� �α����Ͽ� ����ϴ�"�� Ŭ���̾�Ʈ���� ������ 
// DB������ ���� ���Ӽ������� ������ Quit�� ������ CNF�� �ö����� ������ ���·� ����.
// ���Ӽ����� USER_LOGIN ���°� DB������ LOGIN flag�� SET�� ��� �� ������ ����.
// (DB������ LOGIN FLAG�� SET�ϴ� ���ÿ� ���Ӽ����� LOGIN_OK�� ������ �����̴�.) 
// Ŭ���̾�Ʈ�� 3ȸ�� ���û �߰��� SELCHAR�� ���ڸ���, �ٸ������� �α��� �Ǿ ����ϴٸ� �ްԵȴ�.
// (DB������ ���û �޽����� �׻� GAME������ ���� ������� ó���ȴ�)
// 

   


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//                  USERFILE
//
// ID
// PASS
// ��Ÿ ��������
// ��������
// MOB Index
// 
// MOB1    // 1 K //
// MOB2    // 1 K //
// MOB3    // 1 K //
// MOB4    // 1 K //
// MOB5    // 1 K //
// MOB6    // 1 K //
//
//            total : 8K
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


class CUser
{

	public:
	// Saved part
	// ��ī��Ʈ�� ������ �ߺ� üũ�� �Ѵ�
	// ĳ���� ������ ���ۺκ�
    char AccountName[ACCOUNTNAME_LENGTH];
	///////
	int				Slot;                  // DB������ ���° MOB����.
	int				IP;
	char			pIP[18];
	// Temporary part
	int				Mode;
	int				TradeMode;		//	��ȯ
	BYTE			byTradeMode;	//	���λ�ŷ�
    CPSock			cSock;
	STRUCT_ITEM		Cargo[MAX_CARGO];
	int				Coin;
    MSG_Trade		Trade;
	unsigned int	LastAttack;
	unsigned int	LastAttackTick; 
	unsigned int	LastMove;
	unsigned int	LastAction;
	unsigned int	LastActionTick;
	unsigned int	NumError;  // CNFCharacterLoing�� �ʱ�ȭ�Ǹ� Server�� Sync�� ���� ���� ��� Increment. nȸ(30����) �̻��̸� �α׸� ����� CloseConnection.
	int				Billing;   // 0:�Ƿ���-��ñ�ٷ� �ּ���.  1:�Ƿ���-��ñ�ٷ� �ּ���.  2:���-   3:�������-��  4:�������-����.  5:��Ÿ���� (���)
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];
	char			LastChat[SZNAME_LENGTH];
	int				IsBillConnect;     // ���������� �α��� �޽����� �������.
	char			User_Status[4];
	char			Session[32];
	char			szTrade[SZTRADE_LENGTH];
	int				LastX,LastY;
    int				PKMode;
	int				ReqHp;
	int				ReqMp;
	int				bQuaff;
	unsigned int	Mac[4];
	unsigned int	LastReceiveTime;
	time_t			LoginTime;
	int				Admin;
	int				Child;
	unsigned int	ReqBillSec;
	unsigned int	CharLoginTime;
// Functions
   public:
   	CUser();
	~CUser();
	BOOL			AcceptUser ( int ListenSocket);
    BOOL			CloseUser  ( void );
    void			Remove     ( void );
	unsigned int	LastSkillTick[MAX_CLASS*MAX_SKILL];
	int				nGuildIndex;
	int				nGuildLevel;
	char			InviteName[SZNAME_LENGTH];
	char			InviteMessengerName[SZNAME_LENGTH];
	int				nInviteMessengerSlot;
	STRUCT_MESSENGER_ITEM Item[MAX_MESSENGER];		//	Messenger List

	int ssn1;
	int ssn2;
	MOBSTOREITEM	TradeItem[MAX_MOBSTORE];

	int TickDiff;
	BYTE			byEvent;
	int				nPreX, nPreY;
	DWORD			m_dwLastTickTime;
	int				m_LastTime;

	int				m_nCash;
	DWORD			m_time[MAX_TIMEITEM];
	char			m_UserNo[20];

	//	�����ý���
	int				m_nChallengeMode;					//	0:�Ϲݸ��, 1:������û�� �����, 2:�ֹ�Ȯ���� �������
	int				m_nChallenger;						//	������� ID
	char			m_pChallenger[SZNAME_LENGTH];		//	������� �̸�

	short			m_snTimeMode;						//	�Ⱓ�� ������ ���ø��
	byte			m_byItemStatus;						//	�����ۻ���� ����� Ȱ��ȭ���θ� �Ǵ�(bit flag, �����ʱ��� 0st bit)
														//	0st:_MSG_BeautyȰ��ȭ, 1st~7st:����
	//	��忬�հ���
	int				m_nAllianceUser;					//	���տ�û���
	byte			m_byAllianceMode;					//	0:normal, 1:request, 2:response
	
	//	��Ƽ��û
	char			m_pPartyRequester[SZNAME_LENGTH];	//	��Ƽ��û��� �̸�
	DWORD			m_dwEvent;							//	������ �̺�Ʈ �����Ȳ
	DWORD			m_dwCoolEscape;						//	Msg_Escape ��Ŷ�� ��Ÿ�� ����

	//	Quiz
	DWORD			m_dwQuiz;
	DWORD			m_dwQuizCount;

	//	Memorized Position
	byte			m_byZone;
	byte			m_byCloseType;
	byte			m_byCloseAndGoZone;
	short			m_snGoX;
	short			m_snGoY;
	short			m_snMemX;
	short			m_snMemY;
	byte			m_byQuestLevel;
	short			m_snQuestID;
	byte			m_byQuestKill[4];
	DWORD			m_dwQuestClearData;
	DWORD			m_dwQuestHistory[8];		
};

#endif