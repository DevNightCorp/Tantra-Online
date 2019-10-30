//======================================================================
// HTIntroManager.h
// 인트로상황에서의 UI데이터 관리 및 상태
// 2002.    (주)한빛소프트 게임개발팀 정의규, 서명석
// 2003. 02 (주)한빛소프트 게임개발팀 정대호 
//======================================================================
#ifndef _HTINTROMANEGER_H_
#define _HTINTROMANEGER_H_

#include "HTWin32Window.h"
//#include "HTUIUserMsg.h"
#include "HTInterface.h"
#include "HTIntroDef.h"

#define _MAX_CHAR_NUM	3

#define _LOGIN_SERVER	0
#define _ZONE_SERVER1	1
#define _ZONE_SERVER2	2
#define _MAX_CHAR_NUM	3

#define _MANDARA_NUM	3
//#define _ZONENUM_PER_WORLD		20
typedef struct _HT_CHARINFO
{
	HTbool						bSw;
	HTfloat						fHight;
	S_CHARACTER_LIST			sCharInfo;
} _HT_CHARINFO;


class CHTIntroManager
{
	public:
		CHTIntroManager();
		~CHTIntroManager();

	public:
		//-----------------------------------------------------------------------------
		// HTvoid						HT_vAnimationCheck()
		// D : 애니매이션 체크
		//-----------------------------------------------------------------------------
		HTvoid							HT_vAnimationCheck();

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrCameraUpdate( HTfloat fElapsedTime )
		// D : 카메라 컨트롤
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrCameraUpdate( HTfloat fElapsedTime );

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrAutoLoginUpdate()
		// D : 자동 로그인 체크
		//-----------------------------------------------------------------------------
		HTvoid							HT_vAutoLoginUpdate();

		///////////////////////////////////////////////////////////////////////////////
		// 사용자 메세지
		///////////////////////////////////////////////////////////////////////////////
		//-----------------------------------------------------------------------------
		// HTvoid						HT_vLButtonDown(HTint iPosX, HTint iPosY)
		// D : 마우스 LBUTTON DOWN시
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrLButtonDown(HTint iPosX, HTint iPosY);

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrLButtonUp(HTint iPosX, HTint iPosY)
		// D : 마우스 LBUTTON UP시
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrLButtonUp(HTint iPosX, HTint iPosY);

	public:

		//	About Data
		//	Intro Data Clean
		HTRESULT						HT_hrCleanUp();
		//	Init Data Setting and Load Intro UI
		HTvoid							HT_vInitialize();
		//	Create Window
		HTvoid							HT_vIntro_CreateWindow();
		//	Load Intro Map
		HTvoid							HT_vLoadIntroMap();
		//	Load Basic Char Data
		HTvoid							HT_vLoadBasicCharData();
		//	Go Main Game
		HTvoid							HT_vIntro_GoMainGame();

		//	About Update
		//	Update
		HTRESULT						HT_hrUpdate( HTfloat fElapsedTime );
		//	Render
		HTRESULT						HT_hrRender();
		//	Render IME
        HTvoid							HT_vIntroRender_IME();
		//	Server Status Check
		HTvoid							HT_vUpdate_ServerConnectCheck();
		//	Show Window
		HTvoid							HT_vUpdate_ShowWindow();
		//	메시지 뛰어 주는 시간체크
		HTvoid							HT_vUpdate_MsgDisplayTimeCheck();
		//	Login
		HTvoid							HT_vUpdate_LoginDelay();

		//	입력 메세지 처리
		//	Login Box
		static void						HT_hrIntro_InputCheckForLogin(int iAction, int iTarget, int iTargetID);
		//	Server Select
		static void						HT_hrIntro_InputCheckForServerSelect(int iAction, int iTarget, int iTargetID);
		//	Character Info
		static void						HT_hrIntro_InputCheckForCharInfo(int iAction, int iTarget, int iTargetID);
		//	Character Create
		static void						HT_hrIntro_InputCheckForCharCreate(int iAction, int iTarget, int iTargetID);
		//	JuminNo
		static void						HT_hrIntro_InputCheckForJuminNo(int iAction, int iTarget, int iTargetID);
		//	Top Menu
		static void						HT_hrIntro_InputCheckForTopMenu(int iAction, int iTarget, int iTargetID);
		//	3 Mandara Village
		static void						HT_hrIntro_InputCheckFor3MandaraVillage(int iAction, int iTarget, int iTargetID);

		//	Save ID
		HTvoid							HT_vIntro_SaveID();
		//	Load Id
		HTvoid							HT_vIntro_LoadID();

		//	Set Show Window
		HTvoid							HT_vIntro_SetShowWindow( HTint iWinNo, HTdword dwDelayTime );
		//	About Message
		//	Set Show Message
		HTvoid							HT_vIntro_SetShowMessage( CHTString strMsg, HTdword dwDelayTime );
		//	Set Hide Message
		HTvoid							HT_vIntro_SetHideMessage();

		//-----------------------------------------------------------------------------
		// 버튼에 따른 사용자의 메세지
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrUserMsgCancel();
		HTRESULT						HT_hrUserMsgOK();
		HTRESULT						HT_hrUserMsgNewChar();

		HTRESULT						HT_hrUserMsgNewCharSelect(HTint iMsg);
		HTRESULT						HT_hrUserMsgNewCharServiceChakra( HTint iButtonNo );
		HTRESULT						HT_hrUserMsgNewCharFace(HTint iMsg);
		HTRESULT						HT_hrUserMsgNewCharHair(HTint iMsg);

		HTvoid							HT_hrUserMsgNewCharSelect_CharInfo( HTint, HTint, HTbool bRadioInit = HT_TRUE);

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrCharSelect()
		// D : 3D화면으로 전환하고 [캐릭터 선택],[정보]다이알로그를 그린다.
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTvoid							HT_vExistCharCreate();
		HTRESULT						HT_hrCharSelect();
		HTvoid							HT_vCharSelect_SetInfo();
		HTRESULT						HT_hrCharNew();
		
		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrSelectCharCreate()
		// D : 초기 선택할수 있는 캐릭터들을 생성한다.
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrNewCharacterCreate( BYTE );
		HTRESULT						HT_hrNewCharacterChangeFace();
		HTvoid							HT_hrExistCharacterCreate( HTint );
		HTvoid							HT_hrExistCharacterEquipItem( HTint iTribe, HTint nCharIndex, DWORD dwItemIndex, DWORD dwLeftItemIndex );

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrChakraInit()
		// D : 차크라초기화
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrChakraInit();

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType)
		// D : URL설정
		//-----------------------------------------------------------------------------------
		HTvoid							HT_vSetURL();
		//BOOL			GetHttpRequest(LPSTR url,LPSTR recvbuffer,int buffersize);

		//----------------------------------------------------------------------------
		// 메세지 출력
		//----------------------------------------------------------------------------
		HTRESULT		HT_hrSetMessage( HTint idMessage, CHTString* pszMessage );
		HTvoid			HT_vSetParamTextForMessage( HTshort sParam, CHTString* pszParam );
		HTint			HT_iGetCastClass();

		//	동접자 알아오기
		HTint			HT_iIntro_GetConnectNum( HTint iGroup, HTint iConnectZone );

		//	캐릭터가 만다라 마을에 있는지 체크
		HTbool			HT_bIsCharInMandara();
		//	만다라 마을의 동접 알아오기
		HTbool			HT_bSetMandaraCCUser(HTint iNo);

	public:
		//-----------------------------------------------------------------------------
		// Network 함수
		// D : 네트워크 함수들
		// R : HT_void
		//-----------------------------------------------------------------------------
		HTvoid							HT_vCSP_Request_LOGIN();
		HTvoid							HT_vSCP_RESP_LOGIN();
		HTvoid							HT_vCSP_Request_CHAR_LOGOUT();
		HTvoid							HT_vSCP_RESP_CHAR_LOGOUT();
		HTvoid							HT_vSCP_RESP_WORLD_LIST();
		HTvoid							HT_vCSP_Request_MOVE_ZONE_SERVER( BYTE byMoveZoneServerPoint );
		HTvoid							HT_vSCP_RESP_MOVE_ZONE_SERVER( PS_SCP_RESP_MOVE_ZONE_SERVER );
		HTvoid							HT_vCSP_Request_CHAR_LIST();
		HTvoid							HT_vSCP_RESP_CHAR_LIST( char* pData );
		HTvoid							HT_vCSP_Request_CHAR_CREATE();
		HTvoid							HT_vCSP_RESP_CHAR_CREATE( PS_SCP_RESP_CHAR_CREATE );
		HTvoid							HT_vCSP_Request_CHAR_REMOVE();
		HTvoid							HT_vCSP_RESP_CHAR_REMOVE( PS_SCP_RESP_CHAR_REMOVE );
		HTvoid							HT_vCSP_Request_CHAR_SELECT();
		HTvoid							HT_vEnter_MainGame();
		HTvoid							HT_vUpdate_DisconnectServer();
		//	최초 서버에 접속
		HTvoid							HT_vEnter_FirstServer();
		//	TantraParam 변조했는지 확인하기.
		HTvoid							HT_vCheckTantraParam();
		//	After Login Time Check
		HTvoid							HT_vAfterLoginTimeCheck();

	private:
		HTint							m_iIntroStatus;		// 인트로상태 플래그
		// 현재 마우스의 좌표
		HTvector3						m_MousePt;
		//	Character Total Number
		HTint							m_iCharNum;
		//	D3D Render Sw
		HTbool							m_b3DRender;
		//	UI Render Sw
		HTbool							m_bUIRender;
		//	카메라 얼굴까지 줌인
		HTbool							m_bFaceZoominSw;
		//	Screen Size
		HTint							m_iScreenWidth;
		HTint							m_iScreenHeight;

		_HT_CHARINFO					m_oSeverChar[_MAX_CHAR_NUM];	// 서버에 생성된 캐릭터 정보

		HTint							m_nNewCharacterModelID;			// 새 캐릭터의 모델 아이디
		HTint							m_nNewCharacterTribe;			// 새 캐릭터의 종족
		BYTE							m_nNewCharacterFace;			// 새 캐릭터의 얼굴
		BYTE							m_nNewCharacterHair;			// 새 캐릭터의 머리카락
		BYTE							m_byNewCharacterTrimurite;		// 새 캐릭터의 주신
		CHTString						m_strNewCharacterName;			// 새 캐릭터의 이름
		//	애니매이션 인덱스
		HTint							m_iAnimationIndex;
		
		
		//	모델 사이즈
		HTfloat							m_fObjectHeight;

		BYTE							m_byCharCreate_ServiceChakraPoint;
		BYTE   							m_byCharCreate_ChakraMuscle;
		BYTE   							m_byCharCreate_ChakraNerve;
		BYTE   							m_byCharCreate_ChakraHeart;
		BYTE							m_byCharCreate_ChakraSoul; 
				
		HTint							m_nExistCharacterModelID[3];	// 기존 캐릭터들의 모델 아이디
		HTint							m_nExistCharacterNumber;
		HTbool							m_bCharSelectZoomInSw;			// 캐릭터중 한명을 줌인 했냐?
		HTint							m_nSelectedCharNo;				// 선택된 캐릭터
		BYTE							m_byConnectType;				// 접속 유형
		HTbool							m_bCharDeleteSw;				// 캐릭터 삭제 스위치

		HTdword							m_arrExistCharWearItem[_MAX_CHAR_NUM];		// 기존 캐릭터가 입고 있는 아이템 아이디
		HTdword							m_arrExistCharWeaponItem[_MAX_CHAR_NUM];	// 기존 캐릭터가 들고 있는 아이템 아이디

		CHTString						m_strMessage;					// 각종 에러 메시지

		//	Zone server connected_For Intro
		HTbool							m_bZoneServerConnected_ForIntro;
		//	Zone server connected_For MainGame
		HTbool							m_bZoneServerConnected_ForMainGame;
		//	Zone server disconnected_For MainGame
		HTbool							m_bZoneServerDisConnected_ForMainGame;
		//	Zone server disconnected_For LoginFaild
		HTbool							m_bZoneServerDisConnected_ForLoginFaild;
		// 존서버 이동 시점	0x01:로그인후,0x02:메인게임 들어가기 직전
		BYTE							m_byMoveZoneServerPoint;
		//	서버와 연결이 끊어졌을때 체크
		HTbool							m_bServerDisconnectSw;
		DWORD							m_bServerDisconnectTime;
		//	현재 접속할 서버
		HTint							m_iCurServerIndex;

		//	에러처리 함수_서버의 응답요청이 없을 때
		HTbool							m_bErrorCheckSw;				// 체크를 할지 선택
		DWORD							m_dwErrorCheckStartTime;		// 에러체크 스타트 시간
		DWORD							m_dwErrorCheckDelayTime;		// 메시지 기다려 주는 시간

		//	FX 나도 뭔지 모름
		struct HTIntroBackFX
		{
			HTIntroBackFX ();
			~HTIntroBackFX ();


			HTRESULT	HT_hrBeginFX( HTvector3& vecPos );
			HTRESULT	HT_hrStopFX();

		private:
			HTint m_idFX;
			HTint m_idNullModel;
		};

		HTIntroBackFX					m_IntroBackFX;
		//CHTWebLogIn*					m_poWebLogIn;
		HTint							m_iMandaraCCUserNum[_MANDARA_NUM];

		//	이름난에 Display용 String
		CHTString						m_strIntroMessage;
		CHTString						m_strIntroMessage_Display;

		HTbool							m_bSlideOn;

		//	ID
		CHTString						m_strID;
		CHTString						m_strSaveID;
		//	비밀번호
		CHTString						m_strPassword;
		//	지울 캐릭터 주민 번호_앞자리
		CHTString						m_strCharJoominNoFront;
		//	지울 캐릭터 주민 번호_뒷자리
		CHTString						m_strCharJoominNoBack;
		//	새 캐릭터 이름
		CHTString						m_strNewCharName;

		HTint							m_iLowScreen;
		//	캐릭터 셀렉트 단에서 _USER_MESSAGE_EXIT 버튼을 클릭했는지 파악
		HTbool							m_bIntro_User_message_Exit;
		//	For Render Logo
		HTbool							m_bForRenderLogo;
		//	For Render GoMainGame
		HTbool							m_bForRenderGoMainGame;
		//	About Show window
		HTint							m_iShowWinNo;
		HTdword							m_dwShowWinStartTime;
		HTdword							m_dwShowWinDelayTime;
		//	About Message
		CHTString						m_strMeg;
		HTbool							m_bShowMsg;
		HTdword							m_dwShowMsgTime;
		HTdword							m_dwShowMsgStartTime;
		//	About Otheer Object ID Login
		HTint							m_iNorthImperial;
		HTbool							m_bLoginDelay;
		HTdword							m_dwLoginStartTime;
		//	Mob
		HTint							m_iMobForIntro[2];
		DWORD							m_dwChangeAniMobTime[2];
		//	ServerSelect No
		HTint							m_iServerSelectNo;
		//	서버셀렉트에서 존서버에 접속 요청
		HTbool							m_bReqConnectServerInSerSel;
		//	FX of Login Screen
		HTint							m_iFXID1OfLogin;
		HTint							m_iFXID2OfLogin;
		HTint							m_iNullModel1OfLogin;
		HTint							m_iNullModel2OfLogin;
		//	Load CharacterData Sequence
		HTint							m_iLoadCharDataSequence;
		//	For Render Character load
		HTbool							m_bForRenderCharacterData;
		//	Stop Mob Animation
		HTbool							m_bStopMobAnimationSw;
		//	Save ID
		HTbool							m_bIntro_SaveID;
		//	After Login Time Check
		HTdword							m_dwIntro_LoginTimeCheck;
};

#endif
