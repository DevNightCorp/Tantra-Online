
#ifndef __HTGAMESYSTEM_H__
#define __HTGAMESYSTEM_H__

#include "HTMiniMap.h"


class CHTGameSystem
{
public:
	CHTGameSystem();
	~CHTGameSystem();

	//-----GS 데이타 클린업 하기-----//
	HTvoid						HT_vGSDataCleanUp();
	HTRESULT					HT_hrGameSystemInit();
	HTvoid						HT_vGameSystem_CreateWindow();
	CHTString					HT_strGetPCSkillMD5CheckSum();
	CHTString					HT_strGetSkillIDMD5CheckSum(const int id, const byte byteLevel,const int NeedTimes);
	CHTString					HT_strGetServerlistMD5CheckSum();
	//	입력 메세지 처리
	//	Daeth Mssage
	static void					HT_vGameSystem_InputCheckForDeathMsg(int iAction, int iTarget, int iTargetID);
	//	Death Message Fortess
	static void					HT_vGameSystem_InputCheckForDeathinFortess(int iAction, int iTarget, int iTargetID);
	//	DisConnect Server
	static void					HT_vGameSystem_InputCheckForDisConnectServer(int iAction, int iTarget, int iTargetID);
	//	Samudaba Skill
	static void					HT_vGameSystem_InputCheckForSamadaba(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 Revive
	static void					HT_vGameSystem_InputCheckRevive(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 WebBrowser
	static void					HT_vGameSystem_InputCheckWebBrowser(int iAction, int iTarget, int iTargetID);
	//	입력한수 처리 Quiz
	static void					HT_vGameSystem_InputCheckQuiz(int iAction, int iTarget, int iTargetID);

	HTRESULT					HT_hrGameSystemControl( HTfloat );

	//	About Network
	//	서버에서 패킷 내려받기-캐릭터 기본 데이타
	HTvoid						HT_vGameSystem_UpDateUI( PS_SCP_RESP_UPDATE_UI info );
	//	서버에서 패킷 내려받기-캐릭터 최소화한 데이타
	HTvoid						HT_vGameSystem_UpDate_Status( PS_SCP_RESP_UPDATE_STATUS info );
	//	서버에서 패킷 내려받기-최초 초기화에서 캐릭터 죽었을 때
	HTvoid						HT_vGameSystem_NetWorkInitCharDeath();
	//	서버에서 패킷 내려받기-캐릭터 사망
	HTvoid						HT_vGameSystem_NetWorkDeath( HTshort snTribe, CHTString strKillerName );
	//	서버에서 패킷 내려받기-사망 확인창 뛰우기
	HTvoid						HT_vGameSystem_OpenDeathWindow();
	//	서버에서 패킷 내려받기-캐릭터 리젼 요청
	HTvoid						HT_vGameSystem_CSP_INIT_REGEN_CHAR( BYTE );
	//	서버에서 패킷 내려받기-캐릭터 사망시 이닛 리젼요청 결과
	HTvoid						HT_vGameSystem_SCP_INIT_REGEN_CHAR( PS_SCP_RESP_INIT_REGEN_CHAR info );
	//	OtherObjectSystem에서 셋팅함
	//	사무다바 스킬 사용해도 돼냐고 물어보기
	HTvoid						HT_vGameSystem_ReqAnswerUseSamudaba( int iEchoType, int iKeyID, HTbyte byResponse, HTbyte byData );
	HTvoid						HT_vGameSystem_SetKillerName( CHTString strKillerName );
	//	사무다바 스킬 사용해도 돼냐고 물어본것 응답 받기
	HTvoid						HT_vGameSystem_ReciveAnswerUseSamudaba( Msg_Echo* info );
	//	서버에서 패킷 내려받기-서버와 연결이 끊어졌을 때
	HTvoid						HT_vGameSystem_ServerDisConnect_SetDlg( CHTString );
	//	서버에서 패킷 내려받기-서버와 연결이 끊어졌을 때
	HTRESULT					HT_vGameSystem_ServerDisConnect_CheckDlg( HTint iButtonNo );
	//	서버에서 패킷 내려받기-Quiz
	HTvoid						HT_vGameSystem_SCP_Quiz( Msg_Quiz* info );

	//	Set RequestMoveZoneServerCheck
	HTvoid						HT_vSetRequestMoveZoneServer( HTbool );
	HTvoid						HT_vRequestMoveZoneServerCheck();

	//	Get
	//	Server Status
	HTbool						HT_bGameSystem_GetServerStatus()	{	return m_bServerDisConnectSw;	};
	//	Answer SamudabaSw
	HTbool						HT_bGameSystem_GetAskSamudaba()		{	return m_bAnswerSamudabaSw;		};

	//-----랜드-----//
	HTvoid						HT_hrGameSystemRender();
	//	IME Render
	HTvoid						HT_vGameSystemRender_IME();
private:
	HTvoid						HT_vGameSystem_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid						HT_vGameSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//	메모리 스피드핵을 막기위한 뭐 그런것..
	__forceinline HTvoid		HT_vGameSystem_SetCharMoveSpeed( PS_SCP_RESP_UPDATE_UI info );
	//	메모리 스피드핵을 막기위한 뭐 그런것..
	__forceinline HTvoid		HT_vGameSystem_SetCharAttackSpeed( PS_SCP_RESP_UPDATE_UI info );

public:

	//----------캐릭터 죽었을 때 리젼 스위치----------//
	HTbool						m_bReqReenDlgSw;
	//----------서버가 죽었을때 확인 스위치----------//
	HTbool						m_bServerDisConnectSw;

	//----------서버랑 연결이 끊어졌을 때-시간체크하기 위해----------//
	DWORD						m_dwServerDisConnectTimeOut;

	//	리젠타입
	HTbyte						m_byRegenType;

	//	Answer Samudaba
	HTbool						m_bAnswerSamudabaSw;
	//	UserID Answer Samudaba
	HTint						m_iUserIDAnswerSamudaba;
	//	Samudaba Delay Time
	DWORD						m_dwSamudabaDelayTime;
	HTint						m_nRange;

private:
	// 메세지 출력을 위한 변수
	HTint						m_iMessageVal;
	HTbool						m_bPKOn;

	//	포탈 이용할때 RequestMoveZoneServer
	HTbool						m_bRequestMoveZoneServerCheck;
	HTdword						m_bRequestMoveZoneServerStartTime;

	//	나를 죽인 오브젝트 이름
	CHTString					m_strKillerName;

	//	공성전과 요새전에서 사망했을때
	HTint						m_iButtonType;

	//	확인버튼을 눌러서 이닛커넥트 요청했는지를 안다.
	HTbool						m_bUserReqInitRegenChar;
};

#endif

