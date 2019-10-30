#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htexchange.h"

#define EXCHANGE_PROCESS_NONE					0
#define EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM	1
#define EXCHANGE_PROCESS_REQUESTTRADE			2
#define EXCHANGE_PROCESS_RECEIVETRADE			3
#define EXCHANGE_PROCESS_TRADING				4
#define EXCHANGE_PROCESS_PRESS_OK				5 // 내 확인 버튼 누른 상태
#define EXCHANGE_PROCESS_TRADECANCEL			6 // 거래요청 거절

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
	//---------교환 프로세스----------//
	m_byExchange_Squence = EXCHANGE_PROCESS_NONE;

	//---------내가 교환 확인 버튼을 눌렸는가?----------//
	m_bPress_OK_Button = HT_FALSE;

	//---------내가 교환의 요청했냐? 0:없음,1:내가요청,2:상대방이 요청----------//
	//m_byRequest_Index = EXCHANGE_PROCESS_NONE;
	m_dwExchangeCharKeyID = m_dwReceiveExchangeCharKeyID = 0;
	m_szExchangeCharName.HT_hrCleanUp();
	m_iExchangeRupiah = m_iMyExchangeRupiah = 0;
	m_iMyItem_Count = m_iOtherCharItem_Count = 0;
	// 내 교환창에 들어갈 아이템 목록 초기화
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		ZeroMemory( &m_sMyItem[i], sizeof( STRUCT_ITEM ) );
		m_byMyInvenPos[i] = -1;	// 위치가 0부터 시작하기 때문에
	}
	// 상대편 교환창에 들어갈 아이템 목록 초기화
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 0, 8, 3, 36, 1400, 326, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	교환
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Edit facing each other
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 1, 9, 7, 56, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonEachOther, &strMessage, _T(""), _T("") );	//	상대방
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 7, 56, 152, 19 );
	//	Edit the person in question
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 2, 9, 165, 56, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonMySelf, &strMessage, _T(""), _T("") );	//	본인
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 165, 56, 152, 19 );
	//	Button facing each other 루피아
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 3, 88, 8, 157, 89, 87 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 3, 10, 40, 157, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 161, 40, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 161, 73, 13 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 3 );
	//	Button the person in question 루피아
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 4, 88, 176, 157, 89, 87 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 4, 10, 208, 157, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRupia, &strMessage, _T(""), _T("") );	//	루피아
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 288, 161, 40, 16 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 211, 161, 73, 13 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 4 );
	//	Button 교환 facing each other
	g_cUIManager->HT_AddTextureControl( _DIALOG_TRADEWND, 5, 159, 8, 181, 1400, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	교환
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 8, 181, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 5 );
	//	Button 교환 the person in question
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 6, 159, 175, 181, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	교환
	g_cUIManager->HT_AddLabelControl( _DIALOG_TRADEWND, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 175, 181, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TRADEWND, 6 );
	//	Button 교환 the person in question
	g_cUIManager->HT_AddButtonControl( _DIALOG_TRADEWND, 7, 159, 251, 181, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
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

//	입력 메세지 처리
//	Exchange Inventory
void HTExchange::HT_vEchsnhge_InputCheckForExchange(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X Button
		if( iTargetID == -1 )
		{
			// 확인 버튼을 누른 뒤에는 취소할 수 없다
			if( g_cExchangeSystem->m_bPress_OK_Button == HT_FALSE )
				g_pNetWorkMgr->RequestTradeCancel();
		}
		// 아이템 교환
		else if( iTargetID == 6 )
		{
			if( g_cExchangeSystem->m_bPress_OK_Button == HT_FALSE )
			{
				// 확인버튼이 눌려있는 상태
				g_cUIManager->HT_SetButtonControlState(_DIALOG_TRADEWND, 6, 1);
				g_cExchangeSystem->m_bPress_OK_Button = HT_TRUE;
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_PRESS_OK;
				//---------아이템 교환을 승낙----------//
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
			}
		}
		//	취소
		else if( iTargetID == 7 )
		{
			// 확인 버튼을 누른 뒤에는 취소할 수 없다
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
				// NPC와 대화중이거나 개인 상점 열기/구입 일 경우이면 처리 안함
				if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) 
						|| g_cUIManager->HT_isShowWindow(_DIALOG_TRADE)
						|| g_cUIManager->HT_isShowWindow( _DIALOG_PRIVATE_SHOP ) 
						|| g_cUIManager->HT_isShowWindow( _DIALOG_PRIVATE_SHOP_BUY ) )
				{
					g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
				}
				else
				{
					//	아이템 교환 요청을 하자
					g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
					g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE;
				}
			}
			else if( g_cExchangeSystem->m_byExchange_Squence == EXCHANGE_PROCESS_RECEIVETRADE )
			{ 
				// 아이템 교환 요청에 대한 결과를 서버에 전송한다
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				g_cExchangeSystem->HT_vExchange_ActiveSw( HT_TRUE );
			}
		}
		else if( iTargetID == 3 )
		{
			if( g_cExchangeSystem->m_byExchange_Squence == EXCHANGE_PROCESS_RECEIVETRADE )
			{
				// 아이템 교환 요청에 대한 결과를 서버에 전송
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				g_cExchangeSystem->HT_vNetWork_CSP_Req_Trade();
				g_cExchangeSystem->m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	다른 윈도우에서 왔으면 아이콘 스킵
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
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vExchange_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vExchange_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 다른 캐릭터 이름
		case eMsgParamOthercharName	:
			*pszParam = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_dwExchangeCharKeyID);
			break;

		default:
			break;
	}
}

//---------반환/셋팅----------//
//---------교환 요청 버튼을 클릭했는가?----------//
HTvoid HTExchange::HT_vExchange_SetClickTradeButton( HTbool bType )
{
	if( m_bClickTradeButtonSw == HT_TRUE )
	{
		m_bClickTradeButtonSw = HT_FALSE;
		// 일반 커서로 변경
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}
	else
	{
		m_bClickTradeButtonSw = HT_TRUE;
		// Trade Ani 커서로 변경
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
	}
}

HTbool HTExchange::HT_vExchange_GetClickTradeButton()
{
	return m_bClickTradeButtonSw;
}

//---------교환 요청을 하자----------//
HTRESULT HTExchange::HT_vExchange_RequestTrade( HTint nModelID )
{
	if( m_bClickTradeButtonSw == HT_FALSE )
		return HT_FAIL; 
	
	// NPC와 대화중이거나 다른 사람과 trade 중이면 아이템교환 요청 취소
	if(  m_bExchangeWin_Active == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
		return HT_OK;

	//	상대방의 키아디를 알아오고 
	m_dwExchangeCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nModelID );
	m_szExchangeCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwExchangeCharKeyID );

	if (g_iInationalType == INATIONALTYPE_CHINA)
	{
		// 레벨 추가 설정 (중국측 요구 : 2004. 10. 21 선영범) 일방 및 대방 모두 보여야 하므로 두군대서 처리
		HTint OtherLevel = 0;
		OtherLevel = g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel(m_dwExchangeCharKeyID);
		m_szExchangeCharName.HT_szFormat("%s (Lv %d)", m_szExchangeCharName.HT_szGetString(), OtherLevel);
	}

	//	아이템 교환 요청하는 대화상자를 뛰우고
	m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM;

	// %s 님께 아이템 교환을 요청할까요?, m_szExchangeCharName.HT_szGetString()
	HT_vExchange_SetMessage( eMsgTradeReqSendQuestion, &m_szExchange_DialogBoxMessage );
	g_cUIManager->HT_MessageBox( _DIALOG_TRADEWND, m_szExchange_DialogBoxMessage.HT_szGetString(), 1 );

	m_bClickTradeButtonSw = HT_FALSE;
	// 일반 커서로 변경
	g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	
	return HT_OK;
}

//---------교환창 뛰우기----------//
HTvoid HTExchange::HT_vExchange_ActiveSw( HTbool bType )
{
	if( bType == HT_TRUE )
	{
		m_bExchangeWin_Active = HT_TRUE;

		//	캐릭터 좌표 저장
		m_pExchange_MemoryCharPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		
		// 확인 체크 버튼 안누른 상태로...
		g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 159 );
		// 루피아 초기화
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 3, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 4, _T("") );
		// 상대방 이름
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 1, m_szExchangeCharName.HT_szGetString() );
		// 내 이름
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 2, g_oMainCharacterInfo.szCharName );
		// Show Window
		g_cUIManager->HT_SetButtonControlState(_DIALOG_TRADEWND, 6, 0);
		g_cUIManager->HT_ShowWindow( _DIALOG_TRADEWND );
		// 일반 커서로 변경
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
		// 인벤토리 창 열기
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
	}
}

//	ESC Key 누르면 교환창 닫기
HTvoid HTExchange::HT_vExchange_ESC_CloseWindow()
{
	// 아이템 교환 상태 취소
	// 확인 버튼을 누른 뒤에는 취소할 수 없다
	if( m_bPress_OK_Button == HT_FALSE )
		g_pNetWorkMgr->RequestTradeCancel();
}
  
HTbool HTExchange::HT_vExchange_ExchangeWinActive()
{
	return m_bExchangeWin_Active;
}

// 교환한 아이템 중 퀵슬롯에 등록된 아이템 삭제
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

//---------교환 승낙하거나 취소했을대 교환창 닫고 변수 초기화----------//
HTvoid HTExchange::HT_vExchangeWindow_Closed()
{
	m_byExchange_Squence = EXCHANGE_PROCESS_NONE;	// 현재 교환 단계
	//---------내가 교환 확인 버튼을 눌렸는가?----------//
	m_bPress_OK_Button = HT_FALSE;
	m_bExchangeWin_Active = HT_FALSE;
	// 화면 버튼 갱신
	m_bClickTradeButtonSw = HT_FALSE;
	// 일반 커서로 변경
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
		g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

	m_iMyExchangeRupiah = m_iExchangeRupiah = 0;
	m_iMyItem_Count = m_iOtherCharItem_Count = 0;
	m_szExchangeCharName.HT_hrCleanUp();

	// 내 교환창에 들어간 아이템 목록 삭제
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		if( m_sMyItem[i].snIndex != 0 )
			g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, i+EXCHANGE_SLOGCURRECT_MINE,  0 );

		ZeroMemory( &m_sMyItem[i], sizeof( STRUCT_ITEM ) );
		m_byMyInvenPos[i] = -1;
	}

	// 상대편 교환창에 들어간 아이템 목록 삭제
	for( HTint i=0 ; i < MAX_TRADE ; ++i )
	{
		if( m_iOtherCharItemKeyID[i]  != 0 )
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, i+EXCHANGE_SLOGCURRECT_OTHER,  0 );
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_iOtherCharItemKeyID[i] );
			m_iOtherCharItemKeyID[i] = 0;
		}
	}

	// 루피아 이동중이었을 경우 루피아 언패킹창 닫기
	g_cUIManager->HT_HideWindow( _DIALOG_TRADEWND );
}

// 내 교환창에 올려놓은 아이템
HTRESULT HTExchange::HT_hrExchange_SetMyTradeItem( HTdword dwKeyID, HT_ItemReturnRoom sLocRoom )
{
	if( m_iMyItem_Count == MAX_TRADE )
		return HT_FAIL;

	HTbyte byInvenPos = ( sLocRoom.nCellPosx * _INVEN_HEIGHT + sLocRoom.nCellPosy ) + ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );

	for( HTint i = 0; i < m_iMyItem_Count ; ++i )
	{
		if( m_byMyInvenPos[i] == byInvenPos )
			return HT_OK;	// 이미 들어있는 아이템
	}

	if( g_cItemSystem->HT_bItemSystem_GetItemInfo( dwKeyID, m_sMyItem[m_iMyItem_Count] ) == HT_FALSE )
		return HT_FAIL;
	
	// 퀘스트 전용 아이템일 경우
	if( CHTParamIDCheck::HT_bIsItemQuestOnly( m_sMyItem[m_iMyItem_Count].snIndex ) )
		return HT_OK;

	m_sMyItem[m_iMyItem_Count].snIndex -= HT_ITEM_INDEX_START;
	// 아이템 위치 정보
	m_byMyInvenPos[m_iMyItem_Count] = byInvenPos;
	
	// 내 교환창에 아이템 이미지 그리기
	g_cUIManager->HT_SetSlotImage( _DIALOG_TRADEWND, m_iMyItem_Count+EXCHANGE_SLOGCURRECT_MINE, g_pEngineHandler->HT_dwGetItemUIID( m_sMyItem[m_iMyItem_Count].snIndex + HT_ITEM_INDEX_START ) );

	++m_iMyItem_Count;

	// 확인버튼을 누른뒤에 또 아이템을 올려놓았을 경우 
	if( m_bPress_OK_Button == HT_TRUE ) 
	{
		m_bPress_OK_Button = HT_FALSE; // 확인버튼이 안 눌린 상태
		// 내 확인버튼을 다시 누를 수 있게
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}

	HT_vNetWork_CSP_Req_Trade();

	return HT_OK;
}

// 상대방이 교환창에 올려놓은 아이템
HTvoid HTExchange::HT_vExchange_SetOtherTradeItem( PS_CSP_REQ_TRADE info )
{
	HTdword dwItemIndex = 0;
	HTint iKeyID = 0;
	
	// 상대방이 올려놓은 루피아 갱신
	if( info->TradeMoney < 0 )
		m_iExchangeRupiah = 0;
	else
		m_iExchangeRupiah = info->TradeMoney;
	CHTString str;
	str = g_cUIManager->HT_strSetRestMark( m_iExchangeRupiah );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_TRADEWND, 3, str.HT_szGetString() );
	
	// 상대방이 올려놓은 아이템 갱신
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

	// 상대방의 확인버튼이 (눌린 후에 아이템 정보가 갱신됐을지도 모르기 때문에) 안누른 상태로 이미지 바꾸기
	// 내가 확인버튼을 누른뒤에 상대방이 아이템을 올려놓았을 경우 
	if( m_bPress_OK_Button == HT_TRUE ) 
	{
		m_bPress_OK_Button = HT_FALSE; // 확인버튼이 안 눌린 상태
		// 내 확인버튼을 다시 누를 수 있게
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}
}

// 교환창에 올려놓은 아이템 찾기
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
		// KeyID 생성
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, m_byMyInvenPos[iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER], iKeyID);
	}
*/

	return m_iOtherCharItemKeyID[iInvenIndex-EXCHANGE_SLOGCURRECT_OTHER];
}

// 교환할 루피아 설정
HTvoid HTExchange::HT_vExchange_SetMoney( HTint iRupiah )
{
	// 교환중이 아니면 처리하지 않는다.
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

	// 상대방의 확인버튼이 (눌린 후에 아이템 정보가 갱신됐을지도 모르기 때문에) 안누른 상태로 이미지 바꾸기
	g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 159 );

	// 내가 확인버튼을 누른뒤에 상대방이 아이템을 올려놓았을 경우 
	if( m_bPress_OK_Button == HT_TRUE )
	{
		m_bPress_OK_Button = HT_FALSE; // 확인버튼이 안 눌린 상태
		m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
	}

	HT_vNetWork_CSP_Req_Trade();
}

// 현재 교환중인지 상태 반환
HTbool HTExchange::HT_bExchange_IsExchanging( )
{
	// 교환 관련 작업을 안하고 있는 상태
	if( m_byExchange_Squence == EXCHANGE_PROCESS_NONE )
		return HT_FALSE;
	else
		return HT_TRUE;
}

//---------네트워크 부분----------//
HTvoid HTExchange::HT_vNetWork_CSP_Req_Trade()
{
	PS_CSP_REQ_TRADE info = HT_NULL;
	info = new S_CSP_REQ_TRADE;
	ZeroMemory( info, sizeof( S_CSP_REQ_TRADE ) );
	
	if( m_byExchange_Squence == EXCHANGE_PROCESS_TRADECANCEL ) // 교환 요청 거절에 대한 대답일 경우
	{
		// 거래 요청 거절
		info->OpponentID = m_dwReceiveExchangeCharKeyID;
		info->TradeMoney = -1;
	}
	else
	{
		info->OpponentID = (unsigned short)m_dwExchangeCharKeyID;	// 상대방 ID
		info->TradeMoney = m_iMyExchangeRupiah;		// 교환할 루피아
	}

	// 내 확인 버튼 누른 경우 외엔 0이다
	if( m_byExchange_Squence == EXCHANGE_PROCESS_PRESS_OK )
		info->MyCheck = EXCHANGE_OK;
	else
		info->MyCheck = EXCHANGE_CANCEL;

	// 교환 진행 중일 때만 교환창의 아이템 정보를 전송
	HTint i = 0;
	if( m_byExchange_Squence == EXCHANGE_PROCESS_TRADING || m_byExchange_Squence == EXCHANGE_PROCESS_PRESS_OK )	
	{
		HTint j = 0;
		for( i = 0 ; i < m_iMyItem_Count ; ++i)
		{
			// 내 교환창에 올려놓은 아이템 정보
			info->Item[i].snIndex = m_sMyItem[i].snIndex ;
			info->Item[i].byCount = m_sMyItem[i].byCount ;
			info->Item[i].snDurability = m_sMyItem[i].snDurability;
			info->Item[i].byRefineLevel = m_sMyItem[i].byRefineLevel;
			for( j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				info->Item[i].bySubRefine[j] = m_sMyItem[i].bySubRefine[j];
			
			info->Item[i].byDummy = m_sMyItem[i].byDummy ;
			info->Item[i].snDummy = m_sMyItem[i].snDummy ;
			info->Item[i].wSerial = m_sMyItem[i].wSerial ;

			// 아이템 위치 정보
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqTrade : %d", m_dwExchangeCharKeyID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
  
HTvoid HTExchange::HT_vNetWork_SCP_Resp_Trade( PS_CSP_REQ_TRADE info )
{
	switch( m_byExchange_Squence )
	{
		// 상대방이 교환 요청한 경우
		case EXCHANGE_PROCESS_NONE : 
		{
			m_byExchange_Squence = EXCHANGE_PROCESS_RECEIVETRADE;
			m_dwExchangeCharKeyID = m_dwReceiveExchangeCharKeyID =  info->OpponentID;	// 상대방 ID
			m_szExchangeCharName = info->szCharName;

			
			if (g_iInationalType == INATIONALTYPE_CHINA)
			{
				// 레벨 추가 설정 (중국측 요구 : 2004. 10. 21 선영범) 일방 및 대방 모두 보여야 하므로 두군대서 처리
				HTint OtherLevel = 0;
				OtherLevel = g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel(m_dwExchangeCharKeyID);
				m_szExchangeCharName.HT_szFormat("%s (Lv %d)", m_szExchangeCharName.HT_szGetString(), OtherLevel);
			}

			// NPC와 대화중이거나 다른 사람과 trade 중 또는 개인 상점 열기/구입 일 경우이면 아이템교환 요청 거절
			if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
			{
				//m_byExchangeResult = EXCHANGE_CANCEL;
				//아이템 교환 요청에 대한 취소를 전송
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_NONE;
				
				CHTString str;
				// %s님의 교환 요청을 거절했습니다. 
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

				// %s님이 교환을 요청했습니다.
				HT_vExchange_SetMessage( eMsgTradeReqReceive, &m_szExchange_DialogBoxMessage );
				g_cUIManager->HT_MessageBox( _DIALOG_TRADEWND, m_szExchange_DialogBoxMessage.HT_szGetString(), 1 );
			}
		}
			break;
		// 내가 교환 요청하려고 준비하는 경우
		case EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM :
		{
			if( info->OpponentID == m_dwExchangeCharKeyID ) // 내가 교환을 신청한 캐릭터의 교환 신청일 경우
			{
				// 아이템 교환 요청에 대한 결과를 서버에 전송한다
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				HT_vExchange_ActiveSw( HT_TRUE );
			}
			else // 다른 사람이 나에게 교환을 요청했을 경우
			{
				m_dwReceiveExchangeCharKeyID = info->OpponentID;
				//아이템 교환 요청에 대한 취소를 전송
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE_CONFIRM;
			}
		}
			break;
		// 내가 교환 요청한 결과
		case EXCHANGE_PROCESS_REQUESTTRADE :
		{
			if( info->OpponentID == m_dwExchangeCharKeyID ) // 내가 교환을 신청한 캐릭터의 대답일 경우
			{
				// 상대방이 교환 승낙한 경우에만 메세지가 오기 때문에...
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADING;
				HT_vExchange_ActiveSw( HT_TRUE );
			}
			else // 다른 캐릭터의 교환 신청일 경우
			{
				m_dwReceiveExchangeCharKeyID = info->OpponentID;
				//아이템 교환 요청에 대한 취소를 전송
				m_byExchange_Squence = EXCHANGE_PROCESS_TRADECANCEL;
				HT_vNetWork_CSP_Req_Trade();
				m_byExchange_Squence = EXCHANGE_PROCESS_REQUESTTRADE;
			}
		}
			break;
		// 교환 중일 경우 
		case EXCHANGE_PROCESS_TRADING :	
		{
			if( info->MyCheck == EXCHANGE_OK )	// 상대방이 확인 버튼을 눌렀음.
			{
				// 상대방의 확인버튼을 누른 상태로 이미지 바꾸기
				g_cUIManager->HT_SetTextureControlImage( _DIALOG_TRADEWND, 5, 160 );
			}
			else
			{
				// 상대편 교환창의 아이템 갱신
				HT_vExchange_SetOtherTradeItem( info );
			}
		}
			break;

		// 내가 확인 버튼 누른 상태
		case EXCHANGE_PROCESS_PRESS_OK :
		{
			if( info->MyCheck != EXCHANGE_OK )	// 상대방이 확인 버튼을 누르지 않았을 경우
			{
				// 상대편 교환창의 아이템 갱신
				HT_vExchange_SetOtherTradeItem( info );
			}
		}
			break;

		default:
			break;
	}
}

//---------아이템 교환 상태 취소_결과----------//
HTvoid HTExchange::HT_vNetWork_SCP_Resp_Trade_Cancel( PS_RESULT info )
{
	//	S_SCP_RESP_TRADE_CANCEL는 S_RESULT를 이용하기로 한다.
	CHTString str;
	switch( info->nResult )
	{
		case REPLY_TRADE_SUCCESS :
		{
			// 교환이 완료되었습니다.
			HT_vExchange_SetMessage( eMsgTradeSuccess, &str );
			// 교환된 루피아 적용
			// 아이템은 서버에서 변경된 위치로 정보를 보내줌.
			// 상대방이 나에게 주는 루피아
			if( m_iExchangeRupiah > 0 )	
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( 
										g_cEquipInventory->HT_iEquipInventory_GetPCMoney() + m_iExchangeRupiah );
			// 내가 상대방에게 주는 루피아
			if( m_iMyExchangeRupiah > 0 )	
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( 
										g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - m_iMyExchangeRupiah );
			// 교환한 아이템 중 퀵슬롯에 등록된 아이템이 있을 경우 삭제한다
			HT_vExchangeWindow_DeleteQuickSlotItem();
		}
			break;
		case REPLY_TRADE_USER_DENAY :
			// %s님이 거래를 취소했습니다. 
			HT_vExchange_SetMessage( eMsgTradeCancel, &str );
			break;		
		case REPLY_TRADE_OVER_ME :
			// 인벤토리 공간이 부족합니다.
			HT_vExchange_SetMessage( eMsgItemCommonInvenLack, &str );
			break;	
		case REPLY_TRADE_OVER_YOU :
			// 상대방의 인벤토리 공간이 부족합니다.
			HT_vExchange_SetMessage( eMsgTradeOtherInvenLack, &str );
			break;
		case REPLY_TRADE_OUTINDEX :
			// 아이템 정보를 찾을 수 없습니다.
			HT_vExchange_SetMessage( eMsgItemCommonCannotFindInfo, &str );
			break;
		case REPLY_TRADE_USER_DIE:
			// User 사망으로 교환을 마칠 수 없습니다.
			HT_vExchange_SetMessage( eMsgTradeOtherDie, &str );
			break;
		case REPLY_TRADE_USER_CHANGE:
			// 교환 중에 또 다른 캐릭터와 교환할 수 없습니다.
			HT_vExchange_SetMessage( eMsgTradeExchanging, &str );
			break;
		default:
			// 교환이 실패했습니다.
			HT_vExchange_SetMessage( eMsgTradeFail, &str );
			break;
	}
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str );

	// 트레이드창 닫기
	HT_vExchangeWindow_Closed();
}