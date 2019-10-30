#pragma once

const int CHATROOM_MAX_NUMBER = 29;

typedef struct _CHATROOMMSG
{
	CHTString	strMsg;
	HT_COLOR	clrColor;
	int			Pibot;

} CHATROOMMSG;

#define		MAXSCROLLLINE		1000

// ChatRoom UI ���� Ŭ���� 
class HTChatRoom
{
private:
	
public:
	HTChatRoom(void);
	~HTChatRoom(void);
	
	CHATROOM	m_room[MAX_CHATROOM];														// ä�ù� ����Ʈ �迭
	
	CHATROOMMSG m_oChatMsg[MAXSCROLLLINE];															// �޽��� ����� ����ü
	int			m_iTotalLine;																// �޽��� ��� ���۰�
	int			m_iEndLoc;

	HTvoid		HT_vChatRoom_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	HTvoid		HT_vChatRoom_WindowPopup();													// ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	HTvoid		HT_vChatRoom_ConnectLoopCheck();											// ������� ���� üũ �Լ�
	HTvoid		HT_vChatRoom_WindowHide();													// ȭ�� ����� ȣ��
	HTvoid		HT_vChatRoom_SetInfo();														// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	HTvoid		HT_vChatRoom_SetText(CHTString str);
	HTvoid		HT_vChatRoom_ClearText();

	HTvoid		HT_vSetText_Enter(CHTString strCharName, CHTString strCharTrimuriti);		// ����ȳ� ���
	HTvoid		HT_vSetText_Out(CHTString strCharName, CHTString strCharTrimuriti);			// �����ȳ� ���
	HTvoid		HT_vSetText_Cut(CHTString strCharName);			// �߹�ȳ� ���

	int			m_ScrollVarValue;
	int			m_iTotalScrollLine;
	int			m_iRoomNo;																	// ������ �� �ε��� (UI ����)
	int			m_iMessageBoxMode;															// �޽��� �ڽ� ó�� ���� (���� ��ȣ)

	int			m_iByPass[20];																// ���� �����ϰ� �ִ� �� �ε����� ����/����� ���� ����
	int			m_iByNo[20];																// ���� �����ϰ� �ִ� �� �ε����� ��ȣ ����
	CHTString	m_ibyChatRoomName[20];														// ���� �����ϰ� �ִ� �� �ε����� ���� ����
	int			m_iChatRoomPage;																// ���� ä�ù渮��Ʈ ������ ��ȣ
	int			m_iWaitingPage;																// ���� ���� ������ ��ȣ
	int			m_iTargetID;
	CHTString	m_szTargetName;
	CHATMEMBER	m_oRoomMember[7];
	CHATMEMBER	m_oWaitingMember[20];

	CHTString	m_strTitle;																	// ������ ������?
	CHTString	m_strPassWord;																// ������ ��й�ȣ��?
	CHTString	m_strMemberNo;																// ������ �ɹ� ����?
	

	bool		m_bReader;																	// ���� �ڽ��� �����ΰ�? true = �׷���.
	bool		m_bCreate;																	// ������ ������� ���� �������ΰ�? �ƴϸ� ���� ���ΰ�?
	int			m_iWaitingMember;															// ���ǿ��� ������ ��� Index

	static void HT_hrChatRoom_InputCheck(int iAction, int iTarget, int iTargetID);			// ���� �Է� ó�� �Լ� (UI �Է������)
	static void HT_hrChatRoom2_InputCheck(int iAction, int iTarget, int iTargetID);			// ���� �Է� ó�� �Լ� (UI �Է������)
	static void HT_hrChatRoom3_InputCheck(int iAction, int iTarget, int iTargetID);			// ����� ���â �Է� ó�� �Լ� (UI �Է������)
	static void HT_hrChatRoomCreate_InputCheck(int iAction, int iTarget, int iTargetID);	// ä�ù� �Է� ó�� �Լ� (UI �Է������)

	// ������ ������ ��Ŷ ó�� �Լ��� ����
	HTvoid	HT_vNetWork_CSP_Req_ChatMessage(CHTString str);									// �޽��� ����
	HTvoid	HT_vNetWork_CSP_Req_AccountLogin();												// �α��� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomListRequest();										// ä�ù� ����Ʈ ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomCreate();											// ä�ù� ���� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomJoin();												// �ش� ä�ù� ���� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomGoout();											// ������ ä�ù����� ���� ����
	HTvoid	HT_vNetWork_CSP_Req_ChatWaitingListRequest();									// ä�ù� ����� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomInvite(int iType, int iResult = 0);					// �ʴ� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomUpdate();											// ä�ù� ���� ��û
	HTvoid	HT_vNetWork_CSP_Req_ChatRoomOrder(int iType, int iTargetID, CHTString strTargetName);


	// �����κ��� �޴� ��Ŷ ó�� �Լ��� ����
	HTvoid			HT_vNetWork_SCP_ChatMessage( MSG_Chat* info );							// �޽��� ����
	HTvoid			HT_vNetWork_SCP_AccountLogin( Msg_AccountLogin* info );					// �α��� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomList( Msg_ChatRoomList* info );					// ä�ù� ����Ʈ ����
	HTvoid			HT_vNetWork_SCP_ChatRoomCreate( Msg_ChatRoomCreate* info );				// ä�ù� ���� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomJoin( Msg_ChatRoomJoin* info );					// �ش� ä�ù� ���� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomGoout( Msg_ChatRoomGoout* info);				// ������ ä�ù����� ���� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomInfo( Msg_ChatRoomInfo* info );					// ������ ä�ù� ���� ���� ����
	HTvoid			HT_vNetWork_SCP_ChatWaitingList( Msg_ChatWaitingList* info );			// ä�ù� ����� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomInvite( Msg_ChatRoomInvite* info );				// �ʴ� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomUpdate( Msg_ChatRoomUpdate* info );				// ä�ù� ���� ����
	HTvoid			HT_vNetWork_SCP_ChatRoomOrder( Msg_ChatRoomOrder* info );				// ä�ù� ���� ����
};