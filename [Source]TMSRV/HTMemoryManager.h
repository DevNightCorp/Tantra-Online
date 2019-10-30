//----------------------------------------------------------------------------//
//	파일 이름	: HTMemoryManager.h
//	파일 설명 	: 
//		- new, delete 등을 overloading 하여 메모리 누수 등을 관리하고자 함
//	작성자		:
//		- 2002/04/10, Created by HK (Reference to Game Programming Gems 2)
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#ifndef _HTMEMORYMANAGER_H_
#define _HTMEMORYMANAGER_H_

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "Windows.h"

typedef	void					HTvoid;
typedef bool					HTbool;

typedef char					HTchar;
typedef char					HTtchar;
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

//typedef RECT					HT_RECT;

#define HT_NULL					0

#define HT_TRUE					1
#define HT_FALSE				0

#define HT_MAX_STR				256

//#ifdef _DEBUG
#define HT_ACTIVATE_MEMORY_MANAGER
//#endif // #ifndef _DEBUG

#include "HTNew_off.h"

#ifdef HT_ACTIVATE_MEMORY_MANAGER

#define MAX_FILNE_NAME_SIZE 30

// HK : 간단한 Asser다. 이놈은 단지 breakpoint를 삽입하는 역활을 할 뿐
#define InsertSimpleBreak(x) if ( (x) == HT_FALSE ) __asm { int 3 }

typedef HTtchar	ALLOC_TYPE;

const ALLOC_TYPE	HT_MM_UNKNOWN        = 0;  // HK : 메모리 절약을 위해 char 형을 사용한다.
const ALLOC_TYPE	HT_MM_NEW            = 1;  // HK : char은 1byte인 반면에
const ALLOC_TYPE	HT_MM_NEW_ARRAY      = 2;  // HK : enum에 사용되는 int는 4byte이기 때문이다.
const ALLOC_TYPE	HT_MM_MALLOC         = 3;
const ALLOC_TYPE	HT_MM_CALLOC         = 4;
const ALLOC_TYPE	HT_MM_REALLOC        = 5;
const ALLOC_TYPE	HT_MM_DELETE         = 6;
const ALLOC_TYPE	HT_MM_DELETE_ARRAY   = 7;
const ALLOC_TYPE	HT_MM_FREE           = 8;

const HTlong		HT_PADDING			= 0xDEADC0DE;	// HK : 메모리 영역 앞 뒤로 붙이는 값. Bounds Violation이 발생하는지 확인하기 위함.
const HTlong		HT_BODY				= 0xBAADC0DE;	// HK : 메모리 초기화 하는 값. 실제 사용되는 메모리 영역을 확인하기 위해 사용
const HTchar		HT_BREAK_ON_DEALLOC	= 0x1;			// HK : 0x0인 경우 dealloc에서 break 한다.
const HTchar		HT_BREAK_ON_REALLOC	= 0x2;
const HTint			HT_HASH_SIZE		= 1024;
const HTchar* const	HT_ALLOCATION_TYPE[]= { "Unknown", "new", "new[]", "malloc", "calloc", "realloc", "delete", "delete[]", "free" };

typedef struct _HTStackNode
{
	const	HTchar*					m_szFileName;	// HK : 파일 이름
			HTushort				m_usLineNumber;
			struct _HTStackNode*	m_pNext;
} HTStackNode;
// HK : 파일 이름과 라인수를 기억하기 스택 형식의 구조체
// HK : 메모리 allocation 루틴에서 받아들인 파일이름과 라인수만이 기억 가능하다.
// HK : 이 모든 것이 delete는 파일이름과 라인수를 받아들이는 파라메터가 없기 때문이다.

typedef struct _HTMemoryNode
{
	size_t					m_ActualSize;
	size_t					m_ReportedSize;
	HTvoid*					m_pvActualAddress;
	HTvoid*					m_pvReportedAddress;
	HTtchar					m_szSourceFile[MAX_FILNE_NAME_SIZE];
	HTushort				m_usSourceLine;
	HTushort				m_usPaddingSize;
	HTchar					m_cOptions;
	HTlong					m_lPredefinedBody;
	ALLOC_TYPE				m_AllocationType;
	struct _HTMemoryNode*	m_pPrev;
	struct _HTMemoryNode*	m_pNext;

	_HTMemoryNode()
	{
		m_ActualSize = 0;
		m_ReportedSize = 0;
		m_pvActualAddress = HT_NULL;
		m_pvReportedAddress = HT_NULL;
		m_usSourceLine = 0;
		m_usPaddingSize = 0;
		m_cOptions = 0;
		m_lPredefinedBody = 0;
		m_AllocationType = HT_MM_UNKNOWN;
		m_pPrev = HT_NULL;
		m_pNext = HT_NULL;
	}

	HTvoid					HT_vInitializeMemory( HTlong lBody = HT_BODY ) ; // Initailize the nodes memory for interrogation.
} HTMemoryNode;
// HK : 모든 메모리 allocation을 트랙킹 하기 위한 정보를 담고 있는 구조체
// HK : 이 구조체의 정보는 메모리 문제를 트랙하기 위한 정보를 담고 있으며,
// HK : 이 구조체의 내용은 프로그램이 종료될 때 log 파일로 기록되게 된다.
// HK : 메모리를 트랙킹 하면서 발생하는 오버헤드를 줄이기 위해 가능한 메모리를 적게 사용하는 형태로 디자인되었다.
class CHTMemoryManagerInitialize { public: CHTMemoryManagerInitialize(); };
static CHTMemoryManagerInitialize InitMemoryManager;

class CHTMemoryStack
{
public:
					CHTMemoryStack() {}
	HTvoid			HT_vInit() { m_pHead = HT_NULL; m_nCount = 0; }
	HTbool			HT_bEmpty() { return (m_nCount == 0); }
	HTStackNode*	HT_pGetHead() { return m_pHead; }
	HTvoid			HT_vPush( HTStackNode* pStackNode )
					{
						if ( !pStackNode ) return;
						pStackNode->m_pNext = m_pHead;
						m_pHead = pStackNode;
						m_nCount++;
					}
	HTStackNode*	HT_pPop()
					{
						HTStackNode* pStackNode = m_pHead;
						if ( pStackNode ) m_pHead = m_pHead->m_pNext;
						m_nCount--;
						return pStackNode;
					}
private:
	HTStackNode*	m_pHead;
	HTint			m_nCount;
};

class CHTMemoryManager
{
public:
							CHTMemoryManager();
							~CHTMemoryManager();


			
			HTvoid			HT_vInitialize();										// HK : 내부 사용 메모리를 초기화한다.
			HTvoid			HT_vRelease();											// HK : 내부 사용 메모리를 해제한다.

			// HK : 해쉬 테이블과 관계된 함수들
			HTvoid			HT_vInsertMemoryNode( HTMemoryNode* pMemoryNode );		// HK : 새로운 메모리 노드를 삽입한다.
			HTMemoryNode*	HT_pGetMemoryNode( HTvoid* pvAddress );					// HK : 메모리 노드를 회수한다.
			HTMemoryNode*	HT_pRemoveMemoryNode( HTvoid* pvAddress );				// HK : 메모리 노드를 제거한다.
			HTbool			HT_bValidateMemoryUnit( HTMemoryNode* pMemoryNode );	// HK : 메모리 노드의 메모리를 확인한다.

			// HK : Memory Caching to minimize allocations within the memory manager
			HTvoid			HT_vDeAllocateMemory( HTMemoryNode* pMemoryNode );
			HTMemoryNode*	HT_pAllocateMemory();

			// HK : Error Reporting Routines
			HTvoid			HT_vDumpLogReport();
			HTvoid			HT_vDumpMemoryAllocations();
			HTvoid			HT_vLogError( HTchar *szIn, ... );
private:
			HTint			HT_iGetHashIndex( HTvoid* pvAddress );					// HK : pvAddress에 의해 해쉬 테이블의 인덱스를 가져오는 함수
			HTint			HT_iCalculateUnAllocatedMemory();						// HK : 할당되지 않은 메모리량을 계산하는 함수

public:
			// HK : User programmable options
			HTint			m_iBreakOnAllocationCount;
			HTuint			m_nPaddingSize;
			HTbool			m_bLogAlways;
			HTbool			m_bCleanLogFileOnFirstRun;

			// HK : 메모리 사용에 관한 정보
			HTint			m_iTotalMemoryAllocations;  // HK : 총 메모리 할당 수
			HTuint			m_nTotalMemoryAllocated;    // HK : 총 메모리 할당 량 (단위: Bytes)
			HTuint			m_nTotalMemoryUsed;         // HK : 총 사용된 메모리 (단위: Bytes)
	
			HTuint			m_nPeakMemoryAllocation;    // HK : 최대 메모리 할당량
			HTuint			m_nPeakTotalNumAllocations; // HK : 최대 메모리 할당 수
			HTuint			m_nOverheadMemoryCost;      // HK : 이 루틴을 사용하여 메모리 트랙킹을 함으로써 현재 추가 사용된 메모리 양
			HTuint			m_nPeakOverHeadMemoryCost;  // HK : 메모리 트랙킹에 사용된 최대 메모리량
			HTuint			m_nTotalOverHeadMemoryCost; // HK : 메모리 트랙킹에 사용된 전체 메모리량
			HTuint			m_nAllocatedMemory;         // HK : 현재 할당된 메모리량
			HTuint			m_nNumBoundsViolations;     // HK : 메모리 Bound Violation이 발생한 회수

			HTuint			m_nNumHashEntryAllocations;	// HK : 해쉬 테이블에 삽입된 엔트리의 수
			
			CHTMemoryStack	m_TopStack;					// HK : 메모리 deallocation이 어디서 일어났는지 체크하는 스택

private:
			HTMemoryNode*	m_ppHashTable[HT_HASH_SIZE];// HK : 메모리 할당에 관여하는 해쉬 테이블
			HTMemoryNode*	m_pMemoryCache;				// HK : 사용되지 않은 메모리 노드를 캐쉬하기 위한 캐쉬
};

class CHTMemoryManagerGlobal
{
public:
	static	HTvoid*				HT_pvAllocateMemory( const HTtchar *szFileName, HTint iLine, size_t Size, ALLOC_TYPE AllocType, HTvoid* vAddress = HT_NULL );
	// HK : 메인 메모리 allocation 루틴. 메모리를 allocation 하는 것을 track 하기 위해 존재
	// HK : 모든 메모리 allocation 루틴에서는 이 함수를 부른다.
	
	static	HTvoid				HT_vDeAllocateMemory( HTvoid* pvAddress, ALLOC_TYPE AllocType );
	// HK : 메인 메모리 deallocation 루틴. 메모리를 deallocation 하는 것을 track 하기 위해 존재
	// HK : 모든 메모리 deallocation 루틴에서는 이 함수를 부른다.

	static	HTvoid				HT_vDeAllocateMemory( const HTtchar* szFileName, HTint iLine, HTvoid* pvAddress, ALLOC_TYPE AllocType );
	
	static	HTvoid				HT_vSetOwner( const HTtchar* szFileName, HTint iLine );
	// HK : 소스 파일 이름과 소스 상의 라인을 기록하는 역할을 한다.
	// HK : deallocation 함수들에서 사용된다.
	// HK : new와는 달리 delete는 소스 파일의 이름과 라인을 알 수 있는 parameter가 없기때문이다.

	static	HTbool				HT_bInitializeMemoryManager();
	static	HTvoid				HT_vReleaseMemoryManager();
	static	HTtchar*			HT_szFormatOwnerString( const HTchar* szFileName, HTint iLine );
	static	HTtchar*			HT_szSourceFileStripper( const HTchar* szSourceFileName );
	static	HTvoid				HT_vLog( HTchar* szIn, ... );
	static	HTtchar*			HT_szInsertCommas( HTulong lValue );
	static	HTtchar*			HT_szMemorySizeString( HTulong lSize, HTbool bLengthenString = HT_TRUE );
};

static	CHTMemoryManager*	g_pMemoryManager = HT_NULL;
static	HTint				g_nNumMemoryAllocations = 0;
static	HTchar				g_szLogFileName[MAX_FILNE_NAME_SIZE] = "HTMemoryLogFile.log";

inline HTvoid* operator new( size_t Size, const HTtchar* szFileName, HTint iLine )
{ return CHTMemoryManagerGlobal::HT_pvAllocateMemory( szFileName, iLine, Size, HT_MM_NEW ); }
// HK : new 연산자의 overloading 함수이다.
// HK : size_t Size					: new를 통해 요청받은 메모리의 크기 (단위 : Bytes)
// HK : const HTchar* szFileName	: new가 실행된 소스 파일의 이름
// HK : HTint iLine					: 소스 파일에서 new가 실행된 라인

inline HTvoid* operator new[]( size_t Size, const HTtchar* szFileName, HTint iLine )
{ return CHTMemoryManagerGlobal::HT_pvAllocateMemory( szFileName, iLine, Size, HT_MM_NEW_ARRAY ); }
// HK : new[] 연산자의 overloading 함수이다.
// HK : size_t Size					: new를 통해 요청받은 메모리의 크기 (단위 : Bytes)
// HK : const HTchar* szFileName	: new가 실행된 소스 파일의 이름
// HK : HTint iLine					: 소스 파일에서 new가 실행된 라인

inline HTvoid operator delete( HTvoid* pvAddress )
{ CHTMemoryManagerGlobal::HT_vDeAllocateMemory( pvAddress, HT_MM_DELETE ); }
// HK : delete 연산자의 overloading 함수
// HK : HTvoid* pvAddress : deallocation을 요청 받은 메모리의 포인터

inline HTvoid operator delete[]( HTvoid* pvAddress )
{ CHTMemoryManagerGlobal::HT_vDeAllocateMemory( pvAddress, HT_MM_DELETE_ARRAY ); }
// HK : delete[] 연산자의 overloading 함수
// HK : HTvoid* pvAddress : deallocation을 요청 받은 메모리의 포인터

// HK : 다음의 4개의 함수들은 allocation 장치들에서 에러가 발생하지 않는 한은 불려지지 않는다.
// HK : Game Programmin Gems의 부록 시디에 보면 다음을 정의해 주어야
// HK : Visual C++이 Happyㅡ.ㅡ해 한다고 한다.

inline HTvoid* operator new( size_t Size )
{ return malloc( Size ); }

inline HTvoid* operator new[]( size_t Size )
{ return malloc( Size ); }

inline HTvoid operator delete( HTvoid *vAddress, const HTchar* szFileName, HTint iLine )
{ free( vAddress ); }

inline HTvoid operator delete[]( HTvoid *vAddress, const HTchar* szFileName, HTint iLine )
{ free( vAddress ); }

#include "HTNew_on.h"

#endif // #ifdef HT_ACTIVATE_MEMORY_MANAGER
#endif // #ifndef _HTMEMORYMANAGER_H_