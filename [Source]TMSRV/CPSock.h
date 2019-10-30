#ifndef _CPSOCK_
#define _CPSOCK_ 

//#include "protocol.h"

#define WSA_READ            (WM_USER+100) // WSAREAD ~ WSA_READ+10 // 100개만 검색한다.
#define WSA_READDB          (WM_USER+2) 
#define WSA_ACCEPT          (WM_USER+3) 
#define WSA_ACCEPTADMIN     (WM_USER+4) 
#define WSA_READADMINCLIENT	(WM_USER+5) 
#define WSA_READADMIN		(WM_USER+6) 
#define WSA_READBILL		(WM_USER+7) 
#define WSA_READMSG			(WM_USER+8)
#define WSA_ACCEPTWEB		(WM_USER+9)
#define WSA_READWEB			(WM_USER+10)
#define WSA_READITEM		(WM_USER+11)
#define WSA_ACCEPTWHATSUP	(WM_USER+12)

#define MAX_PENDING_CONNECTS  8

#ifdef	__ZONE_SERVER__
	#define RECV_BUFFER_SIZE      (64*1024)         // 64K client하나가 발송하는 양이 중첩되는 최고.
	#define SEND_BUFFER_SIZE      (64*1024)         // 64K 각클라이트가 보낸 메시지가 합쳐지는양.
	//??
#elif	__DBA_SERVER__
	#define RECV_BUFFER_SIZE      (256*1024)         // 256K client하나가 발송하는 양이 중첩되는 최고.
	#define SEND_BUFFER_SIZE      (256*1024)         // 256K 각클라이트가 보낸 메시지가 합쳐지는양.
#elif	__MSG_SERVER__
	#define RECV_BUFFER_SIZE      (256*1024)         // 256K client하나가 발송하는 양이 중첩되는 최고.
	#define SEND_BUFFER_SIZE      (256*1024)         // 256K 각클라이트가 보낸 메시지가 합쳐지는양.
#elif	__CLIENT__
	#define RECV_BUFFER_SIZE      (128*1024)         // 128K client하나가 발송하는 양이 중첩되는 최고.
	#define SEND_BUFFER_SIZE      (128*1024)         // 128K 각클라이트가 보낸 메시지가 합쳐지는양.
#else
	#define RECV_BUFFER_SIZE      (64*1024)         // 64K client하나가 발송하는 양이 중첩되는 최고.
	#define SEND_BUFFER_SIZE      (64*1024)         // 64K 각클라이트가 보낸 메시지가 합쳐지는양.
#endif	

#define MAX_MESSAGE_SIZE           20000         // 모든 Single message 는 4K 미만이다.

#define INITCODE               0x1F44F321

typedef struct _HEADER
{
	WORD	wType;
	WORD	wSeq;
	WORD	wPDULength;
	WORD    wDummy;
	DWORD	dwClientTick;
} HEADER, *PHEADER;

struct STRUCT_SOCKET_THREAD_PARM
{	char	HostAddr[256];
	int		Port;
	int		ip;
	int		WSA;
	HWND	WindowHandle;
};


class  CPSock
{   
public:
	unsigned int  Sock;
	char*	pSendBuffer;
	char*	pRecvBuffer;
	int		nSendPosition;
	int		nRecvPosition;
	int		nProcPosition;
	int		nSentPosition;
	int     Init;	
	unsigned int	IP;
	unsigned short	Port;
	unsigned int	LastReceiveTime;
	//HANDLE			ThreadHandle;
	//CRITICAL_SECTION	csConnecter; // 불편해도 안전을 위해서 global로 뺀다
	STRUCT_SOCKET_THREAD_PARM ThreadParm;
	unsigned int	AsyncSock;
	unsigned char	ucSendSeq;
	unsigned char	ucRecvSeq;
	unsigned char	oldRecvChecksum;
	unsigned char	oldSendChecksum;
	byte			m_byCount;
	char			m_pszWho[128];
	BYTE			m_byWhoCount;
	int				m_iWhoTick;
	BOOL	(*m_pfnSend)(CPSock*, char*, int );
	char*	(*m_pfnRead)(CPSock*, int* , int*);

public:
	CPSock();
	~CPSock();
	static BOOL	WSAInitialize ( void );
	BOOL	StartListen   ( HWND hWnd      , int ip,int Port , int WSA);
	SOCKET	ConnectServer ( char *HostAddr , int Port , int ip, int WSA,HWND WindowHandle,BOOL bSendInit = TRUE );
	BOOL	Receive       ( void );
	char*	ReadMessage   ( int *ErrorCode ,int *ErrorType);
	BOOL	CloseSocket   ( void );
	BOOL	AddMessage    ( char *pMsg,int Size);
	char*	ReadServerMessage   ( int *ErrorCode ,int *ErrorType);
	char*	ReadClientMessage   ( int *ErrorCode ,int *ErrorType);
	BOOL	AddServerMessage    ( char *pMsg,int Size);
	BOOL	AddClientMessage    ( char *pMsg,int Size);
	BOOL	SendMessage   ( void );
	BOOL	SendOneMessage( char* Msg, int Size);
	unsigned int ConnectBillServer(char *HostAddr,int Port ,int ip,int WSA, HWND WindowHandle);
	DWORD	GetLastError();
	void	RefreshRecvBuffer(void);
	void	RefreshSendBuffer(void);
	BOOL	SendBillMessage(char * Msg);
	char *	ReadBillMessage(int * nType, int * ErrorCode,int * ErrorType);
	BOOL	SendCashMessage(char * pMsg, int Size);
	char *	ReadCashMessage(int * ErrorCode,int * ErrorType);
	void	ConnectServerAsync(char *HostAddr , int Port , int ip, int WSA,HWND WindowHandle);
	void	SetServerSecret(bool bFlag = true);

		virtual	void	OnConnect	(int nErrorCode) {}
};

struct _AUTH_GAME{
	int 	Packet_Type;	//	4
	int		Result;			//	4 
	char	S_KEY[32];		//	4*8	 
	char	Session[32];	//  4*8
	char	User_CC[4];		//	4
	char	User_No[20];	//	4*5
	char	User_ID[52];	//  4*13
	char	User_IP[24];	//  4*6
	char	User_Gender;	
	char	User_Status[3];	//	4	
	char	User_PayType[4];//	2 ?
	int 	User_Age;		//  4
	int 	Game_No;		//  4
	char	Bill_PayType[2];
	char	Bill_Method[2];	//	4
	char	Bill_Expire[12];//	4*3 	
	int 	Bill_Remain;	//	4
};

struct _AUTH_GAME2{
	int 	Packet_Type;
	int		Packet_result;
	char	User_ID[52];
	char	User_roleName[20];
	int		Map_number;	
	int		User_co[2];	
	int		article_number;
	int		Dressed;
	int		Time_Exchanged;	
	int		ItemNo;		
	char	cardNumber[20];	
	char	cardPassword[20];
	char	messageflag[4];
	char	activeMessage[20];	
	char 	reserved[36];
};

#define g_cGame  (sizeof(_AUTH_GAME))
#define g_cGame2  (sizeof(_AUTH_GAME2))
extern CRITICAL_SECTION	csConnecter;

#endif
