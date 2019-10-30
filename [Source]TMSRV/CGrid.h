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
#define USER_PLAYWAIT    21   // 게임서버상에서는 캐랙터로그인하였으나 Client의 Confirm은 받지 않은경우.
#define USER_PLAY        22   // DB서버의 정보가 채워져, 사용자 데이터 필드가 유효한 상태.
#define USER_PLAYTOWN    23   // DB서버의 정보가 채워져, 사용자 데이터 필드가 유효한 상태.
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

/*
class CUser
{

   public:

// Saved part
// 어카운트만 생성전 중복 체크를 한다 
// Mob Name은 중복체크 하지 않으며 변경또한 자유롭다.
     
////// 캐랙터 만들기시 전송부분
     STRUCT_ACCOUNT ACCOUNT;
///////
	 int    Slot;                  // DB서버의 몇번째 MOB인지.
     //int    Mob;
	 int    IP;
     int    TradeOn;
// Temporary part
	 int    Mode;
     CPSock cSock;
// Functions
   public:
   	 CUser();
	 ~CUser();
	 BOOL   AcceptUser ( int ListenSocket);
     BOOL   CloseUser  ( void );
     void   Remove     ( void );
};

*/
#endif