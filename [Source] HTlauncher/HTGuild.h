#pragma once


#define 	GUILDTYPE_NONE						0			//	��� ȸ�� �ƴ�
#define 	GUILDTYPE_GUILDMASTER				1			//	��� ��
#define 	GUILDTYPE_GUILDMEMBER				2			//	��� ���

#define 	GUILDTYPE_CONFIRM_NONE				0			//	�ƹ� �ܰ� �ƴ�
#define 	GUILDTYPE_CONFIRM_CREATE			1			//	â����û
#define 	GUILDTYPE_CONFIRM_JOIN				2			//	���Կ�û�� ��
#define 	GUILDTYPE_CONFIRM_SECEDE			4			//	Ż���û
#define 	GUILDTYPE_CONFIRM_DESTROY			5			//	��ü��û
#define 	GUILDTYPE_CONFIRM_JOINNOTIFY		6			//	������ �˸���.
#define 	GUILDTYPE_CONFIRM_EXPEL				7			//	�����Ų��.
#define 	GUILDTYPE_CONFIRM_MAKEBLOG			8			//	Ȩ�� ����
#define 	GUILDTYPE_CONFIRM_ENTERBLOG			9			//	Ȩ�� ����
#define 	GUILDTYPE_CONFIRM_REQALLIANCE		10			//	���վƽ��� ���Կ�û
#define 	GUILDTYPE_CONFIRM_RECIVEALLIANCE	11			//	���Կ�û ����
#define 	GUILDTYPE_CONFIRM_PERSONALBLOG		12			//	���κ�α�
#define 	GUILDTYPE_CONFIRM_OTHERBLOG			13			//	�������α�
#define 	GUILDTYPE_CONFIRM_PERSONALBOARD		14			//	����������
#define 	GUILDTYPE_CONFIRM_ERROR				99			//	�����޽���



class HTGuild
{
public:
	HTGuild(void);
	~HTGuild(void);

	//	����Ÿ ����
	HTvoid				HT_vGuild_Delete();
	//	�ʱ� ����Ÿ ����
	HTvoid				HT_vGuild_Init();
	//	Create Window
	HTvoid				HT_vGuild_CreateWindow();

	//	�Է� �޼��� ó��
	//	AshramInfo
	static void			HT_vGuild_InputCheckForAshramInfo(int iAction, int iTarget, int iTargetID);
	//	AshramMemberList
	static void			HT_vGuild_InputCheckForAshramMemberList(int iAction, int iTarget, int iTargetID);
	//	AshramCago
	static void			HT_vGuild_InputCheckForAshramCago(int iAction, int iTarget, int iTargetID);
	//	Sanction Ashram Cago
	static void			HT_vGuild_InputCheckForSanctionAshramCago(int iAction, int iTarget, int iTargetID);
	//	SetLevel Ashram Cago
	static void			HT_vGuild_InputCheckForSetLevelAshramCago(int iAction, int iTarget, int iTargetID);
	// �ں� ����â
	static void			HT_vGuild_InputCheckForEmblemSelecting(int iAction, int iTarget, int iTargetID);
	HTvoid				HT_vGuild_DialogBoxDrawTab(int iTabNo);			// �ش� �ܹ�ȣ�� �����츦 �׷��ݴϴ�. (��帶ũ ����â �ں�)
	HTvoid				HT_bGuild_DialogBoxDrawEmblem(int iIndex);		// ������ ������ �Է¹޾� �����쿡 �׷��ݴϴ�. (��帶ũ ����â)
	HTvoid				HT_bGuild_DialogBoxEmblemSelect();				// ���� ���� ó��
	HTint				HT_bGuild_GetDialogBoxEmblemMaxButton();		// ����ó����

	//	��ȭ���� Ȱ��ȭ
	HTvoid				HT_vGuild_DialogBoxActive();
	//	��ȭ���� ��Ȱ��ȭ
	HTvoid				HT_vGuild_DialogBoxAntiActive();
	//	â��
	HTvoid				HT_vGuild_Create();

	//	����
	HTRESULT			HT_vGuild_JoinGuild( HTint );
    
	//	��� �ʱ� ������ �޽��ϴ�.
	HTvoid				HT_vNetWork_SCP_INIT_GUILD( MSG_GuildInfo* );
	//	��� ������ ��û�Ѵ�.
	HTRESULT			HT_hrNetWork_CSP_REQ_CREATE_GUILD( CHTString strAshramName );
	//	�ű� ������ ������ �����鿡�� �����Ѵ�.
	HTvoid				HT_vNetWork_SCP_AddGuildMember( MSG_AddGuildMember* info );
	//	��� ��ü�� ��û�Ѵ�.
	HTvoid				HT_vNetWork_CSP_Remove_GuildMember();
	HTvoid				HT_vNetWork_SCP_RemoveGuildMember( MSG_RemoveGuildMember* );
	//	��� ������ ��û�Ѵ�.
	HTvoid				HT_vNetWork_CSP_REQGuild();
	HTvoid				HT_vNetWork_SCP_REQGuild( MSG_REQGuild* info );
	//	��� ���� ��û ����� ������ �����Ѵ�.
	HTvoid				HT_vNetWork_CSP_CNFGuild();
	//	������ ������
	HTvoid				HT_vNetWork_SCP_GuildMemberin( MSG_GuildMemberin* info );
	//	������ ������ ����
	HTvoid				HT_vNetWork_SCP_GuildMemberout( MSG_GuildMemberout* info );
	//	��帶ũ ����
	HTvoid				HT_vNetWork_CSP_MSG_GuildUpdateMark( HTbyte byCostType );
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdateMark( MSG_GuildUpdateMark* );
	//	��������Ʈ
	HTvoid				HT_vNetWork_CSP_MSG_GuildUpdate( CHTString strMessage );
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdate( MSG_GuildUpdate* );
	//	��� ��� ������Ʈ
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdateMember( MSG_GuildUpdateMember* );
	//	��� ��ŷ ������Ʈ
	HTvoid				HT_vNetWork_CSP_MSG_GuildSetRanking( CHTString strTemp );
	HTvoid				HT_vNetWork_SCP_MSG_GuildSetRanking( MSG_GuildSetRanking* );

	//	���� ����Ʈ ��ȭ���ڿ� ǥ���ϱ�
	HTvoid				HT_vGuild_Display();

	// ��� ��ũ ����â Ȱ��ȭ
	HTvoid				HT_vGuild_AmblemMakeActive();
	//	��� ��ũ ����
	HTvoid				HT_vGuild_SetEmblemID( DWORD dwEmblemID );
	//	��� ��ũ ID ������
	HTint				HT_iGuild_GetEmblemID()	{	return m_dwGuild_EmblemID;	};
	//	��� ��ũ ǥ�� �ϱ� ���ϱ�
	HTvoid				HT_vGuild_EmblemOn();
	HTvoid				HT_vGuild_EmblemOff();
	//	��� ��ũ ǥ�� ó��
	HTvoid				HT_vGuild_EmblemSwitch( CHTString );

	//	�ֽ� ��ũ ǥ�� �ϱ� ���ϱ�
	HTvoid				HT_vTrimutiri_MarkOn();
	HTvoid				HT_vTrimutiri_MarkOff();
	//	�ֽ� ��ũ ǥ�� ó��
	HTvoid				HT_vTrimutiri_MarkSwitch( CHTString );

	HTvoid				HT_vSetGuildMark(HTint iBackBmpNo, HTint iShapeBmpNo, HTint iColorNo);
	HTRESULT			HT_hrGetGuildMark(HTdword dwIdentity, HTint* dwColor, HTint* dwTitle, HTint* dwEmblem);

	//	��� �̸�
	CHTString			HT_strGuild_GetGuildName()	{	return m_strGuild_GuildName; };
	//	��峻�� ����
	HTbyte				HT_byGuild_GetAuthority()	{	return m_byGuild_GuilAuthority;	};
	//	��� ID
	HTint				HT_iGuild_GetGuildID()		{	return m_oGuildInfo.GuildID;	};

	// ��� â�� ��� ��ũ �� �ֽŸ�ũ �ٿ��� ���
	HTvoid				HT_vGuild_DialogBoxActiveOutput();

	//------------------------------------------------------------------------------
	// �ƽ��� ����/Ż�� �� ����� ���� �Լ�
	//------------------------------------------------------------------------------

	// ��� ���� �ƽ������� �Ⱦ� ó��
	HTRESULT			HT_hrGuild_PickCheckFromOtherObject( HTint iObjectID );
	
	// ��� ����/Ż�� ��Ŷ ó��
	HTvoid				HT_vGuildNet_CSP_AshuramGuild( BYTE byType, BYTE byAct, BYTE byResult );
	HTvoid				HT_vGuildNet_SCP_AshuramGuild( Msg_GuildAlliance* info );

	//	��� ���� �ƽ��� ��Ŷ Init
	HTvoid				HT_vGuildNet_SCP_StrongGuildInit( Msg_StrongHoldInit* info );
	//	��� ���� �ƽ��� ��Ŷ Udate
	HTvoid				HT_vGuildNet_SCP_StrongGuildUpdate( Msg_StrongHoldUpdate* info );
	//	���� ��� ������
	HTbool				HT_bGuildNet_MyStrongGuild()	{	return m_bMyStrongGuild;	};
	//	���� ������ ����� ����
	HTint				HT_iGuildNet_MyStrongGuildSequence()	{	return m_iMyStrongGuildIndex;	};
	//	���ձ�� 
	CHTString			HT_strGuild_AlliedGuildName( HTint iGuildIndex );

	//	Ashram Cargo
	//	Request Ashram Item
	HTvoid				HT_vAshram_CSPAshramItem();
	//	Recive Ashram Item
	HTvoid				HT_vAshram_SCPAshramItem( Msg_GuildItem* info );
	//	Request Set Level Ashram Cargo
	HTvoid				HT_vAshram_CSPSetLevelAshramCargo( HTbyte byCargoNo, HTbyte byLevel );
	//	Recive Set Level Ashram Cargo
	HTvoid				HT_vAshram_SCPSetLevelAshramCargo( Msg_GuildCargoUsingLevel* info );
	//	Request GuildCargoTimeExtension
	HTvoid				HT_vAshram_CSPGuildCargoTimeExtension( HTbyte byType );
	//	Recive GuildCargoTimeExtension
	HTvoid				HT_vAshram_SCPGuildCargoTimeExtension( Msg_GuildCargoTimeExtension* info );
	//	Recive GuildItemUpdate
	HTvoid				HT_vAshram_SCPGuildItemUpdate( Msg_GuildItemUpdate* info );
	//	Recive GuildCargoTime
	HTvoid				HT_vAshram_SCPGuildCargoTime( Msg_GuildCargoTime* info );

	//	Return
	//	Get Ashram Cargo Extence Type
	HTbyte				HT_byAshram_GetCargoExtenceType()	{	return m_iPageOfAshramCargo;	};

private:

	//------------------------------------------------------------------------------
	// Data manipulation functions
	//------------------------------------------------------------------------------
	//----------��ũ�� ����Ʈ ������ �κ�---------//
	//----------LL �ʱ�ȭ---------//
	HTvoid HT_LL_vInitList();
	//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
	HTvoid HT_LL_hrInsertAfter( S_GUILD_DATA* );
	//----------LL ����Ÿ �����_�̸�����---------//
	HTvoid HT_LL_hrDeleteNode( CHTString strName );
	//----------LL ����Ÿ �����_�O��_�̸�����---------//
	S_GUILD_DATA* HT_LL_hrSerchNode( CHTString strName );
	//----------LL ����Ÿ ���� ����_�ִ��� ������ �̸����� ����---------//
	HTRESULT HT_LL_hrExgistCheckName( CHTString strName );
    //----------LL ����Ÿ ���� �����---------//
	HTvoid HT_LL_hrDeleteAll();

	//--------------------------------------------------------------------------
	// �޼��� ���
	//--------------------------------------------------------------------------
	HTvoid				HT_vGuild_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid				HT_vGuild_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	// �ں� ����â
	HTint				m_iTabNo;						// �ܳѹ� ��� (�ں�)
	HTint				m_iBackIndex;					// ����̹��� �ε���
	HTint				m_iTitleIndex;					// Ÿ��Ʋ�̹��� �ε���
	HTint				m_iBackColor;					// �÷� �ε���
	HTint				m_iSelectWindow;				// 0 = �Ϲ� �ƽ��� ����� â, 1 = ����帶, 2 = �񽴴�, 3 = �ù�

	BYTE				m_byGuild_ConfirmGrade;			//	Ȯ�� �ܰ�
	HTbool				m_bGuild_ConfirmDlgBoxSw;		//	Ȯ�� ��ư ���ȴ��� üũ
	CHTString			m_strGuild_GuildName;			//	â���� ��� �̸�
	CHTString			m_strGuild_GuildMasterName;		//	��� ����Ʈ �̸�
	CHTString			m_strGuild_ListSelectdName;		//	��� ����Ʈ���� ���õ� ����� �̸�
	BYTE				m_byGuild_GuilAuthority;		//	��峻�� ����
	DWORD				m_dwGuild_JoinGuildKeyID;		//	��� ������ ��û�� ����� KeyID
	HTint				m_iGuild_TempGuildID;			//	��� ���� �¶��� ���� ��� ���̵�

	MSG_GuildInfo		m_oGuildInfo;
	
	CHTString			m_strGuild_CharacterName;		//	���� ���� �� ������ ĳ���͸�
	HTint				m_nGuildConnectMsg;				//  ���� ���� �޽��� �˸� üũ �÷��� ����

	// ���� �ƽ��� ����
	HTint				m_nAshuramGuildJoinMode;			// ���� �ƽ��� ��û ���
	HTint				m_iAshuramGuildJoin_SendCharKeyID;	// ���� �ƽ��� ��û�� ���� ���̵�
	CHTString			m_strAshuramGuildJoin_SendCharName;	// ���� �ƽ��� ��û�� ���� �̸�
	HTint				m_byAshuramGuildJoin_ResponseReason;// ���� ����

	CHTString			m_strAlliedGuildName[2];				// ���� ��� �̸�
	CHTString			m_strEnemyGuildName[2];					// ���� ��� �̸�
	
	CHTString			m_strStrongGuildName[4];				// ����� ������ ��� �̸�
	HTbool				m_bMyStrongGuild;						// ���� ����� �����ϰ� �ִ��� Ȯ��
	HTint				m_iMyStrongGuildIndex;					// �� ��� �ε���

	//	MessageBox Type
	HTint				m_iGuild_MsgBoxType;


private:
	// �ּҷ� ������ ����Ʈ
	S_GUILD_DATA*			m_pGuildList_Head;
	S_GUILD_DATA*			m_pGuildList_Tail;
	HTint					m_iGuildCount;

	DWORD					m_dwGuild_EmblemID;
	HTint					m_iEmblem;
	HTint					m_iTitle;
	HTint					m_iColor;

	HTbool					m_bGuild_SlideBarBtn;
	HTint					m_iGuild_SlideBarCurPos;

	CHTString				m_szMsgSting; // �޼����� ���� ��Ʈ��

	//	Ashram Cargo
	HTint					m_iPageOfAshramCargo;
	HTbyte					m_iPrevPageOfAshramCargo;
	//	Ashram Cargo ItemArr
	STRUCT_ITEM				m_arrItemOfAshramCargo[3][MAX_CARGO];
	//	Ashram Cargo Extence Type
	HTbyte					m_byAshramCargoExtenceType;
	//	CargoUse
	HTbool					m_bAshramCargoUseSw;
	//	UseCargoLevel
	HTbyte					m_byUseCargoLevel[3];
};
