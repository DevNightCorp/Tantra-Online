#ifndef __RENTALSTORE_H__
#define __RENTALSTORE_H__

#include <set>
#include <io.h>
#include <fcntl.h>
#include "BaseDef.h"
#include "EventDefines.h"


class CRentalStore
{
private:
	DWORD				m_dwEraseTime;
	STRUCT_RENTALITEM	m_starrItem[MAX_RENTALSTORE*MAX_RENTALSTOREITEM];
	STURCT_RENTALAWARD	m_starrMoney[MAX_RENTALUSER];
	STRUCT_RENTALSTOCK	m_starrStockItem[MAX_RENTALITEM];

	std::map<char*, std::set<DWORD>, HTStr> m_mapItem;			//	위탁 아이템
	std::map<char*, std::set<DWORD>, HTStr> m_mapItemStock;		//	재고 아이템
	std::map<char*, DWORD, HTStr> m_mapMoney;					//	재고 루피아

	byte	m_byRentalTex;
	DWORD	m_dwRentalTexMoney;
	HANDLE	m_hFileHandle;

	void HS_ReadData();
	//void HS_WriteData();
	

public:
	CRentalStore(void);
	~CRentalStore(void);

	bool	HS_bAddMapToStore			(int iIndex);
	bool	HS_bDeleteMapFromStore		(int iIndex);
	bool	HS_bAddMapToStock			(int iIndex);
	bool	HS_bDeleteMapFromStock		(int iIndex);

	void	HS_Init					();
	void	HS_SetEraseDay			(DWORD dwDay);
	void	HS_SetArea				(HS2D_COORD stArea);
	bool	HS_bAddItem				(char* pName, int iStoreIndex, STRUCT_ITEM stItem, int iUserMoney, DWORD* pdwMoney, BYTE byHour);
	int		HS_iGetStockItemCount	(char* pName);										//	케릭별 재고아이템의 수를 얻어온다.
	bool	HS_bGetStockItem		(char* pName, STRUCT_ITEM* pItem);					//	케릭별 재고아이템을 하나 얻어온다.
	void	HS_GetItemList			(char* pName, STRUCT_RENTALITEM* pItemList, WORD* pwIndex);		//	케릭별 위탁한 아이템리스트를 얻어온다.
	void	HS_GetItemList			(int iStoreIndex, STRUCT_RENTALITEM* pItemList);	//	위탁상점별 아이템리스트를 얻어온다.
	void	HS_GetStockItemList		(char* pName, int iFromIndex, STRUCT_RENTALSTOCK* pItemList);
	bool	HS_bDeleteItem			(char* pName, int iIndex, STRUCT_ITEM* stItem);
	void	HS_GetShopItemPrice		(int iIndex, int* piPrice);

	void	HS_SetRentalTex			(byte	byTex);
	byte	HS_GetRentalTex			();
	void	HS_SetRentalTexMoney	(DWORD	dwTexMoney);
	void	HS_GetTexMoney			(DWORD*	dwTexMoney, bool bSearch=true);
	bool	HS_bGetMoney			(char*  pName, DWORD* pdwMoney, bool bSearch=true);

	void	HS_CheckStockItem		(void);
	void	HS_StockItem			(DWORD dwStore);
	bool	HS_bBuyItem				(int iIndex, STRUCT_ITEM stItem);
	void	HS_CheckRentalStore		();
};




#endif	//	#ifndef __RENTALSTORE_H__

