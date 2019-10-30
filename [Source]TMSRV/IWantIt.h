#ifndef __IWANTIT_H__
#define __IWANTIT_H__

#include "BaseDef.h"
#include "EventDefines.h"

class CIWantIt
{
private:
	std::map<char*, int, HTStr> m_mapTable;
	short	m_arrsnValue[20];
	char	m_pCharName[20][20];
	char	m_pJoinUser[20000][20];
	int		m_nIndex;
public:
	CIWantIt(void);
	~CIWantIt(void);

	void	Initialize();
	int		GetUserItemCount(char* pChar);
	void	IncreaseUserItemCount(char* pChar);
	void	GetRankUser(char *pData);
	void	InsertRank(char* pChar, int nCount);
	void	CloseEvent();
};

#endif	//	__IWANTIT_H__