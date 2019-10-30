//////////////////////////////////////////////////////////////////////////////////////////
// ���� : ���� ������ ����� �����޼���, ��Ʈ��ũ �޼��� ������ ���Ǵ� ��Ʈ�� ����
// 
// �ۼ��� : �輱��
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
	// 3�п� �ѹ��� ä�� �޽��� ������ ����
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_Control_Chatting();

	HTvoid			HT_vIndividualStore_Active( HTint iStoreID );
	HTvoid			HT_vIndividualStore_SelectItemForSell( HTdword dwItemKeyID );
	
	//-----------------------------------------------------------------
	// ��ǰ�Ǹ� â
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_AddSellItem();
	HTvoid			HT_vIndividualStore_DeleteSellItem( HTint iPos );
	HTvoid			HT_vIndividualStore_Close();
	// ��� �Ұ����� ǥ�� �ٽ� �׸���
	HTvoid			HT_vRenewalPossibleBar( HTbool bUsable );
	// ��� �Ұ����� ǥ�� ����
	HTvoid			HT_vDelPossibleBar( );
	//-----------------------------------------------------------------
	// ��ǰ���� â
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_StoreModeStart();
	HTvoid			HT_vIndividualStore_StoreModeEnd();

	HTvoid			HT_vIndividualStore_GetUseListOutPut(HTint index);
	HTvoid			HT_vIndividualStore_AddBuyItem( HTint iPos );
	HTvoid			HT_vIndividualStore_DeleteBuyItem( HTint iPos );

	//-----------------------------------------------------------------
	// ����/���� �Է�â
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_PackingWin_Active( );
	HTvoid			HT_vIndividualStore_PriceWin_Active();
	
	//-----------------------------------------------------------------
	// ��ȯ
	//-----------------------------------------------------------------
	// �Ǹ�â�� ��ϵ� ������ KeyID ���ϱ�
	HTint			HT_iIndividualStore_GetKeyIDInSellWin( HTint iPos );
	// ����â�� ��ϵ� ������ KeyID ���ϱ�
	HTint			HT_iIndividualStore_GetKeyIDInBuyWin( HTint iPos );
	// �ǸŸ���� ������ ���� ���ϱ�
	HTint			HT_iIndividualStore_GetRupiah( HTdword dwKeyID );
	// �ǸŸ���� ������ ���� ���ϱ�
	HTint			HT_iIndividualStore_GetPackCount( HTdword dwKeyID );
	// ���� ���� ������ ���� �ִ���
	HTbool			HT_bIndividualStore_IsStoreMode();
	// ���� �޼��� ���ϱ�
	CHTString		HT_szIndividualStore_StoreMessage() { return m_szBuyMessage; };
	//-----------------------------------------------------------------
	// ��Ʈ��ũ �κ�
	//-----------------------------------------------------------------
	HTvoid			HT_vNetWork_CSP_Req_Store( HTint iStoreID = 0 );
	HTvoid			HT_vNetWork_SCP_Resp_Store( MSG_MobStore* info );

	HTvoid			HT_vNetWork_CSP_Req_Store_Buy();
	HTvoid			HT_vNetWork_SCP_Resp_Store_Buy( MSG_MobStore_Buy* info );

	HTvoid			HT_vNetWork_SCP_Resp_Status( MSG_MobStatus* info );

	//-----------------------------------------------------------------
	// �����̾� ���� �̿볻�� �� ����â �κ�
	//-----------------------------------------------------------------
	HTvoid			HT_vIndividualStore_ButtonCheckForBuyListOutPut( HTint iPage);

	HTvoid			HT_vIndividualStore_ButtonCheckForUseListOutPut();

	HTRESULT		HT_hrCheckBox( HTPoint pPt );
	HTvoid			HT_vNetWork_CSP_Req_TimeMode(HTushort Mode);

	HTushort		PrimiumService_UseList();									// ��볻���� ����ġ���� ���´�.
	int				m_iTabNo;				// ����볻�� �����̾� ��ư�� 

private:
	HTbyte					m_byStoreProcess;

	HTint					m_iStoreID;
	HTdword					m_dwSelectKeyID;

	// ������ �ִ� ������ ����
	MOBSTOREITEM			m_sStoreItem[MAX_MOBSTORE];
	HTbyte					m_byStoreItemNum;
	HTint					m_iTotalPrice;
	HTint					m_iPrice;
	HTint					m_iPackCount;
	HTint					m_byMaxStoreItemCount; // ������ ����� �� �ִ� ������ �ִ� ����

	CHTString				m_szBuyMessage;

	// ������� ������ ������ ���
	HTint					m_iStoreItemKeyID[MAX_MOBSTORE];
	HTint					m_iBuyItem[MAX_MOBSTORE];
	HTint					m_byBuyItemNum;
	HTbool					m_bTimeItem;		// �ð��� ������ ���� (�ð��� �������� ���� ������ ���� �ʴ´�)

	//	3�п� �ѹ��� ä�� �޽��� ������ ����
	HTdword					m_dwAutoChatMsgStartTime;

	HTint					m_iMaxPage;
	HTint					m_iNowPage;

	int						m_iCheckUse[10];	// �����̾� ������ ȿ�� ����Ī ���� (1 = TRUE, 0 = FALSE)
	int						m_iCheckEnable[10];	// �����̾� ������ ��� ���� üũ ���� (1 = TRUE, 0 = FALSE)

	//	MessageBox Type
	int						m_iStore_MsgBoxType;
};
#endif