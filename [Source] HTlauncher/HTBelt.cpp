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
	// 새로운UI수정(20030728)
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

//----------윈도우 위에 있는지 체크----------//
HTRESULT HTBelt::HT_bBelt_Check_InWindow( HTPoint pPt, HTbool bType )
{
	return HT_FAIL;
}

//----------윈도우 위치 반환----------//
HTvector3 HTBelt::HT_bBelt_GetWindowPos()
{
	return m_vecBeltItemPos;
}

//----------벨트 윈도우가 활성화 상태인가----------//
HTbool HTBelt::HT_bBeltInventory_GetStatus()
{
	return m_bBeltActive_Sw;
}

//----------아이템 셋팅하기----------//
HTvoid HTBelt::HT_bBeltInventory_SetItem( DWORD dwKeyID, HTPoint pCellPos, HTdword dwItemIndex )
{
	m_dwBeltItem_KeyID[0][pCellPos.x] = dwKeyID;
}

//----------아이템 사용하기----------//
HTvoid HTBelt::HT_bBeltInventory_ItemUse( HTint nIndex )
{
	//	상거래창이 켜져있을때는...
	if( g_cExchangeSystem->HT_vExchange_ExchangeWinActive() == HT_TRUE )
		return;

	//	물품보관 창이 켜져있을때...
	if( g_cMainUISystem->HT_bBeDraw( _DIALOG_GOODSKEEPING ) == HT_TRUE )
		return;

	// 아이템 이동중이면 처리하지 않음
	if( g_cItemControl->HT_nItemControl_ItemStatus() == ITEMCONTROL_STATUS_MOVE )
		return;

	HT_ItemReturnRoom sRoom;

	sRoom.nLocation = ITEM_LOCATION_BELT;
	sRoom.nInventory = ITEM_LOCATION_BELT_BELT1;
	sRoom.nCellPosx = nIndex;
	sRoom.nCellPosy = 0;

	//----------아이템 포지션과 인벤토리 셀좌표를 계산하여 아이템 찿기---------//
	DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sRoom );

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return;
	
	g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( dwItemKeyID, nIndex, 0x01 );
}

//----------네트워크----------//
//----------네트워크_아이템 사용 결과----------//
HTvoid HTBelt::HT_vNetWork_SCP_RESP_BeltItem_Use_Result( DWORD nIndex )
{
	m_dwBeltItem_KeyID[0][nIndex] = 0;
}

/*
>> 김민수 write:
교환창에 루피아를 한번 입력한 상태에서 [확인] 키를 누릅니다.
문제는 이때에 재입력으로 루피아 양을 변경이 가능합니다.
게다가 변경을 한 상태로도 자신쪽의 [확인] 이 활성화 되어 있어서 상대방은 이전에 올렸던 루피아양만 보고 확인을 눌러버리면...
이런 상황을 악용하여 유저간의 거래 도중에 사기가 가능합니다.
*/

