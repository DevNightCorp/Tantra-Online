//------------------------------------------------------------------------------
// HTAddress.h
// 주소창
// (주)한빛소프트 게임개발팀 서명석		2003.03.05
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

	//	입력 메세지 처리
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
	//	ESC Key 누르면 주소창 닫기
	HTvoid					HT_vAddress_ESC_CloseWindow();

	HTbool					HT_bAddress_IsClickRegistBn()	{ return m_bAddress_ReqRegistBtn; }

	//------------------------------------------------------------------------------
	// Ordinary window functions
	//------------------------------------------------------------------------------
	
	// 마우스 입력을 체크
	HTRESULT				HT_hrMouseCheck_OtherChar( HTint );		//	타 캐릭터 체크

	//------------------------------------------------------------------------------
	// Network functions
	//------------------------------------------------------------------------------
	//	주소록 초기화
	HTvoid					HT_vSCP_InitAddressBook( MSG_UpdateMessengerList* info );
	//	주소록의 정보 변경을 처리
	HTvoid					HT_vSCP_UpdateDataAddressBook( MSG_UpdateMessengerItem* info );
	//	로그인/로그아웃
	HTvoid					HT_vSCP_MSG_MessengerLogin( MSG_MessengerLogin* info );
	HTvoid					HT_vSCP_MSG_MessengerLogout( MSG_MessengerLogout* info );
	// 주소록에 등록을 요청
	HTvoid					HT_vCSP_JoinAddressBook( CHTString strName );
	HTvoid					HT_vSCP_JoinAddressBook( MSG_ReqMessenger* info );
	// 등록 대상이 등록 요청에 응답
	HTvoid					HT_vCSP_JoinAddressBookResult( BYTE );
	// 멤버를 삭제
	HTvoid					HT_vCSP_DeleteMember( CHTString );


private:
	//------------------------------------------------------------------------------
	// 메세지 출력
	//------------------------------------------------------------------------------
	HTvoid			HT_vAddress_SetMessage( HTint idMessage );
	HTvoid			HT_vAddress_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool					m_bActive;			// 주소록 윈도우

	HTbool					m_bRegister_Sw;		// 등록 스위치

	HTbool					m_bRegisterBlock;	// 등록 block 기능 스위치

	HTbool					m_bAddress_MemberDeleteBtn;		//	멤버삭제 버튼
	HTbool					m_bAddress_ReqRegistBtn;		//	등록 버튼
	HTbool					m_bAddress_ReceiveRegistBtn;	//	등록 대상의 버튼
	DWORD					m_dwAddress_OtherCharKeyID;		//	상대방의 키아이디
	HTbool					m_bAddress_DlgBoxSw;			//	질문 대화상자
	HTbool					m_bAddress_ReDlgBoxSw;			//	재질문 대화상자
	HTbool					m_bAddress_ErrorSw;				//	에러 스위치
	CHTString				m_strAddress_DlgBoxMessage;		//	질문 대화상자 메시지
	HTint					m_nAddres_MemberCount;
	HTint					m_nAddress_SelectedMember;		//	선택된 라디오 버튼 캐릭터
	CHTString				m_strAddress_SelectedName;		//	선택된 캐릭터 이름
	CHTString				m_strAddress_ReqCharName;		//	선택된 캐릭터 이름

	//PS_SCP_JOIN_ADDRESS_BOOK_NOTIFY m_pAddress_SavedChar;	//	주소록을 요청한 캐릭터의 정보

	HTbool					m_bAddress_JoinAddressResultSw;	//	등록 대상이 등록 요청에 응답

	STRUCT_MESSENGER_ITEM	m_oAddress_Item[MAX_MESSENGER];
private:
	CHTString				m_szParamString;
};


//HT_iGetSlideNo()
//HT_iGetSlideValue() + 라디오 버튼 = 현재의 라디오 버튼

