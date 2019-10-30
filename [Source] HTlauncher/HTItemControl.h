#ifndef _HTItemControl_h_
#define _HTItemControl_h_

class CHTTimer;

// ���� ������ �ε���
#define LOTTERY_ITEM_INDEX				7100
#define LOTTERY_ITEM_INDEX_FAIL			7130	// �κ���
// �̵��� Ǫ��Ƽī ������
#define HT_ITEM_MOVE_PUSTICA			7011
// ���� Ǫ��Ƽī ������
#define HT_ITEM_MOVE_JIVAPUSTICA		7028
// ���� ���� Ǫ��Ƽī ������
#define HT_ITEM_MOVE_UPGRADEJIVAPUSTICA	7034
// ������������
#define HT_ITEM_HIGHZONE_TICKET			7049
// ��ũ�� �ʱ�ȭ ������
#define HT_ITEM_INIT_CHAKRA				7026
// ��ų �ʱ�ȭ ������
#define HT_ITEM_INIT_SKILL				7027
//	������ ������ (ȣ��)
#define HT_ITEM_OPEN_MESSAGE			7038
//	������ ������ (������ɼ�)
#define HT_ITEM_COMBAT_MESSAGE			7043
//	��Ȱ�ֹ���
#define HT_ITEM_REVIVALBOOK				7031
//	��� ��Ȱ�ֹ���
#define HT_ITEM_UPGRADEREVIVALBOOK		7039
//	��� �̵��� Ǫ��Ƽī
#define HT_ITEM_FORTRESSPUSTICA			7072
//	��Ƽ�� ��ȯ �ֹ���
#define HT_ITEM_PARTYMEMBERCALL			7078
//	���� �̵��� Ǫ��Ƽī
#define HT_ITEM_SIEGEPUSTICA			6732
//	��ġ �̵� Ǫ��Ƽī
#define HT_ITEM_MOVEPOSPUSTICA			6748

//	�ֽ� ���� ������
#define HT_ITEM_CHANGEGODCHARM1			6747	//	�ùٷ� �ֽ��� ����
#define HT_ITEM_CHANGEGODCHARM2			6754	//	����帶�� �ֽ��� ����
#define HT_ITEM_CHANGEGODCHARM3			6755	//	�񽴴��� �ֽ��� ����


#define MAX_MAP_SIZE					1024

// �Ҹ� �������� ���Ǵ� ������ ��ġ
#define ITEM_USE_LOC_INVEN				0x01
#define ITEM_USE_LOC_QUICKSLOT			0x02

#define ITEMPACKING_TYPE_PACKING	1
#define ITEMPACKING_TYPE_UNPACKING	2

//-----------------------------------------------------------------------------//
//  ���� : �������� �� �� �ִ� �κ��丮�� ��ǥ
//  �ۼ����� / �ۼ��� : ���Ǳ� / 2002.11.09
//-----------------------------------------------------------------------------//
typedef struct _ItemLocationPos
{
	HTint		nLoop;
	HTPoint		pPos[10];
	HTPoint		pSize[10];
} ItemLocationPos;


//-----------------------------------------------------------------------------//
//  ���� : �������� ��ġ�� ������ ��ȯ��
//  �ۼ����� / �ۼ��� : ���Ǳ� / 2002.11.11
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
	// �ʱ�ȭ / �ε�
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_Init();;
	HTvoid				HT_vItemControl_Init_LoccationPosLoad();

public:
	// �̵��� ���� ������ Ŭ��
	HTRESULT			HT_bItemControl_ButtonCheck_SwitchOn( HTint iBeforDlgNo, HTint iBeforeCellNo, HTint iCurDlgNo, HTint iCurCellNo );
	// �̵��� ��ġ�� ������ Ŭ��
	HTRESULT			HT_vItemControl_ButtonCheck_SwitchOff( HTint iDlgNo, HTint iCellNo );
	// ������ �̵��� ESC�� ���ؼ� â�� ���� ��� ������ ���� �ڸ��� ����
	HTvoid				HT_vItemControl_ESC_ItemAntiActive(/*HTint nDlg*/);
	// ������ �̵� ����
	HTvoid				HT_vItemControl_ItemAntiActive();

	// �������� �̵������� �ƴ��� ��ȯ
	//HTint				HT_nItemControl_ItemStatus()	{ return m_nItemControl_Status; }
	HTbool				HT_bItemControl_IsItemStatusMove();

	// �������� �̵������� ���������� �ƴϸ� �ð��� �� Ư��(�̵� �Ұ�����) ���������� �����Ͽ� ��� ��ȯ
	HTbool				HT_bItemControl_IsItemTimeItem(DWORD dwItemIndex);

	// �̵����� �������� �ִ���
	HTbool				HT_bItemControl_IsItemMove();	

	// �������� ��ġ�� ������ ��ȯ��
	HTPoint				HT_ptItemControl_LoctionSize( HTint Location );
	// �κ��丮�� �������� ���� ��ġ�� �ִ��� �˻�
	HTint				HT_iItemControl_SearchInventory( DWORD dwItemKeyID, HTint iInventory, HTPoint& pPt );

	// ���콺�� � ������ �ȿ� �ִ��� üũ
	HT_ItemReturnRoom	HT_vItemControl_ActiveEachWindowCheck( HTint iDlgNo, HTint iCellNo );
	// ������ �������� �̵�(Ȱ��ȭ)���� ���������� ����
	HTvoid				HT_vItemControl_SelectItemCheck( HT_ItemReturnRoom );
	// �̵����� �������� ���� ��ġ ���� ����
	HTvoid				HT_vItemControl_SecurityItemSettingPos( HT_ItemReturnRoom );
	// ���� ���� üũ
	//	1. �ٸ� �������� �����ž� ���� ��
	//	2. ������
	//	3. �κ��丮 ������
	//	4. �κ��丮 �ܺ�_������ �� �ٸ����� Ŭ�� ���� ��
	//	5. ���� �Ұ�
	HTbool				HT_bItemControl_Limit_InInventory( HTbool );
	//	6. �������� �ٸ� �������� ���� ���� ã��
	HTbool				HT_vItemControl_Limit_InMap();

	// ������ ���� ����� ������� ���� ����
	HTvoid				HT_vItemControl_EconomySetting( DWORD );
	// ����â�� �������� ���� ��� ��ġ ����
	HTvoid				HT_vItemControl_EconomyLocationCheck( );

	// ĳ���� �ֺ��� �� ��ǥ �� �� �� ã��
	HTPoint				HT_ptItemControl_SearchMapPosForItemDrop();

	// �����ߴ� �������� ������ ����� ó��
	HTvoid				HT_vItemControl_ItemMove_UnEquip( HTint iInventory );
	// �������� ����� ó��
	HTvoid				HT_vItemControl_ItemMove_Equip( HTdword dwActiveItemKeyID, HTint iTargetInventory );

	// ȭ�� �ڵ� ä��� - ã�� �������� KeyID ��ȯ
	HTbool				HT_bItemControl_RefillArrow( HTdword dwKeyID, HTdword dwItemIndex );

	//-------------------------------------------------------
	// ������ ����ŷ
	//-------------------------------------------------------
	// �������� ��ġ ���� 
	HTvoid				HT_vItemControl_SetMoveFromPlace( HTint nDlgNo, HT_ItemReturnRoom );
	// �̵��� ��ġ ����
	HTbool				HT_bItemControl_SetMoveToPlace( HTint nDlgNo );
	// ����ŷ�� �������� ���� ��ġ�� �ִ��� �˻�
	HTint				HT_iItemControl_SearchPosForUnPack( HTint iLocation, HTint iInventory, HTPoint& pPt );

	//-------------------------------------------------------
	// ��Ʈ��
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_Control();

	// �ʿ��� ������ �ݱ�
	HTvoid				HT_vItemControl_Control_PickUpItem();
	
	// �۾��� �������� ����
	HTvoid				HT_vItemControl_SetTargetItem( DWORD );
	DWORD				HT_dwItemControl_GetActiveItemKeyID() { return m_dwActiveItemKeyID; }

	// ������ ����
	HTvoid				HT_vItemControl_SettingItem( HTbool );

	//	�������ڸ� ����� �Ƚ���� �Ǵ�
	HTbool				HT_bItemControl_GetAssistant()	{ return m_bAssistant;	};
	HTvoid				HT_bItemControl_SetAssistant( HTbool bFlag )	{ m_bAssistant = bFlag;	};

	//-------------------------------------------------------
	// ������ ���
	//-------------------------------------------------------
	// �Ҹ� ������(���� ��)���� �˻�
	HTRESULT			HT_hrItemControl_ItemUse( HTint nDlgNo, HTdword dwItemKeyID );
	HTRESULT			HT_hrItemControl_ItemUse( HTdword dwKeyID );

	// bag��ȯ�� ���� Ÿ�̸� ����
	HTvoid				HT_vStartTimeForBag( HTint iSelectedBagNo );	
	HTvoid				HT_vEndTimeForBag();
	// �κ��丮 ũ�� Ȯ��
	HTvoid				HT_vItemControl_ExpandInventorySize( HTint& iBagSize , HTint iInventory );
	
	// �����̾� ������ ���
	HTint				HT_iItemControl_SetPrimiumItem( HTint iIndex, HTint iAddDay );

	//-------------------------------------------------------
	// ��Ʈ��ũ ����
	//-------------------------------------------------------
	// ���� ��ġ üũ
	HTbool				HT_bItemControl_Network_ReqEquip_LocationCheck(DWORD dwItemIndex);
	// ������ ������ �̵�
	HTvoid				HT_vItemControl_Network_ReqMove();
	HTvoid				HT_vItemControl_Network_ReqMove_Result( PS_SCP_RESP_ITEM_MOVE info );
	// ������ �̵� ��û ����� ������ �������� source/target ��ġ ����
	HTbool				HT_bItemControl_ReqMoveResult_SetItemPos(PS_SCP_RESP_ITEM_MOVE info);
	// ������ �̵� ��û���� ���ؾ��� �׼ǵ�
	HTvoid				HT_vItemControl_Network_ReqMove_Result_Check();

	// �ʿ� ������
	HTvoid				HT_vItemControl_Network_ReqDrop( );
	HTvoid				HT_vItemControl_Network_ReqDrop_Result( PS_SCP_RESP_ITEM_DROP info );

	// �ʿ��� �ݱ�
	HTvoid				HT_vItemControl_Network_ReqGet();
	HTvoid				HT_vItemControl_Network_ReqGet_Result( PS_SCP_RESP_ITEM_GET info );

	// ������ ��ŷ
	HTvoid				HT_vItemControl_Network_Req_ItemPacking( HTbyte byType );
	HTvoid				HT_vItemControl_Network_Resp_ItemPacking( MSG_Packing* info );
	
	// ������ ���
	HTvoid				HT_vNetWork_CSP_RESP_Item_Use( DWORD, /*BYTE,*/ BYTE, HTchar* pStr = HT_NULL );
	HTvoid				HT_vNetWork_SCP_RESP_Item_Use_Result( MSG_ITEM* info );

	//	Get m_bPotionItemUse_Sw
	HTbool				HT_vItemControl_GetItemUseSw();

private:
	//-------------------------------------------------------
	// ��� �޼��� ����
	//-------------------------------------------------------
	HTvoid				HT_vItemControl_SetMessage( HTint idMessage );
	HTvoid				HT_vItemControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	//-----------------------------------------------------------------------------
	// HTvoid				HT_vReformDurability(HTdword dwID)
	// D : ���� �������� ���� ���� ǥ�� ����
	//-----------------------------------------------------------------------------
	//HTvoid				HT_vReformDurability(HTdword dwID);

	//-----------------------------------------------------------------------------
	// HTvoid				HT_vDelDurability(HTdword dwID)
	// D : Ż���� ���� ������ ǥ�� ����
	//-----------------------------------------------------------------------------
	//HTvoid				HT_vDelDurability(HTdword dwID);

public :
	HTint				m_nItemControl_Status;

	//----- ��Ʈ��(�̵�) �ϴ� ������ -----//
	DWORD				m_dwActiveItemKeyID; // �̵��ǰ� �ִ� ������
	DWORD				m_dwActiveItemIndex;	

	// �������� �ݱ� ���� �̵��ϴ� ���̿� �ٸ� �������� ������ ��츦 ���ؼ� KeyID�� ���� ��
	DWORD				m_dwGetItemKeyID; // �ֿ� ������

	//----- ��ŷ�� Target ������ -----//
	DWORD				m_nDestItemKeyID;

	//-- ����� ������(�Ҹ� ������) ---//
	DWORD				m_dwUseItemKeyID;
	DWORD				m_dwSelectedUseItemKeyID;	// ���õ� ������ KeyID (7077 �����ۿ����� ����)

	//-----������ �������� �����ߴ°�?-----//
	HTbool				m_bSetTargetItem_Sw;

	//-----������ �̵�_�ҽ� ����-----//
	HT_ITEMSETTING_FLAG	m_sSource_Item;

	//-----������ �̵�_Ÿ�� ����-----//
	HT_ITEMSETTING_FLAG	m_sTarget_Item;

	//-----������ �����Ҽ� �ִ°����� ��ǥ��-----//
	HTPoint				m_pPossible_BarSize;
	HT_ItemReturnRoom	m_sPossible_BarInfo;	

	//-----������ ����Ѱ��� �ľ�-----//
    HTbool				m_bPotionItemUse_Sw;

	//-----������ ����� ������ Ÿ��-----//
	DWORD				m_dwItemUse_DelayTime;

	//--------- ������ ����ŷ ���� ���� -----------//
	BYTE					m_byFromPlace;		// �������� ��ġ
	BYTE					m_byToPlace;		// �̵��� ��ġ
	HTint					m_nUnPackCount;		// ������ ����ŷ ����

	//--------- �޼��� â�� ���� ���� -------------//
	BYTE					m_byMessageWin;		// ���� �޼���â
	BYTE					m_byResent;			// ���� �۾� 
	CHTString				m_szMessage;		// ���� �޼���â�� ������ ����
	CHTString				m_szObjectName;		// �޼����� ����� ������ �̸�
	HTint					m_iMoneyForMessage; // ����� �� 	
	
	HTbool					m_bAssistant;		//	�������ڸ� ����� �Ƚ����
private:
	HTfloat					m_fTimeForBag;	// bag ��ȯ�� ���� �ð�
	HTint					m_iSelectBagNo;	// üũ�ϰ� �ִ� bag
	CHTTimer*				m_pTimer;
};
#endif // #ifndef _HTItemControl_h_