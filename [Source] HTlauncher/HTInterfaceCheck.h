
#ifndef __HTINTERFACECHECK_H__
#define __HTINTERFACECHECK_H__

#define CURSOR_FILE_ARROW_1		_T("resource\\etc\\normal1.cur")	// ȭ��ǥ(arrow) Ŀ��
#define CURSOR_FILE_ARROW_2		_T("resource\\etc\\normal2.cur")
#define CURSOR_FILE_RBUTTON		_T("resource\\etc\\normal3.cur")	// ������ Ŭ������ �� Ŀ��

#define CURSOR_FILE_HAND_1		_T("resource\\etc\\hand1.cur")		// ��(hand) Ŀ��
#define CURSOR_FILE_HAND_2		_T("resource\\etc\\hand2.cur")		
#define CURSOR_FILE_HAND_ANI	_T("resource\\etc\\hand.ani")
#define CURSOR_FILE_SWORD		_T("resource\\etc\\sword.cur")		// Į(sword) Ŀ��
#define CURSOR_FILE_SWORD_ANI	_T("resource\\etc\\sword.ani")		
#define CURSOR_FILE_NPC			_T("resource\\etc\\npc.cur")		// ��ȭ(NPC) Ŀ��
#define CURSOR_FILE_NPC_ANI		_T("resource\\etc\\npc.ani")
#define CURSOR_FILE_REPAIR		_T("resource\\etc\\repair.cur")		// ����(repair) Ŀ��
#define CURSOR_FILE_REPAIR_ANI	_T("resource\\etc\\repair.ani")
#define CURSOR_FILE_REPAIRD		_T("resource\\etc\\repaird.cur")	// ���� �Ұ� Ŀ��

#define CURSOR_FILE_ADDRESS_ANI	_T("resource\\etc\\Address.ani")	// Address ȭ��ǥ(arrow) Ŀ��
#define CURSOR_FILE_ADDRESS		_T("resource\\etc\\Address.cur")
#define CURSOR_FILE_PARTY_ANI	_T("resource\\etc\\Party.ani")		// Party ȭ��ǥ(arrow) Ŀ��
#define CURSOR_FILE_PARTY		_T("resource\\etc\\Party.cur")
#define CURSOR_FILE_TRADE_ANI	_T("resource\\etc\\Trade.ani")		// Trade ȭ��ǥ(arrow) Ŀ��
#define CURSOR_FILE_TRADE		_T("resource\\etc\\Trade.cur")

#define CURSOR_FILE_BLOG_ANI	_T("resource\\etc\\blog.ani")		// Blog ������ �����ϴ� Ŀ��
#define CURSOR_FILE_BLOG		_T("resource\\etc\\blog.cur")

#define CURSOR_FILE_DUEL_ANI	_T("resource\\etc\\Select.ani")		//	��ɻ� ĳ���͸� ����Ʈ �ؾ� �ɶ�
#define CURSOR_FILE_DUEL		_T("resource\\etc\\Select.cur")


class CHTInterfaceCheck
{
public:
	CHTInterfaceCheck();
	~CHTInterfaceCheck();

	// �ε� �Ǿ������� �˻�
	HTbool					isLoaded(){	return m_bLoaded;	};


	HTvoid					HT_vCHTInterfaceCheck_CleanUp();

	//----------�㿡 ���� ���� �� �ʿ䰡 �ִ� ��----------//
	HTRESULT				HT_hrInterfaceInit();
	HTRESULT				HT_hrInterfaceControl();
	HTvoid					HT_hrInterfaceControlEnd();

	//----------����� ���� �Ͽ� ó���Ұ�----------//
	// ������ �Է��� ��� ����.
	HTvoid					HT_vFlushInput();
	//-----����� ���� �Ͽ� ó���Ұ�_L��ư �ٿ�-----//
	HTvoid					HT_vInterface_LbuttonDown( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_L��ư ��-----//
	HTvoid					HT_vInterface_LbuttonUp( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_L��ư Ŭ��-----//
	HTvoid					HT_vInterface_LbuttonClick( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_R��ư Ŭ��-----//
	HTvoid					HT_vInterface_RButtonClick( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_R��ư �ٿ�-----//
	HTvoid					HT_vInterface_RButtonDown( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_R��ư ��-----//
	HTvoid					HT_vInterface_RButtonUp( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_���콺 ����-----//
	HTvoid					HT_vInterface_MouseMove( HTPoint );
	//-----����� ���� �Ͽ� ó���Ұ�_���콺 ����_�����͵�-----//
	HTvoid					HT_vInterface_MouseMove_Cursor( HTPoint pPt, HTint nDlgNo );
	//-----����� ���� �Ͽ� ó���Ұ�_���콺 ����_����-----//
//	HTvoid					HT_vInterface_MouseMove_Resent( HTPoint );

	//-----Ű���� üũ_Down-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_KeyDown( WPARAM );
	//-----Ű���� üũ_Up-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_KeyUp( WPARAM );
	//-----Ű���� üũ_Function Key-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_FunctionKey( WPARAM wParam );
	//	ESCŰ ������ �ڵ����� ������ â���� ������ �ֵ���
	HTvoid					HT_vInterface_ESC_CloseWindow();
	//	Ȯ��/��Ȯ��â EnterŰ �Է�
	HTvoid					HT_vInterface_MessageWindowForEnterKey( HTint iDlgNo );
	//	��Ʈ��Ű
	HTvoid					HT_vInterface_SetControlKey( HTbool bValue )	{ m_bInterface_ControlKeySw=bValue; }
	HTbool					HT_vInterface_GetControlKey()	{	return m_bInterface_ControlKeySw;	}

	//-----Ű���� üũ_��� �����°�-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_Continue();

	HTvoid					HT_vSetCursor(HTint iID);			// Ŀ�� ����� ����
	HTint					HT_iGetCursor(){ return m_iCursorID; };			// Ŀ�� ����� ����

	HCURSOR					HT_hLoadCursor(CHTString szFile);
	HTvoid					HT_vRanderCursor();

	//-----���ݽÿ� �Է��� ������ ���� ����-----//
	HTvoid					HT_vInterface_AttackModeTrans( HTint nModelID );
	//-----�� �˻�_������-----//
	HTRESULT				HT_vInterface_Pick_Item( HTint, HTPoint );
	//-----�� �˻�_OtherCharter-----//
	HTRESULT				HT_vInterface_Pick_OtherChar( HTint );
	//-----�� �˻�_NPC-----//
	HTRESULT				HT_vInterface_Pick_NPC( HTint );
	//-----�� �˻�_Object-----//
	HTRESULT				HT_vInterface_Pick_Object( HTint, HTvector3 vecPickPos );
	//-----�� �˻�_��-----//
	HTRESULT				HT_vInterface_Pick_Map( HTvector3 );

	//--------Ȱ��ȭ�� â�� ID�� �����Ѵ�--------//
//	HTvoid					HT_vSetActiveWinID(HTint iActiveWinID);
	//-----ElapsedTime ����-----//
	HTvoid					HT_vInterface_SetElapsedTime( HTfloat );
	HTfloat					HT_fInterface_GetElapsedTime()	{	return m_fInterfaceElapsedTime;	}


	//	�׾߸��� ������ �Կ��� ���� �ӽ��ڵ�
	HTvoid					HT_vInterface_LoadCameraForBroadcast();

private:
	//	���콺�� ���� ��ư�� ������ ���
	HTvoid					HT_hrInterfaceMouseCheck_LbuttonDownPick();	

private:
	HTbool					m_bChatting_ActionSw;

	HTint					m_CursorStatus;
	HTvector3				m_CursorPos;

	HTint					m_iCursorID;

	HTbool					m_bChagedMoveDlg;

	// ���콺 Ŀ�� ��-����(hot spot)��, ��������Ʈ
	HCURSOR					m_hCursor_Normal1, m_hCursor_Normal2;
	HCURSOR					m_hCursor_RButton;
	HCURSOR					m_hCursor_Sword, m_hCursor_Sword_Ani;
	HCURSOR					m_hCursor_NPC, m_hCursor_NPC_Ani;
	HCURSOR					m_hCursor_Repair, m_hCursor_Repair_Ani;
	HCURSOR					m_hCursor_Repaird;
	HCURSOR					m_hCursor_Hand1, m_hCursor_Hand2, m_hCursor_Hand_Ani;
	HCURSOR					m_hCursor_Address_Ani, m_hCursor_Address;
	HCURSOR					m_hCursor_Party_Ani, m_hCursor_Party;
	HCURSOR					m_hCursor_Trade_Ani, m_hCursor_Trade;
	HCURSOR					m_hCursor_Blog_Ani, m_hCursor_Blog;

	HCURSOR					m_hCursor_Select_Ani, m_hCursor_Select;

	// �޸𸮿� ���ҽ��� �ε� �Ǿ������� üũ��.
	HTbool					m_bLoaded;

	HTbool					m_bPickItem;				// Item�� ���� �ִ� ���������� ����

	HTPoint					m_pMouseBackPt;				// ���� ���콺 ���갡 ���������� ��ǥ

public:
	HTbool					m_bUseWindowsCursor;

//////////////////////////////////////////////////////
	HTint					m_nMoney;	// ���Ǿ� ��ȯ �׽�Ʈ �� 2003.4.2 ����
//////////////////////////////////////////////////////

	DWORD					m_dwGetItemDelayTime;		//	������ ���ϰ� �ٽ� ���Ҷ����� ������ Ÿ��
	HTint					m_iPickItemID;				//	���� ������ keyID;

	HTfloat					m_fInterfaceElapsedTime;

	HTbool					m_bInterface_ControlKeySw;		//	��Ʈ��Ű

	HTbool					m_bUIRenderOn;

	//	�׾߸��� ������ �Կ��� ���� �ӽ��ڵ�
	HTfloat					fDefineCameraX[30];
	HTfloat					fDefineCameraY[30];
	HTfloat					fDefineCameraZ[30];
	HTfloat					fDefineCameraSpeed[30];
	HTfloat					fDefineCameraHight[30];
	HTint					iDefineCameraMode;
	HTint					iDefineCameralimitMode;

	//	�̻��ϰ� F10�� ������ �޽����� �������� �ε����ϰ� Ű������ ����
	DWORD					m_dwDelayTimeForF10;

private:
	HTbool					m_bMonHPReleased;
	HTbool					HT_bSetCharMonHPAttach();
};

#endif

