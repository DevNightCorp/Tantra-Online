//======================================================================
// CHTChatting.cpp
// Ã¤ÆÃ °ü·Ã ¸Þ½ÃÁö °ü¸®
// (ÁÖ)ÇÑºû¼ÒÇÁÆ® °ÔÀÓ°³¹ßÆÀ Á¤ÀÇ±Ô		.......... ÃÖÃÊÀÛ¼º
// (ÁÖ)ÇÑºû¼ÒÇÁÆ® °ÔÀÓ°³¹ßÆÀ Á¤´ëÈ£		2002.09.13 Ãß°¡/¼öÁ¤
// (ÁÖ)ÇÑºû¼ÒÇÁÆ® °ÔÀÓ°³¹ßÆÀ ¼­¸í¼®		2002.10.22 Ãß°¡/¼öÁ¤20021022Tenma
// (ÁÖ)ÇÑºû¼ÒÇÁÆ® °ÔÀÓ°³¹ßÆÀ Á¤ÀÇ±Ô		2003.ÀÌÈÄ
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

// Ã¤ÆÃÃ¢ÀÌ ºñÈ°¼ºÀÎ »óÅÂ¿¡¼­ ¸Þ½ÃÁö¸¦ ¹Þ¾ÒÀ» °æ¿ì Ã¤ÆÃ ¹öÆ°ÀÌ ±ôºýÀÌ´Â ½Ã°£À» Á¶ÀýÇÑ´Ù. (ms)
#define CHATTING_BUTTON_FLASHING_INTEVAL		1000

extern CHTWindowManager*			g_CGame;

CHTChatting::CHTChatting()
{
	m_bChatStatusOn			= HT_FALSE;				// Ã³À½¿¡´Â ÀÔ·Âµµ ¾È¹Þ´Â´Ù.
	m_IMEStatus				= IME_STATUS_ENGLISH;	// Ã³À½¿¡´Â ÇÑ±Û ÀÔ·Â ¸ðµåÀÌ´Ù.

	// Ã¤ÆÃ ¸Þ½ÃÁö ÃÊ±âÈ­
	m_strChatMessage.HT_hrCleanUp();
	// ±Ó¼Ó¸» ¹Þ´Â »ç¶÷ ÀÌ¸§ ÃÊ±âÈ­
	m_strWisperName.HT_hrCleanUp();

	// ´ëÈ­³»¿ëÀ» ÆÄÀÏ·Î ·Î±ëÀ» Ã³À½¿¡´Â ´ç¿¬È÷ ¾ÈÇÑ´Ù.
	m_bLogging = HT_FALSE;
	// Ã³À½¿¡´Â ³Î(ÆÄÀÏÀÌ ¿­·Á ÀÖÁö ¾ÊÀ½)
	m_pLogFile = NULL;

	m_iNameListNum = 0;
	for( HTint i=0 ; i<_MAX_SAVED_NAMELIST_NUM ; i++ )
	{
		m_strWhisperNameList[i].HT_hrCleanUp();
	}
	m_iChat_WhisperReadIndex = 0;

	// °øÁö»çÇ× ¹®ÀÚ¿­ ¼ÂÆÃ
	m_pNotifyBuffer = (HTtchar *)malloc( 1000 * sizeof(HTtchar) );
	// 20030123Tenma_test ÀÓ½Ã·Î Ã³À½ °øÁö»çÇ× ¶ç¿ï ¹®ÀÚ¿­
	LoadString(g_hInstance, IDS_NOTIFY_MSG_TEMP, m_pNotifyBuffer, 1000);

	for (i=0; i<_MAX_SAVED_MESSAGE_NUM; i++)		ZeroMemory(&m_oSavedChatMsg[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_HISTORY_NUM; i++)		ZeroMemory(&m_oSavedHistory[i], sizeof(_MESSAGE));
	for (i=0; i<_MAX_SAVED_NAMELIST_NUM; i++)		m_strNameList[i].HT_hrCleanUp();

	//	¸¶Áö¸·À¸·Î ±Ó¼Ó¸» º¸³½ »ó´ë
	m_strLastRiciveWisperName.HT_hrCleanUp();
	//	/Å»Ãâ 3ÃÊ¿¡ ÇÑ¹ø¾¿ º¸³»°Ô ÇÏ±â À§ÇØ
	m_dwEscapeSaveTime = 0;
}

CHTChatting::~CHTChatting()
{	
	// Ã³À½ °øÁö»çÇ× ¹öÆÛ¿¡ ¹®ÀÚ¿­ÀÌ ³²¾Æ ÀÖÀ¸¸é ¹®ÀÚ¿­À» ºñ¿î´Ù 20030123Tenma_test
	if( m_pNotifyBuffer != NULL )
	{
		// °øÁö»çÇ× ¹®ÀÚ¿­ ¹è¿­À» ºñ¿î´Ù.
		free( m_pNotifyBuffer );
		m_pNotifyBuffer = NULL;
	}

	// ·Î±× ÆÄÀÏÀÌ ¿­·Á ÀÖÀ¸¸é ´Ý´Â´Ù.
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
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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

	//	Àü±¤ÆÇ ¾ÆÀÌÅÛ
	m_iOpenMessageItemIndex = 0;
	//	Àü±¤ÆÇ ¾ÆÀÌÅÛ Á¾·ù
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

	//	½ºÅ©·Ñ °ª
	m_iChat_ScrollChat = 0;
	m_iChat_ScrollSystem = 0;
	//	Ã¤ÆÃ ÀÔ·Â ¸ðµå
    m_bChat_InputMode = HT_FALSE;
	//	Open Msg Type
	//	0:¾øÀ½, 1:¾Æ½¬¶÷ÀÌ¸§, 2:Àü±¤ÆÇ, 3:ÀüÅõ¸í·É¼­
	m_byChat_OpenMsgType = 0;
	//	ÀÛ¾÷Áß ¸Þ½ÃÁö Ä«¿îÆ®
	m_iChat_MsgCount = 0;

	//	Ã¤ÆÃ ¼³Á¤
	for( i=0 ; i<5 ; i++ )
        m_bChat_ConfigChat[i] = HT_FALSE;
    m_bChat_ConfigChat[0] = HT_TRUE;
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, m_bChat_ConfigChat[0] );

	//	Ã¤ÆÃ ·Î±×
	ZeroMemory(	&m_oChat_ChatLog, sizeof(ChatLogStrut)*CHATLOG_MAX_COUNT );
	m_iChat_ChatLogCount = 0;
    for( i=0 ; i<6 ; i++ )
        m_bChat_ChatLogConfig[i] = HT_FALSE;
	m_bChat_ChatLogConfig[0] = HT_TRUE;
	ZeroMemory(	&m_oChat_SaveOpenMsg, sizeof(ChatLogStrut)*OPENMSG_MAX_COUNT );
	m_iChat_OpenMsgCount = 0;

	//	ÃÖÃÊ À©µµ¿ì ½ºÅ¸ÀÏ Ã¼Å©
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
	// ÇØ»óµµ ÃßÃâ
	HTint iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();

	//	[_DIALOG_CHATTINGBOX]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATTINGBOX, _T(""), 412, 250, g_cChatting->HT_vChatting_InputCheckForChatWnd, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTINGBOX, true );	// ¹è°æ¿µ¿ª Å¬¸¯½Ã ¸Ê ÇÈµÇ°Ô
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTINGBOX, 0, iScreenHeight-250-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTINGBOX, TRUE, 15,189, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 0, 170, 15, 189 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTINGBOX, 51, 0, 0, 202, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, g_cUIManager->m_nAlphaColor/100.0f ), 412, 48 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATTINGBOX, 51, HT_FALSE );
	//	¿Ü°û¼±
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
	//	½ºÅ©·Ñ ¹Ù
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 1, 1, 104, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 1, 100 );
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTINGBOX, 2, 1, 4, 95 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTINGBOX, 2, 100 );
	//	Button Ã¤ÆÃÃ¢ ¹Ù²Ù±â
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 9, 57, 1, 225, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 9, _T("C1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 228, 24, 16 );
	//	Button ¿£ÅÍ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button Ã¤ÆÃ¸ðµå
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 11, 159, 362, 202, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ¸ðµåº¯È¯
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 202, 50, 19 );
	//	Button Ã¤ÆÃ ¼³Á¤
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 2, 159, 27, 230, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 231, 60, 19 );//Ã¤ÆÃ¼³Á¤
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTINGBOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ³»¿ëÇ¥½Ã¼³Á¤
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTINGBOX, 2, strMessage );
	//	Button ÀüÃ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 3, 204, 88, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 231, 50, 19 );//ÀüÃ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 3 );
	//	Button ÆÄÆ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 4, 204, 139, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 231, 50, 19 );//ÆÄÆ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 4 );
	//	Button ¾Æ½¬¶÷
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 5, 204, 190, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 231, 55, 19 );//¾Æ½¬¶÷
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 5 );
	//	Button ¿¬ÇÕ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 6, 204, 246, 230, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 231, 50, 19 );//¿¬ÇÕ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 6 );
	//	Button ÁÖ¼Ò·Ï
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 7, 204, 297, 230, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 231, 55, 19 );//ÁÖ¼Ò·Ï
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTINGBOX, 7 );
	//	Button Ã¤ÆÃ·Î°í
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTINGBOX, 8, 204, 353, 230, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTINGBOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 231, 59, 19 );//Ã¤ÆÃ·Î±×
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
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING2BOX, true );	// ¹è°æ¿µ¿ª Å¬¸¯½Ã ¸Ê ÇÈµÇ°Ô
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING2BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING2BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING2BOX, 0, 170, 15, 239 );
	//	¿Ü°û¼±
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
	//	½ºÅ©·Ñ ¹Ù
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING2BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING2BOX, 1, 100 );
	//	Button Ã¤ÆÃÃ¢ ¹Ù²Ù±â
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 9, _T("C3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button ¿£ÅÍ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button Ã¤ÆÃ¸ðµå
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ¸ðµåº¯È¯
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button Ã¤ÆÃ ¼³Á¤
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//Ã¤ÆÃ¼³Á¤
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING2BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ³»¿ëÇ¥½Ã¼³Á¤
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING2BOX, 2, strMessage );
	//	Button ÀüÃ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//ÀüÃ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 3 );
	//	Button ÆÄÆ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//ÆÄÆ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 4 );
	//	Button ¾Æ½¬¶÷
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//¾Æ½¬¶÷
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 5 );
	//	Button ¿¬ÇÕ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//¿¬ÇÕ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 6 );
	//	Button ÁÖ¼Ò·Ï
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//ÁÖ¼Ò·Ï
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING2BOX, 7 );
	//	Button Ã¤ÆÃ·Î°í
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING2BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING2BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//Ã¤ÆÃ·Î±×
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
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_CHATTING3BOX, true );	// ¹è°æ¿µ¿ª Å¬¸¯½Ã ¸Ê ÇÈµÇ°Ô
	g_cUIManager->HT_MoveWindow( _DIALOG_CHATTING3BOX, 0, iScreenHeight-300-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_CHATTING3BOX, TRUE, 15,239, 38,11 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 170, 15, 239 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATTING3BOX, 0, 0, 1, 251, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 60.0f/100.0f ), 411, 48 );
	//	¿Ü°û¼±
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
	//	½ºÅ©·Ñ ¹Ù
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_CHATTING3BOX, 1, 1, 4, 240 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_CHATTING3BOX, 1, 100 );
	//	Button Ã¤ÆÃÃ¢ ¹Ù²Ù±â
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 9, 57, 1, 275, 58, 59 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 9, _T("C4"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 278, 24, 16 );
	//	Button ¿£ÅÍ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 1, 0, 0, 0, 0, 0, 1500, 0, 0 );
	//	Button Ã¤ÆÃ¸ðµå
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 11, 159, 362, 252, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 11 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatChangeChatMode, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ¸ðµåº¯È¯
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 11, strMessage );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 50, _T("Mode1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 362, 252, 50, 19 );
	//	Button Ã¤ÆÃ ¼³Á¤
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 2, 159, 27, 280, 160, 161, 1500, 60, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 2, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 281, 60, 19 );//Ã¤ÆÃ¼³Á¤
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_CHATTING3BOX, 2 );
	g_cUIManager->HT_SetScriptMessage( eMsgChatShowConfigChatMsg, &strMessage, _T(""), _T("") );	//	Ã¤ÆÃ³»¿ëÇ¥½Ã¼³Á¤
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHATTING3BOX, 2, strMessage );
	//	Button ÀüÃ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 3, 204, 88, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 3, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 88, 281, 50, 19 );//ÀüÃ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 3 );
	//	Button ÆÄÆ¼
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 4, 204, 139, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 4, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 139, 281, 50, 19 );//ÆÄÆ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 4 );
	//	Button ¾Æ½¬¶÷
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 5, 204, 190, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 5, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 281, 55, 19 );//¾Æ½¬¶÷
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 5 );
	//	Button ¿¬ÇÕ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 6, 204, 246, 280, 205, 206, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 6, eMsgChatUnion, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 281, 50, 19 );//¿¬ÇÕ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 6 );
	//	Button ÁÖ¼Ò·Ï
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 7, 204, 297, 280, 205, 206, 1500, 55, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 7, sMsgAddressAddress, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 297, 281, 55, 19 );//ÁÖ¼Ò·Ï
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATTING3BOX, 7 );
	//	Button Ã¤ÆÃ·Î°í
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATTING3BOX, 8, 204, 353, 280, 205, 206, 1500, 59, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATTING3BOX, 8, eMsgChatChatLog, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 353, 281, 59, 19 );//Ã¤ÆÃ·Î±×
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
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 3, 99, 210, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 3, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 65, 72, 19 );//È®ÀÎ
	//	Button Ãë¼Ò
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPENMESSAGE, 4, 99, 300, 65, 97, 98, 1500, 72, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPENMESSAGE, 4, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 300, 65, 72, 19 );//Ãë¼Ò

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
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//ÀüÃ¼
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_WHISPERLISTWND, 1, strMessage );

	//	[_DIALOG_CHATCONFIG]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATCONFIG, _T(""), 90, 100, g_cChatting->HT_vChatting_InputCheckForChatConfig, 0, HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATCONFIG, 5 );
	//	Button ÀüÃ¼
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 1, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//ÀüÃ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 1 );
	//	Button ÆÄÆ¼
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//ÆÄÆ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 2 );
	//	Button ¾Æ½¬¶÷
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//¾Æ½¬¶÷
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 3 );
	//	Button ¿¬ÇÕ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//¿¬ÇÕ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 4 );
	//	Button ±Ó¼Ó¸»¸®½ºÆ®
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATCONFIG, 5, eMsgChatList, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//¸®½ºÆ®
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATCONFIG, 5 );
    //63 UI_Button03_N_64X19.bmp
	//169, 175
	HT_vChatting_InputCheckForChatWnd(0, 0, 3);

	//	[_DIALOG_CHATLOG1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHATLOG1, _T("ChatLog"), 412, 465, g_cChatting->HT_vChatting_InputCheckForChatLog, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHATLOG1, 5 );
	//	ÁÙ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG1, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button ÀÏ¹Ý ¸Þ½ÃÁö
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 1 );
	//	Button Àü±¤ÆÇ ¸Þ½ÃÁö
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 2 );
	//	Button Ã¤ÆÃ¼³Á¤
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 3 );
	//	Button ÀúÀå
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 4 );
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG1, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG1, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG1, 5 );
	//	½ºÅ©·Ñ ¹Ù
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
	//	ÁÙ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 36, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 66, 1400, 406, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOG2, 0, 8, 3, 415, 1400, 406, 6 );
	//	Button ÀÏ¹Ý ¸Þ½ÃÁö
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 1, eMsgChatNormalMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 1 );
	//	Button Àü±¤ÆÇ ¸Þ½ÃÁö
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 2, eMsgChatOpenMsg, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 2 );
	//	Button Ã¤ÆÃ¼³Á¤
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 3, 159, 55, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 3, eMsgChatConfigChat, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 55, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 3 );
	//	Button ÀúÀå
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 4, 159, 174, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 4, eMsgChatSave, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 174, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 4 );
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOG2, 5, 159, 293, 430, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOG2, 5, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 293, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOG2, 5 );
	//	½ºÅ©·Ñ ¹Ù
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
	//	Button ÀüÃ¼
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 1, 175, 8, 6, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 1, HT_TRUE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 1, 63, 26, 0, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 1, eMsgCommonChatWhole, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 0, 64, 19 );//ÀüÃ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 1 );
	//	Button ÆÄÆ¼
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 20 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 2, 175, 8, 26, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 2, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 2, 63, 26, 20, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 2, eMsgCommonChatParty, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 20, 64, 19 );//ÆÄÆ¼
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 2 );
	//	Button ¾Æ½¬¶÷
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 40 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 3, 175, 8, 46, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 3, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 3, 63, 26, 40, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 3, eMsgCommonChatAshuram, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 40, 64, 19 );//¾Æ½¬¶÷
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 3 );
	//	Button ¿¬ÇÕ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 60 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 4, 175, 8, 66, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 4, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 4, 63, 26, 60, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 4, eMsgCommonCommandAshuramAlliance3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 60, 64, 19 );//¿¬ÇÕ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 4 );
	//	Button ±Ó¼Ó¸»
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 80 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 5, 175, 8, 86, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 5, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 5, 63, 26, 80, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 5, eMsgCommonCommandWhisper2, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 80, 64, 19 );//±Ó¼Ó¸»
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 5 );
	//	Button ½Ã½ºÅÛ
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 0, 169, 0, 100 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHATLOGCONFIG, 6, 175, 8, 106, 1400, 7, 9 );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_CHATLOGCONFIG, 6, HT_FALSE );
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHATLOGCONFIG, 6, 63, 26, 100, 65, 64 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHATLOGCONFIG, 6, eMsgChatSystem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 100, 64, 19 );//½Ã½ºÅÛ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHATLOGCONFIG, 6 );
}
//	Read Parse Msg
HTvoid CHTChatting::HT_vChatting_ReadParseMsg()
{
	HT_vChatting_SetMessage( eMsgCommonChatWhole			, &szWhole );			// ÀüÃ¼
	HT_vChatting_SetMessage( eMsgCommonChatAshuram			, &szAshuram );			// ¾Æ½¬¶÷

	HT_vChatting_SetMessage( eMsgCommonCommandWhole			, &szMsgWhole );		// /ÀüÃ¼
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper		, &szMsgWhisper );		// /±Ó¼Ó¸»
	HT_vChatting_SetMessage( eMsgCommonCommandAddress		, &szMsgAddress );		// /Ä£±¸µî·Ï
	HT_vChatting_SetMessage( eMsgCommonCommandAshuram		, &szMsgAshuram );		// /¾Æ½¬¶÷
	HT_vChatting_SetMessage( eMsgCommonCommandKick			, &szMsgKick );			// /Å±
	HT_vChatting_SetMessage( eMsgCommonCommandWin			, &szMsgCommandWin );	// ¸í·ÉÃ¢

	HT_vChatting_SetMessage( eMsgCommonCommandAS			, &szMsgAS );			// /GMÈ£Ãâ
	HT_vChatting_SetMessage( eMsgCommonCommandAS2			, &szMsgAS2 );			// /GMÈ£Ãâ2
	
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel		, &szMsgASCancel );		// /GMÈ£ÃâÃë¼Ò
	HT_vChatting_SetMessage( eMsgCommonCommandASCancel2		, &szMsgASCancel2 );	// /GMÈ£ÃâÃë¼Ò2

	HT_vChatting_SetMessage( eMsgCommonCommandASCheck		, &szMsgASCheck);		// /GMÈ£ÃâÈ®ÀÎ
	HT_vChatting_SetMessage( eMsgCommonCommandASCheck2		, &szMsgASCheck2 );		// /GMÈ£ÃâÈ®ÀÎ2
    
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildJoin	, &szMsgAshuramGuildJoin);	// /¾Æ½¬¶÷¿¬ÇÕ
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGuildLeave	, &szMsgAshuramGuildLeave );// /¾Æ½¬¶÷¿¬ÇÕÅ»Åð

	HT_vChatting_SetMessage( eMsgCommonCommandGuildMark		, &szMsgGuildMark );	// /±æµå¸¶Å©
	HT_vChatting_SetMessage( eMsgCommonCommandTrimuritiMark	, &szMsgTrimuritiMark ); // /ÁÖ½Å¸¶Å©

	HT_vChatting_SetMessage( eMsgCommonCommandInvisible		, &szMsgInvisible );	// /Åõ¸í
	HT_vChatting_SetMessage( eMsgCommonCommandWarp			, &szMsgWarp );			// /¿öÇÁ
	HT_vChatting_SetMessage( eMsgCommonCommandMove			, &szMsgMove );			// /ÀÌµ¿

	HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szMsgNotice );		// /°øÁö
	HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /ÀüÃ¼°øÁö
	HT_vChatting_SetMessage( eMsgCommonCommandAssistant		, &szMsgAssistant );	// /Á¶±³

	HT_vChatting_SetMessage( eMsgCommonCommandShout			, &szMsgShout );		// /¿ÜÄ¡±â
	HT_vChatting_SetMessage( eMsgCommonCommandParty			, &szMsgParty );		// /ÆÄÆ¼
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramNotice	, &szMsgGuildNotice );	// /°øÁö»çÇ×-±æµå¿ë
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramGrade	, &szMsgGuildGrade );	// /¾Æ½¬¶÷µî±Þ

	HT_vChatting_SetMessage( eMsgCommonChatParty			, &szParty );			// ÆÄÆ¼
	HT_vChatting_SetMessage( eMsgCommonCommandTrade			, &szTrade );			// ±³È¯
	HT_vChatting_SetMessage( eMsgCommonCommandEmerge		, &szEmerge );			// Å»Ãâ

	HT_vChatting_SetMessage( eMsgCommonCommandPartyPart		, &szMsgPartyPart );			// /ÆÄ
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramPart	, &szMsgAshuramPart );			// /¾Æ
	HT_vChatting_SetMessage( eMsgCommonCommandWholePart		, &szMsgWholePart );			// /Àü
	HT_vChatting_SetMessage( eMsgCommonCommandShoutPart		, &szMsgShoutPart );			// /¿Ü
	HT_vChatting_SetMessage( eMsgCommonCommandWhisperPart	, &szMsgWhisperPart );			// /±Ó

	HT_vChatting_SetMessage( eMsgCommonCommandDebugMode		, &szMsgDebugMode );			// Debug Mode
	HT_vChatting_SetMessage( eMsgCommonCommandBroadcastMode	, &szMsgBroadcastMode );		// BroadcastMode
	HT_vChatting_SetMessage( eMsgCommonCommandEngineCamera	, &szMsgEngineCamera );			// Use Engine Camera
	HT_vChatting_SetMessage( eMsgCommonCommandGoCamera		, &szGoCamera );				// Go Camera
	HT_vChatting_SetMessage( eMsgCommonCommandShowCursor	, &szShowCursor );				// ShowCursor

	HT_vChatting_SetMessage( eMsgCommonCommandDuel			, &szMsgDuel );				// Duel

	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance1	, &szMsgAshuramAllince1 );				// ¾Æ½¬¶÷ ¿¬ÇÕ1 /¿¬
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramAlliance2	, &szMsgAshuramAllince2 );				// ¾Æ½¬¶÷ ¿¬ÇÕ2 /¿¬ÇÕ
	HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoin		, &szMsgAshuramJoin );						// ¾Æ½¬¶÷ ¿¬ÇÕ

	HT_vChatting_SetMessage( eMsgCommonChatRoom		, &szMsgChatRoom );						// ¾Æ½¬¶÷ ¿¬ÇÕ// Ã¤ÆÃ¹æ
}

//	ÀÔ·Â ¸Þ¼¼Áö Ã³¸®
//	FromChatWnd
void CHTChatting::HT_vChatting_InputCheckForChatWnd(int iAction, int iTarget, int iTargetID)
{
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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
				// ´Ü, Ã¤ÆÃ¸ðµå°¡ 2ÀÏ¶§´Â ±×³É ³Ñ¾î°£´Ù.
				if (g_cChatting->m_bChat_InputMode)
					return;

				g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			}
		}
		//	Ã¤ÆÃ ¼³Á¤
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
		//	ÀüÃ¼
		else if( iTargetID == 3 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatWhole, &strMessage, _T(""), _T("") );	//	ÀüÃ¼
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
		//	ÆÄÆ¼
		else if( iTargetID == 4 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatParty, &strMessage, _T(""), _T("") );	//	ÆÄÆ¼
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
		//	¾Æ½¬¶÷
		else if( iTargetID == 5 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuram, &strMessage, _T(""), _T("") );	//	¾Æ½¬¶÷
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
		//	¿¬ÇÕ
		else if( iTargetID == 6 )
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonChatAshuramAlliance, &strMessage, _T(""), _T("") );	//	¾Æ½¬¶÷¿¬ÇÕ
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
		//	ÁÖ¼Ò·Ï
		else if( iTargetID == 7 )
		{
			if( g_cAddress->HT_iIsOn() )    g_cAddress->HT_vSetOff();
			else							g_cAddress->HT_vSetOn();
		}
		//	Ã¤ÆÃ ÀÔ·Â ¸ðµå
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
		//	Ã¤ÆÃ·Î±×
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
		//	Ã¤ÆÃÃ¢ º¯È¯
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

	// ¼û°ÜÁø´Ù¸é ´Ù½Ã º¸ÀÌ°Ô ¼³Á¤
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
		//	Ãë¼Ò
		if( iTargetID == -1 || iTargetID == 4 )
		{
			g_cChatting->HT_vChatting_DelOpenMessageItemBox();
		}
		//	È®ÀÎ
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
				//	±Ó¼Ó¸» »óÅÂ·Î ¸¸µé¾î ÁÖ°í..
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
		//	ÀÏ¹Ý ¸Þ½ÃÁö
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
		//	Àü±¤ÆÇ ¸Þ½ÃÁö
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
		//	Ã¤ÆÃ¼³Á¤
		else if( iTargetID == 3 )
		{
			//	ÀÏ¹Ý¸Þ½ÃÁöÃ¢ÀÏ¶§¸¸ »ç¿ë°¡´É
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG2 ) )
				return;
			//	ÄÑÁ® ÀÖÀ¸¸é ²¨°í ²¨Á® ÀÖÀ¸¸é ÄÑÀÚ
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
		//	ÀúÀå
		else if( iTargetID == 4 )
		{
			//	Write Chat Log File
			g_cChatting->JK_vChatting_ChatLogFile();
		}
		//	È®ÀÎ
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

	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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

//	Set Parse Msg  //fors_debug ÌØ±ð²ÎÊýµÄµØ·½
HTvoid CHTChatting::HT_vParseMsg( CHTString strCommand, CHTString strMessage )
{
	//	¸Þ½ÃÁö°¡ ¾øÀ¸¸é.
	if ( strMessage.HT_bIsEmpty() || strMessage.HT_nGetSize() <= 0 )
		return;

	HTtchar* pcMsg;
	HTtchar* token;
    // ±¸ºÐÀÚ(delimiter)·Î ½ºÆäÀÌ½º, ÅÇ, ¿£ÅÍ µîÀ¸·Î ÅäÅ«À» ±¸ºÐÇÑ´Ù.
	HTtchar seps[] = " \t\n";

	CHTString strTemp;
	strTemp = strMessage;
	pcMsg = strTemp.HT_szGetString();
	token = _tcstok(pcMsg, seps);

	// HK : µµ¿ò¸»¿¡ _tcstok()¿¡¼­ NULLÀÌ ³ª¿Ã ¼ö ÀÖ´Ù°í ³ª¿Â´Ù. ÀÌ°æ¿ì ¸®ÅÏ!
	if ( token == HT_NULL ) return;

	//	Ã¹¹øÂ° ±ÛÀÚ ÀúÀå
	CHTString strFirstChar;
	strFirstChar.HT_szFormat("%c", token[0] );

	//	ÆÄ½Ì ¸Þ½ÃÁöµé
	{
		//	Ã¤ÆÃ°ü·Ã
		//	ÀÏ¹ÝÃ¤ÆÃ
		if( strFirstChar.HT_iStringCompare("/") != 0 &&
			( strCommand.HT_iStringCompare( szWhole.HT_szGetString() ) == 0 || strCommand.HT_nGetSize() == 0 ) )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	ÀÏ¹ÝÃ¤ÆÃ - /ÀüÃ¼ || /Àü
		else if( CHTString::HT_iStringCompare(token, szMsgWhole.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, szMsgWholePart.HT_szGetString() ) == 0 
				|| CHTString::HT_iStringCompare(token, "/s") == 0 )
		{
			token = _tcstok(NULL, "");
			this->HT_vSetData_Normal(token);
		}
		//	ÀÏ¹Ý Ã¼ÆÃ ¿¹¿Ü
		else if(CHTString::HT_iStringCompare(token, _T("/À§Ä¡ÀúÀå") )==0 ||
				CHTString::HT_iStringCompare(token, _T("/SavePosition") )==0 )
		{
			this->HT_vSetData_Normal( strMessage );
		}
		//	±Ó¼Ó¸» Ã¤ÆÃ - /±Ó¼Ó¸» || /±Ó
		else if( CHTString::HT_iStringCompare(token, szMsgWhisper.HT_szGetString() )==0 
				|| CHTString::HT_iStringCompare(token, szMsgWhisperPart.HT_szGetString() )==0
				|| CHTString::HT_iStringCompare(token, "/w")==0 )
		{
			HTtchar* Temptoken = _tcstok(NULL, "");
			this->HT_vSetData_Whisper( token, Temptoken );
		}
		//	ÆÄÆ¼ Ã¤ÆÃ - /ÆÄÆ¼ || /ÆÄ
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
		//	±æµå Ã¤ÆÃ - /¾Æ½¬¶÷ || /¾Æ || ¾Æ½¬¶÷
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
		//	¾Æ½¬¶÷ ¿¬ÇÕ - /¿¬ || /¿¬ÇÕ || ¾Æ½¬¶÷¿¬ÇÕ
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
		//	¿ÜÄ¡±â Ã¤ÆÃ - /¿ÜÄ¡±â || /¿Ü
		else if(CHTString::HT_iStringCompare(token, szMsgShout.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, szMsgShoutPart.HT_szGetString() )==0 || 
				CHTString::HT_iStringCompare(token, "/y")==0 )
		{
		}
		//	±æµå ·©Å© ¹«¿© - /¾Æ½¬¶÷µî±Þ
		else if( CHTString::HT_iStringCompare(token, szMsgGuildGrade.HT_szGetString() ) ==0 ||
				CHTString::HT_iStringCompare(token, _T("/av") )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildSetRanking( token );
		}
		//	±æµå Á¤º¸ °»½Å - /°øÁö»çÇ×
		else if(CHTString::HT_iStringCompare(token, szMsgGuildNotice.HT_szGetString() )==0 )
		{
			token = _tcstok(NULL, "");
			g_cGuildSystem->HT_vNetWork_CSP_MSG_GuildUpdate( token );
		}
		else if( CHTString::HT_iStringCompare(token, szMsgChatRoom.HT_szGetString() ) == 0 )
		//else if(CHTString::HT_iStringCompare(token, _T("/Ã¤ÆÃ¹æ") )==0 ) 
		{
			//if( g_iInationalType == INATIONALTYPE_KOREA)	// ÀÏ´Ü ÇÑ±¹¿¡¼­¸¸ µÊ
			//{
				token = _tcstok(NULL, "");
				
				if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)	// ÀÌ¹Ì Ã¤ÆÃ¹æ°ú ¿¬°áÁßÀÌ¶ó¸é ÀÛµ¿ÇÏÁö ¾Ê´Â´Ù.
					return;

				g_cChatRoom->HT_vChatRoom_WindowPopup();
			//}
		}
		else if(CHTString::HT_iStringCompare(token, _T("/Å×½ºÆ®") )==0 )
		{/*
			// ±ÛÀÚ Ãâ·Â
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
		//	GM ¸í·É¾î_ GMÈ£Ãâ
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
				if (iCallStatus==1)		// ½ÇÆÐ
				{
					HT_vChatting_SetMessage( eMsgGMCallTreat	, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==0) // ¼º°ø
				{
					HT_vChatting_SetMessage( eMsgGMCallRegist	, &str );
					HTint iCallCound = m_oGMCall->HT_iGetCallCount();
					str.HT_szFormat(str, iCallCound);
				
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str );
				}
				else if (iCallStatus==-1)	// Àçµî·Ï ¿äÃ»
				{
					HT_vChatting_SetMessage( eMsgGMCallReRegist	, &str );
					//str.HT_szFormat("GMÈ£Ãâ ³»¿ëÀÌ µî·ÏµÇÁö ¾Ê¾Ò½À´Ï´Ù. ´Ù½Ã µî·ÏÇØ ÁÖ½Ã±â ¹Ù¶ø´Ï´Ù.");
				}

				HT_DELETE( m_oGMCall );
			}
		}// GMÈ£ÃâÈ®ÀÎ
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
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildJoin.HT_szGetString() ) == 0)	// ¾Æ½¬¶÷¿¬ÇÕ
		{	
			// Step 1. ÀÚ½ÅÀÌ ¸¶ÇÏ¶óÀÚÀÎÁö Á¶»çÇÏ¿© ¾Æ´Ï¸é ¸Þ½ÃÁö ¼ÛÃâ
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg5, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. ÀÚ½ÅÀÌ ¾Æ½¬¶÷¿¬ÇÕ »óÅÂÀÎÁö Á¶»çÇÏ¿© ÀÌ¹Ì ¸ÎÀº »óÅÂ¶ó¸é ¿¡·¯¸Þ½ÃÁö Ãâ·Â
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), _T(" ")) != 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg11, &strString );	// ÀÌ¹Ì ¾Æ½¬¶÷ ¿¬ÇÕÀ» ¸ÎÀº »óÅÂÀÔ´Ï´Ù.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// Step 3. ¼±ÅÃ¸ðµå·Î º¯°æÇÑ´Ù.
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg7, &strString );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );

					g_cGuildSystem->m_nAshuramGuildJoinMode = 1;
					g_cInterfaceCheck->HT_vSetCursor(CURSOR_SELECT_ANI);
				}

			}
		}
		else if(CHTString::HT_iStringCompare( token, szMsgAshuramGuildLeave.HT_szGetString() ) == 0)	// ¾Æ½¬¶÷¿¬ÇÕÅ»Åð
		{	
			// Step 1. ÀÚ½ÅÀÌ ¸¶ÇÏ¶óÀÚÀÎÁö Á¶»çÇÏ¿© ¾Æ´Ï¸é ¸Þ½ÃÁö ¼ÛÃâ
			if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg6, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			else
			{
				// Step 2. ¾Æ½¬¶÷ ¿¬ÇÕÀÌ µÇ¾î ÀÖ´Â »óÅÂÀÎÁö¸¦ Á¶»çÇÑ´Ù.
				if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), "") == 0)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg10, &strString );	// ¾Æ½¬¶÷ ¿¬ÇÕÀ» ¸ÎÀº ¾Æ½¬¶÷ÀÌ ¾ø½À´Ï´Ù.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else
				{
					// ¼­¹ö¿¡ ÆÐÅ¶ Àü¼ÛÇÏ±â (°ÅºÎÇÔ)
					g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,2,0);
				}
			}

		}
		//	GM ¸í·É¾î_Åõ¸í ¸ðµå
		else if(CHTString::HT_iStringCompare(token, szMsgInvisible.HT_szGetString() )==0)
		{
            if( g_oMainCharacterInfo.snTribe == 0x09 || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( g_oMainCharacterInfo.szCharName, 0x02 );
		}
		//	GM ¸í·É¾î_Chatting Block
		else if(CHTString::HT_iStringCompare(token, _T("/chatblock") )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMode( strMessage, 0x04 );
		}
		//	GM ¸í·É¾î_Æ¯Á¤ Áö¿ª ¿öÇÁ
		else if(CHTString::HT_iStringCompare(token, szMsgWarp.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_POSITION( strMessage );
		}
		//	GM ¸í·É¾î_Æ¯Á¤ Ä³¸¯ÅÍ ¿öÇÁ
		else if(CHTString::HT_iStringCompare(token, szMsgMove.HT_szGetString() )==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				g_cGMSystem->HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( strMessage );
		}
		//	¿ÀÁ÷ Å¬¶óÀÌ¾ðÆ®¿¡¼­¸¸ ÀÚ±âÀ§ Ä³¸¯ÅÍ ¾Èº¸ÀÌ°Ô ÇÏ´Â ¸í·Â¾î
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
		//	GM ¸í·É¾î_´Ù¸¥Ä³¸¯ÅÍ Á¤º¸º¸±â
		else if (CHTString::HT_iStringCompare(token, "/INFO")==0)
		{
			// ³ª¸ÓÁö ½ºÆ®¸µÀ» ¸ðµÎ ÅäÅ«À¸·Î »Ì¾Æ³¿
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharInfo( token );
		}
		//	GM ¸í·É¾î_´Ù¸¥Ä³¸¯ÅÍ ·Î±×¾Æ¿ô ½ÃÅ³¶§ - /Å±
		else if (CHTString::HT_iStringCompare(token, szMsgKick.HT_szGetString() )==0)
		{
			// ³ª¸ÓÁö ½ºÆ®¸µÀ» ¸ðµÎ ÅäÅ«À¸·Î »Ì¾Æ³¿
			token = _tcstok(NULL, "");
			if( token != NULL && g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				HT_vSetData_ReqCharClose( token );
		}
		//	GM ¸í·É¾î - ÆÄÀÏ·Î ºÎÅÍ ÀÐ¾î¼­ ÇÑ²¨¹ø¿¡ Ãâ·ÂÇÔ
		else if (CHTString::HT_iStringCompare(token, "/IDHANFILE")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				// ³ª¸ÓÁö ½ºÆ®¸µÀ» ¸ðµÎ ÅäÅ«À¸·Î »Ì¾Æ³¿
				token = _tcstok(NULL, "");

				// ÆÄÀÏÀ» ÀÐ°Å³ª ¸Þ½ÃÁö¸¦ º¸³»´Âµ¥ ½ÇÆÐÇÏ¿´À½.
				if( token == NULL || FAILED(this->NotifyFromFile(token)) )
				{
					CHTString szMessage;
					HT_vChatting_SetMessage( eMsgCommonSystemFile_Err, &szMessage );
					this->HT_vSaveHistory( 1, szMessage, g_ColorTable[12], g_ColorTable[0]);
				}
			}
		}
		//	GM ¸í·É¾î °øÁöÃ¢À¸·Î °øÁö
		else if(CHTString::HT_iStringCompare(token, szMsgWholeNotice.HT_szGetString() )==0 ||
				CHTString::HT_iStringCompare(token, "/IDHAN")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09  || g_bDevelopingMode )
            	this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM ¸í·É¾î_½Ã½ºÅÛÃ¢¿¡ °øÁö
		else if(CHTString::HT_iStringCompare(token, szMsgNotice.HT_szGetString() )==0 )
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
				this->HT_vSetData_NotifyMessage( strMessage );
		}
		//	GM ¸í·É¾î_¼­¹ö¿¡ ·Î±ëÀ» ½ÃÀÛ ¶Ç´Â ÁßÁö.
		else if(CHTString::HT_iStringCompare(token, "/CHATLOG")==0)
		{
			StartStopLogging();
		}
		//	GM ¸í·É¾î_// CHAR LOCATIONÀ» ¿äÃ»ÇÏ´Â ¸Þ½ÃÁö¸¦ º¸³¿
		else if(CHTString::HT_iStringCompare(token, "/CONNECT")==0)
		{
			if( g_oMainCharacterInfo.snTribe == 0x09 )// || g_bDevelopingMode )
			{
				token = _tcstok(NULL, "");
				this->HT_vSetData_CharacterLocation( token );
			}
		}
		//	°ÔÀÓ±â´É
		//	»ó°Å·¡
		else if(CHTString::HT_iStringCompare(token, "/t")==0 ||
				CHTString::HT_iStringCompare(token, "/T")==0 ||
				CHTString::HT_iStringCompare(token, "/trade")==0 ||
				CHTString::HT_iStringCompare(token, "/TRADE")==0 ||
				CHTString::HT_iStringCompare(token, szTrade.HT_szGetString() )==0 )
		{
			g_cExchangeSystem->HT_vExchange_SetClickTradeButton( HT_TRUE );
		}
		//	/Ä£±¸µî·Ï
		else if( CHTString::HT_iStringCompare(token, szMsgAddress.HT_szGetString() ) == 0 )
		{
			// ³ª¸ÓÁö ½ºÆ®¸µÀ» ¸ðµÎ ÅäÅ«À¸·Î »Ì¾Æ³¿
			token = _tcstok(NULL, "");
			g_cAddress->HT_vCSP_JoinAddressBook( token );
		}
		//	±æµå¸¶Å© ½ºÀ§Ä¡
		else if(CHTString::HT_iStringCompare(token, szMsgGuildMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vGuild_EmblemSwitch( szMsgGuildMark );
		}
		//	ÁÖ½Å¸¶Å© ½ºÀ§Ä¡
		else if(CHTString::HT_iStringCompare(token, szMsgTrimuritiMark.HT_szGetString() )==0)
		{
			g_cGuildSystem->HT_vTrimutiri_MarkSwitch( strMessage );
		}
        //	°®Èùµ¥¼­ ºüÁ®³ª¿À±â - /Å»Ãâ
		else if( CHTString::HT_iStringCompare(token, "/emerge")==0 || 
				 CHTString::HT_iStringCompare(token, szEmerge.HT_szGetString())==0 )
		{
			if( g_iInationalType != INATIONALTYPE_JAPEN )
			{
				//	/Å»Ãâ 3ÃÊ¿¡ ÇÑ¹ø¾¿ º¸³»°Ô ÇÏ±â À§ÇØ
				DWORD dwPassTime = timeGetTime();
				if( dwPassTime > m_dwEscapeSaveTime+3000 )
				{
					m_dwEscapeSaveTime = dwPassTime;
					g_pNetWorkMgr->RequestEscape();

					//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_RequestEscape" );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
				}
			}
		}
		// HK : Cheat Key¿Í °°Àº Çü½ÄÀ¸·Î ¸î¸î ½Ã½ºÅÛ ³»ºÎ ³»¿ëÀ» º¸¿©ÁÖ´Â ºÎºÐÀ» Ã³¸®ÇÑ´Ù.
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
		//	µ¿¿µ»ó Âï±â À§ÇØ
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
		//	°³¹ßÀÚ¸ðµå·Î ÀüÈ¯
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
		//	µ¿¿µ»ó Âï±â À§ÇØ_Ä¿¼­ º¸¿´´Ù ¾Èº¸ÀÌ°ÔÃ³¸®
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
		//	°³¹ßÀÚ¸ðµå·Î ÀüÈ¯
		else if(CHTString::HT_iStringCompare(token, szMsgDuel.HT_szGetString() )==0)
		{
			if( g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				g_pDuelSystem->HT_vDuel_SetDuelMode();
		}
		//	°ø¼ºÀü UI
		else if(CHTString::HT_iStringCompare(token, _T("/siege") )==0)
		{
			g_cCommand->HT_vCommand_Siege();
		}
		//	Ãâ¼®Ã¼Å©
		else if(CHTString::HT_iStringCompare(token, _T("/Attendance") )==0)
		{
			g_pEventWindow->HT_vEventWindow_ReqAttendance();
		}
		//	±Ó¼Ó¸» Ã¤ÆÃ_¸¶Áö¸·¿¡ ±Ó¼Ó¸» Ã¢¿¡ ¹º°¡ ÀÖÀ¸¸é ±Ó¼Ó¸»À» º¸³¿
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

	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_FocusOnEditBoxControl( iChatDlgNo, 2 );
	//	Set Language
	//g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );

	//	±âÁ¸ÀÇ ¹®ÀÚ¸¦ ³Ö¾îÁØ´Ù.
	//m_strChatMessage = g_cUIManager->HT_GetTextEditBoxControl( iChatDlgNo, 2 );
	//g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( m_strChatMessage.HT_szGetString() );
	//g_cImeMgr.InputString();
}
//	Set Focus Off
HTvoid CHTChatting::HT_vChatting_SetFocusOff( HTbool bTrue )
{
	//	Check Ã¤ÆÃ ÀÔ·Â ¸ðµå
	if( bTrue )
	{
		if( m_bChat_InputMode == HT_TRUE )
			return;
	}

	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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

	//	Ã¤ÆÃÃ¢ ÃÊ±âÈ­
	for( HTint i=0 ; i<iLineCount; i++)
		g_cUIManager->HT_SetTextLabelControl( iChatDlgNo, 10+i, _T("") );

	//	Ã¤ÆÃ ¸®½ºÆ® °Ë»ö
	HTint iChatCount = 0;
	HTbool bChatDisplay = HT_FALSE;
	for( i=m_iChat_ScrollChat ; i<_MAX_SAVED_MESSAGE_NUM; i++)
	{
		bChatDisplay = HT_FALSE;
		//	ÀüÃ¼ Âï±â¸é ¹«Á¶°Ç ¼ÂÆÃ
		if( m_bChat_ConfigChat[0] )
		{
            bChatDisplay = HT_TRUE;
		}
		else
		{
			//	ÆÄÆ¼
			if( m_bChat_ConfigChat[1] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_PARTY )
					bChatDisplay = HT_TRUE;
			}
			//	¾Æ½¬¶÷
			if( m_bChat_ConfigChat[2] )
			{
				if( m_oSavedChatMsg[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
					bChatDisplay = HT_TRUE;
			}
			//	¿¬ÇÕ
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
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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

// IME¸ðµå¸¦ ¾ò¾î¿Â´Ù
HTint
CHTChatting::HT_iGetIMEMode()
{
	return m_IMEStatus; 
}

//-------------------------------------------------------------------------------
// HTbool HT_vChatting_SetHistoryFunction( WPARAM wParam )
// D : È÷½ºÅä¸® ±â´É
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetHistoryFunction( WPARAM wParam )
{
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	switch( wParam )
	{
		case VK_PRIOR:
			{
				//	±Ó¼Ó¸» ÀÔ·ÂÃ¢ÀÏ¶§
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
				//	Ã¤ÆÃ ¸Þ½ÃÁö ÀÔ·ÂÃ¢ÀÏ¶§
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
					//	UI ½Ã½ºÅÛ¿¡ ±ÛÀÚ Ãâ·Â_¹Ì´ÏÃ¢°ú ÀüÃ¼Ã¢¿¡ ´Ù!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
		case VK_NEXT:
			{
				//	±Ó¼Ó¸» ÀÔ·ÂÃ¢ÀÏ¶§
				if( g_cUIManager->HT_isFocusOnEditBoxControl( iChatDlgNo, 1 ) )
				{
					if( m_strWhisperNameList[0].HT_bIsEmpty() )
						return;
					m_iChat_WhisperReadIndex++;
					if( m_iChat_WhisperReadIndex > 9 )	m_iChat_WhisperReadIndex = 0;
					if( m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_bIsEmpty() )	m_iChat_WhisperReadIndex = 0;
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWhisperNameList[m_iChat_WhisperReadIndex].HT_szGetString() );
				}
				//	Ã¤ÆÃ ¸Þ½ÃÁö ÀÔ·ÂÃ¢ÀÏ¶§
				else
				{
					m_iChat_HistroyReadIndex++;
					if( m_iChat_HistroyReadIndex > 9 )									m_iChat_HistroyReadIndex = 0;
					if( m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_bIsEmpty() )	m_iChat_HistroyReadIndex = 0;
					m_strChatMessage = m_strChat_HistoryMsg[m_iChat_HistroyReadIndex].HT_szGetString();

					//	UI ½Ã½ºÅÛ¿¡ ±ÛÀÚ Ãâ·Â_¹Ì´ÏÃ¢°ú ÀüÃ¼Ã¢¿¡ ´Ù!
					g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveChatMsg()
// D : ¸Þ¼¼Áö ÀúÀå
//-------------------------------------------------------------------------------
HTvoid 
CHTChatting::HT_vSaveChatMsg( HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground )
{
	this->HT_vArrangeSavedChatMsg( iType, sMsg, colorText );
	this->HT_vChatting_SetChatTextList();
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSaveHistory()
// D : ¸Þ¼¼Áö ÀúÀå
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
		// ´ç½ÅÀº Ã¤ÆÃ ±ÝÁö »óÅÂÀÔ´Ï´Ù.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	PS_CSP_REQ_CHAT info = HT_NULL;
	info = new S_CSP_REQ_CHAT;

	//	ÁÖ½Å ¼ÂÆÃ
	info->byTrimuriti	= g_oMainCharacterInfo.byTrimuriti;
	//	»óÁ¡¸ðµå
	if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
	{
		info->byBgColor		= 0;
		info->byTextColor	= 13;
	}
	//	Á¶±³¸ðµå
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
	//	±â³É ÀÏ¹Ý
	else
	{
		info->byBgColor		= 0;
		info->byTextColor	= 15;
	}

	// ¸Þ½ÃÁö°¡ ÃÖ´ë ±æÀÌ Á¦ÇÑÀ» ÃÊ°ú ÇÏ¿´´Â°¡?
	if(strlen(sChatMsg) > MAX_CHAT_LENGTH )
	{
		// ¸Þ½ÃÁö°¡ ³Ê¹« ±æ´Ù´Â ¸Þ½ÃÁö
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );

		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// Á¤»óÀûÀÎ °æ¿ì
	else
	{
		CHTString::HT_hrStringCopy(info->szMsg, sChatMsg, MAX_CHAT_LENGTH+1 );
	}

	//	¸Ó¸®±Û¿¡
	g_cMainCharacter->HT_vMainChar_NetWork_ChattingMessage( 0x01, info->szMsg );
	//	Ã¤ÆÃÃ¢¿¡
	CHTString strMsg;
	strMsg.HT_szFormat( "%s:", g_oMainCharacterInfo.szCharName );
	strMsg += info->szMsg;
	this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_NORMAL, strMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
	// ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
	g_pNetWorkMgr->RequestReqNormalChat( info );

	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Normal()
// D : ÀÏ¹Ý Ã¤ÆÃ ¸Þ½ÃÁö¸¦ ¼­¹ö·ÎºÎÅÍ ¼ö½ÅÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Normal( PS_SCP_NOTIFY_CHAT info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();
	CHTString strSenderName;
	strSenderName.HT_hrCleanUp();

	// º¸³½»ç¶÷ÀÇ Key ID°¡ ³Ñ¾î¿À¹Ç·Î ±×°ÍÀ» ¹ÙÅÁÀ¸·Î º¸³½»ç¶÷ÀÇ ID¸¦ ±¸ÇÔ
	if( info->nID < 10000 )
		strSenderName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->nID );
	else
		g_sNPCSystem->HT_vNPCSystem_GetName( (info->nID-10000), strSenderName );

	// º¸³½ »ç¶÷ ºÒ¸íÀÏ °æ¿ì ¸®ÅÏÇÑ´Ù.
	if(strSenderName.HT_bIsEmpty())return;
	// ´Ù¸¥»ç¶÷ÀÌ º¸³½ ¸Þ½ÃÁö
	if( SERVEROBJECT_IS_CHARACTER( info->nID  ) )
		strCompoundedMsg = strSenderName+_T(": ")+info->szMsg;
	else
		strCompoundedMsg = info->szMsg;

	//	ÁÖ½ÃÀü Áö¿ª¿¡¼­´Â ´Ù¸¥ ÁÖ½ÅÀÇ ¸Þ½ÃÁö´Â Æ¯¼ö¹®ÀÚ Ã³¸®ÇÑ´Ù.
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		//	ÁÖ½ÅÄÚµå º¸Á¤ÇØÁÖ±â
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

	// 0:Ã¤ÆÃÃ¢, 1:¸Ó¸®Ç³¼±, 2:Ã¤ÆÃÃ¢°ú ¸Ó¸®Ç³¼± ¸ðµÎ
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
//				±Ó¼Ó¸» Ã¤ÆÃ
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Whisper( CHTString token, CHTString sChatMsg )
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ´ç½ÅÀº Ã¤ÆÃ ±ÝÁö »óÅÂÀÔ´Ï´Ù.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	//	ºÐ¸®ÇØ ³»ÀÚ
	char chName[MAX_CHAT_LENGTH];
	strcpy (chName, "");
	//HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
	//strncpy( tokenMsg, sChatMsg, MAX_CHAT_LENGTH );

	//	token ¿¡ ¾Æ¹«°Íµµ ¾øÀ»‹š
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
    
	//	ÁÖ½Å ¼ÂÆÃ
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
			// ±Ó¼Ó¸» ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
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
		// ±Ó¼Ó¸» ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
		g_pNetWorkMgr->RequestReqWhisperChat(info);
	}

	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_WhisperChatting : %s-%s", info->szName, info->szMsg );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	if (!strcmp(info->szMsg,"/ÎÒÒª²Ö¿â"))  //fors_debug iwant
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
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "Á×Àº »óÅÂ¿¡¼­´Â »ç¿ëÇÒ ¼ö ¾ø½À´Ï´Ù." );

			}
	}
	if (!strcmp(info->szMsg,"/ÎÒÒªÊ×ÊÎ"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1302;
		 for (int i=10553 ; i<10569 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	if (!strcmp(info->szMsg,"/ÎÒÒª88Ìì¾§"))  //fors_debug iwant 
	 {
		 g_cNPCControl->m_iNPCIndex=1298;
		 for (int i=10536 ; i<10547 ; i++ )
		 {
			 g_cNPCControl->m_iTaskQuestID = i ;
		     g_cNPCControl->HT_vNetWork_CSP_Req_TaskQuest(g_cNPCControl->m_iTaskQuestID);
		 }

	}
	 if (!strcmp(info->szMsg,"/ÎÒÒª±äÉí"))
	 {
		 int ibodyid=0;
		 ibodyid	= g_pEngineHandler->HT_iCreateMonster( 2570, HTvector3( 100, 100, 100 ) );
		 			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
			g_pEngineHandler->HT_hrMoveObject(ibodyid, vecTempPos );

	 }

	// ¸Þ½ÃÁö¸¦ º¸³½ »ç¸²ÀÌ ÀÚ±â ÀÚ½ÅÀÌ¸é ÀÚ½Å¿¡°Ô º¸³¾ ¼ö ¾ø´Ù´Â ¸Þ½ÃÁö¸¦ Ãâ·ÂÇÑ´Ù.
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
		// ÀÌ¸§À» ÀÌ¸§ ¸®½ºÆ®¿¡ ÀúÀåÇÑ´Ù.
		this->HT_vAddName( 1,  chName );
		//	±×¸®°í ±Ó¼Ó¸» Ã¢¿¡ ÀÌ¸§À» ¼ÂÆÃÇÑ´Ù.
		m_strWisperName = chName;
	}

	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper()
// D : ±Ó¼Ó¸» ¸Þ½ÃÁö¸¦ ¼­¹ö·ÎºÎÅÍ ¼ö½ÅÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Whisper( PS_SCP_NOTIFY_WHISPER_CHAT info )
{
	CHTString strCompare;
	CHTString strCompoundedMsg, szMessage;
	strCompare.HT_hrCleanUp();
	strCompoundedMsg.HT_hrCleanUp();

	strCompare = g_oMainCharacterInfo.szCharName;

	//	¸¶Áö¸·À¸·Î ±Ó¼Ó¸» º¸³½ »ó´ë
	m_strLastRiciveWisperName = info->szName;
	
	// %sÀÇ ±Ó¸»
	m_szMsgName = info->szName;
	HT_vChatting_SetMessage( eMsgCommonChatWhisperReceive, &szMessage );

	// ¸ÞÀÎ Ä³¸¯ÅÍ(ÀÚ±â ÀÚ½Å)ÀÇ ÀÌ¸§°ú ±Ó¼Ó¸» ¸Þ½ÃÁö¿¡¼­ ¹ÞÀº ÀÌ¸§ÀÌ °°À¸¸é
	if( strCompare.HT_iStringCompare(info->szName)==0 )
	{
		// º¸³½ ±Ó¼Ó¸» ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
		// %sÀÇ ±Ó¸»: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		// ¸Þ½ÃÁö¸¦ µî·ÏÇÑ´Ù (Ã¢¿¡ ·»´õ¸µ µÈ´Ù.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[0]);
	}
	else
	{
		// ¹ÞÀº ±Ó¼Ó ¸» ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
		// %sÀÇ ±Ó¸»: %s
		strCompoundedMsg.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
		//	ÁÖ½ÃÀü Áö¿ª¿¡¼­´Â ´Ù¸¥ ÁÖ½ÅÀÇ ¸Þ½ÃÁö´Â Æ¯¼ö¹®ÀÚ Ã³¸®ÇÑ´Ù.
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

		// ¸Þ½ÃÁö¸¦ µî·ÏÇÑ´Ù (Ã¢¿¡ ·»´õ¸µ µÈ´Ù.)
		this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strCompoundedMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);

		// ÀÌ¸§À» ÀÌ¸§ ¸®½ºÆ®¿¡ ÀúÀåÇÑ´Ù.
		this->HT_vAddName( 2,  info->szName );
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_Whisper_Result()
// D : ±Ó¼Ó¸» ¸Þ½ÃÁöÀÇ Àü¼Û°á°ú¸¦ ¼­¹ö·ÎºÎÅÍ ¼ö½ÅÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveDataResult_Whisper( PS_SCP_RESP_WHISPER_CHAT info )
{
	CHTString strTemp, szMessage;

	switch(info->byResult)
	{
		case 0x00:
		{
			// º¸³½ ±Ó¼Ó¸» ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
			m_szMsgName = m_strWisperName;
			HT_vChatting_SetMessage( eMsgCommonChatWhisperSend, &szMessage ); // %s¿¡°Ô ±Ó¸»
			strTemp.HT_szFormat( "%s: %s", szMessage.HT_szGetString(), info->szMsg );
			// ¸Þ½ÃÁö¸¦ µî·ÏÇÑ´Ù (Ã¢¿¡ ·»´õ¸µ µÈ´Ù.)
			this->HT_vSaveChatMsg(CHAT_MESSAGE_TYPE_WISPER, strTemp, 
									g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor]);
		}
			break;
		case REPLY_WHISPER_CHAR_FAIL:
			HT_vChatting_SetMessage( eMsgCommonChatWhisperNotSend, &szMessage ); // %s¿¡°Ô ±Ó¸»
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, szMessage, g_ColorTable[6], g_ColorTable[0]);
			break;
		case REPLY_WHISPER_REJECT :
			this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, _T("ÁË¼ÛÇÕ´Ï´Ù. ÇöÀç ´Ù¸¥ ¾÷¹« ÁßÀ¸·Î ±Ó¸» »ó´ã¿¡ ÀÀÇÒ ¼ö ¾ø½À´Ï´Ù."), g_ColorTable[6], g_ColorTable[0]);
			break;
		default:;
	}
}

//-------------------------------------------------------------------------------
// Add by 20021130Tenma
// Description:
//					±×·ì Ã¤ÆÃ
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_Group(CHTString sChatMsg, HTbyte byMsgType)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ´ç½ÅÀº Ã¤ÆÃ ±ÝÁö »óÅÂÀÔ´Ï´Ù.
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

	//	ÆÄÆ¼
	if( info->byMsgType == MESSAGE_PARTY )
		info->byTextColor	= 7;
	//	±æµå
	else if( info->byMsgType == MESSAGE_GUILD )
		info->byTextColor	= 5;
	//	¾Æ½¬¶÷¿¬ÇÕ
	else if( info->byMsgType == MESSAGE_GUILD_ALLIANCE )
		info->byTextColor	= 6;

	// ¸Þ½ÃÁö°¡ ÃÖ´ë ±æÀÌ Á¦ÇÑÀ» ÃÊ°ú ÇÏ¿´´Â°¡?
	if( sChatMsg.HT_nGetSize() > MAX_GROUPCHAT_LENGTH )
	{
		// ¸Þ½ÃÁö°¡ ³Ê¹« ±æ´Ù´Â ¸Þ½ÃÁö
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgMessageisoutoflimit, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// Á¤»óÀûÀÎ °æ¿ì
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_GROUPCHAT_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
		g_pNetWorkMgr->RequestGroupChat( info );
	}

	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}


//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_NotifyMessage()
// D : °øÁö»çÇ× ¸Þ½ÃÁö¸¦ ¼­¹ö¿¡ Àü¼ÛÇÑ´Ù.
//  
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vSetData_NotifyMessage(CHTString sChatMsg)
{
	//	Chatting Block Check
	if( m_bChat_ChatBlockSw == HT_TRUE )
	{
		// ´ç½ÅÀº Ã¤ÆÃ ±ÝÁö »óÅÂÀÔ´Ï´Ù.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	MSG_Broadcast* info = HT_NULL;
	info = new MSG_Broadcast;

	info->byMsgType		= 1;
	info->byBgColor		= 0;			    // Ã¤ÆÃ ¸Þ¼¼Áö ¹è°æ»ö
	info->byTextColor	= 15;			    // Ã¤ÆÃ ¸Þ¼¼Áö ¹è°æ»ö
	info->byTrimuriti	= 0;

	// ¸Þ½ÃÁö°¡ ÃÖ´ë ±æÀÌ Á¦ÇÑÀ» ÃÊ°ú ÇÏ¿´´Â°¡?
	if( sChatMsg.HT_nGetSize() > MAX_NOTIFY_LENGTH )
	{
		// ¸Þ½ÃÁö°¡ ³Ê¹« ±æ´Ù´Â ¸Þ½ÃÁö
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_MESSAGEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
	}
	// Á¤»óÀûÀÎ °æ¿ì
	else
	{
		CHTString::HT_hrStringCopy( info->szMsg, sChatMsg, MAX_NOTIFY_LENGTH );
		CHTString::HT_hrStringCopy( info->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		// ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
		g_pNetWorkMgr->ReqNotifyMessage( info );
	}

	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_NOTIFY_MESSAGE" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_GlobalNotifyMessage()
// D : Àü¿ùµå¿¡ °øÁö»çÇ×À» ³¯¸°´Ù.
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

		// ÆÄÆ¼¸» ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
		// [ÆÄÆ¼]
		HT_vChatting_SetMessage( eMsgCommonSystemParty, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	ÁÖ½ÃÀü Áö¿ª¿¡¼­´Â ´Ù¸¥ ÁÖ½ÅÀÇ ¸Þ½ÃÁö´Â Æ¯¼ö¹®ÀÚ Ã³¸®ÇÑ´Ù.
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

		// ¾Æ½¬¶÷ ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
		// [¾Æ½¬¶÷]
		HT_vChatting_SetMessage( eMsgCommonSystemAshuram, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	ÁÖ½ÃÀü Áö¿ª¿¡¼­´Â ´Ù¸¥ ÁÖ½ÅÀÇ ¸Þ½ÃÁö´Â Æ¯¼ö¹®ÀÚ Ã³¸®ÇÑ´Ù.
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

		// ÆÄÆ¼¸» ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
		// [¾Æ½¬¶÷]
		HT_vChatting_SetMessage( eMsgCommonCommandAshuramJoinBrackets, &strCompoundedMsg );
		strCompoundedMsg = strCompoundedMsg+info->szName+_T(": ")+info->szMsg;
		//	ÁÖ½ÃÀü Áö¿ª¿¡¼­´Â ´Ù¸¥ ÁÖ½ÅÀÇ ¸Þ½ÃÁö´Â Æ¯¼ö¹®ÀÚ Ã³¸®ÇÑ´Ù.
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
// D : °øÁö»çÇ× ¸Þ½ÃÁö¸¦ ¼­¹ö·ÎºÎÅÍ ¼ö½ÅÇÑ´Ù.
//     S_SCP_NOTIFY_MESSAGE.szNameÀº °øÁö»çÇ×¿¡¼­ »ç¿ëÇÏÁö ¾ÊÀ¸¹Ç·Î ÈÄ¿¡ »èÁ¦ÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_Notify( MSG_Broadcast* info )
{
	//	¹öÆÛNPCÆË¸Þ½ÃÁö(7) ÀüÅõ¸í·É¼­(4), È£¿Ü(5)ÀÏ¶§
	if( info->byMsgType == 7 || info->byMsgType == 4 || info->byMsgType == 5 )
	{
		//	°°Àº ÁÖ½ÅÀÌ ¾Æ´Ï¸é ½ºÅµ
		if( info->byMsgType == 4 )
		{
			if( g_oMainCharacterInfo.byTrimuriti != info->byTrimuriti )
				return;
		}
		//	µð½ºÇÃ·¹ÀÌ ÁßÀÌ ¾Æ´Ò¶§
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
		//	µð½ºÇÃ·¹ÀÌ Áß ÀÏ´ë
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
		//	°øÁö ¸Þ½ÃÁö¸¦ ¹ÞÀ¸¸é »ç¿îµå¸¦ Æ²¾îÁØ´Ù.
		//	ÁÖ½Å¼±ÅÃ ¸Þ½ÃÁö°¡ ¾Æ´Ò¶§
		if( info->byBgColor != 14 )
			g_pEngineHandler->HT_hrPlaySound( 33509, 3 );

		//	°øÁö
		CHTString szNotice, szMsgWholeNotice;
		HT_vChatting_SetMessage( eMsgCommonCommandNotice		, &szNotice );
		HT_vChatting_SetMessage( eMsgCommonCommandWholeNotice	, &szMsgWholeNotice );	// /ÀüÃ¼°øÁö
		
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
			//	°øÁöÃ¢ ÄÔ
			g_pNotifyWindow->HT_vNotify_SetOn();
			g_pNotifyWindow->HT_vNotify_SetText( info->szMsg );

			if( info->byMsgType != MESSAGE_SERVERMSG )
			{
				szNotice += info->szMsg;

				int Length = sizeof(info->szMsg);
				char szNotipy[1024];

				szNotice += info->szMsg;
				if( szNotice.HT_nGetSize() < 256 )			//	»çÀÌÁî°¡ Àû´çÇÒ¶§¸¸ ½Ã½ºÅÛÃ¢¿¡ °øÁö
				{
					//	[°øÁö]
					CHTString strTemp;
					HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
					for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
					{
						//	½Ã½ºÅÛÃ¢¿¡ °øÁö
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
		//	"/°øÁö"
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
			if( szNotice.HT_nGetSize() < 256 )			//	»çÀÌÁî°¡ Àû´çÇÒ¶§¸¸ ½Ã½ºÅÛÃ¢¿¡ °øÁö
			{
				//	[°øÁö]
				CHTString strTemp;
				HT_g_Script_SetMessage( eMsgCommonChatNotice, &strTemp, _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );

				for (int Orj = 0, Dsc = 0; Orj < Length; ++Orj)
				{
					//	½Ã½ºÅÛÃ¢¿¡ °øÁö
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
			//	ÁÖ½Å¼±ÅÃ ¸Þ½ÃÁöÀÏ¶§
			if( info->byBgColor == 14 )
			{
				//	½Ã½ºÅÛ Ã¢À¸·Î º¸³¿
				this->HT_vSaveHistory(HISTORY_MESSAGE_TYPE_NOTIFY, info->szMsg, g_ColorTable[info->byTextColor], g_ColorTable[info->byBgColor] );
			}
		}
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vReceiveData_History()
// D : È÷½ºÅä¸® ¸Þ½ÃÁö¸¦ ¼­¹ö·ÎºÎÅÍ ¼ö½ÅÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vReceiveData_History( PS_SCP_RESP_CHAR_HISTORY info )
{
	CHTString strCompoundedMsg;
	strCompoundedMsg.HT_hrCleanUp();

	// ½Ã°£ Ãß°¡ Ç¥½ÃÇÒ °Í.
	// °øÁö»çÇ× ¸Þ½ÃÁöÀÓÀ» Ç¥½Ã
	//strCompoundedMsg = _T("[È÷½ºÅä¸®Å×½ºÆ®] ");
	HT_vChatting_SetMessage( eMsgCommonSystemHistory, &strCompoundedMsg );
	strCompoundedMsg = strCompoundedMsg+info->szContent;
	this->HT_vSaveHistory(info->wType, strCompoundedMsg, g_ColorTable[4], g_ColorTable[4]);

	HT_Trace(strCompoundedMsg);
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSetData_ReqCharInfo( CHTString strCharname )
// D: GMÀÌ ´Ù¸¥Ä³¸¯ÅÍÀÇ Á¤º¸¸¦ ¿äÃ»ÇÑ´Ù.
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
// D: GMÀÌ ´Ù¸¥Ä³¸¯ÅÍÀÇ °­Á¦ ÅðÀå ½ÃÅ²´Ù.
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
// D: ÆÄÀÏ·Î ºÎÅÍ °øÁö»çÇ×À» ¼­¹ö¿¡ ¼øÂ÷ÀûÀ¸·Î Àü´ÞÇÑ´Ù.
// ¼­¹ö¿¡¼­´Â Àü´Þ ¹ÞÀº´ë·Î Å¬¶óÀÌ¾îÆ®¿¡ º¸³Â´Ù°¡ ¸Þ½ÃÁö¸¦ ´Ù ¹ÞÀ¸¸é ÇÑ²¨¹ø¿¡ Ç¥½Ã ÇØ ÁØ´Ù.
//-------------------------------------------------------------------------------
HTRESULT
CHTChatting::NotifyFromFile( CHTString strFilename )
{
	FILE		*fp;
	HTtchar		in;			// ÀÐ¾î ¿Â ¹ÙÀÌÆ®
	HTint		iCount = 1;	// MAX_CHAT_LENGTH ¸¸Å­ ±ÛÀÚ¸¦ Ä«¿îÆ®ÇÔ
	HTtchar		inBytes[ MAX_CHAT_LENGTH+1 ];	// ÀÐ¾î ¿Â ¹ÙÀÌÆ®¸¦ MAX_CHAT_LENGTH¹ÙÀÌÆ®±îÁö ÀúÀå
	CHTString	strTemp;

	fp = fopen((HTtchar *)strFilename, "rt");
	// ÆÄÀÏÀ» ¿­°í, ¿­¼ö ¾ø¾úÀ¸¸é ¿¡·¯¸¦ Ç¥½ÃÇÑ´Ù.
	if( fp == NULL )
		return HT_FAIL;

	this->HT_vSetData_NotifyMessage( CHTString( "//START NOTIFY MESSAGE//" ) );
	
	//	¸Þ½ÃÁö ¹öÆÛ¸¦ ÃÊ±âÈ­ÇÏ°í
	ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );

	while( (in = fgetc(fp)) != EOF )
	{
		inBytes[ iCount-1 ] = in;

		// MAX_CHAT_LENGTH ±ÛÀÚ±îÁö ÀÔ·Â ¹ÞÀº ÈÄ ³ÎÀ» ºÙÀÌ°í ¸Þ½ÃÁö¸¦ Àü´ÞÇÑ´Ù.
		if( iCount >= MAX_CHAT_LENGTH )
		{	
			// ¸¶Áö¸·ÀÌ ÇÑ±Û ¹ÙÀÌÆ®°¡ ¾Æ´Ñ °æ¿ì´Â ÀüÃ¼¸¦ Ä«ÇÇÇÏ¿© º¸³½´Ù
			if( in >= '!' && in <= '~' ) 
			{
				inBytes[ iCount ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	¸Þ½ÃÁö ¹öÆÛ¸¦ ÃÊ±âÈ­ÇÏ°í
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				
				// Ä«¿îÆ®¸¦ ÃÊ±âÈ­
				iCount = 1;
				
			}
			// ¸¶Áö¸·ÀÌ ÇÑ±Û ¹ÙÀÌÆ®ÀÎ °æ¿ì¿¡´Â ±× ¹ÙÀÌÆ®¸¦ ´ÙÀ½¹ø Ã¹¹øÂ°¿¡ ÀúÀåÇÏ°í ±× ¹ÙÀÌÆ®¸¦ Á¦¿ÜÇÏ°í º¸³½´Ù
			// ºüÁø ÇÑ±Û ¹ÙÀÌÆ®´Â ´ÙÀ½¹ø¿¡ °°ÀÌ °£´Ù.
			else
			{
				inBytes[ iCount-1 ] = '\0';
				CHTString::HT_hrStringCopy(strTemp ,inBytes , HT_MAX_STR);
				//	¸Þ½ÃÁö ¹öÆÛ¸¦ ÃÊ±âÈ­ÇÏ°í
				ZeroMemory( inBytes, MAX_CHAT_LENGTH+1 );
				//strTemp.HT_szFormat("%s", inBytes);
				this->HT_vSetData_NotifyMessage( strTemp );
				// ¹è¿­ÀÇ Ã³À½¿¡ ÇÑ±Û ¾Õ¹ÙÀÌÆ®¸¦ ³Ö¾î³õ°í Ä«¿îÆ®¸¦ ÃÊ±âÈ­
				inBytes[0] = in;
				iCount = 2;
			}
		}
		// MAX_CHAT_LENGTH ±ÛÀÚ°¡ Â÷Áö ¾Ê¾ÒÀ¸¸é Ä«¿îÆ® ÇÑ´Ù.
		else
			iCount ++;
	}

	//	ÆÄÀÏÀ» ´Ý°í
	fclose( fp );

	// ³²Àº ¹ÙÀÌÆ®µéµµ º¸³¿
	inBytes[ iCount ] = '\0';
	strTemp.HT_szFormat("%s", inBytes);
	this->HT_vSetData_NotifyMessage( strTemp );
	this->HT_vSetData_NotifyMessage( CHTString( "//END NOTIFY MESSAGE//" ) );

	return HT_OK;
}



//-------------------------------------------------------------------------------
// HTvoid StartStopLogging( CHTString strFilename )
// D: Ã¤ÆÃ·Î±× ÆÄÀÏÀÇ »ý¼ºÀ» ½ÃÀÛ/ ÁßÁöÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::StartStopLogging()
{
	CHTString strTemp;

	// Ã¤ÆÃ ·Î±× »óÅÂ¸¦ ¹Ù²Û´Ù. ÀúÀå ÁßÀÌ¿´´Ù¸é ±×¸¸µÐ´Ù
	if(m_bLogging)
	{
		HTint iRCode;
		
		// ÆÄÀÏÀÌ ¿­·Á ÀÖ´Ù¸é ´ÝÀ½.
		if(m_pLogFile != NULL)
		{

			struct tm *today;
			char charTimeBuffer[MAX_TIMESTAMP_SIZE];
			time_t tTimeDifference;
			time_t tCurrentTime;

			// ÇöÀç ½Ã°£À» ±¸ÇÑ´Ù.
			time( &tCurrentTime );
			// ÇöÀç ½Ã°£°ú Initialize TimeÀ» ÇÑ ½Ã°£°ú Â÷ÀÌ¸¦ ±¸ÇÏ¿© ÇöÀç ¼­¹ö ½Ã°£À» ±¸ÇÑ´Ù.
			tTimeDifference = g_tInitServerTime + ( g_tInitClientTime - tCurrentTime );

			// ±¸ÇÑ ÇöÀç ¼­¹ö½Ã°£À» °¡Áö°í tm ±¸Á¶Ã¼¸¦ »ý¼ºÇÑ´Ù.
			today = localtime( &tTimeDifference );
			strftime( charTimeBuffer, MAX_TIMESTAMP_SIZE, "[%Y/%m/%d %H:%M:%S]", today );

			// ´ëÈ­ ³»¿ë ÀúÀåÀ» ÁßÁöÇÔÀ» ÆÄÀÏ¿¡ Ç¥½Ã
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
			fprintf( m_pLogFile, "%s %s\n",charTimeBuffer, strTemp.HT_szGetString() );
			fflush( m_pLogFile );

			// ´Ý´Â ¸¶Ä¿¸¦ ÆÄÀÏ¿¡ Ç¥½Ã, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n\n");
			fflush( m_pLogFile );

			iRCode = fclose( m_pLogFile );
		}
		if(iRCode == 0)
		{
			m_pLogFile = NULL;
			m_bLogging = HT_FALSE;
			//strTemp = "´ëÈ­ ³»¿ëÀ» ÀúÀåÀ» Á¾·áÇÕ´Ï´Ù.";
			HT_vChatting_SetMessage( eMsgChatSaveEnd, &strTemp );
		}
		else //strTemp = "·Î±× ÆÄÀÏÀ» ´Ý´Âµ¥ ½ÇÆÐ ÇÏ¿´½À´Ï´Ù. ´ëÈ­ ³»¿ëÀ» °è¼Ó ÀúÀåÇÕ´Ï´Ù.";			
			HT_vChatting_SetMessage( eMsgChatLogFileCloseErr, &strTemp );
	}
	// ÀúÀå ÁßÀÌ ¾Æ´Ï¶ó¸é ÀúÀåÀ» ½ÃÀÛÇÑ´Ù.
	else
	{
		// ÆÄÀÏÀÌ ´ÝÇô ÀÖ´Ù¸é ¿¬´Ù.
		if( m_pLogFile == NULL )
		{
			m_pLogFile = fopen( "chat_log.txt", "at+" );
			// ÆÄÀÏÀÌ ¾ø´Â°æ¿ì (À­ ÇÔ¼ö¿¡¼­ NULL ÀÌ ¸®ÅÏµÈ´Ù)
			if( m_pLogFile == NULL ) m_pLogFile = fopen( "chat_log.txt", "w" );
		}
		// ¼º°øÀûÀ¸·Î ÆÄÀÏÀ» ¿­¾ú´Ù.
		if( m_pLogFile )
		{
			// ¿©´Â ¸¶Ä¿¸¦ ÆÄÀÏ¿¡ Ç¥½Ã, flush
			fprintf( m_pLogFile, "---------------------------------------------------------------\n");
			fflush( m_pLogFile );
			//strTemp = "´ëÈ­ ³»¿ëÀ» ÆÄÀÏ·Î ÀúÀåÇÕ´Ï´Ù.";
			HT_vChatting_SetMessage( eMsgChatSaveStart, &strTemp );
			m_bLogging = HT_TRUE;
		}
		// ÆÄÀÏÀ» ¿©´Âµ¥ ½ÇÆÐ ÇÏ¿´´Ù.
		else //strTemp = "·Î±× ÆÄÀÏÀ» ¿©´Âµ¥ ½ÇÆÐÇÏ¿´½À´Ï´Ù. ´ëÈ­ ³»¿ë ÀúÀåÀ» ½ÃÀÛ ÇÒ ¼ö ¾ø¾ú½À´Ï´Ù.";
			HT_vChatting_SetMessage( eMsgChatLogFileOpenErr, &strTemp );
	}
	this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
}


//-------------------------------------------------------------------------------
// HTvoid addName( HTint type, CHTString strName )
// D: Ã¤ÆÃ ´ë»ó ÀÌ¸§ ¸®½ºÆ®¿¡ ÀÌ¸§À» µî·ÏÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vAddName( HTint type, CHTString strName )
{
	//	°°Àº ÀÌ¸§ ªO±â
	for( HTint i= 0 ;i<m_iNameListNum ; i++ )
	{
		if( strName.HT_iStringCompare( m_strWhisperNameList[i] ) == 0 )
			return;
	}

	//	ÇöÀç 9°³°¡ ³ÑÀ¸¸é
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
// D: ¼­¹ö¿¡ Ä³¸¯ÅÍ À§Ä¡ Á¤º¸¸¦ ¿äÃ»ÇÔ
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
	// ¸Þ½ÃÁö°¡ ÃÖ´ë Á¦ÇÑ ±æÀÌº¸´Ù ±ä °æ¿ì
	else if(strlen(pcharName) > SZNAME_LENGTH){
		CHTString strTemp;
		LoadString(g_hInstance, IDS_CHATTING_MSG_TOO_LONG_NAMEVALUE, strTemp, HT_MAX_STR);
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_ERROR, strTemp, g_ColorTable[12], g_ColorTable[0]);
		return;
	}
	// Á¤»óÀûÀÎ °æ¿ì
	else
	{
		S_GCSP_REQ_CHARACTER_SEARCH* info = HT_NULL;
		info = new S_GCSP_REQ_CHARACTER_SEARCH;
		// Á¤º¸¸¦ º¹»ç, Á¶ÇÕÇÑ´Ù.
		CHTString::HT_hrStringCopy(info->szCharName, pcharName, SZNAME_LENGTH+1);
		// ¼­¹ö¿¡ Ä³¸¯ÅÍ À§Ä¡ Á¤º¸¸¦ ¿äÃ»ÇÔ
		g_pNetWorkMgr->RequestReqCharLocation( info );
		//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send__CHARACTER_SEARCH: %s", info->szCharName );
		//if(	g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		HT_DELETE( info );
	}
}


//-------------------------------------------------------------------------------
// HTvoid HT_vChatting_SetWisper( CHTString )
// D : ¿ÜºÎ¿¡¼­ ±Ó¼Ó¸» »óÅÂ¸¦ ¼³Á¤ÇÑ´Ù.
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetWisper( CHTString strWisperName )
{
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	// ÇöÀç ³ëµåÀÇ ÀÌ¸§À» ±Ó¼Ó¸» ´ë»óÀÌ¸§À¸·Î ¼³Á¤ÇÑ´Ù.
	m_strWisperName			= strWisperName;
    // Edit No 1
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 1, m_strWisperName.HT_szGetString() );
	m_strChatMessage.HT_hrCleanUp();
}


//-------------------------------------------------------------------------------
// ...
// D : ±Ó¼Ó¸» ´ëÈ­»ó´ë ÀúÀåÇÏ´Â ´ëÈ­»óÀÚ ÄÁÆ®·Ñ
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_Whisper_Dlg_Check()
{
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_WHISPERLISTWND ) )
	{
		m_bNameListActive = HT_TRUE;

		//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
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
// D : ÀúÀåµÈ ¸Þ¼¼Áö¿Í È÷½ºÅä¸® Á¤·Ä
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
		//	±ÛÀÚ¸¦ ´ëÀÔ
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ¸¶Áö¸· ¹ÙÀÌÆ®°¡ ±ÛÀÚÀÇ ½ÃÀÛÀÌ ¾Æ´Ñ°æ¿ì¿¡´Â
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
			//	´Ü¾î´ÜÀ§ÀÇ °³ÇàÀÌ ÇÊ¿äÇÒ °æ¿ì, °ø¹é ¹®ÀÚ¸¦ ÆÄ¾ÇÇÏ¿© °ø¹é ¹®ÀÚ±îÁö ´Ù½Ã µÇµ¹¸°´Ù.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	ÇÊ¸®ÇÉ
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	ÀÎµµ³×½Ã¾Æ
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

			//	Ã¹¹øÂ° ¹®Àå
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
		//	±ÛÀÚ¸¦ ´ëÀÔ
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ¸¶Áö¸· ¹ÙÀÌÆ®°¡ ±ÛÀÚÀÇ ½ÃÀÛÀÌ ¾Æ´Ñ°æ¿ì¿¡´Â
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
			//	´Ü¾î´ÜÀ§ÀÇ °³ÇàÀÌ ÇÊ¿äÇÒ °æ¿ì, °ø¹é ¹®ÀÚ¸¦ ÆÄ¾ÇÇÏ¿© °ø¹é ¹®ÀÚ±îÁö ´Ù½Ã µÇµ¹¸°´Ù.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	ÇÊ¸®ÇÉ
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	ÀÎµµ³×½Ã¾Æ
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

			//	Ã¹¹øÂ° ¹®Àå
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
// D : ¸¶Áö¸·À¸·Î ±Ó¼Ó¸» º¸³½ »ó´ë
//-------------------------------------------------------------------------------
HTvoid CHTChatting::HT_vChatting_SetLastSendWisper()
{
	//	Ã¤ÆÃ À©µµ¿ì ½ºÅ¸ÀÏ
	HTint iChatDlgNo;
	if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_NORMAL )				iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_TRANSPARANCY )		iChatDlgNo = _DIALOG_CHATTINGBOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_MIDDLESIZE )		iChatDlgNo = _DIALOG_CHATTING2BOX;
	else if( g_cChatting->m_iChatWindowStyle == CHATWNDSTYLE_BIGSIZE )			iChatDlgNo = _DIALOG_CHATTING3BOX;

	CHTString szCommand;
	HT_vChatting_SetMessage( eMsgCommonCommandWhisper, &szCommand ); // /±Ó¼Ó¸»

	m_strChatMessage = szCommand;
	m_strChatMessage += _T(" ");
	m_strChatMessage += m_strLastRiciveWisperName.HT_szGetString();
	m_strChatMessage += _T(" ");

	//	Edit Box 2
	g_cUIManager->HT_ShowWindow( iChatDlgNo );
	g_cUIManager->HT_SetTextEditBoxControl( iChatDlgNo, 2, m_strChatMessage.HT_szGetString() );
	g_cImeMgr.vImeMgr_SetLimitRecivewParam( 1 );

	//	Ã¤ÆÃ ÀÔ·Â È°¼ºÈ­
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
	
	// º¯¼ö°¡ 3°³ ÀÏ ¶§
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
	// º¯¼ö°¡ 2°³ ÀÏ ¶§
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vChatting_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vChatting_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// º¯¼ö°¡ 1°³ ÀÏ ¶§
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
		// Áö¿ª
		case eMsgParamZoneNum	:	
			pszParam->HT_szFormat( "%d", m_iMessageVal ); break;
		// ´Ù¸¥ Ä³¸¯ÅÍ ÀÌ¸§
		case eMsgParamOthercharName :
			*pszParam = m_szMsgName;
			break;

		default:
			break;
	}
}

//-------------------------------------------------------------------------------
// Àü±¤ÆÇ
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetOpenMessageItem( HTbyte byMsgType, HTint iItemIndex, HTbyte byItemKeyID )
{
	//	°³ÀÎ¼ºÁ¡ÀÌ ¿­·ÁÀÖÀ¸¸é Àü±¤ÆÇ »ç¿ë ¸øÇÏ°Ô ÇÑ´Ù.
	if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
		return;

	//	Open Msg Type
	//	0:¾øÀ½, 1:¾Æ½¬¶÷ÀÌ¸§, 2:Àü±¤ÆÇ, 3:ÀüÅõ¸í·É¼­
	m_byChat_OpenMsgType = byMsgType;
	CHTString strTemp;
	if( m_byChat_OpenMsgType == 1 )
	{
		//	¾Æ½¬¶÷ ÀÌ¸§À» ÀÔ·ÂÇØ ÁÖ½Ê½Ã¿À
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputAshramName, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 2 )
	{
		//	Àü±¤ÆÇ ³»¿ëÀ» ÀÔ·ÂÇØ ÁÖ½Ê½Ã¿À
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputOpenMessage, &strTemp, _T(""), _T("") );
	}
	else if( m_byChat_OpenMsgType == 3 )
	{
		//	ÀüÅõ¸í·É¼­ ³»¿ëÀ» ÀÔ·ÂÇØ ÁÖ½Ê½Ã¿À
		g_cUIManager->HT_SetScriptMessage( eMsgCommonPleaseInputCombatMessage, &strTemp, _T(""), _T("") );
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_OPENMESSAGE, 1, strTemp.HT_szGetString() );

	//	Àü±¤ÆÇ ¾ÆÀÌÅÛ
	m_iOpenMessageItemIndex = iItemIndex;
	//	Àü±¤ÆÇ ¾ÆÀÌÅÛ Á¾·ù
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
		// ´ç½ÅÀº Ã¤ÆÃ ±ÝÁö »óÅÂÀÔ´Ï´Ù.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNoChatMode, &strTemp, _T("") );
		this->HT_vSaveHistory(CHAT_MESSAGE_TYPE_NORMAL, strTemp.HT_szGetString(), g_ColorTable[12], g_ColorTable[0]);
		return;
	}

	CHTString sChatMsg;
	sChatMsg = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_OPENMESSAGE, 2 );

	//	±æµå ÀÌ¸§ÀÇ °æ¿ì
	if( m_byChat_OpenMsgType == 1 )
	{
		//	±æµå »ý¼ºÀ» ¿äÃ»ÇÑ´Ù.
		if(HT_SUCCEED(g_cGuildSystem->HT_hrNetWork_CSP_REQ_CREATE_GUILD( sChatMsg )))
		{
			this->HT_vChatting_DelOpenMessageItemBox();
		}
	}
	//	Àü±¤ÆÇ°ú ÀüÅõ¸í·É¼­ÀÏ°æ¿ì
	else if( m_byChat_OpenMsgType == 2 || m_byChat_OpenMsgType == 3 )
	{
		// ¸Þ½ÃÁö°¡ ÃÖ´ë ±æÀÌ Á¦ÇÑÀ» ÃÊ°ú ÇÏ¿´´Â°¡?
		if( sChatMsg.HT_nGetSize() > 80 )
		{
			// ¸Þ½ÃÁö°¡ ³Ê¹« ±æ´Ù´Â ¸Þ½ÃÁö
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
			// ¸Þ½ÃÁö Àü¼ÛÀ» ¼­¹ö¿¡ ¿äÃ»ÇÔ
			g_pNetWorkMgr->ReqNotifyMessage( info );

			//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
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

//-Àü±¤ÆÇ ¾ÆÀÌÅÛÀ» »ç¿ëÇÏ¿© Ã¢À» ¿­¸é ±×µ¿¾È Å°º¸µå·Î ÀÔ·ÂÇÑ ¸í·ÉµéÀÌ ³ª¿È
//-Àü±¤ÆÇ ¾ÆÀÌÅÛÀ» »ç¿ëÇÏ¿© Ã¢¿¡ ¸Þ½ÃÁö¸¦ ÀÔ·ÂÇÑ µÚ ¿£ÅÍÅ°¸¦ ´©¸£¸é ¸Þ½ÃÁö°¡ »èÁ¦
//-Àü±¤ÆÇ ¾ÆÀÌÅÛÀ» »ç¿ëÇÏ¿© Ã¢¿¡ ¿µ¹® ÀÔ·Â½Ã ´ÜÃàÅ°·Î ÀÎ½Ä, ½ÇÇà µÊ

//-------------------------------------------------------------------------------
//	Ã¤ÆÃ ºí·°
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
//	Ã¤ÆÃ ·Î±×
//-------------------------------------------------------------------------------
HTvoid
CHTChatting::HT_vChatting_SetChatLog( HTint iType, CHTString strMsg, HT_COLOR clColor )
{
	//	µÚ·Î ÇÑÄ­¾¿ ¶¯±ä´Ù.
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
		//	±ÛÀÚ¸¦ ´ëÀÔ
		szTemp[iTempCount1] = szMsg[iTempCount2];
		// ¸¶Áö¸· ¹ÙÀÌÆ®°¡ ±ÛÀÚÀÇ ½ÃÀÛÀÌ ¾Æ´Ñ°æ¿ì¿¡´Â
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
			//	´Ü¾î´ÜÀ§ÀÇ °³ÇàÀÌ ÇÊ¿äÇÒ °æ¿ì, °ø¹é ¹®ÀÚ¸¦ ÆÄ¾ÇÇÏ¿© °ø¹é ¹®ÀÚ±îÁö ´Ù½Ã µÇµ¹¸°´Ù.
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||		//	ÇÊ¸®ÇÉ
				g_iInationalType == INATIONALTYPE_INDONESIA )		//	ÀÎµµ³×½Ã¾Æ
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

			//	µÚ·Î ÇÑÄ­¾¿ ¶¯±ä´Ù.
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
		//	ÀÌ¹Ì ¹®ÀåÀÇ Àý¹Ý ÀÌ»óÀÌ À§ÀÇÄ­¿¡ »ðÀÔµÆÀ»¶§
		if( bChangeMsg == HT_TRUE )
		{
			ZeroMemory( szMsg, 512 );
			strncpy( szMsg, m_oChat_SaveOpenMsg[0].szMsg, strlen(m_oChat_SaveOpenMsg[0].szMsg) );
			ZeroMemory( &m_oChat_SaveOpenMsg[0], 128 );
			strncpy( m_oChat_SaveOpenMsg[0].szMsg, szTemp, strlen(szTemp) );
			strncpy( szTemp, szMsg, strlen(szMsg) );
		}

		//	µÚ·Î ÇÑÄ­¾¿ ¶¯±ä´Ù.
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
	//void HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// ½ºÅ©·Ñ¹Ù ÄÁÆ®·Ñ¿¡ ÃÖ´ë °ªÀ» º¯°æ ÇÕ´Ï´Ù.

	//	Ã¤ÆÃ·Î±×Ã¢ ÃÊ±âÈ­
	for( HTint i=0 ; i<_CHAT_CHAT_LOG_NUM ; i++ )
	{
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG1, CAHT_CHATLOGLABELSATRT+i, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHATLOG2, CAHT_CHATLOGLABELSATRT+i, _T("") );
	}

	//	ÀÏ¹Ý¸Þ½ÃÁö
	HTint iScrolBar;
	HTint iChatCount = 0;
	HTbool bChatDisplay;
	if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATLOG1 ) )
	{
		iScrolBar = g_cUIManager->HT_GetScrollBarValue( _DIALOG_CHATLOG1, 1 );
		
		for( i=iScrolBar ; i<CHATLOG_MAX_COUNT ; i++)
		{
			bChatDisplay = HT_FALSE;
			//	ÀüÃ¼ Âï±â¸é ¹«Á¶°Ç ¼ÂÆÃ
			if( m_bChat_ChatLogConfig[0] )
			{
				bChatDisplay = HT_TRUE;
			}
			else
			{
				//	ÆÄÆ¼
				if( m_bChat_ChatLogConfig[1] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_PARTY )
						bChatDisplay = HT_TRUE;
				}
				//	¾Æ½¬¶÷
				if( m_bChat_ChatLogConfig[2] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ASHRAM )
						bChatDisplay = HT_TRUE;
				}
				//	¿¬ÇÕ
				if( m_bChat_ChatLogConfig[3] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_ALLIANCE )
						bChatDisplay = HT_TRUE;
				}
				//	±Ó¼Ó¸»
				if( m_bChat_ChatLogConfig[4] )
				{
					if( m_oChat_ChatLog[i].iType == CHAT_MESSAGE_TYPE_WISPER )
						bChatDisplay = HT_TRUE;
				}
				//	±Ó¼Ó¸»
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
	//	Àü±¤ÆÇ ¸Þ½ÃÁö
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


//	ÀÛ¾÷Áß ¸Þ½ÃÁö
HTvoid
CHTChatting::HT_vChatting_WorkingMsg()
{
	return;

	CHTString strTemp;
	strTemp.HT_hrCleanUp();
	////	ÀÛ¾÷Áß ¸Þ½ÃÁö Ä«¿îÆ®
	//switch( m_iChat_MsgCount )
	//{
	//	case 0 :	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù.");	break;
	//	case 1 :	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù..");	break;
	//	case 2 :	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù...");	break;
	//	case 3 :	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù....");	break;
	//	case 4 :	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù.....");	break;
	//	case 5 :	strTemp = _T("(Àç±¸¼ºÁß) -.-");	break;
	//	case 6 :	strTemp = _T("(Àç±¸¼ºÁß) -.-;;");	break;
	//	case 7 :	strTemp = _T("(Àç±¸¼ºÁß) -.-;;;");	break;
	//	case 8 :	strTemp = _T("(Àç±¸¼ºÁß) ^^; /('')/ l(``)l ^^");	break;
	//	case 9 :	strTemp = _T("(Àç±¸¼ºÁß) Á» ´õ Æí¸®ÇÑ ±â´ÉÀ¸·Î ¿Ï¼ºÇÏ±â À§ÇÑ ÀÛ¾÷ÀÌ ÁøÇàÁßÀÔ´Ï´Ù.");	break;
	//	case 10 :	strTemp = _T("(Àç±¸¼ºÁß) Èì.. ¿­½ÉÈ÷ ÀÛ¾÷ÁßÀÔ´Ï´Ù. Á¶±Ý¸¸ ´õ ±â´Ù·Á ÁÖ¼¼¿ä... ^^");	break;
	//	case 11 :	strTemp = _T("(Àç±¸¼ºÁß) Èì.. ºÒÃ¶ÁÖ¾ß ÀÛ¾÷ÁßÀÔ´Ï´Ù. Á¶±Ý¸¸ ´õ ±â´Ù·Á ÁÖ¼¼¿ä... ^^");	break;
	//	case 12 :	strTemp = _T("(Àç±¸¼ºÁß) T.T ÈæÈæ.. Á¶±Ý¸¸ ´õ ±â´Ù·ÁÁÖ¼¼¿ä...");	break;
	//	case 13 :	strTemp = _T("(Àç±¸¼ºÁß) T.T ÈæÈæ.. Áý¿¡¸¦ ¸øµé¾î°¡¿©...");	break;
	//	case 14 :	strTemp = _T("(Àç±¸¼ºÁß) T.T ÈæÈæ.. Áý¿¡ °¡°í ½Í¾î¿©... ^^");	break;
	//	case 15 :	strTemp = _T("(Àç±¸¼ºÁß) T.T ÈæÈæ.. ¼úµµ ¸¶½Ã°í ½Í¾î¿©... ^^");	break;
	//	case 16 :	strTemp = _T("(Àç±¸¼ºÁß) ±×·¡µµ ¸ñÀÌ ºüÁ®¶ó ±â´Ù¸®´Â À¯Àú´ÔµéÀ» À§ÇØ ¿À´Ã¹ãµµ ºÒÅÂ¿î´ä´Ï´Ù.");	break;
	//	case 17 :	strTemp = _T("(Àç±¸¼ºÁß) ºÒ ³¯°Í °°¾Æ¿©... WWWW");	break;
	//	case 18 :	strTemp = _T("(Àç±¸¼ºÁß) ...!!!");	break;
	//	case 19 :	strTemp = _T("(Àç±¸¼ºÁß) ³Ê¹« ÂÉ¿ìÁö ¸¶¼¼¿ä");	break;
	//	case 20 :	strTemp = _T("(Àç±¸¼ºÁß) ÀÌÁ¦ ±×¸¸ ´©¸£½Ã¸é ¾ÈµÉ±î¿ä? ^^");	break;
	//	case 21 :	strTemp = _T("(Àç±¸¼ºÁß) ...");	break;
	//	case 22 :	strTemp = _T("(Àç±¸¼ºÁß) ..");	break;
	//	case 23 :	strTemp = _T("(Àç±¸¼ºÁß) .");	break;
	//	case 24 :	strTemp = _T("(Àç±¸¼ºÁß) ³¡³¯ÁÙ ¾Ë¾ÒÁÒ?");	break;
	//	case 25 :	strTemp = _T("(Àç±¸¼ºÁß) ...");	break;
	//	case 26 :	strTemp = _T("(Àç±¸¼ºÁß) V3 ÀÛ¾÷À» ÇÏ´Â ¿ÍÁß¿¡¼­µµ ²À ÇÏ³ª ÇÏ°í ½ÍÀº°ÍÀÌ ÀÖ¾ú´Âµ¥...");	break;
	//	case 27 :	strTemp = _T("(Àç±¸¼ºÁß) ¹ºÁö °¡¸£ÃÄ µå¸±±î¿©?");	break;
	//	case 28 :	strTemp = _T("(Àç±¸¼ºÁß) ±×·³ ¹¹ ÇØÁÙ·¡¿ä? ¤»¤»");	break;
	//	case 29 :	strTemp = _T("(Àç±¸¼ºÁß) Ä£±¸ºÐµé Á» ´õ ¸¹ÀÌ ¸ð½Ã°í ¿À¼Å¼­ ÅºÆ®¶ó ÇØÁÖ¼¼¿ä");	break;
	//	case 30 :	strTemp = _T("(Àç±¸¼ºÁß) ¹º°¡ ÇÏ¸é¿©..");	break;
	//	case 31 :	strTemp = _T("(Àç±¸¼ºÁß) ÅºÆ®¶óÀÇ ¹Ù´Ú Áï ¶¥À» Á»´õ ¹Ì·ÁÇÏ°Ô ¹Ù²Ù°Å ½Í¾ú´ä´Ï´Ù.");	break;
	//	case 32 :	strTemp = _T("(Àç±¸¼ºÁß) ²À ÇÏ°í ½Í¾ú¾ú´Âµ¥...");	break;
	//	case 33 :	strTemp = _T("(Àç±¸¼ºÁß) ³Ê¹« ´ë±Ô¹¦ ÀÛ¾÷ÀÌ¶ó ÁøÇàÇÏÁö ¸øÇß³×¿ä.. ¾Æ½¬¾î¿©(³Ê¹«)");	break;
	//	case 34 :	strTemp = _T("(Àç±¸¼ºÁß) ...");	break;
	//	case 35 :	strTemp = _T("(Àç±¸¼ºÁß) ..");	break;
	//	case 36 :	strTemp = _T("(Àç±¸¼ºÁß) .");	break;
	//	case 37 :	strTemp = _T("(Àç±¸¼ºÁß) ¤»¤» À¯Àú´ÔµéÀÇ ¹ÝÀÀÀÌ ÁÁÀ¸¸é Çª³ä ¸®ÇÃÀº °è¼Ó µË´Ï´Ù.");	break;
	//	case 38 :	strTemp = _T("(Àç±¸¼ºÁß) ±×·³ Have nice day !!! ±×¸®°í ÁñÅº!!!");	break;
	//	default	:	strTemp = _T("Àç±¸¼º ÀÛ¾÷ÁßÀÔ´Ï´Ù.");	break;
	//}

	strTemp = _T("^^");
    g_cChatting->HT_vArrangeSavedHistory( strTemp.HT_szGetString(), g_ColorTable[12]);
	g_cChatting->HT_vChatting_SetSystemTextList();

	//	ÀÛ¾÷Áß ¸Þ½ÃÁö Ä«¿îÆ®
	m_iChat_MsgCount++;
	if( m_iChat_MsgCount > 38 )
		m_iChat_MsgCount = 0;
}
