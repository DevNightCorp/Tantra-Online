#ifndef _HTItemControl_h_
#define _HTItemControl_h_

class CHTTimer;

// 복권 아이템 인덱스
#define LOTTERY_ITEM_INDEX				7100
#define LOTTERY_ITEM_INDEX_FAIL			7130	// 꽝복권
// 이동의 푸스티카 아이템
#define HT_ITEM_MOVE_PUSTICA			7011
// 지바 푸스티카 아이템
#define HT_ITEM_MOVE_JIVAPUSTICA		7028
// 향상된 지바 푸스티카 아이템
#define HT_ITEM_MOVE_UPGRADEJIVAPUSTICA	7034
// 고급지역입장권
#define HT_ITEM_HIGHZONE_TICKET			7049
// 차크라 초기화 아이템
#define HT_ITEM_INIT_CHAKRA				7026
// 스킬 초기화 아이템
#define HT_ITEM_INIT_SKILL				7027
//	정광판 아이템 (호외)
#define HT_ITEM_OPEN_MESSAGE			7038
//	정광판 아이템 (전투명령서)
#define HT_ITEM_COMBAT_MESSAGE			7043
//	부활주문서
#define HT_ITEM_REVIVALBOOK				7031
//	고급 부활주문서
#define HT_ITEM_UPGRADEREVIVALBOOK		7039
//	요새 이동의 푸스티카
#define HT_ITEM_FORTRESSPUSTICA			7072
//	파티원 소환 주문서
#define HT_ITEM_PARTYMEMBERCALL			7078
//	공성 이동의 푸스티카
#define HT_ITEM_SIEGEPUSTICA			6732
//	위치 이동 푸스티카
#define HT_ITEM_MOVEPOSPUSTICA			6748

//	주신 변경 아이템
#define HT_ITEM_CHANGEGODCHARM1			6747	//	시바로 주신을 변경
#define HT_ITEM_CHANGEGODCHARM2			6754	//	브라흐마로 주신을 변경
#define HT_ITEM_CHANGEGODCHARM3			6755	//	비슈누로 주신을 변경


#define MAX_MAP_SIZE					1024

// 소모성 아이템이 사용되는 순간의 위치
#define ITEM_USE_LOC_INVEN				0x01
#define ITEM_USE_LOC_QUICKSLOT			0x02

#define ITEMPACKING_TYPE_PACKING	1
#define ITEMPACKING_TYPE_UNPACKING	2

//-----------------------------------------------------------------------------//
//  설명 : 아이템이 들어갈 수 있는 인벤토리의 좌표
//  작성일자 / 작성자 : 정의규 / 2002.11.09
//-----------------------------------------------------------------------------//
typedef struct _ItemLocationPos
{
	HTint		nLoop;
	HTPoint		pPos[10];
	HTPoint		pSize[10];
} ItemLocationPos;


//-----------------------------------------------------------------------------//
//  설명 : 아이템의 위치와 사이즈 반환값
//  작성일자 / 작성자 : 정의규 / 2002.11.11
//-----------------------------------------------------------------------------//
typedef struct _HT_ItemReturn
{
	HTPoint		pPos;
	HTPoint		pSize;
} HT_ItemReturn;

typedef struct _ITEM_USE
{
	DWORD	dwKeyID;
	HTint	index;
	HTint	iLocation;
} ITEM_USE;

class HTItemControl
{
public :
	HTItemControl(void);
	~HTItemControl(void);
	HTvoid				HT_vItemControl_CleanUp();

	//-------------------------------------------------------
	// 초기화 / 로딩
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_Init();;
	HTvoid				HT_vItemControl_Init_LoccationPosLoad();

public:
	// 이동을 위해 아이템 클릭
	HTRESULT			HT_bItemControl_ButtonCheck_SwitchOn( HTint iBeforDlgNo, HTint iBeforeCellNo, HTint iCurDlgNo, HTint iCurCellNo );
	// 이동할 위치에 아이템 클릭
	HTRESULT			HT_vItemControl_ButtonCheck_SwitchOff( HTint iDlgNo, HTint iCellNo );
	// 아이템 이동중 ESC에 의해서 창이 닫힐 경우 아이템 원래 자리에 놓기
	HTvoid				HT_vItemControl_ESC_ItemAntiActive(/*HTint nDlg*/);
	// 아이템 이동 정지
	HTvoid				HT_vItemControl_ItemAntiActive();

	// 아이템이 이동중인지 아닌지 반환
	//HTint				HT_nItemControl_ItemStatus()	{ return m_nItemControl_Status; }
	HTbool				HT_bItemControl_IsItemStatusMove();

	// 아이템이 이동가능한 아이템인지 아니면 시간제 및 특정(이동 불가능한) 아이템인지 구별하여 결과 반환
	HTbool				HT_bItemControl_IsItemTimeItem(DWORD dwItemIndex);

	// 이동중인 아이템이 있는지
	HTbool				HT_bItemControl_IsItemMove();	

	// 아이템의 위치와 사이즈 반환값
	HTPoint				HT_ptItemControl_LoctionSize( HTint Location );
	// 인벤토리에 아이템을 넣을 위치가 있는지 검사
	HTint				HT_iItemControl_SearchInventory( DWORD dwItemKeyID, HTint iInventory, HTPoint& pPt );

	// 마우스가 어떤 윈도우 안에 있는지 체크
	HT_ItemReturnRoom	HT_vItemControl_ActiveEachWindowCheck( HTint iDlgNo, HTint iCellNo );
	// 선택한 아이템을 이동(활성화)중인 아이템으로 셋팅
	HTvoid				HT_vItemControl_SelectItemCheck( HT_ItemReturnRoom );
	// 이동중인 아이템을 넣을 위치 정보 설정
	HTvoid				HT_vItemControl_SecurityItemSettingPos( HT_ItemReturnRoom );
	// 제한 사항 체크
	//	1. 다른 아이템이 장착돼어 있을 때
	//	2. 같은곳
	//	3. 인벤토리 사이즈
	//	4. 인벤토리 외부_윈도우 안 다른곳을 클릭 했을 때
	//	5. 장착 불가
	HTbool				HT_bItemControl_Limit_InInventory( HTbool );
	//	6. 맵위에서 다른 아이템이 없는 곳을 찾기
	HTbool				HT_vItemControl_Limit_InMap();

	// 제련을 위해 사용할 보조재료 정보 설정
	HTvoid				HT_vItemControl_EconomySetting( DWORD );
	// 제련창에 아이템을 놓을 경우 위치 교정
	HTvoid				HT_vItemControl_EconomyLocationCheck( );

	// 캐릭터 주변의 맵 좌표 중 빈 곳 찾기
	HTPoint				HT_ptItemControl_SearchMapPosForItemDrop();

	// 장착했던 아이템을 벗었을 경우의 처리
	HTvoid				HT_vItemControl_ItemMove_UnEquip( HTint iInventory );
	// 장착했을 경우의 처리
	HTvoid				HT_vItemControl_ItemMove_Equip( HTdword dwActiveItemKeyID, HTint iTargetInventory );

	// 화살 자동 채우기 - 찾은 아이템의 KeyID 반환
	HTbool				HT_bItemControl_RefillArrow( HTdword dwKeyID, HTdword dwItemIndex );

	//-------------------------------------------------------
	// 아이템 언패킹
	//-------------------------------------------------------
	// 보관중인 위치 설정 
	HTvoid				HT_vItemControl_SetMoveFromPlace( HTint nDlgNo, HT_ItemReturnRoom );
	// 이동할 위치 설정
	HTbool				HT_bItemControl_SetMoveToPlace( HTint nDlgNo );
	// 언패킹할 아이템을 넣을 위치가 있는지 검사
	HTint				HT_iItemControl_SearchPosForUnPack( HTint iLocation, HTint iInventory, HTPoint& pPt );

	//-------------------------------------------------------
	// 컨트롤
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_Control();

	// 맵에서 아이템 줍기
	HTvoid				HT_vItemControl_Control_PickUpItem();
	
	// 작업할 아이템을 지정
	HTvoid				HT_vItemControl_SetTargetItem( DWORD );
	DWORD				HT_dwItemControl_GetActiveItemKeyID() { return m_dwActiveItemKeyID; }

	// 아이템 셋팅
	HTvoid				HT_vItemControl_SettingItem( HTbool );

	//	조교모자를 썼는지 안썼는지 판단
	HTbool				HT_bItemControl_GetAssistant()	{ return m_bAssistant;	};
	HTvoid				HT_bItemControl_SetAssistant( HTbool bFlag )	{ m_bAssistant = bFlag;	};

	//-------------------------------------------------------
	// 아이템 사용
	//-------------------------------------------------------
	// 소모성 아이템(물약 등)인지 검사
	HTRESULT			HT_hrItemControl_ItemUse( HTint nDlgNo, HTdword dwItemKeyID );
	HTRESULT			HT_hrItemControl_ItemUse( HTdword dwKeyID );

	// bag전환을 위한 타이머 시작
	HTvoid				HT_vStartTimeForBag( HTint iSelectedBagNo );	
	HTvoid				HT_vEndTimeForBag();
	// 인벤토리 크기 확장
	HTvoid				HT_vItemControl_ExpandInventorySize( HTint& iBagSize , HTint iInventory );
	
	// 프리미엄 아이템 사용
	HTint				HT_iItemControl_SetPrimiumItem( HTint iIndex, HTint iAddDay );

	//-------------------------------------------------------
	// 네트워크 관련
	//-------------------------------------------------------
	// 장착 위치 체크
	HTbool				HT_bItemControl_Network_ReqEquip_LocationCheck(DWORD dwItemIndex);
	// 서버에 아이템 이동
	HTvoid				HT_vItemControl_Network_ReqMove();
	HTvoid				HT_vItemControl_Network_ReqMove_Result( PS_SCP_RESP_ITEM_MOVE info );
	// 서버에 이동 요청 결과로 내려온 아이템의 source/target 위치 설정
	HTbool				HT_bItemControl_ReqMoveResult_SetItemPos(PS_SCP_RESP_ITEM_MOVE info);
	// 서버에 이동 요청한후 취해야할 액션들
	HTvoid				HT_vItemControl_Network_ReqMove_Result_Check();

	// 맵에 버리기
	HTvoid				HT_vItemControl_Network_ReqDrop( );
	HTvoid				HT_vItemControl_Network_ReqDrop_Result( PS_SCP_RESP_ITEM_DROP info );

	// 맵에서 줍기
	HTvoid				HT_vItemControl_Network_ReqGet();
	HTvoid				HT_vItemControl_Network_ReqGet_Result( PS_SCP_RESP_ITEM_GET info );

	// 아이템 패킹
	HTvoid				HT_vItemControl_Network_Req_ItemPacking( HTbyte byType );
	HTvoid				HT_vItemControl_Network_Resp_ItemPacking( MSG_Packing* info );
	
	// 아이템 사용
	HTvoid				HT_vNetWork_CSP_RESP_Item_Use( DWORD, /*BYTE,*/ BYTE, HTchar* pStr = HT_NULL );
	HTvoid				HT_vNetWork_SCP_RESP_Item_Use_Result( MSG_ITEM* info );

	//	Get m_bPotionItemUse_Sw
	HTbool				HT_vItemControl_GetItemUseSw();

private:
	//-------------------------------------------------------
	// 출력 메세지 설정
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_SetMessage( HTint idMessage );
	HTvoid				HT_vItemControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//-----------------------------------------------------------------------------
	// HTvoid				HT_vReformDurability(HTdword dwID)
	// D : 현재 내구도에 따른 수리 표시 갱신
	//-----------------------------------------------------------------------------
	//HTvoid				HT_vReformDurability(HTdword dwID);

	//-----------------------------------------------------------------------------
	// HTvoid				HT_vDelDurability(HTdword dwID)
	// D : 탈착에 따른 내구도 표시 변경
	//-----------------------------------------------------------------------------
	//HTvoid				HT_vDelDurability(HTdword dwID);

public :
	HTint				m_nItemControl_Status;

	//----- 컨트롤(이동) 하는 아이템 -----//
	DWORD				m_dwActiveItemKeyID; // 이동되고 있는 아이템
	DWORD				m_dwActiveItemIndex;	

	// 아이템을 줍기 위해 이동하는 사이에 다른 아이템을 조작할 경우를 위해서 KeyID를 따로 둠
	DWORD				m_dwGetItemKeyID; // 주울 아이템

	//----- 패킹용 Target 아이템 -----//
	DWORD				m_nDestItemKeyID;

	//-- 사용한 아이템(소모성 아이템) ---//
	DWORD				m_dwUseItemKeyID;
	DWORD				m_dwSelectedUseItemKeyID;	// 선택된 아이템 KeyID (7077 아이템에서만 사용됨)

	//-----맵위의 아이템을 지정했는가?-----//
	HTbool				m_bSetTargetItem_Sw;

	//-----아이템 이동_소스 정보-----//
	HT_ITEMSETTING_FLAG	m_sSource_Item;

	//-----아이템 이동_타겟 정보-----//
	HT_ITEMSETTING_FLAG	m_sTarget_Item;

	//-----아이템 장착할수 있는공간에 바표현-----//
	HTPoint				m_pPossible_BarSize;
	HT_ItemReturnRoom	m_sPossible_BarInfo;	

	//-----아이템 사용한건지 파악-----//
    HTbool				m_bPotionItemUse_Sw;

	//-----아이템 사용후 딜레이 타임-----//
	DWORD				m_dwItemUse_DelayTime;

	//--------- 아이템 언패킹 관련 정보 -----------//
	BYTE					m_byFromPlace;		// 보관중인 위치
	BYTE					m_byToPlace;		// 이동할 위치
	HTint					m_nUnPackCount;		// 아이템 언패킹 개수

	//--------- 메세지 창에 대한 정보 -------------//
	BYTE					m_byMessageWin;		// 현재 메세지창
	BYTE					m_byResent;			// 현재 작업 
	CHTString				m_szMessage;		// 현재 메세지창에 보여줄 내용
	CHTString				m_szObjectName;		// 메세지에 출력할 아이템 이름
	HTint					m_iMoneyForMessage; // 출력할 돈 	
	
	HTbool					m_bAssistant;		//	조교모자를 썼는지 안썼는지
private:
	HTfloat					m_fTimeForBag;	// bag 전환을 위한 시간
	HTint					m_iSelectBagNo;	// 체크하고 있는 bag
	CHTTimer*				m_pTimer;
};
#endif // #ifndef _HTItemControl_h_