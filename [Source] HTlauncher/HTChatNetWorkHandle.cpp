//
// ä�ù� �ý���
//
// 2005. 12. 21 : ������ (grecia79@hanbitsoft.co.kr)
//

#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTWindowManager.h"
#include "HTChatNetWorkHandle.h"

HTRESULT CHTChatNetWorkHandle::HT_hrWorkFunction(char* pData)
{
	HRESULT hr = HT_OK;

	MSG_STANDARD *pMsg = (MSG_STANDARD*)pData;
	if ( !pMsg ) return HT_FAIL;

	switch ( pMsg->wType )
	{
	case _MSG_Chat :	// �޽��� ����
		{
			MSG_Chat info; 
			memcpy( &info, pData, sizeof(MSG_Chat) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatMessage( &info ); 
		}
		break;
	case _Msg_AccountLogin :	// �α��� ����
		{
			Msg_AccountLogin info; 
			memcpy( &info, pData, sizeof(Msg_AccountLogin) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_AccountLogin( &info ); 
		}
		break;
	case _Msg_ChatRoomList :	// ä�ù� ����Ʈ ����
		{
			Msg_ChatRoomList info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomList) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomList( &info ); 
		}
		break;

	case _Msg_ChatRoomCreate :	// ä�ù� ���� ����
		{
			Msg_ChatRoomCreate info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomCreate) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomCreate( &info ); 
		}
		break;

	case _Msg_ChatRoomJoin : // ä�ù����� ���� ����
		{
			Msg_ChatRoomJoin info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomJoin) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomJoin( &info ); 
		}
		break;

	case _Msg_ChatRoomGoout : // ä�ù� ���� ����
		{
			Msg_ChatRoomGoout info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomGoout) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomGoout( &info ); 
		}
		break;

	case _Msg_ChatRoomInfo : // ä�ù��� ������ ���� ����
		{
			Msg_ChatRoomInfo info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomInfo) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomInfo( &info ); 
		}
		break;

	case _Msg_ChatWaitingList : // ä�ù� ����� ����Ʈ ����
		{
			Msg_ChatWaitingList info;
			memcpy( &info, pData, sizeof(Msg_ChatWaitingList) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatWaitingList( &info ); 
		}
		break;

	case _Msg_ChatRoomInvite : // ä�ù� �ʴ� ���� ����
		{
			Msg_ChatRoomInvite info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomInvite) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomInvite( &info ); 
		}
		break;

	case _Msg_ChatRoomUpdate : // ä�ù� ���� ���� ��û
		{
			Msg_ChatRoomUpdate info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomUpdate) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomUpdate( &info ); 
		}
		break;

	case _Msg_ChatRoomOrder : // ���� ���
		{
			Msg_ChatRoomOrder info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomOrder) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomOrder( &info ); 
		}
		break;

		// ����ٰ� ������ ��Ŷ�� ���� ó���κ��� �ִ´�.
	default:
		break;
	}

    return hr;
}