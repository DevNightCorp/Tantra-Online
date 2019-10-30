#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htitemcontrol.h"

#include <queue>

#define UNPACKING_WIN_XPOS		300
#define UNPACKING_WIN_YPOS		300

// ������ �̵� ����
#define ITEMCONTROL_STATUS_NONE				1	// ����
#define ITEMCONTROL_STATUS_MOVE				2	// �̵�

// �޼���â 0:�޼���â�ȶ�,1:�۾��Ϸ�
#define ITEMCONTROL_MESSAGE_NONE				0
#define ITEMCONTROL_MESSAGE_COMPLETE			1	
#define ITEMCONTROL_MESSAGE_CONFRIM				2

#define UNPACKING_MOVE_NONE						0x00
#define UNPACKING_MOVE_INVEN					0x04	// PC �κ�
#define UNPACKING_MOVE_GOODSCHARGE				0x05	// NPC �κ�
//#define UNPACKING_MOVE_GILDINVEN				0x06	// ��� �κ�
#define UNPACKING_MOVE_TRADE					0x07	// Ʈ���̵�

// ���� �۾� 
#define RESENT_STEP_NONE				0
#define RESENT_STEP_PACKING				1
#define RESENT_STEP_UNPACKING			2
#define RESENT_STEP_ITEM_MOVE			3
#define RESENT_STEP_EQUIP				4
#define RESENT_STEP_TRADE_MOVE			5
#define RESENT_STEP_BAG_USE				6
#define RESENT_STEP_BAG_CANCEL			7
#define RESENT_STEP_ITEM_GET			8

#define BAG_CHANGE_TIME					0.5f	// bag�� ��ȯ�ϱ� ���� �� ���� ����ؾ��ϴ� �ð�
#define SELECT_BAG_NONE					-1

//#define _CLIENT_INFO_FILE_PATH	_T("system\\ClientInfo.cfg")

enum
{
	JIVA_MANDARA	= 1120,
	JIVA_SHAMBALA	= 1154,
	JIVA_JINA		= 1155,
	JIVA_UBAEJI		= 1156,
	JIVA_GODPLACE	= 1157,
};

HTItemControl::HTItemControl(void)
{
}

HTItemControl::~HTItemControl(void)
{
}

HTvoid HTItemControl::HT_vItemControl_CleanUp()
{
	//-----������ �����Ҽ� �ִ°����� ��ǥ��-----//
	m_sPossible_BarInfo.nBitmapNo = -1;
	m_sPossible_BarInfo.nDlgNo = -1;
	m_sPossible_BarInfo.nGroupNo = -1;
	m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
	m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;

	// ���� �۾� - PACKING/UNPACKING������ �����
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= m_dwGetItemKeyID = RETURNTYPE_MAINGAME_FAILD;

	m_fTimeForBag = 0.0f;	// bag ��ȯ �ð�
	m_iSelectBagNo = SELECT_BAG_NONE;

	m_pTimer->Do( HT_TIMER_STOP );
	HT_DELETE( m_pTimer );
}

//-----�ʱ�ȭ-----//
HTvoid HTItemControl::HT_vItemControl_Init()
{
	//-----�ʱ� �ε�-----//
	HT_vItemControl_Init_LoccationPosLoad();

	//-----������ �����Ҽ� �ִ°����� ��ǥ��-----//
	m_sPossible_BarInfo.nInventory = -1;
	m_sPossible_BarInfo.nBitmapNo = -1;
	m_sPossible_BarInfo.nDlgNo = -1;
	m_sPossible_BarInfo.nGroupNo = -1;
	m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
	m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;

	//-----������ ����Ѱ��� �ľ�-----//
    m_bPotionItemUse_Sw = HT_FALSE;

	//-----������ ����� ������ Ÿ��-----//
	m_dwItemUse_DelayTime = timeGetTime();

	// ���� �۾� - PACKING/UNPACKING������ �����
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= m_dwGetItemKeyID = RETURNTYPE_MAINGAME_FAILD;

	//	�������� �ʱ�ȭ
	m_bAssistant = HT_FALSE;

	m_fTimeForBag = 0.0f;	// bag ��ȯ �ð�
	m_iSelectBagNo = SELECT_BAG_NONE;

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );
}

//-----�ʱ� �ε�-----//
HTvoid HTItemControl::HT_vItemControl_Init_LoccationPosLoad()
{
	m_nItemControl_Status	= ITEMCONTROL_STATUS_NONE;
	m_dwActiveItemKeyID		= RETURNTYPE_MAINGAME_FAILD;
	m_bSetTargetItem_Sw		= HT_FALSE;
}
//------- �޼��� ���  ------//
HTvoid HTItemControl::HT_vItemControl_SetMessage( HTint idMessage )
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
		HT_vItemControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemControl_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vItemControl_SetParamTextForMessage( sParam3, &szOut3 );

		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vItemControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemControl_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vItemControl_SetParamTextForMessage( sParam1, &szOut1 );
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		m_szMessage = szString;
}

HTvoid HTItemControl::HT_vItemControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// �ٸ� ĳ���� �̸�
		case eMsgParamOthercharName :
			break;
		
		// ������ �̸�
		case eMsgParamItemName :
			 *pszParam = m_szObjectName;
			break;

		case eMsgParamSpendingMoney :
			pszParam->HT_szFormat( "%d", m_iMoneyForMessage );
			break;

		default:
			break;
	}
}

HTbool HTItemControl::HT_bItemControl_IsItemStatusMove()
{
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//-----��ư üũ_Switch ON-----//
HTRESULT HTItemControl::HT_bItemControl_ButtonCheck_SwitchOn( HTint iBeforDlgNo, HTint iBeforeCellNo, HTint iCurDlgNo, HTint iCurCellNo )
{
    // �ٸ� �۾��� ������ ��û�� �ϰ� ��ٸ��� �ִ� ��� ó������ ����
	if( m_byResent != RESENT_STEP_NONE )
		return HT_FAIL;

	//----------�������� Ȱ��ȭ ���� üũ->������ ������ �˻�----------//
	HT_ItemReturnRoom sSourceRoom = HT_vItemControl_ActiveEachWindowCheck( iBeforDlgNo, iBeforeCellNo );
	HT_ItemReturnRoom sTargetRoom = HT_vItemControl_ActiveEachWindowCheck( iCurDlgNo, iCurCellNo );
	//if( sTargetRoom.nInventory != -1 )
	{
		// Ư�� ������ ���ؼ��� �̵��� �Ұ����մϴ�.
		if (iCurCellNo == -1 || !(iBeforDlgNo == _DIALOG_EQUPINVENTORY || iBeforDlgNo == _DIALOG_INVENTORY2 || iBeforDlgNo == _DIALOG_GOODSKEEPWND || iBeforDlgNo == _DIALOG_ASHRAMCAGO ) 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE
			|| g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMCAGO ) == HT_TRUE )
		{
			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );
			DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);
			
			// Ư�� �������� �̵��� �Ұ�
			if( HT_SUCCEED(HT_IS_CANNOTMOVEITEM(dwItemIndex)))
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgCommonNotMoveTredeItem, &strMessage, _T(""), _T("") );	//	�� �������� ���� �����ų� �ŷ��� �� �����ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
				return HT_FAIL;
			}
		}

		// ���콺�� PC �κ��丮�� ���� ���
		if( sTargetRoom.nLocation == ITEM_LOCATION_PC)
		{
			// BAG2�� ������� ���ϴ� ������ ��� ó������ ����
			if( sTargetRoom.nInventory == ITEM_LOCATION_PC_BAG2 
						&& g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_FALSE )
				return HT_OK;

			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );

			if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
				return HT_FAIL; 

			// ����/��ü ����� ���
			if( g_cNPCControl->HT_bNPCControl_IsItemFixActive() || g_cNPCControl->HT_bNPCControl_IsItemDisjointActive() )
			{
				g_cNPCControl->HT_vNPCControl_FixDisjoint_LButtonClick(dwItemKeyID);
				return HT_OK;
			}
			// ���� ����� ���
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
			{
				//HTRESULT res = g_cNPCControl->HT_hrNPCControl_ItemWork_LButtonClick( dwItemKeyID );

				// ���ø���϶� ���ð����� �����ۿ��� �ٸ� ������ �������� �̵��� �� �ְ� �ϱ� ����
//				if( res == HT_OK )	
//					return HT_OK;
			} 
			// ���� ���� g_cUIManager����� ���
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE )
			{
				if (iBeforeCellNo >= 100)
				{
					g_cIndividualStore->HT_vIndividualStore_SelectItemForSell( dwItemKeyID );
					return HT_OK;
				}
			}
			// ��Ź ���� ����� ���
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE && g_cRentalStore->m_nWindowType == 1)
			{
				if (iBeforeCellNo >= 100)
				{
					g_cRentalStore->HT_vRentalStore_SelectItemForSell( dwItemKeyID, iCurCellNo );
					return HT_OK;
				}
			}
			// 1:1 ��ȯ ���� ���
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE )
			{
				if (iBeforeCellNo >= 100) 
				{

					//	���� �������� ��ȯ�Ǹ�ȵȴ�.
					if( iCurCellNo <100 )
						return HT_FAIL; 
						
					HTRESULT res = g_cExchangeSystem->HT_hrExchange_SetMyTradeItem( dwItemKeyID, sSourceRoom );
					if( res == HT_OK )	
						return HT_OK;
				}
			}
			// �峳 ����� ���
			else if ( g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND1) ||  g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND2) )
			{
				if (iBeforeCellNo >= 100) 
				{
					g_cNPCControl->HT_vNPCControl_OfferingItemAdd( dwItemKeyID );
					return HT_OK;
				}
			}
			// ���ǵ�� ����� ���
			//else if( sLocRoom.nLocation == ITEM_LOCATION_PC && g_cNPCControl->HT_bNPCControl_IsRegistLotteryActive() )
			//{
			//	if( dwItemKeyID != RETURNTYPE_MAINGAME_FAILD )
			//	{
			//		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);
			//		if(dwItemIndex == 0)
			//			return HT_FAIL;

			//		// �����ȵ� ���ǰ� '��'������ ������ �̺�Ʈ(����) ������
			//		if( LOTTERY_ITEM_INDEX != dwItemIndex && LOTTERY_ITEM_INDEX_FAIL != dwItemIndex )	 
			//			HT_vNetWork_CSP_RESP_Item_Use( dwItemKeyID, sLocRoom.nCellPosx, 0x01 );
			//		
			//		return HT_OK;
			//	}
			//}
		}
		// ���콺�� equipment �� ���� ���
		else if( sTargetRoom.nLocation == ITEM_LOCATION_EQUIP )
		{
			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );
			// ���� ����� ���
			if( g_cNPCControl->HT_bNPCControl_IsItemFixActive() )
			{
				if(dwItemKeyID != RETURNTYPE_MAINGAME_FAILD)
					g_cNPCControl->HT_vNPCControl_FixDisjoint_LButtonClick(dwItemKeyID);
				
				return HT_OK;
			}

			if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE )
			{
				if (iCurDlgNo <= 200) 
					return HT_FALSE;
			}

			if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE )
			{
				if (iCurDlgNo <= 200) 
					return HT_FALSE;
			}

		}

		m_sPossible_BarInfo.nInventory = -1;
		m_sPossible_BarInfo.nBitmapNo = -1;
		m_sPossible_BarInfo.nDlgNo = -1;
		m_sPossible_BarInfo.nGroupNo = -1;
		m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
		m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;
		
		//	�������� �����ϼ� �ִ��� �Ǵ��Ͽ� �����̵��� �����Ѵ�.
		this->HT_vItemControl_SelectItemCheck( sSourceRoom );

		return HT_OK;
	}

	return HT_FAIL;
}

//-----��ư üũ_Switch Off-----//
HTRESULT HTItemControl::HT_vItemControl_ButtonCheck_SwitchOff( HTint iDlgNo, HTint iCellNo )
{
	// �ٸ� �۾��� ������ ��û�� �ϰ� ��ٸ��� �ִ� ��� ó������ ����
	if( m_byResent != RESENT_STEP_NONE )
		return HT_FAIL;

	HT_ItemReturnRoom sLocRoom;
	//----------�������� Ȱ��ȭ ���� üũ->������ ������ �˻�----------//
	sLocRoom = HT_vItemControl_ActiveEachWindowCheck( iDlgNo, iCellNo );
	if( sLocRoom.nInventory != -1 )
	{
		//----------������ ���� ��ġ Ȯ��----------//
		HT_vItemControl_SecurityItemSettingPos( sLocRoom );
		//----------���� ���� üũ----------//
		// �̵� ��ġ �˻�
		HTbool	bRes = HT_bItemControl_Limit_InInventory( HT_TRUE );
        
		if( bRes == HT_FALSE )
		{
			// �̵� ����
			HT_vItemControl_ItemAntiActive();
			HT_vItemControl_SettingItem( HT_FALSE );
			return HT_FAIL;
		}
	}
	else
	{
		//	6. �������� �ٸ� �������� ���� ��_���� ���� ã�� ����
		if( iDlgNo == -1 )
		{
			// �κ��丮 Ȯ��� �������� Ȯ���� ���� ������ ��� �ٴڿ� ���� �� ����.
			if( (m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP && m_sSource_Item.nInventory == ITEM_LOCATION_EQUIP_BAG ) 
								|| HT_vItemControl_Limit_InMap() == HT_FALSE )
			{
				// �̵� ����
				HT_vItemControl_ItemAntiActive();
				HT_vItemControl_SettingItem( HT_FALSE );
			}
		}
		else
		{
			// �̵� ����
			HT_vItemControl_ItemAntiActive();
			HT_vItemControl_SettingItem( HT_FALSE );
			return HT_FAIL;
		}
	}

	m_sPossible_BarInfo.nInventory = -1;
	m_sPossible_BarInfo.nBitmapNo = -1;
	m_sPossible_BarInfo.nDlgNo = -1;
	m_sPossible_BarInfo.nGroupNo = -1;
	m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
	m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;

	return HT_OK;
}

// ������ �̵� ����
HTvoid HTItemControl::HT_vItemControl_ItemAntiActive()
{
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE )
	{
		// �̵� ����
		m_nItemControl_Status = ITEMCONTROL_STATUS_NONE;
	}
}


//--------������ �̵��� ESC�� ���ؼ� â�� ���� ��� ������ ���� �ڸ��� ����------//
HTvoid HTItemControl::HT_vItemControl_ESC_ItemAntiActive()
{
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE)
	{
		//	������ �ý��ۿ� �׸� �̵� ���� ����
		HT_vItemControl_ItemAntiActive();
		HT_vItemControl_SettingItem( HT_FALSE );

		m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
		
		m_sPossible_BarInfo.nInventory = -1;
		m_sPossible_BarInfo.nBitmapNo = -1;
		m_sPossible_BarInfo.nDlgNo = -1;
		m_sPossible_BarInfo.nGroupNo = -1;
		m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
		m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;
	}
}

HTbool HTItemControl::HT_bItemControl_IsItemMove()
{ 
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE)
		return HT_TRUE;
	else
		return HT_FALSE;
}

//----------���콺�� � ������ �ȿ� �ִ��� üũ----------//
HT_ItemReturnRoom HTItemControl::HT_vItemControl_ActiveEachWindowCheck( HTint iDlgNo, HTint iCellNo )
{
	//	1. �κ��丮 ��ġ ����
	HT_ItemReturnRoom sLocRoom;
	sLocRoom.nLocation = sLocRoom.nInventory = -1; 
	sLocRoom.nCellPosx = sLocRoom.nCellPosy = -1;
	sLocRoom.nDlgNo = sLocRoom.nGroupNo = sLocRoom.nBitmapNo = -1;

	if( iCellNo != -1 )
	{
		sLocRoom.nDlgNo = iDlgNo;
		switch( iDlgNo )
		{
			case _DIALOG_EQUPINVENTORY :
			case _DIALOG_INVENTORY2 :
			{
				// Equipment
				if( iCellNo>=1 && iCellNo<=18 )
				{
					sLocRoom.nGroupNo = -1;
					sLocRoom.nLocation = ITEM_LOCATION_EQUIP;
					sLocRoom.nCellPosx = sLocRoom.nCellPosy = 0;
					switch( iCellNo )
					{
						case _INVEN_HEAD			: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_HEAD;			break;
						case _INVEN_BODY			: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_ARMOR;			break;
						case _INVEN_TROUSERS		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_PANTS;			break;
						case _INVEN_GLOVES			: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_GLOVE;			break;
						case _INVEN_BELT			: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_BELT;			break;
						case _INVEN_FOOT			: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_FOOT;			break;
						case _INVEN_RIGHT_EARING	: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_RIGHT_EAR;		break;
						case _INVEN_LEFT_EARING		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_LEFT_EAR;		break;
						case _INVEN_NECKLACE		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_NECK;			break;
						case _INVEN_ATTACK_WEAPON	: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;		break;
						case _INVEN_DEFENCE_WEAPON	: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;		break;
						case _INVEN_RIGHT_ARMLET	: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_RIGHT_BRACELET; break;
						case _INVEN_LEFT_ARMLET		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_LEFT_BRACELET;	break;
						case _INVEN_RIGHT_RING		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_RIGHT_RING;		break;
						case _INVEN_LEFT_RING		: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_LEFT_RING;		break;
						case _INVEN_BAG				: sLocRoom.nInventory = ITEM_LOCATION_EQUIP_BAG;			break;
						default: break;
					}
				}
				// Inventory Bag1
				else if( iCellNo>=_SLOTCURRECT_INVEN && iCellNo<(_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN) )
				{
					sLocRoom.nLocation = ITEM_LOCATION_PC;
					sLocRoom.nInventory = 0;
					sLocRoom.nGroupNo = 0;
					
					HTint nRow = (iCellNo-_SLOTCURRECT_INVEN) / 6;
					HTint nCol = (iCellNo-_SLOTCURRECT_INVEN) % 6;

					if( nCol<6 && nRow<4 )
					{
						sLocRoom.nCellPosx = nCol;
						sLocRoom.nCellPosy = nRow;
					}
					else
					{
						sLocRoom.nLocation = -1;
						sLocRoom.nInventory = -1;
					}
				}
				// Inventory Bag2
				else if( iCellNo>=(_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN) )
				{
					sLocRoom.nLocation = ITEM_LOCATION_PC;
					sLocRoom.nInventory = 1;
					sLocRoom.nGroupNo = 1;
					
					HTint nRow = (iCellNo-(_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)) / 6;
					HTint nCol = (iCellNo-(_SLOTCURRECT_INVEN+_SLOTCURRECT_ADDINVEN)) % 6;

					if( nCol<6 && nRow<4 )
					{
						sLocRoom.nCellPosx = nCol;
						sLocRoom.nCellPosy = nRow;
					}
					else
					{
						sLocRoom.nLocation = -1;
						sLocRoom.nInventory = -1;
					}
				}
			}
				break;
			case _DIALOG_GOODSKEEPWND	:
			{
				if( iCellNo>=10 && iCellNo<=(10+130) )
				{
					sLocRoom.nLocation = ITEM_LOCATION_NPC;
					sLocRoom.nInventory = ITEM_LOCATION_NPC_ITEMSAVED;
					sLocRoom.nCellPosx = (iCellNo-10) % _GOODSKEEP_INVEN_WIDTH;
					sLocRoom.nCellPosy = (iCellNo-10) / _GOODSKEEP_INVEN_WIDTH;
					sLocRoom.nGroupNo = 0;
				}
			}
				break;
			case _DIALOG_ASHRAMCAGO	:
			{
				if( iCellNo>=10 && iCellNo<=(10+360) )
				{
					sLocRoom.nLocation = ITEM_LOCATION_ASHRAMCARGO;
					sLocRoom.nInventory = ITEM_LOCATION_ASHRAMCARGO_BAG1;
					sLocRoom.nCellPosx = (iCellNo-10) % _GOODSKEEP_INVEN_WIDTH;
					sLocRoom.nCellPosy = (iCellNo-10) / _GOODSKEEP_INVEN_WIDTH;
					sLocRoom.nGroupNo = 0;
				}
			}
				break;
		}
	}
		
	return sLocRoom;
}
  
//----------������ ������ �˻�->Ȱ��ȭ ���������� ����----------//
HTvoid HTItemControl::HT_vItemControl_SelectItemCheck( HT_ItemReturnRoom sLocRoom )
{
	// �̿�� �̿�� ����߿� ������ �̵��� �õ��ߴٸ� �ٸ� ���� �߻��� ���� ���� â�� �ݾ� ������.
	if( g_cUIManager->HT_isShowWindow(_DIALOG_BEAUTYSALON2) == HT_TRUE )
	{
		g_cStatus->HT_vStatus_BeautyBack();	// �������·� ���� ����
		g_cUIManager->HT_HideWindow(_DIALOG_BEAUTYSALON2);
	}

	m_dwActiveItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sLocRoom );
	if( m_dwActiveItemKeyID != RETURNTYPE_MAINGAME_FAILD )
	{
		m_nItemControl_Status = ITEMCONTROL_STATUS_MOVE;
		//-----������ �̵�_�ҽ� ����-----//
		m_sSource_Item.nLocation = sLocRoom.nLocation;
		m_sSource_Item.nInventory = sLocRoom.nInventory;
		m_sSource_Item.pCellPos = g_cItemSystem->HT_ptItemSystem_GetInventoryPos( m_dwActiveItemKeyID );

		//-----������ �̵����� �̺��丮 ��ǥ�ø� ���� ������ ������-----//
		//m_pPossible_BarSize = g_cItemSystem->HT_ptItemSystem_GetSize( m_dwActiveItemKeyID );
		m_pPossible_BarSize.x = m_pPossible_BarSize.y = 1;
	}
}

//----------������ ���� ��ġ Ȯ��----------//
HTvoid HTItemControl::HT_vItemControl_SecurityItemSettingPos( HT_ItemReturnRoom sLocRoom )
{
	m_sTarget_Item.nLocation = sLocRoom.nLocation;
	m_sTarget_Item.nInventory = sLocRoom.nInventory;
	m_sTarget_Item.pCellPos.x = sLocRoom.nCellPosx;
	m_sTarget_Item.pCellPos.y = sLocRoom.nCellPosy;
}

//----------���� ���� üũ_�κ��丮 �ȿ���----------//
HTbool HTItemControl::HT_bItemControl_Limit_InInventory( HTbool bType )
{
	if( bType == HT_TRUE )
	{
		DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
		if( dwItemIndex == 0 )
		{
			return HT_FALSE;
		}

		//	1. ������
		if( m_sTarget_Item.nLocation == m_sSource_Item.nLocation &&
			m_sTarget_Item.nInventory == m_sSource_Item.nInventory &&
			m_sTarget_Item.pCellPos.x == m_sSource_Item.pCellPos.x &&
			m_sTarget_Item.pCellPos.y == m_sSource_Item.pCellPos.y )
		{
			return HT_FALSE;
		}
		// ����Ʈ ���� �������� PC�κ� �̿��� ��ҷ� �ű���� �� ���
		if( CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) && m_sTarget_Item.nLocation != ITEM_LOCATION_PC )
			return HT_FALSE;

		//	2. �ٸ� �������� �����ž� ���� ��
		//	3. �κ��丮 ������
		//	4. ���� �Ұ�
		HTint nResult = HT_RESULT_ITEM_MOVE_FAIL; 
		if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
		{
			// ������ �̵� ��ġ ����
			HTbool bRes = HT_bItemControl_Network_ReqEquip_LocationCheck(dwItemIndex);	
			if( bRes == HT_FALSE )	// ������ �� ���� �������̸�
				return HT_FALSE;

			// �̵� ��ġ�� ������ �������� ���� ���
			if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( m_sTarget_Item.nInventory ) )
				nResult = HT_RESULT_ITEM_MOVE_FAIL;
			else
				nResult = HT_RESULT_ITEM_MOVE_OK;
		}
		else
			nResult = g_cItemSystem->HT_iItemAlSetPosInventoryCheck( m_dwActiveItemKeyID, dwItemIndex, m_sTarget_Item );
  
		if( nResult == HT_RESULT_ITEM_MOVE_FAIL )			//	�̵�(����) �Ұ��϶�
		{
			return HT_FALSE;
		}
		else if( nResult == HT_RESULT_ITEM_MOVE_OK )		//	�̵�(����)
		{
			//----------������ �Ⱦ��� ������ �ʱ�ȭ �� ������ ����â �ʱ�ȭ----------//
			if( m_sSource_Item.nLocation == ITEM_LOCATION_MAP )
			{
				g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
			}

			//----------������ �̵�(����) ��û----------//
			if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
			{
				if(m_sTarget_Item.nInventory == ITEM_LOCATION_EQUIP_BAG )	// �κ��丮 Ȯ��
				{
					HT_vItemControl_Network_ReqMove();
					m_byResent = RESENT_STEP_ITEM_MOVE;
				}
				else	// ������ ����
				{
					// ������ ���� ���� �˻�
					if( g_cItemSystem->HT_bItemSystem_GetPossible( m_dwActiveItemKeyID, HT_FALSE ) == HT_TRUE )
					{
						HT_vItemControl_Network_ReqMove();
						m_byResent = RESENT_STEP_ITEM_MOVE;
					}
					else
						return HT_FALSE;
				}
			}	
			else if( m_sTarget_Item.nLocation == ITEM_LOCATION_PC || 
					 m_sTarget_Item.nLocation == ITEM_LOCATION_NPC ||
					 m_sTarget_Item.nLocation == ITEM_LOCATION_ASHRAMCARGO )
			{
				HT_vItemControl_Network_ReqMove();
				m_byResent = RESENT_STEP_ITEM_MOVE;
			}
			// ��ŷ� ����/1:1 ��ȯ/������� ��ȯ
			else 
				return HT_FALSE;
		}
		else if( nResult > HT_RESULT_ITEM_MOVE_OK )		//	��ŷ�Ҷ�
		{
			
			// �Ϻ� �������� ��ŷ �� �� ����. 2004. 11. 11 ������
			//if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE) return HT_FALSE;

			m_nDestItemKeyID = (DWORD)nResult;
			//----------������ ������ ��ŷ�� ��û----------//
			if( m_byResent == RESENT_STEP_NONE ) // ���� ��û �ܰ�
			{
				m_byResent = RESENT_STEP_PACKING;
				HT_vItemControl_Network_Req_ItemPacking( ITEMPACKING_TYPE_PACKING );
			}
			else
				return HT_FALSE;
		}
		else
			return HT_FALSE;
	}
	
	return HT_TRUE;
}

// �������� �̵������� ���������� �ƴϸ� �ð��� �� Ư��(�̵� �Ұ�����) ���������� �����Ͽ� ��� ��ȯ
HTbool HTItemControl::HT_bItemControl_IsItemTimeItem(DWORD dwItemIndex)
{
	// Ư�� �������� ������ ��ŷ/����ŷ �� ��ȯ�̳� ���λ��������� �� ����� ������ �� ���� �ؾ��Ѵ�.
	if (dwItemIndex >= 6801 && dwItemIndex <= 6840 || 
		dwItemIndex >= 7093 && dwItemIndex <= 7094 )
		return HT_FALSE;
	return HT_TRUE;
}

// ����â�� �������� ���� ��� ��ġ ����
HTvoid HTItemControl::HT_vItemControl_EconomyLocationCheck( )
{
	// �������
	m_sTarget_Item.nInventory = ITEM_LOCATION_ECONOMY_AIDITEM;
	m_sTarget_Item.pCellPos.x = 0;	
	m_sTarget_Item.pCellPos.y = 0;
}

//	6. �������� �ٸ� �������� ���� ��_���� ���� �O�� ����
HTbool HTItemControl::HT_vItemControl_Limit_InMap()
{
	// ����Ʈ ���� �������� ������ ���ϰ�
	HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
	if( dwIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwIndex ) )
		return HT_FALSE;

	//	���λ����� ��ȯââ�� �� �������� ���� ������ ���ϰ� ó��
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return HT_FALSE;

	//	2. ������ ���� ���� �� ������ ���
	//	2-1. ����� ��ġ ����
	m_sTarget_Item.nLocation = ITEM_LOCATION_MAP;
	m_sTarget_Item.nInventory = ITEM_LOCATION_MAP_FIELD;
	m_sTarget_Item.pCellPos = HT_ptItemControl_SearchMapPosForItemDrop();
	// ��ǥ���� �̻��ϸ�
	if( m_sTarget_Item.pCellPos.x < 0 || m_sTarget_Item.pCellPos.x >= MAX_MAP_SIZE ||
											m_sTarget_Item.pCellPos.y < 0 || m_sTarget_Item.pCellPos.y >= MAX_MAP_SIZE )
		return HT_FALSE;

	// �ʿ� ���� ������ ��Ȯ�� �޼��� ����
	// %s�� ���� �����ðڽ��ϱ�?
	if( g_pParamMgr->HT_bGetItemName( dwIndex, &m_szObjectName ) == true)
	{
		if (g_cMainCharacter->m_bMainChar_Live == false)	// �������¶�� ���� ������ ����.
			return HT_FALSE;

		HT_vItemControl_SetMessage( eMsgItemMoveDropQuestion );
		m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
		g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_THROWITEM, m_szMessage.HT_szGetString() );
	}
	return HT_FALSE;
}

// ĳ���� �ֺ��� �� ��ǥ �� �� �� ã��
HTPoint HTItemControl::HT_ptItemControl_SearchMapPosForItemDrop()
{
	// ����� ��ġ �����ϰ� ����
	srand( (unsigned)time( NULL ) );
	HTint spaceX = 0, spaceY = 0;
	HTPoint pos;
	HTRESULT res = HT_FALSE;
	HTint nArea = 4;
	HTint nLoopCount = 0;	// ������ ���� ��ġ�� ���ϱ� ���ؼ� while���� ���� Ƚ��

	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	while(1)
	{
		spaceX = rand() % nArea;	// �׳� ���� ����
		spaceY = rand() % nArea;

		pos.x = pPt.x + spaceX;	
		pos.y = pPt.y + spaceY;
		
		res = g_cItemSystem->HT_hrCheckMapPos(pos);
		if(res == HT_FALSE)	// �� ��ġ�� �������� ���� ���
		{
			// �̵� ������ �������� �˻��ؾ���. 2004.1.6 ����
			//HTbool bCanMove = g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecTempPos, 0 );
			//if( bCanMove == HT_TRUE )
				break;			
		}

		++nLoopCount;

		// ���� �Ÿ� �ȿ� �������� ���� ���� a=30ȸ �̻� ã�� ���ϸ� b=2��ŭ ������ ������.
		// �� c=500ȸ �̻� ã�� ���� ��� ������� �ʴ´�.
		// a,b,c �� �ӽ÷� ������. 2003.07.04 ����
		if( nLoopCount%30 == 0 )
			nArea += 2;
		else if( nLoopCount == 500 )
		{
			pPt.x = pPt.y = -1;
			return pPt;
		}
	}
	pPt.x = pos.x;
	pPt.y = pos.y;

	// ��ǥ���� �̻��ϸ�
	if( pPt.x < 0 || pPt.x >= MAX_MAP_SIZE || pPt.y < 0 || pPt.y >= MAX_MAP_SIZE )
	{
		pPt.x = pPt.y = -1;
	}
	
	return pPt;
}

//----------��ŷ� ���� ����----------//
HTvoid HTItemControl::HT_vItemControl_EconomySetting( DWORD dwItemIndex )
{
	HTbool res = HT_FALSE; 

	if( dwItemIndex == -1 )
		return;

	// ���������� �ƴ� ��� ����â�� �ø��� ���Ѵ�
	if( CHTParamIDCheck::HT_bIsItemRefine( dwItemIndex ) == false )
		res = HT_FALSE;
	else
		res = g_cNPCControl->HT_bNPCControl_SetAidItemResource( m_dwActiveItemKeyID );

	HT_vItemControl_SettingItem( res );
}

// �κ��丮�� �������� ���� ��ġ�� �ִ��� �˻�
HTint HTItemControl::HT_iItemControl_SearchInventory( DWORD dwItemKeyID, HTint iInventory, HTPoint& pPt )
{
	HTint bEquip = 0;

	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwIndex == 0 )
		return bEquip;

	HT_ItemReturn sTempPos;
	sTempPos.pSize.x = g_cEquipInventory->HT_byGetInventorySize( iInventory );
	sTempPos.pSize.y = _INVEN_HEIGHT;

	HT_ITEMSETTING_FLAG sSetItem;
	sSetItem.nLocation = ITEM_LOCATION_PC;
	sSetItem.pCellPos.x = sSetItem.pCellPos.y = 0;	
	sSetItem.nInventory = iInventory;

	for( BYTE x=0 ; x<sTempPos.pSize.x ; ++x )
	{
		for( BYTE y=0 ; y<sTempPos.pSize.y ; ++y )
		{	
			sSetItem.pCellPos.x = x;
			sSetItem.pCellPos.y = y;
			bEquip = g_cItemSystem->HT_iItemAlSetPosInventoryCheck(dwItemKeyID, dwIndex, sSetItem );
//			if( bEquip == 1 )
			if( bEquip )
				break;
		}
//		if( bEquip == 1 )
		if( bEquip)
			break;
	}

	pPt.x = sSetItem.pCellPos.x;
	pPt.y = sSetItem.pCellPos.y;

	return bEquip;
}

/*
// �κ��丮�� �ش� �������O�� ����� ������ �ִ��� �˻�
HTint HTItemControl::HT_iItemControl_SearchBlankInventory();
{
	

	HTint bEquip = 0;
	DWORD dwItemKeyID = 

	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwIndex == 0 )
		return bEquip;

	for (iInventory=0; iInventory < 3; ++iInventory)	// �κ��丮 ��� �˻�
	{
		HT_ItemReturn sTempPos;
		sTempPos.pSize.x = g_cEquipInventory->HT_byGetInventorySize( iInventory );
		sTempPos.pSize.y = _INVEN_HEIGHT;

		HT_ITEMSETTING_FLAG sSetItem;
		sSetItem.nLocation = ITEM_LOCATION_PC;
		sSetItem.pCellPos.x = sSetItem.pCellPos.y = 0;	
		sSetItem.nInventory = iInventory;

		for( BYTE x=0 ; x<sTempPos.pSize.x ; ++x )
		{
			for( BYTE y=0 ; y<sTempPos.pSize.y ; ++y )
			{	
				sSetItem.pCellPos.x = x;
				sSetItem.pCellPos.y = y;
				if (g_cItemSystem->HT_iItemAlSetPosInventoryCheck(dwItemKeyID, dwIndex, sSetItem ))
					bEquip++;
			}
		}
	}
	return bEquip;
}
*/

//----------��Ʈ��----------//
HTvoid HTItemControl::HT_vItemControl_Control()
{
	//-----��Ʈ��_������ �ݱ�-----//
	HT_vItemControl_Control_PickUpItem();
}

//------ Bag�� ��ȯ�ϱ� ���� �ð� üũ ���� ----------//
HTvoid HTItemControl::HT_vStartTimeForBag( HTint iSelectedBagNo )
{
	if( m_fTimeForBag == 0.0f || m_iSelectBagNo != iSelectedBagNo )
	{
		m_iSelectBagNo = iSelectedBagNo;
		m_fTimeForBag = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// ���� �ð� ����
	}
}

//------ Bag�� ��ȯ�ϱ� ���� �ð� üũ ���� --------//
HTvoid HTItemControl::HT_vEndTimeForBag()
{
	m_fTimeForBag = 0.0f;
	m_iSelectBagNo = SELECT_BAG_NONE; 
}

//-----��Ʈ��_������ �ݱ�-----//
HTvoid HTItemControl::HT_vItemControl_Control_PickUpItem()
{
	if( m_bSetTargetItem_Sw	== HT_FALSE )
		return;

	//----------�������� �����۰��� �Ÿ��� üũ----------//
	HTbool bResult = g_cItemSystem->HT_bItemSystem_PickUpItemCheck( m_dwGetItemKeyID );

	//----------�������� �ö�� ������ �κ��丮�� �̵� �������� üũ----------//
	if( bResult == HT_TRUE )
	{

		//----------Ư�� �������� ���϶��ڸ� ���� �� �ֵ��� ����----------//
		//7361	ī�콺Ʈ�� ù��° ����
		//7362	ī�콺Ʈ�� �ι�° ����
		//7363	ī�콺Ʈ�� ����° ����
		//7364	ī�콺Ʈ�� �׹�° ����
		//7372	���� ���� �����
		//7379	�ƺ� ���� �����
		//7380	�ܹ� ���� �����
		//7381	���� ���� �����
		HTdword dwGetItemKeyID = g_cItemSystem->HT_bItemSystem_GetMapItemPickUpKeyID();
		if (dwGetItemKeyID == 7361 || dwGetItemKeyID == 7362 || dwGetItemKeyID == 7363 || dwGetItemKeyID == 7364 ||
			dwGetItemKeyID == 7372 || dwGetItemKeyID == 7379 || dwGetItemKeyID == 7380 || dwGetItemKeyID == 7381 )
			if( g_cGuildSystem->HT_byGuild_GetAuthority() < GUILD_AUTHORITY_RAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg16, &strString );	// ���϶��ڸ��� ȹ���� �� �ֽ��ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				m_bSetTargetItem_Sw	= HT_FALSE;
				return;
			}

		HT_vItemControl_Network_ReqGet();
		m_bSetTargetItem_Sw	= HT_FALSE;
		//m_byResent = RESENT_STEP_ITEM_GET;
	}
}

//-------���� ��� ũ�� ��ȯ---------//
HTPoint HTItemControl::HT_ptItemControl_LoctionSize( HTint iLocation )
{
	HTPoint ptSize;

	ptSize.x = ptSize.y = 0;
	switch ( iLocation )
	{
		case ITEM_LOCATION_EQUIP : 
			ptSize.x = 1; ptSize.y = 1;
			break;

		case ITEM_LOCATION_NPC :
			ptSize.x = _GOODSKEEP_INVEN_WIDTH; ptSize.y = _GOODSKEEP_INVEN_HEIGHT;
			break;

		case ITEM_LOCATION_ASHRAMCARGO :
			ptSize.x = _GOODSKEEP_INVEN_WIDTH; ptSize.y = _GOODSKEEP_INVEN_HEIGHT*3;
			break;

		case ITEM_LOCATION_EXCHANGE	:
            ptSize.x = _TRADE_INVEN_WIDTH; ptSize.y = _TRADE_INVEN_HEIGHT;
			break;

		case ITEM_LOCATION_ECONOMY :
			ptSize.x = 1; ptSize.y = 1;
			break;
/*		
		case ITEM_LOCATION_CHATURANGA_BOARD :
			ptSize.x = _CHATURANGA_SAVE_INVEN_WIDTH; ptSize.y = _CHATURANGA_SAVE_INVEN_HEIGHT;
			break;
*/
		default :
			break;
	}

	return ptSize;
}

//-----�������� ����-----//
HTvoid HTItemControl::HT_vItemControl_SetTargetItem( DWORD dwItemKeyID )
{
	m_bSetTargetItem_Sw	= HT_TRUE;
	m_dwGetItemKeyID = dwItemKeyID;
}

//----------������ ����----------//
HTvoid HTItemControl::HT_vItemControl_SettingItem( HTbool bType )
{
	// ��չ����� ��� �޼տ� ��Ʈ���� �׸� ������
	m_byResent = 0;
	HTbool bDrawTwinImage = HT_TRUE;
	HTdword dwLeftItemKeyID = 0;
	
	if( ( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP || m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP)
				&& m_sSource_Item.nInventory != ITEM_LOCATION_EQUIP_LEFT_HAND )
		dwLeftItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );

	if( bType == HT_TRUE )
	{
		// �޼տ� ������ �������� ���� ���
		if( dwLeftItemKeyID > 0 && m_sTarget_Item.nInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )
			bDrawTwinImage = HT_FALSE; 
		if( m_sTarget_Item.nLocation == ITEM_LOCATION_ASHRAMCARGO )
		{
			HTint index = ( m_sTarget_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sTarget_Item.pCellPos.x )+(g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120);
			m_sTarget_Item.pCellPos.x = ( index ) % _GOODSKEEP_INVEN_WIDTH; 
			m_sTarget_Item.pCellPos.y = ( index ) / _GOODSKEEP_INVEN_WIDTH;
		}
		g_cItemSystem->HT_vItemSystem_SettingInventoryPos( m_dwActiveItemKeyID, m_sTarget_Item, bDrawTwinImage );
	}
 	else
	{
		// �޼տ� ������ �������� ���� ���
		if( dwLeftItemKeyID > 0 && m_sSource_Item.nInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )
			bDrawTwinImage = HT_FALSE; 
		if( m_sSource_Item.nLocation == ITEM_LOCATION_ASHRAMCARGO )
		{
			HTint index = ( m_sSource_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sSource_Item.pCellPos.x )+(g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120);
			m_sSource_Item.pCellPos.x = ( index ) % _GOODSKEEP_INVEN_WIDTH; 
			m_sSource_Item.pCellPos.y = ( index ) / _GOODSKEEP_INVEN_WIDTH;
		}

		g_cItemSystem->HT_vItemSystem_SettingInventoryPos( m_dwActiveItemKeyID, m_sSource_Item, bDrawTwinImage );
	}
}

//----------������ ���� ��û_�޼�,������ üũ----------//
HTbool HTItemControl::HT_bItemControl_Network_ReqEquip_LocationCheck(DWORD dwItemIndex)
{
	if( dwItemIndex <= 0 )
		return HT_FALSE;

	if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(dwItemIndex) )			// �Ӹ�
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_HEAD;

	else if( CHTParamIDCheck::HT_bIsItemAccessoryEarring(dwItemIndex) )	// �Ͱ���
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_EAR ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_EAR;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_EAR ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_EAR;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_EAR;
	}
	else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace(dwItemIndex) )// �����
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_NECK;
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceArmor(dwItemIndex) )		// ��
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_ARMOR;
	
	else if( CHTParamIDCheck::HT_bIsItemDefencePants(dwItemIndex) )		// ����
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_PANTS;

	else if( CHTParamIDCheck::HT_bIsItemDefenceGloves(dwItemIndex) )	// �尩
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_GLOVE;

	else if( CHTParamIDCheck::HT_bIsItemDefenceBelt(dwItemIndex) )		// ��Ʈ
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BELT;
	// ��� | Ȱ
	else if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand(dwItemIndex) || CHTParamIDCheck::HT_bIsItemWeaponThrow(dwItemIndex) )	
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;

	else if( CHTParamIDCheck::HT_bIsItemWeaponOneHand(dwItemIndex) )	// ������
	{
		//	�ϻ���(�Ƽ���/������)�϶� �Ƽ��� ��հ��϶��� üũ�Ѵ�.
		if( g_oMainCharacterInfo.snTribe == HT_ID_CHARACTER_ASURA || g_oMainCharacterInfo.snTribe == HT_ID_CHARACTER_RAKSHASA )
		{
			//	����̶�� ��ī ��ų�� üũ�ؾ��Ѵ�.
			if( g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( 3199 ) == 0  )
				m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
			else
			{
				//	���� �����տ� ���� ����Ǿ� ���� ������
				if( g_cItemSystem->HT_dwSystem_GetItemIndex(g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_RIGHT_HAND)) == 0 )
				{
					m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
				}
				else
				{
					//	�����ҷ��� �ϴ� �������� �ܰ��̸�
					if( g_pEngineHandler->HT_bIsShortSword( dwItemIndex ) )
					{
						//	���� �����տ� �ǰ��� ���� �����ϰ� ������
						if( m_dwActiveItemKeyID == g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_RIGHT_HAND) )
							return HT_FALSE;
						m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;
					}
					else
						m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
				}
			}
		}
		else
		{
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
		}
	}
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceShield(dwItemIndex) )	// �޼�
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;
	
	else if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet(dwItemIndex) )// ����
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_BRACELET ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_BRACELET;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_BRACELET ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_BRACELET;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_BRACELET;
	}
	else if( CHTParamIDCheck::HT_bIsItemAccessoryRing(dwItemIndex) )	// ����
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_RING ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_RING;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_RING ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_RING;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_RING;
	}
	else if( CHTParamIDCheck::HT_bIsItemDefenceShoes(dwItemIndex) )	// ��
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_FOOT;
	
	else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(dwItemIndex) && dwItemIndex != 6307)	// �κ��丮Ȯ�� (������������(6307)�� Ȯ�忡 ���Խ�Ű�� ����)
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BAG;
	else if( CHTParamIDCheck::HT_bIsItemCharm(dwItemIndex)) // �κ�Ȯ��
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BAG;
	else if( CHTParamIDCheck::HT_bIsItemUsableArrow(dwItemIndex) && dwItemIndex != 7093 && dwItemIndex != 7094 )	// ȭ��
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;

	else
		return HT_FALSE;

	m_sTarget_Item.pCellPos.x = 0;	
	m_sTarget_Item.pCellPos.y = 0;	

	return HT_TRUE;
}

//----------�Ҹ� ������(���� ��)���� �˻�-------------//
HTRESULT HTItemControl::HT_hrItemControl_ItemUse( HTint nDlgNo, HTdword dwItemKeyID )
{
	// ������ �̵����̸� ó������ ����
	if( m_nItemControl_Status != ITEMCONTROL_STATUS_NONE )
		return HT_FAIL;

	// ��� �κ��丮�� �ִ��� �˻�
	if( nDlgNo != _DIALOG_EQUPINVENTORY )	
		return HT_FAIL; // PC �κ��� �ƴ� ��� ó�� ����

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return HT_FAIL;

	return HT_hrItemControl_ItemUse( dwItemKeyID ) ;
}

HTRESULT HTItemControl::HT_hrItemControl_ItemUse( HTdword dwItemKeyID )
{
	HT_ITEMSETTING_FLAG sLocRoom;
	g_cItemSystem->HT_bItemSystem_GetItemPos(dwItemKeyID, sLocRoom);

	// ����� �������� Ȯ������̰� ���Ұ� �϶�
	if( g_cEquipInventory->HT_bGetInventoryUsable(ITEM_LOCATION_PC_BAG2) == HT_FALSE && sLocRoom.nInventory == ITEM_LOCATION_PC_BAG2)
		return HT_OK;

	// ������ �̵����̸� ó������ ����
	if( m_nItemControl_Status != ITEMCONTROL_STATUS_NONE )
		return HT_FAIL;

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return HT_FAIL;
	m_dwUseItemKeyID = dwItemKeyID;

	HTint dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(m_dwUseItemKeyID);
	if(dwItemIndex == 0)
		return HT_FAIL;

	// �Ϻ��� ��� ������ ���� �뿪�� �����۵��� ���� �κ��丮�� �� ������ 8ĭ �̻��̾�߸� ����� �� �ִ�.
	if( g_iInationalType == INATIONALTYPE_JAPEN)
	{
		if (dwItemIndex >= 7064 && dwItemIndex <= 7067 || dwItemIndex >= 6737 && dwItemIndex <= 6741)
		{
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 8)
			{
				// ���� ������ �����ϸ� ������� ���ϰ� �Ѵ�.
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}
	}

	if( g_wResentZoneServerID == ZONE_ANAKAKURUMA )
	{
		//	���������, ����� �̵��� Ǫ��Ƽī, ���� ���� ���� �����, ����̵��� Ǫ��Ƽī
		if( dwItemIndex == 6722 || dwItemIndex == 6732 || dwItemIndex == 7049 || dwItemIndex == 7072 )
		{
			return HT_FAIL;
		}
	}
	
	// �Ҹ� ������-ȭ�� ����
	if( CHTParamIDCheck::HT_bIsItemUsable( dwItemIndex ) && !CHTParamIDCheck::HT_bIsItemUsableArrow( dwItemIndex ) ||
		CHTParamIDCheck::HT_bIsItemChargeContinuance( dwItemIndex ) )
	{
		// ������ ��� ���� ���� �˻�
		if( g_cItemSystem->HT_bItemSystem_GetPossible( m_dwUseItemKeyID, HT_TRUE ) == HT_FALSE )
		{
			// ������ ������� ���ǿ� ���� ����� �� �����ϴ�.
			HT_vItemControl_SetMessage( eMsgItemUseConditionErr );

			// �Ϸ�â ���
			m_byMessageWin = ITEMCONTROL_MESSAGE_COMPLETE;
			g_cUIStatus->m_MessageBoxType = 1;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 0);

			return HT_OK;
		} 
		// ����/�̵��� Ǫ��Ƽī�� ���� ���¿� �������϶��� ����Ҽ� ���� ó�� ������ ����� �� ���� ó��
		if( dwItemIndex==HT_ITEM_MOVE_PUSTICA ||
			  dwItemIndex==HT_ITEM_MOVE_JIVAPUSTICA || 
			  dwItemIndex==HT_ITEM_MOVE_UPGRADEJIVAPUSTICA || 
			  dwItemIndex==HT_ITEM_HIGHZONE_TICKET ||
			  dwItemIndex==HT_ITEM_FORTRESSPUSTICA )
		{
			if (g_cMainCharacter->HT_bMainChar_GetSitDownState() == HT_TRUE ) 
			{
				// �������� ����� �� ���� �����Դϴ�.
				HT_vItemControl_SetMessage( eMsgItemUseCannot );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			//if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
			//{
			//	CHTString strMessage;
			//	g_cUIManager->HT_SetScriptMessage( eMsgCommonNotUseInDuel, &strMessage, _T(""), _T("") );	//	�������϶��� ����Ҽ� �����ϴ�.
			//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
			//	return HT_OK;
			//}
		}

		// ��� �̵� Ǫ��Ƽī�� ��� ���������� �ֽ������� ����� �� ����.
		if (dwItemIndex==HT_ITEM_FORTRESSPUSTICA)
		{
			if (g_wResentZoneServerID == 11 || g_wResentZoneServerID == 10)
			{
				// �������� ����� �� ���� �����Դϴ�.
				HT_vItemControl_SetMessage( eMsgItemUseCannotNowZone );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}

		// ���� ��ȯ �ֹ����� �Ĺ̸� ���������� ��밡��
		else if( dwItemIndex == 6719 && g_wResentZoneServerID != 8 ) 
		{
			// ���� ��ȯ �ֹ����� �Ĺ̸� ���������� ����� �� �ֽ��ϴ�.
			HT_vItemControl_SetMessage( eMsgPremiumItemMonsterEventError );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
			return HT_OK;
		}
		// ��ũ�� �ʱ�ȭ �������� ��� ��Ȯ�� �޼��� ����
		else if( dwItemIndex == HT_ITEM_INIT_CHAKRA )
		{
			// �ʱ�ȭ �Ͻðڽ��ϱ�?
			HT_vItemControl_SetMessage( eMsgCharacterChakraInitQuestion );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 2;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		// ��ų �ʱ�ȭ �������� ��� ��Ȯ�� �޼��� ����
		else if( dwItemIndex == HT_ITEM_INIT_CHAKRA || dwItemIndex == HT_ITEM_INIT_SKILL )
		{
			// �ʱ�ȭ �Ͻðڽ��ϱ�?
			HT_vItemControl_SetMessage( eMsgCharacterSkillInitQuestion );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 3;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		// �������� ����� ����
		else if( dwItemIndex == 6722)
		{
			// ������ 30 �̸��̸� �����޽��� ���
			if (g_oMainCharacterInfo.byLevel < 30)
			{
				// ���� ��ȯ �ֹ����� �Ĺ̸� ���������� ����� �� �ֽ��ϴ�.
				HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			// �ֽ� ������ ������ ��쿡�� �����޽����� ����ؾ� �Ѵ�.
			if (g_oMainCharacterInfo.byTrimuriti == 0 )
			{
				// �ֽ��� �����ؾ߸� ���������� ������ �� �ֽ��ϴ�.
				HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError2 );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			// �������� ������� ����Ͻðڽ��ϱ�? [Ȯ��/���]
			HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnter );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 4;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		else if (dwItemIndex == 6730)	// â�� �̿�� ���� �˾�
		{
			// �� �׾��� ��쿡�� ��� �Ұ�
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
			{
				g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPING);
				g_cUIManager->HT_ShowWindow( _DIALOG_GOODSKEEPWND );
			}
			else
			{
				//HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError2 );
				//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "���� ���¿����� ����� �� �����ϴ�." );

			}
		}
		// ����Ʈ �ʱ�ȭ ������ ���� ��Ȯ��â ��� 
		else if (dwItemIndex == 7077 || dwItemIndex >= 7061 && dwItemIndex <= 7063 || dwItemIndex == 7050) 
		{
			HT_vItemControl_SetMessage( eMsgReqUsingItem );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 5;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);
			m_dwSelectedUseItemKeyID = m_dwUseItemKeyID;
			return HT_OK;
		}
		else if (dwItemIndex >= 7064 && dwItemIndex <= 7067) //(�ٷ��� ������ ����)
		{
			if ( g_iInationalType == INATIONALTYPE_KOREA )
			{
				//HT_vItemControl_SetMessage( eMsgReqUsingItem );

				m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
				g_cUIStatus->m_MessageBoxType = 6;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgShopReqBuyItem, &strMessage, _T(""), _T("") );	//	"���� �������� ����Ͻðڽ��ϱ�?\n[����]�ڽ��� ��ǻ�� ��¥�� ��Ȯ���� ���� ��� ���Ⱓ�� ����� ǥ����� ���� �� �ֽ��ϴ�."
				g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strMessage.HT_szGetString() , 1);
				m_dwSelectedUseItemKeyID = m_dwUseItemKeyID;
				return HT_OK;
			}
			else
			{
				HT_vItemControl_SetMessage( eMsgReqUsingItem );

				m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
				g_cUIStatus->m_MessageBoxType = 7;
				g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , m_szMessage , 1);
				m_dwSelectedUseItemKeyID = m_dwUseItemKeyID;
				return HT_OK;
			}
		}
		else if( dwItemIndex == 7069)	// ��� ���� ���� �̺��丮�� �������� üũ
		{
			// �κ��丮 ���� üũ
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 7)
			{
				// ���� ������ �����ϸ� ������� ���ϰ� �Ѵ�.
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}
		else if ((dwItemIndex == 7071) || (dwItemIndex == 6764)) // �̿�� �̿�� ����
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON ) )
			{
				g_cUIManager->HT_HideWindow(_DIALOG_BEAUTYSALON);
			}

			g_cStatus->m_dwBeautyItemKeyID = m_dwUseItemKeyID;
			g_cStatus->HT_vStatus_Beauty_Render(_DIALOG_BEAUTYSALON2);
			g_cUIManager->HT_ShowWindow(_DIALOG_BEAUTYSALON2);
			return HT_OK;
		}
		else if (dwItemIndex == 6733) // ��� ���� 
		{
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 9)
			{
				// ���� ������ �����ϸ� ������� ���ϰ� �Ѵ�
				CHTString strString;
				HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// �κ��丮 ������ �����մϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return HT_OK;
			}
		}

//		else if (dwItemIndex == 7073 || dwItemIndex == 7079) // ���̿��� �̺�Ʈ ������ ���� ������ ���� ����� ���� �����Ƿ� ���⼭�� ���Ұ��� �����Ѵ�
//		{
			// ���� ������ �����ϸ� ������� ���ϰ� �Ѵ�.
//			HT_vItemControl_SetMessage( eMsgEventItemUseError );
//			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
//			return HT_OK;
//		}

		// �κ��丮 Ȯ�� ��� ����(����������)��.
		if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwItemIndex ) )
			return HT_OK;

		// �������ǿ� ��� �ش���� ������ ������ ���
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID,/* sLocRoom.nCellPosx,*/ 0x01 );

		return HT_OK;
	}

	// ��Ű�� ������ (3����, 5���� �������� ��� ������ ����ϴ°ɷ� ������.)
	if (dwItemIndex == 7093 || dwItemIndex == 7094) 
	{
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID, 0x01 );
		return HT_OK;
	}

	// ���λ��� Ȯ�� �����۰� ��Ÿ �����۵� ����ϴ� ���������� ó��
	if (dwItemIndex >= 6951 && dwItemIndex <= 6956) 
	{
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID, 0x01 );
		return HT_OK;
	}

	return HT_FAIL;
}

// �������� ��ġ ����
HTvoid HTItemControl::HT_vItemControl_SetMoveFromPlace( HTint nDlgNo, HT_ItemReturnRoom sLocRoom )
{
	m_sSource_Item.nLocation = sLocRoom.nLocation;
	m_sSource_Item.nInventory = sLocRoom.nInventory;
	m_sSource_Item.pCellPos.x = sLocRoom.nCellPosx;
	m_sSource_Item.pCellPos.y = sLocRoom.nCellPosy;

	if(nDlgNo == _DIALOG_INVEN)			// PC �κ��丮
	{
		m_byFromPlace = UNPACKING_MOVE_INVEN;
	}
	else if( nDlgNo == _DIALOG_GOODSKEEPWND)	// NPC �κ��丮
	{
		m_byFromPlace = UNPACKING_MOVE_GOODSCHARGE;
	}
	//else if(nDlgNo == MAIN_DLG_INVEN)		// ��� �κ��丮
	//	m_byFromPlace = UNPACKING;
	else
	{
		m_byFromPlace = UNPACKING_MOVE_NONE;
	}
}

// �̵��� ��ġ ����
HTbool HTItemControl::HT_bItemControl_SetMoveToPlace( HTint nDlgNo )
{
	HT_ITEMSETTING_FLAG sSetItem;
	sSetItem.pCellPos.x = sSetItem.pCellPos.y = 0;	
	HTint bEquip = 0;

	if(nDlgNo == _DIALOG_EQUPINVENTORY)			// PC �κ��丮
	{
		m_byToPlace = UNPACKING_MOVE_INVEN;
		
		sSetItem.nLocation = ITEM_LOCATION_PC;
		// Bag1 �˻�
		if( g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG1 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG1;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
		// Bag2 �˻�
		if( bEquip == 0 && g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG2 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG2;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
		// Bag3 �˻�
		if( bEquip == 0 && g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG3 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG3;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
	}
	else if( nDlgNo == _DIALOG_GOODSKEEPWND)	// NPC �κ��丮
	{
		m_byToPlace = UNPACKING_MOVE_GOODSCHARGE;

		sSetItem.nLocation = ITEM_LOCATION_NPC;
		sSetItem.nInventory = ITEM_LOCATION_NPC_ITEMSAVED;
		bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
	}
	//else if(nDlgNo == MAIN_DLG_INVEN)		// ��� �κ��丮
	//	m_byToPlace = UNPACKING;
	else if( nDlgNo == _DIALOG_TRADE )			// Ʈ���̵�
	{
		m_byToPlace = UNPACKING_MOVE_TRADE;

		sSetItem.nLocation = ITEM_LOCATION_EXCHANGE;
		sSetItem.nInventory = ITEM_LOCATION_EXCHANGE_MYWIN;
		bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
	}
	else
	{
		m_byToPlace = UNPACKING_MOVE_NONE;

		sSetItem.nLocation = -1;
		sSetItem.nInventory = -1;

		return HT_FALSE;
	}

	if( bEquip == 1 )
	{
		m_sTarget_Item.nLocation	= sSetItem.nLocation;
		m_sTarget_Item.nInventory	= sSetItem.nInventory;
		m_sTarget_Item.pCellPos		= sSetItem.pCellPos;

		return HT_TRUE;
	}

	return HT_FALSE; // ������ ����
}

// ����ŷ�� �������� ���� ��ġ�� �ִ��� �˻�
HTint HTItemControl::HT_iItemControl_SearchPosForUnPack( HTint iLocation, HTint iInventory, HTPoint& pPt )
{
	HTPoint sourcePos = g_cItemSystem->HT_ptItemSystem_GetInventoryPos( m_dwActiveItemKeyID );	// source�������� ��ġ
	//DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
	//if( dwIndex == 0 )
//		return HT_FALSE;

	HTint bEquip = 0;	// ���

	//---------- ���������� ���� ����� ũ�� ���ϱ� -------------//
	HTPoint ptSize;
	if( iLocation == ITEM_LOCATION_PC )	
	{
		// PC �κ��丮�� ��� Ȱ��ȭ�Ǿ��ִ� ũ�� ���ϱ�
		ptSize.x = g_cEquipInventory->HT_byGetInventorySize(iInventory);
		ptSize.y = _INVEN_HEIGHT;
	}
	else
		ptSize = g_cItemControl->HT_ptItemControl_LoctionSize ( iLocation );

	HT_ITEMSETTING_FLAG sSetItem;	// �������� ���� �� ����� ��ġ
	sSetItem.nLocation = iLocation;
	sSetItem.pCellPos.x = sSetItem.pCellPos.y = 0;	
	sSetItem.nInventory = iInventory;

	for( BYTE x=0 ; x<ptSize.x ; ++x )
	{
		for( BYTE y=0 ; y<ptSize.y ; ++y )
		{
			sSetItem.pCellPos.x = x;
			sSetItem.pCellPos.y = y;

			bEquip = g_cItemSystem->HT_iItemAlSetPosInventoryCheck(g_cEquipInventory->m_dwObjectKeyID, g_cEquipInventory->m_dwObjectIndex, sSetItem );
			if( bEquip == 1 )
			{
				// ���ο� ��ġ�� �ڱ� �ڽ��� ���� �� ��쿡�� 1�� ��ȯ �ɼ� �ֱ� ������ 
				if( m_byFromPlace != m_byToPlace )	// �ٸ� �κ��丮�� ���� ���
					break;
				// ���� �κ��丮 ������ ��ġ�� �ٸ� ���
				else if( sSetItem.pCellPos.x != sourcePos.x || sSetItem.pCellPos.y != sourcePos.y )
					break;
				else
					bEquip = 0;
			}
		}
		if( bEquip == 1 )
		{
			// ���ο� ��ġ�� �ڱ� �ڽ��� ���� �� ��쿡�� 1�� ��ȯ �ɼ� �ֱ� ������ 
			if( m_byFromPlace != m_byToPlace )	// �ٸ� �κ��丮�� ���� ���
				break;
			// ���� �κ��丮 ������ ��ġ�� �ٸ� ���
			else if( sSetItem.pCellPos.x != sourcePos.x || sSetItem.pCellPos.y != sourcePos.y )
				break;
			else
				bEquip = 0;
		}
	}

	pPt.x = sSetItem.pCellPos.x;
	pPt.y = sSetItem.pCellPos.y;

	return bEquip;
}

//----------������ ��û_������ ���---------------//
//	bLoc 1:PCInventory, 2:quickslot
HTvoid HTItemControl::HT_vNetWork_CSP_RESP_Item_Use( DWORD dwKeyID,/* BYTE byPos,*/ BYTE byLocation, HTchar* pStr )
{
    HTint dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
	// ĳ���Ͱ� ��� ���� ��
	if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )
	{
		if( dwItemIndex != HT_INDEX_SELF_REVIVAL && 
			dwItemIndex != HT_INDEX_SELF_COMPLTEREVIVAL )
			return;
		else
		{
			// Ȯ��â("Ȯ�ι�ư�� ������ ������������ �ٽ� �¾�ϴ�.") �����
			if (g_cUIManager->HT_isShowWindow(_DIALOG_DEATHMSG + 999))
			{
				g_cUIManager->HT_FocusOffEditBoxControl(_DIALOG_DEATHMSG , 1); 
				g_cUIManager->HT_EnableOnWindow(_DIALOG_DEATHMSG );
				g_cUIManager->HT_DeleteWindow(_DIALOG_DEATHMSG + 999);
			}
		}
	}
	//else 
	//{
		//if( dwItemIndex == HT_INDEX_SELF_REVIVAL ||
		//	dwItemIndex == HT_INDEX_SELF_COMPLTEREVIVAL ) // ������� �� ������ �ֹ��� ��� �ȵǰ�...
		//	return;
	//}

	//if (dwItemIndex == 7067) // �����̾� ��Ű�� �÷�Ƽ�� �ٷ��̴� �ּ� 8ĭ �̻��� ������ �ʿ�� �Ѵ�.
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�ٷ��̸� Ǯ�� ���ؼ��� �ּ� 8ĭ�� ���� ������ �ʿ��մϴ�");
	//}


	// ������ ����Ҽ� ���� ��
	if( m_bPotionItemUse_Sw == HT_TRUE )
	{
		DWORD dwPass = GetTickCount();
		if( dwPass < m_dwItemUse_DelayTime+1000 )
			return;
	}

	// �������� ��ġ ���ϱ�
	HT_ITEMSETTING_FLAG sLocRoom;
	if( byLocation != ITEM_PLACE_EVENT ) // ����(�κ��� ���� ������)�� ��츦 ����
	{
		if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwKeyID, sLocRoom ) == HT_FALSE )
			return;
	}

	m_dwUseItemKeyID = dwKeyID;

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	
	info->byType = HT_MSG_ITEM_USE;
	if( byLocation == ITEM_PLACE_EVENT ) // �̺�Ʈ�� ���� ����� ���
	{
		info->byPlace = ITEM_PLACE_EVENT;
		info->byIndex = EVENT_COUPON;
		// ���� ��ȣ
		HTchar strNumber[5], strNumber2[5];

		strncpy( strNumber, pStr, 4 ); // ���� 4�ڸ� : 0~3
		strNumber[4] = '\0';

		strncpy( strNumber2, &(pStr[4]), 4 ); // ���� 4�ڸ� : 4~7
		strNumber2[4] = '\0';

		DWORD dwCount1 = 0, dwCount2 = 0 ;
		sscanf(strNumber, "%x", &dwCount1);
		sscanf(strNumber2, "%x", &dwCount2);
		
		info->snUserKeyID = (short)dwCount1;
		info->snWarpID = (short)dwCount2;
	}
	else
	{
		info->byPlace = ITEM_PLACE_INVEN;
		info->byIndex = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y) 
										+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);

		// ����Ǫ��Ƽī�̸� ���⼭ ������ ��� �޽����� ������ �ʰ�... �ٸ� �Է��� �޾Ƽ� �����ش�.
		if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVE_JIVAPUSTICA )
		{
			//	this item, Because Portal Algorism
			g_cPortal->HT_vPortal_SetDataForMsgItem( info->byPlace, info->byIndex, HT_ITEM_MOVE_JIVAPUSTICA );
			//	Show MovePotal Dlg
			g_cUIManager->HT_ShowWindow( _DIALOG_JIVAPUSTICAWND );
			HT_DELETE( info );
			return;
		}
		//	���� �̵��� ���� Ǫ��Ƽī�� ��������� ���� ��Żâ�� �����ش�.
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVE_UPGRADEJIVAPUSTICA ||
				 g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_HIGHZONE_TICKET )
		{
			//	this item, Because Portal Algorism
			g_cPortal->HT_vPortal_SetDataForMsgItem( info->byPlace, info->byIndex, g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) );
			g_cPortal->HT_vPortal_ImprovementMovePustica();
			g_cUIManager->HT_ShowWindow( _DIALOG_UPGRADEJIVAPUSTICA );
			HT_DELETE( info );
			return;
		}
		//	��Ȱ �ֹ����� �̿�������
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_REVIVALBOOK ||
				 g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_UPGRADEREVIVALBOOK )
		{
			//	this item, Because Portal Algorism
			if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
			{
				if( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSG + 999 ) )
					g_cUIManager->HT_DeleteWindow(_DIALOG_DEATHMSG + 999);

				if( g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) )
					g_cUIManager->HT_HideWindow( _DIALOG_DEATHMSGFOTRESS );

				g_cPortal->HT_vPortal_SetDataForMsgItem( info->byPlace, info->byIndex, g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) );
				g_cUIManager->HT_ShowWindow( _DIALOG_REVIVEWND );
			}
			HT_DELETE( info );
			return;
		}
		//	��� �̵��� Ǫ��Ƽī�ΰ�� ������ ��Ż �̵��� ��û�Ѵ�.
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_FORTRESSPUSTICA )
		{
			g_cPortal->HT_vPortal_SetPortressPustica( info->byPlace, info->byIndex );
			HT_DELETE( info );
			return;
		}
		//	���� �̵��� Ǫ��Ƽī�ΰ�� ������ ��Ż �̵��� ��û�Ѵ�.
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_SIEGEPUSTICA )
		{
			g_cPortal->HT_vPortal_SetSiegePustica( info->byPlace, info->byIndex );
			HT_DELETE( info );
			return;
		}
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_OPEN_MESSAGE ||			//	������ ������ (ȣ��)
			     g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_COMBAT_MESSAGE )		//	������ ������ (������ɼ�)
		{
			if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_OPEN_MESSAGE )
			{
                g_cChatting->HT_vChatting_SetOpenMessageItem( 2, info->byIndex, 5 );
			}
			else
			{
				if( HT_SUCCEED( HT_extern_TrimuritiZone( g_wResentZoneServerID ) ) )
				{
                    g_cChatting->HT_vChatting_SetOpenMessageItem( 3, info->byIndex, 4 );
				}
				else
				{
					//	�ֽ��� ���� �ƴϸ� ������ ���ٴ� �޽��� �߰�
				}
			}
			HT_DELETE( info );
			return;
		}
		//	�ֽ� ���� ������ �������� ��� �ڽ��� �ֽŰ� �����ܿ쿡�� ó������ �ʴ´�. �ù�
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_CHANGEGODCHARM1 )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
			{
				HT_DELETE( info );
				return;
			}
		}
		//	�ֽ� ���� ������ �������� ��� �ڽ��� �ֽŰ� �����ܿ쿡�� ó������ �ʴ´�. ����帶
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_CHANGEGODCHARM2 )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
			{
				HT_DELETE( info );
				return;
			}
		}
		//	�ֽ� ���� ������ �������� ��� �ڽ��� �ֽŰ� �����ܿ쿡�� ó������ �ʴ´�. �񽴴�
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_CHANGEGODCHARM3 )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
			{
				HT_DELETE( info );
				return;
			}
		}
	}
	g_pNetWorkMgr->RequestItemUse( info );

	// ������ ����Ѱ��� �ľ�
    m_bPotionItemUse_Sw = HT_TRUE;
	// ������ ��� �� ������ Ÿ��
	m_dwItemUse_DelayTime = timeGetTime();

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Item_Use : %d(%d:%d)", m_dwUseItemKeyID, info->byPlace, info->byIndex );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );

	//	������ ����� ����Ʈ Ʋ���ֱ�
	//	�̵��� Ǫ��Ƽī
	if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVE_PUSTICA ||
		g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVEPOSPUSTICA )
	{
		HTint iTempFXID;
		g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
		//	ĳ���� �̵����ϰ� ����
		g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

		// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
		if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
			g_cIndividualStore->HT_vIndividualStore_Close();
		}
	}
	else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_PARTYMEMBERCALL )
	{
		HTint iTempFXID;
		g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_PARTYMEMBERCALL, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	}
}

HTint HTItemControl::HT_iItemControl_SetPrimiumItem( HTint iIndex, HTint iAddDay )
{
	// ���� �ð� ���ϱ�
	time_t now, timeTime; time( &now );

	g_cMainCharacter->HT_bMainChar_GetTimeStamp( iIndex, timeTime );

	if (timeTime <  now)	// �����ϰų� ����Ǿ��ٸ� ���� +30�� ����
		timeTime = now + (3600 * 24) * iAddDay;
	else				// �׷��� �ʴٸ� ���� �Ⱓ���� +30�� �߰�
		timeTime += (3600 * 24) * iAddDay;

	g_cMainCharacter->HT_vMainChar_SetTimeStamp( iIndex, timeTime );

	return HT_TRUE;
}

//----------��Ʈ��ũ_������ ��� ���----------//
HTvoid HTItemControl::HT_vNetWork_SCP_RESP_Item_Use_Result( MSG_ITEM* info )
{
	//-----������ ����Ѱ��� �ľ�-----//
    m_bPotionItemUse_Sw = HT_FALSE;
 
	if( info->byPlace == ITEM_PLACE_EVENT ) // �̺�Ʈ ���� ��� ����� ���
	{
		g_cNPCControl->HT_vNetWork_RegistLottery( info->byResult, 0 );
	}
	else // �Ϲ� ������ ��� ����� ���
	{
		// ������ KeyID �˾Ƴ���
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID );
		
		// ������ ����ϴ� �Ҹ��� ����.
		g_pEngineHandler->HT_hrPlaySound( 33010, 1 );

		// ������ ������ �˻��� ���ؼ� ������ ���� ���� �ε����� ���Ѵ�
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(iKeyID); 

        if( info->byResult == 0)
		{
			// �Ⱓ�� �����۵��� ��� ��� Ŭ���̾�Ʈ���� �ð��� �����ؼ� ó���Ѵ�. (������ �ð������� �ٽ� ���� �ʴ´�) 2004. 11. 22 ������
			if (dwItemIndex >= 6951 && dwItemIndex <= 6956 || dwItemIndex >= 7064 && dwItemIndex <= 7067 || dwItemIndex == 7074 || dwItemIndex == 6736) 
			{
				/*
				6951	��Ÿ	�Ѵ� ���� �κ��丮�� Ȯ������ݴϴ�
				6952	���λ���Ȯ��	�Ѵ� ���� ���λ���ũ�⸦ Ȯ���մϴ�
				6953	���Ǿ� �ڵ� ����	���ǾƸ� �ڵ� ���� �մϴ�
				6954	�Ѵ� �ƴ��ٹ�	�Ѵ޵��� ����,�������ݷ�20%%~30%%���(����������)
				6955	�Ѵ� ��Ʈ��	�Ѵ޵��� HP�� 27%% + 270 ���� �մϴ�(����������)
				6956	�Ѵ� ��� ��ũ�� ���	�Ѵ� ���� ��� ��ũ�� 15 ����մϴ�

				7064	�ƴ��ٹ� �ٷ���
				-	�κ��丮 Ȯ�� �Ѵ� ����	-	���λ��� Ȯ�� �Ѵ� ����	-	�ڵ� �� �ݱ� �Ѵ� ����	-	�ƴ��ٹ� ȿ�� �Ѵ� ����

				7065	��Ʈ�� �ٷ���
				-	�κ��丮 Ȯ�� �Ѵ� ����	-	���λ��� Ȯ�� �Ѵ� ����	-	�ڵ� �� �ݱ� �Ѵ� ����	-	��Ʈ�� ȿ�� �Ѵ� ����

				7066	��� �ٷ���
				-	�κ��丮 Ȯ�� �Ѵ� ����	-	���λ��� Ȯ�� �Ѵ� ����	-	�ڵ� �� �ݱ� �Ѵ� ����	-	�ƴ��ٹ��� ȿ�� �Ѵ� ����
				-	��Ʈ�� ȿ�� �Ѵ� ����

				7067	�÷�Ƽ�� �ٷ���
				-	�κ��丮 Ȯ�� �Ѵ� ����	-	���λ��� Ȯ�� �Ѵ� ����	-	�ڵ� �� �ݱ� �Ѵ� ����	-	�ƴ��ٹ��� ȿ�� �Ѵ� ����
				-	��Ʈ�� ȿ�� �Ѵ� ����	-	All ��ũ�� 15 ���� ȿ�� �Ѵ� ����

				7074 �÷�Ƽ�� �ٷ��� 7�ϱ�
				*/

				switch (dwItemIndex)
				{
					case 6951:	// ��Ÿ
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����

						HT_vItemControl_SetMessage( eMsgPremiumItemEffect1 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6952:	// ���λ���Ȯ��
						HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect2 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6953:	// ���Ǿ� �ڵ� ����
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect3 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6954:	// �Ѵ� �ƴ��ٹ�
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect4 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6955:	// �Ѵ� ��Ʈ��
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect5 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6956:	// �Ѵ� ��� ��ũ�� ���
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect6 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7064:	// �Ѵ� �ƴ��ٹ�
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						}
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect7 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7065:	// ��Ʈ�� �ٷ���
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
							HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						}
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect8 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7066:	// ��� �ٷ���
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
							HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						
							HT_vItemControl_SetMessage( eMsgPremiumItemEffect9 );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						}
						break;
					case 7067:	// �÷�Ƽ�� �ٷ���
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
						HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect10 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7074:	// �÷�Ƽ�� �ٷ��� (7�ϱ�)
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 7);
						g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
						HT_iItemControl_SetPrimiumItem(eTime_Store, 7);
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 7);
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 7);
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 7);
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 7);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect10 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6736:	// �̺�Ʈ �÷�Ƽ�� �ٷ��� (30�ϱ�)
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// �κ��丮 ũ�� �ʱ� ����
						HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect10 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
				}
				
				HT_vItemControl_SetMessage( eMsgPremiumItemEffect11 );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
			}

//			if (dwItemIndex == 7073)	// �̺�Ʈ ������ ���������� �˸�.
//			{
//				HT_vItemControl_SetMessage( eMsgEventItemUseOK );
//				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
//			}
		}

		
		if( info->kItem.byCount == 0 )
		{
			// �����Կ� ��ϵ� �������� ��� ������ ���� �����
			//g_cQuickSlot->HT_vQuickSlot_DeleteItem( iKeyID );
			// ������ ����
			g_cItemSystem->HT_vItemSystem_DeleteItem( iKeyID );
		}
		else
		{
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iKeyID, info->kItem.byCount );
		}
		// �����Կ� ��ϵǾ��ִ� �������� ���
		if( g_cQuickSlot->HT_bBeUsedKeyID( dwItemIndex, iKeyID ) )
			g_cQuickSlot->HT_vResultActionItem( iKeyID );

		// ������ ��뿡 ���� ���º����� �������� �����ش�

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("ReceiveSend_Item_Use:ClientSide:%d(ServerSide:%d-%d)", 
																		m_dwUseItemKeyID, iKeyID, info->kItem.byCount);
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
}

// �κ��丮 ũ�� Ȯ��
HTvoid HTItemControl::HT_vItemControl_ExpandInventorySize( HTint& iBagSize , HTint iInventory )
{
	if( iBagSize <= 0 )
	{
		iBagSize = 0;
		return;
	}

	HTint iCurSize = g_cEquipInventory->HT_byGetInventorySize(iInventory);
	HTint iNewSize = 0;
	if( iCurSize < _INVEN_WIDTH )
	{
		if( (_INVEN_WIDTH - iCurSize) <= iBagSize )	// Ȯ��� ũ�Ⱑ ��Ȱ���� bagũ�⺸�� Ŭ ���
		{
			iNewSize = _INVEN_WIDTH ;
			iBagSize -= ( _INVEN_WIDTH - iCurSize );
		}
		else
		{
			iNewSize = iCurSize + iBagSize;
			iBagSize = 0;
		}

		g_cEquipInventory->HT_vRenewalPossibleBar(iInventory, iNewSize );
	}
}

//	Get m_bPotionItemUse_Sw
HTbool HTItemControl::HT_vItemControl_GetItemUseSw()
{
	DWORD dwPass = GetTickCount();
	if( dwPass < m_dwItemUse_DelayTime+1000 )
		return m_bPotionItemUse_Sw;

	m_bPotionItemUse_Sw = HT_FALSE;
	return m_bPotionItemUse_Sw;
}

// ȭ�� �ڵ� ä��� - ã�� �������� KeyID ��ȯ
HTbool HTItemControl::HT_bItemControl_RefillArrow( HTdword dwKeyID, HTdword dwItemIndex )
{
	// �ٸ� �������� �̵��ϰ� ���� ���� ���� ����
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_NONE )
	{
		if( dwItemIndex > 0 )
		{
			// ���� ����(�ε����� ����)�� �������� �κ��丮���� ã�Ƽ� �ٽ� ä���.
			HTdword dwFindKeyID = 0;		// ã�� �������� KEyID
			HT_ITEMSETTING_FLAG sLocRoom;	// ã�� �������� ��ġ
			g_cItemSystem->HT_vItemSystem_GetItemPos( dwItemIndex, dwKeyID, ITEM_LOCATION_PC, dwFindKeyID, sLocRoom);
			if( dwFindKeyID > 0 ) // �������� ã���� ���
			{
				// ������ ���� ��ġ ����
				m_sSource_Item.nLocation = ITEM_LOCATION_PC;
				m_sSource_Item.nInventory = sLocRoom.nInventory;
				m_sSource_Item.pCellPos = sLocRoom.pCellPos;
				// �������� �̵��� ��ġ ����
				m_sTarget_Item.nLocation = ITEM_LOCATION_EQUIP;
				m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;
				m_sTarget_Item.pCellPos.x = m_sTarget_Item.pCellPos.y = 0;
				// ���콺�� ���� �̵��� �������� �ƴϱ⶧����
				// �κ��丮���� �ٸ� ȭ���� ã���� ��� ���� �̹����� ���� �����ش�.
				// ������ �̵� ��û
				HT_vItemControl_Network_ReqMove();
				return HT_TRUE;
			}
		}
	}

	return HT_FALSE;
}

//----------������ �̵� ��û----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove()
{	
	PS_CSP_REQ_ITEM_MOVE info = HT_NULL;
	info = new S_CSP_REQ_ITEM_MOVE;

	// �������� �ִ� ���� ��ġ
	if( m_sSource_Item.nLocation == ITEM_LOCATION_PC )
	{
		info->byFromPlace = ITEM_PLACE_INVEN;
		info->snFromIndex = (m_sSource_Item.pCellPos.x * _INVEN_HEIGHT + m_sSource_Item.pCellPos.y)
							+ (m_sSource_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byFromPlace = ITEM_PLACE_EQUIP;
		info->snFromIndex = m_sSource_Item.nInventory;
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_NPC )
	{
		info->byFromPlace = ITEM_PLACE_CARGO;
		info->snFromIndex = (m_sSource_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sSource_Item.pCellPos.x)
							+ (m_sSource_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_ASHRAMCARGO )
	{
		info->byFromPlace = ITEM_PLACE_GUILDCARGO;
		info->snFromIndex = (m_sSource_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sSource_Item.pCellPos.x)
							+ (m_sSource_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
		info->snFromIndex += (g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120);
	}
	else
	{
		HT_vItemControl_SettingItem( HT_FALSE );
		return;
	}
	// �������� �̵��� ��ġ
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_PC )
	{
		info->byToPlace = ITEM_PLACE_INVEN;
		info->snToIndex = (m_sTarget_Item.pCellPos.x * _INVEN_HEIGHT + m_sTarget_Item.pCellPos.y)
							+ (m_sTarget_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
	}
	else if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byToPlace = ITEM_PLACE_EQUIP;
		info->snToIndex = m_sTarget_Item.nInventory;
	}
	else if( m_sTarget_Item.nLocation == ITEM_LOCATION_NPC )
	{		
		info->byToPlace = ITEM_PLACE_CARGO;
		info->snToIndex = (m_sTarget_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sTarget_Item.pCellPos.x)
							+ (m_sTarget_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
	}
	else if( m_sTarget_Item.nLocation == ITEM_LOCATION_ASHRAMCARGO )
	{
		info->byToPlace = ITEM_PLACE_GUILDCARGO;
		info->snToIndex = (m_sTarget_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sTarget_Item.pCellPos.x)
							+ (m_sTarget_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
		info->snToIndex += (g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120);
	}
	else
	{
		HT_vItemControl_SettingItem( HT_FALSE );
		return;
	}

	g_pNetWorkMgr->RequestItemMove( info );
	 
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemMove : From(%d:%d), To(%d:%d)", 
	//									info->byFromPlace, info->snFromIndex, info->byToPlace, info->snToIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
//----------������ �̵� ��û_���----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove_Result( PS_SCP_RESP_ITEM_MOVE info )
{
	// ������ ���� ��ġ ����
//	m_dwActiveItemKeyID = info->dwKeyID;
	if( HT_bItemControl_ReqMoveResult_SetItemPos(info) == HT_FALSE )
		return;

	// �̵� ����
	HT_vItemControl_ItemAntiActive();

	if( info->nResult == 0x00 )
	{
		// �������� �̵��ǰų� �����Ҷ��� �Ҹ��� ư��.
		DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
		if( dwItemIndex > 0 )
		{
			HTdword dwSoundID = g_pEngineHandler->HT_dwGetItemEquipSoundID( dwItemIndex );
			if ( dwSoundID > 0 )
				g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );

			// ������ ���� ��ġ ����
			m_dwActiveItemIndex = dwItemIndex;

			//----------������ �̵� ��û���� ���ؾ��� �׼ǵ�----------//
			HT_vItemControl_Network_ReqMove_Result_Check();
		}
	}
	else
	{
		//-----�̵��� �� ���� ��-----//
		HT_vItemControl_SettingItem( HT_FALSE );

		switch(info->nResult)
		{
			case REPLY_ITEM_MOVE_LAY_DISABLE : // ������ ��ø �Ұ�
				HT_vItemControl_SetMessage( eMsgItemPackNotPack );
				break;
			case REPLY_ITEM_MOVE_INVENTORY_LACK : // �κ��丮 ���� ����	
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case REPLY_ITEM_MOVE_DISTANCE_ERR: // �̵� �Ÿ� ����
				HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
				break;
			case REPLY_ITEM_MOVE_PLACE_ERR: // �̵� ��ġ ����
				HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
				break;
			case REPLY_ITEM_MOVE_OWNER_ERR: // ������ ������ ����
				HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
				break;
			case REPLY_ITEM_MOVE_ROUTING_TIME: // ������ ���� �ð� ����
				HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
				break;
			case REPLY_ITEM_MOVE_BAG:		// Ȯ���κ��丮�� ������ ����
				HT_vItemControl_SetMessage( eMsgItemEquipDecExistItem );
				break;
			case REPLY_ITEM_MOVE_NOMOVE: // �̵��� �� ���� ������
				HT_vItemControl_SetMessage( eMsgItemMoveCannot );
				break;
			case REPLY_ITEM_MOVE_TWOHAND :	// ��չ��� ���� ����
				HT_vItemControl_SetMessage( eMsgItemMoveTwoHandErr );
				break;
			default :						// ������ �̵� ����
				HT_vItemControl_SetMessage( eMsgItemMoveFail );
				break;
		}
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

// ������ �̵� ��û ����� ������ �������� ��� ��ġ ����
HTbool HTItemControl::HT_bItemControl_ReqMoveResult_SetItemPos( PS_SCP_RESP_ITEM_MOVE info )
{
	// ������ KeyID �˾Ƴ���
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byFromPlace, info->snFromIndex, iKeyID );

	// ������ �̵� ���� - �������� �̵��ϴ� �� �ٸ� �������� ����� ó���ؾ��� ��� ���
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE && m_dwActiveItemKeyID != iKeyID )
		HT_vItemControl_ItemAntiActive();
	m_dwActiveItemKeyID = iKeyID;
	
	// �������� ���� ��ġ ����
	g_cItemSystem->HT_bItemSystem_GetItemPos(iKeyID, m_sSource_Item );

	// �������� �̵��� ��ġ ����
	// �̵��� �������� ��쿡�� target��ġ�� �ǹ��ֱ� ������
	if( info->nResult == 0x00 )
	{
		BYTE byType = info->byToPlace;

		if( byType == ITEM_PLACE_INVEN )
		{
			HTint iInvenSize = _INVEN_WIDTH * _INVEN_HEIGHT;

			m_sTarget_Item.nLocation = ITEM_LOCATION_PC;
			m_sTarget_Item.nInventory = info->snToIndex / iInvenSize ;
			m_sTarget_Item.pCellPos.x = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) / _INVEN_HEIGHT; 
			m_sTarget_Item.pCellPos.y = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) % _INVEN_HEIGHT;
		}
		else if( byType == ITEM_PLACE_EQUIP )
		{
			m_sTarget_Item.nLocation = ITEM_LOCATION_EQUIP;
			m_sTarget_Item.nInventory = info->snToIndex;
			m_sTarget_Item.pCellPos.x = m_sTarget_Item.pCellPos.y = 0;
		}
		else if( byType == ITEM_PLACE_CARGO )
		{
			HTint iInvenSize = _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT;

			m_sTarget_Item.nLocation = ITEM_LOCATION_NPC;
			m_sTarget_Item.nInventory = info->snToIndex / iInvenSize ;
			m_sTarget_Item.pCellPos.x = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) % _GOODSKEEP_INVEN_WIDTH; 
			m_sTarget_Item.pCellPos.y = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) / _GOODSKEEP_INVEN_WIDTH;
		}
		else if( byType == ITEM_PLACE_GUILDCARGO )
		{
			HTint iInvenSize = _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT;
			HTint iDivide = info->snToIndex/120;
			info->snToIndex -= (iDivide*120);
			m_sTarget_Item.nLocation = ITEM_LOCATION_ASHRAMCARGO;
			m_sTarget_Item.nInventory = info->snToIndex / iInvenSize ;
			m_sTarget_Item.pCellPos.x = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) % _GOODSKEEP_INVEN_WIDTH; 
			m_sTarget_Item.pCellPos.y = ( info->snToIndex - (m_sTarget_Item.nInventory * iInvenSize) ) / _GOODSKEEP_INVEN_WIDTH;
		}
		else
			return HT_FALSE;
	}

	return HT_TRUE;
}

// �����ߴ� �������� ������ ����� ó��
HTvoid HTItemControl::HT_vItemControl_ItemMove_UnEquip( HTint iInventory )
{
	// KeyID ����
	HTint iActiveItemKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, (HTbyte)iInventory, iActiveItemKeyID);
	// ������ ��ġ ��������
	HT_ITEMSETTING_FLAG sLocRoom;
	g_cItemSystem->HT_bItemSystem_GetItemPos( iActiveItemKeyID, sLocRoom );
	
	if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		HTdword dwActiveItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( iActiveItemKeyID );

		//-------������ �����۰� ���õ� Bar �����--------//
		// ���� �Ұ����ϰ� �� �������� �����ϰ� �־��� ��� �Ұ��ɹ� �����
		if( g_cItemSystem->HT_bItemSystem_GetPossible( iActiveItemKeyID, HT_TRUE ) == HT_FALSE )
		{
			HTint nCellNum = g_cItemSystem->HT_iItemSystem_GetCellNumber(iActiveItemKeyID);
		}

		if( sLocRoom.nInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )	// ������ 
		{
			// ���õ� �������� FX ���ֱ�
			// ���� ����
			if( g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( iActiveItemKeyID ) > 0 )
				g_pEngineHandler->HT_hrDetachItemMainRefineEffect(g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex );
			// �Ӽ� ����
			if( g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( iActiveItemKeyID ) > 0 )
				g_pEngineHandler->HT_hrDetachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex );

			if ( HT_IS_ITEM_WEAPON( dwActiveItemIndex ) )
			{
				g_cEquipInventory->HT_vEquipInventory_SetRightItem( 0 );
				g_cEquipInventory->HT_vEquipInventory_SetRightItem_KeyID( 0 );
				g_cMainCharacter->HT_vMainChar_SetArmsType( 0 );
			}

			// ��� �������� ��� ���� �̹��� �����
			if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwActiveItemIndex )
							|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwActiveItemIndex ) )
			{
				// �޼տ� �������� �������� �ʾ��� ��� �޼� ��Ʈ�� �����
				if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) == 0 )
				{
					// �̹��� �����
					g_cUIManager->HT_SetSlotImage( _DIALOG_EQUPINVENTORY, _INVEN_DEFENCE_WEAPON, 0 );
					// ���� �� �����
				}
			}
		}
		// �޼� �������� ���� ��� 
		else if( sLocRoom.nInventory ==  ITEM_LOCATION_EQUIP_LEFT_HAND )
		{
			g_cEquipInventory->HT_vEquipInventory_SetLeftItem( 0 );

			DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
			if( dwKeyID > 0 )
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
				// ������ �������� ��տ��̸� ���ʿ� ��Ʈ�� �׸���
				if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwIndex )	|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwIndex ) )
				{
					// �̹��� �׸���
					// ����� �׸���
				}
			}
		}
		else if( sLocRoom.nInventory == ITEM_LOCATION_EQUIP_HEAD )
		{
			if( dwActiveItemIndex == ITEMINDEX_ASSISTANTHAT )		//	�������ڸ� ����� �Ƚ����
				m_bAssistant = HT_FALSE;
		}
		// Ȯ��� �κ��丮 ������ ���
		else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwActiveItemIndex ) )
		{
			// �ý��� â�� ǥ��
			// Ȯ��� �κ��丮�� �����߽��ϴ�.
			HT_vItemControl_SetMessage( eMsgItemEquipInvenDecOK );

			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );

			// Bag1�� �⺻���� ��� ����Ѵ�
			if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) > 0 ) // Bag2�� Ȯ��Ǿ� �־��ٸ�
			{
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, 0);
			}

			if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG3) > 0 ) // Bag3�� Ȯ��Ǿ� �־��ٸ�
			{
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG3, 0);
			}
			// �⺻ �κ�(Bag1) ����
		}

        //------- ĳ���� �ܰ� �ٲٱ�(������ ����) --------//
		HTint iNormalItem, iLeftItem;
		iNormalItem = dwActiveItemIndex, iLeftItem = 0;
		if( sLocRoom.nInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalItem ) )
			{	iLeftItem = iNormalItem;		iNormalItem = 0; 	}
		}
		g_cEquipSystem->HT_EquipSys_UnEquip( g_cMainCharacter->HT_vMainChar_GetModelID(), g_oMainCharacterInfo.snTribe,
												iNormalItem, iLeftItem, g_cMainCharacter->HT_vMainChar_GetHeadType() );
			
		if ( HT_IS_ITEM_WEAR( dwActiveItemIndex ) )
			g_cMainCharacter->HT_vMainChar_SetWearItem( 0 );

		//	���� �������� ��� �����Ÿ� �����ϱ�
		if( dwActiveItemIndex == HT_INDEX_TOTEM_JACUNAEARANI )
			g_cMainCharacter->HT_vMainChar_SetTotemItemRange( 0 );

		// ���� �������� ���� ������ ǥ�� (20030520, DAEHO)
		//this->HT_vDelDurability( dwActiveItemIndex );
	}	// end of if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
}

// �������� ����� ó��
HTvoid HTItemControl::HT_vItemControl_ItemMove_Equip( HTdword dwActiveItemKeyID, HTint iTargetInventory )
{
	// ������ ��ġ ��������
	HT_ITEMSETTING_FLAG sSourceLocRoom;
	g_cItemSystem->HT_bItemSystem_GetItemPos( dwActiveItemKeyID, sSourceLocRoom );
	
	HTdword dwActiveItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwActiveItemKeyID );

	if( iTargetInventory != 0x00 && iTargetInventory != ITEM_LOCATION_EQUIP_BAG)
	{
		HTdword iNormalIndex, iLeftIndex;
		iNormalIndex = dwActiveItemIndex;	iLeftIndex = 0;
        if( iTargetInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalIndex ) )
			{	iLeftIndex = iNormalIndex;	iNormalIndex = 0;		}
		}
        g_cEquipSystem->HT_EquipSys_Equip( g_cMainCharacter->HT_vMainChar_GetModelID(), (HTbyte)g_oMainCharacterInfo.snTribe,
											iNormalIndex, iLeftIndex, g_cMainCharacter->HT_vMainChar_GetHeadType() );
	}
	if( HT_IS_ITEM_WEAR( dwActiveItemIndex ) )
		g_cMainCharacter->HT_vMainChar_SetWearItem( dwActiveItemIndex );
	
	if( iTargetInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )	// ������/���
	{
		// ���� ������ �Ǿ� �ִ� (����) �������� FX ����
		HTbyte byMainRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( dwActiveItemKeyID );
		if( byMainRefineLevel > 0 )
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																dwActiveItemIndex, byMainRefineLevel );
		
		// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
		HTint iSubRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( dwActiveItemKeyID );
		if( iSubRefineLevel > 0 )
		{
			HTint iAttribute = g_cItemSystem->HT_iItemSystem_GetAttributeSubRefineItem( dwActiveItemKeyID );
			// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
			g_pEngineHandler->HT_hrAttachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex,
																(HTESubRefineType)iAttribute, iSubRefineLevel );
		}
		//	���� �����϶��� ���� ����� �����Ѵ�.
		if ( HT_IS_ITEM_WEAPON( dwActiveItemIndex ) )
		{
			g_cMainCharacter->HT_vMainChar_SetArmsType( dwActiveItemIndex );
			g_cEquipInventory->HT_vEquipInventory_SetRightItem( dwActiveItemIndex );
			g_cEquipInventory->HT_vEquipInventory_SetRightItem_KeyID( dwActiveItemKeyID );
		}
	} 
	else if( iTargetInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )	// �޼�
	{
		if( HT_IS_ITEM_SHIELD( dwActiveItemIndex ) )
            g_cEquipInventory->HT_vEquipInventory_SetLeftItem( dwActiveItemIndex );

		DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
		if( dwKeyID > 0 )
		{
			DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
			// ������ �������� ��տ��̸� ���ʿ� ����� �����
		}
	}
	else if( iTargetInventory == ITEM_LOCATION_EQUIP_HEAD )
	{
		if( dwActiveItemIndex == ITEMINDEX_ASSISTANTHAT )		//	�������ڸ� ����� �Ƚ����
			m_bAssistant = HT_TRUE;
	}
	// �κ��丮 Ȯ���� ���
	else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwActiveItemIndex ) )	
	{
		HTint iBagSize = 0; 
		if( g_pParamMgr->HT_bGetItemEffect1Param1( dwActiveItemIndex, &iBagSize ) == false || iBagSize <= 0 )
			return;

		// Bag1 Ȯ��
		if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG1) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG1 );
		}
		// Bag2 Ȯ��
		if( iBagSize > 0 && g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG2 );
		}
		// Bag3 Ȯ��
		if( iBagSize > 0 && g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG3) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG3 );
		}

		// �ý��� â�� ǥ��
		// �κ��丮�� Ȯ��ƽ��ϴ�.
		HT_vItemControl_SetMessage( eMsgItemEquipInvenIncOK );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	/*
	else
	{//fors_debug ���˿���,�����ط��ķ���
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																4001, 15 );
		
	}*/

	// ���� �������� ���� ���� ǥ��(20030520,DAEHO)
	//this->HT_vReformDurability( dwActiveItemKeyID );

	//	Ʃ�丮�� �ý����� ����
	if (g_cTutorialSystem)
	{
		if (7==g_cTutorialSystem->HT_iGetTutorialStep())
			g_cTutorialSystem->HT_vAddTutorialStep( TUTORIAL_STEP_GETITEM );
	}

	//	���� �������� ��� �����Ÿ� �����ϱ�
	if( dwActiveItemIndex == HT_INDEX_TOTEM_JACUNAEARANI )
	{
		int iRange = 0;
		g_pParamMgr->HT_bGetItemEffect1Param1( dwActiveItemIndex, &iRange );
		g_cMainCharacter->HT_vMainChar_SetTotemItemRange( iRange );
	}
}

//----------������ �̵� ��û���� ���ؾ��� �׼ǵ�----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove_Result_Check()
{ 
	//---------������ ���� ����: ������ ��ġ�� �ٲٱ� ���� ó���ؾ� �Ѵ�. --------//
	// �����ߴ� �������� ������ ����� ó��
	if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )
		HT_vItemControl_ItemMove_UnEquip( m_sSource_Item.nInventory );

	// �������� ����� ó��
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
		HT_vItemControl_ItemMove_Equip( m_dwActiveItemKeyID, m_sTarget_Item.nInventory );

	//	Set Item
	this->HT_vItemControl_SettingItem( HT_TRUE );

	// ���� �������� ���� ���� ǥ�� ���� : ������ ��ġ�� �ٲ� �Ŀ� ó���ؾ� �Ѵ�.
	if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )	// Ż��
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )	// ����
	{
		g_cItemSystem->HT_vItemSystem_SetDurabilityWarning( m_sTarget_Item.nInventory );
		//	�޼տ� ������ �������ϰ�� ���⿡ �´� �ִϸ��̼� ����
		if( m_sTarget_Item.nInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )
			g_cMainCharacter->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	
	// �Ҹ� ������(ȭ�� ����)�� ��� ������â�� ��ϵǾ������� ��ϵ� KeyID�� �ٲ�����Ѵ�.
	if( (CHTParamIDCheck::HT_bIsItemUsable( m_dwActiveItemIndex ) && !CHTParamIDCheck::HT_bIsItemUsableArrow( m_dwActiveItemIndex )) ||
		CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwActiveItemIndex ) )
	{
		// ������ â�� ��ϵǾ��ִ� �������� PC�κ��丮 �̿��� ��ҷ� �̵����� ��� �����
		if( m_sTarget_Item.nLocation != ITEM_LOCATION_PC )
		{
			g_cQuickSlot->HT_vDeleteIconInAllSlotByIndex( m_dwActiveItemIndex, (HTint)m_dwActiveItemKeyID );
		}
		else
		{
			HTint iKeyID = 0;
			HTint index = ( m_sTarget_Item.pCellPos.x * _INVEN_HEIGHT + m_sTarget_Item.pCellPos.y ) 
											+ ( m_sTarget_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );

			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, index, iKeyID);
			g_cQuickSlot->HT_bChangeIconByKeyID( m_dwActiveItemKeyID, iKeyID );
		}
	}
}

// �ʿ� ������
HTvoid HTItemControl::HT_vItemControl_Network_ReqDrop( )
{
	PS_CSP_REQ_ITEM_DROP info = NULL;
	info = new S_CSP_REQ_ITEM_DROP;

	info->dwMoney = 0;
	// �������� �ִ� ���� ��ġ
	if( m_sSource_Item.nLocation == ITEM_LOCATION_PC )
	{
		info->byFromPlace = ITEM_PLACE_INVEN;
		info->byIndex = (m_sSource_Item.pCellPos.x * _INVEN_HEIGHT + m_sSource_Item.pCellPos.y)
							+ (m_sSource_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byFromPlace = ITEM_PLACE_EQUIP;
		info->byIndex = m_sSource_Item.nInventory;
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_NPC )
	{
		info->byFromPlace = ITEM_PLACE_CARGO;
		info->byIndex = (m_sSource_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sSource_Item.pCellPos.x)
							+ (m_sSource_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
	}
	else
	{
		HT_vItemControl_SettingItem( HT_FALSE );
		return;
	}

	// �������� �̵��� ��ġ
	info->snX = m_sTarget_Item.pCellPos.x;
	info->snZ = m_sTarget_Item.pCellPos.y;

	g_pNetWorkMgr->RequestItemDrop( info );
	 
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemDrop : From(%d:%d), To(%d:%d)", 
	//														info->byFromPlace, info->byIndex, info->snX, info->snZ );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );

	//	�� �ִ����� ���� ��
	m_byResent = RESENT_STEP_ITEM_MOVE;
}

HTvoid HTItemControl::HT_vItemControl_Network_ReqDrop_Result( PS_SCP_RESP_ITEM_DROP info )
{
	if( info->byType == DROP_TYPE_MONEY ) // �ʿ� ���Ǿ� ������
	{
		if( info->snResult == 0x00 )
		{
			HTdword dwMoney = 0;
			if( info->dwMoney < 0 )
				dwMoney = 0;
			else
				dwMoney = info->dwMoney;
			
			if( info->byPlace == ITEM_PLACE_INVEN )	// PC �κ��� �� ������
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( dwMoney );
			else									// NPC �κ��� �� ������
				g_cEquipInventory->HT_vEquipInventory_SetNPCMoney( dwMoney );
		}
	}
	else
	{
		// KeyID ����
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
		m_dwActiveItemKeyID = iKeyID;

		// �̵� ����
		//HT_vItemControl_ItemAntiActive();

		if( info->snResult == 0x00 )
		{
			// �������� �̵��ǰų� �����Ҷ��� �Ҹ��� ư��.
			DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
			if( dwItemIndex > 0 )
			{
				HTdword dwSoundID = g_pEngineHandler->HT_dwGetItemEquipSoundID( dwItemIndex );
				g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );
				
				m_dwActiveItemIndex = dwItemIndex;
			}
			else
				return;

			/* �޼տ� ������ �������� ������ ��� �����տ� ��վ������� �����ϰ� �ִٸ� 
				�̹����� �׷���� �ϱ� ������ �������� ���� ����� ��ó���� �ϵ��� ����. 2003.12.11. ���� */
			// �����ߴ� �������� ������ ����� ó��:������ ó���� �ϱ� ���� ó���ؾ� �Ѵ�.
			if( info->byPlace == ITEM_PLACE_EQUIP )
				HT_vItemControl_ItemMove_UnEquip( info->byIndex );

			// ������ �����
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwActiveItemKeyID );
		
			// ���� �������� ���� ���� ǥ��:�������� ó�� �� �Ŀ� �ؾ��Ѵ�.
			g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning();
			
			// �Ҹ� �������� ��� ������ â�� ��ϵǾ��ִ��� �˻��ؼ� �����
			if( CHTParamIDCheck::HT_bIsItemUsable( dwItemIndex ) )
			{
				g_cQuickSlot->HT_vDeleteIconInAllSlotByIndex( dwItemIndex, (HTint)m_dwActiveItemKeyID );
			}
		}
		else
		{
			//HT_vItemControl_SettingItem( HT_FALSE );
			switch(info->snResult)
			{
				case REPLY_ITEM_MOVE_INVENTORY_LACK :	
					// �κ��丮 ���� ���� 
					HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
					break;
				case REPLY_ITEM_MOVE_DISTANCE_ERR:	
					// �̵� �Ÿ� ���� 
					HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
					break;
				case REPLY_ITEM_MOVE_PLACE_ERR:
					// �̵� ��ġ ���� 
					HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
					break;
				case REPLY_ITEM_MOVE_OWNER_ERR:
					// ������ ������ ���� 
					HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
					break;
				case REPLY_ITEM_MOVE_ROUTING_TIME:
					// ������ ���� �ð� ���� 
					HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
					break;
				default :
					// ������ ������ ���� 
					HT_vItemControl_SetMessage( eMsgItemMoveFail );
					break;
			}
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
		}
	}
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

// �ʿ��� �ݱ�
HTvoid HTItemControl::HT_vItemControl_Network_ReqGet()
{
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return;

	PS_CSP_REQ_ITEM_GET info = NULL;
	info = new S_CSP_REQ_ITEM_GET;

	info->nItemID = m_dwGetItemKeyID;
	g_pNetWorkMgr->RequestItemGet( info );
	 
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemGet : %d", info->nItemID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
	
	if (g_cTutorialSystem)
	{
		if (_DIALOG_TUTORIALWND_12==g_cTutorialSystem->HT_iGetTutorialStep())
			g_cTutorialSystem->HT_vAddTutorialStep( TUTORIAL_STEP_GETITEM );
	}
}
 
HTvoid HTItemControl::HT_vItemControl_Network_ReqGet_Result( PS_SCP_RESP_ITEM_GET info )
{
	HTdword dwItemKeyID = info->snIndex + HT_ITEM_INDEX_START;
	HT_Trace("\nReqGetResult:%d-ID %d Money %d\n", info->nResult, dwItemKeyID, info->dwMoney );
	if( info->nResult == 0x00 )
	{
		if( CHTParamIDCheck::HT_bIsItemUsableMoney( dwItemKeyID ) && info->dwMoney > 0 )	// �ʿ��� ���Ǿ� �ݱ�
		{
			m_iMoneyForMessage = info->dwMoney - g_cEquipInventory->HT_iEquipInventory_GetPCMoney() ;

			if( m_iMoneyForMessage > 0 ) 
			{
				// ��Ƽ�� �����Ǿ��ְ� �ڵ��й� ����� ���
				if( g_cParty->HT_iParty_GetPartyMemberCount() > 0 && g_cParty->HT_bParty_GetRootingMode() )
					HT_vItemControl_SetMessage( eMsgRupiahMoveAutoReceive ); // [�ڵ��й�]%s���Ǿ� ȹ��
				else
					HT_vItemControl_SetMessage( eMsgRupiahReceive ); // %s ���ǾƸ� ȹ���߽��ϴ�.
			}
			else
				m_szMessage.HT_hrCleanUp();

			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );	// ���Ǿ� ����
		}
		else
		{
			// %s��(��) ȹ���߽��ϴ�.
			if( g_pParamMgr->HT_bGetItemName( dwItemKeyID, &m_szObjectName ) == true )
				HT_vItemControl_SetMessage( eMsgItemMoveReceive );
			else
				m_szMessage.HT_hrCleanUp();
		}
		if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );

		// �ڵ� ��ŷ���� ��� �Ǵ� �ʿ��� �ֿ� �����ۿ� �߰� ������ ���� ��츦 ���� ���� ������ �޾ƾ� �ϴµ�
		// �������� �ڵ����� ������ ���� ������ ���������� ������ ��û�� �ʿ� ����. 2003.05.15
		
		//----------������ �Ⱦ��� ������ �ʱ�ȭ----------//
		g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
	}
	else
	{
		switch(info->nResult)
		{
			case REPLY_ITEM_MOVE_INVENTORY_LACK :	
				// �κ��丮 ���� ���� 
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case REPLY_ITEM_MOVE_DISTANCE_ERR:	
				// �̵� �Ÿ� ���� 
				HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
				break;
			case REPLY_ITEM_MOVE_PLACE_ERR:
				// �̵� ��ġ ���� 
				HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
				break;
			case REPLY_ITEM_MOVE_OWNER_ERR:
				// ������ ������ ���� 
				HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
				break;
			case REPLY_ITEM_MOVE_ROUTING_TIME:
				// ������ ���� �ð� ���� 
				HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
				break;
			case REPLY_ITEM_MOVE_PART :	// (��ø��)������ �Ϻθ� �ݱ�
				// %s��(��) ȹ���߽��ϴ�.
				HT_vItemControl_SetMessage( eMsgItemMoveReceive );
				break;
			default :
				// ������ �ݱ� ���� 
				HT_vItemControl_SetMessage( eMsgItemMoveFail );
				break;
		}
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	//m_byResent = RESENT_STEP_NONE;
	//m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

//----------������ ������ ��ŷ�� ��û----------//
HTvoid HTItemControl::HT_vItemControl_Network_Req_ItemPacking( HTbyte byType )
{
	MSG_Packing* info = HT_NULL;
	info = new MSG_Packing;

	info->byType = byType;

	// �������� �ִ� ���� ��ġ
	if( m_sSource_Item.nLocation == ITEM_LOCATION_PC )
	{
		info->byFromPlace = ITEM_PLACE_INVEN;
		info->byFromIndex = (m_sSource_Item.pCellPos.x * _INVEN_HEIGHT + m_sSource_Item.pCellPos.y)
							+ (m_sSource_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byFromPlace = ITEM_PLACE_EQUIP;
		info->byFromIndex = m_sSource_Item.nInventory;
	}
	else if( m_sSource_Item.nLocation == ITEM_LOCATION_NPC )
	{
		info->byFromPlace = ITEM_PLACE_CARGO;
		info->byFromIndex = (m_sSource_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sSource_Item.pCellPos.x)
							+ (m_sSource_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
	}
	else
	{
		HT_vItemControl_SettingItem( HT_FALSE );
		return;
	}

	// �������� �̵��� ��ġ
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_PC )
	{
		info->byToPlace = ITEM_PLACE_INVEN;
		info->byToIndex = (m_sTarget_Item.pCellPos.x * _INVEN_HEIGHT + m_sTarget_Item.pCellPos.y)
							+ (m_sTarget_Item.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
	}
	else if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byToPlace = ITEM_PLACE_EQUIP;
		info->byToIndex = m_sTarget_Item.nInventory;
	}
	else if( m_sTarget_Item.nLocation == ITEM_LOCATION_NPC )
	{
		info->byToPlace = ITEM_PLACE_CARGO;
		info->byToIndex = (m_sTarget_Item.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + m_sTarget_Item.pCellPos.x)
							+ (m_sTarget_Item.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT);
	}
	else
	{
		HT_vItemControl_SettingItem( HT_FALSE );
		return;
	}

	if( byType == ITEMPACKING_TYPE_PACKING )	// ������ ��ø�� ���
	{
		info->byFromCount = (HTbyte)g_cItemSystem->HT_iItemSystem_GetItemCount( m_dwActiveItemKeyID );
		info->byToCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_nDestItemKeyID );
	}
	else// 	ITEMPACKING_TYPE_UNPACKING - ������ �и��� ���
	{
		info->byFromCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_dwActiveItemKeyID );
		info->byToCount = m_nUnPackCount;
	}

	g_pNetWorkMgr->RequestItemPacking( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemPacking: %d - Des(%d,%d:%d)Sou(%d,%d:%d)", info->byType,
	//	info->byFromPlace, info->byFromIndex, info->byFromCount, info->byToPlace, info->byToIndex, info->byToCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
   
//----------������ ������ ��ŷ�� ��û_���----------//
HTvoid HTItemControl::HT_vItemControl_Network_Resp_ItemPacking( MSG_Packing* info )
{
	HTint iFromKeyID = 0;	// �̵��Ϸ��� ������
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byFromPlace, info->byFromIndex, iFromKeyID );
	m_dwActiveItemKeyID = iFromKeyID;

	HTint iToKeyID = 0;	// �̵��� ��ġ�� �ִ� ������
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byToPlace, info->byToIndex, iToKeyID );

	// �̵� ����
	HT_vItemControl_ItemAntiActive();

	if( info->byType == ITEMPACKING_TYPE_PACKING )	// ������ ��ø ���
	{
		// �ٸ� ������ ���� �̵��� ������ 
		if( info->byFromCount == 0 )
		{
			g_cItemSystem->HT_vItemSystem_DeleteItem( iFromKeyID );

			// ������â�� ��ϵ� �������� �ٸ� �����۰� ������ ���
			g_cQuickSlot->HT_bChangeIconByKeyID( iFromKeyID, iToKeyID );
		}
		else
		{
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iFromKeyID, info->byFromCount );

			// �������� ���� ��ġ ã��
			g_cItemSystem->HT_bItemSystem_GetItemPos( iFromKeyID, m_sSource_Item );
			HT_vItemControl_SettingItem( HT_FALSE );
		}

		// target �������� ���� ����
		g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iToKeyID, info->byToCount );
	}
	else	// ������ �и� ���
	{
		if( info->byResult == 0 )	// ����
		{
			// source
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( m_dwActiveItemKeyID, info->byFromCount - info->byToCount );

			STRUCT_ITEM sItem; // ���� ������ ����
			g_cItemSystem->HT_bItemSystem_GetItemInfo( m_dwActiveItemKeyID, sItem );
			// �� ������ ����
			PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
			item->byType			= SET_ITEM_CREATE;
			item->byPlace			= info->byToPlace;
			item->byIndex			= info->byToIndex;
			item->sitem.byCount		= info->byToCount;

			item->sitem.snIndex		= sItem.snIndex - HT_ITEM_INDEX_START;
			item->sitem.byRefineLevel = sItem.byRefineLevel;
			item->sitem.snDurability = sItem.snDurability;
			item->sitem.byDummy		= sItem.byDummy;
			item->sitem.snDummy		= sItem.snDummy;
			item->sitem.wSerial		= sItem.wSerial;
			// �ּ����� ����
			for( HTint i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i )
				item->sitem.bySubRefine[i] = sItem.bySubRefine[i];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );	
			HT_DELETE( item );
		}
		// �������� ��� ó���� �ܰ� ����.
	}

	// ���� ��û �ܰ�
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;

//	if (g_cObjectInfo)
//		g_cObjectInfo->HT_vObjectInfo_InfoCheck( this->m_nIndex, (*ZOder)->m_nIndex );	// ���Թڽ� ���� ���
}