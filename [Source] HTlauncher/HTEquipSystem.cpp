#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htequipsystem.h"

HTEquipSystem::HTEquipSystem(void)
{
}

HTEquipSystem::~HTEquipSystem(void)
{
}

HTvoid HTEquipSystem::HT_EquipSys_Equip( HTint iModelID, BYTE byTribe, DWORD dwNormalItem, DWORD dwLeftItem, BYTE byHeadType )
{
	g_pEngineHandler->HT_hrEquipItem( iModelID, byTribe, dwNormalItem, dwLeftItem, byHeadType );
}

HTvoid HTEquipSystem::HT_EquipSys_UnEquip( HTint iModelID, HTint nModelType, DWORD dwNormalItem, DWORD dwLeftItem, BYTE byHeadType )
{
	g_pEngineHandler->HT_hrUnEquipItem( iModelID, nModelType, dwNormalItem, dwLeftItem, byHeadType );
}


