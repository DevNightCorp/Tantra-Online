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

	m_iCursorID					= CURSOR_ARROW_1;			// ó���� Ŀ���� �Ϲ� ȭ��ǥ�̴�.

	m_bUseWindowsCursor			= HT_FALSE;

	// ó������ ���� ITEM�� ����.
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


//----------�ʱ�ȭ----------//
HTRESULT CHTInterfaceCheck::HT_hrInterfaceInit()
{
	m_bUseWindowsCursor = g_pEngineHandler->HT_bIsWindowCursor();

	//-----Ŀ��-----//
	// ȭ��ǥ Ŀ�� �ε�
	m_hCursor_Normal1 = HT_hLoadCursor(CURSOR_FILE_ARROW_1);
	m_hCursor_Normal2 = HT_hLoadCursor(CURSOR_FILE_ARROW_2);
	// �����ʹ�ư Ŭ�� Ŀ��
	m_hCursor_RButton = HT_hLoadCursor(CURSOR_FILE_RBUTTON);
	// Į��� Ŀ�� �ε�
	m_hCursor_Sword = HT_hLoadCursor(CURSOR_FILE_SWORD);
	m_hCursor_Sword_Ani = HT_hLoadCursor(CURSOR_FILE_SWORD_ANI);
	// NPC Ŀ�� �ε�
//	m_hCursor_NPC = HT_hLoadCursor(CURSOR_FILE_NPC);
	m_hCursor_NPC_Ani = HT_hLoadCursor(CURSOR_FILE_NPC_ANI);
	// ���� Ŀ�� �ε�
	m_hCursor_Repair = HT_hLoadCursor(CURSOR_FILE_REPAIR);
	m_hCursor_Repair_Ani = HT_hLoadCursor(CURSOR_FILE_REPAIR_ANI);
	m_hCursor_Repaird = HT_hLoadCursor(CURSOR_FILE_REPAIRD);
	// �ո�� Ŀ�� �ε�
	m_hCursor_Hand1 = HT_hLoadCursor(CURSOR_FILE_HAND_1);
	m_hCursor_Hand2 = HT_hLoadCursor(CURSOR_FILE_HAND_2);
	m_hCursor_Hand_Ani = HT_hLoadCursor(CURSOR_FILE_HAND_ANI);

	// Address ȭ��ǥ Ŀ�� �ε�
	m_hCursor_Address = HT_hLoadCursor(CURSOR_FILE_ADDRESS);
	m_hCursor_Address_Ani = HT_hLoadCursor(CURSOR_FILE_ADDRESS_ANI);
	// Party ȭ��ǥ Ŀ�� �ε�
	m_hCursor_Party = HT_hLoadCursor(CURSOR_FILE_PARTY);
	m_hCursor_Party_Ani = HT_hLoadCursor(CURSOR_FILE_PARTY_ANI);
	// Trade ȭ��ǥ Ŀ�� �ε�
	m_hCursor_Trade = HT_hLoadCursor(CURSOR_FILE_TRADE);
	m_hCursor_Trade_Ani = HT_hLoadCursor(CURSOR_FILE_TRADE_ANI);

	// Blog�� ������ ���� Ŀ��
	m_hCursor_Blog = HT_hLoadCursor(CURSOR_FILE_BLOG);
	m_hCursor_Blog_Ani = HT_hLoadCursor(CURSOR_FILE_BLOG_ANI);

	//	Cursor For Select
	m_hCursor_Select = HT_hLoadCursor(CURSOR_FILE_DUEL);
	m_hCursor_Select_Ani = HT_hLoadCursor(CURSOR_FILE_DUEL_ANI);

	// ���ҽ��� �޸𸮿� �ε� �Ǿ���
	m_bLoaded = HT_TRUE;

	//	������ ���ϰ� �ٽ� ���Ҷ����� ������ Ÿ��
	m_dwGetItemDelayTime = GetTickCount();
	m_iPickItemID = 0;

	//	�̻��ϰ� F10�� ������ �޽����� �������� �ε����ϰ� Ű������ ����
	m_dwDelayTimeForF10 = GetTickCount();

	return HT_OK;
}

HTvoid CHTInterfaceCheck::HT_vCHTInterfaceCheck_CleanUp()
{

	//-----Ŀ��-----//
	// ȭ��ǥ Ŀ�� ����
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
	// ������ ��ư Ŭ�� Ŀ�� ����
	if( m_hCursor_RButton != HT_NULL )
	{
		DestroyCursor(m_hCursor_RButton);
		m_hCursor_RButton = HT_NULL;
	}
	// Į��� Ŀ�� ����
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
	// NPC Ŀ�� ����
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
	// ���� Ŀ�� ����
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
	// �ո�� Ŀ�� ����
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
	
	// Address ȭ��ǥ Ŀ�� ����
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
	// Party ȭ��ǥ Ŀ�� ����
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
	// Trade ȭ��ǥ Ŀ�� ����
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

	// Blog Ŀ�� ����
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

	//	���� �ý��� Ŀ�� ����
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

	// ���ҽ��� �޸𸮿� ��ε� �Ǿ���
	m_bLoaded = HT_FALSE;
}

//---------- Ŀ�� �ڵ� �ε� -------------//
HCURSOR CHTInterfaceCheck::HT_hLoadCursor(CHTString szFile)
{
	TCHAR szFullFile[MAX_PATH];
	GetFullPathName( szFile, MAX_PATH, szFullFile, NULL );
	
	return LoadCursorFromFile(szFullFile);
}

//--------- Ŀ�� ����� ���� ------------//
HTvoid CHTInterfaceCheck::HT_vSetCursor(HTint iID)
{
	m_iCursorID = iID;	
	HT_vRanderCursor();
}

HTvoid CHTInterfaceCheck::HT_vRanderCursor()
{
	switch(m_iCursorID)
	{
		// ȭ��ǥ Ŀ��
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
		// �ո�� Ŀ��
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
		//Į��� Ŀ��
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
		// NPC Ŀ��
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
		// ���� Ŀ��
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
		// Address ȭ��ǥ Ŀ��
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
		// Party ȭ��ǥ Ŀ��
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
		// Trade ȭ��ǥ Ŀ��
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
		// Blog Ŀ��
		case CURSOR_BLOG :
		{
			if ( m_hCursor_Blog != HT_NULL ) SetCursor( m_hCursor_Blog );
		}	break;
		case CURSOR_BLOG_ANI :
		{
			if ( m_hCursor_Blog_Ani != HT_NULL ) SetCursor( m_hCursor_Blog_Ani );
		}	break;
		// Duel Ŀ��
		case CURSOR_SELECT :
		{
			if ( m_hCursor_Select != HT_NULL ) SetCursor( m_hCursor_Select );
		}	break;
		case CURSOR_SELECT_ANI :
		{
			if ( m_hCursor_Select_Ani != HT_NULL ) SetCursor( m_hCursor_Select_Ani );
		}	break;
		// ������ ��ư Ŭ��
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

//----------�������̽� ��Ʈ�� �κ�----------//
HTvoid CHTInterfaceCheck::HT_vFlushInput()
{
	// ������ ���콺 Ŭ��, Ű���� �Է� ���� �����Ѵ�.
	g_iInterface.bLbuttonDbClk = HT_FALSE;
	g_iInterface.bRbuttonDbClk = HT_FALSE;
	g_iInterface.iLeftClick = HT_FALSE;
	g_iInterface.iRightClick = HT_FALSE;
}


HTRESULT CHTInterfaceCheck::HT_hrInterfaceControl()
{
	//-----Ű���� üũ_��� �����°�-----//
	this->HT_hrInterfaceKeyboard_Input_Continue();
	
	return HT_OK;
}

//----------����� ���� �Ͽ� ó���Ұ�----------//
//-----����� ���� �Ͽ� ó���Ұ�_L��ư �ٿ�-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonDown( HTPoint pPt )
{
}

//-----����� ���� �Ͽ� ó���Ұ�_L��ư ��-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonUp( HTPoint pPt )
{
	// L��ư ���ÿ� ó���ؾ� �� �������� �ϵ�
	g_cQuest->HT_vMouseSlideBarUp();	
}


//-----����� ���� �Ͽ� ó���Ұ�_L��ư Ŭ��-----//
HTvoid CHTInterfaceCheck::HT_vInterface_LbuttonClick( HTPoint pPt )
{ 
	//	�Է��� �������� �ؼ� �ڵ� ����� ���
	g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	������ �޽��� üũ
	if(HT_SUCCEED(g_cChatting->HT_hrChatting_SetPickOpenMsgWnd(pPt)))
		return;

	//----------��---------//
	// ���λ��� ���� ���̰ų� ���� ���̸� ó������ ����
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) )
		return;

	HTint iObject_ID;
	HTIntersectInfo oInfo;
	HTbool bPickMainChar = HT_FALSE;
	if ( HT_FAILED( g_pEngineHandler->HT_hrPick( pPt.x, pPt.y, &iObject_ID, &oInfo, &bPickMainChar )))		{	return; }
	g_imsi_button[0] = (HTfloat)iObject_ID;

	//	����ĳ���� Ŭ���Ǿ� �������� ���Ǿ��� �����ϰ�
	g_cMainCharacter->HT_vMainCharMyselfUndoClick();

	//-----�� �˻�_������-----//
	if( HT_SUCCEED( HT_vInterface_Pick_Item( iObject_ID, pPt ) ) )
	{	
		g_pMainBar->HT_vSetObjectHPOut();
		return;
	}

	if( iObject_ID > 0 )
	{
		g_cParty->m_party_DeleteMember = 255;	// �� �ɶ����� ���õ� ��Ƽ�� ������

		//----------������ �Ⱦ��� ������ �ʱ�ȭ �� ������ ����â �ʱ�ȭ----------//
		g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
		//----------OtherObjectSystem ����â �ʱ�ȭ---------//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
		//----------NPC ����â �ʱ�ȭ---------//
		g_sNPCSystem->HT_vNPCSystem_HPWindowInit();

        HTbool	bPickSw = HT_FALSE;
		//-----�� �˻�_OtherObject-----//
		if( HT_SUCCEED( HT_vInterface_Pick_OtherChar( iObject_ID ) ) )						{	return;	}//bPickSw = HT_TRUE; }
		//-----�� �˻�_NPC-----//
		if( HT_SUCCEED( HT_vInterface_Pick_NPC( iObject_ID ) ) )							{	bPickSw = HT_TRUE; }
		//-----�� �˻�_Object-----//
		if( HT_SUCCEED( HT_vInterface_Pick_Object( iObject_ID, oInfo.m_vecPosition ) ) )	{	bPickSw = HT_TRUE; }
		if( bPickSw )
            return;
	}

	//	MainChar�� Ŭ���Ǿ����� �ľ��ϰ� Ŭ���Ǿ��ٸ� �׿� ����ó��
	if ( bPickMainChar )
	{
		if( g_cCamera.HT_nCamera_GetCameraTypeEye() != CAMERATYPE_EYE_FRONTVIEW )
		{
			g_cMainCharacter->HT_vMainCharMyselfClick();
			return;
		}
	}
	
	//-----�� �˻�_��-----//
	HT_vInterface_Pick_Map( oInfo.m_vecPosition );
}

//----------RButton Ŭ�� üũ----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonDown( HTPoint pPt )
{
	// �������� ���� �ִ� �����̸� ó������ ����.
	//if( m_bPickItem ) return;
	// ī�޶� ���� ����
	g_cCamera.HT_vCamera_SetInput_On( pPt );
}


//----------RButton Ŭ�� üũ----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonUp( HTPoint pPt )
{
	// ī�޶� ���� ��� ����
	g_cCamera.HT_vCamera_SetInput_Off();
}

//----------RButton Ŭ�� üũ----------//
HTvoid CHTInterfaceCheck::HT_vInterface_RButtonClick( HTPoint pPt )
{
}

//-----����� ���� �Ͽ� ó���Ұ�_���콺 ����-----//
HTvoid CHTInterfaceCheck::HT_vInterface_MouseMove( HTPoint pPt )
{
	HTint nDlgNo = -1;
	// Ŀ��
	HT_vInterface_MouseMove_Cursor( pPt, nDlgNo );

	//----------ī�޶�_�ܺο��� ����_��/�ٿ�/ȸ��----------//
	if( g_cCamera.HT_vCamera_GetInputSw() == HT_TRUE )
	{
		g_cCamera.HT_vCamera_SetUpDownRotate( pPt, m_fInterfaceElapsedTime );
	}

	// ���� ����/ĳ����/NPC�� �����ö�� UI�ý��ۿ� �������� �ʴ� ������ ����.
	g_cUIManager->bRenderNPC = false;
	HTint iObjID = g_pEngineHandler->HT_iGetObjectOnMouse(pPt.x, pPt.y);
	if(iObjID > -1)
	{
		g_cUIManager->bRenderNPC = true;
		// HT_vObjectInfo_Active()���� ������ �����鼭 �������� ĳ�������� ����������Ѵ�.
		//	����Կ��� ���� ���� Ÿ���� �ִϸ��̼��� �Ⱥ��̰� �ϱ� ����
		if( !g_bGamePlayMovieForGlobal )
		{
			g_cObjectInfo->HT_vObjectInfo_Active_NPC(iObjID);
			return;
		}
	}

	// UI �ý��ۿ� ���콺 �����ÿ� ��ȭ���� �����̵��� ����
	m_pMouseBackPt.x = pPt.x;
	m_pMouseBackPt.y = pPt.y;

	g_cQuest->HT_vMouseSlideBarMove();
}

//----- ���콺�� ������ ������ Ŀ�� ��ȯ ó�� -----//
HTvoid CHTInterfaceCheck::HT_vInterface_MouseMove_Cursor( HTPoint  pPt, HTint nDlgNo )
{
	//-----------------------------------------------------------------
	// Ŀ�� ��ȯ�� ó���Ѵ�.
	//-----------------------------------------------------------------
	HTbool	bCursorConfined = HT_FALSE;	// Ŀ���� Ȯ�� �Ǿ������� �˻�

	// ������ ��ư�� Ŭ���� ���¸�
	if( g_iInterface.iRightDown == HT_TRUE )
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor(CURSOR_RBUTTON);

		bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
	}
	// ���� ���� �Ǵ� ��ü����� ��� : Ȯ�� �޼����� ���� �ʾ��� ��
	else if( g_cNPCControl->HT_bNPCControl_IsItemFixActive() && (g_cNPCControl->HT_bNPCControl_IsMessageWinActive() == HT_FALSE) )
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor(CURSOR_REPAIR_ANI);	// ��ġ���

		bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
	}
	// ���콺 ����Ʈ�� PC/NPC �κ��丮 â ���� �ִ��� üũ�ϰ� Ŀ�� ��ȯ
	// �ǸŸ���� ��� �Ϲ� Ŀ�� ������� ����
	else if( nDlgNo == _DIALOG_INVEN && g_cNPCControl->HT_bNPCControl_IsItemDisjointActive() == HT_FALSE )	// PC �κ��丮 
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1 );	// �ո��

		bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
	}
	// NPC �κ��丮
	else if( nDlgNo == _DIALOG_GOODSKEEPWND )	
	{	
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1);	// �ո��

		bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
	}
	// ������ ����Ʈ â���� ���콺�� ������
	else if( nDlgNo == _DIALOG_MERCHANT )	
	{
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			HT_vSetCursor( CURSOR_HAND_1);	// �ո��

		bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
	}
	else 
	{
		// Ŀ�� ���� ������Ʈ�� ���Ѵ�.
		DWORD dwObjectModelID = g_pEngineHandler->HT_iGetObjectOnMouse(pPt.x, pPt.y);
		DWORD dwIndex;
				
		// ������ �ִ� �������� ��� �����̴� ������ �ٲ۴�.
		if( !bCursorConfined && (g_cItemSystem->HT_dwSystem_GetItemKeyFromModelID( dwObjectModelID, HT_FALSE ) != 0) )	
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor(CURSOR_HAND_ANI);
			bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
		}
		// �ٸ� ĳ���� ���� �ִ� ��� PK���� �˻��� Į�� �ٲ۴�.
		HTint iObjectKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( dwObjectModelID );
		if( !bCursorConfined && ( iObjectKeyID != 0 ) )
		{
			if( SERVEROBJECT_IS_MONSTER( iObjectKeyID ) )	// ������ ���
			{
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					HT_vSetCursor( CURSOR_SWORD_ANI );
				bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
			}
			else	// ĳ������ ���
			{
                HTPoint pCharCell = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
				// ���� �� �ִ� ��ġ�� PK������ �����̰� PK��ư�� ���� �����̸� Ŀ���� Į�� �ٲ۴�.
				if( g_pEngineHandler->HT_bIsCellSafeZone( pCharCell.x, pCharCell.y, 0 ) == HT_FALSE )
				{
					//if( g_pMainBar->HT_bGetPKButton() ||
					//	g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
					//{
					//	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					//		HT_vSetCursor( CURSOR_SWORD_ANI );
					//	bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
					//}
				}
			}
		}
		// NPC���� �ִ� ��� ������ �˻��� ��ǳ������ �ٲ۴�.
		if( !bCursorConfined && ((dwIndex = g_sNPCSystem->HT_pNPCSystem_GetIndexFromModelID( dwObjectModelID )) != 0) ) // NPC�� ���
		{
			// NPC�� �� ��ġ�� ����
			HTPoint pNPCCellPos = g_sNPCSystem->HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
			HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
			pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
			pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;

			// x, y�� ������ ���� 6���� ������ ��ȭ�� ���� �� �� �����Ƿ� Ŀ���� ��ȯ(��ȭĿ����)
			if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x <= NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
			{
				if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
					HT_vSetCursor( CURSOR_NPC_ANI );
				bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
			}
		}
		// ��Ƽ ��� ��ư ���� �����̸�
		if( !bCursorConfined 
				&& g_cParty->HT_bParty_IsClickJoinBn() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_PARTY_ANI );

			bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
		}
		// �ּҷ� ��� ��ư ���� �����̸�
		if( !bCursorConfined 
			&& g_cUIManager->HT_isShowWindow( _DIALOG_ADDRESS ) && g_cAddress->HT_bAddress_IsClickRegistBn() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_ADDRESS_ANI );

			bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
		}
		// Trade ��ư ���� �����̸�
		if( !bCursorConfined && g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_TRADE_ANI );

			bCursorConfined = HT_TRUE;		// Ŀ�� Ȯ��
		}
		// Blog ���� ��ư�� ���� ���¶��
		if ( !bCursorConfined && g_eBlogAccessStatus == HT_BLOGACCESSSTATUS_READY )
		{
			if( g_cInterfaceCheck->m_hCursor_Blog_Ani == HT_FALSE ) HT_vSetCursor( CURSOR_BLOG );
			bCursorConfined = HT_TRUE;
		}
		// Blog ���� ��ư�� ���� ���¶��
		if ( !bCursorConfined && g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Request || !bCursorConfined && g_cGuildSystem->m_nAshuramGuildJoinMode == 1)
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
				HT_vSetCursor( CURSOR_SELECT_ANI );
			bCursorConfined = HT_TRUE;
		}

		// Ŀ���� Ȯ������ �ʾ����� ȭ��ǥ Ŀ���� �Ѵ�.
		if( !bCursorConfined )
		{
			if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			{
				HT_vSetCursor( CURSOR_ARROW_1 );
			}
		}
	}
}

//-----���ݽÿ� �Է��� ������ ���� ����-----//
HTvoid CHTInterfaceCheck::HT_vInterface_AttackModeTrans( HTint nModelID )
{
	g_cMainCharacter->HT_vMainChar_SetAttackCancel( 27 );
}

//-----�� �˻�_������-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Item( HTint iObject_ID, HTPoint pPt )
{
	//-----������ ������ üũ-----//
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
		
		//	������ ���ϰ� �ٽ� ���Ҷ����� ������ Ÿ��
		m_dwGetItemDelayTime = GetTickCount();

		g_pEngineHandler->HT_hrPlaySound( 33524, 1 );	// Click Sound

		//-----���ݽÿ� �Է��� ������ ���� ����-----//
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

//-----�� �˻�_OtherCharter-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_OtherChar( HTint iObject_ID )
{
	DWORD dwTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_SRPickIDCheck( iObject_ID );
	//	��Ż�� ���϶��� �״��
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

			//	ĳ���� �϶�
			if( SERVEROBJECT_IS_CHARACTER( dwTargetKeyID ) )
			{
				//	�ֽ��� �����̸�
				if( HT_SUCCEED( HT_extern_TrimuritiZone( g_wResentZoneServerID ) ) )
				{
					if( g_oMainCharacterInfo.byTrimuriti == g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti( dwTargetKeyID ) )
					{
						if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
						if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
						if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
						if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
						// ���� ����� ĳ���͸� Ŭ������ ���
						if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTradeMode( dwTargetKeyID ) != HT_STORE_MODE_END )
						{
							g_cIndividualStore->HT_vNetWork_CSP_Req_Store( dwTargetKeyID ); 
							return HT_OK;
						}
					}
				}
				//	����� �����̸�
				else if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
				{
					if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
					if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_pDuelSystem->HT_hrDuel_PickCheckFromOtherObject( iObject_ID ) ) )		{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_hrGuild_PickCheckFromOtherObject( iObject_ID ) ) )	{	return HT_OK;	}
					
					// ���� ����� ĳ���͸� Ŭ������ ���
					if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTradeMode( dwTargetKeyID ) != HT_STORE_MODE_END )
					{
						g_cIndividualStore->HT_vNetWork_CSP_Req_Store( dwTargetKeyID ); 
						return HT_OK;
					}
				}
				//	�Ϲ� �����϶�
				else
				{
					//	�ֽ��� ������ �ƴ� ���
					if( HT_SUCCEED( g_cParty->HT_vParty_JoinParty( iObject_ID ) ) )							{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_vGuild_JoinGuild( iObject_ID ) ) )					{	return HT_OK;	}
					if( HT_SUCCEED( g_cExchangeSystem->HT_vExchange_RequestTrade( iObject_ID ) ) )			{	return HT_OK;	}
					if( HT_SUCCEED( g_cAddress->HT_hrMouseCheck_OtherChar( iObject_ID ) ) )					{	return HT_OK;	}
					//	������� �ƴҶ���
					if( g_wResentZoneServerID != ZONE_BIRYUCASTLE )
                        if( HT_SUCCEED( g_pDuelSystem->HT_hrDuel_PickCheckFromOtherObject( iObject_ID ) ) )		{	return HT_OK;	}
					if( HT_SUCCEED( g_cGuildSystem->HT_hrGuild_PickCheckFromOtherObject( iObject_ID ) ) )	{	return HT_OK;	}
					
					// ���� ����� ĳ���͸� Ŭ������ ���
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

				//	��Ʈ�� Ű�� ������ �ִٸ� �ӼӸ��� ������ �̸��� �����Ѵ�.
				if( g_cInterfaceCheck->HT_vInterface_GetControlKey() )
				{
					//	�ӼӸ� ���·� ����� �ְ�..
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

//-----�� �˻�_NPC-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_NPC( HTint iObject_ID )
{
	HTint iTempID = g_sNPCSystem->HT_vNPCSystemComIDCheck( iObject_ID );
	if( iTempID != 0 )
	{
		//	�׸��带 ����Ͽ� ���� �׸��� �ȿ� �������� ����
		DWORD dwIndex = g_sNPCSystem->HT_pNPCSystem_GetIndexFromModelID( iTempID );
		HTPoint pCellPt = g_sNPCSystem->HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
		HTPoint pMainCharCell = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		if( pMainCharCell.x >= pCellPt.x-6 && pMainCharCell.x <= pCellPt.x+6 && 
			pMainCharCell.y >= pCellPt.y-6 && pMainCharCell.y <= pCellPt.y+6 )
		{
			//----------ĳ���� ���� ����----------//
			g_cMainCharacter->HT_vMainChar_SetStopMove();
			g_sNPCSystem->HT_pNPCSystem_PickConnect( iTempID );
			//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
			g_cMainCharacter->HT_vInterface_Pick_Map_DeleteEffect();
		}
		else
		{
			HT_CELL_COORD cellPos;
			cellPos.x = pCellPt.x + 1;
			cellPos.y = pCellPt.y + 1;
			g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_FALSE );
			//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
			g_cMainCharacter->HT_vInterface_Pick_Map_DeleteEffect();
		}
		return HT_OK;
	}

	return HT_FAIL;
}

//-----�� �˻�_Object-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Object( HTint nObjectID, HTvector3 vecPickPos )
{
	g_pEngineHandler->HT_hrPlaySound( 33525, 1 );	// Click Sound

	return g_cPortal->HT_vPortal_Click( nObjectID, vecPickPos );
}

//-----�� �˻�_��-----//
HTRESULT CHTInterfaceCheck::HT_vInterface_Pick_Map( HTvector3 vecPos )
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecPos, crdCell );

	//-----������ ������ üũ-----//
	HTint iTempID = 0;
	if (g_cItemSystem)
		iTempID = g_cItemSystem->HT_iSystem_MapCellCheckToItemOnMap( crdCell.x, crdCell.y );

	if( iTempID != 0 )
	{
		//-----���ݽÿ� �Է��� ������ ���� ����-----//
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

//----------Ű���� ��Ʈ��----------//
//-----Ű���� üũ_�ѹ��� ����-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_KeyDown( WPARAM wParam )
{
	// ���Ӿ����� ���������� ����

	// �Է����϶��� ó�� ����
	if (g_cUIManager->HT_isFocusOnEditBoxControl() == true)
		return;

	//	IME String Init (����Ű ���� ��� ������ ������·� ����)
	g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, 0 );
	g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	g_cImeMgr.InputString();

	//	�Է��� �������� �ؼ� �ڵ� ����� ���
	g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	ĳ���Ͱ� �׾���ȴٸ� �ؿ� �޽������� ���� ���Ѵ�.
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	{
		// ���׼��� 2005. 1. 18 ȭ���� �������¿��� ��Ȱâ �˾��� �ٸ���ư Ŭ���ص� ������ �ʰ� �Ѵ�. ������
		if (g_cUIManager->HT_isShowWindow( _DIALOG_REVIVEWND )) 
			g_cUIManager->HT_HideWindow( _DIALOG_REVIVEWND );

		//	ĳ���Ͱ� �׾������� �޽��� ���� �� �ִ� ��
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

	// ��� �ִ� ��쿡�� ó���Ǵ� �޽�����. 
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
		//	�߽��ڿ����� ����� ���ϰ� �Ѵ�.
		if( g_iInationalType == INATIONALTYPE_MEXICO )
			return;

		//	Return Get MoveStop Stauts
		if( !g_cMainCharacter->HT_bMainChar_GetMoveStopStatus() )	return;
		if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;
		if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )			return;
		
		//	���� ������ ������ KeyID ���
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
		//	�߽��ڿ����� ����� ���ϰ� �Ѵ�.
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
		//	�߽��ڿ����� ����� ���ϰ� �Ѵ�.
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

		case VK_F11 :	//	ī�޶� ��� ��ȭ
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
		case VK_F12 :	//	ī�޶� ��� ��ȭ
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
		case VK_INSERT:	//	ī�޶� �ʱⰪ ����
			g_cCamera.HT_vCamera_SetInitCameraMode();
			break;
	}

	// ���Ǿ� �̵�â || ������ �и�â || ������ ���� �Է�â || ���λ���-����â || ��ȯâ�� ������ ��� ó������ ���� ����Ű��
	if( g_cSystem->HT_bSystem_GetF1ToF10Mode() )
	{ // Slot Mode 
		switch(wParam)
		{
			case VK_TAB: // ȭ����� â �Ⱥ��̰� �ϱ�
				//g_iShowUI++;
				//if (g_iShowUI>3) g_iShowUI = 0;
				break;
			// ������
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
		// Skill ���
		switch(wParam)
		{
			case VK_TAB: // ȭ����� â �Ⱥ��̰� �ϱ�
				//g_iShowUI++;
				//if (g_iShowUI>3) g_iShowUI = 0;
				break;
			// ������
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

//-----Ű���� üũ_Up-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_KeyUp( WPARAM wParam )
{
	// �Է����϶��� ó�� ����
	if (g_cUIManager->HT_isFocusOnEditBoxControl() == true)
		return;

//	g_iGlobalKey = 0;

//	if (!(GetAsyncKeyState( 'E' ) < 0) ) 
//		g_iGlobalKeyE = 0;
//	if (!(GetAsyncKeyState( 'R' ) < 0) ) 
//		g_iGlobalKeyR = 0;
///	if (!(GetAsyncKeyState( 'F' ) < 0) ) 
//		g_iGlobalKeyF = 0;

	////	ĳ���Ͱ� �׾���ȴٸ�!
	//if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	//	return;

	////	ä��â�� Ȱ��ȭ ���¶��
	//if( g_cChatting->HT_bIsInputOn() )
	//	return;

	//switch(wParam)
	//{
	//	case ALPAHBAT_KEYVALUE_A :	//	��/�� ȸ��Ű üũ
	//	case ALPAHBAT_KEYVALUE_D :
	//		g_cMainCharacter->HT_vCharSetKeyDownCheck( HT_FALSE );
	//		break;
	//}
}

//-----Ű���� üũ_Function Key-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_FunctionKey( WPARAM wParam )
{
	//	ĳ���Ͱ� �׾���ȴٸ�!
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
	{
		if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
		{
			// ���콺 �������� �޽��� �ؼ� ������ �̵����̿��ٸ� ��ҽ�Ŵ
			g_cUIManager->HT_CancelSlotBoxImageMoving();

			// ����� ��Ȱâ ���
			if (g_cUIManager->HT_isShowWindow( _DIALOG_DEATHMSGFOTRESS ) == false)
				g_cUIManager->HT_ShowWindow( _DIALOG_DEATHMSGFOTRESS );

			//return;
		}
		else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
		{
			// ����� ��Ȱâ ���
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
					// ���� �Է����̿��ٸ� ���� �ʴ´�.
					if (g_cUIManager->HT_isFocusOnEditBoxControl() == true) return;

					CHTString szMessage;
					// Ȯ�� ��ư�� ������ ������������ �ٽ� �¾�ϴ�.
					
					// ���콺 �������� �޽��� �ؼ� ������ �̵����̿��ٸ� ��ҽ�Ŵ
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

//	Ȯ��/��Ȯ��â EnterŰ �Է�
HTvoid CHTInterfaceCheck::HT_vInterface_MessageWindowForEnterKey( HTint iDlgNo )
{
}

//	ESCŰ ������ �ڵ����� ������ â���� ������ �ֵ���
HTvoid CHTInterfaceCheck::HT_vInterface_ESC_CloseWindow()
{
	//	�ƹ��͵� �ɸ��� â�� ������ �ý���â�� ����.
	if (g_cUIManager->HT_CloseWindow() == false)
		g_cSystem->HT_vSystem_ActiveSw();
	else
		g_cSystem->m_bSystem_WindowActiveSw = HT_FALSE;
}

//-----Ű���� üũ_��� �����°�-----//
HTvoid CHTInterfaceCheck::HT_hrInterfaceKeyboard_Input_Continue()
{
	if( g_cUIManager->HT_isFocusOnEditBoxControl() )
		return;

	//	����ī�޶� ����尡 Ȱ��ȭ ���¶��
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

	//	ĳ���Ͱ� �׾���ȴٸ�!
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return;

	//	Return Get MoveStop Stauts
	if( !g_cMainCharacter->HT_bMainChar_GetMoveStopStatus() )	return;
	if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )			return;

	if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
	{
		//-----ĳ���� ����-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_W ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Go( m_fInterfaceElapsedTime );
		}
		//-----ĳ���� RIGHT-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_D ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Right();
		}
		//-----ĳ���� LEFT-----//
		if( GetAsyncKeyState( ALPAHBAT_KEYVALUE_A ) < 0 )
		{
			g_cMainCharacter->HT_vCharSetMoveForward_Left();
		}
		//	�̻��ϰ� F10�� ������ �޽����� �������� �ε����ϰ� ���⿡�� ��´� ��Ÿ��� ������
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


//----------���μ����� ���� �������� �̴�----------//
HTvoid CHTInterfaceCheck::HT_hrInterfaceControlEnd()
{
	g_iInterface.iLeftClick = HT_FALSE;
}

//-----ElapsedTime ����-----//
HTvoid CHTInterfaceCheck::HT_vInterface_SetElapsedTime( HTfloat fElapsedTime )
{
	m_fInterfaceElapsedTime = fElapsedTime;
}

HTbool
CHTInterfaceCheck::HT_bSetCharMonHPAttach()
{
	return HT_TRUE;
}

//	�׾߸��� ������ �Կ��� ���� �ӽ��ڵ�
HTvoid
CHTInterfaceCheck::HT_vInterface_LoadCameraForBroadcast()
{
	char buff[64];

	FILE*	fp;
	fp = fopen( "������.txt", "r" );
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
