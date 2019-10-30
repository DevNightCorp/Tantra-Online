//------------------------------------------------------------------------------
// HTAddress.h
// �ּ�â
// (��)�Ѻ�����Ʈ ���Ӱ����� ����		2003.03.05
//------------------------------------------------------------------------------
#include "HTControlDef.h"
#pragma once

class HTAddress
{
public:
	HTAddress(void);
	~HTAddress(void);

	//------------------------------------------------------------------------------
	// Load / Unload
	//------------------------------------------------------------------------------
	HTvoid					HT_vAddress_Delete();
	HTvoid					HT_vAddress_Init();
	//	Create Window
	HTvoid					HT_vAddress_CreateWindow();

	//	�Է� �޼��� ó��
	//	Address
	static void				HT_vAddress_InputCheckForAddress(int iAction, int iTarget, int iTargetID);

	//	Set Contents in Window
	HTvoid					HT_vAddress_SetContentsInWnd( HTint iScrollValue );

	//------------------------------------------------------------------------------
	// Active / Deactive
	//------------------------------------------------------------------------------
	HTvoid					HT_vSetOn();
	HTvoid					HT_vSetOff();
	HTbool					HT_iIsOn()		{	return m_bActive;		}
	//	ESC Key ������ �ּ�â �ݱ�
	HTvoid					HT_vAddress_ESC_CloseWindow();

	HTbool					HT_bAddress_IsClickRegistBn()	{ return m_bAddress_ReqRegistBtn; }

	//------------------------------------------------------------------------------
	// Ordinary window functions
	//------------------------------------------------------------------------------
	
	// ���콺 �Է��� üũ
	HTRESULT				HT_hrMouseCheck_OtherChar( HTint );		//	Ÿ ĳ���� üũ

	//------------------------------------------------------------------------------
	// Network functions
	//------------------------------------------------------------------------------
	//	�ּҷ� �ʱ�ȭ
	HTvoid					HT_vSCP_InitAddressBook( MSG_UpdateMessengerList* info );
	//	�ּҷ��� ���� ������ ó��
	HTvoid					HT_vSCP_UpdateDataAddressBook( MSG_UpdateMessengerItem* info );
	//	�α���/�α׾ƿ�
	HTvoid					HT_vSCP_MSG_MessengerLogin( MSG_MessengerLogin* info );
	HTvoid					HT_vSCP_MSG_MessengerLogout( MSG_MessengerLogout* info );
	// �ּҷϿ� ����� ��û
	HTvoid					HT_vCSP_JoinAddressBook( CHTString strName );
	HTvoid					HT_vSCP_JoinAddressBook( MSG_ReqMessenger* info );
	// ��� ����� ��� ��û�� ����
	HTvoid					HT_vCSP_JoinAddressBookResult( BYTE );
	// ����� ����
	HTvoid					HT_vCSP_DeleteMember( CHTString );


private:
	//------------------------------------------------------------------------------
	// �޼��� ���
	//------------------------------------------------------------------------------
	HTvoid			HT_vAddress_SetMessage( HTint idMessage );
	HTvoid			HT_vAddress_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool					m_bActive;			// �ּҷ� ������

	HTbool					m_bRegister_Sw;		// ��� ����ġ

	HTbool					m_bRegisterBlock;	// ��� block ��� ����ġ

	HTbool					m_bAddress_MemberDeleteBtn;		//	������� ��ư
	HTbool					m_bAddress_ReqRegistBtn;		//	��� ��ư
	HTbool					m_bAddress_ReceiveRegistBtn;	//	��� ����� ��ư
	DWORD					m_dwAddress_OtherCharKeyID;		//	������ Ű���̵�
	HTbool					m_bAddress_DlgBoxSw;			//	���� ��ȭ����
	HTbool					m_bAddress_ReDlgBoxSw;			//	������ ��ȭ����
	HTbool					m_bAddress_ErrorSw;				//	���� ����ġ
	CHTString				m_strAddress_DlgBoxMessage;		//	���� ��ȭ���� �޽���
	HTint					m_nAddres_MemberCount;
	HTint					m_nAddress_SelectedMember;		//	���õ� ���� ��ư ĳ����
	CHTString				m_strAddress_SelectedName;		//	���õ� ĳ���� �̸�
	CHTString				m_strAddress_ReqCharName;		//	���õ� ĳ���� �̸�

	//PS_SCP_JOIN_ADDRESS_BOOK_NOTIFY m_pAddress_SavedChar;	//	�ּҷ��� ��û�� ĳ������ ����

	HTbool					m_bAddress_JoinAddressResultSw;	//	��� ����� ��� ��û�� ����

	STRUCT_MESSENGER_ITEM	m_oAddress_Item[MAX_MESSENGER];
private:
	CHTString				m_szParamString;
};


//HT_iGetSlideNo()
//HT_iGetSlideValue() + ���� ��ư = ������ ���� ��ư

