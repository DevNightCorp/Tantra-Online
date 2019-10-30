#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTChatRoom.h"

// HTGamble.cpp ������ ���̴� ��� ����

const int UI_WINDOW_CHATROOM = _DIALOG_CHATROOM;			// IMAGE TYPE GAMBLE WINDOW NUMBER (�׸� ���� ������)
const int UI_WINDOW_CHATROOM2 = _DIALOG_CHATROOM_CREATE;	// IMAGE TYPE GAMBLE WINDOW NUMBER (�׸� ���� ������)
const int UI_WINDOW_CHATROOM3 = _DIALOG_CHATROOM_MSG;		// IMAGE TYPE GAMBLE WINDOW NUMBER (�׸� ���� ������)
const int UI_WINDOW_CHATROOM4 = _DIALOG_CHATROOM_WAITING;	// IMAGE TYPE GAMBLE WINDOW NUMBER (�׸� ���� ������)

bool g_bChatServerConnectState = false;

//
// ���� �ܺο��� ���̴� �Լ����Դϴ�. (Public Type)
//
HTChatRoom::HTChatRoom(void) 
{
	g_bChatServerConnectState = false;
	m_iTotalLine = 0;
	m_iEndLoc = 0;
}

HTChatRoom::~HTChatRoom(void)
{
	// ä��â�� �Ҹ�Ǹ� ������ ���������.
	if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)
		g_pChatNetWorkMgr->DisConnect();

	g_cUIManager->HT_DeleteWindow( UI_WINDOW_CHATROOM );
	g_cUIManager->HT_DeleteWindow( UI_WINDOW_CHATROOM2 );
	g_cUIManager->HT_DeleteWindow( UI_WINDOW_CHATROOM3 );
	g_cUIManager->HT_DeleteWindow( UI_WINDOW_CHATROOM4 );
}

// ó�� �ѹ��� ����� (�̰����� UI Window ���� �� �ʿ��� ��Ʈ���� �����Ѵ�) 
// ��Ʈ�� ��ġ�� ���� �ణ�� �밡�� �ʿ�;; (������ UI �� ���߿�����)
HTvoid HTChatRoom::HT_vChatRoom_Init()
{
	CHTString strMessage;

	// �����츦 �����մϴ�.
	//g_cUIManager->HT_SetScriptMessage( eMsgYutTitle, &strMessage, _T(""), _T("") );
	//g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM, strMessage, 330, 466, g_cChatRoom->HT_hrChatRoom_InputCheck, 2);
	g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM, _T("ChatRoom"), 330, 466, g_cChatRoom->HT_hrChatRoom_InputCheck, 2);
	//g_cUIManager->HT_MoveWindow(UI_WINDOW_GAMBLE, 150, 150);
	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 8, 3, 37, 1400, 324, 6);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 1, eMsgChatRoomMessage1, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 3, 43, 75, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 8, 2, 58, 1400, 324, 3);
//	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_CHATROOM, 1, 4);

	// ��ư 3��
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 1, 65, 4, 63, 65, 64, 1500, 92, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, eMsgChatRoomMessage2, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 4, 63, 92, 19);
	
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 2, 63, 97, 63, 65, 64, 1500, 62, 19);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 97, 63, 62, 19);

	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 3, 63, 160, 63, 65, 64, 1500, 62, 19);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("�����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 160, 63, 62, 19);

	// ������ ��ư (279, 68) (296) (311)
	// 145, 146, 147
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 4, 148, 279, 68, 150, 149);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 143, 296, 68 );
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 2, _T("1"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 296, 68, 16, 16);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 5, 145, 311, 68, 146, 147);

	// ���ζ��� ����
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 8, 4, 87, 1400, 322, 3);

	for (int i = 0; i < 16; ++i)
	{
		// ���� ���� 16�� ���
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 8, 4, 87+((i+1)*21), 1400, 322, 3);

		// �� 4���� 16�� ���
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, (i*4)+3, _T(" "), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 4, 87+(i*21)+5, 42, 14);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, (i*4)+4, _T(" "), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 47, 87+(i*21)+5, 147, 14);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, (i*4)+5, _T(" "), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 196, 87+(i*21)+5, 91, 14);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, (i*4)+6, _T(" "), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 289, 87+(i*21)+5, 38, 14);
	}

	// �漱�� ��ư ����
	for (i = 0; i < 15; ++i)
	{
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, i+100, 0, 4, 107+(i*21)+1, 202, 0, 1500, 305, 20);
	}

	// Label 1,2,3,4... 
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 3, eMsgChatRoomMessage3);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 4, eMsgChatRoomMessage4);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 5, eMsgChatRoomMessage5);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 6, eMsgChatRoomMessage6);

	// ���� ���� 3�� ���
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 1, 45, 87, 1400, 4, 336);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 1, 193, 87, 1400, 4, 336);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM, 0, 1, 286, 87, 1400, 4, 336);
	
	// 25, 424, �游��� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 6, 216, 25, 434, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, eMsgChatRoomMessage7, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 25, 434, 64, 19);

	// 161, 424, ���� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 7, 216, 161, 434, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, eMsgChatRoomMessage8, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 161, 434, 64, 19);

	// 235, 424, �ݱ� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 8, 216, 235, 434, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, eMsgChatRoomMessage9, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 235, 434, 64, 19);

	// �׽�Ʈ�� ���� ��ư�� �߰�
	/*
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 10, 159, 25, 454, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("�����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 25, 454, 64, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 11, 159, 90, 454, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("������"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 90, 454, 64, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 12, 159, 154, 454, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("�泪��"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 154, 454, 64, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 13, 159, 208, 454, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("�����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 208, 454, 64, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM, 14, 159, 272, 454, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM, 0, _T("�̻��"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 272, 454, 64, 19);
	*/


	// ����� ������ ����� //
	g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM2, _T("ChatRoom"), 330, 208, g_cChatRoom->HT_hrChatRoomCreate_InputCheck, 2);
	//g_cUIManager->HT_MoveWindow(UI_WINDOW_CHATROOM2, 150, 150);
	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 37, 1400, 324, 6);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 1, eMsgChatRoomMessage10, 0, HT_COLOR( 1, 1, 1, 1), HT_COLOR( 1, 1, 1, 1), 3, 43, 106, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 2, 58, 1400, 324, 3);

	// ������
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 1, 109, 42, 1400, 4, 105);

	// ������
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 58, 1400, 106, 3);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 1, eMsgChatRoomMessage11, 0, HT_COLOR( 1, 1, 1, 1), HT_COLOR( 1, 1, 1, 1), 3, 63, 106, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 80, 1400, 106, 3);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 1, eMsgChatRoomMessage12, 0, HT_COLOR( 1, 1, 1, 1), HT_COLOR( 1, 1, 1, 1), 3, 85, 106, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 102, 1400, 106, 3);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 1, eMsgChatRoomMessage13, 0, HT_COLOR( 1, 1, 1, 1), HT_COLOR( 1, 1, 1, 1), 3, 107, 106, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 124, 1400, 106, 3);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 1, eMsgChatRoomMessage14, 0, HT_COLOR( 1, 1, 1, 1), HT_COLOR( 1, 1, 1, 1), 3, 129, 106, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 8, 3, 146, 1400, 106, 3);

	// ������ �ڽ�
//	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM2, 0, 9, 112, 61);
	g_cUIManager->HT_AddEditBoxControl(UI_WINDOW_CHATROOM2,1, 9, 112, 61, 152, 19);
	g_cUIManager->HT_AddEditBoxControl(UI_WINDOW_CHATROOM2,2, 11, 112, 81, 79, 19);
	g_cUIManager->HT_AddEditBoxControl(UI_WINDOW_CHATROOM2,3, 11, 112, 127, 79, 19);
	g_cUIManager->HT_SetEditBoxControlLimitText(UI_WINDOW_CHATROOM2, 1, 20);
	g_cUIManager->HT_SetEditBoxControlLimitText(UI_WINDOW_CHATROOM2, 2, 1);
	g_cUIManager->HT_SetEditBoxControlLimitText(UI_WINDOW_CHATROOM2, 3, 8);
	g_cUIManager->HT_SetModeEditBoxControl(UI_WINDOW_CHATROOM2, 3, 1);

	// ��ư
	// 59, 179, �游��� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM2, 1, 159, 59, 179, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 0, eMsgChatRoomMessage15, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 59, 179, 64, 19);

	// 120, 179, ���� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM2, 2, 159, 211, 179, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM2, 0, eMsgChatRoomMessage16, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 211, 179, 64, 19);

	


	// ä�ù� ������ �����
	
	g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM3, _T("ChatRoom"), 330, 466, g_cChatRoom->HT_hrChatRoom2_InputCheck, 2);
	//g_cUIManager->HT_MoveWindow(UI_WINDOW_GAMBLE, 150, 150);
	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 3, 37, 1400, 324, 6);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 1, _T("."), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 3, 43, 320, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 2, 58, 1400, 327, 3);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_CHATROOM3, 1, 4);

	// ��ư 3��
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 1, 65, 4, 63, 65, 64, 1500, 92, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage17, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 4, 63, 92, 19);
	
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 2, 63, 97, 63, 65, 64, 1500, 62, 19);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, _T("����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 97, 63, 62, 19);

	// ������ ��ư (279, 68) (296) (311)
	// 145, 146, 147
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 4, 148, 279, 68, 150, 149);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 143, 296, 68 );
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 2, _T("1"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 296, 68, 16, 16);
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 5, 145, 311, 68, 146, 147);

	// ���ζ��� ����
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 4, 87, 1400, 322, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 4, 386, 1400, 231, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 4, 408, 1400, 322, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 4, 408, 1400, 322, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 8, 4, 103, 1400, 322, 3);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage18, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 5, 90, 230, 14);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage19, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 238, 90, 88, 14);

	for (int i = 0; i < 8; ++i)
	{
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, (i*4)+6, _T(" "), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 239, 87+(i*20)+20, 88, 14);
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, i+100, 0, 239, 87+(i*20)+37, 201, 0, 1500, 83, 15);
		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM3, i+100, false);
	}
	// Label 1,2,3,4... 
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 3, _T("Chatting"));

	//	Label Chat Text List
	for( HTint i=0 ; i<15 ; i++)
	{
		g_cUIManager->HT_AddLongLabelControl( UI_WINDOW_CHATROOM3, 100+i, _T(" "), 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.0f, 0.0f, 0.0f, 1.0f), 4, 110+(i*17), 217, 60);
		g_cUIManager->HT_SetArrangementLongLabelControl( UI_WINDOW_CHATROOM3, 100+i, 7 );
	}

	// ä�ù� ��ũ�ѹ�
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_CHATROOM3, 1, 222, 105, 282, 100);

	// ä�� �Է�â ���
	g_cUIManager->HT_AddEditBoxControl(UI_WINDOW_CHATROOM3, 1, 0, 4, 391, 202, 19);
	g_cUIManager->HT_SetEditBoxFocusOnIME(UI_WINDOW_CHATROOM3, 1, 1);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 3, 219, 204, 387, 220, 221);
	g_cUIManager->HT_SetEditBoxControlLimitText(UI_WINDOW_CHATROOM3, 1, 47);
	g_cUIManager->HT_SetButtonEnterOn(UI_WINDOW_CHATROOM3, 3);

	// ���� ���� 3�� ���
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM3, 0, 1, 236, 87, 1400, 4, 320);
	
	// 25, 424, ������ ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 6, 216, 20, 424, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage10, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 20, 424, 64, 19);

	// 25, 424, ������ ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 7, 216, 95, 424, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage20, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 95, 424, 64, 19);

	// 25, 424, ������ ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 8, 216, 170, 424, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage21, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 170, 424, 64, 19);

	// 25, 424, ������ ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM3, 9, 216, 245, 424, 217, 218);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM3, 0, eMsgChatRoomMessage22, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 245, 424, 64, 19);


	// ����� ����Ʈ ������ �����

	// �����츦 �����մϴ�.
	//g_cUIManager->HT_SetScriptMessage( eMsgYutTitle, &strMessage, _T(""), _T("") );
	//g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM4, strMessage, 330, 466, g_cChatRoom->HT_hrChatRoom_InputCheck, 2);
	g_cUIManager->HT_CreateWindow(UI_WINDOW_CHATROOM4, _T("ChatRoom"), 230, 446, g_cChatRoom->HT_hrChatRoom3_InputCheck, 2);
	//g_cUIManager->HT_MoveWindow(UI_WINDOW_GAMBLE, 150, 150);
	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 8, 3, 37, 1400, 224, 6);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 1, eMsgChatRoomMessage1, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 3, 43, 75, 14);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 8, 2, 58, 1400, 224, 3);
//	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_CHATROOM4, 1, 4);

	// ��ư 3��
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 1, 65, 4, 63, 65, 64, 1500, 92, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, eMsgChatRoomMessage2, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 4, 63, 92, 19);
	
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 2, 63, 97, 63, 65, 64, 1500, 62, 19);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, _T("����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 97, 63, 62, 19);

	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 3, 63, 160, 63, 65, 64, 1500, 62, 19);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, _T("�����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 160, 63, 62, 19);

	// ������ ��ư (279, 68) (296) (311)
	// 145, 146, 147
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 4, 148, 179, 68, 150, 149);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 143, 196, 68 );
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 2, _T("1"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 196, 68, 16, 16);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 5, 145, 211, 68, 146, 147);

	// ���ζ��� ����
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 8, 4, 87, 1400, 222, 3);

	for (int i = 0; i < 20; ++i)
	{
		// ���� ���� 16�� ���
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 8, 4, 87+((i+1)*17), 1400, 222, 3);

		// �� 4���� 16�� ���
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, (i*4)+3, _T("-"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 4, 87+(i*17)+5, 42, 14);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, (i*4)+4, _T("-"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 47, 87+(i*17)+5, 147, 14);
		//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, (i*4)+5, _T("-"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 196, 87+(i*21)+5, 91, 14);
		//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, (i*4)+6, _T("-"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 289, 87+(i*21)+5, 38, 14);
	}

	// �漱�� ��ư ����
	for (i = 0; i < 20; ++i)
	{
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, i+100, 0, 4, 107+(i*17)+1, 202, 0, 1500, 205, 17);
	}

	// Label 1,2,3,4... 
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 3, eMsgChatRoomMessage23);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 4, eMsgChatRoomMessage24);
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 5, _T("����"));
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 6, _T("���̵�"));

	// ���� ���� 3�� ���
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 1, 45, 87, 1400, 4, 338);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 1, 193, 87, 1400, 4, 336);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_CHATROOM4, 0, 1, 286, 87, 1400, 4, 336);
	
	// 25, 424, �游��� ��ư
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 6, 216, 25, 434, 217, 218);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, _T("�游���"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 25, 434, 64, 19);

	// 161, 424, ���� ��ư
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 7, 216, 161, 434, 217, 218);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, _T("����"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 161, 434, 64, 19);

	// 235, 424, �ݱ� ��ư
	//g_cUIManager->HT_AddButtonControl(UI_WINDOW_CHATROOM4, 8, 216, 235, 434, 217, 218);
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_CHATROOM4, 0, _T("�ݱ�"), 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 235, 434, 64, 19);

	// ������ �˾�
	//g_cUIManager->HT_ShowWindow(UI_WINDOW_CHATROOM4);

	// ä�ù� ���� ��� ������ ��� �� �����ϰ� ����
	g_cUIManager->HT_SetBackgroundDownEnable(UI_WINDOW_CHATROOM, true);
	g_cUIManager->HT_SetBackgroundDownEnable(UI_WINDOW_CHATROOM2, true);
	g_cUIManager->HT_SetBackgroundDownEnable(UI_WINDOW_CHATROOM3, true);
	g_cUIManager->HT_SetBackgroundDownEnable(UI_WINDOW_CHATROOM4, true);
}

// ó�� ȭ�� �˾��� ȣ�� (UI �⺻�۾�)
HTvoid HTChatRoom::HT_vChatRoom_WindowPopup()
{ 
	// ä�ü����� ������ �õ��Ѵ�.
	if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)
		g_pChatNetWorkMgr->DisConnect();

	g_cChatRoom->m_iRoomNo = -1;
	m_bReader = false;
	m_bCreate = false;
	m_iWaitingPage = 0;
	m_iChatRoomPage = 0;
	m_iWaitingMember = 0;

	CHTString g_strChatServerIP;
	// ä�ü����� ������ �õ��Ѵ�.
	
	FILE *fp = fopen("./ChatServer.cfg","rt");
	if ( fp != NULL )
	{
		memset(g_pServerList,0,sizeof(g_pServerList));
		char str[256];
		char address[64];
		char * ret = fgets((char*)str,255,fp);

		if (ret!=NULL)
		{
			sscanf(str,"%s", address);
			strcpy(g_strChatServerIP, str);
		}
		fclose(fp);
	}
	else
	{
		g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, "Cannot Open ChatServer.cfg!!");
		return;
		//g_strChatServerIP = "211.43.194.56";	// �׽�Ʈ ��
	}

	g_pChatNetWorkMgr->Connect( g_strChatServerIP, CHAT_PORT);
	
	// true�� ��� ������ �Ǿ����� ��������� Ȯ���Ͽ� ���� ������ �Ǹ� �α��� ��Ŷ�� �θ��� ���信�� â�� ����־� ������� ó���� �ϵ��� �Ѵ�.
	g_bChatServerConnectState = true;	

	//CHTString strMessage;
	//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage25, &str );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
}

// ���ῡ �����Ͽ����� ������� ����. ������ �����ϸ� ä�ü������� �α��� ��Ŷ ������.
HTvoid HTChatRoom::HT_vChatRoom_ConnectLoopCheck()
{
	if (g_bChatServerConnectState == true)
	{
		if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)
		{
			// ä�ü����� ����Ǿ����ϴ�. �ý���â�� ����� �α��� ��Ŷ ����
			g_bChatServerConnectState = false;
			
			// ������ ���� �� ���� ��û ��Ŷ�� ������. (������ ��ü ���� ��Ŷ ��û�� ������ �׶����� â ���)
			// �α��� ��Ŷ ����
			this->HT_vNetWork_CSP_Req_AccountLogin();
		}
	}
} 

// â ������ ȣ���ؾ��ϴ� �Լ� (UI �⺻�۾�)
HTvoid HTChatRoom::HT_vChatRoom_WindowHide()
{
	// ä�ü����� ������ �õ��Ѵ�.
	if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE)
	{
		g_pChatNetWorkMgr->DisConnect();

		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage26, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
	}

	g_cChatRoom->m_iRoomNo = -1;
	g_bChatServerConnectState = false;
	g_cUIManager->HT_HideWindow(UI_WINDOW_CHATROOM);
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
HTvoid HTChatRoom::HT_vChatRoom_SetInfo()
{ 
	int iTotalLine = m_iTotalLine;

	int iStartLoc  = m_iEndLoc;
	for (int iChatCount = 0; iChatCount < iTotalLine; ++iChatCount)
	{
		// �Ϲ����� ���
		g_cUIManager->HT_SetTextLongLabelControl( UI_WINDOW_CHATROOM3, 100 + iChatCount, m_oChatMsg[ iStartLoc - iTotalLine + iChatCount - (m_iTotalScrollLine - m_ScrollVarValue)].strMsg );
		//g_cUIManager->HT_SetTextColorLabelControl( UI_WINDOW_CHATROOM3, 100+iChatCount, m_oChatMsg[iStartLoc+iChatCount].clrColor );
	}
}

// ä��â�� ���� ����
HTvoid HTChatRoom::HT_vChatRoom_SetText(CHTString str)
{

	HT_RECT iRect;
	iRect.left = 0; iRect.right = 217; iRect.top = 0; iRect.bottom = 100;

	m_iTotalLine++;
	if (m_iTotalLine > 15) 
	{
		m_iTotalScrollLine++;
		// �̶����� �ƽ� ��ũ�ѹ� ����
		g_cUIManager->HT_SetScrollBarControlMaxValue( UI_WINDOW_CHATROOM3, 1, m_iTotalScrollLine);
		g_cUIManager->HT_SetScrollBarControl( UI_WINDOW_CHATROOM3, 1, g_cUIManager->HT_GetScrollBarValue( UI_WINDOW_CHATROOM3, 1) + 1);
		m_ScrollVarValue = g_cUIManager->HT_GetScrollBarValue( UI_WINDOW_CHATROOM3, 1);
		m_iTotalLine = 15;
	}

	m_oChatMsg[m_iEndLoc].strMsg = str;
	int ComHeight = g_pEngineHandler->HT_iGetTextHeight( HT_FONT_GULIM_12, _T("a"), iRect, TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );

	iRect.left = 0; iRect.right = 217; iRect.top = 0; iRect.bottom = 100;
	int height = g_pEngineHandler->HT_iGetTextHeight( HT_FONT_GULIM_12, str, iRect, TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );

	height = height / ComHeight;

	m_iEndLoc++;
	if (m_iEndLoc > MAXSCROLLLINE) 
	{
		m_iEndLoc = 0;
		m_iTotalLine = 0;
		m_iTotalScrollLine = 0;

		g_cUIManager->HT_SetScrollBarControl(UI_WINDOW_CHATROOM3, 1, 0);
		g_cUIManager->HT_SetScrollBarControlMaxValue( UI_WINDOW_CHATROOM3, 1, 0);
		m_ScrollVarValue = 0;

		// ä�ù� ä��â �ؽ�Ʈ ����
		for (int iChatCount = 0; iChatCount < 15; ++iChatCount)
		g_cUIManager->HT_SetTextLongLabelControl( UI_WINDOW_CHATROOM3, 100+iChatCount, _T(" "));

	}

	if (height > 1)
	{
		for (int i = 1; i< height; ++i)
		{
			m_oChatMsg[m_iEndLoc].strMsg = " ";
			
			m_iEndLoc++;
			m_iTotalLine++;
			if (m_iEndLoc > MAXSCROLLLINE) 
			{
				m_iEndLoc = 0;
				m_iTotalLine = 0;
				m_iTotalScrollLine = 0;

				g_cUIManager->HT_SetScrollBarControl(UI_WINDOW_CHATROOM3, 1, 0);
				g_cUIManager->HT_SetScrollBarControlMaxValue( UI_WINDOW_CHATROOM3, 1, 0);
				m_ScrollVarValue = 0;


				// ä�ù� ä��â �ؽ�Ʈ ����
				for (int iChatCount = 0; iChatCount < 15; ++iChatCount)
					g_cUIManager->HT_SetTextLongLabelControl( UI_WINDOW_CHATROOM3, 100+iChatCount, _T(" "));
			}
		}
	}

	this->HT_vChatRoom_SetInfo();
}

// ä��â�� ���� �ʱ�ȭ
HTvoid HTChatRoom::HT_vChatRoom_ClearText()
{
	m_iTotalLine = 0;
	m_iTotalScrollLine = 0;
	m_iEndLoc = 0;

	g_cUIManager->HT_SetScrollBarControl(UI_WINDOW_CHATROOM3, 1, 0);
	g_cUIManager->HT_SetScrollBarControlMaxValue( UI_WINDOW_CHATROOM3, 1, 0);
	m_ScrollVarValue = 0;

	for (int i = 0; i < MAXSCROLLLINE; i++)
		m_oChatMsg[i].strMsg = _T("");

	for (int j = 0; j< 15; j++)
		g_cUIManager->HT_SetTextLongLabelControl( UI_WINDOW_CHATROOM3, 100 + j, _T(""));

	this->HT_vChatRoom_SetInfo();
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void HTChatRoom::HT_hrChatRoom_InputCheck(int iAction, int iTarget, int iTargetID)
{ 
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:
		{
			if (iTargetID == -2) return;
			if (iTargetID == -1)	// �����ư Ŭ���� â ����
			{
				g_cChatRoom->HT_vChatRoom_WindowHide();
				return;
			}

			if (iTargetID == 4)
			{
				CHTString str;
				g_cChatRoom->m_iChatRoomPage--;
				if (g_cChatRoom->m_iChatRoomPage < 0) g_cChatRoom->m_iChatRoomPage = 0;
				str.HT_szFormat("%d", g_cChatRoom->m_iChatRoomPage+1);
				g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 2, str);
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();	// ���� ���� ���ſ�û
			}

			if (iTargetID == 5)
			{
				CHTString str;
				g_cChatRoom->m_iChatRoomPage++;
				if (g_cChatRoom->m_iChatRoomPage > 2) g_cChatRoom->m_iChatRoomPage = 2;
				str.HT_szFormat("%d", g_cChatRoom->m_iChatRoomPage+1);
				g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, 2, str);
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();	// ���� ���� ���ſ�û
			}

			switch(iTargetID)
			{
			case 1: // ���ΰ�ħ
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();
				break;
			case 6: // �����
				{
					g_cChatRoom->m_bCreate = true;
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage27, &str );
					g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 1, str);
					g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 2, _T("8"));
					g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 3, _T("CleanBox"));
					g_cUIManager->HT_WindowArrangement(UI_WINDOW_CHATROOM2, 5);
					
					g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM2 );
					g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM2, 1);
				}
				break;
			case 7: // ������
				if (g_cChatRoom->m_iRoomNo >= 0)
				{
					CHTString str;
					if (g_cChatRoom->m_iByPass[g_cChatRoom->m_iRoomNo] != 1 )
					{
						g_cChatRoom->m_strPassWord = _T("");
						
						g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage28, &str );
						str.HT_szFormat(str.HT_szGetString(), g_cChatRoom->m_iRoomNo+1);
						g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, str, UI_MESSAGEBOX_RECONFIRM); 
						g_cChatRoom->m_iMessageBoxMode = 1;
					}
					else
					{
						
						g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage29, &str );
						g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, str, UI_MESSAGEBOX_INPUT); 
						g_cChatRoom->m_iMessageBoxMode = 2;
						
					}
				}
				break;
			case 8: // �ݱ�
				g_cChatRoom->HT_vChatRoom_WindowHide();
				break;
			}
			// �漱�ý� �ش� ������ ����
			if (iTargetID >= 100)
			{
				if (g_cChatRoom->m_iRoomNo == g_cChatRoom->m_iByNo[iTargetID - 100])
				{
					CHTString str;
					if (g_cChatRoom->m_iByPass[g_cChatRoom->m_iRoomNo] != 1 )
					{
						g_cChatRoom->m_strPassWord = _T("");
						str.HT_szFormat(str.HT_szGetString(), g_cChatRoom->m_iRoomNo+1);
						g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, str, UI_MESSAGEBOX_RECONFIRM); 
						g_cChatRoom->m_iMessageBoxMode = 1;
					}
					else
					{
						g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage29, &str );
						g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, str, UI_MESSAGEBOX_INPUT); 
						g_cChatRoom->m_iMessageBoxMode = 2;
						
					}
				}
				else
				{
					g_cChatRoom->m_iRoomNo = g_cChatRoom->m_iByNo[iTargetID - 100];
					g_cChatRoom->m_strTitle.HT_szFormat("%d. %s", g_cChatRoom->m_iRoomNo+1, g_cChatRoom->m_ibyChatRoomName[iTargetID - 100].HT_szGetString());
					
					for (int i = 0; i < 15; ++i)
						g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM, i+100, 0);

					g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM, iTargetID, 3);
				}
			}
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		{
			if (g_cChatRoom->m_iMessageBoxMode == 1)	// �����忩�� ����
			{
				if (iTargetID == 2)
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomJoin();
				}
			}
			else if (g_cChatRoom->m_iMessageBoxMode == 2)	// ����� �� ������ ���� ��й�ȣ �Է�
			{
				if (iTargetID == -1 || iTargetID == 3)
					return;

				g_cChatRoom->m_strPassWord = g_cUIManager->m_strMessageBoxText;
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomJoin();
			}
			else if (g_cChatRoom->m_iMessageBoxMode == 3)	// �ʴ� �޽��� �޾��� ��� ó��
			{
				if (iTargetID == -1 || iTargetID == 3)
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomInvite(2, 1);	// �ź�
					return;
				}

				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomInvite(2, 0);	// ����
			}
		}
		break;
	}
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void HTChatRoom::HT_hrChatRoomCreate_InputCheck(int iAction, int iTarget, int iTargetID)
{ 
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:
		{
			if (iTargetID == -2) return;
			if (iTargetID == -1)	// �����ư Ŭ���� â ����
			{
				g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM2 );
				g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM4 );

				if (g_cChatRoom->m_bCreate == true)	// ��������̶�� �����
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();	// ���� ���� ���ſ�û

				return;
			}

			switch(iTargetID)
			{
				case 1: // Ȯ�� ��ư Ŭ���� �����
					{
						int temp = atoi(g_cUIManager->HT_GetTextEditBoxControl( UI_WINDOW_CHATROOM2, 2 ));

						strcpy(g_cChatRoom->m_strTitle, g_cUIManager->HT_GetTextEditBoxControl( UI_WINDOW_CHATROOM2, 1 ));

						if (temp < 1 || temp > 8 || strcmp(g_cChatRoom->m_strTitle, _T("")) == 0)
						{
							//CHTString strMessage;
							//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
							//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
							CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage30, &str );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
							return;
						}

						strcpy(g_cChatRoom->m_strMemberNo, g_cUIManager->HT_GetTextEditBoxControl( UI_WINDOW_CHATROOM2, 2 ));
						strcpy(g_cChatRoom->m_strPassWord, g_cUIManager->HT_GetTextEditBoxControl( UI_WINDOW_CHATROOM2, 3 ));
							
						g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM2 );
						g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM4 );

						if (g_cChatRoom->m_bCreate == true)	// ��������̶�� �����
						{
							g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomCreate();	// ����� ȣ��
						}
						else	// �׷��� �ʴٸ� �� ���� ���� ������ ó��
						{
							g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomUpdate();	// �泻�� ���� ȣ��
						}
					}
					break;
				case 2:	// ��� ��ư Ŭ����
					g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM2 );
					g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM4 );

					if (g_cChatRoom->m_bCreate == true)	// ��������̶�� �����
					{
						g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();	// ���� ���� ���ſ�û
					}
					break;
				default:
					g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM2 );
					g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM4 );
					break;
			}
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		{
		}
		break;
	}
}


// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void HTChatRoom::HT_hrChatRoom2_InputCheck(int iAction, int iTarget, int iTargetID)
{ 
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:
		{
			if (iTargetID == -2) return;
			if (iTargetID == -1)	// �����ư Ŭ���� â ����
			{
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomGoout();
				return;
			}

			if (iTargetID >= 100 && iTargetID < 108)
			{
				//CHTString str;
				
				CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage31, &str );
				str.HT_szFormat(str.HT_szGetString(), g_cChatRoom->m_oRoomMember[iTargetID-100].szName);

				g_cChatRoom->m_iTargetID = g_cChatRoom->m_oRoomMember[iTargetID-100].iID;
				strcpy(g_cChatRoom->m_szTargetName, g_cChatRoom->m_oRoomMember[iTargetID-100].szName);

				g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM3, str, UI_MESSAGEBOX_RECONFIRM); 
				g_cChatRoom->m_iMessageBoxMode = 1;
			}

			switch(iTargetID)
			{
				case 3:	// ä��â �Է�
					{
					CHTString str;
					str = g_cUIManager->HT_GetTextEditBoxControl(UI_WINDOW_CHATROOM3, 1);
					
					if (str.HT_iStringCompare("") != 0) 
					{
						CHTString str2;
						str2.HT_szFormat(" %s", str.HT_szGetString());
						g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(str2);
					}

					g_cUIManager->HT_SetTextEditBoxControl(UI_WINDOW_CHATROOM3, 1, _T("CleanBox"));
					g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM3, 1);
					break;
					}

				case 6: // ����޴� �˾� (���常 ����)
					{
						if ( g_cChatRoom->m_bReader == true)	// ������ ���� �����
						{
							g_cChatRoom->m_bCreate = false;
							g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 1, g_cChatRoom->m_strTitle);
							g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 2, g_cChatRoom->m_strMemberNo);

							if (g_cChatRoom->m_strPassWord.HT_iStringCompare("") == 0)
								g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 3, _T("CleanBox"));
							else
								g_cUIManager->HT_SetTextEditBoxControl( UI_WINDOW_CHATROOM2, 3, g_cChatRoom->m_strPassWord);

							g_cUIManager->HT_WindowArrangement(UI_WINDOW_CHATROOM2, 5);
					
							g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM2 );
							g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM2, 1);
						}
						else
						{
							//CHTString strMessage;
							//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
							//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
							CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage32, &str );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
						}

					}
					break;
				case 7: // �ʴ��ϱ� �˾� (���常 ����)
					// ������ ��쿡�� �ʴ��� Ȱ��ȭ
					if (g_cChatRoom->m_bReader == true)
					{
						g_cChatRoom->m_iWaitingPage = 0;
						g_cChatRoom->HT_vNetWork_CSP_Req_ChatWaitingListRequest();
						//g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomInvite(1)
					}
					else
					{
						//CHTString strMessage;
						//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
						//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
						CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage32, &str );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
					}
					break;
				case 8: // û���ϱ� ����
					g_cChatRoom->HT_vChatRoom_ClearText();
					break;
				case 9: // ������
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomGoout();
					break;
				case 2:
				default:
					break;

			}
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		{
			if (g_cChatRoom->m_iMessageBoxMode == 1)	// �߹� �޽����ڽ� ó��
			{
				if (iTargetID == -1 || iTargetID == 3)
					return;

				// �ش� ĳ���� �߹�
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomOrder(1, g_cChatRoom->m_iTargetID, g_cChatRoom->m_szTargetName);
				g_cChatRoom->HT_vSetText_Cut(g_cChatRoom->m_szTargetName.HT_szGetString());
			}
		}
		break;
	case UI_TARGET_SCROLLBAR:
		{
			if (iTargetID == 1)
			{
				g_cChatRoom->m_ScrollVarValue = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_CHATROOM3, 1);
				g_cChatRoom->HT_vChatRoom_SetInfo();
			}
		}
		break;
	}
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void HTChatRoom::HT_hrChatRoom3_InputCheck(int iAction, int iTarget, int iTargetID)
{ 
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:
		{
			if (iTargetID == -2) return;
			if (iTargetID == -1)	// �����ư Ŭ���� â ����
			{
				g_cUIManager->HT_HideWindow(UI_WINDOW_CHATROOM4);
				return;
			}

			if (iTargetID == 1)	// ���ΰ�ħ Ŭ���� ����
			{
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatWaitingListRequest();
			}

			if (iTargetID == 4)
			{
				CHTString str;
				g_cChatRoom->m_iWaitingPage--;
				if (g_cChatRoom->m_iWaitingPage < 0) g_cChatRoom->m_iWaitingPage = 0;
				str.HT_szFormat("%d", g_cChatRoom->m_iWaitingPage+1);
				g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 2, str);
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatWaitingListRequest();
			}

			if (iTargetID == 5)
			{
				CHTString str;
				g_cChatRoom->m_iWaitingPage++;
				if (g_cChatRoom->m_iWaitingPage > 5) g_cChatRoom->m_iWaitingPage = 5;
				str.HT_szFormat("%d", g_cChatRoom->m_iWaitingPage+1);
				g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, 2, str);
				g_cChatRoom->HT_vNetWork_CSP_Req_ChatWaitingListRequest();
			}

			// ����� ��� Ŭ���� �ش� ����� ��û ����
			if (iTargetID >= 100)
			{
				CHTString str;
				g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage33, &str );
				str.HT_szFormat(str.HT_szGetString(), g_cChatRoom->m_oWaitingMember[iTargetID-100].szName);
				g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM4, str, UI_MESSAGEBOX_RECONFIRM); 
				g_cChatRoom->m_iMessageBoxMode = 1;
				g_cChatRoom->m_iWaitingMember = iTargetID-100;
				
				for (int i = 0; i < 20; ++i)
					g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM4, i+100, 0);

				g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM4, iTargetID, 3);
			}
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		{
			if (g_cChatRoom->m_iMessageBoxMode == 1)	// �����忩�� ����
			{
				if (iTargetID == 2)
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomInvite(1);
				}
			}
		}
		break;
	}
}

//
// Network Functions (Public)
//

//---------- �޽��� �۽� --------//
HTvoid HTChatRoom::HT_vNetWork_CSP_Req_ChatMessage(CHTString str)
{
	MSG_Chat* info = new MSG_Chat;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( MSG_Chat ) );

	CHTString::HT_hrStringCopy( info->szMsg, str, 48 );

	g_pChatNetWorkMgr->RequestMsgChat( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MsgChat Send Message : %s", info->szMsg);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//---------- �޽��� ����---------//
HTvoid HTChatRoom::HT_vNetWork_SCP_ChatMessage( MSG_Chat* info )
{
	CHTString str;
	str.HT_szFormat("%s", info->szMsg);

	if (info->szMsg[0] != '*') // ���� �޽����� �ƴҶ��� �޽��� ����
	{
		str.HT_szFormat("%s : %s", info->szName, info->szMsg);
	}

	g_cChatRoom->HT_vChatRoom_SetText(str);

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Receive_MsgChat Message : %s", info->szMsg);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

}

// �α��� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_AccountLogin()
{
	Msg_AccountLogin* info = new Msg_AccountLogin;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_AccountLogin ) );

	CHTString::HT_hrStringCopy( info->AccountName, g_strLoginID, ACCOUNTNAME_LENGTH );

	g_pChatNetWorkMgr->RequestMsgAccountLogin( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_AccountLogin Req Message : %s", info->AccountName);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// �α��� ����
HTvoid HTChatRoom::HT_vNetWork_SCP_AccountLogin( Msg_AccountLogin* info )
{
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Receive_AccountLogin Message : Result = %s", info->byResult);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	if (info->byResult == S_OK)
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage34, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		g_cUIManager->HT_ShowWindow(UI_WINDOW_CHATROOM);
		
		// ä�ù� ����Ʈ ��û
		this->HT_vNetWork_CSP_Req_ChatRoomListRequest();
	}
	else
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage35, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
	}
}

// ä�� ����Ʈ ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomListRequest()
{
	g_pChatNetWorkMgr->RequestMsgChatRoomListRequest( );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomList Req Message...");
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// ä�ø���Ʈ ����
HTvoid HTChatRoom::HT_vNetWork_SCP_ChatRoomList( Msg_ChatRoomList* info )
{
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Receive_ChatRoomList Message : OK");
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	CHTString strMessage;
	
	g_cChatRoom->m_iRoomNo = -1;

	// ȭ�� ����
	for (int i = 1; i < 16; ++i)
	{ 
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, (i*4)+3, " " );		// ����
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, (i*4)+4, " " );		// ����
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, (i*4)+5, " " );		// ����
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, (i*4)+6, " " );		// ����
		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM, i+99, false);
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_CHATROOM, i+99);
		g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM, i+99, 0);
	}

	int iSkipTab = 0;
	int ipage = (m_iChatRoomPage*16);

	for (int i = 1; i < 16; ++i)
	{ 
		// �� 4���� 16�� ���
		strcpy(strMessage, info->Room[i-1+ipage].pszRoomName);

		if (strMessage.HT_iStringCompare("") == 0)
		{
			iSkipTab++;
			continue;
		}

		m_iByPass[i-1] = info->Room[i-1+ipage].byPass;
		m_iByNo[i-1-iSkipTab] = i-1+ipage;
		m_ibyChatRoomName[i-1-iSkipTab].HT_szFormat("%s", info->Room[i-1+ipage].pszRoomName);

		strMessage.HT_szFormat("%s", info->Room[i-1+ipage].pszRoomName);
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, ((i-iSkipTab)*4)+4, strMessage );		// ����

		if (info->Room[i-1+ipage].byPass == 1)
		{
			strMessage.HT_szFormat("%d(*)", i);
		}
		else
		{
			strMessage.HT_szFormat("%d", i);
		}
		
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, ((i-iSkipTab)*4)+3, strMessage );		// ���ȣ

		strcpy(strMessage, info->Room[i-1+ipage].Leader.szName);
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, ((i-iSkipTab)*4)+5, strMessage );		// ������

		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM, (i-iSkipTab)+99, true);
//		CHTString strToolTip;
//		g_cUIManager->HT_SetButtonControlTextIndex(UI_WINDOW_CHATROOM, (i-iSkipTab)+99, 1);
//		strToolTip.HT_szFormat("[%s]:%s/%s/%s/%s/%s/%s/%s", info->Room[i-1].Leader.szName, info->Room[i-1].Member[0].szName, info->Room[i-1].Member[1].szName, info->Room[i-1].Member[2].szName, info->Room[i-1].Member[3].szName, info->Room[i-1].Member[4].szName, info->Room[i-1].Member[5].szName, info->Room[i-1].Member[6].szName, info->Room[i-1].Member[7].szName);
//		g_cUIManager->HT_SetButtonControlToolTipText(UI_WINDOW_CHATROOM, (i-iSkipTab)+99, 1, strToolTip);
//		g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_CHATROOM, (i-iSkipTab)+99);

		// ���� �ο��� ����
		if (info->Room[i-1+ipage].byMaxMember > 0 )
		{
			int count = 1;
			for (int j = 0; j < 7; ++j)
				if (info->Room[i-1+ipage].Member[j].iID != 0)
					count++;

			strMessage.HT_szFormat("(%d/%d)", count, info->Room[i-1+ipage].byMaxMember);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, ((i-iSkipTab)*4)+6, strMessage );		// �ο�
		}
		else
		{
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM, ((i-iSkipTab)*4)+6, _T("") );		// �ο�
		}
	}
}


// ä�ù� ���� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomCreate()
{
	Msg_ChatRoomCreate* info = new Msg_ChatRoomCreate;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomCreate ) );

	// �׽�Ʈ�� ���� �̰��� �� ����
	info->byMaxMember = atoi(m_strMemberNo);
	strcpy (info->pszRoomName, m_strTitle);
	strcpy (info->szPassword, m_strPassWord);

	g_pChatNetWorkMgr->RequestMsgChatRoomCreate( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_AChatRoomCreate Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ä�ù� ���� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomCreate( Msg_ChatRoomCreate* info )
{
	if (info->byResult == S_OK)
	{
		CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);

		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage36, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		// ���� â�� ���̵��, ä�ù� â���� �˾�
		g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM3 );
		g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM );


		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 1, g_cChatRoom->m_strTitle );		// ����

		// ���� ���
		strcpy(strMessage, g_oMainCharacterInfo.szCharName);
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 6, strMessage );		// ������
	
		m_bReader = true;

		// ���� ���
		for (int i = 0; i < 7; ++i)
		{ 
			strcpy(strMessage, " ");
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, ((i+1)*4)+6, strMessage );		// �ɹ���
		}

		this->HT_vChatRoom_ClearText();
		this->HT_vSetText_Enter(g_oMainCharacterInfo.szCharName, g_cStatus->HT_szStatus_GetTrimuriti());

		g_cUIManager->HT_SetTextEditBoxControl(UI_WINDOW_CHATROOM3, 1, _T("CleanBox"));
		g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM3, 1);
	}
	else
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage37, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
	}
}

// ����
HTvoid	HTChatRoom::HT_vSetText_Enter(CHTString strCharName, CHTString strCharTrimuriti)
{
	//str.HT_szFormat("*%s(%s)���� �����Ͽ����ϴ�.*", strCharName.HT_szGetString(), strCharTrimuriti.HT_szGetString());
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage38, &str );
	str.HT_szFormat(str.HT_szGetString(), strCharName.HT_szGetString());
	g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(str);
	//g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(" ");
	//g_cChatRoom->HT_vChatRoom_SetText(str);
}

// ����
HTvoid	HTChatRoom::HT_vSetText_Out(CHTString strCharName, CHTString strCharTrimuriti)
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage39, &str );
	str.HT_szFormat(str.HT_szGetString(), strCharName.HT_szGetString());
	//g_cChatRoom->HT_vChatRoom_SetText(str);
	g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(str);
	//g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(" ");
}

// �߹�
HTvoid	HTChatRoom::HT_vSetText_Cut(CHTString strCharName)
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage40, &str );
	str.HT_szFormat(str.HT_szGetString(), strCharName.HT_szGetString());
	//g_cChatRoom->HT_vChatRoom_SetText(str);
	g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(str);
	//g_cChatRoom->HT_vNetWork_CSP_Req_ChatMessage(" ");
}

// �ش� ä�ù� ���� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomJoin()
{
	Msg_ChatRoomJoin* info = new Msg_ChatRoomJoin;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomJoin ) );

	info->iChatRoom = g_cChatRoom->m_iRoomNo;
	strcpy(info->szPassword, m_strPassWord);

	g_pChatNetWorkMgr->RequestMsgChatRoomJoin( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomJoin Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// �ش� ä�ù� ���� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomJoin( Msg_ChatRoomJoin* info )
{
	if (info->byResult == S_OK)
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage41, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		// ä�ù� ���� ����
		this->HT_vChatRoom_ClearText();
		this->HT_vSetText_Enter(g_oMainCharacterInfo.szCharName, g_cStatus->HT_szStatus_GetTrimuriti());
		
		// ���� â�� ���̵��, ä�ù� â���� �˾�
		g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM3 );
		g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM );

		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 1, g_cChatRoom->m_strTitle );		// ����

		g_cUIManager->HT_SetTextEditBoxControl(UI_WINDOW_CHATROOM3, 1, _T("CleanBox"));
		g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM3, 1);
	}
	else
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage42, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		// ä�ù� ����Ʈ ��û
		this->HT_vNetWork_CSP_Req_ChatRoomListRequest();
	}
}

// ������ ä�ù����� ���� ����
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomGoout()
{
	// �ֺ� ��������� �˸��� ��
	this->HT_vSetText_Out(g_oMainCharacterInfo.szCharName, g_cStatus->HT_szStatus_GetTrimuriti());

	Msg_ChatRoomGoout* info = new Msg_ChatRoomGoout;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomGoout ) );

	g_pChatNetWorkMgr->RequestMsgChatRoomGoout( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomGoout Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ä�ù� ���� ���� (�����ÿ��� �ް� ��)
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomGoout( Msg_ChatRoomGoout* info )
{ 
	// �ڽ��̸� ���� ó��
	//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage43, &str );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
		
	g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM );
	g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM3 );

	// �� ��Ŷ�� ������ �����κ��� ä�ù� ����Ʈ ��Ŷ�� �ٽ� �ް� �ȴ�. ���� ���� �Լ� ȣ���� �� �ʿ� ����
	// HT_vNetWork_CSP_Req_ChatRoomListRequest();

}

// ä�ù� ����� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatWaitingListRequest()
{
	Msg_ChatWaitingListRequest* info = new Msg_ChatWaitingListRequest;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatWaitingListRequest ) );

	info->byPage = m_iWaitingPage;

	g_pChatNetWorkMgr->RequestMsgChatWaitingListRequest( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatWaitingListRequest Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ä�ù� ����� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatWaitingList( Msg_ChatWaitingList* info )
{ 
	CHTString strMessage;
	//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("����� ����Ʈ�� ������ �Խ��ϴ�."));

	// ����� ��� �˾�
	g_cUIManager->HT_ShowWindow(UI_WINDOW_CHATROOM4);

	// ȭ�� ����
	for (int i = 1; i < 21; ++i)
	{ 
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, (i*4)+3, " " );		// ����
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, (i*4)+4, " " );		// ����
		//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, (i*4)+5, " " );		// ����
		//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, (i*4)+6, " " );		// ����
		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM4, i+99, false);
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_CHATROOM4, i+99);
		g_cUIManager->HT_SetButtonControlState(UI_WINDOW_CHATROOM4, i+99, 0);
	}

	int iSkipTab = 0;

	for (int i = 1; i < 21; ++i)
	{ 
		// �� 4���� 16�� ���
		strcpy(strMessage, info->Member[i-1].szName);

		if (strMessage.HT_iStringCompare("") == 0)
		{
			iSkipTab++;
			continue;
		}

		//m_iByWaitNo[i] = 
		m_oWaitingMember[i-iSkipTab-1].iID = info->Member[i-1].iID;
		m_oWaitingMember[i-iSkipTab-1].snTribe = info->Member[i-1].snTribe;
		strcpy(m_oWaitingMember[i-iSkipTab-1].szName, info->Member[i-1].szName);


		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM4, i+99, true);

		strMessage.HT_szFormat("%d", i + (20 * m_iWaitingPage));
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, ((i-iSkipTab)*4)+3, strMessage );		// ���ȣ

		strMessage.HT_szFormat("%s", m_oWaitingMember[i-iSkipTab-1].szName);
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM4, ((i-iSkipTab)*4)+4, strMessage );		// ����� ��
	}
}

// ������ ä�ù� ���� ���� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomInfo( Msg_ChatRoomInfo* info )
{   
	CHTString strMessage;

	// ���� ���
	strcpy(strMessage, info->Room.Leader.szName);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 6, strMessage );		// ������

	// �ڽ��� ���� ���� �ƴ��� ����
	CHTString str;
	strcpy(str, g_oMainCharacterInfo.szCharName);
	
	if (str.HT_iStringCompare(strMessage) == 0)
		m_bReader = true;
	else
		m_bReader = false;

	int iSkipTab = 0;
	for (int i = 0; i < 7; ++i)
	{ 
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, ((i+1)*4)+6, " " );		// �ɹ���
		
		m_oRoomMember[i].iID = 0;
		m_oRoomMember[i].snTribe = 0;
		strcpy(m_oRoomMember[i].szName, _T(""));
		g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM3, i+100, false);
	}

	// ���� ���
	for (int i = 0; i < 7; ++i)
	{ 
		strcpy(strMessage, info->Room.Member[i].szName);

		if (strMessage.HT_iStringCompare("") == 0)
		{
			iSkipTab++;
			continue;
		}

		// ������ ��쿡�� ������ Ȱ��ȭ
		if (m_bReader == true)
			g_cUIManager->HT_SetButtonEnable(UI_WINDOW_CHATROOM3, i+100, true);

		m_oRoomMember[i-iSkipTab].iID = info->Room.Member[i].iID;
		m_oRoomMember[i-iSkipTab].snTribe = info->Room.Member[i].snTribe;
		strcpy(m_oRoomMember[i-iSkipTab].szName, info->Room.Member[i].szName);

		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, ((i+1-iSkipTab)*4)+6, strMessage );		// �ɹ���
	}

	//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("ä�ù� ������ ���� �����Ͽ����ϴ�."));
}


// �ʴ� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomInvite(int iType, int iResult)
{
	Msg_ChatRoomInvite* info = new Msg_ChatRoomInvite;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomInvite ) );

	info->byResult = iResult;
	info->byType = iType;

	if (iType == 1)
	{
		info->iTarget = m_oWaitingMember[m_iWaitingMember].iID;
		strcpy(info->szTarget, m_oWaitingMember[m_iWaitingMember].szName);

		// �ʴ븦 ��û�� ����� ����� ��� â�� �ݾ��ش�.
		g_cUIManager->HT_HideWindow(UI_WINDOW_CHATROOM4);
	}
	else
	{
		info->iTarget = m_iTargetID;
		strcpy(info->szTarget, m_szTargetName);
	}

	g_pChatNetWorkMgr->RequestMsgChatRoomInvite( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomInvite Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// �ʴ� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomInvite( Msg_ChatRoomInvite* info )
{ 
	CHTString strMessage;

	if (info->byType == 1)	// ��û�� ���Դٸ�...
	{
		// �޽��� �ڽ� �˾���Ű��
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage44, &str );
		str.HT_szFormat(str.HT_szGetString(), info->szTarget);
		g_cUIManager->HT_MessageBox(UI_WINDOW_CHATROOM, str, 1);
		m_iMessageBoxMode = 3;

		m_iTargetID = info->iTarget;
		strcpy(m_szTargetName, info->szTarget);
	}
	else if (info->byType == 2)	// ��û �õ��� ���濡 ���� ���� ó��
	{
		if (info->byResult == 0)	// �³�
		{

			// ä�ù� ���� ����
			this->HT_vChatRoom_ClearText();
			this->HT_vSetText_Enter(g_oMainCharacterInfo.szCharName, g_cStatus->HT_szStatus_GetTrimuriti());
		
			// ���� â�� ���̵��, ä�ù� â���� �˾�
			g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM3 );
			g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM );

			//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 1, g_cChatRoom->m_strTitle );		// ����

			

			g_cUIManager->HT_SetTextEditBoxControl(UI_WINDOW_CHATROOM3, 1, _T("CleanBox"));
			g_cUIManager->HT_FocusOnEditBoxControl(UI_WINDOW_CHATROOM3, 1);
		}
		else	// �ź�
		{
			//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
			//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
			CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage45, &str );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
		}
	}
}

// ä�ù� ���� ��û
HTvoid	HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomUpdate()
{  
	Msg_ChatRoomUpdate* info = new Msg_ChatRoomUpdate;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomUpdate ) );

	// �׽�Ʈ�� ���� �̰��� �� ����
	info->byMaxMember = atoi(m_strMemberNo);
	strcpy (info->pszRoomName, m_strTitle);
	strcpy (info->szPassword, m_strPassWord);

	g_pChatNetWorkMgr->RequestMsgChatRoomUpdate( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomUpdate Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ä�ù� ���� ����
HTvoid	HTChatRoom::HT_vNetWork_SCP_ChatRoomUpdate( Msg_ChatRoomUpdate* info )
{
	if (info->byResult == S_OK)
	{
		CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage46, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_CHATROOM3, 1, g_cChatRoom->m_strTitle );		// ����

		//this->HT_vChatRoom_ClearText();
	}
	else
	{
		CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage47, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
	}
}

// ä�ù� ���� ��û
HTvoid HTChatRoom::HT_vNetWork_CSP_Req_ChatRoomOrder(int iType, int iTargetID, CHTString strTargetName)
{  
	Msg_ChatRoomOrder* info = new Msg_ChatRoomOrder;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_ChatRoomOrder ) );

	info->byOrder = iType;
	info->iTarget = iTargetID;
	strcpy(info->szTarget, strTargetName);

	g_pChatNetWorkMgr->RequestMsgChatRoomOrder( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChatRoomOrder Req Message..." );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// ä�ù� ���� ����
HTvoid HTChatRoom::HT_vNetWork_SCP_ChatRoomOrder( Msg_ChatRoomOrder* info )
{
	if (info->byResult == S_OK)
	{
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgChatRoomMessage48, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);

		g_cUIManager->HT_ShowWindow( UI_WINDOW_CHATROOM );
		g_cUIManager->HT_HideWindow( UI_WINDOW_CHATROOM3 );
	}
	else
	{
		//CHTString strMessage;
		//g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("ä�ù� ���� ����"));
	}
}

