#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"

//-----------------------------------------------------------------------------//
//  설명 : 디버깅 메시지 출력
//  작성일자 / 작성자 : 2003.03.03 서명석 20030303Tenma
//-----------------------------------------------------------------------------//
FILE* g_pDebugFile = NULL;

HTvoid	HT_g_vOpenDebugFile()
{
#ifdef HT_DEBUG_LOGFILE
	//if( g_iInationalType != INATIONALTYPE_KOREA )
		g_pDebugFile = fopen( "Tantra_Crash.txt", "w" );
#endif

	////	임도네시아를 위하여...
	////	NewKruma를 바꾸어 준다.
	//if( g_iInationalType == INATIONALTYPE_INDONESIA )
	//{
	//	WIN32_FIND_DATA FindFileData;
	//	HANDLE hFind;

	//	hFind = FindFirstFile( _T(".\\resource\\map\\NewKruma"), &FindFileData);
	//	//	파일을 찿았으면
	//	if (hFind != INVALID_HANDLE_VALUE)
	//	{
	//		FindClose(hFind);
	//		//	기존의 파일을 전부 지우고
	//		//	맵파일 부분
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
	//		//	맵파일 컨피그 부분
	//		SetFileAttributes( ".\\resource\\map\\MAP_Jina4th.cfg", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\map\\MAP_Jina4th.cfg" );
	//		//	오브젝트 부분
	//		SetFileAttributes( ".\\resource\\object\\Jina4thObjTex.hpk", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\object\\Jina4thObjTex.hpk" );
	//		SetFileAttributes( ".\\resource\\object\\Jina4thObjTmb.hpk", FILE_ATTRIBUTE_NORMAL );
	//		DeleteFile( ".\\resource\\object\\Jina4thObjTmb.hpk" );

	//		//	그리고 새로운 파일을 전부 복사한다.
	//		//	맵파일 부분
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tcc", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tcc" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.thm", ".\\resource\\map\\Jina4th\\MAP_Jina4th.thm" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tme", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tme" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\MAP_NewKruma.tml", ".\\resource\\map\\Jina4th\\MAP_Jina4th.tml" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\Sky.tmd", ".\\resource\\map\\Jina4th\\Sky.tmd" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\SkyTerrain.tmd", ".\\resource\\map\\Jina4th\\SkyTerrain.tmd" );//, FALSE );
	//		MoveFile( ".\\resource\\map\\NewKruma\\TerrainTex.hpk", ".\\resource\\map\\Jina4th\\TerrainTex.hpk" );//, FALSE );
	//		//	맵파일 컨피그 부분
	//		CopyFile( ".\\resource\\map\\MAP_NewKruma.cfg", ".\\resource\\map\\MAP_Jina4th.cfg", FALSE );
	//		//	오브젝트 부분
	//		CopyFile( ".\\resource\\object\\NewKrumaObjTex.hpk", ".\\resource\\object\\Jina4thObjTex.hpk", FALSE );
	//		CopyFile( ".\\resource\\object\\NewKrumaObjTmb.hpk", ".\\resource\\object\\Jina4thObjTmb.hpk", FALSE );

	//		//	전부 성공하였다면 기존의 NewKruma폴더를 지워 버린다.
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
//  설명 : 메인 게임
//  작성일자 / 작성자 : 2003.03.03 서명석 20030303Tenma
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

//현재 게임이 진행된 상태를 가지고 있음.
HTbool							g_bMainCharacterInitialized = HT_FALSE;
BYTE							g_bOneTimeUpdate;
HTint							g_iGameSequnce;
HTint							g_iGameBigSequnce;

//-----기본적인 정보-----//
HTInfoLoad*						g_BasicLoadingInfo;

//-----------------------------------------------------------------------------//
//  설명 : 메인 캐릭터
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTMainCharacter*				g_cMainCharacter = NULL;
HTAOI*							g_cAoi = NULL;
S_CHARACTER_LIST				g_oMainCharacterInfo;
BYTE							g_byteMainCharacterCaste;		// 구조체에 추가할 수없어, 별도로 전역 선언사용 (계급)

//	이동속도
signed char					g_byteSpeed1, g_byteSpeed2, g_byteSpeed3;
signed char					g_byteSpeedCorrection;
signed char					g_byteSpeedParity;

//	공격속도 패킷
signed char					g_byteAS1, g_byteAS2, g_byteAS3, g_byteAS4;
signed char					g_byteParity;

// 서버와 연결되는 종족 코드
BYTE g_byCharacterServerTribe[8] = {	1,	// 나가
										4,	// 아수라
										16,	// 약샤
										64,	// 데바
										2,	// 킨나라
										8, // 라크샤사
										32,	// 간다르바
										128,// 가루다
									};

//-----------------------------------------------------------------------------//
//  설명 : OtherObject 관리
//  작성일자 / 작성자 : 20040106 / 정의규
//-----------------------------------------------------------------------------//
HTOtherObjectSystem*			g_cOtherObjectSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 인트로
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTIntroManager*				g_cIntroManager = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 에디터에서 각종 데이타(스킬, 아이템, 몬스터, NPC, NPC 샆) 로딩
//  작성일자 / 작성자 : 김선미
//-----------------------------------------------------------------------------//
CHTClientParamMgr*				g_pParamMgr = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 에디터에서 각종 데이타(스킬, 아이템, 몬스터, NPC, NPC 샆) 로딩
//  작성일자 / 작성자 : 김선미
//-----------------------------------------------------------------------------//
CHTMessageMgr*					g_pMessageMgr = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 몬스터 / NPC
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTNPCSystem*					g_sNPCSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 스킬
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTSkillSystem*					g_cSkillSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 아이템 시스템
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTItemSystem*					g_cItemSystem = NULL;
HTItemControl*					g_cItemControl = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 게임 시스템
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTGameSystem*					g_cGameSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 2D 스프라이트 메니져
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHT2DObjectMgr*					g_2DObjectMgr = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 네트워크 메니져
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
TNNetworkManager*				g_pNetWorkMgr;
CPSock							g_cCPSock;

TNChatNetworkManager*			g_pChatNetWorkMgr;
CPSock							g_cChatCPSock;	// 성회 추가 (2005.12.19)

//-----------------------------------------------------------------------------//
//  설명 : 채팅에 관련하여
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTChatting*					g_cChatting = NULL;					// 대호 수정 (2002.09.16)

//-----------------------------------------------------------------------------//
//  설명 : 초기화 정보를 내려받았는지 체크
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
DWORD							g_cInitConntion_StartTime;

//-----------------------------------------------------------------------------//
//  설명 : 캐릭터 장착 시스템
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTEquipSystem*					g_cEquipSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 게임 시스템 인벤토리 관련 부분_스킬, 장착인벤토리, 벨트인벤토리
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTSkillInventory*				g_cSkillInventory = NULL;
CHTEquipInventory*				g_cEquipInventory = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 캐릭터 스테이터스 관련
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTStatus*						g_cStatus = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 캐릭터 UI 윈도우 관련 (카타나2 확장버전)
//  작성일자 / 작성자 : 선영범
//-----------------------------------------------------------------------------//
CHTUIStatus						*g_cUIStatus = NULL;				// 상태창
CHTUINPCWindow					*g_cUINPCWindow = NULL;				// NPC 대화창
CHTUISkillWindow				*g_cUISkillWindow = NULL;			// 스킬창
CHTUIRefineWindow				*g_cUIRefineWindow = NULL;			// 제련창
CHTUIQuestWindow				*g_cUIQuestWindow = NULL;			// 퀘스트창
CHTUIMerchantWindow				*g_cUIMerchantWindow = NULL;		// 마켓창
CHTUIEmblemWindow				*g_cUIEmblemWindow = NULL;			// 앰블램

//-----------------------------------------------------------------------------//
//  설명 : 도박 관련
//  작성일자 / 작성자 : 선영범 (Only Tantra V3 UISystem)
//-----------------------------------------------------------------------------//
HTGamble*						g_cGamble = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 채팅 관련
//  작성일자 / 작성자 : 선영범 (Only Tantra V3 UISystem)
//-----------------------------------------------------------------------------//
HTChatRoom*						g_cChatRoom = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 공성전
//  작성일자 / 작성자 : 20050812 / 정의규
//-----------------------------------------------------------------------------//
HTSiege*						g_pSiege = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 파티
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTParty*						g_cParty = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 주소록
//  작성일자 / 작성자 : 2002_12_16 / 정의규
//-----------------------------------------------------------------------------//
HTAddress*						g_cAddress = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 인터페이스 클래스
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
CHTInterfaceCheck*				g_cInterfaceCheck = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 교환 시스템
//  작성일자 / 작성자 : 2002.11.02_정의규
//-----------------------------------------------------------------------------//
HTExchange*						g_cExchangeSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 퀘스트 시스템
//  작성일자 / 작성자 : 2003.04.16_정의규
//-----------------------------------------------------------------------------//
CHTMiniMap*						g_cMiniMap = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 퀘스트 시스템
//  작성일자 / 작성자 : 2002.11.29_정의규
//-----------------------------------------------------------------------------//
HTQuest*						g_cQuest = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 시스템
//  작성일자 / 작성자 : 2002.11.29_정의규
//-----------------------------------------------------------------------------//
HTSystem*						g_cSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 정보창
//  작성일자 / 작성자 : 2002.12.27_김선미
//-----------------------------------------------------------------------------//
HTObjectInfo*					g_cObjectInfo = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 맵정보 활용
//  작성일자 / 작성자 : 2003.01.11_정의규
//-----------------------------------------------------------------------------//
HTMapInfo*						g_cMapInfo = NULL;

//-----------------------------------------------------------------------------//
//  설명 : Config System
//  작성일자 / 작성자 : 2003.01.13_Tenma
//-----------------------------------------------------------------------------//
CHTConfigSystem*				g_pCfgSys = HT_NULL;

//-----------------------------------------------------------------------------//
//  설명 : Window handler, Instance handler
//  작성일자 / 작성자 : 2003.01.13_Tenma
//-----------------------------------------------------------------------------//
HWND							g_hWnd = NULL;
HINSTANCE						g_hInstance = NULL;

//-----------------------------------------------------------------------------//
//  설명 : SCP_INIT_CHAR 시의 Initialize Time (서버 클라이언트 모두)를 저장
//  작성일자 / 작성자 : 2003.01.22_Tenma / 의규
//-----------------------------------------------------------------------------//
time_t							g_tInitServerTime = 0;
time_t							g_tInitClientTime = 0;

//-----------------------------------------------------------------------------//
//용하는 모드인지를 체크한다.
//         일단은 실행 시 커맨드라인의 -netscript가 있는지를 판별하여 체크한다.
//		   -netscrpit가 있으면 HT_TRUE롤 바꾼다.
//  작성일자 / 작성자 : 2003.02.04_Tenma
//-----------------------------------------------------------------------------//
HTint							g_bDevelopingMode = HT_FALSE;
HTbool							g_bTransparencyMode = HT_FALSE;

//-----------------------------------------------------------------------------//
//  설명 : 공지사항 창
//  작성일자 / 작성자 : 2003.02.14Tenma
//-----------------------------------------------------------------------------//
CHTNotifyWindow*				g_pNotifyWindow = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 메인 바
//  작성일자 / 작성자 : 2003.03.07Tenma
//-----------------------------------------------------------------------------//
CHTMainBar*						g_pMainBar = NULL;

//-----------------------------------------------------------------------------//
//  설명 : New Interface System
//  작성일자 / 작성자 : 2005.06.30 / 선영범
//-----------------------------------------------------------------------------//
CHTUIManager*					g_cUIManager = NULL;

//-----------------------------------------------------------------------------//
//  설명 : GM
//  작성일자 / 작성자 : 2004.04.22 / 정의규
//-----------------------------------------------------------------------------//
HTGM*							g_cGMSystem = HT_NULL;

//-----------------------------------------------------------------------------//
//  설명 : 포탈 / 워프
//  작성일자 / 작성자 : 2003.02.20 / 정의규
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
//  설명 : 로딩_언로딩 함수군
//  작성일자 / 작성자 : 2003.02.27Tenma
//-----------------------------------------------------------------------------//
CHTLoading*						g_cLoading = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 서버에 초기화 정보 요청 횟수
//  작성일자 / 작성자 : 2003.02.28Tenma
//-----------------------------------------------------------------------------//
HTint							g_iRequestCharacterInitCount = 0;

//-----------------------------------------------------------------------------//
//  설명 : 컬러테이블
//  작성일자 / 작성자 : 2003.02.07Tenma
//-----------------------------------------------------------------------------//
HT_COLOR						
g_ColorTable[19] = {	// 컬러테이블을 초기화 하여 준다.
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
//  설명 : 애니매이션 테이블
//  작성일자 / 작성자 : 2004.01.07 / 의규
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
	HT_ANISTATE_EMO_BOW,		// PC EMO, Bow, 인사
	HT_ANISTATE_EMO_CHARGE,		// PC EMO, Charge, 돌격
	HT_ANISTATE_EMO_PROVOKE,		// PC EMO, Provoke, 도발
};

//-----------------------------------------------------------------------------//
//  설명 : 플레이영상 촬영 위하여
//  작성일자 / 작성자 : 2003.03.04Tenma  20030304Tenma_test
//-----------------------------------------------------------------------------//
HTbool							g_bGamePlayMovieForGlobal;
HTbool							g_bUseEngineCamera;
HTbool							g_bGoAttackCamera;

//-----------------------------------------------------------------------------//
//  설명 : 상거래( 사고, 팔고, 수리 등등 ), 챠크라 시스템
//  작성일자 / 작성자 : 2003.4.21 김선미
//-----------------------------------------------------------------------------//
CHTNPCControl*					g_cNPCControl = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 공격 클래스 컨트롤
//  작성일자 / 작성자 : 2003.4.21 정의규
//-----------------------------------------------------------------------------//
HTAttackManager*				g_cAttackMgr = NULL;

//-----------------------------------------------------------------------------//
//  설명 : Hit Demage 클래스 컨트롤
//  작성일자 / 작성자 : 2003.11.26 정의규
//-----------------------------------------------------------------------------//
HitCountMgr*					g_cHitCountMgr = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 튜토리얼 시스템
//  작성일자 / 작성자 : 2003.8.1 정의규
//-----------------------------------------------------------------------------//
HTTutorialSystem*				g_cTutorialSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 길드 시스템
//  작성일자 / 작성자 : 2003.8.14 정의규
//-----------------------------------------------------------------------------//
HTGuild*						g_cGuildSystem = NULL;
HTbool							g_bGuildMarkShow;
HTbool							g_bTrimuritiShow;

//-----------------------------------------------------------------------------//
//  설명 : 퀵스킬 창
//  작성일자 / 작성자 : 2003.9.17 정의규
//-----------------------------------------------------------------------------//
HTQuickSlot*					g_cQuickSlot = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 명령창 처리
//  작성일자 / 작성자 : 정의규 20040124
//-----------------------------------------------------------------------------//
HTCommand*						g_cCommand = HT_NULL;

//-----------------------------------------------------------------------------//
//  설명 : 캐리터 이동 스피드 저장
//  작성일자 / 작성자 : 2004.07.15 정의규
//-----------------------------------------------------------------------------//
HTint							g_iMemoryCharMoveSpeed5;

// HK : 개발 테스트를 위해 치트키들
HTDebugCheat g_bShowFPS;

//-----------------------------------------------------------------------------//
//  설명 : ID / PASSWORD / 월드 리스트
//  작성일자 / 작성자 : 정의규
//-----------------------------------------------------------------------------//
HTint							g_iLoginResultID;
HTbool							g_bPCRoomEventWndLogo;
HTdword							g_dwMyEvent;
CHTString						g_strLoginID;
CHTString						g_strLgoinPasswordMD5;
CHTString						g_strLgoinPasswordMD5Plus;
WORLDLIST						g_oWorldList[MAX_SERVERGROUP][MAX_SERVER];		// 각 월드의 정보
HTint							g_iWorldNum;
CHTString						g_strZoneServerIP;
HTint							g_iZoneServerPort;
HTint							g_iConnectServerGroupIndex;					//	선택한 서버 그룹
CHTString						g_strSelectServerName;						//	서택한 서버 이름

//	두벡터를 이용하여 라디안 값을 얻어온다.
HTfloat HT_extern_fGetRidan(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	내적구하기 -> 벡터의 관계(각도)를 알기 위해
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A 벡터의 절대값(길이) 구하기 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B 벡터의 절대값(길이) 구하기 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  세값을 이용해서 각도 구하기

	float acos = acosf( cos );						//	코사인값을 라디안값 바꾸기
	float direction = A.z*B.x - B.z*A.x;			//	왼쪽 오른쪽 비교
	if(direction < 0)								//	dirction 음이면 왼쪽 , 양이면 오른쪽
		acos *= -1;
	return acos;
}

//	Returns Cur TargetToResentTerm
HTfloat HT_extern_fGetDisForTwoPoint( HTvector3 vecTargetPos, HTvector3 vecSourcePos )
{
	return (float)sqrt( double( (vecTargetPos.x - vecSourcePos.x) * (vecTargetPos.x - vecSourcePos.x) ) 
					  + double( (vecTargetPos.z - vecSourcePos.z) * (vecTargetPos.z - vecSourcePos.z) ) );
}

//	주신전 지역 판별
HTRESULT HT_extern_TrimuritiZone( HTint iZone )
{
	if( iZone == ZONE_KURUMA || 
		iZone == ZONE_CHATURANGGA ||
		iZone == ZONE_ANAKAKURUMA )
		return HT_OK;
	else
		return HT_FAIL;
}

//	요새전 지역 판별
HTRESULT HT_extern_ForetressZone( HTint iZone )
{
	if( iZone == ZONE_FORTRESS )
		return HT_OK;
	else
		return HT_FAIL;
}

//-----------------------------------------------------------------------------//
//  설명 : 하늘을 나는 새
//  작성일자 / 작성자 : 정기석 20031219
//-----------------------------------------------------------------------------//
CHTFlocking*					g_pFlocking = HT_NULL;
HTint							m_giBGM = 0;

//-----------------------------------------------------------------------------//
//  설명 : Test/Main Server
//  작성일자 / 작성자 : 정의규 / 20040126
//-----------------------------------------------------------------------------//
HTint							g_gServerType;

//-----------------------------------------------------------------------------//
//  설명 : 개인 상점
//  작성일자 / 작성자 : 김선미 / 20040202
//-----------------------------------------------------------------------------//
CHTIndividualStore*				g_cIndividualStore = HT_NULL;

//-----------------------------------------------------------------------------//
//  설명 : 위탁 상점
//  작성일자 / 작성자 : 선영범 / 20051013
//-----------------------------------------------------------------------------//
CHTRentalStore*				g_cRentalStore = HT_NULL;


//-----------------------------------------------------------------------------//
//  설명 : initChar를 두번 받을 수 있는 경우를 예방하기 위해
//  작성일자 / 작성자 : 정의규 / 20040211
//-----------------------------------------------------------------------------//
HTint							g_iInitCharSW;

//-----------------------------------------------------------------------------//
//  설명 : 화면안의 모든 UI를 보이게 할것인지 안보이게 할것인지 결정
//  작성일자 / 작성자 : 정의규 / 20040214
//-----------------------------------------------------------------------------//
HTbool							g_bShowUI;
HTint							g_iShowUI;

//-----------------------------------------------------------------------------//
//  설명 : 이벤트 팝업 창
//  작성일자 / 작성자 : 2004.04.12 김선미
//-----------------------------------------------------------------------------//
CHTEventWindow*				g_pEventWindow = NULL;

//-----------------------------------------------------------------------------//
//  설명 : 결투 시스템
//  작성일자 / 작성자 : 2004.12.14 정의규
//-----------------------------------------------------------------------------//
HTDuelSystem*					g_pDuelSystem = NULL;

//-----------------------------------------------------------------------------//
//  설명 : IME String
//  작성일자 / 작성자 : 2004.06.22 정의규
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
//  설명 : 국가코드
//  작성일자 / 작성자 : 정의규 / 20040823
//-----------------------------------------------------------------------------//
HTint							g_iInationalCode;
HTint							g_iInationalType;

//-----------------------------------------------------------------------------//
//  설명 : 웹 커넥트
//  작성일자 / 작성자 : 정의규 / 20040023
//-----------------------------------------------------------------------------//
CHTWebLogIn*					g_poWebLogIn;

//-----------------------------------------------------------------------------//
//  설명 : 빌링 서버 받은 결과
//  작성일자 / 작성자 : 2005.03.31
//-----------------------------------------------------------------------------//
HTbool							g_bReciveBillingServer;

//-----------------------------------------------------------------------------//
//  설명 : 카메라 이동상황을 체크해줌
//  작성일자 / 작성자 : 2005.08.14
//-----------------------------------------------------------------------------//
HTbool							g_bCameraMove;

//-----------------------------------------------------------------------------//
//  설명 : 아쉬람 마크 칼라값,
//  작성일자 / 작성자 : 2005.09.13
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
//  설명 : 스크립트로부터 메시지를 얻어와서 셋팅해준다.
//  작성일자 / 작성자 : 정의규 / 20041018
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
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString(), strInputItem2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
//  설명 : 우리의 숙원사업 ReStart
//	Code : 0:최초로그인, 1:서버셀렉트, 2:Character, 3:GameExit
//  작성일자 / 작성자 : 정의규 / 20041121
//-----------------------------------------------------------------------------//
HTbyte							g_byReStartCode;
HTbyte							g_byReStartButtonCode;

//-----------------------------------------------------------------------------//
//  설명 : 버젼 체크
//  작성일자 / 작성자 : 정의규 / 20050311
//-----------------------------------------------------------------------------//
HTshort							g_snVersionCheck[4];


//-----------------------------------------------------------------------------//
//  설명 : 캐릭터 이름과 길드이름에서 사용해서는 안될 문자
//  작성일자 / 작성자 : 정의규 / 20040023
//-----------------------------------------------------------------------------//
char g_szNotCharAndGuildName[NOTCHARANDGUILDNAME_COUNT][3] = { 
							   "　","ㆄ","ㆅ","ㆆ","ㆇ","ㆈ","ㆉ","ㆊ","ㆋ","ㆌ",
							   "ㆌ","ㆍ","ㆎ","ψ","ω","ω","?", "?", "?", "?", 
							   "?", "?", "┨","┷","┿","┝","┰","┥","┸","╂",
							   "┽","┾","╀","╁","╃","╄","╅","?", "?", "?", 
							   "?", "?", "?", "?", "?", "?", "?", "?", "㎳","㎴",
							   "㎵","㎶","㎷","㎸","㎹","㎀","㎁","㎂","㎃","㎄",
							   "㎺","㎻","㎼","?", "?", "?", "?", "?", "?", "?", 
							   "?", "?", "?", "?", "?", "?", "?", "?", "㉰","㉱",
							   "㉲","㉳","④","⑤","⑥","⑦","⑧","⑧","⑨","⑩",
							   "⑪","⑫","⑬","⑭","⑮","⑮","½","⅓","⅓","⅔",
							   "¼","¾","⅛","⅜","⅝","⅞","æ","đ","ð","⑽",
							   "⑾","⑿","⒀","⒁","⒂","¹","²","³","⁴","ⁿ",
							   "₁","₂","₃","₄"," ", "　","　","갦","걁","걂",
                               "괅","괇","?", "놞","놟","?", "?", "놹","놺","놻",
                               "놼","놽","놾","뇀","놿","뇁","뇂","뇃","뇄","뇅",
                               "뇆","뇇","뇈","뇉","뇊","뇋","뇍","뇎","?", "?",
                               "뇖","뇗","뇘","뇙","뇚","뇛","뇞","뇠","뇡","뇢",
							   "뇣","뇤","뇥","뇦","뇧","?", "?", "뇢","뇗","뇙" };

//	캐릭명이나 길드이름으로 불가한 파일 로딩
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

		// Encoding : XOR을 사용해서 0은 1로 1은 0으로 바꾸는 바보같은 인코딩을 사용한다. 만사가 귀찬다 -_-;
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