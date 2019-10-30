//-------------------------------------------------------------------------------
// File: HTAddress.cpp
//
// Desc: Address book(friend list)
// List of friend list, check friend's login status, send them whisper chat
// easily, Group management is also available.
//
// 20030410Tenma
//-------------------------------------------------------------------------------
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTAddress.h" 

//	종족 이미지 넘버
HTint	g_iTribeImageNumber[2][8] = { 23642,23644,23646,23648,23650,23652,23654,23656,
									  23643,23645,23647,23649,23651,23653,23655,23657 };

//	종족 이미지 넘버
HTint	iGodImageNumber[3] = { 23660, 23659, 23658 };

HTint	g_iCast[5]	= { 23704, 23705, 23703, 23702, 23701 };

#define _MAP_NAME_MANDARA1		1
#define _MAP_NAME_SHAMBARA		2
#define _MAP_NAME_UNDER1		3
#define _MAP_NAME_UNDER2		4
#define _MAP_NAME_UNDER3		5
#define _MAP_NAME_UNDER4		6
#define _MAP_NAME_TRIMURITY		10


HTAddress::HTAddress(void)
{
	// Initialize the friend list data structure(linked list)
	m_bActive = HT_FALSE;
	m_bRegister_Sw = HT_FALSE;
	m_bRegisterBlock = HT_FALSE;
	m_bAddress_MemberDeleteBtn = HT_FALSE;
	m_bAddress_ReqRegistBtn = HT_FALSE;
	m_bAddress_ReceiveRegistBtn = HT_FALSE;
	m_bAddress_DlgBoxSw = HT_FALSE;
	m_bAddress_ReDlgBoxSw = HT_FALSE;
	m_bAddress_ErrorSw = HT_FALSE;
	m_bAddress_JoinAddressResultSw = HT_FALSE;
	
	m_dwAddress_OtherCharKeyID = 0;
	m_nAddres_MemberCount = 0;
	m_nAddress_SelectedMember = 0;

	for ( HTint i = 0; i < MAX_MESSENGER; ++i )
	{
		memset( &m_oAddress_Item[i], 0, sizeof(STRUCT_MESSENGER_ITEM) );
	}
}

HTAddress::~HTAddress(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_ADDRESS );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vAddress_Init()
// D : Load resources.
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vAddress_Init()
{
	ZeroMemory( &m_oAddress_Item, sizeof(STRUCT_MESSENGER_ITEM)*MAX_MESSENGER );
	//	Create Window
	this->HT_vAddress_CreateWindow();
	g_cUIManager->HT_ShowWindow( _DIALOG_ADDRESS );
}

//	Create Window
HTvoid HTAddress::HT_vAddress_CreateWindow()
{
	CHTString strMessage;
	//	[Address]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ADDRESS, _T("Address"), 330, 466, g_cAddress->HT_vAddress_InputCheckForAddress, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ADDRESS, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button 주소록
	g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 0, 9, 40, 31, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressAddress, &strMessage, _T(""), _T("") );	//	주소록
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 1 );
	//	Button 종족
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 2, 9, 5, 56, 0, 0, 1500, 62, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressTribe, &strMessage, _T(""), _T("") );	//	종족
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 56, 62, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 2 );
	//	Button 이름
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 3, 9, 70, 56, 0, 0, 1500, 173, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressName, &strMessage, _T(""), _T("") );	//	이름
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 56, 173, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 3 );
	//	Button 접속
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 4, 9, 246, 56, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressConnect, &strMessage, _T(""), _T("") );	//	접속
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 56, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 4 );
	////	Button 등록 요청 차단
	//g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 5, 9, 20, 420, 0, 0, 1500, 90, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 5, _T("등록 요청 차단"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 420, 90, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 5 );
	//	Button 등록
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 6, 159, 20, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRegist, &strMessage, _T(""), _T("") );	//	등록
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 441, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 6 );
	//	Button 삭제
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 7, 159, 98, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonDelete, &strMessage, _T(""), _T("") );	//	삭제
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 98, 441, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 7 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 8, 159, 190, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 190, 441, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 8 );
	//	Roop
	for( HTint i=0 ; i<9 ; i++ )
	{
        g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 0, 66, 5, 77+(39*i) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 10+i, 0, 12, 83+(i*39), 1402, 32, 32 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 10+i, _T("Empty"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 81+(39*i), 173, 19 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 20+i, _T("Off"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 81+(39*i), 64, 19 );
		g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 10+i, 0, 2, 77+(i*39), 202, 0, 1500, 291, 32 );
	}
	//	스크롤 바
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_ADDRESS, 1, 313, 75, 370 );
}

//	입력 메세지 처리
//	Address
void HTAddress::HT_vAddress_InputCheckForAddress(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 )
		{
			g_cAddress->HT_vSetOff();
		}
		//	등록
		else if( iTargetID == 6 )
		{
			if( !g_cAddress->m_bAddress_ReqRegistBtn )
			{
				g_cAddress->m_bAddress_ReqRegistBtn = HT_TRUE;
				// Address 화살표 커서로 변경 
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					g_cInterfaceCheck->HT_vSetCursor(CURSOR_ADDRESS_ANI);
			}
			else
			{
				g_cAddress->m_bAddress_ReqRegistBtn = HT_FALSE;
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
			}
		}
		//	삭제
		else if( iTargetID == 7 )
		{
			if( g_cAddress->m_strAddress_SelectedName.HT_bIsEmpty() )
				return;

			//	멤버삭제 버튼
			g_cAddress->m_bAddress_MemberDeleteBtn = HT_TRUE;
			// %s 님을 주소록에서 삭제하시겠습니까?
			g_cAddress->m_szParamString = g_cAddress->m_strAddress_SelectedName;
			g_cAddress->HT_vAddress_SetMessage( eMsgAddressReqDelQuestion );
			//	Message Box
			g_cAddress->m_bAddress_ReDlgBoxSw = HT_TRUE;
			g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, g_cAddress->m_strAddress_DlgBoxMessage, 1 );
		}
		//	확인
		else if( iTargetID == 8 )
		{
			g_cAddress->HT_vSetOff();
		}
		//	Button 멤버
		else if( iTargetID>=10 && iTargetID<19 )
		{
			g_cAddress->m_strAddress_SelectedName =  g_cUIManager->HT_GetTextLabelControl( _DIALOG_ADDRESS, iTargetID );
			//	귓속말 상태로 만들어 주고..
			g_cChatting->HT_vChatting_SetWisper( g_cAddress->m_strAddress_SelectedName );
		}
	}
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		g_cAddress->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	OK
		if( iTargetID == 2 )
		{
			//	등록버튼이 눌렸을 때
            if( g_cAddress->m_bAddress_ReqRegistBtn == HT_TRUE )
			{
				//	주소록 등록 요청을 상대방에게 보냄
				g_cAddress->HT_vCSP_JoinAddressBook( g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( g_cAddress->m_dwAddress_OtherCharKeyID ) );
				g_cAddress->m_bAddress_ReqRegistBtn = HT_FALSE;
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
			}
			else if( g_cAddress->m_bAddress_ReceiveRegistBtn == HT_TRUE )
			{
				g_cAddress->m_bAddress_ReceiveRegistBtn = HT_FALSE;
				// 등록 대상이 등록 요청에 응답
				g_cAddress->HT_vCSP_JoinAddressBookResult( 0x00 );
			}
			//	멤버삭제 버튼
			else if( g_cAddress->m_bAddress_MemberDeleteBtn == HT_TRUE )
			{
				g_cAddress->m_bAddress_MemberDeleteBtn = HT_FALSE;
				//	멤버 삭제
				g_cAddress->HT_vCSP_DeleteMember( g_cAddress->m_strAddress_SelectedName );
			}
		}
		//	Cancel
		else if( iTargetID == 3 )
		{
			if( g_cAddress->m_bAddress_ReceiveRegistBtn == HT_TRUE )
				g_cAddress->m_bAddress_ReceiveRegistBtn = HT_FALSE;
		}
	}
}

//	Set Contents in Window
HTvoid HTAddress::HT_vAddress_SetContentsInWnd( HTint iScrollValue )
{
	int iStartCount = iScrollValue;	//	스크롤에서 넘어온 값

	//	UI System 에 적용
	CHTString strSaveName[MAX_MESSENGER];
	short snSaveTribe[MAX_MESSENGER];
	HTint iSaveZone[MAX_MESSENGER];
	HTint iSaveSourceIndex[MAX_MESSENGER];

	HTint iTribe;
	HTint iInsertCount = 0;
	HT_COLOR clrKey = HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	CHTString strTemp;
	for( HTint i=0 ; i<MAX_MESSENGER ; ++i )
		strSaveName[i].HT_hrCleanUp();

	//	일단 저장
	for( i=0 ; i<MAX_MESSENGER ; ++i )
	{
		if( m_oAddress_Item[i].Status != 0 )
		{
			//	이름저장
			strTemp = m_oAddress_Item[i].szCharName;
			strSaveName[iInsertCount] = strTemp;
			//	종족코드 보정해서 저장
			HT_ConvertTribeS2C( m_oAddress_Item[i].snTribe, iTribe );
			snSaveTribe[iInsertCount] = iTribe;
			//	존 저장
			iSaveZone[iInsertCount] = m_oAddress_Item[i].Status;
			//	원래 배열정보 저장
			iSaveSourceIndex[iInsertCount] = i;
			//	제일마지막에 카운트를 하나 증가시킴
			iInsertCount++;
		}
	}

	//	UI 초기화
	for( HTint i=0 ; i<9 ; i++ )
	{
		//	종족
		g_cUIManager->HT_SetTextureControlImage( _DIALOG_ADDRESS, 10+i, 0 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ADDRESS, 10+i, HT_FALSE );
		//	이름
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 10+i, _T("") );
		//	접속여부
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 20+i, _T("") );
	}

	//	화면에 뿌려줌
	HTint iConnect;
	iInsertCount = 0;
	for( i=iStartCount ; i<MAX_MESSENGER ; ++i )
	{
		if( strSaveName[i].HT_bIsEmpty() )
		{
			break;
		}
		else
		{
			iConnect = 1;
			if( iSaveZone[i] == 2 )
				iConnect = 0;
			//	종족
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ADDRESS, 10+iInsertCount, g_iTribeImageNumber[iConnect][snSaveTribe[i]-1] );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ADDRESS, 10+iInsertCount, HT_TRUE );
			//	이름
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 10+iInsertCount, strSaveName[i] );
			//	접속여부12
			if( iConnect == 0 )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 20+iInsertCount, _T("ON") );
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ADDRESS, 20+iInsertCount, g_ColorTable[12] );
			}
			else if( iConnect == 1 )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 20+iInsertCount, _T("OFF") );
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ADDRESS, 20+iInsertCount, g_ColorTable[11] );
			}

			iInsertCount++;
			if( iInsertCount == 9 )
				return;
		}
	}
}

//-------------------------------------------------------------------------------
// HTvoid HT_vAddress_Delete()
// D : Unload resources.
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vAddress_Delete()
{
}

//------------------------------------------------------------------------------
// Active / Deactive
//------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSetOn()
{	
	//	선택된 캐릭터
	m_nAddress_SelectedMember = -1;
	m_bActive = HT_TRUE;

	g_cUIManager->HT_ShowWindow( _DIALOG_ADDRESS );
}
HTvoid HTAddress::HT_vSetOff()
{	
	m_bActive = HT_FALSE;
	m_bAddress_ReqRegistBtn = HT_FALSE;

	// 화살표 커서로 변경
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
	{
		if( g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
		else
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}

	g_cUIManager->HT_HideWindow( _DIALOG_ADDRESS );
}

//	ESC Key 누르면 주소창 닫기
HTvoid HTAddress::HT_vAddress_ESC_CloseWindow()
{
	this->HT_vSetOff();
}

HTRESULT HTAddress::HT_hrMouseCheck_OtherChar( HTint nModelID )				//	타 캐릭터 체크
{
    if( m_bAddress_ReqRegistBtn == HT_FALSE )
		return HT_FAIL;

	if( m_bActive == HT_FALSE )
		return HT_FAIL;

	// 커서 변경
	g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

	//	상대방의 키아디를 알아오고
	m_dwAddress_OtherCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nModelID );
	if( m_dwAddress_OtherCharKeyID == 0 )
		return HT_FAIL;

	CHTString strTempName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwAddress_OtherCharKeyID );
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strTempName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			//	이미 주소록에 있는 캐릭터 입니다.
			m_bAddress_ErrorSw = HT_TRUE;
			HT_vAddress_SetMessage( eMsgAddressAlreadyResist );
			g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, m_strAddress_DlgBoxMessage, 0 );
			return HT_FAIL;
		}
	}
	
	//	%s 님께 주소록 등록을 요청하시겠습니까?
	m_szParamString = strTempName;
	HT_vAddress_SetMessage( eMsgAddressReqAddQuestion );
	g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, m_strAddress_DlgBoxMessage, 0 );

	return HT_OK;
}

//-------------------------------------------------------------------------------
// Network functions
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// HTvoid HT_vSCP_InitAddressBook( MSG_UpdateMessengerList info )
// D : 주소록에 등록된 데이타를 받음
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSCP_InitAddressBook( MSG_UpdateMessengerList* info )
{
	memcpy( &m_oAddress_Item, &info->Item, sizeof(STRUCT_MESSENGER_ITEM)*MAX_MESSENGER );
	//	Set Contents in Window
	this->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSCP_UpdateDataAddressBook( PS_SCP_INIT_REAL_ADDRESS_BOOK info )
// D : 주소록의 정보 변경을 처리
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSCP_UpdateDataAddressBook( MSG_UpdateMessengerItem* info )
{
	CHTString strName = info->Item.szCharName;
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( i == info->nSlot )
		{
			memcpy( &m_oAddress_Item[i], &info->Item, sizeof(STRUCT_MESSENGER_ITEM) );
			break;
		}
	}
	//	Set Contents in Window
	this->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
}

//	로그인
HTvoid HTAddress::HT_vSCP_MSG_MessengerLogin( MSG_MessengerLogin* info )
{
	CHTString strName = info->CharName;
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( i == info->nSlot )
		{
			m_oAddress_Item[i].Status = 2;
			break;
		}
	}
	//	Set Contents in Window
	this->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
}
//	로그아웃
HTvoid HTAddress::HT_vSCP_MSG_MessengerLogout( MSG_MessengerLogout* info )
{
	CHTString strName = info->CharName;
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( i == info->nSlot )
		{
			m_oAddress_Item[i].Status = 1;
			break;
		}
	}
	//	Set Contents in Window
	this->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
}


//-------------------------------------------------------------------------------
// HT_vCSP_JoinAddressBook( CHTString pName )
// D : 주소록에 등록을 요청
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_JoinAddressBook( CHTString strName )
{
	//	이미 주소록에 있는 캐릭터인지 조사
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, _T("이미 주소록에 등록되어 있는 분입니다.") );
			HT_vAddress_SetMessage( eMsgAddressAlreadyResist );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_strAddress_DlgBoxMessage );
			return;
		}
	}

	//	슬롯 넘버 조사
	HTint iSlotNo;
	CHTString strTempName;
	for( i=0 ; i<MAX_MESSENGER ; i++ )
	{
		strTempName = m_oAddress_Item[i].szCharName;
		if( strTempName.HT_bIsEmpty() )
		{
			iSlotNo = i;
			break;
		}
	}

	MSG_ReqMessenger* info = HT_NULL;
	info = new MSG_ReqMessenger;
	//	슬롯No
	info->nSlot = iSlotNo;
	//	이름
	CHTString::HT_hrStringCopy( info->Item.szCharName, strName, SZNAME_LENGTH );
	// Send to server
	g_pNetWorkMgr->RequestJoinAddressBook( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_ReqMessenger %s", info->Item.szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//-------------------------------------------------------------------------------
// HT_vSCP_JoinAddressBook( PS_SCP_RESP_JOIN_ADDRESS_BOOK info )
// D : 주소록에 등록을 요청
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSCP_JoinAddressBook( MSG_ReqMessenger* info )
{
	m_strAddress_ReqCharName = info->Item.szCharName;
	m_bAddress_ReceiveRegistBtn = HT_TRUE;
	// %s 님이 주소록 등록을 요청하셨습니다.
	m_szParamString.HT_szFormat( "%s", info->Item.szCharName );
	HT_vAddress_SetMessage( eMsgAddressReqReceive );
	g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, m_strAddress_DlgBoxMessage, 1 );
}

//-------------------------------------------------------------------------------
// HT_vCSP_JoinAddressBookResult()	
// D : 등록 대상이 등록 요청에 응답
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_JoinAddressBookResult( BYTE byResult )
{
	//	슬롯 넘버 조사
	HTint iSlotNo;
	CHTString strTempName;
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( m_oAddress_Item[i].Status == 0 )
		{
			iSlotNo = i;
			break;
		}
	}

	MSG_CNFMessenger* info = HT_NULL;
	info = new MSG_CNFMessenger;
	//	슬롯No
	info->nSlot = iSlotNo;
	//	이름
	CHTString::HT_hrStringCopy( info->CharName, m_strAddress_ReqCharName, SZNAME_LENGTH );
	// Send to server
	g_pNetWorkMgr->RequestJoinAddressBookResult( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_CNFMessenger %s", info->CharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vCSP_DeleteMember( HTtchar *pName )
// D : 멤버를 삭제
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_DeleteMember( CHTString strName )
{
	//	주소록에 있는 캐릭터인지 조사
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			MSG_RemoveMessenger* info = HT_NULL;
			info = new MSG_RemoveMessenger;
			info->nSlot = i;
			// Send to server
			g_pNetWorkMgr->RequestReqAddressBookMemberDelete( info );

			//-----디버깅 테스트를 위하여-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MemberDelete %d", i );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			HT_DELETE( info );
			return;
		}
	}
}

HTvoid HTAddress::HT_vAddress_SetMessage( HTint idMessage )
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
		HT_vAddress_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vAddress_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vAddress_SetParamTextForMessage( sParam3, &szOut3 );

		m_strAddress_DlgBoxMessage.HT_szFormat( szString.HT_szGetString(), 
								szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vAddress_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vAddress_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_strAddress_DlgBoxMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vAddress_SetParamTextForMessage( sParam1, &szOut1 );
		m_strAddress_DlgBoxMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		m_strAddress_DlgBoxMessage = szString;
}

HTvoid HTAddress::HT_vAddress_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		case eMsgParamOthercharName		:
			*pszParam = m_szParamString; break;
		
		default:
			break;
	}
}