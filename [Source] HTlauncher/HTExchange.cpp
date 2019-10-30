#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htexchange.h"

#define EXCHANGE_PROCESS_NONE					0
#define EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM	1
#define EXCHANGE_PROCESS_REQUESTTRADE			2
#define EXCHANGE_PROCESS_RECEIVETRADE			3
#define EXCHANGE_PROCESS_TRADING				4
#define EXCHANGE_PROCESS_PRESS_OK				5 // �� Ȯ�� ��ư ���� ����
#define EXCHANGE_PROCESS_TRADECANCEL			6 // �ŷ���û ����

#define EXCHANGE_OK								1
#define EXCHANGE_CANCEL							0

#define EXCHANGE_MESSAGE_COMPLETE				0x01	
#define EXCHANGE_MESSAGE_CONFIRM				0x00

#define EXCHANGE_SLOGCURRECT_OTHER				10
#define EXCHANGE_SLOGCURRECT_MINE				20

HTExchange::HTExchange(void)
{
}

HTExchange::~HTExchange(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_TRADEWND );
}

HTvoid HTExchange::HT_vExchange_CleanUp()
{
}

HTRESULT HTExchange::HT_hrExchange_Init()
{
	//	Create Window
	this->HT_vExchange_CreateWindow();

	m_bClickTradeButtonSw = HT_FALSE;
	m_bExchangeWin_Active = HT_FALSE;
	//---------��ȯ ���μ���----------//
	m_byExchange_Squence = EXCHANGE_PROCESS_NONE;

	//---------���� ��ȯ Ȯ�� ��ư�� ���ȴ°�?----------//
	m_bPress_OK_Button = HT_FALSE;

	//---------���� ��ȯ�� ��û�߳�? 0:����,1:������û,2:������ ��û----------//
	//m_byRequest_Index = EXCHANGE_PROCESS_NONE;
	m_dwExchangeCharKeyID = m_dwReceiveExchangeCharKeyID = 0;
	m_szExchangeCharName.HT_hrCleanUp();
	m_iExchangeRupiah = m_iMyExchangeRupiah = 0;
	m_iMyItem_Count = m_iOtherCharItem_Count = 0;
	// �� ��ȯâ�� �� ������ ��� �ʱ�ȭ
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		ZeroMemory( &m_sMyItem[i], sizeof( STRUCT_ITEM ) );
		m_byMyInvenPos[i] = -1;	// ��ġ�� 0���� �����ϱ� ������
	}
	// ����� ��ȯâ�� �� ������ ��� �ʱ�ȭ
	ZeroMemory( m_iOtherCharItemKeyID, sizeof( HTint )*MAX_TRADE );

	return HT_OK;
}

//	Create Window
HTvoid HTExchange::HT_vExchange_CreateWindow()
{
	CHTString strMessage;
	//	[Command]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TRADEWND, _T(""), 330, 231, g_cExchangeSystem->HT_vEchsnhge_InputCheckForExchange, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TRADEWND, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 0, 8, 3, 36, 1400, 326, 6 );
	//	Texture ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	��ȯ
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Edit facing each other
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 1, 9, 7, 56, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonEachOther, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 7, 56, 152, 19 );
	//	Edit the person in question
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 2, 9, 165, 56, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonMySelf, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 165, 56, 152, 19 );
	//	Button facing each other ���Ǿ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 3, 88, 8, 157, 89, 87 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 3, 10, 40, 157, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 161, 40, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 161, 73, 13 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 3 );
	//	Button the person in question ���Ǿ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 4, 88, 176, 157, 89, 87 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 4, 10, 208, 157, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	���Ǿ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 288, 161, 40, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 211, 161, 73, 13 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 4 );
	//	Button ��ȯ facing each other
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 5, 159, 8, 181, 1400, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	��ȯ
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 8, 181, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 5 );
	//	Button ��ȯ the person in question
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 6, 159, 175, 181, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	��ȯ
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 181, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 6 );
	//	Button ��ȯ the person in question
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 7, 159, 251, 181, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 251, 181, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 7 );
	//	loop facing each other Slot
	HTint i,j;
	for( i=0 ; i<2 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_OTHER+((i*4)+j), 66, 8+(j*36), 81+(i*37) );
			g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_OTHER+((i*4)+j), 2, 2);
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_OTHER+((i*4)+j), HT_TRUE );
		}
	}
	//	loop the person in question
	for( i=0 ; i<2 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_MINE+((i*4)+j), 66, 170+(j*36), 81+(i*37) );
			g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_MINE+((i*4)+j), 2, 2);
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_TRADEWND, EXCHANGE_SLOGCURRECT_MINE+((i*4)+j), HT_TRUE );
		}
	}
}

//	�Է� �޼��� ó��
//	Exchange Inventory
void HTExchange::HT_vEchsnhge_InputCheckForExchange(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X Button
		if( iTargetID == -1 )
		{
			// Ȯ�� ��ư�� ���� �ڿ��� ����� �� ����
			if( g_cExchangeSystem->m_bPress_OK_Button == HT_FALSE )
				g_pNetWorkMgr->RequestTradeCancel();
		}
		// ������ ��ȯ
		else if( iTargetID == 6 )
		{
			if( g_cExchangeSystem->m_bPress_OK_Button == HT_FALSE )
			{
				// Ȯ�ι�ư�� �����ִ� ����
				g_cUIManager->HT_SetButtonControlState(_DIALOG_TRADEWND, 6, 1);
				g_cExchangeSystem->m_bPress_OK_Button = HT_TRUE;
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_PRESS_OK;
				//---------������ ��ȯ�� �³�----------//
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
			}
		}
		//	���
		else if( iTargetID == 7 )
		{
			// Ȯ�� ��ư�� ���� �ڿ��� ����� �� ����
			if( g_cExchangeSystem->m_bPress_OK_Button == HT_FALSE )
			{
				g_cUIManager->HT_SetButtonControlState(_DIALOG_TRADEWND, 6, 0);
				g_pNetWorkMgr->RequestTradeCancel();
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		if( iTargetID == 2 )
		{
			if( g_cExchangeSystem->m_byExchange_Squence == EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM )
			{
				// NPC�� ��ȭ���̰ų� ���� ���� ����/���� �� ����̸� ó�� ����
				if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) 
						|| g_cUIManager->HT_isShowWindow(_DIALOG_TRADE)
						|| g_cUIManager->HT_isShowWindow( _DIALOG_PRIVATE_SHOP ) 
						|| g_cUIManager->HT_isShowWindow( _DIALOG_PRIVATE_SHOP_BUY ) )
				{
					g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
				}
				else
				{
					//	������ ��ȯ ��û�� ����
					g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
					g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE;
				}
			}
			else if( g_cExchangeSystem->m_byExchange_Squence == EXCHANGE_PROCESS_RECEIVETRADE )
			{ 
				// ������ ��ȯ ��û�� ���� ����� ������ �����Ѵ�
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				g_cExchangeSystem->HT_vExchange_ActiveSw( HT_TRUE );
			}
		}
		else if( iTargetID == 3 )
		{
			if( g_cExchangeSystem->m_byExchange_Squence == EXCHANGE_PROCESS_RECEIVETRADE )
			{
				// ������ ��ȯ ��û�� ���� ����� ������ ����
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	�ٸ� �����쿡�� ������ ������ ��ŵ
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );
		if( _DIALOG_TRADEWND != iWIndex )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
	}
}

HTvoid HTExchange::HT_vExchange_SetMessage( HTint idMessage, CHTString* pstrMessage )
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
		HT_vExchange_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vExchange_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vExchange_SetParamTextForMessage( sParam3, &szOut3 );

		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vExchange_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vExchange_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vExchange_SetParamTextForMessage( sParam1, &szOut1 );
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pstrMessage = szString;
}

HTvoid HTExchange::HT_vExchange_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// �ٸ� ĳ���� �̸�
		case eMsgParamOthercharName	:
			*pszParam = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_dwExchangeCharKeyID);
			break;

		default:
			break;
	}
}

//---------��ȯ/����----------//
//---------��ȯ ��û ��ư�� Ŭ���ߴ°�?----------//
HTvoid HTExchange::HT_vExchange_SetClickTradeButton( HTbool bType )
{
	if( m_bClickTradeButtonSw == HT_TRUE )
	{
		m_bClickTradeButtonSw = HT_FALSE;
		// �Ϲ� Ŀ���� ����
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}
	else
	{
		m_bClickTradeButtonSw = HT_TRUE;
		// Trade Ani Ŀ���� ����
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
	}
}

HTbool HTExchange::HT_vExchange_GetClickTradeButton()
{
	return m_bClickTradeButtonSw;
}

//---------��ȯ ��û�� ����----------//
HTRESULT HTExchange::HT_vExchange_RequestTrade( HTint nModelID )
{
	if( m_bClickTradeButtonSw == HT_FALSE )
		return HT_FAIL; 
	
	// NPC�� ��ȭ���̰ų� �ٸ� ����� trade ���̸� �����۱�ȯ ��û ���
	if(  m_bExchangeWin_Active == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
		return HT_OK;

	//	������ Ű�Ƶ� �˾ƿ��� 
	m_dwExchangeCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nModelID );
	m_szExchangeCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwExchangeCharKeyID );

	if (g_iInationalType == INATIONALTYPE_CHINA)
	{
		// ���� �߰� ���� (�߱��� �䱸 : 2004. 10. 21 ������) �Ϲ� �� ��� ��� ������ �ϹǷ� �α��뼭 ó��
		HTint OtherLevel = 0;
		OtherLevel = g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel(m_dwExchangeCharKeyID);
		m_szExchangeCharName.HT_szFormat("%s (Lv %d)", m_szExchangeCharName.HT_szGetString(), OtherLevel);
	}

	//	������ ��ȯ ��û�ϴ� ��ȭ���ڸ� �ٿ��
	m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM;

	// %s �Բ� ������ ��ȯ�� ��û�ұ��?, m_szExchangeCharName.HT_szGetString()
	HT_vExchange_SetMessage( eMsgTradeReqSendQuestion, &m_szExchange_DialogBoxMessage );
	g_cUIManager->HT_MessageBox( _DIALOG_TRADEWND, m_szExchange_DialogBoxMessage.HT_szGetString(), 1 );

	m_bClickTradeButtonSw = HT_FALSE;
	// �Ϲ� Ŀ���� ����
	g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	
	return HT_OK;
}

//---------��ȯâ �ٿ��----------//
HTvoid HTExchange::HT_vExchange_ActiveSw( HTbool bType )
{
	if( bType == HT_TRUE )
	{
		m_bExchangeWin_Active = HT_TRUE;

		//	ĳ���� ��ǥ ����
		m_pExchange_MemoryCharPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		
		// Ȯ�� üũ ��ư �ȴ��� ���·�...
		g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 159 );
		// ���Ǿ� �ʱ�ȭ
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 3, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 4, _T("") );
		// ���� �̸�
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 1, m_szExchangeCharName.HT_szGetString() );
		// �� �̸�
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 2, g_oMainCharacterInfo.szCharName );
		// Show Window
		g_cUIManager->HT_SetButtonControlState(_DIALOG_TRADEWND, 6, 0);
		g_cUIManager->HT_ShowWindow( _DIALOG_TRADEWND );
		// �Ϲ� Ŀ���� ����
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
		// �κ��丮 â ����
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
	}
}

//	ESC Key ������ ��ȯâ �ݱ�
HTvoid HTExchange::HT_vExchange_ESC_CloseWindow()
{
	// ������ ��ȯ ���� ���
	// Ȯ�� ��ư�� ���� �ڿ��� ����� �� ����
	if( m_bPress_OK_Button == HT_FALSE )
		g_pNetWorkMgr->RequestTradeCancel();
}
  
HTbool HTExchange::HT_vExchange_ExchangeWinActive()
{
	return m_bExchangeWin_Active;
}

// ��ȯ�� ������ �� �����Կ� ��ϵ� ������ ����
HTvoid HTExchange::HT_vExchangeWindow_DeleteQuickSlotItem()
{
	HTint iKeyID = 0;
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		if( m_sMyItem[i].snIndex > 0 )
		{
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, m_byMyInvenPos[i], iKeyID);
			g_cQuickSlot->HT_vDeleteIconInAllSlotByIndex( m_sMyItem[i].snIndex+HT_ITEM_INDEX_START, iKeyID );
		}
	}
}

//---------��ȯ �³��ϰų� ��������� ��ȯâ �ݰ� ���� �ʱ�ȭ----------//
HTvoid HTExchange::HT_vExchangeWindow_Closed()
{
	m_byExchange_Squence = EXCHANGE_PROCESS_NONE;	// ���� ��ȯ �ܰ�
	//---------���� ��ȯ Ȯ�� ��ư�� ���ȴ°�?----------//
	m_bPress_OK_Button = HT_FALSE;
	m_bExchangeWin_Active = HT_FALSE;
	// ȭ�� ��ư ����
	m_bClickTradeButtonSw = HT_FALSE;
	// �Ϲ� Ŀ���� ����
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
		g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

	m_iMyExchangeRupiah = m_iExchangeRupiah = 0;
	m_iMyItem_Count = m_iOtherCharItem_Count = 0;
	m_szExchangeCharName.HT_hrCleanUp();

	// �� ��ȯâ�� �� ������ ��� ����
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		if( m_sMyItem[i].snIndex != 0 )
			g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, i+EXCHANGE_SLOGCURRECT_MINE,  0 );

		ZeroMemory( &m_sMyItem[i], sizeof( STRUCT_ITEM ) );
		m_byMyInvenPos[i] = -1;
	}

	// ����� ��ȯâ�� �� ������ ��� ����
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		if( m_iOtherCharItemKeyID[i]  != 0 )
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, i+EXCHANGE_SLOGCURRECT_OTHER,  0 );
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_iOtherCharItemKeyID[i] );
			m_iOtherCharItemKeyID[i] = 0;
		}
	}

	// ���Ǿ� �̵����̾��� ��� ���Ǿ� ����ŷâ �ݱ�
	g_cUIManager->HT_HideWindow( _DIALOG_TRADEWND );
}

// �� ��ȯâ�� �÷����� ������
HTRESULT HTExchange::HT_hrExchange_SetMyTradeItem( HTdword dwKeyID, HT_ItemReturnRoom sLocRoom )
{
	if( m_iMyItem_Count == MAX_TRADE )
		return HT_FAIL;

	HTbyte byInvenPos = ( sLocRoom.nCellPosx * _INVEN_HEIGHT + sLocRoom.nCellPosy ) + ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );

	for( HTint i = 0; i < m_iMyItem_Count ; ++i )
	{
		if( m_byMyInvenPos[i] == byInvenPos )
			return HT_OK;	// �̹� ����ִ� ������
	}

	if( g_cItemSystem->HT_bItemSystem_GetItemInfo( dwKeyID, m_sMyItem[m_iMyItem_Count] ) == HT_FALSE )
		return HT_FAIL;
	
	// ����Ʈ ���� �������� ���
	if( CHTParamIDCheck::HT_bIsItemQuestOnly( m_sMyItem[m_iMyItem_Count].snIndex ) )
		return HT_OK;

	m_sMyItem[m_iMyItem_Count].snIndex -= HT_ITEM_INDEX_START;
	// ������ ��ġ ����
	m_byMyInvenPos[m_iMyItem_Count] = byInvenPos;
	
	// �� ��ȯâ�� ������ �̹��� �׸���
	g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, m_iMyItem_Count+EXCHANGE_SLOGCURRECT_MINE, g_pEngineHandler->HT_dwGetItemUIID( m_sMyItem[m_iMyItem_Count].snIndex + HT_ITEM_INDEX_START ) );

	++m_iMyItem_Count;

	// Ȯ�ι�ư�� �����ڿ� �� �������� �÷������� ��� 
	if( m_bPress_OK_Button == HT_TRUE ) 
	{
		m_bPress_OK_Button = HT_FALSE; // Ȯ�ι�ư�� �� ���� ����
		// �� Ȯ�ι�ư�� �ٽ� ���� �� �ְ�
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}

	HT_vNetWork_CSP_Req_Trade();

	return HT_OK;
}

// ������ ��ȯâ�� �÷����� ������
HTvoid HTExchange::HT_vExchange_SetOtherTradeItem( PS_CSP_REQ_TRADE info )
{
	HTdword dwItemIndex = 0;
	HTint iKeyID = 0;
	
	// ������ �÷����� ���Ǿ� ����
	if( info->TradeMoney < 0 )
		m_iExchangeRupiah = 0;
	else
		m_iExchangeRupiah = info->TradeMoney;
	CHTString str;
	str = g_cUIManager->HT_strSetRestMark( m_iExchangeRupiah );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 3, str.HT_szGetString() );
	
	// ������ �÷����� ������ ����
	m_iOtherCharItem_Count = 0;
	HTint i = 0, j = 0;
	for( i = 0 ; i < MAX_TRADE ; ++i )
	{
		if( info->Item[i].snIndex > 0 )
		{
			PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
			item->byType = SET_ITEM_CREATE;
			item->byPlace = ITEM_PLACE_OTHERTRADE;
			item->byIndex = i;
			
			item->sitem.byDummy = info->Item[i].byDummy;
			item->sitem.snDummy = info->Item[i].snDummy;
			item->sitem.wSerial = info->Item[i].wSerial;
			item->sitem.snIndex = info->Item[i].snIndex;
			item->sitem.byCount = info->Item[i].byCount;
			item->sitem.byRefineLevel = info->Item[i].byRefineLevel;
			item->sitem.snDurability = info->Item[i].snDurability;
			
			for( j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				item->sitem.bySubRefine[j] = info->Item[i].bySubRefine[j];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );
			HT_DELETE( item );

			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_OTHERTRADE, i, iKeyID);
			m_iOtherCharItemKeyID[i] = iKeyID;
			++m_iOtherCharItem_Count;
		}
	}

	// ������ Ȯ�ι�ư�� (���� �Ŀ� ������ ������ ���ŵ������� �𸣱� ������) �ȴ��� ���·� �̹��� �ٲٱ�
	// ���� Ȯ�ι�ư�� �����ڿ� ������ �������� �÷������� ��� 
	if( m_bPress_OK_Button == HT_TRUE ) 
	{
		m_bPress_OK_Button = HT_FALSE; // Ȯ�ι�ư�� �� ���� ����
		// �� Ȯ�ι�ư�� �ٽ� ���� �� �ְ�
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}
}

// ��ȯâ�� �÷����� ������ ã��
HTint HTExchange::HT_iExchange_GetKeyIDMyTradeItem( HTint iInvenIndex )
{
	if( iInvenIndex < EXCHANGE_SLOGCURRECT_OTHER || iInvenIndex >= EXCHANGE_SLOGCURRECT_OTHER+MAX_TRADE )
		return 0;

	HTint iKeyID = 0;
	
//	if( iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER >= m_iMyItem_Count )
//		return iKeyID;
/*
	if( m_sMyItem[iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER].snIndex > 0 )
	{
		// KeyID ����
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, m_byMyInvenPos[iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER], iKeyID);
	}
*/

	return m_iOtherCharItemKeyID[iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER];
}

// ��ȯ�� ���Ǿ� ����
HTvoid HTExchange::HT_vExchange_SetMoney( HTint iRupiah )
{
	// ��ȯ���� �ƴϸ� ó������ �ʴ´�.
	//if( m_byExchange_Squence != EXCHANGE_PROCESS_TRADING )
	//	return;

	if( iRupiah < 0 )
		m_iMyExchangeRupiah = 0;
	else
		m_iMyExchangeRupiah = iRupiah;

	CHTString str;
	// %d, m_iMyExchangeRupiah
	str = g_cUIManager->HT_strSetRestMark( m_iMyExchangeRupiah );
	// %d, m_iMyExchangeRupiah
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 4, str.HT_szGetString() );

	// ������ Ȯ�ι�ư�� (���� �Ŀ� ������ ������ ���ŵ������� �𸣱� ������) �ȴ��� ���·� �̹��� �ٲٱ�
	g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 159 );

	// ���� Ȯ�ι�ư�� �����ڿ� ������ �������� �÷������� ��� 
	if( m_bPress_OK_Button == HT_TRUE )
	{
		m_bPress_OK_Button = HT_FALSE; // Ȯ�ι�ư�� �� ���� ����
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}

	HT_vNetWork_CSP_Req_Trade();
}

// ���� ��ȯ������ ���� ��ȯ
HTbool HTExchange::HT_bExchange_IsExchanging( )
{
	// ��ȯ ���� �۾��� ���ϰ� �ִ� ����
	if( m_byExchange_Squence == EXCHANGE_PROCESS_NONE )
		return HT_FALSE;
	else
		return HT_TRUE;
}

//---------��Ʈ��ũ �κ�----------//
HTvoid HTExchange::HT_vNetWork_CSP_Req_Trade()
{
	PS_CSP_REQ_TRADE info = HT_NULL;
	info = new S_CSP_REQ_TRADE;
	ZeroMemory( info, sizeof( S_CSP_REQ_TRADE ) );
	
	if( m_byExchange_Squence == EXCHANGE_PROCESS_TRADECANCEL ) // ��ȯ ��û ������ ���� ����� ���
	{
		// �ŷ� ��û ����
		info->OpponentID = m_dwReceiveExchangeCharKeyID;
		info->TradeMoney = -1;
	}
	else
	{
		info->OpponentID = (unsigned short)m_dwExchangeCharKeyID;	// ���� ID
		info->TradeMoney = m_iMyExchangeRupiah;		// ��ȯ�� ���Ǿ�
	}

	// �� Ȯ�� ��ư ���� ��� �ܿ� 0�̴�
	if( m_byExchange_Squence == EXCHANGE_PROCESS_PRESS_OK )
		info->MyCheck = EXCHANGE_OK;
	else
		info->MyCheck = EXCHANGE_CANCEL;

	// ��ȯ ���� ���� ���� ��ȯâ�� ������ ������ ����
	HTint i = 0;
	if( m_byExchange_Squence == EXCHANGE_PROCESS_TRADING || m_byExchange_Squence == EXCHANGE_PROCESS_PRESS_OK )	
	{
		HTint j = 0;
		for( i = 0 ; i < m_iMyItem_Count ; ++i)
		{
			// �� ��ȯâ�� �÷����� ������ ����
			info->Item[i].snIndex = m_sMyItem[i].snIndex ;
			info->Item[i].byCount = m_sMyItem[i].byCount ;
			info->Item[i].snDurability = m_sMyItem[i].snDurability;
			info->Item[i].byRefineLevel = m_sMyItem[i].byRefineLevel;
			for( j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				info->Item[i].bySubRefine[j] = m_sMyItem[i].bySubRefine[j];
			
			info->Item[i].byDummy = m_sMyItem[i].byDummy ;
			info->Item[i].snDummy = m_sMyItem[i].snDummy ;
			info->Item[i].wSerial = m_sMyItem[i].wSerial ;

			// ������ ��ġ ����
			info->InvenPos[i] = m_byMyInvenPos[i];
		}

		for( i = m_iMyItem_Count ; i < MAX_TRADE ; ++i )
			info->InvenPos[i] = -1;
	}
	else
	{
		for( i = 0; i < MAX_TRADE ; ++i )
			info->InvenPos[i] = -1;
	}

	g_pNetWorkMgr->RequestExchange( info );
	HT_DELETE( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqTrade : %d", m_dwExchangeCharKeyID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
  
HTvoid HTExchange::HT_vNetWork_SCP_Resp_Trade( PS_CSP_REQ_TRADE info )
{
	switch( m_byExchange_Squence )
	{
		// ������ ��ȯ ��û�� ���
		case EXCHANGE_PROCESS_NONE : 
		{
			m_byExchange_Squence = EXCHANGE_PROCESS_RECEIVETRADE;
			m_dwExchangeCharKeyID = m_dwReceiveExchangeCharKeyID =  info->OpponentID;	// ���� ID
			m_szExchangeCharName = info->szCharName;

			
			if (g_iInationalType == INATIONALTYPE_CHINA)
			{
				// ���� �߰� ���� (�߱��� �䱸 : 2004. 10. 21 ������) �Ϲ� �� ��� ��� ������ �ϹǷ� �α��뼭 ó��
				HTint OtherLevel = 0;
				OtherLevel = g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel(m_dwExchangeCharKeyID);
				m_szExchangeCharName.HT_szFormat("%s (Lv %d)", m_szExchangeCharName.HT_szGetString(), OtherLevel);
			}

			// NPC�� ��ȭ���̰ų� �ٸ� ����� trade �� �Ǵ� ���� ���� ����/���� �� ����̸� �����۱�ȯ ��û ����
			if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
			{
				//m_byExchangeResult = EXCHANGE_CANCEL;
				//������ ��ȯ ��û�� ���� ��Ҹ� ����
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
				
				CHTString str;
				// %s���� ��ȯ ��û�� �����߽��ϴ�. 
				HT_vExchange_SetMessage( eMsgTradeReqReceiveRejection, &str );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ERROR, str );
			}
			else
			{
				if (g_cUIManager->HT_isShowWindow(_DIALOG_TRADE) == true)
				{
					return;
				}

				m_byExchange_Squence = EXCHANGE_PROCESS_RECEIVETRADE;

				// %s���� ��ȯ�� ��û�߽��ϴ�.
				HT_vExchange_SetMessage( eMsgTradeReqReceive, &m_szExchange_DialogBoxMessage );
				g_cUIManager->HT_MessageBox( _DIALOG_TRADEWND, m_szExchange_DialogBoxMessage.HT_szGetString(), 1 );
			}
		}
			break;
		// ���� ��ȯ ��û�Ϸ��� �غ��ϴ� ���
		case EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM :
		{
			if( info->OpponentID == m_dwExchangeCharKeyID ) // ���� ��ȯ�� ��û�� ĳ������ ��ȯ ��û�� ���
			{
				// ������ ��ȯ ��û�� ���� ����� ������ �����Ѵ�
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				HT_vExchange_ActiveSw( HT_TRUE );
			}
			else // �ٸ� ����� ������ ��ȯ�� ��û���� ���
			{
				m_dwReceiveExchangeCharKeyID = info->OpponentID;
				//������ ��ȯ ��û�� ���� ��Ҹ� ����
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM;
			}
		}
			break;
		// ���� ��ȯ ��û�� ���
		case EXCHANGE_PROCESS_REQUESTTRADE :
		{
			if( info->OpponentID == m_dwExchangeCharKeyID ) // ���� ��ȯ�� ��û�� ĳ������ ����� ���
			{
				// ������ ��ȯ �³��� ��쿡�� �޼����� ���� ������...
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				HT_vExchange_ActiveSw( HT_TRUE );
			}
			else // �ٸ� ĳ������ ��ȯ ��û�� ���
			{
				m_dwReceiveExchangeCharKeyID = info->OpponentID;
				//������ ��ȯ ��û�� ���� ��Ҹ� ����
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE;
			}
		}
			break;
		// ��ȯ ���� ��� 
		case EXCHANGE_PROCESS_TRADING :	
		{
			if( info->MyCheck == EXCHANGE_OK )	// ������ Ȯ�� ��ư�� ������.
			{
				// ������ Ȯ�ι�ư�� ���� ���·� �̹��� �ٲٱ�
				g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 160 );
			}
			else
			{
				// ����� ��ȯâ�� ������ ����
				HT_vExchange_SetOtherTradeItem( info );
			}
		}
			break;

		// ���� Ȯ�� ��ư ���� ����
		case EXCHANGE_PROCESS_PRESS_OK :
		{
			if( info->MyCheck != EXCHANGE_OK )	// ������ Ȯ�� ��ư�� ������ �ʾ��� ���
			{
				// ����� ��ȯâ�� ������ ����
				HT_vExchange_SetOtherTradeItem( info );
			}
		}
			break;

		default:
			break;
	}
}

//---------������ ��ȯ ���� ���_���----------//
HTvoid HTExchange::HT_vNetWork_SCP_Resp_Trade_Cancel( PS_RESULT info )
{
	//	S_SCP_RESP_TRADE_CANCEL�� S_RESULT�� �̿��ϱ�� �Ѵ�.
	CHTString str;
	switch( info->nResult )
	{
		case REPLY_TRADE_SUCCESS :
		{
			// ��ȯ�� �Ϸ�Ǿ����ϴ�.
			HT_vExchange_SetMessage( eMsgTradeSuccess, &str );
			// ��ȯ�� ���Ǿ� ����
			// �������� �������� ����� ��ġ�� ������ ������.
			// ������ ������ �ִ� ���Ǿ�
			if( m_iExchangeRupiah > 0 )	
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( 
										g_cEquipInventory->HT_iEquipInventory_GetPCMoney() + m_iExchangeRupiah );
			// ���� ���濡�� �ִ� ���Ǿ�
			if( m_iMyExchangeRupiah > 0 )	
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( 
										g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - m_iMyExchangeRupiah );
			// ��ȯ�� ������ �� �����Կ� ��ϵ� �������� ���� ��� �����Ѵ�
			HT_vExchangeWindow_DeleteQuickSlotItem();
		}
			break;
		case REPLY_TRADE_USER_DENAY :
			// %s���� �ŷ��� ����߽��ϴ�. 
			HT_vExchange_SetMessage( eMsgTradeCancel, &str );
			break;		
		case REPLY_TRADE_OVER_ME :
			// �κ��丮 ������ �����մϴ�.
			HT_vExchange_SetMessage( eMsgItemCommonInvenLack, &str );
			break;	
		case REPLY_TRADE_OVER_YOU :
			// ������ �κ��丮 ������ �����մϴ�.
			HT_vExchange_SetMessage( eMsgTradeOtherInvenLack, &str );
			break;
		case REPLY_TRADE_OUTINDEX :
			// ������ ������ ã�� �� �����ϴ�.
			HT_vExchange_SetMessage( eMsgItemCommonCannotFindInfo, &str );
			break;
		case REPLY_TRADE_USER_DIE:
			// User ������� ��ȯ�� ��ĥ �� �����ϴ�.
			HT_vExchange_SetMessage( eMsgTradeOtherDie, &str );
			break;
		case REPLY_TRADE_USER_CHANGE:
			// ��ȯ �߿� �� �ٸ� ĳ���Ϳ� ��ȯ�� �� �����ϴ�.
			HT_vExchange_SetMessage( eMsgTradeExchanging, &str );
			break;
		default:
			// ��ȯ�� �����߽��ϴ�.
			HT_vExchange_SetMessage( eMsgTradeFail, &str );
			break;
	}
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str );

	// Ʈ���̵�â �ݱ�
	HT_vExchangeWindow_Closed();
}