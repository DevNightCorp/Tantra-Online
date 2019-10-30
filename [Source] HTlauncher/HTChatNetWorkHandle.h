#ifndef __HTCHATNETWORKHANDLE_H_INCLUDE__
#define __HTCHATNETWORKHANDLE_H_INCLUDE__

#include "BaseDef.h"

class CHTChatNetWorkHandle
{
public:
	CHTChatNetWorkHandle();
	~CHTChatNetWorkHandle();

	static HTRESULT			HT_hrWorkFunction(char* pData);
};

#endif //__HTCHATNETWORKHANDLE_H_INCLUDE__