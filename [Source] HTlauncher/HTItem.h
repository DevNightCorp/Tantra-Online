#ifndef __HTITEMFAL_H__
#define __HTITEMFAL_H__

class CHTItemAl
{
public:
	CHTItemAl();
	~CHTItemAl();

	//---------------------------------------------------------------------
	// ������ ����
	//---------------------------------------------------------------------	
	HTvoid				HT_vItemCreate( PS_SCP_MAP_ITEM_APPEAR info );
	HTvoid				HT_vItemCreate( HTbyte byPlace, HTint iKeyID, STRUCT_ITEM info );
	HTvoid				HT_vItemCreate( HTbyte byLocation, HTbyte byX, HTbyte byZ, HTint iKeyID, 
										STRUCT_ITEM info, HTbyte byBagNo = -1 );

	//---------------------------------------------------------------------
	// ������ �� ����
	//---------------------------------------------------------------------	
	// 3D��
	HTvoid				HT_vItemCreate_Object(); 
	HTvoid				HT_vItemCreate_Destory(); 
	// 2D ��
	HTvoid				HT_vSystem_Create2DItem();
	HTvoid				HT_vSystem_Delete2DItem();

	// �κ��丮���� ������ �����ϱ�
	HTvoid				HT_vItemAlSettingInventoryPos( HT_ITEMSETTING_FLAG flag, HTbool bDrawTwinImage = HT_TRUE );

	//---------------------------------------------------------------------
	// �� ���� ������
	//---------------------------------------------------------------------	
	// �ʻ��� ĳ���Ϳ� �������� ����ġ ��
	HTbool				HT_bComCharacterAndItem();
	// �ʻ� �������� ����-�ʿ� �������� ����
	HTvoid				HT_vItemAlThrowMap( HTint, HTint );
	//	������ �׸��� ��ġ �˾ƿ���	
	HTPoint				HT_ptGeItemSystemCell();				
	
	HTvoid				HT_vItemAlRender();
	
	//---------------------------------------------------------------------
	// �������� ����
	//---------------------------------------------------------------------	
	// �������� ���׿� �ɸ����� �˻�
	HTbool				HT_bItemAl_PossibleCheck(DWORD dwItemIndex, HTbool bLevelCheck );

	//---------------------------------------------------------------------
	// ���� ����
	//---------------------------------------------------------------------	
	// ������� �Ӽ� ���� �ʱ�ȭ
	HTvoid				HT_vItemAI_ClearSubItemInfo();
	// ��ȭ���� ���� ����
	HTvoid				HT_vItemAI_SetMainRefineLevel( HTint iLevel )	{ m_sItemInfo.byRefineLevel = iLevel; }

	// �������� ���� ��ġ ��ȯ
	HTvoid				HT_vItemAI_GetItemEquipPos( DWORD dwItemIndex, HTbyte* byEquipPos );

public:
	STRUCT_ITEM					m_sItemInfo;
	
	DWORD						m_dwItemKeyID;				//	�������� �����ϱ� ���ؼ�
	HTbool						m_bItemActive;				//	������ Ȱ��ȭ ����
	HTint						m_iItemDlgNo;				//	�پ��ִ� ��ȭ���� ��
	HTint						m_iItemLocation;			//	��
	HTint						m_iItemInInventory;			//	�������� ��ġ�� �κ��丮
	HTbyte						m_byItemEquipPos;			//	�������� ������ �� �ִ� �κ��丮
	
	// ������ �������� �������� �ּ����� ����
	HTITEM_REFINE_PARAM			m_sItem_SubRefineInfo[MAX_EFFECT_NUM*MAX_REFINE_SUB_LEVEL];
	HTbyte						m_bySubEffectIDCount;
	 
	HTshort						m_sItemType;				//	�ϴ� �̰����� �������� �Ӽ��� �����ش�.
	HTbyte						m_byItemSizeX;				//	��������  x ���� ũ��
	HTbyte						m_byItemSizeY;				//	��������  y ���� ũ��
	HTbyte						m_byInventory_CellPosX;		//  �κ��丮 ���� x ���� ��ġ
	HTbyte						m_byInventory_CellPosY;		//  �κ��丮 ���� y ���� ��ġ

	//-----2D ��������Ʈ ����-----//
	HTbool						m_bItem2DID_Sw;
	HTint						m_iCellNumber;
	HTint						m_iItemTextureID;

	//-----3D ��������Ʈ ����-----//
	HTbool						m_bItem3DID_Sw;
	HTint						m_iItem3DID;
	HTshort						m_sItemMapCellX;			//	�ʻ��� ����ǥ
	HTshort						m_sItemMapCellZ;			//	�ʻ��� ����ǥ
	HTvector3					m_vecItem3DPosition;

	//------���� ����/�Ұ��� ǥ�ÿ�-------//
	HTbool						m_bPossible;				// HT_FALSE - ���� �Ұ���, HT_TRUE - ���밡��

	HTbool						m_bItem_PickUp_Sw;
	CHTString					m_strItemName;

	//-----������ ���� �����ֱ�-----//
	HTbool						m_bItem_Info_Sw;
};

#endif