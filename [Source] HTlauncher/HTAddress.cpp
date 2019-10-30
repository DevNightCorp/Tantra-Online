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

//	���� �̹��� �ѹ�
HTint	g_iTribeImageNumber[2][8] = { 23642,23644,23646,23648,23650,23652,23654,23656,
									  23643,23645,23647,23649,23651,23653,23655,23657 };

//	���� �̹��� �ѹ�
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
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button �ּҷ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ADDRESS, 0, 9, 40, 31, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressAddress, &strMessage, _T(""), _T("") );	//	�ּҷ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 1 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 2, 9, 5, 56, 0, 0, 1500, 62, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressTribe, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 56, 62, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 2 );
	//	Button �̸�
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 3, 9, 70, 56, 0, 0, 1500, 173, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressName, &strMessage, _T(""), _T("") );	//	�̸�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 56, 173, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 3 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 4, 9, 246, 56, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressConnect, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 246, 56, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 4 );
	////	Button ��� ��û ����
	//g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 5, 9, 20, 420, 0, 0, 1500, 90, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 5, _T("��� ��û ����"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 420, 90, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 5 );
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 6, 159, 20, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonRegist, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 441, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 6 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 7, 159, 98, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonDelete, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ADDRESS, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 98, 441, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ADDRESS, 7 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_ADDRESS, 8, 159, 190, 441, 160, 161, 1500, 72, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
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
	//	��ũ�� ��
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_ADDRESS, 1, 313, 75, 370 );
}

//	�Է� �޼��� ó��
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
		//	���
		else if( iTargetID == 6 )
		{
			if( !g_cAddress->m_bAddress_ReqRegistBtn )
			{
				g_cAddress->m_bAddress_ReqRegistBtn = HT_TRUE;
				// Address ȭ��ǥ Ŀ���� ���� 
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					g_cInterfaceCheck->HT_vSetCursor(CURSOR_ADDRESS_ANI);
			}
			else
			{
				g_cAddress->m_bAddress_ReqRegistBtn = HT_FALSE;
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
			}
		}
		//	����
		else if( iTargetID == 7 )
		{
			if( g_cAddress->m_strAddress_SelectedName.HT_bIsEmpty() )
				return;

			//	������� ��ư
			g_cAddress->m_bAddress_MemberDeleteBtn = HT_TRUE;
			// %s ���� �ּҷϿ��� �����Ͻðڽ��ϱ�?
			g_cAddress->m_szParamString = g_cAddress->m_strAddress_SelectedName;
			g_cAddress->HT_vAddress_SetMessage( eMsgAddressReqDelQuestion );
			//	Message Box
			g_cAddress->m_bAddress_ReDlgBoxSw = HT_TRUE;
			g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, g_cAddress->m_strAddress_DlgBoxMessage, 1 );
		}
		//	Ȯ��
		else if( iTargetID == 8 )
		{
			g_cAddress->HT_vSetOff();
		}
		//	Button ���
		else if( iTargetID>=10 && iTargetID<19 )
		{
			g_cAddress->m_strAddress_SelectedName =  g_cUIManager->HT_GetTextLabelControl( _DIALOG_ADDRESS, iTargetID );
			//	�ӼӸ� ���·� ����� �ְ�..
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
			//	��Ϲ�ư�� ������ ��
            if( g_cAddress->m_bAddress_ReqRegistBtn == HT_TRUE )
			{
				//	�ּҷ� ��� ��û�� ���濡�� ����
				g_cAddress->HT_vCSP_JoinAddressBook( g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( g_cAddress->m_dwAddress_OtherCharKeyID ) );
				g_cAddress->m_bAddress_ReqRegistBtn = HT_FALSE;
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
			}
			else if( g_cAddress->m_bAddress_ReceiveRegistBtn == HT_TRUE )
			{
				g_cAddress->m_bAddress_ReceiveRegistBtn = HT_FALSE;
				// ��� ����� ��� ��û�� ����
				g_cAddress->HT_vCSP_JoinAddressBookResult( 0x00 );
			}
			//	������� ��ư
			else if( g_cAddress->m_bAddress_MemberDeleteBtn == HT_TRUE )
			{
				g_cAddress->m_bAddress_MemberDeleteBtn = HT_FALSE;
				//	��� ����
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
	int iStartCount = iScrollValue;	//	��ũ�ѿ��� �Ѿ�� ��

	//	UI System �� ����
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

	//	�ϴ� ����
	for( i=0 ; i<MAX_MESSENGER ; ++i )
	{
		if( m_oAddress_Item[i].Status != 0 )
		{
			//	�̸�����
			strTemp = m_oAddress_Item[i].szCharName;
			strSaveName[iInsertCount] = strTemp;
			//	�����ڵ� �����ؼ� ����
			HT_ConvertTribeS2C( m_oAddress_Item[i].snTribe, iTribe );
			snSaveTribe[iInsertCount] = iTribe;
			//	�� ����
			iSaveZone[iInsertCount] = m_oAddress_Item[i].Status;
			//	���� �迭���� ����
			iSaveSourceIndex[iInsertCount] = i;
			//	���ϸ������� ī��Ʈ�� �ϳ� ������Ŵ
			iInsertCount++;
		}
	}

	//	UI �ʱ�ȭ
	for( HTint i=0 ; i<9 ; i++ )
	{
		//	����
		g_cUIManager->HT_SetTextureControlImage( _DIALOG_ADDRESS, 10+i, 0 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ADDRESS, 10+i, HT_FALSE );
		//	�̸�
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 10+i, _T("") );
		//	���ӿ���
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 20+i, _T("") );
	}

	//	ȭ�鿡 �ѷ���
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
			//	����
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ADDRESS, 10+iInsertCount, g_iTribeImageNumber[iConnect][snSaveTribe[i]-1] );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ADDRESS, 10+iInsertCount, HT_TRUE );
			//	�̸�
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ADDRESS, 10+iInsertCount, strSaveName[i] );
			//	���ӿ���12
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
	//	���õ� ĳ����
	m_nAddress_SelectedMember = -1;
	m_bActive = HT_TRUE;

	g_cUIManager->HT_ShowWindow( _DIALOG_ADDRESS );
}
HTvoid HTAddress::HT_vSetOff()
{	
	m_bActive = HT_FALSE;
	m_bAddress_ReqRegistBtn = HT_FALSE;

	// ȭ��ǥ Ŀ���� ����
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
	{
		if( g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
		else
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}

	g_cUIManager->HT_HideWindow( _DIALOG_ADDRESS );
}

//	ESC Key ������ �ּ�â �ݱ�
HTvoid HTAddress::HT_vAddress_ESC_CloseWindow()
{
	this->HT_vSetOff();
}

HTRESULT HTAddress::HT_hrMouseCheck_OtherChar( HTint nModelID )				//	Ÿ ĳ���� üũ
{
    if( m_bAddress_ReqRegistBtn == HT_FALSE )
		return HT_FAIL;

	if( m_bActive == HT_FALSE )
		return HT_FAIL;

	// Ŀ�� ����
	g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

	//	������ Ű�Ƶ� �˾ƿ���
	m_dwAddress_OtherCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nModelID );
	if( m_dwAddress_OtherCharKeyID == 0 )
		return HT_FAIL;

	CHTString strTempName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwAddress_OtherCharKeyID );
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strTempName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			//	�̹� �ּҷϿ� �ִ� ĳ���� �Դϴ�.
			m_bAddress_ErrorSw = HT_TRUE;
			HT_vAddress_SetMessage( eMsgAddressAlreadyResist );
			g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, m_strAddress_DlgBoxMessage, 0 );
			return HT_FAIL;
		}
	}
	
	//	%s �Բ� �ּҷ� ����� ��û�Ͻðڽ��ϱ�?
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
// D : �ּҷϿ� ��ϵ� ����Ÿ�� ����
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSCP_InitAddressBook( MSG_UpdateMessengerList* info )
{
	memcpy( &m_oAddress_Item, &info->Item, sizeof(STRUCT_MESSENGER_ITEM)*MAX_MESSENGER );
	//	Set Contents in Window
	this->HT_vAddress_SetContentsInWnd( g_cUIManager->HT_GetScrollBarValue( _DIALOG_ADDRESS, 1 ) );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vSCP_UpdateDataAddressBook( PS_SCP_INIT_REAL_ADDRESS_BOOK info )
// D : �ּҷ��� ���� ������ ó��
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

//	�α���
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
//	�α׾ƿ�
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
// D : �ּҷϿ� ����� ��û
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_JoinAddressBook( CHTString strName )
{
	//	�̹� �ּҷϿ� �ִ� ĳ�������� ����
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, _T("�̹� �ּҷϿ� ��ϵǾ� �ִ� ���Դϴ�.") );
			HT_vAddress_SetMessage( eMsgAddressAlreadyResist );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_strAddress_DlgBoxMessage );
			return;
		}
	}

	//	���� �ѹ� ����
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
	//	����No
	info->nSlot = iSlotNo;
	//	�̸�
	CHTString::HT_hrStringCopy( info->Item.szCharName, strName, SZNAME_LENGTH );
	// Send to server
	g_pNetWorkMgr->RequestJoinAddressBook( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_ReqMessenger %s", info->Item.szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//-------------------------------------------------------------------------------
// HT_vSCP_JoinAddressBook( PS_SCP_RESP_JOIN_ADDRESS_BOOK info )
// D : �ּҷϿ� ����� ��û
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vSCP_JoinAddressBook( MSG_ReqMessenger* info )
{
	m_strAddress_ReqCharName = info->Item.szCharName;
	m_bAddress_ReceiveRegistBtn = HT_TRUE;
	// %s ���� �ּҷ� ����� ��û�ϼ̽��ϴ�.
	m_szParamString.HT_szFormat( "%s", info->Item.szCharName );
	HT_vAddress_SetMessage( eMsgAddressReqReceive );
	g_cUIManager->HT_MessageBox( _DIALOG_ADDRESS, m_strAddress_DlgBoxMessage, 1 );
}

//-------------------------------------------------------------------------------
// HT_vCSP_JoinAddressBookResult()	
// D : ��� ����� ��� ��û�� ����
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_JoinAddressBookResult( BYTE byResult )
{
	//	���� �ѹ� ����
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
	//	����No
	info->nSlot = iSlotNo;
	//	�̸�
	CHTString::HT_hrStringCopy( info->CharName, m_strAddress_ReqCharName, SZNAME_LENGTH );
	// Send to server
	g_pNetWorkMgr->RequestJoinAddressBookResult( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_CNFMessenger %s", info->CharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//-------------------------------------------------------------------------------
// HTvoid HT_vCSP_DeleteMember( HTtchar *pName )
// D : ����� ����
//-------------------------------------------------------------------------------
HTvoid HTAddress::HT_vCSP_DeleteMember( CHTString strName )
{
	//	�ּҷϿ� �ִ� ĳ�������� ����
	for( HTint i=0 ; i<MAX_MESSENGER ; i++ )
	{
		if( strName.HT_iStringCompare(m_oAddress_Item[i].szCharName) == 0 )
		{
			MSG_RemoveMessenger* info = HT_NULL;
			info = new MSG_RemoveMessenger;
			info->nSlot = i;
			// Send to server
			g_pNetWorkMgr->RequestReqAddressBookMemberDelete( info );

			//-----����� �׽�Ʈ�� ���Ͽ�-----//
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
	
	// ������ 3�� �� ��
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
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vAddress_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vAddress_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_strAddress_DlgBoxMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
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