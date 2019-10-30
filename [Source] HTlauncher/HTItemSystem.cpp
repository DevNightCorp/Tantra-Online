
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTItemSystem.h"

#define _DURABLE_WARN_SOUND		33529
#define _DURABLE_WARN_TIMES		3

#define HT_DURABILITY_WARNING_TIME	120.0f	// ������ ��� ǥ���ϴ� �ֱ�

CHTItemSystem::CHTItemSystem()
{
	for (HTint i=0; i < _eITEM_EQUIP_NUM; i++)
	{
		m_bReformNeed[i] = HT_FALSE;
	}

	m_bTReformNeed				= HT_FALSE;
	m_flastWarningTime			= 0.0f;
	m_iNeedReformPlace			= -1;

	m_iItemTargettingEffectID	= 0;
	m_bShowItemName = HT_FALSE;

	m_pTimer = HT_NULL;
}

CHTItemSystem::~CHTItemSystem()
{
}

HTvoid CHTItemSystem::HT_vItemSystem_CleanUp()
{
	HT_LL_hrDeleteAll();
	HT_DELETE( m_sHead );
	HT_DELETE( m_sTail );

	m_pTimer->Do( HT_TIMER_STOP );
	HT_DELETE( m_pTimer );
}

//----------������ �ý��� ����----------//
HTRESULT CHTItemSystem::HT_hrSystemInit()
{
	m_iItem_Count = 0;
	HT_LL_vInitList();

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	return HT_OK;
}

//----------������ ��Ʈ��----------//
HTvoid CHTItemSystem::HT_vItemSystem_Control()
{
	HT_NODE *t;
	HT_NODE *s;
	
	t = m_sHead->next;
	while( t != m_sTail )
	{
		s = t;
		t = t->next;
		HT_vItemSystem_AOI_Check( s );
	}
	
	// ������ ��� �ʿ��ϸ�
	if( m_bTReformNeed )
	{
		HTfloat fCurrentTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );
		if( fCurrentTime - m_flastWarningTime >= HT_DURABILITY_WARNING_TIME )
		{
			HT_vSetDurabilityMsg();
			m_flastWarningTime = fCurrentTime;
		}
	}
}

//----------AOI ���� üũ----------//
HTvoid CHTItemSystem::HT_vItemSystem_AOI_Check( HT_NODE *t )
{
	if( t->cItem.m_iItemLocation != ITEM_LOCATION_MAP )
		return;

	//	AOI Check
	if( g_cAoi->HT_AOI_Level( t->cItem.HT_ptGeItemSystemCell() ) == AOI_LEVEL_NONE )
	{
		this->HT_vItemSystem_DeleteItem( t->cItem.m_dwItemKeyID );
	}
}

//----------�׸��� �κ�---------//
HTRESULT CHTItemSystem::HT_hrSystemRender()
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( GetAsyncKeyState( VK_MENU ) < 0 )
		{
			//----------����_�̸�_3d----------//
			if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP )
				HT_vItemSystem_RenderName( t );
		}

		t = t->next;
	}

	return HT_OK;
}

//----------����_�̸�_3d----------//
HTvoid CHTItemSystem::HT_vItemSystem_RenderName( HT_NODE* t )
{
	HTvector3 vTextPos = t->cItem.m_vecItem3DPosition;
	vTextPos.y += 5;
	if( t->cItem.m_bItem_PickUp_Sw == HT_FALSE )
        g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->cItem.m_strItemName, vTextPos, g_ColorTable[15] ); // white
	else
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->cItem.m_strItemName, vTextPos, g_ColorTable[11] ); // red
}

//----------������ �������� ��Ÿ�� ��----------//
HTvoid CHTItemSystem::HT_vItemSystem_Appear( PS_SCP_MAP_ITEM_APPEAR info )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == info->nItemID )
		{
			t->cItem.m_vecItem3DPosition.y = g_pEngineHandler->HT_fGetTerrainHeight( t->cItem.m_vecItem3DPosition.x, t->cItem.m_vecItem3DPosition.z );
			g_2DObjectMgr->HT_2DObjectMgrSetPosition( t->cItem.m_iItem3DID, t->cItem.m_vecItem3DPosition );
			return;
		}
		t = t->next;
	}

	HT_NODE *s;
	s = NULL;
	s = new HT_NODE;

	s->cItem.HT_vItemCreate( info );
	s->next = m_sHead->next;
	m_sHead->next = s;
}

//----------�ʻ󿡼� �������� �������----------//
HTvoid CHTItemSystem::HT_vItemSystem_DisAppear( PS_SCP_MAP_ITEM_DISAPPEAR info )
{
	HT_NODE* t = NULL;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == info->nItemID )
		{
			if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP )
			{
				if( !CHTParamIDCheck::HT_bIsItemUsableMoney(t->cItem.m_sItemInfo.snIndex) )// ���� �ƴ� ��츸
				{
					// ��Ƽ�� �����Ǿ��ְ� ��Ƽ���� ȹ������ ���
					if( g_cParty->HT_bParty_IsPartyMember( info->szName ) &&
						g_cParty->HT_bParty_GetRootingMode() )
					{
						CHTString szMessage;
						m_dwMsgItemKeyID = t->cItem.m_dwItemKeyID; // ������ �̸�
						m_strMsgCharName = info->szName; // ĳ���� �̸�
						HT_vItemSystem_SetMessage( eMsgItemMoveAutoReceive, &szMessage ); // [�ڵ��й�]%s,%s ȹ��
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
					}
				}

				HT_LL_hrDeleteNode( info->nItemID );
			}
			return;
		}
		t = t->next;
	}
}

//----------3D�������� �����ϰ� 2D �������� �����´�---------//
HTvoid CHTItemSystem::HT_vItemSystem_3DItemHidden( HTint dwItemKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( dwItemKeyID == t->cItem.m_dwItemKeyID )
		{
			//	������ �������� ����Ʈ �����
			if( m_iItemTargettingEffectID != 0 )
			{
				g_pEngineHandler->HT_hrStopSFX( m_iItemTargettingEffectID );
				m_iItemTargettingEffectID = 0;
			}

			t->cItem.HT_vItemCreate_Destory();
			//----------2D �������� �����Ѵ�.----------//
//			t->cItem.HT_hrSystem_Create2DItem();	// 2003.4.2 ����
			break;
		}
		t = t->next;
	}
}

//----------�������� �ʿ� ������.---------//
HTvoid CHTItemSystem::HT_vItemSystem_ThrowItem( HTint iItemKeyID, HTPoint MapCell )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( iItemKeyID == t->cItem.m_dwItemKeyID )
		{
			t->cItem.HT_vItemAlThrowMap( MapCell.x, MapCell.y );
			break;
		}
		t = t->next;
	}
}

//----------�������� �������� üũ----------//
HTbool CHTItemSystem::HT_bItemSystem_PickUpItemCheck( DWORD dwItemKeyID )
{
	HTPoint pCellPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP )
		{
			if ( t->cItem.m_dwItemKeyID == dwItemKeyID )
			{
				m_dwMapItemkeyID = t->cItem.m_sItemInfo.snIndex;

				// HK : ������ ������ ������ ��ġ���� ���� �������� ������,
				// HK : ���� Ŭ���� NO-Move-Cell �� ������ ���縦 �����Ͽ�
				// HK : �μ��� ������ �־ �׳� �ֿ��������� �Ѵ�.
				//if ( t->cItem.m_sItemMapCellX == pCellPos.x && t->cItem.m_sItemMapCellZ == pCellPos.y ) return HT_TRUE;
				HTint iDiffX = HT_ABS( t->cItem.m_sItemMapCellX - pCellPos.x );
				HTint iDiffY = HT_ABS( t->cItem.m_sItemMapCellZ - pCellPos.y );
				if ( iDiffX <= 1 && iDiffY <= 1 ) return HT_TRUE;
			}
		}
		t = t->next;
	}
	return HT_FALSE;
}

//----------������ �Ⱦ��� ������ �ʱ�ȭ----------//
HTvoid CHTItemSystem::HT_vSystem_InitPickUpItemOnMap()
{
	HT_NODE* t;
	t = m_sHead->next;

	//	������ �������� ����Ʈ ó�� �����.
	if( m_iItemTargettingEffectID != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iItemTargettingEffectID );
		m_iItemTargettingEffectID = 0;
	}

	while( t != m_sTail )
	{
		t->cItem.m_bItem_PickUp_Sw	= HT_FALSE;
		//-----������ ���� �����ֱ�-----//
		t->cItem.m_bItem_Info_Sw	= HT_FALSE;
		t = t->next;
	}
}

//----------�ʼ����� ������ �˻�----------//
HTint CHTItemSystem::HT_iSystem_MapCellCheckToItemOnMap( HTint nX, HTint nZ )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP && t->cItem.m_iItemInInventory == ITEM_LOCATION_MAP_FIELD )
		{
			if( t->cItem.m_sItemMapCellX == nX && t->cItem.m_sItemMapCellZ == nZ )
			{
				//-----������ ���� �����ֱ�-----//
				t->cItem.m_bItem_Info_Sw			= HT_TRUE;
				g_pMainBar->HT_vSetObjectTextDraw( t->cItem.m_strItemName );
				return t->cItem.m_iItem3DID;
			}
		}
		t = t->next;
	}

	return 0;
}

//----------�������� ���̵� ���Ѵ�.----------//
HTint CHTItemSystem::HT_iSystem_ComIDCheck( HTint iItemImageID, HTPoint pPt )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItem3DID == iItemImageID )
		{
			//-----������ ���� �����ֱ�-----//
			t->cItem.m_bItem_Info_Sw			= HT_TRUE;
			g_pMainBar->HT_vSetObjectTextDraw( t->cItem.m_strItemName );
			return t->cItem.m_iItem3DID;
		}
		else if( GetAsyncKeyState( VK_MENU ) < 0 )
		{
			HTvector3 vTextPos = t->cItem.m_vecItem3DPosition;
			vTextPos.y += 5;
			HTvector2 vecPt;
			g_pEngineHandler->HT_hrGetScreenCoordFrom3DCoord( vTextPos, vecPt );
			if( vecPt.x>pPt.x-50 && vecPt.x<pPt.x+50 && vecPt.y>pPt.y-15 && vecPt.y<pPt.y+15 )
			{
				t->cItem.m_bItem_Info_Sw	= HT_TRUE;
				t->cItem.m_bItem_PickUp_Sw	= HT_TRUE;
				//-----������ ���� �����ֱ�-----//
				g_pMainBar->HT_vSetObjectTextDraw( t->cItem.m_strItemName );
				return t->cItem.m_iItem3DID;
			}
		}
		t = t->next;
	}

	return 0;
}

//-------������ Ư�� ��ġ�� �������� �ִ��� �˻��ؼ� ������ HT_TRUE�� ����---------//
HTRESULT CHTItemSystem::HT_hrCheckMapPos(HTPoint pos)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		//	������ �ִ� ���������� ��
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP && t->cItem.m_iItemInInventory == ITEM_LOCATION_MAP_FIELD)
		{
			// x, z ��ǥ ��
			if( t->cItem.m_sItemMapCellX == pos.x && t->cItem.m_sItemMapCellZ == pos.y )
			{
				return HT_TRUE;	// �� ��ġ�� �ٸ� �������� ����
			}
		}
		t = t->next;
	}
	
	return HT_FALSE;
}

//	������ ����ǥ�� ��ȯ KeyID
HT_CELL_COORD CHTItemSystem::HT_cellItemSystem_GetMapCellPosForKeyID( HTint iKeyID )
{
	HT_CELL_COORD cellPos;
	cellPos.x = 0;
	cellPos.y = 0;
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == iKeyID )
		{
			cellPos.x = t->cItem.m_sItemMapCellX;
			cellPos.y = t->cItem.m_sItemMapCellZ;
			return cellPos;
		}
		t = t->next;
	}

	return cellPos;	
}

//	������ ����ǥ�� ��ȯ ModelID
HT_CELL_COORD  CHTItemSystem::HT_cellItemSystem_GetMapCellPosForModelID( HTint iModelID )
{
	HT_CELL_COORD cellPos;
	cellPos.x = 0;
	cellPos.y = 0;
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItem3DID == iModelID )
		{
			cellPos.x = t->cItem.m_sItemMapCellX;
			cellPos.y = t->cItem.m_sItemMapCellZ;
			return cellPos;
		}
		t = t->next;
	}

	return cellPos;	
}

//----------������ ������ ���ﶧ---------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemDelete( DWORD dwItemKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
            HT_LL_hrDeleteNode( dwItemKeyID );
			break;
		}
		t = t->next;
	}
}

//----------������ ���θ� ����----------//
HTvoid CHTItemSystem::HT_vItemSystem_TotalItemDelete()
{
	// LL ����Ÿ ���� �����
	HT_LL_hrDeleteAll();
}

//----------�������� �����Ѵ�.---------//
HTvoid CHTItemSystem::HT_vItemSystem_DeleteItem( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			HT_LL_hrDeleteNode( dwKeyID );
			break;
		}
		t = t->next;
	}
}

//----------�κ��丮 ���� ������ ���θ� ����----------//
HTvoid CHTItemSystem::HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory )
{
	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == nLocation && s->cItem.m_iItemInInventory == nInventory )
		{
			HT_LL_hrDeleteNode( s->cItem.m_dwItemKeyID );
		}
	}
}

//----------�κ��丮 ���� Ư�� index�� ������ ���θ� ����----------//
HTvoid CHTItemSystem::HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory, DWORD dwItemIndex )
{
	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == nLocation && s->cItem.m_iItemInInventory == nInventory 
				&& s->cItem.m_sItemInfo.snIndex == dwItemIndex )
		{
			HT_LL_hrDeleteNode( s->cItem.m_dwItemKeyID );
		}
	}
}

//----------�κ��丮 ���� Ư�� type�� ������ ���θ� ����---------//
HTvoid CHTItemSystem::HT_vItemSystem_DeleteItemInventory( WORD wItemType, HTint nLocation, HTint nInventory )
{
	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == nLocation && s->cItem.m_iItemInInventory == nInventory 
				&& s->cItem.m_sItemType == wItemType )
		{
			HT_LL_hrDeleteNode( s->cItem.m_dwItemKeyID );
		}
	}
}

//----------�������� �̵�(����)�� �� �ִ� �κ��丮�ΰ�?----------//
HTint CHTItemSystem::HT_iItemAlSetPosInventoryCheck( DWORD dwKeyID, DWORD dwItemIndex, HT_ITEMSETTING_FLAG sSetItem )
{
	if( dwItemIndex <= 0 )	// �߸��� index�� ��� 
		return HT_RESULT_ITEM_MOVE_FAIL;

	// ������ ũ�� ���ϱ�
	HTbyte byItemSizeX = 1, byItemSizeZ = 1;
	HTPoint ptSize;
	// PC �κ��丮�� ��� Ȱ��ȭ�Ǿ��ִ� ũ�� ���ϱ�
	if( sSetItem.nLocation == ITEM_LOCATION_PC )
	{
		// BAG2�� ����� �� ���� ���
		if( sSetItem.nInventory == ITEM_LOCATION_PC_BAG2 
						&& g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_FALSE )
			return HT_RESULT_ITEM_MOVE_FAIL;

		ptSize.x = g_cEquipInventory->HT_byGetInventorySize(sSetItem.nInventory);
		ptSize.y = _INVEN_HEIGHT;
	}
	else 
	{
        ptSize = g_cItemControl->HT_ptItemControl_LoctionSize( sSetItem.nLocation );
	}
	
	//	�������� �̵��Ҽ� �ִ� ���� �̻��̸� �Ұ�
	if( sSetItem.pCellPos.x+byItemSizeX > ptSize.x || sSetItem.pCellPos.y+byItemSizeZ > ptSize.y )
	{
		return HT_RESULT_ITEM_MOVE_FAIL;
	}

	// ������ �����۰� ��ġ���� �ľ�
	HT_NODE* t;
	t = m_sHead->next;

	//	4_1. ������ ��带 �˻�
	while( t != m_sTail )
	{
		//	4_2. �������� ���� �ִ� ��� �κ��丮�� �������� ��
		if( sSetItem.nLocation == t->cItem.m_iItemLocation && sSetItem.nInventory == t->cItem.m_iItemInInventory )
		{
			//	4_3. �κ��丮�� ũ��(x,y)�� ���� �˻�
			for( HTint x=sSetItem.pCellPos.x ; x<sSetItem.pCellPos.x+byItemSizeX ; ++x )
			{
				for( HTint y=sSetItem.pCellPos.y ; y<sSetItem.pCellPos.y+byItemSizeZ ; ++y )
				{
					//	4_4. �������� ũ��� �� �ؼ� ��ĭ�� ã�Ƴ�
					// �˻��ϴ� ��ġ�� �������� �ִ��� �������� �˻��ϰ�, ���� ��� ��ŷ ������ ���������� �ƴ��� �˻��Ѵ�.
					if( x>=t->cItem.m_byInventory_CellPosX && x<t->cItem.m_byInventory_CellPosX+t->cItem.m_byItemSizeX 
					 && y>=t->cItem.m_byInventory_CellPosY && y<t->cItem.m_byInventory_CellPosY+t->cItem.m_byItemSizeY )
					{
						// ��ø������ �������̸�
						HTbyte byteMaxCount = 0;
						if( g_pParamMgr->HT_bGetItemMaxCount(dwItemIndex, &byteMaxCount) == false )
							return HT_RESULT_ITEM_MOVE_FAIL;

						if( t->cItem.m_dwItemKeyID != dwKeyID && (dwItemIndex == t->cItem.m_sItemInfo.snIndex) && (byteMaxCount > 1) )
						{	//	4_5. �ִ� ��ø�������� ������
							if( t->cItem.m_sItemInfo.byCount < byteMaxCount )
								return t->cItem.m_dwItemKeyID;
							//	4_6. �̵�(����)�Ұ� ����
							else
                                return HT_RESULT_ITEM_MOVE_FAIL;
						}
						// ��ø �Ұ����� �ٸ� �������� ���� ���
						else if( t->cItem.m_dwItemKeyID == dwKeyID )	// �ڱ� �ڽ��� ���
						{
							//continue;
							//return HT_RESULT_ITEM_MOVE_OK;
							return HT_RESULT_ITEM_MOVE_FAIL;	//	4_6. �̵�(����)�Ұ� ����
						}
						else
							return HT_RESULT_ITEM_MOVE_FAIL;	//	4_6. �̵�(����)�Ұ� ����
					}
				}
			}
		}
		t = t->next;
	}

	//	5. �ɸ��� ������ ������ ���� ����
	return HT_RESULT_ITEM_MOVE_OK;
}

//---------- �κ��丮�� ������� ���� �˻� ----------//
HTint CHTItemSystem::HT_iItemAlSetPosInventoryBlankCheck()
{
	HTint iBlankNumber = 0;		// �κ��丮 ���� ����

	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	// ����� ���� ���
	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == ITEM_LOCATION_PC) // ���� �κ��丮 �����ΰ�?
			if( s->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG1 || 
				s->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG2 && g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_TRUE )
				iBlankNumber++;
	}

	HTint MaxBlank;	// �ִ���� ���
	if( g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_TRUE )
     {
		 MaxBlank = g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) * _INVEN_HEIGHT +
			 g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG1) * _INVEN_HEIGHT;
	 }
	else
		 MaxBlank = g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) * _INVEN_HEIGHT;


	// ����� ��ȯ
	return (MaxBlank - iBlankNumber);
}

//---------- �κ��丮�� ������� ���� �˻� ----------//
HTint CHTItemSystem::HT_iItemAlSetPosGoodsKeepBlankCheck()
{
	HTint iBlankNumber = 0;		// �κ��丮 ���� ����

	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	// ����� ���� ���
	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == ITEM_LOCATION_NPC) // â�� �κ��丮 �����ΰ�?
			if( s->cItem.m_iItemInInventory == ITEM_LOCATION_NPC_ITEMSAVED )
				iBlankNumber++;
	}

	HTint MaxBlank;	// �ִ���� ���
	MaxBlank = _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT;


	// ����� ��ȯ
	return (MaxBlank - iBlankNumber);
}

//---------- ������ ������ �������� �˾Ƴ���. : HT_FALSE - ���� �Ұ��� HT_TRUE - ���밡��----//
HTbool CHTItemSystem::HT_bItemSystem_GetPossible(DWORD dwItemKeyID, HTbool bLevelCheck )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		// ������ �ɼǿ� ���� ��ũ�� ������ �������� �������� ��� �ɼ� �����Ŀ��� �������� ����� 
		// ���°� �ֱ� ������ �ٽ� �˻��ؼ� ����.
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
			return t->cItem.HT_bItemAl_PossibleCheck( t->cItem.m_sItemInfo.snIndex, bLevelCheck );

		t = t->next;
	}

	return HT_FALSE;
} 

//---------- �ش� Index�� �������� ���� �κ��丮�� �ش� ĭ�� �󸶳� ���� �ϴ��� ���� ��ȯ
HTint CHTItemSystem::HT_bItemSystem_GetPossible2(DWORD dwIndex, HTint iPos )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_sItemInfo.snIndex == dwIndex )	// ���� ������ �������� �߰��ߴٸ� �ش� ��ġ�� �´��� ����
			if (t->cItem.m_iItemLocation == ITEM_LOCATION_PC )
				if( t->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG1 || t->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG2 && g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_TRUE )
				{
					int index = (t->cItem.m_byInventory_CellPosX * _INVEN_HEIGHT + t->cItem.m_byInventory_CellPosY ) + ( t->cItem.m_iItemInInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
					if (index == iPos)
						 return t->cItem.m_sItemInfo.byCount;
				}

		t = t->next;
	}

	return 0;
} 

HTbool CHTItemSystem::HT_bItemSystem_GetPossibleOnEquip(DWORD dwItemKeyID, HTint nLocation)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			// ����
			if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_TWO_HAND && 
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_HAND || nLocation == ITEM_LOCATION_EQUIP_LEFT_HAND ) )
				return HT_TRUE;
			// �Ͱ���
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_EAR &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_EAR || nLocation == ITEM_LOCATION_EQUIP_LEFT_EAR) )
				return HT_TRUE;
			// ����
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_BRACELET &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_BRACELET || nLocation == ITEM_LOCATION_EQUIP_LEFT_BRACELET) )
				return HT_TRUE;
			// ����
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_RING &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_RING || nLocation == ITEM_LOCATION_EQUIP_LEFT_RING) )
				return HT_TRUE;
			// �κ��丮 Ȯ��� ������
			//else if(CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( t->cItem.m_sItemInfo.snIndex ) && nLocation == ITEM_LOCATION_EQUIP_BAG )	
			//	return HT_TRUE;

			else if( t->cItem.m_byItemEquipPos == nLocation )	
				return HT_TRUE;

			else
				return HT_FALSE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//----------�κ��丮���� ������ �����ϱ�----------//
HTvoid CHTItemSystem::HT_vItemSystem_SettingInventoryPos( HTint iItemKeyID, HT_ITEMSETTING_FLAG flag, HTbool bDrawTwinImage)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == iItemKeyID )
		{
			//	������ ����
            t->cItem.HT_vItemAlSettingInventoryPos( flag , bDrawTwinImage);
			break;
		}

		t = t->next;
	}
}

//---------- �κ��丮�� �ִ� �������� ���밡��/�Ұ��� �� ���� -------------//
HTvoid CHTItemSystem::HT_vItemSystem_RenewalPossibleBar(HTint nDlgNo)
{
	// ���밡��/�Ұ��ɹٸ� ������ �����۵��� PC/NPC�κ��丮�� �ִ� �͵� ���̴�.
	if( nDlgNo != _DIALOG_INVEN && nDlgNo != _DIALOG_GOODSKEEPWND )
		return;

	HT_NODE* t;
	t = m_sHead->next;

	HTbool bPossible = HT_TRUE;
	while( t != m_sTail )
	{
		if( t->cItem.m_iItemDlgNo == nDlgNo )// && t->cItem.m_bPossible == HT_FALSE)
		{
			bPossible = t->cItem.HT_bItemAl_PossibleCheck( t->cItem.m_sItemInfo.snIndex, HT_TRUE );
			if( t->cItem.m_bPossible != bPossible )	// ������ ��쿡�� ����
			{
				t->cItem.m_bPossible = bPossible;
			}
		}
		t = t->next;
	}
}	

//----------�������� �� �Ƶ� ���´�.---------//
HTint CHTItemSystem::HT_iSystem_GetItemModelID( DWORD dKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dKeyID )
		{
			return t->cItem.m_iItem3DID;
		}
		t = t->next;
	}

	return -1;
}

//  ������ ������ ���
HTbool CHTItemSystem::HT_bItemSystem_GetItemInfo( DWORD dwItemKeyID, STRUCT_ITEM& sItem )
{
	HT_NODE* t;

	t = m_sHead->next;
	while( t != m_sTail )
	{
		//-----ĳ���Ϳ� ������ ����ġ ��-----//
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			sItem.snIndex = t->cItem.m_sItemInfo.snIndex;
			sItem.snDurability = t->cItem.m_sItemInfo.snDurability;
			sItem.wSerial = t->cItem.m_sItemInfo.wSerial;
			sItem.snDummy = t->cItem.m_sItemInfo.snDummy;	
				  
			sItem.byCount = t->cItem.m_sItemInfo.byCount;
			for( HTint i = 0 ; i < MAX_SUBMATERIALSIZE ; ++i )
				sItem.bySubRefine[i] =  t->cItem.m_sItemInfo.bySubRefine[i];
			sItem.byDummy = t->cItem.m_sItemInfo.byDummy;
			sItem.byRefineLevel = t->cItem.m_sItemInfo.byRefineLevel;

			return HT_TRUE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//---------- ������ �������� Ű���̵� ���´�.----------//
DWORD CHTItemSystem::HT_dwSystem_GetItemEquipKeyID( HTint byPart )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_EQUIP )
		{
			if( t->cItem.m_iItemInInventory == byPart )
			{
				return t->cItem.m_dwItemKeyID;
			}
		}
		t = t->next;
	}

	return 0;
}

//----------�������� �� ���̵�κ��� Ű���̵� ���´�.----------//
DWORD CHTItemSystem::HT_dwSystem_GetItemKeyFromModelID( HTint nItemModelID, HTbool bPickCheck )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItem3DID == nItemModelID )
		{
			//	������ �������� ����Ʈ ó��
			if( bPickCheck )
			{
				if( m_iItemTargettingEffectID == 0 )
					g_pEngineHandler->HT_hrStartSFX( &m_iItemTargettingEffectID, HT_FX_ITEMTARGETTING, t->cItem.m_iItem3DID, HT_TRUE );
			}
			return t->cItem.m_dwItemKeyID;
		}
		t = t->next;
	}
	return 0;
}

//----------�������� �κ��丮 ��ġ�� KeyID�� ���´�------------//
DWORD CHTItemSystem::HT_dwItemSystem_GetItemKeyIDFromInvenLocation( HTint iCellNo )
{
	HT_NODE *t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_PC || 
			t->cItem.m_iItemLocation == ITEM_LOCATION_EQUIP )
		{
			if( t->cItem.m_iCellNumber == iCellNo )
				return t->cItem.m_dwItemKeyID;
		}
		t = t->next;
	}
	return -1;
}

//----------������ �ִ� �������� KeyID�� ���´�.---------//
DWORD CHTItemSystem::HT_dwItemSystem_GetKeyIDOnCell( HTPoint pt )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_byInventory_CellPosX==pt.x && t->cItem.m_byInventory_CellPosY==pt.y )
		{
			return t->cItem.m_dwItemKeyID;
		}
		t = t->next;
	}

	return -1;
}

//----------�����۰� ���콺 �����͸� �˻��Ͽ� ������ �ε����� ����---------//
HTint CHTItemSystem::HT_iSystem_ItemFind( HTint iLocation, HTint CellPosX, HTint CellPosY )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == iLocation )
		{
			if( CellPosX >= t->cItem.m_byInventory_CellPosX && CellPosX < t->cItem.m_byInventory_CellPosX + t->cItem.m_byItemSizeX &&
				CellPosY >= t->cItem.m_byInventory_CellPosY && CellPosY < t->cItem.m_byInventory_CellPosY + t->cItem.m_byItemSizeY )
			{
				return t->cItem.m_dwItemKeyID;
			}
		}
		t = t->next;
	}

	return RETURNTYPE_MAINGAME_FAILD;
}

//----------������ �����ǰ� �κ��丮 ����ǥ�� ����Ͽ� ������ ã��---------//
DWORD CHTItemSystem::HT_dwItemSystem_ItemSerch( HT_ItemReturnRoom sLocRoom )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == sLocRoom.nLocation && t->cItem.m_iItemInInventory == sLocRoom.nInventory )
		{
			if( sLocRoom.nCellPosx >= t->cItem.m_byInventory_CellPosX && sLocRoom.nCellPosx < t->cItem.m_byInventory_CellPosX + t->cItem.m_byItemSizeX &&
				sLocRoom.nCellPosy >= t->cItem.m_byInventory_CellPosY && sLocRoom.nCellPosy < t->cItem.m_byInventory_CellPosY + t->cItem.m_byItemSizeY )
			{
				return t->cItem.m_dwItemKeyID;
			}
		}
		t = t->next;
	}

	return RETURNTYPE_MAINGAME_FAILD;
}
// ������ �����ǰ� �κ��丮 ����ǥ�� ����Ͽ� ������ KeyIDã�� 
DWORD CHTItemSystem::HT_dwItemSystem_ItemSerch( HTint iLocation, HTint iInventory, HTint iSlotNo )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == iLocation && t->cItem.m_iItemInInventory == iInventory )
		{
			if( t->cItem.m_iCellNumber == iSlotNo )
			{
				return t->cItem.m_dwItemKeyID;
			}
		}
		t = t->next;
	}

	return 0;
}

//----------�ε����� PC�κ��丮�� ���� ó�� �˻��Ǵ� �������� KeyID�� ���´�.-----------//
DWORD CHTItemSystem::HT_dwItemSystem_GetKeyIDInPCInventoryForIndex( HTint iIndex )
{
	HT_NODE* t;
	t = m_sHead->next;
	
	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_PC )
		{
			if( t->cItem.m_sItemInfo.snIndex == iIndex )
                return t->cItem.m_dwItemKeyID;
		}
		t = t->next;
	}

	return 0;
}

//--------- Ư�� ��ġ(iLocation)�� �ڽ��� ������ ���� ������ ������ KeyID, ��ġ ��ȯ---------//
HTvoid CHTItemSystem::HT_vItemSystem_GetItemPos( DWORD dwItemIndex, DWORD dwActiveItemKeyID, HTint iLocation, DWORD& dwItemKeyID, HT_ITEMSETTING_FLAG& sLocRoom )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{	// ���� ��ҿ��� �ڽ��� ������ ���� ������ �������ΰ�
		if( t->cItem.m_dwItemKeyID != dwActiveItemKeyID 
			&& t->cItem.m_sItemInfo.snIndex == dwItemIndex && t->cItem.m_iItemLocation == iLocation )
		{
			dwItemKeyID = t->cItem.m_dwItemKeyID;
			sLocRoom.nLocation = t->cItem.m_iItemLocation;
			sLocRoom.nInventory = t->cItem.m_iItemInInventory;
			sLocRoom.pCellPos.x = t->cItem.m_byInventory_CellPosX;
			sLocRoom.pCellPos.y = t->cItem.m_byInventory_CellPosY;
			
			return;
		}
		t = t->next;
	}
}

//----------���콺 ����Ʈ�� �Ѱܹ޾� Ȱ��ȭ�� �������߿� ����Ʈ ��ġ�� �ִ°��� Ű�Ƶ� ��ȯ----------//
DWORD CHTItemSystem::HT_dwItemSystem_MousePtToItemPosCheck( HTPoint pPt )
{
	/*
	HTint iScreenStartX;
	HTint iScreenStartY;
	HTint iScreenEndX;
	HTint iScreenEndY;

	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_bItem2D_Show == HT_TRUE )
		{
//			if(g_cInterfaceCheck->HT_iGetCursor() != CURSOR_HAND)	//�ո�� => ���� üũ �ķ� ���� 2003.1.14
//				g_cInterfaceCheck->HT_vSetCursor(CURSOR_HAND);

			if(t->cItem.m_bItemActive == HT_TRUE)
				return -1;	// ���� �������� �̵� ���̶�� ����â�� ǥ�� ���� �ʴ´�.

			iScreenStartX = (HTint) t->cItem.m_bItemUIPositon.x;
			iScreenStartY = (HTint) t->cItem.m_bItemUIPositon.y;
			iScreenEndX = (HTint) t->cItem.m_bItemUIPositon.x + ( t->cItem.m_byItemSizeX*INVENTORY_SELLSIZE_X );
			iScreenEndY = (HTint) t->cItem.m_bItemUIPositon.y + ( t->cItem.m_byItemSizeY*INVENTORY_SELLSIZE_X );

			if( pPt.x >= iScreenStartX && pPt.x <= iScreenEndX && 
				pPt.y >= iScreenStartY && pPt.y <= iScreenEndY )
			{
				return t->cItem.m_dwItemKeyID;
			}
		}

		t = t->next;
	}
	*/
	
	return -1;
}

//---------------- �������� KeyID�� Index�� type, ũ�⸦ ��ȯ -----------------------//
HTint CHTItemSystem::HT_iGetItemInfoForEquip(DWORD dwKeyID, DWORD& dwItemIndex, HTint& iItemType, HTPoint& iItemSize)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			dwItemIndex = t->cItem.m_sItemInfo.snIndex;
			iItemType = t->cItem.m_sItemType;
			iItemSize.x = t->cItem.m_byItemSizeX;
			iItemSize.y = t->cItem.m_byItemSizeY;

			return HT_TRUE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//----------�������� Ű�̵�� �ε����� ���´�----------//
DWORD CHTItemSystem::HT_dwSystem_GetItemIndex( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			return t->cItem.m_sItemInfo.snIndex;
		}
		t = t->next;
	}

	return 0;
}

//---------- ������ �̸� ȹ��----//
CHTString CHTItemSystem::HT_strItemSystem_GetItemName(DWORD dwItemKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
			return t->cItem.m_strItemName;

		t = t->next;
	}

	return _T("");
}

//--------������ Ÿ�� ���´�----------------//
HTshort CHTItemSystem::HT_sItemSystem_GetItemType( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			return t->cItem.m_sItemType;
		}
		t = t->next;
	}

	return -1;
}

// ������ KeyID�� ���� ��ġ �˾ƿ���
HTbool CHTItemSystem::HT_bItemSystem_GetItemPos( DWORD dwKeyID, HT_ITEMSETTING_FLAG& sLocRoom )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			sLocRoom.nLocation = t->cItem.m_iItemLocation;
			sLocRoom.nInventory = t->cItem.m_iItemInInventory;
			sLocRoom.pCellPos.x = t->cItem.m_byInventory_CellPosX;
			sLocRoom.pCellPos.y = t->cItem.m_byInventory_CellPosY;

			return HT_TRUE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//----------�������� �κ��丮 �� ��ġ�� ��ȯ.----------//
HTPoint CHTItemSystem::HT_ptItemSystem_GetInventoryPos( DWORD dwItemKeyID )
{
	HTPoint pPt;
	pPt.x = pPt.y = -1;

	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			pPt.x = t->cItem.m_byInventory_CellPosX;
			pPt.y = t->cItem.m_byInventory_CellPosY;
			break;
		}
		t = t->next;
	}

	return pPt;
}

//----------��ø �������� �ִ��� �Ǵ�---------//
HTPoint CHTItemSystem::HT_ptItemSystem_GetOverlapItem( DWORD dwItem )
{
	HTPoint pPt;
	pPt.x = 100; pPt.y = 100;

	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_sItemInfo.snIndex == dwItem )
		{
			pPt.x = t->cItem.m_byInventory_CellPosX;
			pPt.y = t->cItem.m_byInventory_CellPosY;
			return pPt;
		}
		t = t->next;
	}

	return pPt;
}

//----------��ø ������ ����---------//
HTbool CHTItemSystem::HT_bItemSystem_SetOverlapItem_Add( DWORD dwItemKeyID , HTbyte byCount )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID)
		{
			t->cItem.m_sItemInfo.byCount += byCount;
			return HT_TRUE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//----------��ø ������ ����---------//
HTbool CHTItemSystem::HT_bItemSystem_SetOverlapItem_Minus( DWORD dwItemKeyID , HTbyte byCount )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			t->cItem.m_sItemInfo.byCount -= byCount;
			return HT_TRUE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//----------�������� Ű�̵�� �������� �ټ��� ���´�----------//
HTint CHTItemSystem::HT_iItemSystem_GetItemCount( DWORD dwItemKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			return t->cItem.m_sItemInfo.byCount;
		}
		t = t->next;
	}

	return -1;
}

//----------�������� Ű�̵�� �������� �ִ� ��ø ������ ���´�----------//
WORD CHTItemSystem::HT_wItemSystem_GetItemMaxPackCount( DWORD dwItemKeyID )
{
	HTint dwItemIndex = this->HT_dwSystem_GetItemIndex(dwItemKeyID);
	if(dwItemIndex == 0)
		return -1;

	HTbyte byteMaxCount = 0;
	if( g_pParamMgr->HT_bGetItemMaxCount(dwItemIndex, &byteMaxCount) == false )
		return -1;

	return byteMaxCount;
}

//----------�κ��丮 �ȿ��ִ� Ư�� ������(Index)�� �� ������ ���´�----------//
HTint CHTItemSystem::HT_iItemSystem_GetItemCountOnPcInven( DWORD dwItemIndex )
{
	HT_NODE* t;
	t = m_sHead->next;

	HTint nCount = 0;
	while( t != m_sTail )
	{
		if( t->cItem.m_sItemInfo.snIndex == dwItemIndex && t->cItem.m_iItemLocation == ITEM_LOCATION_PC )
		{
			nCount += t->cItem.m_sItemInfo.byCount;
		}
		t = t->next;
	}

	return nCount;
}

//----------��ø �������� �ټ��� �������ش�----------//
HTvoid CHTItemSystem::HT_vItemSystem_SetOverlapItemCount( DWORD dwItemKeyID, HTbyte byItemCount )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			t->cItem.m_sItemInfo.byCount = byItemCount;
			return;
		}
		t = t->next;
	}
}


//----------�������� ����� ��ȯ.----------//
HTPoint CHTItemSystem::HT_ptItemSystem_GetSize( DWORD dwKeyID )
{
	HTPoint pPt;
	pPt.x = 100;	pPt.y = 100;
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			pPt.x = t->cItem.m_byItemSizeX;
			pPt.y = t->cItem.m_byItemSizeY;
			return pPt;
		}
		t = t->next;
	}

	return pPt;
}

//----------�������� �� ��ȣ�� ��ȯ.----------//
HTint CHTItemSystem::HT_iItemSystem_GetCellNumber( DWORD dwItemKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			return t->cItem.m_iCellNumber;
		}
		t = t->next;
	}

	return 0;
}
 
//-------�������� ���� �����ϰų� ����--------//
HTvoid CHTItemSystem::HT_vItemSystem_ItemSet( PS_SCP_RESP_ITEM_SET info )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0;
	HT_NODE *s = NULL;
	if( info->sitem.snIndex > 0 ) 
	{
		// KeyID ����
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);

		switch( info->byPlace )
		{
			case ITEM_PLACE_INVEN :
			{
				// (������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					byBagID = (HTbyte)( info->byIndex / ( _INVEN_WIDTH * _INVEN_HEIGHT ) );
					byX = ( info->byIndex - (byBagID * _INVEN_WIDTH * _INVEN_HEIGHT) ) / _INVEN_HEIGHT; 
					byZ = ( info->byIndex - (byBagID * _INVEN_WIDTH * _INVEN_HEIGHT) ) % _INVEN_HEIGHT;
					s->cItem.HT_vItemCreate( ITEM_LOCATION_PC, byX, byZ, iKeyID, info->sitem, byBagID );
				}
			}
				break;
			case ITEM_PLACE_EQUIP :
			{
				//(������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					s->cItem.HT_vItemCreate( info->byIndex, iKeyID, info->sitem );
				}
			}
				break;
			case ITEM_PLACE_CARGO :
			{
				//(������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					//byBagID = (HTbyte)( info->byIndex / ( _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT ) );
					byX = ( info->byIndex - (byBagID * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT) ) % _GOODSKEEP_INVEN_WIDTH; 
					byZ = ( info->byIndex - (byBagID * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT) ) / _GOODSKEEP_INVEN_WIDTH;
					s->cItem.HT_vItemCreate( ITEM_LOCATION_NPC, byX, byZ, iKeyID, info->sitem );
				}
			}
				break;
			case ITEM_PLACE_OTHERTRADE:
			{
				// (������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					byX = ( info->byIndex - ( byBagID * _TRADE_INVEN_WIDTH * _TRADE_INVEN_HEIGHT ) ) % _TRADE_INVEN_WIDTH; 
					byZ = ( info->byIndex - ( byBagID * _TRADE_INVEN_WIDTH * _TRADE_INVEN_HEIGHT ) ) / _TRADE_INVEN_WIDTH;
					s->cItem.HT_vItemCreate( ITEM_LOCATION_EXCHANGE, byX, byZ, iKeyID, info->sitem );
				}
			}
				break;
			case ITEM_PLACE_STORE:
			{
				// (������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					byX = ( info->byIndex - ( byBagID * _STORE_WIDTH * _STORE_HEIGHT) ) % _STORE_WIDTH; 
					byZ = ( info->byIndex - ( byBagID * _STORE_WIDTH * _STORE_HEIGHT) ) / _STORE_WIDTH;
					s->cItem.HT_vItemCreate( ITEM_LOCATION_STORE, byX, byZ, iKeyID, info->sitem );
				}
			}
				break;
			case ITEM_PLACE_RENTALSTORE:
			{
				// (������) ������ ����
				HT_LL_vInsertAfter_ItemDelete( iKeyID );
				if( info->byType == SET_ITEM_CREATE )
				{
					s = new HT_NODE;
					byX = ( info->byIndex - ( byBagID * _RENTALSTORE_INVEN_WIDTH * _RENTALSTORE_INVEN_HEIGHT) ) % _RENTALSTORE_INVEN_WIDTH; 
					byZ = ( info->byIndex - ( byBagID * _RENTALSTORE_INVEN_WIDTH * _RENTALSTORE_INVEN_HEIGHT) ) / _RENTALSTORE_INVEN_WIDTH;
					s->cItem.HT_vItemCreate( ITEM_LOCATION_RENTALSTORE, byX, byZ, iKeyID, info->sitem );
				}
			}
				break;
			default : return;
		}
		// ������ ������ ����
		if( info->byType == SET_ITEM_CREATE )
		{
			s->next = m_sHead->next;
			m_sHead->next = s;
		}
		// ������� ���� 
		HT_bItemSystem_SetSubRefineItem( iKeyID, info->sitem.bySubRefine );
	}
}
//	�ƽ��� â�� �ƽ��� ����
HTvoid CHTItemSystem::HT_vItemSystem_CreateAshramCargo( HTbyte byPlace, HTshort snIndex, STRUCT_ITEM oItem )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0;
	HT_NODE *s = NULL;

	// KeyID ����
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), byPlace, snIndex, iKeyID);
	//(������) ������ ����
	HT_LL_vInsertAfter_ItemDelete( iKeyID );

	s = new HT_NODE;
	byX = ( snIndex ) % _GOODSKEEP_INVEN_WIDTH; 
	byZ = ( snIndex ) / _GOODSKEEP_INVEN_WIDTH;
	s->cItem.HT_vItemCreate( ITEM_LOCATION_ASHRAMCARGO, byX, byZ, iKeyID, oItem );

	s->next = m_sHead->next;
	m_sHead->next = s;

	// ������� ���� 
	this->HT_bItemSystem_SetSubRefineItem( iKeyID, oItem.bySubRefine );
}
//-------------- PC�κ��丮�� ������ ���� ------------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateInven( STRUCT_ITEM arrInven[MAX_INVEN] )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0, iItemIndex = 0;

	HTint iInvenNo;
	time_t timeTime;
	if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Inven, timeTime ) == HT_FALSE )		iInvenNo = 24;
	else																						iInvenNo = 48;

	for( int i = 0 ; i < iInvenNo ; ++i )//MAX_INVEN
	{
		if( arrInven[i].snIndex > 0 )
		{
			// �������� index�� ���� index�� �����Ѵ�
			//iItemIndex = HT_ITEM_INDEX_START + arrInven[i].snIndex;
			// KeyID ����
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, i, iKeyID);
			//������ ������ ����
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			byBagID = (HTbyte)( i / ( _INVEN_WIDTH * _INVEN_HEIGHT ) );
			byX = ( i - (byBagID * _INVEN_WIDTH * _INVEN_HEIGHT) ) / _INVEN_HEIGHT;
			byZ = ( i - (byBagID * _INVEN_WIDTH * _INVEN_HEIGHT) ) % _INVEN_HEIGHT; 
			
			s->cItem.HT_vItemCreate( ITEM_LOCATION_PC, byX, byZ, iKeyID, arrInven[i], byBagID );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// ������� ���� 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrInven[i].bySubRefine );
		}
	}
}
//------------- ���� ������ ���� -----------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateEquip( STRUCT_ITEM arrEquip[MAX_EQUIP] )
{
	HTint iKeyID = 0, iItemIndex = 0;
	HTbool bInitInven = HT_FALSE;
	HTint iSubRefineLevel = 0;

	for( int i = 0 ; i < MAX_EQUIP ; ++i )
	{
		if( arrEquip[i].snIndex > 0 )
		{
			// �������� index�� ���� index�� �����Ѵ�
			//iItemIndex = HT_ITEM_INDEX_START + arrEquip[i].snIndex;
			// KeyID ����
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, i, iKeyID);
			//������ ������ ����
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			s->cItem.HT_vItemCreate( i, iKeyID, arrEquip[i] );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// ������� ���� 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrEquip[i].bySubRefine );
			
			// ������ ���� ������ FX ����
			iItemIndex = arrEquip[i].snIndex + HT_ITEM_INDEX_START;
			if( CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex ) )
			{
				// ���� ������ �Ǿ� �ִ� (����) �������� FX ����
				if( arrEquip[i].byRefineLevel > 0 )
					g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																		iItemIndex, arrEquip[i].byRefineLevel );

				// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
				iSubRefineLevel = this->HT_iItemSystem_GetSubRefineLevel( iKeyID );
				if( iSubRefineLevel > 0 )
				{
					HTint iAttribute = this->HT_iItemSystem_GetAttributeSubRefineItem( iKeyID );
					// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
					g_pEngineHandler->HT_hrAttachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), iItemIndex,
																		(HTESubRefineType)iAttribute, iSubRefineLevel );
				}
			}

			//	���� �������� ��� �����Ÿ� �����ϱ�
			if( (arrEquip[i].snIndex+HT_PARAMTYPE_ITEM_START-1) == HT_INDEX_TOTEM_JACUNAEARANI )
			{
				int iRange = 0;
				g_pParamMgr->HT_bGetItemEffect1Param1( (arrEquip[i].snIndex+HT_PARAMTYPE_ITEM_START-1), &iRange );
				g_cMainCharacter->HT_vMainChar_SetTotemItemRange( iRange );
			}

			// �κ��丮 ������ �ʱ�ȭ
			//if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( iItemIndex ) )
			//{
			//	g_cEquipInventory->HT_vInitBagStatus( arrEquip[i].snIndex );
			//	bInitInven = HT_TRUE;
			//}
		}
	}
	// �κ��丮 ������ �ʱ�ȭ ��������
	//if( bInitInven == HT_FALSE )	
	//	g_cEquipInventory->HT_vInitBagStatus( 0 );

	HT_vItemSystem_RenewalDurabilityWarning();
}
//----------â�� ������ ����----------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateNPCInven( STRUCT_ITEM arrNPCInven[MAX_CARGO] )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0, iItemIndex = 0;
	for( int i = 0 ; i < MAX_CARGO ; ++i )
	{
		if( arrNPCInven[i].snIndex > 0 )
		{
			// �������� index�� ���� index�� �����Ѵ�
			//iItemIndex = HT_ITEM_INDEX_START + arrNPCInven[i].snIndex;
			// KeyID ����
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_CARGO, i, iKeyID);
			//������ ������ ����
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			//byBagID = (HTbyte)( i / ( _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT ) );
			byX = ( i - (byBagID * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT) ) % _GOODSKEEP_INVEN_WIDTH; 
			byZ = ( i - (byBagID * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT) ) / _GOODSKEEP_INVEN_WIDTH;
			s->cItem.HT_vItemCreate( ITEM_LOCATION_NPC, byX, byZ, iKeyID, arrNPCInven[i]/*, byBagID*/ );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// ������� ���� 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrNPCInven[i].bySubRefine );
		}
	}
}
//	�ƽ��� â�� ����
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemDeleteAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo )
{
	HTint iKeyID = 0;
	for( int i = 0 ; i < MAX_CARGO ; ++i )
	{
		if( arrAshramCargo[i].snIndex > 0 )
		{
			// KeyID ����
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, i+(iCargoNo*120), iKeyID);
			//������ ������ ����
			HT_LL_vInsertAfter_ItemDelete( iKeyID );
		}
	}
}
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo )
{
	HTbyte byX = 0, byZ = 0;
	HTint iKeyID = 0;
	for( int i = 0 ; i < MAX_CARGO ; ++i )
	{
		if( arrAshramCargo[i].snIndex > 0 )
		{
			// KeyID ����
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, i+(iCargoNo*120), iKeyID);
			//������ ������ ����
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			byX = ( i+(iCargoNo*120) ) % _GOODSKEEP_INVEN_WIDTH; 
			byZ = ( i+(iCargoNo*120) ) / _GOODSKEEP_INVEN_WIDTH;
			s->cItem.HT_vItemCreate( ITEM_LOCATION_ASHRAMCARGO, byX, byZ, iKeyID, arrAshramCargo[i] );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// ������� ���� 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrAshramCargo[i].bySubRefine );
		}
	}
}

//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid CHTItemSystem::HT_LL_vInitList()
{
	m_sHead = NULL;
	m_sTail = NULL;

	m_sHead = new HT_NODE;
	m_sTail = new HT_NODE;

	m_sHead->next = m_sTail;
	m_sTail->next = m_sTail;
}

//----------LL ����Ÿ �����---------//
HTRESULT CHTItemSystem::HT_LL_hrDeleteNode( int iItemKeyID )
{
	HT_NODE *s;
	HT_NODE *p;

	p = m_sHead;
	s = p->next;
	while( s->cItem.m_dwItemKeyID != iItemKeyID && s != m_sTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else 
		return HT_FALSE;
}

//----------LL ����Ÿ ���� �����---------//
HT_NODE *CHTItemSystem::HT_LL_hrDeleteAll()
{
	HT_NODE *s;
	HT_NODE *t;
	
	t = m_sHead->next;
	while( t != m_sTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sHead->next = m_sTail;

	return m_sHead;
}


// ---------------------------------------------------------//
//	������ KeyID�� ������ ��� ����(STRUCT_ITEM) ���
// ---------------------------------------------------------//
STRUCT_ITEM CHTItemSystem::HT_iGetItemInfo(DWORD dwKeyID)
{
	CHTString strTemp;
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
			return t->cItem.m_sItemInfo;

		t = t->next;
	}

	STRUCT_ITEM temp;
	temp.snIndex = 0;
	return temp;
}

//------------------------------------------------------------------------------------//
// ���� - ������ ������ ��� �޼����� �����ϰ�, �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
//------------------------------------------------------------------------------------//
HTint CHTItemSystem::HT_iGetItemInfo(DWORD dwKeyID, HT_ITEMINFO& vInfo, BYTE bType)
{
	CHTString strTemp;
	HT_NODE* t;
	t = m_sHead->next;

	HTint winSizeX = 0;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			HT_ITEM_DATA* pData = HT_NULL;
			HT_ITEM_EXPANSION_DATA* pExtData = HT_NULL;
			CHTString str;
			
			// ������ ���� Lock ����
			if( g_pParamMgr->HT_bLockID(t->cItem.m_sItemInfo.snIndex) == false )
				return winSizeX;

			HTint iOut = 0;
			HTshort sOut = 0;

			// ������ �̸�
			vInfo.strName.str = t->cItem.m_strItemName;
			// ������ �������� ��츸 ���� ������ ǥ���Ѵ�.
			if( t->cItem.m_sItemInfo.byRefineLevel > 0)
			{
				str.HT_szFormat("+%d", t->cItem.m_sItemInfo.byRefineLevel);
				vInfo.strName.str += str;
			}
			winSizeX = vInfo.strName.str.HT_nGetSize();

			// ������ Ÿ��(Ư���� ���� �з�)
			// ����ũ������
			if( CHTParamIDCheck::HT_bIsItemUnique( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.58f, 0.35f, 0.99f, 1.0f);	// ����
			// ���������
			else if( CHTParamIDCheck::HT_bIsItemRare( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.82f, 0.71f, 0.44f, 1.0f);	// ���
			// ����Ʈ ������
			else if( CHTParamIDCheck::HT_bIsItemQuest( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.54f, 0.52f, 1.0f, 1.0f);	// ������
			//  �Ϲݾ�����
			else																			
				vInfo.strName.color = g_ColorTable[15];		// white

			// ������ ����
			g_pParamMgr->HT_bGetItemDescription( &vInfo.strDescription.str );
			switch (t->cItem.m_sItemInfo.snIndex)
			{
				case 7064:	// �����̾� �ٷ��� �����۵��� ���� ������ ���ش�.
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem15, &strTemp, _T("") );		//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� ������ ȿ��"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7065:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem16, &strTemp, _T("") );		//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. ��Ʈ�� ������ ȿ��"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7066:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem17, &strTemp, _T("") );		//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7067:
					{
						HT_g_Script_SetMessage( eMsgExPlanPremiumItem18, &strTemp, _T("") );		//	"��� ������ �ֹ��� 1��\n������ �ֹ��� 20��\n������ ������ 10��\n���� ��ɼ� 5��\n�̺�Ʈ�Ⱓ�� ���� �̺�Ʈ ������ ����\n\n30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��\n4. ��� ��ũ�� 15 ���"
						vInfo.strDescription.str.HT_szFormat(strTemp);
						
						pData = new HT_ITEM_DATA;
						pData->color = g_ColorTable[16]; 
						HT_g_Script_SetMessage( eMsgExPlanPremiumItem23, &strTemp, _T("") );
						pData->str = strTemp;

						vInfo.vSourceStr.push_back(pData);
					}
					break;
				case 7069:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem19, &strTemp, _T("") );		//	"������� 1��\n(�Ĺ̸��������� �������� ���� ��ȯ����)\n�����ġ 2��\n(������� �������� ����������)\n�������� ����� 2��\n(���������� �ٷ� ���尡��)\n�̺�Ʈ ��Ÿ�� �ϸ�Ÿ 250�� 2����\n��� ������ �ֹ��� 2��"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7073:	// ���̿���
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );		//	"6�� 5õ �÷� LCD / ��� �̾��� '���̿��� TMP-1000'>>http://www.ioneit.com"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7079:	//�ĸ���
					//HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );		//	"6�� 5õ �÷� LCD / ��� �̾��� '���̿��� TMP-1000'>>http://www.ioneit.com"
					vInfo.strDescription.str.HT_szFormat("COMRADE GeForce 6600 3.3ns�׷��� ī��>>>>300MHz RAM DAC>>128MB RAM SPEED 400MHz 3.3ns>>DVI-1 ��� ���÷��� ����>>�����Ⱓ: 2��>>>>��뷮 ���߿��� ���� ��, S-Video ���̺�, �ѱۼ���>>>>�� ����ũ�λ���>>http://www.microsound.co.kr>>���ǿ��� ��ϰ���");
					break;
				case 6555: // ��ī��
					vInfo.strDescription.str.HT_szFormat("- �ּ����� �������� ���Ѻ��� ����\n- ���ý� ������ �Ӽ��� �ʱ�ȭ�Ǹ�\n     ÷���� ��������� �Ӽ��� �ο�\n\n- ��� ����, ���� ÷�� ����");
					break;
			}

			if( vInfo.strDescription.str == HT_INFO_ITEM_DESCRIPT_NULL )
				vInfo.strDescription.str.HT_hrCleanUp();
			else
				vInfo.strDescription.color = g_ColorTable[16]; //light grey


			// �ٷ��� �������� ���� X����� �ִ��� ������.
			if(t->cItem.m_sItemInfo.snIndex >= 7064 && t->cItem.m_sItemInfo.snIndex <= 7067 || t->cItem.m_sItemInfo.snIndex == 7069 || t->cItem.m_sItemInfo.snIndex == 7073 || t->cItem.m_sItemInfo.snIndex == 7079 || t->cItem.m_sItemInfo.snIndex == 6555)
			//if(t->cItem.m_sItemInfo.snIndex >= 7064 && t->cItem.m_sItemInfo.snIndex <= 7067 || t->cItem.m_sItemInfo.snIndex == 7069 || t->cItem.m_sItemInfo.snIndex == 7079)
			{
				winSizeX = 40;
				vInfo.strName.color = g_ColorTable[17];		// white
				vInfo.strDescription.color = g_ColorTable[15]; //light grey

			}


			// ������ ��� ���ÿ� �����۰� �ּ����� �ʱ�ȭ �������� ǥ�� ���ϱ� ����. 
			if( bType == NPC_ITEM_REFINING && !CHTParamIDCheck::HT_bIsItemRefine( t->cItem.m_sItemInfo.snIndex )
				&& t->cItem.m_sItemInfo.snIndex != HT_INDEX_INIT_SUB_REFINE )	
			{
				HTint iRupiah; // ������ ����
				g_pParamMgr->HT_bGetItemRupiah( &iRupiah );

				// �ּ����� ����
				HTint iSubRefine = 0;
				/*for( HTint i = 0; i < t->cItem.m_iSubItemIndexCount ; ++i )
				{
					iSubRefine += t->cItem.m_iSubItemCount[i];
				}*/
				HTbyte bySubItemIndex = 0;
				for( HTint i = 0; i < MAX_SUBMATERIALSIZE ; ++i )
				{
					if( t->cItem.m_sItemInfo.bySubRefine[i] > 0 )
					{
						bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	����4��Ʈ ����
						if( bySubItemIndex > 0 )
							++iSubRefine;
						bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	����4��Ʈ ����
						if( bySubItemIndex > 0 )
							++iSubRefine;
					}
				}

				if( iRupiah <= 0  
					|| ( t->cItem.m_sItemInfo.byRefineLevel >= MAX_REFINE_MAIN_LEVEL && iSubRefine >= MAX_REFINE_SUB_LEVEL )
					|| !(CHTParamIDCheck::HT_bIsItemWeapon( t->cItem.m_sItemInfo.snIndex )		
							|| CHTParamIDCheck::HT_bIsItemDefence( t->cItem.m_sItemInfo.snIndex )		
							|| CHTParamIDCheck::HT_bIsItemAccessory( t->cItem.m_sItemInfo.snIndex )) ) 
				{
					pData = new HT_ITEM_DATA;
					pData->color = g_ColorTable[11]; //red
					// ���� �Ұ�
					HT_vItemSystem_SetMessage( eMsgItemInfoCannotRefine, &pData->str );

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				else
				{
					HTint iNeedRupiah = HT_iItemSystem_GetRupiahForItemWork( t->cItem.m_sItemInfo.byRefineLevel, iRupiah );
					// ��ȭ���� ���� Ƚ��
					HTint iMainRefine = MAX_REFINE_MAIN_LEVEL - t->cItem.m_sItemInfo.byRefineLevel;
					if( iMainRefine < 0 )	iMainRefine = 0;
					// �ּ����� ���� Ƚ��
					HTint iRemainSubRefine = MAX_REFINE_SUB_LEVEL - iSubRefine;
					if( iRemainSubRefine < 0 )	iRemainSubRefine = 0;

					if( iNeedRupiah > 0 )
					{
						//-------���Ǿ�--------//
						pData = new HT_ITEM_DATA;
						pData->color = g_ColorTable[17]; //yellow
						// %s ���Ǿ�, iNeedRupiah
						HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);
						
						CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // ��ǥ ó��
						pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
						vInfo.vSourceStr.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						//------��ȭ����-------//
						//pData = new HT_ITEM_DATA;
						//if( iMainRefine <= 0 )
						//{
						//	pData->color = g_ColorTable[11]; //red
						//	// ��ȭ���� �Ұ�
						//	HT_vItemSystem_SetMessage( eMsgItemInfoCannotMainRefine, &pData->str);
						//}
						//else
						//{
						//	pData->color = g_ColorTable[17];	// yellow
						//	// ��ȭ���� ���� Ƚ�� %dȸ
						//	HT_vItemSystem_SetMessage( eMsgItemInfoRemainMainRefine, &str);
						//	pData->str.HT_szFormat( str.HT_szGetString(), iMainRefine );
						//}
						//vInfo.vSourceStr.push_back(pData);
						//winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						////--------�ּ�����---------//
						//pData = new HT_ITEM_DATA;
						//if( iRemainSubRefine <= 0 )
						//{
						//	pData->color = g_ColorTable[11]; //red
						//	// �ּ����� �Ұ�
						//	HT_vItemSystem_SetMessage( eMsgItemInfoCannotSubRefine, &pData->str);
						//}
						//else
						//{
						//	pData->color = g_ColorTable[17];	// yellow
						//	// �ּ����� ���� Ƚ�� %dȸ
						//	HT_vItemSystem_SetMessage( eMsgItemInfoRemainSubRefine, &str);
						//	pData->str.HT_szFormat( str.HT_szGetString(), iRemainSubRefine );
						//}
						//vInfo.vSourceStr.push_back(pData);
						//winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
					else
					{
						pData = new HT_ITEM_DATA;
						pData->color = g_ColorTable[11]; //red
						// ���� �Ұ�
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotRefine, &pData->str );

						vInfo.vSourceStr.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			else if( bType == NPC_ITEM_SELL ) // ���� ������
			{
				//���Ǿ�
				HTint iRupiah = g_cIndividualStore->HT_iIndividualStore_GetRupiah( dwKeyID );
				if( iRupiah > 0 )	
				{
					pData = new HT_ITEM_DATA;
					// %s ���Ǿ�
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iRupiah ); // ��ǥ ó��
					pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
					if( iRupiah >= 10000000 )
						pData->color = g_ColorTable[11]; //red
					else if( 1000000 <= iRupiah && iRupiah < 10000000 )
						pData->color = g_ColorTable[12];	// yellow
					else if( 100000 <= iRupiah && iRupiah < 1000000 )
						pData->color = g_ColorTable[7 ];	// ��Ȳ
					else if( 10000 <= iRupiah && iRupiah < 100000 )
						pData->color = g_ColorTable[17];	// �����
					else
						pData->color = g_ColorTable[15];		// white

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
			}
			else if(bType == NPC_ITEM_RENTAL_SELL && g_cRentalStore->m_nWindowType != 2)	// ��Ź�Ǹſ�
			{
				//���Ǿ�
				int Xid = g_cObjectInfo->nControlIndex-_RENTALSTORE_INVEN_BEGIN;
				HTint iRupiah = g_cRentalStore->ItemList[Xid].dwPrice;
				if( iRupiah > 0 )	
				{
					pData = new HT_ITEM_DATA;
					// %s ���Ǿ�
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iRupiah ); // ��ǥ ó��
					pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
					if( iRupiah >= 10000000 )
						pData->color = g_ColorTable[11]; //red
					else if( 1000000 <= iRupiah && iRupiah < 10000000 )
						pData->color = g_ColorTable[12];	// yellow
					else if( 100000 <= iRupiah && iRupiah < 1000000 )
						pData->color = g_ColorTable[7 ];	// ��Ȳ
					else if( 10000 <= iRupiah && iRupiah < 100000 )
						pData->color = g_ColorTable[17];	// �����
					else
						pData->color = g_ColorTable[15];		// white

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());

					//HTint iHour, iMinute;

					// ���� �Ⱓ ǥ��
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					pExtData->basic.color = g_ColorTable[17]; //yellow

					time_t totaltime;
					CHTString vstr;
					totaltime = g_cRentalStore->ItemList[Xid].dwTime;
					tm* psTmTime = localtime( &totaltime );

					//g_cUIManager->HT_SetScriptMessage( eMsgCommonUntilAshramCargo, &str, _T(""), _T("") );	//	�����
					vstr.HT_szFormat("%d.%d.%d(%d:%02d) ����", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday, psTmTime->tm_hour, psTmTime->tm_min);
					pExtData->basic.str = vstr;//.HT_szFormat( vstr.HT_szGetString() );

					// ���� ��Ź������ ���� �ִٸ� � ������ ��Ź�ߴ����� �˷��ִ� ����~
					if (g_cRentalStore->m_nWindowType == 0)
					{
						CHTString gstr;
						int tindex = g_cRentalStore->m_wIndex[Xid];
						int iStoreIndex = (tindex / MAX_USERRENTALITEM);
						//int dwIndex = (tindex % MAX_USERRENTALITEM);

						gstr.HT_szFormat("��Ź��ġ:%d", iStoreIndex+1);
						pExtData->basic.str = vstr + _T(", ") + gstr;
					}
					/*
					iMinute = (g_cRentalStore->ItemList[Xid].dwTime - now ) / 60;
					iHour = (iMinute / 60);
					iMinute = (iMinute % 60);

					if (iHour != 0 && iMinute != 0 )
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoHourMinute, &str);	// ��ȿ�ð� %d�ð� %d��
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour , iMinute );
					}
					else if (iMinute != 0)
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoMinute, &str);	// ��ȿ�ð� %d��
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iMinute );
					}
					else
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoHour, &str);	// ��ȿ�ð� %d�ð�
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour );
					}
					*/
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
				}
			}

			// ��ø�� ����
			HTint iCount = 0;
			if( bType == NPC_ITEM_SELL && g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ))
				iCount = g_cIndividualStore->HT_iIndividualStore_GetPackCount( dwKeyID );
			else
				iCount = t->cItem.m_sItemInfo.byCount;

			// ���Ӿ��������� �˻�
			if (CHTParamIDCheck::HT_bIsItemChargeContinuance(t->cItem.m_sItemInfo.snIndex) == TRUE)
			{
				HTint iHour, iMinute;

				// ���� �Ⱓ ǥ��
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
				pExtData->basic.color = g_ColorTable[17]; //yellow

				iMinute = iCount;
				iHour = iMinute / 60;
				iMinute = iMinute % 60;

				if (iHour != 0 && iMinute != 0 )
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoHourMinute, &str);	// ��ȿ�ð� %d�ð� %d��
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour , iMinute );
				}
				else if (iMinute != 0)
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoMinute, &str);	// ��ȿ�ð� %d��
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iMinute );
				}
				else
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoHour, &str);	// ��ȿ�ð� %d�ð�
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour );
				}

				

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
			}
			else
			{
				if( iCount > 1 )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					pExtData->basic.color = g_ColorTable[16]; //light grey
					// ��ø���� %d
					HT_vItemSystem_SetMessage( eMsgItemInfoPackCount, &str);
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iCount );

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
				}
			}

			

			//-----�������ѻ���------//
			if( g_pParamMgr->HT_bGetItemLimitTrimuriti( &iOut ) == true && iOut > 0 )
			{
				HTRESULT trimuriti = HT_FALSE;
				str.HT_hrCleanUp();

				pData = new HT_ITEM_DATA;
				if( BIT_AND( TRIMURITI_BRAHMA, iOut ) )
				{
					//str = "����帶"; 
					HT_vItemSystem_SetMessage( eMsgCommonTrimuritiBrahma, &pData->str);
					trimuriti = HT_TRUE;
				}
				if( BIT_AND( TRIMURITI_VISHNU, iOut ) )
				{
					if(trimuriti) //str += ", �񽴴�";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiVishunu, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str = "�񽴴�";
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiVishunu, &pData->str);
					trimuriti = HT_TRUE;
				}
				if( BIT_AND( TRIMURITI_SIVA, iOut ) )
				{
					if(trimuriti) //str += ", �ù�";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiSiva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "�ù�";
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiSiva, &pData->str);
					trimuriti = HT_TRUE;
				}

				//str += " ����";
				HT_vItemSystem_SetMessage( eMsgItemInfoPrivateUse, &str);
				pData->str = pData->str + _T(" ") + str;

				if( BIT_AND( g_oMainCharacterInfo.byTrimuriti, iOut ) )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitTribe( &iOut ) == true && iOut > 0)		// ��������
			{
				HTRESULT tribe = HT_FALSE;
				str.HT_hrCleanUp();

				pData = new HT_ITEM_DATA;
				if( BIT_AND( TRIBE_NAGA, iOut ) )
				{
					//str = "����"; 
					HT_vItemSystem_SetMessage( eMsgCommonTribeNaga, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_ASURA, iOut ) )
				{
					if(tribe) //str += ", �Ƽ���";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeAsura, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str = "�Ƽ���";
						HT_vItemSystem_SetMessage( eMsgCommonTribeAsura, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_YAKSA, iOut ) )
				{
					if(tribe) //str += ", ��ũ��";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeYaksha, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "��ũ��";
						HT_vItemSystem_SetMessage( eMsgCommonTribeYaksha, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_DEVA, iOut ) )
				{
					if(tribe) //str += ", ����";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeDeva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonTribeDeva, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_KINNARA, iOut ) )
				{
					if(tribe) //str += ", Ų����";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeKimnara, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "Ų����";
						HT_vItemSystem_SetMessage( eMsgCommonTribeKimnara, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_RAKSHASA , iOut ) )
				{
					if(tribe) //str += ", ��ũ����";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeRakshasa, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "��ũ����";
						HT_vItemSystem_SetMessage( eMsgCommonTribeRakshasa, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_GANDHARVA, iOut ) )
				{
					if(tribe) //str += ", ���ٸ���";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeGandharva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "���ٸ���";
						HT_vItemSystem_SetMessage( eMsgCommonTribeGandharva, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_GARUDA, iOut ) )
				{
					if(tribe) //str += ", �����";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeGaruda, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "�����";
						HT_vItemSystem_SetMessage( eMsgCommonTribeGaruda, &pData->str);
					tribe = HT_TRUE;
				}
				
				//str += " ����";
				HT_vItemSystem_SetMessage( eMsgItemInfoPrivateUse, &str);
				pData->str = pData->str + _T(" ") + str;

				if( BIT_AND( g_cMainCharacter->HT_iMainChar_GetTribeServerCode(), iOut ) )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// ����
			HTbyte byLimitLevel = 0;
			if( g_pParamMgr->HT_bGetItemLimitLevel( &byLimitLevel ) == true && byLimitLevel > 0 )
			{
				pData = new HT_ITEM_DATA;

				// Level %d�ʿ�
				HT_vItemSystem_SetMessage( eMsgItemInfoNeedLevel, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), byLimitLevel );

				if( g_cStatus->HT_byGetLevel() >= byLimitLevel )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitMuscleChakra( &sOut ) == true && sOut > 0 )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("������ ��ũ�� %d", sOut);		// ������ ��ũ��
				HT_vItemSystem_SetMessage( eMsgItemInfoMuscleChakra, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), sOut );

				if( g_cStatus->HT_nGetPureChakraMuscle() >= sOut )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitNerveChakra( &sOut ) == true && sOut > 0 )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("�Ű��� ��ũ�� %d", sOut);		// �Ű��� ��ũ��
				HT_vItemSystem_SetMessage( eMsgItemInfoNerveChakra, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), sOut );

				if( g_cStatus->HT_nGetPureChakraNerve() >= sOut )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitHeartChakra( &sOut ) == true && sOut > 0 )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("������ ��ũ�� %d", sOut);		// ������ ��ũ��
				HT_vItemSystem_SetMessage( eMsgItemInfoHeartChakra, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), sOut );

				if( g_cStatus->HT_nGetPureChakraHeart() >= sOut )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitSoulChakra( &sOut ) == true && sOut > 0 )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("������ ��ũ�� %d", sOut);		// ������ ��ũ��
				HT_vItemSystem_SetMessage( eMsgItemInfoSoulChakra, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), sOut );

				if( g_cStatus->HT_nGetPureChakraSoul() >= sOut )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// ���ý� ������ ������ 
			if( CHTParamIDCheck::HT_bIsItemRefine( t->cItem.m_sItemInfo.snIndex ) 
								&& g_pParamMgr->HT_bGetItemRefinableItemType(&iOut) == true && iOut > 0 )
			{
				// ÷�� ���� ������ �з�(Bit Set)
				HTRESULT enable = HT_FALSE;
				HTint nCommaCount = 0;

				str.HT_hrCleanUp();
				HTRESULT type = HT_FALSE;

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
				// ����
				if( BIT_AND( _REFINE_WEPON_ONEHAND, iOut ) )
				{
					//str = "�Ѽչ���"; 
					HT_vItemSystem_SetMessage( eMsgCommonItemClassOneHand, &pExtData->basic.str);
					type = HT_TRUE;
				}
				if( BIT_AND( _REFINE_WEPON_TWOHAND , iOut ) )
				{
					if(type)
					{
						//str +=", �μչ���";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassTwoHand, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�μչ���";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassTwoHand, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				// ��
				if( BIT_AND( _REFINE_DEFENCE_ARMOR , iOut ) )// �Ǻ�
				{ 
					if(type)
					{
						//str +=", �Ǻ�";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassArmor, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�Ǻ�";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassArmor, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_PANTS , iOut ) )// ����
				{
					if(type)
					{
						//str +=", ����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassPants, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassPants, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_GLOVES , iOut ) )// �尩
				{
					if(type)
					{
						//str +=", �尩";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassGloves, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�尩";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassGloves, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_SHIELD, iOut ) )	// ����
				{
					if(type)
					{
						//str +=", ����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShield, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShield, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_BELT, iOut ) )	// �㸮��
				{
					if(type)
					{
						//str +=", �㸮��";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBelt, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�㸮��";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBelt, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_SHOES, iOut ) )	// �Ź�
				{
					if(type)
					{
						//str +=", �Ź�";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShoes, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�Ź�";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShoes, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_HELMET, iOut ) )	// ����
				{
					if(type)
					{
						//str +=", ����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassHelmet, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassHelmet, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				// �׼�����
				if( BIT_AND( _REFINE_ACCESSORY_EARRING, iOut ) )	
				{
					if(type)
					{
						//str +=", �Ͱ���";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassEarring, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�Ͱ���";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassEarring, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_NECKLACE, iOut ) )	
				{
					if(type)
					{
						//str +=", �����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassNecklace, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "�����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassNecklace, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_BRACELET, iOut ) )	
				{
					if(type)
					{
						//str +=", ����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBracelet, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBracelet, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_RING, iOut ) )	
				{
					if(type)
					{
						//str +=", ����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassRing, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "����";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassRing, &pExtData->basic.str);
					type = HT_TRUE;	
				}
					
				//str += "��";
				HT_vItemSystem_SetMessage( eMsgItemInfoUsable, &str);
				pExtData->basic.str = pExtData->basic.str + _T(" ") + str;
				pExtData->basic.color = g_ColorTable[16]; //light grey

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max( winSizeX, pExtData->basic.str.HT_nGetSize()-(HTint)((HTfloat)nCommaCount/2.0 +0.5) );
			}
			// ������
			if( g_pParamMgr->HT_bGetItemMaxDurability( &sOut ) == true )
			{
				if( sOut < HT_ITEM_INFINITY_DURABILITY && t->cItem.m_sItemInfo.snDurability >= 0 ) 
				{
					HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
					if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
						++iCurDur;	// �ø� ó��
					HTint iMaxDur = sOut/HT_ITEM_DURABILITY_DIVIDING ;
					if( sOut % HT_ITEM_DURABILITY_DIVIDING > 0 )
						++iMaxDur; // �ø� ó��

					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					
					pExtData->basic.color = g_ColorTable[16]; //light grey
					// ������ %d / %d
					HT_vItemSystem_SetMessage( eMsgItemInfoDurability, &str );
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iCurDur, iMaxDur );
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
				}
				// ����/�� �� �ı��Ұ�
				else if( sOut == HT_ITEM_INFINITY_DURABILITY && CHTParamIDCheck::HT_bIsItemWeapon(t->cItem.m_sItemInfo.snIndex)
															&& CHTParamIDCheck::HT_bIsItemDefence(t->cItem.m_sItemInfo.snIndex) )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[11]; //red
					// �ı��Ұ�
					HT_vItemSystem_SetMessage( eMsgItemInfoUnbreakable, &pExtData->basic.str );
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
				}
			}

			// ����ó�� - ��޾ƴ��ٹ�/�ƴ��ٹ��� ������ ��� Effect�� ǥ������ �ʴ´�. (���� 2004. 9. 21 �߰�)
			if( t->cItem.m_sItemInfo.snIndex == HT_INDEX_DAMAGE_UP
						|| t->cItem.m_sItemInfo.snIndex == HT_INDEX_SUPERIOR_DAMAGE_UP
						|| t->cItem.m_sItemInfo.snIndex == HT_INDEX_SUPERIOR_DAMAGE_UP2 )
			{
				// ������ �Ǹ� ����
				if( g_cNPCControl->HT_bNPCControl_IsItemMake() ) 
				{
					pData = new HT_ITEM_DATA;
					pData->color = g_ColorTable[17]; //yellow;
					// �Ǹ� ����
					HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());

					HTint iRupiah = 0 ;
					HTshort sMaxDurability = 0 ;
					g_pParamMgr->HT_bGetItemSellRupiah( &iRupiah );
					g_pParamMgr->HT_bGetItemMaxDurability( &sMaxDurability );

					pData = new HT_ITEM_DATA;
					pData->color = g_ColorTable[17]; //yellow;
					if( iRupiah >= 0 )  // ö
					{
						HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount;// / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
						if(iNeedRupiah >= 0)
						{
							// %d ���Ǿ�
							CHTString szMessage;
							HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

							CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // ��ǥ ó��
							pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
						}
					}
					else
					{
						//if(pData->str.HT_nGetSize() == 0)
						// �Ǹ� �Ұ�
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
						pData->color = g_ColorTable[11];	//red
					}

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}

				// ������ ���� Lock ����
				g_pParamMgr->HT_bUnLockID(t->cItem.m_sItemInfo.snIndex);
				return winSizeX;
			}


			// Effect 1
			HTint iDecreaseVal = HT_iItemSystem_GetDecreaseValForGapLevel( t->cItem.m_sItemInfo.snIndex );
			HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
			if( g_pParamMgr->HT_bGetItemEffect1ID( &iOut ) == true && iOut > 0 )
			{
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetItemEffect1Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect1Param2( &iParam2 );
				g_pParamMgr->HT_bGetItemEffect1Function( &iFunction ); 
				
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
			
				// ���� ������ ���� �������� ��� ����
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// ���ÿ� ���� ������ �Ӽ��� �ִ��� �˻�
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1���� - �ʿ䷹�� �˻�:���°� ���ݷ¸�
				if( iDecreaseVal > 0 
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )	
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2���� - ���� �Ӽ� �˻�
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// �ϴû�
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect1Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð� %d��)	
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// Effect 2
			if( g_pParamMgr->HT_bGetItemEffect2ID( &iOut ) == true && iOut > 0 )
			{
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetItemEffect2Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect2Param2( &iParam2 );
				g_pParamMgr->HT_bGetItemEffect2Function( &iFunction ); 
				
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				// ���� ������ ���� �������� ��� ����
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// ���ÿ� ���� ������ �Ӽ��� �ִ��� �˻�
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1���� - �ʿ䷹�� �˻�:���°� ���ݷ¸�
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2���� - ���� �Ӽ� �˻�
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// �ϴû�
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect2Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (���ӽð� %d��)", iOut/HT_ITEM_DURATION_DIVIDING);	
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING );

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// Effect 3
			if( g_pParamMgr->HT_bGetItemEffect3ID( &iOut ) == true && iOut > 0 )
			{
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetItemEffect3Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect3Param2( &iParam2 );
				g_pParamMgr->HT_bGetItemEffect3Function( &iFunction ); 

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				// ���� ������ ���� �������� ��� ����
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// ���ÿ� ���� ������ �Ӽ��� �ִ��� �˻�
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1���� - �ʿ䷹�� �˻�:���°� ���ݷ¸�
				if( iDecreaseVal > 0 
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2���� - ���� �Ӽ� �˻�
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// �ϴû�
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( t->cItem.m_sItemInfo.snIndex == 6601 || // ������ �������� ����° Ư�� ��¹��� (�󰡸���, �Ҷ󸶴�, �����, ���Ƽ)
					t->cItem.m_sItemInfo.snIndex == 6602 || 
					t->cItem.m_sItemInfo.snIndex == 6603 ||
					t->cItem.m_sItemInfo.snIndex == 6604 ||
					t->cItem.m_sItemInfo.snIndex == 6606 ||	// �߰� : 2006. 2. 17 ����� ���ü� ( ����Ǫ��, �񽴴�, �Ƴ���Ÿ, ��� )
					t->cItem.m_sItemInfo.snIndex == 6607 ||
					t->cItem.m_sItemInfo.snIndex == 6608 ||
					t->cItem.m_sItemInfo.snIndex == 6609 )
				{
					delete pExtData;
				}
				else if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect3Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (���ӽð� %d��)", iOut/HT_ITEM_DURATION_DIVIDING);	
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING );

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// Effect 4
			if( g_pParamMgr->HT_bGetItemEffect4ID( &iOut ) == true && iOut > 0 )
			{
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetItemEffect4Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect4Param2( &iParam2 );
				g_pParamMgr->HT_bGetItemEffect4Function( &iFunction ); 
				
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				// ���� ������ ���� �������� ��� ����
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// ���ÿ� ���� ������ �Ӽ��� �ִ��� �˻�
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1���� - �ʿ䷹�� �˻�:���°� ���ݷ¸�
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2���� - ���� �Ӽ� �˻�
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// �ϴû�
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect4Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (���ӽð� %d��)", iOut/HT_ITEM_DURATION_DIVIDING);	
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING );

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// Effect 5
			if( g_pParamMgr->HT_bGetItemEffect5ID( &iOut ) == true && iOut > 0 )
			{
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetItemEffect5Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect5Param2( &iParam2 );
				g_pParamMgr->HT_bGetItemEffect5Function( &iFunction );

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				// ���� ������ ���� �������� ��� ����
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// ���ÿ� ���� ������ �Ӽ��� �ִ��� �˻�
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1���� - �ʿ䷹�� �˻�:���°� ���ݷ¸�
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2���� - ���� �Ӽ� �˻�
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// �ϴû�
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect5Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (���ӽð� %d��)", iOut/HT_ITEM_DURATION_DIVIDING);		
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING );

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// ���ÿ� ���ؼ� �߰��� �Ӽ��� �ִٸ�
			//if( t->cItem.m_iSubItemIndexCount > 0 )
			if( t->cItem.m_bySubEffectIDCount > 0 )
			{
				// �������� �⺻������ �ִ� �Ӽ���
				HTint iEffect1ID = 0, iEffect2ID = 0, iEffect3ID = 0, iEffect4ID = 0, iEffect5ID = 0;
				
				g_pParamMgr->HT_bGetItemEffect1ID( &iEffect1ID );
				g_pParamMgr->HT_bGetItemEffect2ID( &iEffect2ID );
				g_pParamMgr->HT_bGetItemEffect3ID( &iEffect3ID );
				g_pParamMgr->HT_bGetItemEffect4ID( &iEffect4ID );
				g_pParamMgr->HT_bGetItemEffect5ID( &iEffect5ID );

				//for( int i = 0 ; i < t->cItem.m_iSubItemIndexCount ; ++i )
				for( int i = 0 ; i < t->cItem.m_bySubEffectIDCount ; ++i )
				{
					if( t->cItem.m_sItem_SubRefineInfo[i].iEffectID > 0 
							&& t->cItem.m_sItem_SubRefineInfo[i].iEffectID != iEffect1ID 
							&& t->cItem.m_sItem_SubRefineInfo[i].iEffectID != iEffect2ID
							&& t->cItem.m_sItem_SubRefineInfo[i].iEffectID != iEffect3ID
							&& t->cItem.m_sItem_SubRefineInfo[i].iEffectID != iEffect4ID
							&& t->cItem.m_sItem_SubRefineInfo[i].iEffectID != iEffect5ID )
					{
						str.HT_hrCleanUp();

						if( g_cSkillSystem->HT_bSkillSystem_GetEffect( t->cItem.m_sItem_SubRefineInfo[i].iEffectID, &str, 
							t->cItem.m_sItem_SubRefineInfo[i].iEffectParam1, t->cItem.m_sItem_SubRefineInfo[i].iEffectParam2, 
							t->cItem.m_sItem_SubRefineInfo[i].iEffectFunction, iDecreaseVal ) == HT_TRUE )
						{
							pExtData = new HT_ITEM_EXPANSION_DATA;
							ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

							pExtData->addtion.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f); // �ϴû�

							pExtData->addtion.str = str;		

							vInfo.vAttributeStr.push_back(pExtData);
							winSizeX = max(winSizeX, pExtData->addtion.str.HT_nGetSize());
							// ���ӽð�
							if( t->cItem.m_sItem_SubRefineInfo[i].iEffectDuration > 0 )
							{
								pExtData = new HT_ITEM_EXPANSION_DATA;
								ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

								pExtData->addtion.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f); // �ϴû�
								//    (���ӽð� %d��)	
								HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
								pExtData->addtion.str.HT_szFormat( str.HT_szGetString(), 
											t->cItem.m_sItem_SubRefineInfo[i].iEffectDuration/HT_ITEM_DURATION_DIVIDING );

								vInfo.vAttributeStr.push_back(pExtData);
								winSizeX = max(winSizeX, pExtData->addtion.str.HT_nGetSize());
							}
						}
					}
				} // end of for( int i = 0 ; i < t->cItem.m_iSubItemIndexCount ; ++i )
			} // end of ���ÿ� ���ؼ� �߰��� �Ӽ��� �ִٸ�
			// ���� �ӵ� - ������ ���
			if( CHTParamIDCheck::HT_bIsItemWeapon( t->cItem.m_sItemInfo.snIndex ) )
			{
				/* �����̳� �߰��� �Ӽ��� ���ؼ� ���ݼӵ� ����ƴ��� �˻��ؾ��� 2003.12.10 ���� */
				if( g_pParamMgr->HT_bGetItemCoolDownTime( &iOut ) == true && iOut > 0 )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					
					HTint iSpeed = HT_iItemSystem_CheckItemSpeedRange( iOut );
					pExtData->basic.color = g_ColorTable[16]; //light grey
					switch( iSpeed )
					{
						case HT_ITEM_SPEED_VERY_FAST : // ���� �ӵ� �ſ� ����	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedVeryHigh, &pExtData->basic.str ); break;
						case HT_ITEM_SPEED_FAST		 : // ���� �ӵ� ����
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedHigh, &pExtData->basic.str );		break;
						case HT_ITEM_SPEED_NORMAL	 : // ���� �ӵ� ����		
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedNormal, &pExtData->basic.str );	break;
						case HT_ITEM_SPEED_SLOW		 : // ���� �ӵ� ����	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedLow, &pExtData->basic.str );		break;
						case HT_ITEM_SPEED_VERY_SLOW : // ���� �ӵ� �ſ� ����	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedVeryLow, &pExtData->basic.str );	break;
						default: pExtData->basic.str.HT_hrCleanUp(); break;
					}

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				}
			}
			// �����Ÿ�
			//if( g_pParamMgr->HT_bGetItemRange( &byteOut ) && byteOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("�����Ÿ� %d", byteOut);		

			//	vInfo.vAttributeStr.push_back(pExtData);
			//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			//}
			// �Ҹ� HP
			if( g_pParamMgr->HT_bGetItemCostHP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("�Ҹ� HP %d", iOut);		
				HT_vItemSystem_SetMessage( eMsgItemInfoCostHP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);	

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			// �Ҹ� TP
			if( g_pParamMgr->HT_bGetItemCostTP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// �Ҹ� TP %d, iOut		
				HT_vItemSystem_SetMessage( eMsgItemInfoCostTP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			// �Ҹ� Item
			// ���� ���� ��� �Ҹ� Item ������ �ڽ��� �ε����� ����ִ�.
			if( g_pParamMgr->HT_bGetItemidCostItem( &iOut ) == true && iOut > 0 && iOut != t->cItem.m_sItemInfo.snIndex )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				
				CHTString str;
				g_pParamMgr->HT_bGetItemName( iOut, &str );
				// %s �Ҹ�, str.HT_szGetString()
				CHTString szMessage;
				HT_vItemSystem_SetMessage( eMsgItemInfoCostItem, &szMessage );
				pExtData->basic.str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString() );

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}

			// ������ �Ǹ� ����
			if( g_cNPCControl->HT_bNPCControl_IsItemMake() ) 
			{
				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[17]; //yellow;
				// �Ǹ� ����
				HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

				vInfo.vSourceStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());

				HTint iRupiah = 0 ;
				HTshort sMaxDurability = 0 ;
				g_pParamMgr->HT_bGetItemSellRupiah( &iRupiah );
				g_pParamMgr->HT_bGetItemMaxDurability( &sMaxDurability );

				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[17]; //yellow;
				if( iRupiah > 0 )  // ö
				{
					HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount;// / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
					if(iNeedRupiah > 0)
					{
						// %d ���Ǿ�
						CHTString szMessage;
						HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

						CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // ��ǥ ó��
						pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
					}
				}
				
				if(pData->str.HT_nGetSize() == 0)
				{
					// �Ǹ� �Ұ�
					HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
					pData->color = g_ColorTable[11];	//red
				}

				vInfo.vSourceStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// ������ ���� Lock ����
			g_pParamMgr->HT_bUnLockID(t->cItem.m_sItemInfo.snIndex);
			break;
		}
		t = t->next;
	}
	
	return winSizeX;
}

// ������ �ӵ� ���� ���ϱ�
HTint CHTItemSystem::HT_iItemSystem_CheckItemSpeedRange( HTint iSpeed )
{
	//�ſ����		����			����			����			�ſ� ����
	//����	�ִ�	����	�ִ�	����	�ִ�	����	�ִ�	����	�ִ�
	//501	750		751		1000	1001	1250	1251	1500	1501	
	if( iSpeed < 751 )
		return HT_ITEM_SPEED_VERY_FAST;
	else if( 750 < iSpeed && iSpeed < 1001 )
		return HT_ITEM_SPEED_FAST;
	else if( 1000 < iSpeed && iSpeed < 1251 )
		return HT_ITEM_SPEED_NORMAL;
	else if( 1250 < iSpeed && iSpeed < 1501 )
		return HT_ITEM_SPEED_SLOW;
	else //if( 1500 < iSpeed )
		return HT_ITEM_SPEED_VERY_SLOW;
}

//----- ������ Ÿ�Կ� ���� ���� ��޿� �־����� ���� ����� �ջ��Ѵ� ------//
HTbool CHTItemSystem::HT_bItemSystem_GetMainRefineEffect( HTdword dwIndex, HTint iLevel, HTint iEffectID, HTint* piParam1, HTint* piParam2 )
{
	if( dwIndex <= 0 || iLevel <= 0 )
		return HT_FALSE;

	HTint iVal = 0;
	iVal = HT_iItemSystem_GetMainRefineLevelConst( dwIndex, iLevel );

	// ������� �������� �ջ�
	if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) && g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iEffectID ) )
	{	
		*piParam1 += iVal;
		*piParam2 += iVal;
		return HT_TRUE;
	}
	// �� �� ���ʷ��� ��������� ���� ���� �ջ�
	else if( CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) && (iEffectID == eTNAfn_ACPlus || iEffectID == eTNAfn_ACMinus) )
	{
		*piParam1 += iVal;
		return HT_TRUE;
	}

	return HT_FALSE;
}

// �Ѽհ�, �Ѽյ���, �б�, �ܰ�, �Ѽ�������
//									  1	  2   3   4   5   6   7   8    9   10   11   12  13  14   15
HTint g_iRefineLevelConstType1[ ] = { 4,  8, 12, 16, 20, 24, 32, 40,  50,  60,  72,  84, 98, 102, 118};
// ��հ�, ��յ���, �۷���, â, ��� ������, Ȱ
HTint g_iRefineLevelConstType2[ ] = { 6, 12, 18, 24, 30, 36, 48, 60,  75,  90, 108, 126, 147, 168, 192 };
// ����, ����, ����
HTint g_iRefineLevelConstType3[ ] = { 9, 18, 27, 36, 48, 60, 75, 96, 126, 162, 207, 252, 306, 360, 420 };
// �Ź�, �尩, �㸮��, ����
HTint g_iRefineLevelConstType4[ ] = { 3,  6,  9, 12, 16, 20, 25, 32,  42,  54,  69,  84, 102, 114, 135 };
//--------------- (��ȭ)���ôܰ迡 ���� ���� ��� ���ϱ� ------------------// 
HTint CHTItemSystem::HT_iItemSystem_GetMainRefineLevelConst( HTdword dwIndex, HTint iLevel )
{
	if( dwIndex <= 0 || iLevel <= 0 )
		return 0;

	// ��
	if( CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) )
	{
		// ����, ����, ����
		if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) 
			|| CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) || CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) )
			return g_iRefineLevelConstType3[iLevel-1];
		// �Ź�, �尩, �㸮��, ����
		else
			return g_iRefineLevelConstType4[iLevel-1];
	}
	// ����
	else if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )
	{
		HTshort sType = 0;
		if( g_pParamMgr->HT_bGetItemType( dwIndex, &sType ) == false )
			return 0;

		// �Ѽհ�,�Ѽյ���,�Ѽ� ������, �ܰ�, �б�
		if( ( CHTParamIDCheck::HT_bIsItemWeaponOneHand( dwIndex ) 
					&& ( sType == _ITEM_TYPE_WEPON_SWORD || sType == _ITEM_TYPE_WEPON_AX || sType == _ITEM_TYPE_WEPON_WAND) )
				|| sType == _ITEM_TYPE_WEPON_DAGGER || sType == _ITEM_TYPE_WEPON_MACE )
			return g_iRefineLevelConstType1[iLevel-1];
		// ��հ�, ��յ���, ��� ������, �۷���, â, Ȱ
		else 
			return g_iRefineLevelConstType2[iLevel-1];
	}
	else
		return 0;
}
// �������� �ʿ䷹���� ���� ��ġ ���ҷ�
HTint CHTItemSystem::HT_iItemSystem_GetDecreaseValForGapLevel( HTint iItemIndex )
{
	if( iItemIndex <= 0 )
		return -1;

	HTbyte byLimitLevel = 0;
	if( g_pParamMgr->HT_bGetItemLimitLevel( iItemIndex, &byLimitLevel ) == false )
		return -1;
	
	HTint iGapLevel = 0;
	if( g_cStatus->HT_byGetLevel() < byLimitLevel )
		iGapLevel = byLimitLevel - g_cStatus->HT_byGetLevel();
	else return -1;

	if( iGapLevel < 7 )
		return 50;
	else if( 7 <= iGapLevel && iGapLevel < 13 )
		return 55;
	else if( 13 <= iGapLevel && iGapLevel < 19 )
		return 60;
	else if( 19 <= iGapLevel && iGapLevel < 25 )
		return 65;
	else if( 25 <= iGapLevel && iGapLevel < 31 )
		return 70;
	else if( 31 <= iGapLevel && iGapLevel < 37 )
		return 75;
	else if( 37 <= iGapLevel && iGapLevel < 43 )
		return 80;
	else if( 43 <= iGapLevel && iGapLevel < 49 )
		return 85;
	else if( 49 <= iGapLevel && iGapLevel < 55 )
		return 90;
	else //if( 55 <= iGapLevel )
		return 95;
}
//	Returns Get �÷��̾�� ���� ����� Itemt KeyID�O��
HTint CHTItemSystem::HT_iItemSystem_GetItemKeyIDMostNearMainChar()
{
	HTPoint pMainPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTPoint pObjectPt;
	HTint iMostNearKeyID = 0;
	HTint iMostNear = 100;
	HTint iCurNear;
	CHTString strName;
    
	HT_NODE *t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		pObjectPt.x = t->cItem.m_sItemMapCellX;
		pObjectPt.y = t->cItem.m_sItemMapCellZ;
		iCurNear = (HTint)sqrt( double( (pObjectPt.x - pMainPt.x) * (pObjectPt.x - pMainPt.x) ) 
							  + double( (pObjectPt.y - pMainPt.y) * (pObjectPt.y - pMainPt.y) ) );

		if( iCurNear < iMostNear )
		{
			iMostNear = iCurNear;
			iMostNearKeyID = t->cItem.m_dwItemKeyID;
			strName = t->cItem.m_strItemName;
		}
		t = t->next;
	}

	if( iMostNearKeyID )
	{
		t->cItem.m_bItem_Info_Sw	= HT_TRUE;
		t->cItem.m_bItem_PickUp_Sw	= HT_TRUE;
		//-----������ ���� �����ֱ�-----//
		g_pMainBar->HT_vSetObjectTextDraw( strName );
	}

	return iMostNearKeyID;
}

//	Set Item Targetting Effect
HTvoid CHTItemSystem::HT_vItemSystem_SetItemTargettingEffect( HTint iKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == iKeyID )
		{
			if( m_iItemTargettingEffectID == 0 )
                g_pEngineHandler->HT_hrStartSFX( &m_iItemTargettingEffectID, HT_FX_ITEMTARGETTING, t->cItem.m_iItem3DID, HT_TRUE );
			return;
		}
		t = t->next;
	}
}

//	���� �̸��� �������� �ִ��� �˻�
HTRESULT CHTItemSystem::HT_hrItemSystem_GetSameNameCheck( CHTString strItemName )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( strItemName.HT_iStringCompare( t->cItem.m_strItemName.HT_szGetString() ) == 0 )
		{
			return HT_OK;
		}
		t = t->next;
	}

	return HT_FAIL;
}

//	KeyID�� ������ ������ �ؽ��� ���̵� ����
HTint CHTItemSystem::HT_iItemSystem_GetTextureIDFromKeyID( HTint iKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == iKeyID )
		{
			return t->cItem.m_iItemTextureID;
		}
		t = t->next;
	}

	return 0;
}

//	������ �������� �ִ��� ����
HTRESULT CHTItemSystem::HT_hrItemSystem_CheckEquipItem()
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_EQUIP )
		{
			return HT_OK;
		}
		t = t->next;
	}

	return HT_FAIL;
}

//------- ������ �⺻ �Ӽ��� �������� �߰��� �Ӽ� �� ---------//
HTbool CHTItemSystem::HT_bItemSystem_GetSubRefineEffect( const HT_NODE* pItemNode, const HTint iEffectID, HTint* piParam1, HTint* piParam2, HTint* piFunction )
{
	if( pItemNode == NULL || iEffectID <= 0 )
		return HT_FALSE;

	for( HTint i = 0 ; i < pItemNode->cItem.m_bySubEffectIDCount ; ++i )
	{
		if( pItemNode->cItem.m_sItem_SubRefineInfo[i].iEffectID == iEffectID )
		{
			*piParam1 += pItemNode->cItem.m_sItem_SubRefineInfo[i].iEffectParam1;
			*piParam2 += pItemNode->cItem.m_sItem_SubRefineInfo[i].iEffectParam2;
			*piFunction += pItemNode->cItem.m_sItem_SubRefineInfo[i].iEffectFunction;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

//---------- ��ȭ ���� ���� ���ϱ� ----------//
HTbyte CHTItemSystem::HT_byItemSystem_GetMainRefineLevel( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
			return t->cItem.m_sItemInfo.byRefineLevel;

		t = t->next;
	}

	return -1;
}

//--------�ּ� ���� ���� ���ϱ�------------//
HTint CHTItemSystem::HT_iItemSystem_GetSubRefineLevel( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	HTint iEtcRefine = 0;
	HTbyte bySubItemIndex = 0;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			for( HTint i = 0; i < MAX_SUBMATERIALSIZE ; ++i )
			{
				if( t->cItem.m_sItemInfo.bySubRefine[i] > 0 )
				{
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	����4��Ʈ ����
					if( bySubItemIndex > 0 )
						++iEtcRefine;
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	����4��Ʈ ����
					if( bySubItemIndex > 0 )
						++iEtcRefine;
				}
			}
			return iEtcRefine;
		}
		t = t->next;
	}

	return iEtcRefine;
}

//--------�ּ� ���� ������ �� �Ӽ� ���õ� ������ �˻�---------//
// �� �����ۿ� �ϳ��� �Ӽ��� ���� �����ϴ�.
HTint CHTItemSystem::HT_iItemSystem_GetAttributeSubRefineItem( DWORD dwKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	HTint iAttri = HT_SUBREFINETYPE_NONE;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			for( HTint i = 0; i < t->cItem.m_bySubEffectIDCount ; ++i )
			{
				iAttri = HT_iItemSystem_GetAttribute( t->cItem.m_sItem_SubRefineInfo[i].iEffectID );

				if( iAttri != HT_SUBREFINETYPE_NONE ) // �� �����ۿ� �ϳ��� �Ӽ��� ���� �����ϴ�.
					break;
			}	// end of for( HTint i = 0; i < t->cItem.m_iSubItemIndexCount ; ++i )

			break;
		}	// end of if( t->cItem.m_dwItemKeyID == dwKeyID )
		t = t->next;
	}	// end of while( t != m_sTail )

	return iAttri;
}

HTint CHTItemSystem::HT_iItemSystem_GetAttribute( HTint iEffectID )
{
	switch( iEffectID )
	{
		case eTNAfn_Fire :			
		case eTNAfn_FireSplash :		
		case eTNAfn_FireDamagePlus :			
		case eTNAfn_FireDamageMinus :	
			return HT_SUBREFINETYPE_FIRE;
		
		case eTNAfn_Cold :
		case eTNAfn_ColdSplash :
		case eTNAfn_ColdDamagePlus :		
		case eTNAfn_ColdDamageMinus :	
			return HT_SUBREFINETYPE_ICE;
		
		case eTNAfn_Lightning :
		case eTNAfn_LightningSplash :
		case eTNAfn_LightningDamagePlus :		
		case eTNAfn_LightningDamageMinus :
			return HT_SUBREFINETYPE_LIGHTING;
		
		case eTNAfn_Poison :
		case eTNAfn_PoisonSplash :
		case eTNAfn_PoisonDamagePlus :		
		case eTNAfn_PoisonDamageMinus :
			return HT_SUBREFINETYPE_FIRE;

		default : break;
	}

	return HT_SUBREFINETYPE_NONE;
}

//--------�ּ� ���ÿ� ���� ������ index ���ϱ�------------//
HTint CHTItemSystem::HT_iItemSystem_GetSubRefineItemsIndex( DWORD dwKeyID, HTbyte* bySubRefine )
{
	HT_NODE* t;
	t = m_sHead->next;

	HTint iRefineCount = 0;
	HTbyte bySubItemIndex = 0;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			for( HTint i = 0; i < MAX_SUBMATERIALSIZE ; ++i )
			{
				bySubRefine[i] = t->cItem.m_sItemInfo.bySubRefine[i];
				
				if( t->cItem.m_sItemInfo.bySubRefine[i] > 0 ) // ���� ����
				{
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	����4��Ʈ ����
					if( bySubItemIndex > 0 )
						++iRefineCount; 
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	����4��Ʈ ����
					if( bySubItemIndex > 0 )
						++iRefineCount; 
				}
			}

			return iRefineCount;
		}
		t = t->next;
	}

	return iRefineCount;
}

//----------������ ���� - ������ �̵��ӵ�----------//
//HTfloat CHTItemSystem::HT_fItemSystem_GetItemSpeedUp( DWORD dwKeyID )
//{
//	HT_NODE* t;
//	t = m_sHead->next;
//
//	while( t != m_sTail )
//	{
//		if( t->cItem.m_dwItemKeyID == dwKeyID )
//		{
//			//return t->cItem.m_sItem_Info.sPlusMovingSpeed;
//		}
//		t = t->next;
//	}
//
//	return 0.0f;
//}

//----------������ ���ý� �ʿ��� ���Ǿ� ����-------------//
HTint CHTItemSystem::HT_iItemSystem_GetRupiahForItemWork(HTint nItemLevel, HTint iRupiah)
{
	if( iRupiah <= 0 )
		return -1;

	// ���� ��� ���� (2005. 1. 7 ������) KeyWord: ���ð���, ���ú��
	//iRupiah = (int)(iRupiah * ITEM_REFINING_COAT * (nItemLevel + 1) * (nItemLevel + 1));
	iRupiah = (int)(iRupiah * ITEM_REFINING_COAT * pow((double)nItemLevel + 1, 1.8));

	// iRupiah * 20 / 100 �ּ������� ��쿡�� ���� ���� ����

	return iRupiah;
}

//----------������ ���� ����-------------//
//------------------------------------------------------------------------------------//
// ���� - ���������� ��� �޼����� �����ϰ�, �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
//------------------------------------------------------------------------------------//
HTint CHTItemSystem::HT_iGetFixInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible)
{
    HT_NODE* t;
	t = m_sHead->next;

	HTint winSizeX = 0;
	bPossible = HT_TRUE;	// ���� ����

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			// ������ ���� ������
			HT_ITEM_DATA* pData = HT_NULL;

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[15]; //white;
			//pData->str.HT_szFormat("���� ����");
			HT_vItemSystem_SetMessage( eMsgItemInfoRepairTitle, &pData->str );

			vInfo.push_back(pData);
			winSizeX = pData->str.HT_nGetSize();

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[17]; //yellow;
			pData->str = t->cItem.m_strItemName;
			// ��ȭ ���� ������ ǥ���Ѵ�.
			if( t->cItem.m_sItemInfo.byRefineLevel > 0)
			{
				CHTString str;
				str.HT_szFormat("+%d", t->cItem.m_sItemInfo.byRefineLevel);
				pData->str += str;
			}

			vInfo.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			
			// �Ҹ� ������ �Ǵ� ��� �Ǵ� �������
			if( CHTParamIDCheck::HT_bIsItemUsable( t->cItem.m_sItemInfo.snIndex ) 
					|| CHTParamIDCheck::HT_bIsItemCollect( t->cItem.m_sItemInfo.snIndex ) 
					/*|| CHTParamIDCheck::HT_bIsItemQuestOnly( t->cItem.m_sItemInfo.snIndex ) */ )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("�����Ұ�");
				HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
				pData->color = g_ColorTable[11]; //red;
				bPossible = HT_FALSE;	// ���� �Ұ���

				vInfo.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			else	// ������ ������
			{ 
				// 255�� ���� �������̱� ������....�׸��� ������ῡ ���� �ı��Ұ��� ���� ��� �˻�
				HTshort sMaxDurability;
				if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDurability) == true )
				{
					if( sMaxDurability < HT_ITEM_INFINITY_DURABILITY )
					{
						HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
						if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
							++iCurDur;	// �ø� ó��
						HTint iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
						if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
							++iMaxDur; // �ø� ó��

						// �������� ����� ���
						if( iCurDur < iMaxDur )
						{
							HTint iRupiah;
							if( g_pParamMgr->HT_bGetItemRupiah( t->cItem.m_sItemInfo.snIndex, &iRupiah ) == true && iRupiah > 0 )  // ö
							{
								HTint iNeedRupiah = 0;
								// ����ؾ���
								HTfloat fPrice = ((HTfloat)iRupiah / 10000.0f + (HTfloat)pow((double)iRupiah, 0.85 ))*(HTfloat)(iMaxDur-iCurDur)/(HTfloat)iMaxDur;
								iNeedRupiah = (HTint)( fPrice * (HTfloat)t->cItem.m_sItemInfo.byCount);

								if(iNeedRupiah > 0)
								{
									pData = new HT_ITEM_DATA;
									//pData->str.HT_szFormat("%d ���Ǿ� �ʿ�", iNeedRupiah);
									CHTString szMessage;
									HT_vItemSystem_SetMessage( eMsgItemInfoNeedMoney, &szMessage );
									pData->str.HT_szFormat( szMessage.HT_szGetString(), iNeedRupiah );

									pData->color = g_ColorTable[17]; //yellow;

									vInfo.push_back(pData);
									winSizeX = max(winSizeX, pData->str.HT_nGetSize());
								}
							}
						}	// end of �������� ����� ���
						else	// ������ ��ȭ�� �������
						{
							pData = new HT_ITEM_DATA;
							//pData->str.HT_szFormat("�����Ұ�");
							HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
							pData->color = g_ColorTable[11]; //red;
							bPossible = HT_FALSE;	// ���� �Ұ���

							vInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						}
						pData = new HT_ITEM_DATA;
						//pData->str.HT_szFormat("������ %d/%d", iCurDur, iMaxDur ); 
						CHTString szMessage;
						HT_vItemSystem_SetMessage( eMsgItemInfoDurability, &szMessage );
						pData->str.HT_szFormat( szMessage.HT_szGetString(), iCurDur, iMaxDur );

						pData->color = g_ColorTable[16]; //light grey
						
						vInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}	// end of if( sMaxDurability > 0 )
					else // ���� ������
					{
						pData = new HT_ITEM_DATA;

						//pData->str.HT_szFormat("�����Ұ�");
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
						pData->color = g_ColorTable[11]; //red;
						bPossible = HT_FALSE;	// ���� �Ұ���

						vInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}	// end of if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDurability) == true )
			}	// end of ������ ������
			break;
		}
		t = t->next;
	}
	
	return winSizeX;
}
// ������ �ʿ��� ���������� �˻�
HTbool CHTItemSystem::HT_bItemSystem_CheckNeedFix(DWORD dwItemKeyID)
{
	HTdword dwItemIndex = this->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex == 0 )
		return HT_FALSE;
	
	HTshort sMaxDurability = 0;
	if( g_pParamMgr->HT_bGetItemMaxDurability(dwItemIndex, &sMaxDurability) == false )
		return HT_FALSE;

	HTshort sCurDurability = this->HT_sItemSystem_GetCurDurability(dwItemKeyID);
	HTint iCurDur = sCurDurability/HT_ITEM_DURABILITY_DIVIDING;
	if( sCurDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
		++iCurDur;	// �ø� ó��
	HTint iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
	if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
		++iMaxDur; // �ø� ó��

	// �������� ����� ���
	if( iCurDur < iMaxDur )
		return HT_TRUE;
	else
		return HT_FALSE;
}

// �Ǹűݾ� ����ϱ�
HTint CHTItemSystem::HT_iItemSystem_CalDisjointPrice(DWORD dwKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	//HTint iNeedRupiah = 0;
	HTint iRupiah = 0;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			// ������ ���� ������		// ���� 2004. 9. 18 ������

			g_pParamMgr->HT_bGetItemSellRupiah( t->cItem.m_sItemInfo.snIndex, &iRupiah);
			
			//if( iRupiah > 0 )	
			//	iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount / 6 ;

			break;
		}
		t = t->next;
	}

	//return iNeedRupiah;
	return iRupiah;
}

//----------������ ��ü ����-------------//
//------------------------------------------------------------------------------------//
// ���� - �Ǹ������� ��� �޼����� �����ϰ�, �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
//------------------------------------------------------------------------------------//
HTint CHTItemSystem::HT_iGetDisjointInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible)
{
    HT_NODE* t;
	t = m_sHead->next;

	HTint winSizeX = 0;
	bPossible = HT_TRUE;	// ��ü ����

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			// ������ ���� ������
			HT_ITEM_DATA* pData = HT_NULL;

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[15]; //white;
			// �Ǹ� ����
			HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

			vInfo.push_back(pData);
			winSizeX = pData->str.HT_nGetSize();

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[17]; //yellow;
			pData->str = t->cItem.m_strItemName;
			// ��ȭ ���� ������ ǥ���Ѵ�.
			if( t->cItem.m_sItemInfo.byRefineLevel > 0)
			{
				CHTString str;
				str.HT_szFormat("+%d", t->cItem.m_sItemInfo.byRefineLevel);
				pData->str += str;
			}

			vInfo.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());

			HTint iRupiah = 0 ;
			HTshort sMaxDurability = 0 ;
			if( g_pParamMgr->HT_bLockID( t->cItem.m_sItemInfo.snIndex ) == true )
			{
				g_pParamMgr->HT_bGetItemSellRupiah( &iRupiah);
				g_pParamMgr->HT_bGetItemMaxDurability( &sMaxDurability);

				g_pParamMgr->HT_bUnLockID( t->cItem.m_sItemInfo.snIndex );
			}
			else
				return winSizeX;

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[17]; //yellow;
			if( iRupiah > 0 )  // ö
			{
				HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
				if(iNeedRupiah > 0)
				{
					// %d ���Ǿ�
					CHTString szMessage;
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // ��ǥ ó��
					pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
				}
			}
			
			if(pData->str.HT_nGetSize() == 0)
			{
				// �Ǹ� �Ұ�
				HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
				pData->color = g_ColorTable[11];	//red

				bPossible = HT_FALSE;	// ��ü �Ұ���
			}

			vInfo.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			
			// 255�� ���� �������̱� ������....�׸��� ������ῡ ���� �ı��Ұ��� ���� ��� �˻�
			// ������ - ���� ������(255)�� �ƴҶ��� ǥ�����ش�.
			if( sMaxDurability < HT_ITEM_INFINITY_DURABILITY )
			{
				HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
				if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
					++iCurDur;	// �ø� ó��
				HTint iMaxDur = sMaxDurability/HT_ITEM_DURABILITY_DIVIDING;
				if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
					++iMaxDur; // �ø� ó��

				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[16]; //light grey
				// ������ %d/%d
				CHTString szMessage;
				HT_vItemSystem_SetMessage( eMsgItemInfoDurability, &szMessage );
				pData->str.HT_szFormat( szMessage.HT_szGetString(), iCurDur, iMaxDur );

				vInfo.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			break;
		}
		t = t->next;
	}
	
	return winSizeX;
}

//----------������ ��ȭ�κ�---------//
HTvoid CHTItemSystem::HT_vItemSystem_vNetWork_SCP_Item_Durability_Decrease( MSG_ITEM* info )
{
	if( info->byPlace == ITEM_PLACE_EQUIP )
	{
		if (!( info->byIndex < 0 || info->kItem.snIndex < 0 || info->kItem.snDurability < 0))
		{
			HTdword dwKeyID = this->HT_dwSystem_GetItemEquipKeyID( info->byIndex );
			
			// ���� ���â���� KeyID�� ��� �ε����� �˻�
			HTint iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, info->byIndex, iKeyID );
			
			HTdword dwIndex = this->HT_dwSystem_GetItemIndex( iKeyID );

			if (dwIndex != (info->kItem.snIndex+4000) )	// ��� �ε����� �˻��ؼ� ������ ���� �Ѿ���� ����
				return;

			// ������ ���� ���â�� ǥ��
			HT_dwItemSystem_SetCurDurability( dwKeyID, info->kItem.snDurability );

			// ������ ��� ����
			HT_vItemSystem_SetDurabilityWarning( info->byIndex );

			//CHTString strTemp;
			//strTemp.HT_szFormat("%d, %d\n", info->byIndex, info->kItem.snDurability );
			//HT_g_vLogFile( strTemp.HT_szGetString() );
		}
		else
		{
			int nDurability = info->kItem.snDurability;
		}
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Receive_Item_Decrease: %d:%d-%d", 
	//													info->byPlace, info->byIndex, info->kItem.snDurability);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	0x01:�Ӹ�,0x02:�Ͱ���,0x03:�����,0x04:��,0x05:��Ʈ,0x06:���,0x07:������
//	0x08:�޼�,0x09:������ or �޼�,0x0a:������ ��,0x0b:������ �Ʒ�,0x0c:�޼� ��,0x0d:�޼� �Ʒ�,0x0e:��
HTRESULT CHTItemSystem::HT_hrItemSystem_vNetWork_SCP_Item_Abrasion(PS_SCP_ITEM_ABRASION info)
{
	return HT_TRUE;
}

//--------------���� ������ �����ϰ� �� �������� Index ��ȯ-----------//
DWORD CHTItemSystem::HT_dwItemSystem_SetCurDurability(DWORD dwItemKeyID, HTint iCurDurability)
{
	HT_NODE* t;
	t = m_sHead->next;

	//HTfloat fCurDurability;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			// ���� �������� �ִ� �������� ��
			HTshort sMaxDur;
			if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDur ) == true && iCurDurability <= sMaxDur )
			{
				t->cItem.m_sItemInfo.snDurability = iCurDurability;
				return t->cItem.m_sItemInfo.snIndex;
			}
			else
				return -999;
		}
		t = t->next;
	}

	return -999;	// ������ ����:0~25500
}
 
//-----------���� ������ ��ȯ--------------//
HTshort CHTItemSystem::HT_sItemSystem_GetCurDurability(DWORD dwItemKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
			return t->cItem.m_sItemInfo.snDurability;

		t = t->next;
	}
	return 0;	// 255�� ���ѳ�����
}

//--------------�ִ� ������ ��ȯ-------------------//
HTshort CHTItemSystem::HT_sItemSystem_GetMaxDurability(DWORD dwItemKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			HTshort sMaxDur;
			if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDur ) == true )
				return sMaxDur;
			else
				return 0;
		}

		t = t->next;
	}
	
	return 0;	// -1�� ���ѳ�����
}

//--------������� ���� ����� --------//
HTbool CHTItemSystem::HT_bItemSystem_ClearSubRefineItem(DWORD dwItemKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			t->cItem.HT_vItemAI_ClearSubItemInfo();
			return HT_TRUE;	
		}
		t = t->next;
	}
	
	return HT_FALSE;
}

HTbool CHTItemSystem::HT_bItemSystem_SetMainRefineLevel(DWORD dwItemKeyID, HTint iLevel)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			t->cItem.HT_vItemAI_SetMainRefineLevel(iLevel);
			return HT_TRUE;	
		}
		t = t->next;
	}
	
	return HT_FALSE;
}

HTbool CHTItemSystem::HT_bItemSystem_SetSubRefineEffect
( DWORD dwItemKeyID, HTint iEffectID, HTint iParam1, HTint iParam2, HTint iFunction, HTint iDuration )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID)
		{
			for(HTint i = 0; i < t->cItem.m_bySubEffectIDCount ; ++i)
			{
				if( t->cItem.m_sItem_SubRefineInfo[i].iEffectID == iEffectID )
				{
					t->cItem.m_sItem_SubRefineInfo[i].iEffectParam1 += iParam1;
					t->cItem.m_sItem_SubRefineInfo[i].iEffectParam2 += iParam2;
					break;
				}
			}
			// ���ο� Effect�� ���
			if( i == t->cItem.m_bySubEffectIDCount 
						&& t->cItem.m_bySubEffectIDCount < (MAX_REFINE_SUB_LEVEL*MAX_EFFECT_NUM - 1 ) )	
			{
				++(t->cItem.m_bySubEffectIDCount);

				// ���밡���� �Ӽ����� �˻�
				if( HT_vItemSystem_CheckItemEffect( t->cItem.m_sItemInfo.snIndex, iEffectID ) )
				{
					t->cItem.m_sItem_SubRefineInfo[i].iEffectID = iEffectID;
					t->cItem.m_sItem_SubRefineInfo[i].iEffectParam1 = iParam1;
					t->cItem.m_sItem_SubRefineInfo[i].iEffectParam2 = iParam2;
					t->cItem.m_sItem_SubRefineInfo[i].iEffectFunction = iFunction; 
					t->cItem.m_sItem_SubRefineInfo[i].iEffectDuration = iDuration;
				}
			}
			return HT_TRUE;
		}

		t = t->next;
	} // end of while( t != m_sTail )

	return HT_FALSE;
}

/*
// �ش� ������ (Ű���̵�)�� �ּ� ������ �߸��Ǿ� �ִ� �����Ͽ� �ߵǾ� ������ Ʈ��, �߸��Ǿ� ������ �޽��� ��ȯ�մϴ�.
HTbool CHTItemSystem::HT_bItemSystem_GetSubRefineItemRight(DWORD dwItemKeyID)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID)
			break;

		t = t->next;
	}
	 
	if(t == m_sTail)
		return HT_FALSE;

	BYTE aa;
	for( j = 0; j < MAX_SUBMATERIALSIZE ; ++ j )
	{
		// �������� ������ ���� �״�� ������ �ּ����� ����
		t->cItem.m_sItemInfo.bySubRefine[j];

		if( bySubItem[j] > 0 )
		{
			bySubItemIndex = bySubItem[j] >> 4;		//	����4��Ʈ ����
			bySubItemIndex2 = bySubItem[j] & 0x0F;	//	����4��Ʈ ����
		}
	}

	return true;
}
*/

HTbool CHTItemSystem::HT_bItemSystem_SetSubRefineItem(DWORD dwItemKeyID, HTbyte bySubItem[MAX_SUBMATERIALSIZE] )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID)
			break;

		t = t->next;
	}
	 
	if(t == m_sTail)
		return HT_FALSE;

	HTint iOut = 0;
	HTint i = 0, j = 0;
	HTint iItemIndex = 0;
	HTbyte bySubItemIndex = 0, bySubItemIndex2 = 0;
	HTint iEffectID = 0, iParam1 = 0, iParam2 = 0, iFunction = 0, iDuration = 0;
	for( j = 0; j < MAX_SUBMATERIALSIZE ; ++ j )
	{
		// �������� ������ ���� �״�� ������ �ּ����� ����
		t->cItem.m_sItemInfo.bySubRefine[j] = bySubItem[j] ;

		if( bySubItem[j] > 0 )
		{
			bySubItemIndex = bySubItem[j] >> 4;		//	����4��Ʈ ����
			bySubItemIndex2 = bySubItem[j] & 0x0F;	//	����4��Ʈ ����

			// ������ �������� �������� �ּ����� ����
			for( i = 0 ; i < 2 ; ++ i ) // 2��(��/������Ʈ) �ݺ��ϱ� ���� 
			{
				if( i % 2 == 0 ) // ���� ������ �ε���
					iItemIndex = HT_ITEM_REFINE_INDEX_START + bySubItemIndex;	// ���� 4��Ʈ
				else
					iItemIndex = HT_ITEM_REFINE_INDEX_START + bySubItemIndex2;	// ���� 4��Ʈ
				// ���� ��ᰡ ���� ��� iItemIndex == HT_ITEM_REFINE_INDEX_START
				if( iItemIndex > HT_ITEM_REFINE_INDEX_START )
				{
					if( g_pParamMgr->HT_bLockID( iItemIndex ) == true )	// ������ ���� Lock����
					{
						// Effect1ID
						if( g_pParamMgr->HT_bGetItemEffect1ID( &iEffectID ) == true && iEffectID > 0 )
						{
							g_pParamMgr->HT_bGetItemEffect1Param1( &iParam1 );
							g_pParamMgr->HT_bGetItemEffect1Param2( &iParam2 );
							g_pParamMgr->HT_bGetItemEffect1Function( &iFunction );
							g_pParamMgr->HT_bGetItemEffect1Duration( &iDuration );

							HT_bItemSystem_SetSubRefineEffect( dwItemKeyID, iEffectID, iParam1, iParam2, iFunction, iDuration );
						}
						// Effect2ID
						if( g_pParamMgr->HT_bGetItemEffect2ID( &iEffectID ) == true && iEffectID > 0 )
						{
							g_pParamMgr->HT_bGetItemEffect2Param1( &iParam1 );
							g_pParamMgr->HT_bGetItemEffect2Param2( &iParam2 );
							g_pParamMgr->HT_bGetItemEffect2Function( &iFunction );
							g_pParamMgr->HT_bGetItemEffect2Duration( &iDuration );

							HT_bItemSystem_SetSubRefineEffect( dwItemKeyID, iEffectID, iParam1, iParam2, iFunction, iDuration );
						}
						// Effect3ID
						if( g_pParamMgr->HT_bGetItemEffect3ID( &iEffectID ) == true && iEffectID > 0 )
						{
							g_pParamMgr->HT_bGetItemEffect3Param1( &iParam1 );
							g_pParamMgr->HT_bGetItemEffect3Param2( &iParam2 );
							g_pParamMgr->HT_bGetItemEffect3Function( &iFunction );
							g_pParamMgr->HT_bGetItemEffect3Duration( &iDuration );

							HT_bItemSystem_SetSubRefineEffect( dwItemKeyID, iEffectID, iParam1, iParam2, iFunction, iDuration );
						}
						// Effect4ID
						if( g_pParamMgr->HT_bGetItemEffect4ID( &iEffectID ) == true && iEffectID > 0 )
						{
							g_pParamMgr->HT_bGetItemEffect4Param1( &iParam1 );
							g_pParamMgr->HT_bGetItemEffect4Param2( &iParam2 );
							g_pParamMgr->HT_bGetItemEffect4Function( &iFunction );
							g_pParamMgr->HT_bGetItemEffect4Duration( &iDuration );

							HT_bItemSystem_SetSubRefineEffect( dwItemKeyID, iEffectID, iParam1, iParam2, iFunction, iDuration );
						}
						// Effect5ID
						if( g_pParamMgr->HT_bGetItemEffect5ID( &iEffectID ) == true && iEffectID > 0 )
						{
							g_pParamMgr->HT_bGetItemEffect5Param1( &iParam1 );
							g_pParamMgr->HT_bGetItemEffect5Param2( &iParam2 );
							g_pParamMgr->HT_bGetItemEffect5Function( &iFunction );
							g_pParamMgr->HT_bGetItemEffect5Duration( &iDuration );

							HT_bItemSystem_SetSubRefineEffect( dwItemKeyID, iEffectID, iParam1, iParam2, iFunction, iDuration );
						}

						g_pParamMgr->HT_bUnLockID( iItemIndex );
					} // end of if( g_pParamMgr->HT_bLockID( iItemIndex ) == true )
					else
						return HT_FALSE;
				} // end of if( iItemIndex > HT_ITEM_REFINE_INDEX_START )
			} // end of for( i = 0 ; i < 2 ; ++ i ) // 2��(��/������Ʈ) �ݺ��ϱ� ���� 
		}	// end of if( bySubItem[j] > 0 )
	}

	return HT_TRUE;
}


//--- ������ ������ ���� ������ �Ӽ� ���� ---//
HTbool CHTItemSystem::HT_vItemSystem_CheckItemEffect( HTint iItemIndex, HTint iEffectID )
{
	// 1. �Ӽ�(��/����/��/����)������ ��� 
	// �����϶��� ��������, �Ǻ�/������ ��� ���׷��� ��ȭ��Ų��
	// 2. ����� ������ ��� ���� ��������, �㸮��� ������ ��� ȸ������ ��ȭ��Ų��.
	if( CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex ) )
	{
		switch( iEffectID )
		{
			case eTNAfn_FireResistPlus	:		
			case eTNAfn_FireResistMinus :		
			case eTNAfn_ColdResistPlus	:		
			case eTNAfn_ColdResistMinus :		
			case eTNAfn_LightningResistPlus :		
			case eTNAfn_LightningResistMinus :	
			case eTNAfn_PoisonResistPlus :		
			case eTNAfn_PoisonResistMinus :
			case eTNAfn_DodgeRatePlus :
			case eTNAfn_DodgeRateMinus :
			case eTNAfn_SaveTPCost : // TP �Ҹ��� ����̿��� ����ȴ�.
			case eTNAfn_HPRecoveryPlus : // HP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_TPRecoveryPlus : // TP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_MaxHPPlus : // MAX HP�� ����̿��� ����ȴ�.
			case eTNAfn_AbsorbElementalDamage :
			case eTNAfn_MaxTPPlus : // TP ����
				return HT_FALSE;
			default: 
				return HT_TRUE;
		}
	}
	else if( CHTParamIDCheck::HT_bIsItemDefence( iItemIndex ) )
	{
		switch( iEffectID )
		{
			case eTNAfn_Fire :			
			case eTNAfn_Cold :			
			case eTNAfn_Lightning :		
			case eTNAfn_Poison :			
			case eTNAfn_FireSplash :		
			case eTNAfn_ColdSplash :		
			case eTNAfn_LightningSplash :
			case eTNAfn_PoisonSplash :
			case eTNAfn_FireDamagePlus :			
			case eTNAfn_FireDamageMinus :		
			case eTNAfn_ColdDamagePlus :		
			case eTNAfn_ColdDamageMinus :		
			case eTNAfn_LightningDamagePlus :		
			case eTNAfn_LightningDamageMinus :	
			case eTNAfn_PoisonDamagePlus :		
			case eTNAfn_PoisonDamageMinus :
			case eTNAfn_SaveTPCost : // TP �Ҹ��� ����̿��� ����ȴ�.
			case eTNAfn_HPRecoveryPlus : // HP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_TPRecoveryPlus : // TP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_MaxHPPlus : // MAX HP�� ����̿��� ����ȴ�.			
			case eTNAfn_AbsorbElementalDamage :
			case eTNAfn_MaxTPPlus : // TP ����
				return HT_FALSE;

			case eTNAfn_AttackRatePlus :	
			case eTNAfn_AttackRateMinus :
			{
				if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( iItemIndex ) )
					return HT_TRUE;
				else
					return HT_FALSE;
			}
			case eTNAfn_DodgeRatePlus :
			case eTNAfn_DodgeRateMinus :
			{
				if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( iItemIndex ) )
					return HT_FALSE;
				else
					return HT_TRUE;
			}
				
			default:
				return HT_TRUE;
		}
	}
	else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( iItemIndex ) )
	{
		switch( iEffectID )
		{
			case eTNAfn_SaveTPCost : // TP �Ҹ��� ����̿��� ����ȴ�.
			case eTNAfn_HPRecoveryPlus : // HP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_TPRecoveryPlus : // TP ȸ���� ����̿��� ����ȴ�.
			case eTNAfn_MaxHPPlus : // MAX HP�� ����̿��� ����ȴ�.
			case eTNAfn_AbsorbElementalDamage : // �Ӽ� ������ ���
			case eTNAfn_MaxTPPlus : // TP ����
				return HT_TRUE;
			default:
				return HT_FALSE;
		}
	}
	else
		return HT_TRUE;
}


//-----------------------------------------------------------------------------
// HTvoid				HT_vReformDurability(PS_SCP_INIT_EQUIPMENT oInfo, 
//									ITEM_BASIC_PARAM* sItemBasic, HTfloat fDurability)
// D : ���� �������� ���� ���� ǥ�� ����
//-----------------------------------------------------------------------------
HTvoid					
CHTItemSystem::HT_vItemSystem_SetDurabilityWarning( HTint iInvenIndex )
{
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, iInvenIndex, iKeyID );
	
	HTdword dwIndex = this->HT_dwSystem_GetItemIndex( iKeyID );

	if ( HT_bItemSystem_CheckDurabilityWarning( iKeyID ) )	// ������ ��� �ʿ��ϸ�
	{	
		if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )	// ����
		{
			m_bReformNeed[_eITEM_WEAPON] = HT_TRUE;	
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_RIGHT_HAND;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_BODY]	= HT_TRUE;
			if (!m_bTReformNeed) m_iNeedReformPlace = ITEM_LOCATION_EQUIP_ARMOR;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_PANTS]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_PANTS;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_SHIELD] = HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_LEFT_HAND;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwIndex ) ) // �Ӹ�
		{
			m_bReformNeed[_eITEM_HEAD]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_HEAD;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwIndex ) ) // �Ź�
		{
			m_bReformNeed[_eITEM_FOOT]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_FOOT;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwIndex ) ) // �㸮��
		{
			m_bReformNeed[_eITEM_BELT]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_BELT;
			}
		}
	}
	else
	{
		if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )	// ����
		{
			m_bReformNeed[_eITEM_WEAPON] = HT_FALSE;	
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_BODY]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_PANTS]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) ) // ����
		{
			m_bReformNeed[_eITEM_SHIELD] = HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwIndex ) ) // �Ӹ�
		{
			m_bReformNeed[_eITEM_HEAD]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwIndex ) ) // �Ź�
		{
			m_bReformNeed[_eITEM_FOOT]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwIndex ) ) // �㸮��
		{
			m_bReformNeed[_eITEM_BELT]	= HT_FALSE;
		}
	}
	
	// �������� ���� �������� �ϳ��� ������
	if ( m_bReformNeed[_eITEM_BODY] || m_bReformNeed[_eITEM_SHIELD] || m_bReformNeed[_eITEM_HEAD] || 
		 m_bReformNeed[_eITEM_FOOT] || m_bReformNeed[_eITEM_BELT] || m_bReformNeed[_eITEM_WEAPON] || m_bReformNeed[_eITEM_PANTS] )
			m_bTReformNeed = HT_TRUE;
	else 
	{
		m_bTReformNeed = HT_FALSE;
		m_iNeedReformPlace = -1; // ����
		m_flastWarningTime = 0.0f;
	}
}

HTvoid CHTItemSystem::HT_vItemSystem_RenewalDurabilityWarning( )
{
	HTdword dwKeyID = 0;
	
	if( m_bTReformNeed ) // ���� ���ǥ�� �ϰ� �ִ� ������ �˻�
	{
		dwKeyID = HT_dwSystem_GetItemEquipKeyID( m_iNeedReformPlace ); // ���ǥ�� �ϰ� �ִ� ������ 
		if( dwKeyID != 0 )	// 
		{		
			if( HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
				return;
			else
				HT_vItemSystem_DelDurabilityWarning();
		}
		else
			HT_vItemSystem_DelDurabilityWarning();
	}
	
	// ���� ���ǥ�� �ϰ� �ִ� �������� �����ưų� �����ϰ� ���� ���� ���
	// ��� ǥ���� �ٸ� �������� �ִ��� �˻��Ѵ�.
	// ����
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_RIGHT_HAND ); return;
	}
	// ����
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_ARMOR );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_ARMOR ); return;
	}
	
	// ����
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_PANTS );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_PANTS ); return;
	}

	// ����
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_LEFT_HAND ); return;
	}

	// �Ӹ�
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_HEAD );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_HEAD ); return;
	}

	// �Ź�
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_FOOT );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_FOOT ); return;
	}

	// �㸮��
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_BELT );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_BELT ); return;
	}
}

// ���� ������ ��� ǥ���ϴ� ������ ������ �����Ѵ�.
HTvoid CHTItemSystem::HT_vItemSystem_DelDurabilityWarning( )
{
	m_bTReformNeed = HT_FALSE;
	m_flastWarningTime = 0.0f;
	
	switch( m_iNeedReformPlace )
	{
		case ITEM_LOCATION_EQUIP_HEAD		: m_bReformNeed[_eITEM_HEAD]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_ARMOR		: m_bReformNeed[_eITEM_BODY]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_BELT		: m_bReformNeed[_eITEM_BELT]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_RIGHT_HAND : m_bReformNeed[_eITEM_WEAPON]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_LEFT_HAND	: m_bReformNeed[_eITEM_SHIELD]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_FOOT		: m_bReformNeed[_eITEM_FOOT]	= HT_FALSE; break;
		case ITEM_LOCATION_EQUIP_PANTS		: m_bReformNeed[_eITEM_PANTS]	= HT_FALSE; break;
		default : return;
	}
	m_iNeedReformPlace = -1;
}

// �������� ���� ���������� �˻�
HTbool CHTItemSystem::HT_bItemSystem_CheckDurabilityWarning( HTdword dwKeyID )
{
	HTshort sCurDurability, sMaxDurability = 0;
	HTint iCurDur = 0, iMaxDur = 0;
	HTfloat fDurability = 0;

	// ���� ���ǥ�� �ϰ� �ִ� ������ �˻�
	if( dwKeyID != 0 )
	{	
		HTdword dwIndex = this->HT_dwSystem_GetItemIndex( dwKeyID );
		if( dwIndex <= 0 )
			return HT_FALSE;

		// �ִ� ������ - ���� �������ϰ�� ó������ ����
		if( g_pParamMgr->HT_bGetItemMaxDurability( dwIndex, &sMaxDurability ) == false 
						|| sMaxDurability == HT_ITEM_INFINITY_DURABILITY )
			return HT_FALSE;

		iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
		if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
			++iMaxDur; // �ø� ó��

		// ���� ������
		sCurDurability = this->HT_sItemSystem_GetCurDurability( dwKeyID );
		iCurDur = sCurDurability / HT_ITEM_DURABILITY_DIVIDING;
		if( sCurDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
			++iCurDur;	// �ø� ó��

		fDurability = (HTfloat)iCurDur / (HTfloat)iMaxDur * 100.0f;
		if ( fDurability <= ITEM_DURABILITY_NOTE_MSG )
			return HT_TRUE;
		else
			return HT_FALSE;
	}

	return HT_FALSE;
}

//-----------------------------------------------------------------------------
// HTvoid					HT_vSetDurabilityMsg(HTint iItemNo, HTint dwItemID, HTint iDurability)
// D : ������ ���濡 ���� ���� ǥ�� �޼��� ���� �� �Ҹ� 
//-----------------------------------------------------------------------------
HTvoid
CHTItemSystem::HT_vSetDurabilityMsg( )
{
	m_dwMsgItemKeyID = HT_dwSystem_GetItemEquipKeyID( m_iNeedReformPlace );

	CHTString strMessage;
	// %s�� ���� �������� �ſ� �����ϴ�
	HT_vItemSystem_SetMessage( eMsgItemDurabilityWarning, &strMessage );
	// �ý��� â�� ���
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ERROR, strMessage );
	// �Ҹ� ����
	g_pEngineHandler->HT_hrPlaySound( _DURABLE_WARN_SOUND, _DURABLE_WARN_TIMES );
}

//	��ų�� �� Ÿ���� �Ѱ��ش�
HTint CHTItemSystem::HT_iItemSystem_GetCoolTime( DWORD dwItemKeyID )
{
	return 20;
}

HTvoid CHTItemSystem::HT_vItemSystem_SetMessage( HTint idMessage, CHTString* pstrMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	//------------------------------------------------------------------------------------//
	// ���� - ������ ����, ��������, �Ǹ������� ��� �޼����� �����ϰ�, 
	// �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
	//------------------------------------------------------------------------------------//
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vItemSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemSystem_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vItemSystem_SetParamTextForMessage( sParam3, &szOut3 );

		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vItemSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vItemSystem_SetParamTextForMessage( sParam1, &szOut1 );
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pstrMessage = szString;
}

HTvoid CHTItemSystem::HT_vItemSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// ��Ƽ�� �̸�
		case eMsgParamPartymemberName :
			*pszParam = m_strMsgCharName;
			break;

		// ������ �̸�
		case eMsgParamItemName	:
		{
			HTdword dwIndex = HT_dwSystem_GetItemIndex( m_dwMsgItemKeyID );
			if( dwIndex > 0 )
				g_pParamMgr->HT_bGetItemName( dwIndex, pszParam );
		}
			break;

		default:
			break;
	}
}

//---------------------------------------------------------------------
//	������ ���� ��â ������ �� ����
//---------------------------------------------------------------------	
HTvoid CHTItemSystem::HT_vItemSyste_TribeEquipItemReEquip( HTshort snTribe )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_EQUIP )
		{
			g_pEngineHandler->HT_hrEquipItem( g_cMainCharacter->HT_vMainChar_GetModelID(), snTribe, t->cItem.m_sItemInfo.snIndex );
		}
		t = t->next;
	}
}
