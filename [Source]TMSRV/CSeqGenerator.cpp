#include "CSeqGenerator.h"
#include <LIMITS.h>

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__


CSeqGenerator::CSeqGenerator() : m_wVariable(0), m_wKey(0), m_wCurrent(0)
{
}

CSeqGenerator::~CSeqGenerator()
{
}

BOOL CSeqGenerator::IsInited()
{
	return (m_wVariable == 0) ? FALSE : TRUE;
}

void CSeqGenerator::Init(DWORD dwKey)
{
	m_wVariable = (WORD)((RANDOM_VAR_MULTIPLER * (dwKey / RANDOM_VAR_DIVIDER) + RANDOM_VAR_ADDER));
	m_wKey = (WORD)(((dwKey & RANDOM_KEY_MASK) >> 1) << 1) + 1;	// 홀수를 만든다.
	m_wCurrent = GetRandom((WORD)dwKey);
}

WORD CSeqGenerator::GetRandom(WORD wPrev)
{
	wPrev += RANDOM_PREV_ADDER;
	return ((m_wVariable * wPrev + m_wKey) % RANDOM_MODULER) ^ RANDOM_BITMASK;
}

void CSeqGenerator::GoNext()
{
	m_wCurrent = GetRandom(m_wCurrent);
}

WORD CSeqGenerator::GetCurrent()
{
	return m_wCurrent;
}