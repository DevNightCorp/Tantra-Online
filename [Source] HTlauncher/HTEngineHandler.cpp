#include "stdafx.h"
#include "HTEngineHandler.h"
#include "HTConfigSystem.h"
#include "HTMapSystem.h"
#include "HTResMgr.h"
#include "HTFXResMgr.h"
#include "HTObjResMgr.h"
#include "HTOption.h"
#include "oleauto.h"
#include "comutil.h"

#ifdef HT_IS_TANTRA_LAUNCHER
//#include "HTInterface.h"
#include "HTExtern.h"
#include "HTNPCSystem.h"
#include "HTNPCScriptMgr.h"		// 2003.5.14 선미
#endif

#include "..\HTUtilLib\HTPackFile.h"
#include "..\HT3DHeaven\HTEngineObj\HTObjCamera.h"

#define HT_FXDATA_TFX
//#define HT_FXRESOURCE_XML
#define		_ANCHOR_SCREEN_WIDTH	1024
#define		_ANCHOR_SCREEN_HEIGHT	768

#define		_LOAD_POINT_NUM			30

#define		_BGM_RAKSHASA			33530
#define		_BGM_ASURA				33531

#define		_LOAD_POINT_START		2

#define		_OBJECT_TYPE_PUBLIC		0
#define		_OBJECT_TYPE_SM			1
#define		_OBJECT_TYPE_GRASS		2

//#define		_LOAD_ASURA1			31
//#define		_LOAD_ASURA2			32
//#define		_LOAD_RAKSHASA1			33
//#define		_LOAD_RAKSHASA2			34
//#define		_LOAD_LOADING			35

#define		_LOAD_TYPE1				2
#define		_LOAD_TYPE2				3
#define		_LOAD_TYPE3				4
#define		_LOAD_TYPE4				5
#define		_LOAD_TYPE_NUM			4

#define		_LOADINGUI_SYS_FILEPATH			_T("resource\\UI\\LoadingUI.sys")
#define		_MAP_CFG_DIR					_T("resource\\map\\")
#define		_SPEC_FILEPATH					_T("system\\HTSpec.cfg")
#define		_CLIENT_TXL_FILEPATH			_T("system\\ClientRes.txl")
#define		_CLIENT_XML_FILEPATH			_T("system\\ClientRes.xml")
#define		_SYSTEM_DIR						_T("system\\")

#define HT_FORTWAR_MAP_ID 40016
#define HT_FORTWAR_GUILD_FLAG_RESID 18126

CHTEngineHandler* g_pEngineHandler = HT_NULL;

IHT3DMgr* g_pEngineMgr;		
HTtchar szWorkingPath[1000];

HTint HT_iSortObjByZ( const HTvoid* pvA, const HTvoid* pvB )
{
	HTfloat fDistA = g_pEngineMgr->HT_fGetDistanceFromCamera( *(HTint*)pvA );
	HTfloat fDistB = g_pEngineMgr->HT_fGetDistanceFromCamera( *(HTint*)pvB );
	if ( fDistA < fDistB ) return +1;
	if ( fDistA > fDistB ) return -1;

	return 0;
}

CHTEngineHandler::CHTEngineHandler()
{
	m_h3DDLL				= HT_NULL;
	m_pfnCreate3DMgr		= HT_NULL;
	m_pfnDestroy3DMgr		= HT_NULL;
	m_p3DMgr				= HT_NULL;
	m_pResMgr				= HT_NULL;	
	m_pFXPCResMgr			= HT_NULL;
	m_pFXMAPResMgr			= HT_NULL;
	m_pObjResMgr			= HT_NULL;
	m_pCfgSpec				= HT_NULL;

	m_vectorViewingObjs.clear();
	m_vectorUpdateObjs.clear();
	m_nObjs					= 0;
	m_nTerrainPolyCount		= 0;
	m_nModelPolyCount		= 0;
	m_nRenderObjs			= 0;
	m_nViewings				= 0;
	m_pMapSystem			= HT_NULL;
	m_bWorldLoaded			= HT_FALSE;
	m_bFading				= HT_FALSE;
	m_idCamera				= 0;
	m_idFontFPS				= 0;
	m_idFontHanbitNaru30	= 0;
	m_idFontGulim12			= 0;
	m_idFontGulim10			= 0;
	m_idSun					= 0;
	m_idMoon				= 0;
	m_idSubLight			= -1;
	m_idTerrain				= 0;

	m_idShadow				= 0;
	m_idSkyCloud			= 0;
	m_idSkyTerrain			= 0;
	m_idSky					= 0;
	m_idRain				= 0;
	m_idFog					= 0;
	m_idBGM					= 0;
	m_id2DSound				= 0;
	m_id3DSound				= 0;
	m_arridWater			= HT_NULL;
	m_iNumWater				= 0;
	m_fLifeTime				= 0.0f;
	m_fCenterRatio			= 0.0f;
	m_pTimer				= HT_NULL;
	m_fRenderTime			 = 0.0f;
	m_fUpdateTime			= 0.0f;
	m_fDebugTime			= 0.0f;
	m_fNowTimeInAllDay		= 0.0f;
	m_dwAllInitTimeStartTime = 0;
	m_eCurretTimeStatus		= HT_CURRENT_TIME_STATUS_DEFAULT;
	m_bUpdateTime			= HT_TRUE;
	m_fDayTime				= 0.0f;
	m_fNightTime				= 0.0f;
	m_fMorningStart			= 0.0f;
	m_fMorningEnd			= 0.0f;
	m_fEveningStart			= 0.0f;
	m_fEveningEnd			= 0.0f;
	m_fMorningFogStart		= 0.0f;
	m_fMorningFogEnd		= 0.0f;
	m_fNoonFogStart			= 0.0f;
	m_fNoonFogEnd			= 0.0f;
	m_fEveningFogStart		= 0.0f;
	m_fEveningFogEnd		= 0.0f;
	m_fNightFogStart		= 0.0f;
	m_fNightFogEnd			= 0.0f;
	m_fLODDistanceLow1		= 0.0f;
	m_fLODDistanceLow2		= 0.0f;
	m_fLODDistanceLow3		= 0.0f;
	m_fLODDistanceHigh1		= 0.0f;
	m_fLODDistanceHigh2		= 0.0f;
	m_fLODDistanceHigh3		= 0.0f;
	m_fLODDistanceFar		= 0.0f;
	m_fLODDistanceFarSM		= 0.0f;

	m_fTerrainLODDetail		= 0.0f;
	m_fTerrainTilingDistance = 0.0f;
	m_bTerrainDetailTexture = HT_FALSE;
	m_idMainCharacter		 = -1;
	m_idCharacterLight		= -1;
	m_pPackFileMgr			= HT_NULL;
	m_vPosition				= HTvector3( 0.0f, 0.0f, 0.0f );
	m_idWaterZoro			= -1;

	m_fFXCamJitterVisibleDistance		= 0.0f;
	m_fFXSpriteSystemVisibleDistance	= 0.0f;
	m_fFXSpriteVisibleDistance			= 0.0f;
	m_fFXSoundVisibleDistance			= 0.0f;
	m_fFXModelVisibleDistance			= 0.0f;
	m_fFXDynaLightVisibleDistance		= 0.0f;

	m_arridWaterZoro		= HT_NULL;
	m_iNumWaterZoro			= -1;

	// 20021112 대호
	m_idMiniMap				= 0;
	m_vMiniMapPos			= HTvector3( 0.0f, 0.0f, 0.0f );
	m_iMiniMapWidth			= 0;	
	m_iMiniMapHeight		= 0;
	//	m_bMiniMapDrawOn		= HT_FALSE;
	m_fMinimapZoom			= 500.f;
	m_fGrassarea			= 0.0f;
	m_nGrassCount			= 0;
	m_bUpdateByCamera		= HT_FALSE;
	m_fGrassAlphaDistance	= 20.0f;
	m_fCameraSpeed			= 10.0f;

	m_iObjDrawSteps			= 2;		// 대호
	m_fMiniMapSpace			= 100.0f;

	m_fCharLODDistance1 = 0.0f;
	m_fCharLODDistance2 = 0.0f;
	m_fCharLODDistance3 = 0.0f;

	m_iSpecLevel = 2;
	m_iTextureDetailLevel = 2;
	m_bUseRTShadow = HT_FALSE;
	m_fCameraFarZ = 0.0f;
	m_nMaxModelCount = 0;
	m_iScreenWidth = 1024;
	m_iScreenHeight = 768;
	m_iScreenColorDepth = 32;

	m_fStreamVolume = 0.5f;
	m_fStreamFadeVolume = 0.0f;
	m_bFadeoutBGM = HT_FALSE;
	m_dwNextBGMID = 0;
	m_iNextBGMLoopCount = 0;

	m_pUserSettings = HT_NULL;
	m_iSpeakerType = 0;
	m_str3DProvider = _T("Miles Fast 2D Positional Audio");

	m_vectorNPCMonsterIDs.clear();
	m_vectorNPCMonsterAniIDs.clear();
	m_bDynamicLoading = HT_FALSE;
	m_setToCreate.clear();
	m_setToLoad.clear();
	m_mapLoadedOrNot.clear();
	m_dwCurrentMapID = 0;
	m_iTypeCharLight = 1;

	m_fAniInterpolateTime = 0.1f;

#ifdef HT_IS_TANTRA_LAUNCHER
	m_pNPCScriptMgr = HT_NULL;	// 2003.05.14 선미
#endif

	m_fLoadingNextPercent = 0.0f;
	m_fLoadingCurrentPercent = 0.0f;
	m_bRenderLoading = HT_FALSE;

	m_bUpdateViewingObjs = HT_FALSE;

	m_idIntroBGM		= -1;

	g_pEngineHandler = this;

	m_iLoadTimes	=0;

	m_iAreaID		= -1;
	m_iPrevAreaID	= -1;

	m_fUnloadWaitTime = 600.0f;

	m_strObjResName = _T("");
	m_oMousePosFX.idMouseNullModel = -1;
	m_oMousePosFX.idWideFXTargeting = -1;

	m_iLoadUINo = -1;
	m_bUpdateEnable = HT_TRUE;

	for ( HTint i = 0; i < HT_MAX_EOBJ_COUNT; ++i ) m_arrCanModify[i] = HT_FALSE;

	//	Loading BackGround Image
	m_iBGIBalck = -1;
	m_iLoadingBackGroundImage = -1;
	//	Loading Bar
	m_iLoadingBox = -1;
	m_iLoadingBar = -1;

	m_pWebBrowser = HT_NULL;
	m_hWndExplorer = HT_NULL;

	m_bWindowed = HT_FALSE;

	m_fElapsedTime = 0.0f;

	m_oGuildCastleInfo.dwGMarkUL = 0;
	m_oGuildCastleInfo.dwGMarkUR = 0;
	m_oGuildCastleInfo.dwGMarkLL = 0;
	m_oGuildCastleInfo.dwGMarkLR = 0;
}

CHTEngineHandler::~CHTEngineHandler()
{
	HT_hrUnloadMap();

#ifdef HT_IS_TANTRA_LAUNCHER
	HT_DELETE( m_pNPCScriptMgr );	// 2003.05.14 선미 
#endif

	HT_DELETE( m_pPackFileMgr );
	HT_DELETE( m_pResMgr );

	HT_DELETE( m_pFXPCResMgr );
	HT_DELETE( m_pFXMAPResMgr );

	HT_DELETE( m_pObjResMgr );

	HT_DELETE( m_pCfgSpec );
	m_pTimer->Do( HT_TIMER_STOP );

	m_bUpdateEnable = HT_FALSE;
	if ( HT_FAILED( m_p3DMgr->HT_hrTerm() ) )
	{
		MessageBox( HT_NULL, _T("m_p3DMgr->HT_hrTerm FAIL!"), _T("CHTEngineHandler"), MB_OK );
	}
	m_pfnDestroy3DMgr(m_p3DMgr);

	::FreeLibrary( m_h3DDLL );

	HT_DELETE( m_pUserSettings );

	HT_DELETE( m_pTimer );
}

HTRESULT CHTEngineHandler::HT_hrInit( CHTConfigSystem* pCfg, HWND hWnd )
{
	GetCurrentDirectory( 1000, szWorkingPath );

	m_h3DDLL = ::LoadLibrary( "HT3DHeaven.dll" );
	if( !m_h3DDLL )
	{
		MessageBox( HT_NULL, _T("Cannot load HT3DHeaven.dll!"), _T("CHTEngineHandler"), MB_OK );
		return( HT_FAIL );
	}

	m_pfnCreate3DMgr = (HT_pfnCreate3DMgr)::GetProcAddress( m_h3DDLL, "HT_pCreate3DMgr" );
	assert( m_pfnCreate3DMgr != HT_NULL );
	m_pfnDestroy3DMgr = (HT_pfnDestory3DMgr)::GetProcAddress( m_h3DDLL, "HT_hrDestory3DMgr" );
	assert( m_pfnDestroy3DMgr != HT_NULL );

	// 3DMgr을 생성한다.
	m_p3DMgr = m_pfnCreate3DMgr();
	if( !m_p3DMgr )
	{
		MessageBox( NULL, _T("Cannot Create 3DMgr!"), _T("CHTEngineHandler"), MB_OK );
		return( HT_FAIL );
	}

	g_pEngineMgr = m_p3DMgr;

	//----------------------------------------------------------------
	m_pCfgSpec = new CHTConfigSystem;
	m_pCfgSpec->HT_hrLoad( _SPEC_FILEPATH );

	if ( m_pUserSettings )
	{
		HT_hrSetUserSetting( m_pCfgSpec );
	}
	else
	{
		m_pUserSettings = new CHTUserSetting;
		HTtchar szUserSetting[HT_MAX_STR] = "HTUserSetting.sys";
		HTbool bLoadedUserSetting = g_pEngineHandler->m_pUserSettings->HT_bLoad( szUserSetting );

		if ( bLoadedUserSetting )
		{
			HT_hrSetUserSetting( m_pCfgSpec );			
		}
		else
		{
			pCfg->HT_hrGetValue( _T("OPTION"), _T("spec"), &m_iSpecLevel );
			HT_hrLoadSpecValues( m_iSpecLevel, m_pCfgSpec );
		}
	}

	switch ( m_iSpecLevel ) {
	case 1: m_fUnloadWaitTime = 180.0f;
		break;
	case 2: m_fUnloadWaitTime = 600.0f;
		break;
	case 3: m_fUnloadWaitTime = 1800.0f;
		break;
	default:
		break;
	}

	//----------------------------------------------------------------
	// 그 다음 3DMgr을 초기화 구동 시킨다.
	HT_RENDERMODE oRM;
	pCfg->HT_hrGetValue( _T("RENDERER"), _T("windowed"), &oRM.bWindowed );
	oRM.iScreenWidth = m_iScreenWidth;
	oRM.iScreenHeight = m_iScreenHeight;
	oRM.iBitDepth = m_iScreenColorDepth;
	m_bWindowed = oRM.bWindowed;

	// 윈도우 모드로 창을 열어서 웹 페이지를 붙일 수 있도록 한다.
	oRM.bWindowed = HT_TRUE;

	DEVMODE devmodeCurrent;
	::EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &devmodeCurrent );
	m_iCurrentWindowWidth	= devmodeCurrent.dmPelsWidth;
	m_iCurrentWindowHeight	= devmodeCurrent.dmPelsHeight;

	if ( !m_bWindowed )
	{
		DEVMODE dm;
		ZeroMemory(&dm, sizeof(DEVMODE));
		dm.dmSize		= sizeof(DEVMODE);
		dm.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		dm.dmBitsPerPel = 32;
		dm.dmPelsWidth	= m_iScreenWidth;
		dm.dmPelsHeight	= m_iScreenHeight;
		// 바꿀 수 있는지 시험해보고 바꿈
		if ( ::ChangeDisplaySettings( &dm, CDS_TEST ) == DISP_CHANGE_SUCCESSFUL ) ::ChangeDisplaySettings( &dm, CDS_FULLSCREEN );
	}

	HT_SOUNDENVIRONMENT oSE;
	//pCfg->HT_hrGetValue( _T("SOUND"), _T("3dprovider"), oSE.m_str3DProvider );
	pCfg->HT_hrGetValue( _T("SOUND"), _T("channel"), &oSE.m_nBitsPerSample );
	pCfg->HT_hrGetValue( _T("SOUND"), _T("bitspersample"), &oSE.m_nChannels );
	//pCfg->HT_hrGetValue( _T("SOUND"), _T("speakertype"), &oSE.m_nSpeakerType );
	pCfg->HT_hrGetValue( _T("SOUND"), _T("volume"), &oSE.m_fVolume );

	oSE.m_str3DProvider = m_str3DProvider;
	oSE.m_nSpeakerType = m_iSpeakerType;

	oSE.m_f3DSoundCullingDist = m_fFXSoundVisibleDistance;

	HT_CHECK( m_p3DMgr->HT_hrInit(HT_TYPE_RENDER_DIRECT3D, hWnd, &oRM, &oSE ) );

	m_p3DMgr->HT_vSetSpecLevel( m_iTextureDetailLevel, m_nMaxModelCount );

	m_pPackFileMgr = new CHTPackFileMgr;
	m_p3DMgr->HT_vSetPackMgr( m_pPackFileMgr );

	srand( (unsigned)time( NULL ) );

	// Create Camera
	HT_EOBJ_CREATEPARAM cameraParam;
	cameraParam.eObjType = HT_EOBJTYPE_CAMERA;
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("near"), &cameraParam.fNear );
	cameraParam.fFar = m_fCameraFarZ;
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("fov"), &cameraParam.fFOV );
	cameraParam.iWidth = m_iScreenWidth;
	cameraParam.iHeight = m_iScreenHeight;
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("positionX"), &cameraParam.vecPosition.x );
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("positionY"), &cameraParam.vecPosition.y );
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("positionZ"), &cameraParam.vecPosition.z );
	cameraParam.vecRotation = HTvector3( 0.0f, 0.0f, 0.0f );		// look at
	cameraParam.vecScale = HTvector3( 0.0f, 1.0f, 0.0f );			// up
	m_p3DMgr->HT_hrCreateObject( &m_idCamera, &cameraParam );

#ifdef HT_IS_TANTRA_LAUNCHER
	// NPCScript
	m_pNPCScriptMgr = new HTNPCScriptMgr;	// 2003.05.14 선미
#endif

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadMapObjs( HTdword dwMapID )
{
	m_vectorNPCMonsterIDs.clear();
	m_vectorNPCMonsterAniIDs.clear();
	m_mapLoadedOrNot.clear();

	HT_EOBJ_CREATEPARAM modelParam;
	CHTString strFile;
	CHTFile oFile;
	CHTString strTMDPAK, strANIPAK, strTEXPAK, strPOPTMDPAK, strPOPTEXPAK;
	CHTString strOBJPath("resource\\object\\");

	m_pResMgr->HT_bGetTMOFileName( dwMapID, strFile );
	strFile = m_strMapPath + _T("\\") + strFile;

	// 먼저 DLMap이 있는지 보고, 있으면 TMO가 아닌 DLMap을 통해 로드하고 
	strFile--;strFile--;strFile--;
	strFile += _T("tml");

	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) == HT_TRUE )
	{
		HT_CHECK( m_pMapSystem->HT_hrLoadDLMap( strFile, m_vectorNPCMonsterIDs, m_vectorNPCMonsterAniIDs ) );

		// 20030517 assrada : NPC/Monster를 실시간으로 로딩하도록 바꾼다.
		CHTString strTMDPAK2, strANIPAK2, strTEXNPCPAK1, strTEXNPCPAK2, strTEXMOBPAK1, strTEXMOBPAK2;
		CHTString strBuf;

		//m_pResMgr->HT_bGetNPCTEXPAKFileName( dwMapID, strTEXPAK );
		strTEXNPCPAK1 = _T("resource\\object\\NPC\\NPCTex.hpk");
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXNPCPAK1, HT_FALSE );

		strTEXNPCPAK2 = _T("resource\\object\\NPC\\NPCTex2.hpk");
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXNPCPAK2, HT_FALSE );

		//m_pResMgr->HT_bGetMONTEXPAKFileName( dwMapID, strTEXPAK2 );
		strTEXMOBPAK1 = _T("resource\\object\\Monster\\MonsterTex.hpk");
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXMOBPAK1, HT_FALSE );

		strTEXMOBPAK2 = _T("resource\\object\\Monster\\MonsterTex2.hpk");
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXMOBPAK2, HT_FALSE );

		//m_pResMgr->HT_bGetNPCANIPAKFileName( dwMapID, strANIPAK );
		//strANIPAK = strOBJPath + strANIPAK;
		//m_pPackFileMgr->HT_hrOpenPackFile( strANIPAK, HT_FALSE );

		//m_pResMgr->HT_bGetNPCPAKFileName( dwMapID, strTMDPAK );
		//strTMDPAK = strOBJPath + strTMDPAK;
		//m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK, HT_FALSE );

		//m_pResMgr->HT_bGetMONANIPAKFileName( dwMapID, strANIPAK2 );
		//strANIPAK2 = strOBJPath + strANIPAK2;
		//m_pPackFileMgr->HT_hrOpenPackFile( strANIPAK2, HT_FALSE );

		//m_pResMgr->HT_bGetMONPAKFileName( dwMapID, strTMDPAK2 );
		//strTMDPAK2 = strOBJPath + strTMDPAK2;
		//m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK2, HT_FALSE );

		//--------------------------------------------------------------------------------
		// Load Sounds
		CHTString strPack;
		m_pResMgr->HT_bGetNPCSoundFilesName( dwMapID, strPack );
		strPack = _T("resource\\sound\\") + strPack;
		m_pPackFileMgr->HT_hrOpenPackFile( strPack, HT_FALSE );

		m_pResMgr->HT_bGetMonSoundFilesName( dwMapID, strPack );
		strPack = _T("resource\\sound\\") + strPack;
		m_pPackFileMgr->HT_hrOpenPackFile( strPack, HT_FALSE );

		//--------------------------------------------------------------------------------
		// Load MapObjs
		m_pResMgr->HT_bGetOBJPAKFileName( dwMapID, strTMDPAK );
		m_pResMgr->HT_bGetOBJTEXPAKFileName( dwMapID, strTEXPAK );
		strTMDPAK = strOBJPath + strTMDPAK;
		strTEXPAK = strOBJPath + strTEXPAK;

		m_pResMgr->HT_bGetPopObjPackFilesName( dwMapID, strPOPTMDPAK );
		m_pResMgr->HT_bGetPopTexPackFilesName( dwMapID, strPOPTEXPAK );

		strPOPTMDPAK = strOBJPath + strPOPTMDPAK;
		strPOPTEXPAK = strOBJPath + strPOPTEXPAK;
		//strPOPTMDPAK = strOBJPath + _T("POPOBJTMB.hpk");
		//strPOPTEXPAK = strOBJPath + _T("POPOBJTEX.hpk");

		//--------------------------------------------------------------------------------
		// Map Object에 대한 TMD/TEX PAK 파일은 맵 로딩시 열어놓고, 맵 언로드시 닫자.
		// -> By HK 20040128 TEX는 미리 로드해 놓고 닫아버린다.
		m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK, HT_FALSE );
		m_pPackFileMgr->HT_hrOpenPackFile( strPOPTMDPAK, HT_FALSE );

		// NOTE by HK 20040128
		// MAP Object Texture를 실시간 로드할 경우 CreateTexture가 실패해서 화면이 이상해 지는 경우가 있다.
		// 따라서 미리 모든 MAP Object Texture를 로드해 놓는다.
		CHTString strTex;
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXPAK, HT_FALSE );
		{
			CHTString strOnlyTexPak( strTEXPAK );
			//strOnlyTexPak.HT_hrDeletePath();

			HTint iNumFile = m_pPackFileMgr->HT_iGetNumFile( strOnlyTexPak );
			for ( HTint iFile = 0; iFile < iNumFile; ++iFile )
			{
				if ( HT_SUCCEED( m_pPackFileMgr->HT_hrGetFileName( strOnlyTexPak, iFile, &strTex ) ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strTex, 1 ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot Load Map Obj Texture : %s", (HTtchar*)strTex );
						MessageBox( HT_NULL, strDebug, _T("MAP OBJ Texture Load Error!"), MB_OK );
					}
				}
			}

			m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );
		}

		m_pPackFileMgr->HT_hrOpenPackFile( strPOPTEXPAK, HT_FALSE );
		{
			CHTString strOnlyTexPak( strPOPTEXPAK );
			//strOnlyTexPak.HT_hrDeletePath();

			HTint iNumFile = m_pPackFileMgr->HT_iGetNumFile( strOnlyTexPak );
			for ( HTint iFile = 0; iFile < iNumFile; ++iFile )
			{
				if ( HT_SUCCEED( m_pPackFileMgr->HT_hrGetFileName( strOnlyTexPak, iFile, &strTex ) ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strTex, 1 ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot Load POP Obj Texture : %s", (HTtchar*)strTex );
						MessageBox( HT_NULL, strDebug, _T("MAP OBJ Texture Load Error!"), MB_OK );
					}
				}
			}

			m_pPackFileMgr->HT_hrClosePackFile( strPOPTEXPAK );
		}

		//--------------------------------------------------------------------------------
		/*
		HT_EOBJ_CREATEPARAM modelParam;

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strObjModel, 
		m_oResourcePath.strObjTexture );

		modelParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
		modelParam.byForWhat = HT_EOBJ_FOR_MAP;
		modelParam.clrDiffuse = m_clrDiffuse;
		modelParam.clrAmbient = m_clrAmbient;
		modelParam.clrEmissive = m_clrEmissive;
		modelParam.clrSpecular = m_clrSpecular;
		modelParam.fSizePerGrid = 1.0f;	// fog enable

		HTint idObj;
		CHTString strFileName;
		std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itIDs = m_pMapSystem->m_mapSaveObjs.begin();
		while ( itIDs != m_pMapSystem->m_mapSaveObjs.end() && itIDs->second )
		{
		modelParam.dwID = itIDs->second->dwResID;
		modelParam.matTransform = itIDs->second->matTransform;
		modelParam.vecPosition = HTvector3( itIDs->second->matTransform._41, itIDs->second->matTransform._42, itIDs->second->matTransform._43 );
		memcpy( &modelParam.oProperty, &itIDs->second->oProperty, sizeof(HT_EOBJ_PROPERTY) );

		if ( m_pResMgr->HT_bGetFileName( modelParam.dwID, strFileName ) )
		{
		m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, modelParam.dwID, strFileName );
		}

		if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObj, &modelParam ) ) )
		continue;

		itIDs->second->idRenewal = idObj;

		if ( HT_IS_GRASS( modelParam.dwID ) )
		{
		m_pMapSystem->HT_hrInsertGrassObject( idObj, itIDs->second->vectorNodes );
		}
		else if ( HT_IS_SMOBJ( modelParam.dwID ) )
		{
		m_pMapSystem->HT_hrInsertSMObject( idObj, itIDs->second->vectorNodes );
		}
		else
		{
		m_pMapSystem->HT_hrInsertObject( idObj, itIDs->second->vectorNodes );
		}

		// 지형오브젝트가 만일 효과가 달려있다면 효과를 틀어줘라.
		HTint idFX;
		HTdword dwDayFXID = 0, dwNightFXID = 0;
		CHTString strFX;

		m_pResMgr->HT_bGetDayFXID( modelParam.dwID, dwDayFXID );
		m_pResMgr->HT_bGetNightFXID( modelParam.dwID, dwNightFXID );

		if ( dwDayFXID > 0 )
		{
		this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_DAY );
		}

		if ( dwNightFXID > 0 )
		{
		this->HT_hrStartFieldFX( &idFX, dwNightFXID, idObj, HT_TRUE, HT_FX_WHEN_NIGHT );
		}
		itIDs++;
		}
		*/
		//--------------------------------------------------------------------------------

		m_bDynamicLoading = HT_TRUE;

		m_bWorldLoaded = HT_TRUE;

		return ( HT_OK );
	}

	// 그렇지 않으면 전체를 TMO로부터 로드한다.
	strFile--;strFile--;strFile--;
	strFile += _T("tmo");
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	CHTString strBuf;
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );	// read version
	HTint iVersion = 0;
	if ( strBuf == _T("[VERSION_1001]") )
		iVersion = 1001;
	else if ( strBuf == _T("[VERSION_1002]") )
		iVersion = 1002;

	if ( iVersion > 0 )
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );

	HTuint iObjCount = atoi( strBuf );

	HTint idObj;
	HTdword dwID;
	HTuint i;

	m_pResMgr->HT_bGetOBJPAKFileName( dwMapID, strTMDPAK );
	m_pResMgr->HT_bGetOBJTEXPAKFileName( dwMapID, strTEXPAK );
	strTMDPAK = strOBJPath + strTMDPAK;
	strTEXPAK = strOBJPath + strTEXPAK;

	m_pResMgr->HT_bGetPopObjPackFilesName( dwMapID, strPOPTMDPAK );
	m_pResMgr->HT_bGetPopTexPackFilesName( dwMapID, strPOPTEXPAK );

	strPOPTMDPAK = strOBJPath + strPOPTMDPAK;
	strPOPTEXPAK = strOBJPath + strPOPTEXPAK;
	//strPOPTMDPAK = strOBJPath + _T("POPOBJTMB.hpk");
	//strPOPTEXPAK = strOBJPath + _T("POPOBJTEX.hpk");

	if ( iObjCount > 0 )
	{
		m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK );
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXPAK );

		m_pPackFileMgr->HT_hrOpenPackFile( strPOPTMDPAK );
		m_pPackFileMgr->HT_hrOpenPackFile( strPOPTEXPAK );

		// Load MapObjs
		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strObjModel, 
			m_oResourcePath.strObjTexture );

		for ( i = 0; i < iObjCount; i++ )
		{
			modelParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
			modelParam.byForWhat = HT_EOBJ_FOR_MAP;

			// read resource id
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			dwID = atoi( strBuf );

			if ( iVersion >= 1001 )
			{
				HTmatrix matRead;
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f %f", &matRead._11, &matRead._12, &matRead._13, &matRead._14 );
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f %f", &matRead._21, &matRead._22, &matRead._23, &matRead._24 );
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f %f", &matRead._31, &matRead._32, &matRead._33, &matRead._34 );
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f %f", &matRead._41, &matRead._42, &matRead._43, &matRead._44 );

				modelParam.vecPosition = HTvector3( matRead._41, matRead._42, matRead._43 );
				modelParam.matTransform = matRead;

				if ( iVersion >= 1002 )
				{
					oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
					sscanf( strBuf, "%d %d %d %d %d %d", &modelParam.oProperty.iDayFXID, &modelParam.oProperty.iNightFXID,
						&modelParam.oProperty.iPickableFlag, &modelParam.oProperty.iCollisionFlag,
						&modelParam.oProperty.iObjType, &modelParam.oProperty.iPortalID );
				}
			}
			else
			{
				// read translation, rotation, scale value
				HTvector3 vecTran, vecRot, vecScale;
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f", &vecTran.x, &vecTran.y, &vecTran.z );
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f", &vecRot.x, &vecRot.y, &vecRot.z );
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				sscanf( strBuf, "%f %f %f", &vecScale.x, &vecScale.y, &vecScale.z );

				HTquaternion qutRot;
				CHTQuaternion::HT_qutQuaternionRotationYawPitchRoll( &qutRot, 
					vecRot.y, vecRot.x, vecRot.z );
				CHTMatrix::HT_pmatMatrixTransformation( &modelParam.matTransform,
					HT_NULL, HT_NULL, &vecScale, HT_NULL, &qutRot, &vecTran );

				modelParam.vecPosition = vecTran;
				modelParam.vecRotation = vecRot;
				modelParam.vecScale = vecScale;
			}

			if ( !m_pObjResMgr->HT_bGetFileName( dwID, modelParam.strFileName ) )
				continue;

			modelParam.clrDiffuse = m_clrDiffuseObjs;
			modelParam.clrAmbient = m_clrAmbientObjs;
			modelParam.clrEmissive = m_clrEmissiveObjs;
			modelParam.clrSpecular = m_clrSpecularObjs;
			modelParam.fSizePerGrid = 1.0f;	// fog enable

			modelParam.dwID = dwID;
			if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, dwID, modelParam.strFileName ) ) )
				continue;

			m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwID, HT_TRUE ) );

			if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObj, &modelParam ) ) )
				continue;

			HT_AABB oAABB;
			HTmatrix matTransform;
			m_p3DMgr->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform );

			if (modelParam.oProperty.iObjType==_OBJECT_TYPE_GRASS)
				//if ( HT_IS_GRASS( dwID ) )
			{
				m_pMapSystem->HT_hrInsertGrassObject( idObj, &oAABB, &matTransform, dwID, &modelParam.oProperty );
			}
			//else if ( HT_IS_SMOBJ( dwID ) )
			else if (modelParam.oProperty.iObjType==_OBJECT_TYPE_SM)
			{
				m_pMapSystem->HT_hrInsertSMObject( idObj, &oAABB, &matTransform, dwID, &modelParam.oProperty );
			}
			else
			{
				m_pMapSystem->HT_hrInsertObject( idObj, &oAABB, &matTransform, HT_OBJSIZE_NONE, 0, dwID, &modelParam.oProperty );
			}

			// 지형오브젝트가 만일 효과가 달려있다면 효과를 틀어줘라.
			HTint idFX;
			HTdword dwDayFXID = 0, dwNightFXID = 0;
			CHTString strFX;

			//			m_pObjResMgr->HT_bGetDayFXID( dwID, dwDayFXID );
			//			m_pObjResMgr->HT_bGetNightFXID( dwID, dwNightFXID );

			if ( dwDayFXID > 0 && dwNightFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_ALWAYS );
			}
			else if ( dwDayFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_DAY );
			}
			else if ( dwNightFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwNightFXID, idObj, HT_TRUE, HT_FX_WHEN_NIGHT );
			}
		}
		m_pPackFileMgr->HT_hrClosePackFile( strPOPTMDPAK );
		m_pPackFileMgr->HT_hrClosePackFile( strPOPTEXPAK );
		m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK );
		m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );
	}

	HTdword* dwIDs;
	// Load NPC
	HTdword dwAniID;
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	HTuint iNPCCount = atoi( strBuf );

	m_pResMgr->HT_bGetNPCPAKFileName( dwMapID, strTMDPAK );
	m_pResMgr->HT_bGetNPCANIPAKFileName( dwMapID, strANIPAK );
	m_pResMgr->HT_bGetNPCTEXPAKFileName( dwMapID, strTEXPAK );
	strTMDPAK = strOBJPath + strTMDPAK;
	strANIPAK = strOBJPath + strANIPAK;
	strTEXPAK = strOBJPath + strTEXPAK;

	// Load Model
	if ( iNPCCount > 0 )
	{
		m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK );
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXPAK );

		dwIDs = new HTdword[iNPCCount];
		for ( i = 0; i < iNPCCount; i++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			dwIDs[i] = atoi( strBuf );

			m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strNPCModel, 
				m_oResourcePath.strNPCTexture );
			if ( m_pResMgr->HT_bGetModelFileID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SKINNEDMODEL, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}

					m_vectorNPCMonsterIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
		}
		m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );
		m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK );

		// Load Anim
		m_pPackFileMgr->HT_hrOpenPackFile( strANIPAK );
		for ( i = 0; i < iNPCCount; i++ )
		{
			m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strNPCAnimation, 
				m_oResourcePath.strNPCAnimation );
			if ( m_pResMgr->HT_bGetSTDAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetMOVAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetIDLAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
		}
		delete[] dwIDs;
		m_pPackFileMgr->HT_hrClosePackFile( strANIPAK );
	}

	// Load Monster
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	HTuint iMonsterCount = atoi( strBuf );

	m_pResMgr->HT_bGetMONPAKFileName( dwMapID, strTMDPAK );
	m_pResMgr->HT_bGetMONANIPAKFileName( dwMapID, strANIPAK );
	m_pResMgr->HT_bGetMONTEXPAKFileName( dwMapID, strTEXPAK );
	strTMDPAK = strOBJPath + strTMDPAK;
	strANIPAK = strOBJPath + strANIPAK;
	strTEXPAK = strOBJPath + strTEXPAK;

	if ( iMonsterCount > 0 )
	{
		dwIDs = new HTdword[iMonsterCount];

		// Load TMD
		m_pPackFileMgr->HT_hrOpenPackFile( strTMDPAK );
		m_pPackFileMgr->HT_hrOpenPackFile( strTEXPAK );

		for ( i = 0; i < iMonsterCount; i++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			dwIDs[i] = atoi( strBuf );

			m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strMonsterModel, 
				m_oResourcePath.strMonsterTexture );
			if ( m_pResMgr->HT_bGetModelFileID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SKINNEDMODEL, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
		}
		m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK );
		m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );

		// Load Ani
		m_pPackFileMgr->HT_hrOpenPackFile( strANIPAK );
		for ( i = 0; i < iMonsterCount; i++ )
		{
			m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strMonsterAnimation, 
				m_oResourcePath.strMonsterAnimation );
			if ( m_pResMgr->HT_bGetSTDAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetIDLAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetWLKAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetRUNAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetATK1AniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetATK2AniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetHITAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
			if ( m_pResMgr->HT_bGetDIEAniID( dwIDs[i], dwAniID ) )
			{
				if ( m_pResMgr->HT_bGetFileName( dwAniID, strBuf ) )
				{
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwAniID, strBuf ) ) )
					{
						CHTString strDebug;
						strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwAniID, (HTtchar*)strBuf );
						MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
					}
					m_vectorNPCMonsterAniIDs.push_back( dwAniID );
					m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( dwAniID, HT_TRUE ) );
				}
			}
		}
		delete[] dwIDs;
		m_pPackFileMgr->HT_hrClosePackFile( strANIPAK );
	}

	oFile.HT_vClose();

	m_nObjs = iObjCount;

	m_vectorViewingObjs.reserve( m_nObjs );
	m_vectorUpdateObjs.reserve( m_nObjs );

	strFile--;strFile--;strFile--;
	strFile += _T("tml");
	m_pMapSystem->HT_hrSaveDLMap( strFile, m_vectorNPCMonsterIDs, m_vectorNPCMonsterAniIDs );

	m_bDynamicLoading = HT_FALSE;

	m_bWorldLoaded = HT_TRUE;

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUpdate( HTfloat fElapsedTime )
{
	m_fElapsedTime = fElapsedTime;

	// 처음 업데이트 호출시 쓰레기 경과시간이 넘어오는 것을 걸러줌
	if ( fElapsedTime > 30.0f || fElapsedTime < 0.0f ) return ( HT_OK );

	HT_UPDATEOBJPARAM updateParam;

	if (!m_bUpdateEnable) return HT_FAIL;
	if (!m_p3DMgr) return HT_FAIL;

	updateParam.fElapsedTime = fElapsedTime;
	updateParam.idCamera = m_idCamera;

	updateParam.vecSwordStart	= m_vPosition;	// 그림자의 Center
	updateParam.vecSwordEnd		= HTvector3( 1.0f, 0.0f, 1.0f );

	// Default Water Made By Zorotoss
	if ( m_idWaterZoro != -1 )
		m_p3DMgr->HT_hrUpdateObject( m_idWaterZoro, &updateParam );

	for ( HTint i = 0; i < m_iNumWaterZoro; ++i )
	{
		m_p3DMgr->HT_hrUpdateObject( m_arridWaterZoro[i], &updateParam );
	}	

	if ( m_bWorldLoaded )
	{
		// 카메라에 변화가 있을 때에만 업데이트 하라!
		// Note : m_p3DMgr->HT_bIsChangedCamera( m_idCamera ) 이 함수는 카메라에 있는 변수들을 이용한다.
		// 따라서 카메라가 업데이트 된 직후에는 카메라가 움직이지 않는다면 이는 항상 False를 반환한다.
		// 결국 업데이트 직전에 이 함수를 불러 체크하는 것이 안전하겠다.
		if ( m_bUpdateViewingObjs || m_p3DMgr->HT_bIsChangedCamera( m_idCamera ) )
		{
			// 카메라 업데이트
			m_p3DMgr->HT_hrUpdateObject( m_idCamera, &updateParam );

			// 지형 업데이트
			updateParam.fLODDetail				= m_fTerrainLODDetail;
			updateParam.fTilingTextureDistance	= m_fTerrainTilingDistance;
			updateParam.bSwordWindUpdate		= m_bTerrainDetailTexture;
			m_p3DMgr->HT_hrUpdateObject( m_idTerrain, &updateParam );

			HT_hrUpdateMapSystem();
		}

		HT_hrUpdateWorldTime( fElapsedTime );

		// Blind 효과를 위한 상태 변화!
		if ( m_oBlindEffect.fElapsedPercent != 0.0f )
		{
			m_oBlindEffect.fElapsedPercent += fElapsedTime * m_oBlindEffect.fChangePerSecond;

			if ( m_oBlindEffect.fElapsedPercent < 1.0f )
			{
				if ( m_oBlindEffect.bToBlind )
				{
					updateParam.fFogRange = HT_INTERPOLATE( m_oCurrectFogStatus.fStart, m_oBlindEffect.fChangeFogStart, m_oBlindEffect.fElapsedPercent );	// FogStart
					updateParam.fLODDetail = HT_INTERPOLATE( m_oCurrectFogStatus.fEnd, m_oBlindEffect.fChangeFogEnd, m_oBlindEffect.fElapsedPercent );		// FogEnd
					updateParam.clrDiffuse = HT_INTERPOLATE( m_oCurrectFogStatus.clr, m_oBlindEffect.clrChangeFog, m_oBlindEffect.fElapsedPercent );		// FogColor
				}
				else
				{
					updateParam.fFogRange = HT_INTERPOLATE( m_oBlindEffect.fChangeFogStart, m_oCurrectFogStatus.fStart, m_oBlindEffect.fElapsedPercent );	// FogStart
					updateParam.fLODDetail = HT_INTERPOLATE( m_oBlindEffect.fChangeFogEnd, m_oCurrectFogStatus.fEnd, m_oBlindEffect.fElapsedPercent );		// FogEnd
					updateParam.clrDiffuse = HT_INTERPOLATE( m_oBlindEffect.clrChangeFog, m_oCurrectFogStatus.clr, m_oBlindEffect.fElapsedPercent );		// FogColor
				}
			}
			else
			{
				if ( m_oBlindEffect.bToBlind )
				{
					updateParam.fFogRange = m_oBlindEffect.fChangeFogStart;	// FogStart
					updateParam.fLODDetail = m_oBlindEffect.fChangeFogEnd;	// FogEnd
					updateParam.clrDiffuse = m_oBlindEffect.clrChangeFog;	// FogColor
				}
				else
				{
					updateParam.fFogRange = m_oCurrectFogStatus.fStart;	// FogStart
					updateParam.fLODDetail = m_oCurrectFogStatus.fEnd;	// FogEnd
					updateParam.clrDiffuse = m_oCurrectFogStatus.clr;	// FogColor

					m_oBlindEffect.fElapsedPercent = 0.0f;
				}
			}

			m_p3DMgr->HT_hrUpdateObject( m_idFog, &updateParam );
		}

		for ( HTuint i = 0; i < m_iNumWater; ++i )
		{
			if ( m_p3DMgr->HT_bIsInsideFrustum( m_arridWater[i] ) )
				m_p3DMgr->HT_hrUpdateObject( m_arridWater[i], &updateParam );
		}

		// 맵에 있는 오브젝트들을 에니메이션 시킨다.
		//m_p3DMgr->HT_hrAnimateObjects( m_vectorViewingObjs, fElapsedTime );
		m_p3DMgr->HT_hrAnimateObjects( m_vectorUpdateObjs, fElapsedTime );

		HT_UPDATEOBJPARAM FxMgrUpdateParm;
		FxMgrUpdateParm.fElapsedTime	= fElapsedTime;
		FxMgrUpdateParm.idCamera		= m_idCamera;
		FxMgrUpdateParm.fFlickerTime	= m_fNowTimeInAllDay;

		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idField,			&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idMonsterSkill,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idMonsterEtc,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCEtc,			&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCFree,			&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCGodBrahma,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCGodShiba,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCGodVishunu,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCRaceAsuRak,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCRaceDevGar,		&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCRaceNageKin,	&FxMgrUpdateParm );
		m_p3DMgr->HT_hrUpdateObject( m_oIDFXMgr.idPCRaceYakGan,		&FxMgrUpdateParm );

		if ( m_oMousePosFX.idWideFXTargeting > 0 )
		{
			HTbool bMainObjPick;
			HTint idObj;
			HTIntersectInfo oIntersectInfo;
			this->HT_hrPick( m_oMousePosFX.i2DMouseX, m_oMousePosFX.i2DMouseY, &idObj, &oIntersectInfo, &bMainObjPick );
			oIntersectInfo.m_vecPosition.y = this->HT_fGetTerrainHeight( oIntersectInfo.m_vecPosition.x, oIntersectInfo.m_vecPosition.z );

			this->HT_hrMoveObject( m_oMousePosFX.idMouseNullModel, oIntersectInfo.m_vecPosition );
		}
	}
	else
		m_p3DMgr->HT_hrUpdateObject( m_idCamera, &updateParam );

	// BGM Fade out 처리
	// 사운드쪽에서 따로 쓰레드를 만들지 않기 위해서, 이곳에서 처리를 한다.
	if ( m_bFadeoutBGM )
	{
		m_fStreamFadeVolume -= fElapsedTime * 0.5f;

		if ( m_fStreamFadeVolume > 0.0f )
		{
			m_p3DMgr->HT_hrSetStreamVolume( m_fStreamFadeVolume );
		}
		else
		{
			m_p3DMgr->HT_hrSetStreamVolume( m_fStreamVolume );

			if ( m_dwNextBGMID > 0 )
				m_p3DMgr->HT_hrPlaySound( m_dwNextBGMID, m_iNextBGMLoopCount );
			else
				m_p3DMgr->HT_hrStopStreamSound();

			m_bFadeoutBGM = HT_FALSE;
		}
	}

	// Loading Resource Process
	HT_hrLoadingProcess();

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrRenderWorld()
{
	HTuint i;

	m_nTerrainPolyCount = 0;
	m_nModelPolyCount = 0;

	//if ( m_pWebBrowser && m_hWndExplorer )
	//{
	//	VARIANT_BOOL bBusy;
	//	HRESULT hr = m_pWebBrowser->get_Busy( &bBusy );
	//	if ( hr == S_OK )
	//	{
	//		//m_pWebBrowser->put_Width( m_iScreenWidth );
	//		//m_pWebBrowser->put_Height( m_iScreenHeight );
	//		
	//		//m_pWebBrowser->put_Top( 0 );
	//		//m_pWebBrowser->put_Left( 0 );

	//		//g_pEngineHandler->HT_hrChangeColor( m_iBGIBalck, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//		//g_pEngineHandler->HT_hrRenderObject( m_iBGIBalck );

	//		//Sleep( 100 );
	//		//return HT_OK;
	//	}
	//	else
	//	{
	//		//	웹브라우져를 지위기위해서 클라이언트에 창을 뛰운다.
	//		g_cUIManager->HT_ShowWindow( _DIALOG_WEBBROWSER );

	//		m_pWebBrowser->Release();
	//		m_pWebBrowser = HT_NULL;
	//		m_hWndExplorer = HT_NULL;
	//	}
	//}

	if ( m_bWorldLoaded )
	{
		m_p3DMgr->HT_hrRenderObject( m_idFog );

		// 던전과 일반 외부지형의 차이이다.
		if ( m_bUpdateTime )
		{
			m_p3DMgr->HT_hrRenderObject( m_idSky );			// 하늘의 가장 외곽을 렌더링 ( z - buffer off )

			if ( m_p3DMgr->HT_eGetGraphicCardType() == HT_GRAPHICCARDTYPE_VOODOO )
			{
				m_p3DMgr->HT_hrRenderObject( m_idSkyCloud );	// 구름을 렌더링 ( z - buffer off )

				m_p3DMgr->HT_hrRenderObject( m_idSun );			// 해나 달을 렌더링 ( z - buffer off )
				m_p3DMgr->HT_hrRenderObject( m_idMoon );
			}
			else
			{
				m_p3DMgr->HT_hrRenderObject( m_idSun );			// 해나 달을 렌더링 ( z - buffer off )
				m_p3DMgr->HT_hrRenderObject( m_idMoon );

				m_p3DMgr->HT_hrRenderObject( m_idSkyCloud );	// 구름을 렌더링 ( z - buffer off )
				m_p3DMgr->HT_hrRenderObject( m_idSkyTerrain );	// 하늘의 지형띠를 렌더링한다.
			}
		}


		// From now on, z - buffer on..
		m_p3DMgr->HT_hrRenderObject( m_idTerrain );
		//if (m_bMiniMapDrawOn && m_idMiniMap) m_p3DMgr->HT_hrRenderObject( m_idMiniMap );


		m_nTerrainPolyCount = m_p3DMgr->HT_nGetPolyCount( m_idTerrain );

		// 맵에 있는 오브젝트들을 렌더링한다.
		m_p3DMgr->HT_hrRenderObjects( m_vectorViewingObjs, &m_nModelPolyCount );

		// 물을 렌더링 한다. 물은 기본적으로 알파블랜딩을 하므로, Z-buffer는 Read only이고,
		// 다음에 나올 것 끼리는 Z compare를 할 수 없으므로 주의!!
		for ( i = 0; i < m_iNumWater; ++i )	
		{
			if ( m_p3DMgr->HT_bIsInsideFrustum( m_arridWater[i] ) )
				m_p3DMgr->HT_hrRenderObject( m_arridWater[i] );
		}

		// Default Water Made By Zorotoss
		if ( m_idWaterZoro != -1 ) m_p3DMgr->HT_hrRenderObject( m_idWaterZoro );

		for ( HTint i = 0; i < m_iNumWaterZoro; ++i )
		{
			m_p3DMgr->HT_hrRenderObject( m_arridWaterZoro[i] );
		}

		// 풀들을 렌더링한다.
		HTuint nGrassPolyCount = 0;
		m_nGrassCount = (HTuint)m_vectorGrasses.size();
		m_p3DMgr->HT_hrRenderGrasses( m_vectorGrasses, &nGrassPolyCount );
		m_nModelPolyCount += nGrassPolyCount;

		// SFX 들을 렌더링한다.
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idField );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idMonsterSkill );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idMonsterEtc );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCEtc );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCFree );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCGodBrahma );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCGodShiba );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCGodVishunu );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCRaceAsuRak );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCRaceDevGar );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCRaceNageKin );
		m_p3DMgr->HT_hrRenderObject( m_oIDFXMgr.idPCRaceYakGan );
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrRenderFPS( HTfloat fFPS )
{
	//static HTfloat fLastTime = 0.0f;
	//   static HTdword dwFrames  = 0L;
	static CHTString strFrameState;
	//   ++dwFrames;
	//HTfloat fCurrentTime = fFPS;

	//HTvector3 vecCam = m_p3DMgr->HT_vecGetEye( m_idCamera );
	//HTvector3 vecCamLook = ((CHTObjCamera*)m_p3DMgr->HT_pGetObject( m_idCamera ))->HT_rvecGetLookAt();

	// Update the scene stats once per second
	//    if( fCurrentTime - fLastTime > 1.0f )
	{
		strFrameState.HT_szFormat( _T("FPS: %.02f, Polys: %d, Tex: %dKB, VBIB: %dKB, E:%d,S:%d"), 
			//			dwFrames / (fCurrentTime - fLastTime), m_nModelPolyCount + m_nTerrainPolyCount,
			fFPS, m_nModelPolyCount + m_nTerrainPolyCount,
			/*m_nRenderObjs, m_nViewings, m_nObjs, m_nGrassCount,*/ m_p3DMgr->HT_nGetTextureMemSize()/1024, m_p3DMgr->HT_nGetVBIBMemSize()/1024,
			m_p3DMgr->HT_iGetEngineObjCount(), m_p3DMgr->HT_iGetShareObjCount());
		//        fLastTime = fCurrentTime;
		//        dwFrames  = 0L;
	}

	HT_hrRenderText( HT_FONT_ARIAL_20, strFrameState, HTvector3( 0.0f, 0.0f, 0.0f ), 
		HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrCameraControl( WPARAM wParam, HTfloat fElapsedTime )
{
	HTfloat fOffset = m_fCameraSpeed * fElapsedTime;

	switch( wParam )
	{
	case VK_LEFT:
		m_p3DMgr->HT_hrRotateOnY( m_idCamera, -fOffset/8.0f );
		break;
	case VK_RIGHT:
		m_p3DMgr->HT_hrRotateOnY( m_idCamera, fOffset/8.0f );
		break;
	case VK_UP:
		m_p3DMgr->HT_hrRotateOnX( m_idCamera, -fOffset/16.0f );
		break;
	case VK_DOWN:
		m_p3DMgr->HT_hrRotateOnX( m_idCamera, fOffset/16.0f );
		break;
	case 'W':
		m_p3DMgr->HT_hrGoForward( m_idCamera, +fOffset/2.0f );
		break;
	case 'S':
		m_p3DMgr->HT_hrGoForward( m_idCamera, -fOffset/2.0f );
		break;
	case 'D':
		m_p3DMgr->HT_hrGoRight( m_idCamera, fOffset/2.0f );
		break;
	case 'A':
		m_p3DMgr->HT_hrGoRight( m_idCamera, -fOffset/2.0f );
		break;
		//case 'X':
		//	m_p3DMgr->HT_hrZoomIn( m_idCamera, 1.0f );
		//	break;
		//case 'x':
		//	m_p3DMgr->HT_hrZoomIn( m_idCamera, -1.0f );
		//	break;
	case 'Q':
		m_p3DMgr->HT_vRotateHorizontal( m_idCamera, m_vPosition, 2.0f );
		break;
	case 'E':
		m_p3DMgr->HT_vRotateHorizontal( m_idCamera, m_vPosition, -2.0f );
		break;
	case 'Z':
		m_p3DMgr->HT_vRotateVertical( m_idCamera, m_vPosition, 2.0f );
		break;
	case 'C':
		m_p3DMgr->HT_vRotateVertical( m_idCamera, m_vPosition, -2.0f );
		break;
	case 'L':
		m_p3DMgr->HT_hrSetLookAt( m_idCamera, m_vPosition );
		break;
	default:
		break;
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrToggleScreen()
{
	m_bWindowed = !m_bWindowed;

	if ( m_bWindowed )
	{
		DEVMODE dm;
		ZeroMemory( &dm, sizeof(DEVMODE) );
		dm.dmSize		= sizeof(DEVMODE);
		dm.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		dm.dmBitsPerPel = 32;
		dm.dmPelsWidth	= m_iCurrentWindowWidth;
		dm.dmPelsHeight	= m_iCurrentWindowHeight;
		// 바꿀 수 있는지 시험해보고 바꿈
		if ( ::ChangeDisplaySettings( &dm, CDS_TEST ) == DISP_CHANGE_SUCCESSFUL ) ::ChangeDisplaySettings( &dm, CDS_FULLSCREEN );
	}
	else
	{
		DEVMODE dm;
		ZeroMemory( &dm, sizeof(DEVMODE) );
		dm.dmSize		= sizeof(DEVMODE);
		dm.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		dm.dmBitsPerPel = 32;
		dm.dmPelsWidth	= m_iScreenWidth;
		dm.dmPelsHeight	= m_iScreenHeight;
		// 바꿀 수 있는지 시험해보고 바꿈
		if ( ::ChangeDisplaySettings( &dm, CDS_TEST ) == DISP_CHANGE_SUCCESSFUL ) ::ChangeDisplaySettings( &dm, CDS_FULLSCREEN );
	}
//	HT_CHECK( m_p3DMgr->HT_hrToggleScreen() );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrResize()
{
	m_p3DMgr->HT_hrResize();
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrPick( HTint iX, HTint iY, HTint* idObj, HTIntersectInfo* pInfo, HTbool* bMainObjPick )
{
	// 픽되는 오브젝트 아이디를 -1로 초기화 시킨다.
	*idObj = -1;

	HTRESULT hrTerrainPicked;
	// 먼저 지형의 픽을 실행한다.
	if ( HT_FAILED( m_p3DMgr->HT_hrPick( m_idTerrain, (HTfloat)iX, (HTfloat)iY, pInfo ) ) )
	{
		// 실패하면 pInfo의 초기값인 (0,0,0)이 넘어간다.
		hrTerrainPicked = HT_FAIL;
	}
	else
	{
		hrTerrainPicked = HT_OK;
	}

	std::list<HTint> listIDPickedObjs;

	HTRESULT	hrPicked = HT_FAIL;
	HTfloat		fDist;						// 오브젝트의 거리를 통해 오브젝트 PICK을 하기 위한 변수들
	HTint		iObjID;
	HTvector3	rvecPickPos;		

	HTRay oRay;
	m_p3DMgr->HT_hrMakePickRay( iX, iY, &oRay );

	// 오브젝트들이 들어있는 맵 노드에 대해 픽을 실행한다.
	m_pMapSystem->HT_hrPick( oRay, listIDPickedObjs );

	HTfloat fClosestObjDistance = 100000.0f;
	HTvector3 vecCam, vecTmp, vecCamDir;
	vecCam = m_p3DMgr->HT_vecGetEye( m_idCamera );
	vecCamDir = m_p3DMgr->HT_vecGetLookAt( m_idCamera ) - vecCam;

	std::list<HTint>::iterator it = listIDPickedObjs.begin();
	while ( it != listIDPickedObjs.end() )
	{
		// 오브젝트의 바운딩 박스 정보와 반직선 간의 교차 판정을 한다.
		if ( HT_SUCCEED( m_p3DMgr->HT_hrPick( &fDist, *it, (HTfloat)iX, (HTfloat)iY ) ) )
		{			
			// Map Object 중에 픽시키지 않을 놈들을 생략한다.
			HT_EOBJ_PROPERTY* pProperty = HT_NULL;
			m_p3DMgr->HT_hrGetProperty( *it, &pProperty );

			if ( pProperty && !pProperty->iPickableFlag )
			{
				++it;
				continue;
			}

			// Main Object가 픽되었으면 되었다고만 알리고, 실제 픽 되는 자세한 정보는 스킵한다.
			if ( m_idMainCharacter == *it )
			{
				*bMainObjPick = HT_TRUE;
				++it;
				continue;
			}

			// Pick하지 말라고 부탁된 것들은 제외한다. ( 죽은 몬스터들 )
			if ( m_setDontClickObjs.find( *it ) != m_setDontClickObjs.end() )
			{
				++it;
				continue;
			}

			// 커다란 Rigid Model일 경우는 바운딩박스로 픽했을 경우, 오차가 크므로 폴리곤단위의 거리계산을 한다.
			if ( m_p3DMgr->HT_eGetEObjectType(*it) == HT_EOBJTYPE_RIGIDMODEL )
			{
				if ( HT_SUCCEED( m_p3DMgr->HT_hrPick( &rvecPickPos, *it, (HTfloat)iX, (HTfloat)iY ) ) )
				{
					vecTmp = rvecPickPos - vecCam;
					if ( CHTVector::HT_fVec3Dot( &vecCamDir, &vecTmp ) > 0.0f )
					{
						fDist = CHTVector::HT_fVec3Length( &vecTmp );
					}
					else
					{
						++it;
						continue;
					}
				}
				else
				{
					++it;
					continue;
				}
			}

			// 가장 가까운 거리에 있는 오브젝트를 선택한다.
			if ( fDist < fClosestObjDistance  && fDist>0.0f)
			{
				fClosestObjDistance = fDist;
				iObjID = *it;
				hrPicked = HT_OK;
			}
		}
		++it;			
	}

	if ( HT_SUCCEED( hrPicked ) )
	{
		*idObj = iObjID;

		// 만일 픽 된 오브젝트가 SkinnedModel이면, 아이디를 세팅하고 바로 리턴한다.
		if ( m_p3DMgr->HT_eGetEObjectType(iObjID) == HT_EOBJTYPE_SKINNEDMODEL )
		{
			// pInfo에 모델의 위치값을 넣는 부분이다.
			HTvector3 vecPos;
			HT_CHECK( m_p3DMgr->HT_hrGetPosition( iObjID, vecPos ) );
			pInfo->m_vecPosition = vecPos;

			return ( HT_OK );
		}
		// 만일 픽 된 오브젝트가 RigidModel이면, 아래의 할 일이 남았으니 브레이크한다.
		else if ( m_p3DMgr->HT_eGetEObjectType(iObjID) == HT_EOBJTYPE_RIGIDMODEL )
		{
		}
		else	// 이런 상황은 절대 발생하지 않아야 한다.
		{
			MessageBox( NULL, "Error!", "CHTEngineHandler::HT_hrPick", MB_OK );
			return ( HT_FAIL );
		}
	}
	// 픽이 된 오브젝트가 없다면 
	else
	{
		return ( hrTerrainPicked );
	}

	// 이제부터는 픽이 된 오브젝트가 바닥같은 RigidModel인 경우, 폴리곤 검사를 해서 정확한 픽 지점을 찾는다.
	// 폴리곤 검사를 해서 그 놈이 걸린다면,
	if ( HT_SUCCEED( m_p3DMgr->HT_hrPick( &rvecPickPos, iObjID, (HTfloat)iX, (HTfloat)iY ) ) )
	{
		// 지형과의 거리와 오브젝트와의 거리를 비교하여 가까운 것을 택한다.
		HTfloat fDistTerrain, fDistObj;
		vecTmp = pInfo->m_vecPosition - vecCam;
		fDistTerrain = HT_ABS( CHTVector::HT_fVec3Length( &vecTmp ) );
		vecTmp = rvecPickPos - vecCam;
		fDistObj = HT_ABS( CHTVector::HT_fVec3Length( &vecTmp ) );

		// 지형이 오브젝트보다 더 가깝다면, 오브젝트는 바닥 밑이나 산너머에 있는 것이므로, 픽이 된 것이 아니다.
		// 오브젝트가 더 가깝다면 리턴되는 위치 정보를 오브젝트 픽 지점으로 세팅한다.
		if ( fDistTerrain > fDistObj )
		{
			pInfo->m_vecPosition = rvecPickPos;
		}

		// 지형이 픽 되면 아이디를 넘기지 않는다.
		if ( fDistTerrain < fDistObj )
			*idObj = -1;

		return ( HT_OK );
	}
	// 바운딩 박스에는 걸렸는데 폴리곤과는 교차하지 않는다면 지형과의 픽 정보를 이용한다.
	else
	{
		*idObj = -1;
		return ( HT_OK );
	}

	return ( HT_FAIL );
}

HTbool
CHTEngineHandler::HT_bCheckCollide( HTvector3& vecStart, HTvector3& vecEnd, HTvector3* pvecCollidePos )
{
	HTvector3 vecTerrainCollidePos;
	HTbool bTerrainCollide = m_p3DMgr->HT_bCheckCollide( m_idTerrain, vecStart, vecEnd, &vecTerrainCollidePos );

	HTRay oRay;
	oRay.HT_hrInit( vecStart, vecEnd );

	// 오브젝트들이 들어있는 맵 노드에 대해 픽을 실행한다. 충돌의 대상이 되는 것들이 검출된다.
	std::list<HTint> listIDPickedObjs;
	m_pMapSystem->HT_hrPick( oRay, listIDPickedObjs );

	HTfloat	fDist; // 오브젝트의 거리를 통해 오브젝트 PICK을 하기 위한 변수들
	HTfloat fDistTmp;
	HTfloat fClosestObjDistance = FLT_MAX;
	HTvector3 vecTmp, vecDir, vecDirNormal;
	HTvector3 vecCollidePos;

	vecDir = vecEnd - vecStart;
	CHTVector::HT_pvecVec3Normalize( &vecDirNormal, &vecDir );

	HTbool bCollide;
	std::list<HTint>::iterator it = listIDPickedObjs.begin();
	while ( it != listIDPickedObjs.end() )
	{
		// 오브젝트의 바운딩 박스 정보와 반직선 간의 교차 판정을 한다.
		if ( m_p3DMgr->HT_bCheckCollide( *it, oRay, &fDistTmp ) )
		{			
			if ( m_idMainCharacter == *it ) continue; // Main Obj는 충돌되었다 해도 생깐다.
			else if ( m_p3DMgr->HT_eGetEObjectType( *it ) == HT_EOBJTYPE_SKINNEDMODEL )
			{
				// Skinned Model의 경우에는 이 놈의 바운딩 박스에 있는 충돌 지점을 충돌지점으로 사용한다.
				vecCollidePos = vecStart + (vecDirNormal * fDistTmp);
				fDist = fDistTmp * fDistTmp;
			}
			else if ( m_p3DMgr->HT_eGetEObjectType( *it ) == HT_EOBJTYPE_RIGIDMODEL )
			{
				// 커다란 Rigid Model일 경우는 바운딩박스로 픽했을 경우, 오차가 크므로
				// 폴리곤 단위 검사를 하는 함수를 불러준다.
				if ( m_p3DMgr->HT_bCheckCollide( *it, oRay, &vecCollidePos ) )
				{
					vecTmp = vecCollidePos - vecStart;
					if ( CHTVector::HT_fVec3Dot( &vecDir, &vecTmp ) > 0.0f )
					{
						// SQ 연산이 더 싸니까.
						fDist = CHTVector::HT_fVec3LengthSq( &vecTmp );
					}
					else
					{
						++it;
						continue;
					}
				}
				else
				{
					++it;
					continue;
				}
			}

			// 가장 가까운 거리에 있는 오브젝트를 선택한다.
			if ( fDist < fClosestObjDistance  && fDist > 0.0f )
			{
				fClosestObjDistance = fDist;
				*pvecCollidePos = vecCollidePos;
				bCollide = HT_TRUE;
			}
		}

		++it;
	}

	if ( bCollide )
	{
		// 오브젝트와 지형이 모두 충돌한 경우에는 지형과 오브젝트 중 어느것이 더 가까운지 비교해주어야 한다.
		if ( bTerrainCollide )
		{
			HTvector3 vecStart2Terrain = vecTerrainCollidePos - vecStart;
			HTvector3 vecStart2Obj = *pvecCollidePos - vecStart;
			HTfloat fStart2TerrainDist = CHTVector::HT_fVec3LengthSq( &vecStart2Terrain );
			HTfloat fStart2ObjDist = CHTVector::HT_fVec3LengthSq( &vecStart2Obj );

			if ( fStart2ObjDist < fStart2TerrainDist )
			{
				*pvecCollidePos = vecTerrainCollidePos;
			}
		}

		return HT_TRUE;
	}
	// 픽이 된 오브젝트가 없다면 
	else
	{
		return bTerrainCollide;
	}
}

HTbool
CHTEngineHandler::HT_bCheckCollideMainCharToCamera( HTint* arrIDRigidObj, HTint* arrIDSkinnedObj, HTbool* pbTerrain, HTint* piNumRigidObj, HTint* piNumSkinnedObj )
{
	if ( !arrIDRigidObj || !arrIDSkinnedObj || !pbTerrain ) return HT_FALSE;

	memset( arrIDRigidObj, 0, sizeof(HTint) * HT_MAX_CHECK_COLLISION );
	memset( arrIDSkinnedObj, 0, sizeof(HTint) * HT_MAX_CHECK_COLLISION );
	*pbTerrain = HT_FALSE;
	*piNumRigidObj = 0;
	*piNumSkinnedObj = 0;

	HTvector3 vecEye = this->HT_rvecGetEye();
	HTvector3 vecMainChar;
	//m_p3DMgr->HT_hrGetPosition( m_idMainCharacter, vecMainChar );

	HT_AABB oAABB;
	HTmatrix matTransform;
	if ( HT_SUCCEED( m_p3DMgr->HT_hrGetBoundingBox( m_idMainCharacter, &oAABB, &matTransform ) ) )
	{
		CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMax, &oAABB.vecMax, &matTransform );
		CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMin, &oAABB.vecMin, &matTransform );

		vecMainChar = oAABB.vecMax + oAABB.vecMin;
		vecMainChar /= 2.0f;
	}
	else return HT_FALSE;

	HTfloat fDistEye2MainChar = CHTVector::HT_fVec3Length( &(vecEye - vecMainChar) );

	// 먼저 지형에 대해 충돌했는지 확인한다.
	HTvector3 vecTerrainCollidePos;
	*pbTerrain = m_p3DMgr->HT_bCheckCollide( m_idTerrain, vecEye, vecMainChar, &vecTerrainCollidePos );

	HTRay oRay;
	oRay.HT_hrInit( vecEye, vecMainChar );

	// 충돌의 대상이 되는 오브젝트들의 리스트를 얻어온다.
	std::list<HTint> listIDColloidObjs;
	m_pMapSystem->HT_hrPick( oRay, listIDColloidObjs );

	// 실제 충돌이 되는 오브젝트가 어떤 오브젝트인지 확인하고 추가해준다.
	HTfloat fDistTmp;
	HTvector3 vecCollPos;
	HTdword dwResID;
	HTbool bNeedCamCollide;

	std::list<HTint>::iterator it = listIDColloidObjs.begin();
	while ( it != listIDColloidObjs.end() )
	{
		// 먼저 Bounding Box만을 가지고 충돌을 확인한다.
		if ( m_p3DMgr->HT_bCheckCollide( *it, oRay, &fDistTmp ) )
		{
			if ( m_idMainCharacter == *it )
			{	// Main Obj는 충돌되었다 해도 생깐다.
				++it;
				continue;
			}
			else if ( m_p3DMgr->HT_eGetEObjectType( *it ) == HT_EOBJTYPE_SKINNEDMODEL && *piNumSkinnedObj < HT_MAX_CHECK_COLLISION )
			{
				arrIDSkinnedObj[(*piNumSkinnedObj)++] = *it;
			}
			else if ( m_p3DMgr->HT_eGetEObjectType( *it ) == HT_EOBJTYPE_RIGIDMODEL && *piNumRigidObj < HT_MAX_CHECK_COLLISION )
			{
				dwResID = m_p3DMgr->HT_dwGetResourceID( *it );
				m_pObjResMgr->HT_bGetCamCollision( dwResID, bNeedCamCollide );
				// Obj.TXL에 적혀 있는 CamCollide를 읽어서 이 값에 의해 카메라와 충돌을 해야 할지 말지를 검사한다.

				if ( bNeedCamCollide )
				{
					// 커다란 Rigid Model일 경우는 바운딩박스로 픽했을 경우, 오차가 크므로
					// 폴리곤 단위 검사를 하는 함수를 불러준다.
					if ( m_p3DMgr->HT_bCheckCollide( *it, oRay, &vecCollPos ) )
					{
						arrIDRigidObj[(*piNumRigidObj)++] = *it;
					}
				}
			}
		}

		++it;
	}

	// 일단은 RigidModel 과의 충돌만을 충돌로 판단한다. SkinnedModel과의 충돌은 현재 상태에서는 알 필요가 없는거 같다.
	if ( *pbTerrain || *piNumRigidObj > 0 ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool
CHTEngineHandler::HT_bCheck2ObjCollide( HTint iObjChar, HTint iObjMon )
{
	// 두 Object의 BB를 추출하여 충돌하면 HT_TRUE를, 충돌하지 않으면 HT_FALSE 를 반환한다.
	// 단 계산의 효율을 위해 iObjChar는 Boung Sphere를, iObjMon은 OBB를 사용하도록 한다.
	// 이 함수는 캐릭터와 몬스터에 충돌에 사용될 함수인데,
	// 캐릭터의 경우에는 (y를 무시한) 2차원적으로 정사각 모양을 가진다고 가정할 수 있기에 가능하다.

	HT_AABB oAABBChar;
	HTmatrix matXformChar;
	m_p3DMgr->HT_hrGetBoundingBox( iObjChar, &oAABBChar, &matXformChar );

	HT_AABB oAABBMon;
	HTmatrix matXformMon;
	m_p3DMgr->HT_hrGetBoundingBox( iObjMon, &oAABBMon, &matXformMon );

	HTvector3 vecCharCenter;
	vecCharCenter = oAABBChar.vecMax + oAABBChar.vecMin;
	vecCharCenter *= 0.5f;

	HTfloat fBBOffset = CHTVector::HT_fVec3Length( &(oAABBChar.vecMax - vecCharCenter) );

	// 이제 캐릭터를 하나의 구로 가정하고 Monster의 OBB의 공간으로 이동하여 캐릭터의 구와 몬스터의 OBB간의 교차 판정을 한다.
	// 캐릭터의 중심 : vecCharCenter, 반지름 : fBBOffset
	HTfloat fDit;
	HTmatrix matXformMonInv;
	CHTMatrix::HT_pmatMatrixInverse( &matXformMonInv, &fDit, &matXformMon );
	CHTVector::HT_pvecVec3TransformCoord( &vecCharCenter, &vecCharCenter, &matXformMonInv );

	HTfloat f = 0.0f;
	if ( vecCharCenter.x < oAABBMon.vecMin.x ) f += ( vecCharCenter.x - oAABBMon.vecMin.x ) * ( vecCharCenter.x - oAABBMon.vecMin.x );
	else if ( vecCharCenter.x > oAABBMon.vecMax.x ) f += ( vecCharCenter.x - oAABBMon.vecMax.x ) * ( vecCharCenter.x - oAABBMon.vecMax.x );

	if ( vecCharCenter.y < oAABBMon.vecMin.y ) f += ( vecCharCenter.y - oAABBMon.vecMin.y ) * ( vecCharCenter.y - oAABBMon.vecMin.y );
	else if ( vecCharCenter.y > oAABBMon.vecMax.y ) f += ( vecCharCenter.y - oAABBMon.vecMax.y ) * ( vecCharCenter.y - oAABBMon.vecMax.y );

	if ( vecCharCenter.z < oAABBMon.vecMin.z ) f += ( vecCharCenter.z - oAABBMon.vecMin.z ) * ( vecCharCenter.z - oAABBMon.vecMin.z );
	else if ( vecCharCenter.z > oAABBMon.vecMax.z ) f += ( vecCharCenter.z - oAABBMon.vecMax.z ) * ( vecCharCenter.z - oAABBMon.vecMax.z );

	if ( f > fBBOffset * fBBOffset ) return HT_FALSE;
	else return HT_TRUE;
}

HTbool
CHTEngineHandler::HT_bCheck2ObjCollide( HTint iObjMon, HTvector3& vecPosChar, HTfloat fBBOffset )
{	
	// 단 Main Char는 ID가 아니라 위치 정보와 BB의 크기를 입력 받도록 한다.

	// 단 계산의 효율을 위해 캐릭터는 Bounding Sphere 를 사용하고 몬스터는 OBB를 사용하도록 한다.
	// 이 함수는 캐릭터와 몬스터에 충돌에 사용될 함수인데,
	// 캐릭터의 경우에는 (y를 무시한) 2차원적으로 정사각 모양을 가진다고 가정할 수 있기에 가능하다.

	HT_AABB oAABBMon;
	HTmatrix matXformMon;
	m_p3DMgr->HT_hrGetBoundingBox( iObjMon, &oAABBMon, &matXformMon );

	HTvector3 vecCharCenter( vecPosChar.x, vecPosChar.y + fBBOffset * 0.5f, vecPosChar.z );

	// 이제 캐릭터를 하나의 구로 가정하고 Monster의 OBB의 공간으로 이동하여 캐릭터의 구와 몬스터의 OBB간의 교차 판정을 한다.
	// 캐릭터의 중심 : vecCharCenter, 반지름 : fBBOffset
	HTfloat fDit;
	HTmatrix matXformMonInv;
	CHTMatrix::HT_pmatMatrixInverse( &matXformMonInv, &fDit, &matXformMon );
	CHTVector::HT_pvecVec3TransformCoord( &vecCharCenter, &vecCharCenter, &matXformMonInv );

	HTfloat f = 0.0f;
	if ( vecCharCenter.x < oAABBMon.vecMin.x ) f += ( vecCharCenter.x - oAABBMon.vecMin.x ) * ( vecCharCenter.x - oAABBMon.vecMin.x );
	else if ( vecCharCenter.x > oAABBMon.vecMax.x ) f += ( vecCharCenter.x - oAABBMon.vecMax.x ) * ( vecCharCenter.x - oAABBMon.vecMax.x );

	if ( vecCharCenter.y < oAABBMon.vecMin.y ) f += ( vecCharCenter.y - oAABBMon.vecMin.y ) * ( vecCharCenter.y - oAABBMon.vecMin.y );
	else if ( vecCharCenter.y > oAABBMon.vecMax.y ) f += ( vecCharCenter.y - oAABBMon.vecMax.y ) * ( vecCharCenter.y - oAABBMon.vecMax.y );

	if ( vecCharCenter.z < oAABBMon.vecMin.z ) f += ( vecCharCenter.z - oAABBMon.vecMin.z ) * ( vecCharCenter.z - oAABBMon.vecMin.z );
	else if ( vecCharCenter.z > oAABBMon.vecMax.z ) f += ( vecCharCenter.z - oAABBMon.vecMax.z ) * ( vecCharCenter.z - oAABBMon.vecMax.z );

	if ( f > fBBOffset * fBBOffset ) return HT_FALSE;
	else return HT_TRUE;
}

HTRESULT CHTEngineHandler::HT_hrPick( HTIntersectInfo* pInfo, HTint iX, HTint iY )
{
	if ( HT_SUCCEED( m_p3DMgr->HT_hrPick( m_idTerrain, (HTfloat)iX, (HTfloat)iY, pInfo ) ) )
	{
		return ( HT_OK );
	}

	return ( HT_FAIL );
}

HTRESULT CHTEngineHandler::HT_hrPick(HTIntersectInfo* pInfo, HTint idObj, HTbool* bSkinnedModel, HTint iX, HTint iY )
{
	if ( m_p3DMgr->HT_eGetEObjectType( idObj ) == HT_EOBJTYPE_SKINNEDMODEL )
	{
		*bSkinnedModel = HT_TRUE;
		return ( HT_OK );
	}
	else 
	{
		HTRESULT hr = HT_FAIL;
		HTvector3 rvecPickPos;		
		*bSkinnedModel = HT_FALSE;
		hr = m_p3DMgr->HT_hrPick(&rvecPickPos, idObj, (HTfloat)iX, (HTfloat)iY);
		pInfo->m_vecPosition = rvecPickPos;
		return hr;
	}
	return ( HT_FAIL );
}

HTbool CHTEngineHandler::HT_bObjectPicked( HTint iX, HTint iY, HTint idObj )
{
	// Skinned Model 만 체크하도록 한다.
	if ( m_p3DMgr->HT_eGetEObjectType( idObj ) == HT_EOBJTYPE_SKINNEDMODEL )
	{
		HTfloat	fDistance;
		if ( HT_FAILED( m_p3DMgr->HT_hrPick( &fDistance, idObj, (HTfloat)iX, (HTfloat)iY ) ) )
		{
			return ( HT_FALSE );
		}
		return ( HT_TRUE );
	}

	return ( HT_FALSE );
}

HTfloat CHTEngineHandler::HT_fGetTerrainHeight( HTfloat fX, HTfloat fZ, HTbool*	bOnObject )
{
	HT_CELL_COORD cellPos;
	HTvector3 vecPos( fX, 0.0f, fZ );

	if (this->HT_3DCOORD_TO_CELL( vecPos, cellPos ))
	{
		HTword wObjHeight = HT_wGetObjHeight( cellPos.x, cellPos.y, 0 );
		HTfloat fObjHeight = (HTfloat)wObjHeight/10.0f;

		if ( wObjHeight != 0 )
		{
			if (bOnObject) *bOnObject = HT_TRUE;
			HTfloat fTerrainHeight = m_p3DMgr->HT_fGetMidHeight( m_idTerrain, fX, fZ );

			//CHTString strD;
			//strD.HT_szFormat( "fTerrainHeight : %f, fObjHeight : %f", fTerrainHeight, fObjHeight );
			//MessageBox( HT_NULL, (HTtchar*)strD, "", MB_OK );

			if ( fObjHeight > fTerrainHeight )
			{
				vecPos.y = fObjHeight;
			}
			else
			{
				vecPos.y = fTerrainHeight;
			}
		}
		else
		{
			vecPos.y = m_p3DMgr->HT_fGetMidHeight( m_idTerrain, fX, fZ );
			if (bOnObject)  *bOnObject = HT_FALSE;
		}	
	}

	return ( vecPos.y );
}

HTRESULT CHTEngineHandler::HT_hrCheckScreen()
{
	return ( m_p3DMgr->HT_hrCheckScreen() );
}

HTint CHTEngineHandler::HT_iCreateNullModel( HTvector3& vecPos )
{
	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
	objParam.dwID = HT_NULL_MODEL_ID;
	objParam.vecPosition = vecPos;

	HTint idObjID;
	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateMapObject( HTdword dwID, HTvector3& vecPos )
{
	// 여기서 데이타를 로드한다!
	HTint idObjID = -1;

	CHTString strFile, strPack;
	if ( !m_pResMgr->HT_bGetFileName( dwID, strFile ) )
	{
		return ( -1 );
	}

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
	objParam.byForWhat = HT_EOBJ_FOR_MAP;
	objParam.strFileName = strFile;
	objParam.clrDiffuse = m_clrDiffuseObjs;
	objParam.clrAmbient = m_clrAmbientObjs;
	objParam.clrEmissive = m_clrEmissiveObjs;
	objParam.fSizePerGrid = 1.0f;	// fog enable
	objParam.vecPosition = vecPos;

	strPack = _T("resource\\object\\OBJTMD.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strPack );

	m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strObjModel, 
		m_oResourcePath.strObjTexture );

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	if ( m_bWorldLoaded )
	{
		HT_AABB oAABB;
		HTmatrix matTransform;
		m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
		m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_NONE, 0 );
	}

	++m_nObjs;

	m_bUpdateViewingObjs = HT_TRUE;

	m_pPackFileMgr->HT_hrClosePackFile( strPack );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateFieldItem( HTdword dwItemID, HTvector3& vecPos )
{
	HTint idObjID = -1;

	if ( dwItemID == HT_ITEM_ARROW_MODELID )
	{	// 화살 전용
		HTdword dwModelID = 0;
		if ( m_pResMgr->HT_bGetSocketModelID( dwItemID, dwModelID ) )
		{
			this->HT_hrLoadToResPool( dwModelID, HT_FALSE );

			HT_EOBJ_CREATEPARAM objParam;
			objParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
			objParam.byForWhat = HT_EOBJ_FOR_MAP;
			objParam.dwID = dwModelID;
			objParam.clrDiffuse = HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
			objParam.clrAmbient = HT_COLOR( 0.8f, 0.8f, 0.8f, 0.8f );
			objParam.clrEmissive = objParam.clrAmbient;
			objParam.fSizePerGrid = 1.0f;	// fog enable
			objParam.vecPosition = vecPos;
			objParam.oProperty.iCollisionFlag = HT_FALSE;
			objParam.oProperty.iPickableFlag = HT_FALSE;
			objParam.vecScale = HTvector3( 1.0f, 1.0f, 1.0f );

			if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
			{
				return ( -1 );
			}

			if ( m_bWorldLoaded )
			{
				HT_AABB oAABB;
				HTmatrix matTransform;
				m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
				m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );
			}

			HTdword dwTexID;
			if ( m_pResMgr->HT_bGetSocketTexID( dwItemID, dwTexID ) && dwTexID > 0 )
			{
				CHTString strFile;
				m_pResMgr->HT_bGetFileName( dwTexID, strFile );
				m_p3DMgr->HT_hrChangeTexture( idObjID, strFile );
			}

			++m_nObjs;

			m_bUpdateViewingObjs = HT_TRUE;
			m_mapModelIndex.insert( std::map<HTint,HTdword>::value_type( idObjID, dwItemID ) );
		}
		else
		{
			return -1;
		}
	}
	else if ( HT_IS_ITEM( dwItemID ) )
	{
		HTdword dwModelID;
		CHTString strFile;
		if ( !m_pResMgr->HT_bGetFallenModelID( dwItemID, dwModelID ) )
			return ( -1 );

		HT_hrLoadToResPool( dwModelID, HT_FALSE );

		HT_EOBJ_CREATEPARAM objParam;
		objParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
		objParam.byForWhat = HT_EOBJ_FOR_MAP;
		objParam.dwID = dwModelID;
		objParam.clrDiffuse = m_clrDiffuseChar;
		objParam.clrAmbient = m_clrAmbientChar;
		objParam.clrEmissive = m_clrEmissiveChar;
		objParam.fSizePerGrid = 1.0f;	// fog enable
		objParam.vecPosition = vecPos;
		objParam.oProperty.iCollisionFlag = HT_FALSE;
		objParam.oProperty.iPickableFlag = HT_TRUE;

		HTfloat fScale = 1.0f;
		if ( m_pResMgr->HT_bGetNAGScale( dwModelID, fScale ) )
			objParam.vecScale = HTvector3( fScale, fScale, fScale );

		HT_CELL_COORD cellPos;
		HT_3DCOORD_TO_CELL( objParam.vecPosition, cellPos );
		HTword wObjHeight = HT_wGetObjHeight( cellPos.x, cellPos.y, 0 );
		if ( wObjHeight != 0 )
			objParam.vecPosition.y = (HTfloat)wObjHeight/10.0f;		

		if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
		{
			return ( -1 );
		}

		if ( m_bWorldLoaded )
		{
			HT_AABB oAABB;
			HTmatrix matTransform;
			m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
			m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );
		}

		HTdword dwTexID;
		if ( m_pResMgr->HT_bGetFallenModelTexID( dwItemID, dwTexID ) && dwTexID > 0 )
		{
			m_pResMgr->HT_bGetFileName( dwTexID, strFile );
			m_p3DMgr->HT_hrChangeTexture( idObjID, strFile );
		}

		++m_nObjs;

		m_bUpdateViewingObjs = HT_TRUE;

		m_mapModelIndex.insert( std::map<HTint,HTdword>::value_type( idObjID, dwItemID ) );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateUIItem( HTdword dwItemID, HTvector3& vecPos )
{
	HTint idObjID = -1;

	if ( HT_IS_ITEM( dwItemID ) )
	{
		HTdword dwModelID;
		CHTString strFile;
		if ( !m_pResMgr->HT_bGetInvenTexID( dwItemID, dwModelID ) )
			return ( -1 );

		HT_EOBJ_CREATEPARAM objParam;
		objParam.eObjType = HT_EOBJTYPE_2DSPRITE;
		objParam.dwID = dwModelID;
		objParam.vecPosition = vecPos;
		objParam.byForWhat = HT_EOBJ_FOR_UI;

		if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
		{
			return ( -1 );
		}
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreate2DSprite( HTdword dwID, HTvector3& vecPos, HTbyte byForWhat)
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_2DSPRITE;
	objParam.dwID = dwID;
	objParam.vecPosition = vecPos;
	objParam.byForWhat = byForWhat;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint
CHTEngineHandler::HT_iCreate2DUISprite( HTdword dwID, HTvector3& vecPos, HTbyte byForWhat )
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_2DUISPRITE;
	objParam.dwID = dwID;
	objParam.vecPosition = vecPos;
	objParam.byForWhat = byForWhat;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint
CHTEngineHandler::HT_iCreate2DUIWindowSprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack )
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_2DUISPRITE;
	objParam.dwID = dwID;
	objParam.vecPosition.x = (HTfloat)iPosX;
	objParam.vecPosition.y = (HTfloat)iPosY;
	objParam.iWidth = iSizeX;
	objParam.iHeight = iSizeY;
	objParam.clrDiffuse = clrBack;
	objParam.byForWhat = HT_EOBJ_FOR_UI;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTRESULT
CHTEngineHandler::HT_hrRender2DUI()
{
	return m_p3DMgr->HT_hrBatchRender2DUISprite();
}

HTRESULT
CHTEngineHandler::HT_hrClearUISpriteVB()
{
	return m_p3DMgr->HT_hrClearUISpriteVB();
}

//---------------------------------------------------------------------------------------------
// HTRESULT				HT_hrChangeColor( HTint idObj, HT_COLOR	clrDiffuse)
// M : 200308 
// I : idObj - 엔진 오브젝트 아이디, clrDiffuse - 바꿀 색
//---------------------------------------------------------------------------------------------
HTRESULT
CHTEngineHandler::HT_hrChangeColor( HTint idObj, HT_COLOR	clrDiffuse)
{
	return m_p3DMgr->HT_hrChangeColor( idObj, clrDiffuse );
}

//---------------------------------------------------------------------------------------------
// HTint	HT_iCreateMiniMap( HTdword dwID, HTvector3& vecPos, 
//					HTint iSteps, HTfloat fSpace, HTint iObjDrawSteps, HTint iWidth, HTint iHeight)
// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
// I : dwID - 아이디, vecPos - 위치(입력하면 int로 변환되어 사용된다.), iWidth/iHeight - 크기
//---------------------------------------------------------------------------------------------
HTint
CHTEngineHandler::HT_iCreateMiniMap( HTdword dwID, HTvector3& vecPos, 
									HTint iSteps, HTfloat fSpace, HTint iObjDrawSteps,
									HTint iWidth, HTint iHeight)
{
	if (iWidth==0 || iHeight==0) return -1;
	HTint idObjID = -1;

	m_vMiniMapPos		= vecPos; 
	m_iMiniMapWidth		= iWidth;
	m_iMiniMapHeight	= iHeight;
	m_iObjDrawSteps		= iObjDrawSteps;
	m_fMiniMapSpace		= fSpace;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType		= HT_EOBJTYPE_MINIMAP;	
	objParam.byForWhat		= HT_EOBJ_FOR_UI;
	objParam.dwID			= dwID;
	objParam.vecPosition	= m_vMiniMapPos;
	objParam.iWidth			= m_iMiniMapWidth;
	objParam.iHeight		= m_iMiniMapHeight;
	objParam.clrDiffuse		= 0xffffffff;
	objParam.iSteps			= iSteps;
	objParam.fSpace			= fSpace;
	objParam.iObjDrawSteps	= iObjDrawSteps;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	m_idMiniMap = idObjID;

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateBillboard( HTdword dwID, HTvector3& vecPos )
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_BILLBOARD;
	objParam.byForWhat = HT_EOBJ_FOR_UI;
	objParam.dwID = dwID;
	objParam.vecPosition = vecPos;
	objParam.iHeight = 10;
	objParam.iWidth = 30;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateCharacter( HTdword dwID, HTvector3& vecPos, HTint iHairType, HTint iFaceType, HTint idWearItem , HTint idShoesItem )
{
	HTint idObjID = -1;
	HTdword dwModelID;
	CHTString strFile;
	if ( !m_pResMgr->HT_bGetModelFileID( dwID, dwModelID ) )
		return ( -1 );

	//HT_hrLoadToResPool( dwModelID, HT_FALSE );

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_SKINNEDMODEL;
	objParam.byForWhat = HT_EOBJ_FOR_MAP;
	objParam.dwID = dwModelID;
	objParam.clrDiffuse = m_clrDiffuseChar;
	objParam.clrAmbient = m_clrAmbientChar;
	objParam.clrEmissive = m_clrEmissiveChar;
	objParam.clrSpecular = m_clrSpecularChar;
	objParam.fRippleSpeed = 1.0f;	// shadow
	objParam.fSizePerGrid = 1.0f;	// fog enable

	if ( dwID == HT_ID_CHARACTER_GM )
	{
		objParam.fFOV = 0.0f;			// change armor
		objParam.fTextureSpeed = 0.0f;	// share animation
	}
	else
	{
		objParam.fFOV = 1.0f;			// change armor
		objParam.fTextureSpeed = 1.0f;	// share animation
	}
	objParam.vecPosition = vecPos;
	if ( m_bUseRTShadow )
		objParam.bUseRealtimeShadow = HT_TRUE;	// real time shadow

	HT_CELL_COORD cellPos;
	HT_3DCOORD_TO_CELL( objParam.vecPosition, cellPos );
	HTword wObjHeight = HT_wGetObjHeight( cellPos.x, cellPos.y, 0 );
	if ( wObjHeight != 0 )
		objParam.vecPosition.y = (HTfloat)wObjHeight/10.0f;		

	m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam );

	this->HT_vSetCanModify( idObjID );

	if ( m_bWorldLoaded )
	{
		HT_AABB oAABB;
		HTmatrix matTransform;
		m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
		m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );
	}

	if ( dwID != HT_ID_CHARACTER_GM )
	{
		m_p3DMgr->HT_hrHideAllMesh( idObjID );

		HT_hrChangeHead( idObjID, dwID, iHairType, iFaceType );

		if ( idWearItem <= 0 && idShoesItem <= 0 )
		{
			HT_hrEquipDefault( idObjID, dwID );
		}
		else
		{
			if ( idWearItem > 0 )
				HT_hrChangeClothes( idObjID, dwID, idWearItem );

			if ( idShoesItem > 0 )
				HT_hrChangeShoes( idObjID, dwID, idShoesItem );
		}
	}

	//// Load Animation
	//HTdword dwStateID, dwAnimID, dwHairAnimID;
	//CHTString strTable = _T("PCStateAni");
	//HTuint iCount = m_pResMgr->HT_nGetItemCount( strTable );
	//for ( HTuint i = 0; i < iCount; i++ )
	//{
	//	dwStateID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
	//	dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwStateID );
	//	HT_hrLoadToResPool( dwAnimID, HT_FALSE );

	//	dwHairAnimID = m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwHairAnimID );
	//	HT_hrLoadToResPool( dwHairAnimID, HT_FALSE );
	//	dwHairAnimID = m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwHairAnimID );
	//	HT_hrLoadToResPool( dwHairAnimID, HT_FALSE );

	//	dwAnimID = HT_dwGetFApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
	//	HT_hrLoadToResPool( dwAnimID, HT_FALSE );
	//	dwAnimID = HT_dwGetBApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
	//	HT_hrLoadToResPool( dwAnimID, HT_FALSE );
	//}

	//// 기본 에니메이션으로 세팅한다.
	HT_hrStartAnimation( idObjID, dwID, HT_ANISTATE_STD, -1 );

	// 일반적인 맵 오브젝트 생성
	++m_nObjs;
	m_bUpdateViewingObjs = HT_TRUE;

	m_mapModelIndex.insert( std::map<HTint,HTdword>::value_type( idObjID, dwID ) );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateNPC( HTdword dwID, HTvector3& vecPos )
{
	HTint idObjID = -1;
	HTdword dwModelID, dwAniID;

	if ( !m_pResMgr->HT_bGetModelFileID( dwID, dwModelID ) )
		return ( -1 );

	HT_hrLoadToResPool( dwModelID, HT_TRUE );

	if ( m_pResMgr->HT_bGetSTDAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetMOVAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetIDLAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}

	// Sound Data를 필요하면 로딩한다.
	HTdword dwSoundID;
	CHTString strFile;
	if ( m_pResMgr->HT_bGetClickSoundID( dwID, dwSoundID ) )
	{
		if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
		{
			m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
		}
	}

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_SKINNEDMODEL;
	objParam.dwID = dwModelID;
	objParam.clrDiffuse = m_clrDiffuseChar;
	objParam.clrAmbient = m_clrAmbientChar;
	objParam.clrEmissive = m_clrEmissiveChar;
	objParam.clrSpecular = m_clrSpecularChar;
	objParam.fRippleSpeed = 1.0f;	// shadow
	objParam.fSizePerGrid = 1.0f;	// fog enable
	objParam.fTextureSpeed = 1.0f;	// share animation
	objParam.vecPosition = vecPos;
	objParam.byForWhat = HT_EOBJ_FOR_MAP;
	if ( m_bUseRTShadow )
		objParam.bUseRealtimeShadow = HT_TRUE;	// real time shadow

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) ) return ( -1 );

	if ( m_bWorldLoaded )
	{
		HT_AABB oAABB;
		HTmatrix matTransform;
		m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
		m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );	// TODO
	}

	++m_nObjs;
	m_bUpdateViewingObjs = HT_TRUE;

	m_mapModelIndex.insert( std::map<HTint,HTdword>::value_type( idObjID, dwID ) );

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint CHTEngineHandler::HT_iCreateMonster( HTdword dwID, HTvector3& vecPos )
{
	HTint idObjID = -1;
	HTdword dwBasicModelID, dwAniID;
	HTdword dwFXID, dwSoundID;

	//if ( !m_pResMgr->HT_bGetModelFileID( dwID, dwModelID ) )
	//	return ( -1 );
	const HTuint nNumMonsterMaxMesh = 5;
	HTuint nNumMesh;
	HTdword arrdwMesh[nNumMonsterMaxMesh];
	HTdword arrdwTex[nNumMonsterMaxMesh];
	HTdword dwItemR, dwItemL, dwItemRTex, dwItemLTex;
	if ( !m_pResMgr->HT_bGetMonModelTexItem( dwID,
		nNumMesh, dwBasicModelID,
		arrdwMesh[0], arrdwMesh[1], arrdwMesh[2], arrdwMesh[3], arrdwMesh[4],
		arrdwTex[0], arrdwTex[1], arrdwTex[2], arrdwTex[3], arrdwTex[4],
		dwItemR, dwItemRTex, dwItemL, dwItemLTex ) ) return -1;

	// Load Mesh
	if ( nNumMesh == 0 )
	{
		return this->HT_iCreateNullModel( vecPos );
	}
	else if ( nNumMesh == 1 )
	{
		this->HT_hrLoadToResPool( dwBasicModelID, HT_TRUE );
	}
	else
	{
		this->HT_hrLoadToResPool( dwBasicModelID, HT_TRUE );
	}

	if ( !m_pResMgr->HT_bGetMonFXID( dwID, dwFXID ) )
		return ( -1 );

	// Load Ani
	if ( m_pResMgr->HT_bGetSTDAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetIDLAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetWLKAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetRUNAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetATK1AniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetATK2AniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetHITAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}
	if ( m_pResMgr->HT_bGetDIEAniID( dwID, dwAniID ) )
	{
		HT_hrLoadToResPool( dwAniID, HT_TRUE );
	}

	// Sound Data를 필요하면 로딩한다.
	CHTString strFile;
	if ( m_pResMgr->HT_bGetMonFXID( dwID, dwFXID ) )
	{
		if ( m_pResMgr->HT_bGetMonAttackSoundID1( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonAttackSoundID2( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonHitSoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonHit2SoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonWalkSoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonRunSoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonIdleSoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
		if ( m_pResMgr->HT_bGetMonDieSoundID( dwFXID, dwSoundID ) )
		{
			if ( m_pResMgr->HT_bGetFileName( dwSoundID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwSoundID, strFile );
			}
		}
	}

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_SKINNEDMODEL;
	objParam.dwID = dwBasicModelID;

	objParam.clrAmbient = m_clrAmbientChar;
	objParam.clrEmissive = m_clrEmissiveChar;
	//	objParam.clrSpecular = m_clrSpecularChar;
	objParam.clrSpecular = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );

	HT_COLOR clrMonster;
	m_pResMgr->HT_bGetMonColor( dwID, clrMonster );

	if ( clrMonster.r == 0.0f && clrMonster.g == 0.0f && clrMonster.b == 0.0f )
	{
		objParam.clrDiffuse = m_clrDiffuseChar;
	}
	else
	{
		objParam.clrDiffuse = clrMonster;
		objParam.clrEmissive = clrMonster;
	}

	objParam.fRippleSpeed = 1.0f;	// shadow
	objParam.fSizePerGrid = 1.0f;	// fog enable
	objParam.fTextureSpeed = 1.0f;	// share animation
	objParam.vecPosition = vecPos;
	objParam.byForWhat = HT_EOBJ_FOR_MAP;
	if ( m_bUseRTShadow )
		objParam.bUseRealtimeShadow = HT_TRUE;	// real time shadow

	HTfloat fScale = 1.0f;
	m_pResMgr->HT_bGetMonScale( dwID, fScale );
	objParam.vecScale = HTvector3( fScale, fScale, fScale );

	if ( nNumMesh == 1 )
	{
		// Basic Mesh 에 있는 Bounding Box 정보만 필요한 몬스터도 존재한다.
		if ( arrdwMesh[0] == 0 )	
		{
			objParam.fFOV = 1.0f; // Change Armor
			if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) ) return ( -1 );
			m_p3DMgr->HT_hrHideAllMesh( idObjID );
		}
		else
		{
			if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) ) return ( -1 );
			m_pResMgr->HT_bGetFileName( arrdwTex[0], strFile );
			m_p3DMgr->HT_hrChangeTexture( idObjID, strFile );
		}
	}
	else
	{
		objParam.fFOV = 1.0f; // Change Armor
		if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) ) return ( -1 );
		for ( HTuint i = 0; i < nNumMesh; ++i )
		{
			if ( arrdwMesh[i] > 0 && arrdwTex[i] > 0 )
			{
				this->HT_hrLoadToResPool4MonsterMesh( arrdwMesh[i], HT_TRUE );
				m_p3DMgr->HT_hrShowMesh( idObjID, arrdwMesh[i], HT_MODELPART_MONSTER );
				m_pResMgr->HT_bGetFileName( arrdwTex[i], strFile );
				m_p3DMgr->HT_hrChangeTexture( idObjID, strFile, arrdwMesh[i] );
			}
		}
	}

	CHTString strSocket;

	// Equip Item for Right Hand
	if ( dwItemR > 0 && dwItemRTex > 0 )
	{
		strSocket = _T("R_WPN");
		this->HT_hrAttachObject( idObjID, strSocket, dwItemR, 1.0f );
		m_pResMgr->HT_bGetFileName( dwItemRTex, strFile );
		m_p3DMgr->HT_hrChangeSocketTexture( idObjID, strSocket, strFile );
	}

	// Equip Item for Left Hand
	if ( dwItemL > 0 && dwItemLTex > 0 )
	{
		strSocket = _T("L_WPN");
		this->HT_hrAttachObject( idObjID, strSocket, dwItemL, 1.0f );
		m_pResMgr->HT_bGetFileName( dwItemLTex, strFile );
		m_p3DMgr->HT_hrChangeSocketTexture( idObjID, strSocket, strFile );
	}

	if ( m_bWorldLoaded )
	{
		HT_AABB oAABB;
		HTmatrix matTransform;
		m_p3DMgr->HT_hrGetBoundingBox( idObjID, &oAABB, &matTransform );
		m_pMapSystem->HT_hrInsertObject( idObjID, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );	// TODO
	}

	// HK FX
	// 항상 FX를 달고 다니는 놈이라면 셋팅한다.
	HTdword dwFX;
	if ( m_pFXMAPResMgr->HT_bGetAlwaysFX( dwFXID, dwFX ) )
	{
		if ( dwFX > 0 )
		{
			HTint idFX;
			this->HT_hrStartSFX( &idFX, dwFX, idObjID, HT_TRUE );
			CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( idObjID );
			if ( pObj )
			{
				pObj->HT_hrSetFXID( m_oIDFXMgr.idMonsterEtc, idFX );
			}
		}
	}

	++m_nObjs;
	m_bUpdateViewingObjs = HT_TRUE;

	m_mapModelIndex.insert( std::map<HTint,HTdword>::value_type( idObjID, dwID ) );

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTRESULT CHTEngineHandler::HT_hrLoadCharacterData()
{
	CHTString strTable;

	// Open Pack File!
	CHTString strFile, strTexPC1, strTexPC2;

	//	HTfloat fTempStartPercent, fTempNextPercent;
	//	fTempStartPercent = m_fLoadingStartPercent;
	//	fTempNextPercent = m_fLoadingNextPercent;

	//	m_fLoadingNextPercent = m_fLoadingStartPercent + (fTempNextPercent-fTempStartPercent)*2.0f/10.0f;

	// Load character's textures - wear, hair, face, shoes
	strTexPC1 = _T("resource\\object\\PC\\PCTex.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strTexPC1 );
	strTexPC2 = _T("resource\\object\\PC\\PCTex2.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strTexPC2 );

	strTable = HT_RES_TABLENAME_PCTEX;
	CHTString strPCMesh( _T("resource\\object\\PC\\Mesh") );
	CHTString strPCTex( _T("resource\\object\\PC\\PCTex") );
	CHTString strPCAni( _T("resource\\object\\PC\\Ani") );
	//HT_hrLoadTextures( strTable, strPCMesh, strPCTex );
	HTuint n, nMax = m_pResMgr->HT_nGetItemCount( strTable );
	for ( n = 0; n < nMax; ++n )
	{
		// 2.0f는 Texture 로딩이 시작과 끝인 0.5와 0.7의 차이값이다.
		HTfloat fT = (HTfloat)nMax/2.0f;
		HTfloat fS = (HTfloat)n/fT + 0.5f;
		HTfloat fE = (HTfloat)(n+1)/fT + 0.5f;
		///////////////////////////////////////////////////////
		//	여기에 로딩이미지가 들어간다.
		///////////////////////////////////////////////////////

		HTdword dwID = m_pResMgr->HT_dwGetIDByIndex( strTable, n );
		if ( m_pResMgr->HT_bGetFileName( dwID, strFile ) )
		{
			if ( m_iTextureDetailLevel == 1 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 3 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else if ( m_iTextureDetailLevel == 2 || m_iTextureDetailLevel == 3 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 1 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else
			{
				MessageBox( HT_NULL, _T("Not Valid Spec Value!"), _T("HT_hrLoadTexture Error!"), MB_OK );
			}

		}
		else
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Cannot find file name by ID[%d] table[%s]!", dwID, (HTtchar*)strTable );
			MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
			return ( HT_FAIL );
		}
	}

    m_pPackFileMgr->HT_hrClosePackFile( strTexPC1 );
	m_pPackFileMgr->HT_hrClosePackFile( strTexPC2 );

	// Load Basic Bone & Model & Animation
	for ( HTdword dwID = 1; dwID <= 9; ++dwID )
	{
		// 4.5f는 로딩이 시작하는 0.7과 0.9의 차이값을 2.0f으로 나눈 값이다.
		HTfloat fS = (HTfloat)(dwID-1)/4.5f + 0.7f;
		HTfloat fE = (HTfloat)dwID/4.5f + 0.7f;
		///////////////////////////////////////////////////////
		//	여기에 로딩이미지가 들어간다.
		///////////////////////////////////////////////////////

		HTdword dwModelID;
		HT_SHAREOBJ_TYPE eType = HT_SOBJTYPE_SKINNEDMODEL;
		strFile.HT_hrCleanUp();
		if ( m_pResMgr->HT_bGetModelFileID( dwID, dwModelID ) && m_pResMgr->HT_bGetFileName( dwModelID, strFile ) )
		{			
			m_p3DMgr->HT_vSetResourcePath( strPCMesh, strPCTex );
			m_p3DMgr->HT_hrLoadObject( eType, dwModelID, strFile );
		}

		// Load Animation
		HTdword dwStateID, dwAnimID, dwHairAnimID1, dwHairAnimID2, dwFApronAnimID, dwBApronAnimID;
		CHTString strTable = _T("PCStateAni");
		HTuint iCount = m_pResMgr->HT_nGetItemCount( strTable );
		eType = HT_SOBJTYPE_ANIMATION;
		for ( HTuint i = 0; i < iCount; i++ )
		{
			dwStateID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
			dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwStateID );
			dwFApronAnimID = HT_dwGetFApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
			dwBApronAnimID = HT_dwGetBApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
			m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwHairAnimID1 );
			m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwHairAnimID2 );

			m_p3DMgr->HT_vSetResourcePath( strPCAni, strPCTex );

			strFile.HT_hrCleanUp();
			if ( dwAnimID > 0 && m_pResMgr->HT_bGetFileName( dwAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwFApronAnimID > 0 && m_pResMgr->HT_bGetFileName( dwFApronAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwFApronAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwBApronAnimID > 0 && m_pResMgr->HT_bGetFileName( dwBApronAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwBApronAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwHairAnimID1 > 0 && m_pResMgr->HT_bGetFileName( dwHairAnimID1, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwHairAnimID1, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwHairAnimID2 > 0 && m_pResMgr->HT_bGetFileName( dwHairAnimID2, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwHairAnimID2, strFile );
			}
		}

		//		m_fLoadingStartPercent += (fTempNextPercent-fTempStartPercent)*2.0f/10.0f;
		//		m_fLoadingNextPercent += (fTempNextPercent-fTempStartPercent)*2.0f/10.0f;
	}	

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadCharacterTexture()
{
	CHTString strTable;
	CHTString strFile, strTexPC1, strTexPC2;

	// Load character's textures - wear, hair, face, shoes
	strTexPC1 = _T("resource\\object\\PC\\PCTex.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strTexPC1 );
	strTexPC2 = _T("resource\\object\\PC\\PCTex2.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strTexPC2 );

	strTable = HT_RES_TABLENAME_PCTEX;

	//HT_hrLoadTextures( strTable, strPCMesh, strPCTex );
	HTuint n, nMax = m_pResMgr->HT_nGetItemCount( strTable );
	for ( n = 0; n < nMax; ++n )
	{
		// 2.0f는 Texture 로딩이 시작과 끝인 0.5와 0.7의 차이값이다.
		HTfloat fT = (HTfloat)nMax/2.0f;
		HTfloat fS = (HTfloat)n/fT + 0.5f;
		HTfloat fE = (HTfloat)(n+1)/fT + 0.5f;
		///////////////////////////////////////////////////////
		//	여기에 로딩이미지가 들어간다.
		///////////////////////////////////////////////////////

		HTdword dwID = m_pResMgr->HT_dwGetIDByIndex( strTable, n );
		if ( m_pResMgr->HT_bGetFileName( dwID, strFile ) )
		{
			if ( m_iTextureDetailLevel == 1 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 3 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else if ( m_iTextureDetailLevel == 2 || m_iTextureDetailLevel == 3 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 1 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else
			{
				MessageBox( HT_NULL, _T("Not Valid Spec Value!"), _T("HT_hrLoadTexture Error!"), MB_OK );
			}

		}
		else
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Cannot find file name by ID[%d] table[%s]!", dwID, (HTtchar*)strTable );
			MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
			return ( HT_FAIL );
		}
	}
	m_pPackFileMgr->HT_hrClosePackFile( strTexPC1 );
	m_pPackFileMgr->HT_hrClosePackFile( strTexPC2 );
	return ( HT_OK );
}
HTRESULT CHTEngineHandler::HT_hrLoadCharacterBonModelAni( HTdword dwID )
{
	CHTString strFile;
	CHTString strPCMesh( _T("resource\\object\\PC\\Mesh") );
	CHTString strPCTex( _T("resource\\object\\PC\\PCTex") );
	CHTString strPCAni( _T("resource\\object\\PC\\Ani") );

	// Load Basic Bone & Model & Animation
	//for ( HTdword dwID = 1; dwID <= 9; ++dwID )
	{
		// 4.5f는 로딩이 시작하는 0.7과 0.9의 차이값을 2.0f으로 나눈 값이다.
		HTfloat fS = (HTfloat)(dwID-1)/4.5f + 0.7f;
		HTfloat fE = (HTfloat)dwID/4.5f + 0.7f;
		///////////////////////////////////////////////////////
		//	여기에 로딩이미지가 들어간다.
		///////////////////////////////////////////////////////

		HTdword dwModelID;
		HT_SHAREOBJ_TYPE eType = HT_SOBJTYPE_SKINNEDMODEL;
		strFile.HT_hrCleanUp();
		if ( m_pResMgr->HT_bGetModelFileID( dwID, dwModelID ) && m_pResMgr->HT_bGetFileName( dwModelID, strFile ) )
		{			
			m_p3DMgr->HT_vSetResourcePath( strPCMesh, strPCTex );
			m_p3DMgr->HT_hrLoadObject( eType, dwModelID, strFile );
		}

		// Load Animation
		HTdword dwStateID, dwAnimID, dwHairAnimID1, dwHairAnimID2, dwFApronAnimID, dwBApronAnimID;
		CHTString strTable = _T("PCStateAni");
		HTuint iCount = m_pResMgr->HT_nGetItemCount( strTable );
		eType = HT_SOBJTYPE_ANIMATION;
		for ( HTuint i = 0; i < iCount; i++ )
		{
			dwStateID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
			dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwStateID );
			dwFApronAnimID = HT_dwGetFApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
			dwBApronAnimID = HT_dwGetBApronAnimID( dwID, (HT_ANIM_STATE)dwStateID );
			m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwHairAnimID1 );
			m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwHairAnimID2 );

			m_p3DMgr->HT_vSetResourcePath( strPCAni, strPCTex );

			strFile.HT_hrCleanUp();
			if ( dwAnimID > 0 && m_pResMgr->HT_bGetFileName( dwAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwFApronAnimID > 0 && m_pResMgr->HT_bGetFileName( dwFApronAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwFApronAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwBApronAnimID > 0 && m_pResMgr->HT_bGetFileName( dwBApronAnimID, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwBApronAnimID, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwHairAnimID1 > 0 && m_pResMgr->HT_bGetFileName( dwHairAnimID1, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwHairAnimID1, strFile );
			}

			strFile.HT_hrCleanUp();
			if ( dwHairAnimID2 > 0 && m_pResMgr->HT_bGetFileName( dwHairAnimID2, strFile ) )
			{
				m_p3DMgr->HT_hrLoadObject( eType, dwHairAnimID2, strFile );
			}
		}
	}
	return ( HT_OK );
}


HTdword CHTEngineHandler::HT_dwGetItemUIID( HTdword dwID )
{
	HTdword dwReturn;

	if ( HT_IS_ITEM( dwID ) )
	{
		if ( !m_pResMgr->HT_bGetInvenTexID( dwID, dwReturn ) )
			return ( 0 );
		return ( dwReturn );
	}
	return ( 0 );
}

HTdword CHTEngineHandler::HT_dwGetSkillUIID( HTdword dwID )
{
	HTdword dwReturn;
	if ( HT_IS_PCSKILL( dwID ) )
	{
		if ( !m_pFXPCResMgr->HT_bGetUI( dwID, dwReturn ) )
			return ( 0 );
		return ( dwReturn );
	}
	return ( 0 );
}

HTRESULT CHTEngineHandler::HT_hrLoadETCData()
{
	CHTString strTable;

	strTable = HT_RES_TABLENAME_ETCTEX;
	HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSPRITE, 
		m_oResourcePath.strETC, m_oResourcePath.strETC );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadItemData()
{
	CHTString strTable, strItemTex1, strItemTex2;

	HTfloat fTempStartPercent, fTempNextPercent;
	fTempStartPercent = m_fLoadingStartPercent;
	fTempNextPercent = m_fLoadingNextPercent;

	m_fLoadingNextPercent = m_fLoadingStartPercent + (fTempNextPercent-fTempStartPercent)*2.0f/4.0f;

	strItemTex1 = _T("resource\\object\\Item\\ItemTex.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strItemTex1 );
	strItemTex2 = _T("resource\\object\\Item\\ItemTex2.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strItemTex2 );

	strTable = HT_RES_TABLENAME_ITEMTEX;
	HT_hrLoadTextures( strTable, m_oResourcePath.strItemModel, m_oResourcePath.strItemTexture );

	m_pPackFileMgr->HT_hrClosePackFile( strItemTex1 );
	m_pPackFileMgr->HT_hrClosePackFile( strItemTex2 );

	m_fLoadingStartPercent += (fTempNextPercent-fTempStartPercent)*2.0f/4.0f;
	m_fLoadingNextPercent += (fTempNextPercent-fTempStartPercent)*2.0f/4.0f;

	// Load TMD model files
	//strFile = _T("resource\\object\\ITEMTMD.hpk");
	//m_pPackFileMgr->HT_hrOpenPackFile( strFile );
	//strTable = HT_RES_TABLENAME_ITEMTMD;
	//	HT_hrLoadResource( strTable, HT_SOBJTYPE_RIGIDMODEL, 
	//		m_oResourcePath.strItemModel, m_oResourcePath.strItemTexture );
	//	m_pPackFileMgr->HT_hrClosePackFile( strFile );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadSoundData()
{
	CHTString strTable;

	// Load sound files
	HTfloat fTempStartPercent, fTempNextPercent;
	fTempStartPercent = m_fLoadingStartPercent;
	fTempNextPercent = m_fLoadingNextPercent;

	m_fLoadingNextPercent = m_fLoadingStartPercent + (fTempNextPercent-fTempStartPercent)*1.0f/3.0f;

	CHTString strPack;
	strPack = _T("resource\\sound\\PCSound.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strPack );
	strTable = HT_RES_TABLENAME_PCSOUND;
	HT_hrLoadResource( strTable, HT_SOBJTYPE_3DSAMPLE, 
		m_oResourcePath.strSound, m_oResourcePath.strSound );
	m_pPackFileMgr->HT_hrClosePackFile( strPack );

	m_fLoadingStartPercent += (fTempNextPercent-fTempStartPercent)*1.0f/3.0f;
	m_fLoadingNextPercent += (fTempNextPercent-fTempStartPercent)*1.0f/3.0f;

	strPack = _T("resource\\sound\\ItemSound.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strPack );
	strTable = HT_RES_TABLENAME_ITEMSOUND;
	HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSAMPLE, 
		m_oResourcePath.strSound, m_oResourcePath.strSound );
	m_pPackFileMgr->HT_hrClosePackFile( strPack );

	m_fLoadingStartPercent += (fTempNextPercent-fTempStartPercent)*1.0f/3.0f;
	m_fLoadingNextPercent += (fTempNextPercent-fTempStartPercent)*1.0f/3.0f;

	strPack = _T("resource\\sound\\ETCSound.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strPack );
	strTable = HT_RES_TABLENAME_ETCSOUND;
	HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSAMPLE, 
		m_oResourcePath.strSound, m_oResourcePath.strSound );
	m_pPackFileMgr->HT_hrClosePackFile( strPack );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadIntroUIData()
{
	CHTString strTable;

	CHTString strFile;
	strFile = _T("resource\\UI\\INTROUI.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strFile );
	strTable = HT_RES_TABLENAME_UIINTRO;
	//HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );
	HT_hrLoadResource( strTable, HT_SOBJTYPE_2DUISPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );
	m_pPackFileMgr->HT_hrClosePackFile( strFile );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadMainUIData()
{
	CHTString strTable( HT_RES_TABLENAME_UIMAIN );
	CHTString strFile1( _T("resource\\UI\\MAINUI.hpk") );
	CHTString strFile2( _T("resource\\UI\\MAIN_ITEM.hpk") );
	CHTString strFile3( _T("resource\\UI\\MAIN_RESOURCE.hpk") );
	CHTString strFile4( _T("resource\\UI\\MAIN_SKILL.hpk") );

	m_pPackFileMgr->HT_hrOpenPackFile( strFile1 );
	m_pPackFileMgr->HT_hrOpenPackFile( strFile2 );
	m_pPackFileMgr->HT_hrOpenPackFile( strFile3 );
	m_pPackFileMgr->HT_hrOpenPackFile( strFile4 );

	strTable = HT_RES_TABLENAME_UIMAIN;
	HT_hrLoadResource( strTable, HT_SOBJTYPE_2DUISPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );
	
	m_pPackFileMgr->HT_hrClosePackFile( strFile1 );
	m_pPackFileMgr->HT_hrClosePackFile( strFile2 );
	m_pPackFileMgr->HT_hrClosePackFile( strFile3 );
	m_pPackFileMgr->HT_hrClosePackFile( strFile4 );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadIntroUIData()
{
	CHTString strTable;
	strTable = HT_RES_TABLENAME_UIINTRO;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadSoundData()
{
	CHTString strTable;

	strTable = HT_RES_TABLENAME_PCSOUND;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	strTable = HT_RES_TABLENAME_ITEMSOUND;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	strTable = HT_RES_TABLENAME_ETCSOUND;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadCharacterData()
{
	CHTString strFile;
	//	strFile = _T("resource\\object\\PCTEX.hpk");
	//	m_pPackFileMgr->HT_hrClosePackFile( strFile );

	//strFile = _T("resource\\object\\PCMesh.hpk");
	//m_pPackFileMgr->HT_hrClosePackFile( strFile );

	//strFile = _T("resource\\object\\PCANI.hpk");
	//m_pPackFileMgr->HT_hrClosePackFile( strFile );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadItemData()
{
	CHTString strFile;

	//strFile = _T("resource\\object\\ITEMTex.hpk");
	//m_pPackFileMgr->HT_hrClosePackFile( strFile );

	//strFile = _T("resource\\object\\ITEMTMD.hpk");
	//m_pPackFileMgr->HT_hrClosePackFile( strFile );

	HT_RES_POOL_DATA* pData = HT_NULL;
	std::map<HTdword,HT_RES_POOL_DATA*>::iterator it = m_mapResPools.begin();
	while ( it != m_mapResPools.end() )
	{
		pData = (it->second);
		if ( pData )
		{
			HT_DELETE( pData );
			it = m_mapResPools.erase( it );
			m_p3DMgr->HT_hrUnLoadObject( it->first );
		}
		else
		{
			it++;
		}
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadMainUIData()
{
	CHTString strTable;
	strTable = HT_RES_TABLENAME_UIMAIN;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	//strTable = HT_RES_TABLENAME_3DSPR;
	//HT_hrUnloadResource( strTable );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnLoadETCData()
{
	CHTString strTable;
	strTable = HT_RES_TABLENAME_ETCTEX;
	HT_CHECK( HT_hrUnloadResource( strTable ) );

	return ( HT_OK );
}

HTvoid CHTEngineHandler::HT_vDestroyObject( HTint idObj, HTint index )
{
	if ( m_p3DMgr->HT_pGetObject( idObj ) == HT_NULL )
	{
		return;
	}

	if ( m_p3DMgr->HT_byEObjectForWhat( idObj ) == HT_EOBJ_FOR_MAP )
	{
		m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );
		m_setDontClickObjs.erase( idObj );
		--m_nObjs;
	}

	this->HT_vSetCanNOTModify( idObj );

	m_p3DMgr->HT_hrDestroyObject( idObj, index );
}

HTvoid CHTEngineHandler::HT_vDestroyCharacter( HTint idObj, HTint index )
{
	if ( m_p3DMgr->HT_pGetObject( idObj ) == HT_NULL )
		return;

	this->HT_vSetCanNOTModify( idObj );

	//-------------------------------------------------------------------------------
	// Unload Socket Items
	CHTString strSocket;
	strSocket = _T("RightHand");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("RightClaw");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("LeftClaw");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("BWeapon01");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("BWeapon02");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("Hat");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("SLD");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("BWeapon03");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("Arrow_Box");
	HT_hrDetachObject( idObj, strSocket );

	strSocket = _T("FApron");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("BApron");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("LShoulder");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("RShoulder");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("LThigh");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("RThigh");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("LKnee");
	HT_hrDetachObject( idObj, strSocket );
	strSocket = _T("RKnee");
	HT_hrDetachObject( idObj, strSocket );

	// Unload Model
	//HTint idTribe = 0;
	//std::map<HTint,HTdword>::iterator it = m_mapModelIndex.find( idObj );
	//if ( it != m_mapModelIndex.end() )
	//{
	//	HTdword dwModelID;
	//	if ( m_pResMgr->HT_bGetModelFileID( it->second, dwModelID ) )
	//	{
	//		HT_hrUnloadFromResPool( dwModelID );
	//	}

	//	idTribe = it->second;
	//	m_mapModelIndex.erase( it );
	//}

	// Unload Meshes
	this->HT_hrHideMeshFace( idObj );
	this->HT_hrHideMeshHair( idObj );
	this->HT_hrHideMeshDownWear( idObj );
	this->HT_hrHideMeshUpWear( idObj );
	this->HT_hrHideMeshHandWear( idObj );
	this->HT_hrHideMeshShoes( idObj );

	// Unload Animation
	//HTdword dwStateID, dwAnimID, dwHairAnimID;
	//CHTString strTable = _T("PCStateAni");
	//HTuint iCount = m_pResMgr->HT_nGetItemCount( strTable );
	//for ( HTuint i = 0; i < iCount; i++ )
	//{
	//	dwStateID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
	//	dwAnimID = HT_dwGetPCAniID( idTribe, (HT_ANIM_STATE)dwStateID );
	//	HT_hrUnloadFromResPool( dwAnimID );

	//	dwHairAnimID = m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwHairAnimID );
	//	HT_hrUnloadFromResPool( dwHairAnimID );
	//	dwHairAnimID = m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwHairAnimID );
	//	HT_hrUnloadFromResPool( dwHairAnimID );

	//	dwAnimID = HT_dwGetFApronAnimID( idTribe, (HT_ANIM_STATE)dwStateID );
	//	HT_hrUnloadFromResPool( dwAnimID );
	//	dwAnimID = HT_dwGetBApronAnimID( idTribe, (HT_ANIM_STATE)dwStateID );
	//	HT_hrUnloadFromResPool( dwAnimID );
	//}

	//-------------------------------------------------------------------------------
	m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );
	m_p3DMgr->HT_hrDestroyObject( idObj, index );
	m_setDontClickObjs.erase( idObj );
	--m_nObjs;

}

HTvoid CHTEngineHandler::HT_vDestroyFieldItem( HTint idObj, HTint index )
{
	if ( m_p3DMgr->HT_pGetObject( idObj ) == HT_NULL )
		return;

	this->HT_vSetCanNOTModify( idObj );

	HTdword dwResID = 0;
	std::map<HTint,HTdword>::iterator it = m_mapModelIndex.find( idObj );
	if ( it != m_mapModelIndex.end() )
	{
		dwResID = it->second;
		m_mapModelIndex.erase( it );
	}

	HTdword dwModelID;
	if ( m_pResMgr->HT_bGetFallenModelID( dwResID, dwModelID ) )
		HT_hrUnloadFromResPool( dwModelID );

	m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );
	m_p3DMgr->HT_hrDestroyObject( idObj, index );
	m_setDontClickObjs.erase( idObj );
	--m_nObjs;
}

HTvoid CHTEngineHandler::HT_vDestroyMonster( HTint idObj, HTint index )
{
	if ( m_p3DMgr->HT_pGetObject( idObj ) == HT_NULL )
		return;

	this->HT_vSetCanNOTModify( idObj );

	m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );
	m_p3DMgr->HT_hrDestroyObject( idObj, index );
	m_setDontClickObjs.erase( idObj );
	--m_nObjs;

	//-------------------------------------------------------------------------------
	HTdword dwResID = 0;
	std::map<HTint,HTdword>::iterator it = m_mapModelIndex.find( idObj );
	if ( it != m_mapModelIndex.end() )
	{
		dwResID = it->second;
		m_mapModelIndex.erase( it );
	}

	//-------------------------------------------------------------------------------
	// Unload 

	HTdword dwModelID, dwAniID;

	if ( !m_pResMgr->HT_bGetModelFileID( dwResID, dwModelID ) )
		return;

	HT_hrUnloadFromResPool( dwModelID );

	if ( m_pResMgr->HT_bGetSTDAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetIDLAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetWLKAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetRUNAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetATK1AniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetATK2AniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetHITAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetDIEAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
}

HTvoid CHTEngineHandler::HT_vDestroyNPC( HTint idObj, HTint index )
{
	if ( m_p3DMgr->HT_pGetObject( idObj ) == HT_NULL )
		return;

	this->HT_vSetCanNOTModify( idObj );

	m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );	// TEMP : TODO
	m_p3DMgr->HT_hrDestroyObject( idObj, index );
	m_setDontClickObjs.erase( idObj );
	--m_nObjs;

	//-------------------------------------------------------------------------------
	HTdword dwResID = 0;
	std::map<HTint,HTdword>::iterator it = m_mapModelIndex.find( idObj );
	if ( it != m_mapModelIndex.end() )
	{
		dwResID = it->second;
		m_mapModelIndex.erase( it );
	}

	//-------------------------------------------------------------------------------
	HTdword dwModelID, dwAniID;

	if ( !m_pResMgr->HT_bGetModelFileID( dwResID, dwModelID ) )
		return;

	HT_hrUnloadFromResPool( dwModelID );

	if ( m_pResMgr->HT_bGetSTDAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetMOVAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
	if ( m_pResMgr->HT_bGetIDLAniID( dwResID, dwAniID ) )
	{
		HT_hrUnloadFromResPool( dwAniID );
	}
}


HTRESULT CHTEngineHandler::HT_hrMoveObject( HTint idObj, HTvector3& vecTo, HTbool bObjMount )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_UPDATEOBJPARAM updateParam;
	updateParam.vecPosition = vecTo;
	updateParam.idCamera	= m_idCamera;

	if ( m_p3DMgr->HT_byEObjectForWhat( idObj ) != HT_EOBJ_FOR_MAP )
	{
		m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );
		return ( HT_OK );
	}

	if ( m_bWorldLoaded )
	{
		//if (bObjMount)		// 오브젝트 선택시와 비선택시를 구별합니다. (20021029 대호)
		//{
		//	HT_CELL_COORD cellPos;
		//	HT_3DCOORD_TO_CELL( updateParam.vecPosition, cellPos );
		//	HTword wObjHeight = HT_wGetObjHeight( cellPos.x, cellPos.y, 0 );
		//	if ( wObjHeight != 0 )
		//		updateParam.vecPosition.y = (HTfloat)wObjHeight/10.0f;		
		//}

		HTvector3 vecBefore;
		m_p3DMgr->HT_hrGetPosition( m_idMainCharacter, vecBefore );

		m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );

		//		if ( m_pMapSystem->HT_bCanMove( HT_OBJSIZE_SMALL, updateParam.vecPosition, 0 ) )
		{
			HT_AABB oAABB;
			HTmatrix matTransform;
			m_p3DMgr->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform );

			m_pMapSystem->HT_hrMoveObject( idObj, &oAABB, &matTransform, HT_OBJSIZE_NONE, 0 );	// TODO

			// Main Character를 이동시 그 위치에 맞는 공간음과 배경음을 틀어주어야 한다.
			if ( idObj == m_idMainCharacter )
			{
				m_iPrevAreaID = m_iAreaID;
				if ( m_fNowTimeInAllDay < 0.5f )	// 낮시간
					m_pMapSystem->HT_hrNotifySoundMove( HT_TRUE, vecTo );
				else
					m_pMapSystem->HT_hrNotifySoundMove( HT_FALSE, vecTo );

				m_iAreaID = m_pMapSystem->HT_iSetArea(vecTo);


				// 이동한 거리가 32미터될때마다 로드를 조금씩 한다.
				if ( CHTVector::HT_fVec3Length( &(m_vecStampPos - vecTo) ) > 320.0f )
				{
					m_vecStampPos = vecTo;
					HT_hrLoadMapObjsDynamic( vecTo );
				}
			}

			m_bUpdateViewingObjs = HT_TRUE;
		}
	}
	else
	{
		return ( HT_FAIL );
	}

	return ( HT_OK );
}

HTfloat CHTEngineHandler::HT_fGetObjectHeight( HTvector3& vecPos )
{
	HTfloat fHeight = 0.0f;

	if ( m_bWorldLoaded )
	{
		HT_CELL_COORD cellPos;
		HT_3DCOORD_TO_CELL( vecPos, cellPos );
		HTword wObjHeight = HT_wGetObjHeight( cellPos.x, cellPos.y, 0 );
		if ( wObjHeight != 0 )
			fHeight = (HTfloat)wObjHeight/10.0f;		
	}

	return ( fHeight );
}

HTRESULT CHTEngineHandler::HT_hrPreload( CHTConfigSystem* pCfg )
{
	HTint	iColorR, iColorG, iColorB;

	//----------------------------------------------------------------
	// 리소스 디렉토리를 세팅시킨다.
	pCfg->HT_hrGetValue( _T("PATH"), _T("charmodel"), m_oResourcePath.strCharacterModel );
	pCfg->HT_hrGetValue( _T("PATH"), _T("chartex"), m_oResourcePath.strCharacterTexture );
	pCfg->HT_hrGetValue( _T("PATH"), _T("charanim"), m_oResourcePath.strCharacterAnimation );
	pCfg->HT_hrGetValue( _T("PATH"), _T("itemmodel"), m_oResourcePath.strItemModel );
	pCfg->HT_hrGetValue( _T("PATH"), _T("itemtex"), m_oResourcePath.strItemTexture );
	pCfg->HT_hrGetValue( _T("PATH"), _T("npcmodel"), m_oResourcePath.strNPCModel );
	pCfg->HT_hrGetValue( _T("PATH"), _T("npctex"), m_oResourcePath.strNPCTexture );
	pCfg->HT_hrGetValue( _T("PATH"), _T("npcanim"), m_oResourcePath.strNPCAnimation );
	pCfg->HT_hrGetValue( _T("PATH"), _T("monstermodel"), m_oResourcePath.strMonsterModel );
	pCfg->HT_hrGetValue( _T("PATH"), _T("monstertex"), m_oResourcePath.strMonsterTexture );
	pCfg->HT_hrGetValue( _T("PATH"), _T("monsteranim"), m_oResourcePath.strMonsterAnimation );
	pCfg->HT_hrGetValue( _T("PATH"), _T("objmodel"), m_oResourcePath.strObjModel );
	pCfg->HT_hrGetValue( _T("PATH"), _T("objtex"), m_oResourcePath.strObjTexture );

	pCfg->HT_hrGetValue( _T("PATH"), _T("leveltex"), m_oResourcePath.strLevelTexture );
	pCfg->HT_hrGetValue( _T("PATH"), _T("sound"), m_oResourcePath.strSound );
	pCfg->HT_hrGetValue( _T("PATH"), _T("fx"), m_oResourcePath.strFX );
	pCfg->HT_hrGetValue( _T("PATH"), _T("interface"), m_oResourcePath.strInterface );
	pCfg->HT_hrGetValue( _T("PATH"), _T("etc"), m_oResourcePath.strETC );

	//----------------------------------------------------------------
	// 디버그용 폰트(Arial)를 생성한다.
	HT_EOBJ_CREATEPARAM fontParam;
	fontParam.eObjType = HT_EOBJTYPE_2DFONT;
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("font"), fontParam.strFileName );
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("size"), &fontParam.iHeight );
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("colorR"), &iColorR );
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("colorG"), &iColorG );
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("colorB"), &iColorB );
	fontParam.clrDiffuse = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	fontParam.iInationalType = g_iInationalType;

	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("posX"), &fontParam.vecPosition.x );
	pCfg->HT_hrGetValue( _T("DEBUGFONT"), _T("posY"), &fontParam.vecPosition.y );

	m_vecFPSText.x = fontParam.vecPosition.x;
	m_vecFPSText.y = fontParam.vecPosition.y;
	m_clrText = fontParam.clrDiffuse;

	//m_p3DMgr->HT_hrCreateObject( &m_idFontFPS, &fontParam );

	//----------------------------------------------------------------
	// 다른 폰트를 생성한다.
#ifdef HT_IS_TANTRA_LAUNCHER
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
//		fontParam.strFileName = _T("한빛나루.TTF");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("굴림");
		fontParam.iHeight = 12; 
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("굴림");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
	else if( g_iInationalType == INATIONALTYPE_CHINA )
	{
//		fontParam.strFileName = _T("ms-song");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("ms-song");
		fontParam.iHeight = 12;
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("ms-song");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
	else if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
//		fontParam.strFileName = _T("MSPGothic");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("MSPGothic");
		fontParam.iHeight = 12;
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("MSPGothic");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
	else if( g_iInationalType == INATIONALTYPE_TAIWAN )
	{
//		fontParam.strFileName = _T("新細明體");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("新細明體");
		fontParam.iHeight = 13;
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("新細明體");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
	else if( g_iInationalType == INATIONALTYPE_PHILIPPINE )
	{
//		fontParam.strFileName = _T("Arial");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("Arial");
		fontParam.iHeight = 14;
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("Arial");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
	else
	{
//		fontParam.strFileName = _T("Arial");
//		fontParam.iHeight = 30;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

		fontParam.strFileName = _T("Arial");
		fontParam.iHeight = 13;
		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//		fontParam.strFileName = _T("Arial");
//		fontParam.iHeight = 10;
//		m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
	}
#else
//	fontParam.strFileName = _T("한빛나루.TTF");
//	fontParam.iHeight = 30;
//	m_p3DMgr->HT_hrCreateObject( &m_idFontHanbitNaru30, &fontParam );

	fontParam.strFileName = _T("굴림");
	fontParam.iHeight = 12;
	m_p3DMgr->HT_hrCreateObject( &m_idFontGulim12, &fontParam );

//	fontParam.strFileName = _T("굴림");
//	fontParam.iHeight = 10;
//	m_p3DMgr->HT_hrCreateObject( &m_idFontGulim10, &fontParam );
#endif

	//----------------------------------------------------------------
	// NULL 모델을 로드해놓는다.
	CHTString strNullModel = _T("null.tmd");
	m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strETC, m_oResourcePath.strETC );
	m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, HT_NULL_MODEL_ID, strNullModel );

	//----------------------------------------------------------------
	// XML Resource Table 을 로딩한다.
	HT_CHECK( HT_hrInitResource() );

	//----------------------------------------------------------------
	pCfg->HT_hrGetValue( _T("SWORDWIND"), _T("lifetime"), &m_fLifeTime );
	pCfg->HT_hrGetValue( _T("SWORDWIND"), _T("centerratio"), &m_fCenterRatio );

	//----------------------------------------------------------------

	//----------------------------------------------------------------
	// Material 라이브러리 정보를 로딩한다.
#if 0
	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_CHARACTER, m_clrDiffuseChar );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_CHARACTER, m_clrAmbientChar );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_CHARACTER, m_clrEmissiveChar );
	m_pResMgr->HT_bGetSpecularColor( HT_ID_MATERIAL_CHARACTER, m_clrSpecularChar );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_STRUCTURE, m_clrDiffuse );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_STRUCTURE, m_clrAmbient );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_STRUCTURE, m_clrEmissive );
	m_pResMgr->HT_bGetSpecularColor( HT_ID_MATERIAL_STRUCTURE, m_clrSpecular );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_TREEBRANCH, m_clrDiffuseTree );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_TREEBRANCH, m_clrAmbientTree );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_TREEBRANCH, m_clrEmissiveTree );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_TREELEAF, m_clrDiffuseLeaf );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_TREELEAF, m_clrAmbientLeaf );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_TREELEAF, m_clrEmissiveLeaf );
#endif

	//------------------------------------------------------------------------------------
	// 게임의 기반이 되는 기본 시간값을 로딩한다.
	HTint iSecond;
	pCfg->HT_hrGetValue( _T("TIME"), _T("InitTime"), &iSecond );
	pCfg->HT_hrGetValue( _T("TIME"), _T("AniInterTime"), &m_fAniInterpolateTime );

	m_dwAllInitTimeStartTime = (HTdword)iSecond;

	pCfg->HT_hrGetValue( _T("CAMERA"), _T("updatecam"), &m_bUpdateByCamera );
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("grassalphaarea"), &m_fGrassAlphaDistance );
	pCfg->HT_hrGetValue( _T("CAMERA"), _T("camspeed"), &m_fCameraSpeed );

	//------------------------------------------------------------------------------------
	// 데이타 로딩 이전에 필요한 리소스들( 로딩화면, 커서 등 )을 로딩한다.
	HT_hrLoadETCData();

	//----------------------------------------------------------------
	// 화면 전체의 Fade in/out에 쓰일 텍스쳐를 생성한다.
	// 이 텍스쳐는 리소스테이블에 포함되지 않고 그냥 로딩한다.
	HT_EOBJ_CREATEPARAM maskParam;
	maskParam.eObjType = HT_EOBJTYPE_2DSPRITE;
	maskParam.dwID = 26007;
	maskParam.clrDiffuse = HT_COLOR( 1.0f, 0.0f, 0.0f, 0.0f );
	maskParam.vecPosition = HTvector3( 0.0f, 0.0f, 0.0f );
	maskParam.iWidth = m_iScreenWidth;
	maskParam.iHeight =m_iScreenHeight;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &m_oFadeScreen.idFade, &maskParam ) ) ) m_oFadeScreen.idFade = -1;

	return ( HT_OK );
}

// 맵에 관련된 메모리 및 데이타를 제거한다.
HTRESULT CHTEngineHandler::HT_hrUnloadMap()
{
	CHTString strPack;
	if ( m_dwCurrentMapID > 0 )
	{
		// NPC/Monster Pack을 메모리에서 해제한다.
		CHTString strTMDPAK, strANIPAK, strTEXNPCPAK1, strTEXNPCPAK2;
		CHTString strTMDPAK2, strANIPAK2, strTEXMOBPAK1, strTEXMOBPAK2;

		//m_pResMgr->HT_bGetNPCTEXPAKFileName( m_dwCurrentMapID, strTEXPAK );
		strTEXNPCPAK1 = _T("resource\\object\\NPC\\NPCTex.hpk");
		m_pPackFileMgr->HT_hrClosePackFile( strTEXNPCPAK1 );

		strTEXNPCPAK2 = _T("resource\\object\\NPC\\NPCTex2.hpk");
		m_pPackFileMgr->HT_hrClosePackFile( strTEXNPCPAK2 );

		//m_pResMgr->HT_bGetMONTEXPAKFileName( m_dwCurrentMapID, strTEXPAK2 );
		strTEXMOBPAK1 = _T("resource\\object\\Monster\\MonsterTex.hpk");
		m_pPackFileMgr->HT_hrClosePackFile( strTEXMOBPAK1 );

		strTEXMOBPAK2 = _T("resource\\object\\Monster\\MonsterTex2.hpk");
		m_pPackFileMgr->HT_hrClosePackFile( strTEXMOBPAK2 );

		//m_pResMgr->HT_bGetNPCANIPAKFileName( m_dwCurrentMapID, strANIPAK );
		//strANIPAK = _T("resource\\object\\") + strANIPAK;
		//m_pPackFileMgr->HT_hrClosePackFile( strANIPAK );

		//m_pResMgr->HT_bGetNPCPAKFileName( m_dwCurrentMapID, strTMDPAK );
		//strTMDPAK = _T("resource\\object\\") + strTMDPAK;
		//m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK );

		//m_pResMgr->HT_bGetMONANIPAKFileName( m_dwCurrentMapID, strANIPAK2 );
		//strANIPAK2 = _T("resource\\object\\") + strANIPAK2;
		//m_pPackFileMgr->HT_hrClosePackFile( strANIPAK2 );

		//m_pResMgr->HT_bGetMONPAKFileName( m_dwCurrentMapID, strTMDPAK2 );
		//strTMDPAK2 = _T("resource\\object\\") + strTMDPAK2;
		//m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK2 );

		m_pResMgr->HT_bGetNPCSoundFilesName( m_dwCurrentMapID, strPack );
		strPack = _T("resource\\sound\\") + strPack;
		m_pPackFileMgr->HT_hrClosePackFile( strPack );

		m_pResMgr->HT_bGetMonSoundFilesName( m_dwCurrentMapID, strPack );
		strPack = _T("resource\\sound\\") + strPack;
		m_pPackFileMgr->HT_hrClosePackFile( strPack );

		m_p3DMgr->HT_hrDestroyObject( m_idSun );
		m_p3DMgr->HT_hrDestroyObject( m_idMoon );
		m_p3DMgr->HT_hrDestroyObject( m_idFog );
		m_p3DMgr->HT_hrDestroyObject( m_idTerrain );

		this->HT_hrDestoryFXMAPMgr();
		this->HT_hrUnloadFXMAPResource();

#ifdef HT_IS_TANTRA_LAUNCHER
		//-----------------------------------------------------------------------
		// NPCScript 파일을 언로드한다.
		m_pNPCScriptMgr->HT_vCleanUp();
#endif

		// Default Water Made By Zorotoss
		if ( m_idWaterZoro != -1 ) m_p3DMgr->HT_hrDestroyObject( m_idWaterZoro );

		m_p3DMgr->HT_hrDestroyObject( m_idSkyCloud );
		m_p3DMgr->HT_hrDestroyObject( m_idSkyTerrain );
		m_p3DMgr->HT_hrDestroyObject( m_idSky );

		for ( HTuint i = 0; i < m_iNumWater; i++ )
			m_p3DMgr->HT_hrDestroyObject( m_arridWater[i] );

		m_iNumWater = m_iNumWaterZoro = 0;
		HT_DELETEARRAY( m_arridWater );
		HT_DELETEARRAY( m_arridWaterZoro );

		m_vectorViewingObjs.clear();
		m_vectorUpdateObjs.clear();

		m_p3DMgr->HT_hrUnloadMapEObjs();

		m_nObjs = 0;

		if ( m_pMapSystem ) 
			m_pMapSystem->HT_hrDestroy();

		HT_DELETE( m_pMapSystem );

		m_p3DMgr->HT_vForceReleaseTexture( HT_TRUE );
		// MapObj Unload
		std::map<HTdword,HTbool>::iterator it = m_mapLoadedOrNot.begin();
		while ( it != m_mapLoadedOrNot.end() )
		{
			if ( it->second )
			{
				m_p3DMgr->HT_hrUnLoadObject( it->first );
			}
			it = m_mapLoadedOrNot.erase( it );
		}

		// NPC Model/Ani Unload
		HT_RES_POOL_DATA* pData = HT_NULL;
		std::map<HTdword,HT_RES_POOL_DATA*>::iterator itLNPC = m_mapResPools.begin();
		while ( itLNPC != m_mapResPools.end() )
		{
			pData = (itLNPC->second);
			if ( pData && pData->bMapDefendent )
			{
				HT_DELETE( pData );
				m_p3DMgr->HT_hrUnLoadObject( itLNPC->first );
				itLNPC = m_mapResPools.erase( itLNPC );
			}
			else
			{
				itLNPC++;
			}
		}
		m_p3DMgr->HT_vForceReleaseTexture( HT_FALSE );

		if ( m_bDynamicLoading )
		{
			CHTString strOBJPath("resource\\object\\");
			CHTString strTMDPAK, strTEXPAK, strPOPTMDPAK, strPOPTEXPAK;
			m_pResMgr->HT_bGetOBJPAKFileName( m_dwCurrentMapID, strTMDPAK );
			m_pResMgr->HT_bGetOBJTEXPAKFileName( m_dwCurrentMapID, strTEXPAK );
			strTMDPAK = strOBJPath + strTMDPAK;
			strTEXPAK = strOBJPath + strTEXPAK;
			//strPOPTMDPAK = strOBJPath + _T("POPOBJTMB.hpk");
			//strPOPTEXPAK = strOBJPath + _T("POPOBJTEX.hpk");

			m_pResMgr->HT_bGetPopObjPackFilesName( m_dwCurrentMapID, strPOPTMDPAK );
			m_pResMgr->HT_bGetPopTexPackFilesName( m_dwCurrentMapID, strPOPTEXPAK );
			strPOPTMDPAK = strOBJPath + strPOPTMDPAK;
			strPOPTEXPAK = strOBJPath + strPOPTEXPAK;

			m_pPackFileMgr->HT_hrClosePackFile( strPOPTMDPAK );
			//m_pPackFileMgr->HT_hrClosePackFile( strPOPTEXPAK );
			m_pPackFileMgr->HT_hrClosePackFile( strTMDPAK );
			//m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );

			// NOTE By HK 20040128
			// 실시간으로 로드 하는 맵 오브젝트 텍스쳐에서 CreateTexture가 실패해서 생기는 문제를 해결하기 위해
			// LoadMap 에서 모든 Texture를 로드해 놓았으니 여기서 해제한다.
			CHTString strTex;
			m_pPackFileMgr->HT_hrOpenPackFile( strTEXPAK );
			{
				CHTString strOnlyTexPak( strTEXPAK );
				//strOnlyTexPak.HT_hrDeletePath();

				HTint iNumFile = m_pPackFileMgr->HT_iGetNumFile( strOnlyTexPak );
				for ( HTint iFile = 0; iFile < iNumFile; ++iFile )
				{
					if ( HT_SUCCEED( m_pPackFileMgr->HT_hrGetFileName( strOnlyTexPak, iFile, &strTex ) ) )
					{					
						if ( HT_FAILED( m_p3DMgr->HT_hrUnLoadTexture( strTex ) ) )
						{
							CHTString strDebug;
							strDebug.HT_szFormat( "Cannot Unload Map Obj Texture : %s", (HTtchar*)strTex );
							MessageBox( HT_NULL, strDebug, _T("MAP OBJ Texture Unload Error!"), MB_OK );
						}
					}
				}

				m_pPackFileMgr->HT_hrClosePackFile( strTEXPAK );
			}

			m_pPackFileMgr->HT_hrOpenPackFile( strPOPTEXPAK );
			{
				CHTString strOnlyTexPak( strPOPTEXPAK );
				//strOnlyTexPak.HT_hrDeletePath();

				HTint iNumFile = m_pPackFileMgr->HT_iGetNumFile( strOnlyTexPak );
				for ( HTint iFile = 0; iFile < iNumFile; ++iFile )
				{
					if ( HT_SUCCEED( m_pPackFileMgr->HT_hrGetFileName( strOnlyTexPak, iFile, &strTex ) ) )
					{
						if ( HT_FAILED( m_p3DMgr->HT_hrUnLoadTexture( strTex ) ) )
						{
							CHTString strDebug;
							strDebug.HT_szFormat( "Cannot Unload POP Obj Texture : %s", (HTtchar*)strTex );
							MessageBox( HT_NULL, strDebug, _T("MAP OBJ Texture Unload Error!"), MB_OK );
						}
					}
				}

				m_pPackFileMgr->HT_hrClosePackFile( strPOPTEXPAK );
			}
		}

		m_setToCreate.clear();
		m_setToLoad.clear();
		m_mapLoadedOrNot.clear();

		if ( m_idSubLight >= 0 )
		{
			m_p3DMgr->HT_hrOffLight( m_idSubLight );
			m_idSubLight = -1;
		}

		m_p3DMgr->HT_hrUnLoadObject( HT_MINIMAP_BMP_ID );

		m_setDontClickObjs.clear();
	}

	m_bWorldLoaded = HT_FALSE;

	m_dwCurrentMapID = 0;

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrStartAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwFXID, dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3;
	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;

	if ( HT_IS_CHARACTER( dwID ) )
	{
		CHTString strSocket( _T("Arrow") );
		this->HT_hrDetachObject( idObj, strSocket );

		dwAnimID = HT_dwGetPCAniID( dwID, eState );
		dwMotionSoundID1 = HT_dwGetPCSoundID1( dwID, eState );
		dwMotionSoundID2 = HT_dwGetPCSoundID2( dwID, eState );
		dwMotionSoundID3 = HT_dwGetPCSoundID3( dwID, eState );
	}
	else if ( HT_IS_NPC( dwID ) )
	{
		// 대장장이의 집게의 경우, 평상시는 안 보이다가, 아이들 동작( 집게를 내려침 )을 할때는 보여야 한다.
		CHTString strWeapon( _T("Weaponmake_item") );	
		switch( eState ) 
		{
		case HT_ANISTATE_STD:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetSTDAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_WLK:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetMOVAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_IDL:
			{
				m_p3DMgr->HT_hrShowMesh( idObj, strWeapon );
				m_pResMgr->HT_bGetIDLAniID( dwID, dwAnimID );

				// 20030110 HK : Idle FX 추가
				m_pResMgr->HT_bGetIdleFX( dwID, dwFXID );
				HTint idFX; this->HT_hrStartSFX( &idFX, dwFXID, idObj, HT_FALSE );

			}	break;
		default:
			break;
		}
	}
	else if ( HT_IS_MONSTER( dwID ) )
	{
		dwAnimID = HT_dwGetMonsterAniID( dwID, eState );
		if ( eState == HT_ANISTATE_DIE ) m_p3DMgr->HT_hrStopAlwaysFX( idObj );
	}
	else
	{
		return ( HT_FAIL );
	}

	HTdword dwSelectSound = HT_dwGetRandomSoundID( dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3 );

	this->HT_hrLoadToResPool( dwAnimID, HT_FALSE );
	m_p3DMgr->HT_hrStartAnimation( idObj, dwAnimID, dwSelectSound, iLoop );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrAddAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop, HTint idHead, HTint idWearItem, HTfloat fTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwFXID, dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3;
	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;

	if ( HT_IS_CHARACTER( dwID ) )
	{
		dwAnimID = HT_dwGetPCAniID( dwID, eState );
		dwMotionSoundID1 = HT_dwGetPCSoundID1( dwID, eState );
		dwMotionSoundID2 = HT_dwGetPCSoundID2( dwID, eState );
		dwMotionSoundID3 = HT_dwGetPCSoundID3( dwID, eState );
	}
	else if ( HT_IS_NPC( dwID ) )
	{
		switch( eState ) 
		{
		case HT_ANISTATE_STD:
			m_pResMgr->HT_bGetSTDAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_WLK:
			m_pResMgr->HT_bGetMOVAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_IDL:
			{
				m_pResMgr->HT_bGetIDLAniID( dwID, dwAnimID );

				// 20030110 HK : Idle FX 추가
				m_pResMgr->HT_bGetIdleFX( dwID, dwFXID );
				HTint idFX; this->HT_hrStartSFX( &idFX, dwFXID, idObj, HT_FALSE );

			}	break;
		default:
			break;
		}
	}
	else if ( HT_IS_MONSTER( dwID ) )
	{
		dwAnimID = HT_dwGetMonsterAniID( dwID, eState );
		if ( eState == HT_ANISTATE_DIE ) m_p3DMgr->HT_hrStopAlwaysFX( idObj );
	}
	else
	{
		return ( HT_FAIL );
	}

	HTdword dwSelectSound = HT_dwGetRandomSoundID( dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3 );

	m_p3DMgr->HT_hrAddAnimation( idObj, dwAnimID, dwSelectSound, iLoop, m_fAniInterpolateTime, fTime );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrStopAnimation( HTint idObj )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	m_p3DMgr->HT_hrStopAnimation( idObj );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrChangeAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop, HTint idHead, HTint idWearItem, HTfloat fTime, HTint idItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3, dwWeaponType, dwAnimType;
	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;
	dwWeaponType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
	dwAnimType = 0;

	if ( HT_IS_CHARACTER( dwID ) )
	{
		CHTString strSocket( _T("Arrow") );
		this->HT_hrDetachObject( idObj, strSocket );

		if ( idItem <= 0 || !HT_IS_ITEM_WEAPON( idItem ) )	
		{
			dwAnimID = HT_dwGetPCAniID( dwID, eState );
		}
		else
		{
			m_pResMgr->HT_bGetItemType( idItem, dwWeaponType );

			if ( HT_IS_ATKSTD_ANI( eState ) || eState == HT_ANISTATE_STD )
			{
				m_pResMgr->HT_bGetWPNATKSTDAniID( dwWeaponType, dwAnimType );
				dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwAnimType );
			}
			else if ( HT_IS_ATKWLK_ANI( eState ) || eState == HT_ANISTATE_WLK )
			{
				m_pResMgr->HT_bGetWPNATKWLKAniID( dwWeaponType, dwAnimType );
				dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwAnimType );
			}
			else if ( HT_IS_ATKRUN_ANI( eState ) || eState == HT_ANISTATE_RUN )
			{
				m_pResMgr->HT_bGetWPNATKRUNAniID( dwWeaponType, dwAnimType );
				dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwAnimType );
			}
			else if ( HT_IS_HIT_ANI( eState ) )
			{
				m_pResMgr->HT_bGetWPNHITAniID( dwWeaponType, dwAnimType );
				dwAnimID = HT_dwGetPCAniID( dwID, (HT_ANIM_STATE)dwAnimType );
			}
			else	// 일반 동작의 경우 종족별로 구분하여 처리한다.
			{
				dwAnimID = HT_dwGetPCAniID( dwID, eState );
			}
		}

		dwMotionSoundID1 = HT_dwGetPCSoundID1( dwID, eState );
		dwMotionSoundID2 = HT_dwGetPCSoundID2( dwID, eState );
		dwMotionSoundID3 = HT_dwGetPCSoundID3( dwID, eState );

		//--------------------------------------------------------------------
		// 소켓에 붙은 모델들의 에니메이션을 세팅해 준다.
		HTdword dwSocketAnimID;
		if ( idHead > 0 )
		{
			HTdword dwIDHead = HT_dwGetHeadID( dwID, idHead );
			HTdword dwHairType;
			strSocket = _T("Hair");
			m_pResMgr->HT_bGetHairType( idHead, dwHairType );
			switch ( dwHairType ) 
			{
			case 1:
				m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
				break;
			case 2:
				m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwSocketAnimID );
				break;
			default:
				m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
				break;
			}

			this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
			m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fTime );
		}

		dwSocketAnimID = 0;

		HTdword dwFApronAniID, dwBApronAniID;
		dwFApronAniID = HT_dwGetFApronAnimID( dwID, eState );
		dwBApronAniID = HT_dwGetBApronAnimID( dwID, eState );

		this->HT_hrLoadToResPool( dwFApronAniID, HT_FALSE );
		this->HT_hrLoadToResPool( dwBApronAniID, HT_FALSE );

		strSocket = _T("FApron");
		m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwFApronAniID, m_fAniInterpolateTime, fTime );

		strSocket = _T("BApron");
		m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwBApronAniID, m_fAniInterpolateTime, fTime );

		//--------------------------------------------------------------------
	}
	else if ( HT_IS_NPC( dwID ) )
	{
		// 대장장이의 집게의 경우, 평상시는 안 보이다가, 아이들 동작( 집게를 내려침 )을 할때는 보여야 한다.
		CHTString strWeapon( _T("Weaponmake_item") );	
		switch( eState ) 
		{
		case HT_ANISTATE_STD:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetSTDAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_WLK:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetMOVAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_IDL:
			m_p3DMgr->HT_hrShowMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetIDLAniID( dwID, dwAnimID );
			break;
		default:
			break;
		}
	}
	else if ( HT_IS_MONSTER( dwID ) )	
	{
		HTdword dwFXMonID;
		m_pResMgr->HT_bGetMonFXID( dwID, dwFXMonID );
		if ( HT_IS_FXMON( dwFXMonID ) )
		{
			dwMotionSoundID1 = HT_dwGetMonsterSoundID( dwFXMonID, eState );
		}

		dwAnimID = HT_dwGetMonsterAniID( dwID, eState );

		if ( dwAnimID <= 0 ) return HT_FAIL;
		if ( eState == HT_ANISTATE_DIE ) m_p3DMgr->HT_hrStopAlwaysFX( idObj );
	}
	else
	{
		return ( HT_FAIL );
	}

	HTdword dwSelectSound = HT_dwGetRandomSoundID( dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3 );

	this->HT_hrLoadToResPool( dwAnimID, HT_FALSE );
	m_p3DMgr->HT_hrChangeAnimation( idObj, dwAnimID, dwSelectSound, iLoop, m_fAniInterpolateTime, fTime );

	m_p3DMgr->HT_hrSetSwordWind( idObj, HT_FALSE );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrRenderObject( HTint idObj )
{
	return m_p3DMgr->HT_hrRenderObject( idObj );
}

HTRESULT CHTEngineHandler::HT_hrRenderObject( HTint idObj, HTword wLayer )
{
	return m_p3DMgr->HT_hrRenderObject( idObj, wLayer );
}

HTRESULT CHTEngineHandler::HT_hrSetLookAt( HTvector3& vecPos )
{
	m_p3DMgr->HT_hrSetLookAt( m_idCamera, vecPos );
	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrSetEye( HTvector3& vecPos )
{
	m_p3DMgr->HT_hrSetEye( m_idCamera, vecPos );
	return ( HT_OK );
}

HTvector3& CHTEngineHandler::HT_rvecGetEye()
{
	return ( m_p3DMgr->HT_vecGetEye( m_idCamera ) );
}

HTRESULT CHTEngineHandler::HT_hrScaleObject( HTint idObj, HTvector3& vecScale )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_UPDATEOBJPARAM updateParam;
	updateParam.idCamera = m_idCamera;
	updateParam.vecScale = vecScale;

	m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );

	return ( HT_OK );
}

// fIntensity 가 0.0 이면 원래의 화면이고, 1.0이면 최대로 페이드된 상태이다.
//HTRESULT CHTEngineHandler::HT_hrFadeScreen( HT_COLOR& clrFade, HTfloat fIntensity )
//{
//	HT_UPDATEOBJPARAM maskParam;
//	maskParam.clrDiffuse = clrFade;
//	maskParam.clrDiffuse.a = fIntensity;
//	m_p3DMgr->HT_hrUpdateObject( m_idFadeMask, &maskParam );
//
//	if ( fIntensity == 0.0f )
//	{
//		m_bFading = HT_FALSE;
//	}
//	else
//	{
//		m_bFading = HT_TRUE;
//	}
//
//	return ( HT_OK );
//}

HTRESULT
CHTEngineHandler::HT_hrFadeInScreen( HT_COLOR& clrFrom, HTfloat fTime )	// 점점 화면이 보임
{
	m_oFadeScreen.bIsFadeIn = HT_TRUE;
	m_oFadeScreen.fFadeTime = m_oFadeScreen.fTime = fTime;
	m_oFadeScreen.clrFade = clrFrom;

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrFadeOutScreen( HT_COLOR& clrTo, HTfloat fTime )	// 점점 화면이 안보여짐.
{
	m_oFadeScreen.bIsFadeIn = HT_FALSE;
	m_oFadeScreen.fFadeTime = m_oFadeScreen.fTime = fTime;
	m_oFadeScreen.clrFade = clrTo;

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HTvector3& vecPos, HT_COLOR& clrText )
{
	HTint idFont;
	HT_UPDATEOBJPARAM updateParam;
	updateParam.vecPosition = vecPos;
	updateParam.clrDiffuse = clrText;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	m_p3DMgr->HT_hrUpdateObject( idFont, &updateParam );
	m_p3DMgr->HT_hrRenderObject( idFont, pszStr );

	return ( HT_OK );
}

HTRESULT
CHTEngineHandler::HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HTvector3& vecPos, HT_COLOR& clrText, HT_COLOR& clrBack, HTfloat fBackOffset )
{
	HTint idFont;
	HT_UPDATEOBJPARAM updateParam;
	updateParam.vecPosition = vecPos;
	updateParam.clrDiffuse = clrText;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	m_p3DMgr->HT_hrUpdateObject( idFont, &updateParam );
	m_p3DMgr->HT_hrRenderObject( idFont, pszStr, clrBack, fBackOffset );

	return ( HT_OK );
}

HTRESULT
CHTEngineHandler::HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_COLOR& clrFont, HT_RECT& Rect, HT_TEXT_FORMATING eTextFormating )
{ 
	HTint idFont;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	return ( m_p3DMgr->HT_hrRenderObject( idFont, pszStr, clrFont, Rect, eTextFormating ) );
}

HTRESULT
CHTEngineHandler::HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_COLOR& clrFont, HTfloat fX, HTfloat fY, HTfloat fWidth, HTfloat fLineSpacing, HTfloat* pfReturnHeight )
{
	HTint idFont;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	return ( m_p3DMgr->HT_hrRenderObject( idFont, pszStr, clrFont, fX, fY, fWidth, fLineSpacing, pfReturnHeight ) );
}

HTRESULT CHTEngineHandler::HT_hrClearScreen( HT_COLOR& clrScreen )
{
	if ( m_bRenderLoading )		// 로딩화면 표시하는 중에 다른 루프에서 화면을 지우는 행위를 막는다.
		return ( HT_OK );

	return ( m_p3DMgr->HT_hrClearScreen( m_clrClearScreen ) );
	//	return ( m_p3DMgr->HT_hrClearScreen( clrScreen ) );
}

HTRESULT
CHTEngineHandler::HT_hrFlipScreen()
{
	if ( m_bRenderLoading )		// 로딩화면 표시하는 중에 다른 루프에서 화면을 지우는 행위를 막는다.
		return ( HT_OK );

	if ( m_oFadeScreen.fTime > 0.0f )
	{
		HTfloat fAlpha = m_oFadeScreen.fTime / m_oFadeScreen.fFadeTime;
		// 1에 가까울수록 최종 색깔에, 0에 가까울수록 최초 색깔에

		m_oFadeScreen.fTime -= m_fElapsedTime;

		HT_UPDATEOBJPARAM maskParam;
		maskParam.clrDiffuse = m_oFadeScreen.clrFade;
		if ( m_oFadeScreen.bIsFadeIn )
		{	// 점점 화면이 나타나는 것이므로 투명도가 점점 투명해지겠다.
			maskParam.clrDiffuse.a = 1.0f - fAlpha;
			m_p3DMgr->HT_hrUpdateObject( m_oFadeScreen.idFade, &maskParam );
		}
		else
		{	// 점점 화면이 사라지는 것이므로 투명도가 점점 불투명해지겠다.
			maskParam.clrDiffuse.a = fAlpha;
			m_p3DMgr->HT_hrUpdateObject( m_oFadeScreen.idFade, &maskParam );
		}

		m_p3DMgr->HT_hrRenderObject( m_oFadeScreen.idFade );
	}
	else m_oFadeScreen.fFadeTime = 0.0f;

	// TODO 
	//if ( m_bFading )
	//	m_p3DMgr->HT_hrRenderObject( m_idFadeMask );

	return ( m_p3DMgr->HT_hrFlipScreen() );
}

HTRESULT CHTEngineHandler::HT_hrAnimateObject( HTint idObj, HTfloat fElapsedTime )
{
	HT_UPDATEOBJPARAM updateParam;
	updateParam.fElapsedTime = fElapsedTime;

	return ( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );
}

HTRESULT CHTEngineHandler::HT_hrRotateObject( HTint idObj, HTfloat fDegree )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	//if ( fDegree < 0.0f || fDegree > HT_PI * 3 )
	//	return ( HT_FAIL );

	HT_UPDATEOBJPARAM updateParam;
	updateParam.vecRotation = HTvector3( 0.0f, fDegree, 0.0f );

	//	updateParam.vecRotation.y = HT_DEGREE_TO_RADIAN( updateParam.vecRotation.y );

	return ( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );
}

HTRESULT CHTEngineHandler::HT_hrRotateObject( HTint idObj, HTvector3& vecDegree )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_UPDATEOBJPARAM updateParam;
	updateParam.vecRotation = vecDegree;
	updateParam.vecRotation.x = HT_DEGREE_TO_RADIAN( updateParam.vecRotation.x );
	updateParam.vecRotation.y = HT_DEGREE_TO_RADIAN( updateParam.vecRotation.y );
	updateParam.vecRotation.z = HT_DEGREE_TO_RADIAN( updateParam.vecRotation.z );

	return ( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );
}

HTRESULT CHTEngineHandler::HT_hrAttachObject( HTint idObj, CHTString& strSocket, HTdword dwModelID, HTfloat fScale, HTdword dwAnimID )
{
	//if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_hrLoadToResPool( dwModelID, HT_FALSE );

	HT_hrLoadToResPool( dwAnimID, HT_FALSE );

	return ( m_p3DMgr->HT_hrAttachObject( idObj, strSocket, dwModelID, HT_FALSE, fScale, dwAnimID ) );
}

HTRESULT CHTEngineHandler::HT_hrDetachObject( HTint idObj, CHTString& strSocket )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTuint idSocketModel = m_p3DMgr->HT_dwDetachObject( idObj, strSocket );
	if ( idSocketModel > 0 )
	{
		HT_hrUnloadFromResPool( idSocketModel );

		HT_hrUnloadWeaponItemAnim( idObj, idSocketModel );
	}

	return ( HT_OK );
}

//HTint CHTEngineHandler::HT_iCreateSound( HTdword dwID )
//{
//	HTint idObjID = -1;
//	HT_EOBJ_CREATEPARAM objParam;
//	objParam.dwID = dwID;
//
//	if ( HT_IS_BGM( dwID ) )
//	{
//		CHTString strFile;
//		objParam.eObjType = HT_EOBJTYPE_BGMSOUND;
//		m_pResMgr->HT_bGetFileName( dwID, strFile );
//		objParam.strFileName = strFile;
//		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strSound, 
//			m_oResourcePath.strSound );
//	}
//	else if ( HT_IS_PCSOUND( dwID ) | HT_IS_NPCSOUND( dwID ) | HT_IS_FXSOUND( dwID ) | HT_IS_MONSTERSOUND( dwID ) |
//		HT_IS_ITEMSOUND( dwID ) | HT_IS_ETCSOUND( dwID ) )
//	{
//		objParam.eObjType = HT_EOBJTYPE_VOICESOUND;
//	}
//	// HK 20030117 
//	else if ( HT_IS_ETCSOUND( dwID ) )
//	{
//		objParam.eObjType = HT_EOBJTYPE_VOICESOUND;
//	}
//	else
//		return ( -1 );
//
//	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
//	{
//		return ( -1 );
//	}
//
//	return ( idObjID );
//}
//
HTRESULT CHTEngineHandler::HT_hrPlaySound( HTdword dwSoundID, HTint iLoop, HSAMPLE* hSample )
{
	// infinite loop
	if ( iLoop == -1 )
		iLoop = 0;

	if ( HT_IS_BGM( dwSoundID ) )	
	{
		CHTString strFile;
		m_pResMgr->HT_bGetFileName( dwSoundID, strFile );
		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strSound, 
			m_oResourcePath.strSound );

		// 이전에 같은 아이디로 생성한 Share Obj가 있다면, 먼저 Free를 시켜준다.
		m_p3DMgr->HT_hrUnLoadObject( dwSoundID );
		// 실제 로딩하는 것이 아니라, 초기화를 해주는 것이다.
		m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_STREAM, dwSoundID, strFile );

		// 현재 플레이되는 BGM이 있다면 Fadeout 시킨다.
		if ( m_p3DMgr->HT_bIsPlayingBGM() )
		{
			m_fStreamFadeVolume = m_fStreamVolume;
			m_bFadeoutBGM = HT_TRUE;
			m_dwNextBGMID = dwSoundID;
			m_iNextBGMLoopCount = iLoop;
			return ( HT_OK );
		}
	}

	if ( !hSample )
	{
		HT_CHECK( m_p3DMgr->HT_hrPlaySound( dwSoundID, iLoop ) );
	}
	else
	{
		HT_CHECK( m_p3DMgr->HT_hrPlaySound( dwSoundID, iLoop, HTvector3(0.0f,0.0f,0.0f), HT_NULL, hSample ) );
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrStopSound( HSAMPLE hSample )
{
	m_p3DMgr->HT_hrStopSound( hSample );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrChangeObject( HTint idObj, HT_EMODELPART ePart, HTint idItem, HTint idTribe )
{
	CHTString strPart, strWhat;

	HTdword dwIDModel, dwIDTex, dwIDMesh;

	switch ( ePart )
	{
	case HT_MODELPART_UPWEAR:
		{
			this->HT_hrHideMeshUpWear( idObj );

			HTdword dwChestMesh = 0, dwChestTexID = 0;
			HTdword dwRUArmMesh = 0, dwLUArmMesh = 0, dwRUArmTexID = 0, dwLUArmTexID = 0;
			HTdword dwSkirtMesh = 0, dwSkirtTexID = 0;
			HTdword dwApronModelID = 0, dwApronTexID = 0, dwApronBackModelID = 0, dwApronBackTexID = 0;
			HTdword dwShoulderLModelID = 0, dwShoulderLTexID = 0, dwShoulderRModelID = 0, dwShoulderRTexID = 0;
			HTbool bSkirtType = HT_FALSE;
			m_pResMgr->HT_bGetUpWearMeshes( idItem,
				dwChestMesh, dwChestTexID,
				dwRUArmMesh, dwLUArmMesh, dwRUArmTexID, dwLUArmTexID,
				dwSkirtMesh, dwSkirtTexID,
				dwApronModelID, dwApronTexID, dwApronBackModelID, dwApronBackTexID,
				dwShoulderLModelID, dwShoulderLTexID, dwShoulderRModelID, dwShoulderRTexID,
				bSkirtType );

			this->HT_hrLoadToResPool( dwChestMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwChestTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwChestMesh, HT_MODELPART_UPWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwChestMesh );

			this->HT_hrLoadToResPool( dwRUArmMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwRUArmTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwRUArmMesh, HT_MODELPART_UPWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwRUArmMesh );

			this->HT_hrLoadToResPool( dwLUArmMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwLUArmTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwLUArmMesh, HT_MODELPART_UPWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwLUArmMesh );

			this->HT_hrLoadToResPool( dwSkirtMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwSkirtTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwSkirtMesh, HT_MODELPART_UPWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwSkirtMesh );

			// Skirt Type 을 기억한다.
			// TRUE인 경우 PantsMesh를 2ndPantsMesh를 사용해야 한다.
			m_p3DMgr->HT_vSetSkirtType( idObj, bSkirtType );
			this->HT_hrHideMeshDownWear( idObj );
			HTdword dwDownWearID = m_p3DMgr->HT_dwGetDownWearID( idObj );

			if ( dwDownWearID > 0 )
			{
				HTdword dwPantsMesh = 0, dw2ndPantsMesh = 0, dwPantsTexID = 0;
				HTdword dwKneeLModelID = 0, dwKneeLTexID = 0, dwKneeRModelID = 0, dwKneeRTexID = 0;
				HTdword dwThighLModelID = 0, dwThighLTexID = 0, dwThighRModelID = 0, dwThighRTexID = 0;
				m_pResMgr->HT_bGetDownWearMeshes( dwDownWearID,
					dwPantsMesh, dw2ndPantsMesh, dwPantsTexID,
					dwKneeLModelID, dwKneeLTexID, dwKneeRModelID, dwKneeRTexID,
					dwThighLModelID, dwThighLTexID, dwThighRModelID, dwThighRTexID );

				if ( m_p3DMgr->HT_bGetSkirtType( idObj ) && dw2ndPantsMesh > 0 )
				{
					this->HT_hrLoadToResPool( dw2ndPantsMesh, HT_FALSE );
					m_pResMgr->HT_bGetFileName( dwPantsTexID, strWhat );
					m_p3DMgr->HT_hrShowMesh( idObj, dw2ndPantsMesh, HT_MODELPART_DOWNWEAR );
					m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dw2ndPantsMesh );
				}
				else
				{
					this->HT_hrLoadToResPool( dwPantsMesh, HT_FALSE );
					m_pResMgr->HT_bGetFileName( dwPantsTexID, strWhat );
					m_p3DMgr->HT_hrShowMesh( idObj, dwPantsMesh, HT_MODELPART_DOWNWEAR );
					m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwPantsMesh );
				}

				strPart = _T("LThigh");
				this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
				if ( dwThighLModelID > 0 )
				{
					this->HT_hrLoadToResPool( dwThighLModelID, HT_FALSE );
					m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwThighLModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwThighLModelID ), 0 );
					m_pResMgr->HT_bGetFileName( dwThighLTexID, strWhat );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				}
				strPart = _T("RThigh");
				this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
				if ( dwThighRModelID > 0 )
				{
					this->HT_hrLoadToResPool( dwThighRModelID, HT_FALSE );
					m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwThighRModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwThighRModelID ), 0 );
					m_pResMgr->HT_bGetFileName( dwThighRTexID, strWhat );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				}
				strPart = _T("LKnee");
				this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
				if ( dwKneeLModelID > 0 )
				{
					this->HT_hrLoadToResPool( dwKneeLModelID, HT_FALSE );
					m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwKneeLModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwKneeLModelID ), 0 );
					m_pResMgr->HT_bGetFileName( dwKneeLTexID, strWhat );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				}
				strPart = _T("RKnee");
				this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
				if ( dwKneeRModelID > 0 )
				{
					this->HT_hrLoadToResPool( dwKneeRModelID, HT_FALSE );
					m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwKneeRModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwKneeRModelID ), 0 );
					m_pResMgr->HT_bGetFileName( dwKneeRTexID, strWhat );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				}
			}

			strPart = _T("FApron");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwApronModelID > 0 )
			{
				HTdword dwSocketAnimID = 0;
				switch( idTribe )
				{
				case HT_ID_CHARACTER_NAGA:		m_pResMgr->HT_bGetNAGFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_YAKSA:		m_pResMgr->HT_bGetYAKFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_ASURA:		m_pResMgr->HT_bGetASUFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_DEVA:		m_pResMgr->HT_bGetDEVFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_KIMNARA:	m_pResMgr->HT_bGetKIMFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_GANDHARVA:	m_pResMgr->HT_bGetGANFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_RAKSHASA:	m_pResMgr->HT_bGetRAKFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_GARUDA:	m_pResMgr->HT_bGetGARFApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				}

				this->HT_hrLoadToResPool( dwApronModelID, HT_FALSE );
				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwApronModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwApronModelID ), dwSocketAnimID );
				m_pResMgr->HT_bGetFileName( dwApronTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strPart, dwSocketAnimID, 0.0f, 0.0f );
			}
			strPart = _T("BApron");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwApronBackModelID > 0 )
			{
				HTdword dwSocketAnimID = 0;
				switch( idTribe )
				{
				case HT_ID_CHARACTER_NAGA:		m_pResMgr->HT_bGetNAGBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_YAKSA:		m_pResMgr->HT_bGetYAKBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_ASURA:		m_pResMgr->HT_bGetASUBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_DEVA:		m_pResMgr->HT_bGetDEVBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_KIMNARA:	m_pResMgr->HT_bGetKIMBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_GANDHARVA:	m_pResMgr->HT_bGetGANBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_RAKSHASA:	m_pResMgr->HT_bGetRAKBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				case HT_ID_CHARACTER_GARUDA:	m_pResMgr->HT_bGetGARBApronAnimID( HT_ANISTATE_STD, dwSocketAnimID ); break;
				}

				this->HT_hrLoadToResPool( dwApronBackModelID, HT_FALSE );
				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwApronBackModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwApronBackModelID ), dwSocketAnimID );
				m_pResMgr->HT_bGetFileName( dwApronBackTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strPart, dwSocketAnimID, 0.0f, 0.0f );
			}
			strPart = _T("LShoulder");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwShoulderLModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwShoulderLModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwShoulderLModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwShoulderLModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwShoulderLTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
			strPart = _T("RShoulder");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			m_pResMgr->HT_bGetShoulderRModelID( idItem, dwIDModel );
			if ( dwShoulderRModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwShoulderRModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwShoulderRModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwShoulderRModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwShoulderRTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
		}
		break;

	case HT_MODELPART_DOWNWEAR :
		{
			this->HT_hrHideMeshDownWear( idObj );

			HTdword dwPantsMesh = 0, dw2ndPantsMesh = 0, dwPantsTexID = 0;
			HTdword dwKneeLModelID = 0, dwKneeLTexID = 0, dwKneeRModelID = 0, dwKneeRTexID = 0;
			HTdword dwThighLModelID = 0, dwThighLTexID = 0, dwThighRModelID = 0, dwThighRTexID = 0;
			m_pResMgr->HT_bGetDownWearMeshes( idItem,
				dwPantsMesh, dw2ndPantsMesh, dwPantsTexID,
				dwKneeLModelID, dwKneeLTexID, dwKneeRModelID, dwKneeRTexID,
				dwThighLModelID, dwThighLTexID, dwThighRModelID, dwThighRTexID );

			// Skirt Type 을 기억해 놓았다
			// TRUE인 경우 PantsMesh를 2ndPantsMesh를 사용해야 한다.
			m_p3DMgr->HT_vSetDownWearID( idObj, idItem );
			if ( m_p3DMgr->HT_bGetSkirtType( idObj ) && dw2ndPantsMesh > 0 )
			{
				this->HT_hrLoadToResPool( dw2ndPantsMesh, HT_FALSE );
				m_pResMgr->HT_bGetFileName( dwPantsTexID, strWhat );
				m_p3DMgr->HT_hrShowMesh( idObj, dw2ndPantsMesh, HT_MODELPART_DOWNWEAR );
				m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dw2ndPantsMesh );
			}
			else
			{
				this->HT_hrLoadToResPool( dwPantsMesh, HT_FALSE );
				m_pResMgr->HT_bGetFileName( dwPantsTexID, strWhat );
				m_p3DMgr->HT_hrShowMesh( idObj, dwPantsMesh, HT_MODELPART_DOWNWEAR );
				m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwPantsMesh );
			}

			strPart = _T("LThigh");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwThighLModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwThighLModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwThighLModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwThighLModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwThighLTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
			strPart = _T("RThigh");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwThighRModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwThighRModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwThighRModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwThighRModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwThighRTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
			strPart = _T("LKnee");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwKneeLModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwKneeLModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwKneeLModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwKneeLModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwKneeLTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
			strPart = _T("RKnee");
			this->HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			if ( dwKneeRModelID > 0 )
			{
				this->HT_hrLoadToResPool( dwKneeRModelID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwKneeRModelID, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwKneeRModelID ), 0 );
				m_pResMgr->HT_bGetFileName( dwKneeRTexID, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
		}
		break;

	case HT_MODELPART_HANDWEAR:
		{
			this->HT_hrHideMeshHandWear( idObj );

			HTdword dwRLArmMesh = 0, dwLLArmMesh = 0, dwRLArmTexID = 0, dwLLArmTexID;
			HTdword dwRHandMesh = 0, dwLHandMesh = 0, dwRHandTexID = 0, dwLHandTexID;
			m_pResMgr->HT_bGetHandWearMeshes( idItem,
				dwRLArmMesh, dwLLArmMesh, dwRLArmTexID, dwLLArmTexID,
				dwRHandMesh, dwLHandMesh, dwRHandTexID, dwLHandTexID );

			this->HT_hrLoadToResPool( dwRLArmMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwRLArmTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwRLArmMesh, HT_MODELPART_HANDWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwRLArmMesh );

			this->HT_hrLoadToResPool( dwLLArmMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwLLArmTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwLLArmMesh, HT_MODELPART_HANDWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwLLArmMesh );

			this->HT_hrLoadToResPool( dwRHandMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwRHandTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwRHandMesh, HT_MODELPART_HANDWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwRHandMesh );

			this->HT_hrLoadToResPool( dwLHandMesh, HT_FALSE );
			m_pResMgr->HT_bGetFileName( dwLHandTexID, strWhat );
			m_p3DMgr->HT_hrShowMesh( idObj, dwLHandMesh, HT_MODELPART_HANDWEAR );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwLHandMesh );
		}
		break;

	case HT_MODELPART_HAIR:
		{
			this->HT_hrHideMeshHair( idObj );

			strPart = _T("Hair");
			HT_hrUnloadFromResPool( m_p3DMgr->HT_dwDetachObject( idObj, strPart ) );
			m_pResMgr->HT_bGetHairModelID( idItem, dwIDModel );
			if ( dwIDModel )
			{
				HTdword dwSocketAnimID = 0;
				HTdword dwHairType, dwSTDAniID;
				dwSTDAniID = HT_dwGetPCAniID( idTribe, HT_ANISTATE_STD );
				if ( dwSTDAniID )
				{
					m_pResMgr->HT_bGetHairType( idItem, dwHairType );
					switch ( dwHairType ) 
					{
					case 1:
						m_pResMgr->HT_bGetHair1AniID( dwSTDAniID, dwSocketAnimID );
						break;
					case 2:
						m_pResMgr->HT_bGetHair2AniID( dwSTDAniID, dwSocketAnimID );
						break;
					default:
						break;
					}
				}
				this->HT_hrLoadToResPool( dwIDModel, HT_FALSE );
				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrAttachObject( idObj, strPart, dwIDModel, HT_TRUE, HT_fGetModelScaleFactor( idTribe, dwIDModel ), dwSocketAnimID );
				m_pResMgr->HT_bGetHairTexID( idItem, dwIDTex );
				m_pResMgr->HT_bGetFileName( dwIDTex, strWhat );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strPart, strWhat );
			}
		}

	case HT_MODELPART_FACE:
		{
			this->HT_hrHideMeshFace( idObj );

			m_pResMgr->HT_bGetFaceMesh( idItem, dwIDMesh );
			this->HT_hrLoadToResPool( dwIDMesh, HT_FALSE );
			m_p3DMgr->HT_hrShowMesh( idObj, dwIDMesh, HT_MODELPART_FACE );
			m_pResMgr->HT_bGetFaceTexID( idItem, dwIDTex );
			m_pResMgr->HT_bGetFileName( dwIDTex, strWhat );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwIDMesh );
		}
		break;

	case HT_MODELPART_SHOES:
		{
			HT_hrHideMeshShoes( idObj );

			m_pResMgr->HT_bGetRBootsMesh( idItem, dwIDMesh );
			m_p3DMgr->HT_hrShowMesh( idObj, dwIDMesh, HT_MODELPART_SHOES );
			HT_hrLoadToResPool( dwIDMesh, HT_FALSE );
			m_pResMgr->HT_bGetBootsTexID( idItem, dwIDTex );
			m_pResMgr->HT_bGetFileName( dwIDTex, strWhat );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwIDMesh );

			m_pResMgr->HT_bGetLBootsMesh( idItem, dwIDMesh );
			HT_hrLoadToResPool( dwIDMesh, HT_FALSE );
			m_p3DMgr->HT_hrShowMesh( idObj, dwIDMesh, HT_MODELPART_SHOES );
			m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwIDMesh );
		}
		break;
	default:
		return ( HT_FAIL );
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrFlickerObject( HTint idObj, HT_COLOR& clrChange, HTfloat fTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	// 이 함수는 공격받는 대상 캐릭만을 위한 것이므로 일반 맵 오브젝트등에는 적용될 필요가 없다.
	// 따라서 SkinnedModel인지 검사를 하고 그 경우에만 작동을 하도록 한다.
	if ( m_p3DMgr->HT_eGetEObjectType( idObj ) == HT_EOBJTYPE_SKINNEDMODEL )
	{
		HT_UPDATEOBJPARAM updateParam;
		updateParam.clrDiffuse = clrChange;
		updateParam.clrAmbient = clrChange;
		updateParam.clrSpecular = clrChange;

		updateParam.fFlickerTime = fTime;

		return ( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );
	}
	else
	{
		return HT_FAIL;
	}
}

HT_ANIMSTATE CHTEngineHandler::HT_eGetAnimState( HTint idObj )
{
	CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( idObj );
	if ( pObj )
	{
		return ( pObj->HT_eGetAnimState() );
	}

	return ( HT_AS_STOP );
}

HTRESULT
CHTEngineHandler::HT_hrSetInitTime( HTdword dwTimeZeroValue )
{
	if ( dwTimeZeroValue < m_dwAllInitTimeStartTime )
	{
		HT_ASSERT( 0 );
		return HT_FAIL;
	}

	HTdword dwElapsedSecondsFromAllInitTimeStart = dwTimeZeroValue - m_dwAllInitTimeStartTime;
	// 서버에서 모든 Time 값이 리셋된 시점의 최초로부터 얼마나 시간이 지났는지....

	HTdouble fElapsedDayFromAllInitTimeStart
		= ((HTdouble)dwElapsedSecondsFromAllInitTimeStart) / (HTdouble)(m_fDayTime + m_fNightTime);
	// 서버에서 모든 Time 값이 리셋된 시점 이후 게임시간으로 몇일과 얼만큼이 지났는지..

	HTdword dwElapsedDayFromAllInitTimeStart
		= (HTdword)fElapsedDayFromAllInitTimeStart;
	// 서버에서 모든 Time 값이 리셋된 시점 이후 게임시간으로 몇일이 지났는지..

	HTfloat fNowTimeInAllDay
		= (HTfloat)(fElapsedDayFromAllInitTimeStart - (HTdouble)dwElapsedDayFromAllInitTimeStart);
	// 게임시간으로 오늘 하루가 시작된지 얼마나 지났는지... 단 이 값은 낮밤이 같다는 생각의 값이 되겠다.


	// 낮과 밤의 비를 계산해서
	// 현재가 낮인 상태라면 값을 줄여주고 밤인 상태라면 값을 늘려주는 형식으로 밤낮이 다른 상태를 맞춰주는 형식이 되겠다.
	HTfloat fDayPercent		= m_fDayTime / (m_fDayTime + m_fNightTime);

	if ( fNowTimeInAllDay < fDayPercent )	// 낮시간
	{
		m_fNowTimeInAllDay = (fNowTimeInAllDay / fDayPercent) * 0.5f;
	}
	else
	{
		m_fNowTimeInAllDay = ( (fNowTimeInAllDay - fDayPercent) / (1.0f - fDayPercent) ) * 0.5f + 0.5f;
	}

	return HT_OK;
}

HTvoid CHTEngineHandler::HT_vLoadTimeValue( CHTConfigSystem* pCfg )
{
	HTfloat fA, fR, fG, fB; 

	pCfg->HT_hrGetValue( _T("TIME"), _T("Update"),					&m_bUpdateTime );
	pCfg->HT_hrGetValue( _T("TIME"), _T("DayTime"),					&m_fDayTime );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightTime"),				&m_fNightTime );
	pCfg->HT_hrGetValue( _T("TIME"), _T("startposX"),				&m_vecSunMoonStartPosition.x );
	pCfg->HT_hrGetValue( _T("TIME"), _T("startposY"),				&m_vecSunMoonStartPosition.y );
	pCfg->HT_hrGetValue( _T("TIME"), _T("startposZ"),				&m_vecSunMoonStartPosition.z );
	pCfg->HT_hrGetValue( _T("TIME"), _T("rotationaxisX"),			&m_vecSunMoonRotationAxis.x );
	pCfg->HT_hrGetValue( _T("TIME"), _T("rotationaxisY"),			&m_vecSunMoonRotationAxis.y );
	pCfg->HT_hrGetValue( _T("TIME"), _T("rotationaxisZ"),			&m_vecSunMoonRotationAxis.z );

	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningStart"),			&m_fMorningStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningEnd"),				&m_fMorningEnd );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningStart"),			&m_fEveningStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningEnd"),				&m_fEveningEnd );

	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogColorB"),		&fB );
	m_clrMorningFog = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogColorA"),			&fA );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogColorR"),			&fR );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogColorG"),			&fG );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogColorB"),			&fB );
	m_clrNoonFog = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogColorB"),		&fB );
	m_clrEveningFog = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogColorA"),			&fA );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogColorR"),			&fR );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogColorG"),			&fG );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogColorB"),			&fB );
	m_clrNightFog = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyHighHeight"),		&m_fMorningSkyHigh );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyMidHeight"),		&m_fMorningSkyMid );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyLowHeight"),		&m_fMorningSkyLow );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyHighColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyHighColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyHighColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyHighColorB"),		&fB );
	m_clrMorningSkyHighColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyMidColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyMidColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyMidColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyMidColorB"),		&fB );
	m_clrMorningSkyMidColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyLowColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyLowColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyLowColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyLowColorB"),		&fB );
	m_clrMorningSkyLowColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyCloudColorA"),	&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyCloudColorR"),	&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyCloudColorG"),	&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("MorningSkyCloudColorB"),	&fB );
	m_clrMorningCloudColor = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyHighHeight"),		&m_fNoonSkyHigh );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyMidHeight"),			&m_fNoonSkyMid );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyLowHeight"),			&m_fNoonSkyLow );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyHighColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyHighColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyHighColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyHighColorB"),		&fB );
	m_clrNoonSkyHighColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyMidColorA"),			&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyMidColorR"),			&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyMidColorG"),			&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyMidColorB"),			&fB );
	m_clrNoonSkyMidColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyLowColorA"),			&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyLowColorR"),			&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyLowColorG"),			&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyLowColorB"),			&fB );
	m_clrNoonSkyLowColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyCloudColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyCloudColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyCloudColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NoonSkyCloudColorB"),		&fB );
	m_clrNoonCloudColor = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyHighHeight"),		&m_fEveningSkyHigh );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyMidHeight"),		&m_fEveningSkyMid );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyLowHeight"),		&m_fEveningSkyLow );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyHighColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyHighColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyHighColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyHighColorB"),		&fB );
	m_clrEveningSkyHighColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyMidColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyMidColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyMidColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyMidColorB"),		&fB );
	m_clrEveningSkyMidColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyLowColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyLowColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyLowColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyLowColorB"),		&fB );
	m_clrEveningSkyLowColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyCloudColorA"),	&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyCloudColorR"),	&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyCloudColorG"),	&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("EveningSkyCloudColorB"),	&fB );
	m_clrEveningCloudColor = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyHighHeight"),		&m_fNightSkyHigh );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyMidHeight"),		&m_fNightSkyMid );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyLowHeight"),		&m_fNightSkyLow );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyHighColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyHighColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyHighColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyHighColorB"),		&fB );
	m_clrNightSkyHighColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyMidColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyMidColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyMidColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyMidColorB"),		&fB );
	m_clrNightSkyMidColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyLowColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyLowColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyLowColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyLowColorB"),		&fB );
	m_clrNightSkyLowColor = HT_COLOR( fR, fG, fB, fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyCloudColorA"),		&fA );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyCloudColorR"),		&fR );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyCloudColorG"),		&fG );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NightSkyCloudColorB"),		&fB );
	m_clrNightCloudColor = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunDiffuseColorA"),	&m_clrMorningSunDiffuse.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunDiffuseColorR"),	&m_clrMorningSunDiffuse.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunDiffuseColorG"),	&m_clrMorningSunDiffuse.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunDiffuseColorB"),	&m_clrMorningSunDiffuse.b );
	//m_clrMorningSunDiffuse = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunAmbientColorA"),	&m_clrMorningSunAmbient.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunAmbientColorR"),	&m_clrMorningSunAmbient.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunAmbientColorG"),	&m_clrMorningSunAmbient.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningSunAmbientColorB"),	&m_clrMorningSunAmbient.b );
	//m_clrMorningSunAmbient = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunDiffuseColorA"),	&m_clrNoonSunDiffuse.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunDiffuseColorR"),	&m_clrNoonSunDiffuse.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunDiffuseColorG"),	&m_clrNoonSunDiffuse.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunDiffuseColorB"),	&m_clrNoonSunDiffuse.b );
	//m_clrNoonSunDiffuse = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunAmbientColorA"),	&m_clrNoonSunAmbient.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunAmbientColorR"),	&m_clrNoonSunAmbient.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunAmbientColorG"),	&m_clrNoonSunAmbient.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonSunAmbientColorB"),	&m_clrNoonSunAmbient.b );
	//m_clrNoonSunAmbient = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunDiffuseColorA"),	&m_clrEveningSunDiffuse.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunDiffuseColorR"),	&m_clrEveningSunDiffuse.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunDiffuseColorG"),	&m_clrEveningSunDiffuse.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunDiffuseColorB"),	&m_clrEveningSunDiffuse.b );
	//m_clrEveningSunDiffuse = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunAmbientColorA"),	&m_clrEveningSunAmbient.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunAmbientColorR"),	&m_clrEveningSunAmbient.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunAmbientColorG"),	&m_clrEveningSunAmbient.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningSunAmbientColorB"),	&m_clrEveningSunAmbient.b );
	//m_clrEveningSunAmbient = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunDiffuseColorA"),	&m_clrNightSunDiffuse.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunDiffuseColorR"),	&m_clrNightSunDiffuse.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunDiffuseColorG"),	&m_clrNightSunDiffuse.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunDiffuseColorB"),	&m_clrNightSunDiffuse.b );
	//m_clrNightSunDiffuse = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunAmbientColorA"),	&m_clrNightSunAmbient.a );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunAmbientColorR"),	&m_clrNightSunAmbient.r );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunAmbientColorG"),	&m_clrNightSunAmbient.g );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightSunAmbientColorB"),	&m_clrNightSunAmbient.b );
	//m_clrNightSunAmbient = HT_COLOR( fR, fG, fB, fA );

	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogStart"),		&m_fMorningFogStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("MorningFogEnd"),		&m_fMorningFogEnd );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogStart"),		&m_fNoonFogStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NoonFogEnd"),			&m_fNoonFogEnd );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogStart"),		&m_fEveningFogStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("EveningFogEnd"),		&m_fEveningFogEnd );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogStart"),		&m_fNightFogStart );
	pCfg->HT_hrGetValue( _T("TIME"), _T("NightFogEnd"),			&m_fNightFogEnd );

	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("startposX"), &(m_vecSubLightStartPosition.x) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("startposY"), &(m_vecSubLightStartPosition.y) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("startposZ"), &(m_vecSubLightStartPosition.z) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("rotationaxisX"), &(m_vecSubLightRotationAxis.x) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("rotationaxisY"), &(m_vecSubLightRotationAxis.y) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("rotationaxisZ"), &(m_vecSubLightRotationAxis.z) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningDiffuseColorA"), &(m_clrMorningSubLightDiffuse.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningDiffuseColorR"), &(m_clrMorningSubLightDiffuse.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningDiffuseColorG"), &(m_clrMorningSubLightDiffuse.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningDiffuseColorB"), &(m_clrMorningSubLightDiffuse.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningAmbientColorA"), &(m_clrMorningSubLightAmbient.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningAmbientColorR"), &(m_clrMorningSubLightAmbient.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningAmbientColorG"), &(m_clrMorningSubLightAmbient.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("MorningAmbientColorB"), &(m_clrMorningSubLightAmbient.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonDiffuseColorA"), &(m_clrNoonSubLightDiffuse.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonDiffuseColorR"), &(m_clrNoonSubLightDiffuse.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonDiffuseColorG"), &(m_clrNoonSubLightDiffuse.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonDiffuseColorB"), &(m_clrNoonSubLightDiffuse.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonAmbientColorA"), &(m_clrNoonSubLightAmbient.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonAmbientColorR"), &(m_clrNoonSubLightAmbient.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonAmbientColorG"), &(m_clrNoonSubLightAmbient.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NoonAmbientColorB"), &(m_clrNoonSubLightAmbient.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningDiffuseColorA"), &(m_clrEveningSubLightDiffuse.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningDiffuseColorR"), &(m_clrEveningSubLightDiffuse.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningDiffuseColorG"), &(m_clrEveningSubLightDiffuse.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningDiffuseColorB"), &(m_clrEveningSubLightDiffuse.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningAmbientColorA"), &(m_clrEveningSubLightAmbient.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningAmbientColorR"), &(m_clrEveningSubLightAmbient.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningAmbientColorG"), &(m_clrEveningSubLightAmbient.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("EveningAmbientColorB"), &(m_clrEveningSubLightAmbient.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightDiffuseColorA"), &(m_clrNightSubLightDiffuse.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightDiffuseColorR"), &(m_clrNightSubLightDiffuse.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightDiffuseColorG"), &(m_clrNightSubLightDiffuse.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightDiffuseColorB"), &(m_clrNightSubLightDiffuse.b) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightAmbientColorA"), &(m_clrNightSubLightAmbient.a) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightAmbientColorR"), &(m_clrNightSubLightAmbient.r) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightAmbientColorG"), &(m_clrNightSubLightAmbient.g) );
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("NightAmbientColorB"), &(m_clrNightSubLightAmbient.b) );

	HTint iLightType;
	pCfg->HT_hrGetValue( _T("SUBLIGHT"), _T("type"), &iLightType );

	if ( iLightType > 0 && m_idSubLight < 0 )
	{
		memset( &m_SubLight, 0, sizeof(HT_LIGHT) );
		m_SubLight.Type			= (D3DLIGHTTYPE)iLightType;
		m_SubLight.Position		= m_vecSubLightStartPosition;
		m_SubLight.Direction	= -m_vecSubLightStartPosition;
		m_SubLight.Diffuse		= m_clrMorningSubLightDiffuse;
		m_SubLight.Ambient		= m_clrMorningSubLightAmbient;
		m_SubLight.Specular		= HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );

		m_p3DMgr->HT_hrCreateLight( &m_SubLight, &m_idSubLight );
	}
}

HTRESULT CHTEngineHandler::HT_hrSaveObject( HTint idObj, CHTString& strFile )
{
	return ( m_p3DMgr->HT_hrSaveObject( idObj, strFile ) );
}

HTRESULT CHTEngineHandler::HT_hrGetBoundingBox( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform )
{
	return ( m_p3DMgr->HT_hrGetBoundingBox( idObj, pBB, pmatTrasform ) );
}

HTRESULT CHTEngineHandler::HT_hrSetBoundingBox( HTint idObj, HT_AABB* pBB )
{
	return ( m_p3DMgr->HT_hrSetBoundingBox( idObj, pBB ) );
}

HTRESULT CHTEngineHandler::HT_hrGetBoundingSphere( HTint idObj, HT_SPHERE* pBS )
{
	CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( idObj );
	if ( pObj )
	{
		memcpy( pBS, pObj->HT_pGetBoundingSphere(), sizeof(HT_SPHERE) );
		return ( HT_OK );
	}

	return ( HT_FAIL );
}

HTRESULT CHTEngineHandler::HT_hrRenderBoundingBox( HTint idObj, HT_COLOR* pColor )
{
	return ( m_p3DMgr->HT_hrRenderBoundingBox( idObj, pColor ) );
}

HT_TILE_TYPE CHTEngineHandler::HT_eGetTileType( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_eGetTileType( iX, iZ, iF ) );
}

HTbool CHTEngineHandler::HT_bIsCellSafeZone( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_bIsCellSafeZone( iX, iZ, iF ) );
}

HTbool CHTEngineHandler::HT_bIsCellConflict( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_bIsCellConflict( iX, iZ, iF ) );
}

HTbool CHTEngineHandler::HT_bIsCellPKZone( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_bIsCellPKZone( iX, iZ, iF ) );
}

HTbool CHTEngineHandler::HT_bIsCellTemple( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_bIsCellTemple( iX, iZ, iF ) );
}

HTbool CHTEngineHandler::HT_bIsCellMoveDisable( HTint iX, HTint iZ, HTint iF )
{
	return ( m_pMapSystem->HT_bIsCellMoveDisable( iX, iZ, iF ) );
}

//HTbool CHTEngineHandler::HT_bIsCellVishunu( HTint iX, HTint iZ, HTint iF )
//{
//	return ( m_pMapSystem->HT_bIsCellVishunu( iX, iZ, iF ) );
//}
//
//HTbool CHTEngineHandler::HT_bIsCellSiva( HTint iX, HTint iZ, HTint iF )
//{
//	return ( m_pMapSystem->HT_bIsCellSiva( iX, iZ, iF ) );
//}

//--------------------------------------------------------------------------
// HTfloat					HT_fGetObjHeight(HTint iX, HTint iZ, HTint iF )
// D : 올라갈 오브젝트의 높이 얻기
// I : iX, iZ - 좌표, iF - 층
// R : 오브젝트의 높이
//--------------------------------------------------------------------------
HTword
CHTEngineHandler::HT_wGetObjHeight( HTint iX, HTint iZ, HTint iF ) // 대호 추가
{
	if (m_pMapSystem)
		return ( m_pMapSystem->HT_wGetObjHeight( iX, iZ, iF ) );
	return 0;
}

//---------------------------------------------------------------------------------
// 1  2
// 4  3
HTRESULT CHTEngineHandler::HT_hrRenderRectangle( HTvector3& vec1, HTvector3& vec2, HTvector3& vec3, HTvector3& vec4, HT_COLOR& clrText )
{
	m_p3DMgr->HT_hrRenderRectangle( vec1, vec2, vec3, vec4, clrText );
	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrRenderLine( HTvector3& vec1, HTvector3& vec2, HT_COLOR& clrText )
{
	m_p3DMgr->HT_hrRenderLine( vec1, vec2, clrText );
	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrPick( HTint iX, HTint iY, HTvector3& vec1, HTvector3& vec2, HTvector3& vec3 )
{
	HTRay oRay;
	m_p3DMgr->HT_hrMakePickRay( iX, iY, &oRay );

	HTIntersectInfo oInfo;

	if ( CHTIntersect::HT_bIsRayTriangleIntersect( &oInfo, oRay, vec1, vec2, vec3 ) )
	{
		return ( HT_OK );
	}

	return ( HT_FAIL );
}

HTbool CHTEngineHandler::HT_3DCOORD_TO_CELL( HTvector3& vecPos, HT_CELL_COORD& vecCell )
{
	if (m_pMapSystem)
	{
		m_pMapSystem->HT_3DCOORD_TO_CELL( vecPos, vecCell );
		return HT_TRUE;
	}
	return HT_FALSE;
}

HTbool CHTEngineHandler::HT_CELL_TO_3DCOORD( HTvector3& vecPos, HT_CELL_COORD& vecCell )
{
	if (m_pMapSystem)
	{
		m_pMapSystem->HT_CELL_TO_3DCOORD( vecPos, vecCell );
		return HT_TRUE;
	}
	return HT_FALSE;
}

HTRESULT CHTEngineHandler::HT_hrPathFind( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal, HTint* nNode, HT_CELL_COORD* arrNode )
{
	return ( m_pMapSystem->HT_hrAStarSearch( rStart, rGoal, nNode, arrNode ) );
}

HTbool CHTEngineHandler::HT_bCanMove( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	return ( m_pMapSystem->HT_bCanMove( eType, vecTo, byFloor ) );
}

HTbool CHTEngineHandler::HT_bCanMove( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor )
{
	HTvector3 vecTo;
	HT_CELL_TO_3DCOORD( vecTo, crdTo );

	return ( m_pMapSystem->HT_bCanMove( eType, vecTo, byFloor ) );
}

HTbool CHTEngineHandler::HT_bCanAttack( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	return ( m_pMapSystem->HT_bCanAttack( eType, vecTo, byFloor ) );
}

HTbool CHTEngineHandler::HT_bCanAttack( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor )
{
	HTvector3 vecTo;
	HT_CELL_TO_3DCOORD( vecTo, crdTo );

	return ( m_pMapSystem->HT_bCanAttack( eType, vecTo, byFloor ) );
}

HTbool
CHTEngineHandler::HT_bMonAttackDisable( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	return ( m_pMapSystem->HT_bNoAttackMonster( eType, vecTo, byFloor ) );
}

HTbool
CHTEngineHandler::HT_bMonAttackDisable( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor )
{
	HTvector3 vecTo;
	HT_CELL_TO_3DCOORD( vecTo, crdTo );

	return ( m_pMapSystem->HT_bNoAttackMonster( eType, vecTo, byFloor ) );
}

HTRESULT CHTEngineHandler::HT_hrSetMainChar( HTint idObj )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_CHECK( m_p3DMgr->HT_hrSetMainObject( idObj ) );
	m_idMainCharacter = idObj;

	// Create Character Follow Light
#if 1
	memset( &m_oCharLight, 0, sizeof(HT_LIGHT) );

	m_oCharLight.Type = (D3DLIGHTTYPE)m_iTypeCharLight;

	m_oCharLight.Diffuse = m_clrSpotDiffuse;
	m_oCharLight.Ambient = m_clrSpotAmbient;
	m_oCharLight.Specular = m_clrSpotSpecular;

	m_oCharLight.Range = m_fSpotRange;
	m_oCharLight.Falloff = 1.0f;
	m_oCharLight.Theta = m_fSmallAngle;
	m_oCharLight.Phi = m_fLargeAngle;

	m_oCharLight.Attenuation0	= 1.0f;
	m_oCharLight.Attenuation1	= 0.0f;
	m_oCharLight.Attenuation2	= 0.0f;

	m_oCharLight.Direction = m_vecSpotRotation;

	HTvector3 vecPos;
	//CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( m_idMainCharacter );
	if ( HT_SUCCEED( m_p3DMgr->HT_hrGetPosition( m_idMainCharacter, vecPos ) ) )
	{
		vecPos += m_vecSpotPosition;
		m_oCharLight.Position = vecPos;
		m_vecStampPos = vecPos;
	}
	else
	{
		m_oCharLight.Position = HTvector3( 0.0f, 0.0f, 0.0f );
		m_vecStampPos = HTvector3( 0.0f, 0.0f, 0.0f );
	}

	if ( m_idCharacterLight >= 0 )
	{
		m_p3DMgr->HT_hrOffLight( m_idCharacterLight );
	}

	m_p3DMgr->HT_hrCreateLight( &m_oCharLight, &m_idCharacterLight );
	m_p3DMgr->HT_vSetCharLight( m_idCharacterLight );


#else
	HT_EOBJ_CREATEPARAM lightParam;
	lightParam.eObjType = HT_EOBJTYPE_SPOTLIGHT;
	lightParam.clrDiffuse = m_clrSpotDiffuse;
	lightParam.clrAmbient = m_clrSpotAmbient;
	lightParam.clrSpecular = m_clrSpotSpecular;
	lightParam.fRange = m_fSpotRange;
	lightParam.fFalloff = 1.0f;
	lightParam.fNear = m_fSmallAngle;
	lightParam.fFar = m_fLargeAngle;
	lightParam.vecScale = HTvector3( 1.0f, 0.0f, 0.0f );
	lightParam.vecRotation = m_vecSpotRotation;

	HTvector3 vecPos;
	CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( m_idMainCharacter );
	if ( pObj )
	{
		vecPos = *(pObj->HT_pGetPosition());
	}
	vecPos += m_vecSpotPosition;
	lightParam.vecPosition = vecPos;

	if ( m_idCharacterLight > 0 )
	{
		m_p3DMgr->HT_hrDestroyObject( m_idCharacterLight );
	}

	m_p3DMgr->HT_hrCreateObject( &m_idCharacterLight, &lightParam );
	m_p3DMgr->HT_vSetCharLight(m_idCharacterLight);

#endif

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrEquipDefault( HTint idObj, HTint idTribe )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwIDWear, dwIDShoes;

	this->HT_hrHideMeshDownWear( idObj );
	this->HT_hrHideMeshUpWear( idObj );
	this->HT_hrHideMeshHandWear( idObj );
	HT_hrHideMeshShoes( idObj );

	m_pResMgr->HT_bGetDefaultUpWearID( idTribe, dwIDWear );
	HT_hrChangeObject( idObj, HT_MODELPART_UPWEAR, dwIDWear, idTribe );
	m_pResMgr->HT_bGetDefaultDownWearID( idTribe, dwIDWear );
	HT_hrChangeObject( idObj, HT_MODELPART_DOWNWEAR, dwIDWear, idTribe );
	m_pResMgr->HT_bGetDefaultHandWearID( idTribe, dwIDWear );
	HT_hrChangeObject( idObj, HT_MODELPART_HANDWEAR, dwIDWear, idTribe );
	m_pResMgr->HT_bGetDefaultShoesID( idTribe, dwIDShoes );
	HT_hrChangeObject( idObj, HT_MODELPART_SHOES, dwIDShoes, idTribe );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrChangeHead( HTint idObj, HTint idTribe, HTint iHairType, HTint iFaceType )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( idTribe == HT_ID_CHARACTER_GM )
		return ( HT_OK );

	HTdword dwIDHead = 0;
	switch( iHairType )
	{
	case HT_HEAD_TYPE_A:
		m_pResMgr->HT_bGetHeadTypeAID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_B:
		m_pResMgr->HT_bGetHeadTypeBID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_C:
		m_pResMgr->HT_bGetHeadTypeCID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_D:
		m_pResMgr->HT_bGetHeadTypeDID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_E:
		m_pResMgr->HT_bGetHeadTypeEID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_F:
		m_pResMgr->HT_bGetHeadTypeFID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_G:
		m_pResMgr->HT_bGetHeadTypeGID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_H:
		m_pResMgr->HT_bGetHeadTypeHID( idTribe, dwIDHead );
		break;
	default:
		return ( HT_FAIL );
	}

	this->HT_hrChangeObject( idObj, HT_MODELPART_HAIR, dwIDHead, idTribe );

	dwIDHead = 0;
	switch( iFaceType )
	{
	case HT_HEAD_TYPE_A:
		m_pResMgr->HT_bGetHeadTypeAID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_B:
		m_pResMgr->HT_bGetHeadTypeBID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_C:
		m_pResMgr->HT_bGetHeadTypeCID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_D:
		m_pResMgr->HT_bGetHeadTypeDID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_E:
		m_pResMgr->HT_bGetHeadTypeEID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_F:
		m_pResMgr->HT_bGetHeadTypeFID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_G:
		m_pResMgr->HT_bGetHeadTypeGID( idTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_H:
		m_pResMgr->HT_bGetHeadTypeHID( idTribe, dwIDHead );
		break;
	default:
		return ( HT_FAIL );
	}

	this->HT_hrChangeObject( idObj, HT_MODELPART_FACE, dwIDHead, idTribe );

	return ( HT_OK );
}

HTdword
CHTEngineHandler::HT_dwGetItemUI( HTint idItem )
{
	HTdword dwItem;
	if ( m_pResMgr->HT_bGetInvenTexID( idItem, dwItem ) ) return dwItem;
	else return 0;
}

HTRESULT CHTEngineHandler::HT_hrChangeClothes( HTint idObj, HTint idTribe, HTint idItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwIDWear;
	switch( idTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKID( idItem, dwIDWear );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARID( idItem, dwIDWear );
		break;
	default:
		return ( HT_FAIL );
	}

	if ( HT_IS_UP_WEAR( dwIDWear ) )
		return this->HT_hrChangeObject( idObj, HT_MODELPART_UPWEAR, dwIDWear, idTribe );
	else if ( HT_IS_DOWN_WEAR( dwIDWear ) )
		return this->HT_hrChangeObject( idObj, HT_MODELPART_DOWNWEAR, dwIDWear, idTribe );
	else if ( HT_IS_HAND_WEAR( dwIDWear ) )
		return this->HT_hrChangeObject( idObj, HT_MODELPART_HANDWEAR, dwIDWear, idTribe );
	else if ( HT_IS_SHOES( dwIDWear ) )
		return this->HT_hrChangeObject( idObj, HT_MODELPART_SHOES, dwIDWear, idTribe );
	else 
		return HT_FALSE;
}

HTRESULT CHTEngineHandler::HT_hrHideHands( HTint idObj, HTint idTribe, HTint idItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwWearID = 0;

	if ( HT_IS_ITEM_WEAR( idItem ) )
		m_pResMgr->HT_bGetWearItemID( idItem, dwWearID );
	else
		dwWearID = 0;

	if ( dwWearID )
	{
		HTdword dwIDWear;
		switch( idTribe )
		{
		case HT_ID_CHARACTER_NAGA:
			m_pResMgr->HT_bGetNAGID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_YAKSA:
			m_pResMgr->HT_bGetYAKID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_ASURA:
			m_pResMgr->HT_bGetASUID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_DEVA:
			m_pResMgr->HT_bGetDEVID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_KIMNARA:
			m_pResMgr->HT_bGetKIMID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			m_pResMgr->HT_bGetGANID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			m_pResMgr->HT_bGetRAKID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_GARUDA:
			m_pResMgr->HT_bGetGARID( dwWearID, dwIDWear );
			break;
		default:
			return ( HT_FAIL );
		}

		HTdword dwRLArmMesh = 0, dwLLArmMesh = 0, dwRLArmTexID = 0, dwLLArmTexID;
		HTdword dwRHandMesh = 0, dwLHandMesh = 0, dwRHandTexID = 0, dwLHandTexID;
		m_pResMgr->HT_bGetHandWearMeshes( dwIDWear,
			dwRLArmMesh, dwLLArmMesh, dwRLArmTexID, dwLLArmTexID,
			dwRHandMesh, dwLHandMesh, dwRHandTexID, dwLHandTexID );

		m_p3DMgr->HT_hrHideMesh( idObj, dwRHandMesh );
		this->HT_hrUnloadFromResPool( dwRHandMesh );

		m_p3DMgr->HT_hrHideMesh( idObj, dwLHandMesh );
		this->HT_hrUnloadFromResPool( dwLHandMesh );

	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrShowHands( HTint idObj, HTint idTribe, HTint idItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwWearID;

	if ( HT_IS_ITEM_WEAR( idItem ) )
		m_pResMgr->HT_bGetWearItemID( idItem, dwWearID );
	else
		dwWearID = 0;

	if ( dwWearID )
	{
		HTdword dwIDWear;
		switch( idTribe )
		{
		case HT_ID_CHARACTER_NAGA:
			m_pResMgr->HT_bGetNAGID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_YAKSA:
			m_pResMgr->HT_bGetYAKID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_ASURA:
			m_pResMgr->HT_bGetASUID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_DEVA:
			m_pResMgr->HT_bGetDEVID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_KIMNARA:
			m_pResMgr->HT_bGetKIMID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			m_pResMgr->HT_bGetGANID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			m_pResMgr->HT_bGetRAKID( dwWearID, dwIDWear );
			break;
		case HT_ID_CHARACTER_GARUDA:
			m_pResMgr->HT_bGetGARID( dwWearID, dwIDWear );
			break;
		default:
			return ( HT_FAIL );
		}

		HTdword dwRLArmMesh = 0, dwLLArmMesh = 0, dwRLArmTexID = 0, dwLLArmTexID;
		HTdword dwRHandMesh = 0, dwLHandMesh = 0, dwRHandTexID = 0, dwLHandTexID;
		m_pResMgr->HT_bGetHandWearMeshes( dwIDWear,
			dwRLArmMesh, dwLLArmMesh, dwRLArmTexID, dwLLArmTexID,
			dwRHandMesh, dwLHandMesh, dwRHandTexID, dwLHandTexID );

		CHTString strWhat;
		this->HT_hrLoadToResPool( dwRHandMesh, HT_FALSE );
		m_p3DMgr->HT_hrShowMesh( idObj, dwRHandMesh );
		m_pResMgr->HT_bGetFileName( dwRHandTexID, strWhat );
		m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwRHandMesh );

		this->HT_hrLoadToResPool( dwLHandMesh, HT_FALSE );
		m_p3DMgr->HT_hrShowMesh( idObj, dwLHandMesh );
		m_pResMgr->HT_bGetFileName( dwLHandTexID, strWhat );
		m_p3DMgr->HT_hrChangeTexture( idObj, strWhat, dwLHandMesh );
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrChangeShoes( HTint idObj, HTint idTribe, HTint idItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwIDShoes;
	switch( idTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKID( idItem, dwIDShoes );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARID( idItem, dwIDShoes );
		break;
	default:
		return ( HT_FAIL );
	}

	HT_hrChangeObject( idObj, HT_MODELPART_SHOES, dwIDShoes, idTribe );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrEquipItem( HTint idObj, HTint idTribe, HTint idItem, HTint idLeftHandWeaponItem, HTint iHeadType, HTint idWearItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwType;

	if ( (!HT_IS_ITEM( idItem )) && (!HT_IS_ITEM( idLeftHandWeaponItem )) )
		return ( HT_FAIL );

	if ( HT_IS_ITEM_WEAPON( idItem ) )
	{
		HTdword dwSocketID;
		CHTString strSocket;
		m_pResMgr->HT_bGetSocketModelID( idItem, dwSocketID );

		strSocket = _T("RightHand");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("LeftHand");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("RightClaw");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("LeftClaw");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Bow");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Arrow_Box");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Arrow");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon01");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon02");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_1");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_2");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon05");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("HWeapon01");
		HT_hrDetachObject( idObj, strSocket );

		m_pResMgr->HT_bGetSocketName( idItem, strSocket );

		if ( dwSocketID )
		{
			HTdword dwSocketTexID;
			CHTString strFile;
			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
			m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );

			// 활을 장착하는 경우 화살통도 장착하는 것으로 한다.
			// 화살통의 모델 아이디가 14189 이다!
			HTdword dwItemType;
			m_pResMgr->HT_bGetItemType( idItem, dwItemType );
			if ( dwItemType == HT_ANISTATE_ATK_BOW )
			{
				strSocket = _T("Arrow_Box");
				this->HT_hrAttachObject( idObj, strSocket, 14189 );
			}
		}

		// Claw의 경우 양쪽에 차야 하기때문에...
		m_pResMgr->HT_bGetSecondSocketModelID( idItem, dwSocketID );
		if ( dwSocketID )
		{
			HTdword dwSocketTexID;
			CHTString strFile;
			strSocket = _T("RightClaw");

			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
			m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );

			//			HT_hrHideHands( idObj, idTribe, idWearItem );
		}
		else
		{
			//			HT_hrShowHands( idObj, idTribe, idWearItem );
		}

		HT_hrLoadWeaponItemAnim( idObj, idTribe, idItem );

		// 양손 무기를 장착하게 되는 경우 왼손의 무기, 단검만 찰 수 있다.
		if ( idLeftHandWeaponItem > 0  && m_pResMgr->HT_bGetItemType( idLeftHandWeaponItem, dwType ) )
		{
			if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD )
			{
				// 만약 왼손에 뭔가 달려 있다면, 등판에 뭔가 달려 있다면, 떼어준다.
				strSocket = _T("HWeapon02");
				HT_hrDetachObject( idObj, strSocket );
				strSocket = _T("LeftSSW");
				HT_hrDetachObject( idObj, strSocket );

				m_pResMgr->HT_bGetSocketModelID( idLeftHandWeaponItem, dwSocketID );

				// 이제 달아준다. strSocket = _T("LeftSSW");
				HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );

				HTdword dwSocketTexID;
				m_pResMgr->HT_bGetSocketTexID( idLeftHandWeaponItem, dwSocketTexID );

				CHTString strFile;
				m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
			}
		}
	}
	// 순수하게 왼손 무기만 장착하게 되는 경우도 발생하면 처리한다.
	else if ( idLeftHandWeaponItem > 0 && m_pResMgr->HT_bGetItemType( idLeftHandWeaponItem, dwType ) )
	{
		if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD )
		{
			HTdword dwSocketID;
			CHTString strSocket;

			// 만약 왼손에 뭔가 달려 있다면, 등판에 뭔가 달려 있다면, 떼어준다.
			strSocket = _T("HWeapon02");
			HT_hrDetachObject( idObj, strSocket );
			strSocket = _T("LeftSSW");
			HT_hrDetachObject( idObj, strSocket );

			m_pResMgr->HT_bGetSocketModelID( idLeftHandWeaponItem, dwSocketID );

			// 이제 달아준다. strSocket = _T("LeftSSW");
			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );

			HTdword dwSocketTexID;
			m_pResMgr->HT_bGetSocketTexID( idLeftHandWeaponItem, dwSocketTexID );

			CHTString strFile;
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
		}
	}
	//else if ( HT_IS_ITEM_HAT( idItem ) )
	//{
	//	HTdword dwSocketID;
	//	CHTString strSocket;
	//	m_pResMgr->HT_bGetSocketModelID( idItem, dwSocketID );
	//	m_pResMgr->HT_bGetSocketName( idItem, strSocket );

	//	HT_hrDetachObject( idObj, strSocket );

	//	CHTString strHideMesh;
	//	m_pResMgr->HT_bGetHideMeshName( idItem, strHideMesh );
	//	if ( strHideMesh != _T("0") )
	//	{
	//		HT_hrDetachObject( idObj, strHideMesh );
	//	}
	//	else
	//	{
	//		HT_hrChangeHead( idObj, idTribe, iHeadType );
	//	}

	//	if ( dwSocketID )
	//	{
	//		HTdword dwSocketTexID;
	//		CHTString strFile;
	//		HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
	//		m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
	//		m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
	//		m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
	//	}
	//}
	else if ( HT_IS_ITEM_SHIELD( idItem ) )
	{
		HTdword dwSocketID;
		CHTString strSocket;
		m_pResMgr->HT_bGetSocketModelID( idItem, dwSocketID );
		m_pResMgr->HT_bGetSocketName( idItem, strSocket );
		HT_hrDetachObject( idObj, strSocket );	// "SLD"

		strSocket = _T("BWeapon03");
		HT_hrDetachObject( idObj, strSocket );

		m_pResMgr->HT_bGetSocketName( idItem, strSocket );

		if ( dwSocketID )
		{
			HTdword dwSocketTexID;
			CHTString strFile;
			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
			m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
		}
	}
	else if ( HT_IS_ITEM_WEAR( idItem ) )
	{
		HTdword dwWearID;
		m_pResMgr->HT_bGetWearItemID( idItem, dwWearID );
		if ( dwWearID )
			this->HT_hrChangeClothes( idObj, idTribe, dwWearID );
	}
	else if ( HT_IS_ITEM_SHOES( idItem ) )
	{
		HTdword dwShoesID;
		m_pResMgr->HT_bGetShoesItemID( idItem, dwShoesID );
		if ( dwShoesID )
			this->HT_hrChangeShoes( idObj, idTribe, dwShoesID );
	}
	else{}

	return ( HT_OK );
}

HTdword CHTEngineHandler::HT_dwGetItemEquipSoundID( HTdword dwItemID )
{
	HTdword dwSoundID = 0;
	m_pResMgr->HT_bGetEquipSoundID( dwItemID, dwSoundID );
	return ( dwSoundID );
}

HTRESULT CHTEngineHandler::HT_hrUnEquipItem( HTint idObj, HTint idTribe, HTint idItem, HTint idLeftHandWeaponItem, HTint iHeadType, HTint idWearItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( (!HT_IS_ITEM( idItem )) && (!HT_IS_ITEM( idLeftHandWeaponItem )) )	return HT_FAIL;

	HTdword dwType;

	if ( HT_IS_ITEM_WEAPON( idItem ) )
	{
		this->HT_hrDetachItemMainRefineEffect( idObj, idItem );
		this->HT_hrDetachItemSubRefineEffect( idObj, idItem );

		CHTString strSocket;
		strSocket = _T("Arrow_Box");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Arrow");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon01");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon02");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_1");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_2");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon05");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("HWeapon01");
		HT_hrDetachObject( idObj, strSocket );

		CHTString strFile;
		m_pResMgr->HT_bGetSocketName( idItem, strFile );
		HT_hrDetachObject( idObj, strFile );

		HTdword dwSocketID;
		// Claw의 경우 양쪽에 차야 하기때문에...
		m_pResMgr->HT_bGetSecondSocketModelID( idItem, dwSocketID );
		if ( dwSocketID )
		{
			strSocket = _T("RightClaw");
			HT_hrDetachObject( idObj, strSocket );
			HT_hrShowHands( idObj, idTribe, idWearItem );
		}

		// 양손 무기를 장착하게 되는 경우 왼손의 무기, 단검만 찰 수 있다.
		if ( idLeftHandWeaponItem > 0  && m_pResMgr->HT_bGetItemType( idLeftHandWeaponItem, dwType ) )
		{
			if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD )
			{
				// 만약 왼손에 뭔가 달려 있다면, 등판에 뭔가 달려 있다면, 떼어준다.
				strSocket = _T("HWeapon02");
				HT_hrDetachObject( idObj, strSocket );
				strSocket = _T("LeftSSW");
				HT_hrDetachObject( idObj, strSocket );
			}
		}
	}
	// 왼손 무기만 독자적으로 제거할 때
	else if ( idLeftHandWeaponItem > 0  && m_pResMgr->HT_bGetItemType( idLeftHandWeaponItem, dwType ) )
	{
		if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD )
		{
			CHTString strSocket;

			// 만약 왼손에 뭔가 달려 있다면, 등판에 뭔가 달려 있다면, 떼어준다.
			strSocket = _T("HWeapon02");
			HT_hrDetachObject( idObj, strSocket );
			strSocket = _T("LeftSSW");
			HT_hrDetachObject( idObj, strSocket );
		}
	}
	else if ( HT_IS_ITEM_SHIELD( idItem ) )
	{
		CHTString strFile;
		m_pResMgr->HT_bGetSocketName( idItem, strFile );
		HT_hrDetachObject( idObj, strFile );

		strFile = _T("BWeapon03");
		HT_hrDetachObject( idObj, strFile );
	}
	//else if ( HT_IS_ITEM_HAT( idItem ) )
	//{
	//	CHTString strFile;
	//	m_pResMgr->HT_bGetSocketName( idItem, strFile );

	//	HT_hrDetachObject( idObj, strFile );

	//	HT_hrChangeHead( idObj, idTribe, iHeadType );
	//}
	//else if ( HT_IS_ITEM_WEAR( idItem ) )
	//{
	//	HTdword dwWearID;
	//	m_pResMgr->HT_bGetDefaultWearID( idTribe, dwWearID );
	//	if ( dwWearID )
	//		HT_hrChangeObject( idObj, HT_MODELPART_BODY, dwWearID, idTribe );
	//}
	else if ( this->HT_bIsWearItem( idItem ) )
	{
		HTdword dwWearID;
		m_pResMgr->HT_bGetWearItemID( idItem, dwWearID );
		if ( HT_IS_UPWEARITEM( dwWearID ) )
		{
			m_pResMgr->HT_bGetDefaultUpWearID( idTribe, dwWearID );
			HT_hrChangeObject( idObj, HT_MODELPART_UPWEAR, dwWearID, idTribe );
		}
		else if ( HT_IS_DOWNWEARITEM( dwWearID ) )
		{
			m_pResMgr->HT_bGetDefaultDownWearID( idTribe, dwWearID );
			HT_hrChangeObject( idObj, HT_MODELPART_DOWNWEAR, dwWearID, idTribe );
		}
		else if ( HT_IS_HANDWEARITEM( dwWearID ) )
		{
			m_pResMgr->HT_bGetDefaultHandWearID( idTribe, dwWearID );
			HT_hrChangeObject( idObj, HT_MODELPART_HANDWEAR, dwWearID, idTribe );
		}
	}
	else if ( HT_IS_ITEM_SHOES( idItem ) )
	{
		HTdword dwShoesID;
		m_pResMgr->HT_bGetDefaultShoesID( idTribe, dwShoesID );
		if ( dwShoesID )
			HT_hrChangeObject( idObj, HT_MODELPART_SHOES, dwShoesID, idTribe );
	}
	else{}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshFace( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_FACE, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_FACE );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshHair( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_HAIR, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_HAIR );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshUpWear( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_UPWEAR, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_UPWEAR );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshDownWear( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_DOWNWEAR, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_DOWNWEAR );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshHandWear( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_HANDWEAR, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_HANDWEAR );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrHideMeshShoes( HTint idObj )
{
	HTdword arrShowMeshID[50];
	HTdword dwShowMeshCount = 0;
	m_p3DMgr->HT_hrGetShowMeshIDs( idObj, HT_MODELPART_SHOES, arrShowMeshID, &dwShowMeshCount );
	for ( HTdword i = 0; i < dwShowMeshCount; i++ )
	{
		HT_hrUnloadFromResPool( arrShowMeshID[i] );
	}

	m_p3DMgr->HT_hrHideMesh( idObj, 0, HT_MODELPART_SHOES );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrInitResource()
{
	m_pResMgr = new CHTResMgr;

	CHTString strFile;
#if 1 
	strFile = _CLIENT_TXL_FILEPATH;
	HT_CHECK( m_pResMgr->HT_hrLoad( strFile ) );
#else
	strFile = _CLIENT_XML_FILEPATH;
	HT_CHECK( m_pResMgr->HT_hrInit( strFile ) );
#endif

	return ( HT_OK );
}
#define HT_FXRES_LOADERRORMESSAGE( dwID, strFile, szWhere ) \
{ CHTString strDebug; strDebug.HT_szFormat( "Cannot Load %s ID[%d] Name[%s]!", (szWhere), (dwID), (HTtchar*)(strFile) ); MessageBox( HT_NULL, (HTtchar*)strDebug, (szWhere), MB_OK ); }

#define HT_FXRES_FINDERRORMESSAGE( dwID, strTable, szWhere ) \
{ CHTString strDebug; strDebug.HT_szFormat( "Cannot Find %s Name by ID[%d] Table[%s]!", (szWhere), (dwID), (HTtchar*)(strTable) ); MessageBox( HT_NULL, (HTtchar*)strDebug, (szWhere), MB_OK ); }

#define HT_FXRES_UNLOADERRERMESSAGE( dwID, szWhere ) \
{ CHTString strDebug; strDebug.HT_szFormat( "Cannot Unload File ID[%d]!", (dwID) ); MessageBox( HT_NULL, (HTtchar*)strDebug, (szWhere), MB_OK ); }


HTRESULT
CHTEngineHandler::HT_hrLoadFXPCResource()
{
	CHTString strResFile;

#ifdef HT_FXRESOURCE_XML
	strResFile = m_oResourcePath.strFX + _T("\\fxPC.xml");
#else
	strResFile = m_oResourcePath.strFX + _T("\\fxPC.txl");
#endif

	if ( m_pFXPCResMgr ) this->HT_hrUnloadFXPCResource();

	m_pFXPCResMgr = new CHTFXPCResMgr;
	HT_CHECK( m_pFXPCResMgr->HT_hrLoad( strResFile ) );

	// Load Model
	strResFile = _T("resource\\fx\\fxPCModel.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strResFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_MODEL );

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX+_T("\\fxPCModel"), m_oResourcePath.strFX +_T("\\fxPCTexture") );
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXPCResMgr->HT_bGetModelName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SKINNEDMODEL, dwID, strFile ) ) ) 
					HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxModel") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxModel") )
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strResFile );

	// Load Texture
	strResFile = _T("resource\\fx\\fxPCTexture.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strResFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_TEXTURE );

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX+_T("\\fxPCTexture"), m_oResourcePath.strFX+_T("\\fxPCTexture") );
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXPCResMgr->HT_bGetTextureName( dwID, strFile ) )
			{
				switch ( m_iTextureDetailLevel )
				{
				case 1:
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 3 ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxTexutre") )
						break;
				case 2: case 3:
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 1 ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxTexture") )
						break;
				default:
					MessageBox( HT_NULL, _T("Not Valid Spec Value!"), _T("HT_hrLoadTexture Error!"), MB_OK );
				}
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxTexture") );
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strResFile );

	// Load Animation
	strResFile = _T("resource\\fx\\fxPCAnimation.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strResFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_ANIMATION );

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX+_T("\\fxPCAnimation"), m_oResourcePath.strFX+_T("\\fxPCTexture") );
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXPCResMgr->HT_bGetAnimationName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwID, strFile ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxAnimation") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxAnimation") )
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strResFile );

	// Load Sound
	strResFile = _T("resource\\fx\\fxPCSound.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strResFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_SOUND );

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX+_T("\\fxPCSound"), m_oResourcePath.strFX+_T("\\fxPCTexture") );
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXPCResMgr->HT_bGetAnimationName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwID, strFile ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxSound") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXPCResource::fxSound") )
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strResFile );

	// Make Sword Common Buffer
	m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SWORDWINDBUFFER, HT_SWORDWINDBUFFER_ID, CHTString("Sword Wind VB & IB") );

	// Make RealTime Shadow RenderTarget Buffer
	// 가끔 RenderTarget Texture를 못 만드는 그래픽 카드를 위해
	// 실시간 그림자 옵션이 꺼져 있는 경우 완전히 만들지 않게 한다.
	if ( m_bUseRTShadow )
		m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RTSHADOWTEXTUREIDBUFFER, HT_RTSHADOWTEXTUREIDBUFFER_ID, CHTString("Real Time Shadow Texture ID") );

	// Make SpriteSystem Common Buffer
	m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SPRITESYSTEMBUFFER, HT_SPRITESYSTEMBUFFER_ID, CHTString("SpriteSystem VB & IB") );
	m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SPRITEBUFFER_ID, HT_FXSPRITEBUFFER_ID, CHTString("FXSprite VB & IB") );

	m_oMousePosFX.idMouseNullModel = this->HT_iCreateNullModel( HTvector3( 0.0f, 0.0f, 0.0f ) );

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrUnloadFXPCResource()
{
	HTuint i;
	CHTString strTable;

	// Unload Model
	strTable = HT_FXRES_TABLENAME_MODEL;
	{
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXPCResource::fxModel") )
		}
	}
	// Unload Texture
	strTable = HT_FXRES_TABLENAME_TEXTURE;
	{
		CHTString strName;
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXPCResMgr->HT_bGetTextureName( dwID, strName ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrUnLoadTexture( strName ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXPCResource::fxTexture") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strTable, _T("HT_hrUnloadFXPCResource::fxTexture") )
		}
	}
	// Unload Animation
	strTable = HT_FXRES_TABLENAME_ANIMATION;
	{
		for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXPCResource::fxAnimation") )
		}
	}
	// Unload Sound
	/*
	strTable = HT_FXRES_TABLENAME_SOUND;
	{
	for ( i = 0; i < m_pFXPCResMgr->HT_nGetItemCount( strTable ); i++ )
	{
	HTdword dwID = m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, i );
	if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXPCResource::fxSound") )
	}
	}
	*/


	m_pFXPCResMgr->HT_hrUnload();
	HT_DELETE( m_pFXPCResMgr );

	m_p3DMgr->HT_hrUnLoadObject( HT_SWORDWINDBUFFER_ID );

	if ( m_bUseRTShadow )
		m_p3DMgr->HT_hrUnLoadObject( HT_RTSHADOWTEXTUREIDBUFFER_ID );

	m_p3DMgr->HT_hrUnLoadObject( HT_SPRITESYSTEMBUFFER_ID );
	m_p3DMgr->HT_hrUnLoadObject( HT_FXSPRITEBUFFER_ID );

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrLoadFXMAPResource( HTdword dwMapID )
{
	if ( m_pFXMAPResMgr ) this->HT_hrUnloadFXMAPResource();

	CHTString strResFile, strHPKFile;
	m_pResMgr->HT_bGetFXFilesName( dwMapID, strResFile );
	strResFile = m_oResourcePath.strFX + _T("\\") + strResFile;

#ifdef HT_FXRESOURCE_XML
	m_pFXMAPResMgr = new CHTFXMAPResMgr;
	HT_CHECK( m_pFXMAPResMgr->HT_hrLoad( strResFile + _T(".xml") ) );
#else
	m_pFXMAPResMgr = new CHTFXMAPResMgr;
	HT_CHECK( m_pFXMAPResMgr->HT_hrLoad( strResFile + _T(".txl") ) );
#endif

	// Load Model
	strHPKFile = strResFile + _T("Model.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strHPKFile );

	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_MODEL );

		m_p3DMgr->HT_vSetResourcePath( strResFile+_T("Model"), strResFile+_T("Texture") );
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXMAPResMgr->HT_bGetModelName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_SKINNEDMODEL, dwID, strFile ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxModel") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxModel") );
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strHPKFile );

	// Load Texture (FX 선영범)
	//strHPKFile = strResFile + _T("Texture.hpk");
	strHPKFile = _T("resource\\fx\\fxPCTexture.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strHPKFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_TEXTURE );

		m_p3DMgr->HT_vSetResourcePath( strResFile+_T("Texture"), strResFile+_T("Texture") );
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXMAPResMgr->HT_bGetTextureName( dwID, strFile ) )
			{
				switch ( m_iTextureDetailLevel )
				{
				case 1:
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 3 ) ) )
					{
						HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxTexutre") )
					}
					break;
				case 2: case 3:
					if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 1 ) ) )
					{
						HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxTexture") )
					}
					break;
				default:
					MessageBox( HT_NULL, _T("Not Valid Spec Value!"), _T("HT_hrLoadTexture Error!"), MB_OK );
				}
			}
			else 
			{
				HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxTexture") )
			}
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strHPKFile );

	// Load Animation
	strHPKFile = strResFile + _T("Animation.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strHPKFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_ANIMATION );

		m_p3DMgr->HT_vSetResourcePath( strResFile+_T("Animation"), strResFile+_T("Texture") );
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXMAPResMgr->HT_bGetAnimationName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_ANIMATION, dwID, strFile ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxAnimation") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxAnimation") )
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strHPKFile );

	// Load FX Sound
	strHPKFile = strResFile + _T("Sound.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strHPKFile );
	{
		HTuint i;
		CHTString strFile;
		CHTString strTable( HT_FXRES_TABLENAME_SOUND );

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX+_T("Sound"), m_oResourcePath.strFX+_T("Texture") );
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); ++i )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXMAPResMgr->HT_bGetAnimationName( dwID, strFile ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_3DSAMPLE, dwID, strFile ) ) ) HT_FXRES_LOADERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxSound") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strFile, _T("HT_hrLoadFXMAPResource::fxSound") )
		}
	} m_pPackFileMgr->HT_hrClosePackFile( strHPKFile );

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrUnloadFXMAPResource()
{
	HTuint i;
	CHTString strTable;

	// Unload Model
	strTable = HT_FXRES_TABLENAME_MODEL;
	{
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXMAPResource::fxModel") )
		}
	}
	// Unload Texture
	strTable = HT_FXRES_TABLENAME_TEXTURE;
	{
		CHTString strName;
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( m_pFXMAPResMgr->HT_bGetTextureName( dwID, strName ) )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrUnLoadTexture( strName ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXMAPResource::fxTexture") )
			}
			else HT_FXRES_FINDERRORMESSAGE( dwID, strTable, _T("HT_hrUnloadFXMAPResource::fxTexture") )
		}
	}
	// Unload Animation
	strTable = HT_FXRES_TABLENAME_ANIMATION;
	{
		for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); i++ )
		{
			HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
			if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXMAPResource::fxAnimation") )
		}
	}
	/*
	strTable = HT_FXRES_TABLENAME_SOUND;
	{
	for ( i = 0; i < m_pFXMAPResMgr->HT_nGetItemCount( strTable ); i++ )
	{
	HTdword dwID = m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, i );
	if ( !dwID || HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) ) HT_FXRES_UNLOADERRERMESSAGE( dwID, _T("HT_hrUnloadFXMAPResource::fxSound") )
	}
	}
	*/

	m_pFXMAPResMgr->HT_hrUnload();
	HT_DELETE( m_pFXMAPResMgr );

	return HT_OK;
}

HTdword
CHTEngineHandler::HT_dwGetMonsterSkillAniID( HTdword dwMonSkillID )
{
	HTdword dwAni = 0;
	m_pFXMAPResMgr->HT_bGetSkillAni( dwMonSkillID, dwAni );

	return dwAni;
}

HTRESULT
CHTEngineHandler::HT_hrCreateFXPCMgr()
{
	HT_EOBJ_CREATEPARAM fxParam;

	fxParam.eObjType		= HT_EOBJTYPE_FXMGR;
	fxParam.fCenterRatio	= m_fFXCamJitterVisibleDistance;
	fxParam.fFalloff		= m_fFXSpriteSystemVisibleDistance;
	fxParam.fFar			= m_fFXSpriteVisibleDistance;
	fxParam.fFOV			= m_fFXSoundVisibleDistance;
	fxParam.fLifeTime		= m_fFXModelVisibleDistance;
	fxParam.fLODDetail		= m_fFXDynaLightVisibleDistance;

#ifdef HT_FXDATA_TFX
	fxParam.strFileName = _T("resource\\FX\\fxPCEtc.tfx");			HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCEtc,			&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCFree.tfx");			HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCFree,		&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodBrahma.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodBrahma,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodShiba.tfx");		HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodShiba,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodVishunu.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodVishunu,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceAsuRak.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceAsuRak,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceDevGar.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceDevGar,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceNagaKin.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceNageKin,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceYakGan.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceYakGan,	&fxParam ) );
#else
	fxParam.strFileName = _T("resource\\FX\\fxPCEtc.fxf");			HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCEtc,			&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCFree.fxf");			HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCFree,		&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodBrahma.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodBrahma,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodShiba.fxf");		HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodShiba,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCGodVishunu.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCGodVishunu,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceAsuRak.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceAsuRak,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceDevGar.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceDevGar,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceNagaKin.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceNageKin,	&fxParam ) );
	fxParam.strFileName = _T("resource\\FX\\fxPCRaceYakGan.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idPCRaceYakGan,	&fxParam ) );
#endif

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrCreateFXMAPMgr( HTdword dwMapID )
{
	HT_EOBJ_CREATEPARAM fxParam;

	fxParam.eObjType		= HT_EOBJTYPE_FXMGR;
	fxParam.fCenterRatio	= m_fFXCamJitterVisibleDistance;
	fxParam.fFalloff		= m_fFXSpriteSystemVisibleDistance;
	fxParam.fFar			= m_fFXSpriteVisibleDistance;
	fxParam.fFOV			= m_fFXSoundVisibleDistance;
	fxParam.fLifeTime		= m_fFXModelVisibleDistance;
	fxParam.fLODDetail		= m_fFXDynaLightVisibleDistance;

	CHTString strName;
	m_pResMgr->HT_bGetFXFilesName( dwMapID, strName );
	strName = m_oResourcePath.strFX + _T("\\") + strName;

#ifdef HT_FXDATA_TFX
	fxParam.strFileName = strName + _T("Field.tfx");		HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idField,			&fxParam ) );
	fxParam.strFileName = strName + _T("MonsterSkill.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idMonsterSkill,	&fxParam ) );
	fxParam.strFileName = strName + _T("MonsterEtc.tfx");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idMonsterEtc,	&fxParam ) );
#else
	fxParam.strFileName = strName + _T("Field.fxf");		HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idField,			&fxParam ) );
	fxParam.strFileName = strName + _T("MonsterSkill.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idMonsterSkill,	&fxParam ) );
	fxParam.strFileName = strName + _T("MonsterEtc.fxf");	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &m_oIDFXMgr.idMonsterEtc,	&fxParam ) );
#endif

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrDestoryFXPCMgr()
{
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCEtc ) );				m_oIDFXMgr.idPCEtc = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCFree ) );			m_oIDFXMgr.idPCFree = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCGodBrahma ) );		m_oIDFXMgr.idPCGodBrahma = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCGodShiba ) );		m_oIDFXMgr.idPCGodShiba = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCGodVishunu ) );		m_oIDFXMgr.idPCGodVishunu = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCRaceAsuRak ) );		m_oIDFXMgr.idPCRaceAsuRak = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCRaceDevGar ) );		m_oIDFXMgr.idPCRaceDevGar = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCRaceNageKin ) );		m_oIDFXMgr.idPCRaceNageKin = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idPCRaceYakGan ) );		m_oIDFXMgr.idPCRaceYakGan = -1;

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrDestoryFXMAPMgr()
{
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idField ) );			m_oIDFXMgr.idField = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idMonsterSkill ) );	m_oIDFXMgr.idMonsterSkill = -1;
	HT_CHECK( m_p3DMgr->HT_hrDestroyObject( m_oIDFXMgr.idMonsterEtc ) );	m_oIDFXMgr.idMonsterEtc = -1;
	
	return HT_OK;
}

HTRESULT CHTEngineHandler::HT_hrLoadResource( CHTString& strTable, HT_SHAREOBJ_TYPE eType,
											 CHTString& strPath, CHTString& strTexPath )
{
	// Load Data
	HTuint i;
	CHTString strFile;

	m_p3DMgr->HT_vSetResourcePath( strPath, strTexPath );

	//OutputDebugString( (HTtchar*)strTable );
	//OutputDebugString( "\n" );

	HTuint iCount = m_pResMgr->HT_nGetItemCount( strTable );
	for ( i = 0; i < iCount; i++ )
	{
		HTdword dwID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
		if ( m_pResMgr->HT_bGetFileName( dwID, strFile ) )
		{
			//CHTString strDDD;
			//strDDD.HT_szFormat( "Load[%d][%s]\n", dwID, (HTtchar*)strFile );
			//OutputDebugString( (HTtchar*)strDDD );

			if ( HT_FAILED( m_p3DMgr->HT_hrLoadObject( eType, dwID, strFile ) ) )
			{
				CHTString strDebug;
				strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
				MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
				//				return ( HT_FAIL );
			}
			//////////////////////////////////////////////////
			//	여기에 로딩 이미지가 들어간다.
			//////////////////////////////////////////////////
		}
		else
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Cannot find file name by ID[%d] table[%s] index[%d] count[%d]!", dwID, (HTtchar*)strTable, i, iCount );
			MessageBox( HT_NULL, strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
			//			return ( HT_FAIL );
		}
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnloadResource( CHTString& strTable )
{
	HTuint i;

	for ( i = 0; i < m_pResMgr->HT_nGetItemCount( strTable ); i++ )
	{
		HTdword dwID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
		if ( !dwID || 
			HT_FAILED( m_p3DMgr->HT_hrUnLoadObject( dwID ) ) )
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Cannot unload file ID[%d]!", dwID );
			MessageBox( HT_NULL, (HTtchar*)strDebug, _T("HT_hrLoadResource Error!"), MB_OK );
			return ( HT_FAIL );
		}
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadTextures( CHTString& strTable, CHTString& strPath, CHTString& strTexPath )
{
	// Load Data
	HTuint i;
	CHTString strFile;

	m_p3DMgr->HT_vSetResourcePath( strPath, strTexPath );

	//OutputDebugString( (HTtchar*)strTable );
	//OutputDebugString( "\n" );

	for ( i = 0; i < m_pResMgr->HT_nGetItemCount( strTable ); i++ )
	{
		HTdword dwID = m_pResMgr->HT_dwGetIDByIndex( strTable, i );
		if ( m_pResMgr->HT_bGetFileName( dwID, strFile ) )
		{
			//CHTString strDDD;
			//strDDD.HT_szFormat( "Load[%d][%s]\n", dwID, (HTtchar*)strFile );
			//OutputDebugString( (HTtchar*)strDDD );

			if ( m_iTextureDetailLevel == 1 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 3 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else if ( m_iTextureDetailLevel == 2 || m_iTextureDetailLevel == 3 )
			{
				if ( HT_FAILED( m_p3DMgr->HT_hrLoadTexture( strFile, 1 ) ) )
				{
					CHTString strDebug;
					strDebug.HT_szFormat( "Cannot load file ID[%d] name[%s]!", dwID, (HTtchar*)strFile );
					MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
					return ( HT_FAIL );
				}
			}
			else
			{
				MessageBox( HT_NULL, _T("Not Valid Spec Value!"), _T("HT_hrLoadTexture Error!"), MB_OK );
			}
			//////////////////////////////////////////////
			//	여기에 로딩 이미지가 들어간다.
			//////////////////////////////////////////////
		}
		else
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Cannot find file name by ID[%d] table[%s]!", dwID, (HTtchar*)strTable );
			MessageBox( HT_NULL, strDebug, _T("HT_hrLoadTexture Error!"), MB_OK );
			return ( HT_FAIL );
		}
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadMap( HTdword dwMapID )
{
	// PC FX Mgr 도 파괴 후 다시 생성하여 전체 FX를 모두 Refresh 시켜준다.
	this->HT_hrDestoryFXPCMgr();
	this->HT_hrCreateFXPCMgr();

	this->HT_hrLoadFXMAPResource( dwMapID );
	this->HT_hrCreateFXMAPMgr( dwMapID );

	this->HT_hrLoadObjResMgr( dwMapID );	// 오브젝트 리소스 분리 (20031008 DaeHo)

	m_dwCurrentMapID = dwMapID;

	SetCurrentDirectory( szWorkingPath );

	CHTString strCfgFile;
	if ( !HT_IS_MAP( dwMapID ) || !m_pResMgr->HT_bGetCFGFileName( dwMapID, strCfgFile ) )
		return ( HT_FAIL );

	CHTConfigSystem* pCfg = new CHTConfigSystem;

	strCfgFile = _MAP_CFG_DIR + strCfgFile;	// 메인폴더 정리
	HT_CHECK( pCfg->HT_hrLoad( strCfgFile ) );

	pCfg->HT_hrGetValue( _T("MAP"), _T("path"), m_strMapPath );

	m_clrClearScreen = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	pCfg->HT_hrGetValue( _T("MAP"), _T("ClearColorR"), &m_clrClearScreen.r );
	pCfg->HT_hrGetValue( _T("MAP"), _T("ClearColorG"), &m_clrClearScreen.g );
	pCfg->HT_hrGetValue( _T("MAP"), _T("ClearColorB"), &m_clrClearScreen.b );

	m_clrAmbientLight = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	pCfg->HT_hrGetValue( _T("AMBIENTLIGHT"), _T("ColorR"), &m_clrAmbientLight.r );
	pCfg->HT_hrGetValue( _T("AMBIENTLIGHT"), _T("ColorG"), &m_clrAmbientLight.g );
	pCfg->HT_hrGetValue( _T("AMBIENTLIGHT"), _T("ColorB"), &m_clrAmbientLight.b );

	m_p3DMgr->HT_hrSetAmbientLight( m_clrAmbientLight );

	m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX, m_oResourcePath.strFX );

	//----------------------------------------------------------------
	pCfg->HT_hrGetValue( _T("TERRAIN"), _T("tiletexturerange"), &m_fTerrainTilingDistance );
	pCfg->HT_hrGetValue( _T("TERRAIN"), _T("detailtexture"), &m_bTerrainDetailTexture );

	CHTString strTexFile( _T("resource\\fx\\ENVTEX.hpk") );
	m_pPackFileMgr->HT_hrOpenPackFile( strTexFile );

	//----------------------------------------------------------------
	// 태양과 달을 생성한다. 즉 라이트를 생성하는 것이다.
	HT_EOBJ_CREATEPARAM sunParam;
	sunParam.eObjType = HT_EOBJTYPE_SUN;
	pCfg->HT_hrGetValue( _T("SUN"), _T("sunfile"), sunParam.strFileName );
	pCfg->HT_hrGetValue( _T("SUN"), _T("scaleX"), &sunParam.vecScale.x );
	pCfg->HT_hrGetValue( _T("SUN"), _T("scaleY"), &sunParam.vecScale.y );
	pCfg->HT_hrGetValue( _T("SUN"), _T("scaleZ"), &sunParam.vecScale.z );
	m_p3DMgr->HT_hrCreateObject( &m_idSun, &sunParam );

	HT_EOBJ_CREATEPARAM moonParam;
	moonParam.eObjType = HT_EOBJTYPE_MOON;
	pCfg->HT_hrGetValue( _T("MOON"), _T("moonfile"), moonParam.strFileName );
	pCfg->HT_hrGetValue( _T("MOON"), _T("scaleX"), &moonParam.vecScale.x );
	pCfg->HT_hrGetValue( _T("MOON"), _T("scaleY"), &moonParam.vecScale.y );
	pCfg->HT_hrGetValue( _T("MOON"), _T("scaleZ"), &moonParam.vecScale.z );
	m_p3DMgr->HT_hrCreateObject( &m_idMoon, &moonParam );

	//----------------------------------------------------------------
	HT_EOBJ_CREATEPARAM fogParam;
	fogParam.eObjType = HT_EOBJTYPE_FOG;
	HTfloat	fFogColorR, fFogColorG, fFogColorB;
	pCfg->HT_hrGetValue( _T("FOG"), _T("isenablefog"),		(HTint*)&fogParam.dwID );
	pCfg->HT_hrGetValue( _T("FOG"), _T("isvertexfog"),		&fogParam.iHeight );
	pCfg->HT_hrGetValue( _T("FOG"), _T("israngebasedfog"),	&fogParam.iWidth );
	pCfg->HT_hrGetValue( _T("FOG"), _T("colorR"),			&fFogColorR );
	pCfg->HT_hrGetValue( _T("FOG"), _T("colorG"),			&fFogColorG );
	pCfg->HT_hrGetValue( _T("FOG"), _T("colorB"),			&fFogColorB );
	pCfg->HT_hrGetValue( _T("FOG"), _T("start"),			&fogParam.fNear );
	pCfg->HT_hrGetValue( _T("FOG"), _T("end"),				&fogParam.fFar );
	fogParam.clrDiffuse = HT_COLOR( fFogColorR, fFogColorG, fFogColorB, 1.0f );

	m_p3DMgr->HT_hrCreateObject( &m_idFog, &fogParam );

	HT_EOBJ_CREATEPARAM terrainParam;
	terrainParam.eObjType = HT_EOBJTYPE_TERRAIN;
	m_pResMgr->HT_bGetTHMFileName( dwMapID, terrainParam.strFileName );
	terrainParam.fLODDetail				= m_fTerrainLODDetail;
	terrainParam.fTilingTextureDistance = m_fTerrainTilingDistance;

#if 1
	HTint	iColorR, iColorG, iColorB;
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("diffuseR"), &iColorR );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("diffuseG"), &iColorG );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("diffuseB"), &iColorB );
	terrainParam.clrDiffuse = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("ambientR"), &iColorR );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("ambientG"), &iColorG );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("ambientB"), &iColorB );
	terrainParam.clrAmbient = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("specularR"), &iColorR );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("specularG"), &iColorG );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("specularB"), &iColorB );
	terrainParam.clrSpecular = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("emissiveR"), &iColorR );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("emissiveG"), &iColorG );
	pCfg->HT_hrGetValue( _T("TERRAIN_MATERIAL"), _T("emissiveB"), &iColorB );
	terrainParam.clrEmissive = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
#else
	HTdword dwMtrlID;
	m_pResMgr->HT_bGetMaterialID( dwMapID, dwMtrlID );
	m_pResMgr->HT_bGetDiffuseColor( dwMtrlID, terrainParam.clrDiffuse );
	m_pResMgr->HT_bGetAmbientColor( dwMtrlID, terrainParam.clrAmbient );
	m_pResMgr->HT_bGetSpecularColor( dwMtrlID, terrainParam.clrSpecular );
	m_pResMgr->HT_bGetEmissiveColor( dwMtrlID, terrainParam.clrEmissive );
#endif

	m_p3DMgr->HT_vSetResourcePath( m_strMapPath, m_oResourcePath.strLevelTexture );

	// ToDo : For Terrain Section Texture UV Adjust
	HTfloat fSectionUVGridFor256 = 0, fSectionUVGridFor512 = 0, fSectionUVAdjustFor256 = 0, fSectionUVAdjustFor512 = 0;
	if ( HT_FAILED( pCfg->HT_hrGetValue( _T("TERRAIN"), _T("SectionUVGridFor256"),		&fSectionUVGridFor256 ) ) )		fSectionUVGridFor256 = 0.0f;
	if ( HT_FAILED( pCfg->HT_hrGetValue( _T("TERRAIN"), _T("SectionUVAdjustFor256"),	&fSectionUVAdjustFor256 ) ) )	fSectionUVAdjustFor256 = 0.0f;
	if ( HT_FAILED( pCfg->HT_hrGetValue( _T("TERRAIN"), _T("SectionUVGridFor512"),		&fSectionUVGridFor512 ) ) )		fSectionUVGridFor512 = 0.0f;
	if ( HT_FAILED( pCfg->HT_hrGetValue( _T("TERRAIN"), _T("SectionUVAdjustFor512"),	&fSectionUVAdjustFor512 ) ) )	fSectionUVAdjustFor512 = 0.0f;

	terrainParam.fCenterRatio		= fSectionUVGridFor256;
	terrainParam.fFalloff			= fSectionUVGridFor512;
	terrainParam.fFar				= fSectionUVAdjustFor256;
	terrainParam.fFOV				= fSectionUVAdjustFor512;
	// ToDo : For Terrain Section Texture UV Adjust

	CHTString strTerrainTexPack( m_strMapPath );
	strTerrainTexPack += _T("\\TerrainTex.hpk");
	m_pPackFileMgr->HT_hrOpenPackFile( strTerrainTexPack );

	m_p3DMgr->HT_hrCreateObject( &m_idTerrain, &terrainParam );

	{	// ToDo(?) : 카메라의 업데이트가 있는 경우에만 Terrain의 업데이트를 호출하는데,
		// 최초 실행시 업데이트를 한번도 호출하지 않고 렌더를 호출하여 죽는 경우가 발생한다.
		// 그래서 한번만 업데이트를 수행해준다. ^^;
		HT_UPDATEOBJPARAM updateParam;
		updateParam.idCamera				= m_idCamera;
		updateParam.fLODDetail				= m_fTerrainLODDetail;
		updateParam.fTilingTextureDistance	= m_fTerrainTilingDistance;
		updateParam.bSwordWindUpdate		= m_bTerrainDetailTexture;
		m_p3DMgr->HT_hrUpdateObject( m_idTerrain, &updateParam );
	}

	// Default Water Made By Zorotoss
	HT_EOBJ_CREATEPARAM WaterParam;
	WaterParam.eObjType = HT_EOBJTYPE_WATER_ZORO;

	HTvector3 vecWaterPos; HTfloat fWaterWidth, fWaterHeight; HT_COLOR clrLayer1, clrLayer2; HTfloat fLayer1FrameTime, fLayer2FrameTime;
	HTfloat fLayer1TextureWidth, fLayer2TextureWidth, fLayer1TextureHeight, fLayer2TextureHeight;
	HTint iNumLayer1Frame, iNumLayer2Frame;
	pCfg->HT_hrGetValue( _T("WATER"), _T("PosX"),					&vecWaterPos.x );
	pCfg->HT_hrGetValue( _T("WATER"), _T("PosY"),					&vecWaterPos.y );
	pCfg->HT_hrGetValue( _T("WATER"), _T("PosZ"),					&vecWaterPos.z );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Width"),					&fWaterWidth );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Height"),					&fWaterHeight );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1ColorR"),			&clrLayer1.r );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1ColorG"),			&clrLayer1.g );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1ColorB"),			&clrLayer1.b );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1ColorA"),			&clrLayer1.a );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2ColorR"),			&clrLayer2.r );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2ColorG"),			&clrLayer2.g );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2ColorB"),			&clrLayer2.b );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2ColorA"),			&clrLayer2.a );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1FrameTime"),		&fLayer1FrameTime );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2FrameTime"),		&fLayer2FrameTime );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1TextureWidth"),		&fLayer1TextureWidth );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2TextureWidth"),		&fLayer2TextureWidth );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1TextureHeight"),	&fLayer1TextureHeight );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2TextureHeight"),	&fLayer2TextureHeight );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer1FrameNum"),			&iNumLayer1Frame );
	pCfg->HT_hrGetValue( _T("WATER"), _T("Layer2FrameNum"),			&iNumLayer2Frame );
	pCfg->HT_hrGetValue( _T("WATER"), _T("TextureSetFileName"),		(HTtchar*)WaterParam.strFileName );

	WaterParam.vecPosition		= vecWaterPos;
	WaterParam.vecScale			= HTvector3( fWaterWidth, 0.0f, fWaterHeight);
	WaterParam.clrDiffuse		= clrLayer1;
	WaterParam.clrAmbient		= clrLayer2;
	WaterParam.fNear			= fLayer1FrameTime;
	WaterParam.fFar				= fLayer2FrameTime;
	WaterParam.fCenterRatio		= fLayer1TextureWidth;
	WaterParam.fFalloff			= fLayer1TextureHeight;
	WaterParam.fLifeTime		= fLayer2TextureWidth;
	WaterParam.fLODDetail		= fLayer2TextureHeight;
	WaterParam.iHeight			= iNumLayer1Frame;
	WaterParam.iWidth			= iNumLayer2Frame;

	if ( HT_SUCCEED( pCfg->HT_hrGetValue( _T("WATER"), _T("PosX"), &vecWaterPos.x ) ) )
	{
		m_p3DMgr->HT_hrCreateObject( &m_idWaterZoro, &WaterParam );
	}
	else
	{ // 만약 CFG에 Default Water에 대한 내용이 없는 경우에는 워터 자체를 사용하지 않는것이다.
		m_idWaterZoro = -1;	// 사용하지 않는 표시를 해 놓는다.
	}

	//----------------------------------------------------------------

	HT_EOBJ_CREATEPARAM skyParam;
	skyParam.eObjType = HT_EOBJTYPE_SKYCLOUD;

	HTbool	bIsFog;
	HTfloat fTexture1USpeed, fTexture1VSpeed, fTexture2USpeed, fTexture2VSpeed;
	HTint	iNumStar;
	pCfg->HT_hrGetValue( _T("SKY"), _T("Fog"),				&bIsFog );
	pCfg->HT_hrGetValue( _T("SKY"), _T("Texture1USpeed"),	&fTexture1USpeed );
	pCfg->HT_hrGetValue( _T("SKY"), _T("Texture1VSpeed"),	&fTexture1VSpeed );
	pCfg->HT_hrGetValue( _T("SKY"), _T("Texture2USpeed"),	&fTexture2USpeed );
	pCfg->HT_hrGetValue( _T("SKY"), _T("Texture2VSpeed"),	&fTexture2VSpeed );
	pCfg->HT_hrGetValue( _T("SKY"), _T("NumOfStar"),		&iNumStar );

	skyParam.nLoops			= (HTint)bIsFog;
	skyParam.fCenterRatio	= fTexture1USpeed;
	skyParam.fFalloff		= fTexture1VSpeed;
	skyParam.fFar			= fTexture2USpeed;
	skyParam.fFOV			= fTexture2VSpeed;
	skyParam.nLoops			= iNumStar;

	if ( HT_SUCCEED( pCfg->HT_hrGetValue( _T("SKY"), _T("TMD"), (HTtchar*)(skyParam.strFileName) ) ) )
	{
		m_p3DMgr->HT_hrCreateObject( &m_idSkyCloud, &skyParam );

		skyParam.eObjType		= HT_EOBJTYPE_SKY;
		HT_COLOR clr = HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );

		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMinR"),	&clr.r ) ) ) clr.r = 1.0f;
		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMinG"),	&clr.g ) ) ) clr.g = 1.0f;
		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMinB"),	&clr.b ) ) ) clr.b = 1.0f;
		skyParam.clrAmbient = clr;

		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMaxR"),	&clr.r ) ) ) clr.r = 1.0f;
		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMaxG"),	&clr.g ) ) ) clr.g = 1.0f;
		if ( HT_FAILED( pCfg->HT_hrGetValue( _T("SKY"), _T("StarMaxB"),	&clr.b ) ) ) clr.b = 1.0f;
		skyParam.clrDiffuse = clr;

		m_p3DMgr->HT_hrCreateObject( &m_idSky, &skyParam );
	}
	else
	{
		m_idSkyCloud = -1;
	}

	// 지형 Terrain
	if ( HT_SUCCEED( pCfg->HT_hrGetValue( _T("SKY"), _T("SkyTerrain"), (HTtchar*)(skyParam.strFileName) ) ) )
	{
		skyParam.eObjType = HT_EOBJTYPE_SKYTERRAIN;
		HTfloat fHeight;
		if ( HT_SUCCEED( pCfg->HT_hrGetValue( _T("SKY"), _T("SkyTerrainHeight"), &fHeight ) ) )
		{
			skyParam.fRange = fHeight;
		}
		else
		{
			skyParam.fRange  = 0.0f;
		}

		m_p3DMgr->HT_hrCreateObject( &m_idSkyTerrain, &skyParam );
	}
	else
	{
		m_idSkyTerrain = -1;
	}

	// 플로킹
	HTint iNumFlocking = 0;
	if ( HT_SUCCEED( pCfg->HT_hrGetValue( _T("FLOCKING"), _T("NUM"), &iNumFlocking ) ) )
	{
		for ( HTint iFlocking = 0; iFlocking < iNumFlocking; ++iFlocking )
		{
			CHTString strBuf; HTint dwNPCID;
			strBuf.HT_szFormat( "MODEL_%d", iFlocking );
			pCfg->HT_hrGetValue( _T("FLOCKING"), (HTtchar*)strBuf, &dwNPCID );

			HTvector3 vecPos;
			strBuf.HT_szFormat( "X%d", iFlocking );
			pCfg->HT_hrGetValue( _T("FLOCKING"), (HTtchar*)strBuf, &(vecPos.x) );

			strBuf.HT_szFormat( "Y%d", iFlocking );
			pCfg->HT_hrGetValue( _T("FLOCKING"), (HTtchar*)strBuf, &(vecPos.y) );

			strBuf.HT_szFormat( "Z%d", iFlocking );
			pCfg->HT_hrGetValue( _T("FLOCKING"), (HTtchar*)strBuf, &(vecPos.z) );

			HTFlocking Flocking;
			Flocking.dwNPCID = dwNPCID;
			Flocking.vecPos = vecPos;

			m_vectorFlocking.push_back( std::vector<HTFlocking>::value_type( Flocking ) );
		}		
	}

	//-------------------------------------
	// 미니맵 비트맵 파일을 로드한다. 실제 있는 경우에만 로드한다.
	CHTString strMinimap;
	m_p3DMgr->HT_vSetResourcePath( m_strMapPath, m_strMapPath );
	m_pResMgr->HT_bGetMinimapFilesName( dwMapID, strMinimap );
	if ( strMinimap.HT_nGetSize() > 2 )
	{
		strMinimap--; strMinimap--; strMinimap--; strMinimap += _T("dds");
		if ( strMinimap != _T("0") && strMinimap != _T("") )
		{
			m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_2DSPRITE, HT_MINIMAP_BMP_ID, strMinimap );
		}
	}

#ifdef HT_IS_TANTRA_LAUNCHER
	//-------------------------------------
	// NPCScript 파일을 로드한다.
	CHTString strNPCScript;
	m_pResMgr->HT_bGetNPCScriptFilesName( dwMapID, strNPCScript );

	if ( strNPCScript != _T("0") && strNPCScript != _T("") )
	{
		strNPCScript = _SYSTEM_DIR + strNPCScript;	// 메인폴더 정리
		HTRESULT res = m_pNPCScriptMgr->HT_hrLoad( strNPCScript );
	}
#endif

	//----------------------------------------------------------------
	CHTString strWaterFileName;
	m_pResMgr->HT_bGetTMEFileName( dwMapID, strWaterFileName );

	HT_hrLoadWaterFile( m_strMapPath, strWaterFileName );

	m_pPackFileMgr->HT_hrClosePackFile( strTexFile );
	m_pPackFileMgr->HT_hrClosePackFile( strTerrainTexPack );

	//----------------------------------------------------------------
	// Character Spot light 정보를 로딩한다.
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("type"), &m_iTypeCharLight );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("diffuseR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("diffuseG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("diffuseB"), &iColorB );
	m_clrSpotDiffuse = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("ambientR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("ambientG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("ambientB"), &iColorB );
	m_clrSpotAmbient = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("specularR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("specularG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("specularB"), &iColorB );
	m_clrSpotSpecular = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("range"), &m_fSpotRange );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("smallangle"), &m_fSmallAngle );
	m_fSmallAngle = HT_DEGREE_TO_RADIAN( m_fSmallAngle );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("largeangle"), &m_fLargeAngle );
	m_fLargeAngle = HT_DEGREE_TO_RADIAN( m_fLargeAngle );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("positionX"), &m_vecSpotPosition.x );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("positionY"), &m_vecSpotPosition.y );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("positionZ"), &m_vecSpotPosition.z );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("directionX"), &m_vecSpotRotation.x );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("directionY"), &m_vecSpotRotation.y );
	pCfg->HT_hrGetValue( _T("CHARACTERLIGHT"), _T("directionZ"), &m_vecSpotRotation.z );

	//----------------------------------------------------------------
	// Material 라이브러리 정보를 로딩한다.
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("diffuseR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("diffuseG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("diffuseB"), &iColorB );
	m_clrDiffuseChar = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("ambientR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("ambientG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("ambientB"), &iColorB );
	m_clrAmbientChar = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("specularR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("specularG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("specularB"), &iColorB );
	m_clrSpecularChar = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("emissiveR"), &iColorR );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("emissiveG"), &iColorG );
	pCfg->HT_hrGetValue( _T("CHAR_MATERIAL"), _T("emissiveB"), &iColorB );
	m_clrEmissiveChar = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);

	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("diffuseR"), &iColorR );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("diffuseG"), &iColorG );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("diffuseB"), &iColorB );
	m_clrDiffuseObjs = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("ambientR"), &iColorR );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("ambientG"), &iColorG );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("ambientB"), &iColorB );
	m_clrAmbientObjs = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("specularR"), &iColorR );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("specularG"), &iColorG );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("specularB"), &iColorB );
	m_clrSpecularObjs = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("emissiveR"), &iColorR );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("emissiveG"), &iColorG );
	pCfg->HT_hrGetValue( _T("OBJ_MATERIAL"), _T("emissiveB"), &iColorB );
	m_clrEmissiveObjs = HT_COLORCONVERT(iColorR,iColorG,iColorB,255);

	/*	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_CHARACTER, m_clrDiffuseChar );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_CHARACTER, m_clrAmbientChar );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_CHARACTER, m_clrEmissiveChar );
	m_pResMgr->HT_bGetSpecularColor( HT_ID_MATERIAL_CHARACTER, m_clrSpecularChar );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_STRUCTURE, m_clrDiffuse );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_STRUCTURE, m_clrAmbient );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_STRUCTURE, m_clrEmissive );
	m_pResMgr->HT_bGetSpecularColor( HT_ID_MATERIAL_STRUCTURE, m_clrSpecular );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_TREEBRANCH, m_clrDiffuseTree );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_TREEBRANCH, m_clrAmbientTree );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_TREEBRANCH, m_clrEmissiveTree );

	m_pResMgr->HT_bGetDiffuseColor( HT_ID_MATERIAL_TREELEAF, m_clrDiffuseLeaf );
	m_pResMgr->HT_bGetAmbientColor( HT_ID_MATERIAL_TREELEAF, m_clrAmbientLeaf );
	m_pResMgr->HT_bGetEmissiveColor( HT_ID_MATERIAL_TREELEAF, m_clrEmissiveLeaf );
	*/
	// 시간 관련 값들을 로드한다.
	HT_vLoadTimeValue( pCfg );

	HT_DELETE( pCfg );

	// Intro Map 일 경우의 시간 세팅
	if ( m_dwCurrentMapID == 40100 )
		m_fNowTimeInAllDay = 0.25f;		// 정오

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadMapSystem( HTdword dwMapID )
{
	//----------------------------------------------------------------
	// 로드한 지형정보를 이용하여 맵 시스템을 초기화한다.
	m_pMapSystem = new CHTMapSystem;

	HTuint nWidthX = 0;
	HTuint nWidthZ = 0;
	CHTEngineObj* pTerrain = m_p3DMgr->HT_pGetObject( m_idTerrain );
	if ( pTerrain )
	{
		nWidthX = pTerrain->HT_nGetWidth();
		nWidthZ = pTerrain->HT_nGetHeight();
	}

	m_pMapSystem->HT_hrCreate( nWidthX, nWidthZ, m_p3DMgr );

	m_pMapSystem->HT_hrSetLODValues( m_fLODDistanceLow1, m_fLODDistanceLow2, m_fLODDistanceLow3, 
		m_fLODDistanceHigh1, m_fLODDistanceHigh2, m_fLODDistanceHigh3, m_fLODDistanceFar, m_fLODDistanceFarSM,
		m_fCharLODDistance1, m_fCharLODDistance2, m_fCharLODDistance3 );

	CHTString strFile;
	m_pResMgr->HT_bGetTCCFileName( dwMapID, strFile );
	strFile = m_strMapPath + _T("\\") + strFile;

	if ( dwMapID != 40100 )	// intro 맵의 경우 다른 맵 시스템들을 로드할 필요없다.
	{
		HT_CHECK( m_pMapSystem->HT_hrLoad( strFile ) );

		strFile--;strFile--;strFile--;
		strFile += _T("tms");
		m_pMapSystem->HT_hrLoadMapSound( strFile );

		strFile--;strFile--;strFile--;
		strFile += _T("tmi");
		m_pMapSystem->HT_hrLoadMapHPVS( strFile );

		strFile--;strFile--;strFile--;
		strFile += _T("tbo");
		m_pMapSystem->HT_hrLoadMapBound( strFile );

		strFile--;strFile--;strFile--;
		strFile += _T("tmf");
		m_pMapSystem->HT_hrLoadMapAreaIndicator( strFile );

		strFile--;strFile--;strFile--;
		strFile += _T("msb");
		m_pMapSystem->HT_hrOpenShootPoint( strFile );

		strFile--;strFile--;strFile--;
		strFile += _T("tfs");
		m_pMapSystem->HT_hrOpenFootSound( strFile );
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrLoadWaterFile( CHTString& strPath, CHTString& strFile )
{
	CHTFile WaterFile;
	CHTString strReadBuffer;

	strFile = strPath + _T("\\") + strFile;
	WaterFile.HT_bOpen( strFile, HT_FILEOPT_TEXT |	HT_FILEOPT_READONLY );
	{
		HTuint					i;
		HTfloat					a, r, g, b;

		WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	strReadBuffer.HT_hrCleanUp();
		WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );
		m_iNumWater = strReadBuffer.HT_iToInt();	strReadBuffer.HT_hrCleanUp();
		m_arridWater = new HTint [m_iNumWater];

		for ( i = 0; i < m_iNumWater; ++i )
		{
			HT_EOBJ_CREATEPARAM		waterParam;

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// x방향 점의 갯수
			waterParam.iWidth = strReadBuffer.HT_iToInt();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// z방향 점의 갯수
			waterParam.iHeight	= strReadBuffer.HT_iToInt();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// x방향그리드의 실수 길이
			waterParam.fSizePerGrid	= strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Z방향그리드의 실수 길이
			waterParam.fRange	= strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// 워터 텍스쳐의 이름
			waterParam.strFileName = strReadBuffer;
			waterParam.strFileName	// 경로까지 지정한다.
				= m_oResourcePath.strFX + _T("\\") + waterParam.strFileName;
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Ambient.a
			a = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Ambient.r
			r = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Ambient.g
			g = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Ambient.b
			b = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			waterParam.clrAmbient = HT_COLOR( r, g, b, a );

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Diffuse.a
			a = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Diffuse.r
			r = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Diffuse.g
			g = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Diffuse.b
			b = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			waterParam.clrDiffuse = HT_COLOR( r, g, b, a );

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Specular.a
			a = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Specular.r
			r = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Specular.g
			g = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Specular.b
			b = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			waterParam.clrDiffuseLeaf = HT_COLOR( r, g, b, a );

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Emissive.a
			a = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Emissive.r
			r = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Emissive.g
			g = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Emissive.b
			b = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			waterParam.clrEmissive = HT_COLOR( r, g, b, a );

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Material.Power
			waterParam.fFalloff = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			waterParam.matTransform._11 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			waterParam.matTransform._12 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			waterParam.matTransform._13 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 1행
			waterParam.matTransform._14 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			waterParam.matTransform._21 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			waterParam.matTransform._22 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			waterParam.matTransform._23 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 2행
			waterParam.matTransform._24 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			waterParam.matTransform._31 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			waterParam.matTransform._32 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			waterParam.matTransform._33 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 3행
			waterParam.matTransform._34 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			waterParam.matTransform._41 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			waterParam.matTransform._42 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			waterParam.matTransform._43 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 4행
			waterParam.matTransform._44 = strReadBuffer.HT_fToFloat();
			strReadBuffer.HT_hrCleanUp();

			waterParam.eObjType = HT_EOBJTYPE_WATER;

			m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strFX, 
				m_oResourcePath.strFX );

			m_p3DMgr->HT_hrCreateObject( &(m_arridWater[i]), &waterParam );
		}

		// Water Zoro Read

		if ( WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' ) == HT_FALSE )
		{ // [ZORO_WATER]가 없는 경우
			WaterFile.HT_vClose();
			return HT_OK;
		}

		WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	//Num of ZoroWater
		m_iNumWaterZoro = strReadBuffer.HT_iToInt();

		if ( m_iNumWaterZoro > 0 )	m_arridWaterZoro = new HTint [m_iNumWaterZoro];
		else						m_iNumWaterZoro = -1;

		for ( HTint j = 0; j < m_iNumWaterZoro; ++j )
		{
			HTmatrix	matWorld4WaterZoro;
			HTfloat		fWidth4WaterZoro, fHeight4WaterZoro;
			HT_COLOR	clrLayerOne4WaterZoro, clrLayerTwo4WaterZoro;
			HTfloat		fLayerOneFrameTime4WaterZoro, fLayerTwoFrameTime4WaterZoro;
			HTfloat		fLayerOneTextureWidth4WaterZoro, fLayerOneTextureHeight4WaterZoro;
			HTfloat		fLayerTwoTextureWidth4WaterZoro, fLayerTwoTextureHeight4WaterZoro;
			HTint		iNumLayerOneFrame4WaterZoro, iNumLayerTwoFrame4WaterZoro;
			CHTString	strTextureSetFileName4WaterZoro;

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			matWorld4WaterZoro._11 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			matWorld4WaterZoro._12 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 1행
			matWorld4WaterZoro._13 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 1행
			matWorld4WaterZoro._14 = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			matWorld4WaterZoro._21 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			matWorld4WaterZoro._22 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 2행
			matWorld4WaterZoro._23 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 2행
			matWorld4WaterZoro._24 = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			matWorld4WaterZoro._31 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			matWorld4WaterZoro._32 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 3행
			matWorld4WaterZoro._33 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 3행
			matWorld4WaterZoro._34 = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			matWorld4WaterZoro._41 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			matWorld4WaterZoro._42 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, ' ' );	// World Matrix 4행
			matWorld4WaterZoro._43 = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// World Matrix 4행
			matWorld4WaterZoro._44 = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Width
			fWidth4WaterZoro = strReadBuffer.HT_fToFloat(); 
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Height
			fHeight4WaterZoro = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Color
			clrLayerOne4WaterZoro.r = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Color
			clrLayerOne4WaterZoro.g = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Color
			clrLayerOne4WaterZoro.b = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Color
			clrLayerOne4WaterZoro.a = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Color
			clrLayerTwo4WaterZoro.r = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Color
			clrLayerTwo4WaterZoro.g = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Color
			clrLayerTwo4WaterZoro.b = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Color
			clrLayerTwo4WaterZoro.a = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 FrameTime
			fLayerOneFrameTime4WaterZoro = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 FrameTime
			fLayerTwoFrameTime4WaterZoro = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Texture Width
			fLayerOneTextureWidth4WaterZoro = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Texture Height
			fLayerOneTextureHeight4WaterZoro = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Texture Width
			fLayerTwoTextureWidth4WaterZoro = strReadBuffer.HT_fToFloat();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Texture Height
			fLayerTwoTextureHeight4WaterZoro = strReadBuffer.HT_fToFloat();

			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer1 Texture Frame Num
			iNumLayerOneFrame4WaterZoro = strReadBuffer.HT_iToInt();
			WaterFile.HT_bReadString( (HTtchar*)strReadBuffer, HT_MAX_STR, '\n' );	// Layer2 Texture Frame Num
			iNumLayerTwoFrame4WaterZoro = strReadBuffer.HT_iToInt();

			WaterFile.HT_bReadString( (HTtchar*)strTextureSetFileName4WaterZoro, HT_MAX_STR, '\n' );
			// Texture Set

			HT_EOBJ_CREATEPARAM WaterZoroCreateParam;

			WaterZoroCreateParam.eObjType		= HT_EOBJTYPE_WATER_ZORO;
			WaterZoroCreateParam.matTransform	= matWorld4WaterZoro;
			WaterZoroCreateParam.vecScale.x		= fWidth4WaterZoro;
			WaterZoroCreateParam.vecScale.z		= fHeight4WaterZoro;
			WaterZoroCreateParam.clrDiffuse		= clrLayerOne4WaterZoro;
			WaterZoroCreateParam.clrAmbient		= clrLayerTwo4WaterZoro;
			WaterZoroCreateParam.fNear			= fLayerOneFrameTime4WaterZoro;
			WaterZoroCreateParam.fFar			= fLayerTwoFrameTime4WaterZoro;
			WaterZoroCreateParam.fCenterRatio	= fLayerOneTextureWidth4WaterZoro;			
			WaterZoroCreateParam.fFalloff		= fLayerOneTextureHeight4WaterZoro;			
			WaterZoroCreateParam.fLifeTime		= fLayerTwoTextureWidth4WaterZoro;			
			WaterZoroCreateParam.fLODDetail		= fLayerTwoTextureHeight4WaterZoro;
			WaterZoroCreateParam.iHeight		= iNumLayerOneFrame4WaterZoro;
			WaterZoroCreateParam.iWidth			= iNumLayerTwoFrame4WaterZoro;
			WaterZoroCreateParam.strFileName	= strTextureSetFileName4WaterZoro;

			m_p3DMgr->HT_hrCreateObject( &m_arridWaterZoro[j], &WaterZoroCreateParam );
		}

	}
	WaterFile.HT_vClose();

	return ( HT_OK );
}

HTint CHTEngineHandler::HT_iCreateUIModel( CHTString& strFile, HT_ENGINEOBJ_TYPE eType )
{
	HTint idObjID;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = eType;
	objParam.byForWhat = HT_EOBJ_FOR_UI;
	objParam.strFileName = strFile;
	objParam.clrDiffuse = m_clrDiffuseChar;
	objParam.clrAmbient = m_clrAmbientChar;
	objParam.clrEmissive = m_clrEmissiveChar;
	objParam.vecPosition = HTvector3( 0.0f, 0.0f, 0.0f );

	HT_CHECK( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) );

	return ( idObjID );
}

HTdword
CHTEngineHandler::HT_dwGetSkillType( HTdword dwSkillID )
{
	HTdword dwSkillType;
	//Skill Type Defined
	//#define HT_SKILL_TYPE_ACTION_NOCAST_SHORT		1
	//#define HT_SKILL_TYPE_ACTION_YESCAST_SHORT	2
	//#define HT_SKILL_TYPE_ACTION_NOCAST_LONG		3
	//#define HT_SKILL_TYPE_ACTION_YESCAST_LONG		4
	//#define HT_SKILL_TYPE_ACTIVE_YESSTATE			5
	//#define HT_SKILL_TYPE_ACTIVE_NOSTATE			6

	if ( HT_IS_PCSKILL(dwSkillID) )
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );
		m_pFXPCResMgr->HT_bGetSkillType( dwSkill, dwSkillType );
		return dwSkillType;
	}
	else if ( HT_IS_MONSTERSKILL(dwSkillID) )
	{
		m_pFXMAPResMgr->HT_bGetSkillType( dwSkillID, dwSkillType );
	}
	else return 0;

	return dwSkillType;
}

HTdword
CHTEngineHandler::HT_dwGetSkillActionActivePassive( HTdword dwSKillID )
{
	HTdword dwSkillType;

	if ( HT_IS_PCSKILL( dwSKillID ) )
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSKillID, dwSkill );

		if ( dwSkill == 0 ) return HT_PCSKILLTYPE_PASSIVE;

		m_pFXPCResMgr->HT_bGetSkillType( dwSkill, dwSkillType );

		if ( dwSkillType > 0 && dwSkillType < 20 ) return HT_PCSKILLTYPE_ACTION;
		else if ( dwSkillType > 20 && dwSkillType < 40 ) return HT_PCSKILLTYPE_ACTIVE;
		else return 0;
	}

	return 0;
}

HTRESULT
CHTEngineHandler::HT_hrGetSkillAniType( HTdword dwSkillID, HTbool* pbIs1H, HTbool* pbIs2HSword, HTbool* pbIs2HAxe, HTbool* pbIsBow, HTbool* pbIsFist )
{	
	if ( HT_IS_PCSKILL( dwSkillID ) )
	{
		if ( this->HT_dwGetSkillActionActivePassive( dwSkillID ) == HT_PCSKILLTYPE_PASSIVE )
		{
			*pbIs1H = HT_FALSE;
			*pbIs2HSword = HT_FALSE;
			*pbIs2HAxe = HT_FALSE;
			*pbIsBow = HT_FALSE;
			*pbIsFist = HT_FALSE;

			return HT_OK;
		}
		else if ( this->HT_dwGetSkillActionActivePassive( dwSkillID ) == HT_PCSKILLTYPE_ACTIVE )
		{
			*pbIs1H = HT_FALSE;
			*pbIs2HSword = HT_FALSE;
			*pbIs2HAxe = HT_FALSE;
			*pbIsBow = HT_FALSE;
			*pbIsFist = HT_TRUE;

			return HT_OK;
		}
		else
		{
			HTdword dwSkill;
			m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );

			*pbIs1H = HT_FALSE;
			*pbIs2HSword = HT_FALSE;
			*pbIs2HAxe = HT_FALSE;
			*pbIsBow = HT_FALSE;
			*pbIsFist = HT_FALSE;

			HTdword dwAni = 0, dwAniFApron = 0, dwAniBApron = 0;
			if ( m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan1H( dwSkill, dwAni, dwAniFApron, dwAniBApron ) )
			{
				if ( dwAni != 0 && dwAniFApron != 0 && dwAniBApron != 0 ) *pbIs1H = HT_TRUE;
			}
			if ( m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan2HSword( dwSkill, dwAni, dwAniFApron, dwAniBApron ) )
			{
				if ( dwAni != 0 && dwAniFApron != 0 && dwAniBApron != 0 ) *pbIs2HSword = HT_TRUE;
			}
			if ( m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan2HAxe( dwSkill, dwAni, dwAniFApron, dwAniBApron ) )
			{
				if ( dwAni != 0 && dwAniFApron != 0 && dwAniBApron != 0 ) *pbIs2HAxe = HT_TRUE;
			}
			if ( m_pFXPCResMgr->HT_bGetSkillActionAniActivateManBow( dwSkill, dwAni, dwAniFApron, dwAniBApron ) )
			{
				if ( dwAni != 0 && dwAniFApron != 0 && dwAniBApron != 0 ) *pbIsBow = HT_TRUE;
			}
			if ( m_pFXPCResMgr->HT_bGetSkillActionAniActivateManFist( dwSkill, dwAni, dwAniFApron, dwAniBApron ) )
			{
				if ( dwAni != 0 && dwAniFApron != 0 && dwAniBApron != 0 ) *pbIsFist = HT_TRUE;
			}

			return HT_OK;
		}
	}
	else
	{
		*pbIs1H = HT_FALSE;
		*pbIs2HSword = HT_FALSE;
		*pbIs2HAxe = HT_FALSE;
		*pbIsBow = HT_FALSE;
		*pbIsFist = HT_FALSE;

		return HT_FAIL;
	}
}

HTbool
CHTEngineHandler::HT_bIsWeaponBack( HTdword dwSkillID )
{
	if ( HT_IS_PCSKILL( dwSkillID ) )
	{
		HTdword dwSkill, dwSkillType;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );
		m_pFXPCResMgr->HT_bGetSkillType( dwSkill, dwSkillType );

		if ( dwSkill == 0 ) // PASSIVE
		{
			return HT_FALSE;
		}
		else if ( dwSkillType > 0 && dwSkillType < 20 ) // HT_PCSKILLTYPE_ACTION
		{
			HTbool bIsWeaponBack;
			if ( m_pFXPCResMgr->HT_bGetIsWeaponBack( dwSkill, bIsWeaponBack ) )
			{
				return bIsWeaponBack;
			}
			else
			{
				return HT_FALSE;
			}
		}
		else if ( dwSkillType > 20 && dwSkillType < 40 ) // HT_PCSKILLTYPE_ACTIVE
		{
			return HT_TRUE;
		}
		else return HT_FALSE;
	}
	else
	{
		return HT_FALSE;
	}
}

HTRESULT
CHTEngineHandler::HT_hrChangeSkillActionAnimation( HTint idObj, HTdword dwSkillID, HTSkillAniSeq eSkillAniSeq, HTint idTribe, HTint idItem, HTint idHead, HTfloat fPlayTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );

		HTSkillItemType eItemType = HT_SKILLITEM_FIST;

		if ( idItem <= 0 )	// 아이템을 안 들고 있으면
			eItemType = HT_SKILLITEM_FIST;
		else
		{
			// 먼저 아이템을 보고 그것의 타입을 참조하여 어떤 공격 에니를 틀 것인지 결정한다.
			HTdword dwItemType;
			if ( m_pResMgr->HT_bGetItemType( idItem, dwItemType ) )
			{
				switch ( dwItemType )
				{
				case 901 :	case 902 :	case 903 :	case 904 : case 910 : case 911 :
					eItemType = HT_SKILLITEM_1H;
					break;
				case 905 : case 913 :
					eItemType = HT_SKILLITEM_FIST;
					break;
				case 906 : case 907 : case 908 :
					eItemType = HT_SKILLITEM_2HAXE;
					break;
				case 909 : case 914 :
					eItemType = HT_SKILLITEM_2HSWORD;
					break;
				case 915 :
					eItemType = HT_SKILLITEM_BOW;
					break;
				default:
					eItemType = HT_SKILLITEM_FIST;
				}
			}
			else
			{
				eItemType = HT_SKILLITEM_FIST;
			}
		}

		// 활공격 애니메이션인 경우 화살이 오른손에 나타나야 한다.
		// 화살 모델의 리소스 값이 14179 이다.
		if ( eItemType == HT_SKILLITEM_BOW && eSkillAniSeq == HT_SKILLANISEQ_READY )
		{
			CHTString strSocket( _T("Arrow") );
			this->HT_hrDetachObject( idObj, strSocket );
			this->HT_hrAttachObject( idObj, strSocket, 14179, HT_fGetModelScaleFactor( idTribe, HT_ITEM_ARROW_MODELID ) );
		}

		HTint iLoop;
		HTdword dwAniID, dwAniFApronID, dwAniBApronID;
		switch ( eSkillAniSeq )
		{
		case HT_SKILLANISEQ_READY :
			{
				iLoop = 1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyMan1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyMan2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyMan2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyManBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}
				else
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyWom1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyWom2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyWom2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniReadyWomBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}
			}
			break;
		case HT_SKILLANISEQ_CAST :
			{
				iLoop = -1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastMan1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastMan2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastMan2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastManBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}
				else
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastWom1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastWom2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastWom2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniCastWomBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}
			}
			break;
		case HT_SKILLANISEQ_ATTACK :
			{
				iLoop = 1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateMan2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateManBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}
				else
				{
					if ( eItemType == HT_SKILLITEM_1H )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateWom1H( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HSWORD )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateWom2HSword( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_2HAXE )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateWom2HAxe( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_FIST )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else if ( eItemType == HT_SKILLITEM_BOW )
						m_pFXPCResMgr->HT_bGetSkillActionAniActivateWomBow( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
					else
						dwAniID = dwAniFApronID = dwAniBApronID = 0;
				}

				HTdword dwSound;
				if ( HT_IS_PC_MAN( idTribe ) )	m_pFXPCResMgr->HT_bGetSkillActionSoundActivateMan( dwSkill, dwSound );
				else							m_pFXPCResMgr->HT_bGetSkillActionSoundActivateWom( dwSkill, dwSound );

				HTvector3 vecPos, vecOffsetPos;
				m_p3DMgr->HT_hrGetPosition( idObj, vecPos );
				m_p3DMgr->HT_hrGetOffsetPosFromMainObj( vecPos, vecOffsetPos );
				m_p3DMgr->HT_hrPlaySound( dwSound, 1, vecOffsetPos );
			}
			break;
		default:
			return HT_FAIL;
		}

		if ( dwAniID > 0 )
		{
			HTdword dwAniHeadID;
			CHTString strSocket;
			if ( idHead > 0 )
			{
				HTdword dwIDHead = HT_dwGetHeadID( idTribe, idHead );
				HTdword dwHairType;
				strSocket = _T("Hair");
				m_pResMgr->HT_bGetHairType( idHead, dwHairType );

				switch ( dwHairType )
				{
				case 1:
					m_pResMgr->HT_bGetHair1AniID( dwAniID, dwAniHeadID );
					break;
				case 2:
					m_pResMgr->HT_bGetHair2AniID( dwAniID, dwAniHeadID );
					break;
				default:
					m_pResMgr->HT_bGetHair1AniID( dwAniID, dwAniHeadID );
					break;
				}

				this->HT_hrLoadToResPool( dwAniHeadID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniHeadID, m_fAniInterpolateTime, fPlayTime );
			}

			this->HT_hrLoadToResPool( dwAniFApronID, HT_FALSE );
			this->HT_hrLoadToResPool( dwAniBApronID, HT_FALSE );

			strSocket = _T("FApron");
			m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniFApronID, m_fAniInterpolateTime, fPlayTime );
			strSocket = _T("BApron");
			m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniBApronID, m_fAniInterpolateTime, fPlayTime );

			this->HT_hrLoadToResPool( dwAniID, HT_FALSE );

			return m_p3DMgr->HT_hrChangeAnimation( idObj, dwAniID, 0, iLoop, 0.0f, fPlayTime );
		}
		else
		{
			return HT_FAIL;
		}
	}
	else return HT_FAIL;
}

HTRESULT
CHTEngineHandler::HT_hrChangeSkillActiveAnimation( HTint idObj, HTdword dwSkillID, HTSkillAniSeq eSkillAniSeq, HTint idTribe, HTint idItem, HTint idHead, HTfloat fPlayTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );

		HTint iLoop;
		HTdword dwAniID, dwAniFApronID, dwAniBApronID;
		switch ( eSkillAniSeq )
		{
		case HT_SKILLANISEQ_READY :
			{
				iLoop = 1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniReadyManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
				else
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniReadyWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
			}
			break;
		case HT_SKILLANISEQ_CAST :
			{
				iLoop = -1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniCastManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
				else
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniCastWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
			}
			break;
		case HT_SKILLANISEQ_ACTIVATE :
			{
				iLoop = 1;
				if ( HT_IS_PC_MAN( idTribe ) )
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniActivateManFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
				else
				{
					m_pFXPCResMgr->HT_bGetSkillActiveAniActivateWomFist( dwSkill, dwAniID, dwAniFApronID, dwAniBApronID );
				}
			}
			break;
		default:
			return HT_FAIL;
		}

		//--------------------------------------------------------------------
		// 소켓에 붙은 모델들의 에니메이션을 세팅해 준다.
		HTdword dwAniHeadID;
		CHTString strSocket;
		if ( idHead > 0 )
		{
			HTdword dwIDHead = HT_dwGetHeadID( idTribe, idHead );
			HTdword dwHairType;
			strSocket = _T("Hair");
			m_pResMgr->HT_bGetHairType( idHead, dwHairType );

			switch ( dwHairType )
			{
			case 1:
				m_pResMgr->HT_bGetHair1AniID( dwAniID, dwAniHeadID );
				break;
			case 2:
				m_pResMgr->HT_bGetHair2AniID( dwAniID, dwAniHeadID );
				break;
			default:
				m_pResMgr->HT_bGetHair1AniID( dwAniID, dwAniHeadID );
				break;
			}

			this->HT_hrLoadToResPool( dwAniHeadID, HT_FALSE );
			m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniHeadID, m_fAniInterpolateTime, fPlayTime );
		}

		this->HT_hrLoadToResPool( dwAniFApronID, HT_FALSE );
		this->HT_hrLoadToResPool( dwAniBApronID, HT_FALSE );

		strSocket = _T("FApron");
		m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniFApronID, m_fAniInterpolateTime, fPlayTime );
		strSocket = _T("BApron");
		m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwAniBApronID, m_fAniInterpolateTime, fPlayTime );

		this->HT_hrLoadToResPool( dwAniID, HT_FALSE );

		return m_p3DMgr->HT_hrChangeAnimation( idObj, dwAniID, 0, iLoop, 0.0f, fPlayTime );
	}
	else return HT_FAIL;
}

HTRESULT
CHTEngineHandler::HT_hrStartSFX( HTint *pidFX, HTdword dwSkillID, HT_SFX_WHEN eType, HTint idParent, HTbool bLoop, HTint iLevel )
{
	HTdword dwFXID = 0, dwCategory = 0, dwWhereAttachType = HT_FX_WHERE_ATTACKER_NOSOCKET, dwPriority = 10;
	CHTString strFX;
	CHTString strSocket;

	if ( HT_IS_PCSKILL(dwSkillID) )
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );
		switch ( eType )
		{
		case HT_SFX_WHEN_READY :	m_pFXPCResMgr->HT_bGetReadyFX( dwSkill, dwFXID );		break;
		case HT_SFX_WHEN_CAST :		m_pFXPCResMgr->HT_bGetCastFX( dwSkill, dwFXID );		break;
		case HT_SFX_WHEN_ACTIVATE :	m_pFXPCResMgr->HT_bGetActivateFX( dwSkill, dwFXID );	break;
		case HT_SFX_WHEN_FOLLOW :	m_pFXPCResMgr->HT_bGetFollowFX( dwSkill, dwFXID );		break;
		case HT_SFX_WHEN_IMPACT :	m_pFXPCResMgr->HT_bGetImpactFX( dwSkill, dwFXID );		break;
		case HT_SFX_WHEN_STATE :	m_pFXPCResMgr->HT_bGetStateFX( dwSkill, dwFXID );		break;
		default : return HT_FAIL;
		}

		// Skill Level Up! 12345, 678, 910
		if ( iLevel > 0 && iLevel <= 5 ) iLevel = 0;
		else if ( iLevel > 5 && iLevel <= 8 ) iLevel = 1;
		else if ( iLevel > 8 && iLevel <= 10 ) iLevel = 2;

		m_pFXPCResMgr->HT_bGetFX( (HTdword)(dwFXID + iLevel), strFX, dwCategory, dwWhereAttachType, dwPriority );
	}
	else if ( HT_IS_MONSTERSKILL(dwSkillID) )
	{
		switch ( eType )
		{
		case HT_SFX_WHEN_CAST :		m_pFXMAPResMgr->HT_bGetCastFX( dwSkillID, dwFXID );		break;
		case HT_SFX_WHEN_ACTIVATE :	m_pFXMAPResMgr->HT_bGetActivateFX( dwSkillID, dwFXID );	break;
		case HT_SFX_WHEN_FOLLOW :	m_pFXMAPResMgr->HT_bGetFollowFX( dwSkillID, dwFXID );	break;
		case HT_SFX_WHEN_IMPACT :	m_pFXMAPResMgr->HT_bGetImpactFX( dwSkillID, dwFXID );	break;
		case HT_SFX_WHEN_STATE :	m_pFXMAPResMgr->HT_bGetStateFX( dwSkillID, dwFXID );	break;
		default : return HT_FAIL;
		}

		m_pFXMAPResMgr->HT_bGetFX( dwFXID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERSKILL;

		//return HT_OK;
	}
	else if ( HT_IS_FXMON( dwSkillID ) )
	{
		m_pFXMAPResMgr->HT_bGetDieActivateFX( dwSkillID, dwFXID );
		switch ( eType )
		{
		case HT_SFX_WHEN_ACTIVATE :					break;
		case HT_SFX_WHEN_FOLLOW :	dwFXID += 1;	break;
		case HT_SFX_WHEN_IMPACT :	dwFXID += 2;	break;
		default : return HT_FAIL;
		}

		m_pFXMAPResMgr->HT_bGetFX( dwFXID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERETC;

		//return HT_OK;
	}
	else return HT_FAIL;

	switch ( dwWhereAttachType )
	{
	case HT_FX_WHERE_ATTACKER_NOSOCKET : case HT_FX_WHERE_OPPONENT_NOSOCKET : case HT_FX_WHERE_BULLET_NOSOCKET : return this->HT_hrStartFX( pidFX, dwCategory, strFX, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET1 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET1, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET2 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET2, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET3 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET3, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET4 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET4, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET5 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET5, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET6 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET6, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET1 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET1, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET2 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET2, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET3 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET3, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET4 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET4, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET5 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET5, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET6 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET6, idParent, dwPriority, bLoop );
	default: return HT_FAIL;
	}
}

HTRESULT
CHTEngineHandler::HT_hrStartSFX( HTint *pidFX, HTdword dwFxID, HTint idParent, HTbool bLoop )
{
	CHTString strFX;
	HTdword dwCategory = 0, dwWhereAttachType = 0, dwPriority = 10;

	if ( HT_IS_ITEM_WEAPON( dwFxID ) )
	{	// 넘어오는 dwFxID가 FX값이 아니고 장착된 무기인 경우 그게 맞는 ImpactFX를 틀어준다.
		HTdword dwWeaponType, dwFX;
		m_pResMgr->HT_bGetItemType( dwFxID, dwWeaponType );
		m_pResMgr->HT_bGetImpactFX( dwWeaponType, dwFX );
		m_pFXPCResMgr->HT_bGetFX( dwFX, strFX, dwCategory, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_PCETC;
		dwWeaponType = HT_FX_WHERE_ATTACKER_SOCKET4;
	}
	else if ( HT_IS_FXNAME_PCSKILL( dwFxID ) || HT_IS_FXNAME_PCEFFECT( dwFxID ) )
	{
		m_pFXPCResMgr->HT_bGetFX( dwFxID, strFX, dwCategory, dwWhereAttachType, dwPriority );
	}
	else if ( HT_IS_FXNAME_MONSTERSKILL( dwFxID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFxID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERSKILL;
	}
	else if ( HT_IS_FXNAME_MONSTERETC( dwFxID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFxID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERETC;
	}
	else if ( HT_IS_FXNAME_FIELDEFFECT( dwFxID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFxID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_FIELD;
	}
	// Monster 탄생 Effect
	else if ( HT_IS_MONSTEREFFECT( dwFxID ) )
	{
		HTdword dwBornFX = 0;
		m_pFXMAPResMgr->HT_bGetBornFX( dwFxID, dwBornFX );
		m_pFXMAPResMgr->HT_bGetFX( dwBornFX, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERETC;
	}
	else return HT_FAIL;

	switch ( dwWhereAttachType )
	{
	case HT_FX_WHERE_ATTACKER_NOSOCKET : case HT_FX_WHERE_OPPONENT_NOSOCKET : case HT_FX_WHERE_BULLET_NOSOCKET : return this->HT_hrStartFX( pidFX, dwCategory, strFX, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET1 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET1, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET2 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET2, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET3 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET3, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET4 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET4, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET5 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET5, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_ATTACKER_SOCKET6 : return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_ATTACKER_ATTACH_SOCKET6, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET1 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET1, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET2 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET2, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET3 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET3, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET4 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET4, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET5 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET5, idParent, dwPriority, bLoop );
	case HT_FX_WHERE_OPPONENT_SOCKET6 :	return this->HT_hrStartFX( pidFX, dwCategory, strFX, HT_FX_OPPONENT_ATTACH_SOCKET6, idParent, dwPriority, bLoop );
	default: return HT_FAIL;
	}
}

// HK FX 타격 받는 FX 전용
HTRESULT
CHTEngineHandler::HT_hrStartSFX( HTdword dwSkillID, HTint idAttacker, HTint idOpponent, HTint iLevel )
{
	HTdword dwFXID = 0, dwCategory = 0, dwWhereAttachType = HT_FX_WHERE_ATTACKER_NOSOCKET, dwPriority = 10;
	CHTString strFX;
	CHTString strSocket;

	if ( HT_IS_ITEM_WEAPON( dwSkillID ) )
	{	// 넘어오는 dwSkillID가 FX값이 아니고 장착된 무기인 경우 그게 맞는 ImpactFX를 틀어준다.
		HTdword dwWeaponType, dwFX;
		m_pResMgr->HT_bGetItemType( dwSkillID, dwWeaponType );
		m_pResMgr->HT_bGetImpactFX( dwWeaponType, dwFX );
		m_pFXPCResMgr->HT_bGetFX( dwFX, strFX, dwCategory, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_PCETC;
		dwWeaponType = HT_FX_WHERE_ATTACKER_SOCKET4;
	}
	else if ( HT_IS_PCSKILL(dwSkillID) ) 
	{
		HTdword dwSkill;
		m_pFXPCResMgr->HT_bGetSkillID( dwSkillID, dwSkill );
		m_pFXPCResMgr->HT_bGetImpactFX( dwSkill, dwFXID );

		iLevel = (HTint)((iLevel-1) / 2.0f);
		m_pFXPCResMgr->HT_bGetFX( (HTdword)(dwFXID + iLevel), strFX, dwCategory, dwWhereAttachType, dwPriority );
	}
	else if ( HT_IS_MONSTERSKILL(dwSkillID) )
	{
		m_pFXMAPResMgr->HT_bGetImpactFX( dwSkillID, dwFXID );
		m_pFXMAPResMgr->HT_bGetFX( dwFXID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_MONSTERSKILL;
	}
	// Normal Attack
	else if ( HT_IS_FXNAME_PCEFFECT(dwSkillID) )
	{
		m_pFXPCResMgr->HT_bGetFX( dwSkillID, strFX, dwCategory, dwWhereAttachType, dwPriority );
	}
	else return HT_FAIL;

	if ( dwWhereAttachType == HT_FX_WHERE_ATTACKER_NOSOCKET 
		|| dwWhereAttachType == HT_FX_WHERE_OPPONENT_NOSOCKET 
		|| dwWhereAttachType == HT_FX_WHERE_BULLET_NOSOCKET )
	{ 
		HTint idFX;
		return this->HT_hrStartFX( &idFX, dwCategory, strFX, idOpponent, dwPriority, HT_FALSE );
	}

	HTfloat fDist = FLT_MAX, fDistTmp;
	HTvector3 vecAPos;
	HT_CHECK( m_p3DMgr->HT_hrGetPosition( idAttacker, vecAPos ) );

	HTvector3 vecOSocketPos;

	m_p3DMgr->HT_hrGetSocketWorldPos( idOpponent, CHTString(_T("Front_Din")),	&vecOSocketPos );
	fDistTmp = CHTVector::HT_fVec3Length( &(vecAPos - vecOSocketPos) );
	fDist = fDistTmp; strSocket = _T("Din"); 

	m_p3DMgr->HT_hrGetSocketWorldPos( idOpponent, CHTString(_T("Front_Din")),	&vecOSocketPos );
	fDistTmp = CHTVector::HT_fVec3Length( &(vecAPos - vecOSocketPos) );
	if ( fDist > fDistTmp  ) { fDist = fDistTmp; strSocket = _T("Front_Din"); }

	m_p3DMgr->HT_hrGetSocketWorldPos( idOpponent, CHTString(_T("Left_Din")),	&vecOSocketPos );
	fDistTmp = CHTVector::HT_fVec3Length( &(vecAPos - vecOSocketPos) );
	if ( fDist > fDistTmp  ) { fDist = fDistTmp; strSocket = _T("Left_Din"); }

	m_p3DMgr->HT_hrGetSocketWorldPos( idOpponent, CHTString(_T("Right_Din")),	&vecOSocketPos );
	fDistTmp = CHTVector::HT_fVec3Length( &(vecAPos - vecOSocketPos) );
	if ( fDist > fDistTmp  ) { fDist = fDistTmp; strSocket = _T("Right_Din"); }

	m_p3DMgr->HT_hrGetSocketWorldPos( idOpponent, CHTString(_T("Back_Din")),	&vecOSocketPos );
	fDistTmp = CHTVector::HT_fVec3Length( &(vecAPos - vecOSocketPos) );
	if ( fDist > fDistTmp  ) { fDist = fDistTmp; strSocket = _T("Back_Din"); }

	HTint idFX;
	return this->HT_hrStartFX( &idFX, dwCategory, strFX, strSocket, idOpponent, dwPriority, HT_FALSE );
}

HTRESULT
CHTEngineHandler::HT_hrStartFieldFX( HTint *pidFX, HTdword dwFxID, HTint idParent, HTbool bLoop, HTint iWhen )
{
	CHTString strFX;
	HTdword dwCategory = 0, dwWhereAttachType = 0, dwPriority = 10;

	if ( HT_IS_FXNAME_FIELDEFFECT( dwFxID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFxID, strFX, dwWhereAttachType, dwPriority );
		dwCategory = HT_FXCATEGORY_FIELD;
	}
	else return HT_FAIL;

	switch ( dwWhereAttachType )
	{
	case HT_FX_WHERE_ATTACKER_NOSOCKET : case HT_FX_WHERE_OPPONENT_NOSOCKET : case HT_FX_WHERE_BULLET_NOSOCKET :
		return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET1 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET1, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET2 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET2, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET3 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET3, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET4 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET4, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET5 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET5, bLoop, iWhen );
	case HT_FX_WHERE_ATTACKER_SOCKET6 : return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_ATTACKER_ATTACH_SOCKET6, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET1 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET1, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET2 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET2, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET3 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET3, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET4 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET4, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET5 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET5, bLoop, iWhen );
	case HT_FX_WHERE_OPPONENT_SOCKET6 :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, HT_FX_OPPONENT_ATTACH_SOCKET6, bLoop, iWhen );
	default: return HT_FAIL;
	}
}

HTRESULT
CHTEngineHandler::HT_hrStartFX( HTint* pidFX, HTdword dwCategory, CHTString& strFX, HTint idParent, HTdword dwPriority, HTbool bLoop )
{
	switch ( dwCategory )
	{
	case HT_FXCATEGORY_PCETC :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCEtc, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCFREE :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCFree, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCGODBRAHMA :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodBrahma, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCGODSHIBA :		return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodShiba, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCGODVISHUNU :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodVishunu, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCRACEASURAK :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceAsuRak, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCRACEDEVGAR :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceDevGar, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCRACENAGAKIN :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceNageKin, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_PCRACEYAKGAN :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceYakGan, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_FIELD :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_MONSTERSKILL :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idMonsterSkill, pidFX, strFX, idParent, dwPriority, bLoop );
	case HT_FXCATEGORY_MONSTERETC :		return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idMonsterEtc, pidFX, strFX, idParent, dwPriority, bLoop );
	default:							return HT_FAIL;
	}
}

HTRESULT
CHTEngineHandler::HT_hrStartFX( HTint* pidFX, HTdword dwCategory, CHTString& strFX, CHTString& strSocket, HTint idParent, HTdword dwPriority, HTbool bLoop )
{
	switch ( dwCategory )
	{
	case HT_FXCATEGORY_PCETC :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCEtc, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCFREE :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCFree, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCGODBRAHMA :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodBrahma, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCGODSHIBA :		return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodShiba, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCGODVISHUNU :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCGodVishunu, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCRACEASURAK :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceAsuRak, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCRACEDEVGAR :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceDevGar, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCRACENAGAKIN :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceNageKin, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_PCRACEYAKGAN :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idPCRaceYakGan, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_FIELD :			return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idField, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_MONSTERSKILL :	return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idMonsterSkill, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	case HT_FXCATEGORY_MONSTERETC :		return m_p3DMgr->HT_hrStartSFX( m_oIDFXMgr.idMonsterEtc, pidFX, strFX, idParent, dwPriority, strSocket, bLoop );
	default:							return HT_FAIL;
	}
}

HTRESULT
CHTEngineHandler::HT_hrPauseSFX( HTint idFx )
{
	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrPlaySFX( HTint idFx )
{
	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrStopSFX( HTint idFx )
{
	// 현재 돌아가고 있는 FX List에서 해당하는 ID를 찾지 못하면 다음과 같이 HT_FAIL을 리턴하게 된다
	// 따라서 다음과 같이 무식한(?) 코드가 가능하다.

	if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCFree, idFx ) ) )
		if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCGodBrahma, idFx ) ) )
			if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCGodShiba, idFx ) ) )
				if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCGodVishunu, idFx ) ) )
					if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCRaceAsuRak, idFx ) ) )
						if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCRaceDevGar, idFx ) ) )
							if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCRaceNageKin, idFx ) ) )
								if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCRaceYakGan, idFx ) ) )
									if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idMonsterSkill, idFx ) ) )
										if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idMonsterEtc, idFx ) ) )
											if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idPCEtc, idFx ) ) )
												if ( HT_FAILED( m_p3DMgr->HT_hrStopSFX( m_oIDFXMgr.idField, idFx ) ) ) return HT_FAIL;

	return HT_OK;
}

HTint
CHTEngineHandler::HT_iGetTextWidth( HT_FONT_TYPE eFont, const HTtchar* pszStr )
{
	HTint idFont;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	return ( m_p3DMgr->HT_iGetTextWidth( idFont, pszStr ) );
}

HTint
CHTEngineHandler::HT_iGetTextHeight( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_RECT& Rect, HT_TEXT_FORMATING eTextFormating )
{
	HTint idFont;
/*
	switch( eFont )
	{
	case HT_FONT_ARIAL_20:
		idFont = m_idFontFPS;
		break;
	case HT_FONT_HANBITNARU_30:
		idFont = m_idFontHanbitNaru30;
		break;
	case HT_FONT_GULIM_12:
		idFont = m_idFontGulim12;
		break;
	case HT_FONT_GULIM_10:
		idFont = m_idFontGulim10;
		break;
	default:*/
		idFont = m_idFontGulim12;
//		break;
//	}

	return ( m_p3DMgr->HT_iGetTextHeight( idFont, pszStr, Rect, eTextFormating ) );
}

//---------------------------------------------------------------------------
// HTint					HT_iGetWidth(HTint iEObjectID);
// D :  텍스쳐의 넓이 구하기
// I : iEObjectID - 엔진오브젝트 아이디
//---------------------------------------------------------------------------
HTint
CHTEngineHandler::HT_iGetWidth(HTint iEObjectID)	//200302대호
{
	CHTEngineObj* pObj = HT_NULL;
	if (!(pObj = m_p3DMgr->HT_pGetObject(iEObjectID))) return -1;
	return pObj->HT_nGetWidth();
}

//---------------------------------------------------------------------------
// HTint					HT_iGetHeight(HTint iEObjectID);
// D :  텍스쳐의 넓이 구하기
// I : iEObjectID - 엔진오브젝트 아이디
//---------------------------------------------------------------------------
HTint
CHTEngineHandler::HT_iGetHeight(HTint iEObjectID)	//200302대호
{
	CHTEngineObj* pObj = HT_NULL;
	if (!(pObj = m_p3DMgr->HT_pGetObject(iEObjectID))) return -1;
	return pObj->HT_nGetHeight();
}

//-----------------------------------------------------------------------------------------------------------
// HTRESULT			HT_hrSetSwordWindOn(HTbool bSwordWindOn)
// M : GAME DEVELOPE TEAM, Chung Daeho, 20021031
// D : SWORD WIND ON/OFF
// I : bSwordWindOn - HT_TRUE/HT_FALSE
// R : HT_OK/HT_FAIL
//-----------------------------------------------------------------------------------------------------------
HTRESULT
CHTEngineHandler::HT_hrSetSwordWindOn( HTint idObj, HTbool bSwordWindOn)
{
	//	m_p3DMgr->HT_pGetObject(idObj)->HT_hrSetSwordWindOn(bSwordWindOn);
	return ( HT_OK );
}

// 2D sprite의 경우, 픽셀 단위로 스케일링하기 위해 만든 함수이다.
HTRESULT				
CHTEngineHandler::HT_hrScaleObject( HTint idObj, HTint iX, HTint iY )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_UPDATEOBJPARAM updateParam;
	updateParam.idCamera = m_idCamera;
	updateParam.iWidth = iX;
	updateParam.iHeight = iY;

	m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );

	return ( HT_OK );
}

HTRESULT 
CHTEngineHandler::HT_hrUpdateWorldTime( HTfloat fElapsedTime )
{
	HT_UPDATEOBJPARAM updateParam;

	updateParam.fElapsedTime = fElapsedTime;
	updateParam.idCamera = m_idCamera;

	// ToDo : 시간을 계산하고 이에 합당한 짓을 한다.
	// 최초의 시작점을 안다.						m_vecSunMoonStartPosition
	// 달과 해가 회전하는 축을 안다.				m_vecSunMoonRotationAxis
	// 낮의 총 길이(초)를 안다.						m_fDayTime
	// 밤의 총 길이(초)를 안다.						m_fNightTime

	// 낮의 길이를 0.5으로 본다.
	// 밤의 길이를 0.5으로 본다.
	// 하루의 길이를 1.0으로 본다.

	// 현재 시간은 1.0 중에 m_fNowTimeInAllDay 로 계산된다.

	// 낮 동안은 해가 렌더링 된다.
	// 밤 동안은 달이 렌더링 된다.

	// Time Calculation
	if ( m_fNowTimeInAllDay < 0.5f )	// 낮시간
	{
		// 지금은 낮인데 좀전에 밤이었다면 지금이 바로 해뜨는 시각!
		if ( m_eCurretTimeStatus == HT_CURRENT_TIME_STATUS_NIGHT ) this->HT_vGoodMorning();

		m_fNowTimeInAllDay += fElapsedTime / (m_fDayTime * 2.0f);
		m_eCurretTimeStatus = HT_CURRENT_TIME_STATUS_DAY;
	}

	else							// 밤시간
	{
		// 지금은 밤인데 좀전에 낮이었다면 지금이 바로 해지는 시각!
		if ( m_eCurretTimeStatus == HT_CURRENT_TIME_STATUS_DAY ) this->HT_vGoodNight();

		m_fNowTimeInAllDay += fElapsedTime / (m_fNightTime * 2.0f);
		m_eCurretTimeStatus = HT_CURRENT_TIME_STATUS_NIGHT;
	}

	if ( m_fNowTimeInAllDay >= 1.0f ) m_fNowTimeInAllDay -= 1.0f;

	// 낮이면 캐릭터 라이트를 끄고, 밤이면 캐릭터 라이트를 켠다.
	//if ( m_bIsDayTime )
	//{
	//	if ( m_idMainCharacter > 0 && m_idCharacterLight > 0 )
	//	{
	//		HT_UPDATEOBJPARAM updateLightParam;
	//		updateLightParam.clrDiffuse = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	//		m_p3DMgr->HT_hrUpdateObject( m_idCharacterLight, &updateLightParam );
	//	}
	//}
	//else
	{
		// Main Character의 위치에 맞게 Character Light의 위치를 업데이트 시킨다.
		if ( m_idMainCharacter > 0 && m_idCharacterLight >= 0 )
		{
			HTvector3 vecPos;
#if 1
			if ( HT_SUCCEED( m_p3DMgr->HT_hrGetPosition( m_idMainCharacter, vecPos ) ) )
			{
				vecPos += m_vecSpotPosition;
			}

			m_oCharLight.Position = vecPos;
			m_p3DMgr->HT_hrChangeLight( m_idCharacterLight, &m_oCharLight );

#else
			HT_UPDATEOBJPARAM updateLightParam;
			CHTEngineObj* pObj = m_p3DMgr->HT_pGetObject( m_idMainCharacter );
			if ( pObj )
			{
				vecPos = *(pObj->HT_pGetPosition());
			}
			vecPos += m_vecSpotPosition;
			updateLightParam.vecPosition = vecPos;
			updateLightParam.clrDiffuse = m_clrSpotSpecular;

			m_p3DMgr->HT_hrUpdateObject( m_idCharacterLight, &updateLightParam );
#endif
		}
	}

	if ( !m_bUpdateTime )
		return ( HT_OK );

	HTfloat	fSkyHeightHigh, fSkyHeightMid, fSkyHeightLow;
	static HT_COLOR
		clrSkyHigh, clrSkyMid, clrSkyLow,
		clrCloud,
		clrSunDiffuse, clrSunAmbient,
		clrSubLightDiffuse, clrSubLightAmbient;
	if ( m_fNowTimeInAllDay >= m_fMorningStart && m_fNowTimeInAllDay < 1.0f )		// 해 뜨기 직전
	{
		HTfloat f		= (m_fNowTimeInAllDay - m_fMorningStart) / (1.0f - m_fMorningStart);
		m_oCurrectFogStatus.clr		= HT_INTERPOLATE( m_clrNightFog,			m_clrMorningFog,			f );
		m_oCurrectFogStatus.fStart	= HT_INTERPOLATE( m_fNightFogStart,			m_fMorningFogStart,			f );
		m_oCurrectFogStatus.fEnd	= HT_INTERPOLATE( m_fNightFogEnd,			m_fMorningFogEnd,			f );
		fSkyHeightHigh	= HT_INTERPOLATE( m_fNightSkyHigh,			m_fMorningSkyHigh,			f );
		fSkyHeightMid	= HT_INTERPOLATE( m_fNightSkyMid,			m_fMorningSkyMid,			f );
		fSkyHeightLow	= HT_INTERPOLATE( m_fNightSkyLow,			m_fMorningSkyLow,			f );
		clrSkyHigh		= HT_INTERPOLATE( m_clrNightSkyHighColor,	m_clrMorningSkyHighColor,	f );
		clrSkyMid		= HT_INTERPOLATE( m_clrNightSkyMidColor,	m_clrMorningSkyMidColor,	f );
		clrSkyLow		= HT_INTERPOLATE( m_clrNightSkyLowColor,	m_clrMorningSkyLowColor,	f );
		clrCloud		= HT_INTERPOLATE( m_clrNightCloudColor,		m_clrMorningCloudColor,		f );
		clrSunDiffuse	= HT_INTERPOLATE( m_clrNightSunDiffuse,		m_clrMorningSunDiffuse,		f );
		clrSunAmbient	= HT_INTERPOLATE( m_clrNightSunAmbient,		m_clrMorningSunAmbient,		f );
		clrSubLightDiffuse
			= HT_INTERPOLATE( m_clrNightSubLightDiffuse, m_clrMorningSubLightDiffuse, f );
		clrSubLightAmbient
			= HT_INTERPOLATE( m_clrNightSubLightAmbient, m_clrMorningSubLightAmbient, f );
	}
	else if ( m_fNowTimeInAllDay >= 0.0f && m_fNowTimeInAllDay < m_fMorningEnd )	// 해 뜬 직후
	{
		HTfloat f		= (m_fNowTimeInAllDay) / (m_fMorningEnd);
		m_oCurrectFogStatus.clr		= HT_INTERPOLATE( m_clrMorningFog,			m_clrNoonFog,				f );
		m_oCurrectFogStatus.fStart	= HT_INTERPOLATE( m_fMorningFogStart,		m_fNoonFogStart,			f );
		m_oCurrectFogStatus.fEnd	= HT_INTERPOLATE( m_fMorningFogEnd,			m_fNoonFogEnd,				f );
		fSkyHeightHigh	= HT_INTERPOLATE( m_fMorningSkyHigh,		m_fNoonSkyHigh,				f );
		fSkyHeightMid	= HT_INTERPOLATE( m_fMorningSkyMid,			m_fNoonSkyMid,				f );
		fSkyHeightLow	= HT_INTERPOLATE( m_fMorningSkyLow,			m_fNoonSkyLow,				f );
		clrSkyHigh		= HT_INTERPOLATE( m_clrMorningSkyHighColor,	m_clrNoonSkyHighColor,		f );
		clrSkyMid		= HT_INTERPOLATE( m_clrMorningSkyMidColor,	m_clrNoonSkyMidColor,		f );
		clrSkyLow		= HT_INTERPOLATE( m_clrMorningSkyLowColor,	m_clrNoonSkyLowColor,		f );
		clrCloud		= HT_INTERPOLATE( m_clrMorningCloudColor,	m_clrNoonCloudColor,		f );
		clrSunDiffuse	= HT_INTERPOLATE( m_clrMorningSunDiffuse,	m_clrNoonSunDiffuse,		f );
		clrSunAmbient	= HT_INTERPOLATE( m_clrMorningSunAmbient,	m_clrNoonSunAmbient,		f );
		clrSubLightDiffuse
			= HT_INTERPOLATE( m_clrMorningSubLightDiffuse, m_clrNoonSubLightDiffuse, f );
		clrSubLightAmbient
			= HT_INTERPOLATE( m_clrMorningSubLightAmbient, m_clrNoonSubLightAmbient, f );
	}
	else if ( m_fNowTimeInAllDay >= m_fMorningEnd && m_fNowTimeInAllDay < m_fEveningStart )	// 낮시간
	{
		m_oCurrectFogStatus.clr		= m_clrNoonFog;
		m_oCurrectFogStatus.fStart	= m_fNoonFogStart;
		m_oCurrectFogStatus.fEnd	= m_fNoonFogEnd;
		fSkyHeightHigh	= m_fNoonSkyHigh;
		fSkyHeightMid	= m_fNoonSkyMid;
		fSkyHeightLow	= m_fNoonSkyLow;
		clrSkyHigh		= m_clrNoonSkyHighColor;
		clrSkyMid		= m_clrNoonSkyMidColor;
		clrSkyLow		= m_clrNoonSkyLowColor;
		clrCloud		= m_clrNoonCloudColor;
		clrSunDiffuse	= m_clrNoonSunDiffuse;
		clrSunAmbient	= m_clrNoonSunAmbient;
		clrSubLightDiffuse = m_clrNoonSubLightDiffuse;
		clrSubLightAmbient = m_clrNoonSubLightAmbient;
	}
	else if ( m_fNowTimeInAllDay >= m_fEveningStart && m_fNowTimeInAllDay < 0.5f )	// 해 지기 직전
	{
		HTfloat f		= (m_fNowTimeInAllDay - m_fEveningStart) / (0.5f - m_fEveningStart);
		m_oCurrectFogStatus.clr		= HT_INTERPOLATE( m_clrNoonFog,				m_clrEveningFog,			f );
		m_oCurrectFogStatus.fStart	= HT_INTERPOLATE( m_fNoonFogStart,			m_fEveningFogStart,			f );
		m_oCurrectFogStatus.fEnd	= HT_INTERPOLATE( m_fNoonFogEnd,			m_fEveningFogEnd,			f );
		fSkyHeightHigh	= HT_INTERPOLATE( m_fNoonSkyHigh,			m_fEveningSkyHigh,			f );
		fSkyHeightMid	= HT_INTERPOLATE( m_fNoonSkyMid,			m_fEveningSkyMid,			f );
		fSkyHeightLow	= HT_INTERPOLATE( m_fNoonSkyLow,			m_fEveningSkyLow,			f );
		clrSkyHigh		= HT_INTERPOLATE( m_clrNoonSkyHighColor,	m_clrEveningSkyHighColor,	f );
		clrSkyMid		= HT_INTERPOLATE( m_clrNoonSkyMidColor,		m_clrEveningSkyMidColor,	f );
		clrSkyLow		= HT_INTERPOLATE( m_clrNoonSkyLowColor,		m_clrEveningSkyLowColor,	f );
		clrCloud		= HT_INTERPOLATE( m_clrNoonCloudColor,		m_clrEveningCloudColor,		f );
		clrSunDiffuse	= HT_INTERPOLATE( m_clrNoonSunDiffuse,		m_clrEveningSunDiffuse,		f );
		clrSunAmbient	= HT_INTERPOLATE( m_clrNoonSunAmbient,		m_clrEveningSunAmbient,		f );
		clrSubLightDiffuse
			= HT_INTERPOLATE( m_clrNoonSubLightDiffuse, m_clrEveningSubLightDiffuse, f );
		clrSubLightAmbient
			= HT_INTERPOLATE( m_clrNoonSubLightAmbient, m_clrEveningSubLightAmbient, f );
	}
	else if ( m_fNowTimeInAllDay >= 0.5f && m_fNowTimeInAllDay < m_fEveningEnd )	// 해 진 직후
	{
		HTfloat f		= (m_fNowTimeInAllDay - 0.5f) / (m_fEveningEnd - 0.5f);
		m_oCurrectFogStatus.clr		= HT_INTERPOLATE( m_clrEveningFog,			m_clrNightFog,			f );
		m_oCurrectFogStatus.fStart	= HT_INTERPOLATE( m_fEveningFogStart,		m_fNightFogStart,		f );
		m_oCurrectFogStatus.fEnd	= HT_INTERPOLATE( m_fEveningFogEnd,			m_fNightFogEnd,			f );
		fSkyHeightHigh	= HT_INTERPOLATE( m_fEveningSkyHigh,		m_fNightSkyHigh,		f );
		fSkyHeightMid	= HT_INTERPOLATE( m_fEveningSkyMid,			m_fNightSkyMid,			f );
		fSkyHeightLow	= HT_INTERPOLATE( m_fEveningSkyLow,			m_fNightSkyLow,			f );
		clrSkyHigh		= HT_INTERPOLATE( m_clrEveningSkyHighColor,	m_clrNightSkyHighColor,	f );
		clrSkyMid		= HT_INTERPOLATE( m_clrEveningSkyMidColor,	m_clrNightSkyMidColor,	f );
		clrSkyLow		= HT_INTERPOLATE( m_clrEveningSkyLowColor,	m_clrNightSkyLowColor,	f );
		clrCloud		= HT_INTERPOLATE( m_clrEveningCloudColor,	m_clrNightCloudColor,	f );
		clrSunDiffuse	= HT_INTERPOLATE( m_clrEveningSunDiffuse,	m_clrNightSunDiffuse,	f );
		clrSunAmbient	= HT_INTERPOLATE( m_clrEveningSunAmbient,	m_clrNightSunAmbient,	f );
		clrSubLightDiffuse
			= HT_INTERPOLATE( m_clrEveningSubLightDiffuse, m_clrNightSubLightDiffuse, f );
		clrSubLightAmbient
			= HT_INTERPOLATE( m_clrEveningSubLightAmbient, m_clrNightSubLightAmbient, f );
	}
	else if ( m_fNowTimeInAllDay >= m_fEveningEnd && m_fNowTimeInAllDay < m_fMorningStart )	// 밤시간
	{
		m_oCurrectFogStatus.clr		= m_clrNightFog;
		m_oCurrectFogStatus.fStart	= m_fNightFogStart;
		m_oCurrectFogStatus.fEnd	= m_fNightFogEnd;
		fSkyHeightHigh	= m_fNightSkyHigh;
		fSkyHeightMid	= m_fNightSkyMid;
		fSkyHeightLow	= m_fNightSkyLow;
		clrSkyHigh		= m_clrNightSkyHighColor;
		clrSkyMid		= m_clrNightSkyMidColor;
		clrSkyLow		= m_clrNightSkyLowColor;
		clrCloud		= m_clrNightCloudColor;
		clrSunDiffuse	= m_clrNightSunDiffuse;
		clrSunAmbient	= m_clrNightSunAmbient;
		clrSubLightDiffuse = m_clrNightSubLightDiffuse;
		clrSubLightAmbient = m_clrNightSubLightAmbient;
	}
	else HT_ASSERT( 0 );	// 위에 언급한 이외에 다른 시간이 있다면 말도 안되지?

	updateParam.fFogRange = m_oCurrectFogStatus.fStart;
	updateParam.fLODDetail = m_oCurrectFogStatus.fEnd;
	updateParam.clrDiffuse = m_oCurrectFogStatus.clr;
	m_p3DMgr->HT_hrUpdateObject( m_idFog, &updateParam );

	if ( m_idSkyTerrain > 0 )
	{
		updateParam.clrDiffuse = m_oCurrectFogStatus.clr;
		m_p3DMgr->HT_hrUpdateObject( m_idSkyTerrain, &updateParam );
	}

	updateParam.fFlickerTime		= fSkyHeightHigh;
	updateParam.fFogRange			= fSkyHeightMid;
	updateParam.fLODDetail			= fSkyHeightLow;
	updateParam.clrAmbient			= clrSkyLow;
	updateParam.clrDiffuse			= clrSkyMid;
	updateParam.clrSpecular			= clrSkyHigh;
	updateParam.bSwordWindUpdate	= (m_eCurretTimeStatus == HT_CURRENT_TIME_STATUS_DAY) ? HT_TRUE : HT_FALSE;
	m_p3DMgr->HT_hrUpdateObject( m_idSky, &updateParam );

	updateParam.clrDiffuse		= clrCloud;
	m_p3DMgr->HT_hrUpdateObject( m_idSkyCloud, &updateParam );

	static HTmatrix		matRotation;
	static HTmatrix		matRotationSubLight;

	if ( m_eCurretTimeStatus == HT_CURRENT_TIME_STATUS_DAY )	// 낮시간
	{
		CHTMatrix::HT_pmatMatrixRotationAxis( &matRotation,
			&m_vecSunMoonRotationAxis, HT_PIX2 * m_fNowTimeInAllDay );
		CHTVector::HT_pvecVec3TransformCoord( &updateParam.vecPosition,
			&m_vecSunMoonStartPosition, &matRotation );
		updateParam.clrDiffuse = clrSunDiffuse;
		updateParam.clrAmbient = clrSunAmbient;

		updateParam.bSwordWindUpdate = HT_TRUE;
		m_p3DMgr->HT_hrUpdateObject( m_idSun, &updateParam );

		updateParam.bSwordWindUpdate = HT_FALSE;
		m_p3DMgr->HT_hrUpdateObject( m_idMoon, &updateParam );
	}
	else							// 밤시간
	{
		CHTMatrix::HT_pmatMatrixRotationAxis( &matRotation,
			&m_vecSunMoonRotationAxis, HT_PIX2 * m_fNowTimeInAllDay - HT_PI );
		CHTVector::HT_pvecVec3TransformCoord( &updateParam.vecPosition,
			&m_vecSunMoonStartPosition, &matRotation );
		updateParam.clrDiffuse = clrSunDiffuse;
		updateParam.clrAmbient = clrSunAmbient;

		updateParam.bSwordWindUpdate = HT_TRUE;
		m_p3DMgr->HT_hrUpdateObject( m_idMoon, &updateParam );

		updateParam.bSwordWindUpdate = HT_FALSE;
		m_p3DMgr->HT_hrUpdateObject( m_idSun, &updateParam );
	}

	CHTMatrix::HT_pmatMatrixRotationAxis( &matRotationSubLight,
		&m_vecSubLightRotationAxis, HT_PIX2 * m_fNowTimeInAllDay );
	CHTVector::HT_pvecVec3TransformCoord( &m_vecSubLightCurrentPosition,
		&m_vecSubLightStartPosition, &matRotationSubLight );
	m_SubLight.Diffuse		= clrSubLightDiffuse;
	m_SubLight.Ambient		= clrSubLightAmbient;
	m_SubLight.Position		= m_vecSubLightCurrentPosition;
	m_SubLight.Direction	= -m_vecSubLightCurrentPosition;
	m_SubLight.Specular		= HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );

	if ( m_idSubLight >= 0 )
		m_p3DMgr->HT_hrChangeLight( m_idSubLight, &m_SubLight );

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrLoadSpecValues( HTint iLevel, CHTConfigSystem* pCfg )
{
	switch( iLevel ) 
	{
	case 1:	// Low
		pCfg->HT_hrGetValue( _T("LOW"), _T("screenwidth"), &m_iScreenWidth );
		pCfg->HT_hrGetValue( _T("LOW"), _T("screenheight"), &m_iScreenHeight );
		pCfg->HT_hrGetValue( _T("LOW"), _T("bitdepth"), &m_iScreenColorDepth );
		pCfg->HT_hrGetValue( _T("LOW"), _T("ModelCount"), &m_nMaxModelCount );
		pCfg->HT_hrGetValue( _T("LOW"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD3"), &m_fCharLODDistance3 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CamFar"), &m_fCameraFarZ );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODFar"), &m_fLODDistanceFar );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODDetail"), &m_fTerrainLODDetail );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;

	case 2: // Medium
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("screenwidth"), &m_iScreenWidth );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("screenheight"), &m_iScreenHeight );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("bitdepth"), &m_iScreenColorDepth );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("ModelCount"), &m_nMaxModelCount );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD3"), &m_fCharLODDistance3 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CamFar"), &m_fCameraFarZ );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODFar"), &m_fLODDistanceFar );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODDetail"), &m_fTerrainLODDetail );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;

	case 3: // High
		pCfg->HT_hrGetValue( _T("HIGH"), _T("screenwidth"), &m_iScreenWidth );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("screenheight"), &m_iScreenHeight );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("bitdepth"), &m_iScreenColorDepth );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("ModelCount"), &m_nMaxModelCount );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD3"), &m_fCharLODDistance3 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CamFar"), &m_fCameraFarZ );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODFar"), &m_fLODDistanceFar );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODDetail"), &m_fTerrainLODDetail );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;

	default:
		return ( HT_FAIL );
	}

	return ( HT_OK );
}



HTRESULT				
CHTEngineHandler::HT_hrGetScreenCoordFrom3DCoord( HTvector3& vec3DPos, HTvector2& vec2DPos )
{
	HT_CHECK( m_p3DMgr->HT_hrGetScreenCoordFrom3DCoord( vec3DPos, vec2DPos ) );
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrClipObject( HTint idObj, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY )
{
	HT_UPDATEOBJPARAM updateParam;
	updateParam.iClippingLTX = iLTX;
	updateParam.iClippingLTY = iLTY;
	updateParam.iClippingRBX = iRBX;
	updateParam.iClippingRBY = iRBY;

	HT_CHECK( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );

	return ( HT_OK );
}

HTint					
CHTEngineHandler::HT_iCreate2DWindowSprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack )
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_2DSPRITE;
	objParam.dwID = dwID;
	objParam.vecPosition.x = (HTfloat)iPosX;
	objParam.vecPosition.y = (HTfloat)iPosY;
	objParam.iWidth = iSizeX;
	objParam.iHeight = iSizeY;
	objParam.clrDiffuse = clrBack;
	objParam.byForWhat = HT_EOBJ_FOR_UI;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}

HTint					
CHTEngineHandler::HT_iCreate2DWindowUISprite( HTdword dwID, HT_COLOR& clrBack )
{
	return this->HT_iCreate2DWindowUISprite( dwID, 0, 0, 1, 1, clrBack );
}

HTint					
CHTEngineHandler::HT_iCreate2DWindowUISprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack )
{
	HTint idObjID = -1;

	HT_EOBJ_CREATEPARAM objParam;
	objParam.eObjType = HT_EOBJTYPE_2DUISPRITE;
	objParam.dwID = dwID;
	objParam.vecPosition.x = (HTfloat)iPosX;
	objParam.vecPosition.y = (HTfloat)iPosY;
	objParam.iWidth = iSizeX;
	objParam.iHeight = iSizeY;
	objParam.clrDiffuse = clrBack;
	objParam.byForWhat = HT_EOBJ_FOR_UI;

	if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObjID, &objParam ) ) )
	{
		return ( -1 );
	}

	this->HT_vSetCanModify( idObjID );

	return ( idObjID );
}


HTRESULT				
CHTEngineHandler::HT_hrPlayAttackOKSound( HTint idTribe, HTint idItem )
{
	HTdword dwSoundID = 0;
	HTdword dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		HTdword dwItemType = 0;
		m_pResMgr->HT_bGetItemType( idItem, dwItemType );

		if ( dwItemType <= 0 )
			dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;

		m_pResMgr->HT_bGetAttackOKID1( dwItemType, dwMotionSoundID1 );
		m_pResMgr->HT_bGetAttackOKID2( dwItemType, dwMotionSoundID2 );
		m_pResMgr->HT_bGetAttackOKID3( dwItemType, dwMotionSoundID3 );
	}
	else
	{
		return ( HT_FAIL );
	}

	HTint iMod;
	// 만약 사운드가 여러개가 나왔다면 그중에서 랜덤으로 하나를 선택한다.
	// 여기서 쓰이는 사운드의 랜덤은 클라이언트 사이에 동기화가 되지 않아도 된다고 가정한다.
	HTint iSoundCount = 0;
	HTdword dwSelectSound = 0;
	if ( dwMotionSoundID1 > 0 )		iSoundCount += 1;
	if ( dwMotionSoundID2 > 0 )		iSoundCount += 2;
	if ( dwMotionSoundID3 > 0 )		iSoundCount += 4;

	if ( iSoundCount == 0 )	// 사운드가 없으면 0을 전달하여 틀지 말라고 한다.
	{
		dwSelectSound = 0;
	}
	else if ( iSoundCount == 1 )	// 
	{
		dwSelectSound = dwMotionSoundID1;
	}
	else if ( iSoundCount == 2 )	// 
	{
		dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 4 )	// 
	{
		dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 3 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 5 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 6 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID2;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 7 )	// 
	{
		iMod = rand() % 3;
		if ( iMod == 0 )		dwSelectSound = dwMotionSoundID1;
		else if ( iMod == 1 )	dwSelectSound = dwMotionSoundID2;
		else					dwSelectSound = dwMotionSoundID3;
	}

	if ( dwSelectSound > 0 )
	{
		HT_CHECK( m_p3DMgr->HT_hrPlaySound( dwSelectSound ) );
	}

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrChangeAttackAnimation( HTint idObj, HTint idTribe, HTint idItem, HTint iLoop, HTint idLeftHandWeaponItem, HTint idHead, HTint idWearItem, HTint iSequnce, HTfloat fPlayTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwSelectSound;
	dwAnimID = 0;
	HTint iSelectedAnim;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		HTdword dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;

		if ( idItem <= 0 )	// 아이템을 안 들고 있으면
			dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
		else
		{
			if ( idLeftHandWeaponItem <= 0 )
			{
				// 먼저 아이템을 보고 그것의 타입을 참조하여 어떤 공격 에니를 틀 것인지 결정한다.
				if ( !m_pResMgr->HT_bGetItemType( idItem, dwItemType ) )
					dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
			}
			// 양손에 무기를 착용하고 있다면
			else
			{
				dwItemType = HT_ANISTATE_ATK_DOUBLEWEAPON;
			}
		}

		// 활공격 애니메이션인 경우 화살이 오른손에 나타나야 한다.
		// 화살 모델의 리소스 값이 14179 이다.
		if ( dwItemType == HT_ANISTATE_ATK_BOW )
		{
			CHTString strSocket( _T("Arrow") );
			this->HT_hrDetachObject( idObj, strSocket );
			this->HT_hrAttachObject( idObj, strSocket, 14179, HT_fGetModelScaleFactor( idTribe, HT_ITEM_ARROW_MODELID ) );
		}

		// 공격 동작의 경우 남녀로 구분하여 처리한다.
		HTdword dwAnimID1, dwAnimID2, dwAnimID3;
		dwAnimID1 = dwAnimID2 = dwAnimID3 = 0;
		if ( HT_IS_PC_MAN( idTribe ) )
		{
			m_pResMgr->HT_bGetManAnim1ID( dwItemType, dwAnimID1 );
			m_pResMgr->HT_bGetManAnim2ID( dwItemType, dwAnimID2 );
			m_pResMgr->HT_bGetManAnim3ID( dwItemType, dwAnimID3 );
		}
		else
		{
			m_pResMgr->HT_bGetWomAnim1ID( dwItemType, dwAnimID1 );
			m_pResMgr->HT_bGetWomAnim2ID( dwItemType, dwAnimID2 );
			m_pResMgr->HT_bGetWomAnim3ID( dwItemType, dwAnimID3 );
		}

		if ( iSequnce <= 0 )
		{
			iSelectedAnim = HT_iGet3RandomID( dwAnimID1, dwAnimID2, dwAnimID3, &dwAnimID );
		}
		else
		{
			iSelectedAnim = iSequnce;
			switch( iSelectedAnim ) 
			{
			case 1:	dwAnimID = dwAnimID1;
				break;
			case 2: dwAnimID = dwAnimID2;
				break;
			case 3: dwAnimID = dwAnimID3;
				break;
			default: dwAnimID = dwAnimID1;
				break;
			}
		}

		// Motion Sound 를 틀어주기 위해서 
		dwSelectSound = HT_dwGetPCSoundID( idTribe, (HT_ANIM_STATE)dwItemType, iSelectedAnim );

		//--------------------------------------------------------------------
		// 소켓에 붙은 모델들의 에니메이션을 세팅해 준다.
		HTdword dwSocketAnimID;
		CHTString strSocket;
		if ( idHead > 0 )
		{
			HTdword dwIDHead = HT_dwGetHeadID( idTribe, idHead );

			HTdword dwHairType;
			strSocket = _T("Hair");
			m_pResMgr->HT_bGetHairType( idHead, dwHairType );
			switch ( dwHairType ) 
			{
			case 1:
				m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
				break;
			case 2:
				m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwSocketAnimID );
				break;
			default:
				m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
				break;
			}

			this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
			m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );
		}

		HTdword dwFApronAniID, dwBApronAniID;
		dwSocketAnimID = dwFApronAniID = dwBApronAniID = 0;

		switch( iSelectedAnim ) 
		{
		case 1:
			{
				strSocket = _T("FApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManFApronAnimID1( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomFApronAnimID1( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );

				strSocket = _T("BApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManBApronAnimID1( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomBApronAnimID1( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );
			}
			break;
		case 2:
			{
				strSocket = _T("FApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManFApronAnimID2( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomFApronAnimID2( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );

				strSocket = _T("BApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManBApronAnimID2( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomBApronAnimID2( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );
			}
			break;
		case 3:
		default:
			{
				strSocket = _T("FApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManFApronAnimID3( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomFApronAnimID3( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );

				strSocket = _T("BApron");
				if ( HT_IS_PC_MAN( idTribe ) )
					m_pResMgr->HT_bGetManBApronAnimID3( dwItemType, dwSocketAnimID );
				else
					m_pResMgr->HT_bGetWomBApronAnimID3( dwItemType, dwSocketAnimID );

				this->HT_hrLoadToResPool( dwSocketAnimID, HT_FALSE );
				m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fPlayTime );
			}
			break;
		}
		//--------------------------------------------------------------------
	}
	else
	{
		return ( HT_FAIL );
	}

	this->HT_hrLoadToResPool( dwAnimID, HT_FALSE );
	m_p3DMgr->HT_hrChangeAnimation( idObj, dwAnimID, dwSelectSound, iLoop, 0.0f, fPlayTime );

	// 무기 휘두르는 소리를 낸다.
	HTdword dwItemType, dwItemSound;
	m_pResMgr->HT_bGetItemType( idItem, dwItemType );
	if ( dwItemType > 0 )
	{
		if ( iSelectedAnim == 1 )
			m_pResMgr->HT_bGetSwingSoundID1( dwItemType, dwItemSound );
		else if ( iSelectedAnim == 2 )
			m_pResMgr->HT_bGetSwingSoundID2( dwItemType, dwItemSound );
		else
			m_pResMgr->HT_bGetSwingSoundID3( dwItemType, dwItemSound );

		HTvector3 vecPos, vecOffsetPos;
		m_p3DMgr->HT_hrGetPosition( idObj, vecPos );
		m_p3DMgr->HT_hrGetOffsetPosFromMainObj( vecPos, vecOffsetPos );
		m_p3DMgr->HT_hrPlaySound( dwItemSound, 1, vecOffsetPos );
	}

	m_p3DMgr->HT_hrSetSwordWind( idObj, HT_TRUE );

	return ( HT_OK );
}

HTvoid
CHTEngineHandler::HT_vGoodMorning()
{
	if ( m_pMapSystem->HT_bIsIndoorMap() )	// 던전에서는 새소리가 안나야 한다고 한다.
	{
		return;
	}

	if ( rand() % 2 == 0 )
	{
		m_p3DMgr->HT_hrPlaySound( 33507 );	// 아침 새소리 1
	}
	else
	{
		m_p3DMgr->HT_hrPlaySound( 33508 );	// 아침 새소리 2
	}
}

HTvoid
CHTEngineHandler::HT_vGoodNight()
{
	if ( m_pMapSystem->HT_bIsIndoorMap() )	// 던전에서는 새소리가 안나야 한다고 한다.
	{
		return;
	}

	m_p3DMgr->HT_hrPlaySound( 33506 );	// 저녁 새소리
}

HTfloat
CHTEngineHandler::HT_fGetModelScaleFactor( HTint idTribe, HTdword dwModelID )
{
	HTfloat fScale = 1.0f;

	switch( idTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKScale( dwModelID, fScale );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARScale( dwModelID, fScale );
		break;
	default:
		break;
	}

	return ( fScale );
}

HTint					
CHTEngineHandler::HT_iGet3RandomID( HTdword dwID1, HTdword dwID2, HTdword dwID3, HTdword* dwID )
{
	HTint iCount = 0, iMod;
	HTdword dwSelectID = 0;
	if ( dwID1 > 0 )		iCount += 1;
	if ( dwID2 > 0 )		iCount += 2;
	if ( dwID3 > 0 )		iCount += 4;

	if ( iCount == 0 )	// 사운드가 없으면 0을 전달하여 틀지 말라고 한다.
	{
		dwSelectID = 0;
	}
	else if ( iCount == 1 )	// 
	{
		dwSelectID = dwID1;
	}
	else if ( iCount == 2 )	// 
	{
		dwSelectID = dwID2;
	}
	else if ( iCount == 4 )	// 
	{
		dwSelectID = dwID3;
	}
	else if ( iCount == 3 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectID = dwID1;
		else				dwSelectID = dwID2;
	}
	else if ( iCount == 5 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectID = dwID1;
		else				dwSelectID = dwID3;
	}
	else if ( iCount == 6 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectID = dwID2;
		else				dwSelectID = dwID3;
	}
	else if ( iCount == 7 )	// 
	{
		iMod = rand() % 3;
		if ( iMod == 0 )		dwSelectID = dwID1;
		else if ( iMod == 1 )	dwSelectID = dwID2;
		else					dwSelectID = dwID3;
	}

	*dwID = dwSelectID;

	if ( dwSelectID == dwID1 )
		return ( 1 );
	else if ( dwSelectID == dwID2 )
		return ( 2 );
	else
		return ( 3 );
}

HTint CHTEngineHandler::HT_iGetObjectOnMouse( HTint iX, HTint iY )
{
	HTfloat		fDist;						// 오브젝트의 거리를 통해 오브젝트 PICK을 하기 위한 변수들
	HTint		iObjID;
	HTRESULT	hrPicked = HT_FAIL;

	HTRay oRay;
	m_p3DMgr->HT_hrMakePickRay( iX, iY, &oRay );

	// 오브젝트들이 들어있는 맵 노드에 대해 픽을 실행한다.
	std::list<HTint> listIDPickedObjs;
	m_pMapSystem->HT_hrPick( oRay, listIDPickedObjs );

	HTfloat fClosestObjDistance = 100000.0f;

	std::list<HTint>::iterator it = listIDPickedObjs.begin();
	while ( it != listIDPickedObjs.end() )
	{
		// 오브젝트의 바운딩 박스 정보와 반직선 간의 교차 판정을 한다.
		if ( HT_SUCCEED( m_p3DMgr->HT_hrPick( &fDist, *it, (HTfloat)iX, (HTfloat)iY ) ) )
		{			
			// Map Object는 픽시키지 않는다.
			HTdword dwID = m_p3DMgr->HT_dwGetResourceID( *it );
			if ( HT_IS_OBJS( dwID ) )
			{
				++it;
				continue;
			}

			// Pick하지 말라고 부탁된 것들은 제외한다. ( 죽은 몬스터들 )
			if ( m_setDontClickObjs.find( *it ) != m_setDontClickObjs.end() )
			{
				++it;
				continue;
			}

			// 만약 메인 캐릭터일 경우에는 자기 자신이 찍히는 것을 막기 위해 픽시키지 않는다.
			if ( m_idMainCharacter != *it )
			{
				// 가장 가까운 거리에 있는 오브젝트를 선택한다.
				if ( fDist < fClosestObjDistance  && fDist>0.0f)
				{
					fClosestObjDistance = fDist;
					iObjID = *it;
					hrPicked = HT_OK;
				}
			}
		}
		++it;			
	}

	if ( HT_SUCCEED( hrPicked ) )	// PICK되지 않았으면 아이디를 찾을 필요 없으므로 체크후 아이디를 찾는다.
	{
		return ( iObjID );
	}
	// 픽이 된 오브젝트가 없다면 
	else
	{
		return ( -1 );
	}

}

HTRESULT				
CHTEngineHandler::HT_hrStartStreamSound()
{
	m_p3DMgr->HT_hrSetStreamVolume( m_fStreamVolume );
	m_p3DMgr->HT_hrStartStreamSound();
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrStartSampleSound()
{
	m_pMapSystem->HT_hrStopAmbientSounds();

	m_p3DMgr->HT_hrStartSampleSound();

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrStopStreamSound()
{
	m_bFadeoutBGM = HT_TRUE;
	m_fStreamFadeVolume = m_fStreamVolume;
	m_dwNextBGMID = 0;
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrStopSampleSound()
{
	m_p3DMgr->HT_hrStopSampleSound();
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrSetStreamVolume( HTfloat fVolume )
{
	m_p3DMgr->HT_hrSetStreamVolume( fVolume );
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrSetSampleVolume( HTfloat fVolume )
{
	m_p3DMgr->HT_hrSetSampleVolume( fVolume );
	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrChangeScreenBrightness( HTfloat fFactor )
{
	m_p3DMgr->HT_hrChangeScreenBrightness( fFactor );
	return ( HT_OK );
}

HTdword					
CHTEngineHandler::HT_dwGetPCSoundID( HTint idTribe, HT_ANIM_STATE eState, HTint iSeq )
{
	HTdword dwSoundID = 0;

	switch ( iSeq ) 
	{
	case 0:
		{
		}
		break;
	case 1:
		{
			switch( idTribe )
			{
			case HT_ID_CHARACTER_NAGA:
				m_pResMgr->HT_bGetNAGSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_YAKSA:
				m_pResMgr->HT_bGetYAKSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_ASURA:
				m_pResMgr->HT_bGetASUSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_DEVA:
				m_pResMgr->HT_bGetDEVSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_KIMNARA:
				m_pResMgr->HT_bGetKIMSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GANDHARVA:
				m_pResMgr->HT_bGetGANSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_RAKSHASA:
				m_pResMgr->HT_bGetRAKSoundID1( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GARUDA:
				m_pResMgr->HT_bGetGARSoundID1( eState, dwSoundID );
				break;
			}
		}
		break;
	case 2:
		{
			switch( idTribe )
			{
			case HT_ID_CHARACTER_NAGA:
				m_pResMgr->HT_bGetNAGSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_YAKSA:
				m_pResMgr->HT_bGetYAKSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_ASURA:
				m_pResMgr->HT_bGetASUSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_DEVA:
				m_pResMgr->HT_bGetDEVSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_KIMNARA:
				m_pResMgr->HT_bGetKIMSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GANDHARVA:
				m_pResMgr->HT_bGetGANSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_RAKSHASA:
				m_pResMgr->HT_bGetRAKSoundID2( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GARUDA:
				m_pResMgr->HT_bGetGARSoundID2( eState, dwSoundID );
				break;
			}
		}
		break;
	case 3:
		{
			switch( idTribe )
			{
			case HT_ID_CHARACTER_NAGA:
				m_pResMgr->HT_bGetNAGSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_YAKSA:
				m_pResMgr->HT_bGetYAKSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_ASURA:
				m_pResMgr->HT_bGetASUSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_DEVA:
				m_pResMgr->HT_bGetDEVSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_KIMNARA:
				m_pResMgr->HT_bGetKIMSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GANDHARVA:
				m_pResMgr->HT_bGetGANSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_RAKSHASA:
				m_pResMgr->HT_bGetRAKSoundID3( eState, dwSoundID );
				break;
			case HT_ID_CHARACTER_GARUDA:
				m_pResMgr->HT_bGetGARSoundID3( eState, dwSoundID );
				break;
			}
		}
		break;
	default:
		break;
	}

	return ( dwSoundID );
}

HTdword					
CHTEngineHandler::HT_dwGetNPCClickSoundID( HTdword dwNPCID )
{
	HTdword dwSoundID = 0;
	m_pResMgr->HT_bGetClickSoundID( dwNPCID, dwSoundID );
	return ( dwSoundID );
}

HTdword
CHTEngineHandler::HT_dwConvrtMonsterID2MonFXID( HTdword dwMonID )
{
	HTdword dwOutID;
	m_pResMgr->HT_bGetMonFXIDFromMonID( dwMonID, dwOutID );
	return dwOutID;
}

HTint					
CHTEngineHandler::HT_iGetPortalID( HTint idObj )
{
	HT_EOBJ_PROPERTY* pProperty = HT_NULL;
	m_p3DMgr->HT_hrGetProperty( idObj, &pProperty );

	if ( pProperty )
	{
		return ( pProperty->iPortalID );
	}

	return ( 0 );
}

HTRESULT
CHTEngineHandler::HT_hrSetUserSetting( CHTConfigSystem* pCfg )
{
	m_iSpecLevel = m_pUserSettings->HT_eGetSpecLevel();

	HT_hrLoadSpecValues( m_iSpecLevel, m_pCfgSpec );

	m_iScreenWidth = m_pUserSettings->HT_iGetScreenWidth();
	m_iScreenHeight = m_pUserSettings->HT_iGetScreenHeight();
	m_iScreenColorDepth = m_pUserSettings->HT_iGetScreenColorDepth();

	switch( m_pUserSettings->HT_eGetShadowType() ) 
	{
	case HT_OPT_REALTIMESHADOW:
		m_bUseRTShadow = HT_TRUE;
		break;
	default:
		m_bUseRTShadow = HT_FALSE;
		break;
	}

	switch ( m_pUserSettings->HT_eGetCameraRange() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("CamFar"), &m_fCameraFarZ );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CamFar"), &m_fCameraFarZ );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CamFar"), &m_fCameraFarZ );
		break;
	default:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CamFar"), &m_fCameraFarZ );
		break;
	}

	switch ( m_pUserSettings->HT_eGetObjectRange() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("GrassArea"), &m_fGrassarea );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SMObjArea"), &m_fLODDistanceFarSM );
		break;
	default:
		break;
	}

	switch( m_pUserSettings->HT_eGetModelDetail() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD3"), &m_fCharLODDistance3 );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CharLOD3"), &m_fCharLODDistance3 );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CharLOD3"), &m_fCharLODDistance3 );
		break;
	default:
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD1"), &m_fCharLODDistance1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD2"), &m_fCharLODDistance2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("CharLOD3"), &m_fCharLODDistance3 );
		break;
	}

	switch( m_pUserSettings->HT_eGetHeightMapDetail() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODDetail"), &m_fTerrainLODDetail );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODDetail"), &m_fTerrainLODDetail );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODDetail"), &m_fTerrainLODDetail );
		break;
	default:
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODDetail"), &m_fTerrainLODDetail );
		break;
	}

	switch( m_pUserSettings->HT_eGetObjectRange() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODFar"), &m_fLODDistanceFar );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("LODFar"), &m_fLODDistanceFar );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("LODFar"), &m_fLODDistanceFar );
		break;
	default:
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow1"), &m_fLODDistanceLow1 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow2"), &m_fLODDistanceLow2 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODLow3"), &m_fLODDistanceLow3 );
		pCfg->HT_hrGetValue( _T("LOW"), _T("LODFar"), &m_fLODDistanceFar );
		break;
	}

	switch( m_pUserSettings->HT_eGetFXRange() ) 
	{
	case HT_OPT_LOW:
		pCfg->HT_hrGetValue( _T("LOW"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;
	case HT_OPT_MEDIUM:
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("MEDIUM"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;
	case HT_OPT_HIGH:
		pCfg->HT_hrGetValue( _T("HIGH"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("HIGH"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;
	default:
		pCfg->HT_hrGetValue( _T("LOW"), _T("CamJitterVisibleDistance"), &m_fFXCamJitterVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteSystemVisibleDistance"), &m_fFXSpriteSystemVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SpriteVisibleDistance"), &m_fFXSpriteVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("SoundVisibleDistance"), &m_fFXSoundVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("ModelVisibleDistance"), &m_fFXModelVisibleDistance );
		pCfg->HT_hrGetValue( _T("LOW"), _T("DynaLightVisibleDistance"), &m_fFXDynaLightVisibleDistance );
		break;
	}

	switch( m_pUserSettings->HT_eGetTextureDetail() ) 
	{
	case HT_OPT_LOW:
		m_iTextureDetailLevel = 1;
		m_nMaxModelCount = 30;
		break;
	case HT_OPT_MEDIUM:
		m_iTextureDetailLevel = 2;
		m_nMaxModelCount = 40;
		break;
	case HT_OPT_HIGH:
		m_iTextureDetailLevel = 3;
		m_nMaxModelCount = 60;
		break;
	default:
		m_iTextureDetailLevel = 1;
		m_nMaxModelCount = 30;
		break;
	}

	//	m_nMaxModelCount = m_pUserSettings->HT_iGetMaxModelCount();		// TODO

	switch( m_pUserSettings->HT_eGet3DSoundProvider() ) 
	{
	case HT_OPT_MILES:
		m_str3DProvider = _T("Miles Fast 2D Positional Audio");
		break;
	case HT_OPT_EAX2:
		m_str3DProvider = _T("Creative Labs EAX 2 (TM)");
		break;
	case HT_OPT_DOLBYSROUND:
		m_str3DProvider = _T("Dolby Surround");
		break;
	case HT_OPT_DIRECTSOUND:
		m_str3DProvider = _T("DirectSound3D Hardware Support");
		break;
	default:
		m_str3DProvider = _T("Miles Fast 2D Positional Audio");
		break;
	}

	switch( m_pUserSettings->HT_eGetSpeakerType() ) 
	{
	case HT_OPT_2SPEAKER:
		m_iSpeakerType = AIL_3D_2_SPEAKER;
		break;
	case HT_OPT_HEADPHONE:
		m_iSpeakerType = AIL_3D_HEADPHONE;
		break;
	case HT_OPT_4SPEAKER:
		m_iSpeakerType = AIL_3D_4_SPEAKER;
		break;
	case HT_OPT_51SPEAKER:
		m_iSpeakerType = AIL_3D_51_SPEAKER;
		break;
	case HT_OPT_71SPEAKER:
		m_iSpeakerType = AIL_3D_71_SPEAKER;
		break;
	default:
		m_iSpeakerType = AIL_3D_2_SPEAKER;
		break;
	}

	return ( HT_OK );
}

HTdword					
CHTEngineHandler::HT_dwGetResourceID( HTint idObj )
{
	return ( m_p3DMgr->HT_dwGetResourceID( idObj ) );
}

HTRESULT				
CHTEngineHandler::HT_hrLoadMapObjsInitial( HTvector3& vecPos )
{
	//-----------------------------------------------------------------
	// 로딩시 화면이 검으면 좀 그렇다.
	///////////////////////////////////////////////////////
	//	여기에 로딩이미지가 들어간다.
	///////////////////////////////////////////////////////
	m_iLoadTimes++;


	std::set<HTint> setToLoad;
	std::set<HTint> setToUnload;
	std::set<HTint> setToCreate;
	std::set<HTint> setToDestroy;
	std::set<HTint>::iterator it;

	m_pMapSystem->HT_hrGetIDToLoad( vecPos, m_fCameraFarZ, setToLoad, setToUnload, setToCreate, setToDestroy );

	// Destroy!
	it = setToDestroy.begin();
	while ( it != setToDestroy.end() )
	{
		std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itIDs = m_pMapSystem->m_mapSaveObjs.find( *it );
		if ( itIDs != m_pMapSystem->m_mapSaveObjs.end() && itIDs->second )
		{
			if ( itIDs->second->idDayFX > 0 )	this->HT_hrStopSFX( itIDs->second->idDayFX );
			if ( itIDs->second->idNightFX > 0 )	this->HT_hrStopSFX( itIDs->second->idNightFX );
			HT_vDestroyObject( itIDs->second->idRenewal, 33 );
			itIDs->second->idRenewal = 0;
		}
		it++;
	}

	// Unload!
	it = setToUnload.begin();
	while ( it != setToUnload.end() )
	{
		m_p3DMgr->HT_hrUnLoadObject( *it );

		std::map<HTdword,HTbool>::iterator itLON = m_mapLoadedOrNot.find( *it );
		if ( itLON != m_mapLoadedOrNot.end() )
		{
			itLON->second = HT_FALSE;
		}

		it++;
	}

	// Load!
	CHTString strFileName;
	it = setToLoad.begin();
	while ( it != setToLoad.end() )
	{
		if ( m_pObjResMgr->HT_bGetFileName( *it, strFileName ) )
		{
			m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, *it, strFileName );

			std::map<HTdword,HTbool>::iterator itLON = m_mapLoadedOrNot.find( *it );
			if ( itLON != m_mapLoadedOrNot.end() )
			{
				itLON->second = HT_TRUE;
			}
			else
			{
				m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( *it, HT_TRUE ) );
			}
		}
		it++;
	}

	// Create!
	HT_EOBJ_CREATEPARAM modelParam;

	m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strObjModel, 
		m_oResourcePath.strObjTexture );

	modelParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
	modelParam.byForWhat = HT_EOBJ_FOR_MAP;
	modelParam.clrDiffuse = m_clrDiffuseObjs;
	modelParam.clrAmbient = m_clrAmbientObjs;
	modelParam.clrEmissive = m_clrEmissiveObjs;
	modelParam.clrSpecular = m_clrSpecularObjs;
	modelParam.fSizePerGrid = 1.0f;	// fog enable

	HTint idObj;

	it = setToCreate.begin();
	while ( it != setToCreate.end() )
	{
		std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itIDs = m_pMapSystem->m_mapSaveObjs.find( *it );
		if ( itIDs != m_pMapSystem->m_mapSaveObjs.end() && itIDs->second )
		{
			modelParam.dwID = itIDs->second->dwResID;
			modelParam.matTransform = itIDs->second->matTransform;
			modelParam.vecPosition = HTvector3( itIDs->second->matTransform._41, itIDs->second->matTransform._42, itIDs->second->matTransform._43 );
			memcpy( &modelParam.oProperty, &itIDs->second->oProperty, sizeof(HT_EOBJ_PROPERTY) );

			if ( HT_FAILED( m_p3DMgr->HT_hrCreateObject( &idObj, &modelParam ) ) )
			{
				if ( m_pObjResMgr->HT_bGetFileName( modelParam.dwID, modelParam.strFileName ) && HT_SUCCEED( m_p3DMgr->HT_hrCreateObject( &idObj, &modelParam ) ) )
				{
				}
				else
				{
					it++;
					continue;
				}
			}

			itIDs->second->idRenewal = idObj;

			if (modelParam.oProperty.iObjType==_OBJECT_TYPE_GRASS)
				//if ( HT_IS_GRASS( modelParam.dwID ) )
			{
				m_pMapSystem->HT_hrInsertGrassObject( idObj, itIDs->second->vectorNodes );
			}
			else if (modelParam.oProperty.iObjType==_OBJECT_TYPE_SM)
				//else if ( HT_IS_SMOBJ( modelParam.dwID ) )
			{
				m_pMapSystem->HT_hrInsertSMObject( idObj, itIDs->second->vectorNodes );
			}
			else
			{
				m_pMapSystem->HT_hrInsertObject( idObj, itIDs->second->vectorNodes );
			}

			// 지형오브젝트가 만일 효과가 달려있다면 효과를 틀어줘라.
			HTint idFX;
			HTdword dwDayFXID = 0, dwNightFXID = 0;
			CHTString strFX;

			itIDs->second->idDayFX = 0;
			itIDs->second->idNightFX = 0;

			dwDayFXID = itIDs->second->oProperty.iDayFXID;
			dwNightFXID = itIDs->second->oProperty.iNightFXID;

			if ( dwDayFXID > 0 && dwNightFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_ALWAYS );
				itIDs->second->idDayFX = idFX;
				itIDs->second->idNightFX = idFX;
			}
			else if ( dwDayFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_DAY );
				itIDs->second->idDayFX = idFX;
			}
			else if ( dwNightFXID > 0 )
			{
				this->HT_hrStartFieldFX( &idFX, dwNightFXID, idObj, HT_TRUE, HT_FX_WHEN_NIGHT );
				itIDs->second->idNightFX = idFX;
			}
		}
		it++;
	}

	if ( m_dwCurrentMapID != 40100 )	// IntroMap이 아닐 경우
		HT_hrStopIntroBGM();

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrLoadMapResource( HTdword dwID )
{
	CHTString strFile;

	if ( m_pResMgr->HT_bGetFileName( dwID, strFile ) )
	{
		return ( m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, dwID, strFile ) );
	}

	return ( HT_FAIL );
}

HTRESULT				
CHTEngineHandler::HT_hrLoadMapObjsDynamic( HTvector3& vecPos )
{
	std::set<HTint> setToLoad;
	std::set<HTint> setToCreate;
	std::set<HTint> setToUnload;
	std::set<HTint> setToDestroy;
	std::set<HTint>::iterator it;

	m_pMapSystem->HT_hrGetIDToLoad( vecPos, m_fCameraFarZ, setToLoad, setToUnload, setToCreate, setToDestroy );

	m_setToLoad.insert( setToLoad.begin(), setToLoad.end() );
	m_setToCreate.insert( setToCreate.begin(), setToCreate.end() );

	// Destroy!
	it = setToDestroy.begin();
	while ( it != setToDestroy.end() )
	{
		std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itIDs = m_pMapSystem->m_mapSaveObjs.find( *it );
		if ( itIDs != m_pMapSystem->m_mapSaveObjs.end() && itIDs->second )
		{
			if ( itIDs->second->idDayFX > 0 )	this->HT_hrStopSFX( itIDs->second->idDayFX );
			if ( itIDs->second->idNightFX > 0 )	this->HT_hrStopSFX( itIDs->second->idNightFX );
			HT_vDestroyObject( itIDs->second->idRenewal, 34 );
			itIDs->second->idRenewal = 0;
		}
		it++;
	}

	// Unload!
	it = setToUnload.begin();
	while ( it != setToUnload.end() )
	{
		m_p3DMgr->HT_hrUnLoadObject( *it );

		std::map<HTdword,HTbool>::iterator itLON = m_mapLoadedOrNot.find( *it );
		if ( itLON != m_mapLoadedOrNot.end() )
		{
			itLON->second = HT_FALSE;
		}

		it++;
	}

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrLoadingProcess()
{
	// 로딩 예약 되어있는 것들을 한번에 하나씩 로드를 한다.
	std::set<HTint>::iterator it = m_setToLoad.begin();
	if ( it != m_setToLoad.end() )
	{
		CHTString strFileName;
		if ( m_pObjResMgr->HT_bGetFileName( *it, strFileName ) )
		{
			m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_RIGIDMODEL, *it, strFileName );

			std::map<HTdword,HTbool>::iterator itLON = m_mapLoadedOrNot.find( *it );
			if ( itLON != m_mapLoadedOrNot.end() )
			{
				itLON->second = HT_TRUE;
			}
			else
			{
				m_mapLoadedOrNot.insert( std::map<HTdword,HTbool>::value_type( *it, HT_TRUE ) );
			}
		}
		m_setToLoad.erase( it );
	}

	// 로딩을 다 했으면 생성할 것들을 생성해주자.
	if ( m_setToLoad.empty() && !m_setToCreate.empty() )
	{
		HT_EOBJ_CREATEPARAM modelParam;

		m_p3DMgr->HT_vSetResourcePath( m_oResourcePath.strObjModel, 
			m_oResourcePath.strObjTexture );

		modelParam.eObjType = HT_EOBJTYPE_RIGIDMODEL;
		modelParam.byForWhat = HT_EOBJ_FOR_MAP;
		modelParam.clrDiffuse = m_clrDiffuseObjs;
		modelParam.clrAmbient = m_clrAmbientObjs;
		modelParam.clrEmissive = m_clrEmissiveObjs;
		modelParam.clrSpecular = m_clrSpecularObjs;
		modelParam.fSizePerGrid = 1.0f;	// fog enable

		HTint idObj;
		it = m_setToCreate.begin();
		while ( it != m_setToCreate.end() )
		{
			std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itIDs = m_pMapSystem->m_mapSaveObjs.find( *it );
			if ( itIDs != m_pMapSystem->m_mapSaveObjs.end() && itIDs->second )
			{
				// 로드가 안 되어 있는 리소스를 로드할 순 없다.
				std::map<HTdword,HTbool>::iterator itLON = m_mapLoadedOrNot.find( itIDs->second->dwResID );
				if ( itLON != m_mapLoadedOrNot.end() )
				{
					if ( !itLON->second )
					{
						it++;
						continue;
					}
				}
				else
				{
					it++;
					continue;
				}

				// 이미 생성된 것은 스킵한다.
				if ( itIDs->second->idRenewal > 0 )		
				{
					it = m_setToCreate.erase( it );
				}
				else
				{
					modelParam.dwID = itIDs->second->dwResID;
					modelParam.matTransform = itIDs->second->matTransform;
					modelParam.vecPosition = HTvector3( itIDs->second->matTransform._41, itIDs->second->matTransform._42, itIDs->second->matTransform._43 );
					memcpy( &modelParam.oProperty, &itIDs->second->oProperty, sizeof(HT_EOBJ_PROPERTY) );

					m_p3DMgr->HT_hrCreateObject( &idObj, &modelParam );

					itIDs->second->idRenewal = idObj;

					if (modelParam.oProperty.iObjType==_OBJECT_TYPE_GRASS)
						//if ( HT_IS_GRASS( modelParam.dwID ) )
					{
						m_pMapSystem->HT_hrInsertGrassObject( idObj, itIDs->second->vectorNodes );
					}
					//else if ( HT_IS_SMOBJ( modelParam.dwID ) )
					else if ( modelParam.oProperty.iObjType==_OBJECT_TYPE_SM)
					{
						m_pMapSystem->HT_hrInsertSMObject( idObj, itIDs->second->vectorNodes );
					}
					else
					{
						m_pMapSystem->HT_hrInsertObject( idObj, itIDs->second->vectorNodes );
					}

					// 지형오브젝트가 만일 효과가 달려있다면 효과를 틀어줘라.
					HTint idFX;
					HTdword dwDayFXID = 0, dwNightFXID = 0;
					CHTString strFX;

					itIDs->second->idDayFX = 0;
					itIDs->second->idNightFX = 0;
					dwDayFXID = itIDs->second->oProperty.iDayFXID;
					dwNightFXID = itIDs->second->oProperty.iNightFXID;

					if ( dwDayFXID > 0 && dwNightFXID > 0 )
					{
						this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_ALWAYS );
						itIDs->second->idDayFX = idFX;
						itIDs->second->idNightFX = idFX;
					}
					else if ( dwDayFXID > 0 )
					{
						this->HT_hrStartFieldFX( &idFX, dwDayFXID, idObj, HT_TRUE, HT_FX_WHEN_DAY );
						itIDs->second->idDayFX = idFX;
					}
					else if ( dwNightFXID > 0 )
					{
						this->HT_hrStartFieldFX( &idFX, dwNightFXID, idObj, HT_TRUE, HT_FX_WHEN_NIGHT );
						itIDs->second->idNightFX = idFX;
					}

					// 만약 요새전 맵이고, 요새전 깃발이 나와야 한다면 여기서 처리한다.
					// 대략 맵의 중심이 3160, 3160 에 있는 격투장이므로 이를 기준으로 4개의 성을 구분한다.
					if ( m_dwCurrentMapID == HT_FORTWAR_MAP_ID )
					{
						if ( modelParam.dwID == HT_FORTWAR_GUILD_FLAG_RESID )
						{
							HTdword dwGuildMark = 0;
							if ( modelParam.vecPosition.x > 3160.0f && modelParam.vecPosition.x < 7000.0f
								&& modelParam.vecPosition.z > 3160.0f && modelParam.vecPosition.z < 7000.0f )
							{	// 위, 우측 : UR
								if ( m_oGuildCastleInfo.dwGMarkUR != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkUR;
								else
								{
									m_p3DMgr->HT_hrUnset2GuildMark( idObj );
								}
							}

							if ( modelParam.vecPosition.x > 0.0f && modelParam.vecPosition.x < 3160.0f
								&& modelParam.vecPosition.z > 3160.0f && modelParam.vecPosition.z < 7000.0f )
							{	// 위, 좌측 : UL
								if ( m_oGuildCastleInfo.dwGMarkUL != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkUL;
								else
								{
									m_p3DMgr->HT_hrUnset2GuildMark( idObj );
								}
							}

							if ( modelParam.vecPosition.x > 3160.0f && modelParam.vecPosition.x < 7000.0f
								&& modelParam.vecPosition.z > 0.0f && modelParam.vecPosition.z < 3160.0f )
							{	// 아래, 우측 : LR
								if ( m_oGuildCastleInfo.dwGMarkLR != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkLR;
								else
								{
									m_p3DMgr->HT_hrUnset2GuildMark( idObj );
								}
							}

							if ( modelParam.vecPosition.x > 0.0f && modelParam.vecPosition.x < 3160.0f
								&& modelParam.vecPosition.z > 0.0f && modelParam.vecPosition.z < 3160.0f )
							{	// 아래, 좌측 : LL
								if ( m_oGuildCastleInfo.dwGMarkLL != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkLL;
								else
								{
									m_p3DMgr->HT_hrUnset2GuildMark( idObj );
								}
							}

							if ( dwGuildMark > 0 )
							{
								HTdword dwGuildEmblem	= (dwGuildMark & 0x000000FF);
								HTdword dwGuildTitle	= (dwGuildMark & 0x0000FF00) >> 8;
								HTdword dwGuildColor	= (dwGuildMark & 0x00FF0000) >> 16;

								if ( dwGuildEmblem < 1 || dwGuildEmblem > 72 || dwGuildTitle < 1 || dwGuildTitle > 84 || dwGuildColor < 1 || dwGuildColor > 72 )
								{
								}
								else
								{
									CHTString strGuildTitle;
									HTdword dwColor;
									m_pResMgr->HT_bGetGuildTitleTex( dwGuildTitle + HT_ID_GUILDMARK_TITLE_START - 1, strGuildTitle );
									m_pResMgr->HT_bGetGuildEmblemDWColor( dwGuildColor + HT_ID_GUILDMARK_COLOR_START - 1, dwColor );

									//m_p3DMgr->HT_hrAttachGuildMark( idParent, dwGuildEmblem, strGuildTitle, dwColor, 7.5f, 3.0f );
									m_p3DMgr->HT_hrSet2GuildMark( idObj, dwGuildEmblem, strGuildTitle, dwColor );
								}							
							}
						}
					}

					it = m_setToCreate.erase( it );
				}
			}
			else
			{
				// TODO
				it = m_setToCreate.erase( it );
			}
		}
	}

	// Resource Pool에 있는 것들에 대한 처리를 한다.
	HTfloat fCurrentTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );
	std::map<HTdword,HTfloat>::iterator itWU = m_mapWaitUnloads.begin();
	while ( itWU != m_mapWaitUnloads.end() )
	{
		if ( fCurrentTime - itWU->second > m_fUnloadWaitTime )
		{
			HT_RES_POOL_DATA* pData = HT_NULL;
			std::map<HTdword,HT_RES_POOL_DATA*>::iterator itRP = m_mapResPools.find( itWU->first );
			if ( itRP != m_mapResPools.end() )
			{
				pData = (itRP->second);
				if ( pData )
				{
					if ( pData->iRefCount <= 0 )
					{
						HT_DELETE( pData );
						m_mapResPools.erase( itRP );
						m_p3DMgr->HT_hrUnLoadObject( itWU->first );
					}
				}
				itWU = m_mapWaitUnloads.erase( itWU );
			}
			else
				itWU++;
		}
		else
			itWU++;
	}

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrBlendAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop, HTfloat fTime, CHTString* pstrBone )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTint iMod;

	HTdword dwAnimID, dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3;
	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;
	HTint iSelectedAnim;

	if ( HT_IS_CHARACTER( dwID ) )
	{
		// 공격 동작의 경우 남녀로 구분하여 처리한다.
		if ( eState >= HT_ANISTATE_ATK_IRON_ONEHAND_SWORD && eState < HT_ANISTATE_ATK_END )
		{
			HTdword dwAnimID1, dwAnimID2, dwAnimID3;
			dwAnimID1 = dwAnimID2 = dwAnimID3 = 0;
			if ( HT_IS_PC_MAN( dwID ) )
			{
				m_pResMgr->HT_bGetManAnim1ID( eState, dwAnimID1 );
				m_pResMgr->HT_bGetManAnim2ID( eState, dwAnimID2 );
				m_pResMgr->HT_bGetManAnim3ID( eState, dwAnimID3 );
			}
			else
			{
				m_pResMgr->HT_bGetWomAnim1ID( eState, dwAnimID1 );
				m_pResMgr->HT_bGetWomAnim2ID( eState, dwAnimID2 );
				m_pResMgr->HT_bGetWomAnim3ID( eState, dwAnimID3 );
			}

			iSelectedAnim = HT_iGet3RandomID( dwAnimID1, dwAnimID2, dwAnimID3, &dwAnimID );
		}
		else	// 일반 동작의 경우 종족별로 구분하여 처리한다.
		{
			switch( dwID )
			{
			case HT_ID_CHARACTER_NAGA:
				m_pResMgr->HT_bGetNAGID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_YAKSA:
				m_pResMgr->HT_bGetYAKID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_ASURA:
				m_pResMgr->HT_bGetASUID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_DEVA:
				m_pResMgr->HT_bGetDEVID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_KIMNARA:
				m_pResMgr->HT_bGetKIMID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_GANDHARVA:
				m_pResMgr->HT_bGetGANID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_RAKSHASA:
				m_pResMgr->HT_bGetRAKID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_GARUDA:
				m_pResMgr->HT_bGetGARID( eState, dwAnimID );
				break;
			case HT_ID_CHARACTER_GM:
				if ( eState == HT_ANISTATE_IDL )
					dwAnimID = 50001; 
				else if ( eState == HT_ANISTATE_WLK )
					dwAnimID = 50003; 
				else if ( eState == HT_ANISTATE_RUN )
					dwAnimID = 50003; 
				else
					dwAnimID = 50002; 
				break;
			}
		}

		switch( dwID )
		{
		case HT_ID_CHARACTER_NAGA:
			m_pResMgr->HT_bGetNAGSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetNAGSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetNAGSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_YAKSA:
			m_pResMgr->HT_bGetYAKSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetYAKSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetYAKSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_ASURA:
			m_pResMgr->HT_bGetASUSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetASUSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetASUSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_DEVA:
			m_pResMgr->HT_bGetDEVSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetDEVSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetDEVSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_KIMNARA:
			m_pResMgr->HT_bGetKIMSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetKIMSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetKIMSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			m_pResMgr->HT_bGetGANSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetGANSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetGANSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			m_pResMgr->HT_bGetRAKSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetRAKSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetRAKSoundID3( eState, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_GARUDA:
			m_pResMgr->HT_bGetGARSoundID1( eState, dwMotionSoundID1 );
			m_pResMgr->HT_bGetGARSoundID2( eState, dwMotionSoundID2 );
			m_pResMgr->HT_bGetGARSoundID3( eState, dwMotionSoundID3 );
			break;
		}
		// 소켓에 붙은 모델들의 에니메이션은 무시한다.
	}
	else if ( HT_IS_NPC( dwID ) )
	{
		// 대장장이의 집게의 경우, 평상시는 안 보이다가, 아이들 동작( 집게를 내려침 )을 할때는 보여야 한다.
		CHTString strWeapon( _T("Weaponmake_item") );	
		switch( eState ) 
		{
		case HT_ANISTATE_STD:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetSTDAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_WLK:
			m_p3DMgr->HT_hrHideMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetMOVAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_IDL:
			m_p3DMgr->HT_hrShowMesh( idObj, strWeapon );
			m_pResMgr->HT_bGetIDLAniID( dwID, dwAnimID );
			break;
		default:
			break;
		}
	}
	else if ( HT_IS_MONSTER( dwID ) )	
	{
		HTdword dwFXMonID;
		m_pResMgr->HT_bGetMonFXID( dwID, dwFXMonID );
		if ( HT_IS_FXMON( dwFXMonID ) )
		{
			switch( eState ) 
			{
			case HT_ANISTATE_WLK:
				m_pResMgr->HT_bGetMonWalkSoundID( dwFXMonID, dwMotionSoundID1 );
				break;
			case HT_ANISTATE_IDL:
				m_pResMgr->HT_bGetMonIdleSoundID( dwFXMonID, dwMotionSoundID1 );
				break;
			case HT_ANISTATE_RUN:
				m_pResMgr->HT_bGetMonRunSoundID( dwFXMonID, dwMotionSoundID1 );
				break;
			case HT_ANISTATE_ATK_1:
				m_pResMgr->HT_bGetMonAttackSoundID1( dwFXMonID, dwMotionSoundID1 );
				m_pResMgr->HT_bGetMonAttackSoundID2( dwFXMonID, dwMotionSoundID2 );
				break;
			case HT_ANISTATE_ATK_2:
				m_pResMgr->HT_bGetMonAttackSoundID1( dwFXMonID, dwMotionSoundID1 );
				m_pResMgr->HT_bGetMonAttackSoundID2( dwFXMonID, dwMotionSoundID2 );
				break;
			case HT_ANISTATE_HIT:
				m_pResMgr->HT_bGetMonHitSoundID( dwFXMonID, dwMotionSoundID1 );
				m_pResMgr->HT_bGetMonHit2SoundID( dwFXMonID, dwMotionSoundID2 );
				break;
			case HT_ANISTATE_DIE:
				m_pResMgr->HT_bGetMonDieSoundID( dwFXMonID, dwMotionSoundID1 );
				break;
			default:
				break;
			}
		}

		switch( eState ) 
		{
		case HT_ANISTATE_STD:
			m_pResMgr->HT_bGetSTDAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_WLK:
			m_pResMgr->HT_bGetWLKAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_IDL:
			m_pResMgr->HT_bGetIDLAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_RUN:
			m_pResMgr->HT_bGetRUNAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_ATK_1:
			m_pResMgr->HT_bGetATK1AniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_ATK_2:
			m_pResMgr->HT_bGetATK2AniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_HIT:
			m_pResMgr->HT_bGetHITAniID( dwID, dwAnimID );
			break;
		case HT_ANISTATE_DIE:
			m_pResMgr->HT_bGetDIEAniID( dwID, dwAnimID );
			break;
		default:
			break;
		}
	}
	else
	{
		return ( HT_FAIL );
	}

	// 만약 사운드가 여러개가 나왔다면 그중에서 랜덤으로 하나를 선택한다.
	// 여기서 쓰이는 사운드의 랜덤은 클라이언트 사이에 동기화가 되지 않아도 된다고 가정한다.
	HTint iSoundCount = 0;
	HTdword dwSelectSound = 0;
	if ( dwMotionSoundID1 > 0 )		iSoundCount += 1;
	if ( dwMotionSoundID2 > 0 )		iSoundCount += 2;
	if ( dwMotionSoundID3 > 0 )		iSoundCount += 4;

	if ( iSoundCount == 0 )	// 사운드가 없으면 0을 전달하여 틀지 말라고 한다.
	{
		dwSelectSound = 0;
	}
	else if ( iSoundCount == 1 )	// 
	{
		dwSelectSound = dwMotionSoundID1;
	}
	else if ( iSoundCount == 2 )	// 
	{
		dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 4 )	// 
	{
		dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 3 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 5 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 6 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID2;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 7 )	// 
	{
		iMod = rand() % 3;
		if ( iMod == 0 )		dwSelectSound = dwMotionSoundID1;
		else if ( iMod == 1 )	dwSelectSound = dwMotionSoundID2;
		else					dwSelectSound = dwMotionSoundID3;
	}

	m_p3DMgr->HT_hrBlendAnimation( idObj, dwAnimID, dwSelectSound, iLoop, fTime, pstrBone );

	return ( HT_OK );
}

HTint
CHTEngineHandler::HT_iGetItemCount( HTbool bIsPC, CHTString& strTable )
{
	if ( bIsPC )	return (HTint)m_pFXPCResMgr->HT_nGetItemCount( strTable );
	else			return (HTint)m_pFXMAPResMgr->HT_nGetItemCount( strTable );
}

HTdword
CHTEngineHandler::HT_dwGetIDByIndex( HTbool bIsPC, CHTString& strTable, HTuint idxRow )
{
	if ( bIsPC )	return m_pFXPCResMgr->HT_dwGetIDByIndex( strTable, idxRow );
	else			return m_pFXMAPResMgr->HT_dwGetIDByIndex( strTable, idxRow );
}

HTRESULT
CHTEngineHandler::HT_hrGetFXName( HTdword dwFXID, CHTString* pstrFX )
{
	HTdword dwCategory = 0, dwWhereAttachType = 0, dwPriority = 10;

	if ( HT_IS_FXNAME_PCSKILL( dwFXID ) || HT_IS_FXNAME_PCEFFECT( dwFXID ) )
	{
		m_pFXPCResMgr->HT_bGetFX( dwFXID, *pstrFX, dwCategory, dwWhereAttachType, dwPriority );
		return HT_OK;
	}
	else if ( HT_IS_FXNAME_MONSTERSKILL( dwFXID ) || HT_IS_FXNAME_MONSTERETC( dwFXID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFXID, *pstrFX, dwWhereAttachType, dwPriority );
		return HT_OK;
	}
	else if ( HT_IS_FXNAME_FIELDEFFECT( dwFXID ) )
	{
		m_pFXMAPResMgr->HT_bGetFX( dwFXID, *pstrFX, dwWhereAttachType, dwPriority );
		return HT_OK;
	}
	else if ( HT_IS_PCSKILL( dwFXID ) )
	{
		m_pFXPCResMgr->HT_bGetSkillName( dwFXID, *pstrFX );
		return HT_OK;
	}
	else return HT_FAIL;
}

HTbool
CHTEngineHandler::HT_bGetItemName( HTdword dwID, CHTString* pstrName )
{
	if ( m_pResMgr && pstrName ) return m_pResMgr->HT_bGetName( dwID, *pstrName );
	else return HT_FALSE;
}

HTint
CHTEngineHandler::HT_iGetItemCount( CHTString& strTable )
{
	if ( m_pResMgr ) return (HTint)m_pResMgr->HT_nGetItemCount( strTable );
	else return -1;
}

HTdword
CHTEngineHandler::HT_dwGetIDByIndex( CHTString& strTable, HTint i )
{
	if ( m_pResMgr ) return m_pResMgr->HT_dwGetIDByIndex( strTable, (HTuint)i );
	else return -1;
}

HTRESULT
CHTEngineHandler::HT_hrSetSoundRoomType( HTint iType )
{
	m_p3DMgr->HT_hrSetSoundRoomType( iType );

	return ( HT_OK );
}

HTdword				
CHTEngineHandler::HT_dwGetPCAniID( HTint idTribe, HT_ANIM_STATE eState )
{
	HTdword dwAnimID = 0;

	switch( idTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GM:
		if ( eState == HT_ANISTATE_IDL )
			dwAnimID = 50001; 
		else if ( eState == HT_ANISTATE_WLK )
			dwAnimID = 50003; 
		else if ( eState == HT_ANISTATE_RUN )
			dwAnimID = 50003; 
		else
			dwAnimID = 50002; 
		break;
	}

	return ( dwAnimID );
}

HTRESULT				
CHTEngineHandler::HT_hrUnarmWeapon( HTint idObj, HTint idTribe, HTint idItem, HTint idShield, HTint idLeftHandWeaponItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( !HT_IS_ITEM( idItem ) && !HT_IS_ITEM( idItem ) ) return ( HT_FAIL );

	// 글러브일 경우는 해제하지 않는다. -> 이제는 등에 단다
	//if ( HT_IS_ITEM_GLOVE( idItem ) )
	//{
	//	return ( HT_OK );
	//}

	// 양손 무기를 장착하게 되는 경우 왼손의 무기, 단검만 찰 수 있다.
	HTdword dwType;
	if ( idLeftHandWeaponItem > 0  && m_pResMgr->HT_bGetItemType( idLeftHandWeaponItem, dwType ) )
	{
		if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD )
		{
			CHTString strSocket;
			// 만약 왼손에 뭔가 달려 있다면, 등판에 뭔가 달려 있다면, 떼어준다.
			strSocket = _T("LeftSSW");
			HT_hrDetachObject( idObj, strSocket );
			strSocket = _T("HWeapon02");
			HT_hrDetachObject( idObj, strSocket );

			HTdword dwSocketID;
			m_pResMgr->HT_bGetSocketModelID( idLeftHandWeaponItem, dwSocketID );

			// 이제 달아준다. strSocket = _T("LeftSSW");
			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );

			HTdword dwSocketTexID;
			m_pResMgr->HT_bGetSocketTexID( idLeftHandWeaponItem, dwSocketTexID );

			CHTString strFile;
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
		}
	}

	if ( HT_IS_ITEM_WEAPON( idItem ) )
	{
		HTdword dwSocketID, dwItemType;
		CHTString strSocket, strTmp;
		m_pResMgr->HT_bGetSocketModelID( idItem, dwSocketID );
		m_pResMgr->HT_bGetItemType( idItem, dwItemType );

		strSocket = _T("RightHand");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("LeftHand");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("RightClaw");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("LeftClaw");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Bow");
		HT_hrDetachObject( idObj, strSocket );
		// 화살통은 원래 달려있는 그 위치를 그대로 유지한다.
		//strSocket = _T("Arrow_Box");
		//HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("Arrow");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon01");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon02");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_1");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon04_2");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon05");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("HWeapon01");
		HT_hrDetachObject( idObj, strSocket );

		if ( dwSocketID )
		{
			HTdword dwSocketTexID;
			CHTString strFile;
			switch ( dwItemType )
			{
				// 단검
			case HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD :		// 902 철단검
				{
					strSocket = _T("HWeapon01");
					HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
					m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
					m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
				}	break;

				// 한손 무기
			case HT_ANISTATE_ATK_IRON_ONEHAND_SWORD :			// 901 철한손검
			case HT_ANISTATE_ATK_IRON_ONEHAND_AXE :				// 903 철한손도끼
			case HT_ANISTATE_ATK_IRON_ONEHAND_MACE :			// 904 철한손둔기
				{
					m_pResMgr->HT_bGetSocketName( idItem, strSocket );
					if ( strSocket == _T("RightClaw") )
					{	// 파타와 같은 무기는 일반 무기 장착이 아니라, 장갑형 무기 장착 소켓을 사용한다.
						strSocket = _T("BWeapon04_1");
						HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
						m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
						m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
						m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
					}
					else
					{
						strSocket = _T("BWeapon01");
						HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
						m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
						m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
						m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
					}
				}	break;

				// 두손 무기
			case HT_ANISTATE_ATK_IRON_TWOHAND_SPEAR :			// 906 철양손창
			case HT_ANISTATE_ATK_IRON_TWOHAND_AXE :				// 907 철양손도끼
			case HT_ANISTATE_ATK_IRON_TWOHAND_SWORD :			// 909 철양손검
			case HT_ANISTATE_ATK_WOOD_STAFF :					// 911 나무 지팡이
			case HT_ANISTATE_ATK_IRON_TWOHAND_MOONSWORD :		// 914 언월도
				{
					strSocket = _T("BWeapon05");
					HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
					m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
					m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
				}	break;

				// 활
			case HT_ANISTATE_ATK_BOW :							// 915 활
				{
					strSocket = _T("BWeapon02");
					HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
					m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
					m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
				}	break;

				// 글러브
			case HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON :		// 905 가죽격투무기
			case HT_ANISTATE_ATK_IRON_MATIALART_WEAPON :		// 913 갈퀴격투무기
				{			
					// 왼손
					strSocket = _T("BWeapon04_2");
					HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
					m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
					m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );

					// 오른손
					strSocket = _T("BWeapon04_1");
					HTdword dwIDSecondModel;
					m_pResMgr->HT_bGetSecondSocketModelID( idItem, dwIDSecondModel );
					HT_hrAttachObject( idObj, strSocket, dwIDSecondModel, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
					m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
					m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
					m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
				}	break;

			default :
				strSocket = _T("BWeapon01");
				HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
				m_pResMgr->HT_bGetSocketTexID( idItem, dwSocketTexID );
				m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
				m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
				break;
			}
		}
	}

	if ( HT_IS_ITEM_SHIELD( idShield ) )
	{
		HTdword dwSocketID;
		CHTString strSocket;
		m_pResMgr->HT_bGetSocketModelID( idShield, dwSocketID );

		strSocket = _T("SLD");
		HT_hrDetachObject( idObj, strSocket );
		strSocket = _T("BWeapon03");
		HT_hrDetachObject( idObj, strSocket );

		if ( dwSocketID )
		{
			HTdword dwSocketTexID;
			CHTString strFile;
			HT_hrAttachObject( idObj, strSocket, dwSocketID, HT_fGetModelScaleFactor( idTribe, dwSocketID ) );
			m_pResMgr->HT_bGetSocketTexID( idShield, dwSocketTexID );
			m_pResMgr->HT_bGetFileName( dwSocketTexID, strFile );
			m_p3DMgr->HT_hrChangeSocketTexture( idObj, strSocket, strFile );
		}
	}

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrShowShadow( HTint idObj, HTbool bShow )
{
	m_p3DMgr->HT_hrShowShadow( idObj, bShow );
    return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrRenderLoadingBGI()
{
	//	Render BGI
	if( m_iBGIBalck>0 )
	{
		g_pEngineHandler->HT_hrScaleObject( m_iBGIBalck, this->HT_iGetScreenWidth(), this->HT_iGetScreenHeight() );
		g_pEngineHandler->HT_hrChangeColor( m_iBGIBalck, HT_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
		g_pEngineHandler->HT_hrRenderObject( m_iBGIBalck );
	}

	if( m_iLoadingBackGroundImage>0 )
		g_pEngineHandler->HT_hrRenderObject( m_iLoadingBackGroundImage );

	return ( HT_OK );
}

HTRESULT
CHTEngineHandler::HT_hrRenderLoadingProgress( HTbool bFlip, HTfloat fBarValue )
{
	//	Render Progress Bar
	if (m_iLoadingBox > 0)
		g_pEngineHandler->HT_hrRenderObject( m_iLoadingBox );
	if (m_iLoadingBar > 0)
	{
		HTint iScaleX = HTint(fBarValue*512);
		g_pEngineHandler->HT_hrScaleObject( m_iLoadingBar, iScaleX, 16 );
		g_pEngineHandler->HT_hrRenderObject( m_iLoadingBar );
	}
	if( bFlip )
        m_p3DMgr->HT_hrFlipScreen();

	return ( HT_OK );
}

//	울고싶다.
HTvoid
CHTEngineHandler::HT_vCreate_LoadingBGImage()
{
	// 해상도 추출
	HTint iScreenWidth	= this->HT_iGetScreenWidth();
	HTint iScreenHeight	= this->HT_iGetScreenHeight();

	m_iBGIBalck = this->HT_iCreate2DSprite( 26085, HTvector3( 0, 0, 0 ) );
	//	Loading BackGround Image
	if( iScreenWidth < _ANCHOR_SCREEN_WIDTH )
	{
        m_iLoadingBackGroundImage = this->HT_iCreate2DSprite( 26029, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBackGroundImage, HTvector3( 144, 100, 0 ) );

		//	Loading progress bar
		m_iLoadingBox = this->HT_iCreate2DSprite( 26081, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBox, HTvector3( (HTfloat)((iScreenWidth/2)-256), (HTfloat)(iScreenHeight-100), 0 ) );
		m_iLoadingBar = this->HT_iCreate2DSprite( 26082, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBar, HTvector3( (HTfloat)((iScreenWidth/2)-249), (HTfloat)(iScreenHeight-93), 0 ) );
	}
	else if( iScreenWidth == _ANCHOR_SCREEN_WIDTH )
	{
		m_iLoadingBackGroundImage = this->HT_iCreate2DSprite( 26032, HTvector3( 0, 0, 0 ) );
		HTint iWidthTerm = iScreenWidth - _ANCHOR_SCREEN_WIDTH;
		HTint iHightTerm = iScreenHeight - _ANCHOR_SCREEN_HEIGHT;
		this->HT_hrMoveObject( m_iLoadingBackGroundImage, HTvector3( (HTfloat)(iWidthTerm), (HTfloat)(iHightTerm), 0 ) );

		//	Loading progress bar
		m_iLoadingBox = this->HT_iCreate2DSprite( 26081, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBox, HTvector3( (HTfloat)((iScreenWidth/2)-256), (HTfloat)(iScreenHeight-100), 0 ) );
		m_iLoadingBar = this->HT_iCreate2DSprite( 26082, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBar, HTvector3( (HTfloat)((iScreenWidth/2)-249), (HTfloat)(iScreenHeight-93), 0 ) );
	}
	else
	{
		m_iLoadingBackGroundImage = this->HT_iCreate2DSprite( 26032, HTvector3( 0, 0, 0 ) );
		HTint iWidthTerm = iScreenWidth - _ANCHOR_SCREEN_WIDTH;
		HTint iHightTerm = iScreenHeight - (_ANCHOR_SCREEN_HEIGHT);
		this->HT_hrMoveObject( m_iLoadingBackGroundImage, HTvector3( (HTfloat)(iWidthTerm/2), (HTfloat)(iHightTerm/2), 0 ) );

		//	Loading progress bar
		m_iLoadingBox = this->HT_iCreate2DSprite( 26081, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBox, HTvector3( (HTfloat)((iScreenWidth/2)-256), (HTfloat)(iScreenHeight-200), 0 ) );
		m_iLoadingBar = this->HT_iCreate2DSprite( 26082, HTvector3( 0, 0, 0 ) );
		this->HT_hrMoveObject( m_iLoadingBar, HTvector3( (HTfloat)((iScreenWidth/2)-249), (HTfloat)(iScreenHeight-193), 0 ) );
	}
}

HTvoid
CHTEngineHandler::HT_vDestory_LoadingBGImage()
{
	//	Destory BackGround Image
	if( m_iBGIBalck != -1 )
	{
		this->HT_vDestroyObject( m_iBGIBalck, 1 );
		m_iBGIBalck = -1;
	}
	if( m_iLoadingBackGroundImage != -1 )
	{
		this->HT_vDestroyObject( m_iLoadingBackGroundImage, 1 );
		m_iLoadingBackGroundImage = -1;
	}
	//	Destory progress bar
	if( m_iLoadingBox != -1 )
	{
		this->HT_vDestroyObject( m_iLoadingBox, 1 );
		m_iLoadingBox = -1;
	}
	if( m_iLoadingBar != -1 )
	{
		this->HT_vDestroyObject( m_iLoadingBar, 1 );
		m_iLoadingBar = -1;
	}
}

HTRESULT
CHTEngineHandler::HT_hrMoveObject(HTint idObj, HTvector3& vecTo, HTvector3& vecResult)
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HT_UPDATEOBJPARAM updateParam;
	updateParam.idCamera	= m_idCamera;

	if ( m_p3DMgr->HT_byEObjectForWhat( idObj ) != HT_EOBJ_FOR_MAP )
	{
		m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );
		return ( HT_OK );
	}

	if ( m_bWorldLoaded )
	{
		HTvector3 vecStartPos;
		m_p3DMgr->HT_hrGetPosition( m_idMainCharacter, vecStartPos );

		if ( CHTVector::HT_fVec3Length( &(vecTo-vecStartPos) ) < HT_EPSILON )
		{
			vecResult = vecTo;
			return ( HT_OK );
		}

		m_pMapSystem->HT_hrMoveObject( idObj, vecStartPos, 5.0f, vecTo, vecResult );

		// TODO
		//vecResult.y = m_p3DMgr->HT_fGetMidHeight( m_idTerrain, vecResult.x, vecResult.z );

		// Main Character를 이동시 그 위치에 맞는 공간음과 배경음을 틀어주어야 한다.
		if ( idObj == m_idMainCharacter )
		{
			m_iPrevAreaID = m_iAreaID;

			if ( m_fNowTimeInAllDay < 0.5f )	// 낮시간
				m_pMapSystem->HT_hrNotifySoundMove( HT_TRUE, vecResult );
			else
				m_pMapSystem->HT_hrNotifySoundMove( HT_FALSE, vecResult );

			m_iAreaID = m_pMapSystem->HT_iSetArea(vecTo);
			// 이동한 거리가 32미터될때마다 로드를 조금씩 한다.
			if ( CHTVector::HT_fVec3Length( &(m_vecStampPos - vecResult) ) > 320.0f )
			{
				m_vecStampPos = vecResult;
				HT_hrLoadMapObjsDynamic( vecResult );
			}
		}

		updateParam.vecPosition = vecResult;
		m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam );
	}
	else
	{
		return ( HT_FAIL );
	}

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrDrawBoundingTriangle( HTvector3& vecPoint1, HTvector3& vecPoint2, HTvector3& vecPoint3, HTmatrix& matTransform )
{
	m_p3DMgr->HT_hrDrawBoundingTriangle( vecPoint1, vecPoint2, vecPoint3, matTransform );

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrShowObject( const HTint idObj, HTbool bFlag )
{
	//if ( m_bWorldLoaded )
	//{
	//	if ( bFlag )
	//	{
	//		HT_AABB oAABB;
	//		HTmatrix matTransform;
	//		m_p3DMgr->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform );
	//		m_pMapSystem->HT_hrInsertObject( idObj, &oAABB, &matTransform, HT_OBJSIZE_SMALL, 0 );
	//	}
	//	else
	//	{
	//		OutputDebugString("HT_OBJSIZE_NONE 시작");
	//		m_pMapSystem->HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );
	//		OutputDebugString("HT_OBJSIZE_NONE 끝");
	//	}
	//}

	return ( m_p3DMgr->HT_hrShowObject( idObj, bFlag ) );
}

HTRESULT				
CHTEngineHandler::HT_hrChangeSkillAnimation( HTint idObj, HTint idTribe, HTdword dwSkillID, HTint iLoop, HTint idHead, HTint idWearItem, HTfloat fTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3, dwAnimType;
	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;
	dwAnimType = 0;
	//	HT_ANIM_STATE eState;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		//m_pFXPCResMgr->HT_bGetSkillAniType( dwSkillID, dwAnimType );
		//switch ( dwAnimType ) 
		//{
		//case HT_SKILL_ANITYPE_CURE:
		//	eState = HT_ANISTATE_MAGIC_HEAL;
		//	break;
		//case HT_SKILL_ANITYPE_DEFENCE:
		//	eState = HT_ANISTATE_MAGIC_DEFENCE;
		//	break;
		//case HT_SKILL_ANITYPE_ASSIST:
		//	eState = HT_ANISTATE_MAGIC_HEAL;
		//	break;
		//default:
		//	return ( HT_FAIL );
		//}

		//dwAnimID = HT_dwGetPCAniID( idTribe, eState );

		//dwMotionSoundID1 = HT_dwGetPCSoundID1( idTribe, eState );
		//dwMotionSoundID2 = HT_dwGetPCSoundID2( idTribe, eState );
		//dwMotionSoundID3 = HT_dwGetPCSoundID3( idTribe, eState );
		////--------------------------------------------------------------------
		//// 소켓에 붙은 모델들의 에니메이션을 세팅해 준다.
		//HTdword dwSocketAnimID;
		//CHTString strSocket;
		//if ( idHead > 0 )
		//{
		//	HTdword dwIDHead = HT_dwGetHeadID( idTribe, idHead );

		//	HTdword dwHairType;
		//	strSocket = _T("Hair");
		//	m_pResMgr->HT_bGetHairType( idHead, dwHairType );
		//	switch ( dwHairType ) 
		//	{
		//	case 1:
		//		m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
		//		break;
		//	case 2:
		//		m_pResMgr->HT_bGetHair2AniID( dwAnimID, dwSocketAnimID );
		//		break;
		//	default:
		//		m_pResMgr->HT_bGetHair1AniID( dwAnimID, dwSocketAnimID );
		//		break;
		//	}
		//	m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwSocketAnimID, m_fAniInterpolateTime, fTime );
		//}

		//dwSocketAnimID = 0;

		//HTdword dwFApronAniID, dwBApronAniID;
		//dwFApronAniID = HT_dwGetFApronAnimID( idTribe, eState );
		//dwBApronAniID = HT_dwGetBApronAnimID( idTribe, eState );

		//strSocket = _T("FApron");
		//m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwFApronAniID, m_fAniInterpolateTime, fTime );

		//strSocket = _T("BApron");
		//m_p3DMgr->HT_hrSetSocketAnim( idObj, strSocket, dwBApronAniID, m_fAniInterpolateTime, fTime );
		//--------------------------------------------------------------------
	}
	else
	{
		return ( HT_FAIL );
	}

	HTdword dwSelectSound = HT_dwGetRandomSoundID( dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3 );

	m_p3DMgr->HT_hrChangeAnimation( idObj, dwAnimID, dwSelectSound, iLoop, m_fAniInterpolateTime, fTime );

	m_p3DMgr->HT_hrSetSwordWind( idObj, HT_FALSE );

	return ( HT_OK );
}

//HTdword					
//CHTEngineHandler::HT_dwGetSkillAniType( HTdword dwSkillID )
//{
//	HTdword dwSkillAniType = 0;
//	m_pFXPCResMgr->HT_bGetSkillAniType( dwSkillID, dwSkillAniType );
//	return ( dwSkillAniType );
//}

//---------------------------------------------------------------------------------------------
// HTRESULT	HT_hrUpdateMiniMap( HTvector3& vecCharPos)
// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
// I : vecPos - 위치(입력하면 int로 변환되어 사용된다.), iWidth/iHeight - 크기
//---------------------------------------------------------------------------------------------
HTRESULT
CHTEngineHandler::HT_hrUpdateMiniMap( HTint iMiniMapID, HTint iMiniMapLevel, HTint iXPos, HTint iYPos, HTint iWidth, HTint iHeight, HTvector3& vecInterestPos, HTvector3& vecInterestUp, HTfloat fZoom )
{
	HTvector3 vecEyePos = vecInterestPos + HTvector3( 0.0f, 1000.0f, 0.0f );

	HTvector3 arrvecFrustum[5];
	HTFrustumPlane arrFrustumPlane[6];

	// 회전을 해야 하기 때문에 원래는 아래의 FrustumPlane과 FrustumPoint를 변환해줘야 하는데,
	// 차라리 조금 더 넓은 Culling 공간을 사용하는 것이 연산 속도도 적고,
	// 고쳐야 할 코드도 적기^^;; 때문이다.
	HTfloat fMinimapZoom = fZoom * 1.5f;

	HTvector3 vec = vecInterestPos;
	vec.y = 0.0f; //CHTVector::HT_pvecVec3Normalize( &vec, &vec );
	// OrthoProjection에 적합한 arrvecFrustum와 arrFrustumPlane를 구한다.
	// FrustumPlane : N - F - L - R - T - B
	arrFrustumPlane[0].m_vecNormal = HTvector3( 0.0f, -1.0f, 0.0f );
	arrFrustumPlane[0].m_fDistance = -1000.0f;

	arrFrustumPlane[1].m_vecNormal = HTvector3( 0.0f, 1.0f, 0.0f );
	arrFrustumPlane[1].m_fDistance = -1000.0f;

	arrFrustumPlane[2].m_vecNormal = HTvector3( 1.0f, 0.0f, 0.0f );
	arrFrustumPlane[2].m_fDistance = (vec.x - fMinimapZoom);

	arrFrustumPlane[3].m_vecNormal = HTvector3( -1.0f, 0.0f, 0.0f );
	arrFrustumPlane[3].m_fDistance = -(vec.x + fMinimapZoom);

	arrFrustumPlane[4].m_vecNormal = HTvector3( 0.0f, 0.0f, -1.0f );
	arrFrustumPlane[4].m_fDistance = -(vec.z + fMinimapZoom);

	arrFrustumPlane[5].m_vecNormal = HTvector3( 0.0f, 0.0f, 1.0f );
	arrFrustumPlane[5].m_fDistance = (vec.z - fMinimapZoom);

	// FrustumPoints : Eye - LeftUp - LeftDown - RightUp - RightDown
	arrvecFrustum[0] = vecEyePos;
	arrvecFrustum[1] = HTvector3( vec.x - fMinimapZoom, -1000.0f, vec.z + fMinimapZoom ) * 2.0f;
	arrvecFrustum[2] = HTvector3( vec.x - fMinimapZoom, -1000.0f, vec.z - fMinimapZoom ) * 2.0f;
	arrvecFrustum[3] = HTvector3( vec.x + fMinimapZoom, -1000.0f, vec.z + fMinimapZoom ) * 2.0f;
	arrvecFrustum[4] = HTvector3( vec.x + fMinimapZoom, -1000.0f, vec.z - fMinimapZoom ) * 2.0f;

	std::vector<HTint> arrvecMiniMapViewingObjs;
	std::vector<HTint> arrvecMiniMapUpdateObjs;
	arrvecMiniMapViewingObjs.clear();
	arrvecMiniMapUpdateObjs.clear();
	m_pMapSystem->HT_hrUpdateViewingNodes( arrvecFrustum, arrFrustumPlane, arrvecMiniMapViewingObjs, arrvecMiniMapUpdateObjs );

	static HT_UPDATEOBJPARAM UpdateParam;

	// 화면에 나오는 곳의 위치
	UpdateParam.vecPosition = HTvector3( (HTfloat)iXPos, (HTfloat)iYPos, 0.0f );
	// 화면에 나오는 크기
	UpdateParam.vecScale = HTvector3( (HTfloat)iWidth, (HTfloat)iWidth, 0.0f );
	// 미니맵에 찍는 곳의 중심점
	UpdateParam.vecCharPos = vecInterestPos;
	// 미니맵을 찍는 방향
	UpdateParam.vecRotation = vecInterestUp;
	// 미니맵에 찍는 곳을 중심으로 옆으로의 길이
	UpdateParam.fLODDetail = fZoom;
	// 미니맵에 나오는 MapObjs
	UpdateParam.piViewObjIDs = (HTint*)(&arrvecMiniMapViewingObjs);
	// 뭐뭐를 찍을건가요?
	UpdateParam.nVolume = iMiniMapLevel;

	return m_p3DMgr->HT_hrUpdateObject( m_idMiniMap, &UpdateParam );
}

HTbool CHTEngineHandler::HT_bMinimapLoaded()
{
	CHTString strMinimap;
	m_pResMgr->HT_bGetMinimapFilesName( m_dwCurrentMapID, strMinimap );
	if ( strMinimap != _T("0") && strMinimap != _T("") )
		return ( HT_TRUE );

	return ( HT_FALSE );
}

HTRESULT				
CHTEngineHandler::HT_hrClipRotateObject( HTint idObj, HTfloat fRot, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY, HTint iPosX, HTint iPosY )
{
	HT_UPDATEOBJPARAM updateParam;
	updateParam.iClippingLTX = iLTX;
	updateParam.iClippingLTY = iLTY;
	updateParam.iClippingRBX = iRBX;
	updateParam.iClippingRBY = iRBY;

	updateParam.vecRotation = HTvector3( 0.0f, fRot, 0.0f );

	updateParam.vecPosition = HTvector3( (HTfloat)(iPosX - iLTX), (HTfloat)(iPosY - iLTY), 0.0f );

	HT_CHECK( m_p3DMgr->HT_hrUpdateObject( idObj, &updateParam ) );

	return ( HT_OK );
}

HTRESULT
CHTEngineHandler::HT_hrPrintScreenShot()
{
	::CreateDirectory( "ScreenShot", HT_NULL );

	CHTString strFile( ".\\ScreenShot\\Tantra" );
	char tmpbuf[128];
	_tzset();
	__time64_t ltime;
	_time64( &ltime );
	//_i64toa( ltime, tmpbuf, 10 );
	struct tm *today;
	today = _localtime64( &ltime );
	_tcsftime( tmpbuf, 128, "(%Y%m%d,%H-%M-%S)", today );
	strFile += tmpbuf;
	strFile += _T(".bmp");

	return ( m_p3DMgr->HT_hrPrintScreenShot( strFile ) );
}

#ifdef HT_IS_TANTRA_LAUNCHER
//------------------------------------------------------------------------------//
//	NPC Script
//------------------------------------------------------------------------------//
HTint CHTEngineHandler::HT_nSetActiveNPC(BYTE byNPCType)
{
	return m_pNPCScriptMgr->HT_nSetActiveNPC(byNPCType);
}
//-------처음 단계로 셋팅한다---------//
HTint CHTEngineHandler::HT_nSetFirstStep()
{
	return m_pNPCScriptMgr->HT_nSetFirstStep();
}
//-------다음 단계로 간다-------------//
HTint CHTEngineHandler::HT_nNextStep(HTint nSelNum)
{
	return m_pNPCScriptMgr->HT_nNextStep(nSelNum);
}

HTvoid CHTEngineHandler::HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam)
{
	m_pNPCScriptMgr->HT_vGetQuestion(szText, pbyteParam);
}

HTvoid CHTEngineHandler::HT_vGetSelectText(HTint nIndex, CHTString& szText)
{
	m_pNPCScriptMgr->HT_vGetSelectText(nIndex, szText );
}

HTint CHTEngineHandler::HT_iGetNowQuestionIndex()
{
	return m_pNPCScriptMgr->m_iQuestion;
}

HTshort CHTEngineHandler::HT_sGetClientEvent()
{
	return m_pNPCScriptMgr->HT_sGetClientEvent();
}

HTshort CHTEngineHandler::HT_sGetServerEvent()
{
	return m_pNPCScriptMgr->HT_sGetServerEvent();
}

//-------- 현재 퀘스트 레벨을 찾는다 ----------//
HTvoid CHTEngineHandler::HT_vGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& byClientLvlTime)
{
	m_pNPCScriptMgr->HT_vGetQuestLevel(byServerLvl, byClientLvl, byClientLvlTime);
}

//-------- 현재 퀘스트의 다음 레벨을 찾는다 ----------//
HTvoid CHTEngineHandler::HT_vGetNextQuestLevel(BYTE& byClientLvl, BYTE& byClientLvlTime)
{
	m_pNPCScriptMgr->HT_vGetNextQuestLevel(byClientLvl, byClientLvlTime);
}

#endif

HTRESULT				
CHTEngineHandler::HT_hrPlayHitSound( HTint idTribe, HTint idObj )
{
	HTdword dwMotionSoundID1, dwMotionSoundID2, dwMotionSoundID3;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;
	dwMotionSoundID3 = 0;

	if ( HT_IS_CHARACTER( idTribe ) )
	{
		switch( idTribe )
		{
		case HT_ID_CHARACTER_NAGA:
			m_pResMgr->HT_bGetNAGSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetNAGSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetNAGSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_YAKSA:
			m_pResMgr->HT_bGetYAKSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetYAKSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetYAKSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_ASURA:
			m_pResMgr->HT_bGetASUSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetASUSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetASUSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_DEVA:
			m_pResMgr->HT_bGetDEVSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetDEVSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetDEVSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_KIMNARA:
			m_pResMgr->HT_bGetKIMSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetKIMSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetKIMSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_GANDHARVA:
			m_pResMgr->HT_bGetGANSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetGANSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetGANSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_RAKSHASA:
			m_pResMgr->HT_bGetRAKSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetRAKSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetRAKSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		case HT_ID_CHARACTER_GARUDA:
			m_pResMgr->HT_bGetGARSoundID1( HT_ANISTATE_HIT_S1H, dwMotionSoundID1 );
			m_pResMgr->HT_bGetGARSoundID2( HT_ANISTATE_HIT_S1H, dwMotionSoundID2 );
			m_pResMgr->HT_bGetGARSoundID3( HT_ANISTATE_HIT_S1H, dwMotionSoundID3 );
			break;
		}
	}
	else if ( HT_IS_MONSTER( idTribe ) )	
	{
		HTdword dwFXMonID;
		m_pResMgr->HT_bGetMonFXID( idTribe, dwFXMonID );
		if ( HT_IS_FXMON( dwFXMonID ) )
		{
			m_pResMgr->HT_bGetMonHitSoundID( dwFXMonID, dwMotionSoundID1 );
			m_pResMgr->HT_bGetMonHit2SoundID( dwFXMonID, dwMotionSoundID2 );
		}
	}

	// 만약 사운드가 여러개가 나왔다면 그중에서 랜덤으로 하나를 선택한다.
	// 여기서 쓰이는 사운드의 랜덤은 클라이언트 사이에 동기화가 되지 않아도 된다고 가정한다.
	HTint iSoundCount = 0;
	HTdword dwSelectSound = 0;
	if ( dwMotionSoundID1 > 0 )		iSoundCount += 1;
	if ( dwMotionSoundID2 > 0 )		iSoundCount += 2;
	if ( dwMotionSoundID3 > 0 )		iSoundCount += 4;

	HTint iMod;
	if ( iSoundCount == 0 )	// 사운드가 없으면 0을 전달하여 틀지 말라고 한다.
	{
		dwSelectSound = 0;
	}
	else if ( iSoundCount == 1 )	// 
	{
		dwSelectSound = dwMotionSoundID1;
	}
	else if ( iSoundCount == 2 )	// 
	{
		dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 4 )	// 
	{
		dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 3 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID2;
	}
	else if ( iSoundCount == 5 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID1;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 6 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwMotionSoundID2;
		else				dwSelectSound = dwMotionSoundID3;
	}
	else if ( iSoundCount == 7 )	// 
	{
		iMod = rand() % 3;
		if ( iMod == 0 )		dwSelectSound = dwMotionSoundID1;
		else if ( iMod == 1 )	dwSelectSound = dwMotionSoundID2;
		else					dwSelectSound = dwMotionSoundID3;
	}

	HTvector3 vecPos, vecOffsetPos;
	m_p3DMgr->HT_hrGetPosition( idObj, vecPos );
	m_p3DMgr->HT_hrGetOffsetPosFromMainObj( vecPos, vecOffsetPos );
	m_p3DMgr->HT_hrPlaySound( dwSelectSound, 1, vecOffsetPos );

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrUpdateMapSystem()
{
	// 맵 오브젝트들을 현재 카메라와 LODFar를 이용하여 보이는 오브젝트 리스트를 업데이트 해준다.
	HTvector3 arrvecPoints[5];
	if ( m_p3DMgr )	m_p3DMgr->HT_hrGetFrustumPoints( m_idCamera, m_fLODDistanceFar, arrvecPoints ); else return HT_FAIL;
	HTFrustumPlane arrFrustumPlane[6]; 
	if ( m_p3DMgr )	m_p3DMgr->HT_hrGetFrustumPlanes( m_idCamera, arrFrustumPlane ); else return HT_FAIL;
	//			arrFrustumPlane[1].m_fDistance -= m_p3DMgr->HT_fGetCameraFarZ(m_idCamera) - m_fLODDistanceFar;

	// 일반적인 큰 건물같은 오브젝트들에 대한 처리를 한다.
	m_vectorViewingObjs.clear();
	m_vectorUpdateObjs.clear();
	if ( m_pMapSystem ) m_pMapSystem->HT_hrUpdateViewingNodes( arrvecPoints, arrFrustumPlane, m_vectorViewingObjs, m_vectorUpdateObjs ); else return HT_FAIL;

	// 멀리있으면 신경도 안 쓰일거 같은 작은 오브젝트들에 대한 처리를 한다.
	if ( m_p3DMgr )	m_p3DMgr->HT_hrGetFrustumPoints( m_idCamera, m_fLODDistanceFarSM, arrvecPoints ); else return HT_FAIL;
	if ( m_pMapSystem ) m_pMapSystem->HT_hrUpdateViewingSMNodes( arrvecPoints, arrFrustumPlane, m_vectorViewingObjs ); else return HT_FAIL;

	m_nRenderObjs = (HTuint)m_vectorViewingObjs.size();

	// 풀들이 보이는지 검사하고, 거리에 따라 알파값을 먹인다.
	if ( m_pMapSystem ) m_pMapSystem->HT_hrUpdateViewingGrasses( arrvecPoints, arrFrustumPlane, m_fGrassarea, m_fGrassAlphaDistance, m_vectorGrasses ); else return HT_FAIL;

	m_bUpdateViewingObjs = HT_FALSE;

	return ( HT_OK );
}

//HTRESULT				
//CHTEngineHandler::HT_hrGetObjSize( HTint idObj, HTfloat* fHeight, HTfloat* fWidth, HTfloat* fDepth )
//{
//	if ( !fHeight || !fWidth || !fDepth )
//	{
//		return ( HT_FAIL );
//	}
//
//	HT_AABB oAABB;
//	HTmatrix matTransform;
//	HT_CHECK( m_p3DMgr->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform ) );
//
//	CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMax, &oAABB.vecMax, &matTransform );
//	CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMin, &oAABB.vecMin, &matTransform );
//
//	*fWidth = oAABB.vecMax.x - oAABB.vecMin.x;
//	*fHeight = oAABB.vecMax.y - oAABB.vecMin.y;
//	*fDepth = oAABB.vecMax.z - oAABB.vecMin.z;
//
//	return ( HT_OK );
//}

HTfloat
CHTEngineHandler::HT_fGetObjHeight( HTint idObj )
{
	HTfloat fHeight = m_p3DMgr->HT_fGetObjHeight( idObj );

	if ( fHeight != 0.0f )
	{
		return fHeight;
	}
	else
	{
		// 설마 구하고자 하는 대상이 SkinnedModel이 아니어서 이쪽으로 오는 경우가 있겠냐만은.. 그래도 확인차..
		HT_AABB oAABB;
		HTmatrix matTransform;

		if ( HT_SUCCEED( m_p3DMgr->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform ) ) )
		{
			CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMax, &oAABB.vecMax, &matTransform );
			CHTVector::HT_pvecVec3TransformCoord( &oAABB.vecMin, &oAABB.vecMin, &matTransform );

			return ( oAABB.vecMax.y - oAABB.vecMin.y );
		}
		else
		{
			return 0.0f;
		}
	}
}

HTbool					
CHTEngineHandler::HT_bIsWeapon( HTdword dwID )
{
	HTdword dwType = 0;
	if ( m_pResMgr->HT_bGetItemType( dwID, dwType ) )
	{
		if ( dwType >= HT_ANISTATE_ATK_IRON_ONEHAND_SWORD && dwType < HT_ANISTATE_ATK_END )
			return ( HT_TRUE );
	}
	return ( HT_FALSE );
}

HTRESULT				
CHTEngineHandler::HT_hrOpenPackFile( CHTString& strFile, HTbool bMemUse )
{
	return ( m_pPackFileMgr->HT_hrOpenPackFile( strFile, bMemUse ) );
}

HTRESULT				
CHTEngineHandler::HT_hrClosePackFile( CHTString& strFile )
{
	return ( m_pPackFileMgr->HT_hrClosePackFile( strFile ) );
}

HTRESULT				
CHTEngineHandler::HT_hrPlayIntroBGM()
{
	switch ( rand() % 2 ) 
	{
	case 0:
		m_idIntroBGM = 30015;
		break;
	case 1:
		m_idIntroBGM = 30015;
		break;
	default:
		break;
	}

	//CHTString strBGM( _T("resource\\sound\\OSTSound.hpk") );
	//m_pPackFileMgr->HT_hrOpenPackFile( strBGM, HT_FALSE );

	// BGM으로 OST의 mp3를 Pak으로 쓰기 때문에 할 수 없이 2DSAMPLE로 사용하게 되었다.
	CHTString strFile;
	m_pResMgr->HT_bGetFileName( m_idIntroBGM, strFile );
	m_p3DMgr->HT_hrLoadObject( HT_SOBJTYPE_STREAM, m_idIntroBGM, strFile );

	m_p3DMgr->HT_hrPlaySound( m_idIntroBGM, 2 );

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrStopIntroBGM()
{
	if ( m_idIntroBGM < 0 )
		return ( HT_FAIL );

	m_p3DMgr->HT_hrStopSampleSound();

	m_p3DMgr->HT_hrUnLoadObject( m_idIntroBGM );

	CHTString strBGM( _T("resource\\sound\\OSTSound.hpk") );
	m_pPackFileMgr->HT_hrClosePackFile( strBGM );

	m_p3DMgr->HT_hrStartSampleSound();

	m_idIntroBGM = -1;

	return ( HT_OK );
}

HTRESULT				
CHTEngineHandler::HT_hrChangeMonsterAttackAnimation( HTint idObj, HTdword dwID, HTdword dwSkillID, HTint iLoop, HTfloat fTime )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	HTdword dwAnimID, dwMotionSoundID1, dwMotionSoundID2;

	dwAnimID = 0;
	dwMotionSoundID1 = 0;
	dwMotionSoundID2 = 0;

	HTdword dwFXMonID;
	m_pResMgr->HT_bGetMonFXID( dwID, dwFXMonID );
	if ( HT_IS_FXMON( dwFXMonID ) )
	{
		m_pResMgr->HT_bGetMonAttackSoundID1( dwFXMonID, dwMotionSoundID1 );
		m_pResMgr->HT_bGetMonAttackSoundID2( dwFXMonID, dwMotionSoundID2 );
	}

	m_pFXMAPResMgr->HT_bGetSkillAni( dwSkillID, dwAnimID );

	if ( dwAnimID == 0 )
		m_pResMgr->HT_bGetATK1AniID( dwID, dwAnimID );

	HTdword dwSelectSound;
	if ( rand() % 2 == 0 )
		dwSelectSound = dwMotionSoundID1;
	else
		dwSelectSound = dwMotionSoundID2;

	this->HT_hrLoadToResPool( dwAnimID, HT_TRUE );
	m_p3DMgr->HT_hrChangeAnimation( idObj, dwAnimID, dwSelectSound, iLoop, m_fAniInterpolateTime, fTime );

	return ( HT_OK );
}

HTvoid
CHTEngineHandler::HT_vSetLoadTimes(HTint iTimes)
{
	m_iLoadTimes = iTimes;
}

HTRESULT
CHTEngineHandler::HT_hrLoadGuildMark()
{
	CHTString strResFile( _T("resource\\UI\\GuildMark.hpk") );

	m_pPackFileMgr->HT_hrOpenPackFile( strResFile );
	{
		CHTString strTable;

		strTable = HT_RES_TABLENAME_GUILDMARK_BACK;
		HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );

		strTable = HT_RES_TABLENAME_GUILDMARK_EMBLEM;
		HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );

		strTable = HT_RES_TABLENAME_GUILDMARK_TITLE;
		HT_hrLoadResource( strTable, HT_SOBJTYPE_2DSPRITE, m_oResourcePath.strInterface, m_oResourcePath.strInterface );
	}
	m_pPackFileMgr->HT_hrClosePackFile( strResFile );

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrAttachGuildMark( HTint idParent, HTdword wGuildIdenty )
{
	if ( !this->HT_bGetCanModify( idParent ) ) return HT_FAIL;

	HTdword dwGuildEmblem	= (wGuildIdenty & 0x000000FF);
	HTdword dwGuildTitle	= (wGuildIdenty & 0x0000FF00) >> 8;
	HTdword dwGuildColor	= (wGuildIdenty & 0x00FF0000) >> 16;

	if ( dwGuildEmblem < 1 || dwGuildEmblem > 72
		|| dwGuildTitle < 1 || dwGuildTitle > 84
		|| dwGuildColor < 1 || dwGuildColor > 72 ) return HT_FAIL;

	CHTString strGuildTitle;
	HTdword dwColor;
	m_pResMgr->HT_bGetGuildTitleTex( dwGuildTitle + HT_ID_GUILDMARK_TITLE_START - 1, strGuildTitle );
	m_pResMgr->HT_bGetGuildEmblemDWColor( dwGuildColor + HT_ID_GUILDMARK_COLOR_START - 1, dwColor );

	return m_p3DMgr->HT_hrAttachGuildMark( idParent, dwGuildEmblem, strGuildTitle, dwColor, 7.5f, 3.0f );
}

HTRESULT
CHTEngineHandler::HT_hrDestroyGuildMark( HTint idParent )
{
	if ( !this->HT_bGetCanModify( idParent ) ) return HT_FAIL;

	return m_p3DMgr->HT_hrDestroyGuildMark( idParent );
}

HTRESULT
CHTEngineHandler::HT_hrSetRederState(HTint idObj, HTint iRenderState)
{
	return m_p3DMgr->HT_hrSetRederState(idObj, iRenderState);
}

HTdword
CHTEngineHandler::HT_dwConvertGuildMarkIdenty( HTint iEmblem, HTint iTitle, HTint iColor )
{
	HTdword dwGuildIdenty = 0;

	if ( iEmblem >= 1 && iEmblem <= 72 )
	{
		dwGuildIdenty = dwGuildIdenty | iEmblem;
	}
	else
	{
		return 0;
	}

	if ( iTitle >= 1 && iTitle <= 84 )
	{
		dwGuildIdenty = dwGuildIdenty | (iTitle << 8);
	}
	else
	{
		return 0;
	}

	if ( iColor >= 1 && iColor <= 72 )
	{
		dwGuildIdenty = dwGuildIdenty | (iColor << 16);
	}
	else
	{
		return 0;
	}

	return dwGuildIdenty;
}

HTRESULT
CHTEngineHandler::HT_hrAttachGodMark( HTint idParent, HTint idTribe, HTEGodType eGod, HTint iLevel )
{
	if ( !this->HT_bGetCanModify( idParent ) ) return HT_FAIL;

	this->HT_hrDetachGodMark( idParent );

	CHTString strSocket( _T("Lord") );
	CHTString strTex;

	HT_COLOR clrStart, clrEnd;
	HTvector3 vecStart, vecEnd;
	HTfloat fStart2EndTime = 5.0f;

	vecStart = HTvector3( 1.0f, 1.0f, 1.0f ); vecEnd = HTvector3( 1.1f, 1.1f, 1.1f );

	switch ( eGod )
	{
	case HT_GODTYPE_SIVA :
		{
			strTex = HT_GODMARK_SIVA_TEX;
			switch ( iLevel )
			{
			case 1 :
				clrStart	= HT_COLOR( 0.050980392f, 0.0f, 0.298039216f, 0.5f );
				clrEnd		= HT_COLOR( 0.050980392f, 0.0f, 0.298039216f, 0.5f );
				break;
			case 2 :
				clrStart	= HT_COLOR( 0.105882353f, 0.078431373f, 0.392156863f, 0.6f );
				clrEnd		= HT_COLOR( 0.105882353f, 0.078431373f, 0.392156863f, 0.6f );
				break;
			case 3 :
				clrStart	= HT_COLOR( 0.180392157f, 0.192156863f, 0.57254902f, 0.7f );
				clrEnd		= HT_COLOR( 0.180392157f, 0.192156863f, 0.57254902f, 0.7f );
				break;
			case 4 :
				clrStart	= HT_COLOR( 0.376470588f, 0.360784314f, 0.658823529f, 0.8f );
				clrEnd		= HT_COLOR( 0.376470588f, 0.360784314f, 0.658823529f, 0.8f );
				break;
			case 5 :
				clrStart	= HT_COLOR( 0.529411765f, 0.505882353f, 0.741176471f, 0.9f );
				clrEnd		= HT_COLOR( 0.529411765f, 0.505882353f, 0.741176471f, 0.9f );
				break;
			default : return HT_FAIL;
			}

			this->HT_hrLoadToResPool( HT_GODMARK_MODEL_SIVA, HT_FALSE );
			m_p3DMgr->HT_hrAttachObject( idParent, strSocket, HT_GODMARK_MODEL_SIVA, HT_FALSE, this->HT_fGetModelScaleFactor( idTribe, HT_GODMARK_MODEL_SIVA ), (HTdword)iLevel );
			m_p3DMgr->HT_hrChangeSocketTexture( idParent, strSocket, strTex );
		} break;
	case HT_GODTYPE_BRAHMA:
		{
			strTex = HT_GODMARK_BRAHMA_TEX;
			switch ( iLevel )
			{
			case 1 :
				clrStart	= HT_COLOR( 0.509803922f, 0.482352941f, 0.0f, 0.5f );
				clrEnd		= HT_COLOR( 0.509803922f, 0.482352941f, 0.0f, 0.5f );
				break;
			case 2 :
				clrStart	= HT_COLOR( 0.670588235f, 0.62745098f, 0.0f, 0.6f );
				clrEnd		= HT_COLOR( 0.670588235f, 0.62745098f, 0.0f, 0.6f );
				break;
			case 3 :
				clrStart	= HT_COLOR( 1.0f, 0.949019608f, 0.0f, 0.7f );
				clrEnd		= HT_COLOR( 1.0f, 0.949019608f, 0.0f, 0.7f );
				break;
			case 4 :
				clrStart	= HT_COLOR( 1.0f, 0.960784314f, 0.407843137f, 0.8f );
				clrEnd		= HT_COLOR( 1.0f, 0.960784314f, 0.407843137f, 0.8f );
				break;
			case 5 :
				clrStart	= HT_COLOR( 1.0f, 0.968627451f, 0.6f, 0.9f );
				clrEnd		= HT_COLOR( 1.0f, 0.968627451f, 0.6f, 0.9f );
				break;
			default : return HT_FAIL;
			}

			this->HT_hrLoadToResPool( HT_GODMARK_MODEL_BRAHMA, HT_FALSE );
			m_p3DMgr->HT_hrAttachObject( idParent, strSocket, HT_GODMARK_MODEL_BRAHMA, HT_FALSE, this->HT_fGetModelScaleFactor( idTribe, HT_GODMARK_MODEL_BRAHMA ), (HTdword)iLevel );
			m_p3DMgr->HT_hrChangeSocketTexture( idParent, strSocket, strTex );
		} break;
	case HT_GODTYPE_VISUNU:
		{
			strTex = HT_GODMARK_VISUNU_TEX;
			switch ( iLevel )
			{
			case 1 :
				clrStart	= HT_COLOR( 0.474509804f, 0.0f, 0.0f, 0.5f );
				clrEnd		= HT_COLOR( 0.474509804f, 0.0f, 0.0f, 0.5f );
				break;
			case 2 :
				clrStart	= HT_COLOR( 0.619607843f, 0.054901961f, 0.043137255f, 0.6f );
				clrEnd		= HT_COLOR( 0.619607843f, 0.054901961f, 0.043137255f, 0.6f );
				break;
			case 3 :
				clrStart	= HT_COLOR( 0.929411765f, 0.109803922f, 0.141176471f, 0.7f );
				clrEnd		= HT_COLOR( 0.929411765f, 0.109803922f, 0.141176471f, 0.7f );
				break;
			case 4 :
				clrStart	= HT_COLOR( 0.949019608f, 0.423529412f, 0.309803922f, 0.8f );
				clrEnd		= HT_COLOR( 0.949019608f, 0.423529412f, 0.309803922f, 0.8f );
				break;
			case 5 :
				clrStart	= HT_COLOR( 0.964705882f, 0.588235294f, 0.474509804f, 0.9f );
				clrEnd		= HT_COLOR( 0.964705882f, 0.588235294f, 0.474509804f, 0.9f );
				break;
			default : return HT_FAIL;
			}

			this->HT_hrLoadToResPool( HT_GODMARK_MODEL_VISUNU, HT_FALSE );
			m_p3DMgr->HT_hrAttachObject( idParent, strSocket, HT_GODMARK_MODEL_VISUNU, HT_FALSE, this->HT_fGetModelScaleFactor( idTribe, HT_GODMARK_MODEL_VISUNU ), (HTdword)iLevel );
			m_p3DMgr->HT_hrChangeSocketTexture( idParent, strSocket, strTex );
		} break;
	default: return HT_FAIL;
	}

	// 이곳에서 에러가 나는 듯하여 일단 막는다. -> 괜찮은거 같아 다시 살려 놓는다.
	m_p3DMgr->HT_hrAttachObjectGlow( idParent, strSocket, clrStart, clrEnd, vecStart, vecEnd, fStart2EndTime );

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrDetachGodMark( HTint idParent )
{
	if ( !this->HT_bGetCanModify( idParent ) ) return HT_FAIL;

	CHTString strSocket( _T("Lord") );
	// 이곳에서 에러가 나는 듯하여 일단 막는다. -> 괜찮은거 같아 다시 살려 놓는다.
	m_p3DMgr->HT_hrDetachObjectGlow( idParent, strSocket );
	return this->HT_hrDetachObject( idParent, strSocket );
}

HTRESULT				
CHTEngineHandler::HT_hrStopBGM()
{
	m_p3DMgr->HT_hrStopStreamSound();

	return ( HT_OK );
}

HTbool					
CHTEngineHandler::HT_bIsWearItem( HTdword dwID )
{
	HTdword dwType = 0;
	if ( m_pResMgr->HT_bGetWearItemID( dwID, dwType ) )
	{
		if ( ( dwType >= HT_ID_UP_WEAR_ITEM_START && dwType < HT_ID_UP_WEAR_ITEM_END )
			|| ( dwType >= HT_ID_DOWN_WEAR_ITEM_START && dwType < HT_ID_DOWN_WEAR_ITEM_END )
			|| ( dwType >= HT_ID_HAND_WEAR_ITEM_START && dwType < HT_ID_HAND_WEAR_ITEM_END ) )
		{
			return ( HT_TRUE );
		}
		else return HT_FALSE;
	}
	return ( HT_FALSE );
}

HTbool					
CHTEngineHandler::HT_bIsGloveItem( HTdword dwID )
{
	CHTString strSocket;
	if ( m_pResMgr->HT_bGetSocketName( dwID, strSocket ) )
	{
		if ( strSocket.HT_bFind( "LeftClaw" ) )
			return ( HT_TRUE );
	}
	return ( HT_FALSE );
}

HTbool					
CHTEngineHandler::HT_bIsDartItem( HTdword dwID )
{
	if ( dwID >= HT_ID_ITEM_DART_START && dwID <= HT_ID_ITEM_DART_END )
		return ( HT_TRUE );

	return ( HT_FALSE );
}

HTbool					
CHTEngineHandler::HT_bIsHatItem( HTdword dwID )
{
	CHTString strSocket;
	if ( m_pResMgr->HT_bGetSocketName( dwID, strSocket ) )
	{
		if ( strSocket.HT_bFind( "Hat" ) )
			return ( HT_TRUE );
	}
	return ( HT_FALSE );
}

HTbool					
CHTEngineHandler::HT_bIsShieldItem( HTdword dwID )
{
	CHTString strSocket;
	if ( m_pResMgr->HT_bGetSocketName( dwID, strSocket ) )
	{
		if ( strSocket.HT_bFind( "SLD" ) )
			return ( HT_TRUE );
	}
	return ( HT_FALSE );
}

HTbool				
CHTEngineHandler::HT_bIsShoesItem( HTdword dwID )
{
	HTdword dwType = 0;
	if ( m_pResMgr->HT_bGetShoesItemID( dwID, dwType ) )
	{
		if ( dwType >= HT_ID_SHOES_ITEM_START && dwType < HT_ID_SHOES_ITEM_END )
			return ( HT_TRUE );
	}
	return ( HT_FALSE );
}

HTbool
CHTEngineHandler::HT_bIsShortSword( HTdword dwID )
{
	HTdword dwType = 0;
	m_pResMgr->HT_bGetItemType( dwID, dwType );
	if ( dwType == HT_ANISTATE_ATK_IRON_ONEHAND_SHORTSWORD ) return HT_TRUE;
	else return HT_FALSE;
}

HTRESULT				
CHTEngineHandler::HT_hrDontClickIt( HTint idObj )
{
	m_setDontClickObjs.insert( idObj );
	return ( HT_OK );
}

HTbool					
CHTEngineHandler::HT_bIsWindowCursor()
{
	switch ( m_pUserSettings->HT_eGetCursorType() ) 
	{
	case HT_OPT_CURSOR_WINDOW:
		return ( HT_TRUE );
	case HT_OPT_CURSOR_IMAGE:
		return ( HT_FALSE );
	default:
		return ( HT_FALSE );
	}
}

HTbool
CHTEngineHandler::HT_bGetIndicatedArea(HTint& iPrevAreaID, HTint& iAreaID, CHTString& strAreaName)
{
	iPrevAreaID = m_iPrevAreaID;
	iAreaID = m_iAreaID;
	return m_pResMgr->HT_bGetAreaName( HT_ID_AREAINDICATE_START, m_iPrevAreaID, m_iAreaID, strAreaName );

}

HTRESULT
CHTEngineHandler::HT_hrGetNPCName( HTdword dwID, CHTString* pstrName )
{
	if ( m_pResMgr->HT_bGetName( dwID, *pstrName ) ) return HT_OK;
	else return HT_FAIL;
}

HTRESULT
CHTEngineHandler::HT_hrGetPCSkillName( HTdword dwID, CHTString* pstrName )
{
	if ( m_pFXPCResMgr->HT_bGetSkillName( dwID, *pstrName ) ) return HT_OK;
	else return HT_FAIL;
}

HTRESULT
CHTEngineHandler::HT_hrGetPCSkillDesc( HTdword dwID, CHTString* pstrName )
{
	if ( m_pFXPCResMgr->HT_bGetSkillDesc( dwID, *pstrName ) ) return HT_OK;
	else return HT_FAIL;
}

HTRESULT
CHTEngineHandler::HT_hrGetMonsterName( HTdword dwID, CHTString* pstrName )
{
	if ( m_pResMgr->HT_bGetName( dwID, *pstrName ) ) return HT_OK;
	else return HT_FAIL;
}

HTvoid
CHTEngineHandler::HT_vOnMouseMove( HTint iX, HTint iY )
{
	m_oMousePosFX.i2DMouseX = iX;
	m_oMousePosFX.i2DMouseY = iY;
}

HTRESULT
CHTEngineHandler::HT_hrOnMouseWideEffect( HTdword dwFX )
{
	if ( m_oMousePosFX.idWideFXTargeting > 0 ) this->HT_hrStopSFX( m_oMousePosFX.idWideFXTargeting );

	return this->HT_hrStartSFX( &m_oMousePosFX.idWideFXTargeting, dwFX, m_oMousePosFX.idMouseNullModel, HT_TRUE );
}

HTRESULT
CHTEngineHandler::HT_hrOffMouseWideEffect()
{
	if ( m_oMousePosFX.idWideFXTargeting > 0 ) this->HT_hrStopSFX( m_oMousePosFX.idWideFXTargeting );

	m_oMousePosFX.idWideFXTargeting = -1;
	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrAttachItemMainRefineEffect( HTint idObj, HTdword dwIDItem, HTint iMainRefineLevel )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_ITEM_WEAPON( dwIDItem ) || HT_IS_ITEM_SHIELD( dwIDItem ) || HT_IS_ITEM_WEAR( dwIDItem ) )//fors_debug  離棺것컸몸꿎桿
	{
		// 메인 재련
		this->HT_hrDetachItemMainRefineEffect( idObj, dwIDItem );

		HTdword dwRefineID;
		switch ( iMainRefineLevel )
		{
		case 0  : case 1  : case 2 :	m_pResMgr->HT_bGetItemRifining012( dwIDItem, dwRefineID );  break;
		case 3  : case 4  : case 5 :	m_pResMgr->HT_bGetItemRifining345( dwIDItem, dwRefineID );  break;
		case 6  : case 7  : case 8 :	m_pResMgr->HT_bGetItemRifining678( dwIDItem, dwRefineID );  break;
		case 9  : case 10 :				m_pResMgr->HT_bGetItemRifining910( dwIDItem, dwRefineID );  break;
		case 11 : case 12 :				m_pResMgr->HT_bGetItemRifining1112( dwIDItem, dwRefineID ); break;
		case 13 :				m_pResMgr->HT_bGetItemRifining13( dwIDItem, dwRefineID ); break;
        case 14 :				m_pResMgr->HT_bGetItemRifining14( dwIDItem, dwRefineID ); break;
        case 15 :				m_pResMgr->HT_bGetItemRifining15( dwIDItem, dwRefineID ); break;
		default : return HT_FAIL;
		}
      //  if (iMainRefineLevel == 15) dwRefineID ++;
		HTvector3 vecScaleStart, vecScaleEnd;
		HTdword dwColorStart, dwColorEnd;
		HTfloat fStart2EndTime;

		if ( dwRefineID > 0 )
		{
			m_pResMgr->HT_bGetItemRifiningScaleColorTime( dwRefineID,
				vecScaleStart, vecScaleEnd, dwColorStart, dwColorEnd, fStart2EndTime );

			CHTString strSocket;
			m_pResMgr->HT_bGetSocketName( dwIDItem, strSocket );

			m_p3DMgr->HT_hrAttachObjectGlow( idObj, strSocket,
				HT_COLOR(dwColorStart), HT_COLOR(dwColorEnd), vecScaleStart, vecScaleEnd, fStart2EndTime );

			HTdword dwSecondItem;
			m_pResMgr->HT_bGetSecondSocketModelID( dwIDItem, dwSecondItem );

			if ( dwSecondItem > 0 )
			{
				strSocket = _T("RightClaw");
				m_p3DMgr->HT_hrAttachObjectGlow( idObj, strSocket,
					HT_COLOR(dwColorStart), HT_COLOR(dwColorEnd), vecScaleStart, vecScaleEnd, fStart2EndTime );
			}
		}
	}

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrAttachItemSubRefineEffect( HTint idObj, HTdword dwIDItem, HTESubRefineType eSubRefineType, HTint iSubRefineLevel )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_ITEM_WEAPON( dwIDItem ) )
	{
		// 서브 재련
		this->HT_hrDetachItemSubRefineEffect( idObj, dwIDItem );

		HT_SWORDWIND_TEXTURE_TYPE eSwordWindTextureType;
		HT_COLOR clrSwordWindColor;
		switch ( eSubRefineType )
		{
		case HT_SUBREFINETYPE_FIRE :		eSwordWindTextureType = HT_SWTEX_FIRE; break;
		case HT_SUBREFINETYPE_ICE :			eSwordWindTextureType = HT_SWTEX_ICE; break;
		case HT_SUBREFINETYPE_LIGHTING :	eSwordWindTextureType = HT_SWTEX_LIGHTING; break;
		case HT_SUBREFINETYPE_POISON :		eSwordWindTextureType = HT_SWTEX_POISION; break;
		default :							eSwordWindTextureType = HT_SWTEX_NONE;
		}

		switch ( iSubRefineLevel )
		{
		case 1  : clrSwordWindColor = HT_COLOR( 0.5f, 0.5f, 0.5f, 0.5f ); break;
		case 2  : clrSwordWindColor = HT_COLOR( 0.55f, 0.55f, 0.55f, 0.55f ); break;
		case 3  : clrSwordWindColor = HT_COLOR( 0.6f, 0.6f, 0.6f, 0.6f ); break;
		case 4  : clrSwordWindColor = HT_COLOR( 0.65f, 0.65f, 0.65f, 0.65f ); break;
		case 5  : clrSwordWindColor = HT_COLOR( 0.7f, 0.7f, 0.7f, 0.7f ); break;
		case 6  : clrSwordWindColor = HT_COLOR( 0.75f, 0.75f, 0.75f, 0.75f ); break;
		case 7  : clrSwordWindColor = HT_COLOR( 0.8f, 0.8f, 0.8f, 0.8f ); break;
		case 8  : clrSwordWindColor = HT_COLOR( 0.85f, 0.85f, 0.85f, 0.85f ); break;
		case 9  : clrSwordWindColor = HT_COLOR( 0.9f, 0.9f, 0.9f, 0.9f ); break;
		case 10 : clrSwordWindColor = HT_COLOR( 0.95f, 0.95f, 0.95f, 0.95f ); break;
		default : clrSwordWindColor = HT_COLOR( 0.40f, 0.40f, 0.40f, 0.40f ); eSwordWindTextureType = HT_SWTEX_NONE;
		}

		m_p3DMgr->HT_hrSetSwordWindTexture( idObj, eSwordWindTextureType );
		m_p3DMgr->HT_hrSetSwordWindColor( idObj, clrSwordWindColor );
	}

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrDetachItemMainRefineEffect( HTint idObj, HTdword dwIDItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_ITEM_WEAPON( dwIDItem ) )
	{
		CHTString strSocket;
		m_pResMgr->HT_bGetSocketName( dwIDItem, strSocket );
		m_p3DMgr->HT_hrDetachObjectGlow( idObj, strSocket );

		HTdword dwSecondItem;
		m_pResMgr->HT_bGetSecondSocketModelID( dwIDItem, dwSecondItem );

		if ( dwSecondItem > 0 )
		{
			strSocket = _T("RightClaw");
			m_p3DMgr->HT_hrDetachObjectGlow( idObj, strSocket );
		}
	}

	return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrDetachItemSubRefineEffect( HTint idObj, HTdword dwIDItem )
{
	if ( !this->HT_bGetCanModify( idObj ) ) return HT_FAIL;

	if ( HT_IS_ITEM_WEAPON( dwIDItem ) )
	{
		m_p3DMgr->HT_hrSetSwordWindTexture( idObj, HT_SWTEX_NONE );
		m_p3DMgr->HT_hrSetSwordWindColor( idObj, HT_COLOR( 0.40f, 0.40f, 0.40f, 0.40f ) );

		return HT_OK;
	}
	else
	{
		return HT_OK;
	}
}

HTvoid
CHTEngineHandler::HT_vSetBlind( HTint iMSTime, HTfloat fFogStart, HTfloat fFogEnd, HTfloat fFogColorR, HTfloat fFogColorG, HTfloat fFogColorB )
{
	m_oBlindEffect.bToBlind = HT_TRUE;

	if ( iMSTime > 0 ) m_oBlindEffect.fChangePerSecond = 1000.0f / (HTfloat)iMSTime;
	else m_oBlindEffect.fChangePerSecond = 0.001f;

	m_oBlindEffect.fChangeFogStart = fFogStart;
	m_oBlindEffect.fChangeFogEnd = fFogEnd;
	m_oBlindEffect.clrChangeFog = HT_COLOR( fFogColorR, fFogColorG, fFogColorB, 1.0f );
	m_oBlindEffect.fElapsedPercent = HT_EPSILON;
}

HTvoid
CHTEngineHandler::HT_vSetUnBlind( HTint iMSTime )
{
	m_oBlindEffect.bToBlind = HT_FALSE;

	if ( iMSTime > 0 ) m_oBlindEffect.fChangePerSecond = 1000.0f / (HTfloat)iMSTime;
	else m_oBlindEffect.fChangePerSecond = 0.001f;

	m_oBlindEffect.fElapsedPercent = HT_EPSILON;
}

HTRESULT CHTEngineHandler::HT_hrLoadToResPool( HTdword dwResID, HTbool bMapDefendent )
{
	if ( dwResID <= 0 )
		return ( HT_OK );

	CHTString strFile;
	HT_RES_POOL_DATA* pData = HT_NULL;
	HT_SHAREOBJ_TYPE eType;

	std::map<HTdword,HT_RES_POOL_DATA*>::iterator it = m_mapResPools.find( dwResID );
	if ( it != m_mapResPools.end() )
	{
		pData = it->second;
		if ( pData )
		{
			(pData->iRefCount)++;
		}
	}
	else
	{
		if ( m_pResMgr->HT_bGetFileName( dwResID, strFile ) )
		{
			CHTString strPath;
			if ( dwResID == HT_GODMARK_MODEL_BRAHMA || dwResID == HT_GODMARK_MODEL_SIVA || dwResID == HT_GODMARK_MODEL_VISUNU )
			{
				strPath = _T("resource\\object\\PC\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_RIGIDMODEL;
			}
			else if ( HT_IS_CHARACTERTMD( dwResID ) )
			{
				strPath = _T("resource\\object\\PC\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_SKINNEDMODEL;
			}
			else if ( HT_IS_CHARACTERMESHTMD( dwResID ) )
			{
				strPath = _T("resource\\object\\PC\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_SKINNEDMESH;
			}
			else if ( HT_IS_NPC_TMD( dwResID ) )
			{
				strPath = _T("resource\\object\\NPC\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_SKINNEDMODEL;
			}
			else if ( HT_IS_MONSTER_TMD( dwResID ) )
			{
				strPath = _T("resource\\object\\Monster\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_SKINNEDMODEL;
			}
			else if ( HT_IS_ITEM_TMD( dwResID ) )
			{
				strPath = _T("resource\\object\\Item\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_RIGIDMODEL;
			}
			else if ( HT_IS_CHARACTERANI( dwResID ) )
			{
				strPath = _T("resource\\object\\PC\\Ani");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_ANIMATION;
			}
			else if ( HT_IS_NPC_ANI( dwResID ) )
			{
				strPath = _T("resource\\object\\NPC\\Ani");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_ANIMATION;
			}
			else if ( HT_IS_MONSTER_ANI( dwResID ) )
			{
				strPath = _T("resource\\object\\Monster\\Ani");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_ANIMATION;
			}
			else return HT_FAIL;

			m_p3DMgr->HT_hrLoadObject( eType, dwResID, strFile );

			pData = new HT_RES_POOL_DATA;
			pData->eType = eType;
			pData->bMapDefendent = bMapDefendent;
			pData->iRefCount = 1;

			m_mapResPools.insert( std::map<HTdword,HT_RES_POOL_DATA*>::value_type( dwResID, pData ) );
		}
	}

	return ( HT_OK );
}

HTRESULT
CHTEngineHandler::HT_hrLoadToResPool4MonsterMesh( HTdword dwResID, HTbool bMapDefendent )
{
	if ( dwResID <= 0 )
		return ( HT_OK );

	CHTString strFile;
	HT_RES_POOL_DATA* pData = HT_NULL;
	HT_SHAREOBJ_TYPE eType;

	std::map<HTdword,HT_RES_POOL_DATA*>::iterator it = m_mapResPools.find( dwResID );
	if ( it != m_mapResPools.end() )
	{
		pData = it->second;
		if ( pData )
		{
			(pData->iRefCount)++;
		}
	}
	else
	{
		if ( m_pResMgr->HT_bGetFileName( dwResID, strFile ) )
		{
			CHTString strPath;
			if ( HT_IS_MONSTER_TMD( dwResID ) )
			{
				strPath = _T("resource\\object\\Monster\\Mesh");
				m_p3DMgr->HT_vSetResourcePath( strPath, strPath );
				eType = HT_SOBJTYPE_SKINNEDMESH;
			}
			else return HT_FAIL;

			m_p3DMgr->HT_hrLoadObject( eType, dwResID, strFile );

			pData = new HT_RES_POOL_DATA;
			pData->eType = eType;
			pData->bMapDefendent = bMapDefendent;
			pData->iRefCount = 1;

			m_mapResPools.insert( std::map<HTdword,HT_RES_POOL_DATA*>::value_type( dwResID, pData ) );
		}
	}

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnloadFromResPool( HTdword dwResID )
{
	if ( dwResID <= 0 )
		return ( HT_OK );

	HT_RES_POOL_DATA* pData = HT_NULL;
	std::map<HTdword,HT_RES_POOL_DATA*>::iterator it = m_mapResPools.find( dwResID );
	if ( it != m_mapResPools.end() )
	{
		pData = (it->second);

		if ( pData )
		{
			(pData->iRefCount)--;

			if ( pData->iRefCount > 0 )
				return ( HT_OK );
			else
			{
				pData->iRefCount = 0;	// 마이너스가 되는 것을 막는다.

				HTfloat fTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );

				std::map<HTdword,HTfloat>::iterator itWU = m_mapWaitUnloads.find( dwResID );
				if ( itWU != m_mapWaitUnloads.end() )
				{
					itWU->second = fTime;	// 최근 언로드 요청 시간으로 업데이트 시킨다
				}
				else
					m_mapWaitUnloads.insert( std::map<HTdword,HTfloat>::value_type( dwResID, fTime ) );
			}
		}
		else
			return ( HT_FAIL );
	}
	else
	{
		return ( HT_FAIL );
	}

	return ( HT_OK );
}

HTdword CHTEngineHandler::HT_dwGetPCSoundID1( HTdword dwTribe, HT_ANIM_STATE eState )
{
	HTdword dwSoundID = 0;

	switch( dwTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKSoundID1( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARSoundID1( eState, dwSoundID );
		break;
	}

	return ( dwSoundID );
}

HTdword CHTEngineHandler::HT_dwGetPCSoundID2( HTdword dwTribe, HT_ANIM_STATE eState )
{
	HTdword dwSoundID = 0;

	switch( dwTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKSoundID2( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARSoundID2( eState, dwSoundID );
		break;
	}

	return ( dwSoundID );
}

HTdword CHTEngineHandler::HT_dwGetPCSoundID3( HTdword dwTribe, HT_ANIM_STATE eState )
{
	HTdword dwSoundID = 0;

	switch( dwTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKSoundID3( eState, dwSoundID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARSoundID3( eState, dwSoundID );
		break;
	}

	return ( dwSoundID );
}

HTdword CHTEngineHandler::HT_dwGetMonsterAniID( HTdword dwResID, HT_ANIM_STATE eState )
{
	HTdword dwAnimID = 0;

	switch( eState ) 
	{
	case HT_ANISTATE_STD:
		m_pResMgr->HT_bGetSTDAniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_WLK:
		m_pResMgr->HT_bGetWLKAniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_IDL:
		m_pResMgr->HT_bGetIDLAniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_RUN:
		m_pResMgr->HT_bGetRUNAniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_ATK_1:
		m_pResMgr->HT_bGetATK1AniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_ATK_2:
		m_pResMgr->HT_bGetATK2AniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_HIT:
		m_pResMgr->HT_bGetHITAniID( dwResID, dwAnimID );
		break;
	case HT_ANISTATE_DIE:
		m_pResMgr->HT_bGetDIEAniID( dwResID, dwAnimID );
		break;
	default:
		break;
	}

	return ( dwAnimID );
}

HTdword CHTEngineHandler::HT_dwGetRandomSoundID( HTdword dwSound1, HTdword dwSound2, HTdword dwSound3 )
{
	// 만약 사운드가 여러개가 나왔다면 그중에서 랜덤으로 하나를 선택한다.
	// 여기서 쓰이는 사운드의 랜덤은 클라이언트 사이에 동기화가 되지 않아도 된다고 가정한다.
	HTint iSoundCount = 0;
	HTdword dwSelectSound = 0;
	if ( dwSound1 > 0 )		iSoundCount += 1;
	if ( dwSound2 > 0 )		iSoundCount += 2;
	if ( dwSound3 > 0 )		iSoundCount += 4;

	HTint iMod;
	if ( iSoundCount == 0 )	// 사운드가 없으면 0을 전달하여 틀지 말라고 한다.
	{
		dwSelectSound = 0;
	}
	else if ( iSoundCount == 1 )	// 
	{
		dwSelectSound = dwSound1;
	}
	else if ( iSoundCount == 2 )	// 
	{
		dwSelectSound = dwSound2;
	}
	else if ( iSoundCount == 4 )	// 
	{
		dwSelectSound = dwSound3;
	}
	else if ( iSoundCount == 3 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwSound1;
		else				dwSelectSound = dwSound2;
	}
	else if ( iSoundCount == 5 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwSound1;
		else				dwSelectSound = dwSound3;
	}
	else if ( iSoundCount == 6 )	// 
	{
		iMod = rand() % 2;
		if ( iMod == 0 )	dwSelectSound = dwSound2;
		else				dwSelectSound = dwSound3;
	}
	else if ( iSoundCount == 7 )	// 
	{
		iMod = rand() % 3;
		if ( iMod == 0 )		dwSelectSound = dwSound1;
		else if ( iMod == 1 )	dwSelectSound = dwSound2;
		else					dwSelectSound = dwSound3;
	}

	return ( dwSelectSound );
}

HTdword CHTEngineHandler::HT_dwGetHeadID( HTdword dwTribe, HTint idHead )
{
	HTdword dwIDHead = 0;
	switch( idHead )
	{
	case HT_HEAD_TYPE_A:
		m_pResMgr->HT_bGetHeadTypeAID( dwTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_B:
		m_pResMgr->HT_bGetHeadTypeBID( dwTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_C:
		m_pResMgr->HT_bGetHeadTypeCID( dwTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_D:
		m_pResMgr->HT_bGetHeadTypeDID( dwTribe, dwIDHead );
		break;
	case HT_HEAD_TYPE_E:
		m_pResMgr->HT_bGetHeadTypeEID( dwTribe, dwIDHead );
		break;
	default:
		m_pResMgr->HT_bGetHeadTypeAID( dwTribe, dwIDHead );
		break;
	}

	return ( dwIDHead );
}

HTdword CHTEngineHandler::HT_dwGetFApronAnimID( HTdword dwTribe, HT_ANIM_STATE eState )
{
	HTdword dwAnimID = 0;
	switch( dwTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKFApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARFApronAnimID( eState, dwAnimID );
		break;
	}

	return ( dwAnimID );
}

HTdword CHTEngineHandler::HT_dwGetBApronAnimID( HTdword dwTribe, HT_ANIM_STATE eState )
{
	HTdword dwAnimID = 0;
	switch( dwTribe )
	{
	case HT_ID_CHARACTER_NAGA:
		m_pResMgr->HT_bGetNAGBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_YAKSA:
		m_pResMgr->HT_bGetYAKBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_ASURA:
		m_pResMgr->HT_bGetASUBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_DEVA:
		m_pResMgr->HT_bGetDEVBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_KIMNARA:
		m_pResMgr->HT_bGetKIMBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GANDHARVA:
		m_pResMgr->HT_bGetGANBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_RAKSHASA:
		m_pResMgr->HT_bGetRAKBApronAnimID( eState, dwAnimID );
		break;
	case HT_ID_CHARACTER_GARUDA:
		m_pResMgr->HT_bGetGARBApronAnimID( eState, dwAnimID );
		break;
	}

	return ( dwAnimID );
}

HTdword CHTEngineHandler::HT_dwGetMonsterSoundID( HTdword dwFXMonID, HT_ANIM_STATE eState )
{
	HTdword dwMotionSoundID1, dwMotionSoundID2;
	dwMotionSoundID1 = dwMotionSoundID2 = 0;

	switch( eState ) 
	{
	case HT_ANISTATE_WLK:
		m_pResMgr->HT_bGetMonWalkSoundID( dwFXMonID, dwMotionSoundID1 );
		break;
	case HT_ANISTATE_IDL:
		m_pResMgr->HT_bGetMonIdleSoundID( dwFXMonID, dwMotionSoundID1 );
		break;
	case HT_ANISTATE_RUN:
		m_pResMgr->HT_bGetMonRunSoundID( dwFXMonID, dwMotionSoundID1 );
		break;
	case HT_ANISTATE_ATK_1:
		m_pResMgr->HT_bGetMonAttackSoundID1( dwFXMonID, dwMotionSoundID1 );
		m_pResMgr->HT_bGetMonAttackSoundID2( dwFXMonID, dwMotionSoundID2 );
		break;
	case HT_ANISTATE_ATK_2:
		m_pResMgr->HT_bGetMonAttackSoundID1( dwFXMonID, dwMotionSoundID1 );
		m_pResMgr->HT_bGetMonAttackSoundID2( dwFXMonID, dwMotionSoundID2 );
		break;
	case HT_ANISTATE_HIT:
		m_pResMgr->HT_bGetMonHitSoundID( dwFXMonID, dwMotionSoundID1 );
		m_pResMgr->HT_bGetMonHit2SoundID( dwFXMonID, dwMotionSoundID2 );
		break;
	case HT_ANISTATE_DIE:
		m_pResMgr->HT_bGetMonDieSoundID( dwFXMonID, dwMotionSoundID1 );
		break;
	default:
		break;
	}

	if ( dwMotionSoundID2 > 0 )
	{
		if ( rand() % 2 == 0 )
		{
			return ( dwMotionSoundID1 );
		}
		else
		{
			return ( dwMotionSoundID2 );
		}
	}
	else
	{
		return ( dwMotionSoundID1 );
	}
}

HTRESULT CHTEngineHandler::HT_hrLoadWeaponItemAnim( HTint idObj, HTint idTribe, HTint idItem )
{
	//----------------------------------------------------------------------------------------
	// Load Animation
	HTdword dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;

	if ( idItem <= 0 )	// 아이템을 안 들고 있으면
		dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
	else
	{
		// 먼저 아이템을 보고 그것의 타입을 참조하여 어떤 공격 에니를 틀 것인지 결정한다.
		if ( !m_pResMgr->HT_bGetItemType( idItem, dwItemType ) )
			dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
	}

	// 공격 동작의 경우 남녀로 구분하여 처리한다.
	HTdword dwAnimID1, dwAnimID2, dwAnimID3;
	dwAnimID1 = dwAnimID2 = dwAnimID3 = 0;
	HTdword dwFAnimID1, dwFAnimID2, dwFAnimID3;
	dwFAnimID1 = dwFAnimID2 = dwFAnimID3 = 0;
	HTdword dwBAnimID1, dwBAnimID2, dwBAnimID3;
	dwBAnimID1 = dwBAnimID2 = dwBAnimID3 = 0;
	if ( HT_IS_PC_MAN( idTribe ) )
	{
		m_pResMgr->HT_bGetManAnim1ID( dwItemType, dwAnimID1 );
		m_pResMgr->HT_bGetManAnim2ID( dwItemType, dwAnimID2 );
		m_pResMgr->HT_bGetManAnim3ID( dwItemType, dwAnimID3 );

		m_pResMgr->HT_bGetManFApronAnimID1( dwItemType, dwFAnimID1 );
		m_pResMgr->HT_bGetManFApronAnimID2( dwItemType, dwFAnimID2 );
		m_pResMgr->HT_bGetManFApronAnimID3( dwItemType, dwFAnimID3 );

		m_pResMgr->HT_bGetManBApronAnimID1( dwItemType, dwBAnimID1 );
		m_pResMgr->HT_bGetManBApronAnimID2( dwItemType, dwBAnimID2 );
		m_pResMgr->HT_bGetManBApronAnimID3( dwItemType, dwBAnimID3 );
	}
	else
	{
		m_pResMgr->HT_bGetWomAnim1ID( dwItemType, dwAnimID1 );
		m_pResMgr->HT_bGetWomAnim2ID( dwItemType, dwAnimID2 );
		m_pResMgr->HT_bGetWomAnim3ID( dwItemType, dwAnimID3 );

		m_pResMgr->HT_bGetWomFApronAnimID1( dwItemType, dwFAnimID1 );
		m_pResMgr->HT_bGetWomFApronAnimID2( dwItemType, dwFAnimID2 );
		m_pResMgr->HT_bGetWomFApronAnimID3( dwItemType, dwFAnimID3 );

		m_pResMgr->HT_bGetWomBApronAnimID1( dwItemType, dwBAnimID1 );
		m_pResMgr->HT_bGetWomBApronAnimID2( dwItemType, dwBAnimID2 );
		m_pResMgr->HT_bGetWomBApronAnimID3( dwItemType, dwBAnimID3 );
	}

	HT_hrLoadToResPool( dwAnimID1, HT_FALSE );
	HT_hrLoadToResPool( dwAnimID2, HT_FALSE );
	HT_hrLoadToResPool( dwAnimID3, HT_FALSE );
	HT_hrLoadToResPool( dwFAnimID1, HT_FALSE );
	HT_hrLoadToResPool( dwFAnimID2, HT_FALSE );
	HT_hrLoadToResPool( dwFAnimID3, HT_FALSE );
	HT_hrLoadToResPool( dwBAnimID1, HT_FALSE );
	HT_hrLoadToResPool( dwBAnimID2, HT_FALSE );
	HT_hrLoadToResPool( dwBAnimID3, HT_FALSE );

	m_mapItemIndex.insert( std::multimap<HTint,HTdword>::value_type( idObj, idItem ) );

	return ( HT_OK );
}

HTRESULT CHTEngineHandler::HT_hrUnloadWeaponItemAnim( HTint idObj, HTint idItem )
{
	// tribe id를 찾는다
	HTint idTribe = 0;
	std::map<HTint,HTdword>::iterator it = m_mapModelIndex.find( idObj );
	if ( it != m_mapModelIndex.end() )
	{
		idTribe = it->second;
	}
	else
	{
		return ( HT_FAIL );
	}

	// item idx를 찾는다
	std::multimap<HTint,HTdword>::iterator itItem = m_mapItemIndex.begin();
	while ( itItem != m_mapItemIndex.end() )
	{
		if ( itItem->first == idObj )
		{
			idItem = itItem->second;

			HTdword dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;

			if ( idItem <= 0 )	// 아이템을 안 들고 있으면
				dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
			else
			{
				// 먼저 아이템을 보고 그것의 타입을 참조하여 어떤 공격 에니를 틀 것인지 결정한다.
				if ( !m_pResMgr->HT_bGetItemType( idItem, dwItemType ) )
					dwItemType = HT_ANISTATE_ATK_LEATHER_MATIALART_WEAPON;
			}

			// 공격 동작의 경우 남녀로 구분하여 처리한다.
			HTdword dwAnimID1, dwAnimID2, dwAnimID3;
			dwAnimID1 = dwAnimID2 = dwAnimID3 = 0;
			HTdword dwFAnimID1, dwFAnimID2, dwFAnimID3;
			dwFAnimID1 = dwFAnimID2 = dwFAnimID3 = 0;
			HTdword dwBAnimID1, dwBAnimID2, dwBAnimID3;
			dwBAnimID1 = dwBAnimID2 = dwBAnimID3 = 0;
			if ( HT_IS_PC_MAN( idTribe ) )
			{
				m_pResMgr->HT_bGetManAnim1ID( dwItemType, dwAnimID1 );
				m_pResMgr->HT_bGetManAnim2ID( dwItemType, dwAnimID2 );
				m_pResMgr->HT_bGetManAnim3ID( dwItemType, dwAnimID3 );

				m_pResMgr->HT_bGetManFApronAnimID1( dwItemType, dwFAnimID1 );
				m_pResMgr->HT_bGetManFApronAnimID2( dwItemType, dwFAnimID2 );
				m_pResMgr->HT_bGetManFApronAnimID3( dwItemType, dwFAnimID3 );

				m_pResMgr->HT_bGetManBApronAnimID1( dwItemType, dwBAnimID1 );
				m_pResMgr->HT_bGetManBApronAnimID2( dwItemType, dwBAnimID2 );
				m_pResMgr->HT_bGetManBApronAnimID3( dwItemType, dwBAnimID3 );
			}
			else
			{
				m_pResMgr->HT_bGetWomAnim1ID( dwItemType, dwAnimID1 );
				m_pResMgr->HT_bGetWomAnim2ID( dwItemType, dwAnimID2 );
				m_pResMgr->HT_bGetWomAnim3ID( dwItemType, dwAnimID3 );

				m_pResMgr->HT_bGetWomFApronAnimID1( dwItemType, dwFAnimID1 );
				m_pResMgr->HT_bGetWomFApronAnimID2( dwItemType, dwFAnimID2 );
				m_pResMgr->HT_bGetWomFApronAnimID3( dwItemType, dwFAnimID3 );

				m_pResMgr->HT_bGetWomBApronAnimID1( dwItemType, dwBAnimID1 );
				m_pResMgr->HT_bGetWomBApronAnimID2( dwItemType, dwBAnimID2 );
				m_pResMgr->HT_bGetWomBApronAnimID3( dwItemType, dwBAnimID3 );
			}

			HT_hrUnloadFromResPool( dwAnimID1 );
			HT_hrUnloadFromResPool( dwAnimID2 );
			HT_hrUnloadFromResPool( dwAnimID3 );
			HT_hrUnloadFromResPool( dwFAnimID1 );
			HT_hrUnloadFromResPool( dwFAnimID2 );
			HT_hrUnloadFromResPool( dwFAnimID3 );
			HT_hrUnloadFromResPool( dwBAnimID1 );
			HT_hrUnloadFromResPool( dwBAnimID2 );
			HT_hrUnloadFromResPool( dwBAnimID3 );

			itItem = m_mapItemIndex.erase( itItem );
		}
		else
			itItem++;
	}

	return ( HT_OK );
}


HTRESULT CHTEngineHandler::HT_hrLoadObjResMgr( HTdword dwMapID )
{
	CHTString strObjResName;
	strObjResName.HT_hrCleanUp();
	m_pResMgr->HT_bGetObjResFilesName( dwMapID, strObjResName );

	if (strObjResName!=m_strObjResName)
	{
		HT_DELETE ( m_pObjResMgr );
		m_pObjResMgr = new CHTObjResMgr;

		m_strObjResName = strObjResName;

		strObjResName = _SYSTEM_DIR + strObjResName;
		m_pObjResMgr->HT_hrLoad( strObjResName );
		return HT_OK;
	}
	return HT_FAIL;
}

HTbool
CHTEngineHandler::HT_bGetNearestShoot( HTvector3 vecChar, HTfloat& fRetDist, HTvector3& vecShootPos )
{
	if (m_pMapSystem)
		return m_pMapSystem->HT_bGetNearestShoot(vecChar, fRetDist, vecShootPos);

	return FALSE;
}

HTint
CHTEngineHandler::HT_iGetNumFlocking()
{
	return (HTint)m_vectorFlocking.size();
}

HTvoid
CHTEngineHandler::HT_vGetBaseFlockingInfo( HTint index, HTdword* pdwNPC, HTvector3* pvecBasePos )
{
	if ( index >= 0 && index < (HTint)m_vectorFlocking.size() )
	{
		*pdwNPC = m_vectorFlocking[index].dwNPCID;
		*pvecBasePos = m_vectorFlocking[index].vecPos;
	}
	else
	{
		*pdwNPC = 0;
		*pvecBasePos = HTvector3( 0.0f, 0.0f, 0.0f );
	}
}

HTvoid
CHTEngineHandler::HT_vReleaseBaseFlockingInfo()
{
	m_vectorFlocking.clear();
}

HTdword
CHTEngineHandler::HT_dwGetFootSound( HTvector3 vecChar, HTint iStatus)
{	
	HTint iMapStatus = m_pMapSystem->HT_iGetMapStatus(vecChar);
	return m_pResMgr->HT_dwGetFootSound(28301, iMapStatus, iStatus);
}

#ifndef HT_IS_TANTRA_LAUNCHER
HTvoid
CHTEngineHandler::HT_vRestartFieldFX()
{
	std::map<HTint, HT_MAP_SAVEOBJ*>::iterator it;
	it = m_pMapSystem->m_mapSaveObjs.begin();
	while ( it != m_pMapSystem->m_mapSaveObjs.end() )
	{
		HT_MAP_SAVEOBJ* pSaveObj = it->second;
		if ( pSaveObj && pSaveObj->idRenewal != 0 )
		{
			if ( pSaveObj->oProperty.iDayFXID > 0 && pSaveObj->oProperty.iNightFXID > 0 )
				this->HT_hrStartFieldFX( &(pSaveObj->idDayFX), pSaveObj->oProperty.iDayFXID, pSaveObj->idRenewal, HT_TRUE, HT_FX_WHEN_ALWAYS );
			else if ( pSaveObj->oProperty.iDayFXID > 0 )
				this->HT_hrStartFieldFX( &(pSaveObj->idDayFX), pSaveObj->oProperty.iDayFXID, pSaveObj->idRenewal, HT_TRUE, HT_FX_WHEN_DAY );
			else if ( pSaveObj->oProperty.iNightFXID > 0 )
				this->HT_hrStartFieldFX( &(pSaveObj->idNightFX), pSaveObj->oProperty.iNightFXID, pSaveObj->idRenewal, HT_TRUE, HT_FX_WHEN_NIGHT );
		}

		it++;
	}
}
#endif

#ifdef HT_IS_TANTRA_LAUNCHER
HTint
CHTEngineHandler::HT_iGetGoingPotal(HTdword dwID, HTint iNo, HTdword& dwFee, HTdword& dwLevel)
{
	HTint iGoPortal;
	if( g_pParamMgr->HT_bGetGoingPortal(dwID, iNo, &iGoPortal, &dwFee, &dwLevel))
		return iGoPortal ; 
	else
		return 0;
}

HTbool
CHTEngineHandler::HT_bGetPotalName(HTdword dwID, CHTString* strName)
{	
	if( g_pParamMgr->HT_bGetPortalName(dwID, strName)) return HT_TRUE;
	return HT_FALSE;
}

HTdword
CHTEngineHandler::HT_dwGetPortalFee(HTdword dwFrom, HTdword dwTo)
{
	HTdword dwFee;
	if( g_pParamMgr->HT_bGetPortalFee(dwFrom, dwTo, &dwFee)) return dwFee;

	return 0;
}

HTdword
CHTEngineHandler::HT_dwGetPortalLevel(HTdword dwFrom, HTdword dwTo)
{
	HTdword dwLevel;
	if( g_pParamMgr->HT_bGetPortalLevel(dwFrom, dwTo, &dwLevel)) return dwLevel;


	return 0;

}

HTvoid
CHTEngineHandler::HT_vSetStreamVolume(HTfloat fVolume)
{
	m_fStreamVolume = fVolume;
}

HTdword
CHTEngineHandler::HT_dwGetAffectionFXID( HTqword qwCurAffectionID, HTqword qwPreAffectionID )
{
	HTint iPrePriority = 100;

	if ( qwPreAffectionID & eTNVSAfn_HaveKalaCore ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_BlessOfGod ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Damage ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Stun ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Fire ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Cold ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Lightning ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Poison ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Hold ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_MagicShield ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_EnhancedMagicShield )  iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_ManaShield ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_ReflectDamage ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Invulnerable ) iPrePriority = 1;
	else if ( qwPreAffectionID & eTNVSAfn_Hold2 ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_MoveSpeedMinus ) iPrePriority = 2;
	//else if ( qwPreAffectionID & eTNVSAfn_MoveSpeed140R ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_ProtectAll ) iPrePriority = 2;
	//else if ( eTNVSAfn_MoveSpeed140R == qwPreAffectionID) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_MoveSpeedPlus ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_Sleep ) iPrePriority = 2;
	//else if ( qwPreAffectionID & eTNVSAfn_FireDamagePlus ) iPrePriority = 2;
	//else if ( qwPreAffectionID & eTNVSAfn_ColdDamagePlus ) iPrePriority = 2;
	//else if ( qwPreAffectionID & eTNVSAfn_LightningDamagePlus ) iPrePriority = 2;
	//else if ( qwPreAffectionID & eTNVSAfn_PoisonDamagePlus ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_AttackSpeedPlus ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_AttackSpeedMinus ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_ProtectFromPK ) iPrePriority = 2;
	else if ( qwPreAffectionID & eTNVSAfn_Blind ) iPrePriority = 3;
	else if ( qwPreAffectionID & eTNVSAfn_Invisible ) iPrePriority = 1;	//fors_debug old 3 
	else if ( qwPreAffectionID & eTNVSAfn_Weakness ) iPrePriority = 4;
	else if ( qwPreAffectionID & eTNVSAfn_RecoverTP ) iPrePriority = 4;	
	else iPrePriority = 10;

	// Current
	switch ( iPrePriority )
	{
	case 1 :
		{
			// Current Priority 1
			if ( qwCurAffectionID & eTNVSAfn_HaveKalaCore ) return 1010059;
			else if ( qwCurAffectionID & eTNVSAfn_BlessOfGod ) return 1010061;
			else if ( qwCurAffectionID & eTNVSAfn_Damage ) return 1010037;
			else if ( qwCurAffectionID & eTNVSAfn_Stun ) return	1010006;
			else if ( qwCurAffectionID & eTNVSAfn_Cold ) return 1010039;
			else if ( qwCurAffectionID & eTNVSAfn_Lightning ) return 1010040;
			else if ( qwCurAffectionID & eTNVSAfn_Poison ) return 1010041;
			else if ( qwCurAffectionID & eTNVSAfn_Fire ) return	1010038;			
			else if ( qwCurAffectionID & eTNVSAfn_Hold ) return	1010036;
			else if ( qwCurAffectionID & eTNVSAfn_MagicShield ) return 1010045;
			else if ( qwCurAffectionID & eTNVSAfn_EnhancedMagicShield ) return 1010071;
			else if ( qwCurAffectionID & eTNVSAfn_ManaShield ) return 1010047;
			else if ( qwCurAffectionID & eTNVSAfn_ReflectDamage ) return 1010048;
			else if ( qwCurAffectionID & eTNVSAfn_Invulnerable ) return 0;
			else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0; //fors_debug 茶�盞턴�
		}	break;
	case 2:
		{
			// Current Priority 1
			if ( qwCurAffectionID & eTNVSAfn_HaveKalaCore ) return 1010059;
			else if ( qwCurAffectionID & eTNVSAfn_BlessOfGod ) return 1010061;
			else if ( qwCurAffectionID & eTNVSAfn_Damage ) return 1010037;
			else if ( qwCurAffectionID & eTNVSAfn_Stun ) return	1010006;
			else if ( qwCurAffectionID & eTNVSAfn_Cold ) return 1010039;
			else if ( qwCurAffectionID & eTNVSAfn_Lightning ) return 1010040;
			else if ( qwCurAffectionID & eTNVSAfn_Poison ) return 1010041;
			else if ( qwCurAffectionID & eTNVSAfn_Fire ) return	1010038;
			else if ( qwCurAffectionID & eTNVSAfn_Hold ) return	1010036;
			else if ( qwCurAffectionID & eTNVSAfn_MagicShield ) return 1010045;
            else if ( qwCurAffectionID & eTNVSAfn_EnhancedMagicShield ) return 1010071;
			else if ( qwCurAffectionID & eTNVSAfn_ManaShield ) return 1010047;
			else if ( qwCurAffectionID & eTNVSAfn_ReflectDamage ) return 1010048;
			else if ( qwCurAffectionID & eTNVSAfn_Invulnerable ) return 0;
            else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;          
			// Current Priority 2
			else if ( qwCurAffectionID & eTNVSAfn_Hold2 ) return 1010046;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedMinus ) return 1010054;
			else if ( qwCurAffectionID & eTNVSAfn_Sleep ) return 1010035;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedPlus )
				{
				// if (g_oMainCharacterInfo.byLevel != 140)	//qwCurAffectionID = eTNVSAfn_MoveSpeed140R;fors_debug 녁곪洸땍鞫刻，섬깎譚와빵똥털뙤
				  return 1010075;//1010075  1010091(no fight 140) 1010090 (zone 1 10 140) 1010071 침제뜀
			//	 else 
			//	  return 1010090;
				}
            else if ( qwCurAffectionID & eTNVSAfn_ProtectAll ) return 1010090;
			//	eTNVSAfn_MoveSpeed140B			= 0x00600000,
	//eTNVSAfn_MoveSpeed140R			= 0x00500000,
			//else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140R ) return 1010090;
           // else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140B ) return 1010091;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromAttackOnlyOnce ) return 1010067;
			//else if ( qwCurAffectionID & eTNVSAfn_FireDamagePlus ) return 1010049;
			//else if ( qwCurAffectionID & eTNVSAfn_ColdDamagePlus ) return 1010050;
			//else if ( qwCurAffectionID & eTNVSAfn_LightningDamagePlus ) return 1010051;
			//else if ( qwCurAffectionID & eTNVSAfn_PoisonDamagePlus ) return 1010052;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedPlus ) return 1010055;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedMinus ) return 1010056;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromPK ) return 0;
        //    else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0; //fors_debug 茶�盞턴�
			
		}	break;
	case 3:
		{
			// Current Priority 1
			if ( qwCurAffectionID & eTNVSAfn_HaveKalaCore ) return 1010059;
			else if ( qwCurAffectionID & eTNVSAfn_BlessOfGod ) return 1010061;
			else if ( qwCurAffectionID & eTNVSAfn_Damage ) return 1010037;
			else if ( qwCurAffectionID & eTNVSAfn_Stun ) return	1010006;
			else if ( qwCurAffectionID & eTNVSAfn_Cold ) return 1010039;
			else if ( qwCurAffectionID & eTNVSAfn_Lightning ) return 1010040;
			else if ( qwCurAffectionID & eTNVSAfn_Poison ) return 1010041;
			else if ( qwCurAffectionID & eTNVSAfn_Fire ) return	1010038;
			else if ( qwCurAffectionID & eTNVSAfn_Hold ) return	1010036;
			else if ( qwCurAffectionID & eTNVSAfn_MagicShield ) return 1010045;
			else if ( qwCurAffectionID & eTNVSAfn_EnhancedMagicShield ) return 1010071;
			else if ( qwCurAffectionID & eTNVSAfn_ManaShield ) return 1010047;
			else if ( qwCurAffectionID & eTNVSAfn_ReflectDamage ) return 1010048;
			else if ( qwCurAffectionID & eTNVSAfn_Invulnerable ) return 0;
            else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;

			// Current Priority 2
			else if ( qwCurAffectionID & eTNVSAfn_Hold2 ) return 1010046;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedMinus ) return 1010054;
			else if ( qwCurAffectionID & eTNVSAfn_Sleep ) return 1010035;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedPlus )
				{
				// if (g_oMainCharacterInfo.byLevel != 140)	//qwCurAffectionID = eTNVSAfn_MoveSpeed140R;fors_debug 녁곪洸땍鞫刻，섬깎譚와빵똥털뙤
				  return 1010075;//1010075  1010091(no fight 140) 1010090 (zone 1 10 140)
			//	 else 
			//	  return 1010090;
				}
            else if ( qwCurAffectionID & eTNVSAfn_ProtectAll ) return 1010090;
			//else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140R ) return 1010090;
            //else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140B ) return 1010091;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromAttackOnlyOnce ) return 1010067;
			//else if ( qwCurAffectionID & eTNVSAfn_ColdDamagePlus ) return 1010050;
			//else if ( qwCurAffectionID & eTNVSAfn_LightningDamagePlus ) return 1010051;
			//else if ( qwCurAffectionID & eTNVSAfn_PoisonDamagePlus ) return 1010052;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedPlus ) return 1010055;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedMinus ) return 1010056;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromPK ) return 0;
        //    else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;
			// Current Priority 3
			else if ( qwCurAffectionID & eTNVSAfn_Blind ) return 1010043;
         //   else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;			
		}	break;
	case 4: default :
		{
			// Current Priority 1
			if ( qwCurAffectionID & eTNVSAfn_HaveKalaCore ) return 1010059;
			else if ( qwCurAffectionID & eTNVSAfn_BlessOfGod ) return 1010061;
			else if ( qwCurAffectionID & eTNVSAfn_Damage ) return 1010037;
			else if ( qwCurAffectionID & eTNVSAfn_Stun ) return	1010006;
			else if ( qwCurAffectionID & eTNVSAfn_Cold ) return 1010039;
			else if ( qwCurAffectionID & eTNVSAfn_Lightning ) return 1010040;
			else if ( qwCurAffectionID & eTNVSAfn_Poison ) return 1010041;
			else if ( qwCurAffectionID & eTNVSAfn_Fire ) return	1010038;
			else if ( qwCurAffectionID & eTNVSAfn_Hold ) return	1010036;
			else if ( qwCurAffectionID & eTNVSAfn_MagicShield ) return 1010045;
			else if ( qwCurAffectionID & eTNVSAfn_EnhancedMagicShield ) return 1010071;
			else if ( qwCurAffectionID & eTNVSAfn_ManaShield ) return 1010047;
			else if ( qwCurAffectionID & eTNVSAfn_ReflectDamage ) return 1010048;
			else if ( qwCurAffectionID & eTNVSAfn_Invulnerable ) return 0;
            else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;

			// Current Priority 2
			else if ( qwCurAffectionID & eTNVSAfn_Hold2 ) return 1010046;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedMinus ) return 1010054;
			else if ( qwCurAffectionID & eTNVSAfn_Sleep ) return 1010035;
			else if ( qwCurAffectionID & eTNVSAfn_MoveSpeedPlus )
				{
				// if (g_oMainCharacterInfo.byLevel != 140)	//qwCurAffectionID = eTNVSAfn_MoveSpeed140R;fors_debug 녁곪洸땍鞫刻，섬깎譚와빵똥털뙤
				  return 1010075;//1010075  1010091(no fight 140) 1010090 (zone 1 10 140)
			//	 else 
			//	  return 1010090;
				}
            else if ( qwCurAffectionID & eTNVSAfn_ProtectAll ) return 1010090;
			//else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140R ) return 1010090;
         //   else if ( qwCurAffectionID & eTNVSAfn_MoveSpeed140B ) return 1010091;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromAttackOnlyOnce ) return 1010067;
			//else if ( qwCurAffectionID & eTNVSAfn_ColdDamagePlus ) return 1010050;
			//else if ( qwCurAffectionID & eTNVSAfn_LightningDamagePlus ) return 1010051;
			//else if ( qwCurAffectionID & eTNVSAfn_PoisonDamagePlus ) return 1010052;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedPlus ) return 1010055;
			else if ( qwCurAffectionID & eTNVSAfn_AttackSpeedMinus ) return 1010056;
			else if ( qwCurAffectionID & eTNVSAfn_ProtectFromPK ) return 0;
            //else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;
			// Current Priority 3
			else if ( qwCurAffectionID & eTNVSAfn_Blind ) return 1010043;
			//else if ( qwCurAffectionID & eTNVSAfn_Invisible ) return 0;

			// Current Priority 4
			else if ( qwCurAffectionID & eTNVSAfn_Weakness ) return 1010062;
			else if ( qwCurAffectionID & eTNVSAfn_RecoverTP ) return 0;			
		}
	}

	return 0;
}

#endif


//	Open Web
HRESULT CHTEngineHandler::JK_hrWebMgr_SetOpenWeb( int iIndex, HWND hWnd, char* szURL, int iSecondToWait, int iLeft, int iTop, int iWidth, int iHight )
{
	//	Open Web
	if( !m_pWebBrowser )
	{
		//	웹브라우져를 지위기위해서 클라이언트에 창을 뛰운다.
		g_cUIManager->HT_ShowWindow( _DIALOG_WEBBROWSER );

		m_pWebBrowser		= NULL;
		m_hWndExplorer		= NULL;

		CoInitialize( NULL );
		if(FAILED( CoCreateInstance( CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, 
										IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser )))
		{
			return E_FAIL;
		}
		m_pWebBrowser->put_AddressBar( VARIANT_FALSE );
		m_pWebBrowser->put_FullScreen( VARIANT_FALSE );
		m_pWebBrowser->put_MenuBar( VARIANT_FALSE );
		m_pWebBrowser->put_StatusBar( VARIANT_FALSE );
		m_pWebBrowser->put_ToolBar( VARIANT_FALSE );
		m_pWebBrowser->put_Visible( VARIANT_FALSE );		
		// Capture Explorer HWND 
		m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" );
		if( m_hWndExplorer == NULL )
		{
			return E_FAIL;
		}
		::SetWindowLong( m_hWndExplorer, GWL_STYLE, WS_POPUP );
		::SetParent( m_hWndExplorer, hWnd );

		Sleep( 100 );
		SetFocus( hWnd );

		VARIANT var;
		var.vt = VT_I4;
		var.lVal = 0;

		VARIANT vURL = {0};
		BSTR bstrURL = _com_util::ConvertStringToBSTR(szURL);
		V_VT(&vURL) = VT_BSTR;
		V_BSTR(&vURL) = bstrURL;
		m_pWebBrowser->Navigate( bstrURL, &var, &var, &var, &var );
		if ( bstrURL ) SysFreeString(bstrURL);

		int i = 0;
		VARIANT_BOOL varBool;
		do
		{
			++i;
			Sleep( 100 );
			m_pWebBrowser->get_Busy( &varBool );
		} while ( varBool && i < (iSecondToWait * 10) );

		if ( i >= (iSecondToWait * 10) )
		{
			if ( m_pWebBrowser )
			{
				return E_FAIL;
			}
		}
		else
		{
			SetWindowPos( m_hWndExplorer, NULL, iLeft, iTop, iWidth, iHight, SWP_SHOWWINDOW );
			m_pWebBrowser->put_Visible( VARIANT_TRUE );
		}
	}

	SetFocus( hWnd );

	return S_OK;
}


HTRESULT
CHTEngineHandler::HT_hrOpenWeb( HWND hWnd, CHTString& strURL, HTint iSecondToWait )
{
	if ( !m_pWebBrowser )
	{
		//	웹브라우져를 지위기위해서 클라이언트에 창을 뛰운다.
		g_cUIManager->HT_ShowWindow( _DIALOG_WEBBROWSER );

		if ( FAILED( CoInitialize( HT_NULL ) ) )
		{
			// 타니 결제 서버 연결을 위한 프로그램 초기화에 실패했습니다.
			return 1;
			//return HT_FAIL;
		}

		// Instantiate a browser 
		if ( FAILED( CoCreateInstance( CLSID_InternetExplorer, HT_NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser ) ) )
		{
			// 타니 결제 서버 연결 초기화에 실패했습니다.
			this->HT_hrCloseWeb();
			return 2;
			//return HT_FAIL;
		}

		m_pWebBrowser->put_AddressBar( VARIANT_FALSE );
		m_pWebBrowser->put_FullScreen( VARIANT_FALSE );
		m_pWebBrowser->put_MenuBar( VARIANT_FALSE );
		m_pWebBrowser->put_StatusBar( VARIANT_FALSE );
		m_pWebBrowser->put_ToolBar( VARIANT_FALSE );
		m_pWebBrowser->put_Visible( VARIANT_FALSE );
		//m_pWebBrowser->put_Resizable( VARIANT_FALSE );

		// Capture Explorer HWND 
		if ( ( m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" ) ) == NULL )
		{
			// 타니 결제 서버 연결을 위한 프로그램 검색에 실패했습니다.
			this->HT_hrCloseWeb();
			return 3;
			//return HT_FAIL;
		}

		::SetWindowLong( m_hWndExplorer, GWL_STYLE, WS_CHILD );
		::SetParent( m_hWndExplorer, hWnd );

		VARIANT var;
		var.vt = VT_I4;
		var.lVal = 0;

		_bstr_t bstrURL( (HTtchar*)strURL );
		m_pWebBrowser->Navigate( bstrURL, &var, &var, &var, &var );

		HTint i = 0;
		VARIANT_BOOL varBool;
		do
		{
			++i;
			Sleep( 100 );
			m_pWebBrowser->get_Busy( &varBool );
		} while ( varBool && i < (iSecondToWait * 10) );

		if ( i >= (iSecondToWait * 10) )
		{
			this->HT_hrCloseWeb();
			return HT_FAIL;
		}
		else
		{
			//m_pWebBrowser->put_Width( m_iScreenWidth );
			//m_pWebBrowser->put_Height( m_iScreenHeight-50 );
			//m_pWebBrowser->put_Left( 0 );
			//m_pWebBrowser->put_Top( 0 );
			//m_pWebBrowser->put_FullScreen( VARIANT_TRUE );
			SetWindowPos( m_hWndExplorer, NULL, 0, 0, m_iScreenWidth, m_iScreenHeight-50, SWP_SHOWWINDOW );
			m_pWebBrowser->put_Visible( VARIANT_TRUE );

			return HT_OK;
		}
	}
	else return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrOpenWebWithPost( HWND hWnd, CHTString& strURL, CHTString& strPost, HTint iSecondToWait )
{
	if ( m_pWebBrowser )
        this->HT_hrCloseWeb();

	if ( !m_pWebBrowser )
	{
		if ( FAILED( CoInitialize( HT_NULL ) ) )
		{
			// 타니 결제 서버 연결을 위한 프로그램 초기화에 실패했습니다.
			return 1;
			//return HT_FAIL;
		}

		// Instantiate a browser 
		if ( FAILED( CoCreateInstance( CLSID_InternetExplorer, HT_NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser ) ) )
		{
			// 타니 결제 서버 연결 초기화에 실패했습니다.
			this->HT_hrCloseWeb();
			return 2;
			//return HT_FAIL;
		}

		m_pWebBrowser->put_Visible( VARIANT_FALSE );
		m_pWebBrowser->put_AddressBar( VARIANT_FALSE );
		m_pWebBrowser->put_MenuBar( VARIANT_FALSE );
		m_pWebBrowser->put_StatusBar( VARIANT_FALSE );
		m_pWebBrowser->put_ToolBar( VARIANT_FALSE );
		m_pWebBrowser->put_Resizable( VARIANT_FALSE );

		// Capture Explorer HWND 
		if ( ( m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" ) ) == NULL )
		{
			// 타니 결제 서버 연결을 위한 프로그램 검색에 실패했습니다.
			this->HT_hrCloseWeb();
			return 3;
			//return HT_FAIL;
		}

		::SetWindowLong( m_hWndExplorer, GWL_STYLE, WS_POPUP );
		::SetParent( m_hWndExplorer, hWnd );

		VARIANT vFlags = {0}, vTargetFrameName = {0}, vPostData = {0}, vHeaders = {0};

		BSTR bstrHeaders = NULL;
		_bstr_t bstrURL( (HTtchar*)strURL );
		bstrHeaders = ::SysAllocString( L"Content-Type: application/x-www-form-urlencoded\r\n" );
		V_VT(&vHeaders) = VT_BSTR;
		V_BSTR(&vHeaders) = bstrHeaders;

		// Post Data
		// MSDN에서 http://support.microsoft.com/kb/167658/EN-US/ (Article ID : 167658)을 참조하여 구현
		LPSAFEARRAY psa;
		LPCTSTR cszPostData = (HTtchar*)strPost;
		UINT cElems = lstrlen( cszPostData );
		LPSTR pPostData;

		VariantInit( &vPostData );
		psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
		SafeArrayAccessData( psa, (LPVOID*)&pPostData );
		memcpy( pPostData, cszPostData, cElems );
		SafeArrayUnaccessData( psa );
		V_VT( &vPostData ) = VT_ARRAY | VT_UI1;
		V_ARRAY( &vPostData ) = psa;
		// Post Data

		m_pWebBrowser->Navigate( bstrURL, &vFlags, &vTargetFrameName, &vPostData, &vHeaders );

		if ( bstrHeaders ) SysFreeString(bstrHeaders);
		VariantClear( &vPostData );

		HTint i = 0;
		VARIANT_BOOL varBool;
		do
		{
			++i;
			Sleep( 100 );
			m_pWebBrowser->get_Busy( &varBool );
		} while ( varBool && i < (iSecondToWait * 10) );

		if ( i >= (iSecondToWait * 10) )
		{
			this->HT_hrCloseWeb();
			return HT_FAIL;
		}
		else
		{
			m_pWebBrowser->put_Width( m_iScreenWidth );
			m_pWebBrowser->put_Height( m_iScreenHeight );
			m_pWebBrowser->put_Left( 0 );
			m_pWebBrowser->put_Top( 0 );
			//			m_pWebBrowser->put_FullScreen( VARIANT_TRUE );
			m_pWebBrowser->put_Visible( VARIANT_TRUE );

			return HT_OK;
		}
	}
	else return HT_OK;
}

HTRESULT
CHTEngineHandler::HT_hrCloseWeb()
{
	//	웹브라우져를 지위기위해서 클라이언트에 창을 뛰운다. 그리고 지운다.
	g_cUIManager->HT_HideWindow( _DIALOG_WEBBROWSER );

	if ( m_pWebBrowser )
	{
		m_pWebBrowser->Quit();
		m_pWebBrowser->Release();

		m_pWebBrowser = HT_NULL;
		m_hWndExplorer = HT_NULL;

		return HT_OK;
	}
	else return HT_FAIL;
}

#ifdef HT_IS_TANTRA_LAUNCHER

HTRESULT
CHTEngineHandler::HT_hrClearWebCookies()
{
	if ( m_pWebBrowser ) this->HT_hrCloseWeb();

	if ( FAILED( CoInitialize( HT_NULL ) ) ) return HT_FAIL; 
	if ( FAILED( CoCreateInstance( CLSID_InternetExplorer, HT_NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser ) ) ) return HT_FAIL;

	m_pWebBrowser->put_Visible( VARIANT_FALSE );
	m_pWebBrowser->put_AddressBar( VARIANT_FALSE );
	m_pWebBrowser->put_MenuBar( VARIANT_FALSE );
	m_pWebBrowser->put_StatusBar( VARIANT_FALSE );
	m_pWebBrowser->put_ToolBar( VARIANT_FALSE );
	m_pWebBrowser->put_Resizable( VARIANT_FALSE );

	// Capture Explorer HWND 
	if ( ( m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" ) ) == NULL ) return HT_FAIL;

	::SetWindowLong( m_hWndExplorer, GWL_STYLE, WS_POPUP );

	VARIANT var;
	var.vt = VT_I4;
	var.lVal = 0;

	// 아래 사이트에 접속하면 혹시 사용되었던 결제 관련 쿠키를 지워주는 효과가 있다.
	CHTString strTemp; 
	HT_g_Script_SetMessage( eURLGMlogout, &strTemp, _T("") );
	_bstr_t bstrURL( strTemp.HT_szGetString() );
	m_pWebBrowser->Navigate( bstrURL, &var, &var, &var, &var );

	HTint i = 0;
	VARIANT_BOOL varBool;
	do
	{
		++i;
		Sleep( 100 );
		m_pWebBrowser->get_Busy( &varBool );
	} while ( varBool && i < 30 );
	
	HT_g_Script_SetMessage( eURLGMlogout2, &strTemp, _T("") );
	strTemp.HT_szFormat(strTemp, g_strLoginID.HT_szGetString());
	_bstr_t bstrURL2( strTemp.HT_szGetString() );
	m_pWebBrowser->Navigate( bstrURL2, &var, &var, &var, &var );


	HTint i2 = 0;
	VARIANT_BOOL varBool2;
	do
	{
		++i2;
		Sleep( 100 );
		m_pWebBrowser->get_Busy( &varBool2 );
	} while ( varBool2 && i2 < 30 );

	m_pWebBrowser->put_Width( 10 );
	m_pWebBrowser->put_Height( 10 );
	m_pWebBrowser->put_Left( 0 );
	m_pWebBrowser->put_Top( 0 );

	m_pWebBrowser->Quit();
	m_pWebBrowser->Release();

	m_pWebBrowser = HT_NULL;
	m_hWndExplorer = HT_NULL;

	return HT_OK;
}

#endif

HTRESULT
CHTEngineHandler::HT_hrSetGuildCastleMark( HTdword dwGMarkUL, HTdword dwGMarkUR, HTdword dwGMarkLL, HTdword dwGMarkLR )
{
	m_oGuildCastleInfo.dwGMarkUL = dwGMarkUL;
	m_oGuildCastleInfo.dwGMarkUR = dwGMarkUR;
	m_oGuildCastleInfo.dwGMarkLL = dwGMarkLL;
	m_oGuildCastleInfo.dwGMarkLR = dwGMarkLR;

	// 만약 이미 화면에 뿌려지고 있는 Object 중에 바꾸어야 할 것이 있다면 여기서 바꿔줘야 한다.
	std::map<HTint,HT_MAP_SAVEOBJ*>::iterator it = m_pMapSystem->m_mapSaveObjs.begin();
	while ( it != m_pMapSystem->m_mapSaveObjs.end() )
	{
		HT_MAP_SAVEOBJ* pObj = it->second;
		if ( m_dwCurrentMapID == HT_FORTWAR_MAP_ID && pObj )
		{
			if ( pObj->dwResID == HT_FORTWAR_GUILD_FLAG_RESID )
			{
				HTdword dwGuildMark = 0;
				HTvector3 vecPos( pObj->matTransform._41, pObj->matTransform._42, pObj->matTransform._43 );
				if ( vecPos.x > 3160.0f && vecPos.x < 7000.0f && vecPos.z > 3160.0f && vecPos.z < 7000.0f )
				{	// 위, 우측 : UR
					if ( m_oGuildCastleInfo.dwGMarkUR != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkUR;
				}

				if ( vecPos.x > 0.0f && vecPos.x < 3160.0f && vecPos.z > 3160.0f && vecPos.z < 7000.0f )
				{	// 위, 좌측 : UL
					if ( m_oGuildCastleInfo.dwGMarkUL != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkUL;
				}

				if ( vecPos.x > 3160.0f && vecPos.x < 7000.0f && vecPos.z > 0.0f && vecPos.z < 3160.0f )
				{	// 아래, 우측 : LR
					if ( m_oGuildCastleInfo.dwGMarkLR != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkLR;
				}

				if ( vecPos.x > 0.0f && vecPos.x < 3160.0f && vecPos.z > 0.0f && vecPos.z < 3160.0f )
				{	// 아래, 좌측 : LL
					if ( m_oGuildCastleInfo.dwGMarkLL != 0 ) dwGuildMark = m_oGuildCastleInfo.dwGMarkLL;
				}

				if ( dwGuildMark > 0 )
				{	// 마크가 바꾸어주면 된다.
					HTdword dwGuildEmblem	= (dwGuildMark & 0x000000FF);
					HTdword dwGuildTitle	= (dwGuildMark & 0x0000FF00) >> 8;
					HTdword dwGuildColor	= (dwGuildMark & 0x00FF0000) >> 16;

					if ( dwGuildEmblem < 1 || dwGuildEmblem > 72 || dwGuildTitle < 1 || dwGuildTitle > 84 || dwGuildColor < 1 || dwGuildColor > 72 )
					{
					}
					else
					{
						CHTString strGuildTitle;
						HTdword dwColor;
						m_pResMgr->HT_bGetGuildTitleTex( dwGuildTitle + HT_ID_GUILDMARK_TITLE_START - 1, strGuildTitle );
						m_pResMgr->HT_bGetGuildEmblemDWColor( dwGuildColor + HT_ID_GUILDMARK_COLOR_START - 1, dwColor );

						if ( pObj->idRenewal > 0 ) m_p3DMgr->HT_hrSet2GuildMark( pObj->idRenewal, dwGuildEmblem, strGuildTitle, dwColor );
					}
				}
				else
				{	// 길드 마크가 붙어 있었는데 지금은 없어진 경우이므로 렌더링이 안되게 한다.
					m_p3DMgr->HT_hrUnset2GuildMark( pObj->idRenewal );
				}
			}
		}
		it++;
	}

	return HT_OK;
}