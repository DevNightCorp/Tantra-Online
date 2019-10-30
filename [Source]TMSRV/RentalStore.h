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

	std::map<char*, std::set<DWORD>, HTStr> m_mapItem;			//	��Ź ������
	std::map<char*, std::set<DWORD>, HTStr> m_mapItemStock;		//	��� ������
	std::map<char*, DWORD, HTStr> m_mapMoney;					//	��� ���Ǿ�

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
	int		HS_iGetStockItemCount	(char* pName);										//	�ɸ��� ���������� ���� ���´�.
	bool	HS_bGetStockItem		(char* pName, STRUCT_ITEM* pItem);					//	�ɸ��� ���������� �ϳ� ���´�.
	void	HS_GetItemList			(char* pName, STRUCT_RENTALITEM* pItemList, WORD* pwIndex);		//	�ɸ��� ��Ź�� �����۸���Ʈ�� ���´�.
	void	HS_GetItemList			(int iStoreIndex, STRUCT_RENTALITEM* pItemList);	//	��Ź������ �����۸���Ʈ�� ���´�.
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

