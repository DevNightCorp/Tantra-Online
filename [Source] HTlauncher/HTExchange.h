#ifndef _HTExchange_h_
#define _HTExchange_h_

class HTExchange
{
public:
	HTExchange(void);
	~HTExchange(void);
	HTvoid				HT_vExchange_CleanUp();

	HTRESULT			HT_hrExchange_Init();
	//	Create Window
	HTvoid				HT_vExchange_CreateWindow();

	//	입력 메세지 처리
	//	Exchange Inventory
	static void			HT_vEchsnhge_InputCheckForExchange(int iAction, int iTarget, int iTargetID);
	
	//-----------------------------------------------------------------
	// 마우스 입력 체크
	//-----------------------------------------------------------------
	// 교환 요청
	HTRESULT			HT_vExchange_RequestTrade( HTint );
	// 교환창 뛰우기/지우기
	HTvoid				HT_vExchange_ActiveSw( HTbool );
	//	ESC Key 누르면 교환창 닫기
	HTvoid				HT_vExchange_ESC_CloseWindow();
	// 교환한 아이템 중 퀵슬롯에 등록된 아이템 삭제
	HTvoid				HT_vExchangeWindow_DeleteQuickSlotItem();

	//-----------------------------------------------------------------
	// 반환/셋팅
	//-----------------------------------------------------------------
	// 메인창의 교환 버튼
	HTvoid				HT_vExchange_SetClickTradeButton( HTbool );
	HTbool				HT_vExchange_GetClickTradeButton();
	// 교환창 활성화 상태 반환
	HTbool				HT_vExchange_ExchangeWinActive();
	// 현재 교환중인지 상태 반환
	HTbool				HT_bExchange_IsExchanging( );

	// 상대방 또는 내 교환창에 아이템 정보 갱신
	HTRESULT			HT_hrExchange_SetMyTradeItem(  HTdword dwKeyID, HT_ItemReturnRoom sLocRoom );
	HTvoid				HT_vExchange_SetOtherTradeItem( PS_CSP_REQ_TRADE info );
	// 교환할 돈 정보 갱신
	HTvoid				HT_vExchange_SetMoney(HTint iRupiah);

	// 내 교환창에 올려놓은 아이템 찾기
	HTint				HT_iExchange_GetKeyIDMyTradeItem( HTint iInvenIndex );
	// 교환 승낙하거나 취소했을대 교환창 닫고 변수 초기화
	HTvoid				HT_vExchangeWindow_Closed();

	//-----------------------------------------------------------------
	// 네트워크 부분
	//-----------------------------------------------------------------
	HTvoid HT_vNetWork_CSP_Req_Trade();
	HTvoid HT_vNetWork_SCP_Resp_Trade( PS_CSP_REQ_TRADE info );
	// 교환 취소
	HTvoid HT_vNetWork_SCP_Resp_Trade_Cancel( PS_RESULT info );

private:
	HTvoid				HT_vExchange_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid				HT_vExchange_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool				m_bExchangeWin_Active;

	// 교환 진행 상태
	HTbyte				m_byExchange_Squence;
	// 내가 교환 확인 버튼을 눌렸는가?
	HTbool						m_bPress_OK_Button;
	// 교환 요청 온 상대
	DWORD				m_dwReceiveExchangeCharKeyID;
	// 교환할 상대의 정보
	DWORD				m_dwExchangeCharKeyID;
	CHTString			m_szExchangeCharName;

	// 상대방의 교환 요청에 대한 응답
	BYTE				m_byExchangeResult;
	
	// 교환 요청을 했는가?
	HTbool				m_bClickTradeButtonSw;

	// 대화상자가 활성화 상태
	CHTString			m_szExchange_DialogBoxMessage;

	// 상대편 교환창에 들어갈 아이템 목록
	HTint						m_iOtherCharItemKeyID[MAX_TRADE];
	HTint						m_iOtherCharItem_Count;
	HTint						m_iExchangeRupiah;		// 교환할 상대의 루피아
	// 내 교환창에 들어갈 아이템 목록
	STRUCT_ITEM					m_sMyItem[MAX_TRADE];
	HTbyte						m_byMyInvenPos[MAX_TRADE];
	HTint						m_iMyItem_Count;
	HTint						m_iMyExchangeRupiah;	// 내가 상대방에게 줄 루피아
	// 캐릭터 위치 정보
	HTPoint						m_pExchange_MemoryCharPos;
};
#endif // #ifndef _HTExchange_h_