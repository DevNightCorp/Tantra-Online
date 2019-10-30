//======================================================================
// CHTChatting.h
// ä�� ���� �޽��� ����
// (��)�Ѻ�����Ʈ ���Ӱ����� ���Ǳ�		.......... �����ۼ�
// (��)�Ѻ�����Ʈ ���Ӱ����� ����ȣ		2002.09.13 �߰�/����
// (��)�Ѻ�����Ʈ ���Ӱ����� ����		2002.10.22 �߰�/����20021022Tenma
//======================================================================

#ifndef __HTCHATTING_H__
#define __HTCHATTING_H__

// �迭�� ����Ǵ� �޽��� Ÿ��
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

// �迭�� ����Ǵ� �޽��� Ÿ��
#define HISTORY_MESSAGE_TYPE_NORMAL			10
#define HISTORY_MESSAGE_TYPE_NOTIFY			20
#define HISTORY_MESSAGE_TYPE_ITEM			30
#define HISTORY_MESSAGE_TYPE_ATTACK			40
#define HISTORY_MESSAGE_TYPE_ATTACKED		50
#define HISTORY_MESSAGE_TYPE_QUEST			60
#define HISTORY_MESSAGE_TYPE_PARTY			70
#define HISTORY_MESSAGE_TYPE_PRANA			80	// 2003.3.22 ����
#define HISTORY_MESSAGE_TYPE_SKILL			90	// 2003.3.26 ����
#define HISTORY_MESSAGE_TYPE_CHAKRA			100
#define	HISTORY_MESSAGE_TYPE_BRAMAN			110
#define HISTORY_MESSAGE_TYPE_ETC			999
#define HISTORY_MESSAGE_TYPE_ERROR			-1

// �� ����Ʈ�� �ִ� ���� ����(���� ������� �ʴ´�.)
#define _MAX_SAVED_MESSAGE_NUM				105
#define _MAX_SAVED_MINIMESSAGE_NUM			116
#define _MAX_SAVED_HISTORY_NUM				105
#define _MAX_SAVED_NAMELIST_NUM				10
// (���� ���� �ȴ�.)
//#define _MAX_SAVED_NAMELIST_NUM				10
//#define _MAX_SAVED_CHAT_MESSAGE_HISTORY_NUM 30

// IME�� ���¸� �����Ѵ�. 
// ä���� �����ϸ� ���ӿ��� ��� ���� ��尡 ���̰� �ǹǷ�
// ä��â�� ����� ��쿡 üũ�Ͽ� IME�� �Է� ��带 ��ȯ�Ѵ�.
// �⺻���� IME_STATUS_KOREAN �� ó���� �ѱ۸�尡 �ȴ�.
#define IME_STATUS_ENGLISH		0
#define IME_STATUS_KOREAN		1

// ä�� �α׸� �����Ҷ� �ð��� ǥ���ϴ� ���ڿ��� �ִ� ����
#define MAX_TIMESTAMP_SIZE 128

//	������ ���� ����
#define OPENMESSAGE_MAX_COUNT	20
//	ä�÷α� �������
#define CHATLOG_MAX_COUNT		1000
//	������ �������
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
	CHTString	strSenChar;					//	������ �޽��� �������
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
		//	�Է� �޼��� ó��
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
		// D : �����丮 ���
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetHistoryFunction( WPARAM wParam );
        
		//-------------------------------------------------------------------------------
		// HTvoid HT_vReceiveData_xxxx()
		// D : �����κ��� �ش� �޽����� �����͸� �޴´�.
		//-------------------------------------------------------------------------------
		HTvoid						HT_vReceiveData_Normal( PS_SCP_NOTIFY_CHAT );
		HTvoid						HT_vReceiveData_Whisper( PS_SCP_NOTIFY_WHISPER_CHAT );
		HTvoid						HT_vReceiveData_Group( MSG_Chat* );
		HTvoid						HT_vReceiveData_Notify( MSG_Broadcast* );
		HTvoid						HT_vReceiveData_History( PS_SCP_RESP_CHAR_HISTORY );

		//-------------------------------------------------------------------------------
		// HTvoid HT_vReceiveDataResult_xxxx()
		// D : ������ �۽��� �޽����� ����� �޴´�.
		//-------------------------------------------------------------------------------
		//HTvoid						HT_vReceiveDataResult_Normal( PS_SCP_RESP_NORMAL_CHAT );
		HTvoid						HT_vReceiveDataResult_Whisper( PS_SCP_RESP_WHISPER_CHAT );
		//HTvoid						HT_vReceiveDataResult_Shout( PS_SCP_RESP_SHOUT_CHAT );	
		//HTvoid						HT_vReceiveDataResult_Guild( PS_SCP_RESP_GUILD_CHAT );	

		//-------------------------------------------------------------------------------
		// HTvoid HT_vSetData_xxxxx()
		// D : �Է� �� �޽����� �ؼ��Ͽ� ������ ������.
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

		// Add Comment by 20021025Tenma ä��â�� ���¸� ��Ÿ���� ����.
		// Input On
		HTbool						m_bChatStatusOn;
		
		HTint						m_IMEStatus;
		// Add by 20021202Tenma ä�ý��� ��/�� ��带 �����Ѵ�.
		HTint						HT_iGetIMEMode();

		// �α׸� ���� �Ǵ� ���� �Ѵ�.
		HTvoid						StartStopLogging();

		// ��ȭ ��븦 ���Ѵ�.
		HTvoid						HT_vAddName( HTint type, CHTString strName );

		//-------------------------------------------------------------------------------
		// HTvoid HT_vSaveHistory(CHTString sMsg)
		// D : �����丮 ����
		//-------------------------------------------------------------------------------
		HTvoid
		HT_vSaveHistory(HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground);

		//-------------------------------------------------------------------------------
		// HTvoid HT_vChatting_SetWisper( CHTString )
		// D : �ܺο��� �ӼӸ� ���¸� �����Ѵ�.
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetWisper( CHTString );

		//-------------------------------------------------------------------------------
		// HTvoid						HT_hrSelectChar();
		// D : ä�ð��� ĳ���͸� �����Ѵ�.
		//-------------------------------------------------------------------------------
		CHTString					HT_vChatting_GetChatMsg()		{	return m_strChatMessage;	};

		//-------------------------------------------------------------------------------
		// HTvoid						HT_hrSelectChar();
		// D : ���������� �ӼӸ� ���� ���
		//-------------------------------------------------------------------------------
		HTvoid						HT_vChatting_SetLastSendWisper();

	private:
		//-------------------------------------------------------------------------------
		// HTvoid HT_vCHTChatting_TextInputCurFlash()
		// D : �Է�Ŀ�� �÷���
		//-------------------------------------------------------------------------------
		HTvoid						HT_vTextCursorFlash();


		//-------------------------------------------------------------------------------
		// HTvoid HT_vSaveChatMsg(CHTString sMsg)
		// D : �޼��� ����
		//-------------------------------------------------------------------------------
		HTvoid
		HT_vSaveChatMsg(HTint iType, CHTString sMsg, HT_COLOR colorText, HT_COLOR colorBackground);

		//-------------------------------------------------------------------------------
		// ...
		// D : �ӼӸ� ��ȭ��� �����ϴ� ��ȭ���� ��Ʈ��
		//-------------------------------------------------------------------------------
		HTvoid						HT_Whisper_Dlg_Check();

		//-------------------------------------------------------------------------------
		// �޼��� ���
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetMessage( HTint idMessage, CHTString* pszMessage );
		HTvoid			HT_vChatting_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	public:
		//-------------------------------------------------------------------------------
		// HTvoid						HT_vArrangeSavedChatMsg(CHTString, HT_COLOR);
		// HTvoid						HT_vArrangeSavedHistory(CHTString, HT_COLOR);
		// D : ����� �޼����� �����丮 ����
		//-------------------------------------------------------------------------------
		HTvoid						HT_vArrangeSavedChatMsg(HTint iType, CHTString, HT_COLOR);
		HTvoid						HT_vArrangeSavedHistory(CHTString, HT_COLOR);

        //-------------------------------------------------------------------------------
		//	������
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetOpenMessageItem( HTbyte byMsgType, HTint iItemIndex, HTbyte byItemKeyID );
		HTvoid			HT_vChatting_DelOpenMessageItemBox();
		HTvoid			HT_vChatting_NetworkSendOpenMessage();
		HTvoid			HT_vChatting_RenderOpenMsg( HTfloat fElapsedTime );
		HTRESULT		HT_hrChatting_SetPickOpenMsgWnd( HTPoint pPt );

		//-------------------------------------------------------------------------------
		//	ä�� ��
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetChatBlock( HTbyte byChatBlock );

		//-------------------------------------------------------------------------------
		//	ä�� �α�
		//-------------------------------------------------------------------------------
		HTvoid			HT_vChatting_SetChatLog( HTint iType, CHTString strMsg, HT_COLOR clColor );
		HTvoid			HT_vChatting_SetOpenMeg( CHTString strMsg );
		HTvoid			HT_vChatting_SetTextinChatLog();
		HTvoid			JK_vChatting_ChatLogFile();	//	Write Chat Log File

		//	�۾��� �޽���
        HTvoid			HT_vChatting_WorkingMsg();

	public:
		//	ä�� ������ ��Ÿ��
		HTint						m_iChatWindowStyle;

	private:

		// �޼��� ��¿�
		HTint						m_iMessageVal;
		CHTString					m_szMsgName;	// �޼��� ��¿� �̸�

		// �ӼӸ� ����Ʈ
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

		// ä�� ���� �α��� ���� �÷��� ���� ����ü
		HTbool						m_bLogging;
		FILE*						m_pLogFile;

		// ó�� �ߴ� ���������� ���� Buffer 1000����Ʈ! 20030123Tenma_test
		HTtchar*					m_pNotifyBuffer;

		// Edited by 20021022Tenma
		// �ǹ̸� ��Ȯ�� �ϱ� ���Ͽ� �������� �����Ͽ���.
		// m_cChattingText���� m_c_DisplayingText�� ���� �Ͽ���
		CHTString					m_strChatMessage;
		CHTString					m_strWisperName;
		
		//	���������� �ӼӸ� ���� ���
		CHTString					m_strLastRiciveWisperName;
		//	������ ������
		HTint						m_iOpenMessageItemIndex;
		//	������ ������ ����
		HTbyte						m_byOpenMessageItemType;
		//	Save Recive Msg
		OpenMESSAGE					m_oOpenMessageSave[OPENMESSAGE_MAX_COUNT];
		//	Text Positiion
		HTfloat						m_fOpenTextPosX;
		//	Text Rotate Count
		HTint						m_iOpenRotateCount;
		//	Chatting Block
		HTbool						m_bChat_ChatBlockSw;
		//	/Ż�� 3�ʿ� �ѹ��� ������ �ϱ� ����
		DWORD						m_dwEscapeSaveTime;
		//	��ɾ�
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
		//	��ũ�� ��
		HTint						m_iChat_ScrollChat;
		HTint						m_iChat_ScrollSystem;
		//	ä�� �Է� ���
        HTbool						m_bChat_InputMode;
		//	Open Msg Type
		//	0:����, 1:�ƽ����̸�, 2:������, 3:������ɼ�
		HTbyte						m_byChat_OpenMsgType;
		//	�۾��� �޽��� ī��Ʈ
		HTint						m_iChat_MsgCount;
		//	ä�� ����
		HTbool						m_bChat_ConfigChat[5];

		//	ä�� �α�
		ChatLogStrut				m_oChat_ChatLog[CHATLOG_MAX_COUNT];
		int							m_iChat_ChatLogCount;
		HTbool						m_bChat_ChatLogConfig[6];
		//	������ �޽���
		ChatLogStrut				m_oChat_SaveOpenMsg[OPENMSG_MAX_COUNT];
		int							m_iChat_OpenMsgCount;
};

#endif

