
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTItemSystem.h"

#define _DURABLE_WARN_SOUND		33529
#define _DURABLE_WARN_TIMES		3

#define HT_DURABILITY_WARNING_TIME	120.0f	// 내구도 경고 표시하는 주기

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

//----------아이템 시스템 구현----------//
HTRESULT CHTItemSystem::HT_hrSystemInit()
{
	m_iItem_Count = 0;
	HT_LL_vInitList();

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	return HT_OK;
}

//----------아이템 컨트롤----------//
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
	
	// 내구도 경고가 필요하면
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

//----------AOI 영역 체크----------//
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

//----------그리는 부분---------//
HTRESULT CHTItemSystem::HT_hrSystemRender()
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( GetAsyncKeyState( VK_MENU ) < 0 )
		{
			//----------랜더_이름_3d----------//
			if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP )
				HT_vItemSystem_RenderName( t );
		}

		t = t->next;
	}

	return HT_OK;
}

//----------랜더_이름_3d----------//
HTvoid CHTItemSystem::HT_vItemSystem_RenderName( HT_NODE* t )
{
	HTvector3 vTextPos = t->cItem.m_vecItem3DPosition;
	vTextPos.y += 5;
	if( t->cItem.m_bItem_PickUp_Sw == HT_FALSE )
        g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->cItem.m_strItemName, vTextPos, g_ColorTable[15] ); // white
	else
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->cItem.m_strItemName, vTextPos, g_ColorTable[11] ); // red
}

//----------맵위에 아이템이 나타날 때----------//
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

//----------맵상에서 아이템이 사라진다----------//
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
				if( !CHTParamIDCheck::HT_bIsItemUsableMoney(t->cItem.m_sItemInfo.snIndex) )// 돈이 아닐 경우만
				{
					// 파티가 생성되어있고 파티원이 획득했을 경우
					if( g_cParty->HT_bParty_IsPartyMember( info->szName ) &&
						g_cParty->HT_bParty_GetRootingMode() )
					{
						CHTString szMessage;
						m_dwMsgItemKeyID = t->cItem.m_dwItemKeyID; // 아이템 이름
						m_strMsgCharName = info->szName; // 캐릭터 이름
						HT_vItemSystem_SetMessage( eMsgItemMoveAutoReceive, &szMessage ); // [자동분배]%s,%s 획득
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

//----------3D아이템을 삭제하고 2D 아이템을 가져온다---------//
HTvoid CHTItemSystem::HT_vItemSystem_3DItemHidden( HTint dwItemKeyID )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( dwItemKeyID == t->cItem.m_dwItemKeyID )
		{
			//	아이템 픽했을때 이펙트 지우기
			if( m_iItemTargettingEffectID != 0 )
			{
				g_pEngineHandler->HT_hrStopSFX( m_iItemTargettingEffectID );
				m_iItemTargettingEffectID = 0;
			}

			t->cItem.HT_vItemCreate_Destory();
			//----------2D 아이템을 생성한다.----------//
//			t->cItem.HT_hrSystem_Create2DItem();	// 2003.4.2 선미
			break;
		}
		t = t->next;
	}
}

//----------아이템을 맵에 버린다.---------//
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

//----------맵위에서 아이템을 체크----------//
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

				// HK : 원래는 완전히 아이템 위치까지 가야 아이템을 줍지만,
				// HK : 서버 클라의 NO-Move-Cell 의 오차의 존재를 감안하여
				// HK : 두셀의 오차가 있어도 그냥 주워버리도록 한다.
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

//----------맵위의 픽업된 아이템 초기화----------//
HTvoid CHTItemSystem::HT_vSystem_InitPickUpItemOnMap()
{
	HT_NODE* t;
	t = m_sHead->next;

	//	아이템 픽했을때 이펙트 처리 지운다.
	if( m_iItemTargettingEffectID != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iItemTargettingEffectID );
		m_iItemTargettingEffectID = 0;
	}

	while( t != m_sTail )
	{
		t->cItem.m_bItem_PickUp_Sw	= HT_FALSE;
		//-----아이템 정보 보여주기-----//
		t->cItem.m_bItem_Info_Sw	= HT_FALSE;
		t = t->next;
	}
}

//----------맵셀위에 아이템 검색----------//
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
				//-----아이템 정보 보여주기-----//
				t->cItem.m_bItem_Info_Sw			= HT_TRUE;
				g_pMainBar->HT_vSetObjectTextDraw( t->cItem.m_strItemName );
				return t->cItem.m_iItem3DID;
			}
		}
		t = t->next;
	}

	return 0;
}

//----------아이템의 아이디 비교한다.----------//
HTint CHTItemSystem::HT_iSystem_ComIDCheck( HTint iItemImageID, HTPoint pPt )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItem3DID == iItemImageID )
		{
			//-----아이템 정보 보여주기-----//
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
				//-----아이템 정보 보여주기-----//
				g_pMainBar->HT_vSetObjectTextDraw( t->cItem.m_strItemName );
				return t->cItem.m_iItem3DID;
			}
		}
		t = t->next;
	}

	return 0;
}

//-------맵위의 특정 위치에 아이템이 있는지 검사해서 있으면 HT_TRUE를 리턴---------//
HTRESULT CHTItemSystem::HT_hrCheckMapPos(HTPoint pos)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		//	맵위에 있는 아이템인지 비교
		if( t->cItem.m_iItemLocation == ITEM_LOCATION_MAP && t->cItem.m_iItemInInventory == ITEM_LOCATION_MAP_FIELD)
		{
			// x, z 좌표 비교
			if( t->cItem.m_sItemMapCellX == pos.x && t->cItem.m_sItemMapCellZ == pos.y )
			{
				return HT_TRUE;	// 그 위치에 다른 아이템이 있음
			}
		}
		t = t->next;
	}
	
	return HT_FALSE;
}

//	맵위의 셀좌표를 반환 KeyID
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

//	맵위의 셀좌표를 반환 ModelID
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

//----------기존의 아이템 지울때---------//
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

//----------아이템 전부를 삭제----------//
HTvoid CHTItemSystem::HT_vItemSystem_TotalItemDelete()
{
	// LL 데이타 전부 지우기
	HT_LL_hrDeleteAll();
}

//----------아이템을 삭제한다.---------//
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

//----------인벤토리 내의 아이템 전부를 삭제----------//
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

//----------인벤토리 내의 특정 index의 아이템 전부를 삭제----------//
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

//----------인벤토리 내의 특정 type의 아이템 전부를 삭제---------//
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

//----------아이템이 이동(장착)될 수 있는 인벤토리인가?----------//
HTint CHTItemSystem::HT_iItemAlSetPosInventoryCheck( DWORD dwKeyID, DWORD dwItemIndex, HT_ITEMSETTING_FLAG sSetItem )
{
	if( dwItemIndex <= 0 )	// 잘못된 index일 경우 
		return HT_RESULT_ITEM_MOVE_FAIL;

	// 아이템 크기 구하기
	HTbyte byItemSizeX = 1, byItemSizeZ = 1;
	HTPoint ptSize;
	// PC 인벤토리일 경우 활성화되어있는 크기 구하기
	if( sSetItem.nLocation == ITEM_LOCATION_PC )
	{
		// BAG2를 사용할 수 없을 경우
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
	
	//	아이템을 이동할수 있는 공간 이상이면 불가
	if( sSetItem.pCellPos.x+byItemSizeX > ptSize.x || sSetItem.pCellPos.y+byItemSizeZ > ptSize.y )
	{
		return HT_RESULT_ITEM_MOVE_FAIL;
	}

	// 기존의 아이템과 겹치는지 파악
	HT_NODE* t;
	t = m_sHead->next;

	//	4_1. 아이템 노드를 검색
	while( t != m_sTail )
	{
		//	4_2. 아이템이 들어갈수 있는 방과 인벤토리가 같은건지 비교
		if( sSetItem.nLocation == t->cItem.m_iItemLocation && sSetItem.nInventory == t->cItem.m_iItemInInventory )
		{
			//	4_3. 인벤토리의 크기(x,y)를 전부 검색
			for( HTint x=sSetItem.pCellPos.x ; x<sSetItem.pCellPos.x+byItemSizeX ; ++x )
			{
				for( HTint y=sSetItem.pCellPos.y ; y<sSetItem.pCellPos.y+byItemSizeZ ; ++y )
				{
					//	4_4. 아이템의 크기와 비교 해서 빈칸을 찾아냄
					// 검색하는 위치에 아이템이 있는지 없는지를 검사하고, 있을 경우 패킹 가능한 아이템인지 아닌지 검사한다.
					if( x>=t->cItem.m_byInventory_CellPosX && x<t->cItem.m_byInventory_CellPosX+t->cItem.m_byItemSizeX 
					 && y>=t->cItem.m_byInventory_CellPosY && y<t->cItem.m_byInventory_CellPosY+t->cItem.m_byItemSizeY )
					{
						// 중첩가능한 아이템이면
						HTbyte byteMaxCount = 0;
						if( g_pParamMgr->HT_bGetItemMaxCount(dwItemIndex, &byteMaxCount) == false )
							return HT_RESULT_ITEM_MOVE_FAIL;

						if( t->cItem.m_dwItemKeyID != dwKeyID && (dwItemIndex == t->cItem.m_sItemInfo.snIndex) && (byteMaxCount > 1) )
						{	//	4_5. 최대 중첩개수보다 작으면
							if( t->cItem.m_sItemInfo.byCount < byteMaxCount )
								return t->cItem.m_dwItemKeyID;
							//	4_6. 이동(장착)불가 리턴
							else
                                return HT_RESULT_ITEM_MOVE_FAIL;
						}
						// 중첩 불가능한 다른 아이템이 있을 경우
						else if( t->cItem.m_dwItemKeyID == dwKeyID )	// 자기 자신일 경우
						{
							//continue;
							//return HT_RESULT_ITEM_MOVE_OK;
							return HT_RESULT_ITEM_MOVE_FAIL;	//	4_6. 이동(장착)불가 리턴
						}
						else
							return HT_RESULT_ITEM_MOVE_FAIL;	//	4_6. 이동(장착)불가 리턴
					}
				}
			}
		}
		t = t->next;
	}

	//	5. 걸리는 사항이 없으면 투루 리턴
	return HT_RESULT_ITEM_MOVE_OK;
}

//---------- 인벤토리에 빈공간의 갯수 검사 ----------//
HTint CHTItemSystem::HT_iItemAlSetPosInventoryBlankCheck()
{
	HTint iBlankNumber = 0;		// 인벤토리 공간 세기

	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	// 사용한 공간 계산
	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == ITEM_LOCATION_PC) // 개인 인벤토리 공간인가?
			if( s->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG1 || 
				s->cItem.m_iItemInInventory == ITEM_LOCATION_PC_BAG2 && g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_TRUE )
				iBlankNumber++;
	}

	HTint MaxBlank;	// 최대공간 계산
	if( g_cEquipInventory->HT_bGetInventoryUsable( ITEM_LOCATION_PC_BAG2 ) == HT_TRUE )
     {
		 MaxBlank = g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) * _INVEN_HEIGHT +
			 g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG1) * _INVEN_HEIGHT;
	 }
	else
		 MaxBlank = g_cEquipInventory->HT_byGetInventorySize(ITEM_LOCATION_PC_BAG2) * _INVEN_HEIGHT;


	// 빈공간 반환
	return (MaxBlank - iBlankNumber);
}

//---------- 인벤토리에 빈공간의 갯수 검사 ----------//
HTint CHTItemSystem::HT_iItemAlSetPosGoodsKeepBlankCheck()
{
	HTint iBlankNumber = 0;		// 인벤토리 공간 세기

	HT_NODE *t;
	HT_NODE *s;
	t = m_sHead->next;

	// 사용한 공간 계산
	while( t != m_sTail )
	{
		s = t;
		t = t->next;

		if( s->cItem.m_iItemLocation == ITEM_LOCATION_NPC) // 창고 인벤토리 공간인가?
			if( s->cItem.m_iItemInInventory == ITEM_LOCATION_NPC_ITEMSAVED )
				iBlankNumber++;
	}

	HTint MaxBlank;	// 최대공간 계산
	MaxBlank = _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT;


	// 빈공간 반환
	return (MaxBlank - iBlankNumber);
}

//---------- 아이템 착용이 가능한지 알아낸다. : HT_FALSE - 착용 불가능 HT_TRUE - 착용가능----//
HTbool CHTItemSystem::HT_bItemSystem_GetPossible(DWORD dwItemKeyID, HTbool bLevelCheck )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		// 아이템 옵션에 의해 차크라를 높여서 아이템을 착용했을 경우 옵션 제거후에도 아이템이 착용된 
		// 상태가 있기 때문에 다시 검사해서 리턴.
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
			return t->cItem.HT_bItemAl_PossibleCheck( t->cItem.m_sItemInfo.snIndex, bLevelCheck );

		t = t->next;
	}

	return HT_FALSE;
} 

//---------- 해당 Index의 아이템이 개인 인벤토리의 해당 칸에 얼마나 존재 하는지 갯수 반환
HTint CHTItemSystem::HT_bItemSystem_GetPossible2(DWORD dwIndex, HTint iPos )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_sItemInfo.snIndex == dwIndex )	// 같은 종류의 아이템을 발견했다면 해당 위치가 맞는지 조사
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
			// 무기
			if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_TWO_HAND && 
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_HAND || nLocation == ITEM_LOCATION_EQUIP_LEFT_HAND ) )
				return HT_TRUE;
			// 귀걸이
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_EAR &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_EAR || nLocation == ITEM_LOCATION_EQUIP_LEFT_EAR) )
				return HT_TRUE;
			// 팔찌
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_BRACELET &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_BRACELET || nLocation == ITEM_LOCATION_EQUIP_LEFT_BRACELET) )
				return HT_TRUE;
			// 반지
			else if( t->cItem.m_byItemEquipPos == ITEM_LOCATION_EQUIP_RIGHT_RING &&
							( nLocation == ITEM_LOCATION_EQUIP_RIGHT_RING || nLocation == ITEM_LOCATION_EQUIP_LEFT_RING) )
				return HT_TRUE;
			// 인벤토리 확장용 아이템
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

//----------인벤토리내의 아이템 셋팅하기----------//
HTvoid CHTItemSystem::HT_vItemSystem_SettingInventoryPos( HTint iItemKeyID, HT_ITEMSETTING_FLAG flag, HTbool bDrawTwinImage)
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == iItemKeyID )
		{
			//	아이템 셋팅
            t->cItem.HT_vItemAlSettingInventoryPos( flag , bDrawTwinImage);
			break;
		}

		t = t->next;
	}
}

//---------- 인벤토리에 있는 아이템의 착용가능/불가능 바 갱신 -------------//
HTvoid CHTItemSystem::HT_vItemSystem_RenewalPossibleBar(HTint nDlgNo)
{
	// 착용가능/불가능바를 갱신할 아이템들은 PC/NPC인벤토리에 있는 것들 뿐이다.
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
			if( t->cItem.m_bPossible != bPossible )	// 변했을 경우에만 갱신
			{
				t->cItem.m_bPossible = bPossible;
			}
		}
		t = t->next;
	}
}	

//----------아이템의 모델 아디를 얻어온다.---------//
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

//  아이템 데이터 얻기
HTbool CHTItemSystem::HT_bItemSystem_GetItemInfo( DWORD dwItemKeyID, STRUCT_ITEM& sItem )
{
	HT_NODE* t;

	t = m_sHead->next;
	while( t != m_sTail )
	{
		//-----캐릭터와 아이템 셀위치 비교-----//
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

//---------- 장착한 아이템의 키아이디를 얻어온다.----------//
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

//----------아이템의 모델 아이디로부터 키아이디를 얻어온다.----------//
DWORD CHTItemSystem::HT_dwSystem_GetItemKeyFromModelID( HTint nItemModelID, HTbool bPickCheck )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{
		if( t->cItem.m_iItem3DID == nItemModelID )
		{
			//	아이템 픽했을때 이펙트 처리
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

//----------아이템의 인벤토리 위치로 KeyID를 얻어온다------------//
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

//----------셀위에 있는 아이템의 KeyID를 얻어온다.---------//
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

//----------아이템과 마우스 포인터를 검색하여 아이템 인데스를 리턴---------//
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

//----------아이템 포지션과 인벤토리 셀좌표를 계산하여 아이템 찾기---------//
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
// 아이템 포지션과 인벤토리 셀좌표를 계산하여 아이템 KeyID찾기 
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

//----------인덱스로 PC인벤토리내 가장 처음 검색되는 아이템의 KeyID를 얻어온다.-----------//
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

//--------- 특정 위치(iLocation)에 자신을 제외한 같은 종류의 아이템 KeyID, 위치 반환---------//
HTvoid CHTItemSystem::HT_vItemSystem_GetItemPos( DWORD dwItemIndex, DWORD dwActiveItemKeyID, HTint iLocation, DWORD& dwItemKeyID, HT_ITEMSETTING_FLAG& sLocRoom )
{
	HT_NODE* t;
	t = m_sHead->next;

	while( t != m_sTail )
	{	// 같은 장소에서 자신을 제외한 같은 종류의 아이템인가
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

//----------마우스 포인트를 넘겨받아 활성화된 아이템중에 포인트 위치에 있는것의 키아디를 반환----------//
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
//			if(g_cInterfaceCheck->HT_iGetCursor() != CURSOR_HAND)	//손모양 => 부하 체크 후로 보류 2003.1.14
//				g_cInterfaceCheck->HT_vSetCursor(CURSOR_HAND);

			if(t->cItem.m_bItemActive == HT_TRUE)
				return -1;	// 현재 아이템이 이동 중이라면 정보창을 표시 하지 않는다.

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

//---------------- 아이템의 KeyID로 Index와 type, 크기를 반환 -----------------------//
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

//----------아이템의 키이디로 인덱스를 얻어온다----------//
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

//---------- 아이템 이름 획득----//
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

//--------아이템 타입 얻어온다----------------//
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

// 아이템 KeyID로 현재 위치 알아오기
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

//----------아이템의 인벤토리 셀 위치를 반환.----------//
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

//----------중첩 아이템이 있는지 판단---------//
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

//----------중첩 아이템 증가---------//
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

//----------중첩 아이템 감소---------//
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

//----------아이템의 키이디로 아이템의 겟수를 얻어온다----------//
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

//----------아이템의 키이디로 아이템의 최대 중첩 개수를 얻어온다----------//
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

//----------인벤토리 안에있는 특정 아이템(Index)의 총 개수를 얻어온다----------//
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

//----------중첩 아이템의 겟수를 셋팅해준다----------//
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


//----------아이템을 사이즈를 반환.----------//
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

//----------아이템의 셀 번호를 반환.----------//
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
 
//-------아이템을 새로 생성하거나 삭제--------//
HTvoid CHTItemSystem::HT_vItemSystem_ItemSet( PS_SCP_RESP_ITEM_SET info )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0;
	HT_NODE *s = NULL;
	if( info->sitem.snIndex > 0 ) 
	{
		// KeyID 생성
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);

		switch( info->byPlace )
		{
			case ITEM_PLACE_INVEN :
			{
				// (기존의) 아이템 지움
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
				//(기존의) 아이템 지움
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
				//(기존의) 아이템 지움
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
				// (기존의) 아이템 지움
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
				// (기존의) 아이템 지움
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
				// (기존의) 아이템 지움
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
		// 아이템 생성할 때만
		if( info->byType == SET_ITEM_CREATE )
		{
			s->next = m_sHead->next;
			m_sHead->next = s;
		}
		// 보조재료 정보 
		HT_bItemSystem_SetSubRefineItem( iKeyID, info->sitem.bySubRefine );
	}
}
//	아쉬람 창고에 아쉬람 셋팅
HTvoid CHTItemSystem::HT_vItemSystem_CreateAshramCargo( HTbyte byPlace, HTshort snIndex, STRUCT_ITEM oItem )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0;
	HT_NODE *s = NULL;

	// KeyID 생성
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), byPlace, snIndex, iKeyID);
	//(기존의) 아이템 지움
	HT_LL_vInsertAfter_ItemDelete( iKeyID );

	s = new HT_NODE;
	byX = ( snIndex ) % _GOODSKEEP_INVEN_WIDTH; 
	byZ = ( snIndex ) / _GOODSKEEP_INVEN_WIDTH;
	s->cItem.HT_vItemCreate( ITEM_LOCATION_ASHRAMCARGO, byX, byZ, iKeyID, oItem );

	s->next = m_sHead->next;
	m_sHead->next = s;

	// 보조재료 정보 
	this->HT_bItemSystem_SetSubRefineItem( iKeyID, oItem.bySubRefine );
}
//-------------- PC인벤토리에 아이템 생성 ------------//
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
			// 아이템의 index는 무기 index로 시작한다
			//iItemIndex = HT_ITEM_INDEX_START + arrInven[i].snIndex;
			// KeyID 생성
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, i, iKeyID);
			//기존의 아이템 지움
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

			// 보조재료 정보 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrInven[i].bySubRefine );
		}
	}
}
//------------- 장착 아이템 생성 -----------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateEquip( STRUCT_ITEM arrEquip[MAX_EQUIP] )
{
	HTint iKeyID = 0, iItemIndex = 0;
	HTbool bInitInven = HT_FALSE;
	HTint iSubRefineLevel = 0;

	for( int i = 0 ; i < MAX_EQUIP ; ++i )
	{
		if( arrEquip[i].snIndex > 0 )
		{
			// 아이템의 index는 무기 index로 시작한다
			//iItemIndex = HT_ITEM_INDEX_START + arrEquip[i].snIndex;
			// KeyID 생성
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, i, iKeyID);
			//기존의 아이템 지움
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			s->cItem.HT_vItemCreate( i, iKeyID, arrEquip[i] );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// 보조재료 정보 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrEquip[i].bySubRefine );
			
			// 장착한 무기 아이템 FX 설정
			iItemIndex = arrEquip[i].snIndex + HT_ITEM_INDEX_START;
			if( CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex ) )
			{
				// 메인 제련이 되어 있는 (무기) 아이템의 FX 설정
				if( arrEquip[i].byRefineLevel > 0 )
					g_pEngineHandler->HT_hrAttachItemMainRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), 
																		iItemIndex, arrEquip[i].byRefineLevel );

				// 속성 제련 되어 있는 (무기) 아이템의 경우
				iSubRefineLevel = this->HT_iItemSystem_GetSubRefineLevel( iKeyID );
				if( iSubRefineLevel > 0 )
				{
					HTint iAttribute = this->HT_iItemSystem_GetAttributeSubRefineItem( iKeyID );
					// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
					g_pEngineHandler->HT_hrAttachItemSubRefineEffect( g_cMainCharacter->HT_vMainChar_GetModelID(), iItemIndex,
																		(HTESubRefineType)iAttribute, iSubRefineLevel );
				}
			}

			//	토템 아이템의 경우 서정거리 적용하기
			if( (arrEquip[i].snIndex+HT_PARAMTYPE_ITEM_START-1) == HT_INDEX_TOTEM_JACUNAEARANI )
			{
				int iRange = 0;
				g_pParamMgr->HT_bGetItemEffect1Param1( (arrEquip[i].snIndex+HT_PARAMTYPE_ITEM_START-1), &iRange );
				g_cMainCharacter->HT_vMainChar_SetTotemItemRange( iRange );
			}

			// 인벤토리 사이즈 초기화
			//if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven( iItemIndex ) )
			//{
			//	g_cEquipInventory->HT_vInitBagStatus( arrEquip[i].snIndex );
			//	bInitInven = HT_TRUE;
			//}
		}
	}
	// 인벤토리 사이즈 초기화 못했으면
	//if( bInitInven == HT_FALSE )	
	//	g_cEquipInventory->HT_vInitBagStatus( 0 );

	HT_vItemSystem_RenewalDurabilityWarning();
}
//----------창고에 아이템 생성----------//
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemCreateNPCInven( STRUCT_ITEM arrNPCInven[MAX_CARGO] )
{
	HTbyte byX = 0, byZ = 0, byBagID = 0;
	HTint iKeyID = 0, iItemIndex = 0;
	for( int i = 0 ; i < MAX_CARGO ; ++i )
	{
		if( arrNPCInven[i].snIndex > 0 )
		{
			// 아이템의 index는 무기 index로 시작한다
			//iItemIndex = HT_ITEM_INDEX_START + arrNPCInven[i].snIndex;
			// KeyID 생성
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_CARGO, i, iKeyID);
			//기존의 아이템 지움
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

			// 보조재료 정보 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrNPCInven[i].bySubRefine );
		}
	}
}
//	아쉬람 창고 관련
HTvoid CHTItemSystem::HT_LL_vInsertAfter_ItemDeleteAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo )
{
	HTint iKeyID = 0;
	for( int i = 0 ; i < MAX_CARGO ; ++i )
	{
		if( arrAshramCargo[i].snIndex > 0 )
		{
			// KeyID 생성
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, i+(iCargoNo*120), iKeyID);
			//기존의 아이템 지움
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
			// KeyID 생성
			iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, i+(iCargoNo*120), iKeyID);
			//기존의 아이템 지움
			HT_LL_vInsertAfter_ItemDelete( iKeyID );

			HT_NODE *s;
			s = NULL;
			s = new HT_NODE;
			byX = ( i+(iCargoNo*120) ) % _GOODSKEEP_INVEN_WIDTH; 
			byZ = ( i+(iCargoNo*120) ) / _GOODSKEEP_INVEN_WIDTH;
			s->cItem.HT_vItemCreate( ITEM_LOCATION_ASHRAMCARGO, byX, byZ, iKeyID, arrAshramCargo[i] );
			s->next = m_sHead->next;
			m_sHead->next = s;

			// 보조재료 정보 
			HT_bItemSystem_SetSubRefineItem( iKeyID, arrAshramCargo[i].bySubRefine );
		}
	}
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid CHTItemSystem::HT_LL_vInitList()
{
	m_sHead = NULL;
	m_sTail = NULL;

	m_sHead = new HT_NODE;
	m_sTail = new HT_NODE;

	m_sHead->next = m_sTail;
	m_sTail->next = m_sTail;
}

//----------LL 데이타 지우기---------//
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

//----------LL 데이타 전부 지우기---------//
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
//	아이템 KeyID로 아이템 모든 정보(STRUCT_ITEM) 얻기
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
// 예외 - 아이템 정보의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
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
			
			// 아이템 정보 Lock 설정
			if( g_pParamMgr->HT_bLockID(t->cItem.m_sItemInfo.snIndex) == false )
				return winSizeX;

			HTint iOut = 0;
			HTshort sOut = 0;

			// 아이템 이름
			vInfo.strName.str = t->cItem.m_strItemName;
			// 장착용 아이템일 경우만 제련 정도를 표시한다.
			if( t->cItem.m_sItemInfo.byRefineLevel > 0)
			{
				str.HT_szFormat("+%d", t->cItem.m_sItemInfo.byRefineLevel);
				vInfo.strName.str += str;
			}
			winSizeX = vInfo.strName.str.HT_nGetSize();

			// 아이템 타입(특성에 따른 분류)
			// 유니크아이템
			if( CHTParamIDCheck::HT_bIsItemUnique( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.58f, 0.35f, 0.99f, 1.0f);	// 보라
			// 레어아이템
			else if( CHTParamIDCheck::HT_bIsItemRare( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.82f, 0.71f, 0.44f, 1.0f);	// 노랑
			// 퀘스트 아이템
			else if( CHTParamIDCheck::HT_bIsItemQuest( t->cItem.m_sItemInfo.snIndex ) )		
				vInfo.strName.color = HT_COLOR(0.54f, 0.52f, 1.0f, 1.0f);	// 남보라
			//  일반아이템
			else																			
				vInfo.strName.color = g_ColorTable[15];		// white

			// 아이템 설명
			g_pParamMgr->HT_bGetItemDescription( &vInfo.strDescription.str );
			switch (t->cItem.m_sItemInfo.snIndex)
			{
				case 7064:	// 프리미엄 꾸러미 아이템들은 세부 설명을 해준다.
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem15, &strTemp, _T("") );		//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 부적의 효과"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7065:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem16, &strTemp, _T("") );		//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아트만 부적의 효과"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7066:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem17, &strTemp, _T("") );		//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7067:
					{
						HT_g_Script_SetMessage( eMsgExPlanPremiumItem18, &strTemp, _T("") );		//	"고급 생명의 주문서 1개\n생명의 주문서 20개\n전광판 아이템 10개\n작전 명령서 5개\n이벤트기간에 사용시 이벤트 아이템 지급\n\n30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과\n4. 모든 차크라 15 상승"
						vInfo.strDescription.str.HT_szFormat(strTemp);
						
						pData = new HT_ITEM_DATA;
						pData->color = g_ColorTable[16]; 
						HT_g_Script_SetMessage( eMsgExPlanPremiumItem23, &strTemp, _T("") );
						pData->str = strTemp;

						vInfo.vSourceStr.push_back(pData);
					}
					break;
				case 7069:
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem19, &strTemp, _T("") );		//	"요술램프 1개\n(파미르지역에서 보스몬스터 랜덤 소환가능)\n요술망치 2개\n(장비중인 모든아이템 내구도수리)\n차투랑가 입장권 2개\n(차투랑가로 바로 입장가능)\n이벤트 우타라 암리타 250개 2묶음\n고급 생명의 주문서 2개"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7073:	// 아이원잇
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );		//	"6만 5천 컬러 LCD / 듀얼 이어폰 '아이원잇 TMP-1000'>>http://www.ioneit.com"
					vInfo.strDescription.str.HT_szFormat(strTemp);
					break;
				case 7079:	//컴리드
					//HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );		//	"6만 5천 컬러 LCD / 듀얼 이어폰 '아이원잇 TMP-1000'>>http://www.ioneit.com"
					vInfo.strDescription.str.HT_szFormat("COMRADE GeForce 6600 3.3ns그래픽 카드>>>>300MHz RAM DAC>>128MB RAM SPEED 400MHz 3.3ns>>DVI-1 듀얼 디스플레이 지원>>보증기간: 2년>>>>대용량 저발열의 고성능 쿨러, S-Video 케이블, 한글설명서>>>>㈜ 마이크로사운드>>http://www.microsound.co.kr>>라훌에서 등록가능");
					break;
				case 6555: // 비카리
					vInfo.strDescription.str.HT_szFormat("- 주술제련 아이템의 제한부위 해제\n- 제련시 기존의 속성은 초기화되며\n     첨가된 제련재료의 속성을 부여\n\n- 모든 무기, 방어구에 첨가 가능");
					break;
			}

			if( vInfo.strDescription.str == HT_INFO_ITEM_DESCRIPT_NULL )
				vInfo.strDescription.str.HT_hrCleanUp();
			else
				vInfo.strDescription.color = g_ColorTable[16]; //light grey


			// 꾸러미 아이템의 경우는 X사이즈를 최대한 넓힌다.
			if(t->cItem.m_sItemInfo.snIndex >= 7064 && t->cItem.m_sItemInfo.snIndex <= 7067 || t->cItem.m_sItemInfo.snIndex == 7069 || t->cItem.m_sItemInfo.snIndex == 7073 || t->cItem.m_sItemInfo.snIndex == 7079 || t->cItem.m_sItemInfo.snIndex == 6555)
			//if(t->cItem.m_sItemInfo.snIndex >= 7064 && t->cItem.m_sItemInfo.snIndex <= 7067 || t->cItem.m_sItemInfo.snIndex == 7069 || t->cItem.m_sItemInfo.snIndex == 7079)
			{
				winSizeX = 40;
				vInfo.strName.color = g_ColorTable[17];		// white
				vInfo.strDescription.color = g_ColorTable[15]; //light grey

			}


			// 제련할 경우 제련용 아이템과 주술제련 초기화 아이템은 표시 안하기 위해. 
			if( bType == NPC_ITEM_REFINING && !CHTParamIDCheck::HT_bIsItemRefine( t->cItem.m_sItemInfo.snIndex )
				&& t->cItem.m_sItemInfo.snIndex != HT_INDEX_INIT_SUB_REFINE )	
			{
				HTint iRupiah; // 아이템 가격
				g_pParamMgr->HT_bGetItemRupiah( &iRupiah );

				// 주술제련 레벨
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
						bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	상위4비트 리드
						if( bySubItemIndex > 0 )
							++iSubRefine;
						bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	하위4비트 리드
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
					// 제련 불가
					HT_vItemSystem_SetMessage( eMsgItemInfoCannotRefine, &pData->str );

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				else
				{
					HTint iNeedRupiah = HT_iItemSystem_GetRupiahForItemWork( t->cItem.m_sItemInfo.byRefineLevel, iRupiah );
					// 강화제련 가능 횟수
					HTint iMainRefine = MAX_REFINE_MAIN_LEVEL - t->cItem.m_sItemInfo.byRefineLevel;
					if( iMainRefine < 0 )	iMainRefine = 0;
					// 주술제련 가능 횟수
					HTint iRemainSubRefine = MAX_REFINE_SUB_LEVEL - iSubRefine;
					if( iRemainSubRefine < 0 )	iRemainSubRefine = 0;

					if( iNeedRupiah > 0 )
					{
						//-------루피아--------//
						pData = new HT_ITEM_DATA;
						pData->color = g_ColorTable[17]; //yellow
						// %s 루피아, iNeedRupiah
						HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);
						
						CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // 쉼표 처리
						pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
						vInfo.vSourceStr.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						//------강화제련-------//
						//pData = new HT_ITEM_DATA;
						//if( iMainRefine <= 0 )
						//{
						//	pData->color = g_ColorTable[11]; //red
						//	// 강화제련 불가
						//	HT_vItemSystem_SetMessage( eMsgItemInfoCannotMainRefine, &pData->str);
						//}
						//else
						//{
						//	pData->color = g_ColorTable[17];	// yellow
						//	// 강화제련 가능 횟수 %d회
						//	HT_vItemSystem_SetMessage( eMsgItemInfoRemainMainRefine, &str);
						//	pData->str.HT_szFormat( str.HT_szGetString(), iMainRefine );
						//}
						//vInfo.vSourceStr.push_back(pData);
						//winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						////--------주술제련---------//
						//pData = new HT_ITEM_DATA;
						//if( iRemainSubRefine <= 0 )
						//{
						//	pData->color = g_ColorTable[11]; //red
						//	// 주술제련 불가
						//	HT_vItemSystem_SetMessage( eMsgItemInfoCannotSubRefine, &pData->str);
						//}
						//else
						//{
						//	pData->color = g_ColorTable[17];	// yellow
						//	// 주술제련 가능 횟수 %d회
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
						// 제련 불가
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotRefine, &pData->str );

						vInfo.vSourceStr.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			else if( bType == NPC_ITEM_SELL ) // 개인 상점용
			{
				//루피아
				HTint iRupiah = g_cIndividualStore->HT_iIndividualStore_GetRupiah( dwKeyID );
				if( iRupiah > 0 )	
				{
					pData = new HT_ITEM_DATA;
					// %s 루피아
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iRupiah ); // 쉼표 처리
					pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
					if( iRupiah >= 10000000 )
						pData->color = g_ColorTable[11]; //red
					else if( 1000000 <= iRupiah && iRupiah < 10000000 )
						pData->color = g_ColorTable[12];	// yellow
					else if( 100000 <= iRupiah && iRupiah < 1000000 )
						pData->color = g_ColorTable[7 ];	// 주황
					else if( 10000 <= iRupiah && iRupiah < 100000 )
						pData->color = g_ColorTable[17];	// 연노랑
					else
						pData->color = g_ColorTable[15];		// white

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
			}
			else if(bType == NPC_ITEM_RENTAL_SELL && g_cRentalStore->m_nWindowType != 2)	// 위탁판매용
			{
				//루피아
				int Xid = g_cObjectInfo->nControlIndex-_RENTALSTORE_INVEN_BEGIN;
				HTint iRupiah = g_cRentalStore->ItemList[Xid].dwPrice;
				if( iRupiah > 0 )	
				{
					pData = new HT_ITEM_DATA;
					// %s 루피아
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &str);

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iRupiah ); // 쉼표 처리
					pData->str.HT_szFormat( str.HT_szGetString(), szMoney.HT_szGetString() );
					
					if( iRupiah >= 10000000 )
						pData->color = g_ColorTable[11]; //red
					else if( 1000000 <= iRupiah && iRupiah < 10000000 )
						pData->color = g_ColorTable[12];	// yellow
					else if( 100000 <= iRupiah && iRupiah < 1000000 )
						pData->color = g_ColorTable[7 ];	// 주황
					else if( 10000 <= iRupiah && iRupiah < 100000 )
						pData->color = g_ColorTable[17];	// 연노랑
					else
						pData->color = g_ColorTable[15];		// white

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());

					//HTint iHour, iMinute;

					// 남은 기간 표시
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					pExtData->basic.color = g_ColorTable[17]; //yellow

					time_t totaltime;
					CHTString vstr;
					totaltime = g_cRentalStore->ItemList[Xid].dwTime;
					tm* psTmTime = localtime( &totaltime );

					//g_cUIManager->HT_SetScriptMessage( eMsgCommonUntilAshramCargo, &str, _T(""), _T("") );	//	사용중
					vstr.HT_szFormat("%d.%d.%d(%d:%02d) 까지", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday, psTmTime->tm_hour, psTmTime->tm_min);
					pExtData->basic.str = vstr;//.HT_szFormat( vstr.HT_szGetString() );

					// 나의 위탁상점을 보고 있다면 어떤 상점에 위탁했는지도 알려주는 센쓰~
					if (g_cRentalStore->m_nWindowType == 0)
					{
						CHTString gstr;
						int tindex = g_cRentalStore->m_wIndex[Xid];
						int iStoreIndex = (tindex / MAX_USERRENTALITEM);
						//int dwIndex = (tindex % MAX_USERRENTALITEM);

						gstr.HT_szFormat("위탁위치:%d", iStoreIndex+1);
						pExtData->basic.str = vstr + _T(", ") + gstr;
					}
					/*
					iMinute = (g_cRentalStore->ItemList[Xid].dwTime - now ) / 60;
					iHour = (iMinute / 60);
					iMinute = (iMinute % 60);

					if (iHour != 0 && iMinute != 0 )
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoHourMinute, &str);	// 유효시간 %d시간 %d분
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour , iMinute );
					}
					else if (iMinute != 0)
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoMinute, &str);	// 유효시간 %d분
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iMinute );
					}
					else
					{
						HT_vItemSystem_SetMessage( 	eMsgItemInfoHour, &str);	// 유효시간 %d시간
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour );
					}
					*/
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
				}
			}

			// 중첩된 개수
			HTint iCount = 0;
			if( bType == NPC_ITEM_SELL && g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ))
				iCount = g_cIndividualStore->HT_iIndividualStore_GetPackCount( dwKeyID );
			else
				iCount = t->cItem.m_sItemInfo.byCount;

			// 지속아이템인지 검사
			if (CHTParamIDCheck::HT_bIsItemChargeContinuance(t->cItem.m_sItemInfo.snIndex) == TRUE)
			{
				HTint iHour, iMinute;

				// 남은 기간 표시
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
				pExtData->basic.color = g_ColorTable[17]; //yellow

				iMinute = iCount;
				iHour = iMinute / 60;
				iMinute = iMinute % 60;

				if (iHour != 0 && iMinute != 0 )
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoHourMinute, &str);	// 유효시간 %d시간 %d분
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iHour , iMinute );
				}
				else if (iMinute != 0)
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoMinute, &str);	// 유효시간 %d분
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iMinute );
				}
				else
				{
					HT_vItemSystem_SetMessage( 	eMsgItemInfoHour, &str);	// 유효시간 %d시간
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
					// 중첩개수 %d
					HT_vItemSystem_SetMessage( eMsgItemInfoPackCount, &str);
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iCount );

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
				}
			}

			

			//-----착용제한사항------//
			if( g_pParamMgr->HT_bGetItemLimitTrimuriti( &iOut ) == true && iOut > 0 )
			{
				HTRESULT trimuriti = HT_FALSE;
				str.HT_hrCleanUp();

				pData = new HT_ITEM_DATA;
				if( BIT_AND( TRIMURITI_BRAHMA, iOut ) )
				{
					//str = "브라흐마"; 
					HT_vItemSystem_SetMessage( eMsgCommonTrimuritiBrahma, &pData->str);
					trimuriti = HT_TRUE;
				}
				if( BIT_AND( TRIMURITI_VISHNU, iOut ) )
				{
					if(trimuriti) //str += ", 비슈누";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiVishunu, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str = "비슈누";
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiVishunu, &pData->str);
					trimuriti = HT_TRUE;
				}
				if( BIT_AND( TRIMURITI_SIVA, iOut ) )
				{
					if(trimuriti) //str += ", 시바";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiSiva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "시바";
						HT_vItemSystem_SetMessage( eMsgCommonTrimuritiSiva, &pData->str);
					trimuriti = HT_TRUE;
				}

				//str += " 전용";
				HT_vItemSystem_SetMessage( eMsgItemInfoPrivateUse, &str);
				pData->str = pData->str + _T(" ") + str;

				if( BIT_AND( g_oMainCharacterInfo.byTrimuriti, iOut ) )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			if( g_pParamMgr->HT_bGetItemLimitTribe( &iOut ) == true && iOut > 0)		// 종족제한
			{
				HTRESULT tribe = HT_FALSE;
				str.HT_hrCleanUp();

				pData = new HT_ITEM_DATA;
				if( BIT_AND( TRIBE_NAGA, iOut ) )
				{
					//str = "나가"; 
					HT_vItemSystem_SetMessage( eMsgCommonTribeNaga, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_ASURA, iOut ) )
				{
					if(tribe) //str += ", 아수라";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeAsura, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str = "아수라";
						HT_vItemSystem_SetMessage( eMsgCommonTribeAsura, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_YAKSA, iOut ) )
				{
					if(tribe) //str += ", 야크사";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeYaksha, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "야크사";
						HT_vItemSystem_SetMessage( eMsgCommonTribeYaksha, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_DEVA, iOut ) )
				{
					if(tribe) //str += ", 데바";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeDeva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "데바";
						HT_vItemSystem_SetMessage( eMsgCommonTribeDeva, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_KINNARA, iOut ) )
				{
					if(tribe) //str += ", 킨나라";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeKimnara, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "킨나라";
						HT_vItemSystem_SetMessage( eMsgCommonTribeKimnara, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_RAKSHASA , iOut ) )
				{
					if(tribe) //str += ", 라크샤사";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeRakshasa, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "라크샤사";
						HT_vItemSystem_SetMessage( eMsgCommonTribeRakshasa, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_GANDHARVA, iOut ) )
				{
					if(tribe) //str += ", 간다르바";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeGandharva, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "간다르바";
						HT_vItemSystem_SetMessage( eMsgCommonTribeGandharva, &pData->str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( TRIBE_GARUDA, iOut ) )
				{
					if(tribe) //str += ", 가루다";
					{
						HT_vItemSystem_SetMessage( eMsgCommonTribeGaruda, &str);
						pData->str = pData->str + _T(", ") + str;
					}
					else	//str += "가루다";
						HT_vItemSystem_SetMessage( eMsgCommonTribeGaruda, &pData->str);
					tribe = HT_TRUE;
				}
				
				//str += " 전용";
				HT_vItemSystem_SetMessage( eMsgItemInfoPrivateUse, &str);
				pData->str = pData->str + _T(" ") + str;

				if( BIT_AND( g_cMainCharacter->HT_iMainChar_GetTribeServerCode(), iOut ) )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// 레벨
			HTbyte byLimitLevel = 0;
			if( g_pParamMgr->HT_bGetItemLimitLevel( &byLimitLevel ) == true && byLimitLevel > 0 )
			{
				pData = new HT_ITEM_DATA;

				// Level %d필요
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
				//pData->str.HT_szFormat("근육의 차크라 %d", sOut);		// 근육의 차크라
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
				//pData->str.HT_szFormat("신경의 차크라 %d", sOut);		// 신경의 차크라
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
				//pData->str.HT_szFormat("심장의 차크라 %d", sOut);		// 심장의 차크라
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
				//pData->str.HT_szFormat("정신의 차크라 %d", sOut);		// 정신의 차크라
				HT_vItemSystem_SetMessage( eMsgItemInfoSoulChakra, &str);
				pData->str.HT_szFormat( str.HT_szGetString(), sOut );

				if( g_cStatus->HT_nGetPureChakraSoul() >= sOut )
					pData->color = g_ColorTable[16]; //light grey
				else
					pData->color = g_ColorTable[11];	//red

				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// 제련시 가능한 아이템 
			if( CHTParamIDCheck::HT_bIsItemRefine( t->cItem.m_sItemInfo.snIndex ) 
								&& g_pParamMgr->HT_bGetItemRefinableItemType(&iOut) == true && iOut > 0 )
			{
				// 첨가 가능 아이템 분류(Bit Set)
				HTRESULT enable = HT_FALSE;
				HTint nCommaCount = 0;

				str.HT_hrCleanUp();
				HTRESULT type = HT_FALSE;

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
				// 무기
				if( BIT_AND( _REFINE_WEPON_ONEHAND, iOut ) )
				{
					//str = "한손무기"; 
					HT_vItemSystem_SetMessage( eMsgCommonItemClassOneHand, &pExtData->basic.str);
					type = HT_TRUE;
				}
				if( BIT_AND( _REFINE_WEPON_TWOHAND , iOut ) )
				{
					if(type)
					{
						//str +=", 두손무기";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassTwoHand, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "두손무기";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassTwoHand, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				// 방어구
				if( BIT_AND( _REFINE_DEFENCE_ARMOR , iOut ) )// 의복
				{ 
					if(type)
					{
						//str +=", 의복";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassArmor, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "의복";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassArmor, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_PANTS , iOut ) )// 바지
				{
					if(type)
					{
						//str +=", 바지";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassPants, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "바지";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassPants, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_GLOVES , iOut ) )// 장갑
				{
					if(type)
					{
						//str +=", 장갑";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassGloves, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "장갑";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassGloves, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_SHIELD, iOut ) )	// 방패
				{
					if(type)
					{
						//str +=", 방패";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShield, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "방패";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShield, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_BELT, iOut ) )	// 허리띠
				{
					if(type)
					{
						//str +=", 허리띠";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBelt, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "허리띠";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBelt, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_SHOES, iOut ) )	// 신발
				{
					if(type)
					{
						//str +=", 신발";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShoes, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "신발";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassShoes, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_DEFENCE_HELMET, iOut ) )	// 모자
				{
					if(type)
					{
						//str +=", 모자";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassHelmet, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "모자";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassHelmet, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				// 액세서리
				if( BIT_AND( _REFINE_ACCESSORY_EARRING, iOut ) )	
				{
					if(type)
					{
						//str +=", 귀걸이";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassEarring, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "귀걸이";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassEarring, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_NECKLACE, iOut ) )	
				{
					if(type)
					{
						//str +=", 목걸이";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassNecklace, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "목걸이";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassNecklace, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_BRACELET, iOut ) )	
				{
					if(type)
					{
						//str +=", 팔찌";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBracelet, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "팔찌";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassBracelet, &pExtData->basic.str);
					type = HT_TRUE;	
				}
				if( BIT_AND( _REFINE_ACCESSORY_RING, iOut ) )	
				{
					if(type)
					{
						//str +=", 반지";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassRing, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
						++nCommaCount;
					}
					else		//str += "반지";
						HT_vItemSystem_SetMessage( eMsgCommonItemClassRing, &pExtData->basic.str);
					type = HT_TRUE;	
				}
					
				//str += "용";
				HT_vItemSystem_SetMessage( eMsgItemInfoUsable, &str);
				pExtData->basic.str = pExtData->basic.str + _T(" ") + str;
				pExtData->basic.color = g_ColorTable[16]; //light grey

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max( winSizeX, pExtData->basic.str.HT_nGetSize()-(HTint)((HTfloat)nCommaCount/2.0 +0.5) );
			}
			// 내구도
			if( g_pParamMgr->HT_bGetItemMaxDurability( &sOut ) == true )
			{
				if( sOut < HT_ITEM_INFINITY_DURABILITY && t->cItem.m_sItemInfo.snDurability >= 0 ) 
				{
					HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
					if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
						++iCurDur;	// 올림 처리
					HTint iMaxDur = sOut/HT_ITEM_DURABILITY_DIVIDING ;
					if( sOut % HT_ITEM_DURABILITY_DIVIDING > 0 )
						++iMaxDur; // 올림 처리

					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					
					pExtData->basic.color = g_ColorTable[16]; //light grey
					// 내구도 %d / %d
					HT_vItemSystem_SetMessage( eMsgItemInfoDurability, &str );
					pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iCurDur, iMaxDur );
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
				}
				// 무기/방어구 중 파괴불가
				else if( sOut == HT_ITEM_INFINITY_DURABILITY && CHTParamIDCheck::HT_bIsItemWeapon(t->cItem.m_sItemInfo.snIndex)
															&& CHTParamIDCheck::HT_bIsItemDefence(t->cItem.m_sItemInfo.snIndex) )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[11]; //red
					// 파괴불가
					HT_vItemSystem_SetMessage( eMsgItemInfoUnbreakable, &pExtData->basic.str );
					
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
				}
			}

			// 예외처리 - 고급아누바바/아누바바의 부적의 경우 Effect를 표시하지 않는다. (수정 2004. 9. 21 추가)
			if( t->cItem.m_sItemInfo.snIndex == HT_INDEX_DAMAGE_UP
						|| t->cItem.m_sItemInfo.snIndex == HT_INDEX_SUPERIOR_DAMAGE_UP
						|| t->cItem.m_sItemInfo.snIndex == HT_INDEX_SUPERIOR_DAMAGE_UP2 )
			{
				// 아이템 판매 정보
				if( g_cNPCControl->HT_bNPCControl_IsItemMake() ) 
				{
					pData = new HT_ITEM_DATA;
					pData->color = g_ColorTable[17]; //yellow;
					// 판매 정보
					HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());

					HTint iRupiah = 0 ;
					HTshort sMaxDurability = 0 ;
					g_pParamMgr->HT_bGetItemSellRupiah( &iRupiah );
					g_pParamMgr->HT_bGetItemMaxDurability( &sMaxDurability );

					pData = new HT_ITEM_DATA;
					pData->color = g_ColorTable[17]; //yellow;
					if( iRupiah >= 0 )  // 철
					{
						HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount;// / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
						if(iNeedRupiah >= 0)
						{
							// %d 루피아
							CHTString szMessage;
							HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

							CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // 쉼표 처리
							pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
						}
					}
					else
					{
						//if(pData->str.HT_nGetSize() == 0)
						// 판매 불가
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
						pData->color = g_ColorTable[11];	//red
					}

					vInfo.vSourceStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}

				// 아이템 정보 Lock 해제
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
			
				// 제련 레벨에 의해 더해지는 상수 적용
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// 제련에 의해 더해진 속성이 있는지 검사
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1순위 - 필요레벨 검사:방어력과 공격력만
				if( iDecreaseVal > 0 
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )	
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2순위 - 제련 속성 검사
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// 하늘색
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect1Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간 %d초)	
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

				// 제련 레벨에 의해 더해지는 상수 적용
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// 제련에 의해 더해진 속성이 있는지 검사
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1순위 - 필요레벨 검사:방어력과 공격력만
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2순위 - 제련 속성 검사
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// 하늘색
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect2Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (지속시간 %d초)", iOut/HT_ITEM_DURATION_DIVIDING);	
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

				// 제련 레벨에 의해 더해지는 상수 적용
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// 제련에 의해 더해진 속성이 있는지 검사
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1순위 - 필요레벨 검사:방어력과 공격력만
				if( iDecreaseVal > 0 
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2순위 - 제련 속성 검사
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// 하늘색
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( t->cItem.m_sItemInfo.snIndex == 6601 || // 다음의 아이템은 세번째 특성 출력무시 (라가마니, 닐라마니, 비사잔, 루바티)
					t->cItem.m_sItemInfo.snIndex == 6602 || 
					t->cItem.m_sItemInfo.snIndex == 6603 ||
					t->cItem.m_sItemInfo.snIndex == 6604 ||
					t->cItem.m_sItemInfo.snIndex == 6606 ||	// 추가 : 2006. 2. 17 목걸이 제련석 ( 마니푸라, 비슈다, 아나하타, 아즈나 )
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

					// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect3Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (지속시간 %d초)", iOut/HT_ITEM_DURATION_DIVIDING);	
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

				// 제련 레벨에 의해 더해지는 상수 적용
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// 제련에 의해 더해진 속성이 있는지 검사
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1순위 - 필요레벨 검사:방어력과 공격력만
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2순위 - 제련 속성 검사
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// 하늘색
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect4Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (지속시간 %d초)", iOut/HT_ITEM_DURATION_DIVIDING);	
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

				// 제련 레벨에 의해 더해지는 상수 적용
				HTbool bMainRefineEffect = HT_FALSE;
				if( g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iOut) || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus )
				{
					bMainRefineEffect = HT_bItemSystem_GetMainRefineEffect( t->cItem.m_sItemInfo.snIndex, 
																t->cItem.m_sItemInfo.byRefineLevel, iOut, &iParam1, &iParam2 );
				}
				// 제련에 의해 더해진 속성이 있는지 검사
				HTbool bSubRefineEffect = HT_bItemSystem_GetSubRefineEffect( t, iOut, &iParam1, &iParam2, &iFunction );

				// 1순위 - 필요레벨 검사:방어력과 공격력만
				if( iDecreaseVal > 0
						&& ( iOut == eTNAfn_Damage || iOut == eTNAfn_ACPlus || iOut == eTNAfn_ACMinus ) )
					pExtData->basic.color = g_ColorTable[11];	//red
				// 2순위 - 제련 속성 검사
				else if( bMainRefineEffect == HT_TRUE || bSubRefineEffect == HT_TRUE )											
					pExtData->basic.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f);	// 하늘색
				else
					pExtData->basic.color = g_ColorTable[16];	//light grey
			
				if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, iDecreaseVal ) == HT_TRUE )
				{
					pExtData->basic.str = str;

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
					if( CHTParamIDCheck::HT_bIsItemChargeContinuance( t->cItem.m_sItemInfo.snIndex ) == false
						&& g_pParamMgr->HT_bGetItemEffect5Duration( &iOut ) == true && iOut > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//pExtData->basic.str.HT_szFormat("   (지속시간 %d초)", iOut/HT_ITEM_DURATION_DIVIDING);		
						HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING );

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
				}
				else
					delete pExtData;
			}
			// 제련에 의해서 추가된 속성이 있다면
			//if( t->cItem.m_iSubItemIndexCount > 0 )
			if( t->cItem.m_bySubEffectIDCount > 0 )
			{
				// 아이템이 기본적으로 있는 속성들
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

							pExtData->addtion.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f); // 하늘색

							pExtData->addtion.str = str;		

							vInfo.vAttributeStr.push_back(pExtData);
							winSizeX = max(winSizeX, pExtData->addtion.str.HT_nGetSize());
							// 지속시간
							if( t->cItem.m_sItem_SubRefineInfo[i].iEffectDuration > 0 )
							{
								pExtData = new HT_ITEM_EXPANSION_DATA;
								ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

								pExtData->addtion.color = HT_COLOR( 0.36f, 0.88f, 1.0f, 1.0f); // 하늘색
								//    (지속시간 %d초)	
								HT_vItemSystem_SetMessage( eMsgItemInfoDuration, &str );
								pExtData->addtion.str.HT_szFormat( str.HT_szGetString(), 
											t->cItem.m_sItem_SubRefineInfo[i].iEffectDuration/HT_ITEM_DURATION_DIVIDING );

								vInfo.vAttributeStr.push_back(pExtData);
								winSizeX = max(winSizeX, pExtData->addtion.str.HT_nGetSize());
							}
						}
					}
				} // end of for( int i = 0 ; i < t->cItem.m_iSubItemIndexCount ; ++i )
			} // end of 제련에 의해서 추가된 속성이 있다면
			// 공격 속도 - 무기일 경우
			if( CHTParamIDCheck::HT_bIsItemWeapon( t->cItem.m_sItemInfo.snIndex ) )
			{
				/* 제련이나 추가된 속성에 의해서 공격속도 변경됐는지 검사해야함 2003.12.10 선미 */
				if( g_pParamMgr->HT_bGetItemCoolDownTime( &iOut ) == true && iOut > 0 )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
					
					HTint iSpeed = HT_iItemSystem_CheckItemSpeedRange( iOut );
					pExtData->basic.color = g_ColorTable[16]; //light grey
					switch( iSpeed )
					{
						case HT_ITEM_SPEED_VERY_FAST : // 공격 속도 매우 빠름	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedVeryHigh, &pExtData->basic.str ); break;
						case HT_ITEM_SPEED_FAST		 : // 공격 속도 빠름
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedHigh, &pExtData->basic.str );		break;
						case HT_ITEM_SPEED_NORMAL	 : // 공격 속도 보통		
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedNormal, &pExtData->basic.str );	break;
						case HT_ITEM_SPEED_SLOW		 : // 공격 속도 느림	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedLow, &pExtData->basic.str );		break;
						case HT_ITEM_SPEED_VERY_SLOW : // 공격 속도 매우 느림	
							HT_vItemSystem_SetMessage( eMsgItemInfoAttackSpeedVeryLow, &pExtData->basic.str );	break;
						default: pExtData->basic.str.HT_hrCleanUp(); break;
					}

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				}
			}
			// 사정거리
			//if( g_pParamMgr->HT_bGetItemRange( &byteOut ) && byteOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("사정거리 %d", byteOut);		

			//	vInfo.vAttributeStr.push_back(pExtData);
			//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			//}
			// 소모 HP
			if( g_pParamMgr->HT_bGetItemCostHP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("소모 HP %d", iOut);		
				HT_vItemSystem_SetMessage( eMsgItemInfoCostHP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);	

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			// 소모 TP
			if( g_pParamMgr->HT_bGetItemCostTP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// 소모 TP %d, iOut		
				HT_vItemSystem_SetMessage( eMsgItemInfoCostTP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			// 소모 Item
			// 물약 같은 경우 소모 Item 정보에 자신의 인덱스가 들어있다.
			if( g_pParamMgr->HT_bGetItemidCostItem( &iOut ) == true && iOut > 0 && iOut != t->cItem.m_sItemInfo.snIndex )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				
				CHTString str;
				g_pParamMgr->HT_bGetItemName( iOut, &str );
				// %s 소모, str.HT_szGetString()
				CHTString szMessage;
				HT_vItemSystem_SetMessage( eMsgItemInfoCostItem, &szMessage );
				pExtData->basic.str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString() );

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}

			// 아이템 판매 정보
			if( g_cNPCControl->HT_bNPCControl_IsItemMake() ) 
			{
				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[17]; //yellow;
				// 판매 정보
				HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

				vInfo.vSourceStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());

				HTint iRupiah = 0 ;
				HTshort sMaxDurability = 0 ;
				g_pParamMgr->HT_bGetItemSellRupiah( &iRupiah );
				g_pParamMgr->HT_bGetItemMaxDurability( &sMaxDurability );

				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[17]; //yellow;
				if( iRupiah > 0 )  // 철
				{
					HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount;// / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
					if(iNeedRupiah > 0)
					{
						// %d 루피아
						CHTString szMessage;
						HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

						CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // 쉼표 처리
						pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
					}
				}
				
				if(pData->str.HT_nGetSize() == 0)
				{
					// 판매 불가
					HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
					pData->color = g_ColorTable[11];	//red
				}

				vInfo.vSourceStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			// 아이템 정보 Lock 해제
			g_pParamMgr->HT_bUnLockID(t->cItem.m_sItemInfo.snIndex);
			break;
		}
		t = t->next;
	}
	
	return winSizeX;
}

// 아이템 속도 정도 구하기
HTint CHTItemSystem::HT_iItemSystem_CheckItemSpeedRange( HTint iSpeed )
{
	//매우빠름		빠름			보통			느림			매우 느림
	//최저	최대	최저	최대	최저	최대	최저	최대	최저	최대
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

//----- 아이템 타입에 따라 제련 등급에 주어지는 증가 상수를 합산한다 ------//
HTbool CHTItemSystem::HT_bItemSystem_GetMainRefineEffect( HTdword dwIndex, HTint iLevel, HTint iEffectID, HTint* piParam1, HTint* piParam2 )
{
	if( dwIndex <= 0 || iLevel <= 0 )
		return HT_FALSE;

	HTint iVal = 0;
	iVal = HT_iItemSystem_GetMainRefineLevelConst( dwIndex, iLevel );

	// 무기류는 데미지에 합산
	if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) && g_cSkillSystem->HT_bSkillSystem_IsDamageEffect(iEffectID ) )
	{	
		*piParam1 += iVal;
		*piParam2 += iVal;
		return HT_TRUE;
	}
	// 방어구 중 갑옷류는 증가상수를 곱한 값을 합산
	else if( CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) && (iEffectID == eTNAfn_ACPlus || iEffectID == eTNAfn_ACMinus) )
	{
		*piParam1 += iVal;
		return HT_TRUE;
	}

	return HT_FALSE;
}

// 한손검, 한손도끼, 둔기, 단검, 한손지팡이
//									  1	  2   3   4   5   6   7   8    9   10   11   12  13  14   15
HTint g_iRefineLevelConstType1[ ] = { 4,  8, 12, 16, 20, 24, 32, 40,  50,  60,  72,  84, 98, 102, 118};
// 양손검, 양손도끼, 글러브, 창, 양손 지팡이, 활
HTint g_iRefineLevelConstType2[ ] = { 6, 12, 18, 24, 30, 36, 48, 60,  75,  90, 108, 126, 147, 168, 192 };
// 상의, 하의, 방패
HTint g_iRefineLevelConstType3[ ] = { 9, 18, 27, 36, 48, 60, 75, 96, 126, 162, 207, 252, 306, 360, 420 };
// 신발, 장갑, 허리띠, 모자
HTint g_iRefineLevelConstType4[ ] = { 3,  6,  9, 12, 16, 20, 25, 32,  42,  54,  69,  84, 102, 114, 135 };
//--------------- (강화)제련단계에 따른 증가 상수 구하기 ------------------// 
HTint CHTItemSystem::HT_iItemSystem_GetMainRefineLevelConst( HTdword dwIndex, HTint iLevel )
{
	if( dwIndex <= 0 || iLevel <= 0 )
		return 0;

	// 방어구
	if( CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) )
	{
		// 상의, 하의, 방패
		if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) 
			|| CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) || CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) )
			return g_iRefineLevelConstType3[iLevel-1];
		// 신발, 장갑, 허리띠, 모자
		else
			return g_iRefineLevelConstType4[iLevel-1];
	}
	// 무기
	else if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )
	{
		HTshort sType = 0;
		if( g_pParamMgr->HT_bGetItemType( dwIndex, &sType ) == false )
			return 0;

		// 한손검,한손도끼,한손 지팡이, 단검, 둔기
		if( ( CHTParamIDCheck::HT_bIsItemWeaponOneHand( dwIndex ) 
					&& ( sType == _ITEM_TYPE_WEPON_SWORD || sType == _ITEM_TYPE_WEPON_AX || sType == _ITEM_TYPE_WEPON_WAND) )
				|| sType == _ITEM_TYPE_WEPON_DAGGER || sType == _ITEM_TYPE_WEPON_MACE )
			return g_iRefineLevelConstType1[iLevel-1];
		// 양손검, 양손도끼, 양손 지팡이, 글러브, 창, 활
		else 
			return g_iRefineLevelConstType2[iLevel-1];
	}
	else
		return 0;
}
// 아이템의 필요레벨에 따른 수치 감소량
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
//	Returns Get 플레이어와 가장 가까운 Itemt KeyID찿기
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
		//-----아이템 정보 보여주기-----//
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

//	같은 이름의 아이템이 있는지 검사
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

//	KeyID로 아이템 아이콘 텍스쳐 아이디 얻어도기
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

//	장착한 아이템이 있는지 조사
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

//------- 아이템 기본 속성과 제련으로 추가된 속성 비교 ---------//
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

//---------- 강화 제련 레벨 구하기 ----------//
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

//--------주술 제련 레벨 구하기------------//
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
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	상위4비트 리드
					if( bySubItemIndex > 0 )
						++iEtcRefine;
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	하위4비트 리드
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

//--------주술 제련 아이템 중 속성 제련된 아이템 검사---------//
// 한 아이템에 하나의 속성만 제련 가능하다.
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

				if( iAttri != HT_SUBREFINETYPE_NONE ) // 한 아이템에 하나의 속성만 제련 가능하다.
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

//--------주술 제련에 사용된 아이템 index 구하기------------//
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
				
				if( t->cItem.m_sItemInfo.bySubRefine[i] > 0 ) // 제련 레벨
				{
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] >> 4;		//	상위4비트 리드
					if( bySubItemIndex > 0 )
						++iRefineCount; 
					bySubItemIndex = t->cItem.m_sItemInfo.bySubRefine[i] & 0x0F;	//	하위4비트 리드
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

//----------아이템 레벨 - 증가된 이동속도----------//
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

//----------아이템 제련시 필요한 루피아 정보-------------//
HTint CHTItemSystem::HT_iItemSystem_GetRupiahForItemWork(HTint nItemLevel, HTint iRupiah)
{
	if( iRupiah <= 0 )
		return -1;

	// 제련 비용 변경 (2005. 1. 7 선영범) KeyWord: 제련가격, 제련비용
	//iRupiah = (int)(iRupiah * ITEM_REFINING_COAT * (nItemLevel + 1) * (nItemLevel + 1));
	iRupiah = (int)(iRupiah * ITEM_REFINING_COAT * pow((double)nItemLevel + 1, 1.8));

	// iRupiah * 20 / 100 주술제련의 경우에는 기존 공식 적용

	return iRupiah;
}

//----------아이템 수리 정보-------------//
//------------------------------------------------------------------------------------//
// 예외 - 수리정보의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
//------------------------------------------------------------------------------------//
HTint CHTItemSystem::HT_iGetFixInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible)
{
    HT_NODE* t;
	t = m_sHead->next;

	HTint winSizeX = 0;
	bPossible = HT_TRUE;	// 수리 가능

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			// 아이템 정보 얻어오기
			HT_ITEM_DATA* pData = HT_NULL;

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[15]; //white;
			//pData->str.HT_szFormat("수리 정보");
			HT_vItemSystem_SetMessage( eMsgItemInfoRepairTitle, &pData->str );

			vInfo.push_back(pData);
			winSizeX = pData->str.HT_nGetSize();

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[17]; //yellow;
			pData->str = t->cItem.m_strItemName;
			// 강화 제련 정도를 표시한다.
			if( t->cItem.m_sItemInfo.byRefineLevel > 0)
			{
				CHTString str;
				str.HT_szFormat("+%d", t->cItem.m_sItemInfo.byRefineLevel);
				pData->str += str;
			}

			vInfo.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			
			// 소모성 아이템 또는 재료 또는 수집재료
			if( CHTParamIDCheck::HT_bIsItemUsable( t->cItem.m_sItemInfo.snIndex ) 
					|| CHTParamIDCheck::HT_bIsItemCollect( t->cItem.m_sItemInfo.snIndex ) 
					/*|| CHTParamIDCheck::HT_bIsItemQuestOnly( t->cItem.m_sItemInfo.snIndex ) */ )
			{
				pData = new HT_ITEM_DATA;
				//pData->str.HT_szFormat("수리불가");
				HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
				pData->color = g_ColorTable[11]; //red;
				bPossible = HT_FALSE;	// 수리 불가능

				vInfo.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			}
			else	// 나머지 아이템
			{ 
				// 255는 무한 내구도이기 때문에....그리고 보조재료에 의해 파괴불가가 됐을 경우 검사
				HTshort sMaxDurability;
				if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDurability) == true )
				{
					if( sMaxDurability < HT_ITEM_INFINITY_DURABILITY )
					{
						HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
						if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
							++iCurDur;	// 올림 처리
						HTint iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
						if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
							++iMaxDur; // 올림 처리

						// 내구도가 닳았을 경우
						if( iCurDur < iMaxDur )
						{
							HTint iRupiah;
							if( g_pParamMgr->HT_bGetItemRupiah( t->cItem.m_sItemInfo.snIndex, &iRupiah ) == true && iRupiah > 0 )  // 철
							{
								HTint iNeedRupiah = 0;
								// 계산해야함
								HTfloat fPrice = ((HTfloat)iRupiah / 10000.0f + (HTfloat)pow((double)iRupiah, 0.85 ))*(HTfloat)(iMaxDur-iCurDur)/(HTfloat)iMaxDur;
								iNeedRupiah = (HTint)( fPrice * (HTfloat)t->cItem.m_sItemInfo.byCount);

								if(iNeedRupiah > 0)
								{
									pData = new HT_ITEM_DATA;
									//pData->str.HT_szFormat("%d 루피아 필요", iNeedRupiah);
									CHTString szMessage;
									HT_vItemSystem_SetMessage( eMsgItemInfoNeedMoney, &szMessage );
									pData->str.HT_szFormat( szMessage.HT_szGetString(), iNeedRupiah );

									pData->color = g_ColorTable[17]; //yellow;

									vInfo.push_back(pData);
									winSizeX = max(winSizeX, pData->str.HT_nGetSize());
								}
							}
						}	// end of 내구도가 닳았을 경우
						else	// 내구도 변화가 없을경우
						{
							pData = new HT_ITEM_DATA;
							//pData->str.HT_szFormat("수리불가");
							HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
							pData->color = g_ColorTable[11]; //red;
							bPossible = HT_FALSE;	// 수리 불가능

							vInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());
						}
						pData = new HT_ITEM_DATA;
						//pData->str.HT_szFormat("내구도 %d/%d", iCurDur, iMaxDur ); 
						CHTString szMessage;
						HT_vItemSystem_SetMessage( eMsgItemInfoDurability, &szMessage );
						pData->str.HT_szFormat( szMessage.HT_szGetString(), iCurDur, iMaxDur );

						pData->color = g_ColorTable[16]; //light grey
						
						vInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}	// end of if( sMaxDurability > 0 )
					else // 무한 내구도
					{
						pData = new HT_ITEM_DATA;

						//pData->str.HT_szFormat("수리불가");
						HT_vItemSystem_SetMessage( eMsgItemInfoCannotRepair, &pData->str );
						pData->color = g_ColorTable[11]; //red;
						bPossible = HT_FALSE;	// 수리 불가능

						vInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}	// end of if( g_pParamMgr->HT_bGetItemMaxDurability( t->cItem.m_sItemInfo.snIndex, &sMaxDurability) == true )
			}	// end of 나머지 아이템
			break;
		}
		t = t->next;
	}
	
	return winSizeX;
}
// 수리가 필요한 아이템인지 검사
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
		++iCurDur;	// 올림 처리
	HTint iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
	if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
		++iMaxDur; // 올림 처리

	// 내구도가 닳았을 경우
	if( iCurDur < iMaxDur )
		return HT_TRUE;
	else
		return HT_FALSE;
}

// 판매금액 계산하기
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
			// 아이템 정보 얻어오기		// 수정 2004. 9. 18 선영범

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

//----------아이템 해체 정보-------------//
//------------------------------------------------------------------------------------//
// 예외 - 판매정보의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
//------------------------------------------------------------------------------------//
HTint CHTItemSystem::HT_iGetDisjointInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible)
{
    HT_NODE* t;
	t = m_sHead->next;

	HTint winSizeX = 0;
	bPossible = HT_TRUE;	// 해체 가능

	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwKeyID )
		{
			// 아이템 정보 얻어오기
			HT_ITEM_DATA* pData = HT_NULL;

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[15]; //white;
			// 판매 정보
			HT_vItemSystem_SetMessage( eMsgItemInfoSellTitle, &pData->str );

			vInfo.push_back(pData);
			winSizeX = pData->str.HT_nGetSize();

			pData = new HT_ITEM_DATA;
			pData->color = g_ColorTable[17]; //yellow;
			pData->str = t->cItem.m_strItemName;
			// 강화 제련 정도를 표시한다.
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
			if( iRupiah > 0 )  // 철
			{
				HTint iNeedRupiah = iRupiah * t->cItem.m_sItemInfo.byCount / HT_INFO_ITEM_SELL_DIVIDING_CONST ;
				if(iNeedRupiah > 0)
				{
					// %d 루피아
					CHTString szMessage;
					HT_vItemSystem_SetMessage( eMsgItemInfoPrice2, &szMessage );

					CHTString szMoney = g_cUIManager->HT_strSetRestMark( iNeedRupiah ); // 쉼표 처리
					pData->str.HT_szFormat( szMessage.HT_szGetString(), szMoney.HT_szGetString() );
				}
			}
			
			if(pData->str.HT_nGetSize() == 0)
			{
				// 판매 불가
				HT_vItemSystem_SetMessage( eMsgItemInfoCannotSell, &pData->str );
				pData->color = g_ColorTable[11];	//red

				bPossible = HT_FALSE;	// 해체 불가능
			}

			vInfo.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
			
			// 255는 무한 내구도이기 때문에....그리고 보조재료에 의해 파괴불가가 됐을 경우 검사
			// 내구도 - 무한 내구도(255)가 아닐때만 표시해준다.
			if( sMaxDurability < HT_ITEM_INFINITY_DURABILITY )
			{
				HTint iCurDur = t->cItem.m_sItemInfo.snDurability/HT_ITEM_DURABILITY_DIVIDING;
				if( t->cItem.m_sItemInfo.snDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
					++iCurDur;	// 올림 처리
				HTint iMaxDur = sMaxDurability/HT_ITEM_DURABILITY_DIVIDING;
				if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
					++iMaxDur; // 올림 처리

				pData = new HT_ITEM_DATA;
				pData->color = g_ColorTable[16]; //light grey
				// 내구도 %d/%d
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

//----------내구도 변화부분---------//
HTvoid CHTItemSystem::HT_vItemSystem_vNetWork_SCP_Item_Durability_Decrease( MSG_ITEM* info )
{
	if( info->byPlace == ITEM_PLACE_EQUIP )
	{
		if (!( info->byIndex < 0 || info->kItem.snIndex < 0 || info->kItem.snDurability < 0))
		{
			HTdword dwKeyID = this->HT_dwSystem_GetItemEquipKeyID( info->byIndex );
			
			// 현재 장비창에서 KeyID로 장비 인덱스를 검사
			HTint iKeyID = 0;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, info->byIndex, iKeyID );
			
			HTdword dwIndex = this->HT_dwSystem_GetItemIndex( iKeyID );

			if (dwIndex != (info->kItem.snIndex+4000) )	// 장비 인덱스를 검사해서 엉뚱한 값이 넘어오면 리턴
				return;

			// 내구도 상태 장비창에 표시
			HT_dwItemSystem_SetCurDurability( dwKeyID, info->kItem.snDurability );

			// 내구도 경고 설정
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Receive_Item_Decrease: %d:%d-%d", 
	//													info->byPlace, info->byIndex, info->kItem.snDurability);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	0x01:머리,0x02:귀걸이,0x03:목걸이,0x04:몸,0x05:벨트,0x06:양손,0x07:오른손
//	0x08:왼손,0x09:오른손 or 왼손,0x0a:오른손 위,0x0b:오른손 아래,0x0c:왼손 위,0x0d:왼손 아래,0x0e:발
HTRESULT CHTItemSystem::HT_hrItemSystem_vNetWork_SCP_Item_Abrasion(PS_SCP_ITEM_ABRASION info)
{
	return HT_TRUE;
}

//--------------현재 내구도 변경하고 그 아이템의 Index 반환-----------//
DWORD CHTItemSystem::HT_dwItemSystem_SetCurDurability(DWORD dwItemKeyID, HTint iCurDurability)
{
	HT_NODE* t;
	t = m_sHead->next;

	//HTfloat fCurDurability;
	while( t != m_sTail )
	{
		if( t->cItem.m_dwItemKeyID == dwItemKeyID )
		{
			// 현재 아이템의 최대 내구도와 비교
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

	return -999;	// 내구도 범위:0~25500
}
 
//-----------현재 내구도 반환--------------//
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
	return 0;	// 255는 무한내구도
}

//--------------최대 내구도 반환-------------------//
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
	
	return 0;	// -1은 무한내구도
}

//--------보조재료 정보 지우기 --------//
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
			// 새로운 Effect일 경우
			if( i == t->cItem.m_bySubEffectIDCount 
						&& t->cItem.m_bySubEffectIDCount < (MAX_REFINE_SUB_LEVEL*MAX_EFFECT_NUM - 1 ) )	
			{
				++(t->cItem.m_bySubEffectIDCount);

				// 적용가능한 속성인지 검사
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
// 해당 아이템 (키아이디)의 주술 제련이 잘못되어 있는 조사하여 잘되어 있으면 트루, 잘못되어 있으면 펄스를 반환합니다.
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
		// 서버에서 보내준 순서 그대로 유지한 주술제련 정보
		t->cItem.m_sItemInfo.bySubRefine[j];

		if( bySubItem[j] > 0 )
		{
			bySubItemIndex = bySubItem[j] >> 4;		//	상위4비트 리드
			bySubItemIndex2 = bySubItem[j] & 0x0F;	//	하위4비트 리드
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
		// 서버에서 보내준 순서 그대로 유지한 주술제련 정보
		t->cItem.m_sItemInfo.bySubRefine[j] = bySubItem[j] ;

		if( bySubItem[j] > 0 )
		{
			bySubItemIndex = bySubItem[j] >> 4;		//	상위4비트 리드
			bySubItemIndex2 = bySubItem[j] & 0x0F;	//	하위4비트 리드

			// 아이템 종류별로 재정리한 주술제련 정보
			for( i = 0 ; i < 2 ; ++ i ) // 2번(상/하위비트) 반복하기 위해 
			{
				if( i % 2 == 0 ) // 제련 아이템 인덱스
					iItemIndex = HT_ITEM_REFINE_INDEX_START + bySubItemIndex;	// 상위 4비트
				else
					iItemIndex = HT_ITEM_REFINE_INDEX_START + bySubItemIndex2;	// 하위 4비트
				// 제련 재료가 없을 경우 iItemIndex == HT_ITEM_REFINE_INDEX_START
				if( iItemIndex > HT_ITEM_REFINE_INDEX_START )
				{
					if( g_pParamMgr->HT_bLockID( iItemIndex ) == true )	// 아이템 정보 Lock설정
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
			} // end of for( i = 0 ; i < 2 ; ++ i ) // 2번(상/하위비트) 반복하기 위해 
		}	// end of if( bySubItem[j] > 0 )
	}

	return HT_TRUE;
}


//--- 아이템 종류로 적용 가능한 속성 구분 ---//
HTbool CHTItemSystem::HT_vItemSystem_CheckItemEffect( HTint iItemIndex, HTint iEffectID )
{
	// 1. 속성(불/추위/독/전기)제련의 경우 
	// 무기일때는 데미지에, 의복/방패일 경우 저항력을 변화시킨다
	// 2. 무기와 모자일 경우 공격 성공률을, 허리띠와 방패일 경우 회피율을 변화시킨다.
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
			case eTNAfn_SaveTPCost : // TP 소모량은 목걸이에만 적용된다.
			case eTNAfn_HPRecoveryPlus : // HP 회복은 목걸이에만 적용된다.
			case eTNAfn_TPRecoveryPlus : // TP 회복은 목걸이에만 적용된다.
			case eTNAfn_MaxHPPlus : // MAX HP는 목걸이에만 적용된다.
			case eTNAfn_AbsorbElementalDamage :
			case eTNAfn_MaxTPPlus : // TP 증가
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
			case eTNAfn_SaveTPCost : // TP 소모량은 목걸이에만 적용된다.
			case eTNAfn_HPRecoveryPlus : // HP 회복은 목걸이에만 적용된다.
			case eTNAfn_TPRecoveryPlus : // TP 회복은 목걸이에만 적용된다.
			case eTNAfn_MaxHPPlus : // MAX HP는 목걸이에만 적용된다.			
			case eTNAfn_AbsorbElementalDamage :
			case eTNAfn_MaxTPPlus : // TP 증가
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
			case eTNAfn_SaveTPCost : // TP 소모량은 목걸이에만 적용된다.
			case eTNAfn_HPRecoveryPlus : // HP 회복은 목걸이에만 적용된다.
			case eTNAfn_TPRecoveryPlus : // TP 회복은 목걸이에만 적용된다.
			case eTNAfn_MaxHPPlus : // MAX HP는 목걸이에만 적용된다.
			case eTNAfn_AbsorbElementalDamage : // 속성 데미지 흡수
			case eTNAfn_MaxTPPlus : // TP 증가
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
// D : 현재 내구도에 따른 수리 표시 갱신
//-----------------------------------------------------------------------------
HTvoid					
CHTItemSystem::HT_vItemSystem_SetDurabilityWarning( HTint iInvenIndex )
{
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_EQUIP, iInvenIndex, iKeyID );
	
	HTdword dwIndex = this->HT_dwSystem_GetItemIndex( iKeyID );

	if ( HT_bItemSystem_CheckDurabilityWarning( iKeyID ) )	// 내구도 경고가 필요하면
	{	
		if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )	// 무기
		{
			m_bReformNeed[_eITEM_WEAPON] = HT_TRUE;	
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_RIGHT_HAND;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) ) // 갑옷
		{
			m_bReformNeed[_eITEM_BODY]	= HT_TRUE;
			if (!m_bTReformNeed) m_iNeedReformPlace = ITEM_LOCATION_EQUIP_ARMOR;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) ) // 바지
		{
			m_bReformNeed[_eITEM_PANTS]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_PANTS;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) ) // 방패
		{
			m_bReformNeed[_eITEM_SHIELD] = HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_LEFT_HAND;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwIndex ) ) // 머리
		{
			m_bReformNeed[_eITEM_HEAD]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_HEAD;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwIndex ) ) // 신발
		{
			m_bReformNeed[_eITEM_FOOT]	= HT_TRUE;
			if (!m_bTReformNeed) 
			{
				m_flastWarningTime = 0.0f;
				m_iNeedReformPlace = ITEM_LOCATION_EQUIP_FOOT;
			}
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwIndex ) ) // 허리띠
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
		if( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) )	// 무기
		{
			m_bReformNeed[_eITEM_WEAPON] = HT_FALSE;	
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwIndex ) ) // 갑옷
		{
			m_bReformNeed[_eITEM_BODY]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefencePants( dwIndex ) ) // 바지
		{
			m_bReformNeed[_eITEM_PANTS]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwIndex ) ) // 방패
		{
			m_bReformNeed[_eITEM_SHIELD] = HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwIndex ) ) // 머리
		{
			m_bReformNeed[_eITEM_HEAD]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwIndex ) ) // 신발
		{
			m_bReformNeed[_eITEM_FOOT]	= HT_FALSE;
		}
		else if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwIndex ) ) // 허리띠
		{
			m_bReformNeed[_eITEM_BELT]	= HT_FALSE;
		}
	}
	
	// 내구도가 낮은 아이템이 하나라도 있으면
	if ( m_bReformNeed[_eITEM_BODY] || m_bReformNeed[_eITEM_SHIELD] || m_bReformNeed[_eITEM_HEAD] || 
		 m_bReformNeed[_eITEM_FOOT] || m_bReformNeed[_eITEM_BELT] || m_bReformNeed[_eITEM_WEAPON] || m_bReformNeed[_eITEM_PANTS] )
			m_bTReformNeed = HT_TRUE;
	else 
	{
		m_bTReformNeed = HT_FALSE;
		m_iNeedReformPlace = -1; // 없음
		m_flastWarningTime = 0.0f;
	}
}

HTvoid CHTItemSystem::HT_vItemSystem_RenewalDurabilityWarning( )
{
	HTdword dwKeyID = 0;
	
	if( m_bTReformNeed ) // 현재 경고표시 하고 있는 아이템 검사
	{
		dwKeyID = HT_dwSystem_GetItemEquipKeyID( m_iNeedReformPlace ); // 경고표시 하고 있는 아이템 
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
	
	// 현재 경고표시 하고 있던 아이템이 수리됐거나 장착하고 있지 않을 경우
	// 경고 표시할 다른 아이템이 있는지 검사한다.
	// 무기
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_RIGHT_HAND ); return;
	}
	// 갑옷
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_ARMOR );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_ARMOR ); return;
	}
	
	// 바지
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_PANTS );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_PANTS ); return;
	}

	// 방패
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_LEFT_HAND ); return;
	}

	// 머리
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_HEAD );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_HEAD ); return;
	}

	// 신발
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_FOOT );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_FOOT ); return;
	}

	// 허리띠
	dwKeyID = HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_BELT );
	if( dwKeyID!= 0 && HT_bItemSystem_CheckDurabilityWarning( dwKeyID ) )
	{
		HT_vItemSystem_SetDurabilityWarning( ITEM_LOCATION_EQUIP_BELT ); return;
	}
}

// 현재 내구도 경고 표시하는 아이템 설정을 해제한다.
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

// 내구도가 낮은 아이템인지 검사
HTbool CHTItemSystem::HT_bItemSystem_CheckDurabilityWarning( HTdword dwKeyID )
{
	HTshort sCurDurability, sMaxDurability = 0;
	HTint iCurDur = 0, iMaxDur = 0;
	HTfloat fDurability = 0;

	// 현재 경고표시 하고 있는 아이템 검사
	if( dwKeyID != 0 )
	{	
		HTdword dwIndex = this->HT_dwSystem_GetItemIndex( dwKeyID );
		if( dwIndex <= 0 )
			return HT_FALSE;

		// 최대 내구도 - 무한 내구도일경우 처리하지 않음
		if( g_pParamMgr->HT_bGetItemMaxDurability( dwIndex, &sMaxDurability ) == false 
						|| sMaxDurability == HT_ITEM_INFINITY_DURABILITY )
			return HT_FALSE;

		iMaxDur = sMaxDurability / HT_ITEM_DURABILITY_DIVIDING ;
		if( sMaxDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
			++iMaxDur; // 올림 처리

		// 현재 내구도
		sCurDurability = this->HT_sItemSystem_GetCurDurability( dwKeyID );
		iCurDur = sCurDurability / HT_ITEM_DURABILITY_DIVIDING;
		if( sCurDurability % HT_ITEM_DURABILITY_DIVIDING > 0 )
			++iCurDur;	// 올림 처리

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
// D : 내구도 변경에 따른 수리 표시 메세지 설정 및 소리 
//-----------------------------------------------------------------------------
HTvoid
CHTItemSystem::HT_vSetDurabilityMsg( )
{
	m_dwMsgItemKeyID = HT_dwSystem_GetItemEquipKeyID( m_iNeedReformPlace );

	CHTString strMessage;
	// %s의 현재 내구도가 매우 낮습니다
	HT_vItemSystem_SetMessage( eMsgItemDurabilityWarning, &strMessage );
	// 시스템 창에 찍기
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ERROR, strMessage );
	// 소리 내기
	g_pEngineHandler->HT_hrPlaySound( _DURABLE_WARN_SOUND, _DURABLE_WARN_TIMES );
}

//	스킬의 쿨 타임을 넘겨준다
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
	// 예외 - 아이템 정보, 수리정보, 판매정보의 경우 메세지만 설정하고, 
	// 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
	//------------------------------------------------------------------------------------//
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vItemSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vItemSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 파티원 이름
		case eMsgParamPartymemberName :
			*pszParam = m_strMsgCharName;
			break;

		// 아이템 이름
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
//	성별에 따라서 장창 아이템 재 설정
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
