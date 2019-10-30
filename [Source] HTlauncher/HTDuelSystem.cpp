#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSystem.h"
#include "htduelsystem.h"

HTDuelSystem::HTDuelSystem(void)
{
	m_byDuel_Mode = eChallenge_WAIT;
	m_byDuel_ResponseReason = 0;
	//	자동 응답 기능 셋팅
	m_bDuel_WaitMode = HT_FALSE;
	m_bDuel_AutoOK = HT_FALSE;
	m_dwDuel_WaitTime = timeGetTime();
	m_dwDuel_AutoWaitTime = timeGetTime();
	m_iDuel_DuelCharKeyID = -1;
	m_strDuel_DuelCharName.HT_hrCleanUp();
	m_dwDuel_RequestTime = 0;
}

HTDuelSystem::~HTDuelSystem(void)
{
}

//	Update
HTvoid HTDuelSystem::HT_vDuel_Update()
{
	//	Update Wait Mode Check
	this->HT_vDuel_Update_WaitModeCheck();
	//	Update Remain Time Check
	this->HT_vDuel_Update_RemainTimeCheck();
}
//	Update Wait Mode Check
HTvoid HTDuelSystem::HT_vDuel_Update_WaitModeCheck()
{
	if( m_bDuel_WaitMode == HT_TRUE &&
		g_bOneTimeUpdate != GAMESEQUNCE_MAINGAME_GMAEPLAY )
		return;

	if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )
		return;

	// NPC와 대화중이거나 다른 사람과 trade 중 또는 개인 상점 열기/구입 일 경우이면 Skip
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) || 
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) )
		return;

	HTdword dwPassTime = timeGetTime();
	if( dwPassTime > m_dwDuel_WaitTime + 180000 )
	{
		HT_vSet_EmptyPlace();
	}
}

// 자리비움 모드 가동
HTvoid HTDuelSystem::HT_vSet_EmptyPlace()
{
	m_bDuel_WaitMode = HT_TRUE;

	// 캐릭터 앉히기
	if( g_cMainCharacter->HT_bMainChar_GetSitDownState() != HT_TRUE )
		g_cMainCharacter->HT_vMainChar_SetSit();
}

//	Update Remain Time Check
HTvoid HTDuelSystem::HT_vDuel_Update_RemainTimeCheck()
{
	// NPC와 대화중이거나 다른 사람과 trade 중 또는 개인 상점 열기/구입 일 경우이면 Skip
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
		return;

	//	자동 응답 체크
	if( m_byDuel_Mode == eChallenge_Response )
	{
		//	결투 요청에 따른 자종 응답 기능
		HTdword dwPassTime = timeGetTime();
		if( dwPassTime > m_dwDuel_AutoWaitTime + 60000 )
		{
			m_byDuel_ResponseReason = eChallenge_Accept;
			this->HT_vDuelNet_CSP_Challenger();

			//	5분후에 결투상태를 종료하기 위해서
			m_dwDuel_AutoWaitTime = timeGetTime();
		}
	}
	//	5분후 결투 종료 체크
	else if( m_byDuel_Mode == eChallenge_Combat )
	{
		HTdword dwPassTime = timeGetTime();
		if( dwPassTime > m_dwDuel_AutoWaitTime + 300000 )
		{
			m_byDuel_Mode = eChallenge_Response;
			m_byDuel_ResponseReason = eChallenge_End;
			this->HT_vDuelNet_CSP_Challenger();
		}
	}
}

//	Dlg Check For ReConfirm
HTvoid HTDuelSystem::HT_vDuel_LButtonCheckForReConfirm( HTint iProp, HTint iButtonNo )
{
	//	Button
	{
		if( iButtonNo == _BTN_MSG_OK )
		{
			m_byDuel_ResponseReason = eChallenge_Accept;
			this->HT_vDuelNet_CSP_Challenger();
		}
		else if( iButtonNo == _BTN_MSG_CANCEL )
		{
			m_byDuel_ResponseReason = eChallenge_Denay;
			this->HT_vDuelNet_CSP_Challenger();
		}
	}
}

//	Pick Check From OtherObject
HTRESULT HTDuelSystem::HT_hrDuel_PickCheckFromOtherObject( HTint iObjectID )
{
	if( m_byDuel_Mode == eChallenge_Request )
	{
		//	안전지역이면 리턴
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
			return HT_OK;

		CHTString strDuelCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromModelID( iObjectID );
		//	파티 멤버라면 스킵
		if( g_cParty->HT_bParty_IsPartyMember( strDuelCharName.HT_szGetString() ) == HT_TRUE )
			return HT_OK;

		//	만약 이전에 요청했던 녀석이라면 시간경과를 따져서 일정시간 이전에 요청했으면 스킵힌다.
		if( strDuelCharName.HT_iStringCompare( m_strDuel_DuelCharName.HT_szGetString() ) == 0 )
		{
			DWORD dwPassTime = timeGetTime();
			if( dwPassTime <= m_dwDuel_RequestTime+180000 )
			{
				//	Get message and set
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonDuelLimitPerson, &strString, _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				m_byDuel_Mode = eChallenge_WAIT;
				return HT_OK;
			}
		}
/*
		//	루피아 10000 이하면 스킵
		if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() > 10000 )
		{*/
			m_iDuel_SendCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( iObjectID );
			m_strDuel_SendCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_iDuel_SendCharKeyID);
			m_byDuel_ResponseReason = 0;
            this->HT_vDuelNet_CSP_Challenger();
			m_strDuel_DuelCharName = strDuelCharName;
			m_dwDuel_RequestTime = timeGetTime();

			//	Get message and set
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonDuelAutoOK, &strString, m_strDuel_SendCharName.HT_szGetString() );
			g_cUIStatus->m_MessageBoxType = 0;
			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strString , 0);
//		}
//		else
//		{
//			//	Get message and set
//			CHTString strString;
//			HT_g_Script_SetMessage( eMsgCommonDuelMoreRhupia, &strString, _T("") );
//			g_cUIStatus->m_MessageBoxType = 0;
//			g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strString , 0);
//		}

		//	아이콘 한번 클릭하고 이닛되게 처리
		//m_byDuel_Mode = eChallenge_WAIT;

		return HT_OK;
	}

	return HT_FAIL;
}

//	Set
//	Set Init
HTvoid HTDuelSystem::HT_vDuel_SetInit()
{
}
//	Set Duel Mode
HTvoid HTDuelSystem::HT_vDuel_SetDuelMode()
{
	if( m_byDuel_Mode == eChallenge_WAIT )
	{
		m_byDuel_Mode = eChallenge_Request;
		g_cInterfaceCheck->HT_vSetCursor(CURSOR_SELECT_ANI);
	}
	else
		m_byDuel_Mode = eChallenge_WAIT;
}
//	Set Wait Mode Cancel From KeyInput
HTvoid HTDuelSystem::HT_vDuel_SetWaitModeCancelFromKeyInput()
{
	m_bDuel_WaitMode = HT_FALSE;
	m_dwDuel_WaitTime = timeGetTime();
	//	자동 응답 기능 셋팅
	m_bDuel_AutoOK = HT_TRUE;
}

//	Net
//	Request Challenger
HTvoid HTDuelSystem::HT_vDuelNet_CSP_Challenger()
{
	Msg_Challenger* info = HT_NULL;
	info = new Msg_Challenger;

	info->nID = m_iDuel_SendCharKeyID ;
	strncpy( info->szCharName, m_strDuel_SendCharName.HT_szGetString(), SZNAME_LENGTH );
	info->byMode = m_byDuel_Mode;
	info->byReason = m_byDuel_ResponseReason;
	g_pNetWorkMgr->RequestMsgChallenger( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqChallenger : %s", info->szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Recive Challenger
HTvoid HTDuelSystem::HT_vDuelNet_SCP_Challenger( Msg_Challenger* info )
{
	//	결투 상태라는 아이콘을 붙임
	if( info->byMode == eChallenge_Combat )
        g_pMainBar->HT_vMainBar_SetMySkill( 23021, 3, 0 );
	else
		g_pMainBar->HT_vMainBar_MySkillSetDelete( 23021 );

	if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_FALSE )
	{
		m_byDuel_Mode = info->byMode;
		return;
	}
	else
	{
		g_cUIManager->HT_HideWindow( _DIALOG_BACKGROUND );

		if( info->byMode == eChallenge_Request )
		{
			//	나의 입장에 봐야 하기때문에 메시지를 받았기때문에 보내기 모드로 변경
			m_byDuel_Mode = eChallenge_Response;
			m_iDuel_SendCharKeyID = info->nID;
			m_strDuel_SendCharName = info->szCharName;

			// NPC와 대화중이거나 다른 사람과 trade 중 또는 개인 상점 열기/구입 일 경우이면 아이템교환 요청 거절
			if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) || 
				g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) || 
				g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) || 
				g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
			{
				m_byDuel_ResponseReason = eChallenge_Denay;
				this->HT_vDuelNet_CSP_Challenger();
			}

			//	안전지역에서는 스킬 시전 못한다.
			HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
			if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
				return;

			//	대기 모드인지를 판단하여 대기모드면 바로 취소를 날려줌
			if( m_bDuel_WaitMode == HT_TRUE )
			{
				m_byDuel_ResponseReason = eChallenge_Rest;
				this->HT_vDuelNet_CSP_Challenger();
			}
			else
			{
				//	자동 응답 기능 셋팅
				m_dwDuel_AutoWaitTime = 0;
				m_dwDuel_WaitTime = timeGetTime();
				m_bDuel_AutoOK = HT_FALSE;
				m_dwDuel_AutoWaitTime = timeGetTime();

				//	Get message and set
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonDuelRequest, &strString, info->szCharName );

				g_cUIStatus->m_MessageBoxType = 8;
				g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strString , 1);
				
				// 오토 메크로를 막기 위한 다이알로그 출력 위치 무작위 변경 (범위 +-5)
				HTint ax, ay;
				ax = rand() % 10;
				ay = rand() % 10;
				g_cUIManager->HT_MoveWindow(_DIALOG_BACKGROUND, ax-5, ay-5);
			}
		}
		else if( info->byMode == eChallenge_Response )
		{
			m_byDuel_Mode = eChallenge_WAIT;
			CHTString strString;
			if( info->byReason == eChallenge_Denay )
			{
				//	Get message and set
				HT_g_Script_SetMessage( eMsgCommonDuelCancel, &strString, info->szCharName );
				g_cUIStatus->m_MessageBoxType = 0;
				g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strString , 0);
			}
			else if( info->byReason == eChallenge_Rest )
			{
				//	Get message and set
				HT_g_Script_SetMessage( eMsgCommonDuelNorReqEmpty, &strString, info->szCharName );
				g_cUIStatus->m_MessageBoxType = 0;
				g_cUIManager->HT_MessageBox(_DIALOG_BACKGROUND , strString , 0);
			}
			else if( info->byReason == eChallenge_System )
			{
				//	Get message and set
				HT_g_Script_SetMessage( eMsgCommonDuelCancel, &strString, _T("") );

				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString.HT_szGetString() );
			}
		}
		else if( info->byMode == eChallenge_Combat )
		{
			m_byDuel_Mode = eChallenge_Combat;
			//	5분후에 결투상태를 종료하기 위해서
			m_dwDuel_AutoWaitTime = timeGetTime();
			//	싸우는 상대의 KeyID
			m_iDuel_DuelCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyIDFromName( info->szCharName );
			//	Setting	Targetting
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting( m_iDuel_DuelCharKeyID );
		}
	}
}

