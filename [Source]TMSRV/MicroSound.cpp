#include "microsound.h"
#include "GetFunc.h"

CMicroSound::CMicroSound(void)
{
}

CMicroSound::~CMicroSound(void)
{
}

void CMicroSound::Initialize()
{
	m_wIndex = 0;
	for(int i=0; i<MAX_MICROSOUND; i++) m_wCoupon[i] = 0;	//	¸ðµç ÄíÆù ²ÎÀ¸·Î ¼³Á¤

	//	Test table
	m_wCoupon[0] = 1;
	m_wCoupon[1] = 2;
	m_wCoupon[2] = 3;
	m_wCoupon[3] = 3;
	m_wCoupon[4] = 4;
	m_wCoupon[5] = 4;
	m_wCoupon[6] = 4;
	m_wCoupon[7] = 4;
	m_wCoupon[8] = 5;
	m_wCoupon[9] = 5;

	m_wCoupon[10] = 5;
	m_wCoupon[11] = 5;
	m_wCoupon[12] = 5;
	m_wCoupon[13] = 5;
	m_wCoupon[14] = 5;
	m_wCoupon[15] = 6;
	m_wCoupon[16] = 6;
	m_wCoupon[17] = 6;
	m_wCoupon[18] = 6;
	m_wCoupon[19] = 6;

	m_wCoupon[20] = 6;
	m_wCoupon[21] = 6;
	m_wCoupon[22] = 6;
	m_wCoupon[23] = 6;
	m_wCoupon[24] = 6;
	m_wCoupon[25] = 6;
	m_wCoupon[26] = 6;
	m_wCoupon[27] = 6;
	m_wCoupon[28] = 6;
	m_wCoupon[29] = 6;

	//	Real table
	bool bFind = false;
	m_wRank[0] = GetRandom(3600, 10600);
	m_wRank[1] = GetRandom(10600, 21100);
	for(i=2; i<MAX_MICROSOUND_GOODS; i++) 
	{
		while(1)
		{
			bFind = false;
			m_wRank[i] = GetRandom(100, 24600);
			for(int k=2; k<i; k++)
			{
				if(m_wRank[k] == m_wRank[i])
				{	bFind = true; break;
				}
			}
			if(!bFind) break;
		}
		if(m_wRank[i]<100 || m_wRank[i]>=24600) 
		{
			MessageBox(NULL, "MicroSound Coupon Initialze Fail.", "Error", MB_OK);
			return;
		}
	}

	m_wCoupon[m_wRank[0]] = 1;
	m_wCoupon[m_wRank[1]] = 2;
	m_wCoupon[m_wRank[2]] = 3;
	m_wCoupon[m_wRank[3]] = 3;
	m_wCoupon[m_wRank[4]] = 4;
	m_wCoupon[m_wRank[5]] = 4;
	m_wCoupon[m_wRank[6]] = 4;
	m_wCoupon[m_wRank[7]] = 4;
	m_wCoupon[m_wRank[8]] = 5;
	m_wCoupon[m_wRank[9]] = 5;

	m_wCoupon[m_wRank[10]] = 5;
	m_wCoupon[m_wRank[11]] = 5;
	m_wCoupon[m_wRank[12]] = 5;
	m_wCoupon[m_wRank[13]] = 5;
	m_wCoupon[m_wRank[14]] = 5;
	m_wCoupon[m_wRank[15]] = 6;
	m_wCoupon[m_wRank[16]] = 6;
	m_wCoupon[m_wRank[17]] = 6;
	m_wCoupon[m_wRank[18]] = 6;
	m_wCoupon[m_wRank[19]] = 6;

	m_wCoupon[m_wRank[20]] = 6;
	m_wCoupon[m_wRank[21]] = 6;
	m_wCoupon[m_wRank[22]] = 6;
	m_wCoupon[m_wRank[23]] = 6;
	m_wCoupon[m_wRank[24]] = 6;
	m_wCoupon[m_wRank[25]] = 6;
	m_wCoupon[m_wRank[26]] = 6;
	m_wCoupon[m_wRank[27]] = 6;
	m_wCoupon[m_wRank[28]] = 6;
	m_wCoupon[m_wRank[29]] = 6;
}

unsigned char CMicroSound::UseCoupon(int *nIndex)
{
	*nIndex = m_wIndex;
	if(m_wIndex<0 || m_wIndex >= 24600) return 0;

	return (unsigned char)m_wCoupon[m_wIndex++];
}
