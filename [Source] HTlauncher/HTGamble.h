#pragma once

const int YUT_MAX_NUMBER = 29;

// GAMBLE UI 제어 클래스 
class HTGamble
{
private:
	// 서버로 보내는 패킷 처리 함수들 모음
	HTvoid		HT_vNetWork_CSP_Req_YutMyMoney();							// Send Msg_YutMyMoney
	HTvoid		HT_vNetWork_CSP_Req_YutStatus();							// Send Msg_YutStatus
	HTvoid		HT_vNetWork_CSP_Req_YutBet();								// Send Msg_YutBet
	HTvoid		HT_vNetWork_CSP_Req_YutGetMoney();							// Send Msg_YutGetMoney

	int			m_nTotalRupia;												// Total Rupia
						
public:
	HTGamble(void);
	~HTGamble(void);
	
	int m_MyStatus[YUT_MAX_NUMBER];											// 내 정보 [주춧돌 배열 기준]
	int m_AllStatus[YUT_MAX_NUMBER];										// 전체 정보 [주춧돌 배열 기준]
	int	m_Count[48];														// 배팅시 서버로 전송해야할 배열[인벤기준으로 소모할 금편의 양을 인벤칸별 적어서 보낸다.]
	int m_Position;															// 배팅할 곳 Index
	int m_TotalMyMoney;														// 총 나의 적립액
	int m_TotalAllMoney;													// 총 적립액

	HTvoid		HT_vGamble_Init();											// 처음 구동시 한번만 실행 (UI 생성부)
	HTvoid		HT_vGamble_WindowPopup();									// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	HTvoid		HT_vGamble_SetInfo();										// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrGamble_InputCheck(int iAction, int iTarget, int iTargetID);// 입력 처리 함수 (UI 입력제어부)

	// 서버로부터 받는 패킷 처리 함수들 모음
	HTvoid		HT_vGamble_NetWorkYutMyMoney( Msg_YutMyMoney* info );		// Recive Msg_YutMyMoney
	HTvoid		HT_vGamble_NetWorkYutStatus( Msg_YutStatus* info );			// Recive Msg_YutStatus
	HTvoid		HT_vGamble_NetWorkYutBet( Msg_YutBet* info );				// Recive Msg_YutBet
	HTvoid		HT_vGamble_NetWorkYutGetMoney( Msg_YutGetMoney* info );				// Recive Msg_YutGetMoney
};


////////////////////////////////////////////////////////////////////
//
//					공성전
//
////////////////////////////////////////////////////////////////////
class HTSiege
{
public:
	HTSiege(void);
	~HTSiege(void);

	//	최초 촉기화
	HTvoid		HT_vSiege_Init();
	//	윈도우 생성
	HTvoid		HT_vSiege_CreateWindow();
	//	입력함수 처리 참가아쉬람
	static void HT_vSiege_InputCheckSiege1(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 공성전상황
	static void HT_vSiege_InputCheckSiege2(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 공성전선포
	static void HT_vSiege_InputCheckSiege3(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 비류성관리
	static void HT_vSiege_InputCheckSiege4(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 아쉬람 정보
	static void HT_vSiege_InputCheckJoinInfo0(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 아쉬람 정보
	static void HT_vSiege_InputCheckJoinInfo1(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 아쉬람 정보
	static void HT_vSiege_InputCheckJoinInfo2(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 아쉬람 정보
	static void HT_vSiege_InputCheckJoinInfo3(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말1
	static void HT_vSiege_InputCheckHelp1(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말2
	static void HT_vSiege_InputCheckHelp2(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말3
	static void HT_vSiege_InputCheckHelp3(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말4
	static void HT_vSiege_InputCheckHelp4(int iAction, int iTarget, int iTargetID);

	//	참가 아쉬람 정보 신청
	HTvoid		HT_vSiege_RequestJoinAshramInfo();
	//	아쉬람 마크 붙이기
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
	// 세금 요청 타입 저장
	int				m_iGetMoneyType;
	int				m_iGetMoneyAction;
	int				m_iGetMoneyYut;			// 윳판에서 쌓인 세금량
	//	선택 아쉬람 정보창 페이지
	HTint			m_iSiege_AshramWndPage[4];
	//	Siege Ashram info, if 0 then empty
	int				m_iSiege_GuildID[8];
	//	Brodcast Siege Time
	int				m_iSiege_SiegeTime;
	//	Castle Ashram ID
	HTint			m_iSiege_CastleAshramID;
	//	세금 비율
	HTbyte			m_bySiege_MoneyRate;
	//	연맹들 이름
	CHTString		m_strSiege_Alliance[4];
};
