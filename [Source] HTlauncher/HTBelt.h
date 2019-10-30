#pragma once


class HTBelt
{
public:
	HTBelt(void);
	~HTBelt(void);
	HTvoid					HT_vBelt_CleanUp();

	HTRESULT				HT_hrBelt_init();
	HTvoid					HT_vBelt_Control();
	HTvoid					HT_vBelt_Active();

	//----------������ ���� �ִ��� üũ----------//
	HTRESULT				HT_bBelt_Check_InWindow( HTPoint pPt, HTbool bType );
	//----------������ ��ġ ��ȯ----------//
	HTvector3				HT_bBelt_GetWindowPos();
	//----------��Ʈ �����찡 Ȱ��ȭ �����ΰ�----------//
	HTbool					HT_bBeltInventory_GetStatus();

	//----------������ �����ϱ�----------//
	HTvoid					HT_bBeltInventory_SetItem( DWORD dwKeyID, HTPoint, HTdword );
	//----------������ ����ϱ�----------//
	HTvoid					HT_bBeltInventory_ItemUse( HTint nIndex);

	//----------��Ʈ��ũ----------//
	HTvoid					HT_vNetWork_CSP_RESP_BeltItem_Use(DWORD dwKeyID);
	HTvoid					HT_vNetWork_SCP_RESP_BeltItem_Use_Result( DWORD dwKeyID ); 
	

private:
	HTbool				m_bBeltActive_Sw;
	HTvector3			m_vecBeltItemPos;

	DWORD				m_dwBeltItem_KeyID[3][5];
	HTint				m_nItemUse_Index;
};
