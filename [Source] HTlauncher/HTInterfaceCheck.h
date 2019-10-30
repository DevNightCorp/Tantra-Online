
#ifndef __HTINTERFACECHECK_H__
#define __HTINTERFACECHECK_H__

#define CURSOR_FILE_ARROW_1		_T("resource\\etc\\normal1.cur")	// 화살표(arrow) 커서
#define CURSOR_FILE_ARROW_2		_T("resource\\etc\\normal2.cur")
#define CURSOR_FILE_RBUTTON		_T("resource\\etc\\normal3.cur")	// 오른쪽 클릭했을 때 커서

#define CURSOR_FILE_HAND_1		_T("resource\\etc\\hand1.cur")		// 손(hand) 커서
#define CURSOR_FILE_HAND_2		_T("resource\\etc\\hand2.cur")		
#define CURSOR_FILE_HAND_ANI	_T("resource\\etc\\hand.ani")
#define CURSOR_FILE_SWORD		_T("resource\\etc\\sword.cur")		// 칼(sword) 커서
#define CURSOR_FILE_SWORD_ANI	_T("resource\\etc\\sword.ani")		
#define CURSOR_FILE_NPC			_T("resource\\etc\\npc.cur")		// 대화(NPC) 커서
#define CURSOR_FILE_NPC_ANI		_T("resource\\etc\\npc.ani")
#define CURSOR_FILE_REPAIR		_T("resource\\etc\\repair.cur")		// 수리(repair) 커서
#define CURSOR_FILE_REPAIR_ANI	_T("resource\\etc\\repair.ani")
#define CURSOR_FILE_REPAIRD		_T("resource\\etc\\repaird.cur")	// 수리 불가 커서

#define CURSOR_FILE_ADDRESS_ANI	_T("resource\\etc\\Address.ani")	// Address 화살표(arrow) 커서
#define CURSOR_FILE_ADDRESS		_T("resource\\etc\\Address.cur")
#define CURSOR_FILE_PARTY_ANI	_T("resource\\etc\\Party.ani")		// Party 화살표(arrow) 커서
#define CURSOR_FILE_PARTY		_T("resource\\etc\\Party.cur")
#define CURSOR_FILE_TRADE_ANI	_T("resource\\etc\\Trade.ani")		// Trade 화살표(arrow) 커서
#define CURSOR_FILE_TRADE		_T("resource\\etc\\Trade.cur")

#define CURSOR_FILE_BLOG_ANI	_T("resource\\etc\\blog.ani")		// Blog 접속을 위한하는 커서
#define CURSOR_FILE_BLOG		_T("resource\\etc\\blog.cur")

#define CURSOR_FILE_DUEL_ANI	_T("resource\\etc\\Select.ani")		//	기능상 캐릭터를 셀렉트 해야 될때
#define CURSOR_FILE_DUEL		_T("resource\\etc\\Select.cur")


class CHTInterfaceCheck
{
public:
	CHTInterfaceCheck();
	~CHTInterfaceCheck();

	// 로드 되었는지를 검사
	HTbool					isLoaded(){	return m_bLoaded;	};


	HTvoid					HT_vCHTInterfaceCheck_CleanUp();

	//----------담에 새로 정리 할 필요가 있는 거----------//
	HTRESULT				HT_hrInterfaceInit();
	HTRESULT				HT_hrInterfaceControl();
	HTvoid					HT_hrInterfaceControlEnd();

	//----------입출력 관련 하여 처리할것----------//
	// 이전의 입력을 모두 비운다.
	HTvoid					HT_vFlushInput();
	//-----입출력 관련 하여 처리할것_L버튼 다운-----//
	HTvoid					HT_vInterface_LbuttonDown( HTPoint );
	//-----입출력 관련 하여 처리할것_L버튼 업-----//
	HTvoid					HT_vInterface_LbuttonUp( HTPoint );
	//-----입출력 관련 하여 처리할것_L버튼 클릭-----//
	HTvoid					HT_vInterface_LbuttonClick( HTPoint );
	//-----입출력 관련 하여 처리할것_R버튼 클릭-----//
	HTvoid					HT_vInterface_RButtonClick( HTPoint );
	//-----입출력 관련 하여 처리할것_R버튼 다운-----//
	HTvoid					HT_vInterface_RButtonDown( HTPoint );
	//-----입출력 관련 하여 처리할것_R버튼 업-----//
	HTvoid					HT_vInterface_RButtonUp( HTPoint );
	//-----입출력 관련 하여 처리할것_마우스 무브-----//
	HTvoid					HT_vInterface_MouseMove( HTPoint );
	//-----입출력 관련 하여 처리할것_마우스 무브_이전것들-----//
	HTvoid					HT_vInterface_MouseMove_Cursor( HTPoint pPt, HTint nDlgNo );
	//-----입출력 관련 하여 처리할것_마우스 무브_현재-----//
//	HTvoid					HT_vInterface_MouseMove_Resent( HTPoint );

	//-----키보드 체크_Down-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_KeyDown( WPARAM );
	//-----키보드 체크_Up-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_KeyUp( WPARAM );
	//-----키보드 체크_Function Key-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_FunctionKey( WPARAM wParam );
	//	ESC키 누려면 자동으로 현재의 창들을 닫을수 있도록
	HTvoid					HT_vInterface_ESC_CloseWindow();
	//	확인/재확인창 Enter키 입력
	HTvoid					HT_vInterface_MessageWindowForEnterKey( HTint iDlgNo );
	//	컨트롤키
	HTvoid					HT_vInterface_SetControlKey( HTbool bValue )	{ m_bInterface_ControlKeySw=bValue; }
	HTbool					HT_vInterface_GetControlKey()	{	return m_bInterface_ControlKeySw;	}

	//-----키보드 체크_계속 들어오는것-----//
	HTvoid					HT_hrInterfaceKeyboard_Input_Continue();

	HTvoid					HT_vSetCursor(HTint iID);			// 커서 모양을 지정
	HTint					HT_iGetCursor(){ return m_iCursorID; };			// 커서 모양을 얻어옴

	HCURSOR					HT_hLoadCursor(CHTString szFile);
	HTvoid					HT_vRanderCursor();

	//-----공격시에 입력이 들어오면 공격 해제-----//
	HTvoid					HT_vInterface_AttackModeTrans( HTint nModelID );
	//-----픽 검색_아이템-----//
	HTRESULT				HT_vInterface_Pick_Item( HTint, HTPoint );
	//-----픽 검색_OtherCharter-----//
	HTRESULT				HT_vInterface_Pick_OtherChar( HTint );
	//-----픽 검색_NPC-----//
	HTRESULT				HT_vInterface_Pick_NPC( HTint );
	//-----픽 검색_Object-----//
	HTRESULT				HT_vInterface_Pick_Object( HTint, HTvector3 vecPickPos );
	//-----픽 검색_맵-----//
	HTRESULT				HT_vInterface_Pick_Map( HTvector3 );

	//--------활성화된 창의 ID로 갱신한다--------//
//	HTvoid					HT_vSetActiveWinID(HTint iActiveWinID);
	//-----ElapsedTime 갱신-----//
	HTvoid					HT_vInterface_SetElapsedTime( HTfloat );
	HTfloat					HT_fInterface_GetElapsedTime()	{	return m_fInterfaceElapsedTime;	}


	//	그야말로 동영상 촬영을 위한 임시코드
	HTvoid					HT_vInterface_LoadCameraForBroadcast();

private:
	//	마우스가 왼쪽 버튼이 눌렸을 경우
	HTvoid					HT_hrInterfaceMouseCheck_LbuttonDownPick();	

private:
	HTbool					m_bChatting_ActionSw;

	HTint					m_CursorStatus;
	HTvector3				m_CursorPos;

	HTint					m_iCursorID;

	HTbool					m_bChagedMoveDlg;

	// 마우스 커서 핫-스폿(hot spot)과, 스프라이트
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

	// 메모리에 리소스가 로딩 되었는지를 체크함.
	HTbool					m_bLoaded;

	HTbool					m_bPickItem;				// Item을 집고 있는 상태인지를 저장

	HTPoint					m_pMouseBackPt;				// 이전 마우스 무브가 들어왔을때의 좌표

public:
	HTbool					m_bUseWindowsCursor;

//////////////////////////////////////////////////////
	HTint					m_nMoney;	// 루피아 교환 테스트 용 2003.4.2 선미
//////////////////////////////////////////////////////

	DWORD					m_dwGetItemDelayTime;		//	아이템 픽하고 다시 픽할때까지 딜레이 타임
	HTint					m_iPickItemID;				//	픽한 아이템 keyID;

	HTfloat					m_fInterfaceElapsedTime;

	HTbool					m_bInterface_ControlKeySw;		//	컨트롤키

	HTbool					m_bUIRenderOn;

	//	그야말로 동영상 촬영을 위한 임시코드
	HTfloat					fDefineCameraX[30];
	HTfloat					fDefineCameraY[30];
	HTfloat					fDefineCameraZ[30];
	HTfloat					fDefineCameraSpeed[30];
	HTfloat					fDefineCameraHight[30];
	HTint					iDefineCameraMode;
	HTint					iDefineCameralimitMode;

	//	이상하게 F10을 윈도우 메시지로 잡지못해 부득이하게 키딜레이 변수
	DWORD					m_dwDelayTimeForF10;

private:
	HTbool					m_bMonHPReleased;
	HTbool					HT_bSetCharMonHPAttach();
};

#endif

