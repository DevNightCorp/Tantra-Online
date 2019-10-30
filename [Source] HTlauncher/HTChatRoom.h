#pragma once

const int CHATROOM_MAX_NUMBER = 29;

typedef struct _CHATROOMMSG
{
	CHTString	strMsg;
	HT_COLOR	clrColor;
	int			Pibot;

} CHATROOMMSG;

#define		MAXSCROLLLINE		1000

// ChatRoom UI 제어 클래스 
class HTChatRoom
{
private:
	
public:
	HTChatRoom(void);
	~HTChatRoom(void);
	
	CHATROOM	m_room[MAX_CHATROOM];														// 채팅방 리스트 배열
	
	CHATROOMMSG m_oChatMsg[MAXSCROLLLINE];															// 메시지 저장용 구조체
	int			m_iTotalLine;																// 메시지 출력 시작값
	int			m_iEndLoc;

	HTvoid		HT_vChatRoom_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	HTvoid		HT_vChatRoom_WindowPopup();													// 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	HTvoid		HT_vChatRoom_ConnectLoopCheck();											// 연결상태 루프 체크 함수
	HTvoid		HT_vChatRoom_WindowHide();													// 화면 감춤시 호출
	HTvoid		HT_vChatRoom_SetInfo();														// 화면 갱신시 호출 (UI 갱신부)
	HTvoid		HT_vChatRoom_SetText(CHTString str);
	HTvoid		HT_vChatRoom_ClearText();

	HTvoid		HT_vSetText_Enter(CHTString strCharName, CHTString strCharTrimuriti);		// 입장안내 출력
	HTvoid		HT_vSetText_Out(CHTString strCharName, CHTString strCharTrimuriti);			// 나감안내 출력
	HTvoid		HT_vSetText_Cut(CHTString strCharName);			// 추방안내 출력

	int			m_ScrollVarValue;
	int			m_iTotalScrollLine;
	int			m_iRoomNo;																	// 선택한 방 인덱스 (UI 기준)
	int			m_iMessageBoxMode;															// 메시지 박스 처리 상태 (구분 번호)

	int			m_iByPass[20];																// 실제 저장하고 있는 룸 인덱스의 공개/비공개 상태 저장
	int			m_iByNo[20];																// 실제 저장하고 있는 룸 인덱스의 번호 저장
	CHTString	m_ibyChatRoomName[20];														// 실제 저장하고 있는 룸 인덱스의 방제 저장
	int			m_iChatRoomPage;																// 현재 채팅방리스트 페이지 번호
	int			m_iWaitingPage;																// 현재 대기실 페이지 번호
	int			m_iTargetID;
	CHTString	m_szTargetName;
	CHATMEMBER	m_oRoomMember[7];
	CHATMEMBER	m_oWaitingMember[20];

	CHTString	m_strTitle;																	// 설정한 방제는?
	CHTString	m_strPassWord;																// 설정한 비밀번호는?
	CHTString	m_strMemberNo;																// 설정한 맴버 수는?
	

	bool		m_bReader;																	// 지금 자신이 리더인가? true = 그렇다.
	bool		m_bCreate;																	// 리더를 대상으로 방을 생성중인가? 아니면 갱신 중인가?
	int			m_iWaitingMember;															// 대기실에서 선택한 사람 Index

	static void HT_hrChatRoom_InputCheck(int iAction, int iTarget, int iTargetID);			// 대기실 입력 처리 함수 (UI 입력제어부)
	static void HT_hrChatRoom2_InputCheck(int iAction, int iTarget, int iTargetID);			// 대기실 입력 처리 함수 (UI 입력제어부)
	static void HT_hrChatRoom3_InputCheck(int iAction, int iTarget, int iTargetID);			// 대기자 명단창 입력 처리 함수 (UI 입력제어부)
	static void HT_hrChatRoomCreate_InputCheck(int iAction, int iTarget, int iTargetID);	// 채팅방 입력 처리 함수 (UI 입력제어부)

	// 서버로 보내는 패킷 처리 함수들 모음
	HTvoid	HT_vNetWork_CSP_Req_ChatMessage(CHTString str);									// 메시지 전송
	HTvoid	HT_vNetWork_CSP_Req_AccountLogin();												// 로그인 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomListRequest();										// 채팅방 리스트 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomCreate();											// 채팅방 생성 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomJoin();												// 해당 채팅방 참여 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomGoout();											// 참여한 채팅방으로 부터 나감
	HTvoid	HT_vNetWork_CSP_Req_ChatWaitingListRequest();									// 채팅방 대기자 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomInvite(int iType, int iResult = 0);					// 초대 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomUpdate();											// 채팅방 변경 요청
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomOrder(int iType, int iTargetID, CHTString strTargetName);


	// 서버로부터 받는 패킷 처리 함수들 모음
	HTvoid			HT_vNetWork_SCP_ChatMessage( MSG_Chat* info );							// 메시지 수신
	HTvoid			HT_vNetWork_SCP_AccountLogin( Msg_AccountLogin* info );					// 로그인 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomList( Msg_ChatRoomList* info );					// 채팅방 리스트 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomCreate( Msg_ChatRoomCreate* info );				// 채팅방 생성 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomJoin( Msg_ChatRoomJoin* info );					// 해당 채팅방 참여 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomGoout( Msg_ChatRoomGoout* info);				// 참여한 채팅방으로 부터 나감
	HTvoid			HT_vNetWork_SCP_ChatRoomInfo( Msg_ChatRoomInfo* info );					// 참여한 채팅방 정보 갱신 응답
	HTvoid			HT_vNetWork_SCP_ChatWaitingList( Msg_ChatWaitingList* info );			// 채팅방 대기자 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomInvite( Msg_ChatRoomInvite* info );				// 초대 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomUpdate( Msg_ChatRoomUpdate* info );				// 채팅방 변경 응답
	HTvoid			HT_vNetWork_SCP_ChatRoomOrder( Msg_ChatRoomOrder* info );				// 채팅방 강퇴 응답
};