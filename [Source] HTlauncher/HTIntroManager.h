//======================================================================
// HTIntroManager.h
// ��Ʈ�λ�Ȳ������ UI������ ���� �� ����
// 2002.    (��)�Ѻ�����Ʈ ���Ӱ����� ���Ǳ�, ����
// 2003. 02 (��)�Ѻ�����Ʈ ���Ӱ����� ����ȣ 
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
		// D : �ִϸ��̼� üũ
		//-----------------------------------------------------------------------------
		HTvoid							HT_vAnimationCheck();

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrCameraUpdate( HTfloat fElapsedTime )
		// D : ī�޶� ��Ʈ��
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrCameraUpdate( HTfloat fElapsedTime );

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrAutoLoginUpdate()
		// D : �ڵ� �α��� üũ
		//-----------------------------------------------------------------------------
		HTvoid							HT_vAutoLoginUpdate();

		///////////////////////////////////////////////////////////////////////////////
		// ����� �޼���
		///////////////////////////////////////////////////////////////////////////////
		//-----------------------------------------------------------------------------
		// HTvoid						HT_vLButtonDown(HTint iPosX, HTint iPosY)
		// D : ���콺 LBUTTON DOWN��
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrLButtonDown(HTint iPosX, HTint iPosY);

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrLButtonUp(HTint iPosX, HTint iPosY)
		// D : ���콺 LBUTTON UP��
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
		//	�޽��� �پ� �ִ� �ð�üũ
		HTvoid							HT_vUpdate_MsgDisplayTimeCheck();
		//	Login
		HTvoid							HT_vUpdate_LoginDelay();

		//	�Է� �޼��� ó��
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
		// ��ư�� ���� ������� �޼���
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
		// D : 3Dȭ������ ��ȯ�ϰ� [ĳ���� ����],[����]���̾˷α׸� �׸���.
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTvoid							HT_vExistCharCreate();
		HTRESULT						HT_hrCharSelect();
		HTvoid							HT_vCharSelect_SetInfo();
		HTRESULT						HT_hrCharNew();
		
		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrSelectCharCreate()
		// D : �ʱ� �����Ҽ� �ִ� ĳ���͵��� �����Ѵ�.
		// R : HT_OK/HT_FAIL
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrNewCharacterCreate( BYTE );
		HTRESULT						HT_hrNewCharacterChangeFace();
		HTvoid							HT_hrExistCharacterCreate( HTint );
		HTvoid							HT_hrExistCharacterEquipItem( HTint iTribe, HTint nCharIndex, DWORD dwItemIndex, DWORD dwLeftItemIndex );

		//-----------------------------------------------------------------------------
		// HTRESULT						HT_hrChakraInit()
		// D : ��ũ���ʱ�ȭ
		//-----------------------------------------------------------------------------
		HTRESULT						HT_hrChakraInit();

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType)
		// D : URL����
		//-----------------------------------------------------------------------------------
		HTvoid							HT_vSetURL();
		//BOOL			GetHttpRequest(LPSTR url,LPSTR recvbuffer,int buffersize);

		//----------------------------------------------------------------------------
		// �޼��� ���
		//----------------------------------------------------------------------------
		HTRESULT		HT_hrSetMessage( HTint idMessage, CHTString* pszMessage );
		HTvoid			HT_vSetParamTextForMessage( HTshort sParam, CHTString* pszParam );
		HTint			HT_iGetCastClass();

		//	������ �˾ƿ���
		HTint			HT_iIntro_GetConnectNum( HTint iGroup, HTint iConnectZone );

		//	ĳ���Ͱ� ���ٶ� ������ �ִ��� üũ
		HTbool			HT_bIsCharInMandara();
		//	���ٶ� ������ ���� �˾ƿ���
		HTbool			HT_bSetMandaraCCUser(HTint iNo);

	public:
		//-----------------------------------------------------------------------------
		// Network �Լ�
		// D : ��Ʈ��ũ �Լ���
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
		//	���� ������ ����
		HTvoid							HT_vEnter_FirstServer();
		//	TantraParam �����ߴ��� Ȯ���ϱ�.
		HTvoid							HT_vCheckTantraParam();
		//	After Login Time Check
		HTvoid							HT_vAfterLoginTimeCheck();

	private:
		HTint							m_iIntroStatus;		// ��Ʈ�λ��� �÷���
		// ���� ���콺�� ��ǥ
		HTvector3						m_MousePt;
		//	Character Total Number
		HTint							m_iCharNum;
		//	D3D Render Sw
		HTbool							m_b3DRender;
		//	UI Render Sw
		HTbool							m_bUIRender;
		//	ī�޶� �󱼱��� ����
		HTbool							m_bFaceZoominSw;
		//	Screen Size
		HTint							m_iScreenWidth;
		HTint							m_iScreenHeight;

		_HT_CHARINFO					m_oSeverChar[_MAX_CHAR_NUM];	// ������ ������ ĳ���� ����

		HTint							m_nNewCharacterModelID;			// �� ĳ������ �� ���̵�
		HTint							m_nNewCharacterTribe;			// �� ĳ������ ����
		BYTE							m_nNewCharacterFace;			// �� ĳ������ ��
		BYTE							m_nNewCharacterHair;			// �� ĳ������ �Ӹ�ī��
		BYTE							m_byNewCharacterTrimurite;		// �� ĳ������ �ֽ�
		CHTString						m_strNewCharacterName;			// �� ĳ������ �̸�
		//	�ִϸ��̼� �ε���
		HTint							m_iAnimationIndex;
		
		
		//	�� ������
		HTfloat							m_fObjectHeight;

		BYTE							m_byCharCreate_ServiceChakraPoint;
		BYTE   							m_byCharCreate_ChakraMuscle;
		BYTE   							m_byCharCreate_ChakraNerve;
		BYTE   							m_byCharCreate_ChakraHeart;
		BYTE							m_byCharCreate_ChakraSoul; 
				
		HTint							m_nExistCharacterModelID[3];	// ���� ĳ���͵��� �� ���̵�
		HTint							m_nExistCharacterNumber;
		HTbool							m_bCharSelectZoomInSw;			// ĳ������ �Ѹ��� ���� �߳�?
		HTint							m_nSelectedCharNo;				// ���õ� ĳ����
		BYTE							m_byConnectType;				// ���� ����
		HTbool							m_bCharDeleteSw;				// ĳ���� ���� ����ġ

		HTdword							m_arrExistCharWearItem[_MAX_CHAR_NUM];		// ���� ĳ���Ͱ� �԰� �ִ� ������ ���̵�
		HTdword							m_arrExistCharWeaponItem[_MAX_CHAR_NUM];	// ���� ĳ���Ͱ� ��� �ִ� ������ ���̵�

		CHTString						m_strMessage;					// ���� ���� �޽���

		//	Zone server connected_For Intro
		HTbool							m_bZoneServerConnected_ForIntro;
		//	Zone server connected_For MainGame
		HTbool							m_bZoneServerConnected_ForMainGame;
		//	Zone server disconnected_For MainGame
		HTbool							m_bZoneServerDisConnected_ForMainGame;
		//	Zone server disconnected_For LoginFaild
		HTbool							m_bZoneServerDisConnected_ForLoginFaild;
		// ������ �̵� ����	0x01:�α�����,0x02:���ΰ��� ���� ����
		BYTE							m_byMoveZoneServerPoint;
		//	������ ������ ���������� üũ
		HTbool							m_bServerDisconnectSw;
		DWORD							m_bServerDisconnectTime;
		//	���� ������ ����
		HTint							m_iCurServerIndex;

		//	����ó�� �Լ�_������ �����û�� ���� ��
		HTbool							m_bErrorCheckSw;				// üũ�� ���� ����
		DWORD							m_dwErrorCheckStartTime;		// ����üũ ��ŸƮ �ð�
		DWORD							m_dwErrorCheckDelayTime;		// �޽��� ��ٷ� �ִ� �ð�

		//	FX ���� ���� ��
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

		//	�̸����� Display�� String
		CHTString						m_strIntroMessage;
		CHTString						m_strIntroMessage_Display;

		HTbool							m_bSlideOn;

		//	ID
		CHTString						m_strID;
		CHTString						m_strSaveID;
		//	��й�ȣ
		CHTString						m_strPassword;
		//	���� ĳ���� �ֹ� ��ȣ_���ڸ�
		CHTString						m_strCharJoominNoFront;
		//	���� ĳ���� �ֹ� ��ȣ_���ڸ�
		CHTString						m_strCharJoominNoBack;
		//	�� ĳ���� �̸�
		CHTString						m_strNewCharName;

		HTint							m_iLowScreen;
		//	ĳ���� ����Ʈ �ܿ��� _USER_MESSAGE_EXIT ��ư�� Ŭ���ߴ��� �ľ�
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
		//	��������Ʈ���� �������� ���� ��û
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
