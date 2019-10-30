#pragma once

class HTCommand
{
public:
	HTCommand(void);
	~HTCommand(void);

	//	명령_초기화
	HTvoid			HT_vCommand_Init();
	//	명령_Create Window
	HTvoid			HT_vCommand_CreateWnd();
	//	명령_입력함수 처리
	static void		HT_hrCommand_InputCheckCommand(int iAction, int iTarget, int iTargetID);
	//	명령_명령창 활성화/비활성화
	HTvoid			HT_vCommand_WndActiveSw();
	//	명령_앉기
	HTvoid			HT_vCommand_Sit();
	//	명령_걷기
	HTvoid			HT_vCommand_Walk();
	//	명령_공격
	HTvoid			HT_vCommand_Attack();
	//	명령_타겥
	HTvoid			HT_vCommand_Target();
	//	명령_추적
	HTvoid			HT_vCommand_Pursuit();
	//	명령_지원
	HTvoid			HT_vCommand_Support();
	//	명령_교환
	HTvoid			HT_vCommand_Exchange();
	//	명령_줍기
	HTvoid			HT_vCommand_PickUp();
	//	명령_파티
	HTvoid			HT_vCommand_Party();
	//	명령_탈퇴
	HTvoid			HT_vCommand_PartyWithDraw();
	//	명령_개인상점
	HTvoid			HT_vCommand_Shop();
	//	명령_도발
	HTvoid			HT_vCommand_Provoke();
	//	명령_인사
	HTvoid			HT_vCommand_Greet();
	//	명령_돌격
	HTvoid			HT_vCommand_Rush();
	//  명령_블로그
	HTvoid			HT_vCommand_Blog();
	//  명령_결투
	HTvoid			HT_vCommand_Duel();
	//  명령_자리비움
	HTvoid			HT_vCommand_EmptyPlace();
	//  명령_도움
	HTvoid			HT_vCommand_Assist();
	//  명령_지시
	HTvoid			HT_vCommand_Directions( HTint iAction );
	//  명령_공성전
	HTvoid			HT_vCommand_Siege();

	//	명령_Set 퀵슬롯에서 명령사용 요청
	HTvoid			HT_vCommand_SetQuickSlotCmdUse( HTint iQuickSlotNo );

	//	Net_Req Assist
	HTvoid			HT_vCommand_NetReqAssist( HTint iTargetKeyID );
	//	Net_Recive Assist
	HTvoid			HT_vCommand_NetReciveAssist( HTint iTargetKeyID );

	//	Get
	//	Get	BitmapImage
	HTint			HT_iCommand_GetBitmapImage()	{	return m_iCommand_GripBitmapImage; };
	//	Get	BeforeTargetID
	HTint			HT_iCommand_GetBeforeTargetID();

	//	Set
	//	Set	BeforeTargetID
	HTvoid			HT_vCommand_SetBeforeTargetID( HTint iBeforeTargetID )	{	m_iCommand_BeforeTargetID = iBeforeTargetID; };

private:
	HTbool			m_bCommand_WndSw;
	HTint			m_iCommand_BeforeTargetID;

	HTint			m_iCommand_CmdIconStatus;

	HTint			m_iCommand_GripBitmapNo;
	HTint			m_iCommand_GripBitmapImage;

	HTbool			m_bCommand_Assist;
	HTint			m_iCommand_AssistTargetID;
};
