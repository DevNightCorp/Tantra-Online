//////////////////////////////////////////////
//			Crack Defines and point			//
//////////////////////////////////////////////

//TYPE		POINT		NOTE
//3			30			개인상점에서 거래시 거래대상이 자신인 경우
//5			1			서버계산보다 큰거리(계산치+2)를 이동시 
//6			3			5번 총이동거리를 계산하여 이동거리가 클경우(계산치+6) 
//7			10			CPU 가속을 이용한 핵사용
//8			10			이동속도와 이동거리를 변경되어 있을 때
//12		10			접속중이 아니거나 플레이 상황이 아닌데 루피아를 창고와 인벤사이에서 옮길경우
//13		20			접속중이 아니거나 플레이 상황이 아닌데 교환을 했을경우
//14		20			접속중이 아니거나 플레이 상황이 아닌데 개인상점을 할경우
//15		20			접속중이 아니거나 플레이 상황이 아닌데 물건을 옮길경우(장착포함)
//16		20			접속중이 아니거나 플레이 상황이 아닌데 물건을 떨어뜨림
//17		20			접속중이 아니거나 플레이 상황이 아닌데 물건을 구입
//18		20			접속중이 아니거나 플레이 상황이 아닌데 물건을 팜
//19		20			접속중이 아니거나 플레이 상황이 아닌데 NPC 기능 사용
//20		50			PK를 이용하여 돈을 떨어뜨려 돈 복사를 시도하는 경우
//21		20			전투 패킷을 뛰어넘고 공격을 시도할 경우
//22		100			공격 속도를 변조하여 핵 사용


#define CRACK_MOBSTORE_SELF		3
#define CRACK_SPEED_HACK1		5
#define CRACK_SPEED_HACK2		6
#define CRACK_SPEED_HACK3		7
#define CRACK_SPEED_HACK4		8
#define CRACK_NOUSER_MONEY		12
#define CRACK_NOUSER_TRADE		13
#define CRACK_NOUSER_MONSTORE	14
#define CRACK_NOUSER_MOVE		15
#define CRACK_NOUSER_DROP		16
#define CRACK_NOUSER_BUY		17
#define CRACK_NOUSER_SELL		18
#define CRACK_USER_STATUS		19
#define CRACK_USER_PKTHACK		20
#define CRACK_IGNORECOMBATPHASE 21
#define CRACK_ATTACK_SPEED_HACK 22
#define CRACK_SKILLCASTSPEED_HACK 23
#define CRACK_QUIZ_NOT_RESPONSE	24
#define CRACK_QUIZ_NOT_CORRECT	25

