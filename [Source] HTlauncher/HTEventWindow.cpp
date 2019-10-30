//======================================================================
// HTEventWindow.cpp
// �̺�Ʈ ���� ��
// �輱��		2004.04.12
//======================================================================

#include "stdafx.h"
#include "HTextern.h"
#include "hteventwindow.h"

CHTEventWindow::CHTEventWindow(void)
{
	//	Today Dete
	m_iTodayDete = 0;
	m_bEventWin_DlgSw = HT_FALSE;
	//	Create Window
	this->HT_vEventWnd_CreateWindow();
}

CHTEventWindow::~CHTEventWindow(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_ATTENDANCECHECK );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WINEVENTWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WINEVENT2WND );
}

//	Create Window
HTvoid CHTEventWindow::HT_vEventWnd_CreateWindow()
{
	struct tm *newtime;
	__time64_t long_time;
	_time64( &long_time );                /* Get time as long integer. */
	newtime = _localtime64( &long_time ); /* Convert to local time. */
	newtime->tm_year += 1900;
	newtime->tm_mon += 1;
	if( newtime->tm_mon == 9 )
	{
		m_iTodayDete = newtime->tm_mday-27;
	}
	else if( newtime->tm_mon == 10 )
	{
		m_iTodayDete = newtime->tm_mday+4;
	}

	if( m_iTodayDete>=0 && m_iTodayDete<=27 )
		g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ATTENDANCECHECK, m_iTodayDete, HT_COLOR( 1.0f, 0, 0, 1.0f ) );
	else
	{
		m_iTodayDete = 1;
		g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ATTENDANCECHECK, m_iTodayDete, HT_COLOR( 1.0f, 0, 0, 1.0f ) );
	}

	//	[_DIALOG_ATTENDANCECHECK]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ATTENDANCECHECK, _T(""), 260, 250, g_pEventWindow->HT_vEventWnd_InputCheckForAttendanceCheck, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ATTENDANCECHECK, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ATTENDANCECHECK, 0, 8, 2, 36, 1400, 254, 6 );
	//	Texture ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_ATTENDANCECHECK, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ATTENDANCECHECK, 0, _T("�⼮üũ"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Slot
	CHTString strTemp;
	HTint iDeteCount = 0;
	for( HTint i=0 ; i<4 ; i++ )
	{
		for( HTint j=0 ; j<7 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_ATTENDANCECHECK, 1+((i*7)+j), 66, 3+(j*36), 53+(i*36), 2000, 35, 35 );
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_ATTENDANCECHECK, 1+((i*7)+j), HT_TRUE );
			if( iDeteCount < 4 )	strTemp.HT_szFormat( "9/%d", 27+iDeteCount );
			else					strTemp.HT_szFormat( "10/%d", iDeteCount-3 );
			g_cUIManager->HT_AddLabelControl( _DIALOG_ATTENDANCECHECK, 1+((i*7)+j), strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3+(j*36), 58+(i*36), 32, 17 );
            iDeteCount++;

			g_cUIManager->HT_SetSlotImage( _DIALOG_ATTENDANCECHECK, 1+((i*7)+j), 22382 );
		}
	}
	//	Button �⼮ üũ
	g_cUIManager->HT_AddButtonControl( _DIALOG_ATTENDANCECHECK, 1, 159, 150, 210, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ATTENDANCECHECK, 1, _T("�⼮üũ"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 150, 210, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ATTENDANCECHECK, 1 );

	//	[_DIALOG_WINEVENTWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WINEVENTWND, _T(""), 400, 300, g_pEventWindow->HT_vEventWnd_InputCheckForWinEvent, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_WINEVENTWND, 5 );
	//	Label
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 1, _T("�� PC �� �̺�Ʈ�� ��ϵǾ����ϴ� ��"), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 30, 400, 19 );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_WINEVENTWND, 2, _T("źƮ��! ���� PC�濡�� ���� ������ ���� ������ϴ�. PC�濡�� ���� �����е鲲 �Ʒ��� ���� ������ �帳�ϴ�"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_WINEVENTWND, 2, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 3, _T("�ϳ�, ����ġ 20%�߰� ���"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 160, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 3, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 4, _T("��, ������ �� ����ġ ��� ����(5% -> 2.5%)"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 180, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 4, 7 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 5, _T("��, ���Ǿ� 20%�߰� ȹ��"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 200, 400, 19 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 5, 7 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_WINEVENTWND, 6, 159, 155, 240, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 6, _T("Ȯ��"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 155, 240, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_WINEVENTWND, 6 );

	//	[_DIALOG_WINEVENT2WND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WINEVENT2WND, _T(""), 400, 300, g_pEventWindow->HT_vEventWnd_InputCheckForWin2Event, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_WINEVENT2WND, 5 );
	//	Label
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 1, _T("�� �Ĺ� �̺�Ʈ�� ��÷�Ǿ����ϴ� ��"), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 30, 400, 19 );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_WINEVENT2WND, 2, _T("�ȳ��ϼ���. źƮ���� ����� ���ƿ��� ���� ȯ���ϸ� �̺�Ʈ �Ⱓ ���� �����Ͻø� �̺�Ʈ �÷�Ƽ�� �ٷ��� �������� �� ���� �帳�ϴ�. ����, ���ٶ� ������ ������!"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_WINEVENT2WND, 2, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 3, _T("�� �Ⱓ : 12�� 6�� ~ 12�� 27��"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 160, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENT2WND, 3, 7 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 4, _T("��, ���� ����(60Lev �̸� ����)"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 180, 400, 19 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENT2WND, 4, 7 );
	//	Button Ȯ��
	//g_cUIManager->HT_AddButtonControl( _DIALOG_WINEVENT2WND, 6, 159, 155, 240, 160, 161, 1500, 89, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 6, _T("Ȯ��"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 155, 240, 89, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_WINEVENT2WND, 6 );

//22382	UI_Event_Cehck01.bmp �⼮
//22383	UI_Event_Cehck02.bmp �Ἦ
//
//[�����] �̺�Ʈ�� 3����... ���� ��:
//' 1|00000001 : �̺�Ʈ1					�ǽù��̺�Ʈ
//' 1|00000010 : �̺�Ʈ2					�⼮üũ(������ 100% ����)
//' 1|00000100 : �̺�Ʈ3					�������̺�Ʈ(������ 100%����)
//' 1|00001000 : �̺�Ʈ4					�ٷ��������̺�Ʈ(�Ĺ��������)
//' 1|00010000 : �̺�Ʈ5					���������̺�Ʈ(�Ĺ��������)
//' 1|00100000 : �̺�Ʈ6					���϶��� �̺�Ʈ ���� �̺�Ʈ -> ÷�� ������ ������
//' 1|01000000 : �̺�Ʈ7					��Ƽ�� ���� �̺�Ʈ -> ��������ó��
//[�����] �̺�Ʈ�� 3����... ���� ��:
//#define		_Msg_GameEvent					0x4501
//struct		Msg_GameEvent
//{	_MSG
//	int	nID;
//	short	snAction;
//	byte	byResult;
//	byte	byDummy;
//	int		iData[4];
//	char	pData[16];
//};
	//	Char �ʱ�ȭ�� ����
	//������ �̺�Ʈ
	//�Ǿ��� �̺�Ʈ
	//�ٷ��������̺�Ʈ

}
//	�Է� �޼��� ó��
//	Event Window
void CHTEventWindow::HT_vEventWnd_InputCheckForAttendanceCheck(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_ATTENDANCECHECK );
		}
		//	�⼮ üũ
		else if( iTargetID == 1 )
		{
			CHTString strResult;
			strResult = g_poWebLogIn->HT_strAttendanceCheck( g_strLoginID, g_strLgoinPasswordMD5.HT_szGetString(), 0 );
			if( strResult.HT_iStringCompare(_T("OK")) == 0 )
			{
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("�⼮ üũ�� ���������� ó���Ǿ����ϴ�.") );
				g_pEventWindow->HT_vEventWindow_ReqAttendance();
			}
			else
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("�⼮ üũ�� ó���� �����߽��ϴ�.") );
		}
	}
}
//	Win Event
void CHTEventWindow::HT_vEventWnd_InputCheckForWinEvent(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 ||
			iTargetID == 6 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_WINEVENTWND );
		}
	}
}
//	Win2 Event
void CHTEventWindow::HT_vEventWnd_InputCheckForWin2Event(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 ||
			iTargetID == 6 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_WINEVENT2WND );
		}
	}
}

//	Network Message
//	Request Attendance
HTvoid CHTEventWindow::HT_vEventWindow_ReqAttendance()
{
	g_cUIManager->HT_ShowWindow( _DIALOG_ATTENDANCECHECK );
	CHTString strResult;
	strResult.HT_hrCleanUp();
	strResult = g_poWebLogIn->HT_strAttendanceCheck( g_strLoginID, g_strLgoinPasswordMD5.HT_szGetString(), 1 );
	//	�����϶�
	//if( strResult.HT_nGetSize() == 28 )
	{
		char szAttendance[28];
		ZeroMemory( szAttendance, 28 );
		strncpy( szAttendance, strResult.HT_szGetString(), strResult.HT_nGetSize() );

		for( HTint i=0 ; i<strResult.HT_nGetSize() ; i++ )
		{
			if( szAttendance[i] == '1' )		g_cUIManager->HT_SetSlotImage( _DIALOG_ATTENDANCECHECK, i+1, 22382 );
			else								g_cUIManager->HT_SetSlotImage( _DIALOG_ATTENDANCECHECK, i+1, 22383 );
		}
	}
}
//	Check Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReqCheckGameEvent( HTdword dwEvent )
{
	g_dwMyEvent = dwEvent;
	HTint iID = 0;
	//	�ǽù� �̺�Ʈ
	if( dwEvent & 0x00000001 )
		iID += 1;
	if( dwEvent & 0x00000002 )
		iID += 2;
	////	���Ӹ� �ص� ���� ��(15~30 : 5���� ��, 31~60���� : 3���� ��)
	//if( dwEvent & 0x00000004 )
	//	iID += 4;
	//	�÷�Ƽ�� �ٷ��� 7���̿�� ���� (ID : 7074)
	//if( dwEvent & 0x00000008 )
	//	iID += 8;
	////	���϶��� �̺�Ʈ ���� �̺�Ʈ -> ÷�� ������ ������
	//if( dwEvent & 0x00000020 )
	//	iID += 32;
	//	Req Game Event
	this->HT_vEventWnd_ReqMsgGameEvent( 1, iID, 0 );

	//	�̺�Ʈ â �ٿ��
	//	PC�� �̺�Ʈ
	if( dwEvent & 0x00000001 &&
		g_oMainCharacterInfo.byLevel < 60 )
	{
		//	PC Room Event Wnd Logo
		if( g_bPCRoomEventWndLogo == HT_FALSE )
		{
			g_bPCRoomEventWndLogo = HT_TRUE;
            g_cUIManager->HT_ShowWindow( _DIALOG_WINEVENTWND );
		}
	}
	//	�ٷ��� & ��������
	if( (dwEvent & 0x00000004) )
	{
       g_cUIManager->HT_ShowWindow( _DIALOG_WINEVENT2WND );
	}


}
//	Check Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReqChangeTribe( HTbyte byTribe )
{
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("�̺�Ʈ�� �������ϴ�.") );
	return;
 //   //	60Level �̻��϶��� ����
	//if( g_cStatus->HT_byGetLevel() > 60 )
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("60���� �̻��϶��� ���������� �� �� �����ϴ�.") );
	//	return;
	//}
	////	�ƹ��͵� �����ϰ� ���� ��������
	//if( HT_SUCCEED( g_cItemSystem->HT_hrItemSystem_CheckEquipItem() ) )
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("������ �������� ������쿡�� ���������� �� �� �����ϴ�.") );
	//	return;
	//}

	//HTbyte byChangeTribe = 1;
	//switch( byTribe )
	//{
	//	case 1 :	byChangeTribe=TRIBE_NAGA;		break;
	//	case 5 :	byChangeTribe=TRIBE_KINNARA;	break;
	//	case 2 :	byChangeTribe=TRIBE_ASURA;		break;
	//	case 6 :	byChangeTribe=TRIBE_RAKSHASA;	break;
	//	case 3 :	byChangeTribe=TRIBE_YAKSA;		break;
	//	case 7 :	byChangeTribe=TRIBE_GANDHARVA;	break;
	//	case 4 :	byChangeTribe=TRIBE_DEVA;		break;
	//	case 8 :	byChangeTribe=TRIBE_GARUDA;		break;
	//	case 9 :	byChangeTribe=0;				break;
	//	default :	byChangeTribe = 1;				break;
	//}
	//this->HT_vEventWnd_ReqMsgGameEvent( 1, 0x00000010, byChangeTribe );
}

//	Request Msg Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReqMsgGameEvent( HTshort snAction, HTint iID, HTchar pData[16])
{
    Msg_GameEvent* info = HT_NULL;
	info = new Msg_GameEvent;
	ZeroMemory( info, sizeof(Msg_GameEvent) );

	info->snAction = snAction;
	info->nID = iID;
	strncpy(info->pData, pData, 16);

	// �޽��� ������ ������ ��û��
	g_pNetWorkMgr->RequestMsgCouponEvent( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_ReqGameEvent : snAction:%d, nID:%d, iData[0]:%d", info->snAction, info->nID, info->iData[0] );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTEventWindow::HT_vEventWnd_ReqMsgGameEvent( HTshort snAction, HTint iID, HTint iData0 )
{
    Msg_GameEvent* info = HT_NULL;
	info = new Msg_GameEvent;
	ZeroMemory( info, sizeof(Msg_GameEvent) );

	info->snAction = snAction;
	info->nID = iID;
	info->iData[0] = iData0;

	// �޽��� ������ ������ ��û��
	g_pNetWorkMgr->RequestMsgCouponEvent( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_ReqGameEvent : snAction:%d, nID:%d, iData[0]:%d", info->snAction, info->nID, info->iData[0] );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	Recive	Msg Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReciveMsgGameEvent( Msg_GameEvent* info )
{
	
	if( info->nID & 0x00000002)	// 2�� �̺�Ʈ �������̰�,
		if( info->byResult & 0x00000002 )	// 2�� �̺�Ʈ ��� �����ÿ��� ���� �޽�����, ���нÿ��� ���� �޽����� �ѷ��ش�.
		{
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "���� �λ������� �޾ҽ��ϴ�. �κ��丮�� Ȯ���غ�����." );
			return;
		}
		else
		{
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�κ��丮 ������ �����Ͽ� ���� �λ������� ���� ���߽��ϴ�. ������ Ȯ���� �Ŀ� �ٽ� �������ֽñ� �ٶ��ϴ�." );
			return;
		}

	/*
		//	�⼮üũ
		if( info->nID & 0x00000002 )
		{
			DWORD dwTempCount = 0x00000000;
			for( HTint i=1 ; i<=m_iTodayDete ; i++ )
			{
				if( info->iData[0] & dwTempCount )		g_cUIManager->HT_SetSlotImage( _DIALOG_ATTENDANCECHECK, i, 22382 );
				else									g_cUIManager->HT_SetSlotImage( _DIALOG_ATTENDANCECHECK, i, 22383 );

				if( dwTempCount == 0x00000000 )		dwTempCount = 0x00000001;
				else								dwTempCount<<1;
			}
		}
		//	ĳ���� ��������
		if( info->nID & 0x00000010 )
		{
			//	�����ڵ� �������ֱ�
			HTint iTribe;
			HT_ConvertTribeS2C( info->iData[0], iTribe );
			g_oMainCharacterInfo.snTribe = iTribe;
			//	Set Change Sex
			g_cMainCharacter->HT_vMainChar_ChangeSexDelCre( g_oMainCharacterInfo.snTribe, g_oMainCharacterInfo.byHeadType, g_oMainCharacterInfo.byFaceType );
		}*/
}

