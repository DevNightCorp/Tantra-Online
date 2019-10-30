#pragma once

#include <windows.h>
#include "basedef.h"

class CHTRankSystem
{
private:
	FILETIME	m_stBramanFiletime;
	char szBramanRanker[4][4][MAX_RANK][SZNAME_LENGTH];
public:
	CHTRankSystem(void);
	~CHTRankSystem(void);

	void ReadRankFile(int nWorld);
	void ReadBramanRank(int nWorld);
	int GetBramanRank(int conn);
	int	GetBramanRank(char* pChar);
};
