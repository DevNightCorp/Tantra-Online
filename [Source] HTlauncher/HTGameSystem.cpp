
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTGameSystem.h"

//-----�޴�������_0:����,1:����Ʈ,2:�κ��丮,3:��ų,4:��Ƽ,5:�ý���
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
	//-----���� �κ��丮-----//
	HT_DELETE( g_cEquipInventory );
    //-----��ų �κ��丮-----//
	HT_DELETE( g_cSkillInventory );
    //-----��ŷ�, íũ�� �ý���-----//
	HT_DELETE( g_cNPCControl);

	//-----�̴ϸ�-----//
	HT_DELETE( g_cMiniMap );
	//-----��ȯ �ý���-----//
	HT_DELETE( g_cExchangeSystem );
	//-----ĳ���� �������ͽ�-----//
	HT_DELETE( g_cStatus );
	//-----��Ƽ-----//
	HT_DELETE( g_cParty );
	//-----����Ʈ-----//
	HT_DELETE( g_cQuest );
	//-----�ý���-----//
	HT_DELETE( g_cSystem );
	//-----����â-----//
	HT_DELETE( g_cObjectInfo );
	//-----�� ����-----//
	HT_DELETE( g_cMapInfo );
	//-----�ּҷ�-----//
	HT_DELETE( g_cAddress );
	//-----�����ý���-----//
	HT_DELETE( g_pDuelSystem );
	//-----Chatting-----//
	HT_DELETE( g_cChatting );
	//-----��ų �ý���-----//
//	HT_DELETE( g_cSkillSystem );
	//-----2D ��������Ʈ��-----//
//	HT_DELETE( g_2DObjectMgr );
	//	������ Ŭ����
	HT_DELETE( g_cQuickSlot );
	//	��� Ŭ����
	HT_DELETE( g_cCommand );

	// ���� ����
    HT_DELETE( g_cIndividualStore );

	g_cUIManager->HT_DeleteWindow( _DIALOG_DEATHMSG );
	g_cUIManager->HT_DeleteWindow( _DIALOG_DEATHMSGFOTRESS );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_DISCONNECTSERVER );
	g_cUIManager->HT_DeleteWindow( _DIALOG_ANSWERUSESAMUDABA );
	g_cUIManager->HT_DeleteWindow( _DIALOG_REVIVEWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WEBBROWSER );
}

//-----GS ����Ÿ Ŭ���� �ϱ�-----//
HTvoid CHTGameSystem::HT_vGSDataCleanUp()
{
	//-----2D ������Ʈ Ŭ����-----//
	if( g_2DObjectMgr) g_2DObjectMgr->HT_2DObjectMgrCleanUp();
	HT_DELETE( g_2DObjectMgr );

	//-----���ι� Ŭ����-----//
	HT_DELETE( g_pMainBar );
	
	//-----������ ���� Ŭ����-----//
	if( g_cItemSystem) g_cItemSystem->HT_vItemSystem_CleanUp();
	HT_DELETE( g_cItemSystem );	
	if( g_cItemControl ) g_cItemControl->HT_vItemControl_CleanUp();
	HT_DELETE( g_cItemControl );

	//-----��ų �κ��丮 Ŭ����-----//
	if( g_cSkillInventory ) g_cSkillInventory->HT_vSkillInventory_CleanUp();
	HT_DELETE( g_cSkillInventory );
	//-----��ų �ý��� Ŭ����-----//
	if( g_cSkillSystem) g_cSkillSystem->HT_vSkillSystem_CleanUp();
	HT_DELETE( g_cSkillSystem );

	//-----���� �κ��丮 Ŭ����-----//
	if( g_cEquipInventory ) g_cEquipInventory->HT_vEquipInventory_CeleanUp();
	HT_DELETE( g_cEquipInventory );

	//-----�̴ϸ� Ŭ����-----//
	if( g_cMiniMap) g_cMiniMap->HT_vMinMap_CeleanUp();
	HT_DELETE( g_cMiniMap );

	//-----��ȯ �ý��� Ŭ����-----//
	if( g_cExchangeSystem) g_cExchangeSystem->HT_vExchange_CleanUp();
	//HT_DELETE( g_cExchangeSystem );

	//----------ĳ���� �������ͽ� Ŭ����----------//
	if(g_cStatus) g_cStatus->HT_vStatus_CleanUp();
	HT_DELETE( g_cStatus );

	//----------��Ƽ Ŭ����----------//
	if(g_cParty) g_cParty->HT_vParty_CleanUp();
	//HT_DELETE( g_cParty );

	//----------Ʃ�丮�� �ý��� Ŭ����----------//
	HT_DELETE( g_cTutorialSystem );

	//----------����Ʈ Ŭ����----------//
	if(g_cQuest) g_cQuest->HT_vQuest_CleanUp();
	HT_DELETE( g_cQuest );

	//----------�ּҷ� Ŭ����----------//
	if( g_cAddress ) g_cAddress->HT_vAddress_Delete();
	//HT_DELETE( g_cAddress );

	//----------�ý��� Ŭ����----------//
	if( g_cSystem ) g_cSystem->HT_vSystem_CleanUp();
	//HT_DELETE( g_cSystem );

	//-----------------------------------------------------------------------------//
	//  ���� : ����â Ŭ����
	//  �ۼ����� / �ۼ��� : 2002.12.27_�輱��
	//-----------------------------------------------------------------------------//
	//HT_DELETE( g_cObjectInfo );

	//----------������ Ŭ����----------//
	HT_DELETE( g_cMapInfo );

	//-----�������� ������ Ŭ����-----//
	if( g_pNotifyWindow && g_pNotifyWindow->isLoaded() ) g_pNotifyWindow->Unload();
	HT_DELETE( g_pNotifyWindow );

	//------�̺�Ʈ â Ŭ����-------//
	HT_DELETE( g_pEventWindow );

	//-----ä�� Ŭ����-----//
	if( g_cChatting ) g_cChatting->HT_vChatting_CleanUp();
	//HT_DELETE( g_cChatting );
	
	//----------��Ż Ŭ����----------//
	HT_DELETE( g_cPortal );

	//----------GM Ŭ����----------//
	HT_DELETE( g_cGMSystem );

	//----------���� ��ȭ���� ----------//
	m_bReqReenDlgSw					= HT_FALSE;

	//----------������ �׾����� Ȯ�� ����ġ----------//
	m_bServerDisConnectSw			= HT_FALSE;

	//-----NPC ���� Ŭ���� -----//
	if(g_cNPCControl)	g_cNPCControl->HT_vNPCControl_CleanUp();
	//HT_DELETE( g_cNPCControl );

	//----------��� Ŭ����----------//
	if( g_cGuildSystem )	g_cGuildSystem->HT_vGuild_Delete();
	HT_DELETE( g_cGuildSystem );

	//----------����ų Ŭ����----------//
	HT_DELETE( g_cQuickSlot );

	//	��� Ŭ����
	HT_DELETE( g_cCommand );

	//	Init QuickSlot
	HT_DELETE( g_cQuickSlot );

	// �׺� Ŭ����
	HT_DELETE( g_cGamble );

	// ChatRoom Ŭ����
	HT_DELETE( g_cChatRoom );

	// ������ Ŭ����
	HT_DELETE( g_pSiege );

	// ��Ź���� Ŭ����
	HT_DELETE( g_cRentalStore );

}

HTRESULT CHTGameSystem::HT_hrGameSystemInit()
{

	// V3 ���� ���� �߰��� �������... (v2 �������� ���� �о�鿩�� �Ѵ�. v2�������� v3���� �Լ��� ����ϹǷ�...)
	if( !g_cUINPCWindow )
	{
		g_cUINPCWindow					= HT_NULL;
		g_cUINPCWindow					= new CHTUINPCWindow;
	}
	g_cUINPCWindow->HT_vNPCWindow_Init(); // ������ ���� ������ ���� ����ؾ� �Ѵ�.

	if( !g_cUIStatus )
	{
		g_cUIStatus						= HT_NULL;
		g_cUIStatus						= new CHTUIStatus;
	}
	g_cUIStatus->HT_vStatus_Init(); // Tantra V3 ����

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

	// ����
	if( !g_cUIRefineWindow )
	{
		g_cUIRefineWindow				= HT_NULL;
		g_cUIRefineWindow				= new CHTUIRefineWindow;
	}
	g_cUIRefineWindow->HT_vRefineWindow_Init();

	// �ں�
	if( !g_cUIEmblemWindow )
	{
		g_cUIEmblemWindow				= HT_NULL;
		g_cUIEmblemWindow				= new CHTUIEmblemWindow;
	}
	g_cUIEmblemWindow->HT_vEmblemWindow_Init();


	//	������
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

	//	��� Ŭ���� ����
	if( !g_cCommand )
	{
		g_cCommand						= HT_NULL;
		g_cCommand						= new HTCommand;
	}
	g_cCommand->HT_vCommand_Init();

	//-----2D ������Ʈ ����-----//
	g_2DObjectMgr = HT_NULL;
	g_2DObjectMgr = new CHT2DObjectMgr;
	g_2DObjectMgr->HT_2DObjectMgrInit();

	//-----���ι� ����-----//
	g_pMainBar = HT_NULL;
	g_pMainBar = new CHTMainBar;
	g_pMainBar->HT_vLoad();
	
	//-----������ ���� ����-----//
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

	//-----��ų �ý��� ����-----//
	g_cSkillSystem = HT_NULL;
	g_cSkillSystem = new HTSkillSystem;
	g_cSkillSystem->HT_hSkillSystemInit();

	//-----��ų �κ��丮 ����-----//
	g_cSkillInventory = HT_NULL;
	g_cSkillInventory = new CHTSkillInventory;
	g_cSkillInventory->HT_hrSkillInventoryInit();

	//-----���� �κ��丮 ����-----//
	g_cEquipInventory = HT_NULL;
	g_cEquipInventory = new CHTEquipInventory;
	g_cEquipInventory->HT_hrInit();

	//-----�̴ϸ� ����-----//
	if( !g_cMiniMap )
	{
		g_cMiniMap = HT_NULL;
		g_cMiniMap = new CHTMiniMap;
	}
	g_cMiniMap->HT_hrMiniMap_Init();
	g_cMiniMap->HT_vTotalMiniMap_Load();

	//-----��ŷ�, íũ�� �ý��� ����-----//
	if( !g_cNPCControl )
	{
		g_cNPCControl = HT_NULL;
		g_cNPCControl = new CHTNPCControl;
	}
	g_cNPCControl->HT_vNPCControl_Init();

	//-----��ȯ �ý��� ����-----//
	if( !g_cExchangeSystem )
	{
		g_cExchangeSystem = HT_NULL;
		g_cExchangeSystem = new HTExchange;
	}
	g_cExchangeSystem->HT_hrExchange_Init();

	//----------ĳ���� �������ͽ�----------//
	g_cStatus						= HT_NULL;
	g_cStatus						= new HTStatus;
	g_cStatus->HT_vStatus_Init();	// ������ ���� ����ؾ� �Ѵ�.
			
	//----------��Ƽ----------//
	if( !g_cParty )
	{
		g_cParty						= HT_NULL;
		g_cParty						= new HTParty;
	}
	g_cParty->HT_vParty_Init();

	//----------Ʃ�丮�� �ý���----------//
	g_cTutorialSystem				= HT_NULL;
	g_cTutorialSystem				= new HTTutorialSystem;
	g_cTutorialSystem->HT_vInit();

	//----------����Ʈ----------//
	g_cQuest						= HT_NULL;
	g_cQuest						= new HTQuest;
	g_cQuest->HT_vQuest_Init();

	//----------�ּҷ�----------//
	if( !g_cAddress )
	{
		g_cAddress						= new HTAddress;
	}
	g_cAddress->HT_vAddress_Init();

	//----------���� �ý���----------//
	if( !g_pDuelSystem )
	{
		g_pDuelSystem				= new HTDuelSystem;
	}

	//----------�ý���----------//
	if( !g_cSystem )
	{
		g_cSystem						= HT_NULL;
		g_cSystem						= new HTSystem;
	}
	g_cSystem->HT_vSystem_Init();

	//----------��� �ý���----------//
	if( !g_cGuildSystem )
	{
		g_cGuildSystem					= HT_NULL;
		g_cGuildSystem					= new HTGuild;
		//	��� �ý��� �ʱ�ȭ
		g_cGuildSystem->HT_vGuild_Init();
	}

	//---------- ����â -------------//
	if( !g_cObjectInfo )
	{
		g_cObjectInfo					= HT_NULL;
		g_cObjectInfo					= new HTObjectInfo;
	}
	g_cObjectInfo->HT_vObjectInfo_Init();

	//---------- ���λ��� ------------//
	if( !g_cIndividualStore )
	{
		g_cIndividualStore				= HT_NULL;
		g_cIndividualStore				= new CHTIndividualStore;
	}
	g_cIndividualStore->HT_vIndividualStore_Init();

	//---------- ��Ź���� ------------//
	if( !g_cRentalStore )
	{
		g_cRentalStore				= HT_NULL;
		g_cRentalStore				= new CHTRentalStore;
	}
	g_cRentalStore->HT_vRentalStore_Init();

	//----------������----------//
	g_cMapInfo						= HT_NULL;
	g_cMapInfo						= new HTMapInfo;

	//-----�������� ������ ����-----//
	g_pNotifyWindow					= HT_NULL;
	g_pNotifyWindow					= new CHTNotifyWindow;
	g_pNotifyWindow->Load();

	//-----�̺�Ʈ ������ ����-----//
	g_pEventWindow					= HT_NULL;
	g_pEventWindow					= new CHTEventWindow;

	//-----ä�� ����-----//
	if( !g_cChatting )
	{
		g_cChatting						= HT_NULL;
		g_cChatting						= new CHTChatting;
	}
	g_cChatting->HT_vChatting_Init();
	
	//----------��Ż----------//
	g_cPortal						= HT_NULL;
	g_cPortal						= new HTPortal;
	g_cPortal->HT_vPortal_Init();

	//----------GM----------//
	g_cGMSystem						= HT_NULL;
	g_cGMSystem						= new HTGM;
	g_cGMSystem->HT_vGM_Init();

	//----------���� ��ȭ����----------//
	m_bReqReenDlgSw					= HT_FALSE;

	//----------������ �׾����� Ȯ�� ����ġ----------//
	m_bServerDisConnectSw			= HT_FALSE;

	//	For Server Connect, DisConnect Check
	//	����Ī ���� üũ
	g_bZoneServerSwitching				= HT_FALSE;
	//	�������� Connect Check
	g_bPortalServerConnectCheckSw		= HT_FALSE;
	//	�������� DisConnect Check
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;
	//	��Ż �̿��Ҷ� RequestMoveZoneServer
	m_bRequestMoveZoneServerCheck		= HT_FALSE;
	//	Zone Setting No
	g_snResentZoneSiege					= 0;
	//	Answer Samudaba
	m_bAnswerSamudabaSw					= HT_FALSE;
	//	UserID Answer Samudaba
	m_iUserIDAnswerSamudaba				= 0;
	//	Samudaba Delay Time
	m_dwSamudabaDelayTime				= 0;
	//	Ȯ�ι�ư�� ������ �̴�Ŀ��Ʈ ��û�ߴ����� �ȴ�.
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
	//	Button �Ʒ��� ���߼����� ��Ȱ(20000 ���Ǿ� �Ҹ�)
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 0, 0, 10, 20, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 20, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 0 );
	//	Button ����� ��ҿ��� ��Ȱ
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 1, 0, 10, 45, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 45, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 1 );
	//	Button ����� ��ҿ��� ��Ȱ
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 2, 0, 10, 70, 201, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 2, _T("Reserved"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_DEATHMSGFOTRESS, 2 );
	//	Button Ȯ�� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_DEATHMSGFOTRESS, 3, 159, 290, 90, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_DEATHMSGFOTRESS, 3, eMsgCommonConfirm, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 290, 90, 89, 19 );//Ȯ��
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
	//	Button ������ �ڸ����� ��Ȱ�մϴ�.
	g_cUIManager->HT_AddButtonControl( _DIALOG_REVIVEWND, 0, 0, 10, 20, 10, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_REVIVEWND, 0, eMsgRevivalRevivalCurrentPos, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 20, 380, 19 );//������ �ڸ����� ��Ȱ�մϴ�.
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_REVIVEWND, 0 );
	//	Button ����� �������� ��Ȱ�մϴ�.
	g_cUIManager->HT_AddButtonControl( _DIALOG_REVIVEWND, 1, 0, 10, 50, 10, 0, 1500, 380, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_REVIVEWND, 1, eMsgRevivalRevivalSavedZone, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 50, 380, 19 );//����� �������� ��Ȱ�մϴ�.
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_REVIVEWND, 1 );

	//	[_DIALOG_WEBBROWSER]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgRevivalWebWindow, &strMessage, _T(""), _T("") );	//	Web Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WEBBROWSER, strMessage, 801, 600, g_cGameSystem->HT_vGameSystem_InputCheckWebBrowser, 2 );//Web Window
	g_cUIManager->HT_MoveWindow( _DIALOG_WEBBROWSER, g_pEngineHandler->HT_iGetScreenWidth()/2-400, g_pEngineHandler->HT_iGetScreenHeight()/2-300 );
	//	Button Ȯ�� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_WEBBROWSER, 1, 159, 650, 565, 160, 161, 1500, 89, 22 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WEBBROWSER, 1, eMsgRevivalExitWeb, 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 650, 565, 89, 22 );//������
	g_cUIManager->HT_SetScriptMessage( eMsgRevivalWebBrowser, &strMessage, _T(""), _T("") );	//	WebBrowser�� �����մϴ�.
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_WEBBROWSER, 1, strMessage );

	//	[_DIALOG_QUIZ]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_QUIZ, _T(""), 400, 200, g_cGameSystem->HT_vGameSystem_InputCheckQuiz, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_QUIZ, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_QUIZ, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture QUIZ
	g_cUIManager->HT_AddTextureControl( _DIALOG_QUIZ, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 2, _T("Quiz"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label Quiz
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 3, _T("Current Not Quiz"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 60, 380, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_QUIZ, 3, 7 );
	//	Button �亯1
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 10, 159, 10, 120, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 10, _T("Answer1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 120, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 10 );
	//	Button �亯2
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 11, 159, 210, 120, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 11, _T("Answer2"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 210, 120, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 11 );
	//	Button �亯3
	g_cUIManager->HT_AddButtonControl( _DIALOG_QUIZ, 12, 159, 10, 150, 160, 161, 1500, 180, 25 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_QUIZ, 12, _T("Answer3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 150, 180, 25 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_QUIZ, 12 );
	//	Button �亯4
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

//	�Է� �޼��� ó��
//	Daeth Mssage
void CHTGameSystem::HT_vGameSystem_InputCheckForDeathMsg(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		if (iTargetID == -1 )
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

		if( iTargetID == 2 )
		{
			//	ä�ø�带 Ǯ����
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			//	Ȯ�ι�ư�� ������ �̴�Ŀ��Ʈ ��û�ߴ����� �ȴ�.
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
				// 2�� ���Ǿƺ��� ���� ������ ������ ����� �� ����.
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
			//-----ĳ���� ���� ������ ��û�Ѵ�-----//
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
			//	Ȯ�ι�ư�� ������ �̴�Ŀ��Ʈ ��û�ߴ����� �ȴ�.
			g_cGameSystem->m_bUserReqInitRegenChar = TRUE;
			g_pNetWorkMgr->RequestReqInitRegenChar( info );

			//-----����� �׽�Ʈ�� ���Ͽ�-----//
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
	// ������Ƽ�� ����
	if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		if( iTargetID == 2 )
		{
			//	ä�ø�带 Ǯ����
			g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );
			// ESCŰ�� ���� Ȯ��â�� �ߴ°� ���� ���� ����� �ɹ�����
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
//	�Է��Լ� ó�� Revive
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
			//	ä�ø�带 Ǯ����
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

			//-----����� �׽�Ʈ�� ���Ͽ�-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_UpgradePustica_Use : %d", info->snWarpID );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			HT_DELETE( info );
		}
	}
}
//	�Է��Լ� ó�� WebBrowser
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
//	�Է��Ѽ� ó�� Quiz
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

//----------��Ʈ��----------//
HTRESULT CHTGameSystem::HT_hrGameSystemControl( HTfloat fElapsedTime )
{
	//	������ ��Ʈ�� ����
	g_cItemControl->HT_vItemControl_Control();
	//	������ �ý���
	g_cItemSystem->HT_vItemSystem_Control();
	//	�̴ϸ�
	g_cMiniMap->HT_vMiniMap_Control( HTvector3( 0, 0, 0 ) );
	//	-NPC_�ý���-----//
	g_cNPCControl->HT_vNPCControl_Control();
	//	��Ż ��ġ üũ
	g_cPortal->HT_vPortal_CharPos_Check();
	//	Ʃ�丮�� �ý���
	g_cTutorialSystem->HT_bTutorialControl();
	//	���ι�_�����췯
	g_pMainBar->HT_vMainBar_Control( fElapsedTime );
	//	�������-�ʵ����� ��������
	g_cMapInfo->HT_vBGMControl(g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER);
	//	3�п� �ѹ��� ä�� �޽��� ������ ����
	if ( g_cIndividualStore )	g_cIndividualStore->HT_vIndividualStore_Control_Chatting();
	//	Quick Slot
	g_cQuickSlot->HT_vContinueTimeCheck();
	//	Duel System
	g_pDuelSystem->HT_vDuel_Update();

	return HT_OK;
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� �⺻ ����Ÿ----------//
HTvoid CHTGameSystem::HT_vGameSystem_UpDateUI( PS_SCP_RESP_UPDATE_UI info )
{
    //	�̵��ӵ� ����
	this->HT_vGameSystem_SetCharMoveSpeed( info );
	//	Default ���� �ӵ� ����
	this->HT_vGameSystem_SetCharAttackSpeed( info );
	//	���� Chakra Point, ���� Skill Point��ų �κ��丮�� ����
	g_cSkillInventory->HT_vSkillInventory_SetSkillPoint( info->snSPRemaining, info->snCasteSPRemaining );
	//	�ִ� HP
	g_cMainCharacter->HT_nMainChar_SetMAXHP( info->iMaxHP );
	//	�� HP
	if( info->iHP > g_cMainCharacter->HT_nMainChar_GetResentHP() )
	{
        g_cMainCharacter->HT_nMainChar_SetCurHP( info->iHP );
	}
	//	�� TP
	g_pMainBar->HT_vMainBar_SetCurTP( info->iTP, info->iMaxTP );
	////	MainCharacter�� ���� x, z
	//g_cMainCharacter->HT_vMainChar_SetCellPosition( info->snX, info->snZ );
	//	LevelUP�� �ʿ��� ����
	g_pMainBar->HT_vMainBar_SetNeedPrana( info->iMaxPrana );
	//	���� ����
	g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->iPrana );
	// ���Ǿ�
	g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->iGold );
	//	ĳ���� ���� Ŭ������ ���� ����
	g_cStatus->HT_vStatus_ChangeParams(info);
	// Tantra V3 ���� 
	g_cUIStatus->HT_vStatus_ChangeParams(info);

	if (g_oMainCharacterInfo.byClass1 != info->byClass1)
	{
		g_oMainCharacterInfo.byClass1 = info->byClass1 ;
		g_oMainCharacterInfo.byClass2 = info->byClass2 ;

		g_cUIStatus->HT_vStatus_SetInfo();	// UI ����
		g_cUISkillWindow->HT_vSkillWindow_SetInfo();	// UI ����
	}

	g_oMainCharacterInfo.byClass1 = info->byClass1 ;
	g_oMainCharacterInfo.byClass2 = info->byClass2 ;

	// ��� �����ޱ�	(2005. 1 31 ������)
	g_byteMainCharacterCaste = info->byCaste ;

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_Update_UI CurHP:%d, MaxHP:%d", info->iMaxHP, info->iHP );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� �ּ�ȭ�� ����Ÿ----------//
HTvoid CHTGameSystem::HT_vGameSystem_UpDate_Status( PS_SCP_RESP_UPDATE_STATUS info )
{
	if( info->snKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		CHTString szMessage;
		//HTint iTempValue;
		//	���� ����
		//iTempValue = info->iPrana - g_cMainCharacter->HT_dwMainChar_GetTotalPrana();
		m_iMessageVal = info->iPrana - g_cMainCharacter->HT_dwMainChar_GetTotalPrana();
		if( m_iMessageVal > 0 )
		{
           	//szMessage.HT_szFormat("���� %d��(��) ȹ���߽��ϴ�.", iTempValue );
			HT_vGameSystem_SetMessage( eMsgAttackReceivePrana, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
		}
		g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->iPrana );
		//	�� HP
		//iTempValue = info->iHP - g_cMainCharacter->HT_nMainChar_GetResentHP();
		//m_iMessageVal = info->iHP - g_cMainCharacter->HT_nMainChar_GetResentHP();
		//if( m_iMessageVal > 0 )
		//{
		//         	//szMessage.HT_szFormat("HP %d��(��) ȸ���Ǿ����ϴ�.", iTempValue );
		//	HT_vGameSystem_SetMessage( eMsgCharacterRecoveryHP, &szMessage );
		//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
		//}
		g_cMainCharacter->HT_nMainChar_SetCurHP( info->iHP );
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetMainCharHPCorrect( info->iHP );
		//	�� TP
		g_pMainBar->HT_vMainBar_SetCurTP( info->iTP, 0 );
		//	�� ī����
		g_oMainCharacterInfo.snKarma = info->snKarma;
        
		//	Set �������� �������� ĳ������ ���� ����
		g_cMainCharacter->HT_vMainCHar_SCP_SetAffections( info->iAffections );

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_UpdateUI_Status:HP:%d, Prana:%d, Affections:%x", info->iHP, info->iPrana, info->iAffections );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	OtherObject
	else
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUpdateStatus( info );
	}
}

//----------�������� ��Ŷ �����ޱ�-���� �ʱ�ȭ���� ĳ���� �׾��� ��----------//
HTvoid CHTGameSystem::HT_vGameSystem_NetWorkInitCharDeath()
{
	//----------ĳ���� �״� �׼�----------//
	g_cMainCharacter->HT_nMainChar_SetCurHP( 0 );
	g_cMainCharacter->HT_vMainChar_NetWorkDieMotion();

	//----------�������� ��Ŷ �����ޱ�-��� Ȯ��â �ٿ��----------//
	this->HT_vGameSystem_OpenDeathWindow();

	// �޼���
	CHTString szMessage;
	//	�ֽ����������� ��� �޽���
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		// [���]�ֽ������� ������� ���� �г�Ƽ�� �����ϴ�. �׷��� �ֽ� ����Ʈ�� 0�� ��� 
		// ĳ���� ����� �ش� ���� ������ 5%�� ����մϴ�.
		HT_vGameSystem_SetMessage( eMsgAttackTrimuritiZoneWarning, &szMessage);
		//	����â ��
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( szMessage.HT_szGetString() );
	}
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� ���----------//
HTvoid CHTGameSystem::HT_vGameSystem_NetWorkDeath( HTshort snTribe, CHTString strKillerName )
{
	//----------ĳ���� �״� �׼�----------//
	g_cMainCharacter->HT_nMainChar_SetCurHP( 0 );
	g_cMainCharacter->HT_vMainChar_NetWorkDieMotion();
	g_cMainCharacter->HT_vMainChar_SetInitAffectionsEffect();

	//	���� ���ư��� �ִ� ��Ÿ���� ���� �ʱ�ȭ ���ش�.
	g_cQuickSlot->HT_vTotalCoolTimeInit();

	// ���� �������� �̵����� ��쿡�� ��� ��Ų��.
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive( /*_DIALOG_INVEN*/ );

	//----------�������� ��Ŷ �����ޱ�-��� Ȯ��â �ٿ��----------//
	this->HT_vGameSystem_OpenDeathWindow();

	// �޼���
	CHTString szMessage;
	//	�ֽ����������� ��� �޽���
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		// [���]�ֽ������� ������� ���� �г�Ƽ�� �����ϴ�. �׷��� �ֽ� ����Ʈ�� 0�� ��� 
		// ĳ���� ����� �ش� ���� ������ 5%�� ����մϴ�.
		HT_vGameSystem_SetMessage( eMsgAttackTrimuritiZoneWarning, &szMessage);
		//	����â ��
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( szMessage.HT_szGetString() );
	}

	//	����ĳ���Ͱ� �׾�����
	//	ų�� ������ ����
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

	// [%s�� ���� ����Ͽ����ϴ�.]", m_strKillerName.HT_szGetString() );
	HT_vGameSystem_SetMessage( eMsgCharacterDead, &szMessage);
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
}

//----------�������� ��Ŷ �����ޱ�-��� Ȯ��â �ٿ��----------//
HTvoid CHTGameSystem::HT_vGameSystem_OpenDeathWindow()
{
	m_bReqReenDlgSw = HT_TRUE;

	CHTString strMessage;
	for( HTint i=0 ; i<3 ; i++ )
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, i, _T("") );

	// ���� ��ġ�� ������̶�� ��Ȱ ��ġ�� �� �� �ִ� â�� ���� �׷��� ������ �Ϲ� Ȯ��â�� ����. ������ 2005. 3. 25
	if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
	{
		// ���콺 �������� �޽��� �ؼ� ������ �̵����̿��ٸ� ��ҽ�Ŵ
       	g_cUIManager->HT_CancelSlotBoxImageMoving();
		// ����� ��Ȱâ ���
		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalArena, &strMessage, _T(""), _T("") );	//	�Ʒ��� ���߼����� ��Ȱ(20000 ���Ǿ� �Ҹ�
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalSavedZone, &strMessage, _T(""), _T("") );	//	����� ��ҿ��� ��Ȱ
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, strMessage );
		//	�������� ��������� ���������
		m_iButtonType = 1;
	}
	else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
	{
		// ���콺 �������� �޽��� �ؼ� ������ �̵����̿��ٸ� ��ҽ�Ŵ
       	g_cUIManager->HT_CancelSlotBoxImageMoving();
		// ����� ��Ȱâ ���
		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalFotress, &strMessage, _T(""), _T("") );	//	������ ������� ��Ȱ
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 0, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalNorthViruCastle, &strMessage, _T(""), _T("") );	//	����� ���� ���� ��ó���� ��Ȱ
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 1, strMessage );
		g_cUIManager->HT_SetScriptMessage( eMsgRevivalRevivalSavedZone, &strMessage, _T(""), _T("") );	//	���� �������� ��Ȱ
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_DEATHMSGFOTRESS, 2, strMessage );
		//	�������� ��������� ���������
		m_iButtonType = 1;
	}
	else
	{
		// Ȯ�� ��ư�� ������ ������������ �ٽ� �¾�ϴ�.
		HT_vGameSystem_SetMessage( eMsgCharacterRebirth, &strMessage);

		// ���콺 �������� �޽��� �ؼ� ������ �̵����̿��ٸ� ��ҽ�Ŵ
		g_cUIManager->HT_CancelSlotBoxImageMoving();

		g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSG );
		g_cUIManager->HT_MessageBox( _DIALOG_DEATHMSG, strMessage.HT_szGetString(), 4 );
	}
}

//	OtherObjectSystem���� ������
HTvoid CHTGameSystem::HT_vGameSystem_SetKillerName( CHTString strKillerName )
{
	m_strKillerName = strKillerName;
}

//	�繫�ٹ� ��ų ����ص� �ųİ� �����
HTvoid CHTGameSystem::HT_vGameSystem_ReqAnswerUseSamudaba( int iEchoType, int iKeyID, HTbyte byResponse, HTbyte byData )
{
	//	�� �ڽ��� Ŭ���ϰ� �־ ��ŵ
	if( g_cMainCharacter->HT_iMainChar_GetKeyID() == iKeyID )
		return;
	////	�ٸ� ĳ���� ��� �־ ��ŵ
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
	//	��û���� ��쿡�� ����
	if( byResponse == 0 )
        m_bAnswerSamudabaSw = HT_TRUE;

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQ_CouponEvent Number : %d", info->iEchoID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

	//	Samudaba Delay Time
	if (byResponse == 0)	// ��ų �����ڸ� �������
		m_dwSamudabaDelayTime = timeGetTime();
}

//	�繫�ٹ� ��ų ����ص� �ųİ� ����� ���� �ޱ�
HTvoid CHTGameSystem::HT_vGameSystem_ReciveAnswerUseSamudaba( Msg_Echo* info )
{
	//	�繫�ٹ� ��� ��û �޾�����
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
		// �������� �����ð��� üũ��
		m_dwSamudabaDelayTime = timeGetTime();

		//������ ����â�� �ݾ��ش�.
		if( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSG ) ) 
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

		// ��������� ���ÿ� ����� ��Ȱâ�� �ݾ��־�� �Ѵ�.
		if ( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) )
			g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );

	}
	//	�³� �޾�����
	else if( info->byResponse == 1 )
	{
		//	Answer Samudaba
		if( !m_bAnswerSamudabaSw )
			return;
		m_bAnswerSamudabaSw = FALSE;

		//	�Ÿ� üũ�Ͽ� �ʹ� �ָ� ������ �ְų� ���� �ð��� �ʰ�(10��)������ Skip
		HTvector3 vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( info->iKeyID );
		HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( vecTargetPos, vecMainCharPos );
		if( nRange > 200 )
			return;

		DWORD dwPassTime = timeGetTime();
		if( dwPassTime > m_dwSamudabaDelayTime+10000 )
			return;

		//----------�׼� ��ų ����----------//
		g_cMainCharacter->HT_vMainChar_SetActionSkill( HT_SKILLINDEX_SAMUDABA );
	}

	//a->b ��û�� a: iEchoID=1, iKeyID=��Ȱ��ų���(������ ����)
	//����->b        iKeyID=��Ȱ��Ű�ٴٴ� ����,  byResponse=0
	//b->a �����    iKeyID=��Ȱ��Ű�ٴٴ� ����,  byResponse=1 or 2
	//����->a        iKeyID=��Ȱ��ų���,         byResponse=1 or 2
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� ���� ��û----------//
HTvoid CHTGameSystem::HT_vGameSystem_CSP_INIT_REGEN_CHAR( BYTE byType )
{
	//-----ĳ���� ���� ������ ��û�Ѵ�-----//
	PS_CSP_REQ_INIT_REGEN_CHAR info = HT_NULL;
	info = new S_CSP_REQ_INIT_REGEN_CHAR;
	info->byConnType = 2;//byType;
	g_pNetWorkMgr->RequestReqInitRegenChar( info );
	HT_DELETE( info );

	//----------�������̸� ���----------//
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 26 );
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� ����� �̴� ������û ���----------//
HTvoid CHTGameSystem::HT_vGameSystem_SCP_INIT_REGEN_CHAR( PS_SCP_RESP_INIT_REGEN_CHAR info )
{
    //	���� ó��
	if(	info->byZone <= 0 )
		info->byZone = 1;

	//	Ȥ�� ���� ��ȭ���ڰ� ���ִٸ�
	if( m_bReqReenDlgSw )
		g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSG );

	// ��������� ���ÿ� ����� ��Ȱâ�� �ݾ��־�� �Ѵ�.
	if ( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) )
		g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );

	//	������ ������ġ�� �ٸ� ���϶�
	if( info->byZone != g_wResentZoneServerID )
	{
     	//	���� ������ ���� ����
		g_pNetWorkMgr->DisConnect();

		//char test[100];
		//sprintf(test, " ������ ���� ����ȣ = %d", info->byZone);
		//MessageBox(NULL, test, test, MB_OK);
		g_wResentZoneServerID = info->byZone;

		//	������ No, IP�� Port�� �������� ����
		g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
		g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;

		//	�������� DisConnect Check Seting
		g_bPortalServerDisConnectCheckSw	= HT_FALSE;
		//	�� ���� Ŀ��Ʈ�� ��ٸ����� ����
		g_bZoneServerSwitching = HT_TRUE;
		//	�������� ����
		//	Ȯ�ι�ư�� ������ �̴�Ŀ��Ʈ ��û�ߴ����� �ȴ�.
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

	//	�����ɷ��ִ� ��ų �ʱ�ȭ
	g_pMainBar->HT_vMainBar_MySkillInit();
}

//----------�������� ��Ŷ �����ޱ�-������ ������ �������� ��----------//
HTvoid CHTGameSystem::HT_vGameSystem_ServerDisConnect_SetDlg( CHTString strMsg )
{
	if( m_bServerDisConnectSw )
		return;

	m_dwServerDisConnectTimeOut = GetTickCount();
	m_bServerDisConnectSw = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_DISCONNECTSERVER );
	g_cUIManager->HT_MessageBox( _DIALOG_DISCONNECTSERVER, strMsg.HT_szGetString(), 0 );
}

//----------�������� ��Ŷ �����ޱ�-������ ������ �������� ��----------//
HTRESULT CHTGameSystem::HT_vGameSystem_ServerDisConnect_CheckDlg( HTint iButtonNo )
{
	//----------������ �׾����� Ȯ�� ����ġ----------//
	if( m_bServerDisConnectSw == HT_FALSE )
		return HT_FAIL;
	
	if( iButtonNo == _BTN_MSG_OK )
	{
		// ���� ���� ��ȭâ �ٿ��
		g_byReStartButtonCode = 10;
	}

	return HT_OK;
}
//	�������� ��Ŷ �����ޱ�-Quiz
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
	
	// ������ 3�� �� ��
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
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vGameSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGameSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
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

		// ȸ���� HP
		case eMsgParamRecoveryHp	:
		// ���� ����
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

//	RequestMoveZoneServer�� ������ 5�ʵ��� ������ ���� ���ϸ� �����Ѵ�.
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
		g_pNetWorkMgr->RequestReqMoveZoneServer( info ); //fors_debug �ķ����һ���ĵط�
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MoveZoneServer");
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		HT_DELETE( info );
	}
}

//----------������----------//
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

//	�޸� ���ǵ����� �������� �� �׷���..
HTvoid CHTGameSystem::HT_vGameSystem_SetCharMoveSpeed( PS_SCP_RESP_UPDATE_UI info )
{
	if( info->byteSpeed1 >= 104  && info->byteSpeed1 <= 112	&& 
		info->byteSpeed2 >= 15 && info->byteSpeed2 <= 23 && 
		info->byteSpeed3 >= 74  &&  info->byteSpeed3 <= 82 )
	{
		//	�̵��ӵ�
		g_byteSpeed1 = info->byteSpeed1;
		g_byteSpeed2 = info->byteSpeed2;
		g_byteSpeed3 = info->byteSpeed3;
		g_byteSpeedCorrection = info->byteSpeedCorrection;
		g_byteSpeedParity = info->byteSpeedParity;
	}
	else
	{
		// ���⼭�� ������ �ٽ� ��Ŷ ��û??? �Ǵ� ���� ó��
		//	�̵��ӵ�
		g_byteSpeed1 = 0;
		g_byteSpeed2 = 0;
		g_byteSpeed3 = 0;
		g_byteSpeedCorrection = 0xf;
		g_byteSpeedParity = 0;
	}
}

//	�޸� ���ǵ����� �������� �� �׷���..
HTvoid CHTGameSystem::HT_vGameSystem_SetCharAttackSpeed( PS_SCP_RESP_UPDATE_UI info )
{
	if ( info->byteAS1 >= 26 && info->byteAS1 <= 30 && 
		 info->byteAS2 >= 61 && info->byteAS2 <= 68	&& 
		 info->byteAS3 >= 27 && info->byteAS3 <= 34	&& 
		 info->byteAS4 >= 15 && info->byteAS4 <= 30 )
	{
		//	���ݼӵ� ��Ŷ
		g_byteAS1 = info->byteAS1;
		g_byteAS2 = info->byteAS2;
		g_byteAS3 = info->byteAS3;
		g_byteAS4 = info->byteAS4;
		g_byteParity = info->byteParity;
	}
	else
	{
		//	���ݼӵ� ��Ŷ
		g_byteAS1 = -126;
		g_byteAS2 = 61;
		g_byteAS3 = 27;
		g_byteAS4 = -101;
		g_byteParity = 0;
	}
}

