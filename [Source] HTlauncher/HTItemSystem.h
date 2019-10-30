
#ifndef __HTITEMSYSTEM_H__
#define __HTITEMSYSTEM_H__

#include "HTItem.h"

#define ITEM_DISMANTLE_PERCENTAGE 50
#define _DURABLE_ITEM_ATTACK	0
#define _DURABLE_ITEM_DEFENCE	1

// 아이템 LL 구현을 위한 구조체 
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
	HTvoid		HT_vItemSystem_AOI_Check( HT_NODE *t );					//	AOI 영역 체크

	// 랜더
	HTRESULT	HT_hrSystemRender();
	// 랜더_이름_3d
	HTvoid		HT_vItemSystem_RenderName( HT_NODE* t );
	
	//---------------------------------------------------------------------
	// 맵에 있는 아이템 관련
	//---------------------------------------------------------------------
	// 맵상에서 아이템이 나타난다.
	HTvoid		HT_vItemSystem_Appear( PS_SCP_MAP_ITEM_APPEAR );
	// 맵상에서 아이템이 사라진다.
	HTvoid		HT_vItemSystem_DisAppear( PS_SCP_MAP_ITEM_DISAPPEAR );
	// 3D아이템을 삭제한다.
	HTvoid		HT_vItemSystem_3DItemHidden( HTint iKeyID );
	// 아이템을 맵이에다가 버린다.
	HTvoid		HT_vItemSystem_ThrowItem( HTint iKeyID, HTPoint );
	// 맵위에서 아이템을 줍는다.
	HTbool		HT_bItemSystem_PickUpItemCheck( DWORD );
	// 맵위의 픽업된 아이템 초기화
	HTvoid		HT_vSystem_InitPickUpItemOnMap();
	// 맵셀위에 아이템 검색
	HTint		HT_iSystem_MapCellCheckToItemOnMap( HTint, HTint );
	// 아이템의 모델 아이디로 비교한다
	HTint		HT_iSystem_ComIDCheck( HTint iID, HTPoint );
	// 맵위의 특정 위치에 아이템이 있는지 검사:있으면 HT_TRUE 리턴
	HTRESULT	HT_hrCheckMapPos(HTPoint pos);
	//	맵위의 셀좌표를 반환 KeyID
	HT_CELL_COORD HT_cellItemSystem_GetMapCellPosForKeyID( HTint );	
	//	맵위의 셀좌표를 반환 ModelID
	HT_CELL_COORD HT_cellItemSystem_GetMapCellPosForModelID( HTint );	

	//---------------------------------------------------------------------
	// 아이템 삭제
	//---------------------------------------------------------------------
	// 기존의 아이템 지울때
	HTvoid		HT_LL_vInsertAfter_ItemDelete( DWORD );							
	// 아이템 전부를 삭제
	HTvoid		HT_vItemSystem_TotalItemDelete();
	// 아이템을 삭제한다
	HTvoid		HT_vItemSystem_DeleteItem( DWORD iKeyID );
	//HTvoid		HT_vItemSystem_DeleteItem(DWORD dwKeyID, HTint nLocation);
	// 인벤토리 내의 아이템 전부를 삭제
	HTvoid		HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory );
	// 인벤토리 내의 특정 index의 아이템 전부를 삭제
	HTvoid		HT_vItemSystem_DeleteItemInventory( HTint nLocation, HTint nInventory, DWORD dwItemIndex );
	// 인벤토리 내의 특정 type의 아이템 전부를 삭제
	HTvoid		HT_vItemSystem_DeleteItemInventory( WORD wItemType, HTint nLocation, HTint nInventory);
	
	//---------------------------------------------------------------------
	// 인벤토리에 있는 아이템 관련
	//---------------------------------------------------------------------
	// 아이템이 장착될 수 있는 인벤토리인가?
	HTint		HT_iItemAlSetPosInventoryCheck( DWORD dwKeyID, DWORD dwItemIndex, HT_ITEMSETTING_FLAG sSetItem );
	
	// 인벤토리에 빈공간의 갯수 반환 - 2005. 2. 14 발랜타인데이에 선영범 작성
	HTint		HT_iItemAlSetPosInventoryBlankCheck();

	// 창고에 빈공간의 갯수 반환 - 2005. 2. 14 발랜타인데이에 선영범 작성
	HTint		HT_iItemAlSetPosGoodsKeepBlankCheck();

	// 인벤토리의 특정칸에 해당 아이템이 몇개 존재 하는가? 알아내기 - 2005. 7. 28 선영범
	HTint		HT_bItemSystem_GetPossible2(DWORD dwIndex, HTint iPos );

	// 아이템이 특정 위치에 놓일 수 있는지 검사
	HTbool		HT_bItemSystem_GetPossibleOnEquip(DWORD dwItemKeyID, HTint nLocation);

	// 인벤토리내의 아이템 셋팅하기
	HTvoid		HT_vItemSystem_SettingInventoryPos( HTint, HT_ITEMSETTING_FLAG, HTbool );
	
	// PC/NPC 인벤토리에 있는 아이템의 착용가능/불가능 바 갱신
	HTvoid		HT_vItemSystem_RenewalPossibleBar(HTint nDlgNo);
	HTbool		HT_bItemSystem_GetPossible(DWORD dwItemKeyID, HTbool bLevelCheck);

	//---------------------------------------------------------------------
	// 제련한 아이템의 제련 정보 관련
	//---------------------------------------------------------------------
	// 강화제련 레벨 셋팅
	HTbool		HT_bItemSystem_SetMainRefineLevel(DWORD dwItemKeyID, HTint iLevel);
	// 보조재료에 의해 아이템에 추가된 속성 셋팅
	HTbool		HT_bItemSystem_SetSubRefineItem(DWORD dwItemKeyID, HTbyte bySubItem[MAX_SUBMATERIALSIZE] );
	HTbool		HT_bItemSystem_SetSubRefineEffect
				( DWORD dwItemKeyID, HTint iEffectID, HTint iParam1, HTint iParam2, HTint iFunction = 0, HTint iDuration = 0 );
	// 보조재료 정보 지우기
	HTbool		HT_bItemSystem_ClearSubRefineItem(DWORD dwItemKeyID);

	// 아이템 타입에 따라 제련 등급에 주어지는 증가 상수를 합산한다 
	HTbool		HT_bItemSystem_GetMainRefineEffect( HTdword dwIndex, HTint iLevel, HTint iEffectID, HTint* piParam1, HTint* piParam2 );
	// (강화)제련단계에 따른 증가 상수 구하기
	HTint		HT_iItemSystem_GetMainRefineLevelConst( HTdword dwIndex, HTint iLevel );
	// 아이템 종류로 적용 가능한 속성 구분
	HTbool		HT_vItemSystem_CheckItemEffect( HTint iItemIndex, HTint iEffectID );
	
	// 아이템 제련시 필요한 루피아 정보
	HTint		HT_iItemSystem_GetRupiahForItemWork(HTint nItemLevel, HTint iRupiah);

	// 강화 제련 레벨
	HTbyte		HT_byItemSystem_GetMainRefineLevel( DWORD dwKeyID );
	// 주술 제련 레벨
	HTint		HT_iItemSystem_GetSubRefineLevel( DWORD dwKeyID );
	// 주술 제련에 사용된 아이템 index 구하기
	HTint		HT_iItemSystem_GetSubRefineItemsIndex( DWORD dwKeyID, HTbyte* bySubRefine );
	// 주술 제련 아이템 중 속성 제련된 아이템 검사
	HTint		HT_iItemSystem_GetAttributeSubRefineItem( DWORD dwKeyID );
	HTint		HT_iItemSystem_GetAttribute( HTint iEffectID );

	//---------------------------------------------------------------------
	// 아이템 정보 반환
	//---------------------------------------------------------------------			
	//	아이템의 모델 ID를 얻어온다.
	HTint		HT_iSystem_GetItemModelID( DWORD );	
	
	//  아이템 데이터 얻기
	HTbool		HT_bItemSystem_GetItemInfo( DWORD dwItemKeyID, STRUCT_ITEM& sItem );

	//	셀위에 있는 아이템의 KeyID를 얻어온다.
	DWORD		HT_dwItemSystem_GetKeyIDOnCell( HTPoint );	
	// 마우스 포인터 위치에 있는 아이템 KeyID 반환
	HTint		HT_iSystem_ItemFind( HTint, HTint, HTint );			
	// 아이템의 모델 아이디로부터 키아이디를 얻어온다.
	DWORD		HT_dwSystem_GetItemKeyFromModelID( HTint, HTbool bPickCheck );
	// 아이템의 인벤토리 위치로 KeyID를 얻어온다
	DWORD		HT_dwItemSystem_GetItemKeyIDFromInvenLocation( HTint iCellNo );
	// 인덱스로 PC인벤토리내 가장 처음 검색되는 아이템의 KeyID를 얻어온다
    DWORD		HT_dwItemSystem_GetKeyIDInPCInventoryForIndex( HTint );
	// 장착한 아이템의 KeyID를 얻어온다.
	DWORD		HT_dwSystem_GetItemEquipKeyID( HTint );					
	// 아이템 포지션과 인벤토리 셀좌표를 계산하여 아이템 KeyID찾기 
	DWORD		HT_dwItemSystem_ItemSerch( HT_ItemReturnRoom );
	// 아이템 포지션과 인벤토리 셀좌표를 계산하여 아이템 KeyID찾기 
	DWORD		HT_dwItemSystem_ItemSerch( HTint iLocation, HTint iInventory, HTint iSlotNo );
	STRUCT_ITEM HT_iGetItemInfo(DWORD dwKeyID);
	// 특정 위치(iLocation)에 자신을 제외한 같은 종류의 아이템이 있는지 검색해서 KeyID와 위치를 얻어온다
	HTvoid		HT_vItemSystem_GetItemPos( DWORD dwItemIndex, DWORD dwActiveItemKeyID, HTint iLocation, 
											DWORD& dwItemKeyID, HT_ITEMSETTING_FLAG& sLocRoom );
	// 마우스 포인트를 넘겨받아 활성화된 아이템중에 포인트 위치에 있는것의 KeyID를 반환
	DWORD		HT_dwItemSystem_MousePtToItemPosCheck( HTPoint pPt );

	// 아이템의 KeyID로 Index와 type, 크기를 반환 
	HTint		HT_iGetItemInfoForEquip(DWORD dwKeyID, DWORD& dwItemIndex, HTint& iItemType, HTPoint& iItemSize);
	// 아이템의 키이디로 인덱스를 얻어온다
	DWORD		HT_dwSystem_GetItemIndex( DWORD );

	// 아이템 이름 획득
	CHTString	HT_strItemSystem_GetItemName(DWORD dwItemKeyID);
	// 아이템 타입 얻어온다
	HTshort		HT_sItemSystem_GetItemType( DWORD dwKeyID );

	// 아이템 KeyID로 위치 알아오기
	HTbool		HT_bItemSystem_GetItemPos( DWORD dwKeyID, HT_ITEMSETTING_FLAG& sLocRoom );
	// 아이템의 인벤토리 셀 위치를 반환
	HTPoint		HT_ptItemSystem_GetInventoryPos( DWORD );
	
	// 중첩 아이템 겟수 얻어오기
	HTint		HT_iItemSystem_GetItemCount( DWORD );
	// 중첩 아이템의 겟수를 셋팅해준다
	HTvoid		HT_vItemSystem_SetOverlapItemCount( DWORD, HTbyte );
	// 중첩 아이템 증가
	HTbool		HT_bItemSystem_SetOverlapItem_Add( DWORD, HTbyte );	
	// 중첩 아이템 감소
	HTbool		HT_bItemSystem_SetOverlapItem_Minus( DWORD, HTbyte );	
	// 아이템의 키이디로 아이템의 최대 중첩 개수를 얻어온다
	WORD		HT_wItemSystem_GetItemMaxPackCount( DWORD dwItemKeyID );
	// 중첩 아이템이 있는지 판단
	HTPoint		HT_ptItemSystem_GetOverlapItem( DWORD );					
	// 인벤토리 안에있는 특정 아이템(Index)의 총 개수를 얻어온다
	HTint		HT_iItemSystem_GetItemCountOnPcInven( DWORD dwItemIndex );
	
	// 아이템을 사이즈를 반환
	HTPoint		HT_ptItemSystem_GetSize( DWORD dwKeyID );
	// 아이템의 셀 번호를 반환
	HTint		HT_iItemSystem_GetCellNumber( DWORD dwItemKeyID );

	// 아이템 속도 정도 구하기
	HTint		HT_iItemSystem_CheckItemSpeedRange( HTint iSpeed );
	// 아이템의 필요레벨에 따른 수치 감소량
	HTint		HT_iItemSystem_GetDecreaseValForGapLevel( HTint iItemIndex );
	//	Returns Get 플레이어와 가장 가까운 Itemt KeyID찿기
	HTint		HT_iItemSystem_GetItemKeyIDMostNearMainChar();
	//	Set Item Targetting Effect
	HTvoid		HT_vItemSystem_SetItemTargettingEffect( HTint iKeyID );
	//	같은 이름의 아이템이 있는지 검사
	HTRESULT	HT_hrItemSystem_GetSameNameCheck( CHTString strItemName );
	//	KeyID로 아이템 아이콘 텍스쳐 아이디 얻어도기
	HTint		HT_iItemSystem_GetTextureIDFromKeyID( HTint iKeyID );
	//	장착한 아이템이 있는지 조사
	HTRESULT	HT_hrItemSystem_CheckEquipItem();

	//---------------------------------------------------------------------
	// 아이템 정보창에 보여줄 정보 
	//---------------------------------------------------------------------	
	// 아이템 일반 정보를 얻어온다
	HTint		HT_iGetItemInfo(DWORD dwKeyID, HT_ITEMINFO& vInfo, BYTE bType = 0);
	// 아이템에 기본적으로 추가되어있는 정보 얻어오기
	HTbool		HT_bItemSystem_GetSubRefineEffect( const HT_NODE* pItemNode, const HTint iEffectID, 
												HTint* piParam1, HTint* piParam2, HTint* piFunction/*, CHTString* str*/);
	// 아이템 수리/해체 정보
	HTint		HT_iGetFixInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible);
	HTint		HT_iGetDisjointInfo(DWORD dwKeyID, vector<HT_ITEM_DATA*>& vInfo, HTbool& bPossible);
	// 판매금액 계산하기
	HTint		HT_iItemSystem_CalDisjointPrice(DWORD dwKeyID );

	// 아이템 레벨 - 증가된 이동속도
	//HTfloat		HT_fItemSystem_GetItemSpeedUp( DWORD dwKeyID );

	//	스킬의 쿨 타임을 넘겨준다
	HTint		HT_iItemSystem_GetCoolTime( DWORD );

	//---------------------------------------------------------------------
	// 내구도 관련
	//---------------------------------------------------------------------	
	// 현재 내구도 변경하고 그 아이템의 내구도 반환
	DWORD		HT_dwItemSystem_SetCurDurability(DWORD dwItemKeyID, HTint iCurDurability);
	// 현재 내구도 반환
	HTshort		HT_sItemSystem_GetCurDurability(DWORD dwItemKeyID);
	// 최대 내구도 반환
	HTshort		HT_sItemSystem_GetMaxDurability(DWORD dwItemKeyID);
	
	// 내구도 경고 표시 갱신
	HTvoid					HT_vItemSystem_SetDurabilityWarning( HTint iInvenIndex );
	HTvoid					HT_vItemSystem_RenewalDurabilityWarning( );

	// 수리가 필요한 아이템인지 검사
	HTbool					HT_bItemSystem_CheckNeedFix(DWORD dwKeyID);
	//---------------------------------------------------------------------
	// 네트워크 관련
	//---------------------------------------------------------------------	
	// 아이템 생성
	HTvoid		HT_vItemSystem_ItemSet( PS_SCP_RESP_ITEM_SET info );
	HTvoid		HT_vItemSystem_CreateAshramCargo( HTbyte byPlace, HTshort snIndex, STRUCT_ITEM oItem );
	HTvoid		HT_LL_vInsertAfter_ItemCreateInven( STRUCT_ITEM arrInven[MAX_INVEN] );
	HTvoid		HT_LL_vInsertAfter_ItemCreateEquip( STRUCT_ITEM arrEquip[MAX_EQUIP] );
	HTvoid		HT_LL_vInsertAfter_ItemCreateNPCInven( STRUCT_ITEM arrNPCInven[MAX_CARGO] );
	//	아쉬람 창고 관련
	HTvoid		HT_LL_vInsertAfter_ItemDeleteAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo );
	HTvoid		HT_LL_vInsertAfter_ItemCreateAshramCargo( STRUCT_ITEM arrAshramCargo[MAX_CARGO], HTint iCargoNo );

	// 아이템 내구도 감소
	HTvoid		HT_vItemSystem_vNetWork_SCP_Item_Durability_Decrease( MSG_ITEM* info );
	// 아이템 소모로 사라짐
	HTRESULT	HT_hrItemSystem_vNetWork_SCP_Item_Abrasion(PS_SCP_ITEM_ABRASION info);

	//---------------------------------------------------------------------
	//	성별에 따라서 장창 아이템 재 설정
	//---------------------------------------------------------------------	
	HTvoid		HT_vItemSyste_TribeEquipItemReEquip( HTshort snTribe );

	// 맵에 떨어진 아이템 픽업시 키아이디 얻음
	HTdword					HT_bItemSystem_GetMapItemPickUpKeyID() {return m_dwMapItemkeyID;};

private:	
	HTvoid					HT_LL_vInitList();
	HTRESULT				HT_LL_hrDeleteNode( int info );
	HT_NODE*				HT_LL_hrDeleteAll();

	// 내구도가 낮은 아이템인지 검사
	HTbool					HT_bItemSystem_CheckDurabilityWarning( HTdword dwKeyID );
	
	//-----------------------------------------------------------------------------
	// HTvoid					HT_vSetDurabilityMsg(HTint iItemNo, HTint dwItemID, HTint iDurability)
	// D : 내구도 변경에 따른 수리 표시 메세지 설정 및 소리 
	//-----------------------------------------------------------------------------
	HTvoid					HT_vSetDurabilityMsg( );
	// 현재 내구도 경고 표시하는 아이템 설정을 해제한다.
	HTvoid					HT_vItemSystem_DelDurabilityWarning( );

	HTvoid					HT_vShowItemName() { m_bShowItemName = !m_bShowItemName; };

	//--------------------------------------------------------------------------
	// 메세지 출력
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
	HTbool					m_bTReformNeed; // 내구도 경고 필요한지
	HTint					m_iNeedReformPlace;	// 내구도 경고하고 있는 아이템의 장착 위치
	HTfloat					m_flastWarningTime;	// 마지막으로 내구도 경고한 시간

	HTdword					m_dwMapItemkeyID;	// 땅에 떨어진 아이템 픽업의 KeyID

	//	지정 되었음을 보여주는 이펙트
	HTint					m_iItemTargettingEffectID;
	HTbool					m_bShowItemName;
	// 메세지 관련
	HTdword					m_dwMsgItemKeyID;
	CHTString				m_strMsgCharName;
};

#endif

