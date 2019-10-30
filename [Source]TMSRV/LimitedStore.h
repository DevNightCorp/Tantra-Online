#pragma once
#include "Basedef.h"

class CLimitedStore
{
public:
	CLimitedStore(void);
	~CLimitedStore(void);

	void			Initialize();
	void			ReadItemList();
	bool			GetItem(DWORD dwNPCID, DWORD dwItemID, S_SellItem* pItem);
	bool			GetItemList(DWORD dwNPCID, S_SellItem* pItemList);
	int				GetItemPrice(DWORD dwNPCID, DWORD dwItemID);
	int				GetItemCount(DWORD dwNPCID, DWORD dwItemID, int* pnCount);
	int				BuyItem(DWORD dwNPCID, DWORD dwItemID, short snCount);
	bool			ResetItemList(DWORD dwNPCID, S_SellItem* pItemList);
	bool			IsSellingItem(DWORD dwNPCID, DWORD dwItemID);

	S_LimitedStore	m_stStore;
};
