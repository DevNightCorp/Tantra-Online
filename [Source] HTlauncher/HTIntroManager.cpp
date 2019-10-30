 
#include <windows.h>

#include "stdafx.h"
#include "resource.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTIntroManager.h"
#include "TNNetworkManager.h"
#include "HTWindowManager.h"
#include "HTApplication.h"
#include <wininet.h>
#define _INTROUI_SYS_FILE_NAME		_T("resource\\UI\\IntroUIInfo.sys")
#define _INTROUI_NOTIFY_FILE_NAME	_T("NotifyMsg.txt")
#define _TEST_SYS_FILE_NAME			_T("resource\\UI\\MainUIInfo.sys")


#define MESSAGE_DELAYTIME_SHORT			5000
#define MESSAGE_DELAYTIME_MIDDLE		10000
#define MESSAGE_DELAYTIME_LONG			60000
#define MESSAGE_DELAYTIME_LONGLONG		1000000

#define _ANCHOR_SCREEN_WIDTH	1024
#define _ANCHOR_SCREEN_HEIGHT	768

#define _MANDARA1ST_1			1
#define _MANDARA1ST_2			18
#define _MANDARA1ST_3			19

enum
{
	_REGULAR_CHECK		= 1,
	_IRREGULAR_CHECK	= 2,
	_SERVER_UPDATE		= 3,
	_ETC				= 4,
};

//	���� ó������
#define REQUEST_CANCEL						0
#define REQUEST_CONNECT_LOGINSERVER			10
#define	REQUEST_LOGIN						20
#define	REQUEST_WORLD_LIST					30
#define REQUEST_CONNECT_ZONESERVER			40
#define	REQUEST_MOVE_ZONE_SERVER			50
#define	REQUEST_CHAR_LIST					60
#define	REQUEST_CHAR_CREATE					70
#define	REQUEST_CHAR_REMOVE					80
#define	REQUEST_ZONE_CONNECT				90
#define	REQUEST_LOGOUT						100

// ���� ���۵Ǿ� �ִ� ���� �ڵ�
BYTE g_byCharacterTribe[8] = {	0x01,	// ����
								0x02,	// �Ƽ���
								0x03,	// ���
								0x04,	// ����
								0x05,	// Ų����
								0x06,	// ��ũ����
								0x07,	// ���ٸ���
								0x08,	// �����
							};

//	8������ ���� ���� �ɷ�ġ
//	0:����,1:�Ű�,2:����,3:����
HTint g_iCharacterChacraPoint[8][4] = 
{	
	12,	10,	11,	10,
	11,	12,	10,	10,
	11,	11,	11,	10,
	10,	10,	10,	13,
	12,	10,	11,	10,
	11,	12,	10,	10,
	11,	11,	11,	10,
	10,	10,	10,	13
};
#define CHOOSE_CHAKRA_POINT	7

//	New ĳ���� ��ġ / ���� (�ִ� 3��)
HTfloat g_fCharacter_New[3]			= { 1276,			56,				1150 };
HTfloat g_fCharacter_Exist[3][3]	= { 1255, 47, 1079,	1276, 47, 1094,	1295, 47, 1080, };
HTfloat g_fCharacter_ExistAngle[3]	= { 2.73f,			2.80f,			3.22f };

//	Window Monster Pos
HTvector3 g_vecWndMonsterPos[3] = { HTvector3( 1240, 49, 1079 ),
									HTvector3( 1262, 49, 1099 ),
									HTvector3( 1309.95f, 49, 1078.7f ) };

//	Window Monster Angle
HTfloat g_fWndMonsterAngle[3] = { HT_PI+0.07f, HT_PI+0.07f, HT_PI-0.07f };

//	Char info Wnd Pos
HTvector3 g_vecCharInfoWndPos[3] = { HTvector3( 110, 35, 0 ),	
									 HTvector3( 136, 35, 0 ),
									 HTvector3( 586, 35, 0 ) };

//	ī�޶� ��ġ
HTvector3 g_fCameraPos[10][2] = { HTvector3( 1270, 105, 90 ),	HTvector3( 1276, 95, -100 ),
								 HTvector3( 1276, 150, 100 ),	HTvector3( 1276, 150, -150 ),
								 HTvector3( 1276, 98, 650 ),	HTvector3( 1276, 98, 617 ),
							     HTvector3( 1276, 65, 1050 ),	HTvector3( 1276, 65, 1000 ),
								 HTvector3( 1276, 70, 1170 ),	HTvector3( 1276, 70, 1100 ),
								 HTvector3( 1250, 55, 1080 ),	HTvector3( 1246, 55, 1040 ),
								 HTvector3( 1271, 55, 1100 ),	HTvector3( 1266, 55, 1060 ),
								 HTvector3( 1300, 55, 1080 ),	HTvector3( 1305, 55, 1040 ),
								 HTvector3( 1400, 75, 1000 ),	HTvector3( 1330, 75, 1000 ),
								 HTvector3( 1276, 80, 1170 ),	HTvector3( 1276, 75, 1135 ) };

#define HT_INTRO_CAMERA_INIT			0
#define HT_INTRO_CAMERA_LOGIN			1
#define HT_INTRO_CAMERA_SERVER			2
#define HT_INTRO_CAMERA_SELECTCAHR		3
#define HT_INTRO_CAMERA_NEWCAHR			4
#define HT_INTRO_CAMERA_CHAR1			5
#define HT_INTRO_CAMERA_CHAR2			6
#define HT_INTRO_CAMERA_CHAR3			7
#define HT_INTRO_CAMERA_DELETECHAR		8
#define HT_INTRO_CAMERA_FACEZOOMIN		9

//	Intro Prosess
#define GAMESEQUENCE_INTRO_FIRST					0
#define GAMESEQUENCE_INTRO_LOADINTROMAP				1
#define GAMESEQUENCE_INTRO_LOADCHARACTER			2
#define GAMESEQUENCE_INTRO_INTROPLAY				3
#define GAMESEQUENCE_INTRO_GOMAINGAME				4

//����Ʈ��� ��Ʈ�ο� �Ƴ������Ÿ ��� ���� ���մ°� ���f�µ� ���� �������� ����(�� ���� ����..) 2. ��������������� ȯ�� 3. �ϱ����� ��Į�� ����  4. ��ȯ���� ���� �ٴ�Ƽ������ ��� �ý��ϴ�. �ð� �ǽø� �ѹ� �־� ���ø�,,,�׷��������� ��긮�� ����� ã���� ������ �����ϴ�.   ���׸��� ���� �α��� ȭ���� ī�޶�� ������Ʈ�� �Ÿ��� �־ õ�� ������Ʈ �Ϻκ��� �״�� ���� �ǹǷ� ���ݸ� ��� �ָ� ���� ������ �ɰ� �����ϴ�. ����,, ^^;; �����Ͻʽÿ�
#define INTRO_GATEMOB1		 2077
#define INTRO_GATEMOB2		 2077

//	�����ӽÿ� �������� ����ġ
HTbool	m_bIntro_RestartConnect;

extern CHTWindowManager* g_CGame;

CHTIntroManager::CHTIntroManager()
{
	//	ĳ���� ����Ʈ �ܿ��� _USER_MESSAGE_EXIT ��ư�� Ŭ���ߴ��� �ľ�
	m_bIntro_User_message_Exit = HT_FALSE;

	m_iIntroStatus			= GAMESEQUENCE_INTRO_FIRST;
	m_bSlideOn				= HT_FALSE;

	if( g_byReStartCode == 0 )
        g_poWebLogIn		= HT_NULL;

	m_iMandaraCCUserNum[0]	= -1;
	m_iMandaraCCUserNum[1]	= -1;
	m_iMandaraCCUserNum[2]	= -1;
}

CHTIntroManager::~CHTIntroManager()
{
}

//	Intro Data Clean
HTRESULT CHTIntroManager::HT_hrCleanUp()
{
	//	Delete Window
	//g_cUIManager->HT_DeleteWindow( _DIALOG_CHARACTERINFO2 );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_CHARACTERINFO3 );
	
	g_cUIManager->HT_DeleteWindow( _DIALOG_KATHANALOGO );
	g_cUIManager->HT_DeleteWindow( _DIALOG_LOGINBOX );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SERVERSELECT );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHARACTERINFO1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHARACTERCREATE );
	g_cUIManager->HT_DeleteWindow( _DIALOG_INPUTJUMINNO );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TOPMENU );
	g_cUIManager->HT_DeleteWindow( _DIALOG_LIMIT12AGE );
	g_cUIManager->HT_DeleteWindow( _DIALOG_3MANDARAVILLAGE );

	//	Unlode Intro Resource
	g_cLoading->HT_hrUnloadIntroResources();

	//	Delete Char
	if( m_nNewCharacterModelID != -1 )
	{
		g_pEngineHandler->HT_vDestroyCharacter( m_nNewCharacterModelID, 1 );
		m_nNewCharacterModelID = -1;
	}
	for( HTint i=0 ; i<3 ; i++ )
	{
		if( m_nExistCharacterModelID[i] != -1 )
		{
			g_pEngineHandler->HT_vDestroyCharacter( m_nExistCharacterModelID[i], 2 );
			m_nExistCharacterModelID[i] = -1;
		}
	}

	//	Delete Window Monster
	if( m_iMobForIntro[0] )       g_pEngineHandler->HT_vDestroyCharacter( m_iMobForIntro[0], 2 );
	if( m_iMobForIntro[1] )       g_pEngineHandler->HT_vDestroyCharacter( m_iMobForIntro[1], 2 );

	//	FX of Login Screen
	if( m_iFXID1OfLogin )		g_pEngineHandler->HT_hrStopSFX( m_iFXID1OfLogin );
	if( m_iFXID2OfLogin )		g_pEngineHandler->HT_hrStopSFX( m_iFXID2OfLogin );
	if( m_iNullModel1OfLogin )	g_pEngineHandler->HT_vDestroyObject( m_iNullModel1OfLogin, 0 );
	if( m_iNullModel2OfLogin )	g_pEngineHandler->HT_vDestroyObject( m_iNullModel2OfLogin, 0 );

	return HT_OK;
}

//	Init Data Setting and Load Intro UI
HTvoid CHTIntroManager::HT_vInitialize()
{
	//	Loading IntroUI Resource
	g_cLoading->HT_htLoadIntroUIResources();

	//	�̸� �ѹ� ������ �ؾ� ��Ȱ�ϰ� �����Ǵ°� ����.
	RECT rRect = g_CGame->CHTApplication::GetScreenRect();
	//	Character Total Number
	m_iCharNum				= 0;
	//	D3D Render Sw
	m_b3DRender				= HT_FALSE;
	//	UI Render Sw
	m_bUIRender				= HT_TRUE;
	//	�� ��/��
	m_bFaceZoominSw			= HT_FALSE;

	m_bCharSelectZoomInSw	= HT_FALSE;						//	ĳ������ �Ѹ��� ���� �߳�?
	m_bCharDeleteSw			= HT_FALSE;						//	ĳ���� ���� ����ġ
	m_dwErrorCheckDelayTime = 2000;							//	�޽��� ��ٷ� �ִ� �ð�

	m_bZoneServerConnected_ForIntro			= HT_FALSE;
	m_bZoneServerConnected_ForMainGame		= HT_TRUE;
	m_bZoneServerDisConnected_ForMainGame	= HT_FALSE;
	m_bZoneServerDisConnected_ForLoginFaild	= HT_FALSE;

	m_nSelectedCharNo		= 0;

	m_bServerDisconnectSw	= HT_FALSE;

	m_iScreenWidth			= 1024;
	m_iScreenHeight			= 768;

	// �ػ� ����
	m_iScreenWidth	= g_pEngineHandler->HT_iGetScreenWidth();
	m_iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();

	//���� �ػ󵵰� ���ػ�(800*600)�� ��� ���ػ� ���̾˷α׷� ��쵵�� ����
	m_iLowScreen = 0;
	if( m_iScreenWidth < _ANCHOR_SCREEN_WIDTH )
	{
		m_iLowScreen = 9;
	}

	//	String Init
	m_strID.HT_hrCleanUp();
	m_strSaveID.HT_hrCleanUp();
	m_strPassword.HT_hrCleanUp();
	m_strCharJoominNoFront.HT_hrCleanUp();
	m_strCharJoominNoBack.HT_hrCleanUp();

	//	�ִϸ��̼� �ε���
	m_iAnimationIndex = 0;
	//	���� ������ ����
	m_iCurServerIndex = 1;

	//	���� ���� �ٷ� �Ѿ�Ƿ�, �ѹ� �׷��ش�.
	this->HT_hrRender();

	//	������ ĳ���� �̸�
	m_strNewCharacterName.HT_hrCleanUp();

	//	�̸����� Display�� String
	m_strIntroMessage.HT_hrCleanUp();
	m_strIntroMessage_Display.HT_hrCleanUp();

	m_nNewCharacterModelID	= -1;
	for( HTint i=0 ; i<3 ; i++ )
		m_nExistCharacterModelID[i] = -1;

	m_bErrorCheckSw = HT_FALSE;

	//  ���� : ���� ���� ���� ���
	//	�ϴ��� ������ ������ ���� ���·� �����صд�.
	g_bReciveBillingServer = HT_TRUE;
	//	�ڵ��α����� �ƴҶ���
	if( g_byReStartCode == 0 )
        g_strLoginID.HT_hrCleanUp();
	g_iLoginResultID = 0;
	g_bPCRoomEventWndLogo = HT_FALSE;
	g_dwMyEvent = 0;

	//	ī�޶� �̵���Ȳ�� üũ����
	g_bCameraMove = HT_FALSE;

	//	�Ϻ��϶� ĳ�����̳� ����̸����� �Ұ��� ���� �ε�
	if( g_iInationalType == INATIONALTYPE_JAPEN )
        HT_g_LoadNotCharAndGuildName();

	// Tantra V3 UI ����
	if( g_cUIManager )
	{
		delete( g_cUIManager );
		g_cUIManager = NULL;
	} 
	g_cUIManager = new CHTUIManager;
	// IntroUI ClientRes Setting (Tantra V3)
	g_cUIManager->HTSetGameEnvironment(m_iScreenWidth, m_iScreenHeight, g_iInationalType, g_gServerType, g_bDevelopingMode, 0);
    //	Create Window
	this->HT_vIntro_CreateWindow();

	//	����ŸƮ�϶��� ���⸦ ��ġ�� �ȵȴ�.
	if( g_byReStartCode == 0 )
	{
		CHTString szMessage;
		this->HT_hrSetMessage( eMsgLogInInputID, &szMessage );
		g_poWebLogIn = new CHTWebLogIn;
		this->HT_vSetURL();

		//	�ε� �̹����� �ε��Ѵ�.
		g_pEngineHandler->HT_vCreate_LoadingBGImage();
	}

	//	For Render Logo
	m_bForRenderLogo = HT_FALSE;
	//	For Render GoMainGame
	m_bForRenderGoMainGame = HT_FALSE;

	//	Set Camera
	if( g_byReStartCode == 0 )
	{
		g_cCamera.HT_vUpdateLook_SetPositon( g_fCameraPos[HT_INTRO_CAMERA_INIT][0] );
		g_cCamera.HT_vUpdateEye_SetPositon( g_fCameraPos[HT_INTRO_CAMERA_INIT][1] );
	}
	//	������϶��� ī�޶� ĳ���������� �������ش�.
	else if( g_byReStartCode == 2 )
	{
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_SERVER][0], 1, 0.0f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_SERVER][1], 1, 0.0f);
	}

	//	About Show window
	m_iShowWinNo = 0;
	m_dwShowWinStartTime = 0;
	m_dwShowWinDelayTime = 0;

	//	About Message
	m_strMeg.HT_hrCleanUp();
	m_bShowMsg = HT_FALSE;
	m_dwShowMsgTime = 0;
	m_dwShowMsgStartTime = 0;

	//	About Otheer Object ID Login
	m_iMobForIntro[0] = 0;
	m_iMobForIntro[1] = 0;
	m_dwChangeAniMobTime[0] = 0;
	m_dwChangeAniMobTime[1] = 0;

	m_bLoginDelay = HT_FALSE;
	m_dwLoginStartTime = 0;

	//	Init Character data
	for( i=0 ; i<3 ; i++ )
        memset( &m_oSeverChar[i], 0, sizeof(_HT_CHARINFO) );

	//	��������Ʈ���� �������� ���� ��û
	m_bReqConnectServerInSerSel = HT_FALSE;
	//	�����ӽÿ� �������� ����ġ
	m_bIntro_RestartConnect = HT_FALSE;

	//	FX of Login Screen
	m_iFXID1OfLogin = 0;
	m_iFXID2OfLogin = 0;
	m_iNullModel1OfLogin = 0;
	m_iNullModel2OfLogin = 0;

	//	Load CharacterData Sequence
	m_iLoadCharDataSequence = -1;
	//	For Render Character load
	m_bForRenderCharacterData = HT_FALSE;
	//	Stop Mob Animation
	m_bStopMobAnimationSw = HT_FALSE;
	//	Save ID
	m_bIntro_SaveID = HT_FALSE;
	//	After Login Time Check
	m_dwIntro_LoginTimeCheck = timeGetTime();;

	//	Chnage Status Intro Map Loading
	m_iIntroStatus = GAMESEQUENCE_INTRO_LOADINTROMAP;
}
//	Create Window
HTvoid CHTIntroManager::HT_vIntro_CreateWindow()
{
	HTint i;
	CHTString strTemp;
	CHTString strMessage;

	//	[Kathana Logo]
	if( m_iScreenWidth < _ANCHOR_SCREEN_WIDTH )
	{
		g_cUIManager->HT_CreateWindow( _DIALOG_KATHANALOGO, _T(""), 512, 512, g_cUIManager->ActionTarget, 0 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_KATHANALOGO, 0, 100, 0, 0 );
	}
	else
	{
		g_cUIManager->HT_CreateWindow( _DIALOG_KATHANALOGO, _T(""), 1024, 512, g_cUIManager->ActionTarget, 0 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_KATHANALOGO, 0, 101, 0, 0 );
	}
	g_cUIManager->HT_WindowArrangement( _DIALOG_KATHANALOGO, 5 );
	if( g_byReStartCode == 0 )
        g_cUIManager->HT_ShowWindow(_DIALOG_KATHANALOGO );

	//	[LoginBox]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_LOGINBOX, _T(""), 304, 208, g_cIntroManager->HT_hrIntro_InputCheckForLogin, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_LOGINBOX, m_iScreenWidth/2-150, m_iScreenHeight-400 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_LOGINBOX, 0, 34, 0, 0 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_LOGINBOX, 1, 25, 190, 175, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,0.9f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 185, 176, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_LOGINBOX, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_LOGINBOX, 2, 25, 55, 175, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,0.9f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 50, 176, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_LOGINBOX, 2 );
	//	Set Enter Button
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_LOGINBOX, 2 );
	//	Edit ID
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_LOGINBOX, 3, 0, 135, 65, 140, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroID, &strMessage, _T(""), _T("") );	//	���̵�
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 43, 65, 70, 19 );
	//	Edit Password
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_LOGINBOX, 4, 0, 135, 100, 140, 19 );
	g_cUIManager->HT_SetModeEditBoxControl( _DIALOG_LOGINBOX, 4, 1 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroPassWord, &strMessage, _T(""), _T("") );	//	��й�ȣ
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 43, 99, 70, 19 );
	//	ID ����ϱ�
	g_cUIManager->HT_SetScriptMessage( eMsgIntroIDsave, &strMessage, _T(""), _T("") );	//	ID ����ϱ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 43, 133, 70, 19 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_LOGINBOX, 5, 0, 133, 130, 0, 0, 1500, 22, 22 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_LOGINBOX, 6, 27062, 133, 130, HT_COLOR( 1,1,1,1 ) );
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_LOGINBOX, 6, HT_FALSE );

	//	[Server Select]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SERVERSELECT, _T(""), 288, 367, g_cIntroManager->HT_hrIntro_InputCheckForServerSelect, 0 );
    //g_cUIManager->HT_MoveWindow( _DIALOG_SERVERSELECT, 312, 190 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SERVERSELECT, 5 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_SERVERSELECT, 0, 36, 0, 0 );
	//	Label fors_debug ȥ��ѡ������� �ĳ�Ѱ�������һ��
	//g_cUIManager->HT_SetScriptMessage( eMsgIntroSelectServer, &strMessage, _T(""), _T("") );	//	��������
	//g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 10, 130, 17 );
	//	Button Cancel
    g_cUIManager->HT_AddButtonControl( _DIALOG_SERVERSELECT, 1, 25, 180, 338, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 339, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SERVERSELECT, 1 );
	//	Button OK
	g_cUIManager->HT_AddButtonControl( _DIALOG_SERVERSELECT, 2, 25, 50, 338, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 45, 339, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SERVERSELECT, 2 );
	//	Set Enter Button
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_SERVERSELECT, 2 );
	//	Button Server list
	CHTString strServerName;
	for( i=0 ; i<8 ; i++)
	{
		g_cUIManager->HT_AddButtonControl( _DIALOG_SERVERSELECT, 3+i, 19, 23, 49+(i*34), 20, 21, 1500 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SERVERSELECT, 3+i );
		if( i<g_iWorldNum )
		{
			strServerName.HT_szFormat( "%s", g_oWorldList[i][m_iCurServerIndex].szWorldName );
			if( i == 0 )	g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 3+i, strServerName.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 27, 49+(i*34), 158, 23 );
			else			g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 3+i, strServerName.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 27, 49+(i*34), 158, 23 );
			//strServerName.HT_szFormat( "��Ȱ" );
			g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 20+i, eMsgIntorSmooth, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 206, 49+(i*34), 54, 23 );
		}
	}

	//	[Character Info 1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHARACTERINFO1, _T(""), 289, 415, g_cIntroManager->HT_hrIntro_InputCheckForCharInfo, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERINFO1, 200, 50 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARACTERINFO1, 0, 33, 0, 0 );
	//	Label
	//	Label Char Info
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgCharInfoTitle, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 66, 9, 155, 17 );//ĳ���� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, sMsgAddressName, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 40, 78, 17 );//�̸�
	//	Label Level Name
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 11, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 65, 180, 17 );
	//	Label My God Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntorTrimuriti, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 104, 78, 17 );//�ֽ�
	//	Label My God
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 13, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 130, 180, 17 );
	//	Label Chakra
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 168, 78, 17 );//��ũ��
	//	Label Chakra 1_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroMuscleChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 194, 106, 17 );//��������ũ��
	//	Label Chakra 2_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroNerveChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 220, 106, 17 );//�Ű�����ũ��
	//	Label Chakra 3_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroheartChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 246, 106, 17 );//��������ũ��
	//	Label Chakra 4_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroSoulChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 271, 106, 17 );//��������ũ��
	//	Label Chakra 1_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 19, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 194, 59, 17 );
	//	Label Chakra 2_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 20, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 220, 59, 17 );
	//	Label Chakra 3_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 21, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 246, 59, 17 );
	//	Label Chakra 4_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 22, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 271, 59, 17 );
	//	Label Connect Position Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroSavePos, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 311, 78, 17 );//������ġ
	//	Label Connect Position
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 24, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 338, 180, 17 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 1, 25, 200, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f),195, 383, 70, 23 );//���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERINFO1, 1 );
	//	Button OK
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 2, 25, 30, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 383, 70, 23 );//Ȯ��
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERINFO1, 2 );
	//	Button Del Char
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 3, 25, 115, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 3, eMsgCommonDelete, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 383, 70, 23 );//����
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERINFO1, 3 );

	//	[Character Carate]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHARACTERCREATE, _T(""), 800, 410, g_cIntroManager->HT_hrIntro_InputCheckForCharCreate, 0 );
	//g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERCREATE, 115, 242 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHARACTERCREATE, 5 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARACTERCREATE, 0, 35, 0, 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARACTERCREATE, 0, 37, 510, 0 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 1, 25, 690, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 685, 382, 70, 23 );//���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 2, 25, 560, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 555, 382, 70, 23 );//Ȯ��
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 2 );
	//	Button Tribe Left
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 3, 38, 69, 67, 39, 40 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroLeft, &strMessage, _T(""), _T("") );	//	Left
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 3, strMessage );
	//	Button Tribe Right
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 4, 22, 205, 67, 23, 24 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroRight, &strMessage, _T(""), _T("") );	//	Right
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 4, strMessage );
	//	Button Face Left
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 5, 38, 69, 276, 39, 40 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroLeft, &strMessage, _T(""), _T("") );	//	Left
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 5, strMessage );
	//	Button Face Right
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 6, 22, 205, 276, 23, 24 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroRight, &strMessage, _T(""), _T("") );	//	Right
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 6, strMessage );
	//	Button Head Left
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 7, 38, 69, 339, 39, 40 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroLeft, &strMessage, _T(""), _T("") );	//	Left
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 7, strMessage );
	//	Button Hed Right
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 8, 22, 205, 339, 23, 24 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroRight, &strMessage, _T(""), _T("") );	//	Right
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_CHARACTERCREATE, 8, strMessage );
	//	Button Face Chakra1
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 9, 28, 743, 178, 29, 30 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 9 );
	//	Button Face Chakra2
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 10, 28, 743, 214, 29, 30 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 10 );
	//	Button Face Chakra3
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 11, 28, 743, 246, 29, 30 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 11 );
	//	Button Face Chakra4
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 12, 28, 743, 277, 29, 30 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 12 );
	//	Button Face Chakra5
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 13, 28, 743, 310, 29, 30 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 13 );
	////	Button Face Service
	//g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 30, 25, 115, 382, 26, 27 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 30, _T("^__^"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 109, 382, 70, 23 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 30 );
	//	Edit Character Name
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_CHARACTERCREATE, 3, 0, 567, 82, 180, 18 );
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHARACTERCREATE, 3, SZNAME_LENGTH-2 );
	else
		g_cUIManager->HT_SetEditBoxControlLimitText( _DIALOG_CHARACTERCREATE, 3, SZNAME_LENGTH );
	//	Label Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroCreateNewChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 73, 6, 145, 20 );//��ĳ���͸����
	//	Label ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, sMsgAddressTribe, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 41, 80, 14 );//��  ��
	//	Label ����2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 12, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 65, 103, 17 );
	//	Label ���� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroExplainTribe, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 108, 80, 14 );//��������
	//	Label ���� ���� 2
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_CHARACTERCREATE, 14, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 37, 137, 213, 88 );
	//	Label �� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgSelectFace, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 250, 80, 14 );//�󱼼���
	//	Label �� ���� 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 16, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f),92, 276, 103, 17 );
	//	Label �Ӹ� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgFaceHair3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 315, 80, 14 );//�Ӹ�����
	//	Label �Ӹ� ���� 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 18, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 339, 103, 17 );
	//	Label Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroCreateNewChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 580, 6, 145, 19 );//��ĳ���͸����
	//	Label ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroInputName, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 614, 59, 80, 14 );//�̸��Է�
	//	Label ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 614, 146, 80, 14 );//��ũ��
	//	Label ������ ��ũ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroMuscleChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 178, 106, 18 );//������ ��ũ��
	//	Label �Ű��� ��ũ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroNerveChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 214, 106, 18 );//�Ű��� ��ũ��
	//	Label ������ ��ũ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroheartChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 246, 106, 18 );//������ ��ũ��
	//	Label ������ ��ũ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroSoulChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 277, 106, 18 );//������ ��ũ��
	//	Label ��Ű�� ����Ʈ
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroServicePoint, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 310, 106, 18 );//���� ����Ʈ
	//	Label ������ ��ũ��2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 25, _T("11"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 178, 60, 18 );
	//	Label �Ű��� ��ũ��2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 26, _T("22"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 214, 60, 18 );
	//	Label ������ ��ũ��2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 27, _T("33"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 246, 60, 18 );
	//	Label ������ ��ũ��2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 28, _T("44"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 277, 60, 18 );
	//	Label ���� ����Ʈ
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 29, _T("55"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 310, 60, 18 );

	//	[Input Jumin Number]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_INPUTJUMINNO, _T(""), 290, 300, g_cIntroManager->HT_hrIntro_InputCheckForJuminNo, 0 );
    g_cUIManager->HT_MoveWindow( _DIALOG_INPUTJUMINNO, 458, 212 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_INPUTJUMINNO, 0, 32, 0, 0 );

	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroDeleteChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 7, 150, 19 );//ĳ���ͻ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroExplain, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 104, 54, 84, 14 );//�� ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroResidentNumber, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 104, 196, 84, 14 );//�ֹε�Ϲ�ȣ
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 5, eMsgIntroExplain01, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 40, 83, 210, 84 );//������ ���Ͻø� �ֹε�Ϲ�ȣ�� �Է��Ͻð� Ȯ���� �����ּ���
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INPUTJUMINNO, 5, 7 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_INPUTJUMINNO, 1, 25, 180, 271, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 271, 70, 23 );//���
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INPUTJUMINNO, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_INPUTJUMINNO, 2, 25, 50, 271, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 45, 271, 70, 23 );//Ȯ��
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INPUTJUMINNO, 2 );

	if( g_iInationalType == INATIONALTYPE_KOREA )
	{	
		//	Edit Jumin1
		g_cUIManager->HT_AddEditBoxControl( _DIALOG_INPUTJUMINNO, 3,  0,  38, 222, 100, 15 );
		//	Edit Jumin2
		g_cUIManager->HT_AddEditBoxControl( _DIALOG_INPUTJUMINNO, 4, 0, 153, 222, 100, 15 );
		g_cUIManager->HT_SetModeEditBoxControl( _DIALOG_INPUTJUMINNO, 4, 1 );
	}
	else
	{
		//	Text Jumin1
		g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 3, _T("Password"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 38,222, 100,15);
		//	Edit Jumin2
		g_cUIManager->HT_AddEditBoxControl( _DIALOG_INPUTJUMINNO, 4, 0, 153, 222, 100, 15 );
		g_cUIManager->HT_SetModeEditBoxControl( _DIALOG_INPUTJUMINNO, 4, 1 );
	}

	//	[Top Menu]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TOPMENU, _T(""), 300, 120, g_cIntroManager->HT_hrIntro_InputCheckForTopMenu, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TOPMENU, 3 );
	//	Button Create Character
	g_cUIManager->HT_AddButtonControl( _DIALOG_TOPMENU, 1, 16, 100, 10, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TOPMENU, 1, eMsgIntroTopMenu01, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 100, 13, 194, 19 );//Create Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TOPMENU, 1 );
	//	Button Select Character
	g_cUIManager->HT_AddButtonControl( _DIALOG_TOPMENU, 2, 16, 100, 40, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TOPMENU, 2, eMsgIntroTopMenu02, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 100, 43, 194, 19 );//Select Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TOPMENU, 2 );
	//	Button Exit Game
	g_cUIManager->HT_AddButtonControl( _DIALOG_TOPMENU, 3, 16, 100, 70, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TOPMENU, 3, eMsgIntroTopMenu03, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 100, 75, 194, 19 );//Exit Game
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TOPMENU, 3 );

	//	[_DIALOG_LIMIT12AGE]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_LIMIT12AGE, _T(""), 64, 64, g_cIntroManager->HT_hrIntro_InputCheckForTopMenu, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_LIMIT12AGE, 9 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_LIMIT12AGE, 0, 31, 0, 0 );

	//	[_DIALOG_3MANDARAVILLAGE]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_3MANDARAVILLAGE, _T(""), 192, 90, g_cIntroManager->HT_hrIntro_InputCheckFor3MandaraVillage, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_3MANDARAVILLAGE, 6 );
	//	ù��° ���ٶ� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_3MANDARAVILLAGE, 1, 16, 0, 10, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_3MANDARAVILLAGE, 1, eMsgPortalExtraMandara1, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 13, 194, 19 );//Create Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_3MANDARAVILLAGE, 1 );
	//	�ι�° ���ٶ� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_3MANDARAVILLAGE, 2, 16, 0, 35, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_3MANDARAVILLAGE, 2, eMsgPortalExtraMandara2, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 38, 194, 19 );//Select Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_3MANDARAVILLAGE, 2 );
	//	����° ���ٶ� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_3MANDARAVILLAGE, 3, 16, 0, 60, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_3MANDARAVILLAGE, 3, eMsgPortalExtraMandara3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 62, 194, 19 );//Exit Game
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_3MANDARAVILLAGE, 3 );
}
//	Load Intro Map
HTvoid CHTIntroManager::HT_vLoadIntroMap()
{
	//	For Render Logo
	if( !m_bForRenderLogo )
		return;

	//	��Ʈ�� �� / ��ü ���ҽ� �ҷ�����
	g_cLoading->HT_hrLoadIntroResources();
	//	D3D Render Sw
	m_b3DRender				= HT_TRUE;

	g_cUIManager->HT_HideWindow( _DIALOG_KATHANALOGO );
	if( g_iInationalType == INATIONALTYPE_KOREA )
        g_cUIManager->HT_ShowWindow( _DIALOG_LIMIT12AGE );

	if( g_byReStartCode == 0 )
	{
        this->HT_vIntro_SetShowWindow( _DIALOG_LOGINBOX, 1000 );
		//	Load Id
		this->HT_vIntro_LoadID();
	}

	g_pEngineHandler->HT_hrLoadMapObjsInitial( g_fCameraPos[HT_INTRO_CAMERA_LOGIN][1] );

	//	Login Monster
	m_iMobForIntro[0] = g_pEngineHandler->HT_iCreateMonster( INTRO_GATEMOB1, HTvector3( 0, 0, 0 ) );
	g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[0], HT_PI );
	m_iMobForIntro[1] = g_pEngineHandler->HT_iCreateMonster( INTRO_GATEMOB1, HTvector3( 0, 0, 0 ) );
	g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[1], HT_PI );

	//	�ϵμ���
	//m_iNorthImperial = g_pEngineHandler->HT_iCreateMonster( 2250, HTvector3( 1276, 90, 90 ) );
	//g_pEngineHandler->HT_hrRotateObject( m_iNorthImperial, HT_PI );
	//g_pEngineHandler->HT_hrStartAnimation( m_iNorthImperial, 2250, HT_ANISTATE_STD, -1 );

	//	Set Position Login Mob
	g_pEngineHandler->HT_hrMoveObject( m_iMobForIntro[0], HTvector3( 1154, 105, 216 ) );
	g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[0], HT_PI-(HT_PI/4) );
	g_pEngineHandler->HT_hrScaleObject( m_iMobForIntro[0], HTvector3( 3.0f, 3.0f, 3.0f ) );
	g_pEngineHandler->HT_hrStartAnimation(  m_iMobForIntro[0], INTRO_GATEMOB1, HT_ANISTATE_WLK, 1 );

	g_pEngineHandler->HT_hrMoveObject( m_iMobForIntro[1], HTvector3( 1398, 105, 216 ) );
	g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[1], HT_PI+(HT_PI/4) );
	g_pEngineHandler->HT_hrScaleObject( m_iMobForIntro[1], HTvector3( 3.0f, 3.0f, 3.0f ) );
	g_pEngineHandler->HT_hrStartAnimation(  m_iMobForIntro[1], INTRO_GATEMOB1, HT_ANISTATE_RUN, 1 );

	m_iNullModel1OfLogin = g_pEngineHandler->HT_iCreateNullModel( HTvector3( 1192, 173, 160 ) );
	m_iNullModel2OfLogin = g_pEngineHandler->HT_iCreateNullModel( HTvector3( 1359, 173, 160 ) );
	g_pEngineHandler->HT_hrStartSFX( &m_iFXID1OfLogin, HT_FX_INTROMFIRE, m_iNullModel1OfLogin, HT_TRUE );
	g_pEngineHandler->HT_hrStartSFX( &m_iFXID2OfLogin, HT_FX_INTROMFIRE, m_iNullModel2OfLogin, HT_TRUE );

	m_dwChangeAniMobTime[0] = timeGetTime()+1000;
	m_dwChangeAniMobTime[1] = timeGetTime()+1000;

	if( g_byReStartCode == 0 )
	{
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_LINEMOVE, g_fCameraPos[HT_INTRO_CAMERA_LOGIN][0], 1, 0.02f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_LINEMOVE, g_fCameraPos[HT_INTRO_CAMERA_LOGIN][1], 1, 0.02f);
	}

	//	Change Status Login and Server select
	m_iIntroStatus = GAMESEQUENCE_INTRO_INTROPLAY;
}
//	Load Basic Char Data
HTvoid CHTIntroManager::HT_vLoadBasicCharData()
{
	//	For Render Character load
	if( !m_bForRenderCharacterData )
		return;

	m_IntroBackFX.HT_hrBeginFX( HTvector3( g_fCharacter_New[0], g_fCharacter_New[1], g_fCharacter_New[2] ) );

	//	Load Character Data
	if( HT_SUCCEED(	g_cLoading->HT_hrLoadCharacterResource() ) ||
		m_iLoadCharDataSequence < 10 )
	{
		switch( m_iLoadCharDataSequence )
		{
			case 0 :
				g_pEngineHandler->HT_hrLoadCharacterTexture();
				m_iLoadCharDataSequence = 1;
				break;
			case 1 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 1 );
				m_iLoadCharDataSequence = 2;
				break;
			case 2 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 2 );
				m_iLoadCharDataSequence = 3;
				break;
			case 3 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 3 );
				m_iLoadCharDataSequence = 4;
				break;
			case 4 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 4 );
				m_iLoadCharDataSequence = 5;
				break;
			case 5 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 5 );
				m_iLoadCharDataSequence = 6;
				break;
			case 6 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 6 );
				m_iLoadCharDataSequence = 7;
				break;
			case 7 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 7 );
				m_iLoadCharDataSequence = 8;
				break;
			case 8 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 8 );
				m_iLoadCharDataSequence = 9;
				break;
			case 9 :
				g_pEngineHandler->HT_hrLoadCharacterBonModelAni( 9 );
				m_iLoadCharDataSequence = 10;
				break;
		}
		m_bForRenderCharacterData = HT_FALSE;
	}
	else
	{
		m_iLoadCharDataSequence = 10;
	}

	//	��ü �ε� ���α׷����� �����ٸ�
	if( m_iLoadCharDataSequence == 10 )
	{
		m_nExistCharacterNumber	= 0;
		m_nNewCharacterModelID	= -1;

		//	Show Window
		g_cUIManager->HT_HideWindow( _DIALOG_KATHANALOGO );
		//	Hide Window
		g_cUIManager->HT_HideWindow( _DIALOG_LOGINBOX );
		//	Hide Window
		g_cUIManager->HT_HideWindow( _DIALOG_SERVERSELECT );

		//	Show Top Window
		g_cUIManager->HT_ShowWindow( _DIALOG_TOPMENU );

		//	Set Position Login Mob
		g_pEngineHandler->HT_hrMoveObject( m_iMobForIntro[0], HTvector3( 1180, 68, 1380 ) );
		g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[0], HT_PI-(HT_PI/4) );
		g_pEngineHandler->HT_hrScaleObject( m_iMobForIntro[0], HTvector3( 2.0f, 2.0f, 2.0f ) );
		g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[0], INTRO_GATEMOB1, HT_ANISTATE_RUN, 1 );

		g_pEngineHandler->HT_hrMoveObject( m_iMobForIntro[1], HTvector3( 1365, 68, 1380 ) );
		g_pEngineHandler->HT_hrRotateObject( m_iMobForIntro[1], HT_PI+(HT_PI/4) );
		g_pEngineHandler->HT_hrScaleObject( m_iMobForIntro[1], HTvector3( 2.0f, 2.0f, 2.0f ) );
		g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[1], INTRO_GATEMOB1, HT_ANISTATE_WLK, 1 );

		m_dwChangeAniMobTime[0] = timeGetTime()+1000;
		m_dwChangeAniMobTime[1] = timeGetTime()+1000;

		//	ĳ���͸���Ʈ�� �ǰ��� ĳ���͸� ����
		this->HT_vExistCharCreate();

		//	Hide Server Select Window
		g_cUIManager->HT_HideWindow( _DIALOG_SERVERSELECT );

		m_iLoadCharDataSequence = -1;
		//	Change Status Login and Server select
		m_iIntroStatus = GAMESEQUENCE_INTRO_INTROPLAY;
	}
}
//	Go Main Game
HTvoid CHTIntroManager::HT_vIntro_GoMainGame()
{
	//	For Render GoMainGame
	if( !m_bForRenderGoMainGame )
		return;

	//	�ε��̹��� ����1
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.1f );

	//	���ΰ��� ���ҽ��� �ε��Ѵ�.
	g_cLoading->HT_hrLoadMainResources( g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER );

	//	�ε��̹��� ����5
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.9f );

	/*
	//	�÷�ŷ ���(������ ���� ��)�� �����Ѵ�.
	if ( g_pFlocking ) HT_DELETE( g_pFlocking );
	g_pFlocking = new CHTFlocking;
	if(g_pFlocking)
	{
		HTint iNumFlocking = g_pEngineHandler->HT_iGetNumFlocking();
		g_pFlocking->HT_hrCreate( iNumFlocking );

		for ( HTint iFlocking = 0; iFlocking < iNumFlocking; ++iFlocking )
		{
			HTdword dwNPC;
			HTvector3 vecPos;
			g_pEngineHandler->HT_vGetBaseFlockingInfo( iFlocking, &dwNPC, &vecPos );
			g_pFlocking->HT_vPushOne( dwNPC, vecPos );
		}
		g_pEngineHandler->HT_vReleaseBaseFlockingInfo();
	}
	*/

	//	�ε��̹��� ����5
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 1.0f );

	//	���� ���� ����
	if( g_wResentZoneServerID == ZONE_MANDARA1ST || 
		g_wResentZoneServerID == ZONE_MANDARA2ND || 
		g_wResentZoneServerID == ZONE_MANDARA3TH )
		g_wFirstZoneServerID = g_wResentZoneServerID;
	else
		g_wFirstZoneServerID = 0;

	//	Change Status Intro Complate
	m_iIntroStatus = GAMESEQUENCE_INTRO_RETURNCOMPLETE;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrUpdate()
// D : UI���� ������ ������Ʈ
// R : HT_TRUE/HT_FALSE
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrUpdate( HTfloat fElapsedTime )
{
	//	_USER_MESSAGE_EXIT �� ���õǾ����� �Ǵ�
	if( m_bIntro_User_message_Exit )
	{
		//	��Ʈ�ο� ���ҽ��� �� �����.
		this->HT_hrCleanUp();
		return RETURNTYPE_EXIT_INTRO;
	}

	//	Process
	if( m_iIntroStatus == GAMESEQUENCE_INTRO_FIRST )
	{
		//	Init Data Setting and Load Intro UI
		this->HT_vInitialize();
	}
	else if( m_iIntroStatus == GAMESEQUENCE_INTRO_LOADINTROMAP )
	{
		//	Load Intro Map
		if( g_byReStartCode == 2 )
			m_bForRenderLogo = HT_TRUE;
        this->HT_vLoadIntroMap();
	}
	else if( m_iIntroStatus == GAMESEQUENCE_INTRO_LOADCHARACTER )
	{
		//	Load Basic Char Data
        this->HT_vLoadBasicCharData();
	}
	else if( m_iIntroStatus == GAMESEQUENCE_INTRO_INTROPLAY )
	{
	}
	else if( m_iIntroStatus == GAMESEQUENCE_INTRO_GOMAINGAME )
	{
		//	Go Main Game
		this->HT_vIntro_GoMainGame();
	}
	else if( m_iIntroStatus == GAMESEQUENCE_INTRO_RETURNCOMPLETE )
	{
		m_iIntroStatus = GAMESEQUENCE_INTRO_FIRST;
		return RETURNTYPE_INTRO_COMPLETE;
	}

	this->HT_hrCameraUpdate( fElapsedTime );
	//	�޽��� �پ� �ִ� �ð�üũ
	this->HT_vUpdate_MsgDisplayTimeCheck();
	//	���� ���� ���� üũ �����췯
	this->HT_vUpdate_ServerConnectCheck();
	//	������ ������ ���������� ������� ������
	this->HT_vUpdate_DisconnectServer();
	//	�ִϸ��̼� üũ
	this->HT_vAnimationCheck();
	//	Auto Login
	this->HT_vAutoLoginUpdate();
	//	Show Window
	this->HT_vUpdate_ShowWindow();
	//	Login Delay Time
	this->HT_vUpdate_LoginDelay();
	//	After Login Time Check
	this->HT_vAfterLoginTimeCheck();

	return HT_OK;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrRender()
// D : UI���� ������ ������
// R : HT_TRUE/HT_FALSE
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrRender()
{
	HTbool bRenderSw = HT_FALSE;

	if( m_iIntroStatus != GAMESEQUENCE_INTRO_RETURNCOMPLETE )
	{
		bRenderSw = HT_TRUE;
	}

	if( bRenderSw )
	{	
		if( m_b3DRender )
			g_pEngineHandler->HT_hrRenderWorld();

		// Tantra V3 Render
		if( m_bUIRender )
		{
			if ( g_cUIManager ) 
			{
				g_cUIManager->HT_Render();
				m_bForRenderLogo = HT_TRUE;
				m_bForRenderCharacterData = HT_TRUE;
			}
		}

		//	Loading Progress Bar
		if( m_iIntroStatus == GAMESEQUENCE_INTRO_LOADCHARACTER &&
			(m_iLoadCharDataSequence>=0 && m_iLoadCharDataSequence<=10) )
		{
			HTfloat fBarValue = HTfloat((HTfloat)(m_iLoadCharDataSequence+1)/10);
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_FALSE, fBarValue );
		}

		//	About Message
		if( m_bShowMsg )
		{
			// �ؽ�Ʈ�� ȭ���� ����� ����
			HTvector3 vecMsgText;
			vecMsgText = HTvector3( (m_iScreenWidth - g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, m_strMeg.HT_szGetString() ))/2.0f+20.0f, (m_iScreenHeight-696.0f) + 600.0f, 0.0f );
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strMeg.HT_szGetString(), vecMsgText, HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
		}

		//	ĳ���� �̸� ǥ��
		//	ĳ������ �Ѹ��� ���� �������� ǥ�þ���
		if( m_iIntroStatus == GAMESEQUENCE_INTRO_INTROPLAY &&
			m_bCharSelectZoomInSw != HT_TRUE )
		{
			for( HTint i=0 ; i<3 ; i++ )
			{
				if( m_oSeverChar[i].bSw )
				{
					HTvector3 vTextPos;
					vTextPos.x = g_fCharacter_Exist[i][0];
					vTextPos.y = g_fCharacter_Exist[i][1] + m_oSeverChar[i].fHight + 3;
					vTextPos.z = g_fCharacter_Exist[i][2];
					
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_oSeverChar[i].sCharInfo.szCharName, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
				}
			}
		}

		//	For Render GoMainGame
		m_bForRenderGoMainGame = HT_TRUE;
	}

	//	IME ó����
	this->HT_vIntroRender_IME();

	return HT_OK;
}

HTvoid
CHTIntroManager::HT_vIntroRender_IME()
{
	if( !g_cUIManager )
		return;

	//	Get Cursor Pos
	HTvector3 vecCursorPos = g_cUIManager->HT_GetEditBoxCursorPos();

	if( g_iInationalType == INATIONALTYPE_KOREA ||
		g_iInationalType == INATIONALTYPE_JAPEN )
	{
		//	IME_CandiList
		for( HTint i=0 ; i<9 ; i++ )
		{
			if( !g_strCandidateList[i].HT_bIsEmpty() )
			{
				if( g_iCandiSelectionNo == i )
				{
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_strCandidateList[i].HT_szGetString(), 
									HTvector3( vecCursorPos.x, vecCursorPos.y-180+((9-g_idwCandidateListNo)*20)+(i*20), 0.0f ), g_ColorTable[15], HT_COLOR( 0.0f, 0.5f, 0.5f, 0.7f ), 3.0f  );
				}
				else
				{
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_strCandidateList[i].HT_szGetString(), 
									HTvector3( vecCursorPos.x, vecCursorPos.y-180+((9-g_idwCandidateListNo)*20)+(i*20), 0.0f ), g_ColorTable[12], HT_COLOR( 0.5f, 0.0f, 0.5f, 0.7f ), 3.0f  );
				}
			}
		}
	}

	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		if( !g_strCompStr.HT_bIsEmpty() )
		{
            g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_strCompStr.HT_szGetString(), 
							vecCursorPos, g_ColorTable[12], HT_COLOR( 0.0f, 0.5f, 0.5f, 0.7f ), 3.0f );
		}
	}
	
	//	IME_Description
	if( g_iInationalType == INATIONALTYPE_CHINA || 
	    g_iInationalType == INATIONALTYPE_TAIWAN )
	{
		if( !g_strImeName.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_strImeName.HT_szGetString(), 
							HTvector3( 0, (HTfloat)(g_pEngineHandler->HT_iGetScreenHeight()-16 ), 0.0f ), g_ColorTable[12], HT_COLOR( 0.5f, 0.0f, 0.5f, 0.7f ), 3.0f );
		}
	}
}

//-----------------------------------------------------------------------------
// ���� ���ϴ� Ÿ��/��������üũ �����췯
//-----------------------------------------------------------------------------
//	Server Status Check
HTvoid CHTIntroManager::HT_vUpdate_ServerConnectCheck()
{
	//	������ ���� ���� ��
	if( g_pNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
	{
		//	���� ������ �� ����ó�� ������ ������� ��
		if( !m_bZoneServerConnected_ForIntro )
		{
			//	������ Ŀ��Ʈ Ȯ��
			m_bZoneServerConnected_ForIntro = HT_TRUE;
			//	[��ǥ] �������� �̵�
			this->HT_vCSP_Request_MOVE_ZONE_SERVER( 0x01 );
		}
		//	ĳ���� ����Ʈ �� ���ΰ��Ӱ� ������� ��
		if( !m_bZoneServerConnected_ForMainGame )
		{
			m_bZoneServerConnected_ForMainGame = HT_TRUE;
			//	[�ش�]	�������� �̵�
			this->HT_vCSP_Request_MOVE_ZONE_SERVER( 0x02 );
		}
	}
	//	������ ���� ���� ��
	else if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
	{
		//	LoginFaild DisConnect Setting
		if( m_bZoneServerDisConnected_ForLoginFaild )
		{
            m_bZoneServerDisConnected_ForLoginFaild = HT_FALSE;
			m_bZoneServerConnected_ForIntro = HT_FALSE;
		}

		//	DisConnect ���� ������ ��
		if( m_bZoneServerDisConnected_ForMainGame )
		{
			m_bZoneServerDisConnected_ForMainGame = HT_FALSE;
			//	������ �� ����
			g_pNetWorkMgr->Connect( g_strZoneServerIP, g_iZoneServerPort );
			//	���ΰ��� ���� ��������
			m_bZoneServerConnected_ForMainGame = HT_FALSE;
		}
	}
}
//	Show Window
HTvoid CHTIntroManager::HT_vUpdate_ShowWindow()
{
	if( m_iShowWinNo == 0 )
		return;

	//HTdword dwPassTime = timeGetTime();
	////	About Show window
	//if( dwPassTime > m_dwShowWinStartTime+m_dwShowWinDelayTime )
	//{
	//	g_cUIManager->HT_ShowWindow( m_iShowWinNo );
	//	m_iShowWinNo = 0;
	//}

	//	ī�޶� �̵��� ���������� ����
	if( g_bCameraMove == HT_FALSE )
	{
		g_cUIManager->HT_ShowWindow( m_iShowWinNo );
		
		//	Foucs �����ֱ�
		if( m_iShowWinNo == _DIALOG_LOGINBOX )
		{
			// �α��� ���������� üũ�Ͽ� �α��� �����͹ڽ��� ������ ��� �����ش�.
			if( g_cIntroManager->m_bIntro_SaveID )
			{
				g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_LOGINBOX, 4, "");
				g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_LOGINBOX, 4 );
			}
			else
			{
				g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_LOGINBOX, 3, "");
				g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_LOGINBOX, 4, "");
				g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_LOGINBOX, 3 );
			}
		}
		else if( m_iShowWinNo == _DIALOG_CHARACTERCREATE )
		{
			g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_CHARACTERCREATE, 3, "");
			g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_CHARACTERCREATE, 3 );
		}
		else if( m_iShowWinNo == _DIALOG_INPUTJUMINNO )
		{
			// �α��� �����͹ڽ��� ������ ��� �����ش�.
			g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_INPUTJUMINNO, 3, "");
			g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_INPUTJUMINNO, 4, "");
            g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_INPUTJUMINNO, 3 );
		}

		m_iShowWinNo = 0;
	}
}
//	�޽��� �پ� �ִ� �ð�üũ
HTvoid CHTIntroManager::HT_vUpdate_MsgDisplayTimeCheck()
{
	if( !m_bShowMsg )
		return;

	HTdword dwPassTime = timeGetTime();
	if( dwPassTime >= m_dwShowMsgTime + m_dwShowMsgStartTime )
	{
		m_strMeg.HT_hrCleanUp();
		m_bShowMsg = HT_FALSE;
	}
}
//	Login Delay Time
HTvoid CHTIntroManager::HT_vUpdate_LoginDelay()
{
	if( !m_bLoginDelay )
		return;

	HTdword dwPassTime = timeGetTime();
	if( dwPassTime >= m_dwLoginStartTime+1000 )
	{
		//	Move Camera
		if( g_byReStartCode == 0 )
		{
			g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_LINEMOVE, g_fCameraPos[HT_INTRO_CAMERA_SERVER][0], 1, 0.01f );
			g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_LINEMOVE, g_fCameraPos[HT_INTRO_CAMERA_SERVER][1], 1, 0.01f);
		}

		//	Delete Logo Window
		g_cUIManager->HT_HideWindow( _DIALOG_LOGINBOX );

		//	Show Window
		if( g_byReStartCode == 0 )
            this->HT_vIntro_SetShowWindow( _DIALOG_SERVERSELECT, 2500 );
		g_iConnectServerGroupIndex = 0;
		//	ServerSelect No
		m_iServerSelectNo = -1;

		//	Set Position Server Select Mob
		//g_pEngineHandler->HT_hrMoveObject( m_iMobForIntro[1], HTvector3( 1276.0f, 92.5f, 635.0f ) );
		//g_pEngineHandler->HT_hrScaleObject( m_iMobForIntro[1], HTvector3( 0.15f, 0.15f, 0.15f ) );
		//g_pEngineHandler->HT_hrStartAnimation(  m_iMobForIntro[1], 2458, HT_ANISTATE_STD, -1 );

		m_bLoginDelay= HT_FALSE;
	}
}


//	�Է� �޼��� ó��
//	Login Box
void CHTIntroManager::HT_hrIntro_InputCheckForLogin(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button �� ��� ������
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Cancel
		if( iTargetID == 1 )
		{
			//	Click Sound
			g_pEngineHandler->HT_hrPlaySound( 33523, 1 );
			//	Init Text
			g_cIntroManager->m_strID.HT_hrCleanUp();
			g_cIntroManager->m_strPassword.HT_hrCleanUp();
			//	_USER_MESSAGE_EXIT ����
			g_cIntroManager->m_bIntro_User_message_Exit = HT_TRUE;
		}
		//	OK
		else if( iTargetID == 2 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_LOGINBOX ) )
			{
				//	Click Sound
				g_pEngineHandler->HT_hrPlaySound( 33523, 1 );
				//	Set ID/PW
				g_cIntroManager->m_strID = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
				g_cIntroManager->m_strPassword = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 4 );
				//	�α��� ������ �������� ������ �����ϹǷ� ���⼭ �α��� �ҷ��ش�.
				g_cIntroManager->HT_vCSP_Request_LOGIN();
				//	Save ID
				if( g_cIntroManager->m_bIntro_SaveID )
                    g_cIntroManager->HT_vIntro_SaveID();
			}
		}
		else if( iTargetID == 5 )
		{
			//	Save ID
			if( g_cIntroManager->m_bIntro_SaveID )
			{
				g_cIntroManager->m_bIntro_SaveID = HT_FALSE;
                g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_LOGINBOX, 6, HT_FALSE );
				//	���̺�� ������ �����
                DeleteFile( "./system/SaveID.bin" );
			}
			else
			{
				g_cIntroManager->m_bIntro_SaveID = HT_TRUE;
				g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_LOGINBOX, 6, HT_TRUE );
				//	Save ID
				g_cIntroManager->HT_vIntro_SaveID();
			}
		}
	}
}
//	Server Select
void CHTIntroManager::HT_hrIntro_InputCheckForServerSelect(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Msg Button �� ��� ������
		//	Cancel
		if( iTargetID == 1 )
		{
			if( g_cIntroManager->m_iLoadCharDataSequence == -1 )
			{
				g_pEngineHandler->HT_hrPlaySound( 33523, 1 );	// Click Sound
				g_cIntroManager->m_bErrorCheckSw = HT_FALSE;
				g_cIntroManager->HT_vCSP_Request_CHAR_LOGOUT();
				g_cIntroManager->m_strID = g_cIntroManager->m_strSaveID.HT_szGetString();
				//	IME String Init �ϴ� �ӽ÷� �̷��� �صΰ� ���߿� �ٽ� ��������
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
				g_cImeMgr.InputString();
			}
		}
		//	OK
		else if( iTargetID == 2 )
		{
			if( g_cIntroManager->m_iLoadCharDataSequence == -1 )
			{
				//	 ���� ������ ����
				if( g_cUIManager->HT_isShowWindow( _DIALOG_SERVERSELECT ) )
					g_cIntroManager->HT_vEnter_FirstServer();
			}
		}
		//	Server No
		else if( iTargetID>=3 && iTargetID<3+g_iWorldNum )
		{
			g_iConnectServerGroupIndex = iTargetID-3;
			//	ServerSelect No
			if( g_cIntroManager->m_iServerSelectNo == g_iConnectServerGroupIndex )
			{
				//	 ���� ������ ����
				g_cIntroManager->HT_vEnter_FirstServer();
			}
			else
			{
				g_cIntroManager->m_iServerSelectNo = g_iConnectServerGroupIndex;
				//	Set Color
				for( HTint i=0 ; i<g_iWorldNum ; i++)
				{
					g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_SERVERSELECT, 3+i, HT_COLOR(1.0f,1.0f,1.0f,1.0f) );
				}
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_SERVERSELECT, 3+g_iConnectServerGroupIndex, HT_COLOR(1.0f,1.0f,0.0f,1.0f) );
			}
		}
	}
}
//	Character Info
void CHTIntroManager::HT_hrIntro_InputCheckForCharInfo(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button �� ��� ������
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	���� ���ٶ� ���� ���� �����찡 �˾��Ǿ� �մٸ� �����ش�.
		if( g_cUIManager->HT_isShowWindow( _DIALOG_3MANDARAVILLAGE ) )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_3MANDARAVILLAGE );
			return;
		}

		//	Cancel
		if( iTargetID == 1 )
		{
			//	ĳ���� ����Ʈ ��üȭ��
			g_cIntroManager->HT_hrCharSelect();
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	���� ĳ���� ��ŵ
			if( g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.byGMStatus == 0x01 )
			{
				// �� ĳ���� ���� �����Դϴ�.
				CHTString szMessage;
				HT_g_Script_SetMessage( eMsgCommonNoLoginChar, &szMessage, _T("") );
				g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				return;
			}

			HTbool	bMandraBoxSw = HT_FALSE;
			//	��ġ�� ������ ���ٶ� �����̸�
			if( !g_bDevelopingMode )
			{
				if( g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA1ST ||
					g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA2ND ||
					g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA3TH )
				{
					//	���ٶ� ������ ������ ���õǾ� �ִٸ�
					if( g_poWebLogIn->HT_iGetCCUserNum(g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1) != -1 || 
						g_poWebLogIn->HT_iGetCCUserNum(g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1) != -1  )
					{
						bMandraBoxSw = HT_TRUE;
					}
				}
			}

			if( bMandraBoxSw == HT_TRUE )
			{
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_CHARACTERINFO1, iPosX, iPosY );
				g_cUIManager->HT_ShowWindow( _DIALOG_3MANDARAVILLAGE );
				g_cUIManager->HT_MoveWindow( _DIALOG_3MANDARAVILLAGE, iPosX, iPosY+410 );
			}
			else
			{
				//	ĳ���� ����Ÿ �������� ����
				CopyMemory(&g_oMainCharacterInfo, &g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo, sizeof(S_CHARACTER_LIST));
				//	�����ڵ� �������ֱ�
				HTint iTribe;
				HT_ConvertTribeS2C( g_oMainCharacterInfo.snTribe, iTribe );
				g_oMainCharacterInfo.snTribe = iTribe;

				if( g_cIntroManager->HT_bIsCharInMandara() )
					g_wResentZoneServerID = ZONE_MANDARA1ST;

				g_iZoneServerPort		= g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
				g_strZoneServerIP	    = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;

				//	������ ����
				g_cIntroManager->m_byConnectType = 0x01;
				g_cIntroManager->HT_vCSP_Request_CHAR_SELECT();
				//	Stop Mob Animation
				g_cIntroManager->m_bStopMobAnimationSw = HT_TRUE;
			}
			return;
		}
		//	Delete Character
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_CHARACTERINFO1 );
			//	Show Top Window
			g_cIntroManager->HT_vIntro_SetShowWindow( _DIALOG_INPUTJUMINNO, 1000 );
			//	IME String Init
			g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
			g_cImeMgr.InputString();
			//	Set Focus
			if( g_iInationalType == INATIONALTYPE_KOREA )
                g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_INPUTJUMINNO, 3 );
			else
				g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_INPUTJUMINNO, 4 );

			//	�����Է� ������ �ڽ� �����
			g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_INPUTJUMINNO, 4, _T("CleanBox") );
			//	IME String Init
			g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
			g_cImeMgr.InputString();
			
			g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_DELETECHAR][0], 1, 0.95f);
			g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_DELETECHAR][1], 1, 0.95f);
		}
	}
}
//	Character Create
void CHTIntroManager::HT_hrIntro_InputCheckForCharCreate(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button �� ��� ������
	if( iTarget == UI_TARGET_BUTTON )
	{
        //	Cancel
		if( iTargetID == 1 )
		{
			//	���� ĳ���Ͱ� ������ ĳ���� ����Ʈ ȭ������ �Ѿ
			if( g_cIntroManager->m_iCharNum != 0 )
			{
				g_cIntroManager->HT_hrCharSelect();
			}
			//	ĳ���Ͱ� ������ �����޽����� �پ���
			else
			{
				//	�޽��� ����
				CHTString szMessage;
				HT_g_Script_SetMessage( eMsgCharacListNotExist, &szMessage, _T("") );
				g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			}
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	ĳ�������� ����ġ ���Ѵܾ �O�Ƴ�
			g_cIntroManager->m_strNewCharacterName = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHARACTERCREATE, 3 );
			//	Request Create Character
			g_cIntroManager->HT_vCSP_Request_CHAR_CREATE();
		}
		//	���� ���� Left
		else if( iTargetID == 3 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharSelect(_USER_MESSAGE_TRIBELEFT);
		}
		//	���� ���� Right
		else if( iTargetID == 4 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharSelect(_USER_MESSAGE_TRIBERIGHT);
		}
		//	�� ����
		else if( iTargetID==5 || iTargetID==6 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharFace( iTargetID );
		}
		//	�Ӹ� ����
		else if( iTargetID==7 || iTargetID==8 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharHair( iTargetID );
		}
		//	íũ�� ����Ʈ
		else if( iTargetID==9 || iTargetID==10 || iTargetID==11 || iTargetID==12 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharServiceChakra( iTargetID );
		}
		//	íũ�� ����Ʈ �ʱ�ȭ
		else if( iTargetID==13 )
		{
			g_cIntroManager->HT_hrChakraInit();
		}
		////	�ڹ� ���
		//else if( iTargetID==30 )
		//{
		//	g_pEngineHandler->HT_hrChangeAnimation( g_cIntroManager->m_nNewCharacterModelID, g_cIntroManager->m_nNewCharacterTribe, HT_ANISTATE_IDL, 1 );
		//	//g_pEngineHandler->HT_hrChangeAnimation( g_cIntroManager->m_nNewCharacterModelID, g_cIntroManager->m_nNewCharacterTribe, HT_ANISTATE_IDL, 1, g_cIntroManager->m_nNewCharacterHair, g_cIntroManager->m_nNewCharacterFace );
		//}
	}
}
//	JuminNo
void CHTIntroManager::HT_hrIntro_InputCheckForJuminNo(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button �� ��� ������
	if( iTarget == UI_TARGET_BUTTON )
	{
        //	Cancel
		if( iTargetID == 1 )
		{
			//	ĳ���� ����Ʈ ��üȭ��
			g_cIntroManager->HT_hrCharSelect();
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	���� ĳ���� �ֹ� ��ȣ_���ڸ�
			if( g_iInationalType == INATIONALTYPE_KOREA )
			{
				g_cIntroManager->m_strCharJoominNoFront = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_INPUTJUMINNO, 3 );
			}
			else
			{
				g_cIntroManager->m_strCharJoominNoFront.HT_hrCleanUp();
			}
			//	���� ĳ���� �ֹ� ��ȣ_���ڸ�
			g_cIntroManager->m_strCharJoominNoBack = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_INPUTJUMINNO, 4 );
			//	ĳ���� ����
			g_cIntroManager->HT_vCSP_Request_CHAR_REMOVE();
		}
	}
}
//	Top Menu
void CHTIntroManager::HT_hrIntro_InputCheckForTopMenu(int iAction, int iTarget, int iTargetID)
{
	//	Create Character
	if( iTargetID == 1 )
	{
		if( g_cIntroManager->m_iCharNum < 3 )
		{
            g_cIntroManager->HT_hrCharNew();
		}
		else
		{
			//	�޽��� ����
			CHTString szMessage;
			HT_g_Script_SetMessage( eMsgCharacListCannotCreate, &szMessage );
			g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
		}
	}
	//	Select Character
	else if( iTargetID == 2 )
	{
		//	���� ĳ���Ͱ� ������ ĳ���� ����Ʈ ȭ������ �Ѿ
		if( g_cIntroManager->m_iCharNum != 0 )
		{
			g_cIntroManager->HT_hrCharSelect();
		}
		//	ĳ���Ͱ� ������ �����޽����� �پ���
		else
		{
			//	�޽��� ����
			CHTString szMessage;
			HT_g_Script_SetMessage( eMsgCharacListNotExist, &szMessage, _T("") );
			g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
		}
	}
	//	Select Server
	else if( iTargetID == 3 )
	{
		//	ĳ���� ����Ʈ �ܿ��� _USER_MESSAGE_EXIT ��ư�� Ŭ���ߴ��� �ľ�
		g_cIntroManager->m_bIntro_User_message_Exit = HT_TRUE;
	}
}
//	3 Mandara Village
void CHTIntroManager::HT_hrIntro_InputCheckFor3MandaraVillage(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button �� ��� ������
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Mandara1, Mandara2, Mandara3
		if( iTargetID == 1 )		g_wResentZoneServerID = ZONE_MANDARA1ST;
		else if( iTargetID == 2 )	g_wResentZoneServerID = ZONE_MANDARA2ND;
		else if( iTargetID == 3 )	g_wResentZoneServerID = ZONE_MANDARA3TH;
		else return;

		HTint iConnectCharNum = g_cIntroManager->HT_iIntro_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, g_wResentZoneServerID-1 );
		if( g_bDevelopingMode )		iConnectCharNum = 0;
		if( iConnectCharNum > CONNECTNUM_CLIENTLIMIT && g_oMainCharacterInfo.snTribe != 9)
		{	
			//	ĳ���� ����Ʈ ��üȭ��
			g_cIntroManager->HT_hrCharSelect();
			CHTString strMessage;
			// �������� �����ο��� �ʰ��Ǿ����ϴ�. ����� �ٽ� ������ �ֽʽÿ�
			g_cIntroManager->HT_hrSetMessage( eMsgLogInOverMember, &strMessage );
			g_cIntroManager->HT_vIntro_SetShowMessage( strMessage, 5000 );
		}
		else
		{
			//	ĳ���� ����Ÿ �������� ����
			CopyMemory(&g_oMainCharacterInfo, &g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo, sizeof(S_CHARACTER_LIST));
			//	�����ڵ� �������ֱ�
			HTint iTribe;
			HT_ConvertTribeS2C( g_oMainCharacterInfo.snTribe, iTribe );
			g_oMainCharacterInfo.snTribe = iTribe;
			//	Ŀ�ؼ�Ÿ��, ĳ�����̸�, ���� ��NO, IP, Port �ٽ� ��� �ϹǷ� �������� ����
			g_iZoneServerPort		= g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
			g_strZoneServerIP	    = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
			//	������ ����
			g_cIntroManager->m_byConnectType = 0x01;
			g_cIntroManager->HT_vCSP_Request_CHAR_SELECT();
		}

		//	Hide Window
		g_cUIManager->HT_HideWindow( _DIALOG_3MANDARAVILLAGE );
	}
}


//	Save ID
HTvoid CHTIntroManager::HT_vIntro_SaveID()
{
	CHTString strTempID = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
	if( strTempID.HT_bIsEmpty() )
		return;

	//	�����ִ����� ����
	DeleteFile( "./system/SaveID.bin" );

	// Encoding : XOR�� ����ؼ� 0�� 1�� 1�� 0���� �ٲٴ� �ٺ����� ���ڵ��� ����Ѵ�. ���簡 ������ -_-;
	CHTFile oFile;
	if ( oFile.HT_bOpen( "./system/SaveID.bin", HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
	{
		HTint iIDCount = strTempID.HT_nGetSize();
		char szTempID[ACCOUNTNAME_LENGTH+1];
		strncpy( szTempID, strTempID.HT_szGetString(), iIDCount+1 );
		HTtchar szSaveIDBin[ACCOUNTNAME_LENGTH+1];
		ZeroMemory( szSaveIDBin, ACCOUNTNAME_LENGTH+1 );
		for ( HTint i=0 ; i<iIDCount; ++i )
			szSaveIDBin[i] = szTempID[i] ^ 0xFF;
		oFile.HT_bWrite( szSaveIDBin, ACCOUNTNAME_LENGTH+1 );
		oFile.HT_vClose();
	}
}
//	Load Id
HTvoid CHTIntroManager::HT_vIntro_LoadID()
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( "./system/SaveID.bin", HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) )
	{
		HTtchar szID[ACCOUNTNAME_LENGTH+1];
        HTtchar szSaveIDBin[ACCOUNTNAME_LENGTH+1];
		ZeroMemory( szID, ACCOUNTNAME_LENGTH+1 );
		ZeroMemory( szSaveIDBin, ACCOUNTNAME_LENGTH+1 );

		oFile.HT_bRead( szSaveIDBin, ACCOUNTNAME_LENGTH+1 );
		HTint iLangth = strlen( szSaveIDBin );
		if( iLangth > ACCOUNTNAME_LENGTH )
			iLangth = ACCOUNTNAME_LENGTH;
		if( iLangth>0 )
		{
			for ( HTint i=0 ; i<iLangth ; ++i ) 
				szID[i] = szSaveIDBin[i] ^ 0xFF;
			oFile.HT_vClose();

			CHTString strID(szID);
			g_cIntroManager->m_bIntro_SaveID = HT_TRUE;
			g_cUIManager->HT_SetTextEditBoxControl( _DIALOG_LOGINBOX, 3, strID );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_LOGINBOX, 6, HT_TRUE );
		}
		oFile.HT_vClose();
	}
}

//	Set Show Window
HTvoid CHTIntroManager::HT_vIntro_SetShowWindow( HTint iWinNo, HTdword dwDelayTime )
{
	//	About Show window
	m_iShowWinNo = iWinNo;
	m_dwShowWinStartTime = timeGetTime();
	m_dwShowWinDelayTime = dwDelayTime;
}
//	Set Message
HTvoid CHTIntroManager::HT_vIntro_SetShowMessage( CHTString strMsg, HTdword dwDelayTime )
{
	//	About Message
	m_strMeg = strMsg.HT_szGetString();
	m_bShowMsg = HT_TRUE;
	m_dwShowMsgTime = dwDelayTime;
	m_dwShowMsgStartTime = timeGetTime();
}
//	Set Hide Message
HTvoid CHTIntroManager::HT_vIntro_SetHideMessage()
{
	m_bShowMsg = HT_FALSE;

	m_bErrorCheckSw = HT_FALSE;
}

//-----------------------------------------------------------------------------
// HTvoid						HT_vAnimationCheck()
// D : �ִϸ��̼� üũ
//-----------------------------------------------------------------------------
HTvoid
CHTIntroManager::HT_vAnimationCheck()
{
	//	Stop Mob Animation
	if( m_bStopMobAnimationSw )
		return;

	for( HTint i=0 ; i<3 ; i++ )
	{
		if( m_nExistCharacterModelID[i] != -1 )
		{
			if( m_oSeverChar[i].bSw )
			{
				HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_nExistCharacterModelID[i] );
				if( sAnmState == HT_AS_STOP )
				{
					// ���� ������ Ŭ���̾�Ʈ ���� �ڵ�� ��ȯ
					HTint iTribe;
					HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );

					// ���⸦ ��������� �����ϴ� �ڼ��� �ƴ϶� �ùٸ� �ڼ��� ���ִ� ������ �ϱ� ���ؼ�
					g_pEngineHandler->HT_hrChangeAnimation( m_nExistCharacterModelID[i], iTribe, HT_ANISTATE_STD, -1, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], 0.0f, m_arrExistCharWeaponItem[i] );
				}
			}
		}
	}

	//if( m_nNewCharacterModelID != -1 )
	//{
	//	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_nNewCharacterModelID );
	//	if( sAnmState == HT_AS_STOP )
	//	{
	//		g_pEngineHandler->HT_hrChangeAnimation( m_nNewCharacterModelID, m_nNewCharacterTribe, HT_ANISTATE_STD, -1, m_nNewCharacterFace, m_nNewCharacterHair );
	//	}
	//}

	for( i=0 ; i<2 ; i++ )
	{
		if( m_iMobForIntro[i] > 0 )
		{
			HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iMobForIntro[i] );
			if( sAnmState == HT_AS_STOP )
			{
				g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[i], INTRO_GATEMOB1, HT_ANISTATE_STD, -1 );
			}
		}
	}

	//	Change Ani
	//	�α��� ������ �ð����� �۵����ϰ� ��
	if( m_bLoginDelay )
		return;
	DWORD dwPassTime = timeGetTime();
	HTint iRnd = rand()%5;
	for( i=0 ; i<2 ; i++ )
	{
		if( m_iMobForIntro[i] > 0 )
		{
			if( dwPassTime > m_dwChangeAniMobTime[i]+4000+(i*500) )
			{
				m_dwChangeAniMobTime[i] = dwPassTime;
				if( iRnd == 0 )			g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[i], INTRO_GATEMOB1, HT_ANISTATE_RUN, 2 );
				else if( iRnd == 1 )	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[i], INTRO_GATEMOB1, HT_ANISTATE_ATK_2, 1 );
				else if( iRnd == 2 )	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[i], INTRO_GATEMOB1, HT_ANISTATE_IDL, 1 );
				else if( iRnd == 3 )	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[i], INTRO_GATEMOB1, HT_ANISTATE_WLK, 1 );
				else if( iRnd == 4 )	g_pEngineHandler->HT_hrChangeMonsterAttackAnimation( m_iMobForIntro[i], INTRO_GATEMOB1, 3612, 1 );
			}
		}
	}
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrCameraUpdate( HTfloat fElapsedTime )
// D : ī�޶� ��Ʈ��
// R : HT_OK/HT_FAIL
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrCameraUpdate( HTfloat fElapsedTime )
{
	//	ī�޶� ����
	g_cCamera.HT_vCameraUpdate( HTvector3( 0,0,0 ), HT_PI, fElapsedTime );

	return HT_OK;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrAutoLoginUpdate()
// D : �ڵ� �α��� üũ
//-----------------------------------------------------------------------------
HTvoid
CHTIntroManager::HT_vAutoLoginUpdate()
{
	if( g_byReStartCode == 0 )
		return;

    //	�α��� �� ó��
	if( m_iIntroStatus == GAMESEQUENCE_INTRO_LOADINTROMAP )
	{
		// ���� ���� �ܰ�
		//m_iIntroStatus = GAMESEQUENCE_INTRO_LOGSERVERCONNECT;
	}
	//	���� ����Ʈ�� ó��
	if( m_iIntroStatus == GAMESEQUENCE_INTRO_INTROPLAY )
	{
		if( g_byReStartCode == 2 &&
			m_bIntro_RestartConnect == HT_FALSE )
		{
			//	�����ӽÿ� �������� ����ġ
			m_bIntro_RestartConnect = HT_TRUE;
			//	������ ������ �����׷��� �̿��Ͽ� ������ �����̸��� �˾ƿ´�.
			g_strSelectServerName = g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldName;

			g_pNetWorkMgr->Connect( g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldIP, g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].snWorldPort );
			CHTString szMessage;
			this->HT_hrSetMessage( eMsgLogInReqGameServer, &szMessage );
		}
	}
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrCharSelect()
// D : 3Dȭ������ ��ȯ�ϰ� [ĳ���� ����],[����]���̾˷α׸� �׸���.
// R : HT_OK/HT_FAIL
//-----------------------------------------------------------------------------
HTvoid
CHTIntroManager::HT_vExistCharCreate()
{
	for (HTint i=0; i<3; i++)
	{
		if( m_oSeverChar[i].bSw == HT_TRUE )
		{
			this->HT_hrExistCharacterCreate( i );

			m_arrExistCharWearItem[i] = -1;
			m_arrExistCharWeaponItem[i] = -1;

			// ���⸦ ��������� �����ϴ� �ڼ��� �ƴ϶� �ùٸ� �ڼ��� ���ִ� ������ �ϱ� ���ؼ�
			//	�����ڵ� �������ֱ�
			HTint iTribe;
			HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );
            
			HTint iNormaIndex, iLeftIndex;
			for (HTint j=0 ; j<7 ; j++)
			{
				iNormaIndex = m_oSeverChar[i].sCharInfo.Equip[j].snIndex;
				iLeftIndex = 0;
				//	�޼� �ܰ��϶��� üũ
				if( j==3 )
				{
					if( g_pEngineHandler->HT_bIsShortSword( iNormaIndex ) )
					{
						iLeftIndex = iNormaIndex;
						iNormaIndex = 0;
					}
				}

				this->HT_hrExistCharacterEquipItem( iTribe, i, iNormaIndex, iLeftIndex );
			}

			g_pEngineHandler->HT_hrChangeAnimation( m_nExistCharacterModelID[i], iTribe, 
				HT_ANISTATE_STD, -1, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], 0.0f, m_arrExistCharWeaponItem[i] );
		}
	}

	// ������ ���� ĳ���Ͱ� ������ ĳ���� ����ȭ������, ������ ĳ���� ����ȭ������
	if (m_iCharNum)		this->HT_hrCharSelect();
	else				this->HT_hrCharNew();
}
HTRESULT
CHTIntroManager::HT_hrCharSelect()
{
	m_bCharSelectZoomInSw = HT_FALSE;

	//	��ĳ���Ͱ� �����Ǿ� ������ ������ �Ѵ�.
	if( m_nNewCharacterModelID != -1 )
	{
		g_pEngineHandler->HT_vDestroyCharacter( m_nNewCharacterModelID, 3 );
		m_nNewCharacterModelID = -1;
	}

	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_SELECTCAHR][0], 1, 0.95f);
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_SELECTCAHR][1], 1, 0.95f);

	//	Show Window
	g_cUIManager->HT_HideWindow( _DIALOG_CHARACTERINFO1 );
	//	Hide Window
	g_cUIManager->HT_HideWindow( _DIALOG_CHARACTERCREATE );
	//	Hide Window
	g_cUIManager->HT_HideWindow( _DIALOG_INPUTJUMINNO );

	m_bCharDeleteSw = HT_FALSE;

	return HT_OK;
}

HTvoid
CHTIntroManager::HT_vCharSelect_SetInfo()
{
	CHTString strString;
	CHTString strJob;

	//�̸� Label Level Name
	strString.HT_szFormat( "%s [%d]", m_oSeverChar[m_nSelectedCharNo].sCharInfo.szCharName, m_oSeverChar[m_nSelectedCharNo].sCharInfo.byLevel );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 11, strString.HT_szGetString() );
	//�ֽ� Label My God
	if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_BRAHMA )
		this->HT_hrSetMessage( eMsgCommonTrimuritiBrahma, &strString);
	else if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_VISHNU )
		this->HT_hrSetMessage( eMsgCommonTrimuritiVishunu, &strString);
	else if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_SIVA )																	//strTrimuriti = _T("�ù�");
		this->HT_hrSetMessage( eMsgCommonTrimuritiSiva, &strString);
	else
		this->HT_hrSetMessage( eMsgCommonNone, &strString);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 13, strString.HT_szGetString() );
	//	��������ũ��
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraMuscle );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 19, strString.HT_szGetString() );
	//	��������ũ��
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraHeart );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 21, strString.HT_szGetString() );
	//	�Ű�����ũ��
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraNerve );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 20, strString.HT_szGetString() );
	//	��������ũ��
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraSoul );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 22, strString.HT_szGetString() );
	//	��ġ�� ���� 10 Label Connect Position
	switch( m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone )
	{
		case 1 : // ���ٶ� 1������
			//HT_vSetMessage( eMsgCommonZoneMandara_1, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;
		case 18 :
			//HT_vSetMessage( eMsgCommonZoneMandara_2, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;
		case 19 :
			//HT_vSetMessage( eMsgCommonZoneMandara_3, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;

		case 2 : // ���ٶ� 2������
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_2, &strString ); break;
		case 3 : // ���ٶ� ����1��
		case 4 : // ���ٶ� ����2��
			this->HT_hrSetMessage( eMsgCommonZoneMandaraDungeon, &strString ); break;
		case 5 : // ���߶� ����1��
		case 6 : // ���߶� ����2��
			this->HT_hrSetMessage( eMsgCommonZoneShambalaDungeon, &strString ); break;
		case 7 : // ���� 1������
		case 8 : // ���� 2������
		case 9 : // ���� 3������
			this->HT_hrSetMessage( eMsgCommonZoneJina, &strString ); break;
		case 10 : // ���� 4������(��縶)
			this->HT_hrSetMessage( eMsgCommonZoneTrimuriti, &strString ); break;
		case 11 : // ���� 5������(í������)
			this->HT_hrSetMessage( eMsgCommonZoneChatulangga, &strString ); break;
		case 12 : // �ϵμ�����
			this->HT_hrSetMessage( eMsgCommonZoneBookDooTomb, &strString ); break;
		case 16 : // �����
			this->HT_hrSetMessage( eMsgCommonZoneArenaDurga, &strString ); break;
		case 17 : // �����
			this->HT_hrSetMessage( eMsgCommonZoneBiryuCastle, &strString ); break;
		case 20 :
			this->HT_hrSetMessage( eMsgCommonZoneAnakaKruma, &strString ); break;
		default: strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone ); break;
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 24, strString.HT_szGetString() );
}

HTRESULT
CHTIntroManager::HT_hrCharNew()
{
	//	Show Window
	g_cUIManager->HT_HideWindow( _DIALOG_CHARACTERINFO1 );
	//	Hide Window
	g_cUIManager->HT_HideWindow( _DIALOG_INPUTJUMINNO );

	//	Show Top Window
	g_cIntroManager->HT_vIntro_SetShowWindow( _DIALOG_CHARACTERCREATE, 1000 );

	//	��ĳ���� �����̵� �ʱ�ȭ
	m_nNewCharacterFace		= 0x01;
	m_nNewCharacterHair		= 0x01;
	m_nNewCharacterTribe	= 0;

	HT_hrNewCharacterCreate( g_byCharacterTribe[m_nNewCharacterTribe] );

	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_NEWCAHR][0], 1, 0.95f);
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_NEWCAHR][1], 1, 0.95f);

	m_byCharCreate_ServiceChakraPoint= CHOOSE_CHAKRA_POINT;
	m_byCharCreate_ChakraMuscle = 0;
  	m_byCharCreate_ChakraNerve = 0;
  	m_byCharCreate_ChakraHeart = 0;
	m_byCharCreate_ChakraSoul = 0; 
	//	ĳ���� ���� ����, ��
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace );

	//	�̸����� Display�� String
	m_strIntroMessage.HT_hrCleanUp();
	m_strIntroMessage_Display.HT_hrCleanUp();

	//	IME String Init
	g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	g_cImeMgr.InputString();

	return HT_OK;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrSelectCharCreate()
// D : �ʱ� �����Ҽ� �ִ� ĳ���͵��� �����Ѵ�.
// R : HT_OK/HT_FAIL
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrNewCharacterCreate( BYTE byCharTribe )
{
	if( m_nNewCharacterModelID != -1 )
	{
		g_pEngineHandler->HT_vDestroyCharacter( m_nNewCharacterModelID, 4 );
		m_nNewCharacterModelID = -1;
	}

	HTvector3 vecPos = HTvector3( g_fCharacter_New[0], g_fCharacter_New[1], g_fCharacter_New[2] );
	m_nNewCharacterModelID = g_pEngineHandler->HT_iCreateCharacter( byCharTribe, vecPos, 1, 1 );
	g_pEngineHandler->HT_hrStartAnimation( m_nNewCharacterModelID, byCharTribe, HT_ANISTATE_STD, -1 );
	g_pEngineHandler->HT_hrRotateObject( m_nNewCharacterModelID, 2.8f );
	m_fObjectHeight = g_pEngineHandler->HT_fGetObjHeight( m_nNewCharacterModelID );

	//	�������� ����Ʈ
	static HTint idFx = -1;
	if ( idFx > 0 ) g_pEngineHandler->HT_hrStopSFX( idFx );
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_INTROCHARACTERSELECT, m_nNewCharacterModelID, HT_FALSE );
	
	return HT_OK;
}
HTRESULT
CHTIntroManager::HT_hrNewCharacterChangeFace()
{
	g_pEngineHandler->HT_hrChangeHead( m_nNewCharacterModelID, g_byCharacterTribe[m_nNewCharacterTribe], m_nNewCharacterHair, m_nNewCharacterFace );
	return HT_OK;
}

HTvoid
CHTIntroManager::HT_hrExistCharacterCreate( HTint nIndex )
{
	if( m_nExistCharacterModelID[nIndex] != -1 )
	{
		g_pEngineHandler->HT_vDestroyCharacter( m_nExistCharacterModelID[nIndex], 5 );
		m_nExistCharacterModelID[nIndex] = -1;
	}

	//	�����ڵ� �������ֱ�
	HTint iTribe;
	HT_ConvertTribeS2C( m_oSeverChar[nIndex].sCharInfo.snTribe, iTribe );

	HTvector3 vecPos = HTvector3( g_fCharacter_Exist[nIndex][0], g_fCharacter_Exist[nIndex][1], g_fCharacter_Exist[nIndex][2] );
	m_nExistCharacterModelID[nIndex] = g_pEngineHandler->HT_iCreateCharacter( iTribe, vecPos, m_oSeverChar[nIndex].sCharInfo.byHeadType, m_oSeverChar[nIndex].sCharInfo.byFaceType );
	g_pEngineHandler->HT_hrStartAnimation( m_nExistCharacterModelID[nIndex], iTribe, HT_ANISTATE_STD, -1 );
	g_pEngineHandler->HT_hrRotateObject( m_nExistCharacterModelID[nIndex], g_fCharacter_ExistAngle[nIndex] );
	m_nExistCharacterNumber++;
	m_oSeverChar[nIndex].fHight = g_pEngineHandler->HT_fGetObjHeight( m_nExistCharacterModelID[nIndex] );
}
HTvoid
CHTIntroManager::HT_hrExistCharacterEquipItem( HTint iTribe, HTint nCharIndex, DWORD dwItemIndex, DWORD dwLeftItemIndex  )
{
	//if( dwItemIndex == 0 )
	//	return;

	g_pEngineHandler->HT_hrEquipItem( m_nExistCharacterModelID[nCharIndex], iTribe, dwItemIndex, dwLeftItemIndex, m_oSeverChar[nCharIndex].sCharInfo.byFaceType );
        
	if ( HT_IS_ITEM_WEAR( dwItemIndex ) )
	{
		m_arrExistCharWearItem[nCharIndex]	= dwItemIndex;
	}
	else if ( HT_IS_ITEM_WEAPON( dwItemIndex ) )
	{
		m_arrExistCharWeaponItem[nCharIndex] = dwItemIndex;
	}
}

//-----------------------------------------------------------------------------
// Network �Լ�
// D : ��Ʈ��ũ �Լ���
// R : HT_void
//-----------------------------------------------------------------------------
//	�α���
HTvoid
CHTIntroManager::HT_vCSP_Request_LOGIN()
{
	//	���� ����϶�
	if( g_bDevelopingMode )
	{
		CHTString strPass;
		CHTString strLowerPass;
		//	�ڵ��α����� �ƴҶ��� ID/PW �������ش�.
		if( g_byReStartCode == 0 )
		{
			if( g_iInationalType == INATIONALTYPE_JAPEN )
				g_bDevelopingMode = HT_FALSE;

			g_strLoginID		= g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
			strPass				= g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 4 );
		}

		// by ��� 20050504 : ��� �н������ ��ҹ��ڸ� �����ϰ� �ȴ�. �ѱ��� ��� MD5 ���¸� ����ϰ�,
		if( g_iInationalType == INATIONALTYPE_KOREA )	strLowerPass = strPass;
		else							                strLowerPass = _tcslwr( (HTtchar*)strPass );
		// by ��� 20050504 : �ܱ��� ��쿡�� ���� ���� �״�� ����ϰ� �ȴ�.
		//if ( g_iInationalType == INATIONALTYPE_KOREA )
		{
			//strLowerPass = strPass;
			g_strLgoinPasswordMD5 = strLowerPass.HT_strGetMD5();
		}
		//else
		{
			//strLowerPass = _tcslwr( (HTtchar*)strPass );
			//	MD+��� ��ȯ
			HTchar	szChar[20];
			HTint iPassSize = strLowerPass.HT_nGetSize();
			strncpy( szChar, strLowerPass.HT_szGetString(), 20 );
			strLowerPass.HT_hrCleanUp();
			strLowerPass = _T("@");
			strLowerPass += szChar[0];
			strLowerPass += _T("^");
			for( HTint i=1 ; i<iPassSize ; i++ )
				strLowerPass += szChar[i];
			//HTchar	szPassword[36];
			//ZeroMemory( szPassword, 36 );
			//strncpy( szPassword, strLowerPass.HT_szGetString(), 36 );
			//strLowerPass = _tcslwr( (HTtchar*)szPassword );
			g_strLgoinPasswordMD5Plus = strLowerPass.HT_strGetMD5();
		}

		if (!g_poWebLogIn) MessageBox(NULL, "g_poWebLogIn Memory Create Fail", "g_poWebLogIn Memory Create Fail", MB_OK);
		g_poWebLogIn->HT_vSetWorldNum(g_iWorldNum);
		//	Set Log Event Value
		g_iLoginResultID = 0;
		//�α��� ����
		this->HT_vSCP_RESP_LOGIN();
		return;
	}
	else
	{
		//	�ڵ��α����� �ƴҶ��� ID/PW �������ش�.
		if( g_byReStartCode == 0 )
		{
			CHTString strLoginID = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
			if( g_strLoginID.HT_iStringCompare( strLoginID.HT_szGetString() ) == 0 )
			{
				//  ���� ���� ���� ���
				if( g_bReciveBillingServer == HT_FALSE )
				{
					CHTString szMessage;
					// ����� ������ �Ⱓ�� ����Ǿ����ϴ�.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
					return;
				}
			}
			else
			{
				//  ���� ���� ���� ���
				g_bReciveBillingServer = HT_TRUE;
			}
			g_strLoginID = strLoginID.HT_szGetString();
			m_strPassword =  g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 4 );
			CHTString strPass( m_strPassword );
			CHTString strLowerPass;

			// by ��� 20050504 : ��� �н������ ��ҹ��ڸ� �����ϰ� �ȴ�. �ѱ��� ��� MD5 ���¸� ����ϰ�,
			if( g_iInationalType == INATIONALTYPE_KOREA )	strLowerPass = strPass;
			else							                strLowerPass = _tcslwr( (HTtchar*)strPass );
			// by ��� 20050504 : �ܱ��� ��쿡�� ���� ���� �״�� ����ϰ� �ȴ�.
			//if ( g_iInationalType == INATIONALTYPE_KOREA )
			{
				//strLowerPass = strPass;
				g_strLgoinPasswordMD5 = strLowerPass.HT_strGetMD5();
			}
			//else
			{
				//strLowerPass = _tcslwr( (HTtchar*)strPass );
				//	MD+��� ��ȯ
				HTchar	szChar[20];
				HTint iPassSize = strLowerPass.HT_nGetSize();
				strncpy( szChar, strLowerPass.HT_szGetString(), 20 );
				strLowerPass.HT_hrCleanUp();
				strLowerPass = _T("@");
				strLowerPass += szChar[0];
				strLowerPass += _T("^");
				for( HTint i=1 ; i<iPassSize ; i++ )
					strLowerPass += szChar[i];
				//HTchar	szPassword[36];
				//ZeroMemory( szPassword, 36 );
				//strncpy( szPassword, strLowerPass.HT_szGetString(), 36 );
				//strLowerPass = _tcslwr( (HTtchar*)szPassword );
				g_strLgoinPasswordMD5Plus = strLowerPass.HT_strGetMD5();
			}
		}

		// �α��� ���̵�� �н������ �α��� ����
		if (g_poWebLogIn)
		{
			if( g_iInationalType == INATIONALTYPE_KOREA )
			{
				g_iLoginResultID = g_poWebLogIn->HT_iGetLogInIDCheck( g_strLoginID, g_strLgoinPasswordMD5.HT_szGetString(), g_gServerType);
			}
			else
			{
				g_iLoginResultID = g_poWebLogIn->HT_iGetLogInIDCheck( g_strLoginID, g_strLgoinPasswordMD5Plus.HT_szGetString(), g_gServerType);
			}
		}

		CHTString szMessage = _T(" ");

		// �α����� ������ ��
		HTchar		cFailCause[1024];
		ZeroMemory(cFailCause, sizeof(HTchar)*1024);

		if (g_poWebLogIn)
		{
			if (g_poWebLogIn->HT_bGetLogInEnable())
			{	
				// �޼��� ǥ��
				this->HT_hrSetMessage( eMsgLogInReqWeb, &szMessage );
				this->HT_vIntro_SetShowMessage( szMessage.HT_szGetString(), 5000 );
				// ������ ���� �� ���������ڼ� üũ
				if (!g_poWebLogIn->HT_bGetServerStatusCheck())
				{
					// ������ �ٿ�Ǿ� ������ ���� ǥ��
					if (g_poWebLogIn->HT_bGetServerDownCause(cFailCause)) 
					{
						this->HT_vIntro_SetShowMessage( cFailCause, 5000 );
					}
				}
				else
				{
					this->HT_vSCP_RESP_LOGIN();
				}
			}
			else											
			{
				CHTString strErrorCause;
				strErrorCause = _T("");
				HTRESULT hr = HT_FAIL;
				szMessage = _T(" ");
				// �α����� �Ұ����� �� �α����� �Ұ����� ���� ǥ��
				if( g_iInationalType == INATIONALTYPE_KOREA )
				{
					switch(g_iLoginResultID)
					{
						case 1001 : //	���̵� ����ġ
							this->HT_hrSetMessage( eMsgLogInInvalidUser, &szMessage);
							break;
						case 1002 : //	�н����� ����ġ
							this->HT_hrSetMessage( eMsgLogInPasswdMismatch, &szMessage);
							break;
						case 1003 : //	���Ӻ�
							this->HT_hrSetMessage( eMsgLogInBlockID, &szMessage);
							break;
						case 1004 : //	��������
							this->HT_hrSetMessage( eMsgLogInEtc, &szMessage);
							break;
						case 1005 : //	ȸ��Ż��
							this->HT_hrSetMessage( eMsgLogInHomepageWithdraw, &szMessage);
							break;
						case 1006 : //	14�� �̸�
							this->HT_hrSetMessage( eMsgLogInNeedParentAgree, &szMessage);
							break;
						case 1007 : //	�׽�Ʈ���� ����
							this->HT_hrSetMessage( eMsgLoginErrorTestServer, &szMessage);
							break;
						case 1008 : //	12�� �̸�
							this->HT_hrSetMessage( eMsgLoginErrorAgeLimit, &szMessage);
							break;
						case 1009 : //	18�� �̸�
							g_cUIManager->HT_SetScriptMessage( eMsgIntorLimitAge, &szMessage, _T(""), _T("") );	//	źƮ��� ��15�� �̻� ������ �̿��ϽǼ� �ֽ��ϴ�.
							break;
						default :
							this->HT_hrSetMessage( eMsgLoginServerBusy, &szMessage);
							break;
					}
				}
				else
				{
					switch(g_iLoginResultID)
					{	
						case _LOGIN_DISABLE_CAUSE_PASSWORDERROR:
							this->HT_hrSetMessage( eMsgLogInPasswdMismatch, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_IDERROR:
							this->HT_hrSetMessage( eMsgLogInInvalidUser, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_BLOCKUSER:
							this->HT_hrSetMessage( eMsgLogInBlockID, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_SERVERDOWN:
							this->HT_hrSetMessage( eMsgLogInEtc, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_HOMEPAGE_WITHDRAW:
							this->HT_hrSetMessage( eMsgLogInHomepageWithdraw, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_NEED_EXTRAINFO:
							this->HT_hrSetMessage( eMsgLogInNeedExtraInfo, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_NEED_PARENTAGREE:
							this->HT_hrSetMessage( eMsgLogInNeedParentAgree, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_UNKNOWN:
							this->HT_hrSetMessage( eMsgLoginServerBusy, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_NOTBILL:
							this->HT_hrSetMessage( eMsgLoginServerNotBill, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_NEEDBILL:
							this->HT_hrSetMessage( eMsgLoginServerNeedBill, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_OPENWAIT:
							this->HT_hrSetMessage( eMsgLoginServerOpenWait, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_TESTSERVER:
							this->HT_hrSetMessage( eMsgLoginErrorTestServer, &szMessage);
							break;
						case _LOGIN_DISABLE_CAUSE_AGELIMIT:
							this->HT_hrSetMessage( eMsgLoginErrorAgeLimit, &szMessage);
							break;
						default:
							return;
					}
				}
				this->HT_vIntro_SetShowMessage( szMessage.HT_szGetString(), 5000 );
			}
		}
	}
}
HTvoid
CHTIntroManager::HT_vSCP_RESP_LOGIN()
{
	//	�޽��� �� �����ֱ�
	this->HT_vIntro_SetHideMessage();
	m_strSaveID = m_strID.HT_szGetString();
	m_strID.HT_hrCleanUp();
	m_strPassword.HT_hrCleanUp();

	//	Object Ani
	g_pEngineHandler->HT_hrChangeMonsterAttackAnimation( m_iMobForIntro[0], INTRO_GATEMOB1, 3612, 1 );
	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[1], INTRO_GATEMOB1, HT_ANISTATE_ATK_2, 1 );

	//	About Otheer Object ID Login
	m_bLoginDelay = HT_TRUE;
	m_dwLoginStartTime = timeGetTime();

	//	2003119_���� ����Ʈ�� �̹� Ŭ���̾�Ʈ�� Ȯ���ϰ� �ֱ� ������... ���⼭�� ���帮��Ʈ ��û�� �ƴ� ������� �ҷ��ش�.
    //this->HT_vSCP_RESP_WORLD_LIST();
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_LOGOUT()
{
	g_pNetWorkMgr->DisConnect();
	this->HT_vSCP_RESP_CHAR_LOGOUT();
}
HTvoid
CHTIntroManager::HT_vSCP_RESP_CHAR_LOGOUT()
{
	//	Delete Logo Window
	g_cUIManager->HT_HideWindow( _DIALOG_SERVERSELECT );
	//	Show Window
	this->HT_vIntro_SetShowWindow( _DIALOG_LOGINBOX, 1000 );
	//	Load Id
	this->HT_vIntro_LoadID();
	//	Set Animation
	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[0], INTRO_GATEMOB1, HT_ANISTATE_STD, -1 );
	g_pEngineHandler->HT_hrChangeAnimation(  m_iMobForIntro[1], INTRO_GATEMOB1, HT_ANISTATE_STD, -1 );

	m_strID.HT_hrCleanUp();
	m_strPassword.HT_hrCleanUp();

	//	Move Camera
	if( g_byReStartCode == 0 )
	{
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_LOGIN][0], 1, 0.98f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_LOGIN][1], 1, 0.98f);
	}
}

//	World List ����
HTvoid
CHTIntroManager::HT_vSCP_RESP_WORLD_LIST()
{
	HTint i;
	HTint iWorldCCUserNum, iBtnOnNum, iAliveWorldNum;
	{
		for( i=0 ; i<g_iWorldNum ; i++)
		{	
			if( !g_bDevelopingMode )
			{
				if (g_poWebLogIn)
				{
					iWorldCCUserNum = g_poWebLogIn->HT_iGetCCUserNum(i+g_gServerType, 0);// ���ٶ� ������ �������� ������ ǥ�� ����
					iAliveWorldNum = g_poWebLogIn->HT_iGetAliveZoneNum(i+g_gServerType);
					
					if (!iAliveWorldNum)
						iBtnOnNum = 0;
					else
						iBtnOnNum = iWorldCCUserNum/100;

					//	�ּ� ������ 5ĭ �̻����� �������ش�.
					if( g_iInationalType == INATIONALTYPE_KOREA )
					{
						if( iBtnOnNum < 5 )
							iBtnOnNum = 5;
					}
				}
			}
			else
			{
				iBtnOnNum = 0;
			}
		}
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_MOVE_ZONE_SERVER( BYTE byMoveZoneServerPoint )
{
	//	0x01:�α�����,0x02:���ΰ��� ���� ����
	m_byMoveZoneServerPoint = byMoveZoneServerPoint;

	//-----------------------------------------------
	// �� ������ �̵�
	//-----------------------------------------------
	S_CSP_REQ_MOVE_ZONE_SERVER info;
	memset( &info, 0, sizeof(S_CSP_REQ_MOVE_ZONE_SERVER) );

	//CHTString strTemp2;
	//strTemp2.HT_szFormat( "dwEvent:%d", g_iLoginResultID );
	//MessageBox( NULL, strTemp2, "Debug", MB_OK );
	if( g_iLoginResultID == 0xcccccccc )
		g_iLoginResultID = 0;
	info.dwEvent = (DWORD)g_iLoginResultID;
	CHTString::HT_hrStringCopy( info.AccountName, (HTtchar*)g_strLoginID, ACCOUNTNAME_LENGTH );
	CHTString::HT_hrStringCopy( info.AccountPass, (HTtchar*)g_strLgoinPasswordMD5, ACCOUNTPASS_LENGTH );
	for( int i=0 ; i<4 ; i++ )	info.snVersion[i] = g_snVersionCheck[i];
	
	//	0x01:�α�����,0x02:���ΰ��� ���� ����
	if( m_byMoveZoneServerPoint == 0x01 )
	{
		ZeroMemory( info.szCharName, sizeof(BYTE)*SZNAME_LENGTH );
	}
	else if( m_byMoveZoneServerPoint == 0x02 )
	{
        CHTString::HT_hrStringCopy( info.szCharName, m_oSeverChar[m_nSelectedCharNo].sCharInfo.szCharName, SZNAME_LENGTH );
	}
	g_pNetWorkMgr->RequestReqMoveZoneServer( &info );
	//-----------------------------------------------

	//	�޽��� ����
	CHTString szMessage;
	this->HT_hrSetMessage( eMsgLogInReqGameServer, &szMessage );
    this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONG );
}

HTvoid
CHTIntroManager::HT_vSCP_RESP_MOVE_ZONE_SERVER( PS_SCP_RESP_MOVE_ZONE_SERVER info )
{
	CHTString strMessage;
	strMessage.HT_hrCleanUp();
	switch( info->nResult )
	{
		case REPLY_ACK_OK :
			//	�޽��� �� �����ֱ�
			this->HT_vIntro_SetHideMessage();
			//	���� ������ ����� �Ѿ������ ĳ���� ����Ʈ ��û
			if( m_byMoveZoneServerPoint == 0x01 )
			{
				for( HTint i=0 ; i<3 ; i++ )
					m_nExistCharacterModelID[i] = -1;
				//ĳ���͸���Ʈ�� �޶� ��û
				this->HT_vCSP_Request_CHAR_LIST();
			}
			//	���ΰ��� �������� ������ ���� ��û������
			else if( m_byMoveZoneServerPoint == 0x02 )
			{
				this->HT_vEnter_MainGame();
			}
			return;
		case REPLY_INVALID_USER :
			// ������ �������� �ʽ��ϴ�.
			this->HT_hrSetMessage( eMsgLogInInvalidUser, &strMessage );
			break;
		case REPLY_INVALID_PASSWD :
			// ��й�ȣ�� Ʋ���ϴ�.
			this->HT_hrSetMessage( eMsgLogInPasswdMismatch, &strMessage );
			break;
		case REPLY_NO_RESPONSE	:
			// �������� ������ �����ϴ�.
			this->HT_hrSetMessage( eMsgLogInNoResponse, &strMessage );
			break;
		case REPLY_ACCOUNT :
			// ������, �ð����� ���� ������ ���� �Ұ��մϴ�.
			this->HT_hrSetMessage( eMsgLogInBlockID, &strMessage );
			break;
		case REPLY_ALREADY_LOGIN :
			// �̹� �α��� �Ǿ� �ֽ��ϴ�.
			this->HT_hrSetMessage( eMsgLogInAlreadyLogIn, &strMessage );
			break;
		case REPLY_NEED_LOGIN :
			// �α��� ���� ���� ������Դϴ�.
			this->HT_hrSetMessage( eMsgLogInNeed, &strMessage );
			break;
	}

	if( strMessage.HT_nGetSize() != 0 )
	{
		//	�޽��� ����
		this->HT_vIntro_SetShowMessage( strMessage, MESSAGE_DELAYTIME_SHORT );
		//	���� ������ ���� ����
		g_pNetWorkMgr->DisConnect();
		//	LoginFaild DisConnect Setting
		m_bZoneServerDisConnected_ForLoginFaild	= HT_TRUE;
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_LIST()
{
	//	ĳ���� ����Ʈ ��û�ϱ����� ĳ���� �� �ʱ�ȭ
	m_iCharNum = 0;
	for( HTint i=0 ; i<3 ; i++ )
	{
		m_oSeverChar[i].bSw = HT_FALSE;
		if( m_nExistCharacterModelID[i] != -1 )
		{
			g_pEngineHandler->HT_vDestroyCharacter( m_nExistCharacterModelID[i], 6 );
			m_nExistCharacterModelID[i] = -1;
		}
	}
	//	ĳ���� ����Ʈ ��û
	g_pNetWorkMgr->RequestCharList();
	
	CHTString szMessage;
	HT_g_Script_SetMessage( eMsgLogInReqCharacterList, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, 5000 );
}
HTvoid
CHTIntroManager::HT_vSCP_RESP_CHAR_LIST( char* pData )
{ 
	//	�޽��� �� �����ֱ�
	this->HT_vIntro_SetHideMessage();

	//	ĳ���� ����Ÿ�� ����
	HTint  iPosition = 0;
	CHTString strName;
	for (HTint i=0; i<3; i++)
	{
		memcpy(&(m_oSeverChar[i].sCharInfo), pData+iPosition, sizeof(S_CHARACTER_LIST) );
		strName = m_oSeverChar[i].sCharInfo.szCharName;
		if( strName.HT_bIsEmpty() )
		{
			m_oSeverChar[i].bSw = HT_FALSE;
		}
		else
		{
			m_oSeverChar[i].bSw = HT_TRUE;
			for( HTint j=0 ; j<7 ; j++ )
                m_oSeverChar[i].sCharInfo.Equip[j].snIndex += HT_ITEM_INDEX_START;
			m_iCharNum++;
		}
		iPosition += sizeof(S_CHARACTER_LIST);
	}

	//	ĳ���� ����Ʈ ���� �������� ĳ���� ����Ʈ�� �Ѿ������ �����ؾ� �� �κе�
	{
		//	��Ż ID �ʱ�ȭ
		g_wPotalID			= 0x00;
        m_byConnectType		= 0x00;
		g_wWalf				= 0x00;

		m_strID.HT_hrCleanUp();
		m_strPassword.HT_hrCleanUp();

		//	For Render Character load
		m_bForRenderCharacterData = FALSE;
		m_iLoadCharDataSequence = 0;
		//if( g_byReStartCode == 0 )
  //          this->HT_vIntro_SetShowMessage( _T("Loading Character data...."), 5000 );

		m_iIntroStatus = GAMESEQUENCE_INTRO_LOADCHARACTER;
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_CREATE()
{
    CHTString szMessage;

	//	����ġ ���� �ܾ� �ɷ�����
	for( HTint i=0 ; i<NOTCHARANDGUILDNAME_COUNT ; i++ )
	{
		if( m_strNewCharacterName.HT_bFind( g_szNotCharAndGuildName[i] ) == HT_TRUE )
		{
			this->HT_hrSetMessage( eMsgCharacListInvalidName, &szMessage );
			this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_MIDDLE );
			return;
		}
	}

	//	�Ϻ������� ĳ������ ���� ���� ���
	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		if( m_strNewCharacterName.HT_nGetSize() > SZNAME_LENGTH-2 )
		{
			this->HT_hrSetMessage( eMsgCharacListNameLengthErr, &szMessage );
			this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_MIDDLE );
			return;
		}
	}

	if( m_byCharCreate_ServiceChakraPoint != 0 )
	{
		HT_g_Script_SetMessage( eMsgCharacListChakraPointErr, &szMessage );
		this->HT_vIntro_SetShowMessage( szMessage, 5000 );
		return;
	}

	PS_CSP_REQ_CHAR_CREATE info = HT_NULL;
    info = new S_CSP_REQ_CHAR_CREATE;

	info->byFaceType = m_nNewCharacterFace;
	info->byHeadType = m_nNewCharacterHair;
	info->snTribe = g_byCharacterServerTribe[m_nNewCharacterTribe];
	info->byTrimuriti = 0;
	info->byChakraMuscle = m_byCharCreate_ChakraMuscle;
  	info->byChakraNerve = m_byCharCreate_ChakraNerve;
  	info->byChakraHeart = m_byCharCreate_ChakraHeart;
	info->byChakraSoul = m_byCharCreate_ChakraSoul;
	CHTString::HT_hrStringCopy( info->szCharName, m_strNewCharacterName, SZNAME_LENGTH );
	g_pNetWorkMgr->RequestCharCreation( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_Create_Character : %s", info->szCharName );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

	//	�޽��� ����
	this->HT_hrSetMessage( eMsgCharacListReqCreate, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONGLONG );
}

HTvoid
CHTIntroManager::HT_vCSP_RESP_CHAR_CREATE( PS_SCP_RESP_CHAR_CREATE info )
{
	if( info->byResult == 0x00 )
	{
		g_pEngineHandler->HT_hrPlaySound( 33502, 1 );	// Click Sound

		this->HT_vIntro_SetHideMessage();		//	�޽��� �� �����ֱ�

		//	������� ĳ���� �����ϱ�
		for( HTint i=0 ; i<3 ; i++ )
		{
			if( !m_oSeverChar[i].bSw )
			{
				m_oSeverChar[i].bSw = HT_TRUE;
				m_oSeverChar[i].sCharInfo.byFaceType = m_nNewCharacterFace;
				m_oSeverChar[i].sCharInfo.byHeadType = m_nNewCharacterHair;
				m_oSeverChar[i].sCharInfo.snTribe = g_byCharacterServerTribe[m_nNewCharacterTribe];
				m_oSeverChar[i].sCharInfo.byTrimuriti = 0;
				m_oSeverChar[i].sCharInfo.byTrimuritiClass = 0;
				m_oSeverChar[i].sCharInfo.nBrahmanPoint = 0;
				m_oSeverChar[i].sCharInfo.byLevel = 1;
				m_oSeverChar[i].sCharInfo.snChakraHeart	 = g_iCharacterChacraPoint[m_nNewCharacterTribe][2] + m_byCharCreate_ChakraHeart;
				m_oSeverChar[i].sCharInfo.snChakraMuscle = g_iCharacterChacraPoint[m_nNewCharacterTribe][0] + m_byCharCreate_ChakraMuscle;
				m_oSeverChar[i].sCharInfo.snChakraNerve  = g_iCharacterChacraPoint[m_nNewCharacterTribe][1] + m_byCharCreate_ChakraNerve;
				m_oSeverChar[i].sCharInfo.snChakraSoul	 = g_iCharacterChacraPoint[m_nNewCharacterTribe][3] + m_byCharCreate_ChakraSoul;
				CHTString::HT_hrStringCopy( m_oSeverChar[i].sCharInfo.szCharName, m_strNewCharacterName, SZNAME_LENGTH );

				//STRUCT_ITEM	Equip[5];
				HTint ib1, ib2, ib3, ib4;
				m_oSeverChar[i].sCharInfo.LastServerPort = g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].snWorldPort;
				sscanf( g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldIP, "%d.%d.%d.%d", &ib1, &ib2, &ib3, &ib4 );
				m_oSeverChar[i].sCharInfo.LastServerIP.S_un.S_un_b.s_b1 = ib1;
				m_oSeverChar[i].sCharInfo.LastServerIP.S_un.S_un_b.s_b2 = ib2;
				m_oSeverChar[i].sCharInfo.LastServerIP.S_un.S_un_b.s_b3 = ib3;
				m_oSeverChar[i].sCharInfo.LastServerIP.S_un.S_un_b.s_b4 = ib4;

				m_oSeverChar[i].sCharInfo.LastZone = 1;

				for( HTint j=0 ; j<7 ; j++ )
                    m_oSeverChar[i].sCharInfo.Equip[j].snIndex = 0;
				
				m_iCharNum++;
				//ĳ���͸���Ʈ�� �ǰ��� ĳ���͸� ����
				this->HT_vExistCharCreate();
				return;
			}
		}		
	}
	else
	{
		// �޽��� ����
		CHTString strMsg;
		switch( info->byResult )
		{
			case REPLY_CHAR_CREATE_ALREADY_EXIST:	// ĳ���� �̹� ����
				HT_hrSetMessage( eMsgCharacListAlreadyExist, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHAR_FULL:		// ĳ���� ��� ����
				HT_hrSetMessage( eMsgCharacListCannotCreate, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHR_CHAR_FAIL:	// ĳ�����̸� ������
				HT_hrSetMessage( eMsgCharacListInvalidName, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHAKRA_OVER:		// ������ũ�����
				HT_hrSetMessage( eMsgCharacListBasicChakraOver, &strMsg );
				break;
			default: // REPLY_CHAR_CREATE_FAIL		// ĳ���� ���� ����
				HT_hrSetMessage( eMsgCharacListCreateFail, &strMsg );
				break;
		}

		this->HT_vIntro_SetShowMessage( strMsg, 5000 );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_Recive_Character : %d", info->byResult );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_REMOVE()
{
	//	�޽��� ����
//	this->HT_vIntro_SetShowMessage( _T("���� ĳ���͸� �����Ҽ� �����ϴ�. "), MESSAGE_DELAYTIME_SHORT );
//	return;

	PS_CSP_REQ_CHAR_REMOVE info = HT_NULL;
	info = new S_CSP_REQ_CHAR_REMOVE;
	if (!info) return;

	CHTString::HT_hrStringCopy( info->szCharName, m_oSeverChar[m_nSelectedCharNo].sCharInfo.szCharName, SZNAME_LENGTH );
	CHTString strTemp;
	//	�߱��� �ֹ� ���ڸ��� �Ⱦ��ϱ� __ 0���� ������.
	if( g_iInationalType == INATIONALTYPE_KOREA )	info->ssn1 = atoi( m_strCharJoominNoFront.HT_szGetString() );
	else											info->ssn1 = 0;
	//	�ֹ� ���ڸ��� �ƹ��͵� ������ Skip
	if( m_strCharJoominNoBack.HT_bIsEmpty() )
		return;
	info->ssn2 = atoi( m_strCharJoominNoBack.HT_szGetString() );
	g_pNetWorkMgr->RequestCharDeletion( info );

	HT_DELETE( info );

	//	�޽��� ����
	CHTString szMessage;
	this->HT_hrSetMessage( eMsgCharacListReqDelete, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONGLONG );

}
HTvoid
CHTIntroManager::HT_vCSP_RESP_CHAR_REMOVE( PS_SCP_RESP_CHAR_REMOVE info )
{
	if( info->byResult == 0x00 )
	{
		this->HT_vIntro_SetHideMessage();		//	�޽��� �� �����ֱ�
		g_pEngineHandler->HT_hrPlaySound( 33503, 1 );	// Click Sound

		//	������ ĳ���� �� �����ϱ�
		if( m_nExistCharacterModelID[m_nSelectedCharNo] != -1 )
		{
			g_pEngineHandler->HT_vDestroyCharacter( m_nExistCharacterModelID[m_nSelectedCharNo], 7 );
			m_nExistCharacterModelID[m_nSelectedCharNo] = -1;
		}
		memset( &m_oSeverChar[m_nSelectedCharNo], 0, sizeof(_HT_CHARINFO) );
		m_iCharNum--;

		//	Hide Window
		g_cUIManager->HT_HideWindow( _DIALOG_INPUTJUMINNO );

		if (m_iCharNum)		this->HT_hrCharSelect();
		else				this->HT_hrCharNew();
	}
	else
	{
		//	�޽��� ����
		CHTString strMsg;
		HT_hrSetMessage( eMsgCharacListDeleteFail, &strMsg ); // ĳ���� ���� ����
		this->HT_vIntro_SetShowMessage( strMsg, MESSAGE_DELAYTIME_MIDDLE );
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_SELECT()
{
	// ���࿡ ���� ���� �� ������ IP, PORT�� ������ �� ���� �̵��� ���� �ʰ� �ٷ� ó�� �ȴ�.
	if( g_strZoneServerIP.HT_iStringCompare( g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldIP ) == 0 &&
		g_iZoneServerPort == g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].snWorldPort )
	{
		this->HT_vEnter_MainGame();
	}
	else
	{
		//	���� ������ ���� ����
		g_pNetWorkMgr->DisConnect();
		//	DisConnect Setting
		m_bZoneServerDisConnected_ForMainGame = HT_TRUE;
		//	�޽��� ����
		CHTString szMessage;
		this->HT_hrSetMessage( eMsgLogInReqZoneServer, &szMessage );
		this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONG );
	}
}

//	�������� �̵��Ѵ�.
HTvoid CHTIntroManager::HT_vEnter_MainGame()
{
	//	��Ʈ�ο� ���ҽ��� �� �����.
	this->HT_hrCleanUp();
	g_pEngineHandler->HT_hrClearUISpriteVB();

	//	Set Not Render
	m_b3DRender = HT_FALSE;
	//	UI Render Sw
	m_bUIRender	= HT_FALSE;
	//	For Render GoMainGame
	m_bForRenderGoMainGame = HT_FALSE;

	//	Change Status Go Main Game
	m_iIntroStatus = GAMESEQUENCE_INTRO_GOMAINGAME;
}

//	������ ������ ���������� ������� ������
HTvoid
CHTIntroManager::HT_vUpdate_DisconnectServer()
{
	if( !m_bServerDisconnectSw )
		return;

	DWORD passTime = GetTickCount();
	if( passTime > m_bServerDisconnectTime + 3000 )
	{
		g_pEngineHandler->HT_hrUnloadMap();
		PostQuitMessage( 0 );
	}
}

//	 ���� ������ ����
HTvoid CHTIntroManager::HT_vEnter_FirstServer()
{
	//	��������Ʈ���� �������� ���� ��û������ ��ŵ
	if( m_bReqConnectServerInSerSel )
		return;

	// Click Sound
	g_pEngineHandler->HT_hrPlaySound( 33523, 1 );
	//  ���� ���� ���� ���
	//	ReStart�� �ƴҰ�쿡
	if( g_byReStartCode == 0 )
	{
		if( g_bReciveBillingServer == HT_FALSE )
		{
			CHTString szMessage;
			// ����� ������ �Ⱓ�� ����Ǿ����ϴ�.
			if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
					g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			return;
		}
	}

	//	���� ���� ��忡���� ���� �ټ� üũ
	if( !g_bDevelopingMode )
	{
		if( g_iConnectServerGroupIndex>=g_iWorldNum)
			return;
	}

	//	������ ���� �̸�
	g_strSelectServerName = g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].szWorldName;

	//	���� ���� ���� �������� ���� �ο� �ʰ� �Ǿ����� üũ�ϴ°͵� ���� �ʿ䰡 ������
	//	���Ŀ� �۾�����

	//	Connect Server
	if( g_bDevelopingMode )     g_cIntroManager->m_iCurServerIndex = 1;
	else						g_cIntroManager->m_iCurServerIndex = 6;
	g_pNetWorkMgr->Connect( g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].szWorldIP, 
							g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].snWorldPort );
	//	������ ������ ��û�ߴٴ� �޽��� ���

	//	��������Ʈ���� �������� ���� ��û
	m_bReqConnectServerInSerSel = HT_TRUE;
}
//	TantraParam �����ߴ��� Ȯ���ϱ�.
HTvoid
CHTIntroManager::HT_vCheckTantraParam()
{
	HTint iTempValue;
	HTbool	bTrue = HT_FALSE;
	//	it seems strange
	//	3007	�߷�ī ��Ʈ��(������ ����)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3007, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}
	//3008	�ٷ糪 ����(���� ����) 1000
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3008, 1, &iTempValue ) )
	{
		if( iTempValue != 1000 )		bTrue = HT_TRUE;
	}
	//3022	�縶��(�ε��) 200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3022, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3030	����Ʈ(���� �� ������)	200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3030, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3102	�Ķ�ī(���󽯵�)	200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3102, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3043	����Ƽ(��ũ��)	800
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3043, 1, &iTempValue ) )
	{
		if( iTempValue != 800 )			bTrue = HT_TRUE;
	}
	//3026	�Ƹ��� ī��(ũ���� ��ο�)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3026, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}
	//3042	���Ʈ�� ����(���Ʈ�� ����)	1000
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3042, 1, &iTempValue ) )
	{
		if( iTempValue != 1000 )		bTrue = HT_TRUE;
	}
	//3041	��Ÿ��(�о��)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3041, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}

	if( bTrue == HT_TRUE )
	{
        MessageBox( NULL, _T("It seems strange!!!"), _T("error"), MB_OK );
		//	_USER_MESSAGE_EXIT ����
		m_bIntro_User_message_Exit = HT_TRUE;
	}
//3009	Ÿ��ī(����ų��)	400
//3011	�������(�Ƹ���ī��2) 300
//3013	�׶��	300
//3021	��Ž(����)	300
//3023	���ν��Ƴ�(Ÿ��Ʈ) 300
//3024	��޸��϶���¡(��޸��϶���¡) 200
//3025	�Ʒ�īŲ(����ŷ)	200
//3027	������	300
//3028	���ν��Ƴ� ��Ƽ��(���� Ÿ��Ʈ)	1000
//3029	����ī(�Ǿ�)	1000
//3031	�츶 �縶��(��Ƽ �縶��)	200
//3032	����_ī����	200
//3058	īƾ	300
//3059	��Ÿ	300
//3061	�ο�į��(����ũ)	800
//3103	��ī��(���̵�)	2000
//3104	�� ���(�Ϲ�ī ����Ƽ)	200
//3122	����(�׸��� ���)	600
//3160	��ų��(�ϻ�)	400
//3162	�����ī(���̵�� �ַο�)	745
//3229	�ε�� �߶�(�̵��ӵ�����)	200
//3241	ī������(�ǻ�Ƣ��)	200
//3261	�繫�ٹ�(��Ȱ)	200
//3214	��ĭ�� ǻ��(���ݼӵ� ����)	200
}
//	After Login Time Check
HTvoid
CHTIntroManager::HT_vAfterLoginTimeCheck()
{
	DWORD dwPassTime = timeGetTime();
	//	After Login Time Check
	if( dwPassTime > m_dwIntro_LoginTimeCheck+300000 )
	{
		// �α��� �ð��� �ʰ��Ͽ� ������ �����մϴ�.
		CHTString strMsg;
		HT_hrSetMessage( eMsgCommonExcessLoginTime, &strMsg );
		MessageBox( NULL, strMsg, "error", MB_OK );
		//	_USER_MESSAGE_EXIT ����
		g_cIntroManager->m_bIntro_User_message_Exit = HT_TRUE;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ����� �޼���
///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// HTvoid						HT_vLButtonDown(HTint iPosX, HTint iPosY)
// D : ���콺 LBUTTON DOWN��
//-------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrLButtonDown(HTint iPosX, HTint iPosY)
{
	if( m_bErrorCheckSw == HT_TRUE )	return HT_OK;
	return HT_OK;
}

//-------------------------------------------------------------------------
// HTRESULT						HT_hrLButtonUp(HTint iPosX, HTint iPosY)
// D : ���콺 LBUTTON UP��
//-------------------------------------------------------------------------
HTRESULT CHTIntroManager::HT_hrLButtonUp(HTint iPosX, HTint iPosY)
{
	//	3D ȭ���϶�
	if (m_b3DRender)
	{
		//	� ĳ���� ���� ������ ��
		if( m_bCharSelectZoomInSw == HT_FALSE )
		{
			HTint iObject_ID;
			HTIntersectInfo oInfo;
			g_pEngineHandler->HT_hrPick( iPosX, iPosY, &iObject_ID, &oInfo );

			if( iObject_ID != -1 )
			{
				for( HTint i=0 ; i<3 ; i++ )
				{
					if( m_nExistCharacterModelID[i] == iObject_ID )
					{
						g_pEngineHandler->HT_hrPlaySound( 33502, 1 );	// Click Sound
						m_nSelectedCharNo = i;
						//	ĳ������ �Ѹ��� ���� �߳�?
						m_bCharSelectZoomInSw = HT_TRUE;
						//	Show Window
						this->HT_vIntro_SetShowWindow( _DIALOG_CHARACTERINFO1, 1500 );
						//	ĳ���� ���� �پ��ֱ�
						this->HT_vCharSelect_SetInfo();
						if( i==2 && m_iScreenWidth==800 )
							g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERINFO1, (HTint)g_vecCharInfoWndPos[i].x-100, (HTint)g_vecCharInfoWndPos[i].y );
						else
							g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERINFO1, (HTint)g_vecCharInfoWndPos[i].x, (HTint)g_vecCharInfoWndPos[i].y );
						g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_CHAR1+m_nSelectedCharNo][0], 1, 0.93f);
						g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_CHAR1+m_nSelectedCharNo][1], 1, 0.93f);
						
						//	�����ڵ� �������ֱ�
						HTint iTribe;
						HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );

						HTint iLeftItem = 0;
						if( g_pEngineHandler->HT_bIsShortSword( m_oSeverChar[i].sCharInfo.Equip[3].snIndex ) )
							iLeftItem = m_oSeverChar[i].sCharInfo.Equip[3].snIndex;

						//	�ִϸ��̼� �ε���
						m_iAnimationIndex++;
						if( m_iAnimationIndex == 5 )
							m_iAnimationIndex = 0;

						if( m_iAnimationIndex == 0 )
							g_pEngineHandler->HT_hrChangeAttackAnimation( m_nExistCharacterModelID[i], iTribe, m_arrExistCharWeaponItem[i], 1, iLeftItem, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], m_iAnimationIndex, 0 );
						else if( m_iAnimationIndex == 1 )
							g_pEngineHandler->HT_hrChangeAttackAnimation( m_nExistCharacterModelID[i], iTribe, m_arrExistCharWeaponItem[i], 1, iLeftItem, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], m_iAnimationIndex, 0 );
						else if( m_iAnimationIndex == 2 )
							g_pEngineHandler->HT_hrChangeAttackAnimation( m_nExistCharacterModelID[i], iTribe, m_arrExistCharWeaponItem[i], 1, iLeftItem, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], m_iAnimationIndex, 0 );
						else if( m_iAnimationIndex == 3 )
							g_pEngineHandler->HT_hrChangeAnimation( m_nExistCharacterModelID[i], iTribe, HT_ANISTATE_MAGIC_DEFENCE, 1, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], 0.0f, m_arrExistCharWeaponItem[i] );
						else
							g_pEngineHandler->HT_hrChangeAnimation( m_nExistCharacterModelID[i], m_oSeverChar[i].sCharInfo.snTribe, HT_ANISTATE_MAGIC_HEAL, 1, m_oSeverChar[i].sCharInfo.byFaceType, m_arrExistCharWearItem[i], 0.0f, m_arrExistCharWeaponItem[i] );

						break;
					}
				}
			}
		}
	}

	//	������ ������� �޽��� üũ�ϰ� ������
	if( m_bErrorCheckSw == HT_TRUE )
		return HT_OK;

	m_bSlideOn				= HT_FALSE;

	return HT_OK;
}

// NEW CHARACTER ��ư�� ������ �� ���¿� ���� ����
HTRESULT
CHTIntroManager::HT_hrUserMsgNewChar()
{
	g_pEngineHandler->HT_hrPlaySound( 33502, 1 );	// Click Sound
	switch(m_iIntroStatus)
	{
		case GAMESEQUENCE_INTRO_FIRST:
			break;
		case GAMESEQUENCE_INTRO_LOGSERVERCONNECT:
			break;
		case GAMESEQUENCE_INTRO_LOGIN:
			break;
		case GAMESEQUENCE_INTRO_SELECTWORLD:
			break;
		case GAMESEQUENCE_INTRO_CHAR_SELECT:
			if( m_iCharNum < 3 )
                this->HT_hrCharNew();
			else
			{
				//	�޽��� ����
				CHTString szMessage;
				this->HT_hrSetMessage( eMsgCharacListCannotCreate, &szMessage );
				this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_MIDDLE );
			}
			break;
		case GAMESEQUENCE_INTRO_NEW_CHAR:
			break;
	}
	return HT_OK;
}

HTRESULT CHTIntroManager::HT_hrUserMsgNewCharSelect(HTint iMsg)
{
    g_pEngineHandler->HT_hrPlaySound( 33501, 1 );	// Click Sound

	if( m_bFaceZoominSw )
	{
		m_bFaceZoominSw = HT_FALSE;
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_NEWCAHR][0], 1, 0.95f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_NEWCAHR][1], 1, 0.95f);
	}

	switch( iMsg )
	{
		case _USER_MESSAGE_TRIBELEFT:
			m_nNewCharacterTribe--;
			m_nNewCharacterFace = 0x01;
			m_nNewCharacterHair = 0x01;
			m_byCharCreate_ServiceChakraPoint = CHOOSE_CHAKRA_POINT;
			if( m_nNewCharacterTribe < 0 )
				m_nNewCharacterTribe = 7;
			this->HT_hrNewCharacterCreate( g_byCharacterTribe[m_nNewCharacterTribe] );
			this->HT_hrChakraInit();
			break;
		case _USER_MESSAGE_TRIBERIGHT:
			m_nNewCharacterTribe++;
			m_nNewCharacterFace = 0x01;
			m_nNewCharacterHair = 0x01;
			m_byCharCreate_ServiceChakraPoint = CHOOSE_CHAKRA_POINT;
			if( m_nNewCharacterTribe > 7 )
				m_nNewCharacterTribe = 0;
			this->HT_hrNewCharacterCreate( g_byCharacterTribe[m_nNewCharacterTribe] );
			this->HT_hrChakraInit();
			break;
	}
	//	ĳ���� ���� ����, ��
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace );
	return HT_OK;
}

HTRESULT CHTIntroManager::HT_hrUserMsgNewCharServiceChakra( HTint iButtonNo )
{
	if( m_byCharCreate_ServiceChakraPoint == 0 )
		return HT_OK;

	g_pEngineHandler->HT_hrPlaySound( 33501, 1 );	// Click Sound
	if( iButtonNo == 9 )
		m_byCharCreate_ChakraMuscle++;
	else if( iButtonNo == 10 )
        m_byCharCreate_ChakraNerve++;
	else if( iButtonNo == 11 )
        m_byCharCreate_ChakraHeart++;
	else if( iButtonNo == 12 )
		m_byCharCreate_ChakraSoul++;

	//	���� íũ�� ����
	m_byCharCreate_ServiceChakraPoint--;
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace, HT_FALSE );
	return HT_OK;
}

HTRESULT CHTIntroManager::HT_hrUserMsgNewCharFace(HTint iMsg)
{
	if( iMsg == 5 )
	{
		m_nNewCharacterFace--;
		if( m_nNewCharacterFace <= 1 )
			m_nNewCharacterFace = 1;
	}
	else if( iMsg == 6 )
	{
		m_nNewCharacterFace++;
		if( m_nNewCharacterFace >= 5 )
			m_nNewCharacterFace = 5;
	}

	if( !m_bFaceZoominSw )
	{
		HTvector3 vecTempPos1 = g_fCameraPos[HT_INTRO_CAMERA_FACEZOOMIN][0];
		HTvector3 vecTempPos2 = g_fCameraPos[HT_INTRO_CAMERA_FACEZOOMIN][1];
		vecTempPos1.y = vecTempPos1.y-(22-m_fObjectHeight);
		vecTempPos2.y = vecTempPos2.y-(22-m_fObjectHeight);
		m_bFaceZoominSw = HT_TRUE;
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, vecTempPos1, 1, 0.95f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, vecTempPos2, 1, 0.95f);
	}

	g_pEngineHandler->HT_hrPlaySound( 33501, 1 );	// Click Sound
	this->HT_hrNewCharacterChangeFace();
	//	ĳ���� ���� ����, ��
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace, HT_FALSE );
	return HT_OK;
}

HTRESULT CHTIntroManager::HT_hrUserMsgNewCharHair(HTint iMsg)
{
	if( iMsg == 7 )
	{
		m_nNewCharacterHair--;
		if( m_nNewCharacterHair <= 1 )
			m_nNewCharacterHair = 1;
	}
	else if( iMsg == 8 )
	{
		m_nNewCharacterHair++;
		if( m_nNewCharacterHair >= 5 )
			m_nNewCharacterHair = 5;
	}

	if( !m_bFaceZoominSw )
	{
		HTvector3 vecTempPos1 = g_fCameraPos[HT_INTRO_CAMERA_FACEZOOMIN][0];
		HTvector3 vecTempPos2 = g_fCameraPos[HT_INTRO_CAMERA_FACEZOOMIN][1];
		vecTempPos1.y = vecTempPos1.y-(22-m_fObjectHeight);
		vecTempPos2.y = vecTempPos2.y-(22-m_fObjectHeight);
		m_bFaceZoominSw = HT_TRUE;
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, vecTempPos1, 1, 0.95f);
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, vecTempPos2, 1, 0.95f);
	}

	g_pEngineHandler->HT_hrPlaySound( 33501, 1 );	// Click Sound
	this->HT_hrNewCharacterChangeFace();
	//	ĳ���� ���� ����, ��
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace, HT_FALSE );
	return HT_OK;
}

//	ĳ���� ���� ����, ��
HTvoid
CHTIntroManager::HT_hrUserMsgNewCharSelect_CharInfo( HTint nTribe, HTint nFace, HTbool bRadioInit )
{
	//	Label ����
	CHTString strTemp;
	CHTString strExplain;
	switch( nTribe+1 )
	{
		case HT_ID_CHARACTER_NAGA:
			this->HT_hrSetMessage( eMsgCommonTribeNaga, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain002, &strExplain, _T(""), _T("") );	//	���� ���� ������ �߿� �ְ��� ���ݷ°� �پ �������� ���ϰ� �ִ�.\n ��, �ӵ��� ������ �������� ��������.
			break;
		case HT_ID_CHARACTER_ASURA:
			this->HT_hrSetMessage( eMsgCommonTribeAsura, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain003, &strExplain, _T(""), _T("") );	//	�Ƽ��� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
			break;
		case HT_ID_CHARACTER_YAKSA:
			this->HT_hrSetMessage( eMsgCommonTribeYaksha, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain004, &strExplain, _T(""), _T("") );	//	��ũ�� ���� ���� ������ ��Ȯ�� ��ġ�� ������. ���ݷ��� ������ ������ �ʿ����� ������ �������� �׵��� ���� �����ϰ� �����.
			break;
		case HT_ID_CHARACTER_DEVA:
			this->HT_hrSetMessage( eMsgCommonTribeDeva, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain005, &strExplain, _T(""), _T("") );	//	�������� �������� �ɷ¿����� � �������� �������� �������� �鿡���� �� � �������� ���ϴ�.
			break;
		case HT_ID_CHARACTER_KIMNARA:
			this->HT_hrSetMessage( eMsgCommonTribeKimnara, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain006, &strExplain, _T(""), _T("") );	//	Ų���� ���� ������ �߿� �ְ��� ���ݷ°� �پ �������� ���ϰ� �ִ�.\n ��, �ӵ��� ������ �������� ��������.
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			this->HT_hrSetMessage( eMsgCommonTribeRakshasa, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain007, &strExplain, _T(""), _T("") );	//	��ũ���� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			this->HT_hrSetMessage( eMsgCommonTribeGandharva, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain008, &strExplain, _T(""), _T("") );	//	���ٸ��� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
			break;
		case HT_ID_CHARACTER_GARUDA:
			this->HT_hrSetMessage( eMsgCommonTribeGaruda, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain009, &strExplain, _T(""), _T("") );	//	����� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
			break;
		default:
			this->HT_hrSetMessage( eMsgCommonNone, &strTemp);
			break;
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 12, strTemp.HT_szGetString() );
	//	Label ���� ����
	g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_CHARACTERCREATE, 14, strExplain.HT_szGetString() );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_CHARACTERCREATE, 14, 7 );
	//	Label �� ����
	this->HT_hrSetMessage( eMsgFace, &strTemp);
	strTemp.HT_szFormat( strTemp, m_nNewCharacterFace );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 16, strTemp.HT_szGetString() );
	//	Label �Ӹ� ����
	this->HT_hrSetMessage( eMsgHead, &strTemp);
	strTemp.HT_szFormat( strTemp, m_nNewCharacterHair );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 18, strTemp.HT_szGetString() );
	//	íũ�� ����Ʈ
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][0] + m_byCharCreate_ChakraMuscle);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 25, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][1] + m_byCharCreate_ChakraNerve);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 26, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][2] + m_byCharCreate_ChakraHeart);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 27, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][3] + m_byCharCreate_ChakraSoul);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 28, strTemp.HT_szGetString() );
	//	��ü ����Ʈ
	strTemp.HT_szFormat("%d", m_byCharCreate_ServiceChakraPoint );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 29, strTemp.HT_szGetString() );
}

// Intro ��濡 ���Ǵ� FX ����
CHTIntroManager::HTIntroBackFX::HTIntroBackFX () : m_idFX (-1), m_idNullModel (-1)
{}

CHTIntroManager::HTIntroBackFX::~HTIntroBackFX ()
{ HT_hrStopFX(); }

HTRESULT
CHTIntroManager::HTIntroBackFX::HT_hrBeginFX( HTvector3& vecPos )
{
	m_idNullModel = g_pEngineHandler->HT_iCreateNullModel( vecPos );
	return g_pEngineHandler->HT_hrStartSFX( &m_idFX, HT_FX_INTROBACK, m_idNullModel, HT_TRUE );
}

HTRESULT
CHTIntroManager::HTIntroBackFX::HT_hrStopFX()
{
	if ( m_idFX > 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_idFX );
		m_idFX = -1;
	}

	if ( m_idNullModel > 0 )
	{
		g_pEngineHandler->HT_vDestroyObject( m_idNullModel, 13 );
		m_idNullModel = -1;
	}

	return HT_OK;
}

HTRESULT CHTIntroManager::HT_hrChakraInit()
{
	m_byCharCreate_ChakraMuscle = 0;
	m_byCharCreate_ChakraNerve	= 0;
	m_byCharCreate_ChakraHeart	= 0;
	m_byCharCreate_ChakraSoul	= 0;
	m_byCharCreate_ServiceChakraPoint = CHOOSE_CHAKRA_POINT;

	CHTString strTemp;
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[m_nNewCharacterTribe][0]);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 25, strTemp.HT_szGetString() );

	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[m_nNewCharacterTribe][1]);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 26, strTemp.HT_szGetString() );

	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[m_nNewCharacterTribe][2]);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 27, strTemp.HT_szGetString() );

	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[m_nNewCharacterTribe][3]);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 28, strTemp.HT_szGetString() );

	//	��ü ����Ʈ
	strTemp.HT_szFormat("%d",  m_byCharCreate_ServiceChakraPoint);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 29, strTemp.HT_szGetString() );

	return HT_OK;
}

//BOOL 
//CHTIntroManager::GetHttpRequest(LPSTR url,LPSTR recvbuffer,int buffersize)
//{
//	DWORD dwBytesRead;
//	HINTERNET m_Session	= InternetOpen("MS",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL,0) ;
//	if (!m_Session) return FALSE;
//
//	HINTERNET hHttpFile	= InternetOpenUrl(m_Session, (const char *) url, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE , 0);
//	if	(hHttpFile)
//	{	
//		InternetReadFile(hHttpFile, recvbuffer, buffersize, &dwBytesRead); 
//		InternetCloseHandle(hHttpFile);
//		//Request[dwBytesRead]=0;
//	}	
//	else
//	{	int ret=GetLastError();
//		// check ret (?)
//		return FALSE;
//	}
//	return TRUE;
//}

HTRESULT CHTIntroManager::HT_hrSetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
	{	
		szString.HT_hrCleanUp();
		return HT_FAIL;
	}
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vSetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vSetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vSetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vSetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;

	return HT_OK;
}

HTvoid CHTIntroManager::HT_vSetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// ī��Ʈ ���
		case eMsgParamCastGrade :
		{
			HTint iCast = HT_iGetCastClass();
			if( iCast == _CHARAC_CAST_SUDRA_3 || iCast == _CHARAC_CAST_VAISHA_3 || iCast == _CHARAC_CAST_KSHATRYA_3
				 || iCast == _CHARAC_CAST_BRAMAN_3 || iCast == _CHARAC_CAST_AVATARA_3 || iCast == _CHARAC_CAST_RESERVE_3 )
				*pszParam = _T("3");
			else if( iCast == _CHARAC_CAST_SUDRA_2 || iCast == _CHARAC_CAST_VAISHA_2 || iCast == _CHARAC_CAST_KSHATRYA_2
				 || iCast == _CHARAC_CAST_BRAMAN_2 || iCast == _CHARAC_CAST_AVATARA_2 || iCast == _CHARAC_CAST_RESERVE_2 )
				*pszParam = _T("2");
			else if( iCast == _CHARAC_CAST_SUDRA_1 || iCast == _CHARAC_CAST_VAISHA_1 || iCast == _CHARAC_CAST_KSHATRYA_1
				 || iCast == _CHARAC_CAST_BRAMAN_1 || iCast == _CHARAC_CAST_AVATARA_1 || iCast == _CHARAC_CAST_RESERVE_1 )
				*pszParam = _T("1");
			else
				*pszParam = _T("0");

		}
			break;
		// ����
		case eMsgParamZoneNum:
		{
			switch( m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone )
			{
				case 1 : // ���ٶ� 1��
				case 3 : // ���ٶ� ���� 1��
				case 5 : // ���߶� ���� 1��
				case 7 : // ���� 1��
				case 18 : // 18�� ��
				case 19 :
					pszParam->HT_szFormat( "%d", 1);	break;

				case 2 : // ���ٶ� 2��
				case 4 : // ���ٶ� ���� 2��
				case 6 : // ���߶� ���� 2��
				case 8 : // ���� 2��
					pszParam->HT_szFormat( "%d", 2);	break;

				case 9 : // ���� 3��
					pszParam->HT_szFormat( "%d", 3);	break;
			
				case 10 : // ���� 4��
					pszParam->HT_szFormat( "%d", 4);	break;

				default: pszParam->HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone); break;
			}
		}
			break;

		default:
			break;
	}
}

HTint CHTIntroManager::HT_iGetCastClass()
{
	
	HTint iBrahmanPoint = m_oSeverChar[m_nSelectedCharNo].sCharInfo.nBrahmanPoint;
	// ����� 3��
	if( iBrahmanPoint <= _CHARAC_CAST_SUDRA_3_END )										
		return _CHARAC_CAST_SUDRA_3;
	// ����� 2��
	else if ( _CHARAC_CAST_SUDRA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_2_END )
		return _CHARAC_CAST_SUDRA_2;
	// ����� 1��
	else if ( _CHARAC_CAST_SUDRA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_1_END )
		return _CHARAC_CAST_SUDRA_1;
	// ���̻� 3��
	else if ( _CHARAC_CAST_VAISHA_3_START	<= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_3_END )
		return _CHARAC_CAST_VAISHA_3;
	// ���̻� 2��
	else if ( _CHARAC_CAST_VAISHA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_2_END )
		return _CHARAC_CAST_VAISHA_2;
	// ���̻� 1��
	else if ( _CHARAC_CAST_VAISHA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_1_END )
		return _CHARAC_CAST_VAISHA_1;
	// ũ��Ʈ���� 3��
	else if ( _CHARAC_CAST_KSHATRYA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_3_END )
		return _CHARAC_CAST_KSHATRYA_3;
	// ũ��Ʈ���� 2��
	else if ( _CHARAC_CAST_KSHATRYA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_2_END )
		return _CHARAC_CAST_KSHATRYA_2;
	// ũ��Ʈ���� 1��
	else if ( _CHARAC_CAST_KSHATRYA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_1_END )
		return _CHARAC_CAST_KSHATRYA_1;
	// ��� 3��
	else if ( _CHARAC_CAST_BRAMAN_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_3_END )
		return _CHARAC_CAST_BRAMAN_3;
	// ��� 2��
	else if ( _CHARAC_CAST_BRAMAN_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_2_END )
		return _CHARAC_CAST_BRAMAN_2;
	// ��� 1��
	else if ( _CHARAC_CAST_BRAMAN_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_1_END )
		return _CHARAC_CAST_BRAMAN_1;
	// �ƹ�Ÿ�� 3��
	else if ( _CHARAC_CAST_AVATARA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_3_END )
		return _CHARAC_CAST_AVATARA_3;
	// �ƹ�Ÿ�� 2��
	else if ( _CHARAC_CAST_AVATARA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_2_END )
		return _CHARAC_CAST_AVATARA_2;
	// �ƹ�Ÿ�� 1��
	else if ( _CHARAC_CAST_AVATARA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_1_END )
		return _CHARAC_CAST_AVATARA_1;
	// ���� 3��
	else if ( _CHARAC_CAST_RESERVE_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_3_END )
		return _CHARAC_CAST_RESERVE_3;
	// ���� 2��
	else if ( _CHARAC_CAST_RESERVE_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_2_END )
		return _CHARAC_CAST_RESERVE_2;
	// ���� 1��
	else if ( _CHARAC_CAST_RESERVE_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_1_END )
		return _CHARAC_CAST_RESERVE_1;
	
	else
		return _CHARAC_CAST_NONE;
	
	//return m_oSeverChar[m_nSelectedCharNo].sCharInfo.
}

//	������ �˾ƿ���
HTint
CHTIntroManager::HT_iIntro_GetConnectNum( HTint iGroup, HTint iConnectZone )
{
	if( !g_bDevelopingMode )
	{
		if (g_poWebLogIn)
		{
			//g_poWebLogIn->HT_bGetServerStatusCheck(/*HTchar* pcWebRecv*/);
			//return g_poWebLogIn->HT_iGetCCUserNum( iGroup+g_gServerType, iConnectZone );
			return g_poWebLogIn->HT_iGetCCUserNum( iGroup, iConnectZone );
		}
	}
	return 1;
}

// ĳ���Ͱ� ���ٶ� ������ �ִ��� üũ
HTbool
CHTIntroManager::HT_bIsCharInMandara()
{
	g_wResentZoneServerID = m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone;

	if (g_wResentZoneServerID==_MANDARA1ST_1 ||
		g_wResentZoneServerID==_MANDARA1ST_2 ||
		g_wResentZoneServerID==_MANDARA1ST_3)	return HT_TRUE;
	return HT_FALSE;
}

//	���ٶ� ������ ���� �˾ƿ���
HTbool
CHTIntroManager::HT_bSetMandaraCCUser(HTint iNo)
{
	HTfloat fCCUserNum = 0;
	switch(iNo)
	{
		case 0:
			m_iMandaraCCUserNum[iNo] = this->HT_iIntro_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, _MANDARA1ST_1-1 );
			break;
		case 1:
			m_iMandaraCCUserNum[iNo] = this->HT_iIntro_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, _MANDARA1ST_2-1 );
			break;
		case 2:
			m_iMandaraCCUserNum[iNo] = this->HT_iIntro_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, _MANDARA1ST_3-1 );
			break;
	}
	
	fCCUserNum = (HTfloat)(m_iMandaraCCUserNum[iNo])/1000.0f;
	if (fCCUserNum<0.0f ) fCCUserNum = 0.0f;
	if (fCCUserNum>1.0f ) fCCUserNum = 1.0f;

	return HT_TRUE;
}

HTvoid
CHTIntroManager::HT_vSetURL()
{
	CHTString strURL;
	HTchar cURL[HT_MAX_STR];
	ZeroMemory(cURL, sizeof(HTchar)*HT_MAX_STR);
	HTint iSize = 0, i=0;


	this->HT_hrSetMessage( eURLLogInEnable, &strURL );
	iSize = strURL.HT_nGetSize();
	CopyMemory(cURL, strURL, sizeof(HTchar)*iSize);
	//for (i=0; i<iSize; i++)	cURL[i] = strURL[i];
	g_poWebLogIn->HT_vSetURL(strURL, LOGIN_ENABLE);

	ZeroMemory(cURL, sizeof(HTchar)*HT_MAX_STR);
	this->HT_hrSetMessage( eURLIDPASSWORDCheckTestSev, &strURL );
	iSize = strURL.HT_nGetSize();
	//for (i=0; i<iSize; i++)	cURL[i] = strURL[i];
	CopyMemory(cURL, strURL, sizeof(HTchar)*iSize);
	g_poWebLogIn->HT_vSetURL(strURL, IDPASSWORD_TESTSEV);

	ZeroMemory(cURL, sizeof(HTchar)*HT_MAX_STR);
	this->HT_hrSetMessage( eURLIDPASSWORDCheckMainSev, &strURL );
	iSize = strURL.HT_nGetSize();
	//for (i=0; i<iSize; i++)	cURL[i] = strURL[i];
	CopyMemory(cURL, strURL, sizeof(HTchar)*iSize);
	g_poWebLogIn->HT_vSetURL(strURL, IDPASSWORD_MAINSEV);

	ZeroMemory(cURL, sizeof(HTchar)*HT_MAX_STR);
	this->HT_hrSetMessage( eURLGMCall, &strURL );
	iSize = strURL.HT_nGetSize();
	//sprintf(strURL, str);
	CopyMemory(cURL, strURL, sizeof(HTchar)*iSize);
	g_poWebLogIn->HT_vSetURL(strURL, GM_CALL);

	//this->HT_hrSetMessage( eURLGMCallCancel, &szURL );
	//sprintf(strURL, str);
	//g_poWebLogIn->HT_vSetURL(strURL, GM_CALL_CANCEL);
}

