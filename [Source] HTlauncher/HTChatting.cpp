//======================================================================
// CHTChatting.cpp
// 채팅 관련 메시지 관리
// (주)한빛소프트 게임개발팀 정의규		.......... 최초작성
// (주)한빛소프트 게임개발팀 정대호		2002.09.13 추가/수정
// (주)한빛소프트 게임개발팀 서명석		2002.10.22 추가/수정20021022Tenma
// (주)한빛소프트 게임개발팀 정의규		2003.이후
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

// 채팅창이 비활성인 상태에서 메시지를 받았을 경우 채팅 버튼이 깜빡이는 시간을 조절한다. (ms)
#define CHATTING_BUTTON_FLASHING_INTEVAL		1000

extern CHTWindowManager*			g_CGame;

CHTChatting::CHTChatting()
{
	m_bChatStatusOn			= HT_FALSE;				// 처음에는 입력도 안받는다.
	m_IMEStatus				= IME_STATUS_ENGLISH;	// 처음에는 한글 입력 모드이다.

	// 채팅 메시지 초기화
	m_strChatMessage.HT_hrCleanUp();
	// 귓속말 받는 사람 이름 초기화
	m_strWisperName.HT_hrCleanUp();

	// 대화내용을 파일로 로깅을 처음에는 당연히 안한다.
	m_bLogging = HT_FALSE;
	// 처음에는 널(파일이 열려 있지 않음)
	m_pLogFile = NULL;

	m_iNameListNum = 0;
	for( HTint i=0 ; i<_MAX_SAVED_NAMELIST_NUM ; i++ )
	{
		m_strWhisperNameList[i].HT_hrCleanUp();
	}
	m_iChat_WhisperReadIndex = 0;

	// 공지사항 문자열 셋팅
	m_pNotifyBuffer = (HTtchar *)malloc( 1000 * sizeof(HTtchar) );
	// 20030123Tenma_test 임시로 처음 공지사항 띄울 문자열
	LoadString(g_hInstance, IDS_NOTIFY_MSG_TEMP, m_pNotifyBuffer, 1000);

	for (i=0; i<_MAX_SAVED_MESSAGE_NUM; i++)		ZeroMemory(&m_oSavedChatMsg[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_HISTORY_NUM; i++)		ZeroMemory(&m_oSavedHistory[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_NAMELIST_NUM; i++)		m_strNameList[i].HT_hrCleanUp();

	//	마지막으로 귓속말 보낸 상대
	m_strLastRiciveWisperName.HT_hrCleanUp();
	//	/탈출 3초에 한번씩 보내게 하기 위해
	m_dwEscapeSaveTime = 0;
}

CHTChatting::~CHTChatting()
{	
	// 처음 공지사항 버퍼에 문자열이 남아 있으면 문자열을 비운다 20030123Tenma_test
	if( m_pNotifyBuffer != NULL )
	{
		// 공지사항 문자열 배열을 비운다.
		free( m_pNotifyBuffer );
		m_pNotifyBuffer = NULL;
	}

	// 로그 파일이 열려 있으면 닫는다.
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
	//	채팅 윈도우 스타일
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

	//	전광판 아이템
	m_iOpenMessageItemIndex = 0;
	//	전광판 아이템 종류
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

	//	스크롤 값
	m_iChat_ScrollChat = 0;
	m_iChat_ScrollSystem = 0;
	//	채팅 입력 모드
    m_bChat_InputMode = HT_FALSE;
	//	Open Msg Type
	//	0:없음, 1:아쉬람이름, 2:전광판, 3:전투명령서
	m_byChat_OpenMsgType = 0;
	//	작업중 메시지 카운트
	m_iChat_MsgCount = 0;

	//	채팅 설정
	for( i=0 ; i<5 ; i++ )
        m_bChat_ConfigChat[i] = HT_FALSE;
    m_bChat_ConfigChat[0] = HT_TRUE;
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, m_bChat_ConfigChat[0] );

	//	채팅 로그
	ZeroMemory(	&m_oChat_ChatLog, sizeof(ChatLogStrut)*CHATLOG_MAX_COUNT );
	m_iChat_ChatLogCount = 0;
    for( i=0 ; i<6 ; i++ )
        m_bChat_ChatLogConfig[i] = HT_FALSE;
	m_bChat_ChatLogConfig[0] = HT_TRUE;
	ZeroMemory(	&m_oChat_SaveOpenMsg, sizeof(ChatLogStrut)*OPENMSG_MAX_COUNT );
	m_iChat_OpenMsgCount = 0;

	//	최초 윈도우 스타일 체크
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
	// 해상도 추출
	HTint iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();

	//	[_DIALOG_CHATTINGBOX]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATTINGBOX, _T(""), 412, 250, g_cChatting->HT_vChatting_InputCheckForChatWnd, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTINGBOX, true );	// 배경영역 클릭시 맵 픽되게
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTINGBOX, 0, iScreenHeight-250-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTINGBOX, TRUE, 15,189, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 170, 15, 189 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 51, 0, 0, 202, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, g_cUIManager->m_nAlphaColor/100.0f ), 412, 48 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 51, HT_FALSE );
	//	외곽선
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
	//	스크롤 바
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 1, 1, 104, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 1, 100 );
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 2, 1, 4, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 2, 100 );
	//	Button 채팅창 바꾸기
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 9, 57, 1, 225, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 9, _T("C1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 228, 24, 16 );
	//	Button 엔터
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button 채팅모드
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 11, 159, 362, 202, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	채팅모드변환
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 202, 50, 19 );
	//	Button 채팅 설정
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 2, 159, 27, 230, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 231, 60, 19 );//채팅설정
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	채팅내용표시설정
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 2, strMessage );
	//	Button 전체
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 3, 204, 88, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 231, 50, 19 );//전체
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 3 );
	//	Button 파티
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 4, 204, 139, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 231, 50, 19 );//파티
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 4 );
	//	Button 아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 5, 204, 190, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 231, 55, 19 );//아쉬람
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 5 );
	//	Button 연합
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 6, 204, 246, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 231, 50, 19 );//연합
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 6 );
	//	Button 주소록
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 7, 204, 297, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 231, 55, 19 );//주소록
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 7 );
	//	Button 채팅로고
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 8, 204, 353, 230, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 231, 59, 19 );//채팅로그
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
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING2BOX, true );	// 배경영역 클릭시 맵 픽되게
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING2BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING2BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 170, 15, 239 );
	//	외곽선
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
	//	스크롤 바
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING2BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING2BOX, 1, 100 );
	//	Button 채팅창 바꾸기
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 9, _T("C3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button 엔터
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button 채팅모드
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	채팅모드변환
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button 채팅 설정
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//채팅설정
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	채팅내용표시설정
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 2, strMessage );
	//	Button 전체
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//전체
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 3 );
	//	Button 파티
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//파티
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 4 );
	//	Button 아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//아쉬람
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 5 );
	//	Button 연합
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//연합
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 6 );
	//	Button 주소록
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//주소록
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 7 );
	//	Button 채팅로고
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//채팅로그
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
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING3BOX, true );	// 배경영역 클릭시 맵 픽되게
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING3BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING3BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 170, 15, 239 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 0, 1, 251, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ), 411, 48 );
	//	외곽선
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
	//	스크롤 바
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING3BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING3BOX, 1, 100 );
	//	Button 채팅창 바꾸기
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 9, _T("C4"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button 엔터
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button 채팅모드
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	채팅모드변환
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button 채팅 설정
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//채팅설정
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	채팅내용표시설정
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 2, strMessage );
	//	Button 전체
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//전체
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 3 );
	//	Button 파티
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//파티
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 4 );
	//	Button 아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//아쉬람
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 5 );
	//	Button 연합
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//연합
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 6 );
	//	Button 주소록
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//주소록
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 7 );
	//	Button 채팅로고
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//채팅로그
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
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 3, 99, 210, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 3, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 65, 72, 19 );//확인
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 4, 99, 300, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 4, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 300, 65, 72, 19 );//취소

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
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//전체
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_WHISPERLISTWND, 1, strMessage );

	//	[_DIALOG_CHATCONFIG]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATCONFIG, _T(""), 90, 100, g_cChatting->HT_vChatting_InputCheckForChatConfig, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATCONFIG, 5 );
	//	Button 전체
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//전체
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 1 );
	//	Button 파티
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//파티
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 2 );
	//	Button 아쉬람
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//아쉬람
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 3 );
	//	Button 연합
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//연합
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 4 );
	//	Button 귓속말리스트
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 5, eMsgChatList, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//리스트
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 5 );
    //63 UI_Button03_N_64X19.bmp
	//169, 175
	HT_vChatting_InputCheckForChatWnd(0, 0, 3);

	//	[_DIALOG_CHATLOG1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATLOG1, _T("ChatLog"), 412, 465, g_cChatting->HT_vChatting_InputCheckForChatLog, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATLOG1, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button 일반 메시지
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 1 );
	//	Button 전광판 메시지
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 2 );
	//	Button 채팅설정
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 3 );
	//	Button 저장
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 4 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 5 );
	//	스크롤 바
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
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button 일반 메시지
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 1 );
	//	Button 전광판 메시지
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 2 );
	//	Button 채팅설정
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 3 );
	//	Button 저장
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 4 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 5 );
	//	스크롤 바
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
	//	Button 전체
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 1, HT_TRUE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//전체
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 1 );
	//	Button 파티
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//파티
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 2 );
	//	Button 아쉬람
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//아쉬람
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 3 );
	//	Button 연합
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//연합
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 4 );
	//	Button 귓속말
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 5, eMsgCommonCommandWhisper2, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//귓속말
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 5 );
	//	Button 시스템
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 100 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 6, 175, 8, 106, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 6, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 6, 63, 26, 100, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 6, eMsgChatSystem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 100, 64, 19 );//시스템
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 6 );
}
//	Read Parse Msg
HTvoid CHTChatting::HT_vChatting_ReadParseMsg()
{
	HT_vChatting_SetMessage( eMsgCommonChatWhole			, &szWhole );			// 전체
	HT_vChatting_SetMessage( eMsgCommonChatAshuram			, &szAshuram );			// 아쉬람

	HT_vChatting_SetMessage( eMsgCommonCommandWhole			, &szMsgWhole );		// /전체
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper		, &szMsgWhisper );		// /귓속말
	HT_vChatting_SetMessage( eMsgCommonCommandAddress		, &szMsgAddress );		// /친구등록
	HT_vChatting_SetMessage( eMsgCommonCommandAshuram		, &szMsgAshuram );		// /아쉬람
	HT_vChatting_SetMessage( eMsgCommonCommandKick			, &szMsgKick );			// /킥
	HT_vChatting_SetMessage( eMsgCommonCommandWin			, &szMsgCommandWin );	// 명령창

	HT_vChatting_SetMessage( eMsgCommonCommandAS			, &szMsgAS );			// /GM호출
	HT_vChatting_SetMessage( eMsgCommonCommandAS2			, &szMsgAS2 );			// /GM호출2
	
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel		, &szMsgASCancel );		// /GM호출취소
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel2		, &szMsgASCancel2 );	// /GM호출취소2

	HT_vChatting_SetMessage( eMsgCommonCommandASCheck		, &szMsgASCheck);		// /GM호출확인
	HT_vChatting_SetMessage( eMsgCommonCommandASCheck2		, &szMsgASCheck2 );		// /GM호출확인2
    
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildJoin	, &szMsgAshuramGuildJoin);	// /아쉬람연합
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildLeave	, &szMsgAshuramGuildLeave );// /아쉬람연합탈퇴

	HT_vChatting_SetMessage( eMsgCommonCommandGuildMark		, &szMsgGuildMark );	// /길드마크
	HT_vChatting_SetMessage( eMsgCommonCommandTrimuritiMark	, &szMsgTrimuritiMark ); // /주신마크

	HT_vChatting_SetMessage( eMsgCommonCommandInvisible		, &szMsgInvisible );	// /투명
	HT_vChatting_SetMessage( eMsgCommonCommandWarp			, &szMsgWarp );			// /워프
	HT_vChatting_SetMessage( eMsgCommonCommandMove			, &szMsgMove );			// /이동

	HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szMsgNotice );		// /공지
	HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /전체공지
	HT_vChatting_SetMessage( eMsgCommonCommandAssistant		, &szMsgAssistant );	// /조교

	HT_vChatting_SetMessage( eMsgCommonCommandShout			, &szMsgShout );		// /외치기
	HT_vChatting_SetMessage( eMsgCommonCommandParty			, &szMsgParty );		// /파티
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramNotice	, &szMsgGuildNotice );	// /공지사항-길드용
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGrade	, &szMsgGuildGrade );	// /아쉬람등급

	HT_vChatting_SetMessage( eMsgCommonChatParty			, &szParty );			// 파티
	HT_vChatting_SetMessage( eMsgCommonCommandTrade			, &szTrade );			// 교환
	HT_vChatting_SetMessage( eMsgCommonCommandEmerge		, &szEmerge );			// 탈출

	HT_vChatting_SetMessage( eMsgCommonCommandPartyPart		, &szMsgPartyPart );			// /파
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramPart	, &szMsgAshuramPart );			// /아
	HT_vChatting_SetMessage( eMsgCommonCommandWholePart		, &szMsgWholePart );			// /전
	HT_vChatting_SetMessage( eMsgCommonCommandShoutPart		, &szMsgShoutPart );			// /외
	HT_vChatting_SetMessage( eMsgCommonCommandWhisperPart	, &szMsgWhisperPart );			// /귓

	HT_vChatting_SetMessage( eMsgCommonCommandDebugMode		, &szMsgDebugMode );			// Debug Mode
	HT_vChatting_SetMessage( eMsgCommonCommandBroadcastMode	, &szMsgBroadcastMode );		// BroadcastMode
	HT_vChatting_SetMessage( eMsgCommonCommandEngineCamera	, &szMsgEngineCamera );			// Use Engine Camera
	HT_vChatting_SetMessage( eMsgCommonCommandGoCamera		, &szGoCamera );				// Go Camera
	HT_vChatting_SetMessage( eMsgCommonCommandShowCursor	, &szShowCursor );				// ShowCursor

	HT_vChatting_SetMessage( eMsgCommonCommandDuel			, &szMsgDuel );				// Duel

	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance1	, &szMsgAshuramAllince1 );				// 아쉬람 연합1 /연
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance2	, &szMsgAshuramAllince2 );				// 아쉬람 연합2 /연합
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoin		, &szMsgAshuramJoin );						// 아쉬람 연합

	HT_vChatting_SetMessage( eMsgCommonChatRoom		, &szMsgChatRoom );						// 아쉬람 연합// 채팅방
}

//	입력 메세지 처리
//	FromChatWnd
void CHTChatting::HT_vChatting_InputCheckForChatWnd(int iAction, int iTarget, int iTargetID)
{
	//	채팅 윈도우 스타일
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
				// 단, 채팅모드가 2일때는 그냥 넘어간다.
				if (g_cChatting->m_bChat_InputMode)
					return;

				g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			}
		}
		//	채팅 설정
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
		//	전체
		else if( iTargetID == 3 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//	전체
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
		//	파티
		else if( iTargetID == 4 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatParty, &strMessage, _T(""), _T("") );	//	파티
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
		//	아쉬람
		else if( iTargetID == 5 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuram, &strMessage, _T(""), _T("") );	//	아쉬람
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
		//	연합
		else if( iTargetID == 6 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuramAlliance, &strMessage, _T(""), _T("") );	//	아쉬람연합
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
		//	주소록
		else if( iTargetID == 7 )
		{
			if( g_cAddress->HT_iIsOn() )    g_cAddress->HT_vSetOff();
			else							g_cAddress->HT_vSetOn();
		}
		//	채팅 입력 모드
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
		//	채팅로그
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
		//	채팅창 변환
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

	// 숨겨진다면 다시 보이게 설정
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
		//	취소
		if( iTargetID == -1 || iTargetID == 4 )
		{
			g_cChatting->HT_vChatting_DelOpenMessageItemBox();
		}
		//	확인
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
				//	귓속말 상태로 만들어 주고..
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
		//	일반 메시지
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
		//	전광판 메시지
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
		//	채팅설정
		else if( iTargetID == 3 )
		{
			//	일반메시지창일때만 사용가능
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG2 ) )
				return;
			//	켜져 있으면 꺼고 꺼져 있으면 켜자
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
		//	저장
		else if( iTargetID == 4 )
		{
			//	Write Chat Log File
			g_cChatting->JK_vChatting_ChatLogFile();
		}
		//	확인
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

	//	채팅 윈도우 스타일
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

//	Set Parse Msg  //fors_debug 景깎꽝鑒돨뒈렘
HTvoid CHTChatting::HT_vParseMsg( CHTString strCommand, CHTString strMessage )
{
	//	메시지가 없으면.
	if ( strMessage.HT_bIsEmpty() || strMessage.HT_nGetSize() <= 0 )
		return;

	HTtchar* pcMsg;
	HTtchar* token;
    // 구분자(delimiter)로 스페이스, 탭, 엔터 등으로 토큰을 구분한다.
	HTtchar seps[] = " \t\n";

	CHTString strTemp;
	strTemp = strMessage;
	pcMsg = strTemp.HT_szGetString();
	token = _tcstok(pcMsg, seps);

	// HK : 도움말에 _tcstok()에서 NULL이 나올 수 있다고 나온다. 이경우 리턴!
	if ( token == HT_NULL ) return;

	//	첫번째 글자 저장
	CHTString strFirstChar;
	strFirstChar.HT_szFormat("%c", token[0] );

	//	파싱 메시지들
	{
		//	채팅관련
		//	일반채팅
		if( strFirstChar.HT_iStringCompare("/") != 0 &&
			( strCommand.HT_iStringCompare( szWhole.HT_szGetString() ) == 0 || strCommand.HT_nGetSize() == 0 ) )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	일반채팅 - /전체 || /전
		else if( CHTString::HT_iStringCompare(token, szMsgWhole.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, szMsgWholePart.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, "/s") == 0 )
		{
			token = _tcstok(NULL, "");
			this->HT_vSetData_Normal(token);
		}
		//	일반 체팅 예외
		else if(CHTString::HT_iStringCompare(token, _T("/위치저장") )==0 ||
				CHTString::HT_iStringCompare(token, _T("/SavePosition") )==0 )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	귓속말 채팅 - /귓속말 || /귓
		else if( CHTString::HT_iStringCompare(token, szMsgWhisper.HT_szGetString() )==0 
				|| CHTString::HT_iStringCompare(token, szMsgWhisperPart.HT_szGetString() )==0
				|| CHTString::HT_iStringCompare(token, "/w")==0 )
		{
			HTtchar* Temptoken = _tcstok(NULL, "");
			this->HT_vSetData_Whisper( token, Temptoken );
		}
		//	파티 채팅 - /파티 || /파
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
		//	길드 채팅 - /아쉬람 || /아 || 아쉬람
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
		//	아쉬람 연합 - /연 || /연합 || 아쉬람연합
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
		//	외치기 채팅 - /외치기 || /외
		else if(CHTString::HT_iStringCompare(token, szMsgShout.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgShoutPart.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare(token, "/y")==0 )
		{
		}
		//	길드 랭크 무여 - /아쉬람등급
		else if( CHTString::HT_iStringCompare(token, szMsgGuildGrade.HT_szGetString() ) ==0 ||
				CHTString::HT_iStringCompare(token, _T("/av") )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildSetRanking( token );
		}
		//	길드 정보 갱신 - /공지사항
		else if(CHTString::HT_iStringCompare(token, szMsgGuildNotice.HT_szGetString() )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildUpdate( token );
		}
		else if( CHTString::HT_iStringCompare(token, szMsgChatRoom.HT_szGetString() ) == 0 )
		//else if(CHTString::HT_iStringCompare(token, _T("/채팅방") )==0 ) 
		{
			//if( g_iInationalType == INATIONALTYPE_KOREA)	// 일단 한국에서만 됨
			//{
				token = _tcstok(NULL, "");
				
				if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)	// 이미 채팅방과 연결중이라면 작동하지 않는다.
					return;

				g_cChatRoom->HT_vChatRoom_WindowPopup();
			//}
		}
		else if(CHTString::HT_iStringCompare(token, _T("/테스트") )==0 )
		{/*
			// 글자 출력
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
		//	GM 명령어_ GM호출
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
				if (iCallStatus==1)		// 실패
				{
					HT_vChatting_SetMessage( eMsgGMCallTreat	, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==0) // 성공
				{
					HT_vChatting_SetMessage( eMsgGMCallRegist	, &str );
					HTint iCallCound = m_oGMCall->HT_iGetCallCount();
					str.HT_szFormat(str, iCallCound);
				
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==-1)	// 재등록 요청
				{
					HT_vChatting_SetMessage( eMsgGMCallReRegist	, &str );
					//str.HT_szFormat("GM호출 내용이 등록되지 않았습니다. 다시 등록해 주시기 바랍니다.");
				}

				HT_DELETE( m_oGMCall );
			}
		}// GM호출확인
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
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildJoin.HT_szGetString() ) == 0)	// 아쉬람연합
		{	
			// Step 1. 자신이 마하라자인지 조사하여 아니면 메시지 송출
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg5, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. 자신이 아쉬람연합 상태인지 조사하여 이미 맺은 상태라면 에러메시지 출력
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), _T(" ")) != 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg11, &strString );	// 이미 아쉬람 연합을 맺은 상태입니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// Step 3. 선택모드로 변경한다.
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg7, &strString );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );

					g_cGuildSystem->m_nAshuramGuildJoinMode = 1;
					g_cInterfaceCheck->HT_vSetCursor(CURSOR_SELECT_ANI);
				}

			}
		}
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildLeave.HT_szGetString() ) == 0)	// 아쉬람연합탈퇴
		{	
			// Step 1. 자신이 마하라자인지 조사하여 아니면 메시지 송출
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg6, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. 아쉬람 연합이 되어 있는 상태인지를 조사한다.
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), "") == 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg10, &strString );	// 아쉬람 연합을 맺은 아쉬람이 없습니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// 서버에 패킷 전송하기 (거부함)
					g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,2,0);
				}
			}

		}
		//	GM 명령어_투명 모드
		else if(CHTString::HT_iStringCompare(token, szMsgInvisible.HT_szGetString() )==0)
		{
            if( g_oMainCharacterInfo.snTribe == 0x09 || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( g_oMainCharacterInfo.szCharName, 0x02 );
		}
		//	GM 명령어_Chatting Block
		else if(CHTString::HT_iStringCompare(token, _T("/chatblock") )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( strMessage, 0x04 );
		}
		//	GM 명령어_특정 지역 워프
		else if(CHTString::HT_iStringCompare(token, szMsgWarp.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_POSITION( strMessage );
		}
		//	GM 명령어_특정 캐릭터 워프
		else if(CHTString::HT_iStringCompare(token, szMsgMove.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( strMessage );
		}
		//	오직 클라이언트에서만 자기위 캐릭터 안보이게 하는 명력어
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
		//	GM 명령어_다른캐릭터 정보보기
		else if (CHTString::HT_iStringCompare(token, "/INFO")==0)
		{
			// 나머지 스트링을 모두 토큰으로 뽑아냄
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharInfo( token );
		}
		//	GM 명령어_다른캐릭터 로그아웃 시킬때 - /킥
		else if (CHTString::HT_iStringCompare(token, szMsgKick.HT_szGetString() )==0)
		{
			// 나머지 스트링을 모두 토큰으로 뽑아냄
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharClose( token );
		}
		//	GM 명령어 - 파일로 부터 읽어서 한꺼번에 출력함
		else if (CHTString::HT_iStringCompare(token, "/IDHANFILE")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				// 나머지 스트링을 모두 토큰으로 뽑아냄
				token = _tcstok(NULL, "");

				// 파일을 읽거나 메시지를 보내는데 실패하였음.
				if( token == NULL || FAILED(this->NotifyFromFile(token)) )
				{
					CHTString szMessage;
					HT_vChatting_SetMessage( eMsgCommonSystemFile_Err, &szMessage );
					this->HT_vSaveHistory( 1, szMessage, g_ColorTable[12], g_ColorTable[0]);
				}
			}
		}
		//	GM 명령어 공지창으로 공지
		else if(CHTString::HT_iStringCompare(token, szMsgWholeNotice.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, "/IDHAN")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09  || g_bDevelopingMode )
            	this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM 명령어_시스템창에 공지
		else if(CHTString::HT_iStringCompare(token, szMsgNotice.HT_szGetString() )==0 )
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM 명령어_서버에 로깅을 시작 또는 중지.
		else if(CHTString::HT_iStringCompare(token, "/CHATLOG")==0)
		{
			StartStopLogging();
		}
		//	GM 명령어_// CHAR LOCATION을 요청하는 메시지를 보냄
		else if(CHTString::HT_iStringCompare(token, "/CONNECT")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				token = _tcstok(NULL, "");
				this->HT_vSetData_CharacterLocation( token );
			}
		}
		//	게임기능
		//	상거래
		else if(CHTString::HT_iStringCompare(token, "/t")==0 ||
				CHTString::HT_iStringCompare(token, "/T")==0 ||
				CHTString::HT_iStringCompare(token, "/trade")==0 ||
				CHTString::HT_iStringCompare(token, "/TRADE")==0 ||
				CHTString::HT_iStringCompare(token, szTrade.HT_szGetString() )==0 )
		{
			g_cExchangeSystem->HT_vExchange_SetClickTradeButton( HT_TRUE );
		}
		//	/친구등록
		else if( CHTString::HT_iStringCompare(token, szMsgAddress.HT_szGetString() ) == 0 )
		{
			// 나머지 스트링을 모두 토큰으로 뽑아냄
			token = _tcstok(NULL, "");
			g_cAddress->HT_vCSP_JoinAddressBook( token );
		}
		//	길드마크 스위치
		else if(CHTString::HT_iStringCompare(token, szMsgGuildMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vGuild_EmblemSwitch( szMsgGuildMark );
		}
		//	주신마크 스위치
		else if(CHTString::HT_iStringCompare(token, szMsgTrimuritiMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vTrimutiri_MarkSwitch( strMessage );
		}
        //	갖힌데서 빠져나오기 - /탈출
		else if( CHTString::HT_iStringCompare(token, "/emerge")==0 || 
				 CHTString::HT_iStringCompare(token, szEmerge.HT_szGetString())==0 )
		{
			if( g_iInationalType != INATIONALTYPE_JAPEN )
			{
				//	/탈출 3초에 한번씩 보내게 하기 위해
				DWORD dwPassTime = timeGetTime();
				if( dwPassTime > m_dwEscapeSaveTime+3000 )
				{
					m_dwEscapeSaveTime = dwPassTime;
					g_pNetWorkMgr->RequestEscape();

					//-----디버깅 테스트를 위하여-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_RequestEscape" );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
				}
			}
		}
		// HK : Cheat Key와 같은 형식으로 몇몇 시스템 내부 내용을 보여주는 부분을 처리한다.
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
		//	동영상 찍기 위해
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
		//	개발자모드로 전환
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
		//	동영상 찍기 위해_커서 보였다 안보이게처리
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
		//	개발자모드로 전환
		else if(CHTString::HT_iStringCompare(token, szMsgDuel.HT_szGetString() )==0)
		{
			if( g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				g_pDuelSystem->HT_vDuel_SetDuelMode();
		}
		//	공성전 UI
		else if(CHTString::HT_iStringCompare(token, _T("/siege") )==0)
		{
			g_cCommand->HT_vCommand_Siege();
		}
		//	출석체크
		else if(CHTString::HT_iStringCompare(token, _T("/Attendance") )==0)
		{
			g_pEventWindow->HT_vEventWindow_ReqAttendance();
		}
		//	귓속말 채팅_마지막에 귓속말 창에 뭔가 있으면 귓속말을 보냄
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

	//	채팅 윈도우 스타일
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_FocusOnEditBoxControl( iChatDlgNo, 2 );
	//	Set Language
	//g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );

	//	기존의 문자를 넣어준다.
	//m_strChatMessage = g_cUIManager->HT_GetTextEditBoxControl( iChatDlgNo, 2 );
	//g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( m_strChatMessage.HT_szGetString() );
	//g_cImeMgr.InputString();
}
//	Set Focus Off
HTvoid CHTChatting::HT_vChatting_SetFocusOff( HTbool bTrue )
{
	//	Check 채팅 입력 모드
	if( bTrue )
	{
		if( m_bChat_InputMode == HT_TRUE )
			return;
	}

	//	채팅 윈도우 스타일
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
	//	채팅 윈도우 스타일
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

	//	채팅창 초기화
	for( HTint i=0 ; i<iLineCount; i++)
		g_cUIManager->HT_SetTextLabelControl( iChatDlgNo, 10+i, _T("") );

	//	채팅 리스트 검색
	HTint iChatCount = 0;
	HTbool bChatDisplay = HT_FALSE;
	for( i=m_iChat_ScrollChat ; i<_MAX_SAVED_MESSAGE_NUM; i++)
	{
		bChatDisplay = HT_FALSE;
		//	전체 찍기면 무조건 셋팅
		if( m_bChat_ConfigChat[0] )
		{
            bChatDisplay = HT_TRUE;
		}
		else
		{
			//	파티
			if( m_bChat_ConfigChat[1] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_PARTY )
					bChatDisplay = HT_TRUE;
			}
			//	아쉬람
			if( m_bChat_ConfigChat[2] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
					bChatDisplay = HT_TRUE;
			}
			//	연합
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
	//	채팅 윈도우 스타일
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
	//	채팅 윈도우 스타일
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

// IME모드를 얻어온다
HTint
CHTChatting::HT_iGetIMEMode()
{
	return m_IMEStatus; 
}

//-------------------------------------------------------------------------------
// HTbool HT_vChatting_SetHistoryFunction( WPARAM wParam )
// D : 히스토리 기능
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetHistoryFunction( WPARAM wParam )
{
	//	채팅 윈도우 스타일
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	switch( wParam )
	{
		case VK_PRIOR:
			{
				//	귓속말 입력창일때
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
				//	채팅 메시지 입력창일때
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
					//	UI 시스템에 글자 출력_미니창과 전체창에 다!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
		case VK_NEXT:
			{
				//	귓속말 입력창일때
				if( g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 1 ) )
				{
					if( m_strWhisperNameList[0].HT_bIsEmpty() )
						return;
					m_iChat_WhisperReadIndex++;
					if( m_iChat_WhisperReadIndex > 9 )	m_iChat_WhisperReadIndex = 0;
					if( m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_bIsEmpty() )	m_iChat_WhisperReadIndex = 0;
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_szGetString() );
				}
				//	채팅 메시지 입력창일때
				else
				{
					m_iChat_HistroyReadIndex++;
					if( m_iChat_HistroyReadIndex > 9 )									m_iChat_HistroyReadIndex = 0;
					if( m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_bIsEmpty() )	m_iChat_HistroyReadIndex = 0;
					m_strChatMessage = m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_szGetString();

					//	UI 시스템에 글자 출력_미니창과 전체창에 다!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveChatMsg()
// D : 메세지 저장
//-------------------------------------------------------------------------------
HTvoid 
CHTChatting::HT_vSaveChatMsg( HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground )
{
	this->HT_vArrangeSavedChatMsg( iType, sMsg, colorText );
	this->HT_vChatting_SetChatTextList();
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveHistory()
// D : 메세지 저장
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
		// 당신은 채팅 금지 상태입니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	PS_CSP_REQ_CHAT info = HT_NULL;
	info = new S_CSP_REQ_CHAT;

	//	주신 셋팅
	info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;
	//	상점모드
	if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
	{
		info->byBgColor		= 0;
		info->byTextColor	= 13;
	}
	//	조교모드
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
	//	기냥 일반
	else
	{
		info->byBgColor		= 0;
		info->byTextColor	= 15;
	}

	// 메시지가 최대 길이 제한을 초과 하였는가?
	if(strlen(sChatMsg) > MAX_CHAT_LENGTH )
	{
		// 메시지가 너무 길다는 메시지
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );

		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// 정상적인 경우
	else
	{
		CHTString::HT_hrStringCopy(info->szMsg, sChatMsg, MAX_CHAT_LENGTH+1 );
	}

	//	머리글에
	g_cMainCharacter->HT_vMainChar_NetWork_ChattingMessage( 0x01, info->szMsg );
	//	채팅창에
	CHTString strMsg;
	strMsg.HT_szFormat( "%s:", g_oMainCharacterInfo.szCharName );
	strMsg += info->szMsg;
	this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_NORMAL, strMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	// 메시지 전송을 서버에 요청함
	g_pNetWorkMgr->RequestReqNormalChat( info );

	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Normal()
// D : 일반 채팅 메시지를 서버로부터 수신한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Normal( PS_SCP_NOTIFY_CHAT info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();
	CHTString strSenderName;
	strSenderName.HT_hrCleanUp();

	// 보낸사람의 Key ID가 넘어오므로 그것을 바탕으로 보낸사람의 ID를 구함
	if( info->nID < 10000 )
		strSenderName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->nID );
	else
		g_sNPCSystem->HT_vNPCSystem_GetName( (info->nID-10000), strSenderName );

	// 보낸 사람 불명일 경우 리턴한다.
	if(strSenderName.HT_bIsEmpty())return;
	// 다른사람이 보낸 메시지
	if( SERVEROBJECT_IS_CHARACTER( info->nID  ) )
		strCompoundedMsg = strSenderName+_T(": ")+info->szMsg;
	else
		strCompoundedMsg = info->szMsg;

	//	주시전 지역에서는 다른 주신의 메시지는 특수문자 처리한다.
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		//	주신코드 보정해주기
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

	// 0:채팅창, 1:머리풍선, 2:채팅창과 머리풍선 모두
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
//				귓속말 채팅
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Whisper( CHTString token, CHTString sChatMsg )
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// 당신은 채팅 금지 상태입니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	//	분리해 내자
	char chName[MAX_CHAT_LENGTH];
	strcpy (chName, "");
	//HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
	//strncpy( tokenMsg, sChatMsg, MAX_CHAT_LENGTH );

	//	token 에 아무것도 없을떄
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
    
	//	주신 셋팅
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
			// 귓속말 메시지 전송을 서버에 요청함
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
		// 귓속말 메시지 전송을 서버에 요청함
		g_pNetWorkMgr->RequestReqWhisperChat(info);
	}

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_WhisperChatting : %s-%s", info->szName, info->szMsg );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	if (!strcmp(info->szMsg,"/乖狼꾑욋"))  //fors_debug iwant
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
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "죽은 상태에서는 사용할 수 없습니다." );

			}
	}
	if (!strcmp(info->szMsg,"/乖狼看干"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1302;
		 for (int i=10553 ; i<10569 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	if (!strcmp(info->szMsg,"/乖狼88莖쑨"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1298;
		 for (int i=10536 ; i<10547 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	 if (!strcmp(info->szMsg,"/乖狼긴��"))
	 {
		 int ibodyid=0;
		 ibodyid	= g_pEngineHandler->HT_iCreateMonster( 2570, HTvector3( 100, 100, 100 ) );
		 			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
			g_pEngineHandler->HT_hrMoveObject(ibodyid, vecTempPos );

	 }

	// 메시지를 보낸 사림이 자기 자신이면 자신에게 보낼 수 없다는 메시지를 출력한다.
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
		// 이름을 이름 리스트에 저장한다.
		this->HT_vAddName( 1,  chName );
		//	그리고 귓속말 창에 이름을 셋팅한다.
		m_strWisperName = chName;
	}

	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper()
// D : 귓속말 메시지를 서버로부터 수신한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Whisper( PS_SCP_NOTIFY_WHISPER_CHAT info )
{
	CHTString strCompare;
	CHTString strCompoundedMsg, szMessage;
	strCompare.HT_hrCleanUp();
	strCompoundedMsg.HT_hrCleanUp();

	strCompare = g_oMainCharacterInfo.szCharName;

	//	마지막으로 귓속말 보낸 상대
	m_strLastRiciveWisperName = info->szName;
	
	// %s의 귓말
	m_szMsgName = info->szName;
	HT_vChatting_SetMessage( eMsgCommonChatWhisperReceive, &szMessage );

	// 메인 캐릭터(자기 자신)의 이름과 귓속말 메시지에서 받은 이름이 같으면
	if( strCompare.HT_iStringCompare(info->szName)==0 )
	{
		// 보낸 귓속말 메시지임을 표시
		// %s의 귓말: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		// 메시지를 등록한다 (창에 렌더링 된다.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[0]);
	}
	else
	{
		// 받은 귓속 말 메시지임을 표시
		// %s의 귓말: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		//	주시전 지역에서는 다른 주신의 메시지는 특수문자 처리한다.
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

		// 메시지를 등록한다 (창에 렌더링 된다.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);

		// 이름을 이름 리스트에 저장한다.
		this->HT_vAddName( 2,  info->szName );
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper_Result()
// D : 귓속말 메시지의 전송결과를 서버로부터 수신한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveDataResult_Whisper( PS_SCP_RESP_WHISPER_CHAT info )
{
	CHTString strTemp, szMessage;

	switch(info->byResult)
	{
		case 0x00:
		{
			// 보낸 귓속말 메시지임을 표시
			m_szMsgName = m_strWisperName;
			HT_vChatting_SetMessage( eMsgCommonChatWhisperSend, &szMessage ); // %s에게 귓말
			strTemp.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
			// 메시지를 등록한다 (창에 렌더링 된다.)
			this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strTemp, 
									g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
		}
			break;
		case REPLY_WHISPER_CHAR_FAIL:
			HT_vChatting_SetMessage( eMsgCommonChatWhisperNotSend, &szMessage ); // %s에게 귓말
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, szMessage, g_ColorTable[6], g_ColorTable[0]);
			break;
		case REPLY_WHISPER_REJECT :
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, _T("죄송합니다. 현재 다른 업무 중으로 귓말 상담에 응할 수 없습니다."), g_ColorTable[6], g_ColorTable[0]);
			break;
		default:;
	}
}

//-------------------------------------------------------------------------------
// Add by 20021130Tenma
// Description:
//					그룹 채팅
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Group(CHTString sChatMsg, HTbyte byMsgType)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// 당신은 채팅 금지 상태입니다.
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

	//	파티
	if( info->byMsgType == MESSAGE_PARTY )
		info->byTextColor	= 7;
	//	길드
	else if( info->byMsgType == MESSAGE_GUILD )
		info->byTextColor	= 5;
	//	아쉬람연합
	else if( info->byMsgType == MESSAGE_GUILD_ALLIANCE )
		info->byTextColor	= 6;

	// 메시지가 최대 길이 제한을 초과 하였는가?
	if( sChatMsg.HT_nGetSize() > MAX_GROUPCHAT_LENGTH )
	{
		// 메시지가 너무 길다는 메시지
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// 정상적인 경우
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_GROUPCHAT_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// 메시지 전송을 서버에 요청함
		g_pNetWorkMgr->RequestGroupChat( info );
	}

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_NotifyMessage()
// D : 공지사항 메시지를 서버에 전송한다.
//  
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_NotifyMessage(CHTString sChatMsg)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// 당신은 채팅 금지 상태입니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	MSG_Broadcast* info = HT_NULL;
	info = new MSG_Broadcast;

	info->byMsgType		= 1;
	info->byBgColor		= 0;			    // 채팅 메세지 배경색
	info->byTextColor	= 15;			    // 채팅 메세지 배경색
	info->byTrimuriti	= 0;

	// 메시지가 최대 길이 제한을 초과 하였는가?
	if( sChatMsg.HT_nGetSize() > MAX_NOTIFY_LENGTH )
	{
		// 메시지가 너무 길다는 메시지
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_MESSAGEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// 정상적인 경우
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_NOTIFY_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// 메시지 전송을 서버에 요청함
		g_pNetWorkMgr->ReqNotifyMessage( info );
	}

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_GlobalNotifyMessage()
// D : 전월드에 공지사항을 날린다.
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

		// 파티말 메시지임을 표시
		// [파티]
		HT_vChatting_SetMessage( eMsgCommonSystemParty, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	주시전 지역에서는 다른 주신의 메시지는 특수문자 처리한다.
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

		// 아쉬람 메시지임을 표시
		// [아쉬람]
		HT_vChatting_SetMessage( eMsgCommonSystemAshuram, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	주시전 지역에서는 다른 주신의 메시지는 특수문자 처리한다.
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

		// 파티말 메시지임을 표시
		// [아쉬람]
		HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoinBrackets, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	주시전 지역에서는 다른 주신의 메시지는 특수문자 처리한다.
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
// D : 공지사항 메시지를 서버로부터 수신한다.
//     S_SCP_NOTIFY_MESSAGE.szName은 공지사항에서 사용하지 않으므로 후에 삭제한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Notify( MSG_Broadcast* info )
{
	//	버퍼NPC팝메시지(7) 전투명령서(4), 호외(5)일때
	if( info->byMsgType == 7 || info->byMsgType == 4 || info->byMsgType == 5 )
	{
		//	같은 주신이 아니면 스킵
		if( info->byMsgType == 4 )
		{
			if( g_oMainCharacterInfo.byTrimuriti != info->byTrimuriti )
				return;
		}
		//	디스플레이 중이 아닐때
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
		//	디스플레이 중 일대
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
		//	공지 메시지를 받으면 사운드를 틀어준다.
		//	주신선택 메시지가 아닐때
		if( info->byBgColor != 14 )
			g_pEngineHandler->HT_hrPlaySound( 33509, 3 );

		//	공지
		CHTString szNotice, szMsgWholeNotice;
		HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szNotice );
		HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /전체공지
		
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
			//	공지창 켬
			g_pNotifyWindow->HT_vNotify_SetOn();
			g_pNotifyWindow->HT_vNotify_SetText( info->szMsg );

			if( info->byMsgType != MESSAGE_SERVERMSG )
			{
				szNotice += info->szMsg;

				int Length = sizeof(info->szMsg);
				char szNotipy[1024];

				szNotice += info->szMsg;
				if( szNotice.HT_nGetSize() < 256 )			//	사이즈가 적당할때만 시스템창에 공지
				{
					//	[공지]
					CHTString strTemp;
					HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
					for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
					{
						//	시스템창에 공지
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
		//	"/공지"
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
			if( szNotice.HT_nGetSize() < 256 )			//	사이즈가 적당할때만 시스템창에 공지
			{
				//	[공지]
				CHTString strTemp;
				HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );

				for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
				{
					//	시스템창에 공지
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
			//	주신선택 메시지일때
			if( info->byBgColor == 14 )
			{
				//	시스템 창으로 보냄
				this->HT_vSaveHistory(HISTORY_MESSAGE_TYPE_NOTIFY, info->szMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor] );
			}
		}
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_History()
// D : 히스토리 메시지를 서버로부터 수신한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_History( PS_SCP_RESP_CHAR_HISTORY info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();

	// 시간 추가 표시할 것.
	// 공지사항 메시지임을 표시
	//strCompoundedMsg = _T("[히스토리테스트] ");
	HT_vChatting_SetMessage( eMsgCommonSystemHistory, &strCompoundedMsg );
	strCompoundedMsg = strCompoundedMsg+info->szContent;
	this->HT_vSaveHistory(info->wType, strCompoundedMsg, g_ColorTable[4], g_ColorTable[4]);

	HT_Trace(strCompoundedMsg);
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_ReqCharInfo( CHTString strCharname )
// D: GM이 다른캐릭터의 정보를 요청한다.
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
// D: GM이 다른캐릭터의 강제 퇴장 시킨다.
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
// D: 파일로 부터 공지사항을 서버에 순차적으로 전달한다.
// 서버에서는 전달 받은대로 클라이어트에 보냈다가 메시지를 다 받으면 한꺼번에 표시 해 준다.
//-------------------------------------------------------------------------------
HTRESULT
CHTChatting::NotifyFromFile( CHTString strFilename )
{
	FILE		*fp;
	HTtchar		in;			// 읽어 온 바이트
	HTint		iCount = 1;	// MAX_CHAT_LENGTH 만큼 글자를 카운트함
	HTtchar		inBytes[ MAX_CHAT_LENGTH+1 ];	// 읽어 온 바이트를 MAX_CHAT_LENGTH바이트까지 저장
	CHTString	strTemp;

	fp = fopen((HTtchar *)strFilename, "rt");
	// 파일을 열고, 열수 없었으면 에러를 표시한다.
	if( fp == NULL )
		return HT_FAIL;

	this->HT_vSetData_NotifyMessage( CHTString( "//START NOTIFY MESSAGE//" ) );
	
	//	메시지 버퍼를 초기화하고
	ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );

	while( (in = fgetc(fp)) != EOF )
	{
		inBytes[ iCount-1 ] = in;

		// MAX_CHAT_LENGTH 글자까지 입력 받은 후 널을 붙이고 메시지를 전달한다.
		if( iCount >= MAX_CHAT_LENGTH )
		{	
			// 마지막이 한글 바이트가 아닌 경우는 전체를 카피하여 보낸다
			if( in >= '!' && in <= '~' ) 
			{
				inBytes[ iCount ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	메시지 버퍼를 초기화하고
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				
				// 카운트를 초기화
				iCount = 1;
				
			}
			// 마지막이 한글 바이트인 경우에는 그 바이트를 다음번 첫번째에 저장하고 그 바이트를 제외하고 보낸다
			// 빠진 한글 바이트는 다음번에 같이 간다.
			else
			{
				inBytes[ iCount-1 ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	메시지 버퍼를 초기화하고
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				// 배열의 처음에 한글 앞바이트를 넣어놓고 카운트를 초기화
				inBytes[0] = in;
				iCount = 2;
			}
		}
		// MAX_CHAT_LENGTH 글자가 차지 않았으면 카운트 한다.
		else
			iCount ++;
	}

	//	파일을 닫고
	fclose( fp );

	// 남은 바이트들도 보냄
	inBytes[ iCount ] = '\0';
	strTemp.HT_szFormat("%s", inBytes);
	this->HT_vSetData_NotifyMessage( strTemp );
	this->HT_vSetData_NotifyMessage( CHTString( "//END NOTIFY MESSAGE//" ) );

	return HT_OK;
}



//-------------------------------------------------------------------------------
// HTvoid StartStopLogging( CHTString strFilename )
// D: 채팅로그 파일의 생성을 시작/ 중지한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::StartStopLogging()
{
	CHTString strTemp;

	// 채팅 로그 상태를 바꾼다. 저장 중이였다면 그만둔다
	if(m_bLogging)
	{
		HTint iRCode;
		
		// 파일이 열려 있다면 닫음.
		if(m_pLogFile != NULL)
		{

			struct tm *today;
			char charTimeBuffer[MAX_TIMESTAMP_SIZE];
			time_t tTimeDifference;
			time_t tCurrentTime;

			// 현재 시간을 구한다.
			time( &tCurrentTime );
			// 현재 시간과 Initialize Time을 한 시간과 차이를 구하여 현재 서버 시간을 구한다.
			tTimeDifference = g_tInitServerTime + ( g_tInitClientTime - tCurrentTime );

			// 구한 현재 서버시간을 가지고 tm 구조체를 생성한다.
			today = localtime( &tTimeDifference );
			strftime( charTimeBuffer, MAX_TIMESTAMP_SIZE, "[%Y/%m/%d %H:%M:%S]", today );

			// 대화 내용 저장을 중지함을 파일에 표시
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
			fprintf( m_pLogFile, "%s %s\n",charTimeBuffer, strTemp.HT_szGetString() );
			fflush( m_pLogFile );

			// 닫는 마커를 파일에 표시, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n\n");
			fflush( m_pLogFile );

			iRCode = fclose( m_pLogFile );
		}
		if(iRCode == 0)
		{
			m_pLogFile = NULL;
			m_bLogging = HT_FALSE;
			//strTemp = "대화 내용을 저장을 종료합니다.";
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
		}
		else //strTemp = "로그 파일을 닫는데 실패 하였습니다. 대화 내용을 계속 저장합니다.";			
			HT_vChatting_SetMessage( eMsgChatLogFileCloseErr, &strTemp );
	}
	// 저장 중이 아니라면 저장을 시작한다.
	else
	{
		// 파일이 닫혀 있다면 연다.
		if( m_pLogFile == NULL )
		{
			m_pLogFile = fopen( "chat_log.txt", "at+" );
			// 파일이 없는경우 (윗 함수에서 NULL 이 리턴된다)
			if( m_pLogFile == NULL ) m_pLogFile = fopen( "chat_log.txt", "w" );
		}
		// 성공적으로 파일을 열었다.
		if( m_pLogFile )
		{
			// 여는 마커를 파일에 표시, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n");
			fflush( m_pLogFile );
			//strTemp = "대화 내용을 파일로 저장합니다.";
			HT_vChatting_SetMessage( eMsgChatSaveStart, &strTemp );
			m_bLogging = HT_TRUE;
		}
		// 파일을 여는데 실패 하였다.
		else //strTemp = "로그 파일을 여는데 실패하였습니다. 대화 내용 저장을 시작 할 수 없었습니다.";
			HT_vChatting_SetMessage( eMsgChatLogFileOpenErr, &strTemp );
	}
	this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
}


//-------------------------------------------------------------------------------
// HTvoid addName( HTint type, CHTString strName )
// D: 채팅 대상 이름 리스트에 이름을 등록한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vAddName( HTint type, CHTString strName )
{
	//	같은 이름 찿기
	for( HTint i= 0 ;i<m_iNameListNum ; i++ )
	{
		if( strName.HT_iStringCompare( m_strWhisperNameList[i] ) == 0 )
			return;
	}

	//	현재 9개가 넘으면
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
// D: 서버에 캐릭터 위치 정보를 요청함
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
	// 메시지가 최대 제한 길이보다 긴 경우
	else if(strlen(pcharName) > SZNAME_LENGTH){
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_NAMEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// 정상적인 경우
	else
	{
		S_GCSP_REQ_CHARACTER_SEARCH* info = HT_NULL;
		info = new S_GCSP_REQ_CHARACTER_SEARCH;
		// 정보를 복사, 조합한다.
		CHTString::HT_hrStringCopy(info->szCharName, pcharName, SZNAME_LENGTH+1);
		// 서버에 캐릭터 위치 정보를 요청함
		g_pNetWorkMgr->RequestReqCharLocation( info );
		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send__CHARACTER_SEARCH: %s", info->szCharName );
		//if(	g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		HT_DELETE( info );
	}
}


//-------------------------------------------------------------------------------
// HTvoid HT_vChatting_SetWisper( CHTString )
// D : 외부에서 귓속말 상태를 설정한다.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetWisper( CHTString strWisperName )
{
	//	채팅 윈도우 스타일
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	// 현재 노드의 이름을 귓속말 대상이름으로 설정한다.
	m_strWisperName			= strWisperName;
    // Edit No 1
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWisperName.HT_szGetString() );
	m_strChatMessage.HT_hrCleanUp();
}


//-------------------------------------------------------------------------------
// ...
// D : 귓속말 대화상대 저장하는 대화상자 컨트롤
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_Whisper_Dlg_Check()
{
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_WHISPERLISTWND ) )
	{
		m_bNameListActive = HT_TRUE;

		//	채팅 윈도우 스타일
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
// D : 저장된 메세지와 히스토리 정렬
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
		//	글자를 대입
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// 마지막 바이트가 글자의 시작이 아닌경우에는
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
			//	단어단위의 개행이 필요할 경우, 공백 문자를 파악하여 공백 문자까지 다시 되돌린다.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	필리핀
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	인도네시아
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

			//	첫번째 문장
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
		//	글자를 대입
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// 마지막 바이트가 글자의 시작이 아닌경우에는
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
			//	단어단위의 개행이 필요할 경우, 공백 문자를 파악하여 공백 문자까지 다시 되돌린다.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	필리핀
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	인도네시아
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

			//	첫번째 문장
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
// D : 마지막으로 귓속말 보낸 상대
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vChatting_SetLastSendWisper()
{
	//	채팅 윈도우 스타일
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	CHTString szCommand;
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper, &szCommand ); // /귓속말

	m_strChatMessage = szCommand;
	m_strChatMessage += _T(" ");
	m_strChatMessage += m_strLastRiciveWisperName.HT_szGetString();
	m_strChatMessage += _T(" ");

	//	Edit Box 2
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
	g_cImeMgr.vImeMgr_SetLimitRecivewParam( 1 );

	//	채팅 입력 활성화
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
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vChatting_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vChatting_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 지역
		case eMsgParamZoneNum	:	
			pszParam->HT_szFormat( "%d", m_iMessageVal ); break;
		// 다른 캐릭터 이름
		case eMsgParamOthercharName :
			*pszParam = m_szMsgName;
			break;

		default:
			break;
	}
}

//-------------------------------------------------------------------------------
// 전광판
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetOpenMessageItem( HTbyte byMsgType, HTint iItemIndex, HTbyte byItemKeyID )
{
	//	개인성점이 열려있으면 전광판 사용 못하게 한다.
	if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
		return;

	//	Open Msg Type
	//	0:없음, 1:아쉬람이름, 2:전광판, 3:전투명령서
	m_byChat_OpenMsgType = byMsgType;
	CHTString strTemp;
	if( m_byChat_OpenMsgType == 1 )
	{
		//	아쉬람 이름을 입력해 주십시오
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputAshramName, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 2 )
	{
		//	전광판 내용을 입력해 주십시오
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputOpenMessage, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 3 )
	{
		//	전투명령서 내용을 입력해 주십시오
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputCombatMessage, &strTemp, _T(""), _T("") );
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_OPENMESSAGE, 1, strTemp.HT_szGetString() );

	//	전광판 아이템
	m_iOpenMessageItemIndex = iItemIndex;
	//	전광판 아이템 종류
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
		// 당신은 채팅 금지 상태입니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	CHTString sChatMsg;
	sChatMsg = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_OPENMESSAGE, 2 );

	//	길드 이름의 경우
	if( m_byChat_OpenMsgType == 1 )
	{
		//	길드 생성을 요청한다.
		if(HT_SUCCEED(g_cGuildSystem->HT_hrNetWork_CSP_REQ_CREATE_GUILD( sChatMsg )))
		{
			this->HT_vChatting_DelOpenMessageItemBox();
		}
	}
	//	전광판과 전투명령서일경우
	else if( m_byChat_OpenMsgType == 2 || m_byChat_OpenMsgType == 3 )
	{
		// 메시지가 최대 길이 제한을 초과 하였는가?
		if( sChatMsg.HT_nGetSize() > 80 )
		{
			// 메시지가 너무 길다는 메시지
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
			// 메시지 전송을 서버에 요청함
			g_pNetWorkMgr->ReqNotifyMessage( info );

			//-----디버깅 테스트를 위하여-----//
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

//-전광판 아이템을 사용하여 창을 열면 그동안 키보드로 입력한 명령들이 나옴
//-전광판 아이템을 사용하여 창에 메시지를 입력한 뒤 엔터키를 누르면 메시지가 삭제
//-전광판 아이템을 사용하여 창에 영문 입력시 단축키로 인식, 실행 됨

//-------------------------------------------------------------------------------
//	채팅 블럭
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
//	채팅 로그
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetChatLog( HTint iType, CHTString strMsg, HT_COLOR clColor )
{
	//	뒤로 한칸씩 땡긴다.
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
		//	글자를 대입
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// 마지막 바이트가 글자의 시작이 아닌경우에는
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
			//	단어단위의 개행이 필요할 경우, 공백 문자를 파악하여 공백 문자까지 다시 되돌린다.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	필리핀
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	인도네시아
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

			//	뒤로 한칸씩 땡긴다.
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
		//	이미 문장의 절반 이상이 위의칸에 삽입됐을때
		if( bChangeMsg == HT_TRUE )
		{
			ZeroMemory( szMsg, 512 );
			strncpy( szMsg, m_oChat_SaveOpenMsg[0].szMsg, strlen(m_oChat_SaveOpenMsg[0].szMsg) );
			ZeroMemory( &m_oChat_SaveOpenMsg[0], 128 );
			strncpy( m_oChat_SaveOpenMsg[0].szMsg, szTemp, strlen(szTemp) );
			strncpy( szTemp, szMsg, strlen(szMsg) );
		}

		//	뒤로 한칸씩 땡긴다.
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
	//void HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// 스크롤바 컨트롤에 최대 값을 변경 합니다.

	//	채팅로그창 초기화
	for( HTint i=0 ; i<_CHAT_CHAT_LOG_NUM ; i++ )
	{
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+i, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+i, _T("") );
	}

	//	일반메시지
	HTint iScrolBar;
	HTint iChatCount = 0;
	HTbool bChatDisplay;
	if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG1 ) )
	{
		iScrolBar = g_cUIManager->HT_GetScrollBarValue( _DIALOG_CHATLOG1, 1 );
		
		for( i=iScrolBar ; i<CHATLOG_MAX_COUNT ; i++)
		{
			bChatDisplay = HT_FALSE;
			//	전체 찍기면 무조건 셋팅
			if( m_bChat_ChatLogConfig[0] )
			{
				bChatDisplay = HT_TRUE;
			}
			else
			{
				//	파티
				if( m_bChat_ChatLogConfig[1] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_PARTY )
						bChatDisplay = HT_TRUE;
				}
				//	아쉬람
				if( m_bChat_ChatLogConfig[2] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
						bChatDisplay = HT_TRUE;
				}
				//	연합
				if( m_bChat_ChatLogConfig[3] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ALLIANCE )
						bChatDisplay = HT_TRUE;
				}
				//	귓속말
				if( m_bChat_ChatLogConfig[4] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_WISPER )
						bChatDisplay = HT_TRUE;
				}
				//	귓속말
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
	//	전광판 메시지
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


//	작업중 메시지
HTvoid
CHTChatting::HT_vChatting_WorkingMsg()
{
	return;

	CHTString strTemp;
	strTemp.HT_hrCleanUp();
	////	작업중 메시지 카운트
	//switch( m_iChat_MsgCount )
	//{
	//	case 0 :	strTemp = _T("재구성 작업중입니다.");	break;
	//	case 1 :	strTemp = _T("재구성 작업중입니다..");	break;
	//	case 2 :	strTemp = _T("재구성 작업중입니다...");	break;
	//	case 3 :	strTemp = _T("재구성 작업중입니다....");	break;
	//	case 4 :	strTemp = _T("재구성 작업중입니다.....");	break;
	//	case 5 :	strTemp = _T("(재구성중) -.-");	break;
	//	case 6 :	strTemp = _T("(재구성중) -.-;;");	break;
	//	case 7 :	strTemp = _T("(재구성중) -.-;;;");	break;
	//	case 8 :	strTemp = _T("(재구성중) ^^; /('')/ l(``)l ^^");	break;
	//	case 9 :	strTemp = _T("(재구성중) 좀 더 편리한 기능으로 완성하기 위한 작업이 진행중입니다.");	break;
	//	case 10 :	strTemp = _T("(재구성중) 흠.. 열심히 작업중입니다. 조금만 더 기다려 주세요... ^^");	break;
	//	case 11 :	strTemp = _T("(재구성중) 흠.. 불철주야 작업중입니다. 조금만 더 기다려 주세요... ^^");	break;
	//	case 12 :	strTemp = _T("(재구성중) T.T 흑흑.. 조금만 더 기다려주세요...");	break;
	//	case 13 :	strTemp = _T("(재구성중) T.T 흑흑.. 집에를 못들어가여...");	break;
	//	case 14 :	strTemp = _T("(재구성중) T.T 흑흑.. 집에 가고 싶어여... ^^");	break;
	//	case 15 :	strTemp = _T("(재구성중) T.T 흑흑.. 술도 마시고 싶어여... ^^");	break;
	//	case 16 :	strTemp = _T("(재구성중) 그래도 목이 빠져라 기다리는 유저님들을 위해 오늘밤도 불태운답니다.");	break;
	//	case 17 :	strTemp = _T("(재구성중) 불 날것 같아여... WWWW");	break;
	//	case 18 :	strTemp = _T("(재구성중) ...!!!");	break;
	//	case 19 :	strTemp = _T("(재구성중) 너무 쪼우지 마세요");	break;
	//	case 20 :	strTemp = _T("(재구성중) 이제 그만 누르시면 안될까요? ^^");	break;
	//	case 21 :	strTemp = _T("(재구성중) ...");	break;
	//	case 22 :	strTemp = _T("(재구성중) ..");	break;
	//	case 23 :	strTemp = _T("(재구성중) .");	break;
	//	case 24 :	strTemp = _T("(재구성중) 끝날줄 알았죠?");	break;
	//	case 25 :	strTemp = _T("(재구성중) ...");	break;
	//	case 26 :	strTemp = _T("(재구성중) V3 작업을 하는 와중에서도 꼭 하나 하고 싶은것이 있었는데...");	break;
	//	case 27 :	strTemp = _T("(재구성중) 뭔지 가르쳐 드릴까여?");	break;
	//	case 28 :	strTemp = _T("(재구성중) 그럼 뭐 해줄래요? ㅋㅋ");	break;
	//	case 29 :	strTemp = _T("(재구성중) 친구분들 좀 더 많이 모시고 오셔서 탄트라 해주세요");	break;
	//	case 30 :	strTemp = _T("(재구성중) 뭔가 하면여..");	break;
	//	case 31 :	strTemp = _T("(재구성중) 탄트라의 바닥 즉 땅을 좀더 미려하게 바꾸거 싶었답니다.");	break;
	//	case 32 :	strTemp = _T("(재구성중) 꼭 하고 싶었었는데...");	break;
	//	case 33 :	strTemp = _T("(재구성중) 너무 대규묘 작업이라 진행하지 못했네요.. 아쉬어여(너무)");	break;
	//	case 34 :	strTemp = _T("(재구성중) ...");	break;
	//	case 35 :	strTemp = _T("(재구성중) ..");	break;
	//	case 36 :	strTemp = _T("(재구성중) .");	break;
	//	case 37 :	strTemp = _T("(재구성중) ㅋㅋ 유저님들의 반응이 좋으면 푸념 리플은 계속 됩니다.");	break;
	//	case 38 :	strTemp = _T("(재구성중) 그럼 Have nice day !!! 그리고 즐탄!!!");	break;
	//	default	:	strTemp = _T("재구성 작업중입니다.");	break;
	//}

	strTemp = _T("^^");
    g_cChatting->HT_vArrangeSavedHistory( strTemp.HT_szGetString(), g_ColorTable[12]);
	g_cChatting->HT_vChatting_SetSystemTextList();

	//	작업중 메시지 카운트
	m_iChat_MsgCount++;
	if( m_iChat_MsgCount > 38 )
		m_iChat_MsgCount = 0;
}
