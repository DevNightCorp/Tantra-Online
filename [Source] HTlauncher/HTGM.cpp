#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htgm.h"

HTGM::HTGM(void)
{
	m_strNearCharName.HT_hrCleanUp();
	m_bGMCommandWnd = HT_FALSE;
	m_bDlgBoxSw = HT_FALSE;
	m_bReDlgBoxSw = HT_FALSE;
}

HTGM::~HTGM(void)
{
}

//	GM 초기화
HTvoid HTGM::HT_vGM_Init()
{
}

HTvoid HTGM::HT_vGM_ActionOn()
{
	m_bGMCommandWnd = HT_TRUE;
}

HTvoid HTGM::HT_vGM_ActionOff()
{
	m_bGMCommandWnd = HT_FALSE;
}

//	GM_확인 창만 체크
HTRESULT HTGM::HT_vGM_DlgBox_Check()
{
	if( m_bDlgBoxSw == HT_FALSE )
		return HT_FAIL;
	
	return HT_OK;
}

//	GM_확인 / 취소 다 체크마우스 클릭시 체크
HTRESULT HTGM::HT_vGM_ReDlgBox_Check()
{
	if( m_bReDlgBoxSw == HT_FALSE )
		return HT_FAIL;

	return HT_OK;
}

//	반환값들
CHTString HTGM::HT_strGM_GetNearCharName()
{
	return m_strNearCharName;
}

//			0x25 Group(GM)	212
//			네트워크 함수
//---------- GM의 투명모드를 설정 또는 해제를 요청한다-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMode( CHTString strMessage, HTbyte byGMMode )
{
	MSG_GMMode* info = HT_NULL;
	info = new MSG_GMMode;
	
	if( byGMMode == 0x02 )
	{
		if( g_oMainCharacterInfo.byGMStatus & 0x02 )	// 현재 투명인 경우 -> 투명을 푸는 요청을
			info->byGMMode = 0x02;	//g_oMainCharacterInfo.byGMStatus & 0xfd;
		else											// 현재 투명이 아닌 경우 -> 투명을 하는 요청을 
			info->byGMMode = 0x82;	//g_oMainCharacterInfo.byGMStatus | 0x02;

		//	이름 추출
		CHTString::HT_hrStringCopy( info->szCharName, strMessage.HT_szGetString(), SZNAME_LENGTH );
	}
	// GM 이 특정 캐릭터의 채팅을 블럭하는 경우
	else if( byGMMode == 0x04 )
	{
		//	이름 추출
		HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
		int iGMMode = 0;
		CHTString::HT_hrStringCopy( tokenMsg, strMessage.HT_szGetString(), MAX_CHAT_LENGTH );
		sscanf( tokenMsg, "/chatblock %s %d", info->szCharName, &iGMMode );

		if( iGMMode == 0 )	// Chat Block 해제
            info->byGMMode = 0x04;
		else				// Chat Block 실행
			info->byGMMode = 0x84;
	}

	g_pNetWorkMgr->RequestGMMode( info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMode : %s, %d", info->szCharName, info->byGMMode );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_GMMode( MSG_GMMode* info )
{
	CHTString szMessage;
	if( info->byResult == 0 )
	{
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, _T("요청하신 명령을 성공하였습니다.") );
	}
	else if( info->byResult == 1 )
	{
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, _T("요청하신 명령을 실패하였습니다.") );
	}
}
//---------- 특정위치로의 워프를 요청한다.(동일존내)-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMOVE_POSITION( CHTString strInfo )
{
	// 캐릭터의 이름을 분리해 내기(sscanf) 위한 토큰 구성
	CHTString szMessage, szToken;
	if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCommandWarp, &szMessage ) == false )
		return;
	szToken = szMessage + _T(" %d, %d") ;

	// 메시지의 최대 길이와 ID의 최대 길이가 있다면 추가 할 것.
	char tokenMsg[MAX_CHAT_LENGTH] = "\0";
	HTint nX, nZ;
	CHTString::HT_hrStringCopy( tokenMsg, strInfo, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/워프 %d, %d", &nX, &nZ );
	sscanf( tokenMsg, szToken.HT_szGetString(), &nX, &nZ );

	MSG_GMMovePosition* info = HT_NULL;
	info = new MSG_GMMovePosition;

	info->snX = nX;
	info->snZ = nZ;

	if( info->snX>0 && info->snX<1024 &&
		info->snZ>0 && info->snZ<1024 )
	{
		g_pNetWorkMgr->RequestGMMovePosition( info );
		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMovePositon: x:%d, z:%d", info->snX, info->snZ );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	else
	{
		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("셀범위가 벗어났습니다" );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}

	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_GMMOVE_POSITION( MSG_GMMovePosition* info )
{
	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	if( pPt.x != info->snX || pPt.y != info->snZ )
	{
		g_cMainCharacter->HT_vMainChar_SetCharacterPosition( info->snX, info->snZ, 0 );
	}
}
//---------- 특정케릭터 근처로의 워프를 요청한다-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( CHTString strInfo )
{
	// 캐릭터의 이름을 분리해 내기(sscanf) 위한 토큰 구성
	CHTString szMessage, szToken;
	if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCommandMove, &szMessage ) == false )
		return;
	szToken = szMessage + _T(" %s");

	char chName[SZNAME_LENGTH];
	// 메시지의 최대 길이와 ID의 최대 길이가 있다면 추가 할 것.
	HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";

	CHTString::HT_hrStringCopy( tokenMsg, strInfo, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/이동 %s", chName );
	sscanf( tokenMsg, szToken.HT_szGetString(), chName );
	
	MSG_GMMoveToPlayer* info = HT_NULL;
	info = new MSG_GMMoveToPlayer;

	CHTString::HT_hrStringCopy( info->szCharName, chName, SZNAME_LENGTH );
	m_strNearCharName = info->szCharName;
	
	g_pNetWorkMgr->RequestGMMoveNearChar( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMovePositon Name:%s", info->szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_GMMOVE_NEAR_CHAR( MSG_GMMoveToPlayer* info )
{
	//	현재 서버와 연결 끊음
	g_pNetWorkMgr->DisConnect();

	//	새로운 존
	g_wResentZoneServerID = info->byZone;

	//	존서버 No, IP와 Port를 전역으로 저장
	g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
	g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;

	//	서버와의 DisConnect Check Seting
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;

	//	존 서버 커넥트를 기다리도록 설정
	g_bZoneServerSwitching = HT_TRUE;

	//	연결형태 셋팅
	g_byInitConnectType = CONNECT_TYPE_WARP;
}
//---------- 특정케릭터를 GM 근처로 워프 요청한다-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CHAR_RECALL_send()
{
	PS_CSP_REQ_CHAR_RECALL info = HT_NULL;
	info = new S_CSP_REQ_CHAR_RECALL;
	info->szCharName;

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_MovePositon Name:%s", info->szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_CHAR_RECALL_recive( PS_SCP_RESP_CHAR_RECALL info )
{
}
//---------- 채팅사용의 금지, 해제 요청한다-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CONTROL_CHAT_send()
{
}
HTvoid HTGM::HT_vNetWork_SSP_Resp_CONTROL_CHAT_recive( PS_SCP_RESP_CONTROL_CHAT info )
{
}
//---------- 채팅사용의 금지, 해제를 알린다.-------------//
HTvoid HTGM::HT_vNetWork_CSP_CONTROL_CHAT_NOTIFY_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_CONTROL_CHAT_NOTIFY_recive( PS_CSP_CONTROL_CHAT_NOTIFY info )
{
}
//---------- 특정케릭터의 동작멈춤을 요청한다-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CONTROL_ACTION_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_CONTROL_ACTION_recive( PS_SCP_RESP_CONTROL_ACTION info )
{
}
//---------- GM케릭터에의한 동작멈춤을 알린다-------------//
HTvoid HTGM::HT_vNetWork_CSP_CONTROL_ACTION_NOTIFY_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_CONTROL_ACTION_NOTIFY_recive( PS_SCP_CONTROL_ACTION_NOTIFY info )
{
}
//---------- GM케릭터가 다른캐릭터의 정보를 요청에 대한 답-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CHAR_INFO( PS_SCP_RESP_CHAR_INFO info )
{
	//	상대캐릭터의 정보를 저장하는곳
	m_strInfoBuffer1.HT_hrCleanUp();

	CHTString szMessage;
	m_strInfoBuffer1 += _T("기본정보\n");
	szMessage.HT_szFormat( "이름:%s, MaxHP:%d, CurHP:%d", info->szCharName, info->nMaxHP, info->nCurHP );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "최소물리공격력:%d, 최대물리공격력:%d, 최소마법공격력:%d, 최대마법공격력:%d", info->snMinPhysicalDamage, info->snMaxPhysicalDamage, info->snMinMagicDamage, info->snMaxMagicDamage  );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "최소불데미지:%d, 최대불데미지:%d, 최소추위데미지:%d, 최대추위대미지:%d, 최소독데미지:%d, 최대독데미지:%d, 최소산데미지:%d, 최대산데미지:%d", 
		info->snMinFireDamage, info->snMaxFireDamage, info->snMinColdDamage, info->snMaxColdDamage, info->snMinPoisonDamage, info->snMaxPoisonDamage, info->snMinAcidDamage, info->snMaxAcidDamage );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "방어력:%d, 블럭율:%d", info->snArmorIntensity, info->snBlockRate );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "전체챠크라:%d, 근육의챠크라:%d, 신경의챠크라:%d, 심장의챠크라:%d, 정신의챠크라:%d", info->nSumChakraPoint, info->snChakraMuscle, info->snChakraNerve, info->snChakraHeart, info->snChakraSoul );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "공격성공율:%d, 회피율:%d, 이동속도:%d, 공격속도:%d", info->snAttackSuccRate, info->snAvoidanceRate, info->snMovingSpeed, info->snAttackSpeed );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	m_strInfoBuffer1 += ("\n");
}

//---------- GM케릭터가 다른캐릭터의 정보를 요청에 대한 답-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CHAR_SKILL( PS_SCP_RESP_CHAR_SKILL info )
{
	//	상대캐릭터의 정보를 저장하는곳
	m_strInfoBuffer3.HT_hrCleanUp();
	CHTString				szMessage;

	m_strInfoBuffer3 = _T("스킬 정보\n");

							//	SKILL_BASIC_PARAMS*		sSkill_Param;
	CHTString szName;
	for( HTint i=0 ; i<30 ; i++ )
	{
		if( info->SkillInfo[i].dwIndex != 0 )
		{
							//			sSkill_Param = g_pclsEditorsData->SearchSkillParam( info->SkillInfo[i].dwIndex, info->SkillInfo[i].byLevel );
							//			szMessage.HT_szFormat( "스킬이름:%s, 스킬레벨:%d", sSkill_Param->szName, info->SkillInfo[i].byLevel );
			if( g_pEngineHandler->HT_hrGetFXName( info->SkillInfo[i].dwIndex, &szName ) == HT_OK )
				szMessage.HT_szFormat( "스킬이름:%s, 스킬레벨:%d", szName.HT_szGetString(), info->SkillInfo[i].byLevel );
			else
				szMessage = _T("스킬 정보를 찾지 못했습니다.");

			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
			m_strInfoBuffer3 += szMessage;
		}
	}

	HTtchar* pNotifyBuffer;
	pNotifyBuffer = NULL;
	pNotifyBuffer = (HTtchar *)malloc( m_strInfoBuffer1.HT_nGetSize()+m_strInfoBuffer1.HT_nGetSize()+m_strInfoBuffer2.HT_nGetSize()+1 );
	
	strncpy( pNotifyBuffer, (HTtchar*)m_strInfoBuffer1, m_strInfoBuffer1.HT_nGetSize() );
	strncpy( pNotifyBuffer+m_strInfoBuffer1.HT_nGetSize(), (HTtchar*)m_strInfoBuffer2, m_strInfoBuffer2.HT_nGetSize() );
	strncpy( pNotifyBuffer+m_strInfoBuffer1.HT_nGetSize()+m_strInfoBuffer2.HT_nGetSize(), (HTtchar*)m_strInfoBuffer3, m_strInfoBuffer3.HT_nGetSize() );

	//	공지창 켬
	g_pNotifyWindow->HT_vNotify_SetOn();
	g_pNotifyWindow->HT_vNotify_SetText( (HTtchar*)pNotifyBuffer );

	free( pNotifyBuffer );
	pNotifyBuffer = NULL;
}
//---------- GM케릭터가 다른캐릭터의 로그아웃 요청에 대한 답-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CLOSE_CHAR( PS_SCP_RESP_CLOSE_CHAR info )
{
}

// 진정 메시지
HTvoid HTGM::HT_vNewWork_CSP_Req_Appeal_Chat( CHTString strMsg )
{
	PS_CSP_REQ_APPEAL_CHAT info;
	info = new S_CSP_REQ_APPEAL_CHAT;

	// 메시지의 최대 길이와 ID의 최대 길이가 있다면 추가 할 것.
	CHTString::HT_hrStringCopy( info->szMsg, strMsg, MAX_CHAT_LENGTH );
	g_pNetWorkMgr->RuquestAppealChat( info );
	HT_DELETE( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_Request_AppealChat" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTGM::HT_vNewWork_SCP_RESP_Appeal_Chat( PS_SCP_RESP_APPEAL_CHAT info )
{
	// 결과 : 0x00 - 성공, 0x01 - 실패(접수되지 않음), 0x02 - 실패(진정 처리한도 초과)
	CHTString szMessage;
	switch( info->byResult )
	{
		case 0 : // 진정이 접수되었습니다.
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptOK, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
		case 1 : // 진정이 접수되지 않았습니다.
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptFail, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
		case 2 : // 진정 처리한도가 초과하였습니다
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptLimitOver, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
	}
}
