#ifndef __EVENTDEFINES_H__
#define __EVENTDEFINES_H__

#define __GAMERS__

#include <windows.h>

typedef struct _HTStr
{
	template<typename PtrType>
		bool operator()( PtrType pStr1, PtrType pStr2 ) const
	{
		int i = stricmp( pStr1, pStr2 );
		if ( i < 0 )
			return ( TRUE );
		else
			return ( FALSE );
	}
} HTStr;

const int MAX_COUPONSIZE = 100000;
const int SZCOUPON_LENGTH = 14;
const int MAX_MICROSOUND_GOODS = 30;
const int MAX_MICROSOUND = 24500+100;

struct stCoupon
{
	byte byUsed;						//	0:not used, 1:used
	byte byDummy;
	char pstrData[SZCOUPON_LENGTH];
};

#endif	//	__EVENTDEFINES_H__
