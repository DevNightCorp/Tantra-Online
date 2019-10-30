//------------------------------------------------------------------------------
// HTAddress.h
// �ּ�â
// (��)�Ѻ�����Ʈ ���Ӱ����� ���Ǳ�		2003.04.21
//------------------------------------------------------------------------------
#pragma once


class HTGM
{
public:
	HTGM(void);
	~HTGM(void);

	HTvoid				HT_vGM_Init();

	HTbool				HT_bGM_CommandSw() { return m_bGMCommandWnd; };
	HTvoid				HT_vGM_ActionOn();
	HTvoid				HT_vGM_ActionOff();

	HTRESULT			HT_vGM_DlgBox_Check();
	HTRESULT			HT_vGM_ReDlgBox_Check();

	//	��ȯ����
	CHTString			HT_strGM_GetNearCharName();

	//			0x25 Group(GM)	212
	//			��Ʈ��ũ �Լ�
	HTvoid				HT_vNetWork_CSP_Req_GMMode( CHTString strMessage, HTbyte byGMMode );
	HTvoid				HT_vNetWork_SCP_Resp_GMMode( MSG_GMMode* info );
	HTvoid				HT_vNetWork_CSP_Req_GMMOVE_POSITION( CHTString strInfo );
	HTvoid				HT_vNetWork_SCP_Resp_GMMOVE_POSITION( MSG_GMMovePosition* info );
	HTvoid				HT_vNetWork_CSP_Req_GMMOVE_NEAR_CHAR( CHTString strInfo );
	HTvoid				HT_vNetWork_SCP_Resp_GMMOVE_NEAR_CHAR( MSG_GMMoveToPlayer* info );
	HTvoid				HT_vNetWork_CSP_Req_CHAR_RECALL_send();
	HTvoid				HT_vNetWork_SCP_Resp_CHAR_RECALL_recive( PS_SCP_RESP_CHAR_RECALL info );
	HTvoid				HT_vNetWork_CSP_Req_CONTROL_CHAT_send();
	HTvoid				HT_vNetWork_SSP_Resp_CONTROL_CHAT_recive( PS_SCP_RESP_CONTROL_CHAT info );
	HTvoid				HT_vNetWork_CSP_CONTROL_CHAT_NOTIFY_send();
	HTvoid				HT_vNetWork_SCP_CONTROL_CHAT_NOTIFY_recive( PS_CSP_CONTROL_CHAT_NOTIFY info );
	HTvoid				HT_vNetWork_CSP_Req_CONTROL_ACTION_send();
	HTvoid				HT_vNetWork_SCP_Resp_CONTROL_ACTION_recive( PS_SCP_RESP_CONTROL_ACTION info );
	HTvoid				HT_vNetWork_CSP_CONTROL_ACTION_NOTIFY_send();
	HTvoid				HT_vNetWork_SCP_CONTROL_ACTION_NOTIFY_recive( PS_SCP_CONTROL_ACTION_NOTIFY info );
	HTvoid				HT_vNetWork_SCP_RESP_CHAR_INFO( PS_SCP_RESP_CHAR_INFO info );
	HTvoid				HT_vNetWork_SCP_RESP_CHAR_SKILL( PS_SCP_RESP_CHAR_SKILL info );
	HTvoid				HT_vNetWork_SCP_RESP_CLOSE_CHAR( PS_SCP_RESP_CLOSE_CHAR info );

	// ���� �޽���
	HTvoid				HT_vNewWork_CSP_Req_Appeal_Chat( CHTString strMsg );
	HTvoid				HT_vNewWork_SCP_RESP_Appeal_Chat( PS_SCP_RESP_APPEAL_CHAT info );


public:
	HTbool				m_bGMCommandWnd;
	HTbool				m_bDlgBoxSw;
	HTbool				m_bReDlgBoxSw;

	CHTString			m_strNearCharName;

	//	���ĳ������ ������ �����ϴ°�1
	CHTString			m_strInfoBuffer1;
	//	���ĳ������ ������ �����ϴ°�2
	CHTString			m_strInfoBuffer2;
	//	���ĳ������ ������ �����ϴ°�3
	CHTString			m_strInfoBuffer3;

};
