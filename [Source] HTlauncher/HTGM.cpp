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

//	GM �ʱ�ȭ
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

//	GM_Ȯ�� â�� üũ
HTRESULT HTGM::HT_vGM_DlgBox_Check()
{
	if( m_bDlgBoxSw == HT_FALSE )
		return HT_FAIL;
	
	return HT_OK;
}

//	GM_Ȯ�� / ��� �� üũ���콺 Ŭ���� üũ
HTRESULT HTGM::HT_vGM_ReDlgBox_Check()
{
	if( m_bReDlgBoxSw == HT_FALSE )
		return HT_FAIL;

	return HT_OK;
}

//	��ȯ����
CHTString HTGM::HT_strGM_GetNearCharName()
{
	return m_strNearCharName;
}

//			0x25 Group(GM)	212
//			��Ʈ��ũ �Լ�
//---------- GM�� �����带 ���� �Ǵ� ������ ��û�Ѵ�-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMode( CHTString strMessage, HTbyte byGMMode )
{
	MSG_GMMode* info = HT_NULL;
	info = new MSG_GMMode;
	
	if( byGMMode == 0x02 )
	{
		if( g_oMainCharacterInfo.byGMStatus & 0x02 )	// ���� ������ ��� -> ������ Ǫ�� ��û��
			info->byGMMode = 0x02;	//g_oMainCharacterInfo.byGMStatus & 0xfd;
		else											// ���� ������ �ƴ� ��� -> ������ �ϴ� ��û�� 
			info->byGMMode = 0x82;	//g_oMainCharacterInfo.byGMStatus | 0x02;

		//	�̸� ����
		CHTString::HT_hrStringCopy( info->szCharName, strMessage.HT_szGetString(), SZNAME_LENGTH );
	}
	// GM �� Ư�� ĳ������ ä���� ���ϴ� ���
	else if( byGMMode == 0x04 )
	{
		//	�̸� ����
		HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
		int iGMMode = 0;
		CHTString::HT_hrStringCopy( tokenMsg, strMessage.HT_szGetString(), MAX_CHAT_LENGTH );
		sscanf( tokenMsg, "/chatblock %s %d", info->szCharName, &iGMMode );

		if( iGMMode == 0 )	// Chat Block ����
            info->byGMMode = 0x04;
		else				// Chat Block ����
			info->byGMMode = 0x84;
	}

	g_pNetWorkMgr->RequestGMMode( info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMode : %s, %d", info->szCharName, info->byGMMode );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_GMMode( MSG_GMMode* info )
{
	CHTString szMessage;
	if( info->byResult == 0 )
	{
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, _T("��û�Ͻ� ����� �����Ͽ����ϴ�.") );
	}
	else if( info->byResult == 1 )
	{
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, _T("��û�Ͻ� ����� �����Ͽ����ϴ�.") );
	}
}
//---------- Ư����ġ���� ������ ��û�Ѵ�.(��������)-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMOVE_POSITION( CHTString strInfo )
{
	// ĳ������ �̸��� �и��� ����(sscanf) ���� ��ū ����
	CHTString szMessage, szToken;
	if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCommandWarp, &szMessage ) == false )
		return;
	szToken = szMessage + _T(" %d, %d") ;

	// �޽����� �ִ� ���̿� ID�� �ִ� ���̰� �ִٸ� �߰� �� ��.
	char tokenMsg[MAX_CHAT_LENGTH] = "\0";
	HTint nX, nZ;
	CHTString::HT_hrStringCopy( tokenMsg, strInfo, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/���� %d, %d", &nX, &nZ );
	sscanf( tokenMsg, szToken.HT_szGetString(), &nX, &nZ );

	MSG_GMMovePosition* info = HT_NULL;
	info = new MSG_GMMovePosition;

	info->snX = nX;
	info->snZ = nZ;

	if( info->snX>0 && info->snX<1024 &&
		info->snZ>0 && info->snZ<1024 )
	{
		g_pNetWorkMgr->RequestGMMovePosition( info );
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMovePositon: x:%d, z:%d", info->snX, info->snZ );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	else
	{
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("�������� ������ϴ�" );
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
//---------- Ư���ɸ��� ��ó���� ������ ��û�Ѵ�-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( CHTString strInfo )
{
	// ĳ������ �̸��� �и��� ����(sscanf) ���� ��ū ����
	CHTString szMessage, szToken;
	if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCommandMove, &szMessage ) == false )
		return;
	szToken = szMessage + _T(" %s");

	char chName[SZNAME_LENGTH];
	// �޽����� �ִ� ���̿� ID�� �ִ� ���̰� �ִٸ� �߰� �� ��.
	HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";

	CHTString::HT_hrStringCopy( tokenMsg, strInfo, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/�̵� %s", chName );
	sscanf( tokenMsg, szToken.HT_szGetString(), chName );
	
	MSG_GMMoveToPlayer* info = HT_NULL;
	info = new MSG_GMMoveToPlayer;

	CHTString::HT_hrStringCopy( info->szCharName, chName, SZNAME_LENGTH );
	m_strNearCharName = info->szCharName;
	
	g_pNetWorkMgr->RequestGMMoveNearChar( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_GMMovePositon Name:%s", info->szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_GMMOVE_NEAR_CHAR( MSG_GMMoveToPlayer* info )
{
	//	���� ������ ���� ����
	g_pNetWorkMgr->DisConnect();

	//	���ο� ��
	g_wResentZoneServerID = info->byZone;

	//	������ No, IP�� Port�� �������� ����
	g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
	g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;

	//	�������� DisConnect Check Seting
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;

	//	�� ���� Ŀ��Ʈ�� ��ٸ����� ����
	g_bZoneServerSwitching = HT_TRUE;

	//	�������� ����
	g_byInitConnectType = CONNECT_TYPE_WARP;
}
//---------- Ư���ɸ��͸� GM ��ó�� ���� ��û�Ѵ�-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CHAR_RECALL_send()
{
	PS_CSP_REQ_CHAR_RECALL info = HT_NULL;
	info = new S_CSP_REQ_CHAR_RECALL;
	info->szCharName;

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_MovePositon Name:%s", info->szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_CHAR_RECALL_recive( PS_SCP_RESP_CHAR_RECALL info )
{
}
//---------- ä�û���� ����, ���� ��û�Ѵ�-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CONTROL_CHAT_send()
{
}
HTvoid HTGM::HT_vNetWork_SSP_Resp_CONTROL_CHAT_recive( PS_SCP_RESP_CONTROL_CHAT info )
{
}
//---------- ä�û���� ����, ������ �˸���.-------------//
HTvoid HTGM::HT_vNetWork_CSP_CONTROL_CHAT_NOTIFY_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_CONTROL_CHAT_NOTIFY_recive( PS_CSP_CONTROL_CHAT_NOTIFY info )
{
}
//---------- Ư���ɸ����� ���۸����� ��û�Ѵ�-------------//
HTvoid HTGM::HT_vNetWork_CSP_Req_CONTROL_ACTION_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_Resp_CONTROL_ACTION_recive( PS_SCP_RESP_CONTROL_ACTION info )
{
}
//---------- GM�ɸ��Ϳ����� ���۸����� �˸���-------------//
HTvoid HTGM::HT_vNetWork_CSP_CONTROL_ACTION_NOTIFY_send()
{
}
HTvoid HTGM::HT_vNetWork_SCP_CONTROL_ACTION_NOTIFY_recive( PS_SCP_CONTROL_ACTION_NOTIFY info )
{
}
//---------- GM�ɸ��Ͱ� �ٸ�ĳ������ ������ ��û�� ���� ��-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CHAR_INFO( PS_SCP_RESP_CHAR_INFO info )
{
	//	���ĳ������ ������ �����ϴ°�
	m_strInfoBuffer1.HT_hrCleanUp();

	CHTString szMessage;
	m_strInfoBuffer1 += _T("�⺻����\n");
	szMessage.HT_szFormat( "�̸�:%s, MaxHP:%d, CurHP:%d", info->szCharName, info->nMaxHP, info->nCurHP );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "�ּҹ������ݷ�:%d, �ִ빰�����ݷ�:%d, �ּҸ������ݷ�:%d, �ִ븶�����ݷ�:%d", info->snMinPhysicalDamage, info->snMaxPhysicalDamage, info->snMinMagicDamage, info->snMaxMagicDamage  );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "�ּҺҵ�����:%d, �ִ�ҵ�����:%d, �ּ�����������:%d, �ִ����������:%d, �ּҵ�������:%d, �ִ뵶������:%d, �ּһ굥����:%d, �ִ�굥����:%d", 
		info->snMinFireDamage, info->snMaxFireDamage, info->snMinColdDamage, info->snMaxColdDamage, info->snMinPoisonDamage, info->snMaxPoisonDamage, info->snMinAcidDamage, info->snMaxAcidDamage );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "����:%d, ����:%d", info->snArmorIntensity, info->snBlockRate );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "��üíũ��:%d, ������íũ��:%d, �Ű���íũ��:%d, ������íũ��:%d, ������íũ��:%d", info->nSumChakraPoint, info->snChakraMuscle, info->snChakraNerve, info->snChakraHeart, info->snChakraSoul );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	szMessage.HT_szFormat( "���ݼ�����:%d, ȸ����:%d, �̵��ӵ�:%d, ���ݼӵ�:%d", info->snAttackSuccRate, info->snAvoidanceRate, info->snMovingSpeed, info->snAttackSpeed );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	m_strInfoBuffer1 += szMessage;
	m_strInfoBuffer1 += ("\n");
}

//---------- GM�ɸ��Ͱ� �ٸ�ĳ������ ������ ��û�� ���� ��-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CHAR_SKILL( PS_SCP_RESP_CHAR_SKILL info )
{
	//	���ĳ������ ������ �����ϴ°�
	m_strInfoBuffer3.HT_hrCleanUp();
	CHTString				szMessage;

	m_strInfoBuffer3 = _T("��ų ����\n");

							//	SKILL_BASIC_PARAMS*		sSkill_Param;
	CHTString szName;
	for( HTint i=0 ; i<30 ; i++ )
	{
		if( info->SkillInfo[i].dwIndex != 0 )
		{
							//			sSkill_Param = g_pclsEditorsData->SearchSkillParam( info->SkillInfo[i].dwIndex, info->SkillInfo[i].byLevel );
							//			szMessage.HT_szFormat( "��ų�̸�:%s, ��ų����:%d", sSkill_Param->szName, info->SkillInfo[i].byLevel );
			if( g_pEngineHandler->HT_hrGetFXName( info->SkillInfo[i].dwIndex, &szName ) == HT_OK )
				szMessage.HT_szFormat( "��ų�̸�:%s, ��ų����:%d", szName.HT_szGetString(), info->SkillInfo[i].byLevel );
			else
				szMessage = _T("��ų ������ ã�� ���߽��ϴ�.");

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

	//	����â ��
	g_pNotifyWindow->HT_vNotify_SetOn();
	g_pNotifyWindow->HT_vNotify_SetText( (HTtchar*)pNotifyBuffer );

	free( pNotifyBuffer );
	pNotifyBuffer = NULL;
}
//---------- GM�ɸ��Ͱ� �ٸ�ĳ������ �α׾ƿ� ��û�� ���� ��-------------//
HTvoid HTGM::HT_vNetWork_SCP_RESP_CLOSE_CHAR( PS_SCP_RESP_CLOSE_CHAR info )
{
}

// ���� �޽���
HTvoid HTGM::HT_vNewWork_CSP_Req_Appeal_Chat( CHTString strMsg )
{
	PS_CSP_REQ_APPEAL_CHAT info;
	info = new S_CSP_REQ_APPEAL_CHAT;

	// �޽����� �ִ� ���̿� ID�� �ִ� ���̰� �ִٸ� �߰� �� ��.
	CHTString::HT_hrStringCopy( info->szMsg, strMsg, MAX_CHAT_LENGTH );
	g_pNetWorkMgr->RuquestAppealChat( info );
	HT_DELETE( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_Request_AppealChat" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTGM::HT_vNewWork_SCP_RESP_Appeal_Chat( PS_SCP_RESP_APPEAL_CHAT info )
{
	// ��� : 0x00 - ����, 0x01 - ����(�������� ����), 0x02 - ����(���� ó���ѵ� �ʰ�)
	CHTString szMessage;
	switch( info->byResult )
	{
		case 0 : // ������ �����Ǿ����ϴ�.
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptOK, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
		case 1 : // ������ �������� �ʾҽ��ϴ�.
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptFail, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
		case 2 : // ���� ó���ѵ��� �ʰ��Ͽ����ϴ�
			if( g_pMessageMgr->HT_bGetMessage( eMsgGMASReceiptLimitOver, &szMessage ) == true )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			break;
	}
}
