//======================================================================
// CHTChatting.cpp
// ä�� ���� �޽��� ����
// (��)�Ѻ�����Ʈ ���Ӱ����� ���Ǳ�		.......... �����ۼ�
// (��)�Ѻ�����Ʈ ���Ӱ����� ����ȣ		2002.09.13 �߰�/����
// (��)�Ѻ�����Ʈ ���Ӱ����� ����		2002.10.22 �߰�/����20021022Tenma
// (��)�Ѻ�����Ʈ ���Ӱ����� ���Ǳ�		2003.����
//======================================================================
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTWindowManager.h"
#include "HTChatting.h"
#include "resource.h"

#define _CHAT_CHAT_USER_NUM				10
#define _CHAT_CHAT_LOG_NUM				21

#define CHATWNDSTYLE_NORMAL			0
#define CHATWNDSTYLE_TRANSPARANCY	1
#define CHATWNDSTYLE_MIDDLESIZE		2
#define CHATWNDSTYLE_BIGSIZE		3

#define	CHAT_CHATLAVELINDEX			10
#define	CHAT_SYSTEMLAVELINDEX		30
#define CAHT_CHATLOGLABELSATRT		10

// ä��â�� ��Ȱ���� ���¿��� �޽����� �޾��� ��� ä�� ��ư�� �����̴� �ð��� �����Ѵ�. (ms)
#define CHATTING_BUTTON_FLASHING_INTEVAL		1000

extern CHTWindowManager*			g_CGame;

CHTChatting::CHTChatting()
{
	m_bChatStatusOn			= HT_FALSE;				// ó������ �Էµ� �ȹ޴´�.
	m_IMEStatus				= IME_STATUS_ENGLISH;	// ó������ �ѱ� �Է� ����̴�.

	// ä�� �޽��� �ʱ�ȭ
	m_strChatMessage.HT_hrCleanUp();
	// �ӼӸ� �޴� ��� �̸� �ʱ�ȭ
	m_strWisperName.HT_hrCleanUp();

	// ��ȭ������ ���Ϸ� �α��� ó������ �翬�� ���Ѵ�.
	m_bLogging = HT_FALSE;
	// ó������ ��(������ ���� ���� ����)
	m_pLogFile = NULL;

	m_iNameListNum = 0;
	for( HTint i=0 ; i<_MAX_SAVED_NAMELIST_NUM ; i++ )
	{
		m_strWhisperNameList[i].HT_hrCleanUp();
	}
	m_iChat_WhisperReadIndex = 0;

	// �������� ���ڿ� ����
	m_pNotifyBuffer = (HTtchar *)malloc( 1000 * sizeof(HTtchar) );
	// 20030123Tenma_test �ӽ÷� ó�� �������� ��� ���ڿ�
	LoadString(g_hInstance, IDS_NOTIFY_MSG_TEMP, m_pNotifyBuffer, 1000);

	for (i=0; i<_MAX_SAVED_MESSAGE_NUM; i++)		ZeroMemory(&m_oSavedChatMsg[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_HISTORY_NUM; i++)		ZeroMemory(&m_oSavedHistory[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_NAMELIST_NUM; i++)		m_strNameList[i].HT_hrCleanUp();

	//	���������� �ӼӸ� ���� ���
	m_strLastRiciveWisperName.HT_hrCleanUp();
	//	/Ż�� 3�ʿ� �ѹ��� ������ �ϱ� ����
	m_dwEscapeSaveTime = 0;
}

CHTChatting::~CHTChatting()
{	
	// ó�� �������� ���ۿ� ���ڿ��� ���� ������ ���ڿ��� ���� 20030123Tenma_test
	if( m_pNotifyBuffer != NULL )
	{
		// �������� ���ڿ� �迭�� ����.
		free( m_pNotifyBuffer );
		m_pNotifyBuffer = NULL;
	}

	// �α� ������ ���� ������ �ݴ´�.
	if( m_pLogFile )
		fclose( m_pLogFile );

	//fclose( pFile_Point );

	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATTINGBOX );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATTING2BOX );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATTING3BOX );
	g_cUIManager->HT_DeleteWindow( _DIALOG_OPENMESSAGE );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WHISPERLISTWND );
	
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATCONFIG );

	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATLOGCONFIG );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATLOG1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHATLOG2 );
}

HTvoid CHTChatting::HT_vChatting_Init()
{
	//	ä�� ������ ��Ÿ��
	m_iChatWindowStyle = CHATWNDSTYLE_NORMAL;
	//	Create Window
	this->HT_vChatting_CreateWindow();
	//	Set Enter Button
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_CHATTINGBOX, 1 );
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_CHATTING2BOX, 1 );
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_CHATTING3BOX, 1 );
	g_cUIManager->HT_ShowWindow( _DIALOG_CHATTINGBOX );
	//	Read Parse Msg
	this->HT_vChatting_ReadParseMsg();

	//	������ ������
	m_iOpenMessageItemIndex = 0;
	//	������ ������ ����
	m_byOpenMessageItemType = 0;
	//	Save Recive Msg
	for( int i=0 ; i<OPENMESSAGE_MAX_COUNT ; i++ )
	{
        memset( &m_oOpenMessageSave[i], 0, sizeof(OpenMESSAGE) );
		m_oOpenMessageSave[i].bExistSw = HT_FALSE;
	}
    //	Text Positiion
	m_fOpenTextPosX = -999;
	//	Text Rotate Count
	m_iOpenRotateCount = 0;
	//	Chatting Block
	m_bChat_ChatBlockSw = HT_FALSE;

	//	History, Whisper Fucntion
	for( i=0 ; i<10 ; i++ )
		m_strChat_HistoryMsg[i].HT_hrCleanUp();
    m_iChat_HistroyWriteIndex = 0;
	m_iChat_HistroyReadIndex = 0;

	//	��ũ�� ��
	m_iChat_ScrollChat = 0;
	m_iChat_ScrollSystem = 0;
	//	ä�� �Է� ���
    m_bChat_InputMode = HT_FALSE;
	//	Open Msg Type
	//	0:����, 1:�ƽ����̸�, 2:������, 3:������ɼ�
	m_byChat_OpenMsgType = 0;
	//	�۾��� �޽��� ī��Ʈ
	m_iChat_MsgCount = 0;

	//	ä�� ����
	for( i=0 ; i<5 ; i++ )
        m_bChat_ConfigChat[i] = HT_FALSE;
    m_bChat_ConfigChat[0] = HT_TRUE;
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, m_bChat_ConfigChat[0] );

	//	ä�� �α�
	ZeroMemory(	&m_oChat_ChatLog, sizeof(ChatLogStrut)*CHATLOG_MAX_COUNT );
	m_iChat_ChatLogCount = 0;
    for( i=0 ; i<6 ; i++ )
        m_bChat_ChatLogConfig[i] = HT_FALSE;
	m_bChat_ChatLogConfig[0] = HT_TRUE;
	ZeroMemory(	&m_oChat_SaveOpenMsg, sizeof(ChatLogStrut)*OPENMSG_MAX_COUNT );
	m_iChat_OpenMsgCount = 0;

	//	���� ������ ��Ÿ�� üũ
	this->HT_vChatting_ChangeChatWnd();
	
	//g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
}

HTvoid CHTChatting::HT_vChatting_CleanUp()
{
}

//	Create Window
HTvoid CHTChatting::HT_vChatting_CreateWindow()
{
	CHTString strMessage;
	// �ػ� ����
	HTint iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();

	//	[_DIALOG_CHATTINGBOX]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATTINGBOX, _T(""), 412, 250, g_cChatting->HT_vChatting_InputCheckForChatWnd, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTINGBOX, true );	// ��濵�� Ŭ���� �� �ȵǰ�
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTINGBOX, 0, iScreenHeight-250-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTINGBOX, TRUE, 15,189, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 170, 15, 189 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 51, 0, 0, 202, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, g_cUIManager->m_nAlphaColor/100.0f ), 412, 48 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 51, HT_FALSE );
	//	�ܰ���
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 2, 0, 0, 1400, 412, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 100, 2, 0, 100, 1400, 412, 3 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 1, 412, 0, 1400, 3, 250 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 2, 73, 201, 1400, 339, 3 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 2, 73, 220, 1400, 339, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 2, 2, 201, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 2, 2, 220, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 1, 2, 201, 1400, 3, 19 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 1, 73, 201, 1400, 3, 19 );
	//	Edit Box 1
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTINGBOX, 1, 0, 3, 202, 70, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTINGBOX, 1, 30 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTINGBOX, 1, 1);
	//	Edit Box 2
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTINGBOX, 2, 0, 73, 203, 291, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTINGBOX, 2, MAX_CHAT_LENGTH+1 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTINGBOX, 2, 1);
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 1, 1, 104, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 1, 100 );
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 2, 1, 4, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 2, 100 );
	//	Button ä��â �ٲٱ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 9, 57, 1, 225, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 9, _T("C1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 228, 24, 16 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button ä�ø��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 11, 159, 362, 202, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	ä�ø�庯ȯ
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 202, 50, 19 );
	//	Button ä�� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 2, 159, 27, 230, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 231, 60, 19 );//ä�ü���
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	ä�ó���ǥ�ü���
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 2, strMessage );
	//	Button ��ü
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 3, 204, 88, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 231, 50, 19 );//��ü
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 3 );
	//	Button ��Ƽ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 4, 204, 139, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 231, 50, 19 );//��Ƽ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 4 );
	//	Button �ƽ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 5, 204, 190, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 231, 55, 19 );//�ƽ���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 5 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 6, 204, 246, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 231, 50, 19 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 6 );
	//	Button �ּҷ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 7, 204, 297, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 231, 55, 19 );//�ּҷ�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 7 );
	//	Button ä�÷ΰ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 8, 204, 353, 230, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 231, 59, 19 );//ä�÷α�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 8 );
	
	//	Label Chat Text List
	for( HTint i=0 ; i<5 ; i++)
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, CHAT_CHATLAVELINDEX+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 20, 183-(i*18), 500, 40);
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATTINGBOX, CHAT_CHATLAVELINDEX+i, 7 );
	}
	//	Label System Text List
	for( i=0 ; i<5 ; i++)
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, CHAT_SYSTEMLAVELINDEX+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 20, 83-(i*18), 500, 40);
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATTINGBOX, CHAT_SYSTEMLAVELINDEX+i, 7 );
	}

	//	[_DIALOG_CHATTING2BOX]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATTING2BOX, _T(""), 412, 300, g_cChatting->HT_vChatting_InputCheckForChatWnd, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING2BOX, true );	// ��濵�� Ŭ���� �� �ȵǰ�
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING2BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING2BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 170, 15, 239 );
	//	�ܰ���
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 2, 0, 0, 1400, 412, 3 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 1, 412, 0, 1400, 3, 300 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 2, 73, 251, 1400, 339, 3 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 2, 73, 270, 1400, 339, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 2, 2, 251, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 2, 2, 270, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 1, 2, 251, 1400, 3, 19 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 1, 73, 251, 1400, 3, 19 );
	//	Edit Box 1
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTING2BOX, 1, 0, 3, 252, 70, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTING2BOX, 1, 30 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTING2BOX, 1, 1);
	//	Edit Box 2
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTING2BOX, 2, 0, 73, 253, 291, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTING2BOX, 2, MAX_CHAT_LENGTH+1 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTING2BOX, 2, 1);
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING2BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING2BOX, 1, 100 );
	//	Button ä��â �ٲٱ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 9, _T("C3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button ä�ø��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	ä�ø�庯ȯ
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button ä�� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//ä�ü���
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	ä�ó���ǥ�ü���
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 2, strMessage );
	//	Button ��ü
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//��ü
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 3 );
	//	Button ��Ƽ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//��Ƽ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 4 );
	//	Button �ƽ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//�ƽ���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 5 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 6 );
	//	Button �ּҷ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//�ּҷ�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 7 );
	//	Button ä�÷ΰ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//ä�÷α�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 8 );
	//	Label Chat Text List
	for( HTint i=0 ; i<14 ; i++)
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, CHAT_CHATLAVELINDEX+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 20, 233-(i*17), 500, 40);
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATTING2BOX, CHAT_CHATLAVELINDEX+i, 7 );
	}

	//	[_DIALOG_CHATTING3BOX]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATTING3BOX, _T(""), 412, 300, g_cChatting->HT_vChatting_InputCheckForChatWnd, 0 );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING3BOX, true );	// ��濵�� Ŭ���� �� �ȵǰ�
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING3BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING3BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 170, 15, 239 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 0, 1, 251, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ), 411, 48 );
	//	�ܰ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 2, 2, 251, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 2, 2, 270, 1400, 410, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 1, 2, 251, 1400, 3, 19 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 1, 73, 251, 1400, 3, 19 );
	//	Edit Box 1
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTING3BOX, 1, 0, 3, 252, 70, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTING3BOX, 1, 30 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTING3BOX, 1, 1);
	//	Edit Box 2
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHATTING3BOX, 2, 0, 73, 253, 291, 22 );
	g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHATTING3BOX, 2, MAX_CHAT_LENGTH+1 );
	g_cUIManager->HT_SetEditBoxFocusOnIME( _DIALOG_CHATTING3BOX, 2, 1);
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING3BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING3BOX, 1, 100 );
	//	Button ä��â �ٲٱ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 9, _T("C4"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button ä�ø��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	ä�ø�庯ȯ
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button ä�� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//ä�ü���
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	ä�ó���ǥ�ü���
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 2, strMessage );
	//	Button ��ü
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//��ü
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 3 );
	//	Button ��Ƽ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//��Ƽ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 4 );
	//	Button �ƽ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//�ƽ���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 5 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 6 );
	//	Button �ּҷ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//�ּҷ�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 7 );
	//	Button ä�÷ΰ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//ä�÷α�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 8 );
	//	Label Chat Text List
	for( HTint i=0 ; i<14 ; i++)
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, CHAT_CHATLAVELINDEX+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 20, 233-(i*17), 500, 40);
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATTING3BOX, CHAT_CHATLAVELINDEX+i, 7 );
	}

	//	[_DIALOG_OPENMESSAGE]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_OPENMESSAGE, _T(""), 400, 90, g_cChatting->HT_vChatting_InputCheckForOpenMsg, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_OPENMESSAGE, 5 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPENMESSAGE, 0, 0, 25, 60, 1400, 350, 1 );
	//	Explan Label
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 1, _T(""), 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, 20, 360, 16 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_OPENMESSAGE, 1, 7 );
	//	Edit
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_OPENMESSAGE, 2, 0, 30, 40, 340, 16 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 3, 99, 210, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 3, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 65, 72, 19 );//Ȯ��
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 4, 99, 300, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 4, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 300, 65, 72, 19 );//���

	//	[_DIALOG_WHISPERLISTWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WHISPERLISTWND, _T(""), 184, 148, g_cChatting->HT_vChatting_InputCheckForWhisperList, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_WindowArrangement( _DIALOG_WHISPERLISTWND, 5 );
	//	Button
	for( i=0 ; i<_CHAT_CHAT_USER_NUM ; i++ )
	{
		g_cUIManager->HT_AddButtonControl( _DIALOG_WHISPERLISTWND, _CHAT_CHAT_USER_NUM-i, 0, 0, 5+(i*13), 201, 0, 1500, 184, 12 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_WHISPERLISTWND, _CHAT_CHAT_USER_NUM-i, _T(""), 4, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 5+(i*13), 184, 12 );
	}
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//��ü
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_WHISPERLISTWND, 1, strMessage );

	//	[_DIALOG_CHATCONFIG]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATCONFIG, _T(""), 90, 100, g_cChatting->HT_vChatting_InputCheckForChatConfig, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATCONFIG, 5 );
	//	Button ��ü
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//��ü
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 1 );
	//	Button ��Ƽ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//��Ƽ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 2 );
	//	Button �ƽ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//�ƽ���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 3 );
	//	Button ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 4 );
	//	Button �ӼӸ�����Ʈ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 5, eMsgChatList, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//����Ʈ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 5 );
    //63 UI_Button03_N_64X19.bmp
	//169, 175
	HT_vChatting_InputCheckForChatWnd(0, 0, 3);

	//	[_DIALOG_CHATLOG1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATLOG1, _T("ChatLog"), 412, 465, g_cChatting->HT_vChatting_InputCheckForChatLog, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATLOG1, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button �Ϲ� �޽���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 1 );
	//	Button ������ �޽���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 2 );
	//	Button ä�ü���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 3 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 4 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 5 );
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATLOG1, 1, 393, 73, 335, 1000 );
	//	Text
	for( i=0 ; i<_CHAT_CHAT_LOG_NUM ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 5, 77+(i*16), 500, 16 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+i, 7 );
	}

	//	[_DIALOG_CHATLOG2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATLOG2, _T("ChatLog"), 412, 465, g_cChatting->HT_vChatting_InputCheckForChatLog, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATLOG2, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button �Ϲ� �޽���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 1 );
	//	Button ������ �޽���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 2 );
	//	Button ä�ü���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 3 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 4 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 5 );
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATLOG2, 1, 393, 73, 335, 100 );
	//	Text
	for( i=0 ; i<_CHAT_CHAT_LOG_NUM ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+i, _T(""), 4, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 5, 77+(i*16), 500, 16);
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+i, 7 );
	}

	//	[_DIALOG_CHATLOGCONFIG]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATLOGCONFIG, _T(""), 90, 120, g_cChatting->HT_vChatting_InputCheckForChatLogConfig, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATLOGCONFIG, 5 );
	//	Button ��ü
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 1, HT_TRUE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//��ü
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 1 );
	//	Button ��Ƽ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//��Ƽ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 2 );
	//	Button �ƽ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//�ƽ���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 3 );
	//	Button ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 4 );
	//	Button �ӼӸ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 5, eMsgCommonCommandWhisper2, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//�ӼӸ�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 5 );
	//	Button �ý���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 100 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 6, 175, 8, 106, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 6, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 6, 63, 26, 100, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 6, eMsgChatSystem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 100, 64, 19 );//�ý���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 6 );
}
//	Read Parse Msg
HTvoid CHTChatting::HT_vChatting_ReadParseMsg()
{
	HT_vChatting_SetMessage( eMsgCommonChatWhole			, &szWhole );			// ��ü
	HT_vChatting_SetMessage( eMsgCommonChatAshuram			, &szAshuram );			// �ƽ���

	HT_vChatting_SetMessage( eMsgCommonCommandWhole			, &szMsgWhole );		// /��ü
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper		, &szMsgWhisper );		// /�ӼӸ�
	HT_vChatting_SetMessage( eMsgCommonCommandAddress		, &szMsgAddress );		// /ģ�����
	HT_vChatting_SetMessage( eMsgCommonCommandAshuram		, &szMsgAshuram );		// /�ƽ���
	HT_vChatting_SetMessage( eMsgCommonCommandKick			, &szMsgKick );			// /ű
	HT_vChatting_SetMessage( eMsgCommonCommandWin			, &szMsgCommandWin );	// ���â

	HT_vChatting_SetMessage( eMsgCommonCommandAS			, &szMsgAS );			// /GMȣ��
	HT_vChatting_SetMessage( eMsgCommonCommandAS2			, &szMsgAS2 );			// /GMȣ��2
	
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel		, &szMsgASCancel );		// /GMȣ�����
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel2		, &szMsgASCancel2 );	// /GMȣ�����2

	HT_vChatting_SetMessage( eMsgCommonCommandASCheck		, &szMsgASCheck);		// /GMȣ��Ȯ��
	HT_vChatting_SetMessage( eMsgCommonCommandASCheck2		, &szMsgASCheck2 );		// /GMȣ��Ȯ��2
    
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildJoin	, &szMsgAshuramGuildJoin);	// /�ƽ�������
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildLeave	, &szMsgAshuramGuildLeave );// /�ƽ�������Ż��

	HT_vChatting_SetMessage( eMsgCommonCommandGuildMark		, &szMsgGuildMark );	// /��帶ũ
	HT_vChatting_SetMessage( eMsgCommonCommandTrimuritiMark	, &szMsgTrimuritiMark ); // /�ֽŸ�ũ

	HT_vChatting_SetMessage( eMsgCommonCommandInvisible		, &szMsgInvisible );	// /����
	HT_vChatting_SetMessage( eMsgCommonCommandWarp			, &szMsgWarp );			// /����
	HT_vChatting_SetMessage( eMsgCommonCommandMove			, &szMsgMove );			// /�̵�

	HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szMsgNotice );		// /����
	HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /��ü����
	HT_vChatting_SetMessage( eMsgCommonCommandAssistant		, &szMsgAssistant );	// /����

	HT_vChatting_SetMessage( eMsgCommonCommandShout			, &szMsgShout );		// /��ġ��
	HT_vChatting_SetMessage( eMsgCommonCommandParty			, &szMsgParty );		// /��Ƽ
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramNotice	, &szMsgGuildNotice );	// /��������-����
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGrade	, &szMsgGuildGrade );	// /�ƽ������

	HT_vChatting_SetMessage( eMsgCommonChatParty			, &szParty );			// ��Ƽ
	HT_vChatting_SetMessage( eMsgCommonCommandTrade			, &szTrade );			// ��ȯ
	HT_vChatting_SetMessage( eMsgCommonCommandEmerge		, &szEmerge );			// Ż��

	HT_vChatting_SetMessage( eMsgCommonCommandPartyPart		, &szMsgPartyPart );			// /��
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramPart	, &szMsgAshuramPart );			// /��
	HT_vChatting_SetMessage( eMsgCommonCommandWholePart		, &szMsgWholePart );			// /��
	HT_vChatting_SetMessage( eMsgCommonCommandShoutPart		, &szMsgShoutPart );			// /��
	HT_vChatting_SetMessage( eMsgCommonCommandWhisperPart	, &szMsgWhisperPart );			// /��

	HT_vChatting_SetMessage( eMsgCommonCommandDebugMode		, &szMsgDebugMode );			// Debug Mode
	HT_vChatting_SetMessage( eMsgCommonCommandBroadcastMode	, &szMsgBroadcastMode );		// BroadcastMode
	HT_vChatting_SetMessage( eMsgCommonCommandEngineCamera	, &szMsgEngineCamera );			// Use Engine Camera
	HT_vChatting_SetMessage( eMsgCommonCommandGoCamera		, &szGoCamera );				// Go Camera
	HT_vChatting_SetMessage( eMsgCommonCommandShowCursor	, &szShowCursor );				// ShowCursor

	HT_vChatting_SetMessage( eMsgCommonCommandDuel			, &szMsgDuel );				// Duel

	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance1	, &szMsgAshuramAllince1 );				// �ƽ��� ����1 /��
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance2	, &szMsgAshuramAllince2 );				// �ƽ��� ����2 /����
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoin		, &szMsgAshuramJoin );						// �ƽ��� ����

	HT_vChatting_SetMessage( eMsgCommonChatRoom		, &szMsgChatRoom );						// �ƽ��� ����// ä�ù�
}

//	�Է� �޼��� ó��
//	FromChatWnd
void CHTChatting::HT_vChatting_InputCheckForChatWnd(int iAction, int iTarget, int iTargetID)
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	//	Enter Key or Enter Button
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 1 )
		{
			CHTString strEdit2 = g_cUIManager->HT_GetTextEditBoxControl( iChatDlgNo, 2 );
			if( !strEdit2.HT_bIsEmpty() )
			{
                g_cChatting->HT_vParseMsg( g_cUIManager->HT_GetTextEditBoxControl( iChatDlgNo, 1 ), strEdit2.HT_szGetString() );
				//	History Fucntion
				g_cChatting->m_strChat_HistoryMsg[g_cChatting->m_iChat_HistroyWriteIndex++] = strEdit2.HT_szGetString();
				if(	g_cChatting->m_iChat_HistroyWriteIndex > 9 )	g_cChatting->m_iChat_HistroyWriteIndex = 0;
				//	IME Message Init
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( _T("") );
				g_cImeMgr.InputString();
				g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, _T("") );
				g_cChatting->HT_vChatting_SetFocusOff( HT_TRUE );
			}
			else
			{
				// ��, ä�ø�尡 2�϶��� �׳� �Ѿ��.
				if (g_cChatting->m_bChat_InputMode)
					return;

				g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			}
		}
		//	ä�� ����
		else if( iTargetID == 2 )
		{
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_CHATCONFIG ) )
			{
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( iChatDlgNo, iPosX, iPosY );
				g_cUIManager->HT_ShowWindow( _DIALOG_CHATCONFIG );
                if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTINGBOX ) )	g_cUIManager->HT_MoveWindow( _DIALOG_CHATCONFIG, iPosX+27, iPosY+128 );
				else														g_cUIManager->HT_MoveWindow( _DIALOG_CHATCONFIG, iPosX+27, iPosY+178 );

				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 2, 1);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 2, 1);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 2, 1);

				return;
			}
			else
			{
				g_cUIManager->HT_HideWindow( _DIALOG_CHATCONFIG );
				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 2, 0);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 2, 0);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 2, 0);

				return;
			}
		}
		//	��ü
		else if( iTargetID == 3 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//	��ü
			g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, strMessage );
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_SetFocusOn();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 3, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 3, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 3, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 6, 0);
		}
		//	��Ƽ
		else if( iTargetID == 4 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatParty, &strMessage, _T(""), _T("") );	//	��Ƽ
			g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, strMessage );
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_SetFocusOn();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 4, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 4, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 4, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 6, 0);
		}
		//	�ƽ���
		else if( iTargetID == 5 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuram, &strMessage, _T(""), _T("") );	//	�ƽ���
			g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, strMessage );
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_SetFocusOn();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 5, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 5, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 6, 0);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 5, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 6, 0);
		}
		//	����
		else if( iTargetID == 6 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuramAlliance, &strMessage, _T(""), _T("") );	//	�ƽ�������
			g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, strMessage );
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_SetFocusOn();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 6, 1);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 6, 1);

			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 3, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 4, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 5, 0);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 6, 1);
		}
		//	�ּҷ�
		else if( iTargetID == 7 )
		{
			if( g_cAddress->HT_iIsOn() )    g_cAddress->HT_vSetOff();
			else							g_cAddress->HT_vSetOn();
		}
		//	ä�� �Է� ���
		else if( iTargetID == 11 )
		{
			g_cChatting->m_bChat_InputMode = !g_cChatting->m_bChat_InputMode;
			if( g_cChatting->m_bChat_InputMode )	
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTINGBOX, 50, _T("Mode2") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTING2BOX, 50, _T("Mode2") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTING3BOX, 50, _T("Mode2") );
			}
			else
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTINGBOX, 50, _T("Mode1") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTING2BOX, 50, _T("Mode1") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTING3BOX, 50, _T("Mode1") );
			}
			//	Set Focus
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_SetFocusOn();
		}
		//	ä�÷α�
		else if( iTargetID == 8)
		{
			if( g_iInationalType == INATIONALTYPE_KOREA ||
				g_iInationalType == INATIONALTYPE_JAPEN )
			{
				g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG2 );
				g_cUIManager->HT_ShowWindow( _DIALOG_CHATLOG1 );
				//	Set Chat Log
				g_cChatting->HT_vChatting_SetTextinChatLog();
			}
			else
			{
				g_cChatting->HT_vChatting_WorkingMsg();
			}
		}
		//	ä��â ��ȯ
		else if( iTargetID == 9 )
		{
			//	Change Chat Wnd
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			g_cChatting->HT_vChatting_ChangeChatWnd();
		}
	}
	//	Scroll Bar
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		if( iTargetID == 1 )
		{
			g_cChatting->m_iChat_ScrollChat = 100 - g_cUIManager->HT_GetScrollBarValue( iChatDlgNo, 1 );
			g_cChatting->HT_vChatting_SetChatTextList();
		}
		else if( iTargetID == 2 )
		{
			g_cChatting->m_iChat_ScrollSystem = 100 - g_cUIManager->HT_GetScrollBarValue( iChatDlgNo, 2 );
			g_cChatting->HT_vChatting_SetSystemTextList();
		}
	}

	// �������ٸ� �ٽ� ���̰� ����
	if (g_cUIManager->HT_isShowWindow(_DIALOG_WHISPERLISTWND) == true)
	{
		g_cUIManager->HT_HideWindow(_DIALOG_WHISPERLISTWND);
	}
		
	if (g_cUIManager->HT_isShowWindow(_DIALOG_CHATCONFIG) == true)
	{
		g_cUIManager->HT_HideWindow(_DIALOG_CHATCONFIG);
		g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTINGBOX, 2, 0);
		g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING2BOX, 2, 0);
		g_cUIManager->HT_SetButtonControlState(_DIALOG_CHATTING3BOX, 2, 0);
	}
}
//	FromOpenMessage
void CHTChatting::HT_vChatting_InputCheckForOpenMsg(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	���
		if( iTargetID == -1 || iTargetID == 4 )
		{
			g_cChatting->HT_vChatting_DelOpenMessageItemBox();
		}
		//	Ȯ��
		else if( iTargetID == 3 )
		{
			g_cChatting->HT_vChatting_NetworkSendOpenMessage();
		}

		//	Init Ime Mode
		if( g_iInationalType == INATIONALTYPE_JAPEN )
			g_cImeMgr.vImeMgr_SetImeModeCancel();
	}
}
//	FromWhisperList
void CHTChatting::HT_vChatting_InputCheckForWhisperList(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID >= 1 || iTargetID <= 10 )
		{
			CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_WHISPERLISTWND, iTargetID );
			if( !strTemp.HT_bIsEmpty() )
			{
				//	�ӼӸ� ���·� ����� �ְ�..
				g_cChatting->HT_vChatting_SetWisper( strTemp.HT_szGetString() );
				g_cUIManager->HT_HideWindow( _DIALOG_WHISPERLISTWND );
			}
		}
	}
}
//	FromChatConfig
void CHTChatting::HT_vChatting_InputCheckForChatConfig(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID >= 1 && iTargetID <= 4 )
		{
			if( g_cChatting->m_bChat_ConfigChat[iTargetID-1] )	g_cChatting->m_bChat_ConfigChat[iTargetID-1] = HT_FALSE;
			else												g_cChatting->m_bChat_ConfigChat[iTargetID-1] = HT_TRUE;
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, iTargetID, g_cChatting->m_bChat_ConfigChat[iTargetID-1] );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATCONFIG );
			//	Set Text List
			g_cChatting->HT_vChatting_SetChatTextList();
		}
		else if( iTargetID == 5 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_CHATCONFIG );
			g_cChatting->HT_Whisper_Dlg_Check();
		}
	}
}
//	FromChatLog1
void CHTChatting::HT_vChatting_InputCheckForChatLog(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG1 );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG2 );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOGCONFIG );
		}
		//	�Ϲ� �޽���
		else if( iTargetID == 1 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_CHATLOG2, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG2 );
			g_cUIManager->HT_ShowWindow( _DIALOG_CHATLOG1 );
			g_cUIManager->HT_MoveWindow( _DIALOG_CHATLOG1, iPosX, iPosY );
			//	Set Chat Log
			g_cChatting->HT_vChatting_SetTextinChatLog();
		}
		//	������ �޽���
		else if( iTargetID == 2 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_CHATLOG1, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG1 );
			g_cUIManager->HT_ShowWindow( _DIALOG_CHATLOG2 );
			g_cUIManager->HT_MoveWindow( _DIALOG_CHATLOG2, iPosX, iPosY );
			//	Set Chat Log
			g_cChatting->HT_vChatting_SetTextinChatLog();
		}
		//	ä�ü���
		else if( iTargetID == 3 )
		{
			//	�Ϲݸ޽���â�϶��� ��밡��
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG2 ) )
				return;
			//	���� ������ ���� ���� ������ ����
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOGCONFIG ) )
			{
				g_cUIManager->HT_HideWindow( _DIALOG_CHATLOGCONFIG );
			}
			else
			{
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_CHATLOG1, iPosX, iPosY );
				g_cUIManager->HT_ShowWindow( _DIALOG_CHATLOGCONFIG );
				g_cUIManager->HT_MoveWindow( _DIALOG_CHATLOGCONFIG, iPosX+55, iPosY+310 );
			}
		}
		//	����
		else if( iTargetID == 4 )
		{
			//	Write Chat Log File
			g_cChatting->JK_vChatting_ChatLogFile();
		}
		//	Ȯ��
		else if( iTargetID == 5 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG1 );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOG2 );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOGCONFIG );
		}
	}
	//	Scroll Bar
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		//	Set Chat Log
		g_cChatting->HT_vChatting_SetTextinChatLog();
	}
}
//	FromChatConfig
void CHTChatting::HT_vChatting_InputCheckForChatLogConfig(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID >= 1 && iTargetID <= 6 )
		{
			if( g_cChatting->m_bChat_ChatLogConfig[iTargetID-1] )	g_cChatting->m_bChat_ChatLogConfig[iTargetID-1] = HT_FALSE;
			else													g_cChatting->m_bChat_ChatLogConfig[iTargetID-1] = HT_TRUE;
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, iTargetID, g_cChatting->m_bChat_ChatLogConfig[iTargetID-1] );
			g_cUIManager->HT_HideWindow( _DIALOG_CHATLOGCONFIG );
			//	Set Chat Log
			g_cChatting->HT_vChatting_SetTextinChatLog();
		}
	}
}

//	Change Chat Wnd
HTvoid CHTChatting::HT_vChatting_ChangeChatWnd()
{
	HTint iPosX, iPosY;

	//	ä�� ������ ��Ÿ��
	if( m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )
	{
		m_iChatWindowStyle = CHATWNDSTYLE_TRANSPARANCY;
		g_cUIManager->HT_SetBackgroundColor( _DIALOG_CHATTINGBOX, HT_COLOR(0,0,0,0) );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 51, HT_TRUE );
		//	Set Chat Window Style
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTINGBOX, 9, _T("C2") );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 100, false);
	}
	else if( m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )
	{
		m_iChatWindowStyle = CHATWNDSTYLE_MIDDLESIZE;
		g_cUIManager->HT_GetWindowPos( _DIALOG_CHATTINGBOX, iPosX, iPosY );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTINGBOX );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTING3BOX );
		g_cUIManager->HT_ShowWindow( _DIALOG_CHATTING2BOX );
		g_cUIManager->HT_MoveWindow(_DIALOG_CHATTING2BOX, iPosX, iPosY-50 );
		//	Edit Box 2
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTING2BOX, 1, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTINGBOX, 1 ) );
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTING2BOX, 2, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTINGBOX, 2 ) );
	}
	else if( m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )
	{
		m_iChatWindowStyle = CHATWNDSTYLE_BIGSIZE;
		g_cUIManager->HT_GetWindowPos( _DIALOG_CHATTING2BOX, iPosX, iPosY );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTINGBOX );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTING2BOX );
		g_cUIManager->HT_ShowWindow( _DIALOG_CHATTING3BOX );
		g_cUIManager->HT_MoveWindow(_DIALOG_CHATTING3BOX, iPosX, iPosY );
		//	Edit Box 2
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTING3BOX, 1, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTING2BOX, 1 ) );
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTING3BOX, 2, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTING2BOX, 2 ) );
	}
	else if( m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )
	{
		m_iChatWindowStyle = CHATWNDSTYLE_NORMAL;
		g_cUIManager->HT_GetWindowPos( _DIALOG_CHATTING3BOX, iPosX, iPosY );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTING2BOX );
		g_cUIManager->HT_HideWindow( _DIALOG_CHATTING3BOX );
		g_cUIManager->HT_ShowWindow( _DIALOG_CHATTINGBOX );
		g_cUIManager->HT_SetBackgroundColor( _DIALOG_CHATTINGBOX, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ) );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 51, HT_FALSE );
		g_cUIManager->HT_MoveWindow(_DIALOG_CHATTINGBOX, iPosX, iPosY+50 );

		//	Set Chat Window Style
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATTINGBOX, 9, _T("C1") );
		//	Edit Box 2
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTINGBOX, 1, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTING3BOX, 1 ) );
		g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_CHATTINGBOX, 2, g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHATTING3BOX, 2 ) );

		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 100, true);
	}

	//	Message Display
	g_cChatting->HT_vChatting_SetChatTextList();
	g_cChatting->HT_vChatting_SetSystemTextList();

	//	Set Focus
	this->HT_vChatting_SetFocusOn();
}

//	Set Parse Msg  //fors_debug �ر�����ĵط�
HTvoid CHTChatting::HT_vParseMsg( CHTString strCommand, CHTString strMessage )
{
	//	�޽����� ������.
	if ( strMessage.HT_bIsEmpty() || strMessage.HT_nGetSize() <= 0 )
		return;

	HTtchar* pcMsg;
	HTtchar* token;
    // ������(delimiter)�� �����̽�, ��, ���� ������ ��ū�� �����Ѵ�.
	HTtchar seps[] = " \t\n";

	CHTString strTemp;
	strTemp = strMessage;
	pcMsg = strTemp.HT_szGetString();
	token = _tcstok(pcMsg, seps);

	// HK : ���򸻿� _tcstok()���� NULL�� ���� �� �ִٰ� ���´�. �̰�� ����!
	if ( token == HT_NULL ) return;

	//	ù��° ���� ����
	CHTString strFirstChar;
	strFirstChar.HT_szFormat("%c", token[0] );

	//	�Ľ� �޽�����
	{
		//	ä�ð���
		//	�Ϲ�ä��
		if( strFirstChar.HT_iStringCompare("/") != 0 &&
			( strCommand.HT_iStringCompare( szWhole.HT_szGetString() ) == 0 || strCommand.HT_nGetSize() == 0 ) )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	�Ϲ�ä�� - /��ü || /��
		else if( CHTString::HT_iStringCompare(token, szMsgWhole.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, szMsgWholePart.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, "/s") == 0 )
		{
			token = _tcstok(NULL, "");
			this->HT_vSetData_Normal(token);
		}
		//	�Ϲ� ü�� ����
		else if(CHTString::HT_iStringCompare(token, _T("/��ġ����") )==0 ||
				CHTString::HT_iStringCompare(token, _T("/SavePosition") )==0 )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	�ӼӸ� ä�� - /�ӼӸ� || /��
		else if( CHTString::HT_iStringCompare(token, szMsgWhisper.HT_szGetString() )==0 
				|| CHTString::HT_iStringCompare(token, szMsgWhisperPart.HT_szGetString() )==0
				|| CHTString::HT_iStringCompare(token, "/w")==0 )
		{
			HTtchar* Temptoken = _tcstok(NULL, "");
			this->HT_vSetData_Whisper( token, Temptoken );
		}
		//	��Ƽ ä�� - /��Ƽ || /��
		else if(CHTString::HT_iStringCompare(token, szMsgParty.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgPartyPart.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare(token, "/g")==0 ||
				strCommand.HT_iStringCompare( szParty.HT_szGetString() ) == 0 )
		{
			if( strCommand.HT_iStringCompare( szParty.HT_szGetString() ) != 0 )
			{
                token = _tcstok(NULL, "");
				this->HT_vSetData_Group(token, MESSAGE_PARTY);
			}
			else
			{
				this->HT_vSetData_Group( strMessage, MESSAGE_PARTY );
			}
		}
		//	��� ä�� - /�ƽ��� || /�� || �ƽ���
		else if(CHTString::HT_iStringCompare(token, szMsgAshuram.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgAshuramPart.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare(token, "/gc")==0 ||
				strCommand.HT_iStringCompare( szAshuram.HT_szGetString() ) == 0 )
		{
			if( strCommand.HT_iStringCompare( szAshuram.HT_szGetString() ) != 0 )
			{
                token = _tcstok(NULL, "");
				this->HT_vSetData_Group(token, MESSAGE_GUILD);
			}
			else
			{
				this->HT_vSetData_Group( strMessage, MESSAGE_GUILD );
			}
		}
		//	�ƽ��� ���� - /�� || /���� || �ƽ�������
		else if(CHTString::HT_iStringCompare(token, szMsgAshuramAllince1.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgAshuramAllince2.HT_szGetString() )==0 || 
				strCommand.HT_iStringCompare( szMsgAshuramJoin.HT_szGetString() ) == 0 )
		{
			if( strCommand.HT_iStringCompare( szMsgAshuramJoin.HT_szGetString() ) != 0 )
			{
                token = _tcstok(NULL, "");
				this->HT_vSetData_Group(token, MESSAGE_GUILD_ALLIANCE);
			}
			else
			{
				this->HT_vSetData_Group( strMessage, MESSAGE_GUILD_ALLIANCE );
			}
		}
		//	��ġ�� ä�� - /��ġ�� || /��
		else if(CHTString::HT_iStringCompare(token, szMsgShout.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgShoutPart.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare(token, "/y")==0 )
		{
		}
		//	��� ��ũ ���� - /�ƽ������
		else if( CHTString::HT_iStringCompare(token, szMsgGuildGrade.HT_szGetString() ) ==0 ||
				CHTString::HT_iStringCompare(token, _T("/av") )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildSetRanking( token );
		}
		//	��� ���� ���� - /��������
		else if(CHTString::HT_iStringCompare(token, szMsgGuildNotice.HT_szGetString() )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildUpdate( token );
		}
		else if( CHTString::HT_iStringCompare(token, szMsgChatRoom.HT_szGetString() ) == 0 )
		//else if(CHTString::HT_iStringCompare(token, _T("/ä�ù�") )==0 ) 
		{
			//if( g_iInationalType == INATIONALTYPE_KOREA)	// �ϴ� �ѱ������� ��
			//{
				token = _tcstok(NULL, "");
				
				if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)	// �̹� ä�ù�� �������̶�� �۵����� �ʴ´�.
					return;

				g_cChatRoom->HT_vChatRoom_WindowPopup();
			//}
		}
		else if(CHTString::HT_iStringCompare(token, _T("/�׽�Ʈ") )==0 )
		{/*
			// ���� ���
			RECT rect;
			unsigned char str[65537*2];
			
			for (int i = 1; i < 128; ++i)
			{
				for (int j = 1; j < 256; ++j)
				{
					str[(j*2)+(i*256*2)] = 128;
					str[(j*2)+(i*256*2)+1] = j;
				}
			}
			str[65536*2] = NULL;

			rect.left = 0; rect.top = 0; rect.right = 800; rect.bottom = 400;
//			g_pEngineHandler->HT_hrRenderText(HT_FONT_GULIM_12, (char) str, HT_COLOR(1,1,1,1), rect, TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP);
*/
		}
		//	GM ��ɾ�_ GMȣ��
		else if(CHTString::HT_iStringCompare( token, szMsgAS.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare( token, szMsgAS2.HT_szGetString() )==0)
		{	
			
			if (g_iInationalType == INATIONALTYPE_INDONESIA)
			{
				CHTGMCall	*m_oGMCall = new CHTGMCall;

				CHTString str = _T("");
				token = _tcstok(NULL, "");

				str.HT_szFormat("Processing...");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );

				//_T("http://61.254.146.183/GMCall/GMAppeal.asp?server_no=%s&user_id=%s&user_name=%s&appeal_text=%s");
				HT_vChatting_SetMessage( eURLGMCall	, &str );

				HTint iCallStatus = m_oGMCall->HT_iGMCall(str.HT_szGetString(), g_iConnectServerGroupIndex + g_gServerType , g_strLoginID, g_oMainCharacterInfo.szCharName, token);
				if (iCallStatus==1)		// ����
				{
					HT_vChatting_SetMessage( eMsgGMCallTreat	, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==0) // ����
				{
					HT_vChatting_SetMessage( eMsgGMCallRegist	, &str );
					HTint iCallCound = m_oGMCall->HT_iGetCallCount();
					str.HT_szFormat(str, iCallCound);
				
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==-1)	// ���� ��û
				{
					HT_vChatting_SetMessage( eMsgGMCallReRegist	, &str );
					//str.HT_szFormat("GMȣ�� ������ ��ϵ��� �ʾҽ��ϴ�. �ٽ� ����� �ֽñ� �ٶ��ϴ�.");
				}

				HT_DELETE( m_oGMCall );
			}
		}// GMȣ��Ȯ��
		else if(CHTString::HT_iStringCompare( token, szMsgASCheck.HT_szGetString() )==0 || 
			CHTString::HT_iStringCompare( token, szMsgASCheck2.HT_szGetString() )==0)
		{	 

			if (g_iInationalType == INATIONALTYPE_INDONESIA)
			{
				CHTGMCall	*m_oGMCall = new CHTGMCall;

				CHTString str = _T("");
				token = _tcstok(NULL, "");

				HT_vChatting_SetMessage( eURLGMCallCheck	, &str );	//	str = _T("http://61.254.146.183/GMCall/AppealView.asp?server_no=%s&user_name=%s");
				HTint iCallStatus = m_oGMCall->HT_iGMCallCheck(str.HT_szGetString(), g_iConnectServerGroupIndex + g_gServerType, g_strLoginID, g_oMainCharacterInfo.szCharName);

				if (iCallStatus==1)
				{
					HT_vChatting_SetMessage( eMsgHaveNoGMCall	, &str );
					
					this->HT_vArrangeSavedHistory(str, g_ColorTable[12]);
				}
				else if (iCallStatus==0)
				{
					//str.HT_szFormat(str, iCallCound);
					str.HT_szFormat("GM Reply: %s", m_oGMCall->HT_szGetCallReply());

					//this->HT_vArrangeSavedHistory(str, g_ColorTable[12]);
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				
				HT_DELETE( m_oGMCall );
			}
		}
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildJoin.HT_szGetString() ) == 0)	// �ƽ�������
		{	
			// Step 1. �ڽ��� ���϶������� �����Ͽ� �ƴϸ� �޽��� ����
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg5, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. �ڽ��� �ƽ������� �������� �����Ͽ� �̹� ���� ���¶�� �����޽��� ���
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), _T(" ")) != 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg11, &strString );	// �̹� �ƽ��� ������ ���� �����Դϴ�.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// Step 3. ���ø��� �����Ѵ�.
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg7, &strString );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );

					g_cGuildSystem->m_nAshuramGuildJoinMode = 1;
					g_cInterfaceCheck->HT_vSetCursor(CURSOR_SELECT_ANI);
				}

			}
		}
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildLeave.HT_szGetString() ) == 0)	// �ƽ�������Ż��
		{	
			// Step 1. �ڽ��� ���϶������� �����Ͽ� �ƴϸ� �޽��� ����
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg6, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. �ƽ��� ������ �Ǿ� �ִ� ���������� �����Ѵ�.
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), "") == 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg10, &strString );	// �ƽ��� ������ ���� �ƽ����� �����ϴ�.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// ������ ��Ŷ �����ϱ� (�ź���)
					g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,2,0);
				}
			}

		}
		//	GM ��ɾ�_���� ���
		else if(CHTString::HT_iStringCompare(token, szMsgInvisible.HT_szGetString() )==0)
		{
            if( g_oMainCharacterInfo.snTribe == 0x09 || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( g_oMainCharacterInfo.szCharName, 0x02 );
		}
		//	GM ��ɾ�_Chatting Block
		else if(CHTString::HT_iStringCompare(token, _T("/chatblock") )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( strMessage, 0x04 );
		}
		//	GM ��ɾ�_Ư�� ���� ����
		else if(CHTString::HT_iStringCompare(token, szMsgWarp.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_POSITION( strMessage );
		}
		//	GM ��ɾ�_Ư�� ĳ���� ����
		else if(CHTString::HT_iStringCompare(token, szMsgMove.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( strMessage );
		}
		//	���� Ŭ���̾�Ʈ������ �ڱ��� ĳ���� �Ⱥ��̰� �ϴ� ��¾�
		else if(CHTString::HT_iStringCompare(token, "/jungmanse" )==0)
		{
			g_bTransparencyMode = !g_bTransparencyMode;
			g_cMainCharacter->HT_vMainChar_SetTransparency( 0, 0 );
		}
		else if ( CHTString::HT_iStringCompare( token, _T("/dmap") )==0 )
		{
			if ( g_bDevelopingMode )
			{
				token = _tcstok(NULL, "");
				HTint iLevel = CHTString::HT_iASCIItoInt( token );

				if ( iLevel == 32 )
				{
					g_cStatus->m_sStatus_CharInfo.byLevel = 35;
					g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORTRIMURITICAVE, g_cMainCharacter->HT_vecGetPosition() );
				}
				else if ( iLevel == 64 )
				{
					g_cStatus->m_sStatus_CharInfo.byLevel = 55;
					g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORTRIMURITICAVE, g_cMainCharacter->HT_vecGetPosition() );
				}
				else if ( iLevel == 128 )
				{
					g_cStatus->m_sStatus_CharInfo.byLevel = 65;
					g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORTRIMURITICAVE, g_cMainCharacter->HT_vecGetPosition() );
				}
				else if ( iLevel == 256 )
				{
					g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORCHATURANGR, g_cMainCharacter->HT_vecGetPosition() );
				}
			}
		}
		//else if ( CHTString::HT_iStringCompare( token, _T("/OpenPWeb") ) == 0 )
		//{
		//	CHTString strURLperson_buy; 
		//	HT_g_Script_SetMessage( eURLperson_buy, &strURLperson_buy, _T("") );
		//	g_pEngineHandler->HT_hrOpenWeb( g_hWnd, strURLperson_buy, 10 );
		//}
		//else if ( CHTString::HT_iStringCompare( token, _T("/OpenTWeb") ) == 0 )
		//{
		//	CHTString strWeb;
		//	HT_g_Script_SetMessage( eURLfilling_cash, &strWeb, _T("") );
		//	strWeb += _T("?CashID=");
		//	strWeb += g_strLoginID;
		//	strWeb += _T("&CashPass=");
		//	strWeb += g_strLgoinPasswordMD5;
		//	g_pEngineHandler->JK_hrWebMgr_SetOpenWeb( 0, g_hWnd, strWeb, 10, g_pEngineHandler->HT_iGetScreenWidth()/2-400, g_pEngineHandler->HT_iGetScreenHeight()/2-250, 800, 550 );
		//}
		else if ( CHTString::HT_iStringCompare( token, _T("/AshramCago") ) == 0 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_ASHRAMCAGO);
			g_cGuildSystem->HT_vAshram_CSPAshramItem();
		}
		else if ( CHTString::HT_iStringCompare( token, _T("/SanAshramCago") ) == 0 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_SANCTIONASHCAGO);
		}
		else if ( CHTString::HT_iStringCompare( token, _T("/SetAshramCago") ) == 0 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_SETLEVELASHCAGO);
		}
		//	GM ��ɾ�_�ٸ�ĳ���� ��������
		else if (CHTString::HT_iStringCompare(token, "/INFO")==0)
		{
			// ������ ��Ʈ���� ��� ��ū���� �̾Ƴ�
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharInfo( token );
		}
		//	GM ��ɾ�_�ٸ�ĳ���� �α׾ƿ� ��ų�� - /ű
		else if (CHTString::HT_iStringCompare(token, szMsgKick.HT_szGetString() )==0)
		{
			// ������ ��Ʈ���� ��� ��ū���� �̾Ƴ�
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharClose( token );
		}
		//	GM ��ɾ� - ���Ϸ� ���� �о �Ѳ����� �����
		else if (CHTString::HT_iStringCompare(token, "/IDHANFILE")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				// ������ ��Ʈ���� ��� ��ū���� �̾Ƴ�
				token = _tcstok(NULL, "");

				// ������ �аų� �޽����� �����µ� �����Ͽ���.
				if( token == NULL || FAILED(this->NotifyFromFile(token)) )
				{
					CHTString szMessage;
					HT_vChatting_SetMessage( eMsgCommonSystemFile_Err, &szMessage );
					this->HT_vSaveHistory( 1, szMessage, g_ColorTable[12], g_ColorTable[0]);
				}
			}
		}
		//	GM ��ɾ� ����â���� ����
		else if(CHTString::HT_iStringCompare(token, szMsgWholeNotice.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, "/IDHAN")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09  || g_bDevelopingMode )
            	this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM ��ɾ�_�ý���â�� ����
		else if(CHTString::HT_iStringCompare(token, szMsgNotice.HT_szGetString() )==0 )
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM ��ɾ�_������ �α��� ���� �Ǵ� ����.
		else if(CHTString::HT_iStringCompare(token, "/CHATLOG")==0)
		{
			StartStopLogging();
		}
		//	GM ��ɾ�_// CHAR LOCATION�� ��û�ϴ� �޽����� ����
		else if(CHTString::HT_iStringCompare(token, "/CONNECT")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				token = _tcstok(NULL, "");
				this->HT_vSetData_CharacterLocation( token );
			}
		}
		//	���ӱ��
		//	��ŷ�
		else if(CHTString::HT_iStringCompare(token, "/t")==0 ||
				CHTString::HT_iStringCompare(token, "/T")==0 ||
				CHTString::HT_iStringCompare(token, "/trade")==0 ||
				CHTString::HT_iStringCompare(token, "/TRADE")==0 ||
				CHTString::HT_iStringCompare(token, szTrade.HT_szGetString() )==0 )
		{
			g_cExchangeSystem->HT_vExchange_SetClickTradeButton( HT_TRUE );
		}
		//	/ģ�����
		else if( CHTString::HT_iStringCompare(token, szMsgAddress.HT_szGetString() ) == 0 )
		{
			// ������ ��Ʈ���� ��� ��ū���� �̾Ƴ�
			token = _tcstok(NULL, "");
			g_cAddress->HT_vCSP_JoinAddressBook( token );
		}
		//	��帶ũ ����ġ
		else if(CHTString::HT_iStringCompare(token, szMsgGuildMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vGuild_EmblemSwitch( szMsgGuildMark );
		}
		//	�ֽŸ�ũ ����ġ
		else if(CHTString::HT_iStringCompare(token, szMsgTrimuritiMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vTrimutiri_MarkSwitch( strMessage );
		}
        //	�������� ���������� - /Ż��
		else if( CHTString::HT_iStringCompare(token, "/emerge")==0 || 
				 CHTString::HT_iStringCompare(token, szEmerge.HT_szGetString())==0 )
		{
			if( g_iInationalType != INATIONALTYPE_JAPEN )
			{
				//	/Ż�� 3�ʿ� �ѹ��� ������ �ϱ� ����
				DWORD dwPassTime = timeGetTime();
				if( dwPassTime > m_dwEscapeSaveTime+3000 )
				{
					m_dwEscapeSaveTime = dwPassTime;
					g_pNetWorkMgr->RequestEscape();

					//-----����� �׽�Ʈ�� ���Ͽ�-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_RequestEscape" );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
				}
			}
		}
		// HK : Cheat Key�� ���� �������� ��� �ý��� ���� ������ �����ִ� �κ��� ó���Ѵ�.
		else if ( CHTString::HT_iStringCompare(token, "/@HT") == 0 )
		{
			token = _tcstok( HT_NULL, seps );
			// Render FPS
			if ( CHTString::HT_iStringCompare(token, "showfps") == 0 )
			{
				token = _tcstok( HT_NULL, seps );
				if ( CHTString::HT_iStringCompare(token, "on") == 0 )
				{
					g_bShowFPS.g_bShowFPS = HT_TRUE;
				}
				else if ( CHTString::HT_iStringCompare(token, "off") == 0 )
				{
					g_bShowFPS.g_bShowFPS = HT_FALSE;
				}
			}
			else
			{
			}
		}
		//	������ ��� ����
		else if(CHTString::HT_iStringCompare(token, szMsgBroadcastMode.HT_szGetString() )==0)
		{
			if( g_bGamePlayMovieForGlobal )
				g_bGamePlayMovieForGlobal = HT_FALSE;
			else
				g_bGamePlayMovieForGlobal = HT_TRUE;
		}
		else if(CHTString::HT_iStringCompare(token, szMsgEngineCamera.HT_szGetString() )==0)
		{
			if( g_bUseEngineCamera )
				g_bUseEngineCamera = HT_FALSE;
			else
				g_bUseEngineCamera = HT_TRUE;
		}
		else if(CHTString::HT_iStringCompare(token, szGoCamera.HT_szGetString() )==0)
		{
			if( g_bGoAttackCamera )
                g_bGoAttackCamera = HT_FALSE;
			else
			{
				g_cInterfaceCheck->HT_vInterface_LoadCameraForBroadcast();
				g_bGoAttackCamera = HT_TRUE;
			}
		}
		//	�����ڸ��� ��ȯ
		else if(CHTString::HT_iStringCompare(token, szMsgDebugMode.HT_szGetString() )==0)
		{
			if( g_iInationalType == INATIONALTYPE_INDONESIA ||
				g_iInationalType == INATIONALTYPE_PHILIPPINE || 
				g_iInationalType == INATIONALTYPE_JAPEN )
			{
				if( g_oMainCharacterInfo.snTribe == 0x09 )
				{
					if( g_bDevelopingMode )
						g_bDevelopingMode = HT_FALSE;
					else
						g_bDevelopingMode = HT_TRUE;
				}
			}
			else
			{
				if( g_bDevelopingMode )
					g_bDevelopingMode = HT_FALSE;
				else
					g_bDevelopingMode = HT_TRUE;
			}
		}
		//	������ ��� ����_Ŀ�� ������ �Ⱥ��̰�ó��
		else if(CHTString::HT_iStringCompare(token, szShowCursor.HT_szGetString() )==0)
		{
			static HTint iCursorSw = 1;
			if( iCursorSw == 0 )
			{
				iCursorSw = 1;
				ShowCursor( true );
			}
			else
			{
				iCursorSw = 0;
				ShowCursor( false );
			}
		}
		//	�����ڸ��� ��ȯ
		else if(CHTString::HT_iStringCompare(token, szMsgDuel.HT_szGetString() )==0)
		{
			if( g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				g_pDuelSystem->HT_vDuel_SetDuelMode();
		}
		//	������ UI
		else if(CHTString::HT_iStringCompare(token, _T("/siege") )==0)
		{
			g_cCommand->HT_vCommand_Siege();
		}
		//	�⼮üũ
		else if(CHTString::HT_iStringCompare(token, _T("/Attendance") )==0)
		{
			g_pEventWindow->HT_vEventWindow_ReqAttendance();
		}
		//	�ӼӸ� ä��_�������� �ӼӸ� â�� ���� ������ �ӼӸ��� ����
		else if( strCommand.HT_nGetSize() )
		{
			token = _tcstok(NULL, "");
			this->HT_vSetData_Whisper( strCommand, strMessage );
		}
	}
}
//	Set Focus
HTvoid CHTChatting::HT_vChatting_SetFocusOn()
{ 
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
		return;

	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_FocusOnEditBoxControl( iChatDlgNo, 2 );
	//	Set Language
	//g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );

	//	������ ���ڸ� �־��ش�.
	//m_strChatMessage = g_cUIManager->HT_GetTextEditBoxControl( iChatDlgNo, 2 );
	//g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( m_strChatMessage.HT_szGetString() );
	//g_cImeMgr.InputString();
}
//	Set Focus Off
HTvoid CHTChatting::HT_vChatting_SetFocusOff( HTbool bTrue )
{
	//	Check ä�� �Է� ���
	if( bTrue )
	{
		if( m_bChat_InputMode == HT_TRUE )
			return;
	}

	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	g_cUIManager->HT_FocusOffWindow( iChatDlgNo );
	g_cUIManager->HT_FocusOffEditBoxControl( iChatDlgNo, 2 );
	g_cUIManager->HT_FocusOffEditBoxControl( iChatDlgNo, 1 );
	//	Set Language
	//g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, IME_CMODE_ALPHANUMERIC );
}
//	Set Text List
HTvoid CHTChatting::HT_vChatting_SetChatTextList()
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	HTint iLineCount = 5;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )
	{
		iChatDlgNo = _DIALOG_CHATTINGBOX;
		iLineCount = 5;
	}
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )
	{
		iChatDlgNo = _DIALOG_CHATTINGBOX;
		iLineCount = 5;
	}
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )
	{
		iChatDlgNo = _DIALOG_CHATTING2BOX;
		iLineCount = 14;
	}
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )
	{
		iChatDlgNo = _DIALOG_CHATTING3BOX;
		iLineCount = 14;
	}

	//	ä��â �ʱ�ȭ
	for( HTint i=0 ; i<iLineCount; i++)
		g_cUIManager->HT_SetTextLabelControl( iChatDlgNo, 10+i, _T("") );

	//	ä�� ����Ʈ �˻�
	HTint iChatCount = 0;
	HTbool bChatDisplay = HT_FALSE;
	for( i=m_iChat_ScrollChat ; i<_MAX_SAVED_MESSAGE_NUM; i++)
	{
		bChatDisplay = HT_FALSE;
		//	��ü ���� ������ ����
		if( m_bChat_ConfigChat[0] )
		{
            bChatDisplay = HT_TRUE;
		}
		else
		{
			//	��Ƽ
			if( m_bChat_ConfigChat[1] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_PARTY )
					bChatDisplay = HT_TRUE;
			}
			//	�ƽ���
			if( m_bChat_ConfigChat[2] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
					bChatDisplay = HT_TRUE;
			}
			//	����
			if( m_bChat_ConfigChat[3] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_ALLIANCE )
					bChatDisplay = HT_TRUE;
			}
		}

		if( bChatDisplay )
		{
			g_cUIManager->HT_SetTextLabelControl( iChatDlgNo, CHAT_CHATLAVELINDEX+iChatCount, m_oSavedChatMsg[i].strMsg );
			g_cUIManager->HT_SetTextColorLabelControl( iChatDlgNo, CHAT_CHATLAVELINDEX+iChatCount, m_oSavedChatMsg[i].clrColor );
			iChatCount++;
			if( iChatCount >= iLineCount )
				break;
		}
	}
}
//	Set System Text List
HTvoid CHTChatting::HT_vChatting_SetSystemTextList()
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	for( HTint i=m_iChat_ScrollSystem ; i<m_iChat_ScrollSystem+5; i++)
	{
		g_cUIManager->HT_SetTextLabelControl( iChatDlgNo, CHAT_SYSTEMLAVELINDEX+(i-m_iChat_ScrollSystem), m_oSavedHistory[i].strMsg );
		g_cUIManager->HT_SetTextColorLabelControl( iChatDlgNo, CHAT_SYSTEMLAVELINDEX+(i-m_iChat_ScrollSystem), m_oSavedHistory[i].clrColor );
	}
}

//	About Get Data
//	Get Chat Edit Focus
HTbool CHTChatting::HT_bChatting_GetChatEditFocus()
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	if( g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 1 ) ||
		g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 2 ) )
        return HT_TRUE;
	else
		return HT_FALSE;
}

// IME��带 ���´�
HTint
CHTChatting::HT_iGetIMEMode()
{
	return m_IMEStatus; 
}

//-------------------------------------------------------------------------------
// HTbool HT_vChatting_SetHistoryFunction( WPARAM wParam )
// D : �����丮 ���
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetHistoryFunction( WPARAM wParam )
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	switch( wParam )
	{
		case VK_PRIOR:
			{
				//	�ӼӸ� �Է�â�϶�
				if( g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 1 ) )
				{
					m_iChat_WhisperReadIndex--;
					if( m_iChat_WhisperReadIndex < 0 )	m_iChat_WhisperReadIndex = 9;
					if( m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_bIsEmpty() )
					{
						for( int i=9 ; i>=0 ; i-- )
						{
							if( !m_strWhisperNameList[i].HT_bIsEmpty() )
							{
								m_iChat_WhisperReadIndex = i;
								break;
							}
						}
					}
					if( m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_bIsEmpty() )
						return;
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_szGetString() );
				}
				//	ä�� �޽��� �Է�â�϶�
				else
				{
					m_iChat_HistroyReadIndex--;
					if( m_iChat_HistroyReadIndex < 0 )	m_iChat_HistroyReadIndex = 9;
					if( m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_bIsEmpty() )
					{
						for( int i=9 ; i>=0 ; i-- )
						{
							if( !m_strChat_HistoryMsg[i].HT_bIsEmpty() )
							{
								m_iChat_HistroyReadIndex = i;
								break;
							}
						}
					}
				
					m_strChatMessage = m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_szGetString();
					//	UI �ý��ۿ� ���� ���_�̴�â�� ��üâ�� ��!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
		case VK_NEXT:
			{
				//	�ӼӸ� �Է�â�϶�
				if( g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 1 ) )
				{
					if( m_strWhisperNameList[0].HT_bIsEmpty() )
						return;
					m_iChat_WhisperReadIndex++;
					if( m_iChat_WhisperReadIndex > 9 )	m_iChat_WhisperReadIndex = 0;
					if( m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_bIsEmpty() )	m_iChat_WhisperReadIndex = 0;
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_szGetString() );
				}
				//	ä�� �޽��� �Է�â�϶�
				else
				{
					m_iChat_HistroyReadIndex++;
					if( m_iChat_HistroyReadIndex > 9 )									m_iChat_HistroyReadIndex = 0;
					if( m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_bIsEmpty() )	m_iChat_HistroyReadIndex = 0;
					m_strChatMessage = m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_szGetString();

					//	UI �ý��ۿ� ���� ���_�̴�â�� ��üâ�� ��!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveChatMsg()
// D : �޼��� ����
//-------------------------------------------------------------------------------
HTvoid 
CHTChatting::HT_vSaveChatMsg( HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground )
{
	this->HT_vArrangeSavedChatMsg( iType, sMsg, colorText );
	this->HT_vChatting_SetChatTextList();
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveHistory()
// D : �޼��� ����
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vSaveHistory( HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground )
{
	this->HT_vArrangeSavedHistory(sMsg, colorText);
	this->HT_vChatting_SetSystemTextList();
}

HTvoid
CHTChatting::HT_vSetData_Normal(CHTString sChatMsg)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ����� ä�� ���� �����Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	PS_CSP_REQ_CHAT info = HT_NULL;
	info = new S_CSP_REQ_CHAT;

	//	�ֽ� ����
	info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;
	//	�������
	if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
	{
		info->byBgColor		= 0;
		info->byTextColor	= 13;
	}
	//	�������
	else if( g_cItemControl->HT_bItemControl_GetAssistant() == HT_TRUE )
	{
        info->byBgColor		= 15;
		info->byTextColor	= 12;
	}
	//	GM
	else if( g_oMainCharacterInfo.snTribe == 9 )
	{
		info->byTrimuriti	= 10;
		info->byBgColor		= 0;
		info->byTextColor	= 12;
	}
	//	��� �Ϲ�
	else
	{
		info->byBgColor		= 0;
		info->byTextColor	= 15;
	}

	// �޽����� �ִ� ���� ������ �ʰ� �Ͽ��°�?
	if(strlen(sChatMsg) > MAX_CHAT_LENGTH )
	{
		// �޽����� �ʹ� ��ٴ� �޽���
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );

		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// �������� ���
	else
	{
		CHTString::HT_hrStringCopy(info->szMsg, sChatMsg, MAX_CHAT_LENGTH+1 );
	}

	//	�Ӹ��ۿ�
	g_cMainCharacter->HT_vMainChar_NetWork_ChattingMessage( 0x01, info->szMsg );
	//	ä��â��
	CHTString strMsg;
	strMsg.HT_szFormat( "%s:", g_oMainCharacterInfo.szCharName );
	strMsg += info->szMsg;
	this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_NORMAL, strMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	// �޽��� ������ ������ ��û��
	g_pNetWorkMgr->RequestReqNormalChat( info );

	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Normal()
// D : �Ϲ� ä�� �޽����� �����κ��� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Normal( PS_SCP_NOTIFY_CHAT info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();
	CHTString strSenderName;
	strSenderName.HT_hrCleanUp();

	// ��������� Key ID�� �Ѿ���Ƿ� �װ��� �������� ��������� ID�� ����
	if( info->nID < 10000 )
		strSenderName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->nID );
	else
		g_sNPCSystem->HT_vNPCSystem_GetName( (info->nID-10000), strSenderName );

	// ���� ��� �Ҹ��� ��� �����Ѵ�.
	if(strSenderName.HT_bIsEmpty())return;
	// �ٸ������ ���� �޽���
	if( SERVEROBJECT_IS_CHARACTER( info->nID  ) )
		strCompoundedMsg = strSenderName+_T(": ")+info->szMsg;
	else
		strCompoundedMsg = info->szMsg;

	//	�ֽ��� ���������� �ٸ� �ֽ��� �޽����� Ư������ ó���Ѵ�.
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		//	�ֽ��ڵ� �������ֱ�
		if( info->byTrimuriti == 5 )		info->byTrimuriti = TRIMURITI_BRAHMA;
		else if( info->byTrimuriti == 6 )	info->byTrimuriti = TRIMURITI_VISHNU;
		else if( info->byTrimuriti == 7 )	info->byTrimuriti = TRIMURITI_SIVA;

		if( info->byTrimuriti != g_oMainCharacterInfo.byTrimuriti &&
			info->byTrimuriti <= 4 &&
			g_oMainCharacterInfo.snTribe != 9 )
		{
			strCompoundedMsg.HT_hrCleanUp();
			HTint iStrangLen = strlen(info->szMsg);
			for( HTint i=0; i<iStrangLen ; i++ )
			{
                if( rand()%2 == 0 )		strCompoundedMsg += _T("o");
				else					strCompoundedMsg += _T("O");
			}
		}
	}

	// 0:ä��â, 1:�Ӹ�ǳ��, 2:ä��â�� �Ӹ�ǳ�� ���
	if( info->byWhere == 0 )
	{
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_NORMAL, strCompoundedMsg, 
										g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	}
	else if( info->byWhere == 1 )
	{
		if( info->nID < 10000 )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkChatMsg( info->nID, strCompoundedMsg );
		else
			g_sNPCSystem->HT_vNPCSystem_SetChatMsg( (info->nID-10000), strCompoundedMsg );
	}
	else
	{
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_NORMAL, strCompoundedMsg, 
										g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
		if( info->nID < 10000 )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkChatMsg( info->nID, strCompoundedMsg );
		else
			g_sNPCSystem->HT_vNPCSystem_SetChatMsg( (info->nID-10000), strCompoundedMsg );
	}

	//if( info->byBgColor == 15 )
	//	this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
}

//-------------------------------------------------------------------------------
// Edited by 20021022Tenma
// Description:
//				�ӼӸ� ä��
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Whisper( CHTString token, CHTString sChatMsg )
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ����� ä�� ���� �����Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	//	�и��� ����
	char chName[MAX_CHAT_LENGTH];
	strcpy (chName, "");
	//HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
	//strncpy( tokenMsg, sChatMsg, MAX_CHAT_LENGTH );

	//	token �� �ƹ��͵� ������
	if( token.HT_iStringCompare( szMsgWhisper.HT_szGetString() )==0 || 
		token.HT_iStringCompare( szMsgWhisperPart.HT_szGetString() )==0 || 
		token.HT_iStringCompare( "/w")==0 )
	{
		sscanf( sChatMsg, "%s", chName );
		HTint iLen = strlen(chName);
		HTint iLen2 = sChatMsg.HT_nGetSize();
		char chTemp[MAX_CHAT_LENGTH];
		ZeroMemory( chTemp, MAX_CHAT_LENGTH );
		strncpy( chTemp, sChatMsg.HT_szGetString(), iLen2 );
		strncpy( sChatMsg, chTemp+iLen+1, (iLen2-iLen) );

		this->HT_vChatting_SetWisper( chName );
	}
	else
	{
		sscanf( token, "%s", chName );
		this->HT_vChatting_SetWisper( chName );
	}

	if( strlen( chName ) >= SZNAME_LENGTH )
	{
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, _T("Wrong Name!!!"), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	CHTString strName;
	strName.HT_hrCleanUp();
	PS_CSP_REQ_WHISPER_CHAT info = HT_NULL;
	info = new S_CSP_REQ_WHISPER_CHAT;
	memset( info, 0, sizeof(S_CSP_REQ_WHISPER_CHAT) );
    
	//	�ֽ� ����
	if( g_oMainCharacterInfo.snTribe == 9 )
		info->byTrimuriti = 10;
	else
		info->byTrimuriti = g_oMainCharacterInfo.byTrimuriti;
	info->byBgColor		= 0;
	info->byTextColor	= 3;
	info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;
	strncpy( info->szName, chName, SZNAME_LENGTH );

	if( g_iInationalType == INATIONALTYPE_INDONESIA )
	{
		if( sChatMsg.HT_nGetSize() <= 150 )
		{
			strncpy(info->szMsg, sChatMsg.HT_szGetString(), 150 );
			// �ӼӸ� �޽��� ������ ������ ��û��
			g_pNetWorkMgr->RequestReqWhisperChat(info);
		}
		else
		{
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, _T("Chat Message Size Wrong!!!"), g_ColorTable[12], g_ColorTable[0]);
		}
	}
	else
	{
		strncpy(info->szMsg, sChatMsg.HT_szGetString(), MAX_CHAT_LENGTH );
		// �ӼӸ� �޽��� ������ ������ ��û��
		g_pNetWorkMgr->RequestReqWhisperChat(info);
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_WhisperChatting : %s-%s", info->szName, info->szMsg );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	if (!strcmp(info->szMsg,"/��Ҫ�ֿ�"))  //fors_debug iwant
	 {
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
			{
				g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPING);
				g_cUIManager->HT_ShowWindow( _DIALOG_GOODSKEEPWND );
			}
			else
			{
				//HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError2 );
				//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "���� ���¿����� ����� �� �����ϴ�." );

			}
	}
	if (!strcmp(info->szMsg,"/��Ҫ����"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1302;
		 for (int i=10553 ; i<10569 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	if (!strcmp(info->szMsg,"/��Ҫ88�쾧"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1298;
		 for (int i=10536 ; i<10547 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	 if (!strcmp(info->szMsg,"/��Ҫ����"))
	 {
		 int ibodyid=0;
		 ibodyid	= g_pEngineHandler->HT_iCreateMonster( 2570, HTvector3( 100, 100, 100 ) );
		 			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
			g_pEngineHandler->HT_hrMoveObject(ibodyid, vecTempPos );

	 }

	// �޽����� ���� �縲�� �ڱ� �ڽ��̸� �ڽſ��� ���� �� ���ٴ� �޽����� ����Ѵ�.
	strName = g_oMainCharacterInfo.szCharName;
	if(strName.HT_iStringCompare(chName) == 0)
	{
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_CANNOT_SEND_MYSELF, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_WISPER, strTemp, g_ColorTable[12], g_ColorTable[0]);
		HT_DELETE( info );
		return;
	}
	else
	{
		// �̸��� �̸� ����Ʈ�� �����Ѵ�.
		this->HT_vAddName( 1,  chName );
		//	�׸��� �ӼӸ� â�� �̸��� �����Ѵ�.
		m_strWisperName = chName;
	}

	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper()
// D : �ӼӸ� �޽����� �����κ��� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Whisper( PS_SCP_NOTIFY_WHISPER_CHAT info )
{
	CHTString strCompare;
	CHTString strCompoundedMsg, szMessage;
	strCompare.HT_hrCleanUp();
	strCompoundedMsg.HT_hrCleanUp();

	strCompare = g_oMainCharacterInfo.szCharName;

	//	���������� �ӼӸ� ���� ���
	m_strLastRiciveWisperName = info->szName;
	
	// %s�� �Ӹ�
	m_szMsgName = info->szName;
	HT_vChatting_SetMessage( eMsgCommonChatWhisperReceive, &szMessage );

	// ���� ĳ����(�ڱ� �ڽ�)�� �̸��� �ӼӸ� �޽������� ���� �̸��� ������
	if( strCompare.HT_iStringCompare(info->szName)==0 )
	{
		// ���� �ӼӸ� �޽������� ǥ��
		// %s�� �Ӹ�: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		// �޽����� ����Ѵ� (â�� ������ �ȴ�.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[0]);
	}
	else
	{
		// ���� �Ӽ� �� �޽������� ǥ��
		// %s�� �Ӹ�: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		//	�ֽ��� ���������� �ٸ� �ֽ��� �޽����� Ư������ ó���Ѵ�.
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( info->byTrimuriti != g_oMainCharacterInfo.byTrimuriti &&
				info->byTrimuriti <= 4 &&
				g_oMainCharacterInfo.snTribe != 9 )
			{
				strCompoundedMsg.HT_hrCleanUp();
				HTint iStrangLen = strlen(info->szMsg);
				for( HTint i=0; i<iStrangLen ; i++ )
				{
					if( rand()%2 == 0 )		strCompoundedMsg += _T("o");
					else					strCompoundedMsg += _T("O");
				}
			}
		}

		// �޽����� ����Ѵ� (â�� ������ �ȴ�.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);

		// �̸��� �̸� ����Ʈ�� �����Ѵ�.
		this->HT_vAddName( 2,  info->szName );
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper_Result()
// D : �ӼӸ� �޽����� ���۰���� �����κ��� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveDataResult_Whisper( PS_SCP_RESP_WHISPER_CHAT info )
{
	CHTString strTemp, szMessage;

	switch(info->byResult)
	{
		case 0x00:
		{
			// ���� �ӼӸ� �޽������� ǥ��
			m_szMsgName = m_strWisperName;
			HT_vChatting_SetMessage( eMsgCommonChatWhisperSend, &szMessage ); // %s���� �Ӹ�
			strTemp.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
			// �޽����� ����Ѵ� (â�� ������ �ȴ�.)
			this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strTemp, 
									g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
		}
			break;
		case REPLY_WHISPER_CHAR_FAIL:
			HT_vChatting_SetMessage( eMsgCommonChatWhisperNotSend, &szMessage ); // %s���� �Ӹ�
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, szMessage, g_ColorTable[6], g_ColorTable[0]);
			break;
		case REPLY_WHISPER_REJECT :
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, _T("�˼��մϴ�. ���� �ٸ� ���� ������ �Ӹ� ��㿡 ���� �� �����ϴ�."), g_ColorTable[6], g_ColorTable[0]);
			break;
		default:;
	}
}

//-------------------------------------------------------------------------------
// Add by 20021130Tenma
// Description:
//					�׷� ä��
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Group(CHTString sChatMsg, HTbyte byMsgType)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ����� ä�� ���� �����Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	MSG_Chat* info = HT_NULL;
	info = new 	MSG_Chat;

	info->byMsgType		= byMsgType;
	info->byBgColor		= 0;
	info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;

	//	��Ƽ
	if( info->byMsgType == MESSAGE_PARTY )
		info->byTextColor	= 7;
	//	���
	else if( info->byMsgType == MESSAGE_GUILD )
		info->byTextColor	= 5;
	//	�ƽ�������
	else if( info->byMsgType == MESSAGE_GUILD_ALLIANCE )
		info->byTextColor	= 6;

	// �޽����� �ִ� ���� ������ �ʰ� �Ͽ��°�?
	if( sChatMsg.HT_nGetSize() > MAX_GROUPCHAT_LENGTH )
	{
		// �޽����� �ʹ� ��ٴ� �޽���
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// �������� ���
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_GROUPCHAT_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// �޽��� ������ ������ ��û��
		g_pNetWorkMgr->RequestGroupChat( info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_NotifyMessage()
// D : �������� �޽����� ������ �����Ѵ�.
//  
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_NotifyMessage(CHTString sChatMsg)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ����� ä�� ���� �����Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	MSG_Broadcast* info = HT_NULL;
	info = new MSG_Broadcast;

	info->byMsgType		= 1;
	info->byBgColor		= 0;			    // ä�� �޼��� ����
	info->byTextColor	= 15;			    // ä�� �޼��� ����
	info->byTrimuriti	= 0;

	// �޽����� �ִ� ���� ������ �ʰ� �Ͽ��°�?
	if( sChatMsg.HT_nGetSize() > MAX_NOTIFY_LENGTH )
	{
		// �޽����� �ʹ� ��ٴ� �޽���
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_MESSAGEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// �������� ���
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_NOTIFY_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// �޽��� ������ ������ ��û��
		g_pNetWorkMgr->ReqNotifyMessage( info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_GlobalNotifyMessage()
// D : �����忡 ���������� ������.
//  
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_GlobalNotifyMessage( CHTString sChatMsg )
{
}

HTvoid
CHTChatting::HT_vReceiveData_Group( MSG_Chat* info )
{
	if( info->byMsgType == MESSAGE_PARTY )
	{
		CHTString strCompoundedMsg;
		strCompoundedMsg.HT_hrCleanUp();

		// ��Ƽ�� �޽������� ǥ��
		// [��Ƽ]
		HT_vChatting_SetMessage( eMsgCommonSystemParty, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	�ֽ��� ���������� �ٸ� �ֽ��� �޽����� Ư������ ó���Ѵ�.
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( info->byTrimuriti != g_oMainCharacterInfo.byTrimuriti )
			{
				strCompoundedMsg.HT_hrCleanUp();
				HTint iStrangLen = strlen(info->szMsg);
				for( HTint i=0; i<iStrangLen ; i++ )
				{
					if( rand()%2 == 0 )		strCompoundedMsg += _T("o");
					else					strCompoundedMsg += _T("O");
				}
			}
		}

		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_PARTY, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	}
	else if( info->byMsgType == MESSAGE_GUILD )
	{
		CHTString strCompoundedMsg;
		strCompoundedMsg.HT_hrCleanUp();

		// �ƽ��� �޽������� ǥ��
		// [�ƽ���]
		HT_vChatting_SetMessage( eMsgCommonSystemAshuram, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	�ֽ��� ���������� �ٸ� �ֽ��� �޽����� Ư������ ó���Ѵ�.
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( info->byTrimuriti != g_oMainCharacterInfo.byTrimuriti )
			{
				strCompoundedMsg.HT_hrCleanUp();
				HTint iStrangLen = strlen(info->szMsg);
				for( HTint i=0; i<iStrangLen ; i++ )
				{
					if( rand()%2 == 0 )		strCompoundedMsg += _T("o");
					else					strCompoundedMsg += _T("O");
				}
			}
		}

		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_ASHRAM, strCompoundedMsg , g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	}
	else if( info->byMsgType == MESSAGE_GUILD_ALLIANCE )
	{
		CHTString strCompoundedMsg;
		strCompoundedMsg.HT_hrCleanUp();

		// ��Ƽ�� �޽������� ǥ��
		// [�ƽ���]
		HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoinBrackets, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	�ֽ��� ���������� �ٸ� �ֽ��� �޽����� Ư������ ó���Ѵ�.
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( info->byTrimuriti != g_oMainCharacterInfo.byTrimuriti )
			{
				strCompoundedMsg.HT_hrCleanUp();
				HTint iStrangLen = strlen(info->szMsg);
				for( HTint i=0; i<iStrangLen ; i++ )
				{
					if( rand()%2 == 0 )		strCompoundedMsg += _T("o");
					else					strCompoundedMsg += _T("O");
				}
			}
		}

		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_ALLIANCE, strCompoundedMsg , g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Notify()
// D : �������� �޽����� �����κ��� �����Ѵ�.
//     S_SCP_NOTIFY_MESSAGE.szName�� �������׿��� ������� �����Ƿ� �Ŀ� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Notify( MSG_Broadcast* info )
{
	//	����NPC�˸޽���(7) ������ɼ�(4), ȣ��(5)�϶�
	if( info->byMsgType == 7 || info->byMsgType == 4 || info->byMsgType == 5 )
	{
		//	���� �ֽ��� �ƴϸ� ��ŵ
		if( info->byMsgType == 4 )
		{
			if( g_oMainCharacterInfo.byTrimuriti != info->byTrimuriti )
				return;
		}
		//	���÷��� ���� �ƴҶ�
		if( m_fOpenTextPosX == -999 )
		{
			m_fOpenTextPosX = (HTfloat)g_pEngineHandler->HT_iGetScreenWidth();
			m_iOpenRotateCount = 0;
			m_oOpenMessageSave[0].bExistSw = HT_TRUE;
			m_oOpenMessageSave[0].byMsgType = info->byMsgType;
			m_oOpenMessageSave[0].strMsg = info->szMsg;
			m_oOpenMessageSave[0].strMsg += _T(" : [");
			m_oOpenMessageSave[0].strMsg += info->szName;
			m_oOpenMessageSave[0].strMsg += _T("]");
			if( info->byMsgType == 7 )	m_oOpenMessageSave[0].strSenChar.HT_hrCleanUp();
			else						m_oOpenMessageSave[0].strSenChar = info->szName;
			//	Set Open Message
			this->HT_vChatting_SetOpenMeg( m_oOpenMessageSave[0].strMsg );
		}
		//	���÷��� �� �ϴ�
		else
		{
			for( int i=0 ; i<OPENMESSAGE_MAX_COUNT ; i++ )
			{
				if( m_oOpenMessageSave[i].bExistSw == HT_FALSE )
				{
					m_oOpenMessageSave[i].bExistSw = HT_TRUE;
					m_oOpenMessageSave[i].byMsgType = info->byMsgType;
					m_oOpenMessageSave[i].strMsg = info->szMsg;
					m_oOpenMessageSave[i].strMsg += _T(" : [");
					m_oOpenMessageSave[i].strMsg += info->szName;
					m_oOpenMessageSave[i].strMsg += _T("]");
					if( info->byMsgType == 7 )	m_oOpenMessageSave[i].strSenChar.HT_hrCleanUp();
					else						m_oOpenMessageSave[i].strSenChar = info->szName;
					//	Set Open Message
					this->HT_vChatting_SetOpenMeg( m_oOpenMessageSave[i].strMsg );
					return;
				}
			}
		}
	}
	else
	{
		//	���� �޽����� ������ ���带 Ʋ���ش�.
		//	�ֽż��� �޽����� �ƴҶ�
		if( info->byBgColor != 14 )
			g_pEngineHandler->HT_hrPlaySound( 33509, 3 );

		//	����
		CHTString szNotice, szMsgWholeNotice;
		HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szNotice );
		HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /��ü����
		
		if( strncmp( info->szMsg, "/IDHAN", strlen("/IDHAN") ) == 0 ||
			strncmp( info->szMsg, szMsgWholeNotice.HT_szGetString(), szMsgWholeNotice.HT_nGetSize() ) == 0 ||
			info->byMsgType == MESSAGE_SERVERMSG )
		{
			int iMinusNum = 7;
			if( strncmp( info->szMsg, "/IDHAN", strlen("/IDHAN") ) == 0 )
				iMinusNum = 7;
			else
				iMinusNum = szMsgWholeNotice.HT_nGetSize();

			memmove( info->szMsg, info->szMsg+iMinusNum, MAX_NOTIFY_LENGTH-iMinusNum );
			//	����â ��
			g_pNotifyWindow->HT_vNotify_SetOn();
			g_pNotifyWindow->HT_vNotify_SetText( info->szMsg );

			if( info->byMsgType != MESSAGE_SERVERMSG )
			{
				szNotice += info->szMsg;

				int Length = sizeof(info->szMsg);
				char szNotipy[1024];

				szNotice += info->szMsg;
				if( szNotice.HT_nGetSize() < 256 )			//	����� �����Ҷ��� �ý���â�� ����
				{
					//	[����]
					CHTString strTemp;
					HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
					for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
					{
						//	�ý���â�� ����
						szNotipy[Dsc++] = info->szMsg[Orj];
						if (info->szMsg[Orj] == '>' && info->szMsg[Orj+1] == '>')
						{
							szNotipy[Dsc-1] = NULL;
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szNotipy );
							Dsc=0; Orj++;
						}
					}
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szNotipy );
				}
			}
		}
		//	"/����"
		else if( strncmp( info->szMsg, szNotice.HT_szGetString(), szNotice.HT_nGetSize() ) == 0 ||
				 strncmp( info->szMsg, _T("/notice"), strlen("/notice") ) == 0 )
		{
			if( strncmp( info->szMsg, szNotice.HT_szGetString(), szNotice.HT_nGetSize() ) == 0 )
                memmove( info->szMsg, info->szMsg+(szNotice.HT_nGetSize()+1), MAX_NOTIFY_LENGTH-(szNotice.HT_nGetSize()+1) );
			else
				memmove( info->szMsg, info->szMsg+(strlen("/notice")+1), MAX_NOTIFY_LENGTH-(strlen("/notice")+1) );
			szNotice += info->szMsg;

			int Length = sizeof(info->szMsg);
			char szNotipy[1024];

			szNotice += info->szMsg;
			if( szNotice.HT_nGetSize() < 256 )			//	����� �����Ҷ��� �ý���â�� ����
			{
				//	[����]
				CHTString strTemp;
				HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );

				for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
				{
					//	�ý���â�� ����
					szNotipy[Dsc++] = info->szMsg[Orj];
					if (info->szMsg[Orj] == '>' && info->szMsg[Orj+1] == '>')
					{
						szNotipy[Dsc-1] = NULL;
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szNotipy );
						Dsc=0; Orj++;
					}
				}
				if( info->byBgColor == 14 )
					this->HT_vSaveHistory(HISTORY_MESSAGE_TYPE_NOTIFY, info->szMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor] );
				else
                    g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szNotipy );
			}
		}
		else
		{
			//	�ֽż��� �޽����϶�
			if( info->byBgColor == 14 )
			{
				//	�ý��� â���� ����
				this->HT_vSaveHistory(HISTORY_MESSAGE_TYPE_NOTIFY, info->szMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor] );
			}
		}
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_History()
// D : �����丮 �޽����� �����κ��� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_History( PS_SCP_RESP_CHAR_HISTORY info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();

	// �ð� �߰� ǥ���� ��.
	// �������� �޽������� ǥ��
	//strCompoundedMsg = _T("[�����丮�׽�Ʈ] ");
	HT_vChatting_SetMessage( eMsgCommonSystemHistory, &strCompoundedMsg );
	strCompoundedMsg = strCompoundedMsg+info->szContent;
	this->HT_vSaveHistory(info->wType, strCompoundedMsg, g_ColorTable[4], g_ColorTable[4]);

	HT_Trace(strCompoundedMsg);
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_ReqCharInfo( CHTString strCharname )
// D: GM�� �ٸ�ĳ������ ������ ��û�Ѵ�.
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vSetData_ReqCharInfo( CHTString strCharname )
{
	PS_CSP_REQ_CHAR_INFO info = HT_NULL;
	info = new S_CSP_REQ_CHAR_INFO;
	CHTString::HT_hrStringCopy(info->szCharName, strCharname, SZNAME_LENGTH );
	g_pNetWorkMgr->RuquestCharacterInfo( info );
	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_ReqCharInfo( CHTString strCharname )
// D: GM�� �ٸ�ĳ������ ���� ���� ��Ų��.
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vSetData_ReqCharClose( CHTString strCharname )
{
	MSG_GMKickPlayer* info = HT_NULL;
	info = new MSG_GMKickPlayer;
	CHTString::HT_hrStringCopy(info->szCharName, strCharname.HT_szGetString(), SZNAME_LENGTH );
	g_pNetWorkMgr->RuquestCloseCharacter( info );
	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid NotifyFromFile( CHTString strFilename )
// D: ���Ϸ� ���� ���������� ������ ���������� �����Ѵ�.
// ���������� ���� ������� Ŭ���̾�Ʈ�� ���´ٰ� �޽����� �� ������ �Ѳ����� ǥ�� �� �ش�.
//-------------------------------------------------------------------------------
HTRESULT
CHTChatting::NotifyFromFile( CHTString strFilename )
{
	FILE		*fp;
	HTtchar		in;			// �о� �� ����Ʈ
	HTint		iCount = 1;	// MAX_CHAT_LENGTH ��ŭ ���ڸ� ī��Ʈ��
	HTtchar		inBytes[ MAX_CHAT_LENGTH+1 ];	// �о� �� ����Ʈ�� MAX_CHAT_LENGTH����Ʈ���� ����
	CHTString	strTemp;

	fp = fopen((HTtchar *)strFilename, "rt");
	// ������ ����, ���� �������� ������ ǥ���Ѵ�.
	if( fp == NULL )
		return HT_FAIL;

	this->HT_vSetData_NotifyMessage( CHTString( "//START NOTIFY MESSAGE//" ) );
	
	//	�޽��� ���۸� �ʱ�ȭ�ϰ�
	ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );

	while( (in = fgetc(fp)) != EOF )
	{
		inBytes[ iCount-1 ] = in;

		// MAX_CHAT_LENGTH ���ڱ��� �Է� ���� �� ���� ���̰� �޽����� �����Ѵ�.
		if( iCount >= MAX_CHAT_LENGTH )
		{	
			// �������� �ѱ� ����Ʈ�� �ƴ� ���� ��ü�� ī���Ͽ� ������
			if( in >= '!' && in <= '~' ) 
			{
				inBytes[ iCount ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	�޽��� ���۸� �ʱ�ȭ�ϰ�
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				
				// ī��Ʈ�� �ʱ�ȭ
				iCount = 1;
				
			}
			// �������� �ѱ� ����Ʈ�� ��쿡�� �� ����Ʈ�� ������ ù��°�� �����ϰ� �� ����Ʈ�� �����ϰ� ������
			// ���� �ѱ� ����Ʈ�� �������� ���� ����.
			else
			{
				inBytes[ iCount-1 ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	�޽��� ���۸� �ʱ�ȭ�ϰ�
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				// �迭�� ó���� �ѱ� �չ���Ʈ�� �־���� ī��Ʈ�� �ʱ�ȭ
				inBytes[0] = in;
				iCount = 2;
			}
		}
		// MAX_CHAT_LENGTH ���ڰ� ���� �ʾ����� ī��Ʈ �Ѵ�.
		else
			iCount ++;
	}

	//	������ �ݰ�
	fclose( fp );

	// ���� ����Ʈ�鵵 ����
	inBytes[ iCount ] = '\0';
	strTemp.HT_szFormat("%s", inBytes);
	this->HT_vSetData_NotifyMessage( strTemp );
	this->HT_vSetData_NotifyMessage( CHTString( "//END NOTIFY MESSAGE//" ) );

	return HT_OK;
}



//-------------------------------------------------------------------------------
// HTvoid StartStopLogging( CHTString strFilename )
// D: ä�÷α� ������ ������ ����/ �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::StartStopLogging()
{
	CHTString strTemp;

	// ä�� �α� ���¸� �ٲ۴�. ���� ���̿��ٸ� �׸��д�
	if(m_bLogging)
	{
		HTint iRCode;
		
		// ������ ���� �ִٸ� ����.
		if(m_pLogFile != NULL)
		{

			struct tm *today;
			char charTimeBuffer[MAX_TIMESTAMP_SIZE];
			time_t tTimeDifference;
			time_t tCurrentTime;

			// ���� �ð��� ���Ѵ�.
			time( &tCurrentTime );
			// ���� �ð��� Initialize Time�� �� �ð��� ���̸� ���Ͽ� ���� ���� �ð��� ���Ѵ�.
			tTimeDifference = g_tInitServerTime + ( g_tInitClientTime - tCurrentTime );

			// ���� ���� �����ð��� ������ tm ����ü�� �����Ѵ�.
			today = localtime( &tTimeDifference );
			strftime( charTimeBuffer, MAX_TIMESTAMP_SIZE, "[%Y/%m/%d %H:%M:%S]", today );

			// ��ȭ ���� ������ �������� ���Ͽ� ǥ��
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
			fprintf( m_pLogFile, "%s %s\n",charTimeBuffer, strTemp.HT_szGetString() );
			fflush( m_pLogFile );

			// �ݴ� ��Ŀ�� ���Ͽ� ǥ��, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n\n");
			fflush( m_pLogFile );

			iRCode = fclose( m_pLogFile );
		}
		if(iRCode == 0)
		{
			m_pLogFile = NULL;
			m_bLogging = HT_FALSE;
			//strTemp = "��ȭ ������ ������ �����մϴ�.";
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
		}
		else //strTemp = "�α� ������ �ݴµ� ���� �Ͽ����ϴ�. ��ȭ ������ ��� �����մϴ�.";			
			HT_vChatting_SetMessage( eMsgChatLogFileCloseErr, &strTemp );
	}
	// ���� ���� �ƴ϶�� ������ �����Ѵ�.
	else
	{
		// ������ ���� �ִٸ� ����.
		if( m_pLogFile == NULL )
		{
			m_pLogFile = fopen( "chat_log.txt", "at+" );
			// ������ ���°�� (�� �Լ����� NULL �� ���ϵȴ�)
			if( m_pLogFile == NULL ) m_pLogFile = fopen( "chat_log.txt", "w" );
		}
		// ���������� ������ ������.
		if( m_pLogFile )
		{
			// ���� ��Ŀ�� ���Ͽ� ǥ��, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n");
			fflush( m_pLogFile );
			//strTemp = "��ȭ ������ ���Ϸ� �����մϴ�.";
			HT_vChatting_SetMessage( eMsgChatSaveStart, &strTemp );
			m_bLogging = HT_TRUE;
		}
		// ������ ���µ� ���� �Ͽ���.
		else //strTemp = "�α� ������ ���µ� �����Ͽ����ϴ�. ��ȭ ���� ������ ���� �� �� �������ϴ�.";
			HT_vChatting_SetMessage( eMsgChatLogFileOpenErr, &strTemp );
	}
	this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
}


//-------------------------------------------------------------------------------
// HTvoid addName( HTint type, CHTString strName )
// D: ä�� ��� �̸� ����Ʈ�� �̸��� ����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vAddName( HTint type, CHTString strName )
{
	//	���� �̸� �O��
	for( HTint i= 0 ;i<m_iNameListNum ; i++ )
	{
		if( strName.HT_iStringCompare( m_strWhisperNameList[i] ) == 0 )
			return;
	}

	//	���� 9���� ������
	if( m_iNameListNum >= 9 )
	{
		m_iNameListNum = 8;
		for( i=0 ; i<8 ; i++ )
		{
			m_strWhisperNameList[i] = m_strWhisperNameList[i+1];
		}
	}

	m_strWhisperNameList[i] = strName;
	m_iNameListNum++;
	for( HTint i=1; i<_CHAT_CHAT_USER_NUM ; ++i )
	{
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_WHISPERLISTWND, i+1, m_strWhisperNameList[i-1] );
	}
}


//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_CharacterLocation( HTtchar* pcharName )
// D: ������ ĳ���� ��ġ ������ ��û��
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_CharacterLocation( HTtchar* pcharName )
{
	PS_CSP_REQ_CHAR_LOCATION s_CSP_REQ_CHAR_LOCATION = new S_CSP_REQ_CHAR_LOCATION;
    
	if(!pcharName){
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_NO_NAME, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// �޽����� �ִ� ���� ���̺��� �� ���
	else if(strlen(pcharName) > SZNAME_LENGTH){
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_NAMEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// �������� ���
	else
	{
		S_GCSP_REQ_CHARACTER_SEARCH* info = HT_NULL;
		info = new S_GCSP_REQ_CHARACTER_SEARCH;
		// ������ ����, �����Ѵ�.
		CHTString::HT_hrStringCopy(info->szCharName, pcharName, SZNAME_LENGTH+1);
		// ������ ĳ���� ��ġ ������ ��û��
		g_pNetWorkMgr->RequestReqCharLocation( info );
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send__CHARACTER_SEARCH: %s", info->szCharName );
		//if(	g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		HT_DELETE( info );
	}
}


//-------------------------------------------------------------------------------
// HTvoid HT_vChatting_SetWisper( CHTString )
// D : �ܺο��� �ӼӸ� ���¸� �����Ѵ�.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetWisper( CHTString strWisperName )
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	// ���� ����� �̸��� �ӼӸ� ����̸����� �����Ѵ�.
	m_strWisperName			= strWisperName;
    // Edit No 1
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWisperName.HT_szGetString() );
	m_strChatMessage.HT_hrCleanUp();
}


//-------------------------------------------------------------------------------
// ...
// D : �ӼӸ� ��ȭ��� �����ϴ� ��ȭ���� ��Ʈ��
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_Whisper_Dlg_Check()
{
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_WHISPERLISTWND ) )
	{
		m_bNameListActive = HT_TRUE;

		//	ä�� ������ ��Ÿ��
		HTint iChatDlgNo;
		if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
		else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
		else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
		else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( iChatDlgNo, iPosX, iPosY );
		g_cUIManager->HT_ShowWindow( _DIALOG_WHISPERLISTWND );
		if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTINGBOX ) )	g_cUIManager->HT_MoveWindow( _DIALOG_WHISPERLISTWND, iPosX+27, iPosY+70 );
		else														g_cUIManager->HT_MoveWindow( _DIALOG_WHISPERLISTWND, iPosX+27, iPosY+120 );
	}
	else
	{
		m_bNameListActive = HT_FALSE;
		g_cUIManager->HT_HideWindow( _DIALOG_WHISPERLISTWND );
	}
}
	
//-------------------------------------------------------------------------------
// HT_vArrangeSavedChatMsg(), HT_vArrangeSavedHistory()
// D : ����� �޼����� �����丮 ����
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vArrangeSavedChatMsg(HTint iType, CHTString strMsg, HT_COLOR clrColor)
{
	HTint i;
	HTint iStrlen = strMsg.HT_nGetSize();
	HTint iTempCount1 = 0;
	HTint iTempCount2 = 0;
	int iStrlength;
	char szMsg[512];
	char szTemp[512];
	HTbool bTrue;

	ZeroMemory( szTemp, 512 );
	ZeroMemory( szMsg, 512 );
	strncpy( szMsg, strMsg.HT_szGetString(), iStrlen );
	while( iTempCount2 < iStrlen )
	{
		bTrue = HT_FALSE;
		//	���ڸ� ����
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ������ ����Ʈ�� ������ ������ �ƴѰ�쿡��
		int iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );
		while ( iResult == 0 && iTempCount2<iStrlen )
		{
			iTempCount1++;
			iTempCount2++;
			szTemp[iTempCount1] = szMsg[iTempCount2];
			iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );

			iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
			if( iStrlength > 380 )
			{
				if( iResult == 0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
					szTemp[iTempCount1] = szMsg[iTempCount2];
					bTrue = HT_TRUE;
				}
				break;
			}
		}
		iTempCount1++;
		iTempCount2++;

		iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
		if( iStrlength > 380 || bTrue == HT_TRUE )
		{
			//	�ܾ������ ������ �ʿ��� ���, ���� ���ڸ� �ľ��Ͽ� ���� ���ڱ��� �ٽ� �ǵ�����.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	�ʸ���
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	�ε��׽þ�
			{
				char szTemp2[512];
				HTint iTempCount3 = iTempCount1;
				ZeroMemory( szTemp2, 512 );
				strncpy( szTemp2, szTemp, iTempCount1 );
				while( szTemp[iTempCount1]!=' ' && iTempCount1>0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
				}
				if( iTempCount1 == 0 )
				{
					iTempCount1 = iTempCount3;
					iTempCount2 = iTempCount3;
					strncpy( szTemp, szTemp2, iTempCount1 );
				}
			}

			//	ù��° ����
			for( i=(_MAX_SAVED_MESSAGE_NUM-2); i>=0; i-- )
			{
				m_oSavedChatMsg[i+1].iType		= m_oSavedChatMsg[i].iType;
				m_oSavedChatMsg[i+1].strMsg		= m_oSavedChatMsg[i].strMsg;
				m_oSavedChatMsg[i+1].clrColor	= m_oSavedChatMsg[i].clrColor;
			}
			m_oSavedChatMsg[0].iType		= iType;
			m_oSavedChatMsg[0].strMsg		= szTemp;
			m_oSavedChatMsg[0].clrColor		= clrColor;
			//	Set Chat Log
			this->HT_vChatting_SetChatLog( iType, m_oSavedChatMsg[0].strMsg, clrColor );

			ZeroMemory( szTemp, 512 );
			iTempCount1 = 0;
		}
	}
	if( strlen( szTemp ) > 0 )
	{
		for( i=(_MAX_SAVED_MESSAGE_NUM-2); i>=0; i-- )
		{
			m_oSavedChatMsg[i+1].iType		= m_oSavedChatMsg[i].iType;
			m_oSavedChatMsg[i+1].strMsg		= m_oSavedChatMsg[i].strMsg;
			m_oSavedChatMsg[i+1].clrColor	= m_oSavedChatMsg[i].clrColor;
		}
		m_oSavedChatMsg[0].iType		= iType;
		m_oSavedChatMsg[0].strMsg		= szTemp;
		m_oSavedChatMsg[0].clrColor		= clrColor;
		//	Set Chat Log
		this->HT_vChatting_SetChatLog( iType, m_oSavedChatMsg[0].strMsg, clrColor );
	}
}

HTvoid
CHTChatting::HT_vArrangeSavedHistory(CHTString strHistory, HT_COLOR clrColor)
{
	HTint i;
	HTint iStrlen = strHistory.HT_nGetSize();
	HTint iTempCount1 = 0;
	HTint iTempCount2 = 0;
	int iStrlength;
	char szMsg[512];
	char szTemp[512];
	HTbool bTrue;

	ZeroMemory( szTemp, 512 );
	ZeroMemory( szMsg, 512 );
	strncpy( szMsg, strHistory.HT_szGetString(), iStrlen );
	while( iTempCount2 < iStrlen )
	{
		bTrue = HT_FALSE;
		//	���ڸ� ����
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ������ ����Ʈ�� ������ ������ �ƴѰ�쿡��
		int iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );
		while ( iResult == 0 && iTempCount2<iStrlen )
		{
			iTempCount1++;
			iTempCount2++;
			szTemp[iTempCount1] = szMsg[iTempCount2];
			iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );

			iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
			if( iStrlength > 380 )
			{
				if( iResult == 0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
					szTemp[iTempCount1] = szMsg[iTempCount2];
					bTrue = HT_TRUE;
				}
				break;
			}
		}
		iTempCount1++;
		iTempCount2++;

		iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
		if( iStrlength > 380 || bTrue == HT_TRUE )
		{
			//	�ܾ������ ������ �ʿ��� ���, ���� ���ڸ� �ľ��Ͽ� ���� ���ڱ��� �ٽ� �ǵ�����.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	�ʸ���
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	�ε��׽þ�
			{
				char szTemp2[512];
				HTint iTempCount3 = iTempCount1;
				ZeroMemory( szTemp2, 512 );
				strncpy( szTemp2, szTemp, iTempCount1 );
				while( szTemp[iTempCount1]!=' ' && iTempCount1>0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
				}
				if( iTempCount1 == 0 )
				{
					iTempCount1 = iTempCount3;
					iTempCount2 = iTempCount3;
					strncpy( szTemp, szTemp2, iTempCount1 );
				}
			}

			//	ù��° ����
			for( i=(_MAX_SAVED_HISTORY_NUM-2); i>=0; i-- )
			{
				m_oSavedHistory[i+1].strMsg		= m_oSavedHistory[i].strMsg;
				m_oSavedHistory[i+1].clrColor	= m_oSavedHistory[i].clrColor;
			}
			m_oSavedHistory[0].strMsg		= szTemp;
			m_oSavedHistory[0].clrColor		= clrColor;
			//	Set Chat Log
			this->HT_vChatting_SetChatLog( CHAT_MESSAGE_TYPE_SYSTEM, m_oSavedHistory[0].strMsg, clrColor );

			ZeroMemory( szTemp, 512 );
			iTempCount1 = 0;
		}
	}
	if( strlen( szTemp ) > 0 )
	{
		for( i=(_MAX_SAVED_HISTORY_NUM-2); i>=0; i-- )
		{
			m_oSavedHistory[i+1].strMsg		= m_oSavedHistory[i].strMsg;
			m_oSavedHistory[i+1].clrColor	= m_oSavedHistory[i].clrColor;
		}
		m_oSavedHistory[0].strMsg		= szTemp;
		m_oSavedHistory[0].clrColor		= clrColor;
		//	Set Chat Log
		this->HT_vChatting_SetChatLog( CHAT_MESSAGE_TYPE_SYSTEM, m_oSavedHistory[0].strMsg, clrColor );
	}
}

//-------------------------------------------------------------------------------
// HTvoid						HT_hrSelectChar();
// D : ���������� �ӼӸ� ���� ���
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vChatting_SetLastSendWisper()
{
	//	ä�� ������ ��Ÿ��
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	CHTString szCommand;
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper, &szCommand ); // /�ӼӸ�

	m_strChatMessage = szCommand;
	m_strChatMessage += _T(" ");
	m_strChatMessage += m_strLastRiciveWisperName.HT_szGetString();
	m_strChatMessage += _T(" ");

	//	Edit Box 2
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
	g_cImeMgr.vImeMgr_SetLimitRecivewParam( 1 );

	//	ä�� �Է� Ȱ��ȭ
	//	Set Focus
	this->HT_vChatting_SetFocusOn();
}

HTvoid CHTChatting::HT_vChatting_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vChatting_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vChatting_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vChatting_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vChatting_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vChatting_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vChatting_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid CHTChatting::HT_vChatting_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// ����
		case eMsgParamZoneNum	:	
			pszParam->HT_szFormat( "%d", m_iMessageVal ); break;
		// �ٸ� ĳ���� �̸�
		case eMsgParamOthercharName :
			*pszParam = m_szMsgName;
			break;

		default:
			break;
	}
}

//-------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetOpenMessageItem( HTbyte byMsgType, HTint iItemIndex, HTbyte byItemKeyID )
{
	//	���μ����� ���������� ������ ��� ���ϰ� �Ѵ�.
	if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
		return;

	//	Open Msg Type
	//	0:����, 1:�ƽ����̸�, 2:������, 3:������ɼ�
	m_byChat_OpenMsgType = byMsgType;
	CHTString strTemp;
	if( m_byChat_OpenMsgType == 1 )
	{
		//	�ƽ��� �̸��� �Է��� �ֽʽÿ�
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputAshramName, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 2 )
	{
		//	������ ������ �Է��� �ֽʽÿ�
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputOpenMessage, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 3 )
	{
		//	������ɼ� ������ �Է��� �ֽʽÿ�
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputCombatMessage, &strTemp, _T(""), _T("") );
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_OPENMESSAGE, 1, strTemp.HT_szGetString() );

	//	������ ������
	m_iOpenMessageItemIndex = iItemIndex;
	//	������ ������ ����
    m_byOpenMessageItemType = byItemKeyID;
	//	Open Dlg
	g_cUIManager->HT_ShowWindow( _DIALOG_OPENMESSAGE );
	g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_OPENMESSAGE, 2 );
	//	IME String Init
	g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );
	g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	g_cImeMgr.InputString();
}
HTvoid 
CHTChatting::HT_vChatting_DelOpenMessageItemBox()
{
	g_cUIManager->HT_HideWindow( _DIALOG_OPENMESSAGE );
}
HTvoid 
CHTChatting::HT_vChatting_NetworkSendOpenMessage()
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ����� ä�� ���� �����Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	CHTString sChatMsg;
	sChatMsg = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_OPENMESSAGE, 2 );

	//	��� �̸��� ���
	if( m_byChat_OpenMsgType == 1 )
	{
		//	��� ������ ��û�Ѵ�.
		if(HT_SUCCEED(g_cGuildSystem->HT_hrNetWork_CSP_REQ_CREATE_GUILD( sChatMsg )))
		{
			this->HT_vChatting_DelOpenMessageItemBox();
		}
	}
	//	�����ǰ� ������ɼ��ϰ��
	else if( m_byChat_OpenMsgType == 2 || m_byChat_OpenMsgType == 3 )
	{
		// �޽����� �ִ� ���� ������ �ʰ� �Ͽ��°�?
		if( sChatMsg.HT_nGetSize() > 80 )
		{
			// �޽����� �ʹ� ��ٴ� �޽���
			CHTString strTemp;
			LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_MESSAGEVALUE, strTemp, HT_MAX_STR);
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
		}
		else if( sChatMsg.HT_nGetSize() == 0 )
		{
			return;
		}
		else
		{
			MSG_Broadcast* info = HT_NULL;
			info = new MSG_Broadcast;

			info->byMsgType		= m_byOpenMessageItemType;
			info->byBgColor		= 0;
			info->byTextColor	= m_iOpenMessageItemIndex;
			info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;

			CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_NOTIFY_LENGTH );
			CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
			// �޽��� ������ ������ ��û��
			g_pNetWorkMgr->ReqNotifyMessage( info );

			//-----����� �׽�Ʈ�� ���Ͽ�-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			HT_DELETE( info );
			this->HT_vChatting_DelOpenMessageItemBox();
		}
	}
}
HTvoid 
CHTChatting::HT_vChatting_RenderOpenMsg( HTfloat fElapsedTime )
{
	if( m_fOpenTextPosX <= -999 )
		return;

	g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_oOpenMessageSave[0].strMsg, HTvector3( m_fOpenTextPosX, 10.0f, 0.0f ), g_ColorTable[12], HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 5.0f );

	m_fOpenTextPosX -= 4;//fElapsedTime*100;
	if( m_fOpenTextPosX < -300 )
	{
		m_fOpenTextPosX = -999;
		if( m_iOpenRotateCount >= 1 )
		{
			for( int i=0 ; i<OPENMESSAGE_MAX_COUNT-1 ; i++ )
			{
				//	Input
				m_oOpenMessageSave[i].bExistSw = m_oOpenMessageSave[i+1].bExistSw;
				m_oOpenMessageSave[i].byMsgType = m_oOpenMessageSave[i+1].byMsgType;
				m_oOpenMessageSave[i].strMsg = m_oOpenMessageSave[i+1].strMsg;
				m_oOpenMessageSave[i].strSenChar = m_oOpenMessageSave[i+1].strSenChar;

				//	Init
				memset( &m_oOpenMessageSave[i+1], 0, sizeof(OpenMESSAGE) );
				m_oOpenMessageSave[i+1].bExistSw = HT_FALSE;
			}

			if( m_oOpenMessageSave[0].bExistSw == HT_TRUE )
			{
				m_fOpenTextPosX = (HTfloat)g_pEngineHandler->HT_iGetScreenWidth();
				m_iOpenRotateCount = 0;
			}
		}
		else
		{
			m_fOpenTextPosX = (HTfloat)g_pEngineHandler->HT_iGetScreenWidth();
			m_iOpenRotateCount++;
		}
	}
}
HTRESULT 
CHTChatting::HT_hrChatting_SetPickOpenMsgWnd( HTPoint pPt )
{
	if( m_fOpenTextPosX <= -999 )
		return HT_FAIL;

	if( m_oOpenMessageSave[0].strSenChar.HT_bIsEmpty() )
		return HT_FAIL;

	if( pPt.x>m_fOpenTextPosX && pPt.x<m_fOpenTextPosX+300 &&
		pPt.y>10 && pPt.y<22 )
	{
		this->HT_vChatting_SetWisper( m_oOpenMessageSave[0].strSenChar.HT_szGetString() );
		return HT_OK;
	}
	return HT_FAIL;
}

//-������ �������� ����Ͽ� â�� ���� �׵��� Ű����� �Է��� ��ɵ��� ����
//-������ �������� ����Ͽ� â�� �޽����� �Է��� �� ����Ű�� ������ �޽����� ����
//-������ �������� ����Ͽ� â�� ���� �Է½� ����Ű�� �ν�, ���� ��

//-------------------------------------------------------------------------------
//	ä�� ��
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetChatBlock( HTbyte byChatBlock )
{
	if( byChatBlock & 0x04 )
		m_bChat_ChatBlockSw = HT_TRUE;
	else
		m_bChat_ChatBlockSw = HT_FALSE;
}

//-------------------------------------------------------------------------------
//	ä�� �α�
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetChatLog( HTint iType, CHTString strMsg, HT_COLOR clColor )
{
	//	�ڷ� ��ĭ�� �����.
	memcpy( (m_oChat_ChatLog+1), m_oChat_ChatLog, sizeof(ChatLogStrut)*(CHATLOG_MAX_COUNT-1) );

	//	Set Data
	m_oChat_ChatLog[0].iType = iType;
	m_oChat_ChatLog[0].clrColor = clColor;
	strncpy( m_oChat_ChatLog[0].szMsg, strMsg.HT_szGetString(), 128 );

	struct tm *newtime;
	__time64_t long_time;
	_time64( &long_time );                /* Get time as long integer. */
	newtime = _localtime64( &long_time ); /* Convert to local time. */
	newtime->tm_year += 1900;
	newtime->tm_mon += 1;

	char szFileName[64];
	ZeroMemory( szFileName, 64 );
	sprintf( szFileName, " (%04d%02d%02d,%02d:%02d:%02d)", newtime->tm_year, newtime->tm_mon, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec );

	strncpy( m_oChat_ChatLog[0].szTime, szFileName, 64 );
	m_iChat_ChatLogCount++;

	//	Set Chat Log
	this->HT_vChatting_SetTextinChatLog();
}
HTvoid
CHTChatting::HT_vChatting_SetOpenMeg( CHTString strMsg )
{
	HTint iStrlen = strMsg.HT_nGetSize();
	HTint iTempCount1 = 0;
	HTint iTempCount2 = 0;
	int iStrlength;
	char szMsg[512];
	char szTemp[512];
	HTbool bTrue;
	HTbool bChangeMsg;

	bChangeMsg = HT_FALSE;
	ZeroMemory( szTemp, 512 );
	ZeroMemory( szMsg, 512 );
	strncpy( szMsg, strMsg.HT_szGetString(), iStrlen );
	while( iTempCount2 < iStrlen )
	{
		bTrue = HT_FALSE;
		//	���ڸ� ����
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ������ ����Ʈ�� ������ ������ �ƴѰ�쿡��
		int iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );
		while ( iResult == 0 && iTempCount2<iStrlen )
		{
			iTempCount1++;
			iTempCount2++;
			szTemp[iTempCount1] = szMsg[iTempCount2];
			iResult = _ismbstrail( (unsigned char*)szTemp, (unsigned char*)(&szTemp[iTempCount1]) );

			iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
			if( iStrlength > 380 )
			{
				if( iResult == 0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
					szTemp[iTempCount1] = szMsg[iTempCount2];
					bTrue = HT_TRUE;
				}
				break;
			}
		}
		iTempCount1++;
		iTempCount2++;

		iStrlength = g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, szTemp );
		if( iStrlength > 380 || bTrue == HT_TRUE )
		{
			//	�ܾ������ ������ �ʿ��� ���, ���� ���ڸ� �ľ��Ͽ� ���� ���ڱ��� �ٽ� �ǵ�����.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	�ʸ���
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	�ε��׽þ�
			{
				char szTemp2[512];
				HTint iTempCount3 = iTempCount1;
				ZeroMemory( szTemp2, 512 );
				strncpy( szTemp2, szTemp, iTempCount1 );
				while( szTemp[iTempCount1]!=' ' && iTempCount1>0 )
				{
					szTemp[iTempCount1] = 0;
					iTempCount1--;
					iTempCount2--;
				}
				if( iTempCount1 == 0 )
				{
					iTempCount1 = iTempCount3;
					iTempCount2 = iTempCount3;
					strncpy( szTemp, szTemp2, iTempCount1 );
				}
			}

			//	�ڷ� ��ĭ�� �����.
			memcpy( (m_oChat_SaveOpenMsg+1), m_oChat_SaveOpenMsg, sizeof(ChatLogStrut)*(OPENMSG_MAX_COUNT-1) );
			ZeroMemory( &m_oChat_SaveOpenMsg[0], 128 );
			strncpy( m_oChat_SaveOpenMsg[0].szMsg, szTemp, strlen(szTemp) );
			m_iChat_OpenMsgCount++;

			ZeroMemory( szTemp, 512 );
			iTempCount1 = 0;
			bChangeMsg = HT_TRUE;
		}
	}
	if( strlen( szTemp ) > 0 )
	{
		//	�̹� ������ ���� �̻��� ����ĭ�� ���Ե�����
		if( bChangeMsg == HT_TRUE )
		{
			ZeroMemory( szMsg, 512 );
			strncpy( szMsg, m_oChat_SaveOpenMsg[0].szMsg, strlen(m_oChat_SaveOpenMsg[0].szMsg) );
			ZeroMemory( &m_oChat_SaveOpenMsg[0], 128 );
			strncpy( m_oChat_SaveOpenMsg[0].szMsg, szTemp, strlen(szTemp) );
			strncpy( szTemp, szMsg, strlen(szMsg) );
		}

		//	�ڷ� ��ĭ�� �����.
		memcpy( (m_oChat_SaveOpenMsg+1), m_oChat_SaveOpenMsg, sizeof(ChatLogStrut)*(OPENMSG_MAX_COUNT-1) );
		ZeroMemory( &m_oChat_SaveOpenMsg[0], 128 );
		strncpy( m_oChat_SaveOpenMsg[0].szMsg, szTemp, strlen(szTemp) );
		m_iChat_OpenMsgCount++;
	}

	//	Set Chat Log
	this->HT_vChatting_SetTextinChatLog();
}
HTvoid
CHTChatting::HT_vChatting_SetTextinChatLog()
{
	//void HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// ��ũ�ѹ� ��Ʈ�ѿ� �ִ� ���� ���� �մϴ�.

	//	ä�÷α�â �ʱ�ȭ
	for( HTint i=0 ; i<_CHAT_CHAT_LOG_NUM ; i++ )
	{
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+i, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+i, _T("") );
	}

	//	�Ϲݸ޽���
	HTint iScrolBar;
	HTint iChatCount = 0;
	HTbool bChatDisplay;
	if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG1 ) )
	{
		iScrolBar = g_cUIManager->HT_GetScrollBarValue( _DIALOG_CHATLOG1, 1 );
		
		for( i=iScrolBar ; i<CHATLOG_MAX_COUNT ; i++)
		{
			bChatDisplay = HT_FALSE;
			//	��ü ���� ������ ����
			if( m_bChat_ChatLogConfig[0] )
			{
				bChatDisplay = HT_TRUE;
			}
			else
			{
				//	��Ƽ
				if( m_bChat_ChatLogConfig[1] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_PARTY )
						bChatDisplay = HT_TRUE;
				}
				//	�ƽ���
				if( m_bChat_ChatLogConfig[2] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
						bChatDisplay = HT_TRUE;
				}
				//	����
				if( m_bChat_ChatLogConfig[3] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ALLIANCE )
						bChatDisplay = HT_TRUE;
				}
				//	�ӼӸ�
				if( m_bChat_ChatLogConfig[4] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_WISPER )
						bChatDisplay = HT_TRUE;
				}
				//	�ӼӸ�
				if( m_bChat_ChatLogConfig[5] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_SYSTEM )
						bChatDisplay = HT_TRUE;
				}
			}

			if( bChatDisplay )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+iChatCount, m_oChat_ChatLog[i].szMsg );
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+iChatCount, m_oChat_ChatLog[i].clrColor );
				iChatCount++;
				if( iChatCount >= _CHAT_CHAT_LOG_NUM )
					break;
			}
		}
	}
	//	������ �޽���
	else
	{
		iScrolBar = g_cUIManager->HT_GetScrollBarValue( _DIALOG_CHATLOG2, 1 );
		
		for( i=iScrolBar ; i<OPENMSG_MAX_COUNT ; i++)
		{
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+iChatCount, m_oChat_SaveOpenMsg[i].szMsg );
			g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+iChatCount, HT_COLOR( 1,1,1,1 ) );
			iChatCount++;
			if( iChatCount >= _CHAT_CHAT_LOG_NUM )
				break;
		}
	}
}
//	Write Chat Log File
void
CHTChatting::JK_vChatting_ChatLogFile()
{
	struct tm *newtime;
	__time64_t long_time;
	_time64( &long_time );                /* Get time as long integer. */
	newtime = _localtime64( &long_time ); /* Convert to local time. */
	newtime->tm_year += 1900;
	newtime->tm_mon += 1;

	FILE* pFile;
	pFile = NULL;

	::CreateDirectory( "ScreenShot", HT_NULL );

	char szFileName[64];
	ZeroMemory( szFileName, 64 );
	sprintf( szFileName, "ScreenShot\\ChatLog_%d_%d_%d", newtime->tm_year, newtime->tm_mon, newtime->tm_mday );

	char szTemp[64];
	ZeroMemory( szTemp, 64 );
	int iNameCount = 0;
	BOOL bFinder;
    bFinder = TRUE;
	FILE* pFindFile = NULL;
	while( bFinder )
	{
        sprintf( szTemp, "%s_%d.txt", szFileName, iNameCount );
		pFindFile = fopen( szTemp, "r" );
		if( pFindFile )
			fclose( pFindFile );
		else
			break;
		iNameCount++;
	}
    pFile = fopen( szTemp, "w" );
	if( pFile )
	{
		fprintf( pFile, "[ChatLog]\n" );

		for( HTint i=0 ; i<CHATLOG_MAX_COUNT ; i++ )
		{
			fprintf( pFile, m_oChat_ChatLog[i].szMsg );
			fprintf( pFile, m_oChat_ChatLog[i].szTime );
			fprintf( pFile, "\n" );
			if( i>=m_iChat_ChatLogCount )
				break;
		}

		fprintf( pFile, "[OpenMsg]\n" );
		for( i=0 ; i<OPENMSG_MAX_COUNT ; i++ )
		{
			fprintf( pFile, m_oChat_SaveOpenMsg[i].szMsg );
			fprintf( pFile, m_oChat_ChatLog[i].szTime );
			fprintf( pFile, "\n" );
			if( i>=m_iChat_OpenMsgCount )
				break;
		}
		fclose( pFile );
	}
}


//	�۾��� �޽���
HTvoid
CHTChatting::HT_vChatting_WorkingMsg()
{
	return;

	CHTString strTemp;
	strTemp.HT_hrCleanUp();
	////	�۾��� �޽��� ī��Ʈ
	//switch( m_iChat_MsgCount )
	//{
	//	case 0 :	strTemp = _T("�籸�� �۾����Դϴ�.");	break;
	//	case 1 :	strTemp = _T("�籸�� �۾����Դϴ�..");	break;
	//	case 2 :	strTemp = _T("�籸�� �۾����Դϴ�...");	break;
	//	case 3 :	strTemp = _T("�籸�� �۾����Դϴ�....");	break;
	//	case 4 :	strTemp = _T("�籸�� �۾����Դϴ�.....");	break;
	//	case 5 :	strTemp = _T("(�籸����) -.-");	break;
	//	case 6 :	strTemp = _T("(�籸����) -.-;;");	break;
	//	case 7 :	strTemp = _T("(�籸����) -.-;;;");	break;
	//	case 8 :	strTemp = _T("(�籸����) ^^; /('')/ l(``)l ^^");	break;
	//	case 9 :	strTemp = _T("(�籸����) �� �� ���� ������� �ϼ��ϱ� ���� �۾��� �������Դϴ�.");	break;
	//	case 10 :	strTemp = _T("(�籸����) ��.. ������ �۾����Դϴ�. ���ݸ� �� ��ٷ� �ּ���... ^^");	break;
	//	case 11 :	strTemp = _T("(�籸����) ��.. ��ö�־� �۾����Դϴ�. ���ݸ� �� ��ٷ� �ּ���... ^^");	break;
	//	case 12 :	strTemp = _T("(�籸����) T.T ����.. ���ݸ� �� ��ٷ��ּ���...");	break;
	//	case 13 :	strTemp = _T("(�籸����) T.T ����.. ������ ������...");	break;
	//	case 14 :	strTemp = _T("(�籸����) T.T ����.. ���� ���� �;... ^^");	break;
	//	case 15 :	strTemp = _T("(�籸����) T.T ����.. ���� ���ð� �;... ^^");	break;
	//	case 16 :	strTemp = _T("(�籸����) �׷��� ���� ������ ��ٸ��� �����Ե��� ���� ���ù㵵 ���¿��ϴ�.");	break;
	//	case 17 :	strTemp = _T("(�籸����) �� ���� ���ƿ�... WWWW");	break;
	//	case 18 :	strTemp = _T("(�籸����) ...!!!");	break;
	//	case 19 :	strTemp = _T("(�籸����) �ʹ� �ɿ��� ������");	break;
	//	case 20 :	strTemp = _T("(�籸����) ���� �׸� �����ø� �ȵɱ��? ^^");	break;
	//	case 21 :	strTemp = _T("(�籸����) ...");	break;
	//	case 22 :	strTemp = _T("(�籸����) ..");	break;
	//	case 23 :	strTemp = _T("(�籸����) .");	break;
	//	case 24 :	strTemp = _T("(�籸����) ������ �˾���?");	break;
	//	case 25 :	strTemp = _T("(�籸����) ...");	break;
	//	case 26 :	strTemp = _T("(�籸����) V3 �۾��� �ϴ� ���߿����� �� �ϳ� �ϰ� �������� �־��µ�...");	break;
	//	case 27 :	strTemp = _T("(�籸����) ���� ������ �帱�?");	break;
	//	case 28 :	strTemp = _T("(�籸����) �׷� �� ���ٷ���? ����");	break;
	//	case 29 :	strTemp = _T("(�籸����) ģ���е� �� �� ���� ��ð� ���ż� źƮ�� ���ּ���");	break;
	//	case 30 :	strTemp = _T("(�籸����) ���� �ϸ鿩..");	break;
	//	case 31 :	strTemp = _T("(�籸����) źƮ���� �ٴ� �� ���� ���� �̷��ϰ� �ٲٰ� �;���ϴ�.");	break;
	//	case 32 :	strTemp = _T("(�籸����) �� �ϰ� �;����µ�...");	break;
	//	case 33 :	strTemp = _T("(�籸����) �ʹ� ��Թ� �۾��̶� �������� ���߳׿�.. �ƽ��(�ʹ�)");	break;
	//	case 34 :	strTemp = _T("(�籸����) ...");	break;
	//	case 35 :	strTemp = _T("(�籸����) ..");	break;
	//	case 36 :	strTemp = _T("(�籸����) .");	break;
	//	case 37 :	strTemp = _T("(�籸����) ���� �����Ե��� ������ ������ Ǫ�� ������ ��� �˴ϴ�.");	break;
	//	case 38 :	strTemp = _T("(�籸����) �׷� Have nice day !!! �׸��� ��ź!!!");	break;
	//	default	:	strTemp = _T("�籸�� �۾����Դϴ�.");	break;
	//}

	strTemp = _T("^^");
    g_cChatting->HT_vArrangeSavedHistory( strTemp.HT_szGetString(), g_ColorTable[12]);
	g_cChatting->HT_vChatting_SetSystemTextList();

	//	�۾��� �޽��� ī��Ʈ
	m_iChat_MsgCount++;
	if( m_iChat_MsgCount > 38 )
		m_iChat_MsgCount = 0;
}
