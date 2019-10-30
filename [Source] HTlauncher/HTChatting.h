//======================================================================
// CHTChatting.h
// 채팅 관련 메시지 관리
// (주)한빛소프트 게임개발팀 정의규		.......... 최초작성
// (주)한빛소프트 게임개발팀 정대호		2002.09.13 추가/수정
// (주)한빛소프트 게임개발팀 서명석		2002.10.22 추가/수정20021022Tenma
//======================================================================

#ifndef __HTCHATTING_H__
#define __HTCHATTING_H__

// 배열에 저장되는 메시지 타입
#define CHAT_MESSAGE_TYPE_SYSTEM			0
#define CHAT_MESSAGE_TYPE_NORMAL			10
#define CHAT_MESSAGE_TYPE_WISPER			20
#define CHAT_MESSAGE_TYPE_SHOUT				30
#define CHAT_MESSAGE_TYPE_PARTY				40
#define CHAT_MESSAGE_TYPE_ASHRAM			41
#define CHAT_MESSAGE_TYPE_ALLIANCE			42
#define CHAT_MESSAGE_TYPE_GROUP				50
#define CHAT_MESSAGE_TYPE_ETC				999
#define CHAT_MESSAGE_TYPE_ERROR				-1

// 배열에 저장되는 메시지 타입
#define HISTORY_MESSAGE_TYPE_NORMAL			10
#define HISTORY_MESSAGE_TYPE_NOTIFY			20
#define HISTORY_MESSAGE_TYPE_ITEM			30
#define HISTORY_MESSAGE_TYPE_ATTACK			40
#define HISTORY_MESSAGE_TYPE_ATTACKED		50
#define HISTORY_MESSAGE_TYPE_QUEST			60
#define HISTORY_MESSAGE_TYPE_PARTY			70
#define HISTORY_MESSAGE_TYPE_PRANA			80	// 2003.3.22 선미
#define HISTORY_MESSAGE_TYPE_SKILL			90	// 2003.3.26 선미
#define HISTORY_MESSAGE_TYPE_CHAKRA			100
#define	HISTORY_MESSAGE_TYPE_BRAMAN			110
#define HISTORY_MESSAGE_TYPE_ETC			999
#define HISTORY_MESSAGE_TYPE_ERROR			-1

// 각 리스트의 최대 저장 갯수(현재 적용되지 않는다.)
#define _MAX_SAVED_MESSAGE_NUM				105
#define _MAX_SAVED_MINIMESSAGE_NUM			116
#define _MAX_SAVED_HISTORY_NUM				105
#define _MAX_SAVED_NAMELIST_NUM				10
// (현재 적용 된다.)
//#define _MAX_SAVED_NAMELIST_NUM				10
//#define _MAX_SAVED_CHAT_MESSAGE_HISTORY_NUM 30

// IME의 상태를 저장한다. 
// 채팅을 제외하면 게임에서 모두 영문 모드가 쓰이게 되므로
// 채팅창이 띄워질 경우에 체크하여 IME의 입력 모드를 전환한다.
// 기본값은 IME_STATUS_KOREAN 로 처음에 한글모드가 된다.
#define IME_STATUS_ENGLISH		0
#define IME_STATUS_KOREAN		1

// 채팅 로그를 저장할때 시간을 표시하는 문자열의 최대 길이
#define MAX_TIMESTAMP_SIZE 128

//	전광판 저장 공간
#define OPENMESSAGE_MAX_COUNT	20
//	채팅로그 저장공간
#define CHATLOG_MAX_COUNT		1000
//	전광판 저장공간
#define OPENMSG_MAX_COUNT		100


typedef struct _MESSAGE
{
	HTint		iType;
	CHTString	strMsg;
	HT_COLOR	clrColor;
	CHTString	szTime;
} _MESSAGE;

typedef struct _OpenMESSAGE
{
	HTbool		bExistSw;
	CHTString	strMsg;
	HTbyte		byMsgType;
	CHTString	strSenChar;					//	전광판 메시지 보낸사람
	CHTString	szTime;
} OpenMESSAGE;

typedef struct _ChatLog
{
	HTint		iType;
	char		szMsg[128];
	HT_COLOR	clrColor;
	CHTString	szTime;
} ChatLogStrut;



class CHTChatting
{
	public:
		CHTChatting();
		~CHTChatting();
		HTvoid						HT_vChatting_Init();
		HTvoid						HT_vChatting_CleanUp();

		//	Create Window
		HTvoid						HT_vChatting_CreateWindow();
		//	Read Parse Msg
		HTvoid						HT_vChatting_ReadParseMsg();

	public:
		//	입력 메세지 처리
		//	FromChatWnd
		static void					HT_vChatting_InputCheckForChatWnd(int iAction, int iTarget, int iTargetID);
		//	FromOpenMessage
		static void					HT_vChatting_InputCheckForOpenMsg(int iAction, int iTarget, int iTargetID);
		//	FromWhisperList
		static void					HT_vChatting_InputCheckForWhisperList(int iAction, int iTarget, int iTargetID);
		//	FromChatConfig
		static void					HT_vChatting_InputCheckForChatConfig(int iAction, int iTarget, int iTargetID);
		//	FromChatLog1
		static void					HT_vChatting_InputCheckForChatLog(int iAction, int iTarget, int iTargetID);
		//	FromChatConfig
		static void					HT_vChatting_InputCheckForChatLogConfig(int iAction, int iTarget, int iTargetID);

		//	Change Chat Wnd
		HTvoid						HT_vChatting_ChangeChatWnd();

		//	About Setting
		//	Set Parse Msg
		HTvoid						HT_vParseMsg( CHTString strCommand, CHTString strMessage );
		//	Set Focus On
		HTvoid						HT_vChatting_SetFocusOn();
		//	Set Focus Off
		HTvoid						HT_vChatting_SetFocusOff( HTbool bTrue );
		//	Set Chat Text List
		HTvoid						HT_vChatting_SetChatTextList();
		//	Set System Text List
		HTvoid						HT_vChatting_SetSystemTextList();

		//	About Get Data
		//	Get Chat Edit Focus
		HTbool						HT_bChatting_GetChatEditFocus();

		//-------------------------------------------------------------------------------
		// HTbool HT_vChatting_SetHistoryFunction( WPARAM wParam )
		// D : 히스토리 기능
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetHistoryFunction( WPARAM wParam );
        
		//-------------------------------------------------------------------------------
		// HTvoid HT_vReceiveData_xxxx()
		// D : 서버로부터 해당 메시지의 데이터를 받는다.
		//-------------------------------------------------------------------------------
		HTvoid						HT_vReceiveData_Normal( PS_SCP_NOTIFY_CHAT );
		HTvoid						HT_vReceiveData_Whisper( PS_SCP_NOTIFY_WHISPER_CHAT );
		HTvoid						HT_vReceiveData_Group( MSG_Chat* );
		HTvoid						HT_vReceiveData_Notify( MSG_Broadcast* );
		HTvoid						HT_vReceiveData_History( PS_SCP_RESP_CHAR_HISTORY );

		//-------------------------------------------------------------------------------
		// HTvoid HT_vReceiveDataResult_xxxx()
		// D : 서버로 송신한 메시지의 결과를 받는다.
		//-------------------------------------------------------------------------------
		//HTvoid						HT_vReceiveDataResult_Normal( PS_SCP_RESP_NORMAL_CHAT );
		HTvoid						HT_vReceiveDataResult_Whisper( PS_SCP_RESP_WHISPER_CHAT );
		//HTvoid						HT_vReceiveDataResult_Shout( PS_SCP_RESP_SHOUT_CHAT );	
		//HTvoid						HT_vReceiveDataResult_Guild( PS_SCP_RESP_GUILD_CHAT );	

		//-------------------------------------------------------------------------------
		// HTvoid HT_vSetData_xxxxx()
		// D : 입력 된 메시지를 해석하여 서버로 보낸다.
		//-------------------------------------------------------------------------------
		HTvoid						HT_vSetData_Normal(CHTString sChatMsg);
		HTvoid						HT_vSetData_Whisper( CHTString token, CHTString sChatMsg);
		HTvoid						HT_vSetData_Shout(CHTString sChatMsg);
		HTvoid						HT_vSetData_Group(CHTString sChatMsg, HTbyte byMsgType );
		//HTvoid					HT_vSetData_Guild(CHTString sChatMsg);
		HTvoid						HT_vSetData_AddressBook(CHTString sChatMsg);
		HTvoid						HT_vSetData_NotifyMessage(CHTString sChatMsg);
		HTvoid						HT_vSetData_GlobalNotifyMessage(CHTString sChatMsg);
		HTvoid						HT_vSetData_CharacterLocation( HTtchar* pcharName );
		HTRESULT					NotifyFromFile( CHTString strFilename );
		HTvoid						HT_vSetData_ReqCharInfo( CHTString strCharname );
		HTvoid						HT_vSetData_ReqCharClose( CHTString strCharname );

		// Add Comment by 20021025Tenma 채팅창의 상태를 나타내는 변수.
		// Input On
		HTbool						m_bChatStatusOn;
		
		HTint						m_IMEStatus;
		// Add by 20021202Tenma 채팅시의 한/영 모드를 결정한다.
		HTint						HT_iGetIMEMode();

		// 로그를 시작 또는 중지 한다.
		HTvoid						StartStopLogging();

		// 대화 상대를 더한다.
		HTvoid						HT_vAddName( HTint type, CHTString strName );

		//-------------------------------------------------------------------------------
		// HTvoid HT_vSaveHistory(CHTString sMsg)
		// D : 히스토리 저장
		//-------------------------------------------------------------------------------
		HTvoid
		HT_vSaveHistory(HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground);

		//-------------------------------------------------------------------------------
		// HTvoid HT_vChatting_SetWisper( CHTString )
		// D : 외부에서 귓속말 상태를 설정한다.
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetWisper( CHTString );

		//-------------------------------------------------------------------------------
		// HTvoid						HT_hrSelectChar();
		// D : 채팅관련 캐릭터를 설정한다.
		//-------------------------------------------------------------------------------
		CHTString					HT_vChatting_GetChatMsg()		{	return m_strChatMessage;	};

		//-------------------------------------------------------------------------------
		// HTvoid						HT_hrSelectChar();
		// D : 마지막으로 귓속말 보낸 상대
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetLastSendWisper();

	private:
		//-------------------------------------------------------------------------------
		// HTvoid HT_vCHTChatting_TextInputCurFlash()
		// D : 입력커서 플래쉬
		//-------------------------------------------------------------------------------
		HTvoid						HT_vTextCursorFlash();


		//-------------------------------------------------------------------------------
		// HTvoid HT_vSaveChatMsg(CHTString sMsg)
		// D : 메세지 저장
		//-------------------------------------------------------------------------------
		HTvoid
		HT_vSaveChatMsg(HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground);

		//-------------------------------------------------------------------------------
		// ...
		// D : 귓속말 대화상대 저장하는 대화상자 컨트롤
		//-------------------------------------------------------------------------------
		HTvoid						HT_Whisper_Dlg_Check();

		//-------------------------------------------------------------------------------
		// 메세지 출력
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetMessage( HTint idMessage, CHTString* pszMessage );
		HTvoid			HT_vChatting_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	public:
		//-------------------------------------------------------------------------------
		// HTvoid						HT_vArrangeSavedChatMsg(CHTString, HT_COLOR);
		// HTvoid						HT_vArrangeSavedHistory(CHTString, HT_COLOR);
		// D : 저장된 메세지와 히스토리 정렬
		//-------------------------------------------------------------------------------
		HTvoid						HT_vArrangeSavedChatMsg(HTint iType, CHTString, HT_COLOR);
		HTvoid						HT_vArrangeSavedHistory(CHTString, HT_COLOR);

        //-------------------------------------------------------------------------------
		//	전광판
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetOpenMessageItem( HTbyte byMsgType, HTint iItemIndex, HTbyte byItemKeyID );
		HTvoid			HT_vChatting_DelOpenMessageItemBox();
		HTvoid			HT_vChatting_NetworkSendOpenMessage();
		HTvoid			HT_vChatting_RenderOpenMsg( HTfloat fElapsedTime );
		HTRESULT		HT_hrChatting_SetPickOpenMsgWnd( HTPoint pPt );

		//-------------------------------------------------------------------------------
		//	채팅 블럭
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetChatBlock( HTbyte byChatBlock );

		//-------------------------------------------------------------------------------
		//	채팅 로그
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetChatLog( HTint iType, CHTString strMsg, HT_COLOR clColor );
		HTvoid			HT_vChatting_SetOpenMeg( CHTString strMsg );
		HTvoid			HT_vChatting_SetTextinChatLog();
		HTvoid			JK_vChatting_ChatLogFile();	//	Write Chat Log File

		//	작업중 메시지
        HTvoid			HT_vChatting_WorkingMsg();

	public:
		//	채팅 윈도우 스타일
		HTint						m_iChatWindowStyle;

	private:

		// 메세지 출력용
		HTint						m_iMessageVal;
		CHTString					m_szMsgName;	// 메세지 출력용 이름

		// 귓속말 리스트
		HTbool						m_bNameListActive;
		HTint						m_iNameListNum;
		CHTString					m_strWhisperNameList[_MAX_SAVED_NAMELIST_NUM];
		int							m_iChat_WhisperReadIndex;

		_MESSAGE					m_oSavedChatMsg[_MAX_SAVED_MESSAGE_NUM];
		_MESSAGE					m_oSavedHistory[_MAX_SAVED_HISTORY_NUM];
		CHTString					m_strNameList[_MAX_SAVED_NAMELIST_NUM];

		//	History Fucntion
		CHTString					m_strChat_HistoryMsg[10];
		int							m_iChat_HistroyWriteIndex;
		int							m_iChat_HistroyReadIndex;

		// 채팅 내용 로깅을 위한 플랙과 파일 구조체
		HTbool						m_bLogging;
		FILE*						m_pLogFile;

		// 처음 뜨는 공지사항을 담을 Buffer 1000바이트! 20030123Tenma_test
		HTtchar*					m_pNotifyBuffer;

		// Edited by 20021022Tenma
		// 의미를 명확히 하기 위하여 변수명을 수정하였음.
		// m_cChattingText에서 m_c_DisplayingText로 수정 하였음
		CHTString					m_strChatMessage;
		CHTString					m_strWisperName;
		
		//	마지막으로 귓속말 보낸 상대
		CHTString					m_strLastRiciveWisperName;
		//	전광판 아이템
		HTint						m_iOpenMessageItemIndex;
		//	전광판 아이템 종류
		HTbyte						m_byOpenMessageItemType;
		//	Save Recive Msg
		OpenMESSAGE					m_oOpenMessageSave[OPENMESSAGE_MAX_COUNT];
		//	Text Positiion
		HTfloat						m_fOpenTextPosX;
		//	Text Rotate Count
		HTint						m_iOpenRotateCount;
		//	Chatting Block
		HTbool						m_bChat_ChatBlockSw;
		//	/탈출 3초에 한번씩 보내게 하기 위해
		DWORD						m_dwEscapeSaveTime;
		//	명령어
		CHTString szWhole, szAshuram;
		CHTString szMsgWhole, szMsgWhisper, szMsgAddress, szMsgAshuram, szMsgKick, szMsgCommandWin;
		CHTString szMsgGuildMark, szMsgTrimuritiMark, szMsgInvisible;
		CHTString szMsgWarp, szMsgMove, szMsgNotice, szMsgWholeNotice, szMsgAssistant;
		CHTString szMsgShout, szMsgParty, szMsgGuildNotice, szMsgGuildGrade;
		CHTString szParty, szTrade, szEmerge;
		CHTString szMsgAS, szMsgAS2, szMsgASCancel, szMsgASCancel2, szMsgASCheck, szMsgASCheck2;
		CHTString szMsgShoutPart, szMsgPartyPart, szMsgAshuramPart, szMsgWholePart, szMsgWhisperPart;
		CHTString szMsgDebugMode, szMsgBroadcastMode, szMsgEngineCamera, szGoCamera, szShowCursor;
		CHTString szMsgDuel,szMsgChatRoom;
		CHTString szMsgAshuramJoin, szMsgAshuramGuildJoin, szMsgAshuramGuildLeave, szMsgAshuramAllince1, szMsgAshuramAllince2;
		//	스크롤 값
		HTint						m_iChat_ScrollChat;
		HTint						m_iChat_ScrollSystem;
		//	채팅 입력 모드
        HTbool						m_bChat_InputMode;
		//	Open Msg Type
		//	0:없음, 1:아쉬람이름, 2:전광판, 3:전투명령서
		HTbyte						m_byChat_OpenMsgType;
		//	작업중 메시지 카운트
		HTint						m_iChat_MsgCount;
		//	채팅 설정
		HTbool						m_bChat_ConfigChat[5];

		//	채팅 로그
		ChatLogStrut				m_oChat_ChatLog[CHATLOG_MAX_COUNT];
		int							m_iChat_ChatLogCount;
		HTbool						m_bChat_ChatLogConfig[6];
		//	전광판 메시지
		ChatLogStrut				m_oChat_SaveOpenMsg[OPENMSG_MAX_COUNT];
		int							m_iChat_OpenMsgCount;
};

#endif

