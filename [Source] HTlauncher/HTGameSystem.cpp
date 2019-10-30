
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTGameSystem.h"

//-----메뉴윈도우_0:상태,1:퀘스트,2:인벤토리,3:스킬,4:파티,5:시스템
HTint g_fWindowMenuBarX[6] = { 7, 52, 97, 142, 187, 232 };


CHTGameSystem::CHTGameSystem()
{
	m_bReqReenDlgSw = HT_FALSE;
	m_bServerDisConnectSw = HT_FALSE;
	m_dwServerDisConnectTimeOut = 0;
	m_byRegenType = 0;
	m_iMessageVal = -1;
	m_bPKOn = HT_FALSE;;
	m_bRequestMoveZoneServerCheck = HT_FALSE;
	m_bRequestMoveZoneServerStartTime = HT_FALSE;
}

CHTGameSystem::~CHTGameSystem()
{
	//-----장착 인벤토리-----//
	HT_DELETE( g_cEquipInventory );
    //-----스킬 인벤토리-----//
	HT_DELETE( g_cSkillInventory );
    //-----상거래, 챠크라 시스템-----//
	HT_DELETE( g_cNPCControl);

	//-----미니맵-----//
	HT_DELETE( g_cMiniMap );
	//-----교환 시스템-----//
	HT_DELETE( g_cExchangeSystem );
	//-----캐릭터 스테이터스-----//
	HT_DELETE( g_cStatus );
	//-----파티-----//
	HT_DELETE( g_cParty );
	//-----퀘스트-----//
	HT_DELETE( g_cQuest );
	//-----시스템-----//
	HT_DELETE( g_cSystem );
	//-----정보창-----//
	HT_DELETE( g_cObjectInfo );
	//-----맵 정보-----//
	HT_DELETE( g_cMapInfo );
	//-----주소록-----//
	HT_DELETE( g_cAddress );
	//-----결투시스템-----//
	HT_DELETE( g_pDuelSystem );
	//-----Chatting-----//
	HT_DELETE( g_cChatting );
	//-----스킬 시스템-----//
//	HT_DELETE( g_cSkillSystem );
	//-----2D 스프라이트를-----//
//	HT_DELETE( g_2DObjectMgr );
	//	퀵슬롯 클리어
	HT_DELETE( g_cQuickSlot );
	//	명령 클리어
	HT_DELETE( g_cCommand );

	// 개인 상점
    HT_DELETE( g_cIndividualStore );

	g_cUIManager->HT_DeleteWindow( _DIALOG_DEATHMSG );
	g_cUIManager->HT_DeleteWindow( _DIALOG_DEATHMSGFOTRESS );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_DISCONNECTSERVER );
	g_cUIManager->HT_DeleteWindow( _DIALOG_ANSWERUSESAMUDABA );
	g_cUIManager->HT_DeleteWindow( _DIALOG_REVIVEWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WEBBROWSER );
}

//-----GS 데이타 클린업 하기-----//
HTvoid CHTGameSystem::HT_vGSDataCleanUp()
{
	//-----2D 오브젝트 클리어-----//
	if( g_2DObjectMgr) g_2DObjectMgr->HT_2DObjectMgrCleanUp();
	HT_DELETE( g_2DObjectMgr );

	//-----메인바 클리어-----//
	HT_DELETE( g_pMainBar );
	
	//-----아이템 관련 클리어-----//
	if( g_cItemSystem) g_cItemSystem->HT_vItemSystem_CleanUp();
	HT_DELETE( g_cItemSystem );	
	if( g_cItemControl ) g_cItemControl->HT_vItemControl_CleanUp();
	HT_DELETE( g_cItemControl );

	//-----스킬 인벤토리 클리어-----//
	if( g_cSkillInventory ) g_cSkillInventory->HT_vSkillInventory_CleanUp();
	HT_DELETE( g_cSkillInventory );
	//-----스킬 시스템 클리어-----//
	if( g_cSkillSystem) g_cSkillSystem->HT_vSkillSystem_CleanUp();
	HT_DELETE( g_cSkillSystem );

	//-----장착 인벤토리 클리어-----//
	if( g_cEquipInventory ) g_cEquipInventory->HT_vEquipInventory_CeleanUp();
	HT_DELETE( g_cEquipInventory );

	//-----미니맵 클리어-----//
	if( g_cMiniMap) g_cMiniMap->HT_vMinMap_CeleanUp();
	HT_DELETE( g_cMiniMap );

	//-----교환 시스템 클리어-----//
	if( g_cExchangeSystem) g_cExchangeSystem->HT_vExchange_CleanUp();
	//HT_DELETE( g_cExchangeSystem );

	//----------캐릭터 스테이터스 클리어----------//
	if(g_cStatus) g_cStatus->HT_vStatus_CleanUp();
	HT_DELETE( g_cStatus );

	//----------파티 클리어----------//
	if(g_cParty) g_cParty->HT_vParty_CleanUp();
	//HT_DELETE( g_cParty );

	//----------튜토리얼 시스템 클리어----------//
	HT_DELETE( g_cTutorialSystem );

	//----------퀘스트 클리어----------//
	if(g_cQuest) g_cQuest->HT_vQuest_CleanUp();
	HT_DELETE( g_cQuest );

	//----------주소록 클리어----------//
	if( g_cAddress ) g_cAddress->HT_vAddress_Delete();
	//HT_DELETE( g_cAddress );

	//----------시스템 클리어----------//
	if( g_cSystem ) g_cSystem->HT_vSystem_CleanUp();
	//HT_DELETE( g_cSystem );

	//-----------------------------------------------------------------------------//
	//  설명 : 정보창 클리어
	//  작성일자 / 작성자 : 2002.12.27_김선미
	//-----------------------------------------------------------------------------//
	//HT_DELETE( g_cObjectInfo );

	//----------맵정보 클리어----------//
	HT_DELETE( g_cMapInfo );

	//-----공지사항 윈도우 클리어-----//
	if( g_pNotifyWindow && g_pNotifyWindow->isLoaded() ) g_pNotifyWindow->Unload();
	HT_DELETE( g_pNotifyWindow );

	//------이벤트 창 클리어-------//
	HT_DELETE( g_pEventWindow );

	//-----채팅 클리어-----//
	if( g_cChatting ) g_cChatting->HT_vChatting_CleanUp();
	//HT_DELETE( g_cChatting );
	
	//----------포탈 클리어----------//
	HT_DELETE( g_cPortal );

	//----------GM 클리어----------//
	HT_DELETE( g_cGMSystem );

	//----------리젼 대화상자 ----------//
	m_bReqReenDlgSw					= HT_FALSE;

	//----------서버가 죽었을때 확인 스위치----------//
	m_bServerDisConnectSw			= HT_FALSE;

	//-----NPC 관련 클리어 -----//
	if(g_cNPCControl)	g_cNPCControl->HT_vNPCControl_CleanUp();
	//HT_DELETE( g_cNPCControl );

	//----------길드 클리어----------//
	if( g_cGuildSystem )	g_cGuildSystem->HT_vGuild_Delete();
	HT_DELETE( g_cGuildSystem );

	//----------퀵스킬 클리어----------//
	HT_DELETE( g_cQuickSlot );

	//	명령 클리어
	HT_DELETE( g_cCommand );

	//	Init QuickSlot
	HT_DELETE( g_cQuickSlot );

	// 겜블 클리어
	HT_DELETE( g_cGamble );

	// ChatRoom 클리어
	HT_DELETE( g_cChatRoom );

	// 공성전 클리어
	HT_DELETE( g_pSiege );

	// 위탁상점 클리어
	HT_DELETE( g_cRentalStore );

}

HTRESULT CHTGameSystem::HT_hrGameSystemInit()
{

	// V3 에서 새로 추가된 윈도우들... (v2 버전보다 먼저 읽어들여야 한다. v2버전에서 v3버전 함수를 사용하므로...)
	if( !g_cUINPCWindow )
	{
		g_cUINPCWindow					= HT_NULL;
		g_cUINPCWindow					= new CHTUINPCWindow;
	}
	g_cUINPCWindow->HT_vNPCWindow_Init(); // 지금은 예전 버전과 같이 사용해야 한다.

	if( !g_cUIStatus )
	{
		g_cUIStatus						= HT_NULL;
		g_cUIStatus						= new CHTUIStatus;
	}
	g_cUIStatus->HT_vStatus_Init(); // Tantra V3 전용

	if( !g_cUISkillWindow )
	{
		g_cUISkillWindow = HT_NULL;
		g_cUISkillWindow = new CHTUISkillWindow;
	}
	g_cUISkillWindow->HT_vSkillWindow_Init();

	if( !g_cUIQuestWindow )
	{
		g_cUIQuestWindow				= HT_NULL;
		g_cUIQuestWindow				= new CHTUIQuestWindow;
	}
	g_cUIQuestWindow->HT_vQuestWindow_Init();

	if( !g_cUIMerchantWindow )
	{
		g_cUIMerchantWindow				= HT_NULL;
		g_cUIMerchantWindow				= new CHTUIMerchantWindow;
	}
	g_cUIMerchantWindow->HT_vMerchantWindow_Init();

	// 제련
	if( !g_cUIRefineWindow )
	{
		g_cUIRefineWindow				= HT_NULL;
		g_cUIRefineWindow				= new CHTUIRefineWindow;
	}
	g_cUIRefineWindow->HT_vRefineWindow_Init();

	// 앰블램
	if( !g_cUIEmblemWindow )
	{
		g_cUIEmblemWindow				= HT_NULL;
		g_cUIEmblemWindow				= new CHTUIEmblemWindow;
	}
	g_cUIEmblemWindow->HT_vEmblemWindow_Init();


	//	공성전
	g_pSiege						= HT_NULL;
	g_pSiege						= new HTSiege;
	g_pSiege->HT_vSiege_Init();

	//--------- Gamble UI Class ----------//
	g_cGamble						= HT_NULL;
	g_cGamble						= new HTGamble;
	g_cGamble->HT_vGamble_Init();


	//--------- ChatRoom UI Class -------- //
	g_cChatRoom						= HT_NULL;
	g_cChatRoom						= new HTChatRoom;
	g_cChatRoom->HT_vChatRoom_Init();

	if( !g_cQuickSlot )
	{
		g_cQuickSlot					= HT_NULL;
		g_cQuickSlot					= new HTQuickSlot;
		//	Quick Bar
		g_cQuickSlot->HT_vInit();
	}

	//	명령 클래스 생성
	if( !g_cCommand )
	{
		g_cCommand						= HT_NULL;
		g_cCommand						= new HTCommand;
	}
	g_cCommand->HT_vCommand_Init();

	//-----2D 오브젝트 생성-----//
	g_2DObjectMgr = HT_NULL;
	g_2DObjectMgr = new CHT2DObjectMgr;
	g_2DObjectMgr->HT_2DObjectMgrInit();

	//-----메인바 생성-----//
	g_pMainBar = HT_NULL;
	g_pMainBar = new CHTMainBar;
	g_pMainBar->HT_vLoad();
	
	//-----아이템 관련 생성-----//
	if( !g_cItemControl )
	{
		g_cItemControl = HT_NULL;
		g_cItemControl = new HTItemControl;
	}
	g_cItemControl->HT_vItemControl_Init();

	if( !g_cItemSystem )
	{
		g_cItemSystem = HT_NULL;
		g_cItemSystem = new	CHTItemSystem;
	}
	g_cItemSystem->HT_hrSystemInit();

	//-----스킬 시스템 생성-----//
	g_cSkillSystem = HT_NULL;
	g_cSkillSystem = new HTSkillSystem;
	g_cSkillSystem->HT_hSkillSystemInit();

	//-----스킬 인벤토리 생성-----//
	g_cSkillInventory = HT_NULL;
	g_cSkillInventory = new CHTSkillInventory;
	g_cSkillInventory->HT_hrSkillInventoryInit();

	//-----장착 인벤토리 생성-----//
	g_cEquipInventory = HT_NULL;
	g_cEquipInventory = new CHTEquipInventory;
	g_cEquipInventory->HT_hrInit();

	//-----미니맵 생성-----//
	if( !g_cMiniMap )
	{
		g_cMiniMap = HT_NULL;
		g_cMiniMap = new CHTMiniMap;
	}
	g_cMiniMap->HT_hrMiniMap_Init();
	g_cMiniMap->HT_vTotalMiniMap_Load();

	//-----상거래, 챠크라 시스템 생성-----//
	if( !g_cNPCControl )
	{
		g_cNPCControl = HT_NULL;
		g_cNPCControl = new CHTNPCControl;
	}
	g_cNPCControl->HT_vNPCControl_Init();

	//-----교환 시스템 생성-----//
	if( !g_cExchangeSystem )
	{
		g_cExchangeSystem = HT_NULL;
		g_cExchangeSystem = new HTExchange;
	}
	g_cExchangeSystem->HT_hrExchange_Init();

	//----------캐릭터 스테이터스----------//
	g_cStatus						= HT_NULL;
	g_cStatus						= new HTStatus;
	g_cStatus->HT_vStatus_Init();	// 지금은 같이 사용해야 한다.
			
	//----------파티----------//
	if( !g_cParty )
	{
		g_cParty						= HT_NULL;
		g_cParty						= new HTParty;
	}
	g_cParty->HT_vParty_Init();

	//----------튜토리얼 시스템----------//
	g_cTutorialSystem				= HT_NULL;
	g_cTutorialSystem				= new HTTutorialSystem;
	g_cTutorialSystem->HT_vInit();

	//----------퀘스트----------//
	g_cQuest						= HT_NULL;
	g_cQuest						= new HTQuest;
	g_cQuest->HT_vQuest_Init();

	//----------주소록----------//
	if( !g_cAddress )
	{
		g_cAddress						= new HTAddress;
	}
	g_cAddress->HT_vAddress_Init();

	//----------결투 시스템----------//
	if( !g_pDuelSystem )
	{
		g_pDuelSystem				= new HTDuelSystem;
	}

	//----------시스템----------//
	if( !g_cSystem )
	{
		g_cSystem						= HT_NULL;
		g_cSystem						= new HTSystem;
	}
	g_cSystem->HT_vSystem_Init();

	//----------길드 시스템----------//
	if( !g_cGuildSystem )
	{
		g_cGuildSystem					= HT_NULL;
		g_cGuildSystem					= new HTGuild;
		//	길드 시스템 초기화
		g_cGuildSystem->HT_vGuild_Init();
	}

	//---------- 정보창 -------------//
	if( !g_cObjectInfo )
	{
		g_cObjectInfo					= HT_NULL;
		g_cObjectInfo					= new HTObjectInfo;
	}
	g_cObjectInfo->HT_vObjectInfo_Init();

	//---------- 개인상점 ------------//
	if( !g_cIndividualStore )
	{
		g_cIndividualStore				= HT_NULL;
		g_cIndividualStore				= new CHTIndividualStore;
	}
	g_cIndividualStore->HT_vIndividualStore_Init();

	//---------- 위탁상점 ------------//
	if( !g_cRentalStore )
	{
		g_cRentalStore				= HT_NULL;
		g_cRentalStore				= new CHTRentalStore;
	}
	g_cRentalStore->HT_vRentalStore_Init();

	//----------맵정보----------//
	g_cMapInfo						= HT_NULL;
	g_cMapInfo						= new HTMapInfo;

	//-----공지사항 윈도우 생성-----//
	g_pNotifyWindow					= HT_NULL;
	g_pNotifyWindow					= new CHTNotifyWindow;
	g_pNotifyWindow->Load();

	//-----이벤트 윈도우 생성-----//
	g_pEventWindow					= HT_NULL;
	g_pEventWindow					= new CHTEventWindow;

	//-----채팅 생성-----//
	if( !g_cChatting )
	{
		g_cChatting						= HT_NULL;
		g_cChatting						= new CHTChatting;
	}
	g_cChatting->HT_vChatting_Init();
	
	//----------포탈----------//
	g_cPortal						= HT_NULL;
	g_cPortal						= new HTPortal;
	g_cPortal->HT_vPortal_Init();

	//----------GM----------//
	g_cGMSystem						= HT_NULL;
	g_cGMSystem						= new HTGM;
	g_cGMSystem->HT_vGM_Init();

	//----------리젼 대화상자----------//
	m_bReqReenDlgSw					= HT_FALSE;

	//----------서버가 죽었을때 확인 스위치----------//
	m_bServerDisConnectSw			= HT_FALSE;

	//	For Server Connect, DisConnect Check
	//	스위칭 서버 체크
	g_bZoneServerSwitching				= HT_FALSE;
	//	서버와의 Connect Check
	g_bPortalServerConnectCheckSw		= HT_FALSE;
	//	서버와의 DisConnect Check
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;
	//	포탈 이용할때 RequestMoveZoneServer
	m_bRequestMoveZoneServerCheck		= HT_FALSE;
	//	Zone Setting No
	g_snResentZoneSiege					= 0;
	//	Answer Samudaba
	m_bAnswerSamudabaSw					= HT_FALSE;
	//	UserID Answer Samudaba
	m_iUserIDAnswerSamudaba				= 0;
	//	Samudaba Delay Time
	m_dwSamudabaDelayTime				= 0;
	//	확인버튼을 눌러서 이닛커넥트 요청했는지를 안다.
	m_bUserReqInitRegenChar				= FALSE;

	//	Create Window
	this->HT_vGameSystem_CreateWindow();

	return HT_OK;
}

HTvoid CHTGameSystem::HT_vGameSystem_CreateWindow()
{
	CHTString strMessage;

	//	[_DIALOG_DEATHMSG]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_DEATHMSG, _T(""), 0, 0, g_cGameSystem->HT_vGameSystem_InputCheckForDeathMsg, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_DEATHMSG, 5 );

	//	[_DIALOG_DEATHMSGFOTRESS]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_DEATHMSGFOTRESS, _T(""), 400, 120, g_cGameSystem->HT_vGameSystem_InputCheckForDeathinFortess, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_DEATHMSGFOTRESS, 5 );
	//	Button 아레나 관중석에서 부활(20000 루피아 소모)
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 0, 0, 10, 20, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 20, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 0 );
	//	Button 저장된 장소에서 부활
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 1, 0, 10, 45, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 45, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 1 );
	//	Button 저장된 장소에서 부활
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 2, 0, 10, 70, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 2, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 2 );
	//	Button 확인 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 3, 159, 290, 90, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 3, eMsgCommonConfirm, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 290, 90, 89, 19 );//확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 3 );

	//	[_DIALOG_DISCONNECTSERVER]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_DISCONNECTSERVER, _T(""), 0, 0, g_cGameSystem->HT_vGameSystem_InputCheckForDisConnectServer, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_DISCONNECTSERVER, 5 );

	//	[_DIALOG_ANSWERUSESAMUDABA]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ANSWERUSESAMUDABA, _T(""), 0, 0, g_cGameSystem->HT_vGameSystem_InputCheckForSamadaba, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ANSWERUSESAMUDABA, 5 );

	//	[_DIALOG_REVIVEWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_REVIVEWND, _T(""), 400, 90, g_cGameSystem->HT_vGameSystem_InputCheckRevive, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_REVIVEWND, 5 );
	//	Button 현재의 자리에서 부활합니다.
	g_cUIManager->HT_AddButtonControl( _DIALOG_REVIVEWND, 0, 0, 10, 20, 10, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_REVIVEWND, 0, eMsgRevivalRevivalCurrentPos, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 20, 380, 19 );//현재의 자리에서 부활합니다.
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_REVIVEWND, 0 );
	//	Button 저장된 지역에서 부활합니다.
	g_cUIManager->HT_AddButtonControl( _DIALOG_REVIVEWND, 1, 0, 10, 50, 10, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_REVIVEWND, 1, eMsgRevivalRevivalSavedZone, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 50, 380, 19 );//저장된 지역에서 부활합니다.
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_REVIVEWND, 1 );

	//	[_DIALOG_WEBBROWSER]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgRevivalWebWindow, &strMessage, _T(""), _T("") );	//	Web Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WEBBROWSER, strMessage, 801, 600, g_cGameSystem->HT_vGameSystem_InputCheckWebBrowser, 2 );//Web Window
	g_cUIManager->HT_MoveWindow( _DIALOG_WEBBROWSER, g_pEngineHandler->HT_iGetScreenWidth()/2-400, g_pEngineHandler->HT_iGetScreenHeight()/2-300 );
	//	Button 확인 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_WEBBROWSER, 1, 159, 650, 565, 160, 161, 1500, 89, 22 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WEBBROWSER, 1, eMsgRevivalExitWeb, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 650, 565, 89, 22 );//나가기
	g_cUIManager->HT_SetScriptMessage( eMsgRevivalWebBrowser, &strMessage, _T(""), _T("") );	//	WebBrowser를 종료합니다.
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_WEBBROWSER, 1, strMessage );

	//	[_DIALOG_QUIZ]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_QUIZ, _T(""), 400, 200, g_cGameSystem->HT_vGameSystem_InputCheckQuiz, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_QUIZ, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_QUIZ, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture QUIZ
	g_cUIManager->HT_AddTextureControl( _DIALOG_QUIZ, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 2, _T("Quiz"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label Quiz
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 3, _T("Current Not Quiz"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 60, 380, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_QUIZ, 3, 7 );
	//	Button 답변1
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 10, 159, 10, 120, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 10, _T("Answer1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 120, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 10 );
	//	Button 답변2
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 11, 159, 210, 120, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 11, _T("Answer2"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 120, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 11 );
	//	Button 답변3
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 12, 159, 10, 150, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 12, _T("Answer3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 150, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 12 );
	//	Button 답변4
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 13, 159, 210, 150, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 13, _T("Answer4"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 150, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 13 );
}
CHTString CHTGameSystem::HT_strGetPCSkillMD5CheckSum()
{
	std::vector< HTIDLevel > vecIDLevel; 
	g_pParamMgr->HT_bGetAllID( HT_PARAMTYPE_PCSKILL, &vecIDLevel );

	int *pCastTimes = new int[vecIDLevel.size()];
	for ( int i = 0 ; i < vecIDLevel.size() ; i++ )
	{
		HTIDLevel &oIDLevel = vecIDLevel[i];
		//g_pParamMgr->HT_bGetPCSkillCastingTime( oIDLevel.iID, oIDLevel.byteLevel, &pCastTimes[i] );
		g_pParamMgr->HT_bGetPCSkillReadyTime( oIDLevel.iID, oIDLevel.byteLevel, &pCastTimes[i] );
	}

	CHTMD5Checksum oMD5CheckSum;
	CHTString strMD5 = oMD5CheckSum.HT_strGetMD5( (char*)pCastTimes, vecIDLevel.size() * sizeof(int) );
	delete[] pCastTimes;
	return strMD5.HT_szGetString();
}
CHTString HT_strGetSkillIDMD5CheckSum(const int id, const byte byteLevel, const int NeedTimes )
{

	//int pCastTimes ;

	//	g_pParamMgr->HT_bGetPCSkillReadyTime( id,byteLevel, &pCastTimes );

	CHTMD5Checksum oMD5CheckSum;
	CHTString strMD5 = oMD5CheckSum.HT_strGetMD5( (char*)NeedTimes, sizeof(int) );
//	delete[] pCastTimes;
	return strMD5.HT_szGetString();
}

CHTString CHTGameSystem::HT_strGetServerlistMD5CheckSum()
{
	unsigned r1,r2,r3,r4;

	S_SERVERLIST	stServerlist;
	ZeroMemory(&stServerlist, sizeof(stServerlist));

	for(int i=0; i<MAX_SERVERGROUP; i++)
	{
		for ( int k=0 ; k<MAX_SERVER ; k++ )
		{
			r1=0;r2=0;r3=0;r4=0;
			if( g_oWorldList[i][k].snWorldPort > 0 )
                sscanf( g_oWorldList[i][k].szWorldIP,"%d.%d.%d.%d",&r1,&r2,&r3,&r4 );
			stServerlist.pServerListPort[i][k] = g_oWorldList[i][k].snWorldPort;
			stServerlist.pServerListBin[i][k] = (r1) | (r2<<8) | (r3<<16) | (r4<<24);
		}
	}
	CHTMD5Checksum oMD5CheckSum;
	CHTString strMD5 = oMD5CheckSum.HT_strGetMD5( (char*)&stServerlist, sizeof(stServerlist) );
	return strMD5.HT_szGetString();
}

//	입력 메세지 처리
//	Daeth Mssage
void CHTGameSystem::HT_vGameSystem_InputCheckForDeathMsg(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		if (iTargetID == -1 )
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

		if( iTargetID == 2 )
		{
			//	채팅모드를 풀어줌
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			//	확인버튼을 눌러서 이닛커넥트 요청했는지를 안다.
			g_cGameSystem->m_bUserReqInitRegenChar = TRUE;
			g_cGameSystem->HT_vGameSystem_CSP_INIT_REGEN_CHAR( 0x01 );
		}
		g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );
	}
}
//	Death Message Fortess
void CHTGameSystem::HT_vGameSystem_InputCheckForDeathinFortess(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 0 )
		{
			if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				// 2만 루피아보다 적게 가지고 있으면 사용할 수 없다.
				if (g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 20000)
				{
					CHTString strString;
					HT_g_Script_SetMessage( eMsgCommonServerMoreRupia, &strString );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
					return;
				}
			}
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 0 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 1 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 2 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 0, 201, 10, 20, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 1, 0, 10, 45, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 2, 0, 10, 70, 201, 0, 1500, 380, 19 );
			g_cGameSystem->m_iButtonType = 0;
		}
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 0 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 1 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 2 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 0, 0, 10, 20, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 1, 201, 10, 45, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 2, 0, 10, 70, 201, 0, 1500, 380, 19 );
			g_cGameSystem->m_iButtonType = 1;
		}
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 0 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 1 );
			g_cUIManager->HT_DelButtonControl( _DIALOG_DEATHMSGFOTRESS, 2 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 0, 0, 10, 20, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 1, 0, 10, 45, 201, 0, 1500, 380, 19 );
			g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 2, 201, 10, 70, 201, 0, 1500, 380, 19 );
			g_cGameSystem->m_iButtonType = 2;
		}
		else if( iTargetID == 3 )
		{
			//-----캐릭터 리젼 정보를 요청한다-----//
			PS_CSP_REQ_INIT_REGEN_CHAR info = HT_NULL;
			info = new S_CSP_REQ_INIT_REGEN_CHAR;

			if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				if( g_cGameSystem->m_iButtonType == 0 )
                    info->byConnType = REGEN_TYPE_ARENA;
				else if( g_cGameSystem->m_iButtonType == 1 )
					info->byConnType = REGEN_TYPE_REGEN;
			}
			else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
			{
				if( g_cGameSystem->m_iButtonType == 0 )
                    info->byConnType = REGEN_TYPE_CASTLE1;
				else if( g_cGameSystem->m_iButtonType == 1 )
					info->byConnType = REGEN_TYPE_CASTLE2;
				else if( g_cGameSystem->m_iButtonType == 2 )
					info->byConnType = REGEN_TYPE_REGEN;
			}
			//	확인버튼을 눌러서 이닛커넥트 요청했는지를 안다.
			g_cGameSystem->m_bUserReqInitRegenChar = TRUE;
			g_pNetWorkMgr->RequestReqInitRegenChar( info );

			//-----디버깅 테스트를 위하여-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Revive_Req : %d", info->byConnType );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			HT_DELETE( info );

			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );
		}
	}
}
//	DisConnect Server
void CHTGameSystem::HT_vGameSystem_InputCheckForDisConnectServer(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		g_byReStartButtonCode = 10;
		//PostQuitMessage(0);
	}
}
//	Samudaba Skill
void CHTGameSystem::HT_vGameSystem_InputCheckForSamadaba(int iAction, int iTarget, int iTargetID)
{
	g_cMainCharacter->m_bMainChar_Reviving = HT_FALSE;
	// 프로퍼티를 선택
	if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		if( iTargetID == 2 )
		{
			//	채팅모드를 풀어줌
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			// ESC키를 눌러 확인창이 뜨는걸 막기 위해 사용할 맴버변수
			g_cMainCharacter->m_bMainChar_Reviving = HT_TRUE;
			//	HIde
			g_cUIManager->HT_HideWindow( _DIALOG_ANSWERUSESAMUDABA );

			DWORD dwPassTime = timeGetTime();
			HTvector3 vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( g_cGameSystem->m_iUserIDAnswerSamudaba );
			HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
			g_cGameSystem->m_nRange = (HTint)HT_extern_fGetDisForTwoPoint( vecTargetPos, vecMainCharPos );

			if( dwPassTime > g_cGameSystem->m_dwSamudabaDelayTime+10000 )
			{
				g_cMainCharacter->m_bMainChar_Reviving = HT_FALSE;
			
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAnswerUseSamudabaErr2, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return;
			}
			else if ( g_cGameSystem->m_nRange > 200 )
			{
				g_cMainCharacter->m_bMainChar_Reviving = HT_FALSE;

				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAnswerUseSamudabaErr1, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return;
			}
			else
			{
				g_cGameSystem->HT_vGameSystem_ReqAnswerUseSamudaba( 1, g_cGameSystem->m_iUserIDAnswerSamudaba, 1, 0 );
			}
		}
		else if( iTargetID == 3 )
		{
			//	HIde
			g_cUIManager->HT_HideWindow( _DIALOG_ANSWERUSESAMUDABA );
		}
	}
}
//	입력함수 처리 Revive
void CHTGameSystem::HT_vGameSystem_InputCheckRevive(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{ 
		HTint iButtonNo = -1;
		if( iTargetID == 0 )
		{
			iButtonNo = 0;
		}
		else if( iTargetID == 1 )
		{
			iButtonNo = 1;
		}
		else if (iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_REVIVEWND );
		}

		if( iButtonNo != -1 )
		{
			//	채팅모드를 풀어줌
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );

			g_cUIManager->HT_HideWindow( _DIALOG_REVIVEWND );

			MSG_ITEM* info = HT_NULL;
			info = new MSG_ITEM;
			info->byType = HT_MSG_ITEM_USE;
			//	Data Setting for MSG_Item
			info->byPlace = g_cPortal->m_byPlace_ForMsgItem;
			info->byIndex = g_cPortal->m_byIndex_ForMsgItem;

			if( iButtonNo == 0 )
				info->snWarpID = RESURRECT_TYPE_PRESENT;
			else if( iButtonNo == 1 )
				info->snWarpID = RESURRECT_TYPE_SAVE;

			g_pNetWorkMgr->RequestItemUse( info );

			//-----디버깅 테스트를 위하여-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_UpgradePustica_Use : %d", info->snWarpID );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			HT_DELETE( info );
		}
	}
}
//	입력함수 처리 WebBrowser
void CHTGameSystem::HT_vGameSystem_InputCheckWebBrowser(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 || iTargetID == 1 )
		{
			g_pEngineHandler->HT_hrCloseWeb();
		}
	}
}
//	입력한수 처리 Quiz
void CHTGameSystem::HT_vGameSystem_InputCheckQuiz(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
			return;

		Msg_QuizResponse* info = HT_NULL;
		info = new Msg_QuizResponse;
		memset( info, 0, sizeof(Msg_QuizResponse) );

		if( iTargetID == 10 )		  info->nResult = 1;
		else if( iTargetID == 11 )    info->nResult = 2;
		else if( iTargetID == 12 )    info->nResult = 3;
		else if( iTargetID == 13 )    info->nResult = 4;

		g_pNetWorkMgr->ReplyQuiz( info );
		g_cUIManager->HT_HideWindow( _DIALOG_QUIZ );
	}
}

//----------컨트롤----------//
HTRESULT CHTGameSystem::HT_hrGameSystemControl( HTfloat fElapsedTime )
{
	//	아이템 컨트롤 생성
	g_cItemControl->HT_vItemControl_Control();
	//	아이템 시스템
	g_cItemSystem->HT_vItemSystem_Control();
	//	미니맵
	g_cMiniMap->HT_vMiniMap_Control( HTvector3( 0, 0, 0 ) );
	//	-NPC_시스템-----//
	g_cNPCControl->HT_vNPCControl_Control();
	//	포탈 위치 체크
	g_cPortal->HT_vPortal_CharPos_Check();
	//	튜토리얼 시스템
	g_cTutorialSystem->HT_bTutorialControl();
	//	메인바_스케쥴러
	g_pMainBar->HT_vMainBar_Control( fElapsedTime );
	//	배경음악-필드인지 마을인지
	g_cMapInfo->HT_vBGMControl(g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER);
	//	3분에 한번씩 채팅 메시지 날리기 위해
	if ( g_cIndividualStore )	g_cIndividualStore->HT_vIndividualStore_Control_Chatting();
	//	Quick Slot
	g_cQuickSlot->HT_vContinueTimeCheck();
	//	Duel System
	g_pDuelSystem->HT_vDuel_Update();

	return HT_OK;
}

//----------서버에서 패킷 내려받기-캐릭터 기본 데이타----------//
HTvoid CHTGameSystem::HT_vGameSystem_UpDateUI( PS_SCP_RESP_UPDATE_UI info )
{
    //	이동속도 셋팅
	this->HT_vGameSystem_SetCharMoveSpeed( info );
	//	Default 공격 속도 셋팅
	this->HT_vGameSystem_SetCharAttackSpeed( info );
	//	남은 Chakra Point, 남은 Skill Point스킬 인벤토리에 셋팅
	g_cSkillInventory->HT_vSkillInventory_SetSkillPoint( info->snSPRemaining, info->snCasteSPRemaining );
	//	최대 HP
	g_cMainCharacter->HT_nMainChar_SetMAXHP( info->iMaxHP );
	//	현 HP
	if( info->iHP > g_cMainCharacter->HT_nMainChar_GetResentHP() )
	{
        g_cMainCharacter->HT_nMainChar_SetCurHP( info->iHP );
	}
	//	현 TP
	g_pMainBar->HT_vMainBar_SetCurTP( info->iTP, info->iMaxTP );
	////	MainCharacter의 현재 x, z
	//g_cMainCharacter->HT_vMainChar_SetCellPosition( info->snX, info->snZ );
	//	LevelUP에 필요한 프라나
	g_pMainBar->HT_vMainBar_SetNeedPrana( info->iMaxPrana );
	//	현재 프라나
	g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->iPrana );
	// 루피아
	g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->iGold );
	//	캐릭터 상태 클래스에 정보 셋팅
	g_cStatus->HT_vStatus_ChangeParams(info);
	// Tantra V3 전용 
	g_cUIStatus->HT_vStatus_ChangeParams(info);

	if (g_oMainCharacterInfo.byClass1 != info->byClass1)
	{
		g_oMainCharacterInfo.byClass1 = info->byClass1 ;
		g_oMainCharacterInfo.byClass2 = info->byClass2 ;

		g_cUIStatus->HT_vStatus_SetInfo();	// UI 갱신
		g_cUISkillWindow->HT_vSkillWindow_SetInfo();	// UI 갱신
	}

	g_oMainCharacterInfo.byClass1 = info->byClass1 ;
	g_oMainCharacterInfo.byClass2 = info->byClass2 ;

	// 계급 내려받기	(2005. 1 31 선영범)
	g_byteMainCharacterCaste = info->byCaste ;

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_Update_UI CurHP:%d, MaxHP:%d", info->iMaxHP, info->iHP );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------서버에서 패킷 내려받기-캐릭터 최소화한 데이타----------//
HTvoid CHTGameSystem::HT_vGameSystem_UpDate_Status( PS_SCP_RESP_UPDATE_STATUS info )
{
	if( info->snKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		CHTString szMessage;
		//HTint iTempValue;
		//	현재 프라나
		//iTempValue = info->iPrana - g_cMainCharacter->HT_dwMainChar_GetTotalPrana();
		m_iMessageVal = info->iPrana - g_cMainCharacter->HT_dwMainChar_GetTotalPrana();
		if( m_iMessageVal > 0 )
		{
           	//szMessage.HT_szFormat("프라나 %d을(를) 획득했습니다.", iTempValue );
			HT_vGameSystem_SetMessage( eMsgAttackReceivePrana, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
		}
		g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->iPrana );
		//	현 HP
		//iTempValue = info->iHP - g_cMainCharacter->HT_nMainChar_GetResentHP();
		//m_iMessageVal = info->iHP - g_cMainCharacter->HT_nMainChar_GetResentHP();
		//if( m_iMessageVal > 0 )
		//{
		//         	//szMessage.HT_szFormat("HP %d이(가) 회복되었습니다.", iTempValue );
		//	HT_vGameSystem_SetMessage( eMsgCharacterRecoveryHP, &szMessage );
		//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
		//}
		g_cMainCharacter->HT_nMainChar_SetCurHP( info->iHP );
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetMainCharHPCorrect( info->iHP );
		//	현 TP
		g_pMainBar->HT_vMainBar_SetCurTP( info->iTP, 0 );
		//	현 카르마
		g_oMainCharacterInfo.snKarma = info->snKarma;
        
		//	Set 서버에서 내려오는 캐릭터의 각종 상태
		g_cMainCharacter->HT_vMainCHar_SCP_SetAffections( info->iAffections );

		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_UpdateUI_Status:HP:%d, Prana:%d, Affections:%x", info->iHP, info->iPrana, info->iAffections );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	OtherObject
	else
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUpdateStatus( info );
	}
}

//----------서버에서 패킷 내려받기-최초 초기화에서 캐릭터 죽었을 때----------//
HTvoid CHTGameSystem::HT_vGameSystem_NetWorkInitCharDeath()
{
	//----------캐릭터 죽는 액션----------//
	g_cMainCharacter->HT_nMainChar_SetCurHP( 0 );
	g_cMainCharacter->HT_vMainChar_NetWorkDieMotion();

	//----------서버에서 패킷 내려받기-사망 확인창 뛰우기----------//
	this->HT_vGameSystem_OpenDeathWindow();

	// 메세지
	CHTString szMessage;
	//	주신전지역에서 경고 메시지
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		// [경고]주신전에서 사망으로 인한 패널티는 없습니다. 그러나 주신 포인트가 0인 경우 
		// 캐릭터 사망시 해당 레벨 프라나의 5%를 상실합니다.
		HT_vGameSystem_SetMessage( eMsgAttackTrimuritiZoneWarning, &szMessage);
		//	공지창 켬
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( szMessage.HT_szGetString() );
	}
}

//----------서버에서 패킷 내려받기-캐릭터 사망----------//
HTvoid CHTGameSystem::HT_vGameSystem_NetWorkDeath( HTshort snTribe, CHTString strKillerName )
{
	//----------캐릭터 죽는 액션----------//
	g_cMainCharacter->HT_nMainChar_SetCurHP( 0 );
	g_cMainCharacter->HT_vMainChar_NetWorkDieMotion();
	g_cMainCharacter->HT_vMainChar_SetInitAffectionsEffect();

	//	현재 돌아가고 있는 쿨타임을 전부 초기화 해준다.
	g_cQuickSlot->HT_vTotalCoolTimeInit();

	// 만약 아이템을 이동중일 경우에는 취소 시킨다.
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive( /*_DIALOG_INVEN*/ );

	//----------서버에서 패킷 내려받기-사망 확인창 뛰우기----------//
	this->HT_vGameSystem_OpenDeathWindow();

	// 메세지
	CHTString szMessage;
	//	주신전지역에서 경고 메시지
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		// [경고]주신전에서 사망으로 인한 패널티는 없습니다. 그러나 주신 포인트가 0인 경우 
		// 캐릭터 사망시 해당 레벨 프라나의 5%를 상실합니다.
		HT_vGameSystem_SetMessage( eMsgAttackTrimuritiZoneWarning, &szMessage);
		//	공지창 켬
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( szMessage.HT_szGetString() );
	}

	//	메인캐릭터가 죽었을때
	//	킬러 네임을 셋팅
	if( snTribe > 128 )
	{
		if( g_pParamMgr->HT_bGetMonsterName( snTribe, &m_strKillerName ) == false )
		{
			m_strKillerName.HT_szFormat( "%d", snTribe );
		}
	}
	else
	{
		m_strKillerName = strKillerName;
	}

	// [%s에 의해 사망하였습니다.]", m_strKillerName.HT_szGetString() );
	HT_vGameSystem_SetMessage( eMsgCharacterDead, &szMessage);
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
}

//----------서버에서 패킷 내려받기-사망 확인창 뛰우기----------//
HTvoid CHTGameSystem::HT_vGameSystem_OpenDeathWindow()
{
	m_bReqReenDlgSw = HT_TRUE;

	CHTString strMessage;
	for( HTint i=0 ; i<3 ; i++ )
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, i, _T("") );

	// 현재 위치가 요새전이라면 부활 위치를 고를 수 있는 창을 띄우고 그렇지 않으면 일반 확인창을 띄운다. 선영범 2005. 3. 25
	if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
	{
		// 마우스 무빙상태 펄스로 해서 아이콘 이동중이였다면 취소시킴
       	g_cUIManager->HT_CancelSlotBoxImageMoving();
		// 요새전 부활창 띄움
		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalArena, &strMessage, _T(""), _T("") );	//	아레나 관중석에서 부활(20000 루피아 소모
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalSavedZone, &strMessage, _T(""), _T("") );	//	저장된 장소에서 부활
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, strMessage );
		//	공성전과 요새전에서 사망했을때
		m_iButtonType = 1;
	}
	else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
	{
		// 마우스 무빙상태 펄스로 해서 아이콘 이동중이였다면 취소시킴
       	g_cUIManager->HT_CancelSlotBoxImageMoving();
		// 요새전 부활창 띄움
		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalFotress, &strMessage, _T(""), _T("") );	//	버려진 요새에서 부활
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalNorthViruCastle, &strMessage, _T(""), _T("") );	//	비류성 북쪽 성문 근처에서 부활
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalSavedZone, &strMessage, _T(""), _T("") );	//	저장 지역에서 부활
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 2, strMessage );
		//	공성전과 요새전에서 사망했을때
		m_iButtonType = 1;
	}
	else
	{
		// 확인 버튼을 누르면 저장지역에서 다시 태어납니다.
		HT_vGameSystem_SetMessage( eMsgCharacterRebirth, &strMessage);

		// 마우스 무빙상태 펄스로 해서 아이콘 이동중이였다면 취소시킴
		g_cUIManager->HT_CancelSlotBoxImageMoving();

		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSG );
		g_cUIManager->HT_MessageBox( _DIALOG_DEATHMSG, strMessage.HT_szGetString(), 4 );
	}
}

//	OtherObjectSystem에서 셋팅함
HTvoid CHTGameSystem::HT_vGameSystem_SetKillerName( CHTString strKillerName )
{
	m_strKillerName = strKillerName;
}

//	사무다바 스킬 사용해도 돼냐고 물어보기
HTvoid CHTGameSystem::HT_vGameSystem_ReqAnswerUseSamudaba( int iEchoType, int iKeyID, HTbyte byResponse, HTbyte byData )
{
	//	나 자신을 클릭하고 있어도 스킵
	if( g_cMainCharacter->HT_iMainChar_GetKeyID() == iKeyID )
		return;
	////	다른 캐릭이 살아 있어도 스킵
	//if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetLiveFromKeyID( iKeyID ) == HT_TRUE )
	//	return;

	Msg_Echo* info = HT_NULL;
	info = new Msg_Echo;
	memset( info, 0, sizeof(Msg_Echo) );

	info->iEchoID = iEchoType;
	info->iKeyID = iKeyID;
	info->byResponse = byResponse;
	info->byData = byData;
	g_pNetWorkMgr->RequestMsgEcho( info );
	//	요청자일 경우에만 적용
	if( byResponse == 0 )
        m_bAnswerSamudabaSw = HT_TRUE;

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_CouponEvent Number : %d", info->iEchoID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

	//	Samudaba Delay Time
	if (byResponse == 0)	// 스킬 시전자만 정보기록
		m_dwSamudabaDelayTime = timeGetTime();
}

//	사무다바 스킬 사용해도 돼냐고 물어본것 응답 받기
HTvoid CHTGameSystem::HT_vGameSystem_ReciveAnswerUseSamudaba( Msg_Echo* info )
{
	//	사무다바 사용 요청 받았을때
	if( info->byResponse == 0 && g_cMainCharacter->m_bMainChar_Live != HT_TRUE)
	{
		//	UserID Answer Samudaba
		m_iUserIDAnswerSamudaba	= info->iKeyID;
		CHTString strTemp;
		strTemp.HT_szFormat( "%d", info->byData );
		//
		CHTString szMessage;
		HT_g_Script_SetMessage( eMsgCommonAnswerUseSamudaba, &szMessage, g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(info->iKeyID), strTemp.HT_szGetString() );
		g_cUIManager->HT_MessageBox( _DIALOG_ANSWERUSESAMUDABA, szMessage.HT_szGetString(), 1 );
		// 시전자의 시전시간을 체크함
		m_dwSamudabaDelayTime = timeGetTime();

		//기존의 부할창은 닫아준다.
		if( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSG ) ) 
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

		// 요새전에서 사용시엔 요새전 부활창을 닫아주어야 한다.
		if ( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) )
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );

	}
	//	승낙 받았을때
	else if( info->byResponse == 1 )
	{
		//	Answer Samudaba
		if( !m_bAnswerSamudabaSw )
			return;
		m_bAnswerSamudabaSw = FALSE;

		//	거리 체크하여 너무 멀리 떨어져 있거나 제한 시간이 초과(10초)했으면 Skip
		HTvector3 vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( info->iKeyID );
		HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( vecTargetPos, vecMainCharPos );
		if( nRange > 200 )
			return;

		DWORD dwPassTime = timeGetTime();
		if( dwPassTime > m_dwSamudabaDelayTime+10000 )
			return;

		//----------액션 스킬 셋팅----------//
		g_cMainCharacter->HT_vMainChar_SetActionSkill( HT_SKILLINDEX_SAMUDABA );
	}

	//a->b 요청시 a: iEchoID=1, iKeyID=부활시킬대상(서버로 전송)
	//서버->b        iKeyID=부활시키겟다는 간달,  byResponse=0
	//b->a 응답시    iKeyID=부활시키겟다는 간달,  byResponse=1 or 2
	//서버->a        iKeyID=부활시킬대상,         byResponse=1 or 2
}

//----------서버에서 패킷 내려받기-캐릭터 리젼 요청----------//
HTvoid CHTGameSystem::HT_vGameSystem_CSP_INIT_REGEN_CHAR( BYTE byType )
{
	//-----캐릭터 리젼 정보를 요청한다-----//
	PS_CSP_REQ_INIT_REGEN_CHAR info = HT_NULL;
	info = new S_CSP_REQ_INIT_REGEN_CHAR;
	info->byConnType = 2;//byType;
	g_pNetWorkMgr->RequestReqInitRegenChar( info );
	HT_DELETE( info );

	//----------공격중이면 취소----------//
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 26 );
}

//----------서버에서 패킷 내려받기-캐릭터 사망시 이닛 리젼요청 결과----------//
HTvoid CHTGameSystem::HT_vGameSystem_SCP_INIT_REGEN_CHAR( PS_SCP_RESP_INIT_REGEN_CHAR info )
{
    //	에러 처리
	if(	info->byZone <= 0 )
		info->byZone = 1;

	//	혹시 리젠 대화상자가 떠있다면
	if( m_bReqReenDlgSw )
		g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

	// 요새전에서 사용시엔 요새전 부활창을 닫아주어야 한다.
	if ( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) )
		g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );

	//	마지막 저장위치가 다른 존일때
	if( info->byZone != g_wResentZoneServerID )
	{
     	//	현재 서버와 연결 끊음
		g_pNetWorkMgr->DisConnect();

		//char test[100];
		//sprintf(test, " 서버로 받은 존번호 = %d", info->byZone);
		//MessageBox(NULL, test, test, MB_OK);
		g_wResentZoneServerID = info->byZone;

		//	존서버 No, IP와 Port를 전역으로 저장
		g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
		g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;

		//	서버와의 DisConnect Check Seting
		g_bPortalServerDisConnectCheckSw	= HT_FALSE;
		//	존 서버 커넥트를 기다리도록 설정
		g_bZoneServerSwitching = HT_TRUE;
		//	연결형태 셋팅
		//	확인버튼을 눌러서 이닛커넥트 요청했는지를 안다.
		if( m_bUserReqInitRegenChar	)
            g_byInitConnectType = CONNECT_TYPE_DIE;
		else
			g_byInitConnectType = CONNECT_TYPE_FIRST;
		m_bUserReqInitRegenChar = FALSE;
	}
	else
	{
		info->snDegree;     
		info->dwGameTime;   
		info->byWhether;    
		g_cMainCharacter->HT_vMainChar_SCP_INIT_REGEN_CHAR( info->snX, info->snZ );
	}

	//	내가걸려있는 스킬 초기화
	g_pMainBar->HT_vMainBar_MySkillInit();
}

//----------서버에서 패킷 내려받기-서버와 연결이 끊어졌을 때----------//
HTvoid CHTGameSystem::HT_vGameSystem_ServerDisConnect_SetDlg( CHTString strMsg )
{
	if( m_bServerDisConnectSw )
		return;

	m_dwServerDisConnectTimeOut = GetTickCount();
	m_bServerDisConnectSw = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_DISCONNECTSERVER );
	g_cUIManager->HT_MessageBox( _DIALOG_DISCONNECTSERVER, strMsg.HT_szGetString(), 0 );
}

//----------서버에서 패킷 내려받기-서버와 연결이 끊어졌을 때----------//
HTRESULT CHTGameSystem::HT_vGameSystem_ServerDisConnect_CheckDlg( HTint iButtonNo )
{
	//----------서버가 죽었을때 확인 스위치----------//
	if( m_bServerDisConnectSw == HT_FALSE )
		return HT_FAIL;
	
	if( iButtonNo == _BTN_MSG_OK )
	{
		// 게임 종료 대화창 뛰우기
		g_byReStartButtonCode = 10;
	}

	return HT_OK;
}
//	서버에서 패킷 내려받기-Quiz
HTvoid CHTGameSystem::HT_vGameSystem_SCP_Quiz( Msg_Quiz* info )
{
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_QUIZ, 3, info->pszQuiz );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_QUIZ, 10, info->pszQuizSelect1[0] );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_QUIZ, 11, info->pszQuizSelect1[1] );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_QUIZ, 12, info->pszQuizSelect1[2] );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_QUIZ, 13, info->pszQuizSelect1[3] );
	g_cUIManager->HT_ShowWindow( _DIALOG_QUIZ );
}

HTvoid CHTGameSystem::HT_vGameSystem_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
	{
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	}
	else
	{
		szString.HT_hrCleanUp();
	}
	
	// 변수가 3개 일 때
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vGameSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGameSystem_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vGameSystem_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vGameSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGameSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vGameSystem_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
	{
		*pszMessage = szString;
	}
}

HTvoid CHTGameSystem::HT_vGameSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		case eMsgParamEnemyName		:
			*pszParam = m_strKillerName;
			break;

		// 회복된 HP
		case eMsgParamRecoveryHp	:
		// 받은 프라나
		case eMsgParamRecoveryPrana	:	
			pszParam->HT_szFormat("%d", m_iMessageVal );
			break;

		default:
			break;
	}
}

//	Set RequestMoveZoneServerCheck
HTvoid CHTGameSystem::HT_vSetRequestMoveZoneServer( HTbool bType )
{
	m_bRequestMoveZoneServerCheck = bType;	

	if( m_bRequestMoveZoneServerCheck )
	{
		m_bRequestMoveZoneServerStartTime = timeGetTime() - 10000;
	}
}

//	RequestMoveZoneServer을 날리고 5초동안 응답을 받지 못하면 종료한다.
HTvoid CHTGameSystem::HT_vRequestMoveZoneServerCheck()
{
	if( !m_bRequestMoveZoneServerCheck )
		return;

	HTdword dwPassTime = timeGetTime();
	if( dwPassTime > m_bRequestMoveZoneServerStartTime + 10000 )
	{
		m_bRequestMoveZoneServerStartTime = dwPassTime;
		//	Request Move Zone Server
		g_bZoneServerSwitching = HT_FALSE;

		PS_CSP_REQ_MOVE_ZONE_SERVER info = NULL;
		info = new S_CSP_REQ_MOVE_ZONE_SERVER;
		info->dwEvent = (DWORD)g_iLoginResultID;
		CHTString::HT_hrStringCopy( info->AccountName, g_strLoginID, ACCOUNTNAME_LENGTH );
		CHTString::HT_hrStringCopy( info->AccountPass, g_strLgoinPasswordMD5, ACCOUNTPASS_LENGTH );
		CHTString::HT_hrStringCopy( info->szCharName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
		for( int i=0 ; i<4 ; i++ )	info->snVersion[i] = g_snVersionCheck[i];
		g_pNetWorkMgr->RequestReqMoveZoneServer( info ); //fors_debug 맣룐관뒤寧꼍돨뒈렘
		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MoveZoneServer");
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		HT_DELETE( info );
	}
}

//----------랜더러----------//
HTvoid CHTGameSystem::HT_hrGameSystemRender()
{
	//-----Item-----//
	g_cItemSystem->HT_hrSystemRender();
}

//	IME Render
HTvoid CHTGameSystem::HT_vGameSystemRender_IME()
{
	if( !g_cUIManager )
		return;

	//	Get Cursor Pos
	HTvector3 vecCursorPos = g_cUIManager->HT_GetEditBoxCursorPos();

	if( g_iInationalType == INATIONALTYPE_KOREA ||
		g_iInationalType == INATIONALTYPE_JAPEN )
	{
		//	IME_CandiList
		for( HTint i=0 ; i<10 ; i++ )
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
							HTvector3( vecCursorPos.x, vecCursorPos.y, 0.0f ), g_ColorTable[12], HT_COLOR( 0.0f, 0.5f, 0.5f, 0.7f ), 3.0f );
			//CHTString strTemp;
			//strTemp.HT_szFormat( "%d:%d:%s\n", vecCursorPos.x, vecCursorPos.y, g_strCompStr );
			//HT_g_vLogFile( strTemp );
		}
	}

	//	IME_Description
	if( g_iInationalType == INATIONALTYPE_CHINA || 
		g_iInationalType == INATIONALTYPE_TAIWAN )
	{
		if( !g_strImeName.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_strImeName.HT_szGetString(), 
							HTvector3( 383, (HTfloat)(g_pEngineHandler->HT_iGetScreenHeight()-16 ), 0.0f ), g_ColorTable[12], HT_COLOR( 0.5f, 0.0f, 0.5f, 0.7f ), 3.0f );
		}
	}
}

//	메모리 스피드핵을 막기위한 뭐 그런것..
HTvoid CHTGameSystem::HT_vGameSystem_SetCharMoveSpeed( PS_SCP_RESP_UPDATE_UI info )
{
	if( info->byteSpeed1 >= 104  && info->byteSpeed1 <= 112	&& 
		info->byteSpeed2 >= 15 && info->byteSpeed2 <= 23 && 
		info->byteSpeed3 >= 74  &&  info->byteSpeed3 <= 82 )
	{
		//	이동속도
		g_byteSpeed1 = info->byteSpeed1;
		g_byteSpeed2 = info->byteSpeed2;
		g_byteSpeed3 = info->byteSpeed3;
		g_byteSpeedCorrection = info->byteSpeedCorrection;
		g_byteSpeedParity = info->byteSpeedParity;
	}
	else
	{
		// 여기서는 서버에 다시 패킷 요청??? 또는 에러 처리
		//	이동속도
		g_byteSpeed1 = 0;
		g_byteSpeed2 = 0;
		g_byteSpeed3 = 0;
		g_byteSpeedCorrection = 0xf;
		g_byteSpeedParity = 0;
	}
}

//	메모리 스피드핵을 막기위한 뭐 그런것..
HTvoid CHTGameSystem::HT_vGameSystem_SetCharAttackSpeed( PS_SCP_RESP_UPDATE_UI info )
{
	if ( info->byteAS1 >= 26 && info->byteAS1 <= 30 && 
		 info->byteAS2 >= 61 && info->byteAS2 <= 68	&& 
		 info->byteAS3 >= 27 && info->byteAS3 <= 34	&& 
		 info->byteAS4 >= 15 && info->byteAS4 <= 30 )
	{
		//	공격속도 패킷
		g_byteAS1 = info->byteAS1;
		g_byteAS2 = info->byteAS2;
		g_byteAS3 = info->byteAS3;
		g_byteAS4 = info->byteAS4;
		g_byteParity = info->byteParity;
	}
	else
	{
		//	공격속도 패킷
		g_byteAS1 = -126;
		g_byteAS2 = 61;
		g_byteAS3 = 27;
		g_byteAS4 = -101;
		g_byteParity = 0;
	}
}

