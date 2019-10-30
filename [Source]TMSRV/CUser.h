#ifndef _CUSER_
#define _CUSER_
#include <windows.h>

#include "Basedef.h"
#include "CPSock.h"
#include "CMob.h"



// 기본적으로 MOB 정보가 없는 경우에는, 클라이언트 커넥션 로스트시 LOGIN 플레그만 리셋해주면 된다.
// MOB정보가 있는 경우에는 SAVING4QUIT 상태로 만든후, MOB_SAVE를 요청한다. 
// MOB_SAVE의 CNF에서 SAVING4QUIT을 EMPTY로 바꾼다.



//----------------------------------------------------------------------------------------------------------
#define USER_EMPTY       0   // 비어있다.
#define USER_ACCEPT      1   // ACCEPT 직후상태. CloseUser에서 저장하지 않는다.
#define USER_LOGIN       2   // DB서버에 ID,PASS를 넘기고 기다리는중. CloseUser에서 저장하지 않는다. 
                             // CloseUser후 DB계정정보가 오는경우 처리하지 않는다. 
                             // CloseUser가 오면 DB에 SaveUser가 아닌 Login flag만 reset 시킨다.
//-------어카운트 로그인 했는가----------------------------------------------------------------------------
#define USER_SELCHAR     11   // DB서버의 캐랙터 중에서 어느걸 쓸지 고르는 중.
#define USER_CHARWAIT    12   // DB서버에서 캐랙터 정보를 읽어 오는중 
#define USER_CREWAIT     13   // CreateCharactor요청상태 이상태에서 Login은 불가하다.
#define USER_DELWAIT     14   // DB서버에서 캐랙터 정보를 읽어 오는중 

//-------게임서버에 MOB데이터가 있는가----------------------------------------------------------------------
#define USER_PLAY        22   // DB서버의 정보가 채워져, 사용자 데이터 필드가 유효한 상태.
#define USER_SAVING4QUIT 24   // 접속은 이미 종료 되었고, SAVEUSER를 DB서버에 날리고  CNF에 EMPTY로 바꾼다. Sock은 NULL이다.
//#define USER_RECONNECT   24   // 이미 접속중일때, 이전 접속이 끊겨 저장되기를 기다리는 상태. CloseUser에서 저장하지 않는다.



// A가 접속중이고 BCD가 동시에 끊고 접속을 요청했다.

// B의 요청으로 DB서버는 A의 접속을 끈도록 요구한다. 이때 게임서버는 클라이언트는 끊어 버린다.
// C의 요청으로 DB서버는 A의 접속을 끈도록 요구한다. 이때 게임서버는 클라이언트는 끊어 버린다.
// D의 요청으로 DB서버는 A의 접속을 끈도록 요구한다. 이때 게임서버는 클라이언트는 끊어 버린다.
// 이때 게임서버는 USER_SELCHAR 이전은 AccountName이 채워져 있어도 유효한 Account로 보지 않는다.
// A를 가진 게임서버는 A는 끊어진체 A의 저장종료 요청을 DB서버에 날린다.
// DB서버는 A의 접속을 끊도록 요구한체 기다리는 경우 재 종료 요청이 오면 역시 메시지를 다시 날린다.
// (A의 게임 서버가 메시지를 먹어 버렸을수 있기 때문)
// B는 4초 간격으로 3회 끊고 접속하기를 시도한다. ->  Client는 특정 모드에서 Sock이 NULL일 경우 카운트 하며
// 시도를 반복하다 3회 실패시 "접속자가 많아, 접속할수 없습니다. 조금후에 다시 시도해 주세요"를 리턴.
// 이 재시도중 가짱 빠른 BCD중 하나가 먹는다.
// DB 서버는 연속으로 끊는 메시지에 대해 "다른곳에서 로그인하여 끊깁니다"를 클라이언트에게 보내며 
// DB서버는 역시 게임서버에는 끊도록 Quit를 날리고 CNF가 올때까지 접속중 상태로 본다.
// 게임서버가 USER_LOGIN 상태고 DB서버가 LOGIN flag가 SET된 경우 는 있을수 없다.
// (DB서버는 LOGIN FLAG를 SET하는 동시에 게임서버에 LOGIN_OK를 날리기 때문이다.) 
// 클라이언트가 3회의 재요청 중간에 SELCHAR를 받자마자, 다른곳에서 로그인 되어서 끊깁니다를 받게된다.
// (DB서버의 재요청 메시지는 항상 GAME서버를 거쳐 순서대로 처리된다)
// 

   


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//                  USERFILE
//
// ID
// PASS
// 기타 프로파일
// 과금정보
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
	// 어카운트만 생성전 중복 체크를 한다
	// 캐랙터 만들기시 전송부분
    char AccountName[ACCOUNTNAME_LENGTH];
	///////
	int				Slot;                  // DB서버의 몇번째 MOB인지.
	int				IP;
	char			pIP[18];
	// Temporary part
	int				Mode;
	int				TradeMode;		//	교환
	BYTE			byTradeMode;	//	개인상거래
    CPSock			cSock;
	STRUCT_ITEM		Cargo[MAX_CARGO];
	int				Coin;
    MSG_Trade		Trade;
	unsigned int	LastAttack;
	unsigned int	LastAttackTick; 
	unsigned int	LastMove;
	unsigned int	LastAction;
	unsigned int	LastActionTick;
	unsigned int	NumError;  // CNFCharacterLoing에 초기화되며 Server와 Sync가 맞지 않을 경우 Increment. n회(30정도) 이상이면 로그를 남기고 CloseConnection.
	int				Billing;   // 0:의뢰전-잠시기다려 주세요.  1:의뢰후-잠시기다려 주세요.  2:통과-   3:사용제한-돈  4:사용제한-동접.  5:기타에러 (통과)
	S_CHARACTER_LIST	sData[MOB_PER_ACCOUNT];
	char			LastChat[SZNAME_LENGTH];
	int				IsBillConnect;     // 빌링서버에 로그인 메시지를 날린경우.
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

	//	결투시스템
	int				m_nChallengeMode;					//	0:일반모드, 1:신투신청후 대기모드, 2:쌍방확인후 결투모드
	int				m_nChallenger;						//	결투상대 ID
	char			m_pChallenger[SZNAME_LENGTH];		//	결투상대 이름

	short			m_snTimeMode;						//	기간제 아이템 세팅모드
	byte			m_byItemStatus;						//	아이템사용후 기능의 활성화여부를 판단(bit flag, 오른쪽기준 0st bit)
														//	0st:_MSG_Beauty활성화, 1st~7st:미정
	//	길드연합관련
	int				m_nAllianceUser;					//	연합요청대상
	byte			m_byAllianceMode;					//	0:normal, 1:request, 2:response
	
	//	파티요청
	char			m_pPartyRequester[SZNAME_LENGTH];	//	파티요청상대 이름
	DWORD			m_dwEvent;							//	유저의 이벤트 진행상황
	DWORD			m_dwCoolEscape;						//	Msg_Escape 패킷의 쿨타임 적용

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