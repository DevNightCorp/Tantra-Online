
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

//#define DIALOC_WIN_SEL_TEXT_HEIGHT	18		// 선택문 간격
//#define DIALOC_WIN_QUE_SEL_SPACE	15		// 질의문과 선택문과의 간격

// 메세지창 0:메세지창안뜸,1:작업완료
#define EQUIP_MESSAGE_NONE				0
#define EQUIP_MESSAGE_COMPLETE			1	
#define EQUIP_MESSAGE_CONFIRM			2

#define MONEY_MOVE_NONE						0x00
//#define MONEY_MOVE_INVEN					0x04	// PC 인벤
//#define MONEY_MOVE_GOODSCHARGE				0x05	// NPC 인벤
#define MONEY_MOVE_OFFERING					0x06	// 헌납
#define MONEY_MOVE_QUEST					0x07	// 퀘스트에 의해 발생
#define MONEY_MOVE_TRADE					0x08	// 트레이드창

#define _INVEN_ACTIVE_POS_REVISION			1	// 인벤토리 활성화시 붙이는 BMP 보정 위치
#define _INVEN_INACTIVE_POS_REVISION		-1	// 인벤토리 비활성화시 붙이는 BMP 보정 위치

// 인벤토리가 확장된 상태로 로그인 했을 경우 가상의 Bag Item을 보여주기 위한 임의의 KeyID 
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

	//	왼쪽, 오른쪽에 장착되 아이템 초기화
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
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 1, 8, 2, 36, 1400, 274, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 9, 40, 31, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenSubTitle, &strMessage, _T(""), _T("") );	//	인벤토리
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 90, 19 );
	//	Button 개인상점
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 3, 159, 207, 214, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenPrivateShop, &strMessage, _T(""), _T("") );	//	개인상점
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 207, 214, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 3 );
	//	Button 물품교환
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 4, 159, 207, 237, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenTrade, &strMessage, _T(""), _T("") );	//	물품교환
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 207, 237, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 4 );
	//	Button 루피아
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 5, 88, 37, 262, 89, 87 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_EQUPINVENTORY, 5 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 265, 56, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 5, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 133, 265, 80, 16 );
	//	Button 확장기한
	g_cUIManager->HT_SetScriptMessage( eMsgInvenNoExpansionInven, &strMessage, _T(""), _T("") );	//	인벤토리 확장하지 않았음
	g_cUIManager->HT_AddLabelControl( _DIALOG_EQUPINVENTORY, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 438, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_EQUPINVENTORY, 6, 7 );
	//	Button 인벤1
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 7, 185, 238, 283, 186, 184, 1500, 24, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenFirstInven, &strMessage, _T(""), _T("") );	//	첫번째 인벤토리
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_EQUPINVENTORY, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_EQUPINVENTORY, 7 );
	//	Button 인벤1
	g_cUIManager->HT_AddButtonControl( _DIALOG_EQUPINVENTORY, 8, 91, 238, 304, 92, 90, 1500, 24, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenSecondInven, &strMessage, _T(""), _T("") );	//	두번째 인벤토리
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_EQUPINVENTORY, 8, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_EQUPINVENTORY, 8 );
	//	줄	루피아 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 2, 1, 127, 264, 1400, 3, 15 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 3, 1, 211, 263, 1400, 3, 18 );
	//	줄	루피아 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 4, 2, 69, 263, 1400, 142, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 5, 2, 69, 278, 1400, 142, 3 );

	//	줄 슬롯 세로 줄
	for( i=0 ; i<7 ; i ++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 1, 24+(i*35), 286, 1400, 3, 140 );

	//	줄 슬롯 가로 줄
	for( i=0 ; i<5 ; i++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 14, 2, 24, 283+(i*35), 1400, 212, 3 );

	//	Slot Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_EQUPINVENTORY, 0, 67, 9, 56 );
	//	Slot Equip 투구
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 1, 0, 106, 57 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 1, 2, 2 );
	//	Slot Equip 갑옷
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 2, 0, 106, 98 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 2, 2, 2 );
	//	Slot Equip 허리띠
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 3, 0, 106, 139 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 3, 2, 2 );
	//	Slot Equip 바지
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 4, 0, 106, 181 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 4, 2, 2 );
	//	Slot Equip 신발
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 5, 0, 106, 223 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 5, 2, 2 );
	//	Slot Equip 목걸이
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 6, 0, 65, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 6, 2, 2 );
	//	Slot Equip 오른손무기
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 7, 0, 23, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 7, 2, 2 );
	//	Slot Equip 장갑
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 8, 0, 65, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 8, 2, 2 );
	//	Slot Equip 팔찌1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 9, 0, 10, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 9, 2, 2 );
	//	Slot Equip 팔찌2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 11, 0, 45, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 11, 2, 2 );
	//	Slot Equip 반지1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 10, 0, 169, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 10, 2, 2 );
	//	Slot Equip 반지2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 12, 0, 204, 147 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 12, 2, 2 );
	//	Slot Equip 귀고리1
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 13, 0, 147, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 13, 2, 2 );
	//	Slot Equip 귀고리2
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 14, 0, 182, 67 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 14, 2, 2 );
	//	Slot Equip 방패or두손무기
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_EQUPINVENTORY, 15, 0, 147, 107 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_EQUPINVENTORY, 15, 2, 2 );
	//	Slot Equip 부적
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
	//	줄 슬롯 세로 줄
	for( i=0 ; i<7 ; i ++ )
		g_cUIManager->HT_AddTextureControl( _DIALOG_INVENTORY2, 0, 1, 24+(i*35), 20, 1400, 3, 140 );
	//	줄 슬롯 가로 줄
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenCargo, &strMessage, _T(""), _T("") );	//	개인창고
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	줄	루피아 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 127, 490, 1400, 3, 15 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 211, 490, 1400, 3, 15 );
	//	줄	루피아 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 2, 69, 490, 1401, 142, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 2, 69, 490, 1401, 142, 3 );
	//	Button 루피아
	g_cUIManager->HT_AddButtonControl( _DIALOG_GOODSKEEPWND, 1, 88, 40, 490, 89, 87 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 490, 56, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_GOODSKEEPWND, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 130, 490, 80, 16 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_GOODSKEEPWND, 1 );
	//	loop
	//	세로
	for( i=0 ; i<11 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_GOODSKEEPWND, 0, 1, 3+(i*36), 52, 1400, 3, 432 );
	}
	//	가로
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 8, 2, 36, 1400, 326, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenContribution, &strMessage, _T(""), _T("") );	//	기부
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Label 설명 1
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain01, &strMessage, _T(""), _T("") );	//	신은 당신의 기부를 축복으로 보답하실 것입니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 70, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND1, 6, 7 );
	//	Label 설명 2
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain02, &strMessage, _T(""), _T("") );	//	현재 신으로부터의 축복정도는 아래와 같습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 105, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND1, 7, 7 );
	//	Label 루피아
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 265, 60, 17 );
	//	Label 루피아 값
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 128, 265, 50, 17 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND1, 2, 99, 56, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND1, 2 );
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND1, 3, 99, 157, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND1, 3 );
	//	Texture 헌납게이지1
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 4, 101, 35, 150, 1400, 150, 5 );
	//	Texture 헌납게이지2
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 5, 101, 35, 160, 1400, 150, 5 );
	//	세로
	for( i=0 ; i<6 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND1, 0, 1, 59+(i*36), 188, 1400, 3, 69 );
	}
	//	가로
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 8, 2, 36, 1400, 326, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgInvenContribution, &strMessage, _T(""), _T("") );	//	기부
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Label 설명 1
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain03, &strMessage, _T(""), _T("") );	//	신도들의 헌납으로 시험의 문 차투랑가의 문이 열릴 것 입니다. 게이지가 모두
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 30, 70, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND2, 6, 7 );
	//	Label 설명 2
	g_cUIManager->HT_SetScriptMessage( eMsgInvenExplain04, &strMessage, _T(""), _T("") );	//	채워지면 칼라 스코어와 관계없이 5분간 차투랑가의 문이 열립니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 105, 270, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_CHARITYWND2, 7, 7 );
	//	Label 루피아
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 265, 60, 17 );
	//	Label 루피아 값
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 1, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 128, 265, 50, 17 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND2, 2, 99, 56, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND2, 2 );
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_CHARITYWND2, 3, 99, 157, 313, 97, 98, 1500, 89, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
	g_cUIManager->HT_AddLabelControl( _DIALOG_CHARITYWND2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 313, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_CHARITYWND2, 3 );
	//	Texture 헌납게이지1
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 4, 101, 35, 150, 1400, 150, 5 );
	//	Texture 헌납게이지2
	g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 5, 101, 35, 160, 1400, 150, 5 );
	//	세로
	for( i=0 ; i<6 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_CHARITYWND2, 0, 1, 59+(i*36), 188, 1400, 3, 69 );
	}
	//	가로
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

//	입력 메세지 처리
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
		//	루피아
		else if( iTargetID == 5 )
		{
			if (g_cMainCharacter->m_bMainChar_Live == false)	// 죽은상태라면 루피아 이동이 불가하다.
				return;

			// 루피아 보관중인 위치 설정
			g_cEquipInventory->HT_vRupiahWin_SetMoveFromPlace( _DIALOG_EQUPINVENTORY );
			//	Set Message Box
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveRupia, &strMessage, _T(""), _T("") );	//	이동할 루피아를 입력해주세요.
            g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_RUPIAH, strMessage );
		}
		//	개인상점
		else if( iTargetID == 3 )
		{
			g_cCommand->HT_vCommand_Shop();
		}
		//	물품교환
		else if( iTargetID == 4 )
		{
			g_cCommand->HT_vCommand_Exchange();
		}
		//	슬롯1
		//else if( iTargetID == 7 )
		//{
		//	if( g_cUIManager->HT_isShowWindow( _DIALOG_INVENTORY2 ) )
		//	{
		//		g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
		//	}
		//}
		//	슬롯2
		else if( iTargetID == 8 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_INVENTORY2 ) )
			{
				g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
			}
			else
			{
				//	현재 인벤토리의 위치를 구해와서 백2를 바로아래에 달아준다.
				//	만약 인벤토리 사이즈가 나오지 않으면 원래 인벤토리도 위로 댕겨준다.
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
		//	윈두우 배경
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );
 
		//	Rbutton Click이 들어왔을때
		if( iAction == UI_ACTION_MOUSE_RCLK )
		{
			// 개인상점이나, 거래창이 띄어져 있다면 리턴
			if (g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE)
				return;

			// 소모성 아이템(물약 등) 인지..
			if( HT_SUCCEED(g_cItemControl->HT_hrItemControl_ItemUse( _DIALOG_EQUPINVENTORY, g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(iTargetID) ) ) )
				return;

			// 소모성을 제외한 그외의 언패킹 가능한 아이템인지 조사하여 가능하면 언패킹메시지창 띄움
			g_cItemControl->m_dwActiveItemKeyID = g_cEquipInventory->m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(iTargetID);
			g_cEquipInventory->m_dwObjectIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(g_cEquipInventory->m_dwObjectKeyID);
			
			// 특정 아이템은 언패킹이 불가능함
			if (g_cItemControl->HT_bItemControl_IsItemTimeItem(g_cEquipInventory->m_dwObjectIndex) == HT_FALSE) 	return;
            
			g_cEquipInventory->m_nOverlapCount = g_cItemSystem->HT_iItemSystem_GetItemCount(g_cEquipInventory->m_dwObjectKeyID);	// 중첩된 개수얻기
			// 아이템이 PC/NPC인벤에 있고 중첩된 개수가 1보다 클 경우에만 언패킹창 띄움
			if( g_cEquipInventory->m_nOverlapCount > 1)	 
			{
				// 인벤토리에 빈 공간이 없다면 분리불가
				if (!g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck())
				{
					CHTString strMessage;
					g_cUIManager->HT_SetScriptMessage( eMsgInvenNotMoveShortOfInven, &strMessage, _T(""), _T("") );	//	인벤토리 공간이 부족하여 아이템을 이동할 수 없습니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
					return;
				}

				g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_UNPACKING;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveItem, &strMessage, _T(""), _T("") );	//	이동할 개수를 입력해 주세요.
				g_cUIManager->HT_MessageBox(_DIALOG_EQUPINVENTORY, strMessage, 2);
				// 아이템을 보관중인 위치 설정
				HT_ItemReturnRoom sSourceRoom = g_cItemControl->HT_vItemControl_ActiveEachWindowCheck( iWIndex, iCIndex );
				g_cItemControl->HT_vItemControl_SetMoveFromPlace(_DIALOG_EQUPINVENTORY, sSourceRoom);
				return;
			}
		}
		else
		{
			//	아이콘을 들고 엉뚱한 곳에 클릭했을때
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
			
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )	// 죽은상태라면 무조건 실패
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			//	아이콘을 클릭하는 순간에도 이벤트가 발생해 줘야 함 그래서 클릭한 아이콘을 팝업할수 있는지 확인하는 절차가 필요함 일단은 여기다 둔다.
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

			//	기존의 슬롯에 아이템이 있으면 덮어지지 않게 처리
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
		// 언패킹할 물품 개수를 입력했다면 분리시킨다.
		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_UNPACKING)
		{
			if (iTargetID <= 0) return;

			// 언패킹 개수가 0이면 || 가진 개수보다 크면 
			if( g_cEquipInventory->m_nOverlapCount < iTargetID)
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenWrongInput, &strMessage, _T(""), _T("") );	//	잘못 입력하셨습니다.
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
		//	땅에 돈버리거나 아이템 버릴때 물어보는것
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWITEM )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			//	확인 버튼
			if( iTargetID == 2 )
			{
				g_cItemControl->HT_vItemControl_Network_ReqDrop();
			}
		}
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_RUPIAH )
		{
			//	Set Rupiah
			g_cEquipInventory->m_nRupiah = iTargetID;

			if(g_cNPCControl->m_iDurgaReceiptofMoney == -1) // 만약 요새전 기부모드일경우에는 기부패킷 전송
			{
				g_cNPCControl->m_iDurgaReceiptofMoney = 0;

				if ( g_cEquipInventory->m_nRupiah < 0 || g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iPCMoney)
				{
					// 이동할 금액이 부적합합니다
					g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
					// 완료창 띄움
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

			// 언패킹 금액이 0이면
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

				// 이동할 금액이 부적합합니다
//				g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
				// 완료창 띄움
//				g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_COMPLETE;
				//	Set Message Box
//				g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_NONE, g_cEquipInventory->m_szMessage.HT_szGetString() );
			} 
			else
			{
				// 루피아 이동할 위치 설정
				// 보관장소 - PC 인벤토리
				if( g_cEquipInventory->m_byFromPlace == ITEM_PLACE_INVEN )
				{
					if( g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == HT_TRUE ) // 창고
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_GOODSKEEPWND );
					else if ( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE ) // 교환창
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_TRADEWND );
					else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHARITYWND1 ) == HT_TRUE ) // 헌납창
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_CHARITYWND1 );
					else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHARITYWND2 ) == HT_TRUE ) // 헌납창
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_CHARITYWND2 );
					else
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( -1 );	// 맵에 버리기
				}

				// 트레이드
				if( g_cEquipInventory->m_byToPlace == MONEY_MOVE_TRADE )
				{
					g_cExchangeSystem->HT_vExchange_SetMoney(g_cEquipInventory->m_nRupiah);
				}
				// 맵에 버리기
				else if( g_cEquipInventory->m_byToPlace == ITEM_PLACE_MAP )
				{
					if (g_cMainCharacter->m_bMainChar_Live == false)	// 죽은상태라면 땅에 버릴수 없다.
						return;

					// 땅에 떨어뜨리시겠습니까?
					g_cEquipInventory->m_iRupiahResult = g_cEquipInventory->m_nRupiah = iTargetID;
					g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveDropQuestion );
					g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_CONFIRM;
					//	Set Message Box
					g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_THROWRUPIAH, g_cEquipInventory->m_szMessage.HT_szGetString() );
				}
				// 헌납
				else if( g_cEquipInventory->m_byToPlace == MONEY_MOVE_OFFERING )
				{
					g_cNPCControl->HT_vNPCControl_Offering_SetRupiah( g_cEquipInventory->m_nRupiah );
				}
				else
				{
					// 만약 20억이 넘어버리면 에러메시지 출력
					int temp = iTargetID + g_cEquipInventory->HT_iEquipInventory_GetNPCMoney();
					if (temp < 0 || temp > 2000000000L) 
					{
						//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "20억 루피아 이상 저장할 수 없습니다.");
						return;
					}
					
					g_cEquipInventory->HT_vNetwork_CSP_Req_Money_Move();
				}
			}
		}
		else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWRUPIAH )
		{
			//	OK 버튼
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
		//	윈두우 배경
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		// 서버에서 내려온 인벤확장 서비스 기한
		time_t timeTime;
		if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Inven, timeTime ) == HT_FALSE )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		// 현재 시간 변환
		time_t now; time( &now );
		// Bag2 설정 : 현재 시간과 인벤확장 서비스 기한 비교
		if( now > timeTime )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		if (g_cEquipInventory->m_bUsableInventory == false) // 확장 인벤토리의 사용이 금지된 경우라면 작동하지 않는다.
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		////	해당 슬롯에 이미 아이콘이 있을때
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
		//	루피아
		else if( iTargetID == 1 )
		{
			// 인벤토리 창이나 확장 인벤토리 창이 닫혀 있다면 강제로 열어준다.
			//if (g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) == false)
			//	g_cUIManager->HT_ShowWindow( _DIALOG_EQUPINVENTORY );

			g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_RUPIAH;
			// 루피아 보관중인 위치 설정
			g_cEquipInventory->HT_vRupiahWin_SetMoveFromPlace( _DIALOG_GOODSKEEPWND );
			// 개인상점 판매창이 떠있을 경우 처리하지 않음
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveRupia, &strMessage, _T(""), _T("") );	//	이동할 루피아를 입력해 주세요.
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
			// 분해창 띄울것인가
			// 언패킹 가능한 아이템인지 조사하여 가능하면 언패킹메시지창 띄움
			g_cItemControl->m_dwActiveItemKeyID = g_cEquipInventory->m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_NPC, ITEM_LOCATION_NPC_ITEMSAVED, iTargetID);
			g_cEquipInventory->m_dwObjectIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(g_cEquipInventory->m_dwObjectKeyID);
			
			// 특정 아이템은 언패킹이 불가능함
			if (g_cItemControl->HT_bItemControl_IsItemTimeItem(g_cEquipInventory->m_dwObjectIndex) == HT_FALSE) 	return;
            
			g_cEquipInventory->m_nOverlapCount = g_cItemSystem->HT_iItemSystem_GetItemCount(g_cEquipInventory->m_dwObjectKeyID);	// 중첩된 개수얻기
			// 아이템이 PC/NPC인벤에 있고 중첩된 개수가 1보다 클 경우에만 언패킹창 띄움
			if( g_cEquipInventory->m_nOverlapCount > 1)	 
			{
				// 인벤토리에 빈 공간이 없다면 분리불가
				if (!g_cItemSystem->HT_iItemAlSetPosGoodsKeepBlankCheck())
				{
					CHTString strMessage;
					g_cUIManager->HT_SetScriptMessage( eMsgInvenNotMoveShortOfCargo, &strMessage, _T(""), _T("") );	//	창고 공간이 부족하여 아이템을 이동할 수 없습니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
					return;
				}

				g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_UNPACKING;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenInputMoveItem, &strMessage, _T(""), _T("") );	//	이동할 개수를 입력해 주세요.
				g_cUIManager->HT_MessageBox(_DIALOG_GOODSKEEPWND, strMessage, 2);
				// 아이템을 보관중인 위치 설정
				HT_ItemReturnRoom sSourceRoom = g_cItemControl->HT_vItemControl_ActiveEachWindowCheck( iWIndex, iCIndex );
				g_cItemControl->HT_vItemControl_SetMoveFromPlace(_DIALOG_GOODSKEEPWND, sSourceRoom);
				return;
			}
		}
		else
		{

			//	아이콘을 들고 엉뚱한 곳에 클릭했을때
			if( iTargetID == -1 || iTargetID == -2 )
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			//	아이콘을 클릭하는 순간에도 이벤트가 발생해 줘야 함 그래서 클릭한 아이콘을 팝업할수 있는지 확인하는 절차가 필요함 일단은 여기다 둔다.
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
			//	기존의 슬롯에 아이템이 있으면 덮어지지 않게 처리
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
		// 언패킹할 물품 개수를 입력했다면 분리시킨다.
		if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_UNPACKING)
		{
			if (iTargetID <= 0) return;

			// 언패킹 개수가 0이면 || 가진 개수보다 크면 
			if( g_cEquipInventory->m_nOverlapCount < iTargetID)
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgInvenWrongInput, &strMessage, _T(""), _T("") );	//	잘못 입력하셨습니다.
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

			// 언패킹 금액이 0이면
			if( ( g_cEquipInventory->m_nRupiah <= 0 && g_cEquipInventory->m_byToPlace != MONEY_MOVE_TRADE )
				|| g_cEquipInventory->m_byFromPlace == MONEY_MOVE_NONE 
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_INVEN && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iPCMoney )
				|| (  g_cEquipInventory->m_byFromPlace == ITEM_PLACE_CARGO && g_cEquipInventory->m_nRupiah > g_cEquipInventory->m_iNPCMoney ) )
			{
				if (g_cEquipInventory->m_nRupiah == 0)
					return;

				CHTString strString;
				HT_g_Script_SetMessage( eMsgRupiahMoveAmountErr, &strString );	//마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString);

				// 이동할 금액이 부적합합니다
				//g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveAmountErr );
				// 완료창 띄움
				//g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_COMPLETE;
				//	Set Message Box
				//g_cUIManager->HT_MessageBox( _DIALOG_GOODSKEEPWND, g_cEquipInventory->m_szMessage.HT_szGetString(), 0 );
			} 
			else
			{
				// 보관장소 - NPC 인벤토리
				if( g_cEquipInventory->m_byFromPlace == ITEM_PLACE_CARGO )
				{
					//	인벤토리
					//if( g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) == HT_TRUE )
						g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( _DIALOG_EQUPINVENTORY );
					// 맵에 버리기
					//else
					//	g_cEquipInventory->HT_vRupiahWin_SetMoveToPlace( -1 );

					// 맵에 버리기
						
					//if( g_cEquipInventory->m_byToPlace == ITEM_PLACE_MAP )
					//{
						// 땅에 떨어뜨리시겠습니까?
					//	g_cEquipInventory->m_iRupiahResult = g_cEquipInventory->m_nRupiah = iTargetID;
					//	g_cEquipInventory->HT_vEquipInventory_SetMessage( eMsgRupiahMoveDropQuestion );
					//	g_cEquipInventory->m_byMessageWin = EQUIP_MESSAGE_CONFIRM;
					//	g_cEquipInventory->m_iEI_MsgType = _MESSAGEBOX_THROWRUPIAH;
						//	Set Message Box
					//	g_cUIManager->HT_MessageBox( _DIALOG_GOODSKEEPWND, g_cEquipInventory->m_szMessage.HT_szGetString(), 1 );
					//}
					//else
					//{ 

						// 만약 20억이 넘어버리면 에러메시지 출력
						int temp = iTargetID + g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
						if (temp < 0 || temp > 2000000000L) 
						{
							//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "20억 루피아 이상 저장할 수 없습니다.");
							return;
						}

						g_cEquipInventory->HT_vNetwork_CSP_Req_Money_Move();
					//}
				}
			}
		}
		//else if( g_cEquipInventory->m_iEI_MsgType == _MESSAGEBOX_THROWRUPIAH )
		//{
			//	OK 버튼
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
		// 개인상점 판매창이 떠있을 경우 처리하지 않음
		g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, strMsg, UI_MESSAGEBOX_NUMBERINPUT );
		m_nRupiah = 0;
	}
	else
	{
		//	Show Message Box
		g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, strMsg.HT_szGetString(), 1 );
	}
}

 
//----------인벤토리창 활성화 / 비활성화----------//
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
	//	성별 아이템 만들때
	//if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) || g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) )
	//	return;

	m_bEquipInventoryActive = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_EQUPINVENTORY );
	
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetAntiActive()
{
	// 현재창 범위에 정보창이 띄워져 있을 경우 정보창을 닫는다
	if( g_cObjectInfo->HT_bObjectInfo_IsActive() == HT_TRUE )
		g_cObjectInfo->HT_vObjectInfo_AntiActive();

	// 아이템 이동중이었을 경우
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive( /*_DIALOG_INVEN*/ );

	m_bEquipInventoryActive = HT_FALSE;

	// 창고창이 열려 있다면 창고창도 닫아준다.
//	if (g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == true)
//		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	g_cUIManager->HT_HideWindow( _DIALOG_EQUPINVENTORY );
	g_cUIManager->HT_HideWindow( _DIALOG_INVENTORY2 );
}

// 출력할 메세지 설정
HTvoid CHTEquipInventory::HT_vEquipInventory_SetMessage( HTint idMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vEquipInventory_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vEquipInventory_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 사용/획득한 돈
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

//---------루피아 언패킹 윈도우 띄우기--------//
HTvoid CHTEquipInventory::HT_vRupiahWin_Active()
{
	// 개인상점 판매창이 떠있을 경우 처리하지 않음
	g_cUIManager->HT_MessageBox( _DIALOG_EQUPINVENTORY, _T(""), UI_MESSAGEBOX_NUMBERINPUT );
    m_nRupiah = 0;
	m_iEI_MsgType = _MESSAGEBOX_RUPIAH;
}

// 루피아를 보관중인 위치 설정
HTvoid CHTEquipInventory::HT_vRupiahWin_SetMoveFromPlace( HTint nDlgNo )
{
	switch(nDlgNo)
	{
		case _DIALOG_EQUPINVENTORY:	// PC 인벤토리
			m_byFromPlace = ITEM_PLACE_INVEN;
			break;
		case _DIALOG_GOODSKEEPWND:	// NPC 인벤토리
			m_byFromPlace = ITEM_PLACE_CARGO;
			break;
		case _DIALOG_TRADEWND:		// 트레이드
			m_byFromPlace = MONEY_MOVE_TRADE;
			break;
		default:
			m_byFromPlace = MONEY_MOVE_NONE;
			break;
	}
}

// 루피아를 이동할 위치 설정
HTvoid CHTEquipInventory::HT_vRupiahWin_SetMoveToPlace( HTint nDlgNo )
{
	switch(nDlgNo)
	{
		case _DIALOG_EQUPINVENTORY:				// PC 인벤토리
			m_byToPlace = ITEM_PLACE_INVEN;
			break;
		case _DIALOG_GOODSKEEPWND:		// NPC 인벤토리
			m_byToPlace = ITEM_PLACE_CARGO;
			break;
		case _DIALOG_TRADEWND:			// 트레이드
			m_byToPlace = MONEY_MOVE_TRADE;
			break;
		case _DIALOG_CHARITYWND1:	// 축복의 신단
		case _DIALOG_CHARITYWND2:	// 트루마 신로
			m_byToPlace = MONEY_MOVE_OFFERING;
			break;
		default:
			m_byToPlace = ITEM_PLACE_MAP;
			break;
	}
}

//------- 맵에 루피아 버리기 -----------//
HTvoid CHTEquipInventory::HT_vRupiahWin_ReqDropMoney( )
{
	PS_CSP_REQ_ITEM_DROP info = NULL;
	info = new S_CSP_REQ_ITEM_DROP;

	// 아이템이 있던 원래 위치
	info->byFromPlace = m_byFromPlace;
	info->byIndex = 255;
	info->dwMoney = m_nRupiah;

	// 아이템을 이동할 위치
	HTPoint pPt = g_cItemControl->HT_ptItemControl_SearchMapPosForItemDrop();
	if( pPt.x < 0 || pPt.y < 0 )
	{
		HT_DELETE( info );
		return;
	}

	info->snX = pPt.x;
	info->snZ = pPt.y;

	g_pNetWorkMgr->RequestItemDrop( info );
	 
	//-----디버깅 테스트를 위하여-----//
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
	//	메인캐릭터 전투중이면 취소
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 2 );
}

HTvoid CHTEquipInventory::HT_vEquipInventory_SetRightItem_KeyID( DWORD dwItemKeyID )
{
	m_dwEquip_RightItemKeyID = dwItemKeyID;
}

// 왼쪽에 장착한 아이템의 Index 반환
DWORD CHTEquipInventory::HT_dwEquipInventory_GetLeftItem()
{
	return m_dwEquip_LeftItem;
}
// 오른쪽에 장착한 아이템의 Index 반환
DWORD CHTEquipInventory::HT_dwEquipInventory_GetRightItem()
{
	return m_dwEquip_RightItem;
}

DWORD CHTEquipInventory::HT_dwEquipInventory_GetRightItem_KeyID()
{
	return m_dwEquip_RightItemKeyID;
}

// 인벤토리 크기 구하기
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

// 인벤토리 사용가능 여부
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

// 해당 갯수만큼 인벤토리 공간이 있는 여부 확인 2004. 11. 29 선영범
HTbool CHTEquipInventory::HT_bGetInventoryBlank( HTint nNum )
{
	// 먼저, 사용가능한 인벤토리의 크기를 구해온다.

	return HT_FALSE;
}

// 인벤토리 크기 초기 설정
HTvoid CHTEquipInventory::HT_vInitBagStatus( )
{
	if( g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
		g_cUIManager->HT_ShowWindow(_DIALOG_EQUPINVENTORY);

	// Bag1은 기본 사용 가능
	HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG1, _INVEN_WIDTH);
	// Bag3은 사용불가
	HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG3, 0 );

	// 서버에서 내려온 인벤확장 서비스 기한
	time_t timeTime;
	if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Inven, timeTime ) == HT_FALSE )
		return;
	
	if( timeTime <= 0 ) // 인벤확장 서비스를 신청해본 적이 없음
	{
		HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 사용 불가능
	}
	else
	{
		// 현재 시간 변환
		time_t now; time( &now );

		// Bag2 설정 : 현재 시간과 인벤확장 서비스 기한 비교
		if( now <= timeTime )
		{
			HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); // Bag2 사용가능

			// 확장기한 표시하기
			CHTString szTime;
			g_cMainCharacter->HT_vMainChar_GetTimeStamp( 254, szTime );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_EQUPINVENTORY, 6, szTime.HT_szGetString() );
		}
		else
			HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 사용 불가능
	}
}


// 사용 불가능한 인벤토리 표시 다시 그리기
HTvoid CHTEquipInventory::HT_vRenewalPossibleBar( HTint iInventory, HTbyte byNewSize, HTbool bUsable )
{
	if( byNewSize > _INVEN_WIDTH || byNewSize < 0 )	// 실제 인벤토리 크기보다 클 경우
		return;

	// 이전 사용 불가능 표시 지우기
	HT_vDelPossibleBar(iInventory);

	// 새로운 사이즈로 설정하고 그리기
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

	// x좌표 구하기(y는 항상 0)
	//HTint iSizeX = _INVEN_WIDTH - byNewSize ;
	//HTint iColNo = _INVEN_WIDTH - iSizeX;

	//if( iColNo >= 0 && iSizeX > 0 )
	if( bUsable == HT_FALSE )
	{
		m_bUsableInventory = bUsable;
		// 사용 불가능한 인벤토리 부분의 Bitmap색을 바꾼다
		for( HTint i=0 ; i<6 ; i++ )
		{
			for( HTint j=0 ; j<4 ; j++ )
			{
				g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INVENTORY2, (_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)+i+(j*6), bUsable );
			}
		}
	}
}

// 사용 불가능한 인벤토리 표시 삭제
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

	// x좌표 구하기(y는 항상 0)
	HTint iSizeX = _INVEN_WIDTH - iColNo ;
	//iColNo = _INVEN_WIDTH - iSizeX;
	if( iColNo >= 0 && iSizeX > 0 )
	{
		m_bUsableInventory = true;

		// 사용 불가능한 인벤토리 부분의 Bitmap색을 바꾼다
		for( HTint i=0 ; i<6 ; i++ )
		{
			for( HTint j=0 ; j<4 ; j++ )
			{
				g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INVENTORY2, (_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)+i+(j*6), HT_TRUE );
			}
		}
	}
}

//--------- 루피아 이동 요청 ----------//
HTvoid CHTEquipInventory::HT_vNetwork_CSP_Req_Money_Move()
{
	MSG_Money_Move* info = HT_NULL;
	info = new MSG_Money_Move;

	info->byFromPlace = m_byFromPlace;
	info->byToPlace = m_byToPlace;
	info->dwMoney = m_nRupiah;

	g_pNetWorkMgr->RequestMoneyMove( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqMoneyMove : %d(From:%x To:%x)", 
	//															m_nRupiah, m_byFromPlace, m_byToPlace );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTEquipInventory::HT_vNetwork_SCP_Resp_Money_Move( MSG_Money_Move* info )
{
	// 성공일 때만 내려온다
	m_bMessage_Error = HT_FALSE;	// 에러 없음

	// 보관 위치의 루피아 갱신
	if( info->byFromPlace == ITEM_PLACE_INVEN )			// PC 인벤토리
		HT_vEquipInventory_SetPCMoney( info->dwFromMoney ) ;

	else if( info->byFromPlace == ITEM_PLACE_CARGO )	// NPC 인벤토리
		HT_vEquipInventory_SetNPCMoney( info->dwFromMoney );

	m_szMessage.HT_hrCleanUp();

	// 이동 위치의 루피아 갱신
	if(  info->byToPlace == ITEM_PLACE_INVEN )			// PC 인벤토리
	{
		// 이동/사용/받은 루피아 금액
		m_iRupiahResult = info->dwToMoney - m_iPCMoney;
		if( m_iRupiahResult < 0 )
			m_iRupiahResult = 0;

		if( info->byFromPlace == ITEM_PLACE_QUEST )	// 퀘스트로부터 발생
		{
			if( m_iRupiahResult == 0 )
			{
				m_iRupiahResult = m_iPCMoney - info->dwToMoney;
				// 퀘스트에 의해 %d 루피아를 소비했습니다.
				HT_vEquipInventory_SetMessage( eMsgRupiahSpendingQuest );
			}
			else
				// %d 루피아를 받았습니다.
				HT_vEquipInventory_SetMessage( eMsgRupiahReceiveQuest );
		}
		else if( info->byFromPlace == ITEM_PLACE_PORTAL )	// 포탈 사용에 의해 돈이 감소된 경우
		{	
			if( m_iRupiahResult == 0 )
				m_iRupiahResult = m_iPCMoney - info->dwToMoney;
			
			// 포탈 이용으로 %d 루피아를 소비했습니다.
			HT_vEquipInventory_SetMessage( eMsgRupiahSpendingPortal );
		}
		else if( info->byFromPlace == ITEM_PLACE_EVENT )	// 이벤트로부터 발생
		{
			// %d 루피아를 획득했습니다.
			HT_vEquipInventory_SetMessage( eMsgRupiahReceive );
		}
		else 
		{
			// PC인벤토리로 %d 루피아를 옮겼습니다.
			HT_vEquipInventory_SetMessage( eMsgRupiahMoveToPCInven );
		}

		HT_vEquipInventory_SetPCMoney( info->dwToMoney );
	}
	else if(  info->byToPlace == ITEM_PLACE_CARGO )	// NPC 인벤토리
	{
		// 이동 루피아 금액
		m_iRupiahResult = info->dwToMoney - m_iNPCMoney;
		if( m_iRupiahResult < 0 )
			m_iRupiahResult = 0;

		HT_vEquipInventory_SetNPCMoney( info->dwToMoney );
		
		// NPC인벤토리로 %d루피아를 옮겼습니다.
		HT_vEquipInventory_SetMessage( eMsgRupiahMoveToNPCInven );
	}
	else
		return;
	
	// 시스템 창에 표시
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

