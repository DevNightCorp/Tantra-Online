#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htbelt.h"

HTBelt::HTBelt(void)
{
}

HTBelt::~HTBelt(void)
{
}

HTvoid HTBelt::HT_vBelt_CleanUp()
{
}

HTRESULT HTBelt::HT_hrBelt_init()
{
	m_bBeltActive_Sw = HT_TRUE;

	for( HTint i=0 ; i<3 ; i++ )
	{
		for( HTint j=0 ; j<5 ; j++ )
		{
			m_dwBeltItem_KeyID[i][j] = 0;
		}
	}

	m_vecBeltItemPos = HTvector3( 428, 734, 0 );

#ifndef QUICKSLOT_MODE
	//====================================================================================
	// ���ο�UI����(20030728)
	//====================================================================================
	g_cMainUISystem->HT_hrAddDraw( _DIALOG_BELT );
	//====================================================================================
#endif


	return HT_OK;
}

HTvoid HTBelt::HT_vBelt_Control()
{
}

HTvoid HTBelt::HT_vBelt_Active()
{
}

//----------������ ���� �ִ��� üũ----------//
HTRESULT HTBelt::HT_bBelt_Check_InWindow( HTPoint pPt, HTbool bType )
{
	return HT_FAIL;
}

//----------������ ��ġ ��ȯ----------//
HTvector3 HTBelt::HT_bBelt_GetWindowPos()
{
	return m_vecBeltItemPos;
}

//----------��Ʈ �����찡 Ȱ��ȭ �����ΰ�----------//
HTbool HTBelt::HT_bBeltInventory_GetStatus()
{
	return m_bBeltActive_Sw;
}

//----------������ �����ϱ�----------//
HTvoid HTBelt::HT_bBeltInventory_SetItem( DWORD dwKeyID, HTPoint pCellPos, HTdword dwItemIndex )
{
	m_dwBeltItem_KeyID[0][pCellPos.x] = dwKeyID;
}

//----------������ ����ϱ�----------//
HTvoid HTBelt::HT_bBeltInventory_ItemUse( HTint nIndex )
{
	//	��ŷ�â�� ������������...
	if( g_cExchangeSystem->HT_vExchange_ExchangeWinActive() == HT_TRUE )
		return;

	//	��ǰ���� â�� ����������...
	if( g_cMainUISystem->HT_bBeDraw( _DIALOG_GOODSKEEPING ) == HT_TRUE )
		return;

	// ������ �̵����̸� ó������ ����
	if( g_cItemControl->HT_nItemControl_ItemStatus() == ITEMCONTROL_STATUS_MOVE )
		return;

	HT_ItemReturnRoom sRoom;

	sRoom.nLocation = ITEM_LOCATION_BELT;
	sRoom.nInventory = ITEM_LOCATION_BELT_BELT1;
	sRoom.nCellPosx = nIndex;
	sRoom.nCellPosy = 0;

	//----------������ �����ǰ� �κ��丮 ����ǥ�� ����Ͽ� ������ �O��---------//
	DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sRoom );

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return;
	
	g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( dwItemKeyID, nIndex, 0x01 );
}

//----------��Ʈ��ũ----------//
//----------��Ʈ��ũ_������ ��� ���----------//
HTvoid HTBelt::HT_vNetWork_SCP_RESP_BeltItem_Use_Result( DWORD nIndex )
{
	m_dwBeltItem_KeyID[0][nIndex] = 0;
}

/*
>> ��μ� write:
��ȯâ�� ���ǾƸ� �ѹ� �Է��� ���¿��� [Ȯ��] Ű�� �����ϴ�.
������ �̶��� ���Է����� ���Ǿ� ���� ������ �����մϴ�.
�Դٰ� ������ �� ���·ε� �ڽ����� [Ȯ��] �� Ȱ��ȭ �Ǿ� �־ ������ ������ �÷ȴ� ���Ǿƾ縸 ���� Ȯ���� ����������...
�̷� ��Ȳ�� �ǿ��Ͽ� �������� �ŷ� ���߿� ��Ⱑ �����մϴ�.
*/

