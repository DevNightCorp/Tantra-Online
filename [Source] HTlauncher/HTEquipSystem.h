
#ifndef __HTEQUIPSYSTEM_H__
#define __HTEQUIPSYSTEM_H__

#pragma once

class HTEquipSystem
{
public:
	HTEquipSystem(void);
	~HTEquipSystem(void);

	HTvoid			HT_EquipSys_Equip( HTint iModelID, BYTE bTribe, DWORD dwNormalItem, DWORD dwLeftItem, BYTE byHeadType );
	HTvoid			HT_EquipSys_UnEquip( HTint iModelID, HTint nModelType, DWORD dwNormalItem, DWORD dwLeftItem, BYTE byHeadType );
	
private:
};


#endif
