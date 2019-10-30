#ifndef __MICROSOUND_H__
#define __MICROSOUND_H__

#include "EventDefines.h"

class CMicroSound
{
public:
	CMicroSound(void);
	~CMicroSound(void);

	void Initialize();
	unsigned char UseCoupon(int * nIndex);

	unsigned short m_wIndex;
	unsigned short m_wRank[MAX_MICROSOUND_GOODS];
	unsigned short m_wCoupon[MAX_MICROSOUND];
};

#endif	//	#ifndef __MICROSOUND_H__
