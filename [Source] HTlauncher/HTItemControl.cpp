#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htitemcontrol.h"

#include <queue>

#define UNPACKING_WIN_XPOS		300
#define UNPACKING_WIN_YPOS		300

// 아이템 이동 상태
#define ITEMCONTROL_STATUS_NONE				1	// 정지
#define ITEMCONTROL_STATUS_MOVE				2	// 이동

// 메세지창 0:메세지창안뜸,1:작업완료
#define ITEMCONTROL_MESSAGE_NONE				0
#define ITEMCONTROL_MESSAGE_COMPLETE			1	
#define ITEMCONTROL_MESSAGE_CONFRIM				2

#define UNPACKING_MOVE_NONE						0x00
#define UNPACKING_MOVE_INVEN					0x04	// PC 인벤
#define UNPACKING_MOVE_GOODSCHARGE				0x05	// NPC 인벤
//#define UNPACKING_MOVE_GILDINVEN				0x06	// 길드 인벤
#define UNPACKING_MOVE_TRADE					0x07	// 트레이드

// 현재 작업 
#define RESENT_STEP_NONE				0
#define RESENT_STEP_PACKING				1
#define RESENT_STEP_UNPACKING			2
#define RESENT_STEP_ITEM_MOVE			3
#define RESENT_STEP_EQUIP				4
#define RESENT_STEP_TRADE_MOVE			5
#define RESENT_STEP_BAG_USE				6
#define RESENT_STEP_BAG_CANCEL			7
#define RESENT_STEP_ITEM_GET			8

#define BAG_CHANGE_TIME					0.5f	// bag을 전환하기 위해 탭 위에 대기해야하는 시간
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
	//-----아이템 장착할수 있는공간에 바표현-----//
	m_sPossible_BarInfo.nBitmapNo = -1;
	m_sPossible_BarInfo.nDlgNo = -1;
	m_sPossible_BarInfo.nGroupNo = -1;
	m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
	m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;

	// 현재 작업 - PACKING/UNPACKING에서만 사용함
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= m_dwGetItemKeyID = RETURNTYPE_MAINGAME_FAILD;

	m_fTimeForBag = 0.0f;	// bag 전환 시간
	m_iSelectBagNo = SELECT_BAG_NONE;

	m_pTimer->Do( HT_TIMER_STOP );
	HT_DELETE( m_pTimer );
}

//-----초기화-----//
HTvoid HTItemControl::HT_vItemControl_Init()
{
	//-----초기 로딩-----//
	HT_vItemControl_Init_LoccationPosLoad();

	//-----아이템 장착할수 있는공간에 바표현-----//
	m_sPossible_BarInfo.nInventory = -1;
	m_sPossible_BarInfo.nBitmapNo = -1;
	m_sPossible_BarInfo.nDlgNo = -1;
	m_sPossible_BarInfo.nGroupNo = -1;
	m_sPossible_BarInfo.nCellPosx = m_sPossible_BarInfo.nCellPosy = -1;
	m_pPossible_BarSize.x = m_pPossible_BarSize.y = 0;

	//-----아이템 사용한건지 파악-----//
    m_bPotionItemUse_Sw = HT_FALSE;

	//-----아이템 사용후 딜레이 타임-----//
	m_dwItemUse_DelayTime = timeGetTime();

	// 현재 작업 - PACKING/UNPACKING에서만 사용함
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= m_dwGetItemKeyID = RETURNTYPE_MAINGAME_FAILD;

	//	조교모자 초기화
	m_bAssistant = HT_FALSE;

	m_fTimeForBag = 0.0f;	// bag 전환 시간
	m_iSelectBagNo = SELECT_BAG_NONE;

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );
}

//-----초기 로딩-----//
HTvoid HTItemControl::HT_vItemControl_Init_LoccationPosLoad()
{
	m_nItemControl_Status	= ITEMCONTROL_STATUS_NONE;
	m_dwActiveItemKeyID		= RETURNTYPE_MAINGAME_FAILD;
	m_bSetTargetItem_Sw		= HT_FALSE;
}
//------- 메세지 출력  ------//
HTvoid HTItemControl::HT_vItemControl_SetMessage( HTint idMessage )
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
		HT_vItemControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemControl_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vItemControl_SetParamTextForMessage( sParam3, &szOut3 );

		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vItemControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemControl_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 다른 캐릭터 이름
		case eMsgParamOthercharName :
			break;
		
		// 아이템 이름
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

//-----버튼 체크_Switch ON-----//
HTRESULT HTItemControl::HT_bItemControl_ButtonCheck_SwitchOn( HTint iBeforDlgNo, HTint iBeforeCellNo, HTint iCurDlgNo, HTint iCurCellNo )
{
    // 다른 작업을 서버에 요청을 하고 기다리고 있는 경우 처리하지 않음
	if( m_byResent != RESENT_STEP_NONE )
		return HT_FAIL;

	//----------각윈도우 활성화 상태 체크->선택한 아이템 검색----------//
	HT_ItemReturnRoom sSourceRoom = HT_vItemControl_ActiveEachWindowCheck( iBeforDlgNo, iBeforeCellNo );
	HT_ItemReturnRoom sTargetRoom = HT_vItemControl_ActiveEachWindowCheck( iCurDlgNo, iCurCellNo );
	//if( sTargetRoom.nInventory != -1 )
	{
		// 특정 공간에 대해서는 이동이 불가능합니다.
		if (iCurCellNo == -1 || !(iBeforDlgNo == _DIALOG_EQUPINVENTORY || iBeforDlgNo == _DIALOG_INVENTORY2 || iBeforDlgNo == _DIALOG_GOODSKEEPWND || iBeforDlgNo == _DIALOG_ASHRAMCAGO ) 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE 
			|| g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE
			|| g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMCAGO ) == HT_TRUE )
		{
			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );
			DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);
			
			// 특정 아이템은 이동이 불가
			if( HT_SUCCEED(HT_IS_CANNOTMOVEITEM(dwItemIndex)))
			{
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgCommonNotMoveTredeItem, &strMessage, _T(""), _T("") );	//	본 아이템은 땅에 버리거나 거래할 수 없습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
				return HT_FAIL;
			}
		}

		// 마우스가 PC 인벤토리에 있을 경우
		if( sTargetRoom.nLocation == ITEM_LOCATION_PC)
		{
			// BAG2를 사용하지 못하는 상태일 경우 처리하지 않음
			if( sTargetRoom.nInventory == ITEM_LOCATION_PC_BAG2 
						&& g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_FALSE )
				return HT_OK;

			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );

			if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
				return HT_FAIL; 

			// 수리/해체 모드일 경우
			if( g_cNPCControl->HT_bNPCControl_IsItemFixActive() || g_cNPCControl->HT_bNPCControl_IsItemDisjointActive() )
			{
				g_cNPCControl->HT_vNPCControl_FixDisjoint_LButtonClick(dwItemKeyID);
				return HT_OK;
			}
			// 제련 모드일 경우
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
			{
				//HTRESULT res = g_cNPCControl->HT_hrNPCControl_ItemWork_LButtonClick( dwItemKeyID );

				// 제련모드일때 제련가능한 아이템외의 다른 종류의 아이템을 이동할 수 있게 하기 위함
//				if( res == HT_OK )	
//					return HT_OK;
			} 
			// 개인 상점 g_cUIManager모드일 경우
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) == HT_TRUE )
			{
				if (iBeforeCellNo >= 100)
				{
					g_cIndividualStore->HT_vIndividualStore_SelectItemForSell( dwItemKeyID );
					return HT_OK;
				}
			}
			// 위탁 상점 모드일 경우
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE && g_cRentalStore->m_nWindowType == 1)
			{
				if (iBeforeCellNo >= 100)
				{
					g_cRentalStore->HT_vRentalStore_SelectItemForSell( dwItemKeyID, iCurCellNo );
					return HT_OK;
				}
			}
			// 1:1 교환 중일 경우
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE )
			{
				if (iBeforeCellNo >= 100) 
				{

					//	착용 아이템은 교환되면안된다.
					if( iCurCellNo <100 )
						return HT_FAIL; 
						
					HTRESULT res = g_cExchangeSystem->HT_hrExchange_SetMyTradeItem( dwItemKeyID, sSourceRoom );
					if( res == HT_OK )	
						return HT_OK;
				}
			}
			// 헌납 모드일 경우
			else if ( g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND1) ||  g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND2) )
			{
				if (iBeforeCellNo >= 100) 
				{
					g_cNPCControl->HT_vNPCControl_OfferingItemAdd( dwItemKeyID );
					return HT_OK;
				}
			}
			// 복권등록 모드일 경우
			//else if( sLocRoom.nLocation == ITEM_LOCATION_PC && g_cNPCControl->HT_bNPCControl_IsRegistLotteryActive() )
			//{
			//	if( dwItemKeyID != RETURNTYPE_MAINGAME_FAILD )
			//	{
			//		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);
			//		if(dwItemIndex == 0)
			//			return HT_FAIL;

			//		// 개봉안된 복권과 '꽝'복권을 제외한 이벤트(복권) 아이템
			//		if( LOTTERY_ITEM_INDEX != dwItemIndex && LOTTERY_ITEM_INDEX_FAIL != dwItemIndex )	 
			//			HT_vNetWork_CSP_RESP_Item_Use( dwItemKeyID, sLocRoom.nCellPosx, 0x01 );
			//		
			//		return HT_OK;
			//	}
			//}
		}
		// 마우스가 equipment 에 있을 경우
		else if( sTargetRoom.nLocation == ITEM_LOCATION_EQUIP )
		{
			DWORD dwItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sSourceRoom );
			// 수리 모드일 경우
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
		
		//	아이템을 움직일수 있는지 판단하여 움직이도록 셋팅한다.
		this->HT_vItemControl_SelectItemCheck( sSourceRoom );

		return HT_OK;
	}

	return HT_FAIL;
}

//-----버튼 체크_Switch Off-----//
HTRESULT HTItemControl::HT_vItemControl_ButtonCheck_SwitchOff( HTint iDlgNo, HTint iCellNo )
{
	// 다른 작업을 서버에 요청을 하고 기다리고 있는 경우 처리하지 않음
	if( m_byResent != RESENT_STEP_NONE )
		return HT_FAIL;

	HT_ItemReturnRoom sLocRoom;
	//----------각윈도우 활성화 상태 체크->선택한 아이템 검색----------//
	sLocRoom = HT_vItemControl_ActiveEachWindowCheck( iDlgNo, iCellNo );
	if( sLocRoom.nInventory != -1 )
	{
		//----------아이템 셋팅 위치 확보----------//
		HT_vItemControl_SecurityItemSettingPos( sLocRoom );
		//----------제한 사항 체크----------//
		// 이동 위치 검사
		HTbool	bRes = HT_bItemControl_Limit_InInventory( HT_TRUE );
        
		if( bRes == HT_FALSE )
		{
			// 이동 정지
			HT_vItemControl_ItemAntiActive();
			HT_vItemControl_SettingItem( HT_FALSE );
			return HT_FAIL;
		}
	}
	else
	{
		//	6. 맵위에서 다른 아이템이 있을 때_없는 곳을 찾아 셋팅
		if( iDlgNo == -1 )
		{
			// 인벤토리 확장용 아이템이 확장을 위해 사용됐을 경우 바닥에 버릴 수 없다.
			if( (m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP && m_sSource_Item.nInventory == ITEM_LOCATION_EQUIP_BAG ) 
								|| HT_vItemControl_Limit_InMap() == HT_FALSE )
			{
				// 이동 정지
				HT_vItemControl_ItemAntiActive();
				HT_vItemControl_SettingItem( HT_FALSE );
			}
		}
		else
		{
			// 이동 정지
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

// 아이템 이동 정지
HTvoid HTItemControl::HT_vItemControl_ItemAntiActive()
{
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE )
	{
		// 이동 정지
		m_nItemControl_Status = ITEMCONTROL_STATUS_NONE;
	}
}


//--------아이템 이동중 ESC에 의해서 창이 닫힐 경우 아이템 원래 자리에 놓기------//
HTvoid HTItemControl::HT_vItemControl_ESC_ItemAntiActive()
{
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE)
	{
		//	유아이 시스템에 그림 이동 정지 셋팅
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

//----------마우스가 어떤 윈도우 안에 있는지 체크----------//
HT_ItemReturnRoom HTItemControl::HT_vItemControl_ActiveEachWindowCheck( HTint iDlgNo, HTint iCellNo )
{
	//	1. 인벤토리 위치 선택
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
  
//----------선택한 아이템 검색->활성화 아이템으로 셋팅----------//
HTvoid HTItemControl::HT_vItemControl_SelectItemCheck( HT_ItemReturnRoom sLocRoom )
{
	// 미용실 이용권 사용중에 아이템 이동을 시도했다면 다른 문제 발생을 막기 위해 창을 닫아 버린다.
	if( g_cUIManager->HT_isShowWindow(_DIALOG_BEAUTYSALON2) == HT_TRUE )
	{
		g_cStatus->HT_vStatus_BeautyBack();	// 원래상태로 성형 돌림
		g_cUIManager->HT_HideWindow(_DIALOG_BEAUTYSALON2);
	}

	m_dwActiveItemKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch( sLocRoom );
	if( m_dwActiveItemKeyID != RETURNTYPE_MAINGAME_FAILD )
	{
		m_nItemControl_Status = ITEMCONTROL_STATUS_MOVE;
		//-----아이템 이동_소스 정보-----//
		m_sSource_Item.nLocation = sLocRoom.nLocation;
		m_sSource_Item.nInventory = sLocRoom.nInventory;
		m_sSource_Item.pCellPos = g_cItemSystem->HT_ptItemSystem_GetInventoryPos( m_dwActiveItemKeyID );

		//-----아이템 이동가능 이벤토리 바표시를 위한 아이템 사이즈-----//
		//m_pPossible_BarSize = g_cItemSystem->HT_ptItemSystem_GetSize( m_dwActiveItemKeyID );
		m_pPossible_BarSize.x = m_pPossible_BarSize.y = 1;
	}
}

//----------아이템 셋팅 위치 확보----------//
HTvoid HTItemControl::HT_vItemControl_SecurityItemSettingPos( HT_ItemReturnRoom sLocRoom )
{
	m_sTarget_Item.nLocation = sLocRoom.nLocation;
	m_sTarget_Item.nInventory = sLocRoom.nInventory;
	m_sTarget_Item.pCellPos.x = sLocRoom.nCellPosx;
	m_sTarget_Item.pCellPos.y = sLocRoom.nCellPosy;
}

//----------제한 사항 체크_인벤토리 안에서----------//
HTbool HTItemControl::HT_bItemControl_Limit_InInventory( HTbool bType )
{
	if( bType == HT_TRUE )
	{
		DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
		if( dwItemIndex == 0 )
		{
			return HT_FALSE;
		}

		//	1. 같은곳
		if( m_sTarget_Item.nLocation == m_sSource_Item.nLocation &&
			m_sTarget_Item.nInventory == m_sSource_Item.nInventory &&
			m_sTarget_Item.pCellPos.x == m_sSource_Item.pCellPos.x &&
			m_sTarget_Item.pCellPos.y == m_sSource_Item.pCellPos.y )
		{
			return HT_FALSE;
		}
		// 퀘스트 전용 아이템을 PC인벤 이외의 장소로 옮기려고 할 경우
		if( CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) && m_sTarget_Item.nLocation != ITEM_LOCATION_PC )
			return HT_FALSE;

		//	2. 다른 아이템이 장착돼어 있을 때
		//	3. 인벤토리 사이즈
		//	4. 장착 불가
		HTint nResult = HT_RESULT_ITEM_MOVE_FAIL; 
		if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
		{
			// 아이템 이동 위치 교정
			HTbool bRes = HT_bItemControl_Network_ReqEquip_LocationCheck(dwItemIndex);	
			if( bRes == HT_FALSE )	// 장착할 수 없는 아이템이면
				return HT_FALSE;

			// 이동 위치에 장착한 아이템이 있을 경우
			if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( m_sTarget_Item.nInventory ) )
				nResult = HT_RESULT_ITEM_MOVE_FAIL;
			else
				nResult = HT_RESULT_ITEM_MOVE_OK;
		}
		else
			nResult = g_cItemSystem->HT_iItemAlSetPosInventoryCheck( m_dwActiveItemKeyID, dwItemIndex, m_sTarget_Item );
  
		if( nResult == HT_RESULT_ITEM_MOVE_FAIL )			//	이동(장착) 불가일때
		{
			return HT_FALSE;
		}
		else if( nResult == HT_RESULT_ITEM_MOVE_OK )		//	이동(장착)
		{
			//----------맵위의 픽업된 아이템 초기화 및 아이템 정보창 초기화----------//
			if( m_sSource_Item.nLocation == ITEM_LOCATION_MAP )
			{
				g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
			}

			//----------서버에 이동(장착) 요청----------//
			if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
			{
				if(m_sTarget_Item.nInventory == ITEM_LOCATION_EQUIP_BAG )	// 인벤토리 확장
				{
					HT_vItemControl_Network_ReqMove();
					m_byResent = RESENT_STEP_ITEM_MOVE;
				}
				else	// 아이템 장착
				{
					// 아이템 착용 조건 검사
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
			// 상거래 관련/1:1 교환/수집재료 교환
			else 
				return HT_FALSE;
		}
		else if( nResult > HT_RESULT_ITEM_MOVE_OK )		//	패킹할때
		{
			
			// 일부 아이템은 패킹 할 수 없다. 2004. 11. 11 선영범
			//if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE) return HT_FALSE;

			m_nDestItemKeyID = (DWORD)nResult;
			//----------서버에 아이템 패킹을 요청----------//
			if( m_byResent == RESENT_STEP_NONE ) // 서버 요청 단계
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

// 아이템이 이동가능한 아이템인지 아니면 시간제 및 특정(이동 불가능한) 아이템인지 구별하여 결과 반환
HTbool HTItemControl::HT_bItemControl_IsItemTimeItem(DWORD dwItemIndex)
{
	// 특정 아이템은 아이템 패킹/언패킹 및 교환이나 개인상점에서도 그 기능을 적용할 수 없게 해야한다.
	if (dwItemIndex >= 6801 && dwItemIndex <= 6840 || 
		dwItemIndex >= 7093 && dwItemIndex <= 7094 )
		return HT_FALSE;
	return HT_TRUE;
}

// 제조창에 아이템을 놓을 경우 위치 교정
HTvoid HTItemControl::HT_vItemControl_EconomyLocationCheck( )
{
	// 보조재료
	m_sTarget_Item.nInventory = ITEM_LOCATION_ECONOMY_AIDITEM;
	m_sTarget_Item.pCellPos.x = 0;	
	m_sTarget_Item.pCellPos.y = 0;
}

//	6. 맵위에서 다른 아이템이 있을 때_없는 곳을 찿아 셋팅
HTbool HTItemControl::HT_vItemControl_Limit_InMap()
{
	// 퀘스트 전용 아이템은 버리지 못하게
	HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
	if( dwIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwIndex ) )
		return HT_FALSE;

	//	개인상점과 교환창창이 떠 있을때도 땅에 버리지 못하게 처리
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return HT_FALSE;

	//	2. 윈도우 위에 없을 때 맵위에 드롭
	//	2-1. 드롭할 위치 지정
	m_sTarget_Item.nLocation = ITEM_LOCATION_MAP;
	m_sTarget_Item.nInventory = ITEM_LOCATION_MAP_FIELD;
	m_sTarget_Item.pCellPos = HT_ptItemControl_SearchMapPosForItemDrop();
	// 좌표값이 이상하면
	if( m_sTarget_Item.pCellPos.x < 0 || m_sTarget_Item.pCellPos.x >= MAX_MAP_SIZE ||
											m_sTarget_Item.pCellPos.y < 0 || m_sTarget_Item.pCellPos.y >= MAX_MAP_SIZE )
		return HT_FALSE;

	// 맵에 버릴 것인지 재확인 메세지 띄운다
	// %s을 땅에 버리시겠습니까?
	if( g_pParamMgr->HT_bGetItemName( dwIndex, &m_szObjectName ) == true)
	{
		if (g_cMainCharacter->m_bMainChar_Live == false)	// 죽은상태라면 땅에 버릴수 없다.
			return HT_FALSE;

		HT_vItemControl_SetMessage( eMsgItemMoveDropQuestion );
		m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
		g_cEquipInventory->HT_vEI_SetMessageBox( _MESSAGEBOX_THROWITEM, m_szMessage.HT_szGetString() );
	}
	return HT_FALSE;
}

// 캐릭터 주변의 맵 좌표 중 빈 곳 찾기
HTPoint HTItemControl::HT_ptItemControl_SearchMapPosForItemDrop()
{
	// 드롭할 위치 랜덤하게 설정
	srand( (unsigned)time( NULL ) );
	HTint spaceX = 0, spaceY = 0;
	HTPoint pos;
	HTRESULT res = HT_FALSE;
	HTint nArea = 4;
	HTint nLoopCount = 0;	// 아이템 버릴 위치를 구하기 위해서 while문을 돌린 횟수

	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	while(1)
	{
		spaceX = rand() % nArea;	// 그냥 정한 숫자
		spaceY = rand() % nArea;

		pos.x = pPt.x + spaceX;	
		pos.y = pPt.y + spaceY;
		
		res = g_cItemSystem->HT_hrCheckMapPos(pos);
		if(res == HT_FALSE)	// 그 위치에 아이템이 없을 경우
		{
			// 이동 가능한 지역인지 검사해야함. 2004.1.6 선미
			//HTbool bCanMove = g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecTempPos, 0 );
			//if( bCanMove == HT_TRUE )
				break;			
		}

		++nLoopCount;

		// 일정 거리 안에 아이템을 버릴 곳을 a=30회 이상 찾지 못하면 b=2만큼 범위를 넓힌다.
		// 또 c=500회 이상 찾지 못할 경우 드롭하지 않는다.
		// a,b,c 는 임시로 정했음. 2003.07.04 선미
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

	// 좌표값이 이상하면
	if( pPt.x < 0 || pPt.x >= MAX_MAP_SIZE || pPt.y < 0 || pPt.y >= MAX_MAP_SIZE )
	{
		pPt.x = pPt.y = -1;
	}
	
	return pPt;
}

//----------상거래 관련 셋팅----------//
HTvoid HTItemControl::HT_vItemControl_EconomySetting( DWORD dwItemIndex )
{
	HTbool res = HT_FALSE; 

	if( dwItemIndex == -1 )
		return;

	// 재료아이템이 아닐 경우 제조창에 올리지 못한다
	if( CHTParamIDCheck::HT_bIsItemRefine( dwItemIndex ) == false )
		res = HT_FALSE;
	else
		res = g_cNPCControl->HT_bNPCControl_SetAidItemResource( m_dwActiveItemKeyID );

	HT_vItemControl_SettingItem( res );
}

// 인벤토리에 아이템을 넣을 위치가 있는지 검사
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
// 인벤토리에 해당 갯수만긐의 충분한 공간이 있는지 검사
HTint HTItemControl::HT_iItemControl_SearchBlankInventory();
{
	

	HTint bEquip = 0;
	DWORD dwItemKeyID = 

	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwIndex == 0 )
		return bEquip;

	for (iInventory=0; iInventory < 3; ++iInventory)	// 인벤토리 모두 검사
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

//----------컨트롤----------//
HTvoid HTItemControl::HT_vItemControl_Control()
{
	//-----컨트롤_아이템 줍기-----//
	HT_vItemControl_Control_PickUpItem();
}

//------ Bag을 전환하기 위한 시간 체크 시작 ----------//
HTvoid HTItemControl::HT_vStartTimeForBag( HTint iSelectedBagNo )
{
	if( m_fTimeForBag == 0.0f || m_iSelectBagNo != iSelectedBagNo )
	{
		m_iSelectBagNo = iSelectedBagNo;
		m_fTimeForBag = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// 현재 시간 저장
	}
}

//------ Bag을 전환하기 위한 시간 체크 중지 --------//
HTvoid HTItemControl::HT_vEndTimeForBag()
{
	m_fTimeForBag = 0.0f;
	m_iSelectBagNo = SELECT_BAG_NONE; 
}

//-----컨트롤_아이템 줍기-----//
HTvoid HTItemControl::HT_vItemControl_Control_PickUpItem()
{
	if( m_bSetTargetItem_Sw	== HT_FALSE )
		return;

	//----------맵위에서 아이템과의 거리를 체크----------//
	HTbool bResult = g_cItemSystem->HT_bItemSystem_PickUpItemCheck( m_dwGetItemKeyID );

	//----------맵위에서 올라온 아이템 인벤토리에 이동 가능한지 체크----------//
	if( bResult == HT_TRUE )
	{

		//----------특정 아이템은 마하라자만 집을 수 있도록 설정----------//
		//7361	카우스트밤 첫번째 조각
		//7362	카우스트밤 두번째 조각
		//7363	카우스트밤 세번째 조각
		//7364	카우스트밤 네번째 조각
		//7372	마히 던전 입장권
		//7379	아브 던전 입장권
		//7380	단바 던전 입장권
		//7381	나르 던전 입장권
		HTdword dwGetItemKeyID = g_cItemSystem->HT_bItemSystem_GetMapItemPickUpKeyID();
		if (dwGetItemKeyID == 7361 || dwGetItemKeyID == 7362 || dwGetItemKeyID == 7363 || dwGetItemKeyID == 7364 ||
			dwGetItemKeyID == 7372 || dwGetItemKeyID == 7379 || dwGetItemKeyID == 7380 || dwGetItemKeyID == 7381 )
			if( g_cGuildSystem->HT_byGuild_GetAuthority() < GUILD_AUTHORITY_RAJA )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg16, &strString );	// 마하라자만이 획득할 수 있습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				m_bSetTargetItem_Sw	= HT_FALSE;
				return;
			}

		HT_vItemControl_Network_ReqGet();
		m_bSetTargetItem_Sw	= HT_FALSE;
		//m_byResent = RESENT_STEP_ITEM_GET;
	}
}

//-------저장 장소 크기 반환---------//
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

//-----아이템을 지정-----//
HTvoid HTItemControl::HT_vItemControl_SetTargetItem( DWORD dwItemKeyID )
{
	m_bSetTargetItem_Sw	= HT_TRUE;
	m_dwGetItemKeyID = dwItemKeyID;
}

//----------아이템 셋팅----------//
HTvoid HTItemControl::HT_vItemControl_SettingItem( HTbool bType )
{
	// 양손무기일 경우 왼손에 비트맵을 그릴 것인지
	m_byResent = 0;
	HTbool bDrawTwinImage = HT_TRUE;
	HTdword dwLeftItemKeyID = 0;
	
	if( ( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP || m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP)
				&& m_sSource_Item.nInventory != ITEM_LOCATION_EQUIP_LEFT_HAND )
		dwLeftItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );

	if( bType == HT_TRUE )
	{
		// 왼손에 장착된 아이템이 있을 경우
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
		// 왼손에 장착된 아이템이 있을 경우
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

//----------서버에 장착 요청_왼손,오른손 체크----------//
HTbool HTItemControl::HT_bItemControl_Network_ReqEquip_LocationCheck(DWORD dwItemIndex)
{
	if( dwItemIndex <= 0 )
		return HT_FALSE;

	if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(dwItemIndex) )			// 머리
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_HEAD;

	else if( CHTParamIDCheck::HT_bIsItemAccessoryEarring(dwItemIndex) )	// 귀걸이
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_EAR ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_EAR;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_EAR ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_EAR;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_EAR;
	}
	else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace(dwItemIndex) )// 목걸이
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_NECK;
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceArmor(dwItemIndex) )		// 몸
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_ARMOR;
	
	else if( CHTParamIDCheck::HT_bIsItemDefencePants(dwItemIndex) )		// 바지
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_PANTS;

	else if( CHTParamIDCheck::HT_bIsItemDefenceGloves(dwItemIndex) )	// 장갑
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_GLOVE;

	else if( CHTParamIDCheck::HT_bIsItemDefenceBelt(dwItemIndex) )		// 벨트
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BELT;
	// 양손 | 활
	else if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand(dwItemIndex) || CHTParamIDCheck::HT_bIsItemWeaponThrow(dwItemIndex) )	
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;

	else if( CHTParamIDCheck::HT_bIsItemWeaponOneHand(dwItemIndex) )	// 오른손
	{
		//	암살자(아수라/략샤샤)일때 아수라 양손검일때를 체크한다.
		if( g_oMainCharacterInfo.snTribe == HT_ID_CHARACTER_ASURA || g_oMainCharacterInfo.snTribe == HT_ID_CHARACTER_RAKSHASA )
		{
			//	드바이라다 로카 스킬도 체크해야한다.
			if( g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( 3199 ) == 0  )
				m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
			else
			{
				//	만약 오른손에 검이 착용되어 있지 않으면
				if( g_cItemSystem->HT_dwSystem_GetItemIndex(g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_RIGHT_HAND)) == 0 )
				{
					m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
				}
				else
				{
					//	착용할려고 하는 아이템이 단검이면
					if( g_pEngineHandler->HT_bIsShortSword( dwItemIndex ) )
					{
						//	만약 오른손에 또같은 검을 착용하고 있으면
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
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceShield(dwItemIndex) )	// 왼손
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;
	
	else if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet(dwItemIndex) )// 팔찌
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_BRACELET ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_BRACELET;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_BRACELET ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_BRACELET;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_BRACELET;
	}
	else if( CHTParamIDCheck::HT_bIsItemAccessoryRing(dwItemIndex) )	// 반지
	{
		if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_RING ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_RING;
		else if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_RING ) == 0 )
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_RING;
		else
			m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_RIGHT_RING;
	}
	else if( CHTParamIDCheck::HT_bIsItemDefenceShoes(dwItemIndex) )	// 발
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_FOOT;
	
	else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(dwItemIndex) && dwItemIndex != 6307)	// 인벤토리확장 (차투랑가보드(6307)는 확장에 포함시키지 않음)
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BAG;
	else if( CHTParamIDCheck::HT_bIsItemCharm(dwItemIndex)) // 인벤확장
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_BAG;
	else if( CHTParamIDCheck::HT_bIsItemUsableArrow(dwItemIndex) && dwItemIndex != 7093 && dwItemIndex != 7094 )	// 화살
		m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;

	else
		return HT_FALSE;

	m_sTarget_Item.pCellPos.x = 0;	
	m_sTarget_Item.pCellPos.y = 0;	

	return HT_TRUE;
}

//----------소모성 아이템(물약 등)인지 검사-------------//
HTRESULT HTItemControl::HT_hrItemControl_ItemUse( HTint nDlgNo, HTdword dwItemKeyID )
{
	// 아이템 이동중이면 처리하지 않음
	if( m_nItemControl_Status != ITEMCONTROL_STATUS_NONE )
		return HT_FAIL;

	// 어느 인벤토리에 있는지 검색
	if( nDlgNo != _DIALOG_EQUPINVENTORY )	
		return HT_FAIL; // PC 인벤이 아닐 경우 처리 안함

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return HT_FAIL;

	return HT_hrItemControl_ItemUse( dwItemKeyID ) ;
}

HTRESULT HTItemControl::HT_hrItemControl_ItemUse( HTdword dwItemKeyID )
{
	HT_ITEMSETTING_FLAG sLocRoom;
	g_cItemSystem->HT_bItemSystem_GetItemPos(dwItemKeyID, sLocRoom);

	// 사용한 아이템이 확장공간이고 사용불가 일때
	if( g_cEquipInventory->HT_bGetInventoryUsable(ITEM_LOCATION_PC_BAG2) == HT_FALSE && sLocRoom.nInventory == ITEM_LOCATION_PC_BAG2)
		return HT_OK;

	// 아이템 이동중이면 처리하지 않음
	if( m_nItemControl_Status != ITEMCONTROL_STATUS_NONE )
		return HT_FAIL;

	if( dwItemKeyID == RETURNTYPE_MAINGAME_FAILD )
		return HT_FAIL;
	m_dwUseItemKeyID = dwItemKeyID;

	HTint dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(m_dwUseItemKeyID);
	if(dwItemIndex == 0)
		return HT_FAIL;

	// 일본의 경우 다음과 같은 대역의 아이템들은 사용시 인벤토리의 빈 공간이 8칸 이상이어야만 사용할 수 있다.
	if( g_iInationalType == INATIONALTYPE_JAPEN)
	{
		if (dwItemIndex >= 7064 && dwItemIndex <= 7067 || dwItemIndex >= 6737 && dwItemIndex <= 6741)
		{
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 8)
			{
				// 만약 공간이 부족하면 사용하지 못하게 한다.
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}
	}

	if( g_wResentZoneServerID == ZONE_ANAKAKURUMA )
	{
		//	차투입장권, 비류성 이동의 푸스티카, 레벨 제한 지역 입장권, 요새이동의 푸스티카
		if( dwItemIndex == 6722 || dwItemIndex == 6732 || dwItemIndex == 7049 || dwItemIndex == 7072 )
		{
			return HT_FAIL;
		}
	}
	
	// 소모성 아이템-화살 제외
	if( CHTParamIDCheck::HT_bIsItemUsable( dwItemIndex ) && !CHTParamIDCheck::HT_bIsItemUsableArrow( dwItemIndex ) ||
		CHTParamIDCheck::HT_bIsItemChargeContinuance( dwItemIndex ) )
	{
		// 아이템 사용 제한 조건 검사
		if( g_cItemSystem->HT_bItemSystem_GetPossible( m_dwUseItemKeyID, HT_TRUE ) == HT_FALSE )
		{
			// 아이템 사용제한 조건에 의해 사용할 수 없습니다.
			HT_vItemControl_SetMessage( eMsgItemUseConditionErr );

			// 완료창 띄움
			m_byMessageWin = ITEMCONTROL_MESSAGE_COMPLETE;
			g_cUIStatus->m_MessageBoxType = 1;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 0);

			return HT_OK;
		} 
		// 지바/이동의 푸스티카를 앉은 상태와 결투중일때는 사용할수 없게 처리 에서는 사용할 수 없게 처리
		if( dwItemIndex==HT_ITEM_MOVE_PUSTICA ||
			  dwItemIndex==HT_ITEM_MOVE_JIVAPUSTICA || 
			  dwItemIndex==HT_ITEM_MOVE_UPGRADEJIVAPUSTICA || 
			  dwItemIndex==HT_ITEM_HIGHZONE_TICKET ||
			  dwItemIndex==HT_ITEM_FORTRESSPUSTICA )
		{
			if (g_cMainCharacter->HT_bMainChar_GetSitDownState() == HT_TRUE ) 
			{
				// 아이템을 사용할 수 없는 상태입니다.
				HT_vItemControl_SetMessage( eMsgItemUseCannot );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			//if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
			//{
			//	CHTString strMessage;
			//	g_cUIManager->HT_SetScriptMessage( eMsgCommonNotUseInDuel, &strMessage, _T(""), _T("") );	//	결투중일때는 사용할수 없습니다.
			//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strMessage );
			//	return HT_OK;
			//}
		}

		// 요새 이동 푸스티카의 경우 차투랑가와 주신전에서 사용할 수 없다.
		if (dwItemIndex==HT_ITEM_FORTRESSPUSTICA)
		{
			if (g_wResentZoneServerID == 11 || g_wResentZoneServerID == 10)
			{
				// 아이템을 사용할 수 없는 지역입니다.
				HT_vItemControl_SetMessage( eMsgItemUseCannotNowZone );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}

		// 몬스터 소환 주문서는 파미르 지역에서만 사용가능
		else if( dwItemIndex == 6719 && g_wResentZoneServerID != 8 ) 
		{
			// 몬스터 소환 주문서는 파미르 지역에서만 사용할 수 있습니다.
			HT_vItemControl_SetMessage( eMsgPremiumItemMonsterEventError );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
			return HT_OK;
		}
		// 차크라 초기화 아이템일 경우 재확인 메세지 띄우기
		else if( dwItemIndex == HT_ITEM_INIT_CHAKRA )
		{
			// 초기화 하시겠습니까?
			HT_vItemControl_SetMessage( eMsgCharacterChakraInitQuestion );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 2;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		// 스킬 초기화 아이템일 경우 재확인 메세지 띄우기
		else if( dwItemIndex == HT_ITEM_INIT_CHAKRA || dwItemIndex == HT_ITEM_INIT_SKILL )
		{
			// 초기화 하시겠습니까?
			HT_vItemControl_SetMessage( eMsgCharacterSkillInitQuestion );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 3;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		// 차투랑가 입장권 사용시
		else if( dwItemIndex == 6722)
		{
			// 레벨이 30 미만이면 에러메시지 출력
			if (g_oMainCharacterInfo.byLevel < 30)
			{
				// 몬스터 소환 주문서는 파미르 지역에서만 사용할 수 있습니다.
				HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			// 주신 선택을 안했을 경우에도 에러메시지를 출력해야 한다.
			if (g_oMainCharacterInfo.byTrimuriti == 0 )
			{
				// 주신을 선택해야만 차투랑가에 입장할 수 있습니다.
				HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError2 );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}

			// 차투랑가 입장권을 사용하시겠습니까? [확인/취소]
			HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnter );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 4;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);

			return HT_OK;
		}
		else if (dwItemIndex == 6730)	// 창고 이용권 사용시 팝업
		{
			// 단 죽었을 경우에는 사용 불가
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
			{
				g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPING);
				g_cUIManager->HT_ShowWindow( _DIALOG_GOODSKEEPWND );
			}
			else
			{
				//HT_vItemControl_SetMessage( eMsgPremiumItemChaturangaEnterError2 );
				//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "죽은 상태에서는 사용할 수 없습니다." );

			}
		}
		// 퀘스트 초기화 아이템 사용시 재확인창 띄움 
		else if (dwItemIndex == 7077 || dwItemIndex >= 7061 && dwItemIndex <= 7063 || dwItemIndex == 7050) 
		{
			HT_vItemControl_SetMessage( eMsgReqUsingItem );

			m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
			g_cUIStatus->m_MessageBoxType = 5;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND ,m_szMessage , 1);
			m_dwSelectedUseItemKeyID = m_dwUseItemKeyID;
			return HT_OK;
		}
		else if (dwItemIndex >= 7064 && dwItemIndex <= 7067) //(꾸러미 아이템 포함)
		{
			if ( g_iInationalType == INATIONALTYPE_KOREA )
			{
				//HT_vItemControl_SetMessage( eMsgReqUsingItem );

				m_byMessageWin = ITEMCONTROL_MESSAGE_CONFRIM;
				g_cUIStatus->m_MessageBoxType = 6;
				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgShopReqBuyItem, &strMessage, _T(""), _T("") );	//	"정말 아이템을 사용하시겠습니까?\n[참고]자신의 컴퓨터 날짜가 정확하지 않을 경우 사용기간이 제대로 표기되지 않을 수 있습니다."
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
		else if( dwItemIndex == 7069)	// 요술 상자 사용시 이벤토리에 여유공간 체크
		{
			// 인벤토리 공간 체크
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 7)
			{
				// 만약 공간이 부족하면 사용하지 못하게 한다.
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				return HT_OK;
			}
		}
		else if ((dwItemIndex == 7071) || (dwItemIndex == 6764)) // 미용실 이용권 사용시
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
		else if (dwItemIndex == 6733) // 요술 상자 
		{
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 9)
			{
				// 만약 공간이 부족하면 사용하지 못하게 한다
				CHTString strString;
				HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// 인벤토리 공간이 부족합니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return HT_OK;
			}
		}

//		else if (dwItemIndex == 7073 || dwItemIndex == 7079) // 아이원잇 이벤트 아이템 사용시 라훌을 통해 사용할 수만 있으므로 여기서는 사용불가로 판정한다
//		{
			// 만약 공간이 부족하면 사용하지 못하게 한다.
//			HT_vItemControl_SetMessage( eMsgEventItemUseError );
//			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
//			return HT_OK;
//		}

		// 인벤토리 확장 방식 변경(착용방식으로)됨.
		if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwItemIndex ) )
			return HT_OK;

		// 위의조건에 모두 해당되지 않으면 아이템 사용
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID,/* sLocRoom.nCellPosx,*/ 0x01 );

		return HT_OK;
	}

	// 패키지 아이템 (3전통, 5전통 아이템의 경우 서버에 사용하는걸로 보낸다.)
	if (dwItemIndex == 7093 || dwItemIndex == 7094) 
	{
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID, 0x01 );
		return HT_OK;
	}

	// 개인상점 확장 아이템과 페타 아이템도 사용하는 아이템으로 처리
	if (dwItemIndex >= 6951 && dwItemIndex <= 6956) 
	{
		HT_vNetWork_CSP_RESP_Item_Use( m_dwUseItemKeyID, 0x01 );
		return HT_OK;
	}

	return HT_FAIL;
}

// 보관중인 위치 설정
HTvoid HTItemControl::HT_vItemControl_SetMoveFromPlace( HTint nDlgNo, HT_ItemReturnRoom sLocRoom )
{
	m_sSource_Item.nLocation = sLocRoom.nLocation;
	m_sSource_Item.nInventory = sLocRoom.nInventory;
	m_sSource_Item.pCellPos.x = sLocRoom.nCellPosx;
	m_sSource_Item.pCellPos.y = sLocRoom.nCellPosy;

	if(nDlgNo == _DIALOG_INVEN)			// PC 인벤토리
	{
		m_byFromPlace = UNPACKING_MOVE_INVEN;
	}
	else if( nDlgNo == _DIALOG_GOODSKEEPWND)	// NPC 인벤토리
	{
		m_byFromPlace = UNPACKING_MOVE_GOODSCHARGE;
	}
	//else if(nDlgNo == MAIN_DLG_INVEN)		// 길드 인벤토리
	//	m_byFromPlace = UNPACKING;
	else
	{
		m_byFromPlace = UNPACKING_MOVE_NONE;
	}
}

// 이동할 위치 설정
HTbool HTItemControl::HT_bItemControl_SetMoveToPlace( HTint nDlgNo )
{
	HT_ITEMSETTING_FLAG sSetItem;
	sSetItem.pCellPos.x = sSetItem.pCellPos.y = 0;	
	HTint bEquip = 0;

	if(nDlgNo == _DIALOG_EQUPINVENTORY)			// PC 인벤토리
	{
		m_byToPlace = UNPACKING_MOVE_INVEN;
		
		sSetItem.nLocation = ITEM_LOCATION_PC;
		// Bag1 검사
		if( g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG1 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG1;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
		// Bag2 검사
		if( bEquip == 0 && g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG2 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG2;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
		// Bag3 검사
		if( bEquip == 0 && g_cEquipInventory->HT_byGetInventorySize( ITEM_LOCATION_PC_BAG3 ) > 0 )
		{
			sSetItem.nInventory = ITEM_LOCATION_PC_BAG3;
			bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
		}
	}
	else if( nDlgNo == _DIALOG_GOODSKEEPWND)	// NPC 인벤토리
	{
		m_byToPlace = UNPACKING_MOVE_GOODSCHARGE;

		sSetItem.nLocation = ITEM_LOCATION_NPC;
		sSetItem.nInventory = ITEM_LOCATION_NPC_ITEMSAVED;
		bEquip = HT_iItemControl_SearchPosForUnPack( sSetItem.nLocation, sSetItem.nInventory, sSetItem.pCellPos );
	}
	//else if(nDlgNo == MAIN_DLG_INVEN)		// 길드 인벤토리
	//	m_byToPlace = UNPACKING;
	else if( nDlgNo == _DIALOG_TRADE )			// 트레이드
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

	return HT_FALSE; // 공간이 부족
}

// 언패킹할 아이템을 넣을 위치가 있는지 검사
HTint HTItemControl::HT_iItemControl_SearchPosForUnPack( HTint iLocation, HTint iInventory, HTPoint& pPt )
{
	HTPoint sourcePos = g_cItemSystem->HT_ptItemSystem_GetInventoryPos( m_dwActiveItemKeyID );	// source아이템의 위치
	//DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
	//if( dwIndex == 0 )
//		return HT_FALSE;

	HTint bEquip = 0;	// 결과

	//---------- 새아이템이 놓일 장소의 크기 구하기 -------------//
	HTPoint ptSize;
	if( iLocation == ITEM_LOCATION_PC )	
	{
		// PC 인벤토리일 경우 활성화되어있는 크기 구하기
		ptSize.x = g_cEquipInventory->HT_byGetInventorySize(iInventory);
		ptSize.y = _INVEN_HEIGHT;
	}
	else
		ptSize = g_cItemControl->HT_ptItemControl_LoctionSize ( iLocation );

	HT_ITEMSETTING_FLAG sSetItem;	// 아이템이 놓일 빈 장소의 위치
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
				// 새로운 위치에 자기 자신이 포함 될 경우에도 1이 반환 될수 있기 때문에 
				if( m_byFromPlace != m_byToPlace )	// 다른 인벤토리에 있을 경우
					break;
				// 같은 인벤토리 내에서 위치가 다를 경우
				else if( sSetItem.pCellPos.x != sourcePos.x || sSetItem.pCellPos.y != sourcePos.y )
					break;
				else
					bEquip = 0;
			}
		}
		if( bEquip == 1 )
		{
			// 새로운 위치에 자기 자신이 포함 될 경우에도 1이 반환 될수 있기 때문에 
			if( m_byFromPlace != m_byToPlace )	// 다른 인벤토리에 있을 경우
				break;
			// 같은 인벤토리 내에서 위치가 다를 경우
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

//----------서버에 요청_아이템 사용---------------//
//	bLoc 1:PCInventory, 2:quickslot
HTvoid HTItemControl::HT_vNetWork_CSP_RESP_Item_Use( DWORD dwKeyID,/* BYTE byPos,*/ BYTE byLocation, HTchar* pStr )
{
    HTint dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
	// 캐릭터가 사망 했을 시
	if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )
	{
		if( dwItemIndex != HT_INDEX_SELF_REVIVAL && 
			dwItemIndex != HT_INDEX_SELF_COMPLTEREVIVAL )
			return;
		else
		{
			// 확인창("확인버튼을 누르면 저장지역에서 다시 태어납니다.") 지우기
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
		//	dwItemIndex == HT_INDEX_SELF_COMPLTEREVIVAL ) // 살아있을 때 생명의 주문서 사용 안되게...
		//	return;
	//}

	//if (dwItemIndex == 7067) // 프리미엄 패키지 플래티넘 꾸러미는 최소 8칸 이상의 공간을 필요로 한다.
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "꾸러미를 풀기 위해서는 최소 8칸의 여유 공간이 필요합니다");
	//}


	// 아이템 사용할수 없을 때
	if( m_bPotionItemUse_Sw == HT_TRUE )
	{
		DWORD dwPass = GetTickCount();
		if( dwPass < m_dwItemUse_DelayTime+1000 )
			return;
	}

	// 아이템의 위치 구하기
	HT_ITEMSETTING_FLAG sLocRoom;
	if( byLocation != ITEM_PLACE_EVENT ) // 쿠폰(인벤에 없는 아이템)일 경우를 제외
	{
		if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwKeyID, sLocRoom ) == HT_FALSE )
			return;
	}

	m_dwUseItemKeyID = dwKeyID;

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	
	info->byType = HT_MSG_ITEM_USE;
	if( byLocation == ITEM_PLACE_EVENT ) // 이벤트용 쿠폰 등록할 경우
	{
		info->byPlace = ITEM_PLACE_EVENT;
		info->byIndex = EVENT_COUPON;
		// 쿠폰 번호
		HTchar strNumber[5], strNumber2[5];

		strncpy( strNumber, pStr, 4 ); // 앞의 4자리 : 0~3
		strNumber[4] = '\0';

		strncpy( strNumber2, &(pStr[4]), 4 ); // 뒤의 4자리 : 4~7
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

		// 지바푸스티카이면 여기서 아이템 사용 메시지를 보내지 않고... 다름 입력을 받아서 보내준다.
		if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVE_JIVAPUSTICA )
		{
			//	this item, Because Portal Algorism
			g_cPortal->HT_vPortal_SetDataForMsgItem( info->byPlace, info->byIndex, HT_ITEM_MOVE_JIVAPUSTICA );
			//	Show MovePotal Dlg
			g_cUIManager->HT_ShowWindow( _DIALOG_JIVAPUSTICAWND );
			HT_DELETE( info );
			return;
		}
		//	향상된 이동의 지바 푸스티카를 사용했으면 전용 포탈창을 열어준다.
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
		//	부활 주문서를 이용했을때
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
		//	요새 이동의 푸스티카인경우 아이템 포탈 이동을 요청한다.
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_FORTRESSPUSTICA )
		{
			g_cPortal->HT_vPortal_SetPortressPustica( info->byPlace, info->byIndex );
			HT_DELETE( info );
			return;
		}
		//	공성 이동의 푸스티카인경우 아이템 포탈 이동을 요청한다.
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_SIEGEPUSTICA )
		{
			g_cPortal->HT_vPortal_SetSiegePustica( info->byPlace, info->byIndex );
			HT_DELETE( info );
			return;
		}
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_OPEN_MESSAGE ||			//	정광판 아이템 (호외)
			     g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_COMBAT_MESSAGE )		//	정광판 아이템 (전투명령서)
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
					//	주신전 지역 아니면 보낼수 없다는 메시지 추가
				}
			}
			HT_DELETE( info );
			return;
		}
		//	주신 변경 아이템 아이템의 경우 자신의 주신과 같을겨우에는 처리하지 않는다. 시바
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_CHANGEGODCHARM1 )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
			{
				HT_DELETE( info );
				return;
			}
		}
		//	주신 변경 아이템 아이템의 경우 자신의 주신과 같을겨우에는 처리하지 않는다. 브라흐마
		else if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_CHANGEGODCHARM2 )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
			{
				HT_DELETE( info );
				return;
			}
		}
		//	주신 변경 아이템 아이템의 경우 자신의 주신과 같을겨우에는 처리하지 않는다. 비슈느
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

	// 아이템 사용한건지 파악
    m_bPotionItemUse_Sw = HT_TRUE;
	// 아이템 사용 후 딜레이 타임
	m_dwItemUse_DelayTime = timeGetTime();

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Item_Use : %d(%d:%d)", m_dwUseItemKeyID, info->byPlace, info->byIndex );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );

	//	아이템 사용한 이펙트 틀어주기
	//	이동의 푸스티카
	if( g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVE_PUSTICA ||
		g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwUseItemKeyID ) == HT_ITEM_MOVEPOSPUSTICA )
	{
		HTint iTempFXID;
		g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
		//	캐릭터 이동못하게 셋팅
		g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

		// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
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
	// 현재 시간 구하기
	time_t now, timeTime; time( &now );

	g_cMainCharacter->HT_bMainChar_GetTimeStamp( iIndex, timeTime );

	if (timeTime <  now)	// 사용안하거나 만료되었다면 현재 +30일 증가
		timeTime = now + (3600 * 24) * iAddDay;
	else				// 그렇지 않다면 남은 기간에서 +30일 추가
		timeTime += (3600 * 24) * iAddDay;

	g_cMainCharacter->HT_vMainChar_SetTimeStamp( iIndex, timeTime );

	return HT_TRUE;
}

//----------네트워크_아이템 사용 결과----------//
HTvoid HTItemControl::HT_vNetWork_SCP_RESP_Item_Use_Result( MSG_ITEM* info )
{
	//-----아이템 사용한건지 파악-----//
    m_bPotionItemUse_Sw = HT_FALSE;
 
	if( info->byPlace == ITEM_PLACE_EVENT ) // 이벤트 쿠폰 등록 결과일 경우
	{
		g_cNPCControl->HT_vNetWork_RegistLottery( info->byResult, 0 );
	}
	else // 일반 아이템 사용 결과일 경우
	{
		// 아이템 KeyID 알아내기
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID );
		
		// 아이템 사용하는 소리가 난다.
		g_pEngineHandler->HT_hrPlaySound( 33010, 1 );

		// 퀵슬롯 아이템 검색을 위해서 아이템 삭제 전에 인덱스를 구한다
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(iKeyID); 

        if( info->byResult == 0)
		{
			// 기간제 아이템들은 사용 즉시 클라이언트에서 시간을 셋팅해서 처리한다. (서버로 시간정보를 다시 받지 않는다) 2004. 11. 22 선영범
			if (dwItemIndex >= 6951 && dwItemIndex <= 6956 || dwItemIndex >= 7064 && dwItemIndex <= 7067 || dwItemIndex == 7074 || dwItemIndex == 6736) 
			{
				/*
				6951	페타	한달 동안 인벤토리를 확장시켜줍니다
				6952	개인상점확장	한달 동안 개인상점크기를 확장합니다
				6953	루피아 자동 습득	루피아를 자동 습득 합니다
				6954	한달 아누바바	한달동안 물리,마법공격력20%%~30%%상승(퀵슬롯전용)
				6955	한달 아트만	한달동안 HP가 27%% + 270 증가 합니다(퀵슬롯전용)
				6956	한달 모든 차크라 상승	한달 동안 모든 차크라가 15 상승합니다

				7064	아누바바 꾸러미
				-	인벤토리 확장 한달 지속	-	개인상점 확장 한달 지속	-	자동 돈 줍기 한달 지속	-	아누바바 효과 한달 지속

				7065	아트만 꾸러미
				-	인벤토리 확장 한달 지속	-	개인상점 확장 한달 지속	-	자동 돈 줍기 한달 지속	-	아트만 효과 한달 지속

				7066	골드 꾸러미
				-	인벤토리 확장 한달 지속	-	개인상점 확장 한달 지속	-	자동 돈 줍기 한달 지속	-	아누바바의 효과 한달 지속
				-	아트만 효과 한달 지속

				7067	플래티넘 꾸러미
				-	인벤토리 확장 한달 지속	-	개인상점 확장 한달 지속	-	자동 돈 줍기 한달 지속	-	아누바바의 효과 한달 지속
				-	아트만 효과 한달 지속	-	All 차크라 15 증가 효과 한달 지속

				7074 플래티넘 꾸러미 7일권
				*/

				switch (dwItemIndex)
				{
					case 6951:	// 페타
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정

						HT_vItemControl_SetMessage( eMsgPremiumItemEffect1 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6952:	// 개인상점확장
						HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect2 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6953:	// 루피아 자동 습득
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect3 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6954:	// 한달 아누바바
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect4 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6955:	// 한달 아트만
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect5 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6956:	// 한달 모든 차크라 상승
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect6 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7064:	// 한달 아누바바
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						}
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect7 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7065:	// 아트만 꾸러미
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
							HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						}
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect8 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7066:	// 골드 꾸러미
						if (g_iInationalType == INATIONALTYPE_JAPEN)
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
							HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						}
						else
						{
							HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
							g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
							HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
							HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
							HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						
							HT_vItemControl_SetMessage( eMsgPremiumItemEffect9 );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						}
						break;
					case 7067:	// 플래티넘 꾸러미
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
						HT_iItemControl_SetPrimiumItem(eTime_Store, 30);
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 30);
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 30);
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 30);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect10 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 7074:	// 플래티넘 꾸러미 (7일권)
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 7);
						g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
						HT_iItemControl_SetPrimiumItem(eTime_Store, 7);
						HT_iItemControl_SetPrimiumItem(eTime_AMoneyRoot, 7);
						HT_iItemControl_SetPrimiumItem(eTime_Anubaba, 7);
						HT_iItemControl_SetPrimiumItem(eTime_Atman, 7);
						HT_iItemControl_SetPrimiumItem(eTime_15Chakra, 7);
						HT_vItemControl_SetMessage( eMsgPremiumItemEffect10 );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
						break;
					case 6736:	// 이벤트 플래티넘 꾸러미 (30일권)
						HT_iItemControl_SetPrimiumItem(eTime_Inven, 30);
						g_cEquipInventory->HT_vInitBagStatus();	// 인벤토리 크기 초기 설정
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

//			if (dwItemIndex == 7073)	// 이벤트 아이템 적립했음을 알림.
//			{
//				HT_vItemControl_SetMessage( eMsgEventItemUseOK );
//				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, m_szMessage);
//			}
		}

		
		if( info->kItem.byCount == 0 )
		{
			// 퀵슬롯에 등록된 아이템일 경우 퀵슬롯 정보 지우기
			//g_cQuickSlot->HT_vQuickSlot_DeleteItem( iKeyID );
			// 아이템 삭제
			g_cItemSystem->HT_vItemSystem_DeleteItem( iKeyID );
		}
		else
		{
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iKeyID, info->kItem.byCount );
		}
		// 퀵슬롯에 등록되어있는 아이템일 경우
		if( g_cQuickSlot->HT_bBeUsedKeyID( dwItemIndex, iKeyID ) )
			g_cQuickSlot->HT_vResultActionItem( iKeyID );

		// 아이템 사용에 따른 상태변경은 서버에서 내려준다

		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("ReceiveSend_Item_Use:ClientSide:%d(ServerSide:%d-%d)", 
																		m_dwUseItemKeyID, iKeyID, info->kItem.byCount);
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
}

// 인벤토리 크기 확장
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
		if( (_INVEN_WIDTH - iCurSize) <= iBagSize )	// 확장될 크기가 비활성된 bag크기보다 클 경우
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

// 화살 자동 채우기 - 찾은 아이템의 KeyID 반환
HTbool HTItemControl::HT_bItemControl_RefillArrow( HTdword dwKeyID, HTdword dwItemIndex )
{
	// 다른 아이템을 이동하고 있지 않을 때만 실행
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_NONE )
	{
		if( dwItemIndex > 0 )
		{
			// 같은 종류(인덱스가 같은)의 아이템을 인벤토리에서 찾아서 다시 채운다.
			HTdword dwFindKeyID = 0;		// 찾은 아이템의 KEyID
			HT_ITEMSETTING_FLAG sLocRoom;	// 찾은 아이템의 위치
			g_cItemSystem->HT_vItemSystem_GetItemPos( dwItemIndex, dwKeyID, ITEM_LOCATION_PC, dwFindKeyID, sLocRoom);
			if( dwFindKeyID > 0 ) // 아이템을 찾았을 경우
			{
				// 아이템 원래 위치 설정
				m_sSource_Item.nLocation = ITEM_LOCATION_PC;
				m_sSource_Item.nInventory = sLocRoom.nInventory;
				m_sSource_Item.pCellPos = sLocRoom.pCellPos;
				// 아이템을 이동할 위치 설정
				m_sTarget_Item.nLocation = ITEM_LOCATION_EQUIP;
				m_sTarget_Item.nInventory = ITEM_LOCATION_EQUIP_LEFT_HAND;
				m_sTarget_Item.pCellPos.x = m_sTarget_Item.pCellPos.y = 0;
				// 마우스로 직접 이동한 아이템이 아니기때문에
				// 인벤토리에서 다른 화살을 찾았을 경우 원본 이미지를 직접 지워준다.
				// 아이템 이동 요청
				HT_vItemControl_Network_ReqMove();
				return HT_TRUE;
			}
		}
	}

	return HT_FALSE;
}

//----------서버에 이동 요청----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove()
{	
	PS_CSP_REQ_ITEM_MOVE info = HT_NULL;
	info = new S_CSP_REQ_ITEM_MOVE;

	// 아이템이 있던 원래 위치
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
	// 아이템을 이동할 위치
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
	 
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemMove : From(%d:%d), To(%d:%d)", 
	//									info->byFromPlace, info->snFromIndex, info->byToPlace, info->snToIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
//----------서버에 이동 요청_결과----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove_Result( PS_SCP_RESP_ITEM_MOVE info )
{
	// 아이템 놓일 위치 설정
//	m_dwActiveItemKeyID = info->dwKeyID;
	if( HT_bItemControl_ReqMoveResult_SetItemPos(info) == HT_FALSE )
		return;

	// 이동 정지
	HT_vItemControl_ItemAntiActive();

	if( info->nResult == 0x00 )
	{
		// 아이템이 이동되거나 장착할때의 소리를 튼다.
		DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
		if( dwItemIndex > 0 )
		{
			HTdword dwSoundID = g_pEngineHandler->HT_dwGetItemEquipSoundID( dwItemIndex );
			if ( dwSoundID > 0 )
				g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );

			// 아이템 놓일 위치 설정
			m_dwActiveItemIndex = dwItemIndex;

			//----------서버에 이동 요청한후 취해야할 액션들----------//
			HT_vItemControl_Network_ReqMove_Result_Check();
		}
	}
	else
	{
		//-----이동할 수 없을 때-----//
		HT_vItemControl_SettingItem( HT_FALSE );

		switch(info->nResult)
		{
			case REPLY_ITEM_MOVE_LAY_DISABLE : // 아이템 중첩 불가
				HT_vItemControl_SetMessage( eMsgItemPackNotPack );
				break;
			case REPLY_ITEM_MOVE_INVENTORY_LACK : // 인벤토리 공간 부족	
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case REPLY_ITEM_MOVE_DISTANCE_ERR: // 이동 거리 오류
				HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
				break;
			case REPLY_ITEM_MOVE_PLACE_ERR: // 이동 위치 오류
				HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
				break;
			case REPLY_ITEM_MOVE_OWNER_ERR: // 아이템 소유자 오류
				HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
				break;
			case REPLY_ITEM_MOVE_ROUTING_TIME: // 아이템 루팅 시간 오류
				HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
				break;
			case REPLY_ITEM_MOVE_BAG:		// 확장인벤토리에 아이템 있음
				HT_vItemControl_SetMessage( eMsgItemEquipDecExistItem );
				break;
			case REPLY_ITEM_MOVE_NOMOVE: // 이동할 수 없는 아이템
				HT_vItemControl_SetMessage( eMsgItemMoveCannot );
				break;
			case REPLY_ITEM_MOVE_TWOHAND :	// 양손무기 착용 오류
				HT_vItemControl_SetMessage( eMsgItemMoveTwoHandErr );
				break;
			default :						// 아이템 이동 실패
				HT_vItemControl_SetMessage( eMsgItemMoveFail );
				break;
		}
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

// 서버에 이동 요청 결과로 내려온 아이템의 결과 위치 설정
HTbool HTItemControl::HT_bItemControl_ReqMoveResult_SetItemPos( PS_SCP_RESP_ITEM_MOVE info )
{
	// 아이템 KeyID 알아내기
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byFromPlace, info->snFromIndex, iKeyID );

	// 아이템 이동 정지 - 아이템을 이동하던 중 다른 아이템의 결과를 처리해야할 경우 대비
	if( m_nItemControl_Status == ITEMCONTROL_STATUS_MOVE && m_dwActiveItemKeyID != iKeyID )
		HT_vItemControl_ItemAntiActive();
	m_dwActiveItemKeyID = iKeyID;
	
	// 아이템의 원래 위치 설정
	g_cItemSystem->HT_bItemSystem_GetItemPos(iKeyID, m_sSource_Item );

	// 아이템의 이동할 위치 설정
	// 이동이 성공했을 경우에만 target위치가 의미있기 때문에
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

// 장착했던 아이템을 벗었을 경우의 처리
HTvoid HTItemControl::HT_vItemControl_ItemMove_UnEquip( HTint iInventory )
{
	// KeyID 생성
	HTint iActiveItemKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, (HTbyte)iInventory, iActiveItemKeyID);
	// 아이템 위치 가져오기
	HT_ITEMSETTING_FLAG sLocRoom;
	g_cItemSystem->HT_bItemSystem_GetItemPos( iActiveItemKeyID, sLocRoom );
	
	if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		HTdword dwActiveItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( iActiveItemKeyID );

		//-------장착한 아이템과 관련된 Bar 지우기--------//
		// 착용 불가능하게 된 아이템을 착용하고 있었을 경우 불가능바 지우기
		if( g_cItemSystem->HT_bItemSystem_GetPossible( iActiveItemKeyID, HT_TRUE ) == HT_FALSE )
		{
			HTint nCellNum = g_cItemSystem->HT_iItemSystem_GetCellNumber(iActiveItemKeyID);
		}

		if( sLocRoom.nInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )	// 오른손 
		{
			// 제련된 아이템의 FX 없애기
			// 메인 제련
			if( g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( iActiveItemKeyID ) > 0 )
				g_pEngineHandler->HT_hrDetachItemMainRefineEffect(g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex );
			// 속성 제련
			if( g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( iActiveItemKeyID ) > 0 )
				g_pEngineHandler->HT_hrDetachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex );

			if ( HT_IS_ITEM_WEAPON( dwActiveItemIndex ) )
			{
				g_cEquipInventory->HT_vEquipInventory_SetRightItem( 0 );
				g_cEquipInventory->HT_vEquipInventory_SetRightItem_KeyID( 0 );
				g_cMainCharacter->HT_vMainChar_SetArmsType( 0 );
			}

			// 양손 아이템일 경우 왼쪽 이미지 지우기
			if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwActiveItemIndex )
							|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwActiveItemIndex ) )
			{
				// 왼손에 아이템을 장착하지 않았을 경우 왼손 비트맵 지우기
				if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) == 0 )
				{
					// 이미지 지우기
					g_cUIManager->HT_SetSlotImage( _DIALOG_EQUPINVENTORY, _INVEN_DEFENCE_WEAPON, 0 );
					// 투명 바 지우기
				}
			}
		}
		// 왼손 아이템을 내린 경우 
		else if( sLocRoom.nInventory ==  ITEM_LOCATION_EQUIP_LEFT_HAND )
		{
			g_cEquipInventory->HT_vEquipInventory_SetLeftItem( 0 );

			DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
			if( dwKeyID > 0 )
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
				// 오른손 아이템이 양손용이면 왼쪽에 비트맵 그리기
				if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwIndex )	|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwIndex ) )
				{
					// 이미지 그리기
					// 투명바 그리기
				}
			}
		}
		else if( sLocRoom.nInventory == ITEM_LOCATION_EQUIP_HEAD )
		{
			if( dwActiveItemIndex == ITEMINDEX_ASSISTANTHAT )		//	조교모자를 썼는지 안썼는지
				m_bAssistant = HT_FALSE;
		}
		// 확장된 인벤토리 해제일 경우
		else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwActiveItemIndex ) )
		{
			// 시스템 창에 표시
			// 확장된 인벤토리를 해제했습니다.
			HT_vItemControl_SetMessage( eMsgItemEquipInvenDecOK );

			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );

			// Bag1은 기본으로 모두 사용한다
			if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) > 0 ) // Bag2가 확장되어 있었다면
			{
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, 0);
			}

			if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG3) > 0 ) // Bag3가 확장되어 있었다면
			{
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG3, 0);
			}
			// 기본 인벤(Bag1) 선택
		}

        //------- 캐릭터 외관 바꾸기(아이템 벗기) --------//
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

		//	토템 아이템의 경우 서정거리 적용하기
		if( dwActiveItemIndex == HT_INDEX_TOTEM_JACUNAEARANI )
			g_cMainCharacter->HT_vMainChar_SetTotemItemRange( 0 );

		// 현재 내구도에 따른 내구도 표시 (20030520, DAEHO)
		//this->HT_vDelDurability( dwActiveItemIndex );
	}	// end of if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
}

// 장착했을 경우의 처리
HTvoid HTItemControl::HT_vItemControl_ItemMove_Equip( HTdword dwActiveItemKeyID, HTint iTargetInventory )
{
	// 아이템 위치 가져오기
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
	
	if( iTargetInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )	// 오른손/양손
	{
		// 메인 제련이 되어 있는 (무기) 아이템의 FX 설정
		HTbyte byMainRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( dwActiveItemKeyID );
		if( byMainRefineLevel > 0 )
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																dwActiveItemIndex, byMainRefineLevel );
		
		// 속성 제련 되어 있는 (무기) 아이템의 경우
		HTint iSubRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( dwActiveItemKeyID );
		if( iSubRefineLevel > 0 )
		{
			HTint iAttribute = g_cItemSystem->HT_iItemSystem_GetAttributeSubRefineItem( dwActiveItemKeyID );
			// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
			g_pEngineHandler->HT_hrAttachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), dwActiveItemIndex,
																(HTESubRefineType)iAttribute, iSubRefineLevel );
		}
		//	공격 무기일때만 공격 무기로 셋팅한다.
		if ( HT_IS_ITEM_WEAPON( dwActiveItemIndex ) )
		{
			g_cMainCharacter->HT_vMainChar_SetArmsType( dwActiveItemIndex );
			g_cEquipInventory->HT_vEquipInventory_SetRightItem( dwActiveItemIndex );
			g_cEquipInventory->HT_vEquipInventory_SetRightItem_KeyID( dwActiveItemKeyID );
		}
	} 
	else if( iTargetInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )	// 왼손
	{
		if( HT_IS_ITEM_SHIELD( dwActiveItemIndex ) )
            g_cEquipInventory->HT_vEquipInventory_SetLeftItem( dwActiveItemIndex );

		DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
		if( dwKeyID > 0 )
		{
			DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
			// 오른손 아이템이 양손용이면 왼쪽에 투명바 지우기
		}
	}
	else if( iTargetInventory == ITEM_LOCATION_EQUIP_HEAD )
	{
		if( dwActiveItemIndex == ITEMINDEX_ASSISTANTHAT )		//	조교모자를 썼는지 안썼는지
			m_bAssistant = HT_TRUE;
	}
	// 인벤토리 확장의 경우
	else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( dwActiveItemIndex ) )	
	{
		HTint iBagSize = 0; 
		if( g_pParamMgr->HT_bGetItemEffect1Param1( dwActiveItemIndex, &iBagSize ) == false || iBagSize <= 0 )
			return;

		// Bag1 확장
		if( g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG1) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG1 );
		}
		// Bag2 확장
		if( iBagSize > 0 && g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG2 );
		}
		// Bag3 확장
		if( iBagSize > 0 && g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG3) < _INVEN_WIDTH )
		{
			HT_vItemControl_ExpandInventorySize( iBagSize, ITEM_LOCATION_PC_BAG3 );
		}

		// 시스템 창에 표시
		// 인벤토리가 확장됐습니다.
		HT_vItemControl_SetMessage( eMsgItemEquipInvenIncOK );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	/*
	else
	{//fors_debug 멥죄였였,페儉뒈렘돨랙밟
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																4001, 15 );
		
	}*/

	// 현재 내구도에 따른 수리 표시(20030520,DAEHO)
	//this->HT_vReformDurability( dwActiveItemKeyID );

	//	튜토리얼 시스템을 위함
	if (g_cTutorialSystem)
	{
		if (7==g_cTutorialSystem->HT_iGetTutorialStep())
			g_cTutorialSystem->HT_vAddTutorialStep( TUTORIAL_STEP_GETITEM );
	}

	//	토템 아이템의 경우 서정거리 적용하기
	if( dwActiveItemIndex == HT_INDEX_TOTEM_JACUNAEARANI )
	{
		int iRange = 0;
		g_pParamMgr->HT_bGetItemEffect1Param1( dwActiveItemIndex, &iRange );
		g_cMainCharacter->HT_vMainChar_SetTotemItemRange( iRange );
	}
}

//----------서버에 이동 요청한후 취해야할 액션들----------//
HTvoid HTItemControl::HT_vItemControl_Network_ReqMove_Result_Check()
{ 
	//---------아이템 장착 관련: 아이템 위치를 바꾸기 전에 처리해야 한다. --------//
	// 장착했던 아이템을 벗었을 경우의 처리
	if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )
		HT_vItemControl_ItemMove_UnEquip( m_sSource_Item.nInventory );

	// 장착했을 경우의 처리
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )
		HT_vItemControl_ItemMove_Equip( m_dwActiveItemKeyID, m_sTarget_Item.nInventory );

	//	Set Item
	this->HT_vItemControl_SettingItem( HT_TRUE );

	// 현재 내구도에 따른 수리 표시 갱신 : 아이템 위치를 바꾼 후에 처리해야 한다.
	if( m_sSource_Item.nLocation == ITEM_LOCATION_EQUIP )	// 탈착
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );
	if( m_sTarget_Item.nLocation == ITEM_LOCATION_EQUIP )	// 장착
	{
		g_cItemSystem->HT_vItemSystem_SetDurabilityWarning( m_sTarget_Item.nInventory );
		//	왼손에 장착된 아이템일경우 무기에 맞는 애니매이션 셋팅
		if( m_sTarget_Item.nInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )
			g_cMainCharacter->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	
	// 소모성 아이템(화살 제외)의 경우 퀵슬롯창에 등록되어있으면 등록된 KeyID를 바꿔줘야한다.
	if( (CHTParamIDCheck::HT_bIsItemUsable( m_dwActiveItemIndex ) && !CHTParamIDCheck::HT_bIsItemUsableArrow( m_dwActiveItemIndex )) ||
		CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwActiveItemIndex ) )
	{
		// 퀵슬롯 창에 등록되어있는 아이템이 PC인벤토리 이외의 장소로 이동됐을 경우 지우기
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

// 맵에 버리기
HTvoid HTItemControl::HT_vItemControl_Network_ReqDrop( )
{
	PS_CSP_REQ_ITEM_DROP info = NULL;
	info = new S_CSP_REQ_ITEM_DROP;

	info->dwMoney = 0;
	// 아이템이 있던 원래 위치
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

	// 아이템을 이동할 위치
	info->snX = m_sTarget_Item.pCellPos.x;
	info->snZ = m_sTarget_Item.pCellPos.y;

	g_pNetWorkMgr->RequestItemDrop( info );
	 
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemDrop : From(%d:%d), To(%d:%d)", 
	//														info->byFromPlace, info->byIndex, info->snX, info->snZ );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );

	//	왜 넣는지는 나도 모름
	m_byResent = RESENT_STEP_ITEM_MOVE;
}

HTvoid HTItemControl::HT_vItemControl_Network_ReqDrop_Result( PS_SCP_RESP_ITEM_DROP info )
{
	if( info->byType == DROP_TYPE_MONEY ) // 맵에 루피아 버리기
	{
		if( info->snResult == 0x00 )
		{
			HTdword dwMoney = 0;
			if( info->dwMoney < 0 )
				dwMoney = 0;
			else
				dwMoney = info->dwMoney;
			
			if( info->byPlace == ITEM_PLACE_INVEN )	// PC 인벤의 돈 버리기
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( dwMoney );
			else									// NPC 인벤의 돈 버리기
				g_cEquipInventory->HT_vEquipInventory_SetNPCMoney( dwMoney );
		}
	}
	else
	{
		// KeyID 생성
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
		m_dwActiveItemKeyID = iKeyID;

		// 이동 정지
		//HT_vItemControl_ItemAntiActive();

		if( info->snResult == 0x00 )
		{
			// 아이템이 이동되거나 장착할때의 소리를 튼다.
			DWORD dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwActiveItemKeyID );
			if( dwItemIndex > 0 )
			{
				HTdword dwSoundID = g_pEngineHandler->HT_dwGetItemEquipSoundID( dwItemIndex );
				g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );
				
				m_dwActiveItemIndex = dwItemIndex;
			}
			else
				return;

			/* 왼손에 장착된 아이템을 벗었을 경우 오른손에 양손아이템을 장착하고 있다면 
				이미지를 그려줘야 하기 때문에 아이템을 먼저 지우고 뒤처리를 하도록 했음. 2003.12.11. 선미 */
			// 장착했던 아이템을 벗었을 경우의 처리:아이템 처리를 하기 전에 처리해야 한다.
			if( info->byPlace == ITEM_PLACE_EQUIP )
				HT_vItemControl_ItemMove_UnEquip( info->byIndex );

			// 아이템 지우기
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwActiveItemKeyID );
		
			// 현재 내구도에 따른 수리 표시:아이템이 처리 된 후에 해야한다.
			g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning();
			
			// 소모성 아이템일 경우 퀵슬롯 창에 등록되어있는지 검사해서 지우기
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
					// 인벤토리 공간 부족 
					HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
					break;
				case REPLY_ITEM_MOVE_DISTANCE_ERR:	
					// 이동 거리 오류 
					HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
					break;
				case REPLY_ITEM_MOVE_PLACE_ERR:
					// 이동 위치 오류 
					HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
					break;
				case REPLY_ITEM_MOVE_OWNER_ERR:
					// 아이템 소유자 오류 
					HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
					break;
				case REPLY_ITEM_MOVE_ROUTING_TIME:
					// 아이템 루팅 시간 오류 
					HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
					break;
				default :
					// 아이템 버리기 실패 
					HT_vItemControl_SetMessage( eMsgItemMoveFail );
					break;
			}
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
		}
	}
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

// 맵에서 줍기
HTvoid HTItemControl::HT_vItemControl_Network_ReqGet()
{
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return;

	PS_CSP_REQ_ITEM_GET info = NULL;
	info = new S_CSP_REQ_ITEM_GET;

	info->nItemID = m_dwGetItemKeyID;
	g_pNetWorkMgr->RequestItemGet( info );
	 
	//-----디버깅 테스트를 위하여-----//
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
		if( CHTParamIDCheck::HT_bIsItemUsableMoney( dwItemKeyID ) && info->dwMoney > 0 )	// 맵에서 루피아 줍기
		{
			m_iMoneyForMessage = info->dwMoney - g_cEquipInventory->HT_iEquipInventory_GetPCMoney() ;

			if( m_iMoneyForMessage > 0 ) 
			{
				// 파티가 생성되어있고 자동분배 모드일 경우
				if( g_cParty->HT_iParty_GetPartyMemberCount() > 0 && g_cParty->HT_bParty_GetRootingMode() )
					HT_vItemControl_SetMessage( eMsgRupiahMoveAutoReceive ); // [자동분배]%s루피아 획득
				else
					HT_vItemControl_SetMessage( eMsgRupiahReceive ); // %s 루피아를 획득했습니다.
			}
			else
				m_szMessage.HT_hrCleanUp();

			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );	// 루피아 갱신
		}
		else
		{
			// %s를(을) 획득했습니다.
			if( g_pParamMgr->HT_bGetItemName( dwItemKeyID, &m_szObjectName ) == true )
				HT_vItemControl_SetMessage( eMsgItemMoveReceive );
			else
				m_szMessage.HT_hrCleanUp();
		}
		if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );

		// 자동 패킹했을 경우 또는 맵에서 주운 아이템에 추가 정보가 있을 경우를 위해 새로 정보를 받아야 하는데
		// 서버에서 자동으로 아이템 관련 정보를 내려보내기 때문에 요청할 필요 없음. 2003.05.15
		
		//----------맵위의 픽업된 아이템 초기화----------//
		g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
	}
	else
	{
		switch(info->nResult)
		{
			case REPLY_ITEM_MOVE_INVENTORY_LACK :	
				// 인벤토리 공간 부족 
				HT_vItemControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case REPLY_ITEM_MOVE_DISTANCE_ERR:	
				// 이동 거리 오류 
				HT_vItemControl_SetMessage( eMsgItemMoveDistanceErr );
				break;
			case REPLY_ITEM_MOVE_PLACE_ERR:
				// 이동 위치 오류 
				HT_vItemControl_SetMessage( eMsgItemCommonPositionErr );
				break;
			case REPLY_ITEM_MOVE_OWNER_ERR:
				// 아이템 소유자 오류 
				HT_vItemControl_SetMessage( eMsgItemCommonOwnerErr );
				break;
			case REPLY_ITEM_MOVE_ROUTING_TIME:
				// 아이템 루팅 시간 오류 
				HT_vItemControl_SetMessage( eMsgItemMoveRoutingTime );
				break;
			case REPLY_ITEM_MOVE_PART :	// (중첩된)아이템 일부만 줍기
				// %s를(을) 획득했습니다.
				HT_vItemControl_SetMessage( eMsgItemMoveReceive );
				break;
			default :
				// 아이템 줍기 실패 
				HT_vItemControl_SetMessage( eMsgItemMoveFail );
				break;
		}
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
	}
	//m_byResent = RESENT_STEP_NONE;
	//m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;
}

//----------서버에 아이템 패킹을 요청----------//
HTvoid HTItemControl::HT_vItemControl_Network_Req_ItemPacking( HTbyte byType )
{
	MSG_Packing* info = HT_NULL;
	info = new MSG_Packing;

	info->byType = byType;

	// 아이템이 있던 원래 위치
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

	// 아이템을 이동할 위치
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

	if( byType == ITEMPACKING_TYPE_PACKING )	// 아이템 중첩일 경우
	{
		info->byFromCount = (HTbyte)g_cItemSystem->HT_iItemSystem_GetItemCount( m_dwActiveItemKeyID );
		info->byToCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_nDestItemKeyID );
	}
	else// 	ITEMPACKING_TYPE_UNPACKING - 아이템 분리일 경우
	{
		info->byFromCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_dwActiveItemKeyID );
		info->byToCount = m_nUnPackCount;
	}

	g_pNetWorkMgr->RequestItemPacking( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemPacking: %d - Des(%d,%d:%d)Sou(%d,%d:%d)", info->byType,
	//	info->byFromPlace, info->byFromIndex, info->byFromCount, info->byToPlace, info->byToIndex, info->byToCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
   
//----------서버에 아이템 패킹을 요청_결과----------//
HTvoid HTItemControl::HT_vItemControl_Network_Resp_ItemPacking( MSG_Packing* info )
{
	HTint iFromKeyID = 0;	// 이동하려던 아이템
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byFromPlace, info->byFromIndex, iFromKeyID );
	m_dwActiveItemKeyID = iFromKeyID;

	HTint iToKeyID = 0;	// 이동할 위치에 있던 아이템
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byToPlace, info->byToIndex, iToKeyID );

	// 이동 정지
	HT_vItemControl_ItemAntiActive();

	if( info->byType == ITEMPACKING_TYPE_PACKING )	// 아이템 중첩 결과
	{
		// 다른 아이템 위로 이동한 아이템 
		if( info->byFromCount == 0 )
		{
			g_cItemSystem->HT_vItemSystem_DeleteItem( iFromKeyID );

			// 퀵슬롯창에 등록된 아이템을 다른 아이템과 합쳤을 경우
			g_cQuickSlot->HT_bChangeIconByKeyID( iFromKeyID, iToKeyID );
		}
		else
		{
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iFromKeyID, info->byFromCount );

			// 아이템의 원래 위치 찾기
			g_cItemSystem->HT_bItemSystem_GetItemPos( iFromKeyID, m_sSource_Item );
			HT_vItemControl_SettingItem( HT_FALSE );
		}

		// target 아이템의 개수 셋팅
		g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iToKeyID, info->byToCount );
	}
	else	// 아이템 분리 결과
	{
		if( info->byResult == 0 )	// 성공
		{
			// source
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( m_dwActiveItemKeyID, info->byFromCount - info->byToCount );

			STRUCT_ITEM sItem; // 원본 아이템 정보
			g_cItemSystem->HT_bItemSystem_GetItemInfo( m_dwActiveItemKeyID, sItem );
			// 새 아이템 생성
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
			// 주술제련 정보
			for( HTint i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i )
				item->sitem.bySubRefine[i] = sItem.bySubRefine[i];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );	
			HT_DELETE( item );
		}
		// 실패했을 경우 처리할 단계 없음.
	}

	// 서버 요청 단계
	m_byResent = RESENT_STEP_NONE;
	m_dwActiveItemKeyID	= RETURNTYPE_MAINGAME_FAILD;

//	if (g_cObjectInfo)
//		g_cObjectInfo->HT_vObjectInfo_InfoCheck( this->m_nIndex, (*ZOder)->m_nIndex );	// 슬롯박스 정보 출력
}