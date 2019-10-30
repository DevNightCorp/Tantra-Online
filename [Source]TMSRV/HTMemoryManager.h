//----------------------------------------------------------------------------//
//	���� �̸�	: HTMemoryManager.h
//	���� ���� 	: 
//		- new, delete ���� overloading �Ͽ� �޸� ���� ���� �����ϰ��� ��
//	�ۼ���		:
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

// HK : ������ Asser��. �̳��� ���� breakpoint�� �����ϴ� ��Ȱ�� �� ��
#define InsertSimpleBreak(x) if ( (x) == HT_FALSE ) __asm { int 3 }

typedef HTtchar	ALLOC_TYPE;

const ALLOC_TYPE	HT_MM_UNKNOWN        = 0;  // HK : �޸� ������ ���� char ���� ����Ѵ�.
const ALLOC_TYPE	HT_MM_NEW            = 1;  // HK : char�� 1byte�� �ݸ鿡
const ALLOC_TYPE	HT_MM_NEW_ARRAY      = 2;  // HK : enum�� ���Ǵ� int�� 4byte�̱� �����̴�.
const ALLOC_TYPE	HT_MM_MALLOC         = 3;
const ALLOC_TYPE	HT_MM_CALLOC         = 4;
const ALLOC_TYPE	HT_MM_REALLOC        = 5;
const ALLOC_TYPE	HT_MM_DELETE         = 6;
const ALLOC_TYPE	HT_MM_DELETE_ARRAY   = 7;
const ALLOC_TYPE	HT_MM_FREE           = 8;

const HTlong		HT_PADDING			= 0xDEADC0DE;	// HK : �޸� ���� �� �ڷ� ���̴� ��. Bounds Violation�� �߻��ϴ��� Ȯ���ϱ� ����.
const HTlong		HT_BODY				= 0xBAADC0DE;	// HK : �޸� �ʱ�ȭ �ϴ� ��. ���� ���Ǵ� �޸� ������ Ȯ���ϱ� ���� ���
const HTchar		HT_BREAK_ON_DEALLOC	= 0x1;			// HK : 0x0�� ��� dealloc���� break �Ѵ�.
const HTchar		HT_BREAK_ON_REALLOC	= 0x2;
const HTint			HT_HASH_SIZE		= 1024;
const HTchar* const	HT_ALLOCATION_TYPE[]= { "Unknown", "new", "new[]", "malloc", "calloc", "realloc", "delete", "delete[]", "free" };

typedef struct _HTStackNode
{
	const	HTchar*					m_szFileName;	// HK : ���� �̸�
			HTushort				m_usLineNumber;
			struct _HTStackNode*	m_pNext;
} HTStackNode;
// HK : ���� �̸��� ���μ��� ����ϱ� ���� ������ ����ü
// HK : �޸� allocation ��ƾ���� �޾Ƶ��� �����̸��� ���μ����� ��� �����ϴ�.
// HK : �� ��� ���� delete�� �����̸��� ���μ��� �޾Ƶ��̴� �Ķ���Ͱ� ���� �����̴�.

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
// HK : ��� �޸� allocation�� Ʈ��ŷ �ϱ� ���� ������ ��� �ִ� ����ü
// HK : �� ����ü�� ������ �޸� ������ Ʈ���ϱ� ���� ������ ��� ������,
// HK : �� ����ü�� ������ ���α׷��� ����� �� log ���Ϸ� ��ϵǰ� �ȴ�.
// HK : �޸𸮸� Ʈ��ŷ �ϸ鼭 �߻��ϴ� ������带 ���̱� ���� ������ �޸𸮸� ���� ����ϴ� ���·� �����εǾ���.
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


			
			HTvoid			HT_vInitialize();										// HK : ���� ��� �޸𸮸� �ʱ�ȭ�Ѵ�.
			HTvoid			HT_vRelease();											// HK : ���� ��� �޸𸮸� �����Ѵ�.

			// HK : �ؽ� ���̺�� ����� �Լ���
			HTvoid			HT_vInsertMemoryNode( HTMemoryNode* pMemoryNode );		// HK : ���ο� �޸� ��带 �����Ѵ�.
			HTMemoryNode*	HT_pGetMemoryNode( HTvoid* pvAddress );					// HK : �޸� ��带 ȸ���Ѵ�.
			HTMemoryNode*	HT_pRemoveMemoryNode( HTvoid* pvAddress );				// HK : �޸� ��带 �����Ѵ�.
			HTbool			HT_bValidateMemoryUnit( HTMemoryNode* pMemoryNode );	// HK : �޸� ����� �޸𸮸� Ȯ���Ѵ�.

			// HK : Memory Caching to minimize allocations within the memory manager
			HTvoid			HT_vDeAllocateMemory( HTMemoryNode* pMemoryNode );
			HTMemoryNode*	HT_pAllocateMemory();

			// HK : Error Reporting Routines
			HTvoid			HT_vDumpLogReport();
			HTvoid			HT_vDumpMemoryAllocations();
			HTvoid			HT_vLogError( HTchar *szIn, ... );
private:
			HTint			HT_iGetHashIndex( HTvoid* pvAddress );					// HK : pvAddress�� ���� �ؽ� ���̺��� �ε����� �������� �Լ�
			HTint			HT_iCalculateUnAllocatedMemory();						// HK : �Ҵ���� ���� �޸𸮷��� ����ϴ� �Լ�

public:
			// HK : User programmable options
			HTint			m_iBreakOnAllocationCount;
			HTuint			m_nPaddingSize;
			HTbool			m_bLogAlways;
			HTbool			m_bCleanLogFileOnFirstRun;

			// HK : �޸� ��뿡 ���� ����
			HTint			m_iTotalMemoryAllocations;  // HK : �� �޸� �Ҵ� ��
			HTuint			m_nTotalMemoryAllocated;    // HK : �� �޸� �Ҵ� �� (����: Bytes)
			HTuint			m_nTotalMemoryUsed;         // HK : �� ���� �޸� (����: Bytes)
	
			HTuint			m_nPeakMemoryAllocation;    // HK : �ִ� �޸� �Ҵ緮
			HTuint			m_nPeakTotalNumAllocations; // HK : �ִ� �޸� �Ҵ� ��
			HTuint			m_nOverheadMemoryCost;      // HK : �� ��ƾ�� ����Ͽ� �޸� Ʈ��ŷ�� �����ν� ���� �߰� ���� �޸� ��
			HTuint			m_nPeakOverHeadMemoryCost;  // HK : �޸� Ʈ��ŷ�� ���� �ִ� �޸𸮷�
			HTuint			m_nTotalOverHeadMemoryCost; // HK : �޸� Ʈ��ŷ�� ���� ��ü �޸𸮷�
			HTuint			m_nAllocatedMemory;         // HK : ���� �Ҵ�� �޸𸮷�
			HTuint			m_nNumBoundsViolations;     // HK : �޸� Bound Violation�� �߻��� ȸ��

			HTuint			m_nNumHashEntryAllocations;	// HK : �ؽ� ���̺� ���Ե� ��Ʈ���� ��
			
			CHTMemoryStack	m_TopStack;					// HK : �޸� deallocation�� ��� �Ͼ���� üũ�ϴ� ����

private:
			HTMemoryNode*	m_ppHashTable[HT_HASH_SIZE];// HK : �޸� �Ҵ翡 �����ϴ� �ؽ� ���̺�
			HTMemoryNode*	m_pMemoryCache;				// HK : ������ ���� �޸� ��带 ĳ���ϱ� ���� ĳ��
};

class CHTMemoryManagerGlobal
{
public:
	static	HTvoid*				HT_pvAllocateMemory( const HTtchar *szFileName, HTint iLine, size_t Size, ALLOC_TYPE AllocType, HTvoid* vAddress = HT_NULL );
	// HK : ���� �޸� allocation ��ƾ. �޸𸮸� allocation �ϴ� ���� track �ϱ� ���� ����
	// HK : ��� �޸� allocation ��ƾ������ �� �Լ��� �θ���.
	
	static	HTvoid				HT_vDeAllocateMemory( HTvoid* pvAddress, ALLOC_TYPE AllocType );
	// HK : ���� �޸� deallocation ��ƾ. �޸𸮸� deallocation �ϴ� ���� track �ϱ� ���� ����
	// HK : ��� �޸� deallocation ��ƾ������ �� �Լ��� �θ���.

	static	HTvoid				HT_vDeAllocateMemory( const HTtchar* szFileName, HTint iLine, HTvoid* pvAddress, ALLOC_TYPE AllocType );
	
	static	HTvoid				HT_vSetOwner( const HTtchar* szFileName, HTint iLine );
	// HK : �ҽ� ���� �̸��� �ҽ� ���� ������ ����ϴ� ������ �Ѵ�.
	// HK : deallocation �Լ��鿡�� ���ȴ�.
	// HK : new�ʹ� �޸� delete�� �ҽ� ������ �̸��� ������ �� �� �ִ� parameter�� ���⶧���̴�.

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
// HK : new �������� overloading �Լ��̴�.
// HK : size_t Size					: new�� ���� ��û���� �޸��� ũ�� (���� : Bytes)
// HK : const HTchar* szFileName	: new�� ����� �ҽ� ������ �̸�
// HK : HTint iLine					: �ҽ� ���Ͽ��� new�� ����� ����

inline HTvoid* operator new[]( size_t Size, const HTtchar* szFileName, HTint iLine )
{ return CHTMemoryManagerGlobal::HT_pvAllocateMemory( szFileName, iLine, Size, HT_MM_NEW_ARRAY ); }
// HK : new[] �������� overloading �Լ��̴�.
// HK : size_t Size					: new�� ���� ��û���� �޸��� ũ�� (���� : Bytes)
// HK : const HTchar* szFileName	: new�� ����� �ҽ� ������ �̸�
// HK : HTint iLine					: �ҽ� ���Ͽ��� new�� ����� ����

inline HTvoid operator delete( HTvoid* pvAddress )
{ CHTMemoryManagerGlobal::HT_vDeAllocateMemory( pvAddress, HT_MM_DELETE ); }
// HK : delete �������� overloading �Լ�
// HK : HTvoid* pvAddress : deallocation�� ��û ���� �޸��� ������

inline HTvoid operator delete[]( HTvoid* pvAddress )
{ CHTMemoryManagerGlobal::HT_vDeAllocateMemory( pvAddress, HT_MM_DELETE_ARRAY ); }
// HK : delete[] �������� overloading �Լ�
// HK : HTvoid* pvAddress : deallocation�� ��û ���� �޸��� ������

// HK : ������ 4���� �Լ����� allocation ��ġ�鿡�� ������ �߻����� �ʴ� ���� �ҷ����� �ʴ´�.
// HK : Game Programmin Gems�� �η� �õ� ���� ������ ������ �־��
// HK : Visual C++�� Happy��.���� �Ѵٰ� �Ѵ�.

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