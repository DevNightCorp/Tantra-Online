#pragma once

const int YUT_MAX_NUMBER = 29;

// GAMBLE UI ���� Ŭ���� 
class HTGamble
{
private:
	// ������ ������ ��Ŷ ó�� �Լ��� ����
	HTvoid		HT_vNetWork_CSP_Req_YutMyMoney();							// Send Msg_YutMyMoney
	HTvoid		HT_vNetWork_CSP_Req_YutStatus();							// Send Msg_YutStatus
	HTvoid		HT_vNetWork_CSP_Req_YutBet();								// Send Msg_YutBet
	HTvoid		HT_vNetWork_CSP_Req_YutGetMoney();							// Send Msg_YutGetMoney

	int			m_nTotalRupia;												// Total Rupia
						
public:
	HTGamble(void);
	~HTGamble(void);
	
	int m_MyStatus[YUT_MAX_NUMBER];											// �� ���� [���嵹 �迭 ����]
	int m_AllStatus[YUT_MAX_NUMBER];										// ��ü ���� [���嵹 �迭 ����]
	int	m_Count[48];														// ���ý� ������ �����ؾ��� �迭[�κ��������� �Ҹ��� ������ ���� �κ�ĭ�� ��� ������.]
	int m_Position;															// ������ �� Index
	int m_TotalMyMoney;														// �� ���� ������
	int m_TotalAllMoney;													// �� ������

	HTvoid		HT_vGamble_Init();											// ó�� ������ �ѹ��� ���� (UI ������)
	HTvoid		HT_vGamble_WindowPopup();									// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	HTvoid		HT_vGamble_SetInfo();										// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrGamble_InputCheck(int iAction, int iTarget, int iTargetID);// �Է� ó�� �Լ� (UI �Է������)

	// �����κ��� �޴� ��Ŷ ó�� �Լ��� ����
	HTvoid		HT_vGamble_NetWorkYutMyMoney( Msg_YutMyMoney* info );		// Recive Msg_YutMyMoney
	HTvoid		HT_vGamble_NetWorkYutStatus( Msg_YutStatus* info );			// Recive Msg_YutStatus
	HTvoid		HT_vGamble_NetWorkYutBet( Msg_YutBet* info );				// Recive Msg_YutBet
	HTvoid		HT_vGamble_NetWorkYutGetMoney( Msg_YutGetMoney* info );				// Recive Msg_YutGetMoney
};


////////////////////////////////////////////////////////////////////
//
//					������
//
////////////////////////////////////////////////////////////////////
class HTSiege
{
public:
	HTSiege(void);
	~HTSiege(void);

	//	���� �˱�ȭ
	HTvoid		HT_vSiege_Init();
	//	������ ����
	HTvoid		HT_vSiege_CreateWindow();
	//	�Է��Լ� ó�� �����ƽ���
	static void HT_vSiege_InputCheckSiege1(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ��������Ȳ
	static void HT_vSiege_InputCheckSiege2(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ����������
	static void HT_vSiege_InputCheckSiege3(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���������
	static void HT_vSiege_InputCheckSiege4(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� �ƽ��� ����
	static void HT_vSiege_InputCheckJoinInfo0(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� �ƽ��� ����
	static void HT_vSiege_InputCheckJoinInfo1(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� �ƽ��� ����
	static void HT_vSiege_InputCheckJoinInfo2(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� �ƽ��� ����
	static void HT_vSiege_InputCheckJoinInfo3(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����1
	static void HT_vSiege_InputCheckHelp1(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����2
	static void HT_vSiege_InputCheckHelp2(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����3
	static void HT_vSiege_InputCheckHelp3(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����4
	static void HT_vSiege_InputCheckHelp4(int iAction, int iTarget, int iTargetID);

	//	���� �ƽ��� ���� ��û
	HTvoid		HT_vSiege_RequestJoinAshramInfo();
	//	�ƽ��� ��ũ ���̱�
	HTvoid		HT_vSiege_SetAhsramMark( HTint iDlgNo, HTint iSlotNo, HTint iGuildNo );

	//	Get
	//	Get Owner of Castle
	HTbool		HT_vSiege_GetOwerOfCastle();
	//	Get Money Rate
	HTbyte		HT_bySiege_GetMoneyRate()		{	return m_bySiege_MoneyRate;	};

	//	Network
	//	ApplySiege
	HTvoid		HT_vSiege_NetworkApplySiege( HTbyte byClanSlot, HTbyte byExpandSlot );
	//	SCP ApplySiege
	HTvoid		HT_vSiege_NetworkSCP_ApplySiege( MSG_APPLY_SIEGE* info );
	//	CheckSiegeEntry
	HTvoid		HT_vSiege_NetworkCheckSiegeEntry( HTint iClanSlot, HTint iPage );
	//	Siege Entry
	HTvoid		HT_vSiege_NetworkSiegeEntry( MSG_SIEGE_ENTRY* info );
	//	CSP State of the siege
	HTvoid		HT_vSiege_NetworkCSPStateOfTheSiege();
	//	SCP State of the siege
	HTvoid		HT_vSiege_NetworkSCPStateOfTheSiege( MSG_STATE_OF_THE_SIEGE* info );
	//	CSP Fix Data of Siege
	HTvoid		HT_vSiege_NetworkCSP_FixDataOfSiege( HTbyte byWhat, HTbyte byDate );
	//	SCP Fix Data Of Siege
	HTvoid		HT_vSiege_NetworkSCP_FixDataOfSiege( MSG_FIX_DATE_OF_SIEGE* info );
	//	CSP Set SalesRate
	HTvoid		HT_vSiege_NetworkCSP_SetSalesRate( HTbyte byType, HTbyte byRate );
	//	SCP Set SalesRate
	HTvoid		HT_vSiege_NetworkSCP_SetSalesRate( Msg_SetSalesRate* info );
	//	CSP Get Money
	HTvoid		HT_vSiege_NetworkCSP_GetMoney();
	//	SCP Get Money
	HTvoid		HT_vSiege_NetworkSCP_GetMoney( Msg_GetMoney* info );
	//	SCP Castle
	HTvoid		HT_vSiege_NetworkSCP_SetCastle( HTint iAshramID );

public:
	// ���� ��û Ÿ�� ����
	int				m_iGetMoneyType;
	int				m_iGetMoneyAction;
	int				m_iGetMoneyYut;			// ���ǿ��� ���� ���ݷ�
	//	���� �ƽ��� ����â ������
	HTint			m_iSiege_AshramWndPage[4];
	//	Siege Ashram info, if 0 then empty
	int				m_iSiege_GuildID[8];
	//	Brodcast Siege Time
	int				m_iSiege_SiegeTime;
	//	Castle Ashram ID
	HTint			m_iSiege_CastleAshramID;
	//	���� ����
	HTbyte			m_bySiege_MoneyRate;
	//	���͵� �̸�
	CHTString		m_strSiege_Alliance[4];
};
