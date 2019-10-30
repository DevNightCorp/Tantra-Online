 
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

//	예외 처리사항
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

// 실제 제작되어 있는 종족 코드
BYTE g_byCharacterTribe[8] = {	0x01,	// 나가
								0x02,	// 아수라
								0x03,	// 약샤
								0x04,	// 데바
								0x05,	// 킨나라
								0x06,	// 라크샤사
								0x07,	// 간다르바
								0x08,	// 가루다
							};

//	8족종에 대한 최초 능력치
//	0:근육,1:신경,2:심장,3:정신
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

//	New 캐릭터 위치 / 각도 (최대 3명)
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

//	카메라 위치
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

//정파트장님 인트로에 아난가드반타 대신 넣을 수잇는거 골라봣는데 먼저 차투랑가 보스(말 에서 내린..) 2. 요새던전에나오는 환두 3. 북구성군 쌍칼든 보스  4. 소환법사 몬스터 다다티정도로 골라 봤습니다. 시간 되시면 한번 넣어 보시면,,,그래픽적으로 어룰리는 모양을 찾을수 있을것 같습니다.   참그리고 지금 로그인 화면은 카메라와 오브젝트가 거리가 멀어서 천장 오브젝트 일부분이 그대로 노출 되므로 조금만 당겨 주면 좋은 구도가 될거 같습니다. 히궁,, ^^;; 수고하십시요
#define INTRO_GATEMOB1		 2077
#define INTRO_GATEMOB2		 2077

//	재접속시에 서버접속 스위치
HTbool	m_bIntro_RestartConnect;

extern CHTWindowManager* g_CGame;

CHTIntroManager::CHTIntroManager()
{
	//	캐릭터 셀렉트 단에서 _USER_MESSAGE_EXIT 버튼을 클릭했는지 파악
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

	//	미리 한번 셋팅을 해야 원활하게 가동되는것 같다.
	RECT rRect = g_CGame->CHTApplication::GetScreenRect();
	//	Character Total Number
	m_iCharNum				= 0;
	//	D3D Render Sw
	m_b3DRender				= HT_FALSE;
	//	UI Render Sw
	m_bUIRender				= HT_TRUE;
	//	얼굴 줌/인
	m_bFaceZoominSw			= HT_FALSE;

	m_bCharSelectZoomInSw	= HT_FALSE;						//	캐릭터중 한명을 줌인 했냐?
	m_bCharDeleteSw			= HT_FALSE;						//	캐릭터 삭제 스위치
	m_dwErrorCheckDelayTime = 2000;							//	메시지 기다려 주는 시간

	m_bZoneServerConnected_ForIntro			= HT_FALSE;
	m_bZoneServerConnected_ForMainGame		= HT_TRUE;
	m_bZoneServerDisConnected_ForMainGame	= HT_FALSE;
	m_bZoneServerDisConnected_ForLoginFaild	= HT_FALSE;

	m_nSelectedCharNo		= 0;

	m_bServerDisconnectSw	= HT_FALSE;

	m_iScreenWidth			= 1024;
	m_iScreenHeight			= 768;

	// 해상도 추출
	m_iScreenWidth	= g_pEngineHandler->HT_iGetScreenWidth();
	m_iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();

	//현재 해상도가 저해상도(800*600)일 경우 저해상도 다이알로그로 띄우도록 셋팅
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

	//	애니매이션 인덱스
	m_iAnimationIndex = 0;
	//	현재 접속할 서버
	m_iCurServerIndex = 1;

	//	렌더 없이 바로 넘어가므로, 한번 그려준다.
	this->HT_hrRender();

	//	생성한 캐릭터 이름
	m_strNewCharacterName.HT_hrCleanUp();

	//	이름난에 Display용 String
	m_strIntroMessage.HT_hrCleanUp();
	m_strIntroMessage_Display.HT_hrCleanUp();

	m_nNewCharacterModelID	= -1;
	for( HTint i=0 ; i<3 ; i++ )
		m_nExistCharacterModelID[i] = -1;

	m_bErrorCheckSw = HT_FALSE;

	//  설명 : 빌링 서버 받은 결과
	//	일단은 응답을 참으로 받은 상태로 설정해둔다.
	g_bReciveBillingServer = HT_TRUE;
	//	자동로그인이 아닐때만
	if( g_byReStartCode == 0 )
        g_strLoginID.HT_hrCleanUp();
	g_iLoginResultID = 0;
	g_bPCRoomEventWndLogo = HT_FALSE;
	g_dwMyEvent = 0;

	//	카메라 이동상황을 체크해줌
	g_bCameraMove = HT_FALSE;

	//	일본일때 캐릭명이나 길드이름으로 불가한 파일 로딩
	if( g_iInationalType == INATIONALTYPE_JAPEN )
        HT_g_LoadNotCharAndGuildName();

	// Tantra V3 UI 적용
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

	//	리스타트일때는 여기를 거치면 안된다.
	if( g_byReStartCode == 0 )
	{
		CHTString szMessage;
		this->HT_hrSetMessage( eMsgLogInInputID, &szMessage );
		g_poWebLogIn = new CHTWebLogIn;
		this->HT_vSetURL();

		//	로딩 이미지를 로드한다.
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
	//	재시작일때만 카메라 캐릭셀릭까지 셋팅해준다.
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

	//	서버셀렉트에서 존서버에 접속 요청
	m_bReqConnectServerInSerSel = HT_FALSE;
	//	재접속시에 서버접속 스위치
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
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,0.9f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 185, 176, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_LOGINBOX, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_LOGINBOX, 2, 25, 55, 175, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,0.9f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 50, 176, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_LOGINBOX, 2 );
	//	Set Enter Button
	g_cUIManager->HT_SetButtonEnterOn( _DIALOG_LOGINBOX, 2 );
	//	Edit ID
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_LOGINBOX, 3, 0, 135, 65, 140, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroID, &strMessage, _T(""), _T("") );	//	아이디
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 43, 65, 70, 19 );
	//	Edit Password
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_LOGINBOX, 4, 0, 135, 100, 140, 19 );
	g_cUIManager->HT_SetModeEditBoxControl( _DIALOG_LOGINBOX, 4, 1 );
	g_cUIManager->HT_SetScriptMessage( eMsgIntroPassWord, &strMessage, _T(""), _T("") );	//	비밀번호
	g_cUIManager->HT_AddLabelControl( _DIALOG_LOGINBOX, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 43, 99, 70, 19 );
	//	ID 기억하기
	g_cUIManager->HT_SetScriptMessage( eMsgIntroIDsave, &strMessage, _T(""), _T("") );	//	ID 기억하기
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
	//	Label fors_debug 혼딜朞嶝륩蛟포 맣냥璣冷콱돨쥼寧곕
	//g_cUIManager->HT_SetScriptMessage( eMsgIntroSelectServer, &strMessage, _T(""), _T("") );	//	서버선택
	//g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 10, 130, 17 );
	//	Button Cancel
    g_cUIManager->HT_AddButtonControl( _DIALOG_SERVERSELECT, 1, 25, 180, 338, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
	g_cUIManager->HT_AddLabelControl( _DIALOG_SERVERSELECT, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 339, 70, 23 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SERVERSELECT, 1 );
	//	Button OK
	g_cUIManager->HT_AddButtonControl( _DIALOG_SERVERSELECT, 2, 25, 50, 338, 26, 27 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
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
			//strServerName.HT_szFormat( "원활" );
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
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgCharInfoTitle, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 66, 9, 155, 17 );//캐릭터 정보
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, sMsgAddressName, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 40, 78, 17 );//이름
	//	Label Level Name
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 11, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 65, 180, 17 );
	//	Label My God Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntorTrimuriti, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 104, 78, 17 );//주신
	//	Label My God
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 13, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 130, 180, 17 );
	//	Label Chakra
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 168, 78, 17 );//차크라
	//	Label Chakra 1_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroMuscleChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 194, 106, 17 );//근육의차크라
	//	Label Chakra 2_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroNerveChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 220, 106, 17 );//신경의차크라
	//	Label Chakra 3_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroheartChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 246, 106, 17 );//심장의차크라
	//	Label Chakra 4_1
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroSoulChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,0.8f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 271, 106, 17 );//정신의차크라
	//	Label Chakra 1_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 19, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 194, 59, 17 );
	//	Label Chakra 2_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 20, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 220, 59, 17 );
	//	Label Chakra 3_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 21, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 246, 59, 17 );
	//	Label Chakra 4_2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 22, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 271, 59, 17 );
	//	Label Connect Position Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 0, eMsgIntroSavePos, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 103, 311, 78, 17 );//저장위치
	//	Label Connect Position
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 24, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 54, 338, 180, 17 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 1, 25, 200, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f),195, 383, 70, 23 );//취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERINFO1, 1 );
	//	Button OK
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 2, 25, 30, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25, 383, 70, 23 );//확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERINFO1, 2 );
	//	Button Del Char
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERINFO1, 3, 25, 115, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERINFO1, 3, eMsgCommonDelete, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 383, 70, 23 );//삭제
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
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 685, 382, 70, 23 );//취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARACTERCREATE, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARACTERCREATE, 2, 25, 560, 382, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 555, 382, 70, 23 );//확인
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
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroCreateNewChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 73, 6, 145, 20 );//새캐릭터만들기
	//	Label 종족
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, sMsgAddressTribe, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 41, 80, 14 );//종  족
	//	Label 종족2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 12, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 65, 103, 17 );
	//	Label 종족 설명
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroExplainTribe, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 108, 80, 14 );//종족설명
	//	Label 종족 설명 2
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_CHARACTERCREATE, 14, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 37, 137, 213, 88 );
	//	Label 얼굴 선택
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgSelectFace, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 250, 80, 14 );//얼굴선택
	//	Label 얼굴 선택 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 16, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f),92, 276, 103, 17 );
	//	Label 머리 선택
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgFaceHair3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 101, 315, 80, 14 );//머리선택
	//	Label 머리 선택 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 18, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 339, 103, 17 );
	//	Label Title
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroCreateNewChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 580, 6, 145, 19 );//새캐릭터만들기
	//	Label 종족
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroInputName, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 614, 59, 80, 14 );//이름입력
	//	Label 종족
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 614, 146, 80, 14 );//차크라
	//	Label 근육의 차크라
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroMuscleChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 178, 106, 18 );//근육의 차크라
	//	Label 신경의 차크라
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroNerveChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 214, 106, 18 );//신경의 차크라
	//	Label 심장의 차크라
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroheartChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 246, 106, 18 );//심장의 차크라
	//	Label 정신의 차크라
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroSoulChakra, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 277, 106, 18 );//정신의 차크라
	//	Label 스키스 포인트
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 0, eMsgIntroServicePoint, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 554, 310, 106, 18 );//서비스 포인트
	//	Label 근육의 차크라2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 25, _T("11"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 178, 60, 18 );
	//	Label 신경의 차크라2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 26, _T("22"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 214, 60, 18 );
	//	Label 심장의 차크라2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 27, _T("33"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 246, 60, 18 );
	//	Label 정신의 차크라2
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 28, _T("44"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 277, 60, 18 );
	//	Label 스비스 포인트
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARACTERCREATE, 29, _T("55"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 675, 310, 60, 18 );

	//	[Input Jumin Number]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_INPUTJUMINNO, _T(""), 290, 300, g_cIntroManager->HT_hrIntro_InputCheckForJuminNo, 0 );
    g_cUIManager->HT_MoveWindow( _DIALOG_INPUTJUMINNO, 458, 212 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_INPUTJUMINNO, 0, 32, 0, 0 );

	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroDeleteChar, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 7, 150, 19 );//캐릭터삭제
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroExplain, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 104, 54, 84, 14 );//설 명
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 0, eMsgIntroResidentNumber, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 104, 196, 84, 14 );//주민등록번호
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 5, eMsgIntroExplain01, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 40, 83, 210, 84 );//삭제를 원하시면 주민등록번호를 입력하시고 확인을 눌러주세요
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INPUTJUMINNO, 5, 7 );
	//	Button Cancel
	g_cUIManager->HT_AddButtonControl( _DIALOG_INPUTJUMINNO, 1, 25, 180, 271, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 1, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 271, 70, 23 );//취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INPUTJUMINNO, 1 );
	//	Button OK
 	g_cUIManager->HT_AddButtonControl( _DIALOG_INPUTJUMINNO, 2, 25, 50, 271, 26, 27 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INPUTJUMINNO, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 45, 271, 70, 23 );//확인
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
	//	첫번째 만다라 지역
	g_cUIManager->HT_AddButtonControl( _DIALOG_3MANDARAVILLAGE, 1, 16, 0, 10, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_3MANDARAVILLAGE, 1, eMsgPortalExtraMandara1, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 13, 194, 19 );//Create Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_3MANDARAVILLAGE, 1 );
	//	두번째 만다라 지역
	g_cUIManager->HT_AddButtonControl( _DIALOG_3MANDARAVILLAGE, 2, 16, 0, 35, 17, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_3MANDARAVILLAGE, 2, eMsgPortalExtraMandara2, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 38, 194, 19 );//Select Character
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_3MANDARAVILLAGE, 2 );
	//	세번째 만다라 지역
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

	//	인트로 맵 / 전체 리소스 불러오기
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

	//	북두성군
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

	//	전체 로딩 프로그래서가 끝났다면
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

		//	캐릭터리스트에 의거한 캐릭터를 생성
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

	//	로딩이미지 랜더1
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.1f );

	//	메인게임 리소스를 로딩한다.
	g_cLoading->HT_hrLoadMainResources( g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER );

	//	로딩이미지 랜더5
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.9f );

	/*
	//	플로킹 기능(하을을 나는 매)을 셋팅한다.
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

	//	로딩이미지 랜더5
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 1.0f );

	//	최초 접속 지역
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
// D : UI관련 데이터 업데이트
// R : HT_TRUE/HT_FALSE
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrUpdate( HTfloat fElapsedTime )
{
	//	_USER_MESSAGE_EXIT 가 셋팅되었는지 판단
	if( m_bIntro_User_message_Exit )
	{
		//	인트로용 리소스를 다 지운다.
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
	//	메시지 뛰어 주는 시간체크
	this->HT_vUpdate_MsgDisplayTimeCheck();
	//	서버 연결 상태 체크 스케쥴러
	this->HT_vUpdate_ServerConnectCheck();
	//	서버와 연결이 끊어졌을때 연결끊고 나가기
	this->HT_vUpdate_DisconnectServer();
	//	애니매이션 체크
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
// D : UI관련 데이터 렌더링
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
			// 텍스트를 화면의 가운데로 정렬
			HTvector3 vecMsgText;
			vecMsgText = HTvector3( (m_iScreenWidth - g_pEngineHandler->HT_iGetTextWidth( HT_FONT_GULIM_12, m_strMeg.HT_szGetString() ))/2.0f+20.0f, (m_iScreenHeight-696.0f) + 600.0f, 0.0f );
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strMeg.HT_szGetString(), vecMsgText, HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
		}

		//	캐릭터 이름 표시
		//	캐릭터중 한명을 줌인 했을때는 표시안함
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

	//	IME 처리기
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
// 소위 말하는 타임/서버접속체크 스케쥴러
//-----------------------------------------------------------------------------
//	Server Status Check
HTvoid CHTIntroManager::HT_vUpdate_ServerConnectCheck()
{
	//	서버가 연결 됐을 때
	if( g_pNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
	{
		//	서버 셀렉터 후 제일처음 존서버 연결됐을 때
		if( !m_bZoneServerConnected_ForIntro )
		{
			//	존서버 커넥트 확인
			m_bZoneServerConnected_ForIntro = HT_TRUE;
			//	[대표] 존서버로 이동
			this->HT_vCSP_Request_MOVE_ZONE_SERVER( 0x01 );
		}
		//	캐릭터 셀렉트 후 메인게임과 연결됐을 때
		if( !m_bZoneServerConnected_ForMainGame )
		{
			m_bZoneServerConnected_ForMainGame = HT_TRUE;
			//	[해당]	존서버로 이동
			this->HT_vCSP_Request_MOVE_ZONE_SERVER( 0x02 );
		}
	}
	//	서버가 끊어 졌을 때
	else if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
	{
		//	LoginFaild DisConnect Setting
		if( m_bZoneServerDisConnected_ForLoginFaild )
		{
            m_bZoneServerDisConnected_ForLoginFaild = HT_FALSE;
			m_bZoneServerConnected_ForIntro = HT_FALSE;
		}

		//	DisConnect 셋팅 들어왔을 때
		if( m_bZoneServerDisConnected_ForMainGame )
		{
			m_bZoneServerDisConnected_ForMainGame = HT_FALSE;
			//	서버와 재 연결
			g_pNetWorkMgr->Connect( g_strZoneServerIP, g_iZoneServerPort );
			//	메인게임 연결 셋팅해줌
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

	//	카메라 이동이 정지했을때 셋팅
	if( g_bCameraMove == HT_FALSE )
	{
		g_cUIManager->HT_ShowWindow( m_iShowWinNo );
		
		//	Foucs 맞춰주기
		if( m_iShowWinNo == _DIALOG_LOGINBOX )
		{
			// 로그인 저장모드인지 체크하여 로그인 에디터박스의 내용을 모두 지워준다.
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
			// 로그인 에디터박스의 내용을 모두 지워준다.
			g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_INPUTJUMINNO, 3, "");
			g_cUIManager->HT_SetTextEditBoxControl(_DIALOG_INPUTJUMINNO, 4, "");
            g_cUIManager->HT_FocusOnEditBoxControl( _DIALOG_INPUTJUMINNO, 3 );
		}

		m_iShowWinNo = 0;
	}
}
//	메시지 뛰어 주는 시간체크
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


//	입력 메세지 처리
//	Login Box
void CHTIntroManager::HT_hrIntro_InputCheckForLogin(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button 이 들어 왔을때
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
			//	_USER_MESSAGE_EXIT 셋팅
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
				//	로그인 서버가 없어졌고 웹에서 인증하므로 여기서 로그인 불러준다.
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
				//	세이브된 파일을 지운다
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
		//	Msg Button 이 들어 왔을때
		//	Cancel
		if( iTargetID == 1 )
		{
			if( g_cIntroManager->m_iLoadCharDataSequence == -1 )
			{
				g_pEngineHandler->HT_hrPlaySound( 33523, 1 );	// Click Sound
				g_cIntroManager->m_bErrorCheckSw = HT_FALSE;
				g_cIntroManager->HT_vCSP_Request_CHAR_LOGOUT();
				g_cIntroManager->m_strID = g_cIntroManager->m_strSaveID.HT_szGetString();
				//	IME String Init 일단 임시로 이렇게 해두고 나중에 다시 수정하자
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
				g_cImeMgr.InputString();
			}
		}
		//	OK
		else if( iTargetID == 2 )
		{
			if( g_cIntroManager->m_iLoadCharDataSequence == -1 )
			{
				//	 최초 서버에 접속
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
				//	 최초 서버에 접속
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
	//	Msg Button 이 들어 왔을때
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	만약 만다라 마을 선택 윈도우가 팝업되어 잇다면 지워준다.
		if( g_cUIManager->HT_isShowWindow( _DIALOG_3MANDARAVILLAGE ) )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_3MANDARAVILLAGE );
			return;
		}

		//	Cancel
		if( iTargetID == 1 )
		{
			//	캐릭터 셀렉트 전체화면
			g_cIntroManager->HT_hrCharSelect();
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	블럭된 캐릭터 스킵
			if( g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.byGMStatus == 0x01 )
			{
				// 이 캐릭은 블럭된 상태입니다.
				CHTString szMessage;
				HT_g_Script_SetMessage( eMsgCommonNoLoginChar, &szMessage, _T("") );
				g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				return;
			}

			HTbool	bMandraBoxSw = HT_FALSE;
			//	위치한 지역이 만다라 지역이면
			if( !g_bDevelopingMode )
			{
				if( g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA1ST ||
					g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA2ND ||
					g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo.LastZone == ZONE_MANDARA3TH )
				{
					//	만다라 마을이 여러개 셋팅되어 있다면
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
				//	캐릭터 데이타 전역으로 저장
				CopyMemory(&g_oMainCharacterInfo, &g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo, sizeof(S_CHARACTER_LIST));
				//	종족코드 보정해주기
				HTint iTribe;
				HT_ConvertTribeS2C( g_oMainCharacterInfo.snTribe, iTribe );
				g_oMainCharacterInfo.snTribe = iTribe;

				if( g_cIntroManager->HT_bIsCharInMandara() )
					g_wResentZoneServerID = ZONE_MANDARA1ST;

				g_iZoneServerPort		= g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
				g_strZoneServerIP	    = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;

				//	존서버 접속
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

			//	숫자입력 에디터 박스 지우기
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
	//	Msg Button 이 들어 왔을때
	if( iTarget == UI_TARGET_BUTTON )
	{
        //	Cancel
		if( iTargetID == 1 )
		{
			//	기존 캐릭터가 있으면 캐릭터 셀렉트 화면으로 넘어감
			if( g_cIntroManager->m_iCharNum != 0 )
			{
				g_cIntroManager->HT_hrCharSelect();
			}
			//	캐릭터가 없으면 에러메시지만 뛰어줌
			else
			{
				//	메시지 셋팅
				CHTString szMessage;
				HT_g_Script_SetMessage( eMsgCharacListNotExist, &szMessage, _T("") );
				g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			}
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	캐릭명으로 적절치 못한단어를 찿아냄
			g_cIntroManager->m_strNewCharacterName = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_CHARACTERCREATE, 3 );
			//	Request Create Character
			g_cIntroManager->HT_vCSP_Request_CHAR_CREATE();
		}
		//	종족 선택 Left
		else if( iTargetID == 3 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharSelect(_USER_MESSAGE_TRIBELEFT);
		}
		//	종족 선택 Right
		else if( iTargetID == 4 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharSelect(_USER_MESSAGE_TRIBERIGHT);
		}
		//	얼굴 선택
		else if( iTargetID==5 || iTargetID==6 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharFace( iTargetID );
		}
		//	머리 선택
		else if( iTargetID==7 || iTargetID==8 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharHair( iTargetID );
		}
		//	챠크라 포인트
		else if( iTargetID==9 || iTargetID==10 || iTargetID==11 || iTargetID==12 )
		{
			g_cIntroManager->HT_hrUserMsgNewCharServiceChakra( iTargetID );
		}
		//	챠크라 포인트 초기화
		else if( iTargetID==13 )
		{
			g_cIntroManager->HT_hrChakraInit();
		}
		////	코믹 모션
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
	//	Msg Button 이 들어 왔을때
	if( iTarget == UI_TARGET_BUTTON )
	{
        //	Cancel
		if( iTargetID == 1 )
		{
			//	캐릭터 셀렉트 전체화면
			g_cIntroManager->HT_hrCharSelect();
		}
		//	OK
		else if( iTargetID == 2 )
		{
			//	지울 캐릭터 주민 번호_앞자리
			if( g_iInationalType == INATIONALTYPE_KOREA )
			{
				g_cIntroManager->m_strCharJoominNoFront = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_INPUTJUMINNO, 3 );
			}
			else
			{
				g_cIntroManager->m_strCharJoominNoFront.HT_hrCleanUp();
			}
			//	지울 캐릭터 주민 번호_뒷자리
			g_cIntroManager->m_strCharJoominNoBack = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_INPUTJUMINNO, 4 );
			//	캐릭터 삭제
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
			//	메시지 셋팅
			CHTString szMessage;
			HT_g_Script_SetMessage( eMsgCharacListCannotCreate, &szMessage );
			g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
		}
	}
	//	Select Character
	else if( iTargetID == 2 )
	{
		//	기존 캐릭터가 있으면 캐릭터 셀렉트 화면으로 넘어감
		if( g_cIntroManager->m_iCharNum != 0 )
		{
			g_cIntroManager->HT_hrCharSelect();
		}
		//	캐릭터가 없으면 에러메시지만 뛰어줌
		else
		{
			//	메시지 셋팅
			CHTString szMessage;
			HT_g_Script_SetMessage( eMsgCharacListNotExist, &szMessage, _T("") );
			g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
		}
	}
	//	Select Server
	else if( iTargetID == 3 )
	{
		//	캐릭터 셀렉트 단에서 _USER_MESSAGE_EXIT 버튼을 클릭했는지 파악
		g_cIntroManager->m_bIntro_User_message_Exit = HT_TRUE;
	}
}
//	3 Mandara Village
void CHTIntroManager::HT_hrIntro_InputCheckFor3MandaraVillage(int iAction, int iTarget, int iTargetID)
{
	//	Msg Button 이 들어 왔을때
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
			//	캐릭터 셀렉트 전체화면
			g_cIntroManager->HT_hrCharSelect();
			CHTString strMessage;
			// 동시접속 제한인원이 초과되었습니다. 잠시후 다시 접속해 주십시오
			g_cIntroManager->HT_hrSetMessage( eMsgLogInOverMember, &strMessage );
			g_cIntroManager->HT_vIntro_SetShowMessage( strMessage, 5000 );
		}
		else
		{
			//	캐릭터 데이타 전역으로 저장
			CopyMemory(&g_oMainCharacterInfo, &g_cIntroManager->m_oSeverChar[g_cIntroManager->m_nSelectedCharNo].sCharInfo, sizeof(S_CHARACTER_LIST));
			//	종족코드 보정해주기
			HTint iTribe;
			HT_ConvertTribeS2C( g_oMainCharacterInfo.snTribe, iTribe );
			g_oMainCharacterInfo.snTribe = iTribe;
			//	커넥션타입, 캐릭터이름, 현재 존NO, IP, Port 다시 써야 하므로 전역으로 저장
			g_iZoneServerPort		= g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
			g_strZoneServerIP	    = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
			//	존서버 접속
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

	//	먼저있던것은 지움
	DeleteFile( "./system/SaveID.bin" );

	// Encoding : XOR을 사용해서 0은 1로 1은 0으로 바꾸는 바보같은 인코딩을 사용한다. 만사가 귀찬다 -_-;
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
// D : 애니매이션 체크
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
					// 서버 종족을 클라이언트 종족 코드로 변환
					HTint iTribe;
					HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );

					// 무기를 들었을때에 자해하는 자세가 아니라 올바른 자세로 서있는 동작을 하기 위해서
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
	//	로그인 딜레이 시간에는 작동안하게 함
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
// D : 카메라 컨트롤
// R : HT_OK/HT_FAIL
//-----------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrCameraUpdate( HTfloat fElapsedTime )
{
	//	카메라 셋팅
	g_cCamera.HT_vCameraUpdate( HTvector3( 0,0,0 ), HT_PI, fElapsedTime );

	return HT_OK;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrAutoLoginUpdate()
// D : 자동 로그인 체크
//-----------------------------------------------------------------------------
HTvoid
CHTIntroManager::HT_vAutoLoginUpdate()
{
	if( g_byReStartCode == 0 )
		return;

    //	로그인 단 처리
	if( m_iIntroStatus == GAMESEQUENCE_INTRO_LOADINTROMAP )
	{
		// 서버 선택 단계
		//m_iIntroStatus = GAMESEQUENCE_INTRO_LOGSERVERCONNECT;
	}
	//	서버 셀렉트단 처리
	if( m_iIntroStatus == GAMESEQUENCE_INTRO_INTROPLAY )
	{
		if( g_byReStartCode == 2 &&
			m_bIntro_RestartConnect == HT_FALSE )
		{
			//	재접속시에 서버접속 스위치
			m_bIntro_RestartConnect = HT_TRUE;
			//	이전에 선택한 서버그룹을 이용하여 선택한 서버이름을 알아온다.
			g_strSelectServerName = g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldName;

			g_pNetWorkMgr->Connect( g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldIP, g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].snWorldPort );
			CHTString szMessage;
			this->HT_hrSetMessage( eMsgLogInReqGameServer, &szMessage );
		}
	}
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrCharSelect()
// D : 3D화면으로 전환하고 [캐릭터 선택],[정보]다이알로그를 그린다.
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

			// 무기를 들었을때에 자해하는 자세가 아니라 올바른 자세로 서있는 동작을 하기 위해서
			//	종족코드 보정해주기
			HTint iTribe;
			HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );
            
			HTint iNormaIndex, iLeftIndex;
			for (HTint j=0 ; j<7 ; j++)
			{
				iNormaIndex = m_oSeverChar[i].sCharInfo.Equip[j].snIndex;
				iLeftIndex = 0;
				//	왼손 단검일때를 체크
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

	// 생성해 놓은 캐릭터가 있으면 캐릭터 선택화면으로, 없으면 캐릭터 생성화면으로
	if (m_iCharNum)		this->HT_hrCharSelect();
	else				this->HT_hrCharNew();
}
HTRESULT
CHTIntroManager::HT_hrCharSelect()
{
	m_bCharSelectZoomInSw = HT_FALSE;

	//	뉴캐릭터가 생성되어 있으면 지워야 한다.
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

	//이름 Label Level Name
	strString.HT_szFormat( "%s [%d]", m_oSeverChar[m_nSelectedCharNo].sCharInfo.szCharName, m_oSeverChar[m_nSelectedCharNo].sCharInfo.byLevel );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 11, strString.HT_szGetString() );
	//주신 Label My God
	if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_BRAHMA )
		this->HT_hrSetMessage( eMsgCommonTrimuritiBrahma, &strString);
	else if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_VISHNU )
		this->HT_hrSetMessage( eMsgCommonTrimuritiVishunu, &strString);
	else if( m_oSeverChar[m_nSelectedCharNo].sCharInfo.byTrimuriti == TRIMURITI_SIVA )																	//strTrimuriti = _T("시바");
		this->HT_hrSetMessage( eMsgCommonTrimuritiSiva, &strString);
	else
		this->HT_hrSetMessage( eMsgCommonNone, &strString);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 13, strString.HT_szGetString() );
	//	근육의차크라
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraMuscle );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 19, strString.HT_szGetString() );
	//	심장의차크라
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraHeart );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 21, strString.HT_szGetString() );
	//	신경의차크라
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraNerve );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 20, strString.HT_szGetString() );
	//	정신의차크라
	strString.HT_szFormat( "%d", m_oSeverChar[m_nSelectedCharNo].sCharInfo.snChakraSoul );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERINFO1, 22, strString.HT_szGetString() );
	//	위치한 지역 10 Label Connect Position
	switch( m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone )
	{
		case 1 : // 만다라 1차지역
			//HT_vSetMessage( eMsgCommonZoneMandara_1, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;
		case 18 :
			//HT_vSetMessage( eMsgCommonZoneMandara_2, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;
		case 19 :
			//HT_vSetMessage( eMsgCommonZoneMandara_3, &strString ); break;
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_1, &strString ); break;

		case 2 : // 만다라 2차지역
			this->HT_hrSetMessage( eMsgCommonZoneForBillPotal_2, &strString ); break;
		case 3 : // 만다라 던젼1층
		case 4 : // 만다라 던젼2층
			this->HT_hrSetMessage( eMsgCommonZoneMandaraDungeon, &strString ); break;
		case 5 : // 샴발라 던젼1층
		case 6 : // 샴발라 던젼2층
			this->HT_hrSetMessage( eMsgCommonZoneShambalaDungeon, &strString ); break;
		case 7 : // 지나 1차지역
		case 8 : // 지나 2차지역
		case 9 : // 지나 3차지역
			this->HT_hrSetMessage( eMsgCommonZoneJina, &strString ); break;
		case 10 : // 지나 4차지역(쿠루마)
			this->HT_hrSetMessage( eMsgCommonZoneTrimuriti, &strString ); break;
		case 11 : // 지나 5차지역(챠투랑가)
			this->HT_hrSetMessage( eMsgCommonZoneChatulangga, &strString ); break;
		case 12 : // 북두성군릉
			this->HT_hrSetMessage( eMsgCommonZoneBookDooTomb, &strString ); break;
		case 16 : // 요새전
			this->HT_hrSetMessage( eMsgCommonZoneArenaDurga, &strString ); break;
		case 17 : // 비류성
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

	//	뉴캐릭터 모델이이디 초기화
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
	//	캐릭터 종족 설명, 얼굴
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace );

	//	이름난에 Display용 String
	m_strIntroMessage.HT_hrCleanUp();
	m_strIntroMessage_Display.HT_hrCleanUp();

	//	IME String Init
	g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	g_cImeMgr.InputString();

	return HT_OK;
}

//-----------------------------------------------------------------------------
// HTRESULT						HT_hrSelectCharCreate()
// D : 초기 선택할수 있는 캐릭터들을 생성한다.
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

	//	생성시의 이펙트
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

	//	종족코드 보정해주기
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
// Network 함수
// D : 네트워크 함수들
// R : HT_void
//-----------------------------------------------------------------------------
//	로그인
HTvoid
CHTIntroManager::HT_vCSP_Request_LOGIN()
{
	//	개발 모드일때
	if( g_bDevelopingMode )
	{
		CHTString strPass;
		CHTString strLowerPass;
		//	자동로그인이 아닐때만 ID/PW 셋팅해준다.
		if( g_byReStartCode == 0 )
		{
			if( g_iInationalType == INATIONALTYPE_JAPEN )
				g_bDevelopingMode = HT_FALSE;

			g_strLoginID		= g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
			strPass				= g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 4 );
		}

		// by 충배 20050504 : 모든 패스워드는 대소문자를 구별하게 된다. 한국의 경우 MD5 형태를 사용하고,
		if( g_iInationalType == INATIONALTYPE_KOREA )	strLowerPass = strPass;
		else							                strLowerPass = _tcslwr( (HTtchar*)strPass );
		// by 충배 20050504 : 외국의 경우에는 이전 형식 그대로 사용하게 된다.
		//if ( g_iInationalType == INATIONALTYPE_KOREA )
		{
			//strLowerPass = strPass;
			g_strLgoinPasswordMD5 = strLowerPass.HT_strGetMD5();
		}
		//else
		{
			//strLowerPass = _tcslwr( (HTtchar*)strPass );
			//	MD+방식 변환
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
		//로그인 성공
		this->HT_vSCP_RESP_LOGIN();
		return;
	}
	else
	{
		//	자동로그인이 아닐때만 ID/PW 셋팅해준다.
		if( g_byReStartCode == 0 )
		{
			CHTString strLoginID = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 3 );
			if( g_strLoginID.HT_iStringCompare( strLoginID.HT_szGetString() ) == 0 )
			{
				//  빌링 서버 받은 결과
				if( g_bReciveBillingServer == HT_FALSE )
				{
					CHTString szMessage;
					// 당신의 계정은 기간이 만료되었습니다.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
					return;
				}
			}
			else
			{
				//  빌링 서버 받은 결과
				g_bReciveBillingServer = HT_TRUE;
			}
			g_strLoginID = strLoginID.HT_szGetString();
			m_strPassword =  g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_LOGINBOX, 4 );
			CHTString strPass( m_strPassword );
			CHTString strLowerPass;

			// by 충배 20050504 : 모든 패스워드는 대소문자를 구별하게 된다. 한국의 경우 MD5 형태를 사용하고,
			if( g_iInationalType == INATIONALTYPE_KOREA )	strLowerPass = strPass;
			else							                strLowerPass = _tcslwr( (HTtchar*)strPass );
			// by 충배 20050504 : 외국의 경우에는 이전 형식 그대로 사용하게 된다.
			//if ( g_iInationalType == INATIONALTYPE_KOREA )
			{
				//strLowerPass = strPass;
				g_strLgoinPasswordMD5 = strLowerPass.HT_strGetMD5();
			}
			//else
			{
				//strLowerPass = _tcslwr( (HTtchar*)strPass );
				//	MD+방식 변환
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

		// 로그인 아이디와 패스워드로 로그인 인증
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

		// 로그인이 가능할 때
		HTchar		cFailCause[1024];
		ZeroMemory(cFailCause, sizeof(HTchar)*1024);

		if (g_poWebLogIn)
		{
			if (g_poWebLogIn->HT_bGetLogInEnable())
			{	
				// 메세지 표시
				this->HT_hrSetMessage( eMsgLogInReqWeb, &szMessage );
				this->HT_vIntro_SetShowMessage( szMessage.HT_szGetString(), 5000 );
				// 서버의 상태 및 동시접속자수 체크
				if (!g_poWebLogIn->HT_bGetServerStatusCheck())
				{
					// 서버가 다운되어 있을때 이유 표시
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
				// 로그인이 불가능할 때 로그인이 불가능한 이유 표시
				if( g_iInationalType == INATIONALTYPE_KOREA )
				{
					switch(g_iLoginResultID)
					{
						case 1001 : //	아이디 불일치
							this->HT_hrSetMessage( eMsgLogInInvalidUser, &szMessage);
							break;
						case 1002 : //	패스워드 불일치
							this->HT_hrSetMessage( eMsgLogInPasswdMismatch, &szMessage);
							break;
						case 1003 : //	게임블럭
							this->HT_hrSetMessage( eMsgLogInBlockID, &szMessage);
							break;
						case 1004 : //	서버점검
							this->HT_hrSetMessage( eMsgLogInEtc, &szMessage);
							break;
						case 1005 : //	회원탈퇴
							this->HT_hrSetMessage( eMsgLogInHomepageWithdraw, &szMessage);
							break;
						case 1006 : //	14세 미만
							this->HT_hrSetMessage( eMsgLogInNeedParentAgree, &szMessage);
							break;
						case 1007 : //	테스트서버 제한
							this->HT_hrSetMessage( eMsgLoginErrorTestServer, &szMessage);
							break;
						case 1008 : //	12세 미만
							this->HT_hrSetMessage( eMsgLoginErrorAgeLimit, &szMessage);
							break;
						case 1009 : //	18세 미만
							g_cUIManager->HT_SetScriptMessage( eMsgIntorLimitAge, &szMessage, _T(""), _T("") );	//	탄트라는 만15세 이상만 게임을 이용하실수 있습니다.
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
	//	메시지 안 보여주기
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

	//	2003119_월드 리스트를 이미 클라이언트가 확보하고 있기 때문에... 여기서는 월드리스트 요청이 아닌 결과값을 불러준다.
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

//	World List 셋팅
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
					iWorldCCUserNum = g_poWebLogIn->HT_iGetCCUserNum(i+g_gServerType, 0);// 만다라 마을을 기준으로 동접자 표시 변경
					iAliveWorldNum = g_poWebLogIn->HT_iGetAliveZoneNum(i+g_gServerType);
					
					if (!iAliveWorldNum)
						iBtnOnNum = 0;
					else
						iBtnOnNum = iWorldCCUserNum/100;

					//	최소 동접을 5칸 이상으로 유지해준다.
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
	//	0x01:로그인후,0x02:메인게임 들어가기 직전
	m_byMoveZoneServerPoint = byMoveZoneServerPoint;

	//-----------------------------------------------
	// 존 서버로 이동
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
	
	//	0x01:로그인후,0x02:메인게임 들어가기 직전
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

	//	메시지 셋팅
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
			//	메시지 안 보여주기
			this->HT_vIntro_SetHideMessage();
			//	최초 존서버 무브로 넘어왔으면 캐릭터 리스트 요청
			if( m_byMoveZoneServerPoint == 0x01 )
			{
				for( HTint i=0 ; i<3 ; i++ )
					m_nExistCharacterModelID[i] = -1;
				//캐릭터리스트를 달라꼬 요청
				this->HT_vCSP_Request_CHAR_LIST();
			}
			//	메인게임 들어가기전에 존서버 무브 요청햇으면
			else if( m_byMoveZoneServerPoint == 0x02 )
			{
				this->HT_vEnter_MainGame();
			}
			return;
		case REPLY_INVALID_USER :
			// 계정이 존재하지 않습니다.
			this->HT_hrSetMessage( eMsgLogInInvalidUser, &strMessage );
			break;
		case REPLY_INVALID_PASSWD :
			// 비밀번호가 틀림니다.
			this->HT_hrSetMessage( eMsgLogInPasswdMismatch, &strMessage );
			break;
		case REPLY_NO_RESPONSE	:
			// 서버에서 응답이 없습니다.
			this->HT_hrSetMessage( eMsgLogInNoResponse, &strMessage );
			break;
		case REPLY_ACCOUNT :
			// 월정액, 시간정액 등의 이유로 접속 불가합니다.
			this->HT_hrSetMessage( eMsgLogInBlockID, &strMessage );
			break;
		case REPLY_ALREADY_LOGIN :
			// 이미 로그인 되어 있습니다.
			this->HT_hrSetMessage( eMsgLogInAlreadyLogIn, &strMessage );
			break;
		case REPLY_NEED_LOGIN :
			// 로그인 되지 않은 사용자입니다.
			this->HT_hrSetMessage( eMsgLogInNeed, &strMessage );
			break;
	}

	if( strMessage.HT_nGetSize() != 0 )
	{
		//	메시지 셋팅
		this->HT_vIntro_SetShowMessage( strMessage, MESSAGE_DELAYTIME_SHORT );
		//	현재 서버와 연결 끊음
		g_pNetWorkMgr->DisConnect();
		//	LoginFaild DisConnect Setting
		m_bZoneServerDisConnected_ForLoginFaild	= HT_TRUE;
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_LIST()
{
	//	캐릭터 리스트 요청하기전에 캐릭터 값 초기화
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
	//	캐릭터 리스트 요청
	g_pNetWorkMgr->RequestCharList();
	
	CHTString szMessage;
	HT_g_Script_SetMessage( eMsgLogInReqCharacterList, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, 5000 );
}
HTvoid
CHTIntroManager::HT_vSCP_RESP_CHAR_LIST( char* pData )
{ 
	//	메시지 안 보여주기
	this->HT_vIntro_SetHideMessage();

	//	캐릭터 데이타를 셋팅
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

	//	캐릭터 리스트 받은 시점에서 캐릭터 셀렉트로 넘어가기전에 셋팅해야 할 부분들
	{
		//	포탈 ID 초기화
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

	//	적질치 못한 단어 걸러내기
	for( HTint i=0 ; i<NOTCHARANDGUILDNAME_COUNT ; i++ )
	{
		if( m_strNewCharacterName.HT_bFind( g_szNotCharAndGuildName[i] ) == HT_TRUE )
		{
			this->HT_hrSetMessage( eMsgCharacListInvalidName, &szMessage );
			this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_MIDDLE );
			return;
		}
	}

	//	일본에서의 캐릭명의 길이 따로 계산
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

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_Create_Character : %s", info->szCharName );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

	//	메시지 셋팅
	this->HT_hrSetMessage( eMsgCharacListReqCreate, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONGLONG );
}

HTvoid
CHTIntroManager::HT_vCSP_RESP_CHAR_CREATE( PS_SCP_RESP_CHAR_CREATE info )
{
	if( info->byResult == 0x00 )
	{
		g_pEngineHandler->HT_hrPlaySound( 33502, 1 );	// Click Sound

		this->HT_vIntro_SetHideMessage();		//	메시지 안 보여주기

		//	만들어진 캐릭터 생성하기
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
				//캐릭터리스트에 의거한 캐릭터를 생성
				this->HT_vExistCharCreate();
				return;
			}
		}		
	}
	else
	{
		// 메시지 셋팅
		CHTString strMsg;
		switch( info->byResult )
		{
			case REPLY_CHAR_CREATE_ALREADY_EXIST:	// 캐릭터 이미 존재
				HT_hrSetMessage( eMsgCharacListAlreadyExist, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHAR_FULL:		// 캐릭터 모두 생성
				HT_hrSetMessage( eMsgCharacListCannotCreate, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHR_CHAR_FAIL:	// 캐릭터이름 부적합
				HT_hrSetMessage( eMsgCharacListInvalidName, &strMsg );
				break;
			case REPLY_CHAR_CREATE_CHAKRA_OVER:		// 기초차크라오버
				HT_hrSetMessage( eMsgCharacListBasicChakraOver, &strMsg );
				break;
			default: // REPLY_CHAR_CREATE_FAIL		// 캐릭터 생성 실패
				HT_hrSetMessage( eMsgCharacListCreateFail, &strMsg );
				break;
		}

		this->HT_vIntro_SetShowMessage( strMsg, 5000 );
	}

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_Recive_Character : %d", info->byResult );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_REMOVE()
{
	//	메시지 셋팅
//	this->HT_vIntro_SetShowMessage( _T("현재 캐릭터를 삭제할수 없습니다. "), MESSAGE_DELAYTIME_SHORT );
//	return;

	PS_CSP_REQ_CHAR_REMOVE info = HT_NULL;
	info = new S_CSP_REQ_CHAR_REMOVE;
	if (!info) return;

	CHTString::HT_hrStringCopy( info->szCharName, m_oSeverChar[m_nSelectedCharNo].sCharInfo.szCharName, SZNAME_LENGTH );
	CHTString strTemp;
	//	중국은 주민 앞자리를 안쓰니까 __ 0으로 보낸다.
	if( g_iInationalType == INATIONALTYPE_KOREA )	info->ssn1 = atoi( m_strCharJoominNoFront.HT_szGetString() );
	else											info->ssn1 = 0;
	//	주민 뒷자리에 아무것도 없으면 Skip
	if( m_strCharJoominNoBack.HT_bIsEmpty() )
		return;
	info->ssn2 = atoi( m_strCharJoominNoBack.HT_szGetString() );
	g_pNetWorkMgr->RequestCharDeletion( info );

	HT_DELETE( info );

	//	메시지 셋팅
	CHTString szMessage;
	this->HT_hrSetMessage( eMsgCharacListReqDelete, &szMessage );
	this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONGLONG );

}
HTvoid
CHTIntroManager::HT_vCSP_RESP_CHAR_REMOVE( PS_SCP_RESP_CHAR_REMOVE info )
{
	if( info->byResult == 0x00 )
	{
		this->HT_vIntro_SetHideMessage();		//	메시지 안 보여주기
		g_pEngineHandler->HT_hrPlaySound( 33503, 1 );	// Click Sound

		//	삭제된 캐릭터 모델 삭제하기
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
		//	메시지 셋팅
		CHTString strMsg;
		HT_hrSetMessage( eMsgCharacListDeleteFail, &strMsg ); // 캐릭터 삭제 실패
		this->HT_vIntro_SetShowMessage( strMsg, MESSAGE_DELAYTIME_MIDDLE );
	}
}

HTvoid
CHTIntroManager::HT_vCSP_Request_CHAR_SELECT()
{
	// 만약에 현재 연결 된 서버와 IP, PORT가 같으면 존 서버 이동을 하지 않고 바로 처리 된다.
	if( g_strZoneServerIP.HT_iStringCompare( g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].szWorldIP ) == 0 &&
		g_iZoneServerPort == g_oWorldList[g_iConnectServerGroupIndex][m_iCurServerIndex].snWorldPort )
	{
		this->HT_vEnter_MainGame();
	}
	else
	{
		//	현재 서버와 연결 끊음
		g_pNetWorkMgr->DisConnect();
		//	DisConnect Setting
		m_bZoneServerDisConnected_ForMainGame = HT_TRUE;
		//	메시지 셋팅
		CHTString szMessage;
		this->HT_hrSetMessage( eMsgLogInReqZoneServer, &szMessage );
		this->HT_vIntro_SetShowMessage( szMessage, MESSAGE_DELAYTIME_LONG );
	}
}

//	게임으로 이동한다.
HTvoid CHTIntroManager::HT_vEnter_MainGame()
{
	//	인트로용 리소스를 다 지운다.
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

//	서버와 연결이 끊어졌을때 연결끊고 나가기
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

//	 최초 서버에 접속
HTvoid CHTIntroManager::HT_vEnter_FirstServer()
{
	//	서버셀렉트에서 존서버에 접속 요청했으면 스킵
	if( m_bReqConnectServerInSerSel )
		return;

	// Click Sound
	g_pEngineHandler->HT_hrPlaySound( 33523, 1 );
	//  빌링 서버 받은 결과
	//	ReStart가 아닐경우에
	if( g_byReStartCode == 0 )
	{
		if( g_bReciveBillingServer == HT_FALSE )
		{
			CHTString szMessage;
			// 당신의 계정은 기간이 만료되었습니다.
			if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
					g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			return;
		}
	}

	//	실제 게임 모드에서는 서버 겟수 체크
	if( !g_bDevelopingMode )
	{
		if( g_iConnectServerGroupIndex>=g_iWorldNum)
			return;
	}

	//	서택한 서버 이름
	g_strSelectServerName = g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].szWorldName;

	//	서버 접속 전에 동시접속 제한 인원 초과 되었는지 체크하는것도 넣을 필요가 있을듯
	//	차후에 작업하자

	//	Connect Server
	if( g_bDevelopingMode )     g_cIntroManager->m_iCurServerIndex = 1;
	else						g_cIntroManager->m_iCurServerIndex = 6;
	g_pNetWorkMgr->Connect( g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].szWorldIP, 
							g_oWorldList[g_iConnectServerGroupIndex][g_cIntroManager->m_iCurServerIndex].snWorldPort );
	//	서버에 접속을 요청했다는 메시지 출력

	//	서버셀렉트에서 존서버에 접속 요청
	m_bReqConnectServerInSerSel = HT_TRUE;
}
//	TantraParam 변조했는지 확인하기.
HTvoid
CHTIntroManager::HT_vCheckTantraParam()
{
	HTint iTempValue;
	HTbool	bTrue = HT_FALSE;
	//	it seems strange
	//	3007	발루카 만트라(무실패 공격)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3007, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}
	//3008	바루나 포스(공성 증가) 1000
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3008, 1, &iTempValue ) )
	{
		if( iTempValue != 1000 )		bTrue = HT_TRUE;
	}
	//3022	사마테(인듀어) 200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3022, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3030	마야트(리턴 투 라이프)	200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3030, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3102	파라카(오라쉴드)	200
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3102, 1, &iTempValue ) )
	{
		if( iTempValue != 200 )			bTrue = HT_TRUE;
	}
	//3043	나우티(스크림)	800
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3043, 1, &iTempValue ) )
	{
		if( iTempValue != 800 )			bTrue = HT_TRUE;
	}
	//3026	아마다 카스(크러싱 블로우)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3026, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}
	//3042	사비트리 포스(사비트리 포스)	1000
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3042, 1, &iTempValue ) )
	{
		if( iTempValue != 1000 )		bTrue = HT_TRUE;
	}
	//3041	가타나(밀어내기)	300
	if( g_pParamMgr->HT_bGetPCSkillReadyTime( 3041, 1, &iTempValue ) )
	{
		if( iTempValue != 300 )			bTrue = HT_TRUE;
	}

	if( bTrue == HT_TRUE )
	{
        MessageBox( NULL, _T("It seems strange!!!"), _T("error"), MB_OK );
		//	_USER_MESSAGE_EXIT 셋팅
		m_bIntro_User_message_Exit = HT_TRUE;
	}
//3009	타르카(페인킬러)	400
//3011	비즈사이(아마다카스2) 300
//3013	그라브	300
//3021	스탐(스턴)	300
//3023	프로스아나(타운트) 300
//3024	쿤달리니라이징(쿤달리니라이징) 200
//3025	아로카킨(버저킹)	200
//3027	프라베자	300
//3028	프로스아나 바티아(지역 타운트)	1000
//3029	아자카(피어)	1000
//3031	우마 사마테(파티 사마테)	200
//3032	쉴딩_카르만	200
//3058	카틴	300
//3059	우타	300
//3061	부우캄파(퀘이크)	800
//3103	얀카나(하이딩)	2000
//3104	눈 찌르기(암바카 비자티)	200
//3122	차야(그림자 잡기)	600
//3160	아킬라(암살)	400
//3162	프라니카(가이디드 애로우)	745
//3229	인드라 잘라(이동속도증가)	200
//3241	카도라이(피뻥튀기)	200
//3261	사무다바(부활)	200
//3214	스칸다 퓨리(공격속도 증가)	200
}
//	After Login Time Check
HTvoid
CHTIntroManager::HT_vAfterLoginTimeCheck()
{
	DWORD dwPassTime = timeGetTime();
	//	After Login Time Check
	if( dwPassTime > m_dwIntro_LoginTimeCheck+300000 )
	{
		// 로그인 시간이 초과하여 게임을 종료합니다.
		CHTString strMsg;
		HT_hrSetMessage( eMsgCommonExcessLoginTime, &strMsg );
		MessageBox( NULL, strMsg, "error", MB_OK );
		//	_USER_MESSAGE_EXIT 셋팅
		g_cIntroManager->m_bIntro_User_message_Exit = HT_TRUE;
	}
}

///////////////////////////////////////////////////////////////////////////////
// 사용자 메세지
///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// HTvoid						HT_vLButtonDown(HTint iPosX, HTint iPosY)
// D : 마우스 LBUTTON DOWN시
//-------------------------------------------------------------------------
HTRESULT
CHTIntroManager::HT_hrLButtonDown(HTint iPosX, HTint iPosY)
{
	if( m_bErrorCheckSw == HT_TRUE )	return HT_OK;
	return HT_OK;
}

//-------------------------------------------------------------------------
// HTRESULT						HT_hrLButtonUp(HTint iPosX, HTint iPosY)
// D : 마우스 LBUTTON UP시
//-------------------------------------------------------------------------
HTRESULT CHTIntroManager::HT_hrLButtonUp(HTint iPosX, HTint iPosY)
{
	//	3D 화면일때
	if (m_b3DRender)
	{
		//	어떤 캐릭도 선택 안했을 때
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
						//	캐릭터중 한명을 줌인 했냐?
						m_bCharSelectZoomInSw = HT_TRUE;
						//	Show Window
						this->HT_vIntro_SetShowWindow( _DIALOG_CHARACTERINFO1, 1500 );
						//	캐릭터 정보 뛰어주기
						this->HT_vCharSelect_SetInfo();
						if( i==2 && m_iScreenWidth==800 )
							g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERINFO1, (HTint)g_vecCharInfoWndPos[i].x-100, (HTint)g_vecCharInfoWndPos[i].y );
						else
							g_cUIManager->HT_MoveWindow( _DIALOG_CHARACTERINFO1, (HTint)g_vecCharInfoWndPos[i].x, (HTint)g_vecCharInfoWndPos[i].y );
						g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_CHAR1+m_nSelectedCharNo][0], 1, 0.93f);
						g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, g_fCameraPos[HT_INTRO_CAMERA_CHAR1+m_nSelectedCharNo][1], 1, 0.93f);
						
						//	종족코드 보정해주기
						HTint iTribe;
						HT_ConvertTribeS2C( m_oSeverChar[i].sCharInfo.snTribe, iTribe );

						HTint iLeftItem = 0;
						if( g_pEngineHandler->HT_bIsShortSword( m_oSeverChar[i].sCharInfo.Equip[3].snIndex ) )
							iLeftItem = m_oSeverChar[i].sCharInfo.Equip[3].snIndex;

						//	애니매이션 인덱스
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

	//	서버간 통신으로 메시지 체크하고 있으면
	if( m_bErrorCheckSw == HT_TRUE )
		return HT_OK;

	m_bSlideOn				= HT_FALSE;

	return HT_OK;
}

// NEW CHARACTER 버튼이 눌렸을 때 상태에 따른 정의
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
				//	메시지 셋팅
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
	//	캐릭터 종족 설명, 얼굴
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

	//	서비스 챠크라 빼기
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
	//	캐릭터 종족 설명, 얼굴
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
	//	캐릭터 종족 설명, 얼굴
	this->HT_hrUserMsgNewCharSelect_CharInfo( m_nNewCharacterTribe, m_nNewCharacterFace, HT_FALSE );
	return HT_OK;
}

//	캐릭터 종족 설명, 얼굴
HTvoid
CHTIntroManager::HT_hrUserMsgNewCharSelect_CharInfo( HTint nTribe, HTint nFace, HTbool bRadioInit )
{
	//	Label 종족
	CHTString strTemp;
	CHTString strExplain;
	switch( nTribe+1 )
	{
		case HT_ID_CHARACTER_NAGA:
			this->HT_hrSetMessage( eMsgCommonTribeNaga, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain002, &strExplain, _T(""), _T("") );	//	나가 족은 종족들 중에 최고의 공격력과 뛰어난 지구력을 지니고 있다.\n 단, 속도가 느리고 정교함이 떨어진다.
			break;
		case HT_ID_CHARACTER_ASURA:
			this->HT_hrSetMessage( eMsgCommonTribeAsura, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain003, &strExplain, _T(""), _T("") );	//	아수라 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
			break;
		case HT_ID_CHARACTER_YAKSA:
			this->HT_hrSetMessage( eMsgCommonTribeYaksha, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain004, &strExplain, _T(""), _T("") );	//	야크샤 족은 가장 빠르고 정확한 펀치를 날린다. 공격력은 강하지 않지만 초원에서 다져진 지구력은 그들을 더욱 강력하게 만든다.
			break;
		case HT_ID_CHARACTER_DEVA:
			this->HT_hrSetMessage( eMsgCommonTribeDeva, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain005, &strExplain, _T(""), _T("") );	//	데바족은 물리적인 능력에서는 어떤 종족보다 약하지만 정신적인 면에서는 그 어떤 종족보다 강하다.
			break;
		case HT_ID_CHARACTER_KIMNARA:
			this->HT_hrSetMessage( eMsgCommonTribeKimnara, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain006, &strExplain, _T(""), _T("") );	//	킨나라 족은 종족들 중에 최고의 공격력과 뛰어난 지구력을 지니고 있다.\n 단, 속도가 느리고 정교함이 떨어진다.
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			this->HT_hrSetMessage( eMsgCommonTribeRakshasa, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain007, &strExplain, _T(""), _T("") );	//	라크샤사 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			this->HT_hrSetMessage( eMsgCommonTribeGandharva, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain008, &strExplain, _T(""), _T("") );	//	간다르바 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
			break;
		case HT_ID_CHARACTER_GARUDA:
			this->HT_hrSetMessage( eMsgCommonTribeGaruda, &strTemp);
			g_cUIManager->HT_SetScriptMessage( eMsgIntroExplain009, &strExplain, _T(""), _T("") );	//	가루다 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
			break;
		default:
			this->HT_hrSetMessage( eMsgCommonNone, &strTemp);
			break;
	}
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 12, strTemp.HT_szGetString() );
	//	Label 종족 설명
	g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_CHARACTERCREATE, 14, strExplain.HT_szGetString() );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_CHARACTERCREATE, 14, 7 );
	//	Label 얼굴 선택
	this->HT_hrSetMessage( eMsgFace, &strTemp);
	strTemp.HT_szFormat( strTemp, m_nNewCharacterFace );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 16, strTemp.HT_szGetString() );
	//	Label 머리 선택
	this->HT_hrSetMessage( eMsgHead, &strTemp);
	strTemp.HT_szFormat( strTemp, m_nNewCharacterHair );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 18, strTemp.HT_szGetString() );
	//	챠크라 포인트
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][0] + m_byCharCreate_ChakraMuscle);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 25, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][1] + m_byCharCreate_ChakraNerve);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 26, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][2] + m_byCharCreate_ChakraHeart);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 27, strTemp.HT_szGetString() );
	strTemp.HT_szFormat("%d", g_iCharacterChacraPoint[nTribe][3] + m_byCharCreate_ChakraSoul);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 28, strTemp.HT_szGetString() );
	//	전체 포인트
	strTemp.HT_szFormat("%d", m_byCharCreate_ServiceChakraPoint );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_CHARACTERCREATE, 29, strTemp.HT_szGetString() );
}

// Intro 배경에 사용되는 FX 관리
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

	//	전체 포인트
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
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vSetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 카스트 계급
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
		// 지역
		case eMsgParamZoneNum:
		{
			switch( m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone )
			{
				case 1 : // 만다라 1차
				case 3 : // 만다라 던젼 1층
				case 5 : // 샴발라 던젼 1층
				case 7 : // 지나 1차
				case 18 : // 18번 존
				case 19 :
					pszParam->HT_szFormat( "%d", 1);	break;

				case 2 : // 만다라 2차
				case 4 : // 만다라 던젼 2층
				case 6 : // 샴발라 던젼 2층
				case 8 : // 지나 2차
					pszParam->HT_szFormat( "%d", 2);	break;

				case 9 : // 지나 3차
					pszParam->HT_szFormat( "%d", 3);	break;
			
				case 10 : // 지나 4차
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
	// 수드라 3급
	if( iBrahmanPoint <= _CHARAC_CAST_SUDRA_3_END )										
		return _CHARAC_CAST_SUDRA_3;
	// 수드라 2급
	else if ( _CHARAC_CAST_SUDRA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_2_END )
		return _CHARAC_CAST_SUDRA_2;
	// 수드라 1급
	else if ( _CHARAC_CAST_SUDRA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_1_END )
		return _CHARAC_CAST_SUDRA_1;
	// 바이샤 3급
	else if ( _CHARAC_CAST_VAISHA_3_START	<= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_3_END )
		return _CHARAC_CAST_VAISHA_3;
	// 바이샤 2급
	else if ( _CHARAC_CAST_VAISHA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_2_END )
		return _CHARAC_CAST_VAISHA_2;
	// 바이샤 1급
	else if ( _CHARAC_CAST_VAISHA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_1_END )
		return _CHARAC_CAST_VAISHA_1;
	// 크샤트리아 3급
	else if ( _CHARAC_CAST_KSHATRYA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_3_END )
		return _CHARAC_CAST_KSHATRYA_3;
	// 크샤트리아 2급
	else if ( _CHARAC_CAST_KSHATRYA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_2_END )
		return _CHARAC_CAST_KSHATRYA_2;
	// 크샤트리아 1급
	else if ( _CHARAC_CAST_KSHATRYA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_1_END )
		return _CHARAC_CAST_KSHATRYA_1;
	// 브라만 3급
	else if ( _CHARAC_CAST_BRAMAN_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_3_END )
		return _CHARAC_CAST_BRAMAN_3;
	// 브라만 2급
	else if ( _CHARAC_CAST_BRAMAN_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_2_END )
		return _CHARAC_CAST_BRAMAN_2;
	// 브라만 1급
	else if ( _CHARAC_CAST_BRAMAN_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_1_END )
		return _CHARAC_CAST_BRAMAN_1;
	// 아바타라 3급
	else if ( _CHARAC_CAST_AVATARA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_3_END )
		return _CHARAC_CAST_AVATARA_3;
	// 아바타라 2급
	else if ( _CHARAC_CAST_AVATARA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_2_END )
		return _CHARAC_CAST_AVATARA_2;
	// 아바타라 1급
	else if ( _CHARAC_CAST_AVATARA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_1_END )
		return _CHARAC_CAST_AVATARA_1;
	// 미정 3급
	else if ( _CHARAC_CAST_RESERVE_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_3_END )
		return _CHARAC_CAST_RESERVE_3;
	// 미정 2급
	else if ( _CHARAC_CAST_RESERVE_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_2_END )
		return _CHARAC_CAST_RESERVE_2;
	// 미정 1급
	else if ( _CHARAC_CAST_RESERVE_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_1_END )
		return _CHARAC_CAST_RESERVE_1;
	
	else
		return _CHARAC_CAST_NONE;
	
	//return m_oSeverChar[m_nSelectedCharNo].sCharInfo.
}

//	동접자 알아오기
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

// 캐릭터가 만다라 마을에 있는지 체크
HTbool
CHTIntroManager::HT_bIsCharInMandara()
{
	g_wResentZoneServerID = m_oSeverChar[m_nSelectedCharNo].sCharInfo.LastZone;

	if (g_wResentZoneServerID==_MANDARA1ST_1 ||
		g_wResentZoneServerID==_MANDARA1ST_2 ||
		g_wResentZoneServerID==_MANDARA1ST_3)	return HT_TRUE;
	return HT_FALSE;
}

//	만다라 마을의 동접 알아오기
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

