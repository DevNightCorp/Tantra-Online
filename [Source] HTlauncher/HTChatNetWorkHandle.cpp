//
// 채팅방 시스템
//
// 2005. 12. 21 : 선영범 (grecia79@hanbitsoft.co.kr)
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
	case _MSG_Chat :	// 메시지 수신
		{
			MSG_Chat info; 
			memcpy( &info, pData, sizeof(MSG_Chat) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatMessage( &info ); 
		}
		break;
	case _Msg_AccountLogin :	// 로그인 응답
		{
			Msg_AccountLogin info; 
			memcpy( &info, pData, sizeof(Msg_AccountLogin) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_AccountLogin( &info ); 
		}
		break;
	case _Msg_ChatRoomList :	// 채팅방 리스트 응답
		{
			Msg_ChatRoomList info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomList) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomList( &info ); 
		}
		break;

	case _Msg_ChatRoomCreate :	// 채팅방 생성 응답
		{
			Msg_ChatRoomCreate info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomCreate) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomCreate( &info ); 
		}
		break;

	case _Msg_ChatRoomJoin : // 채팅방으로 참여 응답
		{
			Msg_ChatRoomJoin info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomJoin) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomJoin( &info ); 
		}
		break;

	case _Msg_ChatRoomGoout : // 채팅방 나감 응답
		{
			Msg_ChatRoomGoout info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomGoout) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomGoout( &info ); 
		}
		break;

	case _Msg_ChatRoomInfo : // 채팅방의 정보를 갱신 응답
		{
			Msg_ChatRoomInfo info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomInfo) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomInfo( &info ); 
		}
		break;

	case _Msg_ChatWaitingList : // 채팅방 대기자 리스트 응답
		{
			Msg_ChatWaitingList info;
			memcpy( &info, pData, sizeof(Msg_ChatWaitingList) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatWaitingList( &info ); 
		}
		break;

	case _Msg_ChatRoomInvite : // 채팅방 초대 관련 응답
		{
			Msg_ChatRoomInvite info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomInvite) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomInvite( &info ); 
		}
		break;

	case _Msg_ChatRoomUpdate : // 채팅방 정보 변경 요청
		{
			Msg_ChatRoomUpdate info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomUpdate) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomUpdate( &info ); 
		}
		break;

	case _Msg_ChatRoomOrder : // 강퇴 기능
		{
			Msg_ChatRoomOrder info;
			memcpy( &info, pData, sizeof(Msg_ChatRoomOrder) ); 
			if(g_cChatRoom) g_cChatRoom->HT_vNetWork_SCP_ChatRoomOrder( &info ); 
		}
		break;

		// 여기다가 각각의 패킷에 대한 처리부분을 넣는다.
	default:
		break;
	}

    return hr;
}