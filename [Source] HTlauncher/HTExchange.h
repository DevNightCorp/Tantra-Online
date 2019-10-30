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

	//	�Է� �޼��� ó��
	//	Exchange Inventory
	static void			HT_vEchsnhge_InputCheckForExchange(int iAction, int iTarget, int iTargetID);
	
	//-----------------------------------------------------------------
	// ���콺 �Է� üũ
	//-----------------------------------------------------------------
	// ��ȯ ��û
	HTRESULT			HT_vExchange_RequestTrade( HTint );
	// ��ȯâ �ٿ��/�����
	HTvoid				HT_vExchange_ActiveSw( HTbool );
	//	ESC Key ������ ��ȯâ �ݱ�
	HTvoid				HT_vExchange_ESC_CloseWindow();
	// ��ȯ�� ������ �� �����Կ� ��ϵ� ������ ����
	HTvoid				HT_vExchangeWindow_DeleteQuickSlotItem();

	//-----------------------------------------------------------------
	// ��ȯ/����
	//-----------------------------------------------------------------
	// ����â�� ��ȯ ��ư
	HTvoid				HT_vExchange_SetClickTradeButton( HTbool );
	HTbool				HT_vExchange_GetClickTradeButton();
	// ��ȯâ Ȱ��ȭ ���� ��ȯ
	HTbool				HT_vExchange_ExchangeWinActive();
	// ���� ��ȯ������ ���� ��ȯ
	HTbool				HT_bExchange_IsExchanging( );

	// ���� �Ǵ� �� ��ȯâ�� ������ ���� ����
	HTRESULT			HT_hrExchange_SetMyTradeItem(  HTdword dwKeyID, HT_ItemReturnRoom sLocRoom );
	HTvoid				HT_vExchange_SetOtherTradeItem( PS_CSP_REQ_TRADE info );
	// ��ȯ�� �� ���� ����
	HTvoid				HT_vExchange_SetMoney(HTint iRupiah);

	// �� ��ȯâ�� �÷����� ������ ã��
	HTint				HT_iExchange_GetKeyIDMyTradeItem( HTint iInvenIndex );
	// ��ȯ �³��ϰų� ��������� ��ȯâ �ݰ� ���� �ʱ�ȭ
	HTvoid				HT_vExchangeWindow_Closed();

	//-----------------------------------------------------------------
	// ��Ʈ��ũ �κ�
	//-----------------------------------------------------------------
	HTvoid HT_vNetWork_CSP_Req_Trade();
	HTvoid HT_vNetWork_SCP_Resp_Trade( PS_CSP_REQ_TRADE info );
	// ��ȯ ���
	HTvoid HT_vNetWork_SCP_Resp_Trade_Cancel( PS_RESULT info );

private:
	HTvoid				HT_vExchange_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid				HT_vExchange_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool				m_bExchangeWin_Active;

	// ��ȯ ���� ����
	HTbyte				m_byExchange_Squence;
	// ���� ��ȯ Ȯ�� ��ư�� ���ȴ°�?
	HTbool						m_bPress_OK_Button;
	// ��ȯ ��û �� ���
	DWORD				m_dwReceiveExchangeCharKeyID;
	// ��ȯ�� ����� ����
	DWORD				m_dwExchangeCharKeyID;
	CHTString			m_szExchangeCharName;

	// ������ ��ȯ ��û�� ���� ����
	BYTE				m_byExchangeResult;
	
	// ��ȯ ��û�� �ߴ°�?
	HTbool				m_bClickTradeButtonSw;

	// ��ȭ���ڰ� Ȱ��ȭ ����
	CHTString			m_szExchange_DialogBoxMessage;

	// ����� ��ȯâ�� �� ������ ���
	HTint						m_iOtherCharItemKeyID[MAX_TRADE];
	HTint						m_iOtherCharItem_Count;
	HTint						m_iExchangeRupiah;		// ��ȯ�� ����� ���Ǿ�
	// �� ��ȯâ�� �� ������ ���
	STRUCT_ITEM					m_sMyItem[MAX_TRADE];
	HTbyte						m_byMyInvenPos[MAX_TRADE];
	HTint						m_iMyItem_Count;
	HTint						m_iMyExchangeRupiah;	// ���� ���濡�� �� ���Ǿ�
	// ĳ���� ��ġ ����
	HTPoint						m_pExchange_MemoryCharPos;
};
#endif // #ifndef _HTExchange_h_