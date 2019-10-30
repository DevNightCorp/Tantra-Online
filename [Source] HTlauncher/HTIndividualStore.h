//////////////////////////////////////////////////////////////////////////////////////////
// 설명 : 게임 내에서 출력할 에러메세지, 네트워크 메세지 등으로 사용되는 스트링 모음
// 
// 작성자 : 김선미
// 2004.01.09
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTIndividualStore_H_
#define _HTIndividualStore_H_

class CHTIndividualStore
{
public:
	CHTIndividualStore(void);
	~CHTIndividualStore(void);

	HTvoid			HT_vIndividualStore_CleanUp();

	HTvoid			HT_vIndividualStore_Init();
	//	Create Window
	HTvoid			HT_vIndividualStore_CreateWindow();
	//	IndividualStore1
	static void		HT_vEI_InputCheckForIndividualStore1(int iAction, int iTarget, int iTargetID);
	//	IndividualStore2
	static void		HT_vEI_InputCheckForIndividualStore2(int iAction, int iTarget, int iTargetID);
	//	Bye List Wnd
	static void		HT_vEI_InputCheckForByeListWnd(int iAction, int iTarget, int iTargetID);
	//	DIALOG_MY_USEINFO_V3
	static void		HT_vEI_InputCheckForMyUseInfo(int iAction, int iTarget, int iTargetID);

	//-----------------------------------------------------------------
	// 3분에 한번씩 채팅 메시지 날리기 위해
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_Control_Chatting();

	HTvoid			HT_vIndividualStore_Active( HTint iStoreID );
	HTvoid			HT_vIndividualStore_SelectItemForSell( HTdword dwItemKeyID );
	
	//-----------------------------------------------------------------
	// 물품판매 창
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_AddSellItem();
	HTvoid			HT_vIndividualStore_DeleteSellItem( HTint iPos );
	HTvoid			HT_vIndividualStore_Close();
	// 사용 불가능한 표시 다시 그리기
	HTvoid			HT_vRenewalPossibleBar( HTbool bUsable );
	// 사용 불가능한 표시 삭제
	HTvoid			HT_vDelPossibleBar( );
	//-----------------------------------------------------------------
	// 물품구입 창
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_StoreModeStart();
	HTvoid			HT_vIndividualStore_StoreModeEnd();

	HTvoid			HT_vIndividualStore_GetUseListOutPut(HTint index);
	HTvoid			HT_vIndividualStore_AddBuyItem( HTint iPos );
	HTvoid			HT_vIndividualStore_DeleteBuyItem( HTint iPos );

	//-----------------------------------------------------------------
	// 개수/가격 입력창
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_PackingWin_Active( );
	HTvoid			HT_vIndividualStore_PriceWin_Active();
	
	//-----------------------------------------------------------------
	// 반환
	//-----------------------------------------------------------------
	// 판매창에 등록된 아이템 KeyID 구하기
	HTint			HT_iIndividualStore_GetKeyIDInSellWin( HTint iPos );
	// 구매창에 등록된 아이템 KeyID 구하기
	HTint			HT_iIndividualStore_GetKeyIDInBuyWin( HTint iPos );
	// 판매목록의 아이템 가격 구하기
	HTint			HT_iIndividualStore_GetRupiah( HTdword dwKeyID );
	// 판매목록의 아이템 개수 구하기
	HTint			HT_iIndividualStore_GetPackCount( HTdword dwKeyID );
	// 현재 내가 상점을 열고 있는지
	HTbool			HT_bIndividualStore_IsStoreMode();
	// 상점 메세지 구하기
	CHTString		HT_szIndividualStore_StoreMessage() { return m_szBuyMessage; };
	//-----------------------------------------------------------------
	// 네트워크 부분
	//-----------------------------------------------------------------
	HTvoid			HT_vNetWork_CSP_Req_Store( HTint iStoreID = 0 );
	HTvoid			HT_vNetWork_SCP_Resp_Store( MSG_MobStore* info );

	HTvoid			HT_vNetWork_CSP_Req_Store_Buy();
	HTvoid			HT_vNetWork_SCP_Resp_Store_Buy( MSG_MobStore_Buy* info );

	HTvoid			HT_vNetWork_SCP_Resp_Status( MSG_MobStatus* info );

	//-----------------------------------------------------------------
	// 프리미엄 서비스 이용내역 및 구입창 부분
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_ButtonCheckForBuyListOutPut( HTint iPage);

	HTvoid			HT_vIndividualStore_ButtonCheckForUseListOutPut();

	HTRESULT		HT_hrCheckBox( HTPoint pPt );
	HTvoid			HT_vNetWork_CSP_Req_TimeMode(HTushort Mode);

	HTushort		PrimiumService_UseList();									// 사용내역을 스위치값을 얻어온다.
	int				m_iTabNo;				// 내사용내역 프리미엄 버튼값 

private:
	HTbyte					m_byStoreProcess;

	HTint					m_iStoreID;
	HTdword					m_dwSelectKeyID;

	// 상점에 있는 아이템 관련
	MOBSTOREITEM			m_sStoreItem[MAX_MOBSTORE];
	HTbyte					m_byStoreItemNum;
	HTint					m_iTotalPrice;
	HTint					m_iPrice;
	HTint					m_iPackCount;
	HTint					m_byMaxStoreItemCount; // 상점에 등록할 수 있는 아이템 최대 개수

	CHTString				m_szBuyMessage;

	// 사기위해 선택한 아이템 목록
	HTint					m_iStoreItemKeyID[MAX_MOBSTORE];
	HTint					m_iBuyItem[MAX_MOBSTORE];
	HTint					m_byBuyItemNum;
	HTbool					m_bTimeItem;		// 시간제 아이템 구분 (시간제 아이템은 갯수 구분을 하지 않는다)

	//	3분에 한번씩 채팅 메시지 날리기 위해
	HTdword					m_dwAutoChatMsgStartTime;

	HTint					m_iMaxPage;
	HTint					m_iNowPage;

	int						m_iCheckUse[10];	// 프리미엄 아이템 효과 스위칭 변수 (1 = TRUE, 0 = FALSE)
	int						m_iCheckEnable[10];	// 프리미엄 아이템 사용 여부 체크 변수 (1 = TRUE, 0 = FALSE)

	//	MessageBox Type
	int						m_iStore_MsgBoxType;
};
#endif