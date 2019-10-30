
#ifndef __HTGAMESYSTEM_H__
#define __HTGAMESYSTEM_H__

#include "HTMiniMap.h"


class CHTGameSystem
{
public:
	CHTGameSystem();
	~CHTGameSystem();

	//-----GS ����Ÿ Ŭ���� �ϱ�-----//
	HTvoid						HT_vGSDataCleanUp();
	HTRESULT					HT_hrGameSystemInit();
	HTvoid						HT_vGameSystem_CreateWindow();
	CHTString					HT_strGetPCSkillMD5CheckSum();
	CHTString					HT_strGetSkillIDMD5CheckSum(const int id, const byte byteLevel,const int NeedTimes);
	CHTString					HT_strGetServerlistMD5CheckSum();
	//	�Է� �޼��� ó��
	//	Daeth Mssage
	static void					HT_vGameSystem_InputCheckForDeathMsg(int iAction, int iTarget, int iTargetID);
	//	Death Message Fortess
	static void					HT_vGameSystem_InputCheckForDeathinFortess(int iAction, int iTarget, int iTargetID);
	//	DisConnect Server
	static void					HT_vGameSystem_InputCheckForDisConnectServer(int iAction, int iTarget, int iTargetID);
	//	Samudaba Skill
	static void					HT_vGameSystem_InputCheckForSamadaba(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� Revive
	static void					HT_vGameSystem_InputCheckRevive(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� WebBrowser
	static void					HT_vGameSystem_InputCheckWebBrowser(int iAction, int iTarget, int iTargetID);
	//	�Է��Ѽ� ó�� Quiz
	static void					HT_vGameSystem_InputCheckQuiz(int iAction, int iTarget, int iTargetID);

	HTRESULT					HT_hrGameSystemControl( HTfloat );

	//	About Network
	//	�������� ��Ŷ �����ޱ�-ĳ���� �⺻ ����Ÿ
	HTvoid						HT_vGameSystem_UpDateUI( PS_SCP_RESP_UPDATE_UI info );
	//	�������� ��Ŷ �����ޱ�-ĳ���� �ּ�ȭ�� ����Ÿ
	HTvoid						HT_vGameSystem_UpDate_Status( PS_SCP_RESP_UPDATE_STATUS info );
	//	�������� ��Ŷ �����ޱ�-���� �ʱ�ȭ���� ĳ���� �׾��� ��
	HTvoid						HT_vGameSystem_NetWorkInitCharDeath();
	//	�������� ��Ŷ �����ޱ�-ĳ���� ���
	HTvoid						HT_vGameSystem_NetWorkDeath( HTshort snTribe, CHTString strKillerName );
	//	�������� ��Ŷ �����ޱ�-��� Ȯ��â �ٿ��
	HTvoid						HT_vGameSystem_OpenDeathWindow();
	//	�������� ��Ŷ �����ޱ�-ĳ���� ���� ��û
	HTvoid						HT_vGameSystem_CSP_INIT_REGEN_CHAR( BYTE );
	//	�������� ��Ŷ �����ޱ�-ĳ���� ����� �̴� ������û ���
	HTvoid						HT_vGameSystem_SCP_INIT_REGEN_CHAR( PS_SCP_RESP_INIT_REGEN_CHAR info );
	//	OtherObjectSystem���� ������
	//	�繫�ٹ� ��ų ����ص� �ųİ� �����
	HTvoid						HT_vGameSystem_ReqAnswerUseSamudaba( int iEchoType, int iKeyID, HTbyte byResponse, HTbyte byData );
	HTvoid						HT_vGameSystem_SetKillerName( CHTString strKillerName );
	//	�繫�ٹ� ��ų ����ص� �ųİ� ����� ���� �ޱ�
	HTvoid						HT_vGameSystem_ReciveAnswerUseSamudaba( Msg_Echo* info );
	//	�������� ��Ŷ �����ޱ�-������ ������ �������� ��
	HTvoid						HT_vGameSystem_ServerDisConnect_SetDlg( CHTString );
	//	�������� ��Ŷ �����ޱ�-������ ������ �������� ��
	HTRESULT					HT_vGameSystem_ServerDisConnect_CheckDlg( HTint iButtonNo );
	//	�������� ��Ŷ �����ޱ�-Quiz
	HTvoid						HT_vGameSystem_SCP_Quiz( Msg_Quiz* info );

	//	Set RequestMoveZoneServerCheck
	HTvoid						HT_vSetRequestMoveZoneServer( HTbool );
	HTvoid						HT_vRequestMoveZoneServerCheck();

	//	Get
	//	Server Status
	HTbool						HT_bGameSystem_GetServerStatus()	{	return m_bServerDisConnectSw;	};
	//	Answer SamudabaSw
	HTbool						HT_bGameSystem_GetAskSamudaba()		{	return m_bAnswerSamudabaSw;		};

	//-----����-----//
	HTvoid						HT_hrGameSystemRender();
	//	IME Render
	HTvoid						HT_vGameSystemRender_IME();
private:
	HTvoid						HT_vGameSystem_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid						HT_vGameSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//	�޸� ���ǵ����� �������� �� �׷���..
	__forceinline HTvoid		HT_vGameSystem_SetCharMoveSpeed( PS_SCP_RESP_UPDATE_UI info );
	//	�޸� ���ǵ����� �������� �� �׷���..
	__forceinline HTvoid		HT_vGameSystem_SetCharAttackSpeed( PS_SCP_RESP_UPDATE_UI info );

public:

	//----------ĳ���� �׾��� �� ���� ����ġ----------//
	HTbool						m_bReqReenDlgSw;
	//----------������ �׾����� Ȯ�� ����ġ----------//
	HTbool						m_bServerDisConnectSw;

	//----------������ ������ �������� ��-�ð�üũ�ϱ� ����----------//
	DWORD						m_dwServerDisConnectTimeOut;

	//	����Ÿ��
	HTbyte						m_byRegenType;

	//	Answer Samudaba
	HTbool						m_bAnswerSamudabaSw;
	//	UserID Answer Samudaba
	HTint						m_iUserIDAnswerSamudaba;
	//	Samudaba Delay Time
	DWORD						m_dwSamudabaDelayTime;
	HTint						m_nRange;

private:
	// �޼��� ����� ���� ����
	HTint						m_iMessageVal;
	HTbool						m_bPKOn;

	//	��Ż �̿��Ҷ� RequestMoveZoneServer
	HTbool						m_bRequestMoveZoneServerCheck;
	HTdword						m_bRequestMoveZoneServerStartTime;

	//	���� ���� ������Ʈ �̸�
	CHTString					m_strKillerName;

	//	�������� ��������� ���������
	HTint						m_iButtonType;

	//	Ȯ�ι�ư�� ������ �̴�Ŀ��Ʈ ��û�ߴ����� �ȴ�.
	HTbool						m_bUserReqInitRegenChar;
};

#endif

