#include "limitedstore.h"
#include "HTParamMgr.h"

extern CHTParameterMgr g_ParamMgr;

CLimitedStore::CLimitedStore(void)
{
}

CLimitedStore::~CLimitedStore(void)
{
}

void CLimitedStore::Initialize()
{
	ZeroMemory(	&m_stStore, sizeof(m_stStore) );
}

void CLimitedStore::ReadItemList()
{
	FILE *fp = fopen(FILE_LIMITEDSTORE,"rt");
	if ( fp != NULL )
	{
		fscanf(fp, "%d", &m_stStore.nNPCID);
		if(m_stStore.nNPCID == 0) return;

		byte byLevel = 0;
		short snX, snY = 0;
		unsigned long dwItemID = 0;
		unsigned long dwItemIndex = 0;
		unsigned long dwMaxItemIndex = HT_PARAMTYPE_ITEM_END-HT_PARAMTYPE_ITEM_START+1;
		bool bFlag = CHTParamIDCheck::HT_bIsNPC( m_stStore.nNPCID );
		bFlag &= g_ParamMgr.HT_bGetNPCPosition( m_stStore.nNPCID, &snX, &snY );
		if(!bFlag) { ZeroMemory(&m_stStore, sizeof(m_stStore)); return; }

		for(int k=1; k<MAX_LIMITEDITEM+1; k++)
		{
			fscanf(fp, "%d %d %d", &m_stStore.stItem[k].dwItemID, &m_stStore.stItem[k].dwPrice, &m_stStore.stItem[k].dwCount);
			if(m_stStore.stItem[k].dwItemID==0) break;

			dwItemID = m_stStore.stItem[k].dwItemID;
			bFlag = CHTParamIDCheck::HT_bIsItem( dwItemID );
			if(!bFlag) { ZeroMemory(&m_stStore, sizeof(m_stStore)); return; }
		}

	}
}

bool CLimitedStore::GetItemList(DWORD dwNPCID, S_SellItem* pItemList)
{

	if(m_stStore.nNPCID != dwNPCID) return false;

	memcpy(pItemList, m_stStore.stItem, sizeof(m_stStore.stItem));
	return true;

	return false;
}

bool CLimitedStore::GetItem(DWORD dwNPCID, DWORD dwItemID, S_SellItem* pItem)
{

	if(m_stStore.nNPCID != dwNPCID) return false;

	for(int k=0; k<MAX_LIMITEDITEM; k++)
	{
		if(dwItemID == m_stStore.stItem[k+1].dwItemID)
		{
			*pItem = m_stStore.stItem[k+1];
			return true;
		}
	}

	return false;
}

int CLimitedStore::GetItemPrice(DWORD dwNPCID, DWORD dwItemID)
{
	S_SellItem stItem;

	bool bFlag = GetItem(dwNPCID, dwItemID, &stItem);
	if(!bFlag) return -1;

	return (int)stItem.dwPrice;
}

int CLimitedStore::GetItemCount(DWORD dwNPCID, DWORD dwItemID, int* pnCount)
{
	for(int i=0; i<MAX_LIMITEDITEM; i++)
	{
		if(m_stStore.stItem[i+1].dwItemID == 0) break;
		if(dwItemID == m_stStore.stItem[i+1].dwItemID)
		{
			*pnCount = m_stStore.stItem[i+1].dwCount;
			return i+1;
		}
	}

	return -1;
}

int CLimitedStore::BuyItem(DWORD dwNPCID, DWORD dwItemID, short snCount)
{
	S_SellItem stItem;

	int nCount = 0;
	int nIndex = GetItemCount(dwNPCID, dwItemID, &nCount);
	if(nIndex<0 || nIndex>MAX_LIMITEDITEM) return -1;
	if(m_stStore.stItem[nIndex].dwCount==0) return 0; 
	if(m_stStore.stItem[nIndex].dwCount>=snCount)	//	재고보다 많은 아이템을 사려는 경우(재고 만큼 사진다)
	{
		m_stStore.stItem[nIndex].dwCount -= snCount;
		return (int)snCount;
	}

	return 0;
}

bool CLimitedStore::ResetItemList(DWORD dwNPCID, S_SellItem* pItemList)
{
	if(pItemList == NULL) return false;
	if(dwNPCID != m_stStore.nNPCID) return false;
	
	for(int k=1; k<MAX_LIMITEDITEM+1; k++)
	{
		if(pItemList[k].dwItemID==0) break;
		if(!CHTParamIDCheck::HT_bIsItem( pItemList[k].dwItemID )) return false;
	}

	ZeroMemory(m_stStore.stItem, sizeof(m_stStore.stItem));
	memcpy(m_stStore.stItem, pItemList, sizeof(S_SellItem)*k);

	return true;;
}

bool CLimitedStore::IsSellingItem(DWORD dwNPCID, DWORD dwItemID)
{
	if(dwNPCID != m_stStore.nNPCID) return false;
	for(int k=1; k<MAX_LIMITEDITEM+1; k++)
	{
		if(m_stStore.stItem[k].dwItemID==0) return false;
		if(m_stStore.stItem[k].dwItemID==dwItemID) return true;
	}
	return false;
}

