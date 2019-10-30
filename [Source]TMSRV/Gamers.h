#ifndef __GAMERS_H__
#define __GAMERS_H__

#include <map>
#include "EventDefines.h"

class CGamers
{
private:
	std::map<char*, int, HTStr> m_mapTable;
	stCoupon	m_stCoupon[MAX_COUPONSIZE];
	int			m_iMaxCoupon;
public:
	CGamers(void);
	~CGamers(void);
	bool UseCoupon(char* pData);		//	0:success, 1:already used, 2:out of Index
	bool Initialize();
	bool WriteCoupon();
	void CloseEvent();
};

#endif	//	__GAMERS_H__
