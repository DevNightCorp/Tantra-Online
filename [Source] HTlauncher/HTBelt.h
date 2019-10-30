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

	//----------윈도우 위에 있는지 체크----------//
	HTRESULT				HT_bBelt_Check_InWindow( HTPoint pPt, HTbool bType );
	//----------윈도우 위치 반환----------//
	HTvector3				HT_bBelt_GetWindowPos();
	//----------벨트 윈도우가 활성화 상태인가----------//
	HTbool					HT_bBeltInventory_GetStatus();

	//----------아이템 셋팅하기----------//
	HTvoid					HT_bBeltInventory_SetItem( DWORD dwKeyID, HTPoint, HTdword );
	//----------아이템 사용하기----------//
	HTvoid					HT_bBeltInventory_ItemUse( HTint nIndex);

	//----------네트워크----------//
	HTvoid					HT_vNetWork_CSP_RESP_BeltItem_Use(DWORD dwKeyID);
	HTvoid					HT_vNetWork_SCP_RESP_BeltItem_Use_Result( DWORD dwKeyID ); 
	

private:
	HTbool				m_bBeltActive_Sw;
	HTvector3			m_vecBeltItemPos;

	DWORD				m_dwBeltItem_KeyID[3][5];
	HTint				m_nItemUse_Index;
};
