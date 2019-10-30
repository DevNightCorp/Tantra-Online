#include "stdafx.h"
#include "HTextern.h"
#include "htinfoload.h"

#define _NETWORK_MSG_FILEPATH	_T("system\\HTNetworkmessage.cfg")
HTInfoLoad::HTInfoLoad(void)
{
}

HTInfoLoad::~HTInfoLoad(void)
{
}

HTvoid HTInfoLoad::HT_vNetWorkMessageSetHistory( HTint iType, CHTString strMessage )
{
	HT_COLOR color;		// 글자색
	HT_COLOR bgcolor;	// 배경색
	
	// 메시지 타입에 따라 다른 색깔을 적용한다.
	switch( iType )
	{
	case HISTORY_MESSAGE_TYPE_NORMAL:
		color	= g_ColorTable[14];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_NOTIFY:
		color	= g_ColorTable[15];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_ITEM:
		color	= g_ColorTable[8];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_ATTACK:
		color	= g_ColorTable[15];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_ATTACKED:
		color	= g_ColorTable[5];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_QUEST:
		color	= g_ColorTable[11];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_PARTY:
		color	= g_ColorTable[7];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_PRANA:
		color	= g_ColorTable[10];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_SKILL:
		color	= g_ColorTable[8];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_CHAKRA:
		color	= g_ColorTable[12];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_BRAMAN:
		color	= g_ColorTable[10];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_ETC:
		color	= g_ColorTable[15];
		bgcolor	= g_ColorTable[0];
		break;
	case HISTORY_MESSAGE_TYPE_ERROR:
		color	= g_ColorTable[6];
		bgcolor	= g_ColorTable[0];
		break;
	default:
		color	= g_ColorTable[15];
		bgcolor	= g_ColorTable[0];
	}
	g_cChatting->HT_vSaveHistory( iType, strMessage, color, bgcolor );
}

HTvoid HTInfoLoad::HT_vNetWorkMessageSetHistory( HTint iType, CHTString strMessage, HT_COLOR color, HT_COLOR bgcolor )
{
	g_cChatting->HT_vSaveHistory( iType, strMessage, color, bgcolor );
}
