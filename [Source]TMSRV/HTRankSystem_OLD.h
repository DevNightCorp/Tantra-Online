#pragma once

#include <windows.h>
#include "basedef.h"

class CHTRankSystemOld
{
private:
	FILETIME	m_stBramanFiletime;
	char szBramanRanker[4][250][SZNAME_LENGTH];
public:
	CHTRankSystemOld(void);
	~CHTRankSystemOld(void);

	void ReadRankFile(int nWorld);
	void ReadBramanRank(int nWorld);
	int GetBramanRank(int conn);
	int	GetBramanRank(char* pChar);
};