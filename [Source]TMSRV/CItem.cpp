#include <windows.h>
#include "Basedef.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

#include "CItem.h"
void                          Log(char * str1,char * str2);
CItem::CItem()
{
	Mode       = 0;
    GridCharge = 0;
    State      = 0;
    Rotate     = 0;
	Delay      = 0; // ���� ������ Delay=0; 20��ƽ�� Delay=1; ���� ������ Delay=0;

}

CItem::~CItem()
{
}
