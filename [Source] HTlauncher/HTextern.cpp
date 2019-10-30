#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"

//-----------------------------------------------------------------------------//
//  ���� : ����� �޽��� ���
//  �ۼ����� / �ۼ��� : 2003.03.03 ���� 20030303Tenma
//-----------------------------------------------------------------------------//
FILE* g_pDebugFile = NULL;

HTvoid	HT_g_vOpenDebugFile()
{
#ifdef HT_DEBUG_LOGFILE
	//if( g_iInationalType != INATIONALTYPE_KOREA )
		g_pDebugFile = fopen( "Tantra_Crash.txt", "w" );
#endif

	////	�ӵ��׽þƸ� ���Ͽ�...
	////	NewKruma�� �ٲپ� �ش�.
	//if( g_iInationalType == INATIONALTYPE_INDONESIA )
	//{
	//	WIN32_FIND_DATA FindFileData;
	//	HANDLE hFind;

	//	hFind = FindFirstFile( _T(".\\resource\\map\\NewKruma"), &FindFileData);
	//	//	������ �O������
	//	if (hFind != INVALID_HANDLE_VALUE)
	//	{
	//		FindClose(hFind);
	//		//	������ ������ ���� �����
	//		//	������ �κ�
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tcc", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tcc" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\MAP_Jina4th.thm", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\MAP_Jina4th.thm" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tme", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tme" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tml", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\MAP_Jina4th.tml" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\Sky.tmd", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\Sky.tmd" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\SkyTerrain.tmd", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\SkyTerrain.tmd" );
	//		SetFileAttributes( ".\\resource\\map\\Jina4th\\TerrainTex.hpk", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\Jina4th\\TerrainTex.hpk" );
	//		//	������ ���Ǳ� �κ�
	//		SetFileAttributes( ".\\resource\\map\\MAP_Jina4th.cfg", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\MAP_Jina4th.cfg" );
	//		//	������Ʈ �κ�
	//		SetFileAttributes( ".\\resource\\object\\Jina4thObjTex.hpk", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\object\\Jina4thObjTex.hpk" );
	//		SetFileAttributes( ".\\resource\\object\\Jina4thObjTmb.hpk", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\object\\Jina4thObjTmb.hpk" );

	//		//	�׸��� ���ο� ������ ���� �����Ѵ�.
	//		//	������ �κ�
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tcc", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tcc" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.thm", ".\\resource\\map\\Jina4th\\MAP_Jina4th.thm" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tme", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tme" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tml", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tml" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\Sky.tmd", ".\\resource\\map\\Jina4th\\Sky.tmd" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\SkyTerrain.tmd", ".\\resource\\map\\Jina4th\\SkyTerrain.tmd" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\TerrainTex.hpk", ".\\resource\\map\\Jina4th\\TerrainTex.hpk" );//, FALSE );
	//		//	������ ���Ǳ� �κ�
	//		CopyFile( ".\\resource\\map\\MAP_NewKruma.cfg", ".\\resource\\map\\MAP_Jina4th.cfg", FALSE );
	//		//	������Ʈ �κ�
	//		CopyFile( ".\\resource\\object\\NewKrumaObjTex.hpk", ".\\resource\\object\\Jina4thObjTex.hpk", FALSE );
	//		CopyFile( ".\\resource\\object\\NewKrumaObjTmb.hpk", ".\\resource\\object\\Jina4thObjTmb.hpk", FALSE );

	//		//	���� �����Ͽ��ٸ� ������ NewKruma������ ���� ������.
	//		if( !RemoveDirectory( ".\\resource\\map\\NewKruma" ) )
	//			return;
	//	}
	//}
}

HTvoid	HT_g_vCloseDebugFile()
{
#ifdef HT_DEBUG_LOGFILE
	if( g_pDebugFile )
        fclose( g_pDebugFile );
#endif
}

HTvoid	HT_g_vLogFile( CHTString strTemp )
{
#ifdef HT_DEBUG_LOGFILE
	//if( g_iInationalType != INATIONALTYPE_KOREA  )
	{
		if( g_pDebugFile )
		{
			fprintf( g_pDebugFile, strTemp.HT_szGetString() );
			flushall();
		}
	}
#endif
}

//-----------------------------------------------------------------------------//
//  ���� : ���� ����
//  �ۼ����� / �ۼ��� : 2003.03.03 ���� 20030303Tenma
//-----------------------------------------------------------------------------//
CHTWindowManager*				g_CGame = HT_NULL;

HT_INTERFACE_FLAG				g_iInterface;

//TNCLIENT_COMMAND				g_Player_Command;
HTfloat							g_imsi_button[7];
int								g_button_count;
HTbool							g_bHelp_Text;
CHTString						g_DebugingFont[10];
HTint							g_DebugingFont_Count;

CHTCamera						g_cCamera;
CHTNetworkMsg*					g_pNetMsg;

//���� ������ ����� ���¸� ������ ����.
HTbool							g_bMainCharacterInitialized = HT_FALSE;
BYTE							g_bOneTimeUpdate;
HTint							g_iGameSequnce;
HTint							g_iGameBigSequnce;

//-----�⺻���� ����-----//
HTInfoLoad*						g_BasicLoadingInfo;

//-----------------------------------------------------------------------------//
//  ���� : ���� ĳ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTMainCharacter*				g_cMainCharacter = NULL;
HTAOI*							g_cAoi = NULL;
S_CHARACTER_LIST				g_oMainCharacterInfo;
BYTE							g_byteMainCharacterCaste;		// ����ü�� �߰��� ������, ������ ���� ������ (���)

//	�̵��ӵ�
signed char					g_byteSpeed1, g_byteSpeed2, g_byteSpeed3;
signed char					g_byteSpeedCorrection;
signed char					g_byteSpeedParity;

//	���ݼӵ� ��Ŷ
signed char					g_byteAS1, g_byteAS2, g_byteAS3, g_byteAS4;
signed char					g_byteParity;

// ������ ����Ǵ� ���� �ڵ�
BYTE g_byCharacterServerTribe[8] = {	1,	// ����
										4,	// �Ƽ���
										16,	// ���
										64,	// ����
										2,	// Ų����
										8, // ��ũ����
										32,	// ���ٸ���
										128,// �����
									};

//-----------------------------------------------------------------------------//
//  ���� : OtherObject ����
//  �ۼ����� / �ۼ��� : 20040106 / ���Ǳ�
//-----------------------------------------------------------------------------//
HTOtherObjectSystem*			g_cOtherObjectSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��Ʈ��
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTIntroManager*				g_cIntroManager = NULL;

//-----------------------------------------------------------------------------//
//  ���� : �����Ϳ��� ���� ����Ÿ(��ų, ������, ����, NPC, NPC ��) �ε�
//  �ۼ����� / �ۼ��� : �輱��
//-----------------------------------------------------------------------------//
CHTClientParamMgr*				g_pParamMgr = NULL;

//-----------------------------------------------------------------------------//
//  ���� : �����Ϳ��� ���� ����Ÿ(��ų, ������, ����, NPC, NPC ��) �ε�
//  �ۼ����� / �ۼ��� : �輱��
//-----------------------------------------------------------------------------//
CHTMessageMgr*					g_pMessageMgr = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� / NPC
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTNPCSystem*					g_sNPCSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��ų
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTSkillSystem*					g_cSkillSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ������ �ý���
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTItemSystem*					g_cItemSystem = NULL;
HTItemControl*					g_cItemControl = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� �ý���
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTGameSystem*					g_cGameSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : 2D ��������Ʈ �޴���
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHT2DObjectMgr*					g_2DObjectMgr = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��Ʈ��ũ �޴���
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
TNNetworkManager*				g_pNetWorkMgr;
CPSock							g_cCPSock;

TNChatNetworkManager*			g_pChatNetWorkMgr;
CPSock							g_cChatCPSock;	// ��ȸ �߰� (2005.12.19)

//-----------------------------------------------------------------------------//
//  ���� : ä�ÿ� �����Ͽ�
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTChatting*					g_cChatting = NULL;					// ��ȣ ���� (2002.09.16)

//-----------------------------------------------------------------------------//
//  ���� : �ʱ�ȭ ������ �����޾Ҵ��� üũ
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
DWORD							g_cInitConntion_StartTime;

//-----------------------------------------------------------------------------//
//  ���� : ĳ���� ���� �ý���
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTEquipSystem*					g_cEquipSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� �ý��� �κ��丮 ���� �κ�_��ų, �����κ��丮, ��Ʈ�κ��丮
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTSkillInventory*				g_cSkillInventory = NULL;
CHTEquipInventory*				g_cEquipInventory = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ĳ���� �������ͽ� ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTStatus*						g_cStatus = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ĳ���� UI ������ ���� (īŸ��2 Ȯ�����)
//  �ۼ����� / �ۼ��� : ������
//-----------------------------------------------------------------------------//
CHTUIStatus						*g_cUIStatus = NULL;				// ����â
CHTUINPCWindow					*g_cUINPCWindow = NULL;				// NPC ��ȭâ
CHTUISkillWindow				*g_cUISkillWindow = NULL;			// ��ųâ
CHTUIRefineWindow				*g_cUIRefineWindow = NULL;			// ����â
CHTUIQuestWindow				*g_cUIQuestWindow = NULL;			// ����Ʈâ
CHTUIMerchantWindow				*g_cUIMerchantWindow = NULL;		// ����â
CHTUIEmblemWindow				*g_cUIEmblemWindow = NULL;			// �ں�

//-----------------------------------------------------------------------------//
//  ���� : ���� ����
//  �ۼ����� / �ۼ��� : ������ (Only Tantra V3 UISystem)
//-----------------------------------------------------------------------------//
HTGamble*						g_cGamble = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ä�� ����
//  �ۼ����� / �ۼ��� : ������ (Only Tantra V3 UISystem)
//-----------------------------------------------------------------------------//
HTChatRoom*						g_cChatRoom = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ������
//  �ۼ����� / �ۼ��� : 20050812 / ���Ǳ�
//-----------------------------------------------------------------------------//
HTSiege*						g_pSiege = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��Ƽ
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTParty*						g_cParty = NULL;

//-----------------------------------------------------------------------------//
//  ���� : �ּҷ�
//  �ۼ����� / �ۼ��� : 2002_12_16 / ���Ǳ�
//-----------------------------------------------------------------------------//
HTAddress*						g_cAddress = NULL;

//-----------------------------------------------------------------------------//
//  ���� : �������̽� Ŭ����
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
CHTInterfaceCheck*				g_cInterfaceCheck = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��ȯ �ý���
//  �ۼ����� / �ۼ��� : 2002.11.02_���Ǳ�
//-----------------------------------------------------------------------------//
HTExchange*						g_cExchangeSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ����Ʈ �ý���
//  �ۼ����� / �ۼ��� : 2003.04.16_���Ǳ�
//-----------------------------------------------------------------------------//
CHTMiniMap*						g_cMiniMap = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ����Ʈ �ý���
//  �ۼ����� / �ۼ��� : 2002.11.29_���Ǳ�
//-----------------------------------------------------------------------------//
HTQuest*						g_cQuest = NULL;

//-----------------------------------------------------------------------------//
//  ���� : �ý���
//  �ۼ����� / �ۼ��� : 2002.11.29_���Ǳ�
//-----------------------------------------------------------------------------//
HTSystem*						g_cSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ����â
//  �ۼ����� / �ۼ��� : 2002.12.27_�輱��
//-----------------------------------------------------------------------------//
HTObjectInfo*					g_cObjectInfo = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ������ Ȱ��
//  �ۼ����� / �ۼ��� : 2003.01.11_���Ǳ�
//-----------------------------------------------------------------------------//
HTMapInfo*						g_cMapInfo = NULL;

//-----------------------------------------------------------------------------//
//  ���� : Config System
//  �ۼ����� / �ۼ��� : 2003.01.13_Tenma
//-----------------------------------------------------------------------------//
CHTConfigSystem*				g_pCfgSys = HT_NULL;

//-----------------------------------------------------------------------------//
//  ���� : Window handler, Instance handler
//  �ۼ����� / �ۼ��� : 2003.01.13_Tenma
//-----------------------------------------------------------------------------//
HWND							g_hWnd = NULL;
HINSTANCE						g_hInstance = NULL;

//-----------------------------------------------------------------------------//
//  ���� : SCP_INIT_CHAR ���� Initialize Time (���� Ŭ���̾�Ʈ ���)�� ����
//  �ۼ����� / �ۼ��� : 2003.01.22_Tenma / �Ǳ�
//-----------------------------------------------------------------------------//
time_t							g_tInitServerTime = 0;
time_t							g_tInitClientTime = 0;

//-----------------------------------------------------------------------------//
//���ϴ� ��������� üũ�Ѵ�.
//         �ϴ��� ���� �� Ŀ�ǵ������ -netscript�� �ִ����� �Ǻ��Ͽ� üũ�Ѵ�.
//		   -netscrpit�� ������ HT_TRUE�� �ٲ۴�.
//  �ۼ����� / �ۼ��� : 2003.02.04_Tenma
//-----------------------------------------------------------------------------//
HTint							g_bDevelopingMode = HT_FALSE;
HTbool							g_bTransparencyMode = HT_FALSE;

//-----------------------------------------------------------------------------//
//  ���� : �������� â
//  �ۼ����� / �ۼ��� : 2003.02.14Tenma
//-----------------------------------------------------------------------------//
CHTNotifyWindow*				g_pNotifyWindow = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� ��
//  �ۼ����� / �ۼ��� : 2003.03.07Tenma
//-----------------------------------------------------------------------------//
CHTMainBar*						g_pMainBar = NULL;

//-----------------------------------------------------------------------------//
//  ���� : New Interface System
//  �ۼ����� / �ۼ��� : 2005.06.30 / ������
//-----------------------------------------------------------------------------//
CHTUIManager*					g_cUIManager = NULL;

//-----------------------------------------------------------------------------//
//  ���� : GM
//  �ۼ����� / �ۼ��� : 2004.04.22 / ���Ǳ�
//-----------------------------------------------------------------------------//
HTGM*							g_cGMSystem = HT_NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��Ż / ����
//  �ۼ����� / �ۼ��� : 2003.02.20 / ���Ǳ�
//-----------------------------------------------------------------------------//
HTPortal*						g_cPortal				= HT_NULL;
HTbool							g_bZoneServerSwitching;
HTbool							g_bPortalServerConnectCheckSw;
HTbool							g_bPortalServerDisConnectCheckSw;
WORD							g_wResentZoneServerID	= 0;
HTshort							g_snResentZoneSiege		= 0;
HTint							g_wFirstZoneServerID	= 0;
WORD							g_wPotalID				= 0x00;
WORD							g_wWalf					= 0x00;
BYTE							g_byInitConnectType;
HTbyte							g_byIsDeadInit;

//-----------------------------------------------------------------------------//
//  ���� : �ε�_��ε� �Լ���
//  �ۼ����� / �ۼ��� : 2003.02.27Tenma
//-----------------------------------------------------------------------------//
CHTLoading*						g_cLoading = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ������ �ʱ�ȭ ���� ��û Ƚ��
//  �ۼ����� / �ۼ��� : 2003.02.28Tenma
//-----------------------------------------------------------------------------//
HTint							g_iRequestCharacterInitCount = 0;

//-----------------------------------------------------------------------------//
//  ���� : �÷����̺�
//  �ۼ����� / �ۼ��� : 2003.02.07Tenma
//-----------------------------------------------------------------------------//
HT_COLOR						
g_ColorTable[19] = {	// �÷����̺��� �ʱ�ȭ �Ͽ� �ش�.
		// COLORTABLE_BLACK
		HT_COLOR( 0.00f, 0.00f, 0.00f, 1.0f ),		// g_ColorTable[0 ]
		// COLORTABLE_BLUE
		HT_COLOR( 0.00f, 0.00f, 1.00f, 1.0f ),		// g_ColorTable[1 ]
		// COLORTABLE_LIGHTBLUE
		HT_COLOR( 0.00f, 0.68f, 0.93f, 1.0f ),		// g_ColorTable[2 ]
		// COLORTABLE_SKY
		HT_COLOR( 0.00f, 1.00f, 1.00f, 1.0f ),		// g_ColorTable[3 ]
		// COLORTABLE_DARKGREEN
		HT_COLOR( 0.00f, 1.00f, 0.00f, 1.0f ),		// g_ColorTable[4 ]
		// COLORTABLE_GREEN
		HT_COLOR( 0.00f, 1.00f, 0.00f, 1.0f ),		// g_ColorTable[5 ]
		// COLORTABLE_LIGHTGREEN
		HT_COLOR( 0.48f, 0.77f, 0.46f, 1.0f ),		// g_ColorTable[6 ]
		// COLORTABLE_ORANGE
		//HT_COLOR( 0.94f, 0.39f, 0.00f, 1.0f ),	// g_ColorTable[7 ]
		HT_COLOR( 1.00f, 0.59f, 0.00f, 1.0f ),		// g_ColorTable[7 ]
		// COLORTABLE_LIGHTORANGE
		HT_COLOR( 0.96f, 0.58f, 0.11f, 1.0f ),		// g_ColorTable[8 ]
		// COLORTABLE_DARKPEOPLE
		HT_COLOR( 0.99f, 0.77f, 0.54f, 1.0f ),		// g_ColorTable[9 ]
		// COLORTABLE_PEOPLE
		HT_COLOR( 0.75f, 0.25f, 1.00f, 1.0f ),		// g_ColorTable[10 ]
		// COLORTABLE_RED
		HT_COLOR( 1.00f, 0.00f, 0.00f, 1.0f ),		// g_ColorTable[11]
		// COLORTABLE_YELLOW
		HT_COLOR( 1.00f, 1.00f, 0.00f, 1.0f ),		// g_ColorTable[12]
		// COLORTABLE_TRADEMODE
		HT_COLOR( 0.00f, 0.68f, 0.93f, 1.0f ),		// g_ColorTable[13]
		// COLORTABLE_PEOPLE(?)
		HT_COLOR( 1.00f, 0.00f, 1.00f, 1.0f ),		// g_ColorTable[14]
		// COLORTABLE_WHITE
		HT_COLOR( 1.00f, 1.00f, 1.00f, 1.0f ),		// g_ColorTable[15]
		// COLORTABLE_LIGHTGRAY
		HT_COLOR( 0.80f, 0.80f, 0.80f, 1.0f ),		// g_ColorTable[16]
		// COLORTABLE_LIGHTYELLOW
		HT_COLOR( 1.00f, 0.96f, 0.60f, 1.0f ),		// g_ColorTable[17]
		// COLORTABLE_LIGHTRED
		HT_COLOR( 0.93f, 0.50f, 0.60f, 1.0f )		// g_ColorTable[18]
};

//-----------------------------------------------------------------------------//
//  ���� : �ִϸ��̼� ���̺�
//  �ۼ����� / �ۼ��� : 2004.01.07 / �Ǳ�
//-----------------------------------------------------------------------------//
HTint g_EtcAnmIndex[14] =
{
	HT_ANISTATE_STD,
	HT_ANISTATE_WLK,
	HT_ANISTATE_RUN,
	HT_ANISTATE_IDL,
	HT_ANISTATE_SITDOWN,
	HT_ANISTATE_HIT_S1H,
	HT_ANISTATE_DIE,
	HT_ANISTATE_STANDUP,
	HT_ANISTATE_MAGIC_DEFENCE,
	HT_ANISTATE_SIT,
	HT_ANISTATE_HIT,
	HT_ANISTATE_EMO_BOW,		// PC EMO, Bow, �λ�
	HT_ANISTATE_EMO_CHARGE,		// PC EMO, Charge, ����
	HT_ANISTATE_EMO_PROVOKE,		// PC EMO, Provoke, ����
};

//-----------------------------------------------------------------------------//
//  ���� : �÷��̿��� �Կ� ���Ͽ�
//  �ۼ����� / �ۼ��� : 2003.03.04Tenma  20030304Tenma_test
//-----------------------------------------------------------------------------//
HTbool							g_bGamePlayMovieForGlobal;
HTbool							g_bUseEngineCamera;
HTbool							g_bGoAttackCamera;

//-----------------------------------------------------------------------------//
//  ���� : ��ŷ�( ���, �Ȱ�, ���� ��� ), íũ�� �ý���
//  �ۼ����� / �ۼ��� : 2003.4.21 �輱��
//-----------------------------------------------------------------------------//
CHTNPCControl*					g_cNPCControl = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� Ŭ���� ��Ʈ��
//  �ۼ����� / �ۼ��� : 2003.4.21 ���Ǳ�
//-----------------------------------------------------------------------------//
HTAttackManager*				g_cAttackMgr = NULL;

//-----------------------------------------------------------------------------//
//  ���� : Hit Demage Ŭ���� ��Ʈ��
//  �ۼ����� / �ۼ��� : 2003.11.26 ���Ǳ�
//-----------------------------------------------------------------------------//
HitCountMgr*					g_cHitCountMgr = NULL;

//-----------------------------------------------------------------------------//
//  ���� : Ʃ�丮�� �ý���
//  �ۼ����� / �ۼ��� : 2003.8.1 ���Ǳ�
//-----------------------------------------------------------------------------//
HTTutorialSystem*				g_cTutorialSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��� �ý���
//  �ۼ����� / �ۼ��� : 2003.8.14 ���Ǳ�
//-----------------------------------------------------------------------------//
HTGuild*						g_cGuildSystem = NULL;
HTbool							g_bGuildMarkShow;
HTbool							g_bTrimuritiShow;

//-----------------------------------------------------------------------------//
//  ���� : ����ų â
//  �ۼ����� / �ۼ��� : 2003.9.17 ���Ǳ�
//-----------------------------------------------------------------------------//
HTQuickSlot*					g_cQuickSlot = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���â ó��
//  �ۼ����� / �ۼ��� : ���Ǳ� 20040124
//-----------------------------------------------------------------------------//
HTCommand*						g_cCommand = HT_NULL;

//-----------------------------------------------------------------------------//
//  ���� : ĳ���� �̵� ���ǵ� ����
//  �ۼ����� / �ۼ��� : 2004.07.15 ���Ǳ�
//-----------------------------------------------------------------------------//
HTint							g_iMemoryCharMoveSpeed5;

// HK : ���� �׽�Ʈ�� ���� ġƮŰ��
HTDebugCheat g_bShowFPS;

//-----------------------------------------------------------------------------//
//  ���� : ID / PASSWORD / ���� ����Ʈ
//  �ۼ����� / �ۼ��� : ���Ǳ�
//-----------------------------------------------------------------------------//
HTint							g_iLoginResultID;
HTbool							g_bPCRoomEventWndLogo;
HTdword							g_dwMyEvent;
CHTString						g_strLoginID;
CHTString						g_strLgoinPasswordMD5;
CHTString						g_strLgoinPasswordMD5Plus;
WORLDLIST						g_oWorldList[MAX_SERVERGROUP][MAX_SERVER];		// �� ������ ����
HTint							g_iWorldNum;
CHTString						g_strZoneServerIP;
HTint							g_iZoneServerPort;
HTint							g_iConnectServerGroupIndex;					//	������ ���� �׷�
CHTString						g_strSelectServerName;						//	������ ���� �̸�

//	�κ��͸� �̿��Ͽ� ���� ���� ���´�.
HTfloat HT_extern_fGetRidan(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	�������ϱ� -> ������ ����(����)�� �˱� ����
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A ������ ���밪(����) ���ϱ� 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B ������ ���밪(����) ���ϱ� 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  ������ �̿��ؼ� ���� ���ϱ�

	float acos = acosf( cos );						//	�ڻ��ΰ��� ���Ȱ� �ٲٱ�
	float direction = A.z*B.x - B.z*A.x;			//	���� ������ ��
	if(direction < 0)								//	dirction ���̸� ���� , ���̸� ������
		acos *= -1;
	return acos;
}

//	Returns Cur TargetToResentTerm
HTfloat HT_extern_fGetDisForTwoPoint( HTvector3 vecTargetPos, HTvector3 vecSourcePos )
{
	return (float)sqrt( double( (vecTargetPos.x - vecSourcePos.x) * (vecTargetPos.x - vecSourcePos.x) ) 
					  + double( (vecTargetPos.z - vecSourcePos.z) * (vecTargetPos.z - vecSourcePos.z) ) );
}

//	�ֽ��� ���� �Ǻ�
HTRESULT HT_extern_TrimuritiZone( HTint iZone )
{
	if( iZone == ZONE_KURUMA || 
		iZone == ZONE_CHATURANGGA ||
		iZone == ZONE_ANAKAKURUMA )
		return HT_OK;
	else
		return HT_FAIL;
}

//	����� ���� �Ǻ�
HTRESULT HT_extern_ForetressZone( HTint iZone )
{
	if( iZone == ZONE_FORTRESS )
		return HT_OK;
	else
		return HT_FAIL;
}

//-----------------------------------------------------------------------------//
//  ���� : �ϴ��� ���� ��
//  �ۼ����� / �ۼ��� : ���⼮ 20031219
//-----------------------------------------------------------------------------//
CHTFlocking*					g_pFlocking = HT_NULL;
HTint							m_giBGM = 0;

//-----------------------------------------------------------------------------//
//  ���� : Test/Main Server
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040126
//-----------------------------------------------------------------------------//
HTint							g_gServerType;

//-----------------------------------------------------------------------------//
//  ���� : ���� ����
//  �ۼ����� / �ۼ��� : �輱�� / 20040202
//-----------------------------------------------------------------------------//
CHTIndividualStore*				g_cIndividualStore = HT_NULL;

//-----------------------------------------------------------------------------//
//  ���� : ��Ź ����
//  �ۼ����� / �ۼ��� : ������ / 20051013
//-----------------------------------------------------------------------------//
CHTRentalStore*				g_cRentalStore = HT_NULL;


//-----------------------------------------------------------------------------//
//  ���� : initChar�� �ι� ���� �� �ִ� ��츦 �����ϱ� ����
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040211
//-----------------------------------------------------------------------------//
HTint							g_iInitCharSW;

//-----------------------------------------------------------------------------//
//  ���� : ȭ����� ��� UI�� ���̰� �Ұ����� �Ⱥ��̰� �Ұ����� ����
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040214
//-----------------------------------------------------------------------------//
HTbool							g_bShowUI;
HTint							g_iShowUI;

//-----------------------------------------------------------------------------//
//  ���� : �̺�Ʈ �˾� â
//  �ۼ����� / �ۼ��� : 2004.04.12 �輱��
//-----------------------------------------------------------------------------//
CHTEventWindow*				g_pEventWindow = NULL;

//-----------------------------------------------------------------------------//
//  ���� : ���� �ý���
//  �ۼ����� / �ۼ��� : 2004.12.14 ���Ǳ�
//-----------------------------------------------------------------------------//
HTDuelSystem*					g_pDuelSystem = NULL;

//-----------------------------------------------------------------------------//
//  ���� : IME String
//  �ۼ����� / �ۼ��� : 2004.06.22 ���Ǳ�
//-----------------------------------------------------------------------------//
//	IME Mgr Class
HTImeMgr						g_cImeMgr;
HTbool							g_bShowCompStrSw;
CHTString						g_strImeName;
CHTString						g_strResultText;
CHTString						g_strCompStr;
CHTString						g_strCompReadStr;
CHTString						g_strCandidateList[10];
HTint							g_iCandiSelectionNo;
HTint							g_idwCandidateListNo;
HTbool							g_bSkipMessageOnChar;
HTvector3						g_vecCompStrPos;			//	IME Comp String Pos

//-----------------------------------------------------------------------------//
//  ���� : �����ڵ�
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040823
//-----------------------------------------------------------------------------//
HTint							g_iInationalCode;
HTint							g_iInationalType;

//-----------------------------------------------------------------------------//
//  ���� : �� Ŀ��Ʈ
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040023
//-----------------------------------------------------------------------------//
CHTWebLogIn*					g_poWebLogIn;

//-----------------------------------------------------------------------------//
//  ���� : ���� ���� ���� ���
//  �ۼ����� / �ۼ��� : 2005.03.31
//-----------------------------------------------------------------------------//
HTbool							g_bReciveBillingServer;

//-----------------------------------------------------------------------------//
//  ���� : ī�޶� �̵���Ȳ�� üũ����
//  �ۼ����� / �ۼ��� : 2005.08.14
//-----------------------------------------------------------------------------//
HTbool							g_bCameraMove;

//-----------------------------------------------------------------------------//
//  ���� : �ƽ��� ��ũ Į��,
//  �ۼ����� / �ۼ��� : 2005.09.13
//-----------------------------------------------------------------------------//
HT_COLOR AMBLEM_COLOR[72] = 
{
	HT_COLOR(57.0f/255.0f,	221.0f/255.0f,	215.0f/255.0f,1.0f),
	HT_COLOR(26.0f/255.0f,	156.0f/255.0f,	216.0f/255.0f,1.0f), 
	HT_COLOR(54.0f/255.0f,	84.0f/255.0f,	221.0f/255.0f,1.0f),
	HT_COLOR(124.0f/255.0f, 206.0f/255.0f,	159.0f/255.0f,1.0f), 
	HT_COLOR(70.0f/255.0f,	196.0f/255.0f,	49.0f/255.0f ,1.0f), 
	HT_COLOR(101.0f/255.0f, 141.0f/255.0f,	77.0f/255.0f ,1.0f), 
	HT_COLOR(253.0f/255.0f, 65.0f/255.0f,	34.0f/255.0f ,1.0f),
	HT_COLOR(216.0f/255.0f, 53.0f/255.0f,	26.0f/255.0f ,1.0f),
	HT_COLOR(186.0f/255.0f, 18.0f/255.0f,	18.0f/255.0f ,1.0f),
	HT_COLOR(236.0f/255.0f, 195.0f/255.0f,	107.0f/255.0f,1.0f),
	HT_COLOR(238.0f/255.0f, 138.0f/255.0f,	41.0f/255.0f ,1.0f),
	HT_COLOR(221.0f/255.0f, 99.0f/255.0f,	0.0f/255.0f  ,1.0f),
	HT_COLOR(255.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 249.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 246.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 242.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 237.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(240.0f/255.0f, 232.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(240.0f/255.0f, 227.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(240.0f/255.0f, 221.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(240.0f/255.0f, 216.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(240.0f/255.0f, 210.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(230.0f/255.0f, 204.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(230.0f/255.0f, 198.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(230.0f/255.0f, 194.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(230.0f/255.0f, 188.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(230.0f/255.0f, 183.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(227.0f/255.0f, 179.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(227.0f/255.0f, 174.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(227.0f/255.0f, 170.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(227.0f/255.0f, 167.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(227.0f/255.0f, 165.0f/255.0f, 0.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 201.0f/255.0f, 28.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 189.0f/255.0f, 28.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 180.0f/255.0f, 28.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 170.0f/255.0f, 28.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 160.0f/255.0f, 28.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 148.0f/255.0f, 15.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 136.0f/255.0f, 15.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 122.0f/255.0f, 15.0f/255.0f,1.0f),
	HT_COLOR(255.0f/255.0f, 109.0f/255.0f, 15.0f/255.0f,1.0f),
	HT_COLOR(251.0f/255.0f, 96.0f/255.0f, 15.0f/255.0f,1.0f),
	HT_COLOR(246.0f/255.0f, 83.0f/255.0f, 7.0f/255.0f, 1.0f),
	HT_COLOR(242.0f/255.0f, 69.0f/255.0f, 7.0f/255.0f, 1.0f),
	HT_COLOR(236.0f/255.0f, 55.0f/255.0f, 7.0f/255.0f, 1.0f),
	HT_COLOR(233.0f/255.0f, 45.0f/255.0f, 7.0f/255.0f, 1.0f),
	HT_COLOR(229.0f/255.0f, 33.0f/255.0f, 7.0f/255.0f, 1.0f),
	HT_COLOR(223.0f/255.0f, 21.0f/255.0f, 1.0f/255.0f, 1.0f),
	HT_COLOR(221.0f/255.0f, 12.0f/255.0f, 1.0f/255.0f, 1.0f),
	HT_COLOR(217.0f/255.0f, 2.0f/255.0f, 1.0f/255.0f, 1.0f),
	HT_COLOR(215.0f/255.0f, 0.0f/255.0f, 1.0f/255.0f, 1.0f),
	HT_COLOR(214.0f/255.0f, 0.0f/255.0f, 1.0f/255.0f, 1.0f),
	HT_COLOR(0.0f/255.0f, 204.0f/255.0f, 255.0f/255.0f, 1.0f),
	HT_COLOR(0.0f/255.0f, 197.0f/255.0f, 253.0f/255.0f, 1.0f),
	HT_COLOR(0.0f/255.0f, 192.0f/255.0f, 250.0f/255.0f, 1.0f),
	HT_COLOR(0.0f/255.0f, 185.0f/255.0f, 248.0f/255.0f, 1.0f),
	HT_COLOR(0.0f/255.0f, 178.0f/255.0f, 245.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 172.0f/255.0f, 243.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 164.0f/255.0f, 240.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 157.0f/255.0f, 238.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 149.0f/255.0f, 235.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 140.0f/255.0f, 232.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 132.0f/255.0f, 229.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 124.0f/255.0f, 226.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 117.0f/255.0f, 223.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 109.0f/255.0f, 221.0f/255.0f, 1.0f),
	HT_COLOR(1.0f/255.0f, 101.0f/255.0f, 218.0f/255.0f, 1.0f),
	HT_COLOR(2.0f/255.0f, 95.0f/255.0f, 215.0f/255.0f, 1.0f),
	HT_COLOR(2.0f/255.0f, 89.0f/255.0f, 213.0f/255.0f, 1.0f),
	HT_COLOR(2.0f/255.0f, 83.0f/255.0f, 212.0f/255.0f, 1.0f),
	HT_COLOR(2.0f/255.0f, 79.0f/255.0f, 210.0f/255.0f, 1.0f),
	HT_COLOR(2.0f/255.0f, 75.0f/255.0f, 209.0f/255.0f, 1.0f)
};	  

//-----------------------------------------------------------------------------//
//  ���� : ��ũ��Ʈ�κ��� �޽����� ���ͼ� �������ش�.
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20041018
//-----------------------------------------------------------------------------//
HTvoid HT_g_Script_SetMessage( HTint idMessage, CHTString* pszMessage, CHTString strInputItem1, CHTString strInputItem2 )
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
		//CHTString szOut1, szOut2, szOut3;

		//// sParam1
		//HT_g_Script_SetParamTextForMessage( sParam1, &szOut1 );
		//// sParam2
		//HT_g_Script_SetParamTextForMessage( sParam2, &szOut2 );
		//// sParam3
		//HT_g_Script_SetParamTextForMessage( sParam3, &szOut3 );

		//pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString(), strInputItem2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString() );
	}
	else
	{
		*pszMessage = szString;
	}
}

HTEBlogAccessStatus g_eBlogAccessStatus;
HTint g_iBlogClickedChar;

//-----------------------------------------------------------------------------//
//  ���� : �츮�� ������� ReStart
//	Code : 0:���ʷα���, 1:��������Ʈ, 2:Character, 3:GameExit
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20041121
//-----------------------------------------------------------------------------//
HTbyte							g_byReStartCode;
HTbyte							g_byReStartButtonCode;

//-----------------------------------------------------------------------------//
//  ���� : ���� üũ
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20050311
//-----------------------------------------------------------------------------//
HTshort							g_snVersionCheck[4];


//-----------------------------------------------------------------------------//
//  ���� : ĳ���� �̸��� ����̸����� ����ؼ��� �ȵ� ����
//  �ۼ����� / �ۼ��� : ���Ǳ� / 20040023
//-----------------------------------------------------------------------------//
char g_szNotCharAndGuildName[NOTCHARANDGUILDNAME_COUNT][3] = { 
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","��","?", "?", "?", "?", 
							   "?", "?", "��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","��","��","?", "?", "?", 
							   "?", "?", "?", "?", "?", "?", "?", "?", "��","��",
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","?", "?", "?", "?", "?", "?", "?", 
							   "?", "?", "?", "?", "?", "?", "?", "?", "��","��",
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��"," ", "��","��","�Q","�i","�j",
                               "��","��","?", "�A","�B","?", "?", "�a","�b","�c",
                               "�d","�e","�f","�h","�g","�i","�j","�k","�l","�m",
                               "�n","�o","�p","�q","�r","�s","�t","�u","?", "?",
                               "��","��","��","��","��","��","��","��","��","��",
							   "��","��","��","��","��","?", "?", "��","��","��" };

//	ĳ�����̳� ����̸����� �Ұ��� ���� �ε�
HTvoid  HT_g_LoadNotCharAndGuildName()
{
	memset( g_szNotCharAndGuildName, 0, 3 * NOTCHARANDGUILDNAME_COUNT );

	FILE *fp = fopen("./system/bufferstring.txt","rt");
	if ( fp )
	{
		HTint i, j;
		HTtchar str[256];
		HTtchar* token;
		HTtchar seps[] = ",\n";

		for ( i = 0; i < NOTCHARANDGUILDNAME_COUNT; i += 10 )
		{
			HTtchar* ret = _fgetts( str, 255, fp );

			token = _tcstok( str, seps );
			if ( token ) CHTString::HT_hrStringCopy( g_szNotCharAndGuildName[i], token, 3 );

			for ( j = 1; j < 10; ++j )
			{
				token = _tcstok( HT_NULL, seps );
				if ( token ) CHTString::HT_hrStringCopy( g_szNotCharAndGuildName[i+j], token, 3 );
			}
		}
		fclose(fp);

		// Encoding : XOR�� ����ؼ� 0�� 1�� 1�� 0���� �ٲٴ� �ٺ����� ���ڵ��� ����Ѵ�. ���簡 ������ -_-;
		CHTFile oFile;
		if ( oFile.HT_bOpen( "./system/bufferstring.bin", HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
		{
			HTtchar szServerBin[3];
			for ( i = 0; i < NOTCHARANDGUILDNAME_COUNT; ++i )
			{
				for ( j = 0; j < 3; ++j )
				{
					szServerBin[j] = g_szNotCharAndGuildName[i][j] ^ 0xFF;
				}
				oFile.HT_bWrite( szServerBin, 3 );
			}
			oFile.HT_vClose();
		}
	}
	else
	{
		CHTFile oFile;
		if ( oFile.HT_bOpen( "./system/bufferstring.bin", HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) )
		{
			HTtchar szServerBin[3];
			for ( HTint i = 0; i < NOTCHARANDGUILDNAME_COUNT; ++i )
			{
				oFile.HT_bRead( szServerBin, 3 );
				for ( HTint j = 0; j < 3; ++j ) 
				{
					g_szNotCharAndGuildName[i][j] = szServerBin[j] ^ 0xFF;
				}
			}
			oFile.HT_vClose();
		}
	}
}