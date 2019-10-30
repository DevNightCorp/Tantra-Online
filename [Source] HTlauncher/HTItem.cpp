
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTItem.h"

#define HT_ITEM_SIZE	1

CHTItemAl::CHTItemAl()
{
	m_bItem3DID_Sw = HT_FALSE;
	
	//----------������ �Ⱦ��� �ߴ°�?----------//
	m_bItem_PickUp_Sw		= HT_FALSE;
	//-----������ ���� �����ֱ�-----//
	m_bItem_Info_Sw			= HT_FALSE;

	m_iCellNumber = 0;
	m_iItemDlgNo = -1;
	m_iItemTextureID = 0;
	m_iItem3DID = 0;
	m_bPossible = HT_TRUE;

	ZeroMemory( &m_sItemInfo, sizeof( STRUCT_ITEM ) );
	// ���Ե� �������
	for( HTint i = 0 ; i < MAX_EFFECT_NUM*MAX_REFINE_SUB_LEVEL ; ++i )
		ZeroMemory( &m_sItem_SubRefineInfo[i], sizeof( HTITEM_REFINE_PARAM ) );
	m_bySubEffectIDCount = 0;
	m_dwItemKeyID = 0;
}

CHTItemAl::~CHTItemAl()
{
	//	2D �� ����
	HT_vSystem_Delete2DItem();
	//	3D �� ����
	HT_vItemCreate_Destory();
}

// Map
HTvoid CHTItemAl::HT_vItemCreate( PS_SCP_MAP_ITEM_APPEAR info )
{
	//	Ű���̵�� �ε����� �����ϰ�,
	m_dwItemKeyID			= info->nItemID;
	m_sItemInfo.snIndex		= (HTshort)info->dwIndex + HT_ITEM_INDEX_START;
	m_sItemInfo.snDurability = 0;
	m_sItemInfo.byCount		= 0;

	//	������ ��Ÿ���� ������ ������ġ�� �ʵ�� ���������ش�.
	m_iItemLocation			= ITEM_LOCATION_MAP;
	m_iItemInInventory		= ITEM_LOCATION_MAP_FIELD;
	m_sItemMapCellX			= info->snX;
	m_sItemMapCellZ			= info->snZ;

	//	���ʿ��� � �׼ǵ� ������
	m_bItemActive			= HT_FALSE;
	
	m_byItemEquipPos = m_byItemSizeX = m_byItemSizeY = 0;	
	m_sItemType = 0;
	if( g_pParamMgr->HT_bGetItemName( m_sItemInfo.snIndex, &m_strItemName ) == false )
		m_strItemName.HT_hrCleanUp();
	
	//----------3D �𵨰� ����----------//
	HT_vItemCreate_Object();
}

// PC/NPC Inventory, OtherTrade, Store_Sell
HTvoid CHTItemAl::HT_vItemCreate( HTbyte byLocation, HTbyte byX, HTbyte byZ, HTint iKeyID, STRUCT_ITEM info, HTbyte byBagNo )
{
	//---------------------------------
	if( g_pParamMgr->HT_bLockID( info.snIndex+HT_ITEM_INDEX_START ) == true ) // ������ ���� Lock ����
	{
		//	Ű���̵�� �ε��� �� ��ġ�� �����ϰ�
		m_dwItemKeyID			= iKeyID;
		m_sItemInfo.snIndex		= info.snIndex + HT_ITEM_INDEX_START;
		m_sItemInfo.snDurability= info.snDurability;
		m_sItemInfo.wSerial		= info.wSerial;
		m_sItemInfo.snDummy		= info.snDummy;
		m_sItemInfo.byCount		= info.byCount;
		m_sItemInfo.byDummy		= info.byDummy;
		m_sItemInfo.byRefineLevel=info.byRefineLevel;

		m_sItemMapCellX			= 10;
		m_sItemMapCellZ			= 10;
		m_byInventory_CellPosX	= byX;
		m_byInventory_CellPosY	= byZ;

		//	�������� ������ ��������
		HT_vItemAI_GetItemEquipPos( m_sItemInfo.snIndex, &m_byItemEquipPos );
		m_byItemSizeX = m_byItemSizeY = HT_ITEM_SIZE;	// ��� ������ ũ�Ⱑ 1*1�� ��������.
		g_pParamMgr->HT_bGetItemType( &m_sItemType );
		if( g_pParamMgr->HT_bGetItemName( &m_strItemName ) == false )
			m_strItemName.HT_hrCleanUp();
		
		g_pParamMgr->HT_bUnLockID( info.snIndex+HT_ITEM_INDEX_START ); // ������ ���� Lock ����
	}
	else
		return;

	//----------2D �̹��� ����----------//
	HT_vSystem_Create2DItem();

	m_iItemLocation			= byLocation;
	if( m_iItemLocation == ITEM_LOCATION_EXCHANGE )				m_iItemInInventory = ITEM_LOCATION_EXCHANGE_OTHERWIN;
	else if( m_iItemLocation == ITEM_LOCATION_NPC )				m_iItemInInventory = ITEM_LOCATION_NPC_ITEMSAVED;
	else if( m_iItemLocation == ITEM_LOCATION_ASHRAMCARGO )		m_iItemInInventory = ITEM_LOCATION_ASHRAMCARGO_BAG1;
	else if( m_iItemLocation == ITEM_LOCATION_STORE )			m_iItemInInventory = ITEM_LOCATION_STORE_SELL;
	else if( m_iItemLocation == ITEM_LOCATION_RENTALSTORE )		m_iItemInInventory = ITEM_LOCATION_RENTALSTORE_BAG1;
	else														m_iItemInInventory = byBagNo;	

	HT_ITEMSETTING_FLAG flag;
	flag.nLocation = m_iItemLocation;
	flag.nInventory = m_iItemInInventory;
	flag.pCellPos.x = m_byInventory_CellPosX;
	flag.pCellPos.y = m_byInventory_CellPosY;

	//----------�κ��丮���� ������ �����ϱ�----------//
	this->HT_vItemAlSettingInventoryPos( flag );
}

// Equipment 
HTvoid CHTItemAl::HT_vItemCreate( HTbyte byPlace, HTint iKeyID, STRUCT_ITEM info )
{ 
	//---------------------------------
	HTshort snAttackSpeed = 0;
	HTint iCoolDownTime = 0;
	HTbyte byRange = 0;
	if( g_pParamMgr->HT_bLockID( info.snIndex+HT_ITEM_INDEX_START ) == true ) // ������ ���� Lock ����
	{
		//	Ű���̵�� �ε��� �� ��ġ�� �����ϰ�
		m_dwItemKeyID			= iKeyID;
		m_sItemInfo.snIndex		= info.snIndex + HT_ITEM_INDEX_START;
		m_sItemInfo.snDurability= info.snDurability;
		m_sItemInfo.wSerial		= info.wSerial;
		m_sItemInfo.snDummy		= info.snDummy;
		m_sItemInfo.byCount		= info.byCount;
		m_sItemInfo.byDummy		= info.byDummy;
		m_sItemInfo.byRefineLevel=info.byRefineLevel;

		m_sItemMapCellX			= 10;
		m_sItemMapCellZ			= 10;
		m_byInventory_CellPosX	= 0;
		m_byInventory_CellPosY	= 0;

		//	�������� ������ ��������
		HT_vItemAI_GetItemEquipPos( m_sItemInfo.snIndex, &m_byItemEquipPos );
		m_byItemSizeX = m_byItemSizeY = HT_ITEM_SIZE;	// ��� ������ ũ�Ⱑ 1*1�� ��������
		g_pParamMgr->HT_bGetItemType( &m_sItemType );
		if( g_pParamMgr->HT_bGetItemName( &m_strItemName ) == false )
			m_strItemName.HT_hrCleanUp();

		// ���� ������ġ�� �����ϰ�
		m_iItemLocation			= ITEM_LOCATION_EQUIP;
		m_iItemInInventory		= byPlace;

		g_pParamMgr->HT_bGetItemRange( &byRange );
//		g_pParamMgr->HT_bGetItemCoolDownTime( iCoolDownTime );

		g_pParamMgr->HT_bUnLockID( info.snIndex+HT_ITEM_INDEX_START ); // ������ ���� Lock ����
	}	// end of if( g_pParamMgr->HT_bLockID( info.snIndex+HT_ITEM_INDEX_START ) == true ) // ������ ���� Lock ����
	else
		return;

	if( byPlace == ITEM_LOCATION_EQUIP_HEAD )
	{	
		if( m_sItemInfo.snIndex == ITEMINDEX_ASSISTANTHAT ) 		//	������������ �ľ�
			g_cItemControl->HT_bItemControl_SetAssistant( HT_TRUE );
	}
	else if( byPlace == ITEM_LOCATION_EQUIP_TWO_HAND )	// ���
	{
		m_iItemInInventory = ITEM_LOCATION_EQUIP_RIGHT_HAND;
		g_cEquipInventory->HT_vEquipInventory_SetRightItem( m_sItemInfo.snIndex );
		g_cEquipInventory->HT_vEquipInventory_SetRightItem_KeyID( m_dwItemKeyID );
		g_cMainCharacter->HT_vMainChar_SetArmsType( m_sItemInfo.snIndex );
	}
	else if( byPlace == ITEM_LOCATION_EQUIP_LEFT_HAND && CHTParamIDCheck::HT_bIsItemUsableArrow(m_sItemInfo.snIndex) == false )
	{
		g_cEquipInventory->HT_vEquipInventory_SetLeftItem( m_sItemInfo.snIndex );
	}
	else if( byPlace == ITEM_LOCATION_EQUIP_RIGHT_HAND ) 
	{
		g_cMainCharacter->HT_vMainChar_SetArmsType( m_sItemInfo.snIndex );
	}

	// �κ��丮 Ȯ��� ������ �Ǵ� ȭ���� �ƴ� ���
	if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( m_sItemInfo.snIndex ) == false 
				&& CHTParamIDCheck::HT_bIsItemUsableArrow( m_sItemInfo.snIndex ) == false )
	{
		HTdword iNormalIndex, iLeftIndex;
		iNormalIndex = m_sItemInfo.snIndex;	iLeftIndex = 0;
        if( byPlace == ITEM_LOCATION_EQUIP_LEFT_HAND )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalIndex ) )
			{	iLeftIndex = iNormalIndex;	iNormalIndex = 0;		}
		}
        g_cEquipSystem->HT_EquipSys_Equip( g_cMainCharacter->HT_vMainChar_GetModelID(), g_oMainCharacterInfo.snTribe,
											iNormalIndex, iLeftIndex, g_cMainCharacter->HT_vMainChar_GetHeadType() );
	}
	//----------2D �̹��� ����----------//
	HT_vSystem_Create2DItem();	// ������ῡ ���� �߰��� �Ӽ� ������ ���� ������ �ʱ�ȭ�Ѵ�.

	HT_ITEMSETTING_FLAG flag;
	flag.nLocation = m_iItemLocation;
	flag.nInventory = m_iItemInInventory;
	flag.pCellPos.x = m_byInventory_CellPosX;
	flag.pCellPos.y = m_byInventory_CellPosY;

	//----------�κ��丮���� ������ �����ϱ�----------//
	this->HT_vItemAlSettingInventoryPos( flag );

//	m_bPossible = HT_TRUE;	// Equipment�� �ֱ� ������ ���밡���� ��.
}

//----------������� �Ӽ� ���� �ʱ�ȭ----------//
HTvoid CHTItemAl::HT_vItemAI_ClearSubItemInfo()
{
	for( HTint i = 0 ; i < MAX_REFINE_SUB_LEVEL*MAX_EFFECT_NUM ; ++i )
		ZeroMemory(&m_sItem_SubRefineInfo[i], sizeof(HTITEM_REFINE_PARAM));

	m_bySubEffectIDCount = 0;
	ZeroMemory( m_sItemInfo.bySubRefine , sizeof(HTbyte)*MAX_SUBMATERIALSIZE );
}

//----------�κ��丮���� ������ �����ϱ�----------//
HTvoid CHTItemAl::HT_vItemAlSettingInventoryPos( HT_ITEMSETTING_FLAG flag, HTbool bDrawTwinImage )
{
	// ���� �ڸ��� �ִ� ������ �׸� �����
	if( m_iItemLocation == ITEM_LOCATION_PC )
	{
		if( m_iItemDlgNo != -1 )
			g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, m_iCellNumber, 0 );
		// �������� ���� �ɷ�������
        if( m_bPossible == HT_FALSE ) 
		{
			// ���� �� �����
		}
		
	}
	else if ( g_cUIManager )
	{
		if( m_iItemDlgNo != -1 )
			g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, m_iCellNumber, 0 );
		// �����ߴ� ��� �������� ��� ���� �̹��� �����
		if( m_iItemLocation == ITEM_LOCATION_EQUIP && m_iItemInInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND
			&& ( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( m_sItemInfo.snIndex )
				|| CHTParamIDCheck::HT_bIsItemWeaponThrow( m_sItemInfo.snIndex ) ) )
		{
			// �޼տ� �������� �������� �ʾ��� ��� �޼� ��Ʈ�� �����
			if( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) == 0 )
			{
				// �̹��� �����
				g_cUIManager->HT_SetSlotImage( _DIALOG_EQUPINVENTORY, _INVEN_DEFENCE_WEAPON, 0 );
				// ���� �� �����
			}
		}
	}

	m_iItemLocation = flag.nLocation;
	m_iItemInInventory = flag.nInventory;
	m_byInventory_CellPosX = flag.pCellPos.x;
	m_byInventory_CellPosY = flag.pCellPos.y;

	// ��ġ�� ���� ItemKeyID�� �ٲ�� ������ ���� ���� �ؾ��Ѵ�.
	HTint iKeyID = 0, index = 0;
	if( m_iItemLocation == ITEM_LOCATION_EQUIP )
	{
		index = m_iItemInInventory;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else if( m_iItemLocation == ITEM_LOCATION_NPC )
	{
		index = ( m_byInventory_CellPosY * _GOODSKEEP_INVEN_WIDTH + m_byInventory_CellPosX );
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_CARGO, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else if( m_iItemLocation == ITEM_LOCATION_ASHRAMCARGO )
	{
		index = ( m_byInventory_CellPosY * _GOODSKEEP_INVEN_WIDTH + m_byInventory_CellPosX );
		m_byInventory_CellPosX = ( index-(g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120) ) % _GOODSKEEP_INVEN_WIDTH; 
		m_byInventory_CellPosY = ( index-(g_cGuildSystem->HT_byAshram_GetCargoExtenceType()*120) ) / _GOODSKEEP_INVEN_WIDTH;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else if( m_iItemLocation == ITEM_LOCATION_RENTALSTORE )
	{
		index = ( m_byInventory_CellPosY * _RENTALSTORE_INVEN_WIDTH + m_byInventory_CellPosX );
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_RENTALSTORE, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else if( m_iItemLocation == ITEM_LOCATION_EXCHANGE )
	{
		index = m_byInventory_CellPosY * _TRADE_INVEN_WIDTH + m_byInventory_CellPosX;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_OTHERTRADE, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else if( m_iItemLocation == ITEM_LOCATION_STORE )
	{
		index = m_byInventory_CellPosY * _STORE_WIDTH + m_byInventory_CellPosX;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_STORE, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}
	else //if( m_iItemLocation == ITEM_LOCATION_PC )
	{
		index = ( m_byInventory_CellPosX * _INVEN_HEIGHT + m_byInventory_CellPosY ) + ( m_iItemInInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, index, iKeyID);
		m_dwItemKeyID = iKeyID;
	}	
	

	HTint iGroupNo = -1;
	
	switch( flag.nLocation )
	{
		case ITEM_LOCATION_PC :
			iGroupNo = flag.nInventory;
			m_iCellNumber = ( m_byInventory_CellPosY *_INVEN_WIDTH ) + m_byInventory_CellPosX + _SLOTCURRECT_INVEN;
			if( iGroupNo == 0 )
			{
				m_iItemDlgNo = _DIALOG_EQUPINVENTORY;
			}
			else
			{
				m_iItemDlgNo = _DIALOG_INVENTORY2;
				m_iCellNumber += _SLOTCURRECT_ADDINVEN;
			}
			
			break;
		case ITEM_LOCATION_EQUIP :
            m_iItemDlgNo = _DIALOG_EQUPINVENTORY;
			if( flag.nInventory == ITEM_LOCATION_EQUIP_HEAD )					m_iCellNumber = _INVEN_HEAD;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_RIGHT_EAR )			m_iCellNumber = _INVEN_RIGHT_EARING;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_LEFT_EAR )			m_iCellNumber = _INVEN_LEFT_EARING;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_NECK )				m_iCellNumber = _INVEN_NECKLACE;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_ARMOR )				m_iCellNumber = _INVEN_BODY;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_BELT )				m_iCellNumber = _INVEN_BELT;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_RIGHT_HAND )		m_iCellNumber = _INVEN_ATTACK_WEAPON;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_LEFT_HAND )			m_iCellNumber = _INVEN_DEFENCE_WEAPON;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_RIGHT_BRACELET )	m_iCellNumber = _INVEN_RIGHT_ARMLET;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_LEFT_BRACELET )		m_iCellNumber = _INVEN_LEFT_ARMLET;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_RIGHT_RING )		m_iCellNumber = _INVEN_RIGHT_RING;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_LEFT_RING )			m_iCellNumber = _INVEN_LEFT_RING;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_FOOT )				m_iCellNumber = _INVEN_FOOT;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_BAG )				m_iCellNumber = _INVEN_BAG;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_PANTS )				m_iCellNumber = _INVEN_TROUSERS;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_GLOVE )				m_iCellNumber = _INVEN_GLOVES;
			else if( flag.nInventory == ITEM_LOCATION_EQUIP_BAG )				m_iCellNumber = _INVEN_BAG;
			else			m_iCellNumber = -1;
			break;
		case ITEM_LOCATION_NPC :
			m_iItemDlgNo = _DIALOG_GOODSKEEPWND;
			m_iCellNumber = 10 + ((m_byInventory_CellPosY*_GOODSKEEP_INVEN_WIDTH)+m_byInventory_CellPosX);
			break;
		case ITEM_LOCATION_ASHRAMCARGO :
			m_iItemDlgNo = _DIALOG_ASHRAMCAGO;
			m_iCellNumber = 10 + ((m_byInventory_CellPosY*_GOODSKEEP_INVEN_WIDTH)+m_byInventory_CellPosX);
			break;
		case ITEM_LOCATION_EXCHANGE :
			m_iItemDlgNo = _DIALOG_TRADEWND;
			if( m_iItemInInventory	== ITEM_LOCATION_EXCHANGE_OTHERWIN )
				m_iCellNumber = ( m_byInventory_CellPosY*_TRADE_INVEN_WIDTH ) + m_byInventory_CellPosX + _TRADE_INVEN_YOU_START;
			else
				m_iCellNumber = ( m_byInventory_CellPosY*_TRADE_INVEN_WIDTH ) + m_byInventory_CellPosX + _TRADE_MY_BEGIN;
			break;
		case ITEM_LOCATION_ECONOMY :
			m_iItemDlgNo = _DIALOG_REFINE;
			m_iCellNumber = _ITEMREFINE_SUBITEM_POS ;
			break;
		case ITEM_LOCATION_STORE:
			m_iItemDlgNo = _DIALOG_INDIVIDUALWND2;
			m_iCellNumber = ( m_byInventory_CellPosY*_STORE_WIDTH ) + m_byInventory_CellPosX + _STORE_BUY_BEGIN;
			break;
		case ITEM_LOCATION_RENTALSTORE:
			m_iItemDlgNo = _DIALOG_RENTALSTORE;
			m_iCellNumber = ( m_byInventory_CellPosY*_RENTALSTORE_INVEN_WIDTH ) + m_byInventory_CellPosX + _RENTALSTORE_INVEN_BEGIN;
			break;
	}
	
	if( iGroupNo >= 0 )
	{
        g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, m_iCellNumber, m_iItemTextureID );
	}
	else
	{
		g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, m_iCellNumber, m_iItemTextureID );
		
		// ���
		if( m_iItemLocation == ITEM_LOCATION_EQUIP && m_byItemEquipPos == ITEM_LOCATION_EQUIP_TWO_HAND 
												   && bDrawTwinImage == HT_TRUE )	
		{
			// �޼��ʿ� ������ �̹��� �׸���
			// �޼��ʿ� ����� �׸���
			g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, 15, m_iItemTextureID );
		}
	}
	//------------------------------
	// �������� ���׿� �ɸ��ٸ� ������ ���� ������ ó���ؾ��Ѵ�.
	if( m_iItemLocation == ITEM_LOCATION_PC || m_iItemLocation == ITEM_LOCATION_NPC || m_iItemLocation == ITEM_LOCATION_EQUIP )
	{
		m_bPossible = HT_bItemAl_PossibleCheck( m_sItemInfo.snIndex, HT_TRUE );
		if( m_bPossible == HT_FALSE )
		{
//			g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_EQUPINVENTORY, m_iCellNumber, HT_FALSE );
		}
	}
	else
	{
		m_bPossible = HT_TRUE;
//		g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_EQUPINVENTORY, m_iCellNumber, HT_TRUE );
	}
}

//----------3D �� ����----------//
HTvoid CHTItemAl::HT_vItemCreate_Object()
{
	m_bItem3DID_Sw = HT_TRUE;
	//	���� �������� �̹������� �ε��Ѵ�. 3D Model -> 2D Image ������
	HT_CELL_COORD codCell1;
	codCell1.x = m_sItemMapCellX;
	codCell1.y = m_sItemMapCellZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecItem3DPosition, codCell1 );
	m_vecItem3DPosition.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecItem3DPosition.x, m_vecItem3DPosition.z );

	m_iItem3DID = g_pEngineHandler->HT_iCreateFieldItem( m_sItemInfo.snIndex, m_vecItem3DPosition );
}

//----------3D �� ����-----------//
HTvoid CHTItemAl::HT_vItemCreate_Destory()
{
	if( m_bItem3DID_Sw == HT_TRUE && m_iItem3DID != 0 )
	{
		m_bItem3DID_Sw = HT_FALSE;
		g_pEngineHandler->HT_vDestroyFieldItem( m_iItem3DID, 10 );
        m_iItem3DID = 0;
	}	
}

//----------2D �������� ����----------//
HTvoid CHTItemAl::HT_vSystem_Create2DItem()
{
	m_bItem2DID_Sw = HT_TRUE;
	m_iItemTextureID = g_pEngineHandler->HT_dwGetItemUIID( m_sItemInfo.snIndex );
	//-------------------------------------
	// �ʿ��� �ֿ� �������� ���� ������� �Ӽ� ���� �ʱ�ȭ�� ���⿡ �־���. 2003.3.21 ����.
	HT_vItemAI_ClearSubItemInfo();
}

//---------2D �� ����-----------//
HTvoid CHTItemAl::HT_vSystem_Delete2DItem()
{
	//	2D �̹��� �����
	if( m_iItemTextureID !=0 && m_iItemDlgNo != -1 )
	{
		g_cUIManager->HT_SetSlotImage( m_iItemDlgNo, m_iCellNumber, 0 );
		m_iItemTextureID = 0;
		m_iItemDlgNo = -1;
	}
}

//----------�ʻ� �������� ����----------//
HTvoid CHTItemAl::HT_vItemAlThrowMap( HTint iTargetCellX, HTint iTargetCellZ )
{
	//	2D �� ����
	HT_vSystem_Delete2DItem();

	m_bItemActive			= HT_FALSE;
	m_sItemMapCellX			= iTargetCellX;
	m_sItemMapCellZ			= iTargetCellZ;

	m_iItemLocation			= ITEM_LOCATION_MAP;
	m_iItemInInventory		= ITEM_LOCATION_MAP_FIELD;
	
	//----------3D �� ����----------//
	HT_vItemCreate_Object();
}

//----------�ʻ��� ĳ���Ϳ� �������� ����ġ ��----------//
HTbool CHTItemAl::HT_bComCharacterAndItem()
{
	if( m_iItemLocation	== ITEM_LOCATION_MAP )
	{
		HTPoint CellPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		if( CellPos.x == m_sItemMapCellX && CellPos.y == m_sItemMapCellZ )
		{
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

//----------- �������� ���׿� �ɸ����� �˻�---------------//
HTbool CHTItemAl::HT_bItemAl_PossibleCheck( DWORD dwItemIndex, HTbool bLevelCheck )
{
	HTbool bAllow = HT_TRUE;

	//	�������� ������ ��������
	HTshort sLimit;
	HTbyte byteLimit;
	HTint iLimit;
	if( g_pParamMgr->HT_bLockID( dwItemIndex ) == true )
	{
		// ������ ��ũ��
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitMuscleChakra(&sLimit) == true && sLimit > 0 )
		{
			if( g_cStatus->HT_nGetChakraMuscle() < (HTint)sLimit )		
				bAllow = HT_FALSE;
		}
		// �Ű��� ��ũ��
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitNerveChakra(&sLimit) == true && sLimit > 0)
		{
			if( g_cStatus->HT_nGetChakraNerve() < (HTint)sLimit )		
				bAllow = HT_FALSE;
		}
		// ������ ��ũ��
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitHeartChakra(&sLimit) == true && sLimit > 0)
		{
			if(g_cStatus->HT_nGetChakraHeart() < (HTint)sLimit )		
				bAllow = HT_FALSE;
		}
		// ������ ��ũ��
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitSoulChakra(&sLimit) == true && sLimit > 0)
		{
			if(g_cStatus->HT_nGetChakraSoul() < (HTint)sLimit )		
				bAllow = HT_FALSE;
		}
		// ���� ���ѻ���
		if(bLevelCheck == HT_TRUE && bAllow == HT_TRUE 
							&& g_pParamMgr->HT_bGetItemLimitLevel(&byteLimit) == true && byteLimit > 0)	
		{
			//HTbyte byteLevel = 0;
			// 5���� ������ �����۸� ���� ���ѻ����� �����Ѵ�.
			//if( g_pParamMgr->HT_bGetItemLevel( &byteLevel ) == true )
			{
				if(/*byteLevel <= 5 &&*/ g_cStatus->HT_byGetLevel() < byteLimit )
					bAllow = HT_FALSE;
			}
		}
		// �ֽ�����
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitTrimuriti( &iLimit ) == true && iLimit > 0)	
		{
			if( !BIT_AND( g_oMainCharacterInfo.byTrimuriti, iLimit ) )
				bAllow = HT_FALSE;
		}
		// ��������
		if(bAllow == HT_TRUE && g_pParamMgr->HT_bGetItemLimitTribe( &iLimit ) == true && iLimit > 0  )
		{
			if( !BIT_AND( g_cMainCharacter->HT_iMainChar_GetTribeServerCode(), iLimit ) )	
			{
				bAllow = HT_FALSE;
			}
		}

		g_pParamMgr->HT_bUnLockID( dwItemIndex ); // ������ ���� Lock ����
	}
	else
		return HT_FALSE;
	
	return bAllow;
}

//----------������ �׸��� ��ġ �˾ƿ���----------//
HTPoint CHTItemAl::HT_ptGeItemSystemCell()
{
	HTPoint ItemCell;

	ItemCell.x = m_sItemMapCellX;
	ItemCell.y = m_sItemMapCellZ;

	return ItemCell;
}

//----------�׸���----------//
HTvoid CHTItemAl::HT_vItemAlRender()
{
	HTvector3 vTextPos = m_vecItem3DPosition;
	vTextPos.y += 5;
	if( m_bItem_PickUp_Sw == HT_FALSE )
        g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strItemName, vTextPos, g_ColorTable[15] ); // white
	else
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strItemName, vTextPos, g_ColorTable[11] ); // red
}

HTvoid CHTItemAl::HT_vItemAI_GetItemEquipPos( DWORD dwItemIndex, HTbyte* byEquipPos )
{
	if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(dwItemIndex) )			// �Ӹ�
		*byEquipPos = ITEM_LOCATION_EQUIP_HEAD;
		
	else if( CHTParamIDCheck::HT_bIsItemAccessoryEarring(dwItemIndex) ) // �Ͱ���
		*byEquipPos = ITEM_LOCATION_EQUIP_RIGHT_EAR;
	
	else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace(dwItemIndex) )// �����
		*byEquipPos = ITEM_LOCATION_EQUIP_NECK;
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceArmor(dwItemIndex) )		// ��
		*byEquipPos = ITEM_LOCATION_EQUIP_ARMOR;

	else if( CHTParamIDCheck::HT_bIsItemDefenceBelt(dwItemIndex) )		// ��Ʈ
		*byEquipPos = ITEM_LOCATION_EQUIP_BELT;

	// ��չ��Ⱑ �����ʿ� �������� ����
	// ��� || Ȱ
	else if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand(dwItemIndex) || CHTParamIDCheck::HT_bIsItemWeaponThrow(dwItemIndex) )	
		*byEquipPos = ITEM_LOCATION_EQUIP_TWO_HAND;	
	
	else if( CHTParamIDCheck::HT_bIsItemWeaponOneHand(dwItemIndex) )	// ������
		*byEquipPos = ITEM_LOCATION_EQUIP_RIGHT_HAND;
	
	else if( CHTParamIDCheck::HT_bIsItemDefenceShield(dwItemIndex) )	// �޼�
		*byEquipPos = ITEM_LOCATION_EQUIP_LEFT_HAND;

	else if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet(dwItemIndex) )// ����
		*byEquipPos = ITEM_LOCATION_EQUIP_RIGHT_BRACELET;

	else if( CHTParamIDCheck::HT_bIsItemAccessoryRing(dwItemIndex) )	// ����
		*byEquipPos = ITEM_LOCATION_EQUIP_RIGHT_RING;

	else if( CHTParamIDCheck::HT_bIsItemDefenceShoes(dwItemIndex) )		// ��
		*byEquipPos = ITEM_LOCATION_EQUIP_FOOT;

	else if( CHTParamIDCheck::HT_bIsItemDefenceGloves(dwItemIndex) )	// �尩
		*byEquipPos = ITEM_LOCATION_EQUIP_GLOVE;

	else if( CHTParamIDCheck::HT_bIsItemDefencePants(dwItemIndex) )		// ����
		*byEquipPos = ITEM_LOCATION_EQUIP_PANTS;

	else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(dwItemIndex) )	// �κ��丮 Ȯ��� ������
		*byEquipPos = ITEM_LOCATION_EQUIP_BAG;

	else if( CHTParamIDCheck::HT_bIsItemUsableArrow(dwItemIndex) )		// ȭ��
		*byEquipPos = ITEM_LOCATION_EQUIP_LEFT_HAND;

	else
		*byEquipPos = 0x00;
}