#ifndef __HTITEMFAL_H__
#define __HTITEMFAL_H__

class CHTItemAl
{
public:
	CHTItemAl();
	~CHTItemAl();

	//---------------------------------------------------------------------
	// 아이템 생성
	//---------------------------------------------------------------------	
	HTvoid				HT_vItemCreate( PS_SCP_MAP_ITEM_APPEAR info );
	HTvoid				HT_vItemCreate( HTbyte byPlace, HTint iKeyID, STRUCT_ITEM info );
	HTvoid				HT_vItemCreate( HTbyte byLocation, HTbyte byX, HTbyte byZ, HTint iKeyID, 
										STRUCT_ITEM info, HTbyte byBagNo = -1 );

	//---------------------------------------------------------------------
	// 아이템 모델 생성
	//---------------------------------------------------------------------	
	// 3D모델
	HTvoid				HT_vItemCreate_Object(); 
	HTvoid				HT_vItemCreate_Destory(); 
	// 2D 모델
	HTvoid				HT_vSystem_Create2DItem();
	HTvoid				HT_vSystem_Delete2DItem();

	// 인벤토리내의 아이템 셋팅하기
	HTvoid				HT_vItemAlSettingInventoryPos( HT_ITEMSETTING_FLAG flag, HTbool bDrawTwinImage = HT_TRUE );

	//---------------------------------------------------------------------
	// 맵 위의 아이템
	//---------------------------------------------------------------------	
	// 맵상의 캐릭터와 아이템의 셀위치 비교
	HTbool				HT_bComCharacterAndItem();
	// 맵상에 아이템을 버림-맵에 아이템이 생성
	HTvoid				HT_vItemAlThrowMap( HTint, HTint );
	//	맵위의 그리드 위치 알아오기	
	HTPoint				HT_ptGeItemSystemCell();				
	
	HTvoid				HT_vItemAlRender();
	
	//---------------------------------------------------------------------
	// 착용제한 사항
	//---------------------------------------------------------------------	
	// 착용제한 사항에 걸리는지 검사
	HTbool				HT_bItemAl_PossibleCheck(DWORD dwItemIndex, HTbool bLevelCheck );

	//---------------------------------------------------------------------
	// 제련 정보
	//---------------------------------------------------------------------	
	// 보조재료 속성 변수 초기화
	HTvoid				HT_vItemAI_ClearSubItemInfo();
	// 강화제련 레벨 셋팅
	HTvoid				HT_vItemAI_SetMainRefineLevel( HTint iLevel )	{ m_sItemInfo.byRefineLevel = iLevel; }

	// 아이템의 장착 위치 반환
	HTvoid				HT_vItemAI_GetItemEquipPos( DWORD dwItemIndex, HTbyte* byEquipPos );

public:
	STRUCT_ITEM					m_sItemInfo;
	
	DWORD						m_dwItemKeyID;				//	아이템을 구별하기 위해서
	HTbool						m_bItemActive;				//	아이템 활성화 인자
	HTint						m_iItemDlgNo;				//	붙어있는 대화상자 방
	HTint						m_iItemLocation;			//	방
	HTint						m_iItemInInventory;			//	아이템이 위치한 인벤토리
	HTbyte						m_byItemEquipPos;			//	아이템이 장착될 수 있는 인벤토리
	
	// 아이템 종류별로 재정리한 주술제련 정보
	HTITEM_REFINE_PARAM			m_sItem_SubRefineInfo[MAX_EFFECT_NUM*MAX_REFINE_SUB_LEVEL];
	HTbyte						m_bySubEffectIDCount;
	 
	HTshort						m_sItemType;				//	일단 이것으로 아이템의 속성을 정해준다.
	HTbyte						m_byItemSizeX;				//	아이템의  x 단위 크기
	HTbyte						m_byItemSizeY;				//	아이템의  y 단위 크기
	HTbyte						m_byInventory_CellPosX;		//  인벤토리 내의 x 단위 위치
	HTbyte						m_byInventory_CellPosY;		//  인벤토리 내의 y 단위 위치

	//-----2D 스프라이트 관리-----//
	HTbool						m_bItem2DID_Sw;
	HTint						m_iCellNumber;
	HTint						m_iItemTextureID;

	//-----3D 스프라이트 관리-----//
	HTbool						m_bItem3DID_Sw;
	HTint						m_iItem3DID;
	HTshort						m_sItemMapCellX;			//	맵상의 셀좌표
	HTshort						m_sItemMapCellZ;			//	맵상의 셀좌표
	HTvector3					m_vecItem3DPosition;

	//------착용 가능/불가능 표시용-------//
	HTbool						m_bPossible;				// HT_FALSE - 착용 불가능, HT_TRUE - 착용가능

	HTbool						m_bItem_PickUp_Sw;
	CHTString					m_strItemName;

	//-----아이템 정보 보여주기-----//
	HTbool						m_bItem_Info_Sw;
};

#endif