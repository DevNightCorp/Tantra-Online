#pragma once

class HTCommand
{
public:
	HTCommand(void);
	~HTCommand(void);

	//	���_�ʱ�ȭ
	HTvoid			HT_vCommand_Init();
	//	���_Create Window
	HTvoid			HT_vCommand_CreateWnd();
	//	���_�Է��Լ� ó��
	static void		HT_hrCommand_InputCheckCommand(int iAction, int iTarget, int iTargetID);
	//	���_���â Ȱ��ȭ/��Ȱ��ȭ
	HTvoid			HT_vCommand_WndActiveSw();
	//	���_�ɱ�
	HTvoid			HT_vCommand_Sit();
	//	���_�ȱ�
	HTvoid			HT_vCommand_Walk();
	//	���_����
	HTvoid			HT_vCommand_Attack();
	//	���_Ÿ��
	HTvoid			HT_vCommand_Target();
	//	���_����
	HTvoid			HT_vCommand_Pursuit();
	//	���_����
	HTvoid			HT_vCommand_Support();
	//	���_��ȯ
	HTvoid			HT_vCommand_Exchange();
	//	���_�ݱ�
	HTvoid			HT_vCommand_PickUp();
	//	���_��Ƽ
	HTvoid			HT_vCommand_Party();
	//	���_Ż��
	HTvoid			HT_vCommand_PartyWithDraw();
	//	���_���λ���
	HTvoid			HT_vCommand_Shop();
	//	���_����
	HTvoid			HT_vCommand_Provoke();
	//	���_�λ�
	HTvoid			HT_vCommand_Greet();
	//	���_����
	HTvoid			HT_vCommand_Rush();
	//  ���_��α�
	HTvoid			HT_vCommand_Blog();
	//  ���_����
	HTvoid			HT_vCommand_Duel();
	//  ���_�ڸ����
	HTvoid			HT_vCommand_EmptyPlace();
	//  ���_����
	HTvoid			HT_vCommand_Assist();
	//  ���_����
	HTvoid			HT_vCommand_Directions( HTint iAction );
	//  ���_������
	HTvoid			HT_vCommand_Siege();

	//	���_Set �����Կ��� ��ɻ�� ��û
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
