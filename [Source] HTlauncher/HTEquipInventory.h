
#ifndef __HTINVENTORY_H__
#define __HTINVENTORY_H__

#include "HTControlDef.h"
#include "HTItem.h"
#include "HTItemSystem.h"

typedef struct _BAGINFO
{
	HTbyte		bySize;
	HTbool		bUsable;
} BAGINFO;

class CHTEquipInventory
{
public:
	CHTEquipInventory();
	~CHTEquipInventory();
	
	HTvoid		HT_vEquipInventory_CeleanUp();

	HTRESULT	HT_hrInit();
	//	Create Window
	HTvoid		HT_vEI_CreateWindow();

	//	입력 메세지 처리
	//	Equip Inventory
	static void		HT_vEI_InputCheckForEquipInven(int iAction, int iTarget, int iTargetID);
	//	Inventory2
	static void		HT_vEI_InputCheckForInven2(int iAction, int iTarget, int iTargetID);
	//	Equip GoodsKeep
	static void		HT_vEI_InputCheckForGoodsKeep(int iAction, int iTarget, int iTargetID);
	//	Charity
	static void		HT_vEI_InputCheckForCharity(int iAction, int iTarget, int iTargetID);

	//	Set Message Box
	HTvoid		HT_vEI_SetMessageBox( int iType, CHTString strMsg );
	bool		m_bUsableInventory;		// 확장 인벤토리 사용여부 체크

	//-----------------------------------------------------------
	// PC 인벤토리
	//-----------------------------------------------------------
	HTRESULT HT_hrEquipPcInventoryActiveSw();
	// 인벤토리창 띄우기
	HTvoid HT_vEquipInventory_SetActive();
	// 인벤토리창 없애기
	HTvoid HT_vEquipInventory_SetAntiActive();

	// 인벤토리 크기 초기 설정
	HTvoid		HT_vInitBagStatus( );
	// 인벤토리(bag1, bag2, bag3) 사이즈 설정
	//HTvoid		HT_vSetInventorySize( HTint nInventory, BYTE bySize );
	// 인벤토리 크기 구하기
	HTbyte		HT_byGetInventorySize( HTint nInventory );
	// 인벤토리 사용가능 여부
	HTbool		HT_bGetInventoryUsable( HTint nInventory );
	
	// 사용 불가능한 인벤토리 표시 다시 그리기
	HTvoid		HT_vRenewalPossibleBar( HTint iInventory, HTbyte byNewSize, HTbool bUsable = HT_TRUE );
	// 사용 불가능한 인벤토리 표시 삭제
	HTvoid		HT_vDelPossibleBar( HTint nInventory );

	// 해당 갯수만큼 인벤토리 공간이 있는 여부 확인 2004. 11. 29 선영범
	HTbool		HT_bGetInventoryBlank( HTint nNum );

	//-----------------------------------------------------------
	// 루피아
	//-----------------------------------------------------------
	// 루피아 이동창 띄우기
	HTvoid		HT_vRupiahWin_Active();


	// 루피아를 보관중인 위치 설정
	HTvoid		HT_vRupiahWin_SetMoveFromPlace( HTint nDlgNo );
	// 루피아를 이동할 위치 설정
	HTvoid		HT_vRupiahWin_SetMoveToPlace( HTint nDlgNo );
	// 루피아 땅에 버리기
	HTvoid		HT_vRupiahWin_ReqDropMoney( );

	HTvoid	HT_vEquipInventory_SetPCMoney(HTint iMoney);
	HTint	HT_iEquipInventory_GetPCMoney()				{ return m_iPCMoney; }

	HTvoid	HT_vEquipInventory_SetNPCMoney(HTint iMoney);
	HTint	HT_iEquipInventory_GetNPCMoney()			{ return m_iNPCMoney; }

	// 루피아 이동 요청
	HTvoid		HT_vNetwork_CSP_Req_Money_Move();
	HTvoid		HT_vNetwork_SCP_Resp_Money_Move( MSG_Money_Move* info );

	//-----------------------------------------------------------
	// 왼손/오른손에 장착한 아이템
	//-----------------------------------------------------------
	// 장착한 아이템 인덱스 정보
	HTvoid HT_vEquipInventory_SetLeftItem( DWORD dwLeftItem );
	HTvoid HT_vEquipInventory_SetRightItem( DWORD dwRightItem );
	HTvoid HT_vEquipInventory_SetRightItem_KeyID( DWORD dwItemKeyID );
	DWORD HT_dwEquipInventory_GetLeftItem();	
	DWORD HT_dwEquipInventory_GetRightItem();	
	DWORD HT_dwEquipInventory_GetRightItem_KeyID();

	// 언패킹을 위한 맴버변수
	DWORD m_dwObjectKeyID;	// 키아이디
	DWORD m_dwObjectIndex;	// 인덱스
	HTint m_nOverlapCount;  // 중첩갯수

private:

	//--------------------------------------------------------------------
	// 메세지 출력
	//--------------------------------------------------------------------
	HTvoid		HT_vEquipInventory_SetMessage( HTint idMessage );
	HTvoid		HT_vEquipInventory_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//CHTString	HT_strSetRestMark(HTint iNumber);

private:
	HTbool							m_bEquipInventoryActive;
	
	//	아이템 장착 인벤토리
//	BYTE							m_iItem_Count;

	//	왼쪽, 오른쪽에 장착되 아이템
	DWORD							m_dwEquip_LeftItem;
	DWORD							m_dwEquip_RightItem;
	DWORD							m_dwEquip_RightItemKeyID;

	// 루피아
	HTint							m_iPCMoney;
	HTint							m_iNPCMoney;

	//--------- 메세지 창에 대한 정보 -------------//
	BYTE					m_byMessageWin;			//  현재 메세지창
	HTbool					m_bMessage_Error;		//  현재 메세지창의 내용이 실패메세지 인지..
	CHTString				m_szMessage;			//  현재 메세지창에 보여줄 내용
	HTint					m_iRupiahResult;		//	실제 이동/사용/받은 루피아 금액

	//--------- 루피아 이동 관련 정보 -----------//
	BYTE					m_byFromPlace;		// 보관중인 위치
	BYTE					m_byToPlace;		// 이동할 위치
	HTint					m_nRupiah;			//	루피아 언패킹되는 금액

	//--------- 인벤토리 사이즈 관련 정보 ----------//
	BAGINFO					m_sBag1;
	BAGINFO					m_sBag2;
	BAGINFO					m_sBag3;

	//	Inventory Msg Type
	HTint					m_iEI_MsgType;
};

#endif