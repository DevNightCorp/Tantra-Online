#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTApplication.h"
#include "HTInterfaceCheck.h"
//#include "HTNotifyWindow.h"

#define NUMBER_KEYVALUE_0		0x30
#define NUMBER_KEYVALUE_1		0x31
#define NUMBER_KEYVALUE_2		0x32
#define NUMBER_KEYVALUE_3		0x33
#define NUMBER_KEYVALUE_4		0x34
#define NUMBER_KEYVALUE_5		0x35
#define NUMBER_KEYVALUE_6		0x36
#define NUMBER_KEYVALUE_7		0x37
#define NUMBER_KEYVALUE_8		0x38
#define NUMBER_KEYVALUE_9		0x39

#define ALPAHBAT_KEYVALUE_A		0x41
#define ALPAHBAT_KEYVALUE_B		0x42
#define ALPAHBAT_KEYVALUE_C		0x43
#define ALPAHBAT_KEYVALUE_D		0x44
#define ALPAHBAT_KEYVALUE_E		0x45
#define ALPAHBAT_KEYVALUE_F		0x46
#define ALPAHBAT_KEYVALUE_G		0x47
#define ALPAHBAT_KEYVALUE_H		0x48
#define ALPAHBAT_KEYVALUE_I		0x49
#define ALPAHBAT_KEYVALUE_J		0x4A
#define ALPAHBAT_KEYVALUE_K		0x4B
#define ALPAHBAT_KEYVALUE_L		0x4C
#define ALPAHBAT_KEYVALUE_M		0x4D
#define ALPAHBAT_KEYVALUE_N		0x4E
#define ALPAHBAT_KEYVALUE_O		0x4F
#define ALPAHBAT_KEYVALUE_P		0x50
#define ALPAHBAT_KEYVALUE_Q		0x51
#define ALPAHBAT_KEYVALUE_R		0x52
#define ALPAHBAT_KEYVALUE_S		0x53
#define ALPAHBAT_KEYVALUE_T		0x54
#define ALPAHBAT_KEYVALUE_U		0x55
#define ALPAHBAT_KEYVALUE_V		0x56
#define ALPAHBAT_KEYVALUE_W		0x57
#define ALPAHBAT_KEYVALUE_X		0x58
#define ALPAHBAT_KEYVALUE_Y		0x59
#define ALPAHBAT_KEYVALUE_Z		0x5A

#define ALPAHBAT_KEYVALUE_SUBTRACT		0xBD
#define ALPAHBAT_KEYVALUE_ADD			0xBB

//int g_iGlobalKey;
//int g_iGlobalKeyE;
//int g_iGlobalKeyR;
//int g_iGlobalKeyF;

CHTInterfaceCheck::CHTInterfaceCheck()
{
	m_bChatting_ActionSw		= HT_TRUE;

	m_iCursorID					= CURSOR_ARROW_1;			// 처음의 커서는 일반 화살표이다.

	m_bUseWindowsCursor			= HT_FALSE;

	// 처음에는 집은 ITEM이 없음.
	m_bPickItem = HT_FALSE;

	m_hCursor_Normal1 = m_hCursor_Normal2 = HT_NULL;
	m_hCursor_Sword = m_hCursor_Sword_Ani = HT_NULL;
	m_hCursor_NPC = m_hCursor_NPC_Ani = HT_NULL;
	m_hCursor_Repair = m_hCursor_Repair_Ani = HT_NULL;
	m_hCursor_Repaird = HT_NULL;
	m_hCursor_Hand1 = m_hCursor_Hand2 = m_hCursor_Hand_Ani = HT_NULL;

	m_bInterface_ControlKeySw = HT_FALSE;

	m_bChagedMoveDlg			= HT_FALSE;
	m_bUIRenderOn				= HT_TRUE;
	m_bMonHPReleased			= HT_FALSE;
	g_bShowUI					= HT_TRUE;
	g_iShowUI					= 0;
	//	OnChar Message Skip
	g_bSkipMessageOnChar		= HT_FALSE;
//	g_iGlobalKey = 0;
//	g_iGlobalKeyE = 0;
//	g_iGlobalKeyR = 0;
//	g_iGlobalKeyF = 0;
}

CHTInterfaceCheck::~CHTInterfaceCheck()
{
}


//----------초기화----------//
HTRESULT CHTInterfaceCheck::HT_hrInterfaceInit()
{
	m_bUseWindowsCursor = g_pEngineHandler->HT_bIsWindowCursor();

	//-----커서-----//
	// 화살표 커서 로딩
	m_hCursor_Normal1 = HT_hLoadCursor(CURSOR_FILE_ARROW_1);
	m_hCursor_Normal2 = HT_hLoadCursor(CURSOR_FILE_ARROW_2);
	// 오른쪽버튼 클릭 커서
	m_hCursor_RButton = HT_hLoadCursor(CURSOR_FILE_RBUTTON);
	// 칼모양 커서 로딩
	m_hCursor_Sword = HT_hLoadCursor(CURSOR_FILE_SWORD);
	m_hCursor_Sword_Ani = HT_hLoadCursor(CURSOR_FILE_SWORD_ANI);
	// NPC 커서 로딩
//	m_hCursor_NPC = HT_hLoadCursor(CURSOR_FILE_NPC);
	m_hCursor_NPC_Ani = HT_hLoadCursor(CURSOR_FILE_NPC_ANI);
	// 수리 커서 로딩
	m_hCursor_Repair = HT_hLoadCursor(CURSOR_FILE_REPAIR);
	m_hCursor_Repair_Ani = HT_hLoadCursor(CURSOR_FILE_REPAIR_ANI);
	m_hCursor_Repaird = HT_hLoadCursor(CURSOR_FILE_REPAIRD);
	// 손모양 커서 로딩
	m_hCursor_Hand1 = HT_hLoadCursor(CURSOR_FILE_HAND_1);
	m_hCursor_Hand2 = HT_hLoadCursor(CURSOR_FILE_HAND_2);
	m_hCursor_Hand_Ani = HT_hLoadCursor(CURSOR_FILE_HAND_ANI);

	// Address 화살표 커서 로딩
	m_hCursor_Address = HT_hLoadCursor(CURSOR_FILE_ADDRESS);
	m_hCursor_Address_Ani = HT_hLoadCursor(CURSOR_FILE_ADDRESS_ANI);
	// Party 화살표 커서 로딩
	m_hCursor_Party = HT_hLoadCursor(CURSOR_FILE_PARTY);
	m_hCursor_Party_Ani = HT_hLoadCursor(CURSOR_FILE_PARTY_ANI);
	// Trade 화살표 커서 로딩
	m_hCursor_Trade = HT_hLoadCursor(CURSOR_FILE_TRADE);
	m_hCursor_Trade_Ani = HT_hLoadCursor(CURSOR_FILE_TRADE_ANI);

	// Blog를 접근을 위한 커서
	m_hCursor_Blog = HT_hLoadCursor(CURSOR_FILE_BLOG);
	m_hCursor_Blog_Ani = HT_hLoadCursor(CURSOR_FILE_BLOG_ANI);

	//	Cursor For Select
	m_hCursor_Select = HT_hLoadCursor(CURSOR_FILE_DUEL);
	m_hCursor_Select_Ani = HT_hLoadCursor(CURSOR_FILE_DUEL_ANI);

	// 리소스가 메모리에 로드 되었음
	m_bLoaded = HT_TRUE;

	//	아이템 픽하고 다시 픽할때까지 딜레이 타임
	m_dwGetItemDelayTime = GetTickCount();
	m_iPickItemID = 0;

	//	이상하게 F10을 윈도우 메시지로 잡지못해 부득이하게 키딜레이 변수
	m_dwDelayTimeForF10 = GetTickCount();

	return HT_OK;
}

HTvoid CHTInterfaceCheck::HT_vCHTInterfaceCheck_CleanUp()
{

	//-----커서-----//
	// 화살표 커서 삭제
	if( m_hCursor_Normal1 != HT_NULL)
	{
		DestroyCursor(m_hCursor_Normal1);
		m_hCursor_Normal1 = HT_NULL;
	}
	if( m_hCursor_Normal2 != HT_NULL)
	{
		DestroyCursor(m_hCursor_Normal2);
		m_hCursor_Normal2 = HT_NULL;
	}
	// 오른쪽 버튼 클릭 커서 삭제
	if( m_hCursor_RButton != HT_NULL )
	{
		DestroyCursor(m_hCursor_RButton);
		m_hCursor_RButton = HT_NULL;
	}
	// 칼모양 커서 삭제
	if( m_hCursor_Sword != HT_NULL)
	{
		DestroyCursor(m_hCursor_Sword);
		m_hCursor_Sword = HT_NULL;
	}
	if( m_hCursor_Sword_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Sword_Ani);
		m_hCursor_Sword_Ani = HT_NULL;
	}
	// NPC 커서 삭제
/*	if( m_hCursor_NPC != HT_NULL)
	{
		DestroyCursor(m_hCursor_NPC);
		m_hCursor_NPC = HT_NULL;
	}
*/	if( m_hCursor_NPC_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_NPC_Ani);
		m_hCursor_NPC_Ani = HT_NULL;
	}
	// 수리 커서 삭제
	if( m_hCursor_Repair != HT_NULL)
	{
		DestroyCursor(m_hCursor_Repair);
		m_hCursor_Repair = HT_NULL;
	}
	if( m_hCursor_Repair_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Repair_Ani);
		m_hCursor_Repair_Ani = HT_NULL;
	}
	if( m_hCursor_Repaird != HT_NULL)
	{
		DestroyCursor(m_hCursor_Repaird);
		m_hCursor_Repaird = HT_NULL;
	}
	// 손모양 커서 삭제
	if( m_hCursor_Hand1 != HT_NULL)
	{
		DestroyCursor(m_hCursor_Hand1);
		m_hCursor_Hand1 = HT_NULL;
	}
	if( m_hCursor_Hand2 != HT_NULL)
	{
		DestroyCursor(m_hCursor_Hand2);
		m_hCursor_Hand2 = HT_NULL;
	}
	if( m_hCursor_Hand_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Hand_Ani);
		m_hCursor_Hand_Ani = HT_NULL;
	}
	
	// Address 화살표 커서 삭제
	if( m_hCursor_Address != HT_NULL)
	{
		DestroyCursor(m_hCursor_Address);
		m_hCursor_Address = HT_NULL;
	}
	if( m_hCursor_Address_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Address_Ani);
		m_hCursor_Address_Ani = HT_NULL;
	}
	// Party 화살표 커서 삭제
	if( m_hCursor_Party != HT_NULL)
	{
		DestroyCursor(m_hCursor_Party);
		m_hCursor_Party = HT_NULL;
	}
	if( m_hCursor_Party_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Party_Ani);
		m_hCursor_Party_Ani = HT_NULL;
	}
	// Trade 화살표 커서 삭제
	if( m_hCursor_Trade != HT_NULL)
	{
		DestroyCursor(m_hCursor_Trade);
		m_hCursor_Trade = HT_NULL;
	}
	if( m_hCursor_Trade_Ani != HT_NULL)
	{
		DestroyCursor(m_hCursor_Trade_Ani);
		m_hCursor_Trade_Ani = HT_NULL;
	}

	// Blog 커서 삭제
	if ( m_hCursor_Blog != HT_NULL )
	{
		DestroyCursor( m_hCursor_Blog );
		m_hCursor_Blog = HT_NULL;
	}
	if ( m_hCursor_Blog_Ani != HT_NULL )
	{
		DestroyCursor( m_hCursor_Blog_Ani );
		m_hCursor_Blog_Ani = HT_NULL;
	}

	//	결투 시스템 커서 삭제
	if ( m_hCursor_Select != HT_NULL )
	{
		DestroyCursor( m_hCursor_Select );
		m_hCursor_Select = HT_NULL;
	}
	if ( m_hCursor_Select_Ani != HT_NULL )
	{
		DestroyCursor( m_hCursor_Select_Ani );
		m_hCursor_Select_Ani = HT_NULL;
	}

	// 리소스가 메모리에 언로드 되었음
	m_bLoaded = HT_FALSE;
}

//---------- 커서 핸들 로딩 -------------//
HCURSOR CHTInterfaceCheck::HT_hLoadCursor(CHTString szFile)
{
	TCHAR szFullFile[MAX_PATH];
	GetFullPathName( szFile, MAX_PATH, szFullFile, NULL );
	
	return LoadCursorFromFile(szFullFile);
}

//--------- 커서 모양을 지정 ------------//
HTvoid CHTInterfaceCheck::HT_vSetCursor(HTint iID)
{
	m_iCursorID = iID;	
	HT_vRanderCursor();
}

HTvoid CHTInterfaceCheck::HT_vRanderCursor()
{
	switch(m_iCursorID)
	{
		// 화살표 커서
		case CURSOR_ARROW_1 :
		{
			if( m_hCursor_Normal1 != HT_NULL)
			{
				SetCursor(m_hCursor_Normal1);
			}
		}
			break;
		case CURSOR_ARROW_2 :	
		{
			if( m_hCursor_Normal2 != HT_NULL)
			{
				SetCursor(m_hCursor_Normal2);
			}
		}
			break;
		// 손모양 커서
		case CURSOR_HAND_1 :
		{
			if( m_hCursor_Hand1 != HT_NULL)
			{
				SetCursor(m_hCursor_Hand1);
			}
		}
			break;
		case CURSOR_HAND_2 :
		{
			if( m_hCursor_Hand2 != HT_NULL)
			{
				SetCursor(m_hCursor_Hand2);
			}
		}
			break;
		case CURSOR_HAND_ANI :
		{
			if( m_hCursor_Hand_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Hand_Ani);
			}
		}
			break;
		//칼모양 커서
		case CURSOR_SWORD :
		{
			if( m_hCursor_Sword != HT_NULL)
			{
				SetCursor(m_hCursor_Sword);
			}
		}
			break;
		case CURSOR_SWORD_ANI :
		{
			if( m_hCursor_Sword_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Sword_Ani);
			}
		}
			break;
		// NPC 커서
		case CURSOR_NPC :
		{
			if( m_hCursor_NPC != HT_NULL)
			{
				SetCursor(m_hCursor_NPC);
			}
		}
			break;
		case CURSOR_NPC_ANI :
		{
			if( m_hCursor_NPC_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_NPC_Ani);
			}
		}
			break;
		// 수리 커서
		case CURSOR_REPAIR :
		{
			if( m_hCursor_Repair != HT_NULL)
			{
				SetCursor(m_hCursor_Repair);
			}
		}
			break;
		case CURSOR_REPAIR_ANI :
		{
			if( m_hCursor_Repair_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Repair_Ani);
			}
		}
			break;
		case CURSOR_REPAIRD :
		{
			if( m_hCursor_Repaird != HT_NULL)
			{
				SetCursor(m_hCursor_Repaird);
			}
		}
			break;
		// Address 화살표 커서
		case CURSOR_ADDRESS :
		{
			if( m_hCursor_Address != HT_NULL)
			{
				SetCursor(m_hCursor_Address);
			}
		}
			break;
		case CURSOR_ADDRESS_ANI :	
		{
			if( m_hCursor_Address_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Address_Ani);
			}
		}
			break;
		// Party 화살표 커서
		case CURSOR_PARTY :
		{
			if( m_hCursor_Party != HT_NULL)
			{
				SetCursor(m_hCursor_Party);
			}
		}
			break;
		case CURSOR_PARTY_ANI :	
		{
			if( m_hCursor_Party_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Party_Ani);
			}
		}
			break;
		// Trade 화살표 커서
		case CURSOR_TRADE :
		{
			if( m_hCursor_Trade != HT_NULL)
			{
				SetCursor(m_hCursor_Trade);
			}
		}	break;
		case CURSOR_TRADE_ANI :	
		{
			if( m_hCursor_Trade_Ani != HT_NULL)
			{
				SetCursor(m_hCursor_Trade_Ani);
			}
		}	break;
		// Blog 커서
		case CURSOR_BLOG :
		{
			if ( m_hCursor_Blog != HT_NULL ) SetCursor( m_hCursor_Blog );
		}	break;
		case CURSOR_BLOG_ANI :
		{
			if ( m_hCursor_Blog_Ani != HT_NULL ) SetCursor( m_hCursor_Blog_Ani );
		}	break;
		// Duel 커서
		case CURSOR_SELECT :
		{
			if ( m_hCursor_Select != HT_NULL ) SetCursor( m_hCursor_Select );
		}	break;
		case CURSOR_SELECT_ANI :
		{
			if ( m_hCursor_Select_Ani != HT_NULL ) SetCursor( m_hCursor_Select_Ani );
		}	break;
		// 오른쪽 버튼 클릭
		case CURSOR_RBUTTON :
		{
			if( m_hCursor_RButton != HT_NULL)
			{
				SetCursor(m_hCursor_RButton);
			}
		}
			break;

		default:
			break;
	}
}

//----------인터페이스 컨트롤 부분----------//
HTvoid CHTInterfaceCheck::HT_vFlushInput()
{
	// 이전의 마우스 클릭, 키보드 입력 등은 무시한다.
	g_iInterface.bLbuttonDbClk = HT_FALSE;
	g_iInterface.bRbuttonDbClk = HT_FALSE;
	g_iInterface.iLeftClick = HT_FALSE;
	g_iInterface.iRightClick = HT_FALSE;
}


HTRESULT CHTInterfaceCheck::HT_hrInterfaceControl()
{
	//-----키보드 체크_계속 들어오는것-----//
	this->HT_hrInterfaceKeyboard_Input_Continue();
	
	return HT_OK;
}

//----------입출력 관련 하여 처리할것----------//
//-----입출력 관련 하여 처리할것_L버튼 다운-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonDown( HTPoint pPt )
{
}

//-----입출력 관련 하여 처리할것_L버튼 업-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonUp( HTPoint pPt )
{
	// L버튼 업시에 처리해야 할 여러가지 일들
	g_cQuest->HT_vMouseSlideBarUp();	
}


//-----입출력 관련 하여 처리할것_L버튼 클릭-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonClick( HTPoint pPt )
{ 
	//	입력을 받음으로 해서 자동 대기모드 취소
	g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	전광판 메시지 체크
	if(HT_SUCCEED(g_cChatting->HT_hrChatting_SetPickOpenMsgWnd(pPt)))
		return;

	//----------픽---------//
	// 개인상점 개설 중이거나 열람 중이면 처리하지 않음
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) )
		return;

	HTint iObject_ID;
	HTIntersectInfo oInfo;
	HTbool bPickMainChar = HT_FALSE;
	if ( HT_FAILED( g_pEngineHandler->HT_hrPick( pPt.x, pPt.y, &iObject_ID, &oInfo, &bPickMainChar )))		{	return; }
	g_imsi_button[0] = (HTfloat)iObject_ID;

	//	메인캐리겉 클릭되어 있을때는 조건없이 해제하고
	g_cMainCharacter->HT_vMainCharMyselfUndoClick();

	//-----픽 검색_아이템-----//
	if( HT_SUCCEED( HT_vInterface_Pick_Item( iObject_ID, pPt ) ) )
	{	
		g_pMainBar->HT_vSetObjectHPOut();
		return;
	}

	if( iObject_ID > 0 )
	{
		g_cParty->m_party_DeleteMember = 255;	// 픽 될때마다 선택된 파티명 지워줌

		//----------맵위의 픽업된 아이템 초기화 및 아이템 정보창 초기화----------//
		g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
		//----------OtherObjectSystem 정보창 초기화---------//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
		//----------NPC 정보창 초기화---------//
		g_sNPCSystem->HT_vNPCSystem_HPWindowInit();

        HTbool	bPickSw = HT_FALSE;
		//-----픽 검색_OtherObject-----//
		if( HT_SUCCEED( HT_vInterface_Pick_OtherChar( iObject_ID ) ) )						{	return;	}//bPickSw = HT_TRUE; }
		//-----픽 검색_NPC-----//
		if( HT_SUCCEED( HT_vInterface_Pick_NPC( iObject_ID ) ) )							{	bPickSw = HT_TRUE; }
		//-----픽 검색_Object-----//
		if( HT_SUCCEED( HT_vInterface_Pick_Object( iObject_ID, oInfo.m_vecPosition ) ) )	{	bPickSw = HT_TRUE; }
		if( bPickSw )
            return;
	}

	//	MainChar가 클릭되었는지 파악하고 클릭되었다면 그에 따른처리
	if ( bPickMainChar )
	{
		if( g_cCamera.HT_nCamera_GetCameraTypeEye() != CAMERATYPE_EYE_FRONTVIEW )
		{
			g_cMainCharacter->HT_vMainCharMyselfClick();
			return;
		}
	}
	
	//-----픽 검색_맵-----//
	HT_vInterface_Pick_Map( oInfo.m_vecPosition );
}

//----------RButton 클릭 체크----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonDown( HTPoint pPt )
{
	// 아이템을 집고 있는 상태이면 처리하지 않음.
	//if( m_bPickItem ) return;
	// 카메라 조절 셋팅
	g_cCamera.HT_vCamera_SetInput_On( pPt );
}


//----------RButton 클릭 체크----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonUp( HTPoint pPt )
{
	// 카메라 조절 모드 해제
	g_cCamera.HT_vCamera_SetInput_Off();
}

//----------RButton 클릭 체크----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonClick( HTPoint pPt )
{
}

//-----입출력 관련 하여 처리할것_마우스 무브-----//
HTvoid CHTInterfaceCheck::HT_vInterface_MouseMove( HTPoint pPt )
{
	HTint nDlgNo = -1;
	// 커서
	HT_vInterface_MouseMove_Cursor( pPt, nDlgNo );

	//----------카메라_외부에서 셋팅_업/다운/회전----------//
	if( g_cCamera.HT_vCamera_GetInputSw() == HT_TRUE )
	{
		g_cCamera.HT_vCamera_SetUpDownRotate( pPt, m_fInterfaceElapsedTime );
	}

	// 먼저 몬스터/캐릭터/NPC에 오버시라면 UI시스템에 의존하지 않는 툴팁을 띄운다.
	g_cUIManager->bRenderNPC = false;
	HTint iObjID = g_pEngineHandler->HT_iGetObjectOnMouse(pPt.x, pPt.y);
	if(iObjID > -1)
	{
		g_cUIManager->bRenderNPC = true;
		// HT_vObjectInfo_Active()에서 정보를 얻어오면서 몬스터인지 캐릭터인지 구분해줘야한다.
		//	방송촬영을 위해 몬스터 타겥팅 애니매이션이 안보이게 하기 위해
		if( !g_bGamePlayMovieForGlobal )
		{
			g_cObjectInfo->HT_vObjectInfo_Active_NPC(iObjID);
			return;
		}
	}

	// UI 시스템에 마우스 무빙시에 대화상자 움직이도록 셋팅
	m_pMouseBackPt.x = pPt.x;
	m_pMouseBackPt.y = pPt.y;

	g_cQuest->HT_vMouseSlideBarMove();
}

//----- 마우스가 움직일 때마다 커서 전환 처리 -----//
HTvoid CHTInterfaceCheck::HT_vInterface_MouseMove_Cursor( HTPoint  pPt, HTint nDlgNo )
{
	//-----------------------------------------------------------------
	// 커서 전환을 처리한다.
	//-----------------------------------------------------------------
	HTbool	bCursorConfined = HT_FALSE;	// 커서가 확정 되었는지를 검사

	// 오른쪽 버튼이 클릭된 상태면
	if( g_iInterface.iRightDown == HT_TRUE )
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor(CURSOR_RBUTTON);

		bCursorConfined = HT_TRUE;		// 커서 확정
	}
	// 현재 수리 또는 해체모드일 경우 : 확인 메세지가 뜨지 않았을 때
	else if( g_cNPCControl->HT_bNPCControl_IsItemFixActive() && (g_cNPCControl->HT_bNPCControl_IsMessageWinActive() == HT_FALSE) )
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor(CURSOR_REPAIR_ANI);	// 망치모양

		bCursorConfined = HT_TRUE;		// 커서 확정
	}
	// 마우스 포인트가 PC/NPC 인벤토리 창 위에 있는지 체크하고 커서 변환
	// 판매모드일 경우 일반 커서 모양으로 설정
	else if( nDlgNo == _DIALOG_INVEN && g_cNPCControl->HT_bNPCControl_IsItemDisjointActive() == HT_FALSE )	// PC 인벤토리 
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1 );	// 손모양

		bCursorConfined = HT_TRUE;		// 커서 확정
	}
	// NPC 인벤토리
	else if( nDlgNo == _DIALOG_GOODSKEEPWND )	
	{	
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1);	// 손모양

		bCursorConfined = HT_TRUE;		// 커서 확정
	}
	// 아이템 리스트 창위에 마우스가 있으면
	else if( nDlgNo == _DIALOG_MERCHANT )	
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1);	// 손모양

		bCursorConfined = HT_TRUE;		// 커서 확정
	}
	else 
	{
		// 커서 위의 오브젝트를 구한다.
		DWORD dwObjectModelID = g_pEngineHandler->HT_iGetObjectOnMouse(pPt.x, pPt.y);
		DWORD dwIndex;
				
		// 맵위에 있는 아이템일 경우 움직이는 손으로 바꾼다.
		if( !bCursorConfined && (g_cItemSystem->HT_dwSystem_GetItemKeyFromModelID( dwObjectModelID, HT_FALSE ) != 0) )	
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor(CURSOR_HAND_ANI);
			bCursorConfined = HT_TRUE;		// 커서 확정
		}
		// 다른 캐릭터 위에 있는 경우 PK존을 검사해 칼로 바꾼다.
		HTint iObjectKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( dwObjectModelID );
		if( !bCursorConfined && ( iObjectKeyID != 0 ) )
		{
			if( SERVEROBJECT_IS_MONSTER( iObjectKeyID ) )	// 몬스터일 경우
			{
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					HT_vSetCursor( CURSOR_SWORD_ANI );
				bCursorConfined = HT_TRUE;		// 커서 확정
			}
			else	// 캐릭터일 경우
			{
                HTPoint pCharCell = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
				// 지금 서 있는 위치가 PK가능한 지역이고 PK버튼을 누른 상태이면 커서를 칼로 바꾼다.
				if( g_pEngineHandler->HT_bIsCellSafeZone( pCharCell.x, pCharCell.y, 0 ) == HT_FALSE )
				{
					//if( g_pMainBar->HT_bGetPKButton() ||
					//	g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
					//{
					//	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					//		HT_vSetCursor( CURSOR_SWORD_ANI );
					//	bCursorConfined = HT_TRUE;		// 커서 확정
					//}
				}
			}
		}
		// NPC위에 있는 경우 범위를 검사해 말풍선으로 바꾼다.
		if( !bCursorConfined && ((dwIndex = g_sNPCSystem->HT_pNPCSystem_GetIndexFromModelID( dwObjectModelID )) != 0) ) // NPC일 경우
		{
			// NPC의 셀 위치를 구함
			HTPoint pNPCCellPos = g_sNPCSystem->HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
			HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
			pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
			pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;

			// x, y의 떨어진 셀이 6보다 작으면 대화를 승인 할 수 있으므로 커서를 전환(대화커서로)
			if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x <= NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
			{
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					HT_vSetCursor( CURSOR_NPC_ANI );
				bCursorConfined = HT_TRUE;		// 커서 확정
			}
		}
		// 파티 등록 버튼 누른 상태이면
		if( !bCursorConfined 
				&& g_cParty->HT_bParty_IsClickJoinBn() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_PARTY_ANI );

			bCursorConfined = HT_TRUE;		// 커서 확정
		}
		// 주소록 등록 버튼 누른 상태이면
		if( !bCursorConfined 
			&& g_cUIManager->HT_isShowWindow( _DIALOG_ADDRESS ) && g_cAddress->HT_bAddress_IsClickRegistBn() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_ADDRESS_ANI );

			bCursorConfined = HT_TRUE;		// 커서 확정
		}
		// Trade 버튼 누른 상태이면
		if( !bCursorConfined && g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_TRADE_ANI );

			bCursorConfined = HT_TRUE;		// 커서 확정
		}
		// Blog 관련 버튼을 누른 상태라면
		if ( !bCursorConfined && g_eBlogAccessStatus == HT_BLOGACCESSSTATUS_READY )
		{
			if( g_cInterfaceCheck->m_hCursor_Blog_Ani == HT_FALSE ) HT_vSetCursor( CURSOR_BLOG );
			bCursorConfined = HT_TRUE;
		}
		// Blog 관련 버튼을 누른 상태라면
		if ( !bCursorConfined && g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Request || !bCursorConfined && g_cGuildSystem->m_nAshuramGuildJoinMode == 1)
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_SELECT_ANI );
			bCursorConfined = HT_TRUE;
		}

		// 커서가 확정되지 않았으면 화살표 커서로 한다.
		if( !bCursorConfined )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			{
				HT_vSetCursor( CURSOR_ARROW_1 );
			}
		}
	}
}

//-----공격시에 입력이 들어오면 공격 해제-----//
HTvoid CHTInterfaceCheck::HT_vInterface_AttackModeTrans( HTint nModelID )
{
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 27 );
}

//-----픽 검색_아이템-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Item( HTint iObject_ID, HTPoint pPt )
{
	//-----맵위의 아이템 체크-----//
	HTint iTempID = g_cItemSystem->HT_iSystem_ComIDCheck( iObject_ID, pPt );
	if( iTempID != 0 )
	{
		DWORD dwPassTime = GetTickCount();
		if( dwPassTime < m_dwGetItemDelayTime + 5000 )
		{
			if( m_iPickItemID != iTempID )
			{
				m_iPickItemID = iTempID;
			}
			else
				return HT_OK;
		}
		
		//	아이템 픽하고 다시 픽할때까지 딜레이 타임
		m_dwGetItemDelayTime = GetTickCount();

		g_pEngineHandler->HT_hrPlaySound( 33524, 1 );	// Click Sound

		//-----공격시에 입력이 들어오면 공격 해제-----//
		HT_vInterface_AttackModeTrans( iObject_ID );

		//-----To Do-----//
		HT_CELL_COORD cellPos = g_cItemSystem->HT_cellItemSystem_GetMapCellPosForModelID( iTempID );

		DWORD dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemKeyFromModelID( iTempID, HT_TRUE );
		g_cItemControl->HT_vItemControl_SetTargetItem( dwItemKeyID );

		g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_FALSE );
		//---------------//
		return HT_OK;
	}

	return HT_FAIL;
}

//-----픽 검색_OtherCharter-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_OtherChar( HTint iObject_ID )
{
	DWORD dwTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_SRPickIDCheck( iObject_ID );
	//	포탈용 몹일때는 그대로
	if( dwTargetKeyID == FORPOTAL_MOBID_FORCHATURANGR ||
		dwTargetKeyID == FORPOTAL_MOBID_FORTRIMURITICAVE )
	{
		return HT_OK;
	}
	else
	{
		if( dwTargetKeyID != 0 )
		{
			g_pEngineHandler->HT_hrPlaySound( 33524, 1 );	// Click Sound

			//	캐릭터 일때
			if( SERVEROBJECT_IS_CHARACTER( dwTargetKeyID ) )
			{
				//	주신전 지역이면
				if( HT_SUCCEED( HT_extern_TrimuritiZone( g_wResentZoneServerID ) ) )
				{
					if( g_oMainCharacterInfo.byTrimuriti == g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti( dwTargetKeyID ) )
					{
						if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
						if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
						if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
						if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
						// 상점 모드의 캐릭터를 클릭했을 경우
						if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTradeMode( dwTargetKeyID ) != HT_STORE_MODE_END )
						{
							g_cIndividualStore->HT_vNetWork_CSP_Req_Store( dwTargetKeyID ); 
							return HT_OK;
						}
					}
				}
				//	요새전 지역이면
				else if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
				{
					if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
					if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_pDuelSystem->HT_hrDuel_PickCheckFromOtherObject( iObject_ID ) ) )		{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_hrGuild_PickCheckFromOtherObject( iObject_ID ) ) )	{	return HT_OK;	}
					
					// 상점 모드의 캐릭터를 클릭했을 경우
					if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTradeMode( dwTargetKeyID ) != HT_STORE_MODE_END )
					{
						g_cIndividualStore->HT_vNetWork_CSP_Req_Store( dwTargetKeyID ); 
						return HT_OK;
					}
				}
				//	일반 지역일때
				else
				{
					//	주신전 지역이 아닌 경우
					if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
					if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
					//	비류성이 아닐때만
					if( g_wResentZoneServerID != ZONE_BIRYUCASTLE )
                        if( HT_SUCCEED( g_pDuelSystem->HT_hrDuel_PickCheckFromOtherObject( iObject_ID ) ) )		{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_hrGuild_PickCheckFromOtherObject( iObject_ID ) ) )	{	return HT_OK;	}
					
					// 상점 모드의 캐릭터를 클릭했을 경우
					if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTradeMode( dwTargetKeyID ) != HT_STORE_MODE_END )
					{
						g_cIndividualStore->HT_vNetWork_CSP_Req_Store( dwTargetKeyID ); 
						return HT_OK;
					}

					if ( g_eBlogAccessStatus == HT_BLOGACCESSSTATUS_READY )
					{
						g_eBlogAccessStatus = HT_BLOGACCESSSTATUS_NULL;
						g_iBlogClickedChar = iObject_ID;

						CHTString strString;
						if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
						{
							g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
							//	MessageBox Type
							g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_OTHERBLOG;
						}
					}
				}

				//	컨트롤 키가 눌려져 있다면 귓속말에 상대방의 이름을 삽입한다.
				if( g_cInterfaceCheck->HT_vInterface_GetControlKey() )
				{
					//	귓속말 상태로 만들어 주고..
					CHTString strMyName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( dwTargetKeyID );
					{
						if( strMyName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) != 0 )
                            g_cChatting->HT_vChatting_SetWisper( strMyName.HT_szGetString() );
					}
				}
			}

			g_cMainCharacter->HT_vMainChar_SetAttackStatus( dwTargetKeyID, iObject_ID, HT_TRUE );

			return HT_OK;
		}
	}

	return HT_FAIL;
}

//-----픽 검색_NPC-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_NPC( HTint iObject_ID )
{
	HTint iTempID = g_sNPCSystem->HT_vNPCSystemComIDCheck( iObject_ID );
	if( iTempID != 0 )
	{
		//	그리드를 계산하여 일정 그리드 안에 있을때만 적용
		DWORD dwIndex = g_sNPCSystem->HT_pNPCSystem_GetIndexFromModelID( iTempID );
		HTPoint pCellPt = g_sNPCSystem->HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
		HTPoint pMainCharCell = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		if( pMainCharCell.x >= pCellPt.x-6 && pMainCharCell.x <= pCellPt.x+6 && 
			pMainCharCell.y >= pCellPt.y-6 && pMainCharCell.y <= pCellPt.y+6 )
		{
			//----------캐릭터 정지 셋팅----------//
			g_cMainCharacter->HT_vMainChar_SetStopMove();
			g_sNPCSystem->HT_pNPCSystem_PickConnect( iTempID );
			//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
			g_cMainCharacter->HT_vInterface_Pick_Map_DeleteEffect();
		}
		else
		{
			HT_CELL_COORD cellPos;
			cellPos.x = pCellPt.x + 1;
			cellPos.y = pCellPt.y + 1;
			g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_FALSE );
			//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
			g_cMainCharacter->HT_vInterface_Pick_Map_DeleteEffect();
		}
		return HT_OK;
	}

	return HT_FAIL;
}

//-----픽 검색_Object-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Object( HTint nObjectID, HTvector3 vecPickPos )
{
	g_pEngineHandler->HT_hrPlaySound( 33525, 1 );	// Click Sound

	return g_cPortal->HT_vPortal_Click( nObjectID, vecPickPos );
}

//-----픽 검색_맵-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Map( HTvector3 vecPos )
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecPos, crdCell );

	//-----맵위의 아이템 체크-----//
	HTint iTempID = 0;
	if (g_cItemSystem)
		iTempID = g_cItemSystem->HT_iSystem_MapCellCheckToItemOnMap( crdCell.x, crdCell.y );

	if( iTempID != 0 )
	{
		//-----공격시에 입력이 들어오면 공격 해제-----//
		HT_vInterface_AttackModeTrans( iTempID );

		//-----To Do-----//
		DWORD dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemKeyFromModelID( iTempID, HT_TRUE );
		if (g_cItemControl)
			g_cItemControl->HT_vItemControl_SetTargetItem( dwItemKeyID );

		if (g_cMainCharacter)
			g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( crdCell, HT_FALSE );
	}
	else
	{
		if (g_cMainCharacter)
			g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( crdCell, HT_TRUE );
	}

	return HT_OK;
}

//----------키보드 컨트롤----------//
//-----키보드 체크_한번만 셋팅-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_KeyDown( WPARAM wParam )
{
	// 게임안으로 들어왔을때만 수행

	// 입력중일때는 처리 안함
	if (g_cUIManager->HT_isFocusOnEditBoxControl() == true)
		return;

	//	IME String Init (단축키 누를 경우 무조건 영어상태로 변경)
	g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, 0 );
	g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	g_cImeMgr.InputString();

	//	입력을 받음으로 해서 자동 대기모드 취소
	g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	캐릭터가 죽어버렸다면 밑에 메시지들은 받지 못한다.
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	{
		// 버그수정 2005. 1. 18 화요일 죽은상태에서 부활창 팝업시 다른버튼 클릭해도 먹히지 않게 한다. 선영범
		if (g_cUIManager->HT_isShowWindow( _DIALOG_REVIVEWND )) 
			g_cUIManager->HT_HideWindow( _DIALOG_REVIVEWND );

		//	캐릭터가 죽었을때라도 메시지 받을 수 있는 것
		//if ( g_iGlobalKey != 'M' && GetAsyncKeyState( 'M' ) < 0 )
		//{
			//	IME String Init
		//	g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, 0 );

		switch(wParam)
		{
		case ALPAHBAT_KEYVALUE_M:
			g_cMiniMap->HT_vMiniMap_Action();
			return;
		//}
		//if ( g_iGlobalKey != 'I' && GetAsyncKeyState( 'I' ) < 0 )
		//{
			//	IME String Init
		//	g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, 0 );
		case ALPAHBAT_KEYVALUE_I:
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
			return;
		}
		//}
		return;
	}

	// 살아 있는 경우에만 처리되는 메시지들. 
	switch(wParam)
	{
	case ALPAHBAT_KEYVALUE_B:
	{

			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowChatMsg();
	}
	break;
	case ALPAHBAT_KEYVALUE_C:
	{		
			g_cCommand->HT_vCommand_WndActiveSw();
	}
	break;
	case ALPAHBAT_KEYVALUE_G:
	{
			g_cGuildSystem->HT_vGuild_DialogBoxActive();
	}
	break;
	case ALPAHBAT_KEYVALUE_H:
	{
			if( g_cTutorialSystem->HT_bTutorial_HelpWnd() )
                g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
			else
				g_cTutorialSystem->HT_vTutorial_SetHelpWnd();
	}
	break;
	case ALPAHBAT_KEYVALUE_J:
	{
			if( g_cAddress->HT_iIsOn() )
                g_cAddress->HT_vSetOff();
			else
				g_cAddress->HT_vSetOn();
	}
	break;
	case ALPAHBAT_KEYVALUE_K:
	{
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
				g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
	}
	break;
	case ALPAHBAT_KEYVALUE_L:
	{
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
				g_cStatus->HT_vStatus_ActiveSw();
	}
	break;
	case ALPAHBAT_KEYVALUE_N:
	{
		if (g_cSystem->m_bOption1 == true)
		{
			g_cSystem->HT_vSystem_InputCheckSystem(1, UI_TARGET_BUTTON, 5);
		}
		else
		{
			g_cSystem->HT_vSystem_InputCheckSystem(1, UI_TARGET_BUTTON, 4);
		}
//			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowName();
//			g_cMainCharacter->HT_bMainChar_SetShowName();
	}
	break;
	case ALPAHBAT_KEYVALUE_M:
	{
			g_cMiniMap->HT_vMiniMap_Action();
	}
	break;
	case ALPAHBAT_KEYVALUE_O:
	{
			g_cSystem->HT_vSystem_ActiveSw();
	}
	break;
	case ALPAHBAT_KEYVALUE_U:
	{
			if (m_bInterface_ControlKeySw)
				m_bUIRenderOn = !m_bUIRenderOn;
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )
				g_cQuest->HT_vQuest_ActiveSw();
	}
	break;
	case ALPAHBAT_KEYVALUE_V:
	{
			g_cChatting->HT_vChatting_SetLastSendWisper();
	}
	break;
	case ALPAHBAT_KEYVALUE_Z:
	{
			g_cMainCharacter->HT_vMainChar_SetMoveType();
	}
	break;
	case ALPAHBAT_KEYVALUE_F:
	{
		//	멕시코에스는 기능을 못하게 한다.
		if( g_iInationalType == INATIONALTYPE_MEXICO )
			return;

		//	Return Get MoveStop Stauts
		if( !g_cMainCharacter->HT_bMainChar_GetMoveStopStatus() )	return;
		if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;
		if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )			return;
		
		//	가장 근접한 아이템 KeyID 얻기
		HTint iItemKeyID = g_cItemSystem->HT_iItemSystem_GetItemKeyIDMostNearMainChar();
		if( iItemKeyID )
		{
			HT_CELL_COORD cellPos = g_cItemSystem->HT_cellItemSystem_GetMapCellPosForKeyID( iItemKeyID );
			g_cItemControl->HT_vItemControl_SetTargetItem( (HTdword)iItemKeyID );
			g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_FALSE );
			g_cItemSystem->HT_vItemSystem_SetItemTargettingEffect( iItemKeyID );
		}
	}
	break;
	case ALPAHBAT_KEYVALUE_E:
	{
		//	멕시코에스는 기능을 못하게 한다.
		if( g_iInationalType == INATIONALTYPE_MEXICO )
			return;

		if( !g_cMainCharacter->HT_bMainChar_GetAttackStopStatus() )	return;
		if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;
		if( g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Blind )	return;

		HTbool bTrue = HT_TRUE;
		if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )
		{
			if( g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_WLK &&
				g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_RUN )
			{
				bTrue = HT_FALSE;
			}
		}

		if( bTrue )
		{
			HTint iTargetKeyID = 0;
			HTint iObjectID;
			iTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetObjectKeyIDMostNearMainChar( g_cCommand->HT_iCommand_GetBeforeTargetID() );
			if( iTargetKeyID )
			{
				iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( iTargetKeyID );
				g_cMainCharacter->HT_vMainChar_SetAttackStatus( iTargetKeyID, iObjectID, HT_FALSE );
			}
		}
	}
	break;
	case ALPAHBAT_KEYVALUE_R:
	{
		//	멕시코에스는 기능을 못하게 한다.
		if( g_iInationalType == INATIONALTYPE_MEXICO )
			return;

		HTint iAttackTargetID = g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID();
		if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetLiveFromKeyID( iAttackTargetID ) )
		{
			g_cMainCharacter->HT_vMainChar_SetAttackStatus( -1, -1, HT_TRUE );
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetAttackTargetting( iAttackTargetID );
		}
	}
	break;
	case ALPAHBAT_KEYVALUE_T:
	{
		//	Return Get MoveStop Stauts
		if( !g_cMainCharacter->HT_bMainChar_GetAttackStopStatus() )	return;
		if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;

		HTbool bTrue = HT_TRUE;
		if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )
		{
			if( g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_WLK &&
				g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_RUN )
			{
				bTrue = HT_FALSE;
			}
		}

		if( bTrue )
		{
			HTint iTargetKeyID = 0;
			HTint iObjectID;
			iTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetAssociateKeyIDMostNearMainChar( g_cCommand->HT_iCommand_GetBeforeTargetID() );
			if( iTargetKeyID )
			{
				iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( iTargetKeyID );
				g_cMainCharacter->HT_vMainChar_SetAttackStatus( iTargetKeyID, iObjectID, HT_FALSE );
			}
		}
	}
	break;
	case ALPAHBAT_KEYVALUE_X:
	{
		//	Return Get MoveStop Stauts
		if( !g_cMainCharacter->HT_bMainChar_GetMoveStopStatus() )	return;
		g_cMainCharacter->HT_vMainChar_SetSit();
	}
	break;
	case ALPAHBAT_KEYVALUE_I:
	{
		g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();

	}
	break;
	case ALPAHBAT_KEYVALUE_SUBTRACT :
		g_cQuickSlot->HT_vSetSide( 100 );
		break;

	case ALPAHBAT_KEYVALUE_ADD :
		g_cQuickSlot->HT_vSetSide( 101 );
		break;

		case VK_F11 :	//	카메라 모드 변화
			if( g_bGoAttackCamera )
			{
				iDefineCameraMode++;
				if( iDefineCameraMode == iDefineCameralimitMode )
					iDefineCameraMode = 0;

				HTvector3 vecTemp = g_cMainCharacter->HT_vecGetPosition();
				g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, HTvector3( vecTemp.x, vecTemp.y+(g_pEngineHandler->HT_fGetObjHeight( g_cMainCharacter->HT_vMainChar_GetModelID() )/2)+fDefineCameraHight[iDefineCameraMode], vecTemp.z ) , 1, fDefineCameraSpeed[iDefineCameraMode] );
				g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, HTvector3( fDefineCameraX[iDefineCameraMode]+vecTemp.x, fDefineCameraY[iDefineCameraMode]+vecTemp.y, fDefineCameraZ[iDefineCameraMode]+vecTemp.z) , 1, fDefineCameraSpeed[iDefineCameraMode] );
			}
			break;
		case VK_F12 :	//	카메라 모드 변화
			g_cCamera.HT_vCamera_TransView( 12 );
			//{
			//	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
			//	MSG_Action* info = HT_NULL;
			//	info = new MSG_Action;
			//	info->TargetX = pPt.x+10;
			//	info->TargetY = pPt.y+10;
			//	info->Effect = 11;
			//	g_cMainCharacter->HT_vNetWork_Recive_MSGAction( info );
			//	HT_DELETE( info );
			//}
			break;
		case VK_INSERT:	//	카메라 초기값 셋팅
			g_cCamera.HT_vCamera_SetInitCameraMode();
			break;
	}

	// 루피아 이동창 || 아이템 분리창 || 아이템 개수 입력창 || 개인상점-구입창 || 교환창이 떠있을 경우 처리하지 않을 단축키들
	if( g_cSystem->HT_bSystem_GetF1ToF10Mode() )
	{ // Slot Mode 
		switch(wParam)
		{
			case VK_TAB: // 화면상의 창 안보이게 하기
				//g_iShowUI++;
				//if (g_iShowUI>3) g_iShowUI = 0;
				break;
			// 퀵슬롯
			case VK_F1 :
				g_cQuickSlot->HT_vSetSide( 0 );
				break;
			case NUMBER_KEYVALUE_1 :
				if( GetAsyncKeyState( VK_SHIFT ) < 0 )	g_cQuickSlot->HT_vSetSide( 0 );
				else									g_cQuickSlot->HT_vAction( 0 );
				break;
			case VK_F2 :
				g_cQuickSlot->HT_vSetSide( 1 );
				break;
			case NUMBER_KEYVALUE_2 :
				if( GetAsyncKeyState( VK_SHIFT ) < 0 )	g_cQuickSlot->HT_vSetSide( 1 );
				else									g_cQuickSlot->HT_vAction( 1 );
				break;
			case VK_F3 :
				g_cQuickSlot->HT_vSetSide( 2 );
				break;
			case NUMBER_KEYVALUE_3 :
				if( GetAsyncKeyState( VK_SHIFT ) < 0 )	g_cQuickSlot->HT_vSetSide( 2 );
				else									g_cQuickSlot->HT_vAction( 2 );
				break;
			case VK_F4 :
				g_cQuickSlot->HT_vSetSide( 3 );
				break;
			case NUMBER_KEYVALUE_4 :
				if( GetAsyncKeyState( VK_SHIFT ) < 0 )	g_cQuickSlot->HT_vSetSide( 3 );
				else									g_cQuickSlot->HT_vAction( 3 );
				break;
			case VK_F5 :
				g_cQuickSlot->HT_vSetSide( 4 );
				break;
			case NUMBER_KEYVALUE_5 :
				if( GetAsyncKeyState( VK_SHIFT ) < 0 )	g_cQuickSlot->HT_vSetSide( 4 );
				else									g_cQuickSlot->HT_vAction( 4 );
				break;
			case VK_F6 :
				//g_cQuickSlot->HT_vAction( 5 );
				break;
			case NUMBER_KEYVALUE_6 :
				g_cQuickSlot->HT_vAction( 5 );
				break;
			case VK_F7 :
				//g_cQuickSlot->HT_vAction( 6 );
				break;
			case NUMBER_KEYVALUE_7 :
				g_cQuickSlot->HT_vAction( 6 );
				break;
			case VK_F8 :
				//g_cQuickSlot->HT_vAction( 7 );
				break;
			case NUMBER_KEYVALUE_8 :
				g_cQuickSlot->HT_vAction( 7 );
				break;
			case VK_F9 :
				//g_cQuickSlot->HT_vAction( 8 );
				break;
			case NUMBER_KEYVALUE_9 :
				g_cQuickSlot->HT_vAction( 8 );
				break;
			case VK_F10 :
				//g_cQuickSlot->HT_vAction( 9 );
				break;
			case NUMBER_KEYVALUE_0 :
				g_cQuickSlot->HT_vAction( 9 );
				break;
			default:
				break;
		}
	}
	else
	{
		// Skill 모드
		switch(wParam)
		{
			case VK_TAB: // 화면상의 창 안보이게 하기
				//g_iShowUI++;
				//if (g_iShowUI>3) g_iShowUI = 0;
				break;
			// 퀵슬롯
			case VK_F1 :
				g_cQuickSlot->HT_vAction( 0 );
				break;
			case NUMBER_KEYVALUE_1 :
				g_cQuickSlot->HT_vSetSide( 0 );
				break;
			case VK_F2 :
				g_cQuickSlot->HT_vAction( 1 );
				break;
			case NUMBER_KEYVALUE_2 :
				g_cQuickSlot->HT_vSetSide( 1 );
				break;
			case VK_F3 :
				g_cQuickSlot->HT_vAction( 2 );
				break;
			case NUMBER_KEYVALUE_3 :
				g_cQuickSlot->HT_vSetSide( 2 );
				break;
			case VK_F4 :
				g_cQuickSlot->HT_vAction( 3 );
				break;
			case NUMBER_KEYVALUE_4 :
				g_cQuickSlot->HT_vSetSide( 3 );
				break;
			case VK_F5 :
				g_cQuickSlot->HT_vAction( 4 );
				break;
			case NUMBER_KEYVALUE_5 :
				g_cQuickSlot->HT_vSetSide( 4 );
				break;
			case VK_F6 :
				g_cQuickSlot->HT_vAction( 5 );
				break;
			case NUMBER_KEYVALUE_6 :
				//g_cQuickSlot->HT_vAction( 5 );
				break;
			case VK_F7 :
				g_cQuickSlot->HT_vAction( 6 );
				break;
			case NUMBER_KEYVALUE_7 :
				//g_cQuickSlot->HT_vAction( 6 );
				break;
			case VK_F8 :
				g_cQuickSlot->HT_vAction( 7 );
				break;
			case NUMBER_KEYVALUE_8 :
				//g_cQuickSlot->HT_vAction( 7 );
				break;
			case VK_F9 :
				g_cQuickSlot->HT_vAction( 8 );
				break;
			case NUMBER_KEYVALUE_9 :
				//g_cQuickSlot->HT_vAction( 8 );
				break;
			case VK_F10 :
				g_cQuickSlot->HT_vAction( 9 );
				break;
			case NUMBER_KEYVALUE_0 :
				//g_cQuickSlot->HT_vAction( 9 );
				break;
			default:
				break;
		}
	}
}

//-----키보드 체크_Up-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_KeyUp( WPARAM wParam )
{
	// 입력중일때는 처리 안함
	if (g_cUIManager->HT_isFocusOnEditBoxControl() == true)
		return;

//	g_iGlobalKey = 0;

//	if (!(GetAsyncKeyState( 'E' ) < 0) ) 
//		g_iGlobalKeyE = 0;
//	if (!(GetAsyncKeyState( 'R' ) < 0) ) 
//		g_iGlobalKeyR = 0;
///	if (!(GetAsyncKeyState( 'F' ) < 0) ) 
//		g_iGlobalKeyF = 0;

	////	캐릭터가 죽어버렸다면!
	//if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	//	return;

	////	채팅창이 활성화 상태라면
	//if( g_cChatting->HT_bIsInputOn() )
	//	return;

	//switch(wParam)
	//{
	//	case ALPAHBAT_KEYVALUE_A :	//	좌/우 회전키 체크
	//	case ALPAHBAT_KEYVALUE_D :
	//		g_cMainCharacter->HT_vCharSetKeyDownCheck( HT_FALSE );
	//		break;
	//}
}

//-----키보드 체크_Function Key-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_FunctionKey( WPARAM wParam )
{
	//	캐릭터가 죽어버렸다면!
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	{
		if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
		{
			// 마우스 무빙상태 펄스로 해서 아이콘 이동중이였다면 취소시킴
			g_cUIManager->HT_CancelSlotBoxImageMoving();

			// 요새전 부활창 띄움
			if (g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) == false)
				g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );

			//return;
		}
		else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
		{
			// 요새전 부활창 띄움
			if (g_cUIManager->HT_isShowWindow(_DIALOG_DEATHMSGFOTRESS ) == false)
				g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );
			//return;
		}
		else
		{
			DWORD dwPassTime = timeGetTime();
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_ANSWERUSESAMUDABA ) )
			{
				if ( g_cMainCharacter->m_bMainChar_Reviving == HT_FALSE || 
					(dwPassTime > g_cGameSystem->m_dwSamudabaDelayTime+10000 && g_cMainCharacter->m_bMainChar_Reviving == HT_TRUE) )
				{
					// 무언가 입력중이였다면 뜨지 않는다.
					if (g_cUIManager->HT_isFocusOnEditBoxControl() == true) return;

					CHTString szMessage;
					// 확인 버튼을 누르면 저장지역에서 다시 태어납니다.
					
					// 마우스 무빙상태 펄스로 해서 아이콘 이동중이였다면 취소시킴
					g_cUIManager->HT_CancelSlotBoxImageMoving();

					HT_g_Script_SetMessage( eMsgCharacterRebirth, &szMessage, _T("") );
					g_cUIManager->HT_MessageBox( _DIALOG_DEATHMSG, szMessage.HT_szGetString(), 4 );
				}
			}
			return;
		}
	}

    switch(wParam)
	{
		case VK_ESCAPE:
			this->HT_vInterface_ESC_CloseWindow();
			break;
		//case VK_RETURN:
		//	g_cChatting->HT_vChatting_SetFocusOn();
		//	break;
		default:
			break;
	}
}

//	확인/재확인창 Enter키 입력
HTvoid CHTInterfaceCheck::HT_vInterface_MessageWindowForEnterKey( HTint iDlgNo )
{
}

//	ESC키 누려면 자동으로 현재의 창들을 닫을수 있도록
HTvoid CHTInterfaceCheck::HT_vInterface_ESC_CloseWindow()
{
	//	아무것도 걸리는 창이 없으면 시스템창을 연다.
	if (g_cUIManager->HT_CloseWindow() == false)
		g_cSystem->HT_vSystem_ActiveSw();
	else
		g_cSystem->m_bSystem_WindowActiveSw = HT_FALSE;
}

//-----키보드 체크_계속 들어오는것-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_Continue()
{
	if( g_cUIManager->HT_isFocusOnEditBoxControl() )
		return;

	//	엔진카메라 사용모드가 활성화 상태라면
	if( g_bUseEngineCamera )
	{
		if( GetAsyncKeyState( VK_LEFT ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( VK_LEFT, m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( VK_RIGHT ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( VK_RIGHT, m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( VK_UP ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( VK_UP, m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( VK_DOWN ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( VK_DOWN, m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'W' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'W', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'S' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'S', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'D' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'D', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'A' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'A', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'X' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'X', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'x' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'x', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'Q' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'Q', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'E' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'E', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'Z' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'Z', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'C' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'C', m_fInterfaceElapsedTime );
		else if( GetAsyncKeyState( 'L' ) < 0 )
			g_pEngineHandler->HT_hrCameraControl( 'L', m_fInterfaceElapsedTime );
		return;
	}

	//	캐릭터가 죽어버렸다면!
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return;

	//	Return Get MoveStop Stauts
	if( !g_cMainCharacter->HT_bMainChar_GetMoveStopStatus() )	return;
	if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;

	if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
	{
		//-----캐릭터 전진-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_W ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Go( m_fInterfaceElapsedTime );
		}
		//-----캐릭터 RIGHT-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_D ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Right();
		}
		//-----캐릭터 LEFT-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_A ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Left();
		}
		//	이상하게 F10을 윈도우 메시지로 잡지못해 부득이하게 여기에서 잡는다 안타까운 일이지
		if( GetAsyncKeyState( VK_F10 ) < 0 )
		{
			DWORD dwPassTime = GetTickCount();
			if( dwPassTime > m_dwDelayTimeForF10+500 )
			{
				m_dwDelayTimeForF10 = dwPassTime;
                this->HT_hrInterfaceKeyboard_Input_KeyDown( VK_F10 );
			}
		}
	}

	//	Camera_ZOOM IN / ZOOM OUT
	if( GetAsyncKeyState( VK_ADD ) < 0 )
	{
		g_cCamera.HT_vCamera_ZoomInAndOutTrans( m_fInterfaceElapsedTime*100.0f );
	}
	else if( GetAsyncKeyState( VK_SUBTRACT ) < 0 )
	{
		g_cCamera.HT_vCamera_ZoomInAndOutTrans( -(m_fInterfaceElapsedTime*100.0f) );
	}
	//	Camera_Rotate
	if( GetAsyncKeyState( VK_LEFT ) < 0 )
	{
		g_cCamera.HT_vCamera_SetRotate( -( m_fInterfaceElapsedTime*2 ) );
	}
	else if( GetAsyncKeyState( VK_RIGHT ) < 0 )
	{
		g_cCamera.HT_vCamera_SetRotate( ( m_fInterfaceElapsedTime*2 ) );
	}
}


//----------프로세스의 가장 마지막에 이닛----------//
HTvoid CHTInterfaceCheck::HT_hrInterfaceControlEnd()
{
	g_iInterface.iLeftClick = HT_FALSE;
}

//-----ElapsedTime 갱신-----//
HTvoid CHTInterfaceCheck::HT_vInterface_SetElapsedTime( HTfloat fElapsedTime )
{
	m_fInterfaceElapsedTime = fElapsedTime;
}

HTbool
CHTInterfaceCheck::HT_bSetCharMonHPAttach()
{
	return HT_TRUE;
}

//	그야말로 동영상 촬영을 위한 임시코드
HTvoid
CHTInterfaceCheck::HT_vInterface_LoadCameraForBroadcast()
{
	char buff[64];

	FILE*	fp;
	fp = fopen( "동영상.txt", "r" );
	if (!fp) return;
	
	HTint count;
	fgets( buff, 64, fp);
	sscanf( buff, "%d", &iDefineCameralimitMode );

	for( HTint i=0 ; i<iDefineCameralimitMode ; i++ )
	{
		fgets( buff, 64, fp);
		sscanf( buff, "%d: %f, %f, %f, %f, %f", &count, &fDefineCameraX[i], &fDefineCameraY[i], &fDefineCameraZ[i], &fDefineCameraSpeed[i], &fDefineCameraHight[i] );
	}
	iDefineCameraMode = 0;
}
