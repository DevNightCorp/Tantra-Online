//======================================================================
// HTEventWindow.cpp
// 이벤트 내용 등
// 김선미		2004.04.12
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_ATTENDANCECHECK, 0, 8, 2, 36, 1400, 254, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_ATTENDANCECHECK, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ATTENDANCECHECK, 0, _T("출석체크"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
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
	//	Button 출석 체크
	g_cUIManager->HT_AddButtonControl( _DIALOG_ATTENDANCECHECK, 1, 159, 150, 210, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ATTENDANCECHECK, 1, _T("출석체크"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 150, 210, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ATTENDANCECHECK, 1 );

	//	[_DIALOG_WINEVENTWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WINEVENTWND, _T(""), 400, 300, g_pEventWindow->HT_vEventWnd_InputCheckForWinEvent, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_WINEVENTWND, 5 );
	//	Label
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 1, _T("◐ PC 방 이벤트에 등록되었습니다 ◑"), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 30, 400, 19 );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_WINEVENTWND, 2, _T("탄트라! 이제 PC방에서 즐기면 혜택이 마구 쏟아집니다. PC방에서 즐기는 유저분들께 아래와 같은 혜택을 드립니다"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_WINEVENTWND, 2, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 3, _T("하나, 경험치 20%추가 상승"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 160, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 3, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 4, _T("둘, 누웠을 때 경험치 상실 감소(5% -> 2.5%)"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 180, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 4, 7 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 5, _T("셋, 루피아 20%추가 획득"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 200, 400, 19 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENTWND, 5, 7 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_WINEVENTWND, 6, 159, 155, 240, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENTWND, 6, _T("확인"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 155, 240, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_WINEVENTWND, 6 );

	//	[_DIALOG_WINEVENT2WND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WINEVENT2WND, _T(""), 400, 300, g_pEventWindow->HT_vEventWnd_InputCheckForWin2Event, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_WINEVENT2WND, 5 );
	//	Label
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 1, _T("◐ 컴백 이벤트에 당첨되었습니다 ◑"), 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 30, 400, 19 );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_WINEVENT2WND, 2, _T("안녕하세요. 탄트라의 세계로 돌아오신 것을 환영하며 이벤트 기간 동안 접속하시면 이벤트 플래티넘 꾸러미 아이템을 한 개씩 드립니다. 지금, 만다라 마을로 가세요!"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 70, 380, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_WINEVENT2WND, 2, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 3, _T("※ 기간 : 12월 6일 ~ 12월 27일"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 160, 400, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENT2WND, 3, 7 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 4, _T("둘, 종족 변경(60Lev 미만 유저)"), 0, HT_COLOR(0.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 180, 400, 19 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_WINEVENT2WND, 4, 7 );
	//	Button 확인
	//g_cUIManager->HT_AddButtonControl( _DIALOG_WINEVENT2WND, 6, 159, 155, 240, 160, 161, 1500, 89, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_WINEVENT2WND, 6, _T("확인"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 155, 240, 89, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_WINEVENT2WND, 6 );

//22382	UI_Event_Cehck01.bmp 출석
//22383	UI_Event_Cehck02.bmp 결석
//
//[윤우경] 이벤트가 3개넹... 님의 말:
//' 1|00000001 : 이벤트1					피시방이벤트
//' 1|00000010 : 이벤트2					출석체크(무조건 100% 설정)
//' 1|00000100 : 이벤트3					레벨업이벤트(무조건 100%설정)
//' 1|00001000 : 이벤트4					꾸러미지급이벤트(컴백유저대상)
//' 1|00010000 : 이벤트5					종족변경이벤트(컴백유저대상)
//' 1|00100000 : 이벤트6					마하라자 이벤트 지금 이벤트 -> 첨에 무조건 보내기
//' 1|01000000 : 이벤트7					겜티즌 쿠폰 이벤트 -> 종족변경처럼
//[윤우경] 이벤트가 3개넹... 님의 말:
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
	//	Char 초기화때 쏴줌
	//레벨업 이벤트
	//피씨방 이벤트
	//꾸러미지급이벤트

}
//	입력 메세지 처리
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
		//	출석 체크
		else if( iTargetID == 1 )
		{
			CHTString strResult;
			strResult = g_poWebLogIn->HT_strAttendanceCheck( g_strLoginID, g_strLgoinPasswordMD5.HT_szGetString(), 0 );
			if( strResult.HT_iStringCompare(_T("OK")) == 0 )
			{
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("출석 체크가 정상적으로 처리되었습니다.") );
				g_pEventWindow->HT_vEventWindow_ReqAttendance();
			}
			else
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("출석 체크의 처리가 실패했습니다.") );
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
	//	성공일때
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
	//	피시방 이벤트
	if( dwEvent & 0x00000001 )
		iID += 1;
	if( dwEvent & 0x00000002 )
		iID += 2;
	////	접속만 해도 레벨 업(15~30 : 5레벨 업, 31~60레벨 : 3레벨 업)
	//if( dwEvent & 0x00000004 )
	//	iID += 4;
	//	플래티넘 꾸러미 7일이용권 증정 (ID : 7074)
	//if( dwEvent & 0x00000008 )
	//	iID += 8;
	////	마하라자 이벤트 지금 이벤트 -> 첨에 무조건 보내기
	//if( dwEvent & 0x00000020 )
	//	iID += 32;
	//	Req Game Event
	this->HT_vEventWnd_ReqMsgGameEvent( 1, iID, 0 );

	//	이벤트 창 뛰우기
	//	PC방 이벤트
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
	//	꾸러미 & 종족변경
	if( (dwEvent & 0x00000004) )
	{
       g_cUIManager->HT_ShowWindow( _DIALOG_WINEVENT2WND );
	}


}
//	Check Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReqChangeTribe( HTbyte byTribe )
{
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("이벤트가 끝났습니다.") );
	return;
 //   //	60Level 이상일때만 가능
	//if( g_cStatus->HT_byGetLevel() > 60 )
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("60레벨 이상일때는 종족변경을 할 수 없습니다.") );
	//	return;
	//}
	////	아무것도 장착하고 있지 않을때만
	//if( HT_SUCCEED( g_cItemSystem->HT_hrItemSystem_CheckEquipItem() ) )
	//{
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("장착된 아이템이 있을경우에는 종족변경을 할 수 없습니다.") );
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

	// 메시지 전송을 서버에 요청함
	g_pNetWorkMgr->RequestMsgCouponEvent( info );

	//-----디버깅 테스트를 위하여-----//
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

	// 메시지 전송을 서버에 요청함
	g_pNetWorkMgr->RequestMsgCouponEvent( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_ReqGameEvent : snAction:%d, nID:%d, iData[0]:%d", info->snAction, info->nID, info->iData[0] );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	Recive	Msg Game Event
HTvoid CHTEventWindow::HT_vEventWnd_ReciveMsgGameEvent( Msg_GameEvent* info )
{
	
	if( info->nID & 0x00000002)	// 2번 이벤트 수행중이고,
		if( info->byResult & 0x00000002 )	// 2번 이벤트 결과 성공시에는 성공 메시지를, 실패시에는 실패 메시지를 뿌려준다.
		{
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "새해 인사편지를 받았습니다. 인벤토리를 확인해보세요." );
			return;
		}
		else
		{
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "인벤토리 공간이 부족하여 새해 인사편지를 받지 못했습니다. 공간을 확보한 후에 다시 접속해주시기 바랍니다." );
			return;
		}

	/*
		//	출석체크
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
		//	캐릭터 종족변경
		if( info->nID & 0x00000010 )
		{
			//	종족코드 보정해주기
			HTint iTribe;
			HT_ConvertTribeS2C( info->iData[0], iTribe );
			g_oMainCharacterInfo.snTribe = iTribe;
			//	Set Change Sex
			g_cMainCharacter->HT_vMainChar_ChangeSexDelCre( g_oMainCharacterInfo.snTribe, g_oMainCharacterInfo.byHeadType, g_oMainCharacterInfo.byFaceType );
		}*/
}

