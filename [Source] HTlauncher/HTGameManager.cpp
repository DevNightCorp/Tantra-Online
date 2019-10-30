
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTGameManager.h"
#include "DES.h"
//#include"HideProcess.h"

#define TIMEOUT_INIT_CHARACTER			500000		// 서버에서 캐릭터 초기화 정보를 기다리는 시간
#define WAITTIME_INIT_CHARACTER			10000		// 캐릭터 정보가 오지 않았을 경우 게임을 끝내는 시간
#define WAITTIME_NETWORK_CONNECTION		10000		// 네트워크 연결이 끊어졌을 경우 게임을 끝내는 시간

#define _MAINUI_SYS_FILE_NAME	_T("resource\\UI\\MainUIInfo.sys")		// 인트로 관련 구성 파일 이름
#define _MAINUI_SAVE_FILE_NAME	_T("resource\\UI\\MainUISave.sys")		// 인트로 관련 구성 파일 이름

#define _PARAMETER_FILE_NAME	_T("system\\TantraParam.tpa")		// Monster, Item Parameter 파일
#define _REAL_PARAMETER_FILE_NAME  _T("resource\\fx\\fxPCTree.tfx")
#define _MESSAGE_FILE_NAME		_T("system\\HTMessage.txl")

HTbool	m_bServerConnectCheck;

CHTGameManager::CHTGameManager()
{
}

CHTGameManager::~CHTGameManager()
{
}

//	게임 전체를 통틀어 로딩해 두어야 할 떄
HTRESULT CHTGameManager::HT_hrGMInit()
{
	//	Set Game Sequnce
	g_iGameBigSequnce = GAMESEQUNCEBIG_INTRO;
	//  우리의 숙원사업 ReStart
	g_byReStartCode = 0;
	g_byReStartButtonCode = 0;
	m_dwReStartRemainTime = 15000;

	//----------메인게임 루프 한번만 업데이트----------//
	g_bOneTimeUpdate				= GAMESEQUNCE_MAINGAME_NONE;

	//----------네트웍 초기화----------//
	g_pNetMsg						= NULL;
	g_pNetMsg						= new CHTNetworkMsg;
	//----------네트웍 초기화----------//

	//-----카메라를 초기화 시켜준다-----//
	g_cCamera.HT_CameraInit();

	//----------에디터 파일 생성 및 로딩----------//
    g_pParamMgr						= HT_NULL;
	g_pParamMgr						= new CHTClientParamMgr;

	CHTString streFile = _PARAMETER_FILE_NAME;
    CHTString strFile = _REAL_PARAMETER_FILE_NAME;

/*    api
char szFp[]="system\\TantraParam.tpa";
 //memcpy(szFp,(LPCTSTR)streFile,0);
HANDLE hfile;
hfile = CreateFile(
   szFp,         //匡숭쨌쓺
   GENERIC_READ,    //뚤匡숭돨꾸鱗잚謹
   FILE_SHARE_READ,      //匡숭댔역렘駕
   NULL,         //갛홍橄昑
   OPEN_EXISTING,       //눼쉔샀림맨
   FILE_ATTRIBUTE_NORMAL,     //흔벎눼쉔，橙꽝鑒槨匡숭橄昑
   NULL         //轟친겼
);

long lFileLen=GetFileSize(hfile,NULL);
long c=lFileLen/8;
long d=lFileLen%8;

char szRealFp[]="resource\\fx\\fxPCTree.tfx";
 //memcpy(szFp,(LPCTSTR)streFile,0);
HANDLE hRfile;
hRfile = CreateFile(
   szRealFp,         //匡숭쨌쓺
   GENERIC_WRITE|GENERIC_READ,    //뚤匡숭돨꾸鱗잚謹
   FILE_SHARE_READ,      //匡숭댔역렘駕
   NULL,         //갛홍橄昑
   OPEN_ALWAYS,       //눼쉔샀림맨
   FILE_ATTRIBUTE_NORMAL,     //흔벎눼쉔，橙꽝鑒槨匡숭橄昑
   NULL         //轟친겼
);
SetFilePointer(hfile,0,NULL,FILE_BEGIN);
SetFilePointer(hRfile,0,NULL,FILE_BEGIN);
DES jm;
char inbuff[8]={NULL},oubuff[8]={NULL},skey[8]={NULL};
itoa(23830,skey,10);
//CHTString m_filekey=_T("23830");
// memcpy(skey,(LPCTSTR)m_filekey,8);
for(long i=0;i<c;i++)
	{
		   DWORD dwReadSize = 0;
          ReadFile(hfile,inbuff,8,&dwReadSize,NULL);

		
        jm.Des_Go(oubuff, inbuff, sizeof(inbuff), skey,sizeof(skey), DECRYPT);
//		fp.HT_bWrite(oubuff,8);
          DWORD dwWritenSize = 0;
        WriteFile(hRfile,oubuff,8,&dwWritenSize,NULL);
		 
	}
 FlushFileBuffers(hRfile);
CloseHandle(hfile);
CloseHandle(hRfile); */
////to enc
/*
	CHTFile ff;
	ff.HT_bOpen(streFile,HT_FILEOPT_BINARY | HT_FILEOPT_READONLY);
	long lFileLen=ff.HT_dwGetLength();
long c=lFileLen/8;
long d=lFileLen%8;

   CHTFile fp;
   fp.HT_bOpen(strFile,HT_FILEOPT_BINARY | HT_FILEOPT_READWRITE);
   fp.HT_vSeekToBegin();
   ff.HT_vSeekToBegin();
DES jm;
char inbuff[8],oubuff[8],skey[8];

//itoa(23830,skey,10); 
CHTString tkey;
tkey=_T("23830");
memcpy(skey,(LPCTSTR)tkey,8);

	for(long i=0;i<c;i++)
	{
		ff.HT_bRead(inbuff,8);
		jm.Des_Go(oubuff, inbuff, sizeof(inbuff), skey,sizeof(skey), ENCRYPT);
		fp.HT_bWrite(oubuff,8);
	}
	if(d>0)
	{
		ff.HT_bRead(inbuff,d);
		jm.Des_Go(oubuff, inbuff, sizeof(inbuff), skey,sizeof(skey), ENCRYPT);
		fp.HT_bWrite(oubuff,8);
	}
*/
//////  to dec

	CHTFile ff;
	ff.HT_bOpen(streFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY);
	long lFileLen= ff.HT_dwGetLength();
long c=lFileLen/8;
long d=lFileLen%8;



   CHTFile fp;
   fp.HT_bOpen(strFile,HT_FILEOPT_BINARY | HT_FILEOPT_READWRITE);
   fp.HT_vSeekToBegin();
   ff.HT_vSeekToBegin();

//CString inbuff;


DES jm;

char inbuff[8]={NULL},oubuff[8]={NULL},skey[8]={NULL};

//itoa(23830,skey,10);
CHTString tkey;
tkey=_T("23830");
memcpy(skey,(LPCTSTR)tkey,8);

for(long i=0;i<c;i++)
	{
		ff.HT_bRead(inbuff,8);
		
        jm.Des_Go(oubuff, inbuff, sizeof(inbuff), skey,sizeof(skey), DECRYPT);
		fp.HT_bWrite(oubuff,8);
	}

 
//fors_debug to 썩쵱
	ff.HT_vClose();
	fp.HT_vClose(); 

	g_pParamMgr->HT_bLoad(strFile);

	//----------게임 내 메세지-----------//
	g_pMessageMgr					= HT_NULL;
	g_pMessageMgr					= new CHTMessageMgr;

	strFile = _MESSAGE_FILE_NAME;
	g_pMessageMgr->HT_bLoad(strFile);

	//	서버 리스트를 연결시켜줌
	g_pNetWorkMgr->InitNetworkManager();

	//----------기본적인 게임 정보 로딩----------//
	g_BasicLoadingInfo				= HT_NULL;
	g_BasicLoadingInfo				= new HTInfoLoad;

	//----------로딩 시스템 인터페이스 INIT----------//
	g_cLoading						= HT_NULL;
	g_cLoading						= new CHTLoading;	

	//----------게임 인터페이스 INIT----------//
	g_cInterfaceCheck				= HT_NULL;
	g_cInterfaceCheck				= new CHTInterfaceCheck;
	g_cInterfaceCheck->HT_hrInterfaceInit();
	
	//----------디버깅 버튼 초기셋팅----------//
	g_button_count					= 0;
	//----------헬프 폰트 셋팅----------//
	g_bHelp_Text					= HT_FALSE;

	//----------메인게임 랜더 결정----------//
	g_bMainCharacterInitialized		= HT_FALSE;

	//----------타이머 셋팅----------//
	m_cGMTimer						= NULL;
	m_cGMTimer						= new CHTTimer;
	m_cGMTimer->Do( HT_TIMER_START );

	// 존 서버 전환을 체크한다.
	m_bServerConnectCheck = HT_FALSE;
	//	서버 연결 끊어졌는지 체크한다.
	m_bZoneServerDisConnectCheck = HT_FALSE;

	//	플레이 동영상_Global
	g_bGamePlayMovieForGlobal		= HT_FALSE;
	g_bUseEngineCamera				= HT_FALSE;
	g_bGoAttackCamera				= HT_FALSE;

	//	핑하기 위해
	m_bRequestCharPingDelay			= GetTickCount();
	//	Bot Check
	m_bBotCheckDelay				= timeGetTime();
    DeleteFile("resource\\fx\\fxPCTree.tfx"); //fors_debug 攣駕랙꼈侶쟁狼唐槻，겉썩쵱匡숭혼딜
	//HideProcess();
	return ( HT_OK );
}

//-----GM 데이타 클린업 하기-----//
HTvoid CHTGameManager::HT_vGMDataCleanUp()
{
	// AOI 클리어
	HT_DELETE( g_cAoi );
	
	// 에디터 파일 클리어
	HT_DELETE( g_pParamMgr );

	// 메세지 : EngineHandler 에서 ClearCokies 에서 g_pMessageMgr 을 호출한다. 따라서 먼저 호출한다.
	if( g_iInationalType == INATIONALTYPE_KOREA )
        g_pEngineHandler->HT_hrClearWebCookies();
	HT_DELETE( g_pMessageMgr );

	// 기본적인 게임 정보 클리어
	HT_DELETE( g_BasicLoadingInfo );
	//-----NPC 시스템 클리어-----//
	if ( g_sNPCSystem ) g_sNPCSystem->HT_vNPCSystem_CleanUp();
	HT_DELETE( g_sNPCSystem );

	//	OtherObject Clear
	if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_TotalObjectDelete();
	HT_DELETE( g_cOtherObjectSystem );

	//-----게임 인터페이스 클리어-----//
	if( g_cInterfaceCheck ) g_cInterfaceCheck->HT_vCHTInterfaceCheck_CleanUp();
	HT_DELETE( g_cInterfaceCheck );

	if ( g_cUIManager ) g_cUIManager->HT_vSaveDialogPos(_INTERFACE_SAVE_FILE_NAME);

	//----------퀵스킬 세이브----------//
	if ( g_iGameSequnce == 2 ) g_cQuickSlot->HT_vIconSave();
	//-----메인캐릭터 클리어-----//
	if ( g_cMainCharacter ) g_cMainCharacter->HT_vMainChar_CleanUp();
	HT_DELETE( g_cMainCharacter );
	//----------공격/Hit 시스템 클리어----------//
	HT_DELETE( g_cAttackMgr );
	HT_DELETE( g_cHitCountMgr );
	//	Web Login
	HT_DELETE(g_poWebLogIn);

	// Game System 클리어
	if ( g_cGameSystem ) g_cGameSystem->HT_vGSDataCleanUp();
	HT_DELETE( g_cGameSystem );
	// Main UI System 클리어
	
	//	플로킹 시스템
	if ( g_pFlocking ) HT_DELETE( g_pFlocking );
	//	Timer CleanUp
	HT_DELETE( m_cGMTimer );

	// V3 에서 새로 추가된 윈도우들... (v2 버전보다 먼저 읽어들여야 한다. v2버전에서 v3버전 함수를 사용하므로...)
	HT_DELETE( g_cUINPCWindow );
	HT_DELETE( g_cUIStatus );
	HT_DELETE( g_cUISkillWindow );
	HT_DELETE( g_cUIQuestWindow );
	HT_DELETE( g_cUIMerchantWindow );
	HT_DELETE( g_cUIRefineWindow );
	HT_DELETE( g_cUIEmblemWindow );

	// Tantra3 UI Class 제거
	HT_DELETE( g_cUIManager );
}

// Map을 Load, Unload
HTvoid CHTGameManager::HT_vCleanUpGameDataForPortal()
{
	//	현재 돌아가고 있는 쿨타임을 전부 초기화 해준다.
	g_cQuickSlot->HT_vTotalCoolTimeInit();

	//	캐릭터 클린업
	g_cMainCharacter->HT_vMainChar_CleanUp();

	//	OtherObject Clear
	g_cOtherObjectSystem->HT_vOtherObjectSystem_TotalObjectDelete();

	//	NPC 전부 클리어
	g_sNPCSystem->HT_vNPCSystem_TotalNPCDelete();

	//	아이템/스킬 전부를 삭제
	g_cItemSystem->HT_vItemSystem_TotalItemDelete();
	g_cSkillSystem->HT_vSkillSystem_TotalSkillDelete();

	//	미니맵 삭제
	g_cMiniMap->HT_vMiniMap_MoveMap_Init();
	g_cMiniMap->HT_vMinMap_CeleanUp();

	//	파티 삭제
	if( g_cParty )			
	{
		g_cUIManager->HT_DeleteWindow( _DIALOG_PARTYWND );
		g_cParty->HT_vParty_Init();
	}

	//	길드 삭제
	if( g_cGuildSystem )	g_cGuildSystem->HT_vGuild_Delete();

	//	주소록 초기화
	g_cAddress->HT_vAddress_Delete();

	//-----스킬 시스템 생성-----//
	g_cSkillSystem->HT_hSkillSystemInit();
	//-----스킬 인벤토리 생성-----//
	g_cSkillInventory->HT_hrSkillInventoryInit();
	//	내가걸려있는 스킬 초기화
	g_pMainBar->HT_vMainBar_MySkillInit();
	//	PK Button 이 켜져 있다면 PK Button 초기화
	if( g_pMainBar->HT_bGetPKButton() )
        g_pMainBar->HT_vMainBar_GameSystem_SetForPKButton();

	if( g_cParty )
		g_cParty->HT_vParty_CleanUp();
}

HTvoid CHTGameManager::HT_vCleanUpGameDataForReStart()
{
	//	Delete Aoi
	HT_DELETE( g_cAoi );
	//	Delete HitSystem
	HT_DELETE( g_cHitCountMgr );
	//	Delete Attack Mgr
	HT_DELETE( g_cAttackMgr );
	//	Delete OtherObjectSystem
	g_cOtherObjectSystem->HT_vOtherObjectSystem_TotalObjectDelete();
	HT_DELETE( g_cOtherObjectSystem );
	//	Delete NPC System
	g_sNPCSystem->HT_vNPCSystem_CleanUp();
	HT_DELETE( g_sNPCSystem );
	//	Delete MainCharacter
	g_cMainCharacter->HT_vMainChar_CleanUp();
	HT_DELETE( g_cMainCharacter );
	//	Delete Equip System
	HT_DELETE( g_cEquipSystem );
	//	Delete System
	if ( g_cGameSystem ) g_cGameSystem->HT_vGSDataCleanUp();
	HT_DELETE( g_cGameSystem );
	//	Delete Main UI System & Main UI VertexBuffer
	g_pEngineHandler->HT_hrClearUISpriteVB();
	//	Delete Flocking
	//HT_DELETE( g_pFlocking );
	//	Delete Unload Map
	if (g_cLoading) g_cLoading->HT_hrUnloadMap();

	// V3 에서 새로 추가된 윈도우들... (v2 버전보다 먼저 읽어들여야 한다. v2버전에서 v3버전 함수를 사용하므로...)
	HT_DELETE( g_cUINPCWindow );
	HT_DELETE( g_cUIStatus );
	HT_DELETE( g_cUISkillWindow );
	HT_DELETE( g_cUIQuestWindow );
	HT_DELETE( g_cUIMerchantWindow );
	HT_DELETE( g_cUIRefineWindow );
	HT_DELETE( g_cUIEmblemWindow );

	// UIManager 제거
	HT_DELETE( g_cUIManager);

	// 주요 렌더링 리소스를 다시 할당할 필요가 있다. 여기서 한다.
	g_pEngineHandler->HT_hrCheckScreen();

	//	메인게임 랜더 결정
	g_bMainCharacterInitialized		= HT_FALSE;
	//	메인게임 루프 한번만 업데이트
	g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_NONE;
    //	Set Game Sequnce
	g_iGameSequnce = 0;
}

//---------메인게임 직전에 이니트 해야 할 부분----------//
HTvoid CHTGameManager::HT_hrMainLoopBeforeInit()
{
	// MainUI ClientRes Setting (Tantra V3)
	// Tantra V3 UI 적용
	HT_DELETE( g_cUIManager);
	g_cUIManager = new CHTUIManager;

	int iScreenWidth, iScreenHeight;
	iScreenWidth = g_pEngineHandler->HT_iGetScreenWidth();
	iScreenHeight = g_pEngineHandler->HT_iGetScreenHeight();
	g_cUIManager->HTSetGameEnvironment(iScreenWidth, iScreenHeight, g_iInationalType, g_gServerType, g_bDevelopingMode, 1);

	//-----게임 시스템 생성-----//
	g_cGameSystem		= HT_NULL;
	g_cGameSystem		= new CHTGameSystem;
	g_cGameSystem->HT_hrGameSystemInit();

	//-----장착 시스템 생성-----//
	g_cEquipSystem					= HT_NULL;
	g_cEquipSystem					= new HTEquipSystem;

	//----------메인캐릭터----------//
	g_cMainCharacter				= HT_NULL;
	g_cMainCharacter				= new HTMainCharacter;
	g_cMainCharacter->HT_hrMainCharInitVariable();

    //-----NPC 시스템 생성-----//
	g_sNPCSystem = new HTNPCSystem;
	g_sNPCSystem->HT_hNPCSystemInit();

	//	OtherObject 생성
	g_cOtherObjectSystem = new HTOtherObjectSystem;
	g_cOtherObjectSystem->HT_vOtherObjectSystem_Init();

	//-----공격 클래스 생성-----//
	g_cAttackMgr = HT_NULL;
	g_cAttackMgr = new HTAttackManager;

	//-----Hit 클래스 생성-----//
	g_cHitCountMgr = HT_NULL;
	g_cHitCountMgr = new HitCountMgr;
	
	//-----AOI 시스템 생성-----//
	if( !g_cAoi )
	{
		g_cAoi = NULL;
		g_cAoi = new HTAOI;
	}
	g_cAoi->HT_AOI_Init();

	//  설명 : 우리의 숙원사업 ReStart를 다시 0으로 셋팅
	g_byReStartCode = 0;
	g_byReStartButtonCode = 0;

	// 여기서 모든 윈도우를 읽어왔다면 해당 예전 저장위치로 이동
	CHTString	strFileName;
	strFileName = _INTERFACE_SAVE_FILE_NAME;
	g_cUIManager->HT_vOpenDialogPos(strFileName);
}


//----------클래스 비우기----------//
HTvoid CHTGameManager::HT_hrMainGameDestory()
{
}

//---------인트로 업데이트----------//
HTRESULT CHTGameManager::HT_hrReadyGameControl()
{
	HTRESULT hr = HT_OK;

	//----------캐릭터가 살아 있음을 서버에 계속 알림----------//
	this->HT_vMainGame_RequestCharPing();

	//	Elapsed 시간 구하기
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	m_cGMTimer->Do( HT_TIMER_RESET );

    //	인트로 컨트롤
	if( g_cIntroManager )
		hr = g_cIntroManager->HT_hrUpdate( m_fElapsedTime );
			
	return hr;
}

//---------인트로 랜드링----------//
HTRESULT CHTGameManager::HT_hrRender_Ready()
{
	// If D3Device losted stop rendering!
	if(HT_hrBeforeRender() != HT_OK)
		return HT_OK;

	// 렌더링: 내부에서 현재 상태에 따라 분기한다.
	g_cIntroManager->HT_hrRender();

	HT_hrAfterRender();
	return ( HT_OK );
}

//----------메인게임 루프 한번만 업데이트----------//
HTvoid CHTGameManager::HT_vMainGame_OneTimetUpdate()
{
	if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_RECEIVEINITCHAR )
	{
		g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_DONEINITCHAR;

		HTvector3 vecPos;
        //----------초기화----------//
		vecPos = g_cMainCharacter->HT_vecGetPosition();
        g_cCamera.HT_vCamera_SetOneTimeInit( vecPos.y );
		
		m_bRequestCharPingDelay = GetTickCount();
		m_bBotCheckDelay		= timeGetTime();
		g_pNetWorkMgr->RequestCharPing();

		//	카메라 고정
		g_cCamera.HT_vUpdateLook_SetPositon( vecPos );
		vecPos.x += 5;
		vecPos.y += 10;
		vecPos.z += 5;
		g_cCamera.HT_vUpdateEye_SetPositon( vecPos );

		//	카메라 초기화
		g_cCamera.HT_vCamera_SetInitMainGameCamera();

		//	카메라 게임 스타트 연출
		vecPos = g_cMainCharacter->HT_vecGetPosition();
		g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STARTGAMEPLAY, vecPos, 1, 0.8f);
		vecPos.x += 0.0f;
		vecPos.y += 70.0f; 
		vecPos.z += 100;
		g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STARTGAMEPLAY, vecPos, 1, 0.8f);
	}
	else
		return;
}

//---------게임시작 셋팅----------//
HTvoid CHTGameManager::HT_vSetStartMainGamePlay()
{
	g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_GMAEPLAY;

	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.5f);
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.5f);

	//	캐릭터 한번만 업데이트
	g_cMainCharacter->HT_vMainChar_OneTimeUpdate();

	//	Elapsed 시간 구하기
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	m_cGMTimer->Do( HT_TIMER_RESET );

	//	죽어서 태어나는 캐릭터 체크
	if( g_byIsDeadInit == 1 )
	{
		g_cGameSystem->HT_vGameSystem_NetWorkInitCharDeath();
	}
}

//=====   메인 게임에서 - 업데이트  =====//
HTRESULT CHTGameManager::HT_hrMainGameControl()
{
	//	Elapsed 시간 구하기
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	g_cInterfaceCheck->HT_vInterface_SetElapsedTime( m_fElapsedTime );
	m_cGMTimer->Do( HT_TIMER_RESET );

	if( !g_bMainCharacterInitialized )
		return HT_OK;

	//  설명 : 우리의 숙원사업 ReStart를 Check
	if( g_byReStartCode != 0 )
	{
		HTdword dwPassTime = GetTickCount();
		m_dwReStartRemainTime = dwPassTime - m_dwReStartStartTime;
		//	아예 게임 End라면 전체 게임데이타를 삭제하고
        if( g_byReStartCode == 3 )
		{
			if( dwPassTime > m_dwReStartStartTime + 500 )
			{
				this->HT_vGMDataCleanUp();
				return RETURNTYPE_EXIT_MAINGAME;
			}
		}
		//	그 외의 경우라면 일부만(거의 전체지만) 삭제한다.
		else if( g_byReStartCode == 2 )
		{
			HTint iRemainTime;
			if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||
				g_iInationalType == INATIONALTYPE_INDONESIA )
				iRemainTime = 15000;
			else
				iRemainTime = 12000;

			if( dwPassTime > m_dwReStartStartTime + iRemainTime )
			{
                this->HT_vCleanUpGameDataForReStart();
				return RETURNTYPE_EXIT_MAINGAME;
			}
		}

		return HT_OK;
	}


	//-----9. 카메라를 업데이트 해준다-----//
	HT_hrMainGameSetCamera();

	//----------메인게임 루프 한번만 업데이트----------//
	HT_vMainGame_OneTimetUpdate();
	//-----1.메인게임 루프최초 단기 초기화-----//
	HT_hrMainGamefreInit();
	//-----2.맵 Control-----//
	g_cMapInfo->HT_vMapControl();
	//-----3. 인터페이스 처리-----//
	g_cInterfaceCheck->HT_hrInterfaceControl();
	//-----7. UI를 포함하는 게임 시스템-----//
	g_cGameSystem->HT_hrGameSystemControl( m_fElapsedTime );
	//-----9. NPC-----//
	g_sNPCSystem->HT_vNPCSystemControl();
	//-----12. Other Objectr-----//
	g_cOtherObjectSystem->HT_vOtherObjectSystem_Control( m_fElapsedTime );
	//-----13. 메인캐릭터-----//
	g_cMainCharacter->HT_vMainChar_Control( m_fElapsedTime );
	//	13.1 하늘을 나느 새의 처리를 하는데 원래 엔젠에 있어야하는데 부득이하게 여기 있음
	//if ( g_pFlocking ) g_pFlocking->HT_hrUpdate( m_fElapsedTime );
	//-----14. 공격/Hit 시스템 컨트롤-----//
	g_cAttackMgr->HT_vAttackMgr_Control( m_fElapsedTime );
	g_cHitCountMgr->HT_vHitCountMgr_Control( m_fElapsedTime );
	//-----16.메인게임 루프최후 단기 삭제-----//
	HT_hrMainGameEndClean();
	// 포탈로 이동하는 경우 존 서버를 바꾸어 접속하도록 요청 후 접속을 확인
	if( g_bZoneServerSwitching ) 
		this->HT_vCheckZoneServerSwitching();
	//	서버 연결 끊어졌는지 체크한다.
	else
        HT_vCheckZoneServerDisConnect();

	return HT_OK;
}

//----------메인게임 루프최초 단기 초기화----------//
HTvoid CHTGameManager::HT_hrMainGamefreInit()
{
	//----------캐릭터가 살아 있음을 서버에 계속 알림----------//
	this->HT_vMainGame_RequestCharPing();
}

//----------메인게임 루프최후 단기 삭제----------//
HTvoid CHTGameManager::HT_hrMainGameEndClean()
{	
	g_cInterfaceCheck->HT_hrInterfaceControlEnd();
}

//----------캐릭터가 살아 있음을 서버에 계속 알림----------//
HTvoid CHTGameManager::HT_vMainGame_RequestCharPing()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_bRequestCharPingDelay+120000 )
	{
		g_pNetWorkMgr->RequestCharPing();
		m_bRequestCharPingDelay = GetTickCount();
		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_RequestCharPing" );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}

	if( dwPassTime > m_bBotCheckDelay+10000 )
	{
		m_bBotCheckDelay = dwPassTime;
		if( g_cCPSock.IsNeedToSendWho() )
		{
			char pKey[32] = {0,};
			char szTempKey[32] = {0,};
            CHTString strCheckSum;
			strCheckSum.HT_hrCleanUp();
			if( g_cGameSystem )
			{
				strCheckSum	= g_cGameSystem->HT_strGetPCSkillMD5CheckSum();
				strncpy( pKey, strCheckSum, 32 );
				//fors_debug 세콘MD5쇱꿴꼇뵨SERVERLIST寧폅뇹잿
		//		strCheckSum	= g_cGameSystem->HT_strGetServerlistMD5CheckSum();
		//		strncpy( szTempKey, strCheckSum, 32 );
		//		for(int i=0; i<32; i++)
		//			pKey[i] ^= szTempKey[i];
			} 
			Msg_Who* info = HT_NULL;
			info = new Msg_Who;
			ZeroMemory( info, sizeof( Msg_Who ) );
			memcpy( info->pszCheckSum, pKey, 32 );
			info->skillid=9;
			info->byteLevel=9;
			// Send to server
			g_pNetWorkMgr->RequestWhoMessage( info );
			HT_DELETE( info );
		}
	}
}

//----------카메라 셋팅----------//
HTvoid CHTGameManager::HT_hrMainGameSetCamera()
{
	if( !g_cMainCharacter )
		return;

	HTvector3 vecPos;
	HTfloat fAngle;
	
	vecPos = g_cMainCharacter->HT_vecGetPosition();
	fAngle = g_cMainCharacter->m_cMainCharMove->HT_fGetDirect();

	g_cCamera.HT_vCameraUpdate( vecPos, fAngle, m_fElapsedTime );
}


//-----Render-----//
HTRESULT CHTGameManager::HT_hrMainGameRender()
{
	if( g_bOneTimeUpdate < GAMESEQUNCE_MAINGAME_GMAEPLAY )
		return HT_OK;

	// If D3Device losted stop rendering!
	if(HT_hrBeforeRender() != HT_OK)
		return HT_OK;

	//  설명 : 우리의 숙원사업 ReStart를 Check
	if( g_byReStartCode != 0 )
	{
		//	ReStart or GameEnd Check
		this->HT_vMainGamReStartOrGameendRender( m_dwReStartRemainTime );
		return HT_OK;
	}

	// 서버에서 캐릭터 정보를 받았을 경우
	if(g_bMainCharacterInitialized)
	{
		//	Render World
        HT_hrWorldRender();

		//-----. MinMap-----//
		g_cMiniMap->HT_vMiniMap_Render();
		//-----. 2D Object-----//
		g_2DObjectMgr->HT_2DObjectMgrRender();
		//-----. NPC-----//
		g_sNPCSystem->HT_vNPCSystemRender();
		//-----. 메인캐릭터-----//
		g_cMainCharacter->HT_vCharRender();
		//-----. Other Character-----//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_Render();
		//-----. 게임 시스템-----//
		g_cGameSystem->HT_hrGameSystemRender();
		
		//	전광판 텍스트
		g_cChatting->HT_vChatting_RenderOpenMsg( m_fElapsedTime );
		
		// Tantra V3 Render
		g_cUIManager->HT_Render();

		//	Render MinimapPoint
		g_cOtherObjectSystem->HT_vOtherObjectSystem_RenderMinimapPoint();
		//	Render MiniMap Point
		g_sNPCSystem->HT_vNPCSystem_MiniMapPoint();

		//	IME Render
		g_cGameSystem->HT_vGameSystemRender_IME();
	}

	//	서버에서 초기화를 받았는지 체크
	HT_vMainGameServerConntionRender();

	// 채팅창 접속했는지 체크
	if (g_cChatRoom)
		g_cChatRoom->HT_vChatRoom_ConnectLoopCheck();

	HT_hrAfterRender();
	return ( HT_OK );
}

//-----Render_서버에서 초기화를 받았는지 체크-----//
HTvoid CHTGameManager::HT_vMainGameServerConntionRender()
{	
	// 서버에서 아직 캐릭터 정보가 넘어오지 않았다면
	if(!g_bMainCharacterInitialized && g_cGameSystem->m_bServerDisConnectSw == HT_FALSE )
	{
		// 캐릭터를 빈 상태로 생성
		CHTString strTemp = CHTString("");

		if( g_iRequestCharacterInitCount != 1 )
		{
			// 서버에 초기화 정보를 재요청 하고 응답을 기다리는 중 입니다.
			if( g_pMessageMgr )
				g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitializeAgain, &strTemp );
		}
		else
		{
			// 서버에 초기화 정보를 요청했습니다. 잠시만 기다려 주십시요.
			if( g_pMessageMgr )
				g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitialize, &strTemp );
		}

		// 캐릭터 정보를 요청한 때 부터 걸린 시간을 구한다 (단위:ms)
		HTuint uiTimeDifference = (GetTickCount() - g_cInitConntion_StartTime);

		if( TIMEOUT_INIT_CHARACTER < uiTimeDifference)
		{
			// 시간을 체크하는 중이고 시간이 지났다면 메시지를 표시
			if( g_cInitConntion_StartTime != 0 )
			{
				strTemp.HT_hrCleanUp();

				// 5번 이후에는 메시지 출력하면서 정료
				// 서버에서 초기화 정보가 내려오지 못했습니다. %d초 후에 게임이 자동으로 종료됩니다.", ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
				CHTString szMessage;
				if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInAutoGameEnd, &szMessage ) == true )
					strTemp.HT_szFormat( szMessage.HT_szGetString(), ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );

				// 받지 못했으면 5번까지 요청한다.
				if( g_iRequestCharacterInitCount < 5 )
				{
					// 서버에 캐릭터 초기화 정보를 요청한다_이니트 메인캐릭터,
					// 시간 초기화를 좀 더 비슷하게 하기 위하여 순서를 뒷쪽으로 빼었다. (20030109Tenma)
					g_cInitConntion_StartTime = GetTickCount();
					// 서버에 초기화 재 요청 합니다.
					if( g_pMessageMgr )
						g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitializeAgain, &strTemp );
					g_iRequestCharacterInitCount ++;
				}
				else
				{
					// 5번 이후에는 메시지 출력하면서 정료
					// 서버에서 초기화 정보가 내려오지 못했습니다. %d초 후에 게임이 자동으로 종료됩니다.", ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInAutoGameEnd, &szMessage ) == true )
						strTemp.HT_szFormat( szMessage.HT_szGetString(), ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
				}
			}

			// 대기 시간이 지났고, 아직 시간을 체크 중이면 게임을 끝낸다.
			if( ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 <= 0 && g_cInitConntion_StartTime != 0)
			{
				// 시간을 더 이상 체크하지 않게 한다.
				g_cInitConntion_StartTime = 0;

				g_byReStartButtonCode = _BTN_MSG_GAME_END;
				//	현재 서버와 연결 끊음
				g_pNetWorkMgr->DisConnect();
			}
		}
	}
}

//	ReStart or GameEnd Check
HTvoid CHTGameManager::HT_vMainGamReStartOrGameendRender( DWORD dwRemainTime )
{
	// 해상도 추출
	HTint iScreenWidth	= g_pEngineHandler->HT_iGetScreenWidth();
	HTint iScreenHeight	= g_pEngineHandler->HT_iGetScreenHeight();
	CHTString szParam, strTemp;
	HTfloat fCorrectPosX;

	if( g_byReStartCode == 2 )
	{
		HTint iDevideTime;
		if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||
			g_iInationalType == INATIONALTYPE_INDONESIA )
		{
			fCorrectPosX = 90;
			iDevideTime = 15;
		}
		else
		{
			fCorrectPosX = 150;
			iDevideTime = 12;
		}

		CHTString szParam, strTemp;
		strTemp.HT_szFormat("%d", (HTint)(iDevideTime-(dwRemainTime/1000)) );
		HT_g_Script_SetMessage( eMsgReStartRemindTime, &szParam, strTemp.HT_szGetString() );
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, szParam.HT_szGetString(), HTvector3( (HTfloat)iScreenWidth/2-150, (HTfloat)iScreenHeight/2, 0.0f ), HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
	}
	else if( g_byReStartCode == 3 )
	{
		if( g_iInationalType == INATIONALTYPE_PHILIPPINE ||
			g_iInationalType == INATIONALTYPE_INDONESIA )
		{
			fCorrectPosX = 100;
		}
		else
		{
			fCorrectPosX = 130;
		}

		HT_g_Script_SetMessage( eMsgGameExit, &strTemp, _T("") );
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strTemp.HT_szGetString(), HTvector3( (HTfloat)iScreenWidth/2-130, (HTfloat)iScreenHeight/2, 0.0f ), HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
	}

	HT_hrAfterRender();
}

// 리전 서버 전환 시 접속을 확인하고 연결을 재설정 한다.
HTvoid CHTGameManager::HT_vCheckZoneServerSwitching()
{
	//	서버가 연결 됐을 때
	if( m_bServerConnectCheck )
	{
		if( g_pNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
		{
			//	로딩이미지 랜더
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.1f );

			//	전체적인 데이타를 지우고
			//	게임 프로세스 진행안되게 셋팅
			g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_NONE;
			// 포탈이동을 위한 최소한의 데이타 이니트
			g_bMainCharacterInitialized = HT_FALSE;
			if (g_CGame) g_CGame->HT_vCleanUpGameDataForPortal();

			HT_DELETE( g_pFlocking );

			//	로딩이미지 랜더
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.15f );

			//	해당 번호의 맵을 로드
			if (g_cLoading) g_cLoading->HT_hrLoadMap( g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER );

			//	로딩이미지 랜더
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.9f );
/*
			g_pFlocking = new CHTFlocking;
			if (!g_pFlocking) return;

			if (g_pEngineHandler) 
			{
				HTint iNumFlocking = g_pEngineHandler->HT_iGetNumFlocking();
				g_pFlocking->HT_hrCreate( iNumFlocking );

				for ( HTint iFlocking = 0; iFlocking < iNumFlocking; ++iFlocking )
				{
					HTdword dwNPC;
					HTvector3 vecPos;
					if (g_pEngineHandler) g_pEngineHandler->HT_vGetBaseFlockingInfo( iFlocking, &dwNPC, &vecPos );
					if (g_pFlocking) g_pFlocking->HT_vPushOne( dwNPC, vecPos );
				}

				g_pEngineHandler->HT_vReleaseBaseFlockingInfo();
			}
*/
			//	해당 번호의 맵의 미니맵을 초기화
			if (g_cMiniMap) 
			{
				g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPSMALL );
				g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPBIG );
				g_cMiniMap->HT_hrMiniMap_Init();
				g_cMiniMap->HT_vTotalMiniMap_Load();
			}

			//	로딩이미지 랜더
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 1.0f );

			m_bServerConnectCheck = HT_FALSE;
			//	Request Move Zone Server
			g_bZoneServerSwitching = HT_FALSE;

			PS_CSP_REQ_MOVE_ZONE_SERVER info = NULL;
			info = new S_CSP_REQ_MOVE_ZONE_SERVER;
			info->dwEvent = (DWORD)g_iLoginResultID;
			CHTString::HT_hrStringCopy( info->AccountName, g_strLoginID, ACCOUNTNAME_LENGTH );
			CHTString::HT_hrStringCopy( info->AccountPass, g_strLgoinPasswordMD5, ACCOUNTPASS_LENGTH );
			CHTString::HT_hrStringCopy( info->szCharName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
			for( int i=0 ; i<4 ; i++ )	info->snVersion[i] = g_snVersionCheck[i];
			g_pNetWorkMgr->RequestReqMoveZoneServer( info );
			//-----디버깅 테스트를 위하여-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MoveZoneServer");
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			HT_DELETE( info );

			//	Request Move Zone Server
            //g_cGameSystem->HT_vSetRequestMoveZoneServer( HT_TRUE );
		}
	}
	else
	{	
		//	서버가 끊어 졌을 때
		if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
		{
			//	서버와 재 연결
			g_pNetWorkMgr->Connect( g_strZoneServerIP, g_iZoneServerPort );
			m_bServerConnectCheck = HT_TRUE;
		}
	}
}

//	서버 연결 끊어졌는지 체크한다.
HTvoid CHTGameManager::HT_vCheckZoneServerDisConnect()
{
	//	서버 연결 끊어졌는지 체크한다.
	if( m_bZoneServerDisConnectCheck )
	{
		if( g_byReStartButtonCode == 10 )
		{
			m_dwReStartStartTime = GetTickCount();
            g_byReStartCode = 3;
		}
		return;
	}

	//	서버가 끊어 졌을 때
	if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
	{
		if( g_byReStartButtonCode == _BTN_MSG_GAME_END )
		{
			m_dwReStartStartTime = GetTickCount();
            g_byReStartCode = 3;
		}
		else if( g_byReStartButtonCode == _BTN_MSG_RESTART )
		{
			m_dwReStartStartTime = GetTickCount();
			g_byReStartCode = 2;
		}
		else
		{
			m_bZoneServerDisConnectCheck = HT_TRUE;
//			HSTRACE(eGame, "Network(Region) Disconnected!!!\n");
			CHTString szMessage;
			//if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
			//	g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );
		}
	}
}
