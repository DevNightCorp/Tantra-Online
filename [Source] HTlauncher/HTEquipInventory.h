
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

	//	�Է� �޼��� ó��
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
	bool		m_bUsableInventory;		// Ȯ�� �κ��丮 ��뿩�� üũ

	//-----------------------------------------------------------
	// PC �κ��丮
	//-----------------------------------------------------------
	HTRESULT HT_hrEquipPcInventoryActiveSw();
	// �κ��丮â ����
	HTvoid HT_vEquipInventory_SetActive();
	// �κ��丮â ���ֱ�
	HTvoid HT_vEquipInventory_SetAntiActive();

	// �κ��丮 ũ�� �ʱ� ����
	HTvoid		HT_vInitBagStatus( );
	// �κ��丮(bag1, bag2, bag3) ������ ����
	//HTvoid		HT_vSetInventorySize( HTint nInventory, BYTE bySize );
	// �κ��丮 ũ�� ���ϱ�
	HTbyte		HT_byGetInventorySize( HTint nInventory );
	// �κ��丮 ��밡�� ����
	HTbool		HT_bGetInventoryUsable( HTint nInventory );
	
	// ��� �Ұ����� �κ��丮 ǥ�� �ٽ� �׸���
	HTvoid		HT_vRenewalPossibleBar( HTint iInventory, HTbyte byNewSize, HTbool bUsable = HT_TRUE );
	// ��� �Ұ����� �κ��丮 ǥ�� ����
	HTvoid		HT_vDelPossibleBar( HTint nInventory );

	// �ش� ������ŭ �κ��丮 ������ �ִ� ���� Ȯ�� 2004. 11. 29 ������
	HTbool		HT_bGetInventoryBlank( HTint nNum );

	//-----------------------------------------------------------
	// ���Ǿ�
	//-----------------------------------------------------------
	// ���Ǿ� �̵�â ����
	HTvoid		HT_vRupiahWin_Active();


	// ���ǾƸ� �������� ��ġ ����
	HTvoid		HT_vRupiahWin_SetMoveFromPlace( HTint nDlgNo );
	// ���ǾƸ� �̵��� ��ġ ����
	HTvoid		HT_vRupiahWin_SetMoveToPlace( HTint nDlgNo );
	// ���Ǿ� ���� ������
	HTvoid		HT_vRupiahWin_ReqDropMoney( );

	HTvoid	HT_vEquipInventory_SetPCMoney(HTint iMoney);
	HTint	HT_iEquipInventory_GetPCMoney()				{ return m_iPCMoney; }

	HTvoid	HT_vEquipInventory_SetNPCMoney(HTint iMoney);
	HTint	HT_iEquipInventory_GetNPCMoney()			{ return m_iNPCMoney; }

	// ���Ǿ� �̵� ��û
	HTvoid		HT_vNetwork_CSP_Req_Money_Move();
	HTvoid		HT_vNetwork_SCP_Resp_Money_Move( MSG_Money_Move* info );

	//-----------------------------------------------------------
	// �޼�/�����տ� ������ ������
	//-----------------------------------------------------------
	// ������ ������ �ε��� ����
	HTvoid HT_vEquipInventory_SetLeftItem( DWORD dwLeftItem );
	HTvoid HT_vEquipInventory_SetRightItem( DWORD dwRightItem );
	HTvoid HT_vEquipInventory_SetRightItem_KeyID( DWORD dwItemKeyID );
	DWORD HT_dwEquipInventory_GetLeftItem();	
	DWORD HT_dwEquipInventory_GetRightItem();	
	DWORD HT_dwEquipInventory_GetRightItem_KeyID();

	// ����ŷ�� ���� �ɹ�����
	DWORD m_dwObjectKeyID;	// Ű���̵�
	DWORD m_dwObjectIndex;	// �ε���
	HTint m_nOverlapCount;  // ��ø����

private:

	//--------------------------------------------------------------------
	// �޼��� ���
	//--------------------------------------------------------------------
	HTvoid		HT_vEquipInventory_SetMessage( HTint idMessage );
	HTvoid		HT_vEquipInventory_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//CHTString	HT_strSetRestMark(HTint iNumber);

private:
	HTbool							m_bEquipInventoryActive;
	
	//	������ ���� �κ��丮
//	BYTE							m_iItem_Count;

	//	����, �����ʿ� ������ ������
	DWORD							m_dwEquip_LeftItem;
	DWORD							m_dwEquip_RightItem;
	DWORD							m_dwEquip_RightItemKeyID;

	// ���Ǿ�
	HTint							m_iPCMoney;
	HTint							m_iNPCMoney;

	//--------- �޼��� â�� ���� ���� -------------//
	BYTE					m_byMessageWin;			//  ���� �޼���â
	HTbool					m_bMessage_Error;		//  ���� �޼���â�� ������ ���и޼��� ����..
	CHTString				m_szMessage;			//  ���� �޼���â�� ������ ����
	HTint					m_iRupiahResult;		//	���� �̵�/���/���� ���Ǿ� �ݾ�

	//--------- ���Ǿ� �̵� ���� ���� -----------//
	BYTE					m_byFromPlace;		// �������� ��ġ
	BYTE					m_byToPlace;		// �̵��� ��ġ
	HTint					m_nRupiah;			//	���Ǿ� ����ŷ�Ǵ� �ݾ�

	//--------- �κ��丮 ������ ���� ���� ----------//
	BAGINFO					m_sBag1;
	BAGINFO					m_sBag2;
	BAGINFO					m_sBag3;

	//	Inventory Msg Type
	HTint					m_iEI_MsgType;
};

#endif