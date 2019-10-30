
#ifndef __HTITEMSYSTEM_H__
#define __HTITEMSYSTEM_H__

#include "HTItem.h"

#define ITEM_DISMANTLE_PERCENTAGE 50
#define _DURABLE_ITEM_ATTACK	0
#define _DURABLE_ITEM_DEFENCE	1

// ������ LL ������ ���� ����ü 
typedef struct _HT_NODE
{
	CHTItemAl						cItem;
	struct _HT_NODE					*next;

} HT_NODE;


class CHTItemSystem
{
public:
	CHTItemSystem();
	~CHTItemSystem();
	
	HTvoid		HT_vItemSystem_CleanUp();
	HTRESULT	HT_hrSystemInit();

	HTvoid		HT_vItemSystem_Control();
	HTvoid		HT_vItemSystem_AOI_Check( HT_NODE *t );					//	AOI ���� üũ

	// ����
	HTRESULT	HT_hrSystemRender();
	// ����_�̸�_3d
	HTvoid		HT_vItemSystem_RenderName( HT_NODE* t );
	
	//---------------------------------------------------------------------
	// �ʿ� �ִ� ������ ����
	//---------------------------------------------------------------------
	// �ʻ󿡼� �������� ��Ÿ����.
	HTvoid		HT_vItemSystem_Appear( PS_SCP_MAP_ITEM_APPEAR );
	// �ʻ󿡼� �������� �������.
	HTvoid		HT_vItemSystem_DisAppear( PS_SCP_MAP_ITEM_DISAPPEAR );
	// 3D�������� �����Ѵ�.
	HTvoid		HT_vItemSystem_3DItemHidden( HTint iKeyID );
	// �������� ���̿��ٰ� ������.
	HTvoid		HT_vItemSystem_ThrowItem( HTint iKeyID, HTPoint );
	// �������� �������� �ݴ´�.
	HTbool		HT_bItemSystem_PickUpItemCheck( DWORD );
	// ������ �Ⱦ��� ������ �ʱ�ȭ
	HTvoid		HT_vSystem_InitPickUpItemOnMap();
	// �ʼ����� ������ �˻�
	HTint		HT_iSystem_MapCellCheckToItemOnMap( HTint, HTint );
	// �������� �� ���̵�� ���Ѵ�
	HTint		HT_iSystem_ComIDCheck( HTint iID, HTPoint );
	// ������ Ư�� ��ġ�� �������� �ִ��� �˻�:������ HT_TRUE ����
	HTRESULT	HT_hrCheckMapPos(HTPoint pos);
	//	������ ����ǥ�� ��ȯ KeyID
	HT_CELL_COORD HT_cellItemSystem_GetMapCellPosForKeyID( HTint );	
	//	������ ����ǥ�� ��ȯ ModelID
	HT_CELL_COORD HT_cellItemSystem_GetMapCellPosForModelID( HTint );	

	//---------------------------------------------------------------------
	// ������ ����
	//---------------------------------------------------------------------
	// ������ ������ ���ﶧ
	HTvoid		HT_LL_vInsertAfter_ItemDelete( DWORD );							
	// ������ ���θ� ����
	HTvoid		HT_vItemSystem_TotalItemDelete();
	// �������� �����Ѵ�
	HTvoid		HT_vItemSystem_DeleteItem( DWORD iKeyID );
	//HTvoid		HT_vItemSystem_DeleteItem(DWORD dwKeyID, HTint nLocation);
	// �κ��丮 ���� ������ ���θ� ����
	HTvoid		HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory );
	// �κ��丮 ���� Ư�� index�� ������ ���θ� ����
	HTvoid		HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory, DWORD dwItemIndex );
	// �κ��丮 ���� Ư�� type�� ������ ���θ� ����
	HTvoid		HT_vItemSystem_DeleteItemInventory( WORD wItemType, HTint nLocation, HTint nInventory);
	
	//---------------------------------------------------------------------
	// �κ��丮�� �ִ� ������ ����
	//---------------------------------------------------------------------
	// �������� ������ �� �ִ� �κ��丮�ΰ�?
	HTint		HT_iItemAlSetPosInventoryCheck( DWORD dwKeyID, DWORD dwItemIndex, HT_ITEMSETTING_FLAG sSetItem );
	
	// �κ��丮�� ������� ���� ��ȯ - 2005. 2. 14 �߷�Ÿ�ε��̿� ������ �ۼ�
	HTint		HT_iItemAlSetPosInventoryBlankCheck();

	// â�� ������� ���� ��ȯ - 2005. 2. 14 �߷�Ÿ�ε��̿� ������ �ۼ�
	HTint		HT_iItemAlSetPosGoodsKeepBlankCheck();

	// �κ��丮�� Ư��ĭ�� �ش� �������� � ���� �ϴ°�? �˾Ƴ��� - 2005. 7. 28 ������
	HTint		HT_bItemSystem_GetPossible2(DWORD dwIndex, HTint iPos );

	// �������� Ư�� ��ġ�� ���� �� �ִ��� �˻�
	HTbool		HT_bItemSystem_GetPossibleOnEquip(DWORD dwItemKeyID, HTint nLocation);

	// �κ��丮���� ������ �����ϱ�
	HTvoid		HT_vItemSystem_SettingInventoryPos( HTint, HT_ITEMSETTING_FLAG, HTbool );
	
	// PC/NPC �κ��丮�� �ִ� �������� ���밡��/�Ұ��� �� ����
	HTvoid		HT_vItemSystem_RenewalPossibleBar(HTint nDlgNo);
	HTbool		HT_bItemSystem_GetPossible(DWORD dwItemKeyID, HTbool bLevelCheck);

	//---------------------------------------------------------------------
	// ������ �������� ���� ���� ����
	//---------------------------------------------------------------------
	// ��ȭ���� ���� ����
	HTbool		HT_bItemSystem_SetMainRefineLevel(DWORD dwItemKeyID, HTint iLevel);
	// ������ῡ ���� �����ۿ� �߰��� �Ӽ� ����
	HTbool		HT_bItemSystem_SetSubRefineItem(DWORD dwItemKeyID, HTbyte bySubItem[MAX_SUBMATERIALSIZE] );
	HTbool		HT_bItemSystem_SetSubRefineEffect
				( DWORD dwItemKeyID, HTint iEffectID, HTint iParam1, HTint iParam2, HTint iFunction = 0, HTint iDuration = 0 );
	// ������� ���� �����
	HTbool		HT_bItemSystem_ClearSubRefineItem(DWORD dwItemKeyID);

	// ������ Ÿ�Կ� ���� ���� ��޿� �־����� ���� ����� �ջ��Ѵ� 
	HTbool		HT_bItemSystem_GetMainRefineEffect( HTdword dwIndex, HTint iLevel, HTint iEffectID, HTint* piParam1, HTint* piParam2 );
	// (��ȭ)���ôܰ迡 ���� ���� ��� ���ϱ�
	HTint		HT_iItemSystem_GetMainRefineLevelConst( HTdword dwIndex, HTint iLevel );
	// ������ ������ ���� ������ �Ӽ� ����
	HTbool		HT_vItemSystem_CheckItemEffect( HTint iItemIndex, HTint iEffectID );
	
	// ������ ���ý� �ʿ��� ���Ǿ� ����
	HTint		HT_iItemSystem_GetRupiahForItemWork(HTint nItemLevel, HTint iRupiah);

	// ��ȭ ���� ����
	HTbyte		HT_byItemSystem_GetMainRefineLevel( DWORD dwKeyID );
	// �ּ� ���� ����
	HTint		HT_iItemSystem_GetSubRefineLevel( DWORD dwKeyID );
	// �ּ� ���ÿ� ���� ������ index ���ϱ�
	HTint		HT_iItemSystem_GetSubRefineItemsIndex( DWORD dwKeyID, HTbyte* bySubRefine );
	// �ּ� ���� ������ �� �Ӽ� ���õ� ������ �˻�
	HTint		HT_iItemSystem_GetAttributeSubRefineItem( DWORD dwKeyID );
	HTint		HT_iItemSystem_GetAttribute( HTint iEffectID );

	//---------------------------------------------------------------------
	// ������ ���� ��ȯ
	//---------------------------------------------------------------------			
	//	�������� �� ID�� ���´�.
	HTint		HT_iSystem_GetItemModelID( DWORD );	
	
	//  ������ ������ ���
	HTbool		HT_bItemSystem_GetItemInfo( DWORD dwItemKeyID, STRUCT_ITEM& sItem );

	//	������ �ִ� �������� KeyID�� ���´�.
	DWORD		HT_dwItemSystem_GetKeyIDOnCell( HTPoint );	
	// ���콺 ������ ��ġ�� �ִ� ������ KeyID ��ȯ
	HTint		HT_iSystem_ItemFind( HTint, HTint, HTint );			
	// �������� �� ���̵�κ��� Ű���̵� ���´�.
	DWORD		HT_dwSystem_GetItemKeyFromModelID( HTint, HTbool bPickCheck );
	// �������� �κ��丮 ��ġ�� KeyID�� ���´�
	DWORD		HT_dwItemSystem_GetItemKeyIDFromInvenLocation( HTint iCellNo );
	// �ε����� PC�κ��丮�� ���� ó�� �˻��Ǵ� �������� KeyID�� ���´�
    DWORD		HT_dwItemSystem_GetKeyIDInPCInventoryForIndex( HTint );
	// ������ �������� KeyID�� ���´�.
	DWORD		HT_dwSystem_GetItemEquipKeyID( HTint );					
	// ������ �����ǰ� �κ��丮 ����ǥ�� ����Ͽ� ������ KeyIDã�� 
	DWORD		HT_dwItemSystem_ItemSerch( HT_ItemReturnRoom );
	// ������ �����ǰ� �κ��丮 ����ǥ�� ����Ͽ� ������ KeyIDã�� 
	DWORD		HT_dwItemSystem_ItemSerch( HTint iLocation, HTint iInventory, HTint iSlotNo );
	STRUCT_ITEM HT_iGetItemInfo(DWORD dwKeyID);
	// Ư�� ��ġ(iLocation)�� �ڽ��� ������ ���� ������ �������� �ִ��� �˻��ؼ� KeyID�� ��ġ�� ���´�
	HTvoid		HT_vItemSystem_GetItemPos( DWORD dwItemIndex, DWORD dwActiveItemKeyID, HTint iLocation, 
											DWORD& dwItemKeyID, HT_ITEMSETTING_FLAG& sLocRoom );
	// ���콺 ����Ʈ�� �Ѱܹ޾� Ȱ��ȭ�� �������߿� ����Ʈ ��ġ�� �ִ°��� KeyID�� ��ȯ
	DWORD		HT_dwItemSystem_MousePtToItemPosCheck( HTPoint pPt );

	// �������� KeyID�� Index�� type, ũ�⸦ ��ȯ 
	HTint		HT_iGetItemInfoForEquip(DWORD dwKeyID, DWORD& dwItemIndex, HTint& iItemType, HTPoint& iItemSize);
	// �������� Ű�̵�� �ε����� ���´�
	DWORD		HT_dwSystem_GetItemIndex( DWORD );

	// ������ �̸� ȹ��
	CHTString	HT_strItemSystem_GetItemName(DWORD dwItemKeyID);
	// ������ Ÿ�� ���´�
	HTshort		HT_sItemSystem_GetItemType( DWORD dwKeyID );

	// ������ KeyID�� ��ġ �˾ƿ���
	HTbool		HT_bItemSystem_GetItemPos( DWORD dwKeyID, HT_ITEMSETTING_FLAG& sLocRoom );
	// �������� �κ��丮 �� ��ġ�� ��ȯ
	HTPoint		HT_ptItemSystem_GetInventoryPos( DWORD );
	
	// ��ø ������ �ټ� ������
	HTint		HT_iItemSystem_GetItemCount( DWORD );
	// ��ø �������� �ټ��� �������ش�
	HTvoid		HT_vItemSystem_SetOverlapItemCount( DWORD, HTbyte );
	// ��ø ������ ����
	HTbool		HT_bItemSystem_SetOverlapItem_Add( DWORD, HTbyte );	
	// ��ø ������ ����
	HTbool		HT_bItemSystem_SetOverlapItem_Minus( DWORD, HTbyte );	
	// �������� Ű�̵�� �������� �ִ� ��ø ������ ���´�
	WORD		HT_wItemSystem_GetItemMaxPackCount( DWORD dwItemKeyID );
	// ��ø �������� �ִ��� �Ǵ�
	HTPoint		HT_ptItemSystem_GetOverlapItem( DWORD );					
	// �κ��丮 �ȿ��ִ� Ư�� ������(Index)�� �� ������ ���´�
	HTint		HT_iItemSystem_GetItemCountOnPcInven( DWORD dwItemIndex );
	
	// �������� ����� ��ȯ
	HTPoint		HT_ptItemSystem_GetSize( DWORD dwKeyID );
	// �������� �� ��ȣ�� ��ȯ
	HTint		HT_iItemSystem_GetCellNumber( DWORD dwItemKeyID );

	// ������ �ӵ� ���� ���ϱ�
	HTint		HT_iItemSystem_CheckItemSpeedRange( HTint iSpeed );
	// �������� �ʿ䷹���� ���� ��ġ ���ҷ�
	HTint		HT_iItemSystem_GetDecreaseValForGapLevel( HTint iItemIndex );
	//	Returns Get �÷��̾�� ���� ����� Itemt KeyID�O��
	HTint		HT_iItemSystem_GetItemKeyIDMostNearMainChar();
	//	Set Item Targetting Effect
	HTvoid		HT_vItemSystem_SetItemTargettingEffect( HTint iKeyID );
	//	���� �̸��� �������� �ִ��� �˻�
	HTRESULT	HT_hrItemSystem_GetSameNameCheck( CHTString strItemName );
	//	KeyID�� ������ ������ �ؽ��� ���̵� ����
	HTint		HT_iItemSystem_GetTextureIDFromKeyID( HTint iKeyID );
	//	������ �������� �ִ��� ����
	HTRESULT	HT_hrItemSystem_CheckEquipItem();

	//---------------------------------------------------------------------
	// ������ ����â�� ������ ���� 
	//---------------------------------------------------------------------	
	// ������ �Ϲ� ������ ���´�
	HTint		HT_iGetItemInfo(DWORD dwKeyID, HT_ITEMINFO& vInfo, BYTE bType = 0);
	// �����ۿ� �⺻������ �߰��Ǿ��ִ� ���� ������
	HTbool		HT_bItemSystem_GetSubRefineEffect( const HT_NODE* pItemNode, const HTint iEffectID, 
												HTint* piParam1, HTint* piParam2, HTint* piFunction/*, CHTString* str*/);
	// ������ ����/��ü ����
	HTint		HT_iGetFixInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible);
	HTint		HT_iGetDisjointInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible);
	// �Ǹűݾ� ����ϱ�
	HTint		HT_iItemSystem_CalDisjointPrice(DWORD dwKeyID );

	// ������ ���� - ������ �̵��ӵ�
	//HTfloat		HT_fItemSystem_GetItemSpeedUp( DWORD dwKeyID );

	//	��ų�� �� Ÿ���� �Ѱ��ش�
	HTint		HT_iItemSystem_GetCoolTime( DWORD );

	//---------------------------------------------------------------------
	// ������ ����
	//---------------------------------------------------------------------	
	// ���� ������ �����ϰ� �� �������� ������ ��ȯ
	DWORD		HT_dwItemSystem_SetCurDurability(DWORD dwItemKeyID, HTint iCurDurability);
	// ���� ������ ��ȯ
	HTshort		HT_sItemSystem_GetCurDurability(DWORD dwItemKeyID);
	// �ִ� ������ ��ȯ
	HTshort		HT_sItemSystem_GetMaxDurability(DWORD dwItemKeyID);
	
	// ������ ��� ǥ�� ����
	HTvoid					HT_vItemSystem_SetDurabilityWarning( HTint iInvenIndex );
	HTvoid					HT_vItemSystem_RenewalDurabilityWarning( );

	// ������ �ʿ��� ���������� �˻�
	HTbool					HT_bItemSystem_CheckNeedFix(DWORD dwKeyID);
	//---------------------------------------------------------------------
	// ��Ʈ��ũ ����
	//---------------------------------------------------------------------	
	// ������ ����
	HTvoid		HT_vItemSystem_ItemSet( PS_SCP_RESP_ITEM_SET info );
	HTvoid		HT_vItemSystem_CreateAshramCargo( HTbyte byPlace, HTshort snIndex, STRUCT_ITEM oItem );
	HTvoid		HT_LL_vInsertAfter_ItemCreateInven( STRUCT_ITEM arrInven[MAX_INVEN] );
	HTvoid		HT_LL_vInsertAfter_ItemCreateEquip( STRUCT_ITEM arrEquip[MAX_EQUIP] );
	HTvoid		HT_LL_vInsertAfter_ItemCreateNPCInven( STRUCT_ITEM arrNPCInven[MAX_CARGO] );
	//	�ƽ��� â�� ����
	HTvoid		HT_LL_vInsertAfter_ItemDeleteAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo );
	HTvoid		HT_LL_vInsertAfter_ItemCreateAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo );

	// ������ ������ ����
	HTvoid		HT_vItemSystem_vNetWork_SCP_Item_Durability_Decrease( MSG_ITEM* info );
	// ������ �Ҹ�� �����
	HTRESULT	HT_hrItemSystem_vNetWork_SCP_Item_Abrasion(PS_SCP_ITEM_ABRASION info);

	//---------------------------------------------------------------------
	//	������ ���� ��â ������ �� ����
	//---------------------------------------------------------------------	
	HTvoid		HT_vItemSyste_TribeEquipItemReEquip( HTshort snTribe );

	// �ʿ� ������ ������ �Ⱦ��� Ű���̵� ����
	HTdword					HT_bItemSystem_GetMapItemPickUpKeyID() {return m_dwMapItemkeyID;};

private:	
	HTvoid					HT_LL_vInitList();
	HTRESULT				HT_LL_hrDeleteNode( int info );
	HT_NODE*				HT_LL_hrDeleteAll();

	// �������� ���� ���������� �˻�
	HTbool					HT_bItemSystem_CheckDurabilityWarning( HTdword dwKeyID );
	
	//-----------------------------------------------------------------------------
	// HTvoid					HT_vSetDurabilityMsg(HTint iItemNo, HTint dwItemID, HTint iDurability)
	// D : ������ ���濡 ���� ���� ǥ�� �޼��� ���� �� �Ҹ� 
	//-----------------------------------------------------------------------------
	HTvoid					HT_vSetDurabilityMsg( );
	// ���� ������ ��� ǥ���ϴ� ������ ������ �����Ѵ�.
	HTvoid					HT_vItemSystem_DelDurabilityWarning( );

	HTvoid					HT_vShowItemName() { m_bShowItemName = !m_bShowItemName; };

	//--------------------------------------------------------------------------
	// �޼��� ���
	//--------------------------------------------------------------------------
	HTvoid					HT_vItemSystem_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid					HT_vItemSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTint					m_iItem_Count;

private:
	HT_NODE*				m_sHead;
	HT_NODE*				m_sTail;

	CHTTimer*				m_pTimer;
	HTbool					m_bReformNeed[_eITEM_EQUIP_NUM];
	HTbool					m_bTReformNeed; // ������ ��� �ʿ�����
	HTint					m_iNeedReformPlace;	// ������ ����ϰ� �ִ� �������� ���� ��ġ
	HTfloat					m_flastWarningTime;	// ���������� ������ ����� �ð�

	HTdword					m_dwMapItemkeyID;	// ���� ������ ������ �Ⱦ��� KeyID

	//	���� �Ǿ����� �����ִ� ����Ʈ
	HTint					m_iItemTargettingEffectID;
	HTbool					m_bShowItemName;
	// �޼��� ����
	HTdword					m_dwMsgItemKeyID;
	CHTString				m_strMsgCharName;
};

#endif

