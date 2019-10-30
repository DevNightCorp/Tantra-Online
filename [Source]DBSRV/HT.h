//----------------------------------------------------------------------------//
//	파일 이름	: HT.h
//	파일 설명 	: 
//		- 라이브러리의 모든 소스 파일들은 이 헤더를 stdafx.h에 포함시켜야한다!
//		- C Run Time, Window, STL, DirectX 헤더를 포함시켰다.
//		- 유용한 매크로들을 포함시켰다.
//		- 데이타 타입을 재정의했다.
//	작성자		:
//		- 2002/03/15, Created by HK
//		- 2002/04/01, Modified by Assrada
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#ifndef _HT_H_
#define _HT_H_

//----------------------------------------------------------------------------//
//																			  
// C Run Time Header Files

#ifndef _WINDOWS_H_
#define _WINDOWS_H_
#include <windows.h>
#endif

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif

#ifndef _TCHAR_H_
#define _TCHAR_H_
#include <tchar.h>
#endif

#ifndef _ASSERT_H_
#define _ASSERT_H_
#include <assert.h>
#endif

#ifndef _MATH_H_
#define _MATH_H_
#include <math.h>
#endif

#ifndef _TIME_H_
#define _TIME_H_
#include <time.h>
#endif

#ifndef _CRTDBG_H_
#define _CRTDBG_H_
#include <crtdbg.h>
#endif

#ifndef _STDARG_H_
#define _STDARG_H_
#include <stdarg.h>
#endif

//----------------------------------------------------------------------------//
//																			  
// STL Library Headers

#ifndef _STL_HEADER_
#define _STL_HEADER_

// map을 사용하면 Compile시 WARNING 4786가 마구 뜬다. MS STL 버그같다.
#pragma warning(disable:4786)
#include <iterator>
#include <stack>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <set>
//#include <hash_map>
#include <ostream>
#include <string>

using namespace std;

#endif	// _STL_HEADER_

//#pragma warning(disable:4251)	// dll interface warning...

//----------------------------------------------------------------------------//
//																			  
//	 Helpful Macro definitions.

#define HT_MAX_STR				256
#define HT_NULL					0

#define HT_TRUE					1
#define HT_FALSE				0

// 리턴 코드 용으로써의 반환값 플래그
//	 High 8 bits: error flags
//	 Low 24 bits: error code
typedef unsigned int			HTRESULT;

#define HT_OK					0	
#define HT_FAIL					0x80004005		// HRESULT의 E_FAIL값과 같다.

#define HT_SUCCEED(C)			((C) == HT_OK)
#define HT_FAILED(C)			((C) != HT_OK)

//----------------------------------------------------------------------------//
//																			  
//	 Helpful math definitions.

#define HT_PI					3.1415926535897932384626433832795f
#define HT_PIX2					6.283185307178f
#define HT_PIDIV2				1.5707963267948966192313216916398f
#define HT_PIDIV4				0.7853981633974483096156608458199f
#define HT_PIDIV6				0.5235987755982988730771072305466f
#define HT_PIDIV8				0.3926990816987241548078304229099f
#define HT_PIDIV12				0.2617993877991494365385536152733f

#define	HT_EPSILON				0.000001f

#define HT_DEGREE_TO_RADIAN(degree) ((degree) * (HT_PI / 180.0f))
#define HT_RADIAN_TO_DEGREE(radian) ((radian) * (180.0f / HT_PI))

#define HT_ABS(x)				((x) < 0 ? -(x) : (x))
#define HT_MIN(a,b)				((a) < (b) ? (a) : (b))
#define HT_MIN3(a,b,c)			((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define HT_MAX(a,b)				((a) > (b) ? (a) : (b))
#define HT_MAX3(a,b,c)			((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
#define HT_CLAMP(min,x,max)		{if (x < min) x = min; if (x > max ) x = max;}
#define HT_SIGN( x )			((x) > 0 ? 1 : ((x) == 0 ? 0: (-1)))	// 양수:1, 0, 음:-1
#define HT_DIFF(a,b)			(((a) < (b)) ? ((b) - (a)) : ((a) - (b)))
#define HT_INTERPOLATE( start, end, f )		( (start) + (((end) - (start)) * (f)) )

//----------------------------------------------------------------------------//
//																			  
// Miscellaneous helper functions

#define HT_DELETE(x)			{ if (x) { delete(x); (x)=0; } }
#define HT_DELETEARRAY(x)		{ if (x) { delete[](x); (x)=0; } }
#define HT_FREE(x)				{ if (x) { free(x); (x)=0; } }
#define HT_RELEASE(x)			{ if (x) { (x)->Release(); (x)=0; } }
#define HT_CHECK(x)				{ if (HT_FAILED(x)) return HT_FAIL; }
//#define HT_ASSERT(x)			{ if (!x) assert(0); }
// HK : 20020819 Assert를 재정의해버렸다. 이상하게 warning이 자꾸 뜨길래.... HTDebug를 참조해보자.

//----------------------------------------------------------------------------//
//																			  
//  Data Type Redifinition

typedef	void					HTvoid;
typedef bool					HTbool;

typedef char					HTchar;
typedef TCHAR					HTtchar;
typedef signed short			HTshort;
typedef signed int				HTint;
typedef signed long				HTlong;

typedef unsigned char			HTuchar;
typedef unsigned short			HTushort;
typedef unsigned int			HTuint;
typedef unsigned long			HTulong;

typedef unsigned char			HTbyte;
typedef unsigned short			HTword;
typedef unsigned long			HTdword;
typedef unsigned __int64		HTqword;

typedef signed __int8			HTint8;
typedef signed __int16			HTint16;
typedef signed __int32			HTint32;
typedef signed __int64			HTint64;

typedef float					HTfloat;
typedef double					HTdouble;
typedef long double				HTldouble;

typedef RECT					HT_RECT;

#endif // #ifndef _HT_H_