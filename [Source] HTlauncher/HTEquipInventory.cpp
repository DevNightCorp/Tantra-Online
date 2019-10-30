
#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTEquipInventory.h"
#include "HTNPCScriptMgr.h"
#include "HTNPCScriptDef.h"

//#define RUPIAH_WIN_XPOS		300
//#define RUPIAH_WIN_YPOS		300

//#define MESSAGE_WIN_WIDTH		255
//#define MESSAGE_WIN_HEIGHT		128

//#define DIALOC_WIN_SEL_TEXT_HEIGHT	18		// ���ù� ����
//#define DIALOC_WIN_QUE_SEL_SPACE	15		// ���ǹ��� ���ù����� ����

// �޼���â 0:�޼���â�ȶ�,1:�۾��Ϸ�
#define EQUIP_MESSAGE_NONE				0
#define EQUIP_MESSAGE_COMPLETE			1	
#define EQUIP_MESSAGE_CONFIRM			2

#define MONEY_MOVE_NONE						0x00
//#define MONEY_MOVE_INVEN					0x04	// PC �κ�
//#define MONEY_MOVE_GOODSCHARGE				0x05	// NPC �κ�
#define MONEY_MOVE_OFFERING					0x06	// �峳
#define MONEY_MOVE_QUEST					0x07	// ����Ʈ�� ���� �߻�
#define MONEY_MOVE_TRADE					0x08	// Ʈ���̵�â

#define _INVEN_ACTIVE_POS_REVISION			1	// �κ��丮 Ȱ��ȭ�� ���̴� BMP ���� ��ġ
#define _INVEN_INACTIVE_POS_REVISION		-1	// �κ��丮 ��Ȱ��ȭ�� ���̴� BMP ���� ��ġ

// �κ��丮�� Ȯ��� ���·� �α��� ���� ��� ������ Bag Item�� �����ֱ� ���� ������ KeyID 
//#define INVEN_EXPAND_ITEM_KEYID				0	

CHTEquipInventory::CHTEquipInventory()
{
	m_bEquipInventoryActive					= HT_FALSE;
	m_byMessageWin = EQUIP_MESSAGE_NONE;

	m_iPCMoney = m_iNPCMoney = 0;
}

CHTEquipInventory::~CHTEquipInventory()
{
}

HTvoid CHTEquipInventory::HT_vEquipInventory_CeleanUp()
{
	m_byMessageWin = EQUIP_MESSAGE_NONE;
	m_iPCMoney = m_iNPCMoney = 0;
	g_cUIManager->HT_DeleteWindow( _DIALOG_EQUPINVENTORY );
	g_cUIManager->HT_DeleteWindow( _DIALOG_GOODSKEEPWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_INVENTORY2 );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_GOODSKEEPWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHARITYWND1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_CHARITYWND2 );
}

HTRESULT CHTEquipInventory::HT_hrInit()
{
	//	Create Window
	this->HT_vEI_CreateWindow();
	//g_cUIManager->HT_SetMagnet( _DIALOG_INVENTORY2, _DIALOG_EQUPINVENTORY );

	//	����, �����ʿ� ������ ������ �ʱ�ȭ
	m_dwEquip_LeftItem				= 0;
	m_dwEquip_RightItem				= 0;
	m_dwEquip_RightItemKeyID		= 0;

	m_byMessageWin = EQUIP_MESSAGE_NONE;

	m_byFromPlace = m_byToPlace = MONEY_MOVE_NONE;
	m_sBag1.bySize = m_sBag2.bySize = m_sBag3.bySize = 0;
	m_sBag1.bUsable = m_sBag2.bUsable = m_sBag3.bUsable = HT_FALSE;

	m_iPCMoney = m_iNPCMoney = 0;
	//	Inventory Msg Type
	m_iEI_MsgType = 0;

	return HT_OK;
}

//	Create Window
HTvoid CHTEquipInventory::HT_vEI_CreateWindow()
{
	CHTString strMessage;
	HTint i, j;
	//	[Equip Inventory]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgInvenTitle, &strMessage, _T(""), _T("") );	//	Inventory1
	g_cUIManager->HT_CreateWindow( _DIALOG_EQUPINVENTORY, strMessage, 280, 465, g_cEquipInventory->HT_vEI_InputCheckForEquipInven, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_EQUPINVENTORY, 9 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 1, 8, 2, 36, 1400, 274, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 9, 40, 31, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenSubTitle, &strMessage, _T(""), _T("") );	//	�κ��丮
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 90, 19 );
	//	Button ���λ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 3, 159, 207, 214, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenPrivateShop, &strMessage, _T(""), _T("") );	//	���λ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 207, 214, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 3 );
	//	Button ��ǰ��ȯ
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 4, 159, 207, 237, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenTrade, &strMessage, _T(""), _T("") );	//	��ǰ��ȯ
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 207, 237, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 4 );
	//	Button ���Ǿ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 5, 88, 37, 262, 89, 87 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 5 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 265, 56, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 5, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 133, 265, 80, 16 );
	//	Button Ȯ�����
	g_cUIManager->HT_SetScriptMessage( eMsgInvenNoExpansionInven, &strMessage, _T(""), _T("") );	//	�κ��丮 Ȯ������ �ʾ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 438, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_EQUPINVENTORY, 6, 7 );
	//	Button �κ�1
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 7, 185, 238, 283, 186, 184, 1500, 24, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenFirstInven, &strMessage, _T(""), _T("") );	//	ù��° �κ��丮
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_EQUPINVENTORY, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_EQUPINVENTORY, 7 );
	//	Button �κ�1
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 8, 91, 238, 304, 92, 90, 1500, 24, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenSecondInven, &strMessage, _T(""), _T("") );	//	�ι�° �κ��丮
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_EQUPINVENTORY, 8, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_EQUPINVENTORY, 8 );
	//	��	���Ǿ� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 2, 1, 127, 264, 1400, 3, 15 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 3, 1, 211, 263, 1400, 3, 18 );
	//	��	���Ǿ� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 4, 2, 69, 263, 1400, 142, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 5, 2, 69, 278, 1400, 142, 3 );

	//	�� ���� ���� ��
	for( i=0 ; i<7 ; i ++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 1, 24+(i*35), 286, 1400, 3, 140 );

	//	�� ���� ���� ��
	for( i=0 ; i<5 ; i++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 14, 2, 24, 283+(i*35), 1400, 212, 3 );

	//	Slot Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 67, 9, 56 );
	//	Slot Equip ����
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 1, 0, 106, 57 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 1, 2, 2 );
	//	Slot Equip ����
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 2, 0, 106, 98 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 2, 2, 2 );
	//	Slot Equip �㸮��
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 3, 0, 106, 139 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 3, 2, 2 );
	//	Slot Equip ����
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 4, 0, 106, 181 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 4, 2, 2 );
	//	Slot Equip �Ź�
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 5, 0, 106, 223 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 5, 2, 2 );
	//	Slot Equip �����
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 6, 0, 65, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 6, 2, 2 );
	//	Slot Equip �����չ���
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 7, 0, 23, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 7, 2, 2 );
	//	Slot Equip �尩
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 8, 0, 65, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 8, 2, 2 );
	//	Slot Equip ����1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 9, 0, 10, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 9, 2, 2 );
	//	Slot Equip ����2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 11, 0, 45, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 11, 2, 2 );
	//	Slot Equip ����1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 10, 0, 169, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 10, 2, 2 );
	//	Slot Equip ����2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 12, 0, 204, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 12, 2, 2 );
	//	Slot Equip �Ͱ�1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 13, 0, 147, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 13, 2, 2 );
	//	Slot Equip �Ͱ�2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 14, 0, 182, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 14, 2, 2 );
	//	Slot Equip ����or�μչ���
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 15, 0, 147, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 15, 2, 2 );
	//	Slot Equip ����
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 18, 0, 10, 223 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 18, 2, 2 );
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, _SLOTCURRECT_INVEN+i+(j*6), 0, 24+(i*35), 284+(j*35) );
			g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, _SLOTCURRECT_INVEN+i+(j*6), 3, 2);
		}
	}

	//	[_DIALOG_INVENTORY2]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgInvenInventory2, &strMessage, _T(""), _T("") );	//	Inventory2
    g_cUIManager->HT_CreateWindow( _DIALOG_INVENTORY2, strMessage, 280, 180, g_cEquipInventory->HT_vEI_InputCheckForInven2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_INVENTORY2, 9 );
	//	�� ���� ���� ��
	for( i=0 ; i<7 ; i ++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_INVENTORY2, 0, 1, 24+(i*35), 20, 1400, 3, 140 );
	//	�� ���� ���� ��
	for( i=0 ; i<5 ; i++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_INVENTORY2, 14, 2, 24, 20+(i*35), 1400, 212, 3 );
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_INVENTORY2, (_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)+i+(j*6), 0, 24+(i*35), 20+(j*35) );
		}
	}

	//	[_DIALOG_GOODSKEEPWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_GOODSKEEPWND, _T(""), 370, 520, g_cEquipInventory->HT_vEI_InputCheckForGoodsKeep, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_GOODSKEEPWND, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenCargo, &strMessage, _T(""), _T("") );	//	����â��
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	��	���Ǿ� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 127, 490, 1400, 3, 15 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 211, 490, 1400, 3, 15 );
	//	��	���Ǿ� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 2, 69, 490, 1401, 142, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 2, 69, 490, 1401, 142, 3 );
	//	Button ���Ǿ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_GOODSKEEPWND, 1, 88, 40, 490, 89, 87 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 490, 56, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 130, 490, 80, 16 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_GOODSKEEPWND, 1 );
	//	loop
	//	����
	for( i=0 ; i<11 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 3+(i*36), 52, 1400, 3, 432 );
	}
	//	����
	for( i=0 ; i<13 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 2, 3, 52+(i*36), 1400, 360, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<10 ; i++ )
	{
		for( j=0 ; j<12 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_GOODSKEEPWND, 10+((j*_GOODSKEEP_INVEN_WIDTH)+i), 0, 3+(i*36), 53+(j*36) );
		}
	}

	//	[_DIALOG_CHARITYWND1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHARITYWND1, _T(""), 330, 356, g_cEquipInventory->HT_vEI_InputCheckForCharity, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHARITYWND1, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 8, 2, 36, 1400, 326, 6 );
	//	Texture ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenContribution, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Label ���� 1
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain01, &strMessage, _T(""), _T("") );	//	���� ����� ��θ� �ູ���� �����Ͻ� ���Դϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 70, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND1, 6, 7 );
	//	Label ���� 2
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain02, &strMessage, _T(""), _T("") );	//	���� �����κ����� �ູ������ �Ʒ��� �����ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 105, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND1, 7, 7 );
	//	Label ���Ǿ�
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 265, 60, 17 );
	//	Label ���Ǿ� ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 128, 265, 50, 17 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND1, 2, 99, 56, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND1, 2 );
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND1, 3, 99, 157, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND1, 3 );
	//	Texture �峳������1
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 4, 101, 35, 150, 1400, 150, 5 );
	//	Texture �峳������2
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 5, 101, 35, 160, 1400, 150, 5 );
	//	����
	for( i=0 ; i<6 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 1, 59+(i*36), 188, 1400, 3, 69 );
	}
	//	����
	for( i=0 ; i<3 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 2, 59, 185+(i*36), 1400, 183, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<5 ; i++ )
	{
		for( j=0 ; j<2 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_CHARITYWND1, 10+((j*5)+i), 0, 59+(i*36), 184+(j*36) );
		}
	}

	//	[_DIALOG_CHARITYWND2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_CHARITYWND2, _T(""), 330, 356, g_cEquipInventory->HT_vEI_InputCheckForCharity, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_CHARITYWND2, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 8, 2, 36, 1400, 326, 6 );
	//	Texture ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenContribution, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Label ���� 1
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain03, &strMessage, _T(""), _T("") );	//	�ŵ����� �峳���� ������ �� ���������� ���� ���� �� �Դϴ�. �������� ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 70, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND2, 6, 7 );
	//	Label ���� 2
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain04, &strMessage, _T(""), _T("") );	//	ä������ Į�� ���ھ�� ������� 5�а� ���������� ���� �����ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 105, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND2, 7, 7 );
	//	Label ���Ǿ�
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 265, 60, 17 );
	//	Label ���Ǿ� ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 128, 265, 50, 17 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND2, 2, 99, 56, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND2, 2 );
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND2, 3, 99, 157, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND2, 3 );
	//	Texture �峳������1
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 4, 101, 35, 150, 1400, 150, 5 );
	//	Texture �峳������2
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 5, 101, 35, 160, 1400, 150, 5 );
	//	����
	for( i=0 ; i<6 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 1, 59+(i*36), 188, 1400, 3, 69 );
	}
	//	����
	for( i=0 ; i<3 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 2, 59, 185+(i*36), 1400, 183, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<5 ; i++ )
	{
		for( j=0 ; j<2 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_CHARITYWND2, 10+((j*5)+i), 0, 59+(i*36), 184+(j*36) );
		}
	}
}

//	�Է� �޼��� ó��
//	Equip Inventory
void CHTEquipInventory::HT_vEI_InputCheckForEquipInven(int iAction, int iTarget, int iTargetID)
{ 
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
        if( iTargetID == -1 )
		{
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
		}
		//	���Ǿ�
		else if( iTargetID == 5 )
		{
			if (g_cMainCharacter->m_bMainChar_Live == false)	// �������¶�� ���Ǿ� �̵��� �Ұ��ϴ�.
				return;

			// ���Ǿ� �������� ��ġ ����
			g_cEquipInventory->HT_vRupiahWin_SetMoveFromPlace( _DIALOG_EQUPINVENTORY );
			//	Set Message Box
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveRupia, &strMessage, _T(""), _T("") );	//	�̵��� ���ǾƸ� �Է����ּ���.
            g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_RUPIAH, strMessage );
		}
		//	���λ���
		else if( iTargetID == 3 )
		{
			g_cCommand->HT_vCommand_Shop();
		}
		//	��ǰ��ȯ
		else if( iTargetID == 4 )
		{
			g_cCommand->HT_vCommand_Exchange();
		}
		//	����1
		//else if( iTargetID == 7 )
		//{
		//	if( g_cUIManager->HT_isShowWindow( _DIALOG_INVENTORY2 ) )
		//	{
		//		g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
		//	}
		//}
		//	����2
		else if( iTargetID == 8 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_INVENTORY2 ) )
			{
				g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
			}
			else
			{
				//	���� �κ��丮�� ��ġ�� ���ؿͼ� ��2�� �ٷξƷ��� �޾��ش�.
				//	���� �κ��丮 ����� ������ ������ ���� �κ��丮�� ���� ����ش�.
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_EQUPINVENTORY, iPosX, iPosY );
				HTint iBag2PosY = iPosY + 465;
				if( g_pEngineHandler->HT_iGetScreenWidth() != 800 )
				{
					HTint iScreenHeight = g_pEngineHandler->HT_iGetScreenHeight();
					if( (iBag2PosY+180) > (iScreenHeight-55) )
					{
						iPosY = iPosY - ((iBag2PosY+180)-(iScreenHeight-55));
						g_cUIManager->HT_MoveWindow( _DIALOG_EQUPINVENTORY, iPosX, iPosY );
						iBag2PosY = iPosY + 465;
					}
				}
				g_cUIManager->HT_MoveWindow( _DIALOG_INVENTORY2, iPosX, iBag2PosY );
				g_cUIManager->HT_SetMagnetState( _DIALOG_INVENTORY2, HT_TRUE );
	            g_cUIManager->HT_ShowWindow( _DIALOG_INVENTORY2 );
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	���ο� ���
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );
 
		//	Rbutton Click�� ��������
		if( iAction == UI_ACTION_MOUSE_RCLK )
		{
			// ���λ����̳�, �ŷ�â�� ����� �ִٸ� ����
			if (g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE)
				return;

			// �Ҹ� ������(���� ��) ����..
			if( HT_SUCCEED(g_cItemControl->HT_hrItemControl_ItemUse( _DIALOG_EQUPINVENTORY, g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(iTargetID) ) ) )
				return;

			// �Ҹ��� ������ �׿��� ����ŷ ������ ���������� �����Ͽ� �����ϸ� ����ŷ�޽���â ���
			g_cItemControl->m_dwActiveItemKeyID = g_cEquipInventory->m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(iTargetID);
			g_cEquipInventory->m_dwObjectIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(g_cEquipInventory->m_dwObjectKeyID);
			
			// Ư�� �������� ����ŷ�� �Ұ�����
			if (g_cItemControl->HT_bItemControl_IsItemTimeItem(g_cEquipInventory->m_dwObjectIndex) == HT_FALSE) 	return;
            
			g_cEquipInventory->m_nOverlapCount = g_cItemSystem->HT_iItemSystem_GetItemCount(g_cEquipInventory->m_dwObjectKeyID);	// ��ø�� �������
			// �������� PC/NPC�κ��� �ְ� ��ø�� ������ 1���� Ŭ ��쿡�� ����ŷâ ���
			if( g_cEquipInventory->m_nOverlapCount > 1)	 
			{
				// �κ��丮�� �� ������ ���ٸ� �и��Ұ�
				if (!g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck())
				{
					CHTString strMessage;
					g_cUIManager->HT_SetScriptMessage( eMsgInvenNotMoveShortOfInven, &strMessage, _T(""), _T("") );	//	�κ��丮 ������ �����Ͽ� �������� �̵��� �� �����ϴ�.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
					return;
				}

				g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_UNPACKING;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveItem, &strMessage, _T(""), _T("") );	//	�̵��� ������ �Է��� �ּ���.
				g_cUIManager->HT_MessageBox(_DIALOG_EQUPINVENTORY, strMessage, 2);
				// �������� �������� ��ġ ����
				HT_ItemReturnRoom sSourceRoom = g_cItemControl->HT_vItemControl_ActiveEachWindowCheck( iWIndex, iCIndex );
				g_cItemControl->HT_vItemControl_SetMoveFromPlace(_DIALOG_EQUPINVENTORY, sSourceRoom);
				return;
			}
		}
		else
		{
			//	�������� ��� ������ ���� Ŭ��������
			int iDlgNo = _DIALOG_EQUPINVENTORY;
			if( iTargetID == -2 )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}
			else if( iTargetID == -1 )
			{
				iDlgNo = -1;
			}
			
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )	// �������¶�� ������ ����
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			//	�������� Ŭ���ϴ� �������� �̺�Ʈ�� �߻��� ��� �� �׷��� Ŭ���� �������� �˾��Ҽ� �ִ��� Ȯ���ϴ� ������ �ʿ��� �ϴ��� ����� �д�.
			if( HT_FAILED( g_cItemControl->HT_bItemControl_ButtonCheck_SwitchOn( iWIndex, iCIndex, _DIALOG_EQUPINVENTORY, iTargetID ) ) )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}
			if( HT_FAILED( g_cItemControl->HT_vItemControl_ButtonCheck_SwitchOff( iDlgNo, iTargetID ) ) )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			//	������ ���Կ� �������� ������ �������� �ʰ� ó��
			if( g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(iTargetID) == -1 )
			{
				g_cUIManager->HT_AcceptSlotImageMoving();
				g_cUIManager->HT_SetSlotImage( _DIALOG_EQUPINVENTORY, iTargetID , 0 );
			}
			else
			{
				g_cUIManager->HT_AcceptSlotImageMoving();
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		// ����ŷ�� ��ǰ ������ �Է��ߴٸ� �и���Ų��.
		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_UNPACKING)
		{
			if (iTargetID <= 0) return;

			// ����ŷ ������ 0�̸� || ���� �������� ũ�� 
			if( g_cEquipInventory->m_nOverlapCount < iTargetID)
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenWrongInput, &strMessage, _T(""), _T("") );	//	�߸� �Է��ϼ̽��ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
				return;
			}
			else
			{
				g_cItemControl->m_byToPlace = 0;
				g_cItemControl->m_byResent = 1; //RESENT_STEP_PACKING;
				g_cItemControl->m_nUnPackCount = iTargetID;
				g_cItemControl->HT_bItemControl_SetMoveToPlace( _DIALOG_EQUPINVENTORY );
				g_cItemControl->HT_vItemControl_Network_Req_ItemPacking( ITEMPACKING_TYPE_UNPACKING );
			}
		}

		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_NONE )
		{
		}
		//	���� �������ų� ������ ������ ����°�
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWITEM )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			//	Ȯ�� ��ư
			if( iTargetID == 2 )
			{
				g_cItemControl->HT_vItemControl_Network_ReqDrop();
			}
		}
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_RUPIAH )
		{
			//	Set Rupiah
			g_cEquipInventory->m_nRupiah = iTargetID;

			if(g_cNPCControl->m_iDurgaReceiptofMoney == -1) // ���� ����� ��θ���ϰ�쿡�� �����Ŷ ����
			{
				g_cNPCControl->m_iDurgaReceiptofMoney = 0;

				if ( g_cEquipInventory->m_nRupiah < 0 || g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iPCMoney)
				{
					// �̵��� �ݾ��� �������մϴ�
					g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
					// �Ϸ�â ���
					g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_COMPLETE;
					//	Set Message Box
					g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_NONE, g_cEquipInventory->m_szMessage.HT_szGetString() );
				}
				else
				{
					if (g_cEquipInventory->m_nRupiah == 0)
						return;

					g_cNPCControl->HT_vNetWork_CSP_Req_RupiahOffering( g_cEquipInventory->m_nRupiah );
					return;
				}
			}

			// ����ŷ �ݾ��� 0�̸�
			if( ( g_cEquipInventory->m_nRupiah <= 0 && g_cEquipInventory->m_byToPlace != MONEY_MOVE_TRADE )
				|| g_cEquipInventory->m_byFromPlace == MONEY_MOVE_NONE 
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_INVEN && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iPCMoney )
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_CARGO && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iNPCMoney ) )
			{
				if (g_cEquipInventory->m_nRupiah == 0)
					return;

				CHTString strString;
				HT_g_Script_SetMessage( eMsgRupiahMoveAmountErr, &strString );	
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString);

				// �̵��� �ݾ��� �������մϴ�
//				g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
				// �Ϸ�â ���
//				g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_COMPLETE;
				//	Set Message Box
//				g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_NONE, g_cEquipInventory->m_szMessage.HT_szGetString() );
			} 
			else
			{
				// ���Ǿ� �̵��� ��ġ ����
				// ������� - PC �κ��丮
				if( g_cEquipInventory->m_byFromPlace == ITEM_PLACE_INVEN )
				{
					if( g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == HT_TRUE ) // â��
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_GOODSKEEPWND );
					else if ( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE ) // ��ȯâ
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_TRADEWND );
					else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHARITYWND1 ) == HT_TRUE ) // �峳â
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_CHARITYWND1 );
					else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHARITYWND2 ) == HT_TRUE ) // �峳â
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_CHARITYWND2 );
					else
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( -1 );	// �ʿ� ������
				}

				// Ʈ���̵�
				if( g_cEquipInventory->m_byToPlace == MONEY_MOVE_TRADE )
				{
					g_cExchangeSystem->HT_vExchange_SetMoney(g_cEquipInventory->m_nRupiah);
				}
				// �ʿ� ������
				else if( g_cEquipInventory->m_byToPlace == ITEM_PLACE_MAP )
				{
					if (g_cMainCharacter->m_bMainChar_Live == false)	// �������¶�� ���� ������ ����.
						return;

					// ���� ����߸��ðڽ��ϱ�?
					g_cEquipInventory->m_iRupiahResult = g_cEquipInventory->m_nRupiah = iTargetID;
					g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveDropQuestion );
					g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_CONFIRM;
					//	Set Message Box
					g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_THROWRUPIAH, g_cEquipInventory->m_szMessage.HT_szGetString() );
				}
				// �峳
				else if( g_cEquipInventory->m_byToPlace == MONEY_MOVE_OFFERING )
				{
					g_cNPCControl->HT_vNPCControl_Offering_SetRupiah( g_cEquipInventory->m_nRupiah );
				}
				else
				{
					// ���� 20���� �Ѿ������ �����޽��� ���
					int temp = iTargetID + g_cEquipInventory->HT_iEquipInventory_GetNPCMoney();
					if (temp < 0 || temp > 2000000000L) 
					{
						//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "20�� ���Ǿ� �̻� ������ �� �����ϴ�.");
						return;
					}
					
					g_cEquipInventory->HT_vNetwork_CSP_Req_Money_Move();
				}
			}
		}
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWRUPIAH )
		{
			//	OK ��ư
			if( iTargetID == 2 )
			{
				g_cEquipInventory->HT_vRupiahWin_ReqDropMoney( );
			}
		}
	}
}
//	Inventory2
void CHTEquipInventory::HT_vEI_InputCheckForInven2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
			return;
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	���ο� ���
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		// �������� ������ �κ�Ȯ�� ���� ����
		time_t timeTime;
		if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Inven, timeTime ) == HT_FALSE )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		// ���� �ð� ��ȯ
		time_t now; time( &now );
		// Bag2 ���� : ���� �ð��� �κ�Ȯ�� ���� ���� ��
		if( now > timeTime )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		if (g_cEquipInventory->m_bUsableInventory == false) // Ȯ�� �κ��丮�� ����� ������ ����� �۵����� �ʴ´�.
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		////	�ش� ���Կ� �̹� �������� ������
		//if( g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation( iTargetID ) != -1 )
		//{
		//	g_cUIManager->HT_RefuseSlotImageMoving();
		//	return;
		//}
	}
	g_cEquipInventory->HT_vEI_InputCheckForEquipInven( iAction, iTarget, iTargetID );
}
//	Equip GoodsKeep
void CHTEquipInventory::HT_vEI_InputCheckForGoodsKeep(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
		}
		//	���Ǿ�
		else if( iTargetID == 1 )
		{
			// �κ��丮 â�̳� Ȯ�� �κ��丮 â�� ���� �ִٸ� ������ �����ش�.
			//if (g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) == false)
			//	g_cUIManager->HT_ShowWindow( _DIALOG_EQUPINVENTORY );

			g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_RUPIAH;
			// ���Ǿ� �������� ��ġ ����
			g_cEquipInventory->HT_vRupiahWin_SetMoveFromPlace( _DIALOG_GOODSKEEPWND );
			// ���λ��� �Ǹ�â�� ������ ��� ó������ ����
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveRupia, &strMessage, _T(""), _T("") );	//	�̵��� ���ǾƸ� �Է��� �ּ���.
			g_cUIManager->HT_MessageBox( _DIALOG_GOODSKEEPWND, strMessage, UI_MESSAGEBOX_NUMBERINPUT );
			g_cEquipInventory->m_nRupiah = 0;
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );

		if( iAction == UI_ACTION_MOUSE_RCLK )
		{
			// ����â �����ΰ�
			// ����ŷ ������ ���������� �����Ͽ� �����ϸ� ����ŷ�޽���â ���
			g_cItemControl->m_dwActiveItemKeyID = g_cEquipInventory->m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_NPC, ITEM_LOCATION_NPC_ITEMSAVED, iTargetID);
			g_cEquipInventory->m_dwObjectIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(g_cEquipInventory->m_dwObjectKeyID);
			
			// Ư�� �������� ����ŷ�� �Ұ�����
			if (g_cItemControl->HT_bItemControl_IsItemTimeItem(g_cEquipInventory->m_dwObjectIndex) == HT_FALSE) 	return;
            
			g_cEquipInventory->m_nOverlapCount = g_cItemSystem->HT_iItemSystem_GetItemCount(g_cEquipInventory->m_dwObjectKeyID);	// ��ø�� �������
			// �������� PC/NPC�κ��� �ְ� ��ø�� ������ 1���� Ŭ ��쿡�� ����ŷâ ���
			if( g_cEquipInventory->m_nOverlapCount > 1)	 
			{
				// �κ��丮�� �� ������ ���ٸ� �и��Ұ�
				if (!g_cItemSystem->HT_iItemAlSetPosGoodsKeepBlankCheck())
				{
					CHTString strMessage;
					g_cUIManager->HT_SetScriptMessage( eMsgInvenNotMoveShortOfCargo, &strMessage, _T(""), _T("") );	//	â�� ������ �����Ͽ� �������� �̵��� �� �����ϴ�.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
					return;
				}

				g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_UNPACKING;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveItem, &strMessage, _T(""), _T("") );	//	�̵��� ������ �Է��� �ּ���.
				g_cUIManager->HT_MessageBox(_DIALOG_GOODSKEEPWND, strMessage, 2);
				// �������� �������� ��ġ ����
				HT_ItemReturnRoom sSourceRoom = g_cItemControl->HT_vItemControl_ActiveEachWindowCheck( iWIndex, iCIndex );
				g_cItemControl->HT_vItemControl_SetMoveFromPlace(_DIALOG_GOODSKEEPWND, sSourceRoom);
				return;
			}
		}
		else
		{

			//	�������� ��� ������ ���� Ŭ��������
			if( iTargetID == -1 || iTargetID == -2 )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			//	�������� Ŭ���ϴ� �������� �̺�Ʈ�� �߻��� ��� �� �׷��� Ŭ���� �������� �˾��Ҽ� �ִ��� Ȯ���ϴ� ������ �ʿ��� �ϴ��� ����� �д�.
			if( HT_FAILED( g_cItemControl->HT_bItemControl_ButtonCheck_SwitchOn( iWIndex, iCIndex, _DIALOG_GOODSKEEPWND, iTargetID ) ) )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return; 
			}
			if( HT_FAILED( g_cItemControl->HT_vItemControl_ButtonCheck_SwitchOff( _DIALOG_GOODSKEEPWND, iTargetID ) ) )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}
			//	������ ���Կ� �������� ������ �������� �ʰ� ó��
			if( g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_NPC, ITEM_LOCATION_NPC_ITEMSAVED, iTargetID) == 0 )
			{
				g_cUIManager->HT_AcceptSlotImageMoving();
				g_cUIManager->HT_SetSlotImage( _DIALOG_GOODSKEEPWND, iTargetID , 0 );
			}
			else
			{
				g_cUIManager->HT_AcceptSlotImageMoving();
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		// ����ŷ�� ��ǰ ������ �Է��ߴٸ� �и���Ų��.
		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_UNPACKING)
		{
			if (iTargetID <= 0) return;

			// ����ŷ ������ 0�̸� || ���� �������� ũ�� 
			if( g_cEquipInventory->m_nOverlapCount < iTargetID)
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenWrongInput, &strMessage, _T(""), _T("") );	//	�߸� �Է��ϼ̽��ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
				return;
			}
			else
			{
				g_cItemControl->m_byToPlace = 0;
				g_cItemControl->m_byResent = 1; //RESENT_STEP_PACKING;
				g_cItemControl->m_nUnPackCount = iTargetID;
				g_cItemControl->HT_bItemControl_SetMoveToPlace( _DIALOG_GOODSKEEPWND );
				g_cItemControl->HT_vItemControl_Network_Req_ItemPacking( ITEMPACKING_TYPE_UNPACKING );
			}
		}

		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_RUPIAH )
		{
			//if (iTargetID == 2 && g_cEquipInventory->m_byMessageWin == EQUIP_MESSAGE_COMPLETE) return;

			//	Set Rupiah
			g_cEquipInventory->m_nRupiah = iTargetID;

			// ����ŷ �ݾ��� 0�̸�
			if( ( g_cEquipInventory->m_nRupiah <= 0 && g_cEquipInventory->m_byToPlace != MONEY_MOVE_TRADE )
				|| g_cEquipInventory->m_byFromPlace == MONEY_MOVE_NONE 
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_INVEN && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iPCMoney )
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_CARGO && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iNPCMoney ) )
			{
				if (g_cEquipInventory->m_nRupiah == 0)
					return;

				CHTString strString;
				HT_g_Script_SetMessage( eMsgRupiahMoveAmountErr, &strString );	//���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString);

				// �̵��� �ݾ��� �������մϴ�
				//g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
				// �Ϸ�â ���
				//g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_COMPLETE;
				//	Set Message Box
				//g_cUIManager->HT_MessageBox( _DIALOG_GOODSKEEPWND, g_cEquipInventory->m_szMessage.HT_szGetString(), 0 );
			} 
			else
			{
				// ������� - NPC �κ��丮
				if( g_cEquipInventory->m_byFromPlace == ITEM_PLACE_CARGO )
				{
					//	�κ��丮
					//if( g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) == HT_TRUE )
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_EQUPINVENTORY );
					// �ʿ� ������
					//else
					//	g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( -1 );

					// �ʿ� ������
						
					//if( g_cEquipInventory->m_byToPlace == ITEM_PLACE_MAP )
					//{
						// ���� ����߸��ðڽ��ϱ�?
					//	g_cEquipInventory->m_iRupiahResult = g_cEquipInventory->m_nRupiah = iTargetID;
					//	g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveDropQuestion );
					//	g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_CONFIRM;
					//	g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_THROWRUPIAH;
						//	Set Message Box
					//	g_cUIManager->HT_MessageBox( _DIALOG_GOODSKEEPWND, g_cEquipInventory->m_szMessage.HT_szGetString(), 1 );
					//}
					//else
					//{ 

						// ���� 20���� �Ѿ������ �����޽��� ���
						int temp = iTargetID + g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
						if (temp < 0 || temp > 2000000000L) 
						{
							//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "20�� ���Ǿ� �̻� ������ �� �����ϴ�.");
							return;
						}

						g_cEquipInventory->HT_vNetwork_CSP_Req_Money_Move();
					//}
				}
			}
		}
		//else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWRUPIAH )
		//{
			//	OK ��ư
		//	if( iTargetID == 2 )
		//	{
		//		g_cEquipInventory->HT_vRupiahWin_ReqDropMoney( );
		//	}
		//}
	}
}
//	Charity
void CHTEquipInventory::HT_vEI_InputCheckForCharity(int iAction, int iTarget, int iTargetID)
{
	g_cNPCControl->HT_vNPCControl_ButtonCheck_OfferingWin( iAction, iTarget, iTargetID );
}

//	Set Message Box
HTvoid CHTEquipInventory::HT_vEI_SetMessageBox( int iType, CHTString strMsg )
{
	//	Inventory Msg Type
	m_iEI_MsgType = iType;
	if( iType == _MESSAGEBOX_RUPIAH )
	{
		// ���λ��� �Ǹ�â�� ������ ��� ó������ ����
		g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, strMsg, UI_MESSAGEBOX_NUMBERINPUT );
		m_nRupiah = 0;
	}
	else
	{
		//	Show Message Box
		g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, strMsg.HT_szGetString(), 1 );
	}
}

 
//----------�κ��丮â Ȱ��ȭ / ��Ȱ��ȭ----------//
HTRESULT CHTEquipInventory::HT_hrEquipPcInventoryActiveSw()
{
	if( m_bEquipInventoryActive == HT_TRUE )
	{
		HT_vEquipInventory_SetAntiActive();
	}
	else
	{
		HT_vEquipInventory_SetActive();
	}
	
	return HT_OK;
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetActive()
{
	//	���� ������ ���鶧
	//if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) || g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) )
	//	return;

	m_bEquipInventoryActive = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_EQUPINVENTORY );
	
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetAntiActive()
{
	// ����â ������ ����â�� ����� ���� ��� ����â�� �ݴ´�
	if( g_cObjectInfo->HT_bObjectInfo_IsActive() == HT_TRUE )
		g_cObjectInfo->HT_vObjectInfo_AntiActive();

	// ������ �̵����̾��� ���
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive( /*_DIALOG_INVEN*/ );

	m_bEquipInventoryActive = HT_FALSE;

	// â��â�� ���� �ִٸ� â��â�� �ݾ��ش�.
//	if (g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == true)
//		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	g_cUIManager->HT_HideWindow( _DIALOG_EQUPINVENTORY );
	g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
}

// ����� �޼��� ����
HTvoid CHTEquipInventory::HT_vEquipInventory_SetMessage( HTint idMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vEquipInventory_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vEquipInventory_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vEquipInventory_SetParamTextForMessage( sParam3, &szOut3 );

		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vEquipInventory_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vEquipInventory_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vEquipInventory_SetParamTextForMessage( sParam1, &szOut1 );
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		m_szMessage = szString;
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// ���/ȹ���� ��
		case eMsgParamSpendingMoney	:	
			pszParam->HT_szFormat( "%d", m_iRupiahResult );
			break;

		default:
			break;
	}
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetPCMoney(HTint iMoney) 
{ 
	if( iMoney < 0 )
		m_iPCMoney = 0;
	else
		m_iPCMoney = iMoney;

	CHTString strTemp;
	//strTemp.HT_szFormat( "%d", m_iPCMoney );
	strTemp = g_cUIManager->HT_strSetRestMark(m_iPCMoney);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_EQUPINVENTORY, 5, strTemp.HT_szGetString() );
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetNPCMoney(HTint iMoney) 
{ 
	if( iMoney < 0 )
		m_iNPCMoney = 0;
	else
		m_iNPCMoney = iMoney;
	
	CHTString strTemp;
	//strTemp.HT_szFormat( "%d", m_iNPCMoney );
	strTemp = g_cUIManager->HT_strSetRestMark(m_iNPCMoney);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_GOODSKEEPWND, 1, strTemp.HT_szGetString() );
}

//---------���Ǿ� ����ŷ ������ ����--------//
HTvoid CHTEquipInventory::HT_vRupiahWin_Active()
{
	// ���λ��� �Ǹ�â�� ������ ��� ó������ ����
	g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, _T(""), UI_MESSAGEBOX_NUMBERINPUT );
    m_nRupiah = 0;
	m_iEI_MsgType = _MESSAGEBOX_RUPIAH;
}

// ���ǾƸ� �������� ��ġ ����
HTvoid CHTEquipInventory::HT_vRupiahWin_SetMoveFromPlace( HTint nDlgNo )
{
	switch(nDlgNo)
	{
		case _DIALOG_EQUPINVENTORY:	// PC �κ��丮
			m_byFromPlace = ITEM_PLACE_INVEN;
			break;
		case _DIALOG_GOODSKEEPWND:	// NPC �κ��丮
			m_byFromPlace = ITEM_PLACE_CARGO;
			break;
		case _DIALOG_TRADEWND:		// Ʈ���̵�
			m_byFromPlace = MONEY_MOVE_TRADE;
			break;
		default:
			m_byFromPlace = MONEY_MOVE_NONE;
			break;
	}
}

// ���ǾƸ� �̵��� ��ġ ����
HTvoid CHTEquipInventory::HT_vRupiahWin_SetMoveToPlace( HTint nDlgNo )
{
	switch(nDlgNo)
	{
		case _DIALOG_EQUPINVENTORY:				// PC �κ��丮
			m_byToPlace = ITEM_PLACE_INVEN;
			break;
		case _DIALOG_GOODSKEEPWND:		// NPC �κ��丮
			m_byToPlace = ITEM_PLACE_CARGO;
			break;
		case _DIALOG_TRADEWND:			// Ʈ���̵�
			m_byToPlace = MONEY_MOVE_TRADE;
			break;
		case _DIALOG_CHARITYWND1:	// �ູ�� �Ŵ�
		case _DIALOG_CHARITYWND2:	// Ʈ�縶 �ŷ�
			m_byToPlace = MONEY_MOVE_OFFERING;
			break;
		default:
			m_byToPlace = ITEM_PLACE_MAP;
			break;
	}
}

//------- �ʿ� ���Ǿ� ������ -----------//
HTvoid CHTEquipInventory::HT_vRupiahWin_ReqDropMoney( )
{
	PS_CSP_REQ_ITEM_DROP info = NULL;
	info = new S_CSP_REQ_ITEM_DROP;

	// �������� �ִ� ���� ��ġ
	info->byFromPlace = m_byFromPlace;
	info->byIndex = 255;
	info->dwMoney = m_nRupiah;

	// �������� �̵��� ��ġ
	HTPoint pPt = g_cItemControl->HT_ptItemControl_SearchMapPosForItemDrop();
	if( pPt.x < 0 || pPt.y < 0 )
	{
		HT_DELETE( info );
		return;
	}

	info->snX = pPt.x;
	info->snZ = pPt.y;

	g_pNetWorkMgr->RequestItemDrop( info );
	 
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqDropMoney : %d, From(%d:%d), To(%d,%d)", 
	//											info->dwMoney, info->byFromPlace, info->byIndex, info->snX, info->snZ);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetLeftItem( DWORD dwLeftItem )
{
	m_dwEquip_LeftItem = dwLeftItem;
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetRightItem( DWORD dwRightItem )
{
	m_dwEquip_RightItem = dwRightItem;
	//	����ĳ���� �������̸� ���
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 2 );
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetRightItem_KeyID( DWORD dwItemKeyID )
{
	m_dwEquip_RightItemKeyID = dwItemKeyID;
}

// ���ʿ� ������ �������� Index ��ȯ
DWORD CHTEquipInventory::HT_dwEquipInventory_GetLeftItem()
{
	return m_dwEquip_LeftItem;
}
// �����ʿ� ������ �������� Index ��ȯ
DWORD CHTEquipInventory::HT_dwEquipInventory_GetRightItem()
{
	return m_dwEquip_RightItem;
}

DWORD CHTEquipInventory::HT_dwEquipInventory_GetRightItem_KeyID()
{
	return m_dwEquip_RightItemKeyID;
}

// �κ��丮 ũ�� ���ϱ�
HTbyte CHTEquipInventory::HT_byGetInventorySize( HTint nInventory )
{
	HTbyte bySize = 0;

	if( nInventory == ITEM_LOCATION_PC_BAG1 )
		bySize = m_sBag1.bySize;
	else if( nInventory == ITEM_LOCATION_PC_BAG2 )
		bySize = m_sBag2.bySize;
	else if( nInventory == ITEM_LOCATION_PC_BAG3 )
		bySize = m_sBag3.bySize;
	else
		bySize = 0;

	return bySize;
}

// �κ��丮 ��밡�� ����
HTbool CHTEquipInventory::HT_bGetInventoryUsable( HTint nInventory )
{
	if( nInventory == ITEM_LOCATION_PC_BAG1 )
		return m_sBag1.bUsable;
	else if( nInventory == ITEM_LOCATION_PC_BAG2 )
		return m_sBag2.bUsable;
	else if( nInventory == ITEM_LOCATION_PC_BAG3 )
		return m_sBag3.bUsable;
	else
		return HT_FALSE;
}

// �ش� ������ŭ �κ��丮 ������ �ִ� ���� Ȯ�� 2004. 11. 29 ������
HTbool CHTEquipInventory::HT_bGetInventoryBlank( HTint nNum )
{
	// ����, ��밡���� �κ��丮�� ũ�⸦ ���ؿ´�.

	return HT_FALSE;
}

// �κ��丮 ũ�� �ʱ� ����
HTvoid CHTEquipInventory::HT_vInitBagStatus( )
{
	if( g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
		g_cUIManager->HT_ShowWindow(_DIALOG_EQUPINVENTORY);

	// Bag1�� �⺻ ��� ����
	HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG1, _INVEN_WIDTH);
	// Bag3�� ���Ұ�
	HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG3, 0 );

	// �������� ������ �κ�Ȯ�� ���� ����
	time_t timeTime;
	if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Inven, timeTime ) == HT_FALSE )
		return;
	
	if( timeTime <= 0 ) // �κ�Ȯ�� ���񽺸� ��û�غ� ���� ����
	{
		HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 ��� �Ұ���
	}
	else
	{
		// ���� �ð� ��ȯ
		time_t now; time( &now );

		// Bag2 ���� : ���� �ð��� �κ�Ȯ�� ���� ���� ��
		if( now <= timeTime )
		{
			HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); // Bag2 ��밡��

			// Ȯ����� ǥ���ϱ�
			CHTString szTime;
			g_cMainCharacter->HT_vMainChar_GetTimeStamp( 254, szTime );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_EQUPINVENTORY, 6, szTime.HT_szGetString() );
		}
		else
			HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 ��� �Ұ���
	}
}


// ��� �Ұ����� �κ��丮 ǥ�� �ٽ� �׸���
HTvoid CHTEquipInventory::HT_vRenewalPossibleBar( HTint iInventory, HTbyte byNewSize, HTbool bUsable )
{
	if( byNewSize > _INVEN_WIDTH || byNewSize < 0 )	// ���� �κ��丮 ũ�⺸�� Ŭ ���
		return;

	// ���� ��� �Ұ��� ǥ�� �����
	HT_vDelPossibleBar(iInventory);

	// ���ο� ������� �����ϰ� �׸���
	if( iInventory == ITEM_LOCATION_PC_BAG1 )
	{
		m_sBag1.bySize = byNewSize;
		m_sBag1.bUsable = bUsable;
	}
	else if( iInventory == ITEM_LOCATION_PC_BAG2 )
	{
		m_sBag2.bySize = byNewSize;
		m_sBag2.bUsable = bUsable;
	}
	else if( iInventory == ITEM_LOCATION_PC_BAG3 )
	{
		m_sBag3.bySize = byNewSize;
		m_sBag3.bUsable = bUsable;
	}
    else
		return;

	// x��ǥ ���ϱ�(y�� �׻� 0)
	//HTint iSizeX = _INVEN_WIDTH - byNewSize ;
	//HTint iColNo = _INVEN_WIDTH - iSizeX;

	//if( iColNo >= 0 && iSizeX > 0 )
	if( bUsable == HT_FALSE )
	{
		m_bUsableInventory = bUsable;
		// ��� �Ұ����� �κ��丮 �κ��� Bitmap���� �ٲ۴�
		for( HTint i=0 ; i<6 ; i++ )
		{
			for( HTint j=0 ; j<4 ; j++ )
			{
				g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INVENTORY2, (_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)+i+(j*6), bUsable );
			}
		}
	}
}

// ��� �Ұ����� �κ��丮 ǥ�� ����
HTvoid CHTEquipInventory::HT_vDelPossibleBar( HTint iInventory )
{
	if( iInventory < ITEM_LOCATION_PC_BAG1  || iInventory > ITEM_LOCATION_PC_BAG3 )
		return;

	HTint iColNo = 0;
	//if( iInventory == ITEM_LOCATION_PC_BAG1 )
	//{
	//	iColNo = m_sBag1.bySize;
	//}
	//else if( iInventory == ITEM_LOCATION_PC_BAG2 )
	//{
	//	iColNo = m_sBag2.bySize;
	//}
	//else if( iInventory == ITEM_LOCATION_PC_BAG3 )
	//{
	//	iColNo = m_sBag3.bySize;
	//}
	//else
	//	return;

	// x��ǥ ���ϱ�(y�� �׻� 0)
	HTint iSizeX = _INVEN_WIDTH - iColNo ;
	//iColNo = _INVEN_WIDTH - iSizeX;
	if( iColNo >= 0 && iSizeX > 0 )
	{
		m_bUsableInventory = true;

		// ��� �Ұ����� �κ��丮 �κ��� Bitmap���� �ٲ۴�
		for( HTint i=0 ; i<6 ; i++ )
		{
			for( HTint j=0 ; j<4 ; j++ )
			{
				g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INVENTORY2, (_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)+i+(j*6), HT_TRUE );
			}
		}
	}
}

//--------- ���Ǿ� �̵� ��û ----------//
HTvoid CHTEquipInventory::HT_vNetwork_CSP_Req_Money_Move()
{
	MSG_Money_Move* info = HT_NULL;
	info = new MSG_Money_Move;

	info->byFromPlace = m_byFromPlace;
	info->byToPlace = m_byToPlace;
	info->dwMoney = m_nRupiah;

	g_pNetWorkMgr->RequestMoneyMove( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqMoneyMove : %d(From:%x To:%x)", 
	//															m_nRupiah, m_byFromPlace, m_byToPlace );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTEquipInventory::HT_vNetwork_SCP_Resp_Money_Move( MSG_Money_Move* info )
{
	// ������ ���� �����´�
	m_bMessage_Error = HT_FALSE;	// ���� ����

	// ���� ��ġ�� ���Ǿ� ����
	if( info->byFromPlace == ITEM_PLACE_INVEN )			// PC �κ��丮
		HT_vEquipInventory_SetPCMoney( info->dwFromMoney ) ;

	else if( info->byFromPlace == ITEM_PLACE_CARGO )	// NPC �κ��丮
		HT_vEquipInventory_SetNPCMoney( info->dwFromMoney );

	m_szMessage.HT_hrCleanUp();

	// �̵� ��ġ�� ���Ǿ� ����
	if(  info->byToPlace == ITEM_PLACE_INVEN )			// PC �κ��丮
	{
		// �̵�/���/���� ���Ǿ� �ݾ�
		m_iRupiahResult = info->dwToMoney - m_iPCMoney;
		if( m_iRupiahResult < 0 )
			m_iRupiahResult = 0;

		if( info->byFromPlace == ITEM_PLACE_QUEST )	// ����Ʈ�κ��� �߻�
		{
			if( m_iRupiahResult == 0 )
			{
				m_iRupiahResult = m_iPCMoney - info->dwToMoney;
				// ����Ʈ�� ���� %d ���ǾƸ� �Һ��߽��ϴ�.
				HT_vEquipInventory_SetMessage( eMsgRupiahSpendingQuest );
			}
			else
				// %d ���ǾƸ� �޾ҽ��ϴ�.
				HT_vEquipInventory_SetMessage( eMsgRupiahReceiveQuest );
		}
		else if( info->byFromPlace == ITEM_PLACE_PORTAL )	// ��Ż ��뿡 ���� ���� ���ҵ� ���
		{	
			if( m_iRupiahResult == 0 )
				m_iRupiahResult = m_iPCMoney - info->dwToMoney;
			
			// ��Ż �̿����� %d ���ǾƸ� �Һ��߽��ϴ�.
			HT_vEquipInventory_SetMessage( eMsgRupiahSpendingPortal );
		}
		else if( info->byFromPlace == ITEM_PLACE_EVENT )	// �̺�Ʈ�κ��� �߻�
		{
			// %d ���ǾƸ� ȹ���߽��ϴ�.
			HT_vEquipInventory_SetMessage( eMsgRupiahReceive );
		}
		else 
		{
			// PC�κ��丮�� %d ���ǾƸ� �Ű���ϴ�.
			HT_vEquipInventory_SetMessage( eMsgRupiahMoveToPCInven );
		}

		HT_vEquipInventory_SetPCMoney( info->dwToMoney );
	}
	else if(  info->byToPlace == ITEM_PLACE_CARGO )	// NPC �κ��丮
	{
		// �̵� ���Ǿ� �ݾ�
		m_iRupiahResult = info->dwToMoney - m_iNPCMoney;
		if( m_iRupiahResult < 0 )
			m_iRupiahResult = 0;

		HT_vEquipInventory_SetNPCMoney( info->dwToMoney );
		
		// NPC�κ��丮�� %d���ǾƸ� �Ű���ϴ�.
		HT_vEquipInventory_SetMessage( eMsgRupiahMoveToNPCInven );
	}
	else
		return;
	
	// �ý��� â�� ǥ��
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

