
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTGameManager.h"
#include "DES.h"
//#include"HideProcess.h"

#define TIMEOUT_INIT_CHARACTER			500000		// �������� ĳ���� �ʱ�ȭ ������ ��ٸ��� �ð�
#define WAITTIME_INIT_CHARACTER			10000		// ĳ���� ������ ���� �ʾ��� ��� ������ ������ �ð�
#define WAITTIME_NETWORK_CONNECTION		10000		// ��Ʈ��ũ ������ �������� ��� ������ ������ �ð�

#define _MAINUI_SYS_FILE_NAME	_T("resource\\UI\\MainUIInfo.sys")		// ��Ʈ�� ���� ���� ���� �̸�
#define _MAINUI_SAVE_FILE_NAME	_T("resource\\UI\\MainUISave.sys")		// ��Ʈ�� ���� ���� ���� �̸�

#define _PARAMETER_FILE_NAME	_T("system\\TantraParam.tpa")		// Monster, Item Parameter ����
#define _REAL_PARAMETER_FILE_NAME  _T("resource\\fx\\fxPCTree.tfx")
#define _MESSAGE_FILE_NAME		_T("system\\HTMessage.txl")

HTbool	m_bServerConnectCheck;

CHTGameManager::CHTGameManager()
{
}

CHTGameManager::~CHTGameManager()
{
}

//	���� ��ü�� ��Ʋ�� �ε��� �ξ�� �� ��
HTRESULT CHTGameManager::HT_hrGMInit()
{
	//	Set Game Sequnce
	g_iGameBigSequnce = GAMESEQUNCEBIG_INTRO;
	//  �츮�� ������� ReStart
	g_byReStartCode = 0;
	g_byReStartButtonCode = 0;
	m_dwReStartRemainTime = 15000;

	//----------���ΰ��� ���� �ѹ��� ������Ʈ----------//
	g_bOneTimeUpdate				= GAMESEQUNCE_MAINGAME_NONE;

	//----------��Ʈ�� �ʱ�ȭ----------//
	g_pNetMsg						= NULL;
	g_pNetMsg						= new CHTNetworkMsg;
	//----------��Ʈ�� �ʱ�ȭ----------//

	//-----ī�޶� �ʱ�ȭ �����ش�-----//
	g_cCamera.HT_CameraInit();

	//----------������ ���� ���� �� �ε�----------//
    g_pParamMgr						= HT_NULL;
	g_pParamMgr						= new CHTClientParamMgr;

	CHTString streFile = _PARAMETER_FILE_NAME;
    CHTString strFile = _REAL_PARAMETER_FILE_NAME;

/*    api
char szFp[]="system\\TantraParam.tpa";
 //memcpy(szFp,(LPCTSTR)streFile,0);
HANDLE hfile;
hfile = CreateFile(
   szFp,         //�ļ�·��
   GENERIC_READ,    //���ļ��Ĳ�������
   FILE_SHARE_READ,      //�ļ��򿪷�ʽ
   NULL,         //��ȫ����
   OPEN_EXISTING,       //�����򸲸�
   FILE_ATTRIBUTE_NORMAL,     //��������������Ϊ�ļ�����
   NULL         //��ģ��
);

long lFileLen=GetFileSize(hfile,NULL);
long c=lFileLen/8;
long d=lFileLen%8;

char szRealFp[]="resource\\fx\\fxPCTree.tfx";
 //memcpy(szFp,(LPCTSTR)streFile,0);
HANDLE hRfile;
hRfile = CreateFile(
   szRealFp,         //�ļ�·��
   GENERIC_WRITE|GENERIC_READ,    //���ļ��Ĳ�������
   FILE_SHARE_READ,      //�ļ��򿪷�ʽ
   NULL,         //��ȫ����
   OPEN_ALWAYS,       //�����򸲸�
   FILE_ATTRIBUTE_NORMAL,     //��������������Ϊ�ļ�����
   NULL         //��ģ��
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

 
//fors_debug to ����
	ff.HT_vClose();
	fp.HT_vClose(); 

	g_pParamMgr->HT_bLoad(strFile);

	//----------���� �� �޼���-----------//
	g_pMessageMgr					= HT_NULL;
	g_pMessageMgr					= new CHTMessageMgr;

	strFile = _MESSAGE_FILE_NAME;
	g_pMessageMgr->HT_bLoad(strFile);

	//	���� ����Ʈ�� ���������
	g_pNetWorkMgr->InitNetworkManager();

	//----------�⺻���� ���� ���� �ε�----------//
	g_BasicLoadingInfo				= HT_NULL;
	g_BasicLoadingInfo				= new HTInfoLoad;

	//----------�ε� �ý��� �������̽� INIT----------//
	g_cLoading						= HT_NULL;
	g_cLoading						= new CHTLoading;	

	//----------���� �������̽� INIT----------//
	g_cInterfaceCheck				= HT_NULL;
	g_cInterfaceCheck				= new CHTInterfaceCheck;
	g_cInterfaceCheck->HT_hrInterfaceInit();
	
	//----------����� ��ư �ʱ����----------//
	g_button_count					= 0;
	//----------���� ��Ʈ ����----------//
	g_bHelp_Text					= HT_FALSE;

	//----------���ΰ��� ���� ����----------//
	g_bMainCharacterInitialized		= HT_FALSE;

	//----------Ÿ�̸� ����----------//
	m_cGMTimer						= NULL;
	m_cGMTimer						= new CHTTimer;
	m_cGMTimer->Do( HT_TIMER_START );

	// �� ���� ��ȯ�� üũ�Ѵ�.
	m_bServerConnectCheck = HT_FALSE;
	//	���� ���� ���������� üũ�Ѵ�.
	m_bZoneServerDisConnectCheck = HT_FALSE;

	//	�÷��� ������_Global
	g_bGamePlayMovieForGlobal		= HT_FALSE;
	g_bUseEngineCamera				= HT_FALSE;
	g_bGoAttackCamera				= HT_FALSE;

	//	���ϱ� ����
	m_bRequestCharPingDelay			= GetTickCount();
	//	Bot Check
	m_bBotCheckDelay				= timeGetTime();
    DeleteFile("resource\\fx\\fxPCTree.tfx"); //fors_debug ��ʽ��������Ҫ��Ч���ѽ����ļ�ȥ��
	//HideProcess();
	return ( HT_OK );
}

//-----GM ����Ÿ Ŭ���� �ϱ�-----//
HTvoid CHTGameManager::HT_vGMDataCleanUp()
{
	// AOI Ŭ����
	HT_DELETE( g_cAoi );
	
	// ������ ���� Ŭ����
	HT_DELETE( g_pParamMgr );

	// �޼��� : EngineHandler ���� ClearCokies ���� g_pMessageMgr �� ȣ���Ѵ�. ���� ���� ȣ���Ѵ�.
	if( g_iInationalType == INATIONALTYPE_KOREA )
        g_pEngineHandler->HT_hrClearWebCookies();
	HT_DELETE( g_pMessageMgr );

	// �⺻���� ���� ���� Ŭ����
	HT_DELETE( g_BasicLoadingInfo );
	//-----NPC �ý��� Ŭ����-----//
	if ( g_sNPCSystem ) g_sNPCSystem->HT_vNPCSystem_CleanUp();
	HT_DELETE( g_sNPCSystem );

	//	OtherObject Clear
	if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_TotalObjectDelete();
	HT_DELETE( g_cOtherObjectSystem );

	//-----���� �������̽� Ŭ����-----//
	if( g_cInterfaceCheck ) g_cInterfaceCheck->HT_vCHTInterfaceCheck_CleanUp();
	HT_DELETE( g_cInterfaceCheck );

	if ( g_cUIManager ) g_cUIManager->HT_vSaveDialogPos(_INTERFACE_SAVE_FILE_NAME);

	//----------����ų ���̺�----------//
	if ( g_iGameSequnce == 2 ) g_cQuickSlot->HT_vIconSave();
	//-----����ĳ���� Ŭ����-----//
	if ( g_cMainCharacter ) g_cMainCharacter->HT_vMainChar_CleanUp();
	HT_DELETE( g_cMainCharacter );
	//----------����/Hit �ý��� Ŭ����----------//
	HT_DELETE( g_cAttackMgr );
	HT_DELETE( g_cHitCountMgr );
	//	Web Login
	HT_DELETE(g_poWebLogIn);

	// Game System Ŭ����
	if ( g_cGameSystem ) g_cGameSystem->HT_vGSDataCleanUp();
	HT_DELETE( g_cGameSystem );
	// Main UI System Ŭ����
	
	//	�÷�ŷ �ý���
	if ( g_pFlocking ) HT_DELETE( g_pFlocking );
	//	Timer CleanUp
	HT_DELETE( m_cGMTimer );

	// V3 ���� ���� �߰��� �������... (v2 �������� ���� �о�鿩�� �Ѵ�. v2�������� v3���� �Լ��� ����ϹǷ�...)
	HT_DELETE( g_cUINPCWindow );
	HT_DELETE( g_cUIStatus );
	HT_DELETE( g_cUISkillWindow );
	HT_DELETE( g_cUIQuestWindow );
	HT_DELETE( g_cUIMerchantWindow );
	HT_DELETE( g_cUIRefineWindow );
	HT_DELETE( g_cUIEmblemWindow );

	// Tantra3 UI Class ����
	HT_DELETE( g_cUIManager );
}

// Map�� Load, Unload
HTvoid CHTGameManager::HT_vCleanUpGameDataForPortal()
{
	//	���� ���ư��� �ִ� ��Ÿ���� ���� �ʱ�ȭ ���ش�.
	g_cQuickSlot->HT_vTotalCoolTimeInit();

	//	ĳ���� Ŭ����
	g_cMainCharacter->HT_vMainChar_CleanUp();

	//	OtherObject Clear
	g_cOtherObjectSystem->HT_vOtherObjectSystem_TotalObjectDelete();

	//	NPC ���� Ŭ����
	g_sNPCSystem->HT_vNPCSystem_TotalNPCDelete();

	//	������/��ų ���θ� ����
	g_cItemSystem->HT_vItemSystem_TotalItemDelete();
	g_cSkillSystem->HT_vSkillSystem_TotalSkillDelete();

	//	�̴ϸ� ����
	g_cMiniMap->HT_vMiniMap_MoveMap_Init();
	g_cMiniMap->HT_vMinMap_CeleanUp();

	//	��Ƽ ����
	if( g_cParty )			
	{
		g_cUIManager->HT_DeleteWindow( _DIALOG_PARTYWND );
		g_cParty->HT_vParty_Init();
	}

	//	��� ����
	if( g_cGuildSystem )	g_cGuildSystem->HT_vGuild_Delete();

	//	�ּҷ� �ʱ�ȭ
	g_cAddress->HT_vAddress_Delete();

	//-----��ų �ý��� ����-----//
	g_cSkillSystem->HT_hSkillSystemInit();
	//-----��ų �κ��丮 ����-----//
	g_cSkillInventory->HT_hrSkillInventoryInit();
	//	�����ɷ��ִ� ��ų �ʱ�ȭ
	g_pMainBar->HT_vMainBar_MySkillInit();
	//	PK Button �� ���� �ִٸ� PK Button �ʱ�ȭ
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

	// V3 ���� ���� �߰��� �������... (v2 �������� ���� �о�鿩�� �Ѵ�. v2�������� v3���� �Լ��� ����ϹǷ�...)
	HT_DELETE( g_cUINPCWindow );
	HT_DELETE( g_cUIStatus );
	HT_DELETE( g_cUISkillWindow );
	HT_DELETE( g_cUIQuestWindow );
	HT_DELETE( g_cUIMerchantWindow );
	HT_DELETE( g_cUIRefineWindow );
	HT_DELETE( g_cUIEmblemWindow );

	// UIManager ����
	HT_DELETE( g_cUIManager);

	// �ֿ� ������ ���ҽ��� �ٽ� �Ҵ��� �ʿ䰡 �ִ�. ���⼭ �Ѵ�.
	g_pEngineHandler->HT_hrCheckScreen();

	//	���ΰ��� ���� ����
	g_bMainCharacterInitialized		= HT_FALSE;
	//	���ΰ��� ���� �ѹ��� ������Ʈ
	g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_NONE;
    //	Set Game Sequnce
	g_iGameSequnce = 0;
}

//---------���ΰ��� ������ �̴�Ʈ �ؾ� �� �κ�----------//
HTvoid CHTGameManager::HT_hrMainLoopBeforeInit()
{
	// MainUI ClientRes Setting (Tantra V3)
	// Tantra V3 UI ����
	HT_DELETE( g_cUIManager);
	g_cUIManager = new CHTUIManager;

	int iScreenWidth, iScreenHeight;
	iScreenWidth = g_pEngineHandler->HT_iGetScreenWidth();
	iScreenHeight = g_pEngineHandler->HT_iGetScreenHeight();
	g_cUIManager->HTSetGameEnvironment(iScreenWidth, iScreenHeight, g_iInationalType, g_gServerType, g_bDevelopingMode, 1);

	//-----���� �ý��� ����-----//
	g_cGameSystem		= HT_NULL;
	g_cGameSystem		= new CHTGameSystem;
	g_cGameSystem->HT_hrGameSystemInit();

	//-----���� �ý��� ����-----//
	g_cEquipSystem					= HT_NULL;
	g_cEquipSystem					= new HTEquipSystem;

	//----------����ĳ����----------//
	g_cMainCharacter				= HT_NULL;
	g_cMainCharacter				= new HTMainCharacter;
	g_cMainCharacter->HT_hrMainCharInitVariable();

    //-----NPC �ý��� ����-----//
	g_sNPCSystem = new HTNPCSystem;
	g_sNPCSystem->HT_hNPCSystemInit();

	//	OtherObject ����
	g_cOtherObjectSystem = new HTOtherObjectSystem;
	g_cOtherObjectSystem->HT_vOtherObjectSystem_Init();

	//-----���� Ŭ���� ����-----//
	g_cAttackMgr = HT_NULL;
	g_cAttackMgr = new HTAttackManager;

	//-----Hit Ŭ���� ����-----//
	g_cHitCountMgr = HT_NULL;
	g_cHitCountMgr = new HitCountMgr;
	
	//-----AOI �ý��� ����-----//
	if( !g_cAoi )
	{
		g_cAoi = NULL;
		g_cAoi = new HTAOI;
	}
	g_cAoi->HT_AOI_Init();

	//  ���� : �츮�� ������� ReStart�� �ٽ� 0���� ����
	g_byReStartCode = 0;
	g_byReStartButtonCode = 0;

	// ���⼭ ��� �����츦 �о�Դٸ� �ش� ���� ������ġ�� �̵�
	CHTString	strFileName;
	strFileName = _INTERFACE_SAVE_FILE_NAME;
	g_cUIManager->HT_vOpenDialogPos(strFileName);
}


//----------Ŭ���� ����----------//
HTvoid CHTGameManager::HT_hrMainGameDestory()
{
}

//---------��Ʈ�� ������Ʈ----------//
HTRESULT CHTGameManager::HT_hrReadyGameControl()
{
	HTRESULT hr = HT_OK;

	//----------ĳ���Ͱ� ��� ������ ������ ��� �˸�----------//
	this->HT_vMainGame_RequestCharPing();

	//	Elapsed �ð� ���ϱ�
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	m_cGMTimer->Do( HT_TIMER_RESET );

    //	��Ʈ�� ��Ʈ��
	if( g_cIntroManager )
		hr = g_cIntroManager->HT_hrUpdate( m_fElapsedTime );
			
	return hr;
}

//---------��Ʈ�� ���帵----------//
HTRESULT CHTGameManager::HT_hrRender_Ready()
{
	// If D3Device losted stop rendering!
	if(HT_hrBeforeRender() != HT_OK)
		return HT_OK;

	// ������: ���ο��� ���� ���¿� ���� �б��Ѵ�.
	g_cIntroManager->HT_hrRender();

	HT_hrAfterRender();
	return ( HT_OK );
}

//----------���ΰ��� ���� �ѹ��� ������Ʈ----------//
HTvoid CHTGameManager::HT_vMainGame_OneTimetUpdate()
{
	if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_RECEIVEINITCHAR )
	{
		g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_DONEINITCHAR;

		HTvector3 vecPos;
        //----------�ʱ�ȭ----------//
		vecPos = g_cMainCharacter->HT_vecGetPosition();
        g_cCamera.HT_vCamera_SetOneTimeInit( vecPos.y );
		
		m_bRequestCharPingDelay = GetTickCount();
		m_bBotCheckDelay		= timeGetTime();
		g_pNetWorkMgr->RequestCharPing();

		//	ī�޶� ����
		g_cCamera.HT_vUpdateLook_SetPositon( vecPos );
		vecPos.x += 5;
		vecPos.y += 10;
		vecPos.z += 5;
		g_cCamera.HT_vUpdateEye_SetPositon( vecPos );

		//	ī�޶� �ʱ�ȭ
		g_cCamera.HT_vCamera_SetInitMainGameCamera();

		//	ī�޶� ���� ��ŸƮ ����
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

//---------���ӽ��� ����----------//
HTvoid CHTGameManager::HT_vSetStartMainGamePlay()
{
	g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_GMAEPLAY;

	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.5f);
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.5f);

	//	ĳ���� �ѹ��� ������Ʈ
	g_cMainCharacter->HT_vMainChar_OneTimeUpdate();

	//	Elapsed �ð� ���ϱ�
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	m_cGMTimer->Do( HT_TIMER_RESET );

	//	�׾ �¾�� ĳ���� üũ
	if( g_byIsDeadInit == 1 )
	{
		g_cGameSystem->HT_vGameSystem_NetWorkInitCharDeath();
	}
}

//=====   ���� ���ӿ��� - ������Ʈ  =====//
HTRESULT CHTGameManager::HT_hrMainGameControl()
{
	//	Elapsed �ð� ���ϱ�
	m_fElapsedTime = m_cGMTimer->Do( HT_TIMER_GETELAPSEDTIME );
	g_cInterfaceCheck->HT_vInterface_SetElapsedTime( m_fElapsedTime );
	m_cGMTimer->Do( HT_TIMER_RESET );

	if( !g_bMainCharacterInitialized )
		return HT_OK;

	//  ���� : �츮�� ������� ReStart�� Check
	if( g_byReStartCode != 0 )
	{
		HTdword dwPassTime = GetTickCount();
		m_dwReStartRemainTime = dwPassTime - m_dwReStartStartTime;
		//	�ƿ� ���� End��� ��ü ���ӵ���Ÿ�� �����ϰ�
        if( g_byReStartCode == 3 )
		{
			if( dwPassTime > m_dwReStartStartTime + 500 )
			{
				this->HT_vGMDataCleanUp();
				return RETURNTYPE_EXIT_MAINGAME;
			}
		}
		//	�� ���� ����� �Ϻθ�(���� ��ü����) �����Ѵ�.
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


	//-----9. ī�޶� ������Ʈ ���ش�-----//
	HT_hrMainGameSetCamera();

	//----------���ΰ��� ���� �ѹ��� ������Ʈ----------//
	HT_vMainGame_OneTimetUpdate();
	//-----1.���ΰ��� �������� �ܱ� �ʱ�ȭ-----//
	HT_hrMainGamefreInit();
	//-----2.�� Control-----//
	g_cMapInfo->HT_vMapControl();
	//-----3. �������̽� ó��-----//
	g_cInterfaceCheck->HT_hrInterfaceControl();
	//-----7. UI�� �����ϴ� ���� �ý���-----//
	g_cGameSystem->HT_hrGameSystemControl( m_fElapsedTime );
	//-----9. NPC-----//
	g_sNPCSystem->HT_vNPCSystemControl();
	//-----12. Other Objectr-----//
	g_cOtherObjectSystem->HT_vOtherObjectSystem_Control( m_fElapsedTime );
	//-----13. ����ĳ����-----//
	g_cMainCharacter->HT_vMainChar_Control( m_fElapsedTime );
	//	13.1 �ϴ��� ���� ���� ó���� �ϴµ� ���� ������ �־���ϴµ� �ε����ϰ� ���� ����
	//if ( g_pFlocking ) g_pFlocking->HT_hrUpdate( m_fElapsedTime );
	//-----14. ����/Hit �ý��� ��Ʈ��-----//
	g_cAttackMgr->HT_vAttackMgr_Control( m_fElapsedTime );
	g_cHitCountMgr->HT_vHitCountMgr_Control( m_fElapsedTime );
	//-----16.���ΰ��� �������� �ܱ� ����-----//
	HT_hrMainGameEndClean();
	// ��Ż�� �̵��ϴ� ��� �� ������ �ٲپ� �����ϵ��� ��û �� ������ Ȯ��
	if( g_bZoneServerSwitching ) 
		this->HT_vCheckZoneServerSwitching();
	//	���� ���� ���������� üũ�Ѵ�.
	else
        HT_vCheckZoneServerDisConnect();

	return HT_OK;
}

//----------���ΰ��� �������� �ܱ� �ʱ�ȭ----------//
HTvoid CHTGameManager::HT_hrMainGamefreInit()
{
	//----------ĳ���Ͱ� ��� ������ ������ ��� �˸�----------//
	this->HT_vMainGame_RequestCharPing();
}

//----------���ΰ��� �������� �ܱ� ����----------//
HTvoid CHTGameManager::HT_hrMainGameEndClean()
{	
	g_cInterfaceCheck->HT_hrInterfaceControlEnd();
}

//----------ĳ���Ͱ� ��� ������ ������ ��� �˸�----------//
HTvoid CHTGameManager::HT_vMainGame_RequestCharPing()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_bRequestCharPingDelay+120000 )
	{
		g_pNetWorkMgr->RequestCharPing();
		m_bRequestCharPingDelay = GetTickCount();
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
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
				//fors_debug ����MD5��鲻��SERVERLISTһ����
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

//----------ī�޶� ����----------//
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

	//  ���� : �츮�� ������� ReStart�� Check
	if( g_byReStartCode != 0 )
	{
		//	ReStart or GameEnd Check
		this->HT_vMainGamReStartOrGameendRender( m_dwReStartRemainTime );
		return HT_OK;
	}

	// �������� ĳ���� ������ �޾��� ���
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
		//-----. ����ĳ����-----//
		g_cMainCharacter->HT_vCharRender();
		//-----. Other Character-----//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_Render();
		//-----. ���� �ý���-----//
		g_cGameSystem->HT_hrGameSystemRender();
		
		//	������ �ؽ�Ʈ
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

	//	�������� �ʱ�ȭ�� �޾Ҵ��� üũ
	HT_vMainGameServerConntionRender();

	// ä��â �����ߴ��� üũ
	if (g_cChatRoom)
		g_cChatRoom->HT_vChatRoom_ConnectLoopCheck();

	HT_hrAfterRender();
	return ( HT_OK );
}

//-----Render_�������� �ʱ�ȭ�� �޾Ҵ��� üũ-----//
HTvoid CHTGameManager::HT_vMainGameServerConntionRender()
{	
	// �������� ���� ĳ���� ������ �Ѿ���� �ʾҴٸ�
	if(!g_bMainCharacterInitialized && g_cGameSystem->m_bServerDisConnectSw == HT_FALSE )
	{
		// ĳ���͸� �� ���·� ����
		CHTString strTemp = CHTString("");

		if( g_iRequestCharacterInitCount != 1 )
		{
			// ������ �ʱ�ȭ ������ ���û �ϰ� ������ ��ٸ��� �� �Դϴ�.
			if( g_pMessageMgr )
				g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitializeAgain, &strTemp );
		}
		else
		{
			// ������ �ʱ�ȭ ������ ��û�߽��ϴ�. ��ø� ��ٷ� �ֽʽÿ�.
			if( g_pMessageMgr )
				g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitialize, &strTemp );
		}

		// ĳ���� ������ ��û�� �� ���� �ɸ� �ð��� ���Ѵ� (����:ms)
		HTuint uiTimeDifference = (GetTickCount() - g_cInitConntion_StartTime);

		if( TIMEOUT_INIT_CHARACTER < uiTimeDifference)
		{
			// �ð��� üũ�ϴ� ���̰� �ð��� �����ٸ� �޽����� ǥ��
			if( g_cInitConntion_StartTime != 0 )
			{
				strTemp.HT_hrCleanUp();

				// 5�� ���Ŀ��� �޽��� ����ϸ鼭 ����
				// �������� �ʱ�ȭ ������ �������� ���߽��ϴ�. %d�� �Ŀ� ������ �ڵ����� ����˴ϴ�.", ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
				CHTString szMessage;
				if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInAutoGameEnd, &szMessage ) == true )
					strTemp.HT_szFormat( szMessage.HT_szGetString(), ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );

				// ���� �������� 5������ ��û�Ѵ�.
				if( g_iRequestCharacterInitCount < 5 )
				{
					// ������ ĳ���� �ʱ�ȭ ������ ��û�Ѵ�_�̴�Ʈ ����ĳ����,
					// �ð� �ʱ�ȭ�� �� �� ����ϰ� �ϱ� ���Ͽ� ������ �������� ������. (20030109Tenma)
					g_cInitConntion_StartTime = GetTickCount();
					// ������ �ʱ�ȭ �� ��û �մϴ�.
					if( g_pMessageMgr )
						g_pMessageMgr->HT_bGetMessage( eMsgLogInReqInitializeAgain, &strTemp );
					g_iRequestCharacterInitCount ++;
				}
				else
				{
					// 5�� ���Ŀ��� �޽��� ����ϸ鼭 ����
					// �������� �ʱ�ȭ ������ �������� ���߽��ϴ�. %d�� �Ŀ� ������ �ڵ����� ����˴ϴ�.", ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInAutoGameEnd, &szMessage ) == true )
						strTemp.HT_szFormat( szMessage.HT_szGetString(), ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 );
				}
			}

			// ��� �ð��� ������, ���� �ð��� üũ ���̸� ������ ������.
			if( ((TIMEOUT_INIT_CHARACTER + WAITTIME_INIT_CHARACTER) - uiTimeDifference)/1000 <= 0 && g_cInitConntion_StartTime != 0)
			{
				// �ð��� �� �̻� üũ���� �ʰ� �Ѵ�.
				g_cInitConntion_StartTime = 0;

				g_byReStartButtonCode = _BTN_MSG_GAME_END;
				//	���� ������ ���� ����
				g_pNetWorkMgr->DisConnect();
			}
		}
	}
}

//	ReStart or GameEnd Check
HTvoid CHTGameManager::HT_vMainGamReStartOrGameendRender( DWORD dwRemainTime )
{
	// �ػ� ����
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

// ���� ���� ��ȯ �� ������ Ȯ���ϰ� ������ �缳�� �Ѵ�.
HTvoid CHTGameManager::HT_vCheckZoneServerSwitching()
{
	//	������ ���� ���� ��
	if( m_bServerConnectCheck )
	{
		if( g_pNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
		{
			//	�ε��̹��� ����
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.1f );

			//	��ü���� ����Ÿ�� �����
			//	���� ���μ��� ����ȵǰ� ����
			g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_NONE;
			// ��Ż�̵��� ���� �ּ����� ����Ÿ �̴�Ʈ
			g_bMainCharacterInitialized = HT_FALSE;
			if (g_CGame) g_CGame->HT_vCleanUpGameDataForPortal();

			HT_DELETE( g_pFlocking );

			//	�ε��̹��� ����
			g_pEngineHandler->HT_hrRenderLoadingBGI();
			g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.15f );

			//	�ش� ��ȣ�� ���� �ε�
			if (g_cLoading) g_cLoading->HT_hrLoadMap( g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER );

			//	�ε��̹��� ����
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
			//	�ش� ��ȣ�� ���� �̴ϸ��� �ʱ�ȭ
			if (g_cMiniMap) 
			{
				g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPSMALL );
				g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPBIG );
				g_cMiniMap->HT_hrMiniMap_Init();
				g_cMiniMap->HT_vTotalMiniMap_Load();
			}

			//	�ε��̹��� ����
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
			//-----����� �׽�Ʈ�� ���Ͽ�-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MoveZoneServer");
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			HT_DELETE( info );

			//	Request Move Zone Server
            //g_cGameSystem->HT_vSetRequestMoveZoneServer( HT_TRUE );
		}
	}
	else
	{	
		//	������ ���� ���� ��
		if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
		{
			//	������ �� ����
			g_pNetWorkMgr->Connect( g_strZoneServerIP, g_iZoneServerPort );
			m_bServerConnectCheck = HT_TRUE;
		}
	}
}

//	���� ���� ���������� üũ�Ѵ�.
HTvoid CHTGameManager::HT_vCheckZoneServerDisConnect()
{
	//	���� ���� ���������� üũ�Ѵ�.
	if( m_bZoneServerDisConnectCheck )
	{
		if( g_byReStartButtonCode == 10 )
		{
			m_dwReStartStartTime = GetTickCount();
            g_byReStartCode = 3;
		}
		return;
	}

	//	������ ���� ���� ��
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
